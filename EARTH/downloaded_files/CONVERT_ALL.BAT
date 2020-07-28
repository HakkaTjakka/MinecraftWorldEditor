@echo off
for /D %%a in (%CD%\*) do (
	ECHO %%a
	DIR /s/b %%a >NUL
	for /D %%b in (%%a\*) do (
		for /D %%c in (%%b\*) do (
			ECHO %%c
			for %%d in (%%c\*.png) do (
				echo %%d
  				"C:\Program Files\IrfanView\i_view64.exe" %%d /convert=%%c\%%~nd.jpg
				echo del %%d /s >NUL 2>NUL
			)
			for %%d in (%%c\*.bmp) do (
				echo %%d
  				"C:\Program Files\IrfanView\i_view64.exe" %%d /convert=%%c\%%~nd.jpg
				echo del %%d /s >NUL 2>NUL
			)
		)
	)
)
bash -c "./convert_to_jpg_mtl_files.sh" 2>NUL
pause

