
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
	IB_DBC *pdbc = (IB_DBC *)hdbc;
	char conn_str[1024];
	char szDRIVER[1024];
	char szDATABASE[1024];
	char szHOST[1024];
	char szPORT[1024];
	char szFRAMED[1024];
	char szDebug[1024];
	char hive_err_msg[1024];

	HKEY hkResult;
	DWORD dwDisposition;
	LONG lResult;
	char cRecordPath[_MAX_PATH];
	DWORD dwType;
	DWORD dwSize;

	if( pdbc == NULL ) return SQL_ERROR;

	debuglog("SQLDriverConnect(%X,%d,%d)", hdbc, (int)cbConnStrOutMax, (int)fDriverCompletion );

	//レジストリからデータ取得
	lResult = RegCreateKeyEx(HKEY_LOCAL_MACHINE, 
		"SOFTWARE\\ODBC\\ODBC.INI\\hiveodbc", 
		(DWORD)0, 
		"",
		REG_OPTION_NON_VOLATILE,
		KEY_ALL_ACCESS, NULL,
		&hkResult,
		&dwDisposition);
	if( lResult != ERROR_SUCCESS ){
		debuglog("SQLDriverConnect() registory error");
		return SQL_ERROR;
	}

	szDRIVER[0]=NULL;
	szDATABASE[0]=NULL;
	szHOST[0]=NULL;
	szPORT[0]=NULL;
	szFRAMED[0]=NULL;
	szDebug[0]=NULL;
	RegQueryValueEx(hkResult, "Driver",NULL,&dwType,NULL,&dwSize);
	RegQueryValueEx(hkResult, "Driver",NULL,&dwType,(LPBYTE)(LPCTSTR)szDRIVER,&dwSize);
	RegQueryValueEx(hkResult, "Database",NULL,&dwType,NULL,&dwSize);
	RegQueryValueEx(hkResult, "Database",NULL,&dwType,(LPBYTE)(LPCTSTR)szDATABASE,&dwSize);
	RegQueryValueEx(hkResult, "Server",NULL,&dwType,NULL,&dwSize);
	RegQueryValueEx(hkResult, "Server",NULL,&dwType,(LPBYTE)(LPCTSTR)szHOST,&dwSize);
	RegQueryValueEx(hkResult, "Port",NULL,&dwType,NULL,&dwSize);
	RegQueryValueEx(hkResult, "Port",NULL,&dwType,(LPBYTE)(LPCTSTR)szPORT,&dwSize);
	RegQueryValueEx(hkResult, "Framed",NULL,&dwType,NULL,&dwSize);
	RegQueryValueEx(hkResult, "Framed",NULL,&dwType,(LPBYTE)(LPCTSTR)szFRAMED,&dwSize);
	RegQueryValueEx(hkResult, "Debug",NULL,&dwType,NULL,&dwSize);
	RegQueryValueEx(hkResult, "Debug",NULL,&dwType,(LPBYTE)(LPCTSTR)szDebug,&dwSize);
	RegCloseKey(hkResult);
	if ( szDRIVER[0] == NULL || szDATABASE[0] == NULL || szHOST[0] == NULL || szPORT[0] == NULL || szFRAMED[0] == NULL || szDebug[0]==NULL ){
		debuglog("SQLDriverConnect() registory get error");
		return SQL_ERROR;
	}

	/*
	strcpy(szDRIVER,"hiveodbc");
	strcpy(szDATABASE,"default");
	strcpy(szHOST,"192.168.224.129");
	strcpy(szPORT,"10000");
	strcpy(szFRAMED,"0");
	*/
	sscanf(szDebug,"%d",&debug_level);

	sprintf( conn_str, "DSN=%s;HOST=%s;DATABASE=%s;PORT=%s;FRAMED=%s",szDRIVER, szHOST, szDATABASE, szPORT, szFRAMED);
	debuglog("SQLDriverConnect() %s",conn_str);

	if ( DBConnect(szHOST,atoi(szPORT)) != 0){
		debuglog("SQLDriverConnect() DBconnect error");
		return SQL_ERROR;
	}

	pdbc->is_open = TRUE;

	//出力設定
	strcpy( (char*)szConnStrOut, conn_str);
	*pcbConnStrOut = strlen( conn_str ) ;

	debuglog("SQLDriverConnect() %s,%d",szConnStrOut,*pcbConnStrOut);

	return SQL_SUCCESS;
}

