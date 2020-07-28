@echo off
youtube-dl  --restrict-filenames --abort-on-error --no-mtime --sub-lang "en,nl" --write-sub --convert-subs srt --write-auto-sub --download-archive ARCHIVE.TXT --skip-unavailable-fragments --geo-bypass %1
