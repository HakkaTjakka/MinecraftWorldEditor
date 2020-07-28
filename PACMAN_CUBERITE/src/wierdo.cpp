#define PI 3.141592653589793
#define SFML_STATIC
#undef UNICODE
#include <winsock2.h>
#include <io.h>
#include "WinMain.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <iostream>
#include <cstdlib>
#include <Windows.h>
#include <Winuser.h>
#include <assert.h>
#include <vector>
#include <cmath>
#include <dirent.h>
#include <time.h>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <SFML/System/Mutex.hpp>
#include <SFML/Network/IpAddress.hpp>
#include <SFML/OpenGL.hpp>
#include <GL/glext.h>
#include <GL/glu.h>
#include <GL/gl.h>
extern int movieextern;
extern float run_time;
void gen_picture(int totalx,int totaly);
extern void mydraw_texture(char *towrite, int xpos, int ypos, sf::Color inner, sf::Color outer, sf::RenderTexture * texture);
int status_entry(int num);
int gen_tile(char * type, char * file, char * url, int ref_num, sf::Texture * local_texture,char * MAPDIR,char *ip,int get_map_zoom,int map_y,int map_x,
             int offsetx,int offsety,int totalx,int totaly);
int insert_entry(char * type, char * file, char * url, int ref_num, sf::Texture * texture,char * MAPDIR,char *ip,int get_map_zoom,int map_y,int map_x);
int print_entry(int num);
int internet_threads=0;
sf::Mutex internet_threads_mutex;
extern int is_activated_window[];
extern int do_all;
void CHECKDIR(char * MAPDIR,char * ip,int get_map_zoom,int map_y);
extern sf::Mutex user_mutex;
extern int F1;
int send_flag=0;
struct handler_struct {
    int blending;
    int plot_front;
    int show;
    int tile;
    int shader;
};
int request_3d_x=-1;
int request_3d_y=-1;
extern sf::Mutex wierdo_mutex;
extern sf::Mutex interface_mutex;
extern int drawmazes;
extern int totalfiles_mazes;
extern int totalfiles;
extern char **files;
extern char **files_mazes;
#include <glm/glm.hpp>
#include <glm/common.hpp>

extern std::vector<glm::ivec2> wierdo_requests;
extern std::vector<std::string> wierdo_filenames;

#define FFMPEG_SELECT 0
#define INTERNET_SELECT 1
#define MOVIE_SELECT 2
#define MOVIE2_SELECT 3
#define CANVAS_SELECT 4

#define BLENDING_SELECT 0
#define PLOT_FRONT_SELECT 1
#define SHOW_SELECT 2
#define TILE_SELECT 3
#define SHADER_SELECT 4

extern struct handler_struct handler[];

int error_main=0;
int error_win1=0;
int error_win2=0;
int error_win3=0;
extern int level;
extern int offset_picture_x;
extern int offset_picture_y;
extern char LEVELDIR[];
extern char PICTUREDIR[];
extern int record_screen;
extern int SAS_STARTX_a;
extern int SAS_STARTY_a;
extern int plot_all;
extern int blending;
extern sf::BlendMode MyBlendingMode;
extern int smooth;
extern int long_jump;
extern int picturex;
extern int picturey;
extern int posx;
extern int posy;
extern int fposx;
extern int fposy;
extern void follow_ghost_pos();
extern int forced_jump;
extern ReadBitmaps2();
extern int DONTREADBITMAPS;
extern int render_picturex;
extern int render_picturey;
extern int render_posx;
extern int render_posy;
sf::Mutex render_mutex;
extern int ESCAPE;
extern int goexit;
int kill1=0;int kill2=0;int kill3=0;
extern void launch_monimem();
extern int monitor_off;
extern int monitor;
extern void ShowTaskBar(bool show);
extern int taskbar;
extern MSG msg;
extern void HANDLEEVENTS();
extern int F2;
extern char MAPDIR[];
extern char LEVELDIR[];
extern char PICTUREDIR[];
extern int replace_str(char *str, char *orig, char *rep);
int ending1_x;
int ending2_x;
int ending3_x;
int ending1_y;
int ending2_y;
int ending3_y;
extern void HANDLEKEY(WPARAM wparam,sf::Event event);
extern void HANDLECHAR(WPARAM wparam);
extern void add_border(sf::Texture * MyTexture);
extern int helpme;
char text_line2[2000];
char text_line3[2000];
char text_line4[2000];
char text_line5[2000];
int map_changed=0;
extern int used_maxinmem[];
extern int  **used2;
extern int totalused;
extern char **used;
extern void blitter2();

sf::Event event1;
sf::Event event2;
sf::Event event3;
void background_loader1();
void background_loader2();
void background_loader3();
sf::Vector2i mytotal1;
sf::Vector2i mytotal2;
sf::Vector2i mytotal3;
sf::Thread background_loader_one    (&background_loader1);
sf::Thread background_loader_two    (&background_loader2);
sf::Thread background_loader_three  (&background_loader3);
int loader1_active=0;
int loader2_active=0;
int loader3_active=0;
sf::RenderWindow window_1;
sf::RenderWindow window_2;
sf::RenderWindow window_3;
int window_1_active=0;
int window_2_active=0;
int window_3_active=0;

sf::Mutex loader_mutex;

extern sf::Texture texture_from_movie_new;
extern sf::Texture texture_from_movie2_new;
extern setinternetfile();
extern sf::Texture texture_from_internet;
extern sf::Texture texture_from_ffmpeg;
extern int plot_front,plot_back;
extern char SAS_URL[];
extern char SAS_ORDER[];
extern int SAS_ZOOM;
extern int SAS_ZOOM_DIRECTION;
extern int get_map_x, get_map_y, get_map_zoom;
extern int GetGoogleMap(char * url, sf::Texture * result);
void kiki();
extern void draw2(char *towrite, int xpos, int ypos, sf::Color inner, sf::Color outer);
extern sf::RenderWindow SFMLView1;
extern void blitter(char * line, int mode);
extern bool file_exists3(const char * filename);


extern int internetfile;
extern int ffmpegfile;
extern int movie;
extern int movie2;

extern sf::Sprite *spritemaxinmempoint[];
extern sf::RenderTexture texture_from_buffer;
extern sf::Sprite *sprite_buffer;

extern int totalpicturex;
extern int totalpicturey;
extern int shade_map;

extern int SAS_STARTX;
extern int SAS_STARTY;
extern char SAS_DIR[];
extern char SAS_EXTENSION[];
extern void savedata(char *naam, int data);
extern char **changed;
extern int totalchanged;

extern int frustum_size_x;
extern int frustum_size_y;

float maxim(float a, float b, float c)
{
     float d;
     if (a>b) d=a; else d=b;
     if (c>d) d=c;
     return (d);
}

float minim(float a, float b, float c)
{
     float d;
     if (a<b) d=a; else d=b;
     if (c<d) d=c;
     return (d);
}

void calcpixel2(int pixx, int pixy, int *r, int *g, int *b);

extern sf::RenderTexture *texturemaxinmempoint[];
extern sf::Sprite spritedot;
extern int  **used2;
extern int formula;

extern int fragment_shader;
extern int vertex_shader;

extern sf::Shader picture_shader;
extern sf::RenderStates picture_states;

extern int picturex;
extern int picturey;

extern int BITMAPSX;
extern int BITMAPSY;
extern sf::Texture texture_from_ffmpeg;
extern int ffmpegfile;
extern char *line;
extern int map_end_x;
extern int map_end_y;
extern int plot_shader;
extern int shader_ok;
extern char error_msg2[];
extern int error_flag2;
extern char error_msg[];
extern int error_flag;
extern sf::Sprite sprite_from_internet;
extern sf::Sprite sprite_from_ffmpeg;
extern sf::Sprite sprite_from_movie;
extern sf::Sprite sprite_from_movie2;
extern int buffer_shader;
int mytex_start=0;
sf::Texture mytex;


sf::Texture entry_texture[100];
int generate_tiles=0;

extern int count_errors;

sf::Sprite sprite1_local;
sf::Texture texture1_local;
sf::RenderTexture render_texture1_local;

