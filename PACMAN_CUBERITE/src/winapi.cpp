#define SFML_STATIC
#undef UNICODE
#include <winsock2.h>
#include <io.h>
//#include "WinMain.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sys/stat.h>
#include <iostream>
#include <cstdlib>
#include <Windows.h>

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GLFW/glfw3.h>

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
#include <wchar.h>
#include <locale.h>
#include <iostream>
#include <glm/glm.hpp>
//#include "keylist.hpp"
#define EVENT_ALT 1
#define EVENT_SHIFT 2
#define EVENT_CONTROL 4
#define EVENT_SYSTEM 8

extern void font2function();

extern sf::Texture* backgroundTexture[];
extern bool get_screenshot(sf::Texture* m_texture);
extern void one_region_voxel_files_to_region_files(bool display_only, char* voxel_filename);
extern void region_voxel_files_to_region_files(bool display_only);

extern bool cubic;
extern void launch_REGION_TO_VOXEL();
bool roelof=false;
void multiple_regions_to_voxelfiles(std::string);
bool screensaver=false;

extern bool do_pong=false;
extern bool and_now_i_am_here;
char voxel_filename[200];
std::string obj_filename="";
std::string region_filename="";
bool make_regions=false;
bool make_object=false;
extern bool file_exists(const char * filename);
extern glm::mat4 exporter;
extern glm::mat4 exporter2;
extern char MODELS[];
extern bool make_schematic;
extern bool i_am_here;
extern void voxelize_shell(std::string filename);
extern double schematic_size;
bool automate=false;
extern void cleanupbitmaps_mazes();
extern void clear_map();
extern void CLEANBITMAPS();
extern void ReadBitmaps2();
extern void ReadBitmaps4();
extern int check_dir(int BITMAPSX,int BITMAPSY,int level);
extern int BITMAPSX;
extern int BITMAPSY;
extern int level;
extern int replace_str(char *str, char *orig, char *rep);

extern std::string area;
extern int mirror;
extern int crossing;
extern int combine;
extern int MCEDITOR_running;
extern bool flushing;
sf::ContextSettings contextSettings(0,0,2,3,0);
extern void REPACK(char* filename);

extern int mcglobal;
extern int mcglobal2;
extern int mcglobal3;
extern int mcglobal4;
extern int shut_up;
HGLRC    hglrc_sfmlview1;
HDC      hdc_sfmlview1;
HDC      hdc2_sfmlview1;
extern void flying();
extern void launch_FLY_PLAY();
extern void launch_FLY_PLAY2();
int vm=0;
//extern int main_fly_de_poppa(int what, sf::RenderWindow& window, float delta);
//extern int main_fly_de_poppa(int argc, char** argv);
extern int main_fly(int argc, char** argv);
extern int main_fly_de_poppa();

ATOM RegClass(char *ClassName,HINSTANCE hInstance);
HWND CreateWin(HINSTANCE hInstance, char *ClassName,int Width, int Height);
LRESULT CALLBACK WinProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);
extern void insert_event(sf::Keyboard::Key code,int MODE);
extern void launch_MCEDITOR();
extern int main_cuberite(int argc, char ** argv);
extern void launch_SERVER();
int server_lauch=0;
extern void NonCtrlHandler(int a_Signal);
extern int server_running;
extern void READ_WORLD(char* filename);
extern void READ_WORLD_TO_DIRS(char* filename);
extern void READ_WORLD_TO_GZIPS(char* filename);
extern void WRITE_ALL_REGIONS(char* worldname);

extern void READ_REGION(char* filename);
extern void READ_REGION_TO_DIR(char* filename);
extern void READ_REGION_TO_GZIP(char* filename);

extern void WRITE_REGION(char* filename);
extern void WRITE_REGION_FROM_DIRS(char* filename);
extern void WRITE_REGION_FROM_DIRS_NBT(char* filename);

extern void WRITE_WORLD_TO_MCA(char* filename);
extern void region_header(char* filename);
extern void do_one(char* filename);
extern main_nbt(char* region_name);

extern void MAKE_MCA_FROM_WORLD_NBT(char* worldname);
extern void MAKE_MCA_FROM_WORLD_NBT_GZIPS(char* worldname);

extern void test_write_to_and_read_from_memory();
extern int burn_subs;
extern int MCEDITOR_stop;

int fast=0;
char** argv_main = NULL;
int argc_main = 0;

extern void test_tha_shit(int n);
extern void test1();
extern void test2();
extern int glob_argc;
extern char** glob_argv;

extern void set_print_text();
int start_burning=0;
int go_download=0;
int go_burn=0;
int go_list=0;
void terminate_animator();
extern char send_message;
extern int memory_set;
void ShowTaskBar(bool show);
extern void cleanupmem();
int winmain_running=1;
void set_mytext2();
void set_mytext(int next_font);
void make_text(int next_font);
int MULTIPLAYER=1;
extern void logfile(char *line);
extern int handle_init();
extern void frexit(int err_no);
extern char writer[];
extern char commandline[];
extern int skiphandshake;
extern int playerleft;
extern int server;
extern int client;
extern int connected;
extern int connecting;
extern int udp;
extern int tcp;
extern unsigned short portnumber;
extern int portnumber_int;
extern char portnumber_text[];
extern char connectedip[];
extern HINSTANCE hInstance2;
extern HWND hWndMain2;
extern sf::Sound sound[];
extern char reg[];
extern sf::WindowHandle WindowHandle;
sf::WindowHandle sfmlview1_handle;
extern sf::RenderWindow SFMLView1;
extern sf::Shader m_shader;
extern sf::RenderStates states;
extern sf::Shader m_shader2;
extern sf::RenderStates states2;
extern HWND TextBox, SendButton, TextField;
extern int runTcpServer(unsigned short port);
extern int runTcpClient(char * ipaddress, unsigned short port);
extern int runUdpServer(unsigned short port);
extern int runUdpClient(char * ipaddress, unsigned short port);
extern int reconnectTcpServer(unsigned short port);
extern int reconnectTcpClient(char * ipaddress, unsigned short port);
extern int reconnectUdpServer(unsigned short port);
extern int reconnectUdpClient(char * ipaddress, unsigned short port);
extern void INIT_NETWORK();
extern MSG msg;
extern sf::TcpListener listener1;
extern sf::TcpListener listener2;
extern sf::TcpSocket internet_socket_tcp1;
extern sf::TcpSocket internet_socket_tcp2;
extern sf::UdpSocket internet_socket_udp1;
extern sf::UdpSocket internet_socket_udp2;
extern sf::Font font;
extern sf::Text text;
extern sf::Sprite spritedot;
extern sf::Sprite spritedot2;
extern sf::Texture sfml_mazedot;
extern sf::Texture sfml_mazedot2;
extern int skipinit;
extern int go_on;
extern void HANDLEEVENTS();
extern void playSound();
extern void playMusic(const std::string& filename);
extern int soundoff;
extern int soundloop;
extern int playsound;
extern int playmusic;
extern void DoAnimate2(HINSTANCE,HWND);
extern int totalused;
extern int MAXINMEM;
extern void go_save_some_bitmaps();
sf::SoundBuffer buffer[10];
sf::Music music[10];
extern void terminate_set_monimem_terminator();
extern void launch_set_monimem_terminator();
extern void check_memory2();
extern int kill1,kill2,kill3;
extern int monitor_loop;
extern void cleanupmem();
extern void frexit();
extern int go_on;
extern void kill_background_loader();
extern void kill_threads();
extern sf::Mutex loader_mutex;
extern void SAVEALLBITMAPS();
extern int hanger;
extern void launch_animator();
extern void terminate_animator();
extern int monitor_off;
extern void EXITPROGRAM();

int WINAPI WinMain2();

int animator_running=0;

int wait_for_return() {
    int WINAPI ret=WinMain2();
    printf("Animator stopped\n");
    animator_running=0;
    return ret;
}

sf::Thread animator(&wait_for_return);
//sf::Thread animator(&WinMain2);


