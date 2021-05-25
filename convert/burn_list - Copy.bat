@echo off
setlocal ENABLEDELAYEDEXPANSION

for /F "tokens=*" %%I in (burn_list.txt) do (
	call :BURN_FILE "%%~nI" "%%I"
)

pause

exit /b

:BURN_FILE

set short=%1
set full=%2

echo !full!

rem ffmpeg.exe -hide_banner -i "!full!" -c:v h264_nvenc -vf "scale=1920:1080:-1,subtitles=f='!short!.srt':force_style='FontName=Arial,FontSize=24,Shadow=1'" -c:s mov_text -profile:v high -pix_fmt yuv420p -bufsize 20M -bf:v 3 -preset slow -rc:v vbr_hq -rc-lookahead 32 -c:a copy "!short!.nl.mp4"

rem ffmpeg.exe -hide_banner -i "!full!" -c:v h264_nvenc -vf "scale=1920:1080:-1,subtitles=f='!short!.srt':force_style='FontName=Arial,FontSize=24,Shadow=1'" -profile:v high -pix_fmt yuv420p -bufsize 20M -bf:v 3 -preset slow -rc:v vbr_hq -rc-lookahead 32 -c:a copy "!short!.nl.mp4"

rem ffmpeg.exe -hide_banner -y -ss 01:37:33 -t 00:01:09.5 -copyts -i "!full!" -c:v h264_nvenc -vf "scale=640:-1,subtitles=f='!short!.srt':force_style='FontName=Arial,FontSize=32,Shadow=1'" -c:s mov_text -profile:v high -pix_fmt yuv420p -bufsize 20M -bf:v 3 -preset slow -rc:v vbr_hq -rc-lookahead 32 -c:a copy -ss 01:37:33 "!short!.nl.mp4"

rem ffmpeg.exe -hide_banner -y -copyts -i "!full!" -c:v h264_nvenc -vf "subtitles=f='!short!.srt':force_style='FontName=Arial,FontSize=32,Shadow=1'" -c:s mov_text -profile:v high -pix_fmt yuv420p -bufsize 20M -bf:v 3 -preset slow -rc:v vbr_hq -rc-lookahead 32 -c:a copy -ss 00:00:00 "!short!.nl.mp4"

rem ffmpeg.exe -hide_banner -y -ss 01:37:33 -t 00:01:09.5 -copyts -i "!full!" -c:v h264_nvenc -vf "scale=860:640:force_original_aspect_ratio=decrease,pad=860:640:-1:50:color=#242526,subtitles=f='!short!.srt':force_style='FontName=Arial,FontSize=32,Shadow=1'" -c:s mov_text -profile:v high -pix_fmt yuv420p -bufsize 20M -bf:v 3 -b:v 1M -preset slow -rc:v vbr_hq -rc-lookahead 32 -c:a copy -ss 01:37:33 "!short!.nl.mp4"

rem ffmpeg.exe -hide_banner -y -ss 01:37:33 -copyts -i "!full!" -t 00:01:09.5 -c:v h264_nvenc -vf "scale=860:640:force_original_aspect_ratio=decrease,pad=860:640:-1:50:color=#242526,subtitles=f='!short!.srt':force_style='FontName=Arial,FontSize=32,Shadow=1'" -c:s mov_text -profile:v high -pix_fmt yuv420p -bufsize 20M -bf:v 3 -b:v 1M -preset slow -rc:v vbr_hq -rc-lookahead 32 -c:a copy -ss 01:37:33 "!short!.nl.mp4"

rem ffmpeg.exe -hide_banner -y -ss 01:37:33 -copyts -i "!full!" -t 00:01:09.5 -c:v h264_nvenc -vf "scale=860:640:force_original_aspect_ratio=decrease,pad=860:640:-1:50:color=#242526,subtitles=f='!short!.srt':force_style='FontName=Arial,FontSize=32,Shadow=1'" -c:s mov_text -profile:v high -pix_fmt yuv420p -bufsize 20M -bf:v 3 -b:v 1M -preset slow -rc:v vbr_hq -rc-lookahead 32 -c:a copy -ss 01:37:33 "!short!.nl.mp4"

