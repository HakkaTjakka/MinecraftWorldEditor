@ECHO OFF

setlocal EnableExtensions EnableDelayedExpansion

for /F "tokens=*" %%A in (OCTANTS_TODO.TXT) do (
	CALL DONODE.BAT %%A
)
PAUSE