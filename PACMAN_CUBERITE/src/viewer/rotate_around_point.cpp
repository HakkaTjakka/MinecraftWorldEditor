#include <GL/glew.h>
#include <GL/freeglut.h>

#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>"
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/glm.hpp>
#include <glm/common.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include <GL/glu.h>
#include <GLFW/glfw3.h>

#include <SFML/Graphics.hpp>
#include <float.h>
#include <string>
#include <cmath>
extern bool interpolate_on;
void makeFrustum(double fovY, double aspectRatio, double front, double back, int frustum_toggle, float eye2[3]);
extern void build_rotmatrix_glm(glm::mat4& m, const float q[4]);
extern glm::vec4 test_pos;

extern void lat_lon_to_rel(double latitude, double longitude, double &rel_pos_in_map_x, double &rel_pos_in_map_y );
extern void rel_to_lat_lon(double rel_pos_in_map_x, double rel_pos_in_map_y, double &latitude, double &longitude);

glm::vec4 add_xyz4;

glm::mat4 exporter;
glm::mat4 exporter2;
extern float g_rotate_object_x;
extern float g_rotate_object_y;
extern float g_rotate_object_z;
extern int mirror;

void rotate_around_point(glm::vec3 move_object, glm::vec3 &add_xyz, std::string area, double lat, double lon, bool rot_on, bool interpolate_on, glm::mat4 rot_mat, glm::mat4 &test, float curr_quat2[4], float maxExtent, float bmin[3], float bmax[3]) {
    static bool first=true;
    static glm::mat4 flip_xz(1.0f);
    static glm::mat4 flip_y(1.0f);
    if (first) {
        first=false;
        flip_xz = glm::rotate(flip_xz, float(-90.0*M_PI/180.0), glm::vec3(1.0,0.0,0.0)) ;
        flip_xz = glm::rotate(flip_xz, float(-90.0*M_PI/180.0), glm::vec3(0.0,0.0,1.0)) ;
        flip_y  = glm::rotate(flip_y,  float(-90.0*M_PI/180.0), glm::vec3(0.0,1.0,0.0)) ;
    }

    static glm::mat4 rot_matrix2(1.0f);
    if (interpolate_on) rot_matrix2=glm::mat4(rot_mat);
//    else if (rot_on) rot_matrix2=exporter2;
    else build_rotmatrix_glm(rot_matrix2, curr_quat2);

    glm::vec3 NORMALz = glm::vec3((float)(cos(lat*M_PI/180.0)*cos(lon*M_PI/180.0)), (float)(cos(lat*M_PI/180)*sin(lon*M_PI/180)), (float)(sin(lat*M_PI/180)));
    NORMALz = glm::normalize(NORMALz);
    test=glm::mat4(1.0f);

    if (area!="Models") {
        add_xyz4 = glm::vec4(move_object.x,move_object.y,move_object.z,1.0f) * test;
        test = glm::rotate(test, float(g_rotate_object_x*M_PI/180.0), {1.0,0.0,0.0} ) ;
        test = glm::rotate(test, float(g_rotate_object_y*M_PI/180.0), {0.0,1.0,0.0} ) ;
        test = glm::rotate(test, float(-g_rotate_object_z*M_PI/180.0), {0.0,0.0,1.0} ) ;
        test = test * flip_xz;
//        test = glm::rotate(test, float(-90.0*M_PI/180.0), glm::vec3(1.0,0.0,0.0)) ;
//        test = glm::rotate(test, float(-90.0*M_PI/180.0), glm::vec3(0.0,0.0,1.0)) ;
    } else {
        if (lat!=0.0 || lon!=0.0) {
            test = glm::eulerAngleYX(  (float)((lat)*M_PI/180.0) ,(float)((lon)*M_PI/180.0));
            test = test * flip_y;
//            test = glm::rotate(test, float(-90.0*M_PI/180.0), glm::vec3(0.0,1.0,0.0)) ;
            test = glm::rotate(test, float(-90.0*M_PI/180.0), {NORMALz.x,NORMALz.y,NORMALz.z} ) ;
        } else {
            add_xyz4 = glm::vec4(move_object.x,move_object.y,move_object.z,1.0f) * test;
            test = glm::rotate(test, float(g_rotate_object_x*M_PI/180.0), {1.0,0.0,0.0} ) ;
            test = glm::rotate(test, float(g_rotate_object_y*M_PI/180.0), {0.0,1.0,0.0} ) ;
            test = glm::rotate(test, float(-g_rotate_object_z*M_PI/180.0), {0.0,0.0,1.0} ) ;
        }
    }

    add_xyz.x = add_xyz4.x;
    add_xyz.y = add_xyz4.y;
    add_xyz.z = add_xyz4.z;

    test = rot_matrix2 * test;
    exporter=test;
    glMultMatrixf((float*)&test);

    return;
}

