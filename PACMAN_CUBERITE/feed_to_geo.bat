@ECHO OFF

:BEGIN

rem if not exist input_to_geo.txt (
rem 	timeout 1 > nul
rem 	goto :BEGIN
rem )
rem timeout 1 > nul
rem 
rem for /f "tokens=*" %%G in (input_to_geo.txt) do (
rem 	ECHO %%G
rem )
rem del input_to_geo.txt
rem 
rem goto :BEGIN

set /p id=""
echo %id%
goto :begin
