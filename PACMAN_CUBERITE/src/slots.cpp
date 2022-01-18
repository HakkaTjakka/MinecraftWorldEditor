#include <conio.h>
#include <exception>
#define PI 3.141592653589793
#define SFML_STATIC
#undef UNICODE
#include <winsock2.h>
#include <io.h>
#include "WinMain.h"
#include <psapi.h>
#include <stdio.h>
#include <dos.h>
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
#include <locale.h>
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

extern float fpstime;
extern int y_bar[];
extern int maxpixelsy;
extern int render_picturey,render_posy;

int flasher[5][20];
extern int BITMAPSY;

void set_bars() {
    static float fpstime2=0.0;

    static bool first=true;
    if (first) {
        for (int x=0; x<5; x++) {
            for (int y=0; y<20; y++) {
                if ( sin(5.0*fpstime*3.1415)>0.0) {
                    if (
                        int ary=(y+BITMAPSY)%BITMAPSY;

                        (ary+(int)x+20+(int)(fpstime/2.0)%6)%(1+(int)(fpstime)%4)==0  ||
                        (ary+(int)(fpstime/4.0)%3)%(1+20+(int)x+(int)(fpstime)%5)==0 )
                    {
                        flasher[x][y]=1;
//                        first=false;

                    } else {
                        flasher[x][y]=0;
                    }
                }

            }
        }
    }

    fpstime2=fpstime2+1.0/60.0;
//    fpstime2=fpstime;
    static float fpstime3=0.0;
    fpstime3=(fpstime3*5+fpstime2)/6.0;

    for (int x=0; x<5; x++) {
        int position_y=y_bar[x];

        int y=(render_picturey*1080-render_posy);


//        position_y+=x+1;

        position_y=(x+2)*(2160+160*fpstime3);


//        160*fpstime
//        position_y=(position_y+maxpixelsy)%maxpixelsy;
//        position_y=(y+maxpixelsy)%maxpixelsy;
        y_bar[x]=position_y;
    }
}
