set PATH=%CD%\bin;..\ffmpeg\bin;%PATH%;
pacman.exe utrecht fast 										rem check octant existance when used
rem pacman.exe utrecht 											rem make list / scan all octants first for existance
rem pacman.exe regions r.<x>.<z>.vox cubic utrecht				rem do ../cut/r.<x>.<z>.vox file
rem pacman.exe regions 											rem do all ../cut/*.vox files
rem region files per octant in ../cut/done/<octant>.info
rem octants files per region file in ../cut/done/r.<x>.<z>.info 	
rem Use <octant>.info => [<index>][<octant x>][<octant y>] => object_array.txt => X=octant_x Y=octant_y for regenerating octants/(complete)regions inside
rem plot_tiles.off/plot_tiles.on Set regenerating canvas with ../cut/r.<x>.<z>.png on/off
rem delete object_array.txt for scanning all octants.
rem msg on GitHub for more info. Tia.

pause