int wierdo(int totalx,int totaly, int silent) {
    count_errors=0;
    int x,y;
    sf::Image image1;
    sf::RenderTexture texture2;

    if (shade_map>=1) {
        int runfirst=0;
        error_main=0;
        internet_threads_mutex.lock();
        internet_threads=0;
        internet_threads_mutex.unlock();

        loader_mutex.lock();
        if (mytex_start==0) {
            mytex.loadFromFile("resources/border.png");
            mytex_start=1;
        }
        loader_mutex.unlock();

        sf::Texture texture_from_internet2;
        map_changed=0;
        char url[2000];
        int map_x,map_y;
        int offset_x,offset_y;
        sf::Texture m_texture;
        sf::Sprite m_sprite;
        int get_map_x_new=get_map_x;
        int get_map_y_new=get_map_y;

        int entry[100];
        int entry_plus[100];
        int entry_count;
        for (entry_count=0; entry_count<100; entry_count++) { entry[entry_count]=0; entry_plus[entry_count]=0;}
        int tot_count;
        int run=0;
        int ready=0;
        int num_ready=0;
        int counter=0;
        while (run<=1) {
//            if (F2==1) printf("************************* RUN=%d  RUNFIRST=%d  NUM_READY=%d  COUNTER=%d\n",run,runfirst,num_ready,counter);
            counter++;
            num_ready=0;
            if (run==1) ready=1;
            if (run==1) {
//                if (entry_count==1) return 1;
                tot_count=entry_count;
//                else tot_count=entry_count;
            }
            entry_count=0;
            if (generate_tiles) {
                run=1;
                silent=1;
            }

            map_x=((offset_picture_x+totalx)*1920)/256;
            offset_x=((offset_picture_x+totalx)*1920-map_x*256)%256;
            int map_x_start=map_x;
            int notile=0;
            int tiles_in_map=(int)pow(2.0,(get_map_zoom));
            if (map_x>=tiles_in_map) { map_end_x=1; return 1; }
            map_y=((offset_picture_y+totaly)*1080)/256;
            if (map_y>=tiles_in_map) { map_end_y=1; return 1; }
            while ( (map_x*256 <= (offset_picture_x+totalx+1)*1920+256) && (map_x<tiles_in_map) && notile==0  ) {
                loader_mutex.lock();
                monitor_off=1;
                loader_mutex.unlock();
                map_y=((offset_picture_y+totaly)*1080)/256;
                offset_y=((offset_picture_y+totaly)*1080-map_y*256)%256;
                int map_y_start=map_y;
                notile=0;
                while ( (map_y*256 <= (offset_picture_y+totaly+1)*1080+256) && (map_y<tiles_in_map) && notile==0 ) {
//                    if (run==0) {
//                        m_sprite.setTexture(mytex,true);
//                        m_sprite.setTextureRect({0,0,256,256});
//                        m_sprite.setPosition((map_x-map_x_start)*256-offset_x,(map_y-map_y_start)*256-offset_y);
//                        texturemaxinmempoint[used2[totalx][totaly]]->draw(m_sprite);
//                    }
                    loader_mutex.lock();
                    monitor_off=1;
                    loader_mutex.unlock();
                    if (F2==1 && silent==0) sprintf(text_line5,"STATUS THREADS: HELPME=%d,LOADER=%d,%d,%d WINDOW=%d,%d,%d KILL=%d,%d,%d ",
                            helpme,loader1_active,loader2_active,loader3_active,
                            window_1_active,window_2_active,window_3_active,
                            kill1,kill2,kill3);

                    if (SAS_ZOOM_DIRECTION<0) {
                        if (strcmp(SAS_ORDER,"XYZ")==0)
                            sprintf(url,SAS_URL,map_x,map_y,-SAS_ZOOM_DIRECTION-get_map_zoom);
                        else if (strcmp(SAS_ORDER,"ZXY")==0)
                            sprintf(url,SAS_URL,-SAS_ZOOM_DIRECTION-get_map_zoom,map_x,map_y);
                        else
                            sprintf(url,SAS_URL,-SAS_ZOOM_DIRECTION-get_map_zoom,map_y,map_x);
                    }
                    else {
                        if (strcmp(SAS_ORDER,"XYZ")==0)
                            sprintf(url,SAS_URL,map_x,map_y,get_map_zoom+SAS_ZOOM_DIRECTION);
                        else if (strcmp(SAS_ORDER,"ZXY")==0)
                            sprintf(url,SAS_URL,get_map_zoom+SAS_ZOOM_DIRECTION,map_x,map_y);
                        else
                            sprintf(url,SAS_URL,get_map_zoom+SAS_ZOOM_DIRECTION,map_y,map_x);
                    }
                    char ip[200];
                    char page[4000];
                    if (url[0]>='0' && url[0]<='9') {
                        int dummy;
                        if (toupper(url[5])=='S') sscanf(url, "%dhttps://%199[^/]/%199[^\n]",&dummy, ip,page );
                        else sscanf(url, "%dhttp://%199[^/]/%199[^\n]",&dummy, ip,page);
                        strcpy(page,ip);
                        sprintf(ip,"%s-%d",page,dummy);
                        strcpy(page,url);
                        strcpy(url,&page[1]);
                    } else {
                        if (toupper(url[4])=='S') sscanf(url, "https://%199[^/]/%199[^\n]", ip,page );
                        else sscanf(url, "http://%199[^/]/%199[^\n]", ip,page);
                    }
                    if (strlen(SAS_DIR)>0) {
                        char kwijl[1000];
//                        sprintf(kwijl,"%s/z%d/%d/%d.png", SAS_DIR,get_map_zoom,map_y,map_x);
                        strcpy(kwijl,SAS_DIR);
                        strcat(kwijl,"/z%d/%d/%d.png");

                        sprintf(line,kwijl,get_map_zoom,map_y,map_x);
                    } else {
                        sprintf(line,"%s/%s/map.z%d/y%d/x%d.png",MAPDIR,ip,get_map_zoom,map_y,map_x);
                    }
//                    printf("line=%s\n",line);
                    int res;
                    res=0;
/*
                    if (F2==1 && record_screen==0 && run>=1) { //!!!
                        SFMLView1.setActive(true);
                        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                        SFMLView1.setActive(false);

                        m_sprite.setTexture(texturemaxinmempoint[used2[totalx][totaly]]->getTexture(),true);
                        m_sprite.setTextureRect({0,0,1920,1080});
                        m_sprite.setPosition(0,0);
                        SFMLView1.draw(m_sprite);
                    }
*/
                    int exist;
                    exist=0;
                    int status;
                    status=0;
                    int from_internet;
                    from_internet=0;
                    int texture_loaded;
                    texture_loaded=0;
                    int texture_saved;
                    texture_saved=0;
                    int load_error;
                    load_error=0;
                    int loaded_ready;
                    loaded_ready=0;
                    int saved_ready;
                    saved_ready=0;

                    if (run==0 || generate_tiles) {
                        if (generate_tiles)  {
                            entry[entry_count] = gen_tile("GETTILE",line,url,entry_count,&entry_texture[entry_count],MAPDIR,ip,get_map_zoom,map_y,map_x,
                                                        (map_x-map_x_start)*256-offset_x,(map_y-map_y_start)*256-offset_y,totalx,totaly
                                                          );
                            texture_loaded=1;
                            status=1;
                        }
                        else {
                            entry[entry_count] = insert_entry("GETTILE",line,url,entry_count,&entry_texture[entry_count],MAPDIR,ip,get_map_zoom,map_y,map_x);
                        }
//                        user_mutex.lock();
//                        exist=file_exists3(line);
//                        user_mutex.lock();
                    }
                    else {
                        if (entry[entry_count]!=-9999) {
                            status=status_entry(entry[entry_count]);
                            if ((status&1)==1) texture_loaded=1;
                            if ((status&2)==2) texture_saved=1;
                            if ((status&4)==4) from_internet=1;
                            if ((status&8)==8) load_error=1;
                            ready=0;
                        } else {
//                            printf("READY: entry[%3d]=%3d\n",entry_count,entry[entry_count]);
                            num_ready++;
                            status=-1;
                        }
                    }
                    res=load_error;
                    if ((exist || texture_loaded==1) && status!=-1) {
                        if (run==0) {
//                            entry[entry_count] = insert_entry("LOADFILE",line,"",entry_count,&entry_texture[entry_count]);
//                            if (F2==1) printf("LOAD FROM FILE:     entry[%3d]=%3d FILE %s\n",entry_count,entry[entry_count],line);
                        } else  {
//                            printf("LOAD FROM DISK:?       entry[%d]=%d FILE ? %s\n",entry_count,entry[entry_count],line);
                            if (from_internet==0) {
//                                if (F2==1) printf("LOADED FILE:      print_entry(entry[%3d]=%3d)=",entry_count,entry[entry_count]);
//                                if (F2==1) printf(" REF=%3d\n",print_entry(entry[entry_count]));
                                if (F2==1 && silent==0) sprintf(text_line2,"BITMAP %d,%d Loaded from file:     %s",totalx,totaly,line);
                                entry[entry_count]=-9999;
                                loaded_ready=1;
                            } else {
                                if (entry_plus[entry_count]==0) {
//                                    if (F2==1) printf("LOADED INTERNET:  print_entry(entry[%3d]=%3d)=",entry_count,entry[entry_count]);
//                                    if (F2==1) printf(" REF=%3d\n",print_entry(entry[entry_count]));
                                    if (F2==1 && silent==0) sprintf(text_line2,"BITMAP %d,%d Loaded from internet: %s",totalx,totaly,line);
                                    loaded_ready=1;
                                }
                                if (texture_saved) {
//                                    if (entry_plus[entry_count]==0)
//                                        if (F2==1) printf("                 SAVED INTERNET:   print_entry(entry[%3d]=%3d)=",entry_count,entry[entry_count]);
//                                    else
//                                        if (F2==1) printf("SAVED INTERNET:   print_entry(entry[%3d]=%3d)=",entry_count,entry[entry_count]);
//                                    if (F2==1) printf(" REF=%3d\n",print_entry(entry[entry_count]));
                                    if (F2==1 && silent==0) sprintf(text_line2,"BITMAP %d,%d Saved from internet:  %s",totalx,totaly,line);
                                    entry[entry_count]=-9999;
                                    saved_ready=1;
                                } else {
                                    //if (entry_plus[entry_count]==0)
//                                        if (F2==1) printf("                 WAITING FOR SAVE: print_entry(entry[%3d]=%3d)=",entry_count,entry[entry_count]);
//                                    else
//                                        if (F2==1) printf("WAITING FOR SAVE: print_entry(entry[%3d]=%3d)=",entry_count,entry[entry_count]);
//                                    if (F2==1) printf(" REF=%3d\n",print_entry(entry[entry_count]));
                                    if (F2==1 && silent==0) sprintf(text_line2,"BITMAP %d,%d Don't waiting for save:     %s",totalx,totaly,line);
//                                    if (F2==1 && silent==0) sprintf(text_line2,"BITMAP %d,%d Waiting for save:     %s",totalx,totaly,line);
//after saver. release texture array and exit function. Thread continues to save from other local texture copy.
                                    entry[entry_count]=-9999;
                                    entry_plus[entry_count]=1;
                                }
                            }
//                            res=load_error;
                        }
                    }
                    else {
                        if (run==0) {
                            if (generate_tiles==0) helpme=1;
//                            CHECKDIR(MAPDIR,ip,get_map_zoom,map_y);
/*
                            char nop[100];
                            DIR* dir;
                            strcpy(dirname,MAPDIR);while (replace_str(dirname,"/","\\\\"));
                            dir = opendir(dirname);
                            int msgboxID=0;
                            if (!dir)
                            {
                                mkdir(dirname);
                                dir = opendir(dirname);
                                if (!dir) {msgboxID=MessageBox(NULL, "CANNOT CREATE DIRECOTRY FOR", (char*)line,MB_OK); }
                                else  closedir(dir);
                            } else closedir(dir);

                            sprintf(nop,"\\%s",ip);
                            strcat(dirname,nop);
                            dir = opendir(dirname);
                            if (!dir)
                            {
                                mkdir(dirname);
                                dir = opendir(dirname);
                                if (!dir) {msgboxID=MessageBox(NULL, "CANNOT CREATE DIRECOTRY FOR", (char*)line,MB_OK); }
                                else closedir(dir);
                            } else closedir(dir);

                            sprintf(nop,"\\map.z%d",get_map_zoom);
                            strcat(dirname,nop);
                            dir = opendir(dirname);
                            if (!dir)
                            {
                                mkdir(dirname);
                                dir = opendir(dirname);
                                if (!dir) {msgboxID=MessageBox(NULL, "CANNOT CREATE DIRECOTRY FOR", (char*)line,MB_OK); }
                                else closedir(dir);
                            } else closedir(dir);

                            sprintf(nop,"\\y%d",map_y);
                            strcat(dirname,nop);
                            dir = opendir(dirname);
                            if (!dir)
                            {
                            {
                                mkdir(dirname);
                                dir = opendir(dirname);
                                if (!dir) {msgboxID=MessageBox(NULL, "CANNOT CREATE DIRECOTRY FOR", (char*)line,MB_OK); }
                                else closedir(dir);
                            } else closedir(dir);
*/

//                            entry[entry_count] = insert_entry("LOADINTERNET",line,url,entry_count,&entry_texture[entry_count]);
//                            if (F2==1) printf("LOAD FROM INTERNET: entry[%3d]=%3d FILE %s <- URL %s\n",entry_count,entry[entry_count],line,url);

                        } else if (status>=0) {
//                            printf("LOADED FROM INTERNET:? entry[%d]=%d FILE ? %s <- URL ? %s\n",entry_count,entry[entry_count],line,url);
                            if (from_internet) {
//                                if (F2==1) printf("WAITING INTERNET: print_entry(entry[%3d]=%3d)=",entry_count,entry[entry_count]);
//                                if (F2==1) printf(" REF=%3d\n",print_entry(entry[entry_count]));
//                                if (runfirst<2) {
//                                    res=GetGoogleMap(url,&texture_from_internet2);
//                                }
                            } else {
//                                if (F2==1) printf("WAITING FILE:     print_entry(entry[%3d]=%3d)=",entry_count,entry[entry_count]);
//                                if (F2==1) printf(" REF=%3d\n",print_entry(entry[entry_count]));
//                                if (runfirst<2) {
//                                    texture_from_internet2.loadFromFile(line);
//                                    res=0;
//                                }
                            }
                        }
                        if (run>0 && status>=0 && (texture_loaded || load_error)) {  //!!!!!!!!
                            if (from_internet) {
                                if (res!=0) {
//                                    mytex.copyToImage().saveToFile(line);
//                                    if (F2==1) printf("SAVING INTERNET ERROR TO FILE:  %3d %s\n",entry_count,line);
                                    if (F2==1 && silent==0) sprintf(text_line4,"BITMAP %d,%d FAILED Loading from internet: %s LOADING ABORTED",totalx,totaly,url);
//                                    if (F2==1) printf("%s NOT LOADED. BITMAP X=%d,Y=%d\n",url,totalx,totaly);
                                } else {
//                                    entry_texture[entry_count].copyToImage().saveToFile(line);
//                                    texture_from_internet2.copyToImage().saveToFile(line);
                                    if (entry[entry_count]!=-9999 && loaded_ready) {
//                                        if (F2==1) printf("SUCCES LOADING INTERNET       : %3d %s\n",entry_count,url);
                                        if (F2==1 && silent==0) sprintf(text_line3,"BITMAP %d,%d Loaded from internet: %s",totalx,totaly,url);
                                    }
                                    else if (saved_ready) {
//                                        if (F2==1) printf("SUCCES LOADING/SAVING INTERNET: %3d %s -> %s\n",entry_count,url,line);
                                        if (F2==1 && silent==0) sprintf(text_line3,"BITMAP %d,%d Saved from internet:  %s",totalx,totaly,url);
                                    }
                                }
                            } else {
                                if (res!=0) {
//                                    if (F2==1) printf("ERROR LOADING FILE:  %3d %s\n",entry_count,line);
                                    if (F2==1 && silent==0) sprintf(text_line4,"BITMAP %d,%d FAILED Loading from file:     %s LOADING ABORTED",totalx,totaly,url);
                                } else {
//                                    if (F2==1) printf("SUCCES LOADING FILE: %3d %s\n",entry_count,line);
                                    if (F2==1 && silent==0) sprintf(text_line3,"BITMAP %d,%d Loaded from file:     %s",totalx,totaly,url);
                                }
                            }
                        }
                    }


                    if (run>0 && status>0 && (loaded_ready || load_error>0)) {  //!!!!!!!!
                        if (res==0) {
                            if (!generate_tiles) {
                                m_sprite.setTexture(entry_texture[entry_count],true);
                                m_sprite.setTextureRect({0,0,256,256});
                                m_sprite.setPosition((map_x-map_x_start)*256-offset_x,(map_y-map_y_start)*256-offset_y);
                                texturemaxinmempoint[used2[totalx][totaly]]->draw(m_sprite);
                            }
                            map_changed=1;
                            if (changed[totalx][totaly]==0)
                            {
                                changed[totalx][totaly]=1;
                                totalchanged++;
                            }
                        }
                        else
                        {
                            m_sprite.setTexture(mytex,true);
                            m_sprite.setTextureRect({0,0,256,256});
//                            m_sprite.setPosition(offset_x,offset_y);
                            m_sprite.setPosition((map_x-map_x_start)*256-offset_x,(map_y-map_y_start)*256-offset_y);
                            texturemaxinmempoint[used2[totalx][totaly]]->draw(m_sprite);
//                            texturemaxinmempoint[used2[totalx][totaly]]->display();
//                            if (F2==1 && record_screen==0 && run>=1 && silent==0) texturemaxinmempoint[used2[totalx][totaly]]->display();
                            if (map_y>=tiles_in_map) {
//                            if (get_map_y_new+map_y>=tiles_in_map) {
                                notile=1;
                                map_end_y=1;
                            }
                            loader_mutex.lock();
                            char filenaam[1000];
                            char dirname[1000];
                            sprintf(filenaam,"%s/error.txt",MAPDIR);
                            FILE* file = fopen (filenaam, "a");
                            if (file!=NULL)
                            {
                                strcpy(dirname,line);
                                while (replace_str(dirname,"/","\\"));
                                fprintf (file, "del %s\n",dirname);
                                fclose (file);
                            }
                            if (error_main==0) {
                                sprintf(filenaam,"%s/%dx%d/error.txt",LEVELDIR,BITMAPSX,BITMAPSY);
                                file = fopen (filenaam, "a");
                                if (file!=NULL)
                                {
                                    sprintf(filenaam,"%s\\%dx%d\\%03d\\picture.%06d.%06d.png",LEVELDIR,BITMAPSX,BITMAPSY,level,(totaly),(totalx));
                                    while (replace_str(filenaam,"/","\\"));
                                    fprintf (file, "del %s\n",filenaam);
                                    fclose (file);
                                }
                                sprintf(filenaam,"%s/error.txt",MAPDIR);
                                file = fopen (filenaam, "a");
                                if (file!=NULL)
                                {
                                    sprintf (filenaam, "%s\\map.z%d\\pictures\\y%d\\picture.%06d.%06d.png",LEVELDIR,get_map_zoom,offset_picture_y+totaly,offset_picture_y+totaly,offset_picture_x+totalx);
                                    while (replace_str(filenaam,"/","\\"));
                                    fprintf (file, "del %s\n",filenaam);
                                    fclose (file);
                                }
                            }
                            loader_mutex.unlock();
                            error_main=1;
                            if (changed[totalx][totaly]==1)
                            {
                                changed[totalx][totaly]=0;
                                totalchanged--; // dont save....corrupted
                            }
                        }
                    }
                    if (F2==1 && record_screen==0 && run>=1 && silent==0) { //!!!
                        SFMLView1.setActive(true);
                        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                        SFMLView1.setActive(false);
                        texturemaxinmempoint[used2[totalx][totaly]]->display();
                        m_sprite.setTexture(texturemaxinmempoint[used2[totalx][totaly]]->getTexture(),true);
                        m_sprite.setTextureRect({0,0,1920,1080});
                        m_sprite.setPosition(0,0);
                        SFMLView1.draw(m_sprite);
                        draw2(text_line2,0,32,sf::Color::Blue,sf::Color::White);
                        draw2(text_line3,0,32*2,sf::Color::Blue,sf::Color::White);
                        draw2(text_line4,0,32*3,sf::Color::Blue,sf::Color::Red);
                        draw2(text_line5,0,32*4,sf::Color::Blue,sf::Color::White);
                        draw2((char*)"GENERATING BACKGROUND",780,0,sf::Color(map_x%255,map_y%255,(map_x+map_y)%255,255),sf::Color::White);
                        SFMLView1.display();
                    }
                    if (notile==0) {
                        map_y++;
                    }
                    if (load_error) entry[entry_count]=-9999;
                    entry_count++;
//                    printf("\n");

                }
                map_x++;
                if ((map_x>=tiles_in_map && map_y>=tiles_in_map) && notile==1) {
//                if ((get_map_x_new+map_x>=tiles_in_map && get_map_y_new+map_y>=tiles_in_map) && notile==1) {
                    if (run>0) { //!!!
/*                        if (F2==1 && record_screen==0 && run>0 && silent==0) { //!!!
                            SFMLView1.setActive(true);
                            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                            SFMLView1.setActive(false);
                            m_sprite.setTexture(texturemaxinmempoint[used2[totalx][totaly]]->getTexture(),true);
                            m_sprite.setTextureRect({0,0,1920,1080});
                            m_sprite.setPosition(0,0);
                            SFMLView1.draw(m_sprite);
                            SFMLView1.display();
                        }
*/
                        if (ready) {
                            map_end_x=1;
                            map_end_y=1;
                            if (generate_tiles) gen_picture(totalx,totaly);
                            if ( !(F2==1 && record_screen==0 && run>0 && silent==0))
                                texturemaxinmempoint[used2[totalx][totaly]]->display();
                            return 1;
                        } else {
                            map_end_x=0;
                            map_end_y=0;
                        }
                    } else {
                        map_end_x=0;
                        map_end_y=0;
                    }
                }
                notile=0;
            }
            ready=1;
            num_ready=0;
            for (int c=0; c<entry_count; c++) {
                if (entry[c]!=-9999) {
                    ready=0;
//                    break;
                } else {
                    num_ready++;
                }
            }
            if (ready || run==0) {
//                if (runfirst==1) run=1; // third run...
//                else run++;
                run++;
            }
            runfirst++;
//            if (F2==1) printf("ready=%d  num_ready=%d\n",ready,num_ready);
        }
        if (generate_tiles) gen_picture(totalx,totaly);
        if ( !(F2==1 && record_screen==0 && run>0 && silent==0))
            texturemaxinmempoint[used2[totalx][totaly]]->display();

/*
        if (F2==1 && record_screen==0 && silent==0) {
            m_sprite.setTexture(texturemaxinmempoint[used2[totalx][totaly]]->getTexture(),true);
            m_sprite.setTextureRect({0,0,1920,1080});
            m_sprite.setPosition(0,0);
            SFMLView1.draw(m_sprite);
            draw2(text_line2,0,32,sf::Color::Blue,sf::Color::White);
            draw2(text_line3,0,32*2,sf::Color::Blue,sf::Color::White);
            draw2(text_line4,0,32*3,sf::Color::Blue,sf::Color::Red);
            draw2(text_line5,0,32*4,sf::Color::Blue,sf::Color::White);
            SFMLView1.display();
        }
*/
        return 0;
    }

    if ( (fragment_shader!=0 || plot_shader>=1) && formula>=1) {

        if (shader_ok==0) {
            strcpy(error_msg2,"NO SHADER SELECTED, CTRL-S PLOT SHADER OFF, ALT-F2 SELECT SHADER");
            error_flag2=1;
            return 1;
        } else {
            picture_states.shader = &picture_shader;
        }
        float scalex=1.0,scaley=1.0;
        if (movie==0) {
            if (!buffer_shader==1) picture_shader.setUniform("texture_buffer", texture_from_movie_new);
            if (!buffer_shader==1) picture_shader.setUniform("iResolution_buffer",  sf::Vector2f( texture_from_movie_new.getSize().x,texture_from_movie_new.getSize().y) );
            scalex=sprite_from_movie.getScale().x*texture_from_movie_new.getSize().x/1920.0;
            scaley=sprite_from_movie.getScale().y*texture_from_movie_new.getSize().y/1080.0;
        }  else if (movie2==0) {
            if (!buffer_shader==1) picture_shader.setUniform("texture_buffer", texture_from_movie2_new);
            if (!buffer_shader==1) picture_shader.setUniform("iResolution_buffer",  sf::Vector2f( texture_from_movie2_new.getSize().x,texture_from_movie2_new.getSize().y) );
            scalex=sprite_from_movie2.getScale().x*texture_from_movie2_new.getSize().x/1920.0;
            scaley=sprite_from_movie2.getScale().y*texture_from_movie2_new.getSize().y/1080.0;
        } else if (ffmpegfile==0) {
            if (!buffer_shader==1) picture_shader.setUniform("texture_buffer", texture_from_ffmpeg);
            if (!buffer_shader==1) picture_shader.setUniform("iResolution_buffer",  sf::Vector2f( texture_from_ffmpeg.getSize().x,texture_from_ffmpeg.getSize().y) );
            scalex=sprite_from_ffmpeg.getScale().x*texture_from_ffmpeg.getSize().x/1920.0;
            scaley=sprite_from_ffmpeg.getScale().y*texture_from_ffmpeg.getSize().y/1080.0;
        } else if (internetfile==0) {
            if (!buffer_shader==1) picture_shader.setUniform("texture_buffer", texture_from_internet);
            if (!buffer_shader==1) picture_shader.setUniform("iResolution_buffer",  sf::Vector2f( texture_from_internet.getSize().x,texture_from_internet.getSize().y) );
            scalex=sprite_from_internet.getScale().x*texture_from_internet.getSize().x/1920.0;
            scaley=sprite_from_internet.getScale().y*texture_from_internet.getSize().y/1080.0;
        }

        if (formula==3) {
            float addx=(-scalex*1920.0 + 1920.0)*BITMAPSX/2.0;
            float addy=(-scaley*1080.0 + 1080.0)*BITMAPSY/2.0;
            picture_shader.setUniform("pos_correction", sf::Vector2f((float) ((-totalx*1920)%(BITMAPSX*1920)), (float) (-1080*(BITMAPSY-1)+(totaly*1080)%(BITMAPSY*1080)) ) );
            picture_shader.setUniform("txt_correction", sf::Vector2f(addx+(float) ((-totalx*1920)%(BITMAPSX*1920)), addy+(float) (-1080*(BITMAPSY-1)+(totaly*1080)%(BITMAPSY*1080)) ) );
            picture_shader.setUniform("iResolution",  sf::Vector2f(scalex*(float)1920.0*BITMAPSX,scaley*(float)1080.0*BITMAPSY ) );
        } else {
            picture_shader.setUniform("pos_correction", sf::Vector2f((float) ((-totalx*1920)%(BITMAPSX*1920)), (float) (-1080*(BITMAPSY-1)+(totaly*1080)%(BITMAPSY*1080)) ) );
            picture_shader.setUniform("txt_correction", sf::Vector2f((float) ((-totalx*1920)%(BITMAPSX*1920)), (float) (-1080*(BITMAPSY-1)+(totaly*1080)%(BITMAPSY*1080)) ) );
            picture_shader.setUniform("iResolution",  sf::Vector2f( (float)1920.0*BITMAPSX,(float)1080.0*BITMAPSY ) );
        }
        picture_shader.setUniform("background_plot",  1 );
        picture_shader.setUniform("formula_on",  1 );
        picture_shader.setUniform("formula",  formula );
extern float run_time;
        picture_shader.setUniform("iTime",   run_time );

        sf::RenderTexture* texture_surround[9];
        extern sf::RenderTexture texturemaxinmem[];

        if (formula==2) {
            for (x=-1; x<=1; x++) {
                for (y=-1; y<=1; y++) {
                        texture_surround[(x+1)+(-y+1)*3]=&texturemaxinmem[ used2[(totalx+totalpicturex+x)%(totalpicturex)][(totaly+totalpicturey+y)%(totalpicturey)]];
                }
            }
            picture_shader.setUniform("texture_surround[0]",  texture_surround[0]->getTexture() );
            picture_shader.setUniform("texture_surround[1]",  texture_surround[1]->getTexture() );
            picture_shader.setUniform("texture_surround[2]",  texture_surround[2]->getTexture() );
            picture_shader.setUniform("texture_surround[3]",  texture_surround[3]->getTexture() );
            picture_shader.setUniform("texture_surround[4]",  texture_surround[4]->getTexture() );
            picture_shader.setUniform("texture_surround[5]",  texture_surround[5]->getTexture() );
            picture_shader.setUniform("texture_surround[6]",  texture_surround[6]->getTexture() );
            picture_shader.setUniform("texture_surround[7]",  texture_surround[7]->getTexture() );
            picture_shader.setUniform("texture_surround[8]",  texture_surround[8]->getTexture() );
            SFMLView1.setActive(true);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            SFMLView1.setActive(false);
            texture2.create(1920,1080);
            texture2.clear( sf::Color(0,0,0,0) );
            if (smooth==1) texture2.setSmooth(true);
            else texture2.setSmooth(false);
            sprite1_local.setTexture(texturemaxinmempoint[used2[totalx][totaly]]->getTexture(),false);
//            sprite1.setTexture(texture_from_ffmpeg,false);
            sprite1_local.setTextureRect({0,0,1920,1080});
            texture2.draw(sprite1_local,picture_states);
            texture2.display();
            sprite1_local.setTexture(texture2.getTexture(),false);
            SFMLView1.draw(sprite1_local);
            SFMLView1.display();

            char naam[200];
            sprintf(naam,"%s/picture.%06d.%06d.png",PICTUREDIR,(totaly+totalpicturey)%(totalpicturey),(totalx+totalpicturex)%(totalpicturex));
            texture2.getTexture().copyToImage().saveToFile(naam);
        } else {
            picture_shader.setUniform("pos_abs",  sf::Vector2f(0.0,0.0) );
            texture2.create(1920,1080);
            texture2.clear( sf::Color(0,0,0,0) );
            if (smooth==1) texture2.setSmooth(true);
            else texture2.setSmooth(false);
            if (plot_back==1) {
                sprite1_local.setTexture(texture2.getTexture(),false);
                sprite1_local.setTextureRect({0,0,1920,1080});
                spritemaxinmempoint[used2[totalx][totaly]]->setPosition(0,0);
                texture2.draw(*spritemaxinmempoint[used2[totalx][totaly]]);
                texture2.display();
                texturemaxinmempoint[used2[totalx][totaly]]->clear(sf::Color(0,0,0,0));
                texturemaxinmempoint[used2[totalx][totaly]]->draw(sprite1_local,picture_states);
                texturemaxinmempoint[used2[totalx][totaly]]->draw(sprite1_local);
                texturemaxinmempoint[used2[totalx][totaly]]->display();
                if (plot_all==1) texturemaxinmempoint[used2[totalx][totaly]]->generateMipmap();
            } else {
//hoppa
                if (blending>0) {
                    sprite1_local.setTexture(texture2.getTexture(),true);
//                    texture2.draw(sprite1,picture_states);
//                    texture2.display();
                    texturemaxinmempoint[used2[totalx][totaly]]->draw(sprite1_local,picture_states);

                } else {
                    sprite1_local.setTexture(texture2.getTexture(),true);
                    texture2.draw(sprite1_local,picture_states);
                    texture2.display();
                    texturemaxinmempoint[used2[totalx][totaly]]->draw(sprite1_local);
                }
                texturemaxinmempoint[used2[totalx][totaly]]->display();
                if (plot_all==1) texturemaxinmempoint[used2[totalx][totaly]]->generateMipmap();
            }
        }
//        sprite1.setTexture(texturemaxinmempoint[used2[totalx][totaly]]->getTexture(),true);
//        SFMLView1.draw(sprite1);
//        SFMLView1.display();
        if (changed[totalx][totaly]==0 && formula!=2) {
            changed[totalx][totaly]=1;
            totalchanged++;
        }
        return 0;
    }


    int pixx,pixy;
    int r,g,b,trans=255;
    if (formula==2) {
        image1.create(1920,1080,sf::Color(255, 0, 0, 255));
        for (x=0; x<1920; x++) {
            for (y=0; y<1080; y++) {
                pixx=x+totalx*1920;
                pixy=y+totaly*1080;

               static float calcx=1.0/(1920.0*totalpicturex)*2.0*3.1415;
               static float calcy=1.0/(1080.0*totalpicturey)*2.0*3.1415;

               static float rr,gg,bb;
               static float r1,g1,b1;
               static float r2,g2,b2;
               static float r3,g3,b3;
               static float r4,g4,b4;
               static float r5,g5,b5;
               static float r6,g6,b6;
               static float fpixx;
               static float fpixy;
               static float straal1;
               static float straal2;
               static float straal3;

                fpixx=sin(pixx*calcx*totalpicturex/4);
                fpixy=sin(pixy*calcy*totalpicturey/4);

                  r1=(sin(fpixx*4.1)  +sin(fpixy*3)+2)/4;
                  g1=(sin(fpixx*5.3)  +sin(fpixy*4)+2)/4;
                  b1=(sin(fpixx*6.3)  +sin(fpixy*5)+2)/4;

                  straal1=sqrt(r1*r1*10+10*g1*g1);
                  straal2=sqrt(b1*b1*10+10*g1*g1+straal1);
                  straal3=sqrt(b1*b1*10+10*r1*r1+straal2);

                  r2=(sin(r1*7+fpixx*5.3)+sin(fpixy*5*straal1)+2)/4;
                  g2=(sin(g1*9+fpixx*3)+    sin(fpixy*7*straal2)+2)/4;
                  b2=(sin(b1*5+fpixx*2.5)+sin(fpixy*4*straal3)+2)/4;

                  r3=(sin(fpixx*3*straal1) +sin(r2*3+fpixy*6)+2)/4;
                  g3=(sin(fpixx*4*straal2) +sin(g2*4+fpixy*5)+2)/4;
                  b3=(sin(fpixx*5*straal3)+sin(b2*5+fpixy*4)+2)/4;

                  r4=maxim(r1,r2,g3);
                  g4=maxim(b1,g2,r3);
                  b4=maxim(g1,g3,b2);

                  r5=minim(r2,r3,g1);
                  g5=minim(b1,g3,r3);
                  b5=minim(g1,b2,r1);

                  r6=maxim(r3,g2,b1);
                  g6=maxim(r2,g1,b3);
                  b6=maxim(b2,r2,b1);

                  rr=(r4 + r5+r6)*255.99;
                  gg=(g4 + g5+g6)*255.99;
                  bb=(b4 + b5+b6)*255.99;

                  b=((int)bb)%256;
                  g=((int)gg)%256;
                  r=((int)rr)%256;

                image1.setPixel(x,y,sf::Color(r,g,b));
            }
        }
    } else if (formula==1) {
//        texture1.update();

/*
        if (!(totalx<frustum_size_x && totaly<frustum_size_y)) {
            wierdo_mutex.lock();
            request_3d_x=-1;
            request_3d_y=-1;
            wierdo_mutex.unlock();

            return 1;
        }
*/
/*
        int got_it=0;
        for (int i=0; i<10; i++) {
            if (is_activated_window[i]==1) {
                got_it++;
                if (got_it==2) break;
            }
        }
        if (got_it==0) {
            printf("No 3d system running\n");
            return 1;
        } else if (got_it>1) {
            printf("Only 1 3d system can be used, more than 1 running...\n");
            return 1;
        }
*/
        if (totalx>=frustum_size_x) { map_end_x=1; return 0; }
        if (totaly>=frustum_size_y) { map_end_x=1; map_end_y=1; return 0; }
        char naam[2000];
        sprintf(naam,"%s/%dx%d/%03d/picture.%06d.%06d.png",LEVELDIR,BITMAPSX,BITMAPSY,level,(totaly),(totalx));
        for (auto u : wierdo_requests) {
            if (u.x==totalx && u.y==totaly) {
                printf("Already in list X=%02d,Y=%02d  Setting formula=0\n",totalx,totaly);
                formula=0;
                return 0;
            }
        }

        wierdo_mutex.lock();
        wierdo_requests.push_back(glm::ivec2(totalx,totaly));
        wierdo_filenames.push_back(std::string() + naam);
//        printf("Pushing X=%02d,Y=%02d %s\n",totalx,totaly,naam);
//        printf(".");
        wierdo_mutex.unlock();
        return 0;

        static bool first=1;
        wierdo_mutex.lock();
        request_3d_x=totalx;
        request_3d_y=totaly;
        wierdo_mutex.unlock();
        int test=0;
        int cnt=0;
        while (test>=0) {
            wierdo_mutex.lock();
            test=request_3d_y;
            wierdo_mutex.unlock();
            int got_it=0;
            for (int i=0; i<10; i++) {
                if (is_activated_window[i]==1) {
                    got_it++;
                    if (got_it==1) break;
                }
            }
            if (got_it==0) {
                test=-1;
                printf("Exiting\n");
                wierdo_mutex.lock();
                request_3d_x=-1;
                request_3d_y=-1;
                wierdo_mutex.unlock();
            }

            if (test>=0) {
                sf::sleep(sf::milliseconds(10));
//                cnt++;
//                if ((cnt%10)==0) { cnt=0; printf("."); }
//                if (cnt==100) { cnt=0; printf("bye\n"); return 1;}
            }
        }
        if (request_3d_x>=0) {
            printf("Received X=%02d,Y=%02d\n",totalx,totaly);
            sprite1_local.setTexture(texture1_local,true);
            texturemaxinmempoint[used2[totalx][totaly]]->draw(sprite1_local);
            texturemaxinmempoint[used2[totalx][totaly]]->display();
            wierdo_mutex.lock();
            request_3d_y=-2;
            wierdo_mutex.unlock();
            char naam[2000];
            sprintf(naam,"%s/%dx%d/%03d/picture.%06d.%06d.png",LEVELDIR,BITMAPSX,BITMAPSY,level,(totaly),(totalx));
            texturemaxinmempoint[used2[totalx][totaly]]->getTexture().copyToImage().saveToFile(naam);
            if (drawmazes==1) {
                if (files_mazes[totalx][totaly]==0) {
                    files_mazes[totalx][totaly]=1;
                    totalfiles_mazes++;
                }
            } else {
                if (files[totalx][totaly]==0) {
                    files[totalx][totaly]=1;
                    totalfiles++;
                }
            }
            if (changed[totalx][totaly]==1) {
                changed[totalx][totaly]=0;
                totalchanged--;
            }

//            texturemaxinmempoint[used2[totalx][totaly]]->generateMipmap();

            return 0;
        } else {
//            printf("Aborting at X=%d Y=%d\n",totalx,totaly);
            request_3d_x=-1;
            map_end_x=1;
            map_end_y=1;
            request_3d_y=-2;
//            ESCAPE=1;
            return 1;
        }
    }

    texture1_local.loadFromImage(image1,{0,0,1920,1080});

   	sprite1_local.setTexture(texture1_local,false);
	sprite1_local.setTextureRect({0,0,1920,1080});

	texturemaxinmempoint[used2[totalx][totaly]]->draw(sprite1_local);
	texturemaxinmempoint[used2[totalx][totaly]]->display();
    if (plot_all==1) texturemaxinmempoint[used2[totalx][totaly]]->generateMipmap();
    if (changed[totalx][totaly]==0)
    {
        changed[totalx][totaly]=1;
        totalchanged++;
    }
    return 0;
}

