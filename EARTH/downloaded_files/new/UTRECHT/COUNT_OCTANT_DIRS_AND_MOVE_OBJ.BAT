@echo off
setlocal EnableDelayedExpansion
if not exist obj mkdir obj
set /A total_dirs=0
for /f "tokens=*" %%F in ('dir /b /a:d ".\3*"') do (
	set /A dirs=0
	for /f "tokens=*" %%G in ('dir /b /a:d "%%F\*"') do (
		set /A dirs=!dirs! + 1
		set "l=%%G"
		if exist "%%F\%%G\!l:~0,17!.obj" (
			if exist "%%F\%%G\!l:~0,17!.nbt" (
				echo "%%F\%%G\ nbt and obj found, moving..."
				move "%%F\%%G\!l:~0,17!.obj" obj >NUL
			) else (
				REM echo "%%F\%%G\!l:~0,17!.obj found"
			)
		) else (
			if exist "%%F\%%G\!l:~0,17!.nbt" (
				REM echo "%%F\%%G\!l:~0,17!.nbt found"
			) else (
				echo "%%F\%%G\ FOUND NO NBT AND NO OBJ!!!"
			)
		)
		REM echo "%%F\%%G\!l:~0,17!"
	)
	set /A total_dirs=!total_dirs! + !dirs!
	echo Directory=%%F	dirs=!dirs!		total_dirs=!total_dirs!
)
pause

