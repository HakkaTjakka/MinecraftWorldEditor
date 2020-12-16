extern bool make_regions;
extern bool flushing_mode;
void one_region_voxel_files_to_region_files(bool display_only, char* voxel_filename);

extern char voxel_filename[];

void GLAPIENTRY MessageCallback( GLenum source,
                 GLenum type,
                 GLuint id,
                 GLenum severity,
                 GLsizei length,
                 const GLchar* message,
                 const void* userParam )
{
  fprintf( stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
           ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
            type, severity, message );
}

void SFMLGL2_THREAD()
{
    printf("SFMLGL2 thread starting\n");
    int ret=0;
    do {
        window_num=0;
        printf("Calling do_SFMLGL2()\n");
        ret=do_SFMLGL2(ret);
        printf("Returned from_SFMLGL2()\n");
    } while (ret<=-10);
    printf("SFMLGL2 thread stopped\n");
    window_closed=true;
    SFMLGL2_stop=0;
    SFMLGL2_running=0;
    SFMLView1.requestFocus();
//hoppa
//    SFMLView1.resetGLStates();
}

void SFMLGL2_b_THREAD()
{
    printf("SFMLGL2_b thread starting\n");
    int ret=0;
    do {
        window_num=1;
        ret=do_SFMLGL2(ret);
    } while (ret<=-10);
    printf("SFMLGL2_b thread stopped\n");
    window_closed=true;
    SFMLGL2_b_stop=0;
    SFMLGL2_b_running=0;
    SFMLView1.requestFocus();
//hoppa
//    SFMLView1.resetGLStates();
}

sf::Thread SFMLGL2(&SFMLGL2_THREAD);
sf::Thread SFMLGL2_b(&SFMLGL2_b_THREAD);

using std::string;
string getFileName(const string& s) {

   char sep = '/';

#ifdef _WIN32
   sep = '/';
//   sep = '\\';
#endif

   size_t i = s.rfind(sep, s.length());
   if (i != string::npos) {
      return(s.substr(i+1, s.length() - i));
   }

   return("");
}
char window_name[500]="Noppes";

int keep_running[10]={0,0,0,0,0,0,0,0,0,0};
int is_activated_window[10]={0,0,0,0,0,0,0,0,0,0};
int return_val[10]={0,0,0,0,0,0,0,0,0,0};
bool show_text=true;
bool show_text_short=false;
bool and_now_i_am_here=false;

/*
int main_hoppa3(int argc, char** argv, int cur_x, int cur_y, int max_x, int max_y, int combine);

int main_hoppa2(int argc, char** argv, int cur_x, int cur_y, int max_x, int max_y, int combine) {
    if (keep_running[window_num]) {
        activate_window[window_num]=1;
    } else {
        main_hoppa3(argc,argv,cur_x,cur_y,max_x,max_y,combine);
    }
}
*/

bool init_window_ok[10]={false,false,false,false,false,false,false,false,false,false};
void launch_SFMLGL2()
{
    strcpy(window_name,"SFML OPENGL");
    if (SFMLGL2_running==1)
    {
        if (keep_running[0]) {
            printf("SFMLGL2 already running\n");
            if (!visible[0]) visible[0]=1;
            if (is_activated_window[0]) {
                printf("And active (close first), returning\n");
                return;
            } else {
                printf("Running but not active, activating\n");
                do_SFMLGL2(return_val[0]-1000);
                is_activated_window[0]=1;
                return;
            }
        }

    }
    SFMLGL2_running=1;
    if (init_window_ok[0]==false) reset_text(0);
    init_window_ok[0]=true;
    SFMLGL2.launch();
}

void launch_SFMLGL2_b()
{
    strcpy(window_name,"SFML OPENGL 2");
    if (SFMLGL2_b_running==1)
    {
        if (keep_running[1]) {
            printf("SFMLGL2 b already running\n");
            if (!visible[1]) visible[1]=1;
            if (is_activated_window[1]) {
                printf("And active (close first), returning\n");
                return;
            } else {
                printf("Running but not active, activating\n");
                do_SFMLGL2(return_val[1]-1000);
                is_activated_window[1]=1;
                return;
            }
        }
    }
    SFMLGL2_b_running=1;
    if (init_window_ok[1]==false) reset_text(1);
    init_window_ok[1]=true;
    SFMLGL2_b.launch();
}

void terminate_SFMLGL2()
{
    SFMLGL2.terminate();
}
void terminate_SFMLGL2_b()
{
    SFMLGL2_b.terminate();
}


std::vector<std::string> octants_enschede;
std::vector<std::string> octants_amsterdam;


extern int combine;
#include <dirent.h>
#include <sys/stat.h>

extern void toggle2();

bool test_for_pngfiles(string directory) {
    if (strstr(directory.c_str(), "/nbt/") != NULL)
        directory = GetBaseDir(GetBaseDir(directory))+"/"+GetFileName(directory.substr(0,directory.find_last_of(".")))+"-21/";
    else {
        size_t found;
        found=directory.find_last_of("/\\");
        directory=directory.substr(0,found);
    }

    DIR* dr = opendir(directory.c_str());
    struct dirent *de;
    int png=0;
    size_t tot_size=0;
//    printf("TO DO: ");
    while ((de = readdir(dr)) != NULL) {
        toggle2();
        if ((strstr(de->d_name, ".bmp")) != NULL) {
            closedir(dr);
//            printf(".bmp files found: %s\nConvert with .sh scripts under Ubuntu powershell to .png or adapt this code...\n",directory.c_str());
//            return true;
            return true;
        } else if ((strstr(de->d_name, ".jpg")) != NULL) {
            closedir(dr);
//            printf(".jpg files found: %s\nConvert with .sh scripts under Ubuntu powershell to .png or adapt this code...\n",directory.c_str());
//            return true;
            return true;
        } else if ((strstr(de->d_name, ".png")) != NULL) {
//            struct stat stat_buf;
//            char totfilename[1000];
//            strcpy(totfilename,directory.c_str());
//            strcat(totfilename,"/");
//            strcat(totfilename,de->d_name);
//            int rc = stat(totfilename, &stat_buf);
//            if (rc==0) tot_size+=stat_buf.st_size;
            closedir(dr);
//            png++;
//            printf(".png file(s) found: %s\n",directory.c_str());
            return true;
        }
    }
//    printf("\n");
    closedir(dr);
    if (png==0) {
        printf("No .png/.bmp/.jpg files found: %s\n",directory.c_str());
    }
    else {
        printf("%d .png/.bmp/.jpg files found: %s\n",png,directory.c_str());
        return true;
    }
    return false;
}

void init_sfmlgl();

char arg2_thread[1000];
int send_cur_x_thread=0;
int send_cur_y_thread=0;
int send_max_x_thread=0;
int send_max_y_thread=0;
int combine_thread=0;
extern char MODELS[];

std::string get_area_data(std::string area_name, int &x, int &y);
extern std::string area;

bool remember_911_2=false;
bool remember_911_3=true;

int do_SFMLGL2(int what)
{
    int already_active=0;
    if (what<-900) {
        what=what+1000;
        already_active=1;
    }
    init_sfmlgl();
    char *m_argv[5];
    char arg1[20]="ik";
//    for (int t=0; t<octants.size(); t++) printf("%s\n",octants[t].c_str());
    char arg2[1000];
    srand(time(0));
    std::string str;
    int send_cur_x,send_cur_y,send_max_x,send_max_y;
    if (area!="") {
        int looper=0;
        do {
            static int first=1;
            static int max_x,max_y;
            static int cur_x,cur_y;
            static std::string last_one="";
            printf("Area=%s\n",area.c_str());
            if (area=="Canvas") {
                char filename[2000];
                sprintf(filename,"%s/canvas.nbt", MODELS);
                if (!file_exists(filename)) Make_Canvas();
                area="Models";
                str=filename;
                first=0;
                last_one=area;
            }
            if (last_one!=area) {
                what=0;
                max_x=-1;max_y=-1;
                get_area_data(area,max_x,max_y);
                printf("New area: Size=%d,%d\n",max_x,max_y);
                first=1;
            }
            if (area!="Models" && area!="Canvas") lat_lon=get_lat_lon(area);
            else { lat_lon.x=999; lat_lon.y=999; }
            if (first==1 || lat_lon.x!=999) {
                max_x=-1;max_y=-1;
                str=get_area_data(area,max_x,max_y);
                if (lat_lon.x!=999) {
                    cur_x=lat_lon.x;
                    cur_y=lat_lon.y;
                    printf("From lat_lon.txt: %d,%d %s\n",cur_x,cur_y,area.c_str());
                } else if (area=="Enschede") {
                    printf("Home: %d,%d %s\n",cur_x,cur_y,area.c_str());
//                    cur_x=max_x/2;
//                    cur_y=max_y/2;
                    cur_x=15;
                    cur_y=12;
                } else if (area=="NewYork") {
//                        cur_x=44;
//                        cur_y=54;
//                        printf("Empire State: %d,%d %s\n",cur_x,cur_y,area.c_str());
                        cur_x=50;
                        cur_y=68;
                        printf("WTC: %d,%d %s\n",cur_x,cur_y,area.c_str());
//                } else if (area=="Miami") {
//                        cur_x=0;
//                        cur_y=25;
//                        printf("Test: %d,%d %s\n",cur_x,cur_y,area.c_str());
                } else if (area=="Amsterdam") {
                        cur_x=31;
                        cur_y=28;
                        printf("Test: %d,%d %s\n",cur_x,cur_y,area.c_str());
                } else if (area=="Miami") {
                        cur_x=34;
                        cur_y=42;
                        printf("Miami: %d,%d %s\n",cur_x,cur_y,area.c_str());
                } else if (area=="Schweiz") {
                        cur_x=40;
                        cur_y=21;
                        printf("Matterhorn: %d,%d %s\n",cur_x,cur_y,area.c_str());
                } else {
                        cur_x=max_x/2;
                        cur_y=max_y/2;
                        printf("Center: %d,%d %s\n",cur_x,cur_y,area.c_str());
                }
//                first=0;
            }
            if (looper==1) {
                cur_x=rand()%max_x;
                cur_y=rand()%max_y;
                printf("No .png/.bmp/.jpg -> Random -> %d,%d\n",cur_x,cur_y);
            } else {
                if (what==-20) { cur_x=lat_lon.x; cur_y=lat_lon.y; }
                else if (what==-10) { cur_x--; if (cur_x<0) cur_x=0; }
                else if (what==-11) { cur_x++; if (cur_x>=max_x) cur_x=max_x-1; }
                else if (what==-12) { cur_y--; if (cur_y<0) cur_y=0; }
                else if (what==-13) { cur_y++; if (cur_y>=max_y) cur_y=max_y-1; }
                else if (what==-99) {
                    if (first==0) {
                        cur_x=rand()%max_x;
                        if (max_y!=0) cur_y=rand()%max_y;
                        else cur_y=0;
                        printf("No .png/.bmp/.jpg -> Random -> X=%d,Y=%d\n",cur_x,cur_y);
                    }
                }
            }
            if (first==1) {
                first=0;
            }
            str=get_area_data(area,cur_x,cur_y);
            if (crossing!=1) printf("Trying: %s %d,%d -> %s\n",area.c_str(),cur_x,cur_y,str.c_str());
            strcpy(arg2,str.c_str());
//            found=str.find_last_of("/\\");
            looper=1;
            send_max_x=max_x;
            send_max_y=max_y;
            send_cur_x=cur_x;
            send_cur_y=cur_y;
            last_one=area;
        } while (crossing!=1 && area!=std::string()+"Models" && test_for_pngfiles(str)==false);
    } else {
        area="Enschede";
        int looper=0;
        do {
            static int first=1;
            static int max_x,max_y;
            static int cur_x,cur_y;
            if (first==1) {
                max_x=-1;max_y=-1;
                get_octant_ENSCHEDE(max_x,max_y);
                cur_x=max_x/2;
                cur_y=max_y/2;
            }
            if (looper==1) {
                cur_x=rand()%max_x;
                cur_y=rand()%max_y;
                printf("No .png -> Random -> ");
            } else {
                if (what==-20) { cur_x=lat_lon.x; cur_y=lat_lon.y; }
                else if (what==-10) { cur_x--; if (cur_x<0) cur_x=0; }
                else if (what==-11) { cur_x++; if (cur_x>=max_x) cur_x=max_x-1; }
                else if (what==-12) { cur_y--; if (cur_y<0) cur_y=0; }
                else if (what==-13) { cur_y++; if (cur_y>=max_y) cur_y=max_y-1; }
                else if (what==-99) {
                    if (first==0) {
                        cur_x=rand()%max_x;
                        cur_y=rand()%max_y;
                        printf("N -> Random -> ");
                    }
                }
            }
            if (first==1) {
                first=0;
            }
            str=get_octant_ENSCHEDE(cur_x,cur_y);
            if (crossing!=1) printf("Trying: %d,%d -> %s\n",cur_x,cur_y,str.c_str());
            strcpy(arg2,str.c_str());
//            found=str.find_last_of("/\\");
            looper=1;
            send_max_x=max_x;
            send_max_y=max_y;
            send_cur_x=cur_x;
            send_cur_y=cur_y;
        } while (crossing!=1 &&  area!=std::string()+"Models"  && test_for_pngfiles(str)==false);
    }

//    printf("Loading: %s\n",arg2);
    static int welke=0;

    m_argv[0]=arg1;
    m_argv[1]=arg2;
//    m_argv[2]=arg3;
    int old_shut_up=shut_up;
    shut_up=1;
//combine 0=enschede, 1=amsterdam
    int ret;
    if (already_active) {
        strcpy(arg2_thread,arg2);
        send_cur_x_thread=send_cur_x;
        send_cur_y_thread=send_cur_y;
        send_max_x_thread=send_max_x;
        send_max_y_thread=send_max_y;
        combine_thread=combine;
        return 0;
    }
    else
        ret=main_hoppa2(arg2,send_cur_x,send_cur_y,send_max_x,send_max_y,combine);

    shut_up=old_shut_up;
    return ret;
}

