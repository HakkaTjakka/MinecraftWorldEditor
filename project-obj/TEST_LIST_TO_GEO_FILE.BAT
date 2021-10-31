@echo off

rem echo  projection.py 4.313243 52.079576 to bte121
rem python projection.py 4.313243 52.079576

rem echo ============================

rem echo to_geo.py 6086.106737690075 -10488.871257942425 to lat/lon
REM python list_to_geo.py REGION.LST
rem type REGION.LST | python list_to_geo.py

rem for /f "tokens=*" %%G in ('type INPUT.BAT | python list_to_geo.py') do (
rem for /f "tokens=*" %%G in ('INPUT.BAT') do (
rem 	ECHO %%G
rem )

REM for /f "tokens=*" %%G in ('python list_to_geo.py REGION.LST') do (
REM for /f "tokens=*" %%G in ('INPUT.BAT') do (
REM  	ECHO %%G
REM )

IF EXIST STARTED.TXT DEL STARTED.TXT>NUL
START CMD /C CALL "START_INPUT_FILE.BAT"
:WAIT
IF NOT EXIST STARTED.TXT GOTO :WAIT
rem TIMEOUT 5
START CMD /C CALL "OUTPUT.BAT"

REM python list_to_geo.py < REGION.LST

rem list_to_geo.exe REGION.LST

PAUSE