void calcpixel3(int pixx, int pixy, int *r, int *g, int *b) {
    static float calcx=1.0/(1920.0*totalpicturex)*2.0*3.1415;
    static float calcy=1.0/(1080.0*totalpicturey)*2.0*3.1415;
    float totx=pixx*calcx;
    float toty=pixy*calcy;

    float straal1=sin((totx-0.5)*(totx-0.5)+(toty-0.5)*(toty-0.5));
    float straal2=sin((totx+0.5)*(totx+0.5)+(toty-1.5)*(toty-1.5));
    float straal3=sin((totx+0.5)*(toty-0.5)+(toty+0.5)*(totx+0.5));

    float rr=sin(straal1*totx*5)+cos(straal2*toty*4)+2;
    float gg=sin(straal3*totx*7)+cos(straal1*toty*6)+2;
    float bb=sin(straal2*totx*8)+cos(straal3*toty*3)+2;

    float rg=sin(straal3*totx*4.5)+cos(straal1*toty*4.5)+2;
    float gb=sin(straal2*totx*7.5)+cos(straal2*toty*6.5)+2;
    float br=sin(straal1*totx*8.5)+cos(straal3*toty*3.5)+2;

    float r1=maxim(rr,rg,br);
    float g1=maxim(gg,gb,rg);
    float b1=maxim(bb,br,gb);

    float r2=minim(rr,rg,br);
    float g2=minim(gg,gb,rg);
    float b2=minim(bb,br,gb);

    rr=(r2 + r1)*31.999;
    gg=(g2 + g1)*31.999;
    bb=(b2 + b1)*31.999;


    *b=((int)bb)%256;
    *g=((int)gg)%256;
    *r=((int)rr)%256;

   return;
}

void kiki(){
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    else
    {
        HANDLEEVENTS();
    }
}

void kill_threads() {
    loader_mutex.lock();
        background_loader_one.terminate();
        background_loader_two.terminate();
        background_loader_three.terminate();
    loader_mutex.unlock();
}

