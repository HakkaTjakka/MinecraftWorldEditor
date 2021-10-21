@echo off
setlocal EnableExtensions EnableDelayedExpansion
rem if exist HOLLAND.TXT DEL HOLLAND.TXT
for /f "tokens=*" %%P in (HOLLAND_LAT_LON_LARGER.TXT) do (
	for /f "tokens=1,2 delims=='='" %%a in ("%%P") do (
		set "l=%%b"
		set "dir=!l:~0,10!"
		set "octant=!l:~0,17!"
		if not !octant! == 00000000000000000 echo %%a=!octant!>>HOLLAND_!dir!.TXT
		rem echo %%a %%b>> HOLLAND.TXT
		
	)
)

pause
exit /b
