//
//
//
// Simple .obj viewer(vertex only)
//
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
#ifdef __APPLE__
#include <OpenGL/glu.h>
#else
#include <GL/glu.h>
#endif

#include <GLFW/glfw3.h>

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

#include "trackball.h"

#define STB_IMAGE_IMPLEMENTATION

#define PI 3.141592653589793
extern float plot_all_translate_x;
extern float plot_all_translate_y;
extern float plot_all_translate_z;
extern float plot_all_rotate_x;
extern float plot_all_rotate_y;
extern float plot_all_rotate_z;

extern std::string get_octant_Amsterdam(int &x, int &y);
extern std::string get_octant_Enschede(int &x, int &y);
extern std::string get_octant_LA(int &x, int &y);

extern int smooth;

static std::string GetBaseDir(const std::string& filepath)
{
    if (filepath.find_last_of("/\\") != std::string::npos)
        return filepath.substr(0, filepath.find_last_of("/\\"));
    return "";
}


char img_filename_1[10][1000];
sf::Image *image_1[10];
int image_ready_1[10];
sf::Mutex diff_draw;
int different_draw=0;
sf::Mutex locker;
sf::Mutex render_locker;
int thread_num=0;

void IMG_THREAD1() {
    int thread_number=thread_num;

    if (image_1[thread_number]->loadFromFile(img_filename_1[thread_number])) {
        image_ready_1[thread_number]=1;
    } else {
        image_ready_1[thread_number]=-1;
    }
}
std::string prevbasedir[10];

void IMG_THREAD2() {
    int thread_number=thread_num;

    std::string base_dir = GetBaseDir(img_filename_1[thread_number]);
    base_dir += "/";
    if (base_dir != prevbasedir[thread_number]) {
    }
    prevbasedir[thread_number] = base_dir;
}

sf::Thread loadoneimagefromfile_thread_1(&IMG_THREAD1);
sf::Thread loadoneimagefromfile_thread_2(&IMG_THREAD2);

void loadoneimagefromfile_1(sf::Image *image, std::string filename) {
    locker.lock();
    image_ready_1[thread_num]=0;
    strcpy(img_filename_1[thread_num],filename.c_str());
    image_1[thread_num]=image;
    loadoneimagefromfile_thread_1.launch();
    loadoneimagefromfile_thread_2.launch();
    sf::sleep(sf::milliseconds(5.0));
    thread_num++;
    thread_num=thread_num%10;
    locker.unlock();
}


bool glew_initor=false;
bool glwf_initor=false;
//#include "stb_image.h"
//double
enum
{
    STBI_default = 0, // only used for req_comp

    STBI_grey       = 1,
    STBI_grey_alpha = 2,
    STBI_rgb        = 3,
    STBI_rgb_alpha  = 4
};

typedef unsigned char stbi_uc;

#ifdef __cplusplus
extern "C" {
#endif

#ifdef STB_IMAGE_STATIC
#define STBIDEF static
#else
#define STBIDEF extern
#endif

STBIDEF void     stbi_image_free      (void *retval_from_stbi_load);
STBIDEF stbi_uc *stbi_load               (char              const *filename,           int *x, int *y, int *comp, int req_comp);
#ifdef __cplusplus
}
#endif

#ifdef _WIN32
#ifdef __cplusplus
extern "C" {
#endif
#include <windows.h>

#ifdef max
#undef max
#endif

#ifdef min
#undef min
#endif

#include <mmsystem.h>
#ifdef __cplusplus
}
#endif
#pragma comment(lib, "winmm.lib")
#else
#if defined(__unix__) || defined(__APPLE__)
#include <sys/time.h>
#else
#include <ctime>
#endif
#endif

class timerutil
{
public:
#ifdef _WIN32
    typedef DWORD time_t;

    timerutil()
    {
        ::timeBeginPeriod(1);
    }
    ~timerutil()
    {
        ::timeEndPeriod(1);
    }

    void start()
    {
        t_[0] = ::timeGetTime();
    }
    void end()
    {
        t_[1] = ::timeGetTime();
    }

    time_t sec()
    {
        return (time_t)((t_[1] - t_[0]) / 1000);
    }
    time_t msec()
    {
        return (time_t)((t_[1] - t_[0]));
    }
    time_t usec()
    {
        return (time_t)((t_[1] - t_[0]) * 1000);
    }
    time_t current()
    {
        return ::timeGetTime();
    }

#else
#if defined(__unix__) || defined(__APPLE__)
    typedef unsigned long int time_t;

    void start()
    {
        gettimeofday(tv + 0, &tz);
    }
    void end()
    {
        gettimeofday(tv + 1, &tz);
    }

    time_t sec()
    {
        return (time_t)(tv[1].tv_sec - tv[0].tv_sec);
    }
    time_t msec()
    {
        return this->sec() * 1000 +
               (time_t)((tv[1].tv_usec - tv[0].tv_usec) / 1000);
    }
    time_t usec()
    {
        return this->sec() * 1000000 + (time_t)(tv[1].tv_usec - tv[0].tv_usec);
    }
    time_t current()
    {
        struct timeval t;
        gettimeofday(&t, NULL);
        return (time_t)(t.tv_sec * 1000 + t.tv_usec);
    }

#else  // C timer
    // using namespace std;
    typedef clock_t time_t;

    void start()
    {
        t_[0] = clock();
    }
    void end()
    {
        t_[1] = clock();
    }

    time_t sec()
    {
        return (time_t)((t_[1] - t_[0]) / CLOCKS_PER_SEC);
    }
    time_t msec()
    {
        return (time_t)((t_[1] - t_[0]) * 1000 / CLOCKS_PER_SEC);
    }
    time_t usec()
    {
        return (time_t)((t_[1] - t_[0]) * 1000000 / CLOCKS_PER_SEC);
    }
    time_t current()
    {
        return (time_t)clock();
    }

#endif
#endif

private:
#ifdef _WIN32
    DWORD t_[2];
#else
#if defined(__unix__) || defined(__APPLE__)
    struct timeval tv[2];
    struct timezone tz;
#else
    time_t t_[2];
#endif
#endif
};

typedef struct
{
    GLuint vb_id;  // vertex buffer id
    int numTriangles;
    size_t material_id;
} DrawObject;

static void Get_Draw(const std::vector<DrawObject>& drawObjects,  std::vector<tinyobj::material_t>& materials, std::map<std::string, GLuint>& textures);

int width = 768;
int height = 768;

double prevMouseX, prevMouseY;

bool mouseLeftPressed;
bool mouseMiddlePressed;
bool mouseRightPressed;

bool mouseLeftPressed2;
bool mouseMiddlePressed2;
bool mouseRightPressed2;

float curr_quat[4];
float prev_quat[4];
float eye[3], lookat[3], up[3];


GLFWwindow* window;


static bool FileExists(const std::string& abs_filename)
{
    bool ret;
    FILE* fp = fopen(abs_filename.c_str(), "rb");
    if (fp)
    {
        ret = true;
        fclose(fp);
    }
    else
    {
        ret = false;
    }

    return ret;
}

static void CheckErrors(std::string desc)
{
    GLenum e = glGetError();
    if (e != GL_NO_ERROR)
    {
        fprintf(stderr, "OpenGL error in \"%s\": %d (%d)\n", desc.c_str(), e, e);
        exit(20);
    }
}

static void CalcNormal(float N[3], float v0[3], float v1[3], float v2[3])
{
    float v10[3];
    v10[0] = v1[0] - v0[0];
    v10[1] = v1[1] - v0[1];
    v10[2] = v1[2] - v0[2];

    float v20[3];
    v20[0] = v2[0] - v0[0];
    v20[1] = v2[1] - v0[1];
    v20[2] = v2[2] - v0[2];

    N[0] = v20[1] * v10[2] - v20[2] * v10[1];
    N[1] = v20[2] * v10[0] - v20[0] * v10[2];
    N[2] = v20[0] * v10[1] - v20[1] * v10[0];

    float len2 = N[0] * N[0] + N[1] * N[1] + N[2] * N[2];
    if (len2 > 0.0f)
    {
        float len = sqrtf(len2);

        N[0] /= len;
        N[1] /= len;
        N[2] /= len;
    }
}

