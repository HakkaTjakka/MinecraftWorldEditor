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
#include <sfeMovie/Movie.hpp>
#include "StreamSelector.hpp"
#include "MediaInfo.hpp"
#include "Effect.hpp"
#include <SFML/OpenGL.hpp>
#include <GL/glext.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include "keylist.hpp"
#define EVENT_ALT 1
#define EVENT_SHIFT 2
#define EVENT_CONTROL 4
#define EVENT_SYSTEM 8

#define KBQ_START 0x41E
#define KBQ_HEAD 0x41A
#define KBQ_TAIL 0x41C

#define FFMPEG_SELECT 0
#define INTERNET_SELECT 1
#define MOVIE_SELECT 2
#define MOVIE2_SELECT 3
#define CANVAS_SELECT 4

#include <glm/glm.hpp>
#include <glm/common.hpp>
#include <../VOXEL.HPP>
bool dont_slow_down=false;
extern int draw_model;
extern bool roelof;
extern bool screensaver;
extern void merge_back_to_front();
bool got_next=false;
extern bool voxel_to_file;
extern bool plot_only;
extern bool flushing;
extern bool burn;
extern sf::Clock kp;
extern sf::Mutex wierdo_mutex;
extern int active_window_num;
extern sf::RenderWindow* windows_3d[];
extern int is_activated_window[];
extern int bar_on[];
extern bool set_save;

extern void text_to_ffmpeg(char * in,int font_size, sf::Color inner, sf::Color outer);
extern sf::Color random_pixel;
extern int plot_all_factor;

extern std::vector<glm::ivec2> wierdo_requests_ready;
extern sf::RectangleShape rectangle_paper;
extern int paper_select;
void update_MC(sf::Image& image_local, int x, int y);
extern sf::Image scan_image;
extern int scan_x,scan_z;
int blocked_by_window=0;
extern sf::Mutex render_locker;
extern sf::Mutex render_locker2;
extern void expres(int objnum);
extern int ready_to_render[];
static int rendering=0;
int render_now=0;
void reset_all();
void read_one_plot(int x, int y, sf::Image* image);
extern sf::Image image_plot2;
extern int update_request;
extern int MCEDITOR_running;
extern int read_request;
extern sf::Image* read_image;
extern int read_x,read_y;
extern int happening;
static int happening_counter=0;
extern int jump_ready;
extern sf::Mutex MUTEX_MCEDITOR;
int jump_request=0;
int jump_x=0;
int jump_y=0;
extern int shut_up;
void plot_cubes_vertex();

float scale_now_adj=1.0;
float color_to_gradient();
extern int soft_jump;
extern void kiki();
void update_plot_all2(int plot_front);
void update_plot_all();
extern sf::Clock rec_clock_tot;
extern sf::Clock rec_clock_frame;
extern sf::Clock play_clock_tot;
extern sf::Clock play_clock_frame;
extern void test_write_to_and_read_from_memory();

extern float fps_record_tot;
extern float fps_record_frame;
extern float fps_playing_tot;
extern float fps_playing_frame;
extern int testing;
extern char recording_info_static[];

sf::Mutex burn_next_sub_ready_mutex;

struct pts_struct
{
    int var_font;
    char text_to_print[2000];
    int font_size;
    sf::Color paint_in;
    sf::Color paint_out;
    sf::Color paint_back;
    float outline;
    sf::Uint32 text_type;
};

extern struct pts_struct pts;
extern int playing_screen_num;
extern void disp_open();
extern void disp_close();
extern int sub_load_maze;
extern void start_burn_next_sub_thread();
extern int go_list;
extern int go_burn;
extern void loadmul();
extern void add_border_left_right(sf::Texture * MyTexture);
extern int kleur_back;
extern float recording_time;
extern void print_to_screen(int var_font, char * text_to_print, int font_size, sf::Color paint_in, sf::Color paint_out, sf::Color paint_back, float outline, sf::Uint32 text_type );
char * seconds_to_time(float finputSecond);
extern float playing_time;
extern char playing_info_static[];
std::vector<sf::Vector2i> to_plot;
extern int burn_subs;
extern int start_burning;
extern int go_download;
extern int burn_next_sub_ready;
extern void burn_next_sub();
extern int record_debug;
void plot_ghosts();
extern void do_the_recording_stuff();
extern void testit();
extern void read_keylist_hpp();
extern void RenderBlitg(int totalx,int totaly, int xdest, int ydest, int width, int height, int xsource, int ysource);
extern float fpstime_factor;
extern char going_to[];
extern void pacman_to_rel_pos();
extern void rel_pos_to_pacman();
extern void do_command(int what);
extern int DO_ADAPT;
extern int DO_ZOOM_IN;
extern int DO_ZOOM_OUT;
int no_scale=0;
extern float fspeed_ghost_all;
int move_slow=0;
extern int MUL_MATCH_LEVEL;
extern int loadallmaps;
extern int loadallmaps_level;
int dir_up=0;
int dir_down=0;
int dir_left=0;
int dir_right=0;
int dir_mid=0;
float fspeed_mem=4.0;
static float maze_size=0.0;
int eat_delay=0;
int eat_delay_mazemove_blokje;
int eat_delay_next_plot_blokje;
int eat_delay_mazemovex;
int eat_delay_mazemovey;
int eat_delay_mazemovex2;
int eat_delay_mazemovey2;
int eat_delay_next_plotx;
int eat_delay_next_ploty;
int recover=20;
extern int flippo;
extern int SAS_MAX_ZOOM;
extern int show_shade_map;
extern int mul;
extern int MUL_COUNTER;
extern int SAS_STARTX_a;
extern int SAS_STARTY_a;

extern int offset_picture_x;
extern int offset_picture_y;

extern sf::RenderTexture overlay;
extern std::vector<Effect*> effects;
extern std::size_t current ;
extern int set_transparant;
extern int skipclear;

extern float plot_all_znear;
extern float plot_all_zfar;
extern float plot_all_fovyInDegrees;

extern float plot_all_translate_x;
extern float plot_all_translate_y;
extern float plot_all_translate_z;
extern float plot_all_rotate_x;
extern float plot_all_rotate_y;
extern float plot_all_rotate_z;

float shader_map_angle=0.0;
int go_go=0;
int blendit=0;
int plot_all=0;
int plot_cubes=0;
extern void set_mapper();
extern void set_geometry();
extern int mappos_x,mappos_y;
extern void shader_map(int x,int y);

extern Effect* mapper_effect;
extern Effect* cube_effect;
//extern Effect* mapper_effect;

int crop_x=0;
int crop_x_size=0;
int crop_y_size=0;
int crop=0;

float the_time;

extern void goto_maze(int mazemovex, int mazemovey);
extern int maze_plotsizex;
extern int maze_plotsizey;

int adapt_maze=0;
extern void f8_repeater();
int f8_repeat=0;
int tune=1;
//utrecht
int rate=2;
int play_rate=2;
int rate_count=0;

extern double BYTES_DOWNLOADED;
int frame_counter=0;
int flop=0;
extern void playing_end();
extern void Screenget3();
extern int playing_start(char * filename);
extern void playing(sf::Image * image);

float new_scale;
float fspeed=1.0;

extern int movieextern;
int ffmpeg_recurse=0;

int selector=0;
int selector_item=0;
#define BLENDING_SELECT 0
#define PLOT_FRONT_SELECT 1
#define SHOW_SELECT 2
#define TILE_SELECT 3
#define SHADER_SELECT 4

struct handler_struct
{
    int blending=1;
    int plot_front=1;
    int show=1;
    int tile=0;
    int shader=1;
};
struct handler_struct handler[5];

float old_internet_scale=1.0;
void load_next_internet();
extern int exiting;
char send_message=0;
int monitor_loop=1;
extern int memory_set;
extern void launch_animator();
extern void terminate_animator();
extern int winmain_running;
extern sf::SoundBuffer buffer[10];
extern sf::Music music[10];
int taskbar=1;
extern int shaders();
extern int kill1,kill2,kill3;
extern int loader1_active;
extern int loader2_active;
extern int loader3_active;
int get_date_time(char * ret);
extern int helpme;
extern void kill_threads();
extern void kill_background_loader();

sf::Thread sub_thread_shaders(&shaders);
extern int kill1,kill2,kill3;
extern int loader1_active;
extern int loader2_active;
extern int loader3_active;
int get_date_time(char * ret);
extern sf::Mutex loader_mutex;
void text_to_ffmpeg(char * in, int font_size);

extern void font_to_ffmpeg();
extern void plot_some();
extern int scripting();
sf::Vector2i position=sf::Vector2i(960,540);
int forced_speed=0;
extern int pacman;
extern void set_print_text();
void set_mytext(int next_font);
void load_next_ffmpeg();
extern int background_loader;
extern int blank_maze;
extern void mydraw(char *towrite, int xpos, int ypos, sf::Color inner, sf::Color outer);
extern void mydraw2(char *towrite, int xpos, int ypos, sf::Color inner, sf::Color outer);
extern void make_text(int next_font);
extern int once;
extern double rel_pos_in_map_x;
extern double rel_pos_in_map_y;
int force_loading=0;
extern int window_1_active;
extern int window_2_active;
extern int window_3_active;
extern int ESCAPE;
extern double Fget_map_x,Fget_map_y;
extern int get_map_x,get_map_y,get_map_zoom;
extern int autodraw;
extern void set_smooth(int x,int y);
int rendered=1;
double slept=0.0;

extern void update_map(int totalx,int totaly);

int size_pointcloud=0;
extern sf::VertexArray m_pointCloud;
extern sf::VertexArray m_pointCloud3;
extern sf::VertexArray m_lineCloud3;


//sf::VertexArray m_hoppa(sf::Points,1);
//sf::VertexArray m_pointCloud_maps[2][2];
sf::VertexArray m_pointCloud_map0;
sf::VertexArray m_pointCloud_map1;

extern double avg_speedx;
extern double avg_speedy;
int cool=0;
extern int thread_run_sub;
extern double smooth_x;
extern double smooth_y;
extern sf::Color background_color[];
int monitor=0;
int monitor_off=1;
void MonitorMemory();
sf::Thread monimem(&MonitorMemory);
void check_memory();
int check_mem=0;
extern int mouse_move;
extern float scale_now;
extern void ghost_next();
int disp_text=0;
int LOADED_SEED=0;
int iFrame=0;
sf::Sprite *sprite_buffer;
int perform_quit=0;
int MAZEOFF=0;
int shade_map=0;
int shade_main=0;
int plot_shader=0;
int newmaze=0;
int difficulty=2;
float fpstime;
int fragment_shader=0;
int vertex_shader=0;
int buffer_shader=0;
float run_time;

sf::Shader shader_buffer;
sf::Shader picture_shader;
sf::RenderStates picture_states;
sf::RenderStates buffer_states;

extern void do_nextlevel();
int die=0;
int smooth=1;
//sf::RenderTexture GHOSTtexture;
//sf::Sprite GHOSTsprite;
int crossing=0;
extern int first1;
extern int first2;
extern void set_blending();
extern void movie_to_ffmpeg(sf::Texture * MyTexture_movie, sf::Texture * MyTexture_ffmpeg);
extern void convert_to_scale(sf::Texture * MyTexture,sf::Sprite * MySprite);
extern void soften_edge(sf::Texture * MyTexture);
extern void INIT_NETWORK();
extern void NETWORK_HANDLER2();
extern void SEND(char *towrite);
extern void terminate_thread();
int connected_ready=2;
int old_shift;
extern void get_ffmpegfile();
int mirror=0;
extern void do_mirror_sub(int mazemovex, int mazemovey);
extern void do_mirror(int mazemovex,int mazemovey,int blokje);
int blend_on_movie=0;
sf::RenderTexture tussen_texture;
sf::RenderTexture backup_texture;
sf::Sprite backup_sprite;
char movie_name[1000]="";
int reload;
int render_picturex_mem;
int render_picturey_mem;
int render_posx_mem;
int render_posy_mem;
int picturex_mem;
int picturey_mem;
int posx_mem;
int posy_mem;
int old_draw;
extern void Screenshot();
extern void plotplot();
extern void Screenshot3();
extern void Screenshot3_m_orig();
int reset_normal=0;
int size_internet=0;
int size_canvas=0;
int size_ffmpeg=0;
int size_movie=0;
int size_movie2=0;
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
extern int MyBlending;
extern int MyBlendMode_num;
extern int MyBlend_colorSrcFactor_num;
extern int MyBlend_colorDstFactor_num;
extern int MyBlend_colorEquation_num;
extern int MyBlend_alphaSrcFactor_num;
extern int MyBlend_alphaDstFactor_num;
extern int MyBlend_alphaEquation_num;
extern sf::BlendMode MyBlendingMode;
//extern sf::BlendMode MyBlendingMode_movie;
extern sf::BlendMode MyBlendMode[];
extern char * MyBlendMode_text[];
extern sf::BlendMode::Equation MyEquation[];
extern char * MyEquation_text[];
extern sf::BlendMode::Factor MyFactor[];
extern char * MyFactor_text[];
int start_posx_mem;
int start_posy_mem;
float rot_speed_movie=1.0;
float rot_speed_movie2=1.0;
float rot_speed_ffmpeg=1.0;
float rot_speed_internet=1.0;
float rot_speed_canvas=1.0;
float rotation_movie=0.0;
float rotation_movie2=0.0;
float rotation_ffmpeg=0.0;
float rotation_internet=0.0;
float rotation_canvas=0.0;
int live_movie_is_mp3=0;
int live_movie2_is_mp3=0;
int timer_movie;
sf::Time time_movie;
sf::Time time_ghost;
int timer_movie2;
sf::Time time_movie2;
extern int reload_init();
int recording_type=0;
extern void recording(sf::Image * image);
extern int recording_start(int x, int y);
extern void recording_end();
extern void recording_m_orig(sf::Image * image);
extern int recording_start_m_orig();
int record_pause=0;
int record_screen=0;
int record_screen_num=0;
struct stat stat_buffer;
int blending=0;
int PIXELISBLACKTHRESHOLD=10;
int PIXELISWHITETHRESHOLD=10;
int PIXELISCOLORTHRESHOLD=10;
int PIXELISCOLOR_R=255;
int PIXELISCOLOR_G=0;
int PIXELISCOLOR_B=0;
char SHADERDIR[2000];
char MACRODIR[2000];
char SCRIPTDIR[2000];
char MOVIEDIR[2000];
char LEVELDIR[2000];
char MAPDIR[2000];
char PICTUREDIR[2000];
char BLENDINGPICTUREDIR[2000];
char URLDIR[2000];
char FONTDIR[2000];
char FFMPEGCOMMAND_CROP[5000]="";
char FFMPEGCOMMAND_CROP_RGBA[5000]="";
char FFMPEGCOMMAND_SCREENSHOT[5000]="";
char FFMPEGCOMMAND[5000]="";
int RGBA=0;
char FFMPEGCOMMAND_RGBA[5000]="";
char FFMPEGCOMMANDIN[5000]="";
char FFMPEGCOMMANDIN_SUBS[5000]="";
char FFMPEGCOMMANDIN_SUBS_RES[5000]="";
char FFMPEGCOMMANDIN_FILTER_COMPLEX[5000]="";
char FFMPEGCOMMAND_BURN_SUBS[5000]="";
char FFMPEGCOMMAND_M_ORIG[5000]="";
char FFMPEGCOMMAND_M_ORIG_AUDIO[5000]="";

int movie_posx,movie_posy;
int movie2_posx,movie2_posy;
int ffmpeg_posx,ffmpeg_posy;
int internet_posx,internet_posy;
int movie_move=0;
int movie2_move=0;
int ffmpeg_move=0;
int internet_move=0;
int select_from_list(char *filename, char * path, int next);
int err_level=0;
sf::BlendMode MyBlend=sf::BlendNone;
int lookahead=0;
int force_game=1;
int loadbackground=1;
int plot_front=1,plot_back=0;
int internetfile=1;
int ffmpegfile=1;
int movie=1;
int movie2=1;
extern int startmovie(char* naam);
extern void stopmovie();
extern void updatemovie();
extern int startmovie2(char* naam);
extern void stopmovie2();
extern void updatemovie2();
extern int playmovie(char* naam);
int again1=0;
int again2=0;
sf::Event event;
int formula=0;
extern void wierdo(int totalx, int totaly);
int drawmazes=1;
int shift=0;
extern int check_dir(int BITMAPSX,int BITMAPSY,int level);
void putinmazeSFML(int totalx,int totaly);
extern void ReadSFML(char * naam, int x, int y, int draw);
int forced_jump=1;
int new_verschilx2=0;
int new_verschily2=0;
int test_verschilx=0,test_verschily=0;
int mem_picturex;
int mem_picturey;
int mem_posx;
int mem_posy;
float mem_fposx;
float mem_fposy;
int render_picturex;
int render_picturey;
int render_posx;
int render_posy;
int new_verschilx;
int new_verschily;
int new_picturex;
int new_picturey;
int new_posx;
int new_posy;
float new_fposx;
float new_fposy;
int maxpixelsx;
int maxpixelsy;
int first_follow=1;
int real_posx;
int real_posy;
int real_posx2;
int real_posy2;
int long_jump=1;
int old_pen=0;
int old_pen_mode=2;
int follow_ghost_num=0;
int follow_ghost=0;
int follow_ghost_start=0;
int best_ghost_num=-1;
float fbest_distance=0.0;
int eatmode=0;
extern void adapt(int mazemovex, int mazemovey);
extern void adapt2(int mazemovex, int mazemovey);
int DONTSAVEFILES=0;
int go_on=1;
float fhapper2=0;
int total_points_start;
int total_points;
sf::WindowHandle WindowHandle;
int ghostmode=0;
sf::Clock clock_ghost;
sf::Clock clock_shader;
sf::Shader m_shader;
sf::Shader m_shader2;
sf::VertexArray m_points;
sf::RenderStates states;
sf::RenderStates states2;
int sending_pos=1;
int plot_internetfile=0;
int plot_ffmpegfile=0;
int plot_moviefile=0;
int plot_moviefile2=0;
int rotate_movie=0;
int rotate_movie2=0;
int rotate_ffmpeg=0;
int rotate_internet=0;
int rotate_canvas=0;
extern int GetFileFromInternet(char * naam);
void goto_partner();
char reg[100];
int	remote_edit=0;
int sync=1;
extern int position1x,position1y;
extern int position2x,position2y;
int mazetype=0;
int totalfiles;
int totalfiles_mazes;
extern void go_save_some_bitmaps();
extern void frexit(int err_no);
char *line;
int levelnotsaved=0;
int overwrite1=0;
int overwrite2=0;
char error_msg[1000];
int error_flag=0;
char error_msg_s[1000];
int error_flag_s=0;
char error_msg2[1000];
int error_flag2=0;
char error_msg3[1000];
int error_flag3=0;
char error_msg4[1000];
int error_flag4=0;
char error_msg5[1000];
int error_flag5=0;
int	move_remote_posx;
int	move_remote_posy;
extern void remote_plot(int mazemovex, int mazemovey, int blokje, int remote_pen_mode);
extern void goto_plot(int mazemovex, int mazemovey);
extern void goto_pos_remote();
int goexit=0;
int remote_init=0;
int remote_points=0;
int local_points=0;
extern void remote_point(int remote_posx,int remote_posy);
void SEND(char *towrite);
int REMOTE_ALIVE=10000;
int SEED;
char commandline[200];
int skipcount=0;
int F1=0;
int F2=1;
int F4=0;
int loadmap=0;
int combine=0;
int	plotx;
int	ploty;
int start_posx=0;
int start_posy=0;
int waitforplayer=0;
char writer[1024*4]="";
int framespersecond;
char lastmove;
sf::Int64 umicrosec;
sf::Int64 remote_time;
sf::Int64 umicrosec_total;
sf::Int64 umicrosec_last;
sf::Clock clock_frame;
float fps_float;
sf::Color pixel_color;
sf::RenderTexture texture_point;
sf::Image image_point;
sf::Sprite sprite_point;
sf::Texture sfml_bitmaps;
sf::Texture sfml_mazedot2;
sf::Texture sfml_mazedot;
sf::Texture texture_cube;
sf::Sprite spritedot;
sf::Sprite spritedot2;
sf::RenderWindow SFMLView1;
sf::Text text;
sf::Font font;
HINSTANCE hInstance2;
HWND hWndMain2;
int playerleft=0;
int skiphandshake=0;
int skip=0;
int loaded_from_maze=0;
int big_large=0;
extern void	generate_maze(int width, int height, int seed);
void DoAnimate2(HINSTANCE,HWND);
int init=0;
int init2=1;
int level=1;
int next=0;
int loaded=0;
int xdraw,ydraw;
int mapx,mapy;
int breed,hoog;
int ghost=1;
int hunt=0;
int hunt_counter=0;
int hunt_max=0;
int soundoff=0;
int soundloop=0;
int playsound=0;
int playmusic=0;
int posx=-1920-32+960-64;
int posy=-1080-36+540;
float fposx=-1920-32+960-64;
float fposy=-1080-36+540;
float fspeed_adjust=1.0;
int speedx=0;
int speedy=0;
float fspeedx=0;
float fspeedy=0;
int picturex=1;
int picturey=1;
int pen=0;
int pen_mode=0;
int mazemovex=0;
int mazemovey=0;
int old_mazemovex;
int old_mazemovey;
int thread_mazemovex;
int thread_mazemovey;
int mazemovexold=0;
int mazemoveyold=0;
int maze_up=0;
int maze_down=0;
int maze_left=0;
int maze_right=0;
int speedx_new=0;
int speedy_new=0;
float fspeedx_new=0;
float fspeedy_new=0;
int maze_up_new=0;
int maze_down_new=0;
int maze_left_new=0;
int maze_right_new=0;
int toggle_point=0;
int SFML=1;
int pressed;
int server;
int client;
int connected;
int connecting;
int maxpicturex;
int maxpicturey;
char **maze_plot;
int totalpicturex;
int totalpicturey;
char **Maze;
char **Maze2;
int mazesizex;
int mazesizey;
int number=1;
int old_number=number;
int maxnumber=10000;
int num_ghost;
int 	*pos_ghostx;
int 	*pos_ghosty;
float 	*fpos_ghostx;
float 	*fpos_ghosty;
float 	*fspeed_ghostx;
float 	*fspeed_ghosty;
int 	*check;

sf::RenderTexture texturemaxinmem[800];
sf::RenderTexture *texturemaxinmempoint[800];
int used_maxinmem[800];
sf::Sprite *spritemaxinmempoint[800];

//sf::RenderTexture *texturemaxinmem=NULL;
//sf::RenderTexture **texturemaxinmempoint=NULL;
//int *used_maxinmem=NULL;
//sf::Sprite **spritemaxinmempoint=NULL;

char **used;
int  **used2;
char **changed;
char **files;
char **files_mazes;
int totalused=0;
int totalchanged=0;
char savename1[80];
char savename2[80];
int texture_1x;
int texture_1y;
int texture_2x;
int texture_2y;
sf::Sprite sprite_from_canvas;
sf::Sprite sprite_from_internet;
sf::Sprite sprite_from_ffmpeg;
sf::Sprite sprite_from_crop;
sf::Sprite sprite_from_movie;
sf::Sprite sprite_from_movie2;
sf::Texture texture_from_internet;
sf::RenderTexture texture_from_buffer;
sf::RenderTexture texture_from_buffer2;
int swapper=0;
sf::Texture texture_from_ffmpeg;
sf::Texture texture_from_crop;
extern sf::Texture texture_from_movie_new;
extern sf::Texture texture_from_movie2_new;
extern sfe::Movie* live_movie;
extern StreamSelector *live_selector;
extern sfe::Movie *live_movie2;
extern StreamSelector *live_selector2;
HWND TextBox, SendButton, TextField;
extern int runTcpServer(unsigned short port);
extern int runTcpClient(char * ipaddress, unsigned short port);
extern int runUdpServer(unsigned short port);
extern int runUdpClient(char * ipaddress, unsigned short port);
extern int reconnectTcpServer(unsigned short port);
extern int reconnectTcpClient(char * ipaddress, unsigned short port);
extern int reconnectUdpServer(unsigned short port);
extern int reconnectUdpClient(char * ipaddress, unsigned short port);
char connectedip[100];
extern sf::TcpSocket internet_socket_tcp1;
extern sf::TcpSocket internet_socket_tcp2;
extern sf::UdpSocket internet_socket_udp1;
extern sf::UdpSocket internet_socket_udp2;
extern sf::TcpListener listener1;
extern sf::TcpListener listener2;
extern sf::IpAddress sender;
extern sf::IpAddress server_address;
sf::IpAddress dummy_address;
extern sf::IpAddress sender;
extern unsigned short senderPort1;
extern unsigned short senderPort2;
unsigned short dummyPort;
unsigned short portnumber=50001;
int portnumber_int;
char portnumber_text[10];
int udp=0;
int tcp=0;
int BITMAPSX=0;
int BITMAPSY=0;
int MAXINMEM=0;
int PRELOAD=0;
int MAXGHOSTS=0;
int LOADLAST=1;
int SAVELAST=1;
int MAZEHEIGHT=0;
int MAZEWIDTH=0;
int LOGFILE=0;
int SAS_STARTX;
int SAS_STARTY;
int SAS_ZOOM;
extern int SAS_ZOOM_DIRECTION;
char SAS_DIR[2000];
char SAS_URL[2000];
char SAS_EXTENSION[20];
char SAS_ORDER[5];

extern void cleanupmem();
int inpointer=0;
sf::Mutex mutex;
char in[256*256];
char out[256];
char print[256*256];
char last_in[256*256];
std::size_t received=0;
std::size_t sent=0;
int remote_posx;
int remote_posy;
int old_remote_posx;
int old_remote_posy;
int accepted_ready=2;
extern bool file_exists(const char * filename);
extern bool file_exists2(const char * filename);
extern void draw2(char *towrite, int xpos, int ypos, sf::Color inner, sf::Color outer);
extern void draw3(char *towrite, int xpos, int ypos, sf::Color inner, sf::Color outer);
extern void savedata(char *naam, int data);
extern void logfile(char *line);
extern void CreateAll();
extern void save_map();
extern void save_map_last();
extern void load_map_last();
extern void load_map();
extern void count_points();
extern void goto_partner();
extern void set_pacman();
extern void follow_ghost_pos();
extern void set_position1();
extern void set_position2();
extern void get_position1();
extern void get_position2();
extern void get_position3();
extern void clear_map();
extern void home_map();
extern void loadlevel();
extern void savelevel();
extern void putinmazeSFML(int totalx,int totaly);
extern void DRAWALLMAZES();
extern void DRAWMAZE(int totalx,int totaly);
extern void LOADALLBITMAPS();
extern void RenderBlit(int mapx,int mapy, int xdest, int ydest, int width, int height, int xsource, int ysource);
extern void RenderBlit_total(int totalx,int totaly, int xdest, int ydest, int width, int height, int xsource, int ysource, int remote_pen_mode);
extern void RenderBlit2(float xdest, float ydest, int xsource, int ysource, int width, int height);
MSG msg;
int first=1;
int skipinit=0;
extern int handle_init();
sf::Sound sound[10];
extern int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow);
extern int WINAPI WinMain2(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow);
extern ATOM RegClass(char *ClassName,HINSTANCE hInstance);
extern HWND CreateWin(HINSTANCE hInstance, char *ClassName,int Width, int Height);
extern BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam);
extern select_movie(char *filename, char * path);
extern int select_from_list(char *filename, char * path, int next);
extern int GETPICTURE(char *naam);
extern int GETBLENDINGPICTURE(char *naam);
extern void ShowTaskBar(bool show);
extern void SAVEALLBITMAPS();
extern void CLEANBITMAPS();
extern void EXITPROGRAM();
extern void HALT();
extern VOID HANDLECHAR(WPARAM wparam);
extern void HANDLEEVENTS();
extern VOID HANDLEKEY(WPARAM wparam);
extern void SENDGOTOPOS();
extern LRESULT CALLBACK WinProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);
HWND hWindow;
HFONT hFont;
HFONT hTmp;
extern void zetom();
extern void reversed_zetom();
extern void blitter(char * line,int mode);
extern void save_maze(int lastmap);
extern void load_maze(int lastmap);
extern void ReadOneBitmap(int picturex,int picturey);
extern void ReadBitmaps2();
extern void ReadBitmaps4();
extern void ReadBitmaps2_remote(int picturex, int picturey);
extern void cleanupbitmaps();
extern void cleanupbitmaps_mazes();

sf::RenderTexture texture_final;
char naam[2000];
FILE * testfile;
int x=1919;
int y=0;
int plaatje=0;
char message[100];
SYSTEMTIME str_t;
int wocky=0;
int wocky_speed=10;
float fwocky_speed=10;
int packy;
int wocky2=0;
int wocky_speed2=10;
float fwocky_speed2=10;
int packy2;
float fwocky2=0;
char wocky_anim[]= {0,1,2,3,2,1};
//int xx;
int i2;
int todo=0;
char digitsold[3]="";
char digits[3]="";
float fhapper=0;
float fwocky=0;
int remote_posx_ar[4096];
int remote_posy_ar[4096];
int remote_pos_counter=0;
int remote_pos_start=0;
char remote_movement[4096];
sf::Int64 remote_timer[4096];
int start_buffering;
long plotdatax[4096];
long plotdatay[4096];
int plot_start=0;
int plot_count=0;
float time_per_pixel=1000000.0/60/4;
int first_message=300;
extern void save_mazeoff();
extern int read_mazeoff(int nopos);
sf::Mutex mutje;
double scale_jump=0.02880;

#define ALT 1
#define SHIFT 2
#define CONTROL 4
#define SYSTEM 8

extern void insert_event(sf::Keyboard::Key code,int MODE);

extern void insert_key(WPARAM key);

int flowx=0;
int flowy=0;
int nextlevel=0;
//extern int mul;
extern void putinmazeSFML_all();
sf::Mutex animate_lock;
int something_to_do=0;

void DoAnimate2(HINSTANCE hInstance, HWND hWndMain)
{
    static int next_key=0;
//    printf("x=%d,y=%d\n",pos_ghostx[0],pos_ghosty[0]);
    if (loadallmaps)
    {
        putinmazeSFML_all();
        if (next_key==1)
        {
            next_key=0;
            playmusic=1;
            save_maze(level);
            sf::sleep(sf::seconds(1.0));
            insert_key((WPARAM)'<');

        }
        else if (mul>0)
        {
            playmusic=1;
            save_maze(level);
            sf::sleep(sf::seconds(1.0));
            insert_key((WPARAM)'<');
        }
        else
        {
            if (level>0)
            {
                playmusic=2;
                save_maze(level);
                sf::sleep(sf::seconds(1.0));
                insert_key((WPARAM)'[');
                next_key=1;
            }
            else
            {
                loadallmaps=0;
                playsound=playsound|8;
            }
        }
    }
    if (loadallmaps_level)
    {
        putinmazeSFML_all();
        if (level>0)
        {
            playmusic=2;
            save_maze(level);
            sf::sleep(sf::seconds(1.0));
            insert_key((WPARAM)'[');
            next_key=1;
        }
        else
        {
            loadallmaps_level=0;
            playsound=playsound|8;
        }
    }


    static int next_level_counter=60;
    if (nextlevel==1)
    {
        next_level_counter--;
        if (next_level_counter<=0)
        {
            next_level_counter=60;
            nextlevel=0;
            do_nextlevel();
        }
    }
    if (flippo==1)
    {
//        if (pen==1) pen_mode=2;
        pen=0;
    }
    once=0;
    ESCAPE=0;
    if (next==1)
    {
//        animate_lock.unlock();
//        animate_lock.lock();
//            if (flippo==1 && level==2 && force_game) F2=0;
        skipclear=0;
        check_dir(BITMAPSX,BITMAPSY,level);
        if (shade_map>=1)
        {
            int ret;
            force_game=0;
            char ip[200];
            char page[200];
//            shade_map=2;
            reload_init();

            if (SAS_URL[0]>='0' && SAS_URL[0]<='9')
            {
                int dummy;
                if (toupper(SAS_URL[5])=='S')
                    sscanf(SAS_URL, "%dhttps://%199[^/]/%199[^\n]",&dummy, ip,page );
                else
                    sscanf(SAS_URL, "%dhttp://%199[^/]/%199[^\n]",&dummy, ip,page);
                sprintf(LEVELDIR,"%s/%s-%d",MAPDIR,ip,dummy);
            }
            else
            {
                if (toupper(SAS_URL[4])=='S')
                    sscanf(SAS_URL, "https://%199[^/]/%199[^\n]", ip,page );
                else
                    sscanf(SAS_URL, "http://%199[^/]/%199[^\n]", ip,page);
                sprintf(LEVELDIR,"%s/%s",MAPDIR,ip);
            }

            ret=read_mazeoff(1);
            SAS_STARTX_a=SAS_STARTX*256-(int)((float)(SAS_STARTX*256)/1920.0)*1920;
            SAS_STARTY_a=SAS_STARTY*256-(int)((float)(SAS_STARTY*256)/1080.0)*1080;

//            printf("CALCULATED NEW:\n");
//            printf("SAS:   x=%8d , y=%8d , zoom=%d\n",SAS_STARTX,SAS_STARTY,SAS_ZOOM);
//            printf("ADAPT: x=%8d , y=%8d \n" ,(int)(SAS_STARTX_a/256),(int)(SAS_STARTY_a/256));
//            printf("REST:  x=%8d , y=%8d \n" ,SAS_STARTX_a,SAS_STARTY_a);
//            printf("X: tot=%d  /1920=%f\n",SAS_STARTX*256-SAS_STARTX_a,(float)(SAS_STARTX*256-SAS_STARTX_a)/1920.0);
//            printf("Y: tot=%d  /1080=%f\n",SAS_STARTY*256-SAS_STARTY_a,(float)(SAS_STARTY*256-SAS_STARTY_a)/1080.0);
//            printf("===========================\n");
//
//                    SAS_STARTX=SAS_STARTX-SAS_STARTX_a/256;
//                    SAS_STARTY=SAS_STARTY-SAS_STARTY_a/256;
//                    SAS_STARTX_a=SAS_STARTX_a-(int)(SAS_STARTX_a/256)*256;
//                    SAS_STARTY_a=SAS_STARTY_a-(int)(SAS_STARTY_a/256)*256;

            offset_picture_x=(int)((float)(SAS_STARTX*256+255)/1920.0);
            offset_picture_y=(int)((float)(SAS_STARTY*256+255)/1080.0);

            SAS_STARTX= (offset_picture_x*1920)/256;
            SAS_STARTY= (offset_picture_y*1080)/256;

            SAS_STARTX_a=offset_picture_x*1920-SAS_STARTX*256;
            SAS_STARTY_a=offset_picture_y*1080-SAS_STARTY*256;

//            printf("RE-RECALCULATED NEW:\n");
//            printf("SAS:   x=%8d , y=%8d , zoom=%d\n",SAS_STARTX,SAS_STARTY,SAS_ZOOM);
//            printf("ADAPT: x=%8d , y=%8d \n" ,(int)(SAS_STARTX_a/256),(int)(SAS_STARTY_a/256));
//            printf("REST:  x=%8d , y=%8d \n" ,SAS_STARTX_a,SAS_STARTY_a);
//            printf("X: tot=%d  /1920=%f\n",SAS_STARTX*256-SAS_STARTX_a,(float)(SAS_STARTX*256-SAS_STARTX_a)/1920.0);
//            printf("Y: tot=%d  /1080=%f\n",SAS_STARTY*256-SAS_STARTY_a,(float)(SAS_STARTY*256-SAS_STARTY_a)/1080.0);
//            printf("===========================\n");


//                    offset_picture_x=(SAS_STARTX*256-SAS_STARTX_a)/1920;
//                    offset_picture_y=(SAS_STARTY*256-SAS_STARTY_a)/1080;
//            save_mazeoff();
            Fget_map_x=(double)SAS_STARTX-(double)SAS_STARTX_a/256.0;
            Fget_map_y=(double)SAS_STARTY-(double)SAS_STARTY_a/256.0;
            get_map_zoom=SAS_ZOOM;
            get_map_x=SAS_STARTX;
            get_map_y=SAS_STARTY;
        }
        clock_ghost.restart();
        die=0;
        loadbackground=1;
        CLEANBITMAPS();
        forced_jump=1;
        first_follow=1;
        long_jump=1;
//        printf("2\n");
        old_pen=0;
        old_pen_mode=2;
        follow_ghost_start=0;
//        eatmode=0;
        follow_ghost=0;
        follow_ghost_num=0;
        best_ghost_num=-1;
        fbest_distance=0.0;
        logfile((char*)"Next");
        number=1;
        levelnotsaved=0;
        remote_init=1;
        in[0]='\0';
        inpointer=0;
        speedx=0;
        speedy=0;
        fspeedx=0;
        fspeedy=0;
        maze_up_new=0;
        maze_down_new=0;
        maze_left_new=0;
        maze_right_new=0;
        remote_pos_counter=0;
        remote_pos_start=0;
        remote_points=0;
        strcpy(error_msg2,"LOADED: ");
        strcpy(error_msg3,"SAVED: ");
        strcpy(error_msg4,"CREATED: ");
        strcpy(error_msg5,"DELETED: ");

        if (connected==1)
            waitforplayer=1;
        int xx,yy;
        lastmove='0';
        for (xx=0; xx<4096; xx++)
        {
            remote_posx_ar[xx]=0;
            remote_posy_ar[xx]=0;
            remote_timer[xx]=0;
        }

        for (xx=0; xx<4096; xx++)
        {
            plotdatax[xx]=0;
            plotdatay[xx]=0;
        }
        plot_start=0;
        plot_count=0;

        start_buffering=1;
        fhapper=1.0;
        fhapper2=1.0;
        if (connected==1)
        {
        }
//        ghost=1;

        savelevel();

        logfile((char*)"Clean up / testing files");

        if (skip==0 && (force_loading==1 || MAZEOFF==0))
//        if (skip==0 && (MAZEOFF==0 || force_loading==1))
        {
            if (combine==0)
            {
                for (xx=0; xx<maze_plotsizex; xx++)
                {
                    for (yy=0; yy<maze_plotsizey; yy++)
                    {
                        maze_plot[xx][yy]=0;
                    }
                }
            }
            if (loaded_from_maze==0)
            {
                for (xx=0; xx<=(mazesizex+1); xx++)
                {
                    for (yy=0; yy<=(mazesizey+1); yy++)
                    {
                        Maze[xx][yy]='O';
                    }
                }
            }
        }
        totalfiles=0;
        totalfiles_mazes=0;
        if (MAZEOFF==0)
        {
//            SFMLView1.clear(sf::Color(0,0,0,0));
            glClearColor(0.0f, 0.0f, 0.0f, (float)(set_transparant==0));
//            glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
            if (F2==1)
            {
//                SFMLView1.setActive(true);
//                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//                SFMLView1.setActive(false);
                if (!burn_subs)
                {
                    draw2((char*)"TESTING FILES",0,0,sf::Color::Blue,sf::Color::White);
                    SFMLView1.display();
                }
            }
            for (x=0; x<=maxpicturex; x++)
            {
                for (y=0; y<=maxpicturey; y++)
                {
//                    sprintf(naam,"levels/%dx%d/%03d/picture.%06d.%06d.png",BITMAPSX,BITMAPSY,level,y,x);
                    sprintf(naam,"%s/%dx%d/%03d/picture.%06d.%06d.png",LEVELDIR,BITMAPSX,BITMAPSY,level,y,x);
                    int exist;
                    exist = stat(naam,&stat_buffer);
                    if ( exist!=0)
                    {
                        files[x][y]=0;
                    }
                    else
                    {
                        files[x][y]=1;
                        totalfiles++;
                    }
//                    sprintf(naam,"levels/%dx%d/%03d/picture_maze.%06d.%06d.png",BITMAPSX,BITMAPSY,level,y,x);
                    sprintf(naam,"%s/%dx%d/%03d/picture_maze.%06d.%06d.png",LEVELDIR,BITMAPSX,BITMAPSY,level,y,x);
                    exist = stat(naam,&stat_buffer);
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

        if (combine==1)
        {
            err_level=1;
            strcpy(error_msg,"GO BACK TO YOUR LEVEL AND PRESS SHIFT-L TO LOAD BITMAPS AND z OR Z TO SAVE MAZE");
            error_flag=1;
            pen=1;
            pen_mode=2;
            levelnotsaved=1;
        }
        else
            err_level=0;

        if (level<0)
            level=0;

        int tussen;
        int half;

        if (loaded==0 || newmaze==1 &&!MCEDITOR_running)
        {
            if (connected==0)
            {
//                SEED=time(0);
            }
            else
                srand(SEED);

//            printf("big_large=%d\n",big_large)                ;
            if (big_large==1)
            {
                breed=mazesizey/2-1;
                hoog=mazesizex/2-1;
            }
            else
            {
                if (newmaze==0)
                {

                    reload_init();
                    if (MAZEHEIGHT!=0)
                        breed=MAZEHEIGHT;	//	(breed=height)
                    if (MAZEWIDTH!=0)
                        hoog=MAZEWIDTH;		//	(hoog=width)   :(


                    breed=breed+(int)maze_size/2;
                    hoog=hoog+(int)maze_size/2;
//                    breed=breed+(int)maze_size/2+rand()%(2+(int)maze_size/2);
//                    hoog=hoog+(int)maze_size/2+rand()%(2+(int)maze_size/2);
//rinkel
//                    maze_size=maze_size*1.2+1.0;
                    if (breed>mazesizey/2-1)
                        breed=mazesizey/2-1;
                    if (hoog>mazesizex/2-1)
                        hoog=mazesizex/2-1;
                }
            }

            if (!burn_subs)
            {
                draw2((char*)"GENERATING MAZE",800,0,sf::Color::Red,sf::Color::White);
                SFMLView1.display();
            }
            sprintf(writer,"breed=%d hoog=%d",breed,hoog);
            logfile(writer);
            generate_maze(breed,hoog,SEED);

            if (go_list || go_download || go_burn)
            {
                mazetype=1;
                combine=1;
            }

            Maze[2][1]='#';
            Maze[hoog*2][1]='#';
            Maze[hoog*2][breed*2+1]='#';
            combine=0;
            adapt_maze=1;
            if (go_list || go_download || go_burn)
            {
                mazetype=1;
                combine=1;
            }
            zetom();
            if (go_list || go_download || go_burn)
            {
                mazetype=1;
                combine=0;
            }
            adapt_maze=0;
            count_points();


//adaptmaze
            goto_maze(-59,-30);
//            goto_maze(maze_plotsizex-59,maze_plotsizey-30);

            /*
                        if (shade_map==0) {
                            posx=-1920-32+960;
                            posy=-1080-36+540;
                            fposx=posx;
                            fposy=posy;
                            picturex=1;
                            picturey=1;
                        }
            */
            start_posx=(picturex*1920-posx);
            start_posy=(picturey*1080-posy);
            mazetype=1;
            newmaze=0;
            forced_jump=1;
        }
        else
        {
            if (loaded_from_maze==1)
            {
                if (MAZEOFF==0 || force_loading==1)
                    zetom();
                if (skipcount==0 || (level==0 && skip==0))
                {
                    count_points();
                    local_points=0;
                }
            }
            if (loaded_from_maze==0)
                if (skip==0)
                {
                    if (loadmap==1)
                    {
                        if (MAZEOFF==0 || force_loading==1)
                            if (level==0 )
                                load_map_last();
                            else
                                load_map();
                        count_points();
                    }
                    else
                    {
                        if (MAZEOFF==0 || force_loading==1)
                        {
                            load_maze(level);
                            zetom();
                        }
                        count_points();
                    }
                }
//			breed=0;
        }
        loaded_from_maze=0;
        combine=0;
        loadmap=0;
        skipcount=0;

        if (skip==1)
            skip=0;

        maze_up=0;
        maze_down=0;
        maze_left=0;
        maze_right=0;
        maze_up_new=0;
        maze_down_new=0;
        maze_left_new=0;
        maze_right_new=0;
        wocky=2;
        wocky_speed=5;
        wocky2=2;
        wocky_speed2=5;
        speedx=0;
        speedy=0;
        speedx_new=0;
        speedy_new=0;
        fspeedx=0;
        fspeedy=0;
        fspeedx_new=0;
        fspeedy_new=0;
        packy=0;
        packy2=0;
        hunt=0;
        hunt_counter=0;

        for (xx=0; xx<totalpicturex; xx++)
        {
            for (yy=0; yy<totalpicturey; yy++)
            {
                if (changed[xx][yy]==1)
                {
                    changed[xx][yy]=0;
                    totalchanged--;
                }
                if (used[xx][yy]==1)
                {
                    used[xx][yy]=0;
                    totalused--;
                }
                used2[xx][yy]=0;
            }
        }
        for (xx=0; xx<MAXINMEM+12; xx++)
            used_maxinmem[xx]=0;

//        CLEANBITMAPS();
//        cleanupbitmaps_mazes();
        if (PRELOAD==1)
            CreateAll();
        ReadBitmaps2();
        ReadBitmaps4();

        next=0;
//        if (movie==1)
//            playsound=playsound|8;

        if (connected==1)
        {
            sprintf(writer,"T=READY,\0");
            SEND(writer);
        }

        clock_frame.restart().asMicroseconds();
        umicrosec=0;
        umicrosec_total=0;
        fspeed_adjust=1.0;
        total_points_start=total_points;
//        force_game=1;
//        set_smooth(picturex*1920-posx,picturey*1080-posy);
//        render_picturex=picturex; render_posx=posx;
//        render_picturey=picturey; render_posy=posy;
//        forced_jump=1;
//        follow_ghost_pos();
        force_loading=0;
//        update_map(0,1);
//        update_map(1,0);
//        update_map(1,1);

        posx=posx-posx%64-32;
//pospos
        if (posx<-1920)
//        if (posx<=-1920)
        {
            posx=posx+1920;
            picturex=(picturex+1+totalpicturex)%totalpicturex;
        }
        posy=posy-(posy-36)%72-36;
        if (posy<-1080)
//        if (posy<=-1080)
        {
            posy=posy+1080;
            picturey=(picturey+1+totalpicturey)%totalpicturey;
        }
        fposx=posx;
        fposy=posy;
        ReadBitmaps2();
        if (shade_map>=1)
        {
            pacman_to_rel_pos();
        }

        if ( (mazetype==0 && first_message==0 && force_game==1) || flippo==1)
        {
            for (num_ghost=0; num_ghost<1; num_ghost++)
            {
//                fpos_ghostx[num_ghost]=-1920-32+960-64-(float)(num_ghost)/4*64;
//                fpos_ghosty[num_ghost]=-1080-36+540+3*72;
                if (mazetype==1)
                {
                    fpos_ghostx[number-1]=-1920-32+960+64*59;
                    fpos_ghosty[number-1]=-1080-36+540+72*30;
                }
                else
                {
                    fpos_ghostx[number-1]=1920-position1x;
                    fpos_ghosty[number-1]=1080-position1y;
                }
                pos_ghostx[number-1]=fpos_ghostx[number-1];
                pos_ghosty[number-1]=fpos_ghosty[number-1];
//                fpos_ghostx[num_ghost]=-1920-32+960;
//                fpos_ghosty[num_ghost]=-1080-36+540;


                if ((maze_plot[(-59+maze_plotsizex)%maze_plotsizex][(-30+maze_plotsizey)%maze_plotsizey]&2)==2)
                {
                    fspeed_ghostx[num_ghost]=0;
                    if (flippo==1)
                        fspeed_ghosty[num_ghost]=fspeed_mem;
                    else
                        fspeed_ghosty[num_ghost]=4;
                }
                else
                {
                    if (flippo==1)
                        fspeed_ghostx[num_ghost]=fspeed_mem;
                    else
                        fspeed_ghostx[num_ghost]=4;
                    fspeed_ghosty[num_ghost]=0;
                }


                check[num_ghost]=0;
            }
            ghost=1;
            number=1;
        }
        else
            number=0;
        /*
                else  if (first_message==0)
                {

                    for (num_ghost=0; num_ghost<1; num_ghost++)
                    {
                        fpos_ghostx[num_ghost]=-1920-32+960;
                        fpos_ghosty[num_ghost]=-1080-36+540;

                        if (number%4==0)
                        {
                            fspeed_ghostx[num_ghost]=2.0+(rand()%1001)/(500.0+hunt*500.0);
                            fspeed_ghosty[num_ghost]=0.0;
                        }
                        else if (number%4==1)
                        {
                            fspeed_ghostx[num_ghost]=0.0;
                            fspeed_ghosty[num_ghost]=-2.0-(rand()%1001)/(500.0+hunt*500.0);
                        }
                        else if (number%4==2)
                        {
                            fspeed_ghostx[num_ghost]=-2.0-(rand()%1001)/(500.0+hunt*500.0);
                            fspeed_ghosty[num_ghost]=0.0;
                        }
                        else if (number%4==3)
                        {
                            fspeed_ghostx[num_ghost]=0.0;
                            fspeed_ghosty[num_ghost]=2.0+(rand()%1001)/(500.0+hunt*500.0);
                        }
                        check[num_ghost]=0;
                    }
                    number=1;
                } else number=0;
            */

        if (go_list || go_download || go_burn)
        {
            cleanupbitmaps_mazes();
            CLEANBITMAPS();
            ReadBitmaps2();
            ReadBitmaps4();
            F4=1;
            difficulty=4;
            skipclear=1;
            force_game=0;
            F2=0;
            eatmode=1;
            flippo=0;
            mazetype=1;
            DONTSAVEFILES=0;
        }

        extern test();
        ShowCursor(true);
extern int trace( std::string scanfile );
extern int trace_line( std::string filename );
extern int trace_line2( std::string filename );
extern int trace_line3(std::string in);
extern int trace_line4(std::string in);

//        trace_line4("../pictures/x271941.png");
//        trace_line4("../pictures/picture.040929.036315.png");
        ShowCursor(false);
//        getchar();

        if (MCEDITOR_running==1) {
            clear_map();
            cleanupbitmaps_mazes();
            ReadBitmaps2();
        }
        if (!screensaver) SFMLView1.requestFocus();
//        playsound=playsound|256;
        got_next=true;
    }


    if (first==1)
    {
//        if (mirror==4 && crossing==2) sf::sleep(sf::seconds(5.0));
        read_keylist_hpp();
        testit(); // enable ansi codes in terminal




//        loaded=1;
//        loaded_from_maze=1;
//        newmaze=1;
//        flippo=1;
//        skipinit=1;
//        eatmode=1;
//        DONTSAVEFILES=1;
        F2=1;
//        flippo=1;
//        to_plot.push_back(sf::Vector2i(0,0));
//        to_plot[0].x=0;
//        to_plot[0].y=0;
        loadmul();
        MyBlendMode_num=4;
        set_blending();
        MyBlendMode_num=0;
        set_blending();
        scale_now=1.0;
        sprite_from_ffmpeg.setScale(1.0,1.0);
        sprite_from_internet.setScale(1.0,1.0);
        sprite_from_movie.setScale(1.0,1.0);
        sprite_from_movie2.setScale(1.0,1.0);
        sprite_from_canvas.setScale(0.02,0.02);
        sprite_from_ffmpeg.setTexture(texture_from_ffmpeg,false);
        sprite_from_internet.setTexture(texture_from_internet,false);
        sprite_from_movie.setTexture(texture_from_movie_new,false);
        sprite_from_movie2.setTexture(texture_from_movie2_new,false);
        texture_from_ffmpeg.setRepeated(TRUE);
        texture_from_internet.setRepeated(TRUE);
        texture_from_movie_new.setRepeated(TRUE);
        texture_from_movie2_new.setRepeated(TRUE);
        size_ffmpeg=1;
        size_internet=1;
        size_movie=1;
        size_movie2=1;

        sf::Image im;
        im.create(1,1);
        im.setPixel(0,0,sf::Color(255,128,0,128));
        texture_from_crop.create(1,1);
        texture_from_crop.update(im);
        sprite_from_crop.setTexture(texture_from_crop,false);
        sprite_from_crop.setScale(1920.0/2,1080.0/2);
        sprite_from_crop.setTextureRect({0,0,1,1});
        sprite_from_crop.setPosition(0.0,0.0);

        handler[MOVIE_SELECT].blending=0;
        handler[MOVIE_SELECT].plot_front=0;
        handler[MOVIE_SELECT].show=1;
        handler[MOVIE_SELECT].tile=0;
        handler[MOVIE_SELECT].shader=1;

        handler[MOVIE2_SELECT].blending=0;
        handler[MOVIE2_SELECT].plot_front=0;
        handler[MOVIE2_SELECT].show=1;
        handler[MOVIE2_SELECT].tile=0;
        handler[MOVIE2_SELECT].shader=1;

        handler[FFMPEG_SELECT].blending=0;
        handler[FFMPEG_SELECT].plot_front=0;
        handler[FFMPEG_SELECT].show=1;
        handler[FFMPEG_SELECT].tile=0;
        handler[FFMPEG_SELECT].shader=1;

        handler[INTERNET_SELECT].blending=0;
        handler[INTERNET_SELECT].plot_front=0;
        handler[INTERNET_SELECT].show=1;
        handler[INTERNET_SELECT].tile=0;
        handler[INTERNET_SELECT].shader=1;

        handler[CANVAS_SELECT].blending=0;
        handler[CANVAS_SELECT].plot_front=0;
        handler[CANVAS_SELECT].show=1;
        handler[CANVAS_SELECT].tile=0;
        handler[CANVAS_SELECT].shader=1;

//        displayer.launch();
//        m_pointCloud.clear();
        int xx,yy;
//        GHOSTtexture.create(64,72);
//        GHOSTsprite.setTexture(GHOSTtexture.getTexture(),true);
//        GHOSTsprite.setTextureRect({0,0,64,72});
        tussen_texture.create(1,1);
        backup_texture.create(1920,1080);
        backup_sprite.setTexture(backup_texture.getTexture(),false);
        backup_sprite.setTextureRect({0,0,1920,1080});
        backup_texture.setRepeated(true);
        texture_final.create(1920,1080,true);

        MyBlend.alphaDstFactor = sf::BlendMode::OneMinusSrcAlpha;
        MyBlend.alphaSrcFactor = sf::BlendMode::Zero;

        maxpixelsx=totalpicturex*1920;
        maxpixelsy=totalpicturey*1080;
        if (MAXGHOSTS>0)
            maxnumber=MAXGHOSTS;
        logfile((char*)"Entering loop first time");
//asshole
//        first=0;
        hWindow=hWndMain;

//        texture_cube.loadFromFile("resources/CUBE3.png");
        texture_cube.loadFromFile("resources/CUBE3.png");
        texture_cube.setSmooth(TRUE);
        texture_cube.generateMipmap();
        texture_cube.setRepeated(true);

        sfml_mazedot.loadFromFile("resources/maze2.png");
        sfml_mazedot.setSmooth(TRUE);
        sfml_mazedot.generateMipmap();
        sfml_mazedot2.loadFromFile("resources/maze3.png");
        sfml_mazedot2.setSmooth(TRUE);
//        sfml_mazedot2.generateMipmap();
        if (skipinit==0)
            loadlevel();
        next=1;
        texture_point.create(1,1);

        for (xx=0; xx<MAXINMEM+12; xx++)
        {
            used_maxinmem[xx]=0;
        }
        for (xx=0; xx<MAXINMEM+12; xx++)
        {
            if (!texturemaxinmem[xx].create(1920,1080))
            {
                logfile((char*)"Cannot create textures");
            }
            texturemaxinmem[xx].clear(sf::Color(0,0,0,0));
            texturemaxinmem[xx].display();
            if (smooth==1)
                texturemaxinmem[xx].setSmooth(true);
            else
                texturemaxinmem[xx].setSmooth(false);
            texturemaxinmempoint[xx]=&texturemaxinmem[xx];
            spritemaxinmempoint[xx] = new sf::Sprite();
            spritemaxinmempoint[xx]->setTexture(texturemaxinmem[xx].getTexture(),false);
            spritemaxinmempoint[xx]->setPosition(0,0);
            spritemaxinmempoint[xx]->setTextureRect({0,0,1920,1080});
//mafkees
//            texturemaxinmem[xx].setRepeated(TRUE);
            texturemaxinmem[xx].setRepeated(FALSE);
        }
        sprite_buffer = new sf::Sprite();

        if (skipinit==0 && LOADLAST==1)
        {
            sprintf(naam,"%s/%dx%d/%03d/maze.dat",LEVELDIR,BITMAPSX,BITMAPSY,0);
//            sprintf(naam,"levels/%dx%d/%03d/maze.dat",BITMAPSX,BITMAPSY,0);
            testfile = fopen (naam, "r");
            if (testfile!=NULL)
            {
                fclose(testfile);
                if (MAZEOFF==0)
                    load_maze(0);
                loaded=1;
                loaded_from_maze=1;
                skip=1;
            }
            else
            {
//                cleanupbitmaps_mazes();
            }
        }
        else
        {
            if (MAZEOFF==0)
                load_maze(level);
            loaded=1;
            loaded_from_maze=1;
            skip=0;
        }
        if (connected==1)
            waitforplayer=1;

        Effect::setFont(font);
        m_pointCloud_map0.setPrimitiveType(sf::Points);
        m_pointCloud_map0.clear();
        m_pointCloud_map0.resize(450);
        m_pointCloud_map1.setPrimitiveType(sf::Points);
        m_pointCloud_map1.clear();
        m_pointCloud_map1.resize(1);
        update_map(0,0);
//        m_pointCloud_map0.resize(450);
//        insert_key((WPARAM)'m');
        first=0;

        return;
    }
extern void parse_command(char * text);
extern char frag_name[];
extern char SHADERDIR[];
extern int fragment_shader;
extern int update_shader();
extern int plot_shader;
extern void insert_key(WPARAM key);
extern void insert_event(sf::Keyboard::Key code,int MODE);
extern bool do_pong;
extern char picture_name[];
extern char PICTUREDIR[];
extern int replace_string(char *str, char *orig, char *rep);

    if (DO_ADAPT)
        do_command(ADAPT_SPEED);
    if (DO_ZOOM_IN)
        do_command(ZOOM_IN);
    if (DO_ZOOM_OUT)
        do_command(ZOOM_OUT);
    if (start_burning>0)
    {
        start_burning++;
        if (start_burning>20)
        {
            burn_next_sub_ready_mutex.lock();
            start_burning=0;
            burn_next_sub_ready_mutex.unlock();
            do_command(GO_BURN);
        }
    }
extern int timenow;
extern int record_window;
    if (combine==1 && record_screen==1 && record_screen_num==200*5 && !record_window) {
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
        int scale_x=texture_from_ffmpeg.getSize().x*sprite_from_ffmpeg.getScale().x;
        int scale_y=texture_from_ffmpeg.getSize().y*sprite_from_ffmpeg.getScale().y;
        if (scale_x>1920) scale_x=1920;
        if (scale_y>1080) scale_y=1080;
        FILE* HOP;
        HOP=fopen("../record/make.bat","a");
        fprintf(HOP,"ffmpeg -y -i output%d.mp4 -filter:v \"crop=%d:%d:%d:%d\" -c:v h264_nvenc -profile:v high -pix_fmt yuv420p -b:v 10M -bufsize 20M -bf:v 3 -preset slow -rc:v vbr_hq -rc-lookahead 32 output%d_crop.mp4",timenow,scale_x,scale_y,int((1920-scale_x)/2),int((1080-scale_y)/2),timenow);
        fclose(HOP);

//        printf("%d:%d:%d:%d",scale_x,scale_y,(1920-scale_x)/2,(1080-scale_y)/2);
    }

    if (do_pong) {
        static int waiter=0;
        if (waiter==1) {
            static char pname[1000];
            static bool first=true;
            cleanupbitmaps_mazes();
            cleanupbitmaps();
            insert_key('P');
            if (first) {
                strcpy(pname,picture_name);
                first=false;
                printf("Picture: %s\n",picture_name);
/*
                if (file_exists("pong.txt")) {
                    FILE* pbs=fopen("pong.txt","r");
                    char line[100];
                    fgets(line,100,pbs);
                    fclose(pbs);
                    while (replace_str(line,",","."));
                    sscanf(line,"%f",&playbackspeed);
                    printf("playbackspeed set to %f\n",playbackspeed);
                }
*/

            } else {
                if (strcmp(pname,picture_name)==0) {
                    GenerateConsoleCtrlEvent(CTRL_C_EVENT, 0);
                    waiter=-1;
                    do_pong=false;
                    send_message='x';
                } else {
                    printf("Picture: %s\n",picture_name);
                }
            }


        } else if (waiter==2) {

//            replace_string(picture_name,".png",".jpg");
//            replace_string(picture_name,".bmp",".jpg");
//            texture_from_ffmpeg.copyToImage().saveToFile(picture_name);
//            sprite_from_ffmpeg.setScale(5.0,5.0);
//            convert_to_scale(&texture_from_ffmpeg, &sprite_from_ffmpeg);
//            sprite_from_ffmpeg.setScale(0.2,0.2);

        } else if (waiter==3) {

            sprintf(frag_name,"%s/fragment/picture_shader 01.frag",SHADERDIR);
            fragment_shader=1;
            update_shader();

        } else if (waiter>=4 && waiter<=4+8) {

            plot_shader=1;
            plot_ffmpegfile=1; plotplot();

        } else if (waiter==4+9) {

            sprintf(frag_name,"%s/fragment/picture_shader 02.frag",SHADERDIR);
            update_shader();

        } else if (waiter==4+10) {
//            plot_ffmpegfile=1; plotplot();
//            plot_ffmpegfile=0;
            int s;
            if (texture_from_ffmpeg.getSize().x >= texture_from_ffmpeg.getSize().y ) s=9600/texture_from_ffmpeg.getSize().x;
            else s=9600/texture_from_ffmpeg.getSize().y;
            sprite_from_ffmpeg.setScale(s,s);
            plot_shader=0;
//            setffmpegfile();
            plot_ffmpegfile=1; plotplot();
//            insert_event(sf::Keyboard::Key::F8, 0);
            convert_to_scale(&texture_from_ffmpeg, &sprite_from_ffmpeg);
            insert_event(sf::Keyboard::Key::F8, EVENT_SHIFT);

        } else if (waiter==4+11) {

            plot_shader=0;
            fragment_shader=0;

        } else if (waiter==4+12) {

            replace_string(picture_name,".jpg",".pong.jpg");
            texture_from_ffmpeg.copyToImage().saveToFile(picture_name);

        } else if (waiter==4+13) {

            insert_key('P');
//            do_pong=false;

        } else if (waiter==4+14) {
            waiter=-1;
        }
        waiter++;
    }

    loader_mutex.lock();
    monitor_off=1;
    loader_mutex.unlock();
    if (monitor==0 && exiting==0)
        monimem.launch();

    if (first_message>0)
    {
        first_message--;
        if (first_message==0)
        {
//            if (file_exists("../record/background_music/pacman.mp3")) movie=startmovie("../record/background_music/pacman.mp3");
            strcpy(error_msg,"F1=HELP F2=DEBUG DIFFICULTY=");
            error_flag=1;
            strcpy(error_msg2,"CTRL-F = AUTOPLAY OFF");
            error_flag2=1;
            strcpy(error_msg3,"CTRL-F = AUTOPLAY OFF");
            error_flag3=1;
            strcpy(error_msg4,"CTRL-F = AUTOPLAY OFF");
            error_flag2=1;
            strcpy(error_msg5,"CTRL-F = AUTOPLAY OFF");
            error_flag5=1;
            if (difficulty==1)
                strcat(error_msg,"EASY");
            if (difficulty==2)
                strcat(error_msg,"NORMAL");
            if (difficulty==3)
                strcat(error_msg,"HARD");
            if (difficulty==4)
                strcat(error_msg,"ULTRA");
            strcat(error_msg," (PRESS 1-4 TO CHANGE)");
        }
    }


    if (MCEDITOR_running) monitor_off=1;
    if (update_request==1) {
        int picturex_back=picturex;
        int picturey_back=picturey;
        int posx_back=posx;
        int posy_back=posy;
        fposx=(int)(fposx);
        fposy=(int)(fposy);
        smooth_x=picturex*1920-posx;
        smooth_y=picturey*1080-posy;
        forced_jump=1;
        ReadBitmaps2();
        follow_ghost_pos();
        if (ffmpegfile==0) {
            int smooth_old=smooth;
            smooth=0;
            smooth_x=0;
            smooth_y=0;
            texture_from_ffmpeg.setSmooth(FALSE);
            perform_quit=1;
            plot_ffmpegfile=1;
            plot_some();
            perform_quit=0;
            smooth=smooth_old;
        }
/*
        picturex=picturex_back;
        picturey=picturey_back;
        posx=posx_back;
        posy=posy_back;
        fposx=posx;
        fposy=posy;
        smooth_x=picturex*1920-posx;
        smooth_x=picturey*1080-posy;
        forced_jump=1;
        ReadBitmaps2();
        follow_ghost_pos();
*/
        texture_from_ffmpeg.create(512+10,512+10);
        for (int xy=0; xy<512+10; xy++) {
            image_plot2.setPixel(0,xy,sf::Color(255,128,0,255));
            image_plot2.setPixel(511+10,xy,sf::Color(255,128,0,255));
            image_plot2.setPixel(xy,0,sf::Color(255,128,0,255));
            image_plot2.setPixel(xy,511+10,sf::Color(255,128,0,255));
        }
        texture_from_ffmpeg.update(image_plot2);
        texture_from_ffmpeg.setRepeated(FALSE);
        texture_from_ffmpeg.setSmooth(FALSE);
        sprite_from_ffmpeg.setTextureRect( {0,0,(int)texture_from_ffmpeg.getSize().x, (int)texture_from_ffmpeg.getSize().y } );
        sprite_from_ffmpeg.setTexture(texture_from_ffmpeg,false);
        sprite_from_ffmpeg.setScale(1.0,1.0);
        rotation_ffmpeg=0.0;
        rot_speed_ffmpeg=0.0;
        scale_now=1.0;
        ffmpeg_move=1;
        ffmpeg_posx=jump_x+1920/2-256;
        ffmpeg_posy=jump_y+1080/2-256;
        ffmpegfile=0;
        blending=1;
        setffmpegfile();
        update_request=0;
//        printf("Updated\n");
    }
    if (jump_request==1) {
/*
        picturex=(int)jump_x/1920;
        posx=jump_x-1920*picturex;
        picturey=(int)jump_y/1080;
        posy=jump_y-1080*picturey;
        picturex=picturex%maxpicturex;
        picturey=picturey%maxpicturey;
        posx=-posx;
        posy=-posy;
        fposx=posx;
        fposy=posy;
        smooth_x=picturex*1920-posx;
        smooth_x=picturey*1080-posy;
        start_posx=(picturex*1920-posx);
        start_posy=(picturey*1080-posy);
*/
        jump_request=0;
        printf("Jumped\n");
    } else {
    }


    int pen_maze_up=maze_up;
    int pen_maze_down=maze_down;
    int pen_maze_left=maze_left;
    int pen_maze_right=maze_right;
    int pen_speedx=speedx;
    int pen_speedy=speedy;
    float fpen_speedx=fspeedx;
    float fpen_speedy=fspeedy;
    int pencontrol=0;

    if (drawmazes==0 && eatmode)  //hoihoi
    {
        strcpy(error_msg,"SETTING EAT MODE=OFF WHEN DRAWMODE=OFF!!!");
        error_flag=1;
        eatmode=0;
    }
    static int check_once=2;

    if (screensaver && check_once) {
        if (check_once==1) {
            insert_key('P');
//            insert_event(sf::Keyboard::P,EVENT_SHIFT);
            F1=0;
            playsound=playsound|7;
            check_once=0;
        } else {
            check_once=1;
        }
    } else if (check_once==2 && the_time>1.0) {
        if (!SFMLView1.hasFocus()) {
            SetFocus(SFMLView1.getSystemHandle());
            if (!SFMLView1.hasFocus()) {
                playsound=playsound|4;
                check_once=1;
            }
        } else check_once=0;
    } else if (check_once==1 && the_time>2.0) {
        check_once=0;
        if (!SFMLView1.hasFocus()) {
            SetFocus(SFMLView1.getSystemHandle());
            if (!SFMLView1.hasFocus()) {
                playsound=playsound|1;
            }
        }
    }


    if (record_screen==1 && record_pause==0)
        the_time=the_time+(float)rate/60.0;
    else if (record_screen==1 && record_pause==0) {}
    else
        the_time=clock_ghost.getElapsedTime().asSeconds();
//flippo
    if ( ( (go_list || go_download || go_burn) && number<50 ) ||
            (number<maxnumber && (the_time>(15.0-(difficulty-2)*2) || (flippo==1 && (number==0 || the_time>15.0))) && force_game==1 && first_message==0 && goexit==0) )
    {
        clock_ghost.restart();
        the_time=0.0;


        number++;
        if (mazetype==0)
        {
            if (number==1 || check[number-2]>1)
            {

                fpos_ghostx[number-1]=1920-position1x;
                fpos_ghosty[number-1]=1080-position1y;
//                fpos_ghostx[number-1]=-1920-32+960+64*1;
//                fpos_ghosty[number-1]=-1080-36+540-0*72;
                pos_ghostx[number-1]=fpos_ghostx[number-1];
                pos_ghosty[number-1]=fpos_ghosty[number-1];
//adaptmaze
//                fpos_ghostx[number-1]=-1920-32+960+64*59;
//                fpos_ghosty[number-1]=-1080-36+540+72*30;
//                fpos_ghostx[number-1]=-1920-32+960;
//                fpos_ghosty[number-1]=-1080-36+540;
                if (hunt==1)
                    fspeed_ghostx[number-1]=2;
                else
                    fspeed_ghostx[number-1]=4;
                fspeed_ghosty[number-1]=0;
                if (flippo==1 && number==1)
                    fspeed_ghostx[number-1]=fspeed_mem;
            }
            else
            {
                fpos_ghostx[number-1]=fpos_ghostx[number-2];
                fpos_ghosty[number-1]=fpos_ghosty[number-2];
                pos_ghostx[number-1]=fpos_ghostx[number-1];
                pos_ghosty[number-1]=fpos_ghosty[number-1];
                fspeed_ghostx[number-1]=fspeed_ghostx[number-2];
                fspeed_ghosty[number-1]=fspeed_ghosty[number-2];
            }
        }
        else
        {
            if (number==1)
            {
                strcpy(error_msg,"GO TO LOWER RIGHT CORNER");
                error_flag=2;
            }
            if (1)
            {
//            if ((rand()%2)==0) {
                if ((maze_plot[(-59+maze_plotsizex)%maze_plotsizex][(-30+maze_plotsizey)%maze_plotsizey]&2)==2)
//                if ((maze_plot[0][0]&2)==2)
                {
                    fspeed_ghosty[number-1]=2.0+(rand()%1001)/(500.0+hunt*500.0);
                    if (burn_subs)
                        fspeed_ghosty[number-1]=fspeed_mem;
                    if (flippo==1 && number==1)
                        fspeed_ghosty[number-1]=fspeed_mem;
                    fspeed_ghostx[number-1]=0;
                }
                else
                {
                    fspeed_ghostx[number-1]=2.0+(rand()%1001)/(500.0+hunt*500.0);
                    if (burn_subs)
                        fspeed_ghostx[number-1]=fspeed_mem;
                    if (flippo==1 && number==1)
                        fspeed_ghostx[number-1]=fspeed_mem;
                    fspeed_ghosty[number-1]=0;
                }
                fpos_ghostx[number-1]=-1920-32+960+64*59;
                fpos_ghosty[number-1]=-1080-36+540+72*30;
                pos_ghostx[number-1]=fpos_ghostx[number-1];
                pos_ghosty[number-1]=fpos_ghosty[number-1];
//                fpos_ghostx[number-1]=-1920-32+960;
//                fpos_ghosty[number-1]=-1080-36+540;
            }
            else
            {
                if ((maze_plot[(hoog-1-59+maze_plotsizex)%maze_plotsizex][(breed-1-30+maze_plotsizey)%maze_plotsizey]&2)==1)
//                if ((maze_plot[hoog-1][breed-1]&2)==1)
                {
                    fspeed_ghosty[number-1]=-(2.0+(rand()%1001)/(500.0+hunt*500.0));
                    fspeed_ghostx[number-1]=0;
                }
                else
                {
                    fspeed_ghostx[number-1]=-(2.0+(rand()%1001)/(500.0+hunt*500.0));
                    fspeed_ghosty[number-1]=0;
                }
                fpos_ghostx[number-1]=-1920-32+960-(hoog-1-59)*64;
                fpos_ghosty[number-1]=-1080-36+540-(breed-1-30)*72;
                pos_ghostx[number-1]=fpos_ghostx[number-1];
                pos_ghosty[number-1]=fpos_ghosty[number-1];
//                fpos_ghostx[number-1]=-1920-32+960-(hoog-1)*64;
//                fpos_ghosty[number-1]=-1080-36+540-(breed-1)*72;

//                fpos_ghostx[number-1]=(-32+960+(hoog-1)*64+maxpixelsx)%maxpixelsx-1920;
//                fpos_ghosty[number-1]=(-36+540+(breed-1)*72+maxpixelsy)%maxpixelsy-1080;
            }
        }
        check[number-1]=0;

    }
    if (testing>0) {
        static int xp=0,yp=0;
        if (posx!=xp || posy!=yp) testing = 200;
        xp=posx;yp=posy;

        testing--;
        if (testing==0) {
            testing=200;
            test_write_to_and_read_from_memory();
        }
    }


//list

    int testsomething=0;
    if (testsomething==1) {
        static int plotx_old=-999999999;
        static int ploty_old=-999999999;
        static int addx=-45+60*totalpicturex;
        static int addy=-23+30*totalpicturey;
        static int modx=30*totalpicturex;
        static int mody=15*totalpicturey;
        static int start_logger=0;
        static int plotx=0;
        static int ploty=0;
        if (follow_ghost==1) {
            int px=(-pos_ghostx[follow_ghost_num]+1920+maxpixelsx)%maxpixelsx;
            int py=(-pos_ghosty[follow_ghost_num]+1080+maxpixelsy)%maxpixelsy;
            static int px_old=-9999999999;
            static int py_old=-9999999999;
            if (abs(px-px_old)>10 || abs(py-py_old)>10) {
                plotx=(px)/64;
                ploty=(py)/72;
                plotx=(plotx+addx)%modx;
                ploty=(ploty+addy)%mody;
                if (plotx!=plotx_old || ploty!=ploty_old) {
                    px_old=px;
                    py_old=py;
                }
            }
        } else {
            int px=(picturex*1920-posx)%maxpixelsx;
            int py=(picturey*1080-posy)%maxpixelsy;
            static int px_old=-9999999999;
            static int py_old=-9999999999;
            if (abs(px-px_old)>10 || abs(py-py_old)>10) {
                plotx=(px)/64;
                ploty=(py)/72;
                plotx=(plotx+addx)%modx;
                ploty=(ploty+addy)%mody;
                if (plotx!=plotx_old || ploty!=ploty_old) {
                    px_old=px;
                    py_old=py;
                }
            }
        }

        if (start_logger==0 && plotx==16 && ploty==0) start_logger=1;
        if (start_logger==1 && (plotx_old!=plotx || ploty_old!=ploty)) {
            char data[100];
            sprintf(data,"%d,%d",plotx,ploty);
            logfile(data);
            plotx_old=plotx;
            ploty_old=ploty;
        }
        if (plotx==15 && ploty==0) start_logger=0;
    }

//jojojo
    static float scaler=1.0;
    static int timer2=0;
    static float size_x;
    if (f8_repeat && movie==0) {
        static int hoppa=0;
        hoppa++;
        if (hoppa==100 && rand()%2)      { int m_old=mirror; mirror=0; insert_event(sf::Keyboard::Key::Left, 0); mirror=m_old; /* if (!(rand()%15)) insert_event(sf::Keyboard::Key::Left, 0); if (rand()%2) insert_event(sf::Keyboard::Key::Down, 0); if (rand()%2) insert_event(sf::Keyboard::Key::Right,0); if (rand()%2) insert_event(sf::Keyboard::Key::Up,   0);*/  }
        else if (hoppa==200 && rand()%2) { int m_old=mirror; mirror=0; insert_event(sf::Keyboard::Key::Up,   0); mirror=m_old; /* if (!(rand()%15)) insert_event(sf::Keyboard::Key::Up,   0); if (rand()%2) insert_event(sf::Keyboard::Key::Left, 0); if (rand()%2) insert_event(sf::Keyboard::Key::Down, 0); if (rand()%2) insert_event(sf::Keyboard::Key::Right,0);*/  }
        else if (hoppa==300 && rand()%2) { int m_old=mirror; mirror=0; insert_event(sf::Keyboard::Key::Right,0); mirror=m_old; /* if (!(rand()%15)) insert_event(sf::Keyboard::Key::Right,0); if (rand()%2) insert_event(sf::Keyboard::Key::Up,   0); if (rand()%2) insert_event(sf::Keyboard::Key::Left, 0); if (rand()%2) insert_event(sf::Keyboard::Key::Down, 0);*/  }
        else if (hoppa==400 && rand()%2) { int m_old=mirror; mirror=0; insert_event(sf::Keyboard::Key::Down, 0); mirror=m_old; /* if (!(rand()%15)) insert_event(sf::Keyboard::Key::Down, 0); if (rand()%2) insert_event(sf::Keyboard::Key::Right,0); if (rand()%2) insert_event(sf::Keyboard::Key::Up,   0); if (rand()%2) insert_event(sf::Keyboard::Key::Left, 0);*/  }
        if (hoppa==400) hoppa=0;
        static int hoppa2=0;
        hoppa2++;

        if (hoppa2>=60*10) {
            hoppa2=0;
            if (live_movie->getStatus()==sfe::Stopped)
                updatemovie();
            else
            {
                timer2++;
                time_movie=live_movie->getDuration();
                int add=20.0+rand()%( int( time_movie.asSeconds() - 30.0 )  );
//                printf("time: %d  add: %d  ",int( time_movie.asSeconds() ), add);

                if ( timer2<(2+time_movie.asSeconds()/1600) && add>1.0 && add < int(time_movie.asSeconds()-11.0) )
                {
                    printf( "timer=%d  duration=%d  is=%d  goto=%d  ->  ",
                           timer2,int(time_movie.asSeconds()),int(live_movie->getPlayingOffset().asSeconds()), add );

                    time_movie=sf::seconds((float)add);

                    try
                    {
                        char sys[1000];
                        sprintf(sys,"echo \"offset: %s\" >> movie_offset.log",movie_name);
                        system(sys);

                        live_movie->setPlayingOffset(time_movie);
                    }
                    catch (std::exception const &exc)
                    {
                        std::cerr << "\nException caught " << exc.what() << "\n";
                        printf( "is=%d\n",int(live_movie->getPlayingOffset().asSeconds()) );
                        if (live_movie->getStatus() != sfe::Playing) {
                            printf("    next3: ");

                            try
                            {
                                live_movie->stop();
                                updatemovie();

                                time_movie=live_movie->getDuration();
                                int add=20+rand()%( int( time_movie.asSeconds() - 30.0 )  );
                                if ( add>1.0 && add < int(time_movie.asSeconds()-11.0) )
                                {
                                    printf( "   timer=%d  duration=%d  is=%d  goto=%d  ->  ",
                                           timer2,int(time_movie.asSeconds()),int(live_movie->getPlayingOffset().asSeconds()), add );
                                    time_movie=sf::seconds((float)add);
                                    live_movie->setPlayingOffset(time_movie);
                                }
                            }
                            catch (std::exception const &exc)
                            {

                                char sys[1000];
                                sprintf(sys,"echo \"%s\" >> movie_error.log",movie_name);
                                system(sys);

                                std::cerr << "\n    Exception caught " << exc.what() << "\n";
                                printf( "   is=%d\n",int(live_movie->getPlayingOffset().asSeconds()) );
                            }

                            printf("    playing\n");
//                            live_movie->play();
                        }
                    }
                    catch (...)
                    {
                        std::cerr << "\nUnknown exception caught\n";
                    }
//                    rotation_movie=sin(fpstime/3.0)*30;
//                    rotation_movie=rand()%61-30;
//                    rot_speed_movie=-rotation_movie/1200.0;
                    rotate_canvas=1;
                    rotate_movie=1;
//                    rot_speed_movie=(rand()%61)/1200.0;
//                    rot_speed_canvas=-rot_speed_movie*2.0;
                    printf("done\n");
                    srand(time(0));
                }
                else
                {
//                    size_x=sprite_from_movie.getScale().x*texture_from_movie_new.getSize().x;
                    timer2=0;
                    printf("next2: ");
                    try
                    {
                        live_movie->stop();
                        updatemovie();
                        time_movie=live_movie->getDuration();
                        int add=20+rand()%( int( time_movie.asSeconds() - 30.0 )  );
                        if ( add>1.0 && add < int(time_movie.asSeconds()-11.0) )
                        {
                            printf( "   timer=%d  duration=%d  is=%d  goto=%d  ->  ",
                                   timer2,int(time_movie.asSeconds()),int(live_movie->getPlayingOffset().asSeconds()), add );
                            time_movie=sf::seconds((float)add);
                            live_movie->setPlayingOffset(time_movie);
                        }
                    }
                    catch (std::exception const &exc)
                    {

                        char sys[1000];
                        sprintf(sys,"echo \"%s\" >> movie_error.log",movie_name);
                        system(sys);

                        std::cerr << "\nException caught " << exc.what() << "\n";
                        printf( "is=%d\n",int(live_movie->getPlayingOffset().asSeconds()) );
                        if (live_movie->getStatus() != sfe::Playing) {
                            printf("    next3: ");

                            try
                            {
                                live_movie->stop();
                                updatemovie();

                                time_movie=live_movie->getDuration();
                                int add=20+rand()%( int( time_movie.asSeconds() - 30.0 )  );
                                if ( add>1.0 && add < int(time_movie.asSeconds()-11.0) )
                                {
                                    printf( "   timer=%d  duration=%d  is=%d  goto=%d  ->  ",
                                           timer2,int(time_movie.asSeconds()),int(live_movie->getPlayingOffset().asSeconds()), add );
                                    time_movie=sf::seconds((float)add);
                                    live_movie->setPlayingOffset(time_movie);
                                }
                            }
                            catch (std::exception const &exc)
                            {

                                char sys[1000];
                                sprintf(sys,"echo \"%s\" >> movie_error.log",movie_name);
                                system(sys);

                                std::cerr << "\n    Exception caught " << exc.what() << "\n";
                                printf( "   is=%d\n",int(live_movie->getPlayingOffset().asSeconds()) );
                            }
                            printf("    playing\n");
    //                            live_movie->play();
                        }
                    }
                    catch (...)
                    {
                        std::cerr << "\nUnknown exception caught\n";
                    }
                    printf("playing\n");
//                    scaler=size_x/texture_from_movie_new.getSize().x;
                }


//                printf("new time: %d\n ",int( time_movie.asSeconds() ));


/*
                time_movie=live_movie->getPlayingOffset();
                int add=rand()%600;
                if ( live_movie->getDuration() > (time_movie+sf::seconds(add + 11) ) )
                {
                    live_movie->setPlayingOffset(time_movie+sf::seconds(add));
//                                rotation_movie=rand()%41-20;
                }
                else
                {
                    size_x=sprite_from_movie.getScale().x*texture_from_movie_new.getSize().x;
                    live_movie->stop();
                    updatemovie();

                    scaler=size_x/texture_from_movie_new.getSize().x;
                }
*/
            }
        }

        scaler=size_x/(float)texture_from_movie_new.getSize().x;
        float scaler_mod=(1.0+sin(fpstime/5.0)/1.8);
        float f=(scaler*scaler_mod);

        fspeedx=fspeedx+sin(fpstime/2.13)/911.0+sin(fpstime/5.77)/2400.0;
        fspeedy=fspeedy+cos(fpstime/2.13)/911.0+cos(fpstime/5.77)/2400.0;
        speedx=fspeedx;
        speedy=fspeedy;
        sprite_from_movie.setScale(f,f);
        rotation_movie=sin(fpstime/3.0)*40;
    } else if (movie==0) {
        scaler=sprite_from_movie.getScale().x;
        size_x=scaler*(float)texture_from_movie_new.getSize().x;
    }

//hopla
    if (flippo==1 && number>=1)
        fspeed_mem=fabs(fspeed_ghostx[follow_ghost_num])+fabs(fspeed_ghosty[follow_ghost_num]);
    if ( (pen==1 && (fspeedx!=0 || fspeedy!=0 || toggle_point==1)) && follow_ghost==0 && goexit==0 )
//    if ( (pen==1 && (fspeedx!=0 || fspeedy!=0 || toggle_point==1)) && goexit==0 )
    {
        pencontrol=1;
//pospos
        posx=posx-posx%64-32;
        if (posx<-1920)
//        if (posx<=-1920)
        {
            posx=posx+1920;
            picturex=(picturex+1+totalpicturex)%totalpicturex;
        }
        posy=posy-(posy-36)%72-36;
        if (posy<-1080)
//        if (posy<=-1080)
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
        */
        mazemovex=(picturex*1920-posx-32)/64;
        mazemovey=(picturey*1080-posy   )/72;
        mazemovex=(mazemovex-45+60*(maxpicturex+1))%(30*(maxpicturex+1));
        mazemovey=(mazemovey-23+30*(maxpicturey+1))%(15*(maxpicturey+1));


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

        int blokje=maze_plot[mazemovex][mazemovey];

        if (toggle_point==1)
        {
            toggle_point=0;
            if ((maze_plot[mazemovex][mazemovey]&16)==16)
                maze_plot[mazemovex][mazemovey]=maze_plot[mazemovex][mazemovey]&15;
            else
                maze_plot[mazemovex][mazemovey]=maze_plot[mazemovex][mazemovey]|16;
            do_mirror(mazemovex,mazemovey,16);
        }

        if (pen_mode==0)
        {
            if (pen_maze_up==1)
            {
                maze_plot[mazemovex][mazemovey]=maze_plot[mazemovex][mazemovey] | 1;
                do_mirror(mazemovex,mazemovey,1);
            }
            else if (pen_maze_down==1)
            {
                maze_plot[mazemovex][mazemovey]=maze_plot[mazemovex][mazemovey] | 2;
                do_mirror(mazemovex,mazemovey,2);
            }
            else if (pen_maze_left==1)
            {
                maze_plot[mazemovex][mazemovey]=maze_plot[mazemovex][mazemovey] | 4;
                do_mirror(mazemovex,mazemovey,4);
            }
            else if (pen_maze_right==1)
            {
                maze_plot[mazemovex][mazemovey]=maze_plot[mazemovex][mazemovey] | 8;
                do_mirror(mazemovex,mazemovey,8);
            }
            else
            {
                do_mirror(mazemovex,mazemovey,0);
            }
        }
        else if (pen_mode==1)
        {
            if (pen_maze_up==1)
            {
                maze_plot[mazemovex][mazemovey]=maze_plot[mazemovex][mazemovey] & (15-1);
                do_mirror(mazemovex,mazemovey,1);
                if (combine==1)
                {
                    maze_plot[mazemovex][mazemovey]&=(15-4-8-2);
                    do_mirror(mazemovex,mazemovey,14);
                    maze_plot[(mazemovex-1+maze_plotsizex)%maze_plotsizex][mazemovey]&=(15-8);
                    do_mirror(mazemovex-1,mazemovey,8);
                    maze_plot[(mazemovex+1)%maze_plotsizex][mazemovey]&=(15-4);
                    do_mirror(mazemovex+1,mazemovey,4);
                    maze_plot[mazemovex][(mazemovey+1)%maze_plotsizey]&=(15-1);
                    do_mirror(mazemovex,mazemovey+1,1);
                }
            }
            else if (pen_maze_down==1)
            {
                maze_plot[mazemovex][mazemovey]=maze_plot[mazemovex][mazemovey] & (15-2);
                do_mirror(mazemovex,mazemovey,2);
                if (combine==1)
                {
                    maze_plot[mazemovex][mazemovey]&=(15-4-8-1);
                    do_mirror(mazemovex,mazemovey,13);
//                    do_mirror(mazemovex,mazemovey,12);
                    maze_plot[(mazemovex-1+maze_plotsizex)%maze_plotsizex][mazemovey]&=(15-8);
                    do_mirror(mazemovex-1,mazemovey,8);
                    maze_plot[(mazemovex+1)%maze_plotsizex][mazemovey]&=(15-4);
                    do_mirror(mazemovex+1,mazemovey,4);
                    maze_plot[mazemovex][(mazemovey-1+maze_plotsizey)%maze_plotsizey]&=(15-2);
                    do_mirror(mazemovex,mazemovey-1,2);
                }
            }
            else if (pen_maze_left==1)
            {
                maze_plot[mazemovex][mazemovey]&=(15-4);
                do_mirror(mazemovex,mazemovey,4);
                if (combine==1)
                {
                    maze_plot[mazemovex][mazemovey]&=(15-1-2-8);
                    do_mirror(mazemovex,mazemovey,11);
//                    do_mirror(mazemovex,mazemovey,3);
                    maze_plot[mazemovex][(mazemovey-1+maze_plotsizey)%maze_plotsizey]&=(15-2);
                    do_mirror(mazemovex,mazemovey-1,2);
                    maze_plot[mazemovex][(mazemovey+1)%maze_plotsizey]&=(15-1);
                    do_mirror(mazemovex,mazemovey+1,1);
                    maze_plot[(mazemovex+1)%maze_plotsizex][mazemovey]&=(15-4);
                    do_mirror(mazemovex+1,mazemovey,4);
                }
            }
            else if (pen_maze_right==1)
            {
                maze_plot[mazemovex][mazemovey]=maze_plot[mazemovex][mazemovey] & (15-8);
                do_mirror(mazemovex,mazemovey,8);
                if (combine==1)
                {
                    maze_plot[mazemovex][mazemovey]&=(15-1-2-4);
                    do_mirror(mazemovex,mazemovey,7);
//                    do_mirror(mazemovex,mazemovey,3);
                    maze_plot[mazemovex][(mazemovey-1+maze_plotsizey)%maze_plotsizey]&=(15-2);
                    do_mirror(mazemovex,mazemovey-1,2);
                    maze_plot[mazemovex][(mazemovey+1)%maze_plotsizey]&=(15-1);
                    do_mirror(mazemovex,mazemovey+1,1);
                    maze_plot[(mazemovex-1+maze_plotsizex)%maze_plotsizex][mazemovey]&=(15-8);
                    do_mirror(mazemovex-1,mazemovey,8);
                }
            }
            else
            {
//                do_mirror(mazemovex,mazemovey,0);
            }
        }

        posx=posx+pen_speedx;
        posy=posy+pen_speedy;
        fposx=posx;
        fposy=posy;
//pospos
//jojojo
        if (posx<-1920)
        {
            posx=posx+1920;
            fposx=fposx+1920;
//            posx=posx;
            picturex++;
            if (picturex>maxpicturex)
                picturex=0;
            ReadBitmaps2();
        }
        else if (posx>=0)
        {
            posx=posx-1920;
            fposx=fposx-1920;
//            fposx=posx;
            picturex--;
            if (picturex<0)
                picturex=maxpicturex;
            ReadBitmaps2();
        }
        if (posy<-1080)
        {
            posy=posy+1080;
            fposy=fposy+1080;
//            fposy=posy;
            picturey++;
            if (picturey>maxpicturey)
                picturey=0;
            ReadBitmaps2();
        }
        else if (posy>=0)
        {
            posy=posy-1080;
            fposy=fposy-1080;
//            fposy=posy;
            picturey--;
            if (picturey<0)
                picturey=maxpicturey;
            ReadBitmaps2();
        }

        if (fspeedx<0)
            packy=0;
        if (fspeedx>0)
            packy=1;
        if (fspeedy<0)
            packy=2;
        if (fspeedy>0)
            packy=3;
        /*
                if (pen_speedx<0)
                    packy=0;
                if (pen_speedx>0)
                    packy=1;
                if (pen_speedy<0)
                    packy=2;
                if (pen_speedy>0)
                    packy=3;
        */

        toggle_point=0;

        if (blokje!=maze_plot[mazemovex][mazemovey])
            levelnotsaved=1;

        if (connected==1)
        {
            if (blokje!=maze_plot[mazemovex][mazemovey])
            {
                sprintf(writer,"T=PLOT,X=%d,Y=%d,M=%d,PEN_MODE=%d,\0",mazemovex,mazemovey,maze_plot[mazemovex][mazemovey],pen_mode);
                SEND(writer);
            }
            else
            {
                static int old_movex;
                static int old_movey;
                if (mazemovex!=old_movex || mazemovey!=old_movey)
                {
                    sprintf(writer,"T=GOTO,X=%d,Y=%d,\0",mazemovex,mazemovey);
                    SEND(writer);
                    old_movex=mazemovex;
                    old_movey=mazemovey;
                }
            }
        }
    }
    int numloops;
    int loops;

    int posx_old;
    int posy_old;
    float fposx_old;
    float fposy_old;

    if (follow_ghost_start==1)
    {
        follow_ghost_pos();
        follow_ghost_start=0;
    }
    int remem_posx;
    int remem_posy;
    float remem_fposx;
    float remem_fposy;
    int remem_picturex;
    int remem_picturey;

    /*
        if (flippo==1) {
            remem_posx=posx;
            remem_posy=posy;
            remem_fposx=fposx;
            remem_fposy=fposy;
            remem_picturex=picturex;
            remem_picturey=picturey;
            posx=mem_posx;
            posy=mem_posy;
            fposx=mem_fposx;
            fposy=mem_fposy;
            picturex=mem_picturex;
            picturey=mem_picturey;
        }
    */
    static int first1=1;
    /*
            if (flippo==0 && first1==3) {
                    if (fspeedx==0) {
                        posx=posx-posx%64-32;
                        fposx=posx;
                    }
                    if (posx<=-1920) {
                        posx=posx+1920;
                        picturex=(picturex+1+totalpicturex)%totalpicturex;
                    }
                    posy=posy-(posy-36)%72-36;
                    if (fspeedy==0) {
                        posy=posy-(posy-36)%72-36;
                        fposy=posy;
                    }
                    if (posy<=-1080) {
                        posy=posy+1080;
                        picturey=(picturey+1+totalpicturey)%totalpicturey;
                    }
            }
    */
    /*
            if (flippo==0) first1=1;
            if (flippo==1) {
                static int old_follow_ghost_num=follow_ghost_num;
                if (old_follow_ghost_num!=follow_ghost_num) first1=1;
                old_follow_ghost_num=follow_ghost_num;

                static float old_fposx=fpos_ghostx[follow_ghost_num];
                static float old_fposy=fpos_ghosty[follow_ghost_num];
                static float old_fspeedx=-fspeed_ghostx[follow_ghost_num];
                static float old_fspeedy=-fspeed_ghosty[follow_ghost_num];

                if (first1==1) {
                    old_fposx=fpos_ghostx[follow_ghost_num];
                    old_fposy=fpos_ghosty[follow_ghost_num];
                    old_fspeedx=-fspeed_ghostx[follow_ghost_num];
                    old_fspeedy=-fspeed_ghosty[follow_ghost_num];
                    smooth_x=-(old_fposx)+1920.0;
                    smooth_y=-(old_fposy)+1080.0;
                    float x=smooth_x;
                    float y=smooth_y;
                    picturex=(int)x/1920;
                    fposx=x-1920.0*picturex;
                    picturey=(int)y/1080;
                    fposy=y-1080.0*picturey;
                    fposx=-fposx;
                    fposy=-fposy;
                    posx=posx;
                    posy=posy;
                    fspeedx=0;
                    fspeedy=0;
                    speedx=fspeedx;
                    speedy=fspeedy;
                    fspeedx_new=fspeedx;
                    fspeedy_new=fspeedy;
                    speedx_new=fspeedx_new;
                    speedy_new=fspeedy_new;
                    maze_up=0;
                    maze_down=0;
                    maze_left=0;
                    maze_right=0;
                    maze_up_new=0;
                    maze_down_new=0;
                    maze_left_new=0;
                    maze_right_new=0;
                    if (fspeedx_new<0.0)  { maze_left_new=1;  }
                    else if (fspeedx_new>0.0) {maze_right_new=1; }
                    if (fspeedy_new<0.0) {maze_up_new=1;  }
                    else if (fspeedy_new>0.0) {maze_down_new=1; }
                    first1=2;
                } else {
                    float smooth_x=-(old_fposx)+1920.0;
                    float smooth_y=-(old_fposy)+1080.0;
                    float x=smooth_x;
                    float y=smooth_y;
                    picturex=(int)x/1920;
                    fposx=x-1920.0*picturex;
                    picturex=(picturex+totalpicturex)%totalpicturex;
                    picturey=(int)y/1080;
                    fposy=y-1080.0*picturey;
                    picturey=(picturey+totalpicturey)%totalpicturey;
                    fposx=-fposx;
                    fposy=-fposy;
                    posx=fposx;
                    posy=fposy;
                    fspeedx=old_fspeedx;
                    fspeedy=old_fspeedy;
                    speedx=fspeedx;
                    speedy=fspeedy;

                    if (!( (fspeedx>0.0 && -fspeed_ghostx[follow_ghost_num]<0.0) ||
                           (fspeedx<0.0 && -fspeed_ghostx[follow_ghost_num]>0.0) ||
                           (fspeedy>0.0 && -fspeed_ghosty[follow_ghost_num]<0.0) ||
                           (fspeedy<0.0 && -fspeed_ghosty[follow_ghost_num]>0.0) )) {
                        fspeedx_new=-fspeed_ghostx[follow_ghost_num];
                        fspeedy_new=-fspeed_ghosty[follow_ghost_num];
                        speedx_new=fspeedx_new;
                        speedy_new=fspeedy_new;

                        maze_up_new=0;
                        maze_down_new=0;
                        maze_left_new=0;
                        maze_right_new=0;
                        if (fspeedx_new<0.0)  { maze_left_new=1;  }
                        else if (fspeedx_new>0.0) {maze_right_new=1; }
                        if (fspeedy_new<0.0) {maze_up_new=1;  }
                        else if (fspeedy_new>0.0) {maze_down_new=1; }
                    } else {
                        maze_up_new=0;
                        maze_down_new=0;
                        maze_left_new=0;
                        maze_right_new=0;
                        if (fspeedx<0.0)  { maze_left_new=1;  }
                        else if (fspeedx>0.0) {maze_right_new=1; }
                        if (fspeedy<0.0) {maze_up_new=1;  }
                        else if (fspeedy>0.0) {maze_down_new=1; }
                    }
                    if (fspeedx==0) {
                        posx=posx-posx%64-32;
                        fposx=posx;
                    } else if (fspeedy==0) {
                        posy=posy-(posy-36)%72-36;
                        fposy=posy;
                    }
                    first1=3;
                }
                old_fposx=fpos_ghostx[follow_ghost_num];
                old_fposy=fpos_ghosty[follow_ghost_num];
                old_fspeedx=-fspeed_ghostx[follow_ghost_num];
                old_fspeedy=-fspeed_ghosty[follow_ghost_num];
            }
    */


//    if (combine==1 || sf::Mouse::isButtonPressed(sf::Mouse::Right)) color_to_gradient();

    if (flippo==1)
    {

        float x=-(fpos_ghostx[follow_ghost_num])+1920.0;
        float y=-(fpos_ghosty[follow_ghost_num])+1080.0;
        picturex=(int)x/1920;
        fposx=x-1920.0*picturex;
        picturex=(picturex+totalpicturex)%totalpicturex;
        picturey=(int)y/1080;
        fposy=y-1080.0*picturey;
        picturey=(picturey+totalpicturey)%totalpicturey;
        fposx=-fposx;
        fposy=-fposy;
//        fposx=-fposx+(float)smooth_x-(float)((int)smooth_x);
//        fposy=-fposy+(float)smooth_y-(float)((int)smooth_y);
        posx=fposx;
        posy=fposy;
        fspeedx=-fspeed_ghostx[follow_ghost_num];
        fspeedy=-fspeed_ghosty[follow_ghost_num];
        if (fspeedx>0.0)
            speedx=1;
        else if (fspeedx<0.0)
            speedx=-1;
        if (fspeedy>0.0)
            speedy=1;
        else if (fspeedy<0.0)
            speedy=-1;
//        speedx=fspeedx;
//        speedy=fspeedy;
        maze_up_new=0;
        maze_down_new=0;
        maze_left_new=0;
        maze_right_new=0;
        if (fspeedx<0.0)
        {
            maze_left=1;
        }
        else if (fspeedx>0.0)
        {
            maze_right=1;
        }
        if (fspeedy<0.0)
        {
            maze_up=1;
        }
        else if (fspeedy>0.0)
        {
            maze_down=1;
        }
        fspeedx=0.0;
        fspeedy=0.0;
    }
    float fpos_total;
    float remain=0.0;

    if ((fspeedx==0 && fspeedy==0 && pressed==0))
    {
        numloops=0;
    }
    else if (flippo==0)
    {
        if (flippo==0)
            fpos_total=fabs(fspeedx*fspeed_adjust)+fabs(fspeedy*fspeed_adjust);
        else
            fpos_total=0.0;

        if (mouse_move==0 && pen==0 && goexit==0 && pacman==1 && flippo==0)
        {
            posx_old=posx;
            posy_old=posy;

            fposx_old=fposx;
            fposy_old=fposy;

            if (flippo==0)
            {
                fposx=fposx+fspeedx*fspeed_adjust;
                fposy=fposy+fspeedy*fspeed_adjust;
            }

            posx=fposx;
            posy=fposy;

//            if (fspeedx<0.0 || fspeedy<0.0)
//                fpos_total=fpos_total;
//            else if (fspeedx>0.0 || fspeedy>0.0)
//                fpos_total=fpos_total;
            remain=fposx_old-(float)posx_old+fposy_old-(float)posy_old;

            if ( (abs(posx-posx_old) >= 1) || (abs(posy-posy_old) >= 1))
            {
                numloops=abs(posx-posx_old)+abs(posy-posy_old);

                if (fspeedx<0.0)
                {
                    posx=posx_old-1;
                    fpos_total--;
                }
                else if (fspeedx>0.0)
                {
                    posx=posx_old+1;
                    fpos_total--;
                }
                if (fspeedy<0.0)
                {
                    posy=posy_old-1;
                    fpos_total--;
                }
                else if (fspeedy>0.0)
                {
                    posy=posy_old+1;
                    fpos_total--;
                }
            }
            else
            {
                numloops=1;
                posx=posx_old;
                posy=posy_old;
            }
            fposx=fposx_old;
            fposy=fposy_old;
        }
        else
            numloops=1;
    }
    else
    {
        numloops=1;
    }
    if (flippo==1)
    {
        fspeedx=-fspeed_ghostx[follow_ghost_num];
        fspeedy=-fspeed_ghosty[follow_ghost_num];
    }

    if (follow_ghost==1)
        numloops=0;
    if (mouse_move==1)
        numloops=0;
    for (loops=0; loops<numloops; loops++)
    {
        if (pen==0)
        {
        }
        float fspeedx_old=fspeedx;
        float fspeedy_old=fspeedy;
        int	speedx_old=speedx;
        int	speedy_old=speedy;
        if (flippo==0 && pen==0 && ((internetfile!=0 && movie!=0 && ffmpegfile!=0 && pacman==1) || (pen==0 && force_game==1  )) && drawmazes==1 )
        {
            int	maze_down_old=maze_down;
            int	maze_up_old=maze_up;
            int	maze_left_old=maze_left;
            int	maze_right_old=maze_right;

            int mazemovex_next;
            int mazemovey_next;

            if ( (((posx+32)%64)==0) && ((maze_up_new==1) ) )
            {
                if ( (((posy)%72)!=0) )
                {
                    speedy=speedy_new;
                    fspeedy=fspeedy_new;
                    maze_up=maze_up_new;
                }
            }
            if ( (((posx+32)%64)==0) && ((maze_down_new==1)) )
            {
                if ( (((posy)%72)!=0) )
                {
                    speedy=speedy_new;
                    fspeedy=fspeedy_new;
                    maze_down=maze_down_new;
                }
            }
            if ( ( ((posy)%72)==0) && ( (maze_left_new==1)) )
            {
                if ( (((posx+32)%64)!=0) )
                {
                    speedx=speedx_new;
                    fspeedx=fspeedx_new;
                    maze_left=maze_left_new;
                }
            }
            if ( ( ((posy)%72)==0) && ((maze_right_new==1) ) )
            {
                if ( (((posx+32)%64)!=0) )
                {
                    speedx=speedx_new;
                    fspeedx=fspeedx_new;
                    maze_right=maze_right_new;
                }
            }

            if ( (  ((posx+32)%64)==0) && ((posy%72)==0)  && drawmazes==1)
            {
                mazemovex_next=(picturex*1920-posx-32)/64;
                mazemovey_next=(picturey*1080-posy   )/72;
                mazemovex_next=(mazemovex_next-45+30*(maxpicturex+1) )%(30*(maxpicturex+1));
                mazemovey_next=(mazemovey_next-23+15*(maxpicturey+1) )%(15*(maxpicturey+1));

                static float fspeedx_last=0.0,fspeedy_last=0.0;

                if (fspeedx!=0.0 || fspeedy!=0.0)
                {
                    fspeedx_last=fspeedx;
                    fspeedy_last=fspeedy;
                }

                if (maze_down_new==1)
                {
//crossing
//                    if ( ( (maze_plot[mazemovex_next][mazemovey_next]) & 2) == 0 )
                    if ( ( (maze_plot[mazemovex_next][mazemovey_next]) & 2) == 0 || ( (maze_plot[mazemovex_next][mazemovey_next]) & 32) == 32 ||
                            ( ( (maze_plot[mazemovex_next][mazemovey_next]) & 64) == 64 && fspeedx_last!=0.0) )
                    {
                        maze_down=maze_down_old;
                        maze_up=maze_up_old;
                        maze_left=maze_left_old;
                        maze_right=maze_right_old;
                        speedx=speedx_old;
                        speedy=speedy_old;
                        fspeedx=fspeedx_old;
                        fspeedy=fspeedy_old;
                    }
                    else
                    {
                        maze_down=maze_down_new;
                        maze_up=maze_up_new;
                        maze_left=maze_left_new;
                        maze_right=maze_right_new;
                        speedx=speedx_new;
                        speedy=speedy_new;
                        fspeedx=fspeedx_new;
                        fspeedy=fspeedy_new;
                    }
                }
                if (maze_up_new==1 )
                {
                    if ( ( (maze_plot[mazemovex_next][mazemovey_next]) & 1) == 0 || ( (maze_plot[mazemovex_next][mazemovey_next]) & 32) == 32 ||
                            ( ( (maze_plot[mazemovex_next][mazemovey_next]) & 64) == 64 && fspeedx_last!=0) )
                    {
                        maze_down=maze_down_old;
                        maze_up=maze_up_old;
                        maze_left=maze_left_old;
                        maze_right=maze_right_old;
                        speedx=speedx_old;
                        speedy=speedy_old;
                        fspeedx=fspeedx_old;
                        fspeedy=fspeedy_old;
                    }
                    else
                    {
                        maze_down=maze_down_new;
                        maze_up=maze_up_new;
                        maze_left=maze_left_new;
                        maze_right=maze_right_new;
                        speedx=speedx_new;
                        speedy=speedy_new;
                        fspeedx=fspeedx_new;
                        fspeedy=fspeedy_new;
                    }
                }
                if (maze_left_new==1)
                {
                    if ( ( (maze_plot[mazemovex_next][mazemovey_next]) & 4) == 0 || ( (maze_plot[mazemovex_next][mazemovey_next]) & 64) == 64 ||
                            ( ( (maze_plot[mazemovex_next][mazemovey_next]) & 32) == 32 && fspeedy_last!=0) )
                    {
                        maze_down=maze_down_old;
                        maze_up=maze_up_old;
                        maze_left=maze_left_old;
                        maze_right=maze_right_old;
                        speedx=speedx_old;
                        speedy=speedy_old;
                        fspeedx=fspeedx_old;
                        fspeedy=fspeedy_old;
                    }
                    else
                    {
                        maze_down=maze_down_new;
                        maze_up=maze_up_new;
                        maze_left=maze_left_new;
                        maze_right=maze_right_new;
                        speedx=speedx_new;
                        speedy=speedy_new;
                        fspeedx=fspeedx_new;
                        fspeedy=fspeedy_new;
                    }
                }
                if (maze_right_new==1)
                {
                    if ( ( (maze_plot[mazemovex_next][mazemovey_next]) & 8) == 0 || ( (maze_plot[mazemovex_next][mazemovey_next]) & 64) == 64 ||
                            ( ( (maze_plot[mazemovex_next][mazemovey_next]) & 32) == 32 && fspeedy_last!=0) )
                    {
                        maze_down=maze_down_old;
                        maze_up=maze_up_old;
                        maze_left=maze_left_old;
                        maze_right=maze_right_old;
                        speedx=speedx_old;
                        speedy=speedy_old;
                        fspeedx=fspeedx_old;
                        fspeedy=fspeedy_old;
                    }
                    else
                    {
                        maze_down=maze_down_new;
                        maze_up=maze_up_new;
                        maze_left=maze_left_new;
                        maze_right=maze_right_new;
                        speedx=speedx_new;
                        speedy=speedy_new;
                        fspeedx=fspeedx_new;
                        fspeedy=fspeedy_new;
                    }
                }

                if (maze_down==1)
                {
                    if ( ( (maze_plot[mazemovex_next][mazemovey_next]) & 2) == 0 )
                    {
                        speedx=0;
                        speedy=0;
                        fspeedx=0;
                        fspeedy=0;
                        maze_up=0;
                        maze_down=0;
                        maze_left=0;
                        maze_right=0;
                    }
                }
                if (maze_up==1 )
                {
                    if ( ( (maze_plot[mazemovex_next][mazemovey_next]) & 1) == 0 )
                    {
                        speedx=0;
                        speedy=0;
                        fspeedx=0;
                        fspeedy=0;
                        maze_up=0;
                        maze_down=0;
                        maze_left=0;
                        maze_right=0;
                    }
                }
                if (maze_left==1)
                {
                    if ( ( (maze_plot[mazemovex_next][mazemovey_next]) & 4) == 0 )
                    {
                        speedx=0;
                        speedy=0;
                        fspeedx=0;
                        fspeedy=0;
                        maze_up=0;
                        maze_down=0;
                        maze_left=0;
                        maze_right=0;
                    }
                }
                if (maze_right==1)
                {
                    if ( ( (maze_plot[mazemovex_next][mazemovey_next]) & 8) == 0 )
                    {
                        speedx=0;
                        speedy=0;
                        fspeedx=0;
                        fspeedy=0;
                        maze_up=0;
                        maze_down=0;
                        maze_left=0;
                        maze_right=0;
                    }
                }
                if (pressed==1 && speedx==0 && speedy==0)
                    playsound=playsound|4;
            }
        }
        pressed=0;


//        if (pen==0 && ((internetfile!=0 && movie!=0 && ffmpegfile!=0 ) || (pen==0 && force_game==1 )) && drawmazes==1 )
        if (flippo==0 && pen==0 && ((internetfile!=0 && movie!=0 && ffmpegfile!=0 && pacman==1) || (pen==0 && force_game==1 )) && drawmazes==1 )
        {
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

                int arx=(picturex+mapx)%(maxpicturex+1);
                int ary=(picturey+mapy)%(maxpicturey+1);
                sprite_point.setTexture(texturemaxinmempoint[used2[arx][ary]]->getTexture(),false);
                sprite_point.setTextureRect(   { xdraw, ydraw,1, 1 }  );
                sprite_point.setPosition(0,0);
                texture_point.draw(sprite_point);
                texture_point.display();
                image_point=texture_point.getTexture().copyToImage();
                pixel_color=image_point.getPixel(0,0);
                int trans=(pixel_color.toInteger())&255;
                color=(pixel_color.toInteger())>>8;

                static int last_posx;
                static int last_posy;

                mazemovex=(picturex*1920-posx-32)/64;
                mazemovey=(picturey*1080-posy   )/72;

                mazemovex=(mazemovex-45+60*(maxpicturex+1))%(30*(maxpicturex+1));
                mazemovey=(mazemovey-23+30*(maxpicturey+1))%(15*(maxpicturey+1));

                int blokje=maze_plot[mazemovex][mazemovey];

                int go_on;
                go_on=0;
                if ((blokje&15)==0)
                    go_on=0;
                else if ( (blokje&(32+64))>0 )
                {
                    if (fspeedx!=0 && (blokje&32)==32 || ((posx-32)%64!=0))
                        go_on=1;
                    else if (fspeedy!=0 && (blokje&64)==64 || ((posy)%72!=0) )
                        go_on=1;
                }
                else
                    go_on=1;

                if ( (color==16773632 && SFML==1) && go_on==1)
                {
                    total_points--;
                    local_points++;
                    if (fhapper==0)
                    {
                        soundloop=soundloop|1;
                        playsound=playsound|1;
                    }
                    fhapper=40.0/fspeed_adjust;

                    if ((blokje&16)==16 && ((posx-32)%64==0) && ( (posy)%72==0))
                    {
                        if ((xdraw-9)<0)
                            RenderBlit(0,       mapy,   1920+xdraw-9,   ydraw-8,        18, 16, 0, 5*72);
                        if ((ydraw-8)<0)
                            RenderBlit(mapx,    0,      xdraw-9,        1080+ydraw-8,   18, 16, 0, 5*72);
                        RenderBlit(mapx,    mapy,   xdraw-9,        ydraw-8,        18, 16, 0, 5*72);
                    }
                    else
                    {
                        if ((xdraw-7)<0)
                            RenderBlit(0,       mapy,   1920+xdraw-7,   ydraw-6,        14, 12, 0, 5*72);
                        if ((ydraw-6)<0)
                            RenderBlit(mapx,    0,      xdraw-7,        1080+ydraw-6,   14, 12, 0, 5*72);
                        RenderBlit(mapx,    mapy,   xdraw-7,        ydraw-6,        14, 12, 0, 5*72);
//                        printf("posx=%d posy=%d picturex=%d picturey=%d mapx=%d mapy=%d xdraw=%d ydraw=%d\n",posx,posy,picturex,picturey,mapx,mapy,xdraw,ydraw);
                    }

                    if ( ((posx-32)%64==0) && ( (posy)%72==0) )
                    {

                        if ((blokje&16)==16)
                        {
                            blokje=blokje & 15;
                            if (blokje==1 || blokje==2 || blokje==4 || blokje==8)
                            {
                                if (blokje==1)
                                {
                                    speedy=abs(speedy_new)+abs(speedx_new);
                                    speedx=0;
                                    fspeedy=+fabs(fspeedy_new)+fabs(fspeedx_new);
                                    fspeedx=0;
                                }
                                else if (blokje==2)
                                {
                                    speedy=-abs(speedy_new)-abs(speedx_new);
                                    speedx=0;
                                    fspeedy=-fabs(fspeedy_new)-fabs(fspeedx_new);
                                    fspeedx=0;
                                }
                                else if (blokje==4)
                                {
                                    speedx=abs(speedx_new)+abs(speedy_new);
                                    speedy=0;
                                    fspeedx=fabs(fspeedx_new)+fabs(fspeedy_new);
                                    fspeedy=0;
                                }
                                else if (blokje==8)
                                {
                                    speedx=-abs(speedx_new)-abs(speedy_new);
                                    speedy=0;
                                    fspeedx=-fabs(fspeedx_new)-fabs(fspeedy_new);
                                    fspeedy=0;
                                }
                                speedx_new=speedx;
                                speedy_new=speedy;
                                fspeedx_new=fspeedx;
                                fspeedy_new=fspeedy;
                                if (fspeedx>0)
                                {
                                    maze_left_new=1;
                                    maze_right_new=0;
                                    maze_up_new=0;
                                    maze_down_new=0;
                                }
                                if (fspeedx<0)
                                {
                                    maze_right_new=1;
                                    maze_left_new=0;
                                    maze_up_new=0;
                                    maze_down_new=0;
                                }
                                if (fspeedy>0)
                                {
                                    maze_up_new=1;
                                    maze_down_new=0;
                                    maze_left_new=0;
                                    maze_right_new=0;
                                }
                                if (fspeedy<0)
                                {
                                    maze_down_new=1;
                                    maze_up_new=0;
                                    maze_left_new=0;
                                    maze_right_new=0;
                                }
                            }
                        }
//!!!!!!!!!!!!!!!!
                        if ((maze_plot[mazemovex][mazemovey]&16)==16 && eatmode==0)
                        {
                            if (hunt==1||hunt==2)
                            {
                                hunt=1;
                                hunt_max=800-(difficulty-2)*150;
                                if (hunt_counter!=800-(difficulty-2)*150)
                                    hunt_counter=799-(difficulty-2)*150;
                            }
                            else
                            {
                                hunt=1;
                                hunt_max=800-(difficulty-2)*150;
                                hunt_counter=800-(difficulty-2)*150;
                            }
                            playsound=playsound|2;
                        }
                    }

//                    if (loaded==0 && breed!=0)
                    if (mazetype==1 && breed!=0)
                    {

//adaptmaze
                        if ((mazemovex==(hoog-1-59+maze_plotsizex)%maze_plotsizex) && ( mazemovey==(breed-1-30+maze_plotsizey)%maze_plotsizey )   )
//                        if ((mazemovex==hoog-1) && ( mazemovey==(breed-1) )   )
                        {
                            if (connected==1)
                            {
                                SEED=time(0);
                                sprintf(writer,"T=MAZE,BIGLARGE=%d,SEED=%d,LEVEL=%d,\0",big_large,SEED,level);
                                SEND(writer);
                            }
                            if (loaded==0)
                                next=1;
                            else
                                nextlevel=1;
                        }
                    }
                }
                else
                {
                    if (last_posx!=posx || last_posy!=posy)
                    {
                        if (fhapper>0.0)
                        {
                            fhapper=1.0;
                        }
                    }
                }

                last_posx=posx;
                last_posy=posy;
            }
        }



        static int ox=0,oy=0;
        ox=posx;
        oy=posy;
        if (pen==0)
        {
            if (numloops>1 && loops<(numloops-1))
            {
                if (fspeedx<0.0)
                {
                    posx=posx-1;
                    fpos_total--;
                }
                else if (fspeedx>0.0)
                {
                    posx=posx+1;
                    fpos_total--;
                }
                if (fspeedy<0.0)
                {
                    posy=posy-1;
                    fpos_total--;
                }
                else if (fspeedy>0.0)
                {
                    posy=posy+1;
                    fpos_total--;
                }
                if (fspeedx==0.0 && fspeedy==0.0)
                {
                    fpos_total=0.0;
                    remain=0.0;
                }
                if (fspeedx!=0.0)
                    lastmove='X';
                else if (fspeedy!=0.0)
                    lastmove='Y';
            }
            else
            {
                if (pacman==1)
                {
                    if (fspeedx==0.0)
                    {
                        fposx=posx;
                        if (fspeedy>0.0)
                        {
//                            fposy=(float)posy+remain;
                            fposy=posy+(fpos_total+remain);
                        }
                        else if (fspeedy<0.0)
                        {
//                            fposy=(float)posy-remain;
                            fposy=posy-(fpos_total-remain);
                        }
                        else
                            fposy=posy;
                    }
                    else if (fspeedy==0)
                    {
                        fposy=posy;
                        if (fspeedx>0.0)
                        {
//                            fposx=(float)posx+remain;
                            fposx=posx+(fpos_total+remain);
                        }
                        else if (fspeedx<0.0)
                        {
//                            fposx=(float)posx-remain;
                            fposx=posx-(fpos_total-remain);
                        }
                        else
                            fposx=posx;
                    }
                    posx=fposx;
                    posy=fposy;
                }
                else
                {
                    fposx=fposx+fspeedx*fspeed_adjust;
                    fposy=fposy+fspeedy*fspeed_adjust;
                    posx=fposx;
                    posy=fposy;
                }
                if (fspeedx!=0.0)
                    lastmove='X';
                else if (fspeedy!=0.0)
                    lastmove='Y';
            }
        }

        if (pen==1)
        {
            pen_speedx=0;
            pen_speedy=0;
            speedx=0;
            speedy=0;
            fpen_speedx=0;
            fpen_speedy=0;
            fspeedx=0;
            fspeedy=0;
        }

//jojojo
        if (pen!=1) {
//pospos
            if (posx<-1920)
//            if (posx<=-1920)
            {
                posx=posx+1920;
                fposx=fposx+1920;
                picturex++;
                if (picturex>maxpicturex) picturex=0;
                if (posx<-1920)
                {
                    posx=posx+1920;
                    fposx=fposx+1920;
                    picturex++;
                    if (picturex>maxpicturex) picturex=0;
                }

                ReadBitmaps2();
            }
            else if (posx>=0)
            {
                posx=posx-1920;
                fposx=fposx-1920;
                picturex--;
                if (picturex<0) picturex=maxpicturex;
                if (posx>=0)
                {
                    posx=posx-1920;
                    fposx=fposx-1920;
                    picturex--;
                    if (picturex<0) picturex=maxpicturex;
                }
                ReadBitmaps2();
            }
            if (posy<-1080)
//            if (posy<=-1080)
            {
                posy=posy+1080;
                fposy=fposy+1080;
                picturey++;
                if (picturey>maxpicturey) picturey=0;
                if (posy<-1080)
                {
                    posy=posy+1080;
                    fposy=fposy+1080;
                    picturey++;
                    if (picturey>maxpicturey) picturey=0;
                }
                ReadBitmaps2();
            }
            else if (posy>=0)
            {
                posy=posy-1080;
                fposy=fposy-1080;
                picturey--;
                if (picturey<0) picturey=maxpicturey;
                if (posy>=0)
                {
                    posy=posy-1080;
                    fposy=fposy-1080;
                    picturey--;
                    if (picturey<0) picturey=maxpicturey;
                }
                ReadBitmaps2();
            }
        } else {
            if (posx<-1920)
            {
                posx=posx+1920;
                fposx=fposx+1920;
                picturex++;
                if (picturex>maxpicturex)
                    picturex=0;
                if (posx<-1920)
                {
                    posx=posx+1920;
                    fposx=fposx+1920;
                    picturex++;
                    if (picturex>maxpicturex)
                        picturex=0;
                }
                ReadBitmaps2();
            }
            else if (posx>=0)
            {
                posx=posx-1920;
                fposx=fposx-1920;
                picturex--;
                if (picturex<0)
                    picturex=maxpicturex;
                if (posx>=0)
                {
                    posx=posx-1920;
                    fposx=fposx-1920;
                    picturex--;
                    if (picturex<0)
                        picturex=maxpicturex;
                }
                ReadBitmaps2();
            }
            if (posy<-1080)
            {
                posy=posy+1080;
                fposy=fposy+1080;
                picturey++;
                if (picturey>maxpicturey) picturey=0;
                if (posy<-1080)
                {
                    posy=posy+1080;
                    fposy=fposy+1080;
                    picturey++;
                    if (picturey>maxpicturey) picturey=0;
                }
                ReadBitmaps2();
            }
            else if (posy>=0)
            {
                posy=posy-1080;
                fposy=fposy-1080;
                picturey--;
                if (picturey<0) picturey=maxpicturey;
                if (posy>=0)
                {
                    posy=posy-1080;
                    fposy=fposy-1080;
                    picturey--;
                    if (picturey<0) picturey=maxpicturey;
                }
                ReadBitmaps2();
            }
        }
    }
    /*
        if (flippo==1) {
            posx=remem_posx;
            posy=remem_posy;
            fposx=remem_fposx;
            fposy=remem_fposy;
            picturex=remem_picturex;
            picturey=remem_picturey;
        }
    */

//hopla
//    if ( (pen==1 && pencontrol==1) && goexit==0)
    if ( (pen==1 && pencontrol==1) && follow_ghost==0 && goexit==0)
    {
//pospos
        posx=posx-posx%64-32;
        if (posx<-1920)
//        if (posx<=-1920)
        {
            posx=posx+1920;
            picturex=(picturex+1+totalpicturex)%totalpicturex;
        }
        posy=posy-(posy-36)%72-36;
        if (posy<-1080)
//        if (posy<=-1080)
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
                posy=posy-(posy-36)%72-36   ;
                if (posy<=-1080)
                    posy=posy+1080;
        */

        mazemovex=(picturex*1920-posx-32)/64;
        mazemovey=(picturey*1080-posy   )/72;
        mazemovex=(mazemovex-45+60*(maxpicturex+1))%(30*(maxpicturex+1));
        mazemovey=(mazemovey-23+30*(maxpicturey+1))%(15*(maxpicturey+1));

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

        int blokje=maze_plot[mazemovex][mazemovey];

        if (pen_mode==0)
        {
            if (pen_maze_up==1)
            {
                maze_up=0;
                pen_maze_up=0;
                maze_plot[mazemovex][mazemovey]=maze_plot[mazemovex][mazemovey] | 2;
                do_mirror(mazemovex,mazemovey,2);
            }
            else if (pen_maze_down==1)
            {
                pen_maze_down=0;
                maze_down=0;
                maze_plot[mazemovex][mazemovey]=maze_plot[mazemovex][mazemovey] | 1;
                do_mirror(mazemovex,mazemovey,1);
            }
            else if (pen_maze_left==1)
            {
                pen_maze_left=0;
                maze_left=0;
                maze_plot[mazemovex][mazemovey]=maze_plot[mazemovex][mazemovey] | 8;
                do_mirror(mazemovex,mazemovey,8);
            }
            else if (pen_maze_right==1)
            {
                pen_maze_right=0;
                maze_right=0;
                maze_plot[mazemovex][mazemovey]=maze_plot[mazemovex][mazemovey] | 4;
                do_mirror(mazemovex,mazemovey,4);
            }
            else
            {
//                do_mirror(mazemovex,mazemovey,0);
            }
        }
        else if (pen_mode==1)
        {
            if (pen_maze_up==1)
            {
                pen_maze_up=0;
                maze_up=0;
                maze_plot[mazemovex][mazemovey]=maze_plot[mazemovex][mazemovey] & (15-2);
                do_mirror(mazemovex,mazemovey,2);
            }
            else if (pen_maze_down==1)
            {
                maze_down=0;
                pen_maze_down=0;
                maze_plot[mazemovex][mazemovey]=maze_plot[mazemovex][mazemovey] & (15-1);
                do_mirror(mazemovex,mazemovey,1);
            }
            else if (pen_maze_left==1)
            {
                maze_left=0;
                pen_maze_left=0;
                maze_plot[mazemovex][mazemovey]=maze_plot[mazemovex][mazemovey] & (15-8);
                do_mirror(mazemovex,mazemovey,8);
            }
            else if (pen_maze_right==1)
            {
                maze_right=0;
                pen_maze_right=0;

                maze_plot[mazemovex][mazemovey]=maze_plot[mazemovex][mazemovey] & (15-4);
                do_mirror(mazemovex,mazemovey,4);
            }
            else
            {
            }
        }
        else
        {
            maze_right=0;
            maze_left=0;
            maze_down=0;
            maze_up=0;
            pen_maze_right=0;
            pen_maze_left=0;
            pen_maze_down=0;
            pen_maze_up=0;
        }
        if (blokje!=maze_plot[mazemovex][mazemovey])
            levelnotsaved=1;

        if (connected==1)
        {
            if (blokje!=maze_plot[mazemovex][mazemovey])
            {
                sprintf(writer,"T=PLOT,X=%d,Y=%d,M=%d,PEN_MODE=%d,\0",mazemovex,mazemovey,maze_plot[mazemovex][mazemovey],pen_mode);
                SEND(writer);
            }
            else
            {
                static int old_movex;
                static int old_movey;
                if (mazemovex!=old_movex || mazemovey!=old_movey)
                {
                    sprintf(writer,"T=GOTO,X=%d,Y=%d,\0",mazemovex,mazemovey);
                    SEND(writer);
                    old_movex=mazemovex;
                    old_movey=mazemovey;
                }
            }
        }

    }

//testing
//    printf("sx=%f,sy=%f   ",fspeedx,fspeedy);
//    if (follow_ghost==0 && (fabs(fspeedx)>20.0 || fabs(fspeedy)>20.0)) soft_jump=1;
    if (follow_ghost==1)
    {
        if (follow_ghost_num>=number)
            follow_ghost_num=number-1;
        if (follow_ghost_num<0)
        {
            follow_ghost=0;
            follow_ghost_num=0;
            long_jump=1;
//    printf("3\n");
        }
        else
        {
            follow_ghost_pos();
        }
    }
    else
    {
        follow_ghost_pos();
    }

//    if (follow_ghost==0)
//    {
//        follow_ghost_pos();
//    }

//plotting

    extern int one_pixel;
    extern void goto_maze(int mazemovex, int mazemovey);

//    if (autodraw==1 && pen==1 && drawmazes==1 && follow_ghost==0 ) {
    static bool autofirst=true;
    if (autodraw==1 && pen==1 && follow_ghost==0 )
    {
        mazemovex=(picturex*1920-posx-32)/64;
        mazemovey=(picturey*1080-posy   )/72;
        mazemovex=(mazemovex-45+60*(maxpicturex+1))%(30*(maxpicturex+1));
        mazemovey=(mazemovey-23+30*(maxpicturey+1))%(15*(maxpicturey+1));

        static int turn=0;
        if (rand()%400==0)
            turn=0;
        if (rand()%400==0)
            turn=1;
        turn=2;
        if (turn==0)
        {
            char blokje=maze_plot[(mazemovex+maze_plotsizex)%maze_plotsizex][(mazemovey+maze_plotsizey)%maze_plotsizey];

            static char lucky[20]= {'j','k','l','i'};
            static int n=0;
            static int hoppa=100;
            if (rand()%40==0)
                hoppa=rand()%200;
            if (rand()%hoppa==0 || rand()%50==0)
                n=rand()%4;
            insert_key((WPARAM)lucky[n]);
            static int pm=0;
            if ((rand()%50)==0)
                pm=rand()%2;
            if (pm==1)
            {
                pen_mode=1;
                combine=1;
            }
            else
            {
                pen_mode=0;
                combine=0;
            }
            int ok=1;
        }
        /*
                char surround[5][5];
                for (int x=-2; x<=2;x++)
                    for (int y=-2; y<=2;y++) {
                        surround[x+2][y+2]=maze_plot[(x+mazemovex+maze_plotsizex)%maze_plotsizex][(y+mazemovey+maze_plotsizey)%maze_plotsizey];
                    }
                char lucky[20]={'j','k','l','i'};

                int i=0;
                if (surround[2-1][2-1]==0 && surround[2+1][2-1]==0 && surround[2  ][2-1]==0) { lucky[i]='i'; i++;}
                if (surround[2-1][2+1]==0 && surround[2+1][2+1]==0 && surround[2  ][2+1]==0) { lucky[i]='k'; i++;}
                if (surround[2+1][2-1]==0 && surround[2+1][2+1]==0 && surround[2+1][2  ]==0) { lucky[i]='l'; i++;}
                if (surround[2-1][2+1]==0 && surround[2-1][2-1]==0 && surround[2-1][2  ]==0) { lucky[i]='j'; i++;}
        //        if (i>0) { pen_mode=0; insert_key((WPARAM)lucky[rand()%i]); }
        //        else {
          //          if (surround[2-1][2]>0) { lucky[i]='j'; i++;}
        //            if (surround[2+1][2]>0) { lucky[i]='l'; i++;}
        //            if (surround[2][2-1]>0) { lucky[i]='i'; i++;}
        //            if (surround[2][2+1]>0) { lucky[i]='k'; i++;}
        //            if (i>0) { pen_mode=0; insert_key((WPARAM)lucky[rand()%i]); }
        //            else {
                        if (surround[2][2]&1==1) { lucky[i]='i'; i++;}
                        if (surround[2][2]&2==2) { lucky[i]='k'; i++;}
                        if (surround[2][2]&4==4) { lucky[i]='j'; i++;}
                        if (surround[2][2]&8==8) { lucky[i]='l'; i++;}
                        if (i>0) { pen_mode=0; insert_key((WPARAM)lucky[rand()%i]); }
                        else {
                            pen_mode=2;
                            insert_key((WPARAM)lucky[rand()%4]);
                        }
        //            }
        //        }
                if (rand()%5==1) crossing=rand()%2;
                if (rand()%5==1) mirror=rand()%6;
        //        if (rand()%8==1) {
        //            pen_mode=2;
        //            char lucky[]={'j','k','l','i'};
        //            insert_key((WPARAM)lucky[rand()%5]);
        //        }

        */

        if (turn>=1)
        {
            static int n=0;
            char blokje=maze_plot[(mazemovex+maze_plotsizex)%maze_plotsizex][(mazemovey+maze_plotsizey)%maze_plotsizey];
            /*
                        if ((blokje&15)==15) {
                            turn=0;
                            for (int t=0; t<1000; t++) {
                                int x=(rand()*rand())%maze_plotsizex;
                                int y=(rand()*rand())%maze_plotsizey;
                                if ((maze_plot[x][y]&15)<15) {
                                    goto_maze(x,y);
            //                        forced_jump=1;
                                    mazemovex=x;mazemovey=y;
                                    turn=1;
                                    break;
                                }
                            }
                        }
            */
            if (turn==1)
            {

                char surround[7][7];
                for (int x=-3; x<=3; x++)
                    for (int y=-3; y<=3; y++)
                    {
                        surround[x+3][y+3]=maze_plot[(x+mazemovex+maze_plotsizex)%maze_plotsizex][(y+mazemovey+maze_plotsizey)%maze_plotsizey];
                    }

                int n_old=n;
                if (rand()%30==0 || rand()%40==0)
                    n=rand()%4;
                int ok=0;

                if (n==0 &&    ((surround[3+1][3])==0 || ( (surround[3+1][3])==3 && ( (surround[3+2][3])==0 || (surround[3+3][3])==0 ) ) ))
                {
                    insert_key((WPARAM)'l');
                    ok=1;
                }
                if (n==1 &&   ((surround[3-1][3])==0 || ( (surround[3-1][3])==3 &&  ( (surround[3-2][3])==0 || (surround[3-3][3])==0 )  ) ))
                {
                    insert_key((WPARAM)'j');
                    ok=1;
                }
                if (n==2 &&    ((surround[3][3+1])==0 || ( (surround[3][3+1])==12 && ( (surround[3][3+2])==0 || (surround[3][3+3])==0 ) ) ))
                {
                    insert_key((WPARAM)'k');
                    ok=1;
                }
                if (n==3 &&    ((surround[3][3-1])==0 || ( (surround[3][3-1])==12 && ( (surround[3][3-2])==0 || (surround[3][3-3])==0 ) ) ))
                {
                    insert_key((WPARAM)'i');
                    ok=1;
                }
                if (ok==0)
                {
                    n=n+1;
                    n=n%4;
                    if (n==0 &&    ((surround[3+1][3])==0 || ( (surround[3+1][3])==3 && ( (surround[3+2][3])==0 || (surround[3+3][3])==0 ) ) ))
                    {
                        insert_key((WPARAM)'l');
                        ok=1;
                    }
                    if (n==1 &&   ((surround[3-1][3])==0 || ( (surround[3-1][3])==3 &&  ( (surround[3-2][3])==0 || (surround[3-3][3])==0 )  ) ))
                    {
                        insert_key((WPARAM)'j');
                        ok=1;
                    }
                    if (n==2 &&    ((surround[3][3+1])==0 || ( (surround[3][3+1])==12 && ( (surround[3][3+2])==0 || (surround[3][3+3])==0 ) ) ))
                    {
                        insert_key((WPARAM)'k');
                        ok=1;
                    }
                    if (n==3 &&    ((surround[3][3-1])==0 || ( (surround[3][3-1])==12 && ( (surround[3][3-2])==0 || (surround[3][3-3])==0 ) ) ))
                    {
                        insert_key((WPARAM)'i');
                        ok=1;
                    }
                    if (ok==0)
                    {
                        n=n+1;
                        n=n%4;
                        if (n==0 &&    ((surround[3+1][3])==0 || ( (surround[3+1][3])==3 && ( (surround[3+2][3])==0 || (surround[3+3][3])==0 ) ) ))
                        {
                            insert_key((WPARAM)'l');
                            ok=1;
                        }
                        if (n==1 &&   ((surround[3-1][3])==0 || ( (surround[3-1][3])==3 &&  ( (surround[3-2][3])==0 || (surround[3-3][3])==0 )  ) ))
                        {
                            insert_key((WPARAM)'j');
                            ok=1;
                        }
                        if (n==2 &&    ((surround[3][3+1])==0 || ( (surround[3][3+1])==12 && ( (surround[3][3+2])==0 || (surround[3][3+3])==0 ) ) ))
                        {
                            insert_key((WPARAM)'k');
                            ok=1;
                        }
                        if (n==3 &&    ((surround[3][3-1])==0 || ( (surround[3][3-1])==12 && ( (surround[3][3-2])==0 || (surround[3][3-3])==0 ) ) ))
                        {
                            insert_key((WPARAM)'i');
                            ok=1;
                        }
                        if (ok==0)
                        {
                            n=n+1;
                            n=n%4;
                            if (n==0 &&    ((surround[3+1][3])==0 || ( (surround[3+1][3])==3 && ( (surround[3+2][3])==0 || (surround[3+3][3])==0 ) ) ))
                            {
                                insert_key((WPARAM)'l');
                                ok=1;
                            }
                            if (n==1 &&   ((surround[3-1][3])==0 || ( (surround[3-1][3])==3 &&  ( (surround[3-2][3])==0 || (surround[3-3][3])==0 )  ) ))
                            {
                                insert_key((WPARAM)'j');
                                ok=1;
                            }
                            if (n==2 &&    ((surround[3][3+1])==0 || ( (surround[3][3+1])==12 && ( (surround[3][3+2])==0 || (surround[3][3+3])==0 ) ) ))
                            {
                                insert_key((WPARAM)'k');
                                ok=1;
                            }
                            if (n==3 &&    ((surround[3][3-1])==0 || ( (surround[3][3-1])==12 && ( (surround[3][3-2])==0 || (surround[3][3-3])==0 ) ) ))
                            {
                                insert_key((WPARAM)'i');
                                ok=1;
                            }
                        }
                    }
                }
                if (rand()%5==1)
                    crossing=rand()%2+1;
                pen_mode=0;

                static int nep_count=6000;
//                nep_count--;
//                if (ok==0) turn=0;
//                else
                if ( (nep_count<=0 && !( (blokje&12)==12 || (blokje&3)==3  )  ) || ok==0 )
                {
                    nep_count=6000;
//                        turn=0;
                    for (int t=0; t<20000; t++)
                    {
                        int x=(rand()*rand())%maze_plotsizex;
                        int y=(rand()*rand())%maze_plotsizey;
                        if ((maze_plot[x][y]&15)>0)
                        {
                            //                            forced_jump=1;
                            goto_maze(x,y);
                            turn=1;
                            break;
                        }
                    }
                }
            } else if (turn==2) {
                static int nn=0;
                static int rot4[4]={0,2,1,3};
                if (autofirst) {
                    nn=0;
                }
                char surround[7][7];
                for (int x=-3; x<=3; x++)
                    for (int y=-3; y<=3; y++)
                    {
                        surround[x+3][y+3]=maze_plot[(x*40+mazemovex+maze_plotsizex)%maze_plotsizex][(y*11+mazemovey+maze_plotsizey)%maze_plotsizey];
                    }

//                if (nn==0 && mazemovex>=maze_plotsizex-1) nn=1;
//                else if (nn==1 && mazemovey>=maze_plotsizey-1) nn=2;
//                else if (nn==2 && mazemovex==0) nn=3;
//                else if (nn==3 && mazemovey==0) nn=0;

                int n_old=n;
                n=rot4[nn];
//                if (rand()%30==0 || rand()%40==0)
//                    n=rand()%4;
                int ok=0;

                if (n==0 &&    ((surround[3+1][3])==0) )
                {
                    insert_key((WPARAM)'l');
                    ok=1;
                }
                if (n==1 &&   ((surround[3-1][3])==0) )
                {
                    insert_key((WPARAM)'j');
                    ok=1;
                }
                if (n==2 &&    ((surround[3][3+1])==0) )
                {
                    insert_key((WPARAM)'k');
                    ok=1;
                }
                if (n==3 &&    ((surround[3][3-1])==0) )
                {
                    insert_key((WPARAM)'i');
                    ok=1;
                }
                if (ok==0)
                {
                    nn=nn+1;
                    nn=nn%4;
                    n=rot4[nn];
                    if (n==0 &&    ((surround[3+1][3])==0) )
                    {
                        insert_key((WPARAM)'l');
                        ok=1;
                    }
                    if (n==1 &&   ((surround[3-1][3])==0) )
                    {
                        insert_key((WPARAM)'j');
                        ok=1;
                    }
                    if (n==2 &&    ((surround[3][3+1])==0) )
                    {
                        insert_key((WPARAM)'k');
                        ok=1;
                    }
                    if (n==3 &&    ((surround[3][3-1])==0) )
                    {
                        insert_key((WPARAM)'i');
                        ok=1;
                    }
                    if (ok==0)
                    {
                        nn=nn+1;
                        nn=nn%4;
                        n=rot4[nn];
                        if (n==0 &&    ((surround[3+1][3])==0) )
                        {
                            insert_key((WPARAM)'l');
                            ok=1;
                        }
                        if (n==1 &&   ((surround[3-1][3])==0) )
                        {
                            insert_key((WPARAM)'j');
                            ok=1;
                        }
                        if (n==2 &&    ((surround[3][3+1])==0) )
                        {
                            insert_key((WPARAM)'k');
                            ok=1;
                        }
                        if (n==3 &&    ((surround[3][3-1])==0) )
                        {
                            insert_key((WPARAM)'i');
                            ok=1;
                        }
                        if (ok==0)
                        {
                            nn=nn+1;
                            nn=nn%4;
                            n=rot4[nn];
                            if (n==0 &&    ((surround[3+1][3])==0) )
                            {
                                insert_key((WPARAM)'l');
                                ok=1;
                            }
                            if (n==1 &&   ((surround[3-1][3])==0) )
                            {
                                insert_key((WPARAM)'j');
                                ok=1;
                            }
                            if (n==2 &&    ((surround[3][3+1])==0) )
                            {
                                insert_key((WPARAM)'k');
                                ok=1;
                            }
                            if (n==3 &&    ((surround[3][3-1])==0) )
                            {
                                insert_key((WPARAM)'i');
                                ok=1;
                            }
                        }
                    }
                }
                if (rand()%5==1)
                    crossing=rand()%2+1;
                pen_mode=0;

                static int nep_count=6000;
                if ( (nep_count<=0 && !( (blokje&12)==12 || (blokje&3)==3  )  ) || ok==0 )
                {
                    autodraw=0;
                }
            } //end turn2
        }
        DONTSAVEFILES=1;
        autofirst=false;
    } else {
        autofirst=true;
    }

    if (one_pixel==1)
    {
        speedy=0;
        fspeedy=0.0;
        speedx=0;
        fspeedx=0.0;
        one_pixel=0;
    }

    static float old_old_scale=0.0;
    static float old_scale=0.0;
    static int first_click=1;
    static int first_click2=0;
//mafkees
//    if  (( ffmpegfile==0 || movie==0 && !sf::Mouse::isButtonPressed(sf::Mouse::Right)) )
    static int first_plot=1;
    move_slow=0;
    if  (1)
//    if  (!sf::Mouse::isButtonPressed(sf::Mouse::Right) )
    {
        static int counter=1;
        static float run_time_old=run_time+PI*2;
//        counter--;

        float rescale_x; // is max 2.0
        float rescale_y; // is max 2.0
        static int plot_counter=5;
        static int load=1;

        if ((first_plot==1 && follow_ghost==1))
        {
//            load_next_ffmpeg();
            first_plot=0;
            run_time_old=run_time;
            load=10;
            if (internetfile==0 && handler[INTERNET_SELECT].show==1) {
                load_next_internet();
                scale_now=sprite_from_internet.getScale().x;
            }
            if (ffmpegfile==0 && handler[FFMPEG_SELECT].show==1)
                scale_now=sprite_from_ffmpeg.getScale().x;
            if (movie==0 && handler[MOVIE_SELECT].show==1)
                scale_now=sprite_from_movie.getScale().x;
            if (movie2==0 && handler[MOVIE2_SELECT].show==1)
                scale_now=sprite_from_movie2.getScale().x;

            old_internet_scale==scale_now;
        }
        else
        {
            if (follow_ghost==0)
                first_plot=1;
        }

        int fix=0;
          fix=0;
        load--;

//        if (shade_main) no_scale=1;
//        else no_scale=0;

        if (follow_ghost==1 && (ffmpegfile==0 || internetfile==0 || movie==0))
        {
//            rescale_x=1.0-cos( 2.0*3.1416 * (float)(-render_posx+render_picturex*1920+(1920/2))/(float)maxpixelsx   ); // is max 2.0
//            rescale_y=1.0-cos( 2.0*3.1416 * (float)(-render_posy+render_picturey*1080+(1080/2))/(float)maxpixelsy   ); // is max 2.0
//            new_scale=0.5*scale_now * (1.0+rescale_x*rescale_y/(2.0) );  // scale * 1 on edge to 3 times as much in middle of screen. (1 +  max 4/2)
            static float run_time_old=run_time+PI/2;
// on largest
//on smallest

            if (load<0)
                if (sin(run_time_old*fspeed+PI/2.0+PI) > 0.0 && sin(run_time*fspeed+PI/2.0+PI) < 0.0  )
                    fix=1;
            if (load<0)
                if (sin(run_time_old*fspeed+PI/2.0) > 0.0 && sin(run_time*fspeed+PI/2.0) < 0.0  )
                    plot_counter=0;
            if (load<0)
                if (sin(run_time_old*fspeed+PI/2.0) > 0.0 && sin(run_time*fspeed+PI/2.0) < 0.0  )
                    fix=2;
            run_time_old=run_time;
//            old_old_scale=old_scale;
//            old_scale=new_scale;
//mafkees2
//            new_scale=0.6*scale_now * (1.0+sin(run_time*fspeed)/2.0) * scale_now_adj;

            new_scale=scale_now;
//babe
            fix=0;
//            plot_counter=0;
            static int big=0;
//            if (new_scale>old_scale && big==1) {
//                big=0;
//                plot_counter=0;
//            }
//            else if (new_scale<old_scale && big==0) {
//                big=1;
//            }

//            new_scale=scale_now * (1.0 + (float)(rand()%150)/100.0 + (float)(rand()%150)/100.0 );




                        if (ffmpegfile==0 && handler[FFMPEG_SELECT].show==1) {
                            sprite_from_ffmpeg.setScale(new_scale,new_scale);
                            ffmpeg_move=0;
                            size_ffmpeg=0;
                            move_slow=1;
                            if (shade_map>=1 || shade_main) {
                                flowx=sin(fpstime+follow_ghost_num+sin(fpstime*1.2+follow_ghost_num))*50  + sin(fpstime*1.4+follow_ghost_num+sin(fpstime*1.5+follow_ghost_num))*10;
                                flowy=cos(fpstime*1.1+follow_ghost_num+sin(fpstime*1.3+follow_ghost_num))*50 + sin(fpstime*0.9+follow_ghost_num+sin(fpstime*1.3+follow_ghost_num))*10;
                            } else {
                                flowx=0;
                                flowy=0;
                            }
                            ffmpeg_posx=flowx+1920-pos_ghostx[follow_ghost_num]+(1920/2-(int)(texture_from_ffmpeg.getSize().x)/2);
                            ffmpeg_posy=flowy+1080-pos_ghosty[follow_ghost_num]+(1080/2-(int)(texture_from_ffmpeg.getSize().y)/2);
                        }



                        if (internetfile==0 && handler[INTERNET_SELECT].show==1) {
                            sprite_from_internet.setScale(new_scale,new_scale);
                            internet_move=0;
                            size_internet=0;
                            if (shade_map>=1) {
                                flowx=sin(fpstime+follow_ghost_num+sin(fpstime*1.2+follow_ghost_num))*50  + sin(fpstime*1.4+follow_ghost_num+sin(fpstime*1.5+follow_ghost_num))*10;
                                flowy=cos(fpstime*1.1+follow_ghost_num+sin(fpstime*1.3+follow_ghost_num))*50 + sin(fpstime*0.9+follow_ghost_num+sin(fpstime*1.3+follow_ghost_num))*10;
                            } else {
                                flowx=0;
                                flowy=0;
                            }
                            internet_posx=flowx+1920-pos_ghostx[follow_ghost_num]+(1920/2-(int)texture_from_internet.getSize().x/2);
                            internet_posy=flowy+1080-pos_ghosty[follow_ghost_num]+(1080/2-(int)texture_from_internet.getSize().y/2);

                        }


            if (movie==0 && handler[MOVIE_SELECT].show==1)
            {
                sprite_from_movie.setScale(new_scale,new_scale);
                movie_move=0;
                size_movie=0;
                if (shade_map>=1)
                {
                    flowx=sin(fpstime+follow_ghost_num+sin(fpstime*1.2+follow_ghost_num))*50  + sin(fpstime*1.4+follow_ghost_num+sin(fpstime*1.5+follow_ghost_num))*10;
                    flowy=cos(fpstime*1.1+follow_ghost_num+sin(fpstime*1.3+follow_ghost_num))*50 + sin(fpstime*0.9+follow_ghost_num+sin(fpstime*1.3+follow_ghost_num))*10;
                }
                else
                {
                    flowx=0;
                    flowy=0;
                }
                if (blend_on_movie>=0 && ffmpegfile==0)
                {
                    movie_posx=flowx+1920-pos_ghostx[follow_ghost_num]+(1920/2-(int)texture_from_movie_new.getSize().x/2);
                    movie_posy=flowy+1080-pos_ghosty[follow_ghost_num]+(1080/2-(int)texture_from_movie_new.getSize().y/2);
                }
                else
                {
                    movie_posx=flowx+1920-pos_ghostx[follow_ghost_num]+(1920/2-(int)texture_from_movie_new.getSize().x/2);
                    movie_posy=flowy+1080-pos_ghosty[follow_ghost_num]+(1080/2-(int)texture_from_movie_new.getSize().y/2);
                }

            }
            static int saver=5000;
//            saver--;
//            if (saver<=0) {
//                DONTSAVEFILES=0;
//                SAVEALLBITMAPS();
//                saver=5000;
//            }
        }

        if ( (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mouse_move==1) || (follow_ghost==1 && (counter==0 || plot_counter==0 || fix>0)))
        {
            static int counter2=0;
            if (first_click==0)
            {
//babe
                if (mouse_move==1)
                    sf::Mouse::setPosition(sf::Vector2i(960,540));
                position = sf::Vector2i(960,540);
//                position=sf::Mouse::getPosition();
                first_click=1;
                if (ffmpegfile==0 && blend_on_movie==0)
                    plot_ffmpegfile=1;
                if (internetfile==0)
                    plot_internetfile=1;
                if (movie==0 && timer_movie==0 && !live_movie->getStatus()==sfe::Stopped)
                    plot_moviefile=1;
                perform_quit=1;
//                plotplot();
                plot_some();
                perform_quit=0;
                printf("oh oh\n");
            }
            sf::Vector2i position2=sf::Vector2i(960,540);
            if (mouse_move==1)
            {
                position2=sf::Mouse::getPosition();
            }
//            plot_counter--;
            if (position2.x!=960 || position2.y!=540 || (follow_ghost==1 && (counter==0 || plot_counter==0 || fix>0)))
            {
                if (mouse_move==1)
                {
                    posx=posx+(position.x-position2.x);
                    posy=posy+(position.y-position2.y);
//pospos
//                    if (posx<=-1920)
                    if (posx<-1920)
                    {
                        posx=posx+1920;
                        fposx=fposx+1920;
                        picturex++;
                        if (picturex>maxpicturex)
                            picturex=0;
                        ReadBitmaps2();
                    }
                    else if (posx>=0)
//                    else if (posx>0)
                    {
                        posx=posx-1920;
                        fposx=fposx-1920;
                        picturex--;
                        if (picturex<0)
                            picturex=maxpicturex;
                        ReadBitmaps2();
                    }
                    if (posy<-1080)
//                    if (posy<=-1080)
                    {
                        posy=posy+1080;
                        fposy=fposy+1080;
                        picturey++;
                        if (picturey>maxpicturey)
                            picturey=0;
                        ReadBitmaps2();
                    }
                    else if (posy>=0)
//                    else if (posy>0)
                    {
                        posy=posy-1080;
                        fposy=fposy-1080;
                        picturey--;
                        if (picturey<0)
                            picturey=maxpicturey;
                        ReadBitmaps2();
                    }
                }
//babe
//                sf::Mouse::setPosition(sf::Vector2i(960,540));
//                position = sf::Vector2i(960,540);

                if (mouse_move==1)
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    {
                        position=position2;
                        forced_speed=1;
                        follow_ghost_pos();

                        forced_speed=0;
                        if (ffmpegfile==0 && blend_on_movie==0)
                        {
                            perform_quit=1;
                            plot_ffmpegfile=1;
                            plot_some();
                            perform_quit=0;
                        }

                        if (internetfile==0)
                        {
                            perform_quit=1;
                            plot_internetfile=1;
                            plot_some();
                            perform_quit=0;
                        }

                        if (blend_on_movie>=1 && ffmpegfile==0 && movie==0 && handler[MOVIE_SELECT].show==1)
                        {
                            sprite_from_ffmpeg.setTexture(tussen_texture.getTexture(),false);
                            sprite_from_ffmpeg.setRotation(sprite_from_movie.getRotation());
                            perform_quit=1;
                            plot_moviefile=1;
                            plot_some();
                            perform_quit=0;
                            sprite_from_ffmpeg.setTexture(texture_from_ffmpeg,false);
                        }
                        else if (movie==0 && handler[MOVIE_SELECT].show==1)
                        {
                            perform_quit=1;
                            plot_moviefile=1;
                            plot_some();
                            perform_quit=0;
                        }


                    }
//babe
                if (mouse_move==1)
                    sf::Mouse::setPosition(sf::Vector2i(960,540));
                position = sf::Vector2i(960,540);
                if (movie==0 && timer_movie==0 && !live_movie->getStatus()==sfe::Stopped)
                    plot_moviefile=1;

//babe
                if (fix==1)
                {
//                if (plot_counter==0 && load<=0) {
                    counter--;
                    perform_quit=1;



                                            if (internetfile==0 && handler[INTERNET_SELECT].show==1) {
                                                float size=(float)( 1.0+(rand()%200)/100.0);
//                                                float size=(float)((rand()%400)/100.0);
                                                sprite_from_internet.setScale(new_scale*size,new_scale*size);
//                                                sprite_from_internet.setScale(scale_now*size,scale_now*size);
                                                plot_internetfile=1;
                                                int hold=handler[INTERNET_SELECT].plot_front;
                                                handler[INTERNET_SELECT].plot_front=1;
                                                plot_some();
                                                handler[INTERNET_SELECT].plot_front=hold;
                                                sprite_from_internet.setScale(new_scale,new_scale);
                                            }




                                            if (ffmpegfile==0 && blend_on_movie==0 && handler[FFMPEG_SELECT].show==1) {
                                                float size=1.0;
//                                                float size=(float)( 1.0+(rand()%200)/100.0);
//                                                    float size=(float)((rand()%400)/100.0);
                                                    int hold=handler[FFMPEG_SELECT].plot_front;
                                                    int hold_blend=handler[FFMPEG_SELECT].blending;
//                                                    handler[FFMPEG_SELECT].plot_front=1;
                                                    handler[FFMPEG_SELECT].blending=0;
//                                                    sprite_from_ffmpeg.setScale(scale_now*size,scale_now*size);
                                                    sprite_from_ffmpeg.setScale(new_scale*size,new_scale*size);
                                                    plot_ffmpegfile=1; plot_some(); plot_counter=300;
                    //                                sprite_from_ffmpeg.setScale(scale_now,scale_now);
                                                    sprite_from_ffmpeg.setScale(new_scale,new_scale);
                                                    handler[FFMPEG_SELECT].plot_front=hold;
                                                    handler[FFMPEG_SELECT].blending=hold_blend;

                                            }



                                            if (movie==0 && blend_on_movie>=1 && handler[MOVIE_SELECT].show==1) {
                                                sprite_from_ffmpeg.setTexture(tussen_texture.getTexture(),false);

                                                float size=(float)(0.5);
//                                                float size=(float)((rand()%100)/10.0);
                                                sprite_from_ffmpeg.setScale(new_scale*size,new_scale*size);

                                                plot_moviefile=1;
                                                plot_some();
                                                sprite_from_ffmpeg.setTexture(texture_from_ffmpeg,false);
                                                sprite_from_ffmpeg.setScale(new_scale,new_scale);
                                                plot_counter=600;
                                            } else if (movie==0 && handler[MOVIE_SELECT].show==1) {
                                                plot_moviefile=1;
                                                plot_some();
                                                plot_counter=600;
                                            }
                                            perform_quit=0;

                }
//                if (plot_counter<=0) plot_counter=300;

//                plot_counter--;
//                if (movie==0 && timer_movie==0) if (live_movie->getStatus()==sfe::Playing && !(texture_from_movie_new.getSize().x==0) ) live_movie->pause();
//                if (movie==0 && timer_movie==0) if (texture_from_movie_new.getSize().x==0) live_movie->play();
                if (follow_ghost==1 && (counter<=0 || plot_counter==0 || fix>0) )
                {
//                    if (rand()%10==0) insert_key((WPARAM)'h');
//                    if (rand()%5==0) insert_key((WPARAM)'t');
                    /*
                                        if (rand()%10==0) {
                                            if (SAS_ZOOM>1)
                                                insert_key((WPARAM)'(');
                                        } else if (rand()%10==0){
                                            if (SAS_ZOOM<20)
                                                insert_key((WPARAM)')');
                                        }
                    */


                    if (counter<=0)
                    {
                        /*
                                                if (number>1)
                                                {
                                                    pos_ghostx[follow_ghost_num]=pos_ghostx[number-1];
                                                    pos_ghosty[follow_ghost_num]=pos_ghosty[number-1];
                                                    fpos_ghostx[follow_ghost_num]=fpos_ghostx[number-1];
                                                    fpos_ghosty[follow_ghost_num]=fpos_ghosty[number-1];
                                                    fspeed_ghostx[follow_ghost_num]=fspeed_ghostx[number-1];
                                                    fspeed_ghosty[follow_ghost_num]=fspeed_ghosty[number-1];
                                                    number--;
                                                    if (number>1) {
                                                        float xpos=(int)((1920-fpos_ghostx[x])/1920)*BITMAPSY+(int)((1080-fpos_ghosty[x])/1080);
                                                        int lowest=follow_ghost_num;
                                                        for (int x=0; x<number; x++) {
                                                             if ( (int)((1920-fpos_ghostx[x])/1920)*BITMAPSY+(int)((1080-fpos_ghosty[x])/1080)<xpos) {
                                                                xpos=(int)((1920-fpos_ghostx[x])/1920)*BITMAPSY+(int)((1080-fpos_ghosty[x])/1080);
                                                                lowest=x;
                                                             }
                                                        }
                                                        follow_ghost_num=lowest;
                                                    }
                                                } else {
                                                    follow_ghost=0;
                                                }
                        */

                        ghost_next();
//                        playsound|=2;
                        counter=1;
                        /*
                                                if (shade_map>=1 || shade_main) {
                                                    flowx=sin(fpstime+follow_ghost_num+sin(fpstime*1.2+follow_ghost_num))*50  + sin(fpstime*1.4+follow_ghost_num+sin(fpstime*1.5+follow_ghost_num))*10;
                                                    flowy=cos(fpstime*1.1+follow_ghost_num+sin(fpstime*1.3+follow_ghost_num))*50 + sin(fpstime*0.9+follow_ghost_num+sin(fpstime*1.3+follow_ghost_num))*10;
                                                }
                                                ffmpeg_posx=flowx+1920-pos_ghostx[follow_ghost_num]+(1920/2-(int)(texture_from_ffmpeg.getSize().x)/2);
                                                ffmpeg_posy=flowy+1080-pos_ghosty[follow_ghost_num]+(1080/2-(int)(texture_from_ffmpeg.getSize().y)/2);

                        //                        forced_jump=1;
                        //                        follow_ghost_pos();
                        */
                    }
//                    counter=6;

                    if (movie==0)
                    {
                        if (live_movie->getStatus()==sfe::Stopped)
                            updatemovie();
                        if (counter2<=0 && !live_movie->getStatus()==sfe::Stopped)
                        {
                            time_movie=live_movie->getPlayingOffset();
                            int add=300;
//                            int add=rand()%100+20;
                            if ( live_movie->getDuration() > (time_movie+sf::seconds(add + 5) ) )
                            {
                                live_movie->setPlayingOffset(time_movie+sf::seconds(add));
//                                rotation_movie=rand()%41-20;
                            }
                            else
                            {
                                live_movie->stop();
                                updatemovie();
                            }
                            counter2=0;
                        }
                    }





/*

                                         if (ffmpegfile==0 && fix==1) {
                                            int max=20;
                                            do {
                                                load_next_ffmpeg();
                    extern sf::Text mytext;
                    extern int font_to_ffmpeg_size;

                    //                            set_mytext(1);
                    //                            font_to_ffmpeg_size=1;
                    //                            mytext.setCharacterSize(10+rand()%260);
                    //                            font_to_ffmpeg();
                    //                            font_to_ffmpeg_size=0;
                                                if (ffmpegfile==1) { printf("failed loading ffmpeg\n"); max--; }
                                            } while (ffmpegfile==1 && max>=0);
                                            if (ffmpegfile==1) follow_ghost=0;

                                            rotation_ffmpeg=0;
                                            rotate_ffmpeg=0;

                                            rotation_ffmpeg=rand()%81-40;
                                            if (rotation_ffmpeg<0) rot_speed_ffmpeg=(rand()%180)/300.0;
                                            else rot_speed_ffmpeg=-(rand()%180)/300.0;
                    //                        rot_speed_ffmpeg=(rand()%61-30)/900.0;
                                            rotate_ffmpeg=1;
                    //                        size_ffmpeg=1;
                                        }
*/




                                         if (internetfile==0 && fix==1 && handler[INTERNET_SELECT].show==1) {
                                            int max=200;
                                            do {
                                                load_next_internet();
                    //                            set_mytext(1);
                    //                            font_to_ffmpeg();
                                                if (internetfile==1) { printf("failed loading internet\n"); max--; }
                                            } while (internetfile==1 && max>=0);
                                            if (internetfile==1) follow_ghost=0;
                                            rotation_internet=rand()%11-5;
                        //                    if (rotation_ffmpeg<0) rot_speed_ffmpeg=(rand()%20)/300.0;
                        //                    else rot_speed_ffmpeg=-(rand()%20)/300.0;
                                            rot_speed_internet=(rand()%61-30)/600.0;
                                            rotate_internet=1;
                        //                    size_internet=1;
                                        }



                }
            }
            first_click2=0;
//mousemove
//            first_click=0;
//babe
        }
        else if (follow_ghost==0 && mouse_move==1)
        {
            if (first_click2==0)
            {
                sf::Mouse::setPosition(sf::Vector2i(960,540));
                position = sf::Vector2i(960,540);
//                position = sf::Mouse::getPosition();
//                forced_jump=1;
//                follow_ghost_pos();
                first_click2=1;
            }
            sf::Vector2i position2=sf::Mouse::getPosition();
            if (position2.x!=960 || position2.y!=540 )
            {
                fposx=fposx+(position.x-position2.x);
                fposy=fposy+(position.y-position2.y);
                posx=fposx;
                posy=fposy;
//                posx=posx+(position.x-position2.x);
//                posy=posy+(position.y-position2.y);
//pospos
//                if (posx<=-1920)
                if (posx<-1920)
                {
                    posx=posx+1920;
                    fposx=fposx+1920;
                    picturex++;
                    if (picturex>maxpicturex)
                        picturex=0;
                    ReadBitmaps2();
                }
                else if (posx>=0)
//                else if (posx>0)
                {
                    posx=posx-1920;
                    fposx=fposx-1920;
                    picturex--;
                    if (picturex<0)
                        picturex=maxpicturex;
                    ReadBitmaps2();
                }
                if (posy<-1080)
//                if (posy<=-1080)
                {
                    posy=posy+1080;
                    fposy=fposy+1080;
                    picturey++;
                    if (picturey>maxpicturey)
                        picturey=0;
                    ReadBitmaps2();
                }
                else if (posy>=0)
//                else if (posy>0)
                {
                    posy=posy-1080;
                    fposy=fposy-1080;
                    picturey--;
                    if (picturey<0)
                        picturey=maxpicturey;
                    ReadBitmaps2();
                }
                sf::Mouse::setPosition(sf::Vector2i(960,540));
                position = sf::Vector2i(960,540);
                forced_jump=1;
//mousemove
//                first_click=0;
                follow_ghost_pos();
            }
            if (fragment_shader==1)
                picture_shader.setUniform("iMouse",  sf::Vector2f(  (float) (960) / SFMLView1.getSize().x,
                                          (float) (540) / SFMLView1.getSize().y ) );
            first_click=0;
        }
    }
    else
        first_click=0;

    if (record_screen==1 || follow_ghost==1)
    {
        if (record_pause==0)
            run_time=(run_time+fpstime_factor*(float)rate/60.0);
    }
    else
    {
        run_time=10*run_time-run_time;
        run_time=(run_time+fpstime_factor*clock_shader.getElapsedTime().asSeconds())/10;
    }
    blendit=0;
    if (record_screen==1 && recording_type==0 && !blocked_by_window)
        blendit=1;
    if (shade_main)
        blendit=1;
    if (plot_all==1 && handler[CANVAS_SELECT].show==1 && (blending>=1 && handler[CANVAS_SELECT].blending==0) || handler[CANVAS_SELECT].blending>=1)
        blendit=1;
    if (ffmpegfile==0 && handler[FFMPEG_SELECT].show==1 && ((blending>=1 && handler[FFMPEG_SELECT].blending==0) || handler[FFMPEG_SELECT].blending>=1))
        blendit=1;
    if (internetfile==0 && handler[INTERNET_SELECT].show==1 && (blending>=1 && handler[INTERNET_SELECT].blending==0) || handler[INTERNET_SELECT].blending>=1)
        blendit=1;
    if (movie==0 && handler[MOVIE_SELECT].show==1 && (blending>=1 && handler[MOVIE_SELECT].blending==0) || handler[MOVIE_SELECT].blending>=1)
        blendit=1;
    if (movie2==0 && handler[MOVIE2_SELECT].show==1 && (blending>=1 && handler[MOVIE2_SELECT].blending==0) || handler[MOVIE2_SELECT].blending>=1)
        blendit=1;

    if ( fragment_shader==1 || vertex_shader==1 || buffer_shader==1)
    {
        iFrame++;
        picture_shader.setUniform("iTime",   run_time );
    }
    if (fragment_shader==1)
    {
        if (buffer_shader==1)
            picture_shader.setUniform("buffer_plot",  1 );
        else
            picture_shader.setUniform("buffer_plot",  0 );
        picture_shader.setUniform("background_plot",  0 );
        picture_shader.setUniform("formula_on",  formula==1 );
        picture_shader.setUniform("formula",  formula );
        if (movie==0)
        {
            picture_shader.setUniform("iRotate", (float)(sprite_from_movie.getRotation()/360.0*2.0*PI));
            if (buffer_shader==1)
                shader_buffer.setUniform("iRotate", (float)(sprite_from_movie.getRotation()/360.0*2.0*PI));
            picture_shader.setUniform("texture_buffer", texture_from_movie_new);
            picture_shader.setUniform("iResolution_buffer",  sf::Vector2f( texture_from_movie_new.getSize().x,texture_from_movie_new.getSize().y) );
            picture_shader.setUniform("iResolution",  sf::Vector2f( texture_from_movie_new.getSize().x,texture_from_movie_new.getSize().y) );
        }
        else if (movie2==0)
        {
            picture_shader.setUniform("iRotate", (float)(sprite_from_movie2.getRotation()/360.0*2.0*PI));
            if (buffer_shader==1)
                shader_buffer.setUniform("iRotate", (float)(sprite_from_movie2.getRotation()/360.0*2.0*PI));
            picture_shader.setUniform("texture_buffer", texture_from_movie2_new);
            picture_shader.setUniform("iResolution_buffer",  sf::Vector2f( texture_from_movie2_new.getSize().x,texture_from_movie2_new.getSize().y) );
            picture_shader.setUniform("iResolution",  sf::Vector2f( texture_from_movie2_new.getSize().x,texture_from_movie2_new.getSize().y) );
        }
        else if (ffmpegfile==0)
        {
            picture_shader.setUniform("iRotate", (float)(sprite_from_ffmpeg.getRotation()/360.0*2.0*PI));
            if (buffer_shader==1)
                shader_buffer.setUniform("iRotate", (float)(sprite_from_ffmpeg.getRotation()/360.0*2.0*PI));
            picture_shader.setUniform("texture_buffer", texture_from_ffmpeg);
            picture_shader.setUniform("iResolution_buffer",  sf::Vector2f( texture_from_ffmpeg.getSize().x,texture_from_ffmpeg.getSize().y) );
            picture_shader.setUniform("iResolution",  sf::Vector2f( texture_from_ffmpeg.getSize().x,texture_from_ffmpeg.getSize().y) );
        }
        else if (internetfile==0)
        {
            picture_shader.setUniform("iRotate", (float)(sprite_from_internet.getRotation()/360.0*2.0*PI));
            if (buffer_shader==1)
                shader_buffer.setUniform("iRotate", (float)(sprite_from_internet.getRotation()/360.0*2.0*PI));
            picture_shader.setUniform("texture_buffer", texture_from_internet);
            picture_shader.setUniform("iResolution_buffer",  sf::Vector2f( texture_from_internet.getSize().x,texture_from_internet.getSize().y) );
            picture_shader.setUniform("iResolution",  sf::Vector2f( texture_from_internet.getSize().x,texture_from_internet.getSize().y) );
        }
        else if (shade_main>0)
        {
            picture_shader.setUniform("iResolution_buffer",  sf::Vector2f( 1920.0,1080.0) );
            picture_shader.setUniform("iResolution",  sf::Vector2f( 1920.0,1080.0) );
        }
        else if (buffer_shader==1)
        {
            picture_shader.setUniform("iResolution_buffer",  sf::Vector2f( texture_from_buffer.getSize().x,texture_from_buffer.getSize().y) );
        }
        if ( ffmpegfile==0)
        {
            if ( sf::Mouse::isButtonPressed(sf::Mouse::Right))
            {
                picture_shader.setUniform("iMouse",  sf::Vector2f( (float) (sf::Mouse::getPosition(SFMLView1).x) / SFMLView1.getSize().x,
                                          (float) (sf::Mouse::getPosition(SFMLView1).y) / SFMLView1.getSize().y ) );
                picture_shader.setUniform("iMouse_on",  1 );
//                shader_buffer.setUniform("iMouse_on",  1 );
            }
            else
            {
                picture_shader.setUniform("iMouse_on",  0 );
//                shader_buffer.setUniform("iMouse_on",  1 );
            }
            picture_shader.setUniform("iFrame",   iFrame );
        }
        picture_shader.setUniform("SAS_ZOOM",  SAS_ZOOM );
    }
    if (vertex_shader==1)
    {
        picture_shader.setUniform("wave_phase",   run_time );
        picture_shader.setUniform("wave_amplitude",  sf::Vector2f( (float) (sf::Mouse::getPosition(SFMLView1).x) / SFMLView1.getSize().x * 100.0,
                                  (float) (sf::Mouse::getPosition(SFMLView1).y) / SFMLView1.getSize().y * 100.0 ) );
    }
    if (buffer_shader==1)
    {
        shader_buffer.setUniform("background_plot",  0 );
        shader_buffer.setUniform("iTime",   run_time );
        shader_buffer.setUniform("iFrame",   iFrame );

        if (iFrame!=1)
        {
            if (swapper==0)
            {
                if (movie==0)
                {
                    shader_buffer.setUniform("texture_movie", texture_from_movie_new);
                    sprite_buffer->setTexture(texture_from_movie_new,true);
                }
                else if (movie2==0)
                {
                    shader_buffer.setUniform("texture_movie", texture_from_movie2_new);
                    sprite_buffer->setTexture(texture_from_movie2_new,true);
                }
                else
                {
//                    sprite_buffer->setTexture(texture_from_ffmpeg,true);
//                    texture_from_buffer.draw(*sprite_buffer);
//                    texture_from_buffer.display();
                    sprite_buffer->setTexture(texture_from_buffer.getTexture(),true);
                }
                texture_from_buffer2.clear(sf::Color(0,0,0,0));
                texture_from_buffer2.draw(*sprite_buffer,buffer_states);
                texture_from_buffer2.display();
                shader_buffer.setUniform("texture_buffer", texture_from_buffer2.getTexture());
                picture_shader.setUniform("texture_buffer", texture_from_buffer2.getTexture());
                swapper=1;
            }
            else
            {
                if (movie==0)
                {
                    shader_buffer.setUniform("texture_movie", texture_from_movie_new);
                    sprite_buffer->setTexture(texture_from_movie_new,true);
                }
                else if (movie2==0)
                {
                    shader_buffer.setUniform("texture_movie", texture_from_movie2_new);
                    sprite_buffer->setTexture(texture_from_movie2_new,true);
                }
                else
                {
//                    sprite_buffer->setTexture(texture_from_ffmpeg,true);
//                    texture_from_buffer.draw(*sprite_buffer);
//                    texture_from_buffer.display();
                    sprite_buffer->setTexture(texture_from_buffer2.getTexture(),true);
                }
                texture_from_buffer.clear(sf::Color(0,0,0,0));
                texture_from_buffer.draw(*sprite_buffer,buffer_states);
                texture_from_buffer.display();
                shader_buffer.setUniform("texture_buffer", texture_from_buffer.getTexture());
                picture_shader.setUniform("texture_buffer", texture_from_buffer.getTexture());
                swapper=0;
            }
            picture_shader.setUniform("iResolution_buffer",  sf::Vector2f( texture_from_buffer.getSize().x,texture_from_buffer.getSize().y) );
        }
        if ( sf::Mouse::isButtonPressed(sf::Mouse::Right) )
        {
            shader_buffer.setUniform("iMouse",  sf::Vector2f( (float) (sf::Mouse::getPosition(SFMLView1).x) / SFMLView1.getSize().x,
                                     (float) (sf::Mouse::getPosition(SFMLView1).y) / SFMLView1.getSize().y ) );
            shader_buffer.setUniform("iMouse_on",  1 );
        }
        else if ( sf::Mouse::isButtonPressed(sf::Mouse::Left) )
        {
            shader_buffer.setUniform("iMouse",  sf::Vector2f( (float) (sf::Mouse::getPosition(SFMLView1).x) / SFMLView1.getSize().x,
                                     (float) (sf::Mouse::getPosition(SFMLView1).y) / SFMLView1.getSize().y ) );
            shader_buffer.setUniform("iMouse_on",  2 );
        }
        else
            shader_buffer.setUniform("iMouse_on",  0 );
    }

    if (vertex_shader==1 || fragment_shader==1)
        picture_states.shader = &picture_shader;
    else
        picture_states.shader=NULL;

    if (blending>=1 || blendit==1)
    {
        picture_states.blendMode=MyBlendingMode;
    }
    else
    {
        picture_states.blendMode=sf::BlendAlpha;
    }

//    if (ffmpegfile==0 && texture_from_ffmpeg.getSize().x==1920 && texture_from_ffmpeg.getSize().y==1080 ) {
//        texture_from_ffmpeg.update(SFMLView1,1920,1080);
//    }
//    SFMLView1.clear(sf::Color(0,0,0,0));
//    glClear(GL_DEPTH_BUFFER_BIT);
    extern int kleur_back;

    SFMLView1.setActive(true);
//    glClear(GL_COLOR_BUFFER_BIT);
    if (drawmazes==1 && kleur_back==1)
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    else if (drawmazes==0 && kleur_back==0)
        glClearColor(0.0f, 0.0f, 0.0f, (float)(set_transparant==0));
//        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    else if (drawmazes==0 && kleur_back==1)
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    else {
        if (plot_cubes)
            glClearColor(0.0f, 0.4f, 0.6f, (float)(set_transparant==0));
        else
            glClearColor(0.0f, 0.0f, 0.0f, (float)(set_transparant==0));
    }
//        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    SFMLView1.setActive(false);

/*
extern int ding_ready[];
extern sf::Texture ding_texture[];
extern sf::Sprite ding_sprite[];
extern sf::RenderTexture ding_texture_render[];
extern sf::Sprite ding_sprite_render[];
*/
/*
    render_locker2.lock();
    for (int i=0; i<10; i++) {
        if (ding_ready[i]) {
            SFMLView1.draw(ding_sprite[i]);
//            SFMLView1.draw(ding_sprite_render[i]);
            ding_ready[i]=0;
        }
    }
    render_locker2.unlock();
*/
    if (blending>=1 || shade_main!=0 || blendit==1)
    {
        texture_final.setActive(true);
        if (drawmazes==1 && kleur_back==1)
            glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        else if (drawmazes==0 && kleur_back==0)
            glClearColor(0.0f, 0.0f, 0.0f, (float)(set_transparant==0));
//            glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        else if (drawmazes==0 && kleur_back==1)
            glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        else
            glClearColor(0.0f, 0.0f, 0.0f, (float)(set_transparant==0));
//            glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//        texture_final.clear(sf::Color(0,0,0,0));
        texture_final.setActive(false);
    }

    if (movie==0)
        setmoviefile();

    if (blend_on_movie>=1 && movie==0 && ffmpegfile==0 && live_movie_is_mp3==0)
    {
        sf::Sprite sprite;

        if (tussen_texture.getSize()!=texture_from_ffmpeg.getSize())
        {
            tussen_texture.create(texture_from_ffmpeg.getSize().x,texture_from_ffmpeg.getSize().y);
//            savedata("creating texture",0);
        }

        tussen_texture.clear(sf::Color(0,0,0,0));
        if (smooth==1)
            tussen_texture.setSmooth(true);
        else
            tussen_texture.setSmooth(false);
        sf::Vector2f wanted_size = {(float)texture_from_ffmpeg.getSize().x,(float)texture_from_ffmpeg.getSize().y};
        sf::Vector2f new_size;

        sf::Vector2f movie_size = {(float)texture_from_movie_new.getSize().x,(float)texture_from_movie_new.getSize().y};;
//        sf::Vector2f movie_size = live_movie->getSize();
        sf::Vector2f target_size = movie_size;

        float source_ratio;
        float target_ratio;

        source_ratio = movie_size.x / movie_size.y;
        target_ratio = wanted_size.x / wanted_size.y;
        if ( source_ratio > target_ratio )
        {
            target_size.x = movie_size.x * wanted_size.x / movie_size.x;
            target_size.y = movie_size.y * wanted_size.x / movie_size.x;
        }
        else
        {
            target_size.x = movie_size.x * wanted_size.y / movie_size.y;
            target_size.y = movie_size.y * wanted_size.y / movie_size.y;
        }

        if (blend_on_movie==2)
        {
            if (target_size.x<wanted_size.x)
            {
                target_size.y=target_size.y*wanted_size.x/target_size.x;
                target_size.x=wanted_size.x;
            }
            else if (target_size.y<wanted_size.y)
            {
                target_size.x=target_size.x*wanted_size.y/target_size.y;
                target_size.y=wanted_size.y;
            }
        }

        new_size = target_size;
        sprite.setScale((float)new_size.x / movie_size.x, (float)new_size.y / movie_size.y);

        sprite.setTexture(texture_from_movie_new,false);
        sprite.setTextureRect({0,0,texture_from_movie_new.getSize().x,texture_from_movie_new.getSize().y});
        sprite.setOrigin(texture_from_movie_new.getSize().x/2,texture_from_movie_new.getSize().y/2);
//        sprite.setScale(sprite_from_movie.getScale());
//blendonmovie
//        sprite.setRotation(sprite_from_movie.getRotation());
//        sprite.setRotation(sprite_from_ffmpeg.getRotation());
        sprite.setRotation(0.0);
        sprite.setPosition(texture_from_ffmpeg.getSize().x/2,texture_from_ffmpeg.getSize().y/2);

        tussen_texture.draw(sprite);

        sprite.setTexture(texture_from_ffmpeg,false);
        sprite.setTextureRect({0,0,texture_from_ffmpeg.getSize().x,texture_from_ffmpeg.getSize().y});
        sprite.setOrigin(0.0,0.0);
        sprite.setScale(1.0,1.0);
        sprite.setRotation(0.0);
        sprite.setPosition(0.0,0.0);

//        static sf::BlendMode MyBlendingMode_movie(  sf::BlendMode::One,sf::BlendMode::One,sf::BlendMode::Add,
//                                                    sf::BlendMode::One,sf::BlendMode::SrcAlpha,sf::BlendMode::Add);
        static sf::BlendMode MyBlendingMode_movie(  sf::BlendMode::One,sf::BlendMode::One,sf::BlendMode::Add,
                sf::BlendMode::One,sf::BlendMode::SrcAlpha,sf::BlendMode::Add);

        tussen_texture.draw(sprite,MyBlendingMode_movie);
//        tussen_texture.draw(sprite);
        tussen_texture.display();
    }

    if (blend_on_movie>=1 && movieextern==0 && internetfile==0 && ffmpegfile==0)
    {
        sf::Sprite sprite;

        if (tussen_texture.getSize()!=texture_from_ffmpeg.getSize())
        {
            tussen_texture.create(texture_from_ffmpeg.getSize().x,texture_from_ffmpeg.getSize().y);
//            savedata("creating texture",0);
        }

        tussen_texture.clear(sf::Color(0,0,0,0));
        if (smooth==1)
            tussen_texture.setSmooth(true);
        else
            tussen_texture.setSmooth(false);
        sf::Vector2f wanted_size = {(float)texture_from_ffmpeg.getSize().x,(float)texture_from_ffmpeg.getSize().y};
        sf::Vector2f new_size;

        sf::Vector2f movie_size = {(float)texture_from_internet.getSize().x,(float)texture_from_internet.getSize().y};
//        sf::Vector2f movie_size = live_movie->getSize();
        sf::Vector2f target_size = movie_size;

        float source_ratio;
        float target_ratio;

        source_ratio = movie_size.x / movie_size.y;
        target_ratio = wanted_size.x / wanted_size.y;
        if ( source_ratio > target_ratio )
        {
            target_size.x = movie_size.x * wanted_size.x / movie_size.x;
            target_size.y = movie_size.y * wanted_size.x / movie_size.x;
        }
        else
        {
            target_size.x = movie_size.x * wanted_size.y / movie_size.y;
            target_size.y = movie_size.y * wanted_size.y / movie_size.y;
        }

        if (blend_on_movie==2)
        {
            if (target_size.x<wanted_size.x)
            {
                target_size.y=target_size.y*wanted_size.x/target_size.x;
                target_size.x=wanted_size.x;
            }
            else if (target_size.y<wanted_size.y)
            {
                target_size.x=target_size.x*wanted_size.y/target_size.y;
                target_size.y=wanted_size.y;
            }
        }

        new_size = target_size;
        sprite.setScale((float)new_size.x / movie_size.x, (float)new_size.y / movie_size.y);

        sprite.setTexture(texture_from_internet,false);
        sprite.setTextureRect({0,0,texture_from_internet.getSize().x,texture_from_internet.getSize().y});
        sprite.setOrigin(texture_from_internet.getSize().x/2,texture_from_internet.getSize().y/2);
//        sprite.setScale(sprite_from_movie.getScale());
//blendonmovie
//        sprite.setRotation(sprite_from_movie.getRotation());
//        sprite.setRotation(sprite_from_ffmpeg.getRotation());
        sprite.setRotation(0.0);
        sprite.setPosition(texture_from_ffmpeg.getSize().x/2,texture_from_ffmpeg.getSize().y/2);

        tussen_texture.draw(sprite);

        sprite.setTexture(texture_from_ffmpeg,false);
        sprite.setTextureRect({0,0,texture_from_ffmpeg.getSize().x,texture_from_ffmpeg.getSize().y});
        sprite.setOrigin(0.0,0.0);
        sprite.setScale(1.0,1.0);
        sprite.setRotation(0.0);
        sprite.setPosition(0.0,0.0);

//        static sf::BlendMode MyBlendingMode_movie(  sf::BlendMode::One,sf::BlendMode::One,sf::BlendMode::Add,
//                                                    sf::BlendMode::One,sf::BlendMode::SrcAlpha,sf::BlendMode::Add);
        static sf::BlendMode MyBlendingMode_movie(  sf::BlendMode::One,sf::BlendMode::One,sf::BlendMode::Add,
                sf::BlendMode::One,sf::BlendMode::SrcAlpha,sf::BlendMode::Add);

        tussen_texture.draw(sprite,MyBlendingMode_movie);
//        tussen_texture.draw(sprite);
        tussen_texture.display();
    }


    if (fragment_shader==1)
    {
        picture_shader.setUniform("texture_surround[0]",  texturemaxinmempoint[used2[(render_picturex+0)%(maxpicturex+1)][(render_picturey+0)%(maxpicturey+1)]]->getTexture());
        picture_shader.setUniform("texture_surround[1]",  texturemaxinmempoint[used2[(render_picturex+1)%(maxpicturex+1)][(render_picturey+0)%(maxpicturey+1)]]->getTexture());
        picture_shader.setUniform("texture_surround[2]",  texturemaxinmempoint[used2[(render_picturex+0)%(maxpicturex+1)][(render_picturey+1)%(maxpicturey+1)]]->getTexture());
        picture_shader.setUniform("texture_surround[3]",  texturemaxinmempoint[used2[(render_picturex+1)%(maxpicturex+1)][(render_picturey+1)%(maxpicturey+1)]]->getTexture());
//        picture_shader.setUniform("iSubpixel",  sf::Vector2f((float)smooth_x,(float)smooth_y ) );


        picture_shader.setUniform("iSubpixel",  sf::Vector2f(
                        (float)render_posx-(float)smooth_x+(float)((int)smooth_x) ,
                        (float)render_posy-(float)smooth_y+(float)((int)smooth_y)
                                                             )
                                );

//        picture_shader.setUniform("iSubpixel",  sf::Vector2f((float)smooth_x,(float)smooth_y ) );
    }

    SFMLView1.setActive(true);

    if (plot_back==1 || 1)
    {
        if (movie==0 && timer_movie==0 && ((plot_back==1 && handler[MOVIE_SELECT].plot_front==0) || handler[MOVIE_SELECT].plot_front==-1) && handler[MOVIE_SELECT].show)
        {
            setmoviefile();
            if (live_movie_is_mp3==0)
            {
                if (record_screen==0 || record_pause==1 || tune==0) //mafkees
                    updatemovie();

                if (fragment_shader==1)
                {
                    picture_shader.setUniform("iRotate", (float)(sprite_from_movie.getRotation()/360.0*2.0*PI));
                    picture_shader.setUniform("texture_buffer", texture_from_movie_new);
                    picture_shader.setUniform("iResolution_buffer",  sf::Vector2f( texture_from_movie_new.getSize().x,texture_from_movie_new.getSize().y) );
                    picture_shader.setUniform("iResolution",  sf::Vector2f(
                                                  texture_from_movie_new.getSize().x * sprite_from_movie.getScale().x,
                                                  texture_from_movie_new.getSize().y * sprite_from_movie.getScale().y
                                              ) );
                }


                if (blend_on_movie>=1 && ffmpegfile==0)
                {
                    sprite_from_ffmpeg.setTexture(tussen_texture.getTexture(),false);
                    sprite_from_ffmpeg.setPosition(sprite_from_movie.getPosition());
                    sprite_from_ffmpeg.setRotation(sprite_from_movie.getRotation());
                    if (blending>=1 || shade_main!=0 || blendit==1)
                    {
                        if ((blending>=1 && handler[MOVIE_SELECT].blending==0) || handler[MOVIE_SELECT].blending>=1 )
                        {
                            texture_final.draw(sprite_from_ffmpeg,picture_states);
                        }
                        else
                        {
                            sf::BlendMode old_mode=picture_states.blendMode;
                            picture_states.blendMode=sf::BlendAlpha;
                            texture_final.draw(sprite_from_ffmpeg,picture_states);
                            picture_states.blendMode=old_mode;
                        }
                    }
                    else
                        SFMLView1.draw(sprite_from_ffmpeg,picture_states);
                    sprite_from_ffmpeg.setTexture(texture_from_ffmpeg,false);
                }
                else
                {
                    if (blending>=1 || shade_main!=0 || blendit==1)
                    {
                        if ((blending>=1 && handler[MOVIE_SELECT].blending==0) || handler[MOVIE_SELECT].blending>=1 )
                        {
                            texture_final.draw(sprite_from_movie,picture_states);
                        }
                        else
                        {
                            sf::BlendMode old_mode=picture_states.blendMode;
                            picture_states.blendMode=sf::BlendAlpha;
                            texture_final.draw(sprite_from_movie,picture_states);
                            picture_states.blendMode=old_mode;
                        }
                    }
                    else
                        SFMLView1.draw(sprite_from_movie,picture_states);
                }

                sprintf(error_msg2,"%.3f / %.3f  %.3f fps  %d x %d",
                        (float)(live_movie->getPlayingOffset().asMilliseconds())/1000.0,
                        (float)(live_movie->getDuration().asMilliseconds())/1000.0,
                        live_movie->getFramerate(),
                        texture_from_movie_new.getSize().x,
                        texture_from_movie_new.getSize().y ) ;
            }
            else
                sprintf(error_msg2,"%.3f / %.3f",
                        (float)(live_movie->getPlayingOffset().asMilliseconds())/1000.0,
                        (float)(live_movie->getDuration().asMilliseconds())/1000.0);

            error_flag2=1;
        }
        else if (movie==0 && ((plot_back==1 && handler[MOVIE_SELECT].plot_front==0) || handler[MOVIE_SELECT].plot_front==-1))
            timer_movie--;

        if (ffmpegfile==0 && blend_on_movie==0 && ((plot_back==1 && handler[FFMPEG_SELECT].plot_front==0) || handler[FFMPEG_SELECT].plot_front==-1))
//        if (ffmpegfile==0 && blend_on_movie==0 && ((plot_back==1 && handler[FFMPEG_SELECT].plot_front==0)))
        {

            setffmpegfile();
            if (handler[FFMPEG_SELECT].show)
            {

                if (handler[FFMPEG_SELECT].shader==0)
                {
                    picture_states.shader=NULL;
                }

                if (blending>=1 || shade_main!=0 || blendit==1)
                {
                    if ((blending>=1 && handler[FFMPEG_SELECT].blending==0) || handler[FFMPEG_SELECT].blending>=1 )
                    {
                        texture_final.draw(sprite_from_ffmpeg,picture_states);
                    }
                    else
                    {
                        sf::BlendMode old_mode=picture_states.blendMode;
                        picture_states.blendMode=sf::BlendAlpha;
                        texture_final.draw(sprite_from_ffmpeg,picture_states);
                        picture_states.blendMode=old_mode;
                    }
                }
                else
                    SFMLView1.draw(sprite_from_ffmpeg,picture_states);

                if (handler[FFMPEG_SELECT].shader==0)
                {
                    if (vertex_shader==1 || fragment_shader==1)
                        picture_states.shader = &picture_shader;

                }
            }
        }

        if (internetfile==0 && ((plot_back==1 && handler[INTERNET_SELECT].plot_front==0) || handler[INTERNET_SELECT].plot_front==-1)) {
//hello
//            if (movieextern==0) {
//                sprintf(error_msg3,"%s FRAME=%d %s",seconds_to_time(playing_time),playing_screen_num,playing_info_static);
//                error_flag3=1;
//            }
            setinternetfile();
            if ( handler[INTERNET_SELECT].show)
            {

                if (handler[INTERNET_SELECT].shader==0)
                {
                    picture_states.shader = NULL;
                }

                if (blending>=1 || shade_main!=0 || blendit==1)
                {
                    if ((blending>=1 && handler[INTERNET_SELECT].blending==0) || handler[INTERNET_SELECT].blending>=1 )
                    {
                        texture_final.draw(sprite_from_internet,picture_states);
                    }
                    else
                    {
                        sf::BlendMode old_mode=picture_states.blendMode;
                        picture_states.blendMode=sf::BlendAlpha;
                        texture_final.draw(sprite_from_internet,picture_states);
                        picture_states.blendMode=old_mode;
                    }
                }
                else
                    SFMLView1.draw(sprite_from_internet,picture_states);

                if (handler[INTERNET_SELECT].shader==0)
                {
                    if (vertex_shader==1 || fragment_shader==1)
                        picture_states.shader = &picture_shader;
                }

            }
        }
//slots
        if (movie2==0 && timer_movie2==0 && ((plot_back==1 && handler[MOVIE2_SELECT].plot_front==0) || handler[MOVIE2_SELECT].plot_front==-1) && handler[MOVIE2_SELECT].show)
        {
            setmoviefile2();
            if (live_movie2_is_mp3==0)
            {
                if (record_screen==0 || record_pause==1 || tune==0) //mafkees
                    updatemovie2();
//                if (record_screen==0 || record_pause==1)
//                    updatemovie2();
                if (fragment_shader==1)
                {
                    picture_shader.setUniform("iRotate", (float)(sprite_from_movie2.getRotation()/360.0*2.0*PI));
                    picture_shader.setUniform("texture_buffer", texture_from_movie2_new);
                    picture_shader.setUniform("iResolution_buffer",  sf::Vector2f( texture_from_movie2_new.getSize().x,texture_from_movie2_new.getSize().y) );
                    picture_shader.setUniform("iResolution",  sf::Vector2f(
                                                  texture_from_movie2_new.getSize().x * sprite_from_movie2.getScale().x,
                                                  texture_from_movie2_new.getSize().y * sprite_from_movie2.getScale().y
                                              ) );
                }

                if (blending>=1 || shade_main!=0 || blendit==1)
                {
                    if ((blending>=1 && handler[MOVIE2_SELECT].blending==0) || handler[MOVIE2_SELECT].blending>=1 )
                    {
                        texture_final.draw(sprite_from_movie2,picture_states);
                    }
                    else
                    {
                        sf::BlendMode old_mode=picture_states.blendMode;
                        picture_states.blendMode=sf::BlendAlpha;
                        texture_final.draw(sprite_from_movie2,picture_states);
                        picture_states.blendMode=old_mode;
                    }
                }
                else
                    SFMLView1.draw(sprite_from_movie2,picture_states);

                /*                if (blending>=1 || shade_main!=0)
                                    texture_final.draw(sprite_from_movie2,picture_states);  //doesn't need blending, its first. ???
                                else
                                    SFMLView1.draw(sprite_from_movie2,picture_states);
                */

                sprintf(error_msg3,"%.3f / %.3f  %.3f fps  %d x %d",
                        (float)(live_movie2->getPlayingOffset().asMilliseconds())/1000.0,
                        (float)(live_movie2->getDuration().asMilliseconds())/1000.0,
                        live_movie2->getFramerate(),
                        texture_from_movie2_new.getSize().x,
                        texture_from_movie2_new.getSize().y ) ;
            }
            else
                sprintf(error_msg3,"%.3f / %.3f",
                        (float)(live_movie2->getPlayingOffset().asMilliseconds())/1000.0,
                        (float)(live_movie2->getDuration().asMilliseconds())/1000.0);
            error_flag3=1;
        }
        else if (movie2==0 && ((plot_back==1 && handler[MOVIE2_SELECT].plot_front==0) || handler[MOVIE2_SELECT].plot_front==-1))
            timer_movie2--;
    }

//    spritemaxinmempoint[used2[arx][ary]]->setPosition(
//      (float)x*1920-(float)fmod(smooth_x+(double)maxpixelsx,1920.0),
//      (float)y*1080-(float)fmod(smooth_y+(double)maxpixelsy,1080.0));
//flicker

//    int arx=((int)(smooth_x/1920))%(totalpicturex);
//    int ary=((int)(smooth_y/1080))%(totalpicturey);


    for (x=0; x<=1; x++)
    {
        for (y=0; y<=1; y++)
        {
            int arx=(render_picturex+x)%(maxpicturex+1);
            int ary=(render_picturey+y)%(maxpicturey+1);
            if (texturemaxinmempoint[used2[arx][ary]]==NULL)
                savedata((char*)"ITS NULL!!!!",0);
            if (smooth==1)
            {
                spritemaxinmempoint[used2[arx][ary]]->setPosition(
                    (float)x*1920.0+(float)render_posx-(float)smooth_x+(float)((int)smooth_x),
                    (float)y*1080.0+(float)render_posy-(float)smooth_y+(float)((int)smooth_y)
                );
            }
            else
            {
                spritemaxinmempoint[used2[arx][ary]]->setPosition(
                    (float)x*1920.0+(float)render_posx,
                    (float)y*1080.0+(float)render_posy
                );
            }
            if (plot_front==1 && (plot_all==0 || handler[CANVAS_SELECT].show==0))
            {
                if (shade_main==1 && (fragment_shader==1 || vertex_shader==1))
                {
                    texture_final.draw(*spritemaxinmempoint[used2[arx][ary]]);
                }
                else
                {
                    if (blending>=1 || shade_main!=0 || blendit==1)
                        texture_final.draw(*spritemaxinmempoint[used2[arx][ary]]);
                    else
                        SFMLView1.draw(*spritemaxinmempoint[used2[arx][ary]]);
                }
            }
            else if (plot_back==1 && (plot_all==0 || handler[CANVAS_SELECT].show==0))
            {
                if (shade_main==1 && (fragment_shader==1 || vertex_shader==1))
                {
//                    backup_texture.draw(*spritemaxinmempoint[used2[arx][ary]]);
                    texture_final.draw(*spritemaxinmempoint[used2[arx][ary]]);
                }
                else
                {
                    if (blending>=1 || shade_main!=0 || blendit==1)
                        texture_final.draw(*spritemaxinmempoint[used2[arx][ary]]);
                    else
                        SFMLView1.draw(*spritemaxinmempoint[used2[arx][ary]]);
                }
            }
            spritemaxinmempoint[used2[arx][ary]]->setPosition(0.0,0.0);
        }
    }
    shader_map_angle=rotation_canvas;
    if (plot_all || plot_cubes) setcanvasfile();
//transparant
    if (plot_all==1) update_plot_all2(0); // back
    if (plot_cubes) plot_cubes_vertex();

    if (shade_main)
    {
        texture_from_ffmpeg.update(texture_final.getTexture());
    }

    SFMLView1.setActive(true);

    if (disp_text)
        make_text(0);

    if (f8_repeat==1)
    {
        perform_quit=1;
        f8_repeater();
        perform_quit=0;
    }

    if (plot_front==1 || 1)
    {
        if (movie2==0 && timer_movie2==0 && ((plot_front==1 && (handler[MOVIE2_SELECT].plot_front==0 || handler[MOVIE2_SELECT].plot_front==2)) || (handler[MOVIE2_SELECT].plot_front==1 || handler[MOVIE2_SELECT].plot_front==2)) && handler[MOVIE2_SELECT].show)
        {
            setmoviefile2();
            if (live_movie2_is_mp3==0)
            {
                if (record_screen==0 || record_pause==1 || tune==0) //mafkees
                    updatemovie2();
//                if (record_screen==0 || record_pause==1)
//                    updatemovie2();

                if (fragment_shader==1)
                {
                    picture_shader.setUniform("iRotate", (float)(sprite_from_movie2.getRotation()/360.0*2.0*PI));
                    picture_shader.setUniform("texture_buffer", texture_from_movie2_new);
                    picture_shader.setUniform("iResolution_buffer",  sf::Vector2f( texture_from_movie2_new.getSize().x,texture_from_movie2_new.getSize().y) );
                    picture_shader.setUniform("iResolution",  sf::Vector2f(
                                                  texture_from_movie2_new.getSize().x * sprite_from_movie2.getScale().x,
                                                  texture_from_movie2_new.getSize().y * sprite_from_movie2.getScale().y
                                              ) );
                }

                if (blending>=1 || shade_main!=0 || blendit==1)
                {
                    if ((blending>=1 && handler[MOVIE2_SELECT].blending==0) || handler[MOVIE2_SELECT].blending>=1 )
                    {
                        if (blending<2 && handler[MOVIE2_SELECT].blending==2)
                        {
                            sf::BlendMode old_mode=picture_states.blendMode;
                            picture_states.blendMode=MyBlendMode[4];
                            texture_final.draw(sprite_from_movie2,picture_states);
                            picture_states.blendMode=old_mode;
                        }
                        else
                            texture_final.draw(sprite_from_movie2,picture_states);
                    }
                    else
                    {
                        sf::BlendMode old_mode=picture_states.blendMode;
                        picture_states.blendMode=sf::BlendAlpha;
                        texture_final.draw(sprite_from_movie2,picture_states);
                        picture_states.blendMode=old_mode;
                    }
                }
                else
                    SFMLView1.draw(sprite_from_movie2,picture_states);

                /*                if (blending>=1 || shade_main!=0)
                                    texture_final.draw(sprite_from_movie2,picture_states);
                                else
                                    SFMLView1.draw(sprite_from_movie2,picture_states);
                */

                sprintf(error_msg3,"%.3f / %.3f  %.3f fps  %d x %d",
                        (float)(live_movie2->getPlayingOffset().asMilliseconds())/1000.0,
                        (float)(live_movie2->getDuration().asMilliseconds())/1000.0,
                        live_movie2->getFramerate(),
                        texture_from_movie2_new.getSize().x,
                        texture_from_movie2_new.getSize().y ) ;
            }
            else
                sprintf(error_msg3,"%.3f / %.3f",
                        (float)(live_movie2->getPlayingOffset().asMilliseconds())/1000.0,
                        (float)(live_movie2->getDuration().asMilliseconds())/1000.0);

            error_flag3=1;
        }
        else if (movie2==0 && ((plot_front==1 && handler[MOVIE2_SELECT].plot_front==0) || handler[MOVIE2_SELECT].plot_front==1))
            timer_movie2--;

        /*
                if (ffmpegfile==0 && blend_on_movie==0 && handler[FFMPEG_SELECT].plot_front && handler[FFMPEG_SELECT].show)
                {
                    setffmpegfile();
                    if (blending>=1 || shade_main!=0)
                        texture_final.draw(sprite_from_ffmpeg,picture_states);
                    else
                        SFMLView1.draw(sprite_from_ffmpeg,picture_states);
                    setffmpegfile();
                }
        */
//slots
//        if (ffmpegfile==0 && ((plot_front==1 && (handler[FFMPEG_SELECT].plot_front==0 || handler[FFMPEG_SELECT].plot_front==2) ) || handler[FFMPEG_SELECT].plot_front>=1 || handler[FFMPEG_SELECT].plot_front==-1))
        if (ffmpegfile==0 && ((plot_front==1 && (handler[FFMPEG_SELECT].plot_front==0 || handler[FFMPEG_SELECT].plot_front==2) ) || handler[FFMPEG_SELECT].plot_front>=1))

//        if (ffmpegfile==0 && blend_on_movie==0 && ((plot_front==1 && handler[FFMPEG_SELECT].plot_front==0) || handler[FFMPEG_SELECT].plot_front==1))
        {
            setffmpegfile();
            if (handler[FFMPEG_SELECT].show)
            {

                if (!((blending>=1 && handler[CANVAS_SELECT].blending==0) || handler[CANVAS_SELECT].blending>=1))
                {

                    if (handler[FFMPEG_SELECT].plot_front==2 && plot_all==1)
                    {
                        if (blending>=1 || shade_main!=0 || blendit==1)
                        {
                            texture_final.setActive(true);
                            texture_final.pushGLStates();
                        }
                        else
                        {
                            SFMLView1.setActive(true);
                            SFMLView1.pushGLStates();
                        }
//slotter
/*
                        glEnable(GL_TEXTURE_2D);
                        glEnable(GL_DEPTH_CLAMP);
                        glEnable(GL_DEPTH_TEST);
                        glDepthMask(GL_TRUE);
                        glDepthFunc(GL_LEQUAL);
                        glDepthRange(0.0f, 1.0f);
                        glClearDepth(0.0f);
                        glAlphaFunc(GL_GREATER, 0.0);
                        glEnable(GL_ALPHA_TEST);
*/

                        glEnable(GL_TEXTURE_2D);
                        glEnable(GL_DEPTH_CLAMP);
                        glEnable(GL_DEPTH_TEST);
                //        glDisable(GL_DEPTH_TEST);
//                        glDepthMask(GL_FALSE);
                        glDepthMask(GL_TRUE);
                        glDepthFunc(GL_LEQUAL);
                        glDepthRange(0.0f, 1.0f);
                        glClearDepth(0.0f);
                        glAlphaFunc(GL_GREATER, 0.9);
                        glEnable(GL_ALPHA_TEST);
//                        glDisable(GL_ALPHA_TEST);





                        if (blending>=1 || shade_main!=0 || blendit==1)
                        {
                            texture_final.setActive(false);
                        }
                        else
                        {
                            SFMLView1.setActive(false);
                        }
                    }
                }

                if (handler[FFMPEG_SELECT].shader==0)
                {
                    picture_states.shader = NULL;

                }
                if (blending>=1 || shade_main!=0 || blendit==1)
                {
                    if ((blending>=1 && handler[FFMPEG_SELECT].blending==0) || handler[FFMPEG_SELECT].blending>=1 )
                    {
                        if (blending<2 && handler[FFMPEG_SELECT].blending==2)
                        {
                            sf::BlendMode old_mode=picture_states.blendMode;
                            picture_states.blendMode=MyBlendMode[4];
                            texture_final.draw(sprite_from_ffmpeg,picture_states);
                            picture_states.blendMode=old_mode;
                        }
                        else
                            texture_final.draw(sprite_from_ffmpeg,picture_states);
                    }
                    else
                    {
                        sf::BlendMode old_mode=picture_states.blendMode;
                        picture_states.blendMode=sf::BlendAlpha;
                        texture_final.draw(sprite_from_ffmpeg,picture_states);
                        picture_states.blendMode=old_mode;
                    }
                }
                else {

                    SFMLView1.draw(sprite_from_ffmpeg,picture_states);
                }

                if (handler[FFMPEG_SELECT].shader==0)
                {
                    if (vertex_shader==1 || fragment_shader==1)
                        picture_states.shader = &picture_shader;
                }

                if (!((blending>=1 && handler[CANVAS_SELECT].blending==0) || handler[CANVAS_SELECT].blending>=1))
                {
                    if (handler[FFMPEG_SELECT].plot_front==2 && plot_all==1)
                    {
                        if (blending>=1 || shade_main!=0 || blendit==1)
                        {
                            texture_final.setActive(true);
                            texture_final.popGLStates();
//                            texture_final.setActive(false);
                        }
                        else
                        {
                            SFMLView1.setActive(true);
                            SFMLView1.popGLStates();
//                            SFMLView1.setActive(false);
                        }
                    }
                }

            }
        }
        if (internetfile==0 && ((plot_front==1 && (handler[INTERNET_SELECT].plot_front==0 || handler[INTERNET_SELECT].plot_front==2) ) || handler[INTERNET_SELECT].plot_front>=1))
        {
//            if (movieextern==0) {
//                sprintf(error_msg3,"%s FRAME=%d %s",seconds_to_time(playing_time),playing_screen_num,playing_info_static);
//                error_flag3=1;
//            }
            setinternetfile();
            if ( handler[INTERNET_SELECT].show)
            {

                if (!((blending>=1 && handler[CANVAS_SELECT].blending==0) || handler[CANVAS_SELECT].blending>=1))
                {

                    if (handler[INTERNET_SELECT].plot_front==2 && plot_all==1)
                    {
                        if (blending>=1 || shade_main!=0 || blendit==1)
                        {
                            texture_final.setActive(true);
                            texture_final.pushGLStates();
                        }
                        else
                        {
                            SFMLView1.setActive(true);
                            SFMLView1.pushGLStates();
                        }

                        glEnable(GL_TEXTURE_2D);
                        glEnable(GL_DEPTH_CLAMP);
                        glEnable(GL_DEPTH_TEST);
                        glDepthMask(GL_TRUE);
                        glDepthFunc(GL_LEQUAL);
                        glDepthRange(0.0f, 1.0f);
                        glClearDepth(0.0f);
                        glAlphaFunc(GL_GREATER, 0.0);
                        glEnable(GL_ALPHA_TEST);
                        if (blending>=1 || shade_main!=0 || blendit==1)
                        {
                            texture_final.setActive(false);
                        }
                        else
                        {
                            SFMLView1.setActive(false);
                        }
                    }
                }

                if (handler[INTERNET_SELECT].shader==0)
                {
                    picture_states.shader = NULL;
                }

                if (blend_on_movie>=1 && ffmpegfile==0 && movieextern==0 && internetfile==0)
                {
                    sprite_from_ffmpeg.setTexture(tussen_texture.getTexture(),false);
                    sprite_from_ffmpeg.setPosition(sprite_from_internet.getPosition());
                    sprite_from_ffmpeg.setRotation(sprite_from_internet.getRotation());
                    if (blending>=1 || shade_main!=0 || blendit==1)
                    {
                        if ((blending>=1 && handler[INTERNET_SELECT].blending==0) || handler[INTERNET_SELECT].blending>=1 )
                        {
                            if (blending<2 && handler[INTERNET_SELECT].blending==2)
                            {
                                sf::BlendMode old_mode=picture_states.blendMode;
                                picture_states.blendMode=MyBlendMode[4];
                                texture_final.draw(sprite_from_ffmpeg,picture_states);
                                picture_states.blendMode=old_mode;
                            }
                            else
                                texture_final.draw(sprite_from_ffmpeg,picture_states);
                        }
                        else
                        {
                            sf::BlendMode old_mode=picture_states.blendMode;
                            picture_states.blendMode=sf::BlendAlpha;
                            texture_final.draw(sprite_from_ffmpeg,picture_states);
                            picture_states.blendMode=old_mode;
                        }
                    }
                    else
                        SFMLView1.draw(sprite_from_ffmpeg,picture_states);
                    sprite_from_ffmpeg.setTexture(texture_from_ffmpeg,false);
                }
                else if (blending>=1 || shade_main!=0 || blendit==1)
                {
                    if ((blending>=1 && handler[INTERNET_SELECT].blending==0) || handler[INTERNET_SELECT].blending>=1 )
                    {
                        if (blending<2 && handler[INTERNET_SELECT].blending==2)
                        {
                            sf::BlendMode old_mode=picture_states.blendMode;
                            picture_states.blendMode=MyBlendMode[4];
                            texture_final.draw(sprite_from_internet,picture_states);
                            picture_states.blendMode=old_mode;
                        }
                        else
                            texture_final.draw(sprite_from_internet,picture_states);
                    }
                    else
                    {
                        sf::BlendMode old_mode=picture_states.blendMode;
                        picture_states.blendMode=sf::BlendAlpha;
                        texture_final.draw(sprite_from_internet,picture_states);
                        picture_states.blendMode=old_mode;
                    }
                }
                else
                    SFMLView1.draw(sprite_from_internet,picture_states);

                if (handler[INTERNET_SELECT].shader==0)
                {
                    if (vertex_shader==1 || fragment_shader==1)
                        picture_states.shader = &picture_shader;
                }

                if (!((blending>=1 && handler[CANVAS_SELECT].blending==0) || handler[CANVAS_SELECT].blending>=1))
                {
                    if (handler[INTERNET_SELECT].plot_front==2 && plot_all==1)
                    {
                        if (blending>=1 || shade_main!=0 || blendit==1)
                        {
                            texture_final.setActive(true);
                            texture_final.popGLStates();
                        }
                        else
                        {
                            SFMLView1.setActive(true);
                            SFMLView1.popGLStates();
                        }
                    }
                }
            }
        }
//jojojo
//        if (f8_repeat==0 && movie==0 && timer_movie==0 && ((plot_front==1 && handler[MOVIE_SELECT].plot_front==0) || handler[MOVIE_SELECT].plot_front==1) && handler[MOVIE_SELECT].show)
        if (f8_repeat!=0 && mirror==1) {
                    updatemovie();
        } else
        if ( movie==0 && timer_movie==0 && ((plot_front==1 && handler[MOVIE_SELECT].plot_front==0) || handler[MOVIE_SELECT].plot_front==1) && handler[MOVIE_SELECT].show)
        {
            setmoviefile();
            if (live_movie_is_mp3==0)
            {
                if (record_screen==0 || record_pause==1 || tune==0) //mafkees
                    updatemovie();

                if (fragment_shader==1)
                {
                    picture_shader.setUniform("iRotate", (float)(sprite_from_movie.getRotation()/360.0*2.0*PI));
                    picture_shader.setUniform("texture_buffer", texture_from_movie_new);
                    picture_shader.setUniform("iResolution_buffer",  sf::Vector2f( texture_from_movie_new.getSize().x,texture_from_movie_new.getSize().y) );
                    picture_shader.setUniform("iResolution",  sf::Vector2f(
                                                  texture_from_movie_new.getSize().x * sprite_from_movie.getScale().x,
                                                  texture_from_movie_new.getSize().y * sprite_from_movie.getScale().y
                                              ) );
                }

                if (blend_on_movie>=1 && ffmpegfile==0)
                {
                    sprite_from_ffmpeg.setTexture(tussen_texture.getTexture(),false);
                    sprite_from_ffmpeg.setPosition(sprite_from_movie.getPosition());
                    sprite_from_ffmpeg.setRotation(sprite_from_movie.getRotation());
                    if (blending>=1 || shade_main!=0 || blendit==1)
                    {
                        if ((blending>=1 && handler[MOVIE_SELECT].blending==0) || handler[MOVIE_SELECT].blending>=1 )
                        {
                            if (blending<2 && handler[MOVIE_SELECT].blending==2)
                            {
                                sf::BlendMode old_mode=picture_states.blendMode;
                                picture_states.blendMode=MyBlendMode[4];
                                texture_final.draw(sprite_from_ffmpeg,picture_states);
                                picture_states.blendMode=old_mode;
                            }
                            else
                                texture_final.draw(sprite_from_ffmpeg,picture_states);
                        }
                        else
                        {
                            sf::BlendMode old_mode=picture_states.blendMode;
                            picture_states.blendMode=sf::BlendAlpha;
                            texture_final.draw(sprite_from_ffmpeg,picture_states);
                            picture_states.blendMode=old_mode;
                        }
                    }
                    else
                        SFMLView1.draw(sprite_from_ffmpeg,picture_states);
                    sprite_from_ffmpeg.setTexture(texture_from_ffmpeg,false);
                }
                else
                {
                    if (blending>=1 || shade_main!=0 || blendit==1)
                    {
                        if ((blending>=1 && handler[MOVIE_SELECT].blending==0) || handler[MOVIE_SELECT].blending==1 )
                        {
                            texture_final.draw(sprite_from_movie,picture_states);
                        }
                        else
                        {
                            sf::BlendMode old_mode=picture_states.blendMode;
                            picture_states.blendMode=sf::BlendAlpha;
                            texture_final.draw(sprite_from_movie,picture_states);
                            picture_states.blendMode=old_mode;
                        }
                    }
                    else
                        SFMLView1.draw(sprite_from_movie,picture_states);
                }

                /*
                                if (blend_on_movie>=1 && ffmpegfile==0)
                                {
                                    sprite_from_ffmpeg.setTexture(tussen_texture.getTexture(),false);
                //wow
                //                    sprite_from_ffmpeg.setRotation(0.0);
                                    sprite_from_ffmpeg.setPosition(sprite_from_movie.getPosition());
                                    sprite_from_ffmpeg.setRotation(sprite_from_movie.getRotation());
                                    if (blending>=1 || shade_main!=0)
                                        texture_final.draw(sprite_from_ffmpeg,picture_states);
                                    else
                                        SFMLView1.draw(sprite_from_ffmpeg,picture_states);
                                    sprite_from_ffmpeg.setTexture(texture_from_ffmpeg,false);
                                }
                                else
                                {
                                    if (blending>=1 || shade_main!=0)
                                        texture_final.draw(sprite_from_movie,picture_states);
                                    else
                                        SFMLView1.draw(sprite_from_movie,picture_states);
                                }
                */




                sprintf(error_msg2,"%.3f / %.3f  %.3f fps  %d x %d",
                        (float)(live_movie->getPlayingOffset().asMilliseconds())/1000.0,
                        (float)(live_movie->getDuration().asMilliseconds())/1000.0,
                        live_movie->getFramerate(),
                        texture_from_movie_new.getSize().x,
                        texture_from_movie_new.getSize().y ) ;
            }
            else
                sprintf(error_msg2,"%.3f / %.3f",
                        (float)(live_movie->getPlayingOffset().asMilliseconds())/1000.0,
                        (float)(live_movie->getDuration().asMilliseconds())/1000.0);

            error_flag2=1;
        }
        else if (movie==0 && ((plot_front==1 && handler[MOVIE_SELECT].plot_front==0) || handler[MOVIE_SELECT].plot_front==1))
            timer_movie--;


    }
//transparant
    if (plot_all==1) update_plot_all2(1);  //front

extern int rectangle_paper_pos_x;
extern int rectangle_paper_pos_y;
extern int rectangle_paper_count_x;
extern int rectangle_paper_count_y;
extern int width_pixels;
extern int height_pixels;
extern sf::RectangleShape rectangle_paper_inner;
extern sf::RectangleShape rectangle_paper_outer;
extern int overlap_pixels;

    if (paper_select>0) {
        int pos_x;
        int pos_y;
/*
        if (plot_all) {
            rectangle_paper.setScale(sprite_from_canvas.getScale().x, sprite_from_canvas.getScale().y);
            rectangle_paper_inner.setScale(sprite_from_canvas.getScale().x, sprite_from_canvas.getScale().y);
            rectangle_paper_outer.setScale(sprite_from_canvas.getScale().x, sprite_from_canvas.getScale().y);
        } else {
            rectangle_paper.setScale(1.0, 1.0);
            rectangle_paper_inner.setScale(1.0, 1.0);
            rectangle_paper_outer.setScale(1.0, 1.0);
        }
*/
        pos_x=-render_picturex*1920+render_posx;
        pos_y=-render_picturey*1080+render_posy;

        float rot_x;
        float rot_y;
        float rot=rectangle_paper.getRotation();

        texture_final.setActive(false);
        SFMLView1.setActive(false);

        for (int n=0; n<3; n++) {
            for (int yy=0; yy<rectangle_paper_count_y; yy++) {
                for (int xx=0; xx<rectangle_paper_count_x; xx++) {
                    for (int y=-1; y<=1; y++) {
                        for (int x=-1; x<=1; x++) {
                            if (smooth==1) {
                                    rot_x=(float)(maxpixelsx*x)+(float)pos_x-(float)smooth_x+(float)((int)smooth_x);
                                    rot_y=(float)(maxpixelsy*y)+(float)pos_y-(float)smooth_y+(float)((int)smooth_y);
                                    float plus_x=rot_x*cos( rot*M_PI/180.0)+rot_y*sin( rot*M_PI/180.0);
                                    float plus_y=rot_x*sin(-rot*M_PI/180.0)+rot_y*cos(-rot*M_PI/180.0);

                                    if (n==0) rectangle_paper.setPosition(
                                                xx*width_pixels+
                                                plus_x,
                                                yy*height_pixels+
                                                plus_y);
                                    rectangle_paper_outer.setPosition(
                                                xx*width_pixels+
                                                plus_x ,
                                                yy*height_pixels+
                                                plus_y ) ;
                                    if (n==2) rectangle_paper_inner.setPosition(
                                                xx*width_pixels+
                                                (float)(overlap_pixels)+
                                                plus_x ,
                                                yy*height_pixels+
                                                (float)(overlap_pixels)+
                                                plus_y );
                            } else {
                                    rot_x=(float)(maxpixelsx*x)+(float)pos_x;
                                    rot_y=(float)(maxpixelsy*y)+(float)pos_y;
                                    float plus_x=rot_x*cos( rot*M_PI/180.0)+rot_y*sin( rot*M_PI/180.0);
                                    float plus_y=rot_x*sin(-rot*M_PI/180.0)+rot_y*cos(-rot*M_PI/180.0);
                                    if (n==0) rectangle_paper.setPosition(
                                                xx*width_pixels+
                                                plus_x,
                                                yy*height_pixels+
                                                plus_y);
                                    rectangle_paper_outer.setPosition(
                                                xx*width_pixels+
                                                plus_x,
                                                yy*height_pixels+
                                                plus_y);
                                    if (n==2) rectangle_paper_inner.setPosition(
                                                xx*width_pixels+
                                                (float)(overlap_pixels)+
                                                plus_x,
                                                yy*height_pixels+
                                                (float)(overlap_pixels)+
                                                plus_y) ;
                            }
                            rot_x=rectangle_paper_inner.getPosition().x;
                            rot_y=rectangle_paper_inner.getPosition().y;
                            rot=rectangle_paper.getRotation();
                            rectangle_paper_inner.setPosition(
                                                              rot_x*cos(rot*M_PI/180.0)+rot_y*sin(-rot*M_PI/180.0)+rectangle_paper_pos_x,
                                                              rot_x*sin(rot*M_PI/180.0)+rot_y*cos(rot*M_PI/180.0)+rectangle_paper_pos_y
                                                              );

                            rot_x=rectangle_paper_outer.getPosition().x;
                            rot_y=rectangle_paper_outer.getPosition().y;
                            rectangle_paper_outer.setPosition(
                                                              rot_x*cos(rot*M_PI/180.0)+rot_y*sin(-rot*M_PI/180.0)+rectangle_paper_pos_x,
                                                              rot_x*sin(rot*M_PI/180.0)+rot_y*cos(rot*M_PI/180.0)+rectangle_paper_pos_y
                                                              );
                            rot_x=rectangle_paper.getPosition().x;
                            rot_y=rectangle_paper.getPosition().y;
                            rectangle_paper.setPosition(
                                                              rot_x*cos(rot*M_PI/180.0)+rot_y*sin(-rot*M_PI/180.0)+rectangle_paper_pos_x,
                                                              rot_x*sin(rot*M_PI/180.0)+rot_y*cos(rot*M_PI/180.0)+rectangle_paper_pos_y
                                                              );
                            rectangle_paper_inner.setRotation(rot);
                            rectangle_paper_outer.setRotation(rot);
                            if (!
                                ((
                                rectangle_paper_outer.getPosition().y<0 &&
                                rectangle_paper_outer.getPosition().y+rectangle_paper_outer.getSize().y<0
                                ) ||
                                (
                                rectangle_paper_outer.getPosition().y>=1080 &&
                                rectangle_paper_outer.getPosition().y+rectangle_paper_outer.getSize().y>=1080
                                ) ||
                                (
                                rectangle_paper_outer.getPosition().x<0 &&
                                rectangle_paper_outer.getPosition().x+rectangle_paper_outer.getSize().x<0
                                ) ||
                                (
                                rectangle_paper_outer.getPosition().x>=1920 &&
                                rectangle_paper_outer.getPosition().x+rectangle_paper_outer.getSize().x>=1920
                                )
                                )) {
                                if (
                                    (
                                    rectangle_paper_outer.getPosition().y>=0 &&
                                    rectangle_paper_outer.getPosition().y <1080
                                    ) ||
                                    (
                                    rectangle_paper_outer.getPosition().y+rectangle_paper_outer.getSize().y>=0 &&
                                    rectangle_paper_outer.getPosition().y+rectangle_paper_outer.getSize().y <1080
                                    ) ||
                                    (
                                    rectangle_paper_outer.getPosition().x>=0 &&
                                    rectangle_paper_outer.getPosition().x <1920
                                    ) ||
                                    (
                                    rectangle_paper_outer.getPosition().x+rectangle_paper_outer.getSize().x>=0 &&
                                    rectangle_paper_outer.getPosition().x+rectangle_paper_outer.getSize().x <1920
                                    )
                                    ) {
                                    if (blending>=1 || shade_main!=0 || blendit==1)
                                    {
                                        if (n==0) texture_final.draw(rectangle_paper);
                                        if (n==1) texture_final.draw(rectangle_paper_outer);
                                        if (n==2) texture_final.draw(rectangle_paper_inner);
                                    }
                                    else
                                    {
                                        if (n==0) SFMLView1.draw(rectangle_paper);
                                        if (n==1) SFMLView1.draw(rectangle_paper_outer);
                                        if (n==2) SFMLView1.draw(rectangle_paper_inner);
                                    }
                                }

                            }
                        }
                    }
                }
            }
        }
    }
    if (plot_all==1)
    {
        if (!((blending>=1 && handler[CANVAS_SELECT].blending==0) || handler[CANVAS_SELECT].blending>=1))
        {
            if (blending>=1 || shade_main!=0 || blendit==1)
            {
                texture_final.setActive(true);
            }
            else
            {
                SFMLView1.setActive(true);
            }
        }
    }
//    SFMLView1.setActive(false);

//here1
    /*
        if (blending>=1 || shade_main!=0 || blendit==1)
            texture_final.setActive(true);
        else
            SFMLView1.setActive(true);

            SFMLView1.setActive(false);
    */
    /*
        if (blending>=1 || shade_main!=0 || blendit==1)
        {
            SFMLView1.setActive(false);
            sf::Sprite sprite_final;
            sprite_final.setTexture(texture_final.getTexture(),false);
            sprite_final.setTextureRect({0,0,1920,1080});
            sprite_final.setPosition(0,0);
    //        sprite_final.setPosition(-(float)smooth_x+(float)((int)smooth_x),-(float)smooth_y+(float)((int)smooth_y));
            texture_final.display();
            if (shade_main!=0) {
    //            picture_shader.setUniform("texture_buffer", texture_final.getTexture());
    //            picture_shader.setUniform("pos_correction", sf::Vector2f( 0.0,0.0));
    //            picture_shader.setUniform("iResolution",  sf::Vector2f( -1920.0,1080.0) );
    //            picture_shader.setUniform("iResolution_buffer",  sf::Vector2f( -1920.0,1080.0) );
                SFMLView1.draw(sprite_final);
    //            texture_final.setActive(false);
    //            backup_texture.clear(sf::Color(0,0,0,255));
            }
            else {
    //            texture_final.setActive(false);
                SFMLView1.draw(sprite_final);
            }
        }
    */

    static char score[200];

    if (recover>0)
        packy=(rand())%4;
    else
    {
        if (fspeedx<0)
            packy=0;
        if (fspeedx>0)
            packy=1;
        if (fspeedy<0)
            packy=2;
        if (fspeedy>0)
            packy=3;
        /*        if (pen_speedx<0)
                    packy=0;
                if (pen_speedx>0)
                    packy=1;
                if (pen_speedy<0)
                    packy=2;
                if (pen_speedy>0)
                    packy=3;
        */

    }

    if ( ((maze_up==0 && maze_down==0 && maze_left==0 && maze_right==0) || fhapper==0.0) && recover==0)
    {
        wocky=2;
        wocky_speed=5;
        fwocky_speed=20;
        if (fhapper>0.0)
        {
            fhapper=0.0;
            soundoff=soundoff|1;
            playsound=playsound|1;
        }
    }
//hopla

    if (old_number!=number)
    {
        mutje.lock();
        if (connected==1 && playerleft==0)
        {
            m_pointCloud.resize((number*2+2)); // add one or two pacman's.
            size_pointcloud=number*2+2;
        }
        else
        {
            m_pointCloud.resize((number*2+1)); // add one or two pacman's.
            size_pointcloud=number*2+1; // 6 elements (3 x XY)
        }
        old_number=number;
        mutje.unlock();
    }
    if (!(record_screen==1 && record_pause==1))
//    if (ghost==1 && !(record_screen==1 && record_pause==1))
    {
//crossing

        int cut_left=0;
        int cut_right=0;
        int cut_up=0;
        int cut_down=0;

        static float fspeedx_last=0.0,fspeedy_last=0.0;

        int posX;
        int posY;


        if (follow_ghost==0)
        {
            mazemovex=(picturex*1920-posx-32)/64;
            mazemovey=(picturey*1080-posy   )/72;
            posX=(picturex*1920-posx-32)%64;
            posY=(picturey*1080-posy   )%72;
        }
        else
        {
            mazemovex=(  mem_picturex*1920-mem_posx - 32 )/64;
            mazemovey=(  mem_picturey*1080-mem_posy      )/72;
            posX=(mem_picturex*1920-mem_posx-32)%64;
            posY=(mem_picturey*1080-mem_posy   )%72;
        }

        if (fspeedx!=0.0 || fspeedy!=0.0)
        {
            fspeedx_last=fspeedx;
            fspeedy_last=fspeedy;
        }

        mazemovex=(mazemovex-45+60*(maxpicturex+1))%(30*(maxpicturex+1));
        mazemovey=(mazemovey-23+30*(maxpicturey+1))%(15*(maxpicturey+1));

        /*
                if (eat_delay) {
                    maze_plot[eat_delay_mazemovex][eat_delay_mazemovey]=eat_delay_mazemove_blokje;
                    maze_plot[eat_delay_next_plotx][eat_delay_next_ploty]=eat_delay_next_plot_blokje;
                    adapt(eat_delay_mazemovex,eat_delay_mazemovey);
                    adapt(eat_delay_next_plotx,eat_delay_next_ploty);
                    eat_delay=0;
                }

                eat_delay_mazemovex2=mazemovex;
                eat_delay_mazemovey2=mazemovey;
        */

        int blokje=maze_plot[mazemovex][mazemovey];

        if ((blokje&64)==64 && fspeedx_last!=0.0)
        {
            if ( posX>=0 && posX<(63-15) )
                cut_left=63-15-posX;
        }
        if ((blokje&32)==32 && fspeedy_last!=0.0)
        {
            if ( posY>=0 && posY<(71-16) )
                cut_up=71-16-posY;
        }

        blokje=maze_plot[(mazemovex+1)%(30*(maxpicturex+1))][mazemovey];
        if ((blokje&64)==64 && fspeedx_last!=0.0)
        {
            if ( posX>63-47 )
                cut_right=posX-63+47;
        }

        blokje=maze_plot[mazemovex][(mazemovey+1)%(15*(maxpicturey+1))];
        if ((blokje&32)==32 && fspeedy_last!=0.0)
        {
            if ( posY>71-54 )
                cut_down=posY-71+54;
        }

        int offsetx;
        int offsety;

        extern int yellow;

        if (follow_ghost==0)
        {
            float yow;
            yow=0.0;
            float yow_off_x;
            yow_off_x=0.0;
            float yow_off_y;
            yow_off_y=0.0;

            if (recover>0)
            {
                yow=sin((20.0-(float)recover)/20.0*PI)+(1.0+sin(fpstime))/2.0;
                yow_off_x=-(32-9)*(yow*5.0);
                yow_off_y=-(36-10)*(yow*5.0);
                if (yellow==1)
                {
                    spritedot2.setScale(1.0+yow*5.0, 1.0+yow*5.0);
                }
                else
                {
                    spritedot.setScale(1.0+yow*5.0, 1.0+yow*5.0);
                }
                cut_left=0;
                cut_right=0;
                cut_up=0;
                cut_down=0;
            }
            offsetx=960-32+9-new_verschilx;
            offsety=540-36+10-new_verschily;
//yankee
            if ( (offsetx>(9-64-yow_off_x)) && (offsety>(10-72-yow_off_y)) && (offsetx<1980) && (offsety<1080))
            {


                if (ghost==1)
                {
                    if (smooth)
                    {
                        RenderBlit2(  (float)(yow_off_x+offsetx+cut_left)-smooth_x+(float)((int)smooth_x)-(float)fposx+(float)((int)fposx),
                                      (float)(yow_off_y+offsety+cut_up)  -smooth_y+(float)((int)smooth_y)-(float)fposy+(float)((int)fposy),
                                      0*64+9+128*packy+cut_left,
                                      72+10+wocky_anim[wocky]*72+cut_up,
                                      64-18-cut_left-cut_right,
                                      72-20-cut_up-cut_down);
                    }
                    else
                    {
                        RenderBlit2(  (float)(yow_off_x+offsetx+cut_left),
                                      (float)(yow_off_y+offsety+cut_up),
                                      0*64+9+128*packy+cut_left,
                                      72+10+wocky_anim[wocky]*72+cut_up,
                                      64-18-cut_left-cut_right,
                                      72-20-cut_up-cut_down);
                    }
                }
            }
            if (recover>0)
            {
                if (yellow==1)
                {
                    spritedot2.setScale(1.0,1.0 );
                }
                else
                {
                    spritedot.setScale(1.0,1.0);
                }
            }
        }
        else
        {
            int new_verschilx=-(picturex*1920-posx)+(mem_picturex*1920-mem_posx);
            int new_verschily=-(picturey*1080-posy)+(mem_picturey*1080-mem_posy);

            offsetx=960-32+9+new_verschilx;
            offsety=540-36+10+new_verschily;

            if ( (offsetx>(9-64)) && (offsety>(10-72)) && (offsetx<1980) && (offsety<1080))
            {
                if (ghost==1)
                {
                    if (smooth)
                    {
                        RenderBlit2(
                            offsetx+cut_left -smooth_x+(float)((int)smooth_x)-(float)fposx+(float)((int)fposx),
                            offsety+cut_up -smooth_y+(float)((int)smooth_y)-(float)fposy+(float)((int)fposy),
                            0*64+9+128*packy+cut_left,  72+10+wocky_anim[wocky]*72+cut_up,
                            64-18-cut_left-cut_right,72-20-cut_up-cut_down);
                    }
                    else
                    {
                        RenderBlit2(
                            offsetx+cut_left,
                            offsety+cut_up,
                            0*64+9+128*packy+cut_left,  72+10+wocky_anim[wocky]*72+cut_up,
                            64-18-cut_left-cut_right,72-20-cut_up-cut_down);
                    }
                }
            }
        }


//hopla
        m_pointCloud[0].texCoords.x = (float) (9+128*packy+cut_left)*150.0;
        m_pointCloud[0].texCoords.y = (float) (72+10+wocky_anim[wocky]*72+cut_up)*150.0;

        if (smooth)
        {
            m_pointCloud[0].position.x = (float) fmod(offsetx+32-9+cut_left/2.0-cut_right/2.0+maxpixelsx-(float)smooth_x+(float)((int)smooth_x)-(float)fposx+(float)((int)fposx),maxpixelsx);
            m_pointCloud[0].position.y = (float) fmod(offsety+36-10+cut_up/2.0-cut_down/2.0+maxpixelsy*1.5-540.0-(float)smooth_y+(float)((int)smooth_y)-(float)fposy+(float)((int)fposy),maxpixelsy)-(float)maxpixelsy*0.5+540.0;
        }
        else
        {
            m_pointCloud[0].position.x = (float) fmod(offsetx+32-9+cut_left/2.0-cut_right/2.0+maxpixelsx,maxpixelsx);
            m_pointCloud[0].position.y = (float) fmod(offsety+36-10+cut_up/2.0-cut_down/2.0+maxpixelsy*1.5-540.0,maxpixelsy)-(float)maxpixelsy*0.5+540.0;
        }
//        m_pointCloud[0].position.x = (float) fmod(offsetx+32-9+cut_left/2.0-cut_right/2.0+maxpixelsx,maxpixelsx);
//        m_pointCloud[0].position.y = (float) fmod(offsety+36-10+cut_up/2.0-cut_down/2.0+maxpixelsy*1.5-540.0,maxpixelsy)-(float)maxpixelsy*0.5+540.0;
        if (64-18-cut_left-cut_right<1 ||  72-20-cut_up-cut_down<1)
            m_pointCloud[0].color = sf::Color(255,0,0,0);
        else
            m_pointCloud[0].color = sf::Color((UINT32)255,(UINT32)0,(UINT32)(64-18-(cut_left+cut_right)),(UINT32)(72-20-(cut_up+cut_down)));

        if (fragment_shader==1 && ffmpegfile==0)
        {
            float sizex=(float)texture_from_ffmpeg.getSize().x*sprite_from_ffmpeg.getScale().x;
            float sizey=(float)texture_from_ffmpeg.getSize().y*sprite_from_ffmpeg.getScale().y;
            picture_shader.setUniform("pos_pacman",  sf::Vector2f((float)(offsetx-960+32-9) + 1920.0/2.0 - (sizex)/2.0,(float)-(offsety-540+36-10) + 1080.0*0.0 + (1080.0-sizey)/2.0 ) );


//        picture_shader.setUniform("pos_correction",  sf::Vector2f( (float) sprite_from_ffmpeg.getPosition().x - (sizex)/2.0,
//                                                                   (float) -sprite_from_ffmpeg.getPosition().y + 1080.0*0.5 + (1080.0-sizey)/2.0        )  );

        }
    }

    if (fhapper>0.0)
    {
        fhapper=fhapper-1.0;
        if (fhapper<=0.0)
        {
            fhapper=0.0;
            soundoff=soundoff|1;
            playsound=playsound|1;
        }
        fwocky_speed=fwocky_speed-4.0*((float)fabs(fspeedx*fspeed_adjust) + (float)fabs(fspeedy*fspeed_adjust));
        if (fwocky_speed<0.0)
        {
            fwocky_speed=20;
            wocky++;
            if (wocky>5)
                wocky=0;
        }
    }
    if (recover>0)
    {
        wocky=(rand())%6;
    }

    if (playerleft==1)
        remote_init=1;
    if (connected==1 && playerleft==0)
    {
        int offsetx;
        int offsety;
        int verschilx;
        int verschily;
        float volume;
        static int speedx=0,speedy=0;
        static int old_remote_posx2=0,old_remote_posy2=0;

        if (old_remote_posx2!=remote_posx)
        {
            speedx=1;
            speedy=0;
        }
        else if (old_remote_posy2!=remote_posy)
        {
            speedy=1;
            speedx=0;
        }
        old_remote_posx2=remote_posx;
        old_remote_posy2=remote_posy;

        verschilx=remote_posx-(picturex*1920-posx);
        verschily=remote_posy-(picturey*1080-posy);

        if (verschilx<=(-(maxpicturex+1)*1920)/2)
            verschilx=verschilx+(maxpicturex+1)*1920;
        if (verschilx>=((maxpicturex+1)*1920)/2)
            verschilx=verschilx-(maxpicturex+1)*1920;
        if (verschily<=(-(maxpicturey+1)*1080)/2)
            verschily=verschily+(maxpicturey+1)*1080;
        if (verschily>=((maxpicturey+1)*1080/2))
            verschily=verschily-(maxpicturey+1)*1080;

        volume=30.0-sqrt(verschilx*verschilx+verschily*verschily)/100;
        if (volume<5)
            volume=5;
        sound[4].setVolume(volume);

//crossing

        int cut_left=0;
        int cut_right=0;
        int cut_up=0;
        int cut_down=0;

        int posX;
        int posY;

        mazemovex=(remote_posx-32)/64;
        mazemovey=(remote_posy   )/72;
        posX=(remote_posx-32)%64;
        posY=(remote_posy   )%72;

        mazemovex=(mazemovex-45+60*(maxpicturex+1))%(30*(maxpicturex+1));
        mazemovey=(mazemovey-23+30*(maxpicturey+1))%(15*(maxpicturey+1));

        int blokje=maze_plot[mazemovex][mazemovey];

        if ((blokje&64)==64 && speedx!=0)
        {
            if ( posX>=0 && posX<(63-15) )
                cut_left=63-15-posX;
        }
        if ((blokje&32)==32 && speedy!=0.0)
        {
            if ( posY>=0 && posY<(71-16) )
                cut_up=71-16-posY;
        }

        blokje=maze_plot[(mazemovex+1)%(30*(maxpicturex+1))][mazemovey];
        if ((blokje&64)==64 && speedx!=0)
        {
            if ( posX>63-47 )
                cut_right=posX-63+47;
        }

        blokje=maze_plot[mazemovex][(mazemovey+1)%(15*(maxpicturey+1))];
        if ((blokje&32)==32 && speedy!=0)
        {
            if ( posY>71-54 )
                cut_down=posY-71+54;
        }

        if (follow_ghost==0)
        {
            offsetx=960-32+9+verschilx-new_verschilx;
            offsety=540-36+10+verschily-new_verschily;
            if ( (offsetx>(9-64)) && (offsety>(10-72)) && (offsetx<1980) && (offsety<1080))
            {
                if (smooth)
                {
                    RenderBlit2(offsetx+cut_left-smooth_x+(float)((int)smooth_x)-(float)fposx+(float)((int)fposx),
                                offsety+cut_up-smooth_y+(float)((int)smooth_y)-(float)fposy+(float)((int)fposy),
                                0*64+9+128*packy2+cut_left,  72+10+wocky_anim[wocky2]*72+cut_up,
                                64-18-cut_left-cut_right,72-20-cut_up-cut_down);
                }
                else
                {
                    RenderBlit2(offsetx+cut_left,
                                offsety+cut_up,
                                0*64+9+128*packy2+cut_left,  72+10+wocky_anim[wocky2]*72+cut_up,
                                64-18-cut_left-cut_right,72-20-cut_up-cut_down);
                }
            }
        }
        else
        {
            offsetx=960-32+9+verschilx;
            offsety=540-36+10+verschily;
            if ( (offsetx>(9-64)) && (offsety>(10-72)) && (offsetx<1980) && (offsety<1080))
            {
                if (smooth)
                {
                    RenderBlit2(offsetx+cut_left-smooth_x+(float)((int)smooth_x)-(float)fposx+(float)((int)fposx),
                                offsety+cut_up-smooth_y+(float)((int)smooth_y)-(float)fposy+(float)((int)fposy),
                                0*64+9+128*packy2+cut_left,  72+10+wocky_anim[wocky2]*72+cut_up,
                                64-18-cut_left-cut_right,72-20-cut_up-cut_down);
                }
                else
                {
                    RenderBlit2(offsetx+cut_left,
                                offsety+cut_up,
                                0*64+9+128*packy2+cut_left,  72+10+wocky_anim[wocky2]*72+cut_up,
                                64-18-cut_left-cut_right,72-20-cut_up-cut_down);
                }
            }
        }

        m_pointCloud[1].texCoords.x = (float) (9+128*packy2+cut_left)*150.0;
        m_pointCloud[1].texCoords.y = (float) (72+10+wocky_anim[wocky2]*72+cut_up)*150.0;
        if (smooth)
        {
            m_pointCloud[1].position.x = (float) fmod(offsetx+32-9+cut_left/2.0-cut_right/2.0+maxpixelsx-(float)smooth_x+(float)((int)smooth_x)-(float)fposx+(float)((int)fposx),maxpixelsx);
            m_pointCloud[1].position.y = (float) fmod(offsety+36-10+cut_up/2.0-cut_down/2.0+maxpixelsy*1.5-540.0-(float)smooth_y+(float)((int)smooth_y)-(float)fposy+(float)((int)fposy),maxpixelsy)-(float)maxpixelsy*0.5+540.0;
        }
        else
        {
            m_pointCloud[1].position.x = (float) fmod(offsetx+32-9+cut_left/2.0-cut_right/2.0+maxpixelsx,maxpixelsx);
            m_pointCloud[1].position.y = (float) fmod(offsety+36-10+cut_up/2.0-cut_down/2.0+maxpixelsy*1.5-540.0,maxpixelsy)-(float)maxpixelsy*0.5+540.0;
        }
        if (64-18-cut_left-cut_right<1 ||  72-20-cut_up-cut_down<1)
            m_pointCloud[1].color = sf::Color(255,0,0,0);
        else
            m_pointCloud[1].color = sf::Color((UINT32)255,(UINT32)0,(UINT32)(64-18-(cut_left+cut_right)),(UINT32)(72-20-(cut_up+cut_down)));

        static int old_remote_posx;
        static int old_remote_posy;

        if (old_remote_posx==remote_posx && old_remote_posy==remote_posy || fhapper2==0.0)
        {
            wocky2=2;
            wocky_speed2=5;
            fwocky_speed2=20;
            if (fhapper2>0.0)
            {
                fhapper2=0.0;
                soundoff=soundoff|16;
                playsound=playsound|16;
            }
        }
        if (remote_init==1)
        {
            static int hoppa=0;
            static int old_remote_posx;
            static int old_remote_posy;
            if (hoppa==0)
            {
                hoppa=1;
                old_remote_posx=remote_posx;
                old_remote_posy=remote_posy;
                packy2=0;
            }
            if (old_remote_posx!=remote_posx || old_remote_posy!=remote_posy)
            {
                remote_init=0;
                hoppa=0;
                old_remote_posx=0;
                old_remote_posy=0;
            }
            else
                packy2=0;
        }
        if (remote_init==0)
        {
            if (old_remote_posy-remote_posy<0)
                packy2=2;
            if (old_remote_posy-remote_posy>0)
                packy2=3;
            if (old_remote_posx-remote_posx<0)
                packy2=0;
            if (old_remote_posx-remote_posx>0)
                packy2=1;
        }

        if (fhapper2>0.0)
        {
            fhapper2=fhapper2-1.0;
            if (fhapper2<=0.0)
            {
                fhapper2=0.0;
                soundoff=soundoff|16;
                playsound=playsound|16;
            }
            fwocky_speed2=fwocky_speed2-4.0*((float)fabs(old_remote_posx-remote_posx) + (float)fabs(old_remote_posy-remote_posy));
            if (fwocky_speed2<0.0)
            {
                fwocky_speed2=20;
                wocky2++;
                if (wocky2>5)
                    wocky2=0;
            }
        }
        old_remote_posx=remote_posx;
        old_remote_posy=remote_posy;
    }

    fbest_distance=fbest_distance*0.99;

    if (recover>0)
        recover--;

//    if ( (ghost==1 || (follow_ghost==1)) && !(record_screen==1 && record_pause==1))
    if ( !(record_screen==1 && record_pause==1))
    {

        static int addx=-45+60*totalpicturex;
        static int addy=-23+30*totalpicturey;
        static int modx=30*totalpicturex;
        static int mody=15*totalpicturey;
        int mazemovex;
        int mazemovey;

        ghostmode=1;

        for (num_ghost=0; num_ghost<number; num_ghost++)
        {

            int numloops;
            int loops;
            int offsetx=0;
            int offsety=0;
            int verschilx;
            int verschily;

            int pos_ghostx_old;
            int pos_ghosty_old;
            float fpos_ghostx_old;
            float fpos_ghosty_old;


            float fpos_ghostx_num_ghost=fpos_ghostx[num_ghost];
            float fpos_ghosty_num_ghost=fpos_ghosty[num_ghost];
            int pos_ghostx_num_ghost=pos_ghostx[num_ghost];
            int pos_ghosty_num_ghost=pos_ghosty[num_ghost];
            float fspeed_ghostx_num_ghost=fspeed_ghostx[num_ghost]*fspeed_ghost_all;
            float fspeed_ghosty_num_ghost=fspeed_ghosty[num_ghost]*fspeed_ghost_all;
            int check_num_ghost=check[num_ghost];

            if (goexit==0)
            {
                fpos_total=fabs(fspeed_ghostx_num_ghost*fspeed_adjust)+fabs(fspeed_ghosty_num_ghost*fspeed_adjust);
            }
            else
            {
                fpos_total=0.0;
            }

            pos_ghostx_old=pos_ghostx_num_ghost;
            pos_ghosty_old=pos_ghosty_num_ghost;

            fpos_ghostx_old=fpos_ghostx_num_ghost;
            fpos_ghosty_old=fpos_ghosty_num_ghost;

            if (goexit==0)
            {
//                fpos_ghostx_num_ghost=fpos_ghostx_num_ghost-fspeed_adjust*fspeed_ghostx_num_ghost*1.05;
//                fpos_ghosty_num_ghost=fpos_ghosty_num_ghost-fspeed_adjust*fspeed_ghosty_num_ghost*1.05;
                fpos_ghostx_num_ghost=fpos_ghostx_num_ghost-fspeed_adjust*fspeed_ghostx_num_ghost;
                fpos_ghosty_num_ghost=fpos_ghosty_num_ghost-fspeed_adjust*fspeed_ghosty_num_ghost;
            }

            pos_ghostx_num_ghost=fpos_ghostx_num_ghost;
            pos_ghosty_num_ghost=fpos_ghosty_num_ghost;

            remain=-(fpos_ghostx_old-(float)pos_ghostx_old+fpos_ghosty_old-(float)pos_ghosty_old);
//            remain=fpos_ghostx_old-(float)pos_ghostx_old+fpos_ghosty_old-(float)pos_ghosty_old;

            if ( (abs(pos_ghostx_num_ghost-pos_ghostx_old) >= 1) || (abs(pos_ghosty_num_ghost-pos_ghosty_old) >= 1))
            {
                numloops=abs(pos_ghostx_num_ghost-pos_ghostx_old)+abs(pos_ghosty_num_ghost-pos_ghosty_old);

                if (fspeed_ghostx_num_ghost<0.0)
                {
                    pos_ghostx_num_ghost=pos_ghostx_old+1;
                    fpos_total--;
                }
                else if (fspeed_ghostx_num_ghost>0.0)
                {
                    pos_ghostx_num_ghost=pos_ghostx_old-1;
                    fpos_total--;
                }
                else if (fspeed_ghosty_num_ghost<0.0)
                {
                    pos_ghosty_num_ghost=pos_ghosty_old+1;
                    fpos_total--;
                }
                else if (fspeed_ghosty_num_ghost>0.0)
                {
                    pos_ghosty_num_ghost=pos_ghosty_old-1;
                    fpos_total--;
                }
                /*                fpos_ghostx_num_ghost=fpos_ghostx_old-fspeed_adjust*fspeed_ghostx_num_ghost/(numloops+0.1);
                                fpos_ghosty_num_ghost=fpos_ghosty_old-fspeed_adjust*fspeed_ghosty_num_ghost/(numloops+0.1);

                                pos_ghostx_num_ghost=fpos_ghostx_num_ghost;
                                pos_ghosty_num_ghost=fpos_ghosty_num_ghost;
                */

            }
            else
            {
                numloops=1;
                pos_ghostx_num_ghost=pos_ghostx_old;
                pos_ghosty_num_ghost=pos_ghosty_old;
            }
            fpos_ghostx_num_ghost=fpos_ghostx_old;
            fpos_ghosty_num_ghost=fpos_ghosty_old;


            for (loops=0; loops<numloops; loops++)
            {
//                pos_ghostx_num_ghost=fpos_ghostx_num_ghost;
//                pos_ghosty_num_ghost=fpos_ghosty_num_ghost;

                if (pos_ghostx_num_ghost < -maxpixelsx)
                {
                    pos_ghostx_num_ghost=pos_ghostx_num_ghost+maxpixelsx;
                    fpos_ghostx_num_ghost=pos_ghostx_num_ghost;
                }
                else if (pos_ghostx_num_ghost >= 0)
                {
                    pos_ghostx_num_ghost=pos_ghostx_num_ghost-maxpixelsx;
                    fpos_ghostx_num_ghost=pos_ghostx_num_ghost;
                }
                if (pos_ghosty_num_ghost < -maxpixelsy)
                {
                    pos_ghosty_num_ghost=pos_ghosty_num_ghost+maxpixelsy;
                    fpos_ghosty_num_ghost=pos_ghosty_num_ghost;
                }
                else if (pos_ghosty_num_ghost >= 0)
                {
                    pos_ghosty_num_ghost=pos_ghosty_num_ghost-maxpixelsy;
                    fpos_ghosty_num_ghost=pos_ghosty_num_ghost;
                }

                verschilx=-pos_ghostx_num_ghost-(picturex*1920-posx-1920);
                verschily=-pos_ghosty_num_ghost-(picturey*1080-posy-1080);


                if (verschilx<=-maxpixelsx/2)
                    verschilx=verschilx+maxpixelsx;
                else if (verschilx>maxpixelsx/2)
                    verschilx=verschilx-maxpixelsx;
                if (verschily<=-maxpixelsy/2)
                    verschily=verschily+maxpixelsy;
                else if (verschily>maxpixelsy/2)
                    verschily=verschily-maxpixelsy;

//crossing
//                offsetx=960-32+verschilx;
//                offsety=540-36+verschily;
                offsetx=960-32+9+verschilx;
                offsety=540-36+10+verschily;
                int cheat;

                int old_verschilx=verschilx;
                int old_verschily=verschily;

                if (mazetype==1)
                {
                    cheat=rand()%2;
//spooky
//                    verschilx=(rand()*rand())%maxpixelsx-maxpixelsx/2;
//                    verschily=(rand()*rand())%maxpixelsy-maxpixelsy/2;
                }
                else
                    cheat=0;

                if ( (hunt!=0 || cheat==1) && !(flippo==1 && num_ghost==follow_ghost_num) )
//                if (hunt!=0 || cheat==1 || (follow_ghost==1 && num_ghost==follow_ghost_num))
                {
                    verschilx=-verschilx;
                    verschily=-verschily;
                }

                int flip;
                flip=0;

//                if ( (  ((pos_ghostx_num_ghost+32)%64)==0) && ((pos_ghosty_num_ghost%72)==0)  && ( (check[num_ghost]&1)==0))
                int do_also;
                do_also=0;
                if (flippo==1 && num_ghost==follow_ghost_num && ((check_num_ghost&1)==0))
                {
                    if ( ((pos_ghostx_num_ghost%32)==0) && ((pos_ghosty_num_ghost%36)==0)  )
                        do_also=1;
                }
                int do_mid;
                do_mid=0;
                if (((check_num_ghost&1)==0) && (  ((pos_ghostx_num_ghost+32)%64)==0) && ((pos_ghosty_num_ghost%72)==0))
                    do_mid=1;
                if ( do_mid || do_also)
                {
                    int next_plotx;
                    int next_ploty;

                    if (eat_delay && flippo==1 && follow_ghost_num==num_ghost && do_mid)
                    {
                        maze_plot[eat_delay_mazemovex][eat_delay_mazemovey]=eat_delay_mazemove_blokje;
                        maze_plot[eat_delay_next_plotx][eat_delay_next_ploty]=eat_delay_next_plot_blokje;
                        adapt(eat_delay_mazemovex,eat_delay_mazemovey);
                        adapt(eat_delay_next_plotx,eat_delay_next_ploty);
                        eat_delay=0;
                    }
//                    check[num_ghost]=1;
                    mazemovex=(-pos_ghostx_num_ghost+1920-32+maxpixelsx)/64;
                    mazemovey=(-pos_ghosty_num_ghost+1080   +maxpixelsy)/72;
                    mazemovex=(mazemovex+addx)%modx;
                    mazemovey=(mazemovey+addy)%mody;

//                    if (rand()%10000==0) {best_ghost_num=-1; fbest_distance=0;}
                    int blokje;
                    blokje=maze_plot[mazemovex][mazemovey];
                    flip=0;
                    float fnew_distance;
                    if (do_mid)
                    {
                        check_num_ghost=check_num_ghost|1;
                        if (blokje&15!=0)
                        {
                            fnew_distance=sqrt(mazemovex*mazemovex+mazemovey*mazemovey);
                            if (fnew_distance>fbest_distance && best_ghost_num!=num_ghost)
                            {
                                fbest_distance=fnew_distance;
                                best_ghost_num=num_ghost;
                            }

                        }

                        int endpoint;
                        endpoint=0;

                        if (flippo==1)
                        {
                            if (num_ghost==follow_ghost_num)
                            {
                                if ((mazemovex==(hoog-1-59+maze_plotsizex)%maze_plotsizex)   && (mazemovey==(breed-1-30+maze_plotsizey)%maze_plotsizey))
                                {
                                    if (loaded==0)
                                        next=1;
                                    else
                                        nextlevel=1;
                                }
                            }
                        }
                        if (eatmode==2 || (eatmode==1 && num_ghost==follow_ghost_num && flippo)) //hoihoi
                            if ( ((mazemovex==(hoog-1-59+maze_plotsizex)%maze_plotsizex)   && (mazemovey==(breed-1-30+maze_plotsizey)%maze_plotsizey))    && (blokje==1 || blokje==4 || blokje==17 || blokje==20) )
                                endpoint=1;
                        if (eatmode==2 || (eatmode==1 && num_ghost==follow_ghost_num && flippo)) //hoihoi
                            if (mazemovex==(0-59+maze_plotsizex)%maze_plotsizex && mazemovey==(0-30+maze_plotsizey)%maze_plotsizey )
                                endpoint=1;
                        if (    !(flippo==1 && number==1) &&
//                                !(abs(verschilx)<300 && abs(verschily)<300 && flippo==1 && follow_ghost_num!=num_ghost) &&
                                (((blokje&128)==128 && (eatmode==2 || (eatmode==1 && num_ghost==follow_ghost_num && flippo))) || ((blokje&15)==0) || endpoint==1) //hoihoi
                           )
                        {
                            if ((flippo==1 && num_ghost==follow_ghost_num) && !endpoint==1)
                            {
                                fpos_ghostx_num_ghost=-1920-32+960+64*59;
                                fpos_ghosty_num_ghost=-1080-36+540+72*30;
                                pos_ghostx_num_ghost=fpos_ghostx_num_ghost;
                                pos_ghosty_num_ghost=fpos_ghosty_num_ghost;

                                if ((maze_plot[(-59+maze_plotsizex)%maze_plotsizex][(-30+maze_plotsizey)%maze_plotsizey]&2)==2)
                                {
                                    fspeed_ghosty_num_ghost=fabs(fspeed_ghostx_num_ghost+fspeed_ghosty_num_ghost);
                                    fspeed_ghostx_num_ghost=0;
                                }
                                else
                                {
                                    fspeed_ghostx_num_ghost=fabs(fspeed_ghostx_num_ghost+fspeed_ghosty_num_ghost);
                                    fspeed_ghosty_num_ghost=0;
                                }
                                if (follow_ghost_num==num_ghost)
                                {
                                    long_jump=1;
                                }
                            }

                            if (  (mazemovex==(hoog-1-59+maze_plotsizex)%maze_plotsizex) && (mazemovey==(breed-1-30+maze_plotsizey)%maze_plotsizey)  && force_game==0    )
                            {
                                if (number>1)
                                {
                                    pos_ghostx_num_ghost=pos_ghostx[number-1];
                                    pos_ghosty_num_ghost=pos_ghosty[number-1];
                                    fpos_ghostx_num_ghost=fpos_ghostx[number-1];
                                    fpos_ghosty_num_ghost=fpos_ghosty[number-1];
                                    fspeed_ghostx_num_ghost=fspeed_ghostx[number-1];
                                    fspeed_ghosty_num_ghost=fspeed_ghosty[number-1];
                                    number--;

                                    //                                if (best_ghost_num==num_ghost) {best_ghost_num=-1;fbest_distance=0.0;}
                                    if (follow_ghost==1)
                                    {
                                        if (follow_ghost_num>=number)
                                        {
                                            if (number>0)
                                            {
                                                follow_ghost_num=num_ghost;
                                                long_jump=1;
                                                //    printf("4\n");
                                            }
                                            else
                                            {
                                                follow_ghost=0;
                                                //    printf("5\n");
                                                long_jump=1;
                                                set_pacman();
                                            }
                                        }
                                        else if (follow_ghost_num==num_ghost)
                                        {
                                            long_jump=1;
                                        }
                                    }
                                }
                                else
                                {
                                    number=0;
                                    follow_ghost=0;
                                    set_pacman();
                                    //pospos
                                    posx=posx-posx%64-32;
//pospos
                                    if (posx<-1920)
//                                    if (posx<=-1920)
                                    {
                                        posx=posx+1920;
                                        picturex=(picturex-1+totalpicturex)%totalpicturex;
                                    }
                                    posy=posy-(posy-36)%72-36;
                                    if (posy<-1080)
//                                    if (posy<=-1080)
                                    {
                                        posy=posy+1080;
                                        picturey=(picturey-1+totalpicturey)%totalpicturey;
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
                                    //    printf("6\n");
                                    long_jump=1;
                                    pen=old_pen;
                                    pen_mode=old_pen_mode;
                                }
                            }
                            else if (eatmode==2 || (eatmode==1 && num_ghost==follow_ghost_num && flippo)) //hoihoi
                            {
//                              if (!(number==1 && flippo==1 && num_ghost==follow_ghost_num))
//!!!!!!
                                if (number<=2 || best_ghost_num==-1 || ((rand()*10)%10)<5 && !(mazemovex==(-59+maze_plotsizex)%maze_plotsizex && mazemovey==(-30+maze_plotsizey)%maze_plotsizey)
                                        || (flippo==1 && num_ghost==follow_ghost_num) )
                                {
                                    fpos_ghostx_num_ghost=-1920-32+960+64*59;
                                    fpos_ghosty_num_ghost=-1080-36+540+72*30;
                                    pos_ghostx_num_ghost=fpos_ghostx_num_ghost;
                                    pos_ghosty_num_ghost=fpos_ghosty_num_ghost;

                                    if ((maze_plot[(-59+maze_plotsizex)%maze_plotsizex][(-30+maze_plotsizey)%maze_plotsizey]&2)==2)
                                    {
                                        fspeed_ghosty_num_ghost=fabs(fspeed_ghostx_num_ghost+fspeed_ghosty_num_ghost);
                                        fspeed_ghostx_num_ghost=0;
                                    }
                                    else
                                    {
                                        fspeed_ghostx_num_ghost=fabs(fspeed_ghostx_num_ghost+fspeed_ghosty_num_ghost);
                                        fspeed_ghosty_num_ghost=0;
                                    }
                                    if (follow_ghost_num==num_ghost)
                                    {
                                        long_jump=1;
                                    }
                                }
                                else
                                {
                                    int rand_ghost=0;
//!!!!!!!!!!!!
                                    if (rand()%10<=10 || (flippo==1 && best_ghost_num==follow_ghost_num))
                                    {
                                        rand_ghost=(rand()*rand())%number;
                                        if (number>10)
                                        {
                                            while ( (rand_ghost%4)!=(num_ghost%4) || rand_ghost==num_ghost || (flippo==1 && rand_ghost==follow_ghost_num))
                                                rand_ghost=(rand()*rand())%number;
                                        }
                                    }
                                    else
                                        rand_ghost=best_ghost_num;
                                    pos_ghostx_num_ghost=pos_ghostx[rand_ghost];
                                    pos_ghosty_num_ghost=pos_ghosty[rand_ghost];
                                    fpos_ghostx_num_ghost=fpos_ghostx[rand_ghost];
                                    fpos_ghosty_num_ghost=fpos_ghosty[rand_ghost];
                                    if      (fspeed_ghostx[rand_ghost]>0)
                                    {
                                        fspeed_ghostx_num_ghost=fabs(fspeed_ghostx_num_ghost+fspeed_ghosty_num_ghost);
                                        fspeed_ghosty_num_ghost=0;
                                    }
                                    else if (fspeed_ghostx[rand_ghost]<0)
                                    {
                                        fspeed_ghostx_num_ghost=-fabs(fspeed_ghostx_num_ghost+fspeed_ghosty_num_ghost);
                                        fspeed_ghosty_num_ghost=0;
                                    }
                                    else if (fspeed_ghosty[rand_ghost]>0)
                                    {
                                        fspeed_ghosty_num_ghost=fabs(fspeed_ghostx_num_ghost+fspeed_ghosty_num_ghost);
                                        fspeed_ghostx_num_ghost=0;
                                    }
                                    else if (fspeed_ghosty[rand_ghost]<0)
                                    {
                                        fspeed_ghosty_num_ghost=-fabs(fspeed_ghostx_num_ghost+fspeed_ghosty_num_ghost);
                                        fspeed_ghostx_num_ghost=0;
                                    }
                                    if (best_ghost_num==num_ghost)
                                    {
                                        best_ghost_num=-1;
                                        fbest_distance=0.0;
                                    }
                                }
                            }
                            else
                            {
                                int new_mazemovex=(rand()*rand())%modx;
                                int new_mazemovey=(rand()*rand())%mody;
                                pos_ghostx_num_ghost=-new_mazemovex*64+1920-32;
                                pos_ghosty_num_ghost=-new_mazemovey*72+1080;
                                fpos_ghostx_num_ghost=pos_ghostx_num_ghost;
                                fpos_ghosty_num_ghost=pos_ghosty_num_ghost;
                            }
                            check_num_ghost=(check_num_ghost>>1)<<1;
                            //                        check[num_ghost]=0;
                            flip=1;
                        }
                    }

                    int n;
                    n=0;
                    int opt[4];
                    dir_up=0;
                    dir_down=0;
                    dir_left=0;
                    dir_right=0;
                    dir_mid=0;
                    if (do_also && flip==0)
                    {
                        if (flippo==1 && follow_ghost_num==num_ghost)
                        {
                            int xdraw_up,ydraw_up,xdraw_down,ydraw_down,xdraw_left,ydraw_left,xdraw_right,ydraw_right,xdraw_mid,ydraw_mid;
                            int mapx_up,mapy_up,mapx_down,mapy_down,mapx_left,mapy_left,mapx_right,mapy_right,mapx_mid,mapy_mid;
                            COLORREF color;
                            int start;
                            if (do_mid==1)
                                start=0;
                            else
                                start=4;
                            for (int i=start; i<5; i++)
                            {
                                int offx,offy;
                                if (i==0)
                                {
                                    offx=0;
                                    offy=-36;
                                }
                                else if (i==1)
                                {
                                    offx=0;
                                    offy=36;
                                }
                                else if (i==2)
                                {
                                    offx=-32;
                                    offy=0;
                                }
                                else if (i==3)
                                {
                                    offx=32;
                                    offy=0;
                                }
                                else if (i==4)
                                {
                                    offx=0;
                                    offy=0;
                                }
                                if ( (i==0 && (blokje&1)==1) ||
                                        (i==1 && (blokje&2)==2) ||
                                        (i==2 && (blokje&4)==4) ||
                                        (i==3 && (blokje&8)==8) ||
                                        (i==4 ) )
                                {

                                    xdraw=(-posx+960+offx+verschilx);
                                    if (xdraw>=1920)
                                    {
                                        xdraw=xdraw-1920;
                                        mapx=1;
                                    }
                                    else
                                        mapx=0;
                                    ydraw=(-y+540+offy);
                                    ydraw=(-posy+540+offy+verschily);
                                    if (ydraw>=1080)
                                    {
                                        ydraw=ydraw-1080;
                                        mapy=1;
                                    }
                                    else
                                        mapy=0;

                                    int arx=(picturex+mapx)%(maxpicturex+1);
                                    int ary=(picturey+mapy)%(maxpicturey+1);
                                    sprite_point.setTexture(texturemaxinmempoint[used2[arx][ary]]->getTexture(),false);
                                    sprite_point.setTextureRect(   { xdraw, ydraw,1, 1 }  );
                                    sprite_point.setPosition(0,0);
                                    texture_point.draw(sprite_point);
                                    texture_point.display();
                                    image_point=texture_point.getTexture().copyToImage();
                                    pixel_color=image_point.getPixel(0,0);
                                    int trans=(pixel_color.toInteger())&255;
                                    color=(pixel_color.toInteger())>>8;

                                    if (i==4)
                                    {
                                        if (color==16773632 && trans!=0)
                                        {
//                                            printf("right\n");
                                            xdraw_mid=xdraw;
                                            ydraw_mid=ydraw;
//                                            mapx_mid=arx;mapy_mid=ary;
//                                            RenderBlitg(arx,    ary,   xdraw+8,        ydraw+8,        2, 2, 8*64, 6*72);
                                            mapx_mid=mapx;
                                            mapy_mid=mapy;
//                                            RenderBlit(mapx,    mapy,   xdraw+8,        ydraw+8,        2, 2, 8*64, 6*72);
                                            dir_mid=1;
                                        }
                                        else
                                            dir_mid=0;
                                    }
                                    else if (i==0)
                                    {
                                        if (color==16773632 && trans!=0)
                                        {
//                                            printf("up\n");
                                            dir_up=1;
                                            xdraw_up=xdraw;
                                            ydraw_up=ydraw;
//                                            mapx_up=arx;mapy_up=ary;
//                                            RenderBlitg(arx,    ary,   xdraw+8,        ydraw+8,        2, 2, 8*64, 6*72);
                                            mapx_up=mapx;
                                            mapy_up=mapy;
//                                            RenderBlit(mapx,    mapy,   xdraw+8,        ydraw+8,        2, 2, 8*64, 6*72);
                                        }
                                        else
                                            dir_up=0;
                                    }
                                    else if (i==1)
                                    {
                                        if (color==16773632 && trans!=0)
                                        {
//                                            printf("down\n");
                                            dir_down=1;
                                            xdraw_down=xdraw;
                                            ydraw_down=ydraw;
//                                            mapx_down=arx;mapy_down=ary;
//                                            RenderBlitg(arx,    ary,   xdraw+8,        ydraw+8,        2, 2, 8*64, 6*72);
                                            mapx_down=mapx;
                                            mapy_down=mapy;
//                                            RenderBlit(mapx,    mapy,   xdraw+8,        ydraw+8,        2, 2, 8*64, 6*72);
                                        }
                                        else
                                            dir_down=0;
                                    }
                                    else if (i==2)
                                    {
                                        if (color==16773632 && trans!=0)
                                        {
//                                            printf("left\n");
                                            xdraw_left=xdraw;
                                            ydraw_left=ydraw;
//                                            mapx_left=arx;mapy_left=ary;
//                                            RenderBlitg(arx,    ary,   xdraw+8,        ydraw+8,        2, 2, 8*64, 6*72);
                                            mapx_left=mapx;
                                            mapy_left=mapy;
//                                            RenderBlit(mapx,    mapy,   xdraw+8,        ydraw+8,        2, 2, 8*64, 6*72);
                                            dir_left=1;
                                        }
                                        else
                                            dir_left=0;
                                    }
                                    else if (i==3)
                                    {
                                        if (color==16773632 && trans!=0)
                                        {
//                                            printf("right\n");
                                            xdraw_right=xdraw;
                                            ydraw_right=ydraw;
//                                            mapx_right=arx;mapy_right=ary;
//                                            RenderBlitg(arx,    ary,   xdraw+8,        ydraw+8,        2, 2, 8*64, 6*72);
                                            mapx_right=mapx;
                                            mapy_right=mapy;
//                                            RenderBlit(mapx,    mapy,   xdraw+8,        ydraw+8,        2, 2, 8*64, 6*72);
                                            dir_right=1;
                                        }
                                        else
                                            dir_right=0;
                                    }
                                }
                            }
                            if (dir_mid==1)
                            {
                                int go_on;
                                go_on=0;
                                if ((blokje&15)==0)
                                    go_on=0;
                                else if ( (blokje&(32+64))>0 )
                                {
                                    if (fspeed_ghostx_num_ghost!=0 && (blokje&32)==32 || ((pos_ghostx_num_ghost-32)%64!=0))
                                        go_on=1;
                                    else if (fspeed_ghosty_num_ghost!=0 && (blokje&64)==64 || ((pos_ghosty_num_ghost)%72!=0) )
                                        go_on=1;
                                }
                                else
                                    go_on=1;

                                static int last_posx;
                                static int last_posy;
                                last_posx=pos_ghostx_num_ghost;
                                last_posy=pos_ghosty_num_ghost;

                                if (go_on==1)
                                {
                                    total_points--;
                                    local_points++;
                                    if (fhapper==0)
                                    {
                                        soundloop=soundloop|1;
                                        playsound=playsound|1;
                                    }
                                    fhapper=40.0/fspeed_adjust;

                                    if ((blokje&16)==16 && ((pos_ghostx_num_ghost-32)%64==0) && ( (pos_ghosty_num_ghost)%72==0))
                                    {
//                                        if ((xdraw_mid-9)<0)    RenderBlitg(0,           mapy_mid,   1920+xdraw_mid-9,   ydraw_mid-8,        18, 16, 0, 5*72);
//                                        if ((ydraw_mid-8)<0)    RenderBlitg(mapx_mid,    0,          xdraw_mid-9,        1080+ydraw_mid-8,   18, 16, 0, 5*72);
//                                        RenderBlitg(mapx_mid,    mapy_mid,   xdraw_mid-9,        ydraw_mid-8,        18, 16, 0, 5*72);
                                        if ((xdraw_mid-9)<0)
                                            RenderBlit(0,           mapy_mid,   1920+xdraw_mid-9,   ydraw_mid-8,        18, 16, 0, 5*72);
                                        if ((ydraw_mid-8)<0)
                                            RenderBlit(mapx_mid,    0,          xdraw_mid-9,        1080+ydraw_mid-8,   18, 16, 0, 5*72);
                                        RenderBlit(mapx_mid,    mapy_mid,   xdraw_mid-9,        ydraw_mid-8,        18, 16, 0, 5*72);
                                    }
                                    else
                                    {
//                                        if ((xdraw_mid-7)<0)    RenderBlitg(0,           mapy_mid,   1920+xdraw_mid-7,   ydraw_mid-6,        14, 12, 0, 5*72);
//                                        if ((ydraw_mid-6)<0)    RenderBlitg(mapx_mid,    0,          xdraw_mid-7,        1080+ydraw_mid-6,   14, 12, 0, 5*72);
//                                        RenderBlitg(mapx_mid,    mapy_mid,   xdraw_mid-7,        ydraw_mid-6,        14, 12, 0, 5*72);
                                        if ((xdraw_mid-7)<0)
                                            RenderBlit(0,           mapy_mid,   1920+xdraw_mid-7,   ydraw_mid-6,        14, 12, 0, 5*72);
                                        if ((ydraw_mid-6)<0)
                                            RenderBlit(mapx_mid,    0,          xdraw_mid-7,        1080+ydraw_mid-6,   14, 12, 0, 5*72);
                                        RenderBlit(mapx_mid,    mapy_mid,   xdraw_mid-7,        ydraw_mid-6,        14, 12, 0, 5*72);
                                    }

//!!!!!!!!!!!!!!!
                                    if (do_mid && force_game==1)
                                    {
                                        if ((maze_plot[mazemovex][mazemovey]&16)==16)
                                        {
                                            if (hunt==1||hunt==2)
                                            {
                                                hunt=1;
                                                hunt_max=800-(difficulty-2)*150;
                                                if (hunt_counter!=800-(difficulty-2)*150)
                                                    hunt_counter=799-(difficulty-2)*150;
                                            }
                                            else
                                            {
                                                hunt=1;
                                                hunt_max=800-(difficulty-2)*150;
                                                hunt_counter=800-(difficulty-2)*150;
                                            }
                                            playsound=playsound|2;
                                        }
                                    }
                                    if (mazetype==1 && breed!=0)
                                    {
                                        if ((mazemovex==(hoog-1-59+maze_plotsizex)%maze_plotsizex) && ( mazemovey==(breed-1-30+maze_plotsizey)%maze_plotsizey )   )
                                        {
                                            if (connected==1)
                                            {
                                                SEED=time(0);
                                                sprintf(writer,"T=MAZE,BIGLARGE=%d,SEED=%d,LEVEL=%d,\0",big_large,SEED,level);
                                                SEND(writer);
                                            }
                                            if (loaded==0)
                                                next=1;
                                            else
                                                nextlevel=1;
                                        }
                                    }
                                }
                                else
                                {
                                    if (last_posx!=pos_ghostx_num_ghost || last_posy!=pos_ghosty_num_ghost)
                                    {
                                        if (fhapper>0.0)
                                        {
                                            fhapper=1.0;
                                        }
                                    }
                                }
                                last_posx=pos_ghostx_num_ghost;
                                last_posy=pos_ghosty_num_ghost;
                            }
                        }
                    }

                    if (do_mid==1 && flip==0 && (blokje&(32+64))==0 )
                    {
                        if (dir_up==1)
                        {
                            opt[n]=1;
                            n++;
                        }
                        if (dir_down==1)
                        {
                            opt[n]=2;
                            n++;
                        }
                        if (dir_left==1)
                        {
                            opt[n]=4;
                            n++;
                        }
                        if (dir_right==1)
                        {
                            opt[n]=8;
                            n++;
                        }
                        if (n>0)
                        {
                            int choice=opt[rand()%n];
                            if (choice==1)
                            {
//                                    RenderBlit(mapx_up,    mapy_up,   xdraw_up-8,        ydraw_up-8,        2, 2, 0, 6*72);
                                fspeed_ghosty_num_ghost=-(fabs(fspeed_ghostx_num_ghost)+fabs(fspeed_ghosty_num_ghost));
                                fspeed_ghostx_num_ghost=0;
                            }
                            else if (choice==2)
                            {
//                                    RenderBlit(mapx_down,    mapy_down,   xdraw_down-8,        ydraw_down-8,        2, 2, 0, 6*72);
                                fspeed_ghosty_num_ghost=(fabs(fspeed_ghostx_num_ghost)+fabs(fspeed_ghosty_num_ghost));
                                fspeed_ghostx_num_ghost=0;
                            }
                            else if (choice==4)
                            {
//                                    RenderBlit(mapx_left,    mapy_left,   xdraw_left-8,        ydraw_left-8,        2, 2, 0, 6*72);
                                fspeed_ghostx_num_ghost=-(fabs(fspeed_ghostx_num_ghost)+fabs(fspeed_ghosty_num_ghost));
                                fspeed_ghosty_num_ghost=0;
                            }
                            else if (choice==8)
                            {
//                                    RenderBlit(mapx_right,    mapy_right,   xdraw_right-8,        ydraw_right-8,        2, 2, 0, 6*72);
                                fspeed_ghostx_num_ghost=(fabs(fspeed_ghostx_num_ghost)+fabs(fspeed_ghosty_num_ghost));
                                fspeed_ghosty_num_ghost=0;
                            }
                        }
                        if (n==0)
                        {
                            if (fspeed_ghostx_num_ghost<0)
                            {
                                if ( (blokje & 4) == 0 )
                                {
                                    if ( ((blokje & 1)==0) && ((blokje & 2)==2) )
                                    {
                                        fspeed_ghosty_num_ghost=-fspeed_ghostx_num_ghost;
                                        fspeed_ghostx_num_ghost=0;
                                    }
                                    else if ( ((blokje & 1)==1) && ((blokje & 2)==0) )
                                    {
                                        fspeed_ghosty_num_ghost=fspeed_ghostx_num_ghost;
                                        fspeed_ghostx_num_ghost=0;
                                    }
                                    else if ( ((blokje & 1)==1) && ((blokje & 2)==2) )
                                    {
                                        if (verschily==0)
                                        {
                                            if ( (rand()%2)==0 )
                                                fspeed_ghosty_num_ghost=fspeed_ghostx_num_ghost;
                                            else
                                                fspeed_ghosty_num_ghost=-fspeed_ghostx_num_ghost;
                                        }
                                        else if (verschily>0)
                                            fspeed_ghosty_num_ghost=fspeed_ghostx_num_ghost;
                                        else
                                            fspeed_ghosty_num_ghost=-fspeed_ghostx_num_ghost;

                                        fspeed_ghostx_num_ghost=0;
                                    }
                                    else
                                    {
                                        if ( (blokje & 15)!=0 )
                                            fspeed_ghostx_num_ghost=-fspeed_ghostx_num_ghost;
                                    }
                                }
                                else if ( ((blokje & 1)==1) && verschily>=0 && ( abs(verschily)-abs(verschilx) >0  )  && ( (rand()%(2+loaded))>0 || verschilx==0  ) && (rand()%(2+loaded))>0  )
                                {
                                    fspeed_ghosty_num_ghost=fspeed_ghostx_num_ghost;
                                    fspeed_ghostx_num_ghost=0;
                                }
                                else if ( ((blokje & 2)==2) && verschily<=0 && ( abs(verschily)-abs(verschilx) >0  )  && ( (rand()%(2+loaded))>0 || verschilx==0  ) && (rand()%(2+loaded))>0 )
                                {
                                    fspeed_ghosty_num_ghost=-fspeed_ghostx_num_ghost;
                                    fspeed_ghostx_num_ghost=0;
                                }
                                else if ( ((blokje & 1)==1) && ((blokje & 2)==0) && ( (rand()%(3+loaded))>0) && (verschily==0 || ((abs(verschilx)-abs(verschily))>0) ) && verschilx<=0 )
                                {
                                    fspeed_ghosty_num_ghost=fspeed_ghostx_num_ghost;
                                    fspeed_ghostx_num_ghost=0;
                                }
                                else if ( ((blokje & 2)==2) && ((blokje & 1)==0) && ( (rand()%(3+loaded))>0) && (verschily==0 || ((abs(verschilx)-abs(verschily))>0) ) && verschilx<=0 )
                                {
                                    fspeed_ghosty_num_ghost=-fspeed_ghostx_num_ghost;
                                    fspeed_ghostx_num_ghost=0;
                                }
                                else if ( ((blokje & 1)==1) && ((blokje & 2)==2) && ( (rand()%(3+loaded))>0) && (verschily==0 || ((abs(verschilx)-abs(verschily))>0)) && verschilx<=0 )
                                {
                                    if ( (rand()%2)==0)
                                        fspeed_ghosty_num_ghost=-fspeed_ghostx_num_ghost;
                                    else
                                        fspeed_ghosty_num_ghost=fspeed_ghostx_num_ghost;
                                    fspeed_ghostx_num_ghost=0;
                                }
                            }
                            else if (fspeed_ghostx_num_ghost>0)
                            {
                                if ( (blokje & 8) == 0 )
                                {
                                    if ( ((blokje & 1)==0) && ((blokje & 2)==2) )
                                    {
                                        fspeed_ghosty_num_ghost=fspeed_ghostx_num_ghost;
                                        fspeed_ghostx_num_ghost=0;
                                    }
                                    else if ( ((blokje & 1)==1) && ((blokje & 2)==0) )
                                    {
                                        fspeed_ghosty_num_ghost=-fspeed_ghostx_num_ghost;
                                        fspeed_ghostx_num_ghost=0;
                                    }
                                    else if ( ((blokje & 1)==1) && ((blokje & 2)==2) )
                                    {
                                        if (verschily==0)
                                        {
                                            if ( (rand()%2)==0 )
                                                fspeed_ghosty_num_ghost=fspeed_ghostx_num_ghost;
                                            else
                                                fspeed_ghosty_num_ghost=-fspeed_ghostx_num_ghost;
                                        }
                                        else if (verschily<0)
                                            fspeed_ghosty_num_ghost=fspeed_ghostx_num_ghost;
                                        else
                                            fspeed_ghosty_num_ghost=-fspeed_ghostx_num_ghost;
                                        fspeed_ghostx_num_ghost=0;
                                    }
                                    else
                                    {
                                        if ( (blokje & 15)!=0 )
                                            fspeed_ghostx_num_ghost=-fspeed_ghostx_num_ghost;
                                    }
                                }
                                else if ( ((blokje & 1)==1) && verschily>=0  && ( abs(verschily)-abs(verschilx) >0  )  && ( (rand()%(2+loaded))>0 || verschilx==0  ) && (rand()%(2+loaded))>0  )
                                {
                                    fspeed_ghosty_num_ghost=-fspeed_ghostx_num_ghost;
                                    fspeed_ghostx_num_ghost=0;
                                }
                                else if ( ((blokje & 2)==2) && verschily<=0  && ( abs(verschily)-abs(verschilx) >0  )  && ( (rand()%(2+loaded))>0 || verschilx==0  ) && (rand()%(2+loaded))>0  )
                                {
                                    fspeed_ghosty_num_ghost=fspeed_ghostx_num_ghost;
                                    fspeed_ghostx_num_ghost=0;
                                }
                                else if ( ((blokje & 1)==1) && ((blokje & 2)==0) && ( (rand()%(3+loaded))>0) && (verschily==0 || ((abs(verschilx)-abs(verschily))>0) ) && verschilx>=0 )
                                {
                                    fspeed_ghosty_num_ghost=-fspeed_ghostx_num_ghost;
                                    fspeed_ghostx_num_ghost=0;
                                }
                                else if ( ((blokje & 2)==2) && ((blokje & 1)==0) && ( (rand()%(3+loaded))>0) && (verschily==0 || ((abs(verschilx)-abs(verschily))>0) ) && verschilx>=0 )
                                {
                                    fspeed_ghosty_num_ghost=fspeed_ghostx_num_ghost;
                                    fspeed_ghostx_num_ghost=0;
                                }
                                else if ( ((blokje & 1)==1) && ((blokje & 2)==2) && ( (rand()%(3+loaded))>0) && (verschily==0 || ((abs(verschilx)-abs(verschily))>0) ) && verschilx>=0 )
                                {
                                    if ( (rand()%2)==0)
                                        fspeed_ghosty_num_ghost=-fspeed_ghostx_num_ghost;
                                    else
                                        fspeed_ghosty_num_ghost=fspeed_ghostx_num_ghost;
                                    fspeed_ghostx_num_ghost=0;
                                }
                            }
                            else if (fspeed_ghosty_num_ghost<0)
                            {
                                if ( (blokje & 1) == 0 )
                                {
                                    if ( ((blokje & 4)==0) && ((blokje & 8)==8) )
                                    {
                                        fspeed_ghostx_num_ghost=-fspeed_ghosty_num_ghost;
                                        fspeed_ghosty_num_ghost=0;
                                    }
                                    else if ( ((blokje & 4)==4) && ((blokje & 8)==0) )
                                    {
                                        fspeed_ghostx_num_ghost=fspeed_ghosty_num_ghost;
                                        fspeed_ghosty_num_ghost=0;
                                    }
                                    else if ( ((blokje & 4)==4) && ((blokje & 8)==8) )
                                    {
                                        if (verschilx==0)
                                        {
                                            if ( (rand()%2)==0 )
                                                fspeed_ghostx_num_ghost=fspeed_ghosty_num_ghost;
                                            else
                                                fspeed_ghostx_num_ghost=-fspeed_ghosty_num_ghost;
                                        }
                                        else if (verschilx>0)
                                            fspeed_ghostx_num_ghost=fspeed_ghosty_num_ghost;
                                        else
                                            fspeed_ghostx_num_ghost=-fspeed_ghosty_num_ghost;
                                        fspeed_ghosty_num_ghost=0;
                                    }
                                    else
                                    {
                                        if ( (blokje & 15)!=0 )
                                            fspeed_ghosty_num_ghost=-fspeed_ghosty_num_ghost;
                                    }
                                }
                                else if ( ((blokje & 4)==4) && verschilx>=0  && ( abs(verschilx)-abs(verschily) >0  )  && ( (rand()%(2+loaded))>0 || verschily==0 ) && (rand()%(2+loaded))>0  )
                                {
                                    fspeed_ghostx_num_ghost=fspeed_ghosty_num_ghost;
                                    fspeed_ghosty_num_ghost=0;
                                }
                                else if ( ((blokje & 8)==8) && verschilx<=0  && ( abs(verschilx)-abs(verschily) >0  )  && ( (rand()%(2+loaded))>0 || verschily==0  ) && (rand()%(2+loaded))>0  )
                                {
                                    fspeed_ghostx_num_ghost=-fspeed_ghosty_num_ghost;
                                    fspeed_ghosty_num_ghost=0;
                                }
                                else if ( ((blokje & 4)==4) && ((blokje & 8)==0) && ( (rand()%(3+loaded))>0) && (verschilx==0 || ((abs(verschily)-abs(verschilx))>0) ) && verschily<=0 )
                                {
                                    fspeed_ghostx_num_ghost=fspeed_ghosty_num_ghost;
                                    fspeed_ghosty_num_ghost=0;
                                }
                                else if ( ((blokje & 8)==8) && ((blokje & 4)==0) && ( (rand()%(3+loaded))>0) && (verschilx==0 || ((abs(verschily)-abs(verschilx))>0) ) && verschily<=0 )
                                {
                                    fspeed_ghostx_num_ghost=-fspeed_ghosty_num_ghost;
                                    fspeed_ghosty_num_ghost=0;
                                }
                                else if ( ((blokje & 4)==4) && ((blokje & 8)==8) && ( (rand()%(3+loaded))>0) && (verschilx==0 || ((abs(verschily)-abs(verschilx))>0) ) && verschily<=0 )
                                {
                                    if ( (rand()%2)==0)
                                        fspeed_ghostx_num_ghost=-fspeed_ghosty_num_ghost;
                                    else
                                        fspeed_ghostx_num_ghost=fspeed_ghosty_num_ghost;
                                    fspeed_ghosty_num_ghost=0;
                                }
                            }
                            else if (fspeed_ghosty_num_ghost>0)
                            {
                                if ( (blokje & 2) == 0 )
                                {
                                    if ( ((blokje & 4)==0) && ((blokje & 8)==8) )
                                    {
                                        fspeed_ghostx_num_ghost=fspeed_ghosty_num_ghost;
                                        fspeed_ghosty_num_ghost=0;
                                    }
                                    else if ( ((blokje & 4)==4) && ((blokje & 8)==0) )
                                    {
                                        fspeed_ghostx_num_ghost=-fspeed_ghosty_num_ghost;
                                        fspeed_ghosty_num_ghost=0;
                                    }
                                    else if ( ((blokje & 4)==4) && ((blokje & 8)==8) )
                                    {
                                        if (verschilx==0)
                                        {
                                            if ( (rand()%2)==0 )
                                                fspeed_ghostx_num_ghost=fspeed_ghosty_num_ghost;
                                            else
                                                fspeed_ghostx_num_ghost=-fspeed_ghosty_num_ghost;
                                        }
                                        else if (verschilx<0)
                                            fspeed_ghostx_num_ghost=fspeed_ghosty_num_ghost;
                                        else
                                            fspeed_ghostx_num_ghost=-fspeed_ghosty_num_ghost;
                                        fspeed_ghosty_num_ghost=0;
                                    }
                                    else
                                    {
                                        if ( (blokje & 15)!=0 )
                                            fspeed_ghosty_num_ghost=-fspeed_ghosty_num_ghost;
                                    }
                                }
                                else if ( ((blokje & 4)==4) && verschilx>=0  && ( abs(verschilx)-abs(verschily) >0  )  && ( (rand()%(2+loaded))>0 || verschily==0  ) && (rand()%(2+loaded))>0 )
                                {
                                    fspeed_ghostx_num_ghost=-fspeed_ghosty_num_ghost;
                                    fspeed_ghosty_num_ghost=0;
                                }
                                else if ( ((blokje & 8)==8) && verschilx<=0  && ( abs(verschilx)-abs(verschily) >0  )  && ( (rand()%(2+loaded))>0 || verschily==0  )  && (rand()%(2+loaded))>0 )
                                {
                                    fspeed_ghostx_num_ghost=fspeed_ghosty_num_ghost;
                                    fspeed_ghosty_num_ghost=0;
                                }
                                else if ( ((blokje & 4)==4) && ((blokje & 8)==0) && ( (rand()%(3+loaded))>0) && (verschilx==0 || ((abs(verschily)-abs(verschilx))>0) ) && verschily>=0 )
                                {
                                    fspeed_ghostx_num_ghost=-fspeed_ghosty_num_ghost;
                                    fspeed_ghosty_num_ghost=0;
                                }
                                else if ( ((blokje & 8)==8) && ((blokje & 4)==0) && ( (rand()%(3+loaded))>0) && (verschilx==0 || ((abs(verschily)-abs(verschilx))>0) ) && verschily>=0 )
                                {
                                    fspeed_ghostx_num_ghost=fspeed_ghosty_num_ghost;
                                    fspeed_ghosty_num_ghost=0;
                                }
                                else if ( ((blokje & 4)==4) && ((blokje & 8)==8) && ( (rand()%(3+loaded))>0) && (verschilx==0 || ((abs(verschily)-abs(verschilx))>0) ) && verschily>=0 )
                                {
                                    if ( (rand()%2)==0)
                                        fspeed_ghostx_num_ghost=-fspeed_ghosty_num_ghost;
                                    else
                                        fspeed_ghostx_num_ghost=fspeed_ghosty_num_ghost;
                                    fspeed_ghosty_num_ghost=0;
                                }
                            }
                        }
                    }
//!!!!!!!!!!
                    int protect=!(abs(verschilx)<300 && abs(verschily)<300 && flippo==1 && follow_ghost_num!=num_ghost);
//hoihoi
                    if (protect && do_mid && (eatmode==2 || (eatmode==1 && num_ghost==follow_ghost_num && flippo)) && flip==0 && (blokje&128)==0 && ((blokje&15)==1 || (blokje&15)==2 || (blokje&15)==4 || (blokje&15)==8))
//                    if (flip==0)
//                    if ((blokje&128)==0)
//                    if ((blokje&15)==1 || (blokje&15)==2 || (blokje&15)==4 || (blokje&15)==8)
//                    if (
//                        !( ( mazemovex==(hoog-1-59+maze_plotsizex)%maze_plotsizex ) && ( mazemovey==(breed-1-30+maze_plotsizey)%maze_plotsizey))
//                     && !( ( mazemovex==(0-59+maze_plotsizex)%maze_plotsizex)       && ( mazemovey==(0-30+maze_plotsizey)%maze_plotsizey))
//                    )
                    {
                        if ( (blokje & 8)==0 && (blokje & 1)==0 && (blokje & 2)==0 || ((blokje & (32+64))>0 && (blokje & 8)==0) )
                        {
                            next_plotx=(mazemovex-1+modx)%modx;
                            next_ploty=mazemovey;
                            if (  !( (mazemovex==(hoog-1-59+maze_plotsizex)%maze_plotsizex) && (mazemovey==(breed-1-30+maze_plotsizey)%maze_plotsizey)  )  &&
                                    !( (mazemovex==(0-59+maze_plotsizex)%maze_plotsizex) && ( mazemovey==(0-30+maze_plotsizey)%maze_plotsizey) )   )
                            {
                                if (flippo==1 && num_ghost==follow_ghost_num)
                                {
                                    eat_delay=1;
                                    eat_delay_mazemovex=mazemovex;
                                    eat_delay_mazemovey=mazemovey;
                                    eat_delay_mazemove_blokje=maze_plot[mazemovex][mazemovey]&(15-4);
                                    eat_delay_next_plot_blokje=maze_plot[next_plotx][next_ploty]&(128+32+64+15-8);
                                    eat_delay_next_plotx=next_plotx;
                                    eat_delay_next_ploty=next_ploty;
                                }
                                else if (flippo==1 && num_ghost!=follow_ghost_num)
                                {
                                    if (!(eat_delay_mazemovex2==mazemovex && eat_delay_mazemovey2==mazemovey) &&
                                            !(eat_delay_mazemovex2==next_plotx && eat_delay_mazemovey2==next_ploty) )
                                        ;
                                    {
                                        maze_plot[mazemovex][mazemovey]=maze_plot[mazemovex][mazemovey]&(15-4);
                                        maze_plot[next_plotx][next_ploty]=maze_plot[next_plotx][next_ploty]&(128+32+64+15-8);
                                        adapt(mazemovex,mazemovey);
                                        adapt(next_plotx,next_ploty);
                                    }
                                }
                                else
                                {
                                    maze_plot[mazemovex][mazemovey]=maze_plot[mazemovex][mazemovey]&(15-4);
                                    maze_plot[next_plotx][next_ploty]=maze_plot[next_plotx][next_ploty]&(128+32+64+15-8);
                                    adapt(mazemovex,mazemovey);
                                    adapt(next_plotx,next_ploty);
                                }
                            }
                        }
                        else if ( (blokje & 4)==0 && (blokje & 1)==0 && (blokje & 2)==0 || ((blokje & (32+64))>0 && (blokje & 4)==0))
                        {
                            next_plotx=(mazemovex+1)%modx;
                            next_ploty=mazemovey;
                            if (  !( (mazemovex==(hoog-1-59+maze_plotsizex)%maze_plotsizex) && (mazemovey==(breed-1-30+maze_plotsizey)%maze_plotsizey)  )  &&
                                    !( (mazemovex==(0-59+maze_plotsizex)%maze_plotsizex) && ( mazemovey==(0-30+maze_plotsizey)%maze_plotsizey) )   )
                            {
                                if (flippo==1 && num_ghost==follow_ghost_num)
                                {
                                    eat_delay=1;
                                    eat_delay_mazemovex=mazemovex;
                                    eat_delay_mazemovey=mazemovey;
                                    eat_delay_mazemove_blokje=maze_plot[mazemovex][mazemovey]&(15-8);
                                    eat_delay_next_plot_blokje=maze_plot[next_plotx][next_ploty]&(128+32+64+15-4);
                                    eat_delay_next_plotx=next_plotx;
                                    eat_delay_next_ploty=next_ploty;
                                }
                                else if (flippo==1 && num_ghost!=follow_ghost_num)
                                {
                                    if (!(eat_delay_mazemovex2==mazemovex && eat_delay_mazemovey2==mazemovey) &&
                                            !(eat_delay_mazemovex2==next_plotx && eat_delay_mazemovey2==next_ploty) )
                                        ;
                                    {
                                        maze_plot[mazemovex][mazemovey]=maze_plot[mazemovex][mazemovey]&(15-8);
                                        maze_plot[next_plotx][next_ploty]=maze_plot[next_plotx][next_ploty]&(128+32+64+15-4);
                                        adapt(mazemovex,mazemovey);
                                        adapt(next_plotx,next_ploty);
                                    }
                                }
                                else
                                {
                                    maze_plot[mazemovex][mazemovey]=maze_plot[mazemovex][mazemovey]&(15-8);
                                    maze_plot[next_plotx][next_ploty]=maze_plot[next_plotx][next_ploty]&(128+32+64+15-4);
                                    adapt(mazemovex,mazemovey);
                                    adapt(next_plotx,next_ploty);
                                }
                            }
                        }
                        else if ( (blokje & 2)==0 && (blokje & 4)==0 && (blokje & 8)==0 || ((blokje & (32+64))>0 && (blokje & 2)==0))
                        {
                            next_plotx=mazemovex;
                            next_ploty=(mazemovey-1+mody)%mody;
                            if (  !( (mazemovex==(hoog-1-59+maze_plotsizex)%maze_plotsizex) && (mazemovey==(breed-1-30+maze_plotsizey)%maze_plotsizey)  )  &&
                                    !( (mazemovex==(0-59+maze_plotsizex)%maze_plotsizex) && ( mazemovey==(0-30+maze_plotsizey)%maze_plotsizey) )   )
                            {
                                if (flippo==1 && num_ghost==follow_ghost_num)
                                {
                                    eat_delay=1;
                                    eat_delay_mazemovex=mazemovex;
                                    eat_delay_mazemovey=mazemovey;
                                    eat_delay_mazemove_blokje=maze_plot[mazemovex][mazemovey]&(15-1);
                                    eat_delay_next_plot_blokje=maze_plot[next_plotx][next_ploty]&(128+32+64+15-2);
                                    eat_delay_next_plotx=next_plotx;
                                    eat_delay_next_ploty=next_ploty;
                                }
                                else if (flippo==1 && num_ghost!=follow_ghost_num)
                                {
                                    if (!(eat_delay_mazemovex2==mazemovex && eat_delay_mazemovey2==mazemovey) &&
                                            !(eat_delay_mazemovex2==next_plotx && eat_delay_mazemovey2==next_ploty) )
                                        ;
                                    {
                                        maze_plot[mazemovex][mazemovey]=maze_plot[mazemovex][mazemovey]&(15-1);
                                        maze_plot[next_plotx][next_ploty]=maze_plot[next_plotx][next_ploty]&(128+32+64+15-2);
                                        adapt(mazemovex,mazemovey);
                                        adapt(next_plotx,next_ploty);
                                    }
                                }
                                else
                                {
                                    maze_plot[mazemovex][mazemovey]=maze_plot[mazemovex][mazemovey]&(15-1);
                                    maze_plot[next_plotx][next_ploty]=maze_plot[next_plotx][next_ploty]&(128+32+64+15-2);
                                    adapt(mazemovex,mazemovey);
                                    adapt(next_plotx,next_ploty);
                                }
                            }
                        }
                        else if ( (blokje & 1)==0 && (blokje & 4)==0 && (blokje & 8)==0 || ((blokje & (32+64))>0 && (blokje & 1)==0))
                        {
                            next_plotx=mazemovex;
                            next_ploty=(mazemovey+1)%mody;
                            if (  !( (mazemovex==(hoog-1-59+maze_plotsizex)%maze_plotsizex) && (mazemovey==(breed-1-30+maze_plotsizey)%maze_plotsizey)  )  &&
                                    !( (mazemovex==(0-59+maze_plotsizex)%maze_plotsizex) && ( mazemovey==(0-30+maze_plotsizey)%maze_plotsizey) )   )
                            {
                                if (flippo==1 && num_ghost==follow_ghost_num)
                                {
                                    eat_delay=1;
                                    eat_delay_mazemovex=mazemovex;
                                    eat_delay_mazemovey=mazemovey;
                                    eat_delay_mazemove_blokje=maze_plot[mazemovex][mazemovey]&(15-2);
                                    eat_delay_next_plot_blokje=maze_plot[next_plotx][next_ploty]&(128+64+32+15-1);
                                    eat_delay_next_plotx=next_plotx;
                                    eat_delay_next_ploty=next_ploty;
                                }
                                else if (flippo==1 && num_ghost!=follow_ghost_num)
                                {
                                    if (!(eat_delay_mazemovex2==mazemovex && eat_delay_mazemovey2==mazemovey) &&
                                            !(eat_delay_mazemovex2==next_plotx && eat_delay_mazemovey2==next_ploty) )
                                        ;
                                    {
                                        maze_plot[mazemovex][mazemovey]=maze_plot[mazemovex][mazemovey]&(15-2);
                                        maze_plot[next_plotx][next_ploty]=maze_plot[next_plotx][next_ploty]&(128+64+32+15-1);
                                        adapt(mazemovex,mazemovey);
                                        adapt(next_plotx,next_ploty);
                                    }
                                }
                                else
                                {
                                    maze_plot[mazemovex][mazemovey]=maze_plot[mazemovex][mazemovey]&(15-2);
                                    maze_plot[next_plotx][next_ploty]=maze_plot[next_plotx][next_ploty]&(128+64+32+15-1);
                                    adapt(mazemovex,mazemovey);
                                    adapt(next_plotx,next_ploty);
                                }
                            }
                        }
                    }
                }
                else
                {
                    check_num_ghost=(check_num_ghost>>1)<<1;
//                    check_num_ghost=0;
//                    check[num_ghost]=0;
                }

                if (flip==0)
                {
                    if (numloops>1 && loops<(numloops-1))
                    {
                        if (fspeed_ghostx_num_ghost<0.0)
                        {
                            pos_ghostx_num_ghost=pos_ghostx_num_ghost+1;
                            fpos_total--;
                        }
                        else if (fspeed_ghostx_num_ghost>0.0)
                        {
                            pos_ghostx_num_ghost=pos_ghostx_num_ghost-1;
                            fpos_total--;
                        }
                        else if (fspeed_ghosty_num_ghost<0.0)
                        {
                            pos_ghosty_num_ghost=pos_ghosty_num_ghost+1;
                            fpos_total--;
                        }
                        else if (fspeed_ghosty_num_ghost>0.0)
                        {
                            pos_ghosty_num_ghost=pos_ghosty_num_ghost-1;
                            fpos_total--;
                        }
                        if (fspeed_ghostx_num_ghost==0.0 && fspeed_ghosty_num_ghost==0.0)
                        {
                            fpos_total=0.0;
                            remain=0.0;
                        }
                    }
                    else
                    {
                        if (1 || pacman==1)
                        {
                            if (fspeed_ghostx_num_ghost==0.0)
                            {
                                fpos_ghostx_num_ghost=pos_ghostx_num_ghost;
                                if (fspeed_ghosty_num_ghost>0.0)
                                {
                                    fpos_ghosty_num_ghost=pos_ghosty_num_ghost-(fpos_total+remain);
                                }
                                else if (fspeed_ghosty_num_ghost<0.0)
                                {
                                    fpos_ghosty_num_ghost=pos_ghosty_num_ghost+(fpos_total-remain);
                                }
                                else
                                    fpos_ghosty_num_ghost=pos_ghosty_num_ghost;
                            }
                            else if (fspeed_ghosty_num_ghost==0.0)
                            {
                                fpos_ghosty_num_ghost=pos_ghosty_num_ghost;
                                if (fspeed_ghostx_num_ghost>0.0)
                                {
                                    fpos_ghostx_num_ghost=pos_ghostx_num_ghost-(fpos_total+remain);
                                }
                                else if (fspeed_ghostx_num_ghost<0.0)
                                {
                                    fpos_ghostx_num_ghost=pos_ghostx_num_ghost+(fpos_total-remain);
                                }
                                else
                                    fpos_ghostx_num_ghost=pos_ghostx_num_ghost;
                            }
                            pos_ghostx_num_ghost=fpos_ghostx_num_ghost;
                            pos_ghosty_num_ghost=fpos_ghosty_num_ghost;
                        }
                        else
                        {
                            fpos_ghostx_num_ghost=fpos_ghostx_num_ghost-fspeed_ghostx_num_ghost*fspeed_adjust;
                            fpos_ghosty_num_ghost=fpos_ghosty_num_ghost-fspeed_ghosty_num_ghost*fspeed_adjust;
                            pos_ghostx_num_ghost=fpos_ghostx_num_ghost;
                            pos_ghosty_num_ghost=fpos_ghosty_num_ghost;
                        }
                    }
                    /*
                                        if (numloops>1 && loops<(numloops-1))
                                        {
                                            fpos_ghostx_num_ghost=fpos_ghostx_num_ghost-fspeed_adjust*fspeed_ghostx_num_ghost/(numloops+0.1);
                                            fpos_ghosty_num_ghost=fpos_ghosty_num_ghost-fspeed_adjust*fspeed_ghosty_num_ghost/(numloops+0.1);
                                            pos_ghostx_num_ghost=fpos_ghostx_num_ghost;
                                            pos_ghosty_num_ghost=fpos_ghosty_num_ghost;
                                        }
                                        else
                                        {
                                            pos_ghostx_num_ghost=fpos_ghostx_num_ghost;
                                            pos_ghosty_num_ghost=fpos_ghosty_num_ghost;
                                        }
                    */
                }

                if ( (hunt!=0 || cheat==1) && !(flippo==1 && num_ghost==follow_ghost_num) )
                {
                    verschilx=-verschilx;
                    verschily=-verschily;
                }
                if (flip==1)
                    loops=numloops;
            }
            if (shade_map>=1)
            {
                flowx=sin(fpstime+num_ghost+sin(fpstime*1.2+num_ghost))*50  + sin(fpstime*1.4+num_ghost+sin(fpstime*1.5+num_ghost))*10;
                flowy=cos(fpstime*1.1+num_ghost+sin(fpstime*1.3+num_ghost))*50 + sin(fpstime*0.9+num_ghost+sin(fpstime*1.3+num_ghost))*10;
                offsetx=offsetx+flowx;
                offsety=offsety+flowy;
            }
            else
            {
                flowx=0;
                flowy=0;
            }
            int offsetx_store=offsetx;
            int offsety_store=offsety;

            int motion;
            static int motion_up_down[]= {0,1,0,3};

            if (fspeed_ghostx_num_ghost==0)
            {
                motion=(-pos_ghostx_num_ghost-pos_ghosty_num_ghost)*2.5/32;
                motion=motion%4;
                if (motion<0)
                    motion=motion+4;
                motion=motion_up_down[motion];
            }
            else
            {
                motion=(-pos_ghostx_num_ghost-pos_ghosty_num_ghost)*2.5/16;
                motion=motion%4;
                if (motion<0)
                    motion=motion+4;
            }

            /*
                        if (connected==1 && playerleft==0) {
                                m_pointCloud[num_ghost+2].texCoords.x = (float) (9+128*(4+((num_ghost+level+difficulty)%4)))*150.0;
                                m_pointCloud[num_ghost+2].texCoords.y = (float) (10+72+motion*72)*150.0;
                        } else {
                                m_pointCloud[num_ghost+1].texCoords.x = (float) (9+128*(4+((num_ghost+level+difficulty)%4)))*150.0;
                                m_pointCloud[num_ghost+1].texCoords.y = (float) (10+72+motion*72)*150.0;
                        }
            */

//      RenderBlit2(960-32+9+verschilx+offsetx+cut_left,540-36+10+verschily+offsety+cut_up,  128*(4+((num_ghost+level+difficulty)%4))+9+cut_left, 72+motion*72+10+cut_up,      64-18-cut_left-cut_right,72-20-cut_up-cut_down);


            if (ghost==1 || (cool==1 && current==4))
            {
//crossing
//hopla
                int m_index=num_ghost*2+1+(connected==1 && playerleft==0);
                if (cool==1 && current==4)
                {
                    m_pointCloud[m_index].color = sf::Color(0,0,0,0);
                    m_pointCloud[m_index+1].color = sf::Color(0,0,0,0);
                }
                if ( (cool==1 && current==4) || ((offsetx>(9-64-new_verschilx-new_verschilx2)) && (offsety>(11-72-new_verschily-new_verschily2)) && (offsetx<1980-new_verschilx-new_verschilx2) && (offsety<1080-new_verschily-new_verschily2)))
                {
                    offsetx=new_verschilx+new_verschilx2;
                    offsety=new_verschily+new_verschily2;

                    if (shade_map>=1)
                    {
                        offsetx=offsetx+flowx;
                        offsety=offsety+flowy;
                    }
                    m_shader.setUniform("wave_phase", fpstime+num_ghost);

                    if (SFML==1)
                    {
//crossing ghost
                        int cut_left=0;
                        int cut_right=0;
                        int cut_up=0;
                        int cut_down=0;

                        int posX=0;
                        int posY=0;

                        mazemovex=(flowx-pos_ghostx_num_ghost+1920-32+maxpixelsx)/64;
                        mazemovey=(flowy-pos_ghosty_num_ghost+1080   +maxpixelsy)/72;
                        mazemovex=(mazemovex+addx)%modx;
                        mazemovey=(mazemovey+addy)%mody;

                        posX=(flowx-pos_ghostx_num_ghost+1920-32)%64;
                        posY=(flowy-pos_ghosty_num_ghost+1080   )%72;

                        int blokje=maze_plot[mazemovex][mazemovey];

                        int bridge=0;
                        if (flippo==0 || follow_ghost_num!=num_ghost)
                        {
                            if (blank_maze!=1 || drawmazes!=1)
                            {
                                if ( (blokje&(64+32))>0 )
                                    bridge=1;
                                if ((blokje&64)==64 && fspeed_ghostx_num_ghost!=0)
                                {
                                    if ( posX>=0 && posX<(63-15) )
                                        cut_left=63-15-posX;
                                }
                                if ((blokje&32)==32 && fspeed_ghosty_num_ghost!=0.0)
                                {
                                    if ( posY>=0 && posY<(71-16) )
                                        cut_up=71-16-posY;
                                }

                                blokje=maze_plot[(mazemovex+1)%modx][mazemovey];
                                if ( (blokje&(64+32))>0 )
                                    bridge=1;
                                if ((blokje&64)==64 && fspeed_ghostx_num_ghost!=0)
                                {
                                    if ( posX>63-47 )
                                        cut_right=posX-63+47;
                                }

                                blokje=maze_plot[mazemovex][(mazemovey+1)%mody];
                                if ( (blokje&(64+32))>0 )
                                    bridge=1;
                                if ((blokje&32)==32 && fspeed_ghosty_num_ghost!=0)
                                {
                                    if ( posY>71-54 )
                                        cut_down=posY-71+54;
                                }
                            }
                        }
                        else
                        {
                            cut_up=36;
                            cut_down=36;
                            cut_left=32;
                            cut_right=32;
                            bridge=1;
                        }
                        int cutter=0;
                        if (cut_up>0)
                            cutter|=1;
                        if (cut_down>0)
                            cutter|=2;
                        if (cut_left>0)
                            cutter|=4;
                        if (cut_right>0)
                            cutter|=8;
//game
                        if (!follow_ghost && abs(verschilx)<10 && abs(verschily)<10 && pen==0 && check_num_ghost<=1 && recover==0 && force_game==1 && !(flippo==1 && num_ghost==follow_ghost_num))
                        {
                            if (hunt==0 || 0)
                            {
                                if ( ! (bridge==1 && ( (fspeed_ghostx_num_ghost!=0 && fspeedy!=0) || (fspeed_ghosty_num_ghost!=0 && fspeedx!=0) ) ) )
                                {
                                    local_points-=25;
//                                    soundoff=soundoff|4;
                                    playsound=playsound|128;
                                    recover=20;
                                }
//flippo
//                                if (local_points<=0 && MAZEOFF==0) { local_points=0; die=1; next=1;}
                            }
                            else
                            {
                                if ( !(bridge==1 && ( (fspeed_ghostx_num_ghost!=0 && fspeedy!=0) || (fspeed_ghosty_num_ghost!=0 && fspeedx!=0) ) ) )
                                {
                                    /*
                                                                        pos_ghostx_num_ghost=pos_ghostx[number-1];
                                                                        pos_ghosty_num_ghost=pos_ghosty[number-1];
                                                                        fpos_ghostx_num_ghost=fpos_ghostx[number-1];
                                                                        fpos_ghosty_num_ghost=fpos_ghosty[number-1];
                                                                        fspeed_ghostx_num_ghost=fspeed_ghostx[number-1];
                                                                        fspeed_ghosty_num_ghost=fspeed_ghosty[number-1];
                                                                        check_num_ghost=check[number-1];
                                                                        number--;
                                    */
//game
                                    soundoff=soundoff|64;
                                    playsound=playsound|64;
                                    fspeed_ghostx_num_ghost*=2+(float)(rand()%100)/100.0;
                                    fspeed_ghosty_num_ghost*=2+(float)(rand()%100)/100.0;
                                    check_num_ghost+=2;
                                    local_points+=25;
                                }
                            }
                        }
//                        if (posX>0 || posY>0) {
//                            GHOSTtexture.clear(sf::Color(0,0,0,0));
//                            spritedot.setPosition(9,10);
//                        }
                        if (64-18-cut_left-cut_right>0 &&  72-22-cut_up-cut_down>0)
                        {
                            if (cool==1 && current==4)
                            {
                                if (smooth)
                                {
                                    m_pointCloud[m_index].position.x = (float) fmod(
                                                                           offsetx_store+new_verschilx+new_verschilx2 -9  +cut_left/2.0-cut_right/2.0 +32+maxpixelsx
                                                                           -(float)smooth_x+(float)((int)smooth_x)
                                                                           -(float)fpos_ghostx_num_ghost+(float)((int)fpos_ghostx_num_ghost),
                                                                           maxpixelsx);
                                    m_pointCloud[m_index].position.y = (float) fmod(
                                                                           offsety_store+new_verschily+new_verschily2 -11 +cut_up/2.0-cut_down/2.0    +36+maxpixelsy*1.5-540.0
                                                                           -(float)smooth_y+(float)((int)smooth_y)
                                                                           -(float)fpos_ghosty_num_ghost+(float)((int)fpos_ghosty_num_ghost),
                                                                           maxpixelsy)-(float)maxpixelsy*0.5+540.0;
                                    m_pointCloud[m_index+1].position = m_pointCloud[m_index].position;

                                }
                                else
                                {
                                    m_pointCloud[m_index].position.x = (float) fmod(
                                                                           offsetx_store+new_verschilx+new_verschilx2 -9  +cut_left/2.0-cut_right/2.0 +32+maxpixelsx,
                                                                           maxpixelsx);
                                    m_pointCloud[m_index].position.y = (float) fmod(
                                                                           offsety_store+new_verschily+new_verschily2 -11 +cut_up/2.0-cut_down/2.0    +36+maxpixelsy*1.5-540.0,
                                                                           maxpixelsy)-(float)maxpixelsy*0.5+540.0;
                                    m_pointCloud[m_index+1].position = m_pointCloud[m_index].position;
                                }
                                m_pointCloud[m_index].color = sf::Color(cutter,
                                                                        num_ghost%256,
                                                                        64-18-(cut_left+cut_right),
                                                                        72-22-(cut_up+cut_down)
                                                                       );
                                m_pointCloud[m_index+1].color = sf::Color(cutter,num_ghost%256,64-18-(cut_left+cut_right),72-22-(cut_up+cut_down));

                            }
                            if (hunt==1 && check_num_ghost<=1)
                            {
                                if (cool==1 && current==4)
                                {
                                    m_pointCloud[m_index].texCoords.x = (float) (128*(6)+9+cut_left)*150.0;
                                    m_pointCloud[m_index].texCoords.y = (float) (72*5+motion*72+11+cut_up)*150.0;
//                                    m_pointCloud[m_index].color = sf::Color(cutter,num_ghost%256,64-18-(cut_left+cut_right),72-20-(cut_up+cut_down));
                                }
                                if (ghost==1)
                                {
                                    RenderBlit2(960-32+9+verschilx+offsetx+cut_left,
                                                540-36+10+verschily+offsety+cut_up,
                                                128*(6)+9+cut_left,
                                                72*5+motion*72+10+cut_up,
                                                64-18-cut_left-cut_right,
                                                72-20-cut_up-cut_down);
                                }
                            }
                            else if (hunt==2 && check_num_ghost<=1)
                            {
                                if ((((int)((hunt_counter+num_ghost)/15))%2)==0)
                                {
                                    if (cool==1 && current==4)
                                    {
                                        m_pointCloud[m_index].texCoords.x = (float) (128*(7)+9+cut_left)*150.0;
                                        m_pointCloud[m_index].texCoords.y = (float) (72*5+motion*72+11+cut_up)*150.0;
//                                        m_pointCloud[m_index].color = sf::Color(cutter,num_ghost%256,64-18-(cut_left+cut_right),72-20-(cut_up+cut_down));
                                    }
                                    if (ghost==1)
                                    {
                                        RenderBlit2(960-32+9+verschilx+offsetx+cut_left,
                                                    540-36+10+verschily+offsety+cut_up,
                                                    128*(7)+9+cut_left,
                                                    72*5+motion*72+10+cut_up,
                                                    64-18-cut_left-cut_right,
                                                    72-20-cut_up-cut_down);
                                    }
                                }
                                else
                                {
                                    if (cool==1 && current==4)
                                    {
                                        m_pointCloud[m_index].texCoords.x = (float) (128*(6)+9+cut_left)*150.0;
                                        m_pointCloud[m_index].texCoords.y = (float) (72*5+motion*72+11+cut_up)*150.0;
//                                        m_pointCloud[m_index].color = sf::Color(cutter,num_ghost%256,64-18-(cut_left+cut_right),72-20-(cut_up+cut_down));
                                    }
                                    if (ghost==1)
                                    {
                                        RenderBlit2(960-32+9+verschilx+offsetx+cut_left,540-36+10+verschily+offsety+cut_up,
                                                    128*(6)+9+cut_left,           72*5+motion*72+10+cut_up,
                                                    64-18-cut_left-cut_right,72-20-cut_up-cut_down);
                                    }
                                }
                            }
                            else if ((follow_ghost==0 || follow_ghost_num!=num_ghost) && check_num_ghost<=1)
                            {
                                if (cool==1 && current==4)
                                {
                                    m_pointCloud[m_index].texCoords.x = (float) (128*(4+((num_ghost+level+difficulty)%4))+9+cut_left)*150.0;
                                    m_pointCloud[m_index].texCoords.y = (float) (72+motion*72+11+cut_up)*150.0;
//                                    m_pointCloud[m_index].color = sf::Color(cutter,num_ghost%256,64-18-(cut_left+cut_right),72-20-(cut_up+cut_down));
                                }
                                if (ghost==1)
                                    RenderBlit2(960-32+9+verschilx+offsetx+cut_left,
                                                540-36+10+verschily+offsety+cut_up,
                                                128*(4+((num_ghost+level+difficulty)%4))+9+cut_left,
                                                72+motion*72+10+cut_up,
                                                64-18-cut_left-cut_right,
                                                72-20-cut_up-cut_down);
                            }
                            else if (check_num_ghost<=1)
                            {
                                static int flits;
                                flits++;
                                int rev_sync=0;
                                if (sync==0)
                                    rev_sync=1;
                                if ((((int)(flits/(15+rev_sync*50)))%2)==0)
                                {
                                    if (cool==1 && current==4)
                                    {
                                        m_pointCloud[m_index].texCoords.x = (float) (128*(7)+9+cut_left)*150.0;
                                        m_pointCloud[m_index].texCoords.y = (float) (72*5+motion*72+11+cut_up)*150.0;
//                                        m_pointCloud[m_index].color = sf::Color(cutter,num_ghost%256,64-18-(cut_left+cut_right),72-20-(cut_up+cut_down));
                                    }
                                    if (ghost==1)
                                    {
                                        RenderBlit2(960-32+9+verschilx+offsetx+cut_left,540-36+10+verschily+offsety+cut_up,
                                                    128*(7)+9+cut_left,        72*5+motion*72+10+cut_up,
                                                    64-18-cut_left-cut_right,72-20-cut_up-cut_down);
                                    }
                                }
                                else
                                {
                                    if (cool==1 && current==4)
                                    {
                                        m_pointCloud[m_index].texCoords.x = (float) (128*(6)+9+cut_left)*150.0;
                                        m_pointCloud[m_index].texCoords.y = (float) (72*5+motion*72+11+cut_up)*150.0;
//                                        m_pointCloud[m_index].color = sf::Color(cutter,num_ghost%256,64-18-(cut_left+cut_right),72-20-(cut_up+cut_down));
                                    }
                                    if (ghost==1)
                                    {
                                        RenderBlit2(960-32+9+verschilx+offsetx+cut_left,540-36+10+verschily+offsety+cut_up,
                                                    128*(6)+9+cut_left,        72*5+motion*72+10+cut_up,
                                                    64-18-cut_left-cut_right,   72-20-cut_up-cut_down);
                                    }
                                }
                            }

                            int look=0;
                            if (fspeed_ghosty_num_ghost<0)
                                look=0;
                            else if (fspeed_ghosty_num_ghost>0)
                                look=1;
                            else if (fspeed_ghostx_num_ghost<0)
                                look=2;
                            else if (fspeed_ghostx_num_ghost>0)
                                look=3;
                            if (goexit)
                            {
                                look=((int)((fpstime+(float)num_ghost)/10.0))%4;
                            }

                            if (hunt!=2 || check_num_ghost>1)
                            {
                                if (cool==1 && current==4)
                                {
                                    if (check_num_ghost>1)
                                    {
                                        m_pointCloud[m_index].texCoords.x = (float) (0)*150.0;
                                        m_pointCloud[m_index].texCoords.y = (float) (0)*150.0;
                                        m_pointCloud[m_index].color = sf::Color(0,0,0,0);
                                    }
                                    m_pointCloud[m_index+1].texCoords.x = (float) (10*64+9+cut_left)*150.0;
                                    m_pointCloud[m_index+1].texCoords.y = (float) (72*5+look*72+11+cut_up)*150.0;
//                                    m_pointCloud[m_index+1].color = sf::Color(cutter,num_ghost%256,64-18-(cut_left+cut_right),72-20-(cut_up+cut_down));
                                }
                                if (ghost==1)
                                {
                                    RenderBlit2(960-32+9+verschilx+offsetx+cut_left,
                                                540-36+10+verschily+offsety+cut_up,
                                                10*64+9+cut_left,
                                                5*72+look*72+10+cut_up,
                                                64-18-cut_left-cut_right,
                                                72-20-cut_up-cut_down);
                                }
                            }
                            else
                            {
                                if ((((int)(hunt_counter/15))%2)==0 )
                                {
                                    if (cool==1 && current==4)
                                    {
                                        m_pointCloud[m_index+1].texCoords.x = (float) (16*64+9+cut_left)*150.0;
                                        m_pointCloud[m_index+1].texCoords.y = (float) (72*5+look*72+11+cut_up)*150.0;
//                                        m_pointCloud[m_index+1].color = sf::Color(cutter,num_ghost%256,64-18-(cut_left+cut_right),72-20-(cut_up+cut_down));
                                    }
                                    if (ghost==1)
                                    {
                                        RenderBlit2(960-32+9+verschilx+offsetx+cut_left, 540-36+10+verschily+offsety+cut_up,
                                                    16*64+9+cut_left, 5*72+look*72+10+cut_up,
                                                    64-18-cut_left-cut_right,72-20-cut_up-cut_down);
                                    }
                                }
                                else
                                {
                                    if (cool==1 && current==4)
                                    {
                                        m_pointCloud[m_index+1].texCoords.x = (float) (10*64+9+cut_left)*150.0;
                                        m_pointCloud[m_index+1].texCoords.y = (float) (72*5+look*72+11+cut_up)*150.0;
//                                        m_pointCloud[m_index+1].color = sf::Color(cutter,num_ghost%256,64-18-(cut_left+cut_right),72-20-(cut_up+cut_down));
                                    }
                                    if (ghost==1)
                                    {
                                        RenderBlit2(960-32+9+verschilx+offsetx+cut_left, 540-36+10+verschily+offsety+cut_up,
                                                    10*64+9+cut_left, 5*72+look*72+10+cut_up,
                                                    64-18-cut_left-cut_right,72-20-cut_up-cut_down);
                                    }
                                }
                            }
                        }
                    }
                }
            }

            if (check_num_ghost>1)
            {
                check_num_ghost+=2;
                if (check_num_ghost>1000)
                {
                    pos_ghostx_num_ghost=pos_ghostx[number-1];
                    pos_ghosty_num_ghost=pos_ghosty[number-1];
                    fpos_ghostx_num_ghost=fpos_ghostx[number-1];
                    fpos_ghosty_num_ghost=fpos_ghosty[number-1];
                    fspeed_ghostx_num_ghost=fspeed_ghostx[number-1];
                    fspeed_ghosty_num_ghost=fspeed_ghosty[number-1];
                    check_num_ghost=check[number-1];
                    number--;
                }
            }

            fpos_ghostx[num_ghost]=fpos_ghostx_num_ghost;
            fpos_ghosty[num_ghost]=fpos_ghosty_num_ghost;
            pos_ghostx[num_ghost]=pos_ghostx_num_ghost;
            pos_ghosty[num_ghost]=pos_ghosty_num_ghost;
            fspeed_ghostx[num_ghost]=fspeed_ghostx_num_ghost;
            fspeed_ghosty[num_ghost]=fspeed_ghosty_num_ghost;
            check[num_ghost]=check_num_ghost;
        }
    }
    ghostmode=0;
    fspeed_ghost_all=1.0;
//    if (cool==1) mutje.unlock();

    if (hunt!=0)
    {
        if (hunt_counter==hunt_max)
        {
            for (num_ghost=0; num_ghost<number; num_ghost++)
            {
                if (!(flippo==1 && num_ghost==follow_ghost_num))
                {
                    if (check[num_ghost]<2)
                    {
                        if (((pos_ghostx[num_ghost]+32)%64)==0)
                            fspeed_ghostx[num_ghost]=fspeed_ghostx[num_ghost]/2;
                        else
                            fspeed_ghostx[num_ghost]=-fspeed_ghostx[num_ghost]/2;

                        if ((pos_ghosty[num_ghost]%72)==0)
                            fspeed_ghosty[num_ghost]=fspeed_ghosty[num_ghost]/2;
                        else
                            fspeed_ghosty[num_ghost]=-fspeed_ghosty[num_ghost]/2;
                        //flipflop
                    }
                    check[num_ghost]=(check[num_ghost]>>1)<<1;
//                check[num_ghost]=0;
                }
            }
        }
        hunt_counter--;
        if (hunt_counter<(240))
            hunt=2;
        if (hunt_counter<=0)
        {
            hunt=0;
            for (num_ghost=0; num_ghost<number; num_ghost++)
            {
                if (check[num_ghost]<2)
                {
                    if (!(flippo==1 && num_ghost==follow_ghost_num))
                    {
                        fspeed_ghostx[num_ghost]=fspeed_ghostx[num_ghost]*2;
                        fspeed_ghosty[num_ghost]=fspeed_ghosty[num_ghost]*2;
                    }
                }
            }
        }
    }

    static unsigned long long totalmem=0;
    static int old_time=0;
    static int new_time=0;
    static int elaps_time=0;
    static int frames=0;
    static int total_time=0;
    static int old_time_mem=0;


    SFMLView1.setActive(false);


//    if (plot_cubes) plot_cubes_vertex();
    plot_ghosts();

//here1
    if (blending>=1 || shade_main!=0 || blendit==1)
    {
        SFMLView1.setActive(false);
        sf::Sprite sprite_final;
        sprite_final.setTexture(texture_final.getTexture(),false);
        sprite_final.setTextureRect({0,0,1920,1080});
        sprite_final.setPosition(0,0);


        texture_final.display();
        if (shade_main!=0)
        {
            SFMLView1.draw(sprite_final);
        }
        else
        {
            SFMLView1.draw(sprite_final);
        }
    }

    SFMLView1.setActive(false);

    /*
        if (!(record_debug && F2==1)) {
            if (record_screen==1 && record_pause==0) {
                SFMLView1.display();
            }
            do_the_recording_stuff();
        }
    */
    if (crop) {
        static bool first=true;
        static sf::RenderStates crop_RenderStates;
        static sf::BlendMode crop_BlendMode=sf::BlendAlpha;
        if (first) {
            first=false;
            crop_RenderStates.blendMode=crop_BlendMode;
        }
        SFMLView1.draw(sprite_from_crop,crop_RenderStates);
    }
    if (SFML==1)
    {
        if (F2==1)
        {
            if (mazetype==1)
            {
                sprintf(score,"LEVEL=%d TYPE=MAZE WIDTH=%d HEIGHT=%d", level,hoog,breed);
            }
            else
                sprintf(score,"LEVEL=%d", level);
            if (err_level==0)
                draw2(score,0,0,sf::Color::Blue,sf::Color::White);
            else
                draw2(score,0,0,sf::Color::Red,sf::Color::White);
        }

        if (F2==1)
        {
            if (sync==1)
            {
                if (F4==1)
                    sprintf(score,"FPS=%d FRAME=%d SYNC=ON SPEED ADJUST=%f RUNTIME=%f TIME RUN/FPS/FCT=%4.3f/%4.3f/%4.3f DOWNLOADED=%.0f",
                            framespersecond,frame_counter,fspeed_adjust,run_time,fpstime,fpstime*fpstime_factor,fpstime_factor,BYTES_DOWNLOADED);
                else
                    sprintf(score,"FPS=%d FRAME=%d SYNC=ON RUNTIME=%f TIME RUN/FPS/FCT=%4.3f/%4.3f/%4.3f DOWNLOADED=%.0f",
                            framespersecond,frame_counter,run_time,fpstime,fpstime*fpstime_factor,fpstime_factor,BYTES_DOWNLOADED);
            }
            else
            {
                if (F4==1)
                    sprintf(score,"FPS=%d FRAME=%d SYNC=OFF SPEED ADJUST=%f RUNTIME=%f TIME RUN/FPS/FCT=%4.3f/%4.3f/%4.3f DOWNLOADED=%.0f",
                            framespersecond,frame_counter,fspeed_adjust,run_time,fpstime,fpstime*fpstime_factor,fpstime_factor,BYTES_DOWNLOADED);
                else
                    sprintf(score,"FPS=%d FRAME=%d SYNC=OFF RUNTIME=%f TIME RUN/FPS/FCT=%4.3f/%4.3f/%4.3f DOWNLOADED=%.0f",
                            framespersecond,frame_counter,run_time,fpstime,fpstime*fpstime_factor,fpstime_factor,BYTES_DOWNLOADED);
            }
            draw2(score,0,32,sf::Color::Blue,sf::Color::White);

            sprintf(line,"GHOSTS=%d",number);
            if (follow_ghost==1)
            {
                sprintf(score," FOLLOWING NR. %d",follow_ghost_num);
                strcat(line,score);
            }
            draw2(line,0,64,sf::Color::Blue,sf::Color::White);

            if (MAZEOFF==0)
            {
                sprintf(score,"BITMAPS %dx%d USED=%d/%d CHANGED=%d FILES=%d MAZEFILES=%d", BITMAPSX,BITMAPSY,totalused,MAXINMEM,totalchanged, totalfiles,totalfiles_mazes);
                draw2(score,0,96,sf::Color::Blue,sf::Color::White);
            }
            else
            {
                sprintf(score,"BITMAPS %dx%d USED=%d/%d CHANGED=%d (PROCESSED ONLY (MAZEOFF=1) FILES=%d MAZEFILES=%d)", BITMAPSX,BITMAPSY,totalused,MAXINMEM,totalchanged, totalfiles,totalfiles_mazes);
                draw2(score,0,96,sf::Color::Blue,sf::Color::White);
            }
        }

        old_mazemovex=thread_mazemovex;
        old_mazemovey=thread_mazemovey;
        mazemovex=(picturex*1920-posx);
        mazemovey=(picturey*1080-posy);
        thread_mazemovex=mazemovex;
        thread_mazemovey=mazemovey;

        plotx=(picturex*1920-posx-32)/64;
        ploty=(picturey*1080-posy   )/72;
        plotx=(plotx-45+60*(maxpicturex+1) )%(30*(maxpicturex+1));
        ploty=(ploty-23+30*(maxpicturey+1) )%(15*(maxpicturey+1));

        if (connected==1)
            NETWORK_HANDLER2();

        if (F2==1)
        {
            int y_offset=18*32;
            static char * choice[4]= {"OFF","DEF","ON ","CUS"};
            static char * choice2[4]= {"BACK ","DEF  ","FRONT","DEPTH"};
            static char * choice3[3]= {"OFF","ON ","FIX"};
            sprintf(writer,"         BLEND  PLOT  SHOW  TILE  SHADER");
            mydraw2(writer,1200,y_offset-32,sf::Color::Blue,sf::Color::White);

            if (ffmpegfile==0)
            {
                sprintf(writer,"FFMPEG   %s    %s %s   %s   %s",
                        choice[handler[FFMPEG_SELECT].blending+1],
//                        handler[FFMPEG_SELECT].blending ? "ON " : "OFF",
                        choice2[handler[FFMPEG_SELECT].plot_front+1],
//                        handler[FFMPEG_SELECT].plot_front ? "FRONT" : "BACK ",
                        handler[FFMPEG_SELECT].show ? "ON " : "OFF",
                        choice3[handler[FFMPEG_SELECT].tile],
//                        handler[FFMPEG_SELECT].tile ? "ON " : "OFF",
                        handler[FFMPEG_SELECT].shader ? "ON " : "OFF"
                       );
                if (selector==FFMPEG_SELECT)
                    mydraw2(writer,1200,y_offset,sf::Color::Blue,sf::Color::White);
                else
                    mydraw2(writer,1200,y_offset,sf::Color::Black,sf::Color::White);
            }

            if (internetfile==0)
            {
                sprintf(writer,"INTERNET %s    %s %s   %s   %s",
                        choice[handler[INTERNET_SELECT].blending+1],
//                        handler[INTERNET_SELECT].blending ? "ON " : "OFF",
                        choice2[handler[INTERNET_SELECT].plot_front+1],
//                        handler[INTERNET_SELECT].plot_front ? "FRONT" : "BACK ",
                        handler[INTERNET_SELECT].show ? "ON " : "OFF",
                        choice3[handler[INTERNET_SELECT].tile],
//                        handler[INTERNET_SELECT].tile ? "ON " : "OFF",
                        handler[INTERNET_SELECT].shader ? "ON " : "OFF"
                       );
                if (selector==INTERNET_SELECT)
                    mydraw2(writer,1200,y_offset+32,sf::Color::Blue,sf::Color::White);
                else
                    mydraw2(writer,1200,y_offset+32,sf::Color::Black,sf::Color::White);
            }
            if (movie==0)
            {
                sprintf(writer,"MOVIE    %s    %s %s   %s   %s",
                        choice[handler[MOVIE_SELECT].blending+1],
//                        handler[MOVIE_SELECT].blending ? "ON " : "OFF",
                        choice2[handler[MOVIE_SELECT].plot_front+1],
//                        handler[MOVIE_SELECT].plot_front ? "FRONT" : "BACK ",
                        handler[MOVIE_SELECT].show ? "ON " : "OFF",
                        choice3[handler[MOVIE_SELECT].tile],
//                        handler[MOVIE_SELECT].tile ? "ON " : "OFF",
                        handler[MOVIE_SELECT].shader ? "ON " : "OFF"
                       );
                if (selector==MOVIE_SELECT)
                    mydraw2(writer,1200,y_offset+32*2,sf::Color::Blue,sf::Color::White);
                else
                    mydraw2(writer,1200,y_offset+32*2,sf::Color::Black,sf::Color::White);
            }
            if (movie2==0)
            {
                sprintf(writer,"MOVIE2   %s    %s %s   %s   %s",
                        choice[handler[MOVIE2_SELECT].blending+1],
                        choice2[handler[MOVIE2_SELECT].plot_front+1],
                        handler[MOVIE2_SELECT].show ? "ON " : "OFF",
                        choice3[handler[MOVIE2_SELECT].tile],
//                        handler[MOVIE2_SELECT].tile ? "ON " : "OFF",
                        handler[MOVIE2_SELECT].shader ? "ON " : "OFF"

                       );
                if (selector==MOVIE2_SELECT)
                    mydraw2(writer,1200,y_offset+32*3,sf::Color::Blue,sf::Color::White);
                else
                    mydraw2(writer,1200,y_offset+32*3,sf::Color::Black,sf::Color::White);
            }

            if ((plot_all==1 || plot_cubes==1))
            {
                sprintf(writer,"CANVAS   %s    %s %s   %s   %s",
                        choice[handler[CANVAS_SELECT].blending+1],
                        choice2[handler[CANVAS_SELECT].plot_front+1],
                        handler[CANVAS_SELECT].show ? "ON " : "OFF",
                        choice3[handler[CANVAS_SELECT].tile],
//                        handler[CANVAS_SELECT].tile ? "ON " : "OFF",
                        handler[CANVAS_SELECT].shader ? "ON " : "OFF"

                       );
                extern double ddp;
                extern double ddp_loop;
                extern double hold;
                extern int hold_level;

                if (selector==CANVAS_SELECT)
                {
                    mydraw2(writer,1200,y_offset+32*4,sf::Color::Blue,sf::Color::White);
                    sprintf(writer,"TRANSLATE X=%10.4f Y=%10.4f Z=%10.4f",plot_all_translate_x,plot_all_translate_y,plot_all_translate_z);
                    mydraw2(writer,1200,y_offset+32*5,sf::Color::Blue,sf::Color::White);
                    sprintf(writer,"ROTATE    X=%10.4f Y=%10.4f Z=%10.4f",plot_all_rotate_x,plot_all_rotate_y,plot_all_rotate_z);
                    mydraw2(writer,1200,y_offset+32*6,sf::Color::Blue,sf::Color::White);
                    sprintf(writer,"FOVY=%3.0f  ZNEAR=%3.2f  ZFAR=%3.2f  SCALE=%8.5f",
                            plot_all_fovyInDegrees,plot_all_znear,plot_all_zfar,sprite_from_canvas.getScale().x);
                    mydraw2(writer,1200,y_offset+32*7,sf::Color::Blue,sf::Color::White);
                    sprintf(writer,"         PATH=%10.9f    SCALE JUMP=%8.5f",
                            ddp_loop,scale_jump);
                    mydraw2(writer,1200,y_offset+32*8,sf::Color::Blue,sf::Color::White);
                    sprintf(writer,"         PATH=%10.9f   SET HOLD=%8.5f",
                            ddp,hold);
                    mydraw2(writer,1200,y_offset+32*9,sf::Color::Blue,sf::Color::White);
                    sprintf(writer,"         HOLD LEVEL=%2d       CURRENT=%8.5f  MODE=%d",
                            hold_level,(double)(sprite_from_canvas.getScale().x)*pow(2.0,level),draw_model);
                    mydraw2(writer,1200,y_offset+32*10,sf::Color::Blue,sf::Color::White);



                }
                else
                    mydraw2(writer,1200,y_offset+32*4,sf::Color::Black,sf::Color::White);
            }

            if (
                (selector==MOVIE_SELECT && movie==0) ||
                (selector==MOVIE2_SELECT && movie2==0) ||
                (selector==FFMPEG_SELECT && ffmpegfile==0) ||
                (selector==INTERNET_SELECT && internetfile==0) ||
                (selector==CANVAS_SELECT && plot_all==1)
            )
            {
                strcpy(writer,(char*)"         ");
                if (selector_item==BLENDING_SELECT)
                    strcat(writer,choice[handler[selector].blending+1]);
//                    if (selector_item==BLENDING_SELECT) strcat(writer,(char*)handler[selector].blending ? "ON " : "OFF");
                else
                    strcat(writer,(char*)"       ");
                if (selector_item==PLOT_FRONT_SELECT)
                    strcat(writer,choice2[handler[selector].plot_front+1]);
//                    if (selector_item==PLOT_FRONT_SELECT) strcat(writer,(char*)handler[selector].plot_front ? "FRONT" : "BACK ");
                else
                    strcat(writer,(char*)"      ");
                if (selector_item==SHOW_SELECT)
                    strcat(writer,(char*)handler[selector].show ? "ON " : "OFF");
                else
                    strcat(writer,(char*)"      ");
                if (selector_item==TILE_SELECT)
                {

                    strcat(writer,choice3[handler[selector].tile]);
//                        strcat(writer,(char*)handler[selector].tile ? "ON " : "OFF");
                }
                else
                    strcat(writer,(char*)"      ");
                if (selector_item==SHADER_SELECT)
                    strcat(writer,(char*)handler[selector].shader ? "ON " : "OFF");
                else
                    strcat(writer,(char*)"      ");
                mydraw2(writer,1200,y_offset+selector*32,sf::Color::Red,sf::Color::White);
            }

            sprintf(writer,"POSITION: X=%5d Y=%5d MX=%5d MY=%5d TX=%3d TY=%3d SX=%7.3f SY=%7.3f VX=%7.3f VY=%7.3f",
                    (mazemovex+1920/2)%maxpixelsx,(mazemovey+1080/2)%maxpixelsy,plotx,ploty,render_picturex,render_picturey,
                    fmod(smooth_x,(double)maxpixelsx),fmod(smooth_y,(double)maxpixelsy),
                    avg_speedx,avg_speedy);
//hotshot
//            if (follow_ghost==1) printf("F1: x=%d,y%d\n",(render_picturex*y_offset0-render_posx),(render_picturey*1080-render_posy));
            draw2(writer,0,128,sf::Color::Blue,sf::Color::White);

//            printf("main: info: clock: playing_time=%f playing_screen_num=%d\n",playing_time,playing_screen_num);
            if (movieextern==0)
            {
                animate_lock.lock();
                sprintf(writer,"R: REAL=%s TIME=%s FRAME=%d FPS=%.3f/%.3f\n%s",
                        seconds_to_time(play_clock_tot.getElapsedTime().asSeconds()),
                        seconds_to_time(playing_time),
                        playing_screen_num,
                        fps_playing_frame,fps_playing_tot,
                        playing_info_static);
                animate_lock.unlock();
//                draw2(writer,0,160,sf::Color::Yellow,sf::Color::Black);
                mydraw2(writer,0,160,sf::Color(10,130,149,255),sf::Color::White);

            }
            if (record_screen==1)
            {
                animate_lock.lock();
                sprintf(writer,"W: REAL=%s TIME=%s FRAME=%d FPS=%.3f/%.3f\n%s",
                        seconds_to_time(rec_clock_tot.getElapsedTime().asSeconds()),
                        seconds_to_time(recording_time),
                        record_screen_num,
                        fps_record_frame,fps_record_tot,
                        recording_info_static);
//                draw2(writer,0,160+32*4,sf::Color::Green,sf::Color::Black);
                animate_lock.unlock();
                mydraw2(writer,0,160+32*4,sf::Color(170,70,89,255),sf::Color::White);
            }
            if (playerleft==0)
            {
                if (client==1)
                {
                    strcpy(writer,"CONNECTED TO SERVER ");
                    strcat(writer,connectedip);
                    draw2(writer,0,192,sf::Color::Blue,sf::Color::White);

                }
                else if (server==1)
                {
                    strcpy(writer,"CONNECTED TO CLIENT ");
                    strcat(writer,connectedip);
                    draw2(writer,0,192,sf::Color::Blue,sf::Color::White);
                }
            }
        }

        if (playerleft==1)
        {
            if (client==1)
            {
                strcpy(writer,"DISCONNECTED FROM SERVER ");
                strcat(writer,connectedip);
                if (REMOTE_ALIVE==0)
                    strcat(writer," DEAD");
                else
                    strcat(writer," QUIT");
                draw2(writer,0,192,sf::Color::Red,sf::Color::White);

            }
            else if (server==1)
            {
                strcpy(writer,"DISCONNECTED FROM CLIENT ");
                strcat(writer,connectedip);
                if (REMOTE_ALIVE==0)
                    strcat(writer," DEAD");
                else
                    strcat(writer," QUIT");
                draw2(writer,0,192,sf::Color::Red,sf::Color::White);
            }
        }
    }
    static int jump=0;
    static int jump_posx;
    static int jump_posy;
    static char command[20]="\0";
    static char lastcommand[2000]="\0";
    static char lastcommand2[2000]="\0";

    SFMLView1.setActive(true);

    if (connected==1)
    {
        old_remote_posx=remote_posx;
        old_remote_posy=remote_posy;

        int newdata=0;

        if (inpointer!=0)
        {
            newdata=1;
            strcat(last_in,in);
            in[0]='\0';
            inpointer=0;
        }

        if (F2==1)
        {
            if (inpointer!=0)
            {
                strcpy(print,"RECEIVED: ");
            }
            else
            {
                strcpy(print,"RECEIVED: ");
            }
        }
        static char movement;
        static int ALIVE=5000;
        if (newdata==1)
        {
            REMOTE_ALIVE=10000;
            int numread;
            newdata=0;
            lastcommand[0]='\0';
            do
            {
                numread=sscanf(last_in,"T=%[^,],X=%d,Y=%d,M=%c,",command,&remote_posx,&remote_posy,&movement);
                if (numread<0)
                {
                    in[0]='\0';
                    inpointer=0;
                    last_in[0]='\0';
                    break;
                }
                if ((strcmp(command,"POS")==0))
                {
                    playerleft=0;
                    sprintf(writer,"T=%s,X=%d,Y=%d,M=%c,",command,remote_posx,remote_posy,movement);
                    sprintf(last_in,"%s", &last_in[strlen(writer)] );
                    remote_posx_ar[(remote_pos_start+remote_pos_counter)%4096]=remote_posx;
                    remote_posy_ar[(remote_pos_start+remote_pos_counter)%4096]=remote_posy;
                    remote_movement[(remote_pos_start+remote_pos_counter)%4096]=movement;
                    remote_pos_counter+=1;
                    strcat(lastcommand,command);
                    strcat(lastcommand,",");
                    move_remote_posx=remote_posx;
                    move_remote_posy=remote_posy;
                    remote_edit=0;
                    jump=0;
                }
                else if ((strcmp(command,"PLOT")==0))
                {
                    int blokje;
                    int remote_pen_mode;
                    sscanf(last_in,"T=%[^,],X=%d,Y=%d,M=%d,PEN_MODE=%d,",command,&remote_posx,&remote_posy,&blokje,&remote_pen_mode);
                    sprintf(writer,"T=PLOT,X=%d,Y=%d,M=%d,PEN_MODE=%d,\0",remote_posx,remote_posy,blokje,remote_pen_mode);
                    sprintf(last_in,"%s", &last_in[strlen(writer)] );
                    remote_plot(remote_posx,remote_posy,blokje,remote_pen_mode);
                    jump=1;
                    jump_posx=remote_posx;
                    jump_posy=remote_posy;
                    strcat(lastcommand,command);
                    strcat(lastcommand,",");
                    move_remote_posx=remote_posx;
                    move_remote_posy=remote_posy;
                    remote_edit=1;
                }
                else if ((strcmp(command,"GOTO")==0))
                {
                    sscanf(last_in,"T=%[^,],X=%d,Y=%d,",command,&remote_posx,&remote_posy);
                    sprintf(writer,"T=GOTO,X=%d,Y=%d,\0",remote_posx,remote_posy);
                    sprintf(last_in,"%s", &last_in[strlen(writer)] );
                    goto_plot(remote_posx,remote_posy);
                    jump=1;
                    jump_posx=remote_posx;
                    jump_posy=remote_posy;
                    strcat(lastcommand,command);
                    strcat(lastcommand,",");
                    move_remote_posx=remote_posx;
                    move_remote_posy=remote_posy;
                    remote_edit=1;
                }
                else if ((strcmp(command,"ALIVE")==0))
                {
                    sprintf(writer,"T=ALIVE,");
                    sprintf(last_in,"%s", &last_in[strlen(writer)] );
                    strcat(lastcommand,command);
                    strcat(lastcommand,",");
                }
                else if ((strcmp(command,"INVITE")==0))
                {
                    sprintf(writer,"T=INVITE,");
                    sprintf(last_in,"%s", &last_in[strlen(writer)] );
                    strcat(lastcommand,command);
                    strcat(lastcommand,",");
                    goto_partner();
                }
                else if ((strcmp(command,"LEVEL")==0))
                {
                    sprintf(writer,"T=LEVEL,LEVEL=%d,",level);
                    numread=sscanf(last_in,"T=%[^,],LEVEL=%d,",command,&level);
                    loaded=1;
                    next=1;
                    if (combine==1)
                        goto_pos_remote();
                    loaded_from_maze=1;
                    load_maze(level);
                    sprintf(last_in,"%s", &last_in[strlen(writer)] );
                    strcat(lastcommand,command);
                    strcat(lastcommand,",");
                    jump=0;
                    return;
                }
                else if ((strcmp(command,"SAVEMAZE")==0))
                {
                    sprintf(writer,"T=SAVEMAZE,");
                    sprintf(last_in,"%s", &last_in[strlen(writer)] );
                    if (combine==1)
                        goto_pos_remote();
                    save_maze(level);
                    levelnotsaved=0;
                    strcat(lastcommand,command);
                    strcat(lastcommand,",");
                }
                else if ((strcmp(command,"SAVEMAP")==0))
                {
                    sprintf(writer,"T=SAVEMAP,");
                    sprintf(last_in,"%s", &last_in[strlen(writer)] );
                    if (combine==1)
                        goto_pos_remote();
                    levelnotsaved=0;
                    save_map();
                    strcat(lastcommand,command);
                    strcat(lastcommand,",");
                }
                else if ((strcmp(command,"LOADMAP")==0))
                {
                    sprintf(writer,"T=LOADMAP,");
                    sprintf(last_in,"%s", &last_in[strlen(writer)] );
                    loadmap=1;
                    loaded=1;
                    if (combine==1)
                        goto_pos_remote();
                    next=1;
                    strcat(lastcommand,command);
                    strcat(lastcommand,",");
                    jump=0;
                    return;
                }
                else if ((strcmp(command,"COMBINE")==0))
                {
                    numread=sscanf(last_in,"T=%[^,],COMBINE=%d,",command,&combine);
                    sprintf(writer,"T=COMBINE,COMBINE=%d,\0",combine);
                    sprintf(last_in,"%s", &last_in[strlen(writer)] );
                    strcat(lastcommand,command);
                    strcat(lastcommand,",");
                    jump=0;
                }
                else if ((strcmp(command,"MIRROR")==0))
                {
                    numread=sscanf(last_in,"T=%[^,],MIRROR=%d,",command,&mirror);
                    sprintf(writer,"T=MIRROR,MIRROR=%d,\0",mirror);
                    sprintf(last_in,"%s", &last_in[strlen(writer)] );
                    strcat(lastcommand,command);
                    strcat(lastcommand,",");
                    jump=0;
                }
                else if ((strcmp(command,"CROSSING")==0))
                {
                    numread=sscanf(last_in,"T=%[^,],CROSSING=%d,",command,&crossing);
                    sprintf(writer,"T=CROSSING,CROSSING=%d,\0",crossing);
                    sprintf(last_in,"%s", &last_in[strlen(writer)] );
                    strcat(lastcommand,command);
                    strcat(lastcommand,",");
                    jump=0;
                }
                else if ((strcmp(command,"MOVELEVEL")==0))
                {
                    numread=sscanf(last_in,"T=%[^,],LEVEL=%d,",command,&level);
                    sprintf(writer,"T=MOVELEVEL,LEVEL=%d,",level);
                    sprintf(last_in,"%s", &last_in[strlen(writer)] );
                    strcat(lastcommand,command);
                    strcat(lastcommand,",");
                }
                else if ((strcmp(command,"MAZE")==0))
                {
                    numread=sscanf(last_in,"T=%[^,],BIGLARGE=%d,SEED=%d,LEVEL=%d,",command,&big_large,&SEED,&level);
                    sprintf(writer,"T=MAZE,BIGLARGE=%d,SEED=%d,LEVEL=%d,\0",big_large,SEED,level);
                    next=1;
                    loaded=0;
                    sprintf(last_in,"%s", &last_in[strlen(writer)] );
                    strcat(lastcommand,command);
                    strcat(lastcommand,",");
                    jump=0;
                    return;
                }
                else if ((strcmp(command,"NEXT")==0))
                {
                    next=1;
                    level++;
                    if (loaded==1)
                    {
                        loaded_from_maze=1;
                        load_maze(level);
                    }
                    sprintf(writer,"T=NEXT,");
                    sprintf(last_in,"%s", &last_in[strlen(writer)] );
                    strcat(lastcommand,command);
                    strcat(lastcommand,",");
                    jump=0;
                    return;
                }
                else if ((strcmp(command,"QUIT")==0))
                {
                    playerleft=1;
                    in[0]='\0';
                    inpointer=0;
                    last_in[0]='\0';
                    if (tcp==1)
                    {
                        internet_socket_tcp1.disconnect();
                        internet_socket_tcp2.disconnect();
                    }
                    strcat(lastcommand,command);
                    strcat(lastcommand,",");
                    jump=0;
                }
                else if ((strcmp(command,"READY")==0))
                {
                    sprintf(writer,"T=READY,");
                    sprintf(last_in,"%s", &last_in[strlen(writer)] );
                    sprintf(writer,"T=POS,X=%d,Y=%d,M=%c,\0", thread_mazemovex,thread_mazemovey,lastmove);
                    SEND(writer);
                    strcat(lastcommand,command);
                    strcat(lastcommand,",");
                    jump=0;
                }
                else if ((strcmp(command,"CLEARMAP")==0))
                {
                    sprintf(writer,"T=CLEARMAP,");
                    sprintf(last_in,"%s", &last_in[strlen(writer)] );
                    clear_map();
                    ReadBitmaps2();
                    SENDGOTOPOS();
                    strcat(lastcommand,command);
                    strcat(lastcommand,",");
                    jump=0;
                }
                else if ((strcmp(command,"RECONNECT")==0))
                {
                    sprintf(writer,"T=POS,X=%d,Y=%d,M=%c,\0", thread_mazemovex,thread_mazemovey,lastmove);
                    SEND(writer);
                    playerleft=0;
                    sprintf(writer,"T=%s,\0",command);
                    sprintf(last_in,"%s", &last_in[strlen(writer)] );
                    strcat(lastcommand,command);
                    strcat(lastcommand,",");
                }
                else
                {
                    in[0]='\0';
                    inpointer=0;
                    last_in[0]='\0';
                }
            }
            while (numread>=1);
        }
        else if (REMOTE_ALIVE>0)
            REMOTE_ALIVE--;

        if (REMOTE_ALIVE==0)
        {
            playerleft=1;
            in[0]='\0';
            inpointer=0;
            last_in[0]='\0';
            if (tcp==1)
            {
                internet_socket_tcp1.disconnect();
                internet_socket_tcp2.disconnect();
            }
        }
        ALIVE--;
        if (ALIVE==0)
        {
            ALIVE=5000;
            SEND((char*)"T=ALIVE,\0");
        }

        if (remote_pos_counter>0)
        {
            if (remote_pos_counter>1000)
            {
                remote_pos_start+=1;
                remote_pos_start=remote_pos_start%4096;
                remote_pos_counter--;
            }
            if (start_buffering==1)
            {
                remote_posx=remote_posx_ar[remote_pos_start];
                remote_posy=remote_posy_ar[remote_pos_start];
                remote_pos_start+=1;
                remote_pos_start=remote_pos_start%4096;
                remote_pos_counter--;
                start_buffering=0;
                old_remote_posx=remote_posx;
                old_remote_posy=remote_posy;
                plotdatax[(plot_start+plot_count)%4096]=remote_posx;
                plotdatay[(plot_start+plot_count)%4096]=remote_posy;
                plot_count++;
            }
            while (remote_pos_counter>0)
            {
                int last_remote_posx;
                int last_remote_posy;
                int last_remote_time;
                int last_remote_movement;
                int out_x;
                int out_y;

                last_remote_posx=remote_posx_ar[(remote_pos_start+4095)%4096];
                last_remote_posy=remote_posy_ar[(remote_pos_start+4095)%4096];
                last_remote_time=remote_timer[(remote_pos_start+4095)%4096];
                last_remote_movement=remote_movement[(remote_pos_start+4095)%4096];
                out_x=0;
                out_y=0;

                remote_posx=remote_posx_ar[remote_pos_start];
                remote_posy=remote_posy_ar[remote_pos_start];
                movement=remote_movement[remote_pos_start];

                if (abs(remote_posx-last_remote_posx)>1000)
                {
                    remote_posx+=1000;
                    remote_posx=remote_posx%(1920*(totalpicturex));
                    last_remote_posx+=1000;
                    last_remote_posx=last_remote_posx%(1920*(totalpicturex));
                    out_x=1000;
                }
                if (abs(remote_posy-last_remote_posy)>1000)
                {
                    remote_posy+=1000;
                    remote_posy=remote_posy%(1080*(totalpicturey));
                    last_remote_posy+=1000;
                    last_remote_posy=last_remote_posy%(1080*(totalpicturey));
                    out_y=1000;
                }

                static int xtussen;
                static int ytussen;

                if ((remote_posx>last_remote_posx) && (remote_posy-last_remote_posy==0))
                {
                    int xxx;
                    for (xxx=last_remote_posx+1; xxx<=remote_posx; xxx++)
                    {
                        xtussen=(xxx-out_x+(totalpicturex)*1920)%(1920*(totalpicturex));
                        plotdatax[(plot_start+plot_count)%4096]=xtussen;
                        plotdatay[(plot_start+plot_count)%4096]=remote_posy;
                        plot_count++;
                        if (remote_edit==0)
                            if ( (  ((xtussen+32)%32)==0) && ((remote_posy%36)==0)  )
                                remote_point(xtussen,remote_posy);
                    }
                }
                else if ((remote_posx<last_remote_posx) && (remote_posy-last_remote_posy==0))
                {
                    int xxx;
                    for (xxx=last_remote_posx-1; xxx>=remote_posx; xxx--)
                    {
                        xtussen=(xxx-out_x+(totalpicturex)*1920)%(1920*(totalpicturex));
                        plotdatax[(plot_start+plot_count)%4096]=xtussen;
                        plotdatay[(plot_start+plot_count)%4096]=remote_posy;
                        plot_count++;
                        if (remote_edit==0)
                            if ( (  ((xtussen+32)%32)==0) && ((remote_posy%36)==0)  )
                                remote_point(xtussen,remote_posy);
                    }
                }
                else if ((remote_posy>last_remote_posy) && (remote_posx-last_remote_posx==0))
                {
                    int yyy;
                    for (yyy=last_remote_posy+1; yyy<=remote_posy; yyy++)
                    {
                        ytussen=(yyy-out_y+(totalpicturey)*1080)%(1080*(totalpicturey));
                        plotdatax[(plot_start+plot_count)%4096]=remote_posx;
                        plotdatay[(plot_start+plot_count)%4096]=ytussen;
                        plot_count++;
                        if (remote_edit==0)
                            if ( (  ((remote_posx+32)%32)==0) && ((ytussen%36)==0)  )
                                remote_point(remote_posx,ytussen);
                    }
                }
                else if ((remote_posy<last_remote_posy) && (remote_posx-last_remote_posx==0))
                {
                    int yyy;
                    for (yyy=last_remote_posy-1; yyy>=remote_posy; yyy--)
                    {
                        ytussen=(yyy-out_y+(totalpicturey)*1080)%(1080*(totalpicturey));
                        plotdatax[(plot_start+plot_count)%4096]=remote_posx;
                        plotdatay[(plot_start+plot_count)%4096]=ytussen;
                        plot_count++;
                        if (remote_edit==0)
                            if ( (  ((remote_posx+32)%32)==0) && ((ytussen%36)==0)  )
                                remote_point(remote_posx,ytussen);
                    }
                }
                else if (movement=='X')
                {
                    int yyy;
                    int xxx=last_remote_posx;
                    if ((remote_posy>last_remote_posy))
                    {
                        for (yyy=last_remote_posy+1; yyy<=remote_posy; yyy++)
                        {
                            xtussen=(xxx-out_x+(totalpicturex)*1920)%(1920*(totalpicturex));
                            ytussen=(yyy-out_y+(totalpicturey)*1080)%(1080*(totalpicturey));
                            plotdatax[(plot_start+plot_count)%4096]=xtussen;
                            plotdatay[(plot_start+plot_count)%4096]=ytussen;
                            plot_count++;
                            if (remote_edit==0)
                                if ( (  ((xtussen+32)%32)==0) && ((ytussen%36)==0)  )
                                    remote_point(xtussen,ytussen);
                        }
                        yyy=remote_posy;
                    }
                    else if ((remote_posy<last_remote_posy))
                    {
                        for (yyy=last_remote_posy-1; yyy>=remote_posy; yyy--)
                        {
                            xtussen=(xxx-out_x+(totalpicturex)*1920)%(1920*(totalpicturex));
                            ytussen=(yyy-out_y+(totalpicturey)*1080)%(1080*(totalpicturey));
                            plotdatax[(plot_start+plot_count)%4096]=xtussen;
                            plotdatay[(plot_start+plot_count)%4096]=ytussen;
                            plot_count++;
                            if (remote_edit==0)
                                if ( (  ((xtussen+32)%32)==0) && ((ytussen%36)==0)  )
                                    remote_point(xtussen,ytussen);
                        }
                        yyy=remote_posy;
                    }
                    if ((remote_posx>last_remote_posx))
                    {
                        for (xxx=last_remote_posx+1; xxx<=remote_posx; xxx++)
                        {
                            xtussen=(xxx-out_x+(totalpicturex)*1920)%(1920*(totalpicturex));
                            ytussen=(yyy-out_y+(totalpicturey)*1080)%(1080*(totalpicturey));
                            plotdatax[(plot_start+plot_count)%4096]=xtussen;
                            plotdatay[(plot_start+plot_count)%4096]=ytussen;
                            plot_count++;
                            if (remote_edit==0)
                                if ( (  ((xtussen+32)%32)==0) && ((ytussen%36)==0)  )
                                    remote_point(xtussen,ytussen);
                        }
                    }
                    else if ((remote_posx<last_remote_posx))
                    {
                        for (xxx=last_remote_posx-1; xxx>=remote_posx; xxx--)
                        {
                            xtussen=(xxx-out_x+(totalpicturex)*1920)%(1920*(totalpicturex));
                            ytussen=(yyy-out_y+(totalpicturey)*1080)%(1080*(totalpicturey));
                            plotdatax[(plot_start+plot_count)%4096]=xtussen;
                            plotdatay[(plot_start+plot_count)%4096]=ytussen;
                            plot_count++;
                            if (remote_edit==0)
                                if ( (  ((xtussen+32)%32)==0) && ((ytussen%36)==0)  )
                                    remote_point(xtussen,ytussen);
                        }
                    }
                }
                else if (movement=='Y')
                {
                    int xxx;
                    int yyy=last_remote_posy;
                    if ((remote_posx>last_remote_posx))
                    {
                        for (xxx=last_remote_posx+1; xxx<=remote_posx; xxx++)
                        {
                            xtussen=(xxx-out_x+(totalpicturex)*1920)%(1920*(totalpicturex));
                            ytussen=(yyy-out_y+(totalpicturey)*1080)%(1080*(totalpicturey));
                            plotdatax[(plot_start+plot_count)%4096]=xtussen;
                            plotdatay[(plot_start+plot_count)%4096]=ytussen;
                            plot_count++;
                            if (remote_edit==0)
                                if ( (  ((xtussen+32)%32)==0) && ((ytussen%36)==0)  )
                                    remote_point(xtussen,ytussen);
                        }
                        xxx=remote_posx;
                    }
                    else if ((remote_posx<last_remote_posx))
                    {
                        for (xxx=last_remote_posx-1; xxx>=remote_posx; xxx--)
                        {
                            xtussen=(xxx-out_x+(totalpicturex)*1920)%(1920*(totalpicturex));
                            ytussen=(yyy-out_y+(totalpicturey)*1080)%(1080*(totalpicturey));
                            plotdatax[(plot_start+plot_count)%4096]=xtussen;
                            plotdatay[(plot_start+plot_count)%4096]=ytussen;
                            plot_count++;
                            if (remote_edit==0)
                                if ( (  ((xtussen+32)%32)==0) && ((ytussen%36)==0)  )
                                    remote_point(xtussen,ytussen);
                        }
                        xxx=remote_posx;
                    }
                    if ((remote_posy>last_remote_posy))
                    {
                        for (yyy=last_remote_posy+1; yyy<=remote_posy; yyy++)
                        {
                            xtussen=(xxx-out_x+(totalpicturex)*1920)%(1920*(totalpicturex));
                            ytussen=(yyy-out_y+(totalpicturey)*1080)%(1080*(totalpicturey));
                            plotdatax[(plot_start+plot_count)%4096]=xtussen;
                            plotdatay[(plot_start+plot_count)%4096]=ytussen;
                            plot_count++;
                            if (remote_edit==0)
                                if ( (  ((xtussen+32)%32)==0) && ((ytussen%36)==0)  )
                                    remote_point(xtussen,ytussen);
                        }
                    }
                    else if ((remote_posy<last_remote_posy))
                    {
                        for (yyy=last_remote_posy-1; yyy>=remote_posy; yyy--)
                        {
                            xtussen=(xxx-out_x+(totalpicturex)*1920)%(1920*(totalpicturex));
                            ytussen=(yyy-out_y+(totalpicturey)*1080)%(1080*(totalpicturey));
                            plotdatax[(plot_start+plot_count)%4096]=xtussen;
                            plotdatay[(plot_start+plot_count)%4096]=ytussen;
                            plot_count++;
                            if (remote_edit==0)
                                if ( (  ((xtussen+32)%32)==0) && ((ytussen%36)==0)  )
                                    remote_point(xtussen,ytussen);
                        }
                    }
                }
                else if (movement=='0')
                {
                    xtussen=(remote_posx-out_x+(totalpicturex)*1920)%(1920*(totalpicturex));
                    ytussen=(remote_posy-out_y+(totalpicturey)*1080)%(1080*(totalpicturey));

                    plotdatax[(plot_start+plot_count)%4096]=xtussen;
                    plotdatay[(plot_start+plot_count)%4096]=ytussen;
                    plot_count++;
                    if (remote_edit==0)
                        if ( (  ((xtussen+32)%32)==0) && ((ytussen%36)==0)  )
                            remote_point(xtussen,ytussen);
                }
                remote_pos_start+=1;
                remote_pos_start=remote_pos_start%4096;
                remote_pos_counter--;
            }
        }

        float fnumpixels=4.0;
        float ffollow=4.0;

        fnumpixels=fnumpixels+(float)plot_count/10-0.02;
        ffollow=ffollow+(fnumpixels-ffollow)/ffollow*2+0.2;

        if (plot_count>=4)
        {
            int numpixels=ffollow;
            if (numpixels>=plot_count)
                numpixels=plot_count-1;
            remote_posx=plotdatax[plot_start];
            remote_posy=plotdatay[plot_start];
            plot_count=plot_count-numpixels;
            plot_start=(plot_start+numpixels)%4096;
        }
        else if (plot_count>=3)
        {
            remote_posx=plotdatax[plot_start];
            remote_posy=plotdatay[plot_start];
            plot_start=(plot_start+plot_count-2)%4096;
            plot_count=1;
        }
        else if (plot_count>=2)
        {
            remote_posx=plotdatax[plot_start];
            remote_posy=plotdatay[plot_start];
            plot_start=(plot_start+plot_count-1)%4096;
            plot_count=1;
        }
        else
        {
            remote_posx=plotdatax[plot_start];
            remote_posy=plotdatay[plot_start];
        }

        if (jump==1)
        {
            remote_posx=jump_posx;
            remote_posy=jump_posy;
        }

        static char bar1[]="0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
        static char bar2[]="0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
        static int barlength=strlen(bar1);

        SFMLView1.setActive(false);

        if (F2==1)
        {
            if (plot_count>barlength)
                strncpy(bar2,bar1,barlength-1);
            else
                strncpy(bar2,bar1,plot_count);
            bar2[plot_count+1]='\0';
            sprintf(writer," X=%d,Y=%d BUF: %s",remote_posx,remote_posy,bar2);
            strcat(print,writer);
            draw2(print,0,192+32,sf::Color::Blue,sf::Color::White);
            strcat(lastcommand2,lastcommand);
            draw2(lastcommand,0,224+32,sf::Color::Red,sf::Color::White);
            strcpy(lastcommand2,lastcommand);
        }
    }

    if (SFML==1)
    {
        if (drawmazes==1 && pen==0 && MAZEOFF==0 && ghost==1 && record_screen==0)
        {
            if (follow_ghost==0 && flippo==0)
            {
                sprintf(score,"%d",total_points);

                text.setString(score);
                static int xcoor=text.getGlobalBounds().width;
                int xcoor_old=xcoor;
                xcoor=text.getGlobalBounds().width;
                if (xcoor_old>xcoor)
                    xcoor=xcoor_old;

                xcoor=xcoor;
                draw2(score,1900-xcoor,0,sf::Color::Blue,sf::Color::White);

                sprintf(score,"%d",local_points);
                text.setString(score);
                //            xcoor=text.getGlobalBounds().width;
                //            xcoor=xcoor-xcoor%20;
                draw2(score,1900-xcoor,32,sf::Color::Blue,sf::Color::White);

            }

            if (total_points<=0 && drawmazes==1 && force_game==1 && !mazetype==1)
            {
                nextlevel=1;
            }

            if (connected==1)
            {
                sprintf(score,"%d",remote_points);
                static int xcoor=text.getGlobalBounds().width;
                int xcoor_old=xcoor;
                xcoor=text.getGlobalBounds().width;
                if (xcoor_old>xcoor)
                    xcoor=xcoor_old;

                text.setString(score);
                xcoor=text.getGlobalBounds().width;
                xcoor=xcoor-xcoor%20;
                draw2(score,1900-xcoor,64,sf::Color(50,50,255,255),sf::Color::White);
            }
        }

        if (F2==0 && DO_ADAPT)
        {
            draw2(going_to,0,1080-32,sf::Color(20,60,98,255),sf::Color::White);
        }
        if (F2==1)
        {
//            if (check_mem==1) check_memory();
            if (check_mem==1)
                check_memory();

            strcpy(writer,"");
            if (DO_ADAPT==0)
            {
                if (pen==1)
                {
                    strcpy(writer,"EDIT ");
                    if (pen_mode==0)
                        strcat(writer,"DRAW");
                    else if (pen_mode==1)
                        strcat(writer,"ERASE");
                    else if (pen_mode==2)
                        strcat(writer,"MOVE");
                }
int extern pacman_move;
int extern move_config;
                if (pacman_move) {
                    if (pacman_move==1) strcat(writer,"  PM1=H/V");
                    else if (pacman_move==2) strcat(writer,"  PM1=H");
                    else if (pacman_move==3) strcat(writer,"  PM1=V");
                }
                if (move_config) {
                    if (move_config==1) strcat(writer,"  PM2=H/V");
                    else if (move_config==2) strcat(writer,"  PM2=H");
                    else if (move_config==3) strcat(writer,"  PM2=V");
                }
                if (pacman==0)
                    strcat(writer,"  P=OFF");
                if (ghost==0)
                    strcat(writer,"  G=OFF");
                if (DONTSAVEFILES==1)
                    strcat(writer,"  SAVE=OFF");
                if (eatmode) {
                    if (eatmode==1) {
                        strcat(writer,"  EAT=P");
                    } else strcat(writer,"  EAT=P+G");
                }
                if (drawmazes==1)
                {
                    if (blank_maze==0)
                        strcat(writer,"  DRAWMAZES=ON");
                    else
                        strcat(writer,"  DRAWMAZES=BLANKED");
                }
                if (movie_move==1 || internet_move==1 || movie2_move==1 || ffmpeg_move==1)
                {
                    strcat(writer,"  POSITION FIXED=");
                    if (movie_move==1)
                        strcat(writer,"M");
                    if (movie2_move==1)
                        strcat(writer,"/B");
                    if (internet_move==1)
                        strcat(writer,"/I");
                    if (ffmpeg_move==1)
                        strcat(writer,"/P");
                }
                if (blending==1)
                    strcat(writer,"  BLEND=ON");
                else if (blending==2)
                    strcat(writer,"  BLEND=CUSTOM");
                if (movie==0 || movie2==0 || ffmpegfile==0 || internetfile==0 || blending>=1)
                {
                    if (plot_front==1)
                        strcat(writer,"  PLOT=FRONT");
                    else
                        strcat(writer,"  PLOT=BACK");
                }
                if (blend_on_movie==1)
                    strcat(writer,"  BLEND ON MOVIE (FIT) (v)=MAX");
                else if (blend_on_movie==2)
                    strcat(writer,"  BLEND ON MOVIE (MAX) (v)=OFF");

                if (formula>0)
                {
                    sprintf(line,"  FORMULA=%d",formula);
                    strcat(writer,line);
                }
                if (mirror>0)
                {
                    sprintf(line,"  MIRROR=%d",mirror);
                    strcat(writer,line);
                }
                if (crossing>0)
                {
                    sprintf(line,"  CROSSING=%d",crossing);
                    strcat(writer,line);
                }
                if (shade_main==1)
                {
                    sprintf(line,"  SCREEN TRUE SHADER");
                    strcat(writer,line);
                }
                if (mouse_move==1)
                {
                    sprintf(line,"  MOUSE=ON");
                    strcat(writer,line);
                }
                if (force_game==1)
                {
                    sprintf(line,"  GAME=ON(,)");
                    strcat(writer,line);
                    if (difficulty==1)
                        strcat(writer,"(EASY)");
                    if (difficulty==2)
                        strcat(writer,"(NORMAL)");
                    if (difficulty==3)
                        strcat(writer,"(HARD)");
                    if (difficulty==4)
                        strcat(writer,"(ULTRA)");

                }
                if (fragment_shader==1 || vertex_shader==1 || buffer_shader==1)
                {
                    strcpy(line,"  SHADER=");
                    if (vertex_shader==1)
                        strcat(line,"VERTEX");
                    if (vertex_shader==1 && fragment_shader==1)
                        strcat(line,",");
                    if (fragment_shader==1)
                        strcat(line,"FRAGMENT");
                    if ( (vertex_shader==1 || fragment_shader==1) && buffer_shader==1)
                        strcat(line,",");
                    if (buffer_shader==1)
                        strcat(line,"BUFFER");
                    strcat(writer,line);
                }
                if (plot_shader==1)
                    strcat(writer,"  PLOT SHADER");
                if (plot_only)
                    strcat(writer,"  PLOT ONLY");
                if (plot_cubes)
                    strcat(writer,"  PLOT CUBES");
                if (flushing)
                    strcat(writer,"  FLUSHING");
                if (voxel_to_file)
                    strcat(writer,"  VOXEL TO FILE");
                if (plot_shader==2)
                    strcat(writer,"  PLOT SHADER TO BACKGROUND");
                if (MAZEOFF==1)
                    strcat(writer,"  MAZEOFF");
                if (shade_map==1)
                    strcat(writer,"  PLOT MAP");
                if (shade_map==2)
                    strcat(writer,"  PLOT MAP 2");
                if (loadbackground==0)
                    strcat(writer,"  BACKGROUND=OFF");
                if (RGBA==1)
                    strcat(writer,"  RBGA=ON");
                if (crop==1)
                {
                    sf::FloatRect fr=sprite_from_crop.getGlobalBounds();
                    sprintf(line,"  CROP=%d:%d:%d:%d",int(fr.width+0.5),int(fr.height+0.5),int(fr.left+0.5),int(fr.top+0.5));
//                    sprintf(line,"  CROP=%d,%d",crop_x,crop_x_size);
                    strcat(writer,line);
                }
                if (set_transparant==0)
                    strcat(writer,"  TRANSPARANT=OFF");
                if (strlen(writer)>(int)(100))
                {
                    text.setCharacterSize(18);
                    draw2(writer,0,1080-32,sf::Color::Red,sf::Color::White);
                    text.setCharacterSize(24);
                }
                else
                    draw2(writer,0,1080-32,sf::Color::Red,sf::Color::White);
            }
            else
            {
                draw2(going_to,0,1080-32,sf::Color(20,60,98,255),sf::Color::White);
            }

            if (shade_map>=1 && show_shade_map==1)
            {
                double pacx;
                double pacy;
                int pixels_in_map;
                int tiles_in_map;
                if (follow_ghost==1)
                {
                    pacx=fmod((double)(-pos_ghostx[follow_ghost_num]+1920+1920/2+maxpixelsx),(double)maxpixelsx);
                    pacy=fmod((double)(-pos_ghosty[follow_ghost_num]+1080+1080/2+maxpixelsy),(double)maxpixelsy);
                }
                else
                {
                    pacx=fmod((double)(picturex*1920-posx+1920/2),(double)maxpixelsx);
                    pacy=fmod((double)(picturey*1080-posy+1080/2),(double)maxpixelsy);
                }
                tiles_in_map=(int)pow(2.0,(SAS_ZOOM));
                pixels_in_map=256*tiles_in_map;
//                tiles_in_map=(int)pow(2.0,(17-SAS_ZOOM));
//                pixels_in_map=256*tiles_in_map;
//
                int pixels_in_screenx=BITMAPSX*1920;
                int pixels_in_screeny=BITMAPSY*1080;
                double tiles_in_screenx=(double)pixels_in_screenx/256;
                double tiles_in_screeny=(double)pixels_in_screeny/256;
//
                double rel_pos_in_map_x_start=(double)(SAS_STARTX*256 +SAS_STARTX_a)/(double)(pixels_in_map);
                double rel_pos_in_map_y_start=(double)(SAS_STARTY*256 +SAS_STARTY_a)/(double)(pixels_in_map);
                double SAS_ENDX,SAS_ENDY;
                SAS_ENDX=(double)SAS_STARTX+(double)SAS_STARTX_a/256.0+tiles_in_screenx;
                SAS_ENDY=(double)SAS_STARTY+(double)SAS_STARTY_a/256.0+tiles_in_screeny;
//
//
                double rel_pos_in_map_x_end=(double)(SAS_ENDX*256 )/(double)(pixels_in_map);
                double rel_pos_in_map_y_end=(double)(SAS_ENDY*256 )/(double)(pixels_in_map);
                double coverage_x=(rel_pos_in_map_x_end-rel_pos_in_map_x_start);
                if (coverage_x>1)
                    coverage_x=1;
                double coverage_y=(rel_pos_in_map_y_end-rel_pos_in_map_y_start);
                if (coverage_y>1)
                    coverage_y=1;
                double total_coverage=coverage_x*coverage_y;
                coverage_x*=100;
                coverage_y*=100;
                total_coverage*=100;
//
                double tile_pacx,tile_pacy;
                tile_pacx=(double)SAS_STARTX+(double)SAS_STARTX_a/256+(double)pacx/256;
                tile_pacy=(double)SAS_STARTY+(double)SAS_STARTY_a/256+(double)pacy/256;
                double rel_pos_in_map_x_cur=(double)(SAS_STARTX*256 + SAS_STARTX_a + (pacx) )/(double)(pixels_in_map);
                double rel_pos_in_map_y_cur=(double)(SAS_STARTY*256 + SAS_STARTY_a + (pacy) )/(double)(pixels_in_map);
//
                int i=8;

                double pixel_startx=(double)SAS_STARTX*256+(double)SAS_STARTX_a;
                double pixel_starty=(double)SAS_STARTY*256+(double)SAS_STARTY_a;
                double pixel_endx=(double)SAS_ENDX*256;
                double pixel_endy=(double)SAS_ENDY*256;
                double pixel_posx=(double)SAS_STARTX*256+SAS_STARTX_a+(double)pacx;
                double pixel_posy=(double)SAS_STARTY*256+SAS_STARTY_a+(double)pacy;

                sf::Color col;
                if (rel_pos_in_map_x_cur<0 || rel_pos_in_map_x_cur>1 || rel_pos_in_map_y_cur<0 || rel_pos_in_map_y_cur>1 )
                    col=sf::Color(255,0,0,255);
                else
                    col=sf::Color(20,60,98,255);

                sprintf(writer,"MAP:       TILES      X              Y  PIXELS  X         Y  SCREEN X          Y     REL.POSITION IN MAP/LEVEL AT");
                mydraw2(writer,0,500-32*i,sf::Color(10,30,49,255),sf::Color::White);
                sprintf(writer,"____       ___________________________  ___________________  ______________________  _____________________________");
                mydraw2(writer,0,500-32*i,sf::Color(10,30,49,255),sf::Color::White);
                i--;

                sprintf(writer,"TOT:     %9.0f,---- %9.0f,----  %9.0f %9.0f   %10.2f %10.2f",
                        (double)tiles_in_map, (double)tiles_in_map, (double)pixels_in_map, (double)pixels_in_map,
                        (double)pixels_in_map/1920.0,(double)pixels_in_map/1080.0 );
                mydraw2(writer,0,500-32*i,sf::Color(20,60,98,255),sf::Color::White);
                i--;
//                sprintf(writer,"MAP TOTAL:    %17.0f.---- %21.0f", pow((double)tiles_in_map,2),pow((double)pixels_in_map,2));
//                mydraw2(writer,0,500-32*i,sf::Color(20,60,98,255),sf::Color::White); i--;

                sprintf(writer,"START:  %15.4f %14.4f  %9.0f %9.0f   %7.0f,-- %7.0f,--",
                        (double)SAS_STARTX-(double)SAS_STARTX_a/256.0, (double)SAS_STARTY-(double)SAS_STARTY_a/256.0,pixel_startx,pixel_starty,
                        (double)(SAS_STARTX*256.0-SAS_STARTX_a)/1920.0,(double)(SAS_STARTY*256.0-SAS_STARTY_a)/1080.0    );
                mydraw2(writer,0,500-32*i,sf::Color(20,60,98,255),sf::Color::White);
                sprintf(writer,"X=%14.7f%% Y=%14.7f%%",rel_pos_in_map_x_start*100,rel_pos_in_map_y_start*100);
                mydraw2(writer,79*14,500-32*i,sf::Color(20,60,98,255),sf::Color::White);
                i--;


                sprintf(writer,"POS:     %14.4f %14.4f  %9.0f %9.0f   %10.2f %10.2f",
                        tile_pacx,tile_pacy,pixel_posx,pixel_posy,
                        pixel_posx/1920.0, pixel_posy/1080.0);
                mydraw2(writer,0,500-32*i,col,sf::Color::White);
                sprintf(writer,"X=%14.7f%% Y=%14.7f%%",rel_pos_in_map_x_cur*100,rel_pos_in_map_y_cur*100);
//                sprintf(writer,"X=%12.7f,Y=%12.7f  X=%12.5f%%,Y=%12.5f%%",rel_pos_in_map_x_cur,rel_pos_in_map_y_cur,rel_pos_in_map_x_cur*100,rel_pos_in_map_y_cur*100);
                mydraw2(writer,79*14,500-32*i,col,sf::Color::White);
                i--;


                sprintf(writer,"END:     %14.4f %14.4f  %9.0f %9.0f   %10.2f %10.2f",
                        SAS_ENDX, SAS_ENDY,pixel_endx,pixel_endy,
                        pixel_endx/1920.0,pixel_endy/1080.0);
                mydraw2(writer,0,500-32*i,sf::Color(20,60,98,255),sf::Color::White);
                sprintf(writer,"X=%14.7f%% Y=%14.7f%%", rel_pos_in_map_x_end*100,rel_pos_in_map_y_end*100);
//                sprintf(writer,"X=%12.7f,Y=%12.7f  X=%12.5f%%,Y=%12.5f%%", rel_pos_in_map_x_end,rel_pos_in_map_y_end, rel_pos_in_map_x_end*100,rel_pos_in_map_y_end*100);
                mydraw2(writer,79*14,500-32*i,sf::Color(20,60,98,255),sf::Color::White);
                i--;


                sprintf(writer,"LEVEL: TOT:%12.4f   %12.4f  %9.0f %9.0f   %7.0f,-- %7.0f,--",
                        tiles_in_screenx,tiles_in_screeny,(double)maxpixelsx,(double)maxpixelsy,
                        (double)maxpixelsx/1920.0,(double)maxpixelsy/1080.0);
                mydraw2(writer,0,500-32*i,sf::Color(20,60,98,255),sf::Color::White);
                sprintf(writer,"X=%14.7f%% Y=%14.7f%% (TOTAL=%.11f%%)",coverage_x,coverage_y,total_coverage);
                mydraw2(writer,79*14,500-32*i,sf::Color(20,60,98,255),sf::Color::White);
                sprintf(writer,"______");
                mydraw2(writer,0,500-32*i,sf::Color(10,30,49,255),sf::Color::White);
                i--;

                sprintf(writer,"POS:       %12.4f   %12.4f  %9.0f %9.0f   %10.2f %10.2f",
                        (double)pacx/256,(double)pacy/256,(double)pacx,(double)pacy,
                        (double)pacx/1920.0,(double)pacy/1080.0);
                mydraw2(writer,0,500-32*i,sf::Color(20,60,98,255),sf::Color::White);

                sprintf(writer,"X=%14.7f%%,Y=%14.7f%%",(double)pacx/(double)maxpixelsx*100,(double)pacy/(double)maxpixelsy*100);
                mydraw2(writer,79*14,500-32*i,sf::Color(20,60,98,255),sf::Color::White);
                i--;

                sprintf(writer,"LNG=%12.7f ,LAT=%12.7f",
                        rel_pos_in_map_x_cur*360.0-180.0,
                        180.0/PI*atan(0.5 * (exp(PI-2.0*PI*rel_pos_in_map_y_cur) - exp(-(PI-2.0*PI*rel_pos_in_map_y_cur)))));
extern sf::Text mytext2;
                mytext2.setCharacterSize(32);
                mydraw2(writer,79*14,500-32*i-4,sf::Color::White,sf::Color(80,60,98,255));
                i--;
                mytext2.setCharacterSize(24);




//                sprintf(writer,"LEVEL: COVERAGE:TOTAL=%10.7f%%",total_coverage);
//                mydraw2(writer,0,500-32*i,sf::Color(20,60,98,255),sf::Color::White);
//                sprintf(writer,"X=%10.5f%%,Y=%10.5f%%",coverage_x,coverage_y);
//                mydraw2(writer,690+54*12,500-32*i,sf::Color(20,60,98,255),sf::Color::White); i--;

                double tot_screens=(double)((int)((pixels_in_map+1919)/1920)) * (double)((int)((pixels_in_map+1079)/1080)) ;
                sprintf(writer,"MAP TOTAL:      %17.0f,---- %20.0f         %12.0f,--  ZOOM:  %d(%d)   MAP: %d/%d/(%d)",
                        pow((double)tiles_in_map,2),pow((double)pixels_in_map,2),
                        tot_screens,  SAS_ZOOM, SAS_MAX_ZOOM, mul+1,MUL_COUNTER,MUL_MATCH_LEVEL);
                mydraw2(writer,0,500-32*i,sf::Color(20,60,98,255),sf::Color::White);
                i--;

                tot_screens=(double)BITMAPSX*(double)BITMAPSY;
                sprintf(writer,"LEVEL TOTAL:         %17.4f %20.0f          %11.0f,--  LEVEL: %d",
                        (double)tiles_in_screenx*(double)tiles_in_screeny,
                        (double)pixels_in_screenx*(double)pixels_in_screeny,
                        tot_screens,level);
                mydraw2(writer,0,500-32*i,sf::Color(20,60,98,255),sf::Color::White);
                i--;

                /*
                                sprintf(writer,"RESOLUTION=%dx%d", pixels_in_screenx,pixels_in_screeny);
                                mydraw2(writer,770,500-32*i,sf::Color(20,60,98,255),sf::Color::White);
                                sprintf(writer,"(TOTAL PIXELS=%17.0f)",(double)pixels_in_screenx*(double)pixels_in_screeny);
                                mydraw2(writer,1190,500-32*i,sf::Color(20,60,98,255),sf::Color::White); i--;
                */


                /*
                                sprintf(writer,"MAP: ZOOM=%2d   TILES=%dx%d", SAS_ZOOM, tiles_in_map, tiles_in_map);
                                mydraw2(writer,0,500-32*i,sf::Color(20,60,98,255),sf::Color::White);
                                sprintf(writer,"(TOTAL=%12.0f)", (double)tiles_in_map*(double)tiles_in_map);
                                mydraw2(writer,480,500-32*i,sf::Color(20,60,98,255),sf::Color::White);
                                sprintf(writer,"RESOLUTION=%dx%d", pixels_in_map,pixels_in_map);
                                mydraw2(writer,770,500-32*i,sf::Color(20,60,98,255),sf::Color::White);

                                sprintf(writer,"(TOTAL PIXELS=%17.0f)", pow((double)pixels_in_map,2));
                                mydraw2(writer,1190,500-32*i,sf::Color(20,60,98,255),sf::Color::White); i--;
                */



//                int x=(int) (rel_pos_in_map_x_cur*(double)(pixels_in_map))-SAS_STARTX*256;
//                int y=(int) (rel_pos_in_map_y_cur*(double)(pixels_in_map))-SAS_STARTY*256 ;
//              int x=(int) (rel_pos_in_map_x_cur*(double)(pixels_in_map));
//              int y=(int) (rel_pos_in_map_y_cur*(double)(pixels_in_map));
//              sprintf(writer,"ABS.POSITION IN MAP X=%d,Y=%d",x,y);
//              mydraw2(writer,690,500-32*i,col,sf::Color::White); i--;

                sprintf(writer,"LEVELDIR: %s/map.z%d",LEVELDIR,SAS_ZOOM);
                mydraw2(writer,0,500-32*i,col,sf::Color::White);
                i--;

                char url[1000];
                if (SAS_ZOOM_DIRECTION<0)
                {
                    if (strcmp(SAS_ORDER,"XYZ")==0)
                        sprintf(url,SAS_URL,(int)tile_pacx,(int)tile_pacy,(int)(-SAS_ZOOM_DIRECTION-SAS_ZOOM));
                    else if (strcmp(SAS_ORDER,"ZXY")==0)
                        sprintf(url,SAS_URL,(int)(-SAS_ZOOM_DIRECTION-SAS_ZOOM),(int)tile_pacy,(int)tile_pacx);
                    else
                        sprintf(url,SAS_URL,(int)(-SAS_ZOOM_DIRECTION-SAS_ZOOM),(int)tile_pacx,(int)tile_pacy);
                }
                else
                {
                    if (strcmp(SAS_ORDER,"XYZ")==0)
                        sprintf(url,SAS_URL,(int)tile_pacx,(int)tile_pacy,(int)(SAS_ZOOM+SAS_ZOOM_DIRECTION));
                    else if (strcmp(SAS_ORDER,"ZXY")==0)
                        sprintf(url,SAS_URL,SAS_ZOOM+SAS_ZOOM_DIRECTION,(int)tile_pacy,(int)tile_pacx);
                    else
                        sprintf(url,SAS_URL,SAS_ZOOM+SAS_ZOOM_DIRECTION,(int)tile_pacx,(int)tile_pacy);
                }
                if (url[0]>='0' && url[0]<='9')
                    sprintf(writer,"TILE URL: %s",&url[1]);
                else
                    sprintf(writer,"TILE URL: %s",url);
                mydraw2(writer,0,500-32*i,col,sf::Color::White);
                i--;
                sprintf(writer,"STATUS THREADS: HELPME=%d,LOADER=%d,%d,%d WINDOW=%d,%d,%d KILL=%d,%d,%d ",
                        helpme,loader1_active,loader2_active,loader3_active,
                        window_1_active,window_2_active,window_3_active,
                        kill1,kill2,kill3);
                mydraw2(writer,0,500-32*i,col,sf::Color::White);
                i--;
                sprintf(writer,"GEODATA: %s",going_to);
                mydraw2(writer,0,500-32*i,col,sf::Color::White);
                i--;


//                sprintf(writer,"MAP: ZOOM=%d  TILES=%6dx%6d (TOTAL=%.0f)  RESOLUTION=%dx%d (TOTAL PIXELS=%.0f)", SAS_ZOOM, tiles_in_map, tiles_in_map, (double)tiles_in_map*(double)tiles_in_map, pixels_in_map, pixels_in_map, pow((double)pixels_in_map,2));                                    mydraw2(writer,0,500-32*i,sf::Color(20,60,98,255),sf::Color::White); i--;
//                sprintf(writer,"LEVEL:   MAX #TILES=%6.0fx%6.0f (TOTAL=%.0f)  RESOLUTION=%dx%d (TOTAL PIXELS=%.0f)",tiles_in_screenx,tiles_in_screeny,(double)tiles_in_screenx*(double)tiles_in_screeny, pixels_in_screenx,pixels_in_screeny,(double)pixels_in_screenx*(double)pixels_in_screeny);  mydraw2(writer,0,500-32*i,sf::Color(20,60,98,255),sf::Color::White); i--;

                /*                if (SAS_ZOOM_DIRECTION<0)
                                    sprintf(writer,"ZOOM LEVEL TILE DIR: %d",-SAS_ZOOM_DIRECTION-SAS_ZOOM);
                                else
                                    sprintf(writer,"ZOOM LEVEL TILE DIR: %d",SAS_ZOOM_DIRECTION+SAS_ZOOM);
                                mydraw2(writer,0,500-32*i,col,sf::Color::White); i--;
                */


            }
        }

        if (combine==1 && F2==1)
        {
            strcpy(writer,"COMBINING ON: (X/SHIFT-X LOADS AND COMBINES WITH CURRENT, Z/SHIFT-Z SAVES FROM CURSOR WITH MX=0,MY=0 AS UPPER LEFT CORNER)");
            draw2(writer,0,1080-64,sf::Color::Red,sf::Color::White);
        }
//joepie
        if (F2==1)
        {
            if (crop==1) {
                sf::FloatRect fr=sprite_from_crop.getGlobalBounds();

                sprintf(writer,"CROP SIZE: %d x %d  POS: (%d,%d) TO (%d,%d)",
                        (int)fr.width, (int)fr.height,
                        (int)fr.left, (int)fr.top,
                        (int)(fr.left+fr.width),(int)(fr.top+fr.height));
                draw2(writer,0,500+32*9,sf::Color::Blue,sf::Color::White);
            }

            if (ffmpegfile==0)
            {
                int abs_x,abs_y;
                if (ffmpeg_move==1)
                {
                    abs_x=((ffmpeg_posx));
                    abs_x=((int)abs_x+maxpixelsx)%maxpixelsx;

                    abs_y=((ffmpeg_posy));
                    abs_y=((int)abs_y+maxpixelsy)%maxpixelsy;
                }
                else
                {
                    abs_x=(-render_posx+render_picturex*1920+(1920/2) );
                    abs_x=((int)abs_x+maxpixelsx)%maxpixelsx;

                    abs_y=(-render_posy+render_picturey*1080+(1080/2 ) );
                    abs_y=((int)abs_y+maxpixelsy)%maxpixelsy;
                }
                int size_x=texture_from_ffmpeg.getSize().x;
                int size_y=texture_from_ffmpeg.getSize().y;
                int scale_x=texture_from_ffmpeg.getSize().x*sprite_from_ffmpeg.getScale().x;
                int scale_y=texture_from_ffmpeg.getSize().y*sprite_from_ffmpeg.getScale().y;
                extern float plot_abs_x,plot_abs_y;

                if (ffmpeg_move==1)
                    sprintf(writer,"SIZE: %d x %d SCALED: %d x %d POS: %d,%d TO %d,%d (%.6f,%.6f)",
                            size_x,size_y,
                            scale_x,scale_y,

                            (abs_x+maxpixelsx)%maxpixelsx,  (abs_y+maxpixelsy)%maxpixelsy,
                            (abs_x+scale_x+maxpixelsx-1)%maxpixelsx,(abs_y+scale_y+maxpixelsy-1)%maxpixelsy,

                            plot_abs_x,plot_abs_y
                           );
                else
                    sprintf(writer,"SIZE: %d x %d SCALED: %d x %d POS: %d,%d TO %d,%d (%.6f,%.6f)",
                            size_x,size_y,
                            scale_x,scale_y,

                            (abs_x-scale_x/2+maxpixelsx)%maxpixelsx,(abs_y-scale_y/2+maxpixelsy)%maxpixelsy,
                            (abs_x+scale_x/2+maxpixelsx-1)%maxpixelsx,(abs_y+scale_y/2+maxpixelsy-1)%maxpixelsy,

                            plot_abs_x,plot_abs_y
                           );
//                sprintf(writer,"PICTURE SIZE: %d x %d SCALED: %d x %d",
//                        texture_from_ffmpeg.getSize().x,texture_from_ffmpeg.getSize().y,
//                        (int)(texture_from_ffmpeg.getSize().x*sprite_from_ffmpeg.getScale().x),(int)(texture_from_ffmpeg.getSize().y*sprite_from_ffmpeg.getScale().y)
//                        );
                draw2(writer,0,500+5*32,sf::Color::Blue,sf::Color::White);

            }
            if (internetfile==0)
            {
                sprintf(writer,"PICTURE SIZE: %d x %d SCALED: %d x %d",texture_from_internet.getSize().x,texture_from_internet.getSize().y,
                        (int)(texture_from_internet.getSize().x*sprite_from_internet.getScale().x),(int)(texture_from_internet.getSize().y*sprite_from_internet.getScale().y));
                draw2(writer,0,500+32*6,sf::Color::Blue,sf::Color::White);
            }
            if (movie==0)
            {
                sprintf(writer,"MOVIE SIZE: %d x %d SCALED: %d x %d",texture_from_movie_new.getSize().x,texture_from_movie_new.getSize().y,
                        (int)(texture_from_movie_new.getSize().x*sprite_from_movie.getScale().x),(int)(texture_from_movie_new.getSize().y*sprite_from_movie.getScale().y));
                draw2(writer,0,500+32*7,sf::Color::Blue,sf::Color::White);
            }
            if (movie2==0)
            {
                sprintf(writer,"MOVIE SIZE: %d x %d SCALED: %d x %d",texture_from_movie2_new.getSize().x,texture_from_movie2_new.getSize().y,
                        (int)(texture_from_movie2_new.getSize().x*sprite_from_movie2.getScale().x),(int)(texture_from_movie2_new.getSize().y*sprite_from_movie2.getScale().y));
                draw2(writer,0,500+32*8,sf::Color::Blue,sf::Color::White);
            }
        }

        static int xoff=100;
        static int yoff=1080;

        if (F1==1)
        {
            if (yoff>200)
                yoff=yoff-10;
        }
        if (F1==0)
        {
            if (yoff<1080)
                yoff=yoff+10;
        }
        if (yoff<1080)
        {
            int i=0;
            text.setRotation((yoff-200)/5);
            text.setCharacterSize(18);

            strcpy(writer,"a,s,d,w OR j,k,l,i OR CURSOR KEYS : MOVE");
            draw2(writer,xoff,yoff+i*22,sf::Color::Red,sf::Color::White);
            i++;
            strcpy(writer,"TAB : EDIT MODE  ON / OFF   '.' : LOOKAHEAD ON / OFF WHEN DRAWING MAZE   (SET EDIT MODE ON/OFF IN GHOST FOLLOW MODE EFFECTS SCREEN SMOOTH MOTION)");
            draw2(writer,xoff,yoff+i*22,sf::Color::Red,sf::Color::White);
            i++;
            strcpy(writer,"TAB : EDIT MODE : PEN  DRAW / ERASE / MOVE     p : BIG POINT  ON / OFF");
            draw2(writer,xoff,yoff+i*22,sf::Color::Red,sf::Color::White);
            i++;
            strcpy(writer,"q : SAVE BITMAPS ON/OFF   SHIFT-d : PLOT MAZE ON/OFF   SHIFT-s : SAVE BITMAPS   SHIFT-l : LOADBITMAPS   SHIFT-o : BACKGROUND ON/OFF");
            draw2(writer,xoff,yoff+i*22,sf::Color::Red,sf::Color::White);
            i++;
            strcpy(writer,"[ ] : LEVEL  - / +    /    SELECT GHOST IN FOLLOW MODE ('f'/'F')    { } : SPEED GHOST IN FOLLOW MODE +/-");
            draw2(writer,xoff,yoff+i*22,sf::Color::Red,sf::Color::White);
            i++;
            strcpy(writer,"z : SAVE MAZE[LEVEL].DAT ( SHIFT-z : SAVE MAP[LEVEL].DAT EXTRA BACKUP )");
            draw2(writer,xoff,yoff+i*22,sf::Color::Red,sf::Color::White);
            i++;
            strcpy(writer,"x : LOAD/COMBINE MAZE[LEVEL].DAT UNDER SELECTED LEVEL ( SHIFT-X : SAVE MAP[LEVEL].DAT EXTRA BACKUP )");
            draw2(writer,xoff,yoff+i*22,sf::Color::Red,sf::Color::White);
            i++;
            strcpy(writer,"c : TOGGLE COMBINE ON / OFF ( COMBINES CURRENT MAP FROM CURSOR WHEN LOADING WITH x / SHIFT-X )");
            draw2(writer,xoff,yoff+i*22,sf::Color::Red,sf::Color::White);
            i++;
            strcpy(writer,"c : (OR) TOGGLE SAVE FROM CURSOR ON / OFF ( MAKES CURSOR POSITION MX=0,MY=0 WHEN SAVING WITH z / SHIFT-z )");
            draw2(writer,xoff,yoff+i*22,sf::Color::Red,sf::Color::White);
            i++;
            strcpy(writer,"DELETE : CLEAR MAP   ALT-DELETE : CLEAR BITMAPS BACKGROUND (.PNG FILES WILL BE GONE!!! BACKUP THEM TO KEEP BACKGROUND)");
            draw2(writer,xoff,yoff+i*22,sf::Color::Red,sf::Color::White);
            i++;
            strcpy(writer,"0 : SCREENSHOT   9 : CLEAR SCREEN   r : RECORDING (NEED FFMPEG.EXE IN PATH)   SHIFT-R : PAUSE RECORDING");
            draw2(writer,xoff,yoff+i*22,sf::Color::Red,sf::Color::White);
            i++;
            strcpy(writer,"ESCAPE : QUIT/FRUSTRATED    n : NEXT LEVEL   m : MAZE MODE  LEVEL / FULL / OFF    t : MAZE TYPE  LEVEL / MAZE");
            draw2(writer,xoff,yoff+i*22,sf::Color::Red,sf::Color::White);
            i++;
            strcpy(writer,"F2 : DEBUG INFO :  ON / OFF   F3 : HORIZONTAL SYNC :  ON / OFF    ");
            draw2(writer,xoff,yoff+i*22,sf::Color::Red,sf::Color::White);
            i++;
            strcpy(writer,"F4 : SPEED ADJUST :  ON / OFF  (ALWAYS ACTIVE IN MULTIPLAYER MODE)");
            draw2(writer,xoff,yoff+i*22,sf::Color::Red,sf::Color::White);
            i++;
            strcpy(writer,"F5 : GOTO PARTNER     F6 : GET PARTNER   ',' : PLAY MODE ON/OFF WHEN SHIFT-P/SHIFT-I/SHIFT-M USED ");
            draw2(writer,xoff,yoff+i*22,sf::Color::Red,sf::Color::White);
            i++;
            strcpy(writer,"SHIFT-P/SHIFT-I/SHIFT-M/SHIFT-B : LOAD PICTURE/MOVIE FROM INTERNET/DIR SMALL/LARGE   F7 : FRONT/BACK   F8 : PLOT   v : EXPERIMENTAL" );
            draw2(writer,xoff,yoff+i*22,sf::Color::Red,sf::Color::White);
            i++;
            strcpy(writer,"CTRL-P/CTRL-I/CTRL-M/CTRL-B : FIX POSITION ON/OFF" );
            draw2(writer,xoff,yoff+i*22,sf::Color::Red,sf::Color::White);
            i++;
            strcpy(writer,"ALT-P/ALT-I/ALT-M/ALT-B : ROTATE PICTURE DIR/INTERNET/MOVIE ON/OFF   PAGE-UP/-DOWN : ROTATE   ALT-PAGE-UP/-DOWN : ROTATION SPEED");
            draw2(writer,xoff,yoff+i*22,sf::Color::Red,sf::Color::White);
            i++;
            strcpy(writer,"CTRL-A : ADD BORDER  CTRL-E : SOFTEN EDGES  CTRL-C : SIZE TO SCALE  CTRL-R : MOVIE TO (SHIFT-P) PICTURE  CTRL-S : PLOT SHADER INTO PICTURE INSTEAD OF BACKGROUND");
            draw2(writer,xoff,yoff+i*22,sf::Color::Red,sf::Color::White);
            i++;
            strcpy(writer,"SHIFT-A : DARK->  SHIFT-W : WHITE->  SHIFT->T BLACK->  SHIFT-C : COLOR TO->TRANSPARANT");
            draw2(writer,xoff,yoff+i*22,sf::Color::Red,sf::Color::White);
            i++;
            strcpy(writer,"CTRL-PAGE-UP/-DOWN : SIZE PICTURE/MOVIE +/-    SHIFT-PAGE-UP/-DOWN : SIZE PICTURE/MOVIE +/- FAST" );
            draw2(writer,xoff,yoff+i*22,sf::Color::Red,sf::Color::White);
            i++;
            strcpy(writer,"SHIFT-V : BLENDING   SHIFT-V(2x) : CUSTOM BLENDING   ALT-SPACE : ROTATION=OFF   SHIFT-SPACE : SCALE=OFF   CTRL-SPACE : FIXED=OFF" );
            draw2(writer,xoff,yoff+i*22,sf::Color::Red,sf::Color::White);
            i++;
            strcpy(writer,"v : BLEND ON MOVIE (FIT) (SHIFT-M) WITH BLENDINGPICTURE (SHIFT-P)  / v(2x) BLEND ON MOVIE (MAX)  / OFF" );
            draw2(writer,xoff,yoff+i*22,sf::Color::Red,sf::Color::White);
            i++;
            strcpy(writer,"WHEN BLENDING=ON LOAD FROM BLENDINGPICTUREDIR WITH SHIFT-P   '+' or '=' / '-' : BLENDINGMODE UP/DOWN   '1'-'6' / '!'-'^' CUSTOM SETTINGS UP/DOWN");
            draw2(writer,xoff,yoff+i*22,sf::Color::Red,sf::Color::White);
            i++;
            strcpy(writer,"F9 / F10 :  GET / SET POSITION 1     F11 / F12 :  GET / SET POSITION 2    HOME : GOTO STARTING POS   ALT-HOME : GOTO X=0 Y=0");
            draw2(writer,xoff,yoff+i*22,sf::Color::Red,sf::Color::White);
            i++;
            strcpy(writer,"+/= / - : ADD / REMOVE GHOSTS   e : GHOST EAT MODE ON/OFF     g : GHOSTS ON/OFF");
            draw2(writer,xoff,yoff+i*22,sf::Color::Red,sf::Color::White);
            i++;
            strcpy(writer,"SHIFT-K : DRAW MODE MIRROR 3X / 1X / OFF   1-4 : DIFFICULTY    SHADERS : ALT-F1 TO ALT-F7");
            draw2(writer,xoff,yoff+i*22,sf::Color::Red,sf::Color::White);
            i++;
            strcpy(writer,"SHIFT-F8 : REVERSE PLOT SCREEN INTO SHIFT-P PICTURE  ALT-S : SMOOTH TEXTURES ON/OFF  ALT-F8 : SAVE PICTURE (SHIFT-I/SHIFT-P) TO PICTUREDIR");
            draw2(writer,xoff,yoff+i*22,sf::Color::Red,sf::Color::White);
            i++;
            strcpy(writer,"START FROM COMMAND LINE : ");
            strcat(writer,commandline);
            draw2(commandline,xoff,yoff+i*22,sf::Color::Red,sf::Color::White);
            i++;

            text.setCharacterSize(24);
            text.setRotation(0.0);

        }

        static int on_off=0;
//        if (F2==1 && (error_flag==2 || on_off==1 ))
        if (F2==1)
        {
            if (error_flag_s>=1)
            {
                error_flag_s=0;
                error_flag=1;
                strcpy(error_msg,error_msg_s);
            }
            if (error_flag>=1 || on_off==1)
            {

                static int counter;
                on_off=1;
                if (error_flag==1)
                    counter=250;
                else if (error_flag==2)
                    counter=1000;
                if (counter>0)
                    counter--;
                if (counter==0)
                {
                    shift=0;
                    on_off=0;
                    again1=0;
                    again2=0;
                    overwrite1=0;
                    overwrite2=0;
                    first1=0;
                    first2=0;
                    strcpy(error_msg,"");
                }
//                text.setCharacterSize(36);
                draw2(error_msg,0,1079-36-72,sf::Color(50,50,0,255),sf::Color(255,127,0,255));
//                text.setCharacterSize(24);
                if (error_flag>=0 || record_screen==1)
                    error_flag=0;
            }
        }


        if (F2==1)
        {
            static int on_off2=0;
            if (error_flag2>=1 || on_off2==1)
            {
                static int counter;
                on_off2=1;
                if (error_flag2==1)
                    counter=300;
                else if (error_flag2==2)
                    counter=10;
                counter--;
                if (counter==0)
                {
                    shift=0;
                    on_off2=0;
                    strcpy(error_msg2,"LOADED: ");
                }
                draw2(error_msg2,0,1079-36*4,sf::Color(50,50,0,255),sf::Color(255,255,0,255));
                if (error_flag2==1 || record_screen==1)
                    error_flag2=0;
            }

            static int on_off3=0;
            if (error_flag3>=1 || on_off3==1)
            {
                static int counter;
                on_off3=1;
                if (error_flag3==1)
                    counter=300;
                else if (error_flag3==2)
                    counter=10;
                counter--;
                if (counter==0)
                {
                    on_off3=0;
                    strcpy(error_msg3,"SAVED: ");
                }
                draw2(error_msg3,0,1079-36*5,sf::Color(50,50,0,255),sf::Color(255,255,0,255));
                if (error_flag3==1 || record_screen==1)
                    error_flag3=0;
            }

            static int on_off4=0;
            if (error_flag4>=1 || on_off4==1)
            {
                static int counter;
                on_off4=1;
                if (error_flag4==1)
                    counter=300;
                else if (error_flag4==2)
                    counter=10;
                counter--;
                if (counter==0)
                {
                    on_off4=0;
                    strcpy(error_msg4,"CREATED: ");
                }
                draw2(error_msg4,0,1079-36*6,sf::Color(50,50,0,255),sf::Color(255,255,0,255));
                if (error_flag4==1 || record_screen==1 && blending==0)
                    error_flag4=0;
            }

            static int on_off5=0;
            if (error_flag5>=1 || on_off5==1)
            {
                static int counter;
                on_off5=1;
                if (error_flag5==1)
                    counter=300;
                else if (error_flag5==2)
                    counter=10;
                counter--;
                if (counter==0)
                {
                    on_off5=0;
                    strcpy(error_msg5,"DELETED: ");
                }
                draw2(error_msg5,0,1079-36*7,sf::Color(50,50,0,255),sf::Color(255,255,0,255));
                if (error_flag5==1 || record_screen==1 && blending==0)
                    error_flag5=0;
            }
        }

        if (goexit==1)
        {
            text.setCharacterSize(144);
            draw2((char*)"QUIT (Y/N)",490,430,sf::Color(255,0,0,128),sf::Color::White);
            text.setCharacterSize(24);
        }


        if (F2==1)
        {
            if (movieextern==0 && recording_type==1)
            {
                if (record_screen==1)
                {
                    if (record_pause==1)
                    {
                        sprintf(line,"RECORDING 'b' FRAME %05d TIME=%s, PAUZED",record_screen_num,seconds_to_time(recording_time));
                    }
                    else
                    {
                        sprintf(line,"RECORDING 'b' FRAME %05d TIME=%s",record_screen_num,seconds_to_time(recording_time));
                    }
                    draw2(line,700,0,sf::Color::Red,sf::Color::White);
                }
                else
                {
                    sprintf(line,"RECORD 'b' SELECTED, PRESS 'r' to RECORD",record_screen_num,seconds_to_time(recording_time));
                    draw2(line,700,0,sf::Color::Red,sf::Color::White);
                }
            }
            else
            {
                if (record_screen==1)
                {
                    if (record_pause==1)
                    {
                        sprintf(line,"RECORDING FRAME %05d TIME=%s, PAUZED",record_screen_num,seconds_to_time(recording_time));
                    }
                    else
                    {
                        sprintf(line,"RECORDING FRAME %05d TIME=%s",record_screen_num,seconds_to_time(recording_time));
                    }
                    draw2(line,700,0,sf::Color::Red,sf::Color::White);
                }
            }
        }

//        plot_ghosts();

        SFMLView1.setActive(true);

        if (go_download==1)
        {
            do_command(GO_DOWNLOAD);
        }
        if (go_list==1)
        {
            static int skipfirst=1;
            if (!skipfirst)
                do_command(GO_LIST);
            else
                skipfirst=0;
        }
        if (burn_next_sub_ready>0)
        {
            burn_next_sub_ready_mutex.lock();
            if (burn_next_sub_ready==1)
            {
//                if (movieextern==0) playing_end();
            }
            burn_next_sub_ready++;
            if (burn_next_sub_ready>20)
            {
                burn_next_sub_ready=0;
                start_burn_next_sub_thread();
                //            burn_next_sub();
            }
            burn_next_sub_ready_mutex.unlock();
        }

        animate_lock.lock();
        if (something_to_do)
        {
            print_to_screen(pts.var_font,
                            pts.text_to_print,
                            pts.font_size,
                            pts.paint_in,
                            pts.paint_out,
                            pts.paint_back,
                            pts.outline,
                            pts.text_type);
            something_to_do=0;
        }
extern bool hold_voxels;
extern int scan_max_x;
extern int scan_min_x;
extern int scan_max_z;
extern int scan_min_z;

//        MUTEX_MCEDITOR.lock();

        if (update_request==5) {
            update_request=0;
        }
        if (update_request==4) {
            get_position3();
            jump_ready=1;
            forced_jump=1;
            ReadBitmaps2();
            follow_ghost_pos();

            update_request=5;
        }


        static int position1x_wanted=position1x;
        static int position1y_wanted=position1y;
        static int wanted_position1x=position1x;
        static int wanted_position1y=position1y;
        static bool start_to_move=false;

        static bool update_later=false;
        static int savie_savie=0;
        if (savie_savie!=0) {
            savie_savie--;
            if (savie_savie==0) SAVEALLBITMAPS();
        }

        if (update_later) {
            update_MC(scan_image,scan_x,scan_z);
            update_request=0;
            update_later=false;
            if (set_save) {
                static int cnt=60;
                cnt--;
                if (cnt==0) {
                    cnt=10;
                    savie_savie=180;
                    set_save=false;
                }
            }
        }

        if (update_request==2 || update_request==3) {
            float fspeedx_old=fspeedx;
            float fspeedy_old=fspeedy;
            int speedx_old=speedx;
            int speedy_old=speedy;

//            int old_positionx=(render_picturex*1920-render_posx);
//            int old_positiony=(render_picturey*1080-render_posy);

            static int not_next=1;
            pen_mode==2;
            if (not_next) {
                if (update_request==3) update_MC(scan_image,scan_x,scan_z);
            } else {
                if (update_request==3) not_next=0; else not_next=1;
            }

            if (!hold_voxels) {
/*
                static float n_x=scan_x;
                static float n_z=scan_z;
                static int level_hold=level;
extern std::string region_filename;
                if (update_request==3) {
                    n_x=scan_x;
                    n_z=scan_z;
                }
                n_x=(scan_max_x+scan_min_x)/2.0;
                n_x= ( (float)scan_x+(float)n_x*3.0 )/4.0;
                n_z= ( (float)scan_z+(float)n_z*3.0 )/4.0;
                scan_x=n_x;
                scan_z=n_z;

//                int xc=sprite_from_canvas.getScale().x;
                float zc=sprite_from_canvas.getScale().x;

                if (abs(n_x - scan_x) > 3) n_x=scan_x;
                if (abs(n_z - scan_z) > 3) n_z=scan_z;

                int x=(int)( ( (LONG64)(n_x)*512  +256  + (LONG64)maxpixelsx*100 ) % (LONG64)maxpixelsx );
                int y=(int)( ( (LONG64)(n_z)*512  +256-offset_y  + (LONG64)maxpixelsy*100 ) % (LONG64)maxpixelsy );
*/
                float zc=sprite_from_canvas.getScale().x;
//                int offset_y=(zc/0.02)*512.0 - 512;
                int offset_y=(zc/0.02)*512.0;
                int x=(int)( ( (LONG64)(scan_x)*512  +256+ (LONG64)maxpixelsx*1000 ) % (LONG64)maxpixelsx );
                int y=(int)( ( (LONG64)(scan_z)*512  +256 + 512 - offset_y + (LONG64)maxpixelsy*1000 ) % (LONG64)maxpixelsy );

                wanted_position1x=(x+maxpixelsx*2)%maxpixelsx;
                wanted_position1y=(y+maxpixelsy*2)%maxpixelsy;

                position1x_wanted=wanted_position1x;
                position1y_wanted=wanted_position1y;
//                position1x=(picturex*1920-posx);
//                position1y=(picturey*1080-posy);

                start_to_move=true;
            } else {
                position1x=(picturex*1920-posx);
                position1y=(picturey*1080-posy);
                fspeedx=fspeedx_old;
                fspeedy=fspeedy_old;
                speedx=speedx_old;
                speedy=speedy_old;
                get_position1();
            }
//            if (update_request==2) update_request=0;
            if (update_request==2) {
                update_later=true;
            }
        }
extern bool MAKE_NBT;
extern bool make_regions;
        if ( ( (burn && mirror==4 && crossing==2) )  && start_to_move) {
//        if ( ( (burn && mirror==4 && crossing==2) || MAKE_NBT || make_regions)  && start_to_move) {
            if (kp.getElapsedTime()>sf::seconds(20)) {
//                set_position1();
                position1x=(picturex*1920-posx);
                position1y=(picturey*1080-posy);

                int verschilx=position1x_wanted-position1x;
                int verschily=position1y_wanted-position1y;
                if (verschilx<=-maxpixelsx/2)   verschilx=verschilx+maxpixelsx; else if (verschilx>maxpixelsx/2) verschilx=verschilx-maxpixelsx;
                if (verschily<=-maxpixelsy/2)   verschily=verschily+maxpixelsy; else if (verschily>maxpixelsy/2) verschily=verschily-maxpixelsy;


//                position1x=position1x_wanted;
//                position1y=position1y_wanted;

//                follow_ghost_pos();
                float dist=sqrt(verschilx*verschilx+verschily*verschily);

                picturex=position1x_wanted/1920;
                posx=position1x_wanted-1920*picturex;

                picturey=position1y_wanted/1080;
                posy=position1y_wanted-1080*picturey;

                posx=-posx;
                posy=-posy;

                fposx=posx;
                fposy=posy;

//                get_position1();
                if (dist>1000) long_jump=1;
                start_to_move=false;
            }
        } else {
            start_to_move=false;
        }
//        MUTEX_MCEDITOR.unlock();
        if (update_request==3) {
            cleanupbitmaps_mazes();
            ReadBitmaps4();
            update_request=2;
        }
        if (read_request==1) {
            read_one_plot(read_x,read_y,read_image);
            position1x=read_x-1920/2+256+5;
            position1y=read_y-1080/2+256+5;
            get_position1();
            read_request=0;
        }


        animate_lock.unlock();


/*
        render_locker.lock();
        for (int i=0; i<10; i++) {
            if (ready_to_render[i] && combine==1) {
                expres(i);
                rendering=1;
                render_now=1;
            }
        }
        if (render_now==0 && rendering==1) {
//            reset_all();
            rendering=0;
        }
        render_locker.unlock();
*/
        SFMLView1.setActive(false);
extern sf::Mutex window_recording;
        window_recording.unlock();


        SFMLView1.display();

        window_recording.lock();

        if (happening==1) {
            happening=0;
            happening_counter=0;
        }
        happening_counter++;
        static int posx_o;
        static int posy_o;
        if (posx!=posx_o || posy!=posy_o) {
            happening_counter=0;
            posx_o=posx;
            posy_o=posy;
        }
        extern bool running_3d[];
        int slow_down=false;

        static int anti_slow=300;
        if (!dont_slow_down) {
            for (int i=0; i<10; i++) {
                if (running_3d[i]) {
                    slow_down=true;
                    break;
                }
            }
        } else {
            slow_down=false;
        }
        if (kp.getElapsedTime().asSeconds() > 5.0) {

            if (slow_down) {
                if (SFMLView1.hasFocus() || anti_slow-->0) slow_down=false;
                wierdo_mutex.lock();
                if (wierdo_requests_ready.size()>0) {
                    std::vector<glm::ivec2>::iterator it=wierdo_requests_ready.begin();
                    glm::ivec2 v=*it;
                    if (used[v.x][v.y]==1) {
                        totalused--;
                    }
                    used_maxinmem[used2[v.x][v.y]]=0;
                    used2[v.x][v.y]=0;
                    used[v.x][v.y]=0;
                    files[v.x][v.y]=1;
                    if (plot_all) {
                        picturex=(v.x+maxpicturex)%maxpicturex;
                        picturey=(v.y+maxpicturey-3)%maxpicturey;
                    } else {
                        picturex=(v.x+maxpicturex)%maxpicturex;
                        picturey=(v.y+maxpicturey)%maxpicturey;
                    }
                    posx=0;
                    posy=0;
                    fposx=0;
                    fposy=0;
                    follow_ghost_pos();
                    anti_slow=600;
    //                ReadOneBitmap(v.x,v.y);
    //                printf("Updating %2d,%2d\n",v.x,v.y);

                        ReadBitmaps2();
                        ReadBitmaps4();
                    wierdo_requests_ready.erase(it);
                }
                wierdo_mutex.unlock();
            }
            if (MCEDITOR_running || slow_down) {
                shut_up=1;
                if (!movie==0 && !movie2==0 && jump_ready==1 && read_request==0 && update_request==0 && happening_counter>1000) {
                    MUTEX_MCEDITOR.unlock();
//                    if (totalchanged>0 && !(read_request || update_request))
//                    {
//                        DONTSAVEFILES=0;
//                        SAVEALLBITMAPS();

//                        merge_back_to_front();
//                        happening_counter=0;
//                    }
                    for (int t=0; t<20; t++) {
                        sf::sleep(sf::milliseconds(50));
                        MUTEX_MCEDITOR.lock();
                        if (read_request || update_request) {
                            MUTEX_MCEDITOR.unlock();
                            break;
                        }
                        MUTEX_MCEDITOR.unlock();
                        float sc=sin(run_time/10.0)/10.0;
                        if (sc>0.8) {
    //                        float sc_adj=cos((sc-0.8)*5.0*PI)/10.0+1.0;
    //                        sprite_from_ffmpeg.setScale(sc_adj,sc_adj);
                        }
                    }
                    if (crossing==0) {
                        if (handler[FFMPEG_SELECT].blending==0) handler[FFMPEG_SELECT].blending=1;
                        else handler[FFMPEG_SELECT].blending=0;
                    } else handler[FFMPEG_SELECT].blending=0;
                }
                else {
                    if (crossing!=3) {
                        MUTEX_MCEDITOR.unlock();
                        sf::sleep(sf::milliseconds(1));
                        MUTEX_MCEDITOR.lock();
                    }
                }
                monitor_off=1;
                static double old_smooth_x=0,old_smooth_y=0;
                if ( jump_ready==0 && ((int)(smooth_x*10.0+0.5)==(int)(old_smooth_x*10.0+0.5) && (int)(smooth_y*10.0+0.5)==(int)(old_smooth_y*10.0+0.5)) ) {
                    jump_ready=1;
                    forced_jump=1;
                    ReadBitmaps2();
                    follow_ghost_pos();
                } else if (jump_ready==0) {
                    happening_counter=0;
                }
                old_smooth_x=smooth_x;
                old_smooth_y=smooth_y;
                monitor_off=1;
            }
        }
        frame_counter++;

        burn_next_sub_ready_mutex.lock();
        do_the_recording_stuff();
        burn_next_sub_ready_mutex.unlock();
    }

    umicrosec = clock_frame.restart().asMicroseconds();
    umicrosec_total+=umicrosec;

    frames++;
    if (frames==20)
    {
        if (umicrosec_total!=0)
            fps_float=20000000.0/(float)umicrosec_total;
        if (umicrosec_total!=0)
            framespersecond=20000000/umicrosec_total;

        if (connected==1 || F4==1)
            fspeed_adjust=(60.0/20.0*(float)umicrosec_total)/1000000.0;
        else
            fspeed_adjust=1.0;

        umicrosec_total=0;
        frames=0;
    }

    return;
}

// add -U__STRICT_ANSI__ to compiler settings -> other compiler options!!!! (popen() function for ffmpeg recording).
// add SFML_STATIC to compiler settings -> #defines
//#pragma comment(lib,"ws2_32.lib") don't know.
extern sf::Image Inter;

void load_next_ffmpeg()
{
    char naam[2000];
    ffmpegfile=1;
//        size_ffmpeg=1;
//        sprite_from_ffmpeg.setScale(1.0,1.0);
//        scale_now=1.0;
    GETPICTURE(naam);
    if (file_exists(naam))
    {
        if (Inter.loadFromFile(naam))
        {
            if (texture_from_ffmpeg.loadFromImage(Inter))
            {
                ffmpegfile=0;
            }
            else
            {
                printf("FAILED\n");
                savedata((char*)"failed loading1, to large? Then remove from list.",0);
            }
        }
        else
        {
            printf("FAILED\n");
            savedata((char*)"failed loading2, to large? Then remove from list.",0);
        }
    }
    else
    {
        printf("\nFAILED. FILE DOES NOT EXIST\n");
        savedata((char*)"failed loading, file does not exists: ",0);
        savedata((char*)naam,0);
    }
//        Inter.create(0,0);
    if (ffmpegfile==0)
    {
        texture_from_ffmpeg.setRepeated(TRUE);
        if (smooth==1)
            texture_from_ffmpeg.setSmooth(TRUE);
        else
            texture_from_ffmpeg.setSmooth(FALSE);

//            make_white_transparant(&texture_from_ffmpeg);


                    sprite_from_ffmpeg.setTextureRect( { 0,0,(int)texture_from_ffmpeg.getSize().x, (int)texture_from_ffmpeg.getSize().y } );
                    soften_edge(&texture_from_ffmpeg);
                    if (ffmpegfile==1) return;

                    sprite_from_ffmpeg.setTextureRect( { 0,0,(int)texture_from_ffmpeg.getSize().x, (int)texture_from_ffmpeg.getSize().y } );
                    add_border(&texture_from_ffmpeg);
                    if (ffmpegfile==1) return;

                    sprite_from_ffmpeg.setTextureRect( { 0,0,(int)texture_from_ffmpeg.getSize().x, (int)texture_from_ffmpeg.getSize().y } );
                    soften_edge(&texture_from_ffmpeg);
                    if (ffmpegfile==1) return;

                    sprite_from_ffmpeg.setTextureRect( { 0,0,(int)texture_from_ffmpeg.getSize().x, (int)texture_from_ffmpeg.getSize().y } );

                    if (smooth==1) texture_from_ffmpeg.setSmooth(TRUE);
                    else texture_from_ffmpeg.setSmooth(FALSE);
                    texture_from_ffmpeg.setRepeated(TRUE);


//            new_scale=0.6*scale_now * (1.0+sin(run_time*fspeed)/2.0);

                    setffmpegfile();
                    texture_from_ffmpeg.generateMipmap();
    }
    shift=0;
    scale_now_adj=(1000.0/(float)texture_from_ffmpeg.getSize().x);
    new_scale=0.6*scale_now * (1.0+sin(run_time*fspeed)/2.0) * scale_now_adj;
}

char internet_naam[2000]="";

void load_next_internet()
{
    internetfile=1;
//        size_internet=1;
//        sprite_from_internet.setScale(1.0,1.0);
//        scale_now=1.0;


    /*
            GETPICTURE(naam);
            if (file_exists(naam))
            {
                if (Inter.loadFromFile(naam)) {
                    if (texture_from_internet.loadFromImage(Inter))
                    {
                        internetfile=0;
                    }
                    else
                    {
                        printf("FAILED\n");
                        savedata((char*)"failed loading1, to large? Then remove from list.",0);
                    }
                } else {
                    printf("FAILED\n");
                    savedata((char*)"failed loading2, to large? Then remove from list.",0);
                }
            } else {
                printf("\nFAILED. FILE DOES NOT EXIST\n");
                savedata((char*)"failed loading, file does not exists: ",0);
                savedata((char*)naam,0);
            }
    */



    internetfile=GetFileFromInternet(internet_naam);
    if (internetfile==0)
    {
        sprintf(error_msg2,"LOADING FROM INTERNET OK: %s",internet_naam);
        error_flag2=1;
    }
    else
    {
        sprintf(error_msg2,"LOADING FROM INTERNET FAILED: %s",internet_naam);
        error_flag2=1;
        printf("%s\n",error_msg2);
        savedata(error_msg2,0);
    }
//        Inter.create(0,0);


    if (internetfile==0)
    {
        texture_from_internet.setRepeated(TRUE);
        if (smooth==1)
            texture_from_internet.setSmooth(TRUE);
        else
            texture_from_internet.setSmooth(FALSE);
//            rotation_ffmpeg=0.0;
//            rot_speed_ffmpeg=0.0;
//            sprite_from_ffmpeg.setTexture(texture_from_ffmpeg,false);
//            sprite_from_ffmpeg.setScale(1.0,1.0);
//            scale_now=1.0;

        sprite_from_internet.setTextureRect( { 0,0,(int)texture_from_internet.getSize().x, (int)texture_from_internet.getSize().y } );
        soften_edge(&texture_from_internet);
        if (internetfile==1)
            return;

        sprite_from_internet.setTextureRect( { 0,0,(int)texture_from_internet.getSize().x, (int)texture_from_internet.getSize().y } );
        add_border(&texture_from_internet);
        if (internetfile==1)
            return;

        sprite_from_internet.setTextureRect( { 0,0,(int)texture_from_internet.getSize().x, (int)texture_from_internet.getSize().y } );
        soften_edge(&texture_from_internet);
        if (internetfile==1)
            return;

        sprite_from_internet.setTextureRect( { 0,0,(int)texture_from_internet.getSize().x, (int)texture_from_internet.getSize().y } );

        if (smooth==1)
            texture_from_internet.setSmooth(TRUE);
        else
            texture_from_internet.setSmooth(FALSE);
        texture_from_internet.setRepeated(TRUE);

        /*
                    if (texture_from_internet.getSize().x>2000) {

                        old_internet_scale=scale_now;
                        scale_now=1.0/((float)texture_from_internet.getSize().x/2000);
                        new_scale=0.6*scale_now * (1.0+sin(run_time*fspeed)/2.0);
                        sprite_from_internet.setScale(new_scale,new_scale);

                    } else {
                        scale_now=old_internet_scale;
                        new_scale=0.6*scale_now * (1.0+sin(run_time*fspeed)/2.0);
                        sprite_from_internet.setScale(new_scale,new_scale);
                    }
        */
        scale_now_adj=(1000.0/(float)texture_from_internet.getSize().x);
        new_scale=0.6*scale_now * (1.0+sin(run_time*fspeed)/2.0) * scale_now_adj;
        setinternetfile();
    }
    shift=0;
}

size_t str_format_int_grouped(char dst[32])
{
    char src[32];
    char *p_src = src;
    char *p_dst = dst;

    strcpy(src,dst);
    const char separator = ',';
    int num_len, commas;

    num_len = strlen(src);

    if (*p_src == '-')
    {
        *p_dst++ = *p_src++;
        num_len--;
    }

    for (commas = 2 - num_len % 3; *p_src; commas = (commas + 1) % 3)
    {
        *p_dst++ = *p_src++;
        if (commas == 1)
        {
            *p_dst++ = separator;
        }
    }
    *--p_dst = '\0';

    return (size_t)(p_dst - dst);
}

void check_memory()
{
    PROCESS_MEMORY_COUNTERS memory;

//    PROCESS_MEMORY_COUNTERS memory_diff;
    GetProcessMemoryInfo(GetCurrentProcess(), &memory, sizeof(memory));
    static PROCESS_MEMORY_COUNTERS memory_old=memory;

    long long memory_diff_cb                          =(long long)memory.cb                          - (long long)memory_old.cb;
    long long memory_diff_PageFaultCount              =(long long)memory.PageFaultCount              - (long long)memory_old.PageFaultCount;
    long long memory_diff_PeakWorkingSetSize          =(long long)memory.PeakWorkingSetSize          - (long long)memory_old.PeakWorkingSetSize;
    long long memory_diff_WorkingSetSize              =(long long)memory.WorkingSetSize              - (long long)memory_old.WorkingSetSize;
    long long memory_diff_QuotaPeakPagedPoolUsage     =(long long)memory.QuotaPeakPagedPoolUsage     - (long long)memory_old.QuotaPeakPagedPoolUsage;
    long long memory_diff_QuotaPagedPoolUsage         =(long long)memory.QuotaPagedPoolUsage         - (long long)memory_old.QuotaPagedPoolUsage;
    long long memory_diff_QuotaPeakNonPagedPoolUsage  =(long long)memory.QuotaPeakNonPagedPoolUsage  - (long long)memory_old.QuotaPeakNonPagedPoolUsage;
    long long memory_diff_QuotaNonPagedPoolUsage      =(long long)memory.QuotaNonPagedPoolUsage      - (long long)memory_old.QuotaNonPagedPoolUsage;
    long long memory_diff_PagefileUsage               =(long long)memory.PagefileUsage               - (long long)memory_old.PagefileUsage;
    long long memory_diff_PeakPagefileUsage           =(long long)memory.PeakPagefileUsage           - (long long)memory_old.PeakPagefileUsage;

    int addx=500,addy=180+32;
    sprintf(writer,"                        cb = ");
    draw3(writer,addx,addy,sf::Color(0,140,20,255),sf::Color::White);
    addy+=32;
    sprintf(writer,"            PageFaultCount = ");
    draw3(writer,addx,addy,sf::Color(0,140,20,255),sf::Color::White);
    addy+=32;
    sprintf(writer,"            WorkingSetSize = ");
    draw3(writer,addx,addy,sf::Color(0,140,20,255),sf::Color::White);
    addy+=32;
    sprintf(writer,"        PeakWorkingSetSize = ");
    draw3(writer,addx,addy,sf::Color(0,140,20,255),sf::Color::White);
    addy+=32;
    sprintf(writer,"       QuotaPagedPoolUsage = ");
    draw3(writer,addx,addy,sf::Color(0,140,20,255),sf::Color::White);
    addy+=32;
    sprintf(writer,"   QuotaPeakPagedPoolUsage = ");
    draw3(writer,addx,addy,sf::Color(0,140,20,255),sf::Color::White);
    addy+=32;
    sprintf(writer,"    QuotaNonPagedPoolUsage = ");
    draw3(writer,addx,addy,sf::Color(0,140,20,255),sf::Color::White);
    addy+=32;
    sprintf(writer,"QuotaPeakNonPagedPoolUsage = ");
    draw3(writer,addx,addy,sf::Color(0,140,20,255),sf::Color::White);
    addy+=32;
    sprintf(writer,"             PagefileUsage = ");
    draw3(writer,addx,addy,sf::Color(0,140,20,255),sf::Color::White);
    addy+=32;
    sprintf(writer,"         PeakPagefileUsage = ");
    draw3(writer,addx,addy,sf::Color(0,140,20,255),sf::Color::White);
    addy+=32;

    //setlocale(LC_NUMERIC, "");
//    setlocale(LC_ALL,"");

    addx+=200;
    addy=180;
    sprintf(writer,"now:");
    draw3(writer,addx,addy,sf::Color(0,140,40,255),sf::Color::White);
    addy+=32;
    sprintf(writer,"%ld", memory.cb);
    str_format_int_grouped(writer);
    draw3(writer,addx,addy,sf::Color(0,140,20,255),sf::Color::White);
    addy+=32;
    sprintf(writer,"%ld", memory.PageFaultCount);
    str_format_int_grouped(writer);
    draw3(writer,addx,addy,sf::Color(0,140,20,255),sf::Color::White);
    addy+=32;
    sprintf(writer,"%u",  memory.WorkingSetSize);
    str_format_int_grouped(writer);
    draw3(writer,addx,addy,sf::Color(0,140,20,255),sf::Color::White);
    addy+=32;
    sprintf(writer,"%u",  memory.PeakWorkingSetSize);
    str_format_int_grouped(writer);
    draw3(writer,addx,addy,sf::Color(0,140,20,255),sf::Color::White);
    addy+=32;
    sprintf(writer,"%u",  memory.QuotaPagedPoolUsage);
    str_format_int_grouped(writer);
    draw3(writer,addx,addy,sf::Color(0,140,20,255),sf::Color::White);
    addy+=32;
    sprintf(writer,"%u",  memory.QuotaPeakPagedPoolUsage);
    str_format_int_grouped(writer);
    draw3(writer,addx,addy,sf::Color(0,140,20,255),sf::Color::White);
    addy+=32;
    sprintf(writer,"%u",  memory.QuotaNonPagedPoolUsage);
    str_format_int_grouped(writer);
    draw3(writer,addx,addy,sf::Color(0,140,20,255),sf::Color::White);
    addy+=32;
    sprintf(writer,"%u",  memory.QuotaPeakNonPagedPoolUsage);
    str_format_int_grouped(writer);
    draw3(writer,addx,addy,sf::Color(0,140,20,255),sf::Color::White);
    addy+=32;
    sprintf(writer,"%u",  memory.PagefileUsage);
    str_format_int_grouped(writer);
    draw3(writer,addx,addy,sf::Color(0,140,20,255),sf::Color::White);
    addy+=32;
    sprintf(writer,"%u",  memory.PeakPagefileUsage);
    str_format_int_grouped(writer);
    draw3(writer,addx,addy,sf::Color(0,140,20,255),sf::Color::White);
    addy+=32;

    addx+=200;
    addy=180;
    sprintf(writer,"start:");
    draw3(writer,addx,addy,sf::Color(0,140,40,255),sf::Color::White);
    addy+=32;
    sprintf(writer,"%ld", memory_old.cb);
    str_format_int_grouped(writer);
    draw3(writer,addx,addy,sf::Color(0,140,20,255),sf::Color::White);
    addy+=32;
    sprintf(writer,"%ld", memory_old.PageFaultCount);
    str_format_int_grouped(writer);
    draw3(writer,addx,addy,sf::Color(0,140,20,255),sf::Color::White);
    addy+=32;
    sprintf(writer,"%u",  memory_old.WorkingSetSize);
    str_format_int_grouped(writer);
    draw3(writer,addx,addy,sf::Color(0,140,20,255),sf::Color::White);
    addy+=32;
    sprintf(writer,"%u",  memory_old.PeakWorkingSetSize);
    str_format_int_grouped(writer);
    draw3(writer,addx,addy,sf::Color(0,140,20,255),sf::Color::White);
    addy+=32;
    sprintf(writer,"%u",  memory_old.QuotaPagedPoolUsage);
    str_format_int_grouped(writer);
    draw3(writer,addx,addy,sf::Color(0,140,20,255),sf::Color::White);
    addy+=32;
    sprintf(writer,"%u",  memory_old.QuotaPeakPagedPoolUsage);
    str_format_int_grouped(writer);
    draw3(writer,addx,addy,sf::Color(0,140,20,255),sf::Color::White);
    addy+=32;
    sprintf(writer,"%u",  memory_old.QuotaNonPagedPoolUsage);
    str_format_int_grouped(writer);
    draw3(writer,addx,addy,sf::Color(0,140,20,255),sf::Color::White);
    addy+=32;
    sprintf(writer,"%u",  memory_old.QuotaPeakNonPagedPoolUsage);
    str_format_int_grouped(writer);
    draw3(writer,addx,addy,sf::Color(0,140,20,255),sf::Color::White);
    addy+=32;
    sprintf(writer,"%u",  memory_old.PagefileUsage);
    str_format_int_grouped(writer);
    draw3(writer,addx,addy,sf::Color(0,140,20,255),sf::Color::White);
    addy+=32;
    sprintf(writer,"%u",  memory_old.PeakPagefileUsage);
    str_format_int_grouped(writer);
    draw3(writer,addx,addy,sf::Color(0,140,20,255),sf::Color::White);
    addy+=32;

    addx+=200;
    addy=180;
    sprintf(writer,"difference:");
    draw3(writer,addx,addy,sf::Color(0,140,40,255),sf::Color::White);
    addy+=32;
    sprintf(writer,"%lld", memory_diff_cb);
    str_format_int_grouped(writer);
    draw3(writer,addx,addy,sf::Color(0,140,20,255),sf::Color::White);
    addy+=32;
    sprintf(writer,"%lld", memory_diff_PageFaultCount);
    str_format_int_grouped(writer);
    draw3(writer,addx,addy,sf::Color(0,140,20,255),sf::Color::White);
    addy+=32;
    sprintf(writer,"%lld", memory_diff_WorkingSetSize);
    str_format_int_grouped(writer);
    draw3(writer,addx,addy,sf::Color(0,140,20,255),sf::Color::White);
    addy+=32;
    sprintf(writer,"%lld", memory_diff_PeakWorkingSetSize);
    str_format_int_grouped(writer);
    draw3(writer,addx,addy,sf::Color(0,140,20,255),sf::Color::White);
    addy+=32;
    sprintf(writer,"%lld", memory_diff_QuotaPagedPoolUsage);
    str_format_int_grouped(writer);
    draw3(writer,addx,addy,sf::Color(0,140,20,255),sf::Color::White);
    addy+=32;
    sprintf(writer,"%lld", memory_diff_QuotaPeakPagedPoolUsage);
    str_format_int_grouped(writer);
    draw3(writer,addx,addy,sf::Color(0,140,20,255),sf::Color::White);
    addy+=32;
    sprintf(writer,"%lld", memory_diff_QuotaNonPagedPoolUsage);
    str_format_int_grouped(writer);
    draw3(writer,addx,addy,sf::Color(0,140,20,255),sf::Color::White);
    addy+=32;
    sprintf(writer,"%lld", memory_diff_QuotaPeakNonPagedPoolUsage);
    str_format_int_grouped(writer);
    draw3(writer,addx,addy,sf::Color(0,140,20,255),sf::Color::White);
    addy+=32;
    sprintf(writer,"%lld", memory_diff_PagefileUsage);
    str_format_int_grouped(writer);
    draw3(writer,addx,addy,sf::Color(0,140,20,255),sf::Color::White);
    addy+=32;
    sprintf(writer,"%lld", memory_diff_PeakPagefileUsage);
    str_format_int_grouped(writer);
    draw3(writer,addx,addy,sf::Color(0,140,20,255),sf::Color::White);
    addy+=32;

    /*
        printf("                        cb = %ld\n", memory.cb);
        printf("            PageFaultCount = %ld\n", memory.PageFaultCount);
        printf("        PeakWorkingSetSize = %zu\n", memory.PeakWorkingSetSize);
        printf("            WorkingSetSize = %zu\n", memory.WorkingSetSize);
        printf("   QuotaPeakPagedPoolUsage = %zu\n", memory.QuotaPeakPagedPoolUsage);
        printf("       QuotaPagedPoolUsage = %zu\n", memory.QuotaPagedPoolUsage);
        printf("QuotaPeakNonPagedPoolUsage = %zu\n", memory.QuotaPeakNonPagedPoolUsage);
        printf("    QuotaNonPagedPoolUsage = %zu\n", memory.QuotaNonPagedPoolUsage);
        printf("             PagefileUsage = %zu\n", memory.PagefileUsage);
        printf("         PeakPagefileUsage = %zu\n", memory.PeakPagefileUsage);
    */
}

extern PROCESS_MEMORY_COUNTERS memory;

PROCESS_MEMORY_COUNTERS check_memory2()
{
    GetProcessMemoryInfo(GetCurrentProcess(), &memory, sizeof(memory));
    static PROCESS_MEMORY_COUNTERS memory_old=memory;

    printf("                        cb = %ld\n", memory.cb);
    printf("            PageFaultCount = %ld\n", memory.PageFaultCount);
    printf("        PeakWorkingSetSize = %u\n", memory.PeakWorkingSetSize);
    printf("            WorkingSetSize = %u\n", memory.WorkingSetSize);
    printf("   QuotaPeakPagedPoolUsage = %u\n", memory.QuotaPeakPagedPoolUsage);
    printf("       QuotaPagedPoolUsage = %u\n", memory.QuotaPagedPoolUsage);
    printf("QuotaPeakNonPagedPoolUsage = %u\n", memory.QuotaPeakNonPagedPoolUsage);
    printf("    QuotaNonPagedPoolUsage = %u\n", memory.QuotaNonPagedPoolUsage);
    printf("             PagefileUsage = %u\n", memory.PagefileUsage);
    printf("         PeakPagefileUsage = %u\n", memory.PeakPagefileUsage);
    return memory;

}

void set_monimem_terminator();
sf::Thread monimem_terminator(&set_monimem_terminator);

void launch_set_monimem_terminator()
{
    monimem_terminator.launch();
}
void terminate_set_monimem_terminator()
{
    monimem_terminator.terminate();
}

void set_monimem_terminator()
{
    printf("Monitor terminator set and sleeping for 25 secs.\n");
    sf::sleep(sf::milliseconds(22000));
    printf("\n3");
    sf::sleep(sf::milliseconds(333));
    printf(".");
    sf::sleep(sf::milliseconds(333));
    printf(".");
    sf::sleep(sf::milliseconds(333));
    printf("2");
    sf::sleep(sf::milliseconds(333));
    printf(".");
    sf::sleep(sf::milliseconds(333));
    printf(".");
    sf::sleep(sf::milliseconds(333));
    printf("1");
    sf::sleep(sf::milliseconds(333));
    printf(".");
    sf::sleep(sf::milliseconds(333));
    printf(".");
    sf::sleep(sf::milliseconds(333));
    if (monitor_loop==0)
    {
        printf("Terminating monitor.\n");
        loader_mutex.lock();
        monitor_off=1;
        monitor=1; // prevent restarting from other threads.
        loader_mutex.unlock();
        monimem.terminate();
        printf("Restarting monitor.\n");
        if (exiting==0)
            monimem.launch();
    }
    printf("Exiting monitor terminator.\n");
}


void launch_monimem()
{
    if (exiting==0)
        monimem.launch();
}
int hanger=25;


void MonitorMemory()
{
    if (exiting==1)
        return;
    monitor=1;
    if (!shut_up) printf("Background monitor thread entering....\n");
    int count1=10;
    int count2=10;
    int count3=10;
    int count4=10;
    static int count_die=1;
    char date_time[100];
    char out[100];
    loader_mutex.lock();
    monitor_loop=1;
    loader_mutex.unlock();
    while ((monitor_off==1 && monitor_loop==1) || shut_up)
    {
        static int count=30;
        static int sleeper=1000;
        monitor_off=0;
        sf::sleep(sf::milliseconds(sleeper));
        if (exiting==1) return;

/*
        if (active_window_num>=0 && is_activated_window[active_window_num]) {
            if (windows_3d[active_window_num]->hasFocus()) {
                if (bar_on[active_window_num]==1) ShowTaskBar(false);
                bar_on[active_window_num]=0;
            } else {
                if (bar_on[active_window_num]==0) ShowTaskBar(true);
                bar_on[active_window_num]=1;
            }
        }
*/
        sleeper=1000;
        count--;
        if (count<=0)
        {
            count=30;
//                printf("Thread sleeping....but alive.\n");
            count_die--;
            if (count_die<=0)
            {
                count_die=10;
                get_date_time(date_time);
                sprintf(out,"Alive at: %s",date_time);
//                logfile(out);
//                    savedata(out,monitor_off);
            }
        }

        if (thread_run_sub==1)
        {
            thread_run_sub=0;
            printf("Assignment detected, running shader() as thread\n");
            sub_thread_shaders.launch();
        }
        static int task=1;
        loader_mutex.lock();
        if (loader1_active==0 && kill1==1)
        {
            count1--;
            if (count1<=0)
            {
                count1=10;
                kill1=0;
                printf("map loader 1 ready.\n");
            }
        }
        if (loader2_active==0 && kill2==1)
        {
            count2--;
            if (count2<=0)
            {
                count2=10;
                kill2=0;
                printf("map loader 2 ready.\n");
            }
        }
        if (loader3_active==0 && kill3==1)
        {
            count3--;
            if (count3<=0)
            {
                count3=10;
                kill3=0;
                printf("map loader 3 ready.\n");
            }
        }
        if (window_1_active==0 && window_2_active==0 && window_3_active==0 && helpme==1)
        {
            count4--;
            if (count4<=0)
            {
                count4=30;
                if (taskbar==0 && DO_ADAPT==0)
                {
                    ShowTaskBar(true);
                    taskbar=1;
                }
                helpme=0;
                printf("helpme=off.\n");
            }

        }
        if (window_1_active==0 && window_2_active==0 && window_3_active==0 && taskbar==0 && DO_ADAPT==0)
        {
//                    taskbar=1;
//                    ShowTaskBar(true);

        }
        loader_mutex.unlock();

    }
    loader_mutex.lock();
    if (monitor_loop==0)
    {
        printf("Escape pressed. Entering monitor loop.\n");
    }
    else
    {
//            printf("Rendering off, thread awake....lets check memory (also shift-f2)\n");
    }
//        if (taskbar==0) ShowTaskBar(true);
//        taskbar=1;
    loader_mutex.unlock();
    hanger=15;
//    printf("monimem: before do\n");
    do
    {
        if (exiting==1)
            return;
        loader_mutex.lock();
        if (monitor_loop==0)
            hanger=0;
        else
            hanger--;
        loader_mutex.unlock();

//        printf("monimem: before peek\n");
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            HANDLEEVENTS();
        }

//        check_memory2();
//        printf("monimem: sleep do\n");
        sf::sleep(sf::milliseconds(5000));
        get_date_time(date_time);
        sprintf(out,"Program busy or hangs... Thread alive at: %s",date_time);
        savedata(out,monitor_off);
//        printf("monimem:  after savedata()\n");
//        if (hanger==10) {
//            printf(("Autosolving: Unlocking mutex thread loaders.\n"));
//            loader_mutex.unlock();
//        }
        if (hanger==8 && DO_ADAPT==0)
        {
            printf(("Autosolving: Order loader threads to kill themselves.\n"));
            kill1=1;
            kill2=1;
            kill3=1;
        }
        if (hanger==6 && DO_ADAPT==0)
        {
            printf(("Autosolving: Trying to terminate loader threads.\n"));
            kill_threads();
        }
        if (hanger==4 && DO_ADAPT==0)
        {
            printf(("Autosolving: Trying to terminate background_loader_all().\n"));
            kill_background_loader();
        }
        if (hanger==2 && DO_ADAPT==0)
        {
            printf(("Autosolving: Trying to escape.\n"));
            ESCAPE=1;
        }
        if (hanger<=0 && DO_ADAPT==0)
        {
            char c;

            printf("\n");
            printf("1=EXITPROGRAM();\n");
            printf("2=monitor_off=1;\n");
            printf("3=terminate_animator();\n");
            printf("4=launch_animator();\n");
            printf("5=hanger=12;\n");
            printf("6=SAVEALLBITMAPS();\n");
            printf("7=loader_mutex.unlock();\n");
            printf("8=kill_threads();\n");
            printf("9=kill_background_loader();\n");
            printf("0=go_on=0;\n");
            printf("a=winmain_running=0;\n");
            printf("b=frexit(-1);\n");
            printf("c=cleanupmem();\n");
            printf("d=monitor_loop=1;\n");
            printf("e=kill1=kill2=kill3=1;\n");
            printf("f=check_memory2();\n");
            printf("g=terminate_set_monimem_terminator();\n");
            printf("h=launch_set_monimem_terminator();\n");
            printf("i=terminate_animator();launch_animator();\n");

            printf("\n");
            printf("memory_set=%d\n",memory_set);
            printf("monitor_loop=%d\n",monitor_loop);
            printf("\n");
            monimem_terminator.launch();
            sf::sleep(sf::milliseconds(500));
            printf("Restarting monitor after 25 seconds.\n");
            printf("\n");
            printf("What should i do?");
            sf::sleep(sf::milliseconds(1000));
            if (exiting==1)
                return;
            c=tolower(getchar());
//            monimem_terminator.terminate();
            if ( (c>=(char)'0' && c<=(char)'9') || (c>=(char)'a' && c<=(char)'z'))
            {
                send_message=c;
                sf::sleep(sf::milliseconds(1000));
            }
            else
            {
//                monitor_loop=1;
                monitor_off=1;
            }
            /*
                        if (c==(char)'1') EXITPROGRAM();
                        else if (c==(char)'2') monitor_off=1;
                        else if (c==(char)'3') terminate_animator();
                        else if (c==(char)'4') launch_animator();
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
                        else { monitor_loop=1; monitor_off=1; }
            */

        }
    }
    while ((F2==1 && monitor_off==0) || monitor_loop==0 );

//    printf("Rendering on again or user exit monitor thread....exiting thread\n");
    monitor=0;
}

void terminate_monitor()
{
    monimem.terminate();
}


// Print current date and time in C
int get_date_time(char * ret)
{
    int hours, minutes, seconds, day, month, year;

    time_t now;
    time(&now);
    struct tm *local = localtime(&now);

    hours = local->tm_hour;          // get hours since midnight (0-23)
    minutes = local->tm_min;         // get minutes passed after the hour (0-59)
    seconds = local->tm_sec;         // get seconds passed after minute (0-59)

    day = local->tm_mday;            // get day of month (1 to 31)
    month = local->tm_mon + 1;       // get month of year (0 to 11)
    year = local->tm_year + 1900;    // get year since 1900

    sprintf(ret,"%02d/%02d/%d %02d:%02d:%02d",day, month, year, hours, minutes, seconds);

    return 0;
}

extern void RenderBlit3(int xdest, int ydest, int xsource, int ysource, int width, int height, int x, int y);

void plot_all_ghosts(int picturex,int picturey)
{

    static int addx=-45+60*totalpicturex;
    static int addy=-23+30*totalpicturey;
    static int modx=30*totalpicturex;
    static int mody=15*totalpicturey;
    int mazemovex;
    int mazemovey;

    m_shader2.setUniform("offset", sf::Vector2f((float)picturex,(float)picturey));

    ghostmode=1;
    for (num_ghost=0; num_ghost<number; num_ghost++)
    {

        int numloops;
        int loops;
        int offsetx=0;
        int offsety=0;
        int verschilx;
        int verschily;

        int pos_ghostx_old;
        int pos_ghosty_old;
        float fpos_ghostx_old;
        float fpos_ghosty_old;

        float fpos_ghostx_num_ghost=fpos_ghostx[num_ghost];
        float fpos_ghosty_num_ghost=fpos_ghosty[num_ghost];
        int pos_ghostx_num_ghost=pos_ghostx[num_ghost];
        int pos_ghosty_num_ghost=pos_ghosty[num_ghost];
        float fspeed_ghostx_num_ghost=fspeed_ghostx[num_ghost];
        float fspeed_ghosty_num_ghost=fspeed_ghosty[num_ghost];
        int check_num_ghost=check[num_ghost];

        pos_ghostx_old=pos_ghostx_num_ghost;
        pos_ghosty_old=pos_ghosty_num_ghost;

        fpos_ghostx_old=fpos_ghostx_num_ghost;
        fpos_ghosty_old=fpos_ghosty_num_ghost;

        verschilx=-pos_ghostx_num_ghost-(picturex*1920-1920);
        verschily=-pos_ghosty_num_ghost-(picturey*1080-1080);

//        verschilx=-pos_ghostx_num_ghost-(picturex*1920-posx-1920);
//        verschily=-pos_ghosty_num_ghost-(picturey*1080-posy-1080);

        if (verschilx<=-maxpixelsx/2)
            verschilx=verschilx+maxpixelsx;
        else if (verschilx>maxpixelsx/2)
            verschilx=verschilx-maxpixelsx;
        if (verschily<=-maxpixelsy/2)
            verschily=verschily+maxpixelsy;
        else if (verschily>maxpixelsy/2)
            verschily=verschily-maxpixelsy;

        offsetx=960-32+9+verschilx;
        offsety=540-36+10+verschily;
        int cheat;

        int old_verschilx=verschilx;
        int old_verschily=verschily;

        if (shade_map>=1)
        {
            flowx=sin(fpstime+num_ghost+sin(fpstime*1.2+num_ghost))*50  + sin(fpstime*1.4+num_ghost+sin(fpstime*1.5+num_ghost))*10;
            flowy=cos(fpstime*1.1+num_ghost+sin(fpstime*1.3+num_ghost))*50 + sin(fpstime*0.9+num_ghost+sin(fpstime*1.3+num_ghost))*10;
            offsetx=offsetx+flowx;
            offsety=offsety+flowy;
        }

        int motion;
        static int motion_up_down[]= {0,1,0,3};

        if (fspeed_ghostx_num_ghost==0)
        {
            motion=(-pos_ghostx_num_ghost-pos_ghosty_num_ghost)*2.5/32;
            motion=motion%4;
            if (motion<0)
                motion=motion+4;
            motion=motion_up_down[motion];
        }
        else
        {
            motion=(-pos_ghostx_num_ghost-pos_ghosty_num_ghost)*2.5/16;
            motion=motion%4;
            if (motion<0)
                motion=motion+4;
        }

        new_verschilx=0;
        new_verschily=0;
        new_verschilx2=0;
        new_verschily2=0;

        if (ghost==1)
        {
            if ( (offsetx>(9-64-new_verschilx-new_verschilx2)) && (offsety>(10-72-new_verschily-new_verschily2)) && (offsetx<1980-new_verschilx-new_verschilx2) && (offsety<1080-new_verschily-new_verschily2))
            {
                offsetx=new_verschilx+new_verschilx2;
                offsety=new_verschily+new_verschily2;

                if (shade_map>=1)
                {
                    offsetx=offsetx+flowx;
                    offsety=offsety+flowy;
                }
                m_shader.setUniform("wave_phase", fpstime+num_ghost);

                if (SFML==1)
                {
                    int cut_left=0;
                    int cut_right=0;
                    int cut_up=0;
                    int cut_down=0;

                    int posX=0;
                    int posY=0;

                    mazemovex=(-pos_ghostx_num_ghost+1920-32+maxpixelsx)/64;
                    mazemovey=(-pos_ghosty_num_ghost+1080   +maxpixelsy)/72;
                    mazemovex=(mazemovex+addx)%modx;
                    mazemovey=(mazemovey+addy)%mody;

                    posX=(-pos_ghostx_num_ghost+1920-32)%64;
                    posY=(-pos_ghosty_num_ghost+1080   )%72;

                    int blokje=maze_plot[mazemovex][mazemovey];

                    int bridge=0;
                    if (blank_maze!=1 || drawmazes!=1)
                    {
                        if ( (blokje&(64+32))>0 )
                            bridge=1;
                        if ((blokje&64)==64 && fspeed_ghostx_num_ghost!=0)
                        {
                            if ( posX>=0 && posX<(63-15) )
                                cut_left=63-15-posX;
                        }
                        if ((blokje&32)==32 && fspeed_ghosty_num_ghost!=0.0)
                        {
                            if ( posY>=0 && posY<(71-16) )
                                cut_up=71-16-posY;
                        }

                        blokje=maze_plot[(mazemovex+1)%modx][mazemovey];
                        if ( (blokje&(64+32))>0 )
                            bridge=1;
                        if ((blokje&64)==64 && fspeed_ghostx_num_ghost!=0)
                        {
                            if ( posX>63-47 )
                                cut_right=posX-63+47;
                        }

                        blokje=maze_plot[mazemovex][(mazemovey+1)%mody];
                        if ( (blokje&(64+32))>0 )
                            bridge=1;
                        if ((blokje&32)==32 && fspeed_ghosty_num_ghost!=0)
                        {
                            if ( posY>71-54 )
                                cut_down=posY-71+54;
                        }

                    }

                    if (hunt==1 && check_num_ghost<=1)
                    {
                        if (64-18-cut_left-cut_right>0 &&  72-20-cut_up-cut_down>0)
                            RenderBlit3(960-32+9+verschilx+offsetx+cut_left, 540-36+10+verschily+offsety+cut_up,  128*(6)+9+cut_left,          72*5+motion*72+10+cut_up,    64-18-cut_left-cut_right,  72-20-cut_up-cut_down,picturex,picturey);

                    }
                    else if (hunt==2 && check_num_ghost<=1)
                    {
                        if ((((int)((hunt_counter+num_ghost)/15))%2)==0)
                        {
                            if (64-18-cut_left-cut_right>0 &&  72-20-cut_up-cut_down>0)
                                RenderBlit3(960-32+9+verschilx+offsetx+cut_left,540-36+10+verschily+offsety+cut_up,   128*(7)+9+cut_left,         72*5+motion*72+10+cut_up,             64-18-cut_left-cut_right,72-20-cut_up-cut_down,picturex,picturey);
                        }
                        else
                        {
                            if (64-18-cut_left-cut_right>0 &&  72-20-cut_up-cut_down>0)
                                RenderBlit3(960-32+9+verschilx+offsetx+cut_left,540-36+10+verschily+offsety+cut_up,  128*(6)+9+cut_left,           72*5+motion*72+10+cut_up,        64-18-cut_left-cut_right,72-20-cut_up-cut_down,picturex,picturey);
                        }
                    }
                    else if ((follow_ghost==0 || follow_ghost_num!=num_ghost) && check_num_ghost<=1)
                    {
                        if (64-18-cut_left-cut_right>0 &&  72-20-cut_up-cut_down>0)
                            RenderBlit3(960-32+9+verschilx+offsetx+cut_left,540-36+10+verschily+offsety+cut_up,  128*(4+((num_ghost+level+difficulty)%4))+9+cut_left, 72+motion*72+10+cut_up,      64-18-cut_left-cut_right,72-20-cut_up-cut_down,picturex,picturey);
                    }
                    else if (check_num_ghost<=1)
                    {
                        static int flits;
                        flits++;
                        int rev_sync=0;
                        if (sync==0)
                            rev_sync=1;
                        if ((((int)(flits/(15+rev_sync*50)))%2)==0)
                        {
                            if (64-18-cut_left-cut_right>0 &&  72-20-cut_up-cut_down>0)
                                RenderBlit3(960-32+9+verschilx+offsetx+cut_left,540-36+10+verschily+offsety+cut_up,  128*(7)+9+cut_left,        72*5+motion*72+10+cut_up,           64-18-cut_left-cut_right,72-20-cut_up-cut_down,picturex,picturey);
                        }
                        else
                        {
                            if (64-18-cut_left-cut_right>0 &&  72-20-cut_up-cut_down>0)
                                RenderBlit3(960-32+9+verschilx+offsetx+cut_left,540-36+10+verschily+offsety+cut_up,  128*(6)+9+cut_left,        72*5+motion*72+10+cut_up,           64-18-cut_left-cut_right,   72-20-cut_up-cut_down,picturex,picturey);
                        }
                    }

                    int look=0;
                    if (fspeed_ghosty_num_ghost<0)
                        look=0;
                    else if (fspeed_ghosty_num_ghost>0)
                        look=1;
                    else if (fspeed_ghostx_num_ghost<0)
                        look=2;
                    else if (fspeed_ghostx_num_ghost>0)
                        look=3;

                    if (hunt!=2 || check_num_ghost>1)
                    {
                        if (64-18-cut_left-cut_right>0 &&  72-20-cut_up-cut_down>0)
                            RenderBlit3(960-32+9+verschilx+offsetx+cut_left, 540-36+10+verschily+offsety+cut_up,  10*64+9+cut_left, 5*72+look*72+10+cut_up,                 64-18-cut_left-cut_right,72-20-cut_up-cut_down,picturex,picturey);
                    }
                    else
                    {
                        if ((((int)(hunt_counter/15))%2)==0 )
                        {
                            if (64-18-cut_left-cut_right>0 &&  72-20-cut_up-cut_down>0)
                                RenderBlit3(960-32+9+verschilx+offsetx+cut_left, 540-36+10+verschily+offsety+cut_up,  16*64+9+cut_left, 5*72+look*72+10+cut_up, 64-18-cut_left-cut_right,72-20-cut_up-cut_down,picturex,picturey);
                        }
                        else
                        {
                            if (64-18-cut_left-cut_right>0 &&  72-20-cut_up-cut_down>0)
                                RenderBlit3(960-32+9+verschilx+offsetx+cut_left, 540-36+10+verschily+offsety+cut_up,  10*64+9+cut_left, 5*72+look*72+10+cut_up, 64-18-cut_left-cut_right,72-20-cut_up-cut_down,picturex,picturey);
                        }
                    }
                }
            }
        }
    }
}

extern int border_col_r;
extern int border_col_g;
extern int border_col_b;

extern int GETPICTURE2(char *naam);

void batch_pictures()
{
    int x;
    int y;
    int x_old;
    float y_count=0.0;
    int new_mazemovex=-1;
    int new_mazemovey;
    int newone=0;
    crop_x=32;
    crop_x_size=0;
    crop_y_size=0;
    char naam[2000];
    ffmpegfile=1;
    size_ffmpeg=0;
    ffmpeg_move=0;
//    sprite_from_ffmpeg.setScale(1.0,1.0);
    rotate_ffmpeg=0;
    rotation_ffmpeg=0;
    float scale=sprite_from_ffmpeg.getScale().x;
    int size_y_pref=0;
    int size_x_pref=0;
    int x_position=(picturex*1920-posx);
//    int x_position=1920/2;
    double screen_x=x_position;
    double screen_x_prev=x_position;
//    int screen_x=x_position-1920/2;
    int y_position=(picturey*1080-posy);
//    int y_position=0;
    double screen_y=y_position;
    double screen_y_prev=y_position;
//    int screen_y=0;

    rotate_ffmpeg=0;
    rotation_ffmpeg=0;
//            scale_now=1.0;

    float count_y_tot=0.0;
    int start=1;
    int new_mazemovex2;
    int new_mazemovey2;
    int mazemovex2;
    int mazemovey2;
    float count_y=-999.99;
    char test[2000]="";
    char test_prev[2000]="";
    reload_init();
    char f[2000];
    FILE *ff;
    int n=0;

    extern int next_textfile;
    extern int total_textfile;
    extern int start_textfile;

    next_textfile=0;
    total_textfile=0;
    start_textfile=1;

    strcpy(f,PICTUREDIR);
    strcat(f,"/list.txt");
    ff=fopen(f,"r");

//    printf("i'm here -1 n=%d\n",n);
    if (ff==NULL)
    {
        strcpy(error_msg2,"NO PICTUREDIR/LIST.TXT");
        error_flag2=1;
        size_ffmpeg=0;
        ffmpeg_move=0;
        return;
    }
    if (fgets(naam,2000,ff)==NULL) {
        strcpy(error_msg2,"END OF LIST.TXT");
        error_flag2=1;
        size_ffmpeg=0;
        ffmpeg_move=0;
        fclose(ff);
        return;
    }
    if (naam[strlen(naam)-1]=='\r' || naam[strlen(naam)-1]=='\n')
        naam[strlen(naam)-1]='\0';
//    printf("naam=%s\n",naam);
    while (true)
    {
        if (file_exists(naam))
        {
            if (Inter.loadFromFile(naam))
            {
                if (texture_from_ffmpeg.loadFromImage(Inter))
                {
                    ffmpegfile=0;
                    texture_from_ffmpeg.setRepeated(TRUE);
                    if (smooth==1)
                        texture_from_ffmpeg.setSmooth(TRUE);
                    else
                        texture_from_ffmpeg.setSmooth(FALSE);

                    strcpy(test,naam);
                    if (strlen(test)>9) {
                        test[strlen(test)-10]='\0';
                        if (strcmp(test,test_prev)!=0) {
                            do {
                                newone=1;
                                border_col_r=rand()%256;
                                border_col_g=rand()%256;
                                border_col_b=rand()%256;
                            } while (border_col_r+border_col_g+border_col_b<300);
                        }
                    }
                    strcpy(test_prev,test);
                    sprite_from_ffmpeg.setTextureRect( { 0,0,(int)texture_from_ffmpeg.getSize().x, (int)texture_from_ffmpeg.getSize().y } );
                    add_border_left_right(&texture_from_ffmpeg);
                    if (ffmpegfile==1) {
                        border_col_r=0;
                        border_col_g=0;
                        border_col_b=0;
                        return;
                    }

                    /*
                                        sprite_from_ffmpeg.setTextureRect( { 0,0,(int)texture_from_ffmpeg.getSize().x, (int)texture_from_ffmpeg.getSize().y } );
                                        soften_edge(&texture_from_ffmpeg);
                                        if (ffmpegfile==1) return;

                                        sprite_from_ffmpeg.setTextureRect( { 0,0,(int)texture_from_ffmpeg.getSize().x, (int)texture_from_ffmpeg.getSize().y } );
                                        add_border(&texture_from_ffmpeg);
                                        if (ffmpegfile==1) return;

                                        sprite_from_ffmpeg.setTextureRect( { 0,0,(int)texture_from_ffmpeg.getSize().x, (int)texture_from_ffmpeg.getSize().y } );
                                        soften_edge(&texture_from_ffmpeg);
                                        if (ffmpegfile==1) return;

                                        sprite_from_ffmpeg.setTextureRect( { 0,0,(int)texture_from_ffmpeg.getSize().x, (int)texture_from_ffmpeg.getSize().y } );
                    */

                    texture_from_ffmpeg.setRepeated(TRUE);
                    if (smooth==1)
                        texture_from_ffmpeg.setSmooth(TRUE);
                    else
                        texture_from_ffmpeg.setSmooth(FALSE);
                    texture_from_ffmpeg.generateMipmap();

                    if (size_y_pref==0)
                        size_y_pref=texture_from_ffmpeg.getSize().y;
                    if (size_x_pref==0)
                        size_x_pref=texture_from_ffmpeg.getSize().x;
                }
                else
                {
                    sprintf(error_msg2,"FAILED LOADING %s",naam);
                    error_flag2=1;
                    printf("FAILED LOADING %s\n",naam);
                    savedata((char*)"failed loading1, to large? Then remove from list.",0);
                    size_ffmpeg=0;
                    ffmpeg_move=0;
                    border_col_r=0;
                    border_col_g=0;
                    border_col_b=0;
                    return;
                }
            }
            else
            {
                sprintf(error_msg2,"FAILED LOADING %s",naam);
                error_flag2=1;
                printf("FAILED LOADING %s\n",naam);
                savedata((char*)"failed loading2, to large? Then remove from list.",0);
                size_ffmpeg=0;
                ffmpeg_move=0;
                border_col_r=0;
                border_col_g=0;
                border_col_b=0;
                return;
            }
        }
        else
        {
            sprintf(error_msg2,"FAILED LOADING %s FILE DOES NOT EXIST",naam);
            error_flag2=1;
            printf("FAILED LOADING %s FILE DOES NOT EXIST\n",naam);
            savedata((char*)"failed loading, file does not exists: ",0);
            savedata((char*)naam,0);
            size_ffmpeg=0;
            ffmpeg_move=0;
            border_col_r=0;
            border_col_g=0;
            border_col_b=0;
            return;
        }
        //        Inter.create(0,0);

//        if (n==1) screen_y=(-1080+maxpixelsy+y_position+texture_from_ffmpeg.getSize().y/2*scale)%maxpixelsy;
//        printf("n=%d\n",n);

//        if (n==1) screen_y=texture_from_ffmpeg.getSize().y/2*scale-1080;
//        if (n==1) screen_x=texture_from_ffmpeg.getSize().x/2*scale-1920;

        if (texture_from_ffmpeg.getSize().x*scale>crop_x_size)
            crop_x_size=texture_from_ffmpeg.getSize().x*scale;
        if (texture_from_ffmpeg.getSize().y*scale>crop_y_size)
            crop_y_size=texture_from_ffmpeg.getSize().y*scale;
//        if (n==1) screen_y=texture_from_ffmpeg.getSize().y/2;
//        if (n==1) screen_y=texture_from_ffmpeg.getSize().y/2-1080/2;

        if (new_mazemovex==-1)
        {
            new_mazemovex=((int)screen_x-32)/64;
            new_mazemovey=((int)screen_y   )/72;
            new_mazemovex=(new_mazemovex-45+maze_plotsizex)%maze_plotsizex;
            new_mazemovey=(new_mazemovey-23+maze_plotsizey)%maze_plotsizey;
            mazemovex=new_mazemovex;
            mazemovey=new_mazemovey;
            y=new_mazemovey;
            x=new_mazemovex;
        }
        else
        {
            mazemovex=new_mazemovex;
            mazemovey=new_mazemovey;
//            mazemovex=(new_mazemovex+maze_plotsizex)%maze_plotsizex;
//            mazemovey=new_mazemovey%maze_plotsizey;
            y=mazemovey;
            x=mazemovex;
        }

        int xdir,ydir;

        double alpha;
        alpha=asin((double)(texture_from_ffmpeg.getSize().x+40)/(double)(BITMAPSX*1920.0));
        rotation_ffmpeg=(float)(90.0-180.0*alpha/3.141592653589793);
//        if (newone) size_y_pref+=400;
        screen_x=screen_x-cos(alpha)*(size_y_pref+texture_from_ffmpeg.getSize().y)/2.0+0.01;
        screen_y=screen_y+sin(alpha)*(size_y_pref+texture_from_ffmpeg.getSize().y)/2.0;

//1
        /*

                screen_x=screen_x+( (double)(size_y_pref+texture_from_ffmpeg.getSize().y )*scale)*(1.0/1.9);
                screen_y=screen_y+( (double)(size_x_pref+texture_from_ffmpeg.getSize().x )*scale)*(1.0/1.9)
                /(double)(BITMAPSX/(((double)(size_x_pref+texture_from_ffmpeg.getSize().x )*scale)/(1920.0*2.0*1.9)));

        */

//2


        /*
                screen_x=screen_x+( (double)(size_x_pref+texture_from_ffmpeg.getSize().x )*scale)*(0.55);
                screen_y=screen_y+( (double)(size_x_pref+texture_from_ffmpeg.getSize().x )*scale)*(0.275)
                /(double)(BITMAPSX/(((double)(size_y_pref+texture_from_ffmpeg.getSize().y )*scale)/1920.0));
        */

        screen_x_prev=screen_x;
        screen_y_prev=screen_y;


//        screen_x=screen_x+( (size_y_pref+texture_from_ffmpeg.getSize().y )*sprite_from_ffmpeg.getScale().y)*(1.1/2.0);
//        screen_y=screen_y+( (size_y_pref+texture_from_ffmpeg.getSize().y )*sprite_from_ffmpeg.getScale().y)*(1.5/2.0)*(1080.0/1920.0)/BITMAPSX;

//        screen_x=screen_x+(size_x_pref+texture_from_ffmpeg.getSize().x)/2.0*scale;
//        screen_y=screen_y+(size_x_pref+texture_from_ffmpeg.getSize().x)/2.0*scale*1080.0/1920.0*3.0/BITMAPSX;
//        screen_y=screen_y+texture_from_ffmpeg.getSize().x*1080.0/1920.0*2.0/8.0;

        newone=0;

        if (screen_x>screen_x_prev )
            xdir=1;
        else
            xdir=-1;
        if (screen_y>screen_y_prev )
            ydir=1;
        else
            ydir=-1;

        new_mazemovex=((int)screen_x-32)/64;
        new_mazemovey=((int)screen_y   )/72;
        new_mazemovex=(new_mazemovex-45);
        new_mazemovey=(new_mazemovey-23);


        screen_x=fmod(screen_x+(double)maxpixelsx,(double)maxpixelsx);

        size_x_pref=texture_from_ffmpeg.getSize().x;
        size_y_pref=texture_from_ffmpeg.getSize().y;

        smooth_x=screen_x;
        smooth_y=screen_y;

        picturex=(int)screen_x/1920;
        render_picturex=picturex;
        posx=(int)screen_x-1920*picturex;
        picturey=(int)screen_y/1080;
        render_picturey=picturey;
        posy=(int)screen_y-1080*picturey;
        posx=-posx;
        render_posx=posx;
        posy=-posy;
        render_posy=posy;

        render_picturex=picturex;
        render_posx=posx;
        render_picturey=picturey;
        render_posy=posy;

        if (ffmpegfile==0)
        {
            texture_from_ffmpeg.setRepeated(TRUE);
            if (smooth==1)
                texture_from_ffmpeg.setSmooth(TRUE);
            else
                texture_from_ffmpeg.setSmooth(FALSE);
//1
//            rotation_ffmpeg=rand()%11-5+90;
//2
//            rotation_ffmpeg=rand()%11-5;

            rot_speed_ffmpeg=0.0;

            setffmpegfile();
            if ( (vertex_shader==1 || fragment_shader==1) )
            {
                picture_shader.setUniform("iRotate", (float)(sprite_from_ffmpeg.getRotation()/360.0*2.0*PI));
                if (buffer_shader==1)
                    shader_buffer.setUniform("iRotate", (float)(sprite_from_ffmpeg.getRotation()/360.0*2.0*PI));
                picture_shader.setUniform("texture_buffer", texture_from_ffmpeg);
                picture_shader.setUniform("iResolution_buffer",  sf::Vector2f( texture_from_ffmpeg.getSize().x,texture_from_ffmpeg.getSize().y) );
                picture_shader.setUniform("iResolution",  sf::Vector2f( texture_from_ffmpeg.getSize().x,texture_from_ffmpeg.getSize().y) );
            }

//            rotation_ffmpeg=rand()%11-5;
//            rotation_ffmpeg=0.0;
            sprite_from_ffmpeg.setTexture(texture_from_ffmpeg,false);
//            sprite_from_ffmpeg.setScale(1.0,1.0);
            /*
                        if (rand()%2==1) {
                            plot_front=1;
                            plot_back=0;
                        } else {
                            plot_front=1;
                            plot_back=0;
                        }
            */
            perform_quit=1;
            setffmpegfile();
            plot_ffmpegfile=1;
            plotplot();
            perform_quit=0;
        }



        /*
                new_mazemovex=((int)screen_x-32)/64;
                new_mazemovey=((int)screen_y   )/72;
                new_mazemovex=(new_mazemovex-45);
                new_mazemovey=(new_mazemovey-23);
        */

        /*
                    new_mazemovex2=new_mazemovex;
                    new_mazemovey2=new_mazemovey;
                    mazemovex2=mazemovex;
                    mazemovey2=mazemovey;
        */

        if ( xdir==-1 )
        {
            new_mazemovex2=mazemovex;
            new_mazemovey2=mazemovey;
            mazemovex2=new_mazemovex;
            mazemovey2=new_mazemovey;
//            ydir=-ydir;
        }
        else
        {
            new_mazemovex2=new_mazemovex;
            new_mazemovey2=new_mazemovey;
            mazemovex2=mazemovex;
            mazemovey2=mazemovey;
        }
        if ( xdir==-1)
        {
            if (new_mazemovex2<mazemovex2)
                new_mazemovex2+=maze_plotsizex;
            if (new_mazemovey2>mazemovey2)
                new_mazemovey2+=maze_plotsizey;
            if (mazemovex2<0 || new_mazemovex2<0)
            {
                mazemovex2+=maze_plotsizex;
                new_mazemovex2+=maze_plotsizex;
            }
            if (mazemovey2<0 || new_mazemovey2<0)
            {
                mazemovey2+=maze_plotsizey;
                new_mazemovey2+=maze_plotsizey;
            }
        }
        else
        {
            if (new_mazemovex2<mazemovex2)
                new_mazemovex2+=maze_plotsizex;
            if (new_mazemovey2<mazemovey2)
                new_mazemovey2+=maze_plotsizey;
            if (mazemovex2<0 || new_mazemovex2<0)
            {
                mazemovex2+=maze_plotsizex;
                new_mazemovex2+=maze_plotsizex;
            }
            if (mazemovey2<0 || new_mazemovey2<0)
            {
                mazemovey2+=maze_plotsizey;
                new_mazemovey2+=maze_plotsizey;
            }
        }

//        if (fabs(screen_x-screen_x_prev)!=0) count_y= (fabs((float)(screen_y-screen_y_prev))) / (fabs((float)(screen_x-screen_x_prev))) ;
        if (fabs(new_mazemovex2-mazemovex2)!=0)
            count_y= (fabs((float)(new_mazemovey2-mazemovey2))) / (fabs((float)(new_mazemovex2-mazemovex2))) ;
        if (count_y<0.2 && fabs((float)(new_mazemovey2-mazemovey2))<3.0 && fabs((float)(new_mazemovex2-mazemovex2))>6.0)
        {
            new_mazemovex=mazemovex;
            new_mazemovey=mazemovey;
        }
        else
        {
            y=mazemovey2;
            count_y_tot=0.0;
            count_y_tot+=count_y;
            for (x=mazemovex2+1; x<=new_mazemovex2; x++)
            {
                maze_plot[x%maze_plotsizex][y%maze_plotsizey]=maze_plot[x%maze_plotsizex][y%maze_plotsizey]|8;
                maze_plot[(x+1)%maze_plotsizex][y%maze_plotsizey]=maze_plot[(x+1)%maze_plotsizex][y%maze_plotsizey]|4;
                if (drawmazes==1 && blank_maze==0)
                {
                    do_mirror(x,y,maze_plot[x%maze_plotsizex][y%maze_plotsizey]);
                    do_mirror((x+1)%maze_plotsizex,y%maze_plotsizey,maze_plot[(x+1)%maze_plotsizex][y%maze_plotsizey]);
                }
                count_y_tot+=count_y;
                if (count_y_tot>1.0)
                {
                    count_y_tot-=1.0;
                    maze_plot[(x+1)%maze_plotsizex][y%maze_plotsizey]=maze_plot[(x+1)%maze_plotsizex][y%maze_plotsizey]|(2-(ydir==-1));
                    maze_plot[(x+1)%maze_plotsizex][(y+ydir+maze_plotsizey)%maze_plotsizey]=maze_plot[(x+1)%maze_plotsizex][(y+ydir+maze_plotsizey)%maze_plotsizey]|(1+(ydir==-1));
                    if (drawmazes==1 && blank_maze==0)
                    {
                        do_mirror((x+1)%maze_plotsizex,y%maze_plotsizey,maze_plot[(x+1)%maze_plotsizex][y%maze_plotsizey]);
                        do_mirror((x+1)%maze_plotsizex,(y+ydir+maze_plotsizey)%maze_plotsizey,maze_plot[(x+1)%maze_plotsizex][(y+ydir+maze_plotsizey)%maze_plotsizey]);
                    }
                    y+=ydir;
                }
            }
        }
//new!!!

        double screen_y2=fmod(screen_y+(double)maxpixelsy-1080.0*3.0,(double)maxpixelsy);

        smooth_y=screen_y2;

        picturey=(int)screen_y2/1080;
        render_picturey=picturey;
        posy=(int)screen_y2-1080*picturey;
        posy=-posy;
        render_posy=posy;

        render_picturey=picturey;
        render_posy=posy;

        if (plot_all)
        {
            update_plot_all();
        }
        else
            blitter("",1);

        if (screen_y>=maxpixelsy)
        {
//        if (screen_y+texture_from_ffmpeg.getSize().y*scale>=maxpixelsy) {
            strcpy(error_msg4,"END OF SCREEN REACHED, ABORTING");
            printf("%s\n",error_msg4);
            error_flag4=1;
            shift=0;
            ffmpegfile=1;
            forced_jump=1;
            follow_ghost_pos();
            ReadBitmaps2();
            ReadBitmaps4();
            strcpy(error_msg3,"PRESS CTRL+SHIFT+R TO CROP BEFORE RECORDING ('r')");
            printf("%s\n",error_msg3);
            error_flag3=1;
            size_ffmpeg=0;
            ffmpeg_move=0;
            return;
        }
        kiki();kiki();kiki();kiki();kiki();kiki();kiki();kiki();kiki();kiki();
/*
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            HANDLEEVENTS();
        }
*/
        if  (sf::Mouse::isButtonPressed(sf::Mouse::Right) && SFMLView1.hasFocus())
            ESCAPE=1;
        if (ESCAPE==1)
        {
            ESCAPE=0;
            goexit=0;
            shift=0;
            ffmpegfile=1;
            forced_jump=1;
            follow_ghost_pos();
            ReadBitmaps2();
            ReadBitmaps4();
            size_ffmpeg=0;
            ffmpeg_move=0;
            border_col_r=0;
            border_col_g=0;
            border_col_b=0;
            return;
        }
//        n=GETPICTURE(naam);
//        printf("n=%d\n",n);
        if (fgets(naam,2000,ff)==NULL)
//        if (n==-1)
        {
            shift=0;
            ffmpegfile=1;
            forced_jump=1;
            follow_ghost_pos();
            ReadBitmaps2();
            ReadBitmaps4();
            strcpy(error_msg3,"PRESS CTRL+SHIFT+R TO CROP BEFORE RECORDING ('r')");
            printf("%s\n",error_msg3);
            error_flag3=1;
            size_ffmpeg=0;
            ffmpeg_move=0;
            border_col_r=0;
            border_col_g=0;
            border_col_b=0;
            return;
        }
        if (naam[strlen(naam)-1]=='\r' || naam[strlen(naam)-1]=='\n')
            naam[strlen(naam)-1]='\0';
        /*
                render_picturex=render_picturex_mem;
                render_picturey=render_picturey_mem;
                render_posx=render_posx_mem;
                render_posy=render_posy_mem;

                picturex=picturex_mem;
                picturey=picturey_mem;
                posx=posx_mem;
                posy=posy_mem;
        */
    }
    border_col_r=0;
    border_col_g=0;
    border_col_b=0;
}

void batch_pictures2()
{
    int x;
    int y;
    int x_old;
    float y_count=0.0;
    float count_y=0.0;
    int new_mazemovex=-1;
    int new_mazemovey;
    crop_x=32;
    crop_x_size=0;
    crop_y_size=0;
    char naam[2000];
    ffmpegfile=1;
    size_ffmpeg=0;
    ffmpeg_move=0;
//    sprite_from_ffmpeg.setScale(1.0,1.0);
    rotate_ffmpeg=0;
    rotation_ffmpeg=0;
    float scale=sprite_from_ffmpeg.getScale().x;
    int size_y_pref=0;
    int size_x_pref=0;
    int x_position=(picturex*1920-posx);
//    int x_position=1920/2;
    double screen_x=x_position;
//    int screen_x=x_position-1920/2;
    int y_position=(picturey*1080-posy);
//    int y_position=0;
    double screen_y=y_position;
//    int screen_y=0;

    rotate_ffmpeg=0;
    rotation_ffmpeg=0;
//            scale_now=1.0;

    float count_y_tot=0.0;
    mirror=0;
    int n=0;
    strcpy(naam,"RESET");
    n=GETPICTURE(naam);
    if (n==0)
    {
        strcpy(error_msg2,"PICTURE LIST EMPTY");
        error_flag2=1;
        size_ffmpeg=0;
        ffmpeg_move=0;
        return;
    }
    while (true)
    {
        if (file_exists(naam))
        {
            if (Inter.loadFromFile(naam))
            {
                if (texture_from_ffmpeg.loadFromImage(Inter))
                {
                    ffmpegfile=0;
                    texture_from_ffmpeg.setRepeated(TRUE);
                    if (smooth==1)
                        texture_from_ffmpeg.setSmooth(TRUE);
                    else
                        texture_from_ffmpeg.setSmooth(FALSE);
                    if (size_y_pref==0)
                        size_y_pref=texture_from_ffmpeg.getSize().y;
                    if (size_x_pref==0)
                        size_x_pref=texture_from_ffmpeg.getSize().x;

                    /*
                                        sprite_from_ffmpeg.setTextureRect( { 0,0,(int)texture_from_ffmpeg.getSize().x, (int)texture_from_ffmpeg.getSize().y } );
                                        add_border_left_right(&texture_from_ffmpeg);
                                        if (ffmpegfile==1) return;
                    */



                                        sprite_from_ffmpeg.setTextureRect( { 0,0,(int)texture_from_ffmpeg.getSize().x, (int)texture_from_ffmpeg.getSize().y } );
                                        soften_edge(&texture_from_ffmpeg);
                                        if (ffmpegfile==1) return;

                                        sprite_from_ffmpeg.setTextureRect( { 0,0,(int)texture_from_ffmpeg.getSize().x, (int)texture_from_ffmpeg.getSize().y } );
                                        add_border(&texture_from_ffmpeg);
                                        if (ffmpegfile==1) return;

                                        sprite_from_ffmpeg.setTextureRect( { 0,0,(int)texture_from_ffmpeg.getSize().x, (int)texture_from_ffmpeg.getSize().y } );
                                        soften_edge(&texture_from_ffmpeg);
                                        if (ffmpegfile==1) return;

                                        sprite_from_ffmpeg.setTextureRect( { 0,0,(int)texture_from_ffmpeg.getSize().x, (int)texture_from_ffmpeg.getSize().y } );



//                    make_white_transparant(&texture_from_ffmpeg);

                    texture_from_ffmpeg.setRepeated(TRUE);
                    if (smooth==1)
                        texture_from_ffmpeg.setSmooth(TRUE);
                    else
                        texture_from_ffmpeg.setSmooth(FALSE);
                    texture_from_ffmpeg.generateMipmap();
                }
                else
                {
                    sprintf(error_msg2,"FAILED LOADING %s",naam);
                    error_flag2=1;
                    printf("FAILED LOADING %s\n",naam);
                    savedata((char*)"failed loading1, to large? Then remove from list.",0);
                    size_ffmpeg=0;
                    ffmpeg_move=0;
                    return;
                }
            }
            else
            {
                sprintf(error_msg2,"FAILED LOADING %s",naam);
                error_flag2=1;
                printf("FAILED LOADING %s\n",naam);
                savedata((char*)"failed loading2, to large? Then remove from list.",0);
                size_ffmpeg=0;
                ffmpeg_move=0;
                return;
            }
        }
        else
        {
            sprintf(error_msg2,"FAILED LOADING %s FILE DOES NOT EXIST",naam);
            error_flag2=1;
            printf("FAILED LOADING %s FILE DOES NOT EXIST\n",naam);
            savedata((char*)"failed loading, file does not exists: ",0);
            savedata((char*)naam,0);
            size_ffmpeg=0;
            ffmpeg_move=0;
            return;
        }
        //        Inter.create(0,0);

//        if (n==1) screen_y=(-1080+maxpixelsy+y_position+texture_from_ffmpeg.getSize().y/2*scale)%maxpixelsy;
//        printf("n=%d\n",n);

//        if (n==1) screen_y=texture_from_ffmpeg.getSize().y/2*scale-1080;
//        if (n==1) screen_x=texture_from_ffmpeg.getSize().x/2*scale-1920;

        if (texture_from_ffmpeg.getSize().x*scale>crop_x_size)
            crop_x_size=texture_from_ffmpeg.getSize().x*scale;
        if (texture_from_ffmpeg.getSize().y*scale>crop_y_size)
            crop_y_size=texture_from_ffmpeg.getSize().y*scale;

//        if (n==1) screen_y=texture_from_ffmpeg.getSize().y/2;
//        if (n==1) screen_y=texture_from_ffmpeg.getSize().y/2-1080/2;

        if (new_mazemovex==-1)
        {
            new_mazemovex=((int)screen_x-32)/64;
            new_mazemovey=((int)screen_y   )/72;
            new_mazemovex=(new_mazemovex-45+maze_plotsizex)%maze_plotsizex;
            new_mazemovey=(new_mazemovey-23+maze_plotsizey)%maze_plotsizey;
            mazemovex=new_mazemovex;
            mazemovey=new_mazemovey;
            y=new_mazemovey;
            x=new_mazemovex;
        }
        else
        {
            mazemovex=(new_mazemovex+maze_plotsizex)%maze_plotsizex;
            mazemovey=new_mazemovey%maze_plotsizey;
            y=mazemovey;
            x=mazemovex;
        }

        double alpha;
        alpha=acos((double)(texture_from_ffmpeg.getSize().y*sprite_from_ffmpeg.getScale().y+200)/(double)(BITMAPSX*1920.0));
//        alpha=acos((double)(texture_from_ffmpeg.getSize().y*sprite_from_ffmpeg.getScale().y+1100)/(double)(BITMAPSX*1920.0));

        rotation_ffmpeg=(float)(90-180.0*alpha/3.141592653589793);
        screen_x=screen_x+sin(alpha)*( (size_x_pref+texture_from_ffmpeg.getSize().x )*sprite_from_ffmpeg.getScale().x)/2.0+0.01;
        screen_y=screen_y+cos(alpha)*( (size_x_pref+texture_from_ffmpeg.getSize().x )*sprite_from_ffmpeg.getScale().x)/2.0;


        new_mazemovex=((int)screen_x-32)/64;
        new_mazemovey=((int)screen_y   )/72;
        new_mazemovex=(new_mazemovex-45);
        new_mazemovey=(new_mazemovey-23);

        screen_x=fmod(screen_x+(double)maxpixelsx,(double)maxpixelsx);

        size_x_pref=texture_from_ffmpeg.getSize().x;
        size_y_pref=texture_from_ffmpeg.getSize().y;

        smooth_x=screen_x;
        smooth_y=screen_y;

        picturex=(int)screen_x/1920;
        render_picturex=picturex;
        posx=(int)screen_x-1920*picturex;
        picturey=(int)screen_y/1080;
        render_picturey=picturey;
        posy=(int)screen_y-1080*picturey;
        posx=-posx;
        render_posx=posx;
        posy=-posy;
        render_posy=posy;


        render_picturex=picturex;
        render_posx=posx;
        render_picturey=picturey;
        render_posy=posy;

        if (ffmpegfile==0)
        {
            texture_from_ffmpeg.setRepeated(TRUE);
            if (smooth==1)
                texture_from_ffmpeg.setSmooth(TRUE);
            else
                texture_from_ffmpeg.setSmooth(FALSE);

            sprite_from_ffmpeg.setTexture(texture_from_ffmpeg,false);

            setffmpegfile();
            if ( (vertex_shader==1 || fragment_shader==1) )
            {
//                perform_quit=1;
//                plot_ffmpegfile=1;
                picture_shader.setUniform("iRotate", (float)(sprite_from_ffmpeg.getRotation()/360.0*2.0*PI));
                if (buffer_shader==1)
                    shader_buffer.setUniform("iRotate", (float)(sprite_from_ffmpeg.getRotation()/360.0*2.0*PI));
                picture_shader.setUniform("texture_buffer", texture_from_ffmpeg);
                picture_shader.setUniform("iResolution_buffer",  sf::Vector2f( texture_from_ffmpeg.getSize().x,texture_from_ffmpeg.getSize().y) );
                picture_shader.setUniform("iResolution",  sf::Vector2f( texture_from_ffmpeg.getSize().x,texture_from_ffmpeg.getSize().y) );
//                plot_some();
//                perform_quit=0;
            }


//            rotation_ffmpeg=rand()%11-5;
//            rotation_ffmpeg=0.0;
//            sprite_from_ffmpeg.setScale(1.0,1.0);
            perform_quit=1;
            plot_ffmpegfile=1;
            plotplot();
            perform_quit=0;
        }

        new_mazemovex=((int)screen_x-32)/64;
        new_mazemovey=((int)screen_y   )/72;
        new_mazemovex=(new_mazemovex-45);
        new_mazemovey=(new_mazemovey-23);


        if (new_mazemovex<mazemovex)
            new_mazemovex+=maze_plotsizex;
        if (new_mazemovey<mazemovey)
            new_mazemovey+=maze_plotsizey;

        if (mazemovex<0 || new_mazemovex<0)
        {
            mazemovex+=maze_plotsizex;
            new_mazemovex+=maze_plotsizex;
        }
        if (mazemovey<0 || new_mazemovey<0)
        {
            mazemovey+=maze_plotsizey;
            new_mazemovey+=maze_plotsizey;
        }
//        float y_count=0.0;

        float count_y=0.0;
        y=mazemovey;
        count_y_tot=0.0;
//        int xdiff=new_mazemovex-mazemovex;
//        int ydiff=new_mazemovey-mazemovey;
        if (new_mazemovex-mazemovex>0)
            count_y=(float)(new_mazemovey-mazemovey)/(float)(new_mazemovex-mazemovex);
        count_y_tot+=count_y;

        for (x=mazemovex+1; x<=new_mazemovex; x++)
        {
            maze_plot[x%maze_plotsizex][y%maze_plotsizey]=maze_plot[x%maze_plotsizex][y%maze_plotsizey]|8;
            maze_plot[(x+1)%maze_plotsizex][y%maze_plotsizey]=maze_plot[(x+1)%maze_plotsizex][y%maze_plotsizey]|4;
            if (drawmazes==1 && blank_maze==0)
            {
                do_mirror(x,y,maze_plot[x%maze_plotsizex][y%maze_plotsizey]);
                do_mirror((x+1)%maze_plotsizex,y%maze_plotsizey,maze_plot[(x+1)%maze_plotsizex][y%maze_plotsizey]);
            }
            count_y_tot+=count_y;
            if (count_y_tot>1.0)
            {
                count_y_tot-=1.0;
                maze_plot[(x+1)%maze_plotsizex][y%maze_plotsizey]=maze_plot[(x+1)%maze_plotsizex][y%maze_plotsizey]|2;
                maze_plot[(x+1)%maze_plotsizex][(y+1)%maze_plotsizey]=maze_plot[(x+1)%maze_plotsizex][(y+1)%maze_plotsizey]|1;
                if (drawmazes==1 && blank_maze==0)
                {
                    do_mirror((x+1)%maze_plotsizex,y%maze_plotsizey,maze_plot[(x+1)%maze_plotsizex][y%maze_plotsizey]);
                    do_mirror((x+1)%maze_plotsizex,(y+1)%maze_plotsizey,maze_plot[(x+1)%maze_plotsizex][(y+1)%maze_plotsizey]);
                }
                y++;
            }
        }

        if (plot_all)
        {
            update_plot_all();
        }
        else
            blitter("",1);


        if (screen_y+texture_from_ffmpeg.getSize().y*scale>=maxpixelsy)
        {
            strcpy(error_msg4,"END OF SCREEN REACHED, ABORTING");
            printf("%s\n",error_msg4);
            error_flag4=1;
            shift=0;
            ffmpegfile=1;
            forced_jump=1;
            follow_ghost_pos();
            ReadBitmaps2();
            ReadBitmaps4();
            strcpy(error_msg3,"PRESS CTRL+SHIFT+R TO CROP BEFORE RECORDING ('r')");
            printf("%s\n",error_msg3);
            error_flag3=1;
            size_ffmpeg=0;
            ffmpeg_move=0;
            return;
        }

        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            HANDLEEVENTS();
        }
        if  (sf::Mouse::isButtonPressed(sf::Mouse::Right) && SFMLView1.hasFocus())
            ESCAPE=1;
        if (ESCAPE==1)
        {
            ESCAPE=0;
            goexit=0;
            shift=0;
            ffmpegfile=1;
            forced_jump=1;
            follow_ghost_pos();
            ReadBitmaps2();
            ReadBitmaps4();
            size_ffmpeg=0;
            ffmpeg_move=0;
            return;
        }
        n=GETPICTURE(naam);
        if (n==1 && 0)
        {
            shift=0;
            ffmpegfile=1;
            forced_jump=1;
            follow_ghost_pos();
            ReadBitmaps2();
            ReadBitmaps4();
            strcpy(error_msg3,"PRESS CTRL+SHIFT+R TO CROP BEFORE RECORDING ('r')");
            printf("%s\n",error_msg3);
            error_flag3=1;
            size_ffmpeg=0;
            ffmpeg_move=0;
            return;
        }
        /*
                render_picturex=render_picturex_mem;
                render_picturey=render_picturey_mem;
                render_posx=render_posx_mem;
                render_posy=render_posy_mem;

                picturex=picturex_mem;
                picturey=picturey_mem;
                posx=posx_mem;
                posy=posy_mem;
        */
    }
}


void do_the_recording_stuff()
{
    if (blocked_by_window) return;
    if ((movieextern==0 && record_pause==0 && recording_type==0) || (movieextern==0 && record_pause==0 && record_screen==1))
    {
        rate_count--;
        if (rate_count<=0)
        {
            rate_count=play_rate;
//                printf("frame: %d Screenget3()\n",frame_counter);
//            printf("main: screenget3(), ");
            if (play_rate>0)
                Screenget3();
        }
    }

    if (record_screen==1)
    {
        fpstime=fpstime_factor*(float)record_screen_num*(float)rate/60.0;
    }
    else
    {
        fpstime=fpstime_factor*clock_shader.getElapsedTime().asSeconds();
    }

    if (record_screen==1)
    {
//record speed
        if (record_pause==0)
        {
            flop++;
//joepie
            if (flop==rate)
                flop=0;
            /*
                        if (flop==0)
                            flop=1;
                        else
                            flop=0;
            */
            if (flop==0)
            {
//                    printf("frame: %d Screenshot3()\n",frame_counter);
                if (recording_type==0)
                {
//                        if (follow_ghost==1 && floor(fspeed_ghostx[follow_ghost_num])==fspeed_ghostx[follow_ghost_num] && floor(fspeed_ghosty[follow_ghost_num])==fspeed_ghosty[follow_ghost_num]) {
//                            static int oldx=0,oldy=0;
//                            forced_jump=1;
//                            follow_ghost_pos();
//                            printf("RECORD: x=%d,y%d speedx=%f,speedy=%f fposx=%f,fposy=%f\n",(render_picturex*1920-render_posx),(render_picturey*1080-render_posy) ,
//                                    fspeed_ghostx[follow_ghost_num] , fspeed_ghosty[follow_ghost_num] ,
//                                    fpos_ghostx[follow_ghost_num] , fpos_ghosty[follow_ghost_num]);
//                            if (fspeed_ghostx[follow_ghost_num]!=0.0) if ( abs(render_picturex*1920-render_posx - oldx) != 2) printf("!!!!!!!!!!\n");
//                            if (fspeed_ghosty[follow_ghost_num]!=0.0) if ( abs(render_picturey*1080-render_posy - oldy) != 2) printf("!!!!!!!!!!\n");
//                            oldx=render_picturex*1920-render_posx;
//                            oldy=render_picturey*1080-render_posy;
//                        }
//hotshot
                    Screenshot3();
                    record_screen_num++;
                }
                else if (recording_type==1)
                    Screenshot3_m_orig();
//jojojo
                if ((f8_repeat!=0 || mirror!=0) && movie==0 && record_pause==0) {
                    updatemovie();
                }
                else if (record_screen==1 && record_pause==0 && movie==0 ) // change mafkees movie function....
                {
                    if (live_movie->getStatus()==sfe::Playing && timer_movie==0 && live_movie_is_mp3==0 && tune==1)
                    {
                        live_movie->pause();
                        time_movie=live_movie->getPlayingOffset();
                    }
                    else
                    {
                        if (tune==0)
                            time_movie=live_movie->getPlayingOffset();
                        if (timer_movie>0)
                            timer_movie--;
                        if (live_movie->getStatus()!=sfe::End && live_movie->getStatus()!=sfe::Stopped && tune==1)
                            updatemovie();
                        if (recording_type==0)
                        {
                            if (tune==1)
                                time_movie=time_movie+sf::seconds((float)rate/60.0);
                        }
                        else if (recording_type==1)
                        {
                            float frame_rate=live_movie->getFramerate();
                            if (frame_rate==0.0)
                                frame_rate=30.0;
                            if (tune==1)
                                time_movie=time_movie+sf::seconds(1.0/frame_rate);
                            if (live_movie->getStatus()==sfe::End || live_movie->getStatus()==sfe::Stopped)
                            {
                                record_screen=0;
                                sprintf(error_msg,"RECORDING STOPPED, MOVIE SHIFT-M ENDED");
                                error_flag=1;
                            }
                        }
                    }
                    if (live_movie->getStatus()!=sfe::End
                            && live_movie->getStatus()!=sfe::Stopped
                            && time_movie<live_movie2->getDuration() )
                    {
                        int ret=true;
                        if (timer_movie==0 && live_movie_is_mp3==0)
                            if (tune==1)
                                ret=live_movie->setPlayingOffset(time_movie);
                        if (recording_type==1)
                        {
                            if (ret==false)
                            {
                                sprintf(error_msg,"RECORDING STOPPED, MOVIE SHIFT-M ENDED, OFFSET FAILED");
                                error_flag=1;
                                updatemovie();
                                time_movie=live_movie->getPlayingOffset();
                            }
                        }
                    }
                    else
                    {
                        sprintf(error_msg,"RECORDING STOPPED, MOVIE SHIFT-M ENDED, OFFSET > DURATION");
                        error_flag=1;
                        updatemovie();
                        time_movie=live_movie->getPlayingOffset();
                    }
                }
                if (record_screen==1 && record_pause==0 && movie2==0)
                {
                    if (live_movie2->getStatus()==sfe::Playing && timer_movie2==0 && live_movie2_is_mp3==0 && tune==1)
                    {
                        live_movie2->pause();
                        time_movie2=live_movie2->getPlayingOffset();
                    }
                    else
                    {
                        if (tune==0)
                            if (timer_movie2>0)
                                timer_movie2--;
                        if (live_movie2->getStatus()!=sfe::End && live_movie2->getStatus()!=sfe::Stopped && tune==1)
                            updatemovie2();
                        if (tune==1)
                            time_movie2=time_movie2+sf::seconds((float)rate/60.0);
                    }

                    if (live_movie2->getStatus()!=sfe::End
                            && live_movie2->getStatus()!=sfe::Stopped
                            && time_movie2<live_movie2->getDuration() )
                    {
                        int ret=true;
                        if (timer_movie2==0 && live_movie2_is_mp3==0)
                            if (tune==1)
                                ret=live_movie2->setPlayingOffset(time_movie2);
                        if (ret==false)
                        {
                            sprintf(error_msg,"RECORDING STOPPED, MOVIE SHIFT-B ENDED, OFFSET FAILED");
                            error_flag=1;
                            updatemovie2();
                            time_movie2=live_movie2->getPlayingOffset();
                        }
                    }
                    else
                    {
//                            movie2=1;
                        sprintf(error_msg,"RECORDING STOPPED, MOVIE SHIFT-B ENDED, OFFSET > DURATION");
                        error_flag=1;
                        updatemovie2();
                        time_movie2=live_movie2->getPlayingOffset();
                    }
                }
            }
        }
    }
}

void plot_ghosts()
{
    if (cool==1 && current==4 && !(record_screen==1 && record_pause==1))
    {
        mutje.lock();
        if (current==4)
        {
            if (plot_all==1 && handler[CANVAS_SELECT].show==1)
                effects[current]->update(the_time, 1.0/sprite_from_canvas.getScale().x, 1.0/sprite_from_canvas.getScale().y);
            else
                effects[current]->update(the_time, 1.0, 1.0);
//here1
            if (blending>=1 || shade_main!=0 || blendit==1)
            {
                texture_final.setActive(true);
                texture_final.pushGLStates();
            }
            else
            {
                SFMLView1.setActive(true);
                SFMLView1.pushGLStates();
            }

            glEnable(GL_TEXTURE_2D);
            glEnable(GL_DEPTH_CLAMP);
            glEnable(GL_DEPTH_TEST);
            glDepthMask(GL_FALSE);
            glDepthFunc(GL_LEQUAL);
            glDepthRange(0.0f, 1.0f);
            glClearDepth(0.0f);
            if (blending>=1 || shade_main!=0 || blendit==1)
            {
                texture_final.draw(*effects[current]);
                texture_final.popGLStates();
            }
            else
            {
                SFMLView1.draw(*effects[current]);
                SFMLView1.popGLStates();
            }

        }
        mutje.unlock();
    }
}

extern void set_cube();
sf::Vector2f fixit;
float scale_factor=2.0;

sf::Mutex cube_plot;

void plot_cubes_vertex()
{
//    if (!plot_all) {
//        setcanvasfile();
//        shader_map_angle=rotation_canvas;
//    }

    static int first=1;
    int w=10,h=10;
    scale_factor=2.0;
    if (first==1) {
//        set_cube();
        first=0;
        cube_plot.lock();
        m_pointCloud3.clear();
//        m_pointCloud3.resize(w*h);
        int num=0;
        for (int x=0; x<w; x++) {
            for (int y=0; y<h; y++) {
                m_pointCloud3.append(
                    sf::Vertex(
                        sf::Vector2f(
                            (float)(x),
                            (float)(y)
                        ),
                        sf::Color(
                                rand()%256,
                                rand()%256,
                                rand()%256,
                                (rand()%3+rand()%3+rand()%3)
                        ),
                        sf::Vector2f(
                            (float) (((x+y+1000)%6)*256)*150.0,
                            (float) (0)*150.0
                        )
                    )
                );
/*
                m_pointCloud3[num].position.x=((float)x);
                m_pointCloud3[num].position.y=((float)y);
                m_pointCloud3[num].texCoords.x = (float) (((x+y+1000)%6)*256)*150.0;
                m_pointCloud3[num].texCoords.y = (float) (0)*150.0;
                m_pointCloud3[num].color = sf::Color(
                                    rand()%256,
                                    rand()%256,
                                    rand()%256,
                                    (rand()%3+rand()%3+rand()%3)
                                    );
*/
                num++;
            }
        }
        cube_plot.unlock();
    }

    int verschilx=-(picturex*1920-posx);       int offsetx=verschilx;
    int verschily=-(picturey*1080-posy);       int offsety=verschily;

    if (smooth) {
        fixit.x=(float) fmod(
                           offsetx+new_verschilx+new_verschilx2 +128/scale_factor+maxpixelsx,
//                           (-(float)smooth_x+(float)((int)smooth_x)),
                           maxpixelsx)-(float)maxpixelsx*0.5;
        fixit.y=(float) fmod(
                           offsety+new_verschily+new_verschily2 +128/scale_factor+maxpixelsy*1.5-540.0,
//                           (-(float)smooth_y+(float)((int)smooth_y)),
                           maxpixelsy)-(float)maxpixelsy*0.5+540.0;
    } else {
        fixit.x=(float) fmod(
                           offsetx+new_verschilx+new_verschilx2  +128/scale_factor+maxpixelsx,
                           maxpixelsx)-(float)maxpixelsx*0.5;
        fixit.y=(float) fmod(
                           offsety+new_verschily+new_verschily2  +128/scale_factor+maxpixelsy*1.5-540.0,
                           maxpixelsy)-(float)maxpixelsy*0.5+540.0;
    }

    if (smooth) {
        fixit.x+=(-(float)smooth_x+(float)((int)smooth_x));
        fixit.y+=(-(float)smooth_y+(float)((int)smooth_y));
    }

    fixit.x*=scale_factor;
    fixit.y*=scale_factor;


    if (fixit.x<=-maxpixelsx/2) fixit.x=fixit.x+maxpixelsx;   else if (fixit.x>maxpixelsx/2) fixit.x=fixit.x-maxpixelsx;
    if (fixit.y<=-maxpixelsy/2) fixit.y=fixit.y+maxpixelsy;   else if (fixit.y>maxpixelsy/2) fixit.y=fixit.y-maxpixelsy;

//    if (plot_all==1 && handler[CANVAS_SELECT].show==1)
        cube_effect->update(the_time, 1.0/sprite_from_canvas.getScale().x, 1.0/sprite_from_canvas.getScale().y);
//    else
//        cube_effect->update(the_time, 1.0, 1.0);

    if (blending>=1 || shade_main!=0 || blendit==1)
    {
        texture_final.setActive(true);
        texture_final.pushGLStates();
    }
    else
    {
        SFMLView1.setActive(true);
        SFMLView1.pushGLStates();
    }

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_CLAMP);
    glEnable(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);
    glDepthRange(0.0f, 1.0f);
    glClearDepth(0.0f);
    glAlphaFunc(GL_GREATER, 0.0);
    glEnable(GL_ALPHA_TEST);

//    glPolygonMode(GL_FRONT, GL_LINE);
//    glPolygonMode(GL_BACK, GL_LINE);
//    glDisable(GL_POLYGON_OFFSET_FILL);
//    glDisableClientState(GL_COLOR_ARRAY);
//    glDisableClientState(GL_TEXTURE_COORD_ARRAY);

    cube_plot.lock();
    if (blending>=1 || shade_main!=0 || blendit==1)
    {
        texture_final.draw(*cube_effect);
        texture_final.popGLStates();
    }
    else
    {
        SFMLView1.draw(*cube_effect);
        SFMLView1.popGLStates();
    }
    cube_plot.unlock();
}


char * seconds_to_time(float finputSecond)
{
    int inputSecond=(int)finputSecond;
    //10 because if you call it twice or more in one statement/function call, only the last one is printed to all.... :\ (programmers fault #234.24234.234.423-sub a
    static char t_str[10][20];
    static int cnt=0;
    cnt++;
    if (cnt==10)
        cnt=0;
    strcpy(t_str[cnt],"Error!!");
    int hours,minutes,seconds;
    int remainingSeconds;
    int secondsInHour = 3600;
    int secondsInMinute = 60;
    hours = (inputSecond/secondsInHour);
    remainingSeconds = inputSecond - (hours * secondsInHour);
    minutes = remainingSeconds/secondsInMinute;
    remainingSeconds = remainingSeconds - (minutes*secondsInMinute);
    seconds = remainingSeconds;
    sprintf(t_str[cnt],"%02d:%02d:%02d.%02d",hours,minutes,seconds,(int)(100.0*(finputSecond-(int)finputSecond)));
    return t_str[cnt];
}

void update_plot_all()
{
    setcanvasfile();
    shader_map_angle=rotation_canvas;

//here2
    monitor_off=1;

    if (blending>=1 || shade_main!=0 || blendit==1)
    {
        texture_final.pushGLStates();
    }
    else
    {
        SFMLView1.pushGLStates();
    }
//            SFMLView1.pushGLStates();

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_CLAMP);
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);
    glDepthRange(0.0f, 1.0f);
    glClearDepth(0.0f);
    glAlphaFunc(GL_GREATER, 0.0);
    glEnable(GL_ALPHA_TEST);

    if (blending>=1 || shade_main!=0 || blendit==1)
    {
        texture_final.setActive(false);
    }
    else
    {
        SFMLView1.setActive(false);
    }
//            SFMLView1.setActive(false);

    int fromx=-BITMAPSX/2+1;
    if (fromx<-3)
        fromx=-3;
    int tox=BITMAPSX/2;
    if (tox>4)
        tox=4;
    int fromy=-BITMAPSY/2+1;
    if (fromy<-3)
        fromy=-3;
    int toy=BITMAPSY/2;
    if (toy>4)
        toy=4;
    for (x=fromx; x<=tox; x++)
    {
        for (y=fromy; y<=toy; y++)
        {
            int arx=(render_picturex+x+BITMAPSX)%BITMAPSX;
            int ary=(render_picturey+y+BITMAPSY)%BITMAPSY;
            if (used[arx][ary]!=0)
                shader_map(x,y);
//                    else {
            if (totalused>MAXINMEM)
            {
                go_save_some_bitmaps();
            }
//                        SFMLView1.setActive(true);
//                        ReadOneBitmap(arx,ary);
//                        SFMLView1.setActive(false);
//                        shader_map(x,y);
//                    }
        }
    }
//here1
    if (blending>=1 || shade_main!=0 || blendit==1)
    {
        SFMLView1.setActive(false);
        sf::Sprite sprite_final;
        sprite_final.setTexture(texture_final.getTexture(),false);
        sprite_final.setTextureRect({0,0,1920,1080});
        sprite_final.setPosition(0,0);
        texture_final.display();
        if (shade_main!=0)
        {
            SFMLView1.draw(sprite_final);
        }
        else
        {
            SFMLView1.draw(sprite_final);
        }
        SFMLView1.display();
        SFMLView1.setActive(true);
        SFMLView1.popGLStates();

        do_the_recording_stuff();
    }
    else
    {
        SFMLView1.display();
        SFMLView1.setActive(true);
        SFMLView1.popGLStates();
    }

    if (blending>=1 || shade_main!=0 || blendit==1)
    {
        texture_final.setActive(true);
        if (drawmazes==1 && kleur_back==1)
            glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        else if (drawmazes==0 && kleur_back==0)
            glClearColor(0.0f, 0.0f, 0.0f, (float)(set_transparant==0));
        else if (drawmazes==0 && kleur_back==1)
            glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        else
            glClearColor(0.0f, 0.0f, 0.0f, (float)(set_transparant==0));
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        texture_final.setActive(false);

        SFMLView1.setActive(true);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        SFMLView1.setActive(false);
    }
    else
    {
        SFMLView1.setActive(true);
        if (drawmazes==1 && kleur_back==1)
            glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        else if (drawmazes==0 && kleur_back==0)
            glClearColor(0.0f, 0.0f, 0.0f, (float)(set_transparant==0));
        else if (drawmazes==0 && kleur_back==1)
            glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        else
            glClearColor(0.0f, 0.0f, 0.0f, (float)(set_transparant==0));
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        SFMLView1.setActive(false);
    }

}
extern void shader_map_init(int x,int y);
int CapsLock=0;

int y_bar[5]={0,0,0,0,0};

void update_plot_all2(int plot_front)
{
//    if (plot_front==0) {
        setcanvasfile();
//    }
    if (!((blending>=1 && handler[CANVAS_SELECT].blending==0) || handler[CANVAS_SELECT].blending>=1))
    {
//        if (plot_all && 1) {
        if (blending>=1 || shade_main!=0 || blendit==1)
        {
            texture_final.setActive(true);
            texture_final.pushGLStates();
        }
        else
        {
            SFMLView1.setActive(true);
            SFMLView1.pushGLStates();
        }

        glEnable(GL_TEXTURE_2D);
        glEnable(GL_DEPTH_CLAMP);
        glEnable(GL_DEPTH_TEST);
//        glDisable(GL_DEPTH_TEST);
        glDepthMask(GL_FALSE);
        glDepthMask(GL_TRUE);
        glDepthFunc(GL_LEQUAL);
        glDepthRange(0.0f, 1.0f);
        glClearDepth(0.0f);
        glAlphaFunc(GL_GREATER, 0.0);
        glEnable(GL_ALPHA_TEST);
//        glDisable(GL_ALPHA_TEST);
//        glEnable(GL_CLAMP_TO_EDGE);

        if (blending>=1 || shade_main!=0 || blendit==1)
        {
            texture_final.setActive(false);
        }
        else
        {
            SFMLView1.setActive(false);
        }
    }
    int fromx;
    int tox;
    int fromy;
    int toy;

//slots
extern int draw_model;
    if (draw_model==6) {
        fromx=0;
        tox=1;
        fromy=-9;
        toy=10;
//        fromy=-10;
//        toy=9;
    } else {
        fromx=-BITMAPSX/2+1;
        if (fromx<-3-plot_all_factor) fromx=-3-plot_all_factor;

        tox=BITMAPSX/2;
        if (tox>4+plot_all_factor) tox=4+plot_all_factor;

        fromy=-BITMAPSY/2+1;
        if (fromy<-3-plot_all_factor) fromy=-3-plot_all_factor;

        toy=BITMAPSY/2;
        if (toy>4+plot_all_factor) toy=4+plot_all_factor;
    }

//  fromx=-3; tox=4;
//  fromy=-6; toy=7;
    if (plot_front==0) {
        if (draw_model==6 && totalused+40>MAXINMEM) {
            int oldx=picturex,oldy=picturey;
            picturex=render_picturex;
            picturey=render_picturey;
            while (totalused+40>MAXINMEM && draw_model==6) {
                go_save_some_bitmaps();
            }
            picturex=oldx;
            picturey=oldy;
        }
        for (x=fromx; x<=tox; x++)
        {
            for (y=fromy; y<=toy; y++)
            {

                int arx=(render_picturex+x+BITMAPSX)%BITMAPSX;
                int ary=(render_picturey+y+BITMAPSY)%BITMAPSY;
                if (draw_model==6) arx=x    ;
                if (used[arx][ary]!=0) {
                    if (draw_model!=6) shader_map_init(x,y);
                }
                else
                {
                    if (totalused>MAXINMEM)
                    {
                        int oldx=picturex,oldy=picturey;
                        picturex=render_picturex;
                        picturey=render_picturey;

                        go_save_some_bitmaps();
                        if (totalused>MAXINMEM)
                        {
                            go_save_some_bitmaps();
                            if (totalused>MAXINMEM)
                            {
                                go_save_some_bitmaps();
                                if (totalused>MAXINMEM)
                                {
                                    go_save_some_bitmaps();
                                    if (totalused>MAXINMEM)
                                    {
                                        go_save_some_bitmaps();
                                        if (totalused>MAXINMEM)
                                        {
                                            go_save_some_bitmaps();
                                        }
                                    }
                                }
                            }
                        }
                        picturex=oldx;
                        picturey=oldy;
                    }
                    if (!((blending>=1 && handler[CANVAS_SELECT].blending==0) || handler[CANVAS_SELECT].blending>=1))
                    {
                        if (blending>=1 || shade_main!=0 || blendit==1)
                        {
                            texture_final.setActive(true);
                            texture_final.popGLStates();
                        }
                        else
                        {
                            SFMLView1.setActive(true);
                            SFMLView1.popGLStates();
                        }
                    }

                    ReadOneBitmap(arx,ary);

                    if (!((blending>=1 && handler[CANVAS_SELECT].blending==0) || handler[CANVAS_SELECT].blending>=1))
                    {
                        if (blending>=1 || shade_main!=0 || blendit==1)
                        {
                            texture_final.setActive(true);
                            texture_final.pushGLStates();
                        }
                        else
                        {
                            SFMLView1.setActive(true);
                            SFMLView1.pushGLStates();
                        }

                        glEnable(GL_TEXTURE_2D);
                        glEnable(GL_DEPTH_CLAMP);
                        glEnable(GL_DEPTH_TEST);
                //        glDisable(GL_DEPTH_TEST);
                        glDepthMask(GL_FALSE);
                        glDepthMask(GL_TRUE);
                        glDepthFunc(GL_LEQUAL);
                        glDepthRange(0.0f, 1.0f);
                        glClearDepth(0.0f);
                //        glAlphaFunc(GL_GREATER, 0.0);
                //        glEnable(GL_ALPHA_TEST);
                        glDisable(GL_ALPHA_TEST);
                //        glEnable(GL_CLAMP_TO_EDGE);


                        if (blending>=1 || shade_main!=0 || blendit==1)
                        {
                            texture_final.setActive(false);
                        }
                        else
                        {
                            SFMLView1.setActive(false);
                        }
                    }
                    if (draw_model!=6) shader_map_init(x,y);
                }
            }
        }
    }

extern void plot_it(int plot_front);
extern int kleur_back;

    int old_position_y=(render_picturey*1080-render_posy);
    int old_position_x=(render_picturex*1920-render_posx);

    if (draw_model==6) {
/*
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_DEPTH_CLAMP);
        glEnable(GL_DEPTH_TEST);
//        glDisable(GL_DEPTH_TEST);
        glDepthMask(GL_FALSE);
        glDepthMask(GL_TRUE);
        glDepthFunc(GL_LEQUAL);
        glDepthRange(0.0f, 1.0f);
        glClearDepth(0.0f);
//        glAlphaFunc(GL_GREATER, 0.0);
//        glEnable(GL_ALPHA_TEST);
        glDisable(GL_ALPHA_TEST);
//        glEnable(GL_CLAMP_TO_EDGE);
*/
        int position_y=old_position_y;
        int position_x=old_position_x;
//        int position_y;
//        int position_x;

extern void set_bars();
        set_bars();

        for (x=fromx; x<=tox; x++)
        {
            for (y=fromy; y<=toy; y++)
            {
//                posx=-posx;
//                posy=-posy;

                position_y=old_position_y;
                for (int x_bars=-2; x_bars<=2; x_bars++) {
//                    render_posx=0+960-(x_bars+0.5)*500;
//                    position_x=0-(x_bars+0.5)*500;
                    position_x=0-(x_bars)*500;
                    position_x=(position_x+maxpixelsx)%maxpixelsx;
                    render_picturex=position_x/1920;
                    render_posx=position_x-1920*render_picturex;
                    render_posx=-render_posx;



//                    position_y+=(2160+160*fpstime);
                    position_y=y_bar[x_bars+2];
//                    position_y=(x_bars+2)*(2160+160*fpstime);
                    position_y=(position_y+maxpixelsy)%maxpixelsy;
                    render_picturey=position_y/1080;
                    render_posy=position_y-1080*render_picturey;
                    render_posy=-render_posy;

                    shader_map_init(x_bars,y);
                }
/*
                render_posx=0+960-(-2+0.5)*500;
                render_picturex=(-2+BITMAPSX)%BITMAPSX;
                shader_map_init(-2,y);

//            position_y+=1080;
            position_y+=2160+160*fpstime;
            position_y=(position_y+maxpixelsy)%maxpixelsy;
            render_picturey=position_y/1080;
            render_posy=position_y-1080*render_picturey;
            render_posy=-render_posy;

                render_posx=0+960-(-1+0.5)*500;
                render_picturex=(-1+BITMAPSX)%BITMAPSX;
                shader_map_init(-1,y);

            position_y+=2160+160*fpstime;
            position_y=(position_y+maxpixelsy)%maxpixelsy;
            render_picturey=position_y/1080;
            render_posy=position_y-1080*render_picturey;
            render_posy=-render_posy;

                render_posx=0+960-(0+0.5)*500;
                render_picturex=(0+BITMAPSX)%BITMAPSX;
                shader_map_init(0,y);

            position_y+=2160+160*fpstime;
            position_y=(position_y+maxpixelsy)%maxpixelsy;
            render_picturey=position_y/1080;
            render_posy=position_y-1080*render_picturey;
            render_posy=-render_posy;

                render_posx=0+960-(1+0.5)*500;
                render_picturex=(1+BITMAPSX)%BITMAPSX;
                shader_map_init(1,y);

            position_y+=2160+160*fpstime;
            position_y=(position_y+maxpixelsy)%maxpixelsy;
            render_picturey=position_y/1080;
            render_posy=position_y-1080*render_picturey;
            render_posy=-render_posy;

                render_posx=0+960-(2+0.5)*500;
                render_picturex=(2+BITMAPSX)%BITMAPSX;
                shader_map_init(2,y);
*/
            }
        }
        render_picturey=old_position_y/1080;
        render_posy=old_position_y-1080*render_picturey;
        render_posy=-render_posy;
    }

    CapsLock = GetKeyState(0x14);

    plot_it(plot_front);

    if (draw_model==6) {
//        render_picturey=old_position_y/1080;
//        render_posy=old_position_y-1080*render_picturey;
//        render_posy=-render_posy;
//        render_picturey=(render_picturey+BITMAPSY)%BITMAPSY;

        render_picturex=old_position_x/1920;
        render_posx=old_position_x-1920*render_picturex;
        render_posx=-render_posx;

        render_picturey=old_position_y/1080;
        render_posy=old_position_y-1080*render_picturey;
        render_posy=-render_posy;
        for (int x_bars=-2; x_bars<=2; x_bars++) {
//            y_bar[x_bars+2]=(old_position_y+(int)(160*fpstime)*(x_bars+2))%maxpixelsy;
            y_bar[x_bars+2]=( old_position_y + (int)( 160*fpstime  ) )%maxpixelsy;
        }
    }

    if (!((blending>=1 && handler[CANVAS_SELECT].blending==0) || handler[CANVAS_SELECT].blending>=1))
    {
        if (blending>=1 || shade_main!=0 || blendit==1)
        {
            texture_final.setActive(true);
            texture_final.popGLStates();
        }
        else
        {
            SFMLView1.setActive(true);
            SFMLView1.popGLStates();
        }
        if (plot_front==1) {
            if (drawmazes==1 && kleur_back==1)
                glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
            else if (drawmazes==0 && kleur_back==0)
                glClearColor(0.0f, 0.0f, 0.0f, (float)(set_transparant==0));
    //                glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
            else if (drawmazes==0 && kleur_back==1)
                glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
            else
                glClearColor(0.0f, 0.0f, 0.0f, (float)(set_transparant==0));
    //                glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

        }
    }

    texture_final.setActive(false);
    SFMLView1.setActive(false);
}

float color_to_gradient() {
    static float gradient=0.0;
    float gradient_best=PI;
    float gradient_new;
    float gradient_diff;
    static float gradient_mem=0.0;
    static float avg=0.0;
    float avg_new;
    float avg_max=0.0;
    int xmem=2;
    int ymem=2;
    int xmem2=2;
    int ymem2=2;

    sf::Color pixel_arr[5][5];
    int x,y;

    for (x=0; x<5; x++) {
        for (y=0; y<5; y++) {

            xdraw=(-posx+960+x-2);
            if (xdraw>=1920)
            {
                xdraw=xdraw-1920;
                mapx=1;
            }
            else
                mapx=0;
            ydraw=(-posy+540+y-2);
            if (ydraw>=1080)
            {
                ydraw=ydraw-1080;
                mapy=1;
            }
            else
                mapy=0;

            int arx=(picturex+mapx)%(maxpicturex+1);
            int ary=(picturey+mapy)%(maxpicturey+1);
            sprite_point.setTexture(texturemaxinmempoint[used2[arx][ary]]->getTexture(),false);
            sprite_point.setTextureRect(   { xdraw, ydraw,1, 1 }  );
            sprite_point.setPosition(0,0);
            texture_point.clear();
            texture_point.draw(sprite_point);
            texture_point.display();
            image_point=texture_point.getTexture().copyToImage();
            pixel_color=image_point.getPixel(0,0);
            pixel_arr[x][y]=pixel_color;
        }
    }

    int choice=1;
    if (choice==1) {
        for (x=0; x<5; x++) {
            for (y=0; y<5; y++) {

                pixel_color=pixel_arr[x][y];

                avg_new=(float)(pixel_color.r+pixel_color.g+pixel_color.b)/(3.0*256.0);
                gradient_new=atan2( -sqrt(3)*(pixel_color.g-pixel_color.b) , 2*pixel_color.r-pixel_color.g-pixel_color.b );
                gradient_diff=fabs(gradient_new-gradient);
                if (gradient_diff>PI) gradient_diff=2.0*PI-gradient_diff;

                if (avg_new>0.0) {
                    if (gradient_diff<gradient_best) {
                        gradient_mem=gradient_new;
                        gradient_best=gradient_diff;
                        xmem=x;ymem=y;
                    }
                }
                if (avg_new>avg_max) {
                    avg_max=avg_new;
                    xmem2=x;ymem2=y;
                }
            }
        }

    //    xmem=2;ymem=2;
        avg=(float)(pixel_arr[xmem2][ymem2].r+pixel_arr[xmem2][ymem2].g+pixel_arr[xmem2][ymem2].b)/(3.0*256.0);
        if (avg==0.0)
            sprite_from_ffmpeg.setScale(0.1,0.1);
        else
            sprite_from_ffmpeg.setScale(0.1+0.6*avg,0.1+0.6*avg);

        gradient=atan2( -sqrt(3)*(pixel_arr[xmem][ymem].g-pixel_arr[xmem][ymem].b) , 2*pixel_arr[xmem][ymem].r-pixel_arr[xmem][ymem].g-pixel_arr[xmem][ymem].b );
    //    printf("gradient=%f, *180/pi=%f\n",gradient,gradient*180/PI);
        float fspeed=sqrt(pow(fspeedx,2.0)+pow(fspeedy,2.0));
        if (avg==0.0) {
            if (fspeed>0.0) {
                gradient=atan2(-fspeedy,-fspeedx);
                rotation_ffmpeg=gradient*180/PI;
            } else {
                rotate_ffmpeg=1;
                rot_speed_ffmpeg=1.0;
            }
        } else {
            rotation_ffmpeg=gradient*180/PI;
    //        rotation_ffmpeg=gradient*180/PI;
            rotate_ffmpeg=0;
            rot_speed_ffmpeg=0.0;
            if (mouse_move) {
              fposx=fposx-cos(gradient)*2.0;
              fposy=fposy-sin(gradient)*2.0;
    //          fposx=fposx-(xmem-2);
    //          fposy=fposy-(ymem-2);
              posx=fposx;
              posy=fposy;
            } else {
                fspeedx=-cos(gradient)*fspeed;
                fspeedy=-sin(gradient)*fspeed;
            }
        }

    //    ffmpeg_move=1;
    //    ffmpeg_posx=picturex*1920-posx+1920/2;
    //    ffmpeg_posy=picturey*1080-posy+1080/2;
    // end choice 1
    }
    if (choice==2) {
        for (x=0; x<5; x++) {
            for (y=0; y<5; y++) {

                pixel_color=pixel_arr[x][y];

                avg_new=(float)(pixel_color.r+pixel_color.g+pixel_color.b)/(3.0*256.0);

                gradient_new=atan2( -sqrt(3)*(pixel_color.g-pixel_color.b) , 2*pixel_color.r-pixel_color.g-pixel_color.b );

                gradient_diff=fabs(gradient_new-gradient);
                if (gradient_diff>PI) gradient_diff=2.0*PI-gradient_diff;

                if (avg_new>0.0) {
                    if (gradient_diff<gradient_best) {
                        gradient_mem=gradient_new;
                        gradient_best=gradient_diff;
                        xmem=x;ymem=y;
                    }
                }
                if (avg_new>avg_max) {
                    avg_max=avg_new;
                    xmem2=x;ymem2=y;
                }
            }
        }
    }
    if (choice==3) {
        for (x=0; x<5; x++) {
            for (y=0; y<5; y++) {
                pixel_color=pixel_arr[x][y];
                avg_new=(float)(pixel_color.r+pixel_color.g+pixel_color.b)/(3.0*256.0);
                gradient_new=atan2( -sqrt(3)*(pixel_color.g-pixel_color.b) , 2*pixel_color.r-pixel_color.g-pixel_color.b );
            }
        }
    }
    if (choice==4) {
        for (x=0; x<5; x++) {
            for (y=0; y<5; y++) {
                pixel_color=pixel_arr[x][y];
                avg_new=(float)(pixel_color.r+pixel_color.g+pixel_color.b)/(3.0*256.0);
                gradient_new=atan2( -sqrt(3)*(pixel_color.g-pixel_color.b) , 2*pixel_color.r-pixel_color.g-pixel_color.b );
            }
        }
    }
}

extern double tied,tied_total,tied_total_total;

extern char* pretty_number(const long long int input_val);
extern size_t mem_start;
extern size_t mem_now;
extern size_t mem_was;
extern long long int mem_dif;
extern long long int mem_tot_dif1;
extern long long int mem_tot_dif2;
extern size_t mem_first;
extern int loop;
extern long long unsigned int call;
extern long long int total_count;
extern long long unsigned int total_call;
extern int count_loops;
extern PROCESS_MEMORY_COUNTERS memory;
int first_mem=1;

extern int first_dot;
extern void plot_dot(int x, int y, int col);
extern int  map_mode;

PROCESS_MEMORY_COUNTERS check_memory_tofile(char* name)
{
    FILE* file;
    static sf::Clock my_time;
    float xpos;

//    PROCESS_MEMORY_COUNTERS memory;
    GetProcessMemoryInfo(GetCurrentProcess(), &memory, sizeof(memory));
    static PROCESS_MEMORY_COUNTERS memory_old=memory;
    int skip=0;
    if (strlen(name)==0) {
        skip=1;
    }

    if (skip==0)if (!file_exists("memory.txt")) first_mem=1;
    if (skip==0)file=fopen("memory.txt","a");
    if (first_mem==1) {
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
        map_mode=0;
        clear_map();
        CLEANBITMAPS();
        ReadBitmaps2();
        ReadBitmaps4();

        my_time.restart();
        for (x=0; x<1920; x++) plot_dot(x*16,0,7);
        first_mem=0;
        if (skip==1) {
            file=fopen("memory.txt","a");
        }
        fprintf(file,"   TIME   LOOPS   TOTAL       MEM FIRST   DIFFERENCE!       MEM START    DIFFERENCE         MEM NOW      LOOPS        LOOP AVG      LOOPS       TOTAL AVG      CALL        CALL AVG       CALL       TOTAL AVG\n");
        if (skip==1) {
            fclose(file);
        }
    }
    if (skip==0) fprintf(file,"%7.3f %7.3f %7.0f ",tied,tied_total,tied_total_total);
    if (skip==0) fprintf(file,"%15s ",pretty_number(mem_first));
    if (skip==0) fprintf(file,"%13s ",pretty_number(mem_tot_dif2));
    if (skip==0) fprintf(file,"%15s ",pretty_number(mem_start));
    if (skip==0) fprintf(file,"%13s ",pretty_number(mem_tot_dif1));
    if (skip==0) fprintf(file,"%15s ",pretty_number(mem_now));
    if (skip==0) if (count_loops>1) {
        fprintf(file,  "%10d %15s ", count_loops-1, pretty_number(mem_tot_dif1/(long long int)(count_loops-1) ) );
        if (total_count!=0) fprintf(file,  "%10d %15s", total_count, pretty_number(mem_tot_dif2/(long long int)total_count) );
        else fprintf(file,  "                          ");
    } else if (skip==0) fprintf(file,  "                                                     ");
    if (skip==0) if (call>0) {
        fprintf(file,  "%10d %15s ", call, pretty_number( mem_tot_dif1/(long long int)(call) ) );
        if (total_call!=0) fprintf(file,  "%10d %15s", total_call, pretty_number(mem_tot_dif2/(long long int)total_call) );
        else fprintf(file,  "                          ");
    } else if (skip==0) fprintf(file,  "                                                     ");
    if (skip==0) fprintf(file," %s\n",name);

//    fprintf(file,"%s WorkingSetSize = %d    Total: %9.3f Time: %9.6f\n",name, memory.WorkingSetSize,tied_total,tied);
    if (skip==0) fclose(file);
    xpos=my_time.getElapsedTime().asSeconds();
//    printf("x=%f\n",xpos);
    plot_dot((int)xpos,(int)  (100*(log( (double)(mem_tot_dif1)                                 )))  , 3);
    plot_dot((int)xpos,(int)  (100*(log( (double)(mem_tot_dif2)                                 )))  , 4);
    plot_dot((int)xpos,(int)  (100*(log( (double)(mem_tot_dif1/(long long int)(count_loops-1))  )))  , 5);
    plot_dot((int)xpos,(int)  (100*(log( (double)(mem_tot_dif1/(long long int)(call))           )))  , 6);

    plot_dot((int)xpos,(int)  (100*(log( (double)(mem_first)                                    )))  , 0);
    plot_dot((int)xpos,(int)  (100*(log( (double)(mem_start)                                    )))  , 2);
    plot_dot((int)xpos,(int)  (100*(log( (double)(mem_now)                                      )))  , 1);

    return memory;
}

//PROCESS_MEMORY_COUNTERS_EX pmc;

size_t get_mem() {

//    MEMORYSTATUSEX memInfo;
//    memInfo.dwLength = sizeof(MEMORYSTATUSEX);
//    GlobalMemoryStatusEx(&memInfo);

//    DWORDLONG totalVirtualMem = memInfo.ullTotalPageFile;

//    DWORDLONG virtualMemUsed = memInfo.ullTotalPageFile - memInfo.ullAvailPageFile;

//    DWORDLONG totalPhysMem = memInfo.ullTotalPhys;

//    printf("            totalVirtualMem = %u\n",  memInfo.ullTotalPageFile);
//    printf("            virtualMemUsed  = %u\n",  memInfo.ullTotalPageFile - memInfo.ullAvailPageFile);

    GetProcessMemoryInfo(GetCurrentProcess(), &memory, sizeof(memory));

//    GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));

//    GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));

//    SIZE_T virtualMemUsedByMe = pmc.PrivateUsage;



/*
    printf("                        cb = %ld\n", memory.cb);
    printf("            PageFaultCount = %ld\n", memory.PageFaultCount);
    printf("        PeakWorkingSetSize = %u\n", memory.PeakWorkingSetSize);
    printf("            WorkingSetSize = %u\n", memory.WorkingSetSize);
    printf("   QuotaPeakPagedPoolUsage = %u\n", memory.QuotaPeakPagedPoolUsage);
    printf("       QuotaPagedPoolUsage = %u\n", memory.QuotaPagedPoolUsage);
    printf("QuotaPeakNonPagedPoolUsage = %u\n", memory.QuotaPeakNonPagedPoolUsage);
    printf("    QuotaNonPagedPoolUsage = %u\n", memory.QuotaNonPagedPoolUsage);
    printf("             PagefileUsage = %u\n", memory.PagefileUsage);
    printf("         PeakPagefileUsage = %u\n", memory.PeakPagefileUsage);
*/



    return memory.WorkingSetSize;
//    return memory.WorkingSetSize+pmc.PrivateUsage;

}

void dopix(int x, int y, sf::Color col, sf::Image* local) {
    if (x>=0 && x<512+10 && y>=0 && y<512+10) {
        local->setPixel(x,y,col);
    }
}

void read_one_plot(int x, int y, sf::Image* image) {
    sf::RenderTexture texture_plot;
    sf::Sprite sprite_plot;
    sf::Image image_local;
    texture_plot.create(512+10,512+10);

    x=(x+maxpixelsx)%maxpixelsx;
    y=(y+maxpixelsy)%maxpixelsy;

    int loc_picturex=(int)x/1920;
    int loc_posx=x-1920*loc_picturex;
    loc_picturex=(loc_picturex+totalpicturex)%totalpicturex;
    int loc_picturey=(int)y/1080;
    int loc_posy=y-1080*loc_picturey;
    loc_picturey=(loc_picturey+totalpicturey)%totalpicturey;

    int mapx,mapy;

    int xdraw=(loc_posx);
    if (xdraw>=1920) { xdraw=xdraw-1920; mapx=1; }  else mapx=0;

    int ydraw=(loc_posy);
    if (ydraw>=1080) { ydraw=ydraw-1080; mapy=1; }  else mapy=0;

    int arx=(loc_picturex+mapx)%(totalpicturex);
    int ary=(loc_picturey+mapy)%(totalpicturey);

    if (totalused>MAXINMEM) { go_save_some_bitmaps();}
    if (used[arx][ary]==0) ReadOneBitmap(arx,ary);

    int xend;    int yend;
    if ((xdraw+512+10)>1920) { xend=1920-xdraw; } else xend=512+10;
    if ((ydraw+512+10)>1080) { yend=1080-ydraw; } else yend=512+10;

    sprite_plot.setTexture(texturemaxinmempoint[used2[arx][ary]]->getTexture(),true);
    sprite_plot.setTextureRect(   { xdraw, ydraw, xend, yend }  );
    sprite_plot.setPosition(0,0);
    texture_plot.clear(sf::Color(0,0,0,0));
    texture_plot.draw(sprite_plot);

//    printf("0,0: from %4d,%4d to %4d,%4d to position %4d,%4d\n",xdraw+arx*1920,ydraw+ary*1080,xend+xdraw+arx*1920,yend+ydraw+ary*1080,0,0);

    if ((xdraw+512+10)>1920) {
        if (used[(arx+1)%totalpicturex][ary%totalpicturey]==0)  ReadOneBitmap((arx+1)%totalpicturex,ary);
        sprite_plot.setTexture(texturemaxinmempoint[used2[(arx+1)%totalpicturex][ary]]->getTexture(),true);
        int end=(1920-xdraw);
        int extra=(xdraw+512+10)%1920;
        sprite_plot.setTextureRect(   { 0, ydraw, extra, 512 +10}  );
        sprite_plot.setPosition(end,0);
        texture_plot.draw(sprite_plot);
/*
        printf("1,0: from %4d,%4d to %4d,%4d to position %4d,%4d\n",
               ((arx+1)%totalpicturex)*1920,
               ydraw+ary*1080,
               ((arx+1)%totalpicturex)*1920+extra,
               512+10+ydraw+ary*1080,
               end ,
               0);
*/
    }

    if ((ydraw+512+10)>1080) {
        if (used[arx][(ary+1)%totalpicturey]==0)                  ReadOneBitmap(arx,(ary+1)%totalpicturey);
        sprite_plot.setTexture(texturemaxinmempoint[used2[arx][(ary+1)%totalpicturey]]->getTexture(),true);
        int end=(1080-ydraw);
        int extra=(ydraw+512+10)%1080;
        sprite_plot.setTextureRect(   { xdraw, 0, 512+10, extra }  );
        sprite_plot.setPosition(0,end);
        texture_plot.draw(sprite_plot);
/*
        printf("0,1: from %4d,%4d to %4d,%4d to position %4d,%4d\n",
               xdraw+arx*1920,
               0+((ary+1)%totalpicturey)*1080,
               512+10+xdraw+arx*1920,
               ((ary+1)%totalpicturey)*1080+extra,
               0,
               end) ;
*/
    }

    if ( ((ydraw+512+10)>1080) && ((xdraw+512+10)>1920) ) {
        if (used[(arx+1)%totalpicturex][(ary+1)%totalpicturey]==0)  ReadOneBitmap((arx+1)%totalpicturex,(ary+1)%totalpicturey);
        sprite_plot.setTexture(texturemaxinmempoint[used2[(arx+1)%totalpicturex][(ary+1)%totalpicturey]]->getTexture(),true);
        int endx=(1920-xdraw);
        int extrax=(xdraw+512+10)%1920;
        int endy=(1080-ydraw);
        int extray=(ydraw+512+10)%1080;
        sprite_plot.setTextureRect(   { 0, 0, extrax, extray }  );
        sprite_plot.setPosition(endx, endy);
        texture_plot.draw(sprite_plot);

/*
        printf("1,1: from %4d,%4d to %4d,%4d to position %4d,%4d\n",
               0 ,0,
               extrax+((arx+1)%totalpicturex)*1920,
               extray+((ary+1)%totalpicturey)*1080,
               endx+((arx+1)%totalpicturex)*1920,
               endy+((ary+1)%totalpicturey)*1080);
*/
    }

//    printf("\n");
    texture_plot.display();
    *image=texture_plot.getTexture().copyToImage();
    image_local=texture_plot.getTexture().copyToImage();

    for (int xy=0; xy<(512+10); xy++) {
        for (int xx=-2; xx<3; xx++) {
            for (int yy=-2; yy<3; yy++) {
                    dopix(xx        ,yy+xy          ,sf::Color(255,128,0,255),&image_local);
                    dopix(xx+511+10 ,yy+xy          ,sf::Color(255,128,0,255),&image_local);
                    dopix(xx+xy     ,yy             ,sf::Color(255,128,0,255),&image_local);
                    dopix(xx+xy     ,yy+511+10      ,sf::Color(255,128,0,255),&image_local);
                    dopix(xx+xy     ,yy+xy          ,sf::Color(255,128,0,255),&image_local);
                    dopix(xx+xy     ,yy+511+10-xy   ,sf::Color(255,128,0,255),&image_local);
            }
        }
    }

    texture_from_ffmpeg.create(512+10,512+10);
    texture_from_ffmpeg.update(image_local);
    texture_from_ffmpeg.setRepeated(FALSE);
    texture_from_ffmpeg.setSmooth(FALSE);
    sprite_from_ffmpeg.setTextureRect( {0,0,(int)texture_from_ffmpeg.getSize().x, (int)texture_from_ffmpeg.getSize().y } );
    sprite_from_ffmpeg.setTexture(texture_from_ffmpeg,false);
    sprite_from_ffmpeg.setScale(1.0,1.0);
    rotation_ffmpeg=0.0;
    rot_speed_ffmpeg=0.0;
    scale_now=1.0;
    ffmpeg_move=1;
    ffmpeg_posx=x;
    ffmpeg_posy=y;
    ffmpegfile=0;
    int bl_old=blending;
    blending=1;
    ffmpegfile=0;
    setffmpegfile();

    fposx=(int)(fposx);
    fposy=(int)(fposy);
    smooth_x=(float)((int)smooth_x);
    smooth_y=(float)((int)smooth_y);
    int smooth_old=smooth;
    smooth=0;
    texture_from_ffmpeg.setSmooth(FALSE);
    perform_quit=1;
//    plot_ffmpegfile=1;
//    plot_some();
    perform_quit=0;
    smooth=smooth_old;
    blending=bl_old;
}

void reset_all() {
//        load_maze(level);
//        blitter("Hoppa",1);
//        return;
int x=2000,y=2000;
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
//        blitter("Hoppa",1);
    return;
}
extern char mc_text0[100];
extern char mc_text1[100];
extern char mc_text2[100];
//extern int region_counter[1000][1000];
extern int plotting;

#include <../VOXEL.HPP>

extern std::vector<hit_one_region> vector_hit_regions;
extern hit_one_region* findRegion(int x, int z);

extern bool flushing_mode;

extern bool make_region_from_voxel(int x, int z);
std::vector<hit_one_region> ready_regions;
extern bool no_plotting;
extern bool hold_voxels;
extern bool rot_plot;

extern std::map<std::string, std::string> ready_regions_number_of_hits;
extern std::map<std::string, std::string>::iterator it_ready_regions_number_of_hits;

extern bool silence;
void update_MC(sf::Image& image_local2, int xx, int yy) {
    texture_from_ffmpeg.create(512,512);
    texture_from_ffmpeg.update(image_local2);

    sf::Image image_local;
    sf::Image image_local3;
    image_local=texture_from_ffmpeg.copyToImage();

    hit_one_region* hit_one=findRegion(xx, yy);


//    int x=xx*512;
//    int y=yy*512;
    int x=xx*512+1920/2;
    int y=yy*512+1080/2;
    static int smooth_mem=0;
    int smooth_old=smooth;


    bool complete=false;

    int pixel_count=0;
    int pixel_count2=0;
    char fname[1000];
    for (int y=0; y<512; y++)
        for (int x=0; x<512; x++) {
            sf::Color pixel = image_local.getPixel(x,y);
            if (pixel.a!=0) pixel_count++;
        }
    if (!hold_voxels || rot_plot) {
        sf::Image back;
        if ((plot_only && !flushing_mode) || rot_plot) {
            mkdir("../cut/png");
            sprintf(fname,"../cut/png/r.%d.%d.png",xx,yy);
//            texture_from_ffmpeg.copyToImage().saveToFile(fname);
        } else {
            sprintf(fname,"../cut/r.%d.%d.png",xx,yy);
        }
        if (file_exists(fname)) {
            back.loadFromFile(fname);
            if (back.getSize().x==512 && back.getSize().y==512) {
                pixel_count=0;
                for (int y=0; y<512; y++)
                    for (int x=0; x<512; x++) {
                        bool hit=false;
                        sf::Color pixel = image_local.getPixel(x,y);
                        sf::Color pixel_back = back.getPixel(x,y);

                        if (pixel.a!=0) {
                            hit=true;
                            back.setPixel(x,y,pixel);
                        } else {
                            image_local.setPixel(x,y,pixel_back);
                            if (pixel_back.a!=0) hit=true;
                        }
//                        if (pixel_back.a!=0 && hit==false) {
//                            image_local.setPixel(x,y,pixel);
//                            image_local.setPixel(x,y,pixel_back);
//                            hit=true;
//                        }
                        if (hit) pixel_count++;
                        if (hit) pixel_count2++;
                    }
                texture_from_ffmpeg.update(back);
            } else printf("\nError 512*512\n");
            if (silence==false)
                remove(fname);
        }
        if (silence==false)
            texture_from_ffmpeg.copyToImage().saveToFile(fname);
        image_local3=texture_from_ffmpeg.copyToImage();
    }
    if (pixel_count==512*512) complete=true;
    float complete_f2=100.0*float(pixel_count)/(512.0*512.0);

/*
    if (smooth!=smooth_mem && smooth==1) {
        smooth=0;
//    if (smooth==1) {
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
    } else smooth=0;
*/
    smooth_mem=smooth_old;
    smooth=0;
    bool not_ready=false;

    for (int xy=0; xy<511; xy++) {
        sf::Color pixel;

        pixel=image_local.getPixel(0,xy);
//        if (pixel.a!=0) {
            if (!plotting) { pixel.r=(pixel.r*2+255)/3; pixel.g=(pixel.g*2+255)/3; }
            else pixel.r=(pixel.r+255)/2;
            image_local.setPixel(0,xy,pixel);
//        }

        pixel=image_local.getPixel(511,xy+1);
//        if (pixel.a!=0) {
            if (!plotting) { pixel.r=(pixel.r*2+255)/3; pixel.g=(pixel.g*2+255)/3; }
            else pixel.r=(pixel.r+255)/2;
            image_local.setPixel(511,xy+1,pixel);
//        }

        pixel=image_local.getPixel(xy+1,0);
//        if (pixel.a!=0) {
            if (!plotting) { pixel.r=(pixel.r*2+255)/3; pixel.g=(pixel.g*2+255)/3; }
            else pixel.r=(pixel.r+255)/2;
            image_local.setPixel(xy+1,0,pixel);
//        }

        pixel=image_local.getPixel(xy,511);
//        if (pixel.a!=0) {
            if (!plotting) { pixel.r=(pixel.r*2+255)/3; pixel.g=(pixel.g*2+255)/3; }
            else pixel.r=(pixel.r+255)/2;
            image_local.setPixel(xy,511,pixel);
//        }
    }

    if (xx>=0)
        x=(int)( ( (LONG64)x + (LONG64)maxpixelsx*100 ) % (LONG64)maxpixelsx );
    else
        x=(int)( ( (LONG64)x +1 + (LONG64)maxpixelsx*100 ) % (LONG64)maxpixelsx );

    if (yy>=0)
        y=(int)( ( (LONG64)y + (LONG64)maxpixelsy*100 ) % (LONG64)maxpixelsy );
    else
        y=(int)( ( (LONG64)y +1 + (LONG64)maxpixelsy*100 ) % (LONG64)maxpixelsy );

//    printf("\nprint x,y = %d,%d\n",x,y);
    texture_from_ffmpeg.setSmooth(FALSE);

    texture_from_ffmpeg.update(image_local);

/*
    if (crossing==3 && mirror>0) {
        char pic_name[200];
        sprintf(pic_name,"../cut/%s.jpg",mc_text1);
        texture_from_ffmpeg.copyToImage().saveToFile(pic_name);
    }
*/

//extern void draw__on_texture(sf::RenderTexture& texture, char *towrite, int xpos, int ypos, sf::Color inner, sf::Color outer);

//    sprintf(mc_text,"r.%d.%d",int(x/512),int(y/512));

    texture_from_ffmpeg.setRepeated(FALSE);
    sprite_from_ffmpeg.setTextureRect( {0,0,(int)texture_from_ffmpeg.getSize().x, (int)texture_from_ffmpeg.getSize().y } );
    sprite_from_ffmpeg.setTexture(texture_from_ffmpeg,false);
    sprite_from_ffmpeg.setScale(1.0,1.0);
    rotation_ffmpeg=0.0;
    rot_speed_ffmpeg=0.0;
    scale_now=1.0;
    ffmpeg_move=1;
//hehehe
    ffmpeg_posx=x; //todo +6*512;
    ffmpeg_posy=y; //todo +6*512;
    int bl_old=blending;
    blending=0;
    ffmpegfile=0;
extern bool rot_plot;
//    if (!plotting || hold_voxels || flushing || rot_plot || plot_only)
//        { plot_back=0;plot_front=1; }
//    else
//         { plot_back=1;plot_front=0; }
    plot_back=0;plot_front=1;
    setffmpegfile();

    fposx=(int)(fposx);
    fposy=(int)(fposy);

    smooth_x=picturex*1920-posx;
    smooth_y=picturey*1080-posy;
    smooth_x=0;
    smooth_y=0;

    ReadBitmaps2();

    texture_from_ffmpeg.setSmooth(FALSE);
    perform_quit=1;

    plot_ffmpegfile=1;
    plot_some();

    blending=0;
    plot_back=0;plot_front=1;

    if (plotting) {
        if (plotting==2)
            text_to_ffmpeg(mc_text1, 28,sf::Color::Green,sf::Color::Black);
        else if (plotting==3)
            text_to_ffmpeg(mc_text1, 28,sf::Color(255,255,0,255),sf::Color::Black);
        else
            text_to_ffmpeg(mc_text1, 28,sf::Color::Blue,sf::Color::White);
    } else {
        text_to_ffmpeg(mc_text1, 28,sf::Color::Yellow,sf::Color::Black);
    }

    plot_ffmpegfile=1;
    plot_some();


    float complete_f=100.0*float(pixel_count)/(512.0*512.0);
    if (!(flushing_mode && complete_f>99.95 && !no_plotting) && plotting) {
        if (!plot_only) {
            int offset=0;
            std::string s;
            char s_c[100];
            sprintf(s_c,"%d,%d",xx,yy);
            s=s_c;

            random_pixel=sf::Color(24+rand()%80,24+rand()%80,24+rand()%80,255);

            it_ready_regions_number_of_hits=ready_regions_number_of_hits.find(s);
            if (it_ready_regions_number_of_hits != ready_regions_number_of_hits.end()) {
                it_ready_regions_number_of_hits++;
                while (it_ready_regions_number_of_hits != ready_regions_number_of_hits.end() && it_ready_regions_number_of_hits->second!=std::string()+"") {
                    sprintf(mc_text2,"%s",it_ready_regions_number_of_hits->second.c_str());
                    text_to_ffmpeg(mc_text2, 28,random_pixel,sf::Color::White);
                    ffmpeg_posy=y+2+42+28*(offset++);
                    plot_ffmpegfile=1;
                    plot_some();
                    it_ready_regions_number_of_hits++;
                }
            }

    //        it_ready_regions_number_of_hits=ready_regions_number_of_hits.find(s);
    //        if (it_ready_regions_number_of_hits != ready_regions_number_of_hits.end()) {
    //            offset=it_ready_regions_number_of_hits->second.y;
    //            ffmpeg_posy=y+2+42+28*(offset); //todo +6*512;
    //        }

    //        text_to_ffmpeg(mc_text2, 28,random_pixel,sf::Color::White);
    //        if (hit_one!=NULL) {
    //              ffmpeg_posy=y+2+42+28*(offset); //todo +6*512;
    ////            ffmpeg_posy=y+2+42+28*(hit_one->index12); //todo +6*512;
    ////            if (hit_one->index12>4) printf("Error: hit_one->index12>4\n");
    //          }
    //          else
    //              ffmpeg_posy=y+2+42+28; // todo +6*512;


    //        plot_ffmpegfile=1;
    //        plot_some();

            char mc_text3[100];
            sprintf(mc_text3,"%8.3f%%",100.0*float(pixel_count)/(512.0*512.0));
            ffmpeg_posy=y+2+340+28*(hit_one->index12); //todo +6*512;
            ffmpeg_posx=x+200; //todo +6*512;
            text_to_ffmpeg(mc_text3, 28,sf::Color::Red,sf::Color::White);
            plot_ffmpegfile=1;
            plot_some();
        }
    }

//    perform_quit=0;

    smooth=smooth_old;
    blending=bl_old;
    ffmpegfile=1;
//    float complete_f=100.0*float(pixel_count)/(512.0*512.0);
    image_local.create(512,512,sf::Color(0,0,0,0));
    if (flushing_mode && complete_f>99.8 && !no_plotting && silence==false) {
//    if (flushing_mode && complete_f>99.99 && !no_plotting && !complete_f2>99.99) {
        printf("\n\nGOT ONE COMPLETE (%f%% pixels) : r.%d.%d PUSHED ==>>\n",complete_f,xx,yy);
        mkdir("../cut/png2");
        sprintf(fname,"../cut/png2/r.%d.%d.png",xx,yy);
        image_local3.saveToFile(fname);

//        hit_one_region one_region;
//        one_region.x=xx; one_region.z=zz;
        ready_regions.push_back(hit_one_region(xx,yy));
    } else if (complete && flushing_mode) printf("\nGOT ONE COMPLETE (100%% pixels) : r.%d.%d ==>>\n",xx,yy);
    if (complete_f!=100.0) {
        char hoppa[200];
        sprintf(hoppa,"echo r.%d,%d %f%% complete >> not_complete.txt",xx,yy,complete_f);
        system(hoppa);
    }
//    else if (flushing_mode) printf("\nPIXELS=%d = %f%% ==>> \n",pixel_count,complete_f);

    // else printf("\nPIXELS=%d = %f%% ==>> \n",pixel_count,100.0*float(pixel_count)/(512.0*512.0));
//    perform_quit=0;
}



