@echo off
for /f "tokens=*" %%G in ('dir /b /a:d ".\*"') do (
	dir %%G\*.bmp /s/b > png_and_bmp.txt 2>NUL
	dir %%G\*.png /s/b >> png_and_bmp.txt 2>NUL

	for %%a in (png_and_bmp.txt) do (
		if not %%~za == 0 (
			echo Converting to .jpg %%G
			"C:\Program Files\IrfanView\i_view64.exe" /filelist=png_and_bmp.txt /convert=%%G\$d\$N.jpg
			del %%G\*.png /s >NUL 2>NUL 
			del %%G\*.bmp /s >NUL 2>NUL
			echo Converting .mtl %%G
			bash -c "./convert_to_jpg_mtl_files.sh %%~nG" 2>NUL
		) else (
			echo No .bmp or .png files %%G
		)
	)
)
rem for /f "tokens=*" %%G in ('dir /b /a:d ".\*"') do (
rem	for %%a in (%%G\*.mtl) do (
rem	 	echo Converting .mtl %%G
rem 		bash -c "./convert_to_jpg_mtl_files.sh %%~nG" 2>NUL
rem	 )
rem )
rem for /f "tokens=*" %%G in ('dir /b /a:d ".\*"') do (
rem 	for %%a in (%%G\*.obj) do (
rem 		echo Compacting .obj %%G
rem 		compact /c %%a >NUL 2>NUL 
rem 	)
rem )
pause

