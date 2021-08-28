@ECHO OFF

setlocal EnableExtensions EnableDelayedExpansion

for /F "tokens=*" %%A in (OCTANTS_SORTED2.TXT) do (
	CALL DONODE.BAT %%A
)
PAUSE