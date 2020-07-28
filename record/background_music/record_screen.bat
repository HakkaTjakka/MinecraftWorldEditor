@echo off
rem @ffmpeg -y -framerate 1 -hide_banner -f dshow -i video="screen-capture-recorder":audio="Microfoon (HD Webcam C310)" -r 1 -vf settb=\(1/60\),setpts=N/TB/60 -r 60 -c:v libx264 -preset veryfast -crf 23 -c:a copy -pix_fmt yuv420p 	output.mp4
rem @ffmpeg -y -framerate 1 -hide_banner -f dshow -i video="screen-capture-recorder":audio="Microfoon (HD Webcam C310)" -r 1 -an -vf settb=\(1/60\),setpts=N/TB/60 -r 60 -c:v libx264 -preset veryfast -crf 23 -c:a copy -pix_fmt yuv420p output.mp4
rem ffmpeg -y  -framerate 1 -hide_banner -f dshow -i video="screen-capture-recorder" -r 1 -an -vf settb=\(1/30\),setpts=N/TB/30 -c:v libx264 -preset veryfast -crf 23 -pix_fmt yuv420p 	output12.mp4
rem ffmpeg -y  -framerate 1 -hide_banner -f dshow -i video="screen-capture-recorder" -r 1 -an -vf settb=\(1/30\),setpts=N/TB/30 -c:v libx264 -preset veryfast -crf 23 -an -pix_fmt yuv420p 	output12.mp4
rem ffmpeg -y -framerate 1 -hide_banner -f dshow -i video="screen-capture-recorder" -r 1 -an -vf settb=\(1/60\),setpts=N/TB/60 -r 60 -c:v libx264 -preset veryfast -crf 23 -c:a copy -pix_fmt yuv420p output.mp4
rem ffmpeg -y -framerate 60 -hide_banner -f dshow -i video="screen-capture-recorder" -r 60 -an -c:v libx264 -preset veryfast -crf 23 -pix_fmt yuv420p output.mp4
rem ffmpeg -y -framerate 1 -hide_banner -f dshow -i video="screen-capture-recorder" -r 1 -an -vf settb=\(1/60\),setpts=N/TB/60 -r 60 -c:v libx264 -preset veryfast -crf 23 -c:a copy -pix_fmt yuv420p output.mp4
rem ffmpeg -y -framerate 30 -hide_banner -f dshow -i video="screen-capture-recorder" -an -r 30 -vf settb=\(1/30\),setpts=N/TB/30 -c:v libx264 -preset veryfast -crf 23 -an -pix_fmt yuv420p 	output.mp4
rem ffmpeg -y  -framerate 30 -hide_banner -f dshow -i video="screen-capture-recorder" -an -r 30 -vf settb=\(1/30\),setpts=N/TB/30 -c:v libx264 -preset veryfast -crf 23 -an -pix_fmt yuv420p 	output.mp4
rem ffmpeg -y -framerate 30 -hide_banner -f dshow -i video="screen-capture-recorder" -an -r 30 -c:v libx264 -preset ultrafast -crf 23 -pix_fmt yuv420p output.mp4
rem ffmpeg -y -rtbufsize 1000M -framerate 30 -hide_banner -f dshow -i video="screen-capture-recorder" -an -r 30 -c:v h264_nvenc -profile:v high -pixel_format nv12 -b:v 10000k -preset slow -bf:v 2 -rc vbr_hq -rc-lookahead 32 -movflags +faststart output.mp4
rem ffmpeg -i output.mp4 -vf "select=gt(scene\,0.003),setpts=N/(60*TB)" -c:v h264_nvenc -profile:v high -pixel_format nv12 -b:v 14000k -preset slow -bf:v 2 -rc vbr_hq -rc-lookahead 32 output2.mp4
rem ffmpeg -y -rtbufsize 1000M -framerate 30 -hide_banner -f dshow -i video="screen-capture-recorder" -r 30 -vf settb=\(30/60\),setpts=N/TB/30 -r 30 -c:v h264_nvenc -profile:v high -pixel_format nv12 -b:v 14000k -preset slow -bf:v 2 -rc vbr_hq -rc-lookahead 32 output.mp4
rem ffmpeg -y -rtbufsize 1000M -hide_banner -f dshow -i video="screen-capture-recorder" -c:v h264_nvenc -profile:v high -pixel_format nv12 -b:v 14000k -preset slow -bf:v 2 -rc vbr_hq -rc-lookahead 32 output.mp4
rem ffmpeg -y -framerate 30 -rtbufsize 1000M -hide_banner -f dshow -i video="screen-capture-recorder" -c:v h264_nvenc -profile:v high -pixel_format nv12 -b:v 14000k -preset slow -bf:v 2 -rc vbr_hq -rc-lookahead 32 -vsync 0 output.mp4
rem ffmpeg -y -framerate 60 -f gdigrab -i desktop -vf mpdecimate,setpts=N/FRAME_RATE/TB -c:v h264_nvenc -profile:v high -pixel_format nv12 -b:v 14000k -preset slow -bf:v 2 -rc vbr_hq -rc-lookahead 32 output.mp4
rem ffmpeg -y -framerate 60 -f gdigrab -i desktop -c:v h264_nvenc -profile:v high -pixel_format nv12 -b:v 14000k -preset slow -bf:v 2 -rc vbr_hq -rc-lookahead 32 output.mp4
rem -f rawvideo -vcodec rawvideo -pix_fmt rgb24
rem ffmpeg -y -framerate 60 -f gdigrab -i desktop -vf mpdecimate,setpts=N/FRAME_RATE/TB -c:v h264_nvenc -profile:v high -pixel_format nv12 -b:v 8000k -preset slow -bf:v 3 -rc vbr_hq -rc-lookahead 32 -r 60 output.mp4
rem ffmpeg -y -framerate 60 -f gdigrab -i title=Pacman_Graphics -vf mpdecimate,setpts=N/FRAME_RATE/TB -c:v h264_nvenc -profile:v high -pixel_format nv12 -b:v 8000k -preset slow -bf:v 3 -rc vbr_hq -rc-lookahead 32 -r 60 output.mp4