namespace  // Local utility functions
{
struct vec3
{
    float v[3];
    vec3()
    {
        v[0] = 0.0f;
        v[1] = 0.0f;
        v[2] = 0.0f;
    }
};

void normalizeVector(vec3 &v)
{
    float len2 = v.v[0] * v.v[0] + v.v[1] * v.v[1] + v.v[2] * v.v[2];
    if (len2 > 0.0f)
    {
        float len = sqrtf(len2);

        v.v[0] /= len;
        v.v[1] /= len;
        v.v[2] /= len;
    }
}

// Check if `mesh_t` contains smoothing group id.
bool hasSmoothingGroup(const tinyobj::shape_t& shape)
{
    for (size_t i = 0; i < shape.mesh.smoothing_group_ids.size(); i++)
    {
        if (shape.mesh.smoothing_group_ids[i] > 0)
        {
            return true;
        }
    }
    return false;
}

void computeSmoothingNormals(const tinyobj::attrib_t& attrib, const tinyobj::shape_t& shape,
                             std::map<int, vec3>& smoothVertexNormals)
{
    smoothVertexNormals.clear();
    std::map<int, vec3>::iterator iter;

    for (size_t f = 0; f < shape.mesh.indices.size() / 3; f++)
    {
        // Get the three indexes of the face (all faces are triangular)
        tinyobj::index_t idx0 = shape.mesh.indices[3 * f + 0];
        tinyobj::index_t idx1 = shape.mesh.indices[3 * f + 1];
        tinyobj::index_t idx2 = shape.mesh.indices[3 * f + 2];

        // Get the three vertex indexes and coordinates
        int vi[3];      // indexes
        float v[3][3];  // coordinates

        for (int k = 0; k < 3; k++)
        {
            vi[0] = idx0.vertex_index;
            vi[1] = idx1.vertex_index;
            vi[2] = idx2.vertex_index;
            if ( vi[0]< 0 || vi[0]< 0 || vi[0]< 0 ) {
                v[0][k] = 0;   v[1][k] = 0;     v[2][k] = 0;
            } else {
                v[0][k] = attrib.vertices[3 * vi[0] + k];
                v[1][k] = attrib.vertices[3 * vi[1] + k];
                v[2][k] = attrib.vertices[3 * vi[2] + k];
            }
//            assert(vi[0] >= 0);
//            assert(vi[1] >= 0);
//            assert(vi[2] >= 0);

        }

        // Compute the normal of the face
        float normal[3];
        CalcNormal(normal, v[0], v[1], v[2]);

        // Add the normal to the three vertexes
        for (size_t i = 0; i < 3; ++i)
        {
            iter = smoothVertexNormals.find(vi[i]);
            if (iter != smoothVertexNormals.end())
            {
                // add
                iter->second.v[0] += normal[0];
                iter->second.v[1] += normal[1];
                iter->second.v[2] += normal[2];
            }
            else
            {
                smoothVertexNormals[vi[i]].v[0] = normal[0];
                smoothVertexNormals[vi[i]].v[1] = normal[1];
                smoothVertexNormals[vi[i]].v[2] = normal[2];
            }
        }

    }  // f

    // Normalize the normals, that is, make them unit vectors
    for (iter = smoothVertexNormals.begin(); iter != smoothVertexNormals.end();
            iter++)
    {
        normalizeVector(iter->second);
    }

}  // computeSmoothingNormals
}  // namespace

static bool LoadObjAndConvert(float bmin[3], float bmax[3],
                              std::vector<DrawObject>& drawObjects,
                              std::vector<tinyobj::material_t>& materials,
                              std::map<std::string, GLuint>& textures,
                              const char* filename)
{
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

    std::string warn;
    std::string err;


    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, filename, base_dir.c_str());

    if (!warn.empty())
    {
        std::cout << "WARN: " << warn << std::endl;
    }
    if (!err.empty())
    {
        std::cerr << err << std::endl;
    }

    tm.end();

    if (!ret)
    {
        std::cerr << "Failed to load " << filename << std::endl;
        return false;
    }

    printf(" Parsing time: %d [ms]\n", (int)tm.msec());

    printf("# of vertices  = %d\n", (int)(attrib.vertices.size()) / 3);
    printf("# of normals   = %d\n", (int)(attrib.normals.size()) / 3);
    printf("# of texcoords = %d\n", (int)(attrib.texcoords.size()) / 2);
    printf("# of materials = %d\n", (int)materials.size());
    printf("# of shapes    = %d\n", (int)shapes.size());

    // Append `default` material
    materials.push_back(tinyobj::material_t());
    printf("CPU -> GPU:\n");
    {
        for (size_t m = 0; m < materials.size(); m++)
        {
            tinyobj::material_t* mp = &materials[m];
            if (mp->diffuse_texname.length() > 0)
            {
                if (textures.find(mp->diffuse_texname) == textures.end())
                {
                    GLuint texture_id;
                    int w, h;
                    int comp;

                    std::string texture_filename = mp->diffuse_texname;
                    if (!FileExists(texture_filename))
                    {
                        // Append base dir.
                        texture_filename = base_dir + mp->diffuse_texname;
                        if (!FileExists(texture_filename))
                        {
                            std::cerr << "Unable to find file: " << mp->diffuse_texname
                                      << std::endl;
                            return false;
                        }
                    }
                    unsigned char* image;
                    sf::Image sfml_image;
                    bool png=false;
                    if (strstr(texture_filename.c_str(), ".png") != NULL) {
                        png=true;
                        comp=4;
                        int ret;

                        if (!sfml_image.loadFromFile(texture_filename.c_str())) image = 0;
                        else {
                            w=sfml_image.getSize().x;
                            h=sfml_image.getSize().y;
                            image=(unsigned char*)sfml_image.getPixelsPtr();
                        }
                    } else {
                        image = stbi_load(texture_filename.c_str(), &w, &h, &comp, STBI_default);
                    }

                    if (!image)
                    {
                        std::cerr << "Unable to load texture: " << texture_filename
                                  << std::endl;
                    }
                    glGenTextures(1, &texture_id);
                    glBindTexture(GL_TEXTURE_2D, texture_id);
                    printf("Loading texture(s): %d Id: %d Filename: %s          \r",(int)m, texture_id,texture_filename.c_str());
                    if (comp == 3) {
                        glTexStorage2D(GL_TEXTURE_2D, 4, GL_RGB8, w, h);
                        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, w, h, GL_RGB, GL_UNSIGNED_BYTE, image);
                    } else if (comp == 4) {
                        glTexStorage2D(GL_TEXTURE_2D, 4, GL_RGBA8, w, h);
                        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, w, h, GL_RGBA, GL_UNSIGNED_BYTE, image);
                    }
                    else
                    {
                        assert(0);  // TODO
                    }
                    glGenerateMipmap(GL_TEXTURE_2D);

                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

                    if (smooth)
                        glShadeModel(GL_SMOOTH);
                    else
                        glShadeModel(GL_FLAT);
                    glBindTexture(GL_TEXTURE_2D, 0);
                    if (!png) stbi_image_free(image);
                    textures.insert(std::make_pair(mp->diffuse_texname, texture_id));
                }
            }
        }
    }
    printf("\n");

    bmin[0] = bmin[1] = bmin[2] = std::numeric_limits<float>::max();
    bmax[0] = bmax[1] = bmax[2] = -std::numeric_limits<float>::max();

    {
        int tot_indices=0;
        for (size_t s = 0; s < shapes.size(); s++)
        {
            printf("\rLoading shape %5d(%d)\r",(int)s,(int)shapes.size());
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
                        } else  if (attrib.texcoords.size() <=  size_t(2 * idx1.texcoord_index + 1)){
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
                                printf("Invalid_normal_index\n");
                            }
                        }
                        else
                        {
                            for (int k = 0; k < 3; k++)
                            {
                                if (size_t(3 * nf0 + k) >= attrib.normals.size() ||
                                    size_t(3 * nf1 + k) >= attrib.normals.size() ||
                                    size_t(3 * nf2 + k) >= attrib.normals.size()) {
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
/*
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
*/

                    buffer.push_back(tc[k][0]);  buffer.push_back(tc[k][1]);
                }
                tot_indices++;
                if ((!((int)f&0xfff) && (f>0)) || f==(int)shape_size-1 ) printf("\rLoading shape %5d(%d) Total indices: %d       \r",(int)s,(int)shapes.size(),tot_indices);
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
                glGenBuffers(1, &o.vb_id);
                glBindBuffer(GL_ARRAY_BUFFER, o.vb_id);
                glBufferData(GL_ARRAY_BUFFER, buffer.size() * sizeof(float),  &buffer.at(0), GL_STATIC_DRAW);
//color out
                o.numTriangles = buffer.size() / (3 + 3 + 2) / 3;           // 3:vtx, 3:normal,  2:texcoord
//                o.numTriangles = buffer.size() / (3 + 3 + 3 + 2) / 3;     // 3:vtx, 3:normal, 3:col, 2:texcoord

//                printf(" shape[%d] # of triangles = %d", static_cast<int>(s),
//                       o.numTriangles);
            }
            drawObjects.push_back(o);
//            drawObjects->push_back(o);
        }
    }
    printf("\n");

    printf("bmin = %f, %f, %f\n", bmin[0], bmin[1], bmin[2]);
    printf("bmax = %f, %f, %f\n", bmax[0], bmax[1], bmax[2]);

    return true;
}

static void reshapeFunc(GLFWwindow* window, int w, int h)
{
    int fb_w, fb_h;
    // Get actual framebuffer size.
    glfwGetFramebufferSize(window, &fb_w, &fb_h);

    glViewport(0, 0, fb_w, fb_h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)w / (float)h, 0.01f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    width = w;
    height = h;
}

