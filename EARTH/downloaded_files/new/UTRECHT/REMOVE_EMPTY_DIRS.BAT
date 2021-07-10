@echo off
setlocal EnableDelayedExpansion
if not exist obj mkdir obj
set /A dirs=0
set /A total_dirs=0
set /A ready_to_move=0
set /A only_nbt=0
set /A only_obj=0
set /A errors=0
for /f "tokens=*" %%F in ('dir /b /a:d ".\3*"') do (
	set /A dirs=0
	for /f "tokens=*" %%G in ('dir /b /a:d "%%F\*"') do (
		set "l=%%G"
		if not exist "%%F\%%G\!l:~0,17!.obj" (
			if not exist "%%F\%%G\!l:~0,17!.nbt" (
				set /A errors=!errors! + 1
				echo "%%F\%%G\ NO OBJ NO NBT!!!!"
				rmdir %%F\%%G /S /Q
				REM pause
			) else (
				echo "%%F\%%G\!l:~0,17!.nbt found"
			)
		) else (
			echo "%%F\%%G\!l:~0,17!.obj found"
		)
rem 		if not exist "%%F\%%G\*.*" (
rem 			set /A dirs=!dirs! + 1
rem 			dir "%%F\%%G\*.*"
rem 			pause
rem 		)
	)
	echo Directory=%%F	empty dirs=!dirs!
)
pause

