#include <../MCA-NBT-EDIT.HPP>
#include <winsock2.h>
#include <../VOXEL.HPP>

extern bool make_region_from_voxel(int x, int z);
extern std::vector<hit_one_region> ready_regions;
extern bool no_plotting;

bool sort_cubic=false;

extern int F4;
extern bool rot_plot;
extern int follow_ghost;
extern int follow_ghost_num;
extern int picturex;
extern int picturey;
extern int posx;
extern int posy;
extern double smooth_x;
extern double smooth_y;
extern float fspeedx;
extern float fspeedy;
extern int *pos_ghostx;
extern int *pos_ghosty;
extern int maxpixelsx;
extern int maxpixelsy;
extern float* fspeed_ghostx;
extern float* fspeed_ghosty;
extern bool make_regions;

extern int flippo;
extern int ghost;
void flush_voxels_to_region_voxel_files();
extern bool skip_sorting;
int active_window_num=-1;

extern float int_q[4];
extern float int_e[3];
extern float int_l[3];
extern float int_t[3];
extern float int_p[4];
extern float int_bmin[3];
extern float int_bmax[3];
extern int int_frustum_toggle;
extern float fpstime;
extern sf::Clock clock_shader;
glm::vec4 test_pos(0.0);
extern glm::vec4 add_xyz4;
bool i_am_here=false;
bool create_boundaries(std::string area, sf::RenderWindow& window);
bool Make_Canvas();
extern double smooth_x;
extern double smooth_y;
extern int follow_ghost_num;

bool flushing_mode=false;

float g_rotate_object_x=0;
float g_rotate_object_y=0;
float g_rotate_object_z=0;
float g_move_object_x=0;
float g_move_object_y=0;
float g_move_object_z=0;
extern int shut_up;
void flush_voxels();

bool cubic=false;

std::vector<Voxel> voxels_total;
std::vector<hit_one_region> vector_hit_regions;

bool analyse_3d(double lat, double lon, std::string my_area, int cur_x, int win_num, sf::RenderWindow& window, float eye2[3],
                       float perspective[4],int frustum_toggle, glm::mat4 adapt, float maxExtent,
                       float lookat2[3], float up2[3], float move_object_x, float move_object_y, float move_object_z,
                       float translation[3],float curr_quat2[4], float bmin[3], float bmax[3]);
bool plot_it(double& lat, double& lon, std::string& my_area, int win_num, sf::RenderWindow& window, float eye2[3],
                       float perspective[4],int frustum_toggle, float maxExtent,
                       float lookat2[3], float up2[3], float move_object_x, float move_object_y, float move_object_z,
                       float translation[3],float curr_quat2[4], float bmin[3], float bmax[3]);
bool plot_quick_func( double& lat, double& lon, std::string& my_area, int win_num, sf::RenderWindow& window, float eye2[3],
                       float perspective[4],int frustum_toggle, float maxExtent,
                       float lookat2[3], float up2[3], float move_object_x, float move_object_y, float move_object_z,
                       float translation[3],float curr_quat2[4], float bmin[3], float bmax[3]);
bool                    reanalyse_3d(int cur_x, std::string& my_area, int win_num, bool pac_obj2_arr_used[100],Pacman_Object pac_obj2_arr[100], sf::RenderWindow& window);
bool                 get_one_3d_init(int cur_x, std::string& my_area, int win_num, bool pac_obj2_arr_used[100],Pacman_Object pac_obj2_arr[100], sf::RenderWindow& window);
bool   get_one_3d_init_load_obj_data(int cur_x, std::string& my_area, int win_num, bool pac_obj2_arr_used[100],Pacman_Object pac_obj2_arr[100], sf::RenderWindow& window);
bool                     set_view_3d(int cur_x, std::string& my_area, int win_num, bool pac_obj2_arr_used[100],Pacman_Object pac_obj2_arr[100], sf::RenderWindow& window);
bool get_one_3d_update_load_obj_data();
glm::ivec2 get_lat_lon(std::string my_area);
glm::ivec2 GET_LAT_LON2(std::string my_area);
extern int GET_LAT_LON_FROM_FILE_LIST(char *naam);
glm::ivec2 GET_LAT_LON3(std::string my_area, double lat, double lon);

float voxel_bottom=0.0;

extern void make_lookat(float perspective[4], int frustum_toggle, float eye2[3], float lookat2[3], float up2[3], glm::vec3 move_object, sf::Vector2u window_size, bool rot_on, float maxExtent);
extern void rotate_around_point(glm::vec3 move_object, glm::vec3 &add_xyz, std::string area, double lat, double lon, bool rot_on, bool interpolate_on, glm::mat4 rot_mat, glm::mat4 &test, float curr_quat2[4], float maxExtent, float bmin[3], float bmax[3]);
extern void lat_lon_to_rel(double latitude, double longitude, double &rel_pos_in_map_x, double &rel_pos_in_map_y );
extern void rel_to_lat_lon(double rel_pos_in_map_x, double rel_pos_in_map_y, double &latitude, double &longitude);
extern double rel_pos_in_map_x;
extern double rel_pos_in_map_y;
extern void rel_pos_to_pacman();
double eye22=0.0;
int main_hoppa2(char* filename_in, int cur_x, int cur_y, int max_x, int max_y, int yo_combine);
int do_SFMLGL2(int what);
extern int do_all;
int SFMLGL2_stop=0;
int SFMLGL2_running=0;
int SFMLGL2_b_stop=0;
int SFMLGL2_b_running=0;
glm::ivec2 lat_lon;
glm::mat4 rot_mat;
float *rot_arr=(float*)(&rot_mat);

extern int drawmazes;
extern sf::RenderWindow SFMLView1;
extern int request_3d_x;
extern int request_3d_y;
sf::RenderTexture texture_shit;
sf::Sprite sprite_shit;
int window_num=0;
extern int send_flag;
extern sf::RenderTexture render_texture1_local;
extern sf::Texture texture1_local;
extern sf::Sprite sprite1_local;
extern int formula;
extern int shade_map;
extern int request_3d_x;
extern int request_3d_y;
extern int map_end_x;
extern int map_end_y;
extern int ESCAPE;



extern int active_window_num;
extern sf::RenderWindow* windows_3d[];

float rotate_object_x_base=0.0;
float rotate_object_y_base=0.0;
float rotate_object_z_base=0.0;
float rotate_object_z_to_add=0.0;
float rotate_object_y_to_add=0.0;
float rotate_object_x_to_add=0.0;
float rotate_object_x_cum=0.0;
float rotate_object_y_cum=0.0;
float rotate_object_z_cum=0.0;

float fps_base=0.0;
float angle_base=0.0;
float speed_base=0.0;
double smooth_x_old;
double smooth_y_old;

bool dont_write_to_region_voxels=false;
extern bool automate;
bool to_gpu=true;
bool dont_clear=false;
extern bool add_to_region;
extern int loader_index;
extern bool burn;
extern int F2;
extern void toggle4();
extern int count_ready_global;
extern int loader_index;
extern bool nbt_creating;
extern int follow_ghost;
extern int follow_ghost_num;
int mazemovex_voxel=0;
int mazemovey_voxel=0;
bool skip_sorting=false;
extern float g_rotate_object_x;
extern float g_rotate_object_y;
extern float g_rotate_object_z;
extern double schematic_size;
extern bool rot_on;
//int hit_regions[1000][1000][12];
extern double smooth_x;
extern double smooth_y;
extern float g_move_object_x;
extern float g_move_object_y;
extern float g_move_object_z;
extern float g_rotate_object_x;
extern float g_rotate_object_y;
extern float g_rotate_object_z;

bool flushing=false;
extern int scan_x,scan_z;
char mc_text0[100];
extern char mc_text1[100];
extern char mc_text2[100];
extern int update_request;
unsigned char region_block[512*256*512*4];
bool voxel_to_file=false;
//extern int region_counter[1000][1000];
extern sf::Color random_pixel;
extern bool load_voxels();
int first_wuppie=true;
bool play(int& play_num, float bmin[3], float bmax[3]);

#define HIT_REPLACE 1
#define HIT_ADD 2

extern bool adapt_colors;

int region_offset_x=0;
int new_region_offset_x=0;
int region_offset_z=0;
int new_region_offset_z=0;
bool make_schematic=false;
void make_schematic_nbt(std::string fname, std::vector<Voxel>& voxels, size_t first,size_t num_voxels);

extern char LEVELDIR[];
extern int BITMAPSX;
extern int BITMAPSY;
extern int level;
extern int mirror;
extern sf::Image scan_image;
extern bool plot_only;

void OBJECT3D_TO_NBT(std::vector<BufferObject> &buffers, std::vector<tinyobj::material_t> &materials, char* filename, float bmin[3], float bmax[3]);
void NBT_TO_OBJECT3D(std::vector<BufferObject> &buffers, std::vector<tinyobj::material_t> &materials, char* filename, float bmin[3], float bmax[3]);
void CANVAS_OBJECT3D(std::vector<BufferObject> &buffers, std::vector<tinyobj::material_t> &materials, char* filename, float bmin[3], float bmax[3], int picturex, int picturey);
extern void RECALC_BMIN_BMAX(std::vector<BufferObject> buffers, float bmin[3], float bmax[3], double lat, double lon);
extern void RECALC_BMIN_BMAX2(std::vector<BufferObject> buffers, float bmin[3], float bmax[3], double lat, double lon);
extern void RECALC_BMIN_BMAX3(std::vector<BufferObject> buffers, float bmin[3], float bmax[3], double lat, double lon);
extern void RECALC_BMIN_BMAX4(std::vector<BufferObject> buffers, float bmin[3], float bmax[3], double lat, double lon);

void       WUPPIE(std::vector<BufferObject> buffers, std::vector<tinyobj::material_t> &materials, float bmin[3], float bmax[3], double lat, double lon, std::string fn);
int WUPPIE_VECTOR(std::vector<BufferObject> buffers, std::vector<tinyobj::material_t> &materials, float bmin_o[3], float bmax_o[3], double lat, double lon, std::string fn);
void  WUPPIE_SUBS(std::vector<BufferObject> buffers, std::vector<tinyobj::material_t> &materials, float bmin_o[3], float bmax_o[3], double lat, double lon, std::string fn);
extern int main_mceditor6_fixed(int region_x, int region_z, unsigned char* mc);

extern void ROTJE(glm::vec3 &torot, float bmin[3], float bmax[3], double lat, double lon);

extern nbt_tag_t* read_nbt_file(const char* name, int flags);

double lat_north=0.0;
double lat_south=0.0;
double lon_west=0.0;
double lon_east=0.0;
extern std::string area;
extern int MCEDITOR_running;

double lat_global=0.0;
double lon_global=0.0;
extern double eye22;

std::vector<Voxel> voxels;

bool do_wuppie=false;
bool hold_voxels=false;
std::string obj_dir;
static bool LoadObjAndConvert_window(float bmin[3], float bmax[3],
                              std::vector<DrawObject>& drawObjects,
                              std::vector<tinyobj::material_t>& materials,
                              std::map<std::string, GLuint>& textures,
                              char* filename)
{
    sf::Event event;
    float rotScale = 1.0f;
    float transScale = 1.0f;

    std::string nbt_filename=filename;
    obj_dir=GetBaseDir(nbt_filename);

    if (nbt_filename.find_last_of(".") != std::string::npos) nbt_filename=nbt_filename.substr(0,nbt_filename.find_last_of("."))+".nbt";

    if (!burn) {
        if (file_exists(nbt_filename.c_str())) printf("Loading: %s",nbt_filename.c_str());
        else printf("Loading: %s",filename);
        if (load_extra) {
            printf(" extra=");
            for (auto u : to_load_extra) printf("(%d,%d)",u.x,u.y);
        }
    }
    lat_north=0.0;
    lat_south=0.0;
    lon_west=0.0;
    lon_east=0.0;
    if (latitude_longditude!="") {
        char line[2000];
        strcpy(line,latitude_longditude.c_str());
        while (replace_str(line,".",","));
        int num=sscanf(line,"N=%lf S=%lf W=%lf E=%lf", &lat_north, &lat_south, &lon_west, &lon_east);
        if (num==4) {
            char lat_str[100];
            char lon_str[100];
            sprintf(lat_str,"%lf",(lat_north+lat_south)/2.0); while (replace_str(lat_str,",","."));
            sprintf(lon_str,"%lf",(lon_east+lon_west)/2.0); while (replace_str(lon_str,",","."));
            if (!burn) {
                printf(" https://www.google.com/maps/@%s,%s,17.00z\n",lat_str,lon_str);
            }
            if (!burn && F2==0 && !crossing>0) {
                char command_str[1000];
                sprintf(command_str,"\"C:\\Program Files (x86)\\Google\\Chrome\\Application\\chrome.exe\" https://www.google.com/maps/@%s,%s,18.00z >nul 2>nul",lat_str,lon_str);
                system(command_str);
            }
        }
    } else printf("\n");

    double lat=lat_global;
    double lon=lon_global;
//    double lat=(lat_north+lat_south)/2.0;
//    double lon=(lon_east+lon_west)/2.0;

    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;

    timerutil tm;

    tm.start();

    std::string base_dir = GetBaseDir(filename);

    if (base_dir.empty())
    {
        base_dir = ".";
    }
#ifdef _WIN32
//    base_dir += "\\";
    base_dir += "/";
#else
    base_dir += "/";
#endif

    std::string texture_dir = filename;
    if (strstr(texture_dir.c_str(), "/nbt/") != NULL || strstr(texture_dir.c_str(), "/obj/") != NULL)
        texture_dir = GetBaseDir(GetBaseDir(filename))+"/"+GetFileName(texture_dir.substr(0,texture_dir.find_last_of(".")))+"-21/";
    else
        texture_dir=base_dir;

    std::string warn;
    std::string err;

    std::vector<BufferObject> buffers;
    bool NBT_LOADED=false;
    bool ret=true;
//    printf(" KOEKOEK: %s\n",GetFileName(filename).c_str());
    if (strstr(filename, "canvas.nbt") != NULL) {
        char naam[2000];
        sprintf(naam,"%s/%dx%d/%03d/",LEVELDIR,BITMAPSX,BITMAPSY,level);
        texture_dir = naam;
        printf("(canvas)");
    }
    if (0) {
        char naam[2000];
//        BufferObject one_buffer;
//        buffers.push_back(one_buffer);
        CANVAS_OBJECT3D(buffers, materials, filename, bmin,bmax, 0, 0);
        sprintf(naam,"%s/%dx%d/%03d/",LEVELDIR,BITMAPSX,BITMAPSY,level);
        texture_dir = naam;
        NBT_LOADED=true;
        printf("(canvas)");
    } else if (file_exists(nbt_filename.c_str())) {
        NBT_TO_OBJECT3D(buffers, materials, filename, bmin,bmax);
        if (lat_north!=0.0 || lat_south!=0.0 || lon_west!=0.0 || lon_east!=0.0 || strstr(filename, "models") != NULL || area=="Models") {
            if (strstr(filename, "models") != NULL || area=="Models") {
                RECALC_BMIN_BMAX(buffers, bmin,bmax, lat, lon);
            }
            else
                RECALC_BMIN_BMAX2(buffers, bmin,bmax, lat, lon);
        }

        NBT_LOADED=true;
        printf("(nbt)");
    } else {
        ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, filename, base_dir.c_str());
    }


    if (!warn.empty())
    {
        std::cout << "WARN: " << warn << std::endl;
    }
    if (!err.empty())
    {
        std::cerr << err << std::endl;
    }

    tm.end();

    if (!ret && !NBT_LOADED)
    {
        std::cerr << "Failed to load " << filename << std::endl;
        return false;
    }

    if ((!burn && F2==1)) {
        printf(" Parsing time: %d [ms]\n", (int)tm.msec());
        if (NBT_LOADED) {
            printf("# of materials = %d  ", (int)materials.size());
            printf("# of buffers   = %d\n", (int)buffers.size());
            size_t total=0;
            for (auto u : buffers) {
                total+=u.length-1;
            }
            printf("# of elements  = %d  ", (int)(total) / 11 / 3);
        } else {
            printf("# of vertices  = %d  ", (int)(attrib.vertices.size()) / 3);
            printf("# of normals   = %d  ", (int)(attrib.normals.size()) / 3);
            printf("# of texcoords = %d  ", (int)(attrib.texcoords.size()) / 2);
            printf("# of materials = %d  ", (int)materials.size());
            printf("# of shapes    = %d\n", (int)shapes.size());
        }
    }


    // Append `default` material
    if (!NBT_LOADED) {
        materials.push_back(tinyobj::material_t());
    }
    sf::Clock clock;
    sf::Time time_total=clock.getElapsedTime();
    sf::Time time=clock.getElapsedTime();

    if (!burn && F2==1) printf("CPU -> GPU:\n");

    {
        if (!nbt_creating || crossing>0) {
            time=clock.getElapsedTime();
            if (!burn && F2==1) printf("pushing %d threads to load files -> ",materials.size()-1);
            for (size_t m = 0; m < materials.size(); m++) {
                quick_toggle();
                tinyobj::material_t* mp = &materials[m];
                if (mp->diffuse_texname.length() > 0) {
//                    printf("mp->diffuse_texname=%s ",mp->diffuse_texname.c_str());
                    if (textures.find(mp->diffuse_texname) == textures.end()) {
//                        printf(" found!\n");
                        GLuint texture_id;
                        int w, h;
                        int comp;

                        std::string texture_filename = texture_dir + mp->diffuse_texname;
//                        std::string texture_filename = base_dir + mp->diffuse_texname;

                        bool png=false;

                        std::string upped=texture_filename;
                        std::transform(upped.begin(), upped.end(),upped.begin(), ::toupper);

                        if (strstr(upped.c_str(), ".PNG") != NULL ||
                            strstr(upped.c_str(), ".JPG") != NULL ||
                            strstr(upped.c_str(), ".BMP") != NULL ) {
//                        if (strstr(texture_filename.c_str(), ".png") != NULL ||
//                            strstr(texture_filename.c_str(), ".jpg") != NULL ||
//                            strstr(texture_filename.c_str(), ".bmp") != NULL ) {
                            png=true;
                            comp=4;
                            int ret;
    //hier
    //                        printf("m=%d pushing %s            \r",m,texture_filename.c_str());

                            if (!nbt_creating || crossing>0) push_image_file(texture_filename);
    //                        printf("m=%d Pushed %s\n",m,texture_filename.c_str());
                        }
                    } // else printf(" not found!\n");

                }
            }
            if (!burn && F2==1) printf("total time pushing %d textures: %d milliseconds\n",loader_index,clock.getElapsedTime().asMilliseconds()-time.asMilliseconds());
    //        printf("\nGiving load signal:\n");
            time=clock.getElapsedTime();
            batch_load=1;
            int wait_stat=0;
            int count_ready=0;

            while ((wait_stat=wait_for_all_loaded()) == 0) {
    //            printf("\rWaiting for all ready loading or error... ");
    //            quick_toggle();
                if (!burn && F2==1) {
                    printf("\r%d/%d Waiting for textures... ",count_ready_global,loader_index);
                } else {
                    if( NBT_LOADED=true)  printf("\r(nbt)");
                    printf(" %d/%d Waiting for textures... ",count_ready_global,loader_index);
    //                toggle4();
                }

                sf::sleep(sf::seconds(0.025));
    //            while (window.pollEvent(event));
            }
    //        printf("\nStatus report: ");
            if (wait_stat==1) { if (!burn && F2==1) printf("\r%d/%d Waiting for textures...Ok. ",count_ready_global,loader_index); }
            else {
                if (!burn && F2==1) printf("Status= NOT OK!!! File(s) not found or error loading... ");
                clear_image_buffer();
                return false;
            }
            printf("\r%d/%d Waiting for textures...Ok. ",count_ready_global,loader_index);
    //        printf("'clearing' images ");
    //        clear_image_buffer();

    //        printf("image cleared\n");
            if (!burn && F2==1) printf("Total time loading %d TEXTURES: %d milliseconds\n",materials.size()-1,clock.getElapsedTime().asMilliseconds()-time.asMilliseconds());

            time=clock.getElapsedTime();
            if (!burn && F2==1 && to_gpu) printf("loading textures to GPU: ");
            for (size_t m = 0; m < materials.size(); m++)
            {
    //            while (window.pollEvent(event));
                tinyobj::material_t* mp = &materials[m];
                if (mp->diffuse_texname.length() > 0)
                {
                    if (textures.find(mp->diffuse_texname) == textures.end())
                    {
                        GLuint texture_id;
                        int w, h;
                        int comp;

                        std::string texture_filename = texture_dir + mp->diffuse_texname;
//                        std::string texture_filename = base_dir + mp->diffuse_texname;

                        unsigned char* image;

                        sf::Image sfml_image;
                        bool png=false;
                        if (strstr(texture_filename.c_str(), ".png") != NULL ||
                            strstr(texture_filename.c_str(), ".jpg") != NULL ||
                            strstr(texture_filename.c_str(), ".bmp") != NULL ) {
                            png=true;
                            comp=4;
                            int ret;
                            if (!image_buffer[m]->ok) {
                                image=0;
                                printf("Image not ok!!!!\n");
                                return false;
                            }
                            else {
                                w=image_buffer[m]->image->getSize().x;
                                h=image_buffer[m]->image->getSize().y;
//jojo
//                                w=image_buffer[m]->image.getSize().x;
//                                h=image_buffer[m]->image.getSize().y;
                                image=(unsigned char*)image_buffer[m]->image->getPixelsPtr();
//                                image=(unsigned char*)image_buffer[m]->image.getPixelsPtr();
                            }
                        } else {
                            image = stbi_load(texture_filename.c_str(), &w, &h, &comp, STBI_default);
                        }

                        if (!image)
                        {
                            std::cerr << "Unable to load texture: " << texture_filename
                                      << std::endl;
                        }
                        if (to_gpu) {
                            glGenTextures(1, &texture_id);
                            glBindTexture(GL_TEXTURE_2D, texture_id);
                            if (comp == 3) {
                                glTexStorage2D(GL_TEXTURE_2D, 6, GL_RGB8, w, h);
                                glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, w, h, GL_RGB, GL_UNSIGNED_BYTE, image);
                            } else if (comp == 4) {
                                glTexStorage2D(GL_TEXTURE_2D, 6, GL_RGBA8, w, h);
                                glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, w, h, GL_RGBA, GL_UNSIGNED_BYTE, image);
                            }
                            else
                            {
                                assert(0);  // TODO
                            }
                            glGenerateMipmap(GL_TEXTURE_2D);
                            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        //                    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
                            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

                            if (smooth)
                                glShadeModel(GL_SMOOTH);
                            else
                                glShadeModel(GL_FLAT);
                            glBindTexture(GL_TEXTURE_2D, 0);
                            if (!burn && F2==1) quick_toggle();
                        }
                        if (!png) stbi_image_free(image);
                        textures.insert(std::make_pair(mp->diffuse_texname, texture_id));
    //                    printf("done             \r");
                    }
                }
            }
            if (!burn && F2==1 && to_gpu) printf(" total time loading textures to GPU: %d milliseconds\n",clock.getElapsedTime().asMilliseconds()-time.asMilliseconds());
        }
    }
//    printf("\n");

