@ECHO OFF
for /d %%a in ("30604050*") do ( move /y "%%a" "SCHWEIZ" 	>NUL 		& echo SCHWEIZ\%%a )
for /d %%a in ("30604241*") do ( move /y "%%a" "BRUSSEL" 	>NUL		& echo BRUSSEL\%%a )
for /d %%a in ("30604243*") do ( move /y "%%a" "AMSTERDAM" 	>NUL		& echo AMSTERDAM\%%a )
for /d %%a in ("30604252*") do ( move /y "%%a" "ENSCHEDE" 	>NUL		& echo ENSCHEDE\%%a )
for /d %%a in ("31416170*") do ( move /y "%%a" "JOCELYN" 	>NUL		& echo JOCELYN\%%a )
for /d %%a in ("2142725*")  do ( move /y "%%a" "NEWYORK" 	>NUL		& echo NEWYORK\%%a )
for /d %%a in ("2142417*")  do ( move /y "%%a" "MIAMI" 		>NUL		& echo MIAMI\%%a )
for /d %%a in ("20527051*") do ( move /y "%%a" "LA" 		>NUL		& echo LA\%%a )
exit 
