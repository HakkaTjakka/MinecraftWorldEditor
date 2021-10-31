@echo off
dir g:\done\*.dat>in.dat
for /f "tokens=1,2,3" %%a in (in.dat) do (
	echo %%a %%b %%c>>dates.dat
	rem echo %%a %%b %%c
)
.\date.exe -f dates.dat +"%%Y-%%m-%%d %%H:%%M:%%S"





pause
