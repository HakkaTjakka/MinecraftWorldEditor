@echo off
echo RANDOM=ON> list.txt
rem dir /b /s /a-d files\*.txt >> list.txt
dir /b /s /a-d files\*.rnd >> list.txt