void launch_animator() {
    animator_running=1;
    animator.launch();
}

void terminate_animator() {
    animator.terminate();
}

int WINAPI_RETURN=0;
HINSTANCE hInstance_pass;
HINSTANCE hPrevInstance_pass;
LPSTR lpCmdLine_pass;
int nCmdShow_pas;
extern int exiting;
extern int monitor;
extern void launch_monimem();

//extern FILE* file1;
//extern FILE* file2;
//extern FILE* file3;
extern int file_first1;
extern int file_first2;
extern int file_first3;
extern int first;
extern int next;
extern void launch_OPENGL();
extern void launch_SFMLGL();
extern void launch_SFMLGL2();
extern void launch_SFMLGL2_b();
//extern void launch_VIEWER();
extern int main_hoppa();
extern int main_fly3();
extern void splinterpDemo();
extern int reload_init();

int main_get3d(int argc, char **argv);
int main_zoom(int argc, char **argv);
extern sf::Texture interface_texture;
extern sf::Sprite interface_sprite;
extern sf::Texture interface_texture1;
extern sf::Sprite interface_sprite1;
extern sf::RenderTexture render_texture;
extern sf::RenderTexture render_texture1;

struct Options
{
    float seed;
    unsigned int  windowWidth;
    unsigned int  windowHeight;
    bool  manualSeed;
    bool  wireframe;
    bool  showHelp;
    bool  fullscreen;
    bool  planeBox;
};
extern Options processArguments(int argc, char** argv);


sf::Texture texture_test;
sf::RenderTexture rendertexture_test;
sf::Sprite sprite_test;
sf::Sprite rendersprite_test;
sf::Color pixel_test;
sf::Shader shader_test;
sf::RenderStates states_test;
sf::Image image_test;

int main(int argc, char ** argv) {
//    printf("Maximum size texture=%d\n",sf::Texture::getMaximumSize());
//    splinterpDemo();
//    main_cuberite(argc,argv);
//    launch_OPENGL();
//    main_hoppa();
//    launch_FLY_PLAY();
//    printf("FlY_PLAY() LAUNCHED, sleeping 10 secs.\n");
//    sf::sleep(sf::seconds(10.0));
//        char *argv1[]={"moi","--plane-box"};
//        main_fly(1,argv1);

//    printf("main_fly3()\n");

    std::ios_base::sync_with_stdio(false);
    {
        char *argv[]={"moi","--plane-box"};
//        main_fly_de_poppa();

        render_texture.create(1920,1080,true);
        render_texture1.create(1920,1080,true);
        interface_texture1.create(1920,1080);
        interface_texture.create(1920,1080);

        interface_sprite1.setTexture(interface_texture1,true);     //printf("1Creating interface texture1\n");
        interface_sprite.setTexture(interface_texture,true);       //printf("0Creating interface texture1\n");

        Options opts = processArguments(1, argv);

        render_texture.setActive(true);
//        sf::Texture::bind(&render_texture.getTexture());
        glEnable(GL_DEPTH_TEST);        glEnable(GL_CULL_FACE);        if (opts.wireframe) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);        glEnable(GL_BLEND);
        render_texture.setActive(false);

        render_texture1.setActive(true);
        sf::Texture::bind(&render_texture1.getTexture());
        glEnable(GL_DEPTH_TEST);        glEnable(GL_CULL_FACE);        if (opts.wireframe) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);        glEnable(GL_BLEND);
        render_texture1.setActive(false);

    //    interface_sprite.setTexture(interface_texture,true);
    //    interface_sprite1.setTexture(interface_texture1,true);

        sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
        contextSettings.antialiasingLevel = 1;
        contextSettings.stencilBits = 8;
        contextSettings.depthBits=24;
//        contextSettings.sRgbCapable = false;

        texture_test.create(1920,1080);
        texture_test.setSmooth(false);
        sprite_test.setTexture(texture_test,true);
//        sf::Texture::bind(&texture_test);
//        sprite_test.setPosition(0,0);

    //    sf::Texture::bind(&texture);
        rendertexture_test.create(1920,1080,contextSettings);
//        rendertexture_test.create(1,1,contextSettings);
        rendertexture_test.setSmooth(false);
        rendersprite_test.setTexture(rendertexture_test.getTexture(),true);
//        rendertexture_test.setActive(true);
//        glViewport(0, 0, 1920,1080);
//        rendertexture_test.setActive(false);
    //    rendertexture_test.pushGLStates();
//        sprite_test.setTexture(rendertexture_test.getTexture(),true);
    //    sprite_test.setScale(1.0/1920.0,1.0/1080.0);
    //    sprite_test.setTextureRect(sf::IntRect(0, 0, 1, 1));

        image_test.create(1920,1080);

/*
        if (!shader_test.loadFromFile("shaders/analyse3d.frag", sf::Shader::Fragment)) { printf("can not load shader shaders/analyse3d.frag\n"); }
        shader_test.setUniform("texture_current", sf::Shader::CurrentTexture);
        shader_test.setUniform("texture_in", texture_test);
        shader_test.setUniform("texture_size", sf::Vector2i(texture_test.getSize()));
        shader_test.setUniform("iResolution", sf::Vector2f(texture_test.getSize().x,texture_test.getSize().y));
        states_test.shader = &shader_test;
*/

//here you go flying....
//        launch_FLY_PLAY();
//        sf::sleep(sf::seconds(2.0));
//end.


//        main_fly_de_poppa(1,argv);
//        main_fly_de_poppa(1,argv);
    }
//    main_fly(1,argv);


//    flying();

//    main_fly_de_poppa(1,SFMLView1,0.0);
//    printf("1\n");
//    for (int i=0; i<1000; i++) main_fly_de_poppa(0,SFMLView1,0.0);

//    launch_FLY_PLAY2();
//    sf::sleep(sf::seconds(2.0));

//    launch_FLY_PLAY2();

//    sf::sleep(sf::seconds(5.0));
//    printf("main_fly3() returned\n");
//    printf("\nmain_fly3() looping 360\n");
//    for (int i=0; i<360; i++) main_fly3();
//    main_fly3();
//    flying();
//    printf("main_fly3() returned\n");
//    char arg0[10]="moi";
//    char arg1[10]="";
//    char *arg[2]={arg0,arg1};
//    main_zoom(1,arg);
    reload_init();



//    launch_SFMLGL2_b();
//    printf("SFMLGL2_b() LAUNCHED, sleeping 10 secs.\n");
  //  sf::sleep(sf::seconds(10.0));
    char tot[1024]="";
    for (int i=1; i<argc; i++) {strcat(tot,argv[i]); strcat(tot," "); }
    WinMain(0,0,tot,argc);
}


