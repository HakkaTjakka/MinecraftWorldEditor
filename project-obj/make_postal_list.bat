@echo off

setlocal EnableExtensions EnableDelayedExpansion

if exist lat_lon.lst del lat_lon.lst

IF NOT EXIST functions MKDIR functions
for /f "tokens=1,2,3,4,5,6,7,8,9,10 delims=='|'" %%a in (NL_full.txt) do (
 	for /f "tokens=1,2 delims== " %%P in ("%%b") do (
 		if not exist functions\%%P mkdir functions\%%P
		if %%c == %%f (
			echo %%P*%%Q*%%i*%%h*%%f ^(%%d^) ^(%%i,%%h^)
			echo %%P*%%Q*%%i*%%h*%%f ^(%%d^) ^(%%i,%%h^)>> lat_lon.lst
		) else (
			echo %%P*%%Q*%%i*%%h*%%f ^(%%c, %%d^) ^(%%i,%%h^)
			echo %%P*%%Q*%%i*%%h*%%f ^(%%c, %%d^) ^(%%i,%%h^)>> lat_lon.lst
		)
 	)
	
rem NL|1011 AW|Amsterdam|Noord-Holland|07|Amsterdam|0363|||52.373|4.907|
	
)