//    bmin[0] = bmin[1] = bmin[2] = std::numeric_limits<float>::max();
//    bmax[0] = bmax[1] = bmax[2] = -std::numeric_limits<float>::max();

    {
        int tot_indices=0;
        time=clock.getElapsedTime();
        if (!burn && F2==1 && !NBT_LOADED) printf("Loading shapes (%d)\n",(int)shapes.size());

        BufferObject one_buffer;

        if (!NBT_LOADED) {

            for (size_t s = 0; s < shapes.size(); s++)
            {
    //            printf("\rLoading shape %5d(%d)\r",(int)s,(int)shapes.size());
                DrawObject o;
                std::vector<float> buffer;  // pos(3float), normal(3float), color(3float)

                // Check for smoothing group and compute smoothing normals
                std::map<int, vec3> smoothVertexNormals;
                if (hasSmoothingGroup(shapes[s]) > 0)
                {
                    computeSmoothingNormals(attrib, shapes[s], smoothVertexNormals);
                }
                size_t f=0;
                size_t shape_size=shapes[s].mesh.indices.size() / 3;
                for (f = 0; f < shape_size; f++)
                {
                    tinyobj::index_t idx0 = shapes[s].mesh.indices[3 * f + 0];
                    tinyobj::index_t idx1 = shapes[s].mesh.indices[3 * f + 1];
                    tinyobj::index_t idx2 = shapes[s].mesh.indices[3 * f + 2];

                    int current_material_id = shapes[s].mesh.material_ids[f];

                    if ((current_material_id < 0) ||
                            (current_material_id >= static_cast<int>(materials.size())))
                    {
                        // Invaid material ID. Use default material.
                        current_material_id = materials.size() - 1;  // Default material is added to the last item in `materials`.
                    }
                    float diffuse[3];
                    for (size_t i = 0; i < 3; i++)
                    {
                        diffuse[i] = materials[current_material_id].diffuse[i];
                    }
                    float tc[3][2];
                    if (attrib.texcoords.size() > 0)
                    {
                        if ((idx0.texcoord_index < 0) || (idx1.texcoord_index < 0) ||
                                (idx2.texcoord_index < 0))
                        {
                            tc[0][0] = 0.0f;
                            tc[0][1] = 0.0f;
                            tc[1][0] = 0.0f;
                            tc[1][1] = 0.0f;
                            tc[2][0] = 0.0f;
                            tc[2][1] = 0.0f;
                        }
                        else
                        {
                            if (attrib.texcoords.size() <=  size_t(2 * idx0.texcoord_index + 1)){
                                tc[0][0] = 0.0f; tc[0][1] = 0.0f; tc[1][0] = 0.0f; tc[1][1] = 0.0f; tc[2][0] = 0.0f; tc[2][1] = 0.0f;
                            } else if (attrib.texcoords.size() <=  size_t(2 * idx1.texcoord_index + 1)){
                                tc[0][0] = 0.0f; tc[0][1] = 0.0f; tc[1][0] = 0.0f; tc[1][1] = 0.0f; tc[2][0] = 0.0f; tc[2][1] = 0.0f;
                            } else  if (attrib.texcoords.size() <=  size_t(2 * idx2.texcoord_index + 1)){
                                tc[0][0] = 0.0f; tc[0][1] = 0.0f; tc[1][0] = 0.0f; tc[1][1] = 0.0f; tc[2][0] = 0.0f; tc[2][1] = 0.0f;
                            } else {
                                tc[0][0] = attrib.texcoords[2 * idx0.texcoord_index]; tc[0][1] = 1.0f - attrib.texcoords[2 * idx0.texcoord_index + 1];
                                tc[1][0] = attrib.texcoords[2 * idx1.texcoord_index]; tc[1][1] = 1.0f - attrib.texcoords[2 * idx1.texcoord_index + 1];
                                tc[2][0] = attrib.texcoords[2 * idx2.texcoord_index]; tc[2][1] = 1.0f - attrib.texcoords[2 * idx2.texcoord_index + 1];
                            }
                        }
                    }
                    else
                    {
                        tc[0][0] = 0.0f; tc[0][1] = 0.0f; tc[1][0] = 0.0f; tc[1][1] = 0.0f; tc[2][0] = 0.0f; tc[2][1] = 0.0f;
                    }

                    float v[3][3];
                    for (int k = 0; k < 3; k++)
                    {
                        int f0 = idx0.vertex_index;             int f1 = idx1.vertex_index;             int f2 = idx2.vertex_index;
                        assert(f0 >= 0);                        assert(f1 >= 0);                        assert(f2 >= 0);
                        v[0][k] = attrib.vertices[3 * f0 + k];  v[1][k] = attrib.vertices[3 * f1 + k];  v[2][k] = attrib.vertices[3 * f2 + k];
                        bmin[k] = std::min(v[0][k], bmin[k]);   bmin[k] = std::min(v[1][k], bmin[k]);   bmin[k] = std::min(v[2][k], bmin[k]);
                        bmax[k] = std::max(v[0][k], bmax[k]);   bmax[k] = std::max(v[1][k], bmax[k]);   bmax[k] = std::max(v[2][k], bmax[k]);
                    }
                    float n[3][3];
                    {
                        bool invalid_normal_index = false;
                        if (attrib.normals.size() > 0)
                        {
                            int nf0 = idx0.normal_index;        int nf1 = idx1.normal_index;             int nf2 = idx2.normal_index;

                            if ((nf0 < 0) || (nf1 < 0) || (nf2 < 0))
                            {
                                // normal index is missing from this face.
                                invalid_normal_index = true;
                                static int first=1;
                                if (first==1)
                                {
                                    first=0;
                                    if (!burn && F2==1) printf("Invalid_normal_index\n");
                                }
                            }
                            else
                            {
                                for (int k = 0; k < 3; k++)
                                {
                                    if (size_t(3 * nf0 + k) >= attrib.normals.size() ||
                                        size_t(3 * nf1 + k) >= attrib.normals.size() ||
                                        size_t(3 * nf2 + k) >= attrib.normals.size()) {
                                            static int first=1;
                                            if (first==1)
                                            {
                                                first=0;
                                                if (!burn && F2==1) printf("Invalid_normal_index\n");
                                            }
                                            invalid_normal_index = true;
                                            n[0][0] = 0;  n[0][1] = 0;  n[0][2] = 0;
                                            n[1][0] = 0;  n[1][1] = 0;  n[1][2] = 0;
                                            n[2][0] = 0;  n[2][1] = 0;  n[2][2] = 0;
                                    } else {
                                        n[0][k] = attrib.normals[3 * nf0 + k];
                                        n[1][k] = attrib.normals[3 * nf1 + k];
                                        n[2][k] = attrib.normals[3 * nf2 + k];
                                    }
                                }
                            }
                        }
                        else
                        {
                            invalid_normal_index = true;
                            static int first=1;
                            if (first==1)
                            {
                                first=0;
                                if (!burn && F2==1) printf("Invalid_normal_index\n");
                            }
                        }

                        if (invalid_normal_index && !smoothVertexNormals.empty())
                        {
                            int f0 = idx0.vertex_index;  int f1 = idx1.vertex_index;  int f2 = idx2.vertex_index;

                            if (f0 >= 0 && f1 >= 0 && f2 >= 0)
                            {
                                n[0][0] = smoothVertexNormals[f0].v[0];  n[0][1] = smoothVertexNormals[f0].v[1];  n[0][2] = smoothVertexNormals[f0].v[2];
                                n[1][0] = smoothVertexNormals[f1].v[0];  n[1][1] = smoothVertexNormals[f1].v[1];  n[1][2] = smoothVertexNormals[f1].v[2];
                                n[2][0] = smoothVertexNormals[f2].v[0];  n[2][1] = smoothVertexNormals[f2].v[1];  n[2][2] = smoothVertexNormals[f2].v[2];
                                invalid_normal_index = false;
                            }
                        }

                        if (invalid_normal_index)
                        {
                            // compute geometric normal
                            CalcNormal(n[0], v[0], v[1], v[2]);
                            n[1][0] = n[0][0];  n[1][1] = n[0][1];  n[1][2] = n[0][2];
                            n[2][0] = n[0][0];  n[2][1] = n[0][1];  n[2][2] = n[0][2];
                        }
                    }

                    for (int k = 0; k < 3; k++)
                    {
                        buffer.push_back(v[k][0]);  buffer.push_back(v[k][1]);  buffer.push_back(v[k][2]);
                        buffer.push_back(n[k][0]);  buffer.push_back(n[k][1]);  buffer.push_back(n[k][2]);
    //color out

                        // Combine normal and diffuse to get color.
                        float normal_factor = 0.2;
                        float diffuse_factor = 1 - normal_factor;
                        float c[3] = {n[k][0] * normal_factor + diffuse[0] * diffuse_factor,
                                      n[k][1] * normal_factor + diffuse[1] * diffuse_factor,
                                      n[k][2] * normal_factor + diffuse[2] * diffuse_factor
                                     };
                        float len2 = c[0] * c[0] + c[1] * c[1] + c[2] * c[2];
                        if (len2 > 0.0f)
                        {
                            float len = sqrtf(len2);

                            c[0] /= len;
                            c[1] /= len;
                            c[2] /= len;
                        }
                        buffer.push_back(c[0] * 0.5 + 0.5);
                        buffer.push_back(c[1] * 0.5 + 0.5);
                        buffer.push_back(c[2] * 0.5 + 0.5);

    /*
                        float avg=(n[k][0]+n[k][1]+n[k][2])/3.0;
                        float c2[3] = { avg * normal_factor + diffuse[0] * diffuse_factor,
                                        avg * normal_factor + diffuse[1] * diffuse_factor,
                                        avg * normal_factor + diffuse[2] * diffuse_factor
                                     };

                        len2 = c2[0] * c2[0] + c2[1] * c2[1] + c2[2] * c2[2];
                        if (len2 > 0.0f)
                        {
                            float len = sqrtf(len2);

                            c2[0] /= len;
                            c2[1] /= len;
                            c2[2] /= len;
                        }
    */
    //                    buffer.push_back(c2[0] * 0.5 + 0.5);
    //                    buffer.push_back(c2[1] * 0.5 + 0.5);
    //                    buffer.push_back(c2[2] * 0.5 + 0.5);


                        buffer.push_back(tc[k][0]);  buffer.push_back(tc[k][1]);
                    }

/*
                    printf("V:(%-+10.3f,%-+10.3f,%-+10.3f) - (%-+10.3f,%-+10.3f,%-+10.3f) (%-+10.3f,%-+10.3f,%-+10.3f)  T:(%-+10.3f,%-+10.3f,%-+10.3f) - (%-+10.3f,%-+10.3f,%-+10.3f) (%-+10.3f,%-+10.3f,%-+10.3f)\n",
                        v[0][0],v[0][1],v[0][2] , v[1][0],v[1][1],v[1][2]   , v[2][0],v[2][1],v[2][2],
                        tc[0][0],tc[0][1],0.0   , tc[1][0],tc[1][1],0.0     , tc[2][0],tc[2][1],0.0);
*/



                    tot_indices++;
                    //if ((!((int)f&0xfff) && (f>0)) || f==(int)shape_size-1 ) printf("\rLoading shape %5d(%d) Total indices: %d       \r",(int)s,(int)shapes.size(),tot_indices);
                }
    //            if ((!((int)f&0xff) && (f>0)) || f==(int)shape_size-1 ) printf("\rLoading shape %d(%d) Indice: %d(%d)       \r",(int)s,(int)shapes.size(),(int)f,(int)shape_size);
                o.vb_id = 0;
                o.numTriangles = 0;

                if (shapes[s].mesh.material_ids.size() > 0 )
                    o.material_id = shapes[s].mesh.material_ids[0];  // use the material ID
                else
                    o.material_id = materials.size() - 1;  // = ID for default material.

                if (buffer.size() > 0)
                {
                    if (to_gpu) {
                        glGenBuffers(1, &o.vb_id);
                        glBindBuffer(GL_ARRAY_BUFFER, o.vb_id);
                        glBufferData(GL_ARRAY_BUFFER, buffer.size() * sizeof(float),  &buffer.at(0), GL_STATIC_DRAW);
                    }
                    o.numTriangles = buffer.size() / (3 + 3 + 3 + 2) / 3;     // 3:vtx, 3:normal, 3:col, 2:texcoord
    //                printf(" shape[%d] # of triangles = %d", static_cast<int>(s), o.numTriangles);
                    drawObjects.push_back(o);
                    one_buffer.buffer=(int8_t*)malloc(sizeof(int)+buffer.size()*sizeof(float));
                    int mat_id=o.material_id;
                    memcpy(one_buffer.buffer,&mat_id,sizeof(int));
                    memcpy(one_buffer.buffer+sizeof(int),&buffer.at(0),buffer.size()*sizeof(float));
                    one_buffer.length=sizeof(int)+buffer.size()*sizeof(float);
                    buffers.push_back(one_buffer);
        //            printf("Saved #%d -> %u bytes\n",s,one_buffer.length);
                }

            }
        } else {
            for (auto u : buffers) {
                DrawObject o;
                float* buffer=(float*)(u.buffer+sizeof(int));  // one int for mat_id
                size_t length=u.length - sizeof(int);
                o.numTriangles = (length) / (3 + 3 + 3 + 2) / 3;
                memcpy(&o.material_id,u.buffer,sizeof(int));
                if (to_gpu) {
                    o.vb_id = 0;
                    glGenBuffers(1, &o.vb_id);
                    glBindBuffer(GL_ARRAY_BUFFER, o.vb_id);
                    glBufferData(GL_ARRAY_BUFFER, length, buffer, GL_STATIC_DRAW);
                }
                drawObjects.push_back(o);
            }
        }

        if (!burn && F2==1 && to_gpu) printf("total time loading shapes to GPU: %d milliseconds\n",clock.getElapsedTime().asMilliseconds()-time.asMilliseconds());
        if ((!burn && F2==1) || automate) {
            if (to_gpu) printf("total time batch thread loading from disk and loading textures to GPU: %d milliseconds\n",clock.getElapsedTime().asMilliseconds()-time_total.asMilliseconds());
            else printf("total time batch thread loading from disk: %d milliseconds\n",clock.getElapsedTime().asMilliseconds()-time_total.asMilliseconds());
            printf("OBJECT MIN: X=%24.17f Y=%24.17f Z=%24.17f\n",bmin[0],bmin[1],bmin[2]);
            printf("OBJECT MAX: X=%24.17f Y=%24.17f Z=%24.17f\n",bmax[0],bmax[1],bmax[2]);
            printf("OBJECT DIF: X=%24.17f Y=%24.17f Z=%24.17f\n",bmax[0]-bmin[0],bmax[1]-bmin[1],bmax[2]-bmin[2]);
        }

        if (!NBT_LOADED) {
            printf(" Saving to .nbt");
            OBJECT3D_TO_NBT(buffers, materials, filename, bmin, bmax);
            RECALC_BMIN_BMAX2(buffers, bmin, bmax, lat, lon);
        }
        if (do_wuppie) {
            std::string fn = filename;
            fn=GetFileName(fn.substr(0,fn.find_last_of(".")));
            if (mirror==4) {
                if (area=="Models" && rot_plot) {
                    double schem=schematic_size;

                    RECALC_BMIN_BMAX3(buffers, bmin,bmax, 0.0,0.0);

                    std::vector<BufferObject> saved_buffers;
                    for (int n=0; n<buffers.size(); n++) {
                        BufferObject one;
                        one.length=buffers[n].length;
                        one.buffer=(int8_t*)malloc(one.length);
                        memcpy(one.buffer,buffers[n].buffer,one.length);
                        saved_buffers.push_back(one);
                    }
                    int play_num=-1;
                    g_rotate_object_x=0.0; g_rotate_object_y=0.0; g_rotate_object_z=0.0;
                    bool playing_3d=true;
                    float bmin_zero[3];
                    float bmax_zero[3];
                    printf("\n");
extern int ESCAPE_PRESSED;
                    voxel_bottom=0.0;
                    play(play_num, bmin_zero, bmax_zero);
                    while (playing_3d && ESCAPE_PRESSED==0) {
                        if (play_num==0) {
                            for (int n=0; n<3; n++) {
                                bmin_zero[n]=bmin[n];
                                bmax_zero[n]=bmax[n];
                            }
                            g_rotate_object_x=0.0; g_rotate_object_y=0.0; g_rotate_object_z=0.0;
                        }
                        playing_3d=play(play_num, bmin_zero, bmax_zero);
                        if (!playing_3d) continue;
                        if (play_num==0) { //next loop, flush...voxels to voxels total
                            printf("=> Next loop, getting size, flushing voxels...\n");
                            printf("=> Voxels=%10d  Total voxels=%10d Compressing to total, holding voxels:\n",voxels.size(),voxels_total.size());
                            flush_voxels();
                            printf("=> Voxels=%10d  Total voxels=%10d Compressed to total, deleting voxels:\n",voxels.size(),voxels_total.size());
                            voxels.clear();
                            playing_3d=play(play_num, bmin_zero, bmax_zero); // first 2nd loop, set settings....
//                            play_num++;
                        }
//                        play_num++;

                        RECALC_BMIN_BMAX4(buffers, bmin,bmax, 0.0,0.0);

                        if (play_num>0) {
                            WUPPIE_VECTOR(buffers, materials, bmin, bmax, lat, lon, fn);
                            if (play_num==1) voxels.clear();  //testing default size when not rotated....
                            for (int n=0; n<3; n++) {
                                bmin_zero[n]=bmin[n];
                                bmax_zero[n]=bmax[n];
                            }

                            printf("=> Voxels=%10d  Total voxels=%10d\n",voxels.size(), voxels_total.size());
                            mazemovex_voxel=0;
                            mazemovey_voxel=0;

/*
                            if (!playing_3d || (playing_3d && voxels.size() > 20000000)) {
                                printf("=> Voxels=%10d  Total voxels=%10d Compressing to total, holding voxels:\n",voxels.size(),voxels_total.size());
                                flush_voxels();
                                printf("=> Voxels=%10d  Total voxels=%10d Compressed to total, deleting voxels:\n",voxels.size(),voxels_total.size());
                                voxels.clear();
                            }
*/
                            if ((play_num==1 && voxels_total.size()>0) || voxels_total.size() > 40000000 || voxels.size() > 40000000) {
//                            if ((play_num==1 && voxels_total.size()>0) || voxels_total.size() > 40000000) {
                                dont_clear=true;
                                printf("=> Voxels=%10d  Total voxels=%10d Clearing all voxels from memory: Flushing all voxels to region voxel files (adding to existing)\n",voxels.size(),voxels_total.size());
                                flush_voxels_to_region_voxel_files();
                                printf("=> Voxels=%10d  Total voxels=%10d Flushed, clearing all voxels\n",voxels.size(),voxels_total.size());
                                voxels.clear();
                                voxels_total.clear();
                                dont_clear=false;
                            }

                        }
                        if (playing_3d) {
                            for (int n=0; n<buffers.size(); n++) {
                                memcpy(buffers[n].buffer,saved_buffers[n].buffer,buffers[n].length);
                            }
                        }
                    }
/*
                    for (int n=0; n<100; n++) {
                        mazemovex_voxel=smooth_x+(rand()%128-64)*3;
                        mazemovey_voxel=smooth_y+(rand()%152-76)*3;

                        WUPPIE_VECTOR(buffers, materials, bmin, bmax, lat, lon, fn);

                        mazemovex_voxel=0;
                        mazemovey_voxel=0;

                        for (int n=0; n<buffers.size(); n++) {
                            memcpy(buffers[n].buffer,saved_buffers[n].buffer,buffers[n].length);
                        }

                        g_rotate_object_z=rand()%50-25;
                        g_rotate_object_y=rand()%50-25;
                        g_rotate_object_x=rand()%350-180;

                        schematic_size=6000.0/(eye22*10.0);
                        schematic_size=schematic_size*(0.5+0.35*sin((g_rotate_object_x+g_rotate_object_y+g_rotate_object_z)/360.0));
                        RECALC_BMIN_BMAX4(buffers, bmin,bmax, 0.0,0.0);
                    }
*/
                    voxel_bottom=0.0;

                    for (auto u : saved_buffers) {
                        free(u.buffer);
                    }
//                    for (int n=0; n<saved_buffers.size(); n++) {
//                        free(saved_buffers[n].buffer);
//                    }
                    saved_buffers.clear();

                    if (voxels_total.size() > 0 || voxels.size() > 0) {
                        dont_clear=true;
                        printf("=> Voxels=%10d  Total voxels=%10d Clearing all voxels from memory: Flushing all voxels to region voxel files (adding to existing)\n",voxels.size(),voxels_total.size());
//                        skip_sorting=false;
                        flush_voxels_to_region_voxel_files();
                        printf("=> Voxels=%10d  Total voxels=%10d Flushed, clearing all voxels\n",voxels.size(),voxels_total.size());
                        voxels.clear();
                        voxels_total.clear();
                        dont_clear=false;
                    }
                    dont_clear=false;
                    rot_plot=false;
                } else {
                    if (area=="Models") RECALC_BMIN_BMAX3(buffers, bmin,bmax, 0.0,0.0);
                    WUPPIE_SUBS(buffers, materials, bmin, bmax, lat, lon, fn);
                }
            } else {
                printf("loadandconvert: lat=%lf lon=%lf\n",lat,lon);
                WUPPIE_VECTOR(buffers, materials, bmin, bmax, lat, lon, fn);
            }

            do_wuppie=false;
        }
        for (auto u : buffers) {
            free(u.buffer);
        }
    }
    clear_image_buffer();

    return true;
}

extern nbt_tag_t* read_nbt_file(const char* name, int flags);

void OBJECT3D_TO_NBT(std::vector<BufferObject> &buffers, std::vector<tinyobj::material_t> &materials, char* filename, float bmin[3], float bmax[3]) {

    std::string nbt_filename=filename;
    if (nbt_filename.find_last_of(".") != std::string::npos) nbt_filename=nbt_filename.substr(0,nbt_filename.find_last_of("."))+".nbt";

    nbt_tag_t* tag_object;
    tag_object = nbt_new_tag_compound();
    nbt_set_tag_name(tag_object,filename,strlen(filename));

    nbt_tag_t* tag_materials = nbt_new_tag_list(NBT_TYPE_STRING);
    nbt_set_tag_name(tag_materials,(char*)"materials",strlen("materials"));
    nbt_tag_compound_append(tag_object,tag_materials);

    char material_name[200];
    nbt_tag_t* tag_material;
    for (auto p : materials) {
        strcpy(material_name,p.diffuse_texname.c_str());
        tag_material = nbt_new_tag_string(material_name,strlen(material_name));
        nbt_tag_list_append(tag_materials,tag_material);
    }

    nbt_tag_t* tag_buffers = nbt_new_tag_list(NBT_TYPE_BYTE_ARRAY);
    nbt_set_tag_name(tag_buffers,(char*)"buffers",strlen("buffers"));
    nbt_tag_compound_append(tag_object,tag_buffers);

    nbt_tag_t* tag_buffer;
    for (auto p : buffers) {
        tag_buffer = nbt_new_tag_byte_array(p.buffer,p.length);
        nbt_tag_list_append(tag_buffers,tag_buffer);
    }
    nbt_tag_t* tag_bminmax;
    tag_bminmax=nbt_new_tag_float(bmin[0]);
    nbt_set_tag_name(tag_bminmax,(char*)"bmin[0]",strlen("bmin[0]"));
    nbt_tag_compound_append(tag_object,tag_bminmax);
    tag_bminmax=nbt_new_tag_float(bmin[1]);
    nbt_set_tag_name(tag_bminmax,(char*)"bmin[1]",strlen("bmin[1]"));
    nbt_tag_compound_append(tag_object,tag_bminmax);
    tag_bminmax=nbt_new_tag_float(bmin[2]);
    nbt_set_tag_name(tag_bminmax,(char*)"bmin[2]",strlen("bmin[2]"));
    nbt_tag_compound_append(tag_object,tag_bminmax);
    tag_bminmax=nbt_new_tag_float(bmax[0]);
    nbt_set_tag_name(tag_bminmax,(char*)"bmax[0]",strlen("bmax[0]"));
    nbt_tag_compound_append(tag_object,tag_bminmax);
    tag_bminmax=nbt_new_tag_float(bmax[1]);
    nbt_set_tag_name(tag_bminmax,(char*)"bmax[1]",strlen("bmax[1]"));
    nbt_tag_compound_append(tag_object,tag_bminmax);
    tag_bminmax=nbt_new_tag_float(bmax[2]);
    nbt_set_tag_name(tag_bminmax,(char*)"bmax[2]",strlen("bmax[2]"));
    nbt_tag_compound_append(tag_object,tag_bminmax);


    if (!burn) {
        printf("\rSaving to file %s\n",nbt_filename.c_str());
    } else {
        printf("\rSaving to file %s\n",nbt_filename.c_str());
    }
    write_nbt_file(nbt_filename.c_str(), tag_object, NBT_WRITE_FLAG_USE_GZIP);

    nbt_free_tag(tag_object);
}

