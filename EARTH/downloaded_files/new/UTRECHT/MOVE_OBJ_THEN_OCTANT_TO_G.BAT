@echo off
setlocal EnableExtensions EnableDelayedExpansion
if not exist obj mkdir obj
set /A total_dirs=0
for /f "tokens=*" %%F in ('dir /b /a:d ".\3*"') do (
	set /A dirs=0
	for /f "tokens=*" %%G in ('dir /b /a:d "%%F\*"') do (
		set /A dirs=!dirs! + 1
		set "l=%%G"
		if exist "%%F\%%G\!l:~0,17!.obj" (
			if exist "%%F\%%G\!l:~0,17!.nbt" (
				echo "%%F\%%G\ nbt and obj found, moving..."
				move "%%F\%%G\!l:~0,17!.obj" obj >NUL

				if not exist G:\PACMAN\EARTH\DOWNLOADED_FILES\NEW\UTRECHT\%%F mkdir G:\PACMAN\EARTH\DOWNLOADED_FILES\NEW\UTRECHT\%%F
				if not exist G:\PACMAN\EARTH\DOWNLOADED_FILES\NEW\UTRECHT\%%F\%%G mkdir G:\PACMAN\EARTH\DOWNLOADED_FILES\NEW\UTRECHT\%%F\%%G
				echo Copying       %%F\%%G G:\PACMAN\EARTH\DOWNLOADED_FILES\NEW\UTRECHT\%%F
				REM copy %%F\%%G\*.* G:\PACMAN\EARTH\DOWNLOADED_FILES\NEW\UTRECHT\%%F\%%G
				copy %%F\%%G\*.* G:\PACMAN\EARTH\DOWNLOADED_FILES\NEW\UTRECHT\%%F\%%G >NUL
				echo Deleting      %%F\%%G
				rmdir %%F\%%G /S /Q
			) else (
				echo "%%F\%%G\!l:~0,17!.obj found"
 				set "l=%%G"
 				set "result=!l:~0,17!"
 				call F:\PACMAN\EARTH\FIND_OCTANT.BAT !result!
			)
		) else (
			if exist "%%F\%%G\!l:~0,17!.nbt" (
				if not exist G:\PACMAN\EARTH\DOWNLOADED_FILES\NEW\UTRECHT\%%F mkdir G:\PACMAN\EARTH\DOWNLOADED_FILES\NEW\UTRECHT\%%F
				if not exist G:\PACMAN\EARTH\DOWNLOADED_FILES\NEW\UTRECHT\%%F\%%G mkdir G:\PACMAN\EARTH\DOWNLOADED_FILES\NEW\UTRECHT\%%F\%%G
				echo Copying       %%F\%%G G:\PACMAN\EARTH\DOWNLOADED_FILES\NEW\UTRECHT\%%F
				REM copy %%F\%%G\*.* G:\PACMAN\EARTH\DOWNLOADED_FILES\NEW\UTRECHT\%%F\%%G
				copy %%F\%%G\*.* G:\PACMAN\EARTH\DOWNLOADED_FILES\NEW\UTRECHT\%%F\%%G >NUL
				echo Deleting      %%F\%%G
				rmdir %%F\%%G /S /Q
				REM echo "%%F\%%G\!l:~0,17!.nbt found"
			) else (
				echo "%%F\%%G\ FOUND NO NBT AND NO OBJ!!!"
			)
		)
		REM echo "%%F\%%G\!l:~0,17!"
	)
	rmdir %%F /Q 2>nul
	set /A total_dirs=!total_dirs! + !dirs!
	echo Directory=%%F	dirs=!dirs!		total_dirs=!total_dirs!
)
timeout 10