static void keyboardFunc(GLFWwindow* window, int key, int scancode, int action,
                         int mods)
{
    (void)window;
    (void)scancode;
    (void)mods;
    if (action == GLFW_PRESS || action == GLFW_REPEAT)
    {
        // Move camera
        float mv_x = 0, mv_y = 0, mv_z = 0;
        if (key == GLFW_KEY_K)            mv_x += 1;
        else if (key == GLFW_KEY_J)       mv_x += -1;
        else if (key == GLFW_KEY_L)       mv_y += 1;
        else if (key == GLFW_KEY_H)       mv_y += -1;
        else if (key == GLFW_KEY_P)       mv_z += 1;
        else if (key == GLFW_KEY_N)       mv_z += -1;
        // camera.move(mv_x * 0.05, mv_y * 0.05, mv_z * 0.05);
        // Close window
        if (key == GLFW_KEY_Q || key == GLFW_KEY_ESCAPE)  glfwSetWindowShouldClose(window, GL_TRUE);

        // init_frame = true;
    }
}

static void clickFunc(GLFWwindow* window, int button, int action, int mods)
{
    (void)window;
    (void)mods;
    if (button == GLFW_MOUSE_BUTTON_LEFT)
    {
        if (action == GLFW_PRESS)
        {
            mouseLeftPressed = true;
            trackball(prev_quat, 0.0, 0.0, 0.0, 0.0);
        }
        else if (action == GLFW_RELEASE)
        {
            mouseLeftPressed = false;
        }
    }
    if (button == GLFW_MOUSE_BUTTON_RIGHT)
    {
        if (action == GLFW_PRESS)
        {
            mouseRightPressed = true;
        }
        else if (action == GLFW_RELEASE)
        {
            mouseRightPressed = false;
        }
    }
    if (button == GLFW_MOUSE_BUTTON_MIDDLE)
    {
        if (action == GLFW_PRESS)
        {
            mouseMiddlePressed = true;
        }
        else if (action == GLFW_RELEASE)
        {
            mouseMiddlePressed = false;
        }
    }
}

static void motionFunc(GLFWwindow* window, double mouse_x, double mouse_y)
{
    (void)window;
    float rotScale = 1.0f;
    float transScale = 2.0f;

    if (mouseLeftPressed)
    {
        trackball(prev_quat, rotScale * (2.0f * prevMouseX - width) / (float)width,
                  rotScale * (height - 2.0f * prevMouseY) / (float)height,
                  rotScale * (2.0f * mouse_x - width) / (float)width,
                  rotScale * (height - 2.0f * mouse_y) / (float)height);

        add_quats(prev_quat, curr_quat, curr_quat);
    }
    else if (mouseMiddlePressed)
    {
        eye[0] -= transScale * (mouse_x - prevMouseX) / (float)width;
        lookat[0] -= transScale * (mouse_x - prevMouseX) / (float)width;
        eye[1] += transScale * (mouse_y - prevMouseY) / (float)height;
        lookat[1] += transScale * (mouse_y - prevMouseY) / (float)height;
    }
    else if (mouseRightPressed)
    {
        eye[2] += transScale * (mouse_y - prevMouseY) / (float)height;
        lookat[2] += transScale * (mouse_y - prevMouseY) / (float)height;
    }

    // Update mouse point
    prevMouseX = mouse_x;
    prevMouseY = mouse_y;
}

static void Draw(const std::vector<DrawObject>& drawObjects,
                 std::vector<tinyobj::material_t>& materials,
                 std::map<std::string, GLuint>& textures)
{
    glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_BACK, GL_FILL);

    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(1.0, 1.0);
//color out
  GLsizei stride = (3 + 3 + 2) * sizeof(float);
//    GLsizei stride = (3 + 3 + 3 + 2) * sizeof(float);
    for (size_t i = 0; i < drawObjects.size(); i++)
    {
        DrawObject o = drawObjects[i];
        if (o.vb_id < 1)
        {
            continue;
        }
        glBindBuffer(GL_ARRAY_BUFFER, o.vb_id);
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_NORMAL_ARRAY);
//color out
//        glEnableClientState(GL_COLOR_ARRAY);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);

        glBindTexture(GL_TEXTURE_2D, 0);
        if ((o.material_id < materials.size()))
        {
            std::string diffuse_texname = materials[o.material_id].diffuse_texname;
            if (textures.find(diffuse_texname) != textures.end())
            {
                glBindTexture(GL_TEXTURE_2D, textures[diffuse_texname]);
            }
        }

        glVertexPointer(3, GL_FLOAT, stride, (const void*)0);
        glNormalPointer(GL_FLOAT, stride, (const void*)(sizeof(float) * 3));
//color out
//        glColorPointer(3, GL_FLOAT, stride, (const void*)(sizeof(float) * 6));

//color out
        glTexCoordPointer(2, GL_FLOAT, stride, (const void*)(sizeof(float) * 6));
//        glTexCoordPointer(2, GL_FLOAT, stride, (const void*)(sizeof(float) * 9));

        glDrawArrays(GL_TRIANGLES, 0, 3 * o.numTriangles);
        CheckErrors("drawarrays");
        glBindTexture(GL_TEXTURE_2D, 0);
    }


    // draw wireframe
    /*
      glDisable(GL_POLYGON_OFFSET_FILL);
      glPolygonMode(GL_FRONT, GL_LINE);
      glPolygonMode(GL_BACK, GL_LINE);

      glColor3f(0.0f, 0.0f, 0.4f);
      for (size_t i = 0; i < drawObjects.size(); i++) {
        DrawObject o = drawObjects[i];
        if (o.vb_id < 1) {
          continue;
        }

        glBindBuffer(GL_ARRAY_BUFFER, o.vb_id);
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_NORMAL_ARRAY);
        glDisableClientState(GL_COLOR_ARRAY);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        glVertexPointer(3, GL_FLOAT, stride, (const void*)0);
        glNormalPointer(GL_FLOAT, stride, (const void*)(sizeof(float) * 3));
        glColorPointer(3, GL_FLOAT, stride, (const void*)(sizeof(float) * 6));
        glTexCoordPointer(2, GL_FLOAT, stride, (const void*)(sizeof(float) * 9));

        glDrawArrays(GL_TRIANGLES, 0, 3 * o.numTriangles);
        CheckErrors("drawarrays");
      }
    */

}

static void Init()
{
    trackball(curr_quat, 0, 0, 0, 0);

    eye[0] = 0.0f;
    eye[1] = 0.0f;
    eye[2] = 3.0f;

    lookat[0] = 0.0f;
    lookat[1] = 0.0f;
    lookat[2] = 0.0f;

    up[0] = 0.0f;
    up[1] = 1.0f;
    up[2] = 0.0f;
}


int main_viewer(int argc, char** argv);
extern int shut_up;
//extern sf::RenderWindow SFMLView1;

//OBJ_VIEWER
int do_viewer()
{
    char *m_argv[3];
    char arg1[20]="ik";
//    char arg2[]="model.3.obj";
    char arg2[]="apple.obj";

/*    char arg2[1000];
    int x=0,y=0;
    get_octant_Amsterdam(x,y);
    x=25;y=25;
    strcpy(arg2,get_octant_Amsterdam(x,y).c_str());
*/
//    char arg2[]="Sophie.remesh.uv.m";
//    char arg2[]="Alex.uv.m";

//    char arg3[]="check_1k_64.bmp";


    m_argv[0]=arg1;
    m_argv[1]=arg2;
//    m_argv[2]=arg3;
    int old_shut_up=shut_up;
    shut_up=1;

//    SFMLView1.popGLStates();
//    SFMLView1.setActive(false);
    int ret=main_viewer(2,m_argv);

//    SFMLView1.pushGLStates();

    shut_up=old_shut_up;
    return ret;
}


int VIEWER_stop=0;
int VIEWER_running=0;

void VIEWER_THREAD()
{
    printf("VIEWER thread starting\n");
    do_viewer();
    printf("VIEWER thread stopped\n");
    VIEWER_stop=0;
    VIEWER_running=0;
}

sf::Thread VIEWER(&VIEWER_THREAD);

void launch_VIEWER()
{
    if (VIEWER_running==1)
    {
        printf("VIEWER already running\n");
        return;
    }
    VIEWER_running=1;
    VIEWER.launch();

//    sf::sleep(sf::seconds(5.0));

}

void terminate_VIEWER()
{
    VIEWER.terminate();
}


int main_viewer(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cout << "Needs input.obj\n" << std::endl;
        return 0;
    }

    Init();

    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW." << std::endl;
        return -1;
    }

    window = glfwCreateWindow(width, height, "Obj viewer", NULL, NULL);
    if (window == NULL)
    {
        std::cerr << "Failed to open GLFW window. " << std::endl;
        glfwTerminate();
        return 1;
    }