/*
sf::Texture ding_texture[10];
sf::RenderTexture ding_texture_render[10];
sf::Sprite ding_sprite[10];
sf::Sprite ding_sprite_render[10];
int ding_ready[10]={0,0,0,0,0,0,0,0,0,0};
*/
//int main_fly_de_poppa(int what, sf::RenderWindow& window, float mousewheel_delta);
//int main_fly_de_poppa(int argc, char** argv);
int main_fly_de_poppa();

float external_perspective[4]={45.0,1920.0/1080.0,0.01,100.0};

bool fly_on=false;
float mousewheel_delta=0.0;
extern sf::Mutex fly_mutex;
//sf::Texture interface_texture;
//sf::Sprite interface_sprite;

extern void launch_FLY_PLAY();

extern sf::Texture texture_test;
extern sf::RenderTexture rendertexture_test;
extern sf::Sprite sprite_test;
extern sf::Sprite rendersprite_test;
extern sf::Color pixel_test;
extern sf::Shader shader_test;
extern sf::RenderStates states_test;
extern sf::Image image_test;

bool burn=false;
extern float get_fast_sin(float rot);
extern void fast_sin_init();
glm::ivec2 selector_pos=glm::ivec2(-1,-1);

std::string selector_dir="";

std::vector<glm::ivec2> wierdo_requests;
std::vector<glm::ivec2> wierdo_requests_ready;
std::vector<std::string> wierdo_filenames;


double found_lat=0.0;
double found_lon=0.0;
bool lat_lon_found=false;
bool rot_on=false;
int whattodo=0;
sf::RenderWindow* windows_3d[10];
int bar_on[10]={1,1,1,1,1,1,1,1,1,1};

bool rot_plot=false;

