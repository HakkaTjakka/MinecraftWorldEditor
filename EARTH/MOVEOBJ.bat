@echo off
mkdir obj
for /f "tokens=*" %%G in ('dir /b /a:d ".\*"') do (
	for %%a in (%%G\*.obj) do (
		move %%a obj
	)
)
pause

