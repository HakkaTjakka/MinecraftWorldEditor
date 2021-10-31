@echo off

rem echo python to_region 4.313243 52.079576
echo 1
python to_coords.py 4.313243 52.079576 hoppa de poppa
python to_coords.py 4.3132 52.06 hoppa de poppa
echo 2
to_coords.exe 5.079938 51.517132 Tilburg
to_coords.exe 5.038 51.517 Tilburg

echo 2
D:\PACMAN\PROJECT-OBJ\to_coords.exe 5.27083 51.97083 blah di blah

REM echo projection.py togeo 6086.106737690075 -10488.871257942425 to lat/lon
REM python projection.py togeo 6086.106737690075 -10488.871257942425

PAUSE