int main_hoppa2(char* filename_in, int cur_x, int cur_y, int max_x, int max_y, int yo_combine)
{
    rot_plot=false;
    bool do_model=false;
    if (!depth_shader.loadFromFile("shaders/depth_shader.vert","shaders/depth_shader.frag"))
//    if (!depth_shader.loadFromFile("shaders/depth_shader.frag", sf::Shader::Fragment))
    {
        printf("FRAGMENT SHADER ERROR: %s\n","shaders/depth_shader.frag");
        return false;
    } else {
        printf("FRAGMENT SHADER LOADED: %s\n","shaders/depth_shader.frag");
    }
    bool depth_shader_on=false;
//    sf::Shader::bind(&depth_shader);

    running_3d[window_num]=true;
    fast_sin_init();
//    launch_FLY_PLAY();
//    sf::sleep(sf::seconds(1.0));

    bool plot_quick=false;
    int old_cur_x;
    int old_cur_y;
    burn=false;
    int fixed=8;
    glm::mat4 fly_view_start;
    glm::vec3 fly_position_start;
    int loaded=0;
    int loaded2=0;
    int round=0;
    bool frustum=false;
    int flipflop=0;

    rectangle.setFillColor(sf::Color(40,40,40,40));
    rectangle.setOutlineColor(sf::Color(255,255,255,255));
    rectangle.setOutlineThickness(1.0);

    int load_more_remember=0;
    int load_more_counter=0;
    std::string my_area=area;

    int frustum_toggle=0;
    bool load_more=false;
    std::vector<glm::ivec2> to_load;
    sprintf(marker_filename,"markers_window%d.txt",window_num);
    printf("marker_filename=%s\n",marker_filename);
//    marker_file = fopen(marker_filename, "a");

    bool winsize=false;
    bool start_burn=false;
    float scale=1.0f;
    bool no_new_window=false;
    show_text=true;
    float move_object_x=0.0;
    float move_object_y=0.0;
    float move_object_z=0.0;
    float rotate_object_x=0.0;
    float rotate_object_y=0.0;
    float rotate_object_z=0.0;
    rotate_object_x_base=0.0;
    rotate_object_y_base=0.0;
    rotate_object_z_base=0.0;
    rotate_object_z_to_add=0.0;
    rotate_object_y_to_add=0.0;
    rotate_object_x_to_add=0.0;
    rotate_object_x_cum=0.0;
    rotate_object_y_cum=0.0;
    rotate_object_z_cum=0.0;
    int swoop=0;
    char filename[1000];
    strcpy(filename,filename_in);
    int win_num=window_num;
    keep_running[win_num]=1;
    int exit_code=0;
    bool exit_thread = false;
    bool switch_to_full_screen=false;
    int b_o_x=-1;
    int b_o_y=-1;
    char naam[2000];
    double ctr_lat=0.0;
    double ctr_lon=0.0;
    double ctr_lat_last=0.0;
    double ctr_lon_last=0.0;
    sf::Clock render_clock;
    int render_count=0;
    float render_count_time=0.0;
    sf::Int32 misses=0;
    sf::Int32 hits=0;
    float misses_percentage=0;
    float render_time=0.0;
    float render_fps=0.0;
    float cpu_usage=0.0;
    if (crossing==2 && !and_now_i_am_here) do_wuppie=true;
    bool hoppa_de_poppa=false;
    fps_base=0.0;
    angle_base=0.0;
    speed_base=0.0;
    smooth_x_old=0.0;
    smooth_y_old=0.0;
    while (keep_running[win_num]) {
        exit_code=0;
        exit_thread=0;
        is_activated_window[win_num]=1;
        float perspective[4];

        float translation[3];
        float prev_quat2[4];
        float curr_quat2[4];
        float prev_quat1[4];
        float curr_quat1[4];
        float eye2[3], lookat2[3], up2[3];
        double prevMouseX2, prevMouseY2;

        trackball(curr_quat2, 0, 0, 0, 0);
        trackball(curr_quat1, 0, 0, 0, 0);

        eye2[0] = 0.0f;
        eye2[1] = 0.0f;
        eye2[2] = 3.0f;

        lookat2[0] = 0.0f;
        lookat2[1] = 0.0f;
        lookat2[2] = 0.0f;

        up2[0] = 0.0f;
        up2[1] = 1.0f;
        up2[2] = 0.0f;

        int width2 = 1920;
        int height2 = 1080;
        int repeat=0;

        static sf::Vector2u old_size[10];
        static sf::Vector2i old_pos[10];
        if (first_hoppa==1) {
            first_hoppa=0;
            for (int i=0; i<10; i++) {
                if (videomode[i]==0) {
                    old_size[i] = ( sf::Vector2u(1920,1080) );
                    old_pos[i]  = ( sf::Vector2i(0,0) );
                } else {
                    old_size[i] = ( sf::Vector2u(1920/2.0,1080/2.0) );
                    old_pos[i]  = ( sf::Vector2i(1920/2.0-1920/4.0,1080/2.0-1080/4.0) );
                }
            }
        }
        char window_title[1000];
        sprintf(window_title,"X=%d,Y=%d/(%d,%d) %s",cur_x,cur_y,max_x,max_y,filename);
        int fade=0;
        win_fly_setvisible=1;
//        Pacman_Object pac_object_arr[100];
        sf::RenderWindow window;
        windows_3d[win_num] = &window;
//        sf::RenderWindow window2;
//        bool rot_on=false;
//        sf::Texture texture;
        sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

        sf::ContextSettings contextSettings(0,0,2,3,0);

        contextSettings.depthBits    = 24;
        contextSettings.stencilBits  = 8;
//        contextSettings.antialiasingLevel = 0; //important, set to 0 when running shift-b -> analyse. For color feedback from gpu that codes octant block.
        contextSettings.antialiasingLevel = 0;
//        contextSettings.majorVersion = 3;
//        contextSettings.minorVersion = 3;
        contextSettings.sRgbCapable = false;
//        contextSettings.attributeFlags = sf::ContextSettings::Core;

/*
        contextSettings.antialiasingLevel = 0;
        contextSettings.stencilBits = 8;
        contextSettings.depthBits=24;
*/

        static glm::mat4 test;
//        sf::Sprite background(backgroundTexture);

        Pacman_Object pac_obj;
//        Pacman_Object pac_obj2;
        Pacman_Object pac_obj2_arr[100];
        bool pac_obj2_arr_used[100];


        double lat=0;
        double lon=0;
//        double lat=52.2;
//        double lon= 6.9;

        std::string test_area;
//joepie
        if (area=="Models") {
            printf("%s ->",filename);
            test_area=GetFileName(filename);
            test_area=GetFileName(filename);
            test_area=test_area.substr(0,my_area.length()-4);
        } else {
            test_area=area;
        }
        std::transform(test_area.begin(), test_area.end(), test_area.begin(), ::toupper);

        if (test_area=="ENSCHEDE")       { lat= 52.2;       lon=   6.9;  }
        else if (test_area=="LA")        { lat= 34.08;      lon=-118.29; }
        else if (test_area=="MIAMI")     { lat= 25.789;     lon= -80.206; }
        else if (test_area=="BRUSSEL")   { lat= 50.85;      lon=   4.35; }
        else if (test_area=="AMSTERDAM") { lat= 52.35;      lon=   4.89; }
        else if (test_area=="RIO")       { lat=-22.96;      lon=   -43.17; }
		else if (test_area=="UTRECHT")   { lat= 52.0878895; lon=   5.1184395; }
        else if (test_area=="DENHAAG")   { lat= 52.065;     lon=   4.297; }
        else if (test_area=="NEWYORK")   { lat= 40.689242;  lon= -74.04454; }
        else if (test_area=="SCHWEIZ")   { lat= 46.7;       lon=   7.55; }

        lat_global=lat;
        lon_global=lon;
//        if (area=="Models")    { lat=  -lat;     lon=   -lon;  }

        printf("Area=%s, lat=%f, lon=%f\n",area.c_str(), lat,lon);

        while (!exit_thread || exit_code==-98)
        {
            exit_code=0;
            exit_thread=0;


//            if (no_new_window==false) {
#include "viewer_my_window.h"
//            }


            window.setActive(true);


//            main_fly_de_poppa(1,window,0.0);
//            mousewheel_delta=0.0;

            pac_obj.gDrawObjects.clear();
            pac_obj.materials.clear();
            pac_obj.textures.clear();

            for (int i=0; i<100; i++) {
                pac_obj2_arr_used[i]=false;
                pac_obj2_arr[i].gDrawObjects.clear();
                pac_obj2_arr[i].materials.clear();
                pac_obj2_arr[i].textures.clear();
            }
            size_t pac_obj2_arr_size=0;

            glViewport(0, 0, window.getSize().x, window.getSize().y);
//            glMatrixMode(GL_PROJECTION);
//            glLoadIdentity();
//hoppa
//            gluOrtho2D(-window.getSize().x/2, window.getSize().x/2, -window.getSize().y/2, window.getSize().y/2);

            pac_obj.bmin[0] = pac_obj.bmin[1] = pac_obj.bmin[2] = std::numeric_limits<float>::max();
            pac_obj.bmax[0] = pac_obj.bmax[1] = pac_obj.bmax[2] = -std::numeric_limits<float>::max();

//            window.setActive(false);
//            window.pushGLStates();
            if (crossing==1) {
                FILE *file_arr;
                if ((file_arr = fopen ("OBJECT_ARRAY.TXT", "r"))!=NULL) {
                    printf("Loading object array data\n");
                    char line[200];
                    while (fgets (line,200, file_arr)!=NULL ) {
                        int x=-1;int y=-1;
                        int num=sscanf(line,"X=%d Y=%d\n", &x, &y);
//                        printf("Loading: line=%s X=%d Y=%d\n", line, x, y);
                        if (x<0 && num==2 && line[0]=='X') {
                            x=-1;y=-1;
                            get_area_data(my_area,x,y);
                            int xx; int yy;
                            xx=0;yy=0;
                            printf("X=%d Y=%d to load list: %s\n",xx,yy,get_area_data(my_area,xx,yy).c_str());
                            to_load.push_back(glm::vec2(xx,yy));
                            xx=x-1;yy=0;
                            printf("X=%d Y=%d to load list: %s\n",xx,yy,get_area_data(my_area,xx,yy).c_str());
                            to_load.push_back(glm::vec2(xx,yy));
                            xx=0;yy=y-1;
                            printf("X=%d Y=%d to load list: %s\n",xx,yy,get_area_data(my_area,xx,yy).c_str());
                            to_load.push_back(glm::vec2(xx,yy));
                            xx=x-1;yy=y-1;
                            printf("X=%d Y=%d to load list: %s\n",xx,yy,get_area_data(my_area,xx,yy).c_str());
                            to_load.push_back(glm::vec2(xx,yy));
                            load_more=true;
                            continue;
                        }

                        if (num==2 && line[0]=='X') {
                            int cool=1;
                            for (auto u : Pacman_Objects[win_num]) {
                                if (u.map_x==x && u.map_y==y) {
                                    printf("X=%d Y=%d already loaded.\n",x,y);
                                    cool=0;
                                    break;
                                }
                            }
                            if (cool==1) {
                                on_hold=false;
                                printf("X=%d Y=%d to load list: %s\n",x,y,get_area_data(my_area,x,y).c_str());
                                if (load_extra) {
                                    for (auto u : to_load_extra) {
                                        int cool=1;
                                        for (auto p : Pacman_Objects[win_num]) {
                                            if (p.map_x==u.x && p.map_y==u.y) {
                                                cool=0;
                                                break;
                                            }
                                        }
                                        if (cool==1) {
                                            cool=1;
                                            for (auto p : to_load) {
                                                if (p.x==u.x && p.y==u.y) {
                                                    cool=0;
                                                    break;
                                                }
                                            }
                                            if (cool==1) {
                                                to_load.push_back(glm::vec2(u.x,u.y));
                                                load_more=true;
                                            }
                                        }
                                    }
                                    load_extra=false;
                                    to_load_extra.clear();
                                }

                                to_load.push_back(glm::vec2(x,y));
                                load_more=true;
    //                            cur_x=x;
    //                            cur_y=y;
                            }
                        }
                    }
                    fclose(file_arr);
                    if (to_load.size()>0) {
                        std::vector<glm::ivec2>::iterator it=to_load.begin();
                        glm::ivec2 v=*it;
                        cur_x=v.x;
                        cur_y=v.y;
                        to_load.erase(it);
                        if (to_load.size()==0) load_more=false;
                        std::string str;
                        if (yo_combine==1)
                            str=get_area_data(my_area,cur_x,cur_y);
                        else
                            str=get_octant_ENSCHEDE(cur_x,cur_y);
                        strcpy(filename,str.c_str());
                    }
                } else {
                    printf("Cannot open OBJECT_ARRAY.TXT\n");
                }
            }

            if (strlen(filename)==0)
            {
                std::cout << "Needs input.obj\n" << std::endl;
//                fclose(marker_file);
                return 0;
            }

            window.setActive(true);
//hopla
//            if (false == launch_OBJLOADER(pac_obj.bmin, pac_obj.bmax, pac_obj.gDrawObjects, pac_obj.materials, pac_obj.textures, filename, win_num))

            std::string str1;
            on_hold=false;
            strcpy(filename,get_area_data(my_area,cur_x,cur_y).c_str());
            if (load_extra && to_load_extra.size()>0) {
                int back=cur_x;
                cur_x=to_load_extra[to_load_extra.size()-1].x;
                to_load_extra[to_load_extra.size()-1].x=back;
                back=cur_y;
                cur_y=to_load_extra[to_load_extra.size()-1].y;
                to_load_extra[to_load_extra.size()-1].y=back;

                for (auto u : to_load_extra) {
                    int cool=1;
                    for (auto p : Pacman_Objects[win_num]) {
                        if (p.map_x==u.x && p.map_y==u.y) {
                            cool=0;
                            break;
                        }
                        if (p.map_x==cur_x && p.map_y==cur_y) {
                            cool=0;
                            break;
                        }
                    }
                    if (cool==1) {
                        for (auto p : to_load) {
                            if (p.x==u.x && p.y==u.y) {
                                cool=0;
                                break;
                            }
                        }
                        if (cool==1) {
                            to_load.push_back(glm::vec2(u.x,u.y));
                            load_more=true;
                        }
                    }
                }
                load_extra=false;
                to_load_extra.clear();
                strcpy(filename,get_area_data(my_area,cur_x,cur_y).c_str());
            }
            if (and_now_i_am_here && mirror==4 && crossing==2) {
                crossing=0; mirror=0;
            }

            if (false == LoadObjAndConvert_window(pac_obj.bmin, pac_obj.bmax, pac_obj.gDrawObjects, pac_obj.materials, pac_obj.textures, filename))
            {
//                fclose(marker_file);
                return -1;
            }

            if (and_now_i_am_here) {
                and_now_i_am_here=false;
                mirror=4;crossing=2;
            }

            printf("pac_obj.gDrawObjects.size()=%d\n",pac_obj.gDrawObjects.size());
            printf("pac_obj.materials.size()=%d\n",pac_obj.materials.size());
            printf("pac_obj.textures.size()=%d\n",pac_obj.textures.size());

            if (loaded==1) printf("a");

            reset_text(win_num);

            while (replace_str(filename,"\\","/"));

            pac_obj.filename=filename;
            pac_obj.map_x=cur_x;
            pac_obj.map_y=cur_y;
            pac_obj.show=1;
            pac_obj.north=lat_north;
            pac_obj.south=lat_south;
            pac_obj.east=lon_east;
            pac_obj.west=lon_west;

            pac_obj2_arr_size=0;
            pac_obj.arr_index=pac_obj2_arr_size;

            pac_obj2_arr[pac_obj2_arr_size]=pac_obj;
            pac_obj2_arr_used[pac_obj2_arr_size]=true;

            Pacman_Objects[win_num].push_back(pac_obj2_arr[pac_obj2_arr_size++]);
            Pacman_Objects[win_num][Pacman_Objects[win_num].size()-1].map_x=cur_x;
            Pacman_Objects[win_num][Pacman_Objects[win_num].size()-1].map_y=cur_y;
            Pacman_Objects[win_num][Pacman_Objects[win_num].size()-1].show=1;
            Pacman_Objects[win_num][Pacman_Objects[win_num].size()-1].north=lat_north;
            Pacman_Objects[win_num][Pacman_Objects[win_num].size()-1].south=lat_south;
            Pacman_Objects[win_num][Pacman_Objects[win_num].size()-1].west=lon_west;
            Pacman_Objects[win_num][Pacman_Objects[win_num].size()-1].east=lon_east;
            Pacman_Objects[win_num][Pacman_Objects[win_num].size()-1].filename=filename;

            if (loaded==1) printf("b");
            float btot[3]={0.0,0.0,0.0};
            float bmin[3], bmax[3];
            double lat_min=std::numeric_limits<double>::max();
            double lat_max=-std::numeric_limits<double>::max();
            double lon_min=std::numeric_limits<double>::max();
            double lon_max=-std::numeric_limits<double>::max();
            bmin[0] = bmin[1] = bmin[2] = std::numeric_limits<float>::max();
            bmax[0] = bmax[1] = bmax[2] = -std::numeric_limits<float>::max();
            for (auto u : Pacman_Objects[win_num]) {
                bool fix_lat=false;
                bool fix_lon=false;
                if (u.north>lat_max) { lat_max=u.north; fix_lat=true; }
                if (u.south<lat_min) { lat_min=u.south; fix_lat=true; }
                if (u.west<lon_min)  { lon_min=u.west;  fix_lon=true; }
                if (u.east>lon_max)  { lon_max=u.east;  fix_lon=true; }
                if (fix_lat) btot[2]+=(u.bmax[2]-u.bmin[2]);
                if (fix_lon) btot[1]+=(u.bmax[1]-u.bmin[1]);

                if (btot[0]<u.bmax[0]-u.bmin[0]) btot[0]=u.bmax[0]-u.bmin[0];

                if (u.bmin[0]<bmin[0]) bmin[0]=u.bmin[0]; if (u.bmax[0]>bmax[0]) bmax[0]=u.bmax[0];
                if (u.bmin[1]<bmin[1]) bmin[1]=u.bmin[1]; if (u.bmax[1]>bmax[1]) bmax[1]=u.bmax[1];
                if (u.bmin[2]<bmin[2]) bmin[2]=u.bmin[2]; if (u.bmax[2]>bmax[2]) bmax[2]=u.bmax[2];
            }

            render_locker.lock();
            ready_to_render[win_num]=1;
            render_locker.unlock();
            if (loaded==1) printf("c");


            float maxExtent = 0.5f * (bmax[0] - bmin[0]);
            if (maxExtent < 0.5f * (bmax[1] - bmin[1])) maxExtent = 0.5f * (bmax[1] - bmin[1]);
            if (maxExtent < 0.5f * (bmax[2] - bmin[2])) maxExtent = 0.5f * (bmax[2] - bmin[2]);

            float rotScale = 1.0f;
            float transScale = 1.0f;
            if (loaded==1) printf("d");


    //        GLfloat ratio = static_cast<float>(window.getSize().x) / window.getSize().y;
    //        glFrustum(-ratio, ratio, -1.f, 1.f, 1.f, 500.f);

//            if ((float)window.getSize().y > 0.0) gluPerspective(45.0, (float)window.getSize().x / (float)window.getSize().y, 0.01f, 100.0f);
            external_perspective[0]=perspective[0]=45.0;
            external_perspective[1]=perspective[1]=(float)window.getSize().x / (float)window.getSize().y;
            external_perspective[2]=perspective[2]=0.01;
            external_perspective[3]=perspective[3]=100.0f;
            sf::Event event;
            sf::Event fly_event;
            int event_system=0;

//            main_fly2(window,event,event_system,width2,height2, 0);

            if (loaded==1) printf("f");
            window.setActive(false);

            sf::Clock clock;
            bool mipmapEnabled = true;


            bool last_left_mouse = true;
            bool last_right_mouse = true;
            bool last_middle_mouse = true;

            if (loaded==1) printf("g");

            glm::vec3 ap_tot(0.0f);
            int isvisible=true;

            sf::Vector2i mi;
            sf::Vector2f mf;

            glEnable              ( GL_DEBUG_OUTPUT );
            glDebugMessageCallback( MessageCallback, 0 );

            if (area=="Models") do_model=true;
            else do_model=false;
            while (window.isOpen() && exit_thread==0)
            {
                static bool pull_off=false;
                static bool pull_off2=false;
                static bool flick=false;

                static sf::Vector2i mi;
                static sf::Vector2u ms;
                static sf::Vector2f mf;
                mi = sf::Mouse::getPosition(window);
                ms = window.getSize();

                if (ms.x!=0.0 && ms.y!=0.0) mf = {2.0*(float)mi.x/(float)ms.x-1.0,-2.0*(float)mi.y/ms.y+1.0};

                if (lat_lon_found && load_more==false && load_more_remember==false && pull_off==false && pull_off2==false && flick==false) {
                    if (lat_max-lat_min!=0.0) move_object_y = (float)(- ((double)btot[2]) * ( found_lat - (lat_max+lat_min)/2.0 ) / (lat_max-lat_min));
                    if (lon_max-lon_min!=0.0) move_object_x = (float)(- ((double)btot[1]) * ( found_lon - (lon_max+lon_min)/2.0 ) / (lon_max-lon_min));
//                    if (lat_max-lat_min!=0.0) move_object_y = (float)(- (bmax[2] - bmin[2]) * ( found_lat - (lat_max+lat_min)/2.0 ) / (lat_max-lat_min));
//                    if (lon_max-lon_min!=0.0) move_object_x = (float)(- (bmax[1] - bmin[1]) * ( found_lon - (lon_max+lon_min)/2.0 ) / (lon_max-lon_min));
                    lat_lon_found=false;
                }

//                if (lat_lon_found==false && load_more==false && load_more_remember==false && pull_off==false && flick==false) {
                    if (btot[2]!=0.0) ctr_lat=((lat_max-lat_min)*(  -(double)move_object_y/((double)btot[2])  )) + (lat_max+lat_min)/2.0;
                    if (btot[1]!=0.0) ctr_lon=((lon_max-lon_min)*(  -(double)move_object_x/((double)btot[1])  )) + (lon_max+lon_min)/2.0;
                    if (shade_map>=1) {
                        if (ctr_lat!=ctr_lat_last || ctr_lon!=ctr_lon_last) {
                            lat_lon_to_rel(ctr_lat, ctr_lon, rel_pos_in_map_x, rel_pos_in_map_y);
                            rel_pos_to_pacman();
                        }
                    }
                    ctr_lat_last=ctr_lat;
                    ctr_lon_last=ctr_lon;
//                }

                if (load_more_remember==true) {
                    load_more_counter--;
//                    printf(".");
                    if (load_more_counter<50) {
//                        printf("\n");
                        load_more=true;
                    }
//                    load_more=true;
                }


                if (!isvisible && visible[win_num]==true) {
                    window.setVisible(true);
                    isvisible=true;
                }
                if (loaded==1) printf("h");
                static double mouse_x_add=0.0;
                static double mouse_y_add=0.0;
                static double mouse_x_add_left=0.0;
                static double mouse_y_add_left=0.0;
                static double mouse_x_add_middle=0.0;
                static double mouse_y_add_middle=0.0;
                static double mouse_x_add_right=0.0;
                static double mouse_y_add_right=0.0;

                static bool event_happened;
                event_happened=false;

                static bool plot_func;
//fixed3
//                plot_func=false;

                static float run_time1=0.0;
                static float run_time=0.0;
                static glm::vec3 add_xyz(0.0);

//                if ( (ctr_lat<lat_min || ctr_lat>lat_max || ctr_lon<lon_min || ctr_lon>lon_max) ) {

                if (pull_off2) {
//                    printf("pull_off2=true\n");
                    pull_off2=false;
//                    printf("pull_off2=false\n");

                    if (flick) {
                        lat_lon=GET_LAT_LON3(my_area, ctr_lat, ctr_lon);
                    } else {
//                        lat_lon=GET_LAT_LON2(my_area);
                        lat_lon=GET_LAT_LON3(my_area, ctr_lat, ctr_lon);
                    }
                    if (lat_lon.x!=999) {
                        cur_x=lat_lon.x;
                        cur_y=lat_lon.y;
                        bool cleaning=true;
                        bool first=true;
                        int cnt=0;
                        while (cleaning) {
                            cleaning=false;
                            for (auto q : Pacman_Objects[win_num]) {
                                if (q.map_x<cur_x-1 || q.map_x>cur_x+1 || q.map_y<cur_y-1 || q.map_y>cur_y+1 ) {
                                    q.show=0;
                                    if (first) printf("Erasing: (%2d,%2d)",q.map_x,q.map_y);
                                    else printf(" (%2d,%2d)",q.map_x,q.map_y);
                                    cnt++;
                                    first=false;
                                    erase_one_pacman_objects(q.map_x,q.map_y,win_num,pac_obj2_arr_used,pac_obj2_arr);
                                    cleaning=true;
                                    break;
                                }
                            }
                        }
                        if (cnt>0) printf(" (%d)",cnt);
                        if (!first) printf("\n");

                        first=true;
                        cnt=0;
                        bool ctr_last=false;
                        for (int y=-1; y<=1; y++) {
                            for (int x=-1; x<=1; x++) {
//                                if (flick && (x!=0 || y!=0)) continue;
                                bool found=false;
                                for (auto u : Pacman_Objects[win_num]) {
                                    if (u.map_x==x+cur_x && u.map_y==y+cur_y) {
                                        found=true;
                                        break;
                                    }
                                }
                                if (found==false) {
                                    if (cur_x+x>=0 && cur_x+x<max_x && cur_y+y>=0 && cur_y+y<max_y) {
                                        if (x==0 && y==0) {
                                            ctr_last=true;
                                        } else {
                                            to_load.push_back(glm::vec2(cur_x+x,cur_y+y));
                                        }
                                        if (first) printf("Loading: (%2d,%2d)",cur_x+x,cur_y+y);
                                        else printf(" (%2d,%2d)",cur_x+x,cur_y+y);
                                        load_more=true;
                                        cnt++;
                                        first=false;
                                    }
                                }
                            }
                        }
                        if (ctr_last) to_load.push_back(glm::vec2(cur_x,cur_y));
                        if (cnt>0) printf(" (%d)",cnt);
                        if (!first) printf("\n");
                    }
//                    continue;
                    flick=false;

                }

                #include "viewer_my_events.h"

                g_rotate_object_x=rotate_object_x;
                g_rotate_object_y=rotate_object_y;
                g_rotate_object_z=rotate_object_z;
                g_move_object_x=move_object_x;
                g_move_object_y=move_object_y;
                g_move_object_z=move_object_z;

                i_am_here=true;
                if (make_schematic) {
                    voxelize(Pacman_Objects[win_num]);
                    make_schematic=false;
                }
                if (mirror==4 && crossing==2) {
//tuuttuut1
                    flushing_mode=true;

                    create_nbt(my_area, window, win_num, pac_obj2_arr_used, pac_obj2_arr);
                    printf("Creating rest regions...");
                    make_regions=true;
                    crossing=0; mirror=0;
                }
                if (make_regions) {
//tuuttuut2
//                    flushing_mode=true;

                    ShowTaskBar(true);
                    bar_on[win_num]=1;
                    if (strlen(voxel_filename)!=0) {
                        int x,z;
                        int num=sscanf(voxel_filename,"r.%d.%d.vox",&x,&z);
                        printf("Converting ../cut/%s voxel region file to /saves/test/region/done0/r.%d.%d.mca minecraft files\n",voxel_filename,x,z);
                        one_region_voxel_files_to_region_files(false, voxel_filename);
extern char send_message;
                        send_message='x';
                    } else {
                        printf("Converting ../cut/r.*.*.vox voxel region files to /saves/test/region/done0/r.*.*.mca minecraft files\n");
                        region_voxel_files_to_region_files(false);
                    }
                    make_regions=false;
                }

                if (flick==false && pull_off2==false && pull_off==false && !load_extra && !load_more_remember && !load_more
                        && (ctr_lat<lat_min || ctr_lat>lat_max || ctr_lon<lon_min || ctr_lon>lon_max)   ) {
                    pull_off2=true;
                    flick=true;
                }

                if (pull_off2 && !load_extra && !load_more_remember && !load_more) {
//                    printf("pull_off2=true , loading, continue\n");
                    pull_off=true;
//                    printf("pull_off=true\n");
                    continue;
                } else {
                    if (pull_off) {
                        if (!load_extra && !load_more_remember && !load_more) {
                            pull_off=false;
//                            printf("ready: pull_off=false\n");
                        }
                    }
                }
                if (pull_off) {
//                    printf("pull_off=true, continue\n");
                    continue;
                }

                if (plot_quick) {
                    plot_quick_func(lat,lon,area,win_num,window,eye2,perspective,frustum_toggle,maxExtent,lookat2,up2,
                    move_object_x,move_object_y,move_object_z,translation,curr_quat2, bmin, bmax);
                    window.setActive(false);
                    window.display();
                    continue;
                }
                if (plot_func) {

                    plot_it(lat,lon,area,win_num,window,eye2,perspective,frustum_toggle,maxExtent,lookat2,up2,
                    move_object_x,move_object_y,move_object_z,translation,curr_quat2, bmin, bmax);
                    show_text=true;

                    #include "viewer_my_text.h"

                    window.setActive(false);
                    window.display();
                    continue;
                }

                if (exit_thread || !window.isOpen()) {
                    continue;
                }

                if (round<0) loaded=0;
                else round--;
//                if (loaded==1) printf("11-");
                if (window.hasFocus()) {
                    running_3d[win_num]=true;
                    if (bar_on[win_num]==1) ShowTaskBar(false);
                    bar_on[win_num]=0;
                } else {
                    running_3d[win_num]=false;
                    if (bar_on[win_num]==0) ShowTaskBar(true);
                    bar_on[win_num]=1;
                }
                if (burn) running_3d[win_num]=true;

                if (switch_to_full_screen && videomode[win_num]==1) {
                    switch_to_full_screen=false;
                    if (videomode[win_num]==1) {
                        videomode[win_num]=0;
                        old_size[win_num]=sf::Vector2u(1920,1080);
                        old_pos[win_num]=sf::Vector2i(0,0);
                    } else {
                        videomode[win_num]=1;
                    }
                    window.clear(sf::Color(255,0,0,255));
                    window.display();
                    window.clear(sf::Color(255,255,255,255));
                    window.display();
                    window.clear(sf::Color(0,0,255,255));
                    window.display();
                    window.clear(sf::Color(255,255,0,255));
                    window.display();
                    contextSettings.minorVersion = 3;
                    contextSettings.majorVersion = 3;
//                    window.setVerticalSyncEnabled(true);
                    if (videomode[win_num]==0) {
                        window.create(sf::VideoMode(1920,1080), window_title, sf::Style::Fullscreen, contextSettings);
                    }
                    else {
                        window.create(sf::VideoMode(1920,1080), window_title, sf::Style::Resize | sf::Style::Titlebar | sf::Style::Close , contextSettings);
                    }
                    window.setFramerateLimit(60);
//                    window.setVerticalSyncEnabled(true);
                    hglrc[win_num] = wglGetCurrentContext();
                    hwnd[win_num] = window.getSystemHandle();
                    hdc[win_num] = GetDC(hwnd[win_num]) ;

                    window.setSize(old_size[win_num]);
                    window.setPosition(old_pos[win_num]);
                    width2 = old_size[win_num].x;
                    height2 = old_size[win_num].y;
                    window.clear(sf::Color(50,20,30,128));
                    window.display();

                    auto win = window.getSystemHandle();
                    auto style = GetWindowLong(win, GWL_STYLE);
                    auto ex_style = GetWindowLong(win, GWL_EXSTYLE);

//                    window.setVerticalSyncEnabled(true);
                    window.setActive(true);

                    if (depth_shader_on) {
                        sf::Shader::bind(&depth_shader);
                    }
                    else sf::Shader::bind(NULL);

                    if (window.getSize().y>0) perspective[1]=(float)window.getSize().x / (float)window.getSize().y;
                    else perspective[1]=1920.0/1080.0;
                    for (int n=0; n<10; n++) {
                        window.pollEvent(event);
                        sf::sleep(sf::microseconds(10));
                    }
                } else {
                    switch_to_full_screen=false;
                }


                if (interpolate_on) {
                    interpolate_spline(3);
                    get_view(rotate_object_z, curr_quat2,eye2,lookat2,translation,perspective,bmin,bmax,frustum_toggle);
                }

                if (record_window==1)
                {
                    if (record_pause==0) run_time1=(run_time1+(float)rate/60.0);
                }
                else
                {
                    run_time1=20*run_time1-run_time1;
                    run_time1=(run_time1+clock.getElapsedTime().asSeconds())/20;
                }
                run_time=run_time1*3.0/40;

                int local_request_3d_x=-1;
                int local_request_3d_y=-1;
                int local_request_3d_x_next=-1;
                int local_request_3d_y_next=-1;
//                send_flag=0;
                bool wait_one_loop=false;
                while ((formula==1 || drawmazes==0) &&  wierdo_requests.size()>0) {
                    sf::sleep(sf::seconds(1.0));
                    printf("\nWaiting for formula=0 (shift-f) and drawmazes=on (shift-d)\n");
                }
                if (formula==0 && drawmazes==1 && wierdo_requests.size()>0) {
//                if (formula==1 && shade_map==0 || wierdo_requests.size()>0) {
//                    remember_911_3=true;

                    wierdo_mutex.lock();
                    local_request_3d_x=request_3d_x;
                    local_request_3d_y=request_3d_y;
                    wierdo_mutex.unlock();

                    if (!frustum) {
                        if ((local_request_3d_x>=0 && local_request_3d_y>=0) || start_burn || wierdo_requests.size()>0) printf("Set frustum first, ctrl+alt+f, size- = shift+ctrl-f  size+ = shift-alt-f or ctrl-b (after b and shift-b)\n");
                        wierdo_mutex.lock();
                        wierdo_requests.clear();
                        wierdo_filenames.clear();
                        wierdo_requests_ready.clear();
                        map_end_x=1;
                        map_end_y=1;
                        request_3d_y=-1;
                        request_3d_x=-1;
                        remember_911_2=false;
                        ESCAPE=1;
                        wierdo_mutex.unlock();
                    } else {
                        if (wierdo_requests.size()>0 || (local_request_3d_x>=0 && local_request_3d_y>=0 && local_request_3d_x<frustum_size_x && local_request_3d_y<frustum_size_y)) {
//                            window.setVerticalSyncEnabled(false);

                            wierdo_mutex.lock();
                            int num=wierdo_requests.size();
                            wierdo_mutex.unlock();

                            if (num>0) {
                                int diff=1;
                                while (diff!=0) {
//                                    sf::sleep(sf::milliseconds(10));
                                    wierdo_mutex.lock();
                                    diff=num-wierdo_requests.size();
                                    num=wierdo_requests.size();
                                    wierdo_mutex.unlock();

                                }
                                local_request_3d_x=-1;
                                local_request_3d_y=-1;
                                local_request_3d_x_next=-1;
                                local_request_3d_y_next=-1;
                                wierdo_mutex.lock();

                                while (wierdo_requests.size()>0 && (local_request_3d_x<0 || local_request_3d_y<0 || local_request_3d_x>=frustum_size_x || local_request_3d_y>=frustum_size_y)) {
                                    std::vector<glm::ivec2>::iterator it=wierdo_requests.begin();
                                    glm::ivec2 v=*it;
                                    local_request_3d_x=v.x;
                                    local_request_3d_y=v.y;
                                    if (wierdo_requests.size()>1) {
                                        local_request_3d_x_next=wierdo_requests[1].x;
                                        local_request_3d_y_next=wierdo_requests[1].y;
                                    }
                                    wierdo_requests.erase(it);
                                    if (local_request_3d_x<0 || local_request_3d_y<0 || local_request_3d_x>=frustum_size_x || local_request_3d_y>=frustum_size_y) {
                                        printf("Skipping/erasing %03d %03d\n");
                                        if (wierdo_filenames.size()>0) {
                                            std::vector<std::string>::iterator it=wierdo_filenames.begin();
                                            wierdo_filenames.erase(it);
                                        }

                                    }
                                }
                                wierdo_mutex.unlock();
                            }

                            printf("Got request X=%02d Y=%02d ",local_request_3d_x,local_request_3d_y);
                            frustum_count_x=local_request_3d_x;
                            frustum_count_y=local_request_3d_y;
                            remember_911_2=true;
                            if (burn) {
                                window.setActive(true);
                                running_3d[win_num]=true;

                                if (!(load_3d_objects(frustum_count_x,frustum_count_y, my_area,  pac_obj2_arr_used,pac_obj2_arr, win_num, window))) {
                                    printf("Empty?: X=%d,Y=%d\n",frustum_count_x,frustum_count_y);
                                } else {
                                    wait_one_loop=true;
                                }
                                printf("Plotting. ");

                                printf("Model/area: %s %s ",area.c_str(),my_area.c_str());
                                plot_it( lat,lon,area,win_num,window,eye2,perspective,frustum_toggle,maxExtent,lookat2,up2,
                                move_object_x,move_object_y,move_object_z,translation,curr_quat2, bmin, bmax);
                                window.draw(sprite_shit);
                                window.display();
                                plot_it( lat,lon,area,win_num,window,eye2,perspective,frustum_toggle,maxExtent,lookat2,up2,
                                move_object_x,move_object_y,move_object_z,translation,curr_quat2, bmin, bmax);
                                window.draw(sprite_shit);
                                window.display();

                                texture1_local.update(window);

                                if (!start_burn && contextSettings.antialiasingLevel==0) {  //no antialias or no sprite_shit -> no buffer swap...
                                    if (wierdo_filenames.size()>0 && (frustum_count_x>0 || frustum_count_y>0)) {
                                        sprintf(naam,"%s/out",MODELS);
                                        mkdir(naam);
                                        sprintf(naam,"%s/out/picture.%06d.%06d.png",MODELS,(b_o_y),(b_o_x));
                                        printf("Saving: %s ",naam);
                                        texture1_local.copyToImage().saveToFile(naam);
                                        printf("Ready. ");
                                        std::vector<std::string>::iterator it=wierdo_filenames.begin();
                                        std::string v=*it;
                                        printf("Saving: %s ",v.c_str());
                                        texture1_local.copyToImage().saveToFile(v.c_str());
                                        printf("Ready.\n");
                                        wierdo_filenames.erase(it);
                                        wierdo_mutex.lock();
                                        wierdo_requests_ready.push_back(glm::ivec2(b_o_x,b_o_y));
//                                            wierdo_requests_ready.push_back(glm::ivec2(frustum_count_x,frustum_count_y));
                                        wierdo_mutex.unlock();
                                    }
                                } else if (contextSettings.antialiasingLevel!=0) {
                                    if (wierdo_filenames.size()>0) {
                                        sprintf(naam,"%s/out",MODELS);
                                        mkdir(naam);
                                        sprintf(naam,"%s/out/picture.%06d.%06d.png",MODELS,frustum_count_y,frustum_count_x);
                                        printf("Saving: %s ",naam);
                                        texture1_local.copyToImage().saveToFile(naam);
                                        printf("Ready. ");
                                        std::vector<std::string>::iterator it=wierdo_filenames.begin();
                                        std::string v=*it;
                                        printf("Saving %s ",v.c_str());
                                        texture1_local.copyToImage().saveToFile(v.c_str());
                                        printf("Ready.\n");
                                        wierdo_filenames.erase(it);
                                        wierdo_mutex.lock();
                                        wierdo_requests_ready.push_back(glm::ivec2(frustum_count_x,frustum_count_y));
//                                            wierdo_requests_ready.push_back(glm::ivec2(frustum_count_x,frustum_count_y));
                                        wierdo_mutex.unlock();
                                    }
                                }
                                b_o_x=frustum_count_x;
                                b_o_y=frustum_count_y;
                                start_burn=false;
                            }

                            if (local_request_3d_x==frustum_size_x-1) {
                                map_end_x=1;
                            }
                            if (local_request_3d_y==frustum_size_y-1 && local_request_3d_x==frustum_size_x-1) {
                                if (contextSettings.antialiasingLevel==0) {
                                    if (!(load_3d_objects(frustum_count_x,frustum_count_y, my_area,  pac_obj2_arr_used,pac_obj2_arr, win_num, window))) {
                                        printf("Empty?: X=%d,Y=%d\n",frustum_count_x,frustum_count_y);
                                    } else {
                                        wait_one_loop=true;
                                    }
                                    plot_it( lat,lon,area,win_num,window,eye2,perspective,frustum_toggle,maxExtent,lookat2,up2,
                                    move_object_x,move_object_y,move_object_z,translation,curr_quat2, bmin, bmax);
                                    window.draw(sprite_shit);
                                    if (frustum_count_x==frustum_size_x-1 && frustum_count_y==frustum_size_y-1) {
                                        window.pushGLStates();
                                        text_mutex.lock();
                                        text_text->setPosition( 266,(float)(1080-30));
                                        window.draw(*text_text);
                                        text_mutex.unlock();
                                        window.popGLStates();
                                    }
                                    window.display();
                                    texture1_local.update(window);
                                    sprintf(naam,"%s/out/picture.%06d.%06d.png",MODELS,(b_o_y),(b_o_x));
                                    texture1_local.copyToImage().saveToFile(naam);
                                    printf("Saved %s\n",naam);
                                    if (wierdo_filenames.size()>0) {
                                        std::vector<std::string>::iterator it=wierdo_filenames.begin();
                                        std::string v=*it;
                                        texture1_local.copyToImage().saveToFile(v.c_str());
                                        printf("Saved %s\n",v.c_str());
                                        wierdo_filenames.erase(it);
                                        wierdo_mutex.lock();
                                        wierdo_requests_ready.push_back(glm::ivec2(b_o_x,b_o_y));
                                        wierdo_mutex.unlock();
                                    }
                                }

                                map_end_y=1;
                                remember_911_2=false;
                                printf("I'M READY!!!\n");
                                show_text=true;
                                burn=false;
                                frustum=false;
                                sf::sleep(sf::seconds(5.0));
                            }
//                            if (!do_all) {
//                                remember_911_2=false;
//                            }

                        } else {
//                            window.setVerticalSyncEnabled(true);
//                            remember_911_2=true;
                            local_request_3d_x=-1;
                            local_request_3d_y=-1;
//                            remember_911_2=false;
//                            frustum_count_x=0;
//                            frustum_count_y=0;
//                            remember_911_2=true;
//                            remember_911_3=false;
                            wierdo_mutex.lock();
//                            request_3d_x=-1;
//                            request_3d_y=-1;
                            wierdo_mutex.unlock();
                        }
                    }
                }
                if (burn) remember_911_2=true;

                window.setActive(true);
                if (loaded==1) printf("i");

//                float fun_r=0.5+sin(run_time/(14.0+sin(run_time/30.123)*6))/2;
//                float fun_g=0.5+sin(run_time/(16.132+sin(run_time/50.324)*7))/2;
//                float fun_b=0.5+sin(run_time/(18.343+sin(run_time/43.3243)*8))/2;

                glClearColor(0.7,0.8,1.0,0);
//                glClearColor(fun_r,fun_g,fun_b,1.0f);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                glEnable(GL_DEPTH_TEST);
                glDepthMask(GL_TRUE);   //added
                glClearDepth(1.f);      //added

                if (loaded==1) printf("k");

                glEnable(GL_TEXTURE_2D);
                glMatrixMode(GL_MODELVIEW);
                glLoadIdentity();

                if (loaded==1) printf("3-");

/*
                window.setActive(false);

                if (win_num) {
                    background[win_num]->setRotation(run_time*3.0);
                    background[win_num]->setScale(3.0+sin(run_time/10.0)/2.0,3.0+sin(run_time/10.0)/2.0);
                    background[win_num]->setPosition( 1920.0/2.0+sin( run_time/21.0+sin(run_time/34.0) )*200.0,1080/2.0+sin(run_time/31.0+sin(run_time/22))*100);
                }
                else {
                    background[win_num]->setRotation(run_time*-2.5);
                    background[win_num]->setScale(3.0+sin(run_time/12.0)/2.0,3.0+sin(run_time/13.0)/2.0);
                    background[win_num]->setPosition( 1920.0/2.0+sin( run_time/21.0+sin(run_time/34.0) )*200.0,1080/2.0+sin(run_time/31.0+sin(run_time/22))*100);
                }
                if (loaded==1) printf("5.1-");

                window.pushGLStates();

                window.draw(*background[win_num]);

                if (loaded==1) printf("6-");

                window.popGLStates();

                window.setActive(true);
*/
extern double schematic_size;
                static glm::vec3 move_object;
                move_object = glm::vec3(move_object_x, move_object_y, move_object_z);
                add_xyz = glm::vec3(0.0, 0.0, 0.0);








                static float old_time;
                static float flipje;
                static int ccc=0;
//                if (rot_on) rotate_object_z += (run_time1-old_time)*(5.0);


                schematic_size=6000.0/(eye2[2]*10.0);
                eye22=eye2[2];
//                if (rot_on) rotate_object_z++;
                if ((rot_on || rot_plot) && !interpolate_on) {
                    int flits=true;

                    rotate_object_y+=(rotate_object_y_to_add - rotate_object_y)/13.0;
                    if (fabs(rotate_object_y_to_add - rotate_object_y) < 0.5) {
                    } else flits=false;

                    rotate_object_x+=(rotate_object_x_to_add - rotate_object_x)/13.0;
                    if (fabs(rotate_object_x_to_add - rotate_object_x) < 0.5) {
                    } else flits=false;

                    rotate_object_z+=(rotate_object_z_to_add - rotate_object_z)/13.0;
                    if (fabs(rotate_object_z_to_add - rotate_object_z) < 0.5) {
                    } else flits=false;

                    flipje += (run_time1-old_time)*(2.0); if (flipje>99999999) flipje=0.0;
                    schematic_size=sqrt(0.45*schematic_size*(schematic_size-schematic_size/4.0)*(0.5+0.40*sin(flipje*.999)));
                    ccc++; //ccc>60*3 &&

                    float speed_angle;
                    if (follow_ghost) {
                        speed_angle=atan2(-smooth_y+smooth_y_old, -smooth_x+smooth_x_old);
                    } else {
                        speed_angle=angle_base+speed_base*(fpstime-fps_base)/50.0;
                        fspeedx=cos(speed_angle)*speed_base;
                        fspeedy=sin(speed_angle)*speed_base;
                    }
                    if (flits) {

                        int mazemovex=0;
                        int mazemovey=0;
                        int fff=int(350+350*sin(run_time1/9.113)*sin(run_time1/15.547)*sin(run_time1/12.5399));
                        int ggg=int(150+100*sin((float)(fff)/100.0+run_time1/13.313)*sin(run_time1/16.432)*sin(run_time1/9.9349));
                        int distance=(rand()%fff+ggg);
//                        distance=200;
                        if (!flipflop) {
                            mazemovex=distance*sin(speed_angle);
                            mazemovey=-distance*cos(speed_angle);
                        } else {
                            mazemovex=-distance*sin(speed_angle);
                            mazemovey=distance*cos(speed_angle);
                        }

                        voxel_bottom=0.50*( (distance-140)/400.0 + (rand()%(distance-140))/400.0 )/2.0;
                        if (voxel_bottom<0.01) voxel_bottom=0.01;
                        if (!flipflop) distance/=1.5;

                        if ((follow_ghost && follow_ghost_num==0) || hoppa_de_poppa || flippo || rot_plot) {
                            if (hoppa_de_poppa) exporter2=exporter;
                            burn=true;
                            if (follow_ghost) {
                                mazemovex_voxel=(-pos_ghostx[follow_ghost_num]+1920+maxpixelsx)%maxpixelsx+mazemovex;
                                mazemovey_voxel=(-pos_ghosty[follow_ghost_num]+1080+maxpixelsy)%maxpixelsy+mazemovey;
                            } else {
                                mazemovex_voxel=smooth_x+mazemovex;
                                mazemovey_voxel=smooth_y+mazemovey;
                            }

                            if (voxels.size() > 10000000 || hoppa_de_poppa) {
                                printf("Compressing to total, holding voxels\n");
                            } else {
                                skip_sorting=true;
                            }
                            dont_clear=true;
                            hoppa_de_poppa=false;
                            float fspeedx_o=fspeedx;
                            float fspeedy_o=fspeedy;
                            float fpstime_o=fpstime;
                            fspeedx=0.0;
                            fspeedy=0.0;
                            printf("Bottom=%f%%  Angle=%5.1f  Distance=%4d Voxelisizing\n",voxel_bottom*100.0,speed_angle,distance);

                            voxelize(Pacman_Objects[win_num]);
//                            region_voxel_files_to_region_files(false);

                            if (!skip_sorting) {
                                printf("Compressed to total, deleting voxels\n");
                                voxels.clear();
                            }
                            dont_clear=false;
                            skip_sorting=false;
                            mazemovex_voxel=0;
                            mazemovey_voxel=0;

                            if (voxels_total.size() > 20000000) {
                                dont_clear=true;
                                printf("Clearing all voxels from memory: Flushing all voxels to region voxel files (adding to existing)\n");
                                flush_voxels_to_region_voxel_files();
                                voxels.clear();
                                voxels_total.clear();
                            }
                            if (plot_only) {
                                voxels.clear();
                                voxels_total.clear();
                            }
                            burn=false;
                            fspeedx=fspeedx_o;
                            fspeedy=fspeedy_o;
                            fps_base+=fpstime-fpstime_o;
                        }
                        else printf("Bottom=%f%%  Angle=%5.1f  Distance=%4d Voxelisizing when follow ghost=on ('f' on canvas) or ALT-F10 in 3d window\n",voxel_bottom*100.0,speed_angle,distance);

                        flipflop++;
                        if (flipflop>3) flipflop=0;

                        if (flipflop==0) {
                            rotate_object_z_to_add=speed_angle*180.0/M_PI+rotate_object_z_base+rand()%61-30;
                        } else {
                            rotate_object_z_to_add=speed_angle*180.0/M_PI+180.0+rotate_object_z_base+rand()%61-30;
                        }

                        rotate_object_x_to_add=rotate_object_x_base+rand()%61-30;
                        rotate_object_y_to_add=rotate_object_y_base+rand()%61-30;

                        ccc=0;
//                        if (!(rand()%2)) {
//                            exit_code=-10-rand()%2;
//                            exit_thread = true;
//                            no_new_window=true;
//                        }
                    }
                    smooth_y_old=smooth_y; smooth_x_old=smooth_x;
                }
                old_time=run_time1;








                glMatrixMode(GL_PROJECTION);
                glLoadIdentity();
                make_lookat(perspective, frustum_toggle, eye2, lookat2, up2, move_object, window.getSize(), rot_on, maxExtent);

                glMatrixMode(GL_MODELVIEW);
                glLoadIdentity();

                rotate_around_point(move_object, add_xyz, area, lat, lon, rot_on, interpolate_on, rot_mat, test, curr_quat2, maxExtent, bmin, bmax);

                glScalef(1.0f / maxExtent, 1.0f / maxExtent, 1.0f / maxExtent);

                if ( !(interpolate_on  || burn) ) {
                    translation[0]=-0.5 * (bmax[0] + bmin[0])+add_xyz.x;
                    translation[1]=-0.5 * (bmax[1] + bmin[1])+add_xyz.y;
                    translation[2]=-0.5 * (bmax[2] + bmin[2])+add_xyz.z;
                }
                glTranslatef(translation[0] ,translation[1] ,  translation[2]);


//                glMatrixMode(GL_PROJECTION);
//                glLoadIdentity();
//                make_lookat(perspective, frustum_toggle, eye2, lookat2, up2, move_object, window.getSize(), rot_on);

//                glMatrixMode(GL_MODELVIEW);
//                glLoadIdentity();

                if (set_end_of_movement) {
                    interpolate_on=false;
                    set_end_of_movement=false;
                }

                if (fly_on) {
//                    glDisable(GL_DEPTH_TEST);
//                    glDepthMask(GL_FALSE);   //added
                    window.setActive(false);
                    window.pushGLStates();
//                    interface_sprite.setOrigin(render_texture.getTexture().getSize().x/2.0,render_texture.getTexture().getSize().y/2.0);
                    interface_sprite.setOrigin(interface_texture.getSize().x/2.0,interface_texture.getSize().y/2.0);
                    interface_sprite.setPosition(1920.0/2.0,1080.0/2.0);
//                    interface_sprite.setScale(1920.0/render_texture.getTexture().getSize().x,1080.0/render_texture.getTexture().getSize().y);
                    interface_sprite.setScale(1920.0/interface_texture.getSize().x,1080.0/interface_texture.getSize().y);
                    interface_mutex.lock();
                    window.draw(interface_sprite);
                    interface_mutex.unlock();
                    window.popGLStates();
                    window.setActive(true);
//                    glEnable(GL_DEPTH_TEST);
//                    glDepthMask(GL_TRUE);   //added
//                    glClear(GL_DEPTH_BUFFER_BIT);
                }

                if (smooth)
                    glShadeModel(GL_SMOOTH);
                else
                    glShadeModel(GL_FLAT);

                diff_draw.lock();
                int d_d=different_draw;
                different_draw=0;
                diff_draw.unlock();
//                if (loaded==1) printf("6-");
                if (loaded==1) printf("p3");
                if (Pacman_Objects[win_num].size()>0) {
                    if (d_d) {
                        sf::Shader::bind(NULL);
                        for (auto u : Pacman_Objects[win_num]) {
                            if (u.show==1) {
                                Get_Draw(u.gDrawObjects, u.materials, u.textures);
                            }
                            if (loaded==1) printf("p4");
                        }
                    } else {
    //                    if (loaded==1) printf("7-");
                        if (depth_shader_on) {
                            sf::Shader::bind(&depth_shader);
                            if (record_screen==1)
                            {
                                fpstime=fpstime_factor*(float)record_screen_num*(float)rate/60.0;
                            }
                            else
                            {
                                fpstime=fpstime_factor*clock_shader.getElapsedTime().asSeconds();
                            }
                            depth_shader.setUniform("whattodo",         whattodo);
                            depth_shader.setUniform("wave_phase",       fpstime);
                            depth_shader.setUniform("mouse",            mf);
                            depth_shader.setUniform("ratio",            (float)ms.y/(float)ms.x);
                            depth_shader.setUniform("resolution",       sf::Glsl::Vec2((float)ms.x,(float)ms.y));
                            depth_shader.setUniform("move",             sf::Glsl::Vec3(move_object_x,   move_object_y , move_object_z));
                            depth_shader.setUniform("bmin",             sf::Glsl::Vec3(bmin[0],         bmin[1],        bmin[2]));
                            depth_shader.setUniform("bmax",             sf::Glsl::Vec3(bmax[0],         bmax[1],        bmax[2]));
                            depth_shader.setUniform("translation",      sf::Glsl::Vec3(translation[0],  translation[1], translation[2]));
                            depth_shader.setUniform("add_xyz",          sf::Glsl::Vec4(add_xyz4.x,      add_xyz4.y,     add_xyz4.z,     add_xyz4.w));
                            depth_shader.setUniform("maxExtent", maxExtent);
                        }
                        else sf::Shader::bind(NULL);
                        for (auto u : Pacman_Objects[win_num]) {
                            if (u.show==1) Draw(u.gDrawObjects, u.materials, u.textures);

/*
                            if (local_request_3d_x>=0 && local_request_3d_y>=0 && formula==1 && shade_map==0) {
                                window.setActive(false);
//                                render_texture1_local.clear(sf::Color(0,0,0,0));
//                                render_texture1_local.pushGLStates();

                                window2.setActive(true);
//                                render_texture1_local.setActive(true);
//                                sf::Texture::bind(&render_texture1_local.getTexture());
                                glClearColor(255,0,0,0);
                                glEnable(GL_DEPTH_TEST);
                                glDepthMask(GL_TRUE);   //added
                                glClearDepth(1.f);      //added
                                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                                glEnable(GL_TEXTURE_2D);
                                glMatrixMode(GL_MODELVIEW);
                                glLoadIdentity();


                                glEnable(GL_TEXTURE_2D);
                                glMatrixMode(GL_PROJECTION);
                                glLoadIdentity();
                //                gluPerspective(perspective[0],perspective[1],perspective[2],perspective[3]);
                                makeFrustum(perspective[0],perspective[1],perspective[2],perspective[3],frustum_toggle, eye2);

                                glMatrixMode(GL_MODELVIEW);
                                glLoadIdentity();

                                glMultMatrixf((float*)&adapt);

                                glScalef(1.0f / maxExtent, 1.0f / maxExtent, 1.0f / maxExtent);

                                glTranslatef(translation[0] ,translation[1] ,  translation[2]);


//                                glEnable(GL_TEXTURE_2D);
//                                glMatrixMode(GL_MODELVIEW);
//                                glLoadIdentity();

                                if (u.show==1) Draw(u.gDrawObjects, u.materials, u.textures);
                                window2.setActive(false);
//                                render_texture1_local.setActive(false);
//                                render_texture1_local.popGLStates();
                                window2.display();
//                                render_texture1_local.display();

                                window.setActive(true);
                            }
*/
                        }
                    }
                }

//                if (local_request_3d_x>=0 && local_request_3d_y>=0)
//                    render_texture1_local.setActive(false);
//                else
                    window.setActive(false);

//                window.setActive(false);

//                if (remember_911_2) show_text=false;
#include "viewer_my_text.h"

                if (fly_on) {
                    window.pushGLStates();

//                    interface_sprite1.setOrigin(render_texture1.getTexture().getSize().x/2.0,render_texture1.getTexture().getSize().y/2.0);
                    interface_sprite1.setOrigin(interface_texture1.getSize().x/2.0,interface_texture1.getSize().y/2.0);
                    interface_sprite1.setPosition(1920.0/2.0,1080.0/2.0);
//                    interface_sprite1.setScale(1920.0/render_texture1.getTexture().getSize().x,1080.0/render_texture1.getTexture().getSize().y);
                    interface_sprite1.setScale(1920.0/interface_texture1.getSize().x,1080.0/interface_texture1.getSize().y);
                    interface_mutex.lock();
                    window.draw(interface_sprite1);
                    doesnt_work=0;
                    interface_mutex.unlock();
                    window.popGLStates();
                } else {
                    if (doesnt_work==0) doesnt_work=1;
                }
                static float Hz60=1.0/60.0;
                static float render_current;
                render_current=render_clock.getElapsedTime().asSeconds();
                if (render_current-render_time < Hz60) {
                    hits++;
                } else {
                    misses++;
                }
                misses_percentage=misses/(hits+misses)*100.0;
                cpu_usage=(cpu_usage*9.0+(render_current-render_time)/Hz60)/10.0;
                window.display();
                render_time=render_clock.getElapsedTime().asSeconds();
                render_count++;
                if (render_count==60) {
                    render_count_time=render_time-render_count_time;
                    if (render_count_time!=0) render_fps=60.0/render_count_time;
                    render_count_time=render_time;
                    render_count=0;
                }

                remember_911_3=false;
//                if (!wait_one_loop) {


/*
                if (local_request_3d_x>=0 && local_request_3d_y>=0 && local_request_3d_x<frustum_size_x && local_request_3d_y<frustum_size_y) {
                    printf("Interfacing X=%2d,Y=%2d ********************************************************* ",local_request_3d_x,local_request_3d_y);
                    texture1_local.update(window);
                    sf::sleep(sf::milliseconds(250));
                    if (do_all) {
                        remember_911_3=true;
                        if (local_request_3d_x==frustum_size_x-1) {
                            map_end_x=1;
                        }
                        if (local_request_3d_y==frustum_size_y-1 && local_request_3d_x==frustum_size_x-1 ) {
                            map_end_y=1;
                            remember_911_2=false;
                            printf("I'M READY!!!\n");
                            show_text=true;
                        }
                    } else {
                    }
                    wierdo_mutex.lock();
                    request_3d_y=-1;
                    wierdo_mutex.unlock();
                    local_request_3d_x=-1;
                    local_request_3d_y=-1;

                    int test=0;
                    while (test>=0) {
                        wierdo_mutex.lock();
                        test=request_3d_y;
                        wierdo_mutex.unlock();
                        if (test!=-2) {
                            sf::sleep(sf::milliseconds(5));
                        }
                    }




                } else {
                }
*/

//                }


                if (fly_on) {
//                    doesnt_work=0;
///                    interface_mutex.lock();
                }

                if (remember_911) {
                    static bool first=true;
                    static sf::Texture texture;
                    if (first || window.getSize()!=texture.getSize()) {
                        texture.create(window.getSize().x, window.getSize().y);
                        mkdir("../remember_911");
                        first=false;
                    }
                    texture.update(window);

                    char filename[2000];
                    sprintf(filename,"../remember_911/picture.%06d.%06d.png",frustum_count_y,frustum_count_x);
//                    sprintf(filename,"../remember_911/picture.%06d.%06d.png",frustum_size_y-1-frustum_count_y,frustum_count_x);
                    printf("Saving: %s ",filename);
                    if (texture.copyToImage().saveToFile(filename)) {
                        printf("Ok.\n",filename);
                    } else {
                        printf("ERROR SAVING FILE!!! ABORTING.\n",filename);
                        remember_911=false;
                        glMatrixMode(GL_PROJECTION);
                        glLoadIdentity();
                        makeFrustum(perspective[0],perspective[1],perspective[2],perspective[3],frustum_toggle, eye2);
                    }
                    if (remember_911) {
                        frustum_count_x--;
                        if (frustum_count_x<0) {
                            frustum_count_x=frustum_size_x-1;
                            frustum_count_y--;
                            printf("\n");
                            if (frustum_count_y<0) {
//                                frustum_count_x=frustum_size_x-1;
                                frustum_count_y=frustum_size_y-1;
                                remember_911_set_off=true;
                                system("REMEMBER_911_TO_LEVELS_8x8_001.BAT");
//                                system("REMEMBER_911_TO_LEVELS_100x200_001.BAT");
//                                level=1;
//                                next=1;
//                                window.setVerticalSyncEnabled(true);
                                glMatrixMode(GL_PROJECTION);
                                glLoadIdentity();
                                remember_911=false;
                                show_text=true;
                                makeFrustum(perspective[0],perspective[1],perspective[2],perspective[3],frustum_toggle, eye2);
                            }
                        }
                    }
                }
                if (remember_911_set_off) {
                    remember_911_set_off=false;
                    remember_911=false;
                    printf("Time to save %d textures: %.3f seconds\n",frustum_size_x*frustum_size_y,(float)clock_911.getElapsedTime().asSeconds());
                }


                if (record_window) do_the_recording_stuff_window(window, win_num);
            }

            render_locker.lock();
            ready_to_render[win_num]=0;
            render_locker.unlock();

//            window.setActive(false);
            window.setActive(true);
//            window.pushGLStates();

            int num_p=0;
            int num_pb=0;
            int num_p1=0;
            int num_p1b=0;
            int num_p2=0;
//            printf("deleting objects sleeping 2 secs\n");
//            sf::sleep(sf::seconds(2));


            for (auto p : Pacman_Objects[win_num]) {
                {
                    num_p1=0;
                    GLuint gluint_arr[p.textures.size()];
                    int num_com=0;
                    for (auto u : p.textures) {
                        gluint_arr[num_com++]=u.second;
                        if (!(num_com&0xff) || num_com==p.textures.size()) printf("object#=%d index=%d glDeleteTextures() texture#=%d\r",num_p2,p.arr_index,num_p1);
                        num_p++;
                        num_p1++;
                    }
                    glDeleteTextures((GLsizei)p.textures.size(), gluint_arr);
                }
                {

                    num_p1b=0;
                    GLuint gluint_arr[p.gDrawObjects.size()];
                    int num_com=0;
                    for (auto u : p.gDrawObjects) {
                        gluint_arr[num_com++]=u.vb_id;
                        if (!(num_com&0xff) || num_com==p.gDrawObjects.size()) {
                            printf("object#=%d index=%d glDeleteTextures() texture#=%d  ",num_p2,p.arr_index,num_p1);
                            printf("glDeleteBuffers() drawobjects#=%d\r",num_pb);
                        }
                        num_pb++;
                        num_p1b++;
                    }
                    glDeleteBuffers((GLsizei)p.gDrawObjects.size(), gluint_arr);
                }

                printf("object#=%d index=%d glDeleteTextures() texture#=%d  ",num_p2,p.arr_index,num_p1);
                printf("glDeleteBuffers() drawobjects#=%d   \n",num_p1b);
                p.map_x=-1;
                p.map_y=-1;
                pac_obj2_arr_used[p.arr_index]=false;
                num_p2++;

                pac_obj2_arr[p.arr_index].gDrawObjects.clear();
                pac_obj2_arr[p.arr_index].materials.clear();
                pac_obj2_arr[p.arr_index].textures.clear();
                p.gDrawObjects.clear();
                p.materials.clear();
                p.textures.clear();
            }
            Pacman_Objects[win_num].clear();

//            window.popGLStates();
            window.setActive(false);
//            window.pushGLStates();
//            window.popGLStates();
//            window.resetGLStates();
//            printf("objects deleted, sleeoping 2 secs\n");
//            sf::sleep(sf::seconds(2));
//            reset_text(win_num);

/*
            for (auto p : Pacman_Objects[win_num]) {
                int num_p1b=0;
                GLuint gluint_arr[p.gDrawObjects.size()];
                int num_com=0;
                for (auto u : p.gDrawObjects) {
                    gluint_arr[num_com++]=u.vb_id;
                    if (!(num_com&0xff) || num_com==p.gDrawObjects.size()) printf("glDeleteBuffers()     object#=%d/drawobjects#=%d\r",num_p2b,num_pb);
                    num_pb++;
                    num_p1b++;
                }
                printf("glDeleteBuffers()      objects#=%3d/    #drawobjects=%4d index=%d\n",num_p2b,num_p1b,p.arr_index);
                num_p2++;
                glDeleteBuffers((GLsizei)p.gDrawObjects.size(), gluint_arr);
                p.map_x=-1;
                p.map_y=-1;
                pac_obj2_arr_used[p.arr_index]=false;
            }
            pac_obj2_arr_size=0;
            printf("glDeleteTextures() tot #objects=%3d/tot #textures=%4d\r",num_p2,num_p);
            if (num_p>0) printf("\n");
            printf("glDeleteBuffers()  tot #objects=%3d/tot #drawobjects=%d\r",num_p2b,num_pb);
*/
            if (num_pb>0 || num_p>0) printf("\n");
            if (window.isOpen()) {
                if (exit_code!=-2) {
                    old_size[win_num]=window.getSize();
                    old_pos[win_num]=window.getPosition();
//                    no_new_window=true;
//                    exit_thread=false;
//                    exit_code=0;
                }
                if (no_new_window==false) {
                    printf("Closing window\n");
                    window.close();
                    if (bar_on[win_num]==0) ShowTaskBar(true);
                    bar_on[win_num]=1;
                    running_3d[win_num]=false;
                } else {
//                    loaded=1;
//                    round=3;
                    printf("NOT closing window\n");
                    exit_thread=false;
                    if (exit_code<=-10) {
                        my_area=area;
                        do_SFMLGL2(exit_code-1000);
                        strcpy(filename,arg2_thread);
                        cur_x=send_cur_x_thread;
                        cur_y=send_cur_y_thread;
                        max_x=send_max_x_thread;
                        max_y=send_max_y_thread;
                        yo_combine=combine_thread;
                        exit_code=0;
                    }
                }
            }
        }
        // if the thread has a current rendering context ...
        if(hglrc[win_num]) {
//            wglDeleteContext(hglrc);
//            printf("wglDeleteContext()\n");
//            wglMakeCurrent(NULL, NULL) ;
        }
        if (exit_code<=-10) {
            do_SFMLGL2(exit_code-1000);
        } else {
            if (exit_code!=-1) {
                if (exit_code!=-1)  { printf("Exiting, staying active\n"); return_val[win_num]=exit_code; }
                if (exit_code==-2)  { printf("Resizing window, reloading object\n"); return_val[win_num]=0; }
                is_activated_window[win_num]=0;
                do {
                    sf::sleep(sf::milliseconds(500));
                    if (exit_code==-2) is_activated_window[win_num]=1;
                }
                while (!is_activated_window[win_num]);
                running_3d[win_num]=true;
//                exit_thread=0;
//                exit_code=0;
            }
        }
        if (exit_code!=-1 && exit_code!=-2) {
            strcpy(filename,arg2_thread);
            cur_x=send_cur_x_thread;
            cur_y=send_cur_y_thread;
            max_x=send_max_x_thread;
            max_y=send_max_y_thread;
            yo_combine=combine_thread;
//            exit_code=0;
//            exit_thread=0;
        }
        if (exit_code==-2) {
//            exit_code=0;
            exit_thread=0;
        }
    }
    printf("Exiting, leaving thread\n");
    ShowTaskBar(true);
    running_3d[win_num]=false;
//    fclose(marker_file);
    return exit_code;
}


