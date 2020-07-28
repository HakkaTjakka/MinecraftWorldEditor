@echo off

rem youtube-dl --extract-audio PLDGvrCyjfEau0spRkUDVKh5JlVbsZ-Kke

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

rem ffmpeg -safe 0 -f concat -i list.txt -c copy long.mp3

rem ffmpeg -i output1544936155.mp4 -ss 00:00:00 -t 00:34:00  -c copy out11.mp4
rem ffmpeg -i output1544936155.mp4 -ss 00:34:00 -t 00:34:00  -c copy out12.mp4
rem ffmpeg -i output1544936155.mp4 -ss 01:08:00 -t 00:34:00  -c copy out13.mp4
rem ffmpeg -i output1544936155.mp4 -ss 01:42:00 -t 00:35:50  -c copy out14.mp4

rem ffmpeg -i output1544936155.mp4 -ss 00:00:00 -t 00:34:00  -vcodec copy -acodec copy out11.mp4
rem ffmpeg -i output1544936155.mp4 -ss 00:34:00 -t 00:34:00  -vcodec copy -acodec copy out12.mp4
rem ffmpeg -i output1544936155.mp4 -ss 01:08:00 -t 00:34:00  -vcodec copy -acodec copy out13.mp4
rem ffmpeg -i output1544936155.mp4 -ss 01:42:00 -t 00:35:50  -vcodec copy -acodec copy out14.mp4

rem ffmpeg -fflags +igndts -i out2_sound.mp4 -map 0:0 -map 0:2 -c:v copy -c:a copy out2_sound_fixed.mp4
rem call add_mp3 long.mp3 output1544936155.mp4 part_3_sound.mp4
rem call add_mp3 dark.mp3 out1.mp4 out1_sound.mp4
rem ffmpeg -i %1 -i %2 -shortest -codec copy %3


rem ffmpeg -ss 00:00:00 -i long.mp3 -i out11.mp4 -shortest -codec copy out11_sound.mp4
rem ffmpeg -ss 00:34:00 -i long.mp3 -i out12.mp4 -shortest -codec copy out12_sound.mp4
rem ffmpeg -ss 01:08:00 -i long.mp3 -i out13.mp4 -shortest -codec copy out13_sound.mp4
rem ffmpeg -ss 01:42:00 -i long.mp3 -i out14.mp4 -shortest -codec copy out14_sound.mp4


rem ffmpeg -ss 00:01:30 -i old.mp3 -i output1545284687.mp4 -shortest -codec copy cb.mp4

rem ffmpeg -i list.txt i%.mp3"

rem for f in *.mp4; do ffmpeg -i "$f" "${f%.mp4}.mp3"; done


rem ffmpeg -i output1546748971.mp4 -i long_song.mp3 -shortest -codec copy out_sound.mp4


rem fmpeg -i input.mp3 -c:a libfdk_aac output.m4a


rem ffmpeg -i dark.mp3  -i night.mp3 -i rain.mp3 -i dark.mp3 -i night.mp3  -filter_complex [0:a][1:a][2:a][3:a][4:a]concat=n=5:v=0:a=1  long_song.mp3

rem -acodec copy -avoid_negative_ts make_zero

rem ffmpeg -y -i out.mp4 -ss 00:00:00 -t 00:30:00  -an out1.mp4
rem https://github.com/mifi/lossless-cut/pull/13

rem ffmpeg -y -ss 00:00:00 -i out.mp4 -t 00:30:00  -an -vcodec copy out1.mp4
rem ffmpeg -y -ss 00:00:00 -i long_song.mp3 -i out1.mp4 -shortest -vcodec copy -c:a aac -b:a 64k out_sound1.mp4

rem ffmpeg -y -ss 00:30:00 -i out.mp4 -t 00:30:00  -an -vcodec copy out2.mp4
rem ffmpeg -y -ss 00:30:00 -i long_song.mp3 -i out2.mp4 -shortest -vcodec copy -c:a aac -b:a 64k out_sound2.mp4

rem ffmpeg -y -ss 01:00:00 -i out.mp4 -t 00:30:00  -an -vcodec copy out3.mp4
rem ffmpeg -y -ss 01:00:00 -i long_song.mp3 -i out3.mp4 -shortest -vcodec copy -c:a aac -b:a 64k out_sound3.mp4

rem ffmpeg -y -ss 01:30:00 -i out.mp4 -t 00:30:00  -an -vcodec copy out4.mp4
rem ffmpeg -y -ss 01:30:00 -i long_song.mp3 -i out4.mp4 -shortest -vcodec copy -c:a aac -b:a 64k out_sound4.mp4

rem ffmpeg -y -ss 02:00:00 -i out.mp4 -t 00:30:00  -an -vcodec copy out5.mp4
rem ffmpeg -y -ss 02:00:00 -i long_song.mp3 -i out5.mp4 -shortest -vcodec copy -c:a aac -b:a 64k out_sound5.mp4

rem ffmpeg -y -ss 02:30:00 -i out.mp4 -t 00:30:00  -an -vcodec copy out6.mp4
rem ffmpeg -y -ss 02:30:00 -i long_song.mp3 -i out6.mp4 -shortest -vcodec copy -c:a aac -b:a 64k out_sound6.mp4