rem ffmpeg -y -framerate 60 -f gdigrab -i title="Pacman_Graphics" -vf mpdecimate,setpts=N/FRAME_RATE/TB -c:v h264_nvenc -profile:v high -pixel_format nv12 -b:v 8000k -preset slow -bf:v 3 -rc vbr_hq -rc-lookahead 32 -r 60 output.mp4
rem ffmpeg -y -framerate 60 -f gdigrab -i title="OpenJDK Platform binary" -vf mpdecimate,setpts=N/FRAME_RATE/TB -c:v h264_nvenc -profile:v high -pixel_format nv12 -b:v 8000k -preset slow -bf:v 3 -rc vbr_hq -rc-lookahead 32 -r 60 output.mp4

rem ffmpeg -y -framerate 60 -f gdigrab -i title="Minecraft 1.14.4" -vf mpdecimate,setpts=N/FRAME_RATE/TB -c:v h264_nvenc -profile:v high -pixel_format nv12 -b:v 14000k -preset slow -bf:v 3 -rc vbr_hq -rc-lookahead 32 -r 60 -qp 0 output.mp4
rem ffmpeg -y -framerate 60 -f gdigrab -i desktop -vf mpdecimate,setpts=N/FRAME_RATE/TB -c:v h264_nvenc -profile:v high -pixel_format nv12 -b:v 8000k -preset slow -bf:v 3 -rc vbr_hq -rc-lookahead 32 -r 60 -qp 0 output.mp4

rem ffmpeg -y -framerate 60 -f gdigrab -i title="Minecraft 1.14.4" -vf mpdecimate,setpts=N/FRAME_RATE/TB -c:v h264_nvenc -profile:v high -pixel_format nv12 -b:v 10000k -preset slow -bf:v 2 -rc vbr_hq -rc-lookahead 32 -r 60 output.mp4
rem ffmpeg -y -framerate 60 -f gdigrab -i title="Minecraft 1.14.4" -vf mpdecimate,setpts=N/FRAME_RATE/TB -filter:v minterpolate -c:v h264_nvenc -profile:v high -pixel_format nv12 -b:v 10000k -preset slow -bf:v 2 -rc vbr_hq -rc-lookahead 32 -r 60 output.mp4

