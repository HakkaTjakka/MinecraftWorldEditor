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
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>
#include <glm/common.hpp>
#include <iostream>
#include <fcntl.h>
#include <bits/stdc++.h>

#include <geo_thread.hpp>
//#include <glm/gtx/transform.hpp>
//#include <glm/gtx/euler_angles.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//#include <glm/gtx/quaternion.hpp>
//#include <glm/gtc/quaternion.hpp>
//#include <glm/gtx/rotate_vector.hpp>



using namespace std;


extern int replace_str(char *str, char *orig, char *rep);
extern int monitor_off;
extern bool signal2_geo;
extern bool file_exists(const char * filename);
extern std::string area;
extern bool get_area_quick;
extern bool repair_by_list;

int GEO_STOP=0;
int GEO_RUNNING=0;

double pass_geo_xxx;
double pass_geo_yyy;

std::map<long long int, struct geo_region_struct> click_regions;
struct geo_region_struct one_click_regions;

bool fuck_you=false;

void calc_octants(struct geo_region_struct& one_click_region) {
    double lat_min, lat_max, lon_min, lon_max;
    lat_min = lon_min = std::numeric_limits<double>::max();
    lat_max = lon_max = -std::numeric_limits<double>::max();

    double lat,lon;
    for (int n=0; n<4; n++) {
        lat_min=std::min( one_click_region.geo_corners[n].z, lat_min );
        lon_min=std::min( one_click_region.geo_corners[n].x, lon_min );

        lat_max=std::max( one_click_region.geo_corners[n].z, lat_max );
        lon_max=std::max( one_click_region.geo_corners[n].x, lon_max );
    }

    if (area=="") area="Holland";

    glm::ivec2 one_get_lat_lon_top_left;
    glm::ivec2 one_get_lat_lon_bot_right;
    one_get_lat_lon_top_left = GET_LAT_LON4(area,lat_max,lon_min);
    one_get_lat_lon_bot_right = GET_LAT_LON4(area,lat_min,lon_max);

    printf("area=%s\ntop_left=%d,%d\n",area.c_str(),one_get_lat_lon_top_left.x,one_get_lat_lon_top_left.y);
    printf("bot_right=%d,%d\n",one_get_lat_lon_bot_right.x,one_get_lat_lon_bot_right.y);

    if ( (one_get_lat_lon_bot_right.x==9999 && one_get_lat_lon_bot_right.y==9999) || (one_get_lat_lon_top_left.x==9999 && one_get_lat_lon_top_left.y==9999) ) {
        printf("index(es) not found\n");
//        signal2_geo=false;
        return;
    }

    if (one_get_lat_lon_top_left.x>one_get_lat_lon_bot_right.x) {
        int swap=one_get_lat_lon_top_left.x;
        one_get_lat_lon_top_left.x=one_get_lat_lon_bot_right.x;
        one_get_lat_lon_bot_right.x=swap;
    }
    if (one_get_lat_lon_top_left.y>one_get_lat_lon_bot_right.y) {
        int swap=one_get_lat_lon_top_left.y;
        one_get_lat_lon_top_left.y=one_get_lat_lon_bot_right.y;
        one_get_lat_lon_bot_right.y=swap;
    }

//    get_area_quick=true;
    std::string octant;
    char s[1000];
    bool fail=false;

    FILE* f=fopen("OBJECT_ARRAY.NBT","w");
    for (int y=one_get_lat_lon_top_left.y; y<=one_get_lat_lon_bot_right.y; y++) {
        for (int x=one_get_lat_lon_top_left.x; x<=one_get_lat_lon_bot_right.x; x++) {
            get_area_quick=true;
            octant=get_area_data(area,x,y);
            get_area_quick=false;
            printf("X=%d Y=%d %s",x,y,octant.c_str());

            sprintf(s,"../cut/done/%s.dat",octant.c_str());
            if (file_exists(s)) printf(" File %s.dat does exist",octant.c_str());
            else printf(" File %s.dat does not exsist",octant.c_str());

            fprintf(f, "X=%d Y=%d %s\n",x,y,octant.c_str());

            printf(" File %s.nbt ",octant.c_str());
            octant=get_area_data(area,x,y);
            if (octant=="") {
                printf("does not exist.\n",octant.c_str());
                fail=true;
            }
            else printf(" exists.\n");

        }
    }
    fclose(f);
    if (repair_by_list && fail) {
        printf("Not all octants present\n");
//        printf("Not all octants present, aborting repair\n");
//        return;
    }
//    get_area_quick=false;
    sprintf(s,"../cut/r.%d.%d.png",one_click_region.region.x,one_click_region.region.z);
extern sf::Texture texture_from_ffmpeg;
extern int ffmpegfile;
    bool png=true;
    if (file_exists(s)) {
        printf("File %s does exist\n",s);
//        texture_from_ffmpeg.loadFromFile(s);
        scan_image.loadFromFile(s);
        scan_x=one_click_region.region.x;
        scan_z=one_click_region.region.z;
        update_request=2;
        while (update_request) {
            sf::sleep(sf::seconds(0.005));
        }
        ready_regions.clear();
//        ffmpegfile=0;
//        ffmpeg_move=0;
    } else {
        png=false;
        printf("File %s does not exists\n",s);
//        ffmpegfile=1;
    }

    if (!repair_mca) {
        for (region_floor=-2; region_floor<3; region_floor++) {
            sprintf(s,"/saves/test/region/done%d/r.%d.%d.mca",region_floor,one_click_region.region.x,one_click_region.region.z);
            if (file_exists(s)) {
                printf("File %s does exist\n",s);
                printf("Region(%d,%d) floor(%d)\n",one_click_region.region.x,one_click_region.region.z,region_floor);

                ffmpegfile=1;
                crossing=2; mirror=4;
                cubic=true;

    //            std::memset(region_block, 0x0, 512*256*512*4);
                plotting=1;
                MCEDITOR_running=1;
                silence=false;
                flushing_mode=true;
                burn=true;

                scan_image.create(512,512,sf::Color(255,128,0,128));
                scan_x=one_click_region.region.x;
                scan_z=one_click_region.region.z;
                update_request=2;
                while (update_request) {
                    sf::sleep(sf::seconds(0.005));
                }

                fuck_you=true;
                main_mceditor6_fixed(one_click_region.region.x,one_click_region.region.z, region_block);
                fuck_you=false;

                update_request=2;
                while (update_request) {
                    sf::sleep(sf::seconds(0.005));
                }

                silence=true;
                MCEDITOR_running=0;
                plotting=0;
            }
        }
    }
    ready_regions.clear();
    if (repair_mca) {
        printf("Voxelizing octants\n",s);

        for (region_floor=-2; region_floor<3; region_floor++) {
            sprintf(s,"/saves/test/region/done%d/r.%d.%d.mca",region_floor,one_click_region.region.x,one_click_region.region.z);
            if (file_exists(s)) {
                printf("Deleting %s\n",s);
                remove(s);
            }
        }

//        if (png) {
//           sprintf(s,"../cut/r.%d.%d.png",one_click_region.region.x,one_click_region.region.z);
//           printf("Deleting %s\n",s);
//           remove(s);
//        }
//        sprintf(s,"../cut.backup/r.%d.%d.png",one_click_region.region.x,one_click_region.region.z);
//        if (file_exists(s)) {
//            printf("Deleting %s\n",s);
//            remove(s);
//        }

        MAKE_NBT=true;
        MAKE_NBT_EXTERN=true;
        flushing_mode=true;
        do_nbt_fast=true;
        crossing=2;
        mirror=4;
        burn=true;
//        combine=1;
        cubic=true;
        do_wuppie=true;
        ffmpegfile=1;
//        plot_only=true;
        nbt_fast();
    }
}

