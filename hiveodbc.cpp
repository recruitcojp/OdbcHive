#include "hiveodbc.h"

int sockfd=0;
int errflg=0;
REGISTER_INFO reginfo; 

SQLRETURN SQL_API SQLBrowseConnect(
    SQLHDBC            hdbc,
    SQLCHAR FAR       *szConnStrIn,
    SQLSMALLINT        cbConnStrIn,
    SQLCHAR FAR       *szConnStrOut,
    SQLSMALLINT        cbConnStrOutMax,
    SQLSMALLINT FAR   *pcbConnStrOut)
{
	if ( func_init("SQLBrowseConnect") != 0 ){ return SQL_ERROR; }
	return SQL_SUCCESS;
}

SQLRETURN SQL_API SQLColumnPrivileges(
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
	if ( func_init("SQLColumnPrivileges") != 0 ){ return SQL_ERROR; }
	return SQL_SUCCESS;
}

SQLRETURN SQL_API SQLDescribeParam(
    SQLHSTMT           hstmt,
    SQLUSMALLINT       ipar,
    SQLSMALLINT FAR   *pfSqlType,
    SQLUINTEGER FAR   *pcbParamDef,
    SQLSMALLINT FAR   *pibScale,
    SQLSMALLINT FAR   *pfNullable)
{
	if ( func_init("SQLDescribeParam") != 0 ){ return SQL_ERROR; }
	return SQL_SUCCESS;
}

SQLRETURN SQL_API SQLExtendedFetch(
    SQLHSTMT           hstmt,
    SQLUSMALLINT       fFetchType,
    SQLINTEGER         irow,
    SQLUINTEGER FAR   *pcrow,
    SQLUSMALLINT FAR  *rgfRowStatus)
{
	if ( func_init("SQLExtendedFetch") != 0 ){ return SQL_ERROR; }
	return SQL_SUCCESS;
}

SQLRETURN SQL_API SQLForeignKeys(
    SQLHSTMT           hstmt,
    SQLCHAR FAR       *szPkCatalogName,
    SQLSMALLINT        cbPkCatalogName,
    SQLCHAR FAR       *szPkSchemaName,
    SQLSMALLINT        cbPkSchemaName,
    SQLCHAR FAR       *szPkTableName,
    SQLSMALLINT        cbPkTableName,
    SQLCHAR FAR       *szFkCatalogName,
    SQLSMALLINT        cbFkCatalogName,
    SQLCHAR FAR       *szFkSchemaName,
    SQLSMALLINT        cbFkSchemaName,
    SQLCHAR FAR       *szFkTableName,
    SQLSMALLINT        cbFkTableName)
{
	if ( func_init("SQLForeignKeys") != 0 ){ return SQL_ERROR; }
	return SQL_SUCCESS;
}

SQLRETURN SQL_API SQLMoreResults(
    SQLHSTMT           hstmt)
{
	if ( func_init("SQLMoreResults") != 0 ){ return SQL_ERROR; }
	return SQL_SUCCESS;
}

SQLRETURN SQL_API SQLNativeSql(
    SQLHDBC            hdbc,
    SQLCHAR FAR       *szSqlStrIn,
    SQLINTEGER         cbSqlStrIn,
    SQLCHAR FAR       *szSqlStr,
    SQLINTEGER         cbSqlStrMax,
    SQLINTEGER FAR    *pcbSqlStr)
{
	if ( func_init("SQLNativeSql") != 0 ){ return SQL_ERROR; }
	return SQL_SUCCESS;
}

SQLRETURN SQL_API SQLNumParams(
    SQLHSTMT           hstmt,
    SQLSMALLINT FAR   *pcpar)
{
	if ( func_init("SQLNumParams") != 0 ){ return SQL_ERROR; }
	return SQL_SUCCESS;
}

SQLRETURN SQL_API SQLParamOptions(
    SQLHSTMT           hstmt,
    SQLUINTEGER        crow,
    SQLUINTEGER FAR   *pirow)
{
	if ( func_init("SQLParamOptions") != 0 ){ return SQL_ERROR; }
	return SQL_SUCCESS;
}

