rem @echo off
echo run first as non adminitstrator, then as administrator for mklink command (..??...)
MKDIR \Saves
MKDIR \Saves\Leeg
MKDIR \Saves\Test
MKDIR \Saves\Test.copy
XCOPY Leeg \Saves\Leeg /s
XCOPY Leeg \Saves\Test /s
XCOPY Leeg \Saves\Test.copy /s
DEL \Saves\Test\Region\*.*
DEL \Saves\Test.copy\Region\*.*
COPY copy_test.bat \Saves
COPY reset_test.bat \Saves
move "%appdata%\.minecraft\saves" "%appdata%\.minecraft\saves.byebyebaby"
mklink /D "%localappdata%\..\Roaming\.minecraft\saves" D:\Saves
rem mklink /D "%appdata%\.minecraft\saves" \Saves
pause
