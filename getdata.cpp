#include "hiveodbc.h"

static char fetch_fase=0;
static int  fetch_cols;
static char fetch_table[1024];
static char fetch_data[1024];
static char fetch_data_sjis[1024];
static char fetch_data_utf16[1024];
static char fetch_func[1024];
static char fetch_query[1024];

static char *strSepValue(char *s1,char sep1,int idx1){
	static char wk[1024];
	int i,j,idx;

	wk[0]=NULL;
	//sep1で区切った対象文字列先頭までスキップ
	for ( i=0,idx=0; s1[i]!=NULL; i++){
		if ( idx == idx1 ){ break; }
		if ( s1[i] == sep1 ){ idx++; }
	}
	if ( idx != idx1 ){ return wk; }

	//sep1もしくは最終までコピー
	for ( j=0; s1[i]!=NULL; i++){
		if ( s1[i] == sep1 ){ break; }
		wk[j++]=s1[i];
		wk[j]=NULL;
	}

	return wk;
}

static char *strCut(char *in, char c){
	static char wk[1024];
	int i,j,idx;

	wk[0]=NULL;
	for ( i=0,idx=0; in[i]!=NULL; i++){
		if ( in[i] == c ){ continue; }
		wk[idx++]=in[i];
		wk[idx]=NULL;
	}
	return wk;
}



SQLRETURN SQL_API SQLAllocStmt(
    SQLHDBC            hdbc,
    SQLHSTMT FAR      *phstmt)
{
    IB_DBC  * pdbc  = (IB_DBC  *)hdbc;
    IB_STMT * pstmt;
    //ISC_STATUS  *status;

    if( pdbc == NULL ) return SQL_ERROR;

    debuglog("SQLAllocStmt(%X)",(int)pdbc);
    //status = pdbc->err.status;
    if( pdbc->stmt == NULL ) {
        pstmt = pdbc->stmt = (IB_STMT*)malloc( sizeof( IB_STMT ) );
    } else {
        pstmt = pdbc->stmt;
        while( pstmt->next_stmt ) pstmt = (IB_STMT*)pstmt->next_stmt;
		pstmt->next_stmt =(IB_STMT*) malloc( sizeof( IB_STMT ) );
        pstmt = (IB_STMT*)pstmt->next_stmt;
    }
    memset( pstmt, 0, sizeof( IB_STMT ) );
    pstmt->pare_dbc = pdbc;
    //if( isc_dsql_allocate_statement(status, &pdbc->db, &pstmt->isc_hstmt ) ) {
    //    set_server_error( &pdbc->err ) ;
    //    return SQL_ERROR;
    //}
    *phstmt = (SQLHSTMT)pstmt;
    //debuglog("...ok(%X)", (int)pstmt);


	fetch_fase=1;
	fetch_cols=0;
	memset(fetch_data,0,sizeof(fetch_data));
	memset(fetch_data_sjis,0,sizeof(fetch_data_sjis));
	fetch_func[0]=NULL;

	return SQL_SUCCESS;
}

SQLRETURN SQL_API SQLFreeStmt(
    SQLHSTMT           hstmt,
    SQLUSMALLINT       fOption)
{
	debuglog("SQLFreeStmt(%d)", (int)fOption);

	fetch_fase=0;
	fetch_cols=0;
	memset(fetch_data,0,sizeof(fetch_data));
	memset(fetch_data_sjis,0,sizeof(fetch_data_sjis));
	fetch_func[0]=NULL;
	return SQL_SUCCESS;
}


SQLRETURN SQL_API SQLExecDirect(
    SQLHSTMT           hstmt,
    SQLCHAR FAR       *szSqlStr,
    SQLINTEGER         cbSqlStr)
{
    IB_STMT *pstmt = (IB_STMT *)hstmt;
    IB_DBC  *pdbc;
	int ret;
	char szSqlStr2[1024];

    debuglog("SQLExeDirect()");

    if( pstmt == NULL ) return SQL_ERROR;

	/* ダブルクォーテーション削除*/
	strcpy(fetch_query,strCut((char*)szSqlStr,'"'));

	ret=DBExecute(sockfd,(char*)fetch_query);
    debuglog("SQLExeDirect(%s,%d)=%d",fetch_query,cbSqlStr,ret);
	if ( ret != 0 ){ return SQL_ERROR; }
    return SQL_SUCCESS;

}

