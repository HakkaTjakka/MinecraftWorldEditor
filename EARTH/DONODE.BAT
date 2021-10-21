
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
	node DUMP_OBJ_CITY_NOASYNC.js %1 21 --parallel-search --UTRECHT
	IF ERRORLEVEL 1 (
		echo !T! DOWNLOAD FAILED: DOWNLOADED_FILES\obj_new\%1-21>>DOWNLOAD_REPORT.TXT
		echo !T! DOWNLOAD FAILED: DOWNLOADED_FILES\obj_new\%1-21
	) else (
		echo !T! DOWNLOADED: DOWNLOADED_FILES\obj_new\%1-21>>DOWNLOADED.TXT
		echo !T! DOWNLOADED: DOWNLOADED_FILES\obj_new\%1-21
		if exist DOWNLOADED_FILES\obj_new\%1-21 (
			move DOWNLOADED_FILES\obj_new\%1-21 DOWNLOADED_FILES\obj
			IF ERRORLEVEL 1 (
				echo !T! MOVE FAILED: DOWNLOADED_FILES\obj_new\%1-21 TO DOWNLOADED_FILES\obj>>DOWNLOAD_REPORT.TXT
				echo !T! MOVE FAILED: DOWNLOADED_FILES\obj_new\%1-21 TO DOWNLOADED_FILES\obj
			)

		) else (
			echo !T! FILE DOES NOT EXIST: DOWNLOADED_FILES\obj_new\%1-21>>DOWNLOAD_REPORT.TXT
			echo !T! FILE DOES NOT EXIST: DOWNLOADED_FILES\obj_new\%1-21
		)
	)
	timeout 3
) ELSE (
	ECHO ALREADY EXIST: G:\PACMAN\EARTH\DOWNLOADED_FILES\NEW\UTRECHT\!result!\%1-21
)
exit /b
