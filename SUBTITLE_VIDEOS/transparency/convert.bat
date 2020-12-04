@echo off

setlocal ENABLEDELAYEDEXPANSION

REM When not there gives file not found message
for /f "tokens=*" %%I in ('dir /b "*.mkv"') do (
	if exist "%%~nI.nl.srt" (
		call :BURN_FILE "%%~nI" "%%I"
	)
	if exist "%%~nI.en.srt" (
		call :BURN_FILE "%%~nI" "%%I"
	) 
)
for /f "tokens=*" %%I in ('dir /b "*.mp4"') do (
	if exist "%%~nI.nl.srt" (
		call :BURN_FILE "%%~nI" "%%I"
	)
	if exist "%%~nI.en.srt" (
		call :BURN_FILE "%%~nI" "%%I"
	) 
)
for /f "tokens=*" %%I in ('dir /b "*.webm"') do (
	if exist "%%~nI.nl.srt" (
		call :BURN_FILE "%%~nI" "%%I"
	)
	if exist "%%~nI.en.srt" (
		call :BURN_FILE "%%~nI" "%%I"
	) 
)

pause

if not exist ORIGINAL mkdir ORIGINAL
move "%%I" ORIGINAL >NUL
move "%%~nI.*" ORIGINAL >NUL

exit /b

:BURN_FILE

	set hoppa=%1
	set input=%2
	echo hoppa=!hoppa!
	echo input=!input!

 	ffprobe.exe -v error -select_streams v:0 -show_entries format=bit_rate -of default=nw=1 !input! > bit_rate2.txt
	ffprobe.exe -v error -show_entries format=duration -of default=nw=1 !input! > duration2.txt
	ffprobe.exe -v error -show_entries format=duration -of default=nw=1 intro.wav > duration_intro.txt

	for /F "tokens=*" %%R in (bit_rate2.txt) do (
		for /f "tokens=1,2 delims==" %%a in ("%%R") do set NAME=%%a & set bit_rate=%%b
	)
	for /F "tokens=*" %%R in (duration2.txt) do (
		for /f "tokens=1,2 delims==" %%a in ("%%R") do set NAME=%%a & set duration=%%b
	)
	for /F "tokens=*" %%R in (duration_intro.txt) do (
		for /f "tokens=1,2 delims==" %%a in ("%%R") do set NAME=%%a & set duration_intro=%%b
	)
	for /f "tokens=1 delims=." %%a in ('echo !duration!') do set /a number=%%a
	for /f "tokens=1 delims=." %%a in ('echo !duration_intro!') do set /a number_intro=%%a

	set /A number_offset = !number! - !number_intro! - 1
	set /A number_offset = !number_offset! * 1000

