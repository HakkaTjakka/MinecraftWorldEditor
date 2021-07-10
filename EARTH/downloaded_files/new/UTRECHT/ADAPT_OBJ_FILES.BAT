@echo off
echo Adapting obj\*.obj to out\*.obj
echo Are you sure, don't repeat converting with ADAPT_OBJ_FILES.BAT files when already done
echo Press control break to quit....
pause
setlocal enabledelayedexpansion
if not exist out mkdir out
for /D %%a in (%CD%\3*) do (
	for /D %%b in (%%a\*) do (
		set "l=%%~nb"
		set "result=!l:~0,17!"

		if exist "out\!result!.obj" (
			echo "out\!result!.obj" exists, skipping
		) else (
			if exist "%%b\!result!.obj" (
				echo %%b\!result!.obj exists, converting to out\!result!.obj
				project_obj.exe %%b\!result!.obj out\!result!.obj
			) else (
				echo %%b\!result!.obj does not exist, skipping
			)
		)
	)
)
pause

