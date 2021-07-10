@echo off
setlocal EnableDelayedExpansion
if not exist obj mkdir obj
set /A dirs=0
set /A deleted=0
for /f "tokens=*" %%F in ('dir /b /a:d ".\3*"') do (
	set /A dirs=0
	for /f "tokens=*" %%G in ('dir /b /a:d "%%F\*"') do (
		set /A dirs=!dirs! + 1
		set "l=%%G"
		if exist "%%F\%%G\!l:~0,17!.DOT" (
			DEL "%%F\%%G\!l:~0,17!.dot"
			set /A deleted=!deleted! + 1
		)
	)
	echo Directory=%%F	dirs=!dirs! deleted=!deleted!
)
pause

