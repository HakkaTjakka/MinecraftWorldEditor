@echo off
setlocal enabledelayedexpansion
REM if not exist out2 mkdir out2

for /f "tokens=*" %%F in (FIX.TXT) do (
	set "l=%%~nF"
	set "result=!l:~0,17!"
	set "result2=!l:~0,14!"

	if exist "!result2!\!result!-21\%%F.NBT" (
		ECHO EXIST:     "!result2!\!result!-21"
		dir "!result2!\!result!-21"
	) else (
		ECHO NOT EXIST: "!result2!\!result!-21"
		dir "!result2!\!result!-21"
	)

	REM if exist "!result2!\!result!-21\%%~nF.obj" move "!result2!\!result!-21\%%~nF.obj" out2
	REM move "backup_obj_test\%%~nF.obj" "!result2!\!result!-21"
)
pause