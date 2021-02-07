#define PI 3.141592653589793
#define PI 3.141592653589793
#define SFML_STATIC
#undef UNICODE
#include <winsock2.h>
#include <io.h>
#include "WinMain.h"
#include <psapi.h>
#include <stdio.h>
#include <conio.h>
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
#include <SFML/System.hpp>
extern int mazemovex_voxel;
extern int mazemovey_voxel;

extern float voxel_bottom;
extern float g_move_object_x;
extern float g_move_object_y;
extern float g_move_object_z;
extern float g_rotate_object_x;
extern float g_rotate_object_y;
extern float g_rotate_object_z;
extern double schematic_size;
extern double eye22;
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
extern int position1x;
extern int position1y;
extern void get_position3();
extern float rotate_object_x_base;
extern float rotate_object_y_base;
extern float rotate_object_z_base;
extern float rotate_object_z_to_add;
extern float rotate_object_y_to_add;
extern float rotate_object_x_to_add;
extern float rotate_object_x_cum;
extern float rotate_object_y_cum;
extern float rotate_object_z_cum;

extern float fps_base;
extern float angle_base;
extern float speed_base;
extern double smooth_x_old;
extern double smooth_y_old;

bool play(int& play_num, float bmin[3], float bmax[3]) {
    static float flipje;
    static int flipflop=0;
    static double smooth_x_start;
    static double smooth_y_start;
    static float speed_angle;
    static float speed_angle1;
    static float speed_angle2;
    static float bmax_loc[3], bmin_loc[3];
    static double schematic_size_o;
    static float voxel_bottom_o;
    static float distance;
    static float f;
    static float MID[3];
    static float prev_angle=0.0;
    static int loop=0;
    static float speed_angle1_add;
    static float speed_angle2_add;
    static float radius;
    static float radius1;
    static float radius2;
    static int second_loop=0;
    if (play_num==-1) {
        play_num=0;
        loop=0;
        smooth_x_start=(int)smooth_x;
        smooth_y_start=(int)smooth_y;
        second_loop=0;
        return true;
    }
    if (play_num==0 && loop==0) { //start
        distance=150.0;
        flipflop=1;
        angle_base=0.0;
        speed_angle=0.0;
        speed_angle1=0.0;
        speed_angle2=0.0;
        bmax_loc[0]=0; bmax_loc[1]=0; bmax_loc[2]=0;
        bmin_loc[0]=0; bmin_loc[1]=0; bmin_loc[2]=0;
        schematic_size_o=6000.0/(eye22*10.0);
        f=1.0;
        radius=6500.0-second_loop*600;
        radius1=radius+distance;
        radius2=radius-distance;
        voxel_bottom_o=0.0;
    }

    float offset_x=0.0;
    float offset_y=0.0;

    if (play_num==1) {
        for (int n=0;  n<3; n++) {
            bmax_loc[n]=bmax[n];
            bmin_loc[n]=bmin[n];
            MID[n]=(bmax[n]-bmin[n])/2.0;
        }
        speed_angle1_add=(bmax_loc[2]-bmin_loc[2])/(radius1);
        float num=roundf(2.0*M_PI/speed_angle1_add);
        speed_angle1_add=(2.0*M_PI)/num;

        speed_angle2_add=(bmax_loc[2]-bmin_loc[2])/(radius2);
        num=roundf(2.0*M_PI/speed_angle2_add);
        speed_angle2_add=(2.0*M_PI)/num;

        printf("Start size: %d %d %d\n", (int)bmax_loc[0]-(int)bmin_loc[0], (int)bmax_loc[1]-(int)bmin_loc[1], (int)bmax_loc[2]-(int)bmin_loc[2]  );
    }

    schematic_size=schematic_size_o+float(rand()%41-20)/(1.0+(float)loop/2.0);
    voxel_bottom=voxel_bottom_o+float(rand()%41-20)/(1.0+(float)loop/2.0);
    if (voxel_bottom<0.0) voxel_bottom-=voxel_bottom;
    if (schematic_size<30.0) schematic_size=30.0;

    if (play_num>0) {
        if (speed_angle1<speed_angle2) {
            speed_angle=speed_angle1;
            flipflop=1;
            speed_angle1+=speed_angle1_add;
        } else {
            speed_angle=speed_angle2;
            flipflop=2;
            speed_angle2+=speed_angle2_add;
        }
    }

    offset_x=cos(speed_angle)*(radius);
    offset_y=sin(speed_angle)*(radius);
    int mazemovex=0;
    int mazemovey=0;

    if (flipflop==1) {
        mazemovey=(distance+float(rand()%41-20)/(1.0+(float)loop/2.0))*sin(speed_angle);
        mazemovex=(distance+float(rand()%41-20)/(1.0+(float)loop/2.0))*cos(speed_angle);
    } else {
        mazemovey=-(distance+float(rand()%41-20)/(1.0+(float)loop/2.0))*sin(speed_angle);
        mazemovex=-(distance+float(rand()%41-20)/(1.0+(float)loop/2.0))*cos(speed_angle);
    }

    position1x=smooth_x_start+offset_x;
    position1y=smooth_y_start+offset_y;

extern int update_request;

    update_request=4;
    while (update_request) {
        sf::sleep(sf::seconds(0.005));
    }
    sf::sleep(sf::seconds(0.1));
//    get_position3();

    mazemovex_voxel=smooth_x+mazemovex-(bmax[1]-bmin[1])/2.0;
    mazemovey_voxel=smooth_y+mazemovey-(bmax[2]-bmin[2])/2.0;

    printf("NUM: %d: Radius#=%d Bottom=%d  Angle=%5.1f  Distance=%d  Width=%d(%d)  Height=%d(%d)  Depth=%d(%d)  size=%d\n",
           play_num, flipflop, (int)voxel_bottom, speed_angle*180.0/M_PI,(int)distance,
           (int)bmax[2]-(int)bmin[2], (int)bmax_loc[2]-(int)bmin_loc[2],
           (int)bmax[0]-(int)bmin[0], (int)bmax_loc[0]-(int)bmin_loc[0],
           (int)bmax[1]-(int)bmin[1], (int)bmax_loc[1]-(int)bmin_loc[1],
           (int)schematic_size  );

    if (flipflop==1) {
        g_rotate_object_x=(speed_angle)*180.0/M_PI+90.0+float(rand()%61-30);
    } else {
        g_rotate_object_x=(speed_angle)*180.0/M_PI-90.0+float(rand()%61-30);
    }

    g_rotate_object_y=float(rand()%61-30);
    g_rotate_object_z=float(rand()%61-30);


    if (speed_angle>2.0*M_PI && loop==0) {
        play_num=0; // msg next loop
        if (loop==0) loop=1;
        distance=200;
        radius1=radius+distance;
        radius2=radius-distance;
        voxel_bottom_o=schematic_size_o*0.3;
        schematic_size_o=schematic_size_o*0.8;
        speed_angle1=2.0*M_PI;
        speed_angle2=2.0*M_PI;
        speed_angle=2.0*M_PI;
    } else if (speed_angle>4.0*M_PI && loop==1) {
        play_num=0; // msg next loop
        if (loop==1) loop=2;
        distance=230;
        radius1=radius+distance;
        radius2=radius-distance;
        voxel_bottom_o=voxel_bottom_o+schematic_size_o*0.3;
        schematic_size_o=schematic_size_o*0.8;
        speed_angle1=4.0*M_PI;
        speed_angle2=4.0*M_PI;
        speed_angle=4.0*M_PI;
    } else if (speed_angle>6.0*M_PI && loop==2) {
        play_num=0; // msg next loop
        if (loop==2) loop=3;
        distance=250;
        radius1=radius+distance;
        radius2=radius-distance;
        voxel_bottom_o=voxel_bottom_o+schematic_size_o*0.3;
        schematic_size_o=schematic_size_o*0.8;
        speed_angle1=6.0*M_PI;
        speed_angle2=6.0*M_PI;
        speed_angle=6.0*M_PI;
    } else if (speed_angle>8.0*M_PI && loop==3) {
        if (second_loop==0) {
            loop=0;
            play_num=0;
            second_loop=1;
        } else if (second_loop==1) {
            loop=0;
            play_num=0;
            second_loop=2;
        } else if (second_loop==2) {
            loop=0;
            play_num=0;
            second_loop=3;
        } else if (second_loop==3) {
            loop=0;
            play_num=0;
            second_loop=4;
        } else if (second_loop==4) {
            loop=0;
            play_num=0;
            second_loop=5;
        } else if (second_loop==5) {
            loop=0;
            play_num=0;
            second_loop=6;
        } else if (second_loop==6) {
            loop=0;
            play_num=0;
            second_loop=7;
        } else if (second_loop==7) {
            loop=0;
            play_num=0;
            second_loop=8;
        } else if (second_loop==8) {
            loop=0;
            play_num=0;
            second_loop=9;
        } else if (second_loop==9) {
            loop=0;
            play_num=0;
            second_loop=10;
        } else if (second_loop==10) {
            return false;
        }
    } else {
        play_num++;
    }
    prev_angle=speed_angle;

//    if (speed_angle>8.0*M_PI) {
//        return false;
//    }
    return true;
}