void NBT_TO_OBJECT3D(std::vector<BufferObject> &buffers, std::vector<tinyobj::material_t> &materials, char* filename, float bmin[3], float bmax[3]) {

    std::string nbt_filename=filename;
    if (nbt_filename.find_last_of(".") != std::string::npos) nbt_filename=nbt_filename.substr(0,nbt_filename.find_last_of("."))+".nbt";

    nbt_tag_t* tag_object;
    nbt_tag_t* tag_material;
    nbt_tag_t* tag_materials;
    char material_name[200];
    nbt_tag_t* tag_buffer;
    nbt_tag_t* tag_buffers;
    nbt_tag_t* tag_bminmax;

    sf::Clock clock;
    sf::Time time;

    time=clock.getElapsedTime();
    tag_object = read_nbt_file(nbt_filename.c_str(), NBT_PARSE_FLAG_USE_GZIP);

    tag_buffers = tag_object->tag_compound.value[1];
    BufferObject one_buffer;
    std::vector<int> buffer_material;

    int mat_id;
    tag_materials = tag_object->tag_compound.value[0];

//    double lat=(lat_north+lat_south)/2.0;
//    double lon=(lon_east+lon_west)/2.0;

//    glm::vec3 NORMALz;
//    glm::mat4 test(1.0f);

    tag_bminmax = tag_object->tag_compound.value[2];    bmin[0]=tag_bminmax->tag_float.value;
    tag_bminmax = tag_object->tag_compound.value[3];    bmin[1]=tag_bminmax->tag_float.value;
    tag_bminmax = tag_object->tag_compound.value[4];    bmin[2]=tag_bminmax->tag_float.value;
    tag_bminmax = tag_object->tag_compound.value[5];    bmax[0]=tag_bminmax->tag_float.value;
    tag_bminmax = tag_object->tag_compound.value[6];    bmax[1]=tag_bminmax->tag_float.value;
    tag_bminmax = tag_object->tag_compound.value[7];    bmax[2]=tag_bminmax->tag_float.value;

/*
    float tx;
    float ty;
    float tz;
    if (lat_north!=0.0 || lat_south!=0.0 || lon_west!=0.0 || lon_east!=0.0) {
        printf("(original)\n");
        printf("bmin = % 24.13f, % 24.13f, % 24.13f\n", bmin[0],           bmin[1],            bmin[2]);
        printf("bmax = % 24.13f, % 24.13f, % 24.13f\n", bmax[0],           bmax[1],            bmax[2]);
        printf("diff = % 24.13f, % 24.13f, % 24.13f\n", bmax[0]-bmin[0],   bmax[1]-bmin[1],    bmax[2]-bmin[2]);

        tx=-0.5 * (bmax[0] + bmin[0]);
        ty=-0.5 * (bmax[1] + bmin[1]);
        tz=-0.5 * (bmax[2] + bmin[2]);

        printf("lat=%lf  lon=%lf\n",lat,lon);
        bmin[0] = bmin[1] = bmin[2] = std::numeric_limits<float>::max();
        bmax[0] = bmax[1] = bmax[2] = -std::numeric_limits<float>::max();
        NORMALz = glm::vec3((float)(cos(lat*M_PI/180.0)*cos(lon*M_PI/180.0)), (float)(cos(lat*M_PI/180)*sin(lon*M_PI/180)), (float)(sin(lat*M_PI/180)));
        NORMALz = glm::normalize(NORMALz);

        test = glm::eulerAngleYXZ(  (float)((lat)*M_PI/180.0) ,(float)((lon)*M_PI/180.0) , (float)(0.0));
        test = glm::rotate(test, float(-90.0*M_PI/180.0), glm::vec3(0.0,1.0,0.0)) ;
        test = glm::rotate(test, float(-90.0*M_PI/180.0), {NORMALz.x,NORMALz.y,NORMALz.z} ) ;
    }
*/
    for (size_t i = 0; i < tag_buffers->tag_list.size; i++) {
        tag_buffer=tag_buffers->tag_list.value[i];

//select
        memcpy(&mat_id, tag_buffer->tag_byte_array.value, sizeof(int));
        if (mat_id < tag_materials->tag_list.size) {
            tag_material=tag_materials->tag_list.value[mat_id];
//            if (tag_material->tag_string.size != 31 && !(tag_material->tag_string.size==0)) {
//                printf("Skipping buffer(=%d) / material %d(=%s)\n",i,mat_id,tag_material->tag_string.value);
//                continue;
//            }
        } else {
            printf("mat_id(=%d) >= tag_materials->tag_list.size(=%d)\n",mat_id,tag_materials->tag_list.size);
        }

        one_buffer.buffer=(int8_t*)malloc(tag_buffer->tag_byte_array.size);
        memcpy(one_buffer.buffer, tag_buffer->tag_byte_array.value, tag_buffer->tag_byte_array.size);
        one_buffer.length=tag_buffer->tag_byte_array.size;
        buffers.push_back(one_buffer);

        memcpy(&mat_id,one_buffer.buffer,sizeof(int));

        bool found=false;
//hopla
//        if (area!="Models") {
            for (auto u : buffer_material) {
                if (u==mat_id) {
                    found=true;
                    break;
                }
            }
//        }
        if (!found) buffer_material.push_back(mat_id);

/*

        if (lat_north!=0.0 || lat_south!=0.0 || lon_west!=0.0 || lon_east!=0.0) {

            int num_faces=(one_buffer.length-sizeof(int)) / (3 + 3 + 3 + 2) / 3 / sizeof(float);     // 3:vtx, 3:normal, 3:col, 2:texcoord
            float v[3][3];
    //        float n[3][3];
    //        float c[3][3];
    //        float tc[3][2];
            int stride = (3 + 3 + 2 + 3);
            float* real_buffer = (float*)(one_buffer.buffer + sizeof(int));
            float* VertexPointer=real_buffer;
    //        float* NormalPointer=real_buffer + sizeof(float)*3;
    //        float* ColorPointer=real_buffer + sizeof(float)*6;
    //        float* TexCoordPointer=real_buffer + sizeof(float)*9;


            for (int faces=0; faces<num_faces; faces++) {
                for (int l=0; l<3; l++) {
                    int offset=(stride*(l+faces*3));
                    for (int k=0; k<3; k++) {
                        if (offset*sizeof(float) >= one_buffer.length-sizeof(int)) {
                            printf("Error offset\n");
                            return;
                        }
                        v[l][k]=VertexPointer[offset+k];
    //                    n[l][k]=NormalPointer[offset];
    //                    c[l][k]=ColorPointer[offset];
    //                    if (k<2) tc[l][k]=TexCoordPointer[offset];
                    }
                    glm::vec4 hop = glm::vec4(v[l][0]+tx, v[l][1]+ty, v[l][2]+tz, 1.0f) * test;
                    hop = hop - glm::vec4(tx,ty,tz,0.0f);
                    bmin[0]=std::min(hop.x, bmin[0]);   bmax[0]=std::max(hop.x, bmax[0]);
                    bmin[1]=std::min(hop.y, bmin[1]);   bmax[1]=std::max(hop.y, bmax[1]);
                    bmin[2]=std::min(hop.z, bmin[2]);   bmax[2]=std::max(hop.z, bmax[2]);
//                    printf("Buffer: %3d/%3d  Face: %5d/%5d  ",i+1, tag_buffers->tag_list.size, faces+1,num_faces);
//                    printf("Offset: %7d/%7d  Vertice: %d %-+9.3f %-+9.3f %-+9.3f  ==>  %-+9.3f %-+9.3f %-+9.3f  bmin=%-+9.3f %-+9.3f %-+9.3f  bmax=%-+9.3f %-+9.3f %-+9.3f\n",
//                            offset*sizeof(float),one_buffer.length,l,v[l][0],v[l][1],v[l][2],hop.x,hop.y,hop.z,
//                            bmin[0],bmin[1],bmin[2],bmax[0],bmax[1],bmax[2]);
                }
            }
//            printf("Buffer: %3d/%3d  Faces: %5d  bmin=%-+9.3f %-+9.3f %-+9.3f  bmax=%-+9.3f %-+9.3f %-+9.3f\n",
//                   i+1, tag_buffers->tag_list.size, num_faces, bmin[0],bmin[1],bmin[2],bmax[0],bmax[1],bmax[2]);

        }
*/
    }
//    tag_materials = tag_object->tag_compound.value[0];
//hopla
    tinyobj::material_t material;
    for (size_t i = 0; i < tag_materials->tag_list.size; i++) {
        bool found=false;
//        if (area!="Models") {
            for (auto u : buffer_material) {
                if (u == (int)i) {
                    found=true;
                    break;
                }
            }
//        }
        if (found) {
            tag_material=tag_materials->tag_list.value[i];
            strcpy(material_name,tag_material->tag_string.value);
            tinyobj::InitMaterial(&material);
            material.diffuse_texname=material_name;
            for (auto p : buffers) {
                memcpy(&mat_id,p.buffer,sizeof(int));
                if (mat_id==i) {
                    mat_id=(int)materials.size();
                    memcpy(p.buffer, &mat_id , sizeof(int));
                }
            }
            materials.push_back(material);
        }
    }
    materials.push_back(tinyobj::material_t());

//    if (lat_north!=0.0 || lat_south!=0.0 || lon_west!=0.0 || lon_east!=0.0) {
//        tag_object->tag_compound.value[2]->tag_float.value=bmin[0];
//        tag_object->tag_compound.value[3]->tag_float.value=bmin[1];
//        tag_object->tag_compound.value[4]->tag_float.value=bmin[2];
//        tag_object->tag_compound.value[5]->tag_float.value=bmax[0];
//        tag_object->tag_compound.value[6]->tag_float.value=bmax[1];
//        tag_object->tag_compound.value[7]->tag_float.value=bmax[2];
//    } else {
/*
        printf("(calculated)\n");
        printf("bmin = % 24.13f, % 24.13f, % 24.13f\n", bmin[0],           bmin[1],            bmin[2]);
        printf("bmax = % 24.13f, % 24.13f, % 24.13f\n", bmax[0],           bmax[1],            bmax[2]);
        printf("diff = % 24.13f, % 24.13f, % 24.13f\n", bmax[0]-bmin[0],   bmax[1]-bmin[1],    bmax[2]-bmin[2]);
*/

//    }

    nbt_free_tag(tag_object);
}

/*
void RECALC_BMIN_BMAX(std::vector<BufferObject> buffers, float bmin[3], float bmax[3], double lat, double lon) {

//    float curr_quat2[4];
//    trackball(curr_quat2, 0, 0, 0, 0);
//    glm::mat4 rot_matrix2(1.0f);
//    build_rotmatrix_glm(rot_matrix2, curr_quat2);

    BufferObject one_buffer;

    glm::vec3 NORMALz;
    glm::mat4 test(1.0f);

    float tx;
    float ty;
    float tz;


//    printf("(original)\n");
//    printf("bmin = % 24.13f, % 24.13f, % 24.13f\n", bmin[0],           bmin[1],            bmin[2]);
//    printf("bmax = % 24.13f, % 24.13f, % 24.13f\n", bmax[0],           bmax[1],            bmax[2]);
//    printf("diff = % 24.13f, % 24.13f, % 24.13f\n", bmax[0]-bmin[0],   bmax[1]-bmin[1],    bmax[2]-bmin[2]);

    tx=-0.5 * (bmax[0] + bmin[0]);
    ty=-0.5 * (bmax[1] + bmin[1]);
    tz=-0.5 * (bmax[2] + bmin[2]);

//    printf("lat=%lf  lon=%lf\n",lat,lon);
    bmin[0] = bmin[1] = bmin[2] = std::numeric_limits<float>::max();
    bmax[0] = bmax[1] = bmax[2] = -std::numeric_limits<float>::max();
    NORMALz = glm::vec3((float)(cos(lat*M_PI/180.0)*cos(lon*M_PI/180.0)), (float)(cos(lat*M_PI/180)*sin(lon*M_PI/180)), (float)(sin(lat*M_PI/180)));
    NORMALz = glm::normalize(NORMALz);

    test = glm::eulerAngleYXZ(  (float)((lat)*M_PI/180.0) ,(float)((lon)*M_PI/180.0) , (float)(0.0));
    test = glm::rotate(test, float(-90.0*M_PI/180.0), glm::vec3(0.0,1.0,0.0)) ;
    test = glm::rotate(test, float(-90.0*M_PI/180.0), {NORMALz.x,NORMALz.y,NORMALz.z} ) ;

//    test = rot_matrix2 * test;
//    test=glm::inverse(test);

    for (auto u : buffers) {
        one_buffer=u;

        int num_faces=(one_buffer.length-sizeof(int)) / (3 + 3 + 3 + 2) / 3 / sizeof(float);     // 3:vtx, 3:normal, 3:col, 2:texcoord
        float v[3][3];
//        float n[3][3];
//        float c[3][3];
//        float tc[3][2];
        int stride = (3 + 3 + 2 + 3);
        float* real_buffer = (float*)(one_buffer.buffer + sizeof(int));
        float* VertexPointer=real_buffer;
//        float* NormalPointer=real_buffer + sizeof(float)*3;
//        float* ColorPointer=real_buffer + sizeof(float)*6;
//        float* TexCoordPointer=real_buffer + sizeof(float)*9;


        for (int faces=0; faces<num_faces; faces++) {
            for (int l=0; l<3; l++) {
                int offset=(stride*(l+faces*3));
                for (int k=0; k<3; k++) {
                    if (offset*sizeof(float) >= one_buffer.length-sizeof(int)) {
                        printf("Error offset\n");
                        return;
                    }
                    v[l][k]=VertexPointer[offset+k];
//                    n[l][k]=NormalPointer[offset];
//                    c[l][k]=ColorPointer[offset];
//                    if (k<2) tc[l][k]=TexCoordPointer[offset];
                }
//                glm::vec4 hop = glm::vec4(v[l][0], v[l][1], v[l][2], 1.0f) * test;
//normal...
//                glm::vec4 hop = glm::vec4(v[l][0], v[l][1], v[l][2], 1.0f);

                glm::vec4 hop = glm::vec4(v[l][0]+tx, v[l][1]+ty, v[l][2]+tz, 1.0f) * test;
                hop = hop - glm::vec4(tx,ty,tz,0.0f);
                bmin[0]=std::min(hop.x, bmin[0]);   bmax[0]=std::max(hop.x, bmax[0]);
                bmin[1]=std::min(hop.y, bmin[1]);   bmax[1]=std::max(hop.y, bmax[1]);
                bmin[2]=std::min(hop.z, bmin[2]);   bmax[2]=std::max(hop.z, bmax[2]);
//                    printf("Buffer: %3d/%3d  Face: %5d/%5d  ",i+1, tag_buffers->tag_list.size, faces+1,num_faces);
//                    printf("Offset: %7d/%7d  Vertice: %d %-+9.3f %-+9.3f %-+9.3f  ==>  %-+9.3f %-+9.3f %-+9.3f  bmin=%-+9.3f %-+9.3f %-+9.3f  bmax=%-+9.3f %-+9.3f %-+9.3f\n",
//                            offset*sizeof(float),one_buffer.length,l,v[l][0],v[l][1],v[l][2],hop.x,hop.y,hop.z,
//                            bmin[0],bmin[1],bmin[2],bmax[0],bmax[1],bmax[2]);
            }
        }
//            printf("Buffer: %3d/%3d  Faces: %5d  bmin=%-+9.3f %-+9.3f %-+9.3f  bmax=%-+9.3f %-+9.3f %-+9.3f\n",
//                   i+1, tag_buffers->tag_list.size, num_faces, bmin[0],bmin[1],bmin[2],bmax[0],bmax[1],bmax[2]);
    }


//    printf("(calculated)\n");
//    printf("bmin = % 24.13f, % 24.13f, % 24.13f\n", bmin[0],           bmin[1],            bmin[2]);
//    printf("bmax = % 24.13f, % 24.13f, % 24.13f\n", bmax[0],           bmax[1],            bmax[2]);
//    printf("diff = % 24.13f, % 24.13f, % 24.13f\n", bmax[0]-bmin[0],   bmax[1]-bmin[1],    bmax[2]-bmin[2]);

}
*/

/*
void ROTJE(glm::vec3 &torot, float bmin[3], float bmax[3], double lat, double lon) {
    glm::vec3 NORMALz;
    glm::mat4 test(1.0f);

    float tx;
    float ty;
    float tz;

    tx=-0.5 * (bmax[0] + bmin[0]);
    ty=-0.5 * (bmax[1] + bmin[1]);
    tz=-0.5 * (bmax[2] + bmin[2]);

    NORMALz = glm::vec3((float)(cos(lat*M_PI/180.0)*cos(lon*M_PI/180.0)), (float)(cos(lat*M_PI/180)*sin(lon*M_PI/180)), (float)(sin(lat*M_PI/180)));
    NORMALz = glm::normalize(NORMALz);

    test = glm::eulerAngleYXZ(  (float)((lat)*M_PI/180.0) ,(float)((lon)*M_PI/180.0) , (float)(0.0));
//    test = glm::rotate(test, float(-90.0*M_PI/180.0), glm::vec3(0.0,1.0,0.0)) ;
//    test = glm::rotate(test, float(-90.0*M_PI/180.0), {NORMALz.x,NORMALz.y,NORMALz.z} ) ;
//    test = glm::inverse(test);

    glm::vec4 hop = glm::vec4(torot.x+tx, torot.y+ty, torot.z+tz, 1.0f) * test;
    hop = hop - glm::vec4(tx,ty,tz,0.0f);
    torot=glm::vec3(hop.x,hop.y,hop.z);
}
*/


void CANVAS_OBJECT3D(std::vector<BufferObject> &buffers, std::vector<tinyobj::material_t> &materials, char* filename, float bmin[3], float bmax[3], int picturex, int picturey) {
    std::vector<float> buffer;

//    buffer.push_back(0.0);
    for (int y=0; y<15; y++) {
        for (int x=0; x<30; x++) {
            int offset_x=64*x+1920*picturex;
            int offset_y=72*y+1080*picturey;
            int offset_z=0;
            int text_offset_x=64*x;
            int text_offset_y=72*y;

            buffer.push_back((float)offset_x);                      buffer.push_back((float)offset_y);          buffer.push_back((float)offset_z);
            buffer.push_back((float)0.0);                           buffer.push_back((float)0.0);               buffer.push_back((float)0.0);
            buffer.push_back((float)0.0);                           buffer.push_back((float)0.0);               buffer.push_back((float)0.0);
            buffer.push_back((float)(text_offset_x)/1920.0);        buffer.push_back((float)(text_offset_y)/1080.0);

            buffer.push_back((float)offset_x+64);                   buffer.push_back((float)offset_y+72);                   buffer.push_back((float)offset_z);
            buffer.push_back((float)0.0);                           buffer.push_back((float)0.0);                           buffer.push_back((float)0.0);
            buffer.push_back((float)0.0);                           buffer.push_back((float)0.0);                           buffer.push_back((float)0.0);
            buffer.push_back((float)(text_offset_x+64)/1920.0);     buffer.push_back((float)(text_offset_y+72)/1080.0);

            buffer.push_back((float)offset_x+64);                   buffer.push_back((float)offset_y);                      buffer.push_back((float)offset_z);
            buffer.push_back((float)0.0);                           buffer.push_back((float)0.0);                           buffer.push_back((float)0.0);
            buffer.push_back((float)0.0);                           buffer.push_back((float)0.0);                           buffer.push_back((float)0.0);
            buffer.push_back((float)(text_offset_x+64)/1920.0);     buffer.push_back((float)(text_offset_y)/1080.0);

            buffer.push_back((float)offset_x);                      buffer.push_back((float)offset_y);                      buffer.push_back((float)offset_z);
            buffer.push_back((float)0.0);                           buffer.push_back((float)0.0);                           buffer.push_back((float)0.0);
            buffer.push_back((float)0.0);                           buffer.push_back((float)0.0);                           buffer.push_back((float)0.0);
            buffer.push_back((float)(text_offset_x)/1920.0);        buffer.push_back((float)(text_offset_y)/1080.0);

            buffer.push_back((float)offset_x);                      buffer.push_back((float)offset_y+72);                   buffer.push_back((float)offset_z);
            buffer.push_back((float)0.0);                           buffer.push_back((float)0.0);                           buffer.push_back((float)0.0);
            buffer.push_back((float)0.0);                           buffer.push_back((float)0.0);                           buffer.push_back((float)0.0);
            buffer.push_back((float)(text_offset_x)/1920.0);        buffer.push_back((float)(text_offset_y+72)/1080.0);

            buffer.push_back((float)offset_x+64);                   buffer.push_back((float)offset_y+72);                   buffer.push_back((float)offset_z);
            buffer.push_back((float)0.0);                           buffer.push_back((float)0.0);                           buffer.push_back((float)0.0);
            buffer.push_back((float)0.0);                           buffer.push_back((float)0.0);                           buffer.push_back((float)0.0);
            buffer.push_back((float)(text_offset_x+64)/1920.0);     buffer.push_back((float)(text_offset_y+72)/1080.0);

        }
    }
    bmin[0]=picturex*1920;
    bmin[1]=picturey*1080;
    bmin[2]=0;
    bmax[0]=picturex*1920+1920;
    bmax[1]=picturey*1080+1080;
    bmax[2]=0;
    BufferObject one_buffer;
    one_buffer.buffer=(int8_t*)malloc(sizeof(int)+buffer.size()*sizeof(float));
    int mat_id=buffers.size();
    memcpy(one_buffer.buffer,&mat_id,sizeof(int));
    memcpy(one_buffer.buffer+sizeof(int),&buffer.at(0),buffer.size()*sizeof(float));
    one_buffer.length=sizeof(int)+buffer.size()*sizeof(float);
    buffers.push_back(one_buffer);

    char naam[2000];
    sprintf(naam,"picture.%06d.%06d.png",picturey,picturex);  // y then x !!!
    tinyobj::material_t material;
    tinyobj::InitMaterial(&material);
    material.diffuse_texname = naam;
    materials.push_back(material);
}

