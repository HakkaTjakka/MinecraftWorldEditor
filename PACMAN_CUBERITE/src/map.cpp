#define SFML_STATIC
#undef UNICODE
#include <winsock2.h>
#include <io.h>
#include "WinMain.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sys/stat.h>
#include <iostream>
#include <cstdlib>
#include <Windows.h>
#include <Winuser.h>
#include <assert.h>
#include <vector>
#include <cmath>
#include <time.h>
#include <dirent.h>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <SFML/System/Mutex.hpp>
#include <SFML/Network/IpAddress.hpp>
#include <sfeMovie/Movie.hpp>
#include "StreamSelector.hpp"
#include <SFML/OpenGL.hpp>
#include <GL/glext.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include "MediaInfo.hpp"
#define soft_buffer 5000
extern char SAS_LAYER[];
extern int internetfile;
extern int movie;
extern int ffmpegfile;
extern int pacman;
int blend_tiles=0;
extern int soft_jump;
extern float fps_float;
extern int move_slow;
extern int generate_tiles;
extern sf::Sprite sprite_from_canvas;
extern int plot_cubes;
extern int kleur_front;
extern int eatmode;
extern int loaded_picture;
void DRAWMAZE(int totalx,int totaly);
extern int flippo;
extern int start_posx;
extern int start_posy;
extern void cleanupbitmaps_mazes();
extern int shift;
extern int drawmazes;
int first1=0;
int first2=0;
extern int pacman_move;
#include <glm/glm.hpp>
#include <glm/common.hpp>
extern int move_config;
extern std::vector<glm::ivec2> wierdo_requests;
extern std::vector<glm::ivec2> wierdo_requests_ready;
extern std::vector<std::string> wierdo_filenames;

extern int posx;
extern int posy;

int position1x=2912,position1y=1656;
int position2x=2912,position2y=1656;
extern int picturex;
extern int picturey;
extern float 	*fpos_ghostx;
extern float 	*fpos_ghosty;
extern int follow_ghost_num;
extern int follow_ghost;

extern int long_jump;
extern int mem_posx;
extern int mem_posy;
extern float mem_fposx;
extern float mem_fposy;
extern int mem_picturex;
extern int mem_picturey;

extern int forced_jump;
extern int follow_ghost;
extern int *pos_ghostx;
extern int *pos_ghosty;
extern int real_posx2;
extern int real_posy2;
extern int maxpixelsx;
extern int maxpixelsy;
extern int follow_ghost_num;
extern int DONTSAVEFILES;
extern int real_posx;
extern int real_posy;
extern int first_follow;
extern int pen;
extern int lookahead;
extern void savedata(char *naam, int data);
extern int new_picturex;
extern int new_picturey;
extern int new_posx;
extern int new_posy;
extern float new_fposx;
extern float new_fposy;
extern int new_verschilx2;
extern int new_verschily2;
extern int render_picturex;
extern int render_picturey;
extern int render_posx;
extern int render_posy;
extern int new_verschilx;
extern int new_verschily;
extern void ReadBitmaps4();
extern float *fspeed_ghostx;
extern float *fspeed_ghosty;
extern int MAXINMEM;
extern int used_maxinmem[];
extern int  **used2;
extern int totalused;
extern char error_msg4[];
extern int error_flag4;
extern sf::RenderTexture *texturemaxinmempoint[];
extern int formula;
extern char **files;
extern char **files_mazes;
extern void draw2(char *towrite, int xpos, int ypos, sf::Color inner, sf::Color outer);
extern sf::RenderWindow SFMLView1;
extern int wierdo(int totalx, int totaly, int silent);
extern char **changed;
extern int totalchanged;
extern sf::Sprite spritedot;
void putinmazeSFML(int totalx,int totaly);
extern void go_save_some_bitmaps();
extern int F2;

extern MSG msg;
extern void HANDLEEVENTS();

int map_end_x=0;
int map_end_y=0;
extern sf::RenderTexture texturemaxinmem[];

int blocked=0;
extern int sync;
extern char text_line2[];
extern char text_line3[];
extern char text_line4[];
extern int totalfiles;
extern int totalfiles_mazes;
extern int monitor_off;
extern SAVEALLBITMAPS();

int do_all=0;
int dont_stop=0;
extern int ending1_x;
extern int ending2_x;
extern int ending3_x;
extern int ending1_y;
extern int ending2_y;
extern int ending3_y;
extern setinternetfile();
extern sf::Texture texture_from_internet;
extern void add_border(sf::Texture * MyTexture);
extern sf::Sprite sprite_from_internet;
extern char **Maze;
extern int loaded_from_maze;
extern int mazesizex;
extern int mazesizey;
extern void ReadBitmaps2_remote(int picturex, int picturey);
extern int mirror;
extern int pen_mode;
extern void do_mirror(int mazemovex,int mazemovey,int blokje);
extern int BITMAPSX;
extern int BITMAPSY;
extern int level;
extern int check_dir(int BITMAPSX,int BITMAPSY,int level);
extern int combine;
extern int	plotx;
extern int	ploty;
extern char *line;
extern void blitter(char * line, int mode);
extern char error_msg[];
extern int error_flag;
extern char error_msg_s[];
extern int error_flag_s;
extern char error_msg2[];
extern int error_flag2;
sf::Mutex user_mutex;
extern void kiki();
extern char MAPDIR[];
extern int offset_picture_x;
extern int offset_picture_y;
extern int plot_all;
extern sf::RenderTexture texture_point;
extern sf::Image image_point;
extern sf::Sprite sprite_point;
extern sf::Color pixel_color;
extern int SFML;
extern int remote_points;
extern float fhapper2;
extern int soundloop;
extern void playSound();
extern float fspeed_adjust;
extern int mazemovex;
extern int mazemovey;
extern int hunt;
extern int hunt_counter;
extern int hunt_max;
extern int playsound;

extern int set_transparant;
int movex1=0;
int movex2=0;
int movey1=0;
int movey2=0;

extern int skipclear;
extern int local_points;
extern int server;
extern int client;
extern int mazetype;
extern int breed,hoog;
extern int skipcount;

extern int remote_posx;
extern int remote_posy;
extern float fposx;
extern float fposy;
extern void ReadBitmaps2();
extern int connected;
extern int playerleft;
extern char writer[];
extern void SEND(char *towrite);
extern int speedx_new;
extern int speedy_new;
extern float fspeedx_new;
extern float fspeedy_new;
extern int speedx;
extern int speedy;
extern float fspeedx;
extern float fspeedy;
extern int maze_up_new;
extern int maze_down_new;
extern int maze_left_new;
extern int maze_right_new;
extern int maze_up;
extern int maze_down;
extern int maze_left;
extern int maze_right;
extern int sending_pos;


extern int adapt_maze;
extern sf::VertexArray m_pointCloud_map0;
extern sf::VertexArray m_pointCloud_map1;
extern int autodraw;
extern sf::Color background_color[];

int go_pos=0;


extern sf::Sprite *spritemaxinmempoint[];
extern void blitter2();
int go_blit=0;
extern sf::Mutex render_mutex;

int DONTREADBITMAPS=0;
extern sf::Texture sfml_bitmaps;
extern void launch_monimem();
void launch_background_blitter();
extern int monitor;
extern sf::Mutex loader_mutex;   ;
extern int forced_speed;
int background_loader=0;
extern int blank_maze;
extern int drawmazes;
int once=0;
extern int maze_plotsizex;
extern int maze_plotsizey;
extern int replace_str(char *str, char *orig, char *rep);
int helpme=0;
extern char LEVELDIR[];
extern char PICTUREDIR[];
extern int replace_str(char *str, char *orig, char *rep);
extern int goexit;
extern int ESCAPE;
extern int shade_map;
extern sf::RenderWindow window_1;
extern sf::RenderWindow window_2;
extern sf::RenderWindow window_3;
extern int window_1_active;
extern int window_2_active;
extern int window_3_active;
extern sf::Vector2i mytotal1;
extern sf::Vector2i mytotal2;
extern sf::Vector2i mytotal3;
extern int loader1_active;
extern int loader2_active;
extern int loader3_active;
extern void launch_background_loader_one();
extern void launch_background_loader_two();
extern void launch_background_loader_three();

double xdiff2=0;
double ydiff2=0;

extern int get_map_x,get_map_y,get_map_zoom;
int ret=0;
extern int SAS_STARTX;
extern int SAS_STARTY;
extern int SAS_ZOOM;

double smooth_x=0.0;
double smooth_y=0.0;

double avg_speedx=0.0;
double avg_speedy=0.0;
extern CLEANBITMAPS();
extern int LOADED_SEED;
extern int SEED;
extern int MAZEOFF;
extern int mazetype;
extern int crossing;
extern int maxpicturex;
extern int maxpicturey;
extern int totalpicturex;
extern int totalpicturey;
extern int xdraw,ydraw;
extern int mapx,mapy;
extern char **maze_plot;
extern char **used;
extern void RenderBlit_total(int totalx,int totaly, int xdest, int ydest, int width, int height, int xsource, int ysource, int remote_pen_mode);
extern void RenderBlit_adapt(int totalx,int totaly, int xdest, int ydest, int width, int height, int xsource, int ysource, int remote_pen_mode);
extern int force_game;
sf::Color background_color[2]={sf::Color(0,0,0,0),sf::Color(0,0,0,0)};
extern bool file_exists(const char * filename);
extern void ReadSFML(char * naam, int x, int y, int draw);
extern int kill1,kill2,kill3;
void LOAD_MAP_FOR_ALL_BITMAPS();

void adapt(int mazemovex, int mazemovey)
{
    int mapx,mapy;
    int posx;
    int posy;
    int picturex;
    int picturey;
    int remote_posx;
    int remote_posy;
    int xdraw,ydraw;

    if (blank_maze==1) return;

    int blokje=maze_plot[mazemovex][mazemovey];
//    if ((blokje&128)==128) return;

    remote_posx=((mazemovex+45)%(30*(maxpicturex+1)))*64;
    remote_posy=((mazemovey+23)%(15*(maxpicturey+1)))*72;
    remote_posx=(remote_posx+32)%((totalpicturex)*1920);

    picturex=remote_posx/1920;
    posx=remote_posx-1920*picturex;

    picturey=remote_posy/1080;
    posy=remote_posy-1080*picturey;

    posx=-posx;
    posy=-posy;

    xdraw=(-posx+960);
    if (xdraw>=1920)
    {
        xdraw=xdraw-1920;
        mapx=1;
    }
    else
        mapx=0;
    ydraw=(-posy+540);
    if (ydraw>=1080)
    {
        ydraw=ydraw-1080;
        mapy=1;
    }
    else
        mapy=0;

    int arx=(picturex+mapx)%(maxpicturex+1);
    int ary=(picturey+mapy)%(maxpicturey+1);


    if ((blokje&1)==0 && (blokje&2)==0) blokje=blokje&(255-64);
    if ((blokje&4)==0 && (blokje&8)==0) blokje=blokje&(255-32);
    maze_plot[mazemovex][mazemovey]=blokje;

    if (used[arx][ary]==1 && (blank_maze==0 || drawmazes==1))
    {
        if ((blokje&16)==16)
        {
            if ((blokje&32)==32) {
                RenderBlit_adapt(arx,ary, xdraw-32, ydraw-36, 64, 72, (3)*64, 13*72, 1);
                RenderBlit_adapt(arx,ary, xdraw-32, ydraw-36, 64, 72, (12)*64, 13*72, 0);
            } else if ((blokje&64)==64) {
                RenderBlit_adapt(arx,ary, xdraw-32, ydraw-36, 64, 72, (12)*64, 13*72, 1);
                RenderBlit_adapt(arx,ary, xdraw-32, ydraw-36, 64, 72, (3)*64, 13*72, 0);
            } else
                RenderBlit_adapt(arx,ary, xdraw-32, ydraw-36, 64, 72, (blokje&15)*64, 13*72, 1);
        }
        else
        {
            if ((blokje&32)==32) {
                RenderBlit_adapt(arx,ary, xdraw-32, ydraw-36, 64, 72, (3)*64, 13*72, 1);
                RenderBlit_adapt(arx,ary, xdraw-32, ydraw-36, 64, 72, (12)*64, 13*72, 0);
            } else if ((blokje&64)==64) {
                RenderBlit_adapt(arx,ary, xdraw-32, ydraw-36, 64, 72, (12)*64, 13*72, 1);
                RenderBlit_adapt(arx,ary, xdraw-32, ydraw-36, 64, 72, (3)*64, 13*72, 0);
            } else
                RenderBlit_adapt(arx,ary, xdraw-32, ydraw-36, 64, 72, (blokje&15)*64, 13*72, 1);
        }
    }
    return;
}

void adapt2(int mazemovex, int mazemovey)
{
    int mapx,mapy;
    int posx;
    int posy;
    int picturex;
    int picturey;
    int remote_posx;
    int remote_posy;
    int xdraw,ydraw;

    if (blank_maze==1) return;

    int blokje=maze_plot[mazemovex][mazemovey];
//    if ((blokje&128)==128) return;

    remote_posx=((mazemovex+45)%(30*(maxpicturex+1)))*64;
    remote_posy=((mazemovey+23)%(15*(maxpicturey+1)))*72;
    remote_posx=(remote_posx+32)%((totalpicturex)*1920);

    picturex=remote_posx/1920;
    posx=remote_posx-1920*picturex;

    picturey=remote_posy/1080;
    posy=remote_posy-1080*picturey;

    posx=-posx;
    posy=-posy;

    xdraw=(-posx+960);
    if (xdraw>=1920)
    {
        xdraw=xdraw-1920;
        mapx=1;
    }
    else
        mapx=0;
    ydraw=(-posy+540);
    if (ydraw>=1080)
    {
        ydraw=ydraw-1080;
        mapy=1;
    }
    else
        mapy=0;

    int arx=(picturex+mapx)%(maxpicturex+1);
    int ary=(picturey+mapy)%(maxpicturey+1);


    if ((blokje&1)==0 && (blokje&2)==0) blokje=blokje&(255-64);
    if ((blokje&4)==0 && (blokje&8)==0) blokje=blokje&(255-32);
    maze_plot[mazemovex][mazemovey]=blokje;

    if (used[arx][ary]==1 && (blank_maze==0 || drawmazes==1))
    {
        if ((blokje&16)==16)
        {
//crossing
            if ((blokje&32)==32) {
                RenderBlit_total(arx,ary, xdraw-32, ydraw-36, 64, 72, (3)*64, 9*72, 1);
                RenderBlit_total(arx,ary, xdraw-32, ydraw-36, 64, 72, (12)*64, 9*72, 0);
            } else if ((blokje&64)==64) {
                RenderBlit_total(arx,ary, xdraw-32, ydraw-36, 64, 72, (12)*64, 9*72, 1);
                RenderBlit_total(arx,ary, xdraw-32, ydraw-36, 64, 72, (3)*64, 9*72, 0);
            } else
                RenderBlit_total(arx,ary, xdraw-32, ydraw-36, 64, 72, (blokje&15)*64, 9*72, 1);
        }
        else
        {
            if ((blokje&32)==32) {
                RenderBlit_total(arx,ary, xdraw-32, ydraw-36, 64, 72, (3)*64, 0, 1);
                RenderBlit_total(arx,ary, xdraw-32, ydraw-36, 64, 72, (12)*64, 0, 0);
            } else if ((blokje&64)==64) {
                RenderBlit_total(arx,ary, xdraw-32, ydraw-36, 64, 72, (12)*64, 0, 1);
                RenderBlit_total(arx,ary, xdraw-32, ydraw-36, 64, 72, (3)*64, 0, 0);
            } else
                RenderBlit_total(arx,ary, xdraw-32, ydraw-36, 64, 72, (blokje&15)*64, 0, 1);
        }
    }
    return;
}



void save_map()
{
    FILE* file;
    int xx,yy;
    char naam[200];
    int mazeprintx;
    int mazeprinty;


//change
    check_dir(BITMAPSX,BITMAPSY,level);
//    sprintf(naam,"levels/%dx%d/%03d/map.dat",BITMAPSX,BITMAPSY,level);
    sprintf(naam,"%s/%dx%d/%03d/map.dat",LEVELDIR,BITMAPSX,BITMAPSY,level);
    file = fopen (naam, "wb");

    if (combine==0)
    {
        plotx=0;
        ploty=0;
    }
    int tot=totalpicturex*30;
    int scount=100;
    if (file!=NULL)
    {
        for (xx=0; xx<((maxpicturex+1)*30); xx++)
        {
            scount--;
            if (scount==0)
            {
                scount=500;
                sprintf(line,"SAVING MAP %s LINE=%d/%d\n", naam,xx,tot);
                blitter(line,1);
            }

            for (yy=0; yy<((maxpicturey+1)*15); yy++)
            {

                mazeprintx=(xx + plotx+(maxpicturex+1)*30 )%((maxpicturex+1)*30);
                mazeprinty=(yy + ploty+(maxpicturey+1)*15 )%((maxpicturey+1)*15);

                fputc(maze_plot[mazeprintx][mazeprinty],file);
            }
        }
        sprintf(line,"SAVING MAP %s LINE=%d/%d\n", naam,xx,tot);
        blitter(line,1);

        fclose (file);
    }
    combine=0;
    strcpy(error_msg,"SAVED: ");
    strcat(error_msg,naam);
    error_flag=1;
    return;
}


void save_map_last()
{
    FILE* file;
    int xx,yy;
    char naam[200];

//change
    check_dir(BITMAPSX,BITMAPSY,0);
//    sprintf(naam,"levels/%dx%d/%03d/map.dat",BITMAPSX,BITMAPSY,0);
    sprintf(naam,"%s/%dx%d/%03d/map.dat",LEVELDIR,BITMAPSX,BITMAPSY,0);

//	sprintf(naam,"levels/%dx%d/lastmap.dat",BITMAPSX,BITMAPSY);
    file = fopen (naam, "wb");

    int tot=totalpicturex*30;
    int scount=100;
    if (file!=NULL)
    {
        for (xx=0; xx<((maxpicturex+1)*30); xx++)
        {
            scount--;
            if (scount==0)
            {
                scount=500;
                sprintf(line,"SAVING LAST MAP %s LINE=%d/%d\n", naam,xx,tot);
                blitter(line,1);
            }

            for (yy=0; yy<((maxpicturey+1)*15); yy++)
            {
                fputc(maze_plot[xx][yy],file);
            }
        }
        sprintf(line,"SAVING LAST MAP %s LINE=%d/%d\n", naam,xx,tot);
        blitter(line,1);

        fclose (file);
    }
    strcpy(error_msg,"SAVED: ");
    strcat(error_msg,naam);
    error_flag=1;
    return;
}

extern int total_points;

void load_map_last()
{
    FILE* file;
    int xx,yy;
    int i;
    int points;
    char naam[200];
    total_points=0;

//change
//    sprintf(naam,"levels/%dx%d/%03d/map.dat",BITMAPSX,BITMAPSY,0);
    sprintf(naam,"%s/%dx%d/%03d/map.dat",LEVELDIR,BITMAPSX,BITMAPSY,0);

//	sprintf(naam,"levels/%dx%d/lastmap.dat",BITMAPSX,BITMAPSY);
    file = fopen (naam, "rb");

    if (file!=NULL)
    {
        points=0;

        int tot=totalpicturex*30;
        int scount=100;
        for (xx=0; xx<((maxpicturex+1)*30); xx++)
        {
            scount--;
            if (scount==0)
            {
                scount=500;
                sprintf(line,"LOADING LAST MAP %s LINE=%d/%d\n", naam,xx,tot);
                blitter(line,1);
            }
            for (yy=0; yy<((maxpicturey+1)*15); yy++)
            {
                maze_plot[xx][yy]=fgetc(file);
                if ((maze_plot[xx][yy]&15) > 0)
                {
                    points=points+2;
                    if ((maze_plot[xx][yy] & (1))==1 )
                        points=points+1;
                    if ((maze_plot[xx][yy] & (2))==2 )
                        points=points+1;
                    if ((maze_plot[xx][yy] & (4))==4 )
                        points=points+1;
                    if ((maze_plot[xx][yy] & (8))==8 )
                        points=points+1;
                }
            }
        }
        sprintf(line,"LOADING LAST MAP %s LINE=%d/%d\n", naam,xx,tot);
        blitter(line,1);
        total_points=points/2;
        fclose (file);
    }
    strcpy(error_msg,"LOADED: ");
    strcat(error_msg,naam);
    error_flag=1;
    return;
}

void load_map()
{
    FILE* file;
    int xx,yy;
    int i;
    int points;
    char naam[200];
    int mazeprintx;
    int mazeprinty;

    total_points=0;

//change
//    sprintf(naam,"levels/%dx%d/%03d/map.dat",BITMAPSX,BITMAPSY,level);
    sprintf(naam,"%s/%dx%d/%03d/map.dat",LEVELDIR,BITMAPSX,BITMAPSY,level);
//		sprintf(naam,"levels/%dx%d/map%d.dat",BITMAPSX,BITMAPSY,level);

    file = fopen (naam, "rb");
    if (file==NULL)
    {
        strcpy(error_msg,"FILE NOT FOUND: ");
        strcat(error_msg,naam);
        error_flag=1;

        return;
    }

    if (combine==0)
    {
        plotx=0;
        ploty=0;
    }

    if (file!=NULL)
    {
        points=0;

        int tot=totalpicturex*30;
        int scount=100;
        for (xx=0; xx<((maxpicturex+1)*30); xx++)
        {
            scount--;
            if (scount==0)
            {
                scount=500;
                sprintf(line,"LOADING MAP %s LINE=%d/%d\n", naam,xx,tot);
                blitter(line,1);
            }

            for (yy=0; yy<((maxpicturey+1)*15); yy++)
            {

                mazeprintx=(xx + plotx+(maxpicturex+1)*30 )%((maxpicturex+1)*30);
                mazeprinty=(yy + ploty+(maxpicturey+1)*15 )%((maxpicturey+1)*15);

                if (combine==1) {
                    int blokje=maze_plot[mazeprintx][mazeprinty];
                    maze_plot[mazeprintx][mazeprinty]=maze_plot[mazeprintx][mazeprinty] | fgetc(file);
                    if ((maze_plot[mazeprintx][mazeprinty]&(32+64))==(32+64) ) {
                        if (crossing==1) maze_plot[mazeprintx][mazeprinty]=maze_plot[mazeprintx][mazeprinty]&(255-64);
                        else if (crossing==2) maze_plot[mazeprintx][mazeprinty]=maze_plot[mazeprintx][mazeprinty]&(255-32);
                        else if ((blokje&32)==32) maze_plot[mazeprintx][mazeprinty]=maze_plot[mazeprintx][mazeprinty]&(255-64);
                        else maze_plot[mazeprintx][mazeprinty]=maze_plot[mazeprintx][mazeprinty]&(255-32);
                    } else if ((maze_plot[mazeprintx][mazeprinty]&(32+64+15))==15 && crossing>0) {
                        if (crossing==1) maze_plot[mazeprintx][mazeprinty]=maze_plot[mazeprintx][mazeprinty]|32;
                        else if (crossing==2) maze_plot[mazeprintx][mazeprinty]=maze_plot[mazeprintx][mazeprinty]|64;
                    }
//hoppa
                    if (mazetype==1) {
                        if ((blokje&16)==16)
                        {
                            blokje=blokje & (15+32+64);
                            if ((blokje&15)==1 || (blokje&15)==2 || (blokje&15)==4 || (blokje&15)==8) {
//hoihoi
//                                    if (!(rand()%10)) blokje=blokje|16;
                                    blokje=blokje|16;
                            }
                        }
                    }
                }
                else
                    maze_plot[mazeprintx][mazeprinty]=fgetc(file);

                if ((maze_plot[mazeprintx][mazeprinty]&15) > 0)
                {
                    points=points+2;

                    if ((maze_plot[mazeprintx][mazeprinty] & (1))==1 )
                        points=points+1;
                    if ((maze_plot[mazeprintx][mazeprinty] & (2))==2 )
                        points=points+1;
                    if ((maze_plot[mazeprintx][mazeprinty] & (4))==4 )
                        points=points+1;
                    if ((maze_plot[mazeprintx][mazeprinty] & (8))==8 )
                        points=points+1;
                }
            }
        }
        sprintf(line,"LOADING MAP %s LINE=%d/%d\n", naam,xx,tot);
        blitter(line,1);
        total_points=points/2;
        fclose (file);
    }
    combine=0;
    strcpy(error_msg,"LOADED: ");
    strcat(error_msg,naam);
    error_flag=1;
    return;
}

