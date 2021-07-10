@echo off
if not exist obj mkdir obj
setlocal EnableDelayedExpansion
set /A number_obj = 0
set /A number_nbt = 0
set /A number_moved = 0
set /A number_todo = 0
set /A number_dirs = 0
for /D %%a in (%CD%\3*) do (
rem	echo %%a
	for /D %%b in (%%a\*) do (
rem		echo %%b
		set /a number_dirs = !number_dirs! + 1
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
				)
			)
		)
	)
)
echo Number of directories           = !number_dirs!
echo Number of .obj files            = !number_obj!
echo Number of .nbt files            = !number_nbt!
echo Number of .obj files moved      = !number_moved!
echo Number of .obj files to be done = !number_todo!

pause