SQLRETURN SQL_API SQLPrimaryKeys(
    SQLHSTMT           hstmt,
    SQLCHAR FAR       *szCatalogName,
    SQLSMALLINT        cbCatalogName,
    SQLCHAR FAR       *szSchemaName,
    SQLSMALLINT        cbSchemaName,
    SQLCHAR FAR       *szTableName,
    SQLSMALLINT        cbTableName)
{
	if ( func_init("SQLPrimaryKeys") != 0 ){ return SQL_ERROR; }
	return SQL_SUCCESS;
}

SQLRETURN SQL_API SQLProcedureColumns(
    SQLHSTMT           hstmt,
    SQLCHAR FAR       *szCatalogName,
    SQLSMALLINT        cbCatalogName,
    SQLCHAR FAR       *szSchemaName,
    SQLSMALLINT        cbSchemaName,
    SQLCHAR FAR       *szProcName,
    SQLSMALLINT        cbProcName,
    SQLCHAR FAR       *szColumnName,
    SQLSMALLINT        cbColumnName)
{
	if ( func_init("SQLProcedureColumns") != 0 ){ return SQL_ERROR; }
	return SQL_SUCCESS;
}

SQLRETURN SQL_API SQLProcedures(
    SQLHSTMT           hstmt,
    SQLCHAR FAR       *szCatalogName,
    SQLSMALLINT        cbCatalogName,
    SQLCHAR FAR       *szSchemaName,
    SQLSMALLINT        cbSchemaName,
    SQLCHAR FAR       *szProcName,
    SQLSMALLINT        cbProcName)
{
	if ( func_init("SQLProcedures") != 0 ){ return SQL_ERROR; }
	return SQL_SUCCESS;
}

SQLRETURN SQL_API SQLSetPos(
    SQLHSTMT           hstmt,
    SQLUSMALLINT       irow,
    SQLUSMALLINT       fOption,
    SQLUSMALLINT       fLock)
{
	if ( func_init("SQLSetPos") != 0 ){ return SQL_ERROR; }
	return SQL_SUCCESS;
}

SQLRETURN SQL_API SQLTablePrivileges(
    SQLHSTMT           hstmt,
    SQLCHAR FAR       *szCatalogName,
    SQLSMALLINT        cbCatalogName,
    SQLCHAR FAR       *szSchemaName,
    SQLSMALLINT        cbSchemaName,
    SQLCHAR FAR       *szTableName,
    SQLSMALLINT        cbTableName)
{
	if ( func_init("SQLTablePrivileges") != 0 ){ return SQL_ERROR; }
	return SQL_SUCCESS;
}

SQLRETURN SQL_API SQLDrivers(
    SQLHENV            henv,
    SQLUSMALLINT       fDirection,
    SQLCHAR FAR       *szDriverDesc,
    SQLSMALLINT        cbDriverDescMax,
    SQLSMALLINT FAR   *pcbDriverDesc,
    SQLCHAR FAR       *szDriverAttributes,
    SQLSMALLINT        cbDrvrAttrMax,
    SQLSMALLINT FAR   *pcbDrvrAttr)
{
	if ( func_init("SQLDrivers") != 0 ){ return SQL_ERROR; }
	return SQL_SUCCESS;
}

SQLRETURN SQL_API SQLBindParameter(
    SQLHSTMT           hstmt,
    SQLUSMALLINT       ipar,
    SQLSMALLINT        fParamType,
    SQLSMALLINT        fCType,
    SQLSMALLINT        fSqlType,
    SQLUINTEGER        cbColDef,
    SQLSMALLINT        ibScale,
    SQLPOINTER         rgbValue,
    SQLINTEGER         cbValueMax,
    SQLINTEGER FAR    *pcbValue)
{
	if ( func_init("SQLBindParameter") != 0 ){ return SQL_ERROR; }
	return SQL_SUCCESS;
}

SQLRETURN SQL_API SQLAllocConnect(
    SQLHENV            henv,
    SQLHDBC FAR       *phdbc)
{
    IB_ENV *penv = (IB_ENV *)henv;
    IB_DBC *pdbc;

	if ( func_init("SQLAllocConnect") != 0 ){ return SQL_ERROR; }

    if( penv == NULL ) return SQL_ERROR;
    if( penv->dbc == NULL ) {
        pdbc = penv->dbc = (IB_DBC *)malloc( sizeof( IB_DBC ) );
    } else {
        pdbc = penv->dbc;
        while( pdbc->next_dbc ) pdbc = (IB_DBC *)pdbc->next_dbc;
		pdbc->next_dbc = malloc( sizeof( IB_DBC ) );
		pdbc = (IB_DBC *)pdbc->next_dbc;
    }
    memset( pdbc, 0, sizeof( IB_DBC ) );
    pdbc->pare_env = penv;

    // ODBC の仕様には反しますが、デフォルトを concurrenncy にします！
    // pdbc->isolation_level = SQL_TXN_READ_COMMITTED;
    pdbc->isolation_level   = SQL_TXN_REPEATABLE_READ;
    pdbc->current_isolation = pdbc->isolation_level;
    *phdbc = pdbc;

	return SQL_SUCCESS;
}

