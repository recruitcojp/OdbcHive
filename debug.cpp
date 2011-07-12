#include "hiveodbc.h"


void debuglog( char *fmt, ... ) {
	va_list vl;
	static FILE *fp = NULL;
	char msg[10240];
	time_t timer;
	struct tm *tm;
	
	if ( reginfo.debug_level == 0 ){ return; }

	time(&timer);
	tm = localtime(&timer);

	va_start(vl, fmt);
	vsprintf(msg,fmt,vl);
	va_end(vl);

	//ƒtƒ@ƒCƒ‹‘‚«ž‚Ý
	if( (fp=fopen(reginfo.logfile,"a+")) == NULL ){
		return;
	}
	fprintf(fp,"%04d/%02d/%02d %02d:%02d:%02d %s\n",
		tm->tm_year+1900,tm->tm_mon+1,tm->tm_mday, tm->tm_hour,tm->tm_min,tm->tm_sec,msg);
	fclose(fp);

}