void GEO_FUNC_PIPE(struct geo_region_struct& one_click_region) {
//    double xxx=pass_geo_xxx;
//    double yyy=pass_geo_yyy;
//    printf("Pipe thread called: %f %f\n",xxx,yyy);
//    sf::sleep(sf::seconds(5));
    unsigned char frame[1000]; //??? *4 for 4k
    char commandline[100];

    _setmode( _fileno( stdout ), _O_BINARY );   //cuckoo's

    static FILE* pfile=NULL;
    if (pfile==NULL) {
        pfile=popen("to_geo.exe","wb");
//        pfile=popen("python to_geo.py","wb");
        if (pfile==NULL) {
            printf("Cannot open pipe to python to_geo.exe\n");
//            signal2_geo=false;
            return;
        }
    }

    sprintf((char*)frame,"%f %f\r\n",   one_click_region.coords.x,    one_click_region.coords.z  );
    fwrite(frame, strlen((char*)frame), 1, pfile);
    if (repair_mca) {
        for (int n=0; n<4; n++) {
            sprintf((char*)frame,"%d %d\r\n",   one_click_region.region.x+n%2,    one_click_region.region.z+int(n/2)  );
            fwrite(frame, strlen((char*)frame), 1, pfile);
        }
    }
//    sprintf((char*)frame,"%d %d\r\n",   one_click_region.region.x+1,  one_click_region.region.z  ); fwrite(frame, strlen((char*)frame), 1, pfile);
//    sprintf((char*)frame,"%d %d\r\n",   one_click_region.region.x,    one_click_region.region.z+1); fwrite(frame, strlen((char*)frame), 1, pfile);
//    sprintf((char*)frame,"%d %d\r\n",   one_click_region.region.x+1,  one_click_region.region.z+1); fwrite(frame, strlen((char*)frame), 1, pfile);

    sprintf((char*)frame,"ready dummy\r\n");
    fwrite(frame, strlen((char*)frame), 1, pfile);

    fflush(pfile);

    while (!file_exists("geo_ready.txt")) {
        sf::sleep(sf::seconds(0.1));
    }
    sf::sleep(sf::seconds(0.1));

    FILE* HOP;
    char lat_str[100];
    char lon_str[100];
    char line[1000];
    double lon,lat;
    bool ok=false;
    char command_str[1000];
    if ((HOP = fopen ("result.txt", "r"))!=NULL) {
        if (fgets (line,1000, HOP)!=NULL) {
            if ( sscanf(line,"%lf %lf",&lon,&lat) != 2) {
                printf("ERROR READING COORDS from result.txt.txt\n");
                printf("line 1 =\"%s\"\n",line);
            } else {
                printf("CLICKED: LAT=%20.16f LON=%20.16f [%f,%f]\n",
                       lat, lon,
                       one_click_region.coords.x,
                       one_click_region.coords.z
                );
                one_click_region.geo_click=dvec2(lat,lon);

                sprintf(lat_str,"%lf",lat); while (replace_str(lat_str,",","."));
                sprintf(lon_str,"%lf",lon); while (replace_str(lon_str,",","."));
//                printf(" https://www.google.com/maps/@%s,%s,17.00z\n",lat_str,lon_str);

                FILE* f=fopen("call_chrome.bat","w");
//                sprintf(command_str,"\"C:\\Program Files\\Google\\Chrome\\Application\\chrome.exe\" \"https://www.google.com/maps/@%s,%s,18.00z\">nul 2>nul",lat_str,lon_str);
                sprintf(command_str,"@echo off\n\"C:\\Program Files\\Google\\Chrome\\Application\\chrome.exe\" \"https://www.google.com/maps/@%s,%s,553m/data=!3m1!1e3\">nul 2>nul",lat_str,lon_str);
                fprintf(f,command_str);
                fclose(f);
                ok=true;
                if (repair_mca) {
                    for (int n=0; n<4; n++) {
                        if (fgets (line,1000, HOP)!=NULL) {
                            if ( sscanf(line,"%lf %lf",&lon,&lat) != 2) {
                                printf("ERROR READING CORNER from projection.txt\n");
                                printf("line %d =\"%s\"\n",n,line);
                            } else {
                                printf("CORNER:  LAT=%20.16f LON=%20.16f r.%d.%d.mca\n",
                                        lat, lon,
                                        one_click_region.region.x+n%2,
                                        one_click_region.region.z+(int(n/2))
                                );
                                one_click_region.geo_corners[n]=dvec2(lon,lat);
                            }
                        } else {
                            printf("ERROR READING LAT LON FROM TO_GEO.TXT\n");
                            printf("line=%s\n",line);
                            break;
                        }
                    }
                }
            }
        } else {
            printf("ERROR READING LAT LON FROM TO_GEO.TXT\n");
            printf("line=%s\n",line);
        }
        fclose(HOP);
        if (ok && repair_mca) {
            calc_octants(one_click_region);


//            sprintf(command_str,"call_chrome.bat &");
//            system(command_str);
        }
    }
}

