#include "hiveodbc.h"

UWORD is_odbc_function( SQLSMALLINT fFunction ) ;

SQLRETURN SQL_API SQLGetFunctions(
    SQLHDBC            hdbc,
    SQLUSMALLINT       fFunction,
    SQLUSMALLINT FAR  *pfExists)
{
	if ( func_init("SQLGetFunction") != 0 ){ return SQL_ERROR; }

    if (fFunction == SQL_API_ALL_FUNCTIONS) {
        int i;

        memset(pfExists, 0, sizeof(UWORD)*100);

        for( i = 0; i < 100; i++ ) {
            pfExists[i] = is_odbc_function( (SQLSMALLINT)i );
        }
    } else {
        *pfExists = is_odbc_function( fFunction );
    }
    return SQL_SUCCESS;
}


UWORD is_odbc_function( SQLSMALLINT fFunction ) {

    switch(fFunction) {
      case SQL_API_SQLALLOCCONNECT:     return  TRUE;  
      case SQL_API_SQLALLOCENV:         return  TRUE;  
      case SQL_API_SQLALLOCSTMT:        return  TRUE; 
      case SQL_API_SQLBINDCOL:          return  TRUE; 
      case SQL_API_SQLCANCEL:           return  TRUE; 
      case SQL_API_SQLCOLATTRIBUTES:    return  TRUE; 
      case SQL_API_SQLCONNECT:          return  TRUE; 
      case SQL_API_SQLDESCRIBECOL:      return  TRUE;
      case SQL_API_SQLDISCONNECT:       return  TRUE; 
      case SQL_API_SQLERROR:            return  TRUE; 
      case SQL_API_SQLEXECDIRECT:       return  TRUE; 
      case SQL_API_SQLEXECUTE:          return  TRUE; 
      case SQL_API_SQLFETCH:            return  TRUE; 
      case SQL_API_SQLFREECONNECT:      return  TRUE; 
      case SQL_API_SQLFREEENV:          return  TRUE; 
      case SQL_API_SQLFREESTMT:         return  TRUE; 
      case SQL_API_SQLGETCURSORNAME:    return  TRUE; 
      case SQL_API_SQLNUMRESULTCOLS:    return  TRUE; 
      case SQL_API_SQLPREPARE:          return  TRUE; 
      case SQL_API_SQLROWCOUNT:         return  TRUE; 
      case SQL_API_SQLSETCURSORNAME:    return  TRUE; 
      case SQL_API_SQLSETPARAM:         return  TRUE;
      case SQL_API_SQLTRANSACT:         return  TRUE; 

      // ODBC level 1 functions
      case SQL_API_SQLBINDPARAMETER:    return  TRUE; 
      case SQL_API_SQLCOLUMNS:          return  TRUE; 
      case SQL_API_SQLDRIVERCONNECT:    return  TRUE; 
      case SQL_API_SQLGETCONNECTOPTION: return  TRUE;
      case SQL_API_SQLGETDATA:          return  TRUE; 
      case SQL_API_SQLGETFUNCTIONS:     return  TRUE; 
      case SQL_API_SQLGETINFO:          return  TRUE; 
      case SQL_API_SQLGETSTMTOPTION:    return  TRUE;
      case SQL_API_SQLGETTYPEINFO:      return  TRUE; 
      case SQL_API_SQLPARAMDATA:        return  TRUE; 
      case SQL_API_SQLPUTDATA:          return  TRUE; 
      case SQL_API_SQLSETCONNECTOPTION: return  TRUE;
      case SQL_API_SQLSETSTMTOPTION:    return  TRUE; 
      case SQL_API_SQLSPECIALCOLUMNS:   return  TRUE; 
      case SQL_API_SQLSTATISTICS:       return  TRUE; 
      case SQL_API_SQLTABLES:           return  TRUE; 

      // ODBC level 2 functions
      // ExtendedFetch をエミュレートさせる為、FALSE を返す
      case SQL_API_SQLBROWSECONNECT:    return  TRUE;  // other driver
      case SQL_API_SQLCOLUMNPRIVILEGES: return  TRUE;  // other driver
      case SQL_API_SQLDATASOURCES:      return  FALSE;
      case SQL_API_SQLDESCRIBEPARAM:    return  FALSE; // other driver
      case SQL_API_SQLDRIVERS:          return  FALSE;
      case SQL_API_SQLEXTENDEDFETCH:    return  FALSE; 
      case SQL_API_SQLFOREIGNKEYS:      return  TRUE; 
      case SQL_API_SQLMORERESULTS:      return  TRUE; 
      case SQL_API_SQLNATIVESQL:        return  TRUE; 
      case SQL_API_SQLNUMPARAMS:        return  TRUE; 
      case SQL_API_SQLPARAMOPTIONS:     return  FALSE; 
      case SQL_API_SQLPRIMARYKEYS:      return  TRUE; 
      case SQL_API_SQLPROCEDURECOLUMNS: return  TRUE;  // other driver
      case SQL_API_SQLPROCEDURES:       return  TRUE;  // other driver
      case SQL_API_SQLSETPOS:           return  FALSE; 
      case SQL_API_SQLSETSCROLLOPTIONS: return  FALSE;
      case SQL_API_SQLTABLEPRIVILEGES:  return  TRUE;  // other driver
    }

    return FALSE;
}