extern bool remember_911;
extern bool remember_911_2;
extern bool remember_911_3;
extern sf::RectangleShape rectangle;
extern int frustum_count_x;
extern int frustum_count_y;

void make_lookat( float perspective[4], int frustum_toggle, float eye2[3], float lookat2[3],  float up2[3], glm::vec3 move_object, sf::Vector2u window_size, bool rot_on, float maxExtent) {

    makeFrustum(perspective[0],perspective[1],perspective[2],perspective[3],frustum_toggle, eye2);


    if (rot_on || 1) {
        if (frustum_toggle==1) {
            gluLookAt(
                        eye2[0],       eye2[1],     eye2[2]+3.0f ,
                        lookat2[0],    lookat2[1],    lookat2[2],
                        up2[0],   up2[1], up2[2]);
        } else {
            gluLookAt(  eye2[0],       eye2[1],     eye2[2],
                        lookat2[0],    lookat2[1],    lookat2[2],
                        up2[0],   up2[1], up2[2]);
//            gluLookAt(  eye2[0]     +move_object.x/(float)window_size.x,  eye2[1]   +move_object.y/(float)window_size.y,    eye2[2]   +move_object.z/1000.0,
//                        lookat2[0]  +move_object.x/(float)window_size.x,  lookat2[1]+move_object.y/(float)window_size.y,    lookat2[2]+move_object.z/1000.0,
//                        up2[0],   up2[1], up2[2]);
        }
    } else {
        if (frustum_toggle==1) {
            gluLookAt(
                        eye2[0]+move_object.x/(float)window_size.x,       eye2[1]+move_object.y/(float)window_size.y,     3.0f + move_object.z/1000.0,
                        lookat2[0]+move_object.x/(float)window_size.x,    lookat2[1]+move_object.y/(float)window_size.y,    lookat2[2]+move_object.z/1000.0,
                        up2[0],   up2[1], up2[2]);
        } else {
            gluLookAt(  eye2[0]+move_object.x/(float)window_size.x,       eye2[1]+move_object.y/(float)window_size.y,     eye2[2]+move_object.z/1000.0,
                        lookat2[0]+move_object.x/(float)window_size.x,    lookat2[1]+move_object.y/(float)window_size.y,    lookat2[2]+move_object.z/1000.0,
                        up2[0],   up2[1], up2[2]);
        }
    }
}


