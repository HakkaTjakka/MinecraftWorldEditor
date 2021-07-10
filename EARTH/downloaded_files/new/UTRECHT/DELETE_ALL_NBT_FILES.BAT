@echo off
echo Deleting all *.nbt files
echo Press control break to quit....
pause
setlocal enabledelayedexpansion
if not exist out mkdir out
for /D %%a in (%CD%\3*) do (
	for /D %%b in (%%a\*) do (
		set "l=%%~nb"
		set "result=!l:~0,17!"

			if exist "%%b\!result!.nbt" (
				echo %%b\!result!.nbt exists, DELETING
				del "%%b\!result!.nbt"
			) else (
				echo %%b\!result!.nbt does not exist, skipping
			)
		)
	)
)
pause