/*
    nbt_tag_t* tag_buffers_info = nbt_new_tag_compound();
    nbt_set_tag_name(tag_buffers_info,(char*)"buffers_info",strlen("buffers_info"));
    nbt_tag_compound_append(tag_object,tag_buffers_info);

    float buf_min[3];
    float buf_max[3];
    nbt_tag_t* tag_buffer_info;
    nbt_tag_t* tag_num_faces;
    int material_id=0;
    for (auto p : buffers) {
        tag_buffer_info = nbt_new_tag_compound();

        memcpy(&material_id,p.buffer,sizeof(int));
        nbt_tag_t* tag_material_id=nbt_new_tag_int(material_id);
        nbt_set_tag_name(tag_material_id,(char*)"material_id",strlen("material_id"));
        nbt_tag_compound_append(tag_buffer_info,tag_material_id);

        printf("material_id=%d ",material_id);

        strcpy(material_name,materials[material_id].diffuse_texname.c_str());
        tag_materials = nbt_new_tag_string(material_name,strlen(material_name));
        nbt_set_tag_name(tag_materials,(char*)"material",strlen("material"));
        nbt_tag_compound_append(tag_buffer_info,tag_materials);

        int num_faces=(p.length-sizeof(int)) / (3 + 3 + 3 + 2) / 3;     // 3:vtx, 3:normal, 3:col, 2:texcoord

        tag_num_faces=nbt_new_tag_int(num_faces);
        nbt_set_tag_name(tag_num_faces,(char*)"faces",strlen("faces"));
        nbt_tag_compound_append(tag_buffer_info,tag_num_faces);
        printf("Appending %d faces\n",num_faces);

        char name[200];
        sprintf(name,"%d faces (%d)%s",num_faces,material_id,material_name);
        nbt_set_tag_name(tag_buffer_info,name,strlen(name));
        nbt_tag_compound_append(tag_buffers_info,tag_buffer_info);

        buf_min[0] = buf_min[1] = buf_min[2] = std::numeric_limits<float>::max();
        buf_max[0] = buf_max[1] = buf_max[2] = -std::numeric_limits<float>::max();

        float v[3][3];
        float n[3][3];
        float c[3][3];
        float tc[3][2];
        int stride = (3 + 3 + 2 + 3);
        float* real_buffer = (float*)p.buffer + sizeof(int);
        float* VertexPointer=real_buffer;
        float* NormalPointer=real_buffer + sizeof(float)*3;
        float* ColorPointer=real_buffer + sizeof(float)*6;
        float* TexCoordPointer=real_buffer + sizeof(float)*9;

        for (int faces=0; faces<num_faces; faces++) {
            for (int l=0; l<3; l++) {
                for (int k=0; k<3; k++) {
                    int offset=k+l*stride+faces*stride*3;
                    v[l][k]=VertexPointer[offset];
                    n[l][k]=NormalPointer[offset];
                    c[l][k]=ColorPointer[offset];
                    if (k<2) tc[l][k]=TexCoordPointer[offset];
                    buf_min[k] = std::min(v[l][k], buf_min[k]);
                    buf_max[k] = std::max(v[l][k], buf_max[k]);
                }
            }
        }

        tag_bminmax=nbt_new_tag_float(buf_min[0]);
        nbt_set_tag_name(tag_bminmax,(char*)"bmin[0]",strlen("bmin[0]"));
        nbt_tag_compound_append(tag_buffer_info,tag_bminmax);
        tag_bminmax=nbt_new_tag_float(buf_min[1]);
        nbt_set_tag_name(tag_bminmax,(char*)"bmin[1]",strlen("bmin[1]"));
        nbt_tag_compound_append(tag_buffer_info,tag_bminmax);
        tag_bminmax=nbt_new_tag_float(buf_min[2]);
        nbt_set_tag_name(tag_bminmax,(char*)"bmin[2]",strlen("bmin[2]"));
        nbt_tag_compound_append(tag_buffer_info,tag_bminmax);
        tag_bminmax=nbt_new_tag_float(buf_max[0]);
        nbt_set_tag_name(tag_bminmax,(char*)"bmax[0]",strlen("bmax[0]"));
        nbt_tag_compound_append(tag_buffer_info,tag_bminmax);
        tag_bminmax=nbt_new_tag_float(buf_max[1]);
        nbt_set_tag_name(tag_bminmax,(char*)"bmax[1]",strlen("bmax[1]"));
        nbt_tag_compound_append(tag_buffer_info,tag_bminmax);
        tag_bminmax=nbt_new_tag_float(buf_max[2]);
        nbt_set_tag_name(tag_bminmax,(char*)"bmax[2]",strlen("bmax[2]"));
        nbt_tag_compound_append(tag_buffer_info,tag_bminmax);

    }

*/

extern magic(double v[3][3], double tc[3][2], struct image_loader* image_buffer, int buf_count, int faces, sf::Image& image_copy, int offset_x, int offset_y, int offset_z, int box_x, int box_y, int box_z, unsigned short **mc_sub, double block_scale);
extern magic(double v[3][3], double tc[3][2], struct image_loader* image_buffer, int buf_count, int faces, sf::Image& image_copy, int offset_x, int offset_y, int offset_z, int box_x, int box_y, int box_z, unsigned short **mc_sub, double block_scale);
//ayay2
//extern magic(float v[3][3], float tc[3][2], struct image_loader* image_buffer, int buf_count, int faces, sf::Image& image_copy, float offset_x, float offset_y, float offset_z, int box_x, int box_y, int box_z, unsigned short* mc, float block_scale);

extern int main_mceditor5(int box_x, int box_y, int box_z, unsigned char* mc);
extern int main_mceditor6(int box_x, int box_y, int box_z, unsigned char* mc, int box_x_block_start, int box_y_block_start, int box_z_block_start, int box_x_total_start, int box_y_total_start, int box_z_total_start);
extern int main_mceditor6_plot(int box_x, int box_y, int box_z, unsigned char* mc, int box_x_block_start, int box_y_block_start, int box_z_block_start, int box_x_total_start, int box_y_total_start, int box_z_total_start);


extern int small;

extern int block_count;
extern glm::ivec3* blocks;
extern int region_x_request;
extern int region_z_request;
extern glm::vec3* block_colors;

extern bool warning_done_x;
extern bool warning_done_y;
extern bool warning_done_z;
extern bool warning_done_x_min;
extern bool warning_done_y_min;
extern bool warning_done_z_min;

extern bool warning_done_topping;
int offset_real_y;

bool wuppie_all=true;

extern int scan_done0_plot(FILE* report, char* dat_filename, char* voxel_filename);

bool hit_cube_y_start=false;
bool hit_cube_y_end=false;
bool hit_cube_z_start=false;
bool hit_cube_z_end=false;

extern int main_mceditor5_from_file(char* dat_filename, char* voxel_filename);

extern int plotting;



int quad;


int check_tot_hits=0;
int check_tot_blocks=0;

extern glm::dvec2 ModifiedAirocean_fromGeo(double lat, double lon);
extern glm::dvec2 ModifiedAirocean_toGeo(double x, double y);

double tot_lat[2]={0,0};
double tot_lon[2]={0,0};;

double ll_Avx;
double ll_ABv;
double ll_Avz;
double ll_ACv;

double Avx;
double ABv;
double Avz;
double ACv;

double Amx;    double Amz;
double ABx;    double ACx;
double ABz;    double ACz;

double ll_a_x;
double ll_b_x;
double ll_c_x;
double ll_a_z;
double ll_b_z;
double ll_c_z;

glm::fvec2 top_left;
glm::fvec2 top_right;
glm::fvec2 bot_left;
glm::fvec2 bot_right;
//glm::dvec2 top_left;
//glm::dvec2 top_right;
//glm::dvec2 bot_left;
//glm::dvec2 bot_right;
double vertical;

double schematic_size=0;

void minecraft_set(double bmin_total[3], double bmax_total[3], double tot_lon[2], double tot_lat[2]) {
    static bool first=true;

// use pacman_cuberite\project-obj\projection.py (in ubuntu shell, install python jnius & numpy first) lon lat order...!
//for bte 1to1 coordinates. (Build the Earth).

    if (area=="Enschede" && mirror!=0) {
//        top_left =glm::dvec2(3302480.6863125535, -5334572.906513852);
//        top_right=glm::dvec2(3312756.4245311604, -5331483.703731423);
//        bot_left =glm::dvec2(3300154.6704858197, -5326818.811974641);
//        bot_right=glm::dvec2(3310446.4741736553, -5323728.268546224);
        vertical =bmax_total[0]- bmin_total[0];

        top_left =glm::fvec2((3302480-3300154)*2.5, (-5334572+5334572)*2.5);
        top_right=glm::fvec2((3312756-3300154)*2.5, (-5331483+5334572)*2.5);
        bot_left =glm::fvec2((3300154-3300154)*2.5, (-5326818+5334572)*2.5);
        bot_right=glm::fvec2((3310446-3300154)*2.5, (-5323728+5334572)*2.5);
    } else if (area=="DenHaag" && mirror!=0) {
        vertical =bmax_total[0]- bmin_total[0];

//        top_left =glm::dvec2(3109621.6855937983,   -5377456.286742788);
//        top_right=glm::dvec2(3122982.1209280635,   -5373177.931635568);
//        bot_left =glm::dvec2(3105714.1226496957,   -5365303.167017606);
//        bot_right=glm::dvec2(3119098.869450965,    -5361027.64235222);

        float cnt_x=3105714.1226496957;
        float cnt_z=-5377456.286742788;

        top_left =glm::fvec2((3109621.6855937983-cnt_x)*3.0,   (-5377456.286742788-cnt_z)*3.0);
        top_right=glm::fvec2((3122982.1209280635-cnt_x)*3.0,   (-5373177.931635568-cnt_z)*3.0);
        bot_left =glm::fvec2((3105714.1226496957-cnt_x)*3.0,   (-5365303.167017606-cnt_z)*3.0);
        bot_right=glm::fvec2((3119098.869450965 -cnt_x)*3.0,   (-5361027.64235222 -cnt_z)*3.0);
    } else if (area=="Amsterdam" && mirror!=0) {
        vertical =bmax_total[0]- bmin_total[0];

        float cnt_x=0;
        float cnt_z=0;
        top_left =glm::fvec2((3161552.411711868 -cnt_x)*1.0,   (-5428108.961447178 -cnt_z)*1.0);
        top_right=glm::fvec2((3194832.7696658284-cnt_x)*1.0,   (-5417672.727180401 -cnt_z)*1.0);
        bot_left =glm::fvec2((3141325.945715654 -cnt_x)*1.0,   (-5364168.2744096005-cnt_z)*1.0);
        bot_right=glm::fvec2((3174801.152713919 -cnt_x)*1.0,   (-5353619.96164422  -cnt_z)*1.0);

//top left:       3161552.411711868,      -5428108.961447178
//top right:      3194832.7696658284,     -5417672.727180401
//bottom left:    3141325.945715654,      -5364168.2744096005
//bottom right:   3174801.152713919,      -5353619.96164422
    } else if (area=="NewYork" && mirror!=0) {
        vertical =bmax_total[0]- bmin_total[0];

//        top_left =glm::dvec2(3109621.6855937983,   -5377456.286742788);
//        top_right=glm::dvec2(3122982.1209280635,   -5373177.931635568);
//        bot_left =glm::dvec2(3105714.1226496957,   -5365303.167017606);
//        bot_right=glm::dvec2(3119098.869450965,    -5361027.64235222);

        float cnt_x=0;
        float cnt_z=0;
//        float cnt_x=-8544252.905233163;
//        float cnt_z=-6033824.210212925;

        top_left =glm::fvec2((-8544252.905233163-cnt_x)*1.0,   (-6025046.430239671-cnt_z)*1.0);
        top_right=glm::fvec2((-8514849.449649889-cnt_x)*1.0,   (-6033824.210212925-cnt_z)*1.0);
        bot_left =glm::fvec2((-8537325.411157254-cnt_x)*1.0,   (-6001596.67934797 -cnt_z)*1.0);
        bot_right=glm::fvec2((-8507791.20154021 -cnt_x)*1.0,   (-6010397.765766095-cnt_z)*1.0);
//        top_left =glm::dvec2((-8544252.905233163-cnt_x)*1.0,   (-6025046.430239671-cnt_z)*1.0);
//        top_right=glm::dvec2((-8514849.449649889-cnt_x)*1.0,   (-6033824.210212925-cnt_z)*1.0);
//        bot_left =glm::dvec2((-8537325.411157254-cnt_x)*1.0,   (-6001596.67934797 -cnt_z)*1.0);
//        bot_right=glm::dvec2((-8507791.20154021 -cnt_x)*1.0,   (-6010397.765766095-cnt_z)*1.0);
    } else {
        double f;
        if (schematic_size!=0) {
            if (voxel_bottom>0) {
                f=(schematic_size+voxel_bottom)/(bmax_total[0]-bmin_total[0]);

                if (!make_schematic)
                    if (f*(bmax_total[0]-bmin_total[0])>(248.0-voxel_bottom)) f=(248.0-voxel_bottom)/(bmax_total[0]-bmin_total[0]);
                else
                    if (f*(bmax_total[0]-bmin_total[0])>schematic_size) f=schematic_size/(bmax_total[0]-bmin_total[0]);

            } else {
                f=schematic_size/(bmax_total[0]-bmin_total[0]);
                if (!make_schematic)
                    if (f*(bmax_total[0]-bmin_total[0])>248.0) f=248.0/(bmax_total[0]-bmin_total[0]);
                else
                    if (f*(bmax_total[0]-bmin_total[0])>schematic_size) f=schematic_size/(bmax_total[0]-bmin_total[0]);
            }

/*
            f=schematic_size/(bmax_total[0]-bmin_total[0]);
            if (!make_schematic)
                if (f*(bmax_total[0]-bmin_total[0])>248.0) f=248.0/(bmax_total[0]-bmin_total[0]);
            else
                if (f*(bmax_total[0]-bmin_total[0])>schematic_size) f=schematic_size/(bmax_total[0]-bmin_total[0]);
*/

            if (f*(bmax_total[1]-bmin_total[1])>schematic_size) f=schematic_size/(bmax_total[1]-bmin_total[1]);
            if (f*(bmax_total[2]-bmin_total[2])>schematic_size) f=schematic_size/(bmax_total[2]-bmin_total[2]);
        } else {
            if (!make_schematic) {
                f=(248.0-voxel_bottom)/(bmax_total[0]-bmin_total[0]);
                if (f*(bmax_total[1]-bmin_total[1])>=512.0) f=512/(bmax_total[1]-bmin_total[1]);
                if (f*(bmax_total[2]-bmin_total[2])>=512.0) f=512/(bmax_total[2]-bmin_total[2]);
            }
        }

        top_left =glm::fvec2(0,                                       0);
        top_right=glm::fvec2(bmax_total[1]*f - bmin_total[1]*f,       0);
        bot_left =glm::fvec2(0,                                       bmax_total[2]*f - bmin_total[2]*f);
        bot_right=glm::fvec2(bmax_total[1]*f - bmin_total[1]*f,       bmax_total[2]*f - bmin_total[2]*f);
        vertical =bmax_total[0]*f- bmin_total[0]*f;

        tot_lon[0]=-180.0; tot_lon[1]=180.0;
        tot_lat[0]=-90.0; tot_lat[1]=90.0;
    }

    if (top_left[0]<0)
        Amx = top_left[0]-512;  //?????? must be 511?
    else
        Amx = top_left[0];

    ABx = top_right[0] - top_left[0];
    ACx = bot_left[0] - top_left[0];

    if (top_left[1]<0)
        Amz = top_left[1]-512; // must be 511?
    else
        Amz = top_left[1]; // ?????????

    ABz = top_right[1] - top_left[1];
    ACz = bot_left[1] - top_left[1];

    Avx = bmin_total[1];
    ABv = bmax_total[1] - bmin_total[1];
    Avz = bmax_total[2];
    ACv = -(bmax_total[2] - bmin_total[2]);

    ll_Avx = tot_lon[0];
    ll_ABv = tot_lon[1] - tot_lon[0];
    ll_Avz = tot_lat[0];
    ll_ACv = tot_lat[1] - tot_lat[0];

    ll_a_x = (ABx/ll_ABv);
    ll_b_x = (ACx/ll_ACv);
    ll_a_z = (ABz/ll_ABv);
    ll_b_z = (ACz/ll_ACv);

    ll_c_x =  - Amx + (ABx/ll_ABv)*ll_Avx + (ACx/ll_ACv)*ll_Avz;
    ll_c_z =  - Amz + (ABz/ll_ABv)*ll_Avx + (ACz/ll_ACv)*ll_Avz;
}

void vertex_to_minecraft(double vx, double vz, double& m_x, double& m_z) {
    double dABv = (vx - Avx) / ABv;
    double dACv = (vz - Avz) / ACv;

    m_x = Amx  +  dABv * ABx + dACv * ACx;
    m_z = Amz  +  dABv * ABz + dACv * ACz;
}

void lon_lat_to_minecraft(double lon, double lat, double& m_x, double& m_z) {
    double dll_ABv = (lon - ll_Avx) / ll_ABv;
    double dll_ACv = (lat - ll_Avz) / ll_ACv;

    m_x = Amx  +  dll_ABv * ABx + dll_ACv * ACx;
    m_z = Amz  +  dll_ABv * ABz + dll_ACv * ACz;
}

void minecraft_to_lat_lon(double m_x, double m_z, double& lon, double& lat ) {
    double c_x = m_x + ll_c_x;
    double c_z = m_z + ll_c_z;

    lat = (ll_a_x*c_z - ll_a_z*c_x) / (ll_a_x*ll_b_z - ll_a_z*ll_b_x);
    lon = (c_z - ll_b_z*lat) / ll_a_z;
}

double pixels_per_block_glob=0.0;
double pixels_per_block_glob_rev=0.0;

extern glm::mat4 exporter;
extern glm::mat4 exporter2;

extern bool rot_on;
extern float voxel_bottom;

extern bool rot_on;

