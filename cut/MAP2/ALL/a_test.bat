@ECHO OFF

set "outputdir_result=map_result" >NUL 2>NUL

"C:\Program Files\IrfanView\i_view64.exe" /panorama=(2,%outputdir_result%\row_small.*.jpg) /convert=%outputdir_result%\clipboard_small.pdf
"C:\Program Files\IrfanView\i_view64.exe" /panorama=(2,%outputdir_result%\row.*.jpg) /convert=%outputdir_result%\clipboard.pdf
