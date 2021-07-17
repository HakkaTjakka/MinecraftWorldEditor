@echo off
setlocal EnableDelayedExpansion
if not exist obj mkdir obj
set /A total_dirs=0
set /A total_deleted=0
for /f "tokens=*" %%F in ('dir /b /a:d ".\3*"') do (
	set /A dirs=0
	for /f "tokens=*" %%G in ('dir /b /a:d "%%F\*"') do (
		if exist %%F\%%G\checked_ok.txt (
			DEL %%F\%%G\checked_ok.txt
			set /A total_deleted=!total_deleted! + 1
		)
		set /A total_dirs=!total_dirs! + 1
	)
	echo Directory=%%F	dirs=!total_dirs! 	deleted=!total_deleted!
)
pause

