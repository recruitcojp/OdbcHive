
#include "hiveodbc.h"

int sockfd=0;
int errflg=0;
int debug_level=1;

SQLRETURN SQL_API SQLBrowseConnect(
    SQLHDBC            hdbc,
    SQLCHAR FAR       *szConnStrIn,
    SQLSMALLINT        cbConnStrIn,
    SQLCHAR FAR       *szConnStrOut,
    SQLSMALLINT        cbConnStrOutMax,
    SQLSMALLINT FAR   *pcbConnStrOut)
{
	debuglog("SQLBrowseConnect");
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
	debuglog("SQLColumnPrivileges");
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
	debuglog("SQLDescribeParam");
	return SQL_SUCCESS;
}

SQLRETURN SQL_API SQLExtendedFetch(
    SQLHSTMT           hstmt,
    SQLUSMALLINT       fFetchType,
    SQLINTEGER         irow,
    SQLUINTEGER FAR   *pcrow,
    SQLUSMALLINT FAR  *rgfRowStatus)
{
	debuglog("SQLExtendedFetch");
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
	debuglog("SQLForeignKeys");
	return SQL_SUCCESS;
}

SQLRETURN SQL_API SQLMoreResults(
    SQLHSTMT           hstmt)
{
	debuglog("SQLMoreResults");
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
	debuglog("SQLNativeSql");
	return SQL_SUCCESS;
}

SQLRETURN SQL_API SQLNumParams(
    SQLHSTMT           hstmt,
    SQLSMALLINT FAR   *pcpar)
{
	debuglog("SQLNumParams");
	return SQL_SUCCESS;
}

SQLRETURN SQL_API SQLParamOptions(
    SQLHSTMT           hstmt,
    SQLUINTEGER        crow,
    SQLUINTEGER FAR   *pirow)
{
	debuglog("SQLParamOptions");
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
	debuglog("SQLPrimaryKeys");
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
	debuglog("SQLProcedureColumns");
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
	debuglog("SQLProcedures");
	return SQL_SUCCESS;
}

SQLRETURN SQL_API SQLSetPos(
    SQLHSTMT           hstmt,
    SQLUSMALLINT       irow,
    SQLUSMALLINT       fOption,
    SQLUSMALLINT       fLock)
{
	debuglog("SQLSetPos");
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
	debuglog("SQLTablePrivileges");
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
	debuglog("SQLDrivers");
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
	debuglog("SQLBindParameter");
	return SQL_SUCCESS;
}

SQLRETURN SQL_API SQLAllocConnect(
    SQLHENV            henv,
    SQLHDBC FAR       *phdbc)
{
    IB_ENV *penv = (IB_ENV *)henv;
    IB_DBC *pdbc;

	debuglog("SQLAllocConnect");

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
	debuglog("SQLAllocEnv");
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
	debuglog("SQLBindCol");
	return SQL_SUCCESS;
}

SQLRETURN SQL_API SQLCancel(
    SQLHSTMT           hstmt)
{
	debuglog("SQLSqlCancel");
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
	debuglog("SQLColAttributes");
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
	debuglog("SQLConnect");
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
	debuglog("SQLDescribeCol");
	return SQL_SUCCESS;
}

