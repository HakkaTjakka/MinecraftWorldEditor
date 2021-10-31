@echo off
setlocal EnableExtensions EnableDelayedExpansion
if exist FILTERED_OCTANTS.TXT DEL FILTERED_OCTANTS.TXT
for /f "tokens=*" %%P in (HOLLAND_LAT_LON_LARGER.TXT) do (
	for /f "tokens=1,2,3,4 delims=='[]'" %%a in ("%%P") do (
 		set /a n=%%a
 		set /a x=%%b
 		set /a y=%%c
 		set r=%%d
		rem echo !r!
		if !y! GTR 1056 (
			for /f "tokens=1,2 delims=='='" %%e in ("!r!") do (
				for /f "tokens=1,2 delims== " %%g in ("%%e") do (
					set o=%%g
REM 					if not !o! == 00000000000000000 (
						echo !o! [%%b][%%c]
						echo !o! [%%b][%%c]>>FILTERED_OCTANTS.TXT
REM 					)
				)
			)
		)
	)
)

pause
exit /b
