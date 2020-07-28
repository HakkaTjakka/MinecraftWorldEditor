@echo off
for /f "tokens=*" %%G in ('dir /b "nbt\*.nbt"') do (
		move nbt\%%G %%~nG-21
)
pause