rem ffmpeg -y -framerate 60 -f gdigrab -i title="Minecraft 1.14.4" -vf mpdecimate,setpts=N/FRAME_RATE/TB -c:v h264_nvenc -profile:v high -pixel_format nv12 -b:v 10000k -preset slow -bf:v 2 -rc vbr_hq -rc-lookahead 32 -r 60 output.mp4

rem ffmpeg -y -framerate 60 -f gdigrab -i desktop -c:v h264_nvenc -profile:v high -pixel_format nv12 -b:v 10000k -preset slow -bf:v 2 -rc vbr_hq -rc-lookahead 32 -r 60 output2.mp4

rem ffmpeg -y -framerate 20 -f gdigrab -i desktop -vf mpdecimate,setpts=N/FRAME_RATE/TB -c:v h264_nvenc -profile:v high -pixel_format nv12 -b:v 10000k -preset slow -bf:v 2 -rc vbr_hq -rc-lookahead 32 -r 60 output3.mp4

rem ffmpeg -y -framerate 10 -f gdigrab -i desktop -vf mpdecimate,setpts=N/FRAME_RATE/TB -c:v h264_nvenc -profile:v high -pixel_format nv12 -b:v 10000k -preset slow -bf:v 2 -rc vbr_hq -rc-lookahead 32 -r 60 output4.mp4

rem ffmpeg -y -framerate 60 -f gdigrab -i desktop -c:v h264_nvenc -profile:v high -pixel_format nv12 -b:v 10000k -preset slow -bf:v 2 -rc vbr_hq -rc-lookahead 32 -r 60 output7.mp4

rem ffmpeg -y -framerate 60 -f gdigrab -i title="Minecraft 1.14.4" -c:v h264_nvenc -profile:v high -pixel_format nv12 -b:v 10000k -preset slow -bf:v 2 -rc vbr_hq -rc-lookahead 32 -r 60 output2.mp4

rem ffmpeg -y -i output.mp4 -filter:v minterpolate -r 60 hop.mp4
rem -filter:v minterpolate 

rem ffmpeg -i output6.mp4 -vf "tblend=average,framestep=2,tblend=average,framestep=2,tblend=average,framestep=2,tblend=average,framestep=2,setpts=0.25*PTS" -c:v h264_nvenc -profile:v high -pixel_format nv12 -b:v 10000k -preset slow -bf:v 2 -rc vbr_hq -rc-lookahead 32 -r 60 -b:v 30M -an output6b.mp4

rem ffmpeg -y -framerate 60 -f gdigrab -i title="Minecraft 1.14.4" -vf mpdecimate,setpts=N/FRAME_RATE/TB -c:v h264_nvenc -profile:v high -pixel_format nv12 -b:v 10000k -preset slow -bf:v 2 -rc vbr_hq -rc-lookahead 32 -r 60 output7.mp4

rem ffmpeg -y -ss 00:01:36 -i test1.mp4 -vf scale=1920:1080:-1 -c:v libx264 -preset veryfast -crf 23 -pix_fmt yuv420p test1b.mp4

rem ffmpeg -y -ss 00:02:14 -i test1.mp4 -vf scale=1920:1080:-1 -c:v h264_nvenc -profile:v high -pixel_format nv12 -b:v 10000k -preset slow -bf:v 2 -rc vbr_hq -rc-lookahead 32 test1c.mp4

rem ffmpeg -y -ss 00:33:00 -i trance.mp3 -ss 00:00:38 -i test1b.mp4 -shortest -c:a aac -b:a 96k -vcodec copy test1c.mp4
rem ffmpeg -y -ss 00:23:00 -i trance.mp3 -i 2019_09_25_00_34_01.mp4 -shortest -c:a aac -b:a 96k -c:v libx264 -preset veryfast -crf 23 -pix_fmt yuv420p out_360_2.mp4


