@echo off

setlocal EnableDelayedExpansion

set /A number_y = 0

:X_IS_0

set /A number_x = 0

:NEXT_X

set filename=r.!number_x!.!number_y!.png

rem echo !filename!

if not exist !filename! (
	copy source.png !filename! >NUL 2>NUL
	echo copying !filename!
)

set /a number_x = !number_x! + 1

if !number_x! GTR 139 (
	set /a number_y = !number_y! + 1
	if !number_y! equ 120 goto END
	goto X_IS_0
)

goto NEXT_X

:END

pause