//hGLRC = wglCreatContext (hDC);
//wglMakeCurrent(hDC, hGLRC);

void expres(int objnum) {
//    printf("Joehoe...");

//    std::vector<Pacman_Object> Pacman_Objects;
    //std::vector<Pacman_Object> *Pacman_Objects_Global[10];

    static int first=1;
    static float curr_quat2[4];
    static float prev_quat2[4];
    static float eye2[3], lookat2[3], up2[3];
    static double prevMouseX2, prevMouseY2;
    static sf::Texture backgroundTexture;
    static sf::Sprite background;
    static sf::Clock clock;

    if (first==1) {
//        backgroundTexture.setSrgb(sRgb);
        if (!backgroundTexture.loadFromFile("E:\PACMAN\pictures3\files\space-planets-black-background.jpg")) {
            printf("shit happens. -.> resources/background.jpg");
            return;
        }
        background.setTexture(backgroundTexture);
        background.setOrigin(backgroundTexture.getSize().x/2,backgroundTexture.getSize().y/2);
        background.setPosition(1920.0/2.0,1080.0/2.0);
        background.setScale(0.1,0.1);
        trackball(curr_quat2, 0, 0, 0, 0);

        eye2[0] = 0.0f;
        eye2[1] = 0.0f;
        eye2[2] = 3.0f;

        lookat2[0] = 0.0f;
        lookat2[1] = 0.0f;
        lookat2[2] = 0.0f;

        up2[0] = 0.0f;
        up2[1] = 1.0f;
        up2[2] = 0.0f;

        first=0;
    }

//    context_locker.lock();
//    window.setActive(true);
//    wglMakeCurrent (hdc,hglrc);

    context_locker.lock();
    SFMLView1.setActive(true);
//    wglMakeCurrent (hdc_sfmlview1,hglrc_sfmlview1);
//    wglMakeCurrent (hdc[objnum],hglrc[objnum]);

    glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    glEnable(GL_DEPTH_TEST);
//    glDepthMask(GL_TRUE);   //added
//    glClearDepth(0.f);      //added
//added
//    glDepthRange(0.0f, 1.0f);
//    glClearDepth(0.0f);
//                        glDepthRange(0.0f, 1.0f);
//                        glClearDepth(0.0f);

    float bmin[3], bmax[3];
    bmin[0] = bmin[1] = bmin[2] = std::numeric_limits<float>::max();
    bmax[0] = bmax[1] = bmax[2] = -std::numeric_limits<float>::max();
    for (auto u : Pacman_Objects[objnum]) {
//        if (u->bmin[0]<bmin[0]) bmin[0]=u->bmin[0]; if (u->bmax[0]>bmax[0]) bmax[0]=u->bmax[0];
//        if (u->bmin[1]<bmin[1]) bmin[1]=u->bmin[1]; if (u->bmax[1]>bmax[1]) bmax[1]=u->bmax[1];
//        if (u->bmin[2]<bmin[2]) bmin[2]=u->bmin[2]; if (u->bmax[2]>bmax[2]) bmax[2]=u->bmax[2];
        if (u.bmin[0]<bmin[0]) bmin[0]=u.bmin[0]; if (u.bmax[0]>bmax[0]) bmax[0]=u.bmax[0];
        if (u.bmin[1]<bmin[1]) bmin[1]=u.bmin[1]; if (u.bmax[1]>bmax[1]) bmax[1]=u.bmax[1];
        if (u.bmin[2]<bmin[2]) bmin[2]=u.bmin[2]; if (u.bmax[2]>bmax[2]) bmax[2]=u.bmax[2];
    }
    float maxExtent = 0.5f * (bmax[0] - bmin[0]);
    if (maxExtent < 0.5f * (bmax[1] - bmin[1])) maxExtent = 0.5f * (bmax[1] - bmin[1]);
    if (maxExtent < 0.5f * (bmax[2] - bmin[2])) maxExtent = 0.5f * (bmax[2] - bmin[2]);

//    glViewport(0, 0, SFMLView1.getSize().x, SFMLView1.getSize().y);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45.0, (float)SFMLView1.getSize().x / (float)SFMLView1.getSize().y, 0.01f, 100.0f);

//hoppa
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();

    background.setRotation(-clock.getElapsedTime().asSeconds()*10);

    SFMLView1.setActive(false);

    SFMLView1.pushGLStates();
    SFMLView1.draw(background);
    SFMLView1.popGLStates();

    SFMLView1.setActive(true);

    glEnable(GL_TEXTURE_2D);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    GLfloat mat[4][4];

    gluLookAt(eye2[0], eye2[1], eye2[2], lookat2[0], lookat2[1], lookat2[2], up2[0],   up2[1], up2[2]);
    build_rotmatrix(mat, curr_quat2);
    glMultMatrixf(&mat[0][0]);
    glScalef(1.0f / maxExtent, 1.0f / maxExtent, 1.0f / maxExtent);
    glTranslatef(-0.5 * (bmax[0] + bmin[0]), -0.5 * (bmax[1] + bmin[1]),  -0.5 * (bmax[2] + bmin[2]));

    if (smooth)
        glShadeModel(GL_SMOOTH);
    else
        glShadeModel(GL_FLAT);


    for (auto u : Pacman_Objects[objnum]) {
        Draw(u.gDrawObjects, u.materials, u.textures);
//        Draw(u->gDrawObjects, u->materials, u->textures);
    }

//    wglMakeCurrent (NULL,NULL);
//    context_locker.unlock();

extern sf::WindowHandle sfmlview1_handle;

    SFMLView1.setActive(false);
}