rem ffmpeg -y -ss 03:00:00 -i out.mp4 -t 00:30:00  -an -vcodec copy out7.mp4
rem ffmpeg -y -ss 03:00:00 -i long_song.mp3 -i out7.mp4 -shortest -vcodec copy -c:a aac -b:a 64k out_sound7.mp4

rem ffmpeg -y -ss 03:30:00 -i out.mp4 -t 00:30:00  -an -vcodec copy out8.mp4
rem ffmpeg -y -ss 03:30:00 -i long_song.mp3 -i out8.mp4 -shortest -vcodec copy -c:a aac -b:a 64k out_sound8.mp4

rem ffmpeg -y -ss 04:00:00 -i out.mp4 -t 00:30:00  -an -vcodec copy out9.mp4
rem ffmpeg -y -ss 04:00:00 -i long_song.mp3 -i out9.mp4 -shortest -vcodec copy -c:a aac -b:a 64k out_sound9.mp4

rem ffmpeg -y -ss 04:30:00 -i out.mp4 -t 00:25:52  -an -vcodec copy out10.mp4
rem ffmpeg -y -ss 04:30:00 -i long_song.mp3 -i out10.mp4 -shortest -vcodec copy -c:a aac -b:a 64k out_sound10.mp4


rem ffmpeg -y -ss 00:41:11 -i relax.mp3 -i out.mp4 -shortest -vcodec copy -c:a aac -b:a 64k out_sound.mp4

rem ffmpeg -i out_sound.mp4 -filter_complex "afade=d=1.5, areverse, afade=d=1.5, areverse" -vcodec copy out_sound_fade.mp4


rem ffmpeg -i lie.mp3  -i long_song.mp3 -filter_complex [0:a][1:a]concat=n=2:v=0:a=1  long_song_lie.mp3

rem ffmpeg -y -ss 00:00:00 -i out.mp4 -t 01:00:00  -an -vcodec copy out1.mp4
rem ffmpeg -y -ss 00:00:00 -i long_song_lie.mp3 -i out1.mp4 -shortest -vcodec copy -c:a aac -b:a 64k out_sound1.mp4

rem ffmpeg -y -ss 01:00:00 -i out.mp4 -t 01:00:00  -an -vcodec copy out3.mp4
rem ffmpeg -y -ss 01:00:00 -i long_song_lie.mp3 -i out3.mp4 -shortest -vcodec copy -c:a aac -b:a 64k out_sound2.mp4

rem ffmpeg -y -ss 02:00:00 -i out.mp4 -t 01:00:00  -an -vcodec copy out5.mp4
rem ffmpeg -y -ss 02:00:00 -i long_song_lie.mp3 -i out5.mp4 -shortest -vcodec copy -c:a aac -b:a 64k out_sound3.mp4

rem ffmpeg -y -ss 03:00:00 -i out.mp4 -t 00:35:54  -an -vcodec copy out5.mp4
rem ffmpeg -y -ss 03:00:00 -i long_song_lie.mp3 -i out5.mp4 -shortest -vcodec copy -c:a aac -b:a 64k out_sound4.mp4

rem ffmpeg -y -ss 00:22:22 -i whale.mp3 -i out.mp4 -shortest -vcodec copy -c:a aac -b:a 64k out_sound.mp4
rem ffmpeg -i out_sound.mp4 -filter_complex "afade=d=1.5, areverse, afade=d=1.5, areverse" -vcodec copy out_sound_fade.mp4

rem ffmpeg -y -ss 00:00:00 -i out.mp4 -t 00:48:00  -an -vcodec copy out1.mp4
rem ffmpeg -y -ss 02:15:00 -i long_song_lie.mp3 -i out1.mp4 -shortest -vcodec copy -c:a aac -b:a 64k out_sound1.mp4

rem ffmpeg -y -ss 00:00:00 -i out.mp4 -t 01:03:00  -an -vcodec copy out1.mp4
rem ffmpeg -y -ss 00:00:00 -i long_song_lie.mp3 -i out1.mp4 -shortest -vcodec copy -c:a aac -b:a 64k out_sound1.mp4

rem ffmpeg -y -ss 01:03:00 -i out.mp4 -t 01:03:47  -an -vcodec copy out2.mp4
rem ffmpeg -y -ss 01:03:00 -i long_song_lie.mp3 -i out2.mp4 -shortest -vcodec copy -c:a aac -b:a 64k out_sound2.mp4

rem ffmpeg -y -ss 02:00:00 -i long_song_lie.mp3 -i out.mp4 -shortest -vcodec copy -c:a aac -b:a 64k out_sound3.mp4

rem ffmpeg -y -ss 01:00:00 -i long_song_lie.mp3 -i out1.mp4 -shortest -vcodec copy -c:a aac -b:a 64k out_sound1.mp4
rem ffmpeg -y -ss 02:00:00 -i long_song_lie.mp3 -i out2.mp4 -shortest -vcodec copy -c:a aac -b:a 64k out_sound2.mp4