extern int do3dview();
extern bool pb;
extern std::string ltrim(const std::string& s);
extern std::string rtrim(const std::string& s);

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow) {
//    do3dview();
//int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow) {
    printf("sizeof(float)=%d\n",sizeof(float));
    hInstance_pass=hInstance;
    hPrevInstance_pass=hPrevInstance;
    lpCmdLine_pass=lpCmdLine;
    nCmdShow_pas=nCmdShow;
    std::string cmd=rtrim(lpCmdLine);
    std::transform(cmd.begin(), cmd.end(),cmd.begin(), ::toupper);

    if (cmd=="FONT2FUNCTION") {
        font2function();
        ShowTaskBar(true);
        exit(0);
    }
    printf("COMMAND: \"%s\"\n",cmd.c_str());

//    int ret=WinMain2();
//    printf("WinMain2() returned. WINAPI=%d\n",ret);

//    if (!file_exists("secondloop.txt")) {
    if (file_exists("autoflower.txt")) {
//        system("echo hoi > secondloop.txt");
//        sf::sleep(sf::seconds(2));
        FILE* hoppa=fopen("autoflower.txt","r");
        char line[1000];
        fgets(line,1000,hoppa);
        while (replace_str(line,"\n",""));
        if (strcmp("skull",line)==0) {
            while (fgets(line,1000,hoppa)!=NULL) {
                while (replace_str(line,"\n",""));
                if (strcmp("quiet",line)==0) {
                    ::ShowWindow(::GetConsoleWindow(), SW_HIDE);
                } if (strcmp("plotbackground",line)==0) {
                    pb=true;
                }
            }
            system("cd");
            system("cd > /hierbenik.txt");

            backgroundTexture[0] = new sf::Texture();
            backgroundTexture[0]->setSrgb(false);
            backgroundTexture[0]->setSmooth(false);
            get_screenshot(backgroundTexture[0]);

//            fgets(line,1000,hoppa);
//            system((char*)hoppa);
//            exit(0);

//            chdir("d:/pacman/pacman_cuberite");
            screensaver=true;
            combine=1;
            area="Models";
            roelof=true;
//            backgroundTexture[0] = new sf::Texture();
//            get_screenshot(backgroundTexture[0]);

            launch_SFMLGL2();

//            launch_animator();
//            sf::sleep(sf::seconds(1));
//            send_message='B';
        } else {
            printf("bye!\n");
            exit(0);
        }
        fclose(hoppa);
//extern int is_activated_window[];
extern int keep_running[];
        bool loop=true;
        sf::sleep(sf::seconds(1.0));
        while (loop) {
            if (!keep_running[0]) loop=false;
            sf::sleep(sf::seconds(0.1));
        }
        ::ShowWindow(::GetConsoleWindow(), SW_SHOW);
         exit(0);
    }
/*    } else {
        system("del secondloop.txt");
        chdir("d:/pacman/pacman_cuberite");
        screensaver=true;
        roelof=true;
        launch_animator();
        sf::sleep(sf::seconds(1));
        send_message='B';
    }
*/

    if (!roelof) launch_animator(); /* here  */

    while (winmain_running==1) {
        if (monitor==0 && exiting==0 && winmain_running==0) launch_monimem();
        sf::sleep(sf::milliseconds(100));
        char c=send_message;
        send_message=0;
        if (c>0) {
            if (c==(char)'1') EXITPROGRAM();
            else if (c==(char)'2') monitor_off=1;
            else if (c==(char)'3') terminate_animator();
            else if (c==(char)'4') { printf("Launch animator message recieved, starting animator...\n"); strcpy(lpCmdLine,"");  launch_animator(); }
            else if (c==(char)'5') hanger=12;
            else if (c==(char)'6') SAVEALLBITMAPS();
            else if (c==(char)'7') loader_mutex.unlock();
            else if (c==(char)'8') kill_threads();
            else if (c==(char)'9') kill_background_loader();
            else if (c==(char)'0') go_on=0;
            else if (c==(char)'a') winmain_running=0;
            else if (c==(char)'b') frexit(-1);
            else if (c==(char)'c') cleanupmem();
            else if (c==(char)'d') monitor_loop=1;
            else if (c==(char)'e') kill1=kill2=kill3=1;
            else if (c==(char)'f') check_memory2();
            else if (c==(char)'g') terminate_set_monimem_terminator();
            else if (c==(char)'h') launch_set_monimem_terminator();
            else if (c==(char)'i') { terminate_animator();launch_animator();}
            else if (c==(char)'j') {
                kill_threads();
                terminate_animator();
                cleanupmem();
                if (handle_init()==1)
                {
                    int msgboxID;
                    msgboxID=MessageBox(NULL, "ERROR READING PACMAN.INI FILE", "ERROR",MB_OK);
                    frexit(1);
                }
                first=1;
                next=1;
                launch_animator();
            }
            else if (c==(char)'x') {
                go_on=0;
                int count=0;
                ShowTaskBar(true);
                while (animator_running && count<20) { sf::sleep(sf::seconds(0.2)); count++; }
                ShowTaskBar(true);
                exit(0);
            }

//            else if (c==(char)'s') launch_SERVER();
//            else if (c==(char)'S') {
//                if (server_running)
//                    NonCtrlHandler(SIGINT);
//                else printf("Server not running....\n");
//            }
            else if (c==(char)'X') {
                ShowTaskBar(true);
                go_on=0;
                while (animator_running) sf::sleep(sf::seconds(0.2));
                if (memory_set) cleanupmem();
            }
            else if (c==(char)'k') { launch_OPENGL(); }
            else if (c==(char)'l') { launch_SFMLGL(); }
//            else if (c==(char)'m') { launch_VIEWER(); }
            else if (c==(char)'n') { launch_SFMLGL2(); }
            else if (c==(char)'o') { launch_SFMLGL2_b(); }
            else if (c==(char)'p') {
                combine=1;
                area="Models";
                launch_SFMLGL2_b();
                sf::sleep(sf::seconds(1.0));
                flushing=true;
                mirror=4;
                crossing=2;
            }
            else if (c==(char)'r') {
                combine=1;
                area="Models";
                launch_SFMLGL2_b();
                while (!i_am_here) {
                    sf::sleep(sf::seconds(0.1));
                }

                sf::sleep(sf::seconds(0.1));
                make_regions=true;
            }
            else if (c==(char)'m') {
                combine=1;
                area="Models";
                launch_SFMLGL2_b();
                while (!i_am_here) {
                    sf::sleep(sf::seconds(0.1));
                }

                sf::sleep(sf::seconds(0.1));
                make_object=true;
                make_regions=true;
            }
            else if (c==(char)'A') {
                if (region_filename!="")
                    launch_REGION_TO_VOXEL();
//                    multiple_regions_to_voxelfiles(region_filename);
                else
                    launch_REGION_TO_VOXEL();
            }
            else if (c==(char)'q') {
                combine=1;
                area="Models";
                launch_SFMLGL2_b();
                while (!i_am_here) {
                    sf::sleep(sf::seconds(0.1));
                }
//                make_schematic=true;
            }
            else if (c==(char)'B') {
                combine=1;
                area="Models";
                roelof=true;
                launch_SFMLGL2_b();
                while (!i_am_here) {
                    sf::sleep(sf::seconds(0.1));
                }
//                make_schematic=true;
            }
            else if (c==(char)'s') {
                crossing=2; mirror=4;combine=1;
                area="Enschede";
                cubic=true;
                and_now_i_am_here=true;
                launch_SFMLGL2_b();
//                while (!and_now_i_am_here) {
                while (!i_am_here) {
                    sf::sleep(sf::seconds(0.1));
                }
                combine=0;
            } else if (c==(char)'u') {
                do_pong=true;
            } else if (c==(char)'t') {
                crossing=2; mirror=4;combine=1;
                cubic=true;
                area="DenHaag";
                and_now_i_am_here=true;
                launch_SFMLGL2();
//                while (!and_now_i_am_here) {
                while (!i_am_here) {
                    sf::sleep(sf::seconds(0.1));
                }
                combine=0;
            } else if (c==(char)'v') {
                crossing=2; mirror=4;combine=1;
                area="NewYork";
                cubic=true;
                and_now_i_am_here=true;
                launch_SFMLGL2_b();
                while (!i_am_here) {
                    sf::sleep(sf::seconds(0.1));
                }
                combine=0;
            } else if (c==(char)'z') {
                crossing=2; mirror=4;combine=1;
                area="Utrecht";
                cubic=true;
                and_now_i_am_here=true;
                launch_SFMLGL2_b();
                while (!i_am_here) {
                    sf::sleep(sf::seconds(0.1));
                }
                combine=0;
            } else if (c==(char)'y') {
                crossing=2; mirror=4;combine=1;
                area="Rio";
                cubic=true;
                and_now_i_am_here=true;
                launch_SFMLGL2_b();
                while (!i_am_here) {
                    sf::sleep(sf::seconds(0.1));
                }
                combine=0;
            } else if (c==(char)'w') {
                crossing=2; mirror=4;combine=1;
                area="Amsterdam";
                cubic=true;
                and_now_i_am_here=true;
                launch_SFMLGL2_b();
//                while (!and_now_i_am_here) {
                while (!i_am_here) {
                    sf::sleep(sf::seconds(0.1));
                }
                combine=0;
            }
        }
    }

    go_on=0;
//    if (server_running) {
//        printf("Shutting down server\n");
//        NonCtrlHandler(SIGINT);
//    }
    while (animator_running) sf::sleep((sf::seconds(0.2)));
//    EXITPROGRAM();

    printf("WINAPI=%d\n",WINAPI_RETURN);
//    sf::sleep(sf::milliseconds(1000));
//    terminate_animator();
//    GenerateConsoleCtrlEvent(CTRL_C_EVENT, 0);
    exit(WINAPI_RETURN);
//    exit(EXIT_SUCCESS);
	return 0;
//	return WINAPI_RETURN;
//	exit(WINAPI_RETURN);
}
extern void make_colors_from_blocks();
extern void multiple_regions_to_voxelfiles(char* root);