rem ffmpeg.exe -hide_banner -y -ss 01:37:33 -copyts -i "!full!" -t 00:01:09.5 -c:v h264_nvenc -vf "scale=1920:1080:force_original_aspect_ratio=decrease,pad=1920:1080:-1:0:color=#242526,subtitles=f='!short!.srt':force_style='FontName=Arial,FontSize=32,Shadow=1'" -c:s mov_text -profile:v high -pix_fmt yuv420p -bufsize 20M -bf:v 3 -b:v 1M -preset slow -rc:v vbr_hq -rc-lookahead 32 -c:a copy -ss 01:37:33 "!short!.nl.mp4"

rem ffmpeg.exe -hide_banner -y -ss 01:19:16 -copyts -i "!full!" -t 00:03:01 -c:v h264_nvenc -vf "scale=1920:1080:force_original_aspect_ratio=decrease,pad=1920:1080:-1:148:color=#ff5000,subtitles=f='!short!.srt':force_style='FontName=Arial,FontSize=32,Shadow=1'" -c:s mov_text -profile:v high -pix_fmt yuv420p -bufsize 20M -bf:v 3 -b:v 2.0M -preset slow -rc:v vbr_hq -rc-lookahead 32 -c:a copy -ss 01:19:16 "!short!.nl.mp4"

rem ffmpeg.exe -hide_banner -y -ss 01:19:16 -copyts -i "!full!" -t 00:03:01 -vf "[0:v]scale=1920:1080:force_original_aspect_ratio=decrease,pad=1920:1080:-1:148:color=#ff5000,subtitles=f='!short!.srt':force_style='FontName=Arial,FontSize=32,Shadow=1'" -c:s mov_text -c:v h264_nvenc -profile:v high -pix_fmt yuv420p -bufsize 20M -bf:v 3 -b:v 2.0M -preset slow -rc:v vbr_hq -rc-lookahead 32 -c:a copy -ss 01:19:16 "!short!.nl.mp4"

rem 1 ffmpeg.exe -hide_banner -y -ss 01:19:16 -copyts -i "!full!" -t 00:03:01 -filter_complex "[0:v]scale=1920:1080:force_original_aspect_ratio=decrease,pad=1920:1080:-1:148:color=#ff5000[j];[j]subtitles=f='!short!.srt':force_style='FontName=Arial,FontSize=32,Shadow=1'[k]" -map "[k]" -map 0:a -strict -2 -c:s mov_text -c:v h264_nvenc -profile:v high -pix_fmt yuv420p -bufsize 20M -bf:v 3 -b:v 2.0M -preset slow -rc:v vbr_hq -rc-lookahead 32 -c:a copy -ss 01:19:16 "!short!.nl.mp4"

rem ffmpeg -y -ss 01:19:16 -i "!short!.srt" "!short!_moved2.srt"

rem ffmpeg -y -itsoffset 4756.0 -i "!short!.srt" "!short!_moved.srt"




rem ffmpeg -hide_banner -y -i "!full!" -i "!short!.srt" -c copy -c:s srt -metadata:s:s:1 language=eng -map 0 -map 1 -map_metadata 0 "!short!_subs.mkv"
rem ffmpeg -hide_banner -y -ss 01:19:16 -t 00:03:01 -i "!short!_subs.mkv" -c copy "!short!_subs_cut.mkv" 
rem ffmpeg -hide_banner -y -i "!short!_subs_cut.mkv" "!short!_subs_cut_a.srt" 

rem -itsoffset 0.7
rem -itsoffset -0.7

ffmpeg -hide_banner -y -itsoffset -1.0 -i "!short!_subs_cut_a.srt" "!short!_subs_cut.srt"

ffmpeg.exe -hide_banner -y -ss 01:19:16 -t 00:03:01 -i "!short!_subs.mkv" -ss 00:00:00 -stream_loop -1 -i logo.avi -filter_complex "[0:v]scale=1920:1080:force_original_aspect_ratio=decrease[p];[p]pad=1920:1080:-1:148:color=#ff5000[j];[j][1:v]overlay=shortest=1:x=main_w-overlay_w-10:y=main_h-overlay_h[l];[l]subtitles=f='!short!_subs_cut.srt':force_style='FontName=Arial,FontSize=32,Shadow=1'[k]" -map "[k]" -map 0:a -strict -2  -c:s mov_text -c:v h264_nvenc -profile:v high -pix_fmt yuv420p -bufsize 20M -bf:v 3 -b:v 2.0M -preset slow -rc:v vbr_hq -rc-lookahead 32 -shortest "!short!.nl.mp4"



