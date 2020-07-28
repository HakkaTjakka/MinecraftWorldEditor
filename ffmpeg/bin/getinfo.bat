@echo off
cd /pacman/convert
youtube-dl -i --skip-unavailable-fragments --geo-bypass --get-id --get-format --get-filename --get-duration %* 
rem youtube-dl -i --skip-unavailable-fragments --geo-bypass --get-id --get-format --get-filename --get-description %* 
rem youtube-dl -i --skip-unavailable-fragments --geo-bypass --get-id --get-format --get-filename "https://www.youtube.com/watch?v=xQMcsmq9Mq4&list=PLd-BrKN7_A06ziZhokYLO1SURvaiRxV7F" > video.info