int WUPPIE_VECTOR(std::vector<BufferObject> buffers, std::vector<tinyobj::material_t> &materials, float bmin_o[3], float bmax_o[3], double lat, double lon, std::string fn) {

    int flop=0;
    if (!plot_only && !rot_on && !make_schematic && !hold_voxels) {
        char new_file[100];
        sprintf(new_file,"../cut/done/%s.DAT",fn.c_str());
        if (file_exists(new_file)) {
            printf("%s exists, exiting!!!!!!!!!!!!!!\n",new_file);
            return 0;
        }
    }

    double bmin_total[3];
    double bmax_total[3];
    char dat_name[200];
    char line[200];
//aiaiai
//    if (crossing==0) {
    if (area=="Models") {
        printf("OBJECT MIN: X=%24.17f Y=%24.17f Z=%24.17f\n",bmin_o[0],bmin_o[1],bmin_o[2]);
        printf("OBJECT MAX: X=%24.17f Y=%24.17f Z=%24.17f\n",bmax_o[0],bmax_o[1],bmax_o[2]);
        printf("OBJECT DIF: X=%24.17f Y=%24.17f Z=%24.17f\n",bmax_o[0]-bmin_o[0],bmax_o[1]-bmin_o[1],bmax_o[2]-bmin_o[2]);
//        RECALC_BMIN_BMAX3(buffers, bmin_o,bmax_o, 0.0,0.0);


/*        if ((rot_on || rot_plot) && voxel_bottom > 0.0) {
            printf("bmin[0] from %24.17f to ",bmin_o[0]);
            bmin_o[0]=bmin_o[0]-(bmax_o[0]-bmin_o[0])*voxel_bottom;
            printf("%24.17f\n",bmin_o[0]);
            printf("OBJECT MIN: X=%24.17f Y=%24.17f Z=%24.17f\n",bmin_o[0],bmin_o[1],bmin_o[2]);
            printf("OBJECT MAX: X=%24.17f Y=%24.17f Z=%24.17f\n",bmax_o[0],bmax_o[1],bmax_o[2]);
            printf("OBJECT DIF: X=%24.17f Y=%24.17f Z=%24.17f\n",bmax_o[0]-bmin_o[0],bmax_o[1]-bmin_o[1],bmax_o[2]-bmin_o[2]);
        }
*/

        for (int n=0; n<3; n++) {
            bmin_total[n]=bmin_o[n];
            bmax_total[n]=bmax_o[n];
        }
    } else {
        printf("OBJECT MIN: X=%24.17f Y=%24.17f Z=%24.17f\n",bmin_o[0],bmin_o[1],bmin_o[2]);
        printf("OBJECT MAX: X=%24.17f Y=%24.17f Z=%24.17f\n",bmax_o[0],bmax_o[1],bmax_o[2]);
        printf("OBJECT DIF: X=%24.17f Y=%24.17f Z=%24.17f\n",bmax_o[0]-bmin_o[0],bmax_o[1]-bmin_o[1],bmax_o[2]-bmin_o[2]);
        sprintf(dat_name,"%s.DAT",area.c_str());
        FILE* HOP;
        if ((HOP = fopen (dat_name, "r"))!=NULL) {
            if (fgets (line,200, HOP)!=NULL) {
                while (replace_str(line,".",","));
                if ( sscanf(line,"TOTAL MIN: X=%lf Y=%lf Z=%lf\n",&bmin_total[0],&bmin_total[1],&bmin_total[2]) != 3) {
                    printf("ERROR READING TOTAL MIN from %s\n",dat_name);
                    return -1;
                } else {
                    printf("LOADED TOTAL MIN: X=%24.17f Y=%24.17f Z=%24.17f\n",bmin_total[0],bmin_total[1],bmin_total[2]);
                }
            } else {
                printf("ERROR READING TOTAL MIN from %s\n",dat_name);
            }
            if (fgets (line,200, HOP)!=NULL) {
                while (replace_str(line,".",","));
                if (sscanf(line,"TOTAL MAX: X=%lf Y=%lf Z=%lf\n",&bmax_total[0],&bmax_total[1],&bmax_total[2]) != 3) {
                    printf("ERROR READING TOTAL MAX from %s\n",dat_name);
                    return -1;
                } else {
                    printf("LOADED TOTAL MAX: X=%24.17f Y=%24.17f Z=%24.17f\n",bmax_total[0],bmax_total[1],bmax_total[2]);
                }
            } else {
                printf("ERROR READING TOTAL MAX from %s\n",dat_name);
            }
            if (fgets (line,200, HOP)!=NULL) { //diff
            } else {
                printf("ERROR READING TOTAL DIF from %s\n",dat_name);
            }
            printf("LOADED TOTAL DIF: X=%24.17f Y=%24.17f Z=%24.17f\n",bmax_total[0]-bmin_total[0],bmax_total[1]-bmin_total[1],bmax_total[2]-bmin_total[2]);

            if (fgets (line,200, HOP)!=NULL) {
                while (replace_str(line,".",","));
                if (sscanf(line,"LAT: NORTH=%lf SOUTH=%lf\n",&tot_lat[0],&tot_lat[1]) != 2) {
                    printf("ERROR READING LAT FROM %s\n",dat_name);
                }
            }
            if (fgets (line,200, HOP)!=NULL) {
                while (replace_str(line,".",","));
                if (sscanf(line,"LON:  WEST=%lf  EAST=%lf\n",&tot_lon[0],&tot_lon[1]) != 2) {
                    printf("ERROR READING LON FROM %s\n",dat_name);
                }
            }
            printf("TOTAL: NORTH=%20.16f WEST=%20.16f\n",tot_lat[0],tot_lon[0]);
            printf("TOTAL: SOUTH=%20.16f EAST=%20.16f\n",tot_lat[1],tot_lon[1]);
            printf("TOTAL: DIFF =%20.16f      %20.16f\n",tot_lat[0]-tot_lat[1],tot_lon[0]-tot_lon[1]);

            fclose(HOP);
            if (area=="Enschede") {
                bmin_total[0]+=15.0;
                bmax_total[0]+=15.0;
            } else if (area=="DenHaag") {
                bmin_total[0]=-80.0;
                bmax_total[0]=60.0;
            } else if (area=="NewYork") {
//floors
                bmin_total[0]=-40.0;
//                bmin_total[0]=-10.0;
                bmax_total[0]=150.0;
            } else if (area=="Amsterdam") {
                bmin_total[0]=-30.0;
                bmax_total[0]=150.0;
            }
        } else {
            printf("Error reading %s\n",dat_name);
            return-1;
        }
    }

    if (area!="Models") {
        printf("OCTANT NORTH=%20.16f WEST=%20.16f\n",lat_north,lon_west);
        printf("OCTANT SOUTH=%20.16f EAST=%20.16f\n",lat_south,lon_east);
        printf("OCTANT DIFF =%20.16f      %20.16f\n",lat_north-lat_south,lon_east-lon_west);
    }

    minecraft_set(bmin_total, bmax_total, tot_lon, tot_lat);

    if (area!="Models") {
        double ll_lat;
        double ll_lon;

        minecraft_to_lat_lon(top_left[0],  top_left[1],  ll_lon, ll_lat );    printf("TOP_LEFT:  LAT/LON = %20.16f , %20.16f\n",ll_lat,ll_lon);
        minecraft_to_lat_lon(bot_left[0],  bot_left[1],  ll_lon, ll_lat );    printf("BOT_LEFT:  LAT/LON = %20.16f , %20.16f\n",ll_lat,ll_lon);
        minecraft_to_lat_lon(top_right[0], top_right[1], ll_lon, ll_lat );    printf("TOP_RIGHT: LAT/LON = %20.16f , %20.16f\n",ll_lat,ll_lon);
        minecraft_to_lat_lon(bot_right[0], bot_right[1], ll_lon, ll_lat );    printf("BOT_RIGHT: LAT/LON = %20.16f , %20.16f\n",ll_lat,ll_lon);
    } else {
    }

    double blocks_x=sqrt( (top_right[0]-top_left[0])*(top_right[0]-top_left[0])  +  (top_right[1]-top_left[1])*(top_right[1]-top_left[1]) );
    double block_scale_x=blocks_x/(bmax_total[1]-bmin_total[1]);
    printf("BLOCKS X=%15.6f   SCALE=%9.6f\n",blocks_x,block_scale_x);

    double blocks_y=vertical;
    double block_scale_y=blocks_y/(bmax_total[0]-bmin_total[0]);
    printf("BLOCKS Y=%15.6f   SCALE=%9.6f\n",blocks_y,block_scale_y);

    double blocks_z=sqrt( (top_left[0]-bot_left[0])*(top_left[0]-bot_left[0])  +  (top_left[1]-bot_left[1])*(top_left[1]-bot_left[1]) );
    double block_scale_z=blocks_z/(bmax_total[2]-bmin_total[2]);
    printf("BLOCKS Z=%15.6f   SCALE=%9.6f\n",blocks_z,block_scale_z);

    double block_scale_avg=(block_scale_x + block_scale_z)/2.0;
    printf("BLOCKS SCALE AVERAGE            =%9.6f\n",block_scale_avg);

//aiaiai
//    if (crossing==0) {
    if (area=="Models") {
        for (int n=0; n<3; n++) {
            bmin_total[n]*=block_scale_avg;
            bmax_total[n]*=block_scale_avg;
        }
    }

//enschede x3
//    bmin_total[0]=-10;
    printf("TOTAL MIN: X=%24.17f Y=%24.17f Z=%24.17f\n",bmin_total[0],bmin_total[1],bmin_total[2]);
    printf("TOTAL MAX: X=%24.17f Y=%24.17f Z=%24.17f\n",bmax_total[0],bmax_total[1],bmax_total[2]);
    printf("TOTAL DIF: X=%24.17f Y=%24.17f Z=%24.17f\n",bmax_total[0]-bmin_total[0],bmax_total[1]-bmin_total[1],bmax_total[2]-bmin_total[2]);


//Enschede
//TOTAL MIN: X=-42,981323 Y=-4500,724121 Z=-3669,076172
//TOTAL MAX: X=101,206009 Y=5229,716309 Z=3663,711670
//TOTAL DIF: X=144,187332 Y=9730,440430 Z=7332,787842
//    bmin_total[0]=10.0;
//    bmax_total[0]=175.0;
//    bmin_total[0]=-20.0;
//    bmax_total[0]=145.0;
//    double block_scale=1200/(bmax_total[0]-bmin_total[0]);

//    bmin_total[0]=-11.0;
//    bmax_total[0]=165.0;
//    double block_scale=800/(bmax_total[0]-bmin_total[0]);
//  bmin_total[0]=0.0;
//  bmax_total[0]=100.0;

//hopla
//    double block_scale=300.0/(bmax_total[0]-bmin_total[0]);
    double block_scale=block_scale_avg;
//    double block_scale=8.576;

//    double filler_scale=
//total diff:  9.773 * 1.1 -> 10730 /
// 168,2 -> 168,2158 * 1.0

//Amsterdam
//    bmin_total[0]=-62;
//    bmax_total[0]=186;
//    printf("BLOCK SCALE=%2.3f\n",block_scale);

    int o_tot_hits=0;
    int o_tot_blocks=0;

    BufferObject one_buffer;

    double bmin[3];
    double bmax[3];

    int buf_count=0;

    bmin[0] = bmin[1] = bmin[2] = std::numeric_limits<double>::max();
    bmax[0] = bmax[1] = bmax[2] = -std::numeric_limits<double>::max();
    bool do_model=false;
//aiaiai
    if (area=="Models") {
//    if (crossing==0) {
        do_model=true;
        printf("Doing Models\n");
    }

    int total_triangles=0;
    double vertex_scale=0.0;
    double texture_scale=0.0;

    for (auto u : buffers) {
        one_buffer=u;
//        printf("hier4 \n");

        int num_faces=(one_buffer.length-sizeof(int)) / (3 + 3 + 3 + 2) / 3 / sizeof(float);     // 3:vtx, 3:normal, 3:col, 2:texcoord
//test double
        double v[3][3];
//        float v[3][3];
//        float n[3][3];
//        float c[3][3];
        double tc[3][2];
//        float tc[3][2];
//        printf("hier3 \n");
        int stride = (3 + 3 + 2 + 3);
        float* real_buffer = (float*)(one_buffer.buffer + sizeof(int));
        float* VertexPointer=real_buffer;
//        float* NormalPointer=real_buffer + 3;
//        float* ColorPointer=real_buffer + 6;
        float* TexCoordPointer=real_buffer + 9;
//        float* TexCoordPointer=real_buffer + 9;
        int mat_id;
        memcpy(&mat_id,one_buffer.buffer,sizeof(int));

        static bool no_texture;
        int w=0;
        int h=0;
//        printf("hier2 \n");

//jaja
        sf::Image image_copy; //dummy
        image_copy.create(256,256,sf::Color(255,255,255,255));
        sf::Image* image=&image_copy;
        if (mat_id < materials.size())
//        if (mat_id < materials.size()-1)
        {
            if (!image_buffer[mat_id]->ok) {
//                image=0;
                printf("Image not ok!!!!\n");
                w=256;
                h=256;
            }
            else {
                w=image_buffer[mat_id]->image->getSize().x;
                h=image_buffer[mat_id]->image->getSize().y;
//                image=(unsigned char*)image_buffer[mat_id]->image->getPixelsPtr();
//                sfml_image=image_buffer[mat_id]->image;
//                printf("Material id: %3d  w=%3d , h=%3d  ",mat_id,w,h);
            }
            no_texture=false;
            image=image_buffer[mat_id]->image;
        } else {
            printf("No material id: %d\n",mat_id);
//            sf::sleep(sf::seconds(2.0));
            no_texture=true;
        }
//        printf("hier5 mat_id=%d size=%d\n",mat_id, materials.size());
//        printf("hier1 \n");
        for (int faces=0; faces<num_faces; faces++) {
            for (int l=0; l<3; l++) {
                int offset=(stride*(l+faces*3));
                for (int k=0; k<3; k++) {
                    if (offset*sizeof(float) >= one_buffer.length-sizeof(int)) {
                        printf("Error offset\n");
                        return-1;
                    }
//hopla
//                    v[l][k]=VertexPointer[offset+k]*block_scale;

                    v[l][k]=VertexPointer[offset+k];

//                    v[l][k]=(v[l][k])*1.0005;
//                    n[l][k]=NormalPointer[offset+k];
//                    c[l][k]=ColorPointer[offset+k];

                    if (k<2) {
                        if (no_texture)
                            tc[l][k]=1.0/(1.0+(float)l+(float)k);
                        else
                            tc[l][k]=TexCoordPointer[offset+k];
                    }
                } //point

                glm::dvec4 hop;

                if (do_model) {
                    if (make_schematic)
                        v[l][0]=(v[l][0]*block_scale-bmin_total[0]);
                    else
//tuuttuut
                        v[l][0]=(v[l][0]*block_scale-bmin_total[0])+1;
                    v[l][1]=(v[l][1]*block_scale-bmin_total[1]);
                    v[l][2]=(bmax_total[2]-v[l][2]*block_scale);
                    hop = glm::dvec4(v[l][0], v[l][1], v[l][2], 1.0f) ;
                    v[l][0]=hop.x; v[l][1]=hop.y; v[l][2]=hop.z;
                } else {
//                    double m_x;
//                    double m_z;
//                    vertex_to_minecraft(v[l][1], v[l][2], m_x, m_z);
                    v[l][0]=(v[l][0]-bmin_total[0]);
//                    hop = glm::dvec4(v[l][0], m_x, m_z, 1.0f);
                    hop = glm::dvec4(v[l][0]*block_scale, v[l][1], v[l][2], 1.0f);
                }
//                glm::dvec3 hop = glm::dvec4(v[l][0], v[l][1], v[l][2], 1.0f);

                bmin[0]=std::min((double)hop.x, bmin[0]);   bmax[0]=std::max((double)hop.x, bmax[0]);
                bmin[1]=std::min((double)hop.y, bmin[1]);   bmax[1]=std::max((double)hop.y, bmax[1]);
                bmin[2]=std::min((double)hop.z, bmin[2]);   bmax[2]=std::max((double)hop.z, bmax[2]);
            } // triangle
            total_triangles++;
            double texture_scale1=sqrt( (tc[0][0]*w-tc[1][0]*w)*(tc[0][0]*w-tc[1][0]*w) + (tc[0][1]*h-tc[1][1]*h)*(tc[0][1]*h-tc[1][1]*h) );
            double texture_scale2=sqrt( (tc[1][0]*w-tc[2][0]*w)*(tc[1][0]*w-tc[2][0]*w) + (tc[1][1]*h-tc[2][1]*h)*(tc[1][1]*h-tc[2][1]*h) );
            double texture_scale3=sqrt( (tc[2][0]*w-tc[0][0]*w)*(tc[2][0]*w-tc[0][0]*w) + (tc[2][1]*h-tc[0][1]*h)*(tc[2][1]*h-tc[0][1]*h) );
            texture_scale+=(texture_scale1+texture_scale2+texture_scale3)/3.0;
            double vertex_scale1=sqrt( (v[0][0]-v[1][0])*(v[0][0]-v[1][0]) + (v[0][1]-v[1][1])*(v[0][1]-v[1][1]) + (v[0][2]-v[1][2])*(v[0][2]-v[1][2]));
            double vertex_scale2=sqrt( (v[1][0]-v[2][0])*(v[1][0]-v[2][0]) + (v[1][1]-v[2][1])*(v[1][1]-v[2][1]) + (v[1][2]-v[2][2])*(v[1][2]-v[2][2]));
            double vertex_scale3=sqrt( (v[2][0]-v[0][0])*(v[2][0]-v[0][0]) + (v[2][1]-v[0][1])*(v[2][1]-v[0][1]) + (v[2][2]-v[0][2])*(v[2][2]-v[0][2]));
            vertex_scale+=(vertex_scale1+vertex_scale2+vertex_scale3)/3.0;

        } // faces
    } //buffers
    double pixels_per_block=0.0;
//aiaiai
    if (area=="Models") {
        if (vertex_scale!=0.0) pixels_per_block = texture_scale/vertex_scale;
        printf("Pixels per block estimate = %9.6f  Block scale = %9.6f",pixels_per_block,block_scale);
        pixels_per_block_glob=pixels_per_block;
//        pixels_per_block_glob_rev=3.5/pixels_per_block;

        double filler;
//        double filler=0.25*pixels_per_block;
//        if (filler>0.5) filler=0.5;
        filler=pixels_per_block_glob/3.5;
        printf(" Texture pixelator = %9.6f\n",filler);
//        printf("\n");
    } else {
//tuuttuut3
        pixels_per_block_glob=8.0/block_scale;
        pixels_per_block_glob_rev=block_scale/8.0;
//        pixels_per_block_glob=4.0;
//        pixels_per_block_glob_rev=1.0/4.0;
    }

    double offset_xyz[3];

    for (int n=0; n<3; n++) {
        offset_xyz[n]=bmin_total[n]*block_scale;
    }

    int box_x_block_start=bmin[0];
    int box_y_block_start=bmin[1];
    int box_z_block_start=bmin[2];

    int offset_x=offset_xyz[0];
    int offset_y=offset_xyz[1];
    int offset_z=offset_xyz[2];

    int box_x_block_end=bmax[0];
    int box_y_block_end=bmax[1];
    int box_z_block_end=bmax[2];

    int box_x_total_start=bmin_total[0];
    int box_y_total_start=bmin_total[1];
    int box_z_total_start=bmin_total[2];

    int box_x_total_end=bmax_total[0];
    int box_y_total_end=bmax_total[1];
    int box_z_total_end=bmax_total[2];

    int box_x=box_x_block_end-box_x_block_start+1;
    int box_y=box_y_block_end-box_y_block_start+1;
    int box_z=box_z_block_end-box_z_block_start+1;

    for (int n=0; n<3; n++) {
        bmin_o[n]=bmin[n];
        bmax_o[n]=bmax[n];
    }


  //  if (wuppie_all) {
//        if (box_x>255) box_x=255;
//    }

//    offset_real_y=0;
    offset_real_y=box_x_total_start;
//    offset_real_y=box_x_block_start - box_x_total_start;

/*
    Voxel one;

    one=Voxel(box_x,box_y,box_z);
    voxels.push_back(one);

    one=Voxel(box_x_block_start, box_y_block_start, box_z_block_start);
    voxels.push_back(one);

    one=Voxel(box_x_block_end, box_y_block_end, box_z_block_end);
    voxels.push_back(one);

    one=Voxel(box_x_total_start, box_y_total_start, box_z_total_start);
    voxels.push_back(one);

    one=Voxel(box_x_total_end, box_y_total_end, box_z_total_end);
    voxels.push_back(one);

    printf("voxels[0] = SIZE:        X=%8d, Y=%8d, Z=%8d\n", voxels[0].x, voxels[0].y, voxels[0].z );
    printf("voxels[1] = START:       X=%8d, Y=%8d, Z=%8d\n", voxels[1].x, voxels[1].y, voxels[1].z );
    printf("voxels[2] = END:         X=%8d, Y=%8d, Z=%8d\n", voxels[2].x, voxels[2].y, voxels[2].z );
    printf("voxels[3] = TOTAL START: X=%8d, Y=%8d, Z=%8d\n", voxels[3].x, voxels[3].y, voxels[3].z );
    printf("voxels[4] = TOTAL END:   X=%8d, Y=%8d, Z=%8d\n", voxels[4].x, voxels[4].y, voxels[4].z );
*/

//    for (auto u : voxels) {
//        printf("VOXEL SIZE: X=%d, Y=%d, Z=%d\n",u.x,u.y,u.z);
//    }

    if (wuppie_all || make_schematic) {
        printf("\n");
        printf("x_block_start=%6d   y_block_start=%6d   z_block_start=%6d\n",box_x_block_start,box_y_block_start,box_z_block_start);
        printf("x_block_end  =%6d   y_block_end  =%6d   z_block_end  =%6d\n",box_x_block_end,box_y_block_end,box_z_block_end);
        printf("x_block      =%6d   y_block      =%6d   z_block      =%6d\n",box_x_block_end-box_x_block_start,box_y_block_end-box_y_block_start,box_z_block_end-box_z_block_start);
        printf("\n");
        printf("x_total_start=%6d   y_total_start=%6d   z_total_start=%6d\n",box_x_total_start,box_y_total_start,box_z_total_start);
        printf("x_total_end=  %6d   y_total_end=  %6d   z_total_end=  %6d\n",box_x_total_end,box_y_total_end,box_z_total_end);
        printf("x_total      =%6d   y_total      =%6d   z_total      =%6d\n",box_x_total_end-box_x_total_start,box_y_total_end-box_y_total_start,box_z_total_end-box_z_total_start);
        printf("\n");
        printf("Setting           %6d                     %6d                     %6d\n", box_x, box_y, box_z);
        printf("\n");
    }

    unsigned short **mc_sub;
    LONG64 tot_off=box_x*box_y*box_z*4;
    LONG64 tot_off_x=box_y*box_z*4;

    if (!plot_only && !rot_on && !rot_plot) {

        char filename[2000];
        std::ofstream ofs;
        sprintf(filename, "../cut/%s.DAT",fn.c_str());

        if (wuppie_all) printf("Writing %s ...",filename);
        ofs.open(filename);
        ofs << "X=" << box_x << " Y=" << box_y << " Z=" << box_z << "\n";
        ofs << "OCTANT=" << fn.c_str() << "\n";
        ofs << "BYTES=" << tot_off << "\n";
        ofs << "ABS MIN X=" << box_x_block_start << " Y=" << box_y_block_start << " Z=" << box_z_block_start << "\n";
        ofs << "ABS MAX X=" << box_x_block_end   << " Y=" << box_y_block_end   << " Z=" << box_z_block_end   << "\n";
        ofs << "TOTAL MIN X=" << box_x_total_start << " Y=" << box_y_total_start << " Z=" << box_z_total_start << "\n";
        ofs << "TOTAL MAX X=" << box_x_total_end   << " Y=" << box_y_total_end   << " Z=" << box_z_total_end   << "\n";
        ofs << "AREA=" << area   << "\n";

        char n_str[100];    char s_str[100];    char e_str[100];    char w_str[100];
        sprintf(n_str,"%lf",lat_north); while (replace_str(n_str,",","."));
        sprintf(s_str,"%lf",lat_south); while (replace_str(s_str,",","."));
        sprintf(w_str,"%lf",lon_west ); while (replace_str(w_str,",","."));
        sprintf(e_str,"%lf",lon_east ); while (replace_str(e_str,",","."));

        ofs << "N=" << n_str << " W=" << w_str << " E=" << e_str << " S=" << s_str << "\n";

        ofs.close();
    }
    if (wuppie_all) printf("Ready\n");

    buf_count=0;
    int tot_faces=0;

    bool hit_cube_y_start=false;
    bool hit_cube_y_end=false;
    bool hit_cube_z_start=false;
    bool hit_cube_z_end=false;

    double bmin_org[3];
    double bmax_org[3];

    check_tot_hits=0;
    check_tot_blocks=0;

    for (int nnn=0; nnn<buffers.size(); nnn++) {
//    for (auto u : buffers) {
//        one_buffer=u;
        one_buffer=buffers[nnn];

        bmin_org[0] = bmin_org[1] = bmin_org[2] = std::numeric_limits<double>::max();
        bmax_org[0] = bmax_org[1] = bmax_org[2] = -std::numeric_limits<double>::max();

//        size_t length=one_buffer.length - sizeof(int);
//        int numTriangles = (length) / (3 + 3 + 3 + 2) / 3;


        int num_faces=(one_buffer.length-sizeof(int)) / (3 + 3 + 3 + 2) / 3 / sizeof(float);     // 3:vtx, 3:normal, 3:col, 2:texcoord
        double v[3][3];
//        float n[3][3];
//        float c[3][3];
        double tc[3][2];
        int stride = (3 + 3 + 2 + 3);
        float* real_buffer = (float*)(one_buffer.buffer + sizeof(int));
        float* VertexPointer=real_buffer;
//        float* NormalPointer=real_buffer + 3;
//        float* ColorPointer=real_buffer + 6;
        float* TexCoordPointer=real_buffer + 9;
//        float* TexCoordPointer=real_buffer + 9;
        int mat_id;
        memcpy(&mat_id,one_buffer.buffer,sizeof(int));

        static bool no_texture;
        int w=0;
        int h=0;
//jaja
        sf::Image image_copy; //dummy
        image_copy.create(256,256,sf::Color(255,255,255,255));
        sf::Image* image=&image_copy;
        if (mat_id < materials.size())
        {
            if (!image_buffer[mat_id]->ok) {
//                image=0;
                printf("Image not ok!!!!\n");
                w=256;
                h=256;
            }
            else {
                w=image_buffer[mat_id]->image->getSize().x;
                h=image_buffer[mat_id]->image->getSize().y;
//                image=(unsigned char*)image_buffer[mat_id]->image->getPixelsPtr();
//                sfml_image=image_buffer[mat_id]->image;
//                printf("Material id: %3d  w=%3d , h=%3d  ",mat_id,w,h);
            }
            no_texture=false;
            image=image_buffer[mat_id]->image;
        } else {
            printf("No material id: %d\n",mat_id);
//            sf::sleep(sf::seconds(2.0));
            no_texture=true;
        }

        for (int faces=0; faces<num_faces; faces++) {

            for (int l=0; l<3; l++) {
                int offset=(stride*(l+faces*3));
                for (int k=0; k<3; k++) {
                    if (offset*sizeof(float) >= one_buffer.length-sizeof(int)) {
                        printf("Error offset\n");
                        return-1;
                    }
//hopla
                    v[l][k]=VertexPointer[offset+k];
//                    v[l][k]=VertexPointer[offset+k]*block_scale-offset_xyz[k];
//leuk
//                    v[l][k]=(v[l][k] - mid_block[k])*1.001 + mid_block[k];
//                    n[l][k]=NormalPointer[offset+k];
//                    c[l][k]=ColorPointer[offset+k];
                    if (k<2) {
                        if (no_texture)
                            tc[l][k]=1.0/(1.0+(float)l+(float)k);
                        else
                            tc[l][k]=TexCoordPointer[offset+k];
                    }
                } //point

                glm::dvec4 hop;
                if (do_model) {
                    if (make_schematic)
                        v[l][0]=(v[l][0]*block_scale-bmin_total[0]);
                    else
                        v[l][0]=(v[l][0]*block_scale-bmin_total[0])+1;
                    v[l][1]=(v[l][1]*block_scale-bmin_total[1]);
                    v[l][2]=(bmax_total[2]-v[l][2]*block_scale);
//                    v[l][0]=(v[l][0]-bmin_total[0])*block_scale;
//                    v[l][1]=(v[l][1]-bmin_total[1])*block_scale;
//                    v[l][2]=(v[l][2]-bmin_total[2])*block_scale;
                    hop = glm::dvec4(v[l][0], v[l][1], v[l][2], 1.0f);
                    v[l][0]=hop.x; v[l][1]=hop.y; v[l][2]=hop.z;
                } else {
                    double m_x;
                    double m_z;
                    vertex_to_minecraft(v[l][1], v[l][2], m_x, m_z);

                    v[l][0]=(v[l][0]-bmin_total[0])*block_scale;
                    v[l][1]=m_x;
                    v[l][2]=m_z;

                    hop = glm::dvec4(v[l][0], v[l][1], v[l][2], 1.0f);
                }

                bmin_org[0]=std::min((double)hop.x, bmin_org[0]);   bmax_org[0]=std::max((double)hop.x, bmax_org[0]);
                bmin_org[1]=std::min((double)hop.y, bmin_org[1]);   bmax_org[1]=std::max((double)hop.y, bmax_org[1]);
                bmin_org[2]=std::min((double)hop.z, bmin_org[2]);   bmax_org[2]=std::max((double)hop.z, bmax_org[2]);

            } // triangle
//jaja
                if (!no_texture) magic(v,tc,image_buffer[mat_id], buf_count, faces,image_copy, offset_x, offset_y, offset_z, box_x, box_y, box_z, mc_sub, block_scale);
//            }

        } // faces
        printf("\rHits: %d  Mat: %3d/%3d (%3d,%3d) ",check_tot_hits,mat_id,materials.size(),w,h);
        printf("Buffer: %3d/%3d  Faces: %7d\r", buf_count+1, buffers.size(), num_faces);
//        printf("Total: buffer: %3d/%3d  Faces: %7d  ==>  bmin=%8d %8d %8d  bmax=%8d %8d %8d  diff=%8d %8d %8d \r",
//            buf_count+1, buffers.size(),num_faces,
//            (int)bmin_org[0],(int)bmin_org[1],(int)bmin_org[2],(int)bmax_org[0],(int)bmax_org[1],(int)bmax_org[2],
//            (int)bmax_org[0]-(int)bmin_org[0],(int)bmax_org[1]-(int)bmin_org[1],(int)bmax_org[2]-(int)bmin_org[2]);

        buf_count++;
        tot_faces+=num_faces;
    } //buffers
    printf("\rVoxels: %9d  Hits: %8d  ", voxels.size(), check_tot_hits);
    printf("Buffers: %3d  Materials: %3d  Total faces: %8d                   \n",buffers.size(),materials.size(),tot_faces);
    warning_done_y=false;
    warning_done_z=false;
    warning_done_x=false;
    warning_done_y_min=false;
    warning_done_z_min=false;
    warning_done_x_min=false;
    warning_done_topping=false;

    return 1;
}


