@echo off
setlocal ENABLEDELAYEDEXPANSION

CALL :GETONE "%~1"

exit /b

:GETONE


echo GETONE %1
if exist filelist.txt del filelist.txt
youtube-dl --get-filename %1 > filelist.txt

for /F "tokens=*" %%A in (filelist.txt) do (
	set my_yes=1
	set my_error=2
	echo Getting: %%A
	echo Getting: %%A >> debug.log
	set hoppa2="%%A"
rem    echo !hoppa!
	set hoppa2=!hoppa2:'=_!
	set hoppa2=!hoppa2:`=!
	set hoppa2=!hoppa2:“=!
	set hoppa2=!hoppa2:"=!
	set hoppa2=!hoppa2:?=!
	set hoppa2=!hoppa2: =_!
	set hoppa2=!hoppa2:,=_!
	set hoppa2=!hoppa2:^|=_!
	set hoppa2=!hoppa2:^(=!
	set hoppa2=!hoppa2:^)=!
	set hoppa2=!hoppa2:^&=!
	set hoppa2=!hoppa2:^’=!
	set hoppa2=!hoppa2:__=_!
	set hoppa2=!hoppa2:__=_!

	set hoppa=!hoppa2!

	set hoppa=!hoppa:.mp4=!
	set hoppa=!hoppa:.mkv=!
	set hoppa=!hoppa:.webm=!


rem	pause
rem	exit /b

	if exist "!hoppa!.mkv" (
		set input="!hoppa!.mkv"
	) else (
		if exist "!hoppa!.mp4" (
			set input="!hoppa!.mp4"
		) else (
			if exist "!hoppa!.webm" (
				set input="!hoppa!.webm"
			) else (
				if exist "ORIGINAL\!hoppa!.mkv" (
					move "ORIGINAL\!hoppa!.mkv" "."  >NUL
					set input="!hoppa!.mkv"
				) else (
					if exist "ORIGINAL\!hoppa!.mp4" (
						move "ORIGINAL\!hoppa!.mp4" "."  >NUL
						set input="!hoppa!.mp4"
					) else (
						if exist "ORIGINAL\!hoppa!.webm" (
							move "ORIGINAL\!hoppa!.webm" "."  >NUL
							set input="!hoppa!.webm"
						) else (
							set input="!hoppa2!"
						)
					)
				)
			)
		)
	)
rem	echo input0 = !input!

 	if exist "ORIGINAL\!hoppa2!" (
 		move "ORIGINAL\!hoppa2!" "."  >NUL
		set input="!hoppa2!"
		set my_error=3
 	) else (
		if not exist "!hoppa2!" (
			if not exist !input! (
				set my_error=1
			) else (
				set my_error=3
			)
		) else (
			set input="!hoppa2!"
			set my_error=3
		)
 	)
rem	echo input1 = !input!

rem	echo INPUT = !input!

	if exist "SUBTITLES\!hoppa!.nl.srt" (
		move "SUBTITLES\!hoppa!.nl.srt" "." >NUL
		if not !my_error! == 1 set my_error=3		
 	) else (
		if not exist ".\!hoppa!.nl.srt" (
			set my_error=1
		) else (
			if not !my_error! == 1 set my_error=3
		)
	)
	if exist "SUBTITLES\!hoppa!.en.srt" (
		move "SUBTITLES\!hoppa!.en.srt" "." >NUL
		if not !my_error! == 1 set my_error=3
 	) else (
		if not exist ".\!hoppa!.en.srt" (
			set my_error=1
		) else (
			if not !my_error! == 1 set my_error=3
		)
	)
	if !my_error! == 2 set my_error=1
rem 	echo !my_error!
rem  	pause
rem  	exit /b
	
	if !my_error! == 1 (
		call youtube-dl --restrict-filenames --abort-on-error --no-mtime --sub-lang "en,nl" --write-sub --convert-subs srt --write-auto-sub --download-archive ARCHIVE.TXT --skip-unavailable-fragments --geo-bypass %1
	)

	echo input = !input!
	echo input  = !input! >> debug.log
	ffprobe.exe -v error -select_streams v:0 -show_entries format=bit_rate -of default=nw=1 !input! > bit_rate.txt
	for /F "tokens=*" %%R in (bit_rate.txt) do (
		for /f "tokens=1,2 delims==" %%a in ("%%R") do set NAME=%%a & set bit_rate=%%b
	rem	echo bit_rate = !bit_rate!
	)

 	sof.exe "!hoppa!.nl.srt"
	sof.exe "!hoppa!.en.srt"

	if not exist DUTCH mkdir DUTCH

	for %%x in ("!hoppa!.nl.srt.fixed") do (
		if not %%~zx == 0 (
			if not  exist "DUTCH/!hoppa!.nl.mp4" (
				ffmpeg -y -hide_banner -i !input! -filter_complex "[0:v]scale=1920:1080[j];[j]subtitles='!hoppa!.nl.srt.fixed'[k]" -map "[k]" -map 0:a -strict -2 -c:v h264_nvenc -pix_fmt yuv420p -rc-lookahead 32 -b:v !bit_rate! -ac 2 -ar 44100 -acodec aac "DUTCH/!hoppa!.nl.PART.mp4"
			) else (
				echo Already exists: "DUTCH/!hoppa!.nl.mp4" 
			)
		) else (
			echo Subtitle file empty: !hoppa!.nl.srt.fixed
		)
	)

	if exist "DUTCH/!hoppa!.nl.PART.mp4" rename "DUTCH\!hoppa!.nl.PART.mp4" "!hoppa!.nl.mp4"
	if not exist SUBTITLES mkdir SUBTITLES
	if exist "!hoppa!.nl.srt.fixed" move "!hoppa!.nl.srt.fixed" SUBTITLES >NUL
	if exist "!hoppa!.nl.srt" move "!hoppa!.nl.srt" SUBTITLES >NUL

	if not exist ENGLISH mkdir ENGLISH

rem		for %%x in ("!hoppa!.en.srt.fixed") do (
rem			if not %%~zx == 0 (
rem				if not  exist "ENGLISH/!hoppa!.en.mp4" (
rem					ffmpeg -y -hide_banner -i !input! -filter_complex "[0:v]scale=1920:1080[j];[j]subtitles='!hoppa!.en.srt.fixed'[k]" -map "[k]" -map 0:a -strict -2 -c:v h264_nvenc -pix_fmt yuv420p -rc-lookahead 32 -b:v !bit_rate! -ac 2 -ar 44100 -acodec aac "ENGLISH/!hoppa!.en.PART.mp4"
rem				) else (
rem					echo Already exists: "DUTCH/!hoppa!.en.mp4" 
rem				)
rem			) else (
rem				echo Subtitle file empty: !hoppa!.en.srt.fixed
rem			)
rem		)
rem	
rem		if exist "ENGLISH/!hoppa!.en.PART.mp4" rename "ENGLISH\!hoppa!.en.PART.mp4" "!hoppa!.en.mp4"
	if exist "!hoppa!.en.srt.fixed" move "!hoppa!.en.srt.fixed" SUBTITLES >NUL
	if exist "!hoppa!.en.srt" move "!hoppa!.en.srt" SUBTITLES >NUL

	if not exist ORIGINAL mkdir ORIGINAL
	move !input! ORIGINAL >NUL
	

rem 	ffmpeg -y -hide_banner -i "!hoppa2!" -filter_complex "[0:v]scale=1920:1080[j];[j]subtitles='!hoppa!.nl.srt.fixed'[k]" -map "[k]" -map 0:a -strict -2 -c:v h264_nvenc -profile:v high -pixel_format nv12 -bf:v 3 -preset slow -rc:v vbr_hq -rc-lookahead 32 -c:a copy "!hoppa!.hires.nl.mp4"
rem  	ffmpeg -y -hide_banner -i "!hoppa2!" -filter_complex "[0:v]scale=1920:1080[j];[j]subtitles='!hoppa!.en.srt.fixed'[k]" -map "[k]" -map 0:a -strict -2 -c:v h264_nvenc -profile:v high -pixel_format nv12 -bf:v 3 -preset slow -rc:v vbr_hq -rc-lookahead 32 -c:a copy "!hoppa!.hires.en.mp4"
)
exit /b

