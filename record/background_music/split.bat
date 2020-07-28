rem ffmpeg -ss 00:00:00 -t 00:30:00 -i output1544324787.mp4 -vcodec copy -acodec copy out1.mp4
rem ffmpeg -ss 00:30:00 -t 00:30:00 -i output1544324787.mp4 -vcodec copy -acodec copy out2.mp4
rem ffmpeg -ss 01:00:00 -t 00:30:00 -i output1544324787.mp4 -vcodec copy -acodec copy out3.mp4
rem ffmpeg -ss 01:30:00 -t 00:30:00 -i output1544324787.mp4 -vcodec copy -acodec copy out4.mp4
rem ffmpeg -ss 00:04:22 -t 00:00:30 -i Mental.mp4 -vcodec copy -acodec copy mental_out.mp4



rem ffmpeg -i rain.mp3 -i dark.mp3 -i night.mp3 -i rain.mp3 -i dark.mp3 -i night.mp3 -filter_complex [0:a][1:a][2:a][3:a][4:a][5:a]concat=n=6:v=0:a=1 long_song.mp3
rem ffmpeg  -i long_song.mp3 -i hp.mp4 -shortest -codec copy hp_sound.mp4

rem ffmpeg -ss 00:00:00 -t 00:30:00 -i hp_sound.mp4 -vcodec copy -acodec copy out1.mp4
rem ffmpeg -ss 00:30:00 -t 00:30:00 -i hp_sound.mp4 -vcodec copy -acodec copy out2.mp4
rem ffmpeg -ss 01:00:00 -t 00:30:00 -i hp_sound.mp4 -vcodec copy -acodec copy out3.mp4
rem ffmpeg -ss 01:30:00 -t 00:30:00 -i hp_sound.mp4 -vcodec copy -acodec copy out4.mp4
rem ffmpeg -ss 02:00:00 -t 00:30:00 -i hp_sound.mp4 -vcodec copy -acodec copy out5.mp4
rem ffmpeg -ss 02:30:00 -t 00:30:00 -i hp_sound.mp4 -vcodec copy -acodec copy out6.mp4
rem ffmpeg -ss 03:00:00 -t 00:30:00 -i hp_sound.mp4 -vcodec copy -acodec copy out7.mp4
ffmpeg -ss 03:30:00 -t 00:31:17 -i hp_sound.mp4 -vcodec copy -acodec copy out8.mp4
