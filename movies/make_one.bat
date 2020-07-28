@echo off
FOR /f "delims=" %%G in (list_one.txt) DO (
	echo "%%~nG" 
	md "d:/pacman/movie_pictures/%%~nG"

	md "d:/pacman/movie_pictures/%%~nG/00"
    ffmpeg -y -ss 00:00:00 -i "%%G" -t 00:10:00 -vf "scale=640:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/%%~nG/00/%%06d.png" -hide_banner

	md "d:/pacman/movie_pictures/%%~nG/01"
    ffmpeg -y -ss 00:10:00 -i "%%G" -t 00:10:00 -vf "scale=640:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/%%~nG/01/%%06d.png" -hide_banner

	md "d:/pacman/movie_pictures/%%~nG/02"
    ffmpeg -y -ss 00:20:00 -i "%%G" -t 00:10:00 -vf "scale=640:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/%%~nG/02/%%06d.png" -hide_banner

	md "d:/pacman/movie_pictures/%%~nG/03"
    ffmpeg -y -ss 00:30:00 -i "%%G" -t 00:10:00 -vf "scale=640:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/%%~nG/03/%%06d.png" -hide_banner

	md "d:/pacman/movie_pictures/%%~nG/04"
    ffmpeg -y -ss 00:40:00 -i "%%G" -t 00:10:00 -vf "scale=640:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/%%~nG/04/%%06d.png" -hide_banner

	md "d:/pacman/movie_pictures/%%~nG/05"
    ffmpeg -y -ss 00:50:00 -i "%%G" -t 00:10:00 -vf "scale=640:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/%%~nG/05/%%06d.png" -hide_banner

	md "d:/pacman/movie_pictures/%%~nG/10"
    ffmpeg -y -ss 01:00:00 -i "%%G" -t 00:10:00 -vf "scale=640:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/%%~nG/10/%%06d.png" -hide_banner

	md "d:/pacman/movie_pictures/%%~nG/11"
    ffmpeg -y -ss 01:10:00 -i "%%G" -t 00:10:00 -vf "scale=640:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/%%~nG/11/%%06d.png" -hide_banner

	md "d:/pacman/movie_pictures/%%~nG/12"
    ffmpeg -y -ss 01:20:00 -i "%%G" -t 00:10:00 -vf "scale=640:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/%%~nG/12/%%06d.png" -hide_banner

	md "d:/pacman/movie_pictures/%%~nG/13"
    ffmpeg -y -ss 01:30:00 -i "%%G" -t 00:10:00 -vf "scale=640:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/%%~nG/13/%%06d.png" -hide_banner

	md "d:/pacman/movie_pictures/%%~nG/14"
    ffmpeg -y -ss 01:40:00 -i "%%G" -t 00:10:00 -vf "scale=640:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/%%~nG/14/%%06d.png" -hide_banner

	md "d:/pacman/movie_pictures/%%~nG/15"
    ffmpeg -y -ss 01:50:00 -i "%%G" -t 00:10:00 -vf "scale=640:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/%%~nG/15/%%06d.png" -hide_banner

	md "d:/pacman/movie_pictures/%%~nG/20"
    ffmpeg -y -ss 02:00:00 -i "%%G" -t 00:10:00 -vf "scale=640:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/%%~nG/20/%%06d.png" -hide_banner

	md "d:/pacman/movie_pictures/%%~nG/21"
    ffmpeg -y -ss 02:10:00 -i "%%G" -t 00:10:00 -vf "scale=640:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/%%~nG/21/%%06d.png" -hide_banner

	md "d:/pacman/movie_pictures/%%~nG/22"
    ffmpeg -y -ss 02:20:00 -i "%%G" -t 00:10:00 -vf "scale=640:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/%%~nG/22/%%06d.png" -hide_banner

	md "d:/pacman/movie_pictures/%%~nG/23"
    ffmpeg -y -ss 02:30:00 -i "%%G" -t 00:10:00 -vf "scale=640:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/%%~nG/23/%%06d.png" -hide_banner

	md "d:/pacman/movie_pictures/%%~nG/24"
    ffmpeg -y -ss 02:40:00 -i "%%G" -t 00:10:00 -vf "scale=640:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/%%~nG/24/%%06d.png" -hide_banner

	md "d:/pacman/movie_pictures/%%~nG/25"
    ffmpeg -y -ss 02:50:00 -i "%%G" -t 00:10:00 -vf "scale=640:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/%%~nG/25/%%06d.png" -hide_banner

	md "d:/pacman/movie_pictures/%%~nG/30"
    ffmpeg -y -ss 03:00:00 -i "%%G" -vf "scale=640:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/%%~nG/30/%%06d.png" -hide_banner

)                                                                                                                                     

pause