SQLRETURN SQL_API SQLDisconnect(
    SQLHDBC            hdbc)
{
	debuglog("SQLDisconnect");
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
	//debuglog("SQLError");
	//strcpy( (char*)szSqlState, "9999" );
	//*pfNativeError=0;
	//*szErrorMsg = 0;
	//strcpy((char*)szErrorMsg,"");
	//*pcbErrorMsg=strlen((char*)szErrorMsg);
	//return SQL_ERROR;
	//return SQL_SUCCESS;

/*
	if ( errflg != 0 ){
		errflg=0;
	    debuglog("SQLError()=>ERR");
        return SQL_ERROR;
    }
    debuglog("SQLError()=>OK");
	return SQL_SUCCESS;
*/		


    IB_ENV  * penv  = (IB_ENV  *)henv;
    IB_DBC  * pdbc  = (IB_DBC  *)hdbc;
    IB_STMT * pstmt = (IB_STMT *)hstmt;
    IB_ERRINFO *perr = NULL;
    int msg_len = 0;

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
        // エラーメッセージが終わりか？
        if( *perr->msg == 0 ) {
		    debuglog("SQLError()=>ERR");
            return SQL_ERROR;
        }
    } else {
        //ISC_STATUS *pstatus = perr->status;
        char w_msg[512], *w_ptr;

        // エラーメッセージをすべて取得
        //w_ptr = perr->msg;
        //while( isc_interprete(w_msg, &pstatus ) ) {
        //    msg_len = perr->msg + 510 - w_ptr;
        //    strncpy( w_ptr, w_msg, msg_len );
        //    w_ptr += strlen(w_ptr);
        //    *w_ptr++ = '\n';
        //}
        //perr->native = perr->status[1];
        //perr->is_server = FALSE;
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
    } else {
        // 安全サイドなら
        // strcpy( szErrorMsg, perr->msg );
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
	debuglog("SQLFreeConnect");
	return SQL_SUCCESS;
}

SQLRETURN SQL_API SQLFreeEnv(
    SQLHENV            henv)
{
	debuglog("SQLFreeEnv");
	return SQL_SUCCESS;
}

SQLRETURN SQL_API SQLGetCursorName(
    SQLHSTMT           hstmt,
    SQLCHAR FAR       *szCursor,
    SQLSMALLINT        cbCursorMax,
    SQLSMALLINT FAR   *pcbCursor)
{
	debuglog("SQLGetCusorName");
	return SQL_SUCCESS;
}


SQLRETURN SQL_API SQLRowCount(
    SQLHSTMT           hstmt,
    SQLINTEGER FAR    *pcrow)
{
	debuglog("SQLRowCount");
	return SQL_SUCCESS;
}

SQLRETURN SQL_API SQLSetCursorName(
    SQLHSTMT           hstmt,
    SQLCHAR FAR       *szCursor,
    SQLSMALLINT        cbCursor)
{
	debuglog("SQLSetCursorName");
	return SQL_SUCCESS;
}

SQLRETURN SQL_API SQLTransact(
    SQLHENV            henv,
    SQLHDBC            hdbc,
    SQLUSMALLINT       fType)
{
	debuglog("SQLTransact(%d)",fType);
	return SQL_SUCCESS;
}


SQLRETURN SQL_API SQLSetParam(            /*      Use SQLBindParameter */
    SQLHSTMT           hstmt,
    SQLUSMALLINT       ipar,
    SQLSMALLINT        fCType,
    SQLSMALLINT        fSqlType,
    SQLUINTEGER        cbParamDef,
    SQLSMALLINT        ibScale,
    SQLPOINTER         rgbValue,
    SQLINTEGER FAR     *pcbValue)
{
	debuglog("SQLSetParam");
	return SQL_SUCCESS;
}

