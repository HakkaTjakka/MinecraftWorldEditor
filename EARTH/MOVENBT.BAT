@echo off
mkdir nbt
for /f "tokens=*" %%G in ('dir /b /a:d ".\*"') do (
	for %%a in (%%G\*.nbt) do (
		move %%a nbt
	)
)
pause