hit_one_region* findRegion(int x, int z) {
    for (int n=0; n<vector_hit_regions.size(); n++) {
        if (vector_hit_regions[n].x == x && vector_hit_regions[n].z == z) {
            return &vector_hit_regions[n];
        }
    }
//    for (auto it = vector_hit_regions.begin(); it != vector_hit_regions.end(); it++) {
//        if (it->x == x && it->z == z) {
//            return &(*it);
//        }
//    }
    return NULL;
}

int region_floor;

void WUPPIE_SUBS(std::vector<BufferObject> buffers, std::vector<tinyobj::material_t> &materials, float bmin_o[3], float bmax_o[3], double lat, double lon, std::string fn) {
    if (area=="Models") adapt_colors=false;
    else adapt_colors=true;
//printf("I am here 1\n");

    random_pixel=sf::Color(64+rand()%64,64+rand()%64,64+rand()%64,255);
    wuppie_all=false;
    FILE* voxel_file_pointer=NULL;
    bool plot_only_on=false;
    if (!plot_only) {

//        printf("CREATING ARRAY 512*256*512*4 = %d BYTES:",512*256*512*4);
//        region_block = (unsigned char*) malloc(512*256*512*4);
//        printf("CLEARING REGION BLOCK: ");
        std::memset(region_block, 0x0, 512*256*512*4);
//        printf(" OK\n");
    } else {
        plot_only_on=true;
    }

//    static int first=1;
    vector_hit_regions.clear();
//FOKIT
//    first_wuppie=0;
    if (first_wuppie==1) {
        first_wuppie=0;
//        for (int z=0; z<1000; z++) {
//            for (int x=0; x<1000; x++) {
//                hit_regions[x][z][11]=0;
//                region_counter[x][z]=0;
//            }
//        }
        DIR* dr = opendir("/saves/test/region/done0");
        struct dirent *de;
//sukkel
        if (!rot_on && !make_schematic && !plot_only_on && (mirror==3 || mirror==4)) {
            printf("SCANNING REGIONS:\n");
            int x,z;
            char picture_file[200];
            while ((de = readdir(dr)) != NULL) {
                if ((strstr(de->d_name, ".mca")) != NULL) {
    //                printf(de->d_name);
                    printf("\r%s      ",de->d_name);
                    if (!flushing) {
                        sscanf(de->d_name,"r.%d.%d.mca",&x,&z);
//                        printf("r.%d.%d.mca ",x,z);
                        if (mirror==4) {
                            sprintf(picture_file,"../cut/r.%d.%d.png",x,z);
                            if (file_exists(picture_file)) {
                                scan_image.loadFromFile(picture_file);
                                plot_only=1;
                                plotting=3;
                                scan_x=x;
                                scan_z=z;
                                sprintf(mc_text1,"R.%d.%d.MCA",x,z);
                                update_request=2;
                                while (update_request) {
                                    sf::sleep(sf::seconds(0.005));
                                }
                                plotting=0;
                            } else {
                                printf("\r%s ",de->d_name);
                                scan_image.create(512,512,sf::Color(128,128,128,128));
                                plotting=1;
//                                plot_only=1;
                                MCEDITOR_running=1;
                                main_mceditor6_fixed(x, z, region_block);
                                MCEDITOR_running=0;
                                plotting=0;
                            }
                        } else if (mirror==3) {
                            scan_image.create(512,512,sf::Color(128,128,128,128));
                            plotting=1;
                            plot_only=1;
                            MCEDITOR_running=1;
                            main_mceditor6_fixed(x, z, region_block);
                            MCEDITOR_running=0;
                            plotting=0;
                        }
                        plot_only=0;
                    }
                    hit_one_region* hit_one=findRegion(x,z);
                    if (hit_one==NULL) {
                        vector_hit_regions.push_back(hit_one_region(x,z));
                        hit_one=&vector_hit_regions[vector_hit_regions.size()-1];
                    }
//fokit
                    hit_one->index11=1;
//                    else hit_one->index11=0;
//                    hit_one->index11=1;
                    hit_one->index12=1;

//                    hit_regions[x][z][11]=1;
//                    region_counter[x][z]=1;
                }
            }
        }
        closedir(dr);
        printf("\n");
        if (mirror==3) {
//            free(region_block);
            return;
        }
    }

    FILE* dummy;
    char new_file_raw[100];
    char new_file_dat[100];

//    BufferObject one_buffer;
    size_t count=0;

    if (!dont_clear) voxels.clear();
    char new_name[200];
    char new_name2[200];

    sprintf(new_name,"../cut/%s.info",fn.c_str());
    sprintf(new_name2,"../cut/done/%s.info",fn.c_str());
//    mkdir(new_name);
//Amsterdam
//    std::vector<BufferObject> buffers_sub;
//    for (std::vector<BufferObject>::iterator it=buffers.begin(), end = buffers.end(); it != end; ++it) {
//        one_buffer=*it;
//        buffers_sub.push_back(one_buffer);
//        count++;
//    }

    printf("%s\n",fn.c_str());

    int ret=2;
//loaded flushed file.vox
    if (buffers.size()==0) ret=3;

/*
    static int box_x;
    static int box_y;
    static int box_z;

    static int box_x_block_start;
    static int box_y_block_start;
    static int box_z_block_start;

    static int box_x_block_end;
    static int box_y_block_end;
    static int box_z_block_end;

    static int box_x_total_start;
    static int box_y_total_start;
    static int box_z_total_start;

    static int box_x_total_end;
    static int box_y_total_end;
    static int box_z_total_end;
*/
    bool do_model=false;
//    if (crossing==0) {
    if (area=="Models") {
        do_model=true;
    }


//    if (!flushing && ret==2)
    if (ret==2)
        ret=WUPPIE_VECTOR(buffers, materials, bmin_o, bmax_o, lat, lon, fn);

    if (ret==-1) {
        printf("ERROR %s\n",fn.c_str());
//        free(region_block);
        return;
    } else if (ret==0) {
        printf("File exists, skipping\n");
//        free(region_block);
        return;
    } else if (ret!=2) {
//        printf("voxels[0] = SIZE:        X=%6d, Y=%6d, Z=%6d\n", voxels[0].x, voxels[0].y, voxels[0].z );
//        printf("voxels[1] = START:       X=%6d, Y=%6d, Z=%6d\n", voxels[1].x, voxels[1].y, voxels[1].z );
//        printf("voxels[2] = END:         X=%6d, Y=%6d, Z=%6d\n", voxels[2].x, voxels[2].y, voxels[2].z );
//        printf("voxels[3] = TOTAL START: X=%6d, Y=%6d, Z=%6d\n", voxels[3].x, voxels[3].y, voxels[3].z );
//        printf("voxels[4] = TOTAL END:   X=%6d, Y=%6d, Z=%6d\n", voxels[4].x, voxels[4].y, voxels[4].z );

/*
        if (ret==1) {
            box_x=voxels[0].x; box_x_block_start=voxels[1].x; box_x_block_end=voxels[2].x; box_x_total_start=voxels[3].x; box_x_total_end=voxels[4].x;
            box_y=voxels[0].y; box_y_block_start=voxels[1].y; box_y_block_end=voxels[2].y; box_y_total_start=voxels[3].y; box_y_total_end=voxels[4].y;
            box_z=voxels[0].z; box_z_block_start=voxels[1].z; box_z_block_end=voxels[2].z; box_z_total_start=voxels[3].z; box_z_total_end=voxels[4].z;
        }
*/
//        int count=0;

        printf("\n");
        printf("NEW NUMBER OF VOXELS                 %9d  ",voxels.size());

        if (skip_sorting) return;
        size_t total_hits=0;
extern int picturex;
extern int picturey;
extern int posx;
extern int posy;
extern double smooth_x;
extern double smooth_y;
extern float fspeedx;
extern float fspeedy;
extern int *pos_ghostx;
extern int *pos_ghosty;
extern int maxpixelsx;
extern int maxpixelsy;
extern float* fspeed_ghostx;
extern float* fspeed_ghosty;
        int mazemovex=0;
        int mazemovey=0;
        if (rot_on && hold_voxels) {
        }

        for (size_t count=0; count<voxels.size(); count++ ) {
            total_hits+=voxels[count].l;
            voxels[count].y+=mazemovex;
            voxels[count].z+=mazemovey;
            if (voxels[count].status==1) {
                voxels[count].status==0;
            }
        }
        region_offset_x=new_region_offset_x;
        printf("NEW NUMBER OF HITS:                  %9d  ",total_hits);
        if (voxels.size()>0) printf("HITS/VOXEL=%f",(double)total_hits/(double)voxels.size());
        printf("\n");
//        if (skip_sorting) return;

        std::vector<Voxel> voxels_temp;
        if (voxels.size()>0) {
//            printf("SORTING VOXELS TO TEMP: ");
            sort(voxels.begin(), voxels.end());
//            printf("Ok. TOTAL/AVERAGE/COMPRESS: ");
            Voxel last=voxels[5];
            Voxel total_pos=Voxel(last.x,last.y,last.z,0,0,0,0,0);

            for (size_t n=0; n<voxels.size(); n++) {
                if (last.x==voxels[n].x && last.y==voxels[n].y && last.z==voxels[n].z) {
                    total_pos.r+=voxels[n].r;
                    total_pos.g+=voxels[n].g;
                    total_pos.b+=voxels[n].b;
                    total_pos.l+=voxels[n].l;
                    if (n==voxels.size()-1) {
                        total_pos.status=0; //new
                        voxels_temp.push_back(total_pos);
                    }
                } else {
                    total_pos.status=0; //new
                    voxels_temp.push_back(total_pos);
                    last=voxels[n];
                    total_pos=last;
                    if (n==voxels.size()-1) {
                        total_pos.status=0; //new
                        voxels_temp.push_back(total_pos);
                    }
                }
            }
        }

        if (make_schematic) {
            printf("Writing voxels to %s.schematic: ",fn.c_str());
            make_schematic_nbt(fn, voxels_temp, 0,voxels_temp.size());
            voxels.clear();
            voxels_total.clear();
//            printf("Ok!\n");
            return;
        }

//        printf("\n");
        printf("SORTED NUMBER OF NEW VOXELS:         %9d  ",voxels_temp.size());
        total_hits=0;
        for (auto u : voxels_temp) {
            total_hits+=u.l;
        }
        printf("SORTED NUMBER OF NEW HITS:           %9d  ",total_hits);
        if (voxels_temp.size()>0) printf("HITS/VOXEL=%f\n",(double)total_hits/(double)voxels_temp.size());
        else printf ("\n");


        printf("TOTAL NUMBER OF VOXELS:              %9d  ",voxels_total.size());
        total_hits=0;
        for (auto u : voxels_total) {
            total_hits+=u.l;
        }
        printf("TOTAL NUMBER OF HITS:                %9d  ",total_hits);
        if (voxels_total.size()>0) printf("HITS/VOXEL=%f",(double)total_hits/(double)voxels_total.size());
        printf("\n");

//        printf("ADDING TOTAL! VOXELS TO TEMP! VOXELS:  ");
        Voxel one;
        for (auto u : voxels_total) {
            one=u;
            voxels_temp.push_back(one);
        }
//        printf("CLEARING TOTAL: ");
        voxels_total.clear();
//        printf("OK.\n");

        printf("NEW TOTAL NUMBER OF VOXELS:          %9d  ",voxels_temp.size());
        total_hits=0;
        for (auto u : voxels_temp) {
            total_hits+=u.l;
        }
        printf("NEW TOTAL NUMBER OF HITS:            %9d  ",total_hits);
        if (voxels_temp.size()>0) printf("HITS/VOXEL=%f",(double)total_hits/(double)voxels_temp.size());
        printf("\n");

        size_t pixel_adds=0;
        if (voxels_temp.size()>0) {
//            printf("SORTING BOTH VOXELS BACK TO TOTAL VOXELS: ");
            sort(voxels_temp.begin(), voxels_temp.end());
//            printf("Ok. TOTAL/AVERAGE/COMPRESS: ");
            Voxel last=voxels_temp[0];
            Voxel total_pos=Voxel(last.x,last.y,last.z,0,0,0,0,last.status);
            for (size_t n=0; n<voxels_temp.size(); n++) {
                if (last.x==voxels_temp[n].x && last.y==voxels_temp[n].y && last.z==voxels_temp[n].z) {
                    total_pos.r+=voxels_temp[n].r;
                    total_pos.g+=voxels_temp[n].g;
                    total_pos.b+=voxels_temp[n].b;
                    total_pos.l+=voxels_temp[n].l;
                    if (voxels_temp[n].status != total_pos.status==0) pixel_adds++;
                    if (voxels_temp[n].status==0) total_pos.status=0;
                    if (n==voxels_temp.size()-1) {
                        voxels_total.push_back(total_pos);
                    }
                } else {
                    voxels_total.push_back(total_pos);
                    last=voxels_temp[n];
                    total_pos=last;
                    if (n==voxels_temp.size()-1) {
                        voxels_total.push_back(total_pos);
                    }
                }
            }
        }


//        printf("\n");
        printf("SORTED NEW TOTAL NUMBER OF VOXELS:   %9d  ",voxels_total.size());
        total_hits=0;
        for (auto u : voxels_total) {
            total_hits+=u.l;
        }
        printf("SORTED NEW TOTAL NUMBER OF HITS:     %9d  ",total_hits);
        if (voxels_total.size()>0) printf("HITS/VOXEL=%f  ",(double)total_hits/(double)voxels_total.size());
        if (pixel_adds>0) printf(" PIXEL ADDS: %d" ,pixel_adds);
        printf ("\n");


/*
        printf("\n");
        count=0;
        int rx=0, rx_prev=-1;
        int rz=0, rz_prev=-1;
        for (auto u : voxels_total) {
            rx=u.y/512;
            rz=u.z/512;
            if (rx_prev!=rx || rz_prev!=rz) printf("srt:region[%3d][%3d] POS[%3d][%4d][%3d] voxels_total[%5d]=Voxel(%6d,%6d,%6d,%4d,%4d,%4d,%4d)\n",
                   u.y/512,u.z/512, (((LONG64)u.y+100000*512)%512) ,u.x,(((LONG64)u.z+100000*512)%512)  , count++,u.x,u.y,u.z,u.r,u.g,u.b,u.l);
            rx_prev=rx;
            rz_prev=rz;
        }
*/

//        printf("SCANNING REGIONS:\n");
        for (int n=0; n < vector_hit_regions.size(); n++) {
            vector_hit_regions[n].index6=0;
            vector_hit_regions[n].index7=0;
            vector_hit_regions[n].index8=0;
            vector_hit_regions[n].index9=0;
            vector_hit_regions[n].index10=0;
            char mca_file[200];
            sprintf(mca_file,"/saves/test/region/done0/r.%d.%d.mca",vector_hit_regions[n].x,vector_hit_regions[n].z);
            if (file_exists(mca_file)) vector_hit_regions[n].index11=1;
            else vector_hit_regions[n].index11=0;
//            vector_hit_regions[n].index11=0;
        }
//        for (int z=0; z<1000; z++) {
//            for (int x=0; x<1000; x++) {
//                hit_regions[x][z][0]=std::numeric_limits<int>::max();
//                hit_regions[x][z][1]=-std::numeric_limits<int>::max();
//                hit_regions[x][z][2]=std::numeric_limits<int>::max();
//                hit_regions[x][z][3]=-std::numeric_limits<int>::max();
//                hit_regions[x][z][4]=std::numeric_limits<int>::max();
//                hit_regions[x][z][5]=-std::numeric_limits<int>::max();
//                hit_regions[x][z][6]=0;
//                hit_regions[x][z][7]=0;
//                hit_regions[x][z][8]=0;
//                hit_regions[x][z][9]=0;
//                hit_regions[x][z][10]=0;
//            }
//        }
        int one_region[512][512];
        for (int zz=0; zz<512; zz++) {
            for (int xx=0; xx<512; xx++) {
                one_region[xx][zz]=0;
            }
        }

        if (voxels_total.size()>0) {
            int min_x=std::numeric_limits<int>::max();
            int max_x=-std::numeric_limits<int>::max();
            int min_y=std::numeric_limits<int>::max();
            int max_y=-std::numeric_limits<int>::max();
            int min_z=std::numeric_limits<int>::max();
            int max_z=-std::numeric_limits<int>::max();
            int rx,rz;
            Voxel one=voxels_total[0];
            bool plot_region=false;
//            if (one.status==0) {
//                plot_region=true;
//            }
            int y=one.y,z=one.z;
            rx=y/512;
            rz=z/512;

            Voxel prev;
            int rx_prev;
            int rz_prev;

            size_t total_voxels_column=0;
            size_t num_voxels=voxels_total.size();
            size_t voxel_index=0;
//            size_t total_voxels_region=0;
            size_t total_hits_region=0;
            size_t total_voxels_all_regions=0;
            size_t total_hits_all_regions=0;
//            for (auto u : voxels_total) {
            size_t n=0;
//            printf("\n");
//            printf("region[%3d][%3d] POS[%3d][%3d][%3d] voxels_total[%3d]=Voxel(%6d,%6d,%6d,%4d,%4d,%4d,%4d)\n",
//                   rx,rz,one.y%512,one.x,one.z%512,n,one.x,one.y,one.z,one.r,one.g,one.b,one.l);
            while (n<voxels_total.size()) {
                prev=one;
                rx_prev=rx; rz_prev=rz;

                int prev_xx=-1;
                scan_image.create(512,512,sf::Color(0,0,0,0));
                bool xz00=false,xz01=false,xz10=false,xz11=false;
                size_t new_hits_region=0;
                size_t total_voxels_region=0;
                int total_columns=0;
//                total_voxels_region=0;
                while (rx==rx_prev && rz==rz_prev && n<voxels_total.size()) {
                    prev=one;
                    rx_prev=rx; rz_prev=rz;
                    while (y==prev.y && z==prev.z && n<voxels_total.size()) {
                        if (prev.status==0) {
//                            plot_region=true; //new blocks....update region file. if exists....
                            new_hits_region++;
                        }
                        total_voxels_column++;
                        total_hits_region+=one.l;
                        prev=one;
                        rx_prev=rx; rz_prev=rz;
                        n++;
                        if (n<voxels_total.size()) {
                            one=voxels_total[n];
                            y=one.y; z=one.z; rx=y/512; rz=z/512;
//                            printf("region[%3d][%3d] POS[%3d][%3d][%3d] voxels_total[%3d]=Voxel(%6d,%6d,%6d,%4d,%4d,%4d,%4d)\n",
//                                   rx,rz,one.y%512,one.x,one.z%512,n,one.x,one.y,one.z,one.r,one.g,one.b,one.l);
                        }
                    }
                    total_columns++;
//hopla
//                    int prev_y_mod=prev.y%512;
//                    int prev_z_mod=prev.z%512;
                    int prev_y_mod;
                    if (prev.y>=0)
                        prev_y_mod=(int)(((LONG64)prev.y+100000*512)%512);
                    else
                        prev_y_mod=(int)(((LONG64)prev.y-1+100000*512)%512);

                    int prev_z_mod;
                    if (prev.z>=0)
                        prev_z_mod=(int)(((LONG64)prev.z+100000*512)%512);
                    else
                        prev_z_mod=(int)(((LONG64)prev.z-1+100000*512)%512);
//                        prev_z_mod=(int)(((LONG64)prev.z+100000*512)%512);
                    if (!xz00 && prev_y_mod==  0 && prev_z_mod==  0) xz00=true;
                    if (!xz01 && prev_y_mod==  0 && prev_z_mod==511) xz01=true;
                    if (!xz10 && prev_y_mod==511 && prev_z_mod==  0) xz10=true;
                    if (!xz11 && prev_y_mod==511 && prev_z_mod==511) xz11=true;
                    one_region[prev_y_mod][prev_z_mod]=total_voxels_column;
                    total_voxels_region+=total_voxels_column;
                    scan_image.setPixel(prev_y_mod , prev_z_mod,sf::Color(prev.r/prev.l,prev.g/prev.l,prev.b/prev.l,255));
                    if (plot_region==false && prev.status==0) { // new top block.... display top view.
                        plot_region=true;
                    }

   //                 if (rx!=rx_prev || rz!=rz_prev) {
//                        printf("region[%3d][%3d] total_column[%4d][%4d][%4d]=%3d total_culumns=%8d =%6.2f%%\r",
//                               rx_prev,rz_prev,
//                               prev_y_mod,prev.x,prev_z_mod,
//                               total_voxels_column,
//                               total_columns,
//                               100.0*(float)total_columns/(512.0*512.0));

 //                   }

                    prev_xx=prev.y;
                    total_voxels_column=0;
                    min_x=std::min(min_x,prev.x);
                    max_x=std::max(max_x,prev.x);
                    min_y=std::min( min_y , prev_y_mod );
                    max_y=std::max( max_y , prev_y_mod );
                    min_z=std::min( min_z , prev_z_mod );
                    max_z=std::max( max_z , prev_z_mod );
                }
                hit_one_region* hit_one=findRegion(rx_prev,rz_prev);
                if (hit_one==NULL) {
                    vector_hit_regions.push_back(hit_one_region(rx_prev,rz_prev));
                    hit_one=&vector_hit_regions[vector_hit_regions.size()-1];
                    char mca_file[200];
                    sprintf(mca_file,"/saves/test/region/done0/r.%d.%d.mca",hit_one->x,hit_one->z);
                    if (file_exists(mca_file)) hit_one->index11=1;
                    else hit_one->index11=0;

//                    hit_one->index11=0;
//                    hit_one=&(*vector_hit_regions.end());
                }

                if (new_hits_region) {
//                    if (!flushing) {
//                    if (!flushing || plot_only) {
//                    if (!flushing || plot_only || area=="Models") {
                    if (1) {
                        scan_x=rx_prev;
                        scan_z=rz_prev;
                        sprintf(mc_text1,"R.%d.%d.MCA",scan_x,scan_z);
                        sprintf(mc_text2,"%s %7d HITS",fn.c_str(),new_hits_region);

                        if (hit_one->index11 == 0)
                            plotting=1;
                        else
                            plotting=3;

//                        if (hit_regions[rx_prev][rz_prev][11]==0)
//                            plotting=1;
//                        else
//                            plotting=3;

//                        printf("\nPlotting: %s\n",mc_text1);
                        update_request=2;
                        while (update_request) {
                            sf::sleep(sf::seconds(0.005));
                        }
                    } else {
                        scan_image.create(512,512,sf::Color(0,0,0,0));
                    }
//                    region_counter[rx_prev][rz_prev]++;
                    hit_one->index12++;
                }
                hit_one->index0=min_x;
                hit_one->index1=max_x;
                hit_one->index2=min_y;
                hit_one->index3=max_y;
                hit_one->index4=min_z;
                hit_one->index5=max_z;
                hit_one->index6=total_voxels_region;
                hit_one->index7=total_hits_region;
                hit_one->index8=total_columns;
                if (xz00 && xz01 && xz10 && xz11) hit_one->index9=1;
                else hit_one->index9=0;
                hit_one->index10=new_hits_region;

                plot_region=false;

                printf("\rREGION [%3d][%3d] ",rx_prev,rz_prev);
                total_columns=0;
                int total_voxels=0;
                int tline=0;
                for (int zz=0; zz<512; zz++) {
                    for (int xx=0; xx<512; xx++) {
                        if (one_region[xx][zz]>0) {
                            if (zz==0 || zz==511) tline++;
                            if (xx==0 || xx==511) tline++;
                            total_columns++;
                            total_voxels+=one_region[xx][zz];
                        }
                        one_region[xx][zz]=0;
                    }
                }
                if (tline==2048) hit_one->index8=512*512;

                printf("NEW VOXELS=%7d  VOXELS=%9d  ", hit_one->index10, total_voxels);
                printf("%7d  ", total_voxels_region);
                printf("HITS=%10d  ", total_hits_region);
                printf("RR=[%3d-%3d] Y=[%4d-%4d] ZZ=[%3d-%3d]  ",min_y,max_y,min_x,max_x,min_z,max_z);
                if (total_voxels_region!=0) printf("HITS/VOXEL=%6.2f  ", (double)total_hits_region/(double)total_voxels_region );
                else printf("HITS/VOXEL=%6.2f  ",0.0);
                printf("COLUMNS=%6d (%6.2f%%)\r", total_columns,100.0*(double)total_columns/(512.0*512.0) );

                total_voxels_all_regions+=total_voxels_region;
//                total_voxels_region=0;
                total_hits_all_regions+=total_hits_region;
                total_hits_region=0;
                min_x=std::numeric_limits<int>::max();
                max_x=-std::numeric_limits<int>::max();
                min_y=std::numeric_limits<int>::max();
                max_y=-std::numeric_limits<int>::max();
                min_z=std::numeric_limits<int>::max();
                max_z=-std::numeric_limits<int>::max();
//                printf("\n");

                voxel_index++;
            }

            printf("\r");
            printf("TOTAL VOXELS:                        %9d  ",total_voxels_all_regions);
            printf("TOTAL HITS:                         %10d  ",total_hits_all_regions);
            printf("HITS/VOXEL=%f                                                              \n", (double)total_hits_all_regions/(double)total_voxels_all_regions );

            total_voxels_all_regions=0;
            total_hits_all_regions=0;
            int total_columns_all_regions=0;
            printf("TESTING HIT REGIONS:\n");
            int NUMBER_OF_REGIONS=0;
            for (int n=0; n < vector_hit_regions.size(); n++) {
                hit_one_region* hit_one=&vector_hit_regions[n];
                int x=hit_one->x;
                int z=hit_one->z;
                if (hit_one->index6>0) {
                    NUMBER_OF_REGIONS++;
                    printf("REGION [%3d][%3d]  ",x,z);
                    printf("VOXELS=%9d (%6.2f%%)  ", hit_one->index6,100.0*(double)hit_one->index6/(512.0*512.0*256.0));

                    printf("RR=[%3d-%3d] Y=[%4d-%4d] ZZ=[%3d-%3d]  ",
                            hit_one->index2,hit_one->index3,
                            hit_one->index0,hit_one->index1,
                            hit_one->index4,hit_one->index5);

                    printf("COLUMNS=%6d (%6.2f%%)  ", hit_one->index8,100.0*(double)hit_one->index8/(512.0*512.0));
                    printf("NEW VOXELS=%7d  ", hit_one->index10);
                    printf("HITS=%10d HITS/VOXEL=%6.2f  ", hit_one->index7, (double)hit_one->index7/(double)hit_one->index6);

                    if (hit_one->index2==0 && hit_one->index3==511) printf("X+"); else printf("  ");
                    if (hit_one->index4==0 && hit_one->index5==511) printf("Z+"); else printf("  ");
                    if (hit_one->index11) printf(" SAVED");
                    else printf(" HOLD ");
                    if (hit_one->index8==512*512) printf(" COLUMNS=100%%");
                    if (hit_one->index9) printf(" CORNERS=4");
                    if (hit_one->index6!=hit_one->index10 && hit_one->index10!=0) {
                        printf(" NEW=%d",hit_one->index10);
                    }
                    printf("\n");
                    total_voxels_all_regions+=hit_one->index6;
                    total_hits_all_regions+=hit_one->index7;
                    total_columns_all_regions+=hit_one->index8;
                }
            }

            printf("TOTAL VOXELS:                        %9d  ",total_voxels_all_regions);
            printf("TOTAL HITS:                         %10d  ", total_hits_all_regions);
            printf("HITS/VOXEL=%f  ", (double)total_hits_all_regions/(double)total_voxels_all_regions );
            printf("AVG COLUMNS/REGION=%6.2f%%\n", 100.0*(double)total_columns_all_regions/(512*512*NUMBER_OF_REGIONS) );
            printf("NEW NUMBER OF TOTAL VOXELS:          %9d  ",voxels_total.size());
            total_hits=0;
            int total_new=0;
            for (int n=0; n<voxels_total.size(); n++) {
                if (voxels_total[n].status==0) {
                    voxels_total[n].status=1;
                    total_new++;
                }
                total_hits+=voxels_temp[n].l;
            }
            printf("NEW NUMBER OF TOTAL HITS:           %10d\n",total_hits);
            printf("TOTAL NEW VOXELS:                    %9d\n",total_new);
        }

        printf("%3d buffers. Ready.\n",buffers.size());
    }

//change
    if (voxels_total.size()>20000000 && !rot_plot) { flushing_mode=true; make_regions=true; }
    if (!hold_voxels || (flushing_mode)) {
//    if (!hold_voxels || (voxels_total.size()>20000000 && !rot_plot)) {
        if (voxels_total.size()>0) {
    //        if (voxels_total.size()>200000000) flushing=true;
            if (flushing) printf("FLUSHING:\n");
            int NUMBER_OF_REGIONS=0;

            sort(vector_hit_regions.begin(), vector_hit_regions.end()); // sort on number of columns (int)(512.0*512.0*0.9995) (flushing to voxel files first).
            for (int n=0; n < vector_hit_regions.size(); n++) {         // fok! exept not flushing region voxel files... hmmm

                hit_one_region* hit_one=&vector_hit_regions[n];

                int x=hit_one->x;
                int z=hit_one->z;

                bool got_one=false;
                if (flushing_mode) {
                    int n;
                    for (n=0; n<ready_regions.size(); n++) {
//                        printf("SCANNING READY REGIONs: [%d][%d]",ready_regions[n].x,ready_regions[n].z);
                        if (ready_regions[n].x==x && ready_regions[n].z==z) {
                            printf(" HIT FOUND! ");
                            if (make_region_from_voxel(x,z)) {
                                printf(" AND LOADED!");
                                if (cubic) sort_cubic=true;
                                sort(voxels_total.begin(), voxels_total.end());
                                sort_cubic=false;
                                if (!cubic) printf(" SORTED!!!");
                                else  printf(" SORTED CUBIC!!!");
                            } else {
                                printf(" NO VOXELFILE.");
                                if (cubic) {
                                    sort_cubic=true;
                                    sort(voxels_total.begin(), voxels_total.end());
                                    sort_cubic=false;
                                    printf(" SORTED CUBIC!!!");
                                }
                            }
                            got_one=true;
//huh
                            printf("\n");
                        }
                        if (got_one) break;
                    }
                    if (got_one) ready_regions.erase(ready_regions.begin()+n,ready_regions.begin()+n+1);
                }
                if (hit_one->index8 > (int)(512.0*512.0*0.999) || flushing ) {
                    if (!got_one) {
                        if (make_region_from_voxel(x,z)) {
                            printf("LOADED VOXEL FILE!");
                            if (cubic) sort_cubic=true;
                            sort(voxels_total.begin(), voxels_total.end());
                            sort_cubic=false;
                            if (!cubic) printf(" SORTED!!!");
                            else  printf(" SORTED CUBIC!!!");
                        } else {
                            printf(" NO VOXELFILE.");
                            if (cubic) {
                                sort_cubic=true;
                                sort(voxels_total.begin(), voxels_total.end());
                                sort_cubic=false;
                                printf(" SORTED CUBIC!!!");
                            }
                        }
                    }
                    got_one=true;
                }
                if (hit_one->index6>0 || got_one) {
                    NUMBER_OF_REGIONS++;
                    if ((flushing_mode) || hit_one->index8 > (int)(512.0*512.0*0.999) || flushing ) {
//                    if ((voxels_total.size()>25000000) || hit_one->index8 > (int)(512.0*512.0*0.9995) || flushing ) {

                        if (flushing_mode && !got_one)
                            printf("FLUSHING MODE:  [%3d][%3d]  ",x,z);
                        else if (hit_one->index11)
                            printf("UPDATING REGION [%3d][%3d]  ",x,z);
                        else
                            printf("CREATING REGION [%3d][%3d]  ",x,z);
                        if (hit_one->index8==512*512) printf(" COLUMNS=100%% ");
                        if (hit_one->index9) printf(" 4 CORNERS ");
                        printf("\n");
                        int first=-1;
                        size_t hits=0;
                        size_t voxels=0;
                        size_t count=0;
                        size_t columns=0;
                        size_t prev_x=-99999999,prev_z=-99999999;
                        size_t TOP_MIN=0;
                        size_t TOP_MAX=230;
                        size_t TOPPED_MIN=0;
                        size_t TOPPED_MAX=0;
                        int floor=0;
                        int num_floors=0;
                        bool NEXT_FLOOR=false;
                        region_floor=0;
//change
//floors
                        std::memset(region_block, 0x0, 512*256*512*4);
//                        if (!plot_only_on) std::memset(region_block, 0x0, 512*256*512*4);

                        for (auto u : voxels_total) {

                            if ( (int)(u.y/512)==x && (int)(u.z/512)==z ) {

                                if (prev_x!=u.y || prev_z!=u.z) columns++;
//tuuttuut
//                                prev_x=u.y; prev_z=u.z;

                                if (first==-1) {
                                    first=count;
                                    floor=(int)((u.x)/256);
                                    if (u.x<0) floor--;
                                    num_floors++;
                                    region_floor=floor;
                                    prev_x=u.y; prev_z=u.z;
                                }
                                if ( (u.x>=0 && (int)(u.x/256)!=floor) || (u.x<0 && (int)(u.x/256)-1 != floor) ) {
                                    NEXT_FLOOR=true;
                                    num_floors++;
                                }

                                hits+=u.l;

                                if (!(voxels%4096)) printf("count=%d  first=%d  voxels=%d  hits=%d  columns=%d (%6.2f%%)\r",
                                                          count, first, voxels, hits, columns, 100.0*(double)columns/(512.0*512.0));
//change
                                if ((!plot_only_on && !flushing_mode) || got_one) {
//                                if (!plot_only_on) {

                                    int prev_y_mod;
                                    int prev_z_mod;
                                    if (cubic) {
                                        if (NEXT_FLOOR) {
                                            region_floor=floor;

                                            if (voxels==0 || hits==0 || first==-1 || count==0) {
                                                printf("\n1) ERROR: count=%d  first=%d  voxels=%d  hits=%d\n",count, first, voxels, hits);
                                            } else {
                                                printf("\r1) TOTAL: VOXELS %d  HITS: %d  FROM %d to %d  COLUMNS: %d (%6.2f%%)  Creating region file r.%d.%d.mca floor %d\n",
                                                       voxels, hits, first, first+voxels, columns, 100.0*(double)columns/(512.0*512.0), x,z,region_floor);
                                                plotting=0;

                                                sprintf(mc_text2,"SAVING %d",region_floor);
//                                                hit_one->index12=0;

                                                if ((!plot_only_on && !flushing_mode) || got_one) {
                                                    MCEDITOR_running=1;
                    //                                add_to_region=true;
                                                    if (got_one) no_plotting=true;
                                                    main_mceditor6_fixed(x,z,region_block);
                                                    printf("Finished region r.%d.%d floor %d\n",x,z,region_floor);
                                                    if (got_one) no_plotting=false;
                    //                                add_to_region=false;
                                                    MCEDITOR_running=0;
                                                }
                                                hits=0;
                                                count=0;
                                            }

                                            std::memset(region_block, 0x0, 512*256*512*4);

                                            floor=(int)((u.x)/256);
                                            if (u.x<0) floor--;
                                            region_floor=floor;
                                            NEXT_FLOOR=false;
                                        }
                                        if (u.y>=0)
                                            prev_y_mod=(int)(((LONG64)u.y+100000*512)%512);
                                        else
                                            prev_y_mod=(int)(((LONG64)u.y-1+100000*512)%512);

                                        if (u.z>=0)
                                            prev_z_mod=(int)(((LONG64)u.z+100000*512)%512);
                                        else
                                            prev_z_mod=(int)(((LONG64)u.z-1+100000*512)%512);

                                        if (u.l>0) {
                                            size_t off_x=(u.x-floor*256+256*prev_y_mod+prev_z_mod*512*256)*4;
                                            region_block[off_x]=u.r/u.l;
                                            region_block[off_x+1]=u.g/u.l;
                                            region_block[off_x+2]=u.b/u.l;
                                            region_block[off_x+3]=u.l;
                                        } else {
                                            printf("ERROR: u.l=0\n");
                                        }
                                    } else {

                                        if (u.y>=0)
                                            prev_y_mod=(int)(((LONG64)u.y+100000*512)%512);
                                        else
                                            prev_y_mod=(int)(((LONG64)u.y-1+100000*512)%512);

                                        if (u.z>=0)
                                            prev_z_mod=(int)(((LONG64)u.z+100000*512)%512);
                                        else
                                            prev_z_mod=(int)(((LONG64)u.z-1+100000*512)%512);

                                        if (u.x>=0 && u.x<230 && u.l>0) {
                                            size_t off_x=(u.x+256*prev_y_mod+prev_z_mod*512*256)*4;
                                            region_block[off_x]=u.r/u.l;
                                            region_block[off_x+1]=u.g/u.l;
                                            region_block[off_x+2]=u.b/u.l;
                                            region_block[off_x+3]=u.l;
                                        } else if (u.l>0) {
                                            if (u.x<1) {
                                                if (u.x<TOP_MIN) TOP_MIN=u.x;
                                                TOPPED_MIN++;
                                                size_t off_x=(1+256*prev_y_mod+prev_z_mod*512*256)*4;
                                                region_block[off_x]=u.r/u.l;
                                                region_block[off_x+1]=u.g/u.l;
                                                region_block[off_x+2]=u.b/u.l;
                                                region_block[off_x+3]=u.l;
                                            } else if (u.x>=230) {
                                                if (u.x>TOP_MAX) TOP_MAX=u.x;
                                                TOPPED_MAX++;
                                                float togo=u.x-230.0;
                                                float new_real_y=230.0+togo/(1.0+(togo/20.0)); if (new_real_y>=256.0) new_real_y=255.0;
                                                size_t off_x=((int)new_real_y+256*prev_y_mod+prev_z_mod*512*256)*4;
                                                region_block[off_x]=u.r/u.l;
                                                region_block[off_x+1]=u.g/u.l;
                                                region_block[off_x+2]=u.b/u.l;
                                                region_block[off_x+3]=u.l;
                                            }
                                        } else {
                                            printf("ERROR: u.l=0\n");
                                        }
                                    }
                                }
                                voxels++;
                                prev_x=u.y; prev_z=u.z;
                            }
                            count++;
                        }
                        printf("                                                                                                                            \n");
                        if (TOPPED_MIN>0) printf("TOPPED_MIN=%d (MIN=%d)\n",TOPPED_MIN,TOP_MIN);
                        if (TOPPED_MAX>0) printf("TOPPED_MAX=%d (MAX=%d)\n",TOPPED_MAX,TOP_MAX);

                        if (voxels==0 || hits==0 || first==-1 || count==0) {
                            printf("\n2) ERROR: count=%d  first=%d  voxels=%d  hits=%d\n",count, first, voxels, hits);
                        } else {
                            printf("\r2) TOTAL: VOXELS %d  HITS: %d  FROM %d to %d  COLUMNS: %d (%6.2f%%)  Creating region file r.%d.%d.mca floor %d\n",
                                   voxels, hits, first, first+voxels, columns, 100.0*(double)columns/(512.0*512.0), x,z,region_floor);
                            plotting=0;

                            sprintf(mc_text2,"SAVING %d",num_floors);
                            hit_one->index12=0;
//change
//                            char fname[200];
                            if ((!plot_only_on && !flushing_mode) || got_one) {
//                            if (!plot_only_on) {
                                MCEDITOR_running=1;
//                                add_to_region=true;
                                if (got_one) no_plotting=true;

                                main_mceditor6_fixed(x,z,region_block);

                                printf("Finished region r.%d.%d floor %d\n",x,z,floor);

                                if (got_one) no_plotting=false;

//                                add_to_region=false;
                                MCEDITOR_running=0;
                            }

                            char fname[200];
                            char fname2[200];
                            sprintf (fname,"../cut/r.%d.%d.vox",x,z);
//joepie
//                            if (!dont_write_to_region_voxels || got_one) {
                            if (!dont_write_to_region_voxels) {
                                sprintf(fname2,"../cut/done/r.%d.%d.vox",x,z);
                                if (file_exists(fname2)) {
                                    voxel_file_pointer=fopen(fname2,"a");
                                } else {
                                    if (got_one) {
                                        voxel_file_pointer=fopen(fname,"w");
                                    } else {
                                        voxel_file_pointer=fopen(fname,"a");
                                    }
                                }

                                if (voxel_file_pointer==NULL) printf("Error opening file %s for writing\n",fname);
                                else {
                                    printf("Outputing voxels to %s ",fname);
                                    for (int n=first; n<first+voxels; n++) {
                                        Voxel u=voxels_total[n];
                                        if (u.l>0) {
                                            fprintf(voxel_file_pointer,"(%d,%d,%d),(%d,%d,%d),(%d)\n",
                                                    u.y, u.x, u.z,  u.r/u.l,u.g/u.l, u.b/u.l,  u.l );
                                        }
                                        if (!(n%10)) toggle2();
                                    }
                                    fclose(voxel_file_pointer); printf(" Ok.\n");  voxel_file_pointer=NULL;
                                }
                            } else printf("NOT outputing voxels to %s ",fname);

                            FILE* INFO;
                            if (file_exists(new_name2)) {
                                INFO = fopen (new_name2, "a");
                            } else {
                                INFO = fopen (new_name, "a");
                            }
                            if (INFO !=NULL) {
                                fprintf(INFO,"r.%d.%d (%6.2f%%)\n",x,z, 100.0*(double)columns/(512.0*512.0));
                                fclose(INFO);
                            } else {
                                printf("Error opening %s for writing.\n",new_name);
                            }

                            sprintf(fname,"../cut/done/r.%d.%d.info",x,z);
                            if (!file_exists(fname)) {
                                sprintf (fname,"../cut/r.%d.%d.info",x,z);
                            }
                            if ((INFO = fopen (fname, "a"))!=NULL) {
                                fprintf(INFO,"%s\n",fn.c_str());
                                fclose(INFO);
                            } else {
                                printf("Error opening %s for writing.\n",fname);
                            }

                            if ((!plot_only_on && !make_schematic && !hold_voxels && !flushing_mode) || got_one) {
                                char naam[200];
                                mkdir("../cut/done");
                                sprintf (fname,"../cut/r.%d.%d.vox",x,z);
                                if (file_exists(fname)) {
                                    sprintf(naam,"move \"..\\cut\\%s\" ..\\cut\\done\\",fname);
                                    system(naam);
                                }
                                sprintf (fname,"../cut/r.%d.%d.info",x,z);
                                if (file_exists(fname)) {
                                    sprintf(naam,"move \"..\\cut\\%s\" ..\\cut\\done\\",fname);
                                    system(naam);
                                }
                            }

                            printf("Deleting from array: ");
                            printf("Ok.  Erasing region from total voxels:\n");
                            printf("Size voxels_total:     %10d\n",voxels_total.size());
    //                        for(int n=first; n<first+voxels; n++) {
    //                            if (voxels_total[n].y>region_offset_x) region_offset_x=voxels_total[n].y;
    //                        }
                            voxels_total.erase(voxels_total.begin()+first,voxels_total.begin()+first+voxels);
//                            for (auto u = voxels_total.begin()+first; u <= voxels_total.begin()+first+voxels; ++u) {};
//                            for (auto u = voxels_total.begin()+first; u != voxels_total.end(); ++u) {};

                            printf("Erased voxels:         %10d\n",voxels);
                            printf("New size voxels_total: %10d\n",voxels_total.size());
                            printf("New size + voxels:     %10d\n",voxels_total.size()+voxels);
    //                        if (do_model) printf("Offset: %d\n",region_offset_x);
                        }
                    }
                }
            }

            if (voxel_to_file) {
                char fname[200]; sprintf (fname,"../cut/%s.vox",area.c_str());
                voxel_file_pointer=fopen(fname,"w");
                printf("Outputing voxels to %s\n",fname);
                for (auto u : voxels_total) {
                    if (u.l>0 && voxel_to_file) {
                        fprintf(voxel_file_pointer,"(%d,%d,%d),(%d,%d,%d),(%d)\n",
                                u.y, u.x, u.z,  u.r/u.l,u.g/u.l, u.b/u.l,  u.l );
                    }
                }
                if (voxel_file_pointer!=NULL) { fclose(voxel_file_pointer);  voxel_file_pointer=NULL; }
                voxel_to_file=false;
            }
        }
    }
    if (!plot_only_on && !make_schematic && !hold_voxels && !dont_write_to_region_voxels) {
        char naam[200];
        mkdir("../cut/done");
        sprintf(naam,"move \"..\\cut\\%s.*\" ..\\cut\\done\\",fn.c_str());
        system(naam);
    }

//    if (!plot_only_on) free(region_block);
    wuppie_all=true;
    return ;
}