void makeFrustum(double fovY, double aspectRatio, double front, double back, int frustum_toggle, float eye2[3])
{
    static const double DEG2RAD = 3.14159265 / 180;

    double tangent = tan(fovY/2 * DEG2RAD);   // tangent of half fovY
    double height = front * tangent;          // half height of near plane
    double width = height * aspectRatio;      // half width of near plane

    double tot_width = width*2.0;      // half width of near plane
    double tot_height = height*2.0;
    double start_x,start_y;
    double end_x,end_y;
    if (remember_911 || remember_911_2) {

        double screen_x_start=  rectangle.getPosition().x+(float)frustum_count_x*rectangle.getSize().x;
        double screen_x_end=    rectangle.getPosition().x+((float)frustum_count_x+1.0)*rectangle.getSize().x;
        double screen_y_start=  rectangle.getPosition().y+(float)frustum_count_y*rectangle.getSize().y;
        double screen_y_end=    rectangle.getPosition().y+((float)frustum_count_y+1.0)*rectangle.getSize().y;

/*
        if (frustum_count_x==frustum_size_x-1 && frustum_count_y==frustum_size_y-1) {
            printf("\nTOT PICTURE %4d,%4d FROM %4d,%4d TO %4d,%4d => FROM %30.15f %30.15f TO %30.15f  %30.15f\n\n",
                   frustum_size_x,frustum_size_y,
                   int(rectangle.getPosition().x),
                   int(rectangle.getPosition().y),
                   int(rectangle.getPosition().x+(frustum_size_x)*rectangle.getSize().x),
                   int(rectangle.getPosition().y+(frustum_size_y)*rectangle.getSize().y),

                   -width+tot_width*rectangle.getPosition().x/1920.0,
                   -height+tot_height*rectangle.getPosition().y/1080.0,
                   -width+tot_width*(rectangle.getPosition().x+(frustum_size_x)*rectangle.getSize().x)/1920.0,
                   -height+tot_height*(rectangle.getPosition().y+(frustum_size_y)*rectangle.getSize().y)/1080.0);
        }
*/

//        screen_width=screen_x_end-screen_x_start;
//        screen_height=screen_y_end-screen_y_start;

        start_x=-width+tot_width*screen_x_start/1920.0;
        start_y=height-tot_height*screen_y_start/1080.0;
//        start_y=-height+tot_height*screen_y_start/1080.0;

        end_x=-width+tot_width*screen_x_end/1920.0;
        end_y=height-tot_height*screen_y_end/1080.0;
//        end_y=-height+tot_height*screen_y_end/1080.0;

//        tot_width=tot_width*screen_width/1920.0;
//        tot_height=tot_height*screen_height/1080.0;


        double screen_x_start_d=start_x;
        double screen_y_start_d=end_y;
//        double screen_y_start_d=start_y;
        double screen_x_end_d=end_x;
        double screen_y_end_d=start_y;
//        double screen_y_end_d=end_y;


        if (remember_911_3)
            printf("PICTURE %4d,%4d FROM %14.10f,%14.10f TO %14.10f,%14.10f => FROM %14.10f %14.10f TO %14.10f  %14.15f\n",
                    frustum_count_x,frustum_count_y,
                    screen_x_start,screen_y_start,screen_x_end,screen_y_end,
                    screen_x_start_d,screen_y_start_d,screen_x_end_d,screen_y_end_d);
//        if (!remember_911_2) printf("\n");


/*
        double screen_x_start_d=start_x+screen_x_start*tot_width/screen_width;
        double screen_y_start_d=start_y+screen_y_start*tot_height/screen_height;
        double screen_x_end_d=start_x+screen_x_end*tot_width/screen_width;
        double screen_y_end_d=start_y+screen_y_end*tot_height/screen_height;
        double screen_x_start_d=-width+screen_x_start*tot_width/screen_width;
        double screen_y_start_d=-height+screen_y_start*tot_height/screen_height;
        double screen_x_end_d=-width+screen_x_end*tot_width/screen_width;
        double screen_y_end_d=-height+screen_y_end*tot_height/screen_height;
*/

        if (frustum_toggle==0)
            glFrustum(screen_x_start_d, screen_x_end_d, screen_y_start_d, screen_y_end_d, front, back);
        else if (frustum_toggle==1)
            glOrtho(screen_x_start_d*(100.0+eye2[2]*50.0),
                    screen_x_end_d*(100.0+eye2[2]*50.0),
                    screen_y_start_d*(100.0+eye2[2]*50.0),
                    screen_y_end_d*(100.0+eye2[2]*50.0),
                    front, back);
//            glOrtho(-screen_x_start_d*(100.0+eye2[2]*25),
//                     screen_x_end_d*(100.0+eye2[2]*25),
//                     -screen_y_start_d*(100.0+eye2[2]*25),
//                     screen_y_end_d*(100.0+eye2[2]*25),
//                     front, back);

//            glOrtho(-width*(100.0+eye2[2]*25), width*(100.0+eye2[2]*25), -height*(100.0+eye2[2]*25), height*(100.0+eye2[2]*25), front, back);

/*
        frustum_count_x--;
        if (frustum_count_x<0) {
            frustum_count_x=frustum_size_x-1;
            frustum_count_y--;
            printf("\n");
            if (frustum_count_y<0) {
                frustum_count_x=frustum_size_x-1;
                frustum_count_y=frustum_size_y-1;
                remember_911_set_off=true;
            }
        }
*/

    } else {
        if (frustum_toggle==0)
            glFrustum(-width, width, -height, height, front, back);
        else if (frustum_toggle==1)
            glOrtho(-width*(100.0+eye2[2]*50.0),
                     width*(100.0+eye2[2]*50.0),
                     -height*(100.0+eye2[2]*50.0),
                     height*(100.0+eye2[2]*50.0),
                     front, back);
    }
}
