#ifndef KEYLIST_HPP
#define KEYLIST_HPP

//Macro name            Code        Key(s)                  Description
//
//#define 0-6 (7)
//name    8-22 (15)
//code    24-30 (7)
//key     38-58 (21)
//desc    60-end
//
/*
00000000001111111111222222222233333333334444444444555555555566666666667777777777
01234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789
*/

//sf::Keyboard::
//sf::Keyboard::A,EVENT_SHIFT||EVENT_ALT
#define LIST_START      0
#define DO_PONG         2000001     //
#define GO_LIST         4000000     //C,ALT-v               List's convert directory. Compares with record dir, moves converted files to converted.
#define GO_DOWNLOAD     3000000     //ALT-v                 Start downloading url's from ../convert/list.txt. Can be youtube code's kj2GlIIWCL8 or url https://www.youtube.com/watch?v=kj2GlIIWCL8
                                    //                      Creates ../convert/files/convert.txt with data for burning subtitles (GO_BURN / SHIFT-ALT-v)
                                    //                      Creates ../convert/files/convert.bat with ffmpeg commands for converting by batch shell.
#define GO_BURN         3000001     //SHIFT-ALT-v           Start burning subtitles in downloaded files from ALT-V (when downloaded).
                                    //                      Files end up in ../convert/files
                                    //                      ../convert/files/list.txt playable files downloaded.
                                    //                      ../convert/files/convert.txt data for burning. (from GO_DOWNLOAD / ALT-v
                                    //                      Files end up in ../convert/files
#define MACRO1          1000001     //ALT-F11               Macro 1. Set PLOT MAP 2, load rel.pos. (CTRL-F10 and CTRL-F12), set canvas on (CTRL-y), select canvas (ALT-DOWN),zoom in (SHIFT-PGDN), canvas ghost on (SHIFT-F9), GHOST OFF ('g').
#define MACRO2          1000002     //SHFT-F11              Macro 2. Load maze ('x'), set canvas on (SHIFT-F9), GHOST OFF ('g'), canvas ghost on (SHIFT-F9), select canvas (ALT-DOWN), zoom in
#define ZOOM_OUT        1000101     //CTRL-END              Start zoom out macro. (END=set jump level) (Save/load/set start: CTRL-F9/CTRL-F10, Save/load/set end: CTRL-F11/CTRL-F12)
#define ZOOM_IN         1000102     //CTRL-HOME             Start zoom in macro. (END=set jump level)
                                    //                      Zoom uses directory ../geodata, geodata filelist in list.txt (path to filename containing geodata, see example)
#define ADAPT_SPEED     1000103     //-                     Macro used by zoom in/out.
                                    //                      Some keys for map zoom functions: ALT-F6, '['/']'/'<'/'>', ALT-z/ALT-x, ALT-END/ALT-HOME/END/CTRL-F9/CTRL-F10/CTRL-F11/CTRL-F12, SHIFT-PGDN/SHIFT-PGUP, ALT-DOWN/ALT-UP, CTRL-LEFT/CTRL-RIGHT
#define MACRO_LIST      2000000     //SHIFT-F1              Show macro list (this file and data)
#define TEXT_FILES      1000400     //ALT-t                 Text files to font to screen. Filelist in ./list.txt First line of first textfile needs to be empty... (bug).
                                    //                      Usage: TEXT_FILES <FONTSIZE> <COLOR> (COLOR IN HEXADECIMAL LIKE FF00FFFF FOR CYAN NO TRANSPARANT....)
                                    //                      Example: "TEXT_FILES 24 FFFFFFFF"