SQLRETURN SQL_API SQLPrepare(
    SQLHSTMT           hstmt,
    SQLCHAR FAR       *szSqlStr,
    SQLINTEGER         cbSqlStr)
{
	int ret;

    debuglog("SQLPrepare(%s,%d)",szSqlStr,cbSqlStr);
	sprintf(fetch_query,"explain %s",szSqlStr);
	ret=DBExecute(sockfd,(char*)fetch_query);
    debuglog("DBExecute(%s)=%d",fetch_query,ret);
	if ( ret != 0 ){ return SQL_ERROR; }
	return SQL_SUCCESS;
}


SQLRETURN SQL_API SQLExecute(
    SQLHSTMT           hstmt)
{
	int ret;
    IB_STMT *pstmt = (IB_STMT *)hstmt;
    IB_DBC  *pdbc;

    debuglog("SQLExecute()");
    if( pstmt == NULL ) return SQL_ERROR;
    return SQL_SUCCESS;
}



SQLRETURN SQL_API SQLFetch(
    SQLHSTMT           hstmt)
{
    IB_STMT *pstmt = (IB_STMT *)hstmt;
    IB_DBC  *pdbc;
	int ret;
	int wlen;
	int mlen;

	fetch_data[0]=NULL;
	fetch_data_sjis[0]=NULL;

	//型のタイプを返す
	if ( strcmp(fetch_func,"SQLGetTypeInfo") == 0 ){
		return SQL_SUCCESS;
	}

    if( pstmt == NULL || fetch_fase == 0 ){
		debuglog("SQLFetch()=error");
		return SQL_ERROR;
	}
	if ( fetch_fase == 2 ){
		debuglog("SQLFetch()=no data");
		return SQL_NO_DATA_FOUND; 
	}

	//データ取得
	//ret=DBFetchOne(sockfd,fetch_data);
	ret=DBFetchN(sockfd,fetch_data);
	if ( ret == 1 ){

		//UTF8->UTF16
		wlen = MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)fetch_data, -1, NULL, 0);
		MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)fetch_data, -1, (LPWSTR)fetch_data_utf16, wlen);

		//UTF16->shiftJIS
		mlen = WideCharToMultiByte(CP_ACP,0,(LPCWSTR)fetch_data_utf16,-1,NULL,0," ",NULL);
		WideCharToMultiByte(CP_ACP,0,(LPCWSTR)fetch_data_utf16,-1,(LPSTR)fetch_data_sjis,mlen," ",NULL);

		if ( debug_level > 10 ){
		    debuglog("SQLFetch()=[%s]",fetch_data);
		}

		return SQL_SUCCESS;
	}
	debuglog("SQLFetch()=no data");
	return SQL_NO_DATA_FOUND;
}


