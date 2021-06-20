#include <conio.h>
#define PI 3.141592653589793
#define SFML_STATIC
#undef UNICODE
#include <wchar.h>
#include <winsock2.h>
#include <io.h>
#include "WinMain.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sys/stat.h>
#include <iostream>
//#define _WIN32_WINNT 0x0500
#define WINVER 0x0500
#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif
//#include <conio.h>
#include <Windows.h>
#include <TlHelp32.h>
#include <tchar.h>
#include <signal.h>
#include <Winuser.h>
#include <assert.h>
#include <vector>
#include <cmath>
#include <time.h>
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include "StreamSelector.hpp"
#include <SFML/System/Mutex.hpp>
#include <SFML/Network/IpAddress.hpp>
#include <sfeMovie/Movie.hpp>
#include "MediaInfo.hpp"
#include <SFML/OpenGL.hpp>
#include <GL/glext.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <dirent.h>
#include "keylist.hpp"
#include <string.h>

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

int move_config=0;
extern int RGBA;
extern sf::Sprite sprite_from_crop;
extern int iFrame;
static std::string GetFileName(const std::string& filepath)
{
    if (filepath.find_last_of("/\\") != std::string::npos)
        return filepath.substr(1+filepath.find_last_of("/\\"),filepath.length());
    return "";
}

extern sf::VertexArray m_pointCloud3;
extern void set_cube();
extern sf::ContextSettings contextSettings;
extern void shift_back();

extern bool add_to_region;

bool plot_only=false;

extern int vm;
int plot_all_factor=0;
float move_speed=1.0;
int move_speed_int=1.0;
sf::Clock move_clock;
extern int shut_up;
std::string areas(int q);
std::string area="";
extern bool flushing;
extern bool running_3d[];
extern int is_activated_window[];
extern int request_3d_x;
extern int request_3d_y;
extern int main_get3d(int argc, char **argv);
extern int do3d();
extern int do3dview();
extern void OPENGL_THREAD();
extern void launch_SFMLGL();
extern sf::Mutex diff_draw;
extern int different_draw;
extern int MCEDITOR_stop;
extern int mcglobal;
extern sf::Texture texture_cube;
extern int plot_cubes;
extern float iZoom;
//extern "C" int main_mca2nbt(int argc, char *argv[]);
extern void test1();
extern void test2();
extern void launch_SERVER();
extern void NonCtrlHandler(int a_Signal);
extern int server_running;
extern int go_on;
extern int animator_running;
extern int winmain_running;
extern void launch_MCEDITOR();
int happening=1;

extern bool voxel_to_file;

extern void test_write_to_and_read_from_memory();
extern int xallocator_test(void);
extern void do_world(char * filename);
extern void READ_WORLD(char* filename);
extern void READ_REGION(char* filename);
extern void test_tha_shit(int n);
extern main_cuberite(int argc,char** argv);
extern int flying();

extern int main_nbt();
extern void do_one(char* filename);
//extern int main_mca2nbt(int argc, char *argv[]);
//extern "C" int main_nbt();
int testing=0;
//
extern sf::Sound sound[];
extern int monitor_off;
void start_stop_bukkit_thread_server();
void send_through_bukkitserver_mcrcon(char * command);
void start_dos_command_thread();
float ffmpeg_fixed_x=1920.0/2.0;
float ffmpeg_fixed_y=1080.0/2.0;
float internet_fixed_x=1920.0/2.0;
float internet_fixed_y=1080.0/2.0;
float movie_fixed_x=1920.0/2.0;
float movie_fixed_y=1080.0/2.0;
float movie2_fixed_x=1920.0/2.0;
float movie2_fixed_y=1080.0/2.0;
extern int texture_ready;
extern int isrecording;
extern int isplaying;
extern int burn_subs;
int ESCAPE_PRESSED=0;
void burn_next_sub();
void start_get_videos_thread();
int record_debug=0;
extern int handle_init();
extern void frexit(int err_no);
extern void cleanupmem();
extern int first;
extern char send_message;
extern sf::Clock clock_ghost;
extern int trim(char * text);
extern int select_from_list2(char *filename, char * path, int next);
char macro_name[200]="";
extern void parse_command(char * text);
extern void command_par(int what, ...);
extern void read_keylist_hpp();
int reset_map=0;
extern HINSTANCE hInstance2;
extern HWND hWndMain2;
extern void DoAnimate2(HINSTANCE,HWND);
void insert_event(sf::Keyboard::Key code,int MODE);
extern int select_macro(char *filename, char * path);
extern void get_videos();
extern int burn_next_sub_ready;

#define EVENT_ALT 1
#define EVENT_SHIFT 2
#define EVENT_CONTROL 4
#define EVENT_SYSTEM 8

extern int playsound;
double scale_slow=0.0;
double speed_slowx=0.0;
double speed_slowy=0.0;
double ddp_loop=0.0;

double render_rel_pos_in_map_x=0.0;
double render_rel_pos_in_map_y=0.0;
double rel_pos_in_map_x1=0.0;
double rel_pos_in_map_x2=0.0;
double rel_pos_in_map_y1=0.0;
double rel_pos_in_map_y2=0.0;
double rel_pos_in_map_x=0.0;
double rel_pos_in_map_y=0.0;

extern int generate_tiles;
float fpstime_factor=1.0;
extern float fpstime;
float set_time=0.0;
char going_to[2000]="";
extern int replace_str(char *str, char *orig, char *rep);
void next_loc();
extern int select_location(char *filename, char * path);
void adapt_speed();
int zoom_off=1;
double hold=-1.0;
int hold_level=0;
int soft_jump=0;
extern double loadvalue_float(char *filenaam);
extern void savevalue_float(char *filenaam, double value);
void pacman_to_rel_pos();
extern void rel_pos_to_pacman();
extern double scale_jump;
extern void insert_key(WPARAM key);
extern HWND TextBox, SendButton, TextField;
extern int udp;
extern int tcp;
extern unsigned short portnumber;
extern int runTcpServer(unsigned short port);
extern int runTcpClient(char * ipaddress, unsigned short port);
extern int runUdpServer(unsigned short port);
extern int runUdpClient(char * ipaddress, unsigned short port);
extern int reconnectTcpServer(unsigned short port);
extern int reconnectTcpClient(char * ipaddress, unsigned short port);
extern int reconnectUdpServer(unsigned short port);
extern int reconnectUdpClient(char * ipaddress, unsigned short port);
extern int server;
extern int client;
extern HINSTANCE hInstance2;
extern HWND hWndMain2;
extern char connectedip[];
extern void frexit(int err_no);


int DO_ADAPT=0;
int DO_ZOOM_IN=0;
int DO_ZOOM_OUT=0;
extern int F1;
extern int F2;
extern int F4;
extern int playerleft;
extern void goto_partner();
extern int old_shift;
extern int start_posx_mem;
extern int start_posy_mem;
extern int render_picturex_mem;
extern int render_picturey_mem;
extern int render_posx_mem;
extern int render_posy_mem;
extern int picturex_mem;
extern int picturey_mem;
extern int posx_mem;
extern int posy_mem;
extern int render_picturex;
extern int render_picturey;
extern int render_posx;
extern int render_posy;
extern int start_posx;
extern int start_posy;
extern int movie_posx,movie_posy;
extern int movie2_posx,movie2_posy;
extern int ffmpeg_posx,ffmpeg_posy;
extern int internet_posx,internet_posy;
extern int maxpixelsx;
extern int maxpixelsy;
extern void home_map();
extern void get_ffmpegfile();
extern void set_position1();
extern void set_position2();
extern void get_position1();
extern void get_position2();
extern void movie_to_ffmpeg(sf::Texture * MyTexture_movie, sf::Texture * MyTexture_ffmpeg);
extern void convert_to_scale(sf::Texture * MyTexture,sf::Sprite * MySprite);
extern void soften_edge(sf::Texture * MyTexture);
extern int again1;
extern int again2;
void cleanupbitmaps_mazes();
void cleanupbitmaps();
extern int PRELOAD;
extern void CreateAll();
extern void clear_map();
extern void SENDGOTOPOS();
int pacman=1;

float fspeed_ghost_all=1.0;
extern void draw2(char *towrite, int xpos, int ypos, sf::Color inner, sf::Color outer);
extern void do_command(int what);
int loadallmaps=0;
int loadallmaps_level=0;
extern int playmusic;
extern int MUL_SAS_ZOOM_DIRECTION[];
extern int MUL_SAS_MAX_ZOOM[];
extern char **MUL_SAS_URL;
extern char **MUL_SAS_ORDER;
extern int MUL_COUNTER;
extern char **MUL_SAS_EXTENSION;

extern void gen_all_mipmaps();
int sound_counter=0;
sf::SoundBufferRecorder recorder;
int flippo=0;
extern void goto_ghost();
extern void kiki();
extern int pictures_to_ffmpegfile();
extern int pictures_to_ffmpegfile_2();
extern int pictures_to_ffmpegfile_3();
extern int pictures_to_ffmpegfile_4();
int SAS_MAX_ZOOM=100;
int show_shade_map=1;
extern int mul;
extern int MUL_COUNTER;
int offset_picture_x;
int offset_picture_y;
int SAS_STARTX_a=0;
int SAS_STARTY_a=0;
int draw_model=0;
int set_transparant=1;
extern sf::RenderStates picture_states;
extern float plot_all_znear;
extern float plot_all_zfar;
extern float plot_all_fovyInDegrees;
float plot_all_translate_x=0.0;
float plot_all_translate_y=0.0;
float plot_all_translate_z=0.0;
float plot_all_rotate_x=0.0;
float plot_all_rotate_y=0.0;
float plot_all_rotate_z=0.0;
extern int skipclear;
void rot_texture_as_is(sf::Texture * MyTexture, sf::Sprite * MySpriteIn);
void rot_texture_90(sf::Texture * MyTexture);
int end_on_record=0;
extern int go_go;
extern void merge_back_to_front();
int kleur_back=0;
int kleur_front=0;
extern void set_mapper();
extern int totalused;
extern void go_save_some_bitmaps();
extern void ReadOneBitmap(int picturex,int picturey);
extern char **used;
extern int plot_all;
extern int crop_x;
extern int crop_x_size;
extern int crop;

extern void batch_pictures();
extern void batch_pictures2();

extern combine_front_to_back();
void reverse_maze();
extern sf::Mutex mutje;
extern int cool;
void ffmpegfile_to_maze();
void ffmpegfile_to_maze2();
extern int check_mem;
extern int load_vertex_filename();
extern int load_buffer_filename();
extern int load_fragment_filename(int up_down);
extern int f8_repeat;
extern int flop;
extern int play_rate;
extern int rate_count;
int movieextern=1;
extern void playing_end();
extern void Screenget3();
extern int playing_start(char * filename);
extern void playing(sf::Image * image);

extern void ShowTaskBar(bool show);
extern int selector;
extern int selector_item;

struct handler_struct
{
    int blending;
    int plot_front;
    int show;
    int tile;
    int shader;
};


extern struct handler_struct handler[];
extern char URLDIR[];
extern char internet_naam[];
extern int select_line_from_file_w(char * line_of_text, char * path);
extern wchar_t line_w[];
int yellow=0;
extern sf::Text mytext;
extern sf::Text mytext2;
extern int file_is_open_line_from_file;
extern int max_line_from_file;
extern int next_textfile;
extern int total_textfile;
extern int start_textfile;
extern FILE* file_from_file;
extern char naam_from_file[];
extern sf::Mutex loader_mutex;
extern int select_line_from_file(char *filename, char * path, int next);
extern int select_nextline(char *filename, char * path);
extern int select_textfile(char *filename, char * path);
void text_to_ffmpeg(char * in,int font_size, sf::Color inner, sf::Color outer);
void text_to_ffmpeg_w(wchar_t * in,int font_size, sf::Color inner, sf::Color outer, sf::Uint32 type);
void text_to_ffmpeg_w2(int var_font, char * in,int font_size, sf::Color inner, sf::Color outer, sf::Color background, float outline, sf::Uint32 text_type);
extern int perform_quit;
int var_font=0;
int exiting=0;
extern int monitor_loop;
void plot_some();
extern int tune;
extern std::string hoppa;
char *com[2]= {"Program","../scripts/fun.chai"};
extern int doscript(int argc, char *argv[]);
extern int scripting();
int SAS_ZOOM_DIRECTION=1;
extern sf::Vector2i position;
extern void LOADALLBITMAPS_MAZES();
extern int pacman;
int blank_maze=0;
extern void font_to_ffmpeg();
extern void make_text(int next_font);
extern void set_mytext(int next_font);
extern int force_loading;
extern sf::Event event;
VOID HANDLEKEY(WPARAM wparam, sf::Event event);
extern int position1x;
extern int position1y;
extern int position2x;
extern int position2y;
extern char LEVELDIR[];
extern char PICTUREDIR[];
int ESCAPE=0;
extern int kill1,kill2,kill3;
extern sf::Vector2i mytotal1;
extern sf::Vector2i mytotal2;
extern sf::Vector2i mytotal3;
extern int loader1_active;
extern int loader2_active;
extern int loader3_active;
extern void launch_background_loader_one();
extern void launch_background_loader_two();
extern void launch_background_loader_three();
extern int reload_init();
int  SAVEALL=0;
extern double xdiff1;
extern double ydiff1;
extern double xdiff2;
extern double ydiff2;
extern  START_LOADING_FOR_ALL_BITMAPS();
extern int dont_stop;
extern int render_picturex;
extern int render_picturey;
extern int render_posx;
extern int render_posy;
extern int maxpixelsx;
extern int maxpixelsy;
extern int mem_picturex;
extern int mem_picturey;
extern int mem_posx;
extern int mem_posy;
extern float mem_fposx;
extern float mem_fposy;
extern int new_picturex;
extern int new_picturey;
extern int new_posx;
extern int new_posy;
extern float new_fposx;
extern float new_fposy;

extern double smooth_x;
extern double smooth_y;
extern int SAS_STARTX;
extern int SAS_STARTY;
extern int SAS_ZOOM;
extern char SAS_URL[];
extern char MAPDIR[];
extern sf::Color background_color[];
extern int GetGoogleMap(char * url,sf::Texture * result);

int autodraw=0;
int mouse_move=0;
sf::Image Inter;
extern int start_posx;
extern int start_posy;

// http://mt1.google.com/vt/lyrs=m@169000000&hl=nl&x=2107&y=1350&zoom=5

int get_map_x,get_map_y,get_map_zoom=100;
double Fget_map_x,Fget_map_y;

int thread_run_sub=0;
extern int shaders();
int one_pixel=0;
float scale_now=1.0;
float old_scale;
extern int disp_text;
void ghost_next();
extern int update_buffer_shader(int up_down);
extern void follow_ghost_pos();
extern void save_mazeoff();
extern int read_mazeoff(int nopos);
extern int MAZEOFF;
extern int shade_map;
extern int shade_main;
extern int plot_shader;
extern int newmaze;
extern int difficulty;
extern int update_shader();
extern int fragment_shader;
extern int vertex_shader;
extern int buffer_shader;

extern sf::RenderTexture texture_from_buffer;
extern sf::RenderTexture texture_from_buffer2;
extern sf::Texture sfml_mazedot;
extern sf::Texture sfml_mazedot2;
extern int smooth;
extern int crossing;
extern int blending;
extern int MyBlending;
extern int MyBlendMode_num;
extern int MyBlend_colorSrcFactor_num;
extern int MyBlend_colorDstFactor_num;
extern int MyBlend_colorEquation_num;
extern int MyBlend_alphaSrcFactor_num;
extern int MyBlend_alphaDstFactor_num;
extern int MyBlend_alphaEquation_num;
extern sf::BlendMode MyBlendingMode;
extern sf::BlendMode MyBlendingMode_movie;
extern sf::BlendMode MyBlendMode[];
extern void set_blending();
extern void Screenshot();
extern int record_pause;
extern int record_screen;
extern int record_screen_num;
extern int recording_type;
extern int recording_start(int x, int y);
extern void recording_end();
extern void recording_m_orig(sf::Image * image);
extern int recording_start_m_orig();
extern char error_msg[];
extern int error_flag;
extern sf::RenderWindow SFMLView1;
extern int movie;
extern int movie2;
extern int sync;
extern sf::Texture texture_from_movie_new;
extern sf::Texture texture_from_movie2_new;
extern int live_movie_is_mp3;
extern int live_movie2_is_mp3;
extern int timer_movie;
extern sf::Time time_movie;
extern int timer_movie2;
extern sf::Time time_movie2;
extern sfe::Movie* live_movie;
extern sfe::Movie *live_movie2;
extern int DONTSAVEFILES;
extern int BITMAPSX;
extern int BITMAPSY;
extern int eatmode;
extern int drawmazes;
extern int level;
extern int check_dir(int BITMAPSX,int BITMAPSY,int level);
extern bool file_exists2(const char * filename);
extern int overwrite1;
extern int overwrite2;
extern int connected;
extern char writer[];
extern void SEND(char *towrite);
extern void save_map();
extern void save_map_last();
extern void load_map_last();
extern void load_map();
extern int levelnotsaved;
extern bool file_exists(const char * filename);
extern int loadmap;
extern void save_maze(int lastmap);
extern int loaded;
extern int next;
extern int totalchanged;
extern void SAVEALLBITMAPS();
extern int pen;
extern int pen_mode;
extern void cleanupbitmaps_mazes();
extern int combine;
int pacman_move=0;
extern int loaded_from_maze;
extern void load_maze(int lastmap);
extern void save_maze(int lastmap);
extern int follow_ghost;
extern int 	*pos_ghostx;
extern int 	*pos_ghosty;
extern float 	*fpos_ghostx;
extern float 	*fpos_ghosty;
extern float 	*fspeed_ghostx;
extern float 	*fspeed_ghosty;
extern int 	*check;
extern int follow_ghost_num;
extern void DRAWALLMAZES();
extern int err_level;
extern int totalfiles;
extern int totalfiles_mazes;
extern int maxpicturex;
extern int maxpicturey;
extern char *line;
extern void blitter(char * line, int mode);
extern struct stat buffer;
extern char **files;
extern char **files_mazes;
extern int number;
extern void set_pacman();
extern int posx;
extern int posy;
extern float fposx;
extern float fposy;
extern int long_jump;
extern int old_pen;
extern int old_pen_mode;
extern int mazetype;
extern int internetfile;
extern int ffmpegfile;
extern void make_dark_transparant(sf::Texture * MyTexture);
extern void make_black_transparant(sf::Texture * MyTexture);
extern void make_white_transparant(sf::Texture * MyTexture);
extern void make_color_transparant(sf::Texture * MyTexture);
extern void add_border(sf::Texture * MyTexture);
extern void setffmpegfile();
extern void setmoviefile();
extern void setmoviefile2();
extern void setinternetfile();
extern void setcanvasfile();
extern int PIXELISBLACKTHRESHOLD;
extern int PIXELISWHITETHRESHOLD;
extern int PIXELISCOLORTHRESHOLD;
extern int PIXELISCOLOR_R;
extern int PIXELISCOLOR_G;
extern int PIXELISCOLOR_B;
extern int toggle_point;
extern int picturex;
extern int picturey;
extern int real_posx2;
extern int real_posy2;
extern int totalpicturex;
extern int totalpicturey;
extern int maxnumber;
extern int num_ghost;
extern int hunt;
extern int ghost;
extern int formula;
extern int follow_ghost_start;
extern int best_ghost_num;
extern int forced_jump;
extern float fbest_distance;
extern int size_internet;
extern int size_canvas;
extern int size_ffmpeg;
extern int size_movie;
extern int size_movie2;
extern int rotate_movie;
extern int rotate_movie2;
extern int rotate_ffmpeg;
extern int rotate_internet;
extern int rotate_canvas;
extern sf::Sprite sprite_from_canvas;
extern sf::Sprite sprite_from_internet;
extern sf::Sprite sprite_from_ffmpeg;
extern sf::Sprite sprite_from_movie;
extern sf::Sprite sprite_from_movie2;
extern sf::Texture texture_from_internet;
extern sf::Texture texture_from_ffmpeg;
extern sf::Texture texture_from_movie_new;
extern sf::Texture texture_from_movie2_new;
extern sfe::Movie* live_movie;
extern StreamSelector *live_selector;
extern sfe::Movie *live_movie2;
extern StreamSelector *live_selector2;
extern int GetFileFromInternet(char * naam);
extern float rot_speed_movie;
extern float rot_speed_movie2;
extern float rot_speed_ffmpeg;
extern float rot_speed_internet;
extern float rot_speed_canvas;
extern float rotation_movie;
extern float rotation_movie2;
extern float rotation_ffmpeg;
extern float rotation_internet;
extern float rotation_canvas;
extern char error_msg[];
extern int error_flag;
extern char error_msg2[];
extern int error_flag2;
extern char error_msg3[];
extern int error_flag3;
extern char error_msg4[];
extern int error_flag4;
extern char error_msg5[];
extern int error_flag5;
extern void savedata(char *naam, int data);
extern int shift;
extern int blend_on_movie;
extern char MACRODIR[];
extern char SCRIPTDIR[];
extern char MOVIEDIR[];
extern int playmovie(char* naam);
extern int lookahead;
extern select_movie(char *filename, char * path);
extern int force_game;
extern int mirror;
extern int startmovie(char* naam);
extern void stopmovie();
extern void updatemovie();
extern int startmovie2(char* naam);
extern void stopmovie2();
extern void updatemovie2();
extern int playmovie(char* naam);
extern char movie_name[];
extern int GETBLENDINGPICTURE(char* naam);
extern int GETPICTURE(char* naam);
extern int GET_LAT_LON_FROM_FILE_LIST(char *naam);
extern int reload;
extern int old_draw;
extern int loadbackground;
extern void CLEANBITMAPS();
extern void LOADALLBITMAPS();
extern void ReadBitmaps4();
extern void ReadBitmaps2();
extern int plot_internetfile;
extern int plot_ffmpegfile;
extern int plot_moviefile;
extern int plot_moviefile2;
extern int plot_front,plot_back;
extern int reset_normal;
extern void plotplot();
extern int hunt_max;
extern int hunt_counter;
extern int goexit;
extern void EXITPROGRAM();
extern int SEED;
extern int LOADED_SEED;
extern int big_large;
extern int pressed;
extern void HALT();
extern int movie_move;
extern int movie2_move;
extern int ffmpeg_move;
extern int internet_move;
extern int speedx;
extern int speedy;
extern float fspeedx;
extern float fspeedy;
extern int speedx_new;
extern int speedy_new;
extern float fspeedx_new;
extern float fspeedy_new;
extern int maze_up;
extern int maze_down;
extern int maze_left;
extern int maze_right;
extern int maze_up_new;
extern int maze_down_new;
extern int maze_left_new;
extern int maze_right_new;
extern int toggle_point;
extern int F1;
extern int MAXINMEM;
extern sf::RenderTexture texturemaxinmem[];
extern void putinmazeSFML_all();
extern void putinmazeSFML_all_xtheny();

int width_mm=0;
int height_mm=0;
int width_pixels=0;
int height_pixels=0;
int overlap_mm=0;
int overlap_pixels=0;
std::string paper_name="";
sf::RectangleShape rectangle_paper;
sf::RectangleShape rectangle_paper_inner;
sf::RectangleShape rectangle_paper_outer;
int paper_select=0;

int rectangle_paper_pos_x=0;
int rectangle_paper_pos_y=0;
int rectangle_paper_count_x=1;
int rectangle_paper_count_y=1;
int ppi_x,ppi_y;

int paper_format() {
    paper_select++;
    if (paper_select>26) {
        paper_select=0;
        paper_name="";
    }

    if (paper_select==1)        {   paper_name=std::string()+"Poster landscape";    width_mm=1800;  height_mm=1200; overlap_mm=3;   width_pixels=21260;     height_pixels=14174;    overlap_pixels=36; }
    else if (paper_select==2)   {   paper_name=std::string()+"Poster portrait";     width_mm=1200;  height_mm=1800; overlap_mm=0;   width_pixels=14174;     height_pixels=21260;    overlap_pixels=00; }
//    else if (paper_select==2)   {   paper_name=std::string()+"Poster portrait";     width_mm=1200;  height_mm=1800; overlap_mm=3;   width_pixels=14174;     height_pixels=21260;    overlap_pixels=36; }
    else if (paper_select==3)   {   paper_name=std::string()+"A0 Landscape";	    width_mm=1189;  height_mm=841;  overlap_mm=3;   width_pixels=14044;     height_pixels=9934;     overlap_pixels=36; }
    else if (paper_select==4)   {   paper_name=std::string()+"A0 Portrait";	        width_mm=841;   height_mm=1189; overlap_mm=3;   width_pixels=9934;      height_pixels=14044;    overlap_pixels=36; }
    else if (paper_select==5)   {   paper_name=std::string()+"A1 Landscape";	    width_mm=841;   height_mm=594;  overlap_mm=3;   width_pixels=9934;      height_pixels=7016;     overlap_pixels=36; }
    else if (paper_select==6)   {   paper_name=std::string()+"A1 Portrait";	        width_mm=594;   height_mm=841;  overlap_mm=3;   width_pixels=7016;      height_pixels=9934;     overlap_pixels=36; }
    else if (paper_select==7)   {   paper_name=std::string()+"A2 Landscape";	    width_mm=594;   height_mm=420;  overlap_mm=3;   width_pixels=7016;      height_pixels=4962;     overlap_pixels=36; }
    else if (paper_select==8)   {   paper_name=std::string()+"A2 Portrait";	        width_mm=420;   height_mm=594;  overlap_mm=3;   width_pixels=4962;      height_pixels=7016;     overlap_pixels=36; }
    else if (paper_select==9)   {   paper_name=std::string()+"A3 Landscape";	    width_mm=420;   height_mm=297;  overlap_mm=3;   width_pixels=4962;      height_pixels=3508;     overlap_pixels=36; }
    else if (paper_select==10)  {   paper_name=std::string()+"A3 Portrait";	        width_mm=297;   height_mm=420;  overlap_mm=3;   width_pixels=3508;      height_pixels=4962;     overlap_pixels=36; }
    else if (paper_select==11)  {   paper_name=std::string()+"A4 Landscape";	    width_mm=297;   height_mm=210;  overlap_mm=3;   width_pixels=3508;      height_pixels=2480;     overlap_pixels=36; }
    else if (paper_select==12)  {   paper_name=std::string()+"A4 Portrait";	        width_mm=210;   height_mm=297;  overlap_mm=3;   width_pixels=2480;      height_pixels=3508;     overlap_pixels=36; }
    else if (paper_select==13)  {   paper_name=std::string()+"A5 Landscape";	    width_mm=210;   height_mm=148;  overlap_mm=3;   width_pixels=2480;      height_pixels=1748;     overlap_pixels=36; }
    else if (paper_select==14)  {   paper_name=std::string()+"A5 Portrait";	        width_mm=148;   height_mm=210;  overlap_mm=3;   width_pixels=1748;      height_pixels=2480;     overlap_pixels=36; }
    else if (paper_select==15)  {   paper_name=std::string()+"A6 Landscape";	    width_mm=148;   height_mm=105;  overlap_mm=3;   width_pixels=1748;      height_pixels=1240;     overlap_pixels=36; }
    else if (paper_select==16)  {   paper_name=std::string()+"A6 Portrait";	        width_mm=105;   height_mm=148;  overlap_mm=3;   width_pixels=1240;      height_pixels=1748;     overlap_pixels=36; }
    else if (paper_select==17)  {   paper_name=std::string()+"A7 Landscape";	    width_mm=105;   height_mm=74;   overlap_mm=3;   width_pixels=1240;      height_pixels=874;      overlap_pixels=36; }
    else if (paper_select==18)  {   paper_name=std::string()+"A7 Portrait";	        width_mm=74;    height_mm=105;  overlap_mm=3;   width_pixels=874;       height_pixels=1240;     overlap_pixels=36; }
    else if (paper_select==19)  {   paper_name=std::string()+"TEST";	            width_mm=41;    height_mm=23;   overlap_mm=3;   width_pixels=480;       height_pixels=270;      overlap_pixels=36; }
    else if (paper_select==20)  {   paper_name=std::string()+"TEST NO OVERLAP";	    width_mm=41;    height_mm=23;   overlap_mm=0;   width_pixels=480;       height_pixels=270;      overlap_pixels=0;  }
    else if (paper_select==21)  {   paper_name=std::string()+"1920 x 1080";	        width_mm=162;   height_mm=91;   overlap_mm=0;   width_pixels=1920;      height_pixels=1080;     overlap_pixels=0;  }
    else if (paper_select==22)  {   paper_name=std::string()+"3840 x 2160";	        width_mm=324;   height_mm=182;  overlap_mm=0;   width_pixels=3840;      height_pixels=2160;     overlap_pixels=0;  }
    else if (paper_select==23)  {   paper_name=std::string()+"7680 x 4320";	        width_mm=648;   height_mm=364;  overlap_mm=0;   width_pixels=7680;      height_pixels=4320;     overlap_pixels=0;  }
    else if (paper_select==23)  {   paper_name=std::string()+"7680 x 4320";	        width_mm=648;   height_mm=364;  overlap_mm=0;   width_pixels=7680;      height_pixels=4320;     overlap_pixels=0;  }
    else if (paper_select==24)  {   paper_name=std::string()+"5760 x 3240";	        width_mm=486;   height_mm=273;  overlap_mm=0;   width_pixels=5760;      height_pixels=3240;     overlap_pixels=0;  }
    else if (paper_select==25)  {   paper_name=std::string()+"4800 x 2700";	        width_mm=405;   height_mm=227;  overlap_mm=0;   width_pixels=4800;      height_pixels=2700;     overlap_pixels=0;  }
    else if (paper_select==26)  {   paper_name=std::string()+"14400 x 21600";	    width_mm=920;   height_mm=1350; overlap_mm=3*3;   width_pixels=14400;     height_pixels=21600;    overlap_pixels=36*6; }

    if (paper_select) {
        ppi_x=(int)(0.5+(float)width_pixels/((float)width_mm/25.4));
        ppi_y=(int)(0.5+(float)height_pixels/((float)height_mm/25.4));
        sprintf(error_msg2,"PAPERSIZE #%d: %s  WIDTH=%d, HEIGHT=%d, OVERLAP=%d (mm)  PPI: X=%d,Y=%d",paper_select,paper_name.c_str(),width_mm,height_mm,overlap_mm,ppi_x,ppi_y);
        rectangle_paper.setFillColor(sf::Color(0,0,0,0));
        rectangle_paper.setOutlineColor(sf::Color(255,0,0,128));
        rectangle_paper.setOutlineThickness(-overlap_pixels);
        rectangle_paper.setSize(sf::Vector2f(width_pixels+overlap_pixels*2,height_pixels+overlap_pixels*2));
        rectangle_paper.setPosition((float)rectangle_paper_pos_x,(float)rectangle_paper_pos_y);

        rectangle_paper_inner.setFillColor(sf::Color(0,0,0,0));
        rectangle_paper_inner.setOutlineColor(sf::Color(255,255,255,255));
        rectangle_paper_inner.setOutlineThickness(1);
        rectangle_paper_inner.setSize(sf::Vector2f(width_pixels,height_pixels));
        rectangle_paper_inner.setPosition((float)(rectangle_paper_pos_x+overlap_pixels),(float)(rectangle_paper_pos_y+overlap_pixels));

        rectangle_paper_outer.setFillColor(sf::Color(0,0,0,0));
        rectangle_paper_outer.setOutlineColor(sf::Color(255,0,0,255));
        rectangle_paper_outer.setOutlineThickness(-1);
        rectangle_paper_outer.setSize(sf::Vector2f(width_pixels+overlap_pixels*2,height_pixels+overlap_pixels*2));
        rectangle_paper_outer.setPosition((float)rectangle_paper_pos_x,(float)rectangle_paper_pos_y);
    } else {
        strcpy(error_msg2,"PAPERSIZE OFF");
    }
    error_flag2=1;
}

extern bool got_next;
void do_nextlevel()
{
    char naam[400];
    if (goexit==1)
    {
        goexit=0;
        got_next=true;
        return;
    }
    if (levelnotsaved==1)
    {
        strcpy(error_msg,"LEVEL NOT SAVED!!! PRESS AGAIN TO LOAD NEXT");
        error_flag=1;
        levelnotsaved=0;
        got_next=true;
        return;
    }
    if (DONTSAVEFILES==0)
    {
//??????????
        if (1 || drawmazes==0)
        {
            SAVEALLBITMAPS();
            CLEANBITMAPS();
        }
    }
    drawmazes=1;
    if (force_game==1)
        cleanupbitmaps_mazes();
    if (loaded==1)
    {
//        if (shade_map>0) save_mazeoff();
        level++;
//        sprintf(naam,"levels/%dx%d/%03d/maze.dat",BITMAPSX,BITMAPSY,level);
        sprintf(naam,"%s/%dx%d/%03d/maze.dat",LEVELDIR,BITMAPSX,BITMAPSY,level);
        if (!file_exists(naam))
        {
            level=1;
            if (difficulty<4)
                difficulty++;
//            sprintf(naam,"levels/%dx%d/%03d/maze.dat",BITMAPSX,BITMAPSY,level);
            sprintf(naam,"%d/%dx%d/%03d/maze.dat",LEVELDIR,BITMAPSX,BITMAPSY,level);
            while (!file_exists(naam)&& level<50 )
            {
                level++;
//                sprintf(naam,"levels/%dx%d/%03d/maze.dat",BITMAPSX,BITMAPSY,level);
                sprintf(naam,"%s/%dx%d/%03d/maze.dat",LEVELDIR,BITMAPSX,BITMAPSY,level);
//						sprintf(naam,"levels/%dx%d/maze%d.dat",BITMAPSX,BITMAPSY,level);
            }
            if (level==50)
                level=1;
        }
        if (connected==1)
        {
            sprintf(writer,"T=LEVEL,LEVEL=%d,\0",level);
            SEND(writer);
        }
        loaded_from_maze=1;
        load_maze(level);
        if (force_game==1 && mazetype!=0)
        {
            newmaze=1;
        }
    }
    else
    {
//        SEED=time(0);
        if (connected==1)
        {
            sprintf(writer,"T=MAZE,BIGLARGE=%d,SEED=%d,LEVEL=%d,\0",big_large,SEED,level);
            SEND(writer);
        }
    }
    next=1;
    got_next=true;
}

sf::Clock kp;

char picture_name[2000];

VOID HANDLECHAR(WPARAM wparam)
{
/*
    if( sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::RAlt) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::RControl) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::LSystem) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::RSystem) )
            return;
*/
    if (!event.type==sf::Event::TextEntered) return;
//    if (event.key.alt || event.key.control || event.key.system) return;
    kp.restart();

    char filename[400];
    char naam[2000];
    int x,y;
    FILE *testfile;
    std::string texture_name;
    switch((wchar_t)wparam)
    {

    /*
        case '1':
            if (blending==2)
            {
                if (MyBlend_colorSrcFactor_num<9)
                    MyBlend_colorSrcFactor_num++;
                else
                    MyBlend_colorSrcFactor_num=0;
                MyBlendMode_num=4;
                set_blending();
                break;
            }
            difficulty=1;
            strcpy(error_msg,"DIFFICULTY EASY");
            error_flag=2;
            break;
        case '2':
            if (blending==2)
            {
                if (MyBlend_colorDstFactor_num<9)
                    MyBlend_colorDstFactor_num++;
                else
                    MyBlend_colorDstFactor_num=0;
                MyBlendMode_num=4;
                set_blending();
            break;
            }
            difficulty=2;
            strcpy(error_msg,"DIFFICULTY NORMAL");
            error_flag=2;
            break;
        case '3':
            if (blending==2)
            {
                if (MyBlend_colorEquation_num<2)
                    MyBlend_colorEquation_num++;
                else
                    MyBlend_colorEquation_num=0;
                MyBlendMode_num=4;
                set_blending();
                break;
            }
            difficulty=3;
            strcpy(error_msg,"DIFFICULTY HARD");
            error_flag=2;
            break;
        case '4':
            if (blending==2)
            {
                if (MyBlend_alphaSrcFactor_num<9)
                    MyBlend_alphaSrcFactor_num++;
                else
                    MyBlend_alphaSrcFactor_num=0;
                MyBlendMode_num=4;
                set_blending();
                break;
            }
            difficulty=4;
            strcpy(error_msg,"DIFFICULTY ULTRA");
            error_flag=2;
            break;
        case '5':
            if (blending==2)
            {
                if (MyBlend_alphaDstFactor_num<9)
                    MyBlend_alphaDstFactor_num++;
                else
                    MyBlend_alphaDstFactor_num=0;
                MyBlendMode_num=4;
                set_blending();
            }
            break;
        case '6':
            if (blending==2)
            {
                if (MyBlend_alphaEquation_num<2)
                    MyBlend_alphaEquation_num++;
                else
                    MyBlend_alphaEquation_num=0;
                MyBlendMode_num=4;
                set_blending();
            }
            break;

    */
    case '!':
        if (blending==2)
        {
            if (MyBlend_colorSrcFactor_num>0)
                MyBlend_colorSrcFactor_num--;
            else
                MyBlend_colorSrcFactor_num=9;
            MyBlendMode_num=4;
            set_blending();
        }
        break;
    case '@':
        if (blending==2)
        {
            if (MyBlend_colorDstFactor_num>0)
                MyBlend_colorDstFactor_num--;
            else
                MyBlend_colorDstFactor_num=9;
            MyBlendMode_num=4;
            set_blending();
        }
        break;
    case '#':
        if (blending==2)
        {
            if (MyBlend_colorEquation_num>0)
                MyBlend_colorEquation_num--;
            else
                MyBlend_colorEquation_num=2;
            MyBlendMode_num=4;
            set_blending();
        }
        break;
    case '$':
        if (blending==2)
        {
            if (MyBlend_alphaSrcFactor_num>0)
                MyBlend_alphaSrcFactor_num--;
            else
                MyBlend_alphaSrcFactor_num=9;
            MyBlendMode_num=4;
            set_blending();
        }
        break;
    case '%':
        if (blending==2)
        {
            if (MyBlend_alphaDstFactor_num>0)
                MyBlend_alphaDstFactor_num--;
            else
                MyBlend_alphaDstFactor_num=9;
            MyBlendMode_num=4;
            set_blending();
        }
        break;
    case '^':
        if (blending==2)
        {
            if (MyBlend_alphaEquation_num>0)
                MyBlend_alphaEquation_num--;
            else
                MyBlend_alphaEquation_num=2;
            MyBlendMode_num=4;
            set_blending();
        }
        break;
//    case '0':
//        Screenshot();
//        break;
    case 'r':
        if (record_screen==0)
        {
            reload_init();
            record_screen=1;
            play_rate=1;
            end_on_record=0;
            sound_counter=0;
        }
        else
        {
            record_screen=0;
            play_rate=1;
            record_pause=0;
            clock_ghost.restart();
            burn_subs=0;
            texture_ready=0;
            isrecording=0;
//            the_time=0.0;
        }

        if (record_screen==1)
        {
            if (recording_type==0)
            {
                record_screen_num=0;
                if (recording_start(1920,1080)!=0)
                {
                    strcpy(error_msg,"RECORDING_START() FAILED");
                    error_flag=1;
                    record_screen=0;
                }
                else
                {
                    flop=0;
                    rate_count=play_rate-1;
                    record_pause=1;
                    SFMLView1.setVerticalSyncEnabled(true);
//                    iFrame=0;
                }
            }
            else if (recording_type==1)
            {
                if (movieextern==0)
                {
                    record_screen_num=0;
                    if (recording_start_m_orig()!=0)
                    {
                        strcpy(error_msg,"RECORDING_START_M_ORIG() FAILED");
                        error_flag=1;
                        record_screen=0;
                    }
                    else
                    {
                        sprintf(error_msg,"RECORDING MOVIE 'b' ORIGINAL SIZE %d x %d",texture_from_internet.getSize().x,texture_from_internet.getSize().y);
                        error_flag=1;
                        record_pause=0;
                        SFMLView1.setVerticalSyncEnabled(true);
                        play_rate=10;
                    }
                }
                else
                {
                    strcpy(error_msg,"NO MOVIE SELECTED WITH 'b'");
                    error_flag=1;
                    record_screen=0;
                }
            }
//            if (record_screen==1 && movie==0)
//            {
//                detour_movie();
//            }
        }
        else
        {
            if (sync==1)
                SFMLView1.setVerticalSyncEnabled(true);
            else
                SFMLView1.setVerticalSyncEnabled(false);
            record_screen=0;
            record_pause=0;
            sf::sleep(sf::microseconds(100));
            strcpy(error_msg2,"FLUSHING RECORD PIPE...");
            error_flag2=1;
            draw2(error_msg2,770,400,sf::Color::Red,sf::Color::White);
            SFMLView1.display();

            if (recording_type==0)
                recording_end();
        }

        if (record_screen==1 && record_pause==0 && movie==0 && live_movie_is_mp3==0) //mafkees
        {
            time_movie=live_movie->getPlayingOffset();
            if (tune==1)
                live_movie->pause();
//                timer_movie=10;
        }
        if (record_screen==1 && record_pause==0 && movie2==0 && live_movie2_is_mp3==0)
        {
            time_movie2=live_movie2->getPlayingOffset();
            if (tune==1)
                live_movie2->pause();
//                timer_movie2=10;
        }
        break;
    case 'R':
        if (record_screen==1)
        {
            if (record_pause==0)
            {
                play_rate=0;
                record_pause=1;
                if (sync==1)
                    SFMLView1.setVerticalSyncEnabled(true);
                else
                    SFMLView1.setVerticalSyncEnabled(false);
                /*
                                if (sf::SoundRecorder::isAvailable() == true) {
                                    recorder.stop();
                                    const sf::SoundBuffer& buffer = recorder.getBuffer();
                                    char filename[1000];
                                    sprintf(filename,"../record/%d.wav",sound_counter);
                                    buffer.saveToFile(filename);
                                    sound_counter++;
                                }
                */
            }
            else
            {
                play_rate=1;
                record_pause=0;
                SFMLView1.setVerticalSyncEnabled(false);
                /*
                                if (sf::SoundRecorder::isAvailable() == true) {
                                    recorder.start(44100);
                                }
                */
            }
        }
        else
        {
            if (recording_type==0)
            {
                recording_type=1;
                strcpy(error_msg,"RECORDING ONLY 'b' MOVIE ORIGINAL SIZE, PRESS r TO RECORD");
                if (movieextern!=0)
                {
                    strcat(error_msg,", NO MOVIE ('b') YET SELECTED!");
                    error_flag=1;
                }
            }
            else if (recording_type==1)
            {
                recording_type=0;
                strcpy(error_msg,"RECORDING TOTAL SCREEN SIZE (1920x1080)");
                error_flag=1;
            }
        }
        break;
    case 'e':
        if (eatmode==0) {
            eatmode=1;
            skipclear=1;
        }  else if (eatmode==1) {
            eatmode=2;
        }  else {
            eatmode=0;
            skipclear=0;
        }
        if (drawmazes==0 && eatmode==1)
        {
            strcpy(error_msg,"SETTING EAT MODE=OFF WHEN DRAWMODE=OFF AND SAVE FILES=OFF!!!");
            error_flag=1;
            eatmode=0;
            DONTSAVEFILES=1;
        }
        else
        {
//            strcpy(error_msg,"SETTING SAVE FILES=OFF!!!");
//            if (eatmode==1)
//                DONTSAVEFILES=1;
        }
        break;
    case 'Z':
//change
        check_dir(BITMAPSX,BITMAPSY,level);
//        sprintf(naam,"levels/%dx%d/%03d/map.dat",BITMAPSX,BITMAPSY,level);
        sprintf(naam,"%s/%dx%d/%03d/map.dat",LEVELDIR,BITMAPSX,BITMAPSY,level);
//			if (level==0) sprintf(naam,"levels/%dx%d/lastmap.dat",BITMAPSX,BITMAPSY);
//			else sprintf(naam,"levels/%dx%d/map%d.dat",BITMAPSX,BITMAPSY,level);
        if (file_exists2(naam) && overwrite1==0)
        {
            overwrite1=1;
            break;
        }
        else
            overwrite1=1;
        if (overwrite1==1)
        {
            if (shade_map>0)
                save_mazeoff();
            if (connected==1)
            {
                sprintf(writer,"T=SAVEMAP,\0");
                SEND(writer);
            }
            overwrite1=0;
            if (level==0)
                save_map_last();
            else
                save_map();
            levelnotsaved=0;
//                pen=1; pen_mode=2;
            break;
        }
        break;
    case 'z':
//change
        check_dir(BITMAPSX,BITMAPSY,level);
//        sprintf(naam,"levels/%dx%d/%03d/maze.dat",BITMAPSX,BITMAPSY,level);
        sprintf(naam,"%s/%dx%d/%03d/maze.dat",LEVELDIR,BITMAPSX,BITMAPSY,level);
//			if (level==0) sprintf(naam,"levels/%dx%d/lastmaze.dat",BITMAPSX,BITMAPSY);
//			else sprintf(naam,"levels/%dx%d/maze%d.dat",BITMAPSX,BITMAPSY,level);
        if (file_exists2(naam) && overwrite2==0)
        {
            overwrite2=1;
            break;
        }
        else
            overwrite2=1;
        if (overwrite2==1)
        {
            if (connected==1)
            {
                sprintf(writer,"T=SAVEMAZE,\0");
                SEND(writer);
            }
            overwrite2=0;
            save_maze(level);
            if (shade_map>0)
                save_mazeoff();
            levelnotsaved=0;
//                pen=1; pen_mode=2;
            break;
        }
        break;
    case 'X':
        force_loading=1;
//change
//        sprintf(naam,"levels/%dx%d/%03d/map.dat",BITMAPSX,BITMAPSY,level);
        sprintf(naam,"%s/%dx%d/%03d/map.dat",LEVELDIR,BITMAPSX,BITMAPSY,level);
//			if (level==0) sprintf(naam,"levels/%dx%d/lastmap.dat",BITMAPSX,BITMAPSY);
//			else sprintf(naam,"levels/%dx%d/map%d.dat",BITMAPSX,BITMAPSY,level);
        if (levelnotsaved==1)
        {
            strcpy(error_msg,"LEVEL NOT SAVED!!! PRESS AGAIN TO LOAD ");
            strcat(error_msg,naam);
            error_flag=1;
            levelnotsaved=0;
            break;
        }
        if (file_exists(naam))
        {
            loadmap=1;
            loaded=1;
            if (connected==1)
            {
                sprintf(writer,"T=LOADMAP,\0");
                SEND(writer);
            }
            next=1;
        }
        if (drawmazes==0)
        {
            if (totalchanged>0)
            {
                DONTSAVEFILES=0;
                SAVEALLBITMAPS();
            }
        }
        pen=1;
        pen_mode=2;
//        cleanupbitmaps_mazes();
        break;
    case 'c':
        if (!paper_select) {
            if (combine==1)
                combine=0;
            else
                combine=1;
            if (connected==1)
            {
                sprintf(writer,"T=COMBINE,COMBINE=%d,\0",combine);
                SEND(writer);
            }
        }
        break;
    case 'x':
        force_loading=1;
        //change
        sprintf(naam,"%s/%dx%d/%03d/maze.dat",LEVELDIR,BITMAPSX,BITMAPSY,level);
//			if (level==0) sprintf(naam,"levels/%dx%d/lastmaze.dat",BITMAPSX,BITMAPSY);
//			else sprintf(naam,"levels/%dx%d/maze%d.dat",BITMAPSX,BITMAPSY,level);
        if (levelnotsaved==1)
        {
            strcpy(error_msg,"LEVEL NOT SAVED!!! PRESS AGAIN TO LOAD ");
            strcat(error_msg,naam);
            error_flag=1;
            levelnotsaved=0;
            break;
        }
        if (drawmazes==0)
        {
            if (totalchanged>0)
            {
                DONTSAVEFILES=0;
                SAVEALLBITMAPS();
            }
        }
        if (file_exists(naam))
        {
            loaded=1;
            loaded_from_maze=1;
            load_maze(level);
            if (connected==1)
            {
                sprintf(writer,"T=LEVEL,LEVEL=%d,\0",level);
                SEND(writer);
            }
            pen=0;
            pen_mode=0;
            //          cleanupbitmaps_mazes();
            next=1;
//            if (force_game==1 && mazetype!=0) {
//                newmaze=1;
//            }
        }
        break;
    /*
        case '{':
            if (follow_ghost==1 || flippo==1)
            {
                fspeed_ghostx[follow_ghost_num]=fspeed_ghostx[follow_ghost_num]*0.9;
                fspeed_ghosty[follow_ghost_num]=fspeed_ghosty[follow_ghost_num]*0.9;
            }
            break;
        case '}':
            if (follow_ghost==1 || flippo==1)
            {
                fspeed_ghostx[follow_ghost_num]=fspeed_ghostx[follow_ghost_num]*1.1;
                fspeed_ghosty[follow_ghost_num]=fspeed_ghosty[follow_ghost_num]*1.1;
            }
            break;
    */
    case '(':
    case '[':
    case '<':
        if ((follow_ghost==0 && flippo==0) || (wchar_t)wparam=='(' || (wchar_t)wparam=='<' )
        {
            overwrite1=0;
            overwrite2=0;
            if (drawmazes==0 || 1)
            {
                if (totalchanged>0)
                {
//                    DONTSAVEFILES=0;
                    if (DONTSAVEFILES==0)
                        SAVEALLBITMAPS();
                    else
                        CLEANBITMAPS();
                    strcpy(error_msg,"BITMAPS CHANGED!!! SAVING FIRST BEFORE DRAW MAZE / CHANGE LEVEL");
                    error_flag=1;
                }
                else
                {
                    CLEANBITMAPS();
//                    strcpy(error_msg,"DRAWMAZE=ON");
//                    error_flag=1;
                }
//                drawmazes=1;
//                pen=1;
//                pen_mode=2;
//                strcpy(error_msg,"DRAWMAZE=ON");
//                error_flag=1;
//                if (drawmazes==1) DRAWALLMAZES();
            }
            // save current SAS settings and stored positions (f9/f11). (when changed zoom level with alt-z/ctrl-z. Be carefull when changing them. Messes up mazeoff.dat otherwise.
//            if (shade_map==2) {
//                save_mazeoff();
//            }
            if ((wchar_t)wparam=='<' && shade_map>=1)
            {
                char ip[200];
                char page[200];

                if (mul>0)
                {
                    if (MUL_SAS_MAX_ZOOM[mul-1]>=level)
                    {
                        mul--;
                    }
                    else
                    {
                        int cnt=mul-1;
                        while (MUL_SAS_MAX_ZOOM[(cnt+MUL_COUNTER)%MUL_COUNTER]<level && ((cnt+MUL_COUNTER))%MUL_COUNTER!=mul && MUL_COUNTER>1)
                            cnt--;
                        if ( (cnt+MUL_COUNTER)%MUL_COUNTER==mul || MUL_COUNTER<=1)
                        {
                            playmusic=1;
                            break;
                        }
                        else
                        {
                            mul=(cnt+MUL_COUNTER)%MUL_COUNTER;
                        }
                    }
                }
                else
                {
                    if (MUL_SAS_MAX_ZOOM[MUL_COUNTER-1]>=level)
                    {
                        mul=MUL_COUNTER-1;
                    }
                    else
                    {
                        int cnt=MUL_COUNTER-1;
                        while (MUL_SAS_MAX_ZOOM[(cnt+MUL_COUNTER)%MUL_COUNTER]<level && (cnt>0 && MUL_COUNTER>1))
                            cnt--;
                        if ( (cnt+MUL_COUNTER)%MUL_COUNTER<=0 || MUL_COUNTER<=1)
                        {
                            playmusic=1;
                            break;
                        }
                        else
                        {
                            mul=(cnt+MUL_COUNTER)%MUL_COUNTER;
                        }
                    }
                }
                reload_init();
                SAS_ZOOM=get_map_zoom;
                SAS_STARTX=get_map_x;
                SAS_STARTY=get_map_y;
                if (read_mazeoff(1)==0)
                {
//                    save_mazeoff();
                }
                else
                {
                    SAS_ZOOM=get_map_zoom;
                    SAS_STARTX=get_map_x;
                    SAS_STARTY=get_map_y;
                }

                printf("New LEVELDIR=%s\n",LEVELDIR);
            }
            else if (shade_map>0)
            {
                reload_init();
                SAS_ZOOM=get_map_zoom;
                SAS_STARTX=get_map_x;
                SAS_STARTY=get_map_y;
                if (level>0)
                {
                    level--;
                }
            }

            int pixels_in_map;
            int tiles_in_map;
            if (shade_map>=1)
            {
                //position previous level before level-- from their SAS settings.
                int pacx;
                int pacy;
                int render_pacx;
                int render_pacy;
                double rel_x_was=rel_pos_in_map_x;
                double rel_y_was=rel_pos_in_map_y;

                if (follow_ghost==1)
                {
                    pacx=(-pos_ghostx[follow_ghost_num]+1920+1920/2+maxpixelsx)%maxpixelsx;
                    pacy=(-pos_ghosty[follow_ghost_num]+1080+1080/2+maxpixelsy)%maxpixelsy;
                }
                else
                {

                    pacx=(picturex*1920-posx+1920/2)%maxpixelsx;
                    pacy=(picturey*1080-posy+1080/2)%maxpixelsy;
                }
                render_pacx=(render_picturex*1920-render_posx+1920/2)%maxpixelsx;
                render_pacy=(render_picturey*1080-render_posy+1080/2)%maxpixelsy;

                pixels_in_map=256*(int)pow(2.0,(SAS_ZOOM));
                tiles_in_map=(int)pow(2.0,(SAS_ZOOM));

                if (!DO_ADAPT)
                {
                    rel_pos_in_map_x=(double)(SAS_STARTX*256 + SAS_STARTX_a + (pacx) )/(double)(pixels_in_map);
                    rel_pos_in_map_y=(double)(SAS_STARTY*256 + SAS_STARTY_a + (pacy) )/(double)(pixels_in_map);
                }

                render_rel_pos_in_map_x=(double)(SAS_STARTX*256 + SAS_STARTX_a + (render_pacx) )/(double)(pixels_in_map);
                render_rel_pos_in_map_y=(double)(SAS_STARTY*256 + SAS_STARTY_a + (render_pacy) )/(double)(pixels_in_map);
//                printf("before: render_rel_pos_in_map_x=%29.28lf render_rel_pos_in_map_y=%29.28lf\n",render_rel_pos_in_map_x,render_rel_pos_in_map_y);

                rel_x_was=rel_pos_in_map_x;
                rel_y_was=rel_pos_in_map_y;

                /*
                                printf("BEFORE:\n");
                                printf("PACMAN: x=%d , y=%d\n",pacx,pacy);
                                printf("TILES: %d , PIXELS: %d\n",tiles_in_map,pixels_in_map);
                                printf("SAS: x=%d , y=%d , zoom=%d\n",SAS_STARTX,SAS_STARTY,SAS_ZOOM);
                                printf("RELATIVE: x=%f , y=%f\n",rel_pos_in_map_x,rel_pos_in_map_y);
                                printf("===========================\n");
                */
                // new zoom level. level-- means zoom level++ and vise versa
                int zoom_change=0;
                if ((wchar_t)wparam=='<')
                {
                }
                else
                {
                    get_map_zoom--;
                    Fget_map_x=Fget_map_x/2.0;
                    Fget_map_y=Fget_map_y/2.0;
                    if (plot_all==1)
                    {
                        sprite_from_canvas.setScale(sprite_from_canvas.getScale().x*2.0,sprite_from_canvas.getScale().y*2.0);
                        scale_slow*=2.0;
                    }
                    get_map_x=(int)Fget_map_x;
                    get_map_y=(int)Fget_map_y;
                    SAS_STARTX=get_map_x;
                    SAS_STARTY=get_map_y;
                    SAS_ZOOM=get_map_zoom;
                    zoom_change=1;
                }
                /*
                                printf("NEW:\n");
                                printf("PACMAN: x=%d , y=%d\n",pacx,pacy);
                                printf("TILES: %d , PIXELS: %d\n",tiles_in_map,pixels_in_map);
                                printf("SAS: x=%d , y=%d , zoom=%d\n",SAS_STARTX,SAS_STARTY,SAS_ZOOM);
                                printf("RELATIVE: x=%f , y=%f\n",rel_pos_in_map_x,rel_pos_in_map_y);
                                printf("===========================\n");
                */

                // read SAS settings new level from file.
                int ret=read_mazeoff(1);
                if (ret==1 && shade_map==2)
                {
                    pixels_in_map=256*(int)pow(2.0,(SAS_ZOOM));
                    double rel_pos_in_map_x_test=(double)(SAS_STARTX*256 + SAS_STARTX_a + (pacx) )/(double)(pixels_in_map);
                    double rel_pos_in_map_y_test=(double)(SAS_STARTY*256 + SAS_STARTY_a + (pacy) )/(double)(pixels_in_map);
                    if (DO_ADAPT==1 && (pixels_in_map>maxpixelsx || pixels_in_map>maxpixelsy) && (zoom_change || SAS_STARTX!=get_map_x || SAS_STARTY!=get_map_y || SAS_ZOOM!=get_map_zoom))
                    {
//                    if (rel_pos_in_map_x_test<0.2 || rel_pos_in_map_y_test<0.2 || rel_pos_in_map_x_test>0.8 || rel_pos_in_map_y_test>0.8) {
                        ret=0;
                        cleanupbitmaps();
                        cleanupbitmaps_mazes();
                        strcpy(error_msg2,"LEVEL CLEARED, NEW POSITION");
                        error_flag2=1;
                        strcpy(error_msg3,"LEVEL CLEARED, NEW POSITION");
                        error_flag3=1;
                        strcpy(error_msg4,"LEVEL CLEARED, NEW POSITION");
                        error_flag4=1;
                        strcpy(error_msg,"LEVEL CLEARED, NEW POSITION");
                        error_flag=1;
                    }
                }
                if (ret==0)
                {
                    // no file, calculate them.
                    pixels_in_map=256*(int)pow(2.0,(SAS_ZOOM));
                    tiles_in_map=(int)pow(2.0,(SAS_ZOOM));
                    if (pixels_in_map<=maxpixelsx)
                    {
                        SAS_STARTX=0;
                    }
                    else
                    {
                        SAS_STARTX=(-maxpixelsx/2+(int)(rel_pos_in_map_x*(double)pixels_in_map)-1920/2)/256;
                        if (SAS_STARTX<0)
                            SAS_STARTX=0;
                    }
                    if (pixels_in_map<=maxpixelsy)
                    {
                        SAS_STARTY=0;
                    }
                    else
                    {
                        SAS_STARTY=(-maxpixelsy/2+(int)(rel_pos_in_map_y*(double)pixels_in_map)-1080/2)/256;
                        if (SAS_STARTY<0)
                            SAS_STARTY=0;
                    }


                    SAS_STARTX_a=SAS_STARTX*256-(int)((float)(SAS_STARTX*256)/1920.0)*1920;
                    SAS_STARTY_a=SAS_STARTY*256-(int)((float)(SAS_STARTY*256)/1080.0)*1080;

//                    printf("CALCULATED NEW:\n");
//                    printf("RELATIVE: x=%f , y=%f\n",rel_pos_in_map_x,rel_pos_in_map_y);
//                    printf("TILES: %d , PIXELS: %d\n",tiles_in_map,pixels_in_map);
//                    printf("SAS:   x=%8d , y=%8d , zoom=%d\n",SAS_STARTX,SAS_STARTY,SAS_ZOOM);
//                    printf("ADAPT: x=%8d , y=%8d \n" ,(int)(SAS_STARTX_a/256),(int)(SAS_STARTY_a/256));
//                    printf("REST:  x=%8d , y=%8d \n" ,SAS_STARTX_a,SAS_STARTY_a);
//                    printf("X: tot=%d  /1920=%f\n",SAS_STARTX*256-SAS_STARTX_a,(float)(SAS_STARTX*256-SAS_STARTX_a)/1920.0);
//                    printf("Y: tot=%d  /1080=%f\n",SAS_STARTY*256-SAS_STARTY_a,(float)(SAS_STARTY*256-SAS_STARTY_a)/1080.0);
//                    printf("===========================\n");

                    /*
                                        SAS_STARTX=SAS_STARTX-SAS_STARTX_a/256;
                                        SAS_STARTY=SAS_STARTY-SAS_STARTY_a/256;
                                        SAS_STARTX_a=SAS_STARTX_a-(int)(SAS_STARTX_a/256)*256;
                                        SAS_STARTY_a=SAS_STARTY_a-(int)(SAS_STARTY_a/256)*256;

                                        printf("RECALCULATED NEW:\n");
                                        printf("SAS:   x=%8d , y=%8d , zoom=%d\n",SAS_STARTX,SAS_STARTY,SAS_ZOOM);
                                        printf("ADAPT: x=%8d , y=%8d \n" ,(int)(SAS_STARTX_a/256),(int)(SAS_STARTY_a/256));
                                        printf("REST:  x=%8d , y=%8d \n" ,SAS_STARTX_a,SAS_STARTY_a);
                                        printf("X: tot=%d  /1920=%f\n",SAS_STARTX*256-SAS_STARTX_a,(float)(SAS_STARTX*256-SAS_STARTX_a)/1920.0);
                                        printf("Y: tot=%d  /1080=%f\n",SAS_STARTY*256-SAS_STARTY_a,(float)(SAS_STARTY*256-SAS_STARTY_a)/1080.0);
                                        printf("===========================\n");
                    */

                    offset_picture_x=(int)((float)(SAS_STARTX*256+255)/1920.0);
                    offset_picture_y=(int)((float)(SAS_STARTY*256+255)/1080.0);

                    SAS_STARTX= (offset_picture_x*1920)/256;
                    SAS_STARTY= (offset_picture_y*1080)/256;

                    SAS_STARTX_a=offset_picture_x*1920-SAS_STARTX*256;
                    SAS_STARTY_a=offset_picture_y*1080-SAS_STARTY*256;

//                    printf("RE-RECALCULATED NEW:\n");
//                    printf("SAS:   x=%8d , y=%8d , zoom=%d\n",SAS_STARTX,SAS_STARTY,SAS_ZOOM);
//                    printf("ADAPT: x=%8d , y=%8d \n" ,(int)(SAS_STARTX_a/256),(int)(SAS_STARTY_a/256));
//                    printf("REST:  x=%8d , y=%8d \n" ,SAS_STARTX_a,SAS_STARTY_a);
//                    printf("X: tot=%d  /1920=%f\n",SAS_STARTX*256-SAS_STARTX_a,(float)(SAS_STARTX*256-SAS_STARTX_a)/1920.0);
//                    printf("Y: tot=%d  /1080=%f\n",SAS_STARTY*256-SAS_STARTY_a,(float)(SAS_STARTY*256-SAS_STARTY_a)/1080.0);
//                    printf("X: tot=%d  /1920=%f offset=%d\n",SAS_STARTX*256+SAS_STARTX_a,(float)(SAS_STARTX*256+SAS_STARTX_a)/1920.0,offset_picture_x);
//                    printf("Y: tot=%d  /1080=%f offset=%d\n",SAS_STARTY*256+SAS_STARTY_a,(float)(SAS_STARTY*256+SAS_STARTY_a)/1080.0,offset_picture_y);
//                    printf("===========================\n");


                    Fget_map_x=(double)SAS_STARTX+(double)SAS_STARTX_a/256.0;
                    Fget_map_y=(double)SAS_STARTY+(double)SAS_STARTY_a/256.0;
                    get_map_x=SAS_STARTX;
                    get_map_y=SAS_STARTY;
                    get_map_zoom=SAS_ZOOM;
                    // and save them under current new level.
                    if (SAS_STARTX!=0 || SAS_STARTY!=0)
                    {
                        strcpy(error_msg4,"MAP DON'T FIT IN SCREEN, ADAPTING STARTX,STARTY!!!!!!! SAVING REL.OFFSET TO MAZEOFF.DAT");
                        error_flag4=1;
                        strcpy(error_msg3,"DELETE OR CHANGE FILE FOR OTHER SUB SCREENS OF OTHER PARTS OF MAP...!!!!!");
                        error_flag3=1;
                    }
                    save_mazeoff();
                }
                else
                {
                    if (SAS_STARTX!=0 || SAS_STARTY!=0)
                    {
                        strcpy(error_msg4,"MAP DON'T FIT IN SCREEN, ADAPTED STARTX,STARTY!!!!!!! POSITIONS IN MAZEOFF.DAT");
                        error_flag4=1;
                        strcpy(error_msg3,"DELETE OR CHANGE FILE FOR OTHER SUB SCREENS OF OTHER PARTS OF MAP...!!!!!");
                        error_flag3=1;
                    }
                    else
                    {
                        strcpy(error_msg3,"MAP FITS IN SCREEN. NEW POSITION SAVED TO MAZEOFF.DAT. DELETE OR CHANGE FOR OTHER VALUES!!!!");
                        error_flag3=1;
                    }

                    SAS_STARTX_a=SAS_STARTX*256-(int)((float)(SAS_STARTX*256)/1920.0)*1920;
                    SAS_STARTY_a=SAS_STARTY*256-(int)((float)(SAS_STARTY*256)/1080.0)*1080;

                    printf("LOADED:\n");
                    printf("SAS:   x=%8d , y=%8d , zoom=%d\n",SAS_STARTX,SAS_STARTY,SAS_ZOOM);
                    printf("ADAPT: x=%8d , y=%8d \n",(int)(SAS_STARTX_a/256),(int)(SAS_STARTY_a/256));
                    printf("REST:  x=%8d , y=%8d \n",SAS_STARTX_a,SAS_STARTY_a);
                    printf("X: tot=%d  /1920=%f\n",SAS_STARTX*256-SAS_STARTX_a,(float)(SAS_STARTX*256-SAS_STARTX_a)/1920.0);
                    printf("Y: tot=%d  /1080=%f\n",SAS_STARTY*256-SAS_STARTY_a,(float)(SAS_STARTY*256-SAS_STARTY_a)/1080.0);
                    printf("===========================\n");

                    /*
                                        SAS_STARTX=SAS_STARTX-SAS_STARTX_a/256;
                                        SAS_STARTY=SAS_STARTY-SAS_STARTY_a/256;
                                        SAS_STARTX_a=SAS_STARTX_a-(int)(SAS_STARTX_a/256)*256;
                                        SAS_STARTY_a=SAS_STARTY_a-(int)(SAS_STARTY_a/256)*256;

                                        printf("RECALCULATED NEW:\n");
                                        printf("SAS:   x=%8d , y=%8d , zoom=%d\n",SAS_STARTX,SAS_STARTY,SAS_ZOOM);
                                        printf("ADAPT: x=%8d , y=%8d \n" ,(int)(SAS_STARTX_a/256),(int)(SAS_STARTY_a/256));
                                        printf("REST:  x=%8d , y=%8d \n" ,SAS_STARTX_a,SAS_STARTY_a);
                                        printf("X: tot=%d  /1920=%f\n",SAS_STARTX*256-SAS_STARTX_a,(float)(SAS_STARTX*256-SAS_STARTX_a)/1920.0);
                                        printf("Y: tot=%d  /1080=%f\n",SAS_STARTY*256-SAS_STARTY_a,(float)(SAS_STARTY*256-SAS_STARTY_a)/1080.0);
                                        printf("===========================\n");
                    */

                    offset_picture_x=(int)((float)(SAS_STARTX*256+255)/1920.0);
                    offset_picture_y=(int)((float)(SAS_STARTY*256+255)/1080.0);

                    SAS_STARTX= (offset_picture_x*1920)/256;
                    SAS_STARTY= (offset_picture_y*1080)/256;

                    SAS_STARTX_a=offset_picture_x*1920-SAS_STARTX*256;
                    SAS_STARTY_a=offset_picture_y*1080-SAS_STARTY*256;

//                    printf("RE-RECALCULATED NEW:\n");
//                    printf("SAS:   x=%8d , y=%8d , zoom=%d\n",SAS_STARTX,SAS_STARTY,SAS_ZOOM);
//                    printf("ADAPT: x=%8d , y=%8d \n" ,(int)(SAS_STARTX_a/256),(int)(SAS_STARTY_a/256));
//                    printf("REST:  x=%8d , y=%8d \n" ,SAS_STARTX_a,SAS_STARTY_a);
//                    printf("X: tot=%d  /1920=%f\n",SAS_STARTX*256-SAS_STARTX_a,(float)(SAS_STARTX*256-SAS_STARTX_a)/1920.0);
//                    printf("Y: tot=%d  /1080=%f\n",SAS_STARTY*256-SAS_STARTY_a,(float)(SAS_STARTY*256-SAS_STARTY_a)/1080.0);
//                    printf("X: tot=%d  /1920=%f offset=%d\n",SAS_STARTX*256+SAS_STARTX_a,(float)(SAS_STARTX*256+SAS_STARTX_a)/1920.0,offset_picture_x);
//                    printf("Y: tot=%d  /1080=%f offset=%d\n",SAS_STARTY*256+SAS_STARTY_a,(float)(SAS_STARTY*256+SAS_STARTY_a)/1080.0,offset_picture_y);
//                    printf("===========================\n");


                    Fget_map_x=(double)SAS_STARTX+(double)SAS_STARTX_a/256.0;
                    Fget_map_y=(double)SAS_STARTY+(double)SAS_STARTY_a/256.0;
                    get_map_x=SAS_STARTX;
                    get_map_y=SAS_STARTY;
                    get_map_zoom=SAS_ZOOM;
//                    save_mazeoff();
                }
//                offset_picture_x=(SAS_STARTX*256-SAS_STARTX_a)/1920;
//                offset_picture_y=(SAS_STARTY*256-SAS_STARTY_a)/1080;



                // calc new position based on calculated or loaded SAS settings.
                int x,y;
                int render_x,render_y;
                pixels_in_map=256*(int)pow(2.0,(SAS_ZOOM));
                tiles_in_map=(int)pow(2.0,(SAS_ZOOM));
//                pixels_in_map=256*(int)pow(2.0,(17-SAS_ZOOM));
//                tiles_in_map=(int)pow(2.0,(17-SAS_ZOOM));
                /*
                                printf("CALCULATED NEW POSITION PACMAN:\n");
                                printf("PACMAN: x=%d , y=%d\n",x,y);
                                printf("TILES: %d , PIXELS: %d\n",tiles_in_map,pixels_in_map);
                                printf("SAS: x=%d , y=%d , zoom=%d\n",SAS_STARTX,SAS_STARTY,SAS_ZOOM);
                                printf("RELATIVE: x=%f , y=%f\n",rel_pos_in_map_x,rel_pos_in_map_y);
                                printf("===========================\n");
                */
//                x=(int) (abs_pos_in_map_x)-SAS_STARTX*256;
//                y=(int) (abs_pos_in_map_y)-SAS_STARTY*256;
                x=(int) (rel_pos_in_map_x*(double)(pixels_in_map))-SAS_STARTX*256-SAS_STARTX_a;
                y=(int) (rel_pos_in_map_y*(double)(pixels_in_map))-SAS_STARTY*256-SAS_STARTY_a ;

                render_x=(int) (render_rel_pos_in_map_x*(double)(pixels_in_map))-SAS_STARTX*256-SAS_STARTX_a;
                render_y=(int) (render_rel_pos_in_map_y*(double)(pixels_in_map))-SAS_STARTY*256-SAS_STARTY_a;

                if (x<0 || x>=maxpixelsx || y<0 || y>=maxpixelsy)
                {
                    sprintf(error_msg5,"POSITION OUT OF MAP!!!! SET TO EDGE. X=%d,Y=%d",x,y);
                    printf("%s\n",error_msg);
                    error_flag5=1;
                    if (x<0)
                        rel_pos_in_map_x=0.0;
                    if (x>=maxpixelsx)
                        rel_pos_in_map_x=1.0;
                    if (y<0)
                        rel_pos_in_map_y=0.0;
                    if (y>=maxpixelsy)
                        rel_pos_in_map_y=1.0;
                    x=(int) (rel_pos_in_map_x*(double)(maxpixelsx));
                    y=(int) (rel_pos_in_map_y*(double)(maxpixelsy));
                }
                if (render_x<0 || render_x>=maxpixelsx || render_y<0 || render_y>=maxpixelsy)
                {
                    sprintf(error_msg5,"POSITION OUT OF MAP!!!! SET TO EDGE. X=%d,Y=%d",x,y);
                    printf("%s\n",error_msg);
                    error_flag5=1;
                    if (render_x<0)
                        render_rel_pos_in_map_x=0.0;
                    if (render_x>=maxpixelsx)
                        render_rel_pos_in_map_x=1.0;
                    if (render_y<0)
                        render_rel_pos_in_map_y=0.0;
                    if (render_y>=maxpixelsy)
                        render_rel_pos_in_map_y=1.0;
                    x=(int) (rel_pos_in_map_x*(double)(maxpixelsx));
                    y=(int) (rel_pos_in_map_y*(double)(maxpixelsy));
                }

                if (!DO_ADAPT)
                {
                    x=x-1920/2;
                    y=y-1080/2;

                    render_x=render_x-1920/2;
                    render_y=render_y-1080/2;

                    x=(maxpixelsx+x)%maxpixelsx;
                    if (x<0)
                        x=0;
                    y=(maxpixelsy+y)%maxpixelsy;
                    if (y<0)
                        y=0;

                    render_x=(maxpixelsx+render_x)%maxpixelsx;
                    if (render_x<0)
                        render_x=0;
                    render_y=(maxpixelsy+render_y)%maxpixelsy;
                    if (render_y<0)
                        render_y=0;

                    if (ret==0 && follow_ghost==0)
                    {
                        position1x=x;
                        position1y=y;
                        position2x=x;
                        position2y=y;
                        save_mazeoff();
                    }
                    smooth_x=(double)render_x;
                    smooth_y=(double)render_y;

                    picturex=x/1920;
                    posx=x-1920*picturex;
                    picturey=y/1080;
                    posy=y-1080*picturey;
                    posx=-posx;
                    posy=-posy;
                    fposx=posx;
                    fposy=posy;

                    render_picturex=render_x/1920;
                    render_posx=render_x-1920*render_picturex;
                    render_picturey=render_y/1080;
                    render_posy=render_y-1080*render_picturey;
                    render_posx=-render_posx;
                    render_posy=-render_posy;

                    render_pacx=(render_picturex*1920-render_posx+1920/2)%maxpixelsx;
                    render_pacy=(render_picturey*1080-render_posy+1080/2)%maxpixelsy;
                    render_rel_pos_in_map_x=(double)(SAS_STARTX*256 + SAS_STARTX_a + (render_pacx) )/(double)(pixels_in_map);
                    render_rel_pos_in_map_y=(double)(SAS_STARTY*256 + SAS_STARTY_a + (render_pacy) )/(double)(pixels_in_map);
                }
//                printf("after:  render_rel_pos_in_map_x=%29.28lf render_rel_pos_in_map_y=%29.28lf\n",render_rel_pos_in_map_x,render_rel_pos_in_map_y);

                if (follow_ghost==1)
                {
                    posx=posx-posx%64-32;
                    if (posx<=-1920)
                    {
                        posx=posx+1920;
//                        picturex=(picturex-1+totalpicturex)%totalpicturex;
                    }
                    posy=posy-(posy-36)%72-36;
                    if (posy<=-1080)
                    {
                        posy=posy+1080;
//                        picturey=(picturey-1+totalpicturey)%totalpicturey;
                    }
                    fposx=posx;
                    fposy=posy;
                    ReadBitmaps2();
//                    render_posx=posx;
//                    render_posy=posy;
//                    render_picturex=picturex;
//                    render_picturey=picturey;
//                    ReadBitmaps4();

                    int xx=(picturex*1920-posx)%maxpixelsx;
                    int yy=(picturey*1080-posy)%maxpixelsy;


                    fpos_ghostx[follow_ghost_num]=-xx+1920;
                    fpos_ghosty[follow_ghost_num]=-yy+1080;
                    pos_ghostx[follow_ghost_num]=fpos_ghostx[follow_ghost_num];
                    pos_ghosty[follow_ghost_num]=fpos_ghosty[follow_ghost_num];
                    smooth_x=(double)xx;
                    smooth_y=(double)yy;
                }

                if (rel_x_was==rel_pos_in_map_x && rel_y_was==rel_pos_in_map_y && (wchar_t)wparam=='<')
                {
                    if (!DO_ADAPT)
                        forced_jump=1;
                    else
                        soft_jump=1;
                }
                else
                {
                    if (!DO_ADAPT)
                        forced_jump=1;
                    else
                        soft_jump=1;
                }
            }
            else
            {
                if (level>0) level--;
                reload_init();
            }

            err_level=1;
            if (connected==1)
            {
                sprintf(writer,"T=MOVELEVEL,LEVEL=%d,\0",level);
                SEND(writer);
            }
            if (MAZEOFF==0)
            {
                totalfiles=0;
                totalfiles_mazes=0;
                if (F2==1)
                {
                    draw2((char*)"SCANNING FILES",800,0,sf::Color::Red,sf::Color::White);
                    SFMLView1.display();
                }
                for (x=0; x<=maxpicturex; x++)
                {
                    for (y=0; y<=maxpicturey; y++)
                    {
                        sprintf(naam,"%s/%dx%d/%03d/picture.%06d.%06d.png",LEVELDIR,BITMAPSX,BITMAPSY,level,y,x);
                        int exist;
                        exist = stat(naam,&buffer);
                        if ( exist!=0)
                        {
                            files[x][y]=0;
                        }
                        else
                        {
                            files[x][y]=1;
                            totalfiles++;
                        }
                        sprintf(naam,"%s/%dx%d/%03d/picture_maze.%06d.%06d.png",LEVELDIR,BITMAPSX,BITMAPSY,level,y,x);
                        exist = stat(naam,&buffer);
                        if ( exist!=0)
                        {
                            files_mazes[x][y]=0;
                        }
                        else
                        {
                            files_mazes[x][y]=1;
                            totalfiles_mazes++;
                        }
                    }
                }
            }
            else
            {
                CLEANBITMAPS();
                follow_ghost_pos();
                ReadBitmaps2();
                ReadBitmaps4();
            }
            forced_jump=1;
            break;
        }
        else
        {
            if (number==0)
            {
                follow_ghost=0;
                set_pacman();

                posx=posx-posx%64-32;
                if (posx<=-1920)
                {
                    posx=posx+1920;
//                    picturex=(picturex-1+totalpicturex)%totalpicturex;
                }
                posy=posy-(posy-36)%72-36;
                if (posy<=-1080)
                {
                    posy=posy+1080;
//                    picturey=(picturey-1+totalpicturey)%totalpicturey;
                }
                fposx=posx;
                fposy=posy;
                ReadBitmaps2();
//pospos
                /*
                                posx=posx-posx%64-32;
                                if (posx<=-1920)
                                    posx=posx+1920;
                                posy=posy-(posy-36)%72-36;
                                if (posy<=-1080)
                                    posy=posy+1080;
                                fposx=posx;
                                fposy=posy;
                */

                follow_ghost=0;
//                long_jump=1;
                pen=old_pen;
                if (pen==1)
                    pen_mode=2;
                else
                    pen_mode=0;
            }
            if (follow_ghost_num>0)
            {
                follow_ghost_num--;
            }
            else
            {
                follow_ghost_num=number-1;
            }
//            follow_ghost_pos();
//                follow_ghost_start=1;
//            long_jump=1;
            break;
        }
        break;
    case ')':
    case ']':
    case '>':
        int ret;
        if ((follow_ghost==0 && flippo==0) || (wchar_t)wparam==')' ||(wchar_t)wparam=='>')
        {
            overwrite1=0;
            overwrite2=0;
            if (drawmazes==0 || 1)
            {
                if (totalchanged>0)
                {
//                    DONTSAVEFILES=0;
                    if (DONTSAVEFILES==0)
                        SAVEALLBITMAPS();
                    else
                        CLEANBITMAPS();
                    strcpy(error_msg,"BITMAPS CHANGED!!! SAVING FIRST BEFORE DRAW MAZE / CHANGE LEVEL");
                    error_flag=1;
                }
                else
                {
                    CLEANBITMAPS();
//                    strcpy(error_msg,"DRAW MAZE=ON");
//                    error_flag=1;
                }
//                drawmazes=1;
//                strcpy(error_msg,"DRAWMAZE=ON");
//                error_flag=1;
//                if (drawmazes==1) DRAWALLMAZES();
//                pen=1;
//                pen_mode=2;
            }
            // save current SAS settings and stored positions (f9/f11). (when changed zoom level with alt-z/ctrl-z. Be carefull when changing them. Messes up mazeoff.dat otherwise.
//            if (shade_map==2) {
//                save_mazeoff();
//            }

            if ((wchar_t)wparam=='>' && shade_map>=1)
            {
                if (reset_map==1)
                {
                }
                else if (mul<(MUL_COUNTER-1))
                {
                    if (MUL_SAS_MAX_ZOOM[mul+1]>=level)
                    {
                        mul++;
                    }
                    else
                    {
                        int cnt=mul+1;
                        while (MUL_SAS_MAX_ZOOM[(cnt+MUL_COUNTER)%MUL_COUNTER]<level && ((cnt%MUL_COUNTER)!=mul && MUL_COUNTER>1))
                            cnt++;
                        if ( ((cnt%MUL_COUNTER)==mul || MUL_COUNTER<=1) )
                        {
                            playmusic=1;
                            break;
                        }
                        else
                        {
                            mul=(cnt+MUL_COUNTER)%MUL_COUNTER;
                        }
                    }
                }
                else
                {
                    if (MUL_SAS_MAX_ZOOM[0]>=level)
                    {
                        mul=0;
                    }
                    else
                    {
                        int cnt=1;
                        while (MUL_SAS_MAX_ZOOM[(cnt+MUL_COUNTER)%MUL_COUNTER]<level && ((cnt%MUL_COUNTER)!=0 && MUL_COUNTER>1))
                            cnt++;
                        if ( ((cnt%MUL_COUNTER)==0 || MUL_COUNTER<=1) )
                        {
                            playmusic=1;
                            break;
                        }
                        else
                        {
                            mul=(cnt+MUL_COUNTER)%MUL_COUNTER;
                        }
                    }
                }
                reload_init();
                SAS_ZOOM=get_map_zoom;
                SAS_STARTX=get_map_x;
                SAS_STARTY=get_map_y;
                if (read_mazeoff(1)==0)
                {
//                    save_mazeoff();
                }
                else
                {
                    SAS_ZOOM=get_map_zoom;
                    SAS_STARTX=get_map_x;
                    SAS_STARTY=get_map_y;
                }

                printf("New LEVELDIR=%s\n",LEVELDIR);
            }
            else if (shade_map>0)
            {
                reload_init();
                SAS_ZOOM=get_map_zoom;
                SAS_STARTX=get_map_x;
                SAS_STARTY=get_map_y;
                if (level<SAS_MAX_ZOOM)
                {
                    level++;
                    if (level==SAS_MAX_ZOOM)
                    {
                        sprintf(error_msg5,"LAST MAP!!!!!!!!!!!!!!!!");
                        error_flag5=1;
                    }
                }
                else
                {
                    playmusic=1;
                    break;
                }
            }
            int pixels_in_map;
            int tiles_in_map;
            if (shade_map>=1)
            {
                //position previous level before level++ from their SAS settings. Or from reload() ('>').

                double rel_x_was=rel_pos_in_map_x;
                double rel_y_was=rel_pos_in_map_y;

                int pacx;
                int pacy;
                int render_pacx;
                int render_pacy;

                if (reset_map==0)
                {
                    if (follow_ghost==1)
                    {
                        pacx=(-pos_ghostx[follow_ghost_num]+1920+1920/2+maxpixelsx)%maxpixelsx;
                        pacy=(-pos_ghosty[follow_ghost_num]+1080+1080/2+maxpixelsy)%maxpixelsy;
                    }
                    else
                    {
                        pacx=(picturex*1920-posx+1920/2)%maxpixelsx;
                        pacy=(picturey*1080-posy+1080/2)%maxpixelsy;
                    }
                    render_pacx=(render_picturex*1920-render_posx+1920/2)%maxpixelsx;
                    render_pacy=(render_picturey*1080-render_posy+1080/2)%maxpixelsy;

                    pixels_in_map=256*(int)pow(2.0,(SAS_ZOOM));
                    tiles_in_map=(int)pow(2.0,(SAS_ZOOM));

                    if (!DO_ADAPT)
                    {
                        rel_pos_in_map_x=(double)(SAS_STARTX*256 + SAS_STARTX_a + (pacx) )/(double)(pixels_in_map);
                        rel_pos_in_map_y=(double)(SAS_STARTY*256 + SAS_STARTY_a + (pacy) )/(double)(pixels_in_map);
                    }

                    render_rel_pos_in_map_x=(double)(SAS_STARTX*256 + SAS_STARTX_a + (render_pacx) )/(double)(pixels_in_map);
                    render_rel_pos_in_map_y=(double)(SAS_STARTY*256 + SAS_STARTY_a + (render_pacy) )/(double)(pixels_in_map);
                    //                printf("before: render_rel_pos_in_map_x=%29.28lf render_rel_pos_in_map_y=%29.28lf\n",render_rel_pos_in_map_x,render_rel_pos_in_map_y);

                    rel_x_was=rel_pos_in_map_x;
                    rel_y_was=rel_pos_in_map_y;
                    /*

                                    printf("BEFORE:\n");
                                    printf("PACMAN: x=%d , y=%d\n",pacx,pacy);
                                    printf("TILES: %d , PIXELS: %d\n",tiles_in_map,pixels_in_map);
                                    printf("SAS: x=%d , y=%d , zoom=%d\n",SAS_STARTX,SAS_STARTY,SAS_ZOOM);
                                    printf("RELATIVE: x=%f , y=%f\n",rel_pos_in_map_x,rel_pos_in_map_y);
                                    printf("===========================\n");
                    */
                }
                // new zoom level. level-- means zoom level++ and vise versa
                int zoom_change=0;
                if ((wchar_t)wparam=='>')
                {
                }
                else
                {
                    get_map_zoom++;
                    Fget_map_x=Fget_map_x*2.0;
                    Fget_map_y=Fget_map_y*2.0;
                    if (plot_all==1)
                    {
                        sprite_from_canvas.setScale(sprite_from_canvas.getScale().x/2.0,sprite_from_canvas.getScale().y/2.0);
                        scale_slow/=2.0;
                    }
                    get_map_x=(int)Fget_map_x;
                    get_map_y=(int)Fget_map_y;
                    SAS_STARTX=get_map_x;
                    SAS_STARTY=get_map_y;
                    SAS_ZOOM=get_map_zoom;
                    zoom_change=1;
                }
                /*
                                printf("NEW:\n");
                                printf("PACMAN: x=%d , y=%d\n",pacx,pacy);
                                printf("TILES: %d , PIXELS: %d\n",tiles_in_map,pixels_in_map);
                                printf("SAS: x=%d , y=%d , zoom=%d\n",SAS_STARTX,SAS_STARTY,SAS_ZOOM);
                                printf("RELATIVE: x=%f , y=%f\n",rel_pos_in_map_x,rel_pos_in_map_y);
                                printf("===========================\n");
                */

                // read SAS settings new level from file.
                ret=read_mazeoff(1);
                if (ret==1 && shade_map==2)
                {
                    pixels_in_map=256*(int)pow(2.0,(SAS_ZOOM));
                    double rel_pos_in_map_x_test=(double)(SAS_STARTX*256 + SAS_STARTX_a + (pacx) )/(double)(pixels_in_map);
                    double rel_pos_in_map_y_test=(double)(SAS_STARTY*256 + SAS_STARTY_a + (pacy) )/(double)(pixels_in_map);
                    if (DO_ADAPT==1 && (pixels_in_map>maxpixelsx || pixels_in_map>maxpixelsy) && (reset_map==1 || zoom_change || SAS_STARTX!=get_map_x || SAS_STARTY!=get_map_y || SAS_ZOOM!=get_map_zoom))
                    {
//                    if (rel_pos_in_map_x_test<0.2 || rel_pos_in_map_y_test<0.2 || rel_pos_in_map_x_test>0.8 || rel_pos_in_map_y_test>0.8) {
                        ret=0;
                        cleanupbitmaps();
                        cleanupbitmaps_mazes();
                        strcpy(error_msg2,"LEVEL CLEARED, NEW POSITION");
                        error_flag2=1;
                        error_flag2=1;
                        strcpy(error_msg3,"LEVEL CLEARED, NEW POSITION");
                        error_flag3=1;
                        strcpy(error_msg4,"LEVEL CLEARED, NEW POSITION");
                        error_flag4=1;
                        strcpy(error_msg,"LEVEL CLEARED, NEW POSITION");
                        error_flag=1;
                    }
                }
                if (ret==0)
                {
                    // no file, calculate them.
                    pixels_in_map=256*(int)pow(2.0,(SAS_ZOOM));
                    tiles_in_map=(int)pow(2.0,(SAS_ZOOM));
                    if (pixels_in_map<=maxpixelsx)
                    {
                        SAS_STARTX=0;
                    }
                    else
                    {
                        SAS_STARTX=(-maxpixelsx/2+(int)(rel_pos_in_map_x*(double)pixels_in_map)-1920/2)/256;
                        if (SAS_STARTX<0)
                            SAS_STARTX=0;
                    }
                    if (pixels_in_map<=maxpixelsy)
                    {
                        SAS_STARTY=0;
                    }
                    else
                    {
                        SAS_STARTY=(-maxpixelsy/2+(int)(rel_pos_in_map_y*(double)pixels_in_map)-1080/2)/256;
                        if (SAS_STARTY<0)
                            SAS_STARTY=0;
                    }


                    SAS_STARTX_a=SAS_STARTX*256-(int)((float)(SAS_STARTX*256)/1920.0)*1920;
                    SAS_STARTY_a=SAS_STARTY*256-(int)((float)(SAS_STARTY*256)/1080.0)*1080;

//                    printf("CALCULATED NEW:\n");
//                    printf("RELATIVE: x=%f , y=%f\n",rel_pos_in_map_x,rel_pos_in_map_y);
//                    printf("TILES: %d , PIXELS: %d\n",tiles_in_map,pixels_in_map);
//                    printf("SAS:   x=%8d , y=%8d , zoom=%d\n",SAS_STARTX,SAS_STARTY,SAS_ZOOM);
//                    printf("ADAPT: x=%8d , y=%8d \n" ,(int)(SAS_STARTX_a/256),(int)(SAS_STARTY_a/256));
//                    printf("REST:  x=%8d , y=%8d \n" ,SAS_STARTX_a,SAS_STARTY_a);
//                    printf("X: tot=%d  /1920=%f\n",SAS_STARTX*256-SAS_STARTX_a,(float)(SAS_STARTX*256-SAS_STARTX_a)/1920.0);
//                    printf("Y: tot=%d  /1080=%f\n",SAS_STARTY*256-SAS_STARTY_a,(float)(SAS_STARTY*256-SAS_STARTY_a)/1080.0);
//                    printf("===========================\n");
                    /*
                                        SAS_STARTX=SAS_STARTX-SAS_STARTX_a/256;
                                        SAS_STARTY=SAS_STARTY-SAS_STARTY_a/256;
                                        SAS_STARTX_a=SAS_STARTX_a-(int)(SAS_STARTX_a/256)*256;
                                        SAS_STARTY_a=SAS_STARTY_a-(int)(SAS_STARTY_a/256)*256;

                                        printf("RECALCULATED NEW:\n");
                                        printf("SAS:   x=%8d , y=%8d , zoom=%d\n",SAS_STARTX,SAS_STARTY,SAS_ZOOM);
                                        printf("ADAPT: x=%8d , y=%8d \n" ,(int)(SAS_STARTX_a/256),(int)(SAS_STARTY_a/256));
                                        printf("REST:  x=%8d , y=%8d \n" ,SAS_STARTX_a,SAS_STARTY_a);
                                        printf("X: tot=%d  /1920=%f\n",SAS_STARTX*256-SAS_STARTX_a,(float)(SAS_STARTX*256-SAS_STARTX_a)/1920.0);
                                        printf("Y: tot=%d  /1080=%f\n",SAS_STARTY*256-SAS_STARTY_a,(float)(SAS_STARTY*256-SAS_STARTY_a)/1080.0);
                                        printf("===========================\n");

                    */
                    offset_picture_x=(int)((float)(SAS_STARTX*256+255)/1920.0);
                    offset_picture_y=(int)((float)(SAS_STARTY*256+255)/1080.0);

                    SAS_STARTX= (offset_picture_x*1920)/256;
                    SAS_STARTY= (offset_picture_y*1080)/256;

                    SAS_STARTX_a=offset_picture_x*1920-SAS_STARTX*256;
                    SAS_STARTY_a=offset_picture_y*1080-SAS_STARTY*256;

//                    printf("RE-RECALCULATED NEW:\n");
//                    printf("SAS:   x=%8d , y=%8d , zoom=%d\n",SAS_STARTX,SAS_STARTY,SAS_ZOOM);
//                    printf("ADAPT: x=%8d , y=%8d \n" ,(int)(SAS_STARTX_a/256),(int)(SAS_STARTY_a/256));
//                    printf("REST:  x=%8d , y=%8d \n" ,SAS_STARTX_a,SAS_STARTY_a);
//                    printf("X: tot=%d  /1920=%f\n",SAS_STARTX*256-SAS_STARTX_a,(float)(SAS_STARTX*256-SAS_STARTX_a)/1920.0);
//                    printf("Y: tot=%d  /1080=%f\n",SAS_STARTY*256-SAS_STARTY_a,(float)(SAS_STARTY*256-SAS_STARTY_a)/1080.0);
//                    printf("X: tot=%d  /1920=%f offset=%d\n",SAS_STARTX*256+SAS_STARTX_a,(float)(SAS_STARTX*256+SAS_STARTX_a)/1920.0,offset_picture_x);
//                    printf("Y: tot=%d  /1080=%f offset=%d\n",SAS_STARTY*256+SAS_STARTY_a,(float)(SAS_STARTY*256+SAS_STARTY_a)/1080.0,offset_picture_y);
//                    printf("===========================\n");

                    Fget_map_x=(double)SAS_STARTX+(double)SAS_STARTX_a/256.0;
                    Fget_map_y=(double)SAS_STARTY+(double)SAS_STARTY_a/256.0;
                    get_map_x=SAS_STARTX;
                    get_map_y=SAS_STARTY;
                    get_map_zoom=SAS_ZOOM;
                    // and save them under current new level.
                    if (SAS_STARTX!=0 || SAS_STARTY!=0)
                    {
                        strcpy(error_msg4,"MAP DON'T FIT IN SCREEN, ADAPTING STARTX,STARTY!!!!!!! SAVING REL.OFFSET TO MAZEOFF.DAT");
                        error_flag4=1;
                        strcpy(error_msg3,"DELETE OR CHANGE FILE FOR OTHER SUB SCREENS OF OTHER PARTS OF MAP...!!!!!");
                        error_flag3=1;
                    }
                    save_mazeoff();

                }
                else
                {
                    if (SAS_STARTX!=0 || SAS_STARTY!=0)
                    {
                        strcpy(error_msg4,"MAP DON'T FIT IN SCREEN, ADAPTED STARTX,STARTY!!!!!!! POSITIONS IN MAZEOFF.DAT");
                        error_flag4=1;
                        strcpy(error_msg3,"DELETE OR CHANGE FILE FOR OTHER SUB SCREENS OF OTHER PARTS OF MAP...!!!!!");
                        error_flag3=1;
                    }
                    else
                    {
                        strcpy(error_msg3,"MAP FITS IN SCREEN. NEW POSITION SAVED TO MAZEOFF.DAT. DELETE OR CHANGE FOR OTHER VALUES!!!!");
                        error_flag3=1;
                    }

                    SAS_STARTX_a=SAS_STARTX*256-(int)((float)(SAS_STARTX*256)/1920.0)*1920;
                    SAS_STARTY_a=SAS_STARTY*256-(int)((float)(SAS_STARTY*256)/1080.0)*1080;

//                    printf("LOADED:\n");
//                    printf("SAS:   x=%8d , y=%8d , zoom=%d\n",SAS_STARTX,SAS_STARTY,SAS_ZOOM);
//                    printf("ADAPT: x=%8d , y=%8d \n" ,(int)(SAS_STARTX_a/256),(int)(SAS_STARTY_a/256));
//                    printf("REST:  x=%8d , y=%8d \n" ,SAS_STARTX_a,SAS_STARTY_a);
//                    printf("X: tot=%d  /1920=%f\n",SAS_STARTX*256-SAS_STARTX_a,(float)(SAS_STARTX*256-SAS_STARTX_a)/1920.0);
//                    printf("Y: tot=%d  /1080=%f\n",SAS_STARTY*256-SAS_STARTY_a,(float)(SAS_STARTY*256-SAS_STARTY_a)/1080.0);
//                    printf("===========================\n");

                    /*
                                        SAS_STARTX=SAS_STARTX-SAS_STARTX_a/256;
                                        SAS_STARTY=SAS_STARTY-SAS_STARTY_a/256;
                                        SAS_STARTX_a=SAS_STARTX_a-(int)(SAS_STARTX_a/256)*256;
                                        SAS_STARTY_a=SAS_STARTY_a-(int)(SAS_STARTY_a/256)*256;

                                        printf("RECALCULATED NEW:\n");
                                        printf("SAS:   x=%8d , y=%8d , zoom=%d\n",SAS_STARTX,SAS_STARTY,SAS_ZOOM);
                                        printf("ADAPT: x=%8d , y=%8d \n" ,(int)(SAS_STARTX_a/256),(int)(SAS_STARTY_a/256));
                                        printf("REST:  x=%8d , y=%8d \n" ,SAS_STARTX_a,SAS_STARTY_a);
                                        printf("X: tot=%d  /1920=%f\n",SAS_STARTX*256-SAS_STARTX_a,(float)(SAS_STARTX*256-SAS_STARTX_a)/1920.0);
                                        printf("Y: tot=%d  /1080=%f\n",SAS_STARTY*256-SAS_STARTY_a,(float)(SAS_STARTY*256-SAS_STARTY_a)/1080.0);
                                        printf("===========================\n");

                    */
                    offset_picture_x=(int)((float)(SAS_STARTX*256+255)/1920.0);
                    offset_picture_y=(int)((float)(SAS_STARTY*256+255)/1080.0);

                    SAS_STARTX= (offset_picture_x*1920)/256;
                    SAS_STARTY= (offset_picture_y*1080)/256;

                    SAS_STARTX_a=offset_picture_x*1920-SAS_STARTX*256;
                    SAS_STARTY_a=offset_picture_y*1080-SAS_STARTY*256;

//                    printf("RE-RECALCULATED NEW:\n");
//                    printf("SAS:   x=%8d , y=%8d , zoom=%d\n",SAS_STARTX,SAS_STARTY,SAS_ZOOM);
//                    printf("ADAPT: x=%8d , y=%8d \n" ,(int)(SAS_STARTX_a/256),(int)(SAS_STARTY_a/256));
//                    printf("REST:  x=%8d , y=%8d \n" ,SAS_STARTX_a,SAS_STARTY_a);
//                    printf("X: tot=%d  /1920=%f\n",SAS_STARTX*256-SAS_STARTX_a,(float)(SAS_STARTX*256-SAS_STARTX_a)/1920.0);
//                    printf("Y: tot=%d  /1080=%f\n",SAS_STARTY*256-SAS_STARTY_a,(float)(SAS_STARTY*256-SAS_STARTY_a)/1080.0);
//                    printf("X: tot=%d  /1920=%f offset=%d\n",SAS_STARTX*256+SAS_STARTX_a,(float)(SAS_STARTX*256+SAS_STARTX_a)/1920.0,offset_picture_x);
//                    printf("Y: tot=%d  /1080=%f offset=%d\n",SAS_STARTY*256+SAS_STARTY_a,(float)(SAS_STARTY*256+SAS_STARTY_a)/1080.0,offset_picture_y);
//                    printf("===========================\n");

                    Fget_map_x=(double)SAS_STARTX+(double)SAS_STARTX_a/256.0;
                    Fget_map_y=(double)SAS_STARTY+(double)SAS_STARTY_a/256.0;
                    get_map_x=SAS_STARTX;
                    get_map_y=SAS_STARTY;
                    get_map_zoom=SAS_ZOOM;
//                    save_mazeoff();
                }

//                offset_picture_x=(SAS_STARTX*256-SAS_STARTX_a)/1920;
//                offset_picture_y=(SAS_STARTY*256-SAS_STARTY_a)/1080;

                // calc new position based on calculated or loaded SAS settings.
                int x,y;
                int render_x,render_y;
                pixels_in_map=256*(int)pow(2.0,(SAS_ZOOM));
                tiles_in_map=(int)pow(2.0,(SAS_ZOOM));
//              pixels_in_map=256*(int)pow(2.0,(17-SAS_ZOOM));
//                tiles_in_map=(int)pow(2.0,(17-SAS_ZOOM));
                /*
                                printf("CALCULATED NEW POSITION PACMAN:\n");
                                printf("PACMAN: x=%d , y=%d\n",x,y);
                                printf("TILES: %d , PIXELS: %d\n",tiles_in_map,pixels_in_map);
                                printf("SAS: x=%d , y=%d , zoom=%d\n",SAS_STARTX,SAS_STARTY,SAS_ZOOM);
                                printf("RELATIVE: x=%f , y=%f\n",rel_pos_in_map_x,rel_pos_in_map_y);
                                printf("===========================\n");
                */
//                x=(int) (abs_pos_in_map_x)-SAS_STARTX*256;
//                y=(int) (abs_pos_in_map_y)-SAS_STARTY*256 ;
                x=(int) (rel_pos_in_map_x*(double)(pixels_in_map))-SAS_STARTX*256-SAS_STARTX_a;
                y=(int) (rel_pos_in_map_y*(double)(pixels_in_map))-SAS_STARTY*256-SAS_STARTY_a;

                render_x=(int) (render_rel_pos_in_map_x*(double)(pixels_in_map))-SAS_STARTX*256-SAS_STARTX_a;
                render_y=(int) (render_rel_pos_in_map_y*(double)(pixels_in_map))-SAS_STARTY*256-SAS_STARTY_a;

                if (x<0 || x>=maxpixelsx || y<0 || y>=maxpixelsy)
                {
                    sprintf(error_msg5,"POSITION OUT OF MAP!!!! SET TO EDGE. X=%d,Y=%d",x,y);
                    printf("%s\n",error_msg);
                    error_flag5=1;
                    if (x<0)
                        rel_pos_in_map_x=0.0;
                    if (x>=maxpixelsx)
                        rel_pos_in_map_x=1.0;
                    if (y<0)
                        rel_pos_in_map_y=0.0;
                    if (y>=maxpixelsy)
                        rel_pos_in_map_y=1.0;
                    x=(int) (rel_pos_in_map_x*(double)(maxpixelsx));
                    y=(int) (rel_pos_in_map_y*(double)(maxpixelsy));
                }
                if (render_x<0 || render_x>=maxpixelsx || render_y<0 || render_y>=maxpixelsy)
                {
                    sprintf(error_msg5,"POSITION OUT OF MAP!!!! SET TO EDGE. X=%d,Y=%d",x,y);
                    printf("%s\n",error_msg);
                    error_flag5=1;
                    if (render_x<0)
                        render_rel_pos_in_map_x=0.0;
                    if (render_x>=maxpixelsx)
                        render_rel_pos_in_map_x=1.0;
                    if (render_y<0)
                        render_rel_pos_in_map_y=0.0;
                    if (render_y>=maxpixelsy)
                        render_rel_pos_in_map_y=1.0;
                    x=(int) (rel_pos_in_map_x*(double)(maxpixelsx));
                    y=(int) (rel_pos_in_map_y*(double)(maxpixelsy));
                }


                if (!DO_ADAPT)
                {
                    x=x-1920/2;
                    y=y-1080/2;

                    render_x=render_x-1920/2;
                    render_y=render_y-1080/2;

                    x=(maxpixelsx+x)%maxpixelsx;
                    if (x<0)
                        x=0;
                    y=(maxpixelsy+y)%maxpixelsy;
                    if (y<0)
                        y=0;

                    render_x=(maxpixelsx+render_x)%maxpixelsx;
                    if (render_x<0)
                        render_x=0;
                    render_y=(maxpixelsy+render_y)%maxpixelsy;
                    if (render_y<0)
                        render_y=0;

                    if (ret==0 && follow_ghost==0)
                    {
                        position1x=x;
                        position1y=y;
                        position2x=x;
                        position2y=y;
                        save_mazeoff();
                    }
                    smooth_x=(double)render_x;
                    smooth_y=(double)render_y;

                    picturex=x/1920;
                    posx=x-1920*picturex;
                    picturey=y/1080;
                    posy=y-1080*picturey;
                    posx=-posx;
                    posy=-posy;
                    fposx=posx;
                    fposy=posy;

                    render_picturex=render_x/1920;
                    render_posx=render_x-1920*render_picturex;
                    render_picturey=render_y/1080;
                    render_posy=render_y-1080*render_picturey;
                    render_posx=-render_posx;
                    render_posy=-render_posy;

                    render_pacx=(render_picturex*1920-render_posx+1920/2)%maxpixelsx;
                    render_pacy=(render_picturey*1080-render_posy+1080/2)%maxpixelsy;
                    render_rel_pos_in_map_x=(double)(SAS_STARTX*256 + SAS_STARTX_a + (render_pacx) )/(double)(pixels_in_map);
                    render_rel_pos_in_map_y=(double)(SAS_STARTY*256 + SAS_STARTY_a + (render_pacy) )/(double)(pixels_in_map);

                }

                if (follow_ghost==1)
                {
                    posx=posx-posx%64-32;
                    if (posx<=-1920)
                    {
                        posx=posx+1920;
                    }
                    posy=posy-(posy-36)%72-36;
                    if (posy<=-1080)
                    {
                        posy=posy+1080;
                    }
                    fposx=posx;
                    fposy=posy;
                    ReadBitmaps2();

                    int xx=(picturex*1920-posx)%maxpixelsx;
                    int yy=(picturey*1080-posy)%maxpixelsy;

                    fpos_ghostx[follow_ghost_num]=-xx+1920;
                    fpos_ghosty[follow_ghost_num]=-yy+1080;
                    pos_ghostx[follow_ghost_num]=fpos_ghostx[follow_ghost_num];
                    pos_ghosty[follow_ghost_num]=fpos_ghosty[follow_ghost_num];
                    smooth_x=(double)xx;
                    smooth_y=(double)yy;
                }
                if (rel_x_was==rel_pos_in_map_x && rel_y_was==rel_pos_in_map_y && (wchar_t)wparam=='>')
                {
                    if (!DO_ADAPT)
                        forced_jump=1;
                    else
                        soft_jump=1;
                }
                else
                {
                    if (!DO_ADAPT)
                        forced_jump=1;
                    else
                        soft_jump=1;
                }
            }
            else if (follow_ghost==0)
            {
                level++;
                reload_init();
            }

            err_level=1;
            if (connected==1)
            {
                sprintf(writer,"T=MOVELEVEL,LEVEL=%d,\0",level);
                SEND(writer);
            }

            if (MAZEOFF==0)
            {
                totalfiles=0;
                totalfiles_mazes=0;
                if (F2==1)
                {
                    draw2((char*)"SCANNING FILES",800,0,sf::Color::Red,sf::Color::White);
                    SFMLView1.display();
                }
                for (x=0; x<=maxpicturex; x++)
                {
                    for (y=0; y<=maxpicturey; y++)
                    {
                        sprintf(naam,"%s/%dx%d/%03d/picture.%06d.%06d.png",LEVELDIR,BITMAPSX,BITMAPSY,level,y,x);
                        int exist;
                        exist = stat(naam,&buffer);
                        if ( exist!=0)
                        {
                            files[x][y]=0;
                        }
                        else
                        {
                            files[x][y]=1;
                            totalfiles++;
                        }
                        sprintf(naam,"%s/%dx%d/%03d/picture_maze.%06d.%06d.png",LEVELDIR,BITMAPSX,BITMAPSY,level,y,x);
                        exist = stat(naam,&buffer);
                        if ( exist!=0)
                        {
                            files_mazes[x][y]=0;
                        }
                        else
                        {
                            files_mazes[x][y]=1;
                            totalfiles_mazes++;
                        }
                    }
                }
            }
            else
            {
                CLEANBITMAPS();
                follow_ghost_pos();
                ReadBitmaps2();
                ReadBitmaps4();
            }
            forced_jump=1;
            break;
        }
        else
        {
            ghost_next();
//            follow_ghost_pos();
            break;
        }
        break;
    case 't':
        if (mazetype==1)
            mazetype=0;
        else
            mazetype=1;
        break;
    case 'T':
        if (internetfile==0)
        {
            make_black_transparant(&texture_from_internet);
            sprintf(error_msg,"BLACK MADE TRANSPARANT, THRESHOLD=%d",PIXELISBLACKTHRESHOLD);
            error_flag=1;
        }
        if (ffmpegfile==0)
        {
            make_black_transparant(&texture_from_ffmpeg);
            sprintf(error_msg,"BLACK MADE TRANSPARANT, THRESHOLD=%d",PIXELISBLACKTHRESHOLD);
            error_flag=1;
        }
        break;
    case 'W':
        if (internetfile==0)
        {
            make_white_transparant(&texture_from_internet);
            sprintf(error_msg,"WHITE MADE TRANSPARANT, THRESHOLD=%d",PIXELISWHITETHRESHOLD);
            error_flag=1;
        }
        if (ffmpegfile==0)
        {
            make_white_transparant(&texture_from_ffmpeg);
            sprintf(error_msg,"WHITE MADE TRANSPARANT, THRESHOLD=%d",PIXELISWHITETHRESHOLD);
            error_flag=1;
        }
        break;
    case 'A':
        if (internetfile==0)
        {
            make_dark_transparant(&texture_from_internet);
            sprintf(error_msg,"DARK MADE TRANSPARANT");
            error_flag=1;
        }
        if (ffmpegfile==0)
        {
            make_dark_transparant(&texture_from_ffmpeg);
            sprintf(error_msg,"DARK MADE TRANSPARANT");
            error_flag=1;
        }
        break;
    case 'C':
        if (internetfile==0)
        {
            make_color_transparant(&texture_from_internet);
            sprintf(error_msg,"COLOR MADE TRANSPARANT, COLOR-RGB=%d,%d,%d, THRESHOLD=%d",PIXELISCOLOR_B,PIXELISCOLOR_G,PIXELISCOLOR_R,PIXELISCOLORTHRESHOLD);
            error_flag=1;
        }
        if (ffmpegfile==0)
        {
            make_color_transparant(&texture_from_ffmpeg);
            sprintf(error_msg,"COLOR MADE TRANSPARANT, COLOR-RGB=%d,%d,%d, THRESHOLD=%d",PIXELISCOLOR_B,PIXELISCOLOR_G,PIXELISCOLOR_R,PIXELISCOLORTHRESHOLD);
            error_flag=1;
        }
        break;
    case 'p':
        if (drawmazes==1)
            toggle_point=1;
        break;
    case 'q':
        if (DONTSAVEFILES==0)
            DONTSAVEFILES=1;
        else
            DONTSAVEFILES=0;
        break;
    /*
        case '+':
        case '=':
            if (blending==2)
            {
                if (MyBlendMode_num<4)
                    MyBlendMode_num++;
                else
                    MyBlendMode_num=0;
                set_blending();
                break;
            }
            int i;
            int ghostx;
            int ghosty;
            int add;
            if (number<10)
                add=1;
            else if (number<50)
                add=2;
            else if (number<100)
                add=5;
            else if (number<500)
                add=10;
            else if (number<1000)
                add=50;
            else if (number<5000)
                add=100;
            else if (number<10000)
                add=500;
            else if (number<50000)
                add=1000;
            else if (number<100000)
                add=5000;
            else if (number<500000)
                add=10000;
            else
                add=50000;

            if (follow_ghost==0)
            {
                ghostx=posx-( ((picturex-1+(maxpicturex+1))%(maxpicturex+1)) *1920);
                ghosty=posy-( ((picturey-1+(maxpicturey+1))%(maxpicturey+1)) *1080);
            }
            else
            {
                ghostx=real_posx2;
                ghosty=real_posy2;
            }
            ghostx=(ghostx-ghostx%64-32)%(totalpicturex*1920);
            ghosty=(ghosty-(ghosty-36)%72-36)%(totalpicturey*1080);
            for (i=0; i<add; i++)
            {
                int addx=0,addy=0;
                if (number<=maxnumber)
                {
                    if (number!=maxnumber)
                    {
                        if (number%4==0)
                        {
                            fspeed_ghostx[number]=3.0+(rand()%2101)/(1000.0+(hunt>0)*1000.0);
    //                        fspeed_ghostx[number]=10.0+(rand()%8001)/(1000.0+(hunt>0)*1000.0);
    //                        fspeed_ghostx[number]=1.0+floor(pow(number,0.1));
    //                        fspeed_ghostx[number]=10.0123+floor(pow(number,0.1));
                            fspeed_ghosty[number]=0.0;
                            addx-=64;
                        }
                        else if (number%4==1)
                        {
                            fspeed_ghostx[number]=0.0;
    //                        fspeed_ghosty[number]=-10.0123-floor(pow(number,0.1));
    //                        fspeed_ghosty[number]=-1.0-floor(pow(number,0.1));
                            fspeed_ghosty[number]=-3.0-(rand()%2101)/(1000.0+(hunt>0)*1000.0);
    //                        fspeed_ghosty[number]=-10.0-(rand()%8001)/(1000.0+(hunt>0)*1000.0);
                            addy+=72;
                        }
                        else if (number%4==2)
                        {
    //                        fspeed_ghostx[number]=-10.0-(rand()%8001)/(1000.0+(hunt>0)*1000.0);
                            fspeed_ghostx[number]=-3.0-(rand()%2101)/(1000.0+(hunt>0)*1000.0);
    //                        fspeed_ghostx[number]=-10.0123-floor(pow(number,0.1));
    //                        fspeed_ghostx[number]=-1.0-floor(pow(number,0.1));
                            fspeed_ghosty[number]=0.0;
                            addx+=64;
                        }
                        else if (number%4==3)
                        {
                            fspeed_ghostx[number]=0.0;
    //                        fspeed_ghosty[number]=10.0123+floor(pow(number,0.1));
    //                        fspeed_ghosty[number]=1.0+floor(pow(number,0.1));
                            fspeed_ghosty[number]=3.0+(rand()%2101)/(1000.0+(hunt>0)*1000.0);
    //                        fspeed_ghosty[number]=10.0+(rand()%8001)/(1000.0+(hunt>0)*1000.0);
                            addy-=72;
                        }
                        fpos_ghostx[number]=ghostx+addx;
                        fpos_ghosty[number]=ghosty+addy;
                        pos_ghostx[number]=ghostx+addx;
                        pos_ghosty[number]=ghosty+addy;
                        check[number]=0;
                        if (number<maxnumber)
                            number++;
                    }
                }
            }
            break;
    //		case sf::Keyboard::Subtract:
        case '-':
            if (blending==2)
            {
                if (MyBlendMode_num>0)
                    MyBlendMode_num--;
                else
                    MyBlendMode_num=4;
                set_blending();
                break;
            }
            add=1;
            if (number>500000)
                add=50000;
            else if (number>100000)
                add=10000;
            else if (number>50000)
                add=5000;
            else if (number>10000)
                add=1000;
            else if (number>5000)
                add=500;
            else if (number>1000)
                add=100;
            else if (number>500)
                add=50;
            else if (number>100)
                add=10;
            else if (number>50)
                add=5;
            if (number>0)
                number=number-add;
            if (number<=0)
            {
                number=0;
                if (follow_ghost==1)
                {
                    set_pacman();

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

                    follow_ghost=0;
                    long_jump=1;
                    pen=old_pen;
                    if (pen==1)
                        pen_mode=2;
                    else
                        pen_mode=0;
                }
            }
            break;
    */
    case 'g':
        if (ghost==0)
            ghost=1;
        else
            ghost=0;
        break;
    case 'G':
        if (formula==3)
            formula=0;
        else
            formula++;
        break;
    /*
        case 'f':
            if (follow_ghost==0 && number>0)
            {
                follow_ghost=1;
                follow_ghost_start=1;
                old_pen=pen;
                old_pen_mode=pen_mode;
                pen=0;
                pen_mode=0;
                long_jump=1;
                if (movie==0) scale_now=sprite_from_movie.getScale().x;
                if (movie2==0) scale_now=sprite_from_movie2.getScale().x;
                if (internetfile==0) scale_now=sprite_from_internet.getScale().x;
                if (ffmpegfile==0) scale_now=sprite_from_ffmpeg.getScale().x;
            }
            else
            {
                if (movie==0) sprite_from_movie.setScale(scale_now,scale_now);
                if (movie2==0) sprite_from_movie2.setScale(scale_now,scale_now);
    //            if (internetfile==0) sprite_from_internet.setScale(scale_now,scale_now);
                if (ffmpegfile==0) sprite_from_ffmpeg.setScale(scale_now,scale_now);

                set_pacman();
    //pospos
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
                follow_ghost=0;
                long_jump=1;
                pen=old_pen;
                if (pen==1)
                    pen_mode=2;
                else
                    pen_mode=0;
                forced_jump=1;
            }
            if (follow_ghost_num>=number)
                follow_ghost_num=number-1;
            if (number==0)
            {
                follow_ghost=0;
                pen=old_pen;
                if (pen==1)
                    pen_mode=2;
                else
                    pen_mode=0;
                set_pacman();
    //pospos
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

                long_jump=1;
                forced_jump=1;
            }
            break;
    */
    /*
        case 'F':
            if (follow_ghost==0 && number>0)
            {
                follow_ghost=1;
                follow_ghost_start=1;
                old_pen=pen;
                old_pen_mode=pen_mode;
                pen=0;
                pen_mode=0;
            }
            long_jump=1;
            if (best_ghost_num!=-1)
                follow_ghost_num=best_ghost_num;
            fbest_distance=0.0;
            best_ghost_num=-1;
            if (follow_ghost_num>=number)
                follow_ghost_num=number-1;
            if (number==0)
            {
                follow_ghost=0;
                pen=old_pen;
                if (pen==1)
                    pen_mode=2;
                else
                    pen_mode=0;
                set_pacman();
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
                long_jump=1;
                forced_jump=1;
            }
            break;
    */
    case 'U':
        size_internet=1;
//        rotate_internet=0;
        sprite_from_internet.setScale(1.0,1.0);
        scale_now=1.0;
        if (internetfile==0)
        {
            internetfile=1;
            error_flag=0;
            break;
        }
        extern char SAS_URL[];
        extern char SAS_ORDER[];
        get_map_x=SAS_STARTX;
        get_map_y=SAS_STARTY;

        if (strcmp(SAS_ORDER,"XYZ")==0)
            sprintf(line,SAS_URL,get_map_x,get_map_y,get_map_zoom);
        else
            sprintf(line,SAS_URL,get_map_zoom,get_map_y,get_map_x);

        internetfile=GetGoogleMap(line,&texture_from_internet);
//        internetfile=GetGoogleMap(get_map_x,get_map_y,get_map_zoom);

        if (internetfile==0)
        {
            texture_from_internet.setRepeated(TRUE);
            rotation_internet=0.0;
            rot_speed_internet=0.0;
            sprite_from_internet.setTexture(texture_from_internet,false);
            sprite_from_internet.setScale(1.0,1.0);
            scale_now=1.0;
            sprite_from_internet.setTextureRect( { 0,0,(int)texture_from_internet.getSize().x, (int)texture_from_internet.getSize().y } );
            if (smooth==1)
                texture_from_internet.setSmooth(TRUE);
            else
                texture_from_internet.setSmooth(TRUE);
            setinternetfile();
        }
        else
        {
            sprintf(writer,"invalid internet: %s\n",naam);
            savedata(writer,0);
            MessageBox(NULL, writer,"NOT LOADED", MB_ICONEXCLAMATION | MB_OK);
        }
        shift=0;
        break;
    case 'I':
        size_internet=1;
//        rotate_internet=0;
        sprite_from_internet.setScale(1.0,1.0);
        scale_now=1.0;
        if (internetfile==0)
        {
            internetfile=1;
            error_flag=0;
            break;
        }
        internetfile=GetFileFromInternet(naam);

        if (internetfile==0)
        {
            texture_from_internet.setRepeated(TRUE);
            rotation_internet=0.0;
            rot_speed_internet=0.0;
            sprite_from_internet.setTexture(texture_from_internet,false);
            sprite_from_internet.setScale(1.0,1.0);
            scale_now=1.0;
            sprite_from_internet.setTextureRect( { 0,0,(int)texture_from_internet.getSize().x, (int)texture_from_internet.getSize().y } );
            if (smooth==1)
                texture_from_internet.setSmooth(TRUE);
            else
                texture_from_internet.setSmooth(TRUE);
            setinternetfile();
        }
        else
        {
            sprintf(writer,"invalid internet: %s\n",naam);
            savedata(writer,0);
            MessageBox(NULL, writer,"NOT LOADED", MB_ICONEXCLAMATION | MB_OK);
        }
        shift=0;
        break;
    case 'V':
        if (blending==0)
            blending=1;
        else if (blending==1)
            blending=2;
        else
            blending=0;
        if (blending==1)
        {
            strcpy(error_msg2,"BLENDING=ADD, PRESS SHIFT-V AGAIN FOR SPECIAL/CUSTOM BLENDING");
            error_flag2=1;
            MyBlendMode_num=0;
            set_blending();
            error_flag4=0;
            error_flag5=0;
        }
        else if (blending==2)
        {
            strcpy(error_msg2,"SPECIAL BLENDING ON. SHIFT-V=OFF PRESS +(=)/- FOR MODE, 1-6 FOR CUSTOM SETTING. SHIFT-P FOR BLENDING BITMAPS");
            MyBlendMode_num=4;
            error_flag2=1;
            set_blending();
        }
        else
        {
            MyBlendMode_num=0;
            set_blending();
            error_flag4=0;
            error_flag5=0;
        }
        break;
    case 'v':
        if (blend_on_movie==0)
            blend_on_movie=1;
        else if (blend_on_movie==1)
            blend_on_movie=2;
        else
            blend_on_movie=0;

        if (blend_on_movie==1)
        {
            strcpy(error_msg,"BLEND PICTURE (SHIFT-P) ON MOVIE (FIT) (SHIFT-M)  'v' : MAX SIZE");
            error_flag=1;
        }
        else if (blend_on_movie==2)
        {
            strcpy(error_msg,"BLEND PICTURE (SHIFT-P) ON MOVIE (MAX) (SHIFT-M)  'v' : OFF");
            error_flag=1;
        }
        else
        {
            strcpy(error_msg,"BLEND ON MOVIE OFF");
            error_flag=1;
            error_flag4=0;
            error_flag5=0;
        }
        break;

    /*
        case 'b':
            if (movieextern==0) movieextern=1; else movieextern=0;
            if (movieextern==0) {
                if (select_movie(filename,MOVIEDIR)>0) {
                    if (playing_start(filename)==0) {
                        if (record_screen==1) play_rate=1;
                        else play_rate=1;
                        strcpy(error_msg2,"EXTERNAL FFMPEG LOADING SUCCESFULL");
                        error_flag2=1;
    //                    Screenget3();
                        if (flop==0) rate_count=play_rate-1;
                        else rate_count=play_rate;
                    } else {
                        strcpy(error_msg2,"FAILED STARTING MOVIE FROM FFMPEG EXTERN");
                        error_flag2=1;
                        movieextern=1;
                    }
                }
                else
                {
                        strcpy(error_msg2,"EXTERNAL FFMPEG CANNOT SELECT MOVIE (LIST.TXT/PACMAN.INI)");
                        error_flag2=1;
                        movieextern=1;
                }
            } else {
                playing_end();
                strcpy(error_msg2,"EXTERNAL FFMPEG PLAYING ENDED");
                error_flag2=1;
            }
    //        ShowCursor(TRUE);
    //        if (select_movie(filename,MOVIEDIR)>0)
    //            playmovie(filename);
    //        ShowCursor(FALSE);
    //        break;
    */
    case '.':
        if (lookahead==0)
            lookahead=1;
        else
            lookahead=0;
        break;
    case ',':
        if (force_game==0)
            force_game=1;
        else
            force_game=0;
        break;
    case 'K':
        if (mirror==0)
            mirror=1;
        else if (mirror==1)
            mirror=2;
        else if (mirror==2)
            mirror=3;
        else if (mirror==3)
            mirror=4;
        else if (mirror==4)
            mirror=5;
        else if (mirror==5)
            mirror=6;
        else
            mirror=0;
        if (connected==1)
        {
            sprintf(writer,"T=MIRROR,MIRROR=%d,\0",mirror);
            SEND(writer);
        }
        break;
    /*
        case 'B':
            size_movie2=1;
    //        rotate_movie2=0;
            sprite_from_movie2.setScale(1.0,1.0);
            scale_now=1.0;
            if (movie2==1)
            {
                time_movie2=sf::seconds(0.0);
                if (select_movie(filename,MOVIEDIR)>0) {
                    movie2=startmovie2(filename);
                }

                if (movie2==0)
                {
                    texture_from_movie2_new.setRepeated(true);
                    rotation_movie2=0.0;
                    rot_speed_movie2=0.0;
                    rot_speed_movie2=0.0;
                    sprite_from_movie2.setTexture(texture_from_movie2_new,false);
    //                    sprite_from_movie2.setScale(1.0,1.0);
                    scale_now=sprite_from_movie2.getScale().x;

                    sprite_from_movie2.setTextureRect( { 0,0,(int)texture_from_movie2_new.getSize().x, (int)texture_from_movie2_new.getSize().y } );
                    timer_movie2=10;
                    if (smooth==1) texture_from_movie2_new.setSmooth(TRUE);
                    else texture_from_movie2_new.setSmooth(TRUE);
                    setmoviefile2();
                }
                else
                {
                    sprintf(writer,"invalid movie2: %s\n",filename);
                    savedata(writer,0);
                    MessageBox(NULL, writer,"NOT LOADED", MB_ICONEXCLAMATION | MB_OK);
                }

                if (record_screen==1 && record_pause==0 && movie2==0)
                {
    //                    time_movie=sf::seconds(0.0);
                    timer_movie2=10;
                    SFMLView1.setVerticalSyncEnabled(false);
                }
                break;
            }
            else
            {
                error_flag=0;
                stopmovie2();
                movie2=1;
                if (movie!=0)
                {
                    if (sync==1)
                        SFMLView1.setVerticalSyncEnabled(true);
                    else
                        SFMLView1.setVerticalSyncEnabled(false);
                }
            }
            shift=0;
            break;
    */
    /*
        case 'M':
            size_movie=1;
    //        rotate_movie=0;
            sprite_from_movie.setScale(1.0,1.0);
            scale_now=1.0;
            if (movie==1)
            {
                time_movie=sf::seconds(0.0);
                strcpy(movie_name,"");
                if (select_movie(filename,MOVIEDIR)>0)
                    movie=startmovie(filename);
                if (movie==0)
                {
                    texture_from_movie_new.setRepeated(TRUE);
                    strcpy(movie_name,filename);
                    rotation_movie=0.0;
                    rot_speed_movie=0.0;
                    sprite_from_movie.setTexture(texture_from_movie_new,false);
                    sprite_from_movie.setScale(1.0,1.0);
                    scale_now=1.0;

                    sprite_from_movie.setTextureRect( { 0,0,(int)texture_from_movie_new.getSize().x, (int)texture_from_movie_new.getSize().y } );
                    timer_movie=10;
                    if (smooth==1) texture_from_movie_new.setSmooth(TRUE);
                    else texture_from_movie_new.setSmooth(TRUE);
                    setmoviefile();
                }
                else
                {
                    sprintf(writer,"invalid movie: %s\n",filename);
                    savedata(writer,0);
                    MessageBox(NULL, writer,"NOT LOADED", MB_ICONEXCLAMATION | MB_OK);
                }

                if (record_screen==1 && record_pause==0 && movie==0)
                {
    //                    time_movie=sf::seconds(0.0);
                    timer_movie=10;
                    SFMLView1.setVerticalSyncEnabled(false);
                }
                break;
            }
            else
            {
                error_flag=0;
                stopmovie();
                movie=1;
                if (movie2!=0)
                {
                    if (sync==1)
                        SFMLView1.setVerticalSyncEnabled(true);
                    else
                        SFMLView1.setVerticalSyncEnabled(false);
                }
            }
            shift=0;
            break;
    */
    case 'P':
        size_ffmpeg=1;
//        rotate_ffmpeg=0;
        sprite_from_ffmpeg.setScale(1.0,1.0);
        scale_now=1.0;
        if (ffmpegfile==0)
        {
            ffmpegfile=1;
            error_flag=0;
            break;
        }
        if (blending==2 || blend_on_movie>=1)
            GETBLENDINGPICTURE(naam);
        else
            GETPICTURE(naam);

//        texture_name = naam;
        texture_name = std::string() + PICTUREDIR + "/" + GetFileName(naam);
        sprintf(picture_name,"%s",texture_name.c_str());

        if (file_exists(naam))
        {
//            savedata(naam,0);
            if (Inter.loadFromFile(naam))
            {
                if (texture_from_ffmpeg.loadFromImage(Inter))
//            if (texture_from_ffmpeg.loadFromFile(naam))
                {
                    ffmpegfile=0;
                    pen=1;
                    pen_mode=2;
                    if (smooth==1)
                        texture_from_ffmpeg.setSmooth(TRUE);
                    else
                        texture_from_ffmpeg.setSmooth(FALSE);
                }
                else
                {
                    savedata((char*)"failed loading1, to large? Then remove from list.",0);
                    ffmpegfile=1;
                }
            }
            else
            {
                savedata((char*)"failed loading2, to large? Then remove from list.",0);
                ffmpegfile=1;
            }

        }
//        Inter.create(0,0);
        if (ffmpegfile==0)
        {
            texture_from_ffmpeg.setRepeated(TRUE);
            rotation_ffmpeg=0.0;
            rot_speed_ffmpeg=0.0;
            sprite_from_ffmpeg.setTexture(texture_from_ffmpeg,false);
            sprite_from_ffmpeg.setScale(1.0,1.0);
//            sprite_from_ffmpeg.setScale(1.0,1.0);
//            scale_now=0.5;
            scale_now=1.0;
//expand

            sprite_from_ffmpeg.setTextureRect( {0,0,(int)texture_from_ffmpeg.getSize().x, (int)texture_from_ffmpeg.getSize().y } );
//            sprite_from_ffmpeg.setTextureRect( {   -(int)texture_from_ffmpeg.getSize().x,
//                                                    -(int)texture_from_ffmpeg.getSize().y,
//                                                     (int)texture_from_ffmpeg.getSize().x*2,
//                                                     (int)texture_from_ffmpeg.getSize().y*2 }
//                                               );
//            printf("sprite_from_ffmpeg.getTextureRect().left=  %d\n",sprite_from_ffmpeg.getTextureRect().left);
//            printf("sprite_from_ffmpeg.getTextureRect().top=   %d\n",sprite_from_ffmpeg.getTextureRect().top);
//            printf("sprite_from_ffmpeg.getTextureRect().widtht=%d\n",sprite_from_ffmpeg.getTextureRect().width);
//            printf("sprite_from_ffmpeg.getTextureRect().height= %d\n",sprite_from_ffmpeg.getTextureRect().height);

//            sprite_from_ffmpeg.setTextureRect( { 0,0,(int)texture_from_ffmpeg.getSize().x, (int)texture_from_ffmpeg.getSize().y } );
            setffmpegfile();
            texture_from_ffmpeg.generateMipmap();
        }
        else
        {
            sprintf(writer,"invalid image ffmpeg: %s\n",naam);
            savedata(writer,0);
            MessageBox(NULL, writer,"NOT LOADED", MB_ICONEXCLAMATION | MB_OK);
        }
        shift=0;
        break;
    /*
        case '9':
            size_ffmpeg=0;
            rotate_ffmpeg=0;
            sprite_from_ffmpeg.setScale(1.0,1.0);
            scale_now=1.0;
            if (file_exists("resources/black.png"))
            {
                if (texture_from_ffmpeg.loadFromFile("resources/black.png"))
                {
                    ffmpegfile=0;
                    pen=1;
                    pen_mode=2;
                }
                else
                {
                    savedata((char*)"failed resources/black.png",0);
                    ffmpegfile=1;
                }
            }
            if (ffmpegfile==0)
            {
                reload=0;
                old_draw=drawmazes;
                if (loadbackground==0)
                {
                    loadbackground=1;
                    CLEANBITMAPS();
                    //cleanupbitmaps_mazes();
                    reload=1;
                }
                if (drawmazes==1)
                {
                    drawmazes=0;
                    strcpy(error_msg,"DRAW MAZES=OFF  BITMAPS RELOADED  SAVEFILES=0N");
                    error_flag=1;
                    reload=1;
                }
                if (reload==1)
                {
                    LOADALLBITMAPS();
                    ReadBitmaps2();
                    ReadBitmaps4();
                }

                rotation_ffmpeg=0.0;
                rot_speed_ffmpeg=1.0;
                sprite_from_ffmpeg.setTexture(texture_from_ffmpeg,false);
                sprite_from_ffmpeg.setScale(1.0,1.0);
                scale_now=1.0;
                setffmpegfile();
                sprite_from_ffmpeg.setTextureRect( { 0,0,(int)texture_from_ffmpeg.getSize().x, (int)texture_from_ffmpeg.getSize().y } );
                blending=1;
                MyBlendMode_num=4;
                set_blending();
                plot_ffmpegfile=1;
    //      select_url(url,URLDIR)
                plot_front=1;
                plot_back=0;
                reset_normal=1;
                plotplot();
                plot_ffmpegfile=0;
                error_flag4=0;
                error_flag5=0;

                if (old_draw==1)
                {
                    if (totalchanged>0)
                    {
                        DONTSAVEFILES=0;
                        SAVEALLBITMAPS();
                        strcpy(error_msg,"BITMAPS CHANGED!!! SAVING FIRST BEFORE DRAW MAZE!!!");
                        error_flag=1;
                    }
                    else
                    {
                        strcpy(error_msg,"DRAW MAZE=ON");
                        error_flag=1;
                    }
                    drawmazes=1;
                    DRAWALLMAZES();
                    pen=1;
                    pen_mode=2;
                }
            }
            else
            {
                sprintf(writer,"invalid texture %s\n","resources/black.png");
                savedata(writer,0);
                MessageBox(NULL, writer,"NOT LOADED", MB_ICONEXCLAMATION | MB_OK);
            }
            shift=0;
            break;
    */
    case 'h':
        if (hunt==0)
        {
            hunt=1;
            hunt_max=800;
            hunt_counter=800;
        }
        break;
    case 'y':
    case 'Y':
        if (goexit==1)
        {
            if (levelnotsaved==1)
            {
                strcpy(error_msg,"LEVEL FILE ");
//change
                sprintf(naam,"%s/%dx%d/%03d/maze.dat",LEVELDIR,BITMAPSX,BITMAPSY,level);
//					sprintf(naam,"levels/%dx%d/maze%d.dat",BITMAPSX,BITMAPSY,level);
                strcat(error_msg,naam);
                strcat(error_msg," NOT SAVED!!! PRESS AGAIN TO EXIT");
                error_flag=1;
                levelnotsaved=0;
                break;
            }
            else
            {
//                if (server_running) {
//                    send_message='S';
//                    while (server_running) { sf::sleep(sf::seconds(0.1)); kiki(); }
//                    printf("Server stopped, exiting\n");
//                    sf::sleep(sf::seconds(0.2));
//                }
            sound[0].stop();
            sound[1].stop();
            sound[2].stop();
            sound[3].stop();
            sound[4].stop();
            sound[5].stop();
            sound[6].stop();
            sound[7].stop();
//            GenerateConsoleCtrlEvent(CTRL_C_EVENT, 0);
                //exiting=1;
//                go_on=0;
                EXITPROGRAM();
//                exit(0);
//				    cleanupbitmaps_mazes();
            }
            break;
        }
        break;
    case 'n':
        SEED=time(0);
        do_nextlevel();
        if (MAZEOFF!=0)
            read_mazeoff(0);
        break;
    case 'N':
        SEED=LOADED_SEED;
        do_nextlevel();
        if (MAZEOFF!=0)
            read_mazeoff(0);
        break;
    /*
        case 'm':
            if (levelnotsaved==1)
            {
                strcpy(error_msg,"LEVEL NOT SAVED!!! PRESS AGAIN TO MAZE LEVEL / FULL / OFF");
                error_flag=1;
                levelnotsaved=0;
                break;
            }

            if (drawmazes==0)
            {
                if (totalchanged>0)
                {
                    DONTSAVEFILES=0;
                    SAVEALLBITMAPS();
                    strcpy(error_msg,"BITMAPS CHANGED!!! SAVING FIRST BEFORE DRAW MAZE!!!");
                    error_flag=1;
                }
                else
                {
                    strcpy(error_msg,"DRAW MAZE=ON");
                    error_flag=1;
                }
                pen=1;
                pen_mode=2;
                shift=0;
                drawmazes=1;
            }
            cleanupbitmaps_mazes();
            if (loaded==0)
            {
                if (big_large==0)
                {
                    big_large=1;
                    SEED=time(0);
                    sprintf(writer,"T=MAZE,BIGLARGE=%d,SEED=%d,LEVEL=%d,\0",big_large,SEED,level);
                    if (connected==1)
                        SEND(writer);
                }
                else
                {
                    big_large=0;
                    loaded=1;
                }
                loaded_from_maze=0;
            }
            else
            {
                loaded=0;
                if (connected==1)
                {
                    SEED=time(0);
                    sprintf(writer,"T=MAZE,BIGLARGE=%d,SEED=%d,LEVEL=%d,\0",big_large,SEED,level);
                    SEND(writer);
                }
                mazetype=1;
                loaded_from_maze=0;
            }
            if (loaded==1)
            {
    //change
                sprintf(naam,"%s/%dx%d/%03d/maze.dat",LEVELDIR,BITMAPSX,BITMAPSY,level);
    //				sprintf(naam,"levels/%dx%d/maze%d.dat",BITMAPSX,BITMAPSY,level);
                if (!file_exists(naam))
                {
                    level=1;
                    sprintf(naam,"%s/%dx%d/%03d/maze.dat",LEVELDIR,BITMAPSX,BITMAPSY,level);
    //					sprintf(naam,"levels/%dx%d/maze%d.dat",BITMAPSX,BITMAPSY,level);
                    while (!file_exists(naam)&& level<50 )
                    {
                        level++;
                        sprintf(naam,"%s/%dx%d/%03d/maze.dat",LEVELDIR,BITMAPSX,BITMAPSY,level);
    //						sprintf(naam,"levels/%dx%d/maze%d.dat",BITMAPSX,BITMAPSY,level);
                    }
                    if (level==50)
                        level=1;
                }
                if (connected==1)
                {
                    sprintf(writer,"T=LEVEL,LEVEL=%d,\0",level);
                    SEND(writer);
                }
                loaded_from_maze=1;
                load_maze(level);
            }
            next=1;
            forced_jump=1;
            break;
    */
    case ' ':
//		case sf::Keyboard::Space:
        if (follow_ghost==1 && internetfile==0)
        {
            char filenaam[1000];
            sprintf(filenaam,"%s/selected.txt",URLDIR);
            FILE* file = fopen (filenaam, "a");
            if (file!=NULL)
            {
                fprintf (file, "%s\n",internet_naam);
                fclose (file);
            }
            break;
        }
        pressed=1;
        HALT();
        break;
    case 'w':
    case 'i':
//movement
        if (mouse_move==1)
            break;
        if (    ( (internetfile==0 && handler[INTERNET_SELECT].show==1) || (movie==0 ) || (ffmpegfile==0) || (pacman==0) )
                && pen==0 && force_game==0 || (pen==0 && (drawmazes==0 ||   0) ) )
//        if (    ( (internetfile==0 && internet_move==0) || (movie==0 && movie_move==0) || (ffmpegfile==0 && ffmpeg_move==0) )
//                && pen==0 && force_game==0 || (pen==0 && drawmazes==0 && (movie_move==0 || ffmpeg_move==0 || internet_move==0))  )
        {
            if (fspeedy!=0)
            {
                speedy=speedy+1;
                fspeedy=speedy;
//                        speedx=0;
//                        fspeedx=0.0;
            }
            else
            {
                speedy=1;
                fspeedy=1.0;
            }
            speedy_new=speedy;
            speedx_new=0;
            fspeedy_new=speedy;
            fspeedx_new=0;
            maze_up=1;
            maze_down=0;
            maze_left=0;
            maze_right=0;
            maze_up_new=1;
            maze_down_new=0;
            maze_left_new=0;
            maze_right_new=0;
            pressed=1;
            break;
        }
        if (pen==1)
        {
            speedy=72;
            speedx=0;
            fspeedy=72;
            fspeedx=0;
            maze_up=1;
            maze_down=0;
            maze_left=0;
            maze_right=0;
        }
        else
        {
            pressed=1;
//crossing
            speedy_new=4;
            speedx_new=0;
            fspeedy_new=4;
            fspeedx_new=0;
            maze_up_new=1;
            maze_down_new=0;
            maze_left_new=0;
            maze_right_new=0;
        }
        break;
    case 'S':
        if (drawmazes==1)
        {
            static int first=0;
            if (first==0)
            {
                levelnotsaved=1;
                first=1;
            }
            if (levelnotsaved==1)
            {
                strcpy(error_msg,"SAVE BACKGROUND WITH MAZES ON IT????? PRESS AGAIN TO CONFIRM");
                error_flag=1;
                levelnotsaved=0;
                break;
            }
            first=0;
            SAVEALL=1;
        }
        DONTSAVEFILES=0;
        SAVEALLBITMAPS();
        SAVEALL=0;
        pen=1;
        pen_mode=2;
        break;
    case 's':
    case 'k':
//movement
        if (mouse_move==1)
            break;
        if (    ( (internetfile==0 && handler[INTERNET_SELECT].show==1) || (movie==0 ) || (ffmpegfile==0) || (pacman==0) )
                && pen==0 && force_game==0 || (pen==0 && (drawmazes==0 || pacman==0) ) )
//        if (    ( (internetfile==0 && internet_move==0) || (movie==0 && movie_move==0) || (ffmpegfile==0 && ffmpeg_move==0) )
//                && pen==0 && force_game==0 || (pen==0 && drawmazes==0 && (movie_move==0 || ffmpeg_move==0 || internet_move==0))  )
        {
            if (fspeedy!=0)
            {
                speedy=speedy-1;
                fspeedy=speedy;
//                        speedx=0;
//                        fspeedx=0.0;
            }
            else
            {
                speedy=-1;
                fspeedy=-1.0;
            }
            speedy_new=speedy;
            speedx_new=0;
            fspeedy_new=speedy;
            fspeedx_new=0;
            maze_up=0;
            maze_down=1;
            maze_left=0;
            maze_right=0;
            maze_up_new=0;
            maze_down_new=1;
            maze_left_new=0;
            maze_right_new=0;
            pressed=1;
            break;
        }
        if (pen==1)
        {
            speedy=-72;
            speedx=0;
            fspeedy=-72;
            fspeedx=0;
            maze_down=1;
            maze_up=0;
            maze_left=0;
            maze_right=0;
        }
        else
        {
            pressed=1;
//crossing
            speedy_new=-4;
            speedx_new=0;
            fspeedy_new=-4;
            fspeedx_new=0;
            maze_down_new=1;
            maze_up_new=0;
            maze_left_new=0;
            maze_right_new=0;
        }
        break;
    case 'a':
    case 'j':
//movement
        if (mouse_move==1)
            break;
        if (    ( (internetfile==0 && handler[INTERNET_SELECT].show==1) || (movie==0 ) || (ffmpegfile==0) || (pacman==0) )
                && pen==0 && force_game==0 || (pen==0 && (drawmazes==0 || pacman==0) ) )
//        if (    ( (internetfile==0 && internet_move==0) || (movie==0 && movie_move==0) || (ffmpegfile==0 && ffmpeg_move==0) )
//                && pen==0 && force_game==0 || (pen==0 && drawmazes==0 && (movie_move==0 || ffmpeg_move==0 || internet_move==0))  )
        {
            if (fspeedx!=0)
            {
                speedx=speedx+1;
                fspeedx=speedx;
//                        speedy=0;
//                        fspeedy=0.0;
            }
            else
            {
                speedx=1;
                fspeedx=1.0;
            }
            speedx_new=speedx;
            speedy_new=0;
            fspeedx_new=speedx;
            fspeedy_new=0;
            maze_up=0;
            maze_down=0;
            maze_left=1;
            maze_right=0;
            maze_up_new=0;
            maze_down_new=0;
            maze_left_new=1;
            maze_right_new=0;
            pressed=1;
            break;
        }
        if (pen==1)
        {
            speedx=64;
            speedy=0;
            fspeedx=64;
            fspeedy=0;
            maze_left=1;
            maze_right=0;
            maze_up=0;
            maze_down=0;
        }
        else
        {
            pressed=1;
//crossing
            speedx_new=4;
            speedy_new=0;
            fspeedx_new=4;
            fspeedy_new=0;
            maze_left_new=1;
            maze_up_new=0;
            maze_down_new=0;
            maze_right_new=0;
        }
        break;
    case 'D':
        if (drawmazes==0)
        {
            if (totalchanged>0)
            {
                DONTSAVEFILES=0;
                SAVEALLBITMAPS();
                strcpy(error_msg,"BITMAPS CHANGED!!! SAVING FIRST BEFORE DRAW MAZE!!!");
                error_flag=1;
            }
            else
            {
                strcpy(error_msg,"DRAW MAZE=ON");
                error_flag=1;
            }
            drawmazes=1;
            LOADALLBITMAPS();
//            CLEANBITMAPS();
//            ReadBitmaps2();
//            ReadBitmaps4();
            pen=1;
            pen_mode=2;
        }
        else
        {
//???????????
            if (totalchanged>0)
            {
//                DONTSAVEFILES=0;
                if (DONTSAVEFILES==0)
                    SAVEALLBITMAPS();
                strcpy(error_msg,"BITMAPS CHANGED!!! SAVING FIRST BEFORE LOADING BACKGROUND!!!");
                error_flag=1;
            }
            drawmazes=0;
            LOADALLBITMAPS();
            pen=1;
            pen_mode=2;
            strcpy(error_msg,"BITMAPS RELOADED   DRAWMAZES=OFF   SAVE FILES=ON");
            DONTSAVEFILES=0;
            error_flag=1;
            break;
        }
        if (drawmazes==1 && 0)
        {
            strcpy(error_msg,"DRAWMAZE=ON");
            error_flag=1;
//?????????????
//            LOADALLBITMAPS_MAZES();
            DRAWALLMAZES();
        }
        ReadBitmaps2();
        ReadBitmaps4();
        pen=1;
        pen_mode=2;
        break;
    case 'O':
        old_draw=drawmazes;
        if (loadbackground==0)
            loadbackground=1;
        else
            loadbackground=0;
        if (drawmazes==0 || 1)
        {
            if (totalchanged>0)
            {
                if (drawmazes==0)
                    DONTSAVEFILES=0;
                SAVEALLBITMAPS();
                strcpy(error_msg,"BITMAPS CHANGED!!! SAVING FIRST BEFORE SETTING BACKGROUND ON/OFF!!!");
                error_flag=1;
            }
            else
            {
                strcpy(error_msg,"DRAW MAZE=ON");
                error_flag=1;
            }
            pen=1;
            pen_mode=2;
        }
        CLEANBITMAPS();
        drawmazes=old_draw;
//        cleanupbitmaps_mazes();
//        LOADALLBITMAPS();
        ReadBitmaps2();
        ReadBitmaps4();
        pen=1;
        pen_mode=2;
        strcpy(error_msg,"BITMAPS RELOADED   DRAWMAZES=OFF   SAVE FILES=ON");
        DONTSAVEFILES=0;
        error_flag=1;
        if (drawmazes==1)
        {
            strcpy(error_msg,"DRAWMAZE=ON");
            error_flag=1;
            if (blank_maze==0)
                DRAWALLMAZES();
        }
        pen=1;
        pen_mode=2;
        break;
    case 'L':
        err_level=0;
        old_draw=drawmazes;
        if (totalchanged>0 && drawmazes==0)
        {
            DONTSAVEFILES=0;
            SAVEALLBITMAPS();
        }
        drawmazes=0;
        LOADALLBITMAPS();
        pen=1;
        pen_mode=2;
        drawmazes=old_draw;
        if (drawmazes==1)
        {
            strcpy(error_msg,"DRAWMAZE=ON");
            error_flag=1;
            DRAWALLMAZES();
        }
//            DONTSAVEFILES=0;
        break;
    case 'd':
    case 'l':
//movement
        if (mouse_move==1)
            break;
        if (    ( (internetfile==0 && handler[INTERNET_SELECT].show==1) || (movie==0 ) || (ffmpegfile==0) || (pacman==0) )
                && pen==0 && force_game==0 || (pen==0 && (drawmazes==0 || pacman==0) ) )
//        if (    ( (internetfile==0 && internet_move==0) || (movie==0 && movie_move==0) || (ffmpegfile==0 && ffmpeg_move==0) )
//                && pen==0 && force_game==0 || (pen==0 && drawmazes==0 && (movie_move==0 || ffmpeg_move==0 || internet_move==0))  )
        {
            if (fspeedx!=0)
            {
                speedx=speedx-1;
                fspeedx=speedx;
//                        speedy=0;
//                        fspeedy=0.0;
            }
            else
            {
                speedx=-1;
                fspeedx=-1.0;
            }
            speedx_new=speedx;
            speedy_new=0;
            fspeedx_new=speedx;
            fspeedy_new=0;
            maze_up=0;
            maze_down=0;
            maze_left=0;
            maze_right=1;
            maze_up_new=0;
            maze_down_new=0;
            maze_left_new=0;
            maze_right_new=1;
            pressed=1;
            break;
        }
        if (pen==1)
        {
            speedx=-64;
            speedy=0;
            fspeedx=-64;
            fspeedy=0;
            maze_right=1;
            maze_left=0;
            maze_up=0;
            maze_down=0;
        }
        else
        {
            pressed=1;
//crossing
            speedx_new=-4;
            speedy_new=0;
            fspeedx_new=-4;
            fspeedy_new=0;
            maze_right_new=1;
            maze_up_new=0;
            maze_down_new=0;
            maze_left_new=0;
        }
        break;
    case 27:
        int msgboxID;
//        diff_draw.lock();
//        different_draw=1;
//        diff_draw.unlock();
        if (crossing==3 && !mirror==4) MCEDITOR_stop=1;
        else if (mirror==4) {
            flushing=!flushing;
            return;
        }
        if (F1==1)
            F1=0;
        else
        {
            if (goexit==0)
            {
                ESCAPE=1;
                ESCAPE_PRESSED=1;
                flippo=0;
                burn_next_sub_ready=0;
                loadallmaps_level=0;
                loadallmaps=0;
                DO_ZOOM_IN=0;
                DO_ZOOM_OUT=0;
                testing=-1;
                if (levelnotsaved==1 || totalchanged>0 && DONTSAVEFILES==0)
                {
                    strcpy(error_msg,"LEVEL OR BITMAPS NOT SAVED!!!");
                    error_flag=1;
                    levelnotsaved=0;
                }
                if (DO_ADAPT)
                {
                    fspeedx=0;
                    fspeedy=0;
                    DO_ADAPT=0;
                    rel_pos_to_pacman();
                }
                else
                    set_pacman();

                posx=posx-posx%64-32;
                if (posx<=-1920)
                {
                    posx=posx+1920;
                    picturex=(picturex+1+totalpicturex)%totalpicturex;
                }
                posy=posy-(posy-36)%72-36;
                if (posy<=-1080)
                {
                    posy=posy+1080;
                    picturey=(picturey+1+totalpicturey)%totalpicturey;
                }
                fposx=posx;
                fposy=posy;
                ReadBitmaps2();

                follow_ghost=0;
                long_jump=1;
            }
            if (goexit==0)
            {
                loader_mutex.lock();
                monitor_loop=1;
                goexit=1;
                loader_mutex.unlock();
            }
            else
                goexit=0;
            break;
        }
    }
}



void HANDLEEVENTS()
{
    while (SFMLView1.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            SFMLView1.close();
            break;
        case sf::Event::TextEntered:
            if (event.text.unicode < 128)
            {
                HANDLECHAR((WPARAM)event.text.unicode);
                happening=1;
            }
            break;
        case sf::Event::KeyPressed:
            kp.restart();
            HANDLEKEY((WPARAM)event.key.code,event);
            happening=1;
            break;
        case sf::Event::MouseMoved:
        case sf::Event::MouseButtonPressed:
            happening=1;
            if (mouse_move==1)
                continue;
            if (crop && !isrecording) {
                if ( (event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::MouseMoved) && (sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Mouse::isButtonPressed(sf::Mouse::Right) ) )  {
                    sf::Vector2f crop_pos=sprite_from_crop.getPosition();
                    sf::Vector2f crop_size=sprite_from_crop.getScale();
                    int x=event.mouseMove.x;
                    int y=event.mouseMove.y;
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                        if (event.type == sf::Event::MouseButtonPressed) {
                            sf::Mouse::setPosition(sf::Vector2i((int)crop_pos.x,(int)crop_pos.y));
                            x=(int)crop_pos.x;
                            y=(int)crop_pos.y;
                        } else if (event.type == sf::Event::MouseMoved && !(event.type == sf::Event::MouseButtonPressed)) {
                            if (x+crop_size.x>1920) x=1920-crop_size.x;
                            if (y+crop_size.y>1080) y=1080-crop_size.y;
                            sprite_from_crop.setPosition(x,y);
                        }
                    }
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
                        if (event.type == sf::Event::MouseButtonPressed ) {
                            sf::Mouse::setPosition(sf::Vector2i((int)(crop_pos.x+crop_size.x),(int)(crop_pos.y+crop_size.y)));
                            x=(int)(crop_pos.x+crop_size.x);
                            y=(int)(crop_pos.y+crop_size.y);
                        } else if (event.type == sf::Event::MouseMoved && !(event.type == sf::Event::MouseButtonPressed)) {
                            if ( (float)(x-(int)crop_pos.x+1)/2.0 != int((float)(x-(int)crop_pos.x+1)/2.0) ) {
                                x=x+1;
                            }
                            if (crop_pos.x+x > 1920) x-=2;
                            if ( (float)(y-(int)crop_pos.y+1)/2.0 != int((float)(y-(int)crop_pos.y+1)/2.0) ) {
                                y=y+1;
                            }
                            if (crop_pos.y+y > 1080) y-=2;
                            sprite_from_crop.setScale(x-crop_pos.x+1,y-crop_pos.y+1);
                        }
                    }
                }
            }
            if (event.type == sf::Event::MouseButtonPressed || (event.type == sf::Event::MouseMoved && (sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Mouse::isButtonPressed(sf::Mouse::Right) ) ) )
            {
                static int xPos = 0;
                sf::Time targetTime;
                float ratio;
                sf::Vector2f crop_pos;
                if (event.type == sf::Event::MouseButtonPressed && (sf::Mouse::isButtonPressed(sf::Mouse::Left)))
                {
                    xPos = event.mouseButton.x;
                    ratio = static_cast<float>(xPos) / 1920;
                    if (movie==0 && live_movie_is_mp3==0)
                    {
                        targetTime = ratio * live_movie->getDuration();
                        if (record_screen==0 || record_pause==1)
                            live_movie->setPlayingOffset(targetTime);
                        time_movie=targetTime;
                    }
                    if (movie2==0 && live_movie2_is_mp3==0)
                    {
                        targetTime = ratio * live_movie2->getDuration();
                        if (record_screen==0 || record_pause==1)
                            live_movie2->setPlayingOffset(targetTime);
                        time_movie2=targetTime;
                    }
                }
                else if (event.type == sf::Event::MouseMoved && sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    xPos = event.mouseMove.x;
                    ratio = static_cast<float>(xPos) / 1920;
                    if (movie==0 && live_movie_is_mp3==0)
                    {
                        targetTime = ratio * live_movie->getDuration();
                        if (record_screen==0 || record_pause==1)
                            live_movie->setPlayingOffset(targetTime);
                        time_movie=targetTime;
                    }
                    if (movie2==0 && live_movie2_is_mp3==0)
                    {
                        targetTime = ratio * live_movie2->getDuration();
                        if (record_screen==0 || record_pause==1)
                            live_movie2->setPlayingOffset(targetTime);
                        time_movie2=targetTime;
                    }
                }

                if (movie==0)
                {
                    if (xPos!=1919)
                    {
                        static int xPos_mem=0;
                        if (event.type == sf::Event::MouseMoved && sf::Mouse::isButtonPressed(sf::Mouse::Right))
                        {
                            sf::Time t1 = sf::microseconds(500);
                            int xPos2 = event.mouseMove.x-xPos;
                            xPos_mem=xPos_mem+xPos2;
                            xPos2=xPos_mem;

                            ratio = static_cast<float>(xPos) / 1920;
                            t1=t1 * static_cast<float>(xPos2);
                            targetTime = ratio * live_movie->getDuration()+t1;
                            if ( (record_screen==0 || record_pause==1) && live_movie_is_mp3==0)
                                live_movie->setPlayingOffset(targetTime);
                            time_movie=targetTime;
//                                sf::Mouse::setPosition((float)xPos,1080.0/2.0);
                            sf::Mouse::setPosition(sf::Vector2i({xPos,1080/2}),SFMLView1);

                        }
                        if (event.type == sf::Event::MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Right))
                        {
                            xPos_mem=0;
                            if (live_movie->getStatus()==sfe::Playing)
                            {
                                if (live_movie_is_mp3==0)
                                    live_movie->pause();
                            }
                            else
                            {
                                if (record_screen==0 || record_pause==1)
                                    live_movie->play();
                            }
                        }
                    }
                }
                if (movie2==0)
                {
                    if (xPos!=1919)
                    {
                        static int xPos_mem=0;
                        if (event.type == sf::Event::MouseMoved && sf::Mouse::isButtonPressed(sf::Mouse::Right))
                        {
                            sf::Time t1 = sf::microseconds(500);
                            int xPos2 = event.mouseMove.x-xPos;
                            xPos_mem=xPos_mem+xPos2;
                            xPos2=xPos_mem;

                            ratio = static_cast<float>(xPos) / 1920;
                            t1=t1 * static_cast<float>(xPos2);
                            targetTime = ratio * live_movie2->getDuration()+t1;
                            if ( (record_screen==0 || record_pause==1) && live_movie2_is_mp3==0)
                                live_movie2->setPlayingOffset(targetTime);
                            time_movie2=targetTime;
//                                sf::Mouse::setPosition((float)xPos,1080.0/2.0);
                            sf::Mouse::setPosition(sf::Vector2i({xPos,1080/2}),SFMLView1);

                        }
                        if (event.type == sf::Event::MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Right))
                        {
                            xPos_mem=0;
                            if (live_movie2->getStatus()==sfe::Playing)
                            {
                                if (live_movie2_is_mp3==0)
                                    live_movie2->pause();
                            }
                            else
                            {
                                if (record_screen==0 || record_pause==1)
                                    live_movie2->play();
                            }
                        }
                    }
                }
            }
            break;
        default:
            break;
        }
    }
}


void print_event(sf::Event event);
extern void test_minecraft();
extern void launch_MC();

extern void maze_to_ffmpeg();
extern int MCEDITOR_running;
extern int MCEDITOR_stop;

VOID HANDLEKEY(WPARAM wparam, sf::Event event)
{
    char naam[2000];
    char filename[400];
    print_event(event);
    static sf::Vector2u old_size_sfml=sf::Vector2u(1920/2,1080/2);
    static sf::Vector2i old_pos_sfml=sf::Vector2i(10,10);

    switch((wchar_t)wparam)
    {
    case sf::Keyboard::Enter:
        if (event.key.alt && event.key.control) {
            if (vm==1) vm=0;
            else vm=1;
            if (vm==1) {
                SFMLView1.create(sf::VideoMode(1920,1080), "PACMAN", sf::Style::Resize | sf::Style::Titlebar | sf::Style::Close, contextSettings);
                SFMLView1.setSize(old_size_sfml);
                SFMLView1.setPosition(old_pos_sfml);
            }
            else {
                old_size_sfml=SFMLView1.getSize();
                old_pos_sfml=SFMLView1.getPosition();
                SFMLView1.create(sf::VideoMode(1920,1080), "PACMAN", sf::Style::Resize | sf::Style::Fullscreen, contextSettings);
            }
            SFMLView1.setVerticalSyncEnabled(true);
            sync=1;
            break;
        }
        if (event.key.alt) {
            maze_to_ffmpeg();
            break;
        }
        if (event.key.control) {
            if (MCEDITOR_running) {
                printf("   Sending stop signal...wait...\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
                MCEDITOR_stop=1;
                break;
            }
//            mcglobal=2;
            launch_MCEDITOR();
            break;
        } else {
            launch_MC();
            break;
        }
//        test_minecraft();
        break;
    case sf::Keyboard::F:
        if (event.key.control)
        {
            if (flippo==1)
                flippo=0;
            else
                flippo=1;
            if (flippo==0)
            {
                posx=posx-posx%64-32;
                if (posx<=-1920)
                {
                    posx=posx+1920;
                    picturex=(picturex+1+totalpicturex)%totalpicturex;
                }
                posy=posy-(posy-36)%72-36;
                if (posy<=-1080)
                {
                    posy=posy+1080;
                    picturey=(picturey+1+totalpicturey)%totalpicturey;
                }
                fposx=posx;
                fposy=posy;
                ReadBitmaps2();
                fspeedx=0.0;
                fspeedy=0.0;
                speedx=0;
                speedy=0;
                fspeedx_new=0.0;
                fspeedy_new=0.0;
                speedx_new=0;
                speedy_new=0;
                maze_up=0;
                maze_down=0;
                maze_left=0;
                maze_right=0;
                maze_up_new=0;
                maze_down_new=0;
                maze_left_new=0;
                maze_right_new=0;
            }
            break;
        }
        if (event.key.shift)
        {
            if (follow_ghost==0 && number>0)
            {
                follow_ghost=1;
                follow_ghost_start=1;
                old_pen=pen;
                old_pen_mode=pen_mode;
                pen=0;
                pen_mode=0;
            }
//            long_jump=1;
            if (best_ghost_num!=-1)
                follow_ghost_num=best_ghost_num;
            fbest_distance=0.0;
            best_ghost_num=-1;
            if (follow_ghost_num>=number)
                follow_ghost_num=number-1;
            if (number==0)
            {
                follow_ghost=0;
                pen=old_pen;
                if (pen==1)
                    pen_mode=2;
                else
                    pen_mode=0;
                set_pacman();
                posx=posx-posx%64-32;
                if (posx<=-1920)
                {
                    posx=posx+1920;
                    picturex=(picturex+1+totalpicturex)%totalpicturex;
                }
                posy=posy-(posy-36)%72-36;
                if (posy<=-1080)
                {
                    posy=posy+1080;
                    picturey=(picturey+1+totalpicturey)%totalpicturey;
                }
                fposx=posx;
                fposy=posy;
                ReadBitmaps2();
                long_jump=1;
                forced_jump=1;
            }
            break;

        }
        else if (follow_ghost==0 && number>0)
        {
            follow_ghost=1;
            follow_ghost_start=1;
            old_pen=pen;
            old_pen_mode=pen_mode;
            pen=0;
            pen_mode=0;
//            long_jump=1;
            if (movie==0)
                scale_now=sprite_from_movie.getScale().x;
            if (movie2==0)
                scale_now=sprite_from_movie2.getScale().x;
            if (internetfile==0)
                scale_now=sprite_from_internet.getScale().x;
            if (ffmpegfile==0)
                scale_now=sprite_from_ffmpeg.getScale().x;
        }
        else
        {
            if (movie==0)
                sprite_from_movie.setScale(scale_now,scale_now);
            if (movie2==0)
                sprite_from_movie2.setScale(scale_now,scale_now);
//            if (internetfile==0) sprite_from_internet.setScale(scale_now,scale_now);
            if (ffmpegfile==0)
                sprite_from_ffmpeg.setScale(scale_now,scale_now);


            set_pacman();
            posx=posx-posx%64-32;
            if (posx<=-1920)
            {
                posx=posx+1920;
                picturex=(picturex+1+totalpicturex)%totalpicturex;
            }
            posy=posy-(posy-36)%72-36;
            if (posy<=-1080)
            {
                posy=posy+1080;
                picturey=(picturey+1+totalpicturey)%totalpicturey;
            }
            fposx=posx;
            fposy=posy;

            follow_ghost=0;
//            long_jump=1;
            pen=old_pen;
            if (pen==1)
                pen_mode=2;
            else
                pen_mode=0;
//            forced_jump=1;
        }
        if (follow_ghost_num>=number)
            follow_ghost_num=number-1;
        if (number==0)
        {
            follow_ghost=0;
            pen=old_pen;
            if (pen==1)
                pen_mode=2;
            else
                pen_mode=0;
            set_pacman();
//pospos
            posx=posx-posx%64-32;
            if (posx<=-1920)
            {
                posx=posx+1920;
                picturex=(picturex+1+totalpicturex)%totalpicturex;
            }
            posy=posy-(posy-36)%72-36;
            if (posy<=-1080)
            {
                posy=posy+1080;
                picturey=(picturey+1+totalpicturey)%totalpicturey;
            }
            fposx=posx;
            fposy=posy;
            ReadBitmaps2();

//            long_jump=1;
//            forced_jump=1;
        }
        break;
    case sf::Keyboard::Num0:
        Screenshot();
        break;
    case sf::Keyboard::Num1:
        if (blending==2)
        {
            if (MyBlend_colorSrcFactor_num<9)
                MyBlend_colorSrcFactor_num++;
            else
                MyBlend_colorSrcFactor_num=0;
            MyBlendMode_num=4;
            set_blending();
            break;
        }
        difficulty=1;
        strcpy(error_msg,"DIFFICULTY EASY");
        error_flag=2;
        break;
    case sf::Keyboard::Num2:
        if (blending==2)
        {
            if (MyBlend_colorDstFactor_num<9)
                MyBlend_colorDstFactor_num++;
            else
                MyBlend_colorDstFactor_num=0;
            MyBlendMode_num=4;
            set_blending();
            break;
        }
        difficulty=2;
        strcpy(error_msg,"DIFFICULTY NORMAL");
        error_flag=2;
        break;
    case sf::Keyboard::Num3:
        if (blending==2)
        {
            if (MyBlend_colorEquation_num<2)
                MyBlend_colorEquation_num++;
            else
                MyBlend_colorEquation_num=0;
            MyBlendMode_num=4;
            set_blending();
            break;
        }
        difficulty=3;
        strcpy(error_msg,"DIFFICULTY HARD");
        error_flag=2;
        break;
    case sf::Keyboard::Num4:
        if (blending==2)
        {
            if (MyBlend_alphaSrcFactor_num<9)
                MyBlend_alphaSrcFactor_num++;
            else
                MyBlend_alphaSrcFactor_num=0;
            MyBlendMode_num=4;
            set_blending();
            break;
        }
        difficulty=4;
        strcpy(error_msg,"DIFFICULTY ULTRA");
        error_flag=2;
        break;
    case sf::Keyboard::Num5:
        if (blending==2)
        {
            if (MyBlend_alphaDstFactor_num<9)
                MyBlend_alphaDstFactor_num++;
            else
                MyBlend_alphaDstFactor_num=0;
            MyBlendMode_num=4;
            set_blending();
            break;
        }
        send_message='m';
        break;
    case sf::Keyboard::Num6:
        if (blending==2)
        {
            if (MyBlend_alphaEquation_num<2)
                MyBlend_alphaEquation_num++;
            else
                MyBlend_alphaEquation_num=0;
            MyBlendMode_num=4;
            set_blending();
            break;
        }
        if (event.key.control && event.key.alt) {
            flying();
            break;
        }
        if (event.key.shift) {
            send_message='l';
            break;
        } else if (event.key.control) {
            send_message='o';
            break;
        } else if (event.key.alt) {
            char arg0[10]="moi";
            char arg1[10]="";
            char *arg[2]={arg0,arg1};
            main_get3d(1,arg);
            break;
        } else {
            send_message='n';
            break;
        }
//        SFMLGL_THREAD();
        break;
    case sf::Keyboard::Num9:
        size_ffmpeg=0;
        rotate_ffmpeg=0;
        sprite_from_ffmpeg.setScale(1.0,1.0);
        scale_now=1.0;
        if (file_exists("resources/black.png")) {
            if (texture_from_ffmpeg.loadFromFile("resources/black.png")) { ffmpegfile=0; pen=1; pen_mode=2; }
            else { savedata((char*)"failed resources/black.png",0); ffmpegfile=1; }
        }
        if (ffmpegfile==0)
        {
            reload=0;
            old_draw=drawmazes;
            if (loadbackground==0)
            {
                loadbackground=1;
                CLEANBITMAPS();
                //cleanupbitmaps_mazes();
                reload=1;
            }
            /*
                        if (drawmazes==1)
                        {
                            drawmazes=0;
                            strcpy(error_msg,"DRAW MAZES=OFF  BITMAPS RELOADED  SAVEFILES=0N");
                            error_flag=1;
                            reload=1;
                        }
            */
            if (reload==1)
            {
                LOADALLBITMAPS();
                ReadBitmaps2();
                ReadBitmaps4();
            }

            rotation_ffmpeg=0.0;
            rot_speed_ffmpeg=0.0;
            sprite_from_ffmpeg.setTexture(texture_from_ffmpeg,false);
            sprite_from_ffmpeg.setScale(1.0,1.0);
            scale_now=1.0;
            setffmpegfile();
            sprite_from_ffmpeg.setTextureRect( { 0,0,(int)texture_from_ffmpeg.getSize().x, (int)texture_from_ffmpeg.getSize().y } );
            blending=1;
            MyBlendMode_num=4;
            set_blending();
            plot_ffmpegfile=1;
//      select_url(url,URLDIR)
            plot_front=1;
            plot_back=0;
            reset_normal=1;
            selector=FFMPEG_SELECT;
            sf::BlendMode old_mode=picture_states.blendMode;
            picture_states.blendMode=MyBlendMode[4];
            plotplot();
            picture_states.blendMode=old_mode;
            plot_ffmpegfile=0;
            error_flag4=0;
            error_flag5=0;

            /*
                        if (old_draw==1)
                        {
                            if (totalchanged>0)
                            {
                                DONTSAVEFILES=0;
                                SAVEALLBITMAPS();
                                strcpy(error_msg,"BITMAPS CHANGED!!! SAVING FIRST BEFORE DRAW MAZE!!!");
                                error_flag=1;
                            }
                            else
                            {
                                strcpy(error_msg,"DRAW MAZE=ON");
                                error_flag=1;
                            }
                            drawmazes=1;
                            DRAWALLMAZES();
                            pen=1;
                            pen_mode=2;
                        }
            */
        }
        else
        {
            sprintf(writer,"invalid texture %s\n","resources/black.png");
            savedata(writer,0);
            MessageBox(NULL, writer,"NOT LOADED", MB_ICONEXCLAMATION | MB_OK);
        }
        shift=0;
        break;
    case sf::Keyboard::Numpad6:
        if (event.key.alt)
            plot_all_rotate_x+=1.0;
        else
            plot_all_translate_x+=1.0;
        break;
    case sf::Keyboard::Numpad4:
        if (event.key.alt)
            plot_all_rotate_x-=1.0;
        else
            plot_all_translate_x-=1.0;
        break;
    case sf::Keyboard::Numpad8:
        if (event.key.alt)
            plot_all_rotate_y-=1.0;
        else {
            if (event.key.control)
                plot_all_translate_y-=0.1;
            else
                plot_all_translate_y-=1.0;

        }
        break;
    case sf::Keyboard::Numpad2:
        if (event.key.alt)
            plot_all_rotate_y+=1.0;
        else
            if (event.key.control)
                plot_all_translate_y+=0.1;
            else
                plot_all_translate_y+=1.0;
        break;
    case sf::Keyboard::Numpad7:
        if (event.key.alt)
            plot_all_rotate_z-=1.0;
        else if (event.key.control)
        {
            plot_all_fovyInDegrees+=1.0;
        }
        else
            plot_all_translate_z-=1.0;
        break;
    case sf::Keyboard::Numpad1:
        if (event.key.alt)
            plot_all_rotate_z+=1.0;
        else if (event.key.control)
        {
            plot_all_fovyInDegrees-=1.0;
        }
        else
            plot_all_translate_z+=1.0;
        break;
    case sf::Keyboard::Numpad9:
        if (event.key.alt)
        {
            if (event.key.control)
                plot_all_zfar+=0.01;
            else
                plot_all_zfar+=0.1;
            break;
        }
        if (event.key.control)
            plot_all_znear+=0.01;
        else
            plot_all_znear+=0.1;
        break;
    case sf::Keyboard::Numpad5:
        if (event.key.alt)
        {
            if (draw_model==0)
                draw_model=6;
            else
                draw_model--;
        }
        else
        {
            if (draw_model==6)
                draw_model=0;
            else
                draw_model++;
        }
        if (draw_model==6) {
            plot_all_znear=1.6;
//            sprite_from_canvas.setScale(0.15892,0.15892);
//            sprite_from_canvas.setScale(0.15696,0.15696);
            sprite_from_canvas.setScale(0.13304,0.13304);
            plot_all_translate_z=-116;
//            plot_all_translate_y=39;
            plot_all_translate_y=43;


//            plot_all_znear=1.10;
//            sprite_from_canvas.setScale(0.03592,0.03592);
//            plot_all_translate_z=14;
        }
        break;
    case sf::Keyboard::Numpad3:
        if (event.key.alt)
        {
            if (event.key.control)
                plot_all_zfar-=0.01;
            else
                plot_all_zfar-=0.1;
            break;
        }
        if (event.key.control)
            plot_all_znear-=0.01;
        else
            plot_all_znear-=0.1;
        break;
    case sf::Keyboard::Tab:
        if (event.key.control)
        {
            if (pacman==0)
                pacman=1;
            else
                pacman=0;
        }
        else if (event.key.shift)
        {
            if (pen==0)
            {
                pen=1;
                pen_mode=2;
                if (drawmazes==0)
                    pen_mode=2;
            }
            else
            {
                pen_mode--;
                if (pen_mode<0)
                {
                    pen_mode=0;
                    pen=0;
                }
                if (drawmazes==0)
                    pen_mode=2;
            }
            HALT();
        }
        else
        {
            if (pen==0)
            {
                pen=1;
                pen_mode=0;
                if (drawmazes==0)
                    pen_mode=2;
            }
            else
            {
                pen_mode++;
                if (pen_mode>2)
                    pen=0;
                if (drawmazes==0)
                    pen_mode=2;
            }
            HALT();
        }
        if (pacman==1 || pen!=0)
        {
            posx=posx-posx%64-32;
            if (posx<=-1920)
            {
                posx=posx+1920;
                picturex=(picturex+1+totalpicturex)%totalpicturex;
            }
            posy=posy-(posy-36)%72-36;
            if (posy<=-1080)
            {
                posy=posy+1080;
                picturey=(picturey+1+totalpicturey)%totalpicturey;
            }
            fposx=posx;
            fposy=posy;
            ReadBitmaps2();
        }
        break;
    case sf::Keyboard::Num8:
        do3d();
        break;
    case sf::Keyboard::Backspace:
        area=areas(0);
        strcpy(error_msg,area.c_str());
        error_flag=2;
        combine=1;
        break;
    case sf::Keyboard::Num7:
        send_message='k';
//        OPENGL_THREAD();
//        do3dview();
        break;
    case sf::Keyboard::Z:
        if (event.key.alt)
        {
            get_map_zoom++;
//            Fget_map_x=Fget_map_x/2.0;
//            Fget_map_y=Fget_map_y/2.0;
//            SAS_STARTX=(int)Fget_map_x;
//            SAS_STARTY=(int)Fget_map_y;
            SAS_ZOOM=get_map_zoom;
//            get_map_x=(int)Fget_map_x;
//            get_map_y=(int)Fget_map_y;
            break;
        }
        if (event.key.control)
        {
            get_map_zoom--;
//            Fget_map_x=Fget_map_x*2.0;
//            Fget_map_y=Fget_map_y*2.0;
//            SAS_STARTX=(int)Fget_map_x;
//            SAS_STARTY=(int)Fget_map_y;
            SAS_ZOOM=get_map_zoom;
//            get_map_x=(int)Fget_map_x;
//            get_map_y=(int)Fget_map_y;
            break;
        }
        break;
//printing
    case sf::Keyboard::T:
        if (event.key.shift && event.key.control)
        {
            if (combine==1)
                batch_pictures2();
            else
                batch_pictures();
            break;
        }
        if (event.key.alt && event.key.control)
        {
            if (combine==1 && ffmpegfile==0)            //texture -> maze (2)
            {
                ffmpegfile_to_maze2();
            }
            else if (combine==1 && ffmpegfile==1)       //maze -> texture (2)
            {
                ffmpegfile_to_maze2();
            }
            else if (ffmpegfile==0)                     //texture -> maze (1)
            {
                ffmpegfile_to_maze();
            }
            else
            {
                reverse_maze();
            }
            break;
        }
        if (event.key.alt)
        {
            int print_it;
            int name_num=0;
            char name[500];
            print_it=0;
            var_font=1;
            int font_size=60;
            if (ffmpegfile==0)
                font_size=font_size*sprite_from_ffmpeg.getScale().x;
            sprite_from_ffmpeg.setScale(sf::Vector2f(1.0,1.0));
//            int type=sf::Text::Bold;
//            sf::Uint32 type=sf::Text::Bold;
            sf::Uint32 type=sf::Text::Regular;
            int end=0;
            int start=1;
            int x_position;
            int y_position;
//            x_position=1920*2-1920/2;
            y_position=1080;
            char line[2000]="";
            char line2[2000]="";
            char filename[1000];
            int next_file=1;
            int next_line=0;
            int niet_goed=1;
            int screen_x;
            int screen_y;
            int skippy=2;
//            ffmpeg_move=0;
//            size_ffmpeg=0;

//            x_position=0;
//            screen_x=x_position;
//            ffmpeg_move=1;

            x_position=1920/2+32+1920;
            screen_x=x_position-1920/2;
            ffmpeg_move=1;

            screen_y=(-1080+font_size*3+maxpixelsy+y_position)%maxpixelsy;
            size_ffmpeg=1;

            rotate_ffmpeg=0;

//            rotation_ffmpeg=0;

//            scale_now=1.0;

            picturex=screen_x/1920;
            render_picturex=picturex;
            posx=screen_x-1920*picturex;
            picturey=screen_y/1080;
            render_picturey=picturey;
            posy=screen_y-1080*picturey;
            posx=-posx;
            render_posx=posx;
            posy=-posy;
            render_posy=posy;
            fposx=posx;
            fposy=posy;
            ReadBitmaps2();
            ReadBitmaps4();

            ffmpeg_posx=x_position;
//            ffmpeg_posx=x_position+1920/2;
            ffmpeg_posy=y_position;

            strcpy(naam_from_file,"");

            if (file_is_open_line_from_file==1)
                fclose(file_from_file);
            file_is_open_line_from_file=0;
            max_line_from_file=0;

            next_textfile=0;
            total_textfile=0;
            start_textfile=1;

            while (niet_goed==1)
            {
                niet_goed=0;
                if (next_line<1 || start==1)
                {
                    next_file=select_textfile(filename,"..\\tekst");
//                    next_file=select_textfile(filename,".");
                    if (next_file>0)
                    {
                        printf("Selected filename #%d from list.txt : %s\n",next_file,filename);
                        print_it=0;
                    }
                    else if (next_file==0)
                    {
                        printf("list.txt is empty.\n");
                        print_it=0;
                    }
                    else
                    {
                        printf("File list.txt end reached\n");
                        niet_goed=1;
                        print_it=0;
                    }
                    if (next_file==-1)
                    {
                        end=1;
//                        next_file=1;
//                        next_line=-1;
                        break;
                    }
                }
                int plot;
                plot=0;
                if (next_file>0 && next_line<1)
                {
//                    if (start==0) {
//                        y_position=y_position+font_size+4;
//                        screen_y=(-1080-font_size*3+maxpixelsy+y_position)%maxpixelsy;
//                        ffmpeg_posy=y_position;
//                        ffmpeg_posy=ffmpeg_posy+font_size+4;
//                    } else start=0;
//                    sprintf(line2,"FILE #%d : %s",next_file,filename); plot=1;
                    print_it=0;
                }
                else if (next_file==0 && next_line<1)
                {
                    sprintf(line2,"FILE LIST.TXT IS EMPTY");
                    plot=0;
                    print_it=0;
                }
                else if (next_file==-1)
                {
                    sprintf(line2,"END OF LIST.TXT REACHED");
                    plot=0;
                    print_it=0;
                }
                else if (next_line>0)
                {
                    sprintf(line2,"%s",line);
                    plot=1;
//                    sprintf(line2,"%6d : %s",next_line,line); plot=1;
                }
                else if (next_line==0)
                {
                    sprintf(line2,"FILE #%d : %s IS EMPTY",next_file,filename);
                    plot=0;
                    print_it=0;
                }
                else if (next_line<0 && niet_goed==1)
                {
                    sprintf(line2,"END OF FILE #%d : %s",next_file,filename);
                    plot=0;
                    print_it=0;
                }
                if (plot==1 && end==0 && start==0 && print_it==1 && skippy==0)
                {
                    bool nl=true;
                    wchar_t* line_w_pointer=line_w;
                    print_it=0;
                    if (line_w[0]!=(wchar_t)'&') {
                        y_position=y_position+font_size+4;
                        nl=false;
                    } else {
                        sprintf((char*)line_w,"%s",(char*)&line_w[1]);
//                      line_w_pointer=&line_w[4];
                    }
                    screen_y=(-1080+font_size*3+maxpixelsy+y_position)%maxpixelsy;
                    ffmpeg_posy=y_position;
//                    x_position=x_position+200;
//                    screen_x=(x_position+200+maxpixelsx)%maxpixelsx;

                    picturex=screen_x/1920;                    render_picturex=picturex;                    posx=screen_x-1920*picturex;
                    picturey=screen_y/1080;                    render_picturey=picturey;                    posy=screen_y-1080*picturey;
                    posx=-posx;                    render_posx=posx;
                    posy=-posy;                    render_posy=posy;

                    if (!nl)
                        text_to_ffmpeg_w((wchar_t *) line_w,font_size,sf::Color(255,255,255,255),sf::Color(10,10,10,255),type);
                    else
                        text_to_ffmpeg_w(line_w_pointer,font_size,sf::Color(255,0,0,255),sf::Color(10,10,10,255),type);

                    if (combine==1)
                    {
                        sprintf(name,"%s/%dx%d/%03d/text%09d.png",LEVELDIR,BITMAPSX,BITMAPSY,level,name_num);
                        texture_from_ffmpeg.copyToImage().saveToFile(name);
                        name_num++;
                    }

                    ffmpeg_posx=screen_x+1920/2-(int)(texture_from_ffmpeg.getSize().x/2);

                    int start_posx_mem=(picturex*1920-posx);
                    int start_posy_mem=(picturey*1080-posy);

                    int render_picturex_mem=render_picturex;
                    int render_picturey_mem=render_picturey;
                    int render_posx_mem=render_posx;
                    int render_posy_mem=render_posy;

                    int picturex_mem=picturex;
                    int picturey_mem=picturey;
                    int posx_mem=posx;
                    int posy_mem=posy;

                    start_posx=ffmpeg_posx-1920/2+(int)(texture_from_ffmpeg.getSize().x/2);
                    start_posy=ffmpeg_posy-1080/2+(int)(texture_from_ffmpeg.getSize().y/2);
//                    start_posx=ffmpeg_posx-1920/2;
//                    start_posy=ffmpeg_posy-1080/2;

                    if ((start_posx)>=maxpixelsx)
                        start_posx=start_posx-maxpixelsx;
                    else if ((start_posx)<0)
                        start_posx=start_posx+maxpixelsx;
                    if ((start_posy)>=maxpixelsy)
                        start_posy=start_posy-maxpixelsy;
                    else if ((start_posy)<0)
                        start_posy=start_posy+maxpixelsy;

                    home_map();
                    render_picturex=picturex;
                    render_posx=posx;
                    render_picturey=picturey;
                    render_posy=posy;

                    perform_quit=1;
                    setffmpegfile();
                    plot_ffmpegfile=1;
                    plot_some();
                    perform_quit=0;

                    start_posx=start_posx_mem;
                    start_posy=start_posy_mem;

                    render_picturex=render_picturex_mem;
                    render_picturey=render_picturey_mem;
                    render_posx=render_posx_mem;
                    render_posy=render_posy_mem;

                    picturex=picturex_mem;
                    picturey=picturey_mem;
                    posx=posx_mem;
                    posy=posy_mem;

                    blitter("",1);
                    if (y_position>=maxpixelsy)
                    {
                        strcpy(error_msg4,"END OF SCREEN REACHED, ABORTING");
                        printf("%s\n",error_msg4);
                        error_flag4=1;
                        break;
                    }
                    if (end==1)
                    {
                        strcpy(error_msg4,"END OF LIST.TXT, ABORTING");
                        printf("%s\n",error_msg4);
                        error_flag4=1;
                        break;
                    }
                    if (next_file==-1 && next_line<1)
                    {
                        strcpy(error_msg4,"END OF LIST.TXT REACHED, READY");
                        printf("%s\n",error_msg4);
                        error_flag4=1;
                        break;
                    }
                    if (ESCAPE==1)
                    {
                        strcpy(error_msg4,"ESCAPE PRESSED, ABORTING");
                        printf("%s\n",error_msg4);
                        error_flag4=1;
                        goexit=0;
                        break;
                    }
                    if (next_file>0 && next_line<1)
                    {
//                        ffmpeg_posy=ffmpeg_posy+font_size+4;
//                        y_position+=font_size+4;
                    }
                }
                start=0;

                if (next_file>0)
                {
                    static int old_line=0;

                    next_line=select_line_from_file_w(line,filename);
//                    next_line=select_nextline(line,filename);
                    if (next_line>0)
                    {
//                        printf("pos: %d,%d -> Selected line #%d from %s : %s",ffmpeg_posx,ffmpeg_posy,next_line,filename,line);
                        niet_goed=1;
                        print_it=1;
                        if (skippy>0)
                            skippy--;
                    }
                    else if (next_line==0)
                    {
                        printf("File %s is empty.\n",filename);
                        sprintf(line,"File %s is empty.",filename);
                        niet_goed=1;
                    }
                    else
                    {
                        printf("\nFile %s end reached.\n",filename);
                        niet_goed=1;
                    }
                }
                kiki();
            }
            ffmpegfile=0;
            ffmpeg_move=0;
            size_ffmpeg=0;
            forced_jump=1;
            follow_ghost_pos();
            ReadBitmaps2();
            ReadBitmaps4();
            break;
        }
        else if (event.key.control)
        {
            font_to_ffmpeg();
        }
        else if (event.key.shift)     //allready in use.....not working...
        {
            set_mytext(1);
        }
        break;
    case sf::Keyboard::F1:
        if (event.key.control)
        {
            if (mouse_move==1)
                mouse_move=0;
            else
            {
                mouse_move=1;
                position=sf::Vector2i(960,540);
                sf::Mouse::setPosition(sf::Vector2i(960,540));
            }
            break;
        }
        if (event.key.shift)
        {
//            read_keylist_hpp();
//            printf("Test 1: parse_command(\"MACRO_LIST\"); \n");
            parse_command("MACRO_LIST");
//            printf("Test 2: command_par(1,MACRO_LIST); \n");
//            command_par(1,MACRO_LIST);
//            printf("Test 2: command(MACRO_LIST); \n");
//            do_command(MACRO_LIST);

            break;
        }
        if (event.key.alt)
        {
            int result;
            if (vertex_shader==0)
                vertex_shader=1;
            else
                vertex_shader=0;
            load_vertex_filename();
            result=update_shader();
            if (result==1)
            {
                strcpy(error_msg,"ERROR INITIALIZING SHADER(S)");
                error_flag=1;
                vertex_shader=0;
            }
            else
            {
                if (vertex_shader==1 || fragment_shader==1)
                {
                    strcpy(error_msg,"INITIALIZING SHADER(S) OK");
                    error_flag=1;
                }
                else
                {
                    strcpy(error_msg,"SHADER(S) OFF");
                    error_flag=1;
                }
            }
            break;
        }
        if (F1==1)
            F1=0;
        else
            F1=1;
        break;
    case sf::Keyboard::F2:
        if (event.key.control)
        {
            int result;
            load_fragment_filename(-1);
            result=update_shader();
            if (result==1)
            {
                strcpy(error_msg,"ERROR INITIALIZING SHADER(S)");
                error_flag=1;
                fragment_shader=0;
            }
            else
            {
                if (vertex_shader==1 || fragment_shader==1)
                {
                    strcpy(error_msg,"INITIALIZING SHADER(S) OK");
                    error_flag=1;
                }
                else
                {
                    strcpy(error_msg,"SHADER(S) OFF");
                    error_flag=1;
                }
            }
            break;
        }
        if (event.key.alt)
        {
            int result;
            if (fragment_shader==0)
                fragment_shader=1;
            else
                fragment_shader=0;
            if (fragment_shader==1)
            {
                load_fragment_filename(1);
                result=update_shader();
                if (result==1)
                {
                    strcpy(error_msg,"ERROR INITIALIZING SHADER(S)");
                    error_flag=1;
                    fragment_shader=0;
                }
                else
                {
                    if (vertex_shader==1 || fragment_shader==1)
                    {
                        strcpy(error_msg,"INITIALIZING SHADER(S) OK");
                        error_flag=1;
                    }
                    else
                    {
                        strcpy(error_msg,"SHADER(S) OFF");
                        error_flag=1;
                    }
                }
            }
            break;
        }
        if (event.key.shift)
        {
            if (check_mem==0)
                check_mem=1;
            else
                check_mem=0;
            break;
        }
        F2++;
        if (F2>1)
            F2=0;
        break;
    case sf::Keyboard::F3:
        if (event.key.alt)
        {
            int result;
            if (buffer_shader==0)
                buffer_shader=1;
            else
                buffer_shader=0;
            load_buffer_filename();
            result=update_buffer_shader(1);
            if (result==1)
            {
                strcpy(error_msg,"ERROR INITIALIZING BUFFER SHADER");
                error_flag=1;
                buffer_shader=0;
            }
            else
            {
                if (buffer_shader==1)
                {
                    strcpy(error_msg,"INITIALIZING BUFFER SHADER");
                    error_flag=1;
                }
                else
                {
                    strcpy(error_msg,"BUFFER SHADER OFF");
                    error_flag=1;
                }
            }
            break;
        }
        if (sync==1)
            sync=0;
        else
            sync=1;
        if (sync==1)
            SFMLView1.setVerticalSyncEnabled(true);
        else
            SFMLView1.setVerticalSyncEnabled(false);
        break;
    case sf::Keyboard::F4:
        if (F4==1)
            F4=0;
        else
            F4=1;
        break;
    case sf::Keyboard::F5:
        if (event.key.control)
        {
            if (totalchanged>0)
            {
                DONTSAVEFILES=0;
                SAVEALLBITMAPS();
            }
            if (!event.key.shift)
                merge_back_to_front();
            else
                shift_back();

            CLEANBITMAPS();
            ReadBitmaps2();
            ReadBitmaps4();
            break;
        }
        if (event.key.alt)
        {
            if (shade_main==0)
                shade_main=1;
            else
                shade_main=0;
            break;
        }

        if (connected==1 && playerleft==0)
            goto_partner();
        else if (follow_ghost==1)
        {
            goto_ghost();
        }
        break;
    case sf::Keyboard::F6:
        if (event.key.shift && event.key.control)
        {
            if (shade_map>=1) {
                if (combine)
                    pictures_to_ffmpegfile_3();
                else
                    pictures_to_ffmpegfile_4();
            }
            else
                pictures_to_ffmpegfile();
            break;
        }
        if (event.key.alt)
        {
            if (shade_map==0)
                shade_map=1;
            else if (shade_map==1)
                shade_map=2;
            else
                shade_map=0;
//extern int reload_init();
            if (shade_map>=1)
            {
                reload_init();
                int pixels_in_map;
                int tiles_in_map;
                int ret=read_mazeoff(1);
                if (ret==0)
                {
                    pacman_to_rel_pos();
                    // no file, calculate them.
                    pixels_in_map=256*(int)pow(2.0,(SAS_ZOOM));
                    tiles_in_map=(int)pow(2.0,(SAS_ZOOM));
                    if (pixels_in_map<=maxpixelsx)
                    {
                        SAS_STARTX=0;
                    }
                    else
                    {
                        SAS_STARTX=(-maxpixelsx/2+(int)(rel_pos_in_map_x*(double)pixels_in_map)-1920/2)/256;
                        if (SAS_STARTX<0)
                            SAS_STARTX=0;
                    }
                    if (pixels_in_map<=maxpixelsy)
                    {
                        SAS_STARTY=0;
                    }
                    else
                    {
                        SAS_STARTY=(-maxpixelsy/2+(int)(rel_pos_in_map_y*(double)pixels_in_map)-1080/2)/256;
                        if (SAS_STARTY<0)
                            SAS_STARTY=0;
                    }

                    SAS_STARTX_a=SAS_STARTX*256-(int)((float)(SAS_STARTX*256)/1920.0)*1920;
                    SAS_STARTY_a=SAS_STARTY*256-(int)((float)(SAS_STARTY*256)/1080.0)*1080;

                    printf("CALCULATED NEW:\n");
                    printf("RELATIVE: x=%f , y=%f\n",rel_pos_in_map_x,rel_pos_in_map_y);
                    printf("TILES: %d , PIXELS: %d\n",tiles_in_map,pixels_in_map);
                    printf("SAS:   x=%8d , y=%8d , zoom=%d\n",SAS_STARTX,SAS_STARTY,SAS_ZOOM);
                    printf("ADAPT: x=%8d , y=%8d \n",(int)(SAS_STARTX_a/256),(int)(SAS_STARTY_a/256));
                    printf("REST:  x=%8d , y=%8d \n",SAS_STARTX_a,SAS_STARTY_a);
                    printf("X: tot=%d  /1920=%f\n",SAS_STARTX*256-SAS_STARTX_a,(float)(SAS_STARTX*256-SAS_STARTX_a)/1920.0);
                    printf("Y: tot=%d  /1080=%f\n",SAS_STARTY*256-SAS_STARTY_a,(float)(SAS_STARTY*256-SAS_STARTY_a)/1080.0);
                    printf("===========================\n");

                    /*
                                        SAS_STARTX=SAS_STARTX-SAS_STARTX_a/256;
                                        SAS_STARTY=SAS_STARTY-SAS_STARTY_a/256;
                                        SAS_STARTX_a=SAS_STARTX_a-(int)(SAS_STARTX_a/256)*256;
                                        SAS_STARTY_a=SAS_STARTY_a-(int)(SAS_STARTY_a/256)*256;

                                        printf("RECALCULATED NEW:\n");
                                        printf("SAS:   x=%8d , y=%8d , zoom=%d\n",SAS_STARTX,SAS_STARTY,SAS_ZOOM);
                                        printf("ADAPT: x=%8d , y=%8d \n" ,(int)(SAS_STARTX_a/256),(int)(SAS_STARTY_a/256));
                                        printf("REST:  x=%8d , y=%8d \n" ,SAS_STARTX_a,SAS_STARTY_a);
                                        printf("X: tot=%d  /1920=%f\n",SAS_STARTX*256-SAS_STARTX_a,(float)(SAS_STARTX*256-SAS_STARTX_a)/1920.0);
                                        printf("Y: tot=%d  /1080=%f\n",SAS_STARTY*256-SAS_STARTY_a,(float)(SAS_STARTY*256-SAS_STARTY_a)/1080.0);
                                        printf("===========================\n");
                    */
                    offset_picture_x=(int)((float)(SAS_STARTX*256+255)/1920.0);
                    offset_picture_y=(int)((float)(SAS_STARTY*256+255)/1080.0);

                    SAS_STARTX= (offset_picture_x*1920)/256;
                    SAS_STARTY= (offset_picture_y*1080)/256;

                    SAS_STARTX_a=offset_picture_x*1920-SAS_STARTX*256;
                    SAS_STARTY_a=offset_picture_y*1080-SAS_STARTY*256;

                    printf("RE-RECALCULATED NEW:\n");
                    printf("SAS:   x=%8d , y=%8d , zoom=%d\n",SAS_STARTX,SAS_STARTY,SAS_ZOOM);
                    printf("ADAPT: x=%8d , y=%8d \n",(int)(SAS_STARTX_a/256),(int)(SAS_STARTY_a/256));
                    printf("REST:  x=%8d , y=%8d \n",SAS_STARTX_a,SAS_STARTY_a);
//                    printf("X: tot=%d  /1920=%f\n",SAS_STARTX*256-SAS_STARTX_a,(float)(SAS_STARTX*256-SAS_STARTX_a)/1920.0);
//                    printf("Y: tot=%d  /1080=%f\n",SAS_STARTY*256-SAS_STARTY_a,(float)(SAS_STARTY*256-SAS_STARTY_a)/1080.0);
                    printf("X: tot=%d  /1920=%f offset=%d\n",SAS_STARTX*256+SAS_STARTX_a,(float)(SAS_STARTX*256+SAS_STARTX_a)/1920.0,offset_picture_x);
                    printf("Y: tot=%d  /1080=%f offset=%d\n",SAS_STARTY*256+SAS_STARTY_a,(float)(SAS_STARTY*256+SAS_STARTY_a)/1080.0,offset_picture_y);
                    printf("===========================\n");


                    Fget_map_x=(double)SAS_STARTX+(double)SAS_STARTX_a/256.0;
                    Fget_map_y=(double)SAS_STARTY+(double)SAS_STARTY_a/256.0;
                    get_map_x=SAS_STARTX;
                    get_map_y=SAS_STARTY;
                    get_map_zoom=SAS_ZOOM;
                    // and save them under current new level.
                    if (SAS_STARTX!=0 || SAS_STARTY!=0)
                    {
                        strcpy(error_msg4,"MAP DON'T FIT IN SCREEN, ADAPTING STARTX,STARTY!!!!!!! SAVING REL.OFFSET TO MAZEOFF.DAT");
                        error_flag4=1;
                        strcpy(error_msg3,"DELETE OR CHANGE FILE FOR OTHER SUB SCREENS OF OTHER PARTS OF MAP...!!!!!");
                        error_flag3=1;
                    }
//                    save_mazeoff();

                }
                else
                {
                    if (SAS_STARTX!=0 || SAS_STARTY!=0)
                    {
                        strcpy(error_msg4,"MAP DON'T FIT IN SCREEN, ADAPTED STARTX,STARTY!!!!!!! POSITIONS IN MAZEOFF.DAT");
                        error_flag4=1;
                        strcpy(error_msg3,"DELETE OR CHANGE FILE FOR OTHER SUB SCREENS OF OTHER PARTS OF MAP...!!!!!");
                        error_flag3=1;
                    }
                    else
                    {
                        strcpy(error_msg3,"MAP FITS IN SCREEN. NEW POSITION SAVED TO MAZEOFF.DAT. DELETE OR CHANGE FOR OTHER VALUES!!!!");
                        error_flag3=1;
                    }

                    SAS_STARTX_a=SAS_STARTX*256-(int)((float)(SAS_STARTX*256)/1920.0)*1920;
                    SAS_STARTY_a=SAS_STARTY*256-(int)((float)(SAS_STARTY*256)/1080.0)*1080;

                    printf("LOADED:\n");
                    printf("SAS:   x=%8d , y=%8d , zoom=%d\n",SAS_STARTX,SAS_STARTY,SAS_ZOOM);
                    printf("ADAPT: x=%8d , y=%8d \n",(int)(SAS_STARTX_a/256),(int)(SAS_STARTY_a/256));
                    printf("REST:  x=%8d , y=%8d \n",SAS_STARTX_a,SAS_STARTY_a);
                    printf("X: tot=%d  /1920=%f\n",SAS_STARTX*256-SAS_STARTX_a,(float)(SAS_STARTX*256-SAS_STARTX_a)/1920.0);
                    printf("Y: tot=%d  /1080=%f\n",SAS_STARTY*256-SAS_STARTY_a,(float)(SAS_STARTY*256-SAS_STARTY_a)/1080.0);
                    printf("===========================\n");

                    /*
                                        SAS_STARTX=SAS_STARTX-SAS_STARTX_a/256;
                                        SAS_STARTY=SAS_STARTY-SAS_STARTY_a/256;
                                        SAS_STARTX_a=SAS_STARTX_a-(int)(SAS_STARTX_a/256)*256;
                                        SAS_STARTY_a=SAS_STARTY_a-(int)(SAS_STARTY_a/256)*256;

                                        printf("RECALCULATED NEW:\n");
                                        printf("SAS:   x=%8d , y=%8d , zoom=%d\n",SAS_STARTX,SAS_STARTY,SAS_ZOOM);
                                        printf("ADAPT: x=%8d , y=%8d \n" ,(int)(SAS_STARTX_a/256),(int)(SAS_STARTY_a/256));
                                        printf("REST:  x=%8d , y=%8d \n" ,SAS_STARTX_a,SAS_STARTY_a);
                                        printf("X: tot=%d  /1920=%f\n",SAS_STARTX*256-SAS_STARTX_a,(float)(SAS_STARTX*256-SAS_STARTX_a)/1920.0);
                                        printf("Y: tot=%d  /1080=%f\n",SAS_STARTY*256-SAS_STARTY_a,(float)(SAS_STARTY*256-SAS_STARTY_a)/1080.0);
                                        printf("===========================\n");
                    */

                    offset_picture_x=(int)((float)(SAS_STARTX*256+255)/1920.0);
                    offset_picture_y=(int)((float)(SAS_STARTY*256+255)/1080.0);

                    SAS_STARTX= (offset_picture_x*1920)/256;
                    SAS_STARTY= (offset_picture_y*1080)/256;

                    SAS_STARTX_a=offset_picture_x*1920-SAS_STARTX*256;
                    SAS_STARTY_a=offset_picture_y*1080-SAS_STARTY*256;

                    printf("RE-RECALCULATED NEW:\n");
                    printf("SAS:   x=%8d , y=%8d , zoom=%d\n",SAS_STARTX,SAS_STARTY,SAS_ZOOM);
                    printf("ADAPT: x=%8d , y=%8d \n",(int)(SAS_STARTX_a/256),(int)(SAS_STARTY_a/256));
                    printf("REST:  x=%8d , y=%8d \n",SAS_STARTX_a,SAS_STARTY_a);
//                    printf("X: tot=%d  /1920=%f\n",SAS_STARTX*256-SAS_STARTX_a,(float)(SAS_STARTX*256-SAS_STARTX_a)/1920.0);
//                    printf("Y: tot=%d  /1080=%f\n",SAS_STARTY*256-SAS_STARTY_a,(float)(SAS_STARTY*256-SAS_STARTY_a)/1080.0);
                    printf("X: tot=%d  /1920=%f offset=%d\n",SAS_STARTX*256+SAS_STARTX_a,(float)(SAS_STARTX*256+SAS_STARTX_a)/1920.0,offset_picture_x);
                    printf("Y: tot=%d  /1080=%f offset=%d\n",SAS_STARTY*256+SAS_STARTY_a,(float)(SAS_STARTY*256+SAS_STARTY_a)/1080.0,offset_picture_y);
                    printf("===========================\n");


                    Fget_map_x=(double)SAS_STARTX+(double)SAS_STARTX_a/256.0;
                    Fget_map_y=(double)SAS_STARTY+(double)SAS_STARTY_a/256.0;
                    get_map_x=SAS_STARTX;
                    get_map_y=SAS_STARTY;
                    get_map_zoom=SAS_ZOOM;
                    pacman_to_rel_pos();
//                    save_mazeoff();
                }
            }
            break;
        }
        if (event.key.control)
        {
            if (shade_map>=1)
            {
                if (show_shade_map==0)
                    show_shade_map=1;
                else
                    show_shade_map=0;
            }
        }
        if (event.key.shift)
        {
            if (drawmazes==1)
            {
                strcpy(error_msg,"DRAWMAZES=ON, NOT IMPLEMENTED. (YET)");
                error_flag=1;
                break;
            }
            else
            {
                kill1=0;
                kill2=0;
                kill3=0;
//                printf("Calling putinmazeSFML_all()\n");

                if (shade_map>=1)
                {
                    texture_from_internet.create(256,256);
                    add_border(&texture_from_internet);
                    sprite_from_internet.setTextureRect( { 0,0,(int)texture_from_internet.getSize().x, (int)texture_from_internet.getSize().y } );
                    putinmazeSFML_all_xtheny();
//                    putinmazeSFML_all();
                }
                else {
                    if (formula==1 && shade_map==0) {
                        int got_it=0;
                        for (int i=0; i<10; i++) {
                            if (is_activated_window[i]==1) {
                                got_it++;
                                if (got_it==2) break;
                            }
                        }
                        if (got_it==0) {
                            printf("No 3d system running\n");
                            break;
                        } else if (got_it>1) {
                            printf("Only 1 3d system can be used, more than 1 running...\n");
                            break;
                        } else {
                            request_3d_x=-1;
                            request_3d_y=-1;

                            printf("Hang on...\n");
                        }
                    }
                    putinmazeSFML_all_xtheny();
                }

                kill1=0;
                kill2=0;
                kill3=0;
                break;
            }
        }
        if (connected==1 && playerleft==0)
        {
            SEND((char*)"T=INVITE,");
        }
        break;
    case sf::Keyboard::F7:
        if (event.key.shift)
        {
            combine_front_to_back();
            cleanupbitmaps_mazes();
            CLEANBITMAPS();
            ReadBitmaps2();
            ReadBitmaps4();
            break;
        }
        if (plot_front==1)
        {
            plot_front=0;
            plot_back=1;
        }
        else
        {
            plot_front=1;
            plot_back=0;
        }
        break;
    case sf::Keyboard::F8:
        if (event.key.control)
        {
            if (f8_repeat==0)
                f8_repeat=1;
            else
                f8_repeat=0;
            break;
        }
        old_shift=0;
        if (event.key.shift)
        {
            if (ffmpegfile==1 && plot_shader==0)
            {
                strcpy(error_msg,"NO PICTURE FROM SHIFT-P");
                error_flag=1;
                break;
            }
            old_shift=1;
        }
        if (event.key.alt)
        {
            if (ffmpegfile==1 && internetfile==1)
            {
                strcpy(error_msg,"NO PICTURE(S) TO SAVE FROM SHIFT-I AND/OR SHIFT-P");
                error_flag=1;
            }
            else
            {
                strcpy(error_msg,"SAVED: ");
                error_flag=1;
                int timenow= time(0);
                if (ffmpegfile==0)
                {
//                    sprintf(line,"pictures/%d-p.png",timenow);
                    sprintf(line,"%s/%d-p.png",PICTUREDIR,timenow);
                    texture_from_ffmpeg.copyToImage().saveToFile(line);
                    strcat(error_msg,line);
                    strcat(error_msg," ");
                }
                if (internetfile==0)
                {
//                    sprintf(line,"pictures/%d-i.png",timenow);
                    sprintf(line,"%s/%d-i.png",PICTUREDIR,timenow);
                    texture_from_internet.copyToImage().saveToFile(line);
                    strcat(error_msg,line);
                }
            }
            break;
        }
//        if (event.key.control) old_shift=1;
//ohoh
        /*

                if (old_shift==0) {
                    SFMLView1.setVerticalSyncEnabled(false);
                    reload=0;
                    old_draw=drawmazes;
                    if (loadbackground==0)
                    {
                        loadbackground=1;
                        CLEANBITMAPS();
        //                cleanupbitmaps_mazes();
                        reload=1;
                    }
                    if (drawmazes==1)
                    {
                        drawmazes=0;
                        strcpy(error_msg,"DRAW MAZES=OFF  BITMAPS RELOADED  SAVEFILES=0N");
                        error_flag=1;
                        reload=1;
                    }
                    if (reload==1)
                    {
                        LOADALLBITMAPS();
                        ReadBitmaps2();
                        ReadBitmaps4();
                    }
                }
        */
        start_posx_mem=(picturex*1920-posx);
        start_posy_mem=(picturey*1080-posy);

        render_picturex_mem=render_picturex;
        render_picturey_mem=render_picturey;
        render_posx_mem=render_posx;
        render_posy_mem=render_posy;

        picturex_mem=picturex;
        picturey_mem=picturey;
        posx_mem=posx;
        posy_mem=posy;

        if ((event.key.shift || old_shift==1))
        {
            if (ffmpegfile==0)
            {
                if (ffmpeg_move==1)
                {
                    start_posx=ffmpeg_posx-1920/2+(int)texture_from_ffmpeg.getSize().x/2;
                    start_posy=ffmpeg_posy-1080/2+(int)texture_from_ffmpeg.getSize().y/2;

                    if ((start_posx)>=maxpixelsx)
                        start_posx=start_posx-maxpixelsx;
                    else if ((start_posx)<0)
                        start_posx=start_posx+maxpixelsx;
                    if ((start_posy)>=maxpixelsy)
                        start_posy=start_posy-maxpixelsy;
                    else if ((start_posy)<0)
                        start_posy=start_posy+maxpixelsy;

                    home_map();
                    render_picturex=picturex;
                    render_posx=posx;
                    render_picturey=picturey;
                    render_posy=posy;
                }
                if (plot_shader==1)
                {
                    texture_from_ffmpeg.create(1920*4,1080*4);
                    sprite_from_ffmpeg.setTexture(texture_from_ffmpeg,true);
                    sprite_from_ffmpeg.setRotation(0.0);
                    sprite_from_ffmpeg.setScale(BITMAPSX/4.0,BITMAPSY/4.0);
                    scale_now=BITMAPSX;
                    sprite_from_ffmpeg.setPosition(0.0,0.0);
                    sprite_from_ffmpeg.setOrigin(sf::Vector2f(0.0,0.0));
                    rotate_ffmpeg=0;
                    rot_speed_ffmpeg=0;
                    rotation_ffmpeg=0;
                    size_ffmpeg=0;
                    render_picturex=(maxpixelsx-1920)/2/1920;
                    render_posx=(int)(maxpixelsx-1920)/2-1920*render_picturex;
                    render_posx=-render_posx;
                    render_picturey=(maxpixelsy-1080)/2/1080;
                    render_posy=(int)(maxpixelsy-1080)/2-1080*render_picturey;
                    render_posy=-render_posy;
                    get_ffmpegfile();
                }
                else
                {
                    get_ffmpegfile();
                }
            }
        }
        else
        {
            if (movie2==0 && live_movie2_is_mp3==0 && handler[MOVIE2_SELECT].show==1 && selector==MOVIE2_SELECT)
            {
                //                rot_speed_movie2=0.0;
                if (movie2_move==1)
                {
                    start_posx=movie2_posx-1920/2+(int)texture_from_movie2_new.getSize().x/2;
                    start_posy=movie2_posy-1080/2+(int)texture_from_movie2_new.getSize().y/2;

                    if ((start_posx)>=maxpixelsx)
                        start_posx=start_posx-maxpixelsx;
                    else if ((start_posx)<0)
                        start_posx=start_posx+maxpixelsx;
                    if ((start_posy)>=maxpixelsy)
                        start_posy=start_posy-maxpixelsy;
                    else if ((start_posy)<0)
                        start_posy=start_posy+maxpixelsy;

                    home_map();
                    render_picturex=picturex;
                    render_posx=posx;
                    render_picturey=picturey;
                    render_posy=posy;
                }
                plot_moviefile2=1;
                plotplot();
            }

            if (ffmpegfile==0 && handler[FFMPEG_SELECT].show==1 && selector==FFMPEG_SELECT)
            {
                if (ffmpeg_move==1)
                {
                    start_posx=ffmpeg_posx-1920/2+(int)texture_from_ffmpeg.getSize().x/2;
                    start_posy=ffmpeg_posy-1080/2+(int)texture_from_ffmpeg.getSize().y/2;

                    if ((start_posx)>=maxpixelsx)
                        start_posx=start_posx-maxpixelsx;
                    else if ((start_posx)<0)
                        start_posx=start_posx+maxpixelsx;
                    if ((start_posy)>=maxpixelsy)
                        start_posy=start_posy-maxpixelsy;
                    else if ((start_posy)<0)
                        start_posy=start_posy+maxpixelsy;

                    home_map();
                    render_picturex=picturex;
                    render_posx=posx;
                    render_picturey=picturey;
                    render_posy=posy;
                }
                plot_ffmpegfile=1;
                plotplot();
            }

            if (internetfile==0 && handler[INTERNET_SELECT].show==1 && selector==INTERNET_SELECT)
            {
                //                rot_speed_internet=0.0;
                if (internet_move==1)
                {
                    start_posx=internet_posx-1920/2+(int)texture_from_internet.getSize().x/2;
                    start_posy=internet_posy-1080/2+(int)texture_from_internet.getSize().y/2;

                    if ((start_posx)>=maxpixelsx)
                        start_posx=start_posx-maxpixelsx;
                    else if ((start_posx)<0)
                        start_posx=start_posx+maxpixelsx;
                    if ((start_posy)>=maxpixelsy)
                        start_posy=start_posy-maxpixelsy;
                    else if ((start_posy)<0)
                        start_posy=start_posy+maxpixelsy;

                    home_map();
                    render_picturex=picturex;
                    render_posx=posx;
                    render_picturey=picturey;
                    render_posy=posy;
                }
                plot_internetfile=1;
                plotplot();
            }

            if (movie==0 && live_movie_is_mp3==0 && handler[MOVIE_SELECT].show==1 && selector==MOVIE_SELECT)
            {
                if (movie_move==1)
                {
                    start_posx=movie_posx-1920/2+(int)texture_from_movie_new.getSize().x/2;
                    start_posy=movie_posy-1080/2+(int)texture_from_movie_new.getSize().y/2;;

                    if ((start_posx)>=maxpixelsx)
                        start_posx=start_posx-maxpixelsx;
                    else if ((start_posx)<0)
                        start_posx=start_posx+maxpixelsx;
                    if ((start_posy)>=maxpixelsy)
                        start_posy=start_posy-maxpixelsy;
                    else if ((start_posy)<0)
                        start_posy=start_posy+maxpixelsy;

                    home_map();
                    render_picturex=picturex;
                    render_posx=posx;
                    render_picturey=picturey;
                    render_posy=posy;
                }
                plot_moviefile=1;
                plotplot();
            }
        }

        start_posx=start_posx_mem;
        start_posy=start_posy_mem;

        render_picturex=render_picturex_mem;
        render_picturey=render_picturey_mem;
        render_posx=render_posx_mem;
        render_posy=render_posy_mem;

//        picturex=picturex_mem;
//        picturey=picturey_mem;
//        posx=posx_mem;
//        posy=posy_mem;

//ohoh
        /*
                if (old_shift==0) {
                    if (old_draw==1)
                    {
                        if (totalchanged>0)
                        {
                            DONTSAVEFILES=0;
                            SAVEALLBITMAPS();
                            strcpy(error_msg,"BITMAPS CHANGED!!! SAVING FIRST BEFORE DRAW MAZE!!!");
                            error_flag=1;
                        }
                        else
                        {
                            strcpy(error_msg,"DRAW MAZE=ON");
                            error_flag=1;
                        }
                        drawmazes=1;
                        DRAWALLMAZES();
                        pen=1;
                        pen_mode=2;
                    }
                }
        */
        if (sync==1)
            SFMLView1.setVerticalSyncEnabled(true);
        else
            SFMLView1.setVerticalSyncEnabled(false);
        break;
    case sf::Keyboard::F9:
        if (event.key.shift)
        {
            if (cool==0)
                thread_run_sub=1;
            else
                cool=0;
//            shaders();
            break;
        }
        if (event.key.control)
        {
            pacman_to_rel_pos();
            rel_pos_in_map_x1=rel_pos_in_map_x;
            rel_pos_in_map_y1=rel_pos_in_map_y;
            savevalue_float("REL_POS_IN_MAP_X1.TXT",rel_pos_in_map_x1);
            savevalue_float("REL_POS_IN_MAP_Y1.TXT",rel_pos_in_map_y1);
            if (FILE * file = fopen("locations1.txt", "a"))
            {
                fprintf(file,"X=%29.28lf Y=%29.28lf\n",rel_pos_in_map_x,rel_pos_in_map_y);
                fclose(file);
            }
            break;
        }
        if (event.key.alt)
        {
            next_loc();
//            text_to_ffmpeg(going_to,36, sf::Color(255,255,255,255) , sf::Color(0,0,0,255));
            rel_pos_in_map_x=rel_pos_in_map_x2;
            rel_pos_in_map_y=rel_pos_in_map_y2;
            savevalue_float("REL_POS_IN_MAP_X2.TXT",rel_pos_in_map_x2);
            savevalue_float("REL_POS_IN_MAP_Y2.TXT",rel_pos_in_map_y2);
            strcpy(error_msg3,"STORED UNDER CONTROL-F12");
            error_flag3=1;
            rel_pos_to_pacman();
            break;
        }
        set_position1();
        break;
    case sf::Keyboard::F10:
        if (event.key.alt) {
            voxel_to_file=!voxel_to_file;
            break;
        } else if (event.key.shift) {
            plot_only=!plot_only;
            break;
        } else if (event.key.control) {
            rel_pos_in_map_x1=loadvalue_float("REL_POS_IN_MAP_X1.TXT");
            rel_pos_in_map_y1=loadvalue_float("REL_POS_IN_MAP_Y1.TXT");
            rel_pos_in_map_x=rel_pos_in_map_x1;
            rel_pos_in_map_y=rel_pos_in_map_y1;
            rel_pos_to_pacman();
            break;
        }
        get_position1();
        break;
    case sf::Keyboard::F11:
        if (event.key.alt)
        {
            do_command(MACRO1);
            break;
        }
        if (event.key.shift)
        {
            do_command(MACRO2);
            break;
        }
        if (event.key.control)
        {
            pacman_to_rel_pos();
            rel_pos_in_map_x2=rel_pos_in_map_x;
            rel_pos_in_map_y2=rel_pos_in_map_y;
            savevalue_float("REL_POS_IN_MAP_X2.TXT",rel_pos_in_map_x2);
            savevalue_float("REL_POS_IN_MAP_Y2.TXT",rel_pos_in_map_y2);
            if (FILE * file = fopen("locations2.txt", "a"))
            {
                fprintf(file,"X=%29.28lf Y=%29.28lf\n",rel_pos_in_map_x,rel_pos_in_map_y);
                fclose(file);
            }
            break;
        }
        set_position2();
        break;
    case sf::Keyboard::F12:
        if (event.key.alt)
        {
            if (shade_map>=1 && drawmazes==0 && formula==1)
            {
                loadallmaps_level=1;
            }
            break;
        }
        if (event.key.shift)
        {
            if (shade_map>=1 && drawmazes==0 && formula==1)
            {
                loadallmaps=1;
            }
            break;
        }
        if (event.key.control)
        {
            rel_pos_in_map_x2=loadvalue_float("REL_POS_IN_MAP_X2.TXT");
            rel_pos_in_map_y2=loadvalue_float("REL_POS_IN_MAP_Y2.TXT");
            rel_pos_in_map_x=rel_pos_in_map_x2;
            rel_pos_in_map_y=rel_pos_in_map_y2;
            rel_pos_to_pacman();
            break;
        }
        get_position2();
        break;
    case sf::Keyboard::LBracket:
        if (event.key.shift)
        {
            if (follow_ghost==1 || flippo==1)
            {
                if (event.key.control) {
                    fspeed_ghostx[follow_ghost_num]=fspeed_ghostx[follow_ghost_num]*0.995;
                    fspeed_ghosty[follow_ghost_num]=fspeed_ghosty[follow_ghost_num]*0.995;
                } else {
                    fspeed_ghostx[follow_ghost_num]=fspeed_ghostx[follow_ghost_num]*0.9;
                    fspeed_ghosty[follow_ghost_num]=fspeed_ghosty[follow_ghost_num]*0.9;
                }
                if (fabs(fspeed_ghostx[follow_ghost_num])>25.0) {
                    fspeed_ghostx[follow_ghost_num]=round(fspeed_ghostx[follow_ghost_num]);
                    fpos_ghostx[follow_ghost_num]=round(fpos_ghostx[follow_ghost_num]);
                    fpos_ghosty[follow_ghost_num]=round(fpos_ghosty[follow_ghost_num]);
                }
            }
        }
        else if (event.key.alt)
        {
            fspeed_ghost_all=0.9;
        }
        else if (event.key.system) {

//            if (level>0) level--;
            if (plot_all) {
                int x,y;
                int render_x,render_y;
                sprite_from_canvas.setScale(sprite_from_canvas.getScale().x*10,sprite_from_canvas.getScale().y*10.0);
                if (follow_ghost==1)
                {
                    x=(-pos_ghostx[follow_ghost_num]+1920+1920/2+maxpixelsx)%maxpixelsx;
                    y=(-pos_ghosty[follow_ghost_num]+1080+1080/2+maxpixelsy)%maxpixelsy;
                }
                else
                {

                    x=(picturex*1920-posx+1920/2)%maxpixelsx;
                    y=(picturey*1080-posy+1080/2)%maxpixelsy;
                }
                render_x=(render_picturex*1920-render_posx+1920/2)%maxpixelsx;
                render_y=(render_picturey*1080-render_posy+1080/2)%maxpixelsy;

                x=x/10;
                y=y/10;
                render_x=render_x/10;
                render_y=render_y/10;

                x=x-1920/2;
                y=y-1080/2;

                render_x=render_x-1920/2;
                render_y=render_y-1080/2;

                x=(maxpixelsx+x)%maxpixelsx;
                if (x<0)
                    x=0;
                y=(maxpixelsy+y)%maxpixelsy;
                if (y<0)
                    y=0;

                render_x=(maxpixelsx+render_x)%maxpixelsx;
                if (render_x<0)
                    render_x=0;
                render_y=(maxpixelsy+render_y)%maxpixelsy;
                if (render_y<0)
                    render_y=0;

                smooth_x=(double)render_x;
                smooth_y=(double)render_y;

                picturex=x/1920;
                posx=x-1920*picturex;
                picturey=y/1080;
                posy=y-1080*picturey;
                posx=-posx;
                posy=-posy;
                fposx=posx;
                fposy=posy;

                render_picturex=render_x/1920;
                render_posx=render_x-1920*render_picturex;
                render_picturey=render_y/1080;
                render_posy=render_y-1080*render_picturey;
                render_posx=-render_posx;
                render_posy=-render_posy;

                if (follow_ghost==1)
                {
                    posx=posx-posx%64-32;
                    if (posx<=-1920)
                    {
                        posx=posx+1920;
//                        picturex=(picturex-1+totalpicturex)%totalpicturex;
                    }
                    posy=posy-(posy-36)%72-36;
                    if (posy<=-1080)
                    {
                        posy=posy+1080;
//                        picturey=(picturey-1+totalpicturey)%totalpicturey;
                    }
                    fposx=posx;
                    fposy=posy;
                    ReadBitmaps2();
//                    render_posx=posx;
//                    render_posy=posy;
//                    render_picturex=picturex;
//                    render_picturey=picturey;
//                    ReadBitmaps4();

                    int xx=(picturex*1920-posx)%maxpixelsx;
                    int yy=(picturey*1080-posy)%maxpixelsy;

                    fpos_ghostx[follow_ghost_num]=-xx+1920;
                    fpos_ghosty[follow_ghost_num]=-yy+1080;
                    pos_ghostx[follow_ghost_num]=fpos_ghostx[follow_ghost_num];
                    pos_ghosty[follow_ghost_num]=fpos_ghosty[follow_ghost_num];
                    smooth_x=(double)xx;
                    smooth_y=(double)yy;
                }
                forced_jump=1;


            }
            reload_init();

        }


        break;
    case sf::Keyboard::RBracket:
        if (event.key.shift)
        {
            if (follow_ghost==1 || flippo==1)
            {
                if (event.key.control) {
                    fspeed_ghostx[follow_ghost_num]=fspeed_ghostx[follow_ghost_num]*1.005;
                    fspeed_ghosty[follow_ghost_num]=fspeed_ghosty[follow_ghost_num]*1.005;
                } else {
                    fspeed_ghostx[follow_ghost_num]=fspeed_ghostx[follow_ghost_num]*1.1;
                    fspeed_ghosty[follow_ghost_num]=fspeed_ghosty[follow_ghost_num]*1.1;
                }
                if (fabs(fspeed_ghosty[follow_ghost_num])>25.0) {
                    fspeed_ghosty[follow_ghost_num]=round(fspeed_ghosty[follow_ghost_num]);
                    fpos_ghostx[follow_ghost_num]=round(fpos_ghostx[follow_ghost_num]);
                    fpos_ghosty[follow_ghost_num]=round(fpos_ghosty[follow_ghost_num]);
                }
            }
        }
        else if (event.key.alt)
        {
            fspeed_ghost_all=1.1;
        }
        else if (event.key.system) {

//            level++;
            if (plot_all) {
                int x,y;
                int render_x,render_y;
                sprite_from_canvas.setScale(sprite_from_canvas.getScale().x/10,sprite_from_canvas.getScale().y/10.0);
                if (follow_ghost==1)
                {
                    x=(-pos_ghostx[follow_ghost_num]+1920+1920/2+maxpixelsx)%maxpixelsx;
                    y=(-pos_ghosty[follow_ghost_num]+1080+1080/2+maxpixelsy)%maxpixelsy;
                }
                else
                {

                    x=(picturex*1920-posx+1920/2)%maxpixelsx;
                    y=(picturey*1080-posy+1080/2)%maxpixelsy;
                }
                render_x=(render_picturex*1920-render_posx+1920/2)%maxpixelsx;
                render_y=(render_picturey*1080-render_posy+1080/2)%maxpixelsy;

                x=x*10;
                y=y*10;
                render_x=render_x*10;
                render_y=render_y*10;

                x=x-1920/2;
                y=y-1080/2;

                render_x=render_x-1920/2;
                render_y=render_y-1080/2;

                x=(maxpixelsx+x)%maxpixelsx;
                if (x<0)
                    x=0;
                y=(maxpixelsy+y)%maxpixelsy;
                if (y<0)
                    y=0;

                render_x=(maxpixelsx+render_x)%maxpixelsx;
                if (render_x<0)
                    render_x=0;
                render_y=(maxpixelsy+render_y)%maxpixelsy;
                if (render_y<0)
                    render_y=0;

                smooth_x=(double)render_x;
                smooth_y=(double)render_y;

                picturex=x/1920;
                posx=x-1920*picturex;
                picturey=y/1080;
                posy=y-1080*picturey;
                posx=-posx;
                posy=-posy;
                fposx=posx;
                fposy=posy;

                render_picturex=render_x/1920;
                render_posx=render_x-1920*render_picturex;
                render_picturey=render_y/1080;
                render_posy=render_y-1080*render_picturey;
                render_posx=-render_posx;
                render_posy=-render_posy;

                if (follow_ghost==1)
                {
                    posx=posx-posx%64-32;
                    if (posx<=-1920)
                    {
                        posx=posx+1920;
//                        picturex=(picturex-1+totalpicturex)%totalpicturex;
                    }
                    posy=posy-(posy-36)%72-36;
                    if (posy<=-1080)
                    {
                        posy=posy+1080;
//                        picturey=(picturey-1+totalpicturey)%totalpicturey;
                    }
                    fposx=posx;
                    fposy=posy;
                    ReadBitmaps2();
//                    render_posx=posx;
//                    render_posy=posy;
//                    render_picturex=picturex;
//                    render_picturey=picturey;
//                    ReadBitmaps4();

                    int xx=(picturex*1920-posx)%maxpixelsx;
                    int yy=(picturey*1080-posy)%maxpixelsy;

                    fpos_ghostx[follow_ghost_num]=-xx+1920;
                    fpos_ghosty[follow_ghost_num]=-yy+1080;
                    pos_ghostx[follow_ghost_num]=fpos_ghostx[follow_ghost_num];
                    pos_ghosty[follow_ghost_num]=fpos_ghosty[follow_ghost_num];
                    smooth_x=(double)xx;
                    smooth_y=(double)yy;
                }
                forced_jump=1;


            }
            reload_init();

        }
        break;
    case sf::Keyboard::Add:
    case sf::Keyboard::Equal:
        if (event.key.alt)
        {
            plot_all_factor++;
            sprintf(error_msg2,"Total textures=%d",(8+plot_all_factor)*(8+plot_all_factor));
            error_flag2=1;
            break;
        }
        if (event.key.control)
        {
            fpstime_factor=fpstime_factor/0.99;
            break;
        }
/*
        if (blending==2)
        {
            if (MyBlendMode_num<4)
                MyBlendMode_num++;
            else
                MyBlendMode_num=0;
            set_blending();
            break;
        }
*/
        int i;
        int ghostx;
        int ghosty;
        int add;
        if (number<10)
            add=1;
        else if (number<50)
            add=2;
        else if (number<100)
            add=5;
        else if (number<500)
            add=10;
        else if (number<1000)
            add=50;
        else if (number<5000)
            add=100;
        else if (number<10000)
            add=500;
        else if (number<50000)
            add=1000;
        else if (number<100000)
            add=5000;
        else if (number<500000)
            add=10000;
        else
            add=50000;

        if (follow_ghost==0)
        {
            ghostx=posx-( ((picturex-1+(maxpicturex+1))%(maxpicturex+1)) *1920);
            ghosty=posy-( ((picturey-1+(maxpicturey+1))%(maxpicturey+1)) *1080);
        }
        else
        {
            ghostx=real_posx2;
            ghosty=real_posy2;
        }
        ghostx=(ghostx-ghostx%64-32)%(totalpicturex*1920);
        ghosty=(ghosty-(ghosty-36)%72-36)%(totalpicturey*1080);
        for (i=0; i<add; i++)
        {
            int addx=0,addy=0;
            if (number<=maxnumber)
            {
                if (number!=maxnumber)
                {
                    if (number%4==0)
                    {
                        fspeed_ghostx[number]=3.0+(rand()%601+1500)/(1000.0+(hunt>0)*1000.0);
//                        fspeed_ghostx[number]=3.0+(rand()%2101)/(1000.0+(hunt>0)*1000.0);
//                        fspeed_ghostx[number]=10.0+(rand()%8001)/(1000.0+(hunt>0)*1000.0);
//                        fspeed_ghostx[number]=1.0+floor(pow(number,0.1));
//                        fspeed_ghostx[number]=10.0123+floor(pow(number,0.1));
                        fspeed_ghosty[number]=0.0;
                        addx-=64;
                    }
                    else if (number%4==1)
                    {
                        fspeed_ghostx[number]=0.0;
//                        fspeed_ghosty[number]=-10.0123-floor(pow(number,0.1));
//                        fspeed_ghosty[number]=-1.0-floor(pow(number,0.1));
                        fspeed_ghosty[number]=-3.0-(rand()%601+1500)/(1000.0+(hunt>0)*1000.0);
//                        fspeed_ghosty[number]=-3.0-(rand()%2101)/(1000.0+(hunt>0)*1000.0);
//                        fspeed_ghosty[number]=-10.0-(rand()%8001)/(1000.0+(hunt>0)*1000.0);
                        addy+=72;
                    }
                    else if (number%4==2)
                    {
//                        fspeed_ghostx[number]=-10.0-(rand()%8001)/(1000.0+(hunt>0)*1000.0);
                        fspeed_ghostx[number]=-3.0-(rand()%601+1500)/(1000.0+(hunt>0)*1000.0);
//                        fspeed_ghostx[number]=-3.0-(rand()%2101)/(1000.0+(hunt>0)*1000.0);
//                        fspeed_ghostx[number]=-10.0123-floor(pow(number,0.1));
//                        fspeed_ghostx[number]=-1.0-floor(pow(number,0.1));
                        fspeed_ghosty[number]=0.0;
                        addx+=64;
                    }
                    else if (number%4==3)
                    {
                        fspeed_ghostx[number]=0.0;
//                        fspeed_ghosty[number]=10.0123+floor(pow(number,0.1));
//                        fspeed_ghosty[number]=1.0+floor(pow(number,0.1));
                        fspeed_ghosty[number]=3.0+(rand()%601+1500)/(1000.0+(hunt>0)*1000.0);
//                        fspeed_ghosty[number]=3.0+(rand()%2101)/(1000.0+(hunt>0)*1000.0);
//                        fspeed_ghosty[number]=10.0+(rand()%8001)/(1000.0+(hunt>0)*1000.0);
                        addy-=72;
                    }
                    fpos_ghostx[number]=ghostx+addx;
                    fpos_ghosty[number]=ghosty+addy;
                    pos_ghostx[number]=ghostx+addx;
                    pos_ghosty[number]=ghosty+addy;
                    check[number]=0;
                    if (number<maxnumber)
                        number++;
                }
            }
        }
        break;
    case sf::Keyboard::Subtract:
    case sf::Keyboard::Hyphen:
        if (event.key.alt)
        {
            plot_all_factor--;
            sprintf(error_msg3,"Total textures=%d",(8+plot_all_factor)*(8+plot_all_factor));
            error_flag3=1;
            break;
        }
        if (event.key.control)
        {
            fpstime_factor=fpstime_factor*0.99;
            break;
        }
/*
        if (blending==2)
        {
            if (MyBlendMode_num>0)
                MyBlendMode_num--;
            else
                MyBlendMode_num=4;
            set_blending();
            break;
        }
*/
        add=1;
        if (number>500000)
            add=50000;
        else if (number>100000)
            add=10000;
        else if (number>50000)
            add=5000;
        else if (number>10000)
            add=1000;
        else if (number>5000)
            add=500;
        else if (number>1000)
            add=100;
        else if (number>500)
            add=50;
        else if (number>100)
            add=10;
        else if (number>50)
            add=5;
        if (number>0)
            number=number-add;
        if (number<=0)
        {
            number=0;
            if (follow_ghost==1)
            {
                set_pacman();

                posx=posx-posx%64-32;
                if (posx<=-1920)
                {
                    posx=posx+1920;
                    picturex=(picturex+1+totalpicturex)%totalpicturex;
                }
                posy=posy-(posy-36)%72-36;
                if (posy<=-1080)
                {
                    posy=posy+1080;
                    picturey=(picturey+1+totalpicturey)%totalpicturey;
                }
                fposx=posx;
                fposy=posy;
                ReadBitmaps2();
                follow_ghost=0;
                long_jump=1;
                pen=old_pen;
                if (pen==1)
                    pen_mode=2;
                else
                    pen_mode=0;
            }
        }
        break;
    case sf::Keyboard::End:
        if (event.key.alt)
        {
            next_loc();
            DO_ZOOM_OUT=1;
            DO_ZOOM_IN=0;
            zoom_off=1;
            char ip[200];
            char page[4000];
            if (SAS_URL[0]>='0' && SAS_URL[0]<='9')
            {
                int dummy;
                if (toupper(SAS_URL[5])=='S')
                    sscanf(SAS_URL, "%dhttps://%199[^/]/%199[^\n]",&dummy, ip,page );
                else
                    sscanf(SAS_URL, "%dhttp://%199[^/]/%199[^\n]",&dummy, ip,page);
                strcpy(page,ip);
                sprintf(ip,"%s-%d",page,dummy);
            }
            else
            {
                if (toupper(SAS_URL[4])=='S')
                    sscanf(SAS_URL, "https://%199[^/]/%199[^\n]", ip,page );
                else
                    sscanf(SAS_URL, "http://%199[^/]/%199[^\n]", ip,page);
            }
            if (ip[0]=='l' && ip[1]=='o' && ip[2]=='c' && ip[3]=='a' && ip[4]=='l')
                generate_tiles=1;

            if (!generate_tiles)
            {
                mytotal1=sf::Vector2i((picturex  +maxpicturex)%maxpicturex,(picturey+1+maxpicturey)%maxpicturey);
                launch_background_loader_one();
                mytotal2=sf::Vector2i((picturex+1+maxpicturex)%maxpicturex,(picturey  +maxpicturey)%maxpicturey);
                launch_background_loader_two();
                mytotal3=sf::Vector2i((picturex+1+maxpicturex)%maxpicturex,(picturey+1+maxpicturey)%maxpicturey);
                launch_background_loader_three();
            }
            pacman=0;
            DONTSAVEFILES=1;
            ghost=0;
            pen=0;
            formula=1;
            pacman_to_rel_pos();
            rel_pos_in_map_x1=rel_pos_in_map_x;
            rel_pos_in_map_y1=rel_pos_in_map_y;
            break;
        }
        if (event.key.shift)
        {
            scale_jump=0.02880;
            break;
        }
        scale_jump=sprite_from_canvas.getScale().x;
        break;
    case sf::Keyboard::Home:
        if (event.key.control==1)
        {
            shift=1;
            home_map();
            break;
        }
        if (event.key.alt)
        {
            DO_ZOOM_IN=1;
            DO_ZOOM_OUT=0;
            break;
        }
        home_map();
        break;
    case sf::Keyboard::H:
        if (event.key.control==1)
        {
            if (yellow==0)
                yellow=1;
            else
                yellow=0;
            break;
        }
        break;
    case sf::Keyboard::Left:
        if (paper_select>0 && (event.key.alt || event.key.control || event.key.shift || event.key.system)) {
            if (move_clock.getElapsedTime()<sf::milliseconds(200)) {
                move_speed=move_speed*1.01;
                move_speed_int=(int)move_speed;
            } else {
                move_speed_int=1;
                move_speed=1.0;
            }
            move_clock.restart();
            if (event.key.control) {
                rectangle_paper_pos_x-=move_speed_int;
//                if (rectangle_paper_pos_x>=move_speed_int) rectangle_paper_pos_x-=move_speed_int;
            } else if (event.key.alt) {
                if (rectangle_paper_count_x>1) {
                    rectangle_paper_count_x--;
                }
            } else if (event.key.shift) {
                if (width_pixels>=move_speed_int*2) {
                    width_pixels=width_pixels-2*move_speed_int;
                    rectangle_paper.setSize(sf::Vector2f(width_pixels+overlap_pixels*2,height_pixels+overlap_pixels*2));
                    rectangle_paper_inner.setSize(sf::Vector2f(width_pixels,height_pixels));
                    rectangle_paper_outer.setSize(sf::Vector2f(width_pixels+overlap_pixels*2,height_pixels+overlap_pixels*2));
                    ppi_x=(int)(0.5+(float)width_pixels/((float)width_mm/25.4));
                }
            } else if (event.key.system) {

            }
            sprintf(error_msg2,"Position: X=%d,Y=%d  Size: X=%d,Y=%d  Count: X=%d,Y=%d",
                    rectangle_paper_pos_x,rectangle_paper_pos_y,(int)rectangle_paper.getSize().x,(int)rectangle_paper.getSize().y,rectangle_paper_count_x,rectangle_paper_count_y);
            error_flag2=1;

            sprintf(error_msg3,"Total Poster Size: X=%d,Y=%d Pixels => X=%f,Y=%f Centimeters on 300 ppi",
                    width_pixels*rectangle_paper_count_x,height_pixels*rectangle_paper_count_y,
                    (float)(width_pixels*rectangle_paper_count_x)*2.54/300.0,(float)(height_pixels*rectangle_paper_count_y)*2.54/300.0);
            error_flag3=1;

            sprintf(error_msg,"PAPERSIZE #%d: %s  WIDTH=%d, HEIGHT=%d, OVERLAP=%d (mm)  PPI: X=%d,Y=%d",paper_select,paper_name.c_str(),width_mm,height_mm,overlap_mm,ppi_x,ppi_y);
            error_flag=1;

/*
            printf("#%d %s\n",paper_select,paper_name.c_str());
            printf("Paper format:   width=%d,height=%d (mm)\n",width_mm,height_mm);
            printf("Picture format: width=%d,height=%d (mm) (overlap=%d)\n",width_mm+overlap_mm*2,height_mm+overlap_mm*2,overlap_mm);
            printf("Pixels: (picture  pixel width / 25.4 mm/inch) * 300 ppi=%d\n",width_pixels+overlap_pixels*2);
            printf("Pixels: (picture pixel height / 25.4 mm/inch) * 300 ppi=%d\n",height_pixels+overlap_pixels*2);
            printf("Total Poster Size: X=%d,Y=%d Pixels => X=%7.1f,Y=%7.1f Centimeters on 300 ppi\n", width_pixels*rectangle_paper_count_x,height_pixels*rectangle_paper_count_y, (float)(width_pixels*rectangle_paper_count_x)*2.54/300.0,(float)(height_pixels*rectangle_paper_count_y)*2.54/300.0);
            printf("-----------------------------------------------------------------\n");
            printf("Position: X=%d,Y=%d  Size: X=%d,Y=%d  Count: X=%d,Y=%d",rectangle_paper_pos_x,rectangle_paper_pos_y,(int)rectangle_paper.getSize().x,(int)rectangle_paper.getSize().y,rectangle_paper_count_x,rectangle_paper_count_y);
            printf("PAPERSIZE #%d: %s  WIDTH=%d, HEIGHT=%d, OVERLAP=%d (mm)  PPI: X=%d,Y=%d",paper_select,paper_name.c_str(),width_mm,height_mm,overlap_mm,ppi_x,ppi_y);
*/
            break;
        }
        if (event.key.alt)
        {
            selector_item--;
            if (selector_item<0)
                selector_item=4;
            break;
        }
        if (event.key.control)
        {
            fspeedx+=0.1;
            speedx=fspeedx;
//            fspeedx=fspeedx/1.1;
            fspeedx_new=fspeedx;
            speedx_new=fspeedx_new;
            maze_up=0;
            maze_down=0;
            maze_left=1;
            maze_right=0;
            maze_up_new=0;
            maze_down_new=0;
            maze_left_new=1;
            maze_right_new=0;
            pressed=1;
            break;
        }
        if (mouse_move==1)
            break;
        if (    ( (internetfile==0 && handler[INTERNET_SELECT].show==1) || (movie==0 ) || (ffmpegfile==0) || (pacman==0) )
                && pen==0 && force_game==0 || (pen==0 && (drawmazes==0 || pacman==0) ) )
//        if (    ( (internetfile==0 && internet_move==0) || (movie==0 && movie_move==0) || (ffmpegfile==0 && ffmpeg_move==0) )
//                && pen==0 && force_game==0 || (pen==0 && drawmazes==0 && (movie_move==0 || ffmpeg_move==0 || internet_move==0))  )
        {
            if (fspeedx!=0)
            {
                if (mirror==1) speedx+=100;
                else speedx=speedx+1;
                fspeedx=speedx;
                printf("x=%d,y=%d\r",speedx,speedy);
//                        speedy=0;
//                        fspeedy=0.0;
            }
            else
            {
                speedx=1;
                fspeedx=1.0;
                if (event.key.shift)
                {
                    one_pixel=1;
                }
            }
            speedx_new=speedx;
            speedy_new=0;
            fspeedx_new=speedx;
            fspeedy_new=0;
            maze_up=0;
            maze_down=0;
            maze_left=1;
            maze_right=0;
            maze_up_new=0;
            maze_down_new=0;
            maze_left_new=1;
            maze_right_new=0;
            pressed=1;
            break;
        } else printf("NOOOOOOOOOOOOOO\r");
        if (pen==1)
        {
            speedx=64;
            speedy=0;
            fspeedx=64;
            fspeedy=0;
            maze_left=1;
            maze_right=0;
            maze_up=0;
            maze_down=0;
        }
        else
        {
            pressed=1;
//crossing
            speedx_new=4;
            speedy_new=0;
            fspeedx_new=4;
            fspeedy_new=0;
            maze_left_new=1;
            maze_up_new=0;
            maze_down_new=0;
            maze_right_new=0;
        }
        break;
    case sf::Keyboard::Right:
        if (paper_select>0 && (event.key.alt || event.key.control || event.key.shift)) {
            if (move_clock.getElapsedTime()<sf::milliseconds(200)) {
                move_speed=move_speed*1.01;
                move_speed_int=(int)move_speed;
            } else {
                move_speed_int=1;
                move_speed=1.0;
            }
            move_clock.restart();
            if (event.key.control) {
                rectangle_paper_pos_x+=move_speed_int;
//                if (rectangle_paper_pos_x+rectangle_paper.getSize().x<maxpixelsx) rectangle_paper_pos_x+=move_speed_int;
            } else if (event.key.alt) {
                if (rectangle_paper_count_x*rectangle_paper.getSize().x+rectangle_paper_pos_x<maxpixelsx) {
                    rectangle_paper_count_x++;
                }
            } else if (event.key.shift) {
                if (rectangle_paper_count_x*(rectangle_paper_inner.getSize().x)+rectangle_paper_pos_x-2*move_speed_int<maxpixelsx) {
                    width_pixels=width_pixels+2*move_speed_int;
                    rectangle_paper.setSize(sf::Vector2f(width_pixels+overlap_pixels*2,height_pixels+overlap_pixels*2));
                    rectangle_paper_inner.setSize(sf::Vector2f(width_pixels,height_pixels));
                    rectangle_paper_outer.setSize(sf::Vector2f(width_pixels+overlap_pixels*2,height_pixels+overlap_pixels*2));
                    ppi_x=(int)(0.5+(float)width_pixels/((float)width_mm/25.4));
                }
            }
            sprintf(error_msg2,"Position: X=%d,Y=%d  Size: X=%d,Y=%d  Count: X=%d,Y=%d",
                    rectangle_paper_pos_x,rectangle_paper_pos_y,(int)rectangle_paper.getSize().x,(int)rectangle_paper.getSize().y,rectangle_paper_count_x,rectangle_paper_count_y);
            error_flag2=1;
            sprintf(error_msg3,"Total Poster Size: X=%d,Y=%d Pixels => X=%f,Y=%f Centimeters on 300 ppi",
                    width_pixels*rectangle_paper_count_x,height_pixels*rectangle_paper_count_y,
                    (float)(width_pixels*rectangle_paper_count_x)*2.54/300.0,(float)(height_pixels*rectangle_paper_count_y)*2.54/300.0);
            error_flag3=1;
            sprintf(error_msg,"PAPERSIZE #%d: %s  WIDTH=%d, HEIGHT=%d, OVERLAP=%d (mm)  PPI: X=%d,Y=%d",paper_select,paper_name.c_str(),width_mm,height_mm,overlap_mm,ppi_x,ppi_y);
            error_flag=1;
            /*
            printf("#%d %s\n",paper_select,paper_name.c_str());
            printf("Paper format:   width=%d,height=%d (mm)\n",width_mm,height_mm);
            printf("Picture format: width=%d,height=%d (mm) (overlap=%d)\n",width_mm+overlap_mm*2,height_mm+overlap_mm*2,overlap_mm);
            printf("Pixels: (picture  pixel width / 25.4 mm/inch) * 300 ppi=%d\n",width_pixels+overlap_pixels*2);
            printf("Pixels: (picture pixel height / 25.4 mm/inch) * 300 ppi=%d\n",height_pixels+overlap_pixels*2);
            printf("Total Poster Size: X=%d,Y=%d Pixels => X=%7.1f,Y=%7.1f Centimeters on 300 ppi\n", width_pixels*rectangle_paper_count_x,height_pixels*rectangle_paper_count_y, (float)(width_pixels*rectangle_paper_count_x)*2.54/300.0,(float)(height_pixels*rectangle_paper_count_y)*2.54/300.0);
            printf("-----------------------------------------------------------------\n");
            printf("Position: X=%d,Y=%d  Size: X=%d,Y=%d  Count: X=%d,Y=%d",rectangle_paper_pos_x,rectangle_paper_pos_y,(int)rectangle_paper.getSize().x,(int)rectangle_paper.getSize().y,rectangle_paper_count_x,rectangle_paper_count_y);
            printf("PAPERSIZE #%d: %s  WIDTH=%d, HEIGHT=%d, OVERLAP=%d (mm)  PPI: X=%d,Y=%d",paper_select,paper_name.c_str(),width_mm,height_mm,overlap_mm,ppi_x,ppi_y);
*/
            break;
        }
        if (event.key.alt)
        {
            selector_item++;
            if (selector_item==5)
                selector_item=0;
            break;
        }
        if (event.key.control)
        {
            fspeedx-=0.1;
            speedx=fspeedx;
//            fspeedx=fspeedx*1.1;
            fspeedx_new=fspeedx;
            speedx_new=speedx;
            maze_up=0;
            maze_down=0;
            maze_left=0;
            maze_right=1;
            maze_up_new=0;
            maze_down_new=0;
            maze_left_new=0;
            maze_right_new=1;
            pressed=1;
            break;
        }
        if (mouse_move==1)
            break;
        if (    ( (internetfile==0 && handler[INTERNET_SELECT].show==1) || (movie==0 ) || (ffmpegfile==0) || (pacman==0) )
                && pen==0 && force_game==0 || (pen==0 && (drawmazes==0 || pacman==0) ) )
//        if (    ( (internetfile==0 && internet_move==0) || (movie==0 && movie_move==0) || (ffmpegfile==0 && ffmpeg_move==0) )
//                && pen==0 && force_game==0 || (pen==0 && drawmazes==0 && (movie_move==0 || ffmpeg_move==0 || internet_move==0))  )
        {
            if (fspeedx!=0)
            {
                if (mirror==1) speedx-=100;
                else speedx=speedx-1;
                fspeedx=speedx;
                printf("x=%d,y=%d\r",speedx,speedy);
//                        speedy=0;
//                        fspeedy=0.0;
            }
            else
            {
                speedx=-1;
                fspeedx=-1.0;
                if (event.key.shift)
                {
                    one_pixel=1;
                }
            }
            speedx_new=speedx;
            speedy_new=0;
            fspeedx_new=speedx;
            fspeedy_new=0;
            maze_up=0;
            maze_down=0;
            maze_left=0;
            maze_right=1;
            maze_up_new=0;
            maze_down_new=0;
            maze_left_new=0;
            maze_right_new=1;
            pressed=1;
            break;
        } else printf("NOOOOOOOOOOOOOO\r");
        if (pen==1)
        {
            speedx=-64;
            speedy=0;
            fspeedx=-64;
            fspeedy=0;
            maze_right=1;
            maze_left=0;
            maze_up=0;
            maze_down=0;
        }
        else
        {
            pressed=1;
//crossing
            speedx_new=-4;
            speedy_new=0;
            fspeedx_new=-4;
            fspeedy_new=0;
            maze_right_new=1;
            maze_up_new=0;
            maze_down_new=0;
            maze_left_new=0;
        }
        break;
    case sf::Keyboard::Up:
        if (paper_select>0 && (event.key.alt || event.key.control || event.key.shift)) {
            if (move_clock.getElapsedTime()<sf::milliseconds(200)) {
                move_speed=move_speed*1.01;
                move_speed_int=(int)move_speed;
            } else {
                move_speed_int=1;
                move_speed=1.0;
            }
            move_clock.restart();
            if (event.key.control) {
                rectangle_paper_pos_y-=move_speed_int;
//                if (rectangle_paper_pos_y>move_speed_int-1) rectangle_paper_pos_y-=move_speed_int;
            } else if (event.key.alt) {
                if (rectangle_paper_count_y>1) {
                    rectangle_paper_count_y--;
                }
            } else if (event.key.shift) {
                if (height_pixels>=move_speed_int*2) {
                    height_pixels=height_pixels-2*move_speed_int;
                    rectangle_paper.setSize(sf::Vector2f(width_pixels+overlap_pixels*2,height_pixels+overlap_pixels*2));
                    rectangle_paper_inner.setSize(sf::Vector2f(width_pixels,height_pixels));
                    rectangle_paper_outer.setSize(sf::Vector2f(width_pixels+overlap_pixels*2,height_pixels+overlap_pixels*2));
                    ppi_y=(int)(0.5+(float)height_pixels/((float)height_mm/25.4));
                }
            }
            sprintf(error_msg2,"Position: X=%d,Y=%d  Size: X=%d,Y=%d  Count: X=%d,Y=%d",
                    rectangle_paper_pos_x,rectangle_paper_pos_y,(int)rectangle_paper.getSize().x,(int)rectangle_paper.getSize().y,rectangle_paper_count_x,rectangle_paper_count_y);
            error_flag2=1;
            sprintf(error_msg3,"Total Poster Size: X=%d,Y=%d Pixels => X=%f,Y=%f Centimeters on 300 ppi",
                    width_pixels*rectangle_paper_count_x,height_pixels*rectangle_paper_count_y,
                    (float)(width_pixels*rectangle_paper_count_x)*2.54/300.0,(float)(height_pixels*rectangle_paper_count_y)*2.54/300.0);
            error_flag3=1;
            sprintf(error_msg,"PAPERSIZE #%d: %s  WIDTH=%d, HEIGHT=%d, OVERLAP=%d (mm)  PPI: X=%d,Y=%d",paper_select,paper_name.c_str(),width_mm,height_mm,overlap_mm,ppi_x,ppi_y);
            error_flag=1;
/*
            printf("#%d %s\n",paper_select,paper_name.c_str());
            printf("Paper format:   width=%d,height=%d (mm)\n",width_mm,height_mm);
            printf("Picture format: width=%d,height=%d (mm) (overlap=%d)\n",width_mm+overlap_mm*2,height_mm+overlap_mm*2,overlap_mm);
            printf("Pixels: (picture  pixel width / 25.4 mm/inch) * 300 ppi=%d\n",width_pixels+overlap_pixels*2);
            printf("Pixels: (picture pixel height / 25.4 mm/inch) * 300 ppi=%d\n",height_pixels+overlap_pixels*2);
            printf("Total Poster Size: X=%d,Y=%d Pixels => X=%7.1f,Y=%7.1f Centimeters on 300 ppi\n", width_pixels*rectangle_paper_count_x,height_pixels*rectangle_paper_count_y, (float)(width_pixels*rectangle_paper_count_x)*2.54/300.0,(float)(height_pixels*rectangle_paper_count_y)*2.54/300.0);
            printf("-----------------------------------------------------------------\n");
            printf("Position: X=%d,Y=%d  Size: X=%d,Y=%d  Count: X=%d,Y=%d",rectangle_paper_pos_x,rectangle_paper_pos_y,(int)rectangle_paper.getSize().x,(int)rectangle_paper.getSize().y,rectangle_paper_count_x,rectangle_paper_count_y);
            printf("PAPERSIZE #%d: %s  WIDTH=%d, HEIGHT=%d, OVERLAP=%d (mm)  PPI: X=%d,Y=%d",paper_select,paper_name.c_str(),width_mm,height_mm,overlap_mm,ppi_x,ppi_y);
*/
            break;
        }
        if (event.key.alt)
        {
            selector--;
            if (selector<0)
                selector=3;
            for (int i=0; i<4; i++)
            {
                if (selector==FFMPEG_SELECT)
                {
                    if(ffmpegfile==1)
                        selector=CANVAS_SELECT;
                    else
                        break;
                }
                if (selector==MOVIE2_SELECT)
                {
                    if(movie2==1)
                        selector=MOVIE_SELECT;
                    else
                        break;
                }
                if (selector==MOVIE_SELECT)
                {
                    if(movie==1)
                        selector=INTERNET_SELECT;
                    else
                        break;
                }
                if (selector==INTERNET_SELECT)
                {
                    if(internetfile==1)
                        selector=FFMPEG_SELECT;
                    else
                        break;
                }
                if (selector==CANVAS_SELECT)
                {
                    if(plot_all==0 && plot_cubes==0)
                        selector=MOVIE2_SELECT;
                    else
                        break;
                }
            }
            break;
        }
        if (event.key.control)
        {
            fspeedy+=0.1;
            speedy=fspeedy;
//            fspeedy=fspeedy*1.1;
            fspeedy_new=fspeedy;
            speedy_new=speedy;
            maze_up=1;
            maze_down=0;
            maze_left=0;
            maze_right=0;
            maze_up_new=1;
            maze_down_new=0;
            maze_left_new=0;
            maze_right_new=0;
            pressed=1;
            break;
        }
        if (mouse_move==1)
            break;
        if (    ( (internetfile==0 && handler[INTERNET_SELECT].show==1) || (movie==0 ) || (ffmpegfile==0) || (pacman==0) )
                && pen==0 && force_game==0 || (pen==0 && (drawmazes==0 || pacman==0) ) )
//        if (    ( (internetfile==0 && internet_move==0) || (movie==0 && movie_move==0) || (ffmpegfile==0 && ffmpeg_move==0) )
//                && pen==0 && force_game==0 || (pen==0 && drawmazes==0 && (movie_move==0 || ffmpeg_move==0 || internet_move==0))  )
        {
            if (fspeedy!=0)
            {
                if (mirror==1) speedy+=100;
                else speedy=speedy+1;
                fspeedy=speedy;
                printf("x=%d,y=%d\r",speedx,speedy);
//                        speedx=0;
//                        fspeedx=0.0;
            }
            else
            {
                speedy=1;
                fspeedy=1.0;
                if (event.key.shift)
                {
                    one_pixel=1;
                }
            }
            speedy_new=speedy;
            speedx_new=0;
            fspeedy_new=speedy;
            fspeedx_new=0;
            maze_up=1;
            maze_down=0;
            maze_left=0;
            maze_right=0;
            maze_up_new=1;
            maze_down_new=0;
            maze_left_new=0;
            maze_right_new=0;
            pressed=1;
            break;
        } else printf("NOOOOOOOOOOOOOO\r");
        if (pen==1)
        {
            speedy=72;
            speedx=0;
            fspeedy=72;
            fspeedx=0;
            maze_up=1;
            maze_down=0;
            maze_left=0;
            maze_right=0;
        }
        else
        {
            pressed=1;
//crossing
            speedy_new=4;
            speedx_new=0;
            fspeedy_new=4;
            fspeedx_new=0;
            maze_up_new=1;
            maze_down_new=0;
            maze_left_new=0;
            maze_right_new=0;
        }
        break;
    case sf::Keyboard::Down:
        if (paper_select>0 && (event.key.alt || event.key.control || event.key.shift)) {
            if (move_clock.getElapsedTime()<sf::milliseconds(200)) {
                move_speed=move_speed*1.01;
                move_speed_int=(int)move_speed;
            } else {
                move_speed_int=1;
                move_speed=1.0;
            }
            move_clock.restart();
              if (event.key.control) {
                rectangle_paper_pos_y+=move_speed_int;
//                if (rectangle_paper_pos_y+rectangle_paper.getSize().y<maxpixelsy) rectangle_paper_pos_y+=move_speed_int;
            } else if (event.key.alt) {
                if (rectangle_paper_count_y*rectangle_paper.getSize().y+rectangle_paper_pos_y<maxpixelsy) {
                    rectangle_paper_count_y++;
                }
            } else if (event.key.shift) {
                if (rectangle_paper_count_y*(rectangle_paper_inner.getSize().y)+rectangle_paper_pos_y-move_speed_int*2<maxpixelsy) {
                    height_pixels=height_pixels+2*move_speed_int;
                    rectangle_paper.setSize(sf::Vector2f(width_pixels+overlap_pixels*2,height_pixels+overlap_pixels*2));
                    rectangle_paper_inner.setSize(sf::Vector2f(width_pixels,height_pixels));
                    rectangle_paper_outer.setSize(sf::Vector2f(width_pixels+overlap_pixels*2,height_pixels+overlap_pixels*2));
                    ppi_y=(int)(0.5+(float)height_pixels/((float)height_mm/25.4));
                }
            }
            sprintf(error_msg2,"Position: X=%d,Y=%d  Size: X=%d,Y=%d  Count: X=%d,Y=%d",
                    rectangle_paper_pos_x,rectangle_paper_pos_y,(int)rectangle_paper.getSize().x,(int)rectangle_paper.getSize().y,rectangle_paper_count_x,rectangle_paper_count_y);
            error_flag2=1;
            sprintf(error_msg3,"Total Poster Size: X=%d,Y=%d Pixels => X=%f,Y=%f Centimeters on 300 ppi",
                    width_pixels*rectangle_paper_count_x,height_pixels*rectangle_paper_count_y,
                    (float)(width_pixels*rectangle_paper_count_x)*2.54/300.0,(float)(height_pixels*rectangle_paper_count_y)*2.54/300.0);
            error_flag3=1;
            sprintf(error_msg,"PAPERSIZE #%d: %s  WIDTH=%d, HEIGHT=%d, OVERLAP=%d (mm)  PPI: X=%d,Y=%d",paper_select,paper_name.c_str(),width_mm,height_mm,overlap_mm,ppi_x,ppi_y);
            error_flag=1;
  /*
            printf("#%d %s\n",paper_select,paper_name.c_str());
            printf("Paper format:   width=%d,height=%d (mm)\n",width_mm,height_mm);
            printf("Picture format: width=%d,height=%d (mm) (overlap=%d)\n",width_mm+overlap_mm*2,height_mm+overlap_mm*2,overlap_mm);
            printf("Pixels: (picture  pixel width / 25.4 mm/inch) * 300 ppi=%d\n",width_pixels+overlap_pixels*2);
            printf("Pixels: (picture pixel height / 25.4 mm/inch) * 300 ppi=%d\n",height_pixels+overlap_pixels*2);
            printf("Total Poster Size: X=%d,Y=%d Pixels => X=%7.1f,Y=%7.1f Centimeters on 300 ppi\n", width_pixels*rectangle_paper_count_x,height_pixels*rectangle_paper_count_y, (float)(width_pixels*rectangle_paper_count_x)*2.54/300.0,(float)(height_pixels*rectangle_paper_count_y)*2.54/300.0);
            printf("-----------------------------------------------------------------\n");
            printf("Position: X=%d,Y=%d  Size: X=%d,Y=%d  Count: X=%d,Y=%d",rectangle_paper_pos_x,rectangle_paper_pos_y,(int)rectangle_paper.getSize().x,(int)rectangle_paper.getSize().y,rectangle_paper_count_x,rectangle_paper_count_y);
            printf("PAPERSIZE #%d: %s  WIDTH=%d, HEIGHT=%d, OVERLAP=%d (mm)  PPI: X=%d,Y=%d",paper_select,paper_name.c_str(),width_mm,height_mm,overlap_mm,ppi_x,ppi_y);
*/
            break;
        }
        if (event.key.alt)
        {
            selector++;
            if (selector==4)
                selector=0;
            for (int i=0; i<4; i++)
            {
                if (selector==FFMPEG_SELECT)
                {
                    if(ffmpegfile==1)
                        selector=INTERNET_SELECT;
                    else
                        break;
                }
                if (selector==INTERNET_SELECT)
                {
                    if(internetfile==1)
                        selector=MOVIE_SELECT;
                    else
                        break;
                }
                if (selector==MOVIE_SELECT)
                {
                    if(movie==1)
                        selector=MOVIE2_SELECT;
                    else
                        break;
                }
                if (selector==MOVIE2_SELECT)
                {
                    if(movie2==1)
                        selector=CANVAS_SELECT;
                    else
                        break;
                }
                if (selector==CANVAS_SELECT)
                {
                    if(plot_all==0 && plot_cubes==0)
                        selector=FFMPEG_SELECT;
                    else
                        break;
                }
            }
            break;
        }
        if (event.key.control)
        {
            fspeedy-=0.1;
            speedy=fspeedy;
//            fspeedy=fspeedy/1.1;
            fspeedy_new=fspeedy;
            speedy_new=fspeedy_new;
            maze_up=0;
            maze_down=1;
            maze_left=0;
            maze_right=0;
            maze_up_new=0;
            maze_down_new=1;
            maze_left_new=0;
            maze_right_new=0;
            pressed=1;
            break;
        }
        if (mouse_move==1)
            break;
        if (    ( (internetfile==0 && handler[INTERNET_SELECT].show==1) || (movie==0 ) || (ffmpegfile==0) || (pacman==0) )
                && pen==0 && force_game==0 || (pen==0 && (drawmazes==0 || pacman==0) ) )
//        if (    ( (internetfile==0 && internet_move==0) || (movie==0 && movie_move==0) || (ffmpegfile==0 && ffmpeg_move==0) )
//                && pen==0 && force_game==0 || (pen==0 && drawmazes==0 && (movie_move==0 || ffmpeg_move==0 || internet_move==0))  )
        {
            if (fspeedy!=0)
            {
                if (mirror==1) speedy-=100;
                else speedy=speedy-1;
                fspeedy=speedy;
                printf("x=%d,y=%d\r",speedx,speedy);
//                        speedx=0;
//                        fspeedx=0.0;
            }
            else
            {
                speedy=-1;
                fspeedy=-1.0;
                if (event.key.shift)
                {
                    one_pixel=1;
                }
            }
            speedy_new=speedy;
            speedx_new=0;
            fspeedy_new=speedy;
            fspeedx_new=0;
            maze_up=0;
            maze_down=1;
            maze_left=0;
            maze_right=0;
            maze_up_new=0;
            maze_down_new=1;
            maze_left_new=0;
            maze_right_new=0;
            pressed=1;
            break;
        } else printf("NOOOOOOOOOOOOOO\r");
        if (pen==1)
        {
            speedy=-72;
            speedx=0;
            fspeedy=-72;
            fspeedx=0;
            maze_down=1;
            maze_up=0;
            maze_right=0;
            maze_left=0;
        }
        else
        {
            pressed=1;
//crossing
            speedy_new=-4;
            speedx_new=0;
            fspeedy_new=-4;
            fspeedx_new=0;
            maze_down_new=1;
            maze_up_new=0;
            maze_left_new=0;
            maze_right_new=0;
        }
        break;
    case sf::Keyboard::Q:
        if (event.key.control && event.key.alt)
        {
            if (!file_exists(macro_name))
            {
                sprintf(error_msg3,"CANNOT FIND SELECTED MACRO FILE: %s",macro_name);
                printf("%s\n",error_msg3);
                error_flag3=1;
            }
            else
            {
                char execute_me[200]="";
                char execute_check[200]="";
                int line_count=0;
                int ret=1;
                while (line_count<ret)
                {
                    line_count++;
                    ret=select_from_list2(execute_me,macro_name,line_count);
                    if (ret==0)
                    {
                        sprintf(error_msg3,"MACRO FILE EMPTY? : %s",macro_name);
                        printf("%s\n",error_msg3);
                        error_flag3=1;
                        break;
                    }
                    else
                    {
//                        printf("execute_me=%s\n",execute_me);
                        if (!(execute_me[0]=='#') && !(execute_me[0]=='/'))
                        {
//                            printf("execute_me=%s\n",execute_me);
                            while (replace_str(execute_me,"//","\0"));
//                            printf("execute_me=%s\n",execute_me);
                            strcpy(execute_check,execute_me);
                            trim(execute_check);
//                            printf("execute_check=%s\n",execute_check);
                            if (strlen(execute_check)>0)
                                ;
                            {
                                wprintf(L"\x1b[34;47m");
                                printf("EXCUTING MACRO: %s LINE# %d: %s\n",macro_name,line_count,execute_me);
                                wprintf(L"\x1b[0m");
                                parse_command(execute_me);
                            }
                        }
                    }
                }
            }
            break;
        }
        if (event.key.alt)
        {
            if (int index=select_macro(macro_name,MACRODIR))
            {
                sprintf(error_msg3,"SELECTED MACRO FILE #%d: %s",index,macro_name);
                printf("%s\n",error_msg3);
                error_flag3=1;
                sprintf(error_msg4,"PRESS CTRL-ALT-Q TO EXECUTE");
                printf("%s\n",error_msg4);
                error_flag4=1;
            }
            else
            {
                sprintf(error_msg3,"ERROR SELECTING MACRO FILE #%d: %s",index,macro_name);
                printf("%s\n",error_msg3);
                error_flag3=1;
            }
            break;
        }
        if (event.key.shift)
        {
            doscript(2,com);
            std::cout << hoppa;

//            std::cout << '\n';
            break;
        }
//extern FILE* file1;
//extern FILE* file2;
//extern FILE* file3;
        if (event.key.control)
        {
            send_message='x';
            sf::sleep(sf::milliseconds(100));
//            fclose(file1);fclose(file2);fclose(file3);
            for (int kutgodverdomme=0; kutgodverdomme<10; kutgodverdomme++) {
                ShowTaskBar(true);
                kiki();kiki();kiki();kiki();kiki();kiki();kiki();kiki();kiki();kiki();
                sf::sleep(sf::milliseconds(10));
            }
            ShowTaskBar(true);
            if (cool==1)
            {
                mutje.lock();
                cool=0;
                mutje.unlock();
                sf::sleep(sf::milliseconds(1000));
            }
//            if (server_running) {
//                send_message='S';
//                printf("Stopping server\n");
//                while (server_running) { sf::sleep(sf::seconds(0.1)); kiki(); }
//                printf("Server stopped\n");
//                sf::sleep(sf::seconds(0.2));
//            }
            sound[0].stop();
            sound[1].stop();
            sound[2].stop();
            sound[3].stop();
            sound[4].stop();
            sound[5].stop();
            sound[6].stop();
            sound[7].stop();

            go_on=0;
//            printf("Stopping animator\n");
//            while (animator_running==1) { sf::sleep(sf::seconds(0.1)); kiki(); }
//            printf("Animator stopped\n");
//            if (server_running) {
//                printf("Shutting down server\n");
//                NonCtrlHandler(SIGINT);
//            }
//            winmain_running=0;
            GenerateConsoleCtrlEvent(CTRL_C_EVENT, 0);
//            SFMLView1.close();
            break;
        }
        break;
    case sf::Keyboard::PageDown:
        if (combine) {
            if (event.key.alt) {
                if (event.key.control) {
                    iZoom=iZoom/1.002;
                    break;
                } else {
                    iZoom=iZoom/1.01;
                    break;
                }
            } else {
                if (event.key.control) {
                    iZoom=iZoom/1.1;
                    break;
                } else {
                    iZoom=iZoom/1.2;
                    break;
                }
            }
        }
        if (event.key.shift || event.key.control || event.key.system)
        {
            if (paper_select) {
                rectangle_paper.setRotation(rectangle_paper.getRotation()-1.0);
            }
            if (selector==CANVAS_SELECT)
                if (rotate_canvas==0 && (plot_all==1 || plot_cubes==1))
                {
                    rotate_canvas=1;
                    rot_speed_canvas=0;
                    rotation_canvas=0;
                }
            if (selector==FFMPEG_SELECT) {
                if (event.key.shift && event.key.control) {
                    float scale=(float)maxpixelsx/(float)texture_from_ffmpeg.getSize().x;
                    sprite_from_ffmpeg.setScale(scale,scale);
                    break;
                }
                if (rotate_ffmpeg==0 && ffmpegfile==0 && !event.key.system)
                {
                    rotate_ffmpeg=1;
                    rot_speed_ffmpeg=0;
                    rotation_ffmpeg=0;
                    size_ffmpeg=1;
                }
            }
            if (selector==INTERNET_SELECT)
                if (rotate_internet==0 && internetfile==0)
                {
                    rotate_internet=1;
                    rot_speed_internet=0;
                    rotation_internet=0;
                    size_internet=1;
                }
            if (selector==MOVIE_SELECT)
                if (rotate_movie==0 && movie==0)
                {
                    rotate_movie=1;
                    rot_speed_movie=0;
                    rotation_movie=0;
                    size_movie=1;
                }
            if (selector==MOVIE2_SELECT)
                if (rotate_movie2==0 && movie2==0)
                {
                    rotate_movie2=1;
                    rot_speed_movie2=0;
                    rotation_movie2=0;
                    size_movie2=1;
                }
            if (ffmpegfile==0 && selector==FFMPEG_SELECT)
            {
                size_ffmpeg=1;
                if (event.key.shift && event.key.control)
                    sprite_from_ffmpeg.setScale(sprite_from_ffmpeg.getScale().x*0.9999,sprite_from_ffmpeg.getScale().y*0.9999);
                else if (event.key.shift)
                {
                    if (event.key.system)
                        sprite_from_ffmpeg.setScale(sprite_from_ffmpeg.getScale().x*0.95,sprite_from_ffmpeg.getScale().y);
                    else
                        sprite_from_ffmpeg.setScale(sprite_from_ffmpeg.getScale().x*0.95,sprite_from_ffmpeg.getScale().y*0.95);
                }
                else
                {
                    if (event.key.system) {
                        sprite_from_ffmpeg.setScale(sprite_from_ffmpeg.getScale().x*0.995,sprite_from_ffmpeg.getScale().y);
                    }
                    else {
                        sprite_from_ffmpeg.setScale(sprite_from_ffmpeg.getScale().x*0.995,sprite_from_ffmpeg.getScale().y*0.995);
                    }
                }
                scale_now=sprite_from_ffmpeg.getScale().x;
                break;
            }
            if (internetfile==0 && selector==INTERNET_SELECT)
            {
                size_internet=1;
                if (event.key.shift)
                    sprite_from_internet.setScale(sprite_from_internet.getScale().x*0.95,sprite_from_internet.getScale().y*0.95);
                else
                    sprite_from_internet.setScale(sprite_from_internet.getScale().x*0.995,sprite_from_internet.getScale().y*0.995);
//joepiedepoepie
                if (ffmpegfile==1)
                    scale_now=sprite_from_internet.getScale().x;
            }
            if ((plot_all==1 || plot_cubes==1) && selector==CANVAS_SELECT)
            {
                if (event.key.shift)
                    sprite_from_canvas.setScale(sprite_from_canvas.getScale().x*0.95,sprite_from_canvas.getScale().y*0.95);
                else
                    sprite_from_canvas.setScale(sprite_from_canvas.getScale().x*0.995,sprite_from_canvas.getScale().y*0.995);
            }
            if (movie==0 && selector==MOVIE_SELECT)
            {
                size_movie=1;
                if (event.key.shift)
                    sprite_from_movie.setScale(sprite_from_movie.getScale().x*0.95,sprite_from_movie.getScale().y*0.95);
                else
                    sprite_from_movie.setScale(sprite_from_movie.getScale().x*0.995,sprite_from_movie.getScale().y*0.995);
                scale_now=sprite_from_movie.getScale().x;
            }
            if (movie2==0 && selector==MOVIE2_SELECT)
            {
                size_movie2=1;
                if (event.key.shift)
                    sprite_from_movie2.setScale(sprite_from_movie2.getScale().x*0.95,sprite_from_movie2.getScale().y*0.95);
                else
                    sprite_from_movie2.setScale(sprite_from_movie2.getScale().x*0.995,sprite_from_movie2.getScale().y*0.995);
                scale_now=sprite_from_movie2.getScale().x;
            }
        }
        if (event.key.alt)
        {
            if (rotate_ffmpeg==1 && selector==FFMPEG_SELECT)
            {
                if (pen==0)
                    rot_speed_ffmpeg=rot_speed_ffmpeg-0.0001;
                else
                    rot_speed_ffmpeg=rot_speed_ffmpeg-0.01;
            }
            if (rotate_internet==1 && selector==INTERNET_SELECT)
                rot_speed_internet=rot_speed_internet-0.01;
            if (rotate_movie==1 && selector==MOVIE_SELECT)
                rot_speed_movie=rot_speed_movie-0.01;
            if (rotate_movie2==1 && selector==MOVIE2_SELECT)
                rot_speed_movie2=rot_speed_movie2-0.01;
            if (rotate_canvas==1 && selector==CANVAS_SELECT)
                rot_speed_canvas=rot_speed_canvas-0.01;
        }
        else if (!event.key.shift && !event.key.control)
        {
            if (rotate_ffmpeg==1 && selector==FFMPEG_SELECT)
            {
                if (pen==0)
                    rotation_ffmpeg=rotation_ffmpeg-0.0001;
                else
                    rotation_ffmpeg=rotation_ffmpeg-0.1;
            }
            else
                rotate_ffmpeg=1;
            if (rotate_internet==1 && selector==INTERNET_SELECT)
                rotation_internet=rotation_internet-0.1;
            else
                rotate_internet=1;
            if (rotate_movie==1 && selector==MOVIE_SELECT)
                rotation_movie=rotation_movie-0.1;
            else
                rotate_movie=1;
            if (rotate_movie2==1 && selector==MOVIE2_SELECT)
                rotation_movie2=rotation_movie2-0.1;
            else
                rotate_movie2=1;
            if (rotate_canvas==1 && selector==CANVAS_SELECT)
                rotation_canvas=rotation_canvas-0.1;
            else
                rotate_canvas=1;
        }
        break;
    case sf::Keyboard::Space:
        if (event.key.alt==1)
        {
            if (selector==CANVAS_SELECT)
            {
                if (rot_speed_canvas==0.0)
                {
                    rotation_canvas=0.0;
                    rotate_canvas=0.0;
                }
                else
                    rot_speed_canvas=0.0;
            }
            if (selector==MOVIE_SELECT)
                rot_speed_movie=0.0;
            if (selector==MOVIE2_SELECT)
                rot_speed_movie2=0.0;
            if (selector==FFMPEG_SELECT)
                rot_speed_ffmpeg=0.0;
            if (selector==INTERNET_SELECT)
                rot_speed_internet=0.0;
        }
        else if (event.key.shift==1)
        {
            if (selector==CANVAS_SELECT)
                sprite_from_canvas.setScale(0.02,0.02);
            if (selector==FFMPEG_SELECT)
                sprite_from_ffmpeg.setScale(1.0,1.0);
            if (selector==INTERNET_SELECT)
                sprite_from_internet.setScale(1.0,1.0);
            if (selector==MOVIE_SELECT)
                sprite_from_movie.setScale(1.0,1.0);
            if (selector==MOVIE2_SELECT)
                sprite_from_movie2.setScale(1.0,1.0);
            scale_now=1.0;
        }
        else if (event.key.control==1)
        {
            if (movie==0 && selector==MOVIE_SELECT ||
                    movie2==0 && selector==MOVIE2_SELECT ||
                    ffmpegfile==0 && selector==FFMPEG_SELECT ||
                    internetfile==0 && selector==INTERNET_SELECT ||
                    (plot_all==1 || plot_cubes==1) && selector==CANVAS_SELECT
               )
            {
                if (selector_item==BLENDING_SELECT)
                    if (handler[selector].blending==0)
                        handler[selector].blending=1;
                    else if (handler[selector].blending==1)
                        handler[selector].blending=2;
                    else if (handler[selector].blending==2)
                        handler[selector].blending=-1;
                    else
                        handler[selector].blending=0;

                if (selector_item==PLOT_FRONT_SELECT)
                    if (handler[selector].plot_front==0)
                        handler[selector].plot_front=1;
                    else if (handler[selector].plot_front==1)
                        handler[selector].plot_front=2;
                    else if (handler[selector].plot_front==2)
                        handler[selector].plot_front=-1;
                    else
                        handler[selector].plot_front=0
                                                     ;
                if (selector_item==SHOW_SELECT)
                    if (handler[selector].show==1)
                        handler[selector].show=0;
                    else
                        handler[selector].show=1;

                if (selector_item==TILE_SELECT)
                    if (handler[selector].tile==1)
                    {
                        handler[selector].tile=2;
                        if (selector==FFMPEG_SELECT)
                        {
                            if (ffmpeg_move)
                            {
                                ffmpeg_fixed_x=(ffmpeg_posx+render_posx-render_picturex*1920)+(int)texture_from_ffmpeg.getSize().x/2;
                                ffmpeg_fixed_y=(ffmpeg_posy+render_posy-render_picturey*1080)+(int)texture_from_ffmpeg.getSize().y/2;
                            }
                            else
                            {
                                ffmpeg_fixed_x=1920.0/2.0;
                                ffmpeg_fixed_y=1080.0/2.0;
                            }
                        }
                        else if (selector==INTERNET_SELECT)
                        {
                            if (internet_move)
                            {
                                internet_fixed_x=(internet_posx+render_posx-render_picturex*1920)+(int)texture_from_internet.getSize().x/2;
                                internet_fixed_y=(internet_posy+render_posy-render_picturey*1080)+(int)texture_from_internet.getSize().y/2;
                            }
                            else
                            {
                                internet_fixed_x=1920.0/2.0;
                                internet_fixed_y=1080.0/2.0;
                            }
                        }
                        else if (selector==MOVIE_SELECT)
                        {
                            if (movie_move)
                            {
                                movie_fixed_x=(movie_posx+render_posx-render_picturex*1920)+(int)texture_from_movie_new.getSize().x/2;
                                movie_fixed_y=(movie_posy+render_posy-render_picturey*1080)+(int)texture_from_movie_new.getSize().y/2;
                            }
                            else
                            {
                                movie_fixed_x=1920.0/2.0;
                                movie_fixed_y=1080.0/2.0;
                            }
                        }
                        else if (selector==MOVIE2_SELECT)
                        {
                            if (movie2_move)
                            {
                                movie2_fixed_x=(movie2_posx+render_posx-render_picturex*1920)+(int)texture_from_movie2_new.getSize().x/2;
                                movie2_fixed_y=(movie2_posy+render_posy-render_picturey*1080)+(int)texture_from_movie2_new.getSize().y/2;
                            }
                            else
                            {
                                movie2_fixed_x=1920.0/2.0;
                                movie2_fixed_y=1080.0/2.0;
                            }
                        }
                    }
                    else if (handler[selector].tile==2)
                        handler[selector].tile=0;
                    else
                    {
                        handler[selector].tile=1;
                    }

                if (selector_item==SHADER_SELECT)
                    if (handler[selector].shader==1)
                        handler[selector].shader=0;
                    else
                        handler[selector].shader=1;
            }
            /*
                        if (selector==MOVIE_SELECT) movie_move=0;
                        if (selector==MOVIE2_SELECT) movie2_move=0;
                        if (selector==FFMPEG_SELECT) ffmpeg_move=0;
                        if (selector==INTERNET_SELECT) internet_move=0;
            */
        }
        break;
    case sf::Keyboard::Slash:
        if (event.key.shift && event.key.control) {
            send_message='S';
            break;
        } else if (event.key.shift) {
            send_message='s';
//            launch_SERVER();
            break;
        } else if (event.key.control) {
            test_tha_shit(1);
            break;
        } else if (event.key.alt) {
            if (combine==1) {
                test1();
            } else {
                test2();
            }
            testing=1;
            break;
        }
//        send_through_bukkitserver_mcrcon((char *)"noppes");
extern void bukkit_thread_server();
extern int bukkit_running;
        bukkit_running=1;
        bukkit_thread_server();
//            start_stop_bukkit_thread_server();

        break;
    case sf::Keyboard::PageUp:
        if (combine) {
            if (event.key.alt) {
                if (event.key.control) {
                    iZoom=iZoom*1.002;
                    break;
                } else {
                    iZoom=iZoom*1.01;
                    break;
                }
            } else {
                if (event.key.control) {
                    iZoom=iZoom*1.1;
                    break;
                } else {
                    iZoom=iZoom*1.2;
                    break;
                }
            }
        }
        if (event.key.shift || event.key.control || event.key.system)
        {
            if (paper_select) {
                rectangle_paper.setRotation(rectangle_paper.getRotation()+1.0);
            }
            if (selector==FFMPEG_SELECT)
                if (rotate_ffmpeg==0 && ffmpegfile==0)
                {
                    rotate_ffmpeg=1;
                    rot_speed_ffmpeg=0;
                    rotation_ffmpeg=0;
                    size_ffmpeg=1;
                }
            if (selector==CANVAS_SELECT)
                if (rotate_canvas==0 && (plot_all==1 || plot_cubes==1))
                {
                    rotate_canvas=1;
                    rot_speed_canvas=0;
                    rotation_canvas=0;
                }
            if (selector==INTERNET_SELECT)
                if (rotate_internet==0 && internetfile==0)
                {
                    rotate_internet=1;
                    rot_speed_internet=0;
                    rotation_internet=0;
                    size_internet=1;
                }
            if (selector==MOVIE_SELECT)
                if (rotate_movie==0 && movie==0)
                {
                    rotate_movie=1;
                    rot_speed_movie=0;
                    rotation_movie=0;
                    size_movie=1;
                }
            if (selector==MOVIE2_SELECT)
                if (rotate_movie2==0 && movie2==0)
                {
                    rotate_movie2=1;
                    rot_speed_movie2=0;
                    rotation_movie2=0;
                    size_movie2=1;
                }
            if (ffmpegfile==0 && selector==FFMPEG_SELECT)
            {
                size_ffmpeg=1;
                if (event.key.shift && event.key.control)
                    sprite_from_ffmpeg.setScale(sprite_from_ffmpeg.getScale().x*1.0001,sprite_from_ffmpeg.getScale().y*1.0001);
                else if (event.key.shift)
                {
                    if (event.key.system)
                        sprite_from_ffmpeg.setScale(sprite_from_ffmpeg.getScale().x*1.05,sprite_from_ffmpeg.getScale().y);
                    else
                        sprite_from_ffmpeg.setScale(sprite_from_ffmpeg.getScale().x*1.05,sprite_from_ffmpeg.getScale().y*1.05);
                }
                else if (event.key.system) {
                    sprite_from_ffmpeg.setScale(sprite_from_ffmpeg.getScale().x*1.005,sprite_from_ffmpeg.getScale().y);
                }
                else {
                    sprite_from_ffmpeg.setScale(sprite_from_ffmpeg.getScale().x*1.005,sprite_from_ffmpeg.getScale().y*1.005);
                }
                scale_now=sprite_from_ffmpeg.getScale().x;
                break;
            }
            if (internetfile==0  && selector==INTERNET_SELECT)
            {
                size_internet=1;
                if (event.key.shift)
                    sprite_from_internet.setScale(sprite_from_internet.getScale().x*1.05,sprite_from_internet.getScale().y*1.05);
                else
                    sprite_from_internet.setScale(sprite_from_internet.getScale().x*1.005,sprite_from_internet.getScale().y*1.005);
//joepiedepoepie
                if (ffmpegfile==1)
                    scale_now=sprite_from_internet.getScale().x;
            }
            if (movie==0 && selector==MOVIE_SELECT)
            {
                size_movie=1;
                if (event.key.shift)
                    sprite_from_movie.setScale(sprite_from_movie.getScale().x*1.05,sprite_from_movie.getScale().y*1.05);
                else
                    sprite_from_movie.setScale(sprite_from_movie.getScale().x*1.005,sprite_from_movie.getScale().y*1.005);
                scale_now=sprite_from_internet.getScale().x;
            }
            if ((plot_all==1 || plot_cubes==1) && selector==CANVAS_SELECT)
            {
                if (event.key.shift)
                    sprite_from_canvas.setScale(sprite_from_canvas.getScale().x*1.05,sprite_from_canvas.getScale().y*1.05);
                else
                    sprite_from_canvas.setScale(sprite_from_canvas.getScale().x*1.005,sprite_from_canvas.getScale().y*1.005);
            }
            if (movie2==0 && selector==MOVIE2_SELECT)
            {
                size_movie2=1;
                if (event.key.shift)
                    sprite_from_movie2.setScale(sprite_from_movie2.getScale().x*1.05,sprite_from_movie2.getScale().y*1.05);
                else
                    sprite_from_movie2.setScale(sprite_from_movie2.getScale().x*1.005,sprite_from_movie2.getScale().y*1.005);
                scale_now=sprite_from_movie2.getScale().x;
            }
        }
        if (event.key.alt)
        {
            if (rotate_ffmpeg==1 && selector==FFMPEG_SELECT)
            {
                if (pen==0)
                    rot_speed_ffmpeg=rot_speed_ffmpeg+0.0001;
                else
                    rot_speed_ffmpeg=rot_speed_ffmpeg+0.01;
            }
            if (rotate_internet==1 && selector==INTERNET_SELECT)
                rot_speed_internet=rot_speed_internet+0.01;
            if (rotate_movie==1 && selector==MOVIE_SELECT)
                rot_speed_movie=rot_speed_movie+0.01;
            if (rotate_movie2==1 && selector==MOVIE2_SELECT)
                rot_speed_movie2=rot_speed_movie2+0.01;
            if (rotate_canvas==1 && selector==CANVAS_SELECT)
                rot_speed_canvas=rot_speed_canvas+0.01;
        }
        else if (!event.key.shift && !event.key.control)
        {
            if (rotate_ffmpeg==1 && selector==FFMPEG_SELECT)
            {
                if (pen==0)
                    rotation_ffmpeg=rotation_ffmpeg+0.0001;
                else
                    rotation_ffmpeg=rotation_ffmpeg+0.1;
            }
            else
                rotate_ffmpeg=1;
            if (rotate_internet==1 && selector==INTERNET_SELECT)
                rotation_internet=rotation_internet+0.1;
            else
                rotate_internet=1;
            if (rotate_movie==1 && selector==MOVIE_SELECT)
                rotation_movie=rotation_movie+0.1;
            else
                rotate_movie=1;
            if (rotate_movie2==1 && selector==MOVIE2_SELECT)
                rotation_movie2=rotation_movie2+0.1;
            else
                rotate_movie2=1;
            if (rotate_canvas==1 && selector==CANVAS_SELECT)
                rotation_canvas=rotation_canvas+0.1;
            else
                rotate_canvas=1;
        }
        break;
    case sf::Keyboard::X:
        if (event.key.control) {
            for (int t=0; t<30; t++) {
                kiki();
                monitor_off=1;
                sf::sleep(sf::seconds(0.1));
            }
            xallocator_test();
        }
        break;
    case sf::Keyboard::Y:
        if (event.key.shift && event.key.alt)
        {
            if (ffmpegfile==0 && selector==FFMPEG_SELECT)
                rot_texture_90(&texture_from_ffmpeg);
            break;
        }
        if (event.key.shift && event.key.control)
        {
            if (ffmpegfile==0 && selector==FFMPEG_SELECT)
                rot_texture_as_is(&texture_from_ffmpeg,&sprite_from_ffmpeg);
            rotate_ffmpeg=0.0;
            rotation_ffmpeg=0.0;
            break;
        }
        if (event.key.alt)
        {
            rotate_canvas=0;
            rotation_canvas=0.0;
            plot_all_rotate_x=0.0;
            plot_all_rotate_y=0.0;
            plot_all_rotate_z=0.0;
            plot_all_translate_x=0.0;
            plot_all_translate_y=0.0;
            plot_all_translate_z=0.0;
            break;
        }
        if (event.key.control)
        {
            if (plot_all==0)
            {
//                rotation_canvas=0.0;
//                rot_speed_canvas=0.0;
                if (blank_maze==0)
                    gen_all_mipmaps();
                plot_all=1;
                set_mapper();
                perform_quit=1;
                if (F2==1)
                {
                    draw2((char*)"LOADING BITMAPS",800,0,sf::Color::Red,sf::Color::White);
                    SFMLView1.display();
                }
//                if (BITMAPSX*BITMAPSY<=MAXINMEM)
//                    CreateAll(); fok you if > 500 a 600 ...
                if (blank_maze==1)
                    gen_all_mipmaps();
                perform_quit=0;
                /*
                                else {
                                    int fromx=-BITMAPSX/2+1;// if (fromx<-3) fromx=-3;
                                    int tox=BITMAPSX/2;// if (tox>4) tox=4;
                                    int fromy=fromx;
                                    int toy=tox;
                //                    int fromy=-BITMAPSY/2+1;if (fromy<-3) fromy=-3;
                //                    int toy=BITMAPSY/2; if (toy>4) toy=4;
                                    while (!fromx>-2 && !fromy>-2 &&(tox-fromx)*(toy-fromy)>MAXINMEM)
                                    {
                                        fromx++;tox--;
                                        fromy++;toy--;
                                    }
                                    for (int x=fromx; x<=tox; x++)
                                    {
                                        for (int y=fromy; y<=toy; y++)
                                        {
                                            int arx=(render_picturex+x+BITMAPSX)%BITMAPSX;
                                            int ary=(render_picturey+y+BITMAPSY)%BITMAPSY;
                                            if (used[arx][ary]==0) ReadOneBitmap(arx,ary);
                                            if (totalused>MAXINMEM)
                                            {
                                                go_save_some_bitmaps();
                                            }
                                        }
                                    }
                                }
                */
            }
            else
            {
                plot_all=0;
            }
        }
        break;

//    case sf::Keyboard::L:
//        GET_LAT_LON_FROM_FILELIST(naam);
//        if (file_exists(naam)) {
//        }
//        break;
    case sf::Keyboard::P:
        if (event.key.alt)
        {
            if (rotate_ffmpeg==1 )
            {
                if (size_ffmpeg==0)
                    rotate_ffmpeg=0;
                else
                {
                    if (rot_speed_ffmpeg==0 && rotation_ffmpeg==0)
                    {
                        rotate_ffmpeg=1;
                        rot_speed_ffmpeg=1.0;
                    }
                    else
                    {
                        rot_speed_ffmpeg=0;
                        rotation_ffmpeg=0;
                    }
                }
            }
            else
            {
                rotate_ffmpeg=1;
                rot_speed_ffmpeg=1.0;
            }
//                if (rotate_ffmpeg==1) {
            sprite_from_ffmpeg.setOrigin(texture_from_ffmpeg.getSize().x/2,texture_from_ffmpeg.getSize().y/2);
//                } else {
//                    sprite_from_ffmpeg.setOrigin(0,0);
//                }
            break;
        }
        if (event.key.control)
        {
            if (ffmpeg_move==1)
                ffmpeg_move=0;
            else
                ffmpeg_move=1;
            if (ffmpeg_move==1)
            {
                ffmpeg_posx=-render_posx+render_picturex*1920+(1920/2-(int)texture_from_ffmpeg.getSize().x/2);
                ffmpeg_posy=-render_posy+render_picturey*1080+(1080/2-(int)texture_from_ffmpeg.getSize().y/2);
                sprite_from_ffmpeg.setPosition((ffmpeg_posx+render_posx-render_picturex*1920), ( ffmpeg_posy + render_posy-render_picturey*1080) );
            }
            else
            {
                sprite_from_ffmpeg.setPosition( (1920)/2, (1080)/2 );
            }
        }
        break;
    case sf::Keyboard::I:
        if (event.key.alt)
        {
            if (rotate_internet==1)
            {
                if (size_internet==0)
                    rotate_internet=0;
                else
                {
                    if (rot_speed_internet==0 && rotation_internet==0)
                    {
                        rotate_internet=1;
                        rot_speed_internet=1.0;
                    }
                    else
                    {
                        rot_speed_internet=0;
                        rotation_internet=0;
                    }
                }
            }
            else
            {
                rotate_internet=1;
                rot_speed_internet=1.0;
            }
//                if (rotate_internet==1) {
            sprite_from_internet.setOrigin(texture_from_internet.getSize().x/2,texture_from_internet.getSize().y/2);
//                } else {
//                    sprite_from_internet.setOrigin(0,0);
//                }
            break;
        }
        if (event.key.control)
        {
            if (internet_move==1)
                internet_move=0;
            else
                internet_move=1;

            if (internet_move==1)
            {
                internet_posx=-render_posx+render_picturex*1920+(1920/2-(int)texture_from_internet.getSize().x/2);
                internet_posy=-render_posy+render_picturey*1080+(1080/2-(int)texture_from_internet.getSize().y/2);
                sprite_from_internet.setPosition((internet_posx+render_posx-render_picturex*1920), ( internet_posy + render_posy-render_picturey*1080) );
            }
            else
            {
                sprite_from_internet.setPosition( (1920-(int)texture_from_internet.getSize().x)/2,(1080-(int)texture_from_internet.getSize().y)/2);
            }
        }
        break;
    case sf::Keyboard::M:
        if (event.key.shift)
        {
            size_movie=1;
            //        rotate_movie=0;
            sprite_from_movie.setScale(1.0,1.0);
            scale_now=1.0;
            if (movie==1)
            {
                time_movie=sf::seconds(0.0);
                strcpy(movie_name,"");
                if (select_movie(filename,MOVIEDIR)>0)
                    movie=startmovie(filename);
                if (movie==0)
                {
                    texture_from_movie_new.setRepeated(TRUE);
                    strcpy(movie_name,filename);
                    rotation_movie=0.0;
                    rot_speed_movie=0.0;
                    sprite_from_movie.setTexture(texture_from_movie_new,false);
                    sprite_from_movie.setScale(1.0,1.0);
                    scale_now=1.0;

                    sprite_from_movie.setTextureRect( { 0,0,(int)texture_from_movie_new.getSize().x, (int)texture_from_movie_new.getSize().y } );
                    timer_movie=10;
                    if (smooth==1)
                        texture_from_movie_new.setSmooth(TRUE);
                    else
                        texture_from_movie_new.setSmooth(TRUE);
                    setmoviefile();
                }
                else
                {
                    sprintf(writer,"invalid movie: %s\n",filename);
                    savedata(writer,0);
                    MessageBox(NULL, writer,"NOT LOADED", MB_ICONEXCLAMATION | MB_OK);
                }

                if (record_screen==1 && record_pause==0 && movie==0)
                {
                    //                    time_movie=sf::seconds(0.0);
                    timer_movie=10;
                    SFMLView1.setVerticalSyncEnabled(false);
                }
                break;
            }
            else
            {
                error_flag=0;
                stopmovie();
                movie=1;
                if (movie2!=0)
                {
                    if (sync==1)
                        SFMLView1.setVerticalSyncEnabled(true);
                    else
                        SFMLView1.setVerticalSyncEnabled(false);
                }
            }
            shift=0;
            break;
        }
        else if (event.key.alt)
        {
            if (rotate_movie==1 )
            {
                if (size_movie==0)
                    rotate_movie=0;
                else
                {
                    if (rot_speed_movie==0 && rotation_movie==0)
                    {
                        rotate_movie=1;
                        rot_speed_movie=1.0;
                    }
                    else
                    {
                        rot_speed_movie=0;
                        rotation_movie=0;
                    }
                }
            }
            else
            {
                rotate_movie=1;
                rot_speed_movie=1.0;
            }
//                if (rotate_movie==1) {
            sprite_from_movie.setOrigin(texture_from_movie_new.getSize().x/2,texture_from_movie_new.getSize().y/2);
//                } else {
//                    sprite_from_movie.setOrigin(0,0);
//                }
            break;
        }
        else if (event.key.control)
        {
            if (movie_move==1)
                movie_move=0;
            else
                movie_move=1;
            if (movie_move==1)
            {
                movie_posx=-render_posx+render_picturex*1920+(1920/2-(int)texture_from_movie_new.getSize().x/2);
                movie_posy=-render_posy+render_picturey*1080+(1080/2-(int)texture_from_movie_new.getSize().y/2);
                sprite_from_movie.setPosition((movie_posx+render_posx-render_picturex*1920), ( movie_posy + render_posy-render_picturey*1080) );
            }
            else
            {
                sprite_from_movie.setPosition( (1920-(int)texture_from_movie_new.getSize().x)/2,(1080-(int)texture_from_movie_new.getSize().y)/2);
            }
            break;
        }
        else
        {
            if (levelnotsaved==1)
            {
                strcpy(error_msg,"LEVEL NOT SAVED!!! PRESS AGAIN TO MAZE LEVEL / FULL / OFF");
                error_flag=1;
                levelnotsaved=0;
                break;
            }

            if (drawmazes==0)
            {
                if (totalchanged>0)
                {
                    DONTSAVEFILES=0;
                    SAVEALLBITMAPS();
                    strcpy(error_msg,"BITMAPS CHANGED!!! SAVING FIRST BEFORE DRAW MAZE!!!");
                    error_flag=1;
                }
                else
                {
                    strcpy(error_msg,"DRAW MAZE=ON");
                    error_flag=1;
                }
                pen=1;
                pen_mode=2;
                shift=0;
                drawmazes=1;
            }
            cleanupbitmaps_mazes();
            if (loaded==0)
            {
                if (big_large==0)
                {
                    big_large=1;
                    SEED=time(0);
                    sprintf(writer,"T=MAZE,BIGLARGE=%d,SEED=%d,LEVEL=%d,\0",big_large,SEED,level);
                    if (connected==1)
                        SEND(writer);
                }
                else
                {
                    big_large=0;
//rinkel
//                    loaded=1;
                }
                loaded_from_maze=0;
            }
            else
            {
                loaded=0;
                if (connected==1)
                {
                    SEED=time(0);
                    sprintf(writer,"T=MAZE,BIGLARGE=%d,SEED=%d,LEVEL=%d,\0",big_large,SEED,level);
                    SEND(writer);
                }
                mazetype=1;
                loaded_from_maze=0;
            }
            if (loaded==1)
            {
                //change
                sprintf(naam,"%s/%dx%d/%03d/maze.dat",LEVELDIR,BITMAPSX,BITMAPSY,level);
                //				sprintf(naam,"levels/%dx%d/maze%d.dat",BITMAPSX,BITMAPSY,level);
                if (!file_exists(naam))
                {
                    level=1;
                    sprintf(naam,"%s/%dx%d/%03d/maze.dat",LEVELDIR,BITMAPSX,BITMAPSY,level);
                    //					sprintf(naam,"levels/%dx%d/maze%d.dat",BITMAPSX,BITMAPSY,level);
                    while (!file_exists(naam)&& level<50 )
                    {
                        level++;
                        sprintf(naam,"%s/%dx%d/%03d/maze.dat",LEVELDIR,BITMAPSX,BITMAPSY,level);
                        //						sprintf(naam,"levels/%dx%d/maze%d.dat",BITMAPSX,BITMAPSY,level);
                    }
                    if (level==50)
                        level=1;
                }
                if (connected==1)
                {
                    sprintf(writer,"T=LEVEL,LEVEL=%d,\0",level);
                    SEND(writer);
                }
                loaded_from_maze=1;
                load_maze(level);
            }
            next=1;
            forced_jump=1;
        }
        break;
    case sf::Keyboard::A:
        if (event.key.control)
        {
            if (ffmpegfile==0 && selector==FFMPEG_SELECT)
            {
                add_border(&texture_from_ffmpeg);
                sprite_from_ffmpeg.setTextureRect( { 0,0,(int)texture_from_ffmpeg.getSize().x, (int)texture_from_ffmpeg.getSize().y } );
            }
            if (internetfile==0 && selector==INTERNET_SELECT)
            {
                add_border(&texture_from_internet);
                sprite_from_internet.setTextureRect( { 0,0,(int)texture_from_internet.getSize().x, (int)texture_from_internet.getSize().y } );
            }
        }
        break;
    case sf::Keyboard::R:
        if (event.key.control && event.key.shift) {
            if (crop==0) crop=1;
            else crop=0;
            break;
        }
        if (event.key.control && event.key.alt) {
            if (RGBA==0) RGBA=1;
            else RGBA=0;
            break;
        }
        if (event.key.alt)
        {
            if (record_debug==0)
                record_debug=1;
            else
                record_debug=0;
            break;
        }
        if (event.key.control)
        {
            if (movie==0 && selector==MOVIE_SELECT)
            {
                movie_to_ffmpeg(&texture_from_movie_new, &texture_from_ffmpeg);
                size_ffmpeg=0;
                ffmpegfile=0;
                rotate_ffmpeg=0;
                sprite_from_ffmpeg.setScale(1.0,1.0);
                scale_now=1.0;
                rotation_ffmpeg=0.0;
                rot_speed_ffmpeg=1.0;
                sprite_from_ffmpeg.setTexture(texture_from_ffmpeg,false);
                sprite_from_ffmpeg.setScale(1.0,1.0);
                scale_now=1.0;
                setffmpegfile();
                sprite_from_ffmpeg.setTextureRect( { 0,0,(int)texture_from_ffmpeg.getSize().x, (int)texture_from_ffmpeg.getSize().y } );
            }
            if (movie2==0 && selector==MOVIE2_SELECT)
            {
                movie_to_ffmpeg(&texture_from_movie2_new, &texture_from_ffmpeg);
                sprite_from_ffmpeg.setTextureRect( { 0,0,(int)texture_from_ffmpeg.getSize().x, (int)texture_from_ffmpeg.getSize().y } );
                size_ffmpeg=0;
                ffmpegfile=0;
                rotate_ffmpeg=0;
                sprite_from_ffmpeg.setScale(1.0,1.0);
                scale_now=1.0;
                rotation_ffmpeg=0.0;
                rot_speed_ffmpeg=1.0;
                sprite_from_ffmpeg.setTexture(texture_from_ffmpeg,false);
                sprite_from_ffmpeg.setScale(1.0,1.0);
                scale_now=1.0;
                setffmpegfile();
                sprite_from_ffmpeg.setTextureRect( { 0,0,(int)texture_from_ffmpeg.getSize().x, (int)texture_from_ffmpeg.getSize().y } );
            }
            break;
        }
        break;
    case sf::Keyboard::U:
        if (event.key.control && event.key.alt) {
            if (plot_cubes==1) plot_cubes=0; else plot_cubes=1;
            if (plot_cubes) set_cube();

            break;
        }
        if (event.key.control) {
            move_config++;
            if (move_config>3) move_config=0;
            break;
        }
        if (event.key.alt) {
            if (pacman_move==0)
                pacman_move=1;
            else if (pacman_move==1)
                pacman_move=2;
            else if (pacman_move==2)
                pacman_move=3;
            else if (pacman_move==3)
                pacman_move=0;
            break;
        }
        if (shade_map>=1)
        {
            if (dont_stop==0)
            {
                kill1=0;
                kill2=0;
                kill3=0;
                texture_from_internet.create(256,256);
                add_border(&texture_from_internet);
                sprite_from_internet.setTextureRect( { 0,0,(int)texture_from_internet.getSize().x, (int)texture_from_internet.getSize().y } );
                START_LOADING_FOR_ALL_BITMAPS();
            }
            else
                dont_stop=0;
            break;
        }
        else
        {
            strcpy(error_msg,"SELECT SHADE_MAP=2 (ALT-F6)(2X)");
            error_flag=1;
        }
//expand
    case sf::Keyboard::C:

        if (event.key.shift || event.key.alt)
        {
            if (event.key.shift) paper_format();
            printf("#%d %s\n",paper_select,paper_name.c_str());
            printf("Paper format:   width=%d,height=%d (mm)\n",width_mm,height_mm);
            printf("Picture format: width=%d,height=%d (mm) (overlap=%d)\n",width_mm+overlap_mm*2,height_mm+overlap_mm*2,overlap_mm);
            printf("Pixels: (picture  pixel width / 25.4 mm/inch) * 300 ppi=%d\n",width_pixels+overlap_pixels*2);
            printf("Pixels: (picture pixel height / 25.4 mm/inch) * 300 ppi=%d\n",height_pixels+overlap_pixels*2);
            printf("Total Poster Size: X=%d,Y=%d Pixels => X=%7.1f,Y=%7.1f Centimeters on 300 ppi\n", width_pixels*rectangle_paper_count_x,height_pixels*rectangle_paper_count_y, (float)(width_pixels*rectangle_paper_count_x)*2.54/300.0,(float)(height_pixels*rectangle_paper_count_y)*2.54/300.0);
            printf("-----------------------------------------------------------------\n");
            printf("Position: X=%d,Y=%d  Size: X=%d,Y=%d  Count: X=%d,Y=%d",rectangle_paper_pos_x,rectangle_paper_pos_y,(int)rectangle_paper.getSize().x,(int)rectangle_paper.getSize().y,rectangle_paper_count_x,rectangle_paper_count_y);
            printf("PAPERSIZE #%d: %s  WIDTH=%d, HEIGHT=%d, OVERLAP=%d (mm)  PPI: X=%d,Y=%d",paper_select,paper_name.c_str(),width_mm,height_mm,overlap_mm,ppi_x,ppi_y);
            if (event.key.shift) break;
        }
        if (event.key.control)
        {
            if (ffmpegfile==0 && selector==FFMPEG_SELECT)
            {
                convert_to_scale(&texture_from_ffmpeg, &sprite_from_ffmpeg);
                scale_now=1.0;
            }
            if (internetfile==0 && selector==INTERNET_SELECT)
            {
                convert_to_scale(&texture_from_internet, &sprite_from_internet);
                scale_now=1.0;
            }
            break;
        }
        if (event.key.alt)
        {
            ffmpegfile=0;
            texture_from_ffmpeg.create(width_pixels+2*overlap_pixels,height_pixels+2*overlap_pixels);
            sprite_from_ffmpeg.setTexture(texture_from_ffmpeg,true);
            sprite_from_ffmpeg.setScale(1.0,1.0);
            sprite_from_ffmpeg.setPosition(0.0,0.0);
//            sprite_from_ffmpeg.setRotation(rectangle_paper.getRotation());
            rotation_ffmpeg=rectangle_paper.getRotation();
//            sprite_from_ffmpeg.setOrigin(0.0,0.0);
            texture_from_ffmpeg.setSmooth(false);
            selector=FFMPEG_SELECT;
            smooth=0;
            for (int xx=0; xx<MAXINMEM+12; xx++)
            {
                texturemaxinmem[xx].setSmooth(FALSE);
            }
            printf("\n");
            system("mkdir ..\\cut");
            scale_now=1.0;
            ffmpeg_move=1;

            char naam[2000];
            for (int y=0; y<rectangle_paper_count_y; y++) {
                for (int x=0; x<rectangle_paper_count_x; x++) {

                    ffmpeg_posx=x*(width_pixels) + width_pixels/2.0+overlap_pixels;
                    ffmpeg_posy=y*(height_pixels)+height_pixels/2.0+overlap_pixels;

                    float rot=rectangle_paper.getRotation();
                    float rot_x=ffmpeg_posx;
                    float rot_y=ffmpeg_posy;

/*
                                    rot_x=(float)(maxpixelsx*x)+(float)pos_x-(float)smooth_x+(float)((int)smooth_x);
                                    rot_y=(float)(maxpixelsy*y)+(float)pos_y-(float)smooth_y+(float)((int)smooth_y);
                                    float plus_x=rot_x*cos( rot*M_PI/180.0)+rot_y*sin( rot*M_PI/180.0);
                                    float plus_y=rot_x*sin(-rot*M_PI/180.0)+rot_y*cos(-rot*M_PI/180.0);
*/




//                    ffmpeg_posx=rot_x*cos( rot*M_PI/180.0)+rot_y*sin( rot*M_PI/180.0)+rectangle_paper_pos_x;
//                    ffmpeg_posy=rot_x*sin(-rot*M_PI/180.0)+rot_y*cos(-rot*M_PI/180.0)+rectangle_paper_pos_y;

                    ffmpeg_posx=rot_x*cos(rot*M_PI/180.0)+rot_y*sin(-rot*M_PI/180.0)+rectangle_paper_pos_x;
                    ffmpeg_posy=rot_x*sin(rot*M_PI/180.0)+rot_y*cos( rot*M_PI/180.0)+rectangle_paper_pos_y;

                    ffmpeg_posx=ffmpeg_posx-width_pixels/2.0 -overlap_pixels;
                    ffmpeg_posy=ffmpeg_posy-height_pixels/2.0-overlap_pixels;

//                    ffmpeg_posx=ffmpeg_posx-texture_from_ffmpeg.getSize().x/2;
//                    ffmpeg_posy=ffmpeg_posy-texture_from_ffmpeg.getSize().y/2;
//                    ffmpeg_posx=ffmpeg_posx-texture_from_ffmpeg.getSize().x/2;
//                    ffmpeg_posy=ffmpeg_posy-texture_from_ffmpeg.getSize().y/2;

//                    rot_x=texture_from_ffmpeg.getSize().x/2;
//                    rot_y=texture_from_ffmpeg.getSize().y/2;
//                    rot_x= width_pixels/2.0;
//                    rot_y=height_pixels/2.0;

//                    start_posx=ffmpeg_posx-1920/2+rot_x*cos(rot*M_PI/180.0)+rot_y*sin(-rot*M_PI/180.0);
//                    start_posy=ffmpeg_posy-1080/2+rot_x*sin(rot*M_PI/180.0)+rot_y*cos( rot*M_PI/180.0);

//                    start_posx=ffmpeg_posx-1920/2+rot_x*cos(rot*M_PI/180.0)+rot_y*sin(-rot*M_PI/180.0);
//                    start_posy=ffmpeg_posy-1080/2+rot_x*sin(rot*M_PI/180.0)+rot_y*cos( rot*M_PI/180.0);

                    start_posx=ffmpeg_posx-1920/2+ width_pixels/2.0+overlap_pixels;
                    start_posy=ffmpeg_posy-1080/2+height_pixels/2.0+overlap_pixels;

//                    start_posx=ffmpeg_posx-1920/2+texture_from_ffmpeg.getSize().x/2;
//                    start_posy=ffmpeg_posy-1080/2+texture_from_ffmpeg.getSize().y/2;

                    if ((start_posx)>=maxpixelsx)   start_posx=start_posx-maxpixelsx;
                    else if ((start_posx)<0)        start_posx=start_posx+maxpixelsx;
                    if ((start_posy)>=maxpixelsy)   start_posy=start_posy-maxpixelsy;
                    else if ((start_posy)<0)        start_posy=start_posy+maxpixelsy;

                    home_map();
                    render_picturex=picturex;
                    render_posx=posx;
                    render_picturey=picturey;
                    render_posy=posy;
                    printf("Creating X=%d,Y=%d  ",x,y);
//                    sprite_from_ffmpeg.setRotation(rectangle_paper.getRotation());
                    get_ffmpegfile();
                    sprintf(naam,"..\\cut\\picture.%06d.%06d.png",y,x);

                    if (crossing==1) {
                        sprite_from_ffmpeg.setScale(1920.0/(float)texture_from_ffmpeg.getSize().x,1080.0/(float)texture_from_ffmpeg.getSize().y);
                        convert_to_scale(&texture_from_ffmpeg, &sprite_from_ffmpeg);
                        scale_now=1.0;
                    }

                    printf("Saving %s\n",naam);
                    shut_up=1;
                    texture_from_ffmpeg.copyToImage().saveToFile(naam);
                    shut_up=0;

                    if (crossing==1) {
                        texture_from_ffmpeg.create(width_pixels+2*overlap_pixels,height_pixels+2*overlap_pixels);
                        sprite_from_ffmpeg.setTexture(texture_from_ffmpeg,true);
                        sprite_from_ffmpeg.setScale(1.0,1.0);
                        sprite_from_ffmpeg.setPosition(0.0,0.0);
                    }
                }
            }
            ffmpegfile=1;
            break;
        }
        break;
    case sf::Keyboard::E:
        if (event.key.control)
        {
            if (internetfile==0 && selector==INTERNET_SELECT)
            {
                soften_edge(&texture_from_internet);
                sprite_from_internet.setTextureRect( { 0,0,(int)texture_from_internet.getSize().x, (int)texture_from_internet.getSize().y } );
                setinternetfile();
            }
            if (ffmpegfile==0 && selector==FFMPEG_SELECT)
            {
                soften_edge(&texture_from_ffmpeg);
                sprite_from_ffmpeg.setTextureRect( { 0,0,(int)texture_from_ffmpeg.getSize().x, (int)texture_from_ffmpeg.getSize().y } );
                setffmpegfile();
            }
        }
        break;
    case sf::Keyboard::S:
        if (combine==1) {
            sprite_from_ffmpeg.setScale(sf::Vector2f(5.0,5.0));
            break;
        }
        if (event.key.control)
        {
            if (plot_shader==0)
                plot_shader=1;
            else if (plot_shader==1)
                plot_shader=2;
            else
                plot_shader=0;
            break;
        }
        if (event.key.alt)
        {
            if (smooth==0)
                smooth=1;
            else
                smooth=0;
            for (int xx=0; xx<MAXINMEM+12; xx++)
            {
                if (smooth==1)
                {
                    texturemaxinmem[xx].setSmooth(TRUE);
                }
                else
                {
                    texturemaxinmem[xx].setSmooth(FALSE);
                }
            }
            if (smooth==1)
            {
                texture_from_buffer.setSmooth(TRUE);
                texture_from_buffer2.setSmooth(TRUE);
                texture_from_ffmpeg.setSmooth(TRUE);
                texture_from_internet.setSmooth(TRUE);
                texture_from_movie2_new.setSmooth(TRUE);
                texture_from_movie_new.setSmooth(TRUE);
                sfml_mazedot.setSmooth(TRUE);
                sfml_mazedot2.setSmooth(TRUE);
                texture_cube.setSmooth(TRUE);
                texture_cube.setSmooth(TRUE);
            }
            else
            {
                texture_from_buffer.setSmooth(FALSE);
                texture_from_buffer2.setSmooth(FALSE);
                texture_from_ffmpeg.setSmooth(FALSE);
                texture_from_internet.setSmooth(FALSE);
                texture_from_movie2_new.setSmooth(FALSE);
                texture_from_movie_new.setSmooth(FALSE);
                sfml_mazedot.setSmooth(FALSE);
                sfml_mazedot2.setSmooth(FALSE);
                texture_cube.setSmooth(FALSE);
                texture_cube.setSmooth(FALSE);
            }
            if (smooth==1)
                strcpy(error_msg,"SMOOTH TEXTURES ON");
            else
                strcpy(error_msg,"SMOOTH TEXTURES OFF");
            error_flag=1;
        }
        break;
    case sf::Keyboard::B:
        if (event.key.alt)
        {
            if (rotate_movie2==1 )
            {
                if (size_movie2==0)
                    rotate_movie2=0;
                else
                {
                    if (rot_speed_movie2==0 && rotation_movie2==0)
                    {
                        rotate_movie2=1;
                        rot_speed_movie2=1.0;
                    }
                    else
                    {
                        rot_speed_movie2=0;
                        rotation_movie2=0;
                    }
                }
            }
            else
            {
                rotate_movie2=1;
                rot_speed_movie2=1.0;
            }
//                if (rotate_movie2==1) {
            sprite_from_movie2.setOrigin(texture_from_movie2_new.getSize().x/2,texture_from_movie2_new.getSize().y/2);
//                } else {
            sprite_from_movie2.setOrigin(0,0);
//                }
            break;
        }
        else if (event.key.control)
        {
            if (movie2_move==1)
                movie2_move=0;
            else
                movie2_move=1;

            if (movie2_move==1)
            {
                movie2_posx=-render_posx+render_picturex*1920+(1920/2-(int)texture_from_movie2_new.getSize().x/2);
                movie2_posy=-render_posy+render_picturey*1080+(1080/2-(int)texture_from_movie2_new.getSize().y/2);
                sprite_from_movie2.setPosition((movie2_posx+render_posx-render_picturex*1920), ( movie2_posy + render_posy-render_picturey*1080) );
            }
            else
            {
                sprite_from_movie2.setPosition( (1920-(int)texture_from_movie2_new.getSize().x)/2,(1080-(int)texture_from_movie2_new.getSize().y)/2);
            }
        }
        else if (event.key.shift)
        {
            size_movie2=1;
            sprite_from_movie2.setScale(1.0,1.0);
            scale_now=1.0;
            if (movie2==1)
            {
                time_movie2=sf::seconds(0.0);
                if (select_movie(filename,MOVIEDIR)>0)
                {
                    movie2=startmovie2(filename);
                }

                if (movie2==0)
                {
                    texture_from_movie2_new.setRepeated(true);
                    rotation_movie2=0.0;
                    rot_speed_movie2=0.0;
                    rot_speed_movie2=0.0;
                    sprite_from_movie2.setTexture(texture_from_movie2_new,false);
                    //                    sprite_from_movie2.setScale(1.0,1.0);
                    scale_now=sprite_from_movie2.getScale().x;

                    sprite_from_movie2.setTextureRect( { 0,0,(int)texture_from_movie2_new.getSize().x, (int)texture_from_movie2_new.getSize().y } );
                    timer_movie2=10;
                    if (smooth==1)
                        texture_from_movie2_new.setSmooth(TRUE);
                    else
                        texture_from_movie2_new.setSmooth(TRUE);
                    setmoviefile2();
                }
                else
                {
                    sprintf(writer,"invalid movie2: %s\n",filename);
                    savedata(writer,0);
                    MessageBox(NULL, writer,"NOT LOADED", MB_ICONEXCLAMATION | MB_OK);
                }

                if (record_screen==1 && record_pause==0 && movie2==0)
                {
                    //                    time_movie=sf::seconds(0.0);
                    timer_movie2=10;
                    SFMLView1.setVerticalSyncEnabled(false);
                }
                break;
            }
            else
            {
                error_flag=0;
                stopmovie2();
                movie2=1;
                if (movie!=0)
                {
                    if (sync==1)
                        SFMLView1.setVerticalSyncEnabled(true);
                    else
                        SFMLView1.setVerticalSyncEnabled(false);
                }
            }
            shift=0;
            break;
        }
        else
        {
            if (movieextern==0)
                movieextern=1;
            else
                movieextern=0;
            if (movieextern==0)
            {
                if (select_movie(filename,MOVIEDIR)>0)
                {
                    if (playing_start(filename)==0)
                    {
                        if (record_screen==1)
                            play_rate=1;
                        else
                            play_rate=1;
                        strcpy(error_msg2,"EXTERNAL FFMPEG LOADING SUCCESFULL");
                        error_flag2=1;
                        //                    Screenget3();
                        if (flop==0)
                            rate_count=play_rate-1;
                        else
                            rate_count=play_rate;
                    }
                    else
                    {
                        strcpy(error_msg2,"FAILED STARTING MOVIE FROM FFMPEG EXTERN");
                        error_flag2=1;
                        movieextern=1;
                    }
                }
                else
                {
                    strcpy(error_msg2,"EXTERNAL FFMPEG CANNOT SELECT MOVIE (LIST.TXT/PACMAN.INI)");
                    error_flag2=1;
                    movieextern=1;
                }
            }
            else
            {
                if (record_screen)
                {
                    record_pause=1;
                    burn_subs=0;
                }
                playing_end();
                texture_ready=0;
                isplaying=0;
                strcpy(error_msg2,"EXTERNAL FFMPEG PLAYING ENDED");
                error_flag2=1;
            }
        }
        break;
    case sf::Keyboard::D:
        if (event.key.alt)
        {
            start_dos_command_thread();
        }
        else if (event.key.control)
        {
            if (blank_maze==0)
                blank_maze=1;
            else
                blank_maze=0;

            if (drawmazes==1)
            {
                cleanupbitmaps_mazes();
                if (PRELOAD==1)
                    CreateAll();
                ReadBitmaps2();
                ReadBitmaps4();
//                if (blank_maze==1) gen_all_mipmaps();
//                pen=1;
//                pen_mode=2;
//                shift=0;
                break;


                if (blank_maze==0)
                    strcpy(error_msg,"BITMAPS RELOADED   DRAWMAZES=ON   SAVE FILES=ON");
                else
                    strcpy(error_msg,"BITMAPS RELOADED   DRAWMAZES=BLANKED   SAVE FILES=ON");
//                DONTSAVEFILES=0;
                error_flag=1;
                if (blank_maze==0)
                    DRAWALLMAZES();
                break;
            }
        }
        break;
    case sf::Keyboard::Delete:
        if (event.key.control) {
            m_pointCloud3.clear();
            break;
        }
        if (event.key.alt)
        {
            if (levelnotsaved==1)
            {
                strcpy(error_msg,"BACKGROUND EDITED AND NOT SAVED!!! PRESS ALT-DELETE AGAIN 2x TO CLEAR BITMAPS");
                error_flag=1;
                levelnotsaved=0;
//jojojo
//                pen=1;
//                pen_mode=2;
//                shift=0;
//                again1=1;
                break;
            }
            else if (again1<2)
            {
                if (drawmazes==1)
                {
                    if (again1==0)
                        strcpy(error_msg,"DELETE DRAWMAZES BITMAPS PERMANENTLY???? PRESS ALT-DELETE 2x AGAIN TO CLEAR BITMAPS");
                    else
                        strcpy(error_msg,"DELETE DRAWMAZES BITMAPS PERMANENTLY???? PRESS ALT-DELETE ONCE AGAIN TO CLEAR BITMAPS");
                }
                else
                {
                    if (again1==0)
                        strcpy(error_msg,"DELETE WHOLE BACKGROUND BITMAPS PERMANENTLY???? PRESS ALT-DELETE 2x AGAIN TO CLEAR BITMAPS");
                    else
                        strcpy(error_msg,"DELETE WHOLE BACKGROUND BITMAPS PERMANENTLY???? PRESS ALT-DELETE ONCE AGAIN TO CLEAR BITMAPS");
                }
                error_flag=1;
                again1++;
                break;
            }
            again1=0;
//??????????
            if (drawmazes==1)
            {
                cleanupbitmaps_mazes();
                strcpy(error_msg,"ALL BITMAPS MAZES DELETED");
            }
            else
            {
                cleanupbitmaps();
                strcpy(error_msg,"ALL BITMAPS BACKGROUND DELETED");
            }
            set_time=fpstime;
            error_flag=1;

            if (drawmazes==1)
            {
                if (MAPMODE!=0) {
                    kleur_back=0;
                    kleur_front=0;
                } else {
                    if (kleur_front==0)
                        kleur_front=1;
                    else
                        kleur_front=0;
                }
                if (kleur_front==0)
                {
                    if (kleur_back==1 && loadbackground==1)
                    {
//                            SFMLView1.setActive(true);
                        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
//                            SFMLView1.setActive(false);
                    }
                    else
                    {
//                            SFMLView1.setActive(true);
                        glClearColor(0.0f, 0.0f, 0.0f, (float)(set_transparant==0));
//                            glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
//                            SFMLView1.setActive(false);
                    }
                    background_color[1]=sf::Color(0.0,0.0,0.0,(set_transparant==0)*255);
//                        background_color[1]=sf::Color(0.0,0.0,0.0,0.0);
                }
                else
                {
//                        SFMLView1.setActive(true);
//                        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
//                        SFMLView1.setActive(false);
                    background_color[1]=sf::Color(255.0,255.0,255.0,255.0);
                }
            }
            else
            {
                if (MAPMODE!=0) {
                    kleur_back=0;
                    kleur_front=0;
                } else {
                    if (kleur_back==0)
                        kleur_back=1;
                    else
                        kleur_back=0;
                }
                if (kleur_back==0)
                {
                    glClearColor(0.0f, 0.0f, 0.0f, (float)(set_transparant==0));
//                    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
                    background_color[0]=sf::Color(0.0,0.0,0.0,(set_transparant==0)*255);
//                    background_color[0]=sf::Color(0.0,0.0,0.0,0.0);
                }
                else
                {
                    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
                    background_color[0]=sf::Color(255.0,255.0,255.0,255.0);
                }
            }

//            CLEANBITMAPS();
            if (PRELOAD==1)
                CreateAll();
//hiero
            ReadBitmaps2();
            ReadBitmaps4();
            LOADALLBITMAPS();
//jojojo
//            pen=1;
//            pen_mode=2;
//            shift=0;
            break;
        }
        else
        {
            if (levelnotsaved==1)
                {
                strcpy(error_msg,"MAP EDITED AND NOT SAVED!!! PRESS DELETE AGAIN TO CLEAR MAP. BITMAPS DRAWMAZES WILL ALSO BE DELETED!");
                error_flag=1;
                levelnotsaved=0;
                again2=1;
                break;
            }
            else if (again2==0)
            {
                strcpy(error_msg,"DELETE MAP? PRESS DELETE AGAIN TO CLEAR MAP. BITMAPS DRAWMAZES WILL ALSO BE DELETED!");
                error_flag=1;
                again2=1;
                break;
            }
            again2=0;
            clear_map();
            if (connected==1)
            {
                sprintf(writer,"T=CLEARMAP,\0");
                SEND(writer);
                SENDGOTOPOS();
            }
            pen=1;
            pen_mode=2;
            if (drawmazes==1)
                cleanupbitmaps_mazes();
            loadbackground=1;
            CLEANBITMAPS();
            ReadBitmaps2();
            ReadBitmaps4();
            break;
        }
    case sf::Keyboard::Insert:
        if (event.key.shift)
        {
            if (set_transparant==1)
                set_transparant=0;
            else
                set_transparant=1;
            break;
        }
        else if (autodraw==1)
            autodraw=0;
        else
            autodraw=1;
        break;
    case sf::Keyboard::V:
        if (event.key.control)
        {
            if (crossing==0)
                crossing=1;
            else if (crossing==1)
                crossing=2;
            else if (crossing==2)
                crossing=3;
            else
                crossing=0;
            if (connected==1)
            {
                sprintf(writer,"T=CROSSING,CROSSING=%d,\0",crossing);
                SEND(writer);
            }
            break;
        }
        else if (event.key.alt && event.key.control)
        {
            char filename[1000];
            ShowCursor(TRUE);
            if (select_movie(filename,MOVIEDIR)>0)
                playmovie(filename);
            ShowCursor(FALSE);
        }
        else if (event.key.alt && event.key.shift)
        {
            if (burn_subs)
            {
                strcpy(error_msg3,"ALLREADY BURNING SUBTITLES");
                error_flag3=1;
            }
            else
            {
                strcpy(error_msg3,"BURNING SUBTITLES");
                error_flag3=1;
                burn_next_sub_ready=1;
            }
//            burn_next_sub();
//            get_videos();
            break;
        }
        else if (event.key.alt)
        {
            strcpy(error_msg3,"STARTING GET VIDEO'S IN BACKGROUND");
            error_flag3=1;
            start_get_videos_thread();
//            get_videos();
            break;
        }
        break;
    default:
//        printf("Unknow option: ");
//        print_event(event);
        break;
    }
}


LRESULT CALLBACK WinProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
    static int x;
    static int y;
    static char naam[200];

    switch(message)
    {
    case WM_CREATE:
        break;
    case WM_COMMAND:
        switch(LOWORD(wparam))
        {
        case 2:
            switch(HIWORD(wparam))
            {
            case BN_CLICKED:
            case BN_PUSHED:
                int len = GetWindowTextLength(TextBox) + 1;
                char* text = new char[len];
                char text2[100]="ENTERED IP ADDRESS = ";
                GetWindowText(TextBox, &text[0], len);
                strcat(text2,text);
                strcat(text2,"\r\n");
                SendMessage(TextField, EM_SETSEL, -1, -1);
                SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)text2);
                SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"STARTING CLIENT\r\n");

                int reconnect = MessageBox(
                                    NULL,
                                    "RECONNECT FROM PREVIOUS?\n"
                                    "YES FOR RECONNECT NO FOR NEW CONNECTION",
                                    "PLEASE SELECT",
                                    MB_ICONEXCLAMATION | MB_YESNO | MB_DEFBUTTON2
                                );

                if (reconnect == IDYES)
                {
                    if (udp==1)
                        client=reconnectUdpClient(text,portnumber);
                    else if (tcp==1)
                        client=reconnectTcpClient(text,portnumber);
                }
                else
                {
                    if (tcp==1)
                        client=runTcpClient(text,portnumber);
                    else if (udp==1)
                        client=runUdpClient(text,portnumber);
                }

                delete[] text;
                if (client==0)
                {
                    int MID=MessageBox(
                                NULL,
                                "CONNECTION FAILED",
                                "ERROR",
                                MB_ICONEXCLAMATION | MB_RETRYCANCEL | MB_TOPMOST
                            );
                    if (MID==IDCANCEL)
                        frexit(0);
                    SetWindowText(TextField, "");
                    ShowWindow(hWndMain2, SW_SHOW);
                }
                else
                {
                    strcpy(connectedip,text);
                    connected=1;
                }
                break;
            }
            break;
        }
    case WM_KEYDOWN:
        HANDLEKEY(wparam,event);
        break;
    case WM_CHAR:
        HANDLECHAR(wparam);
        break;
    case WM_LBUTTONDOWN:
        if (pen==0)
        {
            pen=1;
            pen_mode=0;
        }
        else
            pen=0;
        HALT();
        break;
    case WM_RBUTTONDOWN:
        pen_mode++;
        if (pen_mode>2)
            pen_mode=0;
        break;
    case WM_MOUSEMOVE:
        x = LOWORD(lparam)-128;
        y = HIWORD(lparam)-128;
        break;
    case WM_CLOSE:
    case WM_DESTROY:
//			cleanupbitmaps();
        PostQuitMessage(0);
        if (connected==1)
        {
        }
        return 0;
    }
    return DefWindowProc(hwnd, message, wparam, lparam);
}

void ghost_next()
{
    if (number==0)
    {
        follow_ghost=0;
        set_pacman();
//pospos
        posx=posx-posx%64-32;
        if (posx<=-1920)
        {
            posx=posx+1920;
            picturex=(picturex+1+totalpicturex)%totalpicturex;
        }
        posy=posy-(posy-36)%72-36;
        if (posy<=-1080)
        {
            posy=posy+1080;
            picturey=(picturey+1+totalpicturey)%totalpicturey;
        }
        fposx=posx;
        fposy=posy;
        ReadBitmaps2();

        /*
                        posx=posx-posx%64-32;
                        if (posx<=-1920)
                            posx=posx+1920;
                        posy=posy-(posy-36)%72-36;
                        if (posy<=-1080)
                            posy=posy+1080;
                        fposx=posx;
                        fposy=posy;
        */


        follow_ghost=0;
//                long_jump=1;
        pen=old_pen;
        if (pen==1)
            pen_mode=2;
        else
            pen_mode=0;
    }
    int ghost_x_now=fpos_ghostx[follow_ghost_num];
    int ghost_y_now=fpos_ghosty[follow_ghost_num];
    int max_dist=99999999999;
    int select_ghost=0;
    for (int i=0; i<number; i++) {
        int next_i=(i+follow_ghost_num)%number;
        int ghost_x_new=fpos_ghostx[next_i];
        int ghost_y_new=fpos_ghosty[next_i];
        int diff_x=abs(ghost_x_new-ghost_x_now);
        int diff_y=abs(ghost_y_new-ghost_y_now);
        if (diff_x>maxpixelsx/2) diff_x=maxpixelsx-diff_x;
        if (diff_y>maxpixelsy/2) diff_y=maxpixelsy-diff_y;
        int dist=sqrt(diff_x*diff_x+diff_y*diff_y);
        if (dist<max_dist && next_i!=follow_ghost_num) { max_dist=dist; select_ghost=next_i;}
        if (dist<2000 && select_ghost!=0) i=number;
    }
    follow_ghost_num=select_ghost;
/*
    if (follow_ghost_num<number-1)
    {
        follow_ghost_num++;
    }
    else
    {
        follow_ghost_num=0;
    }
*/
//            long_jump=1;
    return;
}

void plot_some()
{
//    start_posx_mem=(picturex*1920-posx);
//    start_posy_mem=(picturey*1080-posy);
    float start_posx_mem=start_posx;
    float start_posy_mem=start_posy;

    render_picturex_mem=render_picturex;
    render_picturey_mem=render_picturey;
    render_posx_mem=render_posx;
    render_posy_mem=render_posy;

    picturex_mem=picturex;
    picturey_mem=picturey;
    posx_mem=posx;
    posy_mem=posy;

    float fposx_mem=fposx;
    float fposy_mem=fposy;

    if (plot_moviefile2==1 && live_movie2_is_mp3==0 && handler[MOVIE2_SELECT].show==1)
    {
//                rot_speed_movie2=0.0;
        if (movie2_move==1)
        {
            start_posx=movie2_posx-1920/2+(int)texture_from_movie2_new.getSize().x/2;
            start_posy=movie2_posy-1080/2+(int)texture_from_movie2_new.getSize().y/2;

            if ((start_posx)>=maxpixelsx)
                start_posx=start_posx-maxpixelsx;
            else if ((start_posx)<0)
                start_posx=start_posx+maxpixelsx;
            if ((start_posy)>=maxpixelsy)
                start_posy=start_posy-maxpixelsy;
            else if ((start_posy)<0)
                start_posy=start_posy+maxpixelsy;

            home_map();
            render_picturex=picturex;
            render_posx=posx;
            render_picturey=picturey;
            render_posy=posy;
        }
        plot_moviefile2=1;
        plotplot();
    }

    if (plot_ffmpegfile>0 && handler[FFMPEG_SELECT].show==1)
    {
        if (ffmpeg_move==1)
        {
//expand
//                ffmpeg_posx=-render_posx+render_picturex*1920+(1920/2) -sprite_from_ffmpeg.getTextureRect().width/2;
//                ffmpeg_posy=-render_posy+render_picturey*1080+(1080/2) -sprite_from_ffmpeg.getTextureRect().height/2;


//            start_posx=ffmpeg_posx-1920/2;
//            start_posy=ffmpeg_posy-1080/2;
            start_posx=ffmpeg_posx-1920/2+(int)texture_from_ffmpeg.getSize().x/2;
            start_posy=ffmpeg_posy-1080/2+(int)texture_from_ffmpeg.getSize().y/2;

            if ((start_posx)>=maxpixelsx)
                start_posx=start_posx-maxpixelsx;
            else if ((start_posx)<0)
                start_posx=start_posx+maxpixelsx;
            if ((start_posy)>=maxpixelsy)
                start_posy=start_posy-maxpixelsy;
            else if ((start_posy)<0)
                start_posy=start_posy+maxpixelsy;

            home_map();
            render_picturex=picturex;
            render_posx=posx;
            render_picturey=picturey;
            render_posy=posy;
//extern void ReadBitmaps4();
//            ReadBitmaps4();
        }
        if (plot_ffmpegfile==1)
            plotplot();
    }

    if (plot_internetfile==1 && handler[INTERNET_SELECT].show==1)
    {
//                rot_speed_internet=0.0;
        if (internet_move==1)
        {
            start_posx=internet_posx-1920/2+(int)texture_from_internet.getSize().x/2;
            start_posy=internet_posy-1080/2+(int)texture_from_internet.getSize().y/2;

            if ((start_posx)>=maxpixelsx)
                start_posx=start_posx-maxpixelsx;
            else if ((start_posx)<0)
                start_posx=start_posx+maxpixelsx;
            if ((start_posy)>=maxpixelsy)
                start_posy=start_posy-maxpixelsy;
            else if ((start_posy)<0)
                start_posy=start_posy+maxpixelsy;

            home_map();
            render_picturex=picturex;
            render_posx=posx;
            render_picturey=picturey;
            render_posy=posy;
        }
        plot_internetfile=1;
        plotplot();
    }

    if (plot_moviefile==1 && live_movie_is_mp3==0 && handler[MOVIE_SELECT].show==1)
    {
        if (movie_move==1)
        {
            start_posx=movie_posx-1920/2+(int)texture_from_movie_new.getSize().x/2;
            start_posy=movie_posy-1080/2+(int)texture_from_movie_new.getSize().y/2;;

            if ((start_posx)>=maxpixelsx)
                start_posx=start_posx-maxpixelsx;
            else if ((start_posx)<0)
                start_posx=start_posx+maxpixelsx;
            if ((start_posy)>=maxpixelsy)
                start_posy=start_posy-maxpixelsy;
            else if ((start_posy)<0)
                start_posy=start_posy+maxpixelsy;

            home_map();
            render_picturex=picturex;
            render_posx=posx;
            render_picturey=picturey;
            render_posy=posy;
        }
        plot_moviefile=1;
        plotplot();
    }

    start_posx=start_posx_mem;
    start_posy=start_posy_mem;

    render_picturex=render_picturex_mem;
    render_picturey=render_picturey_mem;
    render_posx=render_posx_mem;
    render_posy=render_posy_mem;

    picturex=picturex_mem;
    picturey=picturey_mem;
    posx=posx_mem;
    posy=posy_mem;
    fposx=fposx_mem;
    fposy=fposy_mem;
}

void f8_repeater()
{
    float start_posx_mem=start_posx;
    float start_posy_mem=start_posy;
//    start_posx_mem=(picturex*1920-posx);
//    start_posy_mem=(picturey*1080-posy);

    int render_picturex_mem=render_picturex;
    int render_picturey_mem=render_picturey;
    int render_posx_mem=render_posx;
    int render_posy_mem=render_posy;

    int picturex_mem=picturex;
    int picturey_mem=picturey;
    int posx_mem=posx;
    int posy_mem=posy;
    float fposx_mem=fposx;
    float fposy_mem=fposy;

    if (movie2==0 && live_movie2_is_mp3==0 && handler[MOVIE2_SELECT].show)
    {
//                rot_speed_movie2=0.0;
        if (movie2_move==1)
        {
            start_posx=movie2_posx-1920/2+(int)texture_from_movie2_new.getSize().x/2;
            start_posy=movie2_posy-1080/2+(int)texture_from_movie2_new.getSize().y/2;

            if ((start_posx)>=maxpixelsx)
                start_posx=start_posx-maxpixelsx;
            else if ((start_posx)<0)
                start_posx=start_posx+maxpixelsx;
            if ((start_posy)>=maxpixelsy)
                start_posy=start_posy-maxpixelsy;
            else if ((start_posy)<0)
                start_posy=start_posy+maxpixelsy;

            home_map();
            render_picturex=picturex;
            render_posx=posx;
            render_picturey=picturey;
            render_posy=posy;
        }
        plot_moviefile2=1;
        plotplot();
    }

    if (ffmpegfile==0 && handler[FFMPEG_SELECT].show)
    {
        if (ffmpeg_move==1)
        {
            start_posx=ffmpeg_posx-1920/2+(int)texture_from_ffmpeg.getSize().x/2;
            start_posy=ffmpeg_posy-1080/2+(int)texture_from_ffmpeg.getSize().y/2;

            if ((start_posx)>=maxpixelsx)
                start_posx=start_posx-maxpixelsx;
            else if ((start_posx)<0)
                start_posx=start_posx+maxpixelsx;
            if ((start_posy)>=maxpixelsy)
                start_posy=start_posy-maxpixelsy;
            else if ((start_posy)<0)
                start_posy=start_posy+maxpixelsy;

            home_map();
            render_picturex=picturex;
            render_posx=posx;
            render_picturey=picturey;
            render_posy=posy;
        }
        plot_ffmpegfile=1;
        plotplot();
    }

    if (internetfile==0 && handler[INTERNET_SELECT].show)
    {
//                rot_speed_internet=0.0;
        if (internet_move==1)
        {
            start_posx=internet_posx-1920/2+(int)texture_from_internet.getSize().x/2;
            start_posy=internet_posy-1080/2+(int)texture_from_internet.getSize().y/2;

            if ((start_posx)>=maxpixelsx)
                start_posx=start_posx-maxpixelsx;
            else if ((start_posx)<0)
                start_posx=start_posx+maxpixelsx;
            if ((start_posy)>=maxpixelsy)
                start_posy=start_posy-maxpixelsy;
            else if ((start_posy)<0)
                start_posy=start_posy+maxpixelsy;

            home_map();
            render_picturex=picturex;
            render_posx=posx;
            render_picturey=picturey;
            render_posy=posy;
        }
        plot_internetfile=1;
        plotplot();
    }

    if (movie==0 && live_movie_is_mp3==0 && handler[MOVIE_SELECT].show)
    {
        if (movie_move==1)
        {
            start_posx=movie_posx-1920/2+(int)texture_from_movie_new.getSize().x/2;
            start_posy=movie_posy-1080/2+(int)texture_from_movie_new.getSize().y/2;;

            if ((start_posx)>=maxpixelsx)
                start_posx=start_posx-maxpixelsx;
            else if ((start_posx)<0)
                start_posx=start_posx+maxpixelsx;
            if ((start_posy)>=maxpixelsy)
                start_posy=start_posy-maxpixelsy;
            else if ((start_posy)<0)
                start_posy=start_posy+maxpixelsy;

            home_map();
            render_picturex=picturex;
            render_posx=posx;
            render_picturey=picturey;
            render_posy=posy;
        }
        plot_moviefile=1;
        plotplot();
    }

    start_posx=start_posx_mem;
    start_posy=start_posy_mem;

    render_picturex=render_picturex_mem;
    render_picturey=render_picturey_mem;
    render_posx=render_posx_mem;
    render_posy=render_posy_mem;

    picturex=picturex_mem;
    picturey=picturey_mem;
    posx=posx_mem;
    posy=posy_mem;
    fposx=fposx_mem;
    fposy=fposy_mem;
}

void textfiles_to_screen(int font_size, sf::Color paint)
{
    int print_it;
    int name_num=0;
    char name[500];
    print_it=0;
    var_font=1;
//    int font_size=va_arg(args,int);
//    sf::Color paint=va_arg(args,sf::Color);
//    int font_size=60;
//    if (ffmpegfile==0) font_size=sprite_from_ffmpeg.getScale().x;
    sprite_from_ffmpeg.setScale(sf::Vector2f(1.0,1.0));
//            int type=sf::Text::Bold;
//            sf::Uint32 type=sf::Text::Bold;
    sf::Uint32 type=sf::Text::Regular;
    int end=0;
    int start=1;
    int x_position;
    int y_position;
    char line[2000]="";
    char line2[2000]="";
    char filename[1000];
    int next_file=1;
    int next_line=0;
    int niet_goed=1;
    int screen_x;
    int screen_y;
    int skippy=2;
//            ffmpeg_move=0;
//            size_ffmpeg=0;

//            x_position=0;
//            screen_x=x_position;
//            ffmpeg_move=1;

    x_position=1920/2;
    screen_x=x_position-1920/2;
    y_position=1080;
    screen_y=(-1080+font_size*3+maxpixelsy+y_position)%maxpixelsy;

    ffmpeg_move=0;
    size_ffmpeg=0;
    rotate_ffmpeg=0;

//            rotation_ffmpeg=0;

//            scale_now=1.0;

    picturex=screen_x/1920;
    render_picturex=picturex;
    posx=screen_x-1920*picturex;
    picturey=screen_y/1080;
    render_picturey=picturey;
    posy=screen_y-1080*picturey;
    posx=-posx;
    render_posx=posx;
    posy=-posy;
    render_posy=posy;
    fposx=posx;
    fposy=posy;
    ReadBitmaps2();
    ReadBitmaps4();

    ffmpeg_posx=x_position;
//            ffmpeg_posx=x_position+1920/2;
    ffmpeg_posy=y_position;

    strcpy(naam_from_file,"");

    if (file_is_open_line_from_file==1)
        fclose(file_from_file);
    file_is_open_line_from_file=0;
    max_line_from_file=0;

    next_textfile=0;
    total_textfile=0;
    start_textfile=1;

    while (niet_goed==1)
    {
        niet_goed=0;
        if (next_line<1 || start==1)
        {
            next_file=select_textfile(filename,".");
            if (next_file>0)
            {
                printf("Selected filename #%d from list.txt : %s\n",next_file,filename);
                print_it=0;
            }
            else if (next_file==0)
            {
                printf("list.txt is empty.\n");
                print_it=0;
            }
            else
            {
                printf("File list.txt end reached\n");
                niet_goed=1;
                print_it=0;
            }
            if (next_file==-1)
            {
                end=1;
//                        next_file=1;
//                        next_line=-1;
                break;
            }
        }
        int plot;
        plot=0;
        if (next_file>0 && next_line<1)
        {
//                    if (start==0) {
//                        y_position=y_position+font_size+4;
//                        screen_y=(-1080-font_size*3+maxpixelsy+y_position)%maxpixelsy;
//                        ffmpeg_posy=y_position;
//                        ffmpeg_posy=ffmpeg_posy+font_size+4;
//                    } else start=0;
//                    sprintf(line2,"FILE #%d : %s",next_file,filename); plot=1;
            print_it=0;
        }
        else if (next_file==0 && next_line<1)
        {
            sprintf(line2,"FILE LIST.TXT IS EMPTY");
            plot=0;
            print_it=0;
        }
        else if (next_file==-1)
        {
            sprintf(line2,"END OF LIST.TXT REACHED");
            plot=0;
            print_it=0;
        }
        else if (next_line>0)
        {
            sprintf(line2,"%s",line);
            plot=1;
//                    sprintf(line2,"%6d : %s",next_line,line); plot=1;
        }
        else if (next_line==0)
        {
            sprintf(line2,"FILE #%d : %s IS EMPTY",next_file,filename);
            plot=0;
            print_it=0;
        }
        else if (next_line<0 && niet_goed==1)
        {
            sprintf(line2,"END OF FILE #%d : %s",next_file,filename);
            plot=0;
            print_it=0;
        }
        if (plot==1 && end==0 && start==0 && print_it==1 && skippy==0)
        {
            print_it=0;
            y_position=y_position+font_size+4;
            screen_y=(-1080+font_size*3+maxpixelsy+y_position)%maxpixelsy;
            ffmpeg_posy=y_position;
//                    x_position=x_position+200;
//                    screen_x=(x_position+200+maxpixelsx)%maxpixelsx;


            picturex=screen_x/1920;
            render_picturex=picturex;
            posx=screen_x-1920*picturex;
            picturey=screen_y/1080;
            render_picturey=picturey;
            posy=screen_y-1080*picturey;
            posx=-posx;
            render_posx=posx;
            posy=-posy;
            render_posy=posy;

            text_to_ffmpeg_w( (wchar_t *) line_w,font_size,paint,sf::Color(10,10,10,255),type);
            if (combine==1)
            {
                sprintf(name,"%s/%dx%d/%03d/text%09d.png",LEVELDIR,BITMAPSX,BITMAPSY,level,name_num);
                texture_from_ffmpeg.copyToImage().saveToFile(name);
                name_num++;
            }

//            ffmpeg_posx=screen_x+1920/2-(int)(texture_from_ffmpeg.getSize().x/2);

            int start_posx_mem=(picturex*1920-posx);
            int start_posy_mem=(picturey*1080-posy);

            int render_picturex_mem=render_picturex;
            int render_picturey_mem=render_picturey;
            int render_posx_mem=render_posx;
            int render_posy_mem=render_posy;

            int picturex_mem=picturex;
            int picturey_mem=picturey;
            int posx_mem=posx;
            int posy_mem=posy;

            start_posx=ffmpeg_posx-1920/2+(int)(texture_from_ffmpeg.getSize().x/2);
            start_posy=ffmpeg_posy-1080/2+(int)(texture_from_ffmpeg.getSize().y/2);
//                    start_posx=ffmpeg_posx-1920/2;
//                    start_posy=ffmpeg_posy-1080/2;

            if ((start_posx)>=maxpixelsx)
                start_posx=start_posx-maxpixelsx;
            else if ((start_posx)<0)
                start_posx=start_posx+maxpixelsx;
            if ((start_posy)>=maxpixelsy)
                start_posy=start_posy-maxpixelsy;
            else if ((start_posy)<0)
                start_posy=start_posy+maxpixelsy;

            home_map();
            render_picturex=picturex;
            render_posx=posx;
            render_picturey=picturey;
            render_posy=posy;

            perform_quit=1;
            setffmpegfile();
            plot_ffmpegfile=1;
            plot_some();
            perform_quit=0;

            start_posx=start_posx_mem;
            start_posy=start_posy_mem;

            render_picturex=render_picturex_mem;
            render_picturey=render_picturey_mem;
            render_posx=render_posx_mem;
            render_posy=render_posy_mem;

            picturex=picturex_mem;
            picturey=picturey_mem;
            posx=posx_mem;
            posy=posy_mem;

            blitter("",1);
            if (y_position>=maxpixelsy)
            {
                strcpy(error_msg4,"END OF SCREEN REACHED, ABORTING");
                printf("%s\n",error_msg4);
                error_flag4=1;
                break;
            }
            if (end==1)
            {
                strcpy(error_msg4,"END OF LIST.TXT, ABORTING");
                printf("%s\n",error_msg4);
                error_flag4=1;
                break;
            }
            if (next_file==-1 && next_line<1)
            {
                strcpy(error_msg4,"END OF LIST.TXT REACHED, READY");
                printf("%s\n",error_msg4);
                error_flag4=1;
                break;
            }
            if (ESCAPE==1)
            {
                strcpy(error_msg4,"ESCAPE PRESSED, ABORTING");
                printf("%s\n",error_msg4);
                error_flag4=1;
                goexit=0;
                break;
            }
            if (next_file>0 && next_line<1)
            {
//                        ffmpeg_posy=ffmpeg_posy+font_size+4;
//                        y_position+=font_size+4;
            }
        }
        start=0;

        if (next_file>0)
        {
            static int old_line=0;

            next_line=select_line_from_file_w(line,filename);
//                    next_line=select_nextline(line,filename);
            if (next_line>0)
            {
//                        printf("pos: %d,%d -> Selected line #%d from %s : %s",ffmpeg_posx,ffmpeg_posy,next_line,filename,line);
                niet_goed=1;
                print_it=1;
                if (skippy>0)
                    skippy--;
            }
            else if (next_line==0)
            {
                printf("File %s is empty.\n",filename);
                sprintf(line,"File %s is empty.",filename);
                niet_goed=1;
            }
            else
            {
                printf("\nFile %s end reached.\n",filename);
                niet_goed=1;
            }
        }
        kiki();
    }
    ffmpegfile=1;
    ffmpeg_move=0;
    size_ffmpeg=0;
    forced_jump=1;
    follow_ghost_pos();
    ReadBitmaps2();
    ReadBitmaps4();
}



int testit()
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE)
    {
        return GetLastError();
    }

    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode))
    {
        return GetLastError();
    }

    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    if (!SetConsoleMode(hOut, dwMode))
    {
        return GetLastError();
    }

//    wprintf(L"\x1b[31mThis text has a red foreground using SGR.31.\r\n");
//    wprintf(L"\x1b[1mThis text has a bright (bold) red foreground using SGR.1 to affect the previous color setting.\r\n");
//    wprintf(L"\x1b[mThis text has returned to default colors using SGR.0 implicitly.\r\n");
//    wprintf(L"\x1b[34;46mThis text shows the foreground and background change at the same time.\r\n");
//    wprintf(L"\x1b[0mThis text has returned to default colors using SGR.0 explicitly.\r\n");
//    wprintf(L"\x1b[31;32;33;34;35;36;101;102;103;104;105;106;107mThis text attempts to apply many colors in the same command. Note the colors are applied from left to right so only the right-most option of foreground cyan (SGR.36) and background bright white (SGR.107) is effective.\r\n");
//    wprintf(L"\x1b[39mThis text has restored the foreground color only.\r\n");
//    wprintf(L"\x1b[49mThis text has restored the background color only.\r\n");

    return 0;
}
struct table_struct
{
    char sfml_name[20];
    int sfml_key;
    char sfml_desc[80];

};

struct table_struct elem[110];

void key_to_sfml()
{
    int first=1;
    if (first==1)
    {
        first=0;
        strcpy(elem[sf::Keyboard::Key::A        ].sfml_name,"A");
        strcpy(elem[sf::Keyboard::Key::A        ].sfml_desc,"The A key");
        strcpy(elem[sf::Keyboard::Key::B        ].sfml_name,"B");
        strcpy(elem[sf::Keyboard::Key::B        ].sfml_desc,"The B key");
        strcpy(elem[sf::Keyboard::Key::C        ].sfml_name,"C");
        strcpy(elem[sf::Keyboard::Key::C        ].sfml_desc,"The C key");
        strcpy(elem[sf::Keyboard::Key::D        ].sfml_name,"D");
        strcpy(elem[sf::Keyboard::Key::D        ].sfml_desc,"The D key");
        strcpy(elem[sf::Keyboard::Key::E        ].sfml_name,"E");
        strcpy(elem[sf::Keyboard::Key::E        ].sfml_desc,"The E key");
        strcpy(elem[sf::Keyboard::Key::F        ].sfml_name,"F");
        strcpy(elem[sf::Keyboard::Key::F        ].sfml_desc,"The F key");
        strcpy(elem[sf::Keyboard::Key::G        ].sfml_name,"G");
        strcpy(elem[sf::Keyboard::Key::G        ].sfml_desc,"The G key");
        strcpy(elem[sf::Keyboard::Key::H        ].sfml_name,"H");
        strcpy(elem[sf::Keyboard::Key::H        ].sfml_desc,"The H key");
        strcpy(elem[sf::Keyboard::Key::I        ].sfml_name,"I");
        strcpy(elem[sf::Keyboard::Key::I        ].sfml_desc,"The I key");
        strcpy(elem[sf::Keyboard::Key::J        ].sfml_name,"J");
        strcpy(elem[sf::Keyboard::Key::J        ].sfml_desc,"The J key");
        strcpy(elem[sf::Keyboard::Key::K        ].sfml_name,"K");
        strcpy(elem[sf::Keyboard::Key::K        ].sfml_desc,"The K key");
        strcpy(elem[sf::Keyboard::Key::L        ].sfml_name,"L");
        strcpy(elem[sf::Keyboard::Key::L        ].sfml_desc,"The L key");
        strcpy(elem[sf::Keyboard::Key::M        ].sfml_name,"M");
        strcpy(elem[sf::Keyboard::Key::M        ].sfml_desc,"The M key");
        strcpy(elem[sf::Keyboard::Key::N        ].sfml_name,"N");
        strcpy(elem[sf::Keyboard::Key::N        ].sfml_desc,"The N key");
        strcpy(elem[sf::Keyboard::Key::O        ].sfml_name,"O");
        strcpy(elem[sf::Keyboard::Key::O        ].sfml_desc,"The O key");
        strcpy(elem[sf::Keyboard::Key::P        ].sfml_name,"P");
        strcpy(elem[sf::Keyboard::Key::P        ].sfml_desc,"The P key");
        strcpy(elem[sf::Keyboard::Key::Q        ].sfml_name,"Q");
        strcpy(elem[sf::Keyboard::Key::Q        ].sfml_desc,"The Q key");
        strcpy(elem[sf::Keyboard::Key::R        ].sfml_name,"R");
        strcpy(elem[sf::Keyboard::Key::R        ].sfml_desc,"The R key");
        strcpy(elem[sf::Keyboard::Key::S        ].sfml_name,"S");
        strcpy(elem[sf::Keyboard::Key::S        ].sfml_desc,"The S key");
        strcpy(elem[sf::Keyboard::Key::T        ].sfml_name,"T");
        strcpy(elem[sf::Keyboard::Key::T        ].sfml_desc,"The T key");
        strcpy(elem[sf::Keyboard::Key::U        ].sfml_name,"U");
        strcpy(elem[sf::Keyboard::Key::U        ].sfml_desc,"The U key");
        strcpy(elem[sf::Keyboard::Key::V        ].sfml_name,"V");
        strcpy(elem[sf::Keyboard::Key::V        ].sfml_desc,"The V key");
        strcpy(elem[sf::Keyboard::Key::W        ].sfml_name,"W");
        strcpy(elem[sf::Keyboard::Key::W        ].sfml_desc,"The W key");
        strcpy(elem[sf::Keyboard::Key::X        ].sfml_name,"X");
        strcpy(elem[sf::Keyboard::Key::X        ].sfml_desc,"The X key");
        strcpy(elem[sf::Keyboard::Key::Y        ].sfml_name,"Y");
        strcpy(elem[sf::Keyboard::Key::Y        ].sfml_desc,"The Y key");
        strcpy(elem[sf::Keyboard::Key::Z        ].sfml_name,"Z");
        strcpy(elem[sf::Keyboard::Key::Z        ].sfml_desc,"The Z key");
        strcpy(elem[sf::Keyboard::Key::Num0     ].sfml_name,"Num0");
        strcpy(elem[sf::Keyboard::Key::Num0     ].sfml_desc,"The 0 key");
        strcpy(elem[sf::Keyboard::Key::Num1     ].sfml_name,"Num1");
        strcpy(elem[sf::Keyboard::Key::Num1     ].sfml_desc,"The 1 key");
        strcpy(elem[sf::Keyboard::Key::Num2     ].sfml_name,"Num2");
        strcpy(elem[sf::Keyboard::Key::Num2     ].sfml_desc,"The 2 key");
        strcpy(elem[sf::Keyboard::Key::Num3     ].sfml_name,"Num3");
        strcpy(elem[sf::Keyboard::Key::Num3     ].sfml_desc,"The 3 key");
        strcpy(elem[sf::Keyboard::Key::Num4     ].sfml_name,"Num4");
        strcpy(elem[sf::Keyboard::Key::Num4     ].sfml_desc,"The 4 key");
        strcpy(elem[sf::Keyboard::Key::Num5     ].sfml_name,"Num5");
        strcpy(elem[sf::Keyboard::Key::Num5     ].sfml_desc,"The 5 key");
        strcpy(elem[sf::Keyboard::Key::Num6     ].sfml_name,"Num6");
        strcpy(elem[sf::Keyboard::Key::Num6     ].sfml_desc,"The 6 key");
        strcpy(elem[sf::Keyboard::Key::Num7     ].sfml_name,"Num7");
        strcpy(elem[sf::Keyboard::Key::Num7     ].sfml_desc,"The 7 key");
        strcpy(elem[sf::Keyboard::Key::Num8     ].sfml_name,"Num8");
        strcpy(elem[sf::Keyboard::Key::Num8     ].sfml_desc,"The 8 key");
        strcpy(elem[sf::Keyboard::Key::Num9     ].sfml_name,"Num9");
        strcpy(elem[sf::Keyboard::Key::Num9     ].sfml_desc,"The 9 key");
        strcpy(elem[sf::Keyboard::Key::Escape   ].sfml_name,"Escape");
        strcpy(elem[sf::Keyboard::Key::Escape   ].sfml_desc,"The Escape key");
        strcpy(elem[sf::Keyboard::Key::LControl ].sfml_name,"LControl");
        strcpy(elem[sf::Keyboard::Key::LControl ].sfml_desc,"The left Control key");
        strcpy(elem[sf::Keyboard::Key::LShift   ].sfml_name,"LShift");
        strcpy(elem[sf::Keyboard::Key::LShift   ].sfml_desc,"The left Shift key");
        strcpy(elem[sf::Keyboard::Key::LAlt     ].sfml_name,"LAlt");
        strcpy(elem[sf::Keyboard::Key::LAlt     ].sfml_desc,"The left Alt key");
        strcpy(elem[sf::Keyboard::Key::LSystem  ].sfml_name,"LSystem");
        strcpy(elem[sf::Keyboard::Key::LSystem  ].sfml_desc,"The left OS specific key: window (Windows and Linux), apple (MacOS X), ...");
        strcpy(elem[sf::Keyboard::Key::RControl ].sfml_name,"RControl");
        strcpy(elem[sf::Keyboard::Key::RControl ].sfml_desc,"The right Control key");
        strcpy(elem[sf::Keyboard::Key::RShift   ].sfml_name,"RShift");
        strcpy(elem[sf::Keyboard::Key::RShift   ].sfml_desc,"The right Shift key");
        strcpy(elem[sf::Keyboard::Key::RAlt     ].sfml_name,"RAlt");
        strcpy(elem[sf::Keyboard::Key::RAlt     ].sfml_desc,"The right Alt key");
        strcpy(elem[sf::Keyboard::Key::RSystem  ].sfml_name,"RSystem");
        strcpy(elem[sf::Keyboard::Key::RSystem  ].sfml_desc,"The right OS specific key: window (Windows and Linux), apple (MacOS X), ...");
        strcpy(elem[sf::Keyboard::Key::Menu     ].sfml_name,"Menu");
        strcpy(elem[sf::Keyboard::Key::Menu     ].sfml_desc,"The Menu key");
        strcpy(elem[sf::Keyboard::Key::LBracket ].sfml_name,"LBracket");
        strcpy(elem[sf::Keyboard::Key::LBracket ].sfml_desc,"The [ key");
        strcpy(elem[sf::Keyboard::Key::RBracket ].sfml_name,"RBracket");
        strcpy(elem[sf::Keyboard::Key::RBracket ].sfml_desc,"The ] key");
        strcpy(elem[sf::Keyboard::Key::Semicolon].sfml_name,"Semicolon");
        strcpy(elem[sf::Keyboard::Key::Semicolon].sfml_desc,"The ; key");
        strcpy(elem[sf::Keyboard::Key::Comma    ].sfml_name,"Comma");
        strcpy(elem[sf::Keyboard::Key::Comma    ].sfml_desc,"The , key");
        strcpy(elem[sf::Keyboard::Key::Period   ].sfml_name,"Period");
        strcpy(elem[sf::Keyboard::Key::Period   ].sfml_desc,"The . key");
        strcpy(elem[sf::Keyboard::Key::Quote    ].sfml_name,"Quote");
        strcpy(elem[sf::Keyboard::Key::Quote    ].sfml_desc,"The ' key");
        strcpy(elem[sf::Keyboard::Key::Slash    ].sfml_name,"Slash");
        strcpy(elem[sf::Keyboard::Key::Slash    ].sfml_desc,"The / key");
        strcpy(elem[sf::Keyboard::Key::Backslash].sfml_name,"Backslash");
        strcpy(elem[sf::Keyboard::Key::Backslash].sfml_desc,"The \ key");
        strcpy(elem[sf::Keyboard::Key::Tilde    ].sfml_name,"Tilde");
        strcpy(elem[sf::Keyboard::Key::Tilde    ].sfml_desc,"The ~ key");
        strcpy(elem[sf::Keyboard::Key::Equal    ].sfml_name,"Equal");
        strcpy(elem[sf::Keyboard::Key::Equal    ].sfml_desc,"The = key");
        strcpy(elem[sf::Keyboard::Key::Hyphen   ].sfml_name,"Hyphen");
        strcpy(elem[sf::Keyboard::Key::Hyphen   ].sfml_desc,"The - key (hyphen)");
        strcpy(elem[sf::Keyboard::Key::Space    ].sfml_name,"Space");
        strcpy(elem[sf::Keyboard::Key::Space    ].sfml_desc,"The Space key");
        strcpy(elem[sf::Keyboard::Key::Enter    ].sfml_name,"Enter");
        strcpy(elem[sf::Keyboard::Key::Enter    ].sfml_desc,"The Enter/Return keys");
        strcpy(elem[sf::Keyboard::Key::Backspace].sfml_name,"Backspace");
        strcpy(elem[sf::Keyboard::Key::Backspace].sfml_desc,"The Backspace key");
        strcpy(elem[sf::Keyboard::Key::Tab      ].sfml_name,"Tab");
        strcpy(elem[sf::Keyboard::Key::Tab      ].sfml_desc,"The Tabulation key");
        strcpy(elem[sf::Keyboard::Key::PageUp   ].sfml_name,"PageUp");
        strcpy(elem[sf::Keyboard::Key::PageUp   ].sfml_desc,"The Page up key");
        strcpy(elem[sf::Keyboard::Key::PageDown ].sfml_name,"PageDown");
        strcpy(elem[sf::Keyboard::Key::PageDown ].sfml_desc,"The Page down key");
        strcpy(elem[sf::Keyboard::Key::End      ].sfml_name,"End");
        strcpy(elem[sf::Keyboard::Key::End      ].sfml_desc,"The End key");
        strcpy(elem[sf::Keyboard::Key::Home     ].sfml_name,"Home");
        strcpy(elem[sf::Keyboard::Key::Home     ].sfml_desc,"The Home key");
        strcpy(elem[sf::Keyboard::Key::Insert   ].sfml_name,"Insert");
        strcpy(elem[sf::Keyboard::Key::Insert   ].sfml_desc,"The Insert key");
        strcpy(elem[sf::Keyboard::Key::Delete   ].sfml_name,"Delete");
        strcpy(elem[sf::Keyboard::Key::Delete   ].sfml_desc,"The Delete key");
        strcpy(elem[sf::Keyboard::Key::Add      ].sfml_name,"Add");
        strcpy(elem[sf::Keyboard::Key::Add      ].sfml_desc,"The + key");
        strcpy(elem[sf::Keyboard::Key::Subtract ].sfml_name,"Subtract");
        strcpy(elem[sf::Keyboard::Key::Subtract ].sfml_desc,"The - key (minus, usually from numpad)");
        strcpy(elem[sf::Keyboard::Key::Multiply ].sfml_name,"Multiply");
        strcpy(elem[sf::Keyboard::Key::Multiply ].sfml_desc,"The * key");
        strcpy(elem[sf::Keyboard::Key::Divide   ].sfml_name,"Divide");
        strcpy(elem[sf::Keyboard::Key::Divide   ].sfml_desc,"The / key");
        strcpy(elem[sf::Keyboard::Key::Left     ].sfml_name,"Left");
        strcpy(elem[sf::Keyboard::Key::Left     ].sfml_desc,"Left arrow");
        strcpy(elem[sf::Keyboard::Key::Right    ].sfml_name,"Right");
        strcpy(elem[sf::Keyboard::Key::Right    ].sfml_desc,"Right arrow");
        strcpy(elem[sf::Keyboard::Key::Up       ].sfml_name,"Up");
        strcpy(elem[sf::Keyboard::Key::Up       ].sfml_desc,"Up arrow");
        strcpy(elem[sf::Keyboard::Key::Down     ].sfml_name,"Down");
        strcpy(elem[sf::Keyboard::Key::Down     ].sfml_desc,"Down arrow");
        strcpy(elem[sf::Keyboard::Key::Numpad0  ].sfml_name,"Numpad0");
        strcpy(elem[sf::Keyboard::Key::Numpad0  ].sfml_desc,"The numpad 0 key");
        strcpy(elem[sf::Keyboard::Key::Numpad1  ].sfml_name,"Numpad1");
        strcpy(elem[sf::Keyboard::Key::Numpad1  ].sfml_desc,"The numpad 1 key");
        strcpy(elem[sf::Keyboard::Key::Numpad2  ].sfml_name,"Numpad2");
        strcpy(elem[sf::Keyboard::Key::Numpad2  ].sfml_desc,"The numpad 2 key");
        strcpy(elem[sf::Keyboard::Key::Numpad3  ].sfml_name,"Numpad3");
        strcpy(elem[sf::Keyboard::Key::Numpad3  ].sfml_desc,"The numpad 3 key");
        strcpy(elem[sf::Keyboard::Key::Numpad4  ].sfml_name,"Numpad4");
        strcpy(elem[sf::Keyboard::Key::Numpad4  ].sfml_desc,"The numpad 4 key");
        strcpy(elem[sf::Keyboard::Key::Numpad5  ].sfml_name,"Numpad5");
        strcpy(elem[sf::Keyboard::Key::Numpad5  ].sfml_desc,"The numpad 5 key");
        strcpy(elem[sf::Keyboard::Key::Numpad6  ].sfml_name,"Numpad6");
        strcpy(elem[sf::Keyboard::Key::Numpad6  ].sfml_desc,"The numpad 6 key");
        strcpy(elem[sf::Keyboard::Key::Numpad7  ].sfml_name,"Numpad7");
        strcpy(elem[sf::Keyboard::Key::Numpad7  ].sfml_desc,"The numpad 7 key");
        strcpy(elem[sf::Keyboard::Key::Numpad8  ].sfml_name,"Numpad8");
        strcpy(elem[sf::Keyboard::Key::Numpad8  ].sfml_desc,"The numpad 8 key");
        strcpy(elem[sf::Keyboard::Key::Numpad9  ].sfml_name,"Numpad9");
        strcpy(elem[sf::Keyboard::Key::Numpad9  ].sfml_desc,"The numpad 9 key");
        strcpy(elem[sf::Keyboard::Key::F1       ].sfml_name,"F1");
        strcpy(elem[sf::Keyboard::Key::F1       ].sfml_desc,"The F1 key");
        strcpy(elem[sf::Keyboard::Key::F2       ].sfml_name,"F2");
        strcpy(elem[sf::Keyboard::Key::F2       ].sfml_desc,"The F2 key");
        strcpy(elem[sf::Keyboard::Key::F3       ].sfml_name,"F3");
        strcpy(elem[sf::Keyboard::Key::F3       ].sfml_desc,"The F3 key");
        strcpy(elem[sf::Keyboard::Key::F4       ].sfml_name,"F4");
        strcpy(elem[sf::Keyboard::Key::F4       ].sfml_desc,"The F4 key");
        strcpy(elem[sf::Keyboard::Key::F5       ].sfml_name,"F5");
        strcpy(elem[sf::Keyboard::Key::F5       ].sfml_desc,"The F5 key");
        strcpy(elem[sf::Keyboard::Key::F6       ].sfml_name,"F6");
        strcpy(elem[sf::Keyboard::Key::F6       ].sfml_desc,"The F6 key");
        strcpy(elem[sf::Keyboard::Key::F7       ].sfml_name,"F7");
        strcpy(elem[sf::Keyboard::Key::F7       ].sfml_desc,"The F7 key");
        strcpy(elem[sf::Keyboard::Key::F8       ].sfml_name,"F8");
        strcpy(elem[sf::Keyboard::Key::F8       ].sfml_desc,"The F8 key");
        strcpy(elem[sf::Keyboard::Key::F9       ].sfml_name,"F9");
        strcpy(elem[sf::Keyboard::Key::F9       ].sfml_desc,"The F9 key");
        strcpy(elem[sf::Keyboard::Key::F10      ].sfml_name,"F10");
        strcpy(elem[sf::Keyboard::Key::F10      ].sfml_desc,"The F10 key");
        strcpy(elem[sf::Keyboard::Key::F11      ].sfml_name,"F11");
        strcpy(elem[sf::Keyboard::Key::F11      ].sfml_desc,"The F11 key");
        strcpy(elem[sf::Keyboard::Key::F12      ].sfml_name,"F12");
        strcpy(elem[sf::Keyboard::Key::F12      ].sfml_desc,"The F12 key");
        strcpy(elem[sf::Keyboard::Key::F13      ].sfml_name,"F13");
        strcpy(elem[sf::Keyboard::Key::F13      ].sfml_desc,"The F13 key");
        strcpy(elem[sf::Keyboard::Key::F14      ].sfml_name,"F14");
        strcpy(elem[sf::Keyboard::Key::F14      ].sfml_desc,"The F14 key");
        strcpy(elem[sf::Keyboard::Key::F15      ].sfml_name,"F15");
        strcpy(elem[sf::Keyboard::Key::F15      ].sfml_desc,"The F15 key");
        strcpy(elem[sf::Keyboard::Key::Pause    ].sfml_name,"Pause");
        strcpy(elem[sf::Keyboard::Key::Pause    ].sfml_desc,"The Pause key");
    }
}

int first_dot=1;
extern int NO_RECT=0;

void plot_dot(int x, int y, int col) {
//    static sf::Texture my_text;
    static sf::Texture my_dot[8];
    x=(x+maxpixelsx)%maxpixelsx;
    y=(y+maxpixelsy)%maxpixelsy;
    if (first_dot==1) {
        my_dot[0].loadFromFile("resources/dot0.png");
        my_dot[1].loadFromFile("resources/dot1.png");
        my_dot[2].loadFromFile("resources/dot2.png");
        my_dot[3].loadFromFile("resources/dot3.png");
        my_dot[4].loadFromFile("resources/dot4.png");
        my_dot[5].loadFromFile("resources/dot5.png");
        my_dot[6].loadFromFile("resources/dot6.png");
        my_dot[7].loadFromFile("resources/dot7.png");

        scale_now=1.0;
//        size_ffmpeg=1;
        first_dot=0;
        rotate_ffmpeg=0;
        rotation_ffmpeg=0;
        sprite_from_ffmpeg.setScale(1,1);
        sprite_from_ffmpeg.rotate(0);
        texture_from_ffmpeg.setRepeated(FALSE);
        rot_speed_ffmpeg=0.0;
        handler[FFMPEG_SELECT].blending=0;
        handler[FFMPEG_SELECT].plot_front=0;
        handler[FFMPEG_SELECT].show=1;
        handler[FFMPEG_SELECT].tile=0;
        handler[FFMPEG_SELECT].shader=1;
//        ffmpeg_move=1;
    }
//    sprite_from_ffmpeg.setTextureRect( {col*8,0,8,8 } );
//    sprite_from_ffmpeg.setTexture(my_dot[col],true);

    sf::Texture old=texture_from_ffmpeg;
    texture_from_ffmpeg=my_dot[col];
    ffmpeg_move=1;
//    size_ffmpeg=0;
    ffmpeg_posx=x-4;
    ffmpeg_posy=y-4;

    ffmpegfile=0;
    plot_ffmpegfile=1;
//    NO_RECT=1;
    perform_quit=1;
    plot_some();
    perform_quit=0;
//    NO_RECT=0;
    ffmpegfile=1;
    texture_from_ffmpeg=old;
//    printf("x=%d y=%d col=%d\n",x,y,col);
}
