@ECHO OFF
if exist show.txt del show.txt

:NEXT
set /p INPUT=Input?
echo %INPUT%>>show.txt
timeout 1 >nul
GOTO :NEXT
