@echo off
for /f "tokens=*" %%G in ('dir /b /a:d ".\*"') do (
	echo Converting to .jpg %%G
	dir %%G\*.bmp /s/b > png_and_bmp.txt 2>NUL
	dir %%G\*.png /s/b >> png_and_bmp.txt 2>NUL

	for %%a in (png_and_bmp.txt) do (
		if not %%~za == 0 (
			"C:\Program Files\IrfanView\i_view64.exe" /filelist=png_and_bmp.txt /convert=$d\$N.jpg
			del %%G\*.png /s >NUL 2>NUL 
			del %%G\*.bmp /s >NUL 2>NUL
		)
	)
	bash -c "./convert_to_jpg_mtl_files.sh %%~nG" 2>NUL
	for %%a in (%%G\*.obj) do (
		compact /c %%a >NUL 2>NUL 
	)
)
pause

