#define PI 3.141592653589793
#define SFML_STATIC
#undef UNICODE
#include <winsock2.h>
#include <io.h>
#include "WinMain.h"
#include <psapi.h>
#include <stdio.h>
#include <conio.h>
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
#include <sfeMovie/Movie.hpp>
#include "StreamSelector.hpp"
#include "MediaInfo.hpp"
#include "Effect.hpp"
#include <SFML/OpenGL.hpp>
#include <GL/glext.h>
#include <GL/glu.h>
#include <GL/gl.h>
#define SCANNER_NUMBER_OF_SIMULTANIOUS_ACTIVE_THREADS 10

extern bool file_exists(const char * filename);

int scanner_batch_load=1;
int scanner_stay_active=true;
int scanner_active_loaders=0;
int scanner_loader_index=0;
int scaner_loader_signal[150000];
void SCANNER_LOAD_ONE_IMAGE(size_t index);
int scanner_count_ready_global=0;
int scanner_sharp=false;

struct scanner_image_loader {
    std::string filename;
    sf::Image* image;
    bool ready=false;
    bool ok=true;
    size_t index;
    sf::Thread *thread_pointer;
    std::string previous="";
//    sf::Thread image_thread;
};

std::vector<struct scanner_image_loader*> scanner_image_buffer;

int scanner_wait_for_all_loaded() {
    bool all_ready=1;
    int count_ready=0;
    int count_not_exist=0;
    int count_error_loading=0;
//    printf("\r");
//    for (auto u : scanner_image_buffer) {
    for (int m=0; m<scanner_loader_index; m++) {
        if (scanner_image_buffer[m]->ready) {
//        if (u->ready) {
            count_ready++;
            if (scanner_image_buffer[m]->ok) {
//            if (u->ok) {
//                    printf("!"); //ready and loaded and ok
            } else {
                all_ready=-1;
                printf("E"); //ready and error loading
                count_error_loading++;
            }
        } else {
            if (scanner_image_buffer[m]->ok) {
//            if (u->ok) {
//                printf("L"); //not ready-loading
                if (all_ready==1) all_ready=0;
            } else {
                count_not_exist++;
                all_ready=-2;
                printf("X");//file does not exists/not ready (should not occur often...)
            }
        }
    }
    if (count_not_exist) {
        printf("                                              #not exist=%d",count_not_exist);
        return 1;//just fok it. Bill Gates corrupts everything through his updates, motherfokking bastard insane psyco....

    }
    if (count_error_loading) {
        printf("                                              #error loading=%d",count_error_loading);
        return 1;//just fok it.
    }
    scanner_count_ready_global=count_ready;
    return all_ready;
//    return all_ready;
};


void SCANNER_LOAD_ONE_IMAGE(size_t index) {
//    printf("index=%d Thread started. filename=%s\n",index,scanner_image_buffer[index].filename.c_str());
    int first=1;
    while (scanner_stay_active==true) {
        char fn[2000];
        if (!file_exists(scanner_image_buffer[index]->filename.c_str())) {
            bool f_ok=false;
            strcpy(fn,scanner_image_buffer[index]->filename.c_str());
            if (strlen(fn)>4) {
                fn[strlen(fn)-3]='j';
                fn[strlen(fn)-2]='p';
                fn[strlen(fn)-1]='g';
                if (!file_exists(fn)) {
                    fn[strlen(fn)-3]='b';
                    fn[strlen(fn)-2]='m';
                    fn[strlen(fn)-1]='p';
                    if (!file_exists(fn)) {
                        fn[strlen(fn)-3]='p';
                        fn[strlen(fn)-2]='n';
                        fn[strlen(fn)-1]='g';
                        if (file_exists(fn)) f_ok=true;
                    } else f_ok=true;
                } else f_ok=true;
            }
            if (f_ok) scanner_image_buffer[index]->filename=fn;
        }

        if (scanner_image_buffer[index]->previous==scanner_image_buffer[index]->filename) {
//            printf("\rSAME FILE!!! NOT LOADING -> %s\n",scanner_image_buffer[index]->previous.c_str());
            scanner_image_buffer[index]->ready=true;
        } else if (!file_exists(scanner_image_buffer[index]->filename.c_str())) {
            printf("\nindex=%d Cannot find file on disk: %s\n",index,scanner_image_buffer[index]->filename.c_str());
            scanner_image_buffer[index]->ok=false;
        } else {
            if (first==1) {
//                printf("index=%d File exists / first run Sleeping for 30 seconds before loading %s\n",index,scanner_image_buffer[index]->filename.c_str());
                while (scanner_batch_load==0) sf::sleep(sf::milliseconds(10));
//                printf("index=%d Waking up after first run. Now loading filename=%s\n",index,scanner_image_buffer[index]->filename.c_str());
            } else {
//                printf("index=%d File exists / loading now: s%s\n",index,scanner_image_buffer[index]->filename.c_str());
                while (scanner_batch_load==0) sf::sleep(sf::milliseconds(10));
            }
            if (index>=SCANNER_NUMBER_OF_SIMULTANIOUS_ACTIVE_THREADS) {
                while (!scanner_image_buffer[index-SCANNER_NUMBER_OF_SIMULTANIOUS_ACTIVE_THREADS]->ready && scanner_stay_active==true) sf::sleep(sf::milliseconds(30));
            }
            if (scanner_stay_active==true) {
                scanner_image_buffer[index]->ok=scanner_image_buffer[index]->image->loadFromFile(scanner_image_buffer[index]->filename.c_str());
                if (!scanner_image_buffer[index]->ok)
                    printf("\nindex=%d Error loading file: %s\n",index,scanner_image_buffer[index]->filename.c_str());
                else
                scanner_image_buffer[index]->previous = scanner_image_buffer[index]->filename;
                scanner_image_buffer[index]->ready=true;
            }
        }
        first=0;
//        printf("index=%d Ready. Staying active, waiting for signal\n");
        while (scaner_loader_signal[index]==0 && scanner_stay_active==true) {
                if (!scanner_sharp) sf::sleep(sf::seconds(1.0));
                else sf::sleep(sf::seconds(0.1));
        }
        scaner_loader_signal[index]=0;
        if (scanner_stay_active==true) {
//            printf("index=%d signal->NEW JOB!!! Got signal..... New file:%s\n",index,scanner_image_buffer[index]->filename.c_str());
        } else if (scanner_stay_active==false) {
//            printf("index=%d scanner_stay_active->Unloading...bye\n",index);
        }
    }
}

