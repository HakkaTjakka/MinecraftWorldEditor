
setlocal EnableExtensions EnableDelayedExpansion

set "l=%1"
set "result=!l:~0,14!"
IF NOT EXIST G:\PACMAN\EARTH\DOWNLOADED_FILES\NEW\UTRECHT\!result!\%1-21 (
	REM node DUMP_OBJ_CITY.js %1 21 --parallel-search --UTRECHT
	for /f "tokens=*" %%G in ('time /t') do ( 
		set T=%%G
	)
		
	ECHO !T! DONT EXISTS: G:\PACMAN\EARTH\DOWNLOADED_FILES\NEW\UTRECHT\!result!\%1-21
	rem node DUMP_OBJ_CITY_NOASYNC.js %1 21 --parallel-search --UTRECHT
	node DUMP_OBJ_CITY_NOASYNC.js %1 21 --UTRECHT
	if exist DOWNLOADED_FILES\obj_new\%1-21 move DOWNLOADED_FILES\obj_new\%1-21 DOWNLOADED_FILES\obj
) ELSE (
	ECHO ALREADY EXIST: G:\PACMAN\EARTH\DOWNLOADED_FILES\NEW\UTRECHT\!result!\%1-21
)
REM timeout 3
exit /b
