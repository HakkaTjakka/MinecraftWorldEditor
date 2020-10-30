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
#include <unistd.h>
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
#include "MediaInfo.hpp"
#include <SFML/OpenGL.hpp>
#include <GL/glext.h>
#include <GL/glu.h>
#include <GL/gl.h>

extern int kleur_front;
extern int kleur_back;
int loaded_picture=0;
extern int eatmode;
extern int plot_all;
extern int render_picturex;
extern int render_picturey;
extern int render_posx;
extern int render_posy;
extern sf::Sprite *spritemaxinmempoint[];
extern MSG msg;
extern void HANDLEEVENTS();
extern int plot_all;
extern sf::Mutex user_mutex;
extern int ESCAPE;
extern int goexit;
extern int sync;
extern sf::Shader m_shader2;
extern sf::RenderStates states2;
extern int plot_shader;
extern void plot_all_ghosts(int picturex,int picturey);
extern int ghost;
extern int number;
extern int ghostmode;
extern sf::RenderWindow SFMLView1;
extern sf::RenderStates states;
extern int combine;
extern int yellow;
extern sf::Mutex loader_mutex;
extern int maxpixelsx;
extern int maxpixelsy;
extern double smooth_x;
extern double smooth_y;
extern int monitor_off;
int skipclear=0;
extern sf::Texture sfml_bitmaps;
extern sf::RenderTexture tussen_texture;
extern int replace_str(char *str, char *orig, char *rep);
extern char LEVELDIR[];
extern sf::Color background_color[];
void ReadOneBitmap(int picturex,int picturey);
extern int F2;
extern int MAXINMEM;
extern int error_flag;
extern int MAZEOFF;
extern int render_picturex;
extern int render_picturey;
extern int picturex;
extern int picturey;
extern int connected;
extern int remote_posx;
extern int remote_posy;
extern int totalpicturex;
extern int totalpicturey;
extern char **used;
extern void savedata(char *naam, int data);
extern char **changed;
extern int drawmazes;
extern int BITMAPSX;
extern int BITMAPSY;
extern int level;
extern char **files_mazes;
extern int totalfiles_mazes;
extern int totalfiles;
extern char **files;
extern sf::RenderTexture *texturemaxinmempoint[];
extern int  **used2;
extern char error_msg3[];
extern int error_flag3;
extern int BITMAPSX;
extern int BITMAPSY;
extern int totalchanged;
extern int totalused;
extern int used_maxinmem[];
extern int  **used2;
extern char writer[];
extern char error_msg5[];
extern int error_flag5;
extern void savedata(char *naam, int data);
extern int DONTSAVEFILES;
void ReadBitmaps4();
extern bool file_exists(const char * filename);

void go_save_some_bitmaps()
{
    int hoppa=0;
    int x,y;
    float verschilx;
    float verschily;
    float distance;
    float longest=0.0;
    int long_x=-1,long_y=-1;
    int long2_x=-1,long2_y=-1;
    char naam[500];
    float remote_distance;
    int remote_picturex;
    int remote_picturey;
    float fremote_picturex;
    float fremote_picturey;
    float remote_verschilx;
    float remote_verschily;
    float calculus=0;
//    float fpicturex=render_picturex+0.5;
//    float fpicturey=render_picturex+0.5;
//plotting
    float fpicturex=picturex+0.5;
    float fpicturey=picturey+0.5;
    float fdiff_distance;
    float fdiff_shortest=100000000.0;

    if (connected==1)
    {
        remote_picturex=remote_posx/1920;
        remote_picturey=remote_posy/1080;
        fremote_picturex=remote_picturex+0.5;
        fremote_picturey=remote_picturey+0.5;
    }

    loader_mutex.lock();
    monitor_off=1;
    loader_mutex.unlock();

    for (x=0; x<totalpicturex; x++)
    {
        for (y=0; y<totalpicturey; y++)
        {

            if (used[x][y]==1)
            {
                verschilx=fabs(x-fpicturex);
                if (verschilx>totalpicturex/2)  verschilx=totalpicturex-verschilx;
                verschily=fabs(y-fpicturey);
                if (verschily>totalpicturey/2)  verschily=totalpicturey-verschily;

                distance=sqrt(verschilx*verschilx+verschily*verschily);

                if (connected==1)
                {

                    remote_verschilx=fabs(x-fremote_picturex);
                    if (remote_verschilx>totalpicturex/2)
                        remote_verschilx=totalpicturex-remote_verschilx;

                    remote_verschily=fabs(y-fremote_picturey);
                    if (remote_verschily>totalpicturey/2)
                        remote_verschily=totalpicturey-remote_verschily;

                    remote_distance=sqrt(remote_verschilx*remote_verschilx+remote_verschily*remote_verschily);

                    if ((distance>longest && remote_distance>2 && distance>1) || (remote_distance>longest && distance>2 && remote_distance>1) )
                    {
//oeioei
                        if ( !( (x==render_picturex                     && y==render_picturey) ||
                                (x==(render_picturex+1)%totalpicturex   && y==render_picturey) ||
                                (x==render_picturex                     && y==(render_picturey+1)%totalpicturey) ||
                                (x==(render_picturex+1)%totalpicturex && y==(render_picturey+1)%totalpicturey))  )
                        {
                            if (long_x!=-1 )
                            {
                                if (distance>remote_distance)
                                    longest=distance;
                                else if ( remote_distance>distance)
                                    longest=remote_distance;
                                else
                                    longest=distance;
                                long_x=x;
                                long_y=y;
                            }
                        }
                    }
                }
                else
                {
//oeioei

extern int plot_all_factor;
                    if (plot_all) {
                        int fromx=-BITMAPSX/2+1;
                        if (fromx<-3-plot_all_factor) fromx=-3-plot_all_factor;

                        int tox=BITMAPSX/2;
                        if (tox>4+plot_all_factor) tox=4+plot_all_factor;

                        int fromy=-BITMAPSY/2+1;
                        if (fromy<-3-plot_all_factor) fromy=-3-plot_all_factor;

                        int toy=BITMAPSY/2;
                        if (toy>4+plot_all_factor) toy=4+plot_all_factor;

                        if (
                            !(x>=(fromx+render_picturex+totalpicturex)%totalpicturex    && x<=(tox+render_picturex)%totalpicturex   && y>=(fromy+render_picturey+totalpicturey)%totalpicturey   && y<=(toy+render_picturey)%totalpicturey ) &&
                            !(x>=(fromx+picturex+totalpicturex)%totalpicturex           && x<=(tox+picturex)%totalpicturex          && y>=(fromy+picturey+totalpicturey)%totalpicturey          && y<=(toy+picturey)%totalpicturey )
                            )
                        {
                            if (distance>longest)
                            {
                                longest=distance;
                                long_x=x;
                                long_y=y;
                            }
                        }
                    } else {
                        if ( !( (x==render_picturex                     && y==render_picturey) ||
                                (x==(render_picturex+1)%totalpicturex   && y==render_picturey) ||
                                (x==render_picturex                     && y==(render_picturey+1)%totalpicturey) ||
                                (x==(render_picturex+1)%totalpicturex   && y==(render_picturey+1)%totalpicturey))  &&
                             !( (x==picturex                            && y==picturey) ||
                                (x==(picturex+1)%totalpicturex          && y==picturey) ||
                                (x==picturex                            && y==(picturey+1)%totalpicturey) ||
                                (x==(picturex+1)%totalpicturex          && y==(picturey+1)%totalpicturey))
                             )
                        {
                            if (distance>longest && distance>2)
                            {
                                longest=distance;
                                long_x=x;
                                long_y=y;
                            }
                        }
                    }
                }
            }
        }
    }
//    if (long_x==-1 && long2_x!=-1)
//    {
//        long_x=long2_x;
//        long_y=long2_y;
//    }
//plotting
    if ( (long_x==picturex && long_y==picturey) || (long_x==(picturex+1)%totalpicturex && long_y==picturey) || (long_x==picturex && long_y==(picturey+1)%totalpicturey) || (long_x==(picturex+1)%totalpicturex && long_y==(picturey+1)%totalpicturey) )
//    if ( (long_x==render_picturex && long_y==render_picturey) || (long_x==(render_picturex+1)%totalpicturex && long_y==render_picturey) || (long_x==render_picturex && long_y==(render_picturey+1)%totalpicturey) || (long_x==(render_picturex+1)%totalpicturex && long_y==(render_picturey+1)%totalpicturey) )
    {
        long_x=-1;
        savedata((char*)"MESSED UP",0);
    }

    if (long_x!=-1)
    {
        if (changed[long_x][long_y]==1)
        {
            if (DONTSAVEFILES==0 || drawmazes==0 )
            {
                if (drawmazes==1)
                {
                    sprintf(naam,"%s/%dx%d/%03d/picture_maze.%06d.%06d.png",LEVELDIR,BITMAPSX,BITMAPSY,level,long_y,long_x);
                    if (MAZEOFF==1) {
                        if (file_exists(naam)) {
                            if (files_mazes[long_x][long_y]==0) totalfiles_mazes++;
                            files_mazes[long_x][long_y]=1;
                        }
                        else {
                            if (files_mazes[long_x][long_y]==1) totalfiles_mazes--;
                            files_mazes[long_x][long_y]=0;
                        }
                        error_flag=0;
                    }
                    else if (files_mazes[long_x][long_y]==0)
                    {
                        files_mazes[long_x][long_y]=1;
                        totalfiles_mazes++;
//                        if (MAZEOFF==0) totalfiles_mazes++;
                    }
                }
                else
                {
                    sprintf(naam,"%s/%dx%d/%03d/picture.%06d.%06d.png",LEVELDIR,BITMAPSX,BITMAPSY,level,long_y,long_x);
                    if (MAZEOFF==1) {
                        if (file_exists(naam)) {
                            if (files[long_x][long_y]==0) totalfiles++;
                            files[long_x][long_y]=1;
                        }
                        else {
                            if (files[long_x][long_y]==1) totalfiles--;
                            files[long_x][long_y]=0;
                        }
                        error_flag=0;
                    }
                    else if (files[long_x][long_y]==0)
                    {
                        files[long_x][long_y]=1;
//                        if (MAZEOFF==0) totalfiles++;
                        totalfiles++;
                    }
                }
//                printf("DONTSAVEFILES=%d drawmazes=%d saving file: %s\n",DONTSAVEFILES,drawmazes,naam);
                texturemaxinmempoint[used2[long_x][long_y]]->display();
                texturemaxinmempoint[used2[long_x][long_y]]->getTexture().copyToImage().saveToFile(naam);
                if (files[long_x][long_y])
                    texturemaxinmempoint[used2[long_x][long_y]]->clear(sf::Color(0,255,0,255));
                else
                    texturemaxinmempoint[used2[long_x][long_y]]->clear(sf::Color(0,255,255,255));
                texturemaxinmempoint[used2[long_x][long_y]]->display();
                if (strlen(error_msg3)>100) strcpy(error_msg3,"SAVED: ");
                strcat(error_msg3,naam);
                strcat(error_msg3," ");
                error_flag3=1;
            }
            else
            {
                if (drawmazes==1)
                {
                    sprintf(naam,"%s/%dx%d/%03d/picture_maze.%06d.%06d.png",LEVELDIR,BITMAPSX,BITMAPSY,level,long_y,long_x);
                }
                else
                {
                    sprintf(naam,"%s/%dx%d/%03d/picture.%06d.%06d.png",LEVELDIR,BITMAPSX,BITMAPSY,level,long_y,long_x);
                }
                if (file_exists(naam))
                    texturemaxinmempoint[used2[long_x][long_y]]->clear(sf::Color(255,255,0,255));
                else
                    texturemaxinmempoint[used2[long_x][long_y]]->clear(sf::Color(255,255,255,255));
                texturemaxinmempoint[used2[long_x][long_y]]->display();
                strcpy(error_msg3,"NOT SAVED: ");
                strcat(error_msg3,naam);
                strcat(error_msg3," ");
                error_flag3=1;
            }
            changed[long_x][long_y]=0;
            totalchanged--;
        }
        if (used[long_x][long_y]==1)
        {
            used[long_x][long_y]=0;
            totalused--;
            used_maxinmem[used2[long_x][long_y]]=0;
            sprintf(writer,"X=%d/Y=%d ",long_x,long_y);
            if (strlen(error_msg5)>100)
                strcpy(error_msg5,"DELETED: ");
            strcat(error_msg5,writer);
            error_flag5=1;
        } else {
            printf("Error go_save_some_bitmaps() long_x=%d long_y=%d\n",long_x,long_y);
        }
    }
    else
    {
        if (strlen(error_msg3)>100) strcpy(error_msg3,"SAVED: ");
        strcat(error_msg3,"MESSED UP ");
        savedata((char*)"MESSED UP",0);
        error_flag3=1;
    }
}

