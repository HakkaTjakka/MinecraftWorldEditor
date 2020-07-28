@ECHO OFF
call /saves/reset_test.bat
echo "If this file exists pacman mceditor [1|2] stops after processing one file." > stop.txt
echo 13 > level.txt
PACMAN.EXE mceditor
echo 13 > level.txt
PACMAN.EXE mceditor 1
echo 14 > level.txt
PACMAN.EXE mceditor 2
call /saves/copy_test.bat
echo *******************************************************************************************************************************
echo *******************************************************************************************************************************
echo *******************************************************************************************************************************
pause