rem ffmpeg -y -ss 00:00:00 -i out.mp4 -t 00:29:42  -an -vcodec copy out1.mp4
rem ffmpeg -y -ss 00:00:00 -i rain.mp3 -i out.mp4 -t 00:29:42 -shortest -vcodec copy -c:a aac -b:a 64k -filter_complex "afade=d=1.5, areverse, afade=d=1.5, areverse" out_sound1.mp4

rem ffmpeg -i out_sound1.mp4 -filter:v "crop=1920:960:0:80" -c:a copy out_sound_cut.mp4

rem ffmpeg -y -i out_sound_cut.mp4 -an -vcodec copy out_cut.mp4

rem ffmpeg -y -i mad.webm -i out1.mp4 -vcodec copy -c:a aac -b:a 128k out1_sound.mp4
rem ffmpeg -y -i mad.webm -i out2.mp4 -vcodec copy -c:a aac -b:a 128k out2_sound.mp4


rem ffmpeg -safe 0 -f concat -i list.txt -c copy long.mp4

rem ffmpeg -i out.mp4 -i mad.webm -shortest -strict -2 -codec copy out_sound.mp4

rem echo file 'out1.mp4' > list.txt
rem echo file 'out2.mp4' >> list.txt

rem ffmpeg -safe 0 -f concat -i list.txt -c copy rutte.mp4
rem ffmpeg -i rutte.mp4 -i pacman.mp3 -shortest -codec copy rutte_sound.mp4

rem ffmpeg -y -ss 00:00:00 -i out.mp4 -t 00:13:00  -an -vcodec copy out1.mp4
rem ffmpeg -y -i duivel.webm -i out.mp4 -shortest -vcodec copy -c:a aac -b:a 128k -filter_complex "afade=d=0.0, areverse, afade=d=4.5, areverse" out_sound.mp4


rem ffmpeg -y -ss 00:00:00 -i out.mp4 -t 00:15:00  -an -vcodec copy out1.mp4
rem ffmpeg -y -ss 00:00:00 -i megamix.webm -i out1.mp4 -shortest -vcodec copy -c:a aac -b:a 96k out_sound1.mp4

rem ffmpeg -y -ss 00:15:00 -i out.mp4 -t 00:15:00  -an -vcodec copy out2.mp4
rem ffmpeg -y -ss 01:00:00 -i megamix.webm -i out2.mp4 -shortest -vcodec copy -c:a aac -b:a 96k out_sound2.mp4

rem ffmpeg -y -ss 00:30:00 -i out.mp4 -t 00:15:00  -an -vcodec copy out3.mp4
rem ffmpeg -y -ss 00:00:00 -i sick.webm -i out.mp4 -shortest -vcodec copy -c:a aac -b:a 96k -filter_complex "afade=d=4.5, areverse, afade=d=4.5, areverse" out_sound.mp4


rem ffmpeg -y -ss 00:00:00 -i out.mp4 -t 00:01:28  -vcodec copy -acodec copy out1.mp4
rem ffmpeg -y -ss 00:00:00 -i sick.webm -i out1.mp4 -shortest -vcodec copy -c:a aac -b:a 96k -filter_complex "afade=d=4.5, areverse, afade=d=4.5, areverse" out_sound.mp4

rem ffmpeg -i klaasvaakmeniet.mp4 klaas.mp3
rem ffmpeg -i out.mp4 -itsoffset 0.2 -i klaas.mp3 -map 0:v -map 1:a -shortest -vcodec copy -c:a aac -b:a 96k klaas.mp4

rem fmpeg.exe -i "movie.mp4" -itsoffset 3.84 -i "movie.mp4" -map 0:v -map 1:a -c copy "movie-audio-delayed.mp4"

rem ffmpeg -y -ss 01:28:42 -i megamix.webm -i out.mp4 -shortest -vcodec copy -c:a aac -b:a 96k -filter_complex "afade=d=1.5, areverse, afade=d=2.5, areverse" out_sound.mp4

rem -vf "crop=w:h:x:y"
rem ffmpeg -i out.mp4 -filter:v "crop=1800:1080:60:0" -c:a copy out_cut.mp4

rem ffmpeg -y -ss 00:10:42 -i jazz.webm -i out.mp4 -shortest -vcodec copy -c:a aac -b:a 96k out_sound.mp4
rem ffmpeg -y -ss 00:20:42 -i jazz.webm -i out2.mp4 -shortest -vcodec copy -c:a aac -b:a 96k out2_sound.mp4

rem ffmpeg -y -ss 00:00:00 -i out.mp4 -t 00:20:00  -an -vcodec copy out1.mp4
rem ffmpeg -y -ss 00:00:00 -i jazz.webm -i out1.mp4 -shortest -vcodec copy -c:a aac -b:a 96k out_sound1.mp4

rem ffmpeg -y -ss 00:20:00 -i out.mp4 -t 00:21:09  -an -vcodec copy out2.mp4
rem ffmpeg -y -ss 00:20:00 -i jazz.webm -i out2.mp4 -shortest -vcodec copy -c:a aac -b:a 96k out_sound2.mp4

