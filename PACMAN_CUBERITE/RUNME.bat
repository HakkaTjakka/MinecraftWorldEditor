@ECHO OFF
ECHO did you run install_saves.bat? (see ..)

timeout 20

echo 13 > level.txt
start cmd /k PACMAN2.BAT mceditor

timeout 200

:START

echo 13 > level.txt
PACMAN.EXE mceditor 1

timeout 10

echo 13 > level.txt
PACMAN.EXE mceditor 2

timeout 600

GOTO START
