@ECHO OFF

setlocal EnableExtensions EnableDelayedExpansion

IF EXIST FIND_EXIST.TXT DEL FIND_EXIST.TXT
SET /A YES=0
SET /A NO=0
SET /A NO_DIR=0
SET /A NO_MTL=0
for /F "tokens=*" %%A in (OCTANTS_SORTED_CIRCLE.TXT) do (
	
	set "l=%%A"
	set "result=!l:~0,14!"
	set "D=  /  /       :     "
	IF EXIST G:\DONE\%%A.DAT (
		for /F "tokens=*" %%F in ("G:\DONE\%%A.DAT") do (
			SET D=%%~tF
		)
		
		ECHO 0:	ALREADY EXIST: G:\DONE\%%A.DAT	!D!/!YES!/!NO!/!NO_DIR!/!NO_MTL!
		ECHO 0:	ALREADY EXIST: G:\DONE\%%A.DAT	!D!/!YES!/!NO!/!NO_DIR!/!NO_MTL!>> FIND_EXIST.TXT
		SET /A YES=!YES! + 1
	) ELSE (
		IF NOT EXIST G:\PACMAN\EARTH\DOWNLOADED_FILES\NEW\UTRECHT\!result!\%%A-21 (
			ECHO 1:	DOESN'T EXIST: G:\PACMAN\EARTH\DOWNLOADED_FILES\NEW\UTRECHT\!result!\%%A-21	!D!/!YES!/!NO!/!NO_DIR!/!NO_MTL!
			ECHO 1:	DOESN'T EXIST: G:\PACMAN\EARTH\DOWNLOADED_FILES\NEW\UTRECHT\!result!\%%A-21	!D!/!YES!/!NO!/!NO_DIR!/!NO_MTL!>> FIND_EXIST.TXT
			SET /A NO_DIR=!NO_DIR! + 1
		) ELSE (
			IF NOT EXIST G:\PACMAN\EARTH\DOWNLOADED_FILES\NEW\UTRECHT\!result!\%%A-21\%%A.MTL (
				ECHO 2:	DOESN'T EXIST: G:\PACMAN\EARTH\DOWNLOADED_FILES\NEW\UTRECHT\!result!\%%A-21\%%A.MTL	!D!/!YES!/!NO!/!NO_DIR!/!NO_MTL!
				ECHO 2:	DOESN'T EXIST: G:\PACMAN\EARTH\DOWNLOADED_FILES\NEW\UTRECHT\!result!\%%A-21\%%A.MTL	!D!/!YES!/!NO!/!NO_DIR!/!NO_MTL!>> FIND_EXIST.TXT
				SET /A NO_MTL=!NO_MTL! + 1
			) ELSE (
				ECHO 3:	DOESN'T EXIST: G:\DONE\%%A.DAT	!D!/!YES!/!NO!/!NO_DIR!/!NO_MTL!
				REM DIR G:\PACMAN\EARTH\DOWNLOADED_FILES\NEW\UTRECHT\!result!\%%A-21\%%A.NBT
				ECHO 3:	DOESN'T EXIST: G:\DONE\%%A.DAT	!D!/!YES!/!NO!/!NO_DIR!/!NO_MTL!>> FIND_EXIST.TXT
				SET /A NO=!NO! + 1
			)
		)
	)
)
PAUSE
EXIT /B

rem     ECHO File Name Only       : %%~n?
rem     ECHO File Extension       : %%~x?
rem     ECHO Name in 8.3 notation : %%~sn?
rem     ECHO File Attributes      : %%~a?
rem     ECHO Located on Drive     : %%~d?
rem     ECHO File Size            : %%~z?
rem     ECHO Last-Modified Date   : %%~t?
rem     ECHO Drive and Path       : %%~dp?
rem     ECHO Drive                : %%~d?
rem     ECHO Fully Qualified Path : %%~f?
rem     ECHO FQP in 8.3 notation  : %%~sf?
rem     ECHO Location in the PATH : %%~dp$PATH:?
