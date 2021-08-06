@ECHO OFF

setlocal EnableExtensions EnableDelayedExpansion

dir *-21 /b > list.txt

:AGAIN

timeout 300

set "nothing=YES"
for %%X in (list.txt) do (
	for /f "tokens=*" %%R in (%%X) do (
		set "nothing=NO"
		IF EXIST %%R MOVE %%R .\doneA\
	)
)

if "!nothing!" == "YES" (
	dir *-21 /b > list.txt
	timeout 300
) else (
	dir *-21 /b > list.txt
	cd doneA
	call divide.bat
	call CHECK_FOR_ALL_TEXTURES.BAT
	cd ..
)

goto :AGAIN



