@echo off

rem F:
rem CD \PACMAN\EARTH\DOWNLOADED_FILES\OBJ
rem start cmd /c DONNER.BAT
rem TIMEOUT 5
rem 
rem F:
rem CD \PACMAN\EARTH\DOWNLOADED_FILES\NEW\UTRECHT
rem start cmd /c JOJO.BAT
rem TIMEOUT 5
rem

rem F:
rem CD \PACMAN\EARTH
rem start cmd /c DUMP_CENTER_HOLLAND.BAT
rem TIMEOUT 5

rem G:
rem start cmd /c "MIRROR TO GOOGLE DRIVE.BAT"
rem CD \sample-utrecht-from
rem TIMEOUT 5

E: 
CD \
call MIRROR_D_SAVES_TEST_TO_SAVES_TEST.bat
CD \PACMAN\PACMAN_CUBERITE
start cmd /c bin\pacman.exe plot
TIMEOUT 5

D:
CD \PACMAN\PACMAN_CUBERITE
start cmd /c bin\pacman.exe holland fast
TIMEOUT 5

G:
CD \sample-utrecht-from
start cmd /c PUSH_REPO.BAT
TIMEOUT 5


pause

rem exit /b