/*
//double theta = 90+lat; //% Rotation around y-axis
//double phi = lon; //% Rotation around z-axis
//phi = (phi*M_PI)/180.0; //% Convert degrees to radians
//theta = (theta*M_PI)/180.0;

//double x = cos(lon*M_PI/180.0)*cos(lat*M_PI/180.0);
//double y = sin(lon*M_PI/180.0)*cos(lat*M_PI/180.0);
//double z = sin(lat*M_PI/180.0);

//                glm::mat4 test2 = glm::eulerAngleYXZ(  x,y,z);

//                glm::mat4 test2(    cos(theta)*cos(phi) , cos(theta)*sin(phi),  sin(theta), 0 ,
//                                    -sin(phi) , cos(phi), 0, 0,
//                                    -sin(theta)*cos(phi) , - sin(theta)*sin(phi) , cos(theta), 0,
//                                    0, 0, 0, 1);
*/

/*

//                if (!fly_on) {
//                    if (area=="Models")
//                        test = glm::rotate(float((rotate_object_x)*M_PI/180.0),glm::vec3(1.0,0.0,0.0)) * test;
//                    else
//                        test = glm::rotate(float((-90+rotate_object_x)*M_PI/180.0),glm::vec3(1.0,0.0,0.0)) * test;
//                }


//                glm::mat4 test2(1.0f);
//                test2= glm::rotate(test2, float(rotate_object_z*M_PI/180), {NORMALz.x,NORMALz.y,NORMALz.z} ) ;




//                    Camera *fly_camera_pointer=&camera;


                glm::vec3 plane_position;
                if (fly_on) {
//                    while (plane_ready==false) sf::sleep(sf::milliseconds(5));
                    delta2_mutex.lock();
                    glm::mat4 scale_view=*fly_view_pointer;

//                    glm::vec3 camera_position = fly_camera_pointer->m_position;

                    plane_position = fly_plane_position;
//                    printf("fpp=%f %f %f   ",plane_position.x,plane_position.y,plane_position.z);
                    delta2_mutex.unlock();

//                    camera_position=camera_position * float(0.1);
//                    scale_view=glm::translate(camera_position) * scale_view;

//                    plane_ready=false;

                    float *arr1=(float*)(&scale_view);
                    float (&arr2)[4][4] = *reinterpret_cast<float (*)[4][4]>(arr1);

                    float *arr1b=(float*)(&fly_view_start);
                    float (&arr2b)[4][4] = *reinterpret_cast<float (*)[4][4]>(arr1b);


                    arr2[3][0]=(arr2[3][0]-arr2b[3][0])*0.1;
                    arr2[3][1]=(arr2[3][1]-arr2b[3][1])*0.1;
                    arr2[3][2]=(arr2[3][2]-arr2b[3][2])*0.1;
//                    printf("1");
                    plane_position=plane_position-fly_plane_position_start;
                    scale_view=glm::translate(scale_view,glm::vec3(-plane_position.x*0.1,-plane_position.y*0.1,-plane_position.z*0.1));
//                    scale_view=glm::translate(scale_view,glm::vec3(-camera_position.x,-camera_position.y,-camera_position.z));
//                    scale_view=glm::translate(scale_view,glm::vec3(-translation[0],-translation[1],-translation[2]));


//excluded for short.
                    test = scale_view * test ;

//                    scale_view=glm::translate(scale_view,glm::vec3(plane_position.x*0.1,plane_position.y*0.1,plane_position.z*0.1));
//                    scale_view=glm::translate(scale_view,glm::vec3(camera_position.x,camera_position.y,camera_position.z));
//                    scale_view=glm::translate(scale_view,glm::vec3(translation[0],translation[1],translation[2]));

//                    scale_view=glm::scale(scale_view , glm::vec3(0.1,0.1,0.1)) ;

//                    Angles view_angles;
//                    columnMatrixToAngles( view_angles, arr2 );
//                    glm::mat4 rm = glm::mat4(1.0f);
//                    arr1b=(float*)(&rm);

//                    rm = rotate(rm, glm::radians(view_angles.yaw),   glm::vec3(0.0, 0.0, 1.0));
//                    rm = rotate(rm, glm::radians(view_angles.pitch), glm::vec3(0.0, 1.0, 0.0));
//                    rm = rotate(rm, glm::radians(view_angles.roll),  glm::vec3(1.0, 0.0, 0.0));

//                    rm = my_rotate_zyx(glm::radians(view_angles.yaw),glm::radians(view_angles.pitch),glm::radians(view_angles.roll)) * rm;
//                    rm = my_rotate(glm::radians(view_angles.pitch),glm::radians(view_angles.yaw),glm::radians(view_angles.roll)) * rm;

//                    rm = rotate(rm, glm::radians(view_angles.yaw),   glm::vec3(0.0, 0.0, 1.0));
//                    rm = rotate(rm, glm::radians(view_angles.pitch), glm::vec3(0.0, 1.0, 0.0));
//                    rm = rotate(rm, glm::radians(view_angles.roll),  glm::vec3(1.0, 0.0, 0.0));

//                    arr2b[3][0]=arr2[3][0];
//                    arr2b[3][1]=arr2[3][1];
//                    arr2b[3][2]=arr2[3][2];

//                      test= rm * test;

*/

