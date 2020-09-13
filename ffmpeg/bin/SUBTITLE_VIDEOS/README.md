YOUTUBE BATCH DOWNLOADER SUBTITLE FIXER/BURNER

Meant for batch downloading lots of youtube video's, and burn subtitles in one or more languages (change code for other/more languages, convert.bat and download_youtube.bat)
Now: --sub-lang "en,nl" (English, Dutch)
Use youtube-dl --list-subs <youtube url> for available language tags

-Usage:
	-place youtube link(s) (full url) from video and/or list into file LIST.TXT (See example)
	-run WORK.BAT from dos cmd commandline or double click WORK.BAT
	-IMPORTANT: edit convert.bat ffmpeg commands depending on video card (see REM statement) when not working, now: NVIDIA h264_nvenc encoder
	-video's are converted to 1920 x 1080 pixels for nice hires subs. Change for 4k or other/original format(s)
	
-Directory .\sof
	-Subtitle overlap fixer
	-Fixes downloaded subtitles with download_youtube.bat
	-Otherwise you will have upper line changed, lower line changed, etc.
	-File: dw.srt									.srt file for testing
	-File: go1.15.2.windows-amd64.msi 				go compiler installer
	-File: make_subtitle-overlap-fixer.exe.bat		cmd batch file to compile subtitle-overlap-fixer.go into sof.exe (takes name directory: sof)
	-File: sof.exe									resulting .exe from subtitle-overlap-fixer.go with make_subtitle-overlap-fixer.exe.bat
	-File: subtitle-overlap-fixer.go				go language actual .srt fixer source
	-File: dw.srt.fixed								resulting test file from dw.srt made with sof.exe made with make_subtitle-overlap-fixer.exe.bat
	
-File: ffmpeg.exe 									pacman ffmpeg video/audio encoder/decoder (Includes ALL codecs), used in convert.bat
-File: ffplay.exe									player
-File: ffprobe.exe									for getting info out of video/audio file, used in convert.bat
-File: sof.exe										see above, used in convert.bat
-File: ARCHIVE.TXT									created/used by youtube-dl.exe for downloaded files to prevent new downloading. Delete if new download wanted
-File: youtube-dl.exe								actual youtube downloader. --help for info, --U for update if not working
-File: convert.bat									cmd batch file to burn subtitles into all .mkv, .mp4, and/or .webm files
-File: download_files.bat							downloads all files from links in list.txt with download_youtube.bat
-File: download_youtube.bat							downloads file with youtube-dl.exe
-File: WORK.BAT										demo test file
-Directory .\DUTCH									output dir for nl subs (created)
-Directory .\ENGLISH								output dir for en subs (created)
-Directory .\ORIGINAL								output dir for downloaded files that are converted (created)
-File: .fixed 										fixed .srt file with sof.exe

https://www.facebook.com/Minecraft-Worldeditor-110607880303634/
https://www.facebook.com/Pacman-Graphics-1601114056700700/
https://github.com/HakkaTjakka
https://www.facebook.com/GoogleEarth3DPostersAndVideos/
https://drive.google.com/drive/folders/12TwAJk4L6kch_bv6_96yDbOMX_gp0IfU
gerardwensink@gmail.com