int WINAPI WinMain2()
{
//    flying();
 //   launch_FLY_PLAY();

//    sf::sleep(sf::seconds(2));
    if (argv_main==NULL) {
        argv_main = new char* [30];
        for (int n=0; n<30; n++) {
            argv_main[n] = new char [1024];
            strcpy(argv_main[n],"");
        }
        argc_main=0;
    }

    HINSTANCE hInstance=hInstance_pass;
    HINSTANCE hPrevInstance=hPrevInstance_pass;
    LPSTR lpCmdLine=lpCmdLine_pass;
    int nCmdShow=nCmdShow_pas;

    HWND hWndMain;
    int    argc;
    char** argv;
    char*  arg;
    int    index;
    int    result;

//define language decimal point / comma .... shit!
    std::lconv* lc;
//    setlocale(LC_ALL, "");
//    setlocale(LC_NUMERIC, "C");
//    setlocale(LC_NUMERIC, "en_US");
//    setlocale(LC_NUMERIC, "");

    lc = localeconv();
    printf("Currency symbol: '%s' (%d)\n",lc->currency_symbol , lc->int_curr_symbol );
    printf("Decimal token:   '%s'\n",lc->decimal_point );

/*
    setlocale(LC_ALL, "");
    lc = localeconv();
    printf("Currency symbol: '%s' (%d)\n",lc->currency_symbol , lc->int_curr_symbol );
    printf("Decimal token:   '%s'\n",lc->decimal_point );

    setlocale(LC_NUMERIC, "en_US");
    lc = localeconv();
    printf("Currency symbol: '%s' (%d)\n",lc->currency_symbol , lc->int_curr_symbol );
    printf("Decimal token:   '%s'\n",lc->decimal_point );

printf("hoppa");
*/
//    setlocale(LC_ALL, "en_US.UTF-8");
//change if dirs can not be created / found
//debug    strcpy(lpCmdLine,"mceditor 9 190 0 4");
//    strcpy(lpCmdLine,"");
    argc = 1;
    arg  = lpCmdLine;
    while (arg[0] != 0)
    {
        while (arg[0] != 0 && arg[0] == ' ')
        {
            arg++;
        }
        if (arg[0] != 0)
        {
            argc++;
            while (arg[0] != 0 && arg[0] != ' ')
            {
                arg++;
            }
        }
    }
    argv = (char**)malloc(argc * sizeof(char*));
    arg = lpCmdLine;
    index = 1;
    while (arg[0] != 0)
    {
        while (arg[0] != 0 && arg[0] == ' ')
        {
            arg++;
        }
        if (arg[0] != 0)
        {
            argv[index] = arg;
            index++;
            while (arg[0] != 0 && arg[0] != ' ')
            {
                arg[0]=tolower(arg[0]);
                arg++;
            }
            if (arg[0] != 0)
            {
                arg[0] = 0;
                arg++;
            }
        }
    }
    char filename[200];
    GetModuleFileName(NULL, filename, 200);
    argv[0] = filename;

    sprintf(writer,"usage: %s [ ? ] [ reconnect ] [ server | client ipaddress ] [ udp | tcp ] [ portnumber ]\n",argv[0]);
    strcpy(commandline,writer);


    int param_connect=0;
    int i,n=1;
    int add=0;
    if (argc>1) {
        if (argc>1) n=atoi(argv[2]);
        //program.exe world2nbtdir <WorldSaveDir>
        //reads:    all the r.*.*.mca files from <WorldSaveDir>/region/r.*.*.mca
        //writes:   <WorldSaveDir>/nbt/r.*.*/<ColumnNumber>.gzip.nbt (nbt's containing column from region files)
        //call:     from directory above the <WorldSaveDir>/region/r.*.* director(y/ies).
        if (        strcmp(argv[1],"world2nbtdir"   )==0) { READ_WORLD_TO_DIRS(             argv[2]);   send_message='x';   return 0; }

        //program.exe world2nbt <WorldSaveDir>
        //reads:    all the r.*.*.mca files from <WorldSaveDir>/region/r.*.*.mca
        //writes:   <WorldSaveDir>/nbt/r.*.*.gzip.nbt (nbt's containing one region file)
        //call:     from directory above the <WorldSaveDir>/region/r.*.* director(y/ies).
        else if (        strcmp(argv[1],"world2nbt"      )==0) { READ_WORLD_TO_GZIPS(            argv[2]);   send_message='x';   return 0; }

        //program.exe header2nbt <r.x.z>.mca
        //reads:    region file <r.x.z>.mca
        //writes:   <r.x.z>.header.gzip.nbt & <r.x.z>.header.txt in current dir
        else if (   strcmp(argv[1],"header2nbt"     )==0) { region_header(                  argv[2]);   send_message='x';   return 0; }

        //program.exe mca2nbtdir <r.x.z>.mca
        //reads:    region file <r.x.z>.mca
        //writes:   <r.x.z>/<ColumnNumber>.gzip.nbt files
        else if (   strcmp(argv[1],"mca2nbtdir"    )==0) { READ_REGION_TO_DIR(                    argv[2]);   send_message='x';   return 0; }

        //program.exe mca2nbt <r.x.z>.mca
        //reads:    region file <r.x.z>.mca
        //writes:   <r.x.z>.gzip.nbt file
        else if (   strcmp(argv[1],"mca2nbt"    )==0) { READ_REGION_TO_GZIP(                        argv[2]);   send_message='x';   return 0; }

        //program.exe nbtdir2mca <r.x.z>
        //reads:    <r.x.z>/*.gzip.nbt files (nbt files containing columns)
        //writes:   region file <r.x.z>.mca
        //call:     from directory above <r.x.z>/*.gzip.nbt
        else if (   strcmp(argv[1],"nbtdir2mca"    )==0) { WRITE_REGION_FROM_DIRS(                   argv[2]);   send_message='x';   return 0; }
        else if (   strcmp(argv[1],"nbtdir2mcanbt"    )==0) { WRITE_REGION_FROM_DIRS_NBT(                   argv[2]);   send_message='x';   return 0; }

        //program.exe nbtdir2world <WorldSaveDir>
        //reads:    <WorldSaveDir>/nbt/r.*.*/<ColumnNumber>.gzip.nbt
        //writes:   all the r.*.*.mca to <WorldSaveDir>/nbt/r.*.*.mca
        //call:     from directory above the <WorldSaveDir>/nbt/r.*.* director(y/ies).

        else if (   strcmp(argv[1],"nbtdir2world"  )==0) { MAKE_MCA_FROM_WORLD_NBT_GZIPS(  argv[2]);   send_message='x';   return 0; }

        else if (   strcmp(argv[1],"nbtdir2worldnbt"  )==0) { MAKE_MCA_FROM_WORLD_NBT(  argv[2]);   send_message='x';   return 0; }

        //program.exe worldnbt2mca <WorldName>.gzip.nbt | <WorldName>.zlib.nbt | <WorldName>.nbt
        //reads:    <WorldName>.gzip.nbt or <WorldName>.zlib.nbt or <WorldName>.nbt
        //writes:   all r.*.*.mca region files contained in <WorldName>.gzip.nbt or <WorldName>.zlib.nbt or <WorldName>.nbt
        //call:     from <WorldSaveDir>/nbt
        else if (   strcmp(argv[1],"worldnbt2world"  )==0) { WRITE_WORLD_TO_MCA(             argv[2]);   send_message='x';   return 0; }

        //program.exe nbt2mca <r.x.z>.gzip.nbt | <r.x.z>.zlib.nbt | <r.x.z>.nbt
        //reads:    <r.x.z>.gzip.nbt or <r.x.z>.zlib.nbt or <r.x.z>.nbt file
        //writes:   <r.x.z>.mca region file contained in <r.x.z>.gzip.nbt or <r.x.z>.zlib.nbt or <r.x.z>.zlib.nbt
        //call:     from <WorldSaveDir>/nbt
        else if (   strcmp(argv[1],"nbt2mca"    )==0) { WRITE_REGION(                   argv[2]);   send_message='x';   return 0; }
        else if (   strcmp(argv[1],"nbt2world"  )==0) { WRITE_ALL_REGIONS(               argv[2]);   send_message='x';   return 0; }
        else if (   strcmp(argv[1],"repack"  )==0) { REPACK(               argv[2]);   send_message='x';   return 0; }
        else if (   strcmp(argv[1],"regions"    )==0) {
            if (argc>2) {
                if (strcmp(argv[2],"cubic")==0) {
                    cubic=true;
                } else {
                    strcpy(voxel_filename,argv[2]);
                    mcglobal=atoi(argv[2]);
                    if (mcglobal==0)
                        printf("One .voxel file: %s\n",voxel_filename);
                    if (argc>3) {
                        if (strcmp(argv[3],"cubic")==0) {
                            cubic=true;
                        } else {
                            mcglobal=atoi(argv[3]);
                        }
                        if (argc>4) {
                            mcglobal=atoi(argv[4]);
                        }
                    }
                }
//                printf("strlen(voxel_filename)=%d\n",strlen(voxel_filename));
            } else {
                strcpy(voxel_filename,"");
            }
            if (mcglobal!=0) printf("mcglobal=%d ",mcglobal);
            send_message='r';
        }

        else if (   strcmp(argv[1],"mo"    )==0) {
            make_object=true;
            make_regions=true;
            if (argc>2) {
                strcpy(voxel_filename,argv[2]);
                printf("One .voxel file: %s\n",voxel_filename);
                one_region_voxel_files_to_region_files(false, voxel_filename);
            } else {
                strcpy(voxel_filename,"");
                region_voxel_files_to_region_files(false);
            }
//            make_object=false;
//            make_regions=false;
            ShowTaskBar(true);
            GenerateConsoleCtrlEvent(CTRL_C_EVENT, 0);
//            send_message='x';
//            exit(0);
        }
        else if (   strcmp(argv[1],"object"    )==0) {
            if (argc>2) {
                strcpy(voxel_filename,argv[2]);
                printf("One .voxel file: %s\n",voxel_filename);
            } else {
                strcpy(voxel_filename,"");
            }
            send_message='m';
        }
        else if (   strcmp(argv[1],"minecraft"    )==0) {


            if (argc>2) {
                if (   strcmp(argv[2],"block"    )==0) {
                    make_colors_from_blocks();
//                    sf::sleep(sf::seconds(5.0));

                }
            }
        }
        else if (   strcmp(argv[1],"enschede"    )==0) { send_message='s'; }
        else if (   strcmp(argv[1],"pong"    )==0) { send_message='u'; }
        else if (   strcmp(argv[1],"denhaag"    )==0) { send_message='t'; }
        else if (   strcmp(argv[1],"newyork"    )==0) { send_message='v'; }
        else if (   strcmp(argv[1],"rio"    )==0) { send_message='y'; }
        else if (   strcmp(argv[1],"utrecht"    )==0) { send_message='z'; }
        else if (   strcmp(argv[1],"amsterdam"    )==0) { send_message='w'; }
        else if (   strcmp(argv[1],"font2function"    )==0) {
            font2function();
            send_message='x';
        }
        else if (   strcmp(argv[1],"voxel"    )==0) {
                for (int n=2; n<argc; n++) {
                    strcpy(argv_main[n-2],argv[n]);
                }
                argc_main=argc-2;
                automate=true;
                if (argc>2) { obj_filename=argv[2]; }
                send_message='p';
        }
        else if (   strcmp(argv[1],"region2voxel"    )==0) {
            if (argc>2) {
                region_filename=argv[2];
                printf("All /saves dirs %s\n",region_filename);
            } else {
                region_filename=std::string()+"";
            }
            send_message='A';
        }
        else if (   strcmp(argv[1],"taskbar"    )==0) {
                ShowTaskBar(true);
                send_message='x';
                return 0;
        }
        else if (   strcmp(argv[1],"schematic"    )==0) {
            for (int n=2; n<argc; n++) {
                strcpy(argv_main[n-2],argv[n]);
            }
            argc_main=argc-2;
            printf("argc=%d\n",argc);
            if (argc>2) {
                while (replace_str(argv[2],"\\","/"));
                FILE* TEST;
                if ((TEST=fopen(argv[2],"r"))!=NULL) {
                    fclose(TEST);
                    obj_filename=argv[2];
                    if (argc>3) {
                        if (strcmp(argv[3],"auto")==0) {
                            if (argc>4) {
                                schematic_size=atoi(argv[4]);
                            } else
                                schematic_size=200.0;

                            automate=true;
                            mirror=4;
                            exporter=glm::mat4(1.0f);
                            exporter2=glm::mat4(1.0f);
                            combine=1;
                            area="Models";
                            make_schematic=true;
                            strcpy(MODELS,"../schematics");
                            voxelize_shell(std::string() + obj_filename);
                            send_message='x';
                            return 0;
                        } else {
                            printf("Usage: schematic <filename.obj> [auto]\n");
                        }
                    }
                    send_message='q';
                } else {
                    printf("Usage: schematic <filename.obj> [auto]\n");
//                    send_message='q';
//                    send_message='x';
                }
            }
        }
        else if (   strcmp(argv[1],"mceditor"    )==0) {
            shut_up=1;
            printf("mceditor ");
            if (argc>2) { mcglobal=atoi(argv[2]); printf("%d ",mcglobal); }
            if (argc>3) { mcglobal2=atoi(argv[3]); printf("%d ",mcglobal2); }
            if (argc>4) { mcglobal3=atoi(argv[4]); printf("%d ",mcglobal3); }
            if (argc>5) { mcglobal4=atoi(argv[5]); printf("%d ",mcglobal4); }
            printf("\n");
//            system("/saves/reset_test.bat");
            launch_MCEDITOR();
            sf::sleep(sf::milliseconds(200));
//            MCEDITOR_stop=1;
        }

//        else if (   strcmp(argv[1],"mca"        )==0) { main_nbt(                       argv[2]);   send_message='x';   return 0; }

        else if (   strcmp(argv[1],"test"    )==0) { test_tha_shit(n);   send_message='x';   return 0; }
        else if (   strcmp(argv[1],"test1"    )==0) { test1();   send_message='x';   return 0; }
        else if (   strcmp(argv[1],"test2"    )==0) { test2();   send_message='x';   return 0; }
//        else if (   strcmp(argv[1],"cuberite"    )==0) { main_cuberite(argc-1,&argv[1]);   send_message='x';   return 0; }
        else if (   strcmp(argv[1],"cuberite"    )==0) {
            for (int n=1; n<argc; n++) {
                strcpy(argv_main[n-1],argv[n]);
            }
            argc_main=argc-1;
            send_message='s';
            return 0;
        }

        if (strcmp(argv[1],"list")==0) {
            go_list=1;
        }
        if (strcmp(argv[1],"download")==0 || strcmp(argv[1],"burn")==0) {
            if (strcmp(argv[1],"download")==0) go_download=1;
            else if (strcmp(argv[1],"burn")==0) { go_burn=1; start_burning=1; }
            if (argc>2) {
                if (strcmp(argv[2],"download")==0 || strcmp(argv[2],"burn")==0) {
                    if (strcmp(argv[2],"download")==0) go_download=1;
                    else if (strcmp(argv[2],"burn")==0) go_burn=1;
                }
            }
//            if (go_download) printf("GO DOWNLOADING\n");
//            if (go_burn) printf("GO BURN\n");
            if (!go_download && go_burn) start_burning=1;
        }

        if (strcmp(argv[1],"?")==0)
        {
            MessageBox(NULL, commandline, "PARAMETERS", MB_OK);
            frexit(0);
        }
        if (strcmp(argv[1],"reconnect")==0)
        {
            add=1;
            skiphandshake=1;
            playerleft=0;
        }
        if (strcmp(argv[1+add],"server")==0)
        {
            server=1;
            if (argc>=3+add)
            {
                if (strcmp(argv[2+add],"udp")==0)
                {
                    udp=1;
                    i=3;
                }
                else if (strcmp(argv[2+add],"tcp")==0)
                {
                    tcp=1;
                    i=3;
                }
                else
                {
                    tcp=1;
                    i=2;
                }
            }
            else
            {
                strcpy(portnumber_text,"50001");
                portnumber=50001;
                tcp=1;
                i=4;
            }
            if (argc>=i+1+add)
            {
                portnumber=atoi(argv[i+add]);
                portnumber_int=atoi(argv[i+add]);

                if (portnumber_int<=1 || (portnumber_int>=65536))
                {
                    sprintf(writer,"WRONG PORT NUMBER: %s MUST BE 1-65535\n",argv[i+add]);
                    MessageBox(NULL, writer, "ERROR", MB_OK);
                    frexit(1);
                }
                else
                {
                    strcpy(portnumber_text,argv[i+add]);
                }
            }
            else if (i!=4)
            {
                portnumber=50001;
                strcpy(portnumber_text,"50001");
            }

            param_connect=1;
        }
        else if (strcmp(argv[1+add],"client")==0)
        {
            client=1;
            if (argc<3+add)
            {
                MessageBox(NULL, "NEED IP ADDRESS OF SERVER", "ERROR", MB_OK);
                sprintf(writer,"usage: %s [reconnect][server|client ipaddress] [udp/tcp] [portnumber]\n",argv[0]);
                MessageBox(NULL, writer, "SERVER", MB_OK);
                frexit(0);
            }
            strcpy(connectedip,argv[2+add]);

            if (argc>=4+add)
            {
                if (strcmp(argv[3+add],"udp")==0)
                {
                    udp=1;
                    i=4;
                }
                else if (strcmp(argv[3+add],"tcp")==0)
                {
                    tcp=1;
                    i=4;
                }
                else
                {
                    tcp=1;
                    i=3;
                }
            }
            else
            {
                strcpy(portnumber_text,"50001");
                portnumber=50001;
                tcp=1;
                i=5;
            }
            if (argc>=i+1+add)
            {
                portnumber=atoi(argv[i+add]);
                portnumber_int=atoi(argv[i+add]);

                if (portnumber_int<=1 || (portnumber_int>=65536))
                {
                    sprintf(writer,"WRONG PORT NUMBER: %s MUST BE 1-65535\n",argv[i+add]);
                    MessageBox(NULL, writer, "ERROR", MB_OK);
                    frexit(1);
                }
                else
                {
                    strcpy(portnumber_text,argv[i+add]);
                }
            }
            else if (i!=5)
            {
                portnumber=50001;
                strcpy(portnumber_text,"50001");
            }
            param_connect=1;
        }

    } else {
//        system("/saves/reset_test.bat");
//        launch_MCEDITOR();
//        sf::sleep(sf::milliseconds(2000));
//        MCEDITOR_stop=1;
    }

    free(argv);

    if (!shader_test.loadFromFile("shaders/analyse3d.frag", sf::Shader::Fragment)) { printf("can not load shader shaders/analyse3d.frag\n"); }
//    shader_test.setUniform("texture_current", sf::Shader::CurrentTexture);
    shader_test.setUniform("texture_in", texture_test);
//    shader_test.setUniform("texture_size", sf::Vector2i(texture_test.getSize()));
    shader_test.setUniform("iResolution", sf::Vector2f(texture_test.getSize().x,texture_test.getSize().y));
    states_test.shader = &shader_test;

    logfile((char*)"Allocating memory");

    if (handle_init()==1)
    {
        int msgboxID;
        msgboxID=MessageBox(NULL, "ERROR READING PACMAN.INI FILE", "ERROR",MB_OK);
        frexit(1);
    }

    extern sf::RenderTexture *texturemaxinmem;
    extern sf::RenderTexture **texturemaxinmempoint;
    extern int *used_maxinmem;
    extern sf::Sprite **spritemaxinmempoint;


//    texturemaxinmem = new sf::RenderTexture [MAXINMEM];
//    texturemaxinmempoint = new sf::RenderTexture* [MAXINMEM];
//    used_maxinmem = new int [MAXINMEM];
//    spritemaxinmempoint = new sf::Sprite* [MAXINMEM];

    hInstance2=hInstance;

    logfile((char*)"Initialising sounds");

//    sf::SoundBuffer buffer[10];
//    sf::Music music[10];

    buffer[0].loadFromFile("resources/dp_superpac_wakka.wav");
    sound[0].setVolume(30);
    buffer[1].loadFromFile("resources/jrenergizer.wav");
    buffer[2].loadFromFile("resources/crash_into_wall.wav");
    buffer[3].loadFromFile("resources/intro.wav");
    sound[3].setVolume(50);
    buffer[4].loadFromFile("resources/dp_superpac_wakka.wav");
    sound[4].setVolume(30);
    buffer[5].loadFromFile("resources/jrenergizer.wav");
    buffer[6].loadFromFile("resources/pacman_eatghost.wav");
    buffer[7].loadFromFile("resources/Kung Fu Old School Hit 09.wav");
    buffer[8].loadFromFile("resources/boem.wav");
    buffer[9].loadFromFile("resources/boem.wav");

    sound[0].setBuffer(buffer[0]);
    sound[1].setBuffer(buffer[1]);
    sound[2].setBuffer(buffer[2]);
    sound[3].setBuffer(buffer[3]);
    sound[4].setBuffer(buffer[4]);
    sound[5].setBuffer(buffer[5]);
    sound[6].setBuffer(buffer[6]);
    sound[7].setBuffer(buffer[7]);
    sound[8].setBuffer(buffer[8]);
    sound[9].setBuffer(buffer[9]);

    music[0].openFromFile("resources/ding.flac");
    music[1].openFromFile("resources/orchestral.ogg");
//    music[2].openFromFile("resources/boem.mp3");

    strcpy(reg,"Pacman_Graphics");
    int t=time(0);
//    int r;
//    char s[20];
//    srand(t);
//    r=rand();
//    sprintf(s,"%d",r);

//    strcat(reg,s);

//    if (client==1)
//        strcat(reg,"_Client");
//    if (server==1)
//        strcat(reg,"_Server");

    if(!RegClass(reg,hInstance))
    {
        MessageBox(0,"There was an error and the app must now exit","Error!",MB_OK);
        return 0;
    }

    logfile((char*)"Creating windows screen and SFML screen");

//sf::Window window(sf::VideoMode(800, 600), "OpenGL", sf::Style::Default, sf::ContextSettings(32));

//    if (!glfwInit())
//    {
//        std::cerr << "Failed to initialize GLFW." << std::endl;
//        return -1;
//    }

    hWndMain = CreateWin(hInstance, reg, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
    hWndMain2=hWndMain;
//    hWndMain=hWndMain2;
    hglrc_sfmlview1 = wglGetCurrentContext();
//    printf("wglGetCurrentContext()=%u\n",hglrc_sfmlview1);

    hdc_sfmlview1 = wglGetCurrentDC() ;
//    printf("wglGetCurrentDC()=%u\n",hdc_sfmlview1);

//    sfmlview1_handle=SFMLView1.getSystemHandle();
//    printf("SFMLView1.getSystemHandle()=%u\n",hdc_sfmlview1);
    SFMLView1.setActive(false);

    hdc2_sfmlview1 = GetDC(hWndMain);
//    printf("GetDC(hWndMain)=%u\n",hdc2_sfmlview1);

    printf("\n");

    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::ContextSettings contextSettings(0,0,2,3,0);
    contextSettings.antialiasingLevel = 0;
    contextSettings.stencilBits = 0;
    contextSettings.depthBits=24;
//    contextSettings.sRgbCapable = false;
//    SFMLView1.create(sf::VideoMode(1920,1080, desktop.bitsPerPixel), reg, sf::Style::None,contextSettings);

//    SFMLView1.create(sf::VideoMode(1920,1080), "PACMAN", sf::Style::Resize | sf::Style::Titlebar | sf::Style::Close, contextSettings);

    SFMLView1.create(sf::VideoMode(1920,1080), "PACMAN", sf::Style::Resize | sf::Style::Fullscreen, contextSettings);
    vm=0;
    SFMLView1.setSize(sf::Vector2u(1920,1080));
    SFMLView1.setPosition(sf::Vector2i(0,0));


//    launch_FLY_PLAY();
//    sf::sleep(sf::seconds(1.0));



    SFMLView1.setActive(true);



//        sf::sleep(sf::seconds(0.1));
//        launch_FLY_PLAY();



    hglrc_sfmlview1 = wglGetCurrentContext();
//    printf("wglGetCurrentContext()=%u\n",hglrc_sfmlview1);

    hdc_sfmlview1 = wglGetCurrentDC() ;
//    printf("wglGetCurrentDC()=%u\n",hdc_sfmlview1);

    sfmlview1_handle=SFMLView1.getSystemHandle();
//    printf("SFMLView1.getSystemHandle()=%u\n",hdc_sfmlview1);
    SFMLView1.setActive(false);


//    main_fly_de_poppa(1,SFMLView1,0.0);
//    sf::sleep(sf::seconds(4.0));

    hdc2_sfmlview1 = GetDC(hWndMain);
//    printf("GetDC(hWndMain)=%u\n",hdc2_sfmlview1);
//    sf::Vector2u size=( sf::Vector2u(1920,1080) );
//    sf::Vector2i pos=( sf::Vector2i(0,0) );
//    SFMLView1.setSize(size);
//    SFMLView1.setPosition(pos);

//    SFMLView1.requestFocus();
//    SFMLView1.setActive(true);
//    SFMLView1.resetGLStates();

sf::ContextSettings windowSettings = SFMLView1.getSettings();
/*
std::cout
	<< "windowSettings.DepthBits: " << windowSettings.depthBits << "\n"
	<< "windowSettings.StencilBits: " << windowSettings.stencilBits << "\n"
	<< "windowSettings.AntialiasingLevel: " << windowSettings.antialiasingLevel << "\n"
	<< "windowSettings.MajorVersion: " << windowSettings.majorVersion << "\n"
	<< "windowSettings.MinorVersion: " << windowSettings.minorVersion << "\n";
*/
extern bool glew_initor;
extern bool glwf_initor;

/*
    if (glew_initor==false) {
        glewExperimental = true;
        if (glewInit() != GLEW_OK)
        {
            std::cerr << "Failed to initialize GLEW." << std::endl;
            return -1;
        }
        glew_initor=true;
    }
*/

/*
    if (glwf_initor==false) {
        if (!glfwInit())
        {
            std::cerr << "Failed to initialize GLFW." << std::endl;
            return -1;
        }
        glwf_initor=true;
    }
*/
    WindowHandle=SFMLView1.getSystemHandle();
    logfile((char*)"Loading shader(s)");

//crossing
extern bool file_exists(const char * filename);
//    if (file_exists("shaders/wave.vert")) printf("exists!!!\n");
    if (!m_shader.loadFromFile("shaders/wave.vert", sf::Shader::Vertex))
    {
        MessageBox(
            NULL,
            "SHADER shaders/wave.vert NOT FOUND",
            "ERROR",
            MB_ICONEXCLAMATION | MB_OK | MB_TOPMOST
        );
        frexit(0);
    }
    m_shader.setUniform("wave_amplitude", sf::Vector2f(5.0, 5.0));
    states.shader = &m_shader;

    if (!m_shader2.loadFromFile("shaders/wave2.vert", sf::Shader::Vertex))
    {
        MessageBox(
            NULL,
            "SHADER shaders/wave2.vert NOT FOUND",
            "ERROR",
            MB_ICONEXCLAMATION | MB_OK | MB_TOPMOST
        );
        frexit(0);
    }
    m_shader2.setUniform("wave_amplitude", sf::Vector2f(5.0, 5.0));
    states2.shader = &m_shader2;

    SFMLView1.setVerticalSyncEnabled(true);

    SetWindowLong(hWndMain, GWL_STYLE, 0);
    ShowWindow(hWndMain, SW_MAXIMIZE);
    UpdateWindow(hWndMain);

    ShowCursor(TRUE);

    if (param_connect==1 && skiphandshake==0)
    {
        TextField = CreateWindow("EDIT",
                                 "",
                                 WS_VISIBLE | WS_CHILD | WS_BORDER | ES_READONLY | ES_MULTILINE | ES_AUTOVSCROLL,
                                 10, 90, 565, 400,
                                 hWndMain2, (HMENU) 3, NULL, NULL);

        SendMessage(TextField, EM_SETSEL, -1, -1);
        if (client==1)
        {
            SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"CLIENT");
            SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"CONNECTING TO IP ADDRESS: ");
            SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)connectedip);
            SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"\r\nCONNECTING TO PORT: ");
            SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)portnumber_text);
            SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"\r\nPROTOCOL: ");
            if (udp==1)
                SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"UDP\r\n");
            if (tcp==1)
                SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"TCP\r\n");
        }
        else if (server==1)
        {
            SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"SERVER");
            SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"\r\nLISTENING ON PORT: ");
            SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)portnumber_text);
            SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"\r\nPROTOCOL: ");
            if (udp==1)
                SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"UDP\r\n");
            if (tcp==1)
                SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"TCP\r\n");
        }

        if (client==1)
        {
            if (udp==1)
                client=runUdpClient(connectedip,portnumber);
            else if (tcp==1)
                client=runTcpClient(connectedip,portnumber);
        }
        else if (server==1)
        {
            if (udp==1)
                server=runUdpServer(portnumber);
            else if (tcp==1)
                server=runTcpServer(portnumber);
        }
        else
        {
            MessageBox(
                NULL,
                "ERROR ON CONNECTING",
                "ERROR",
                MB_ICONEXCLAMATION | MB_OK | MB_TOPMOST
            );
            frexit(0);
        }
        if (server==0 && client==0)
        {
            MessageBox(
                NULL,
                "ERROR ON CONNECTING",
                "ERROR",
                MB_ICONEXCLAMATION | MB_OK | MB_TOPMOST
            );
            frexit(0);
        }
        else
            connected=1;

        DestroyWindow(TextField);
    }
    if (param_connect==1 && skiphandshake==1)
    {
        connected=1;
        TextField = CreateWindow("EDIT",
                                 "",
                                 WS_VISIBLE | WS_CHILD | WS_BORDER | ES_READONLY | ES_MULTILINE | ES_AUTOVSCROLL,
                                 10, 90, 565, 400,
                                 hWndMain2, (HMENU) 3, NULL, NULL);

        SendMessage(TextField, EM_SETSEL, -1, -1);
        if (client==1)
        {
            SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"CLIENT");
            SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"CONNECTING TO IP ADDRESS: ");
            SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)connectedip);
            SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"\r\nCONNECTING TO PORT: ");
            SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)portnumber_text);
            SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"\r\nPROTOCOL: ");
            if (udp==1)
                SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"UDP\r\n");
            if (tcp==1)
                SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"TCP\r\n");
        }
        else if (server==1)
        {
            SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"SERVER");
            SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"\r\nLISTENING ON PORT: ");
            SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)portnumber_text);
            SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"\r\nPROTOCOL: ");
            if (udp==1)
                SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"UDP\r\n");
            if (tcp==1)
                SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"TCP\r\n");
        }

        if (client==1)
        {
            logfile((char*)"Reconnecting client");
            if (udp==1)
                client=reconnectUdpClient(connectedip,portnumber);
            else if (tcp==1)
                client=reconnectTcpClient(connectedip,portnumber);
        }
        else if (server==1)
        {
            logfile((char*)"Reconnecting server");
            if (udp==1)
                server=reconnectUdpServer(portnumber);
            else if (tcp==1)
                server=reconnectTcpServer(portnumber);
        }
        if (server==0 && client==0)
        {
            MessageBox(
                NULL,
                "ERROR ON CONNECTING",
                "ERROR",
                MB_ICONEXCLAMATION | MB_OK | MB_TOPMOST
            );
            frexit(0);
        }
        DestroyWindow(TextField);
    }

    if (connected==0 && (MULTIPLAYER==1 || MULTIPLAYER==-1))
    {
        logfile((char*)"Initialising network");
        INIT_NETWORK();
    }

    while (connecting==1)
    {
//?????? if -> while
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if(msg.message == WM_QUIT)
                break;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        if (connecting==1 && client==0)
        {
            Sleep(10);
        }
        if (connected==1 && client==1)
        {
            DestroyWindow(TextField);
            DestroyWindow(TextBox);
            DestroyWindow(SendButton);
            connecting=0;
        }
    }
    if (connected==1)
    {
        if (tcp==1)
        {
            listener1.setBlocking(false);
            listener2.setBlocking(false);
            internet_socket_tcp1.setBlocking(false);
            internet_socket_tcp2.setBlocking(false);
        }
        else if (udp==1)
        {
            internet_socket_udp1.setBlocking(false);
            internet_socket_udp2.setBlocking(false);
        }
    }

    ShowCursor(FALSE);