rem 	echo !number!
rem 	echo !number_intro!
rem 	echo !number_offset!
rem 
rem 
rem pause

	sof.exe "!hoppa!.nl.srt"

	if not exist DUTCH mkdir DUTCH

	for %%x in ("!hoppa!.nl.srt.fixed") do (
		if not %%~zx == 0 (
			if not  exist "DUTCH/!hoppa!.nl.mp4" (
rem ffmpeg.exe -hide_banner -i "Incase you have not heard this   its important 10160326756397835-0wRbQRRWc80.f244.webm" -i "Incase you have not heard this   its important 10160326756397835-0wRbQRRWc80.f140.m4a" -map 0:v:0 -map 1:a:0 -strict -2 -vf subtitles="f='Incase you have not heard this   its important 10160326756397835-0wRbQRRWc80.nl.srt.fixed':force_style='FontName=Mada Black,FontSize=32'" -c:s mov_text -s 1920x1080 -c:v h264_nvenc -profile:v high -pix_fmt yuv420p -b:v 10M -bufsize 20M -bf:v 3 -preset slow -rc:v vbr_hq -rc-lookahead 32 -c:a aac -b:a 96k "out/Incase you have not heard this   its important 10160326756397835-0wRbQRRWc80.nl.mp4"
rem :force_style='FontName=Mada Black,FontSize=32'
rem -vf subtitles="f='subs.nl.srt.fixed':force_style='FontName=Mada Black,FontSize=32'"

rem  			ffmpeg -y -hide_banner -i !input! -itsoffset 00:00:05 -i intro.wav -map 1:0 -filter_complex "[0:v]scale=1920:1080[j];[j]subtitles='!hoppa!.nl.srt.fixed':force_style='FontName=Mada Black,FontSize=32,BackColour=&HA0000000,BorderStyle=4'[k]" -map "[k]" -map 0:a -strict -2 -c:v h264_nvenc -pix_fmt yuv420p -rc-lookahead 32 -b:v !bit_rate! -ac 2 -ar 44100 -acodec aac "DUTCH/!hoppa!.nl.PART.mp4"
rem  			ffmpeg -y -hide_banner -i !input! -i intro.wav -filter_complex "[0][1]amix=inputs=2;[0:v]scale=1920:1080[j];[j]subtitles='!hoppa!.nl.srt.fixed':force_style='FontName=Mada Black,FontSize=32,BackColour=&HA0000000,BorderStyle=4'[k]" -map "[k]" -map 0:a -strict -2 -c:v h264_nvenc -pix_fmt yuv420p -rc-lookahead 32 -b:v !bit_rate! -ac 2 -ar 44100 -acodec aac "DUTCH/!hoppa!.nl.PART.mp4"
rem  			ffmpeg -y -hide_banner -i !input! -i intro.wav -i intro.wav -i pacman_small.png -filter_complex "[0:v][3:v]overlay=main_w-overlay_w-10:main_h-overlay_h-10;[1]adelay=500|500[s1];[1]adelay=!number_offset!|!number_offset![s2];[0][s1][s2]amix=inputs=3;[0:v]scale=1920:1080[j];[j]subtitles='!hoppa!.nl.srt.fixed':force_style='FontName=Mada Black,FontSize=32,BackColour=&HA0000000,BorderStyle=4'[k]" -map "[k]" -map 0:a -strict -2 -c:v h264_nvenc -pix_fmt yuv420p -rc-lookahead 32 -b:v !bit_rate! -ac 2 -ar 44100 -acodec aac "DUTCH/!hoppa!.nl.PART.mp4"
rem  			ffmpeg -y -hide_banner -i !input! -i intro.wav -i intro.wav -i pacman_small.png -filter_complex "[0:v][3:v]overlay=main_w-overlay_w-10:main_h-overlay_h-10;[1]adelay=500|500[s1];[1]adelay=!number_offset!|!number_offset![s2];[0][s1][s2]amix=inputs=3;[0:v]scale=1920:1080[j];[j]subtitles='!hoppa!.nl.srt.fixed':force_style='FontName=Mada Black,FontSize=32,BackColour=&HA0000000,BorderStyle=4'[k]" -map "[k]" -map 0:a -strict -2 -c:v h264_nvenc -pix_fmt yuv420p -rc-lookahead 32 -b:v !bit_rate! -ac 2 -ar 44100 -acodec aac "DUTCH/!hoppa!.nl.PART.mp4"
rem  			ffmpeg -y -hide_banner -i !input! -i intro.wav -i intro.wav -i pacman_cut.mp4 -filter_complex "[0:v][3:v]overlay=main_w-overlay_w-10:main_h-overlay_h-10;[1]adelay=500|500[s1];[1]adelay=!number_offset!|!number_offset![s2];[0][s1][s2]amix=inputs=3;[0:v]scale=1920:1080[j];[j]subtitles='!hoppa!.nl.srt.fixed':force_style='FontName=Mada Black,FontSize=32,BackColour=&HA0000000,BorderStyle=4'[k]" -map "[k]" -map 0:a -strict -2 -c:v h264_nvenc -pix_fmt yuv420p -rc-lookahead 32 -b:v !bit_rate! -ac 2 -ar 44100 -acodec aac "DUTCH/!hoppa!.nl.PART.mp4"
rem 			ffmpeg -y -hide_banner -i !input! -i intro.wav -i intro.wav -i pacman_cut.mp4 -filter_complex "[3:v]scale=1920:70[q];[0:v][q]overlay=0:main_h-overlay_h-2;[1]adelay=500|500[s1];[1]adelay=!number_offset!|!number_offset![s2];[0][s1][s2]amix=inputs=3;[0:v]scale=1920:1080[j];[j]subtitles='!hoppa!.nl.srt.fixed':force_style='FontName=Mada Black,FontSize=32,BackColour=&HA0000000,BorderStyle=4'[k]" -map "[k]" -map 0:a -strict -2 -c:v h264_nvenc -pix_fmt yuv420p -rc-lookahead 32 -b:v !bit_rate! -ac 2 -ar 44100 -acodec aac "DUTCH/!hoppa!.nl.PART.mp4"
rem  			ffmpeg -y -hide_banner -i !input! -i intro.wav -i intro.wav -i pacman_cut.mp4 -filter_complex "[1]adelay=500|500[s1];[1]adelay=!number_offset!|!number_offset![s2];[0][s1][s2]amix=inputs=3;[0:v]scale=1920:1080[j];[j]subtitles='!hoppa!.nl.srt.fixed':force_style='FontName=Mada Black,FontSize=32,BackColour=&HA0000000,BorderStyle=4'[k];[k][3:v]overlay=0:main_h-overlay_h-2[l]" -map "[l]" -map 0:a -strict -2 -c:v h264_nvenc -pix_fmt yuv420p -rc-lookahead 32 -b:v !bit_rate! -ac 2 -ar 44100 -acodec aac "DUTCH/!hoppa!.nl.PART.mp4"
rem  			ffmpeg -y -hide_banner -i !input! -i intro.wav -i intro.wav -i pacman_cut.mp4 -filter_complex "[1]adelay=500|500[s1];[1]adelay=!number_offset!|!number_offset![s2];[0][s1][s2]amix=inputs=3;[0:v]scale=1920:1080[j];[j][3:v]overlay=0:main_h-overlay_h-2[l];[l]subtitles='!hoppa!.nl.srt.fixed':force_style='FontName=Mada Black,FontSize=32,BackColour=&HA0000000,BorderStyle=4'[k]" -map "[k]" -map 0:a -strict -2 -c:v h264_nvenc -pix_fmt yuv420p -rc-lookahead 32 -b:v !bit_rate! -ac 2 -ar 44100 -acodec aac "DUTCH/!hoppa!.nl.PART.mp4"
rem  			ffmpeg -y -hide_banner -i !input! -i intro.wav -i intro.wav -i pacman_cut.mp4 -filter_complex "[1]adelay=500|500[s1];[1]adelay=!number_offset!|!number_offset![s2];[0][s1][s2]amix=inputs=3;[0:v]scale=1920:1080[j];[3:v]split[m][a];[a]geq='if(gt(lum(X,Y),16),255,0)',hue=s=0[al];[m][al]alphamerge[ovr];[j][ovr]overlay=0:main_h-overlay_h-2[l];[l]subtitles='!hoppa!.nl.srt.fixed':force_style='FontName=Mada Black,FontSize=32,BackColour=&HA0000000,BorderStyle=4'[k]" -map "[k]" -map 0:a -strict -2 -c:v h264_nvenc -pix_fmt yuv420p -rc-lookahead 32 -b:v !bit_rate! -ac 2 -ar 44100 -acodec aac "DUTCH/!hoppa!.nl.PART.mp4"
rem  			 ffmpeg -y -hide_banner -i !input! -i intro.wav -i intro.wav -i pacman_cut.mp4 -filter_complex "[1]adelay=500|500[s1];[1]adelay=!number_offset!|!number_offset![s2];[0][s1][s2]amix=inputs=3;[0:v]scale=1920:1080[j];[3:v]split[m][a];[a]geq='r=r(X,Y)',hue=s=0[al];[m][al]alphamerge[ovr];[j][ovr]overlay=0:main_h-overlay_h-2[l];[l]subtitles='!hoppa!.nl.srt.fixed':force_style='FontName=Mada Black,FontSize=32,BackColour=&HA0000000,BorderStyle=4'[k]" -map "[k]" -map 0:a -strict -2 -c:v h264_nvenc -pix_fmt yuv420p -rc-lookahead 32 -b:v !bit_rate! -ac 2 -ar 44100 -acodec aac "DUTCH/!hoppa!.nl.PART.mp4"
 			REM ffmpeg -y -hide_banner -i !input! -i intro.wav -i intro.wav -i pacman_cut.mp4 -filter_complex "[1]adelay=500|500[s1];[1]adelay=!number_offset!|!number_offset![s2];[0][s1][s2]amix=inputs=3;[0:v]scale=1920:1080[j];[3:v]split[m][a];[a]geq='if(gt(lum(X,Y),16),255,0)',hue=s=0[al];[m][al]alphamerge[ovr];[j][ovr]overlay=0:main_h-overlay_h-2[l];[l]subtitles='!hoppa!.nl.srt.fixed':force_style='FontName=Mada Black,FontSize=32,BackColour=&HA0000000,BorderStyle=4'[k]" -map "[k]" -map 0:a -strict -2 -c:v h264_nvenc -pix_fmt yuv420p -rc-lookahead 32 -b:v !bit_rate! -ac 2 -ar 44100 -acodec aac "DUTCH/!hoppa!.nl.PART.mp4"
rem 			ffmpeg -y -hide_banner -i !input! -i intro.wav -i intro.wav -i pacman2.mp4 -filter_complex "[1]adelay=500|500[s1];[1]adelay=!number_offset!|!number_offset![s2];[0][s1][s2]amix=inputs=3;[0:v]scale=1920:1080[j];[3:v]split[m][a];[a]geq='lum(X,Y)',hue=s=0[al];[m][al]alphamerge[ovr];[ovr]scale=100:-1[sml];[j][sml]overlay=main_w-overlay_w-2:main_h-overlay_h-2[l];[l]subtitles='!hoppa!.nl.srt.fixed':force_style='FontName=Mada Black,FontSize=32,BackColour=&HA0000000,BorderStyle=4'[k]" -map "[k]" -map 0:a -strict -2 -c:v h264_nvenc -pix_fmt yuv420p -rc-lookahead 32 -b:v !bit_rate! -ac 2 -ar 44100 -acodec aac "DUTCH/!hoppa!.nl.PART.mp4"

rem 			ffmpeg -y -hide_banner -i !input! -i intro.wav -i intro.wav -i pacman2.mp4 -filter_complex "[1]adelay=500|500[s1];[1]adelay=!number_offset!|!number_offset![s2];[0][s1][s2]amix=inputs=3;[0:v]scale=1920:1080[j];[3:v]split[m][a];[a]geq='lum(X,Y)',hue=s=0[al];[m][al]alphamerge[ovr];[ovr]scale=150:-1[sml];[j][sml]overlay=main_w-overlay_w-2:main_h-overlay_h-2[l];[l]subtitles='!hoppa!.nl.srt.fixed':force_style='FontName=Mada Black,FontSize=32,BackColour=&HA0000000,BorderStyle=4'[k]" -map "[k]" -map 0:a -strict -2 -c:v h264_nvenc -pix_fmt yuv420p -rc-lookahead 32 -b:v !bit_rate! -ac 2 -ar 44100 -acodec aac -shortest "DUTCH/!hoppa!.nl.PART.mp4"
rem 			ffmpeg -y -hide_banner -i !input! -i intro.wav -i intro.wav -i pacman2_cut.mp4 -filter_complex "[1]adelay=500|500[s1];[1]adelay=!number_offset!|!number_offset![s2];[0][s1][s2]amix=inputs=3;[0:v]scale=1920:1080[j];[3:v]split[m][a];[a]geq='lum(X,Y)',hue=s=0[al];[m][al]alphamerge[ovr];[j][ovr]overlay=x=main_w-overlay_w-2:y=main_h-overlay_h-2[l];[l]subtitles='!hoppa!.nl.srt.fixed':force_style='FontName=Mada Black,FontSize=32,BackColour=&HA0000000,BorderStyle=4'[k]" -map "[k]" -map 0:a -strict -2 -c:v h264_nvenc -pix_fmt yuv420p -rc-lookahead 32 -b:v !bit_rate! -ac 2 -ar 44100 -acodec aac "DUTCH/!hoppa!.nl.PART.mp4"
rem			ffmpeg -y -hide_banner -i !input! -i intro.wav -i intro.wav -i pacman2_cut.mp4 -filter_complex "[1]adelay=500|500[s1];[1]adelay=!number_offset!|!number_offset![s2];[0][s1][s2]amix=inputs=3;[0:v]scale=1920:1080[j];[3:v]split[m][a];[a]geq='lum(X,Y)',hue=s=0[al];[m][al]alphamerge[ovr];[j][ovr]overlay=x=main_w-overlay_w-2:y=main_h-overlay_h-2[l];[l]subtitles='!hoppa!.nl.srt.fixed':force_style='FontName=Mada Black,FontSize=32,BackColour=&HA0000000,BorderStyle=4'[k]" -map "[k]" -map 0:a -strict -2 -c:v h264_nvenc -pix_fmt yuv420p -rc-lookahead 32 -b:v !bit_rate! -ac 2 -ar 44100 -acodec aac "DUTCH/!hoppa!.nl.PART.mp4"
rem 			ffmpeg -y -hide_banner -i !input! -i intro.wav -i intro.wav -i pacman2_cut.mp4 -filter_complex "[1]adelay=500|500[s1];[1]adelay=!number_offset!|!number_offset![s2];[0][s1][s2]amix=inputs=3;[0:v]scale=1920:1080[j];[3:v]split[m][a];[a]geq='lum(X,Y)',hue=s=0[al];[m][al]alphamerge[ovr];[j][ovr]overlay=main_w-overlay_w-2:main_h-overlay_h-2[l];[l]subtitles='!hoppa!.nl.srt.fixed':force_style='FontName=Mada Black,FontSize=32,BackColour=&HA0000000,BorderStyle=4'[k]" -map "[k]" -map 0:a -strict -2 -c:v h264_nvenc -pix_fmt yuv420p -rc-lookahead 32 -b:v !bit_rate! -ac 2 -ar 44100 -acodec aac -shortest "DUTCH/!hoppa!.nl.PART.mp4"
rem 			ffmpeg -y -hide_banner -i !input! -i intro.wav -i intro.wav -i pacman2_cut_rgba.mp4 -filter_complex "[1]adelay=500|500[s1];[1]adelay=!number_offset!|!number_offset![s2];[0][s1][s2]amix=inputs=3;[0:v]scale=1920:1080[j];[3:v]split[m][a];[a]geq='lum(X,Y)',hue=s=0[al];[m][al]alphamerge[ovr];[j][ovr]overlay=main_w-overlay_w-2:main_h-overlay_h-2[l];[l]subtitles='!hoppa!.nl.srt.fixed':force_style='FontName=Mada Black,FontSize=32,BackColour=&HA0000000,BorderStyle=4'[k]" -map "[k]" -map 0:a -strict -2 -c:v h264_nvenc -pix_fmt yuv420p -rc-lookahead 32 -b:v !bit_rate! -ac 2 -ar 44100 -acodec aac -shortest "DUTCH/!hoppa!.nl.PART.mp4"
rem 			ffmpeg -y -hide_banner -i !input! -i intro.wav -i intro.wav -i pacman_cut_rgba.mp4 -filter_complex "[1]adelay=500|500[s1];[1]adelay=!number_offset!|!number_offset![s2];[0][s1][s2]amix=inputs=3;[0:v]scale=1920:1080[j];[j][3:v]overlay=main_w-overlay_w-2:main_h-overlay_h-2[l];[l]subtitles='!hoppa!.nl.srt.fixed':force_style='FontName=Mada Black,FontSize=32,BackColour=&HA0000000,BorderStyle=4'[k]" -map "[k]" -map 0:a -strict -2 -c:v h264_nvenc -pix_fmt yuv420p -rc-lookahead 32 -b:v !bit_rate! -ac 2 -ar 44100 -acodec aac "DUTCH/!hoppa!.nl.PART.mp4"
rem 			ffmpeg -y -hide_banner -i !input! -i intro.wav -i intro.wav -i pacman_rgba.avi -filter_complex "[1]adelay=500|500[s1];[1]adelay=!number_offset!|!number_offset![s2];[0][s1][s2]amix=inputs=3;[0:v]scale=1920:1080[j];[j][3:v]overlay[l];[l]subtitles='!hoppa!.nl.srt.fixed':force_style='FontName=Mada Black,FontSize=32,BackColour=&HA0000000,BorderStyle=4'[k]" -map "[k]" -map 0:a -strict -2 -c:v h264_nvenc -pix_fmt yuv420p -rc-lookahead 32 -b:v !bit_rate! -ac 2 -ar 44100 -acodec aac "DUTCH/!hoppa!.nl.PART.mp4"

rem 			ffmpeg -y -hide_banner -i !input! -i intro.wav -i intro.wav -stream_loop -1 -i pacman_cut_rgba.avi -filter_complex "[1]adelay=500|500[s1];[1]adelay=!number_offset!|!number_offset![s2];[0][s1][s2]amix=inputs=3;[0:v]scale=1920:1080[j];[j][3:v]overlay[l];[l]subtitles='!hoppa!.nl.srt.fixed':force_style='FontName=Mada Black,FontSize=32,BackColour=&HA0000000,BorderStyle=4'[k]" -map "[k]" -map 0:a -strict -2 -c:v h264_nvenc -pix_fmt yuv420p -rc-lookahead 32 -b:v 12M -ac 2 -ar 44100 -acodec aac "DUTCH/!hoppa!.nl.PART.mp4"
 			
rem 			ffmpeg -y -hide_banner -i !input! -i intro.wav -i intro.wav -stream_loop -1 -i pacman_cut_rgba.avi -filter_complex "[1]adelay=500|500[s1];[1]adelay=!number_offset!|!number_offset![s2];[0][s1][s2]amix=inputs=3;[0:v]scale=1920:1080[j];[j][3:v]overlay[l];[l]subtitles='!hoppa!.nl.srt.fixed':force_style='FontName=Mada Black,FontSize=32,BackColour=&HD0000000,BorderStyle=4'[k]" -map "[k]" -map 0:a -strict -2 -c:v h264_nvenc -pix_fmt yuv420p -rc-lookahead 32 -b:v 12M -ac 2 -ar 44100 -acodec aac "DUTCH/!hoppa!.nl.PART.mp4"
rem 			ffmpeg -y -hide_banner -i !input! -i intro.wav -i intro.wav -ss 00:00:00 -stream_loop -1 -i pacman_rgba.avi -filter_complex "[1]adelay=500|500[s1];[1]adelay=!number_offset!|!number_offset![s2];[0][s1][s2]amix=inputs=3;[0:v]scale=1920:1080[j];[3:v]colorchannelmixer=aa=0.4[a];[j][a]overlay=main_w-overlay_w:0[l];[l]subtitles='!hoppa!.nl.srt.fixed':force_style='FontName=Mada Black,FontSize=24,BackColour=&H60000000,BorderStyle=4'[k]" -map "[k]" -map 0:a -strict -2 -c:v h264_nvenc -profile:v high -pix_fmt yuv420p -b:v 10M -bufsize 20M -bf:v 3 -preset slow -rc:v vbr_hq -rc-lookahead 32 -ac 2 -ar 44100 -acodec aac -shortest "DUTCH/!hoppa!.nl.PART.mp4"
rem 			ffmpeg -y -hide_banner -i !input! -i intro.wav -i intro.wav -ss 00:00:00 -stream_loop -1 -i pacman_rgba.avi -filter_complex "[1]adelay=500|500[s1];[1]adelay=!number_offset!|!number_offset![s2];[0][s1][s2]amix=inputs=3;[0:v]scale=1920:1080[j];[3:v]colorchannelmixer=aa=0.4[a];[j][a]overlay=shortest=1:x=main_w-overlay_w[l];[l]subtitles='!hoppa!.nl.srt.fixed':force_style='FontName=Mada Black,FontSize=24,BackColour=&H60000000,BorderStyle=4'[k]" -map "[k]" -map 0:a -strict -2 -c:v h264_nvenc -profile:v high -pix_fmt yuv420p -b:v !bit_rate! -bufsize 20M -bf:v 3 -preset slow -rc:v vbr_hq -rc-lookahead 32 -ac 2 -ar 44100 -acodec aac -shortest "DUTCH/!hoppa!.nl.PART.mp4"
rem 			ffmpeg -y -hide_banner -i !input! -i intro.wav -i intro.wav -ss 00:00:00 -stream_loop -1 -i pacman_rgba.avi -filter_complex "[1]adelay=500|500[s1];[1]adelay=!number_offset!|!number_offset![s2];[0][s1][s2]amix=inputs=3;[0:v]scale=1920:1080[j];[3:v]colorchannelmixer=aa=0.4[a];[j][a]overlay=shortest=1:x=main_w-overlay_w:y=main_h-overlay_h[l];[l]subtitles='!hoppa!.nl.srt.fixed':force_style='FontName=Mada Black,FontSize=24,BackColour=&H60000000,BorderStyle=4'[k]" -map "[k]" -map 0:a -strict -2 -c:v h264_nvenc -profile:v high -pix_fmt yuv420p -b:v !bit_rate! -bufsize 20M -bf:v 3 -preset slow -rc:v vbr_hq -rc-lookahead 32 -ac 2 -ar 44100 -acodec aac -shortest "DUTCH/!hoppa!.nl.PART.mp4"
			ffmpeg -y -hide_banner -i !input! -i intro.wav -i intro.wav -ss 00:00:00 -stream_loop -1 -i pacman_rgba.avi -filter_complex "[1]adelay=500|500[s1];[1]adelay=!number_offset!|!number_offset![s2];[0][s1][s2]amix=inputs=3;[0:v]scale=1920:1080[j];[j][3:v]overlay=shortest=1:x=main_w-overlay_w-10:y=main_h-overlay_h[l];[l]subtitles='!hoppa!.nl.srt.fixed':force_style='FontName=Mada Black,FontSize=24,BackColour=&HE0000000,BorderStyle=4'[k]" -map "[k]" -map 0:a -strict -2 -c:v h264_nvenc -profile:v high -pix_fmt yuv420p -b:v !bit_rate! -bufsize 20M -bf:v 3 -preset slow -rc:v vbr_hq -rc-lookahead 32 -ac 2 -ar 44100 -acodec aac -shortest "DUTCH/!hoppa!.nl.PART.mp4"
																		rem -r 30 																																	rem [3:v]colorchannelmixer=aa=0.05[a];                                                   overlay=shortest=1																							,BackColour=&H60000000,
rem [j][3:v]overlay=0:main_h-overlay_h-2[l];

rem ffmpeg [3:v]split[m][a];[a]geq='if(gt(lum(X,Y),16),255,0)',hue=s=0[al];[m][al]alphamerge[ovr];[j][ovr]overlay=0:main_h-overlay_h-2[l];

rem ffmpeg -i 1.mp4 -i 2.mp4 -filter_complex
rem "[1]split[m][a];
rem  [a]geq='if(gt(lum(X,Y),16),255,0)',hue=s=0[al];
rem  [m][al]alphamerge[ovr];
rem  [0][ovr]overlay"
rem output.mp4

rem [3:v]scale=1920:70[q];
rem ffmpeg -i video.mp4 -i pacman_small.png -filter_complex "[0:v][1:v]overlay=main_w-overlay_w-10:main_h-overlay_h-10" 

rem  			ffmpeg -y -hide_banner -i !input! -i intro.wav -i intro.wav -filter_complex "[1]adelay=500|500[s1];[1]adelay=5500|5500[s2];[0][s1][s2]amix=inputs=3;[0:v]scale=1920:1080[j];[j]subtitles='!hoppa!.nl.srt.fixed':force_style='FontName=Mada Black,FontSize=32,BackColour=&HA0000000,BorderStyle=4'[k]" -map "[k]" -map 0:a -strict -2 -c:v h264_nvenc -pix_fmt yuv420p -rc-lookahead 32 -b:v !bit_rate! -ac 2 -ar 44100 -acodec aac "DUTCH/!hoppa!.nl.PART.mp4"
			
rem ffmpeg -i 1.mp3 -i 1.3gp -i 2.3gp -i 3.3gp -i 4.3gp -i 5.3gp -i 1.mp4 \ 
rem -filter_complex "[2]adelay=2790|2790[s2];\
rem [3]adelay=10300|10300[s3];\
rem [4]adelay=14930|14930[s4];\
rem [5]adelay=21090[s5];\
rem [0][1][s2][s3][s4][s5]amix=6[mixout]" \
rem -map 6:v -map [mixout] -c:v copy result.mp4

rem 																								[2]adelay=2790|2790[s2]			
rem  			ffmpeg -y -hide_banner -i !input! -itsoffset 00:00:05 -i intro.wav -filter_complex "[0:a][1:a] amix=inputs=2:duration=shortest;[0:v]scale=1920:1080[j];[j]subtitles='!hoppa!.nl.srt.fixed':force_style='FontName=Mada Black,FontSize=32,BackColour=&HA0000000,BorderStyle=4'[k]" -map "[k]" -map 0:a -strict -2 -c:v h264_nvenc -pix_fmt yuv420p -rc-lookahead 32 -b:v !bit_rate! -ac 2 -ar 44100 -acodec aac "DUTCH/!hoppa!.nl.PART.mp4"
rem -filter_complex "[0:0][1:0] amix=inputs=2:duration=shortest"
rem ffmpeg -y -i a.mp4 -itsoffset 00:00:30 -i intro.wav -map 0:0 -map 1:0 -c:v copy -preset ultrafast -async 1 out.mp4

rem  			ffmpeg -y -hide_banner -i !input! -filter_complex "[0:v]scale=1920:1080[j];[j]subtitles='!hoppa!.nl.srt.fixed':force_style='FontName=Mada Black,FontSize=32'[k]" -map "[k]" -map 0:a -strict -2 -c:v h264_nvenc -pix_fmt yuv420p -rc-lookahead 32 -b:v !bit_rate! -ac 2 -ar 44100 -acodec aac "DUTCH/!hoppa!.nl.PART.mp4"
rem 			ffmpeg -y -hide_banner -i !input! -filter_complex "[0:v]scale=1920:1080[j];[j]subtitles='!hoppa!.nl.srt.fixed'[k]" -map "[k]" -map 0:a -strict -2 -c:v h264_nvenc -pix_fmt yuv420p -rc-lookahead 32 -b:v !bit_rate! -ac 2 -ar 44100 -acodec aac "DUTCH/!hoppa!.nl.PART.mp4"
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

rem remark (rem) goto for making second language
goto :ENDING

sof.exe "!hoppa!.en.srt"

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

:ENDING

if not exist ORIGINAL mkdir ORIGINAL
move !input! ORIGINAL >NUL
move "!hoppa!.*" ORIGINAL >NUL

exit /b