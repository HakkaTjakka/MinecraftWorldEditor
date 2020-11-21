@echo off
echo TOP-LEFT
python projection.py -22.8955078125 -43.39599609375
echo TOP-RIGHT
python projection.py -22.8955078125 -42.91259765625
echo BOTTOM-LEFT
python projection.py -23.04656982421875 -43.39599609375
echo BOTTOM-RIGHT
python projection.py -23.04656982421875 -42.91259765625

rem echo TOP-LEFT
rem projection.exe -22.8955078125 -43.39599609375
rem echo TOP-RIGHT
rem projection.exe -22.8955078125 -42.91259765625
rem echo BOTTOM-LEFT
rem projection.exe -23.04656982421875 -43.39599609375
rem echo BOTTOM-RIGHT
rem projection.exe -23.04656982421875 -42.91259765625

pause