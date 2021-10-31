@echo off

:BEGIN

echo MONITOR WAITING FOR geo_ready.txt

:AGAIN

TIMEOUT 1

if not exist geo_ready.txt goto :AGAIN

if exist result.txt (
	echo RESULT READY:
rem TIMEOUT 3
	type result.txt
	type result.txt>> GEO_LIST.TXT
rem	TIMEOUT 3
	del result.txt
	del geo_ready.txt
	echo ready> geo_continue.txt
)
echo AGAIN AGAIN!
echo.
goto :BEGIN