#define SCRIPT          1010000     //                      Run script. Usage SCRIPT <CHAI_SCRIPTNAME> PARAMETER1 PARAMETER2
                                    //                      Example: SCRIPT ..//scripts//fun.chai or SCRIPT "..//scripts//fun.chai" or SCRIPT ..\scripts\fun.chai or SCRIPT "..\scripts\fun.chai"
                                    //                      Use quotes when path/filename contains white spaces.... Use backslash to preserve backslash....
                                    //                      PARAMETER1 PARAMETER2 ... etc also end up in chai_input[n], where n is #PARAMETER - 1 (starting from 0, while script starts from 1...
                                    //                      See ../scripts/fun.chai for example. Like GetInput("1") for getting first parameter, and/or ReturnResult("1","This is the output") for sending first output parameter.
                                    //                      Output ends up in chai_output[n], where n=0 is the first("1") output value. (char*). Check code for adding non script (c coded) functions, like the GetInput() and ReturnResult() functions.
#define EXECUTE         1010001     //                      Run script. Usage EXECUTE CHAI_SCRIPT_COMMAND
                                    //                      Example: EXECUTE print("Hello World\n");
#define HELP_ON_OFF     1000500     //F1                    Help on/off
#define HELP_ON         1000501     //                      Help on
#define HELP_OFF        1000502     //                      Help off
#define DEBUG_ON_OFF    1000600     //F2                    Debug info on/off
#define DEBUG_ON        1000601     //                      Debug info on
#define DEBUG_OFF       1000602     //                      Debug info off
#define MOUSE_ON_OFF    1000700     //CTRL-F2               Mouse on/off
#define MOUSE_ON        1000701     //                      Mouse on
#define MOUSE_OFF       1000702     //                      Mouse off
#define SYNC_ON_OFF     1000800     //F3                    Vertical synchonisation on/off
#define SYNC_ON         1000801     //                      Vertical synchonisation on
#define SYNC_OFF        1000802     //                      Vertical synchonisation off
#define SPD_ADJ_ON_OFF  1000900     //F4                    Speed adjust on/off
#define SPD_ADJ_ON      1000901     //                      Speed adjust on
#define SPD_ADJ_OFF     1000902     //                      Speed adjust off
#define OVERWRITE       1001000     //CTRL-F5               Overwrite background textures (picture.*.*.png)with drawmaze (foreground) textures (picture_maze.*.*.png) changed/saved
                                    //                      (copy files picture_maze.* -> picture.*)
#define MERGE           1001100     //SHIFT-F7              Combine background textures with foreground textures.
                                    //                      (render, overwriting background with forground (transparancy))
#define SCREENSHOT      1001300     //0                     Screenshot. Placed in picture SHIFT-P. 1920 x 1080
#define BLENDING        1000310     //                      Set blening mode on/off. Usage: BLENDING <blendingmode>. (0=off/1/2).
                                    //                      When set blening mode 2. Use keys 1-6 and SHIFT 1-6 for custom blending (4) modes/values. '+'/'-' selects 1 out of 4 standard modes. 4 is custom...
#define BLEND_MODE      1000323     //                      Add, Set blending mode. When BLENDING=2 (CUSTOM) Usage: BLEND_MODE <num> where num: 0=Add,, 1=None, 2=Alpha, 3=Multiply, 4=Custom user
                                    //                      Custom user parameter selection:
#define COLORSRCFACTOR  1000324     //                      0=Zero, 1=One, 2=SrcColor, 3=OneMinusSrcColor, 4=DstColor, 5=OneMinusDstColor, 6=SrcAlpha, 7=OneMinusSrcAlpha, 8=DstAlpha, 9=OneMinusDstAlpha
#define COLORDSTFACTOR  1000325     //                      Same as above. Usage: colorDstFactor <num>, where <num> one of the above.
#define ALPHASRCFACTOR  1000326     //                      Same as above
#define ALPHADSTFACTOR  1000327     //                      Same as above
#define COLOREQUATION   1000328     //                      0=Add ,1=Subtract ,2=ReverseSubtract
#define ALPHAEQUATION   1000329     //                      Same as above. Usage alphaEquation <num>
#define RECORD_ON       1001400     //r                     Recording on. (When pressing 'r' on keyboard it sets PAUSE_ON
#define RECORD_OFF      1001401     //                      Recording off.
#define RECORD_MODE     1001402     //R                     Recording mode. Usage: RECORD_MODE <num>, where <num> = 1-2. 1=whole screen, 2=only movie from 'b'
#define PAUSE_ON        1001501     //R                     Pause off. (When pressing 'R' on keyboard when recording is OFF, select RECORDING MODE (0=screen, 1=movie from SHIFT-m)
#define PAUSE_OFF       1001502     //                      Pause on
                                    //                      Check pacman.ini file for FFMPEG input/output settings. Like movie 'b' loading with subtitles(FFMPEG_IN), and/or writing (FFMPEG) output movie with audio track directly to .mp4 (need split audio first or with youtube-dl/getyoutube.bat)
