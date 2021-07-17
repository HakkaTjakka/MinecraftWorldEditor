@ECHO OFF

setlocal EnableExtensions EnableDelayedExpansion

:AGAIN

dir *-21 /b > list.txt

timeout 240

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

dir *-21 /b > list.txt

timeout 240

for %%X in (list.txt) do (
	for /f "tokens=*" %%R in (%%X) do (
		IF EXIST %%R MOVE %%R .\doneB\
REM 		PAUSE
	)
)
cd doneB
call divide.bat
call CHECK_FOR_ALL_TEXTURES.BAT
cd ..

goto :AGAIN



