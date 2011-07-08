target : hiveodbc.dll

CPP_PROJ=/nologo /O2 /c /clr


LINK32 = link.exe

LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib wsock32.lib /nologo /subsystem:windows /dll \
 /machine:I386 /def:".\hiveodbc.def"\
 /out:hiveodbc.dll" /implib:hiveodbc.lib 

LINK32_OBJS= \
SQLGetInfo.obj \
SQLDriverConnect.obj \
SQLGetFunctions.obj \
getdata.obj \
hiveodbc.obj \
hiveclient.obj \
tcp.obj \
debug.obj

.cpp.obj:
   $(CPP) $(CPP_PROJ) $<  

hiveodbc.dll : $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

#	copy /Y hiveodbc.dll D:\hiveodbc

clean :
    del *.obj
    del *.res
    del *.exp

