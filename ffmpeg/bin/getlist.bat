@echo off
SET PATH=%CD%\FFMPEG\BIN;%PATH%
cd /pacman/convert

youtube-dl -i --skip-unavailable-fragments --geo-bypass --get-id --get-format --get-filename --get-duration "%*" 

rem insert this before all lines in 
rem https://www.youtube.com/watch?v=