/*
                    static int cnt=0;
                    cnt--;
                    if (cnt<0) {
                        Angles view_angles;
                        cnt=30;
                        wprintf(L"\x1b[0;0H");

                        columnMatrixToAngles( view_angles, arr2 );
                        for (int c=0; c<4; c++) {
                            for (int r=0; r<4; r++) {
                                printf("%-+f ",arr2[r][c]);
                            }
                            printf("\n");
                            for (int r=0; r<4; r++) {
                                printf("%-+f ",arr2[r][c]-arr2b[r][c]);
                            }
                            printf("\n\n");
                        }

                        printf("pitch=%-+f  roll=%f  yaw=%f  ",view_angles.pitch,view_angles.roll,view_angles.yaw);
                        printf("X=%f  Y=%f  Z=%f\n",arr2[0][3],arr2[1][3],arr2[2][3]);

                    }
*/

/*
//                    arr2[3][0]=0.1*arr2[3][0];
//                    arr2[3][1]=0.1*arr2[3][1];
//                    arr2[3][2]=0.1*arr2[3][2];
//                    float *sp=(float*) &scale_position[0];
//                    *(sp+3*4)=*(sp+3*4)*0.1;
//                    *(sp+3*4+1)=*(sp+3*4+1)*0.1;
//                    *(sp+3*4+2)=*(sp+3*4+2)*0.1;


//                    test= scale_view * test ;
                }
*/
/*
                if (area!="Models") {
                    test = glm::eulerAngleYXZ(  (float)((lat)*M_PI/180.0) ,(float)((lon)*M_PI/180.0) , (float)(0.0));
                    test = glm::rotate(test , float((-90.0)*M_PI/180.0),glm::vec3(0.0,1.0,0.0)) ;
                    test = glm::rotate(test, float(-90.0*M_PI/180), {NORMALz.x,NORMALz.y,NORMALz.z} ) ;
                }
*/
