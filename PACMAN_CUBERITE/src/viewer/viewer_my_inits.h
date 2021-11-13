#include <conio.h>
#include "../MCA-NBT-EDIT.HPP"
#include <winsock2.h>

#include <chrono>

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <map>
#include <string>
#include <vector>
#include <Windows.h>
#include <float.h>

#include <GL/glew.h>
#include <GL/freeglut.h>
//#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
//#include <SFML/Graphics/Image.hpp>
//#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/System.hpp>
//#include <SFML/Network.hpp>
#include <SFML/System/Mutex.hpp>
//#include <SFML/Network/IpAddress.hpp>
//#include <SFML/WindowHandle.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/glm.hpp>
#include <glm/common.hpp>
#include <glm/gtx/rotate_vector.hpp>

//#include <std::vector>
#include <opencv2/core/core.hpp>
#include <iostream>
#include <stdio.h>

#ifndef GL_SRGB8_ALPHA8
#define GL_SRGB8_ALPHA8 0x8C43
#endif

#define F_STARTER 1


#include <cstdint>
#include "Terrain.h"
#include "Log.h"
#include "TextureManager.h"
#include "Camera.h"
#include "Controller.h"
#include "Airplane.h"
#include "Utility.h"
#include "Sky.h"
#include "ShadowMap.h"
#include "CameraController.h"
#include "ParticleSystem.h"
#include "Sprite.h"
#include "Debug/Box.h"

#include "Airplane.h"
//#include <glm/gtx/transform.hpp>
//#include <glm/gtx/euler_angles.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>"
//#include <cmath>
#include <algorithm>
extern void toggle2();


using namespace fly;

struct Angles {
    float yaw;
    float pitch;
    float roll;
};

bool plane_ready=false;

void columnMatrixToAngles( Angles& angles, float colMatrix[4][4] );

glm::mat4 *fly_projection_matrix_pointer;
Terrain *fly_terrain_pointer;
Airplane *fly_aircraft_pointer;
ShadowMap *fly_shadowMap_pointer;
Sky *fly_sky_pointer;
ParticleSystem *fly_particles_pointer;
Camera *fly_camera_pointer;
CameraController *fly_mouse_camera_pointer;
bool fly_paused_pointer;
bool fly_focus_pointer;
float *fly_frame_period_seconds_pointer;
Controller *fly_controller_pointer;
glm::mat4 *fly_view_pointer;

glm::vec3 fly_camera_position;
glm::vec3 fly_plane_position;
glm::vec3 fly_plane_position_start;

sf::Vector2i sending_new_mouse=sf::Vector2i(0,0);
sf::Shader depth_shader;


//void interpolate(int what);
bool fly_visible=true;
bool check_fly=false;

bool fly_is_visible=true;
extern int level;
extern int combine;
extern int next;
void stop_view();
void get_view(float &rotate_object_x, float &rotate_object_y, float &rotate_object_z, float curr_quat2[4],float eye2[3],float lookat2[3],float translation[3],float perspective[4],float bmin[3], float bmax[3], int& frustum_toggle);
void start_view(FILE* file, char* filename);
bool splines_loaded=false;
void interpolate_spline(int what);
extern void makeFrustum(double fovY, double aspectRatio, double front, double back,int frustum_toggle, float eye2[3]);
void trackball_xyz(float q[4], float p1x, float p1y, float p1z);
void add_quats1(float q1[4], float q2[4], float dest[4]);
extern ATOM RegClass(char *ClassName,HINSTANCE hInstance);
extern HWND CreateWin(HINSTANCE hInstance, char *ClassName,int Width, int Height);
extern HINSTANCE hInstance2;
extern HWND hWndMain2;
extern char* reg;
extern bool glew_initor;
bool crashed = false;
bool recover_crash = false;
std::vector<glm::ivec2> to_load_extra;
bool load_extra=false;
bool on_hold=true;