rem ffmpeg -y -ss 00:20:00 -i megamix.webm -i out.mp4 -shortest -vcodec copy -c:a aac -b:a 96k -filter_complex "afade=d=1.5, areverse, afade=d=2.5, areverse" out_sound.mp4

rem ffmpeg -y -ss 00:26:43 -i megamix.webm -i out.mp4 -shortest -vcodec copy -c:a aac -b:a 96k out_sound.mp4

rem ffmpeg -y -ss 00:33:56 -i summer.webm -i out.mp4 -shortest -vcodec copy -c:a aac -b:a 96k out_sound2.mp4

rem ffmpeg -i lie.mp3 -i megamix.webm -filter_complex [0:a][1:a]concat=n=2:v=0:a=1 lie_megamix.mp3

rem ffmpeg -y -ss 00:00:00 -i megamix.webm -i out.mp4 -shortest -vcodec copy -c:a aac -b:a 96k out_sound.mp4


rem ffmpeg -y -ss 00:10:00 -i jazz.webm -i out1.mp4 -shortest -vcodec copy -c:a aac -b:a 96k out_sound1.mp4
rem ffmpeg -y -ss 00:20:00 -i jazz.webm -i out2.mp4 -shortest -vcodec copy -c:a aac -b:a 96k out_sound2.mp4
rem ffmpeg -y -ss 00:30:00 -i jazz.webm -i out3.mp4 -shortest -vcodec copy -c:a aac -b:a 96k out_sound3.mp4
rem ffmpeg -y -ss 00:40:00 -i jazz.webm -i out4.mp4 -shortest -vcodec copy -c:a aac -b:a 96k out_sound4.mp4
rem ffmpeg -y -ss 00:00:00 -i relax.mp3 -i out5.mp4 -shortest -vcodec copy -c:a aac -b:a 96k out_sound5.mp4

rem ffmpeg -y -ss 00:00:00 -i summer.webm -i out6.mp4 -shortest -vcodec copy -c:a aac -b:a 96k out_sound6.mp4
rem ffmpeg -i 2.m4a -i 1.webm -filter_complex [0:a][1:a]concat=n=2:v=0:a=1 c1.mp3
rem ffmpeg -i c1.mp3 -i 3.webm -filter_complex [0:a][1:a]concat=n=2:v=0:a=1 c2.mp3
rem ffmpeg -i 1.webm -i c2.mp3 -filter_complex [0:a][1:a]concat=n=2:v=0:a=1 c3.mp3
rem ffmpeg -i c3.mp3 -i 3.webm -filter_complex [0:a][1:a]concat=n=2:v=0:a=1 c_final.mp3

rem ffmpeg -y -ss 00:00:00 -i jazz.webm -i out.mp4 -shortest -vcodec copy -c:a aac -b:a 96k out_jazz.mp4

rem ffmpeg -i earth.mp4 -ss 00:30:00 -t 00:01:20  -vcodec copy -acodec copy e.mp4

rem ffmpeg -y -i medley.webm -i out.mp4 -shortest -vcodec copy -c:a aac -b:a 96k out_sound.mp4

rem ffmpeg -y -i out.mp4 -t 04:46:11 -vcodec copy out_cut.mp4

rem ffmpeg -i jazz.webm -i jazz.webm -filter_complex [0:a][1:a]concat=n=2:v=0:a=1 jazz2.mp3
rem ffmpeg -i jazz2.mp3 -i jazz2.mp3 -filter_complex [0:a][1:a]concat=n=2:v=0:a=1  jazz3.mp3
rem ffmpeg -i jazz3.mp3 -i jazz3.mp3 -filter_complex [0:a][1:a]concat=n=2:v=0:a=1  jazz4.mp3

rem ffmpeg -i out_cut.mp4 -i jazz4.mp3 -shortest -vcodec copy -acodec copy out_cut_jazz.mp4

rem ffmpeg -i r.3gp -c:a aac -b:a 96k r.mp4
rem ffmpeg -loop 1 -y -i pic.jpg -i r.3gp -shortest -acodec copy -vcodec libx264 r2.mp4

rem ffmpeg -ss 00:30:00 -i jazz4.mp3 -i out.mp4  -shortest -vcodec copy -acodec copy out_jazz.mp4

rem ffmpeg -y -i lie_megamix.mp3 -i output.mp4 -shortest -vcodec copy -c:a aac -b:a 96k MCA-NBT-EDIT.mp4

rem echo file 'output1566500155.mp4' > list.txt
rem echo file 'output.mp4' >> list.txt
rem echo file 'output3.mp4' >> list.txt
rem echo file 'output2.mp4' >> list.txt
rem echo file 'win.mp4' >> list.txt
rem echo file 'win.mp4' >> list.txt

rem ffmpeg -safe 0 -f concat -i list.txt -c:v libx264 -preset veryfast -crf 23 -an -pix_fmt yuv420p win.mp4
rem ffmpeg -i jaws.mkv -i jaws.mkv -filter_complex [0:a][1:a]concat=n=2:v=0:a=1 jaws2.mp3

