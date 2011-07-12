#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <sql.h>
#include <sqlext.h>
#include <stdarg.h>
#include <time.h>
#include <errno.h>
#include <windows.h>

#define MIN(x,y) ( (x) < (y) ? (x) : (y) )
#define ABS(x)   ( (x) < 0 ? (-(x)) : (x) )


typedef unsigned char  uchar;
typedef unsigned short ushort;
typedef unsigned long  ulong;

typedef struct
{
        short       version;                        
        short       sqldaid[8];                     
        long        sqldabc;                        
        short       sqln;                           
        short       sqld;                           
        char sqlvar[1];                      
} XSQLDA;


// SQL_ERROR の情報構造体
typedef struct {
    char       msg[512+32];          // 根拠は無い
    BOOL       is_server;            // エラーの出所
    int        native;               // ネイティブエラーコード
} IB_ERRINFO;



//
// XSQLDA とアプリケーションデータ域との交換情報
//
//   ・param_type は、出力パラメータで使うか？
//
typedef struct {
    SQLUSMALLINT param_type;        // パラメータタイプ（未使用）
    SQLSMALLINT  odbc_type;         // ODBC SQL タイプ
    SQLUINTEGER  odbc_precision;    // ODBC Precision
    SQLSMALLINT  odbc_scale;        // ODBC Scale
    SQLSMALLINT  odbc_nullable;     // ODBC null 可否
    BOOL         is_bind;           // C 変数バインド済みか
    SQLSMALLINT  ctype;             // C 言語タイプ
    void         *data;             // C 変数データ
    SQLINTEGER   *pind;             // データ長およびNULL(負):入出力で使用
    SDWORD       limit;             // C 変数に格納時の限度（出力）
    BOOL         is_at_exec;        // 実行時パラメータ
    BOOL         is_at_exec_end;    // 実行時パラメータのput完了
    long         data_pos;          // CHUNK 処理（入出力）の次のバイト位置
} IB_XCHG;

//
//    HSTMT 領域
//
typedef struct {
    void          *next_stmt;     // next stmt ( list 構造 )
    void          *pare_dbc;      // 親の dbc
    char          *data;          // data area (use sqlda)
    char          *in_data;       // parameter data area (use in_sqlda)
    BOOL          prepared;       // already prepared
    BOOL          is_result;      // select or other(insert/update/delete...)
    XSQLDA        *in_sqlda;      // use input parameter
    XSQLDA        *sqlda;         // use fetch data 
    IB_XCHG       *xchgs;         // output    sqlvar <-> app variables
    IB_XCHG       *in_xchgs;      // parameter sqlvar <-> app variables
    int           in_xchgs_size;  // number of in_chages[]
    IB_ERRINFO    err;            // stmt レベルのエラー構造体
    int           catalog_opt;    // CATALOG Option(1=tables,2=columns...)
    ushort        isc_stmt_type;  // SQL ステートメントの種別
    int           need_data_no;   // 現在処理する実行時パラメータ
    BOOL          is_need_data;   // 実行時パラメータ処理中
    char          cursor_name[32];// カーソル名
    BOOL          is_cancel;      // SQLCancel 操作中
} IB_STMT;

//
//    HDBC 領域
//
typedef struct {
    IB_STMT       *stmt;          // 最初の hstmt 構造への参照
    BOOL          is_open;
    BOOL          is_noautocommit; // AUTOCOMMIT モード
    BOOL          is_trans;       // トランザクション中(htrans では判断出来ない)
    char          *dpb;           // DPB buffer
    int           dpb_size;
    long          sqlcode;        // 未使用
    long          odbc_cursors;   // SQLConnectOption
    void          *next_dbc;      // next dbc ( list 構造 )
    void          *pare_env;      // 親の henv
    ushort        dialect;        // InterBase の互換レベル
    int           isolation_level;  // 設定する ODBC の分離レベル
    int           current_isolation;// 現在 ODBC の分離レベル
    BOOL          is_nowait;      // NO WAIT
    IB_ERRINFO    err;            // dbc レベルのエラー構造体
} IB_DBC;

//
//    HENV 領域
//
typedef struct {
    IB_DBC        *dbc;          // 最初の hdbc （ list 構造 ）
    IB_ERRINFO    err;           // env レベルのエラー構造体
} IB_ENV;


//
//   レジストリ情報
//
typedef struct {
    char	driver[ MAX_PATH ];
    char	database[ MAX_PATH ];
    char	host[ MAX_PATH ];
	char	framed[ MAX_PATH ];
	char	logfile[ MAX_PATH ];
    short	port;
	int		debug_level;
} REGISTER_INFO;


/*
プロトタイプ宣言
*/
void debuglog( char *fmt, ... );
int DBExecute(int sockfd,char *query);
int DBFetchOne(int sockfd,char *ou);
int DBFetchN(int sockfd,char *ou);
int DBConnect(char *svr,short port);
int DBDisconnect();
int tcp_connect(char *server_name,short server_port);
int tcp_select(int type, int tm);
int tcp_write(char *buf, int buf_len);
int tcp_read(char *buf, int buf_len);
int tcp_disconnect();
char *utl_strSepValue(char *s1,char sep1,int idx1);
char *utl_strCut(char *in, char c);
int utl_GetRegistory();
int func_init(char *func);


/*
グローバル変数
*/
extern int sockfd;
extern int errflg;
extern REGISTER_INFO reginfo; 