//window
    ShowWindow(hWndMain, SW_HIDE);
    if (!screensaver) SFMLView1.requestFocus();
    SFMLView1.setActive(true);

    font.loadFromFile("resources/ariblk.ttf");
//    font.loadFromFile("resources/consolab.ttf");
    text.setFont(font);
    text.setFillColor(sf::Color::White);
    text.setCharacterSize(144);
    make_text(0);
    set_mytext(0);
    set_mytext2();
    set_print_text();
    if (connected==1)
    {
        for (int t=0; t<10; t++)
        {
            logfile((char*)"Connected");
            text.setString("!!!  CONNECTED  !!!");
            text.setPosition(200,400);
            text.setFillColor(sf::Color::White);
            SFMLView1.draw(text);
            SFMLView1.display();
            Sleep(50);
            text.setFillColor(sf::Color::Red);
            SFMLView1.draw(text);
            SFMLView1.display();
            Sleep(100);
        }
    }

    text.setFillColor(sf::Color::White);
    text.setCharacterSize(24);

    int x,y;

    spritedot.setTexture(sfml_mazedot,false);
    spritedot2.setTexture(sfml_mazedot2,false);

    if (connected==1 && server==1 && skiphandshake==0)
    {
        skipinit=0;
    }
    else
        skipinit=0;

    logfile((char*)"Starting loop");
    //SFMLView1.requestFocus();
    SFMLView1.setActive(false);

