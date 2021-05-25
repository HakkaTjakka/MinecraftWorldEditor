@echo off

setlocal ENABLEDELAYEDEXPANSION

set /A total_duration_before = 0
set /A total_duration_after = 0
set /A total_duration_before2 = 0
set /A total_duration_after2 = 0


rem ffmpeg -y -i long-oLXioQvGihg.nl.mp4 -ss 00:00:00.00 -t 00:00:57.68 "NEW - Harry G. Frankfurt - 01 - Intro.mp4"

rem set /A total_duration = 0

ffmpeg -y -hide_banner -i long-oLXioQvGihg.nl.mp4 -async 1 -c:v h264_nvenc -profile:v high -pix_fmt yuv420p -bufsize 20M -b:v 10K -bf:v 3 -preset slow -rc:v vbr_hq -rc-lookahead 32 -c:a aac -b:a 64k "NEW_NL_SHORT.MP4"


REM call :BURN_FILE "Harry G. Frankfurt - 01 - Intro.mp4"
REM call :BURN_FILE "Harry G. Frankfurt - 02 - There Is So Much Bullshit.mp4"
REM call :BURN_FILE "Harry G. Frankfurt - 03 - Synonyms For Humbug.mp4"
REM call :BURN_FILE "Harry G. Frankfurt - 04 - Short Of Lying.mp4"
REM call :BURN_FILE "Harry G. Frankfurt - 05 - Humbug Not Strickly A Lie.mp4"
REM call :BURN_FILE "Harry G. Frankfurt - 06 - Wittgenstein Longfellow.mp4"
REM call :BURN_FILE "Harry G. Frankfurt - 07 - Wittgenstein Combatting Insidious Nonsense.mp4"
REM call :BURN_FILE "Harry G. Frankfurt - 08 - What Is Objectionable.mp4"
REM call :BURN_FILE "Harry G. Frankfurt - 09 - The Point That Troubles Wittgenstein.mp4"
REM call :BURN_FILE "Harry G. Frankfurt - 10 - What Tends To Go On In A Bull Session.mp4"
REM call :BURN_FILE "Harry G. Frankfurt - 11 - The Term Bull.mp4"
REM call :BURN_FILE "Harry G. Frankfurt - 12 - Hot Air.mp4"
REM call :BURN_FILE "Harry G. Frankfurt - 13 - Lying And Bluffing.mp4"
REM call :BURN_FILE "Harry G. Frankfurt - 14 - Our Attitude Towards Bullshit.mp4"
REM call :BURN_FILE "Harry G. Frankfurt - 15 - Can_t Lie Unless You Know The Truth.mp4"
REM call :BURN_FILE "Harry G. Frankfurt - 16 - Bullshitters Further From Truth Than Liars.mp4"
REM call :BURN_FILE "Harry G. Frankfurt - 17 - Lack Of Connection Between Opions and Reality.mp4"
REM call :BURN_FILE "Harry G. Frankfurt - 18 - Credits And Adds For Other Books On CD.mp4"
REM 
REM if exist mylist.txt del mylist.txt
REM (for %%i in (NEW_NL2*.mp4) do (
REM 	echo file '%%i') >> mylist.txt
REM )
REM ffmpeg -y -safe 0 -f concat -i mylist3.txt -c copy output_long_NL.mp4

pause

exit /b

:BURN_FILE

set input=%1

set /A total_duration_before3 = !total_duration_before2!
set /A total_duration_after3 = !total_duration_after2!

set /A total_duration_before2 = !total_duration_before!
set /A total_duration_after2 = !total_duration_after!

ffprobe.exe -v error -show_entries format=duration -of default=nw=1 !input! > duration.txt
for /F "tokens=*" %%R in (duration.txt) do (
	for /f "tokens=1,2 delims==" %%a in ("%%R") do set NAME=%%a & set duration=%%b
)

echo 1
rem for /f "tokens=1,2 delims=." %%a in ('echo !duration!') do set /a number=%%a & set /a number1=%%b
for /f "tokens=1,2 delims=." %%a in ('echo !duration!') do set /a number=%%a & set number1=%%b

for /f "tokens=* delims=0" %%N in ("!number1!") do set "number1=%%N"
if not defined number1 set "number1=0"

echo 2

set /A total_duration = !total_duration! + !number! * 1000 + !number1! / 1000
set /A total_duration_before = !total_duration! / 1000
set /A total_duration_after = !total_duration! - !total_duration_before! * 1000

set /A duration_before = !number! 
set /A duration_after = !number1! / 1000

set widget=%input:"=%

REM echo LENGTH=!duration! / !duration_before!.!duration_after!  START=!total_duration_before2!.!total_duration_after2!  TOTAL=!total_duration_before!.!total_duration_after!      !input!  !total_duration!  !number!  !number1!   
echo LENGTH=!duration! / !duration_before!.!duration_after!  START=!total_duration_before2!.!total_duration_after2!  TOTAL=!total_duration_before!.!total_duration_after!  FILE="!widget!"


REM ffmpeg -n -i long-oLXioQvGihg.en.mp4 -ss !total_duration_before2!.!total_duration_after2! -t !duration_before!.!duration_after! -c:v h264_nvenc -profile:v high -pix_fmt yuv420p -bufsize 20M -b:v 25K -bf:v 3 -preset slow -rc:v vbr_hq -rc-lookahead 32 -c:a aac -b:a 32k "NEW_EN - !widget!"
rem ffmpeg -n -ss !total_duration_before3!.!total_duration_after3! -i long-oLXioQvGihg.en.mp4 -ss !total_duration_before2!.!total_duration_after2! -t !duration_before!.!duration_after! -c:v h264_nvenc -profile:v high -pix_fmt yuv420p -bufsize 20M -b:v 25K -bf:v 3 -preset slow -rc:v vbr_hq -rc-lookahead 32 -c:a aac -b:a 32k "NEW_EN - !widget!"

rem ffmpeg -y -hide_banner -ss !total_duration_before2!.!total_duration_after2! -i long-oLXioQvGihg.en.mp4 -to !total_duration_before!.!total_duration_after! -async 1 -c copy "NEW_EN2 - !widget!"

set /A total_duration_before4 = 40
set /A total_duration_after4 = 0
set /A total_duration_before5 = !total_duration_before2! - 50
set /A total_duration_after5 = !total_duration_after2! 
if not !total_duration_before5! GTR 0 (
	set /A total_duration_before5 = 0
	set /A total_duration_after5 = 0
	set /A total_duration_before4 = 0
) else (
	set /A duration_before = !duration_before! + 10
) 

ffmpeg -y -hide_banner -ss !total_duration_before5!.!total_duration_after5! -i long-oLXioQvGihg.nl.mp4 -ss !total_duration_before4!.!total_duration_after4! -t !duration_before!.!duration_after! -async 1 -c:v h264_nvenc -profile:v high -pix_fmt yuv420p -bufsize 20M -b:v 10K -bf:v 3 -preset slow -rc:v vbr_hq -rc-lookahead 32 -c:a aac -b:a 64k "NEW_NL2 - !widget!"

rem PAUSE

exit /b
