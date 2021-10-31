@ECHO OFF

:BEGIN

echo 5837 -10228
TIMEOUT 1 >NUL
echo 5838 -10228
TIMEOUT 1 >NUL
echo 5837 -10227
TIMEOUT 1 >NUL
echo 5838 -10227
TIMEOUT 1 >NUL
echo ready sukkel

:AGAIN

if not exist geo_continue.txt (
	TIMEOUT 1 >NUL
	goto :AGAIN
)
del geo_continue.txt
GOTO :BEGIN 