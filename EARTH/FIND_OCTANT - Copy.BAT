@ECHO OFF
type F:\PACMAN\EARTH\UTRECHT_LAT_LONG_CENTER.TXT | find "=%1" > F:\PACMAN\EARTH\NEW_OCTANT2.TXT
type F:\PACMAN\EARTH\NEW_OCTANT2.TXT >> F:\PACMAN\EARTH\NEW_OCTANTS2.TXT


for %%X in (F:\PACMAN\EARTH\NEW_OCTANT2.TXT) do (
	REM echo %%X
	if not %%~zX == 0 (
		for /f "tokens=*" %%R in (%%X) do (
			REM echo %%R
			for /f "tokens=2,3 delims==[]" %%a in ("%%R") do (
				set "l=%%a"
				set var_x=!l: =!
				set "l=%%b"
				set "var_y=!l: =!
				ECHO X=!var_x! Y=!var_y!>> F:\PACMAN\EARTH\OBJECT_ARRAY3.TXT
				ECHO X=!var_x! Y=!var_y! OCTANT=%1
			)
		)
	)
)

