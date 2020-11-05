@echo off
setlocal EnableDelayedExpansion
set /A number_bmp = 0
set /A number_jpg = 0
set /A number_png = 0
set /A number_bmp_tot = 0
set /A number_jpg_tot = 0
set /A number_png_tot = 0
set /A number_bmp_tot2 = 0
set /A number_jpg_tot2 = 0
set /A number_png_tot2 = 0
set /A number_dirs = 0
for /D %%a in (%CD%\3*) do (
	set /A number_bmp_tot = 0
	set /A number_jpg_tot = 0
	set /A number_png_tot = 0
	for /D %%b in (%%a\*) do (
		set /a number_dirs = !number_dirs! + 1
		set /A number_bmp = 0
		set /A number_jpg = 0
		set /A number_png = 0
		for %%c in (%%b\*.JPG) do (
			set /a number_jpg = !number_jpg! + 1
		)
		for %%c in (%%b\*.BMP) do (
			set /a number_bmp = !number_bmp! + 1
		)
		for %%c in (%%b\*.PNG) do (
			set /a number_png = !number_png! + 1
		)
		echo %%b  #jpg=!number_jpg!  #bmp=!number_bmp!  #png=!number_png!
		set /A number_bmp_tot = !number_bmp_tot! + !number_bmp!
		set /A number_jpg_tot = !number_jpg_tot! + !number_jpg!
		set /A number_png_tot = !number_png_tot! + !number_png!
		set /A number_bmp_tot2 = !number_bmp_tot2! + !number_bmp!
		set /A number_jpg_tot2 = !number_jpg_tot2! + !number_jpg!
		set /A number_png_tot2 = !number_png_tot2! + !number_png!
	)
	echo TOTAL %%a  #jpg=!number_jpg_tot!  #bmp=!number_bmp_tot!  #png=!number_png_tot!
)
echo Number of directories = !number_dirs!
echo Number of .bmp files  = !number_bmp_tot2!
echo Number of .jpg files  = !number_jpg_tot2!
echo Number of .png files  = !number_png_tot2!
pause

