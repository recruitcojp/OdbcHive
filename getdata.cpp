#include "hiveodbc.h"

static char fetch_fase=0;
static int  fetch_cols;
static char fetch_table[1024];
static char fetch_data[1024];
static char fetch_data_sjis[1024];
static char fetch_data_utf16[1024];
static char fetch_func[1024];
static char fetch_query[1024];


SQLRETURN SQL_API SQLAllocStmt(
    SQLHDBC            hdbc,
    SQLHSTMT FAR      *phstmt)
{
	if ( func_init("SQLAllocStmt") != 0 ){ return SQL_ERROR; }

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
	if ( func_init("SQLFreeStmt") != 0 ){ return SQL_ERROR; }

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
	int ret;
	char szSqlStr2[1024];

	if ( func_init("SQLExeDirect") != 0 ){ return SQL_ERROR; }

	/* ダブルクォーテーション削除*/
	strcpy(fetch_query,utl_strCut((char*)szSqlStr,'"'));

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

	if ( func_init("SQLPrepare") != 0 ){ return SQL_ERROR; }

	sprintf(fetch_query,"explain %s",szSqlStr);
	ret=DBExecute(sockfd,(char*)fetch_query);
    debuglog("DBExecute(%s)=%d",fetch_query,ret);
	if ( ret != 0 ){ return SQL_ERROR; }
	return SQL_SUCCESS;
}


SQLRETURN SQL_API SQLExecute(
    SQLHSTMT           hstmt)
{
	if ( func_init("SQLExecute") != 0 ){ return SQL_ERROR; }
    return SQL_SUCCESS;
}



