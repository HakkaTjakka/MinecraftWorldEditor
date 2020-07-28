@echo off
SET PATH=%CD%\FFMPEG\BIN;%PATH%

d:
rem cd /convert/files
cd /pacman/convert/files

youtube-dl -k --abort-on-error --no-mtime --sub-lang "en,nl" --write-sub --convert-subs srt --write-auto-sub --download-archive ARCHIVE.TXT --skip-unavailable-fragments --write-thumbnail --write-info-json --geo-bypass "https://www.youtube.com/watch?v=%*" >> logfile.txt

rem youtube-dl -k --abort-on-error --no-mtime --sub-lang "en,nl" --convert-subs srt --write-auto-sub --download-archive ARCHIVE.TXT --skip-unavailable-fragments --write-thumbnail --write-info-json --geo-bypass "%*" >> logfile.txt
rem youtube-dl -k --abort-on-error --no-mtime --sub-lang "en,nl" --convert-subs srt --write-auto-sub --download-archive ARCHIVE.TXT --skip-unavailable-fragments --write-thumbnail --write-info-json --geo-bypass "https://www.youtube.com/watch?v=%*" >> logfile.txt


rem youtube-dl -k --abort-on-error --no-mtime --sub-lang "en,nl" --write-sub --convert-subs srt --write-auto-sub --download-archive ARCHIVE.TXT --skip-unavailable-fragments --write-thumbnail --write-info-json --geo-bypass "https://www.youtube.com/watch?v=%*" >> logfile.txt

rem youtube-dl -k --abort-on-error --no-mtime --sub-lang "en,nl" --write-sub --convert-subs srt --download-archive ARCHIVE.TXT --skip-unavailable-fragments --write-thumbnail --write-info-json --geo-bypass "https://www.youtube.com/watch?v=%*" >> logfile.txt

rem youtube-dl -k --abort-on-error --no-mtime --sub-lang "en,nl" --write-sub --write-auto-sub --download-archive ARCHIVE.TXT --skip-unavailable-fragments --write-thumbnail --write-info-json --geo-bypass "https://www.youtube.com/watch?v=%*" >> logfile.txt



rem youtube-dl -k --restrict-filenames --abort-on-error --no-mtime --sub-lang "en,nl" --write-sub --write-auto-sub --download-archive ARCHIVE.TXT --skip-unavailable-fragments --write-thumbnail --write-info-json --geo-bypass "https://www.youtube.com/watch?v=%*" >> logfile.txt
rem youtube-dl -k --abort-on-error --no-mtime --sub-lang "en,nl" --write-sub --write-auto-sub --download-archive ARCHIVE.TXT --skip-unavailable-fragments --write-thumbnail --write-info-json --geo-bypass "https://www.youtube.com/watch?v=%*" >> logfile.txt
rem youtube-dl -k -i --sub-lang "en,nl" --write-sub --write-auto-sub --download-archive ARCHIVE.TXT --skip-unavailable-fragments --write-thumbnail --write-info-json --geo-bypass %* >> logfile.txt
REM youtube-dl -k -i --convert-subs ass --sub-lang "en,nl" --write-sub --write-auto-sub --download-archive ARCHIVE.TXT --skip-unavailable-fragments --write-thumbnail --write-info-json --geo-bypass %* >> logfile.txt
REM rem youtube-dl -k -i --convert-subs ass --sub-lang "en,nl" --write-sub --write-auto-sub --download-archive ARCHIVE.TXT --skip-unavailable-fragments --write-thumbnail --write-info-json --write-description --verbose %*
REM cd /pacman/convert
REM makelist.bat

REM --get-format --get-filename

