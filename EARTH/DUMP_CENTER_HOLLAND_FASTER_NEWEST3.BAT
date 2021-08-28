@ECHO OFF

setlocal EnableExtensions EnableDelayedExpansion

for /F "tokens=*" %%A in (OCTANTS_SORTED3.TXT) do (
	CALL DONODE.BAT %%A
)
PAUSE