void launch_background_loader_one() {
    loader1_active=1;
    if (window_1_active==0) background_loader_one.launch();
}
void launch_background_loader_two() {
    loader2_active=1;
    if (window_2_active==0) background_loader_two.launch();
}
void launch_background_loader_three() {
    loader3_active=1;
    if (window_3_active==0) background_loader_three.launch();
}


void background_loader1() {
    error_win1=0;
    char dirname[1000];

    if (mytex_start==0) {
        loader_mutex.lock();
        mytex.loadFromFile("resources/border.png"); mytex_start=1;
        loader_mutex.unlock();
    }

    sf::Sprite m_sprite;
    sf::Texture result;
    char line2[4000];
    char line[4000];
    char url[4000];
    char local_URL[4000];
    int map_x,map_y;
    int offset_x,offset_y;
    int do_totalx=mytotal1.x;
    int do_totaly=mytotal1.y;
    int local_SAS_ZOOM_DIRECTION;
    char local_SAS_ORDER[10];

    static sf::Vector2u old_size=( sf::Vector2u(256,256) );
    static sf::Vector2i old_pos=( sf::Vector2i(1919-280,1079-10-3*300) );

    sf::ContextSettings contextSettings(0,0,2,3,0);
    contextSettings.antialiasingLevel = 0;
    window_1.create(sf::VideoMode(256,256), "Map loader 1", sf::Style::Resize | sf::Style::Titlebar | sf::Style::Close, contextSettings);
    window_1.setSize(old_size);
    window_1.setPosition(old_pos);
    if (F2==0 || record_screen==1) window_1.setVisible(false);
//    if (record_screen==1) window_1.setVisible(false);
    if (record_screen==0) window_1.setVerticalSyncEnabled(false);
    window_1_active=1;
    window_1.clear(sf::Color(255, 128, 0, 255));
    window_1.display();
    loader_mutex.lock();
//        if (taskbar==1 && record_screen==0) {
//            ShowTaskBar(false);
//            taskbar=0;
//        }
        kill1=0;
    loader_mutex.unlock();
    while (window_1.isOpen() ) {
        int thetime; thetime=100;
        srand(time(0)+10);
        while (loader1_active==0) {
            static int r=128,g=128,b=128;
            r=r+(rand()*rand()+rand())%21-10;g=g+(rand()*rand()+rand())%21-10;b=b+(rand()*rand()+rand())%21-10;
            if (r>255) r=255;if (r<0) r=0;   if (g>255) g=255;if (g<0) g=0;   if (b>255) b=255;if (b<0) b=0;
            window_1.clear(sf::Color(r,g,b,255));
            window_1.display();
            sf::sleep(sf::milliseconds(100));
//            SFMLView1.requestFocus();
            if (F2==1 && record_screen==0) thetime--;
            if (thetime<=0) {
                loader_mutex.lock();
                    kill1=1;
                loader_mutex.unlock();
                if (kill1==1 && kill2==1 && kill3==1) helpme=0;
            }
            while (window_1.pollEvent(event1) || kill1==1)
            {
                if (event1.type == sf::Event::Closed || kill1==1) {
                    old_size=window_1.getSize();
                    old_pos=window_1.getPosition();
                    loader_mutex.lock();
                        if (thetime<=0) kill1=0; else kill1=1;
                        window_1_active=0;
                        window_1.close();
                        loader1_active=0;
                    loader_mutex.unlock();
                    if (thetime<=0) printf("Thread1: Killing myself, exiting map loader thread\n");
                    else printf("Thread1: Killed, exiting map loader thread\n");
                    return;
                }
//                if (event1.type == sf::Event::TextEntered) if (event1.text.unicode < 128) HANDLECHAR((WPARAM)event1.text.unicode);
                if (event1.type == sf::Event::KeyPressed) {
                    switch (event1.key.code) {
                        case sf::Keyboard::Escape:
                            old_size=window_1.getSize();
                            old_pos=window_1.getPosition();
                            loader_mutex.lock();
                                window_1_active=0;
                                window_1.close();
                                kill1=1;
                                loader1_active=0;
                            loader_mutex.unlock();
                            printf("Thread1: Killed, exiting map loader thread\n");
                            return;
                            break;
                        default:
//                            HANDLEKEY((WPARAM)event1.key.code, event1); //messes things up like draw context etc...?? :(
                            break;
                    }
                }
            }
        }

        int local_level;
        local_level=level;
        char local_LEVELDIR[500];
        strcpy(local_LEVELDIR,LEVELDIR);
        int local_get_map_zoom;
        local_get_map_zoom=SAS_ZOOM;
        local_SAS_ZOOM_DIRECTION=SAS_ZOOM_DIRECTION;
        strcpy(local_SAS_ORDER,SAS_ORDER);
        strcpy(local_URL,SAS_URL);
        int local_offset_picture_x;
        int local_offset_picture_y;
        local_offset_picture_x=offset_picture_x;
        local_offset_picture_y=offset_picture_y;

        int ending=0;
        do_totalx=mytotal1.x;
        while (do_totalx==mytotal1.x && window_1.isOpen() && ending==0) {
            do_totaly=mytotal1.y;
            while (do_totaly==mytotal1.y && window_1.isOpen() && ending==0) {
//                map_x=(do_totalx*1920-SAS_STARTX_a)/256;
                map_x=((local_offset_picture_x+do_totalx)*1920)/256;
                offset_x=((local_offset_picture_x+do_totalx)*1920-map_x*256)%256;
//                offset_x=(do_totalx*1920-SAS_STARTX_a)%256;
//                offset_x=(do_totalx*1920-SAS_STARTX_a+256)%256;
//                map_x=do_totalx*1920/256; offset_x=(do_totalx*1920)%256;
                int map_x_start=map_x;
                int notile=0;
                int tiles_in_map=(int)pow(2.0,(local_get_map_zoom));
//                int tiles_in_map=(int)pow(2.0,(17-local_get_map_zoom));
                while (window_1.isOpen() && ending==0)
                {
//                    if (map_x+local_get_map_x<0) map_x=-local_get_map_x;
                    while ( (map_x*256 <= (local_offset_picture_x+do_totalx+1)*1920+256) && (map_x<tiles_in_map) && notile==0  ) {
//                    while ( (map_x*256 < (do_totalx+offset_picture_x)*1920+256) && (map_x<tiles_in_map) && notile==0 && ending==0  ) {
//                    while ( (map_x*256 < (do_totalx+1)*1920+256) && (map_x+local_get_map_x<tiles_in_map) && notile==0 && ending==0 && ((map_x-map_x_start)*256-offset_x<1920) ) {
//                        if (map_x+local_get_map_x<0) continue;

                        map_y=((local_offset_picture_y+do_totaly)*1080)/256;
                        offset_y=((local_offset_picture_y+do_totaly)*1080-map_y*256)%256;
//                        map_y=((offset_picture_y+do_totaly)*1080)/256;
//                        offset_y=((offset_picture_y+do_totaly)*1080-map_y*256)%256;
//                        map_y=(do_totaly*1080-SAS_STARTY_a)/256;
//                        offset_y=(do_totaly*1080-SAS_STARTY_a)%256;
//                        offset_y=(do_totaly*1080-SAS_STARTY_a+256)%256;
//                        map_y=do_totaly*1080/256; offset_y=(do_totaly*1080)%256;
                        int map_y_start=map_y;
                        notile=0;


//                        if (map_y+local_get_map_y<0) map_y=-local_get_map_y;
                        while ( (map_y*256 < (local_offset_picture_y+do_totaly+1)*1080+256) && (map_y<tiles_in_map) && notile==0 ) {
//                        while ( (map_y*256 <= (do_totaly+1)*1080+256) && (map_y+local_get_map_y<tiles_in_map) && notile==0 && ending==0 && ((map_y-map_y_start)*256-offset_y<1080) )  {
//                            if (map_y+local_get_map_y<0) continue;
                            if (local_SAS_ZOOM_DIRECTION<0)
                                if (strcmp(local_SAS_ORDER,"XYZ")==0)
                                    sprintf(url,local_URL,map_x,map_y,-local_SAS_ZOOM_DIRECTION-local_get_map_zoom);
                                else
                                    sprintf(url,local_URL,-local_SAS_ZOOM_DIRECTION-local_get_map_zoom,map_y,map_x);
                            else
                                if (strcmp(local_SAS_ORDER,"XYZ")==0)
                                    sprintf(url,local_URL,map_x,map_y,local_get_map_zoom+local_SAS_ZOOM_DIRECTION);
                                else if (strcmp(local_SAS_ORDER,"ZXY")==0)
                                    sprintf(url,local_URL,local_get_map_zoom+local_SAS_ZOOM_DIRECTION,map_x,map_y);
                                else
                                    sprintf(url,local_URL,local_get_map_zoom+local_SAS_ZOOM_DIRECTION,map_y,map_x);

                            char ip[200];
                            char page[4000];
                            if (url[0]>='0' && url[0]<='9') {
                                int dummy;
                                if (toupper(url[5])=='S') sscanf(url, "%dhttps://%199[^/]/%199[^\n]",&dummy, ip,page );
                                else sscanf(url, "%dhttp://%199[^/]/%199[^\n]",&dummy, ip,page);
                                strcpy(page,ip);
                                sprintf(ip,"%s-%d",page,dummy);
                                strcpy(page,url);
                                strcpy(url,&page[1]);
                            } else {
                                if (toupper(url[4])=='S') sscanf(url, "https://%199[^/]/%199[^\n]", ip,page );
                                else sscanf(url, "http://%199[^/]/%199[^\n]", ip,page);
                            }
                            if (strlen(SAS_DIR)>0) {
                                char kwijl[1000];
                                strcpy(kwijl,SAS_DIR);
                                strcat(kwijl,"/z%d/%d/%d.png");
                                sprintf(line,kwijl,local_get_map_zoom,map_y,map_x);
                            } else {
                                sprintf(line,"%s/%s/map.z%d/y%d/x%d.png",MAPDIR,ip,local_get_map_zoom,map_y,map_x);
                            }
                            int res=0;
                            if (file_exists3(line)) {
                                res=0;
                                map_y++;
                                continue;
                            }
                            else {
//google
//                    sprintf(url,SAS_URL,local_get_map_x+map_x,local_get_map_y+map_y,local_get_map_zoom);
//                                sprintf(url,SAS_URL,local_get_map_x+map_x,local_get_map_y+map_y,local_get_map_zoom);
                                res=GetGoogleMap(url,&result);
                                CHECKDIR(MAPDIR,ip,local_get_map_zoom,map_y);

/*
                                char nop[100];
                                DIR* dir;
                                strcpy(dirname,MAPDIR);while (replace_str(dirname,"/","\\\\"));
//                                strcpy(dirname,"pictures");
//                                loader_mutex.lock();
                                dir = opendir(dirname);
                                int msgboxID=0;

                                if (!dir)
                                {
                                    mkdir(dirname);
                                    dir = opendir(dirname);
                                    if (!dir) {msgboxID=MessageBox(NULL, "CANNOT CREATE DIRECOTRY FOR", (char*)line,MB_OK); }
                                    else  closedir(dir);
                                } else closedir(dir);

                                sprintf(nop,"\\%s",ip);
                                strcat(dirname,nop);
                                dir = opendir(dirname);
                                if (!dir)
                                {
                                    mkdir(dirname);
                                    dir = opendir(dirname);
                                    if (!dir) {msgboxID=MessageBox(NULL, "CANNOT CREATE DIRECOTRY FOR", (char*)line,MB_OK); }
                                    else closedir(dir);
                                } else closedir(dir);


                                sprintf(nop,"\\map.z%d",local_get_map_zoom);
                                strcat(dirname,nop);
                                dir = opendir(dirname);
                                if (!dir)
                                {
                                    mkdir(dirname);
                                    dir = opendir(dirname);
                                    if (!dir) {msgboxID=MessageBox(NULL, "CANNOT CREATE DIRECOTRY FOR", (char*)line,MB_OK); }
                                    else closedir(dir);
                                } else closedir(dir);
                                sprintf(nop,"\\y%d",map_y);
                                strcat(dirname,nop);
                                dir = opendir(dirname);
                                if (!dir)
                                {
                                    mkdir(dirname);
                                    dir = opendir(dirname);
                                    if (!dir) {msgboxID=MessageBox(NULL, "CANNOT CREATE DIRECOTRY FOR", (char*)line,MB_OK); }
                                    else closedir(dir);
                                } else closedir(dir);
//                                loader_mutex.unlock();
*/

                                if (res!=0) {
                                    printf("%s NOT LOADED. BITMAP X=%d,Y=%d\n",url,do_totalx,do_totaly);
                                    m_sprite.setTexture(mytex,true);
                                    m_sprite.setTextureRect({0,0,256,256});
                                    m_sprite.setPosition(0,0);
                                    window_1.clear(sf::Color(0,0,0,255));
                                    window_1.draw(m_sprite);
                                    window_1.display();
                                    if (internetfile==0 && !(movieextern==0)) {
                                        if (texture_from_internet.getSize()!=sf::Vector2u(256+20,256+20)) {
                                            texture_from_internet.create(256,256);
                                            add_border(&texture_from_internet);
                                        }
                                        texture_from_internet.update(mytex,10,10);
                                    }
//                                    mytex.copyToImage().saveToFile(line);
                                    loader_mutex.lock();
                                    char filenaam[1000];
                                    sprintf(filenaam,"%s/error.txt",MAPDIR);
                                    FILE* file = fopen (filenaam, "a");
                                    if (file!=NULL)
                                    {
                                        strcpy(dirname,line);
                                        while (replace_str(dirname,"/","\\"));
                                        fprintf (file, "del %s\n",dirname);
                                        fclose (file);
                                    }
                                    if (error_win1==0) {
                                        sprintf(filenaam,"%s/%dx%d/error.txt",local_LEVELDIR,BITMAPSX,BITMAPSY);
                                        file = fopen (filenaam, "a");
                                        if (file!=NULL)
                                        {
                                            sprintf(filenaam,"%s\\%dx%d\\%03d\\picture.%06d.%06d.png",local_LEVELDIR,BITMAPSX,BITMAPSY,local_level,(do_totaly),(do_totalx));
                                            while (replace_str(filenaam,"/","\\"));
                                            fprintf (file, "del %s\n",filenaam);
                                            fclose (file);
                                        }
                                        sprintf(filenaam,"%s/error.txt",MAPDIR);
                                        file = fopen (filenaam, "a");
                                        if (file!=NULL)
                                        {
                                            sprintf (filenaam, "%s\\map.z%d\\pictures\\y%d\\picture.%06d.%06d.png",local_LEVELDIR,local_get_map_zoom,local_offset_picture_y+do_totaly,local_offset_picture_y+do_totaly,local_offset_picture_x+do_totalx);
                                            while (replace_str(filenaam,"/","\\"));
                                            fprintf (file, "del %s\n",filenaam);
                                            fclose (file);
                                        }
                                        error_win1=1;
                                    }
                                    loader_mutex.unlock();
                                } else {
//                                    printf("%s     LOADED. BITMAP X=%d,Y=%d\n",url,do_totalx,do_totaly);
                                    m_sprite.setTexture(result,true);
                                    m_sprite.setTextureRect({0,0,256,256});
                                    m_sprite.setPosition(0,0);
                                    window_1.clear(sf::Color(0,0,0,255));
                                    window_1.draw(m_sprite);
                                    window_1.display();
//                                    printf("Thread1: Saving to file: %s\n",line);

                                    loader_mutex.lock();
                                    if (internetfile==0 && !(movieextern==0)) {
                                        if (texture_from_internet.getSize()!=sf::Vector2u(256+20,256+20)) {
                                            texture_from_internet.create(256,256);
                                            add_border(&texture_from_internet);
                                        }
                                        texture_from_internet.update(result,10,10);
                                    }
                                    result.copyToImage().saveToFile(line);
                                    loader_mutex.unlock();
                                }
                            }
                            if (res==0) {
                            }
                            else
                            {
//                                printf("Thread1: Not loaded.\n");
//                                notile=1;
//                                map_end_y=1;
                            }
                            if (notile==0) {
                                map_y++;
                            }
                            while (window_1.pollEvent(event1) || kill1==1)
                            {
                                if (event1.type == sf::Event::Closed || kill1==1) {
                                    printf("Thread1: Killed, exiting map loader thread\n");
                                    old_size=window_1.getSize();
                                    old_pos=window_1.getPosition();
                                    loader_mutex.lock();
                                        window_1_active=0;
                                        window_1.close();
                                        kill1=1;
                                        loader1_active=0;
                                    loader_mutex.unlock();
                                    return;
                                }
//                                if (event1.type == sf::Event::TextEntered) if (event1.text.unicode < 128) HANDLECHAR((WPARAM)event1.text.unicode);
                                if (event1.type == sf::Event::KeyPressed) {
                                    switch (event1.key.code) {
                                        case sf::Keyboard::Escape:
                                            old_size=window_1.getSize();
                                            old_pos=window_1.getPosition();
                                            loader_mutex.lock();
                                                window_1_active=0;
                                                window_1.close();
                                                kill1=1;
                                                loader1_active=0;
                                            loader_mutex.unlock();
                                            printf("Thread1: Killed, exiting map loader thread\n");
                                            return;
                                            break;
                                        default:
                                            break;
                                    }
                                }
                            }
                        }
                        if ( (map_y==map_y_start && notile==1) || map_y>=tiles_in_map) {
//                        if ( (map_y==map_y_start && notile==1) || map_y+local_get_map_y>=tiles_in_map) {
//                            loader1_active=0;
//                            notile=1;
//                            ending=1;
                              ending1_y=do_totaly;
//                            window_1_active=0;
//                            window_1.close();kill1=1;
//                            printf("Thread1: Exiting map loader thread\n");
//                            return ;
                        }
//                        else
//                        {
//                            notile=0;
                            map_x++;
//                            map_end_y=0;
                            if (map_x>=tiles_in_map && map_y>=tiles_in_map) {
//                            if (local_get_map_x+map_x>=tiles_in_map && local_get_map_y+map_y>=tiles_in_map) {
                                loader1_active=0;
                                notile=1;
                                ending=1;
                                ending1_x=do_totalx;
                            }
//                        }
                        while (window_1.pollEvent(event1) || kill1==1)
                        {
                            if (event1.type == sf::Event::Closed || kill1==1) {
                                printf("Thread1: Killed, exiting map loader thread\n");
                                old_size=window_1.getSize();
                                old_pos=window_1.getPosition();
                                loader_mutex.lock();
                                    window_1_active=0;
                                    window_1.close();
                                    kill1=1;
                                    loader1_active=0;
                                loader_mutex.unlock();
                                return;
                            }
//                            if (event1.type == sf::Event::TextEntered) if (event1.text.unicode < 128) HANDLECHAR((WPARAM)event1.text.unicode);
                            if (event1.type == sf::Event::KeyPressed) {
                                switch (event1.key.code) {
                                    case sf::Keyboard::Escape:
                                        old_size=window_1.getSize();
                                        old_pos=window_1.getPosition();
                                        loader_mutex.lock();
                                            window_1_active=0;
                                            window_1.close();
                                            kill1=1;
                                            loader1_active=0;
                                        loader_mutex.unlock();
                                        printf("Thread1: Killed, exiting map loader thread\n");
                                        return;
                                        break;
                                    default:
                                        break;
                                }
                            }
                        }
                    }
                    ending=1;
    //                window_1_active=0;
    //                window_1.close();kill1=1;
                }
                do_totaly++;
            }
            do_totalx++;
        }
        loader1_active=0;
    }

    printf("Thread1: Exiting map loader thread\n");
    old_size=window_1.getSize();
    old_pos=window_1.getPosition();
    window_1.clear(sf::Color(255,0,0,255));
    window_1.display();
    sf::sleep(sf::milliseconds(1500));
    loader_mutex.lock();
        window_1_active=0;
        window_1.close();
        kill1=1;
        loader1_active=0;
    loader_mutex.unlock();
    return ;
}

