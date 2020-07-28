@echo off
mkdir obj >NUL 2>NUL
for /D %%a in (%CD%\3*) do (
	echo %%a
	for /D %%b in (%%a\*) do (
rem		echo %%b
		for %%c in (%%b\*.obj) do (
			echo %%c
			move %%c obj >NUL
		)
	)
)
pause

