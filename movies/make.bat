@echo off

FOR /f "delims=" %%G in (list.txt) DO (
	echo "%%~nG" 
    ffmpeg -y -ss 00:00:10 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-000".png -hide_banner
    ffmpeg -y -ss 00:01:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-001".png -hide_banner
    ffmpeg -y -ss 00:02:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-002".png -hide_banner
    ffmpeg -y -ss 00:03:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-003".png -hide_banner
    ffmpeg -y -ss 00:04:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-004".png -hide_banner
    ffmpeg -y -ss 00:05:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-005".png -hide_banner
    ffmpeg -y -ss 00:06:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-006".png -hide_banner
    ffmpeg -y -ss 00:07:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-007".png -hide_banner
    ffmpeg -y -ss 00:08:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-008".png -hide_banner
    ffmpeg -y -ss 00:09:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-009".png -hide_banner

    ffmpeg -y -ss 00:10:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-010".png -hide_banner
    ffmpeg -y -ss 00:11:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-011".png -hide_banner
    ffmpeg -y -ss 00:12:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-012".png -hide_banner
    ffmpeg -y -ss 00:13:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-013".png -hide_banner
    ffmpeg -y -ss 00:14:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-014".png -hide_banner
    ffmpeg -y -ss 00:15:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-015".png -hide_banner
    ffmpeg -y -ss 00:16:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-016".png -hide_banner
    ffmpeg -y -ss 00:17:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-017".png -hide_banner
    ffmpeg -y -ss 00:18:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-018".png -hide_banner
    ffmpeg -y -ss 00:19:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-019".png -hide_banner

    ffmpeg -y -ss 00:20:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-020".png -hide_banner
    ffmpeg -y -ss 00:21:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-021".png -hide_banner
    ffmpeg -y -ss 00:22:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-022".png -hide_banner
    ffmpeg -y -ss 00:23:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-023".png -hide_banner
    ffmpeg -y -ss 00:24:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-024".png -hide_banner
    ffmpeg -y -ss 00:25:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-025".png -hide_banner
    ffmpeg -y -ss 00:26:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-026".png -hide_banner
    ffmpeg -y -ss 00:27:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-027".png -hide_banner
    ffmpeg -y -ss 00:28:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-028".png -hide_banner
    ffmpeg -y -ss 00:29:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-029".png -hide_banner
                                                                                                                                      
    ffmpeg -y -ss 00:30:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-030".png -hide_banner
    ffmpeg -y -ss 00:31:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-031".png -hide_banner
    ffmpeg -y -ss 00:32:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-032".png -hide_banner
    ffmpeg -y -ss 00:33:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-033".png -hide_banner
    ffmpeg -y -ss 00:34:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-034".png -hide_banner
    ffmpeg -y -ss 00:35:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-035".png -hide_banner
    ffmpeg -y -ss 00:36:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-036".png -hide_banner
    ffmpeg -y -ss 00:37:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-037".png -hide_banner
    ffmpeg -y -ss 00:38:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-038".png -hide_banner
    ffmpeg -y -ss 00:39:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-039".png -hide_banner

    ffmpeg -y -ss 00:40:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-040".png -hide_banner
    ffmpeg -y -ss 00:41:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-041".png -hide_banner
    ffmpeg -y -ss 00:42:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-042".png -hide_banner
    ffmpeg -y -ss 00:43:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-043".png -hide_banner
    ffmpeg -y -ss 00:44:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-044".png -hide_banner
    ffmpeg -y -ss 00:45:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-045".png -hide_banner
    ffmpeg -y -ss 00:46:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-046".png -hide_banner
    ffmpeg -y -ss 00:47:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-047".png -hide_banner
    ffmpeg -y -ss 00:48:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-048".png -hide_banner
    ffmpeg -y -ss 00:49:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-049".png -hide_banner
                                                                                                                                      
    ffmpeg -y -ss 00:50:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-050".png -hide_banner
    ffmpeg -y -ss 00:51:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-051".png -hide_banner
    ffmpeg -y -ss 00:52:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-052".png -hide_banner
    ffmpeg -y -ss 00:53:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-053".png -hide_banner
    ffmpeg -y -ss 00:54:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-054".png -hide_banner
    ffmpeg -y -ss 00:55:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-055".png -hide_banner
    ffmpeg -y -ss 00:56:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-056".png -hide_banner
    ffmpeg -y -ss 00:57:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-057".png -hide_banner
    ffmpeg -y -ss 00:58:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-058".png -hide_banner
    ffmpeg -y -ss 00:59:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-059".png -hide_banner

    ffmpeg -y -ss 01:00:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-100".png -hide_banner
    ffmpeg -y -ss 01:01:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-101".png -hide_banner
    ffmpeg -y -ss 01:02:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-102".png -hide_banner
    ffmpeg -y -ss 01:03:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-103".png -hide_banner
    ffmpeg -y -ss 01:04:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-104".png -hide_banner
    ffmpeg -y -ss 01:05:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-105".png -hide_banner
    ffmpeg -y -ss 01:06:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-106".png -hide_banner
    ffmpeg -y -ss 01:07:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-107".png -hide_banner
    ffmpeg -y -ss 01:08:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-108".png -hide_banner
    ffmpeg -y -ss 01:09:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-109".png -hide_banner
                                                                                                                                       
    ffmpeg -y -ss 01:10:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-110".png -hide_banner
    ffmpeg -y -ss 01:11:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-111".png -hide_banner
    ffmpeg -y -ss 01:12:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-112".png -hide_banner
    ffmpeg -y -ss 01:13:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-113".png -hide_banner
    ffmpeg -y -ss 01:14:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-114".png -hide_banner
    ffmpeg -y -ss 01:15:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-115".png -hide_banner
    ffmpeg -y -ss 01:16:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-116".png -hide_banner
    ffmpeg -y -ss 01:17:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-117".png -hide_banner
    ffmpeg -y -ss 01:18:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-118".png -hide_banner
    ffmpeg -y -ss 01:19:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-119".png -hide_banner
                                                                                                                                      1
    ffmpeg -y -ss 01:20:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-120".png -hide_banner
    ffmpeg -y -ss 01:21:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-121".png -hide_banner
    ffmpeg -y -ss 01:22:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-122".png -hide_banner
    ffmpeg -y -ss 01:23:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-123".png -hide_banner
    ffmpeg -y -ss 01:24:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-124".png -hide_banner
    ffmpeg -y -ss 01:25:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-125".png -hide_banner
    ffmpeg -y -ss 01:26:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-126".png -hide_banner
    ffmpeg -y -ss 01:27:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-127".png -hide_banner
    ffmpeg -y -ss 01:28:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-128".png -hide_banner
    ffmpeg -y -ss 01:29:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-129".png -hide_banner
                                                                                                                                      1
    ffmpeg -y -ss 01:30:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-130".png -hide_banner
    ffmpeg -y -ss 01:31:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-131".png -hide_banner
    ffmpeg -y -ss 01:32:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-132".png -hide_banner
    ffmpeg -y -ss 01:33:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-133".png -hide_banner
    ffmpeg -y -ss 01:34:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-134".png -hide_banner
    ffmpeg -y -ss 01:35:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-135".png -hide_banner
    ffmpeg -y -ss 01:36:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-136".png -hide_banner
    ffmpeg -y -ss 01:37:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-137".png -hide_banner
    ffmpeg -y -ss 01:38:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-138".png -hide_banner
    ffmpeg -y -ss 01:39:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-139".png -hide_banner
                                                                                                                                      1
    ffmpeg -y -ss 01:40:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-140".png -hide_banner
    ffmpeg -y -ss 01:41:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-141".png -hide_banner
    ffmpeg -y -ss 01:42:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-142".png -hide_banner
    ffmpeg -y -ss 01:43:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-143".png -hide_banner
    ffmpeg -y -ss 01:44:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-144".png -hide_banner
    ffmpeg -y -ss 01:45:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-145".png -hide_banner
    ffmpeg -y -ss 01:46:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-146".png -hide_banner
    ffmpeg -y -ss 01:47:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-147".png -hide_banner
    ffmpeg -y -ss 01:48:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-148".png -hide_banner
    ffmpeg -y -ss 01:49:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-149".png -hide_banner
                                                                                                                                      1
    ffmpeg -y -ss 01:50:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-150".png -hide_banner
    ffmpeg -y -ss 01:51:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-151".png -hide_banner
    ffmpeg -y -ss 01:52:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-152".png -hide_banner
    ffmpeg -y -ss 01:53:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-153".png -hide_banner
    ffmpeg -y -ss 01:54:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-154".png -hide_banner
    ffmpeg -y -ss 01:55:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-155".png -hide_banner
    ffmpeg -y -ss 01:56:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-156".png -hide_banner
    ffmpeg -y -ss 01:57:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-157".png -hide_banner
    ffmpeg -y -ss 01:58:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-158".png -hide_banner
    ffmpeg -y -ss 01:59:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-159".png -hide_banner

    ffmpeg -y -ss 02:00:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-200".png -hide_banner
    ffmpeg -y -ss 02:01:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-201".png -hide_banner
    ffmpeg -y -ss 02:02:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-202".png -hide_banner
    ffmpeg -y -ss 02:03:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-203".png -hide_banner
    ffmpeg -y -ss 02:04:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-204".png -hide_banner
    ffmpeg -y -ss 02:05:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-205".png -hide_banner
    ffmpeg -y -ss 02:06:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-206".png -hide_banner
    ffmpeg -y -ss 02:07:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-207".png -hide_banner
    ffmpeg -y -ss 02:08:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-208".png -hide_banner
    ffmpeg -y -ss 02:09:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-209".png -hide_banner
                                                                                                                                      
    ffmpeg -y -ss 02:10:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-210".png -hide_banner
    ffmpeg -y -ss 02:11:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-211".png -hide_banner
    ffmpeg -y -ss 02:12:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-212".png -hide_banner
    ffmpeg -y -ss 02:13:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-213".png -hide_banner
    ffmpeg -y -ss 02:14:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-214".png -hide_banner
    ffmpeg -y -ss 02:15:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-215".png -hide_banner
    ffmpeg -y -ss 02:16:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-216".png -hide_banner
    ffmpeg -y -ss 02:17:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-217".png -hide_banner
    ffmpeg -y -ss 02:18:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-218".png -hide_banner
    ffmpeg -y -ss 02:19:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-219".png -hide_banner
                                                                                                                                      
    ffmpeg -y -ss 02:20:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-220".png -hide_banner
    ffmpeg -y -ss 02:21:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-221".png -hide_banner
    ffmpeg -y -ss 02:22:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-222".png -hide_banner
    ffmpeg -y -ss 02:23:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-223".png -hide_banner
    ffmpeg -y -ss 02:24:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-224".png -hide_banner
    ffmpeg -y -ss 02:25:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-225".png -hide_banner
    ffmpeg -y -ss 02:26:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-226".png -hide_banner
    ffmpeg -y -ss 02:27:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-227".png -hide_banner
    ffmpeg -y -ss 02:28:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-228".png -hide_banner
    ffmpeg -y -ss 02:29:00 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-229".png -hide_banner
)                                                                                                                                     

pause

rem ffmpeg -ss 00:00:10 -i "%%G"  -vframes 1 -vf "scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-"%%04d.png -hide_banner
rem ffmpeg -i "%%G"  -vf "select='gt(scene,0.9)',scale=320:-1,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-"%%04d.png -hide_banner
rem ffmpeg -i "%%G"  -vf "select='eq(pict_type\,I)+not(mod(n\,3600))',scale=-1:320,tile=10x10" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-"%%04d.png -hide_banner
rem ffmpeg -i "%%G"  -vf "select='not(mod(n\,9000))',scale=-1:320,tile=1x1:margin=2" -vsync vfr "d:/pacman/movie_pictures/files/%%~nG-"%%04d.png -hide_banner
