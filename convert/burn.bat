@echo off

rem ffmpeg.exe -v 0 -hide_banner -i "filein.mp4" -c:v h264_nvenc -vf "scale=1920:1080:-1,subtitles=f='subtitles.srt':force_style='FontName=Arial,FontSize=24,Shadow=1'" -c:s mov_text -profile:v high -pix_fmt yuv420p -b:v 10M -bufsize 20M -bf:v 3 -preset slow -rc:v vbr_hq -rc-lookahead 32  -c:a copy "outfile"

rem  -b:v 10M
ffmpeg.exe -hide_banner -i "hoe lang nog.mkv" -c:v h264_nvenc -vf "scale=1920:1080:-1,subtitles=f='hoe lang nog.srt':force_style='FontName=Arial,FontSize=24,Shadow=1'" -c:s mov_text -profile:v high -pix_fmt yuv420p -bufsize 20M -bf:v 3 -preset slow -rc:v vbr_hq -rc-lookahead 32 -c:a copy "hoe lang nog.nl.2.mp4"

pause

