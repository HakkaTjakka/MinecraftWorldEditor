#ifndef EVERYTHING_HPP_INCLUDED
#define EVERYTHING_HPP_INCLUDED
#define SFML_STATIC
#undef UNICODE
#define PI 3.141592653589793
#include <wchar.h>
#include <winsock2.h>
#include <io.h>
#include "WinMain.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/stat.h>
#include <iostream>
#include <cstdlib>
#define WINVER 0x0500
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
#include <string>
#include <sstream>
#include <list>
#include <chaiscript/chaiscript.hpp>
#include "colorcodes.hpp"

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

#define EVENT_ALT 1
#define EVENT_SHIFT 2
#define EVENT_CONTROL 4
#define EVENT_SYSTEM 8

struct handler_struct
{
    int blending;
    int plot_front;
    int show;
    int tile;
    int shader;
};
extern float fpstime;
extern START_LOADING_FOR_ALL_BITMAPS();
extern FILE* file_from_file;
extern HINSTANCE hInstance2;
extern HWND TextBox, SendButton, TextField;
extern HWND hWndMain2;
extern StreamSelector *live_selector2;
extern StreamSelector *live_selector;
extern VOID HANDLEKEY(WPARAM wparam, sf::Event event);
extern bool file_exists(const char * filename);
extern bool file_exists2(const char * filename);
extern char **MUL_SAS_EXTENSION;
extern char **MUL_SAS_ORDER;
extern char **MUL_SAS_URL;
extern char **files;
extern char **files_mazes;
extern char **used;
extern char *com[];
extern char *line;
extern char LEVELDIR[];
extern char MAPDIR[];
extern char MOVIEDIR[];
extern char PICTUREDIR[];
extern char SAS_URL[];
extern char URLDIR[];
extern char connectedip[];
extern char error_msg2[];
extern char error_msg3[];
extern char error_msg4[];
extern char error_msg5[];
extern char error_msg[];
extern char going_to[2000];
extern char internet_naam[];
extern char movie_name[];
extern char naam_from_file[];
extern char writer[];
extern combine_front_to_back();
extern double Fget_map_x,Fget_map_y;
extern double ddp_loop;
extern double hold;
extern double loadvalue_float(char *filenaam);
extern double rel_pos_in_map_x1;
extern double rel_pos_in_map_x2;
extern double rel_pos_in_map_x;
extern double rel_pos_in_map_y1;
extern double rel_pos_in_map_y2;
extern double rel_pos_in_map_y;
extern double render_rel_pos_in_map_x;
extern double render_rel_pos_in_map_y;
extern double scale_jump;
extern double scale_slow;
extern double smooth_x;
extern double smooth_y;
extern double speed_slowx;
extern double speed_slowy;
extern double xdiff1;
extern double xdiff2;
extern double ydiff1;
extern double ydiff2;
extern float 	*fpos_ghostx;
extern float 	*fpos_ghosty;
extern float 	*fspeed_ghostx;
extern float 	*fspeed_ghosty;
extern float fbest_distance;
extern float fposx;
extern float fposy;
extern float fpstime;
extern float fpstime_factor;
extern float fspeed_ghost_all;
extern float fspeedx;
extern float fspeedx_new;
extern float fspeedy;
extern float fspeedy_new;
extern float mem_fposx;
extern float mem_fposy;
extern float new_fposx;
extern float new_fposy;
extern float old_scale;
extern float plot_all_fovyInDegrees;
extern float plot_all_rotate_x;
extern float plot_all_rotate_y;
extern float plot_all_rotate_z;
extern float plot_all_translate_x;
extern float plot_all_translate_y;
extern float plot_all_translate_z;
extern float plot_all_zfar;
extern float plot_all_znear;
extern float rot_speed_canvas;
extern float rot_speed_ffmpeg;
extern float rot_speed_internet;
extern float rot_speed_movie2;
extern float rot_speed_movie;
extern float rotation_canvas;
extern float rotation_ffmpeg;
extern float rotation_internet;
extern float rotation_movie2;
extern float rotation_movie;
extern float scale_now;
extern float set_time;
extern int 	*check;
extern int 	*pos_ghostx;
extern int 	*pos_ghosty;
extern int  SAVEALL;
extern int BITMAPSX;
extern int BITMAPSY;
extern int DONTSAVEFILES;
extern int DO_ADAPT;
extern int DO_ZOOM_IN;
extern int DO_ZOOM_OUT;
extern int ESCAPE;
extern int F1;
extern int F1;
extern int F2;
extern int F4;
extern int GETBLENDINGPICTURE(char* naam);
extern int GETPICTURE(char* naam);
extern int GetFileFromInternet(char * naam);
extern int GetGoogleMap(char * url,sf::Texture * result);
extern int LOADED_SEED;
extern int MAXINMEM;
extern int MAZEOFF;
extern int MUL_COUNTER;
extern int MUL_COUNTER;
extern int MUL_SAS_MAX_ZOOM[];
extern int MUL_SAS_ZOOM_DIRECTION[];
extern int MyBlendMode_num;
extern int MyBlend_alphaDstFactor_num;
extern int MyBlend_alphaEquation_num;
extern int MyBlend_alphaSrcFactor_num;
extern int MyBlend_colorDstFactor_num;
extern int MyBlend_colorEquation_num;
extern int MyBlend_colorSrcFactor_num;
extern int MyBlending;
extern int PIXELISBLACKTHRESHOLD;
extern int PIXELISCOLORTHRESHOLD;
extern int PIXELISCOLOR_B;
extern int PIXELISCOLOR_G;
extern int PIXELISCOLOR_R;
extern int PIXELISWHITETHRESHOLD;
extern int PRELOAD;
extern int SAS_MAX_ZOOM;
extern int SAS_STARTX;
extern int SAS_STARTX_a;
extern int SAS_STARTY;
extern int SAS_STARTY_a;
extern int SAS_ZOOM;
extern int SAS_ZOOM_DIRECTION;
extern int SEED;
extern int again1;
extern int again2;
extern int autodraw;
extern int best_ghost_num;
extern int big_large;
extern int blank_maze;
extern int blend_on_movie;
extern int blending;
extern int buffer_shader;
extern int check_dir(int BITMAPSX,int BITMAPSY,int level);
extern int check_mem;
extern int client;
extern int combine;
extern int connected;
extern int cool;
extern int crop;
extern int crop_x;
extern int crop_x_size;
extern int crossing;
extern int difficulty;
extern int disp_text;
extern int dont_stop;
extern int doscript(int argc, char *argv[]);
extern int draw_model;
extern int drawmazes;
extern int eatmode;
extern int end_on_record;
extern int err_level;
extern int error_flag2;
extern int error_flag3;
extern int error_flag4;
extern int error_flag5;
extern int error_flag;
extern int error_flag;
extern int exiting;
extern int f8_repeat;
extern int ffmpeg_move;
extern int ffmpeg_posx,ffmpeg_posy;
extern int ffmpegfile;
extern int file_is_open_line_from_file;
extern int flippo;
extern int flop;
extern int follow_ghost;
extern int follow_ghost_num;
extern int follow_ghost_start;
extern int force_game;
extern int force_loading;
extern int forced_jump;
extern int formula;
extern int fragment_shader;
extern int generate_tiles;
extern int get_map_x,get_map_y,get_map_zoom;
extern int ghost;
extern int go_go;
extern int goexit;
extern int hold_level;
extern int hunt;
extern int hunt_counter;
extern int hunt_max;
extern int internet_move;
extern int internet_posx,internet_posy;
extern int internetfile;
extern int kill1,kill2,kill3;
extern int kleur_back;
extern int kleur_front;
extern int level;
extern int levelnotsaved;
extern int live_movie2_is_mp3;
extern int live_movie_is_mp3;
extern int load_buffer_filename();
extern int load_fragment_filename(int up_down);
extern int load_vertex_filename();
extern int loadallmaps;
extern int loadallmaps_level;
extern int loadbackground;
extern int loaded;
extern int loaded_from_maze;
extern int loader1_active;
extern int loader2_active;
extern int loader3_active;
extern int loadmap;
extern int long_jump;
extern int lookahead;
extern int max_line_from_file;
extern int maxnumber;
extern int maxpicturex;
extern int maxpicturey;
extern int maxpixelsx;
extern int maxpixelsx;
extern int maxpixelsy;
extern int maxpixelsy;
extern int maze_down;
extern int maze_down_new;
extern int maze_left;
extern int maze_left_new;
extern int maze_right;
extern int maze_right_new;
extern int maze_up;
extern int maze_up_new;
extern int mazetype;
extern int mem_picturex;
extern int mem_picturey;
extern int mem_posx;
extern int mem_posy;
extern int mirror;
extern int monitor_loop;
extern int mouse_move;
extern int movie2;
extern int movie2_move;
extern int movie2_posx,movie2_posy;
extern int movie;
extern int movie_move;
extern int movie_posx,movie_posy;
extern int movieextern;
extern int mul;
extern int new_picturex;
extern int new_picturey;
extern int new_posx;
extern int new_posy;
extern int newmaze;
extern int next;
extern int next_textfile;
extern int num_ghost;
extern int number;
extern int offset_picture_x;
extern int offset_picture_y;
extern int old_draw;
extern int old_pen;
extern int old_pen_mode;
extern int old_shift;
extern int one_pixel;
extern int overwrite1;
extern int overwrite2;
extern int pacman;
extern int pacman;
extern int pen;
extern int pen_mode;
extern int perform_quit;
extern int pictures_to_ffmpegfile();
extern int picturex;
extern int picturex_mem;
extern int picturey;
extern int picturey_mem;
extern int play_rate;
extern int playerleft;
extern int playing_start(char * filename);
extern int playmovie(char* naam);
extern int playmovie(char* naam);
extern int playmusic;
extern int playsound;
extern int plot_all;
extern int plot_ffmpegfile;
extern int plot_front,plot_back;
extern int plot_internetfile;
extern int plot_moviefile2;
extern int plot_moviefile;
extern int plot_shader;
extern int position1x;
extern int position1y;
extern int position2x;
extern int position2y;
extern int posx;
extern int posx_mem;
extern int posy;
extern int posy_mem;
extern int pressed;
extern int rate_count;
extern int read_mazeoff(int nopos);
extern int real_posx2;
extern int real_posy2;
extern int reconnectTcpClient(char * ipaddress, unsigned short port);
extern int reconnectTcpServer(unsigned short port);
extern int reconnectUdpClient(char * ipaddress, unsigned short port);
extern int reconnectUdpServer(unsigned short port);
extern int record_pause;
extern int record_screen;
extern int record_screen_num;
extern int recording_start(int x, int y);
extern int recording_start_m_orig();
extern int recording_type;
extern int reload;
extern int reload_init();
extern int render_picturex;
extern int render_picturex;
extern int render_picturex_mem;
extern int render_picturey;
extern int render_picturey;
extern int render_picturey_mem;
extern int render_posx;
extern int render_posx;
extern int render_posx_mem;
extern int render_posy;
extern int render_posy;
extern int render_posy_mem;
extern int replace_str(char *str, char *orig, char *rep);
extern int reset_map;
extern int reset_normal;
extern int rotate_canvas;
extern int rotate_ffmpeg;
extern int rotate_internet;
extern int rotate_movie2;
extern int rotate_movie;
extern int runTcpClient(char * ipaddress, unsigned short port);
extern int runTcpServer(unsigned short port);
extern int runUdpClient(char * ipaddress, unsigned short port);
extern int runUdpServer(unsigned short port);
extern int scripting();
extern int select_line_from_file(char *filename, char * path, int next);
extern int select_line_from_file_w(char * line_of_text, char * path);
extern int select_location(char *filename, char * path);
extern int select_nextline(char *filename, char * path);
extern int select_textfile(char *filename, char * path);
extern int selector;
extern int selector_item;
extern int server;
extern int set_transparant;
extern int shade_main;
extern int shade_map;
extern int shaders();
extern int shift;
extern int show_shade_map;
extern int size_canvas;
extern int size_ffmpeg;
extern int size_internet;
extern int size_movie2;
extern int size_movie;
extern int skipclear;
extern int smooth;
extern int soft_jump;
extern int sound_counter;
extern int speedx;
extern int speedx_new;
extern int speedy;
extern int speedy_new;
extern int start_posx;
extern int start_posx;
extern int start_posx_mem;
extern int start_posy;
extern int start_posy;
extern int start_posy_mem;
extern int start_textfile;
extern int startmovie(char* naam);
extern int startmovie2(char* naam);
extern int sync;
extern int tcp;
extern int thread_run_sub;
extern int timer_movie2;
extern int timer_movie;
extern int toggle_point;
extern int toggle_point;
extern int total_textfile;
extern int totalchanged;
extern int totalfiles;
extern int totalfiles_mazes;
extern int totalpicturex;
extern int totalpicturey;
extern int totalused;
extern int tune;
extern int udp;
extern int update_buffer_shader(int up_down);
extern int update_shader();
extern int var_font;
extern int vertex_shader;
extern int yellow;
extern int zoom_off;
extern select_movie(char *filename, char * path);
extern sf::BlendMode MyBlendMode[];
extern sf::BlendMode MyBlendingMode;
extern sf::BlendMode MyBlendingMode_movie;
extern sf::Color background_color[];
extern sf::Event event;
extern sf::Image Inter;
extern sf::Mutex loader_mutex;
extern sf::Mutex mutje;
extern sf::RenderStates picture_states;
extern sf::RenderTexture texture_from_buffer2;
extern sf::RenderTexture texture_from_buffer;
extern sf::RenderTexture texturemaxinmem[];
extern sf::RenderWindow SFMLView1;
extern sf::SoundBufferRecorder recorder;
extern sf::Sprite sprite_from_canvas;
extern sf::Sprite sprite_from_ffmpeg;
extern sf::Sprite sprite_from_internet;
extern sf::Sprite sprite_from_movie2;
extern sf::Sprite sprite_from_movie;
extern sf::Text mytext2;
extern sf::Text mytext;
extern sf::Texture sfml_mazedot2;
extern sf::Texture sfml_mazedot;
extern sf::Texture texture_from_ffmpeg;
extern sf::Texture texture_from_ffmpeg;
extern sf::Texture texture_from_internet;
extern sf::Texture texture_from_internet;
extern sf::Texture texture_from_movie2_new;
extern sf::Texture texture_from_movie2_new;
extern sf::Texture texture_from_movie_new;
extern sf::Texture texture_from_movie_new;
extern sf::Time time_movie2;
extern sf::Time time_movie;
extern sf::Vector2i mytotal1;
extern sf::Vector2i mytotal2;
extern sf::Vector2i mytotal3;
extern sf::Vector2i position;
extern sfe::Movie *live_movie2;
extern sfe::Movie *live_movie2;
extern sfe::Movie* live_movie;
extern sfe::Movie* live_movie;
extern std::string hoppa;
extern struct handler_struct handler[];
extern struct stat buffer;
extern unsigned short portnumber;
extern void CLEANBITMAPS();
extern void CreateAll();
extern void DRAWALLMAZES();
extern void DoAnimate2(HINSTANCE,HWND);
extern void EXITPROGRAM();
extern void HALT();
extern void LOADALLBITMAPS();
extern void LOADALLBITMAPS_MAZES();
extern void ReadBitmaps2();
extern void ReadBitmaps4();
extern void ReadOneBitmap(int picturex,int picturey);
extern void SAVEALLBITMAPS();
extern void SEND(char *towrite);
extern void SENDGOTOPOS();
extern void Screenget3();
extern void Screenshot();
extern void ShowTaskBar(bool show);
extern void adapt_speed();
extern void add_border(sf::Texture * MyTexture);
extern void batch_pictures();
extern void batch_pictures2();
extern void blitter(char * line, int mode);
extern void cleanupbitmaps();
extern void cleanupbitmaps_mazes();
extern void cleanupbitmaps_mazes();
extern void clear_map();
extern void convert_to_scale(sf::Texture * MyTexture,sf::Sprite * MySprite);
extern void draw2(char *towrite, int xpos, int ypos, sf::Color inner, sf::Color outer);
extern void ffmpegfile_to_maze();
extern void ffmpegfile_to_maze2();
extern void follow_ghost_pos();
extern void font_to_ffmpeg();
extern void frexit(int err_no);
extern void gen_all_mipmaps();
extern void get_ffmpegfile();
extern void get_position1();
extern void get_position2();
extern void ghost_next();
extern void go_save_some_bitmaps();
extern void goto_ghost();
extern void goto_partner();
extern void home_map();
extern void insert_event(sf::Keyboard::Key code,int MODE);
extern void insert_key(WPARAM key);
extern void kiki();
extern void launch_background_loader_one();
extern void launch_background_loader_three();
extern void launch_background_loader_two();
extern void load_map();
extern void load_map_last();
extern void load_maze(int lastmap);
extern void make_black_transparant(sf::Texture * MyTexture);
extern void make_color_transparant(sf::Texture * MyTexture);
extern void make_dark_transparant(sf::Texture * MyTexture);
extern void make_text(int next_font);
extern void make_white_transparant(sf::Texture * MyTexture);
extern void merge_back_to_front();
extern void movie_to_ffmpeg(sf::Texture * MyTexture_movie, sf::Texture * MyTexture_ffmpeg);
extern void next_loc();
extern void pacman_to_rel_pos();
extern void playing(sf::Image * image);
extern void playing_end();
extern void plot_some();
extern void plotplot();
extern void putinmazeSFML_all();
extern void putinmazeSFML_all_xtheny();
extern void recording_end();
extern void recording_m_orig();
extern void rel_pos_to_pacman();
extern void reverse_maze();
extern void rot_texture_90(sf::Texture * MyTexture);
extern void rot_texture_as_is(sf::Texture * MyTexture, sf::Sprite * MySpriteIn);
extern void save_map();
extern void save_map_last();
extern void save_maze(int lastmap);
extern void save_maze(int lastmap);
extern void save_mazeoff();
extern void savedata(char *naam, int data);
extern void savevalue_float(char *filenaam, double value);
extern void set_blending();
extern void set_mapper();
extern void set_mytext(int next_font);
extern void set_pacman();
extern void set_position1();
extern void set_position2();
extern void setcanvasfile();
extern void setffmpegfile();
extern void setinternetfile();
extern void setmoviefile();
extern void setmoviefile2();
extern void soften_edge(sf::Texture * MyTexture);
extern void stopmovie();
extern void stopmovie2();
extern void text_to_ffmpeg(char * in,int font_size, sf::Color inner, sf::Color outer);
extern void text_to_ffmpeg_w(char * in,int font_size, sf::Color inner, sf::Color outer, sf::Uint32 type);
extern void updatemovie();
extern void updatemovie2();
extern wchar_t line_w[];
extern void insert_event(sf::Keyboard::Key code,int MODE);
extern void insert_key(WPARAM key);
extern void HANDLECHAR(WPARAM wparam);
extern void HANDLEKEY(WPARAM wparam, sf::Event event);
extern int select_from_list(char *filename, char * path, int next);
extern int select_from_list2(char *filename, char * path, int next);
extern int select_geodat(char *filename, char * path);
extern void adapt_speed();
extern int mazesizex;
extern int mazesizey;
extern void zetom();
extern void reversed_zetom();
extern int maze_plotsizex;
extern int maze_plotsizey;
extern char **Maze;
extern char **maze_plot;
extern void read_keylist_hpp();
extern sf::Font myfont2;
extern void textfiles_to_screen(int font_size, sf::Color paint);
extern void do_command(int what);
extern void parse_command(char * text);
extern int doscript(int argc, char *argv[]);
extern void command_par(int what, ...);
extern int scripting();
//extern int scripting_file(char * filename);
extern int scripting_file(std::vector<char*> v,int num_par);
extern void run_chai(char * execute_string);
extern int select_macro(char *filename, char * path);
extern char SUBTITLES[];
extern char SUBTITLE_FORMAT[];