//sf::Thread* GEO_PIPE=NULL;
//sf::Thread GEO_PIPE=new sf::Thread(&GEO_FUNC_PIPE2, one_click_region);

//void GEO_FUNC_PIPE2(struct geo_region_struct& one_click_region) {
struct geo_region_struct one_click_region_pass;

void VOXEL_TO_REGION(struct geo_region_struct& one_click_region) {
    char voxel_filename[1000];
    sprintf(voxel_filename,"r.%d.%d.vox",one_click_region.region.x,one_click_region.region.z);
    scan_image.create(512,512,sf::Color(0,0,0,0));

    scan_x=one_click_regions.region.x;
    scan_z=one_click_regions.region.z;
    silence=true;
    update_request=2;
    while (update_request) sf::sleep(sf::seconds(0.1));
    silence=false;
    one_region_voxel_files_to_region_files(false, voxel_filename);
}

void GEO_FUNC_PIPE2() {
    if (make_regions) {
        VOXEL_TO_REGION(one_click_region_pass);
    } else {
        GEO_FUNC_PIPE(one_click_region_pass);
    }
    GEO_RUNNING=0;
    GEO_STOP=1;
    printf("Leaving geo pipe thread\n");
    signal2_geo=false;
}

//sf::Thread GEO_PIPE=sf::Thread(&GEO_FUNC_PIPE2, one_click_region_pass);