int doesnt_work=1;
sf::Mutex wait_locker;
int flip=2;
sf::RenderTexture render_texture;
sf::RenderTexture render_texture1;
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
//const Options Fly_DefaultOptions {0.f, 1920/2, 1080/2, false, false, false, false, false};
//extern const Options DefaultOptions {0.f, 1920, 1080, false, false, false, false, false};
extern void printHelp();

//extern const Options DefaultOptions;
sf::Mutex wierdo_mutex;
sf::Mutex interface_mutex;
sf::Mutex delta_mutex;
sf::Mutex delta2_mutex;

sf::Texture interface_texture;
sf::Sprite interface_sprite;
sf::Texture interface_texture1;
sf::Sprite interface_sprite1;


#define NUMBER_OF_SIMULTANIOUS_ACTIVE_THREADS 50

void build_rotmatrix_glm(glm::mat4& m, const float q[4]);
int ready_to_render[10]={0,0,0,0,0,0,0,0,0,0};
int frustum_count_x=0;
int frustum_count_y=0;
bool remember_911=false;
sf::Texture* backgroundTexture[10]={NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};
sf::Sprite* backgroundSprite[10]={NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};
//jojo
bool sRgb = true;
sf::Font *font_window=NULL;
sf::Font *font_text=NULL;
sf::Text *text_window=NULL;
char hoppa[2000];
sf::Text *sRgbInstructions=NULL;
sf::Text *text_text=NULL;
sf::Text *mipmapInstructions=NULL;

extern glm::mat4 rotationMatrix_aircraft;
extern glm::vec3 aircraft_position;
extern glm::vec3 camera_position;
extern glm::vec3 camera_direction;
FILE *marker[10];
char marker_filename[1000];
FILE* marker_file=NULL;

int frustum_size_x=1;
int frustum_size_y=1;

sf::RectangleShape rectangle;

sf::Clock clock_911;
bool remember_911_set_off=false;
extern int crossing;

extern HDC hdc_sfmlview1;
extern HGLRC hglrc_sfmlview1;
extern HWND hWndMain;
bool set_end_of_movement=false;
int screen_width=0;
int screen_height=0;

sf::WindowHandle window_handle;

sf::GlContext* m_context_window;
sf::GlContext* m_context_sfmlview1;

extern void ShowTaskBar(bool show);

HGLRC    hglrc[10];
HDC      hdc[10] ;
HWND     hwnd[10];


bool videomode[10]={0,1,1,1,1,1,1,1,1,1};
bool visible[10]={1,1,1,1,1,1,1,1,1,1};
bool interpolate_on=false;

#ifdef __APPLE__
#include <OpenGL/glu.h>
#else
#include <GL/glu.h>
#endif

#include <GLFW/glfw3.h>

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

#include "trackball.h"
#include "stb_image2.h"

#define STB_IMAGE_IMPLEMENTATION

bool COLOR_ARRAY=false;
bool TEXTURE_ARRAY=true;
bool WIRE_FRAME=false;
sf::Mutex thread_loader;
extern bool window_closed;

typedef struct
{
    GLuint vb_id;  // vertex buffer id
    int numTriangles;
//    int material_id;
    size_t material_id;
} DrawObject;

typedef struct
{
    int8_t* buffer;
    size_t length;
} BufferObject;

struct Pacman_Object
{
    float bmin[3], bmax[3];
    std::vector<DrawObject> gDrawObjects;
    std::vector<tinyobj::material_t> materials;
    std::map<std::string, GLuint> textures;
    int map_x=0;
    int map_y=0;
    int arr_index=0;
    int show=1;
    double south=0.0;
    double north=0.0;
    double east=0.0;
    double west=0.0;
    std::string filename="";
};

std::vector<Pacman_Object> Pacman_Objects[10];

int sync_window[10]={1,1,1,1,1,1,1,1,1,1};
bool FileExists(const std::string& abs_filename);
int batch_load=0;

void quick_toggle() {
    static int toggle=0;
    if (toggle++==4) toggle=0;
    if (toggle==0) printf("/\b");
    else if (toggle==1) printf("-\b");
    else if (toggle==2) printf("\\\b");
    else if (toggle==3) printf("|\b");
}

