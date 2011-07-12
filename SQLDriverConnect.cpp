#include "hiveodbc.h"

SQLRETURN SQL_API SQLDriverConnect(
	SQLHDBC			hdbc,
	SQLHWND			hwnd,
	SQLCHAR FAR	   *szConnStrIn,
	SQLSMALLINT		cbConnStrIn,
	SQLCHAR FAR	   *szConnStrOut,
	SQLSMALLINT		cbConnStrOutMax,
	SQLSMALLINT FAR   *pcbConnStrOut,
	SQLUSMALLINT	   fDriverCompletion)
{
	if ( func_init("SQLDriverConnect") != 0 ){ return SQL_ERROR; }

	sprintf( (char*)szConnStrOut, "DSN=%s;HOST=%s;DATABASE=%s;PORT=%d;FRAMED=%s",reginfo.driver, reginfo.host, reginfo.database, reginfo.port, reginfo.framed);
	*pcbConnStrOut = strlen( (char*)szConnStrOut ) ;

	//コネクト
	debuglog("SQLDriverConnect() %s",szConnStrOut);
	if ( DBConnect(reginfo.host, reginfo.port) != 0){
		debuglog("SQLDriverConnect() DBconnect error");
		return SQL_ERROR;
	}

	debuglog("SQLDriverConnect() %s",szConnStrOut);

	return SQL_SUCCESS;
}

