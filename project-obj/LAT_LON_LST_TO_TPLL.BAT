@echo off
REM TYPE LAT_LON.LST | python list_to_coords.py
IF EXIST RESULT.TXT DEL RESULT.TXT
rem MAKE_POSTAL_LIST.BAT | python list_to_coords.py
MAKE_POSTAL_LIST.BAT | list_to_coords.exe
pause