void count_points()
{
    int points=0;

    int xx,yy;

    for (xx=0; xx<((maxpicturex+1)*30); xx++)
    {
        for (yy=0; yy<((maxpicturey+1)*15); yy++)
        {
            if ((maze_plot[xx][yy]&15) > 0)
            {
                points=points+2;
                if ((maze_plot[xx][yy] & (1))==1 )
                    points=points+1;
                if ((maze_plot[xx][yy] & (2))==2 )
                    points=points+1;
                if ((maze_plot[xx][yy] & (4))==4 )
                    points=points+1;
                if ((maze_plot[xx][yy] & (8))==8 )
                    points=points+1;
            }
        }
    }
    total_points=points/2;
    return;
}



void set_position1()
{
    if (first1==0)
    {
        strcpy(error_msg,"PRESS AGAIN TO CONFIRM POSITION 1 SET");
        error_flag=1;
        first1=1;
        return;
    }
    first1=0;
    strcpy(error_msg,"POSITION 1 SET");
    error_flag=1;

//pospos
/* pposx!!!!!!!!!!!
    int pposx=posx-posx%64-32;
    if (posx<=-1920)
        posx=posx+1920;
    int pposy=posy-(posy-36)%72-36;
    if (posy<=-1080)
        posy=posy+1080;
*/
/*
    posx=posx-posx%64-32;
    if (posx<=-1920) {
        posx=posx+1920;
        picturex=(picturex+1+totalpicturex)%totalpicturex;
    }
    posy=posy-(posy-36)%72-36;
    if (posy<=-1080) {
        posy=posy+1080;
        picturey=(picturey+1+totalpicturey)%totalpicturey;
    }
    fposx=posx;
    fposy=posy;
    ReadBitmaps2();
*/
    position1x=(picturex*1920-posx);
    position1y=(picturey*1080-posy);

    movex1=(picturex*1920-posx-32)/64;
    movey1=(picturey*1080-posy   )/72;
    movex1=(movex1-45+60*(maxpicturex+1))%(30*(maxpicturex+1));
    movey1=(movey1-23+30*(maxpicturey+1))%(15*(maxpicturey+1));
}


void set_position2()
{
    if (first2==0)
    {
        strcpy(error_msg,"PRESS AGAIN TO CONFIRM POSITION 2 SET");
        error_flag=1;
        first2=1;
        return;
    }
    first2=0;
    strcpy(error_msg,"POSITION 2 SET");
    error_flag=1;

/* pposx!!!!!!!!!!!
/*
    int pposx=posx-posx%64-32;
    if (posx<=-1920)
        posx=posx+1920;
    int pposy=posy-(posy-36)%72-36;
    if (posy<=-1080)
        posy=posy+1080;
*/

/*
    posx=posx-posx%64-32;
    if (posx<=-1920) {
        posx=posx+1920;
        picturex=(picturex+1+totalpicturex)%totalpicturex;
    }
    posy=posy-(posy-36)%72-36;
    if (posy<=-1080) {
        posy=posy+1080;
        picturey=(picturey+1+totalpicturey)%totalpicturey;
    }
    fposx=posx;
    fposy=posy;
    ReadBitmaps2();
*/

    position2x=(picturex*1920-posx);
    position2y=(picturey*1080-posy);

    movex2=(picturex*1920-posx-32)/64;
    movey2=(picturey*1080-posy   )/72;
    movex2=(movex2-45+60*(maxpicturex+1))%(30*(maxpicturex+1));
    movey2=(movey2-23+30*(maxpicturey+1))%(15*(maxpicturey+1));

    hoog  =(1+59+movex2);
    breed =(1+30+movey2);
}

void goto_ghost()
{
    smooth_x=-(fpos_ghostx[follow_ghost_num])+1920.0;
    smooth_y=-(fpos_ghosty[follow_ghost_num])+1080.0;
    int x=smooth_x;
    int y=smooth_y;

    picturex=x/1920;
    posx=x-1920*picturex;

    picturey=y/1080;
    posy=y-1080*picturey;

    posx=-posx;
    posy=-posy;

    posx=posx-posx%64-32;
    if (posx<=-1920) {
        posx=posx+1920;
        picturex=(picturex+1+totalpicturex)%totalpicturex;
    }
    posy=posy-(posy-36)%72-36;
    if (posy<=-1080) {
        posy=posy+1080;
        picturey=(picturey+1+totalpicturey)%totalpicturey;
    }
    fposx=posx;
    fposy=posy;

    if (connected==1 || playerleft==0)
    {
        int mazemovex=(picturex*1920-posx-32)/64;
        int mazemovey=(picturey*1080-posy   )/72;
        mazemovex=(mazemovex-45+60*(totalpicturex))%(30*(totalpicturex));
        mazemovey=(mazemovey-23+30*(totalpicturey))%(15*(totalpicturey));
        sprintf(writer,"T=GOTO,X=%d,Y=%d,\0",mazemovex,mazemovey);
        SEND(writer);
    }
    speedy_new=0;
    speedx_new=0;
    fspeedy_new=0;
    fspeedx_new=0;
    speedy=0;
    speedx=0;
    fspeedy=0;
    fspeedx=0;
    maze_up_new=0;
    maze_down_new=0;
    maze_left_new=0;
    maze_right_new=0;
    maze_up=0;
    maze_down=0;
    maze_left=0;
    maze_right=0;
    sending_pos=0;
    if (follow_ghost==1) {
        mem_picturex=picturex;
        mem_picturey=picturey;
        mem_posx=posx;
        mem_posy=posy;
        mem_fposx=fposx;
        mem_fposy=fposy;
    }
}

void goto_partner()
{
    int x=remote_posx;
    int y=remote_posy;

    picturex=x/1920;
    posx=x-1920*picturex;

    picturey=y/1080;
    posy=y-1080*picturey;

    posx=-posx;
    posy=-posy;

    posx=posx-posx%64-32;
    if (posx<=-1920) {
        posx=posx+1920;
        picturex=(picturex+1+totalpicturex)%totalpicturex;
    }
    posy=posy-(posy-36)%72-36;
    if (posy<=-1080) {
        posy=posy+1080;
        picturey=(picturey+1+totalpicturey)%totalpicturey;
    }
    fposx=posx;
    fposy=posy;

    ReadBitmaps2();

    if (connected==1 || playerleft==0)
    {
        int mazemovex=(picturex*1920-posx-32)/64;
        int mazemovey=(picturey*1080-posy   )/72;
        mazemovex=(mazemovex-45+60*(totalpicturex))%(30*(totalpicturex));
        mazemovey=(mazemovey-23+30*(totalpicturey))%(15*(totalpicturey));
        sprintf(writer,"T=GOTO,X=%d,Y=%d,\0",mazemovex,mazemovey);
        SEND(writer);
    }
    speedy_new=0;
    speedx_new=0;
    fspeedy_new=0;
    fspeedx_new=0;
    speedy=0;
    speedx=0;
    fspeedy=0;
    fspeedx=0;
    maze_up_new=0;
    maze_down_new=0;
    maze_left_new=0;
    maze_right_new=0;
    maze_up=0;
    maze_down=0;
    maze_left=0;
    maze_right=0;
    sending_pos=0;
}


void set_pacman()
{
//    long_jump=1;
//    printf("1\n");
    posx=mem_posx;
    posy=mem_posy;
    fposx=mem_fposx;
    fposy=mem_fposy;
    picturex=mem_picturex;
    picturey=mem_picturey;
    ReadBitmaps2();
//    forced_jump=1;
}

#define array_len  400

extern int DO_ADAPT;
extern int combine;
extern int crossing;

void follow_ghost_pos()
{
    if (DO_ADAPT) {
        render_picturex=picturex;
        render_picturey=picturey;
        render_posx=posx;
        render_posy=posy;
        smooth_x=((double)picturex*1920.0-fposx);
        smooth_y=((double)picturey*1080.0-fposy);
//        mem_picturex=picturex;
//        mem_picturey=picturey;
//        mem_posx=posx;
//        mem_posy=posy;
//        mem_fposx=fposx;
//        mem_fposy=fposy;
//        ReadBitmaps2();
//        ReadBitmaps4();
        return;
    }
    static double distance;
    static double distance2;

    static double distance2x=0.0;
    static double distance2x_old=0.0;

    static double distance2y=0.0;
    static double distance2y_old=0.0;

    static int followx[array_len];
    static int followy[array_len];
    static int follow_ghost_num_old=-1;
    static int follow_countx=0;
    static int follow_county=0;
    static int last=1;
    static int last2=1;
    static double verschilx;
    static double verschily;
    int x_old,y_old;
    static double verschilx2;
    static double verschily2;
    static double slow_xdiff2=0.0;
    static double slow_ydiff2=0.0;

    int old_render_picturex=render_picturex;
    int old_render_picturey=render_picturey;
    int old_render_posx=render_posx;
    int old_render_posy=render_posy;
    int old_smoothx=smooth_x;
    int old_smoothy=smooth_y;
    int old_picturex=picturex;
    int old_picturey=picturey;
    int old_posx=posx;
    int old_posy=posy;
    float old_fposx=fposx;
    float old_fposy=fposy;

    int remem_posx=mem_posx;
    int remem_posy=mem_posy;
    float remem_fposx=mem_fposx;
    float remem_fposy=mem_fposy;
    int remem_picturex=mem_picturex;
    int remem_picturey=mem_picturey;

    int x;
    int y;

    if (follow_ghost==1)
    {
        x=-(pos_ghostx[follow_ghost_num]);
        y=-(pos_ghosty[follow_ghost_num]);
    }
    else
    {
        x=(picturex*1920-posx)-1920;
        y=(picturey*1080-posy)-1080;
    }

    int rx,ry;
    rx=(render_picturex*1920-render_posx)-1920;
    ry=(render_picturey*1080-render_posy)-1080;

    int do_reset=0;
    int adaptx=0;
    int adapty=0;
    int jo_verschilx;
    int jo_verschily;
    if (soft_jump==0)
    {
        jo_verschilx=(-real_posx2-x);
        jo_verschily=(-real_posy2-y);
        if (jo_verschilx<-maxpixelsx/2) {
            jo_verschilx=jo_verschilx+maxpixelsx;
            adaptx=maxpixelsx;
        } else if (jo_verschilx>maxpixelsx/2) {
            jo_verschilx=jo_verschilx-maxpixelsx;
            adaptx=-maxpixelsx;
        }
        if (abs(jo_verschilx)>6000) {
            forced_jump=1;
            last=1;
        }

        if (jo_verschily<-maxpixelsy/2) {
            jo_verschily=jo_verschily+maxpixelsy;
            adapty=maxpixelsy;
        } else if (jo_verschily>maxpixelsy/2) {
            jo_verschily=jo_verschily-maxpixelsy;
            adapty=-maxpixelsy;
        }
        if (abs(jo_verschily)>8000) {
            forced_jump=1;
            last=1;
        }
        distance=sqrt(jo_verschilx*jo_verschilx+jo_verschily*jo_verschily);
        if (DONTSAVEFILES==1) {
            if (distance<3000) long_jump=0;
        } else if (distance<3000) long_jump=0;
        if (distance>3000) {
            long_jump=1;
            last=1;
        }
        if (last==1 && (follow_ghost==0) ) {
//                long_jump=1;
            do_reset=1;
        }
        if (last==0 && (follow_ghost==1) ) {
//                 long_jump=1;
            do_reset=1;

        }
        if (last2==0 && (flippo==1) ) {
//                long_jump=1;
            last2=1;
            do_reset=1;
        }
        if (last2==1 && (flippo==0) ) {
//                long_jump=1;
            last2=0;
            do_reset=1;
        }

        if ((adaptx!=0 || adapty!=0) && long_jump==0) {
            for (int i=0; i<array_len; i++) {
                if (adaptx!=0) followx[i]=followx[i]+adaptx;
                if (adapty!=0) followy[i]=followy[i]+adapty;
            }
        }
    }
    if (follow_ghost==1) last=1;

    real_posx2=-x;
    real_posy2=-y;

    x=(x+maxpixelsx+1920);
    y=(y+maxpixelsy+1080);
    rx=(rx+maxpixelsx+1920);
    ry=(ry+maxpixelsy+1080);

    real_posx=x;
    real_posy=y;
//    printf("last2=%d flippo=%d distance2=%f distance=%f long_jump=%d first_follow=%d forced_jump=%d follow_countx=%d follow_county=%d last=%d xdiff2=%f ydiff2=%f\n",
//            last2,flippo,distance2,distance,long_jump,first_follow,forced_jump,follow_countx,follow_county,last,xdiff2,ydiff2);

    float sfspeedx,sfspeedy;
    if (follow_ghost==1 || flippo==1) {
        sfspeedx=fabs(fspeed_ghostx[follow_ghost_num]);
        sfspeedy=fabs(fspeed_ghosty[follow_ghost_num]);
    } else {
        sfspeedx=fabs(fspeedx);
        sfspeedy=fabs(fspeedy);
    }

    static float divx2=8.0;
    static float divy2=8.0;
//    divx2-=fabs(verschilx2)*0.0001; divx2+=0.01;
//    if (divx2>8.0) divx2=8.0; if (divx2<0.1) divx2=0.1;
//    divy2-=fabs(verschily2)*0.0001; divy2+=0.01;
//    if (divy2>8.0) divy2=8.0; if (divy2<0.1) divy2=0.1;
/*
    static int c=0;
    c++;
    if (c>20) {
        printf("verschilx2=%f verschily2=%f verschilx=%5d verschily=%5d divx2=%f divy2=%f\n",
               verschilx2,verschily2,jo_verschilx,jo_verschily,divx2,divy2);
        c=0;
    }
*/
    float numx=0.0;
    if (fps_float>65.0)
        numx+=(1.0)*fspeed_adjust*60.0/fps_float;
//        numx+=(1.0+(pen*4.0))*fspeed_adjust*60.0/fps_float;
    else
        numx+=(1.0)*fspeed_adjust;
//        numx+=(1.0+(pen*4.0))*fspeed_adjust;
    if (soft_jump==0 && (sfspeedx+sfspeedy)<40.0) numx*=(1.0+(2.0-plot_all)*fabs(verschilx2)/5000.0);
    int slowx=0;
    if (follow_ghost==0) numx=numx*(1.0+sfspeedx/divx2);
    if (numx<0.0) slowx=1;
    while (numx>=0.0) {
        if (numx>=0.0)  {
            followx[follow_countx]=x;
            follow_countx=(follow_countx+1)%array_len;
        }
        numx--;
    }
    float numy=0.0;
    if (fps_float>65.0)
//        numy+=(1.0+(pen*4.0))*fspeed_adjust*60.0/fps_float;
        numy+=(1.0)*fspeed_adjust*60.0/fps_float;
    else
        numy+=(1.0)*fspeed_adjust;
//        numy+=(1.0+(pen*4.0))*fspeed_adjust;
    if (soft_jump==0 && (sfspeedx+sfspeedy)<40.0) numy*=(1.0+(2.0-plot_all)*fabs(verschily2)/5000.0);
    int slowy=0;
    if (follow_ghost==0) numy=numy*(1.0+sfspeedy/divy2);
    if (numy<0) slowy=1;
    while (numy>=0.0) {
        if (numy>=0.0)  {
            followy[follow_county]=y;
            follow_county=(follow_county+1)%array_len;
        }
        numy--;
    }

    follow_ghost_num_old=follow_ghost_num;

    if (soft_jump==1)
    {
        for (follow_countx=0; follow_countx<array_len; follow_countx++)
        {
            followx[follow_countx]=x;
            followy[follow_countx]=y;
        }
        xdiff2=smooth_x;
        ydiff2=smooth_y;
        soft_jump=0;
    }
//    if (pacman_move==1) {
//        long_jump=1;
//    }

    if (long_jump==1 || first_follow==1 || forced_jump==1)
    {
//        printf("longjump\n");
        for (follow_countx=0; follow_countx<array_len; follow_countx++)
        {
            followx[follow_countx]=x;
            followy[follow_countx]=y;
        }
        follow_countx=0;
        follow_county=0;
        long_jump=0;
        first_follow=0;
        forced_jump=0;
        if (follow_ghost==1) last=1;
        xdiff2=x;
        ydiff2=y;
        slow_xdiff2=x;
        slow_ydiff2=y;
    }

    if ((pen==1 || autodraw==1) || forced_speed==1)
    {
        for (int i=0; i<-autodraw*2+(4-lookahead*3)+forced_speed*50; i++)
        {
            followx[follow_countx]=x;
            followy[follow_county]=y;
            follow_countx=(follow_countx+1)%array_len;
            follow_county=(follow_county+1)%array_len;
        }
    }
    static double px_sub;
    static double py_sub;
    static double px_sub_old;
    static double py_sub_old;

    double totx=0.0,toty=0.0;
    double divx=0.0;
    double divy=0.0;

/*
    double filter_count=0;
    int swappit=1;
    int swap_count=array_len/2;
    for (int i=follow_countx; i<follow_countx+array_len; i++)
    {
        totx=totx+(double)followx[i%array_len]*filter_count;
        divx=divx+filter_count;
        filter_count=filter_count+0.1*(float)swappit;
        swap_count--;
        if (swap_count==0) swappit=-1;
    }

    swappit=1;
    swap_count=array_len/2;
    filter_count=0;
    for (int i=follow_county; i<follow_county+array_len; i++)
    {
        toty=toty+(double)followy[i%array_len]*filter_count;
        divy=divy+filter_count;
        filter_count=filter_count+0.1*(float)swappit;;
        swap_count--;
        if (swap_count==0) swappit=-1;
    }
*/
    for (int i=follow_countx; i<follow_countx+array_len; i++)
    {
        totx=totx+(double)followx[i%array_len];
        divx++;
    }
    for (int i=follow_county; i<follow_county+array_len; i++)
    {
        toty=toty+(double)followy[i%array_len];
        divy++;
    }

    px_sub=fmod((double)(totx/divx),(double)maxpixelsx);
    py_sub=fmod((double)(toty/divy),(double)maxpixelsy);

/*
    for (int i=0; i<array_len; i++)
    {
        totx=totx+(double)followx[i];
        toty=toty+(double)followy[i];
    }


    px_sub=fmod((double)(totx/array_len),(double)maxpixelsx);
    py_sub=fmod((double)(toty/array_len),(double)maxpixelsy);
*/
    x=(int)(px_sub);
    y=(int)(py_sub);

    avg_speedx=(px_sub - px_sub_old);
    avg_speedy=(py_sub - py_sub_old);

    px_sub_old=px_sub;
    py_sub_old=py_sub;

    smooth_x=px_sub;
    smooth_y=py_sub;

//    if (avg_speedx<0.0) smooth_x--;
//    if (avg_speedy<0.0) smooth_y--;


    x=(x+maxpixelsx)%maxpixelsx;
    y=(y+maxpixelsy)%maxpixelsy;

    picturex=x/1920;
    posx=x-1920*(picturex);
    picturey=y/1080;
    posy=y-1080*(picturey);
    posx=-posx;
    posy=-posy;

/*
    if ( do_reset || (follow_ghost_num_old!=follow_ghost_num && follow_ghost==1) && !(long_jump==1 || first_follow==1 || forced_jump==1)) {
        for (follow_countx=0; follow_countx<array_len; follow_countx++)
        {
            followx[follow_countx]=x;
            followy[follow_countx]=y;
        }
    }
*/

    if (posx<=-1920 || posy<=-1080 || posx>0 || posy>0) {
        sprintf(writer,"BEFORE: ghostx=%d ghosty=%d follow_ghost_pos before: posx=%d, posy=%d, picturex=%d, picturey=%d follow_ghost=%d",x,y,posx,posy,picturex,picturey,follow_ghost);
        savedata(writer,0);
        while (posx<=-1920) posx=posx+1920;
        while (posy<=-1080) posy=posy+1080;
        while (posx>0)      posx=posx-1920;
        while (posy>0)      posy=posy-1080;
    }

    fposx=posx;
    fposy=posy;

    if (posx<=-1920 || posy<=-1080 || posx>0 || posy>0)
    {
        sprintf(writer,"AFTER: ghostx=%d ghosty=%d follow_ghost_pos before: posx=%d, posy=%d, picturex=%d, picturey=%d follow_ghost=%d",x,y,posx,posy,picturex,picturey,follow_ghost);
        savedata(writer,0);
    }


    new_picturex=picturex;
    new_picturey=picturey;
    new_posx=posx;
    new_posy=posy;
    new_fposx=fposx;
    new_fposy=fposy;

    if (follow_ghost==1) {
        verschilx=(-pos_ghostx[follow_ghost_num]-(render_picturex*1920-render_posx)+1920);
        verschily=(-pos_ghosty[follow_ghost_num]-(render_picturey*1080-render_posy)+1080);
    } else {
        verschilx=(smooth_x-(render_picturex*1920-render_posx));
        verschily=(smooth_y-(render_picturey*1080-render_posy));
    }
    verschilx2=(smooth_x-((double)old_picturex*1920.0-old_fposx));
    verschily2=(smooth_y-((double)old_picturey*1080.0-old_fposy));

    if (verschilx<-maxpixelsx/2) { verschilx=verschilx+maxpixelsx; } else if (verschilx>maxpixelsx/2) { verschilx=verschilx-maxpixelsx; }
    if (verschily<-maxpixelsy/2) { verschily=verschily+maxpixelsy; } else if (verschily>maxpixelsy/2) { verschily=verschily-maxpixelsy; }
    if (verschilx2<-maxpixelsx/2) { verschilx2=verschilx2+maxpixelsx; } else if (verschilx2>maxpixelsx/2) { verschilx2=verschilx2-maxpixelsx; }
    if (verschily2<-maxpixelsy/2) { verschily2=verschily2+maxpixelsy; } else if (verschily2>maxpixelsy/2) { verschily2=verschily2-maxpixelsy; }
    distance2x_old=distance2x; distance2y_old=distance2y;
    distance2=sqrt(verschilx*verschilx+verschily*verschily);
    distance2x=verschilx;
    distance2y=verschily;

    if (last==1)
    {
        last=0;
        xdiff2=x;
        ydiff2=y;
    }

    if (follow_ghost==0)
    {
        picturex=old_picturex;
        picturey=old_picturey;
        posx=old_posx;
        posy=old_posy;
        fposx=old_fposx;
        fposy=old_fposy;

        mem_picturex=old_picturex;
        mem_picturey=old_picturey;
        mem_posx=old_posx;
        mem_posy=old_posy;
        mem_fposx=old_fposx;
        mem_fposy=old_fposy;

        new_verschilx=(picturex*1920-posx)-(new_picturex*1920-new_posx);
        new_verschily=(picturey*1080-posy)-(new_picturey*1080-new_posy);

        if (new_verschilx<-maxpixelsx/2) { new_verschilx=new_verschilx+maxpixelsx; } else if (new_verschilx>maxpixelsx/2) { new_verschilx=new_verschilx-maxpixelsx; }
        if (new_verschily<-maxpixelsy/2) { new_verschily=new_verschily+maxpixelsy; } else if (new_verschily>maxpixelsy/2) { new_verschily=new_verschily-maxpixelsy; }

//        printf("new_verschilx=%d new_verschil_y=%d\n",new_verschilx,new_verschily);
        x=(picturex*1920-posx);
        y=(picturey*1080-posy);

        x_old=(x+maxpixelsx)%maxpixelsx;
        y_old=(y+maxpixelsy)%maxpixelsy;

        static float mfspeedx;
        static float mfspeedy;

        if (follow_ghost==1 || flippo==1) {
            mfspeedx=abs(fspeed_ghostx[follow_ghost_num])/(1.0+abs(new_verschilx*5.0));
            mfspeedy=abs(fspeed_ghosty[follow_ghost_num])/(1.0+abs(new_verschily*5.0));
        } else {
            mfspeedx=abs(fspeedx)/(1.0+abs(new_verschilx*5.0));
            mfspeedy=abs(fspeedy)/(1.0+abs(new_verschily*5.0));
        }

/*
        if (plot_all==0) {
            if (fps_float>65.0) {
                x=(x+(int)((new_verschilx/(1.0+mfspeedx/2.0))*(1920.0/1080.0)*1.2*(60.0/fps_float))+maxpixelsx)%maxpixelsx;
                y=(y+(int)((new_verschily/(1.0+mfspeedy/2.0))*1.2*(60.0/fps_float))+maxpixelsy)%maxpixelsy;
            } else {
                x=(x+(int)((new_verschilx/(1.0+mfspeedx/2.0))*(1920.0/1080.0)*1.2)+maxpixelsx)%maxpixelsx;
                y=(y+(int)((new_verschily/(1.0+mfspeedy/2.0))*1.2)+maxpixelsy)%maxpixelsy;
            }
        } else {
            if (fps_float>65.0) {
                x=(x+(int)((new_verschilx/(1.0+mfspeedx/2.0))*(1920.0/1080.0)*1.2*60.0/(sqrt(sprite_from_canvas.getScale().x/3.0+0.1)*3.0*fps_float))+maxpixelsx)%maxpixelsx;
                y=(y+(int)((new_verschily/(1.0+mfspeedy/2.0))*1.2*60.0/(sqrt(sprite_from_canvas.getScale().y/3.0+0.1)*3.0*fps_float))+maxpixelsy)%maxpixelsy;
            } else {
                x=(x+(int)((new_verschilx/(1.0+mfspeedx/2.0))*(1920.0/1080.0)*1.2/(sqrt(sprite_from_canvas.getScale().x/3.0+0.1)*3.0))+maxpixelsx)%maxpixelsx;
                y=(y+(int)((new_verschily/(1.0+mfspeedy/2.0))*1.2/(sqrt(sprite_from_canvas.getScale().y/3.0+0.1)*3.0))+maxpixelsy)%maxpixelsy;
            }
        }
*/
        int addx,addy;
/*
        if (pacman_move) {
            if (plot_all==0 && plot_cubes==0) {
                if (fps_float>65.0) {
                    addx=(int)((verschilx/(1.0))*(1920.0/1080.0)*1.2*(60.0/fps_float));
                    addy=(int)((verschily/(1.0))*1.2*(60.0/fps_float));
                } else {
                    addx=(int)((verschilx/(1.0))*(1920.0/1080.0)*1.2);
                    addy=(int)((verschily/(1.0))*1.2);
                }
            } else {
                if (fps_float>65.0) {
                    addx=(int)((verschilx/(1.0))*(1920.0/1080.0)*1.2*60.0/(sqrt(sprite_from_canvas.getScale().x/3.0+0.1)*3.0*fps_float));
                    addy=(int)((verschily/(1.0))*1.2*60.0/(sqrt(sprite_from_canvas.getScale().y/3.0+0.1)*3.0*fps_float));
                } else {
                    addx=(int)((verschilx/(1.0))*(1920.0/1080.0)*1.2/(sqrt(sprite_from_canvas.getScale().x/3.0+0.1)*3.0));
                    addy=(int)((verschily/(1.0))*1.2/(sqrt(sprite_from_canvas.getScale().y/3.0+0.1)*3.0));
                }
            }
        } else {
*/
            if (plot_all==0 && plot_cubes==0) {
                if (fps_float>65.0) {
                    addx=(int)((new_verschilx/(1.0+mfspeedx/2.0))*(1920.0/1080.0)*1.2*(60.0/fps_float));
                    addy=(int)((new_verschily/(1.0+mfspeedy/2.0))*1.2*(60.0/fps_float));
                } else {
                    addx=(int)((new_verschilx/(1.0+mfspeedx/2.0))*(1920.0/1080.0)*1.2);
                    addy=(int)((new_verschily/(1.0+mfspeedy/2.0))*1.2);
                }
            } else {
                if (fps_float>65.0) {
                    addx=(int)((new_verschilx/(1.0+mfspeedx/2.0))*(1920.0/1080.0)*1.2*60.0/(sqrt(sprite_from_canvas.getScale().x/3.0+0.1)*3.0*fps_float));
                    addy=(int)((new_verschily/(1.0+mfspeedy/2.0))*1.2*60.0/(sqrt(sprite_from_canvas.getScale().y/3.0+0.1)*3.0*fps_float));
                } else {
                    addx=(int)((new_verschilx/(1.0+mfspeedx/2.0))*(1920.0/1080.0)*1.2/(sqrt(sprite_from_canvas.getScale().x/3.0+0.1)*3.0));
                    addy=(int)((new_verschily/(1.0+mfspeedy/2.0))*1.2/(sqrt(sprite_from_canvas.getScale().y/3.0+0.1)*3.0));
                }
            }
//        }
//        if (fspeedx*addx>0) addx=0;
//        if (fspeedy*addy>0) addy=0;
        addx=addx/(1.0+sfspeedx/25.0);
        addy=addy/(1.0+sfspeedy/25.0);
        x=(x+addx+maxpixelsx)%maxpixelsx;
        y=(y+addy+maxpixelsy)%maxpixelsy;

        if ((xdiff2-(double)x)<-(double)maxpixelsx/2) { xdiff2=xdiff2+(double)maxpixelsx; } else if ((xdiff2-(double)x)>(double)maxpixelsx/2) { xdiff2=xdiff2-(double)maxpixelsx; }
        if ((ydiff2-(double)y)<-(double)maxpixelsy/2) { ydiff2=ydiff2+(double)maxpixelsy; } else if ((ydiff2-(double)y)>(double)maxpixelsy/2) { ydiff2=ydiff2-(double)maxpixelsy; }

        double speed_adapt;
        if (pen==0) speed_adapt=75.0-sfspeedx/2.0;
        else speed_adapt=(40.0-(pen!=0)*lookahead*20.0);
        if (speed_adapt<1.0) speed_adapt=1.0;

        xdiff2=xdiff2+((double)x-xdiff2)/(speed_adapt);

        if (pen==0) speed_adapt=75.0-sfspeedy/2.0;
        else speed_adapt=(30.0-(pen!=0)*lookahead*15.0);
        if (speed_adapt<1.0) speed_adapt=1.0;

        ydiff2=ydiff2+((double)y-ydiff2)/(speed_adapt);

        smooth_x=xdiff2;
        smooth_y=ydiff2;

        x=(int)xdiff2;
        y=(int)ydiff2;

        x=(x+maxpixelsx)%maxpixelsx;
        y=(y+maxpixelsy)%maxpixelsy;

        new_verschilx=-x_old+x;
        new_verschily=-y_old+y;

        if (new_verschilx<-maxpixelsx/2) { new_verschilx=new_verschilx+maxpixelsx; } else if (new_verschilx>maxpixelsx/2) { new_verschilx=new_verschilx-maxpixelsx; }
        if (new_verschily<-maxpixelsy/2) { new_verschily=new_verschily+maxpixelsy; } else if (new_verschily>maxpixelsy/2) { new_verschily=new_verschily-maxpixelsy; }

        render_picturex=x/1920; render_posx=x-1920*(render_picturex); render_posx=-render_posx;
        render_picturey=y/1080; render_posy=y-1080*(render_picturey); render_posy=-render_posy;

        new_verschilx2=-(render_picturex*1920-render_posx)+x_old-new_verschilx;
        new_verschily2=-(render_picturey*1080-render_posy)+y_old-new_verschily;

        if (new_verschilx2<-maxpixelsx/2) { new_verschilx2=new_verschilx2+maxpixelsx; } else if (new_verschilx2>maxpixelsx/2) { new_verschilx2=new_verschilx2-maxpixelsx; }
        if (new_verschily2<-maxpixelsy/2) { new_verschily2=new_verschily2+maxpixelsy; } else if (new_verschily2>maxpixelsy/2) { new_verschily2=new_verschily2-maxpixelsy; }
    }
    else
    {
        render_picturex=x/1920;
        render_posx=x-1920*(render_picturex);
        render_picturey=y/1080;
        render_posy=y-1080*(render_picturey);
        render_posx=-render_posx;
        render_posy=-render_posy;

        new_verschilx=0;
        new_verschily=0;
        new_verschilx2=0;
        new_verschily2=0;
    }

    if (pacman_move==1) {
        render_picturex=old_render_picturex;
        render_picturey=old_render_picturey;
        render_posx=old_render_posx;
        render_posy=old_render_posy;
        smooth_x=old_smoothx;
        smooth_y=old_smoothy;
        new_verschilx=-((picturex*1920-posx)-(render_picturex*1920-render_posx));
        new_verschily=-((picturey*1080-posy)-(render_picturey*1080-render_posy));
        while (new_verschilx<-maxpixelsx/2) { new_verschilx=new_verschilx+maxpixelsx; }
        while (new_verschilx>maxpixelsx/2) { new_verschilx=new_verschilx-maxpixelsx; }
        while (new_verschily<-maxpixelsy/2) { new_verschily=new_verschily+maxpixelsy; }
        while (new_verschily>maxpixelsy/2) { new_verschily=new_verschily-maxpixelsy; }
        new_verschilx2=-new_verschilx*2;
        new_verschily2=-new_verschily*2;
        while (new_verschilx2<-maxpixelsx/2) { new_verschilx2=new_verschilx2+maxpixelsx; }
        while (new_verschilx2>maxpixelsx/2) { new_verschilx2=new_verschilx2-maxpixelsx; }
        while (new_verschily2<-maxpixelsy/2) { new_verschily2=new_verschily2+maxpixelsy; }
        while (new_verschily2>maxpixelsy/2) { new_verschily2=new_verschily2-maxpixelsy; }
//        xdiff2=(old_picturex*1920-old_posx)-1920;
//        ydiff2=(old_picturey*1080-old_posy)-1080;
//        xdiff2=rx;
//        ydiff2=ry;
//        if ((xdiff2)<-(double)maxpixelsx/2) { xdiff2=xdiff2+(double)maxpixelsx; } else if ((xdiff2)>(double)maxpixelsx/2) { xdiff2=xdiff2-(double)maxpixelsx; }
//        if ((ydiff2)<-(double)maxpixelsy/2) { ydiff2=ydiff2+(double)maxpixelsy; } else if ((ydiff2)>(double)maxpixelsy/2) { ydiff2=ydiff2-(double)maxpixelsy; }
//        xdiff2=smooth_x;
//        ydiff2=smooth_y;
//        xdiff2=-(old_picturex*1920-old_posx);
//        ydiff2=-(old_picturey*1080-old_posy);
    } else if (pacman_move==2) {
//        ydiff2=smooth_y;
//        xdiff2=0;
        render_picturex=old_render_picturex;
        render_posx=old_render_posx;
        smooth_x=old_smoothx;
//        ydiff2=y_old;
        new_verschilx=-((picturex*1920-posx)-(render_picturex*1920-render_posx));
        while (new_verschilx<-maxpixelsx/2) { new_verschilx=new_verschilx+maxpixelsx; }
        while (new_verschilx>maxpixelsx/2) { new_verschilx=new_verschilx-maxpixelsx; }
        new_verschilx2=-new_verschilx*2;
        while (new_verschilx2<-maxpixelsx/2) { new_verschilx2=new_verschilx2+maxpixelsx; }
        while (new_verschilx2>maxpixelsx/2) { new_verschilx2=new_verschilx2-maxpixelsx; }
//        xdiff2=(picturex*1920-posx)-1920;
//        xdiff2=(old_picturex*1920-old_posx);
//        if ((xdiff2)<-(double)maxpixelsx/2) { xdiff2=xdiff2+(double)maxpixelsx; } else if ((xdiff2)>(double)maxpixelsx/2) { xdiff2=xdiff2-(double)maxpixelsx; }
//        xdiff2=smooth_x;
//        xdiff2=-(old_picturex*1920-old_posx);
    } else if (pacman_move==3) {
//        ydiff2=0;
//        xdiff2=smooth_x;
//        xdiff2=(x_old+xdiff2*5.0)/6.0;
//        xdiff2=x_old;
//        if (xdiff2<-maxpixelsx/2) { xdiff2=xdiff2+maxpixelsx; } else if (xdiff2>maxpixelsx/2) { xdiff2=xdiff2-maxpixelsx; }
//        if (ydiff2<-maxpixelsy/2) { ydiff2=ydiff2+maxpixelsy; } else if (ydiff2>maxpixelsy/2) { ydiff2=ydiff2-maxpixelsy; }
//        ydiff2=y_old;

        render_picturey=old_render_picturey;
        render_posy=old_render_posy;
        smooth_y=old_smoothy;
        new_verschily=-((picturey*1080-posy)-(render_picturey*1080-render_posy));
        while (new_verschily<-maxpixelsy/2) { new_verschily=new_verschily+maxpixelsy; }
        while (new_verschily>maxpixelsy/2) { new_verschily=new_verschily-maxpixelsy; }
        new_verschily2=-new_verschily*2;
        while (new_verschily2<-maxpixelsy/2) { new_verschily2=new_verschily2+maxpixelsy; }
        while (new_verschily2>maxpixelsy/2) { new_verschily2=new_verschily2-maxpixelsy; }
//        ydiff2=(picturey*1080-posy)-1080;
//        ydiff2=(old_picturey*1920-old_posy);
//        if ((ydiff2)<-(double)maxpixelsy/2) { ydiff2=ydiff2+(double)maxpixelsy; } else if ((ydiff2)>(double)maxpixelsy/2) { ydiff2=ydiff2-(double)maxpixelsy; }
//        ydiff2=smooth_y;
//        ydiff2=-(old_picturey*1080-old_posy);

    }

    if (move_config) {
        switch(move_config) {
            case 1:
                xdiff2=x_old;
                ydiff2=y_old;
                break;
            case 2:
                xdiff2=x_old;
                break;
            case 3:
                ydiff2=y_old;
                break;
            default:
                break;
        }
    }
    if (DONTREADBITMAPS==0)
        ReadBitmaps2();
    if (DONTREADBITMAPS==0)
        ReadBitmaps4();
/*
    if (follow_ghost || flippo) {
        mem_posx=remem_posx;
        mem_posy=remem_posy;
        mem_fposx=remem_fposx;
        mem_fposy=remem_fposy;
        mem_picturex=remem_picturex;
        mem_picturey=remem_picturey;
    }
*/
}



