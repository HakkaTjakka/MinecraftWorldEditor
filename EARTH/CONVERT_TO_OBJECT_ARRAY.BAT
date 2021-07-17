@ECHO OFF

setlocal EnableExtensions EnableDelayedExpansion

if exist F:\PACMAN\EARTH\OBJECT_ARRAY.TXT del F:\PACMAN\EARTH\OBJECT_ARRAY.TXT

for %%X in (F:\PACMAN\EARTH\NEW_OCTANTS.TXT) do (
	REM echo %%X
	if not %%~zX == 0 (
		for /f "tokens=*" %%R in (%%X) do (
			REM echo %%R
			for /f "tokens=2,3 delims==[]" %%a in ("%%R") do (
				set "l=%%a"
				set var_x=!l: =!
				set "l=%%b"
				set "var_y=!l: =!
				ECHO X=!var_x! Y=!var_y!>> F:\PACMAN\EARTH\OBJECT_ARRAY.TXT
				ECHO X=!var_x! Y=!var_y!
			)
		)
	)
)

PAUSE