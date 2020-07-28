@echo off
del Test.copy\region\*.* /Q
copy test\region\*.* Test.copy\region
pause
