@ECHO OFF
setlocal EnableExtensions EnableDelayedExpansion

set "l=%1"
set "dir=HOLLAND_!l:~0,10!.TXT"

type F:\PACMAN\EARTH\!dir! | find "=%1" > F:\PACMAN\EARTH\NEW_OCTANT.TXT
rem type F:\PACMAN\EARTH\UTRECHT_LAT_LONG_CENTER2.TXT | find "=%1" > F:\PACMAN\EARTH\NEW_OCTANT.TXT
type F:\PACMAN\EARTH\NEW_OCTANT.TXT >> F:\PACMAN\EARTH\NEW_OCTANTS.TXT

for %%X in (F:\PACMAN\EARTH\NEW_OCTANT.TXT) do (
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
				ECHO X=!var_x! Y=!var_y! OCTANT=%1
			)
		)
	)
)

