@echo off
setlocal EnableDelayedExpansion
set /A number_obj = 0
set /A number_nbt = 0
for /D %%a in (%CD%\3*) do (
rem	echo %%a
	for /D %%b in (%%a\*) do (
rem		echo %%b
		for %%c in (%%b\*.OBJ) do (
			set /a number_obj = !number_obj! + 1
			echo !number_obj! %%c
		)
		for %%c in (%%b\*.NBT) do (
			set /a number_nbt = !number_nbt! + 1
			echo !number_nbt! %%c
		)
	)
)
echo Number of .obj files = !number_obj!
echo Number of .nbt files = !number_nbt!

pause

