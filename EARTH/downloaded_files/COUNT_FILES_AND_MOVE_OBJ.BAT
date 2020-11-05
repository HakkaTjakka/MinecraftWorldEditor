@echo off
if not exist obj mkdir obj
if exist LEFTOVER.TXT DEL LEFTOVER.TXT
if exist EMPTY.TXT DEL EMPTY.TXT
if exist EMPTY_DIR.TXT DEL EMPTY_DIR.TXT
if exist NOOBJ.TXT DEL NOOBJ.TXT
setlocal EnableDelayedExpansion
set /A number_obj = 0
set /A number_nbt = 0
set /A number_moved = 0
set /A number_todo = 0
set /A number_dirs = 0
for /D %%a in (%CD%\03*) do (
rem	echo %%a
	set /A number_dirs_in_dir = 0
	for /D %%b in (%%a\*) do (
rem		echo %%b
		set /a number_dirs = !number_dirs! + 1
		set /a number_dirs_in_dir = !number_dirs_in_dir! + 1
		for %%c in (%%b\*.OBJ) do (
			set /a number_obj = !number_obj! + 1
			echo !number_obj! %%c
		)
		for %%c in (%%b\*.NBT) do (
			set /a number_nbt = !number_nbt! + 1
			echo !number_nbt! %%c
		)
		if exist "%%b\*.obj" (
			if exist "%%b\*.nbt" (
				if not exist "obj" mkdir obj
				for %%c in (%%b\*.OBJ) do (
					set /a number_moved = !number_moved! + 1
					echo !number_moved! MOVING TO OBJ %%c
 					move "%%c" obj >NUL
				)
			) else (
				for %%c in (%%b\*.OBJ) do (
					set /a number_todo = !number_todo! + 1
					echo TO DO: !number_todo! %%c
					echo TO DO: !number_todo! %%c >> LEFTOVER.TXT
					
				)
			)
		) else (
			if not exist "%%b\*.nbt" (
				echo EMPTY: !number_todo! %%b >> EMPTY.TXT
			) 
			echo NO OBJ: !number_todo! %%b >> NOOBJ.TXT
		)
	)
	if !number_dirs_in_dir! EQU 0 (
		echo EMPTY DIR: !number_todo! %%a >> EMPTY_DIR.TXT
	)
)
echo Number of directories           = !number_dirs!
echo Number of .obj files            = !number_obj!
echo Number of .nbt files            = !number_nbt!
echo Number of .obj files moved      = !number_moved!
echo Number of .obj files to be done = !number_todo!

pause

