@echo off



setlocal ENABLEDELAYEDEXPANSION


REM When not there gives file not found message
for /f "tokens=*" %%I in ('dir /b "*.mkv"') do (
	if exist "%%~nI.nl.srt" call :BURN_FILE "%%~nI" "%%I"
)
for /f "tokens=*" %%I in ('dir /b "*.mp4"') do (
	if exist "%%~nI.nl.srt" call :BURN_FILE "%%~nI" "%%I"
)
for /f "tokens=*" %%I in ('dir /b "*.webm"') do (
	if exist "%%~nI.nl.srt" call :BURN_FILE "%%~nI" "%%I"
)

rem pause

exit /b

:BURN_FILE

	set hoppa=%1
	set input=%2
	echo hoppa=!hoppa!
	echo input=!input!

	ffprobe.exe -v error -select_streams v:0 -show_entries format=bit_rate -of default=nw=1 !input! > bit_rate2.txt
	for /F "tokens=*" %%R in (bit_rate2.txt) do (
		for /f "tokens=1,2 delims==" %%a in ("%%R") do set NAME=%%a & set bit_rate=%%b
	)

	sof.exe "!hoppa!.nl.srt"

rem	sof.exe "!hoppa!.en.srt"

	if not exist DUTCH mkdir DUTCH

	for %%x in ("!hoppa!.nl.srt.fixed") do (
		if not %%~zx == 0 (
			if not  exist "DUTCH/!hoppa!.nl.mp4" (
				ffmpeg -y -hide_banner -i !input! -filter_complex "[0:v]scale=1920:1080[j];[j]subtitles='!hoppa!.nl.srt.fixed'[k]" -map "[k]" -map 0:a -strict -2 -c:v h264_nvenc -pix_fmt yuv420p -rc-lookahead 32 -b:v !bit_rate! -ac 2 -ar 44100 -acodec aac "DUTCH/!hoppa!.nl.PART.mp4"
rem				ffmpeg -y -hide_banner -i !input! -filter_complex "[0:v]scale=1920:1080[j];[j]subtitles='!hoppa!.nl.srt.fixed'[k]" -map "[k]" -map 0:a -strict -2 -c:v libx264 -preset slow -crf 23 -pix_fmt yuv420p -b:v !bit_rate! -ac 2 -ar 44100 -acodec aac "DUTCH/!hoppa!.nl.PART.mp4"

			) else (
				echo Already exists: "DUTCH/!hoppa!.nl.mp4" 
			)
		) else (
			echo Subtitle file empty: !hoppa!.nl.srt.fixed
		)
	)

	if exist "DUTCH/!hoppa!.nl.PART.mp4" rename "DUTCH\!hoppa!.nl.PART.mp4" "!hoppa!.nl.mp4"
rem	if not exist SUBTITLES mkdir SUBTITLES
rem	if exist "!hoppa!.nl.srt.fixed" move "!hoppa!.nl.srt.fixed" SUBTITLES
rem	if exist "!hoppa!.nl.srt" move "!hoppa!.nl.srt" SUBTITLES

	goto :ENDING

	if not exist ENGLISH mkdir ENGLISH

 	for %%x in ("!hoppa!.en.srt.fixed") do (
 		if not %%~zx == 0 (
 			if not  exist "ENGLISH/!hoppa!.en.mp4" (
 				ffmpeg -y -hide_banner -i !input! -filter_complex "[0:v]scale=1920:1080[j];[j]subtitles='!hoppa!.en.srt.fixed'[k]" -map "[k]" -map 0:a -strict -2 -c:v h264_nvenc -pix_fmt yuv420p -rc-lookahead 32 -b:v !bit_rate! -ac 2 -ar 44100 -acodec aac "ENGLISH/!hoppa!.en.PART.mp4"
rem 				ffmpeg -y -hide_banner -i !input! -filter_complex "[0:v]scale=1920:1080[j];[j]subtitles='!hoppa!.en.srt.fixed'[k]" -map "[k]" -map 0:a -strict -2 -c:v libx264 -preset slow -crf 23 -pix_fmt yuv420p -b:v !bit_rate! -ac 2 -ar 44100 -acodec aac "ENGLISH/!hoppa!.en.PART.mp4"
 			) else (
 				echo Already exists: "DUTCH/!hoppa!.en.mp4" 
 			)
 		) else (
 			echo Subtitle file empty: !hoppa!.en.srt.fixed
 		)
 	)
 
 	if exist "ENGLISH/!hoppa!.en.PART.mp4" rename "ENGLISH\!hoppa!.en.PART.mp4" "!hoppa!.en.mp4"
rem 	if exist "!hoppa!.en.srt.fixed" move "!hoppa!.en.srt.fixed" SUBTITLES >NUL
rem 	if exist "!hoppa!.en.srt" move "!hoppa!.en.srt" SUBTITLES >NUL

	if not exist ORIGINAL mkdir ORIGINAL
	move !input! ORIGINAL >NUL
	move "!hoppa!.*" ORIGINAL >NUL

:ENDING

exit /b