void get_position1()
{
    int x=position1x;
    int y=position1y;

//    forced_jump=1;
    follow_ghost_pos();
    picturex=x/1920;
    posx=x-1920*picturex;

    picturey=y/1080;
    posy=y-1080*picturey;

    posx=-posx;
    posy=-posy;

    fposx=posx;
    fposy=posy;

    ReadBitmaps2();
//    follow_ghost_pos();

//    follow_ghost_pos();

    if (connected==1 || playerleft==0)
    {
        int mazemovex=(picturex*1920-posx-32)/64;
        int mazemovey=(picturey*1080-posy   )/72;
        mazemovex=(mazemovex-45+60*(totalpicturex))%(30*(totalpicturex));
        mazemovey=(mazemovey-23+30*(totalpicturey))%(15*(totalpicturey));
        sprintf(writer,"T=GOTO,X=%d,Y=%d,\0",mazemovex,mazemovey);
        SEND(writer);
    }
    speedy_new=0;
    speedx_new=0;
    fspeedy_new=0;
    fspeedx_new=0;
    speedy=0;
    speedx=0;
    fspeedy=0;
    fspeedx=0;
    maze_up_new=0;
    maze_down_new=0;
    maze_left_new=0;
    maze_right_new=0;
    maze_up=0;
    maze_down=0;
    maze_left=0;
    maze_right=0;
}

void get_position3()
{
    int x=position1x;
    int y=position1y;

//    forced_jump=1;
//    follow_ghost_pos();
    picturex=x/1920;
    posx=x-1920*picturex;

    picturey=y/1080;
    posy=y-1080*picturey;

    posx=-posx;
    posy=-posy;

    fposx=posx;
    fposy=posy;

    smooth_x=picturex*1920-posx;
    smooth_y=picturey*1080-posy;

    ReadBitmaps2();
//    follow_ghost_pos();

//    follow_ghost_pos();

    if (connected==1 || playerleft==0)
    {
        int mazemovex=(picturex*1920-posx-32)/64;
        int mazemovey=(picturey*1080-posy   )/72;
        mazemovex=(mazemovex-45+60*(totalpicturex))%(30*(totalpicturex));
        mazemovey=(mazemovey-23+30*(totalpicturey))%(15*(totalpicturey));
        sprintf(writer,"T=GOTO,X=%d,Y=%d,\0",mazemovex,mazemovey);
        SEND(writer);
    }
//    speedy_new=0;
//    speedx_new=0;
//    fspeedy_new=0;
//    fspeedx_new=0;
//    speedy=0;
//    speedx=0;
//    fspeedy=0;
//    fspeedx=0;
//    maze_up_new=0;
//    maze_down_new=0;
//    maze_left_new=0;
//    maze_right_new=0;
//    maze_up=0;
//    maze_down=0;
//    maze_left=0;
//    maze_right=0;
}

void get_position2()
{
    int x=position2x;
    int y=position2y;

//    forced_jump=1;
    follow_ghost_pos();

    picturex=x/1920;
    posx=x-1920*picturex;

    picturey=y/1080;
    posy=y-1080*picturey;

    posx=-posx;
    posy=-posy;

    fposx=posx;
    fposy=posy;

    ReadBitmaps2();

//    follow_ghost_pos();

    if (connected==1 || playerleft==0)
    {
        int mazemovex=(picturex*1920-posx-32)/64;
        int mazemovey=(picturey*1080-posy   )/72;
        mazemovex=(mazemovex-45+60*(totalpicturex))%(30*(totalpicturex));
        mazemovey=(mazemovey-23+30*(totalpicturey))%(15*(totalpicturey));
        sprintf(writer,"T=GOTO,X=%d,Y=%d,\0",mazemovex,mazemovey);
        SEND(writer);
    }
    speedy_new=0;
    speedx_new=0;
    fspeedy_new=0;
    fspeedx_new=0;
    speedy=0;
    speedx=0;
    fspeedy=0;
    fspeedx=0;
    maze_up_new=0;
    maze_down_new=0;
    maze_left_new=0;
    maze_right_new=0;
    maze_up=0;
    maze_down=0;
    maze_left=0;
    maze_right=0;
}

int map_mode=0;

void clear_map()
{
    int xx,yy;
    int x,y;
    if (map_mode==0) map_mode=1; else if (map_mode==1) map_mode=2; else map_mode=0;

    if (map_mode==1) {
        for (xx=0; xx<((maxpicturex+1)*30); xx++)
        {
            for (yy=0; yy<((maxpicturey+1)*15); yy++)
            {
                maze_plot[xx][yy]=0;
            }
        }
    } else if (map_mode==2) {
        for (xx=0; xx<((maxpicturex+1)*30); xx++)
        {
            for (yy=0; yy<((maxpicturey+1)*15); yy++)
            {
                maze_plot[xx][yy]=15;
            }
        }
    } else if (map_mode==0) {
        for (xx=0; xx<maze_plotsizex; xx++)
            for (yy=0; yy<maze_plotsizey; yy++)
                maze_plot[xx][yy]=0;
        for (xx=0; xx<maze_plotsizex; xx++)
        {
            for (yy=0; yy<maze_plotsizey; yy++)
            {
                int val;
                val=rand()%16;
                if (rand()%3==1) val=val&(rand()%16);
                if (rand()%5==1) val=val&(rand()%16);
                if (rand()%4==1) val=0;
                if (rand()%5==1) val=15;
                maze_plot[xx][yy]|=val;
                if ((val&1)==1) maze_plot[xx][(yy-1+maze_plotsizey)%maze_plotsizey]=maze_plot[xx][(yy-1+maze_plotsizey)%maze_plotsizey]|2;
                if ((val&2)==2) maze_plot[xx][(yy+1)%maze_plotsizey]=maze_plot[xx][(yy+1)%maze_plotsizey]|1;
                if ((val&4)==4) maze_plot[(xx-1+maze_plotsizex)%maze_plotsizex][yy]=maze_plot[(xx-1+maze_plotsizex)%maze_plotsizex][yy]|8;
                if ((val&8)==8) maze_plot[(xx+1)%maze_plotsizex][yy]=maze_plot[(xx+1)%maze_plotsizex][yy]|4;
                if (val==15 ) {
                    if (rand()%2==0) maze_plot[xx][yy]=maze_plot[xx][yy]|(32);
                    else if (rand()%2==0) maze_plot[xx][yy]=maze_plot[xx][yy]|(64);
                }
            }
        }
        for (xx=0; xx<maze_plotsizex; xx++)
        {
            for (yy=0; yy<maze_plotsizey; yy++)
            {
                char blokje=maze_plot[xx][yy]=maze_plot[xx][yy];
                if (blokje==1 || blokje==2 || blokje==4 || blokje==8) maze_plot[xx][yy]=blokje|16;
            }
        }
    }

    start_posx=(picturex*1920-posx);
    start_posy=(picturey*1080-posy);

    cleanupbitmaps_mazes();

    return;
}

void home_map()
{
    int x=start_posx;
    int y=start_posy;

    if (shift==1)
    {
        x=2912;
        y=1656;
        shift=0;
    }

    picturex=x/1920;
    posx=x-1920*picturex;

    picturey=y/1080;
    posy=y-1080*picturey;

    posx=-posx;
    posy=-posy;

    fposx=posx;
    fposy=posy;

    ReadBitmaps2();

    if (connected==1 || playerleft==0)
    {
        int mazemovex=(picturex*1920-posx-32)/64;
        int mazemovey=(picturey*1080-posy   )/72;
        mazemovex=(mazemovex-45+60*(totalpicturex))%(30*(totalpicturex));
        mazemovey=(mazemovey-23+30*(totalpicturey))%(15*(totalpicturey));
        sprintf(writer,"T=GOTO,X=%d,Y=%d,\0",mazemovex,mazemovey);
        SEND(writer);
    }
    if (drawmazes==1)
    {
        speedy_new=0;
        speedx_new=0;
        fspeedy_new=0;
        fspeedx_new=0;
        speedy=0;
        speedx=0;
        fspeedy=0;
        fspeedx=0;
        maze_up_new=0;
        maze_down_new=0;
        maze_left_new=0;
        maze_right_new=0;
        maze_up=0;
        maze_down=0;
        maze_left=0;
        maze_right=0;
    }
//	forced_jump=1;
}
extern int mul;

void loadlevel()
{
    FILE* file = fopen ("level.txt", "r");
    int i = 0;
    if (file!=NULL)
    {
        fscanf (file, "%d", &i);
        fclose (file);
        level=i;
    }
    return;
}

void loadmul()
{
    FILE* file = fopen ("map.txt", "r");
    int i = 0;
    if (file!=NULL)
    {
        fscanf (file, "%d", &i);
        fclose (file);
        mul=i;
    }
    return;
}

void savelevel()
{
    FILE* file = fopen ("level.txt", "w");
    int i = 0;
    char score[20];

    if (file!=NULL)
    {
        sprintf(score,"%d",level);
        fprintf (file, "%s\n",score);
        fclose (file);
    }
    if (shade_map>=1) {
        file = fopen ("map.txt", "w");
        if (file!=NULL)
        {
            sprintf(score,"%d",mul);
            fprintf (file, "%s\n",score);
            fclose (file);
        }
    }
    return;
}

int wantedx;
int wantedy;
extern int count_errors;