void flush_voxels() {
    if (voxels_total.size()>0 || voxels.size()>0) {
        float minimum[3];
        float maximum[3];
        std::vector<BufferObject> buffers;
        std::vector<tinyobj::material_t> materials;
        flushing=true;
        bool plot_only_o=plot_only;
        plot_only=false;
        dont_clear=true;
        bool skip_sorting_o=skip_sorting;
        skip_sorting=false;
        WUPPIE_SUBS(buffers, materials, minimum, maximum, 0, 0, area);
        skip_sorting=skip_sorting_o;
        dont_clear=false;
        flushing=false;
        plot_only_o=plot_only_o;
    }
}

void flush_voxels_to_region_voxel_files() {
    if (voxels_total.size()>0 || voxels.size()>0) {
        float minimum[3];
        float maximum[3];
        std::vector<BufferObject> buffers;
        std::vector<tinyobj::material_t> materials;
        flushing=true;
        plot_only=true;
        dont_clear=true;
        bool hold_voxels_o=hold_voxels;
        hold_voxels=false;
        bool skip_sorting_o=skip_sorting;
        skip_sorting=false;

        WUPPIE_SUBS(buffers, materials, minimum, maximum, 0, 0, area);
        skip_sorting=skip_sorting_o;
        hold_voxels=hold_voxels_o;
        plot_only=false;
        dont_clear=false;
        flushing=false;
    }
}

