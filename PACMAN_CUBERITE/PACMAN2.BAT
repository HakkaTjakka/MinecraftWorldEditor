@echo off
d:
cd \pacman\pacman_cuberite
set PATH=%CD%\BIN;%CD%\..\FFMPEG\BIN;%PATH%;
PACMAN.EXE %*
pause
exit