SQLRETURN SQL_API SQLAllocEnv(
    SQLHENV FAR       *phenv)
{
	if ( func_init("SQLAllocEnv") != 0 ){ return SQL_ERROR; }

    if( phenv == NULL ) return SQL_ERROR;
    *phenv = (SQLHENV)malloc( sizeof( IB_ENV ) );
    if( *phenv == NULL ) return SQL_ERROR;
    memset( *phenv, 0, sizeof( IB_ENV ) );
	return SQL_SUCCESS;
}


SQLRETURN SQL_API SQLBindCol(
    SQLHSTMT           hstmt,
    SQLUSMALLINT       icol,
    SQLSMALLINT        fCType,
    SQLPOINTER         rgbValue,
    SQLINTEGER         cbValueMax,
    SQLINTEGER FAR    *pcbValue)
{
	if ( func_init("SQLBindCol") != 0 ){ return SQL_ERROR; }
	return SQL_SUCCESS;
}

SQLRETURN SQL_API SQLCancel(
    SQLHSTMT           hstmt)
{
	if ( func_init("SQLSqlCancel") != 0 ){ return SQL_ERROR; }
	return SQL_SUCCESS;
}

SQLRETURN SQL_API SQLColAttributes(
    SQLHSTMT           hstmt,
    SQLUSMALLINT       icol,
    SQLUSMALLINT       fDescType,
    SQLPOINTER         rgbDesc,
    SQLSMALLINT        cbDescMax,
    SQLSMALLINT FAR   *pcbDesc,
    SQLINTEGER FAR    *pfDesc)
{
	if ( func_init("SQLColAttributes") != 0 ){ return SQL_ERROR; }
	return SQL_SUCCESS;
}

SQLRETURN SQL_API SQLConnect(
    SQLHDBC            hdbc,
    SQLCHAR FAR       *szDSN,
    SQLSMALLINT        cbDSN,
    SQLCHAR FAR       *szUID,
    SQLSMALLINT        cbUID,
    SQLCHAR FAR       *szAuthStr,
    SQLSMALLINT        cbAuthStr)
{
	if ( func_init("SQLConnect") != 0 ){ return SQL_ERROR; }

	//コネクト
	if ( DBConnect(reginfo.host, reginfo.port) != 0){
		debuglog("SQLConnect() DBconnect error");
		return SQL_ERROR;
	}
	debuglog("SQLConnect() OK");

	return SQL_SUCCESS;
}

SQLRETURN SQL_API SQLDescribeCol(
    SQLHSTMT           hstmt,
    SQLUSMALLINT       icol,
    SQLCHAR FAR       *szColName,
    SQLSMALLINT        cbColNameMax,
    SQLSMALLINT FAR   *pcbColName,
    SQLSMALLINT FAR   *pfSqlType,
    SQLUINTEGER FAR   *pcbColDef,
    SQLSMALLINT FAR   *pibScale,
    SQLSMALLINT FAR   *pfNullable)
{
	if ( func_init("SQLDescribeCol") != 0 ){ return SQL_ERROR; }
	return SQL_SUCCESS;
}

SQLRETURN SQL_API SQLDisconnect(
    SQLHDBC            hdbc)
{
	if ( func_init("SQLDisconnect") != 0 ){ return SQL_ERROR; }
	return SQL_SUCCESS;
}

