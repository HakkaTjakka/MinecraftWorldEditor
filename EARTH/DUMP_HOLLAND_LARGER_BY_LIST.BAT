@ECHO OFF

setlocal EnableExtensions EnableDelayedExpansion

for /F "tokens=*" %%A in (HOLLAND_LIST_LARGER_SORTED.TXT) do (
	CALL DONODE.BAT %%A
)
PAUSE