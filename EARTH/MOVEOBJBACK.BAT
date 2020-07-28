@echo off
for /f "tokens=*" %%G in ('dir /b "obj\*.obj"') do (
		move obj\%%G %%~nG-21
)
pause

