@echo off
echo Moving files from out back 
echo Are you sure, don't repeat converting with ADAPT_OBJ_FILES.BAT files when already done
echo Press control break to quit....
pause
setlocal enabledelayedexpansion
for /D %%a in (%CD%\3*) do (
rem	echo %%a
	for /D %%b in (%%a\*) do (
rem	echo %%b
		set "l=%%~nb"
		set "result=!l:~0,17!"

		if exist "out\!result!.obj" (
			move "out\!result!.obj" %%b
		)
	)
)
pause