void background_loader2() {
    error_win2=0;
    char dirname[1000];
    if (mytex_start==0) {
        loader_mutex.lock();
        mytex.loadFromFile("resources/border.png"); mytex_start=1;
        loader_mutex.unlock();
    }

    sf::Sprite m_sprite;
    sf::Texture result;
    char line2[4000];
    char line[4000];
    char url[4000];
    char local_URL[4000];
    int map_x,map_y;
    int offset_x,offset_y;
    int do_totalx=mytotal2.x;
    int do_totaly=mytotal2.y;
    int local_SAS_ZOOM_DIRECTION;
    char local_SAS_ORDER[10];

    static sf::Vector2u old_size=( sf::Vector2u(256,256) );
    static sf::Vector2i old_pos=( sf::Vector2i(1919-280,1079-10-2*300) );

    sf::ContextSettings contextSettings(0,0,2,3,0);
    contextSettings.antialiasingLevel = 0;
    window_2.create(sf::VideoMode(256,256), "Map loader 2", sf::Style::Resize | sf::Style::Titlebar | sf::Style::Close, contextSettings);
    window_2.setSize(old_size);
    window_2.setPosition(old_pos);
    if (F2==0 || record_screen==1) window_2.setVisible(false);
//    if (record_screen==1) window_2.setVisible(false);
//    if (record_screen==1 || plot_all==1) window_2.setVisible(false);
    if (record_screen==0) window_2.setVerticalSyncEnabled(false);
    window_2_active=1;
    window_2.clear(sf::Color(255, 128, 0, 255));
    window_2.display();
    loader_mutex.lock();
//        if (taskbar==1 && record_screen==0) {
//            ShowTaskBar(false);
//            taskbar=0;
//        }
        kill2=0;
    loader_mutex.unlock();
    while (window_2.isOpen() ) {
        int thetime; thetime=100;
        srand(time(0)+20);
        while (loader2_active==0) {
            static int r=128,g=128,b=128;
            r=r+(rand()*rand()+rand())%21-10;g=g+(rand()*rand()+rand())%21-10;b=b+(rand()*rand()+rand())%21-10;
            if (r>255) r=255;if (r<0) r=0;if (g>255) g=255;if (g<0) g=0;if (b>255) b=255;if (b<0) b=0;
            window_2.clear(sf::Color(r,g,b,255));
            window_2.display();
//            SFMLView1.requestFocus();
            sf::sleep(sf::milliseconds(100));
            if (F2==1 && record_screen==0) thetime--;
            if (thetime<=0) {
                loader_mutex.lock();
                    kill2=1;
                loader_mutex.unlock();
                if (kill1==1 && kill2==1 && kill3==1) helpme=0;
            }

            while (window_2.pollEvent(event2)|| kill2==1)
            {
                if (event2.type == sf::Event::Closed || kill2==1 ) {
                    old_size=window_2.getSize();
                    old_pos=window_2.getPosition();
                    loader_mutex.lock();
                        if (thetime<=0) kill2=0; else kill2=1;
                        window_2_active=0;
                        window_2.close();
                        loader2_active=0;
                    loader_mutex.unlock();
                    if (thetime<=0) printf("Thread2: Killing myself, exiting map loader thread\n");
                    else printf("Thread2: Killed, exiting map loader thread\n");
                    return;
                }
//                if (event2.type == sf::Event::TextEntered) if (event1.text.unicode < 128) HANDLECHAR((WPARAM)event2.text.unicode);
                if (event2.type == sf::Event::KeyPressed) {
                    switch (event2.key.code) {
                        case sf::Keyboard::Escape:
                            old_size=window_2.getSize();
                            old_pos=window_2.getPosition();
                            loader_mutex.lock();
                                window_2_active=0;
                                window_2.close();
                                kill2=1;
                                loader2_active=0;
                            loader_mutex.unlock();
                            printf("Thread2: Killed, exiting map loader thread\n");
                            return;
                            break;
                        default:
                            break;
                    }
                }
            }
        }

        int local_level;
        local_level=level;
        char local_LEVELDIR[500];
        strcpy(local_LEVELDIR,LEVELDIR);
        int local_get_map_zoom;
        local_get_map_zoom=SAS_ZOOM;
        local_SAS_ZOOM_DIRECTION=SAS_ZOOM_DIRECTION;
        strcpy(local_SAS_ORDER,SAS_ORDER);
        strcpy(local_URL,SAS_URL);
        int local_offset_picture_x;
        int local_offset_picture_y;
        local_offset_picture_x=offset_picture_x;
        local_offset_picture_y=offset_picture_y;

        int ending=0;
        do_totalx=mytotal2.x;
        while (do_totalx==mytotal2.x && window_2.isOpen() && ending==0) {
            do_totaly=mytotal2.y;
            while (do_totaly==mytotal2.y && window_2.isOpen() && ending==0) {

                map_x=((local_offset_picture_x+do_totalx)*1920)/256;
                offset_x=((local_offset_picture_x+do_totalx)*1920-map_x*256)%256;
//                map_x=(do_totalx*1920-SAS_STARTX_a)/256;
//                offset_x=(do_totalx*1920-SAS_STARTX_a+256)%256;
//                offset_x=(do_totalx*1920-SAS_STARTX_a)%256;
//                map_x=do_totalx*1920/256; offset_x=(do_totalx*1920)%256;
                int map_x_start=map_x;
                int notile=0;
                int tiles_in_map=(int)pow(2.0,(local_get_map_zoom));
//                int tiles_in_map=(int)pow(2.0,(17-local_get_map_zoom));
                while (window_2.isOpen() && ending==0)
                {
//                    if (map_x+local_get_map_x<0) map_x=-local_get_map_x;
                    while ( (map_x*256 <= (local_offset_picture_x+do_totalx+1)*1920+256) && (map_x<tiles_in_map) && notile==0  ) {
//                    while ( (map_x*256 < (do_totalx+1)*1920+256) && (map_x+local_get_map_x<tiles_in_map) && notile==0 && ending==0 && ((map_x-map_x_start)*256-offset_x<1920) ) {
//                        if (map_x+local_get_map_x<0) continue;

                        map_y=((local_offset_picture_y+do_totaly)*1080)/256;
                        offset_y=((local_offset_picture_y+do_totaly)*1080-map_y*256)%256;
//                        map_y=(do_totaly*1080-SAS_STARTY_a)/256;
//                        offset_y=(do_totaly*1080-SAS_STARTY_a)%256;
//                        offset_y=(do_totaly*1080-SAS_STARTY_a+256)%256;
//                        map_y=do_totaly*1080/256; offset_y=(do_totaly*1080)%256;
                        int map_y_start=map_y;
                        notile=0;

//                        if (map_y+local_get_map_y<0) map_y=-local_get_map_y;
                        while ( (map_y*256 < (local_offset_picture_y+do_totaly+1)*1080+256) && (map_y<tiles_in_map) && notile==0 ) {
//                        while ( (map_y*256 <= (do_totaly+1)*1080+256) && (map_y+local_get_map_y<tiles_in_map) && notile==0 && ending==0 && ((map_y-map_y_start)*256-offset_y<1080) )  {
//                            if (map_y+local_get_map_y<0) continue;
                            if (local_SAS_ZOOM_DIRECTION<0)
                                if (strcmp(local_SAS_ORDER,"XYZ")==0)
                                    sprintf(url,local_URL,map_x,map_y,-local_SAS_ZOOM_DIRECTION-local_get_map_zoom);
                                else
                                    sprintf(url,local_URL,-local_SAS_ZOOM_DIRECTION-local_get_map_zoom,map_y,map_x);
                            else
                                if (strcmp(local_SAS_ORDER,"XYZ")==0)
                                    sprintf(url,local_URL,map_x,map_y,local_get_map_zoom+local_SAS_ZOOM_DIRECTION);
                                else if (strcmp(local_SAS_ORDER,"ZXY")==0)
                                    sprintf(url,local_URL,local_get_map_zoom+local_SAS_ZOOM_DIRECTION,map_x,map_y);
                                else
                                    sprintf(url,local_URL,local_get_map_zoom+local_SAS_ZOOM_DIRECTION,map_y,map_x);
                            char ip[200];
                            char page[4000];
                            if (url[0]>='0' && url[0]<='9') {
                                int dummy;
                                if (toupper(url[5])=='S') sscanf(url, "%dhttps://%199[^/]/%199[^\n]",&dummy, ip,page );
                                else sscanf(url, "%dhttp://%199[^/]/%199[^\n]",&dummy, ip,page);
                                strcpy(page,ip);
                                sprintf(ip,"%s-%d",page,dummy);
                                strcpy(page,url);
                                strcpy(url,&page[1]);
                            } else {
                                if (toupper(url[4])=='S') sscanf(url, "https://%199[^/]/%199[^\n]", ip,page );
                                else sscanf(url, "http://%199[^/]/%199[^\n]", ip,page);
                            }
                            if (strlen(SAS_DIR)>0) {
                                char kwijl[1000];
                                strcpy(kwijl,SAS_DIR);
                                strcat(kwijl,"/z%d/%d/%d.png");
                                sprintf(line,kwijl,local_get_map_zoom,map_y,map_x);
                            } else {
                                sprintf(line,"%s/%s/map.z%d/y%d/x%d.png",MAPDIR,ip,local_get_map_zoom,map_y,map_x);
                            }
//                            sprintf(line,"%s/map.z%d/y%d/x%d.png",MAPDIR,local_get_map_zoom,local_get_map_y+map_y,local_get_map_x+map_x);
                            int res=0;
                            if (file_exists3(line)) {
//                                printf("Thread2: File exists, skipping: %s\n",line);
                                res=0;
                                map_y++;
                                continue;
                            }
                            else {
//                    sprintf(url,SAS_URL,local_get_map_x+map_x,local_get_map_y+map_y,17-local_get_map_zoom);
//                                sprintf(url,SAS_URL,local_get_map_x+map_x,local_get_map_y+map_y,local_get_map_zoom);
                                res=GetGoogleMap(url,&result);
                                CHECKDIR(MAPDIR,ip,local_get_map_zoom,map_y);
/*
                                char nop[100];
                                DIR* dir;
//                                strcpy(dirname,"pictures");
                                strcpy(dirname,MAPDIR);while (replace_str(dirname,"/","\\\\"));
//                                loader_mutex.lock();
                                dir = opendir(dirname);
                                int msgboxID=0;

                                if (!dir)
                                {
                                    mkdir(dirname);
                                    dir = opendir(dirname);
                                    if (!dir) {msgboxID=MessageBox(NULL, "CANNOT CREATE DIRECOTRY FOR", (char*)line,MB_OK); }
                                    else  closedir(dir);
                                } else closedir(dir);

                                sprintf(nop,"\\%s",ip);
                                strcat(dirname,nop);
                                dir = opendir(dirname);
                                if (!dir)
                                {
                                    mkdir(dirname);
                                    dir = opendir(dirname);
                                    if (!dir) {msgboxID=MessageBox(NULL, "CANNOT CREATE DIRECOTRY FOR", (char*)line,MB_OK); }
                                    else closedir(dir);
                                } else closedir(dir);


                                sprintf(nop,"\\map.z%d",local_get_map_zoom);
                                strcat(dirname,nop);
                                dir = opendir(dirname);
                                if (!dir)
                                {
                                    mkdir(dirname);
                                    dir = opendir(dirname);
                                    if (!dir) {msgboxID=MessageBox(NULL, "CANNOT CREATE DIRECOTRY FOR", (char*)line,MB_OK); }
                                    else closedir(dir);
                                } else closedir(dir);
                                sprintf(nop,"\\y%d",map_y);
                                strcat(dirname,nop);
                                dir = opendir(dirname);
                                if (!dir)
                                {
                                    mkdir(dirname);
                                    dir = opendir(dirname);
                                    if (!dir) {msgboxID=MessageBox(NULL, "CANNOT CREATE DIRECOTRY FOR", (char*)line,MB_OK); }
                                    else closedir(dir);
                                } else closedir(dir);
//                                loader_mutex.unlock();
*/
                                if (res!=0) {
                                    printf("%s NOT LOADED. BITMAP X=%d,Y=%d\n",url,do_totalx,do_totaly);
                                    m_sprite.setTexture(mytex,true);
                                    m_sprite.setTextureRect({0,0,256,256});
                                    m_sprite.setPosition(0,0);
                                    window_2.clear(sf::Color(0,0,0,255));
                                    window_2.draw(m_sprite);
                                    window_2.display();
                                    if (internetfile==0 && !(movieextern==0)) {
                                        if (texture_from_internet.getSize()!=sf::Vector2u(256+20,256+20)) {
                                            texture_from_internet.create(256,256);
                                            add_border(&texture_from_internet);
                                        }
                                        texture_from_internet.update(mytex,10,10);
                                    }
//                                    mytex.copyToImage().saveToFile(line);
                                    loader_mutex.lock();
                                    char filenaam[1000];
                                    sprintf(filenaam,"%s/error.txt",MAPDIR);
                                    FILE* file = fopen (filenaam, "a");
                                    if (file!=NULL)
                                    {
                                        strcpy(dirname,line);
                                        while (replace_str(dirname,"/","\\"));
                                        fprintf (file, "del %s\n",dirname);
                                        fclose (file);
                                    }
                                    if (error_win2==0) {
                                        sprintf(filenaam,"%s/%dx%d/error.txt",local_LEVELDIR,BITMAPSX,BITMAPSY);
                                        file = fopen (filenaam, "a");
                                        if (file!=NULL)
                                        {
                                            sprintf(filenaam,"%s\\%dx%d\\%03d\\picture.%06d.%06d.png",local_LEVELDIR,BITMAPSX,BITMAPSY,local_level,(do_totaly),(do_totalx));
                                            while (replace_str(filenaam,"/","\\"));
                                            fprintf (file, "del %s\n",filenaam);
                                            fclose (file);
                                        }
                                        sprintf(filenaam,"%s/error.txt",MAPDIR);
                                        file = fopen (filenaam, "a");
                                        if (file!=NULL)
                                        {
                                            sprintf (filenaam, "%s\\map.z%d\\pictures\\y%d\\picture.%06d.%06d.png",local_LEVELDIR,local_get_map_zoom,local_offset_picture_y+do_totaly,local_offset_picture_y+do_totaly,local_offset_picture_x+do_totalx);
                                            while (replace_str(filenaam,"/","\\"));
                                            fprintf (file, "del %s\n",filenaam);
                                            fclose (file);
                                        }
                                        error_win2=1;
                                    }
                                    loader_mutex.unlock();
                                } else {
//                                    printf("%s     LOADED. BITMAP X=%d,Y=%d\n",url,do_totalx,do_totaly);
                                    m_sprite.setTexture(result,true);
                                    m_sprite.setTextureRect({0,0,256,256});
                                    m_sprite.setPosition(0,0);
                                    window_2.clear(sf::Color(0,0,0,255));
                                    window_2.draw(m_sprite);
                                    window_2.display();
//                                    printf("Thread2: Saving to file: %s\n",line);

                                    loader_mutex.lock();
                                    if (internetfile==0 && !(movieextern==0)) {
                                        if (texture_from_internet.getSize()!=sf::Vector2u(256+20,256+20)) {
                                            texture_from_internet.create(256,256);
                                            add_border(&texture_from_internet);
                                        }
                                        texture_from_internet.update(result,10,10);
                                    }
                                    result.copyToImage().saveToFile(line);
                                    loader_mutex.unlock();
                                }
                            }
                            if (res==0) {
                            }
                            else
                            {
//                                printf("Thread2: Not loaded.\n");
//                                notile=1;
//                                map_end_y=1;
                            }
                            if (notile==0) {
                                map_y++;
                            }
                            while (window_2.pollEvent(event2) || kill2==1)
                            {
                                if (event2.type == sf::Event::Closed || kill2==1) {
                                    printf("Thread2: Killed, exiting map loader thread\n");
                                    old_size=window_2.getSize();
                                    old_pos=window_2.getPosition();
                                    loader_mutex.lock();
                                        window_2_active=0;
                                        window_2.close();
                                        kill2=1;
                                        loader2_active=0;
                                    loader_mutex.unlock();
                                    return;
                                }
//                                if (event2.type == sf::Event::TextEntered) if (event2.text.unicode < 128) HANDLECHAR((WPARAM)event2.text.unicode);
                                if (event2.type == sf::Event::KeyPressed) {
                                    switch (event2.key.code) {
                                        case sf::Keyboard::Escape:
                                            old_size=window_2.getSize();
                                            old_pos=window_2.getPosition();
                                            loader_mutex.lock();
                                                window_2_active=0;
                                                window_2.close();
                                                kill2=1;
                                                loader2_active=0;
                                            loader_mutex.unlock();
                                            printf("Thread2: Killed, exiting map loader thread\n");
                                            return;
                                            break;
                                        default:
                                            break;
                                    }
                                }
                            }
                        }
                        if ( (map_y==map_y_start && notile==1) || map_y>=tiles_in_map) {
//                        if ( (map_y==map_y_start && notile==1) || map_y+local_get_map_y>=tiles_in_map) {
//                            loader2_active=0;
//                            notile=1;
//                            ending=1;
                            ending2_y=do_totaly;
//                            window_2_active=0;
//                            window_2.close();kill2=1;
//                            printf("Thread2: Exiting map loader thread\n");
//                            return ;
                        }
//                        else
//                        {
//                            notile=0;
                            map_x++;
                            if (map_x>=tiles_in_map && map_y>=tiles_in_map) {
//                            if (local_get_map_x+map_x>=tiles_in_map && local_get_map_y+map_y>=tiles_in_map) {
                                loader2_active=0;
                                notile=1;
                                ending=1;
                                ending2_x=do_totalx;
                            }
//                        }
                        while (window_2.pollEvent(event2) || kill2==1)
                        {
                            if (event2.type == sf::Event::Closed || kill2==1) {
                                printf("Thread2: Killed, exiting map loader thread\n");
                                old_size=window_2.getSize();
                                old_pos=window_2.getPosition();
                                loader_mutex.lock();
                                    window_2_active=0;
                                    window_2.close();
                                    kill2=1;
                                    loader2_active=0;
                                loader_mutex.unlock();
                                return;
                            }
//                            if (event2.type == sf::Event::TextEntered) if (event2.text.unicode < 128) HANDLECHAR((WPARAM)event2.text.unicode);
                            if (event2.type == sf::Event::KeyPressed) {
                                switch (event2.key.code) {
                                    case sf::Keyboard::Escape:
                                        old_size=window_2.getSize();
                                        old_pos=window_2.getPosition();
                                        loader_mutex.lock();
                                            window_2_active=0;
                                            window_2.close();
                                            kill2=1;
                                            loader2_active=0;
                                        loader_mutex.unlock();
                                        printf("Thread2: Killed, exiting map loader thread\n");
                                        return;
                                        break;
                                    default:
                                        break;
                                }
                            }
                        }
                    }
                    ending=1;
    //                window_2_active=0;
    //                window_2.close();kill2=1;
                }
                do_totaly++;
            }
            do_totalx++;
        }
        loader2_active=0;
    }

    printf("Thread2: Exiting map loader thread\n");
    old_size=window_2.getSize();
    old_pos=window_2.getPosition();
    window_2.clear(sf::Color(255,0,0,255));
    window_2.display();
    sf::sleep(sf::milliseconds(1500));
    loader_mutex.lock();
        window_2_active=0;
        window_2.close();
        kill2=1;
        loader2_active=0;
    loader_mutex.unlock();
    return ;
}