SQLRETURN SQL_API SQLError(
    SQLHENV            henv,
    SQLHDBC            hdbc,
    SQLHSTMT           hstmt,
    SQLCHAR FAR       *szSqlState,
    SQLINTEGER FAR    *pfNativeError,
    SQLCHAR FAR       *szErrorMsg,
    SQLSMALLINT        cbErrorMsgMax,
    SQLSMALLINT FAR   *pcbErrorMsg)
{
    IB_ENV  * penv  = (IB_ENV  *)henv;
    IB_DBC  * pdbc  = (IB_DBC  *)hdbc;
    IB_STMT * pstmt = (IB_STMT *)hstmt;
    IB_ERRINFO *perr = NULL;
    int msg_len = 0;

	if ( func_init("SQLError") != 0 ){ return SQL_ERROR; }

    if( szErrorMsg )    *szErrorMsg = 0;  // NULL String
    if( pfNativeError ) *pfNativeError = 0;
    if( szSqlState )    *szSqlState = 0;
    if( pcbErrorMsg )   *pcbErrorMsg = 0;

    if( pstmt ) {
        perr = &pstmt->err;
    } else
    if( pdbc ) {
        perr = &pdbc->err;
    } else
    if( henv ) {
        perr = &penv->err;
    } else  {
	    debuglog("SQLError()=>ERR");
        return SQL_ERROR;
    }

   // サーバー側のエラーならメッセージを生成
    if( !perr->is_server ) {
        if( *perr->msg == 0 ) {
		    debuglog("SQLError()=>ERR");
            return SQL_ERROR;
        }
    }

    msg_len = strlen( perr->msg );
    if( pfNativeError ) {
        *pfNativeError = perr->native;
    }

    // ANSI SQLSTATE に変換が必要、現在は何もしない
    if( szSqlState ) {
        strcpy( (char*)szSqlState, "9999" );
    }

    if( cbErrorMsgMax > 0 ) {
        msg_len = MIN( msg_len, cbErrorMsgMax - 1 );
        strncpy( (char*)szErrorMsg, perr->msg, msg_len );
        szErrorMsg[ msg_len ] = 0;
    }

    if( pcbErrorMsg ) *pcbErrorMsg = msg_len;
    if( perr ) {
        *perr->msg = 0;
        perr->native = 0;
    }
    debuglog("SQLError()=>OK");
    return SQL_SUCCESS;


}

SQLRETURN SQL_API SQLFreeConnect(
    SQLHDBC            hdbc)
{
	if ( func_init("SQLFreeConnect") != 0 ){ return SQL_ERROR; }
	return SQL_SUCCESS;
}

SQLRETURN SQL_API SQLFreeEnv(
    SQLHENV            henv)
{
	if ( func_init("SQLFreeEnv") != 0 ){ return SQL_ERROR; }
	return SQL_SUCCESS;
}

SQLRETURN SQL_API SQLGetCursorName(
    SQLHSTMT           hstmt,
    SQLCHAR FAR       *szCursor,
    SQLSMALLINT        cbCursorMax,
    SQLSMALLINT FAR   *pcbCursor)
{
	if ( func_init("SQLGetCusorName") != 0 ){ return SQL_ERROR; }
	return SQL_SUCCESS;
}


SQLRETURN SQL_API SQLRowCount(
    SQLHSTMT           hstmt,
    SQLINTEGER FAR    *pcrow)
{
	if ( func_init("SQLRowCount") != 0 ){ return SQL_ERROR; }
	return SQL_SUCCESS;
}

SQLRETURN SQL_API SQLSetCursorName(
    SQLHSTMT           hstmt,
    SQLCHAR FAR       *szCursor,
    SQLSMALLINT        cbCursor)
{
	if ( func_init("SQLSetCursorName") != 0 ){ return SQL_ERROR; }
	return SQL_SUCCESS;
}

SQLRETURN SQL_API SQLTransact(
    SQLHENV            henv,
    SQLHDBC            hdbc,
    SQLUSMALLINT       fType)
{
	if ( func_init("SQLTransact") != 0 ){ return SQL_ERROR; }
	return SQL_SUCCESS;
}


SQLRETURN SQL_API SQLSetParam(
    SQLHSTMT           hstmt,
    SQLUSMALLINT       ipar,
    SQLSMALLINT        fCType,
    SQLSMALLINT        fSqlType,
    SQLUINTEGER        cbParamDef,
    SQLSMALLINT        ibScale,
    SQLPOINTER         rgbValue,
    SQLINTEGER FAR     *pcbValue)
{
	if ( func_init("SQLSetParam") != 0 ){ return SQL_ERROR; }
	return SQL_SUCCESS;
}