extern void putinmazeSFML(int totalx,int totaly);
void ReadSFML(char * naam, int x, int y, int draw);
void blitter(char * line, int mode);
extern char error_msg4[];
extern int error_flag4;
extern int loadbackground;

void LOADALLBITMAPS()
{
    int x,y;
    char naam[200];

    for (x=0; x<totalpicturex; x++)
    {
        for (y=0; y<totalpicturey; y++)
        {
            if (used[x][y]==1)
            {
                if (changed[x][y]==1)
                {
                    changed[x][y]=0;
                    totalchanged--;
                }

                if (drawmazes==0) {
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
                    if (files[x][y]==0  || loadbackground==0 )
                    {
//oeioei
                        if (loadbackground==0)
//                        if ( loadbackground==0 || !((x==picturex && y==picturey) ||
//                                                    (x==(picturex+1)%totalpicturex && y==picturey) ||
//                                                    (x==(picturex+1)%totalpicturex && y==(picturey+1)%totalpicturey )  ||
//                                                    (x==picturex && y==(picturey+1)%totalpicturey )  ))

                        {
                            used[x][y]=0;
                            totalused--;
                            used_maxinmem[used2[x][y]]=0;
                            used2[x][y]=0;
                            if (loadbackground==0)
                            {
//                                texturemaxinmempoint[used2[x][y]]->clear(background_color[drawmazes]);
                                putinmazeSFML(x,y);
                            }
                        }
                        else
                        {
                            texturemaxinmempoint[used2[x][y]]->clear(background_color[drawmazes]);
                            putinmazeSFML(x,y);
                        }
                    }
                    else
                    {
                        sprintf(naam,"%s/%dx%d/%03d/picture.%06d.%06d.png",LEVELDIR,BITMAPSX,BITMAPSY,level,y,x);
                        texturemaxinmempoint[used2[x][y]]->clear(background_color[drawmazes]);
                        ReadSFML(naam,x,y,0);
                    }

                    sprintf(writer,"RELOADING BITMAPS BACKGROUND X=%d/Y=%d ",x,y);
                    blitter(writer,1);
                } else {
                    if (MAZEOFF==1) {
                        sprintf(naam,"%s/%dx%d/%03d/picture_maze.%06d.%06d.png",LEVELDIR,BITMAPSX,BITMAPSY,level,y,x);
                        if (file_exists(naam)) {
                            if (files_mazes[x][y]==0) totalfiles_mazes++;
                            files_mazes[x][y]=1;
                        }
                        else {
                            if (files_mazes[x][y]==1) totalfiles_mazes--;
                            files_mazes[x][y]=0;
                        }
                        error_flag=0;
                    }
                    if (files_mazes[x][y]==0  || loadbackground==0 )
                    {

//oeioei
                        if ( loadbackground==0 )
//                        if ( loadbackground==0 || !((x==picturex && y==picturey) ||
//                                                    (x==(picturex+1)%totalpicturex && y==picturey) ||
//                                                    (x==(picturex+1)%totalpicturex && y==(picturey+1)%totalpicturey )  ||
//                                                    (x==picturex && y==(picturey+1)%totalpicturey )  ))
                        {
                            used[x][y]=0;
                            totalused--;
                            used_maxinmem[used2[x][y]]=0;
                            used2[x][y]=0;
                            if (loadbackground==0)
                            {
//                                texturemaxinmempoint[used2[x][y]]->clear(background_color[drawmazes]);
//                                texturemaxinmempoint[used2[x][y]]->clear(sf::Color(0,0,0,0));
                                putinmazeSFML(x,y);
                            }
                        }
                        else
                        {
                            texturemaxinmempoint[used2[x][y]]->clear(background_color[drawmazes]);
//                            texturemaxinmempoint[used2[x][y]]->clear(sf::Color(0,0,0,0));
                            used[x][y]=0;
                            totalused--;
                            used_maxinmem[used2[x][y]]=0;
                            ReadOneBitmap(x,y);
//                            putinmazeSFML(x,y);
                        }
                    }
                    else
                    {
                        sprintf(naam,"%s/%dx%d/%03d/picture_maze.%06d.%06d.png",LEVELDIR,BITMAPSX,BITMAPSY,level,y,x);
                        texturemaxinmempoint[used2[x][y]]->clear(background_color[drawmazes]);
                        ReadSFML(naam,x,y,0);
                    }

                    sprintf(writer,"RELOADING BITMAPS MAZE X=%d/Y=%d ",x,y);
                    blitter(writer,1);
                }
            }
        }
    }

    strcpy(error_msg4,"ALL BITMAPS RELOADED BITMAPS IN MEMORY CLEARED");
    error_flag4=1;
    return;
}