void putinmazeSFML_all() {
//    printf("Inside putinmazeSFML_all()\n");
    once=0;
    int bitmapcount=0;
    int x,y;
    char naam[200];
    int view=0;
    do_all=1;
    strcpy(text_line2,"");
    strcpy(text_line3,"");
    strcpy(text_line4,"");

//    if (formula==2)
//        for (x=0; x<MAXINMEM+12; x++)
//        {
//            texturemaxinmem[x].setRepeated(FALSE);
//            texturemaxinmem[x].setSmooth(FALSE);    // for aa_main. (antialiasing shader 2.frag) (OR DO MANUAL (ALT-S))
//        }

    wantedx=picturex*1920-posx;
    wantedy=picturey*1080-posy;
    map_end_x=0;
    ret=0;
    int mem_posx=posx;
    int mem_posy=posy;
    float mem_fposx=fposx;
    float mem_fposy=fposy;
    int mem_picturex=picturex;
    int mem_picturey=picturey;
    int first=1;
//    launch_background_blitter();
    go_pos=1;
    for (x=0; x<BITMAPSX && ret==0; x++) {
        for (y=0; y<BITMAPSY && ret==0; y++) {
            map_end_x=0;
            map_end_y=0;
            ret=0;
            if (MAZEOFF==1) {
                sprintf(naam,"%s/%dx%d/%03d/picture.%06d.%06d.png",LEVELDIR,BITMAPSX,BITMAPSY,level,y,x);
                if (file_exists(naam)) {
                    if (files[x][y]==0) totalfiles++;
                    files[x][y]=1;
                }
                else {
                    if (files[x][y]==1) totalfiles--;
                    files[x][y]=0;
                }
                error_flag=0;
            }
            if (first==1) {
//                render_mutex.lock();
//                DONTREADBITMAPS=1;
                forced_jump=1;
//                long_jump=1;
                first=0;
//                follow_ghost_pos();
//                DONTREADBITMAPS=0;
//                render_mutex.unlock();
            }
//            blitter2();
//            if (F2==1) {
//                draw2((char*)"GENERATING BACKGROUND",780,0,sf::Color(rand()%256,rand()%256,rand()%256,255),sf::Color::White);
//            }
//            SFMLView1.display();
            count_errors=0;
            if (shade_map>=1 && files[x][y]==1) {
                if (sync==1 && view==0) {
                    sprintf(error_msg,"BITMAP EXISTS, SKIPPING X=%d,Y=%d  ");
                    error_flag=1;
                    SFMLView1.setVerticalSyncEnabled(false);
                    view=1;
                }
//                printf("bitmap exists: %d,%d\n",x,y);
                kiki();
                if (ESCAPE==1) {
                    ESCAPE=0;
                    goexit=0;
                    y=BITMAPSY;
                    x=BITMAPSX;
                }
                continue;
            } else {
                kiki();
                kiki();
                kiki();
                if ( view==1 && sync==1) {
                    strcpy(error_msg2,"TIP: SETTING SYNC OFF (F3) SPEED THINGS UP.");
                    error_flag2=1;
                    SFMLView1.setVerticalSyncEnabled(true);
                    view=0;
                }
//                printf("bitmap don't exists: %d,%d  running putinmazeSFML()\n",x,y);
//                printf("Calling putinmazeSFML()\n");
//                picturex=x;
//                posx=0;
//                picturey=y;
//                posy=0;
//                fposx=posx;
//                fposy=posy;
//                long_jump=1;
                bitmapcount++;
                putinmazeSFML(x,y);
                SFMLView1.setActive(true);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                SFMLView1.setActive(false);
                if (!used[x][y]==0) {
                    spritemaxinmempoint[used2[x][y]]->setTexture(texturemaxinmempoint[used2[x][y]]->getTexture(),true);
                    spritemaxinmempoint[used2[x][y]]->setPosition(0,0);
                    spritemaxinmempoint[used2[x][y]]->setTextureRect({0,0,1920,1080});
                    SFMLView1.draw(*spritemaxinmempoint[used2[x][y]]);
                } else {
                    draw2((char*)"COPIED FROM/TO:",0,32,sf::Color(255,0,0,255),sf::Color::White);
                    sprintf(naam,"%s/map.z%d/pictures/y%d/picture.%06d.%06d.png",LEVELDIR,get_map_zoom,offset_picture_y+y,offset_picture_y+y,offset_picture_x+x);
                    draw2((char*)naam,0,64,sf::Color(255,0,0,255),sf::Color::White);
                    sprintf(naam,"%s/%dx%d/%03d/picture.%06d.%06d.png",LEVELDIR,BITMAPSX,BITMAPSY,level,y,x);
                    draw2((char*)naam,0,96,sf::Color(255,0,0,255),sf::Color::White);
                }
//                SFMLView1.clear(background_color[drawmazes]);
                if (F2==1) {
                    draw2((char*)"GENERATING BACKGROUND",780,0,sf::Color(rand()%256,rand()%256,rand()%256,255),sf::Color::White);
                }
//                SFMLView1.setActive(true);
                SFMLView1.display();
//                SFMLView1.setActive(false);
            }

            if (ESCAPE==1) {
                ESCAPE=0;
                goexit=0;
                y=BITMAPSY;
                x=BITMAPSX;
            }
            if ((shade_map>=1 && formula==1)) {
                if (count_errors>=40) {
                    x=rand()%BITMAPSX;
                    y=rand()%BITMAPSY;
                }
                if (ret==1 && y!=0) ret=0;
                if (map_end_y==1) {
                    y=BITMAPSY;
//                    printf("map_end_y==1\n");
                }
                if (map_end_x==1 || (kill1==1 && kill2==1 && kill3==1)) {
//                    printf("map_end_x==1\n");
                    y=BITMAPSY;
                    x=BITMAPSX;
//                    printf("End of map reached or threads killed.\n");
                }
            }

            if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
            else
            {
                HANDLEEVENTS();
            }

            if (totalused>MAXINMEM)
            {
                int oldx=picturex;
                int oldy=picturey;
                picturex=x;picturey=y;
                go_save_some_bitmaps();
                if (totalused>MAXINMEM+2)
                {
                    go_save_some_bitmaps();
                    if (totalused>MAXINMEM+4)
                    {
                        go_save_some_bitmaps();
                    }
                }
                picturex=oldx;picturey=oldy;
            }
        }
    }
//    go_blit=0;
//    long_jump=1;
    go_pos=0;
    posx=mem_posx;
    posy=mem_posy;
    fposx=mem_fposx;
    fposy=mem_fposy;
    picturex=mem_picturex;
    picturey=mem_picturey;
    forced_jump=1;

    if (formula==2) {
        char new_picturedir[200];
        char new_leveldir[200];
        strcpy(new_picturedir,PICTUREDIR);
        strcpy(new_leveldir,LEVELDIR);
        while (replace_str(new_picturedir,"/","\\\\"));
        while (replace_str(new_leveldir,"/","\\\\"));

//        sprintf(naam,"move pictures\\picture*.* levels\\%dx%d\\%03d\\",BITMAPSX,BITMAPSY,level);
        sprintf(naam,"move %s\\picture*.* %s\\%dx%d\\%03d\\",new_picturedir,new_leveldir,BITMAPSX,BITMAPSY,level);
        system(naam);
        CLEANBITMAPS();
        int x,y;
        for (x=0; x<totalpicturex; x++)
        {
            for (y=0; y<totalpicturey; y++)
            {
                 if (files[x][y]==0) {
                      files[x][y]=1;
                      totalfiles++;
                 }
            }
        }
        ReadBitmaps2();
        ReadBitmaps4();
    }
    if (sync==1) SFMLView1.setVerticalSyncEnabled(true);

extern sf::Mutex loader_mutex;
    loader_mutex.lock();
        kill1=0;kill2=0;kill3=0;
    loader_mutex.unlock();
    if (sync==1 && view==1) SFMLView1.setVerticalSyncEnabled(true);
    sprintf(error_msg,"BITMAPS PROCESSED: %d",bitmapcount);
    error_flag=1;
    do_all=0;
//    SAVEALLBITMAPS();
}


void putinmazeSFML_all_xtheny() {
    wierdo_requests.clear();
    wierdo_requests_ready.clear();
    wierdo_filenames.clear();
//    printf("Inside putinmazeSFML_all()\n");
    once=0;
    int bitmapcount=0;
    int x,y;
    char naam[200];
    int view=0;
    do_all=1;
    strcpy(text_line2,"");
    strcpy(text_line3,"");
    strcpy(text_line4,"");

//    if (formula==2)
//        for (x=0; x<MAXINMEM+12; x++)
//        {
//            texturemaxinmem[x].setRepeated(FALSE);
//            texturemaxinmem[x].setSmooth(FALSE);    // for aa_main. (antialiasing shader 2.frag) (OR DO MANUAL (ALT-S))
//        }

    wantedx=picturex*1920-posx;
    wantedy=picturey*1080-posy;
    map_end_x=0;
    ret=0;
    int mem_posx=posx;
    int mem_posy=posy;
    float mem_fposx=fposx;
    float mem_fposy=fposy;
    int mem_picturex=picturex;
    int mem_picturey=picturey;
    int first=1;
//    launch_background_blitter();
    go_pos=1;
    for (y=0; y<BITMAPSY && ret==0; y++) {
        for (x=0; x<BITMAPSX && ret==0; x++) {
            monitor_off=1;
            map_end_x=0;
            map_end_y=0;
            ret=0;
            if (MAZEOFF==1) {
                sprintf(naam,"%s/%dx%d/%03d/picture.%06d.%06d.png",LEVELDIR,BITMAPSX,BITMAPSY,level,y,x);
                if (file_exists(naam)) {
                    if (files[x][y]==0) totalfiles++;
                    files[x][y]=1;
                }
                else {
                    if (files[x][y]==1) totalfiles--;
                    files[x][y]=0;
                }
                error_flag=0;
            }
            if (first==1) {
//                render_mutex.lock();
//                DONTREADBITMAPS=1;
                forced_jump=1;
//                long_jump=1;
                first=0;
//                follow_ghost_pos();
//                DONTREADBITMAPS=0;
//                render_mutex.unlock();
            }
//            blitter2();
//            if (F2==1) {
//                draw2((char*)"GENERATING BACKGROUND",780,0,sf::Color(rand()%256,rand()%256,rand()%256,255),sf::Color::White);
//            }
//            SFMLView1.display();
            if (shade_map>=1 && files[x][y]==1) {
                if (sync==1 && view==0) {
                    sprintf(error_msg,"BITMAP EXISTS, SKIPPING X=%d,Y=%d  ",x,y);
                    error_flag=1;
                    SFMLView1.setVerticalSyncEnabled(false);
                    view=1;
                }
//                printf("bitmap exists: %d,%d\n",x,y);
extern void kiki();
                kiki();
                if (ESCAPE==1) {
                    ESCAPE=0;
                    goexit=0;
                    y=BITMAPSY;
                    x=BITMAPSX;
                }
                continue;
            } else {
                kiki();
                kiki();
                kiki();
                kiki();
                kiki();
                if ( view==1 && sync==1) {
                    strcpy(error_msg2,"TIP: SETTING SYNC OFF (F3) SPEED THINGS UP.");
                    error_flag2=1;
                    SFMLView1.setVerticalSyncEnabled(true);
                    view=0;
                }
//                printf("bitmap don't exists: %d,%d  running putinmazeSFML()\n",x,y);
//                printf("Calling putinmazeSFML()\n");
//                picturex=x;
//                posx=0;
//                picturey=y;
//                posy=0;
//                fposx=posx;
//                fposy=posy;
//                long_jump=1;
                bitmapcount++;
                if (formula==1 && files[x][y]==1) {
//                    printf("BITMAP EXISTS, SKIPPING X=%d,Y=%d  \r",x,y);
                } else {
//                    printf("\n");
                    if (used[x][y]==1) {
                        spritemaxinmempoint[used2[x][y]]->setTexture(texturemaxinmempoint[used2[x][y]]->getTexture(),false);
                        spritemaxinmempoint[used2[x][y]]->setPosition(0,0);
                        spritemaxinmempoint[used2[x][y]]->setTextureRect({0,0,1920,1080});
                    }
                    printf("Calling putinmazeSFML(%d,%d)\n",x,y);
                    putinmazeSFML(x,y);
                    if (used[x][y]==1) {
                        spritemaxinmempoint[used2[x][y]]->setTexture(texturemaxinmempoint[used2[x][y]]->getTexture(),false);
                        spritemaxinmempoint[used2[x][y]]->setPosition(0,0);
                        spritemaxinmempoint[used2[x][y]]->setTextureRect({0,0,1920,1080});
                    }
                }
//                SFMLView1.clear(background_color[drawmazes]);
/*
                if (formula!=2) {
                    SFMLView1.setActive(true);
                    glClearDepth(1.0f);
                    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                    SFMLView1.setActive(false);
                    SFMLView1.draw(*spritemaxinmempoint[used2[x][y]]);
                    if (F2==1) {
                        draw2((char*)"GENERATING BACKGROUND",780,0,sf::Color(rand()%256,rand()%256,rand()%256,255),sf::Color::White);
                    }
                    SFMLView1.display();
                }
*/
            }

            if (ESCAPE==1) {
                ESCAPE=0;
                goexit=0;
                y=BITMAPSY;
                x=BITMAPSX;
            }
            if ((shade_map>=1 && formula==1) || (shade_map==0 && formula==1)) {
                if (ret==1 && y!=0) ret=0;
                if (map_end_x==1) {
                    x=BITMAPSX;
//                    y=BITMAPSY;
//                    printf("map_end_y==1\n");
                }
                if (map_end_y==1 || (kill1==1 && kill2==1 && kill3==1)) {
//                if (map_end_x==1 || (kill1==1 && kill2==1 && kill3==1)) {
//                    printf("map_end_x==1\n");
                    y=BITMAPSY;
                    x=BITMAPSX;
                    printf("\nEnd.\n");
                }
            }

            if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
            else
            {
                HANDLEEVENTS();
            }

            if (totalused>MAXINMEM)
            {
                int oldx=picturex;
                int oldy=picturey;
                picturex=x;picturey=y;
                go_save_some_bitmaps();
                if (totalused>MAXINMEM+2)
                {
                    go_save_some_bitmaps();
                    if (totalused>MAXINMEM+4)
                    {
                        go_save_some_bitmaps();
                    }
                }
                picturex=oldx;picturey=oldy;
            }
        }
    }
//    go_blit=0;
//    long_jump=1;
    go_pos=0;
    posx=mem_posx;
    posy=mem_posy;
    fposx=mem_fposx;
    fposy=mem_fposy;
    picturex=mem_picturex;
    picturey=mem_picturey;
    forced_jump=1;

    if (formula==2) {
        char new_picturedir[200];
        char new_leveldir[200];
        strcpy(new_picturedir,PICTUREDIR);
        strcpy(new_leveldir,LEVELDIR);
        while (replace_str(new_picturedir,"/","\\\\"));
        while (replace_str(new_leveldir,"/","\\\\"));

//        sprintf(naam,"move pictures\\picture*.* levels\\%dx%d\\%03d\\",BITMAPSX,BITMAPSY,level);
        sprintf(naam,"move %s\\picture*.* %s\\%dx%d\\%03d\\",new_picturedir,new_leveldir,BITMAPSX,BITMAPSY,level);
        system(naam);
        CLEANBITMAPS();
        int x,y;
        for (x=0; x<totalpicturex; x++)
        {
            for (y=0; y<totalpicturey; y++)
            {
                 if (files[x][y]==0) {
                      files[x][y]=1;
                      totalfiles++;
                 }
            }
        }
        ReadBitmaps2();
        ReadBitmaps4();
    }
//    if (sync==1) SFMLView1.setVerticalSyncEnabled(true);

extern sf::Mutex loader_mutex;
    loader_mutex.lock();
        kill1=0;kill2=0;kill3=0;
    loader_mutex.unlock();
    if (sync==1 && view==1) SFMLView1.setVerticalSyncEnabled(true);
    sprintf(error_msg,"BITMAPS PROCESSED: %d",bitmapcount);
    error_flag=1;
    do_all=0;
//    SAVEALLBITMAPS();
}

sf::Thread background_loader_all(&LOAD_MAP_FOR_ALL_BITMAPS);

void START_LOADING_FOR_ALL_BITMAPS() {
    strcpy(error_msg,"STARTING BACKGROUND LOADER MAPS");
    error_flag=1;
    background_loader_all.launch();
}

void kill_background_loader() {
    background_loader_all.terminate();
}


void LOAD_MAP_FOR_ALL_BITMAPS() {
    ending1_x=-1;
    ending2_x=-1;
    ending3_x=-1;
    ending1_y=-1;
    ending2_y=-1;
    ending3_y=-1;
    dont_stop=1;
    if (blocked==1) {
        while (blocked==1) {
            static int timer=20;
            sf::sleep(sf::milliseconds(500));
            if (timer%5==0) printf("THREAD LOAD_MAP_FOR_ALL_BITMAPS() SPEAKING: LOADER THREADS BLOCKED, WAITING FEW SECONDS.\n");
            timer--;
            if (timer<=0) {
                printf("LOAD_MAP_FOR_ALL_BITMAPS() THREADS STILL BLOCKED, EXITING. DOEWIE!\n");
                return;
            }
        }
    }
    if (kill1==1) printf("THREAD 1 KILLED, UNKILLING.\n");
    if (kill2==1) printf("THREAD 2 KILLED, UNKILLING.\n");
    if (kill3==1) printf("THREAD 3 KILLED, UNKILLING.\n");
    if (loader1_active==1) printf("LOADER1 ACTIVE AND NOT BLOCKED?\n");
    if (loader2_active==1) printf("LOADER2 ACTIVE AND NOT BLOCKED?\n");
    if (loader3_active==1) printf("LOADER3 ACTIVE AND NOT BLOCKED?\n");

    loader_mutex.lock();
        kill1=0;kill2=0;kill3=0;
        blocked=1;
        background_loader=1;
    loader_mutex.unlock();


    int x=0,y=0;
    if (shade_map>=1) {
        while (dont_stop==1) {
            int end_x=99999999,end_y=99999999;
            if (end_x==99999999) {
                if (ending1_x>=0) end_x=ending1_x;
                else if (ending2_x>=0) end_x=ending2_x;
                else if (ending3_x>=0) end_x=ending3_x;
            }
            if (end_y==99999999) {
                if (ending1_y>=0) end_y=ending1_y;
                else if (ending2_y>=0) end_y=ending2_y;
                else if (ending3_y>=0) end_y=ending3_y;
            }
            if (loader1_active==0 && kill1==0) {
                mytotal1=sf::Vector2i(x,y);
                loader_mutex.lock();
                    launch_background_loader_one();
                loader_mutex.unlock();
//                x++; if (x==BITMAPSX || x>end_x) { x=0;y++;if (y==BITMAPSY || y>end_y) { blocked=0; dont_stop=0; return; } }
                y++; if (y==BITMAPSY || y>end_y) {
                    y=0;x++;
                    if (x==BITMAPSX || x>end_x) {
                        loader_mutex.lock();
                            blocked=0;
                            dont_stop=0;
                        loader_mutex.unlock();
                        return;
                    }
                }
                sf::sleep(sf::milliseconds(20));
            }
            sprintf(error_msg_s,"BACKGROUND MAP LOADER X=%d,Y=%d",x,y);
            error_flag_s=1;
            if (loader2_active==0 && kill2==0) {
                mytotal2=sf::Vector2i(x,y);
                loader_mutex.lock();
                    launch_background_loader_two();
                loader_mutex.unlock();

//                x++; if (x==BITMAPSX || x>end_x) { x=0;y++;if (y==BITMAPSY || y>end_y) { blocked=0; dont_stop=0; return; } }
                y++; if (y==BITMAPSY || y>end_y) {
                     y=0;x++;
                     if (x==BITMAPSX || x>end_x) {
                        loader_mutex.lock();
                            blocked=0;
                            dont_stop=0;
                        loader_mutex.unlock();
                        return;
                    }
                }
                sf::sleep(sf::milliseconds(20));
            }
            sprintf(error_msg_s,"BACKGROUND MAP LOADER X=%d,Y=%d",x,y);
            error_flag_s=1;
            if (loader3_active==0 && kill3==0) {
                mytotal3=sf::Vector2i(x,y);
                loader_mutex.lock();
                    launch_background_loader_three();
                loader_mutex.unlock();

//                x++; if (x==BITMAPSX || x>end_x) { x=0;y++;if (y==BITMAPSY || y>end_y) { blocked=0; dont_stop=0; return; } }
                y++; if (y==BITMAPSY || y>end_y) {
                    y=0;x++;
                    if (x==BITMAPSX || x>end_x) {
                        loader_mutex.lock();
                            blocked=0;
                            dont_stop=0;
                        loader_mutex.unlock();
                        return;
                    }
                }
                sf::sleep(sf::milliseconds(20));
            }
            sprintf(error_msg_s,"BACKGROUND MAP LOADER X=%d,Y=%d",x,y);
            error_flag_s=1;
            if (kill1==1 && kill2==1 && kill3==1) {
                loader_mutex.lock();
                    kill1=0;kill2=0;kill3=0;
                    blocked=0;
                    dont_stop=0;
                loader_mutex.unlock();
                return;
            }
        }
        loader_mutex.lock();
            kill1=1;kill2=1;kill3=1;
        loader_mutex.unlock();
        printf("Exiting thread LOAD_MAP_FOR_ALL_BITMAPS()\n");
        blocked=0;
        background_loader=0;
        sprintf(error_msg,"EXITING BACKGROUND MAP LOADER AT X=%d,X=%d",x,y);
        error_flag=1;
        return;
    }
}

void putinmazeSFML_final(int totalx,int totaly, int silent);

int sfml_picturex_ar[200];
int sfml_picturey_ar[200];

sf::Thread * thread_ar_sfml[200];

void loadit_sfml(int num) {
    putinmazeSFML_final(sfml_picturex_ar[num],sfml_picturey_ar[num],1);
}

void start_thread_sfml(int num) {
    if (thread_ar_sfml[num]==NULL) {
        thread_ar_sfml[num]=new sf::Thread(&loadit_sfml,num);
    }
    thread_ar_sfml[num]->launch();
}

void putinmazeSFML_thread_ar(int totalx, int totaly) {
    static int num=-1;
    num++;
    if (num>=200) num=0;
    sfml_picturex_ar[num]=totalx;
    sfml_picturey_ar[num]=totaly;
    start_thread_sfml(num);
}

void putinmazeSFML(int totalx, int totaly) {
//    if (F2==1) putinmazeSFML_final(totalx,totaly);
//    else putinmazeSFML_thread_ar(totalx,totaly);
//    putinmazeSFML_thread_ar((totalx+totalpicturex+1)%totalpicturex,(totaly+totalpicturey)%totalpicturey);
//    putinmazeSFML_thread_ar((totalx+totalpicturex)%totalpicturex,(totaly+totalpicturey+1)%totalpicturey);
//    putinmazeSFML_thread_ar((totalx+totalpicturex+1)%totalpicturex,(totaly+totalpicturey+1)%totalpicturey);
//hiero
    do_all=1;
        if (used[totalx][totaly]==1) {
            spritemaxinmempoint[used2[totalx][totaly]]->setTexture(texturemaxinmempoint[used2[totalx][totaly]]->getTexture(),false);
            spritemaxinmempoint[used2[totalx][totaly]]->setPosition(0,0);
            spritemaxinmempoint[used2[totalx][totaly]]->setTextureRect({0,0,1920,1080});
        }
        putinmazeSFML_final(totalx,totaly,0);
/*
        if (formula==1) {
            SFMLView1.setActive(true);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            SFMLView1.setActive(false);
            SFMLView1.draw(*spritemaxinmempoint[used2[totalx][totaly]]);
            if (F2==1) {
                draw2((char*)"GENERATING BACKGROUND",780,0,sf::Color(rand()%256,rand()%256,rand()%256,255),sf::Color::White);
            }
            SFMLView1.display();
        }
*/
}