void background_loader3() {
    error_win3=0;
    char dirname[1000];
    if (mytex_start==0) {
        loader_mutex.lock();
        mytex.loadFromFile("resources/border.png"); mytex_start=1;
        loader_mutex.unlock();
    }

    sf::Sprite m_sprite;
    sf::Texture result;
    char line2[4000];
    char line[4000];
    char url[4000];
    char local_URL[4000];
    int map_x,map_y;
    int offset_x,offset_y;
    int do_totalx=mytotal3.x;
    int do_totaly=mytotal3.y;
    int local_SAS_ZOOM_DIRECTION;
    char local_SAS_ORDER[10];

    static sf::Vector2u old_size=( sf::Vector2u(256,256) );
    static sf::Vector2i old_pos=( sf::Vector2i(1919-280,1079-10-300) );

    sf::ContextSettings contextSettings(0,0,2,3,0);
    contextSettings.antialiasingLevel = 0;
    window_3.create(sf::VideoMode(256,256), "Map loader 3", sf::Style::Resize | sf::Style::Titlebar | sf::Style::Close, contextSettings);
    window_3.setSize(old_size);
    window_3.setPosition(old_pos);
    if (F2==0 || record_screen==1) window_3.setVisible(false);
//    if (record_screen==1) window_3.setVisible(false);
//    if (record_screen==1 || plot_all==1) window_3.setVisible(false);
    if (record_screen==0) window_3.setVerticalSyncEnabled(false);
    window_3_active=1;
    window_3.clear(sf::Color(255, 128, 0, 255));
    window_3.display();
    loader_mutex.lock();
//        if (taskbar==1 && record_screen==0) {
//            ShowTaskBar(false);
//            taskbar=0;
//        }
        kill3=0;
    loader_mutex.unlock();
    while (window_3.isOpen() ) {
        int thetime; thetime=100;
        srand(time(0)+30);
        while (loader3_active==0) {
            static int r=128,g=128,b=128;
            r=r+(rand()*rand()+rand())%21-10;g=g+(rand()*rand()+rand())%21-10;b=b+(rand()*rand()+rand())%21-10;
            if (r>255) r=255;if (r<0) r=0;if (g>255) g=255;if (g<0) g=0;if (b>255) b=255;if (b<0) b=0;
            window_3.clear(sf::Color(r,g,b,255));
            window_3.display();
            sf::sleep(sf::milliseconds(100));
//            SFMLView1.requestFocus();
            if (F2==1 && record_screen==0) thetime--;
            if (thetime<=0) {
                loader_mutex.lock();
                    kill3=1;
                loader_mutex.unlock();
                if (kill1==1 && kill2==1 && kill3==1) helpme=0;
            }
            while (window_3.pollEvent(event3) || kill3==1 )
            {
                if (event3.type == sf::Event::Closed || kill3==1) {
                    old_size=window_3.getSize();
                    old_pos=window_3.getPosition();
                    loader_mutex.lock();
                        if (thetime<=0) kill3=0; else kill3=1;
                        window_3_active=0;
                        window_3.close();
                        loader3_active=0;
                    loader_mutex.unlock();
                    if (thetime<=0) printf("Thread3: Killing myself, exiting map loader thread\n");
                    else printf("Thread3: Killed, exiting map loader thread\n");
                    return;
                }
//                if (event3.type == sf::Event::TextEntered) if (event3.text.unicode < 128) HANDLECHAR((WPARAM)event3.text.unicode);
                if (event3.type == sf::Event::KeyPressed) {
                    switch (event3.key.code) {
                        case sf::Keyboard::Escape:
                            old_size=window_3.getSize();
                            old_pos=window_3.getPosition();
                            loader_mutex.lock();
                                window_3_active=0;
                                window_3.close();
                                kill3=1;
                                loader3_active=0;
                            loader_mutex.unlock();
                            printf("Thread3: Killed, exiting map loader thread\n");
                            return;
                            break;
                        default:
                            break;
                    }
                }
            }
        }
        int local_level;
        local_level=level;
        char local_LEVELDIR[500];
        strcpy(local_LEVELDIR,LEVELDIR);
        int local_get_map_zoom;
        local_get_map_zoom=SAS_ZOOM;
        local_SAS_ZOOM_DIRECTION=SAS_ZOOM_DIRECTION;
        strcpy(local_SAS_ORDER,SAS_ORDER);
        strcpy(local_URL,SAS_URL);
        int local_offset_picture_x;
        int local_offset_picture_y;
        local_offset_picture_x=offset_picture_x;
        local_offset_picture_y=offset_picture_y;

        int ending=0;
        do_totalx=mytotal3.x;
        while (do_totalx==mytotal3.x && window_3.isOpen() && ending==0) {
            do_totaly=mytotal3.y;
    //        printf("Loop do_totalx=%d\n",do_totalx);
            while (do_totaly==mytotal3.y && window_3.isOpen() && ending==0) {
    //            printf("Loop do_totaly=%d\n",do_totaly);

                map_x=((local_offset_picture_x+do_totalx)*1920)/256;
                offset_x=((local_offset_picture_x+do_totalx)*1920-map_x*256)%256;
//                map_x=(do_totalx*1920-SAS_STARTX_a)/256;
//                offset_x=(do_totalx*1920-SAS_STARTX_a)%256;
//                offset_x=(do_totalx*1920-SAS_STARTX_a+256)%256;
//                map_x=do_totalx*1920/256; offset_x=(do_totalx*1920)%256;
                int map_x_start=map_x;
                int notile=0;
                int tiles_in_map=(int)pow(2.0,(local_get_map_zoom));
//                int tiles_in_map=(int)pow(2.0,(17-local_get_map_zoom));
//                ending=0;
                while (window_3.isOpen() && ending==0)
                {

//                    if (map_x+local_get_map_x<0) map_x=-local_get_map_x;
                    while ( (map_x*256 <= (local_offset_picture_x+do_totalx+1)*1920+256) && (map_x<tiles_in_map) && notile==0  ) {
//                    while ( (map_x*256 < (do_totalx+1)*1920+256) && (map_x+local_get_map_x<tiles_in_map) && notile==0 && ending==0 && ((map_x-map_x_start)*256-offset_x<1920) ) {
//                        if (map_x+local_get_map_x<0) continue;

                        map_y=((local_offset_picture_y+do_totaly)*1080)/256;
                        offset_y=((local_offset_picture_y+do_totaly)*1080-map_y*256)%256;
//                        map_y=(do_totaly*1080-SAS_STARTY_a)/256;
//                        offset_y=(do_totaly*1080-SAS_STARTY_a)%256;
//                        offset_y=(do_totaly*1080-SAS_STARTY_a+256)%256;
//                        map_y=do_totaly*1080/256; offset_y=(do_totaly*1080)%256;
                        int map_y_start=map_y;
                        notile=0;
//                        if (map_y+local_get_map_y<0) map_y=-local_get_map_y;
                        while ( (map_y*256 < (local_offset_picture_y+do_totaly+1)*1080+256) && (map_y<tiles_in_map) && notile==0 ) {
//                        while ( (map_y*256 <= (do_totaly+1)*1080+256) && (map_y+local_get_map_y<tiles_in_map) && notile==0 && ending==0 && ((map_y-map_y_start)*256-offset_y<1080) )  {
//                            if (map_y+local_get_map_y<0) continue;
                            if (local_SAS_ZOOM_DIRECTION<0)
                                if (strcmp(local_SAS_ORDER,"XYZ")==0)
                                    sprintf(url,local_URL,map_x,map_y,-local_SAS_ZOOM_DIRECTION-local_get_map_zoom);
                                else
                                    sprintf(url,local_URL,-local_SAS_ZOOM_DIRECTION-local_get_map_zoom,map_y,map_x);
                            else
                                if (strcmp(local_SAS_ORDER,"XYZ")==0)
                                    sprintf(url,local_URL,map_x,map_y,local_get_map_zoom+local_SAS_ZOOM_DIRECTION);
                                else if (strcmp(local_SAS_ORDER,"ZXY")==0)
                                    sprintf(url,local_URL,local_get_map_zoom+local_SAS_ZOOM_DIRECTION,map_x,map_y);
                                else
                                    sprintf(url,local_URL,local_get_map_zoom+local_SAS_ZOOM_DIRECTION,map_y,map_x);
                            char ip[200];
                            char page[4000];
                            if (url[0]>='0' && url[0]<='9') {
                                int dummy;
                                if (toupper(url[5])=='S') sscanf(url, "%dhttps://%199[^/]/%199[^\n]",&dummy, ip,page );
                                else sscanf(url, "%dhttp://%199[^/]/%199[^\n]",&dummy, ip,page);
                                strcpy(page,ip);
                                sprintf(ip,"%s-%d",page,dummy);
                                strcpy(page,url);
                                strcpy(url,&page[1]);
                            } else {
                                if (toupper(url[4])=='S') sscanf(url, "https://%199[^/]/%199[^\n]", ip,page );
                                else sscanf(url, "http://%199[^/]/%199[^\n]", ip,page);
                            }
                            if (strlen(SAS_DIR)>0) {
                                char kwijl[1000];
                                strcpy(kwijl,SAS_DIR);
                                strcat(kwijl,"/z%d/%d/%d.png");
                                sprintf(line,kwijl,local_get_map_zoom,map_y,map_x);
                            } else {
                                sprintf(line,"%s/%s/map.z%d/y%d/x%d.png",MAPDIR,ip,local_get_map_zoom,map_y,map_x);
                            }
//                            sprintf(line,"%s/map.z%d/y%d/x%d.png",MAPDIR,local_get_map_zoom,local_get_map_y+map_y,local_get_map_x+map_x);
/*
                            if (local_SAS_ZOOM_DIRECTION<0)
                                if (strcmp(local_SAS_ORDER,"XYZ")==0)
                                    sprintf(url,SAS_URL,local_get_map_x+map_x,local_get_map_y+map_y,-local_SAS_ZOOM_DIRECTION-local_get_map_zoom);
                                else
                                    sprintf(url,SAS_URL,-local_SAS_ZOOM_DIRECTION-local_get_map_zoom,local_get_map_y+map_y,local_get_map_x+map_x);
                            else
                                if (strcmp(local_SAS_ORDER,"XYZ")==0)
                                    sprintf(url,SAS_URL,local_get_map_x+map_x,local_get_map_y+map_y,local_get_map_zoom+local_SAS_ZOOM_DIRECTION);
                                else if (strcmp(SAS_ORDER,"ZXY")==0)
                                    sprintf(url,SAS_URL,local_get_map_zoom+local_SAS_ZOOM_DIRECTION,local_get_map_x+map_x,local_get_map_y+map_y);
                                else
                                    sprintf(url,SAS_URL,local_get_map_zoom+local_SAS_ZOOM_DIRECTION,local_get_map_y+map_y,local_get_map_x+map_x);
                            char ip[200];
                            char page[4000];
                            if (url[0]>='0' && url[0]<='9') {
                                int dummy;
                                if (toupper(url[5])=='S') sscanf(url, "%dhttps://%199[^/]/%199[^\n]",&dummy, ip,page );
                                else sscanf(url, "%dhttp://%199[^/]/%199[^\n]",&dummy, ip,page);
                                strcpy(page,ip);
                                sprintf(ip,"%s-%d",page,dummy);
                                strcpy(page,url);
                                strcpy(url,&page[1]);
                            } else {
                                if (toupper(url[4])=='S') sscanf(url, "https://%199[^/]/%199[^\n]", ip,page );
                                else sscanf(url, "http://%199[^/]/%199[^\n]", ip,page);
                            }
                            if (local_SAS_ZOOM_DIRECTION<0)
                                sprintf(line,"%s/%s/map.z%d/y%d/x%d.png",MAPDIR,ip,local_get_map_zoom,local_get_map_y+map_y,local_get_map_x+map_x);
                            else
                                sprintf(line,"%s/%s/map.z%d/y%d/x%d.png",MAPDIR,ip,local_get_map_zoom,local_get_map_y+map_y,local_get_map_x+map_x);
//                            sprintf(line,"%s/map.z%d/y%d/x%d.png",MAPDIR,local_get_map_zoom,local_get_map_y+map_y,local_get_map_x+map_x);
*/
                            int res=0;
                            if (file_exists3(line)) {
//                                printf("Thread3: File exists, skipping: %s\n",line);
                                res=0;
                                map_y++;
                                continue;
                            }
                            else {
//                    sprintf(url,SAS_URL,local_get_map_x+map_x,local_get_map_y+map_y,17-local_get_map_zoom);
//                                sprintf(url,SAS_URL,local_get_map_x+map_x,local_get_map_y+map_y,local_get_map_zoom);
                                res=GetGoogleMap(url,&result);
                                CHECKDIR(MAPDIR,ip,local_get_map_zoom,map_y);
/*
                                char nop[100];
                                DIR* dir;
                                strcpy(dirname,MAPDIR);while (replace_str(dirname,"/","\\\\"));
//                                loader_mutex.lock();
                                dir = opendir(dirname);
                                int msgboxID=0;
                                if (!dir)
                                {
                                    mkdir(dirname);
                                    dir = opendir(dirname);
                                    if (!dir) {msgboxID=MessageBox(NULL, "CANNOT CREATE DIRECOTRY FOR", (char*)line,MB_OK); }
                                    else  closedir(dir);
                                } else closedir(dir);

                                sprintf(nop,"\\%s",ip);
                                strcat(dirname,nop);
                                dir = opendir(dirname);
                                if (!dir)
                                {
                                    mkdir(dirname);
                                    dir = opendir(dirname);
                                    if (!dir) {msgboxID=MessageBox(NULL, "CANNOT CREATE DIRECOTRY FOR", (char*)line,MB_OK); }
                                    else closedir(dir);
                                } else closedir(dir);


                                sprintf(nop,"\\map.z%d",local_get_map_zoom);
                                strcat(dirname,nop);
                                dir = opendir(dirname);
                                if (!dir)
                                {
                                    mkdir(dirname);
                                    dir = opendir(dirname);
                                    if (!dir) {msgboxID=MessageBox(NULL, "CANNOT CREATE DIRECOTRY FOR", (char*)line,MB_OK); }
                                    else closedir(dir);
                                } else closedir(dir);
                                sprintf(nop,"\\y%d",map_y);
                                strcat(dirname,nop);
                                dir = opendir(dirname);
                                if (!dir)
                                {
                                    mkdir(dirname);
                                    dir = opendir(dirname);
                                    if (!dir) {msgboxID=MessageBox(NULL, "CANNOT CREATE DIRECOTRY FOR", (char*)line,MB_OK); }
                                    else closedir(dir);
                                } else closedir(dir);
//                                loader_mutex.unlock();
*/

                                if (res!=0) {
                                    printf("%s NOT LOADED. BITMAP X=%d,Y=%d\n",url,do_totalx,do_totaly);
                                    m_sprite.setTexture(mytex,true);
                                    m_sprite.setTextureRect({0,0,256,256});
                                    m_sprite.setPosition(0,0);
                                    window_3.clear(sf::Color(0,0,0,255));
                                    window_3.draw(m_sprite);
                                    window_3.display();
                                    if (internetfile==0 && !(movieextern==0)) {
                                        if (texture_from_internet.getSize()!=sf::Vector2u(256+20,256+20)) {
                                            texture_from_internet.create(256,256);
                                            add_border(&texture_from_internet);
                                        }
                                        texture_from_internet.update(mytex,10,10);
                                    }
//                                    mytex.copyToImage().saveToFile(line);
                                    loader_mutex.lock();
                                    char filenaam[1000];
                                    sprintf(filenaam,"%s/error.txt",MAPDIR);
                                    FILE* file = fopen (filenaam, "a");
                                    if (file!=NULL)
                                    {
                                        strcpy(dirname,line);
                                        while (replace_str(dirname,"/","\\"));
                                        fprintf (file, "del %s\n",dirname);
                                        fclose (file);
                                    }
                                    if (error_win3==0) {
                                        sprintf(filenaam,"%s/%dx%d/error.txt",local_LEVELDIR,BITMAPSX,BITMAPSY);
                                        file = fopen (filenaam, "a");
                                        if (file!=NULL)
                                        {
                                            sprintf(filenaam,"%s\\%dx%d\\%03d\\picture.%06d.%06d.png",local_LEVELDIR,BITMAPSX,BITMAPSY,local_level,(do_totaly),(do_totalx));
                                            while (replace_str(filenaam,"/","\\"));
                                            fprintf (file, "del %s\n",filenaam);
                                            fclose (file);
                                        }
                                        sprintf(filenaam,"%s/error.txt",MAPDIR);
                                        file = fopen (filenaam, "a");
                                        if (file!=NULL)
                                        {
                                            sprintf (filenaam, "%s\\map.z%d\\pictures\\y%d\\picture.%06d.%06d.png",local_LEVELDIR,local_get_map_zoom,local_offset_picture_y+do_totaly,local_offset_picture_y+do_totaly,local_offset_picture_x+do_totalx);
                                            while (replace_str(filenaam,"/","\\"));
                                            fprintf (file, "del %s\n",filenaam);
                                            fclose (file);
                                        }
                                        error_win3=1;
                                    }
                                    loader_mutex.unlock();
                                } else {
//                                    printf("%s     LOADED. BITMAP X=%d,Y=%d\n",url,do_totalx,do_totaly);
                                    m_sprite.setTexture(result,true);
                                    m_sprite.setTextureRect({0,0,256,256});
                                    m_sprite.setPosition(0,0);
                                    window_3.clear(sf::Color(0,0,0,255));
                                    window_3.draw(m_sprite);
                                    window_3.display();
//                                    printf("Thread3: Saving to file: %s\n",line);

                                    loader_mutex.lock();
                                    if (internetfile==0 && !(movieextern==0)) {
                                        if (texture_from_internet.getSize()!=sf::Vector2u(256+20,256+20)) {
                                            texture_from_internet.create(256,256);
                                            add_border(&texture_from_internet);
                                        }
                                        texture_from_internet.update(result,10,10);
                                    }
                                    result.copyToImage().saveToFile(line);
                                    loader_mutex.unlock();
                                }
                            }
                            if (res==0) {
                            }
                            else
                            {
//                                printf("Thread3: Not loaded.\n");
//                                notile=1;
//                                map_end_y=1;
                            }
                            if (notile==0) {
                                map_y++;
                            }
                            while (window_3.pollEvent(event3) || kill3==1)
                            {
                                if (event3.type == sf::Event::Closed || kill3==1) {
                                    printf("Thread3: Killed, exiting map loader thread\n");
                                    old_size=window_3.getSize();
                                    old_pos=window_3.getPosition();
                                    loader_mutex.lock();
                                        window_3_active=0;
                                        window_3.close();
                                        kill3=1;
                                        loader3_active=0;
                                    loader_mutex.unlock();
                                    return;
                                }
//                                if (event3.type == sf::Event::TextEntered) if (event3.text.unicode < 128) HANDLECHAR((WPARAM)event3.text.unicode);
                                if (event3.type == sf::Event::KeyPressed) {
                                    switch (event3.key.code) {
                                        case sf::Keyboard::Escape:
                                            old_size=window_3.getSize();
                                            old_pos=window_3.getPosition();
                                            loader_mutex.lock();
                                                window_3_active=0;
                                                window_3.close();
                                                kill3=1;
                                                loader3_active=0;
                                            loader_mutex.unlock();
                                            printf("Thread3: Killed, exiting map loader thread\n");
                                            return;
                                            break;
                                        default:
                                            break;
                                    }
                                }
                            }
                        }
                        if ( (map_y==map_y_start && notile==1) || map_y>=tiles_in_map) {
//                        if ( (map_y==map_y_start && notile==1) || map_y+local_get_map_y>=tiles_in_map) {
//                            loader3_active=0;
//                            notile=1;
//                            ending=1;
                            ending3_y=do_totaly;
//                            window_3_active=0;
//                            window_3.close();kill3=1;
//                            printf("Thread3: Exiting map loader thread\n");
//                            return ;
                        }
//                        else
//                        {

//                            notile=0;
                            map_x++;
                            if (map_x>=tiles_in_map && map_y>=tiles_in_map) {
//                            if (local_get_map_x+map_x>=tiles_in_map && local_get_map_y+map_y>=tiles_in_map) {
                                loader3_active=0;
                                notile=1;
                                ending=1;
                                ending3_x=do_totalx;
                            }
//                        }
                        while (window_3.pollEvent(event3) || kill3==1)
                        {
                            if (event3.type == sf::Event::Closed || kill3==1) {
                                printf("Thread3: Killed, exiting map loader thread\n");
                                old_size=window_3.getSize();
                                old_pos=window_3.getPosition();
                                loader_mutex.lock();
                                    window_3_active=0;
                                    window_3.close();
                                    kill3=1;
                                    loader3_active=0;
                                loader_mutex.unlock();
                                return;
                            }
//                            if (event3.type == sf::Event::TextEntered) if (event3.text.unicode < 128) HANDLECHAR((WPARAM)event3.text.unicode);
                            if (event3.type == sf::Event::KeyPressed) {
                                switch (event3.key.code) {
                                    case sf::Keyboard::Escape:
                                        old_size=window_3.getSize();
                                        old_pos=window_3.getPosition();
                                        loader_mutex.lock();
                                            window_3_active=0;
                                            window_3.close();
                                            kill3=1;
                                            loader3_active=0;
                                        loader_mutex.unlock();
                                        printf("Thread3: Killed, exiting map loader thread\n");
                                        return;
                                        break;
                                    default:
                                        break;
                                }
                            }
                        }
                    }
                    ending=1;
    //                window_3_active=0;
    //                window_3.close();kill3=1;
                }
                do_totaly++;
            }
            do_totalx++;
        }
        loader3_active=0;
    }

    printf("Thread3: Exiting map loader thread\n");
    old_size=window_3.getSize();
    old_pos=window_3.getPosition();
    window_3.clear(sf::Color(255,0,0,255));
    window_3.display();
    sf::sleep(sf::milliseconds(1500));
    loader_mutex.lock();
        window_3_active=0;
        window_3.close();
        kill3=1;
        loader3_active=0;
    loader_mutex.unlock();
    return ;
}

