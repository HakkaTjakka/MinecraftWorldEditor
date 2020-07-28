@echo off
for /f "tokens=*" %%G in ('dir /b /a:d "..\obj\*."') do (
	echo ..\obj\%%G
	move "..\obj\%%G" . >NUL
)
pause