rem ffmpeg -y -i jaws2.mp3 -i output1566833952.mp4 -shortest -vcodec copy -c:a aac -b:a 96k MCA-NBT-EDIT.mp4


rem echo file 'output.mp4' > list.txt
rem echo file 'output1566848022.mp4' > list.txt
rem echo file 'output1566848230.mp4' >> list.txt
rem rem echo file 'output1566848525.mp4' >> list.txt
rem echo file 'output1566848818.mp4' >> list.txt
rem echo file 'output12.mp4' >> list.txt
rem echo file 'output1566852097.mp4' >> list.txt
rem echo file 'output12 (2).mp4' >> list.txt
rem echo file 'output1566853700.mp4' >> list.txt
rem echo file 'output12 (3).mp4' >> list.txt
rem echo file 'output12 (4).mp4' >> list.txt
rem echo file 'output1566859565.mp4' >> list.txt
rem echo file 'output12 (5).mp4' >> list.txt

rem ffmpeg -i world.webm world.mp3
rem ffmpeg -i world.mp3 -i 2019_08_28_17_13_54.mp4 -shortest -c:a aac -b:a 96k -c:v libx264 -preset veryfast -crf 23 -pix_fmt yuv420p win2.mp4

rem ffmpeg -i tiesto.opus tiesto.mp3
rem ffmpeg -i tiesto.mp3 -i 2019_08_28_20_14_10.mp4 -t 00:01:25 -shortest -c:a aac -b:a 96k -c:v libx264 -preset veryfast -crf 23 -pix_fmt yuv420p fb.mp4
rem ffmpeg -i output1544936155.mp4 -ss 00:00:00 -t 00:34:00  -c copy out11.mp4

rem ffmpeg -i trance.opus trance.mp3
rem ffmpeg -y -ss 00:03:00 -i trance.mp3 -i 2019_08_29_20_13_02.mp4 -shortest -c:a aac -b:a 96k -vf scale=1920:1080:-1 -c:v libx264 -preset veryfast -crf 23 -pix_fmt yuv420p 360.mp4

rem ffmpeg -y -ss 00:13:00 -i trance.mp3 -i 2019_09_01_18_26_06.mp4 -shortest -c:a aac -b:a 96k  -c:v libx264 -preset veryfast -crf 23 -pix_fmt yuv420p out.mp4



rem ffmpeg -y -ss 00:00:05 -i 2019_09_05_02_11_29.mp4 -t 00:01:05 -vcodec copy part1.mp4
rem ffmpeg -y -ss 00:04:00 -i 2019_09_05_02_11_29.mp4 -vcodec copy part2.mp4
rem echo file 'part1.mp4' > list.txt
rem echo file 'part2.mp4' >> list.txt
rem ffmpeg -y -safe 0 -f concat -i list.txt -c:v libx264 -preset veryfast -crf 23 -an -pix_fmt yuv420p tot.mp4
rem ffmpeg -ss 00:20:00 -i trance.mp3 -i tot.mp4 -shortest -vcodec copy -acodec copy tot_sound.mp4
rem ffmpeg -y -i 2019_09_06_03_59_28.mp4 -an -c:v libx264 -preset veryfast -crf 23 -pix_fmt yuv420p demo1.mp4

rem echo file '2019_09_11_18_24_43.mp4' > list.txt
rem echo file '2019_09_11_17_50_17.mp4' >> list.txt
rem echo file '2019_09_11_17_55_53.mp4' >> list.txt
rem echo file '2019_09_11_18_02_59.mp4' >> list.txt
rem echo file '2019_09_11_18_18_35.mp4' >> list.txt
rem ffmpeg -safe 0 -f concat -i list.txt -c:v libx264 -preset veryfast -crf 23 -an -pix_fmt yuv420p 1.12.2.mp4

rem ffmpeg -y -ss 00:19:00 -i trance.mp3 -i 2019_09_12_02_09_25.mp4 -shortest -c:a aac -b:a 96k -c:v libx264 -preset veryfast -crf 23 -pix_fmt yuv420p out.mp4


rem ffmpeg -y -ss 00:23:00 -i trance.mp3 -i 2019_09_23_23_35_24.mp4 -shortest -c:a aac -b:a 96k -c:v h264_nvenc -preset slow -cq 10 -bf 2 -g 150 output.mp4

rem -hwaccel cuvid -c:v h264_cuvid


rem ffmpeg -y -ss 00:23:00 -i trance.mp3 -i 2019_09_23_23_35_24.mp4 -shortest -c:a aac -b:a 96k -c:v libx264 -preset veryfast -crf 23 -pix_fmt yuv420p out.mp4

rem ffmpeg -i out.mp4 -vf mpdecimate,setpts=N/FRAME_RATE/TB -an -c:v libx264 -preset veryfast -crf 23 -pix_fmt yuv420p out_removed.mp4

rem ffmpeg -i out.mp4 -vf mpdecimate out2.mp4

rem ffmpeg -y -ss 00:29:00 -i trance.mp3 -i out_removed.mp4 -shortest -c:a aac -b:a 96k -vcodec copy out3.mp4