sf::Thread GEO_PIPE(&GEO_FUNC_PIPE2);

void SEND_TO_GEO_PIPE(struct geo_region_struct& one_click_region)
{
    int n=0;
    while (GEO_RUNNING==1)
    {
        if (n++==5) { printf("GEO_RUNNING\n"); n=0; }
        sf::sleep(sf::seconds(0.1));
    }
    GEO_RUNNING=1;
    GEO_STOP=0;

    if (file_exists("geo_ready.txt")) {
        remove("geo_ready.txt");
    }

//    static sf::Thread GEO_PIPE(&GEO_FUNC_PIPE2, one_click_region) ;
//    if (GEO_PIPE!=NULL) delete GEO_PIPE;
//     GEO_PIPE=new sf::Thread(&GEO_FUNC_PIPE2, one_click_region);

//    sf::Thread GEO_PIPE=sf::Thread(&GEO_FUNC_PIPE2, one_click_region);
//    m_thread=sf::Thread(&GEO_FUNC_PIPE2, one_click_region) ;


//    GEO_PIPE.launch();
    one_click_region_pass=one_click_region;
   GEO_PIPE.launch();
}

















void GEO_FUNC() {
    double xxx=pass_geo_xxx;
    double yyy=pass_geo_yyy;
    printf("Thread called: %f %f\n",xxx,yyy);
    sf::sleep(sf::seconds(5));

    monitor_off=1;
    char sys_call[200];
    sprintf(sys_call,"python to_geo.py %f %f", xxx,yyy);
    printf("Calling Python: %s\n",sys_call);
    system(sys_call);

    FILE* HOP;
    char lat_str[100];
    char lon_str[100];
    char line[1000];
    double lon,lat;
    bool ok=false;
    char command_str[1000];
    if ((HOP = fopen ("result.txt", "r"))!=NULL) {
        if (fgets (line,1000, HOP)!=NULL) {
            if ( sscanf(line,"%lf %lf",&lon,&lat) != 2) {
                printf("ERROR READING TOP_LEFT from projection.txt\n");
                printf("line=%s\n",line);
            } else {
                printf("LAT=%20.16f LON=%20.16f\n",lat,lon);
                sprintf(lat_str,"%lf",lat); while (replace_str(lat_str,",","."));
                sprintf(lon_str,"%lf",lon); while (replace_str(lon_str,",","."));
                printf(" https://www.google.com/maps/@%s,%s,17.00z\n",lat_str,lon_str);
                FILE* f=fopen("call_chrome.bat","w");
//                sprintf(command_str,"\"C:\\Program Files\\Google\\Chrome\\Application\\chrome.exe\" \"https://www.google.com/maps/@%s,%s,18.00z\">nul 2>nul",lat_str,lon_str);
                sprintf(command_str,"\"C:\\Program Files\\Google\\Chrome\\Application\\chrome.exe\" \"https://www.google.com/maps/@%s,%s,553m/data=!3m1!1e3\">nul 2>nul",lat_str,lon_str);
                fprintf(f,command_str);
                fclose(f);
                ok=true;
//                sprintf(command_str,"\"\"C:\\Program Files\\Google\\Chrome\\Application\\chrome.exe\" \"https://www.google.com/maps/@%s,%s,18.00z\"\"",lat_str,lon_str);
//                printf(command_str); printf("\n");
                // >nul 2>nul
//                system(command_str);
            }
        } else {
            printf("ERROR READING LAT LON FROM TO_GEO.TXT\n");
            printf("line=%s\n",line);
        }
        fclose(HOP);
        if (ok) {
            sprintf(command_str,"call_chrome.bat &");
            system(command_str);
        }
    }
}


