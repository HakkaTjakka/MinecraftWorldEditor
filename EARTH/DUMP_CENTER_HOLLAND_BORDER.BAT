@ECHO OFF

setlocal EnableExtensions EnableDelayedExpansion

for /F "tokens=*" %%A in (OCTANTS_SORTED_BORDER.TXT) do (
	CALL DONODE.BAT %%A
)
PAUSE