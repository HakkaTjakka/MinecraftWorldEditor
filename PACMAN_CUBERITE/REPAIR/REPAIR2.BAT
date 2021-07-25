@echo off
setlocal EnableExtensions EnableDelayedExpansion

if exist OBJECT_ARRAY1.TXT del OBJECT_ARRAY1.TXT
if exist OBJECT_ARRAY2.TXT del OBJECT_ARRAY2.TXT
if exist download_again.bat del download_again.bat
if exist download_again2.bat del download_again2.bat
if exist REGION_CORRUPT.txt del REGION_CORRUPT.txt
if exist OBJECT_ARRAY_RANGE.TXT del OBJECT_ARRAY_RANGE.TXT

for /f "tokens=*" %%F in ('dir /b ".\*.png"') do (

	if exist OBJECT_ARRAY3.TXT del OBJECT_ARRAY3.TXT

	ECHO ====================================
	echo %%~nF
	REM echo %%~nF
	echo %%~nF.mca >> REGION_CORRUPT.txt
	if exist f:\cut\done\%%~nF.info type f:\cut\done\%%~nF.info > octant_list.txt
	if exist f:\cut\%%~nF.info type f:\cut\%%~nF.info >> octant_list.txt

	for %%X in (octant_list.txt) do (
		REM echo %%X
		for /f "tokens=*" %%R in (%%X) do (
			REM echo %%R
			call :MAKE_OBJECT_ARRAY %%R
		)
	)
	echo.
	for /f "tokens=2,3 delims==." %%a in ("%%F") do (
		rem ECHO R.%%a.%%b
		REM ECHO TOGEO.BAT: %%a %%b

		FOR /L %%Y IN (-1,3,2) DO (
			FOR /L %%X IN (-1,3,2) DO (
				SET /A XX=%%X + %%a
				SET /A YY=%%Y + %%b
				REM ECHO !XX!,!YY!
				for /f "tokens=1,2 delims==[]" %%a in ('CALL TO_GEO.BAT !XX! !YY!') do (
					REM ECHO TO_GEO.BAT: %%a %%b
					for /f "tokens=*" %%c in ('CALL TO_OCTANT.BAT %%b %%a') do (
						REM ECHO TO_OCTANT.BAT: %%c
						CALL :FIND_OCTANT %%c
					)
				)
			)
		)
	)
	CALL :FIND_RANGE
	rem if exist f:\cut\done\%%~nF.info type f:\cut\done\%%~nF.info
	rem if exist f:\cut\%%~nF.info type f:\cut\%%~nF.info
	rem PAUSE
)


pause
exit /b

:MAKE_OBJECT_ARRAY

for /f "tokens=*" %%R in ("%*") do (
	REM echo %%R
	for /f "tokens=2,3 delims==[]" %%a in ("%%R") do (
		set "l=%%a"
		set var_x=!l: =!
		set "l=%%b"
		set "var_y=!l: =!
		if !var_x! == 0 (
			if !var_y! == 0 (
				REM echo ERR: %%R
				exit /b
			)
		)
		ECHO X=!var_x! Y=!var_y! %1 %%F>> OBJECT_ARRAY1.TXT
		ECHO X=!var_x! Y=!var_y! OCTANT=%1
		ECHO [!var_x!][!var_y!] %1 %%F>> OBJECT_ARRAY3.TXT

REM 		set /a var_x_min=!var_x! - 1
REM 		set /a var_x_plus=!var_x! + 1
REM 		set /a var_y_min=!var_y! - 1
REM 		set /a var_y_plus=!var_y! + 1

REM 		ECHO X=!var_x_min! Y=!var_y!>> OBJECT_ARRAY.TXT
REM 		ECHO X=!var_x_plus! Y=!var_y!>> OBJECT_ARRAY.TXT
REM 		ECHO X=!var_x! Y=!var_y_min!>> OBJECT_ARRAY.TXT
REM 		ECHO X=!var_x! Y=!var_y_plus!>> OBJECT_ARRAY.TXT
REM 		ECHO X=!var_x_min! Y=!var_y_min!>> OBJECT_ARRAY.TXT
REM 		ECHO X=!var_x_min! Y=!var_y_plus!>> OBJECT_ARRAY.TXT
REM 		ECHO X=!var_x_plus! Y=!var_y_min!>> OBJECT_ARRAY.TXT
REM 		ECHO X=!var_x_plus! Y=!var_y_plus!>> OBJECT_ARRAY.TXT





		
		echo node DUMP_OBJ_CITY.js %1 21 --parallel-search --UTRECHT >> download_again.bat
	)
)
exit /b

:FIND_OCTANT

type F:\PACMAN\EARTH\UTRECHT_LAT_LONG_CENTER2.TXT | find "=%1" > NEW_OCTANT.TXT


for %%O in (NEW_OCTANT.TXT) do (
	if not %%~zO == 0 (
		for /f "tokens=*" %%R in (%%O) do (
			rem echo %%R
			for /f "tokens=2,3 delims==[]" %%a in ("%%R") do (
				set "l=%%a"
				set var_x=!l: =!
				set "l=%%b"
				set "var_y=!l: =!
				ECHO X=!var_x! Y=!var_y! %1 %%F>> OBJECT_ARRAY2.TXT
				ECHO [!var_x!][!var_y!] %1 %%F>> OBJECT_ARRAY3.TXT
				ECHO X=!var_x! Y=!var_y! OCTANT=%1
			)
		)
		echo node DUMP_OBJ_CITY.js %1 21 --parallel-search --UTRECHT >> download_again2.bat
	)
)

exit /b

:FIND_RANGE

for %%O in (OBJECT_ARRAY3.TXT) do (
	if not %%~zO == 0 (
		set /a XX_MIN=99999
		set /a YY_MIN=99999
		set /a XX_MAX=-99999
		set /a YY_MAX=-99999
		for /f "tokens=*" %%R in (%%O) do (
			REM echo R=%%R
			for /f "tokens=1,2 delims==[]" %%a in ("%%R") do (
				set "l=%%a"
				set var_x=!l: =!
				set "l=%%b"
				set "var_y=!l: =!
				set /a XX=!var_x!
				set /a YY=!var_y!
				REM ECHO XX=!XX! YY=!YY!
				if !XX! GTR !XX_MAX! SET /A XX_MAX = !XX!
				if !YY! GTR !YY_MAX! SET /A YY_MAX = !YY!
				if !XX! LSS !XX_MIN! SET /A XX_MIN = !XX!
				if !YY! LSS !YY_MIN! SET /A YY_MIN = !YY!
			)
			for /f "tokens=2" %%a in ("%%R") do (
				set OCTANT=%%a
			)

		)
		ECHO RANGE:
		ECHO X=!XX_MIN! TO !XX_MAX!
		ECHO Y=!YY_MIN! TO !YY_MAX!
		FOR /L %%X IN (!XX_MIN!,1,!XX_MAX!) DO (
			FOR /L %%Y IN (!YY_MIN!,1,!YY_MAX!) DO (
				REM ECHO X=%%X Y=%%Y
				ECHO X=%%X Y=%%Y !OCTANT! %%F>>OBJECT_ARRAY_RANGE.TXT
			)
		)
	)
)

exit /b
