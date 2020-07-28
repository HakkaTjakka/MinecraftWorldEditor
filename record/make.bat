rem ffmpeg -i pacman.mp3 -i pacman.mp3 -filter_complex [0:a][1:a]concat=n=2:v=0:a=1 pac_long.mp3
rem ffmpeg -i pac_long.mp3 -i pac_long.mp3 -filter_complex [0:a][1:a]concat=n=2:v=0:a=1 pac_long2.mp3
rem ffmpeg -i pac_long2.mp3 -i pac_long2.mp3 -filter_complex [0:a][1:a]concat=n=2:v=0:a=1 pac_long3.mp3
rem ffmpeg -i pac_long3.mp3 -i pac_long3.mp3 -filter_complex [0:a][1:a]concat=n=2:v=0:a=1 pac_long4.mp3

rem call add_mp3 pacman.mp3 output1544383459.mp4 output_sound.mp4

rem call add_mp3 dark.mp3 out1.mp4 out1_sound.mp4
rem call add_mp3 rain.mp3 out2.mp4 out2_sound.mp4
rem call add_mp3 dark.mp3 out3.mp4 out3_sound.mp4
rem call add_mp3 rain.mp3 out4.mp4 out4_sound.mp4


rem echo file 'win.mp4' > list.txt
rem echo file 'win.mp4' >> list.txt
rem echo file 'win.mp4' >> list.txt
rem echo file 'win.mp4' >> list.txt
rem echo file 'win.mp4' >> list.txt
rem echo file 'win.mp4' >> list.txt
rem ffmpeg -safe 0 -f concat -i list.txt -c copy win2.mp4

rem call add_mp3 pacman.mp3 output1544641593.mp4 output_sound.mp4

rem ffmpeg  -i kip.mp3 -i output1545372728.mp4 -shortest -codec copy kip_sound.mp4
rem ffmpeg -i frans.mp3 -i output1545403200.mkv  -codec copy frans_sound.mkv

rem ffmpeg -f concat -i list.txt -c copy longsong.mp3

rem ffmpeg -i list.txt -filter_complex concat song_long.mp3
rem ffmpeg -i list.txt -codec copy song_long.mp3


rem call ffmpeg -i 1.mp3 -i 2.mp3 -i 3.mp3 -i 4.mp3 -i 5.mp3 -i 6.mp3 -i 7.mp3 -filter_complex [0:a][1:a][2:a][3:a][4:a][5:a][6:a]concat=n=7:v=0:a=1 long_song.mp3
rem ffmpeg  -i long_song.mp3 -i output1545506159.mp4 -shortest -codec copy babe_sound.mp4

rem ffplay Scan-130929-0001a.pdf

rem ffmpeg -r 1/5 -i image%03d.png -c:v libx264 -r 30 -pix_fmt yuv420p out.mp4

rem ffmpeg  -i long.mp3 -i output1545670723.mp4 -shortest -codec copy holland_sound.mp4

rem ffmpeg  -i long.mp3 -i output1545670723.mp4 -codec copy holland_sound.mp4
rem ffmpeg  -i pacman.mp3 -i output1546055522.mp4 -codec copy mam_sound.mp4

rem -filter:v "minterpolate='mi_mode=mci:mc_mode=aobmc:vsbmc=1:fps=120'"

rem ffmpeg -i output1546748971.mp4 -c copy -f image2pipe - | ffmpeg -f image2pipe -framerate 25 -i - -c copy out.mp4
rem ffmpeg -i output1546748971.mp4 -c copy -f image2pipe - | ffmpeg -f image2pipe -framerate 25 -i - -c copy out.mp4
rem ffmpeg -i output1546748971.mp4 -c copy -f image2pipe - | ffmpeg -framerate 25 -i - -c copy out.mp4

rem ffmpeg -i output1546748971.mp4 -filter:v "setpts=1.2*PTS" output.mp4

rem ffmpeg -y -r 24 -i output1546748971.mp4 -c copy out.mp4
rem ffmpeg -y -r 20 -i output1546748971.mp4 -framerate 20 -c copy out.mp4
rem ffmpeg -i output1546748971.mp4 -vf setpts=(1.5)*PTS out.mp4
rem ffmpeg -i output1546748971.mp4 -c copy -an -video_track_timescale 20 out.mp4

rem ffmpeg  -y -ss 00:01:00 -i red.webm -i output1547955844.mp4 -shortest -codec copy redpillyellowvest.mp4


rem ffmpeg -i output1548035206.mp4 -vf setpts=(1.5)*PTS out.mp4
rem ffmpeg -i output1548035206.mp4 -c copy -an -video_track_timescale 45 out.mp4
rem ffmpeg -y -r 60 -i output1548035206.mp4 -framerate 45 -c copy out.mp4


rem ffmpeg -i output1548035206.mp4 -c copy -an -video_track_timescale 45 in45.mp4 > null
rem ffmpeg -f lavfi -i color=s=1920x1080:r=45:d=1 -profile:v main -video_track_timescale 45 0.mp4
rem echo file '0.mp4' > list.txt
rem echo file 'in45.mp4' >> list.txt
rem ffmpeg -f concat -i list.txt -c copy -video_track_timescale 45 45fps.mp4
rem ffmpeg -ss 1.1 -i 45fps.mp4 -c copy -avoid_negative_ts make_zero in45.mp4

rem goed
rem ffmpeg -y -i output1548035206.mp4 -c copy -f h264 out_tussen.h264
rem ffmpeg -y -r 45 -i out_tussen.h264 -c copy out.mp4

rem ffmpeg -i output1548814314.mp4 -filter:v "crop=1200:1080:360:0"  edo_cut.mp4

pause