void putinmazeSFML_final(int totalx,int totaly,int silent)
{
    static sf::Texture sfml_bitmaps;

    int x,y;
    int blokje=0;
    int mazeprintx;
    int mazeprinty;
    char naam[400];
    char mass[400];
//!!!!!!!!
    loader_mutex.lock();
    monitor_off=1;
    loader_mutex.unlock();

    if (formula>=1 && shade_map==0) {
        for (x=-1; x<=1; x++) {
            for (y=-1; y<=1; y++) {
                if ((formula>=1 && x==0 && y==0) || formula==2) {
                    if (MAZEOFF==1) {
//                        sprintf(naam,"levels/%dx%d/%03d/picture.%06d.%06d.png",BITMAPSX,BITMAPSY,level,(totaly+totalpicturey+y)%(totalpicturey),(totalx+totalpicturex+x)%(totalpicturex));
                        sprintf(naam,"%s/%dx%d/%03d/picture.%06d.%06d.png",LEVELDIR,BITMAPSX,BITMAPSY,level,(totaly+totalpicturey+y)%(totalpicturey),(totalx+totalpicturex+x)%(totalpicturex));
                        if (file_exists(naam)) {
                            if (files[(totalx+totalpicturex+x)%(totalpicturex)][(totaly+totalpicturey+y)%(totalpicturey)]==0) totalfiles++;
                            files[(totalx+totalpicturex+x)%(totalpicturex)][(totaly+totalpicturey+y)%(totalpicturey)]=1;
                        }
                        else {
                            if (files[(totalx+totalpicturex+x)%(totalpicturex)][(totaly+totalpicturey+y)%(totalpicturey)]==1) totalfiles--;
                            files[(totalx+totalpicturex+x)%(totalpicturex)][(totaly+totalpicturey+y)%(totalpicturey)]=0;
                        }
                        sprintf(naam,"%s/%dx%d/%03d/picture_maze.%06d.%06d.png",LEVELDIR,BITMAPSX,BITMAPSY,level,(totaly+totalpicturey+y)%(totalpicturey),(totalx+totalpicturex+x)%(totalpicturex));
                        if (file_exists(naam)) {
                            if (files_mazes[(totalx+totalpicturex+x)%(totalpicturex)][(totaly+totalpicturey+y)%(totalpicturey)]==0) totalfiles_mazes++;
                            files_mazes[(totalx+totalpicturex+x)%(totalpicturex)][(totaly+totalpicturey+y)%(totalpicturey)]=1;
                        }
                        else {
                            if (files_mazes[(totalx+totalpicturex+x)%(totalpicturex)][(totaly+totalpicturey+y)%(totalpicturey)]==1) totalfiles_mazes--;
                            files_mazes[(totalx+totalpicturex+x)%(totalpicturex)][(totaly+totalpicturey+y)%(totalpicturey)]=0;
                        }

                        error_flag=0;
                    }
                    if (files[(totalx+totalpicturex+x)%(totalpicturex)][(totaly+totalpicturey+y)%(totalpicturey)]==1 && used[(totalx+totalpicturex+x)%totalpicturex][(totaly+totalpicturey+y)%totalpicturey]==0) {
                        sprintf(naam,"%s/%dx%d/%03d/picture.%06d.%06d.png",LEVELDIR,BITMAPSX,BITMAPSY,level,(totaly+totalpicturey+y)%(totalpicturey),(totalx+totalpicturex+x)%(totalpicturex));
                        ReadSFML(naam,(totalx+totalpicturex+x)%(totalpicturex),(totaly+totalpicturey+y)%(totalpicturey),0);
                    }
                    user_mutex.lock();
                    if (used[(totalx+totalpicturex+x)%(totalpicturex)][(totaly+totalpicturey+y)%(totalpicturey)]==0)
                    {
                        int found=0;
                        int findempty=0;
                        while (findempty<(MAXINMEM+12) && found==0)
                        {
                            if (used_maxinmem[findempty]==0)
                            {
                                used_maxinmem[findempty]=1;
                                used2[(totalx+totalpicturex+x)%(totalpicturex)][(totaly+totalpicturey+y)%(totalpicturey)]=findempty;
                                used[(totalx+totalpicturex+x)%(totalpicturex)][(totaly+totalpicturey+y)%(totalpicturey)]=1;
                                texturemaxinmempoint[findempty]->clear(background_color[drawmazes]);
                                spritemaxinmempoint[findempty]->setTexture(texturemaxinmempoint[findempty]->getTexture(),false);
                                spritemaxinmempoint[findempty]->setPosition(0,0);
                                spritemaxinmempoint[findempty]->setTextureRect({0,0,1920,1080});
                                totalused++;
                                found=1;
                            }
                            findempty++;
                            if (found==1)
                                break;
                        }
                        if (found==0)
                        {
                            user_mutex.unlock();
                            savedata((char*)"no free spot PUTINMAZESFML",findempty);
                            sprintf(error_msg4,"ERROR: PUTINMAZESFML: X=%d/Y=%d ",(totalx+totalpicturex+x)%(totalpicturex),(totaly+totalpicturey+y)%(totalpicturey));
                            error_flag4=1;
                            return;
                        }
                    }
                    user_mutex.unlock();
                }
            }
        }
    }
    user_mutex.lock();
    if (used[totalx][totaly]==0)
//    if (used[(totalx+totalpicturex)%(totalpicturex)][(totaly+totalpicturey)%(totalpicturey)]==0)
    {
        int found=0;
        int findempty=0;
        while (findempty<(MAXINMEM+12) && found==0)
        {
            if (used_maxinmem[findempty]==0)
            {
                used_maxinmem[findempty]=1;
                used2[totalx][totaly]=findempty;
//                texturemaxinmempoint[findempty]->clear(background_color[drawmazes]);
//                used2[(totalx+totalpicturex)%(totalpicturex)][(totaly+totalpicturey)%(totalpicturey)]=findempty;
//hiero
                texturemaxinmempoint[findempty]->clear( background_color[drawmazes] );
//                texturemaxinmempoint[findempty]->create(1920,1080);
                spritemaxinmempoint[findempty]->setTexture(texturemaxinmempoint[findempty]->getTexture(),false);
                spritemaxinmempoint[findempty]->setPosition(0,0);
                spritemaxinmempoint[findempty]->setTextureRect({0,0,1920,1080});
//                texturemaxinmempoint[findempty]->clear( sf::Color(0,0,0,0) );

                used[totalx][totaly]=1;
//                used[(totalx+totalpicturex)%(totalpicturex)][(totaly+totalpicturey)%(totalpicturey)]=1;
                totalused++;
                found=1;
            }
            findempty++;
            if (found==1)
                break;
        }
        if (found==0)
        {
            savedata((char*)"no free spot PUTINMAZESFML",findempty);
            sprintf(error_msg4,"ERROR: PUTINMAZESFML: X=%d/Y=%d ",totalx,totaly);
            error_flag4=1;
            user_mutex.unlock();
            return;
        }
    }
    user_mutex.unlock();

extern char SAS_URL[];

    if (formula>0) {
        int mem_posx=posx;
        int mem_posy=posy;
        float mem_fposx=fposx;
        float mem_fposy=fposy;
        int mem_picturex=picturex;
        int mem_picturey=picturey;
        int set_off=1;
        wantedx=1920*totalx;
        wantedy=1080*totaly;
        if (do_all==1) {
            set_off=0;
        }
        go_pos=1;
        if (drawmazes==1 && formula==0)
        {
        }
        else
        {
            generate_tiles=0;
            if (shade_map>=1) {
                char ip[200];
                char page[4000];
                if (SAS_URL[0]>='0' && SAS_URL[0]<='9') {
                    int dummy;
                    if (toupper(SAS_URL[5])=='S') sscanf(SAS_URL, "%dhttps://%199[^/]/%199[^\n]",&dummy, ip,page );
                    else sscanf(SAS_URL, "%dhttp://%199[^/]/%199[^\n]",&dummy, ip,page);
                    strcpy(page,ip);
                    sprintf(ip,"%s-%d",page,dummy);
                } else {
                    if (toupper(SAS_URL[4])=='S') sscanf(SAS_URL, "https://%199[^/]/%199[^\n]", ip,page );
                    else sscanf(SAS_URL, "http://%199[^/]/%199[^\n]", ip,page);
                }
                if (ip[0]=='l' && ip[1]=='o' && ip[2]=='c' && ip[3]=='a' && ip[4]=='l') generate_tiles=1;
            }
            if (shade_map>=1 && formula==1 && (helpme==1 || DO_ADAPT==1) && generate_tiles==0) {
                if (blocked==1 && once==0) {
                    printf("BACKGROUND LOADERS BLOCKED BY OTHER BACKGROUND PROCESS? NOT USING THEM.\nSTATUS BACKGROUND LOADERS:\n");
                    if (kill1==1) printf("THREAD 1 KILLED.\n"); else printf("THREAD 1 NOT KILLED, READY FOR USAGE.\n");
                    if (kill2==1) printf("THREAD 2 KILLED.\n"); else printf("THREAD 2 NOT KILLED, READY FOR USAGE.\n");
                    if (kill3==1) printf("THREAD 3 KILLED.\n"); else printf("THREAD 3 NOT KILLED, READY FOR USAGE.\n");
                    if (loader1_active==1) printf("THREAD 1 ACTIVE.\n"); else printf("THREAD 1 INACTIVE.\n");
                    if (loader2_active==1) printf("THREAD 2 ACTIVE.\n"); else printf("THREAD 2 INACTIVE.\n");
                    if (loader3_active==1) printf("THREAD 3 ACTIVE.\n"); else printf("THREAD 3 INACTIVE.\n");
                    once=1;
                }
//                    if (blocked==0) {
                if (blocked==0 && helpme==1) {
                    blocked=1;
                    static int picx1=-1;
                    static int picy1=-1;
                    if (kill1==0 && loader1_active==0 && (picx1!=totalx*(mul+1) || picy1!=totaly*(mul+1))) {
                        sprintf(mass,"%s/map.z%d/pictures/y%d/picture.%06d.%06d.png",
                            LEVELDIR,get_map_zoom,
                            offset_picture_y+totaly,offset_picture_y+totaly,
                            offset_picture_x+(totalx+1+maxpicturex)%maxpicturex);
                        if (!file_exists(mass)) {
                            mytotal1=sf::Vector2i((totalx+1+maxpicturex)%maxpicturex,totaly);
                            launch_background_loader_one();
                            picx1=totalx*(mul+1);
                            picy1=totaly*(mul+1);
                        }
                    }
                    static int picx2=-1;
                    static int picy2=-1;
                    if (kill2==0 && loader2_active==0 && (picx2!=totalx*(mul+1) || picy2!=totaly*(mul+1))) {
                        sprintf(mass,"%s/map.z%d/pictures/y%d/picture.%06d.%06d.png",
                            LEVELDIR,get_map_zoom,
                            offset_picture_y+(totaly+1+maxpicturey)%maxpicturey,offset_picture_y+(totaly+1+maxpicturey)%maxpicturey,
                            offset_picture_x+totalx);
                        if (!file_exists(mass)) {
                            mytotal2=sf::Vector2i(totalx  ,(totaly+1+maxpicturey)%maxpicturey);
                            launch_background_loader_two();
                            picx2=totalx*(mul+1);
                            picy2=totaly*(mul+1);
                        }
                    }
                    static int picx3=-1;
                    static int picy3=-1;
                    if (kill3==0 && loader3_active==0 && (picx3!=totalx*(mul+1) || picy3!=totaly*(mul+1))) {
                        sprintf(mass,"%s/map.z%d/pictures/y%d/picture.%06d.%06d.png",
                            LEVELDIR,get_map_zoom,
                            offset_picture_y+(totaly+1+maxpicturey)%maxpicturey,offset_picture_y+(totaly+1+maxpicturey)%maxpicturey,
                            offset_picture_x+(totalx+1+maxpicturex)%maxpicturex);
                        if (!file_exists(mass)) {
                            mytotal3=sf::Vector2i((totalx+1+maxpicturex)%maxpicturex,(totaly+1+maxpicturey)%maxpicturey);
                            launch_background_loader_three();
                            picx3=totalx*(mul+1);
                            picy3=totaly*(mul+1);
                        }
                    }
//                        if (plot_all==0) {
                        static int picx4=-1;
                        static int picy4=-1;
                        if (kill1==0 && loader1_active==0 && (picx4!=totalx*(mul+1) || picy4!=totaly*(mul+1))) {
                            sprintf(mass,"%s/map.z%d/pictures/y%d/picture.%06d.%06d.png",
                                LEVELDIR,get_map_zoom,
                                offset_picture_y+(totaly+maxpicturey)%maxpicturey,offset_picture_y+(totaly+maxpicturey)%maxpicturey,
                                offset_picture_x+(totalx-1+maxpicturex)%maxpicturex);
                            if (!file_exists(mass)) {
                                mytotal3=sf::Vector2i((totalx-1+maxpicturex)%maxpicturex,(totaly+maxpicturey)%maxpicturey);
                                launch_background_loader_one();
                                picx4=totalx*(mul+1);
                                picy4=totaly*(mul+1);
                            }
                        }
//                        }
//                        if (plot_all==0) {
                        static int picx5=-1;
                        static int picy5=-1;
                        if (kill1==0 && loader1_active==0 && (picx5!=totalx*(mul+1) || picy5!=totaly*(mul+1))) {
                            sprintf(mass,"%s/map.z%d/pictures/y%d/picture.%06d.%06d.png",
                                LEVELDIR,get_map_zoom,
                                offset_picture_y+(totaly-1+maxpicturey)%maxpicturey,offset_picture_y+(totaly-1+maxpicturey)%maxpicturey,
                                offset_picture_x+(totalx+maxpicturex)%maxpicturex);
                            if (!file_exists(mass)) {
                                mytotal3=sf::Vector2i((totalx+maxpicturex)%maxpicturex,(totaly-1+maxpicturey)%maxpicturey);
                                launch_background_loader_one();
                                picx5=totalx*(mul+1);
                                picy5=totaly*(mul+1);
                            }
                        }
//                        }
//                        if (plot_all==0) {
                        static int picx6=-1;
                        static int picy6=-1;
                        if (kill2==0 && loader2_active==0 && (picx6!=totalx*(mul+1) || picy6!=totaly*(mul+1))) {
                            sprintf(mass,"%s/map.z%d/pictures/y%d/picture.%06d.%06d.png",
                                LEVELDIR,get_map_zoom,
                                offset_picture_y+(totaly+1+maxpicturey)%maxpicturey,offset_picture_y+(totaly+1+maxpicturey)%maxpicturey,
                                offset_picture_x-1+totalx);
                            if (!file_exists(mass)) {
                                mytotal2=sf::Vector2i((totalx-1+maxpicturex)%maxpicturex  ,(totaly+1+maxpicturey)%maxpicturey);
                                launch_background_loader_two();
                                picx6=totalx*(mul+1);
                                picy6=totaly*(mul+1);
                            }
                        }
//                        }
//                        if (plot_all==0) {
                        static int picx7=-1;
                        static int picy7=-1;
                        if (kill2==0 && loader2_active==0 && (picx7!=totalx*(mul+1) || picy7!=totaly*(mul+1))) {
                            sprintf(mass,"%s/map.z%d/pictures/y%d/picture.%06d.%06d.png",
                                LEVELDIR,get_map_zoom,
                                offset_picture_y+(totaly-1+maxpicturey)%maxpicturey,offset_picture_y+(totaly-1+maxpicturey)%maxpicturey,
                                offset_picture_x-1+totalx);
                            if (!file_exists(mass)) {
                                mytotal2=sf::Vector2i((totalx-1+maxpicturex)%maxpicturex  ,(totaly-1+maxpicturey)%maxpicturey);
                                launch_background_loader_two();
                                picx7=totalx*(mul+1);
                                picy7=totaly*(mul+1);
                            }
                        }
//                        }
//                        if (plot_all==0) {
                        static int picx8=-1;
                        static int picy8=-1;
                        if (kill3==0 && loader3_active==0 && (picx8!=totalx*(mul+1) || picy8!=totaly*(mul+1))) {
                            sprintf(mass,"%s/map.z%d/pictures/y%d/picture.%06d.%06d.png",
                                LEVELDIR,get_map_zoom,
                                offset_picture_y+(totaly-1+maxpicturey)%maxpicturey,offset_picture_y+(totaly-1+maxpicturey)%maxpicturey,
                                offset_picture_x+(totalx+1+maxpicturex)%maxpicturex);
                            if (!file_exists(mass)) {
                                mytotal3=sf::Vector2i((totalx+1+maxpicturex)%maxpicturex,(totaly-1+maxpicturey)%maxpicturey);
                                launch_background_loader_three();
                                picx8=totalx*(mul+1);
                                picy8=totaly*(mul+1);
                            }
                        }
//                        }
                    blocked=0;
                }
            }
//                printf("Running wierdo: %d,%d\n",totalx,totaly);

//error fok it! kut
//            if (shade_map>=1) {
            if (drawmazes==1 && shade_map>=1) {

                sprintf(naam,"%s/%dx%d/%03d/picture.%06d.%06d.png",LEVELDIR,BITMAPSX,BITMAPSY,level,(totaly),(totalx));
                if (file_exists(naam)) {
                    if (files[totalx][totaly]==0) { totalfiles++; files[totalx][totaly]=1; }
                    sf::Sprite sprite;

                    sfml_bitmaps.loadFromFile(naam);
                    sprite.setTexture(sfml_bitmaps,true);
                    sprite.setTextureRect({0,0,1920,1080});
                    texturemaxinmempoint[used2[totalx][totaly]]->clear(background_color[drawmazes]);
                    texturemaxinmempoint[used2[totalx][totaly]]->draw(sprite);
                    if (strlen(SAS_LAYER)>0) {
                        sprintf(mass,"%s/%s/map.z%d/pictures/y%d/picture.%06d.%06d.png",MAPDIR,SAS_LAYER,get_map_zoom,offset_picture_y+totaly,offset_picture_y+totaly,offset_picture_x+totalx);
                        if (file_exists(mass)) {
                            sfml_bitmaps.loadFromFile(mass);
                            texturemaxinmempoint[used2[totalx][totaly]]->draw(sprite);
                        }
                    }
                    texturemaxinmempoint[used2[totalx][totaly]]->display();
//                        if (plot_all==1) texturemaxinmempoint[used2[totalx][totaly]]->generateMipmap();
//                        if (changed[totalx][totaly]==0) {
//                            changed[totalx][totaly]=1;
//                            totalchanged++;
//                        }
                } else {

                    sprintf(mass,"%s/map.z%d/pictures/y%d/picture.%06d.%06d.png",LEVELDIR,get_map_zoom,offset_picture_y+totaly,offset_picture_y+totaly,offset_picture_x+totalx);
//                        sprintf(mass,"%s/map.z%d/picture.%06d.%06d.png",LEVELDIR,get_map_zoom,offset_picture_y+totaly,offset_picture_x+totalx);
                    if (file_exists(mass)) {
//                            if (DO_ADAPT==0) CopyFile(mass,naam,true);
                        sf::Sprite sprite;

                        sfml_bitmaps.loadFromFile(mass);
                        sprite.setTexture(sfml_bitmaps,true);
                        sprite.setTextureRect({0,0,1920,1080});
                        texturemaxinmempoint[used2[totalx][totaly]]->clear(background_color[drawmazes]);
                        texturemaxinmempoint[used2[totalx][totaly]]->draw(sprite);
                        texturemaxinmempoint[used2[totalx][totaly]]->display();
//                            if (plot_all==1) texturemaxinmempoint[used2[totalx][totaly]]->generateMipmap();
//                            if (changed[totalx][totaly]==0) {
//                                changed[totalx][totaly]=1;
//                                totalchanged++;
//                            }
                        if (files[totalx][totaly]==0) { totalfiles++; files[totalx][totaly]=1; }
                    } else {
                        if (files[totalx][totaly]==1) { totalfiles--; files[totalx][totaly]=0; }
                        ret=wierdo(totalx,totaly, silent);
                    }
                }



            } else {
                if (shade_map>=1) {
                    sprintf(mass,"%s/map.z%d/pictures/y%d/picture.%06d.%06d.png",LEVELDIR,get_map_zoom,offset_picture_y+totaly,offset_picture_y+totaly,offset_picture_x+totalx);
//                        sprintf(mass,"%s/map.z%d/picture.%06d.%06d.png",LEVELDIR,get_map_zoom,offset_picture_y+totaly,offset_picture_x+totalx);
                    if (file_exists(mass)) {
                        sprintf(naam,"%s/%dx%d/%03d/picture.%06d.%06d.png",LEVELDIR,BITMAPSX,BITMAPSY,level,(totaly),(totalx));
//error kut
                        if (DO_ADAPT==0) CopyFile(mass,naam,true);
                        if (do_all==1 && plot_all==0 && DO_ADAPT==0) {
                            if (used[totalx][totaly]==1)
                            {
                                used[totalx][totaly]=0;
                                totalused--;
                                used_maxinmem[used2[totalx][totaly]]=0;
                            }
                        } else {
                            sf::Sprite sprite;
                            sfml_bitmaps.loadFromFile(mass);
                            sprite.setTexture(sfml_bitmaps,true);
                            sprite.setTextureRect({0,0,1920,1080});
                            texturemaxinmempoint[used2[totalx][totaly]]->clear(background_color[drawmazes]);
                            texturemaxinmempoint[used2[totalx][totaly]]->draw(sprite);
                            texturemaxinmempoint[used2[totalx][totaly]]->display();
//                                if (plot_all==1) texturemaxinmempoint[used2[totalx][totaly]]->generateMipmap();
                        }
//                            if (changed[totalx][totaly]==0) {
//                                changed[totalx][totaly]=1;
//                                totalchanged++;
//                            }

                        if (files[totalx][totaly]==0) { totalfiles++; files[totalx][totaly]=1; }
                    } else {
                        if (plot_all==0) count_errors=0;
                        if (shade_map==1 && generate_tiles==1) {
                            blend_tiles=1;
                            ret=wierdo(totalx,totaly, silent);
                            blend_tiles=0;
                        } else {
                            ret=wierdo(totalx,totaly, silent);
                        }
                    }



                } else {
//                    texturemaxinmempoint[used2[totalx][totaly]]->display();
                    ret=wierdo(totalx,totaly, silent);
                    ret=-10;

//                    if (changed[totalx][totaly]==1) {
//                        sprintf(naam,"%s/%dx%d/%03d/picture.%06d.%06d.png",LEVELDIR,BITMAPSX,BITMAPSY,level,(totaly),(totalx));
//                        texturemaxinmempoint[used2[totalx][totaly]]->getTexture().copyToImage().saveToFile(naam);
//                        if (changed[totalx][totaly]==1) {
//                            changed[totalx][totaly]=0;
//                            totalchanged--;
//                        }
//                    }
//hiero
//                    texturemaxinmempoint[used2[totalx][totaly]]->draw(*spritemaxinmempoint[used2[x][y]]);
//                    if (ret==0) texturemaxinmempoint[used2[totalx][totaly]]->display();
                }
            }
/*
            if (drawmazes==1) {
                if ((changed[totalx][totaly]==1 && shade_map>=1))
                {
                    sprintf(naam,"%s/%dx%d/%03d/picture.%06d.%06d.png",LEVELDIR,BITMAPSX,BITMAPSY,level,(totaly),(totalx));
                    if (file_exists(naam)==false) {
//                            texturemaxinmempoint[used2[totalx][totaly]]->display();
                        texturemaxinmempoint[used2[totalx][totaly]]->getTexture().copyToImage().saveToFile(naam);
                        sprintf(error_msg4,"NEW BACKGROUND FILE %s ALSO SAVED.",naam);
                        error_flag4=1;
                        if (files[totalx][totaly]=0) totalfiles++;
                        files[totalx][totaly]=1;
                    } else {
                        if (files[totalx][totaly]=0) totalfiles++;
                        files[totalx][totaly]=1;
                    }
//                        changed[totalx][totaly]=0;totalchanged--;
                }
            }
*/
            if (shade_map>=1) {
                sprintf(naam,"%s/%dx%d/%03d/picture.%06d.%06d.png",LEVELDIR,BITMAPSX,BITMAPSY,level,(totaly),(totalx));
                sprintf(mass,"%s/map.z%d/pictures/y%d/picture.%06d.%06d.png",LEVELDIR,get_map_zoom,offset_picture_y+totaly,offset_picture_y+totaly,offset_picture_x+totalx);

                char nop[100];
                char dirname[1000];
                DIR* dir;

                if (changed[totalx][totaly]==1) {
                    sprintf(dirname,"%s/map.z%d/pictures/y%d",LEVELDIR,get_map_zoom,offset_picture_y+totaly);
                    while (replace_str(dirname,"/","\\\\"));
                    dir = opendir(dirname);
                    if (!dir)
                    {
                        closedir(dir);

                        sprintf(dirname,"%s\\map.z%d",LEVELDIR,get_map_zoom);
                        int msgboxID=0;
                        dir = opendir(dirname);
                        if (!dir)
                        {
                            mkdir(dirname);
                            dir = opendir(dirname);
                            if (!dir) {msgboxID=MessageBox(NULL, "CANNOT CREATE DIRECTORY FOR", (char*)dirname,MB_OK); }
                            else closedir(dir);
                        } else closedir(dir);

                        sprintf(dirname,"%s/map.z%d/pictures",LEVELDIR,get_map_zoom);
                        while (replace_str(dirname,"/","\\\\"));
                        dir = opendir(dirname);
                        if (!dir)
                        {
                            mkdir(dirname);
                            dir = opendir(dirname);
                            if (!dir) {msgboxID=MessageBox(NULL, "CANNOT CREATE DIRECTORY FOR", (char*)dirname,MB_OK); }
                            else  closedir(dir);
                        } else closedir(dir);

                        sprintf(nop,"\\y%d",offset_picture_y+totaly);
                        strcat(dirname,nop);
                        dir = opendir(dirname);
                        if (!dir)
                        {
                            mkdir(dirname);
                            dir = opendir(dirname);
                            if (!dir) {msgboxID=MessageBox(NULL, "CANNOT CREATE DIRECTORY FOR", (char*)dirname,MB_OK); }
                            else closedir(dir);
                        } else closedir(dir);
                    } else closedir(dir);
                }

                if (changed[totalx][totaly]==1) {
                    if (generate_tiles==0) {
                        if (file_exists(mass)==false) {
                            texturemaxinmempoint[used2[totalx][totaly]]->getTexture().copyToImage().saveToFile(mass);
//                            if (DO_ADAPT==0) CopyFile(mass,naam,false);
                        } else {
                            printf("Error:\n%s\n%s\n",naam,mass);
                        }
                        changed[totalx][totaly]=0;totalchanged--;
                    }
                }
//                    if (file_exists(naam) && file_exists(mass)==false) {
//                        CopyFile(naam,mass,true);
//                    }
                if (drawmazes==1) if (changed[totalx][totaly]==1) { changed[totalx][totaly]=0; totalchanged--; }
                if (shade_map==1 && generate_tiles==0) {
                    generate_tiles=1;
                    blend_tiles=1;
                    wierdo(totalx,totaly,1);
                    generate_tiles=0;
                    blend_tiles=0;
                } else if (shade_map==1 && generate_tiles==1) {
                    blend_tiles=1;
                    wierdo(totalx,totaly,1);
                    texturemaxinmempoint[used2[totalx][totaly]]->display();
                    generate_tiles=0;
                    blend_tiles=0;
                    if (changed[totalx][totaly]==0)
                    {
                            changed[totalx][totaly]=1;
                            totalchanged++;
                    }
                }
                if (strlen(SAS_LAYER)>0) {
                    sprintf(mass,"%s/%s/map.z%d/pictures/y%d/picture.%06d.%06d.png",MAPDIR,SAS_LAYER,get_map_zoom,offset_picture_y+totaly,offset_picture_y+totaly,offset_picture_x+totalx);
                    if (file_exists(mass)) {
                        sf::Sprite sprite;
                        sfml_bitmaps.loadFromFile(mass);
                        sprite.setTexture(sfml_bitmaps,true);
                        sprite.setTextureRect({0,0,1920,1080});
                        texturemaxinmempoint[used2[totalx][totaly]]->draw(sprite);
                        texturemaxinmempoint[used2[totalx][totaly]]->display();
                    }
                }
            }
            if (ret==0 && (changed[totalx][totaly]==0 && formula!=2 && !shade_map>=1))
            {
                    changed[totalx][totaly]=1;
                    totalchanged++;
            }
            if (ret==-10) ret=0;
        }
        if (set_off==1) go_pos=0;
    }
    if (drawmazes==1 && blank_maze==0)
    {
        DRAWMAZE(totalx,totaly);
    } else {
        if (plot_all==1) texturemaxinmempoint[used2[totalx][totaly]]->generateMipmap();
//        texturemaxinmempoint[used2[totalx][totaly]]->display();
    }
    sprintf(writer,"X=%d/Y=%d ",totalx,totaly);
    if (strlen(error_msg4)>100)
        strcpy(error_msg4,"CREATED: ");
    strcat(error_msg4,writer);
    error_flag4=1;
    kiki();
    kiki();
    kiki();
    kiki();
    kiki();
}

