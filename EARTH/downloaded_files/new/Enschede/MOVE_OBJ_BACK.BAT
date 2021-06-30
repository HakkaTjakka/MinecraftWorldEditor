@echo off
setlocal enabledelayedexpansion
for /D %%a in (%CD%\3*) do (
rem	echo %%a
	for /D %%b in (%%a\*) do (
rem	echo %%b
		set "l=%%~nb"
		set "result=!l:~0,17!"

		if exist "obj\!result!.obj" (
			move "obj\!result!.obj" %%b
		)
	)
)
pause

