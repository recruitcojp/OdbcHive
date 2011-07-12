#include "hiveodbc.h"

#define CHECK_LEN(x) \
    ( cbInfoValueMax > 0 && sizeof(x) > cbInfoValueMax ? \
        debuglog("ret len over!\n"), FALSE : TRUE )

#define RESULT_LEN(x) \
    ( pcbInfoValue ? *pcbInfoValue = sizeof(x), TRUE : FALSE )

SQLRETURN SQL_API SQLGetInfo(
	SQLHDBC			hdbc,
	SQLUSMALLINT	fInfoType,
	SQLPOINTER		rgbInfoValue,
	SQLSMALLINT		cbInfoValueMax,
	SQLSMALLINT FAR	*pcbInfoValue)
{
	if ( func_init("SQLGetInfo") != 0 ){ return SQL_ERROR; }

    switch( fInfoType ) {

      case SQL_ACCESSIBLE_PROCEDURES:
        if( rgbInfoValue && cbInfoValueMax > 1 ) {
            strcpy( (char*)rgbInfoValue, "N" );  // other driver
        }
        if( pcbInfoValue ) *pcbInfoValue = 1;
        return SQL_SUCCESS;

      case SQL_ACCESSIBLE_TABLES:
        if( rgbInfoValue && cbInfoValueMax > 1 ) {
            strcpy( (char*)rgbInfoValue, "N" );  // other driver
        }
        if( pcbInfoValue ) *pcbInfoValue = 1;
        return SQL_SUCCESS;

      case SQL_ACTIVE_CONNECTIONS:
        if( rgbInfoValue ) {
            *(SQLUSMALLINT *)rgbInfoValue = 10; // other driver
            if( pcbInfoValue ) *pcbInfoValue = sizeof( SQLUSMALLINT );
        }
        return SQL_SUCCESS;

      case SQL_ACTIVE_STATEMENTS:
        if( rgbInfoValue ) {
            *(SQLUSMALLINT *)rgbInfoValue = 0;
        }
        if( pcbInfoValue ) *pcbInfoValue = sizeof( SQLUSMALLINT );
        return SQL_SUCCESS;

      case SQL_ALTER_TABLE:
        if( rgbInfoValue ) {
            *(SQLUINTEGER *)rgbInfoValue =
                SQL_AT_ADD_COLUMN | SQL_AT_DROP_COLUMN;
        }
        if( pcbInfoValue ) *pcbInfoValue = sizeof( SQLUINTEGER );
        return SQL_SUCCESS;

      case SQL_BOOKMARK_PERSISTENCE:
        if( rgbInfoValue ) {
            *(SQLUINTEGER *)rgbInfoValue = 0; // other driver
            CHECK_LEN(SQLUINTEGER);
        }
        RESULT_LEN(SQLUINTEGER);
        return SQL_SUCCESS;

      case SQL_CATALOG_LOCATION:
        if( rgbInfoValue ) {
            *(SQLUSMALLINT *)rgbInfoValue = 0; // other driver
        }
        if( pcbInfoValue ) *pcbInfoValue = sizeof( SQLUSMALLINT );
        return SQL_SUCCESS;

      case SQL_CATALOG_NAME_SEPARATOR:
        if( rgbInfoValue && cbInfoValueMax > 1 ) {
            strcpy( (char*)rgbInfoValue, "" );     // other driver
        }
        if( pcbInfoValue ) *pcbInfoValue = 0;
        return SQL_SUCCESS;

      case SQL_CATALOG_TERM:
        if( rgbInfoValue && cbInfoValueMax > 7 ) {
            strcpy( (char*)rgbInfoValue, "catalog" );
        }
        if( pcbInfoValue ) *pcbInfoValue = 7;
        return SQL_SUCCESS;

      case SQL_CATALOG_USAGE:
        if( rgbInfoValue ) {
            *(SQLUINTEGER *)rgbInfoValue = 0;
        }
        if( pcbInfoValue ) *pcbInfoValue = sizeof( SQLUINTEGER );
        return SQL_SUCCESS;

      case SQL_COLUMN_ALIAS:
        if( rgbInfoValue && cbInfoValueMax > 1 ) {
            strcpy( (char*)rgbInfoValue, "N" );  // other driver
        }
        if( pcbInfoValue ) *pcbInfoValue = 1;
        return SQL_SUCCESS;

      case SQL_CONCAT_NULL_BEHAVIOR:
        if( rgbInfoValue && cbInfoValueMax > 1 ) {
            *(short *)rgbInfoValue = SQL_CB_NULL; // other driver
        }
        if( pcbInfoValue ) *pcbInfoValue = sizeof(short);
        return SQL_SUCCESS;

      case SQL_CONVERT_BIGINT:
        if( rgbInfoValue ) {
            *(SQLUINTEGER *)rgbInfoValue = 0; 
            CHECK_LEN(SQLUINTEGER);
        }
        RESULT_LEN(SQLUINTEGER);
        return SQL_SUCCESS;

      case SQL_CONVERT_BINARY:
        if( rgbInfoValue ) {
            *(SQLUINTEGER *)rgbInfoValue = 0; 
            CHECK_LEN(SQLUINTEGER);
        }
        RESULT_LEN(SQLUINTEGER);
        return SQL_SUCCESS;

      case SQL_CONVERT_BIT:
        if( rgbInfoValue ) {
            *(SQLUINTEGER *)rgbInfoValue = 0; 
            CHECK_LEN(SQLUINTEGER);
        }
        RESULT_LEN(SQLUINTEGER);
        return SQL_SUCCESS;

      case SQL_CONVERT_CHAR:
        if( rgbInfoValue ) {
            *(SQLUINTEGER *)rgbInfoValue = 0x00008002; // other driver
            CHECK_LEN(SQLUINTEGER);
        }
        RESULT_LEN(SQLUINTEGER);
        return SQL_SUCCESS;

      case SQL_CONVERT_DATE:
        if( rgbInfoValue ) {
            *(SQLUINTEGER *)rgbInfoValue = 0x00008101; // other driver
            CHECK_LEN(SQLUINTEGER);
        }
        RESULT_LEN(SQLUINTEGER);
        return SQL_SUCCESS;

      case SQL_CONVERT_DECIMAL:
        if( rgbInfoValue ) {
            *(SQLUINTEGER *)rgbInfoValue = 0; 
            CHECK_LEN(SQLUINTEGER);
        }
        RESULT_LEN(SQLUINTEGER);
        return SQL_SUCCESS;

      case SQL_CONVERT_DOUBLE:
        if( rgbInfoValue ) {
            *(SQLUINTEGER *)rgbInfoValue = 0; 
            CHECK_LEN(SQLUINTEGER);
        }
        RESULT_LEN(SQLUINTEGER);
        return SQL_SUCCESS;

      case SQL_CONVERT_FLOAT:
        if( rgbInfoValue ) {
            *(SQLUINTEGER *)rgbInfoValue = 0; 
            CHECK_LEN(SQLUINTEGER);
        }
        RESULT_LEN(SQLUINTEGER);
        return SQL_SUCCESS;

      case SQL_CONVERT_FUNCTIONS:
        if( rgbInfoValue ) {
            *(SQLUINTEGER *)rgbInfoValue = 0; // âΩÇ‡Ç»Çµ
            CHECK_LEN(SQLUINTEGER);
        }
        RESULT_LEN(SQLUINTEGER);
        return SQL_SUCCESS;

      case SQL_CONVERT_INTEGER:
        if( rgbInfoValue ) {
            *(SQLUINTEGER *)rgbInfoValue = 0; 
            CHECK_LEN(SQLUINTEGER);
        }
        RESULT_LEN(SQLUINTEGER);
        return SQL_SUCCESS;

      case SQL_CONVERT_LONGVARBINARY:
        if( rgbInfoValue ) {
            *(SQLUINTEGER *)rgbInfoValue = 0; 
            CHECK_LEN(SQLUINTEGER);
        }
        RESULT_LEN(SQLUINTEGER);
        return SQL_SUCCESS;

      case SQL_CONVERT_LONGVARCHAR:
        if( rgbInfoValue ) {
            *(SQLUINTEGER *)rgbInfoValue = 0; 
            CHECK_LEN(SQLUINTEGER);
        }
        RESULT_LEN(SQLUINTEGER);
        return SQL_SUCCESS;

      case SQL_CONVERT_NUMERIC:
        if( rgbInfoValue ) {
            *(SQLUINTEGER *)rgbInfoValue = 0x00008101; // other driver
            CHECK_LEN(SQLUINTEGER);
        }
        RESULT_LEN(SQLUINTEGER);
        return SQL_SUCCESS;

      case SQL_CURSOR_COMMIT_BEHAVIOR:
        if( rgbInfoValue ) {
            *(SQLUSMALLINT *)rgbInfoValue = SQL_CB_PRESERVE;
            CHECK_LEN(SQLUSMALLINT);
        }
        RESULT_LEN(SQLUSMALLINT);
        return SQL_SUCCESS;

      case SQL_CURSOR_ROLLBACK_BEHAVIOR:
        if( rgbInfoValue ) {
            *(SQLUSMALLINT *)rgbInfoValue = SQL_CB_DELETE;
            CHECK_LEN(SQLUSMALLINT);
        }
        RESULT_LEN(SQLUSMALLINT);
        return SQL_SUCCESS;

      case SQL_DATABASE_NAME:
        if( rgbInfoValue && cbInfoValueMax > 10 ) {
            strcpy( (char*)rgbInfoValue, "hiveodbc" );
        }
        if( pcbInfoValue ) *pcbInfoValue = 10;
        return SQL_SUCCESS;

      case SQL_DBMS_NAME:
        if( rgbInfoValue && cbInfoValueMax > 10 ) {
            strcpy( (char*)rgbInfoValue, "hiveodbc" );
        }
        if( pcbInfoValue ) *pcbInfoValue = 8;
        return SQL_SUCCESS;

      case SQL_DBMS_VER:
        if( rgbInfoValue && cbInfoValueMax > 10 ) {
            strcpy( (char*)rgbInfoValue, "01.01.0000" );
        }
        if( pcbInfoValue ) *pcbInfoValue = 10;
        return SQL_SUCCESS;

      case SQL_DATA_SOURCE_READ_ONLY:
        if( rgbInfoValue ) {
            strcpy( (char*)rgbInfoValue, "N" );
        }
        if( pcbInfoValue ) *pcbInfoValue = 1;
        return SQL_SUCCESS;

      case SQL_DEFAULT_TXN_ISOLATION:
        if( rgbInfoValue ) {
            *(SQLUINTEGER *)rgbInfoValue = SQL_TXN_READ_COMMITTED;
            CHECK_LEN(SQLUINTEGER);
        }
        RESULT_LEN(SQLUINTEGER);
        return SQL_SUCCESS;

      case SQL_DRIVER_ODBC_VER:
        if( rgbInfoValue && cbInfoValueMax > 5 ) {
            strcpy( (char*)rgbInfoValue, "01.00" );
        }
        if( pcbInfoValue ) *pcbInfoValue = 5;
        return SQL_SUCCESS;

      case SQL_DRIVER_NAME:
        if( rgbInfoValue && cbInfoValueMax > 10 ) {
            strcpy( (char*)rgbInfoValue, "hiveodbc.dll" );
        }
        if( pcbInfoValue ) *pcbInfoValue = 12;
        return SQL_SUCCESS;

      case SQL_DRIVER_VER:
        if( rgbInfoValue && cbInfoValueMax > 10 ) {
            strcpy( (char*)rgbInfoValue, "01.00.0000" );
        }
        if( pcbInfoValue ) *pcbInfoValue = 10;
        return SQL_SUCCESS;

      case SQL_DYNAMIC_CURSOR_ATTRIBUTES1:
        if( rgbInfoValue ) {
            *(SQLUINTEGER *)rgbInfoValue = SQL_CA1_NEXT;
            CHECK_LEN(SQLUINTEGER);
        }
        RESULT_LEN(SQLUINTEGER);
        return SQL_SUCCESS;

      case SQL_EXPRESSIONS_IN_ORDERBY:
        if( rgbInfoValue && cbInfoValueMax > 1 ) {
            strcpy( (char*)rgbInfoValue, "N" );
        }
        if( pcbInfoValue ) *pcbInfoValue = 1;
        return SQL_SUCCESS;

      case SQL_FETCH_DIRECTION:
        if( rgbInfoValue ) {
            *(SQLUINTEGER *)rgbInfoValue = SQL_FD_FETCH_NEXT;
            CHECK_LEN(SQLUINTEGER);
        }
        RESULT_LEN(SQLUINTEGER);
        return SQL_SUCCESS;

      case SQL_FORWARD_ONLY_CURSOR_ATTRIBUTES1:
        if( rgbInfoValue ) {
            *(SQLUINTEGER *)rgbInfoValue = SQL_CA1_NEXT;
            CHECK_LEN(SQLUINTEGER);
        }
        RESULT_LEN(SQLUINTEGER);
        return SQL_SUCCESS;

      case SQL_GETDATA_EXTENSIONS:
        if( rgbInfoValue ) {
            *(long *)rgbInfoValue = SQL_GD_ANY_COLUMN |
            SQL_GD_ANY_ORDER | SQL_GD_BOUND |
            SQL_GD_BLOCK;
        }
        if( pcbInfoValue ) *pcbInfoValue = 4;
        return SQL_SUCCESS;

      case SQL_GROUP_BY:
        if( rgbInfoValue ) {
            *(short *)rgbInfoValue = SQL_GB_GROUP_BY_EQUALS_SELECT; 
            CHECK_LEN(SQLUSMALLINT);
        }
        RESULT_LEN(SQLUSMALLINT);
        return SQL_SUCCESS;

      case SQL_IDENTIFIER_QUOTE_CHAR:
        if( rgbInfoValue ) {
            strcpy( (char*)rgbInfoValue, "" );
        }
        if( pcbInfoValue ) *pcbInfoValue = 1;
        return SQL_SUCCESS;

      case SQL_IDENTIFIER_CASE:
        if( rgbInfoValue ) {
            *(short *)rgbInfoValue = SQL_IC_UPPER; 
            CHECK_LEN(SQLUSMALLINT);
        }
        RESULT_LEN(SQLUSMALLINT);
        return SQL_SUCCESS;

      case SQL_KEYSET_CURSOR_ATTRIBUTES1:
        if( rgbInfoValue ) {
            *(SQLUINTEGER *)rgbInfoValue = SQL_CA1_NEXT;
            CHECK_LEN(SQLUINTEGER);
        }
        RESULT_LEN(SQLUINTEGER);
        return SQL_SUCCESS;

      case SQL_LIKE_ESCAPE_CLAUSE:
        if( rgbInfoValue ) {
            strcpy( (char*)rgbInfoValue, "N" );
        }
        if( pcbInfoValue ) *pcbInfoValue = 1;
        return SQL_SUCCESS;

      case SQL_LOCK_TYPES:
        if( rgbInfoValue ) {
            *(long *)rgbInfoValue = SQL_LCK_NO_CHANGE;
        }
        if( pcbInfoValue ) *pcbInfoValue = 4;
        return SQL_SUCCESS;

      case SQL_MAX_CATALOG_NAME_LEN:
        if( rgbInfoValue ) {
            *(SQLUSMALLINT *)rgbInfoValue = 0;   // other driver
            CHECK_LEN(SQLUSMALLINT);
        }
        RESULT_LEN(SQLUSMALLINT);
        return SQL_SUCCESS;

      case SQL_MAX_COLUMN_NAME_LEN:
        if( rgbInfoValue ) {
            *(short *)rgbInfoValue = 31; 
        }
        if( pcbInfoValue ) *pcbInfoValue = 2;
        return SQL_SUCCESS;

      case SQL_MAX_CURSOR_NAME_LEN:
        if( rgbInfoValue ) {
            *(short *)rgbInfoValue = 31;  // other driver (max 18)
        }
        if( pcbInfoValue ) *pcbInfoValue = 2;
        return SQL_SUCCESS;

      case SQL_MAX_PROCEDURE_NAME_LEN:
        if( rgbInfoValue ) {
            *(SQLUSMALLINT *)rgbInfoValue = 27; // other driver 31?
            CHECK_LEN(SQLUSMALLINT);
        }
        RESULT_LEN(SQLUSMALLINT);
        return SQL_SUCCESS;

      case SQL_MAX_SCHEMA_NAME_LEN:
        if( rgbInfoValue ) {
            *(SQLUSMALLINT *)rgbInfoValue = 0;  // other driver
            CHECK_LEN(SQLUSMALLINT);
        }
        RESULT_LEN(SQLUSMALLINT);
        return SQL_SUCCESS;

      case SQL_MAX_TABLE_NAME_LEN:
        if( rgbInfoValue ) {
            *(short *)rgbInfoValue = 31; 
        }
        if( pcbInfoValue ) *pcbInfoValue = 2;
        return SQL_SUCCESS;

      case SQL_MULT_RESULT_SETS:
        if( rgbInfoValue ) {
            strcpy( (char*)rgbInfoValue, "N" );
        }
        if( pcbInfoValue ) *pcbInfoValue = 1;
        return SQL_SUCCESS;

      case SQL_MULTIPLE_ACTIVE_TXN:
        if( rgbInfoValue ) {
            strcpy( (char*)rgbInfoValue, "Y" );
        }
        if( pcbInfoValue ) *pcbInfoValue = 1;
        return SQL_SUCCESS;

      case SQL_NULL_COLLATION:
        if( rgbInfoValue ) {
            *(short *)rgbInfoValue = 0; // ?
        }
        if( pcbInfoValue ) *pcbInfoValue = 2;
        return SQL_SUCCESS;

      case SQL_NEED_LONG_DATA_LEN:
        if( rgbInfoValue ) {
            *(char *)rgbInfoValue = 'N'; 
        }
        if( pcbInfoValue ) *pcbInfoValue = 1;
        return SQL_SUCCESS;

      case SQL_NUMERIC_FUNCTIONS:
        if( rgbInfoValue ) {
            *(long *)rgbInfoValue = 0; // âΩÇ‡Ç»Çµ
        }
        if( pcbInfoValue ) *pcbInfoValue = 4;
        return SQL_SUCCESS;

      case SQL_ODBC_API_CONFORMANCE:
        if( rgbInfoValue ) {
            *(short *)rgbInfoValue = SQL_OAC_LEVEL1;
        }
        if( pcbInfoValue ) *pcbInfoValue = sizeof( SQLUSMALLINT );
        return SQL_SUCCESS;

      case SQL_ORDER_BY_COLUMNS_IN_SELECT:
        if( rgbInfoValue && cbInfoValueMax > 1 ) {
            strcpy( (char*)rgbInfoValue, "N" );
        }
        if( pcbInfoValue ) *pcbInfoValue = 1;
        return SQL_SUCCESS;

      case SQL_OUTER_JOINS:
        if( rgbInfoValue && cbInfoValueMax > 1 ) {
            strcpy( (char*)rgbInfoValue, "Y" );
        }
        if( pcbInfoValue ) *pcbInfoValue = 1;
        return SQL_SUCCESS;

      case SQL_OWNER_TERM:
        if( rgbInfoValue && cbInfoValueMax > 5 ) {
            strcpy( (char*)rgbInfoValue, "OWNER" );
        }
        if( pcbInfoValue ) *pcbInfoValue = 5;
        return SQL_SUCCESS;

      case SQL_POSITIONED_STATEMENTS:
        if( rgbInfoValue ) {
            *(SQLUINTEGER *)rgbInfoValue = 0; 
            CHECK_LEN(SQLUINTEGER);
        }
        RESULT_LEN(SQLUINTEGER);
        return SQL_SUCCESS;

      case SQL_POS_OPERATIONS:
        if( rgbInfoValue ) {
            *(SQLUINTEGER *)rgbInfoValue = 0; 
            CHECK_LEN(SQLUINTEGER);
        }
        RESULT_LEN(SQLUINTEGER);
        return SQL_SUCCESS;

      case SQL_PROCEDURES:
        if( rgbInfoValue ) {
            strcpy( (char*)rgbInfoValue, "Y" );
        }
        if( pcbInfoValue ) *pcbInfoValue = 1;
        return SQL_SUCCESS;

      case SQL_QUOTED_IDENTIFIER_CASE:
        if( rgbInfoValue ) {
            *(short *)rgbInfoValue = SQL_IC_UPPER; 
        }
        if( pcbInfoValue ) *pcbInfoValue = 2;
        return SQL_SUCCESS;

      case SQL_ROW_UPDATES:
        if( rgbInfoValue ) {
            strcpy( (char*)rgbInfoValue, "Y" );
        }
        if( pcbInfoValue ) *pcbInfoValue = 1;
        return SQL_SUCCESS;

      case SQL_SCROLL_CONCURRENCY:
        if( rgbInfoValue ) {
            *(long *)rgbInfoValue = SQL_SCCO_READ_ONLY;
        }
        if( pcbInfoValue ) *pcbInfoValue = 4;
        return SQL_SUCCESS;

      case SQL_SCROLL_OPTIONS:
        if( rgbInfoValue ) {
            *(long *)rgbInfoValue = SQL_SO_FORWARD_ONLY;
        }
        if( pcbInfoValue ) *pcbInfoValue = 4;
        return SQL_SUCCESS;

      case SQL_SEARCH_PATTERN_ESCAPE:
        if( rgbInfoValue && cbInfoValueMax > 1 ) {
            strcpy( (char*)rgbInfoValue, "" );
        }
        if( pcbInfoValue ) *pcbInfoValue = 0;
        return SQL_SUCCESS;

      case SQL_STATIC_CURSOR_ATTRIBUTES1: // ODBC 3.0
        if( rgbInfoValue ) {
            *(SQLUINTEGER *)rgbInfoValue = SQL_CA1_NEXT;
            CHECK_LEN(SQLUINTEGER);
        }
        RESULT_LEN(SQLUINTEGER);
        return SQL_SUCCESS;

      case SQL_STATIC_SENSITIVITY:
        if( rgbInfoValue ) {
            *(long *)rgbInfoValue = 0; // âΩÇ‡èoóàÇ»Ç¢
        }
        if( pcbInfoValue ) *pcbInfoValue = 4;
        return SQL_SUCCESS;

      case SQL_STRING_FUNCTIONS:
        if( rgbInfoValue ) {
            *(long *)rgbInfoValue = 0; // âΩÇ‡Ç»Çµ
        }
        if( pcbInfoValue ) *pcbInfoValue = 4;
        return SQL_SUCCESS;

      case SQL_SYSTEM_FUNCTIONS:
        if( rgbInfoValue ) {
            *(long *)rgbInfoValue = 0; // âΩÇ‡Ç»Çµ
        }
        if( pcbInfoValue ) *pcbInfoValue = 4;
        return SQL_SUCCESS;

      case SQL_TIMEDATE_FUNCTIONS:
        if( rgbInfoValue ) {
            *(long *)rgbInfoValue = 0; // âΩÇ‡Ç»Çµ
        }
        if( pcbInfoValue ) *pcbInfoValue = 4;
        return SQL_SUCCESS;

      case SQL_TXN_CAPABLE:
        if( rgbInfoValue ) {
            *(short *)rgbInfoValue = SQL_TC_DDL_COMMIT;
        }
        if( pcbInfoValue ) *pcbInfoValue = 2;
        return SQL_SUCCESS;

      case SQL_TXN_ISOLATION_OPTION:
        if( rgbInfoValue ) {
            *(long *)rgbInfoValue =
                SQL_TXN_READ_COMMITTED  |
                SQL_TXN_REPEATABLE_READ |
                SQL_TXN_SERIALIZABLE    ;
        }
        if( pcbInfoValue ) *pcbInfoValue = 4;
        return SQL_SUCCESS;

      case SQL_UNION:
        if( rgbInfoValue ) {
            *(SQLUINTEGER *)rgbInfoValue = SQL_U_UNION | SQL_U_UNION_ALL;
            CHECK_LEN(SQLUINTEGER);
        }
        RESULT_LEN(SQLUINTEGER);
        return SQL_SUCCESS;
    }
    if( pcbInfoValue ) *pcbInfoValue = 0;

	debuglog("unknown SQLGetInfo(%d)", fInfoType );
	return SQL_ERROR;

}