rem ffmpeg.exe -hide_banner -y -ss 01:19:16 -t 00:03:01 -i "!short!_subs.mkv" -ss 00:00:00 -stream_loop -1 -i logo.avi -filter_complex "[0:v]scale=1920:1080:force_original_aspect_ratio=decrease[p];[p]pad=1920:1080:-1:148:color=#ff5000[j];[j][1:v]overlay=shortest=1:x=main_w-overlay_w-10:y=main_h-overlay_h[l];[l]subtitles=f='!short!_moved.srt':force_style='FontName=Arial,FontSize=32,Shadow=1'[k]" -map "[k]" -map 0:a -strict -2  -c:s mov_text -c:v h264_nvenc -profile:v high -pix_fmt yuv420p -bufsize 20M -bf:v 3 -b:v 2.0M -preset slow -rc:v vbr_hq -rc-lookahead 32 -shortest "!short!.nl.mp4"

rem ffmpeg.exe -hide_banner -y -ss 01:19:16 -t 00:03:01 -i "!full!" -ss 00:00:00 -stream_loop -1 -i logo.avi -filter_complex "[0:v]scale=1920:1080:force_original_aspect_ratio=decrease[p];[p]pad=1920:1080:-1:148:color=#ff5000[j];[j][1:v]overlay=shortest=1:x=main_w-overlay_w-10:y=main_h-overlay_h[l];[l]subtitles=f='!short!_moved.srt':force_style='FontName=Arial,FontSize=32,Shadow=1'[k]" -map "[k]" -map 0:a -strict -2  -c:s mov_text -c:v h264_nvenc -profile:v high -pix_fmt yuv420p -bufsize 20M -bf:v 3 -b:v 2.0M -preset slow -rc:v vbr_hq -rc-lookahead 32 -shortest "!short!.nl.mp4"

rem	ffmpeg -y -hide_banner -i !input! -i intro.wav -i intro.wav -ss 00:00:00 -stream_loop -1 -i pacman_rgba.avi -filter_complex "[1]adelay=500|500[s1];[1]adelay=!number_offset!|!number_offset![s2];[0][s1][s2]amix=inputs=3;[0:v]scale=1920:1080[j];[j][3:v]overlay=shortest=1:x=main_w-overlay_w-10:y=main_h-overlay_h[l];[l]subtitles='!hoppa!.nl.srt.fixed':force_style='FontName=Mada Black,FontSize=24,BackColour=&HE0000000,BorderStyle=4'[k]" -map "[k]" -map 0:a -strict -2 -c:v h264_nvenc -profile:v high -pix_fmt yuv420p -bufsize 20M -bf:v 3 -preset slow -rc:v vbr_hq -rc-lookahead 32 -ac 2 -ar 44100 -acodec aac -shortest "DUTCH/!hoppa!.nl.PART.mp4"

rem ffmpeg.exe -hide_banner -y -ss 01:19:16 -copyts -i "!full!" -t 00:03:01 -stream_loop -1 -i logo.avi -filter_complex "[0:v]scale=1920:1080:force_original_aspect_ratio=decrease[p];[p]pad=1920:1080:-1:148:color=#ff5000[j];[j][1:v]overlay=shortest=1:x=main_w-overlay_w-10:y=main_h-overlay_h[l];[l]subtitles=f='!short!.srt':force_style='FontName=Arial,FontSize=32,Shadow=1'[k]" -map "[k]" -map 0:a -strict -2 -c:s mov_text -c:v h264_nvenc -profile:v high -pix_fmt yuv420p -bufsize 20M -bf:v 3 -b:v 2.0M -preset slow -rc:v vbr_hq -rc-lookahead 32 -c:a copy -ss 01:19:16 "!short!.nl.mp4"

rem ffmpeg.exe -hide_banner -y -ss 01:19:16 -copyts -i "!full!" -t 00:03:01 -stream_loop -1 -i logo.avi -filter_complex "[0:v]scale=1920:1080:force_original_aspect_ratio=decrease,pad=1920:1080:-1:148:color=#ff5000[j];[j][1:v]overlay=shortest=1:x=main_w-overlay_w-10:y=main_h-overlay_h[l];[l]subtitles=f='!short!.srt':force_style='FontName=Arial,FontSize=32,Shadow=1'[k]" -map "[k]" -map 0:a -strict -2 -c:s mov_text -c:v h264_nvenc -profile:v high -pix_fmt yuv420p -bufsize 20M -bf:v 3 -b:v 2.0M -preset slow -rc:v vbr_hq -rc-lookahead 32 -c:a copy -ss 01:19:16 "!short!.nl.mp4"