extern int monitor_off;
extern int burn_subs;
extern char quote_subs[];
extern char quote_video[];
extern char quote_audio[];
extern char quote_subs_extra[];
struct container_struct
{
    char extension[10]="";
    int isvideo=0;
    int isaudio=0;
};
extern void get_container(struct container_struct * container, int num);
extern struct container_struct container_video;
extern struct container_struct container_audio;
extern int replace_str(char *str, char *orig, char *rep);
extern int ESCAPE_PRESSED;
extern int get_video_thread_running;
extern int burn_next_sub_ready;
extern char FFMPEGCOMMAND_BURN_SUBS[];
extern int go_download;
extern int go_burn;
extern void start_get_videos_thread();
extern int start_burning;
extern void burn_next_sub();
extern void print_to_screen(int var_font, char * text_to_print, int font_size, sf::Color paint_in, sf::Color paint_out, sf::Color paint_back, float outline, sf::Uint32 text_type );
extern char * get_info_video(char * filename);
extern char * get_info_audio(char * filename);
extern char raw_name[];
extern char raw_name2[];
extern char lang_nq[];
extern void text_to_ffmpeg_w2(int var_font, char * in,int font_size, sf::Color inner, sf::Color outer, sf::Color background, float outline, sf::Uint32 text_type);
extern sf::RenderTexture font_texture;
extern sf::RenderTexture print_font_texture;
extern sf::Mutex animate_lock;
extern int something_to_do;
extern void start_burn_next_sub_thread();
extern int go_list;
extern int sub_load_maze;
extern void disp_open();
extern void disp_close();
extern sf::Font print_font;
extern sf::Text print_text;
extern void set_print_text();
extern void set_mono(int on_off);
extern char FONTDIR[];


#endif // EVERYTHING_HPP_INCLUDED
