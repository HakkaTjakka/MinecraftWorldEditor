@echo off
d:
cd \pacman\pacman_cuberite
set PATH=%CD%\BIN;%CD%\..\FFMPEG\BIN;%PATH%;
BIN\PACMAN.EXE %*
exit

