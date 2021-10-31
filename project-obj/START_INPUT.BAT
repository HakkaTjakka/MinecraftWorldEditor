@ECHO OFF
if exist result.txt del result.txt
if exist quit.txt del quit.txt
rem for /f "tokens=*" %%a in ('CALL INPUT.BAT | python list_to_geo.py') do (
rem 	ECHO RESULT: %%a
rem )
INPUT.BAT | python list_to_geo.py
rem INPUT.BAT | list_to_geo.exe
rem .exe in dir dist 