rem ffmpeg -y -hide_banner -ss 01:19:16 -copyts -i "!full!" -t 00:03:01 -stream_loop -1 -i logo.avi -filter_complex "[0:v]scale=1920:1080:force_original_aspect_ratio=decrease,pad=1920:1080:-1:148:color=#ff5000[j];[j][1:v]overlay=shortest=1:x=main_w-overlay_w-10:y=main_h-overlay_h[l];[l]subtitles=f='!short!.srt':force_style='FontName=Arial,FontSize=32,Shadow=1'[k]" -map "[k]" -map 0:a -strict -2 -c:v h264_nvenc -profile:v high -pix_fmt yuv420p -b:v 2.0M -bufsize 20M -bf:v 3 -preset slow -rc:v vbr_hq -rc-lookahead 32 -shortest -c:a copy -ss 01:19:16 "!short!.nl.mp4"

rem ffmpeg -y -hide_banner -ss 01:19:16 -copyts -i "!full!" -t 00:03:01 -stream_loop -1 -i logo.avi -filter_complex "[0:v]scale=1920:1080:force_original_aspect_ratio=decrease,pad=1920:1080:-1:148:color=#ff5000[j];[j][1:v]overlay=shortest=1:x=main_w-overlay_w-10:y=main_h-overlay_h[l];[l]subtitles=f='!short!.srt':force_style='FontName=Arial,FontSize=32,Shadow=1'[k]" -map "[k]" -map 0:a -strict -2 -c:v h264_nvenc -profile:v high -pix_fmt yuv420p -b:v 2.0M -bf:v 3 -preset slow -rc:v vbr_hq -rc-lookahead 32 -c:a copy -shortest -ss 01:19:16 "!short!.nl.mp4"

rem ffmpeg -y -hide_banner -ss 01:19:16 -copyts -i "!full!" -t 00:03:01 -stream_loop -1 -i logo.avi -filter_complex "[0:v]scale=1920:1080:force_original_aspect_ratio=decrease,pad=1920:1080:-1:148:color=#ff5000[j];[j][1:v]overlay=shortest=1:x=main_w-overlay_w-10:y=main_h-overlay_h[l];[l]subtitles=f='!short!.srt':force_style='FontName=Arial,FontSize=32,Shadow=1'[k]" -map "[k]" -map 0:a -strict -2 -c:v h264_nvenc -profile:v high -pix_fmt yuv420p -bf:v 3 -preset slow -rc:v vbr_hq -rc-lookahead 32 -c:a copy -shortest -ss 01:19:16 "!short!.nl.mp4"

rem -b:v 2.0M 


rem -bufsize 20M 

rem ffmpeg -y -hide_banner -ss 01:19:16 -copyts -i "!full!" -t 00:03:01 -filter_complex "[0:v]scale=1920:1080:force_original_aspect_ratio=decrease,pad=1920:1080:-1:148:color=#ff5000[j];[j]subtitles=f='!short!.srt':force_style='FontName=Arial,FontSize=32,Shadow=1'[k]" -map "[k]" -map 0:a -strict -2 -c:v h264_nvenc -profile:v high -pix_fmt yuv420p -b:v 2.0M -bufsize 20M -bf:v 3 -preset slow -rc:v vbr_hq -rc-lookahead 32 -shortest -c:a copy -ss 01:19:16 "!short!.nl.mp4"


rem ffmpeg.exe -hide_banner -y -ss 01:37:33 -t 00:01:09.5 -copyts -i "!full!" -c:v h264_nvenc -vf "scale=860:640:force_original_aspect_ratio=decrease,pad=860:640:-1:50:color=#ffffff,subtitles=f='!short!.srt':force_style='FontName=Arial,FontSize=32,Shadow=1'" -c:s mov_text -profile:v high -pix_fmt yuv420p -bufsize 20M -bf:v 3 -b:v 1M -preset slow -rc:v vbr_hq -rc-lookahead 32 -c:a copy -ss 01:37:33 "!short!.nl.w.mp4"

rem scale=1920:1080:force_original_aspect_ratio=decrease,pad=1920:1080:-1:-1:color=#242526,subti

rem ffmpeg -ss 25:00 -to 26:00 -copyts -i vid.mp4 -vf subtitles=sub.srt  -c:a copy -ss 25:00 -y final.mp4


exit /b
