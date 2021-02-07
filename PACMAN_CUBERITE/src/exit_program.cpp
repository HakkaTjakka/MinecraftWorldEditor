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
#include "MediaInfo.hpp"

extern void terminate_set_monimem_terminator();
extern void kill_threads();
extern void terminate_animator();
extern void terminate_rendering();
extern char LEVELDIR[];
extern int movie;
extern int movie2;
extern void stopmovie();
extern void stopmovie2();
extern void savelevel();
extern int LOGFILE;
extern int connected;
extern int udp;
extern int tcp;
extern void logfile(char *line);
extern sf::TcpSocket internet_socket_tcp1;
extern sf::TcpSocket internet_socket_tcp2;
extern sf::UdpSocket internet_socket_udp1;
extern sf::UdpSocket internet_socket_udp2;
extern int connected_ready;
extern void terminate_monitor();
extern void terminate_thread();
extern void SEND(char *towrite);
extern int combine;
extern int SAVELAST;
extern void save_map_last();
extern int DONTSAVEFILES;
extern int drawmazes;
extern int totalpicturex;
extern int totalpicturey;
extern void save_maze(int lastmap);
extern char **changed;
extern int BITMAPSX;
extern int BITMAPSY;
extern int level;
extern char **files_mazes;
extern int totalfiles_mazes;
extern char **files;
extern int totalfiles;
extern sf::RenderTexture *texturemaxinmempoint[];
extern int  **used2;
extern int totalchanged;
extern void blitter(char * line, int mode);
extern sf::RenderWindow SFMLView1;
extern void draw2(char *towrite, int xpos, int ypos, sf::Color inner, sf::Color outer);
extern int MAXINMEM;
extern sf::Sprite *spritemaxinmempoint[];
extern int server;
extern int client;
extern sf::TcpListener listener1;
extern sf::TcpListener listener2;
extern void frexit(int err_no);
extern int MAZEOFF;
extern void save_mazeoff();
extern int read_mazeoff();
extern sf::Thread monimem();
extern int dont_stop;
extern int kill1,kill2,kill3;
extern int loader1_active;
extern int loader2_active;
extern int loader3_active;
extern int window_1_active;
extern int window_2_active;
extern int window_3_active;
extern void ShowTaskBar(bool show);
extern void terminate_background_blitter();
extern int go_blit;
extern int cool;

void EXITPROGRAM()
{
//    fclose(file1);fclose(file2);fclose(file3);

    SFMLView1.setActive(false);
    cool=0;
    go_blit=0;
    ShowTaskBar(true);
    kill1=1;kill2=1;kill3=1;
    dont_stop=0;
    int x;
    int y;
    int xx;
    int yy;
    char naam[200];

    if (movie==0)
        stopmovie();
    if (movie2==0)
        stopmovie2();
    savelevel();
    if (MAZEOFF!=0) save_mazeoff();
    logfile((char*)"Exiting program, cleaning up");
    if (connected==1)
    {
        if (tcp==1)
        {
            internet_socket_tcp1.setBlocking(true);
            internet_socket_tcp2.setBlocking(true);
        }
        else if (udp==1)
        {
            internet_socket_udp1.setBlocking(true);
            internet_socket_udp2.setBlocking(true);
        }
    }

    if (connected_ready==0) terminate_thread();

    if (connected==1)
    {
        SEND((char*)"T=QUIT,\0");
    }

    combine=0;
    if (SAVELAST==1)
        save_maze(0);
    if (SAVELAST==1)
        save_map_last();
    char score[80];
    FILE *testfile;
    if (DONTSAVEFILES==0 || drawmazes==0 )
    {
        for (x=0; x<totalpicturex; x++)
        {
            for (y=0; y<totalpicturey; y++)
            {
                if (changed[x][y]==1)
                {
                    if (drawmazes==1)
                    {
                        sprintf(naam,"%s/%dx%d/%03d/picture_maze.%06d.%06d.png",LEVELDIR,BITMAPSX,BITMAPSY,level,y,x);
//                        sprintf(naam,"levels/%dx%d/%03d/picture_maze.%06d.%06d.png",BITMAPSX,BITMAPSY,level,y,x);
                        if (files_mazes[x][y]==0)
                        {
                            files_mazes[x][y]=1;
                            totalfiles_mazes++;
                        }
                    }
                    else
                    {
//                        sprintf(naam,"levels/%dx%d/%03d/picture.%06d.%06d.png",BITMAPSX,BITMAPSY,level,y,x);
                        sprintf(naam,"%s/%dx%d/%03d/picture.%06d.%06d.png",LEVELDIR,BITMAPSX,BITMAPSY,level,y,x);
                        if (files[x][y]==0)
                        {
                            files[x][y]=1;
                            totalfiles++;
                        }
                    }
                    texturemaxinmempoint[used2[x][y]]->getTexture().copyToImage().saveToFile(naam);
                    changed[x][y]=0;
                    totalchanged--;
                    sprintf(score,"SAVING CHANGED BITMAPS ONLY=%d bitmaps\n", totalchanged);
                    blitter(score,1);
                }
            }
        }
    }
//    SFMLView1.clear();
//    sprintf(score,"CLEANING UP MEM\n");
//    draw2(score,0,0,sf::Color::Blue,sf::Color::White);
//    SFMLView1.display();
extern sf::Sprite *sprite_buffer;

    for (x=0; x<MAXINMEM+12; x++)
    {
        if (spritemaxinmempoint[xx]!=NULL) delete spritemaxinmempoint[xx];
        spritemaxinmempoint[xx]=NULL;
    }
    if (sprite_buffer!=NULL) delete sprite_buffer;
    sprite_buffer=NULL;
    if (connected==1)
    {
        SEND((char*)"T=QUIT,\0");
        if (client==1)
        {
            if (udp==1)
            {

            }
            else if (tcp==1)
            {
                internet_socket_tcp1.disconnect();
                internet_socket_tcp2.disconnect();
                listener1.close();
                listener2.close();
            }
        }
        else if (server==1)
        {
            if (udp==1)
            {
                internet_socket_udp1.unbind();
                internet_socket_udp2.unbind();
            }
            else if (tcp==1)
            {
                internet_socket_tcp1.disconnect();
                internet_socket_tcp2.disconnect();
            }
        }
    }

//    sf::Texture::bind(NULL);
    PostQuitMessage(0);
    kill1=1;kill2=1;kill3=1;
    if (loader1_active==1 || loader2_active==1 || loader3_active==1) printf("Waiting for map loader threads to finish\n");
    while (loader1_active==1 || loader2_active==1 || loader3_active==1) {
        sf::sleep(sf::milliseconds(100));
        printf(".");
    }
    PostQuitMessage(0);
    if (window_1_active==1 || window_2_active==1 || window_3_active==1) printf("Waiting for map loader thread windows to close\n");
    while (window_1_active==1 || window_2_active==1 || window_3_active==1) {
        sf::sleep(sf::milliseconds(100));
        printf(".");
    }
    printf("\n");
    ShowTaskBar(true);
    terminate_set_monimem_terminator();
    terminate_monitor();
    kill_threads();
//    terminate_animator();
//    SFMLView1.close();
    GenerateConsoleCtrlEvent(CTRL_C_EVENT, 0);

    frexit(0);
extern int winmain_running;
    winmain_running=0;
}