rem ffmpeg -y -ss 00:14:00 -i trance.mp3 -i 2019_09_24_11_26_59.mp4 -shortest -c:a aac -b:a 96k -c:v libx264 -preset veryfast -crf 23 -pix_fmt yuv420p out.mp4

rem ffmpeg -y -ss 00:23:00 -i trance.mp3 -i 2019_09_25_00_34_01.mp4 -shortest -c:a aac -b:a 96k -c:v libx264 -preset veryfast -crf 23 -pix_fmt yuv420p out_360_2.mp4



rem ffmpeg -y -hwaccel cuvid -c:v h264_cuvid -i 2019_09_25_22_48_43.mp4 -vcodec h264_nvenc -preset slow out.mp4
rem ffmpeg -y -hwaccel cuvid -c:v h264_cuvid -i 2019_09_25_22_48_43.mp4 -vcodec h264_nvenc -b:v 5M out.mp4
rem ffmpeg -y -i 2019_09_25_22_48_43.mp4 -vcodec h264_nvenc -b:v 5M out.mp4
rem ffmpeg -y -i 2019_09_25_22_48_43.mp4 -c:v h264_nvenc -profile:v high444p -pixel_format yuv444p -preset default out.mp4
rem ffmpeg -y -i 2019_09_25_22_48_43.mp4 -c:v h264_nvenc -profile:v high444p -pixel_format yuv444p -preset slow -cq 10 -bf 2 -g 150 out.mp4
rem ffmpeg -y -i 2019_09_25_22_48_43.mp4 -vcodec h264_nvenc -preset slow -cq 10 -bf 2 -g 150 -b:v 5M out.mp4
rem ffmpeg -y -i 2019_09_25_22_48_43.mp4 -vcodec h264_nvenc -preset slow -cq 10 -bf 2 -g 150 out.mp4

rem ffmpeg -y -i 2019_09_25_22_48_43.mp4 -c:v h264_nvenc -profile:v high -pixel_format nv12 -b:v 9000k -preset slow -rc vbr_hq -rc-lookahead 32 out3.mp4

rem ffmpeg -y -i 2019_09_25_22_48_43.mp4 -c:v libx264 -an -preset veryfast -crf 23 -pix_fmt yuv420p out4.mp4

rem ffmpeg -y -i 2019_09_25_22_48_43.mp4 -c:v h264_nvenc -profile:v high -pix_fmt yuv420p -b:v 9000k -preset slow -rc vbr_hq -rc-lookahead 32 out3.mp4


rem ffmpeg -y -ss 00:14:00 -i trance.mp3 -i 2019_09_25_22_48_43.mp4 -shortest -c:v h264_nvenc -profile:v high -pixel_format nv12 -b:v 8000k -preset slow -bf:v 2 -rc vbr_hq -rc-lookahead 32 -c:a aac -b:a 384k -movflags +faststart out6.mp4

rem ffmpeg -y -ss 00:18:00 -i trance.mp3 -i 2019_09_29_03_31_54.mp4_fixed.mp4 -shortest -c:v h264_nvenc -profile:v high -pixel_format nv12 -b:v 8000k -preset slow -bf:v 2 -rc vbr_hq -rc-lookahead 32 -movflags +faststart out.mp4

rem ffmpeg -y -ss 00:18:00 -i trance.mp3 -i 2019_09_29_03_31_54.mp4_fixed.mp4 -codec copy out.mp4

rem echo file '2019_09_29_00_53_46.mp4' > list.txt
rem echo file '2019_09_29_00_53_46.mp4' >> list.txt
rem echo file '2019_09_29_00_53_46.mp4' >> list.txt
rem echo file '2019_09_29_00_53_46.mp4' >> list.txt
rem echo file '2019_09_29_00_53_46.mp4' >> list.txt
rem echo file '2019_09_29_00_53_46.mp4' >> list.txt
rem echo file '2019_09_29_00_53_46.mp4' >> list.txt
rem echo file '2019_09_29_00_53_46.mp4' >> list.txt
rem echo file '2019_09_29_00_53_46.mp4' >> list.txt
rem echo file '2019_09_29_00_53_46.mp4' >> list.txt
rem echo file '2019_09_29_00_53_46.mp4' >> list.txt

rem ffmpeg -safe 0 -f concat -i list.txt -c copy win2.mp4

rem ffmpeg -y -ss 00:18:00 -i trance.mp3 -i 2019_09_29_03_31_54.mp4_fixed.mp4 -shortest -codec copy out.mp4
rem ffmpeg -y -ss 00:18:00 -i trance.mp3 -i 2019_09_29_03_31_54.mp4_fixed.mp4 -shortest -c:v h264_nvenc -profile:v high -pixel_format nv12 -b:v 8000k -preset slow -bf:v 2 -rc vbr_hq -rc-lookahead 32 -movflags +faststart out2.mp4

