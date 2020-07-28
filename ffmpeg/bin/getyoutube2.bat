@echo off
SET PATH=%CD%\FFMPEG\BIN;%PATH%
youtube-dl -k --abort-on-error --no-mtime --download-archive ARCHIVE.TXT --skip-unavailable-fragments --geo-bypass "%*"
