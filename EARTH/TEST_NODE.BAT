@ECHO OFF

setlocal EnableExtensions EnableDelayedExpansion

call :DONODE DUMP_OBJ_CITY.js 30604241726161514 21 --parallel-search --UTRECHT
call :DONODE DUMP_OBJ_CITY.js 30604241726161516 21 --parallel-search --UTRECHT
call :DONODE DUMP_OBJ_CITY.js 30604241726161515 21 --parallel-search --UTRECHT
call :DONODE DUMP_OBJ_CITY.js 30604241726161505 21 --parallel-search --UTRECHT

pause
exit /b

:DONODE

set "l=%2"
set "result=!l:~0,14!"
IF NOT EXIST G:\PACMAN\EARTH\DOWNLOADED_FILES\NEW\UTRECHT\!result!\%2-21 (
	node DUMP_OBJ_CITY.js %2 21 --parallel-search --UTRECHT
) ELSE (
	ECHO ALREADY EXIST: G:\PACMAN\EARTH\DOWNLOADED_FILES\NEW\UTRECHT\!result!\%2-21
)
timeout 3
exit /b