#define EATMODE_ON      1001601     //                      Eatmode on
#define EATMODE_OFF     1001602     //                      Eatmode off
#define SAVE_MAP        1001700     //Z                     Save maze file to map.dat (binary) (maze maps)
#define SAVE_MAZE       1001701     //z                     Save maze file to maze.dat (text)
#define LOAD_MAP        1001702     //SHIFT-x               Read maze file from map.dat
#define LOAD_MAZE       1001703     //x                     Read maze file from maze.dat
#define COMBINE_ON      1001801     //                      Set COMBINE=ON
#define COMBINE_OFF     1001802     //                      Set COMBINE=OFF
                                    //                      When saving map ('z'/'Z') it saves current position pacman as left/top of maze.
                                    //                      '['/']' to switch between levels (different mazes).
                                    //                      Also used in combination with other functions like maze -> texture and vise versa.
#define GHOST_SLOW      1001900     //{                     Current ghost slow down when follow ghost ('f'/'F')
#define GHOST_ALL_SLOW  1001901     //ALT-{                 All ghosts slow down.
#define GHOST_FAST      1001902     //}                     Ghost speed up when follow ghost
#define GHOST_ALL_FAST  1001903     //ALT-}                 All ghost speed up.
#define PREVIOUS_GHOST  1001904     //[                     Previous ghost when follow ghost is on.
#define NEXT_GHOST      1001905     //]                     Next ghost when follow ghost is on.
#define PREVIOUS_LEVEL  1002001     //(/[                   Previous level.
#define NEXT_LEVEL      1002002     //)/]                   Next level when follow ghost is on or off.
#define SET_LEVEL       1002003     //                      Set level. Usage SET_LEVEL <num> where <num> is level number.
#define MAPMODE         1000200     //ALT-F6                Map mode 1,2 or off. 2 normal use. 1 for saving 'local' picture_maze.* tiles and blend tile info onto other maps. (For now....)
                                    //                      Usage: MAPMODE <num> (0=off/1/2). Sets leveldir to ../map_pictures/www.tilesite.com/SIZEXxSIZEY/ use url local.something.more/evenmore ("local"<-!!!) or your serverpath for loading tiles from 'internet'(web server)
#define PREVIOUS_MAP    1002101     //<                     Previous map when SHADE MAP > 0 (ALT-F6) (geo maps)
#define NEXT_MAP        1002102     //<                     Next map when SHADE MAP > 0 (ALT-F6)
#define READ_ALL_MAPS   1001200     //ALT-F12               Read all levels of ALL maps.
                                    //                      Read all levels of maps. Goto point highest zoom level. SHIFT-D DRAWMAZES=OFF, SHIFT-F6: SHADE MAP=1, SHIFT-G: FORMULA=1, ALT-F12
#define READ_ALL_LEVEL  1001201     //SHIFT-F12             Read all levels of current map.
                                    //                      Goto point highest zoom level. SHIFT-D DRAWMAZES=OFF, ALT-F6: SHADE MAP=1, SHIFT-G: FORMULA=1, SHIFT-F12
