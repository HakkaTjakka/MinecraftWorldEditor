@ECHO OFF
setlocal EnableExtensions EnableDelayedExpansion

rem for /F "usebackq tokens=1,2 delims==" %%i in (`wmic os get LocalDateTime /VALUE 2^>NUL`) do if '.%%i.'=='.LocalDateTime.' set ldt=%%j
rem set ldt=%ldt:~0,4%-%ldt:~4,2%-%ldt:~6,2% %ldt:~8,2%:%ldt:~10,2%:%ldt:~12,6%
rem echo Local date is [%ldt%]

IF EXIST TO_SORT.DEL TO_SORT.TXT
dir /b "G:\DONE\*.DAT">FILES.TXT
for /f "tokens=*" %%G in (FILES.TXT) do (
	date.exe -r G:\DONE\%%G +"%%Y-%%m-%%d %%H:%%M:%%S %%G">TO_SORT.TXT
	date.exe -r G:\DONE\%%G +"%%Y-%%m-%%d %%H:%%M:%%S %%G"
)
ECHO SORTING....
SORT TO_SORT.TXT>SORTED.TXT