void gen_all_mipmaps() {
    for (int x=0; x<MAXINMEM+12; x++)
    {
        if (used_maxinmem[x]==1) texturemaxinmempoint[x]->generateMipmap();
    }
}

void RenderBlit_adapt2(int totalx,int totaly, int xdest, int ydest, int width, int height, int xsource, int ysource, int remote_pen_mode)
{
    spritedot.setPosition(xdest,ydest);

    static int first=0;
    static sf::BlendMode MyBlend=sf::BlendAdd;
    static sf::BlendMode MyBlend2=sf::BlendAlpha;
    if (first==0) {
        MyBlend.alphaSrcFactor    = sf::BlendMode::One;
        MyBlend.alphaDstFactor    = sf::BlendMode::One;
        MyBlend.alphaEquation     = sf::BlendMode::ReverseSubtract;
        MyBlend2.colorSrcFactor   = sf::BlendMode::OneMinusDstAlpha;
        MyBlend2.colorDstFactor   = sf::BlendMode::One;
        MyBlend2.colorEquation    = sf::BlendMode::Add;
        MyBlend2.alphaSrcFactor   = sf::BlendMode::OneMinusDstAlpha;
        MyBlend2.alphaDstFactor   = sf::BlendMode::DstColor;
        MyBlend2.alphaEquation    = sf::BlendMode::Add;
        first==1;
    }

    if (remote_pen_mode==1)
    {
        if (kleur_front==1) {
            spritedot.setTextureRect(   { xsource,12*72,width, height }  );
            texturemaxinmempoint[used2[totalx][totaly]]->draw(spritedot,MyBlend);
            spritedot.setTextureRect(   { 0,6*72,width, height }  );
            texturemaxinmempoint[used2[totalx][totaly]]->draw(spritedot,MyBlend2);
        } else {
            spritedot.setTextureRect(   { xsource,12*72,width, height }  );
            texturemaxinmempoint[used2[totalx][totaly]]->draw(spritedot,MyBlend);
        }
    }

    spritedot.setTextureRect(   { xsource, ysource,width, height }  );
    texturemaxinmempoint[used2[totalx][totaly]]->draw(spritedot);
}

extern int plot_shader;

void DRAWMAZE(int totalx,int totaly)
{
    int x,y;
    int blokje=0;
    int mazeprintx;
    int mazeprinty;
    int found=0;
    int findempty=0;
    if (blank_maze==1) {
        if (plot_all==1) texturemaxinmempoint[used2[totalx][totaly]]->generateMipmap();
        return;
    }
    if ( (eatmode==0 || loaded_picture==0) && plot_shader!=2) {
        for (x=0; x<30; x++) {
            for (y=0; y<15; y++) {
                mazeprintx=(totalx*30+x -60 + (maxpicturex+1)*30 )%((maxpicturex+1)*30);
                mazeprinty=(totaly*15+y -30 + (maxpicturey+1)*15 )%((maxpicturey+1)*15);
                blokje=maze_plot[ mazeprintx ][ mazeprinty ];
                if (kleur_front==1) {
                    spritedot.setTextureRect(   { 0,6*72,64,72 }     ); spritedot.setPosition(x*64,y*72);  texturemaxinmempoint[used2[totalx][totaly]]->draw(spritedot);
                }
                if ((blokje&16)==16)
                {
                    if ((blokje&32)==32) {
                        spritedot.setTextureRect(   { (blokje&3)*64,9*72,64,72 }     ); spritedot.setPosition(x*64,y*72);  texturemaxinmempoint[used2[totalx][totaly]]->draw(spritedot);
                        spritedot.setTextureRect(   { (blokje&12)*64,9*72,64,72 }     ); spritedot.setPosition(x*64,y*72);  texturemaxinmempoint[used2[totalx][totaly]]->draw(spritedot);
                    } else if ((blokje&64)==64) {
                        spritedot.setTextureRect(   { (blokje&12)*64,9*72,64,72 }     ); spritedot.setPosition(x*64,y*72);  texturemaxinmempoint[used2[totalx][totaly]]->draw(spritedot);
                        spritedot.setTextureRect(   { (blokje&3)*64,9*72,64,72 }     ); spritedot.setPosition(x*64,y*72);  texturemaxinmempoint[used2[totalx][totaly]]->draw(spritedot);
                    } else
                        spritedot.setTextureRect(   { (blokje&15)*64,9*72,64,72 }     ); spritedot.setPosition(x*64,y*72);  texturemaxinmempoint[used2[totalx][totaly]]->draw(spritedot);
                }
                else
                {
                    if ((blokje&32)==32) {
                        spritedot.setTextureRect(   { (blokje&3)*64,0,64,72 }     ); spritedot.setPosition(x*64,y*72);  texturemaxinmempoint[used2[totalx][totaly]]->draw(spritedot);
                        spritedot.setTextureRect(   { (blokje&12)*64,0,64,72 }     ); spritedot.setPosition(x*64,y*72);  texturemaxinmempoint[used2[totalx][totaly]]->draw(spritedot);
                    } else if ((blokje&64)==64) {
                        spritedot.setTextureRect(   { (blokje&12)*64,0,64,72 }     ); spritedot.setPosition(x*64,y*72);  texturemaxinmempoint[used2[totalx][totaly]]->draw(spritedot);
                        spritedot.setTextureRect(   { (blokje&3)*64,0,64,72 }     ); spritedot.setPosition(x*64,y*72);  texturemaxinmempoint[used2[totalx][totaly]]->draw(spritedot);
                    } else
                        spritedot.setTextureRect(   { (blokje&15)*64,0,64,72 }     );     spritedot.setPosition(x*64,y*72);   texturemaxinmempoint[used2[totalx][totaly]]->draw(spritedot);
                }
                blokje=0;
            }
        }
    } else {
        for (x=0; x<30; x++) {
            for (y=0; y<15; y++) {
                mazeprintx=(totalx*30+x -60 + (maxpicturex+1)*30 )%((maxpicturex+1)*30);
                mazeprinty=(totaly*15+y -30 + (maxpicturey+1)*15 )%((maxpicturey+1)*15);
                blokje=maze_plot[ mazeprintx ][ mazeprinty ];
                if ((blokje&16)==16)
                {
                    if ((blokje&32)==32) {
                        RenderBlit_adapt2(totalx,totaly, x*64, y*72, 64, 72, (3)*64, 13*72, 1);
                        RenderBlit_adapt2(totalx,totaly, x*64, y*72, 64, 72, (12)*64, 13*72, 0);
                    } else if ((blokje&64)==64) {
                        RenderBlit_adapt2(totalx,totaly, x*64, y*72, 64, 72, (12)*64, 13*72, 1);
                        RenderBlit_adapt2(totalx,totaly, x*64, y*72, 64, 72, (3)*64, 13*72, 0);
                    } else
                        RenderBlit_adapt2(totalx,totaly, x*64, y*72, 64, 72, (blokje&15)*64, 13*72, 1);
                }
                else
                {
                    if ((blokje&32)==32) {
                        RenderBlit_adapt2(totalx,totaly, x*64, y*72, 64, 72, (3)*64, 13*72, 1);
                        RenderBlit_adapt2(totalx,totaly, x*64, y*72, 64, 72, (12)*64, 13*72, 0);
                    } else if ((blokje&64)==64) {
                        RenderBlit_adapt2(totalx,totaly, x*64, y*72, 64, 72, (12)*64, 13*72, 1);
                        RenderBlit_adapt2(totalx,totaly, x*64, y*72, 64, 72, (3)*64, 13*72, 0);
                    } else
                        RenderBlit_adapt2(totalx,totaly, x*64, y*72, 64, 72, (blokje&15)*64, 13*72, 1);
                }
                blokje=0;
            }
        }
    }
    texturemaxinmempoint[used2[totalx][totaly]]->display();
    if (plot_all) texturemaxinmempoint[used2[totalx][totaly]]->generateMipmap();
    return;
}


void DRAWALLMAZES()
{
    int x,y;

    for (x=0; x<totalpicturex; x++)
    {
        for (y=0; y<totalpicturey; y++)
        {
//??????????

            if (used[x][y]==1)
            {
                DRAWMAZE(x,y);
                if (F2==1) {
                    sprintf(writer,"DRAWING MAZE ONLY IN USED BITMAPS X=%d/Y=%d ",x,y);
                    blitter(writer,0);
                }
//                if (changed[x][y]==0) {
//                    changed[x][y]=1;
//                    totalchanged++;
//                }
            }
        }
    }

    strcpy(error_msg4,"MAZES DRAWN ONLY IN USED BITMAPS");
    error_flag4=1;
    return;
}


void HALT()
{
    speedy_new=0;
    speedx_new=0;
    fspeedy_new=0;
    fspeedx_new=0;
    speedy=0;
    speedx=0;
    fspeedy=0;
    fspeedx=0;
    maze_up_new=0;
    maze_down_new=0;
    maze_left_new=0;
    maze_right_new=0;
    maze_up=0;
    maze_down=0;
    maze_left=0;
    maze_right=0;
    return;
}

void SENDGOTOPOS()
{
    int mazemovex=(picturex*1920-posx-32)/64;
    int mazemovey=(picturey*1080-posy   )/72;
    mazemovex=(mazemovex-45+60*(totalpicturex))%(30*(totalpicturex));
    mazemovey=(mazemovey-23+30*(totalpicturey))%(15*(totalpicturey));
    sprintf(writer,"T=GOTO,X=%d,Y=%d,\0",mazemovex,mazemovey);
    SEND(writer);
}


void zetom()
{
    int totalx,totaly;
    int x,y;
    int blokje=0;
    int mazeprintx;
    int mazeprinty;
    int mazeplotx;
    int mazeploty;
    int xx,yy;


    int tot=totalpicturex*30;
    int maxx=totalpicturex*30;
    int maxy=totalpicturey*15;
    if (combine==0)
    {
        int scount=500;
        for (xx=maxx-1; xx>=0; xx--)
        {
            scount--;
            if (scount==0)
            {
                scount=500;
                sprintf(line,"CLEANING MAP LINE=%d/%d",xx,tot);
                blitter(line,1);
            }
            for (yy=maxy-1; yy>=0; yy--)
            {
                maze_plot[xx][yy]=0;
            }
        }
        plotx=0;
        ploty=0;
        sprintf(line,"CLEANING MAP LINE=%d/%d",xx,tot);
        blitter(line,1);
    }
    tot=totalpicturex*totalpicturey;
    int scount=100;
//turn
    for (xx=0; xx<=maxpicturex; xx++)
    {
        for (yy=0; yy<=maxpicturey; yy++)
        {
            scount--;
            if (scount==0)
            {
                scount=2000;
                sprintf(line,"CONVERTING MAZE TO MAP BITMAP=%d/%d",yy+(xx-1)*totalpicturey,tot);
                blitter(line,1);
            }

            totalx=xx;
            if (totalx>maxpicturex)
                totalx=0;
            totaly=yy;
            if (totaly>maxpicturey)
                totaly=0;

            int addx=0;
            int minx=0;
            if (xx==maxpicturex)
                addx=1;
            else
                addx=0;
            if (xx==0)
                minx=1;
            else
                minx=0;
            for (x=0-minx; x<30+addx; x++)
            {
                int addy;
                int miny;
                if (yy==maxpicturey)
                    addy=1;
                else
                    addy=0;
                if (yy==0)
                    miny=1;
                else
                    miny=0;
                for (y=0-miny; y<15+addy; y++)
                {
                    if (adapt_maze==1) {
                        mazeplotx=(-59+totalx*30+x -1 + plotx+maxx )%(maxx);
                        mazeploty=(-30+totaly*15+y -1 + ploty+maxy )%(maxy);
//                        mazeprintx=(-59+totalx*30+x -1 + plotx+(maxpicturex+1)*30 )%((maxpicturex+1)*30);
//                        mazeprinty=(-30+totaly*15+y -1 + ploty+(maxpicturey+1)*15 )%((maxpicturey+1)*15);
                    } else {
                        mazeplotx=(totalx*30+x -1 + plotx+maxx )%(maxx);
                        mazeploty=(totaly*15+y -1 + ploty+maxy )%(maxy);
//                        mazeprintx=(totalx*30+x -1 + plotx+(maxpicturex+1)*30 )%((maxpicturex+1)*30);
//                        mazeprinty=(totaly*15+y -1 + ploty+(maxpicturey+1)*15 )%((maxpicturey+1)*15);
                    }

                    blokje=maze_plot[ mazeplotx ][ mazeploty ];


//                    mazeprintx=(totalx*30*2+0  +x*2 )%((maxpicturex+1)*30*2+4);
                    mazeprintx=(totalx*30*2+0  +x*2 +maxx*2+4)%(maxx*2+4);
                    if (mazeprintx<0)
                        mazeprintx+=maxx*2;
                    mazeprinty=(totaly*15*2+0  +y*2 +maxy*2+4)%(maxy*2+4);
                    if (mazeprinty<0)
                        mazeprinty+=maxy*2;

//crossing
                    int blokje_old=blokje;
                    if (  (Maze[mazeprintx][mazeprinty]) == '*')
                        blokje=blokje | 16;
                    else if (  (Maze[mazeprintx][mazeprinty]) == '-')
                        blokje=blokje | 32;
                    else if (  (Maze[mazeprintx][mazeprinty]) == '|')
                        blokje=blokje | 64;
                    if ((blokje&(32+64))==(32+64)) {
                        if (crossing==1) blokje=blokje&(255-64);
                        else if (crossing==2) blokje=blokje&(255-32);
                        else if ((blokje_old&32)==32) blokje=blokje&(255-64);
                        else blokje=blokje&(255-32);
                    }

                    mazeprintx=(totalx*30*2+0  +x*2 +maxx*2+4)%(maxx*2+4);
                    if (mazeprintx<0)
                        mazeprintx+=maxx*2;
                    mazeprinty=(totaly*15*2+0-1+y*2 +maxy*2+4)%(maxy*2+4);
                    if (mazeprinty<0)
                        mazeprinty+=maxy*2;

                    if (  (Maze[mazeprintx][mazeprinty]) == ' ')
                        blokje=blokje | 1;
//                    else if (  (Maze[mazeprintx][mazeprinty]) == '#')
//                        blokje=blokje | (1+16);

                    mazeprintx=(totalx*30*2+0  +x*2 +maxx*2+4)%(maxx*2+4);
                    if (mazeprintx<0)
                        mazeprintx+=maxx*2;
                    mazeprinty=(totaly*15*2+0+1+y*2 +maxy*2+4)%(maxy*2+4);
                    if (mazeprinty<0)
                        mazeprinty+=maxy*2;

                    if (  (Maze[mazeprintx][mazeprinty]) == ' ')
                        blokje=blokje | 2;
//                    else if (  (Maze[mazeprintx][mazeprinty]) == '#')
//                        blokje=blokje | (2+16);


                    mazeprintx=(totalx*30*2+0-1+x*2 +maxx*2+4)%(maxx*2+4);
                    if (mazeprintx<0)
                        mazeprintx+=maxx*2;
                    mazeprinty=(totaly*15*2+0  +y*2 +maxy*2+4)%(maxy*2+4);
                    if (mazeprinty<0)
                        mazeprinty+=maxy*2;

                    if (  (Maze[mazeprintx][mazeprinty]) == ' ')
                        blokje=blokje | 4;
//                    else if (  (Maze[mazeprintx][mazeprinty]) == '#')
//                        blokje=blokje | (4+16);


                    mazeprintx=(totalx*30*2+0+1+x*2 +maxx*2+4)%(maxx*2+4);
                    if (mazeprintx<0)
                        mazeprintx+=maxx*2;
                    mazeprinty=(totaly*15*2+0  +y*2 +maxy*2+4)%(maxy*2+4);
                    if (mazeprinty<0)
                        mazeprinty+=maxy*2;

                    if (  (Maze[mazeprintx][mazeprinty]) == ' ')
                        blokje=blokje | 8;
//                    else if (  (Maze[mazeprintx][mazeprinty]) == '#')
//                        blokje=blokje | (8+16);


/*
                    if (adapt_maze==1) {
                        mazeprintx=(-59+totalx*30+x -1 + plotx+(maxpicturex+1)*30 )%((maxpicturex+1)*30);
                        mazeprinty=(-30+totaly*15+y -1 + ploty+(maxpicturey+1)*15 )%((maxpicturey+1)*15);
                    } else {
                        mazeprintx=(totalx*30+x -1 + plotx+(maxpicturex+1)*30 )%((maxpicturex+1)*30);
                        mazeprinty=(totaly*15+y -1 + ploty+(maxpicturey+1)*15 )%((maxpicturey+1)*15);
                    }
*/

//                    mazeprintx=(totalx*30+x -1 + plotx+(maxpicturex+1)*30 )%((maxpicturex+1)*30);
//                    mazeprinty=(totaly*15+y -1 + ploty+(maxpicturey+1)*15 )%((maxpicturey+1)*15);
//hoppa

                    if (mazetype==1 && (combine==1 || force_game==1)) {
                        if ((blokje&16)==16)
                        {
                            blokje=blokje & (15+32+64);
                            if ((blokje&15)==1 || (blokje&15)==2 || (blokje&15)==4 || (blokje&15)==8) {
//hoihoi
//                                    if (!(rand()%10)) blokje=blokje|16;
                                    blokje=blokje|16;
                            }
                        }
                    }

                    if (mazeplotx>=0 && mazeploty>=0)
                    {
                        if ( (blokje&15)==15 && (blokje&(32+64))==0 && crossing>0 && combine==1) {
                            if (crossing==1) { blokje=blokje|32; crossing=2; }
                            else { blokje=blokje|64; crossing=1; }
                        }
                        maze_plot[ mazeplotx ][ mazeploty ]=blokje;
                    }

                    blokje=0;
                }
            }
        }
    }
    sprintf(line,"CONVERTING MAZE TO MAP BITMAP=%d/%d",yy+(xx-1)*totalpicturey,tot);
    blitter(line,1);
//turn
    if ((loaded_from_maze==0 || force_game==1) && mazetype!=0)
    {
        for (xx=0; xx<((maxpicturex+1)*30); xx++)
        {
            for (yy=0; yy<((maxpicturey+1)*15); yy++)
            {
                blokje=maze_plot[xx][yy];
                if (blokje==1 || blokje==2 || blokje==4 || blokje==8)
//hoihoi
                    blokje=blokje|16;
//                    if (!(rand()%10)) blokje=blokje|16;
                maze_plot[xx][yy]=blokje;

            }
        }
    }

}

void reversed_zetom()
{
    int totalx,totaly;
    int x,y;
    int blokje=0;
    int mazeprintx;
    int mazeprinty;
    int xx,yy;

    if (combine==0)
    {
        plotx=0;
        ploty=0;
    }

    int tot=mazesizey;
    int scount=100;
    for (y=0; y<=mazesizey; y++)
    {
        scount--;
        if (scount==0)
        {
            scount=1000;
            sprintf(line,"CLEANING MAZE LINE=%d/%d",y,tot);
            blitter(line,1);
        }

        for (x=0; x<=mazesizex; x++)
        {

            if (x==0 || y==0)
                Maze[x][y]='O';
            else
                Maze[x][y]='%';
        }
    }
    sprintf(line,"CLEANING MAZE LINE=%d/%d",y,tot);
    blitter(line,1);

    tot=totalpicturex*totalpicturey;
    scount=100;
    for (xx=0; xx<=maxpicturex; xx++)
    {
        for (yy=0; yy<=maxpicturey; yy++)
        {
            scount--;
            if (scount==0)
            {
                scount=1000;
                sprintf(line,"CONVERTING MAP TO MAZE BITMAP=%d/%d",yy+xx*totalpicturey,tot);
                blitter(line,1);
            }

            totalx=xx;
            if (totalx>maxpicturex)
                totalx=0;
            totaly=yy;
            if (totaly>maxpicturey)
                totaly=0;

            for (x=0; x<30; x++)
            {
                for (y=0; y<15; y++)
                {
                    mazeprintx=(totalx*30+x -1 + plotx + (maxpicturex+1)*30 )%((maxpicturex+1)*30);
                    mazeprinty=(totaly*15+y -1 + ploty + (maxpicturey+1)*15 )%((maxpicturey+1)*15);

                    blokje=maze_plot[ mazeprintx ][ mazeprinty ];

                    mazeprintx=(totalx*30*2+0  +x*2 -1)%((maxpicturex+1)*30*2);
                    if (mazeprintx<0)
                        mazeprintx+=(maxpicturex+1)*30*2;
                    mazeprinty=(totaly*15*2+0  +y*2 -1)%((maxpicturey+1)*15*2);
                    if (mazeprinty<0)
                        mazeprinty+=(maxpicturey+1)*15*2;

//crossing
                    if ((blokje&32)==32) {
                        Maze[mazeprintx+1][mazeprinty+1]='-';
                    }
                    else if ((blokje&64)==64) {
                        Maze[mazeprintx+1][mazeprinty+1]='|';
                    }
                    else if ((blokje&16)==16)
//                    if ((blokje&16)==16)
                    {
                        Maze[mazeprintx+1][mazeprinty+1]='*';
                    }
                    else if (blokje==0)
                    {
                        Maze[mazeprintx+1][mazeprinty+1]='#';
                    }
                    else
                    {
                        Maze[mazeprintx+1][mazeprinty+1]=' ';
                    }


                    mazeprintx=(totalx*30*2+0  +x*2 -1)%((maxpicturex+1)*30*2);
                    if (mazeprintx<0)
                        mazeprintx+=(maxpicturex+1)*30*2;
                    mazeprinty=(totaly*15*2+0-1+y*2 -1)%((maxpicturey+1)*15*2);
                    if (mazeprinty<0)
                        mazeprinty+=(maxpicturey+1)*15*2;

                    if ((blokje&1)==1)
                        Maze[mazeprintx+1][mazeprinty+1] = ' ';

                    mazeprintx=(totalx*30*2+0  +x*2 -1)%((maxpicturex+1)*30*2);
                    if (mazeprintx<0)
                        mazeprintx+=(maxpicturex+1)*30*2;
                    mazeprinty=(totaly*15*2+0+1+y*2 -1)%((maxpicturey+1)*15*2);
                    if (mazeprinty<0)
                        mazeprinty+=(maxpicturey+1)*15*2;

                    if ((blokje&2)==2)
                        Maze[mazeprintx+1][mazeprinty+1] = ' ';

                    mazeprintx=(totalx*30*2+0-1+x*2 -1)%((maxpicturex+1)*30*2);
                    if (mazeprintx<0)
                        mazeprintx+=(maxpicturex+1)*30*2;
                    mazeprinty=(totaly*15*2+0  +y*2 -1)%((maxpicturey+1)*15*2);
                    if (mazeprinty<0)
                        mazeprinty+=(maxpicturey+1)*15*2;

                    if ((blokje&4)==4)
                        Maze[mazeprintx+1][mazeprinty+1] = ' ';

                    mazeprintx=(totalx*30*2+0+1+x*2 -1)%((maxpicturex+1)*30*2);
                    if (mazeprintx<0)
                        mazeprintx+=(maxpicturex+1)*30*2;
                    mazeprinty=(totaly*15*2+0  +y*2 -1)%((maxpicturey+1)*15*2);
                    if (mazeprinty<0)
                        mazeprinty+=(maxpicturey+1)*15*2;

                    if ((blokje&8)==8)
                        Maze[mazeprintx+1][mazeprinty+1] = ' ';

                }
            }
        }
    }
    sprintf(line,"CONVERTING MAP TO MAZE BITMAP=%d/%d",yy+xx*totalpicturey,tot);
    blitter(line,1);
}

