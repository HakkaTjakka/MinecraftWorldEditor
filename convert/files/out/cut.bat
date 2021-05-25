rem ffmpeg -i "Dr. Robert O. Young ITNJ Testimony-gKjnEz5s37o.en.mp4" -ss 01:32:13 -async 1 -c:v h264_nvenc -profile:v high -pix_fmt yuv420p -bufsize 20M -bf:v 3 -preset slow -rc:v vbr_hq -rc-lookahead 32 "Dr. Robert O. Young ITNJ Testimony-gKjnEz5s37o.en.cut.mp4"
rem ffmpeg -i "Dr. Robert O. Young ITNJ Testimony-gKjnEz5s37o.en.cut.mp4" -t 00:05:57 -c copy "Dr. Robert O. Young ITNJ Testimony-gKjnEz5s37o.en.cut2.mp4"
rem ffmpeg -i "Dr. Robert O. Young ITNJ Testimony-gKjnEz5s37o.nl.mp4" -ss 01:32:13 -async 1 -c:v h264_nvenc -profile:v high -pix_fmt yuv420p -bufsize 20M -bf:v 3 -preset slow -rc:v vbr_hq -rc-lookahead 32 "Dr. Robert O. Young ITNJ Testimony-gKjnEz5s37o.nl.cut.mp4"
rem ffmpeg -i "Dr. Robert O. Young ITNJ Testimony-gKjnEz5s37o.nl.cut.mp4" -t 00:05:57 -c copy "Dr. Robert O. Young ITNJ Testimony-gKjnEz5s37o.nl.cut2.mp4"

ffmpeg -y -hide_banner -i "Dr. Robert O. Young ITNJ Testimony-gKjnEz5s37o.nl.cut2.mp4" -async 1 -c:v h264_nvenc -profile:v high -pix_fmt yuv420p -bufsize 20M -b:v 10K -bf:v 3 -preset slow -rc:v vbr_hq -rc-lookahead 32 -c:a aac -b:a 64k "Dr. Robert O. Young ITNJ Testimony-gKjnEz5s37o.nl.cut3.mp4"

pause
