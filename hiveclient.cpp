#include "hiveodbc.h"

/* DBExecute */
typedef struct {
		unsigned int inidata;
        unsigned int req_len;
        char req[8];
        unsigned int   cd1;
        unsigned int   cd2;
        unsigned short len;
        char query[1024];
}TP_DBExecute;

typedef struct {
        unsigned int id;
        unsigned int req_len;
        char req[8];
        unsigned int ret;
        unsigned int cd1;
        unsigned int cd2;
        char msg[1024];
}REQ_DBExecute;

/* FetchOne */
typedef struct {
		unsigned int inidata;
        unsigned int req_len;
        char req[16];
}TP_DBFetchOne;

typedef struct {
        unsigned int id;
        unsigned int req_len;
        char req[8];
        char dummy[11];
        char data[1024];
}REQ_DBFetchOne;

/* FetchN */
typedef struct {
		unsigned int inidata;
        unsigned int req_len;
        char req[8];
		unsigned int fetch_cnt;
		unsigned int fetch_max;
		char dummy[4];
}TP_DBFetchN;

typedef struct {
        unsigned int id;
        unsigned int req_len;
        char req[14];
		unsigned char rec_cnt[4];
}REQ_DBFetchN;

/* fetchNキャッシュ */
static int fetchN_rec=0;
static int fetchN_cnt=0;
static int fetchN_read=0;
static int fetchN_ptr=0;
static REQ_DBFetchN fetchN_res;
static char fetchN_data[1024*100];
static char fetchN_keep[1024];
static int  fetchN_keep_len;


int DBConnect(char *svr,short port){
	return tcp_connect(svr,port);
}

int DBDisconnect(){
	return tcp_disconnect();
}

int DBExecute(int sockfd,char *query){
        unsigned int inidata=ntohl(0x80010001);
        TP_DBExecute req;
        REQ_DBExecute res;
        int ret;

		fetchN_rec=0;
		fetchN_cnt=0;
		fetchN_read=0;
		fetchN_ptr=0;
		fetchN_keep_len=0;

        /* 送信 */
		req.inidata=ntohl(0x80010001);
        strcpy(req.req,"execute");
        req.req_len=ntohl(strlen(req.req));
        req.cd1=ntohl(0x0b);
        req.cd2=ntohl(0x00010000);
        req.len=htons(strlen(query));
        strcpy(req.query,query);
        ret=tcp_write((char*)&req, 26+strlen(query)+1);

        /* 応答 */
        ret=tcp_read((char*)&res, sizeof(res));
		if ( ret < 0 ){ return -1; }
        if ( res.ret == 0 ){ return 0; }

        return -2;
}

int DBFetchOne(int sockfd,char *out){
        TP_DBFetchOne req;
        REQ_DBFetchOne res;
        int ret;
		
		out[0]=NULL;

        /* 送信 */
        memset((void*)&req,(int)0,sizeof(TP_DBFetchOne));
		req.inidata=ntohl(0x80010001);
        strcpy(req.req,"fetchOne");
        req.req_len=ntohl(strlen(req.req));
        ret=tcp_write((char*)&req, 21);

        /* 応答 */
        ret=tcp_read((char*)&res, sizeof(res));
		if ( ret < 0 ){ return -1; }
        if ( strlen(res.data) == 0 ){ return 0; }

		strcpy(out,res.data);
        return 1;
}

static int DBFetchN_GetData(char *out){
	int sv_len=0;
	unsigned int w;

	if ( fetchN_rec <= 0 ){ return 0; }
	if ( fetchN_cnt >= fetchN_rec ){ return 0; }

	/* バッファコピー＆次のデータ位置設定 */
	while(1){
		if ( fetchN_ptr >= fetchN_read ){
			//debuglog("DBFetchN_GetData() length short1 (ptr=%d/%d keep=%d sv_len=%d)",fetchN_ptr,fetchN_read,fetchN_keep_len,sv_len);
			return 2;
		}
		if ( fetchN_keep_len > 4 && fetchN_data[fetchN_ptr] == NULL ){ break; }
		fetchN_keep[fetchN_keep_len++]=fetchN_data[fetchN_ptr++];
		fetchN_keep[fetchN_keep_len]=NULL;
	}


	/* 文字数 */
	if ( fetchN_keep_len <= 4 ){
		//debuglog("DBFetchN_GetData() length short2 (ptr=%d/%d keep=%d sv_len=%d)",fetchN_ptr,fetchN_read,fetchN_keep_len,sv_len);
		return 2;
	}
	memcpy((char*)&w, fetchN_keep, 4);
	sv_len = htonl(w);
	if ( sv_len <= 0 ){
		debuglog("DBFetchN_GetData() length error");
		return 0;
	}

	/* １行分のデータ */
	if ( strlen(fetchN_keep+4) < sv_len ){
		//debuglog("DBFetchN_GetData() length short3 (ptr=%d/%d keep=%d sv_len=%d)",fetchN_ptr,fetchN_read,fetchN_keep_len,sv_len);
		return 2;
	}
	fetchN_cnt++;
	strcpy(out,fetchN_keep+4);
	fetchN_keep_len=0;

	//debuglog("DBFetchN_GetData() %d/%d %d/%d [%d,%s]",fetchN_cnt,fetchN_rec, fetchN_ptr,fetchN_read, sv_len,out);
	return 1;
}


int DBFetchN(int sockfd,char *out){
        TP_DBFetchN req;
        int ret;
		unsigned int w;
		
		out[0]=NULL;

		/* キャッシュより読み込み */
		ret=DBFetchN_GetData(out);
		if ( ret == 1 ){ return 1; }
		if ( ret == 0 && fetchN_cnt>=1 ){ return 0; }

		//初期化
		fetchN_ptr=0;
        memset((void*)&req,(int)0,sizeof(TP_DBFetchN));
        memset((void*)&fetchN_res,(int)0,sizeof(fetchN_res));
		memset((void*)&fetchN_data,(int)0,sizeof(fetchN_data));

		//初期リクエスト
		if ( fetchN_cnt == 0 ){
	        /* リクエスト送信 */
			req.inidata=ntohl(0x80010001);
        	strcpy(req.req,"fetchN");
        	req.req_len=ntohl(strlen(req.req));
			req.fetch_cnt=ntohl(0x00000800);
			req.fetch_max=ntohl(0x01000020);
        	ret=tcp_write((char*)&req, 26);

	        /* 応答(ヘッダ部) */
	        ret=tcp_read((char*)&fetchN_res, 26);
			if ( ret < 26 ){ return -1; }

			/* 取得したレコード数 */
			memcpy((char*)&w, fetchN_res.rec_cnt, 4);
			fetchN_rec = htonl(w);
	        if ( fetchN_rec <= 0 ){ return 0; }
		}


		/* 応答(データ部) */
	    fetchN_read=tcp_read((char*)&fetchN_data, sizeof(fetchN_data));
		//debuglog("DBFetchN() tcp_read=%d",fetchN_read);
		if ( fetchN_read < 0 ){ return -1; }


		if ( DBFetchN_GetData(out) == 1 ){ return 1; }
        return 0;
}

