@echo off

rem echo python to_region 4.313243 52.079576
python to_region.py 4.313 52.079 KOEK1 KOEK2 KOEK3
python to_region.py 4.313243 52.079576 KOEK1 KOEK2 KOEK3

to_region.exe 4.313243 52.079576 KOEK1 KOEK2 KOEK3
to_region.exe 4.33 52.06 KOEK1 KOEK2 KOEK3

REM echo projection.py togeo 6086.106737690075 -10488.871257942425 to lat/lon
REM python projection.py togeo 6086.106737690075 -10488.871257942425

PAUSE