//sf::Window
//sf::Context
//sf::GlResources

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    // Callback
    glfwSetWindowSizeCallback(window, reshapeFunc);
    glfwSetKeyCallback(window, keyboardFunc);
    glfwSetMouseButtonCallback(window, clickFunc);
    glfwSetCursorPosCallback(window, motionFunc);

    if (glew_initor==false) {
        glewExperimental = true;
        if (glewInit() != GLEW_OK)
        {
            std::cerr << "Failed to initialize GLEW." << std::endl;
            return -1;
        }
        glew_initor=true;
    }

    reshapeFunc(window, width, height);

    float bmin[3], bmax[3];
    std::vector<DrawObject> gDrawObjects;
    std::vector<tinyobj::material_t> materials;
    std::map<std::string, GLuint> textures;
    if (false == LoadObjAndConvert(bmin, bmax, gDrawObjects, materials, textures,
                                   argv[1]))
    {
        return -1;
    }

    float maxExtent = 0.5f * (bmax[0] - bmin[0]);
    if (maxExtent < 0.5f * (bmax[1] - bmin[1]))
    {
        maxExtent = 0.5f * (bmax[1] - bmin[1]);
    }
    if (maxExtent < 0.5f * (bmax[2] - bmin[2]))
    {
        maxExtent = 0.5f * (bmax[2] - bmin[2]);
    }

    while (glfwWindowShouldClose(window) == GL_FALSE)
    {
        glfwPollEvents();
        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_TEXTURE_2D);

        // camera & rotate
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        GLfloat mat[4][4];
        gluLookAt(eye[0], eye[1], eye[2], lookat[0], lookat[1], lookat[2], up[0],
                  up[1], up[2]);
        build_rotmatrix(mat, curr_quat);
        glMultMatrixf(&mat[0][0]);

        // Fit to -1, 1
        glScalef(1.0f / maxExtent, 1.0f / maxExtent, 1.0f / maxExtent);

        // Centerize object.
        glTranslatef(-0.5 * (bmax[0] + bmin[0]), -0.5 * (bmax[1] + bmin[1]),
                     -0.5 * (bmax[2] + bmin[2]));

        Draw(gDrawObjects, materials, textures);

        glfwSwapBuffers(window);
    }

    glfwTerminate();
}



#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#ifndef GL_SRGB8_ALPHA8
#define GL_SRGB8_ALPHA8 0x8C43
#endif


int main_hoppa2(char* filename_in, int cur_x, int cur_y, int max_x, int max_y, int combine);
int do_SFMLGL2(int what);

int SFMLGL2_stop=0;
int SFMLGL2_running=0;
int SFMLGL2_b_stop=0;
int SFMLGL2_b_running=0;

extern sf::RenderWindow SFMLView1;

char window_num=0;

void SFMLGL2_THREAD()
{
    printf("SFMLGL2 thread starting\n");
    int ret=-99;
    do {
        window_num=0;
        printf("Calling do_SFMLGL2()\n");
        ret=do_SFMLGL2(ret);
        printf("Returned from_SFMLGL2()\n");
    } while (ret<=-10);
    printf("SFMLGL2 thread stopped\n");
    SFMLGL2_stop=0;
    SFMLGL2_running=0;
    SFMLView1.requestFocus();
//hoppa
//    SFMLView1.resetGLStates();
}

