@ECHO OFF

setlocal EnableExtensions EnableDelayedExpansion

:AGAIN

dir *-21 /b > list.txt

timeout 600

for %%X in (list.txt) do (
	for /f "tokens=*" %%R in (%%X) do (
		IF EXIST %%R MOVE %%R .\doneA\
REM		PAUSE
	)
)
cd doneA
call divide.bat
call CHECK_FOR_ALL_TEXTURES.BAT
cd ..

rem dir *-21 /b > list.txt
rem 
rem timeout 240
rem 
rem for %%X in (list.txt) do (
rem 	for /f "tokens=*" %%R in (%%X) do (
rem 		IF EXIST %%R MOVE %%R .\doneB\
rem REM 		PAUSE
rem 	)
rem )
rem cd doneB
rem call divide.bat
rem call CHECK_FOR_ALL_TEXTURES.BAT
rem cd ..

REM dir *-21 /b > list.txt

REM cd \pacman\earth\downloaded_files\new\utrecht
REM 
REM call jojo.bat
REM 
REM cd \pacman\earth\downloaded_files\obj

goto :AGAIN



