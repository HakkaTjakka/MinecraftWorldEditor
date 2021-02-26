
bool glew_initor=false;
bool glwf_initor=false;
//#include "stb_image.h"
//double
//#define STB_IMAGE_STATIC
//#define _WIN32
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


static void Get_Draw(const std::vector<DrawObject>& drawObjects,  std::vector<tinyobj::material_t>& materials, std::map<std::string, GLuint>& textures);
bool launch_OBJLOADER(float bmin[3], float bmax[3], std::vector<DrawObject>& drawObjects, std::vector<tinyobj::material_t>& materials, std::map<std::string, GLuint>& textures, char* filename, int win_num);
//static void Draw_one_shape(const std::vector<DrawObject>& drawObjects, std::vector<tinyobj::material_t>& materials, std::map<std::string,GLuint>& textures, int ii);

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
float adapt_curr_quat[4];
float prev_quat[4];
float eye[3], lookat[3], up[3];


GLFWwindow* window;