#define PI 3.141592653589793
extern float plot_all_translate_x;
extern float plot_all_translate_y;
extern float plot_all_translate_z;
extern float plot_all_rotate_x;
extern float plot_all_rotate_y;
extern float plot_all_rotate_z;
void handle_key_window(sf::Event event, int win_num, sf::RenderWindow& window);
int record_window=0;
void do_the_recording_stuff_window(sf::RenderWindow& window, int win_num);
int first_hoppa=1;

#include "Airplane.h"


extern glm::vec3 aircraft_position;

void draw2_all(sf::RenderWindow& window,char *towrite, int xpos, int ypos, sf::Color inner, sf::Color outer, int text_size);
void reset_text(int win_num);

sf::Mutex text_mutex;
bool running_3d[10]={false,false,false,false,false,false,false,false,false,false};

glm::mat4 my_rotate(float rotate_object_x, float rotate_object_y, float rotate_object_z);
glm::mat4 my_rotate2(float rotate_object_x, float rotate_object_y, float rotate_object_z);
glm::mat4 my_rotate_zyx(float rotate_object_z, float rotate_object_y, float rotate_object_x);

extern int main_fly2(sf::Window& window, sf::Event& event,int& event_system,int& width2, int &height2,int what);
extern int main_fly3();
extern bool win_fly_setvisible;

extern int rate_count;
extern int play_rate;
extern float fpstime;
extern float fpstime_factor;
extern int record_screen_num;
extern int record_pause;
extern int recording_type;
extern int record_pause;
extern int record_screen;
extern void Screenshot3_window(sf::RenderWindow& window);
extern int flop;
extern int rate;

extern int blocked_by_window;

extern int select_from_list2(char* filename, char* path, int next);
extern int replace_str(char* str, char* orig, char* rep);

extern char EARTH_ROOT1[];
extern char EARTH_ROOT2[];
extern char EARTH_ROOT3[];
extern char MODELS[];
std::string latitude_longditude;
std::string return_root="";
int extra_octants=0;
extern std::string area;
extern std::string get_octant_Amsterdam(int &x, int &y);
extern std::string get_octant_ENSCHEDE(int &x, int &y);
extern std::string get_octant_LA(int &x, int &y);

extern int smooth;
int global_octant_x,global_octant_y;

std::string GetBaseDir(const std::string& filepath)
{
    if (filepath.find_last_of("/\\") != std::string::npos)
        return filepath.substr(0, filepath.find_last_of("/\\"));
    return "";
}

std::string GetFileName(const std::string& filepath)
{
    if (filepath.find_last_of("/\\") != std::string::npos)
        return filepath.substr(1+filepath.find_last_of("/\\"),filepath.length());
    return "";
}



sf::Mutex diff_draw;
int different_draw=0;
sf::Mutex locker;
sf::Mutex render_locker;
sf::Mutex render_locker2;
sf::Mutex context_locker;

std::vector<glm::ivec4> frustum_object;
void erase_one_pacman_objects(int map_x,int map_y,int win_num ,bool pac_obj2_arr_used[100],Pacman_Object pac_obj2_arr[100]);
bool load_3d_objects(int frustum_count_x,int frustum_count_y,std::string my_area, bool pac_obj2_arr_used[100],Pacman_Object pac_obj2_arr[100], int win_num, sf::RenderWindow& window);
bool create_nbt(std::string my_area, sf::RenderWindow& window, int win_num, bool pac_obj2_arr_used[100], Pacman_Object pac_obj2_arr[100]);

extern std::string *extra_octants_belong_to_string_pointer;
extern int extra_octants_belong_to_string_pointer_x;
extern std::string get_area_data(std::string area_name, int &x, int &y);
extern void angles_to_quat(float curr_quat2[4], float prev_quat2[4],float &rotate_object_x, float &rotate_object_y, float &rotate_object_z);
extern void quat_to_angles(float curr_quat2[4], float prev_quat2[4],float &rotate_object_x, float &rotate_object_y, float &rotate_object_z);
