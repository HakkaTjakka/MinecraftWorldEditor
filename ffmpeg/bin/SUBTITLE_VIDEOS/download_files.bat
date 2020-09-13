for /F "tokens=*" %%A in (list.txt) do (
	call convert.bat
	call download_youtube.bat "%%A"
)
call convert.bat
