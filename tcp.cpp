#include "hiveodbc.h"

/* サーバ接続 */
int tcp_connect(char *server_name,short server_port){
	int ret;
	int flags;
	struct sockaddr_in client_addr;
	WSADATA data;

	WSAStartup(MAKEWORD(2,0), &data);

	/*client_addr構造体に、接続するサーバのアドレス・ポート番号を設定 */
	memset(&client_addr, 0, sizeof(client_addr));
	client_addr.sin_family = AF_INET;
	client_addr.sin_addr.s_addr = inet_addr(server_name);
	client_addr.sin_port = htons(server_port);

	/* ソケットを生成 */
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		tcp_disconnect();
		sockfd=(-1);
		return -1;
	}

	/* サーバに接続 */
	ret=connect(sockfd, (struct sockaddr *)&client_addr, sizeof(client_addr));
	if ( ret < 0 ){
		tcp_disconnect();
		sockfd=(-1);
		return -2;
	}

	return 0;
}

/* 送信 */
int tcp_write(char *buf, int buf_len){
	int ret;
	if ( sockfd == (-1) ){ return -1; }
	ret=send(sockfd, buf, buf_len, 0);
	return ret;
}

/* 受信 */
int tcp_read(char *buf, int buf_len){
	int ret;
	if ( sockfd == (-1) ){ return -1; }
	ret=recv(sockfd, buf, buf_len, 0);
	return ret;
}

/* ソケットをクローズ */
int tcp_disconnect(){
	if ( sockfd == (-1) ){ return -1; }
	closesocket(sockfd);
	WSACleanup();
	sockfd=(-1);
	return 0;
}

