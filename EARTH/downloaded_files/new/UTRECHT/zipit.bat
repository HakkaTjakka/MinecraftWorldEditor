@echo off
for /D %%a in (%CD%\3*) do (
	echo %%a
	call "c:\Program Files\WinRAR\winrar.exe" -v100m -m0 a -r %%a.exe %%~nxa

)
pause