void GEO_FUNC2() {
    GEO_FUNC();
    GEO_RUNNING=0;
    GEO_STOP=1;
    printf("Leaving geo thread\n");
    signal2_geo=false;
  }

sf::Thread GEO(&GEO_FUNC2);

void LAUNCH_GEO_THREAD(double xxx, double yyy)
{
    if (GEO_RUNNING==1)
    {
        printf("\ngeo thread already running sukkel\n");
        return;
    }
    pass_geo_xxx=xxx;
    pass_geo_yyy=yyy;
    GEO_RUNNING=1;
    GEO_STOP=0;
    GEO.launch();
}


/*


// This pair is used to store the X and Y
// coordinates of a point respectively
#define pdd pair<double, double>

// Function used to display X and Y coordinates
// of a point
void displayPoint(pdd P)
{
    cout << "(" << P.first << ", " << P.second
         << ")" << endl;
}

pdd lineLineIntersection(pdd A, pdd B, pdd C, pdd D)
{
    // Line AB represented as a1x + b1y = c1
    double a1 = B.second - A.second;
    double b1 = A.first - B.first;
    double c1 = a1*(A.first) + b1*(A.second);

    // Line CD represented as a2x + b2y = c2
    double a2 = D.second - C.second;
    double b2 = C.first - D.first;
    double c2 = a2*(C.first)+ b2*(C.second);

    double determinant = a1*b2 - a2*b1;

    if (determinant == 0)
    {
        // The lines are parallel. This is simplified
        // by returning a pair of FLT_MAX
        return make_pair(FLT_MAX, FLT_MAX);
    }
    else
    {
        double x = (b2*c1 - b1*c2)/determinant;
        double y = (a1*c2 - a2*c1)/determinant;
        return make_pair(x, y);
    }
}

// Driver code
int main2()
{
    pdd A = make_pair(1, 1);
    pdd B = make_pair(4, 4);
    pdd C = make_pair(1, 8);
    pdd D = make_pair(2, 4);

    pdd intersection = lineLineIntersection(A, B, C, D);

    if (intersection.first == FLT_MAX &&
        intersection.second==FLT_MAX)
    {
        cout << "The given lines AB and CD are parallel.\n";
    }

    else
    {
        // NOTE: Further check can be applied in case
        // of line segments. Here, we have considered AB
        // and CD as lines
        cout << "The intersection of the given lines AB "
                "and CD is: ";
        displayPoint(intersection);
    }

    return 0;
}


*/
