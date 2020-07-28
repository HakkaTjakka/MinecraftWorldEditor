ffmpeg -i pacman.mp3 -i pacman.mp3 -filter_complex [0:a][1:a]concat=n=2:v=0:a=1 pac_long.mp3
rem ffmpeg -i pac_long.mp3 -i pac_long.mp3 -filter_complex [0:a][1:a]concat=n=2:v=0:a=1 pac_long2.mp3
rem ffmpeg -i pac_long2.mp3 -i pac_long2.mp3 -filter_complex [0:a][1:a]concat=n=2:v=0:a=1 pac_long3.mp3
rem call add_mp3 pac_long3.mp3 output1540952670.mp4 output1.mp4
call add_mp3 pac_long.mp3 output1543277653.mp4 output_sound.mp4

pause