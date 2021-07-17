@echo off
setlocal EnableDelayedExpansion
if not exist obj mkdir obj
set /A total_dirs=0
set /A ready_to_move=0
set /A only_nbt=0
set /A only_obj=0
set /A errors=0
set /A total_OBJ_NBT=0
for /f "tokens=*" %%F in ('dir /b /a:d ".\3*"') do (
	set /A dirs=0
	for /f "tokens=*" %%G in ('dir /b /a:d "%%F\*"') do (
		set /A dirs=!dirs! + 1
		set "l=%%G"
		if exist "%%F\%%G\!l:~0,17!.obj" (
			set /A total_OBJ_NBT=!total_OBJ_NBT! + 1
			if exist "%%F\%%G\!l:~0,17!.nbt" (
				REM echo "%%F\%%G\ nbt and obj found, BUT NOT moving..."
				set /A ready_to_move=!ready_to_move! + 1
				REM move "%%F\%%G\!l:~0,17!.obj" obj >NUL
			) else (
				set /A only_obj=!only_obj! + 1
				REM echo "%%F\%%G\!l:~0,17!.obj found"
			)
		) else (
			if exist "%%F\%%G\!l:~0,17!.nbt" (
				set /A total_OBJ_NBT=!total_OBJ_NBT! + 1
				set /A only_nbt=!only_nbt! + 1
				REM echo "%%F\%%G\!l:~0,17!.nbt found"
			) else (
				set /A errors=!errors! + 1
				echo "%%F\%%G\ FOUND NO NBT AND NO OBJ!!!"
			)
		)
		REM echo "%%F\%%G\!l:~0,17!"
	)
	set /A total_dirs=!total_dirs! + !dirs!
	echo Directory=%%F	dirs=!dirs!	total_dirs=!total_dirs!/!total_OBJ_NBT!	ready_to_move=!ready_to_move!	only_obj=!only_obj!	only_nbt=!only_nbt!	errors=!errors!
)
pause

