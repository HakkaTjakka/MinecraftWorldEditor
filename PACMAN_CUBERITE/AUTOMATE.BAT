@echo off
call \saves\reset_test.bat
bin\pacman.exe mceditor
call \saves\copy_test.bat
echo ready
timeout 10