sf::Thread *thread_ar[1000];
char type_ar[1000];
int ref_num_ar[1000];
int status_ar[1000];
char file_ar[1000][200];
char url_ar[1000][300];
char mapdir_ar[1000][300];
char ip_ar[1000][300];
int get_map_zoom_ar[1000];
int map_y_ar[1000];
int map_x_ar[1000];

void start_thread_load_internet(int num, sf::Texture * texture);
void start_thread_load_file(int num, sf::Texture * texture);
void start_thread_get_tile(int num, sf::Texture * texture);


int insert_entry(char * type, char * file, char * url, int ref_num, sf::Texture * texture,char * MAPDIR,char *ip,int get_map_zoom,int map_y, int map_x) {
    static int num=-1;
//    printf("%d ",num);
    num++;
    if (num>=1000) num=0;
    int ret_val=num;
    strcpy(file_ar[num],file);
    strcpy(url_ar[num],url);
    strcpy(ip_ar[num],ip);
    strcpy(mapdir_ar[num],MAPDIR);
    ref_num_ar[num]=ref_num;
    get_map_zoom_ar[num]=get_map_zoom;
    map_y_ar[num]=map_y;
    map_x_ar[num]=map_x;
    if (strcmp(type,"LOADFILE")==0) {
        type_ar[num]=1;
        status_ar[num]=0;
        start_thread_load_file(num,texture);
    }
    else if (strcmp(type,"LOADINTERNET")==0) {
        type_ar[num]=2;
        status_ar[num]=4;
        start_thread_load_internet(num,texture);
    }
    else if (strcmp(type,"GETTILE")==0) {
        if (generate_tiles) {
//            sf::sleep(sf::milliseconds(5));
            type_ar[num]=4;
        }
        else type_ar[num]=3;
        status_ar[num]=0;
        start_thread_get_tile(num,texture);
    } else {
        printf("Error insert entry, no type specified, skipping\n");
        num--;
        return -1;
    }
    return ret_val;
}

int print_entry(int num) {
    printf("ENTRY=%3d ",num);
    printf("REF=%3d ",ref_num_ar[num]);
    printf("TYPE=%d ",type_ar[num]);
    printf("FILE=%s ",file_ar[num]);
    printf("URL=%s ",url_ar[num]);
    printf("STATUS=%d ",status_ar[num]);
    return ref_num_ar[num];
}

int status_entry(int num) {
    return status_ar[num];
}

void start_thread(int num);

sf::Texture *texture1;

int texture_set;

void start_thread_load_file(int num, sf::Texture * texture) {
    texture_set=0;
    texture1=texture;
    start_thread(num);
    while (texture_set==0) sf::sleep(sf::milliseconds(1));
}

void start_thread_load_internet(int num, sf::Texture * texture) {
    texture_set=0;
    texture1=texture;
    start_thread(num);
    while (texture_set==0) sf::sleep(sf::milliseconds(1));
}

void loadit(int num);
void start_thread_get_tile(int num, sf::Texture * texture) {
    texture_set=0;
    texture1=texture;
    if (generate_tiles) {
        loadit(num);
    } else {
        start_thread(num);
        while (texture_set==0) sf::sleep(sf::milliseconds(1));
    }
}

sf::Mutex locky;