bool play_backup(int& play_num, float bmin[3], float bmax[3]) {
    static float flipje;
    static int flipflop=0;
    static double smooth_x_start;
    static double smooth_y_start;
    static float speed_angle;
    static float speed_angle1;
    static float speed_angle2;
    static float bmax_loc[3], bmin_loc[3];
    static double schematic_size_o;
    static float voxel_bottom_o;
    static float distance;
    static float f;
    static float MID[3];
    static float prev_angle=0.0;
    static int loop=0;
    static float speed_angle1_add;
    static float speed_angle2_add;
    static float radius;
    static float radius1;
    static float radius2;

    if (play_num==-1) {
        play_num=0;
        loop=0;
        return true;
    }
    if (play_num==0 && loop==0) { //start
        distance=200.0;
        flipflop=1;
        smooth_x_start=(int)smooth_x;
        smooth_y_start=(int)smooth_y;
        angle_base=0.0;
        speed_angle=0.0;
        speed_angle1=0.0;
        speed_angle2=0.0;
        bmax_loc[0]=0; bmax_loc[1]=0; bmax_loc[2]=0;
        bmin_loc[0]=0; bmin_loc[1]=0; bmin_loc[2]=0;
        schematic_size_o=6000.0/(eye22*10.0);
        f=1.0;
        radius=500.0;
        radius1=radius+distance;
        radius2=radius-distance;
        voxel_bottom_o=0.0;
    }

    float offset_x=0.0;
    float offset_y=0.0;

    if (play_num==1) {
        for (int n=0;  n<3; n++) {
            bmax_loc[n]=bmax[n];
            bmin_loc[n]=bmin[n];
            MID[n]=(bmax[n]-bmin[n])/2.0;
        }
        speed_angle1_add=(bmax_loc[2]-bmin_loc[2])/(radius1);
        float num=roundf(2.0*M_PI/speed_angle1_add);
        speed_angle1_add=(2.0*M_PI)/num;

        speed_angle2_add=(bmax_loc[2]-bmin_loc[2])/(radius2);
        num=roundf(2.0*M_PI/speed_angle2_add);
        speed_angle2_add=(2.0*M_PI)/num;

        printf("Start size: %d %d %d\n", (int)bmax_loc[0]-(int)bmin_loc[0], (int)bmax_loc[1]-(int)bmin_loc[1], (int)bmax_loc[2]-(int)bmin_loc[2]  );
    }

    schematic_size=schematic_size_o;
    voxel_bottom=voxel_bottom_o;

    if (play_num>0) {
        if (speed_angle1<speed_angle2) {
            speed_angle=speed_angle1;
            flipflop=1;
            speed_angle1+=speed_angle1_add;
        } else {
            speed_angle=speed_angle2;
            flipflop=2;
            speed_angle2+=speed_angle2_add;
        }
    }

    offset_x=cos(speed_angle)*(radius);
    offset_y=sin(speed_angle)*(radius);
    int mazemovex=0;
    int mazemovey=0;

    if (flipflop==1) {
        mazemovey=(distance)*sin(speed_angle);
        mazemovex=(distance)*cos(speed_angle);
    } else {
        mazemovey=-(distance)*sin(speed_angle);
        mazemovex=-(distance)*cos(speed_angle);
    }

    position1x=smooth_x_start+offset_x;
    position1y=smooth_y_start+offset_y;

    get_position3();

    mazemovex_voxel=smooth_x+mazemovex-(bmax[1]-bmin[1])/2.0;
    mazemovey_voxel=smooth_y+mazemovey-(bmax[2]-bmin[2])/2.0;

    printf("NUM: %d: Radius#=%d Bottom=%d  Angle=%5.1f  Distance=%d  Width=%d(%d)  Height=%d(%d)  Depth=%d(%d)  size=%d\n",
           play_num, flipflop, (int)voxel_bottom, speed_angle*180.0/M_PI,(int)distance,
           (int)bmax[2]-(int)bmin[2], (int)bmax_loc[2]-(int)bmin_loc[2],
           (int)bmax[0]-(int)bmin[0], (int)bmax_loc[0]-(int)bmin_loc[0],
           (int)bmax[1]-(int)bmin[1], (int)bmax_loc[1]-(int)bmin_loc[1],
           (int)schematic_size  );

    if (flipflop==1) {
        g_rotate_object_x=(speed_angle)*180.0/M_PI+90.0+rand()%5-2;
    } else {
        g_rotate_object_x=(speed_angle)*180.0/M_PI-90.0+rand()%5-2;
    }

    g_rotate_object_y=rand()%5-2;
    g_rotate_object_z=rand()%5-2;


    if (speed_angle>2.0*M_PI && loop==0) {
        play_num=0; // msg next loop
        if (loop==0) loop=1;
        distance=300;
        radius1=radius+distance;
        radius2=radius-distance;
        voxel_bottom_o=schematic_size_o*0.75;
        schematic_size_o=schematic_size_o*0.75;
        speed_angle1=2.0*M_PI;
        speed_angle2=2.0*M_PI;
        speed_angle=2.0*M_PI;
    } else {
        play_num++;
    }
    prev_angle=speed_angle;

    if (speed_angle>4.0*M_PI) {
        return false;
    }
    return true;
}