SQLRETURN SQL_API SQLGetConnectOption(
    SQLHDBC            hdbc,
    SQLUSMALLINT       fOption,
    SQLPOINTER         pvParam)
{
	IB_DBC *pdbc = (IB_DBC *)hdbc;

	debuglog("SQLGetConnectOption");
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
    IB_STMT *pstmt = (IB_STMT *)hstmt;
    IB_DBC  *pdbc;

    debuglog("SQLGetStmtOption(%d)", (int)fOption);
	return SQL_SUCCESS;

/*
    if( pstmt == NULL) return SQL_ERROR;

    pdbc = (IB_DBC*)pstmt->pare_dbc;
    switch( fOption ) {
      case SQL_QUERY_TIMEOUT:

        // 本来は全然違う設定。
        // nowait を指定する場所が無いので、とりあえず流用
        if( pdbc->is_nowait ) {
            *(DWORD *)pvParam = 1;
        } else {
            *(DWORD *)pvParam = 0;
        }
        return SQL_SUCCESS;

      case SQL_BIND_TYPE:
        *(DWORD *)pvParam = SQL_BIND_BY_COLUMN;
        return SQL_SUCCESS;

      case SQL_CONCURRENCY:
        *(DWORD *)pvParam = SQL_CONCUR_READ_ONLY;
        return SQL_SUCCESS;

      case SQL_CURSOR_TYPE:
        *(DWORD *)pvParam = SQL_CURSOR_FORWARD_ONLY;
        return SQL_SUCCESS;

      case SQL_RETRIEVE_DATA:
        *(DWORD *)pvParam = SQL_RD_OFF;
        return SQL_SUCCESS;

      case SQL_ROWSET_SIZE:
        *(DWORD *)pvParam = 1;
        return SQL_SUCCESS;

      case SQL_MAX_LENGTH:
        break;
    }

    return SQL_ERROR;
*/

}

SQLRETURN SQL_API SQLParamData(
    SQLHSTMT           hstmt,
    SQLPOINTER FAR    *prgbValue)
{
	debuglog("SQLParamData");
	return SQL_SUCCESS;
}

SQLRETURN SQL_API SQLPutData(
    SQLHSTMT           hstmt,
    SQLPOINTER         rgbValue,
    SQLINTEGER         cbValue)
{
	debuglog("SQLPutData");
	return SQL_SUCCESS;
}

SQLRETURN SQL_API SQLSetConnectOption(
    SQLHDBC            hdbc,
    SQLUSMALLINT       fOption,
    SQLUINTEGER        vParam)
{
	IB_DBC *pdbc = (IB_DBC *)hdbc;
	debuglog("SQLSetConnectOption(%d)",fOption);
	return SQL_SUCCESS;
}

SQLRETURN SQL_API SQLSetStmtOption(
    SQLHSTMT           hstmt,
    SQLUSMALLINT       fOption,
    SQLUINTEGER        vParam)
{
    long  llen ;

    IB_STMT *pstmt = (IB_STMT *)hstmt;

    debuglog("SQLSetStmtOption(%d)", (int)fOption);
	return SQL_SUCCESS;
/*
    if( pstmt == NULL ) return SQL_ERROR;

    switch( fOption ) {

      case SQL_CONCURRENCY:
        if( vParam == SQL_CONCUR_READ_ONLY ) {
            return SQL_SUCCESS;
        }
        return SQL_SUCCESS_WITH_INFO;

      case SQL_BIND_TYPE:
        // if( vParam == SQL_BIND_BY_COLUMN ) {
            return SQL_SUCCESS;
        // }
        // return SQL_SUCCESS_WITH_INFO;

      case SQL_QUERY_TIMEOUT:

        // 本来は全然違う設定。
        // nowait を指定する場所が無いので、とりあえず流用
        {
        IB_DBC *pdbc = (IB_DBC*)pstmt->pare_dbc;
        if( vParam == 1 ) pdbc->is_nowait = TRUE;
        else              pdbc->is_nowait = FALSE;
        }
        return SQL_SUCCESS;

      case  SQL_ROWSET_SIZE:
        llen = vParam;
        if( llen == 1 ) {
            return SQL_SUCCESS;
        } else {
            // 必要ならメッセージを...
            return SQL_SUCCESS_WITH_INFO;
        }

      case  SQL_RETRIEVE_DATA:
        if( vParam == SQL_RD_ON ) {
            // 必要ならメッセージを...
            return SQL_SUCCESS; // uso!
            return SQL_SUCCESS_WITH_INFO;
        } else {
            return SQL_SUCCESS;
        }
    }
    return SQL_ERROR;
*/

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
	debuglog("SQLDataSources");
	return SQL_SUCCESS;
}

