@echo off
if exist geo_ready.txt del geo_ready.txt
if exist result.txt del result.txt

start cmd /k "monitor_to_geo.bat"

rem start cmd /k "input_to_geo.bat | python to_geo.py"
start cmd /k "input_to_geo.bat | to_geo.exe"
