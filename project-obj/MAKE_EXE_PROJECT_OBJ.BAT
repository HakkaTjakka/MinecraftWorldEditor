@ECHO OFF

rem pyinstaller --onefile --hidden-import=jnius_config projection.py 

rem pyinstaller --onefile projection.spec

rem pyinstaller --onefile --hidden-import=pkg_resources.py2_warn.jnius_config projection.py 
rem pyinstaller --onefile --hidden-import=pkg_resources.py2_warn myprog.py

rem hiddenimports=jnius_config

rem --hidden-import pkg_resources


pyinstaller --onefile --paths C:\Windows\System32\downlevel project_obj.spec

pause
