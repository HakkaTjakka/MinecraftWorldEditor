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

ffmpeg.exe -hide_banner -y -copyts -i "!full!" -c:v h264_nvenc -vf "subtitles=f='!short!.srt':force_style='FontName=Arial,FontSize=32,Shadow=1'" -c:s mov_text -profile:v high -pix_fmt yuv420p -bufsize 20M -bf:v 3 -preset slow -rc:v vbr_hq -rc-lookahead 32 -c:a copy -ss 00:00:00 "!short!.nl.mp4"

rem ffmpeg.exe -hide_banner -y -ss 01:37:33 -t 00:01:09.5 -copyts -i "!full!" -c:v h264_nvenc -vf "scale=860:640:force_original_aspect_ratio=decrease,pad=860:640:-1:50:color=#242526,subtitles=f='!short!.srt':force_style='FontName=Arial,FontSize=32,Shadow=1'" -c:s mov_text -profile:v high -pix_fmt yuv420p -bufsize 20M -bf:v 3 -b:v 1M -preset slow -rc:v vbr_hq -rc-lookahead 32 -c:a copy -ss 01:37:33 "!short!.nl.mp4"

rem ffmpeg.exe -hide_banner -y -ss 01:37:33 -t 00:01:09.5 -copyts -i "!full!" -c:v h264_nvenc -vf "scale=860:640:force_original_aspect_ratio=decrease,pad=860:640:-1:50:color=#ffffff,subtitles=f='!short!.srt':force_style='FontName=Arial,FontSize=32,Shadow=1'" -c:s mov_text -profile:v high -pix_fmt yuv420p -bufsize 20M -bf:v 3 -b:v 1M -preset slow -rc:v vbr_hq -rc-lookahead 32 -c:a copy -ss 01:37:33 "!short!.nl.w.mp4"

rem scale=1920:1080:force_original_aspect_ratio=decrease,pad=1920:1080:-1:-1:color=#242526,subti

rem ffmpeg -ss 25:00 -to 26:00 -copyts -i vid.mp4 -vf subtitles=sub.srt  -c:a copy -ss 25:00 -y final.mp4


exit /b