SQLRETURN SQL_API SQLGetData(
    SQLHSTMT           hstmt,
    SQLUSMALLINT       icol,
    SQLSMALLINT        fCType,
    SQLPOINTER         rgbValue,
    SQLINTEGER         cbValueMax,
    SQLINTEGER FAR    *pcbValue)
{
    IB_STMT *pstmt = (IB_STMT *)hstmt;
	XSQLDA   *var;
    IB_XCHG  xchg;

	static XSQLDA in_var;
	static char in_data[1024];
	static int in_len;
	char wk[1024];
	char *p;

	if ( debug_level > 10 ){
	    debuglog("SQLGetData(%d,%d,%d)", (int)icol, (int)fCType, (int)cbValueMax);
	}

    if( pstmt == NULL ) return SQL_ERROR;
	if ( fetch_fase == 0 ){ return SQL_ERROR; }
	if ( fetch_fase == 2 ){ return SQL_NO_DATA_FOUND; }

	if ( strcmp(fetch_func,"SQLTables") == 0 ){
		if ( icol == 2 ){
			//strcpy((char*)rgbValue, "default");
			strcpy((char*)rgbValue, "");
		}else if ( icol == 3 ){
			strcpy((char*)rgbValue, fetch_data_sjis);
		}else{
			strcpy((char*)rgbValue, fetch_data_sjis);
		}
	}else if ( strcmp(fetch_func,"SQLColumns") == 0 ){
		if ( icol == 2 ){		/* スキーマ名*/
			//strcpy((char*)rgbValue, "default");
			strcpy((char*)rgbValue, "");
		}else if ( icol == 3 ){		/* テーブル名 */
			strcpy((char*)rgbValue, fetch_table);
		}else if ( icol == 4 ){		/* カラム名 */
			strcpy((char*)rgbValue, strSepValue(fetch_data_sjis,'\t',0));
		}else if ( icol == 5 ){		/* DATA TYPE */
			strcpy(wk, strSepValue(fetch_data_sjis,'\t',1) );
			if ( strcmp(wk,"int") == 0 ){
				sprintf((char*)rgbValue,"%02d",SQL_INTEGER);
			} else if ( strcmp(wk,"string") == 0 ){
				sprintf((char*)rgbValue,"%02d",SQL_CHAR);
			}else{
				strcpy((char*)rgbValue,"");
			}
		}else if ( icol == 6 ){		/* TYPE NAME */
			strcpy((char*)rgbValue, strSepValue(fetch_data_sjis,'\t',1) );
		}else if ( icol == 7 ){		/* PRECISION */
			strcpy((char*)rgbValue, "0010" );
		}else if ( icol == 8 ){		/* LENGTH */
			strcpy((char*)rgbValue, "N");
		}else if ( icol == 9 ){		/* SCALE */
			strcpy((char*)rgbValue, "01");
		}else if ( icol == 10 ){	/* RADIX */
			strcpy((char*)rgbValue, "0");
		}else if ( icol == 11 ){	/* NULLABLE */
			//strcpy((char*)rgbValue, "Y");
			//p=(char*)rgbValue;
			//p[0]=NULL;
			//p[1]='Y';
			strcpy((char*)rgbValue, "");
		}else if ( icol == 12 ){	/* REMARKS */
			strcpy((char*)rgbValue, "");
		}else{
			strcpy((char*)rgbValue, "");
		}
	}else{
		strcpy((char*)rgbValue, strSepValue(fetch_data_sjis,'\t',icol - 1));
	}
	*pcbValue=strlen((char*)rgbValue);


	if ( debug_level > 20 ){
		debuglog("SQLGetData(%d,%d)=[%s]", (int)icol, (int)fCType, rgbValue);
	}

	return SQL_SUCCESS;
}


//SQL結果列数を返す
SQLRETURN SQL_API SQLNumResultCols(
    SQLHSTMT           hstmt,
    SQLSMALLINT FAR   *pccol)
{
    IB_STMT *pstmt = (IB_STMT *)hstmt;

    if( pstmt == NULL ) return SQL_ERROR;
	if ( fetch_fase == 0 ){ return SQL_ERROR; }
	*pccol = fetch_cols;
	debuglog("SQLNumResultCols()=%d",*pccol);

	return SQL_SUCCESS;
}


