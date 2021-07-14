@echo off
setlocal ENABLEDELAYEDEXPANSION
set /A num_converted_total=0
for /f "tokens=*" %%F in ('dir /b /a:d ".\*"') do (
	echo Directory: %%F
	for /f "tokens=*" %%G in ('dir /b /a:d "%%F\*"') do (
		dir %%F\%%G\*.bmp /s/b > png_and_bmp.txt 2>NUL
		dir %%F\%%G\*.png /s/b >> png_and_bmp.txt 2>NUL
		echo here > goingin.txt
		set /A num_converted=0
		for %%a in (png_and_bmp.txt) do (
			if exist goingin.txt (
				del goingin.txt 2>NUL
				if not %%~za == 0 (
					"C:\Program Files\IrfanView\i_view64.exe" /filelist=png_and_bmp.txt /convert=%%F\$d\$N.jpg
					del %%F\%%G\*.png /s >NUL 2>NUL 
					del %%F\%%G\*.bmp /s >NUL 2>NUL
					bash -c "./convert_to_jpg_mtl_files.sh %%F/%%G" 2>NUL
				)
			)
			if not %%~za == 0 set /A num_converted=!num_converted! + 1
		)
		rem if not exist goingin.txt bash -c "./convert_to_jpg_mtl_files.sh %%~nG" 2>NUL
		
		set /A num_converted_total=!num_converted_total! + !num_converted!
	
		echo          Converting to .jpg %%F\%%G :	!num_converted!	total dirs=!num_converted_total!
	
	)
)
pause

