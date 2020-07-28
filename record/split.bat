rem ffmpeg -ss 00:00:00 -t 00:30:00 -i output1544324787.mp4 -vcodec copy -acodec copy out1.mp4
rem ffmpeg -ss 00:30:00 -t 00:30:00 -i output1544324787.mp4 -vcodec copy -acodec copy out2.mp4
rem ffmpeg -ss 01:00:00 -t 00:30:00 -i output1544324787.mp4 -vcodec copy -acodec copy out3.mp4
rem ffmpeg -ss 01:30:00 -t 00:30:00 -i output1544324787.mp4 -vcodec copy -acodec copy out4.mp4
rem ffmpeg -ss 00:04:22 -t 00:00:30 -i Mental.mp4 -vcodec copy -acodec copy mental_out.mp4



rem ffmpeg -ss 00:00:00 -t 00:30:00 -i output1544408340.mp4 -vcodec copy -acodec copy out5.mp4
rem ffmpeg -ss 00:30:00 -t 00:30:00 -i output1544408340.mp4 -vcodec copy -acodec copy out6.mp4
rem ffmpeg -ss 01:00:00 -t 00:30:00 -i output1544408340.mp4 -vcodec copy -acodec copy out7.mp4
rem ffmpeg -ss 01:30:00 -t 00:30:00 -i output1544408340.mp4 -vcodec copy -acodec copy out8.mp4
rem ffmpeg -ss 02:00:00             -i output1544408340.mp4 -vcodec copy -acodec copy out9.mp4

rem ffmpeg -ss 00:00:00 -t 00:35:00 -i output1558560271.mp4 -vcodec copy -acodec copy outcut.mp4

ffmpeg -ss 00:00:00 -t 00:30:00 -i out.mp4 -vcodec copy -acodec copy outcut2.mp4
ffmpeg -ss 00:30:00 -t 00:30:00 -i out.mp4 -vcodec copy -acodec copy outcut3.mp4
ffmpeg -ss 01:00:00 -t 00:30:00 -i out.mp4 -vcodec copy -acodec copy outcut4.mp4
pause
