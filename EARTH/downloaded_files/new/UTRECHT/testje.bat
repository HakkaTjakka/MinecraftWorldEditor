@echo off
setlocal EnableDelayedExpansion

set /A next=%1 + 1

echo %1

time /t 

timeout 5

start cmd /c testje.bat !next!

timeout 5

exit /b