void save_maze(int lastmap)
{
    FILE* file;
    char naam[300];
//    char line[300000];
    int x,y;

    reversed_zetom();

    check_dir(BITMAPSX,BITMAPSY,lastmap);
//    sprintf(naam,"levels/%dx%d/%03d/maze.dat",BITMAPSX,BITMAPSY,lastmap);
    sprintf(naam,"%s/%dx%d/%03d/maze.dat",LEVELDIR,BITMAPSX,BITMAPSY,lastmap);
    file = fopen (naam, "w");

    if (file==NULL)
    {
        savedata((char*)"Error saving maze file(reversed_zetom()):",0);
        savedata(naam,0);
        return;
    }

    for (y=0; y<=mazesizey; y++)
    {
        if (Maze[mazesizex][y]==' ')
            Maze[0][y]=' ';
    }
    for (x=0; x<=mazesizex; x++)
    {
        if (Maze[x][mazesizey]==' ')
            Maze[x][0]=' ';
    }
    int tot=mazesizey;
    int scount=100;
    for (y=0; y<=mazesizey; y++)
    {
        scount--;
        if (scount==0)
        {
            scount=100;
            sprintf(line,"SAVING MAZE %s LINE=%d/%d\n", naam,y,tot);
            blitter(line,1);
        }

        for (x=0; x<=mazesizex; x++)
        {
            line[x]=Maze[x][y];
        }
        line[x]='\0';
        fprintf(file, "%s\n",line);
    }
    sprintf(line,"SAVING MAZE %s LINE=%d/%d\n", naam,y,tot);
    blitter(line,1);
    if (combine==0)
        fprintf(file,"X=%d,Y=%d\n",(picturex*1920-posx),(picturey*1080-posy));
    else
    {
        fprintf(file,"X=%d,Y=%d\n",2912,1656);
        combine=0;
    }

    if (lastmap==0)
        fprintf(file,"POINTSLEFT=%d\n",total_points);
    if (lastmap==0)
        fprintf(file,"POINTS=%d\n",local_points);
    fprintf(file,"POSITION1X=%d\n",position1x);
    fprintf(file,"POSITION1Y=%d\n",position1y);
    fprintf(file,"POSITION2X=%d\n",position2x);
    fprintf(file,"POSITION2Y=%d\n",position2y);
    fprintf(file,"MAZESTART1X=%d\n",movex1);
    fprintf(file,"MAZESTART1Y=%d\n",movey1);
    fprintf(file,"MAZESTART2X=%d\n",movex2);
    fprintf(file,"MAZESTART2Y=%d\n",movey2);

    if (connected==1)
    {
        if (client==1)
            fprintf(file,"REMOTE,X=%d,Y=%d\n",(picturex*1920-posx),(picturey*1080-posy));
        else
            fprintf(file,"REMOTE,X=%d,Y=%d\n",remote_posx,remote_posy);
    }
    fprintf(file,"MAZE=%d\n",mazetype);
    fprintf(file,"HEIGHT=%d\n",breed);
    fprintf(file,"WIDTH=%d\n",hoog);
    fprintf(file,"SEED=%d\n",SEED);
    fprintf(file,"BACKGROUND=%d,%d,%d,%d\n",background_color[0].r,background_color[0].g,background_color[0].b,background_color[0].a);
    fprintf(file,"BACKGROUND_MAZE=%d,%d,%d,%d\n",background_color[1].r,background_color[1].g,background_color[1].b,background_color[1].a);
    fprintf(file,"TRANSPARANT=%d\n",set_transparant);

    fclose (file);

    strcpy(error_msg,"SAVED: ");
    strcat(error_msg,naam);
    error_flag=1;
}

void load_maze(int lastmap)
{
    int totalx,totaly;
    int x,y;
    int blokje=0;
    int mazeprintx;
    int mazeprinty;
    int xx,yy;

    FILE* file;
    char naam[200];

//    sprintf(naam,"levels/%dx%d/%03d/maze.dat",BITMAPSX,BITMAPSY,lastmap);
    sprintf(naam,"%s/%dx%d/%03d/maze.dat",LEVELDIR,BITMAPSX,BITMAPSY,lastmap);

    file = fopen (naam, "r");

    if (file==NULL)
    {
        strcpy(error_msg,"FILE NOT FOUND: ");
        strcat(error_msg,naam);
        error_flag=1;
        return;
    }
    int tot=mazesizey;
    int scount=100;
    int min_size;
//    if (mazesizex<2050*30*2) min_size=2050*30*2;
//    else min_size=mazesizex*2+100;
    min_size=mazesizex*2+100;
    sprintf(line,"LOADING MAZE %s LINE=%d/%d", naam,0,tot);
    blitter(line,1);
    for (y=0; y<=mazesizey; y++)
    {

        int numchars;
        scount--;
        if (scount==0)
        {
            scount=100;
            sprintf(line,"LOADING MAZE %s LINE=%d/%d", naam,y,tot);
            blitter(line,1);
        }

//        printf("y=%d\n",y);
//        getchar();
        if( fgets (line,min_size, file)!=NULL )
        {
//            printf("strlen(line)=%d\n",strlen(line));
//            getchar();
            if (combine==1 && line[0]=='X') {
                fclose (file);
                return;
            } else {
                if (strlen(line)>0)
                    line[strlen(line) - 1] = '\0';
                numchars=strlen(line);
                if (numchars>mazesizex)
                    numchars=mazesizex;
            }
        }
        else
        {
            savedata((char*)"error reading maze file:",0);
            savedata((char*)"line:",y+1);
            savedata(naam,0);
            fclose (file);
            return;
        }

        for (x=0; x<=numchars; x++)
        {
//            if ((line[x]==' ') || (line[x]=='O') || (line[x]=='#') || (line[x]=='*'))
//            {
//                Maze[x][y]=line[x];
//            }
//            else
                Maze[x][y]=line[x];
        }
    }

    sprintf(line,"LOADING MAZE %s LINE=%d/%d", naam,y,tot);
    blitter(line,1);

    if (combine==1) {
            fclose(file);
            return;
    }
    int numread;
    if (combine==0)
    {
        if( fgets (line,min_size, file)!=NULL )
        {
            numread=sscanf(line,"X=%d,Y=%d",&x,&y);
            if (numread>=0)
            {
                picturex=x/1920;
                posx=x-1920*picturex;
                picturey=y/1080;
                posy=y-1080*picturey;
                posx=-posx;
                posy=-posy;
                fposx=posx;
                fposy=posy;
//				start_posx=x;
//				start_posy=y;
                start_posx=(picturex*1920-posx);
                start_posy=(picturey*1080-posy);
            }
        }
    } else {
        fclose(file);
        return;
    }

    char var[100];
    if (lastmap==0) skipcount=1;
    while (fgets (line,min_size, file)!=NULL )
    {
        sscanf(line,"%[^=]",var);

        if (strcmp(var,"SEED")==0)              sscanf(line,"SEED=%d",                      &LOADED_SEED);
        if (strcmp(var,"MAZE")==0)              sscanf(line,"MAZE=%d",                      &mazetype);
        if (strcmp(var,"POINTSLEFT")==0)        sscanf(line,"POINTSLEFT=%d",                &total_points);
        if (strcmp(var,"POINTS")==0)            sscanf(line,"POINTS=%d",                    &local_points);
        if (strcmp(var,"POSITION1X")==0)        sscanf(line,"POSITION1X=%d",                &position1x);
        if (strcmp(var,"POSITION1Y")==0)        sscanf(line,"POSITION1Y=%d",                &position1y);
        if (strcmp(var,"POSITION2X")==0)        sscanf(line,"POSITION2X=%d",                &position2x);
        if (strcmp(var,"POSITION2Y")==0)        sscanf(line,"POSITION2Y=%d",                &position2y);
        if (strcmp(var,"WIDTH")==0)             sscanf(line,"WIDTH=%d",                     &hoog);
        if (strcmp(var,"HEIGHT")==0)            sscanf(line,"HEIGHT=%d",                    &breed);
        if (strcmp(var,"BACKGROUND=")==0)       sscanf(line,"BACKGROUND=%d,%d,%d,%d",       &background_color[0].r,&background_color[0].g,&background_color[0].b,&background_color[0].a);
        if (strcmp(var,"BACKGROUND_MAZE")==0)   sscanf(line,"BACKGROUND_MAZE=%d,%d,%d,%d",  &background_color[1].r,&background_color[1].g,&background_color[1].b,&background_color[1].a);
        if (strcmp(var,"TRANSPARANT")==0)       sscanf(line,"TRANSPARANT=%d",               &set_transparant);

        if (combine==0)
        {
            if (strcmp(var,"REMOTE,X")==0)
            {
                if (connected==1 && client==1 && lastmap!=0)
                {
                    numread=sscanf(line,"REMOTE,X=%d,Y=%d",&x,&y);
                    if (numread>=0)
                    {
                        picturex=x/1920;
                        posx=x-1920*picturex;
                        picturey=y/1080;
                        posy=y-1080*picturey;
                        posx=-posx;
                        posy=-posy;
                        fposx=posx;
                        fposy=posy;
//						start_posx=x;
//						start_posy=y;
                        start_posx=(picturex*1920-posx);
                        start_posy=(picturey*1080-posy);

                    }
                }
            }
        }
    }
    fclose (file);
    strcpy(error_msg,"LOADED: ");
    strcat(error_msg,naam);
    error_flag=1;
}

void remote_plot(int mazemovex, int mazemovey, int blokje, int remote_pen_mode)
{
    int posx;
    int posy;
    int picturex;
    int picturey;

    remote_posx=((mazemovex+45)%(30*(maxpicturex+1)))*64;
    remote_posy=((mazemovey+23)%(15*(maxpicturey+1)))*72;
    remote_posx=(remote_posx+32)%((totalpicturex)*1920);

    picturex=remote_posx/1920;
    posx=remote_posx-1920*picturex;

    picturey=remote_posy/1080;
    posy=remote_posy-1080*picturey;

    posx=-posx;
    posy=-posy;

    xdraw=(-posx+960);
    if (xdraw>=1920)
    {
        xdraw=xdraw-1920;
        mapx=1;
    }
    else
        mapx=0;
    ydraw=(-posy+540);
    if (ydraw>=1080)
    {
        ydraw=ydraw-1080;
        mapy=1;
    }
    else
        mapy=0;

    ReadBitmaps2_remote(picturex, picturey);

    int arx=(picturex+mapx)%(maxpicturex+1);
    int ary=(picturey+mapy)%(maxpicturey+1);
    int blokje_old=maze_plot[mazemovex][mazemovey];

    maze_plot[mazemovex][mazemovey]=blokje;

    if ((blokje&16)==16)
    {
        if ((blokje&32)==32) {
            RenderBlit_adapt(arx,ary, xdraw-32, ydraw-36, 64, 72, (3)*64, 13*72, 1);
            RenderBlit_adapt(arx,ary, xdraw-32, ydraw-36, 64, 72, (12)*64, 13*72, 0);
        } else if ((blokje&64)==64) {
            RenderBlit_adapt(arx,ary, xdraw-32, ydraw-36, 64, 72, (12)*64, 13*72, 1);
            RenderBlit_adapt(arx,ary, xdraw-32, ydraw-36, 64, 72, (3)*64, 13*72, 0);
        } else
            RenderBlit_adapt(arx,ary, xdraw-32, ydraw-36, 64, 72, (blokje&15)*64, 13*72, 1);
    }
    else
    {
        if ((blokje&32)==32) {
            RenderBlit_adapt(arx,ary, xdraw-32, ydraw-36, 64, 72, (3)*64, 13*72, 1);
            RenderBlit_adapt(arx,ary, xdraw-32, ydraw-36, 64, 72, (12)*64, 13*72, 0);
        } else if ((blokje&64)==64) {
            RenderBlit_adapt(arx,ary, xdraw-32, ydraw-36, 64, 72, (12)*64, 13*72, 1);
            RenderBlit_adapt(arx,ary, xdraw-32, ydraw-36, 64, 72, (3)*64, 13*72, 0);
        } else
            RenderBlit_adapt(arx,ary, xdraw-32, ydraw-36, 64, 72, (blokje&15)*64, 13*72, 1);
    }
    if (mirror>=1) {
        int old_pen_mode=pen_mode;
        pen_mode=remote_pen_mode;
        if (remote_pen_mode==1) {
            blokje=blokje_old-blokje;
        }
        do_mirror(mazemovex,mazemovey,blokje);
        pen_mode=old_pen_mode;
    }
}


void remote_point(int remote_posx,int remote_posy)
{
    int posx;
    int posy;
    int picturex;
    int picturey;
    static int remote_posx_old=0,remote_posy_old=0;
    int speedx=0,speedy=0;

    if (remote_posx!=remote_posx_old) speedx=1;
    else if (remote_posy!=remote_posy_old) speedy=1;
    remote_posx_old=remote_posx;
    remote_posy_old=remote_posy;

    picturex=remote_posx/1920;
    posx=remote_posx-1920*picturex;

    picturey=remote_posy/1080;
    posy=remote_posy-1080*picturey;

    posx=-posx;
    posy=-posy;

    if ( (  ((posx+32)%32)==0) && ((posy%36)==0)  )
    {
        COLORREF color;

        xdraw=(-posx+960);
        if (xdraw>=1920)
        {
            xdraw=xdraw-1920;
            mapx=1;
        }
        else
            mapx=0;
        ydraw=(-posy+540);
        if (ydraw>=1080)
        {
            ydraw=ydraw-1080;
            mapy=1;
        }
        else
            mapy=0;

        ReadBitmaps2_remote(picturex, picturey);

        int arx=(picturex+mapx)%(maxpicturex+1);
        int ary=(picturey+mapy)%(maxpicturey+1);

        sprite_point.setTexture(texturemaxinmempoint[used2[arx][ary]]->getTexture(),false);
        sprite_point.setTextureRect(   { xdraw, ydraw,1, 1 }  );
        sprite_point.setPosition(0,0);
        texture_point.draw(sprite_point);
        texture_point.display();
        image_point=texture_point.getTexture().copyToImage();
        pixel_color=image_point.getPixel(0,0);
        color=(pixel_color.toInteger())>>8;

        static int last_posx;
        static int last_posy;

        mazemovex=(picturex*1920-posx-32)/64;
        mazemovey=(picturey*1080-posy   )/72;
        mazemovex=(mazemovex-45+60*(maxpicturex+1))%(30*(maxpicturex+1));
        mazemovey=(mazemovey-23+30*(maxpicturey+1))%(15*(maxpicturey+1));

        int blokje=maze_plot[mazemovex][mazemovey];
//crossing
        int go_on=0;
        if ( (blokje&(32+64))>0 ) {
            if (speedx!=0 && (blokje&32)==32 || ((posx-32)%64!=0)) go_on=1;
            else if (speedy!=0 && (blokje&64)==64 || ((posy)%72!=0) ) go_on=1;
        } else go_on=1;

        if ( (color==16773632 && SFML==1) && go_on==1)
        {
            total_points--;
            remote_points++;
            if (fhapper2==0)
            {
                soundloop=soundloop|16;
                playsound=playsound|16;
            }
            fhapper2=40.0/fspeed_adjust;

            if ((blokje&16)==16 ) {
                if ((xdraw-9)<0)
                    RenderBlit_total(picturex,ary, 1920+xdraw-9, ydraw-8, 18, 16, 0, 5*72, 0);
                if ((ydraw-8)<0)
                    RenderBlit_total(arx,picturey,  xdraw-9, 1080+ydraw-8, 18, 16, 0, 5*72,0);
                RenderBlit_total(arx,ary,  xdraw-9, ydraw-8, 18, 16, 0, 5*72,0);
            } else {
                if ((xdraw-7)<0)
                    RenderBlit_total(picturex,ary, 1920+xdraw-7, ydraw-6, 14, 12, 0, 5*72, 0);
                if ((ydraw-6)<0)
                    RenderBlit_total(arx,picturey,  xdraw-7, 1080+ydraw-6, 14, 12, 0, 5*72,0);
                RenderBlit_total(arx,ary,  xdraw-7, ydraw-6, 14, 12, 0, 5*72,0);
            }

            if ( ((posx-32)%64==0) && ( (posy)%72==0) )
            {

                if ((blokje&16)==16)
                {
                    blokje=blokje & 15;
                    if (blokje==1 || blokje==2 || blokje==4 || blokje==8)
                    {
                    }
                }
                if ((maze_plot[mazemovex][mazemovey]&16)==16)
                {

                    if (hunt==1||hunt==2)
                    {
                        hunt=1;
                        hunt_max=800;
                        if (hunt_counter!=800)
                            hunt_counter=799;
                    }
                    else
                    {
                        hunt=1;
                        hunt_max=800;
                        hunt_counter=800;
                    }

                    playsound=playsound|32;
                }
            }
        }
        else
        {
            if (last_posx!=posx || last_posy!=posy)
            {
                if (fhapper2>0.0)
                {
                    fhapper2=1.0;
                }
            }
        }
        last_posx=posx;
        last_posy=posy;
    }
}

extern int	move_remote_posx;
extern int	move_remote_posy;


void goto_pos_remote()
{
    picturex=move_remote_posx/1920;
    posx=move_remote_posx-1920*picturex;

    picturey=move_remote_posy/1080;
    posy=move_remote_posy-1080*picturey;

    posx=-posx;
    posy=-posy;
    fposx=posx;
    fposy=posy;

    plotx=(picturex*1920-posx-32)/64;
    ploty=(picturey*1080-posy   )/72;
    plotx=(plotx-45+60*(maxpicturex+1) )%(30*(maxpicturex+1));
    ploty=(ploty-23+30*(maxpicturey+1) )%(15*(maxpicturey+1));

//	ReadBitmaps2_remote(picturex, picturey);

    sprintf(writer,"T=GOTO,X=%d,Y=%d,\0",plotx,ploty);
    SEND(writer);

    ReadBitmaps2();
}

void goto_plot(int mazemovex, int mazemovey)
{
    int posx;
    int posy;
    int picturex;
    int picturey;

    remote_posx=((mazemovex+45)%(30*(maxpicturex+1)))*64;
    remote_posy=((mazemovey+23)%(15*(maxpicturey+1)))*72;
    remote_posx=(remote_posx+32)%((totalpicturex)*1920);

    picturex=remote_posx/1920;
    posx=remote_posx-1920*picturex;

    picturey=remote_posy/1080;
    posy=remote_posy-1080*picturey;

    posx=-posx;
    posy=-posy;

    ReadBitmaps2_remote(picturex, picturey);
}

void goto_maze(int mazemovex, int mazemovey)
{
    int remote_posx=((mazemovex+45+maze_plotsizex)%(maze_plotsizex))*64;
    int remote_posy=((mazemovey+23+maze_plotsizey)%(maze_plotsizey))*72;
    remote_posx=(remote_posx+32)%((totalpicturex)*1920);

    picturex=remote_posx/1920;
    posx=remote_posx-1920*picturex;

    picturey=remote_posy/1080;
    posy=remote_posy-1080*picturey;

    posx=-posx;
    posy=-posy;
    fposx=posx;
    fposy=posy;

    ReadBitmaps2();
}

void do_mirror_sub(int mazemovex, int mazemovey)
{
    int posx;
    int posy;
    int picturex;
    int picturey;
    int remote_posx;
    int remote_posy;
    int xdraw,ydraw,mapx,mapy;

    remote_posx=((mazemovex+45)%(30*(maxpicturex+1)))*64;
    remote_posy=((mazemovey+23)%(15*(maxpicturey+1)))*72;
    remote_posx=(remote_posx+32)%((totalpicturex)*1920);

    picturex=remote_posx/1920;
    posx=remote_posx-1920*picturex;

    picturey=remote_posy/1080;
    posy=remote_posy-1080*picturey;

    posx=-posx;
    posy=-posy;

    xdraw=(-posx+960);
    if (xdraw>=1920)
    {
        xdraw=xdraw-1920;
        mapx=1;
    }
    else
        mapx=0;
    ydraw=(-posy+540);
    if (ydraw>=1080)
    {
        ydraw=ydraw-1080;
        mapy=1;
    }
    else
        mapy=0;

    int arx=(picturex+mapx)%(maxpicturex+1);
    int ary=(picturey+mapy)%(maxpicturey+1);

    int blokje=maze_plot[mazemovex][mazemovey];

//crossing
    if (used[arx][ary]==1)
    {
        if ((blokje&16)==16)
        {
            if ((blokje&32)==32) {
                RenderBlit_total(arx,ary, xdraw-32, ydraw-36, 64, 72, (3)*64, 9*72, pen_mode);
                RenderBlit_total(arx,ary, xdraw-32, ydraw-36, 64, 72, (12)*64, 9*72, pen_mode);
            } else if ((blokje&64)==64) {
                RenderBlit_total(arx,ary, xdraw-32, ydraw-36, 64, 72, (12)*64, 9*72, pen_mode);
                RenderBlit_total(arx,ary, xdraw-32, ydraw-36, 64, 72, (3)*64, 9*72, pen_mode);
            } else
                RenderBlit_total(arx,ary, xdraw-32, ydraw-36, 64, 72, (blokje&15)*64, 9*72, pen_mode);
        }
        else
        {
            if ((blokje&32)==32) {
                RenderBlit_total(arx,ary, xdraw-32, ydraw-36, 64, 72, (3)*64, 0, pen_mode);
                RenderBlit_total(arx,ary, xdraw-32, ydraw-36, 64, 72, (12)*64, 0, pen_mode);
            } else if ((blokje&64)==64) {
                RenderBlit_total(arx,ary, xdraw-32, ydraw-36, 64, 72, (12)*64, 0, pen_mode);
                RenderBlit_total(arx,ary, xdraw-32, ydraw-36, 64, 72, (3)*64, 0, pen_mode);
            } else
                RenderBlit_total(arx,ary, xdraw-32, ydraw-36, 64, 72, (blokje&15)*64, 0, pen_mode);
        }
    }
}


