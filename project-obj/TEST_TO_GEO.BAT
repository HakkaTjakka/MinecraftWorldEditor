@echo off

rem echo  projection.py 4.313243 52.079576 to bte121
rem python projection.py 4.313243 52.079576

rem echo ============================

rem echo to_geo.py 6086.106737690075 -10488.871257942425 to lat/lon
python to_geo.py 6086.106737690075 -10488.871257942425
to_geo.exe 6086.106737690075 -10488.871257942425

PAUSE