SQLRETURN SQL_API SQLGetConnectOption(
    SQLHDBC            hdbc,
    SQLUSMALLINT       fOption,
    SQLPOINTER         pvParam)
{
	IB_DBC *pdbc = (IB_DBC *)hdbc;

	if ( func_init("SQLGetConnectOption") != 0 ){ return SQL_ERROR; }

	if( pdbc == NULL || pvParam == NULL ) return SQL_ERROR;

	*(char *)pvParam = 0; // とりあえず文字分クリア

	switch( fOption ) {
	  case SQL_AUTOCOMMIT:
		if( pdbc->is_noautocommit ) {
			*(long *)pvParam = SQL_AUTOCOMMIT_OFF;
			debuglog( "...autocommit off" );
		} else {
			*(long *)pvParam = SQL_AUTOCOMMIT_ON;
			debuglog( "...autocommit on" );
		}
		return SQL_SUCCESS;

	  case SQL_ACCESS_MODE:
		*(long *)pvParam = SQL_MODE_READ_WRITE; 
		return SQL_SUCCESS;

	  case SQL_CURRENT_QUALIFIER: // = SQL_ATTR_CURRENT_CATALOG
		*(char *)pvParam = 0; // ""
		return SQL_SUCCESS;

	  case SQL_LOGIN_TIMEOUT:
		*(long *)pvParam = 0; 
		return SQL_SUCCESS;

	  // これは、ドライバマネジャの仕事で、呼ばれる事はありません
	  case SQL_ODBC_CURSORS:
		*(long *)pvParam = pdbc->odbc_cursors;
		return SQL_SUCCESS;

	  case SQL_PACKET_SIZE:
		*(long *)pvParam = 0; 
		return SQL_SUCCESS;

	  case SQL_QUIET_MODE:
		*(long *)pvParam = 0; 
		return SQL_SUCCESS;

	  case SQL_TRANSLATE_DLL:
		*(char *)pvParam = 0; // ""
		return SQL_SUCCESS;

	  case SQL_TRANSLATE_OPTION:
		*(long *)pvParam = 0;
		return SQL_SUCCESS;

	  case SQL_TXN_ISOLATION:
		*(long *)pvParam = pdbc->isolation_level;
		return SQL_SUCCESS;
	}

	return SQL_SUCCESS;
}

SQLRETURN SQL_API SQLGetStmtOption(
    SQLHSTMT           hstmt,
    SQLUSMALLINT       fOption,
    SQLPOINTER         pvParam)
{
	if ( func_init("SQLGetStmtOption") != 0 ){ return SQL_ERROR; }
	return SQL_SUCCESS;
}

SQLRETURN SQL_API SQLParamData(
    SQLHSTMT           hstmt,
    SQLPOINTER FAR    *prgbValue)
{
	if ( func_init("SQLParamData") != 0 ){ return SQL_ERROR; }
	return SQL_SUCCESS;
}

SQLRETURN SQL_API SQLPutData(
    SQLHSTMT           hstmt,
    SQLPOINTER         rgbValue,
    SQLINTEGER         cbValue)
{
	if ( func_init("SQLPutData") != 0 ){ return SQL_ERROR; }
	return SQL_SUCCESS;
}

SQLRETURN SQL_API SQLSetConnectOption(
    SQLHDBC            hdbc,
    SQLUSMALLINT       fOption,
    SQLUINTEGER        vParam)
{
	if ( func_init("SQLSetConnectOption") != 0 ){ return SQL_ERROR; }
	return SQL_SUCCESS;
}

SQLRETURN SQL_API SQLSetStmtOption(
    SQLHSTMT           hstmt,
    SQLUSMALLINT       fOption,
    SQLUINTEGER        vParam)
{
	if ( func_init("SQLSetStmtOption") != 0 ){ return SQL_ERROR; }
	return SQL_SUCCESS;
}

SQLRETURN SQL_API SQLDataSources(
    SQLHENV            henv,
    SQLUSMALLINT       fDirection,
    SQLCHAR FAR       *szDSN,
    SQLSMALLINT        cbDSNMax,
    SQLSMALLINT FAR   *pcbDSN,
    SQLCHAR FAR       *szDescription,
    SQLSMALLINT        cbDescriptionMax,
    SQLSMALLINT FAR   *pcbDescription)
{
	if ( func_init("SQLDataSources") != 0 ){ return SQL_ERROR; }
	return SQL_SUCCESS;
}

