@echo off
setlocal enabledelayedexpansion
for /f "tokens=*" %%G in ('dir /b /a:d ".\*-21"') do (
    set "l=%%G"
	set "result=!l:~0,14!"
	if not exist "!result!" (
		mkdir "!result!" 2>nul
		if not errorlevel 1 (
rem			echo !result!
		)
	)
	move %%G !result!
)