#define BATCH_PICTURES1 1001300     //SHIFT+CTRL-t          Batch pictures funcion batch_pictures().
                                    //                      Keyboard: If COMBINE=ON ('c') batch_pictures2();
#define BATCH_PICTURES2 1001301     //SHIFT+CTRL-t          Batch pictures funcion batch_pictures2().
#define PIC_TO_MAZE2    1001302     //ALT+CTRL-t            Keyboard: If COMBINE=ON ('c') and picture from SHIFT-P: texture -> maze (type 2)
#define MAZE_TO_PIC     1001303     //ALT+CTRL-t                      and NO picture from SHIFT-P: maze -> texture
#define PIC_TO_MAZE1    1001304     //ALT+CTRL-t                      If combine is off, and picture form SHIFT-P: texture -> maze (type 1)
                                    //ALT+CTRL-t                      and NO picture from SHIFT-P: reverse maze
#define TEXT_TO-PIC     1001401     //ALT-t                 Plot text from list.txt file. list.txt in program dir contains filelist to text files to plot. First line of text file 1 needs to be empty.
                                    //                      The text will be printed with the selected font/size from CTRL-t
#define FONT_LOAD       1001402     //CTRL-t                Select random/next font. Change scale (SHIFT-PGUP/PGDN) and press CTRL-t again for larger/smaller size.
#define FONT_LOAD_NUM   1001403     //                      Load font num <num> from list. Usage: FONT_LOAD_NUM <num>
#define FONT_COLOR      1001404     //                      Set font color. Usage FONT_COLOR FF0000FF FFFFFFFF, for red inline and white outline color
#define FONT_SIZE       1001405     //                      Set font character size. Usage FONT_SIZE <char_size)
#define FONT_OUTLINE    1001406     //                      Set font outline size. Usage FONT_OUTLINE <outline_size)
#define BLACK_TO_TRANS  1001501     //SHITF-t               Make black transparant. See thresholds in pacman.ini
#define WHITE_TO_TRANS  1001502     //SHIFT-w               Make white transparant. (C coded. Make better with shader) See thresholds in pacman.ini
#define DARK_TO_TRANS   1001503     //SHIFT-a               Make dark transparant.
#define COLOR_TO_TRANS  1001504     //SHIFT-c               Make color transparant. See thresholds in pacman.ini (make bettter one with shader)
#define MAZE_TYPE       1001601     //t                     Change maze type. Usage: MAZE_TYPE <type>, 0 for normal (ghosts hunt pacman) or 1 for maze (ghosts go random)
#define SET_POINT       1001701     //p                     Keyboard: Toggle point of maze (big/normal) when DRAWMAZES=ON (SHIFT-d). Usage: SET_POINT <on/off> where 0 is off and 1 is on
#define SAVE_TEXTURES   1001702     //q                     Keyboard: Save (changed) files on/off. (When changed textures are nog neeeded. Maze will be generated new.....)
                                    //                      Usage: SAVE_TEXTURES <on/off> where 0=off and 1=on
#define MORE_GHOSTS     1001801     //+ or =                More ghosts.
#define LESS_GHOSTS     1001802     //-                     Less ghosts.
#define GHOSTS          1001901     //g                     Keyboard: Ghosts on/off. When in plot all mode (CTRL-Y) use it to set normal ghosts off, and use SHIFT-F9 for shader ghosts mode.
                                    //                      Usage: GHOSTS <on/off> where on=1 and off=0