//CatalogName, SchemaName, and TableName
SQLRETURN SQL_API SQLTables(
    SQLHSTMT           hstmt,
    SQLCHAR FAR       *szCatalogName,
    SQLSMALLINT        cbCatalogName,
    SQLCHAR FAR       *szSchemaName,
    SQLSMALLINT        cbSchemaName,
    SQLCHAR FAR       *szTableName,
    SQLSMALLINT        cbTableName,
    SQLCHAR FAR       *szTableType,
    SQLSMALLINT        cbTableType)
{
    IB_STMT *pstmt = (IB_STMT *)hstmt;
    SQLRETURN retcode=SQL_SUCCESS;
    static char sql[]="show tables";

    debuglog("SQLTables()");
    if( pstmt == NULL ) return SQL_ERROR;
    retcode = SQLExecDirect( hstmt, (SQLCHAR FAR *)sql, SQL_NTS );
	strcpy(fetch_func,"SQLTables");
	fetch_cols=4;
    return retcode;
}


//プライマリキーの列
SQLRETURN SQL_API SQLSpecialColumns(
    SQLHSTMT           hstmt,
    SQLUSMALLINT       fColType,
    SQLCHAR FAR       *szCatalogName,
    SQLSMALLINT        cbCatalogName,
    SQLCHAR FAR       *szSchemaName,
    SQLSMALLINT        cbSchemaName,
    SQLCHAR FAR       *szTableName,
    SQLSMALLINT        cbTableName,
    SQLUSMALLINT       fScope,
    SQLUSMALLINT       fNullable)
{
    IB_STMT *pstmt = (IB_STMT *)hstmt;
    SQLRETURN retcode=SQL_SUCCESS;

	debuglog("SQLSpecialColumns() %s.%s.%s",szCatalogName,szSchemaName,szTableName);
    if( pstmt == NULL ) return SQL_ERROR;
	strcpy(fetch_func,"SQLSpecialColumns");
	fetch_cols=4;
	fetch_fase=2;
	return SQL_SUCCESS;
}

//型の定義
SQLRETURN SQL_API SQLGetTypeInfo(
    SQLHSTMT           hstmt,
    SQLSMALLINT        fSqlType)
{

	debuglog("SQLGetTypeInfo(%d)",fSqlType);
	strcpy(fetch_func,"SQLGetTypeInfo");
	fetch_cols=15;
	fetch_fase=1;
	return SQL_SUCCESS;


}

//カラム情報
SQLRETURN SQL_API SQLColumns(
    SQLHSTMT           hstmt,
    SQLCHAR FAR       *szCatalogName,
    SQLSMALLINT        cbCatalogName,
    SQLCHAR FAR       *szSchemaName,
    SQLSMALLINT        cbSchemaName,
    SQLCHAR FAR       *szTableName,
    SQLSMALLINT        cbTableName,
    SQLCHAR FAR       *szColumnName,
    SQLSMALLINT        cbColumnName)
{
    IB_STMT *pstmt = (IB_STMT *)hstmt;
    SQLRETURN retcode=SQL_SUCCESS;
    static char sql[1024];

	debuglog("SQLColumns(%s.%s.%s.%s)",szCatalogName,szSchemaName,szTableName,szColumnName);
    if( pstmt == NULL ) return SQL_ERROR;
	sprintf(sql,"desc %s",szTableName);
    retcode = SQLExecDirect( hstmt, (SQLCHAR FAR *)sql, SQL_NTS );
	strcpy(fetch_func,"SQLColumns");
	strcpy(fetch_table,(char*)szTableName);
	fetch_cols=11;
    return retcode;
}

//
SQLRETURN SQL_API SQLStatistics(
    SQLHSTMT           hstmt,
    SQLCHAR FAR       *szCatalogName,
    SQLSMALLINT        cbCatalogName,
    SQLCHAR FAR       *szSchemaName,
    SQLSMALLINT        cbSchemaName,
    SQLCHAR FAR       *szTableName,
    SQLSMALLINT        cbTableName,
    SQLUSMALLINT       fUnique,
    SQLUSMALLINT       fAccuracy)
{
	debuglog("SQLStatistics(%s.%s.%s)",szCatalogName,szSchemaName,szTableName);
	strcpy(fetch_func,"SQLStatistics");
	fetch_cols=13;
	fetch_fase=1;

	return SQL_SUCCESS;
}