void loadit(int num) {
    sf::Texture * local_texture;

    local_texture=texture1;
    texture_set=1;
    if (type_ar[num]==1) { //load file
        int load_good=local_texture->loadFromFile(file_ar[num]);
        if (load_good) {
//            printf("Loaded file : %s\n",file_ar[num]);
            status_ar[num]|=1;
        } else {
            printf("Load file error loadit() : %s\n",file_ar[num]);
            status_ar[num]|=8;
        }
    } else if (type_ar[num]==2) { //load internet
        while (internet_threads>=4) sf::sleep(sf::milliseconds(50));
        internet_threads_mutex.lock();
        internet_threads++;
        internet_threads_mutex.unlock();
        if (GetGoogleMap(url_ar[num],local_texture)==0) {
            internet_threads_mutex.lock();
            internet_threads--;
            internet_threads_mutex.unlock();
//            printf("Loaded internet : %s\n",file_ar[num]);
            status_ar[num]|=1;
            local_texture->copyToImage().saveToFile(file_ar[num]);
//            printf("Saved internet : %s\n",file_ar[num]);
            status_ar[num]|=2;
        } else {
            printf("Load internet error loadit() : %s\n",file_ar[num]);
            status_ar[num]|=8;
            internet_threads_mutex.lock();
            internet_threads--;
            internet_threads_mutex.unlock();
        }
    } else if (type_ar[num]==3) { //load internet
        if (file_exists3(file_ar[num])) {
            int load_good=local_texture->loadFromFile(file_ar[num]);
            if (load_good) {
    //            printf("Loaded file : %s\n",file_ar[num]);
                status_ar[num]|=1;
            } else {
                printf("Load file error loadit() : %s\n",file_ar[num]);
                status_ar[num]|=8;
            }
        } else {
            if (count_errors>10) {
                    status_ar[num]|=8;
                    return;
            }
            status_ar[num]=4;
            CHECKDIR(mapdir_ar[num],ip_ar[num],get_map_zoom_ar[num],map_y_ar[num]);
            while (internet_threads>=3) sf::sleep(sf::milliseconds(50));
            internet_threads_mutex.lock();
            internet_threads++;
            internet_threads_mutex.unlock();
            int ret;
            ret=GetGoogleMap(url_ar[num],local_texture);
            if (ret!=0) {
                printf("Retry 1: %s\n",url_ar[num]);
                ret=GetGoogleMap(url_ar[num],local_texture);
                if (ret!=0) {
                    printf("Retry 2: %s\n",url_ar[num]);
                    ret=GetGoogleMap(url_ar[num],local_texture);
                }
            }
            if (ret==0) {
                sf::Texture loc_text;
                loc_text.create(local_texture->getSize().x,local_texture->getSize().y);
                loc_text.update(*local_texture);
                internet_threads_mutex.lock();
                internet_threads--;
                internet_threads_mutex.unlock();
    //            printf("Loaded internet : %s\n",file_ar[num]);
                status_ar[num]|=1;
                loc_text.copyToImage().saveToFile(file_ar[num]);
//                local_text->copyToImage().saveToFile(file_ar[num]);
    //            printf("Saved internet : %s\n",file_ar[num]);
                status_ar[num]|=2;
            } else {
                printf("Load internet error loadit() : %s\n",file_ar[num]);
                status_ar[num]|=8;
                internet_threads_mutex.lock();
                internet_threads--;
                internet_threads_mutex.unlock();
            }
        }
    } else if (type_ar[num]==4) { //generate tiles
//        local_texture->loadFromFile("resources/border.png");
        char write[200];
        printf("TILE X=%d Y=%d Z=%d\n",map_x_ar[num],map_y_ar[num],get_map_zoom_ar[num]);
        static sf::RenderTexture * gen_tile=NULL;
        static sf::RectangleShape square;
        if (gen_tile==NULL) {
            gen_tile = new sf::RenderTexture();
            gen_tile->create(256,256,false);
            square.setFillColor(sf::Color(0,0,0,0));
            square.setOutlineThickness(1.0);
            square.setPosition(1.0,1.0);
            square.setOutlineColor(sf::Color(0,0,0,255));
            square.setSize({254,254});
        }
        gen_tile->clear(sf::Color(   (int)((double)map_x_ar[num]/pow(2.0,(double)get_map_zoom_ar[num])*256),
                                    (int)((double)map_y_ar[num]/pow(2.0,(double)get_map_zoom_ar[num])*256),
                                    (int)( (double)map_x_ar[num]/pow(2.0,(double)get_map_zoom_ar[num])*(double)map_y_ar[num]/pow(2.0,(double)get_map_zoom_ar[num]) *256),
                                 255));
        gen_tile->draw(square);
        sprintf(write,"ZOOM=%d",get_map_zoom_ar[num]);
        mydraw_texture(write,10,10,sf::Color(255,0,0,10),sf::Color(255,255,255,255),gen_tile);
        sprintf(write,"TILE X=%d",map_x_ar[num]);
        mydraw_texture(write,10,10+32,sf::Color(255,0,0,10),sf::Color(255,255,255,255),gen_tile);
        sprintf(write,"TILE Y=%d",map_y_ar[num]);
        mydraw_texture(write,10,10+32*2,sf::Color(255,0,0,10),sf::Color(255,255,255,255),gen_tile);

        gen_tile->display();
        local_texture->create(256,256);
        local_texture->update(gen_tile->getTexture());
        status_ar[num]|=1;
    } else {
        printf("Thread error, unknown type\n");
    }
    if (F2==0) printf(".");
}

void start_thread(int num) {
    if (thread_ar[num]==NULL) {
//    if (thread_ar[num]!=NULL) {
//        delete thread_ar[num];
        thread_ar[num]=new sf::Thread(&loadit,num);
    }
    thread_ar[num]->launch();
}

void CHECKDIR(char * MAPDIR,char *ip,int get_map_zoom,int map_y) {
    char nop[100];
    char dirname[1000];
    DIR* dir;
    strcpy(dirname,MAPDIR);while (replace_str(dirname,"/","\\\\"));
    dir = opendir(dirname);
    int msgboxID=0;
    if (!dir)
    {
        mkdir(dirname);
        dir = opendir(dirname);
        if (!dir) {msgboxID=MessageBox(NULL, "CANNOT CREATE DIRECTORY FOR", (char*)dirname,MB_OK); }
        else  closedir(dir);
    } else closedir(dir);

    sprintf(nop,"\\%s",ip);
    strcat(dirname,nop);
    dir = opendir(dirname);
    if (!dir)
    {
        mkdir(dirname);
        dir = opendir(dirname);
        if (!dir) {msgboxID=MessageBox(NULL, "CANNOT CREATE DIRECTORY FOR", (char*)dirname,MB_OK); }
        else closedir(dir);
    } else closedir(dir);

    sprintf(nop,"\\map.z%d",get_map_zoom);
    strcat(dirname,nop);
    dir = opendir(dirname);
    if (!dir)
    {
        mkdir(dirname);
        dir = opendir(dirname);
        if (!dir) {msgboxID=MessageBox(NULL, "CANNOT CREATE DIRECTORY FOR", (char*)dirname,MB_OK); }
        else closedir(dir);
    } else closedir(dir);

    sprintf(nop,"\\y%d",map_y);
    strcat(dirname,nop);
    dir = opendir(dirname);
    if (!dir)
    {
        mkdir(dirname);
        dir = opendir(dirname);
        if (!dir) {msgboxID=MessageBox(NULL, "CANNOT CREATE DIRECTORY FOR", (char*)dirname,MB_OK); }
        else closedir(dir);
    } else closedir(dir);
    return;
}

extern sf::Text mytext3;
extern int blend_tiles;

int gen_tile(char * type, char * file, char * url, int ref_num, sf::Texture * local_texture,char * MAPDIR,char *ip,int get_map_zoom,int map_y,int map_x,
             int offsetx,int offsety,int totalx,int totaly) {
    char write[200];
//    printf("TILE X=%d Y=%d Z=%d\n",map_x,map_y,get_map_zoom);
//    static sf::RenderTexture * gen_tile=NULL;
    static sf::RectangleShape square;
    static int first=0;
//    if (gen_tile==NULL) {
    int trans;
    if (first==0) {
        first=1;
//        gen_tile = new sf::RenderTexture();
//        gen_tile->create(256,256,false);
        square.setOutlineThickness(2.0);
        square.setPosition(2.0,2.0);
        square.setSize({252,252});
    }
    if (blend_tiles==1) {
        if (shade_map==1 && generate_tiles==1) {
            trans=64;
            square.setOutlineColor(sf::Color(255,255,255,64));
        }
        else {
            trans=0;
            square.setOutlineColor(sf::Color(128,128,128,255));
        }
    } else {
        square.setOutlineColor(sf::Color(128,128,128,255));
        trans=255;
    }

    square.setPosition(1.0+offsetx,1.0+offsety);
    square.setFillColor(sf::Color(  255-(int)((double)map_x/pow(2.0,(double)get_map_zoom)*256),
                                    (int)((double)map_y/pow(2.0,(double)get_map_zoom)*256),
                                128, trans));

    if (fragment_shader==1) {
        if (shader_ok==0) {
            strcpy(error_msg2,"NO SHADER SELECTED, CTRL-S PLOT SHADER OFF, ALT-F2 SELECT SHADER");
            error_flag2=1;
        } else {
            picture_states.shader = &picture_shader;
        }
        float scalex=1.0,scaley=1.0;
        if (movie==0) {
            if (!buffer_shader==1) picture_shader.setUniform("texture_buffer", texture_from_movie_new);
            if (!buffer_shader==1) picture_shader.setUniform("iResolution_buffer",  sf::Vector2f( texture_from_movie_new.getSize().x,texture_from_movie_new.getSize().y) );
            scalex=sprite_from_movie.getScale().x*texture_from_movie_new.getSize().x/1920.0;
            scaley=sprite_from_movie.getScale().y*texture_from_movie_new.getSize().y/1080.0;
        }  else if (movie2==0) {
            if (!buffer_shader==1) picture_shader.setUniform("texture_buffer", texture_from_movie2_new);
            if (!buffer_shader==1) picture_shader.setUniform("iResolution_buffer",  sf::Vector2f( texture_from_movie2_new.getSize().x,texture_from_movie2_new.getSize().y) );
            scalex=sprite_from_movie2.getScale().x*texture_from_movie2_new.getSize().x/1920.0;
            scaley=sprite_from_movie2.getScale().y*texture_from_movie2_new.getSize().y/1080.0;
        } else if (ffmpegfile==0) {
            if (!buffer_shader==1) picture_shader.setUniform("texture_buffer", texture_from_ffmpeg);
            if (!buffer_shader==1) picture_shader.setUniform("iResolution_buffer",  sf::Vector2f( texture_from_ffmpeg.getSize().x,texture_from_ffmpeg.getSize().y) );
            scalex=sprite_from_ffmpeg.getScale().x*texture_from_ffmpeg.getSize().x/1920.0;
            scaley=sprite_from_ffmpeg.getScale().y*texture_from_ffmpeg.getSize().y/1080.0;
        } else if (internetfile==0) {
            if (!buffer_shader==1) picture_shader.setUniform("texture_buffer", texture_from_internet);
            if (!buffer_shader==1) picture_shader.setUniform("iResolution_buffer",  sf::Vector2f( texture_from_internet.getSize().x,texture_from_internet.getSize().y) );
            scalex=sprite_from_internet.getScale().x*texture_from_internet.getSize().x/1920.0;
            scaley=sprite_from_internet.getScale().y*texture_from_internet.getSize().y/1080.0;
        }

        picture_shader.setUniform("pos_correction", sf::Vector2f(offsetx+
                                                                 fmod( (double)(-map_x*256) , pow(2.0,(double)(get_map_zoom+8)) ) ,
                                                                 -offsety+1080-256
                                                                 -256.0*(pow(2.0,(double)get_map_zoom)-1.0)+fmod( (double)(map_y*256.0) , pow(2.0,(double)(get_map_zoom+8)) )
                                                                  ) );
        picture_shader.setUniform("iResolution",  sf::Vector2f( pow(2.0,get_map_zoom+8),pow(2.0,get_map_zoom+8) ) );

        picture_shader.setUniform("buffer_plot",  0 );
        picture_shader.setUniform("background_plot",  1 );
        picture_shader.setUniform("formula_on",  1 );
        picture_shader.setUniform("formula",  formula );
extern float set_time;
        picture_shader.setUniform("iTime",   (float)set_time );
    }
    if (fragment_shader) {
//        texturemaxinmempoint[used2[totalx][totaly]]->draw(square);
        texturemaxinmempoint[used2[totalx][totaly]]->draw(square,picture_states);
        square.setFillColor(sf::Color(0,0,0,0));
        texturemaxinmempoint[used2[totalx][totaly]]->draw(square);
    }
    else
        texturemaxinmempoint[used2[totalx][totaly]]->draw(square);


//    gen_tile->clear(sf::Color(   (int)((double)map_x/pow(2.0,(double)get_map_zoom)*256),
//                                (int)((double)map_y/pow(2.0,(double)get_map_zoom)*256),
//                                (int)( (double)map_x/pow(2.0,(double)get_map_zoom)+(double)map_y/pow(2.0,(double)get_map_zoom) *128),
//                             255));
//    gen_tile->draw(square);

//    sprintf(write,"ZOOM=%d",get_map_zoom);
//    mydraw_texture(write,10,10,sf::Color(128,128,128,100),sf::Color(255,255,255,255),gen_tile);
//    sprintf(write,"TILE X=%d",map_x_ar);
//    mydraw_texture(write,10,10+40,sf::Color(128,128,128,100),sf::Color(255,255,255,255),gen_tile);
//    sprintf(write,"TILE Y=%d",map_y_ar);
//    mydraw_texture(write,10,10+40*2,sf::Color(128,128,128,100),sf::Color(255,255,255,255),gen_tile);
    static sf::Color foreg=sf::Color(10,10,10,trans*2);
    static sf::Color backg=sf::Color(255,255,255,trans*3);

    mytext3.setCharacterSize(32);
    sprintf(write,"X=% d",map_x);
    mydraw_texture(write,2+offsetx,2+32*0+offsety,foreg,backg,texturemaxinmempoint[used2[totalx][totaly]]);
    sprintf(write,"Y=% d",map_y);
    mydraw_texture(write,2+offsetx,2+32*1+offsety,foreg,backg,texturemaxinmempoint[used2[totalx][totaly]]);
    sprintf(write,"Z=% d",get_map_zoom);
    mydraw_texture(write,2+offsetx,2+32*2+offsety,foreg,backg,texturemaxinmempoint[used2[totalx][totaly]]);

    int pixels_in_map=256*(int)pow(2.0,(get_map_zoom));
    double rel_x=(double)(map_x*256)/(double)(pixels_in_map);
    double rel_y=(double)(map_y*256)/(double)(pixels_in_map);
    double longitude=rel_x*360.0-180.0;
    double latitude=180.0/PI*atan(0.5 * (exp(PI-2.0*PI*rel_y) - exp(-(PI-2.0*PI*rel_y))));

    double one_degree_lat=111132.92-559.82*cos(latitude*2.0*PI/180.0)+1.175*cos(latitude*4.0*PI/180.0)-0.0023*cos(latitude*6.0*PI/180.0);
    double one_degree_lon=111412.84*cos(latitude*PI/180.0)-93.5*cos(latitude*3.0*PI/180.0)+0.118*cos(latitude*5.0*PI/180.0);

    rel_x=(double)((map_x+1)*256)/(double)(pixels_in_map);
    rel_y=(double)((map_y+1)*256)/(double)(pixels_in_map);
    double longitude2=rel_x*360.0-180.0;
    double latitude2=180.0/PI*atan(0.5 * (exp(PI-2.0*PI*rel_y) - exp(-(PI-2.0*PI*rel_y))));

    mytext3.setCharacterSize(24);
    sprintf(write,"LAT=% 12.8f",latitude);
    mydraw_texture(write,2+offsetx,2+32*3+offsety,foreg,backg,texturemaxinmempoint[used2[totalx][totaly]]);
    sprintf(write,"TO= % 12.8f",latitude2);
    mydraw_texture(write,2+offsetx,2+32*3+24*1+offsety,foreg,backg,texturemaxinmempoint[used2[totalx][totaly]]);
    sprintf(write,"LON=% 12.8f",longitude);
    mydraw_texture(write,2+offsetx,2+32*3+24*2+offsety,foreg,backg,texturemaxinmempoint[used2[totalx][totaly]]);
    sprintf(write,"TO= % 12.8f",longitude2);
    mydraw_texture(write,2+offsetx,2+32*3+24*3+offsety,foreg,backg,texturemaxinmempoint[used2[totalx][totaly]]);

    double width=fabs(longitude2-longitude)*one_degree_lon;
    double height=fabs(latitude2-latitude)*one_degree_lat;

    if (width<=1000)
        sprintf(write,"W=%12.2f M",width);
    else
        sprintf(write,"W=%12.2f KM",width/1000.0);
    mydraw_texture(write,2+offsetx,2+32*3+24*4+offsety,foreg,backg,texturemaxinmempoint[used2[totalx][totaly]]);
    if (height<=1000)
        sprintf(write,"H=%12.2f M",height);
    else
        sprintf(write,"H=%12.2f KM",height/1000.0);
    mydraw_texture(write,2+offsetx,2+32*3+24*5+offsety,foreg,backg,texturemaxinmempoint[used2[totalx][totaly]]);


//    gen_tile->display();
//    local_texture->create(256,256);
//    local_texture->update(gen_tile->getTexture());
    return ref_num;
}

void gen_picture(int totalx,int totaly) {
    static sf::RectangleShape square;
    static int first=0;

    if (first==0) {
        first=1;
        square.setFillColor(sf::Color(0,0,0,0));
        square.setOutlineThickness(2.0);
        square.setPosition(1.0,1.0);
        square.setOutlineColor(sf::Color(255,255,0,255));
        square.setSize({1920-2,1080-2});
        square.setPosition(1.0,1.0);
    }
    texturemaxinmempoint[used2[totalx][totaly]]->draw(square);
}