/*
    winmain_running=1;
    launch_animator();
    while (winmain_running==1) {
        sf::sleep(sf::milliseconds(5000));
    }
*/

//    launch_FLY_PLAY();
//    sf::sleep(sf::milliseconds(1000));

    while(go_on==1)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if(msg.message == WM_QUIT)
                break;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            HANDLEEVENTS();
            int bit=1;
            int playsoundnumber=1;
            while (playsound>=1 && burn_subs==0)
            {
                if ((soundloop&bit)==bit)
                {
                    sound[playsoundnumber-1].setLoop(1);
                    sound[playsoundnumber-1].play();
                    soundloop=soundloop-bit;
                }
                if ((soundoff&bit)==bit)
                {
                    sound[playsoundnumber-1].setLoop(0);
                    sound[playsoundnumber-1].stop();
                    soundloop=soundloop&(1023-bit);
                    soundoff=soundoff-bit;
                }
                if ((playsound&bit)==bit)
                {
                    if (sound[playsoundnumber-1].getStatus() != sf::Sound::Playing)
                    {
                        sound[playsoundnumber-1].setLoop(0);
                        sound[playsoundnumber-1].play();
                    }
                }
                playsound=playsound&(2048-1-bit);
                bit=bit*2;
                playsoundnumber++;
            }
            soundloop=0;
            soundoff=0;
            playsound=0;
            if (playmusic>=1)
            {
                printf("playmusic>=1\n");
                if (music[playmusic-1].getStatus() != sf::Music::Playing) {
                    music[playmusic-1].stop();
                    music[playmusic-1].play();
                }
                else {
                    music[playmusic-1].stop();
                    music[playmusic-1].play();
                }
                playmusic=0;
            }

            DoAnimate2(hInstance,hWndMain);

            if (totalused>MAXINMEM)
            {
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
        }
    }
    sound[0].stop();
    sound[1].stop();
    sound[2].stop();
    sound[3].stop();
    sound[4].stop();
    sound[5].stop();
    sound[6].stop();
    sound[7].stop();