#define GRAPHICS_MODE   1002001     //SHIFT-G               Select graphics mode. GRAPHICS_MODE 1 to plot throught shaders (ALT-F1,ALT-F2,CTRL-F2,ALT-F3).
                                    //                      GRAPHCIS_MODE 2 to shade new copy from original (overlap etc, holding original texturs as source, then copy all back)
                                    //                      When selected shader (ALT-F2), or MAP_MODE is 1 or 2, press SHIFT-F6 to generate shader/maps.
                                    //                      Shading zoom (www.local.com...) levels under constructions. (MAP_MODE=2, SHADER ON, GRAPHICS=1) (Shader over whole zoom level)
                                    //                      Set to background (SHIFT-d). Select GRAPHICS=1 (SHIFT-g). Select shader (SHIFT-F2/CTRL-F2) and/or picture (SHIFT-P). Press SHIFT-F6 to plot all screens.
                                    //                      (Will be separate manual). To plot geo maps set also SHADE MAP to 2 (ALT-F6 2x)
#define ROT_90          1002101     //SHFT+ALT-y            Rotate picture from SHIFT-p 90 degrees.
#define ROT_CURRENT     1002102     //SHFT+CTRL-y           Rotate picture from SHIFT-p to current angle.
#define CANVAS_RESET    1002201     //ALT-y                 Reset canvas (rotation/translation/etc.) from SHIFT-y
#define CANVAS          1002202     //CTRL-y                Keyboard: Load/unload canvas 8x8 bitmaps. Use numpad (NumLock=ON) and keys:
                                    //                      Usage CANVAS <on/off> where 0 is off and 1 is on
#define ROTATE_X_PLUS   1002203     //ALT-4                 rotate x Axis +
#define ROTATE_X_MIN    1002204     //ALT-6                 rotate x Axis -
#define TRANS_X_PLUS    1002205     //4                     translate x +
#define TRANS_X_MIN     1002206     //6                     translate x -
#define ROTATE_Y_PLUS   1002207     //ALT-8                 rotate y Axis +
#define ROTATE_Y_MIN    1002208     //ALT-2                 rotate y Axis -
#define TRANS_Y_PLUS    1002209     //8                     translate y +
#define TRANS_Y_MIN     1002210     //2                     translate y -
#define ROTATE_Z_PLUS   1002211     //ALT-7                 rotate z Axis +
#define ROTATE_Z_MIN    1002212     //ALT-1                 rotate z Axis -
#define TRANS_Z_PLUS    1002213     //7                     translate z +
#define TRANS_Z_MIN     1002214     //1                     translate z -
#define PERS_PLUS       1002215     //9                     perspective +
#define PERS_MIN        1002216     //3                     perspective -
#define PERS_PLUS_SLOW  1002217     //CTRL-9                perspective slow +
#define PERS_MIN_SLOW   1002218     //CTRL-3                perspective slow -
#define DIFFICULTY      1001400     //                      Else select 'difficulty'. Usage: DIFFICULTY <num>, where <num> is 1-4
#define GET_VIDEOS      1002300     //                      Get video's with youtube-dl. Place url's/links in ../convert/list.txt. Downloaded files end up in ../convert/files/
                                    //                      Conversion list (../convert/files/convert.txt) holds all the names audio/subtitle tracks.
#define BURN_SUBS       1002301     //                      (Live) auto burn subtitles downloaded with GET_VIDEOS. (Manual: 'R' (only record movie from 'b'), set FFMPEG_IN like FFMPEG_IN_SUBS, SET FFMPEG_M_ORIG like FFMPEG_M_ORIG_AUDIO,
                                    //                      'r' start recording(pause), 'b' start movie extern, SHIFT-r start recording.
                                    //                      Uses ../convert/files/convert.txt list from GET_VIDEO'S
                                    //                      BURN_SUBS automaticly takes right FFMPEG COMMANDS. (FFMPEG_IN_SUBS & FFMPEG_M_ORIG_AUDIO) (Manual: FFMPEG_IN & FFMPEG_M_ORIG) (pacman.ini).
#define BACKGROUND      1002401     //SHFT-d                SET TO BACKGROUND
#define FOREGROUND      1002402     //SHFT-d                SET TO FORGROUND
#define PLOT_ALL        1002403     //SHFT-F6               PLOT_ALL_TEXTURES
#define LIST_END        0
/*
*/

#endif // KEYLIST_HPP