void do_mirror(int mazemovex,int mazemovey,int blokje) {
    int mazemovex_mirror;
    int mazemovey_mirror;
    int blokje_mirror;

    mazemovex=(mazemovex+maze_plotsizex)%maze_plotsizex;
    mazemovey=(mazemovey+maze_plotsizey)%maze_plotsizey;
    blokje_mirror=maze_plot[mazemovex][mazemovey];
    if ((blokje_mirror&15)==15 && crossing>0) {
            if (crossing==1) blokje_mirror=(blokje_mirror|32)&(255-64);
            else if (crossing==2) blokje_mirror=(blokje_mirror|64)&(255-32);
    }
    else if ((blokje_mirror&15)!=15) {
            blokje_mirror=blokje_mirror&(255-64-32);
    }
    maze_plot[mazemovex][mazemovey]=blokje_mirror;
    do_mirror_sub(mazemovex,mazemovey);

    if (mirror==0) return;

    if ((maze_plot[mazemovex][mazemovey]&16)==16) blokje=blokje|16; else blokje=blokje&15;

    if (mirror==3 || mirror==5 || mirror==6) {

        mazemovex_mirror=BITMAPSX*30-mazemovex; mazemovex_mirror=(mazemovex_mirror+BITMAPSX*30)%(BITMAPSX*30);
        mazemovey_mirror=mazemovey; mazemovey_mirror=(mazemovey_mirror+BITMAPSY*15)%(BITMAPSY*15);
        blokje_mirror=maze_plot[mazemovex_mirror][mazemovey_mirror];
        if ((blokje&16)==16) blokje_mirror=blokje_mirror|16; else blokje_mirror=blokje_mirror&15;
        if (pen_mode==0) {
            if ((blokje&1)==1) blokje_mirror=blokje_mirror|1;
            if ((blokje&2)==2) blokje_mirror=blokje_mirror|2;
            if ((blokje&4)==4) blokje_mirror=blokje_mirror|8;
            if ((blokje&8)==8) blokje_mirror=blokje_mirror|4;
            if ((blokje_mirror&15)==15 && crossing>0) {
                    if (crossing==1) blokje_mirror=(blokje_mirror|32)&(255-64);
                    else if (crossing==2) blokje_mirror=(blokje_mirror|64)&(255-32);

            }
        } else if (pen_mode==1) {
            if ((blokje&1)==1) blokje_mirror=blokje_mirror&(31-1);
            if ((blokje&2)==2) blokje_mirror=blokje_mirror&(31-2);
            if ((blokje&4)==4) blokje_mirror=blokje_mirror&(31-8);
            if ((blokje&8)==8) blokje_mirror=blokje_mirror&(31-4);
            if ((blokje_mirror&15)!=15) {
                    blokje_mirror=blokje_mirror&(255-64-32);
            }
        }
        maze_plot[mazemovex_mirror][mazemovey_mirror]=blokje_mirror;
        do_mirror_sub(mazemovex_mirror,mazemovey_mirror);
    }

    if (mirror==4 || mirror==5 || mirror==6) {
        mazemovex_mirror=mazemovex; mazemovex_mirror=(mazemovex_mirror+BITMAPSX*30)%(BITMAPSX*30);
        mazemovey_mirror=BITMAPSY*15-mazemovey; mazemovey_mirror=(mazemovey_mirror+BITMAPSY*15)%(BITMAPSY*15);
        blokje_mirror=maze_plot[mazemovex_mirror][mazemovey_mirror];
        if ((blokje&16)==16) blokje_mirror=blokje_mirror|16; else blokje_mirror=blokje_mirror&15;
        if (pen_mode==0) {
            if ((blokje&1)==1) blokje_mirror=blokje_mirror|2;
            if ((blokje&2)==2) blokje_mirror=blokje_mirror|1;
            if ((blokje&4)==4) blokje_mirror=blokje_mirror|4;
            if ((blokje&8)==8) blokje_mirror=blokje_mirror|8;
            if ((blokje_mirror&15)==15 && crossing>0) {
                    if (crossing==1) blokje_mirror=(blokje_mirror|32)&(255-64);
                    else if (crossing==2) blokje_mirror=(blokje_mirror|64)&(255-32);

            }
        } else if (pen_mode==1) {
            if ((blokje&1)==1) blokje_mirror=blokje_mirror&(31-2);
            if ((blokje&2)==2) blokje_mirror=blokje_mirror&(31-1);
            if ((blokje&4)==4) blokje_mirror=blokje_mirror&(31-4);
            if ((blokje&8)==8) blokje_mirror=blokje_mirror&(31-8);
            if ((blokje_mirror&15)!=15) {
                    blokje_mirror=blokje_mirror&(255-64-32);
            }
        }
        maze_plot[mazemovex_mirror][mazemovey_mirror]=blokje_mirror;
        do_mirror_sub(mazemovex_mirror,mazemovey_mirror);
    }

    if (mirror==5 ) {
        mazemovex_mirror=BITMAPSX*30-mazemovex; mazemovex_mirror=(mazemovex_mirror+BITMAPSX*30)%(BITMAPSX*30);
        mazemovey_mirror=BITMAPSY*15-mazemovey; mazemovey_mirror=(mazemovey_mirror+BITMAPSY*15)%(BITMAPSY*15);
        blokje_mirror=maze_plot[mazemovex_mirror][mazemovey_mirror];
        if ((blokje&16)==16) blokje_mirror=blokje_mirror|16; else blokje_mirror=blokje_mirror&15;
        if (pen_mode==0) {
            if ((blokje&1)==1) blokje_mirror=blokje_mirror|2;
            if ((blokje&2)==2) blokje_mirror=blokje_mirror|1;
            if ((blokje&4)==4) blokje_mirror=blokje_mirror|8;
            if ((blokje&8)==8) blokje_mirror=blokje_mirror|4;
            if ((blokje_mirror&15)==15 && crossing>0) {
                    if (crossing==1) blokje_mirror=(blokje_mirror|32)&(255-64);
                    else if (crossing==2) blokje_mirror=(blokje_mirror|64)&(255-32);
            }
        } else if (pen_mode==1) {
            if ((blokje&1)==1) blokje_mirror=blokje_mirror&(31-2);
            if ((blokje&2)==2) blokje_mirror=blokje_mirror&(31-1);
            if ((blokje&4)==4) blokje_mirror=blokje_mirror&(31-8);
            if ((blokje&8)==8) blokje_mirror=blokje_mirror&(31-4);
            if ((blokje_mirror&15)!=15) {
                    blokje_mirror=blokje_mirror&(255-64-32);
            }
        }
        maze_plot[mazemovex_mirror][mazemovey_mirror]=blokje_mirror;
        do_mirror_sub(mazemovex_mirror,mazemovey_mirror);
    }

    if (mirror==1 || mirror==2 || mirror==6) {

        mazemovex_mirror=BITMAPSX*30-mazemovex; mazemovex_mirror=(mazemovex_mirror+BITMAPSX*60)%(BITMAPSX*30);
        mazemovey_mirror=BITMAPSY*15-mazemovey; mazemovey_mirror=(mazemovey_mirror+BITMAPSY*30)%(BITMAPSY*15);
        blokje_mirror=maze_plot[mazemovex_mirror][mazemovey_mirror];
        if ((blokje&16)==16) blokje_mirror=blokje_mirror|16; else blokje_mirror=blokje_mirror&15;
        if (pen_mode==0) {
            if ((blokje&1)==1) blokje_mirror=blokje_mirror|2;
            if ((blokje&2)==2) blokje_mirror=blokje_mirror|1;
            if ((blokje&4)==4) blokje_mirror=blokje_mirror|8;
            if ((blokje&8)==8) blokje_mirror=blokje_mirror|4;
            if ((blokje_mirror&15)==15 && crossing>0) {
                    if (crossing==1) blokje_mirror=(blokje_mirror|32)&(255-64);
                    else if (crossing==2) blokje_mirror=(blokje_mirror|64)&(255-32);
            }
        } else if (pen_mode==1) {
            if ((blokje&1)==1) blokje_mirror=blokje_mirror&(31-2);
            if ((blokje&2)==2) blokje_mirror=blokje_mirror&(31-1);
            if ((blokje&4)==4) blokje_mirror=blokje_mirror&(31-8);
            if ((blokje&8)==8) blokje_mirror=blokje_mirror&(31-4);
            if ((blokje_mirror&15)!=15) {
                    blokje_mirror=blokje_mirror&(255-64-32);
            }
        }
        maze_plot[mazemovex_mirror][mazemovey_mirror]=blokje_mirror;
        do_mirror_sub(mazemovex_mirror,mazemovey_mirror);
    }

    if (mirror==2) return;

    int mazemovex_new;
    int mazemovey_new;
    int mazemovex_new1;
    int mazemovey_new1;

    if (mirror==1 || mirror==6) {
        if (mazemovex>(BITMAPSX*30/2)) {mazemovex_new=BITMAPSX*30-mazemovex; mazemovey_new1=BITMAPSY*15-mazemovex_new; } else mazemovey_new1=mazemovex;
        if (mazemovey>(BITMAPSY*15/2)) {mazemovey_new=BITMAPSY*15-mazemovey; mazemovex_new1=BITMAPSX*30-mazemovey_new; } else mazemovex_new1=mazemovey;

        mazemovex=mazemovex_new1;
        mazemovey=mazemovey_new1;

        mazemovex_mirror=BITMAPSX*30-mazemovex; mazemovex_mirror=(mazemovex_mirror+BITMAPSX*60)%(BITMAPSX*30);
        mazemovey_mirror=mazemovey; mazemovey_mirror=(mazemovey_mirror+BITMAPSY*30)%(BITMAPSY*15);
        blokje_mirror=maze_plot[mazemovex_mirror][mazemovey_mirror];
        if ((blokje&16)==16) blokje_mirror=blokje_mirror|16; else blokje_mirror=blokje_mirror&15;
        if (pen_mode==0) {
            if ((blokje&1)==1) blokje_mirror=blokje_mirror|8;
            if ((blokje&2)==2) blokje_mirror=blokje_mirror|4;
            if ((blokje&4)==4) blokje_mirror=blokje_mirror|1;
            if ((blokje&8)==8) blokje_mirror=blokje_mirror|2;
            if ((blokje_mirror&15)==15 && crossing>0) {
                    if (crossing==2) blokje_mirror=(blokje_mirror|32)&(255-64);
                    else if (crossing==1) blokje_mirror=(blokje_mirror|64)&(255-32);

            }
        } else if (pen_mode==1) {
            if ((blokje&1)==1) blokje_mirror=blokje_mirror&(31-8);
            if ((blokje&2)==2) blokje_mirror=blokje_mirror&(31-4);
            if ((blokje&4)==4) blokje_mirror=blokje_mirror&(31-1);
            if ((blokje&8)==8) blokje_mirror=blokje_mirror&(31-2);
            if ((blokje_mirror&15)!=15) {
                    blokje_mirror=blokje_mirror&(255-64-32);
            }
        }

        maze_plot[mazemovex_mirror][mazemovey_mirror]=blokje_mirror;
        do_mirror_sub(mazemovex_mirror,mazemovey_mirror);

        mazemovex_mirror=mazemovex; mazemovex_mirror=(mazemovex_mirror+BITMAPSX*60)%(BITMAPSX*30);
        mazemovey_mirror=BITMAPSY*15-mazemovey; mazemovey_mirror=(mazemovey_mirror+BITMAPSY*30)%(BITMAPSY*15);
        blokje_mirror=maze_plot[mazemovex_mirror][mazemovey_mirror];
        if ((blokje&16)==16) blokje_mirror=blokje_mirror|16; else blokje_mirror=blokje_mirror&15;
        if (pen_mode==0) {
            if ((blokje&1)==1) blokje_mirror=blokje_mirror|4;
            if ((blokje&2)==2) blokje_mirror=blokje_mirror|8;
            if ((blokje&4)==4) blokje_mirror=blokje_mirror|2;
            if ((blokje&8)==8) blokje_mirror=blokje_mirror|1;
            if ((blokje_mirror&15)==15 && crossing>0) {
                    if (crossing==2) blokje_mirror=(blokje_mirror|32)&(255-64);
                    else if (crossing==1) blokje_mirror=(blokje_mirror|64)&(255-32);

            }
        } else if (pen_mode==1) {
            if ((blokje&1)==1) blokje_mirror=blokje_mirror&(31-4);
            if ((blokje&2)==2) blokje_mirror=blokje_mirror&(31-8);
            if ((blokje&4)==4) blokje_mirror=blokje_mirror&(31-2);
            if ((blokje&8)==8) blokje_mirror=blokje_mirror&(31-1);
            if ((blokje_mirror&15)!=15) {
                    blokje_mirror=blokje_mirror&(255-64-32);
            }
        }
        maze_plot[mazemovex_mirror][mazemovey_mirror]=blokje_mirror;
        do_mirror_sub(mazemovex_mirror,mazemovey_mirror);
    }
}

extern char SAS_URL[];
extern char SAS_ORDER[];
extern char SAS_EXTENSION[];
extern int SAS_ZOOM_DIRECTION;

void save_mazeoff()
{
    FILE* file;
    char naam[200];
    int x,y;

    check_dir(BITMAPSX,BITMAPSY,level);
//    sprintf(naam,"levels/%dx%d/%03d/mazeoff.dat",BITMAPSX,BITMAPSY,level);
    sprintf(naam,"%s/%dx%d/%03d/mazeoff_var.dat",LEVELDIR,BITMAPSX,BITMAPSY,level);
    file = fopen (naam, "w");

    if (file==NULL)
    {
        savedata((char*)"Error saving file: ",0);
        savedata(naam,0);
        return;
    }

    fprintf(file,"X=%d,Y=%d\n",(picturex*1920-posx),(picturey*1080-posy));
    fprintf(file,"POSITION1X=%d\n",position1x);
    fprintf(file,"POSITION1Y=%d\n",position1y);
    fprintf(file,"POSITION2X=%d\n",position2x);
    fprintf(file,"POSITION2Y=%d\n",position2y);
    fprintf(file,"SAS_ZOOM_DIRECTION=%d\n",SAS_ZOOM_DIRECTION);
    fprintf(file,"SAS_URL=\"%s\"\n",SAS_URL);
    fprintf(file,"SAS_ORDER=\"%s\"\n",SAS_ORDER);
    fprintf(file,"SAS_EXTENSION=\"%s\"\n",SAS_EXTENSION);
    fclose (file);

    sprintf(naam,"%s/%dx%d/%03d/mazeoff.dat",LEVELDIR,BITMAPSX,BITMAPSY,level);

//    if (file_exists(naam)) return;

    file = fopen (naam, "w");

    if (file==NULL)
    {
        savedata((char*)"Error saving file: ",0);
        savedata(naam,0);
        return;
    }

    fprintf(file,"SAS_STARTX=%d\n",SAS_STARTX);
    fprintf(file,"SAS_STARTY=%d\n",SAS_STARTY);
    fprintf(file,"SAS_ZOOM=%d\n",SAS_ZOOM);

    fclose (file);
}

int read_mazeoff(int nopos) {
    FILE* file;
    char naam[200];
    int x,y;

    sprintf(naam,"%s/%dx%d/%03d/mazeoff.dat",LEVELDIR,BITMAPSX,BITMAPSY,level);
    file = fopen (naam, "r");
    if (file==NULL)
    {
        strcpy(error_msg,"FILE NOT FOUND: ");
        strcat(error_msg,naam);
        error_flag=1;
        return 0;
    }

    char var[100];
    while (fgets (line,mazesizex*2+100, file)!=NULL )
    {
        sscanf(line,"%[^=]",var);
        if (nopos==0) {
            if (strcmp(var,"X")==0)
            {
                sscanf(line,"X=%d,Y=%d",&x,&y);
                picturex=x/1920;
                posx=x-1920*picturex;
                picturey=y/1080;
                posy=y-1080*picturey;
                posx=-posx;
                posy=-posy;
                fposx=posx;
                fposy=posy;
                start_posx=(picturex*1920-posx);
                start_posy=(picturey*1080-posy);
            }
        }
        if (strcmp(var,"MAZESTART1X")==0)
        {
                sscanf(line,"MAZESTART1X=%d",&movex1);
        }
        if (strcmp(var,"MAZESTART1Y")==0)
        {
                sscanf(line,"MAZESTART1Y=%d",&movey1);
        }
        if (strcmp(var,"MAZESTART2X")==0)
        {
                sscanf(line,"MAZESTART2X=%d",&movex2);
        }
        if (strcmp(var,"MAZESTART2Y")==0)
        {
                sscanf(line,"MAZESTART2Y=%d",&movey2);
        }
        if (strcmp(var,"POSITION1X")==0)
        {
                sscanf(line,"POSITION1X=%d",&position1x);
        }
        if (strcmp(var,"POSITION1Y")==0)
        {
                sscanf(line,"POSITION1Y=%d",&position1y);
        }
        if (strcmp(var,"POSITION2X")==0)
        {
                sscanf(line,"POSITION2X=%d",&position2x);
        }
        if (strcmp(var,"POSITION2Y")==0)
        {
                sscanf(line,"POSITION2Y=%d",&position2y);
        }
        if (strcmp(var,"SAS_STARTX")==0)
        {
                sscanf(line,"SAS_STARTX=%d",&SAS_STARTX);
//                get_map_x=SAS_STARTX;
        }
        if (strcmp(var,"SAS_STARTY")==0)
        {
                sscanf(line,"SAS_STARTY=%d",&SAS_STARTY);
//                get_map_y=SAS_STARTY;
        }
        if (strcmp(var,"SAS_ZOOM")==0)
        {
                sscanf(line,"SAS_ZOOM=%d",&SAS_ZOOM);
//                get_map_zoom=SAS_ZOOM;
        }
        if (strcmp(var,"SAS_ZOOM_DIRECTION")==0)
        {
                sscanf(line,"SAS_ZOOM_DIRECTION=%d",&SAS_ZOOM_DIRECTION);
//                get_map_zoom=SAS_ZOOM;
        }
        if (strcmp(var,"SAS_ORDER")==0)
        {
                sscanf(line,"SAS_ORDER=\"%9[^\"]\"",SAS_ORDER);
        }
        if (strcmp(var,"SAS_URL")==0)
        {
                sscanf(line,"SAS_URL=\"%1000[^\"]\"",SAS_URL);
        }
        if (strcmp(var,"SAS_EXTENSION")==0)
        {
                sscanf(line,"SAS_EXTENSION=\"%20[^\"]\"",SAS_EXTENSION);
        }
   }
    fclose (file);

    sprintf(naam,"%s/%dx%d/%03d/mazeoff_var.dat",LEVELDIR,BITMAPSX,BITMAPSY,level);
    file = fopen (naam, "r");
    if (file==NULL)
    {
        strcpy(error_msg,"FILE NOT FOUND: ");
        strcat(error_msg,naam);
        error_flag=1;
        return 0;
    }

    while (fgets (line,mazesizex*2+100, file)!=NULL )
    {
        sscanf(line,"%[^=]",var);
        if (nopos==0) {
            if (strcmp(var,"X")==0)
            {
                sscanf(line,"X=%d,Y=%d",&x,&y);
                picturex=x/1920;
                posx=x-1920*picturex;
                picturey=y/1080;
                posy=y-1080*picturey;
                posx=-posx;
                posy=-posy;
                fposx=posx;
                fposy=posy;
                start_posx=(picturex*1920-posx);
                start_posy=(picturey*1080-posy);
            }
        }

        if (strcmp(var,"MAZESTART1X")==0)
        {
                sscanf(line,"MAZESTART1X=%d",&movex1);
        }
        if (strcmp(var,"MAZESTART1Y")==0)
        {
                sscanf(line,"MAZESTART1Y=%d",&movey1);
        }
        if (strcmp(var,"MAZESTART2X")==0)
        {
                sscanf(line,"MAZESTART2X=%d",&movex2);
        }
        if (strcmp(var,"MAZESTART2Y")==0)
        {
                sscanf(line,"MAZESTART2Y=%d",&movey2);
        }
        if (strcmp(var,"POSITION1X")==0)
        {
                sscanf(line,"POSITION1X=%d",&position1x);
        }
        if (strcmp(var,"POSITION1Y")==0)
        {
                sscanf(line,"POSITION1Y=%d",&position1y);
        }
        if (strcmp(var,"POSITION2X")==0)
        {
                sscanf(line,"POSITION2X=%d",&position2x);
        }
        if (strcmp(var,"POSITION2Y")==0)
        {
                sscanf(line,"POSITION2Y=%d",&position2y);
        }
        if (strcmp(var,"SAS_ZOOM_DIRECTION")==0)
        {
                sscanf(line,"SAS_ZOOM_DIRECTION=%d",&SAS_ZOOM_DIRECTION);
//                get_map_zoom=SAS_ZOOM;
        }
        if (strcmp(var,"SAS_ORDER")==0)
        {
                sscanf(line,"SAS_ORDER=\"%9[^\"]\"",SAS_ORDER);
        }
        if (strcmp(var,"SAS_URL")==0)
        {
                sscanf(line,"SAS_URL=\"%1000[^\"]\"",SAS_URL);
        }
        if (strcmp(var,"SAS_EXTENSION")==0)
        {
                sscanf(line,"SAS_EXTENSION=\"%20[^\"]\"",SAS_EXTENSION);
        }
    }
    fclose (file);
    return 1;
}


void background_blitter();
sf::Thread blitter_thread  (&background_blitter);

int running=0;

void launch_background_blitter() {
    if (running==0) {
        blitter_thread.launch();
        running=1;
    }
    go_blit=1;
}

void terminate_background_blitter() {
    go_blit=0;
//    blitter_thread.terminate();
}
extern sf::Sprite *spritemaxinmempoint[];

//sf::RenderWindow SUB_WINDOW;

void background_blitter() {
    while (go_blit==1) {

    }
    running=0;
}


/*
void background_blitter() {
    static sf::Vector2u old_size=( sf::Vector2u(1920/2,1080/2) );
    static sf::Vector2i old_pos=( sf::Vector2i(1920/4,1080/4));
    sf::Event event;
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::ContextSettings contextSettings(0,0,2,3,0);
    contextSettings.antialiasingLevel = 0;
    SUB_WINDOW.create(sf::VideoMode(1920,1080), "Background Blitter", sf::Style::Resize | sf::Style::Close,contextSettings);
//    SUB_WINDOW.create(sf::VideoMode(1920,1080, desktop.bitsPerPixel), "Bill Gates", sf::Style::None,contextSettings);
    SUB_WINDOW.setSize(old_size);
    SUB_WINDOW.setPosition(old_pos);
//    SUB_WINDOW.requestFocus();
//    SUB_WINDOW.setActive();
    SUB_WINDOW.setVerticalSyncEnabled(true);
    int go_blit_off=1;

    while (1) {
        while (go_blit==1 && SUB_WINDOW.isOpen()) {
            if (go_blit_off==1) {
                go_blit_off=0;
            }
            if (go_pos==1) {
                DONTREADBITMAPS=1;
                render_mutex.lock();
                follow_ghost_pos();
                render_mutex.unlock();
                DONTREADBITMAPS=0;

            }
            SUB_WINDOW.clear(sf::Color(0,0,0,0));
            int x,y;
            render_mutex.lock();
            for (x=0; x<=1; x++)
                for (y=0; y<=1; y++)
                {
                    int arx=(render_picturex+x)%(maxpicturex+1);
                    int ary=(render_picturey+y)%(maxpicturey+1);
                    if (used[arx][ary]==0) {
                    }
                    else {
                        spritemaxinmempoint[used2[arx][ary]]->setPosition((float)(x*1920)-(float)fmod(smooth_x+(double)maxpixelsx,1920.0),(float)(y*1080)-(float)fmod(smooth_y+(double)maxpixelsy,1080.0));
                        SUB_WINDOW.draw(*spritemaxinmempoint[used2[arx][ary]]);
                    }
                }
            render_mutex.unlock();
            loader_mutex.lock();
            monitor_off=1;
            loader_mutex.unlock();
            SUB_WINDOW.display();
            while (SUB_WINDOW.pollEvent(event))
            {
                if (event.type == sf::Event::Closed) {
                        old_size=SUB_WINDOW.getSize();
                        old_pos=SUB_WINDOW.getPosition();
                        SUB_WINDOW.close();
                        running=0;
                        go_blit=0;
                        go_pos=0;
                        return;
                        break;
                }
                if (event.type == sf::Event::KeyPressed)
                {
                    switch (event.key.code)
                    {
                        case sf::Keyboard::Escape:
                            old_size=SUB_WINDOW.getSize();
                            old_pos=SUB_WINDOW.getPosition();
                            running=0;
                            go_blit=0;
                            go_pos=0;
                            SUB_WINDOW.close();
                            return;
                            break;
                        default:
                            break;
                    }
                }
            }
        }
        go_blit_off=1;
    }
    running=0;
    go_blit=0;
    go_pos=0;
}
*/
//extern sf::VertexArray m_pointCloud_maps[2][2];


void update_map(int totalx,int totaly) {
    int x,y;
    int ymap=0;
    int cloud_pos=0;
    m_pointCloud_map1[0].position.x=(float)(0.0);
    m_pointCloud_map1[0].position.y=(float)(0.0);
    m_pointCloud_map1[0].texCoords.x=(float)(0.0);
    m_pointCloud_map1[0].texCoords.y=(float)(0.0);

    for (y=0; y<15; y++)
    {
        int xmap=0;
        for (x=0; x<30; x++)
        {
            m_pointCloud_map0[cloud_pos].position.x=(float)(xmap);
            m_pointCloud_map0[cloud_pos].position.y=(float)(ymap);
//            m_pointCloud_map0[cloud_pos].position.y=(float)(1080-ymap);
            m_pointCloud_map0[cloud_pos].texCoords.x=(float)(xmap*150);
//            m_pointCloud_map0[cloud_pos].texCoords.y=(float)((1080-ymap-72)*150);
            m_pointCloud_map0[cloud_pos].texCoords.y=(float)(ymap*150);
            xmap+=64;
            cloud_pos++;
        }
        ymap+=72;
    }
    return;
}

