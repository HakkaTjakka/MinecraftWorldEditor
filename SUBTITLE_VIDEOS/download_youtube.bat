@echo off
youtube-dl -k --restrict-filenames --abort-on-error --no-mtime --sub-lang "en,nl" --write-sub --convert-subs srt --write-auto-sub --download-archive ARCHIVE.TXT --skip-unavailable-fragments --write-thumbnail --write-info-json --geo-bypass "%*"
rem >> logfile.txt
