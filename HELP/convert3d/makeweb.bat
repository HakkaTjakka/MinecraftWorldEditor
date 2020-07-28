@echo off

if not exist "archive" mkdir archive

dir /b /s /a-d *.3ds *.obj > 3dslist.txt

(
 	echo ^<!DOCTYPE html^>
 	echo ^<html^>
 	echo ^<body^>
 	echo.  
 	echo ^<h2^>HTML Links^</h2^>
 	echo ^<style^>
 	echo p { 
 	echo   line-height: 1px;
 	echo }
 	echo ^</style^>
) > list.html


SETLOCAL EnableDelayedExpansion

for /F "usebackq tokens=*" %%A in ("3dslist.txt") do (
	set "_fullpath=%%~fA"
	set "_dirpath=%%~pA"
	set "_drive=%%~dA"
	set "_filename=%%~nA"
	set "_fileextension=%%~xA"
	set "_subpath=!_drive!!_dirpath!!_filename!"
	set "_subpath=!_subpath:%CD%\=!"
	set "_html_filename=!_subpath!!_fileextension!.html"
	set "_html_filename=!_html_filename:\=_!"
rem	echo !_subpath!
rem	echo !_filepath!!_filename!!_fileextension!
	set "_string=!_subpath:\=/!"
rem 	set "_string=%%A"
rem 	SET "_string=!_string:%CD%\=!"
rem 	set "_string=!_string:\=/!"
	if "!_fileextension!" == ".3ds" (
		echo.!_string!.3ds ^<--^> archive/!_html_filename!
		echo ^<p^>^<a href="archive/!_html_filename!"^>!_string!.3ds^</a^>^</p^> >> list.html
		(
			type fullscreen_a.html 
			echo|set /p="../!_string!.3ds"
			type fullscreen_b.html 
		) > archive/!_html_filename!
	) else if "!_fileextension!" == ".obj" (
		echo.!_string!.obj ^<--^> archive/!_html_filename!
		echo ^<p^>^<a href="archive/!_html_filename!"^>!_string!.obj^</a^>^</p^> >> list.html
		(
			type fullscreen_a.html 
			echo|set /p="../!_string!.obj^|../!_string!.mtl"
			type fullscreen_b.html 
		) > archive/!_html_filename!
	)

)	

(
	echo ^</body^>
	echo ^</html^>
) >> list.html




pause