void SFMLGL2_b_THREAD()
{
    printf("SFMLGL2_b thread starting\n");
    int ret=-99;
    do {
        window_num=1;
        ret=do_SFMLGL2(ret);
    } while (ret<=-10);
    printf("SFMLGL2_b thread stopped\n");
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

void launch_SFMLGL2()
{
    strcpy(window_name,"SFML OPENGL");
    if (SFMLGL2_running==1)
    {
        if (keep_running[0]) {
            printf("SFMLGL2 already running\n");
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
    SFMLGL2.launch();
}

void launch_SFMLGL2_b()
{
    strcpy(window_name,"SFML OPENGL 2");
    if (SFMLGL2_b_running==1)
    {
        if (keep_running[1]) {
            printf("SFMLGL2 b already running\n");
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


bool test_for_pngfiles(string directory) {
    DIR* dr = opendir(directory.c_str());
    struct dirent *de;
    int png=0;
    size_t tot_size=0;
//    printf("TO DO: ");
    while ((de = readdir(dr)) != NULL) {
        toggle2();
        if ((strstr(de->d_name, ".bmp")) != NULL) {
            closedir(dr);
            printf("Fok! .bmp files found: %s\nConvert with .sh scripts under Ubuntu powershell to .png or adapt this code...\n",directory.c_str());
//            return true;
            return false;
        } else if ((strstr(de->d_name, ".jpg")) != NULL) {
            closedir(dr);
            printf("Fok! .jpg files found: %s\nConvert with .sh scripts under Ubuntu powershell to .png or adapt this code...\n",directory.c_str());
//            return true;
            return false;
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
            printf(".png file(s) found: %s\n",directory.c_str());
            return true;
        }
    }
//    printf("\n");
    closedir(dr);
    if (png==0) {
        printf("No .png files found: %s\n",directory.c_str());
    }
    else {
        printf("%d .png files found: %s\n",png,directory.c_str());
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
    size_t found;
    if (combine) {
        int looper=0;
        do {
            static int first=1;
            static int max_x,max_y;
            static int cur_x,cur_y;
            if (first==1) {
                get_octant_Amsterdam(max_x,max_y);
                cur_x=max_x/2;
                cur_y=max_y/2;
                first=0;
            }
            if (looper==1) {
                cur_x=rand()%max_x;
                cur_y=rand()%max_y;
                printf("No .png -> Random -> ");
            } else {
                if (what==-10) { cur_x--; if (cur_x<0) cur_x=0; }
                else if (what==-11) { cur_x++; if (cur_x>=max_x) cur_x=max_x-1; }
                else if (what==-12) { cur_y--; if (cur_y<0) cur_y=0; }
                else if (what==-13) { cur_y++; if (cur_y>=max_y) cur_y=max_y-1; }
            }
            str=get_octant_Amsterdam(cur_x,cur_y);
            printf("Trying: %d,%d -> %s\n",cur_x,cur_y,str.c_str());
            strcpy(arg2,str.c_str());
            found=str.find_last_of("/\\");
            looper=1;
            send_max_x=max_x;
            send_max_y=max_y;
            send_cur_x=cur_x;
            send_cur_y=cur_y;
        } while (test_for_pngfiles(str.substr(0,found))==false);
    } else {
        int looper=0;
        do {
            static int first=1;
            static int max_x,max_y;
            static int cur_x,cur_y;
            if (first==1) {
                get_octant_Enschede(max_x,max_y);
                cur_x=max_x/2;
                cur_y=max_y/2;
                first=0;
            }
            if (looper==1) {
                cur_x=rand()%max_x;
                cur_y=rand()%max_y;
                printf("No .png -> Random -> ");
            } else {
                if (what==-10) { cur_x--; if (cur_x<0) cur_x=0; }
                else if (what==-11) { cur_x++; if (cur_x>=max_x) cur_x=max_x-1; }
                else if (what==-12) { cur_y--; if (cur_y<0) cur_y=0; }
                else if (what==-13) { cur_y++; if (cur_y>=max_y) cur_y=max_y-1; }
            }
            str=get_octant_Enschede(cur_x,cur_y);
            printf("Trying: %d,%d -> %s\n",cur_x,cur_y,str.c_str());
            strcpy(arg2,str.c_str());
            found=str.find_last_of("/\\");
            looper=1;
            send_max_x=max_x;
            send_max_y=max_y;
            send_cur_x=cur_x;
            send_cur_y=cur_y;
        } while (test_for_pngfiles(str.substr(0,found))==false);
    }

    printf("Loading: %s\n",arg2);
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

//typedef struct
struct Pacman_Object
{
    float bmin[3], bmax[3];
    std::vector<DrawObject> gDrawObjects;
    std::vector<tinyobj::material_t> materials;
    std::map<std::string, GLuint> textures;
    int map_x=0;
    int map_y=0;
};

std::vector<Pacman_Object> *Pacman_Objects_Global[10];
int ready_to_render[10]={0,0,0,0,0,0,0,0,0,0};

extern HDC hdc_sfmlview1;
extern HGLRC hglrc_sfmlview1;
extern HWND hWndMain;


sf::WindowHandle window_handle;

sf::GlContext* m_context_window;
sf::GlContext* m_context_sfmlview1;

extern void ShowTaskBar(bool show);

int main_hoppa2(char* filename_in, int cur_x, int cur_y, int max_x, int max_y, int combine)
{
    int swoop=0;
    HGLRC    hglrc;
    HDC      hdc ;
    char filename[1000];
    strcpy(filename,filename_in);
    int win_num=window_num;
    keep_running[win_num]=1;
    int exit_code=0;
    bool exit_thread = false;
    bool sRgb = false;
    while (keep_running[win_num]) {
        is_activated_window[win_num]=1;
        float curr_quat2[4];
        float prev_quat2[4];
        float eye2[3], lookat2[3], up2[3];
        double prevMouseX2, prevMouseY2;

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

        int width2 = 1920;
        int height2 = 1080;
        int repeat=0;

        static int first=1;
        static sf::Vector2u old_size[10];
        static sf::Vector2i old_pos[10];
        if (first==1) {
            first=0;
            for (int i=0; i<10; i++) {
                old_size[i] = ( sf::Vector2u(1920,1080) );
                old_pos[i]  = ( sf::Vector2i(0,0) );
//                old_size[i] = ( sf::Vector2u(1920/2.0,1080/2.0) );
//                old_pos[i]  = ( sf::Vector2i(1920/2.0-1920/4.0,1080/2.0-1080/4.0) );
            }
        }
        char window_title[1000];
        sprintf(window_title,"X=%d,Y=%d/(%d,%d) %s",cur_x,cur_y,max_x,max_y,filename);
        int fade=0;
        while (!exit_thread || exit_code==-98)
        {
            exit_code=0;
            exit_thread=0;
            sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

            sf::ContextSettings contextSettings(0,0,2,3,0);
            contextSettings.antialiasingLevel = 0;
            contextSettings.stencilBits = 0;
            contextSettings.depthBits=24;
            contextSettings.sRgbCapable = sRgb;

            sf::RenderWindow window;
    //            SFMLView1.create(sf::VideoMode(1920,1080), "PACMAN", sf::Style::Resize | sf::Style::Fullscreen, contextSettings);

    //sf::Style::Resize | sf::Style::Titlebar | sf::Style::Close
    //        window.create(sf::VideoMode(width2,height2), "opengltest", sf::Style::Resize | sf::Style::Titlebar | sf::Style::Close , contextSettings);
//            window.create(sf::VideoMode(old_size[win_num].x,old_size[win_num].y), "", sf::Style::Resize , contextSettings);
        SFMLView1.create(sf::VideoMode(1920,1080), "PACMAN", sf::Style::Resize | sf::Style::Fullscreen, contextSettings);
            window.create(sf::VideoMode(1920,1080), window_title, sf::Style::Fullscreen, contextSettings);
//            window.create(sf::VideoMode(1920,1080), window_title, sf::Style::Resize | sf::Style::Titlebar | sf::Style::Close , contextSettings);
            window.setSize(old_size[win_num]);
            window.setPosition(old_pos[win_num]);
            width2 = old_size[win_num].x;
            height2 = old_size[win_num].y;
            window_handle=window.getSystemHandle();
            m_context_window=window.m_context;
    //        window.create(sf::VideoMode(width2,height2), window_name, sf::Style::Resize , contextSettings);
    //        window.create(sf::VideoMode(1920,1080), "SFML OPENGL", sf::Style::Fullscreen, contextSettings);
            ShowCursor(true);

    //        sf::RenderWindow window(sf::VideoMode(width, height), "SFML graphics with OpenGL", GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH, contextSettings);
            hglrc = wglGetCurrentContext();
            hdc = wglGetCurrentDC() ;
    //        glewInit();

    //        UINT l_id = glCreateProgram();

            window.setVerticalSyncEnabled(true);
            sf::Texture backgroundTexture;
            backgroundTexture.setSrgb(sRgb);
            if (!backgroundTexture.loadFromFile("resources/background.jpg"))   return EXIT_FAILURE;
            sf::Sprite background(backgroundTexture);
            backgroundTexture.setSmooth(smooth==1);
            background.setOrigin(backgroundTexture.getSize().x/2,backgroundTexture.getSize().y/2);
            background.setPosition(1920.0/2.0,1080.0/2.0);
            sf::Font font;
            if (!font.loadFromFile("resources/Sansation_Regular.ttf"))     return EXIT_FAILURE;
            char hoppa[2000];
            sprintf(hoppa,"Pacman Graphics SFML / OpenGL demo\nGoogle map satellite 3d data\n3d .obj file loader/opengl renderer\nhttps://www.facebook.com/Pacman-Graphics-1601114056700700/\nhttps://www.facebook.com/Minecraft-Worldeditor-110607880303634/\nhttps://github.com/TheJavaProfessor/MINECRAFT-WORLD-CREATOR");

            sf::Text text(hoppa, font);
            text.setCharacterSize(32);
            text.setOutlineThickness(1.0);
            text.setFillColor(sf::Color(255, 255, 255, 170));
            text.setOutlineColor(sf::Color(0, 0, 0, 255));

            sf::Text sRgbInstructions("Press n to load next object conversion", font);
            sRgbInstructions.setCharacterSize(48);
            sRgbInstructions.setOutlineThickness(2.0);
            sRgbInstructions.setFillColor(sf::Color(255, 255, 255, 170));
            sRgbInstructions.setOutlineColor(sf::Color(0, 0, 0, 255));

            sf::Text mipmapInstructions("Use mouse left, middle and right button", font);
            mipmapInstructions.setCharacterSize(48);
            mipmapInstructions.setOutlineThickness(2.0);
            mipmapInstructions.setFillColor(sf::Color(255, 255, 255, 170));
            mipmapInstructions.setOutlineColor(sf::Color(0, 0, 0, 255));

            text.setPosition(0.f, 800.f);
            sRgbInstructions.setPosition(0.f, 700.f);
            mipmapInstructions.setPosition(0.f, 750.f);
            sf::Texture texture;
            if (!texture.loadFromFile("resources/texture.jpg")) return EXIT_FAILURE;
            texture.generateMipmap();

            window.setActive(true);

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
            if (strlen(filename)==0)
            {
                std::cout << "Needs input.obj\n" << std::endl;
                return 0;
            }

    //        Init2();

            std::vector<Pacman_Object> Pacman_Objects;
            Pacman_Objects_Global[window_num]=&Pacman_Objects;
    //        Pacman_Object *pac_obj = new Pacman_Object;
            Pacman_Object pac_obj;
            if (false == LoadObjAndConvert(pac_obj.bmin, pac_obj.bmax, pac_obj.gDrawObjects, pac_obj.materials, pac_obj.textures, filename))
    //        if (false == LoadObjAndConvert(pac_obj->bmin, pac_obj->bmax, &pac_obj->gDrawObjects, pac_obj->materials, pac_obj->textures, argv[1]))
            {
                return -1;
            }
            pac_obj.map_x=cur_x;
            pac_obj.map_y=cur_y;
            Pacman_Objects.push_back(pac_obj);
    //        pac_obj->map_x=cur_x;
    //        pac_obj->map_y=cur_y;
    //        Pacman_Objects.push_back(*pac_obj);

            float bmin[3], bmax[3];
            bmin[0] = bmin[1] = bmin[2] = std::numeric_limits<float>::max();
            bmax[0] = bmax[1] = bmax[2] = -std::numeric_limits<float>::max();
            for (auto u : Pacman_Objects) {
                if (u.bmin[0]<bmin[0]) bmin[0]=u.bmin[0]; if (u.bmax[0]>bmax[0]) bmax[0]=u.bmax[0];
                if (u.bmin[1]<bmin[1]) bmin[1]=u.bmin[1]; if (u.bmax[1]>bmax[1]) bmax[1]=u.bmax[1];
                if (u.bmin[2]<bmin[2]) bmin[2]=u.bmin[2]; if (u.bmax[2]>bmax[2]) bmax[2]=u.bmax[2];
            }
    //        std::vector<DrawObject> gDrawObjects;
    //        std::vector<tinyobj::material_t> materials;
    //        std::map<std::string, GLuint> textures;

    //        if (false == LoadObjAndConvert(bmin, bmax, &gDrawObjects, materials, textures, argv[1]))
    //        {
    //            return -1;
    //        }

            printf("Succes!!!\n");
            render_locker.lock();
            ready_to_render[win_num]=1;
            render_locker.unlock();
            float maxExtent = 0.5f * (bmax[0] - bmin[0]);
            if (maxExtent < 0.5f * (bmax[1] - bmin[1]))
            {
                maxExtent = 0.5f * (bmax[1] - bmin[1]);
            }
            if (maxExtent < 0.5f * (bmax[2] - bmin[2]))
            {
                maxExtent = 0.5f * (bmax[2] - bmin[2]);
            }

            float rotScale = 1.0f;
            float transScale = 1.0f;

            glViewport(0, 0, window.getSize().x, window.getSize().y);
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();

    //        GLfloat ratio = static_cast<float>(window.getSize().x) / window.getSize().y;
    //        glFrustum(-ratio, ratio, -1.f, 1.f, 1.f, 500.f);

            gluPerspective(45.0, (float)window.getSize().x / (float)window.getSize().y, 0.01f, 100.0f);

            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            window.setActive(false);

            sf::Clock clock;
            bool mipmapEnabled = true;

            static int bar_on[10]={1,1,1,1,1,1,1,1,1,1};
            int loaded=0;
            int round=0;
            sf::Event event;
            while (window.isOpen() && exit_thread==0)
            {
                if (round<0) loaded=0;
                else round--;
                if (loaded==1) printf("11-");
                if (window.hasFocus() ) {
                    if (bar_on[win_num]==1) ShowTaskBar(false);
                    bar_on[win_num]=0;
                } else {
                    if (bar_on[win_num]==0) ShowTaskBar(true);
                    bar_on[win_num]=1;
                }
                if (loaded==1) printf("12-");
                while (window.pollEvent(event))
                {
                    if (loaded==1) printf("13-");
                    if (event.type == sf::Event::Closed) {
                        exit_code=0;
                        exit_thread = true;
                    } else if (event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::MouseButtonReleased) {

                        if (event.mouseButton.button == sf::Mouse::Left) {
                            if (event.type == sf::Event::MouseButtonPressed) {
    //                            printf("Pressed left\n");
                                mouseLeftPressed2 = true;
                                trackball(prev_quat2, 0.0, 0.0, 0.0, 0.0);
                            } else if (event.type == sf::Event::MouseButtonReleased) {
    //                            printf("Released left\n");
                                mouseLeftPressed2 = false;
                            }

                        } else if (event.mouseButton.button == sf::Mouse::Right) {

                            if (event.type == sf::Event::MouseButtonPressed) {
    //                            printf("Pressed right\n");
                                mouseRightPressed2 = true;
                            } else if (event.type == sf::Event::MouseButtonReleased) {
    //                            printf("Released right\n");
                                mouseRightPressed2 = false;
                            }

                        } else if (event.mouseButton.button == sf::Mouse::Middle) {

                            if (event.type == sf::Event::MouseButtonPressed) {
                                mouseMiddlePressed2 = true;
    //                            printf("Pressed middle\n");
                            } else if (event.type == sf::Event::MouseButtonReleased) {
                                mouseMiddlePressed2 = false;
    //                            printf("Released middle\n");
                            }

                        }
                    } else if (event.type == sf::Event::MouseMoved) {
                        if (loaded==1) printf("14-");

                        double mouse_x = (double) event.mouseMove.x ;
                        double mouse_y = (double) event.mouseMove.y ;
                        if (mouseLeftPressed2)
                        {
                            trackball(prev_quat2,
                                      rotScale * (2.0f * prevMouseX2 - width2) / (float)width2,
                                      rotScale * (height2 - 2.0f * prevMouseY2) / (float)height2,
                                      rotScale * (2.0f * mouse_x - width2) / (float)width2,
                                      rotScale * (height2 - 2.0f * mouse_y) / (float)height2);

                            add_quats(prev_quat2, curr_quat2, curr_quat2);
                        }
                        else if (mouseMiddlePressed2)
                        {
                            eye2[0] -= transScale * (mouse_x - prevMouseX2) / (float)width2;
                            lookat2[0] -= transScale * (mouse_x - prevMouseX2) / (float)width2;
                            eye2[1] += transScale * (mouse_y - prevMouseY2) / (float)height2;
                            lookat2[1] += transScale * (mouse_y - prevMouseY2) / (float)height2;
                        }
                        else if (mouseRightPressed2)
                        {
                            eye2[2] += 2*transScale * (mouse_y - prevMouseY2) / (float)height2;
                            lookat2[2] +=2* transScale * (mouse_y - prevMouseY2) / (float)height2;
                        }

                        // Update mouse point
                        prevMouseX2 = mouse_x;
                        prevMouseY2 = mouse_y;
                        if (loaded==1) printf("15-");

                    } else if (event.type == sf::Event::KeyPressed) {
                        if (loaded==1) printf("16-");
                        switch(event.key.code)
                        {
                            case sf::Keyboard::Left:  { exit_code=-10;  exit_thread = true; break; }
                            case sf::Keyboard::Right: { exit_code=-11;  exit_thread = true; break; }
                            case sf::Keyboard::Up:    { exit_code=-12;  exit_thread = true; break; }
                            case sf::Keyboard::Down:  { exit_code=-13;  exit_thread = true; break; }
                            case sf::Keyboard::Q:     { exit_code=-1;   exit_thread = true; keep_running[win_num]=0; break; }
                        }
                        if (event.key.control && exit_code<=-10) {
                            if (loaded==1) printf("17-");
                        }
                        else if (exit_code<=-10) {
                            int x_now=cur_x,y_now=cur_y;
                            if (exit_code==-10) { cur_x--; if (cur_x<0) cur_x=0; }
                            else if (exit_code==-11) { cur_x++; if (cur_x>=max_x) cur_x=max_x-1; }
                            else if (exit_code==-12) { cur_y--; if (cur_y<0) cur_y=0; }
                            else if (exit_code==-13) { cur_y++; if (cur_y>=max_y) cur_y=max_y-1; }
                            if (x_now!=cur_x || y_now!=cur_y) {
                                int cool=1;
                                for (auto u : Pacman_Objects) {
                                    if (u.map_x==cur_x && u.map_y==cur_y) {
                                        cool=0;
                                        break;
                                    }
                                }
                                if (cool==0) {
                                    if (combine==1)
                                        printf("Already loaded: %d,%d: %s\n",cur_x,cur_y,get_octant_Amsterdam(cur_x,cur_y).c_str());
                                    else
                                        printf("Already loaded: %d,%d: %s\n",cur_x,cur_y,get_octant_Enschede(cur_x,cur_y).c_str());

                                } else {
                                    std::string str;
                                    if (combine==1)
                                        str=get_octant_Amsterdam(cur_x,cur_y);
                                    else
                                        str=get_octant_Enschede(cur_x,cur_y);
                                    printf("Trying: %d,%d -> %s\n",cur_x,cur_y,str.c_str());
                                    int found=str.find_last_of("/\\");
                                    if (test_for_pngfiles(str.substr(0,found))==true) {
//                                        while (window.pollEvent(event));
                                        pac_obj.gDrawObjects.clear();
                                        pac_obj.materials.clear();
                                         pac_obj.textures.clear();
//                                        Pacman_Object pac_obj;
                                        window.setActive(true);
                                        if (true == LoadObjAndConvert(pac_obj.bmin, pac_obj.bmax, pac_obj.gDrawObjects, pac_obj.materials, pac_obj.textures, str.c_str()))
    //                                    pac_obj = new Pacman_Object;
    //                                    if (true == LoadObjAndConvert(pac_obj->bmin, pac_obj->bmax, &pac_obj->gDrawObjects, pac_obj->materials, pac_obj->textures, str.c_str()))
                                        {
                                            pac_obj.map_x=cur_x;
                                            pac_obj.map_y=cur_y;
                                            Pacman_Objects.push_back(pac_obj);
    //                                        pac_obj->map_x=cur_x;
    //                                        pac_obj->map_y=cur_y;
    //                                        Pacman_Objects.push_back(*pac_obj);
                                            for (auto u : Pacman_Objects) {
                                                if (u.bmin[0]<bmin[0]) bmin[0]=u.bmin[0]; if (u.bmax[0]>bmax[0]) bmax[0]=u.bmax[0];
                                                if (u.bmin[1]<bmin[1]) bmin[1]=u.bmin[1]; if (u.bmax[1]>bmax[1]) bmax[1]=u.bmax[1];
                                                if (u.bmin[2]<bmin[2]) bmin[2]=u.bmin[2]; if (u.bmax[2]>bmax[2]) bmax[2]=u.bmax[2];
                                            }
                                            printf("New object loaded: %d,%d: %s\n",cur_x,cur_y,str.c_str());
                                            sprintf(window_title,"(%d,%d)/(%d,%d) %s",cur_x,cur_y,max_x,max_y,str.c_str());
                                            window.setTitle(window_title);
                                            loaded=1;round=3;
                                        } else {
                                            printf("Error loading new object: %d,%d: %s\n",cur_x,cur_y,str.c_str());
    //                                        delete pac_obj;
                                        }
                                        window.setActive(false);
//                                        while (window.pollEvent(event));
                                    }
                                }
                            }
                            exit_thread=false;
                            exit_code=0;
                        } else if ((event.key.code == sf::Keyboard::Escape)) {
                            exit_code=0;
                            exit_thread = true;
                        } else if ((event.key.code == sf::Keyboard::Enter)) {
                            if (mipmapEnabled) {
                                if (!texture.loadFromFile("resources/texture.jpg")) {
                                    render_locker.lock();
                                    ready_to_render[win_num]=0;
                                    render_locker.unlock();
                                    exit_code=EXIT_FAILURE;
                                    exit_thread = true;
                                }
                                mipmapEnabled = false;
                            } else {
                                texture.generateMipmap();
                                mipmapEnabled = true;
                            }
                        } else if (event.key.code == sf::Keyboard::N) {
                            exit_code=-99;
                            exit_thread = true;
                        } else if (event.key.code == sf::Keyboard::Space) {
                            old_size[win_num]=window.getSize();
                            old_pos[win_num]=window.getPosition();
                            sRgb = !sRgb;
                            exit_code=-98;
                            exit_thread = true;
//                            window.close();
                        }
                    } else if (event.type == sf::Event::Resized) {
                        window.setActive(true);
                        glViewport(0, 0, event.size.width, event.size.height);

                        glMatrixMode(GL_PROJECTION);
                        glLoadIdentity();
                        gluPerspective(45.0, (float)event.size.width / (float)event.size.height, 0.01f, 100.0f);
                        glMatrixMode(GL_MODELVIEW);
                        glLoadIdentity();

                        window.setActive(false);
                        width2 = event.size.width;
                        height2 =event.size.height;
    //                    background.setPosition(width2/2,height2/2.0);
                    }
                }
                if (loaded==1) printf("1-");
                trackball(prev_quat2,
                          rotScale * (2.0f * 1920.0/2.0 - width2) / (float)width2,
                          rotScale * (height2 - 2.0f * 1080.0/2.0) / (float)height2,
                          rotScale * (2.0f * 1920.0/2.0-1 - width2) / (float)width2,
                          rotScale * (height2 - 2.0f * 1080.0/2.0) / (float)height2);

                add_quats(prev_quat2, curr_quat2, curr_quat2);
                if (loaded==1) printf("2-");
                if (exit_thread || !window.isOpen())
                    continue;

                window.setActive(true);
                if (loaded==1) printf("3-");
                glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                glEnable(GL_DEPTH_TEST);
                glDepthMask(GL_TRUE);   //added
                glClearDepth(1.f);      //added

                window.setActive(false);

                window.pushGLStates();
    //            background.setScale(1.2,1.2);
                if (win_num)
                    background.setRotation(clock.getElapsedTime().asSeconds()*15);
                else
                    background.setRotation(-clock.getElapsedTime().asSeconds()*10);

                window.draw(background);

                window.popGLStates();

                window.setActive(true);

                if (loaded==1) printf("4-");

                glEnable(GL_TEXTURE_2D);
                glMatrixMode(GL_MODELVIEW);
                glLoadIdentity();
                GLfloat mat[4][4];
                gluLookAt(eye2[0], eye2[1], eye2[2], lookat2[0], lookat2[1], lookat2[2], up2[0],   up2[1], up2[2]);
                build_rotmatrix(mat, curr_quat2);
                glMultMatrixf(&mat[0][0]);
                glScalef(1.0f / maxExtent, 1.0f / maxExtent, 1.0f / maxExtent);
                if (loaded==1) printf("5-");

    //            static double lastx=0.0;
    //            double lastonex=clock.getElapsedTime().asSeconds();
    //            glRotatef(lastonex*5,sin(lastonex/20),sin(lastonex/18),sin(lastonex/22));

                glTranslatef(-0.5 * (bmax[0] + bmin[0]), -0.5 * (bmax[1] + bmin[1]),  -0.5 * (bmax[2] + bmin[2]));

                if (smooth)
                    glShadeModel(GL_SMOOTH);
                else
                    glShadeModel(GL_FLAT);

                diff_draw.lock();
                int d_d=different_draw;
                diff_draw.unlock();
                if (loaded==1) printf("6-");
                if (d_d) {
                    diff_draw.lock();
                    different_draw=0;
                    diff_draw.unlock();
                    for (auto u : Pacman_Objects) {
                        Get_Draw(u.gDrawObjects, u.materials, u.textures);
                    }
                } else {
                    if (loaded==1) printf("7-");
                    for (auto u : Pacman_Objects) {
                        Draw(u.gDrawObjects, u.materials, u.textures);
                    }
                    if (loaded==1) printf("8-");
                }

                if (loaded==1) printf("8.1-");
//                if (loaded==1) while (window.pollEvent(event));

                window.setActive(false);
                if (loaded==0 && fade<3800+rand()%100) {
                    if (loaded==1) printf("8.2-");
                    window.pushGLStates();
                    if (loaded==1) printf("8.3-");
                    if (loaded) printf(hoppa);
                    window.draw(text);
                    if (loaded==1) printf("8.4-");
                    if (fade<2500+rand()%500) window.draw(sRgbInstructions);
                    if (loaded==1) printf("8.5-");
                    if (fade<2000+rand()%500) window.draw(mipmapInstructions);
                    if (loaded==1) printf("8.6-");
                    window.popGLStates();
                    if (loaded==1) printf("8.7-");
                }
                fade++;
               if (loaded==1) printf("9-");
                window.display();
                if (loaded==1) printf("10-");
//                swoop++;
                if (swoop>60*60) {
                    swoop=0;
                    exit_code=-99;
                    exit_thread=true;
                }
            }

            render_locker.lock();
            ready_to_render[win_num]=0;
            render_locker.unlock();

            window.setActive(true);

            int num_p=0;
            for (auto p : Pacman_Objects) {
                GLuint gluint_arr[p.textures.size()];
                int num_com=0;
                for (auto u : p.textures) {
                    gluint_arr[num_com++]=u.second;
                    if (!(num_com&0xff) || num_com==p.textures.size()) printf("glDeleteTextures() %d object# %d id=%d     \r",p.textures.size(),num_p,(int)u.second);
                }
                num_p++;
                glDeleteTextures((GLsizei)p.textures.size(), gluint_arr);
            }
            if (num_p>0) printf("\n");
            num_p=0;
            for (auto p : Pacman_Objects) {
                GLuint gluint_arr[p.gDrawObjects.size()];
                int num_com=0;
                for (auto u : p.gDrawObjects) {
                    gluint_arr[num_com++]=u.vb_id;
                    if (!(num_com&0xff) || num_com==p.gDrawObjects.size()) printf("glDeleteBuffers() %d object# %d id=%d     \r",p.gDrawObjects.size(),num_p,(int)u.vb_id);
                }
                num_p++;
                glDeleteBuffers((GLsizei)p.gDrawObjects.size(), gluint_arr);
            }
            if (num_p>0) printf("\n");
            Pacman_Objects.clear();

            window.setActive(false);
            if (window.isOpen()) {
                old_size[win_num]=window.getSize();
                old_pos[win_num]=window.getPosition();
                window.close();
            }
            if (bar_on[win_num]==0) ShowTaskBar(true);
            bar_on[win_num]=1;
        }

        // if the thread has a current rendering context ...
        if(hglrc) {
//            wglDeleteContext(hglrc);
//            printf("wglDeleteContext()\n");
//            wglMakeCurrent(NULL, NULL) ;
        }
        if (exit_code!=-1)
            printf("Exiting, staying active\n");
        if (exit_code==-99) {
            return exit_code;
//            do_SFMLGL2(exit_code-1000);
        } else if (exit_code<=-10) {
            do_SFMLGL2(exit_code-1000);
        } else {
            if (exit_code!=-1) {
                return_val[win_num]=exit_code;
                is_activated_window[win_num]=0;
                do {
                    sf::sleep(sf::milliseconds(500));
                }
                while (!is_activated_window[win_num]);
            }
        }
        if (exit_code!=-1) {
            strcpy(filename,arg2_thread);
            cur_x=send_cur_x_thread;
            cur_y=send_cur_y_thread;
            max_x=send_max_x_thread;
            max_y=send_max_y_thread;
            combine=combine_thread;
            exit_code=0;
            exit_thread=0;
        }
    }
    printf("Exiting, leaving thread\n");
    ShowTaskBar(true);
    return exit_code;
}

void expres(int objnum) {
    std::vector<Pacman_Object> Pacman_Objects=*Pacman_Objects_Global[objnum];

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
        if (!backgroundTexture.loadFromFile("resources/background.jpg")) {
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
    SFMLView1.setActive(true);
//mainwindow->context()->makeCurrent(this);
//    SFMLView1.m_context()->makeCurrent(this);
//    glfwMakeContextCurrent(GLUtil::_loaderWindow);
//    glfwMakeContextCurrent(SFMLView1);
//    wglMakeCurrent(NULL, NULL) ;

//    glfwMakeContextCurrent((GLFWwindow*)window_handle);
//    wglMakeCurrent (hdc,hglrc);
    wglMakeCurrent (hdc_sfmlview1,hglrc_sfmlview1);
//    glfwMakeContextCurrent(SFMLView1);
//    glfwMakeContextCurrent((GLFWwindow*)m_context_window);
//    glfwSwapInterval(1);
//    SFMLView1.m_context()->makeCurrent(this);
//hdc
//    hWndMain

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
    for (auto u : Pacman_Objects) {
        if (u.bmin[0]<bmin[0]) bmin[0]=u.bmin[0]; if (u.bmax[0]>bmax[0]) bmax[0]=u.bmax[0];
        if (u.bmin[1]<bmin[1]) bmin[1]=u.bmin[1]; if (u.bmax[1]>bmax[1]) bmax[1]=u.bmax[1];
        if (u.bmin[2]<bmin[2]) bmin[2]=u.bmin[2]; if (u.bmax[2]>bmax[2]) bmax[2]=u.bmax[2];
    }
    int ffirst=1;
    if (ffirst==1) {
        ffirst=0;
        printf("bmin = %f, %f, %f\n", bmin[0], bmin[1], bmin[2]);
        printf("bmax = %f, %f, %f\n", bmax[0], bmax[1], bmax[2]);
    }
    float maxExtent = 0.5f * (bmax[0] - bmin[0]);
    if (maxExtent < 0.5f * (bmax[1] - bmin[1])) maxExtent = 0.5f * (bmax[1] - bmin[1]);
    if (maxExtent < 0.5f * (bmax[2] - bmin[2])) maxExtent = 0.5f * (bmax[2] - bmin[2]);

//    glViewport(0, 0, SFMLView1.getSize().x, SFMLView1.getSize().y);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45.0, (float)SFMLView1.getSize().x / (float)SFMLView1.getSize().y, 0.01f, 100.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

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

    for (auto u : Pacman_Objects) {
        Draw(u.gDrawObjects, u.materials, u.textures);
    }
extern sf::WindowHandle sfmlview1_handle;
//    glfwMakeContextCurrent((GLFWwindow*)SFMLView1.m_context);
//    glfwMakeContextCurrent((GLFWwindow*)sfmlview1_handle);
//    wglMakeCurrent (hdc_sfmlview1,hglrc_sfmlview1);
//    SFMLView1.setActive(true);
//    SFMLView1.setActive(false);
//    glfwSwapInterval(1);
}

void get_3d_data() {
    GLenum format;
    GLsizei width;
    GLsizei height;
    GLenum type=GL_UNSIGNED_BYTE;
    size_t components;

    switch(format) {
    case GL_BGR:
    case GL_RGB:
        components = 3; break;

    case GL_BGRA:
    case GL_RGBA:
        components = 4; break;

    case GL_ALPHA:
    case GL_LUMINANCE:
        components = 1; break;
    }

    GLubyte *data = (GLubyte*) malloc(components * width * height);
    if( data ) {
        glReadPixels(0, 0, width, height, format, type, data);
    }
}

void display_get3d()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10, 10, -10, 10, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glScalef(5,5,5);
    glBegin(GL_QUADS);
    glColor3ub(255,0,0);
    glVertex2f(-1,-1);
    glColor3ub(0,255,0);
    glVertex2f(1,-1);
    glColor3ub(0,0,255);
    glVertex2f(1,1);
    glColor3ub(255,255,255);
    glVertex2f(-1,1);
    glEnd();

    glutSwapBuffers();
}

void mouse_get3d( int x, int y )
{
    // 4 bytes per pixel (RGBA), 1x1 bitmap
    unsigned char pixels[4];
    glFinish();
    glReadPixels
        (
        x, glutGet( GLUT_WINDOW_HEIGHT ) - y,
        1, 1,
        GL_RGBA, GL_UNSIGNED_BYTE, &pixels[0]
        );

    std::cout << "r: " << (int)pixels[0] << std::endl;
    std::cout << "g: " << (int)pixels[1] << std::endl;
    std::cout << "b: " << (int)pixels[2] << std::endl;
    std::cout << "a: " << (int)pixels[3] << std::endl;
    std::cout << std::endl;
}

int main_get3d(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);

    glutInitWindowSize(800,600);
    glutCreateWindow("glReadPixels()");

    glutDisplayFunc(display_get3d);
    glutPassiveMotionFunc(mouse_get3d);
    glutMainLoop();
    return 0;
}

struct one_elem {
    GLfloat idx0[3+3+2];
    GLfloat idx1[3+3+2];
    GLfloat idx2[3+3+2];
};

static void Get_Draw(const std::vector<DrawObject>& drawObjects,  std::vector<tinyobj::material_t>& materials, std::map<std::string, GLuint>& textures)
{
    glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_BACK, GL_FILL);

    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(1.0, 1.0);
//color out
    GLsizei stride = (3 + 3 + 2) * sizeof(float);
//    GLsizei stride = (3 + 3 + 3 + 2) * sizeof(float);
    for (size_t i = 0; i < drawObjects.size(); i++)
    {
        DrawObject o = drawObjects[i];
        if (o.vb_id < 1)
        {
            continue;
        }
        glBindBuffer(GL_ARRAY_BUFFER, o.vb_id);
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_NORMAL_ARRAY);
//color out
//        glEnableClientState(GL_COLOR_ARRAY);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glBindTexture(GL_TEXTURE_2D, 0);

        if (i<20) {
            printf("Object#: %d(%d) Material id: %d(%d) ",(int)i,(int)drawObjects.size(),(int)o.material_id,materials.size());
            if ((o.material_id < materials.size()))
            {
                std::string diffuse_texname = materials[o.material_id].diffuse_texname;
                if (textures.find(diffuse_texname) != textures.end())
                {
                    glBindTexture(GL_TEXTURE_2D, textures[diffuse_texname]);
                    GLint texDims[2];
                    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &texDims[0]);
                    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &texDims[1]);
                    printf(" Texture size: x=%d,y=%d textures[%s]=%d ",(int)texDims[0],(int)texDims[1],diffuse_texname.c_str(),(int)textures[diffuse_texname]);
                } else {
                    printf(" Texture not found: textures[%s] ",diffuse_texname.c_str());
                }
            } else {
                    printf(" Material id > size ");
            }
        }

        glVertexPointer(3, GL_FLOAT, stride, (const void*)0);
        glNormalPointer(GL_FLOAT, stride, (const void*)(sizeof(float) * 3));
//color out
//        glColorPointer(3, GL_FLOAT, stride, (const void*)(sizeof(float) * 6));

//color out
        glTexCoordPointer(2, GL_FLOAT, stride, (const void*)(sizeof(float) * 6));
//        glTexCoordPointer(2, GL_FLOAT, stride, (const void*)(sizeof(float) * 9));


        if (i<20) {
            printf("#Triangles=%d\n",(int)o.numTriangles);
            if (i<5) {
                GLsizeiptr size=stride*o.numTriangles;
                GLuint target=o.vb_id;
                GLintptr offset=0;
                one_elem *elements = new one_elem [o.numTriangles];
                glGetNamedBufferSubData(target, 	offset, size*3, (GLvoid*)	elements);
                CheckErrors("Huh?");
                size_t T;
                for (T=0; T<o.numTriangles && (T<5);T++) {
        //        for (size_t T=0; T<o.numTriangles;T++) {
                    printf("Triangle %d(%d) of Object#: %d(%d)\n",(int)T,(int)o.numTriangles,(int)i,(int)drawObjects.size());

                    printf("Vertexes: (% 12.7f,% 12.7f,% 12.7f) (% 12.7f,% 12.7f,% 12.7f) (% 12.7f,% 12.7f,% 12.7f)\n",
                             (float)elements[T].idx0[0],(float)elements[T].idx0[1],(float)elements[T].idx0[2],
                             (float)elements[T].idx1[0],(float)elements[T].idx1[1],(float)elements[T].idx1[2],
                             (float)elements[T].idx2[0],(float)elements[T].idx2[1],(float)elements[T].idx2[2]);
                    printf("Normals:  (% 12.7f,% 12.7f,% 12.7f) (% 12.7f,% 12.7f,% 12.7f) (% 12.7f,% 12.7f,% 12.7f)\n",
                             (float)elements[T].idx0[3],(float)elements[T].idx0[4],(float)elements[T].idx0[5],
                             (float)elements[T].idx1[3],(float)elements[T].idx1[4],(float)elements[T].idx1[5],
                             (float)elements[T].idx2[3],(float)elements[T].idx2[4],(float)elements[T].idx2[5]);
                    printf("Texture:  (% 12.7f,% 12.7f)              (% 12.7f,% 12.7f)              (% 12.7f,% 12.7f)\n",
                             (float)elements[T].idx0[6],(float)elements[T].idx0[7],
                             (float)elements[T].idx1[6],(float)elements[T].idx1[7],
                             (float)elements[T].idx2[6],(float)elements[T].idx2[7]);
                }
                if (T<o.numTriangles) printf("(bufferdata) etc\n.\n.\n");
                delete [] elements;
            }
        } else {
            if (i==20) printf("(shapes) etc\n.\n.\n");
        }

        glDrawArrays(GL_TRIANGLES, 0, 3 * o.numTriangles);
        CheckErrors("drawarrays");
        glBindTexture(GL_TEXTURE_2D, 0);
    }


    // draw wireframe
    /*
      glDisable(GL_POLYGON_OFFSET_FILL);
      glPolygonMode(GL_FRONT, GL_LINE);
      glPolygonMode(GL_BACK, GL_LINE);

      glColor3f(0.0f, 0.0f, 0.4f);
      for (size_t i = 0; i < drawObjects.size(); i++) {
        DrawObject o = drawObjects[i];
        if (o.vb_id < 1) {
          continue;
        }

        glBindBuffer(GL_ARRAY_BUFFER, o.vb_id);
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_NORMAL_ARRAY);
        glDisableClientState(GL_COLOR_ARRAY);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        glVertexPointer(3, GL_FLOAT, stride, (const void*)0);
        glNormalPointer(GL_FLOAT, stride, (const void*)(sizeof(float) * 3));
        glColorPointer(3, GL_FLOAT, stride, (const void*)(sizeof(float) * 6));
        glTexCoordPointer(2, GL_FLOAT, stride, (const void*)(sizeof(float) * 9));

        glDrawArrays(GL_TRIANGLES, 0, 3 * o.numTriangles);
        CheckErrors("drawarrays");
      }
    */

}



/*
    GLint texDims[2];
glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, texDims);
//glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, texDims, 1);


int[] texDims = new int[2];
glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, texDims, 0);
glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, texDims, 1);


void glGetTexImage (GLenum      target,
                    GLint       level,
                    GLenum      format, // GL will convert to this format
                    GLenum      type,   // Using this data type per-pixel
                    GLvoid *    img);
*/


#include "test_data.hpp"