void erase_object(Pacman_Object& p);


void voxelize(std::vector<Pacman_Object>& Pacman_Objects) {
    hold_voxels=true;
//    window.setActive(true);
    mirror=4;
    Pacman_Object p;
    for (int n=0; n<Pacman_Objects.size(); n++) {
        p.bmin[0] = p.bmin[1] = p.bmin[2] = std::numeric_limits<float>::max();
        p.bmax[0] = p.bmax[1] = p.bmax[2] = -std::numeric_limits<float>::max();
//        do_wuppie=true;
//        burn=true;
//        crossing=1;
//        mirror=4;
//        plot_only=true;
        if ( n==Pacman_Objects.size()-1 && !rot_on) flushing=true;
//        voxel_to_file=true;
        printf("Voxelizing object %d : %s\n",n,Pacman_Objects[n].filename.c_str());

        do_wuppie=true;
//        burn=true;
        to_gpu=false;
        if (true == LoadObjAndConvert_window(p.bmin, p.bmax, p.gDrawObjects, p.materials, p.textures, (char*) Pacman_Objects[n].filename.c_str())) {
//            printf("p.gDrawObjects.size()=%d\n",p.gDrawObjects.size());
//            printf("p.materials.size()=%d\n",p.materials.size());
//            printf("p.textures.size()=%d\n",p.textures.size());
//            window.setActive(true);
//            printf("Erasing object ");
//            erase_object(p);
            printf("Done\n");
        } else {
            printf("Error...\n");
        }
        to_gpu=true;
    }
    mirror=0;
    flushing=false;
    burn=false;
    hold_voxels=false;
}

void voxelize_shell(std::string filename) {
    std::vector<Pacman_Object> v_po;
    Pacman_Object po;
    po.filename=filename;
    v_po.push_back(po);
    voxelize(v_po);
}

void erase_object(Pacman_Object& p) {
    {
        GLuint gluint_arr[p.textures.size()];
        int num_com=0;
        for (auto u : p.textures) {
            gluint_arr[num_com++]=u.second;
        }
        glDeleteTextures((GLsizei)p.textures.size(), gluint_arr);
    }
    {
        GLuint gluint_arr[p.gDrawObjects.size()];
        int num_com=0;
        for (auto u : p.gDrawObjects) {
            gluint_arr[num_com++]=u.vb_id;
        }
        glDeleteBuffers((GLsizei)p.gDrawObjects.size(), gluint_arr);
    }
    p.gDrawObjects.clear();
    p.materials.clear();
    p.textures.clear();
}

void make_schematic_nbt(std::string fn, std::vector<Voxel>& voxels,size_t first,size_t num_voxels) {

    nbt_tag_t* tag_object;
    tag_object = nbt_new_tag_compound();
    nbt_set_tag_name(tag_object,"Schematic",strlen("Schematic"));

    nbt_tag_t* tag_entities = nbt_new_tag_list(NBT_TYPE_COMPOUND);
    nbt_set_tag_name(tag_entities,(char*)"Entities",strlen("Entities"));
    nbt_tag_compound_append(tag_object,tag_entities);

    nbt_tag_t* tag_tile_entities = nbt_new_tag_list(NBT_TYPE_COMPOUND);
    nbt_set_tag_name(tag_tile_entities,(char*)"TileEntities",strlen("TileEntities"));
    nbt_tag_compound_append(tag_object,tag_tile_entities);

    int min_x=std::numeric_limits<int>::max();
    int max_x=-std::numeric_limits<int>::max();
    int min_y=std::numeric_limits<int>::max();
    int max_y=-std::numeric_limits<int>::max();
    int min_z=std::numeric_limits<int>::max();
    int max_z=-std::numeric_limits<int>::max();
    double color_i_min=255;
    double color_i_max=0;
    for (int n=first; n<first+num_voxels; n++) {
        Voxel* u=&voxels[n];
        if (u->l > 0) {
            min_x=std::min( min_x , u->x);
            max_x=std::max( max_x , u->x);
            min_y=std::min( min_y , u->y);
            max_y=std::max( max_y , u->y);
            min_z=std::min( min_z , u->z);
            max_z=std::max( max_z , u->z);
            double color_i=((float)u->r/(float)u->l + (float)u->g/(float)u->l + (float)u->b/(float)u->l)/3.0;
            if (color_i > color_i_max) color_i_max=color_i;
            if (color_i < color_i_min) color_i_min=color_i;

        }
    }
    int width=(max_y-min_y+1);
    int height=(max_x-min_x+1);
    int length=(max_z-min_z+1);

    nbt_tag_t* tag_materials = nbt_new_tag_string("Alpha",strlen("Alpha"));
    nbt_set_tag_name(tag_materials,(char*)"Materials",strlen("Materials"));
    nbt_tag_compound_append(tag_object,tag_materials);

    nbt_tag_t* tag_height = nbt_new_tag_short(height);
    nbt_set_tag_name(tag_height,(char*)"Height",strlen("Height"));
    nbt_tag_compound_append(tag_object,tag_height);

    nbt_tag_t* tag_width = nbt_new_tag_short(width);
    nbt_set_tag_name(tag_width,(char*)"Width",strlen("Width"));
    nbt_tag_compound_append(tag_object,tag_width);

    nbt_tag_t* tag_length = nbt_new_tag_short(length);
    nbt_set_tag_name(tag_length,(char*)"Length",strlen("Length"));
    nbt_tag_compound_append(tag_object,tag_length);

    nbt_tag_t* tag_offsetx = nbt_new_tag_int(0);
    nbt_set_tag_name(tag_offsetx,(char*)"WEOffsetX",strlen("WEOffsetX"));
    nbt_tag_compound_append(tag_object,tag_offsetx);

    nbt_tag_t* tag_offsety = nbt_new_tag_int(0);
    nbt_set_tag_name(tag_offsety,(char*)"WEOffsetY",strlen("WEOffsetY"));
    nbt_tag_compound_append(tag_object,tag_offsety);

    nbt_tag_t* tag_offsetz = nbt_new_tag_int(0);
    nbt_set_tag_name(tag_offsetz,(char*)"WEOffsetZ",strlen("WEOffsetZ"));
    nbt_tag_compound_append(tag_object,tag_offsetz);

    nbt_tag_t* tag_originx = nbt_new_tag_int(min_y);
    nbt_set_tag_name(tag_originx,(char*)"WEOriginX",strlen("WEOriginX"));
    nbt_tag_compound_append(tag_object,tag_originx);

    nbt_tag_t* tag_originy = nbt_new_tag_int(min_x);
    nbt_set_tag_name(tag_originy,(char*)"WEOriginY",strlen("WEOriginY"));
    nbt_tag_compound_append(tag_object,tag_originy);

    nbt_tag_t* tag_originz = nbt_new_tag_int(min_z);
    nbt_set_tag_name(tag_originz,(char*)"WEOriginZ",strlen("WEOriginZ"));
    nbt_tag_compound_append(tag_object,tag_originz);

    printf("%d x %d x %d : ",width, height, length,2*width*height*length);
    unsigned char* schematic_block = (unsigned char*) malloc(width*height*length);
    unsigned char* schematic_data = (unsigned char*) malloc(width*height*length);
//    printf("OK. CLEARING: ");
    std::memset(schematic_block, 0x0, width*height*length);
    std::memset(schematic_data, 0x0, width*height*length);
    printf("Creating: ");

extern int ret_color(int r, int g, int b);
extern int ret_color3(int r,int g,int b);

    for (int n=first; n<first+num_voxels; n++) {
        Voxel* u=&voxels[n];
        if (u->l > 0) {
            unsigned char color=ret_color(u->r/u->l, u->g/u->l, u->b/u->l);

//            double color_i=((float)u->r + (float)u->g + (float)u->b)/(3.0*u->l);
//            color_i=(color_i-color_i_min)*255.0/(color_i_max-color_i_min+1.0);
//            int color=ret_color3((int)color_i,(int)color_i,(int)color_i);

            size_t offset= ( u->y - min_y )  +  ( u->z - min_z ) * width  +  ( u->x - min_x ) * width * length;
            schematic_block[offset]=251; //blocks id concrete
//            schematic_data[offset]=(unsigned char) ret_color3(u->r/u->l, u->g/u->l, u->b/u->l);
            schematic_data[offset]=(unsigned char) color; //data color

//            fprintf(voxel_file_pointer,"(%d,%d,%d),(%d,%d,%d),(%d)\n",
//                    u.y, u.x, u.z,  u.r/u.l,u.g/u.l, u.b/u.l,  u.l );
        }
        if (!(n%10)) toggle2();
    }
    printf("Ok. Writing: ");

    nbt_tag_t* tag_blocks = nbt_new_tag_byte_array((int8_t*)schematic_block,width*height*length);
    nbt_set_tag_name(tag_blocks,(char*)"Blocks",strlen("Blocks"));
    nbt_tag_compound_append(tag_object,tag_blocks);

    nbt_tag_t* tag_data = nbt_new_tag_byte_array((int8_t*)schematic_data,width*height*length);
    nbt_set_tag_name(tag_data,(char*)"Data",strlen("Data"));
    nbt_tag_compound_append(tag_object,tag_data);

extern std::string obj_filename;
    char filename[200];
    if (automate || obj_filename!="")
        sprintf(filename,"%s/%s.schematic",obj_dir.c_str(),fn.c_str());
    else
        sprintf(filename,"%s/%s.schematic","../cut",fn.c_str());
//    if (!burn) {
        printf("Ok. Saving to file: %s ",filename);
//    }
    write_nbt_file(filename, tag_object, NBT_WRITE_FLAG_USE_GZIP);
    nbt_free_tag(tag_object);

    free(schematic_block);
    free(schematic_data);
    printf(" Ok.\n");
}

void make_test_schematic() {
    std::vector<Voxel> voxels;
    for (int y=0; y++; y<512) {
        Voxel one=Voxel(0,y,0,(int)(y/2),(int)(y/2),(int)(y/2),1,0);
        voxels.push_back(one);
    }
    make_schematic_nbt(std::string() + "../cut/test.schematic", voxels, 0, voxels.size());
}

void region_voxel_files_to_region_files(bool display_only) {
    int x,z;
    char picture_file[200];
    struct dirent *de;
    std::string o_area=area;
    DIR* dr;

    dr = opendir("../cut");
    printf("SCANNING REGION PNG FILES: ../cut/*.png => ");
    while ((de = readdir(dr)) != NULL) {
        if ((strstr(de->d_name, ".png")) != NULL) {
            int num=sscanf(de->d_name,"r.%d.%d.png",&x,&z);
            if (num==2) {
                printf("../cut/%s ",de->d_name);
                sprintf(picture_file,"../cut/r.%d.%d.png",x,z);
                if (file_exists(picture_file)) {
                    scan_image.loadFromFile(picture_file);
                    plot_only=1;
                    plotting=3;
                    scan_x=x;
                    scan_z=z;
                    sprintf(mc_text1,"R.%d.%d.MCA",x,z);
                    update_request=2;
                    while (update_request) {
                        sf::sleep(sf::seconds(0.005));
                    }
                    plotting=0;
                }
            } else  {
                printf("Not region .png file: ../cut/%s\n",de->d_name);
                continue;
            }
        }
    }
    closedir(dr);

    dr = opendir("../cut/done");
    printf("SCANNING REGION PNG FILES: ../cut/done/*.png => ");
    while ((de = readdir(dr)) != NULL) {
        if ((strstr(de->d_name, ".png")) != NULL) {
            int num=sscanf(de->d_name,"r.%d.%d.png",&x,&z);
            if (num==2) {
                printf("../cut/done/%s ",de->d_name);
                sprintf(picture_file,"../cut/done/r.%d.%d.png",x,z);
                if (file_exists(picture_file)) {
                    scan_image.loadFromFile(picture_file);
                    plot_only=1;
                    plotting=3;
                    scan_x=x;
                    scan_z=z;
                    sprintf(mc_text1,"R.%d.%d.MCA",x,z);
                    update_request=2;
                    while (update_request) {
                        sf::sleep(sf::seconds(0.005));
                    }
                    plotting=0;
                }
            } else  {
                printf("Not region .png file: ../cut/done/%s\n",de->d_name);
                continue;
            }
        }
    }
    closedir(dr);

    printf("SCANNING .VOX FILES ../cut/*.vox: ");

    printf("\n");
    dr = opendir("../cut");
    while ((de = readdir(dr)) != NULL) {
        if ((strstr(de->d_name, ".vox")) != NULL) {
            int num=sscanf(de->d_name,"r.%d.%d.vox",&x,&z);
            if (num==2) {
                printf("Converting %s to /saves/test/region/done0/r.%d.%d.mca\n",de->d_name,x,z);
            } else  {
                printf("Not region voxel file: %s\n",de->d_name);
                continue;
            }
            plot_only=0;
            sprintf(picture_file,"r.%d.%d",x,z);
            area=picture_file;
            if (load_voxels()) {
                area=o_area;
                if (voxels_total.size()>0) {
//                    float minimum[3];
//                    float maximum[3];
//                    std::vector<BufferObject> buffers;
//                    std::vector<tinyobj::material_t> materials;
//                    flushing=true;

                    if (voxels_total.size()>0 || voxels.size()>0) {
                        float minimum[3];
                        float maximum[3];
                        std::vector<BufferObject> buffers;
                        std::vector<tinyobj::material_t> materials;
                        flushing=true;
                        plot_only=display_only;
                        dont_write_to_region_voxels=true;
//                        dont_clear=true;
                        crossing=2;mirror=4;
                        WUPPIE_SUBS(buffers, materials, minimum, maximum, 0, 0, picture_file);
                        crossing=0;mirror=0;
                        dont_write_to_region_voxels=false;
//                        dont_clear=false;
                        flushing=false;
                        plot_only=false;
                    }
//                    flush_voxels();

//                    WUPPIE_SUBS(buffers, materials, minimum, maximum, 0, 0, picture_file);
//                    flushing=false;
                    scan_image.create(512,512,sf::Color(0,0,0,0));
                    voxels.clear();
                    voxels_total.clear();
                }
                area=o_area;
            }
        }
    }
    closedir(dr);
    printf("\n");
    area=o_area;
}

void one_region_voxel_files_to_region_files(bool display_only, char* voxel_filename) {
    int x,z;
    char picture_file[200];
    char full_name[1000];
    std::string o_area=area;

    printf("LOADING .VOX FILES ../cut/%s.vox\n", voxel_filename);
    sprintf(full_name,"../cut/%s",voxel_filename);
    if (!file_exists(full_name)) {
        printf("Can not find .vox file: %s\n",full_name);
        return;
    }
    if ((strstr(voxel_filename, ".vox")) != NULL) {
        int num=sscanf(voxel_filename,"r.%d.%d.vox",&x,&z);
        if (num==2) {
            printf("Converting %s to /saves/test/region/done0/r.%d.%d.mca\n",voxel_filename,x,z);
        } else  {
            printf("Not region voxel file: %s\n",voxel_filename);
            return;
        }
        plot_only=0;
        sprintf(picture_file,"r.%d.%d",x,z);
        area=picture_file;
        if (load_voxels()) {
            area=o_area;
            if (voxels_total.size()>0) {
                if (voxels_total.size()>0 || voxels.size()>0) {
                    float minimum[3];
                    float maximum[3];
                    std::vector<BufferObject> buffers;
                    std::vector<tinyobj::material_t> materials;
                    flushing=true;
                    plot_only=display_only;
                    dont_write_to_region_voxels=true;
//                        dont_clear=true;
                    crossing=2;mirror=4;
                    WUPPIE_SUBS(buffers, materials, minimum, maximum, 0, 0, picture_file);
                    crossing=0;mirror=0;
                    dont_write_to_region_voxels=false;
//                        dont_clear=false;
                    flushing=false;
                    plot_only=false;
                }
                scan_image.create(512,512,sf::Color(0,0,0,0));
                voxels.clear();
                voxels_total.clear();
            }
            area=o_area;
        }
    } else {
        printf("Not .vox file: %s\n",voxel_filename);
    }
//    closedir(dr);
    printf("\n");
    area=o_area;
}

/*
extern int position1x;
extern int position1y;
extern void get_position3();

bool play(int play_num, float bmin[3], float bmax[3]) {
    static float flipje;
    static int flipflop=0;
    static double smooth_x_start;
    static double smooth_y_start;
    static float speed_angle;
    static float speed_angle1;
    static float speed_angle2;
    static float bmax_loc[3], bmin_loc[3];
    static double schematic_size_o;
    static float distance;
    if (play_num==0) { //start
        distance=200.0;
        flipflop=1;
        smooth_x_start=(int)smooth_x;
        smooth_y_start=(int)smooth_y;
        angle_base=0.0;
        speed_angle=0.0;
        speed_angle1=0.0;
        speed_angle2=0.0;
        width=0.0;
        bmax_loc[0]=0; bmax_loc[1]=0; bmax_loc[2]=0;
        bmin_loc[0]=0; bmin_loc[1]=0; bmin_loc[2]=0;
        schematic_size_o=6000.0/(eye22*10.0);
    }

    if (play_num==1) {
        for (int n=0;  n<3; n++) {
            bmax_loc[n]=bmax[n];
            bmin_loc[n]=bmin[n];
        }
        printf("Start size: %d %d %d\n", (int)bmax_loc[0]-(int)bmin_loc[0], (int)bmax_loc[1]-(int)bmin_loc[1], (int)bmax_loc[2]-(int)bmin_loc[2]  );
    }

//    schematic_size=6000.0/(eye22*10.0);
//    schematic_size=schematic_size/2.0+rand()%(int(schematic_size));
//    schematic_size=256.0;
    schematic_size=schematic_size_o;
    schematic_size_o=schematic_size_o*0.995;

//    int fff=int(350+350*sin(run_time1/9.113)*sin(run_time1/15.547)*sin(run_time1/12.5399));
//    int ggg=int(150+100*sin((float)(fff)/100.0+run_time1/13.313)*sin(run_time1/16.432)*sin(run_time1/9.9349));
//    int distance=(rand()%fff+ggg);
//    distance*=1.0/0.995;
//                        distance=200;

    float radius=500.0;
    float radius1=500.0+distance;
    float radius2=500.0-distance;
    float offset_x=0.0;
    float offset_y=0.0;

//    if (follow_ghost) {
//        speed_angle=atan2(-smooth_y+smooth_y_old, -smooth_x+smooth_x_old);
//    } else {
//    }

    float f=schematic_size/(6000.0/(eye22*10.0));

    if (play_num>0) {
        if (speed_angle1<speed_angle2) {
            speed_angle=speed_angle1;
            flipflop=1;
//            speed_angle1+=(bmax_loc[2]-bmin_loc[2])/(radius1);
            speed_angle1+=f*(bmax_loc[2]-bmin_loc[2])/(radius1);
        } else {
            speed_angle=speed_angle2;
            flipflop=2;
//            speed_angle2+=(bmax_loc[2]-bmin_loc[2])/(radius2);
            speed_angle2+=f*(bmax_loc[2]-bmin_loc[2])/(radius2);
        }
    }

    offset_x=cos(speed_angle)*radius;
    offset_y=sin(speed_angle)*radius;
//        fspeedx=cos(speed_angle)*speed_base;
//        fspeedy=sin(speed_angle)*speed_base;
//    float run_time1=rand()%50;
    int mazemovex=0;
    int mazemovey=0;

//    if (!flipflop) distance/=1.5;

    if (flipflop==1) {
        mazemovey=distance*sin(speed_angle);
        mazemovex=distance*cos(speed_angle);
    } else {
        mazemovey=-distance*sin(speed_angle);
        mazemovex=-distance*cos(speed_angle);
    }

    voxel_bottom=100.0*(speed_angle/2.0*M_PI);
//    voxel_bottom=g_move_object_z;

    position1x=smooth_x_start+offset_x;
    position1y=smooth_y_start+offset_y;

    get_position3();

    mazemovex_voxel=smooth_x+mazemovex;
    mazemovey_voxel=smooth_y+mazemovey;


//    float fspeedx_o=fspeedx;
//    float fspeedy_o=fspeedy;
//    fspeedx=0.0;
//    fspeedy=0.0;

    printf("NUM: %d: Radius#=%d Bottom=%f%%  Angle=%5.1f  Distance=%d  Width=%d(%d)  Height=%d(%d)  Depth=%d(%d)\n",
           play_num, flipflop, voxel_bottom*100.0,speed_angle*180.0/M_PI,(int)distance,
           (int)bmax[2]-(int)bmin[2], (int)bmax_loc[2]-(int)bmin_loc[2],
           (int)bmax[0]-(int)bmin[0], (int)bmax_loc[0]-(int)bmin_loc[0],
           (int)bmax[1]-(int)bmin[1], (int)bmax_loc[1]-(int)bmin_loc[1]  );
//    if (play_num==0) printf("\n");

//    if (plot_only) {
//        voxels.clear();
//        voxels_total.clear();
//    }

//    fspeedx=fspeedx_o;
//    fspeedy=fspeedy_o;


    if (flipflop==1) {
        g_rotate_object_x=(speed_angle)*180.0/M_PI+90.0+rand()%5-2;
    } else {
        g_rotate_object_x=(speed_angle)*180.0/M_PI-90.0+rand()%5-2;
    }

    g_rotate_object_y=rand()%5-2;
    g_rotate_object_z=rand()%5-2;

//    flipflop++;
//    if (flipflop>3) flipflop=0;

//    smooth_y_old=smooth_y; smooth_x_old=smooth_x;
    if (speed_angle>2.0*M_PI) return false;
    return true;
}
*/
