@echo off

SETLOCAL EnableDelayedExpansion


dir /b /s *.jar > list_jar.txt

for /F "usebackq tokens=*" %%A in ("list_jar.txt") do (
	echo EXECUTING: "C:\Program Files\WinRAR\WinRAR.exe" x -o+ "%%~fxA" "%%~pnA\"
 	"C:\Program Files\WinRAR\WinRAR.exe" x -o+ "%%~fxA" "%%~pnA\"
)

dir /b /s *.class > list_class.txt
for /F "usebackq tokens=*" %%x in ("list_class.txt") do (
 	set "old_path=%CD%"
 	cd "%%~px"
	rem echo EXECUTING: jad "%%x" 
	jad "%%x" 
 	cd "!old_path!"
)