void LOADALLBITMAPS_MAZES()
{
    int x,y;
    char naam[200];

    for (x=0; x<totalpicturex; x++)
    {
        for (y=0; y<totalpicturey; y++)
        {
            if (used[x][y]==1)
            {
                if (changed[x][y]==1)
                {
                    changed[x][y]=0;
                    totalchanged--;
                }

                if (MAZEOFF==1) {
                    sprintf(naam,"%s/%dx%d/%03d/picture_maze.%06d.%06d.png",LEVELDIR,BITMAPSX,BITMAPSY,level,y,x);
                    if (file_exists(naam)) {
                        if (files_mazes[x][y]==0) totalfiles_mazes++;
                        files_mazes[x][y]=1;
                    }
                    else {
                        if (files_mazes[x][y]==1) totalfiles_mazes--;
                        files_mazes[x][y]=0;
                    }
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
                if ( files_mazes[x][y]==0 )
                {
//???????????oeioei
                    if ( !((x==picturex && y==picturey) ||
                                                (x==(picturex+1)%totalpicturex && y==picturey) ||
                                                (x==(picturex+1)%totalpicturex && y==(picturey+1)%totalpicturey )  ||
                                                (x==picturex && y==(picturey+1)%totalpicturey )  ))
                    {
                        used[x][y]=0;
                        totalused--;
                        used_maxinmem[used2[x][y]]=0;
//                        if (loadbackground==0)
//                        {
//                            texturemaxinmempoint[used2[x][y]]->clear(background_color[drawmazes]);
//                            sprintf(naam,"%s/%dx%d/%03d/picture_maze.%06d.%06d.png",LEVELDIR,BITMAPSX,BITMAPSY,level,y,x);
//                            ReadSFML(naam,x,y,0);
                            putinmazeSFML(x,y);
//                        }
                    }
                    else
                    {
//                        sprintf(naam,"%s/%dx%d/%03d/picture_maze.%06d.%06d.png",LEVELDIR,BITMAPSX,BITMAPSY,level,y,x);
//                        texturemaxinmempoint[used2[x][y]]->clear(background_color[drawmazes]);
//                        ReadSFML(naam,x,y,0);
                        putinmazeSFML(x,y);
                    }
                }
                else
                {
                    sprintf(naam,"%s/%dx%d/%03d/picture_maze.%06d.%06d.png",LEVELDIR,BITMAPSX,BITMAPSY,level,y,x);
//                    texturemaxinmempoint[used2[x][y]]->clear(background_color[drawmazes]);
//oeioeioei
                    ReadSFML(naam,x,y,0);
                }

                sprintf(writer,"RELOADING BITMAPS X=%d/Y=%d ",x,y);
                blitter(writer,1);
            }
        }
    }

    strcpy(error_msg4,"ALL BITMAPS RELOADED BITMAPS IN MEMORY CLEARED");
    error_flag4=1;
    return;
}

extern int maxpicturex;
extern int maxpicturey;
extern sf::Sprite spritedot;
extern sf::Sprite spritedot2;
extern int pen_mode;
extern sf::BlendMode MyBlend;

void RenderBlit(int mapx,int mapy, int xdest, int ydest, int width, int height, int xsource, int ysource)
{
//blender

    int totalx=picturex+mapx;
    int totaly=picturey+mapy;
    if (totalx>maxpicturex) totalx=0;
    if (totaly>maxpicturey) totaly=0;
    if (used[totalx][totaly]==0) return;

    spritedot.setPosition(xdest,ydest);

    if (pen_mode==1)
    {
        spritedot.setTextureRect(   { 0,6*72, width, height }  );
        texturemaxinmempoint[used2[totalx][totaly]]->draw(spritedot,MyBlend);
    }

    spritedot.setTextureRect(   { xsource, ysource,width, height }  );
    texturemaxinmempoint[used2[totalx][totaly]]->draw(spritedot);
    texturemaxinmempoint[used2[totalx][totaly]]->display();
    texturemaxinmempoint[used2[totalx][totaly]]->generateMipmap();
    if (changed[totalx][totaly]==0)
    {
        changed[totalx][totaly]=1;
        totalchanged++;
    }
}

void RenderBlitGlobal(int xdest, int ydest, int width, int height, int xsource, int ysource, sf::Texture * SourceTexture) {
    int picturex=xdest/1920;
    xdest=xdest-picturex*1920;
    int picturey=ydest/1080;
    ydest=ydest-picturey*1080;

    if (used[picturex][picturey]==0) ReadOneBitmap(picturex,picturey);

    static sf::Sprite local_sprite;
    static sf::Texture* local_texture=NULL;

    if (local_texture!=SourceTexture) {
        local_sprite.setTexture(*SourceTexture,false);
        local_texture=SourceTexture;
    }

    local_sprite.setTextureRect(   { xsource, ysource,width, height }  );
    local_sprite.setPosition(xdest,ydest);

    texturemaxinmempoint[used2[picturex][picturey]]->draw(local_sprite);

    if (changed[picturex][picturey]==0)
    {
        changed[picturex][picturey]=1;
        totalchanged++;
    }

}

void RenderBlitg(int totalx,int totaly, int xdest, int ydest, int width, int height, int xsource, int ysource)
{
//blender

    if (totalx>maxpicturex) totalx=0;
    if (totaly>maxpicturey) totaly=0;
    if (used[totalx][totaly]==0) return;

    spritedot.setPosition(xdest,ydest);

    if (pen_mode==1)
    {
        spritedot.setTextureRect(   { 0,6*72, width, height }  );
        texturemaxinmempoint[used2[totalx][totaly]]->draw(spritedot,MyBlend);
    }

    spritedot.setTextureRect(   { xsource, ysource,width, height }  );
    texturemaxinmempoint[used2[totalx][totaly]]->draw(spritedot);
    texturemaxinmempoint[used2[totalx][totaly]]->display();
    texturemaxinmempoint[used2[totalx][totaly]]->generateMipmap();
    if (changed[totalx][totaly]==0)
    {
        changed[totalx][totaly]=1;
        totalchanged++;
    }
}



void RenderBlit_total(int totalx,int totaly, int xdest, int ydest, int width, int height, int xsource, int ysource, int remote_pen_mode)
{
//blender

    spritedot.setPosition(xdest,ydest);

    if (remote_pen_mode==1)
    {

        spritedot.setTextureRect(   { 0,6*72,width, height }  );
        texturemaxinmempoint[used2[totalx][totaly]]->draw(spritedot,MyBlend);
    }

    spritedot.setTextureRect(   { xsource, ysource,width, height }  );
    texturemaxinmempoint[used2[totalx][totaly]]->draw(spritedot);
    texturemaxinmempoint[used2[totalx][totaly]]->display();

    if (plot_all) texturemaxinmempoint[used2[totalx][totaly]]->generateMipmap();
    if (changed[totalx][totaly]==0)
    {
        changed[totalx][totaly]=1;
        totalchanged++;
    }
}

void RenderBlit_adapt(int totalx,int totaly, int xdest, int ydest, int width, int height, int xsource, int ysource, int remote_pen_mode)
{
//blender

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
extern sf::Texture sfml_mazedot;
extern int smooth;

    if (remote_pen_mode==1)
    {
        if (kleur_front==1) {
//        if (kleur_front==1 || (kleur_back==1 && loadbackground==1)) {
            spritedot.setTextureRect(   { xsource,12*72,width, height }  );
            texturemaxinmempoint[used2[totalx][totaly]]->draw(spritedot,MyBlend);

            spritedot.setTextureRect(   { 0,6*72,width, height }  );
            texturemaxinmempoint[used2[totalx][totaly]]->draw(spritedot,MyBlend2);
        } else {
            spritedot.setTextureRect(   { xsource,12*72,width, height }  );
            texturemaxinmempoint[used2[totalx][totaly]]->draw(spritedot,MyBlend);
//            texturemaxinmempoint[used2[totalx][totaly]]->draw(spritedot,MyBlend);
        }
    }
    spritedot.setTextureRect(   { xsource, ysource,width, height }  );
    texturemaxinmempoint[used2[totalx][totaly]]->draw(spritedot);
    texturemaxinmempoint[used2[totalx][totaly]]->display();
    if (plot_all) texturemaxinmempoint[used2[totalx][totaly]]->generateMipmap();
    if (changed[totalx][totaly]==0)
    {
        changed[totalx][totaly]=1;
        totalchanged++;
    }
}


void RenderBlit2(float xdest, float ydest, int xsource, int ysource, int width, int height)
{
    if (plot_shader==2) {
        static int memy=0;
        if ((xsource>=8*64 && ysource<5*72)) { memy=ysource; return; }
        else if ((xsource>=12*64 && xsource<=15*64)) { memy=ysource-4*72; return; }
        if ((xsource>=64*10 && xsource<64*11) || (xsource>=64*16 && xsource<64*17)) {
                xsource=128*(8-(int)(ysource/72))+9;
                ysource=memy;

        }
        if (xsource>=8*64) return;
    }

extern int blending;
extern sf::RenderTexture texture_final;
extern int shade_main;
extern int blendit;

    if (yellow==0) {
        spritedot.setTextureRect(   { xsource, ysource,width, height }  );
        spritedot.setPosition(xdest,ydest);
        if (ghostmode==1 && plot_shader!=2) {
            if (blending>=1 || shade_main!=0 || blendit==1)
                texture_final.draw(spritedot,states);
            else
                SFMLView1.draw(spritedot,states);
        }
        else {
            if (blending>=1 || shade_main!=0 || blendit==1)
                texture_final.draw(spritedot);
            else
                SFMLView1.draw(spritedot);
        }
    } else {
        spritedot2.setTextureRect(   { xsource, ysource,width, height }  );
        spritedot2.setPosition(xdest,ydest);
        if (ghostmode==1 && plot_shader!=2) {
            if (blending>=1 || shade_main!=0 || blendit==1)
                texture_final.draw(spritedot2,states);
            else
                SFMLView1.draw(spritedot2,states);
        }
        else {
            if (blending>=1 || shade_main!=0 || blendit==1)
                texture_final.draw(spritedot2);
            else
                SFMLView1.draw(spritedot2);
        }
    }
}

void RenderBlit3(int xdest, int ydest, int xsource, int ysource, int width, int height, int x, int y)
{
    if (plot_shader==2) {
        static int memy=0;
        if ((xsource>=8*64 && ysource<5*72)) { memy=ysource; return; }
        else if ((xsource>=12*64 && xsource<=15*64)) { memy=ysource-4*72; return; }
        if ((xsource>=64*10 && xsource<64*11) || (xsource>=64*16 && xsource<64*17)) {
                xsource=128*(8-(int)(ysource/72))+9;
                ysource=memy;

        }
        if (xsource>=8*64) return;
    }
    if (yellow==0) {
        spritedot.setTextureRect(   { xsource, ysource,width, height }  );
        spritedot.setPosition(xdest,ydest);
        if (ghostmode==1 && plot_shader!=2)
            texturemaxinmempoint[used2[x][y]]->draw(spritedot,states2);
        else
            texturemaxinmempoint[used2[x][y]]->draw(spritedot);
    } else {
        spritedot2.setTextureRect(   { xsource, ysource,width, height }  );
        spritedot2.setPosition(xdest,ydest);
        if (ghostmode==1 && plot_shader!=2)
            texturemaxinmempoint[used2[x][y]]->draw(spritedot2,states2);
        else
            texturemaxinmempoint[used2[x][y]]->draw(spritedot2);
    }
}

extern sf::RenderTexture GHOSTtexture;
extern sf::Sprite GHOSTsprite;


extern void logfile(char *line);
extern int check_dir(int BITMAPSX,int BITMAPSY,int level);
extern char *line;
/*
                    if (files_mazes[x][y]==1) {
                        sf::RenderTexture tussen_texture;
                        tussen_texture.create(1920,1080);
                        tussen_texture.clear(sf::Color(0,0,0,255));
                        sprintf(naam,"%s/%dx%d/%03d/picture_maze.%06d.%06d.png",LEVELDIR,BITMAPSX,BITMAPSY,level,y,x);
                        sfml_bitmaps.loadFromFile(naam);
                        sf::Sprite sprite;
                        sprite.setTexture(texturemaxinmempoint[used2[x][y]]->getTexture(),true);
                        tussen_texture.draw(sprite);
                        sprite.setTexture(sfml_bitmaps,true);
                        tussen_texture.draw(sprite);
                        tussen_texture.display();
                        tussen_texture.getTexture().copyToImage().saveToFile(naam);
                    }
*/

void SAVEALLBITMAPS()
{
    int x;
    int y;
    int xx;
    int yy;
    char naam[400];

    logfile((char*)"Saving all bitmaps");

    check_dir(BITMAPSX,BITMAPSY,level);
    FILE *testfile;
    if (DONTSAVEFILES==0)
    {
        for (y=0; y<totalpicturey; y++)
        {
            for (x=0; x<totalpicturex; x++)
            {
                if (changed[x][y]==1 && drawmazes==0)
                {
//change2
                    sprintf(naam,"%s/%dx%d/%03d/picture.%06d.%06d.png",LEVELDIR,BITMAPSX,BITMAPSY,level,y,x);
                    texturemaxinmempoint[used2[x][y]]->display();
                    texturemaxinmempoint[used2[x][y]]->getTexture().copyToImage().saveToFile(naam);
                    if (MAZEOFF==1) {
                        if (file_exists(naam)) {
                            if (files[x][y]==0) totalfiles++;
                            files[x][y]=1;
                        }
                        else {
                            if (files[x][y]==1) totalfiles--;
                            files[x][y]=0;
                        }
                        error_flag=0;
                    } else if (files[x][y]==0)
                    {
                        files[x][y]=1;
                        totalfiles++;
                    }

                    changed[x][y]=0;
                    totalchanged--;

                    sprintf(line,"SAVING CHANGED BITMAPS ONLY=%d bitmaps\n", totalchanged);
                    blitter(line,1);

                } else if (drawmazes==1) {
                    sprintf(naam,"%s/%dx%d/%03d/picture_maze.%06d.%06d.png",LEVELDIR,BITMAPSX,BITMAPSY,level,y,x);
extern int SAVEALL;
//?????????
                    if (MAZEOFF==1) {
                        if (file_exists(naam)) {
                            if (files_mazes[x][y]==0) totalfiles_mazes++;
                            files_mazes[x][y]=1;
                        }
                        else {
                            if (files_mazes[x][y]==1) totalfiles_mazes--;
                            files_mazes[x][y]=0;
                        }
                        error_flag=0;
                    }
                    if (changed[x][y]==0 && files_mazes[x][y]==0 && SAVEALL==1 ) {
                        if (totalused>MAXINMEM)
                        {
                            if (F2==1)
                            {
                                strcat(line," SAVING BITMAP");
                                blitter(line,1);
                            }
                            go_save_some_bitmaps();
                            if (totalused>MAXINMEM+2)
                            {
                                go_save_some_bitmaps();
                                if (totalused>MAXINMEM+4)
                                {
                                    go_save_some_bitmaps();
                                }
                            }
                        }
                        ReadOneBitmap(x,y);
//ghosts
                        if (plot_shader>0 && ghost==1 && number>0) {
                            plot_all_ghosts(x,y);
                            texturemaxinmempoint[used2[x][y]]->display();
                            if (plot_all) texturemaxinmempoint[used2[x][y]]->generateMipmap();
                        }
                        texturemaxinmempoint[used2[x][y]]->getTexture().copyToImage().saveToFile(naam);
                        sprintf(line,"SAVING ALL MAZE BITMAPS = #%d\n", y+x*BITMAPSY);
                        blitter(line,1);
                        files_mazes[x][y]=1;
                        totalfiles_mazes++;
                    } else {
                        if (changed[x][y]==1 ) {
                            changed[x][y]=0;
                            totalchanged--;
                            texturemaxinmempoint[used2[x][y]]->getTexture().copyToImage().saveToFile(naam);
                            sprintf(line,"SAVING CHANGED MAZE BITMAPS = #%d\n", y+x*BITMAPSY);
                            blitter(line,1);
                            if (files_mazes[x][y]==0)
                            {
                                files_mazes[x][y]=1;
                                totalfiles_mazes++;
                            }
                        }
                    }
                }
            }
        }
    }
    return;
}

void CLEANBITMAPS()
{
    int x,y;
    for (x=0; x<totalpicturex; x++)
    {
        for (y=0; y<totalpicturey; y++)
        {
//change2
//             if (files[x][y]==1) {
//                  files[x][y]=0;
//                  totalfiles--;
//             }
            if (changed[x][y]==1)
            {
                changed[x][y]=0;
                totalchanged--;
            }
            if (used[x][y]==1)
            {
                used[x][y]=0;
                totalused--;
                used_maxinmem[used2[x][y]]=0;
            }
        }
    }
    return;
}

extern sf::Text text;
extern char **used;
extern int picturex;
extern int picturey;
extern int maxpicturex;
extern int maxpicturey;
extern int drawmazes;
extern char **files_mazes;
extern char **files;
extern int loadbackground;
extern void putinmazeSFML(int totalx,int totaly);
extern int BITMAPSX;
extern int BITMAPSY;
extern int level;
extern int totalpicturex;
extern int totalpicturey;
extern sf::RenderWindow SFMLView1;
extern char writer[];
extern void draw2(char *towrite, int xpos, int ypos, sf::Color inner, sf::Color outer);

void CreateAll()
{
    int plaatje=1;
    FILE * testfile;
    char naam[200];
    int x,y;
    int arx,ary;
    sf::Sprite sprite;
    int mazeprintx;
    int mazeprinty;
    int blokje;
    int numcreated=0;
    int numloaded=0;

    text.setCharacterSize(36);
    text.setFillColor(sf::Color::White);

/*
    for (x=0; x<=1; x++)
    {
        for (y=0; y<=1; y++)
        {
            if (used[(picturex+x)%(maxpicturex+1)][(picturey+y)%(maxpicturey+1)]==0)
            {
                if (drawmazes==1)
                {
                    if (MAZEOFF==1) {
                        sprintf(naam,"%s/%dx%d/%03d/picture_maze.%06d.%06d.png",LEVELDIR,BITMAPSX,BITMAPSY,level,(picturey+y)%(maxpicturey+1),(picturex+x)%(maxpicturex+1));
                        if (file_exists(naam)) {
                            if (files_mazes[(picturex+x)%(maxpicturex+1)][(picturey+y)%(maxpicturey+1)]==0) totalfiles_mazes++;
                            files_mazes[(picturex+x)%(maxpicturex+1)][(picturey+y)%(maxpicturey+1)]=1;
                        }
                        else {
                            if (files_mazes[(picturex+x)%(maxpicturex+1)][(picturey+y)%(maxpicturey+1)]==1) totalfiles_mazes--;
                            files_mazes[(picturex+x)%(maxpicturex+1)][(picturey+y)%(maxpicturey+1)]=0;
                        }
                        error_flag=0;
                    }
                    if (files_mazes[(picturex+x)%(maxpicturex+1)][(picturey+y)%(maxpicturey+1)]==0)
                    {
                        if (MAZEOFF==1) {
                            sprintf(naam,"%s/%dx%d/%03d/picture.%06d.%06d.png",LEVELDIR,BITMAPSX,BITMAPSY,level,(picturey+y)%(maxpicturey+1),(picturex+x)%(maxpicturex+1));
                            if (file_exists(naam)) {
                                if (files[(picturex+x)%(maxpicturex+1)][(picturey+y)%(maxpicturey+1)]==0) totalfiles++;
                                files[(picturex+x)%(maxpicturex+1)][(picturey+y)%(maxpicturey+1)]=1;
                            }
                            else {
                                if (files[(picturex+x)%(maxpicturex+1)][(picturey+y)%(maxpicturey+1)]==1) totalfiles--;
                                files[(picturex+x)%(maxpicturex+1)][(picturey+y)%(maxpicturey+1)]=0;
                            }
                            error_flag=0;
                        }
                        if (files[(picturex+x)%(maxpicturex+1)][(picturey+y)%(maxpicturey+1)]==0 || loadbackground==0)
                        {
                            putinmazeSFML((picturex+x)%(maxpicturex+1),(picturey+y)%(maxpicturey+1));
                        }
                        else
                        {
                            sprintf(naam,"%s/%dx%d/%03d/picture.%06d.%06d.png",LEVELDIR,BITMAPSX,BITMAPSY,level,(y+picturey)%(totalpicturey),(x+picturex)%(totalpicturex));
                            ReadSFML(naam,(picturex+x)%(maxpicturex+1),(picturey+y)%(maxpicturey+1),1);
                        }
                    }
                    else
                    {
                        sprintf(naam,"%s/%dx%d/%03d/picture_maze.%06d.%06d.png",LEVELDIR,BITMAPSX,BITMAPSY,level,(y+picturey)%(totalpicturey),(x+picturex)%(totalpicturex));
                        ReadSFML(naam,(picturex+x)%(maxpicturex+1),(picturey+y)%(maxpicturey+1),0);
                    }
                }
                else
                {
                    if (MAZEOFF==1) {
                        sprintf(naam,"%s/%dx%d/%03d/picture.%06d.%06d.png",LEVELDIR,BITMAPSX,BITMAPSY,level,(picturey+y)%(maxpicturey+1),(picturex+x)%(maxpicturex+1));
                        if (file_exists(naam)) {
                            if (files[(picturex+x)%(maxpicturex+1)][(picturey+y)%(maxpicturey+1)]==0) totalfiles++;
                            files[(picturex+x)%(maxpicturex+1)][(picturey+y)%(maxpicturey+1)]=1;
                        }
                        else {
                            if (files[(picturex+x)%(maxpicturex+1)][(picturey+y)%(maxpicturey+1)]==1) totalfiles--;
                            files[(picturex+x)%(maxpicturex+1)][(picturey+y)%(maxpicturey+1)]=0;
                        }
                        error_flag=0;
                    }
                    if (files[(picturex+x)%(maxpicturex+1)][(picturey+y)%(maxpicturey+1)]==0 || loadbackground==0)
                    {
                        putinmazeSFML((picturex+x)%(maxpicturex+1),(picturey+y)%(maxpicturey+1));
                    }
                    else
                    {
                        sprintf(naam,"%s/%dx%d/%03d/picture.%06d.%06d.png",LEVELDIR,BITMAPSX,BITMAPSY,level,(y+picturey)%(totalpicturey),(x+picturex)%(totalpicturex));
                        ReadSFML(naam,(picturex+x)%(maxpicturex+1),(picturey+y)%(maxpicturey+1),0);
                    }
                }
            }
        }
    }
*/
extern int perform_quit;
    for (arx=0; arx<=maxpicturex; arx++)
    {
        for (ary=0; ary<=maxpicturey; ary++)
        {
//            SFMLView1.clear(sf::Color(0,0,0,0));
//            glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
            if (perform_quit==0) {
                SFMLView1.setActive(true);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                SFMLView1.setActive(false);

                sprintf(writer,"LOADING AND/OR CREATING ALL TEXTURES: X=%d Y=%d TOTAL=%d",arx,ary,arx*(maxpicturey+1)+ary+1);
                draw2(writer,0,0,sf::Color::Blue,sf::Color::White);
            }

            if (MAZEOFF==1) {
                sprintf(naam,"%s/%dx%d/%03d/picture.%06d.%06d.png",LEVELDIR,BITMAPSX,BITMAPSY,level,ary,arx);
                if (file_exists(naam)) {
                    if (files[arx][ary]==0) totalfiles++;
                    files[arx][ary]=1;
                } else {
                    if (files[arx][ary]==1) totalfiles--;
                    files[arx][ary]=0;
                }
                sprintf(naam,"%s/%dx%d/%03d/picture_maze.%06d.%06d.png",LEVELDIR,BITMAPSX,BITMAPSY,level,ary,arx);
                if (file_exists(naam)) {
                    if (files_mazes[arx][ary]==0) totalfiles_mazes++;
                    files_mazes[arx][ary]=1;
                } else {
                    if (files_mazes[arx][ary]==1) totalfiles_mazes--;
                    files_mazes[arx][ary]=0;
                }
                error_flag=0;
            }
            if ( files[arx][ary]==0 )
                numcreated++;
            else
                numloaded++;

            if (perform_quit==0) {
                sprintf(writer,"CREATED: %d",numcreated);
                draw2(writer,0,36,sf::Color::Blue,sf::Color::White);
                sprintf(naam,"%s/%dx%d/%03d/picture.%06d.%06d.png",LEVELDIR,BITMAPSX,BITMAPSY,level,ary,arx);
                sprintf(writer,"LOADED: %d %s",numloaded,naam);
                draw2(writer,0,72,sf::Color::Blue,sf::Color::White);

                SFMLView1.display();
            } else {
            }

            if (used[arx][ary]==0)
            {
                if (drawmazes==1)
                {
                    if (files_mazes[arx][ary]==0)
                    {
                        if (files[arx][ary]==0 || loadbackground==0)
                        {
                            putinmazeSFML(arx,ary);
                        }
                        else
                        {
                            sprintf(naam,"%s/%dx%d/%03d/picture.%06d.%06d.png",LEVELDIR,BITMAPSX,BITMAPSY,level,ary,arx);
                            ReadSFML(naam,arx,ary,1);
                        }
                    }
                    else
                    {
                        sprintf(naam,"%s/%dx%d/%03d/picture_maze.%06d.%06d.png",LEVELDIR,BITMAPSX,BITMAPSY,level,ary,arx);
                        ReadSFML(naam,arx,ary,0);
                    }
                }
                else
                {
                    if (files[arx][ary]==0 || loadbackground==0)
                    {
                        putinmazeSFML(arx,ary);
                    }
                    else
                    {
                        sprintf(naam,"%s/%dx%d/%03d/picture.%06d.%06d.png",LEVELDIR,BITMAPSX,BITMAPSY,level,ary,arx);
                        ReadSFML(naam,arx,ary,0);
                    }
                }
            }
        }
    }
    text.setCharacterSize(24);
//    SFMLView1.clear(sf::Color(0,0,0,0));
//    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
//    SFMLView1.setActive(true);
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    SFMLView1.setActive(false);
}

extern int MAXINMEM;
extern int used_maxinmem[];
extern int  **used2;
extern int totalused;
extern void savedata(char *naam, int data);
extern sf::Texture sfml_bitmaps;
extern sf::RenderTexture *texturemaxinmempoint[];
extern void DRAWMAZE(int totalx,int totaly);
extern char error_msg2[];
extern int error_flag2;

void ReadSFML(char * naam, int x, int y, int draw)
{
    int arx,ary;
    int findempty=0;
    int found=0;
    arx=x;
    ary=y;

    user_mutex.lock();
    if (used[arx][ary]==0)
    {
        while (findempty<(MAXINMEM+12) && found==0)
        {
            if (used_maxinmem[findempty]==0)
            {
                used_maxinmem[findempty]=1;
                used2[arx][ary]=findempty;
                used[arx][ary]=1;
                totalused++;
                found=1;
            }
            findempty++;
            if (found==1)
                break;
        }
        if (found==0) {
            savedata((char*)"no free spot READSFML",findempty);
            printf("Error 1 no free spot ReadSFML() : %s\n",naam);
        }
    }
    user_mutex.unlock();

//    SFMLView1.setActive(true);
extern sf::RenderTexture texturemaxinmem[];
//    printf("loading: %s\m",naam);
//    texturemaxinmem[used2[x][y]].setActive(true);

    if (!sfml_bitmaps.loadFromFile(naam)) {
        savedata((char*)"Error loading picture",findempty);
        printf("Error 2 loading picture ReadSFML() : %s\n",naam);
    }
    sf::Sprite sprite;
    sprite.setTexture(sfml_bitmaps,true);
    sprite.setTextureRect({0,0,1920,1080});
    sprite.setPosition(0,0);

//    SFMLView1.setActive(false);
//    texturemaxinmem[used2[x][y]].setActive(false);
//    if (skipclear==0)
//            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        texturemaxinmempoint[used2[arx][ary]]->clear(background_color[drawmazes]);
//    else
//        texturemaxinmempoint[used2[arx][ary]]->clear(sf::Color(0,0,0,0));


//    texturemaxinmem[used2[x][y]].setActive(true);
    texturemaxinmempoint[used2[arx][ary]]->draw(sprite);
    texturemaxinmempoint[used2[arx][ary]]->display();

//    texturemaxinmem[used2[x][y]].setActive(false);
    if (draw==1 || eatmode==1) {
        loaded_picture=1;
        DRAWMAZE(arx,ary);
        loaded_picture=0;
    }
    else {
        if (plot_all==1) texturemaxinmempoint[used2[arx][ary]]->generateMipmap();
    }
    if (strlen(error_msg2)>100) strcpy(error_msg2,"LOADED: ");
    strcat(error_msg2,naam);
    strcat(error_msg2," ");
    error_flag2=1;
}
extern void update_plot_all2();

void blitter(char * line,int mode)
{
    static int blit=50;

    if (F2==0) return;
    blit--;
    if (blit<=0 || mode==1)
    {
//hoppa
//        ReadBitmaps4();
        SFMLView1.clear(background_color[drawmazes]);
//        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
//        SFMLView1.setActive(true);
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//        SFMLView1.setActive(false);
        blit=100;
        if (plot_all) update_plot_all2();
        else {
            ReadBitmaps4();
            int x,y;
            for (x=0; x<=1; x++)
            {
                for (y=0; y<=1; y++)
                {
                    int arx=(render_picturex+x)%(maxpicturex+1);
                    int ary=(render_picturey+y)%(maxpicturey+1);
                    if (texturemaxinmempoint[used2[arx][ary]]==NULL) {
                            printf("NULL!!!\n");
    //                    savedata((char*)"ITS NULL!!!!",0);
                    }
                    else {
                        spritemaxinmempoint[used2[arx][ary]]->setPosition(render_posx+x*1920,render_posy+y*1080);
                        SFMLView1.draw(*spritemaxinmempoint[used2[arx][ary]]);
                        spritemaxinmempoint[used2[arx][ary]]->setPosition(0.0,0.0);
                    }
                }
            }
            draw2(line,0,32,sf::Color::Blue,sf::Color::White);
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
        SFMLView1.display();
    }
    loader_mutex.lock();
    monitor_off=1;
    loader_mutex.unlock();
}

extern sf::Mutex render_mutex;

void blitter2()
{
//        ReadBitmaps4();
//        SFMLView1.clear(sf::Color(0,0,0,0));
//        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        SFMLView1.setActive(true);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        SFMLView1.setActive(false);
        int x,y;
        render_mutex.lock();
        for (x=0; x<=1; x++)
            for (y=0; y<=1; y++)
            {
                int arx=(render_picturex+x)%(maxpicturex+1);
                int ary=(render_picturey+y)%(maxpicturey+1);
                if (used[arx][ary]==0) {
//                if (texturemaxinmempoint[used2[arx][ary]]==NULL) {
                }
                else {
                    spritemaxinmempoint[used2[arx][ary]]->setPosition((float)(x*1920)-(float)fmod(smooth_x+(double)maxpixelsx,1920.0),(float)(y*1080)-(float)fmod(smooth_y+(double)maxpixelsy,1080.0));
//                    spritemaxinmempoint[used2[arx][ary]]->setPosition(posx+x*1920,posy+y*1080);
                    SFMLView1.draw(*spritemaxinmempoint[used2[arx][ary]]);
                    spritemaxinmempoint[used2[arx][ary]]->setPosition(0.0,0.0);
                }
            }
        render_mutex.unlock();
        loader_mutex.lock();
        monitor_off=1;
        loader_mutex.unlock();
}

void ReadOneBitmap(int picturex,int picturey)
{
    char naam[200];
    int x=0,y=0;

    if (used[(picturex+x)%(maxpicturex+1)][(picturey+y)%(maxpicturey+1)]==0)
    {
        if (MAZEOFF==1) {
            sprintf(naam,"%s/%dx%d/%03d/picture.%06d.%06d.png",LEVELDIR,BITMAPSX,BITMAPSY,level,picturey,picturex);
            if (file_exists(naam)) {
                if (files[picturex][picturey]==0) totalfiles++;
                files[picturex][picturey]=1;
            }
            else {
                if (files[picturex][picturey]==1) totalfiles--;
                files[picturex][picturey]=0;
            }
            sprintf(naam,"%s/%dx%d/%03d/picture_maze.%06d.%06d.png",LEVELDIR,BITMAPSX,BITMAPSY,level,picturey,picturex);
            if (file_exists(naam)) {
                if (files_mazes[picturex][picturey]==0) totalfiles_mazes++;
                files_mazes[picturex][picturey]=1;
            }
            else {
                if (files_mazes[picturex][picturey]==1) totalfiles_mazes--;
                files_mazes[picturex][picturey]=0;
            }
            error_flag=0;
        }
        if (drawmazes==1)
        {
            if (files_mazes[(picturex+x)%(maxpicturex+1)][(picturey+y)%(maxpicturey+1)]==0)
            {
                if (files[(picturex+x)%(maxpicturex+1)][(picturey+y)%(maxpicturey+1)]==0 || loadbackground==0)
                {
                    putinmazeSFML((picturex+x)%(maxpicturex+1),(picturey+y)%(maxpicturey+1));
                }
                else
                {
                    sprintf(naam,"%s/%dx%d/%03d/picture.%06d.%06d.png",LEVELDIR,BITMAPSX,BITMAPSY,level,(y+picturey)%(totalpicturey),(x+picturex)%(totalpicturex));
                    ReadSFML(naam,(picturex+x)%(maxpicturex+1),(picturey+y)%(maxpicturey+1),1);
                }
            }
            else
            {
                sprintf(naam,"%s/%dx%d/%03d/picture_maze.%06d.%06d.png",LEVELDIR,BITMAPSX,BITMAPSY,level,(y+picturey)%(totalpicturey),(x+picturex)%(totalpicturex));
                ReadSFML(naam,(picturex+x)%(maxpicturex+1),(picturey+y)%(maxpicturey+1),0);
            }
        }
        else
        {
            if (files[(picturex+x)%(maxpicturex+1)][(picturey+y)%(maxpicturey+1)]==0 || loadbackground==0)
            {
                putinmazeSFML((picturex+x)%(maxpicturex+1),(picturey+y)%(maxpicturey+1));
            }
            else
            {
                sprintf(naam,"%s/%dx%d/%03d/picture.%06d.%06d.png",LEVELDIR,BITMAPSX,BITMAPSY,level,(y+picturey)%(totalpicturey),(x+picturex)%(totalpicturex));
                ReadSFML(naam,(picturex+x)%(maxpicturex+1),(picturey+y)%(maxpicturey+1),0);
            }
        }
    }
}

void ReadBitmaps2()
{
    char naam[200];
    int x,y;

    for (x=0; x<=1; x++)
    {
        for (y=0; y<=1; y++)
        {
            if (used[(picturex+x)%(maxpicturex+1)][(picturey+y)%(maxpicturey+1)]==0)
            {
                if (MAZEOFF==1) {
                    sprintf(naam,"%s/%dx%d/%03d/picture.%06d.%06d.png",LEVELDIR,BITMAPSX,BITMAPSY,level,(picturey+y)%(maxpicturey+1),(picturex+x)%(maxpicturex+1));
                    if (file_exists(naam)) {
                        if (files[(picturex+x)%(maxpicturex+1)][(picturey+y)%(maxpicturey+1)]==0) totalfiles++;
                        files[(picturex+x)%(maxpicturex+1)][(picturey+y)%(maxpicturey+1)]=1;
                    }
                    else {
                        if (files[(picturex+x)%(maxpicturex+1)][(picturey+y)%(maxpicturey+1)]==1) totalfiles--;
                        files[(picturex+x)%(maxpicturex+1)][(picturey+y)%(maxpicturey+1)]=0;
                    }
                    sprintf(naam,"%s/%dx%d/%03d/picture_maze.%06d.%06d.png",LEVELDIR,BITMAPSX,BITMAPSY,level,(picturey+y)%(maxpicturey+1),(picturex+x)%(maxpicturex+1));
                    if (file_exists(naam)) {
                        if (files_mazes[(picturex+x)%(maxpicturex+1)][(picturey+y)%(maxpicturey+1)]==0) totalfiles_mazes++;
                        files_mazes[(picturex+x)%(maxpicturex+1)][(picturey+y)%(maxpicturey+1)]=1;
                    }
                    else {
                        if (files_mazes[(picturex+x)%(maxpicturex+1)][(picturey+y)%(maxpicturey+1)]==1) totalfiles_mazes--;
                        files_mazes[(picturex+x)%(maxpicturex+1)][(picturey+y)%(maxpicturey+1)]=0;
                    }
                    error_flag=0;
                }
                if (drawmazes==1)
                {
                    if (files_mazes[(picturex+x)%(maxpicturex+1)][(picturey+y)%(maxpicturey+1)]==0)
                    {
                        if (files[(picturex+x)%(maxpicturex+1)][(picturey+y)%(maxpicturey+1)]==0 || loadbackground==0)
                        {
                            putinmazeSFML((picturex+x)%(maxpicturex+1),(picturey+y)%(maxpicturey+1));
                        }
                        else
                        {
                            sprintf(naam,"%s/%dx%d/%03d/picture.%06d.%06d.png",LEVELDIR,BITMAPSX,BITMAPSY,level,(y+picturey)%(totalpicturey),(x+picturex)%(totalpicturex));
                            ReadSFML(naam,(picturex+x)%(maxpicturex+1),(picturey+y)%(maxpicturey+1),1);
                        }
                    }
                    else
                    {
//                        sprintf(naam,"%s/%dx%d/%03d/picture.%06d.%06d.png",LEVELDIR,BITMAPSX,BITMAPSY,level,(y+picturey)%(totalpicturey),(x+picturex)%(totalpicturex));
//testing
//                        skipclear=1;
//                        ReadSFML(naam,(picturex+x)%(maxpicturex+1),(picturey+y)%(maxpicturey+1),0);
//                        skipclear=0;
                        sprintf(naam,"%s/%dx%d/%03d/picture_maze.%06d.%06d.png",LEVELDIR,BITMAPSX,BITMAPSY,level,(y+picturey)%(totalpicturey),(x+picturex)%(totalpicturex));
                        ReadSFML(naam,(picturex+x)%(maxpicturex+1),(picturey+y)%(maxpicturey+1),0);
                    }
                }
                else
                {
                    if (files[(picturex+x)%(maxpicturex+1)][(picturey+y)%(maxpicturey+1)]==0 || loadbackground==0)
                    {
                        putinmazeSFML((picturex+x)%(maxpicturex+1),(picturey+y)%(maxpicturey+1));
                    }
                    else
                    {
                        sprintf(naam,"%s/%dx%d/%03d/picture.%06d.%06d.png",LEVELDIR,BITMAPSX,BITMAPSY,level,(y+picturey)%(totalpicturey),(x+picturex)%(totalpicturex));
                        ReadSFML(naam,(picturex+x)%(maxpicturex+1),(picturey+y)%(maxpicturey+1),0);
                    }
                }
            }
        }
    }
}

void ReadBitmaps4()
{
    static char naam[200];
    static int x,y;

    for (x=0; x<=1; x++)
    {
        for (y=0; y<=1; y++)
        {
            if (used[(render_picturex+x)%(maxpicturex+1)][(render_picturey+y)%(maxpicturey+1)]==0)
            {
                if (MAZEOFF==1) {
                    sprintf(naam,"%s/%dx%d/%03d/picture.%06d.%06d.png",LEVELDIR,BITMAPSX,BITMAPSY,level,(render_picturey+y)%(maxpicturey+1),(render_picturex+x)%(maxpicturex+1));
                    if (file_exists(naam)) {
                        if (files[(render_picturex+x)%(maxpicturex+1)][(render_picturey+y)%(maxpicturey+1)]==0) totalfiles++;
                        files[(render_picturex+x)%(maxpicturex+1)][(render_picturey+y)%(maxpicturey+1)]=1;
                    }
                    else {
                        if (files[(render_picturex+x)%(maxpicturex+1)][(render_picturey+y)%(maxpicturey+1)]==1) totalfiles--;
                        files[(render_picturex+x)%(maxpicturex+1)][(render_picturey+y)%(maxpicturey+1)]=0;
                    }
                    sprintf(naam,"%s/%dx%d/%03d/picture_maze.%06d.%06d.png",LEVELDIR,BITMAPSX,BITMAPSY,level,(render_picturey+y)%(maxpicturey+1),(render_picturex+x)%(maxpicturex+1));
                    if (file_exists(naam)) {
                        if (files_mazes[(render_picturex+x)%(maxpicturex+1)][(render_picturey+y)%(maxpicturey+1)]==0) totalfiles_mazes++;
                        files_mazes[(render_picturex+x)%(maxpicturex+1)][(render_picturey+y)%(maxpicturey+1)]=1;
                    }
                    else {
                        if (files_mazes[(render_picturex+x)%(maxpicturex+1)][(render_picturey+y)%(maxpicturey+1)]==1) totalfiles_mazes--;
                        files_mazes[(render_picturex+x)%(maxpicturex+1)][(render_picturey+y)%(maxpicturey+1)]=0;
                    }
                    error_flag=0;
                }
/*
                if (MAZEOFF==1) {
                    sprintf(naam,"%s/%dx%d/%03d/picture.%06d.%06d.png",LEVELDIR,BITMAPSX,BITMAPSY,level,(render_picturey+y)%(maxpicturey+1),(render_picturex+x)%(maxpicturex+1));
                    if (file_exists(naam)) files[(render_picturex+x)%(maxpicturex+1)][(render_picturey+y)%(maxpicturey+1)]=1;
                    else files[(render_picturex+x)%(maxpicturex+1)][(render_picturey+y)%(maxpicturey+1)]=0;
                    sprintf(naam,"%s/%dx%d/%03d/picture_maze.%06d.%06d.png",LEVELDIR,BITMAPSX,BITMAPSY,level,(render_picturey+y)%(maxpicturey+1),(render_picturex+x)%(maxpicturex+1));
                    if (file_exists(naam)) files_mazes[(render_picturex+x)%(maxpicturex+1)][(render_picturey+y)%(maxpicturey+1)]=1;
                    else files_mazes[(render_picturex+x)%(maxpicturex+1)][(render_picturey+y)%(maxpicturey+1)]=0;
                    error_flag=0;
                }
*/
                if (drawmazes==1)
                {
                    if (files_mazes[(render_picturex+x)%(maxpicturex+1)][(render_picturey+y)%(maxpicturey+1)]==0)
                    {
                        if (files[(render_picturex+x)%(maxpicturex+1)][(render_picturey+y)%(maxpicturey+1)]==0 || loadbackground==0)
                        {
                            putinmazeSFML((render_picturex+x)%(maxpicturex+1),(render_picturey+y)%(maxpicturey+1));
                        }
                        else
                        {
                            sprintf(naam,"%s/%dx%d/%03d/picture.%06d.%06d.png",LEVELDIR,BITMAPSX,BITMAPSY,level,(y+render_picturey)%(totalpicturey),(x+render_picturex)%(totalpicturex));
                            ReadSFML(naam,(render_picturex+x)%(maxpicturex+1),(render_picturey+y)%(maxpicturey+1),1);
                        }
                    }
                    else
                    {
                        sprintf(naam,"%s/%dx%d/%03d/picture_maze.%06d.%06d.png",LEVELDIR,BITMAPSX,BITMAPSY,level,(y+render_picturey)%(totalpicturey),(x+render_picturex)%(totalpicturex));
                        ReadSFML(naam,(render_picturex+x)%(maxpicturex+1),(render_picturey+y)%(maxpicturey+1),0);
                    }
                }
                else
                {
                    if (files[(render_picturex+x)%(maxpicturex+1)][(render_picturey+y)%(maxpicturey+1)]==0 || loadbackground==0)
                    {
                        putinmazeSFML((render_picturex+x)%(maxpicturex+1),(render_picturey+y)%(maxpicturey+1));
                    }
                    else
                    {
                        sprintf(naam,"%s/%dx%d/%03d/picture.%06d.%06d.png",LEVELDIR,BITMAPSX,BITMAPSY,level,(y+render_picturey)%(totalpicturey),(x+render_picturex)%(totalpicturex));
                        ReadSFML(naam,(render_picturex+x)%(maxpicturex+1),(render_picturey+y)%(maxpicturey+1),0);
                    }
                }
            }
        }
    }
}

void ReadBitmaps2_remote(int picturex, int picturey)
{
    char naam[200];
    int x,y;

    for (x=0; x<=1; x++)
    {
        for (y=0; y<=1; y++)
        {
            if (MAZEOFF==1) {
                sprintf(naam,"%s/%dx%d/%03d/picture.%06d.%06d.png",LEVELDIR,BITMAPSX,BITMAPSY,level,(picturey+y)%(maxpicturey+1),(picturex+x)%(maxpicturex+1));
                if (file_exists(naam)) {
                    if (files[(picturex+x)%(maxpicturex+1)][(picturey+y)%(maxpicturey+1)]==0) totalfiles++;
                    files[(picturex+x)%(maxpicturex+1)][(picturey+y)%(maxpicturey+1)]=1;
                }
                else {
                    if (files[(picturex+x)%(maxpicturex+1)][(picturey+y)%(maxpicturey+1)]==1) totalfiles--;
                    files[(picturex+x)%(maxpicturex+1)][(picturey+y)%(maxpicturey+1)]=0;
                }
                sprintf(naam,"%s/%dx%d/%03d/picture_maze.%06d.%06d.png",LEVELDIR,BITMAPSX,BITMAPSY,level,(picturey+y)%(maxpicturey+1),(picturex+x)%(maxpicturex+1));
                if (file_exists(naam)) {
                    if (files_mazes[(picturex+x)%(maxpicturex+1)][(picturey+y)%(maxpicturey+1)]==0) totalfiles_mazes++;
                    files_mazes[(picturex+x)%(maxpicturex+1)][(picturey+y)%(maxpicturey+1)]=1;
                }
                else {
                    if (files_mazes[(picturex+x)%(maxpicturex+1)][(picturey+y)%(maxpicturey+1)]==1) totalfiles_mazes--;
                    files_mazes[(picturex+x)%(maxpicturex+1)][(picturey+y)%(maxpicturey+1)]=0;
                }
                error_flag=0;
            }
            if (used[(picturex+x)%(maxpicturex+1)][(picturey+y)%(maxpicturey+1)]==0  )
            {
                if (drawmazes==1)
                {
                    if (files_mazes[(picturex+x)%(maxpicturex+1)][(picturey+y)%(maxpicturey+1)]==0)
                    {
                        if (files[(picturex+x)%(maxpicturex+1)][(picturey+y)%(maxpicturey+1)]==0 || loadbackground==0)
                        {
                            putinmazeSFML((picturex+x)%(maxpicturex+1),(picturey+y)%(maxpicturey+1));
                        }
                        else
                        {
                            sprintf(naam,"%s/%dx%d/%03d/picture.%06d.%06d.png",LEVELDIR,BITMAPSX,BITMAPSY,level,(y+picturey)%(totalpicturey),(x+picturex)%(totalpicturex));
                            ReadSFML(naam,(picturex+x)%(maxpicturex+1),(picturey+y)%(maxpicturey+1),1);
                        }
                    }
                    else
                    {
                        sprintf(naam,"%s/%dx%d/%03d/picture_maze.%06d.%06d.png",LEVELDIR,BITMAPSX,BITMAPSY,level,(y+picturey)%(totalpicturey),(x+picturex)%(totalpicturex));
                        ReadSFML(naam,(picturex+x)%(maxpicturex+1),(picturey+y)%(maxpicturey+1),0);
                    }
                }
                else
                {
                    if (files[(picturex+x)%(maxpicturex+1)][(picturey+y)%(maxpicturey+1)]==0 || loadbackground==0)
                    {
                        putinmazeSFML((picturex+x)%(maxpicturex+1),(picturey+y)%(maxpicturey+1));
                    }
                    else
                    {
                        sprintf(naam,"%s/%dx%d/%03d/picture.%06d.%06d.png",LEVELDIR,BITMAPSX,BITMAPSY,level,(y+picturey)%(totalpicturey),(x+picturex)%(totalpicturex));
                        ReadSFML(naam,(picturex+x)%(maxpicturex+1),(picturey+y)%(maxpicturey+1),0);
                    }
                }
            }
        }
    }
}

void cleanupbitmaps()
{
    FILE * testfile;
    char naam[200];
    int x,y;
    char new_leveldir[1000];
    strcpy(new_leveldir,LEVELDIR);
   	while (replace_str(new_leveldir,"/","\\"));

//    sprintf(naam,"del levels\\%dx%d\\%03d\\picture_maze*.*",BITMAPSX,BITMAPSY,level);
    sprintf(naam,"del %s\\%dx%d\\%03d\\picture.* 2>nul >nul",new_leveldir,BITMAPSX,BITMAPSY,level);
    loader_mutex.lock();
    monitor_off=1;
    loader_mutex.unlock();
    system(naam);
    monitor_off=1;

    for (x=0; x<=maxpicturex; x++)
    {
        for (y=0; y<=maxpicturey; y++)
        {

//            if (MAZEOFF==1) {
//                sprintf(naam,"%s/%dx%d/%03d/picture.%06d.%06d.png",LEVELDIR,BITMAPSX,BITMAPSY,level,y,x);
//                if (file_exists(naam)) files[x][y]=1;
//                else files[x][y]=0;
                files[x][y]=0;
                error_flag=0;
//            }

//            if (files[x][y]==1)
//            {
//                files[x][y]=0;
//                if (MAZEOFF==0) totalfiles--;
//                sprintf(naam,"%s/%dx%d/%03d/picture.%06d.%06d.png",LEVELDIR,BITMAPSX,BITMAPSY,level,y,x);
//                remove(naam);
//            }
//            if (used[x][y]==1)
//            {


//hiero1
//                if (used[x][y]==1) texturemaxinmempoint[used2[x][y]]->clear( sf::Color(0,0,0,0) );
                used[x][y]=0;
                used_maxinmem[used2[x][y]]=0;



//                totalused--;
//                texturemaxinmempoint[used2[x][y]]->clear( sf::Color(0,0,0,0) );
//            }
//            if (changed[x][y]==1)
//            {
                changed[x][y]=0;
//                totalchanged--;
//            }
        }
    }
    totalused=0;
    totalfiles=0;
    totalchanged=0;
}

void cleanupbitmaps_mazes() {
    FILE * testfile;
    char naam[200];
    int x,y;
    char new_leveldir[1000];
    strcpy(new_leveldir,LEVELDIR);
   	while (replace_str(new_leveldir,"/","\\"));

//    sprintf(naam,"del levels\\%dx%d\\%03d\\picture_maze*.*",BITMAPSX,BITMAPSY,level);
    sprintf(naam,"del %s\\%dx%d\\%03d\\picture_maze*.* >nul 2>nul",new_leveldir,BITMAPSX,BITMAPSY,level);
//    sprintf(naam,"del %s\\%dx%d\\%03d\\picture_maze*.* > nul",LEVELDIR,BITMAPSX,BITMAPSY,level);
//    printf(naam);printf("\n");

    loader_mutex.lock();
    monitor_off=1;
    loader_mutex.unlock();
    system(naam);
    monitor_off=1;
    for (x=0; x<=maxpicturex; x++)
    {
        for (y=0; y<=maxpicturey; y++)
        {
//            if (MAZEOFF==1) {
//                sprintf(naam,"levels/%dx%d/%03d/picture_maze.%06d.%06d.png",BITMAPSX,BITMAPSY,level,x,y);
//                if (file_exists(naam)) files_mazes[x][y]=1;
//                else files_mazes[x][y]=0;
//            }
//            if (files_mazes[x][y]==1)
//            {
                files_mazes[x][y]=0;
//                if (MAZEOFF==0) totalfiles_mazes--;
//                sprintf(naam,"levels/%dx%d/%03d/picture_maze.%06d.%06d.png",BITMAPSX,BITMAPSY,level,x,y);
//                remove(naam);
//            }
//            if (used[x][y]==1)
//            {

//hiero1
//                if (used[x][y]==1) texturemaxinmempoint[used2[x][y]]->clear( sf::Color(0,0,0,0) );
                used[x][y]=0;
                used_maxinmem[used2[x][y]]=0;

                //totalused--;
//            }
//            if (changed[x][y]==1)
//            {
                changed[x][y]=0;
//                totalchanged--;
//            }
        }
    }
    totalused=0;
    totalfiles_mazes=0;
    totalchanged=0;
}

extern int blending;
extern sf::BlendMode MyBlendingMode;

void combine_front_to_back() {
    char naam[200];
    int x,y;
    int arx,ary;
    sf::Sprite sprite;
    int numcreated=0;
    int numloaded=0;

    text.setCharacterSize(36);
    text.setFillColor(sf::Color::White);

    sf::RenderTexture texture_new;
    sprite.setTexture(sfml_bitmaps,false);
    sprite.setTextureRect({0,0,1920,1080});
    sprite.setPosition(0,0);
    texture_new.create(1920,1080);

    for (arx=0; arx<=maxpicturex; arx++)
    {
        for (ary=0; ary<=maxpicturey; ary++)
        {

            sprintf(naam,"%s/%dx%d/%03d/picture.%06d.%06d.png",LEVELDIR,BITMAPSX,BITMAPSY,level,ary,arx);
            texture_new.clear(sf::Color(0,0,0,255));
//            SFMLView1.clear(sf::Color(0,0,0,255));
//            glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
            SFMLView1.setActive(true);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            SFMLView1.setActive(false);
            if (file_exists(naam)) {
                sfml_bitmaps.loadFromFile(naam);
                texture_new.draw(sprite);
                SFMLView1.draw(sprite);

                sprintf(writer,"CREATED: %d",numcreated);
                draw2(writer,0,36,sf::Color::Blue,sf::Color::White);
                sprintf(writer,"COMBINING ALL TEXTURES FRONT+BACK: X=%d Y=%d TOTAL=%d",arx,ary,arx*(maxpicturey+1)+ary+1);
                draw2(writer,0,0,sf::Color::Blue,sf::Color::White);
                SFMLView1.display();
            }
            sprintf(naam,"%s/%dx%d/%03d/picture_maze.%06d.%06d.png",LEVELDIR,BITMAPSX,BITMAPSY,level,ary,arx);
            if (file_exists(naam)) {
                sfml_bitmaps.loadFromFile(naam);
                if (blending==0) {
                    texture_new.draw(sprite);
                    SFMLView1.draw(sprite);
                }
                else {
                    texture_new.draw(sprite,MyBlendingMode);
                    SFMLView1.draw(sprite,MyBlendingMode);
                }
            }
            numcreated++;
            sprintf(writer,"CREATED: %d",numcreated);
            draw2(writer,0,36,sf::Color::Blue,sf::Color::White);
            sprintf(writer,"COMBINING ALL TEXTURES FRONT+BACK: X=%d Y=%d TOTAL=%d",arx,ary,arx*(maxpicturey+1)+ary+1);
            draw2(writer,0,0,sf::Color::Blue,sf::Color::White);

            texture_new.display();
            SFMLView1.display();

            sprintf(naam,"%s/%dx%d/%03d/picture.%06d.%06d.png",LEVELDIR,BITMAPSX,BITMAPSY,level,ary,arx);
            texture_new.getTexture().copyToImage().saveToFile(naam);
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
    }
    text.setCharacterSize(24);
}


void merge_back_to_front() {
    char naam_maze[200];
    char naam_back[200];
    int x,y;
    int arx,ary;
    int numoverwritten=0;
    int nummoved=0;
    int totalfiles=0;
    int totalfiles_background=0;
    int totalfiles_mazes=0;


    text.setCharacterSize(36);
    text.setFillColor(sf::Color::White);

    SFMLView1.setVerticalSyncEnabled(false);
    for (ary=0; ary<=maxpicturey; ary++)
    {
        for (arx=0; arx<=maxpicturex; arx++)
        {

            sprintf(naam_maze,"%s/%dx%d/%03d/picture_maze.%06d.%06d.png",LEVELDIR,BITMAPSX,BITMAPSY,level,ary,arx);
            sprintf(naam_back,"%s/%dx%d/%03d/picture.%06d.%06d.png",LEVELDIR,BITMAPSX,BITMAPSY,level,ary,arx);

            if (file_exists(naam_back)) {
//            if (files[arx][ary]) {
                if (file_exists(naam_maze)) {
//                if (files_mazes[arx][ary]) {
                    numoverwritten++;
                    nummoved++;
                    totalfiles_mazes++;
                    if (!remove(naam_back)) {
//                        printf("Error removing: %s\n",naam_back);
                    }
                    if (!rename(naam_maze,naam_back)) {
//                        printf("Error 1 renaming: %s to %s\n",naam_maze,naam_back);
                    }
                }
                totalfiles_background++;
                totalfiles++;
            } else {
                if (file_exists(naam_maze)) {
//                if (files_mazes[arx][ary]) {
                    nummoved++;
//                    rename(naam_maze,naam_back);
                    if (rename(naam_maze,naam_back)) {
//                            printf("Error 2 renaming: %s to %s\n",naam_maze,naam_back);
                    }
                    totalfiles_mazes++;
                    totalfiles++;
                }
            }

            blitter2();

            sprintf(writer,"CHECKING FILES: X=%d Y=%d TOTAL=%d",arx,ary,ary*(maxpicturex+1)+arx+1);
            draw2(writer,0,0,sf::Color::Blue,sf::Color::White);

            sprintf(writer,"BACKGROUND BEFORE:      %d",totalfiles_background);
            draw2(writer,0,36,sf::Color::Blue,sf::Color::White);

            sprintf(writer,"BACKGROUND OVERWRITTEN: %d",numoverwritten);
            draw2(writer,0,36*2,sf::Color::Blue,sf::Color::White);

            sprintf(writer,"FOREGROUND MOVED:       %d",nummoved);
            draw2(writer,0,36*3,sf::Color::Blue,sf::Color::White);

            sprintf(writer,"TOTAL FILES:            %d",totalfiles);
            draw2(writer,0,36*4,sf::Color::Blue,sf::Color::White);

            SFMLView1.display();

            if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
            else
            {
                HANDLEEVENTS();
            }
            if (ESCAPE==1) {
                ESCAPE=0;
                goexit=0;
                arx=BITMAPSX;
                ary=BITMAPSY;
            }
        }
    }
    if (sync==1)
        SFMLView1.setVerticalSyncEnabled(true);

    sprintf(error_msg2,"CHECKED FILES:      TOTAL=%d",arx*ary);
    error_flag2=1;

    sprintf(error_msg3,"BACKGROUND BEFORE:        %d",totalfiles);
    error_flag3=1;

    sprintf(error_msg4,"BACKGROUND OVERWRITTEN:   %d",numoverwritten);
    error_flag4=1;

    sprintf(error_msg5,"FOREGROUND MOVED TO BACK: %d",nummoved);
    error_flag5=1;

    text.setCharacterSize(24);
}

void shift_back() {
    char naam_backup[200];
    char naam_back[200];
    char naam_blanco[200];
    int x,y;
    int arx,ary;
    int numoverwritten=0;
    int nummoved=0;
    int totalfiles=0;
    int to_move_x=picturex;
    int to_move_y=picturey;

    bool put_blanco=false;
    sprintf(naam_blanco,"%s/%dx%d/%03d/blanco.png",LEVELDIR,BITMAPSX,BITMAPSY,level);
    if (file_exists(naam_blanco)) {
        put_blanco=true;
    }

    text.setCharacterSize(36);
    text.setFillColor(sf::Color::White);

    SFMLView1.setVerticalSyncEnabled(false);
    for (ary=0; ary<=maxpicturey; ary++)
    {
        for (arx=0; arx<=maxpicturex; arx++)
        {

            sprintf(naam_backup,"%s/%dx%d/%03d/picture_backup.%06d.%06d.png",LEVELDIR,BITMAPSX,BITMAPSY,level,ary,arx);
            sprintf(naam_back,"%s/%dx%d/%03d/picture.%06d.%06d.png",LEVELDIR,BITMAPSX,BITMAPSY,level,ary,arx);

            if (file_exists(naam_back)) {
                if (!rename(naam_back,naam_backup)) {
                        printf("1) Renaming: %s to %s\n",naam_back,naam_backup);
                } else {
                        printf("Error 1 renaming: %s to %s\n",naam_back,naam_backup);
                }
                totalfiles++;
            }

            blitter2();

            sprintf(writer,"RENAMING FILES TO BACKUP: X=%d Y=%d TOTAL=%d",arx,ary,ary*(maxpicturex+1)+arx+1);
            draw2(writer,0,0,sf::Color::Blue,sf::Color::White);

            sprintf(writer,"TOTAL FILES:            %d",totalfiles);
            draw2(writer,0,36,sf::Color::Blue,sf::Color::White);

            SFMLView1.display();
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
    }
    totalfiles=0;
    for (ary=0; ary<=maxpicturey; ary++)
    {
        for (arx=0; arx<=maxpicturex; arx++)
        {

            sprintf(naam_backup,"%s/%dx%d/%03d/picture_backup.%06d.%06d.png",LEVELDIR,BITMAPSX,BITMAPSY,level,ary,arx);
            sprintf(naam_back,"%s/%dx%d/%03d/picture.%06d.%06d.png",LEVELDIR,BITMAPSX,BITMAPSY,level,(ary-to_move_y+totalpicturey)%totalpicturey,(arx-to_move_x+totalpicturex)%totalpicturex);

            if (file_exists(naam_backup)) {
                if (rename(naam_backup,naam_back)) {
//                    printf("2) Renaming: %s to %s\n",naam_backup,naam_back);
                } else {
//                    printf("Error 2 renaming: %s to %s\n",naam_backup,naam_back);
                }
                totalfiles++;
            } else {
                if (put_blanco) {
                    CopyFile(naam_blanco, naam_back, true);
                }
            }

            blitter2();

            sprintf(writer,"RENAMING FILES TO BACKUP: X=%d Y=%d TOTAL=%d",arx,ary,ary*(maxpicturex+1)+arx+1);
            sprintf(writer,"RENAMING FILES TO NEW OFFSET: X=%d Y=%d TOTAL=%d",arx,ary,ary*(maxpicturex+1)+arx+1);
            draw2(writer,0,0,sf::Color::Blue,sf::Color::White);

            sprintf(writer,"TOTAL FILES:            %d",totalfiles);
            draw2(writer,0,36,sf::Color::Blue,sf::Color::White);

            SFMLView1.display();
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
    }
    if (sync==1)
        SFMLView1.setVerticalSyncEnabled(true);

sprintf(error_msg2,"CHECKED FILES:      TOTAL=%d",arx*ary);
    error_flag2=1;

    sprintf(error_msg3,"BACKGROUND BEFORE:        %d",totalfiles);
    error_flag3=1;

    sprintf(error_msg4,"BACKGROUND OVERWRITTEN:   %d",numoverwritten);
    error_flag4=1;

    sprintf(error_msg5,"FOREGROUND MOVED TO BACK: %d",nummoved);
    error_flag5=1;

    text.setCharacterSize(24);
}

int rotzooi(char * str_from, char * str_to) {
char str_part[2000]="";
    if (!file_exists(str_to)) {
        sprintf(str_part,"move \"%s\" \"%s\"",str_from,str_to);
        system(str_part);
    }
    if (!file_exists(str_to)) {
        sprintf(str_part,"rename \"%s\" \"%s\"",str_from,str_to);
        system(str_part);
    }
    if (!file_exists(str_to)) {
        while (replace_str(str_from,"/","\\"));
        while (replace_str(str_to,"/","\\"));
        sprintf(str_part,"move \"%s\" \"%s\"",str_from,str_to);
        system(str_part);
    }
    if (!file_exists(str_to)) {
        sprintf(str_part,"rename \"%s\" \"%s\"",str_from,str_to);
        system(str_part);
    }
    if (!file_exists(str_to)) {
        rename(str_from,str_to);
    }
    if (!file_exists(str_to)) {
        rename(str_from,str_to);
    }
}