rem ffmpeg -y -framerate 60 -f gdigrab -i title="Minecraft 1.14.4" -vf mpdecimate,setpts=N/FRAME_RATE/TB -c:v h264_nvenc -profile:v high -pixel_format nv12 -b:v 20000k -bufsize 40000k -preset slow -bf:v 2 -rc:v vbr_hq -cq:v 19 -rc-lookahead 32 -r 60 recording_high.mp4
rem ffmpeg -y -vsync 0 -framerate 60 -f gdigrab -i title="Minecraft 1.14.4" -vf mpdecimate,setpts=N/FRAME_RATE/TB -c:v h264_nvenc -profile:v high -pixel_format nv12 -b:v 20000k -bufsize 40000k -bf:v 2 -preset llhq -rc:v constqp -qp 19 -rc-lookahead 32 -r 60 recording_high.mp4
																									 rem -c:v h264_nvenc  -b:v 2500k -maxrate:v 5000k -profile:v high
																									 rem -preset llhq -rc constqp -qp 21

rem ffmpeg -y -vsync 0 -framerate 60 –hwaccel cuvid -c:v h264_cuvid –resize 1920x1080 -f gdigrab -i title="Minecraft 1.14.4" -vf mpdecimate,setpts=N/FRAME_RATE/TB -c:v h264_nvenc -profile:v high -pixel_format nv12 -b:v 20000k -bufsize 40000k -bf:v 2 -preset llhq -rc:v constqp -qp 19 -rc-lookahead 32 -r 60 recording_high.mp4
rem ffmpeg -y -hwaccel cuvid -framerate 60 -f gdigrab -i title="Minecraft 1.14.4" -vf mpdecimate,setpts=N/FRAME_RATE/TB -filter:v scale=w=1920:h=1080 -c:v h264_nvenc -profile:v high -pixel_format nv12 -b:v 12000k -bufsize 24000k -bf:v 2 -preset llhq -rc:v constqp -qp 19 -rc-lookahead 32 -r 60 recording_high.mp4
rem ffmpeg -y -hwaccel cuvid -framerate 60 -f gdigrab -i title="Minecraft 1.14.4" -vf mpdecimate,setpts=N/FRAME_RATE/TB -c:v h264_nvenc -profile:v high -pixel_format nv12 -b:v 12000k -bufsize 24000k -bf:v 2 -preset llhq -rc:v constqp -qp 19 -rc-lookahead 32 -r 60 -resize 1920x1080 recording_high.mp4
rem ffmpeg -y -hwaccel cuvid -framerate 60 -f gdigrab -i title="Minecraft 1.14.4" -vf mpdecimate,setpts=N/FRAME_RATE/TB -c:v h264_nvenc -profile:v high -pixel_format yuv420p -b:v 12000k -bufsize 24000k -bf:v 2 -preset llhq -rc:v constqp -qp 19 -rc-lookahead 32 -r 60 recording_high.mp4
rem ffmpeg -y -framerate 60 -f gdigrab -i title="Minecraft 1.14.4" -vf mpdecimate,setpts=N/FRAME_RATE/TB -s 1920x1080 -c:v h264_nvenc -profile:v high -pixel_format nv12 -b:v 10000k -bufsize 20000k -bf:v 2 -preset slow -rc:v vbr_hq -rc-lookahead 20 -r 60 recording_high.mp4
rem ffmpeg -y -framerate 60 -f gdigrab -i title="Minecraft 1.14.4" -vf mpdecimate,setpts=N/FRAME_RATE/TB -c:v h264_nvenc -profile:v high -pixel_format nv12 -b:v 10000k -bufsize 20000k -bf:v 2 -preset llhq -rc:v vbr_hq -rc-lookahead 20 -r 60 recording_high.mp4
rem -hwaccel cuvid -c:v h264_cuvid
rem –vf scale_npp=1280:720