SQLRETURN SQL_API SQLFetch(
    SQLHSTMT           hstmt)
{
	int ret;
	int wlen;
	int mlen;

	if ( func_init("SQLFetch") != 0 ){ return SQL_ERROR; }

	fetch_data[0]=NULL;
	fetch_data_sjis[0]=NULL;

	//型のタイプを返す
	if ( strcmp(fetch_func,"SQLGetTypeInfo") == 0 ){
		return SQL_SUCCESS;
	}

    if( fetch_fase == 0 ){
		debuglog("SQLFetch()=error");
		return SQL_ERROR;
	}
	if ( fetch_fase == 2 ){
		debuglog("SQLFetch()=no data");
		return SQL_NO_DATA_FOUND; 
	}

	//データ取得
	ret=DBFetchN(sockfd,fetch_data);
	if ( ret == 1 ){

		//UTF8->UTF16
		wlen = MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)fetch_data, -1, NULL, 0);
		MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)fetch_data, -1, (LPWSTR)fetch_data_utf16, wlen);

		//UTF16->shiftJIS
		mlen = WideCharToMultiByte(CP_ACP,0,(LPCWSTR)fetch_data_utf16,-1,NULL,0," ",NULL);
		WideCharToMultiByte(CP_ACP,0,(LPCWSTR)fetch_data_utf16,-1,(LPSTR)fetch_data_sjis,mlen," ",NULL);

		if ( reginfo.debug_level > 10 ){
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
	static int in_len;
	char wk[1024];
	char *p;

	if ( func_init("SQLGetData") != 0 ){ return SQL_ERROR; }

	if ( reginfo.debug_level > 10 ){
	    debuglog("SQLGetData(%d,%d,%d)", (int)icol, (int)fCType, (int)cbValueMax);
	}

	if ( fetch_fase == 0 ){ return SQL_ERROR; }
	if ( fetch_fase == 2 ){ return SQL_NO_DATA_FOUND; }

	if ( strcmp(fetch_func,"SQLTables") == 0 ){
		if ( icol == 2 ){
			strcpy((char*)rgbValue, "");
		}else if ( icol == 3 ){
			strcpy((char*)rgbValue, fetch_data_sjis);
		}else{
			strcpy((char*)rgbValue, fetch_data_sjis);
		}
	}else if ( strcmp(fetch_func,"SQLColumns") == 0 ){
		if ( icol == 2 ){		/* スキーマ名*/
			strcpy((char*)rgbValue, "");
		}else if ( icol == 3 ){		/* テーブル名 */
			strcpy((char*)rgbValue, fetch_table);
		}else if ( icol == 4 ){		/* カラム名 */
			strcpy((char*)rgbValue, utl_strSepValue(fetch_data_sjis,'\t',0));
		}else if ( icol == 5 ){		/* DATA TYPE */
			strcpy(wk, utl_strSepValue(fetch_data_sjis,'\t',1) );
		if ( strcmp(wk,"int") == 0 ){
				sprintf((char*)rgbValue,"%02d",SQL_INTEGER);
			} else if ( strcmp(wk,"tinyint") == 0 ){
				sprintf((char*)rgbValue,"%02d",SQL_TINYINT);
			} else if ( strcmp(wk,"smallint") == 0 ){
				sprintf((char*)rgbValue,"%02d",SQL_SMALLINT);
			} else if ( strcmp(wk,"bigint") == 0 ){
				sprintf((char*)rgbValue,"%02d",SQL_BIGINT);
			} else if ( strcmp(wk,"boolean") == 0 ){
				sprintf((char*)rgbValue,"%02d",SQL_BIT);
			} else if ( strcmp(wk,"float") == 0 ){
				sprintf((char*)rgbValue,"%02d",SQL_FLOAT);
			} else if ( strcmp(wk,"double") == 0 ){
				sprintf((char*)rgbValue,"%02d",SQL_DOUBLE);
			//  HIVE_DATE_TYPE, HIVE_DATETIME_TYPE, HIVE_TIMESTAMP_TYPE 
			} else if ( strcmp(wk,"date") == 0 ){
				sprintf((char*)rgbValue,"%02d",SQL_TYPE_DATE);
			} else if ( strcmp(wk,"datetime") == 0 ){
				sprintf((char*)rgbValue,"%02d",SQL_TYPE_TIME);
			} else if ( strcmp(wk,"timestamp") == 0 ){
				sprintf((char*)rgbValue,"%02d",SQL_TYPE_TIMESTAMP);
			} else if ( strcmp(wk,"string") == 0 ){
				sprintf((char*)rgbValue,"%02d",SQL_CHAR);
			}else{
				strcpy((char*)rgbValue,"");
			}
		}else if ( icol == 6 ){		/* TYPE NAME */
			strcpy((char*)rgbValue, utl_strSepValue(fetch_data_sjis,'\t',1) );
		}else if ( icol == 7 ){		/* PRECISION */
			strcpy((char*)rgbValue, "0010" );
		}else if ( icol == 8 ){		/* LENGTH */
			strcpy((char*)rgbValue, "N");
		}else if ( icol == 9 ){		/* SCALE */
			strcpy((char*)rgbValue, "01");
		}else if ( icol == 10 ){	/* RADIX */
			strcpy((char*)rgbValue, "0");
		}else if ( icol == 11 ){	/* NULLABLE */
			strcpy((char*)rgbValue, "");
		}else if ( icol == 12 ){	/* REMARKS */
			strcpy((char*)rgbValue, "");
		}else{
			strcpy((char*)rgbValue, "");
		}
	}else{
		strcpy((char*)rgbValue, utl_strSepValue(fetch_data_sjis,'\t',icol - 1));
	}
	*pcbValue=strlen((char*)rgbValue);

	//if ( reginfo.debug_level > 20 ){
	//	debuglog("SQLGetData(%d,%d)=[%s]", (int)icol, (int)fCType, rgbValue);
	//}

	return SQL_SUCCESS;
}


//SQL結果列数を返す
SQLRETURN SQL_API SQLNumResultCols(
    SQLHSTMT           hstmt,
    SQLSMALLINT FAR   *pccol)
{
	if ( func_init("SQLNumResultCols") != 0 ){ return SQL_ERROR; }

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
    SQLRETURN retcode=SQL_SUCCESS;
    static char sql[]="show tables";

	if ( func_init("SQLTables") != 0 ){ return SQL_ERROR; }

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
    SQLRETURN retcode=SQL_SUCCESS;

	if ( func_init("SQLSpecialColumns") != 0 ){ return SQL_ERROR; }

	//debuglog("SQLSpecialColumns() %s.%s.%s",szCatalogName,szSchemaName,szTableName);
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
	if ( func_init("SQLGetTypeInfo") != 0 ){ return SQL_ERROR; }

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
    SQLRETURN retcode=SQL_SUCCESS;
    static char sql[1024];

	if ( func_init("SQLColumns") != 0 ){ return SQL_ERROR; }

	//debuglog("SQLColumns(%s.%s.%s.%s)",szCatalogName,szSchemaName,szTableName,szColumnName);
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
	if ( func_init("SQLStatistics") != 0 ){ return SQL_ERROR; }

	//debuglog("SQLStatistics(%s.%s.%s)",szCatalogName,szSchemaName,szTableName);
	strcpy(fetch_func,"SQLStatistics");
	fetch_cols=13;
	fetch_fase=1;

	return SQL_SUCCESS;
}

