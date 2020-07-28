@echo off
set startdir=%~dp0
set bashdir="C:\Program Files\Git\bin\bash.exe"
rem %bashdir% --login -i -c "echo %*"
%bashdir% --login -i -c grep -iR "%*" ./
pause