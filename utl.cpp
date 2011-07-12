#include "hiveodbc.h"

int func_init(char *func){
	static int init_flg=0;
	int ret=0;

	if ( init_flg == 0 ){
		init_flg=1;
		if ( utl_GetRegistory() != 0 ){ ret=1; }
	}

	debuglog(func);

	return ret;
}


char *utl_strSepValue(char *s1,char sep1,int idx1){
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

char *utl_strCut(char *in, char c){
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

int utl_GetRegistory(){
	HKEY hkResult;
	DWORD dwDisposition;
	LONG lResult;
	char cRecordPath[_MAX_PATH];
	DWORD dwType;
	DWORD dwSize;

	char szDRIVER[1024];
	char szDATABASE[1024];
	char szHOST[1024];
	char szPORT[1024];
	char szFRAMED[1024];
	char szDebug[1024];
	char szLogFile[1024];


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
		return 1;
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
	RegQueryValueEx(hkResult, "LogFile",NULL,&dwType,NULL,&dwSize);
	RegQueryValueEx(hkResult, "LogFile",NULL,&dwType,(LPBYTE)(LPCTSTR)szLogFile,&dwSize);
	RegCloseKey(hkResult);
	if ( szDRIVER[0] == NULL || szDATABASE[0] == NULL || szHOST[0] == NULL || 
				szPORT[0] == NULL || szFRAMED[0] == NULL || szDebug[0]==NULL || szLogFile[0]==NULL ){
		debuglog("SQLDriverConnect() registory get error");
		return 1;
	}

	//グローバル変数設定
	strcpy(reginfo.driver, szDRIVER);
	strcpy(reginfo.database, szDATABASE);
	strcpy(reginfo.host, szHOST);
	strcpy(reginfo.framed, szFRAMED);
	strcpy(reginfo.logfile, szLogFile);
	sscanf(szPORT,"%d",&reginfo.port);
	sscanf(szDebug,"%d",&reginfo.debug_level);

	return 0;
}