rem *****************************
rem ffmpeg -y -framerate 60 -f gdigrab -i title="Minecraft 1.14.4" -vf mpdecimate,setpts=N/FRAME_RATE/TB -s 1920x1080 -c:v libx264 -preset ultrafast -crf 23 -an -pix_fmt yuv420p -r 60 recording_high2.mp4
rem ffmpeg -y -framerate 60 -f gdigrab -i title="Minecraft 1.14.4" -vf mpdecimate,setpts=N/FRAME_RATE/TB -s 1920x1080 -c:v h264_nvenc -profile:v high -pixel_format nv12 -b:v 10000k -bufsize 20000k -bf:v 2 -preset slow -rc:v vbr_hq -rc-lookahead 20 -r 60 recording_high3.mp4
rem *****************************


rem ffmpeg -y  -framerate 60 -f gdigrab -i title="Minecraft 1.14.4" -vf mpdecimate,setpts=N/FRAME_RATE/TB -s 1920x1080 -c:v h264_nvenc -b:v 4M -maxrate:v 5M -bufsize:v 8M -profile:v main -level:v 4.1 -rc:v vbr_hq -rc-lookahead:v 32 -refs:v 16 -bf:v 3 -coder:v cabac -b_ref_mode:v middle -f mp4 -r 60 recording_high3.mp4



rem ffmpeg.exe -y -framerate 60 -f gdigrab -i title="Minecraft 1.14.4" -vf mpdecimate,setpts=N/FRAME_RATE/TB -s 1920x1080 -c:v h264_nvenc -preset llhq -profile:v high -rc ll_2pass_quality -an -b:v 10M -pass 1 -2pass -1 -r 60 recording_high3.mp4



rem -b:v 4M -maxrate:v 5M -bufsize:v 8M -profile:v main -level:v 4.1 -rc:v vbr_hq -rc-lookahead:v 32 -refs:v 16 -bf:v 3 -coder:v cabac -b_ref_mode:v middle -f mp4

rem ffmpeg -loglevel debug -threads 4 -hwaccel cuvid -c:v h264_cuvid -i "e:\input.ts" \
rem -filter:v hwupload_cuda,scale_npp=w=1920:h=1080:interp_algo=lanczos \
rem -c:v h264_nvenc -b:v 4M -maxrate:v 5M -bufsize:v 8M -profile:v main \
rem -level:v 4.1 -rc:v vbr_hq -rc-lookahead:v 32 -refs:v 16 \
rem -bf:v 3 -coder:v cabac -b_ref_mode:v middle \
rem -f mp4 "e:\output.mp4"

rem ffmpeg -y -framerate 60 -f gdigrab -i title="Minecraft 1.14.4" -vf mpdecimate,setpts=N/FRAME_RATE/TB -s 1920x1080 -c:v h264_nvenc -profile:v high -pixel_format nv12 -b:v 8M -bufsize 16M -bf:v 3 -preset slow -rc:v vbr_hq -rc-lookahead 32 -r 60 recording_high3.mp4
ffmpeg -y -framerate 60 -f gdigrab -i title="Minecraft 1.14.4" -vf mpdecimate,setpts=N/FRAME_RATE/TB -s 1920x1080 -c:v h264_nvenc -profile:v high -pixel_format nv12 -bf:v 3 -preset slow -rc:v vbr_hq -rc-lookahead 32 -r 60 recording_high3.mp4

rem ffmpeg -y -i recording_high2.mp4 -filter:v hwupload_cuda -c:v h264_nvenc -profile:v high -pixel_format nv12 -bf:v 3 -preset slow -b:v 6M -bufsize 12M -rc:v vbr_hq -rc-lookahead 32 -coder:v cabac recording_low2.mp4
rem ffmpeg -y -framerate 60 -f gdigrab -i title="Minecraft 1.14.4" -vf mpdecimate,setpts=N/FRAME_RATE/TB -s 1920x1080 -c:v libx264 -preset ultrafast -crf 23 -an -pix_fmt yuv420p -r 60 recording_high2.mp4

pause