void scanner_push_image_file(std::string filename) {
    size_t index=scanner_image_buffer.size();
    scanner_sharp=true;
//    struct scanner_image_loader* scanner_image_loader_struct_pointer = new scanner_image_loader;
//    sf::Thread* thread_pointer = new sf::Thread(&SCANNER_LOAD_ONE_IMAGE,index);

    if (scanner_loader_index>=index) {
        struct scanner_image_loader* scanner_image_loader_struct_pointer = new scanner_image_loader;

//        sf::Thread* thread_pointer = new sf::Thread(&SCANNER_LOAD_ONE_IMAGE,index);
//        scanner_image_loader_struct_pointer->thread_pointer=thread_pointer;
        scanner_image_loader_struct_pointer->image = new sf::Image;
        scanner_image_loader_struct_pointer->thread_pointer = new sf::Thread(&SCANNER_LOAD_ONE_IMAGE,index);

        scanner_image_loader_struct_pointer->filename=filename;
        scanner_image_loader_struct_pointer->ready=false;
        scanner_image_loader_struct_pointer->ok=true;
        scaner_loader_signal[scanner_loader_index]=0;
        scanner_image_buffer.push_back(scanner_image_loader_struct_pointer);
//        printf("index=%d loaderindex=%d index=%d First launching: filename=%s\n",scanner_loader_index,index,scanner_image_buffer.size()-1,filename.c_str());
        scanner_image_buffer[scanner_image_buffer.size()-1]->thread_pointer->launch();
//        thread_pointer->launch();
//        printf("index=%d First launched: size=%d filename=%s\n",index,scanner_image_buffer.size(),filename.c_str());
    } else {
//        printf("index=%d re-Launching: filename=%s\n",scanner_loader_index,filename.c_str());
        if (scanner_image_buffer[scanner_loader_index]->image == NULL)
            scanner_image_buffer[scanner_loader_index]->image = new sf::Image;
        scanner_image_buffer[scanner_loader_index]->filename=filename;
        scanner_image_buffer[scanner_loader_index]->ready=false;
        scanner_image_buffer[scanner_loader_index]->ok=true;
//        scaner_loader_signal[scanner_loader_index]=0;
//        scanner_image_buffer[scanner_loader_index]->previous="";
//        scanner_image_buffer[scanner_loader_index]->thread_pointer->launch();
//        printf("index=%d re-Launched: size=%d filename=%s\n",index,scanner_image_buffer.size(),filename.c_str());
        scaner_loader_signal[scanner_loader_index]=1;
    }
    scanner_loader_index++;
//    printf("index=%d scanner_loader_index=%d First launched: scanner_image_buffer.size=%d filename=%s\n",index,scanner_loader_index,scanner_image_buffer.size(),filename.c_str());
}

void scanner_clear_image_buffer() {
//    printf("Clearing image buffer\n");
    scanner_loader_index=0;
    scanner_sharp=false;
    scanner_batch_load=0;
//    scanner_stay_active=false;
    for (int m=0; m<scanner_image_buffer.size(); m++) {
//        scanner_image_buffer[m]->thread_pointer->wait();
//        printf("deleting thread=%u\n",scanner_image_buffer[m]->thread_pointer);
//        printf("deleting scanner_image_loader=%u\n",scanner_image_buffer[m]);
//        delete scanner_image_buffer[m]->thread_pointer;
//        scanner_image_buffer[m]->image->~Image();
        delete scanner_image_buffer[m]->image;
        scanner_image_buffer[m]->image = NULL;
        scanner_image_buffer[m]->previous="";
        scanner_image_buffer[m]->filename="";
//        delete scanner_image_buffer[m];
    }
//    scanner_image_buffer.clear();
//    for (auto u : scanner_image_buffer) {
//        u->ok=true;
//        u->ready=false;
//            u->filename="";
//    }
//    scanner_image_buffer.clear();
//    printf("\nscanner_image_buffer.size()=%d\n",scanner_image_buffer.size());
    scanner_active_loaders=0;
//    scanner_image_buffer.clear();
//    sf::sleep(sf::seconds(0.25));
}
