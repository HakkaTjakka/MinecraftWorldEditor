@echo off

setlocal EnableExtensions EnableDelayedExpansion

if exist lat_lon.lst del lat_lon.lst

for /f "tokens=1,2,3,4,5,6,7,8,9,10 delims=='|'" %%a in (NL_full.txt) do (
	rem echo %%b
REM  	for /f "tokens=1" %%R in ("%%b") do (
REM 		rem echo R=%%R
REM  		set /a now=%%R / 100
REM  	)
	set now=%%g
 	if not !last! == !now! (
 		echo %%a %%b %%c %%d %%e %%f %%g %%h %%i %%j
 		rem echo %%a %%b %%c %%d %%e %%f %%g %%h %%i %%j >> lat_lon.lst
 		echo %%h	%%i	%%g	%%c>> lat_lon.lst
		set last=%%g
 	)
REM  	for /f "tokens=1" %%R in ("%%b") do (
REM  		set /a last=%%R / 100
REM  	)
)

pause