//    SFMLView1.close();
//    printf("SFMLView1.close();\n");
    ShowTaskBar(true);
//    if (memory_set==1) {
//        printf("cleanupmem();\n");
//        cleanupmem();
//    }
    WINAPI_RETURN=(int)(msg.wParam);
    printf("Exiting main thread, closing window(s)\n");
//    DestroyWindow(hWndMain);
//    SFMLView1.close();
    return (int)(msg.wParam);
}



ATOM RegClass(char *ClassName,HINSTANCE hInstance)
{
    WNDCLASSEX wcex = {0};

    wcex.cbClsExtra = 0;
    wcex.cbSize = sizeof(wcex);
    wcex.cbWndExtra = 0;
    wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wcex.hCursor = 0;
    wcex.hIcon = 0;
    wcex.hIconSm = 0;
    wcex.hInstance = hInstance;
    wcex.lpfnWndProc = WinProc;
    wcex.lpszClassName = ClassName;
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);

    return RegisterClassEx(&wcex);
}


HWND CreateWin(HINSTANCE hInstance, char *ClassName,int Width, int Height)
{
    HWND hWnd;
    RECT rWindow;

    rWindow.left	= 0;
    rWindow.right	= Width;
    rWindow.top	    = 0;
    rWindow.bottom	= Height;

    AdjustWindowRect(&rWindow,WS_OVERLAPPED | WS_SYSMENU | WS_CLIPCHILDREN, false);
    hWnd = CreateWindowEx(WS_EX_APPWINDOW, ClassName, reg,				0,CW_USEDEFAULT, CW_USEDEFAULT, rWindow.right - rWindow.left, rWindow.bottom - rWindow.top,NULL, NULL, hInstance, NULL);
    SetWindowPos(hWnd, HWND_TOP, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), 0L);
    ShowCursor(FALSE);
    return hWnd;
}

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
    DWORD dwThreadID = ::GetWindowThreadProcessId(hwnd, NULL);
    if (dwThreadID == static_cast<DWORD>(lParam))
    {
        ::BringWindowToTop(hwnd);    // Breakpoint
        //      ::SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
        return FALSE;
    }

    return TRUE;
}

void ShowTaskBar(bool show)
{
    HWND taskbar = FindWindow((char*)("Shell_TrayWnd"), NULL);
    HWND start = FindWindow((char*)("Button"), NULL);

    if (taskbar != NULL)
    {
        ShowWindow(taskbar, show ? SW_SHOW : SW_HIDE);
        UpdateWindow(taskbar);
    }
//    if (start != NULL)
//    {
//        ShowWindow(start, show ? SW_SHOW : SW_HIDE);
//        UpdateWindow(start);
//    }
}
