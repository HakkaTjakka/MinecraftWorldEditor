@echo off
SET PATH=%CD%\FFMPEG\BIN;%CD%\PACMAN_CUBERITE\BIN;%PATH%
CD PACMAN_CUBERITE
echo 13 > level.txt
rem PACMAN.BAT mceditor 1 -30 -5
rem PACMAN.BAT mceditor 1 -30 5
rem PACMAN.BAT mceditor 1 40 -5

rem PACMAN.EXE mceditor 1 46 5

rem PACMAN.EXE mceditor 1 70 -8

rem PACMAN.EXE mceditor 1 65 -8

rem PACMAN.EXE mceditor 1 75 6

rem PACMAN.BAT mceditor 1 37 5

PACMAN.EXE mceditor 9 190 0 4
rem PACMAN.EXE regions 9

CD ..
pause