rem ffmpeg -hwaccel cuvid -c:v h264_cuvid -i "Minecraft 1.14.4 29-9-2019 23_06_56.mp4" -filter:v fps=fps=60 -c:v h264_nvenc -profile:v high -pixel_format nv12 -b:v 8000k -preset slow -bf:v 2 -rc vbr_hq -rc-lookahead 32 -movflags +faststart out60.mp4
rem ffmpeg -hwaccel cuvid -c:v h264_cuvid -i "Minecraft 1.14.4 29-9-2019 23_06_56.mp4" -r 60 -c:v h264_nvenc -profile:v high -pixel_format nv12 -b:v 8000k -preset slow -bf:v 2 -rc vbr_hq -rc-lookahead 32 -movflags +faststart out60.mp4

rem ffmpeg -y -hwaccel cuvid -c:v h264_cuvid -i "Minecraft 1.14.4 29-9-2019 23_06_56.mp4" -c copy -f image2pipe - | ffmpeg -f image2pipe -framerate 60 -i - -c copy out60.mp4

rem ffmpeg -y -i "Minecraft 1.14.4 29-9-2019 23_06_56.mp4" -c copy -f image2pipe - | ffmpeg -f image2pipe -framerate 60 -i - -an -c copy out60.mp4

rem ffmpeg -y -i "Minecraft 1.14.4 29-9-2019 23_06_56.mp4" -c copy -f image2pipe -
rem FFMPEG="ffmpeg -hide_banner -f rawvideo -vcodec rawvideo -pix_fmt rgb24 -s 1920x1080 -r 60 -i - -an -vcodec h264_nvenc -c:v libx264 -preset veryfast -crf 23 -c:a copy -pix_fmt yuv420p ../record/output%d.mp4"

rem ffmpeg -i "Minecraft 1.14.4 29-9-2019 23_06_56.mp4" -c copy frames%%d.png
rem ffmpeg -y -i frames%%d.tga -framerate 60 -c copy out60.mp4

rem .\ffmpeg.exe -i "Minecraft 1.14.4 29-9-2019 23_06_56.mp4" -c copy frames%%d.png
rem .\ffmpeg.exe -framerate 60 -pattern_type glob -i "*.png" -c:v libx264 -pix_fmt yuv420p out60.mp4

rem ffmpeg -i "Minecraft 1.14.4 29-9-2019 23_06_56.mp4" -c copy frames%%d.jpg
rem ffmpeg -framerate 60 -vcodec mjpeg -i frames%%d.jpg Project.mp4

rem .\ffmpeg.exe -i "Minecraft 1.14.4 29-9-2019 23_06_56.mp4" -c copy frames%%d.jpg
rem .\ffmpeg.exe -r 60 -i frames%%d.jpg -c:v libx264 -pix_fmt yuv420p  out60.mp4

rem .\ffmpeg.exe -i "Minecraft 1.14.4 29-9-2019 23_06_56.mp4" -c copy frames%%d.png
rem .\ffmpeg.exe -r 60 -vcodec mjpeg -i frames%%d.png -c:v libx264 -pix_fmt yuv420p  out60.mp4

rem ffmpeg -i frames%%d.jpg -c:v libx264 -vf fps=60 -pix_fmt yuv420p out60.mp4

rem ffmpeg -r 1/5 -start_number 0 -i C:\myimages\img%03d.png -c:v libx264 -r 30 -pix_fmt yuv420p out.mp4

rem ffmpeg -i "Minecraft 1.14.4 29-9-2019 23_06_56.mp4" frames%%d.jpg
rem ffmpeg -i frames%%d.jpg -c:v libx264 -vf fps=60 -pix_fmt yuv420p out60.mp4


rem ffmpeg -i "Minecraft 1.14.4 29-9-2019 23_06_56.mp4" frames%%d.png
rem ffmpeg -y -r 60 -i frames%%d.png -an -c:v h264_nvenc -profile:v high -pixel_format nv12 -b:v 10000k -preset slow -bf:v 2 -rc vbr_hq -rc-lookahead 32 -movflags +faststart out60.mp4

rem ffmpeg -y -i "Minecraft 1.14.4 29-9-2019 23_06_56.mp4" -f image2pipe - | ffmpeg -y -f image2pipe -framerate 60 -i - -an -c:v h264_nvenc -profile:v high -pixel_format nv12 -b:v 10000k -preset slow -bf:v 2 -rc vbr_hq -rc-lookahead 32 -movflags +faststart out60.mp4
rem ffmpeg -y -i "Minecraft 1.14.4 29-9-2019 23_06_56.mp4" -f image2pipe - | ffmpeg -y -f image2pipe -framerate 60 -i - -an -preset veryfast -c:v libx264 -r 60 -pix_fmt yuv420p out.mp4

rem ffmpeg -i "Minecraft 1.14.4 29-9-2019 23_06_56.mp4" frames%%d.png
rem ffmpeg -y -i "Minecraft 1.14.4 29-9-2019 23_06_56.mp4" -f image2pipe - | ffmpeg -y -f image2pipe -framerate 60 -i - -an -c:v h264_nvenc -profile:v high -pixel_format nv12 -b:v 10000k -preset slow -bf:v 2 -rc vbr_hq -rc-lookahead 32 -movflags +faststart out60.mp4


rem ffmpeg -y -i "Minecraft 1.14.4 29-9-2019 23_06_56.mp4" -f image2pipe - | ffmpeg -y -threads 4 -f image2pipe -framerate 60 -i - -an -c:v h264_nvenc -b:v 4M -maxrate:v 5M -bufsize:v 8M -profile:v main -level:v 4.1 -rc:v vbr_hq -rc-lookahead:v 32 -spatial_aq:v 1 -aq-strength:v 15 -coder:v cabac -f mp4 "out60.mp4"

rem ffmpeg -y -i "Minecraft 1.14.4 29-9-2019 23_06_56.mp4" -f image2pipe - | ffmpeg -y -threads 4 -f image2pipe -r 60 -i - -an -c:v h264_nvenc -b:v 4M -maxrate:v 5M -bufsize:v 8M -preset slow -bf:v 2 -profile:v high -pixel_format nv12 -level:v 4.1 -rc:v vbr_hq -rc-lookahead:v 32 -spatial_aq:v 1 -aq-strength:v 15 -coder:v cabac -f mp4 "out60.mp4"


rem ffmpeg -y -vsync 0 -i "Minecraft 1.14.4 29-9-2019 23_06_56.mp4" -crf 18 -f image2pipe - | ffmpeg -y -f image2pipe -framerate 60 -i - -an -preset veryfast -c:v libx264 -pix_fmt yuv420p -crf 18 out.mp4


rem ffmpeg -y -vsync 0 -i "Minecraft 1.14.4 29-9-2019 23_06_56.mp4" -f image2pipe - | ffmpeg -y -f image2pipe -framerate 60 -i - -an -c:v h264_nvenc -profile:v high -pixel_format nv12 -b:v 10000k -preset slow -bf:v 2 -rc vbr_hq -rc-lookahead 32 -movflags +faststart -crf 0 out60.mp4

rem ffmpeg -y -vsync 0 -i out60.mp4 frames_new%%d.png
rem ffmpeg -y -vsync 0 -i "Minecraft 1.14.4 29-9-2019 23_06_56.mp4" frames_source%%d.png

rem ffmpeg -y -vsync 0 -i "Minecraft 1.14.4 29-9-2019 23_06_56.mp4" -f image2pipe - | ffmpeg -y -f image2pipe -framerate 60 -i - -an -c:v h264_nvenc -profile:v high -pixel_format nv12 -b:v 10000k -preset slow -bf:v 2 -rc vbr_hq -rc-lookahead 32 -movflags +faststart out60.mp4

rem ffmpeg -y -vsync 0 -i "Minecraft 1.14.4 29-9-2019 23_06_56.mp4" -f image2pipe - | ffmpeg -y -f image2pipe -r 60 -i - -an -c:v h264_nvenc -preset slow -b:v 10000k -bufsize 20000k -profile:v high -bf 3 -b_ref_mode 2 -temporal-aq 1 -rc-lookahead 20 -vsync 0 out60.mp4

rem ffmpeg -y -vsync 0 -i "Minecraft 1.14.4 29-9-2019 23_06_56.mp4" -f image2pipe - | ffmpeg -y -f image2pipe -framerate 60 -i - -an -c:v h264_nvenc -profile:v high -pixel_format nv12 -b:v 10000k -preset slow -bf:v 3 -rc vbr_hq -rc-lookahead 32 -movflags +faststart out60.mp4

rem ffmpeg -y -vsync 0 -i "Minecraft 1.14.4 29-9-2019 23_06_56.mp4" -f image2pipe - | ffmpeg -y -f image2pipe -framerate 60 -i - -an -preset veryfast -c:v libx264 -pix_fmt yuv420p -crf 0 out60.mp4
rem ffmpeg -y -vsync 0 -i "Minecraft 1.14.4 29-9-2019 23_06_56.mp4" -f rawvideo -vcodec rawvideo -pix_fmt rgb24  -s 1920x1080 - | ffmpeg -y -f rawvideo -vcodec rawvideo -pix_fmt rgb24  -s 1920x1080 -framerate 60 -i - -an -preset veryfast -c:v libx264 -pix_fmt yuv420p -crf 23 out60.mp4

rem ffmpeg -y -vsync 0 -i "Minecraft 1.14.4 29-9-2019 23_06_56.mp4" -f rawvideo -vcodec rawvideo -pix_fmt rgb24 - | ffmpeg -y -f rawvideo -vcodec rawvideo -pix_fmt rgb24  -s 1920x1080 -framerate 60 -i - -an -preset veryfast -c:v libx264 -pix_fmt yuv420p -crf 23 out60.mp4

rem ffmpeg -y -vsync 0 -i out60.mp4 -vf "select=gte(n\,200)" -vframes 1 frames_new200.png
rem ffmpeg -y -vsync 0 -i "Minecraft 1.14.4 29-9-2019 23_06_56.mp4" -vf "select=gte(n\,200)" -vframes 1 frames_org200.png

ffmpeg -y -ss 00:33:00 -i trance.mp3 -ss 00:00:38 -i test1b.mp4 -shortest -c:a aac -b:a 96k -vcodec copy test1c.mp4


pause
