//#include "../everything.hpp"
//#include "../everything.hpp"
//#include "../everything.hpp"

#include <windows.h>
#include <cstdio>
#include "globals.h"
#include <cstdio>
#include <vector>
#include <string>
#include <cstdlib>
#include <algorithm>
#include "MCEditor.h"
#include "BlockEntity.h"
#include "MCACoder.h"
#include <math.h>
#include <dirent.h>
#include <iostream>
using namespace std;
extern bool no_plotting;
extern int SEED;
#include <glm/glm.hpp>

//#include <queue>
//#include <utility>
//#include <set>
//#include <cstring>

//#include <SFML/Audio.hpp>
//#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
//#include <SFML/Graphics/Texture.hpp>
//#include <SFML/Graphics/RenderWindow.hpp>
//#include <SFML/System.hpp>
//#include <SFML/Network.hpp>
//#include <SFML/System/Mutex.hpp>
//#include <SFML/Network/IpAddress.hpp>

using namespace std;
vector<pair<Pos, string> > SomeStuff;
bool grass_on=true;
bool water_on=true;
bool blue_to_water_on=true;
bool glass_on=true;
bool massiv_on=false;
bool turbo_on=true;
bool boom_on=true;
bool caves_on=true;
bool rooms_on=true;
bool coral_on=true;
bool maze_on=true;
bool lights_on=true;
bool stone_on=true;
extern int replace_string(char *str, char *orig, char *rep);
extern void ret_color_rev(int idx, int&r,int&g,int&b );
void add_maze_to_region(MCRegion& region, int region_x, int region_z, int bottom, int extra_height, int type);

void print_chunk_list();
int reversed_chunk_list[32][32];
bool add_to_region=false;
int fast_build=0;
void hoppa(BlockInfo*** AX, int x, int z, int y);
using namespace std;
int remove_block_entities=1;
extern int mirror;
extern bool flushing;

int ceil_heigher=9;

void scan_done0_regionfiles(char* what);

int chunk_offsetx, chunk_offsetz;
extern string file_name_MCA;
//extern std::string current_filename_mca;
extern int first_MCEDIT;
int main_mceditor2();
int main_mceditor3();
int main_mceditor4();
//int main_mceditor5();
int main_mceditor5_from_file(char* dat_filename,char* voxel_filename);
int shut_up=0;
int chunk_list[1024][2];

int region_counter[1000][1000];

char mc_text1[100];
char mc_text2[100];

sf::Image scan_image;
int scan_x,scan_z;

sf::Color random_pixel;

int mcglobal=0;
int mcglobal2=0;
int mcglobal3=0;
int region_xxx,region_zzz;
extern bool file_exists(const char * filename);
int xx,zz;
int rails=0;
int rails_tot=0;
void setBlockWithCommand(MCRegion &R, int x, int z, int y, const string &cmd, const int &automatic);
void setRepeatingBlockWithCommand(MCRegion &R, int x, int z, int y, const string &cmd, const int &automatic);
void make_mirror(sf::Image* image);
char tmp[256] = {0};
extern void reset_block();
int MCEDITOR_stop=0;
void read_one_plot_WINMAIN(int x, int y, sf::Image* image);
using namespace std;
extern int plot_cubes;
extern sf::VertexArray m_pointCloud3;
extern sf::Color pixel_color;
extern char **used;
extern int **used2;
extern sf::RenderTexture *texturemaxinmempoint[];
sf::Image image_plot;
sf::Image image_plot_org;
sf::Image image_plot2;
sf::Image image_plot3;
sf::Image image_plot_extra;
int t_diff_MCEDITOR;
int trans_MCEDITOR;
extern int ret_color(int r, int g, int b);
extern int ret_Mos_color(int r, int g, int b);
extern int ret_Mos_color_rev(int idx);
extern float scale_factor;
sf::Mutex MUTEX_MCEDITOR;
extern string MCAFileNameXZ(int x, int z);
extern int jump_request;
extern int jump_x;
extern int jump_y;
MCEditor editor;
extern int** color_list_rgb;
int update_request=0;
extern int region_x_old,region_z_old;
extern void kiki();
int main_mceditor();
int MCEDITOR_running=0;
extern int mcmator_running;
extern char send_message;

int x00=0, y00=0, z00=0;
int xl=512, yl=256, zl=512;

//MCRegion region(x00, z00, y00, xl, zl, yl);

float fast_sin[4096];

#define PI 3.141592653589793

float get_fast_sin(float rot) {
    static float parm=4096.0/(2.0*PI);
    if (rot>=0)
        return fast_sin[(int)(rot*parm)&4095];
    else
        return -fast_sin[(int)(-rot*parm)&4095];
}

void fast_sin_init() {
    static bool first=true;
    if (first) {
        for (int n=0; n<4096; n++) {
            fast_sin[n]=sin(2.0*PI*((float)n/4096.0));
        }
        first=false;
    }
}

#define sin get_fast_sin

int toggle_2=0;
void toggle2() {
    toggle_2=(toggle_2+1); if (toggle_2>=5000) toggle_2=0;;
    if (toggle_2==0) printf("/\b");
    else if (toggle_2==1250) {
        static int t=0;
        t++;
        if (t>100) { printf("o-\b"); t=0; }
        else { printf("-\b"); }
    }
    else if (toggle_2==2500) printf("\\\b");
    else if (toggle_2==3750) printf("|\b");
}

int toggle_4=0;
void toggle4() {
    toggle_4=(toggle_4+1); if (toggle_4>=4) toggle_4=0;;
    if (toggle_4==0) printf("/\b");
    else if (toggle_4==1) {
        static int t=0;
        t++;
        if (t>20) { printf("o-\b"); t=0; }
        else { printf("-\b"); }
    }
    else if (toggle_4==2) printf("\\\b");
    else if (toggle_4==3) printf("|\b");
}

extern unsigned char *region_block;
int main_mceditor6_fixed(int region_x, int region_z, unsigned char* mc);

int toggle_3=0;
void toggle3() {
    static int toggle=0;
    if (toggle_3++>=10485760) toggle_3=0;
    if (toggle_3==0) printf("/\b");
    else if (toggle_3==2621440) printf("o-\b");
    else if (toggle_3==5242880) printf("\\\b");
    else if (toggle_3==7864320) printf("|\b");
}

char raw_file[200];
char dat_file[200];

int main_mceditor() {
    fast_sin_init();
    sf::sleep(sf::seconds(2.0));
    if (mcglobal==1 || mcglobal==2) {
        if (mcglobal==2) print_chunk_list();
        main_mceditor3();
    }
    else if (mcglobal==3) {
        print_chunk_list();
        mcglobal=2;
        main_mceditor3();
    }
    else if (mcglobal==4) {
        main_mceditor4();
    }
    else if (mcglobal==5) {
        main_mceditor5_from_file("../cut/voxel.dat","../cut/voxel.raw");
    }
    else if (mcglobal==6 || mcglobal==7) {
        if (mcglobal2==0) scan_done0_regionfiles("/saves/test/region/done0");
        else if (mcglobal2==1) scan_done0_regionfiles("/saves/test/region/done1");
        else if (mcglobal2==2) scan_done0_regionfiles("/saves/test/region/done2");
    }
    else if (mcglobal==10) {
        main_mceditor6_fixed(mcglobal, mcglobal2, region_block);
    }
    else
        main_mceditor2();
//    main_mceditor3();
}


void MCEDITOR_THREAD() {
    printf("MCEDITOR thread starting\n");
    main_mceditor();
    printf("MCEDITOR thread stopped\n");
    MCEDITOR_stop=0;
    MCEDITOR_running=0;
}

sf::Thread MCEDITOR(&MCEDITOR_THREAD);

void launch_MCEDITOR() {
    if (MCEDITOR_running==1) {
        printf("MC already running\n");
        return;
    }
    MCEDITOR_running=1;
    MCEDITOR.launch();
}

void terminate_MCEDITOR() {
    MCEDITOR.terminate();
}

string cmdFillWithTnt()
{
    char tntstr[]="tnt";
//    char tntstr[]="minecraft:tnt"; //doesn't work on bedrock :(
//    char tntstr[]="minecraft:tnt[unstable=true]";
    int what=rand()%1;
    if (what<6)
        sprintf(tmp, "/setblock ~ ~ ~ %s",tntstr);
    else if (what==6)
        sprintf(tmp, "/setblock ~10 ~ ~10 %s",tntstr);
    else if (what==7)
        sprintf(tmp, "/setblock ~-10 ~ ~10 %s",tntstr);
    else if (what==8)
        sprintf(tmp, "/setblock ~-10 ~ ~-10 %s",tntstr);
    else if (what==9)
        sprintf(tmp, "/setblock ~10 ~ ~-10 %s",tntstr);


    string res = tmp;
    return res;
}

string cmdSetBlock(int x, int y, int z, std::string block_string) {
    sprintf(tmp, "/setblock %d %d %d %s",x,y,z,block_string.c_str());
    string res = tmp;
    return res;
}

string cmdSetKelp()
{
    sprintf(tmp, "/setblock ~ ~ ~ kelp");
    string res = tmp;
    return res;
}

string cmdSummonRabbits()
{
    int what=rand()%4;
    if (what==0)
        sprintf(tmp, "/summon minecraft:rabbit ~1 ~2 ~1");
    else if (what==1)
        sprintf(tmp, "/summon minecraft:rabbit ~-1 ~2 ~1");
    else if (what==2)
        sprintf(tmp, "/summon minecraft:rabbit ~-1 ~2 ~-1");
    else if (what==3)
        sprintf(tmp, "/summon minecraft:rabbit ~1 ~2 ~-1");
    else if (what==4)
        sprintf(tmp, "/summon minecraft:rabbit ~ ~2 ~");

    string res = tmp;
    return res;
}

string cmdSummonWolf()
{
    int what=rand()%4;
    if (what==0)
        sprintf(tmp, "/summon minecraft:wolf ~1 ~2 ~1");
    else if (what==1)
        sprintf(tmp, "/summon minecraft:wolf ~-1 ~2 ~1");
    else if (what==2)
        sprintf(tmp, "/summon minecraft:wolf ~-1 ~2 ~-1");
    else if (what==3)
        sprintf(tmp, "/summon minecraft:wolf ~1 ~2 ~-1");

    string res = tmp;
    return res;
}

char ents[][50]={
//    "minecraft:area_effect_cloud",
    "minecraft:armor_stand",
    "minecraft:arrow",
    "minecraft:bat",
    "minecraft:blaze",
//    "minecraft:boat",
    "minecraft:cat",
    "minecraft:cave_spider",
//    "minecraft:chest_minecart",
    "minecraft:chicken",
    "minecraft:cod",
//    "minecraft:command_block_minecart",
    "minecraft:cow",
    "minecraft:creeper",
    "minecraft:dolphin",
    "minecraft:donkey",
//    "minecraft:dragon_fireball",
    "minecraft:drowned",
    "minecraft:egg",
    "minecraft:elder_guardian",
//    "minecraft:end_crystal",
//    "minecraft:ender_dragon",
    "minecraft:ender_pearl",
    "minecraft:enderman",
    "minecraft:endermite",
    "minecraft:evoker",
    "minecraft:evoker_fangs",
//    "minecraft:experience_bottle",
//    "minecraft:experience_orb",
    "minecraft:eye_of_ender",
//    "minecraft:falling_block",
    "minecraft:fireball",
    "minecraft:firework_rocket",
    "minecraft:fox",
//    "minecraft:furnace_minecart",
    "minecraft:ghast",
    "minecraft:giant",
    "minecraft:guardian",
//    "minecraft:hopper_minecart",
    "minecraft:horse",
    "minecraft:husk",
    "minecraft:illusioner",
    "minecraft:iron_golem",
    "minecraft:item",
    "minecraft:item_frame",
    "minecraft:leash_knot",
//    "minecraft:lightning_bolt",
    "minecraft:llama",
//    "minecraft:llama_spit",
//    "minecraft:magma_cube",
//    "minecraft:minecart",
    "minecraft:mooshroom",
    "minecraft:mule",
    "minecraft:ocelot",
//    "minecraft:painting",
    "minecraft:panda",
    "minecraft:parrot",
    "minecraft:phantom",
    "minecraft:pig",
    "minecraft:pillager",
    "minecraft:polar_bear",
    "minecraft:potion",
//    "minecraft:pufferfish",
    "minecraft:rabbit",
    "minecraft:ravager",
    "minecraft:salmon",
    "minecraft:sheep",
    "minecraft:shulker",
    "minecraft:shulker_bullet",
    "minecraft:silverfish",
    "minecraft:skeleton",
    "minecraft:skeleton_horse",
    "minecraft:slime",
//    "minecraft:small_fireball",
    "minecraft:snow_golem",
    "minecraft:snowball",
//    "minecraft:spawner_minecart",
//    "minecraft:spectral_arrow",
    "minecraft:spider",
    "minecraft:squid",
    "minecraft:stray",
//    "minecraft:tnt",
//    "minecraft:tnt_minecart",
    "minecraft:trader_llama",
    "minecraft:trident",
//    "minecraft:tropical_fish",
    "minecraft:turtle",
    "minecraft:vex",
    "minecraft:villager",
    "minecraft:vindicator",
    "minecraft:wandering_trader",
    "minecraft:witch",
//    "minecraft:wither",
//    "minecraft:wither_skeleton",
//    "minecraft:wither_skull",
    "minecraft:wolf",
    "minecraft:zombie",
    "minecraft:zombie_horse",
    "minecraft:zombie_pigman",
    "minecraft:zombie_villager",
    ""
};


string cmdSummonRandom()
{
//    int tot=mcglobal;
    static int tot=-1;
    if (tot==-1) {
        tot=0;
        while (strlen(ents[tot])!=0) {
//            printf("ents[%d]=%s\n",tot,ents[tot]);
            tot++;
        }
    }
    int what=rand()%4;
//    what=0;
    int q=rand()%tot;
//static int q=0;

    if (what==0)
        sprintf(tmp, "/summon %s ~1 ~2 ~1",ents[q],q);
    else if (what==1)
        sprintf(tmp, "/summon %s ~-1 ~2 ~1",ents[q],q);
    else if (what==2)
        sprintf(tmp, "/summon %s ~-1 ~2 ~-1",ents[q],q);
    else if (what==3)
        sprintf(tmp, "/summon %s ~1 ~2 ~-1",ents[q],q);

    string res = tmp;
//    q=q+1;
//    q=q%tot;
    return res;
}


void setBlockWithCommand(MCRegion &R, int x, int z, int y,const string &cmd, const int &automatic)
{
    ui data = 5; //facing east
    R.A[x][z][y] = BlockInfo(137, 0, data);

    Pos position(R.x_ori + region_xxx*512+x, R.z_ori + region_zzz*512+z, R.y_ori + y);
    delete R.B[x][z][y];

    R.B[x][z][y] = new BlockEntityCommand(position, cmd, automatic, 0);
}

void setRepeatingBlockWithCommand(MCRegion &R, int x, int z, int y, const string &cmd, const int &automatic)
{
    ui data = 5; //facing east
    R.A[x][z][y] = BlockInfo(210, 0, data);

    Pos position(R.x_ori + region_xxx*512+x, R.z_ori + region_zzz*512+z, R.y_ori + y);
    delete R.B[x][z][y];
    R.B[x][z][y] = new BlockEntityCommand(position, cmd, automatic, 0);
}

void setBoom(MCRegion &R, int x, int z, int y) {
        string cmd1 = cmdFillWithTnt();
        setBlockWithCommand(R, x, z, y,  cmd1, 0);
}

void setBlock(MCRegion &R, int x, int z, int y, int xx, int yy, int zz, std::string block_string) {
        string cmd1 = cmdSetBlock(xx,yy,zz,block_string);
        setBlockWithCommand(R, x, z, y,  cmd1, 0);
}

void setKelp(MCRegion &R, int x, int z, int y) {
        string cmd1 = cmdSetKelp();
        setRepeatingBlockWithCommand(R, x, z, y,  cmd1, 1);
}

void setWolf(MCRegion &R, int x, int z, int y) {
        string cmd1 = cmdSummonWolf();
        setBlockWithCommand(R, x, z, y,  cmd1, 0);
}

void setRabbits(MCRegion &R, int x, int z, int y) {
        string cmd1 = cmdSummonRabbits();
        setBlockWithCommand(R, x, z, y,  cmd1, 0);
}

void setRandom(MCRegion &R, int x, int z, int y) {
        string cmd1 = cmdSummonRandom();
        setBlockWithCommand(R, x, z, y,  cmd1, 0);
}

inline bool in_region(int x, int z, int y,   int x1, int z1, int y1,  int x2, int z2, int y2) {
    return x1 <= x && x < x2 && z1 <= z && z < z2 && y1 <= y && y < y2;
}

void setExtra(int x, int z, int y, const string &blockid) {
        SomeStuff.push_back(make_pair(Pos(x, z, y),blockid));
}

void setExtra2(int x, int z, int y, const string &blockid, vector<pair<Pos, string> > &SomeStuff) {
        SomeStuff.push_back(make_pair(Pos(x, z, y),blockid));
}

int num_com=0;
int num_command_blocks=0;

int SORT_GRAY=0;

char arr_between[2048][1024];
char arr_total[1000000];

void makeExtra2(MCRegion &R, vector<pair<Pos, string> > &SomeStuff) {
    int arr_cnt=0;
    int arr_len=0;
    int white=ret_color(255,255,255);
    int index=0;
    int blocknr=0;
    std::string cmd_starter;
    std::string cmd_start=
"summon falling_block ~ ~1 ~ {\
Time:1,BlockState:{Name:redstone_block},Passengers:[{\
id:armor_stand,Health:0,Passengers:[{\
id:falling_block,Time:1,BlockState:{Name:activator_rail},Passengers:[\
{id:command_block_minecart,Command:'gamerule commandBlockOutput false'},";
    std::string cmd_end=
"{id:command_block_minecart,Command:'setblock ~ ~1 ~ command_block{auto:1,Command:\"fill ~ ~ ~ ~ ~-3 ~ air\"}'},\
{id:command_block_minecart,Command:'kill @e[type=command_block_minecart,distance=..1]'}\
]\
}]\
}]\
}";
//    std::string cmd_between;
//    std::string cmd_total;
    char line[1000];
//    printf("\n");
    int blocknr2=0;

//printf("\ncall sorting\n");
    SORT_GRAY=1;
    sort(SomeStuff.begin(), SomeStuff.end());
    SORT_GRAY=0;

    pair<Pos, string> Stuffit;
    int m=SomeStuff.size();

    num_com=0;
    num_command_blocks=0;
    int xdir=1;
    int first=1;
    int chunk_checker=-99999;
    int chunk_checker_next;
    int chunk_checker_y=-99999;
    int chunk_checker_next_y;
    int prevx,prevz;
    int prevx_o,prevz_o;
    int skipper=0;
    prevx_o=((chunk_list[0][0]*16)>>4);
    prevz_o=((chunk_list[0][1]*16)>>4);
    strcpy(arr_total,"");
    for (int t=0; t<2048; t++) strcpy(arr_between[t],"");
    for (int t=0; t<1024; t++) {
        int x1=chunk_list[t][0]*16;
        int z1=chunk_list[t][1]*16;
        int x2=chunk_list[(t+1)%1024][0]*16;
        int z2=chunk_list[(t+1)%1024][1]*16;
        if (x1!=x2) {
            int cnt=-2;
            if (x1<x2) cnt=2;
            for (int x=x1; x!=x2; x+=cnt) {
                R.A[x+7][z1+7][0]=BlockInfo(251,0,ret_color(x/2,z1/2,(255-(x+z1)/4)),0);
                R.A[x+8][z1+7][0]=BlockInfo(251,0,ret_color(z1/2,(255-(x+z1)/4),x/2),0);
                R.A[x+7][z1+8][0]=BlockInfo(251,0,ret_color((255-(x+z1)/4),x/2,z1/2),0);
                if (!(rand()%5)) R.A[x+8][z1+8][0]=BlockInfo(89,0,0,0);
                else R.A[x+8][z1+8][0]=BlockInfo(251,0,ret_color(x/2,(255-(x+z1)/4),z1/2),0);
            }
        } else {
            int cnt=-2;
            if (z1<z2) cnt=2;
            for (int z=z1; z!=z2; z+=cnt) {
                R.A[x1+7][z+7][0]=BlockInfo(251,0,ret_color(x1/2,z/2,(255-(x1+z)/4)),0);
                R.A[x1+8][z+7][0]=BlockInfo(251,0,ret_color(z/2,(255-(x1+z)/4),x1/2),0);
                R.A[x1+7][z+8][0]=BlockInfo(251,0,ret_color((255-(x1+z)/4),x1/2,z/2),0);
                if (!(rand()%5)) R.A[x1+8][z+8][0]=BlockInfo(89,0,0,0);
                else R.A[x1+8][z+8][0]=BlockInfo(251,0,ret_color(x1/2,(255-(x1+z)/4),z/2),0);
            }
        }
    }

    for (auto u : SomeStuff) {
        num_com++;
        toggle2();
        Pos position=u.first;
        std::string blockid=u.second;

        chunk_checker_next=(position.y >> 4) + (position.x >> 4)*16 + (position.z >> 4)*16*32;
        chunk_checker_next_y=(position.x >> 4) + (position.z >> 4)*32;
        skipper=0;
        if (chunk_checker!=chunk_checker_next) {
            prevx=(position.x+region_xxx*512)>>4;
            prevz=(position.z+region_zzz*512)>>4;

//            sprintf(line,"{id:command_block_minecart,Command:'say doing chunk %d X=%d,Y=%d,Z=%d (blocks at X=%d Y=%d Z=%d)'},",
//                    reversed_chunk_list[position.x>>4][position.z>>4],prevx,(position.y >> 4),prevz,prevx*16,(position.y >> 4)*16,prevz*16);
//            strcpy(arr_between[arr_cnt], line); arr_len+=strlen(line); arr_cnt++;
//            num_com++;

            if (chunk_checker_y!=chunk_checker_next_y) {
                skipper=1;
                chunk_checker_y=chunk_checker_next_y;
                if (chunk_checker!=-99999) {
                    sprintf(line,"{id:command_block_minecart,Command:'forceload remove %d %d %d %d'},",prevx_o*16+region_xxx*32,prevz_o*16+region_zzz*32,prevx_o*16+region_xxx*32+15,prevz_o*16+region_zzz*32+15);
                    strcpy(arr_between[arr_cnt], line); arr_len+=strlen(line); arr_cnt++;
                    num_com++;
                }
                sprintf(line,"{id:command_block_minecart,Command:'forceload add %d %d %d %d'},",prevx*16,prevz*16,prevx*16+15,prevz*16+15);
                strcpy(arr_between[arr_cnt], line); arr_len+=strlen(line); arr_cnt++;
                num_com++;
                char count[80];
                sprintf(count," %d (%3d,%3d,%3d) %d/%d",reversed_chunk_list[position.x>>4][position.z>>4],position.x,position.y,position.z,num_command_blocks,num_com);
                printf("%s",count);
                for (int t=0; t<strlen(count); t++) printf("\b");
            }
            chunk_checker=chunk_checker_next;
        }

        if ( (arr_len>10000 || arr_cnt>25) || skipper==1) {
            num_command_blocks++;
            if (skipper==1) {
                sprintf(line,"{id:command_block_minecart,Command:'setblock %d 5 %d glowstone'},",1+prevx*16,1+prevz*16);
                strcpy(arr_between[arr_cnt], line); arr_len+=strlen(line); arr_cnt++;

                sprintf(line,"{id:command_block_minecart,Command:'setblock %d ~-1 %d redstone_block'},",1+prevx*16,1+prevz*16);
                strcpy(arr_between[arr_cnt], line); arr_len+=strlen(line); arr_cnt++;

/*
                sprintf(line,"{id:command_block_minecart,Command:'setblock %d ~-1 %d minecraft:redstone_block'},",1+prevx*16+16,1+prevz*16);
                strcpy(arr_between[arr_cnt], line); arr_len+=strlen(line); arr_cnt++;
                sprintf(line,"{id:command_block_minecart,Command:'setblock %d ~-1 %d minecraft:redstone_block'},",1+prevx*16-16,1+prevz*16);
                strcpy(arr_between[arr_cnt], line); arr_len+=strlen(line); arr_cnt++;
                sprintf(line,"{id:command_block_minecart,Command:'setblock %d ~-1 %d minecraft:redstone_block'},",1+prevx*16,1+prevz*16+16);
                strcpy(arr_between[arr_cnt], line); arr_len+=strlen(line); arr_cnt++;
                sprintf(line,"{id:command_block_minecart,Command:'setblock %d ~-1 %d minecraft:redstone_block'},",1+prevx*16,1+prevz*16-16);
                strcpy(arr_between[arr_cnt], line); arr_len+=strlen(line); arr_cnt++;
*/
            } else {
                if ((xdir==1 && blocknr==12) || (xdir==-1 && blocknr==2)) {

                    sprintf(line,"{id:command_block_minecart,Command:'setblock ~ ~-1 ~2 redstone_block'},");
                    strcpy(arr_between[arr_cnt], line); arr_len+=strlen(line); arr_cnt++;
//                    sprintf(line,"{id:command_block_minecart,Command:'setblock ~2 ~-1 ~2 minecraft:redstone_block'},");

                    sprintf(line,"{id:command_block_minecart,Command:'playsound minecraft:block.dispenser.launch block @a ~ ~-1 ~2'},");
                    strcpy(arr_between[arr_cnt], line); arr_len+=strlen(line); arr_cnt++;

                    sprintf(line,"{id:command_block_minecart,Command:'setblock ~-2 ~-1 ~2 redstone_block'},");
                    strcpy(arr_between[arr_cnt], line); arr_len+=strlen(line); arr_cnt++;

                    sprintf(line,"{id:command_block_minecart,Command:'playsound minecraft:block.dispenser.launch block @a ~-2 ~-1 ~2'},");
                    strcpy(arr_between[arr_cnt], line); arr_len+=strlen(line); arr_cnt++;

                } else {
                    if ( (xdir==1 && blocknr!=14) || (xdir==-1 && blocknr==0) ) {
                        sprintf(line,"{id:command_block_minecart,Command:'setblock ~2 ~-1 ~ redstone_block'},");
                        strcpy(arr_between[arr_cnt], line); arr_len+=strlen(line); arr_cnt++;

                        sprintf(line,"{id:command_block_minecart,Command:'playsound minecraft:block.dispenser.launch block @a ~2 ~-1 ~'},");
                        strcpy(arr_between[arr_cnt], line); arr_len+=strlen(line); arr_cnt++;

                        sprintf(line,"{id:command_block_minecart,Command:'setblock ~2 ~-1 ~2 redstone_block'},");
                        strcpy(arr_between[arr_cnt], line); arr_len+=strlen(line); arr_cnt++;

                        sprintf(line,"{id:command_block_minecart,Command:'playsound minecraft:block.dispenser.launch block @a ~2 ~-1 ~2'},");
                        strcpy(arr_between[arr_cnt], line); arr_len+=strlen(line); arr_cnt++;

//                        sprintf(line,"{id:command_block_minecart,Command:'setblock ~2 ~-1 ~-2 minecraft:redstone_block'},");
                    } else {
                        sprintf(line,"{id:command_block_minecart,Command:'setblock ~-2 ~-1 ~ redstone_block'},");
                        strcpy(arr_between[arr_cnt], line); arr_len+=strlen(line); arr_cnt++;

                        sprintf(line,"{id:command_block_minecart,Command:'playsound minecraft:block.dispenser.launch block @a ~-2 ~-1 ~'},");
                        strcpy(arr_between[arr_cnt], line); arr_len+=strlen(line); arr_cnt++;

                        sprintf(line,"{id:command_block_minecart,Command:'setblock ~-2 ~-1 ~2 redstone_block'},");
                        strcpy(arr_between[arr_cnt], line); arr_len+=strlen(line); arr_cnt++;

                        sprintf(line,"{id:command_block_minecart,Command:'playsound minecraft:block.dispenser.launch block @a ~-2 ~-1 ~'},");
                        strcpy(arr_between[arr_cnt], line); arr_len+=strlen(line); arr_cnt++;
//                        sprintf(line,"{id:command_block_minecart,Command:'setblock ~-2 ~-1 ~-2 minecraft:redstone_block'},");
                    }
                }
//                strcpy(arr_between[arr_cnt], line); arr_len+=strlen(line); arr_cnt++;
            }

            strcpy(arr_total,cmd_start.c_str());
            for (int n=0; n<arr_cnt; n++)   strcat(arr_total,arr_between[n]);
            strcat(arr_total,cmd_end.c_str());
            arr_cnt=0;
            arr_len=0;
            num_com++;
            if (xdir==1)
                blocknr+=2;
            else
                blocknr-=2;

            if (blocknr>14) {
                xdir=-1;
                blocknr=14;
                blocknr2+=2;
            } else if (blocknr<0) {
                xdir=1;
                blocknr=0;
                blocknr2+=2;
            }
            setBlockWithCommand(R, 1+blocknr+prevx_o*16, 1+blocknr2+prevz_o*16, 1,  std::string{arr_total}, 0);
            R.A[1+blocknr+prevx_o*16][1+blocknr2+prevz_o*16][0]=BlockInfo(89,0,0,0);

//            if (turbo_on) {
//                if (0+blocknr+prevx_o*16 >= 0 && 0+blocknr+prevx_o*16 < 512 && 1+blocknr2+prevz_o*16 >=0 && 1+blocknr2+prevz_o*16 <512) R.A[0+blocknr+prevx_o*16][1+blocknr2+prevz_o*16][1]=BlockInfo(76,0,0,0);
//                if (2+blocknr+prevx_o*16 >= 0 && 2+blocknr+prevx_o*16 < 512 && 1+blocknr2+prevz_o*16 >=0 && 1+blocknr2+prevz_o*16 <512) R.A[2+blocknr+prevx_o*16][1+blocknr2+prevz_o*16][1]=BlockInfo(76,0,0,0);
//                if (1+blocknr+prevx_o*16 >= 0 && 1+blocknr+prevx_o*16 < 512 && 0+blocknr2+prevz_o*16 >=0 && 0+blocknr2+prevz_o*16 <512) R.A[1+blocknr+prevx_o*16][0+blocknr2+prevz_o*16][1]=BlockInfo(76,0,0,0);
//                if (1+blocknr+prevx_o*16 >= 0 && 1+blocknr+prevx_o*16 < 512 && 2+blocknr2+prevz_o*16 >=0 && 2+blocknr2+prevz_o*16 <512) R.A[1+blocknr+prevx_o*16][2+blocknr2+prevz_o*16][1]=BlockInfo(76,0,0,0);

//                if (0+blocknr+prevx_o*16 >= 0 && 0+blocknr+prevx_o*16 < 512 && 0+blocknr2+prevz_o*16 >=0 && 0+blocknr2+prevz_o*16 <512) R.A[0+blocknr+prevx_o*16][0+blocknr2+prevz_o*16][1]=BlockInfo(55,0,0,0);
//                if (0+blocknr+prevx_o*16 >= 0 && 0+blocknr+prevx_o*16 < 512 && 2+blocknr2+prevz_o*16 >=0 && 2+blocknr2+prevz_o*16 <512) R.A[0+blocknr+prevx_o*16][2+blocknr2+prevz_o*16][1]=BlockInfo(55,0,0,0);
//                if (2+blocknr+prevx_o*16 >= 0 && 2+blocknr+prevx_o*16 < 512 && 0+blocknr2+prevz_o*16 >=0 && 0+blocknr2+prevz_o*16 <512) R.A[2+blocknr+prevx_o*16][0+blocknr2+prevz_o*16][1]=BlockInfo(55,0,0,0);
//                if (2+blocknr+prevx_o*16 >= 0 && 2+blocknr+prevx_o*16 < 512 && 2+blocknr2+prevz_o*16 >=0 && 2+blocknr2+prevz_o*16 <512) R.A[2+blocknr+prevx_o*16][2+blocknr2+prevz_o*16][1]=BlockInfo(55,0,0,0);

//            } else {
                if (0+blocknr+prevx_o*16 >= 0 && 0+blocknr+prevx_o*16 < 512 && 1+blocknr2+prevz_o*16 >=0 && 1+blocknr2+prevz_o*16 <512) R.A[0+blocknr+prevx_o*16][1+blocknr2+prevz_o*16][1]=BlockInfo(147,0,0,0);
                if (2+blocknr+prevx_o*16 >= 0 && 2+blocknr+prevx_o*16 < 512 && 1+blocknr2+prevz_o*16 >=0 && 1+blocknr2+prevz_o*16 <512) R.A[2+blocknr+prevx_o*16][1+blocknr2+prevz_o*16][1]=BlockInfo(147,0,0,0);
                if (1+blocknr+prevx_o*16 >= 0 && 1+blocknr+prevx_o*16 < 512 && 0+blocknr2+prevz_o*16 >=0 && 0+blocknr2+prevz_o*16 <512) R.A[1+blocknr+prevx_o*16][0+blocknr2+prevz_o*16][1]=BlockInfo(147,0,0,0);
                if (1+blocknr+prevx_o*16 >= 0 && 1+blocknr+prevx_o*16 < 512 && 2+blocknr2+prevz_o*16 >=0 && 2+blocknr2+prevz_o*16 <512) R.A[1+blocknr+prevx_o*16][2+blocknr2+prevz_o*16][1]=BlockInfo(147,0,0,0);
//            }

            if (skipper==1) {
                prevx_o=prevx%32;
                prevz_o=prevz%32;
                blocknr=-2;
                blocknr2=0;
                xdir=1;
            }
        }
        char c=blockid.c_str()[0];
        sprintf(line,"{id:command_block_minecart,Command:'setblock %d %d %d %s'},",position.x+region_xxx*512, position.y, position.z+region_zzz*512, blockid.c_str());
        strcpy(arr_between[arr_cnt], line); arr_len+=strlen(line); arr_cnt++;
    }
    if ( arr_cnt>0) {
        num_command_blocks++;
        char count[80];
        sprintf(count," %d/%d",num_com,num_command_blocks);
        for (int t=0; t<strlen(count); t++) printf("\b");
        if ((xdir==1 && blocknr==12) || (xdir==-1 && blocknr==2)) {
            sprintf(line,"{id:command_block_minecart,Command:'setblock ~ ~-1 ~2 redstone_block'},");
        } else {
            if ( (xdir==1 && blocknr!=14) || (xdir==-1 && blocknr==0) ) {
                sprintf(line,"{id:command_block_minecart,Command:'setblock ~2 ~-1 ~ redstone_block'},");
            } else {
                sprintf(line,"{id:command_block_minecart,Command:'setblock ~-2 ~-1 ~ redstone_block'},");
            }
        }
        strcpy(arr_between[arr_cnt], line); arr_len+=strlen(line); arr_cnt++;

        strcpy(arr_total,cmd_start.c_str());
        for (int n=0; n<arr_cnt; n++)
            strcat(arr_total,arr_between[n]);
        strcat(arr_total,cmd_end.c_str());
        arr_cnt=0;
        arr_len=0;
        num_com++;
        if (xdir==1)
            blocknr+=2;
        else
            blocknr-=2;

        if (blocknr>14) {
            xdir=-1;
            blocknr=14;
            blocknr2+=2;
        } else if (blocknr<0) {
            xdir=1;
            blocknr=0;
            blocknr2+=2;
        }
        setBlockWithCommand(R, 1+blocknr+prevx_o*16, 1+blocknr2+prevz_o*16, 1,  std::string{arr_total}, 0);
        R.A[1+blocknr+prevx_o*16][1+blocknr2+prevz_o*16][0]=BlockInfo(89,0,0,0);

//        if (0+blocknr+prevx_o*16 >= 0 && 0+blocknr+prevx_o*16 < 512 && 1+blocknr2+prevz_o*16 >=0 && 1+blocknr2+prevz_o*16 <512) R.A[0+blocknr+prevx_o*16][1+blocknr2+prevz_o*16][1]=BlockInfo(147,0,0,0);
//        if (2+blocknr+prevx_o*16 >= 0 && 2+blocknr+prevx_o*16 < 512 && 1+blocknr2+prevz_o*16 >=0 && 1+blocknr2+prevz_o*16 <512) R.A[2+blocknr+prevx_o*16][1+blocknr2+prevz_o*16][1]=BlockInfo(147,0,0,0);
//        if (1+blocknr+prevx_o*16 >= 0 && 1+blocknr+prevx_o*16 < 512 && 0+blocknr2+prevz_o*16 >=0 && 0+blocknr2+prevz_o*16 <512) R.A[1+blocknr+prevx_o*16][0+blocknr2+prevz_o*16][1]=BlockInfo(147,0,0,0);
//        if (1+blocknr+prevx_o*16 >= 0 && 1+blocknr+prevx_o*16 < 512 && 2+blocknr2+prevz_o*16 >=0 && 2+blocknr2+prevz_o*16 <512) R.A[1+blocknr+prevx_o*16][2+blocknr2+prevz_o*16][1]=BlockInfo(147,0,0,0);
//        if (turbo_on) {
//            if (0+blocknr+prevx_o*16 >= 0 && 0+blocknr+prevx_o*16 < 512 && 1+blocknr2+prevz_o*16 >=0 && 1+blocknr2+prevz_o*16 <512) R.A[0+blocknr+prevx_o*16][1+blocknr2+prevz_o*16][1]=BlockInfo(76,0,0,0);
//            if (2+blocknr+prevx_o*16 >= 0 && 2+blocknr+prevx_o*16 < 512 && 1+blocknr2+prevz_o*16 >=0 && 1+blocknr2+prevz_o*16 <512) R.A[2+blocknr+prevx_o*16][1+blocknr2+prevz_o*16][1]=BlockInfo(76,0,0,0);
//            if (1+blocknr+prevx_o*16 >= 0 && 1+blocknr+prevx_o*16 < 512 && 0+blocknr2+prevz_o*16 >=0 && 0+blocknr2+prevz_o*16 <512) R.A[1+blocknr+prevx_o*16][0+blocknr2+prevz_o*16][1]=BlockInfo(76,0,0,0);
//            if (1+blocknr+prevx_o*16 >= 0 && 1+blocknr+prevx_o*16 < 512 && 2+blocknr2+prevz_o*16 >=0 && 2+blocknr2+prevz_o*16 <512) R.A[1+blocknr+prevx_o*16][2+blocknr2+prevz_o*16][1]=BlockInfo(76,0,0,0);

//            if (0+blocknr+prevx_o*16 >= 0 && 0+blocknr+prevx_o*16 < 512 && 0+blocknr2+prevz_o*16 >=0 && 0+blocknr2+prevz_o*16 <512) R.A[0+blocknr+prevx_o*16][0+blocknr2+prevz_o*16][1]=BlockInfo(55,0,0,0);
//            if (0+blocknr+prevx_o*16 >= 0 && 0+blocknr+prevx_o*16 < 512 && 2+blocknr2+prevz_o*16 >=0 && 2+blocknr2+prevz_o*16 <512) R.A[0+blocknr+prevx_o*16][2+blocknr2+prevz_o*16][1]=BlockInfo(55,0,0,0);
//            if (2+blocknr+prevx_o*16 >= 0 && 2+blocknr+prevx_o*16 < 512 && 0+blocknr2+prevz_o*16 >=0 && 0+blocknr2+prevz_o*16 <512) R.A[2+blocknr+prevx_o*16][0+blocknr2+prevz_o*16][1]=BlockInfo(55,0,0,0);
//            if (2+blocknr+prevx_o*16 >= 0 && 2+blocknr+prevx_o*16 < 512 && 2+blocknr2+prevz_o*16 >=0 && 2+blocknr2+prevz_o*16 <512) R.A[2+blocknr+prevx_o*16][2+blocknr2+prevz_o*16][1]=BlockInfo(55,0,0,0);

//        } else {
            if (0+blocknr+prevx_o*16 >= 0 && 0+blocknr+prevx_o*16 < 512 && 1+blocknr2+prevz_o*16 >=0 && 1+blocknr2+prevz_o*16 <512) R.A[0+blocknr+prevx_o*16][1+blocknr2+prevz_o*16][1]=BlockInfo(147,0,0,0);
            if (2+blocknr+prevx_o*16 >= 0 && 2+blocknr+prevx_o*16 < 512 && 1+blocknr2+prevz_o*16 >=0 && 1+blocknr2+prevz_o*16 <512) R.A[2+blocknr+prevx_o*16][1+blocknr2+prevz_o*16][1]=BlockInfo(147,0,0,0);
            if (1+blocknr+prevx_o*16 >= 0 && 1+blocknr+prevx_o*16 < 512 && 0+blocknr2+prevz_o*16 >=0 && 0+blocknr2+prevz_o*16 <512) R.A[1+blocknr+prevx_o*16][0+blocknr2+prevz_o*16][1]=BlockInfo(147,0,0,0);
            if (1+blocknr+prevx_o*16 >= 0 && 1+blocknr+prevx_o*16 < 512 && 2+blocknr2+prevz_o*16 >=0 && 2+blocknr2+prevz_o*16 <512) R.A[1+blocknr+prevx_o*16][2+blocknr2+prevz_o*16][1]=BlockInfo(147,0,0,0);
//        }
/*
*/
    }
    SomeStuff.clear();
    SomeStuff.shrink_to_fit();

    sprintf(line,"{id:command_block_minecart,Command:'gamerule randomTickSpeed 5'},");
    strcpy(arr_between[arr_cnt], line); arr_len+=strlen(line); arr_cnt++;
    sprintf(line,"{id:command_block_minecart,Command:'setblock ~2 ~-1 ~ redstone_block'},");
    strcpy(arr_between[arr_cnt], line); arr_len+=strlen(line); arr_cnt++;
    strcpy(arr_total,cmd_start.c_str());
    for (int n=0; n<arr_cnt; n++) strcat(arr_total,arr_between[n]);
    strcat(arr_total,cmd_end.c_str());

//    cmd_total=arr_total;

    setBlockWithCommand(R, 1+chunk_list[0][0]*16, 1+chunk_list[0][1]*16, 1,  std::string{arr_total}, 0);
//    setBlockWithCommand(R, 1+chunk_list[0][0]*16, 1+chunk_list[0][1]*16, 1,  cmd_total, 0);
    R.A[1+chunk_list[0][0]*16][1+chunk_list[0][1]*16][0]=BlockInfo(89,0,0,0);

    R.A[0+chunk_list[0][0]*16][1+chunk_list[0][1]*16][5]=BlockInfo(89,0,0,0);
    R.A[1+chunk_list[0][0]*16][1+chunk_list[0][1]*16][5]=BlockInfo(89,0,0,0);
    R.A[1+chunk_list[0][0]*16][1+chunk_list[0][1]*16][4]=BlockInfo(89,0,0,0);
    R.A[2+chunk_list[0][0]*16][1+chunk_list[0][1]*16][5]=BlockInfo(89,0,0,0);

    R.A[0+chunk_list[0][0]*16][0+chunk_list[0][1]*16][5]=BlockInfo(89,0,0,0);
    R.A[1+chunk_list[0][0]*16][0+chunk_list[0][1]*16][5]=BlockInfo(89,0,0,0);
    R.A[2+chunk_list[0][0]*16][0+chunk_list[0][1]*16][5]=BlockInfo(89,0,0,0);

    R.A[0+chunk_list[0][0]*16][2+chunk_list[0][1]*16][5]=BlockInfo(89,0,0,0);
    R.A[1+chunk_list[0][0]*16][2+chunk_list[0][1]*16][5]=BlockInfo(89,0,0,0);
    R.A[2+chunk_list[0][0]*16][2+chunk_list[0][1]*16][5]=BlockInfo(89,0,0,0);

    R.A[1+chunk_list[0][0]*16][0+chunk_list[0][1]*16][1]=BlockInfo(147, 0, 0, 0 );
    R.A[1+chunk_list[0][0]*16][2+chunk_list[0][1]*16][1]=BlockInfo(147, 0, 0, 0 );
    R.A[0+chunk_list[0][0]*16][1+chunk_list[0][1]*16][1]=BlockInfo(147, 0, 0, 0 );
    R.A[2+chunk_list[0][0]*16][1+chunk_list[0][1]*16][1]=BlockInfo(147, 0, 0, 0 );
}




int main_mceditor2()
{
    int region_x=0;
    int region_z=0;

    int skippy=0;
    int skippy2=0;
    int contin=1;
    int skipping=1;
    int light=0;
    int size_regions=0;
	srand(time(0));
	int first_loop=1;
    remove_block_entities=1;
    while (size_regions<60) {
        size_regions++;
        for (region_x=0; region_x<size_regions && MCEDITOR_stop==0; region_x++) {
            for (region_z=0; region_z<size_regions && MCEDITOR_stop==0; region_z++) {
                region_xxx=region_x;
                region_zzz=region_z;
                if (region_x<size_regions-1 && region_z<size_regions-1) {
                    continue;
                }
                toggle_2=0;toggle_3=0;
                if (contin==1) {
                    contin=0;
                }
                chunk_offsetx=region_x*32;
                chunk_offsetz=region_z*32;

                x00=0;
                y00=0;
                z00=0;
                yl=255;
                xl=512; zl=512;


    //            file_name_MCA = MCAFileNameXZ(region_x, region_z);
    //            editor.mca_coder.loadMCA(file_name_MCA);
                char tmp[256];
                sprintf(tmp, "/Saves/Test/region/r.%d.%d.mca", region_x, region_z);
//                string fname=MCAFileNameXZ(region_x, region_z);
                string fname=tmp;
                if ( file_exists(fname.c_str() ) ) {
                    if (skippy2>0) printf("\n");
                    skippy2=0;
                    if (skippy==0)
                        printf("File(s) exists, skipping %s",fname.c_str());
                    else
                        printf(", %s",fname.c_str());
                    skippy++;
                    continue;
                }
//                printf("here 12\n");

                char comm[100];
//                sprintf(comm,"copy %s %s","/Saves/Leeg/region/r.0.0.mca",fname.c_str());
                CopyFile("/Saves/Leeg/region/r.0.0.mca",fname.c_str(),false);

                skipping=1;
//                printf("Getting data\n");
                read_one_plot_WINMAIN(region_z*512, region_x*512 + 30720, &image_plot_extra);
                read_one_plot_WINMAIN(region_x*512-5, region_z*512-5, &image_plot);
                read_one_plot_WINMAIN(region_x*512-5, region_z*512-5, &image_plot3);
                read_one_plot_WINMAIN(region_x*512-5, region_z*512-5, &image_plot_org);

                for (int x = 0; x < 512; x++) {
                    for (int z = 0; z < 512; z++) {
                        if ( !( (image_plot.getPixel(x+5,z+5).r==0) && (image_plot.getPixel(x+5,z+5).b==0) && (image_plot.getPixel(x+5,z+5).g==0)) ) {
                            skipping=0;
                        }
                    }
                }
                if (skipping==1) {
                    if (skippy>0) printf("\n");
                    skippy=0;
                    if (skippy2==0)
                        printf("Empty...no data...skipping r.%d.%d",region_x,region_z);
                    else
                        printf(", r.%d.%d",region_x,region_z);
                    skippy2++;
                    continue;
                }
                for (int x = 0; x < 512+10; x++) {
                    for (int z = 0; z < 512+10; z++) {
                        float pixel;
                        float c;
                        sf::Color col;
                        col=image_plot.getPixel(x,z);
                        c=(col.r+col.b+col.g);
                        pixel = (c/(3));
                        if (col.a==0) pixel=0;
                        if (pixel!=0 && x>0 && x<511+10 && z>0 && z<511+10) {
                            for (int xxx=-1; xxx<=1; xxx++) {
                                for (int zzz=-1; zzz<=1; zzz++) {
//                                    if (xxx==0 || zzz==0) {
                                    if (xxx!=0 || zzz!=0) {
//                                        image_plot3.setPixel(x+xxx,z+zzz, col);
                                        if ((image_plot3.getPixel(x+xxx,z+zzz).r)!=254) image_plot3.setPixel(x+xxx,z+zzz, col);
                                    }
                                }
                            }
                        }
                    }
                }
                for (int x = 0; x < 512+10; x++) {
                    for (int z = 0; z < 512+10; z++) {
                        float pixel;
                        float c;
                        sf::Color col;
                        col=image_plot3.getPixel(x,z);
                        c=(col.r+col.b+col.g);
                        pixel = (c/(3));
                        if (col.a==0) pixel=0;
                        if (pixel!=0 && x>0 && x<511+10 && z>0 && z<511+10) {
                            for (int xxx=-1; xxx<=1; xxx++) {
                                for (int zzz=-1; zzz<=1; zzz++) {
//                                    if (xxx==0 || zzz==0) {
                                    if (xxx!=0 || zzz!=0) {
//                                        image_plot.setPixel(x+xxx,z+zzz, col);
                                        if ((image_plot.getPixel(x+xxx,z+zzz).r)!=254) image_plot.setPixel(x+xxx,z+zzz, col);
                                    }
                                }
                            }
                        }
                    }
                }

//                region.clearRegion();
                MCRegion region(x00, z00, y00, xl, zl, yl);
                if (skippy>0 || skippy2>0) printf("\n");
                skippy2=0;
                skippy=0;
                first_MCEDIT=1;
                editor.mca_coder.loadMCA("/Saves/Leeg/region/r.0.0.mca");
                editor.mca_coder.setPOSITIONS();
                first_MCEDIT=0;
                region_x_old=0,region_z_old=0;

                printf("- Creating region r.%d.%d.mca: ",region_x,region_z);

                BlockInfo*** AX=region.A;
                int leuk_max=1;
                if (1) {
                    int mix1;                int mix2;                int mix3;                int mix4;
                    int mix5;                int mix6;                int mix7;                int mix8;                int mix9;
                    int num_blocks=0;
//                    int leuk_max=rand()%4;
                    leuk_max=rand()%4;
                    for (int leuk=0; leuk<=leuk_max; leuk++) {
                        mix1=rand()%50-25;                    mix2=rand()%50-25;                    mix3=rand()%50-25;                    mix4=rand()%50-25;
                        mix5=rand()%50-25;                    mix6=rand()%50-25;                    mix7=rand()%50-25;                    mix8=rand()%50-25;                    mix9=rand()%50-25;

                        if (first_loop==1) {
                            first_loop=0;
                            mix1=0;mix2=0;mix3=0;mix4=0;mix5=0;mix6=0;mix7=0;mix8=0;mix9=0;
                        }
//editor.mca_coder.getBlock(x,z,y);
                        printf(" Globes:\b\b\b\b\b\b\b\b");
                        if (!fast_build)
                        for (int x = 0; x < xl; x++) {
                            xx=x+chunk_offsetx*16;
                            BlockInfo** AZ=AX[x];
                            for (int z = 0; z < zl; z++) {
                                zz=z+chunk_offsetz*16;
                                BlockInfo* AY=AZ[z];
                                int r, g, b;
                                float pixel;

                                float c;
                                sf::Color col;
                                sf::Color col_extra;
                                col=image_plot.getPixel(x+5,z+5);
                                col_extra=image_plot_extra.getPixel(x,z);

                                toggle2();

                                c=(col.r+col.b+col.g);
                                pixel = (c/(3));
                                if (col.a==0) pixel=0;

                                if (rand()%20<5 && rand()%512<(100+(int)(mix1)) && rand()%512<70-leuk*15 && rand()%256<25)  {
                                    int size_globe=(int)((float)( sin( sin(xx/34.8)*3.1415 + sin(zz/45.7)*3.1415 ) + 1 )*(float)(350+mix2*8)+10.0);
                                    float s=(float)( rand()%((int)(size_globe))+10)/11 ;

    //                                int xr=rand()%(511-(int)(s*2)-2);
    //                                int zr=rand()%(511-(int)(s*2)-2);
    //                                int yr=20+rand()%(210   -(int)(s*2)-2);

                                    int xr=rand()%(512);
                                    int zr=rand()%(512);
                                    int yr=rand()%(256);

                                    int colr=rand()%16;
                                    int blockr;
                                        if (rand()%15==0) blockr=95;
                                    else blockr=251;
                                    int color_one=rand()%16;
                                    float blob1=(float)((rand()%70)+15)/10;
                                    float blob2=(float)((rand()%70)+15)/10;
                                    float blob3=(float)((rand()%70)+15)/10;
                                    float blob4=(float)((rand()%70)+15)/10;
                                    float blob5=(float)((rand()%70)+15)/10;
                                    float blob6=(float)((rand()%70)+15)/10;
                                    for (int xc=(int)-s; xc<(int)(s); xc++) {
                                        for (int zc=(int)-s; zc<(int)(s); zc++) {
                                            toggle2();
                                            for (int yc=(int)-s; yc<(int)(s); yc++) {
                                                float some1;
                                                float some2;
                                                int r;
                                                int g;
                                                int b;
                                                int one_col=1;

                                                one_col=0;
                                                some1=sin(sin((xx+xr+xc)/10)*2+sin((zz+zr+zc)/5.32)*2)*4;
                                                some2=sin(sin((xx+xr+xc)/15.23)*2+sin((zz+zr+zc)/13.32)*2)*4;
                                                int flow;
                                                flow = (   sin((xx+xr+xc)/(83.23+some1) + sin((zz+zr+zc)/73.75)/3 )  +  sin((zz+zr+zc)/(19.75+some2) + sin((xx+xr+xc)/34.87)/7.2  )  )*5+10;
                                                flow+= (sin((xx+xr+xc)/(94.23+some1/20) + sin((zz+zr+zc)/57.75)/2 )+sin((zz+zr+zc)/(26.75+some2/20) + sin((xx+xr+xc)/45.87)/5 ))*1.25+2.5;
                                                flow+= (   sin((xx+xr+xc)/(62.23+some1*2) + sin((zz+zr+zc)/54.75)/3 )  +  sin((zz+zr+zc)/(64.75+some2*3) + sin((xx+xr+xc)/47.87)/6.2  )  )*15+30;

                                                r=(int)( ( ( sin(((float)(zz+zr+zc)/18+(float)(xx+xr+xc)/7+(yc+yr)/6+some1)/30) +sin(flow/33-(float)(yc+yr)/36.66) ) + 2 ) * 60 ) + rand()%(int)(15);
                                                g=(int)( ( ( sin(((float)(yc+yr)/14+(float)(xx+xr+xc)/13+(float)(zz+zr+zc)/17+some1)/49) + sin(flow/74+(float)(yc+yr)/23.33) ) + 2 ) * 60 ) + rand()%(int)(15);
                                                b=(int)( ( ( sin(((float)(zz+zr+zc)/12+(float)(xx+xr+xc)/14+(float)(yc+yr)/12.5+some1)/53) + sin(flow/44+(float)(yc+yr)/30) ) + 2 ) * 60 ) + rand()%(int)(15);

                                                if ( sqrt(
                                                          ((float)xc+(some1+(float)flow/30)/(s/blob1))*((float)xc+some1/(s/blob2)) +
                                                          ((float)zc+(some2+(float)flow/25)/(s/blob4))*((float)zc+some2/(s/blob3)) +
                                                          ((float)yc+(some1+some2)/(s/blob5) )*((float)yc+(some1+some2+(float)flow/20)/(s/blob6))
                                                          )  < (s)
                                                    ) {
                                                        if (in_region(xr+xc, zr+zc, yr+yc, 0, 0, 11, xl , zl , yl-6)) {
                                                            if (one_col)
                                                                AX[xr+xc][zr+zc][yr+yc]=BlockInfo(blockr, 0, ret_color(r,g,b),0 );
                                                            else
                                                                AX[xr+xc][zr+zc][yr+yc]=BlockInfo(blockr, 0, color_one,0 );
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }

                        printf(" Hollow:\b\b\b\b\b\b\b\b");
                        if (!fast_build)
                        for (int x = 0; x < 512; x++) {
                            xx=x+chunk_offsetx*16;
                            BlockInfo** AZ=AX[x];
                            for (int z = 0; z < 512; z++) {
                                zz=z+chunk_offsetz*16;
                                BlockInfo* AY=AZ[z];
                                toggle2();
                                for (int y = 10; y < yl; y++) {
                                    if (AY[y].id!=0) {
                                        if ( y>0 && y<255 && x>0 && x<511 & z>0 && z<511) {
//                                        if ( y>0 && y<255 && x>0 && x<511 & z>1 && z<511) {
                                            if (  (
                                                    (AX[x-1][z-1][y-1].id!=0) &&
                                                    (AX[x+0][z-1][y-1].id!=0) &&
                                                    (AX[x+1][z-1][y-1].id!=0) &&
                                                    (AX[x-1][z+0][y-1].id!=0) &&
                                                    (AX[x+0][z+0][y-1].id!=0) &&
                                                    (AX[x+1][z+0][y-1].id!=0) &&
                                                    (AX[x-1][z+1][y-1].id!=0) &&
                                                    (AX[x+0][z+1][y-1].id!=0) &&
                                                    (AX[x+1][z+1][y-1].id!=0) &&

                                                    (AX[x-1][z-1][y+0].id!=0) &&
                                                    (AX[x+0][z-1][y+0].id!=0) &&
                                                    (AX[x+1][z-1][y+0].id!=0) &&
                                                    (AX[x-1][z+0][y+0].id!=0) &&
                                                    (AX[x+0][z+0][y+0].id!=0) &&
                                                    (AX[x+1][z+0][y+0].id!=0) &&
                                                    (AX[x-1][z+1][y+0].id!=0) &&
                                                    (AX[x+0][z+1][y+0].id!=0) &&
                                                    (AX[x+1][z+1][y+0].id!=0) &&

                                                    (AX[x-1][z-1][y+1].id!=0) &&
                                                    (AX[x+0][z-1][y+1].id!=0) &&
                                                    (AX[x+1][z-1][y+1].id!=0) &&
                                                    (AX[x-1][z+0][y+1].id!=0) &&
                                                    (AX[x+0][z+0][y+1].id!=0) &&
                                                    (AX[x+1][z+0][y+1].id!=0) &&
                                                    (AX[x-1][z+1][y+1].id!=0) &&
                                                    (AX[x+0][z+1][y+1].id!=0) &&
                                                    (AX[x+1][z+1][y+1].id!=0)

                                             ) ) {
                                                    AX[x][z][y].id = 255;
                                             }
                                        }
                                    }
                                }
                            }
                        }

                        for (int x = 0; x < 512; x++) {
                            BlockInfo** AZ=AX[x];
                            for (int z = 0; z < 512; z++) {
                                BlockInfo* AY=AZ[z];
                                toggle2();
                                for (int y = 0; y < yl; y++) {
                                    if (  AY[y].id==255) {
                                        AY[y] = BlockInfo();
                                    }
                                }
                            }
                        }


                        printf(" Globes:\b\b\b\b\b\b\b\b");
//                        if (!fast_build)
                        for (int x = 0; x < xl; x++) {
                            xx=x+chunk_offsetx*16;
                            BlockInfo** AZ=AX[x];
                            for (int z = 0; z < zl; z++) {
                                zz=z+chunk_offsetz*16;
                                BlockInfo* AY=AZ[z];
                                int r, g, b;
                                float pixel;

                                float c;
                                sf::Color col;
                                sf::Color col_extra;
                                col=image_plot_org.getPixel(x+5,z+5);
                                col_extra=image_plot_extra.getPixel(x,z);

                                toggle2();

                                c=(col.r+col.b+col.g);
                                pixel = (c/(3));
                                if (col.a==0) pixel=0;

                                if (!fast_build && rand()%20<5 && rand()%512<(150+(int)(mix1)) && rand()%512<50+leuk*15 && rand()%256<25)  {
                                    int size_globe=( sin( sin(xx/64.8)*3.1415 + sin(zz/88.7)*3.1415 ) + 1 )*(250+mix4-(leuk==0)*125);
                                    float s=(float)(rand()%(size_globe+30))/11;
                                    int xr=rand()%(512);
                                    int zr=rand()%(512);
                                    int yr;
                                    if (leuk==leuk_max) {
                                        yr=90+rand()%25;
                                    } else {
                                        yr=rand()%(256);
                                    }

    //                                int xr=rand()%(511-(int)(s*2)-2);
    //                                int zr=rand()%(511-(int)(s*2)-2);
    //                                int yr=30+rand()%(210   -(int)(s*2)-2);

                                    int colr=rand()%16;
                                    int blockr;
                                    if (rand()%10==0) blockr=95;
                                    else blockr=251;
                                    float blob1=(float)((rand()%70)+5)/10;
                                    float blob2=(float)((rand()%70)+5)/10;
                                    float blob3=(float)((rand()%70)+5)/10;
                                    float blob4=(float)((rand()%70)+5)/10;
                                    float blob5=(float)((rand()%70)+5)/10;
                                    float blob6=(float)((rand()%70)+5)/10;
                                    for (int xc=(int)-s; xc<(int)(s); xc++) {
                                        for (int zc=(int)-s; zc<(int)(s); zc++) {
                                            toggle2();
                                            for (int yc=(int)-s; yc<(int)(s); yc++) {
                                                float some1;
                                                some1=sin(sin((xx+xr+xc)/15)*2+sin((zz+zr+zc)/9.32)*2)*4;
                                                float some2;
                                                some2=sin(sin((xx+xr+xc)/10.23)*2+sin((zz+zr+zc)/11.32)*2)*4;
                                                float some3;
                                                some3=sin(sin((xx+xr+xc)/5)*2+sin((zz+zr+zc)/5.32)*2)*4;
                                                float some4;
                                                some4=sin(sin((xx+xr+xc)/6.23)*2+sin((zz+zr+zc)/4.32)*2)*4;
                                                int flow;
                                                flow = (   sin((xx+xr+xc)/(31.23+some1) + sin((zz+zr+zc)/43.75)/3 )  +  sin((zz+zr+zc)/(4.75+some2) + sin((xx+xr+xc)/34.87)/3.2  )  )*5+10;
                                                flow+= (sin((xx+xr+xc)/(34.23+some1/20) + sin((zz+zr+zc)/47.75)/2 )+sin((zz+zr+zc)/(26.75+some2/20) + sin((xx+xr+xc)/45.87)/3 ))*1.25+2.5;
                                                flow+= (   sin((xx+xr+xc)/(13.23+some1*2) + sin((zz+zr+zc)/25.75)/3 )  +  sin((zz+zr+zc)/(34.75+some2*3) + sin((xx+xr+xc)/47.87)/3.2  )  )*15+30;

                                                int r;
                                                r=(int)( ( ( sin(((float)(zz+zr+zc)/8+(float)(xx+xr+xc)/7+(yc+yr)/3+some1)/30) +sin(flow/33-(float)(yc+yr)/26.66) ) + 2 ) * 60 ) + rand()%(int)(15);
                                                int g;
                                                g=(int)( ( ( sin(((float)(yc+yr)/5+(float)(xx+xr+xc)/4+(float)(zz+zr+zc)/7+some1)/29) + sin(flow/74+(float)(yc+yr)/23.33) ) + 2 ) * 60 ) + rand()%(int)(15);
                                                int b;
                                                b=(int)( ( ( sin(((float)(zz+zr+zc)/4+(float)(xx+xr+xc)/5+(float)(yc+yr)/4.5+some1)/13) + sin(flow/64+(float)(yc+yr)/20) ) + 2 ) * 60 ) + rand()%(int)(15);

                                                if ( sqrt(
                                                          ((float)xc+some3/(s/blob1))*((float)xc+some4/(0.5*s/blob2)) +
                                                          ((float)zc+some4/(s/blob4))*((float)zc+some3/(0.5*s/blob3)) +
                                                          ((float)yc+(some3+some2)/(s/blob5) )*((float)yc+(some1+some4)/(0.5*s/blob6))
                                                          )  < (s)
                                                    ) {
                                                        if (in_region(xr+xc, zr+zc, yr+yc, 0, 0, 11, xl , zl , yl-6))
                                                            AX[xr+xc][zr+zc][yr+yc]=BlockInfo(blockr, 0, ret_color(r,g,b),0 );
                                                }
                                            }
                                        }
                                    }
                                }
                                int red=ret_color(255,0,0);
                                int white=ret_color(255,255,255);
                                if (leuk==leuk_max) {
                                    pixel = (c/(3));
                                    for (int y = 0; y < yl; y++) {
                                        if (y==7 || y==0) {
                                            AY[y] = BlockInfo(7, 0, 0 );
                                        } else if (y==8) {
                                            if ( pixel!=0 && (((int)xx+3)%5)==0 && (((int)zz+3)%5)==0 ) {
                                                AY[y] = BlockInfo(89, 0, 0, 0 );
                                            } else if (col.r==254) {
                                                AY[y] = BlockInfo(251, 0, red,0 );
                                            } else {
                                                AY[y] = BlockInfo(251, 0, white,0 );
                                            }
                                        } else if (y==9) {
                                            if ( pixel!=0 && (((int)xx+3)%5)==0 && (((int)zz+3)%5)==0 ) {
    //                                            AY[y] = BlockInfo(171, 0, 4, 0 );
                                            } else {
                                                if (pixel==0) AY[y] = BlockInfo(251, 0, white,0 );
                                            }
                                        } else if (y==10) {
                                            if (pixel==0) {
                                                AY[y] = BlockInfo(95, 0, ret_color(col_extra.r,col_extra.g,col_extra.b),0 );
                                            }
                                        }
                                    }
                                }
                            }
                        }


                        printf(" Hollow:\b\b\b\b\b\b\b\b");
                        if (!fast_build)
                        for (int x = 0; x < 512; x++) {
                            xx=x+chunk_offsetx*16;
                            BlockInfo** AZ=AX[x];
                            for (int z = 0; z < 512; z++) {
                                zz=z+chunk_offsetz*16;
                                BlockInfo* AY=AZ[z];
                                toggle2();
                                for (int y = 10; y < yl; y++) {
                                    if (AY[y].id!=0) {
                                        if ( ((rand()%300000)>1) && y>0 && y<255 && x>0 && x<511 & z>0 && z<511) {
//                                        if ( ((rand()%300000)>1) && y>0 && y<255 && x>0 && x<511 & z>1 && z<511) {
                                            if (  (
                                                    (AX[x-1][z-1][y-1].id!=0) && (AX[x+0][z-1][y-1].id!=0) && (AX[x+1][z-1][y-1].id!=0) &&
                                                    (AX[x-1][z+0][y-1].id!=0) && (AX[x+0][z+0][y-1].id!=0) && (AX[x+1][z+0][y-1].id!=0) &&
                                                    (AX[x-1][z+1][y-1].id!=0) && (AX[x+0][z+1][y-1].id!=0) && (AX[x+1][z+1][y-1].id!=0) &&
                                                    (AX[x-1][z-1][y+0].id!=0) && (AX[x+0][z-1][y+0].id!=0) && (AX[x+1][z-1][y+0].id!=0) &&
                                                    (AX[x-1][z+0][y+0].id!=0) && (AX[x+0][z+0][y+0].id!=0) && (AX[x+1][z+0][y+0].id!=0) &&
                                                    (AX[x-1][z+1][y+0].id!=0) && (AX[x+0][z+1][y+0].id!=0) && (AX[x+1][z+1][y+0].id!=0) &&
                                                    (AX[x-1][z-1][y+1].id!=0) && (AX[x+0][z-1][y+1].id!=0) && (AX[x+1][z-1][y+1].id!=0) &&
                                                    (AX[x-1][z+0][y+1].id!=0) && (AX[x+0][z+0][y+1].id!=0) && (AX[x+1][z+0][y+1].id!=0) &&
                                                    (AX[x-1][z+1][y+1].id!=0) && (AX[x+0][z+1][y+1].id!=0) && (AX[x+1][z+1][y+1].id!=0)

                                             ) ) {
                                                    AX[x][z][y].id = 255;

                                             }
                                        }
                                    }
                                }
                            }
                        }

                        for (int x = 0; x < 512; x++) {
                            xx=x+chunk_offsetx*16;
                            BlockInfo** AZ=AX[x];
                            for (int z = 0; z < 512; z++) {
                                zz=z+chunk_offsetz*16;
                                BlockInfo* AY=AZ[z];
                                toggle2();
                                for (int y = 0; y < yl; y++) {
                                    if (  AY[y].id==255) {
                                        AY[y] = BlockInfo();
                                    }
                                }
                            }
                        }
                    }//leuk


//solid
                    printf(" Solid:\b\b\b\b\b\b\b");
                    if (!fast_build)
                    for (int x = 0; x < xl; x++) {
                        xx=x+chunk_offsetx*16;
                        BlockInfo** AZ=AX[x];
                        for (int z = 0; z < zl; z++) {
                            zz=z+chunk_offsetz*16;
                            BlockInfo* AY=AZ[z];
                            int r, g, b;
                            float pixel;

                            float c;
                            sf::Color col;
                            sf::Color col_extra;
                            col=image_plot_org.getPixel(x+5,z+5);
                            col_extra=image_plot_extra.getPixel(x,z);

                            toggle2();

                            c=(col.r+col.b+col.g);
                            pixel = (c/(3));
                            if (col.a==0) pixel=0;

                            if (rand()%20<4 && rand()%512<(250+(int)(mix1)) && rand()%512<35 && rand()%256<25)  {
                                int size_globe=( sin( sin(xx/64.8)*3.1415 + sin(zz/88.7)*3.1415 ) + 1 )*(100+mix4);
                                float s=(float)(rand()%(size_globe+30))/11;
                                int xr=rand()%(512);
                                int zr=rand()%(512);
                                int yr;
                                yr=90+rand()%25;

                                int colr=rand()%16;
                                int blockr;
                                if (rand()%16==0) blockr=95;
                                else blockr=251;
                                float blob1=(float)((rand()%70)+5)/10;
                                float blob2=(float)((rand()%70)+5)/10;
                                float blob3=(float)((rand()%70)+5)/10;
                                float blob4=(float)((rand()%70)+5)/10;
                                float blob5=(float)((rand()%70)+5)/10;
                                float blob6=(float)((rand()%70)+5)/10;
                                for (int xc=(int)-s; xc<(int)(s); xc++) {
                                    for (int zc=(int)-s; zc<(int)(s); zc++) {
                                        toggle2();
                                        for (int yc=(int)-s; yc<(int)(s); yc++) {
                                            float some1;
                                            some1=sin(sin((xx+xr+xc)/15)*2+sin((zz+zr+zc)/9.32)*2)*4;
                                            float some2;
                                            some2=sin(sin((xx+xr+xc)/10.23)*2+sin((zz+zr+zc)/11.32)*2)*4;
                                            float some3;
                                            some3=sin(sin((xx+xr+xc)/5)*2+sin((zz+zr+zc)/5.32)*2)*4;
                                            float some4;
                                            some4=sin(sin((xx+xr+xc)/6.23)*2+sin((zz+zr+zc)/4.32)*2)*4;
                                            int flow;
                                            flow = (   sin((xx+xr+xc)/(31.23+some1) + sin((zz+zr+zc)/43.75)/3 )  +  sin((zz+zr+zc)/(4.75+some2) + sin((xx+xr+xc)/34.87)/3.2  )  )*5+10;
                                            flow+= (sin((xx+xr+xc)/(34.23+some1/20) + sin((zz+zr+zc)/47.75)/2 )+sin((zz+zr+zc)/(26.75+some2/20) + sin((xx+xr+xc)/45.87)/3 ))*1.25+2.5;
                                            flow+= (   sin((xx+xr+xc)/(13.23+some1*2) + sin((zz+zr+zc)/25.75)/3 )  +  sin((zz+zr+zc)/(34.75+some2*3) + sin((xx+xr+xc)/47.87)/3.2  )  )*15+30;

                                            int r;
                                            r=(int)( ( ( sin(((float)(zz+zr+zc)/8+(float)(xx+xr+xc)/7+(yc+yr)/3+some1)/30) +sin(flow/33-(float)(yc+yr)/26.66) ) + 2 ) * 60 ) + rand()%(int)(15);
                                            int g;
                                            g=(int)( ( ( sin(((float)(yc+yr)/5+(float)(xx+xr+xc)/4+(float)(zz+zr+zc)/7+some1)/29) + sin(flow/74+(float)(yc+yr)/23.33) ) + 2 ) * 60 ) + rand()%(int)(15);
                                            int b;
                                            b=(int)( ( ( sin(((float)(zz+zr+zc)/4+(float)(xx+xr+xc)/5+(float)(yc+yr)/4.5+some1)/13) + sin(flow/64+(float)(yc+yr)/20) ) + 2 ) * 60 ) + rand()%(int)(15);

                                            if ( sqrt(
                                                      ((float)xc+some3/(s/blob1))*((float)xc+some4/(0.5*s/blob2)) +
                                                      ((float)zc+some4/(s/blob4))*((float)zc+some3/(0.5*s/blob3)) +
                                                      ((float)yc+(some3+some2)/(s/blob5) )*((float)yc+(some1+some4)/(0.5*s/blob6))
                                                      )  < (s)
                                                ) {
                                                    if (in_region(xr+xc, zr+zc, yr+yc, 0, 0, 11, xl , zl , yl-6))
                                                        AX[xr+xc][zr+zc][yr+yc]=BlockInfo(blockr, 0, ret_color(r,g,b),0 );
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }



    //holes
                    printf(" Holes:\b\b\b\b\b\b\b");
                    for (int x = 0; x < xl; x++) {
                        xx=x+chunk_offsetx*16;
                        BlockInfo** AZ=AX[x];
                        for (int z = 0; z < zl; z++) {
                            zz=z+chunk_offsetz*16;
                            BlockInfo* AY=AZ[z];
                            toggle2();
                            if (rand()%512<(100+mix5) && rand()%512<50 && rand()%256<25)  {
                                int size_globe=( sin( sin(xx/34.8)*3.1415 + sin(zz/45.7)*3.1415 ) + 1 )*(145+mix6)+10;
                                float s=(float)(rand()%size_globe+30)/11;

                                int xr=rand()%(512);
                                int zr=rand()%(512);
                                int yr=rand()%(256);

    //                            int xr=rand()%(511-(int)(s*2)-2);
    //                            int zr=rand()%(511-(int)(s*2)-2);
    //                            int yr=35+rand()%(210-(int)(s*2)-2);

                                for (int xc=(int)-s; xc<(int)(s); xc++) {
                                    for (int zc=(int)-s; zc<(int)(s); zc++) {
                                        toggle2();
                                        for (int yc=(int)-s; yc<(int)(s); yc++) {
                                            if ( sqrt(
                                                      ((float)xc)*((float)xc) +
                                                      ((float)zc)*((float)zc) +
                                                      ((float)yc)*((float)yc)
                                                      )  < (s) )
                                             {
                                                if (in_region(xr+xc, zr+zc, yr+yc, 0, 0, 11, xl , zl , yl-6))
                                                    AX[xr+xc][zr+zc][yr+yc]=BlockInfo();
                                            }
                                        }
                                    }
                                }
    //                            if (in_region(xr, zr, yr, 0, 0, 5, xl , zl , yl-6))
    //                                AX[xr][zr][yr]=BlockInfo(50,0,0,0);
                            }
                        }
                    }

                    printf(" Holes2:\b\b\b\b\b\b\b");
                    for (int x = 0; x < xl; x++) {
                        xx=x+chunk_offsetx*16;
                        BlockInfo** AZ=AX[x];
                        for (int z = 0; z < zl; z++) {
                            zz=z+chunk_offsetz*16;
                            BlockInfo* AY=AZ[z];
                            toggle2();
                            if (rand()%512<(250+mix5+mix3) && rand()%512<50 && rand()%256<25)  {
                                int size_globe=( sin( sin(xx/4.8)*3.1415 + sin(zz/5.7)*3.1415 ) + 1 )*(75+mix6-mix3)+10;
                                float s=(float)(rand()%size_globe+20)/11;

                                int xr=rand()%(512);
                                int zr=rand()%(512);
                                int yr=rand()%(256);

    //                            int xr=rand()%(511-(int)(s*2)-2);
    //                            int zr=rand()%(511-(int)(s*2)-2);
    //                            int yr=35+rand()%(210-(int)(s*2)-2);

                                for (int xc=(int)-s; xc<(int)(s); xc++) {
                                    for (int zc=(int)-s; zc<(int)(s); zc++) {
                                        toggle2();
                                        for (int yc=(int)-s; yc<(int)(s); yc++) {
                                            if ( sqrt(
                                                      ((float)xc)*((float)xc) +
                                                      ((float)zc)*((float)zc) +
                                                      ((float)yc)*((float)yc)
                                                      )  < (s) )
                                             {
                                                if (in_region(xr+xc, zr+zc, yr+yc, 0, 0, 11, xl , zl , yl-6))
                                                    AX[xr+xc][zr+zc][yr+yc]=BlockInfo();
                                            }
                                        }
                                    }
                                }
    //                            if (in_region(xr, zr, yr, 0, 0, 5, xl , zl , yl-6))
    //                                AX[xr][zr][yr]=BlockInfo(50,0,0,0);
                            }
                        }
                    }

                    int xr=255;
                    int zr=255;
                    int yr=114;

                    printf(" Aqua:\b\b\b\b\b\b");
                    for (int x = 0; x < xl; x++) {
                        xx=x+chunk_offsetx*16;
                        BlockInfo** AZ=AX[x];
                        for (int z = 0; z < zl; z++) {
                            zz=z+chunk_offsetz*16;
                            BlockInfo* AY=AZ[z];
                            toggle2();

                            if (rand()%20<4 && rand()%512<(100+(int)(mix1+mix2-mix3)) && rand()%512<90 && rand()%256<35)  {
                                xr=(xr+rand()%81-40)%512;
                                zr=(zr+rand()%81-40)%512;
                                if (yr>130) yr=(yr+rand()%61-35)%256;
                                else if (yr<90) yr=(yr+rand()%61-25)%256;
                                else yr=(yr+rand()%61-30)%256;
                                if (!rand()%20) {
                                    xr=511-xr;
                                    zr=511-zr;
                                    yr=255-yr;
                                } else if (xr>462 || xr<50 || zr>462 || zr < 50) {
                                    xr=255;
                                    zr=255;
                                    yr=114;
                                }

//                                int size_globe=( sin( sin(xx/34.8)*3.1415 + sin(zz/45.7)*3.1415 ) + 1 )*(145+mix6)+10;
//                                float s=(float)(rand()%size_globe+10)/11;
                                int size_globe=( sin( sin(xx/39.8)*3.1415 + sin(zz/33.7)*3.1415 ) + 1 )*(350-mix1-mix2+mix3)+10;
                                float sx=(float)(rand()%size_globe+rand()%size_globe+80)/21;
                                size_globe=( sin( sin(xx/44.8)*3.1415 + sin(zz/55.7)*3.1415 ) + 1 )*(350-mix2-mix3+mix3)+10;
                                float sz=(float)(rand()%size_globe+rand()%size_globe+80)/21;
                                size_globe=( sin( sin(xx/24.8)*3.1415 + sin(zz/25.7)*3.1415 ) + 1 )*(350-mix3-mix1+mix3)+10;
                                float sy=(float)(rand()%size_globe+rand()%size_globe+80)/21;
                                if (-sy+yr < 12) yr=sy+12;
                                if (sy+yr >250) yr=250-sy;

//                                int xr=rand()%(511-(int)(s*2)-2);
//                                int zr=rand()%(511-(int)(s*2)-2);
//                                int yr=20+rand()%(210   -(int)(s*2)-2);


                                int colr=rand()%16;
                                int blockr;
                                    if (rand()%15<=10) blockr=95;
                                else blockr=251;
                                int color_one=rand()%16;
                                if (blockr==95) color_one=0;
                                float blob1=(float)((rand()%70)+15)/10;
                                float blob2=(float)((rand()%70)+15)/10;
                                float blob3=(float)((rand()%70)+15)/10;
                                float blob4=(float)((rand()%70)+15)/10;
                                float blob5=(float)((rand()%70)+15)/10;
                                float blob6=(float)((rand()%70)+15)/10;
                                for (int xc=(int)-sx; xc<(int)(sx); xc++) {
                                    for (int zc=(int)-sz; zc<(int)(sz); zc++) {
                                        toggle2();
                                        for (int yc=(int)-sy; yc<(int)(sy); yc++) {
                                            float some1;
                                            float some2;
                                            int r;
                                            int g;
                                            int b;
                                            int one_col=1;

                                            if ((rand()%2==1 && blockr==251) || rand()%10==0) one_col=0;

                                            some1=sin(sin((xx+xr+xc)/10)*2+sin((zz+zr+zc)/5.32)*2)*4;
                                            some2=sin(sin((xx+xr+xc)/15.23)*2+sin((zz+zr+zc)/13.32)*2)*4;
                                            int flow;
                                            flow = (   sin((xx+xr+xc)/(83.23+some1) + sin((zz+zr+zc)/73.75)/3 )  +  sin((zz+zr+zc)/(19.75+some2) + sin((xx+xr+xc)/34.87)/7.2  )  )*5+10;
                                            flow+= (sin((xx+xr+xc)/(94.23+some1/20) + sin((zz+zr+zc)/57.75)/2 )+sin((zz+zr+zc)/(26.75+some2/20) + sin((xx+xr+xc)/45.87)/5 ))*1.25+2.5;
                                            flow+= (   sin((xx+xr+xc)/(62.23+some1*2) + sin((zz+zr+zc)/54.75)/3 )  +  sin((zz+zr+zc)/(64.75+some2*3) + sin((xx+xr+xc)/47.87)/6.2  )  )*15+30;

                                            r=(int)( ( ( sin(((float)(zz+zr+zc)/18+(float)(xx+xr+xc)/7+(yc+yr)/6+some1)/30) +sin(flow/33-(float)(yc+yr)/36.66) ) + 2 ) * 60 ) + rand()%(int)(15);
                                            g=(int)( ( ( sin(((float)(yc+yr)/14+(float)(xx+xr+xc)/13+(float)(zz+zr+zc)/17+some1)/49) + sin(flow/74+(float)(yc+yr)/23.33) ) + 2 ) * 60 ) + rand()%(int)(15);
                                            b=(int)( ( ( sin(((float)(zz+zr+zc)/12+(float)(xx+xr+xc)/14+(float)(yc+yr)/12.5+some1)/53) + sin(flow/44+(float)(yc+yr)/30) ) + 2 ) * 60 ) + rand()%(int)(15);

                                            if ( xc==(int)-sx || xc==(int)sx-1 || zc==(int)-sz || zc==(int)sz-1 || yc==(int)-sy || yc==(int)sy
                                                ) {
                                                if (in_region(xr+xc, zr+zc, yr+yc, 0, 0, 11, xl , zl , yl-6)) {
                                                    if (AX[xr+xc][zr+zc][yr+yc].id==0) {
                                                        if (one_col) {
                                                            if ( yc==(int)sy-1 || (xc==(int)-sx && zc==(int)-sz) ||  (xc==(int)sx-1 && zc==(int)-sz) ||  (xc==(int)-sx && zc==(int)sz-1) ||  (xc==(int)sx-1 && zc==(int)sz-1) || yc==(int)-sy) {
                                                                AX[xr+xc][zr+zc][yr+yc]=BlockInfo(251, 0,  ret_color(r,g,b),0 );
                                                            } else {
                                                                AX[xr+xc][zr+zc][yr+yc]=BlockInfo(blockr, 0, ret_color(r,g,b),0 );
                                                            }
                                                        }
                                                        else {
                                                            if ( yc==(int)sy-1 || (xc==(int)-sx && zc==(int)-sz) ||  (xc==(int)sx-1 && zc==(int)-sz) ||  (xc==(int)-sx && zc==(int)sz-1) ||  (xc==(int)sx-1 && zc==(int)sz-1) || yc==(int)-sy) {
                                                                AX[xr+xc][zr+zc][yr+yc]=BlockInfo(251, 0,  ret_color(r,g,b),0 );
                                                            }
                                                            else {
                                                                AX[xr+xc][zr+zc][yr+yc]=BlockInfo(blockr, 0, color_one,0 );
                                                            }
                                                        }
                                                    }
                                                }
                                            } else if (yc<(int)sy-1) {
                                                if (in_region(xr+xc, zr+zc, yr+yc, 0, 0, 11, xl , zl , yl-6)) {
                                                    if ((rand()%10)==-1) {
                                                        int hop=AX[xr+xc][zr+zc][yr+yc-1].id;
                                                        if (hop==95 || hop==251 || hop==89) {
                                                            int item=rand()%5;
                                                            if (item==0) AX[xr+xc][zr+zc][yr+yc]=BlockInfo(393-256, 1, 0, 0 );
                                                            else AX[xr+xc][zr+zc][yr+yc]=BlockInfo(386-256, 1, rand()%5, 0 );
                                                        } else {
                                                            if (AX[xr+xc][zr+zc][yr+yc].id==0) AX[xr+xc][zr+zc][yr+yc]=BlockInfo(8, 0, 0, 0 );
                                                        }
                                                    } else {
                                                        if (AX[xr+xc][zr+zc][yr+yc].id==0) {
                                                            AX[xr+xc][zr+zc][yr+yc]=BlockInfo(8, 0, 0, 0 );
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }

                    printf(" Glass:\b\b\b\b\b\b\b");
                    for (int x = 1; x < 511; x++) {
                        for (int z = 1; z < 511; z++) {
                            toggle2();
                            for (int y = 1; y < 255; y++) {
                                if  (!(AX[x][z][y].id==8 || AX[x][z][y].id==255)) {
                                    if      ( (AX[x  ][z  ][y-1].id==8 || AX[x  ][z  ][y-1].id==255) && (AX[x  ][z  ][y+1].id==8 || AX[x  ][z  ][y+1].id==255) ) { AX[x][z][y].id = 255; }
                                    else if ( (AX[x  ][z-1][y  ].id==8 || AX[x  ][z-1][y  ].id==255) && (AX[x  ][z+1][y  ].id==8 || AX[x  ][z+1][y  ].id==255) ) { AX[x][z][y].id = 255; }
                                    else if ( (AX[x-1][z  ][y  ].id==8 || AX[x-1][z  ][y  ].id==255) && (AX[x+1][z  ][y  ].id==8 || AX[x+1][z  ][y  ].id==255) ) { AX[x][z][y].id = 255; }
                                }
                            }
                        }
                    }

                    for (int x = 0; x < 512; x++) {
                        for (int z = 0; z < 512; z++) {
                            toggle2();
                            for (int y = 0; y < yl; y++) {
                                if (  AX[x][z][y].id==255) {
                                    AX[x][z][y] = BlockInfo(8, 0, 0, 0 );
                                }
                            }
                        }
                    }

                    ceil_heigher=9;
                    printf(" Walls:\b\b\b\b\b\b\b");
                    int train_height=5;
                    int yellow=ret_color(255,255,0);
                    int white=ret_color(255,255,255);
                    int red=ret_color(255,0,0);
                    int lightred=ret_color(255,64,32);
                    int darkred=ret_color(128,0,0);
                    int black=ret_color(0,0,0);
                    float darkblue=ret_color(0,0,128);
//                    if (!fast_build)
                    for (int x = 0; x < xl; x++) {
                        BlockInfo** AZ=AX[x];
                        for (int z = 0; z < zl; z++) {
                            BlockInfo* AY=AZ[z];
                            float pixel;
                            float pixel_org;

                            float c;
                            sf::Color col;
                            sf::Color col_org;
                            col=image_plot.getPixel(x+5,z+5);
                            col_org=image_plot_org.getPixel(x+5,z+5);

                            c=(col.r+col.b+col.g);
                            if (col.a==0) pixel=0;
                            pixel = (c/(3));

                            c=(col_org.r+col_org.b+col_org.g);
                            if (col_org.a==0) pixel_org=0;
                            pixel_org = (c/(3));
//jojo
                            for (int y = 0; y < 256; y++) {
                                if (  ( (x==0 || z==0 || x==511 || z==511 || x==256 || z==256 || x==255 || z==255 ) && y<248 && y>10 ) || y==247 || (y==11 && pixel_org!=0) ) {
                                    if (!( (pixel!=0) && y>=108-2 && y<116+2+ceil_heigher)) {
                                        if ( ! (AY[y].id==66 || AY[y].id==27 || AY[y-1].id==66 || AY[y-1].id==27) ) {
                                            sf::Color col;

                                            if (x==0) {
                                                col=image_plot_extra.getPixel(z,255-y);
                                            } else if (z==0) {
                                                col=image_plot_extra.getPixel(x,255-y);
                                            } else if (x==511 || x==255) {
                                                col=image_plot_extra.getPixel(511-z,255-y);
                                            } else if (z==511 || z==255) {
                                                col=image_plot_extra.getPixel(511-x,255-y);
                                            } else if (x==256) {
                                                col=image_plot_extra.getPixel(z,255-y);
                                            } else if (z==256) {
                                                col=image_plot_extra.getPixel(x,255-y);
                                            } else if (y==4) {
                                                col=image_plot_extra.getPixel(x,z);
                                            } else if (y==247) {
                                                col=image_plot_extra.getPixel(x,z);
                                            } else col=sf::Color(255,255,0);
                                            int r=col.r + (rand()%11)-5; if (r<0) r=0; if (r>255) r=255;
                                            int g=col.g + (rand()%11)-5; if (g<0) g=0; if (g>255) g=255;
                                            int b=col.b + (rand()%11)-5; if (b<0) b=0; if (b>255) b=255;
                                            AY[y] = BlockInfo(251, 0, ret_color(r,g,b),0 );
                                        }
                                    }
                                }
                            }
                        }
                    }

                    printf(" Light:\b\b\b\b\b\b\b");
                    for (int x = 0; x < 512; x++) {
                        xx=x+chunk_offsetx*16;
                        BlockInfo** AZ=AX[x];
                        for (int z = 0; z < 512; z++) {
                            zz=z+chunk_offsetz*16;
                            BlockInfo* AY=AZ[z];
                            toggle2();
                            float hop=0.0 ;
                            float pixel;
                            float c;
                            float c1,c2,c3,c4;
                            float c5,c6,c7,c8;
                            c1=1.0;
                            sf::Color col;
                            col=image_plot_org.getPixel(x+5,z+5);
                            c=(col.r+col.b+col.g);
                            pixel=c/3;
                            if (col.a==0) pixel=0;
                            for (int y = yl-1; y >=0; y--) {
                                if (  (rand()%4)==0 && AY[y].id!=0 && !(y>=108 && y<115+2+ceil_heigher) && y<248 && y>12 && ( (rand()%15)==0 || AY[y].id!=8 )  ) {
                                    float some1;
                                    float some2;
                                    float flow;
                                    some1=sin(sin(((float)xx)/159.89)*2+sin(((float)zz)/171.32)*2);
                                    some2=sin(sin(((float)xx)/165.23)*2+sin(((float)zz)/157.32)*2);
                                    flow = (   sin(((float)xx)/( 98.23+some1*20)  + sin(((float)zz)/(133.75 +some2*14) )/3 )  +  sin(((float)zz)/(154.75+some2*6 )    + sin(((float)xx)/(114.87+some1*4  ) )/3.2  )  );
                                    flow+= (   sin(((float)xx)/(154.23+some1*17)  + sin(((float)zz)/(87.75  +some2*17) )/2 )  +  sin(((float)zz)/(116.75+some2*5 )    + sin(((float)xx)/(145.87+some1*5  ) )/3    )  );
                                    flow+= (   sin(((float)xx)/(112.23+some1*15)  + sin(((float)zz)/(52.75  +some2*19) )/3 )  +  sin(((float)zz)/(144.75+some2*4 )    + sin(((float)xx)/(197.87+some1*6  ) )/3.2  )  );
                                    hop = sin(
                                                    sin( (float)zz/(  250  + sin((float)xx/76  + (float)y/69   )*(75+flow*5+some1*5)  )  )*(3.1415 +flow/5+some2/5) +
                                                    sin( (float)xx/(  250  + sin((float)zz/98  + (float)y/78   )*(65+flow*7+some2*3)  )  )*(3.1415 +flow/7+some1/3) +
                                                    sin( (float)y /(  150  + sin((float)zz/90 + (float)xx/75  )*(42+flow*6+some1*4)  )  )*(3.1415 +flow/6+some2/4)
                                                  );
                                    if  (
                                            ((int)(hop*12*8) ==    4*8 +rand()%3) ||
                                            ((int)(hop*12*8) ==    8*8 +rand()%3) ||
                                            ((int)(hop*12*8) ==   -8*8 +rand()%3) ||
                                            ((int)(hop*12*8) ==   -4*8 +rand()%3) ||
                                            ((int)(hop*12*8) ==         rand()%3) ||
                                            (rand()%100)==0
                                        )

                                    {
                                        if (in_region(x, z, y, 0, 0, 11, xl , zl , yl-5)) {
                                            int c=AY[y].data;
                                            if (AY[y].id==8) c=rand()%16;
                                            AY[y]=BlockInfo(89, 0, 0, 0);
                                            for (int xxx=-1; xxx<2; xxx++) {
                                                for (int zzz=-1; zzz<2; zzz++) {
                                                    for (int yyy=-1; yyy<2; yyy++) {
                                                        if (!(xxx==0 && yyy==0 && zzz==0)) {
                                                            if (in_region(x+xxx, z+zzz, y+yyy, 0, 0, 11, xl , zl , yl-5)) {
                                                                if (AX[x+xxx][z+zzz][y+yyy].id==0 || AX[x+xxx][z+zzz][y+yyy].id==8) {
                                                                    if ( ! (AX[x+xxx][z+zzz][y+yyy].id==66 || AX[x+xxx][z+zzz][y+yyy].id==27 || AX[x+xxx][z+zzz][y+yyy-1].id==66 || AX[x+xxx][z+zzz][y+yyy-1].id==27) ) {
                                                                         AX[x+xxx][z+zzz][y+yyy]=BlockInfo(95, 0, c, 0);
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    } else {
                                        some1=sin(sin(((float)xx)/169.89)*2+sin(((float)zz)/161.32)*2);
                                        some2=sin(sin(((float)xx)/155.23)*2+sin(((float)zz)/187.32)*2);
                                        flow = (   sin(((float)xx)/(128.23+some1*23)  + sin(((float)zz)/(89.75   +some2*17) )/2 )  +  sin(((float)zz)/(144.75+some2*5 )    + sin(((float)xx)/(134.87+some1*6  ) )/2.9  )  );
                                        flow+= (   sin(((float)xx)/( 94.23+some1*11)  + sin(((float)zz)/(122.75  +some2*15) )/3 )  +  sin(((float)zz)/(126.75+some2*4 )    + sin(((float)xx)/(125.87+some1*5  ) )/3.4    )  );
                                        flow+= (   sin(((float)xx)/(142.23+some1*12)  + sin(((float)zz)/(76.75   +some2*14) )/3 )  +  sin(((float)zz)/(114.75+some2*3 )    + sin(((float)xx)/(137.87+some1*4  ) )/3.2  )  );
                                        hop = sin(
                                                        sin( (float)zz/(  250  + sin((float)xx/86  + (float)y/111 )*(79+flow*6+some1*6)  )  )*(3.1415 +flow/6+some2/7) +
                                                        sin( (float)xx/(  250  + sin((float)zz/78  + (float)y/123 )*(69+flow*5+some2*4)  )  )*(3.1415 +flow/7+some1/6) +
                                                        sin( (float)y /(  150  + sin((float)zz/77 + (float)xx/88  )*(62+flow*7+some1*8)  )  )*(3.1415 +flow/9+some2/5)
                                                      );
                                        if  (
                                                ((int)(hop*12*8) ==    4*8 +rand()%3) ||
                                                ((int)(hop*12*8) ==   -8*8 +rand()%3) ||
                                                ((int)(hop*12*8) ==    8*8 +rand()%3) ||
                                                ((int)(hop*12*8) ==   -4*8 +rand()%3) ||
                                                ((int)(hop*12*8) ==         rand()%3) ||
                                                (rand()%100)==0
                                            )
                                        {
                                            if (in_region(x, z, y, 0, 0, 11, xl , zl , yl-5)) {
                                                int c=AY[y].data;
                                                AY[y]=BlockInfo(89, 0, 0, 0);
                                                for (int xxx=-1; xxx<2; xxx++) {
                                                    for (int zzz=-1; zzz<2; zzz++) {
                                                        for (int yyy=-1; yyy<2; yyy++) {
                                                            if (!(xxx==0 && yyy==0 && zzz==0)) {
                                                                if (in_region(x+xxx, z+zzz, y+yyy, 0, 0, 11, xl , zl , yl-5)) {
                                                                    if (AX[x+xxx][z+zzz][y+yyy].id==0 || AX[x+xxx][z+zzz][y+yyy].id==8) {
                                                                        if ( ! (AX[x+xxx][z+zzz][y+yyy].id==66 || AX[x+xxx][z+zzz][y+yyy].id==27 || AX[x+xxx][z+zzz][y+yyy-1].id==66 || AX[x+xxx][z+zzz][y+yyy-1].id==27) ) {
                                                                            AX[x+xxx][z+zzz][y+yyy]=BlockInfo(95, 0, c, 0);
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                                if (AY[y].id!=0) num_blocks++;
                            }
                        }
                    }

                    printf(" Maze:\b\b\b\b\b\b");
//                    if (!fast_build)
                    for (int x = 0; x < xl; x++) {
                        xx=x+chunk_offsetx*16;
                        BlockInfo** AZ=AX[x];
                        for (int z = 0; z < zl; z++) {
                            zz=z+chunk_offsetz*16;
                            BlockInfo* AY=AZ[z];
                            int r, g, b;
                            float pixel;
                            float pixel_org;

                            float c;
                            sf::Color col;
                            sf::Color col_org;
                            sf::Color col_extra;
                            col=image_plot.getPixel(x+5,z+5);
                            col_org=image_plot_org.getPixel(x+5,z+5);
                            col_extra=image_plot_extra.getPixel(x,z);

                            c=(col.r+col.b+col.g);
                            pixel = (c/(3));
                            if (col.a==0) pixel=0;

                            c=(col_org.r+col_org.b+col_org.g);
                            pixel_org = (c/(3));
                            if (col_org.a==0) pixel_org=0;

                            int x_off=1;
                            int z_off=1;

//                            if (!(x>0 && x<511)) {
//                                x_off=0;
//                            }
//                            if (!(z>0 && z<511)) {
//                                z_off=0;
//                            }


                            for (int y = 0; y < 256; y++) {
                                int edge=0;
                                int edge2=0;
                                int edge3=0;
                                int corner2=0;
                                int red2=0;
                                int dir_x=0;
                                int curve=0;
                                int c1;
                                int c2;
                                int c3;
                                int c4;

                                if (y>=108-2 && y<=115+2+ceil_heigher) {
                                    sf::Color col_side1;
                                    sf::Color col_side2;
                                    sf::Color col_side3;
                                    sf::Color col_side4;
                                    col_side1=image_plot.getPixel(x-x_off+5,    z+5);
                                    col_side2=image_plot.getPixel(x+5,          z-z_off+5);
                                    col_side3=image_plot.getPixel(x+x_off+5,    z+5);
                                    col_side4=image_plot.getPixel(x+5,          z+z_off+5);
                                    red2=0;
                                    if ( col.r==254 || (pixel==0 && (col_side1.r==254 || col_side2.r==254 || col_side3.r==254 || col_side4.r==254)) ) red2=1;
                                    c1=(col_side1.r+col_side1.b+col_side1.g);
                                    c2=(col_side2.r+col_side2.b+col_side2.g);
                                    c3=(col_side3.r+col_side3.b+col_side3.g);
                                    c4=(col_side4.r+col_side4.b+col_side4.g);
                                    if (c1==0 || c2==0 || c3==0 || c4==0) edge=1;
                                    dir_x=0;
                                    curve=0;
                                    if (c1!=0 && c3!=0) dir_x=1+8;
                                    if (c2!=0 && c4!=0) dir_x=0+8;
                                    if (c1!=0 && c2!=0 && c3==0 && c4==0) curve=8;
                                    if (c3!=0 && c4!=0 && c1==0 && c2==0) curve=6;
                                    if (c1!=0 && c4!=0 && c2==0 && c3==0) curve=7;
                                    if (c2!=0 && c3!=0 && c1==0 && c4==0) curve=9;
                                    if (edge==0) {
                                        col_side1=image_plot.getPixel(x-x_off+5,    z-z_off+5);
                                        col_side2=image_plot.getPixel(x+x_off+5,    z-z_off+5);
                                        col_side3=image_plot.getPixel(x+x_off+5,    z+z_off+5);
                                        col_side4=image_plot.getPixel(x-x_off+5,    z+z_off+5);
                                        c1=(col_side1.r+col_side1.b+col_side1.g);
                                        c2=(col_side2.r+col_side2.b+col_side2.g);
                                        c3=(col_side3.r+col_side3.b+col_side3.g);
                                        c4=(col_side4.r+col_side4.b+col_side4.g);
                                        if (c1==0 || c2==0 || c3==0 || c4==0) edge=1;
                                        if (c1==0 && c2!=0 && c3!=0 && c4!=0) curve=8;
                                        if (c1!=0 && c2==0 && c3!=0 && c4!=0) curve=9;
                                        if (c1!=0 && c2!=0 && c3==0 && c4!=0) curve=6;
                                        if (c1!=0 && c2!=0 && c3!=0 && c4==0) curve=7;
                                    }
                                    if (curve!=0) corner2=1;
                                }


                                if (/*y==115+2 ||  y==109-2   || y==108-2+train_height || y==109-2+train_height ||*/ y==108-2) {
/*
                                    sf::Color  col_side1=image_plot_org.getPixel(x-x_off+5,    z+5);
                                    sf::Color  col_side2=image_plot_org.getPixel(x+5,          z-z_off+5);
                                    sf::Color  col_side3=image_plot_org.getPixel(x+x_off+5,    z+5);
                                    sf::Color  col_side4=image_plot_org.getPixel(x+5,          z+z_off+5);
                                    c1=(col_side1.r+col_side1.b+col_side1.g);
                                    c2=(col_side2.r+col_side2.b+col_side2.g);
                                    c3=(col_side3.r+col_side3.b+col_side3.g);
                                    c4=(col_side4.r+col_side4.b+col_side4.g);
                                    if (c1==0 || c2==0 || c3==0 || c4==0) edge3=1;
                                    if (edge3==0) {
                                        col_side1=image_plot_org.getPixel(x-x_off+5,    z-z_off+5);
                                        col_side2=image_plot_org.getPixel(x+x_off+5,    z-z_off+5);
                                        col_side3=image_plot_org.getPixel(x+x_off+5,    z+z_off+5);
                                        col_side4=image_plot_org.getPixel(x-x_off+5,    z+z_off+5);
                                        c1=(col_side1.r+col_side1.b+col_side1.g);
                                        c2=(col_side2.r+col_side2.b+col_side2.g);
                                        c3=(col_side3.r+col_side3.b+col_side3.g);
                                        c4=(col_side4.r+col_side4.b+col_side4.g);
                                        if (c1==0 || c2==0 || c3==0 || c4==0) edge3=1;
                                    }
*/
                                    sf::Color col_side1=image_plot3.getPixel(x-x_off+5,    z+5);
                                    sf::Color col_side2=image_plot3.getPixel(x+5,          z-z_off+5);
                                    sf::Color col_side3=image_plot3.getPixel(x+x_off+5,    z+5);
                                    sf::Color col_side4=image_plot3.getPixel(x+5,          z+z_off+5);
                                    c1=(col_side1.r+col_side1.b+col_side1.g);
                                    c2=(col_side2.r+col_side2.b+col_side2.g);
                                    c3=(col_side3.r+col_side3.b+col_side3.g);
                                    c4=(col_side4.r+col_side4.b+col_side4.g);
                                    if (c1==0 || c2==0 || c3==0 || c4==0) edge2=1;
                                    dir_x=0;
                                    curve=0;
                                    corner2=0;
                                    if (c1!=0 && c3!=0) dir_x=1+8;
                                    if (c2!=0 && c4!=0) dir_x=0+8;
                                    if (c1!=0 && c2!=0 && c3==0 && c4==0) curve=8;
                                    if (c3!=0 && c4!=0 && c1==0 && c2==0) curve=6;
                                    if (c1!=0 && c4!=0 && c2==0 && c3==0) curve=7;
                                    if (c2!=0 && c3!=0 && c1==0 && c4==0) curve=9;


                                    if (edge2==0) {
                                        col_side1=image_plot3.getPixel(x-x_off+5,    z-z_off+5);
                                        col_side2=image_plot3.getPixel(x+x_off+5,    z-z_off+5);
                                        col_side3=image_plot3.getPixel(x+x_off+5,    z+z_off+5);
                                        col_side4=image_plot3.getPixel(x-x_off+5,    z+z_off+5);
                                        c1=(col_side1.r+col_side1.b+col_side1.g);
                                        c2=(col_side2.r+col_side2.b+col_side2.g);
                                        c3=(col_side3.r+col_side3.b+col_side3.g);
                                        c4=(col_side4.r+col_side4.b+col_side4.g);
                                        if (c1==0 || c2==0 || c3==0 || c4==0) {
                                            edge2=1;
                                        }
                                        if (c1==0 && c2!=0 && c3!=0 && c4!=0) curve=8;
                                        if (c1!=0 && c2==0 && c3!=0 && c4!=0) curve=9;
                                        if (c1!=0 && c2!=0 && c3==0 && c4!=0) curve=6;
                                        if (c1!=0 && c2!=0 && c3!=0 && c4==0) curve=7;
                                    }
                                    if (curve!=0) corner2=1;
                                }


                                if (y>=109-2 && y<115+2+ceil_heigher) {
                                    toggle2();
                                    if (pixel!=0) {
                                        if (edge==1) {
                                            if (red2==1) {
                                                if (AY[y].id==0 || AY[y].id==8) AY[y] = BlockInfo(95, 0, red,0 );
                                            }  else {
                                                if (rand()%30==0) {
                                                    AY[y] = BlockInfo(95, 0, ret_color(rand()%256,rand()%256,rand()%256),0 );
                                                } else {
                                                    if (AY[y].id==0 || AY[y].id==8) AY[y] = BlockInfo(95, 0, white,0 );
                                                }
                                            }
                                        } else {
                                            if ( y==109-2 && ((((int)xx+3)%5)==0 && (((int)zz+3)%5)==0) ) {
                                                AY[y] = BlockInfo(147, 0, 0, 0 );
                                            } else if ( y==109-2 && AY[y].id!=147 && AY[108-2].id!=152) {
                                                darkblue=sin(xx/90+zz/100) + sin(xx/100+zz/90) + sin(xx/110+zz/100) + sin(xx/100+zz/110) + sin(xx/110+zz/90) + sin(xx/90+zz/110);
                                                darkblue+=sin(xx/190+zz/200) + sin(xx/200+zz/190) + sin(xx/210+zz/200) + sin(xx/200+zz/210) + sin(xx/210+zz/190) + sin(xx/190+zz/210);
                                                darkblue+=(sin(xx/19+zz/20) + sin(xx/20+zz/19) + sin(xx/21+zz/20) + sin(xx/20+zz/21) + sin(xx/21+zz/19) + sin(xx/19+zz/21))/3;
                                                darkblue=((darkblue+14)/28)*15.9;
                                                AY[y] = BlockInfo(171, 0, (int)darkblue, 0 );

/*
                                            } else if (y==109-2+train_height && edge2==1 && edge==0) {
                                                if (corner2==1) {
                                                    AY[y] = BlockInfo(251, 0, red, 0 );
                                                    AY[y+1] = BlockInfo(66,0,curve,0);
                                                } else {
                                                    if (((((int)xx+3)%15)==0 || (((int)zz+3)%15)==0)) {
                                                        AY[y] = BlockInfo(152, 0, 0, 0 );
                                                        AY[y+1] = BlockInfo(27,0,dir_x,0);
                                                    } else {
                                                        AY[y] = BlockInfo(251, 0, red, 0 );
                                                        AY[y+1] = BlockInfo(27,0,dir_x,0);
                                                    }
                                                }
*/
                                            } else if (AY[y].id!=147 && AY[y].id!=66 && AY[y].id!=27) {
                                                AY[y] = BlockInfo();
                                            }
                                        }
                                    }
                                }
                                else if (y==115+2+ceil_heigher) {
                                    toggle2();
                                    if (pixel!=0) {
                                        if (((((int)xx+3)%5)==0 && (((int)zz+3)%5)==0)) {
                                            AY[y] = BlockInfo(89, 0, 0, 0 );
                                        } else if (edge==1) {
                                            if (corner2==1) {
                                                AY[y] = BlockInfo(251, 0, red, 0 );
                                                AY[y+1] = BlockInfo(66,0,curve,0);
                                            } else {
                                                if ( ((((int)xx+3)%15)==0 || (((int)zz+3)%15)==0) || ( col.r==254 && ( ((((int)xx+3)%5)==0 || (((int)zz+3)%5)==0) ) ) ) {
                                                    AY[y] = BlockInfo(152, 0, 0, 0 );
                                                    AY[y+1] = BlockInfo(27,0,dir_x,0);
                                                } else {
                                                    AY[y] = BlockInfo(251, 0, red, 0 );
                                                    AY[y+1] = BlockInfo(27,0,dir_x,0);
                                                }
                                            }
                                            rails++;
                                            AY[y+2]=BlockInfo();
//hoppa
                                            if (x>0            && AX[x-1][z][y+1].id!=27   && AX[x-1][z][y+1].id!=66  ) { AX[x-1][z][y+1]=BlockInfo(); AX[x-1][z][y+2]=BlockInfo(); }
                                            if (z>0            && AX[x][z-1][y+1].id!=27   && AX[x][z-1][y+1].id!=66  ) { AX[x][z-1][y+1]=BlockInfo(); AX[x][z-1][y+2]=BlockInfo(); }
                                            if (x<511          && AX[x+1][z][y+1].id!=27   && AX[x+1][z][y+1].id!=66  ) { AX[x+1][z][y+1]=BlockInfo(); AX[x+1][z][y+2]=BlockInfo(); }
                                            if (z<511          && AX[x][z+1][y+1].id!=27   && AX[x][z+1][y+1].id!=66  ) { AX[x][z+1][y+1]=BlockInfo(); AX[x][z+1][y+2]=BlockInfo(); }
                                            if (x>0 && z>0     && AX[x-1][z-1][y+1].id!=27 && AX[x-1][z-1][y+1].id!=66) { AX[x-1][z-1][y+1]=BlockInfo(); AX[x-1][z-1][y+2]=BlockInfo(); }
                                            if (z>0 && x<511   && AX[x+1][z-1][y+1].id!=27 && AX[x+1][z-1][y+1].id!=66) { AX[x+1][z-1][y+1]=BlockInfo(); AX[x+1][z-1][y+2]=BlockInfo(); }
                                            if (x<511 && z<511 && AX[x+1][z+1][y+1].id!=27 && AX[x+1][z+1][y+1].id!=66) { AX[x+1][z+1][y+1]=BlockInfo(); AX[x+1][z+1][y+2]=BlockInfo(); }
                                            if (z<511 && x>0   && AX[x-1][z+1][y+1].id!=27 && AX[x-1][z+1][y+1].id!=66) { AX[x-1][z+1][y+1]=BlockInfo(); AX[x-1][z+1][y+2]=BlockInfo(); }
                                            hoppa(AX,x,z,y);
//                                            AY[y+3]=BlockInfo();
                                        } else if (rand()%30==0) {
                                            AY[y] = BlockInfo(95, 0, ret_color(rand()%256,rand()%256,rand()%256),0 );
                                        } else {
                                            if (red2==1) {
                                                if (AY[y].id==0 || AY[y].id==8) AY[y] = BlockInfo(95, 0, red,0 );
                                            } else {
                                                if (AY[y].id==0 || AY[y].id==8) AY[y] = BlockInfo(95, 0, white,0 );
                                            }
                                        }
                                    }
                                }
                                else if (y==108-2) {
                                    if (pixel!=0) {
                                        if (edge==0 &&
                                            (   (((int)xx+2)%5)==0 && (((int)zz+2)%5)==0 ||
                                                (((int)xx+4)%5)==0 && (((int)zz+2)%5)==0 ||
                                                (((int)xx+4)%5)==0 && (((int)zz+4)%5)==0 ||
                                                (((int)xx+2)%5)==0 && (((int)zz+4)%5)==0
                                            ) ) {
                                            AY[y] = BlockInfo(89, 0, 0, 0 );
                                        } else if ((((int)xx+3)%5)==0 && (((int)zz+3)%5)==0 ) {
                                            int what=rand()%20;
                                            setBoom(region,x,z,y);
                                            AY[107-2] = BlockInfo(251, 0, 0, 0 );
                                            AY[109-2] = BlockInfo(147, 0, 0, 0 );
                                        } else if ((((int)xx+1+(rand()%5))%5)==0 && (((int)zz+1+(rand()%5))%5)==0 && edge==0 && edge2==0) {
                                            int what=rand()%16;
                                            if (what<15) setRabbits(region,x,z,y);
                                            else if (what==15) setWolf(region,x,z,y);
                                            else if (what==16) setRandom(region,x,z,y);
                                            else { setBoom(region,x,z,y); AY[107-2] = BlockInfo(251, 0, 0, 0 ); }
                                            AY[109-2] = BlockInfo(147, 0, 0, 0 );
                                        } else if ((((int)xx+1+(rand()%5))%5)==0 && (((int)zz+1+(rand()%5))%5)==0 && edge==0 && edge2==0) {
                                            int what=rand()%16;
                                            if (what<15) setRabbits(region,x,z,y);
                                            else if (what==15) setWolf(region,x,z,y);
                                            else if (what==16) setRandom(region,x,z,y);
                                            else { setBoom(region,x,z,y); AY[107-2] = BlockInfo(251, 0, 0, 0 ); }
                                            AY[109-2] = BlockInfo(147, 0, 0, 0 );
                                        } else if ((((int)xx+1+(rand()%5))%5)==0 && (((int)zz+1+(rand()%5))%5)==0 && edge==0 && edge2==0) {
                                            int what=rand()%16;
                                            if (what<15) setRabbits(region,x,z,y);
                                            else if (what==15) setWolf(region,x,z,y);
                                            else if (what==16) setRandom(region,x,z,y);
                                            else { setBoom(region,x,z,y); AY[107-2] = BlockInfo(251, 0, 0, 0 ); }
                                            AY[109-2] = BlockInfo(147, 0, 0, 0 );
                                        } else if ((((int)xx+1+(rand()%5))%5)==0 && (((int)zz+1+(rand()%5))%5)==0 && edge==0 && edge2==0) {
                                            int what=rand()%7;
                                            if (what<5) setRabbits(region,x,z,y);
                                            else if (what==5) setWolf(region,x,z,y);
                                            else if (what==6) setRandom(region,x,z,y);
                                            else { setBoom(region,x,z,y); AY[107-2] = BlockInfo(251, 0, 0, 0 ); }
                                            AY[109-2] = BlockInfo(147, 0, 0, 0 );
                                        }
                                         else {
//                                         else if (edge==0) {
                                            if (red2==1)
                                                AY[y] = BlockInfo(251, 0, red, 0 );
                                            else
                                                AY[y] = BlockInfo(251, 0, white,0 );
                                        }
                                    }
                                }
                                else if (y==107-2 && (((int)xx+3)%5)==0 && (((int)zz+3)%5)==0 && pixel!=0) { AY[y] = BlockInfo(251, 0, ret_color(rand()%256,rand()%256,rand()%256),0 );  }
                                else if (y==107-2) {  if (pixel!=0 && (rand()%2)==0)      AY[y] = BlockInfo(251-((251-95)*(rand()%2)), 0, ret_color(rand()%256,rand()%256,rand()%256),0 );  }
                                else if (y==106-2) {  if (pixel!=0 && (rand()%4)==0)      AY[y] = BlockInfo(251-((251-95)*(rand()%2)), 0, ret_color(rand()%256,rand()%256,rand()%256),0 );  }
                                else if (y==105-2) {  if (pixel!=0 && (rand()%8)==0)      AY[y] = BlockInfo(251-((251-95)*(rand()%2)), 0, ret_color(rand()%256,rand()%256,rand()%256),0 );  }
                                else if (y==104-2) {  if (pixel!=0 && (rand()%16)==0)     AY[y] = BlockInfo(251-((251-95)*(rand()%2)), 0, ret_color(rand()%256,rand()%256,rand()%256),0 );  }

/*
                                if (y==108-2+train_height) {
                                    if (edge2==1 && edge==0) {
                                        if (red2==1)
                                            AY[y] = BlockInfo(152, 0, 0, 0 );
                                        else
                                            AY[y] = BlockInfo(152, 0, 0, 0 );
                                    }
                                }
*/
                               if (AY[y].id==95 && AY[y].data==0)  AY[y]=BlockInfo(20,0,0,0);
                            }
                        }
                    }

                    printf(" Roof:\b\b\b\b\b\b");
                    for (int x = 0; x < 512; x++) {
                        xx=x+chunk_offsetx*16;
                        BlockInfo** AZ=AX[x];
                        for (int z = 0; z < 512; z++) {
                            zz=z+chunk_offsetz*16;
                            BlockInfo* AY=AZ[z];
                            toggle2();
                            float hop=0.0 ;
                            float pixel;
                            float c;
                            float c1,c2,c3,c4;
                            float c5,c6,c7,c8;
                            c1=1.0;
                            sf::Color col;
                            col=image_plot_org.getPixel(x+5,z+5);
                            c=(col.r+col.b+col.g);
                            pixel=c/3;
                            if (col.a==0) pixel=0;
                            for (int y = yl-1; y >=0; y--) {
                                if (y>=248 && (rand()%10)<8 ) {
                                    sf::Color colminx;
                                    sf::Color colplusx;
                                    sf::Color colminz;
                                    sf::Color colplusz;
                                    sf::Color colminxminz;
                                    sf::Color colplusxminz;
                                    sf::Color colminxplusz;
                                    sf::Color colplusxplusz;
                                    colminx=image_plot_org.getPixel(x+3,z+5);
                                    colplusx=image_plot_org.getPixel(x+7,z+5);
                                    colminz=image_plot_org.getPixel(x+5,z+3);
                                    colplusz=image_plot_org.getPixel(x+5,z+7);

                                    colminxminz=image_plot_org.getPixel(x+3,z+3);
                                    colplusxminz=image_plot_org.getPixel(x+7,z+3);
                                    colminxplusz=image_plot_org.getPixel(x+3,z+7);
                                    colplusxplusz=image_plot_org.getPixel(x+7,z+7);

                                    c1=(colminx.r+colminx.b+colminx.g);
                                    c2=(colplusx.r+colplusx.b+colplusx.g);
                                    c3=(colminz.r+colminz.b+colminz.g);
                                    c4=(colplusz.r+colplusz.b+colplusz.g);

                                    c5=(colminxminz.r+colminxminz.b+colminxminz.g);
                                    c6=(colplusxminz.r+colplusxminz.b+colplusxminz.g);
                                    c7=(colminxplusz.r+colminxplusz.b+colminxplusz.g);
                                    c8=(colplusxplusz.r+colplusxplusz.b+colplusxplusz.g);

                                    if (c1==0 && c2==0 && c3==0 && c4==0 && c5==0 && c6==0 && c7==0 && c8==0) c1=0; else c1=1;
                                }

                                if (y<=253 && y>=250) {
                                    if (y==253) {
                                        if (pixel==0 || xx==0 || zz==0 || xx==60*512-1 || zz==60*512-1) {
                                            if (c1==0 && !(xx==0 || zz==0 || xx==60*512-1 || zz==60*512-1) && AY[y+1].id==0) {
                                                AY[y] = BlockInfo();
                                            } else {
                                                AY[y] = BlockInfo(251, 0, ret_color(255,255,0),0 );
                                            }
                                        } else {
                                            AY[y] = BlockInfo(8, 0, ret_color(0,0,255),0 );
                                        }
                                    }  else if (y==252 || y==251 || y==250) {
                                        if (pixel==0 || xx==0 || zz==0) {
                                            if ( (!(rand()%2)) && c1==0 && !(xx==0 || zz==0 || xx==60*512-1 || zz==60*512-1) && AY[y+1].id==0 ) {
                                                AY[y] = BlockInfo();
                                            } else {
                                                AY[y] = BlockInfo(251, 0, ret_color(255,255,0),0 );
                                            }
                                        } else {
                                            AY[y] = BlockInfo(8, 0, ret_color(0,0,255),0 );
                                        }
                                    }
                                } else if (y==249 || y==248) {
                                    if (pixel==0 || xx==0 || zz==0 || xx==(60*512-1) || zz==(60*512-1)) {
                                        if (c1==0 && !(xx==0 || zz==0 || xx==(60*512-1) || zz==(60*512-1)) && AY[y+1].id==0) {
                                            AY[y] = BlockInfo();
                                            if ((rand()%10)==0) AY[y-1] = BlockInfo();
                                        } else {
                                            AY[y] = BlockInfo(251, 0, ret_color(255,255,0),0 );
                                        }
                                    } else {
                                        AY[y] = BlockInfo(251, 0, ret_color(255,255,0),0 );
                                    }
                                }
                                if (AY[y].id!=0) num_blocks++;
                            }
                        }
                    }

/*
                    minecraft:tube_coral_block
                    minecraft:brain_coral_block
                    minecraft:bubble_coral_block
                    minecraft:fire_coral_block
                    minecraft:horn_coral_block
                    minecraft:tube_coral
                    minecraft:brain_coral
                    minecraft:bubble_coral
                    minecraft:fire_coral
                    minecraft:horn_coral
                    minecraft:tube_coral_fan
                    minecraft:brain_coral_fan
                    minecraft:bubble_coral_fan
                    minecraft:fire_coral_fan
                    minecraft:horn_coral_fan
*/

                    printf(" %d blocks = %5.2f%, #rails = %d, = %7.3f kilometers\n",num_blocks,100.0*(float)num_blocks/(1024*1024*64),rails,(float)rails/1000);
                    rails=0;
/*
                    if (plot_cubes) {
                        int blocks_shown=0;
                        MUTEX_MCEDITOR.lock();
                        m_pointCloud3.resize(num_blocks);
                        for (int x = 0; x < 512; x++) {
                            xx=x+chunk_offsetx*16;
                            BlockInfo** AZ=AX[x];
                            for (int z = 0; z < 512; z++) {
                                zz=z+chunk_offsetz*16;
                                BlockInfo* AY=AZ[z];
                                toggle2();
                                for (int y = 0; y < yl; y++) {
                                    if (AY[y].id!=0) {
                                        if (y>0 && y<255 && x>0 && x<511 & z>1 && z<511) {
                                            if (  (
                                                (AX[x-1][z-1][y-1].id!=0) &&
                                                (AX[x+0][z-1][y-1].id!=0) &&
                                                (AX[x+1][z-1][y-1].id!=0) &&
                                                (AX[x-1][z+0][y-1].id!=0) &&
                                                (AX[x+0][z+0][y-1].id!=0) &&
                                                (AX[x+1][z+0][y-1].id!=0) &&
                                                (AX[x-1][z+1][y-1].id!=0) &&
                                                (AX[x+0][z+1][y-1].id!=0) &&
                                                (AX[x+1][z+1][y-1].id!=0) &&

                                                (AX[x-1][z-1][y+0].id!=0) &&
                                                (AX[x+0][z-1][y+0].id!=0) &&
                                                (AX[x+1][z-1][y+0].id!=0) &&
                                                (AX[x-1][z+0][y+0].id!=0) &&
                                                (AX[x+0][z+0][y+0].id!=0) &&
                                                (AX[x+1][z+0][y+0].id!=0) &&
                                                (AX[x-1][z+1][y+0].id!=0) &&
                                                (AX[x+0][z+1][y+0].id!=0) &&
                                                (AX[x+1][z+1][y+0].id!=0) &&

                                                (AX[x-1][z-1][y+1].id!=0) &&
                                                (AX[x+0][z-1][y+1].id!=0) &&
                                                (AX[x+1][z-1][y+1].id!=0) &&
                                                (AX[x-1][z+0][y+1].id!=0) &&
                                                (AX[x+0][z+0][y+1].id!=0) &&
                                                (AX[x+1][z+0][y+1].id!=0) &&
                                                (AX[x-1][z+1][y+1].id!=0) &&
                                                (AX[x+0][z+1][y+1].id!=0) &&
                                                (AX[x+1][z+1][y+1].id!=0)

                                             ) ) {
                                                 continue;
                                             }
                                        }
                                        m_pointCloud3[blocks_shown].position.x=(float)x*256/scale_factor;
                                        m_pointCloud3[blocks_shown].position.y=(float)z*256/scale_factor;
                                        m_pointCloud3[blocks_shown].texCoords.x = (float) (((x+y+1000)%6)*256)*150.0;
                                        m_pointCloud3[blocks_shown].texCoords.y = (float) (0)*150.0;
                                        m_pointCloud3[blocks_shown].color = sf::Color(y,0,0,0);
                                        blocks_shown++;
                                        if (blocks_shown>num_blocks) {printf("\nError block count\n"); y=yl; x=xl; z=zl;}
                                    }
                                }
                            }
                        }
                        m_pointCloud3.resize(blocks_shown);
                        printf(" %d blocks added to plot_cubes vertex\n",num_blocks);
                        MUTEX_MCEDITOR.unlock();
                    }

                } else {
/*
                    int n=0;                region.A[n][0][0] = BlockInfo( 14, 1, 0 );                region.B[n][0][0] = new BlockEntityGlowColor( Pos(n,0,0), "minecraft:teglowstone" );
                    n++;                    region.A[n][0][0] = BlockInfo( 13, 1, 0 );                region.B[n][0][0] = new BlockEntityGlowColor( Pos(n,0,0), "minecraft:teglowstone" );
                    n++;                    region.A[n][0][0] = BlockInfo( 12, 1, 0 );                region.B[n][0][0] = new BlockEntityGlowColor( Pos(n,0,0), "minecraft:teglowstone" );
                    n++;                    region.A[n][0][0] = BlockInfo( 11, 1, 0 );                region.B[n][0][0] = new BlockEntityGlowColor( Pos(n,0,0), "minecraft:teglowstone" );
                    n++;                    region.A[n][0][0] = BlockInfo( 10, 1, 0 );                region.B[n][0][0] = new BlockEntityGlowColor( Pos(n,0,0), "minecraft:teglowstone" );
                    n++;                    region.A[n][0][0] = BlockInfo(  9, 1, 0 );                region.B[n][0][0] = new BlockEntityGlowColor( Pos(n,0,0), "minecraft:teglowstone" );
                    n++;                    region.A[n][0][0] = BlockInfo(  8, 1, 0 );                region.B[n][0][0] = new BlockEntityGlowColor( Pos(n,0,0), "moglowstone:orange_gsblock" );
                    n++;                    region.A[n][0][0] = BlockInfo(  7, 1, 0 );                region.B[n][0][0] = new BlockEntityGlowColor( Pos(n,0,0), "minecraft:teglowstone" );
                    n++;                    region.A[n][0][0] = BlockInfo(  6, 1, 0 );                region.B[n][0][0] = new BlockEntityGlowColor( Pos(n,0,0), "minecraft:teglowstone" );
                    n++;                    region.A[n][0][0] = BlockInfo(  4, 1, 0 );                region.B[n][0][0] = new BlockEntityGlowColor( Pos(n,0,0), "minecraft:teglowstone" );
                    n++;                    region.A[n][0][0] = BlockInfo(  3, 1, 0 );                region.B[n][0][0] = new BlockEntityGlowColor( Pos(n,0,0), "minecraft:teglowstone" );
                    n++;                    region.A[n][0][0] = BlockInfo(  2, 1, 0 );                region.B[n][0][0] = new BlockEntityGlowColor( Pos(n,0,0), "minecraft:teglowstone" );
                    n++;                    region.A[n][0][0] = BlockInfo(  1, 1, 0 );                region.B[n][0][0] = new BlockEntityGlowColor( Pos(n,0,0), "minecraft:teglowstone" );
                    n++;                    region.A[n][0][0] = BlockInfo((ui)254, 0, 0 );         //   region.B[n][0][1] = new BlockEntityGlowColor( Pos(n,0,1) );
                    n++;                    region.A[n][0][0] = BlockInfo((ui)253, 0, 0 );         //   region.B[n][0][1] = new BlockEntityGlowColor( Pos(n,0,1) );

                    n=0;                    region.A[n][1][0] = BlockInfo();
                    n++;                    region.A[n][1][0] = BlockInfo();
                    n++;                    region.A[n][1][0] = BlockInfo();
                    n++;                    region.A[n][1][0] = BlockInfo();
                    n++;                    region.A[n][1][0] = BlockInfo();
                    n++;                    region.A[n][1][0] = BlockInfo();
                    n++;                    region.A[n][1][0] = BlockInfo();
                    n++;                    region.A[n][1][0] = BlockInfo();
                    n++;                    region.A[n][1][0] = BlockInfo();
                    n++;                    region.A[n][1][0] = BlockInfo();
                    n++;                    region.A[n][1][0] = BlockInfo();
                    n++;                    region.A[n][1][0] = BlockInfo();
                    n++;                    region.A[n][1][0] = BlockInfo();
                    n++;                    region.A[n][1][0] = BlockInfo();
                    n++;                    region.A[n][1][0] = BlockInfo();
                    int col=ret_color(255,255,0);
                    for (int x = 0; x < 512; x++) {
                        int xx=x+chunk_offsetx*16;
                        BlockInfo** AZ=AX[x];
                        for (int z = 0; z < 512; z++) {
                            int zz=z+chunk_offsetz*16;
                            BlockInfo* AY=AZ[z];
                            toggle2();
                            for (int y = 0; y < yl; y++) {
                                if (xx%64==0 || zz%64==0 || y%63==0) AY[y] = BlockInfo(251,0,col);
                            }
                        }
                    }
*/
                }

                printf(" ");
                first_MCEDIT=0;
                region_x_old=0;
                region_z_old=0;
//                file_name_MCA = MCAFileNameXZ(region_x, region_z);
                mkdir("/Saves/test/region/done0");
                sprintf(tmp, "/Saves/Test/region/done0/r.%d.%d.mca", region_x, region_z);
                file_name_MCA = tmp;
                editor.setRegion(region);

//                char tmp[256];
//                sprintf(tmp, "/Saves/Test/region/done/r.%d.%d.mca", region_x, region_z);
//                CopyFile(file_name_MCA.c_str(),tmp,true);

                CopyFile(tmp,fname.c_str(),false);

                if (MCEDITOR_stop==1 || file_exists("stop.txt")) {
                    printf("Stop requested, exiting\n");
//                    system("/saves/copy_test.bat");
                    send_message='x';
                    return 0;
                }
            }
        }
    }
    return 0;
}


MCEditor editor2;

// set from_empty=1 for also creating non existing files (when data in texture, otherwise also skipped...), otherwise they are skipped.....
// aternative you can set a file in the pacman_cuberite dir called from_empty.txt, then it does the same, don't forget to remove it when need skipping non existing files....
// so you also can control behaviour while program is running....
int from_empty=0;
int load_leeg;

int main_mceditor3()
{
    int region_x=0;
    int region_z=0;

    int contin=1;
    int skipping=1;
    int skippy=0;
    int skippy2=0;
    int light=0;
    int size_regions=0;
	srand(time(0));
	int first_loop=1;
    while (size_regions<60) {
        size_regions++;
//        printf("1) size_regions=%d, Region=%d,%d\n",size_regions,region_x,region_z);
        for (region_x=0; region_x<size_regions && MCEDITOR_stop==0; region_x++) {
//            printf("2) size_regions=%d, Region=%d,%d\n",size_regions,region_x,region_z);
            for (region_z=0; region_z<size_regions && MCEDITOR_stop==0; region_z++) {
//                printf("3) size_regions=%d, Region=%d,%d\n",size_regions,region_x,region_z);
                region_xxx=region_x;
                region_zzz=region_z;
                if (region_x<size_regions-1 && region_z<size_regions-1) {
                    continue;
                }
                toggle_2=0;toggle_3=0;
                if (contin==1) {
                    contin=0;
                }
                chunk_offsetx=region_x*32;
                chunk_offsetz=region_z*32;

                x00=0; y00=0; z00=0;
                yl = 255;
                xl=512; zl=512;
                load_leeg=0;
                if (from_empty==0 && file_exists("from_empty.txt")) {
                    from_empty=1;
                }

                string fname=MCAFileNameXZ(region_x, region_z);
                if (mcglobal==1) {
                    char tmp[256];
                    sprintf(tmp, "/Saves/Test/region/done0/r.%d.%d.mca", region_x, region_z);
                    fname=tmp;
                } else if (mcglobal==2) {
                    char tmp[256];
                    sprintf(tmp, "/Saves/Test/region/done1/r.%d.%d.mca", region_x, region_z);
                    fname=tmp;
                }
                if ( !file_exists(fname.c_str() ) ) {
                    if (from_empty==0 && file_exists("from_empty.txt")) {
                        printf("File from_empty.txt exists. Also create new non existing source files.\n");
                        from_empty=1;
                    }
                    if (from_empty==0) {
                        if (skippy2>0) printf("\n");
                        skippy2=0;
                        if (skippy==0)
                            printf("File(s) do(es)n't exists, skipping %s",fname.c_str());
                        else
                            printf(", %s",fname.c_str());
                        skippy++;
                        continue;
                    } else {
                        printf("File %s doesn't exists, creating new\n",fname.c_str());
                        load_leeg=1;
                    }
                }

                read_one_plot_WINMAIN(29995-512-region_x*512-5, 29995-512-region_z*512-5, &image_plot);
                read_one_plot_WINMAIN(29995-512-region_x*512-5, 29995-512-region_z*512-5, &image_plot3);

                if (mcglobal==1) {
                    skipping=1;
                    for (int x = 0; x < 512; x++) {
                        for (int z = 0; z < 512; z++) {
                            if ( !( (image_plot.getPixel(x+5,z+5).r==0) && (image_plot.getPixel(x+5,z+5).g==0) && (image_plot.getPixel(x+5,z+5).b==0)) ) {
                                skipping=0;
                            }
                        }
                    }
                    if (skipping==1) {
                        if (skippy>0) printf("\n");
                        skippy=0;
                        if (skippy2==0)
                            printf("Empty...no data...skipping r.%d.%d",region_x,region_z);
                        else
                            printf(", r.%d.%d",region_x,region_z);
                        skippy2++;
                        continue;
                    }
                } else {
                    skipping=0;
                }

//                region.clearRegion();
                MCRegion region(x00, z00, y00, xl, zl, yl);

                int num_blocks=0;

                BlockInfo*** AX=region.A;
                if (skippy>0 || skippy2>0) printf("\n");
                skippy=0;
                skippy2=0;
                if (load_leeg) {
                    remove_block_entities=1;
                    first_MCEDIT=1;
                    editor.mca_coder.loadMCA("/Saves/Leeg/region/r.0.0.mca");
                    editor.mca_coder.setPOSITIONS();
                    first_MCEDIT=0;
                    region_x_old=0,region_z_old=0;
                    printf("- Creating region r.%d.%d.mca: ",region_x,region_z);
                } else {
                    remove_block_entities=0;
                    printf("File %s exists. ",fname.c_str());
                    first_MCEDIT=1;
                    editor.mca_coder.loadMCA(fname.c_str());
                    first_MCEDIT=0;
                    region_x_old=0,region_z_old=0;
                    for (int x = 0; x < xl; x++) {
                        BlockInfo** AZ=AX[x];
                        for (int z = 0; z < zl; z++) {
                            BlockInfo* AY=AZ[z];
                            toggle2();
                            for (int y = 0; y < 256; y++) {
                                BlockInfo bi=editor.mca_coder.getBlock(x,z,y);
                                if (bi.id!=0) AY[y]=BlockInfo(bi.id,bi.add,bi.data,bi.block_light,bi.sky_light);
//                                if (bi.id!=0) AY[y]=bi;
    //                                AY[y]=editor.mca_coder.getBlock(x,z,y);
                                if (AY[y].id!=0) num_blocks++;
                            }
                        }
                    }
                    reset_block();
                }



//              remove block entities when loading one with entities? Or nog.... ???
//                    editor2.mca_coder.clearModification();
//                    printf("\n");

                skipping=0;
//                printf("Getting data\n");
//                read_one_plot_WINMAIN(59*512-region_x*512,   59*512-region_z*512 + 30720, &image_plot_extra);
//                read_one_plot_WINMAIN(30000-512-region_x*512-5, 30000-512-region_z*512-5, &image_plot_org);
                make_mirror(&image_plot);
                make_mirror(&image_plot3);
//                make_mirror(&image_plot_org);

                for (int x = 1; x < 511+10; x++) {
                    for (int z = 1; z < 511+10; z++) {
                        if (image_plot.getPixel(x,z).r!=0 || image_plot.getPixel(x,z).g!=0 || image_plot.getPixel(x,z).b!=0) {
                            if ((image_plot.getPixel(x-1,z).r==0 && image_plot.getPixel(x-1,z).g==0 && image_plot.getPixel(x-1,z).b==0) &&
                                 (image_plot.getPixel(x+1,z).r==0 && image_plot.getPixel(x+1,z).g==0 && image_plot.getPixel(x+1,z).b==0)  ) image_plot.setPixel(x,z,sf::Color(0,0,0,0));
                            if ((image_plot.getPixel(x,z-1).r==0 && image_plot.getPixel(x,z-1).g==0 && image_plot.getPixel(x,z-1).b==0) &&
                                 (image_plot.getPixel(x,z+1).r==0 && image_plot.getPixel(x,z+1).g==0 && image_plot.getPixel(x,z+1).b==0)  ) image_plot.setPixel(x,z,sf::Color(0,0,0,0));
                        }
                    }
                }

                for (int x = 0; x < 512+10; x++) {
                    for (int z = 0; z < 512+10; z++) {
                        float pixel;
                        float c;
                        sf::Color col;
                        col=image_plot.getPixel(x,z);
                        c=(col.r+col.b+col.g);
                        pixel = (c/(3));
                        if (col.a==0) pixel=0;
                        if (pixel==0 && x>0 && x<511+10 && z>0 && z<511+10) {
                            for (int xxx=-1; xxx<=1; xxx++) {
                                for (int zzz=-1; zzz<=1; zzz++) {
//                                    if (xxx==0 || zzz==0) {
                                    if (xxx!=0 || zzz!=0) {
//                                        image_plot3.setPixel(x+xxx,z+zzz, col);
                                        image_plot3.setPixel(x+xxx,z+zzz, col);
                                    }
                                }
                            }
                        }
                    }
                }

                for (int x = 1; x < 511+10; x++) {
                    for (int z = 1; z < 511+10; z++) {
//                        float pixel;
//                        float c;
                        if (image_plot3.getPixel(x,z).r!=0 || image_plot3.getPixel(x,z).g!=0 || image_plot3.getPixel(x,z).b!=0) {
                            if ((image_plot3.getPixel(x-1,z).r==0 && image_plot3.getPixel(x-1,z).g==0 && image_plot3.getPixel(x-1,z).b==0) &&
                                 (image_plot3.getPixel(x+1,z).r==0 && image_plot3.getPixel(x+1,z).g==0 && image_plot3.getPixel(x+1,z).b==0)  ) image_plot3.setPixel(x,z,sf::Color(0,0,0,0));
                            if ((image_plot3.getPixel(x,z-1).r==0 && image_plot3.getPixel(x,z-1).g==0 && image_plot3.getPixel(x,z-1).b==0) &&
                                 (image_plot3.getPixel(x,z+1).r==0 && image_plot3.getPixel(x,z+1).g==0 && image_plot3.getPixel(x,z+1).b==0)  ) image_plot3.setPixel(x,z,sf::Color(0,0,0,0));
                        }
                    }
                }


                int maze_offset=mcglobal2;
                int maze_shrink=mcglobal3;

                if (mcglobal==1) {
                    if (maze_offset==0) maze_offset=7;
                    if (maze_shrink==0) maze_shrink=5;
                } else if (mcglobal==2) {
                    if (maze_offset==0) maze_offset=2+ceil_heigher+50;
                    if (maze_shrink==0) maze_shrink=-5;
                }
//                printf("Offset=%d\n",maze_offset);

//                BlockInfo*** AX=region.A;
                if (1) {
                    int mix1;                int mix2;                int mix3;                int mix4;
                    int mix5;                int mix6;                int mix7;                int mix8;                int mix9;

                    printf(" Maze:\b\b\b\b\b\b");
                    int train_height=5;
                    int yellow=ret_color(255,255,0);
                    int white=ret_color(255,255,255);
                    int red=ret_color(255,0,0);
                    int lightred=ret_color(255,64,32);
                    int darkred=ret_color(128,0,0);
                    int black=ret_color(0,0,0);
                    float darkblue=ret_color(0,0,128);


                    for (int x = 0; x < xl; x++) {
                        xx=x+chunk_offsetx*16;
                        BlockInfo** AZ=AX[x];
                        for (int z = 0; z < zl; z++) {
                            zz=z+chunk_offsetz*16;
                            BlockInfo* AY=AZ[z];
                            int r, g, b;
                            float pixel;
//                            float pixel_org;

                            float c;
                            sf::Color col;
//                            sf::Color col_org;
//                            sf::Color col_extra;
//goed?
                            col=image_plot.getPixel(x+5,z+5);
//                                col=image_plot.getPixel(x+5,z+5);
//                            col_org=image_plot_org.getPixel(x+5,z+5);
//                            col_extra=image_plot_extra.getPixel(x,z);

                            c=(col.r+col.b+col.g);
                            pixel = (c/(3));
                            if (col.a==0) pixel=0;

//                            c=(col_org.r+col_org.b+col_org.g);
//                            if (col_org.a==0) pixel_org=0;
//                            pixel_org = (c/(3));

                            int x_off=1;
                            int z_off=1;

                            for (int y = 0; y < 256; y++) {
                                int edge=0;
                                int edge2=0;
                                int edge3=0;
                                int corner2=0;
                                int red2=0;
                                int dir_x=0;
                                int curve=0;
                                int c1;
                                int c2;
                                int c3;
                                int c4;

                                if (y!=(115+2+maze_offset-maze_shrink)) {
                                    if (                  y>0 && (AX[x][z][y-1].id==27     || AX[x][z][y-1].id==66    )) { continue; }
                                    if (x>0            && y>0 && (AX[x-1][z][y-1].id==27   || AX[x-1][z][y-1].id==66  )) { continue; }
                                    if (z>0            && y>0 && (AX[x][z-1][y-1].id==27   || AX[x][z-1][y-1].id==66  )) { continue; }
                                    if (x<511          && y>0 && (AX[x+1][z][y-1].id==27   || AX[x+1][z][y-1].id==66  )) { continue; }
                                    if (z<511          && y>0 && (AX[x][z+1][y-1].id==27   || AX[x][z+1][y-1].id==66  )) { continue; }
                                    if (x>0 && z>0     && y>0 && (AX[x-1][z-1][y-1].id==27 || AX[x-1][z-1][y-1].id==66)) { continue; }
                                    if (z>0 && x<511   && y>0 && (AX[x+1][z-1][y-1].id==27 || AX[x+1][z-1][y-1].id==66)) { continue; }
                                    if (x<511 && z<511 && y>0 && (AX[x+1][z+1][y-1].id==27 || AX[x+1][z+1][y-1].id==66)) { continue; }
                                    if (z<511 && x>0   && y>0 && (AX[x-1][z+1][y-1].id==27 || AX[x-1][z+1][y-1].id==66)) { continue; }

                                    if (                  (AX[x][z][y].id==27     || AX[x][z][y].id==66    )) { rails_tot++; continue; }
                                    if (x>0            && (AX[x-1][z][y].id==27   || AX[x-1][z][y].id==66  )) { continue; }
                                    if (z>0            && (AX[x][z-1][y].id==27   || AX[x][z-1][y].id==66  )) { continue; }
                                    if (x<511          && (AX[x+1][z][y].id==27   || AX[x+1][z][y].id==66  )) { continue; }
                                    if (z<511          && (AX[x][z+1][y].id==27   || AX[x][z+1][y].id==66  )) { continue; }
                                    if (x>0 && z>0     && (AX[x-1][z-1][y].id==27 || AX[x-1][z-1][y].id==66)) { continue; }
                                    if (z>0 && x<511   && (AX[x+1][z-1][y].id==27 || AX[x+1][z-1][y].id==66)) { continue; }
                                    if (x<511 && z<511 && (AX[x+1][z+1][y].id==27 || AX[x+1][z+1][y].id==66)) { continue; }
                                    if (z<511 && x>0   && (AX[x-1][z+1][y].id==27 || AX[x-1][z+1][y].id==66)) { continue; }
                                }
                                if (y>=(108-2+maze_offset) && y<=(115+2+maze_offset-maze_shrink)) {
                                    sf::Color col_side1;
                                    sf::Color col_side2;
                                    sf::Color col_side3;
                                    sf::Color col_side4;
                                    col_side1=image_plot.getPixel(x-x_off+5,    z+5);
                                    col_side2=image_plot.getPixel(x+5,          z-z_off+5);
                                    col_side3=image_plot.getPixel(x+x_off+5,    z+5);
                                    col_side4=image_plot.getPixel(x+5,          z+z_off+5);
                                    red2=0;
                                    if ( col.r==254 || (pixel==0 && (col_side1.r==254 || col_side2.r==254 || col_side3.r==254 || col_side4.r==254)) ) red2=1;
                                    c1=(col_side1.r+col_side1.b+col_side1.g);
                                    c2=(col_side2.r+col_side2.b+col_side2.g);
                                    c3=(col_side3.r+col_side3.b+col_side3.g);
                                    c4=(col_side4.r+col_side4.b+col_side4.g);
                                    if (c1==0 || c2==0 || c3==0 || c4==0) edge=1;
                                    dir_x=0;
                                    curve=0;
                                    if (c1!=0 && c3!=0) dir_x=1+8;
                                    if (c2!=0 && c4!=0) dir_x=0+8;
                                    if (c1!=0 && c2!=0 && c3==0 && c4==0) curve=8;
                                    if (c3!=0 && c4!=0 && c1==0 && c2==0) curve=6;
                                    if (c1!=0 && c4!=0 && c2==0 && c3==0) curve=7;
                                    if (c2!=0 && c3!=0 && c1==0 && c4==0) curve=9;
                                    if (edge==0) {
                                        col_side1=image_plot.getPixel(x-x_off+5,    z-z_off+5);
                                        col_side2=image_plot.getPixel(x+x_off+5,    z-z_off+5);
                                        col_side3=image_plot.getPixel(x+x_off+5,    z+z_off+5);
                                        col_side4=image_plot.getPixel(x-x_off+5,    z+z_off+5);
                                        c1=(col_side1.r+col_side1.b+col_side1.g);
                                        c2=(col_side2.r+col_side2.b+col_side2.g);
                                        c3=(col_side3.r+col_side3.b+col_side3.g);
                                        c4=(col_side4.r+col_side4.b+col_side4.g);
                                        if (c1==0 || c2==0 || c3==0 || c4==0) edge=1;
                                        if (c1==0 && c2!=0 && c3!=0 && c4!=0) curve=8;
                                        if (c1!=0 && c2==0 && c3!=0 && c4!=0) curve=9;
                                        if (c1!=0 && c2!=0 && c3==0 && c4!=0) curve=6;
                                        if (c1!=0 && c2!=0 && c3!=0 && c4==0) curve=7;
                                    }
                                    if (curve!=0) corner2=1;
                                }

                                if ( y==(108-2+maze_offset) ) {
//                                if ( y==(108-2+maze_offset) || y==(115+2+maze_offset-maze_shrink) ) {
                                    sf::Color col_side1=image_plot3.getPixel(x-x_off+5,    z+5);
                                    sf::Color col_side2=image_plot3.getPixel(x+5,          z-z_off+5);
                                    sf::Color col_side3=image_plot3.getPixel(x+x_off+5,    z+5);
                                    sf::Color col_side4=image_plot3.getPixel(x+5,          z+z_off+5);
                                    c1=(col_side1.r+col_side1.b+col_side1.g);
                                    c2=(col_side2.r+col_side2.b+col_side2.g);
                                    c3=(col_side3.r+col_side3.b+col_side3.g);
                                    c4=(col_side4.r+col_side4.b+col_side4.g);
                                    if (c1==0 || c2==0 || c3==0 || c4==0) edge2=1;
                                    if ( y==(108-2+maze_offset)) {
                                        dir_x=0;
                                        curve=0;
                                        corner2=0;
                                        if (c1!=0 && c3!=0) dir_x=1+8;
                                        if (c2!=0 && c4!=0) dir_x=0+8;
                                        if (c1!=0 && c2!=0 && c3==0 && c4==0) curve=8;
                                        if (c3!=0 && c4!=0 && c1==0 && c2==0) curve=6;
                                        if (c1!=0 && c4!=0 && c2==0 && c3==0) curve=7;
                                        if (c2!=0 && c3!=0 && c1==0 && c4==0) curve=9;
                                    }

                                    if (edge2==0) {
                                        col_side1=image_plot3.getPixel(x-x_off+5,    z-z_off+5);
                                        col_side2=image_plot3.getPixel(x+x_off+5,    z-z_off+5);
                                        col_side3=image_plot3.getPixel(x+x_off+5,    z+z_off+5);
                                        col_side4=image_plot3.getPixel(x-x_off+5,    z+z_off+5);
                                        c1=(col_side1.r+col_side1.b+col_side1.g);
                                        c2=(col_side2.r+col_side2.b+col_side2.g);
                                        c3=(col_side3.r+col_side3.b+col_side3.g);
                                        c4=(col_side4.r+col_side4.b+col_side4.g);
                                        if (c1==0 || c2==0 || c3==0 || c4==0) {
                                            edge2=1;
                                        }
                                        if ( y==(108-2+maze_offset)) {
                                            if (c1==0 && c2!=0 && c3!=0 && c4!=0) curve=8;
                                            if (c1!=0 && c2==0 && c3!=0 && c4!=0) curve=9;
                                            if (c1!=0 && c2!=0 && c3==0 && c4!=0) curve=6;
                                            if (c1!=0 && c2!=0 && c3!=0 && c4==0) curve=7;
                                        }
                                    }
                                    if ( y==(108-2+maze_offset)) {
                                        if (curve!=0) corner2=1;
                                    }
                                }

                                if (y>=109-2+maze_offset && y<115+2+maze_offset-maze_shrink) {
                                    toggle2();
                                    if (pixel!=0) {
                                        if (edge==1) {
                                            if (red2==1) {
                                                if (AY[y].id==0 || AY[y].id==8) AY[y] = BlockInfo(95, 0, red,0 );
                                            }  else {
                                                if (rand()%30==0) {
                                                    AY[y] = BlockInfo(95, 0, ret_color(rand()%256,rand()%256,rand()%256),0 );
                                                } else {
                                                    if (AY[y].id==0 || AY[y].id==8) AY[y] = BlockInfo(95, 0, white,0 );
                                                }
                                            }
                                        } else {
//                                            if ( y==109-2+maze_offset && ((((int)xx+3)%5)==0 && (((int)zz+3)%5)==0))  {
//                                            if ( y==109-2+maze_offset && ((((int)xx+3)%5)==0 && (((int)zz+3)%5)==0) ) {
//                                                AY[y] = BlockInfo(147, 0, 0, 0 );
//                                            } else if ( y==109-2+maze_offset && AY[y].id!=147 && AY[108-2+maze_offset].id!=152) {
                                            if ( y==109-2+maze_offset && AY[y].id!=147 && AY[108-2+maze_offset].id!=152) {
                                                darkblue=sin(xx/40+zz/50) + sin(xx/50+zz/40) + sin(xx/70+zz/40) + sin(xx/60+zz/70) + sin(xx/70+zz/30) + sin(xx/30+zz/50);
                                                darkblue+=sin(xx/99+zz/110) + sin(xx/100+zz/90) + sin(xx/110+zz/100) + sin(xx/100+zz/110) + sin(xx/110+zz/99) + sin(xx/90+zz/110);
                                                darkblue+=(sin(xx/9+zz/10) + sin(xx/10+zz/9) + sin(xx/11+zz/11) + sin(xx/10+zz/12) + sin(xx/13+zz/14) + sin(xx/11+zz/17))/3;
                                                darkblue=((darkblue+14)/28)*15.9;
                                                AY[y] = BlockInfo(171, 0, (int)darkblue, 0 );
                                            } else if (AY[y].id!=147 && AY[y].id!=66 && AY[y].id!=27) {
                                                AY[y] = BlockInfo();
                                            }
                                        }
                                    }
                                }
                                else if (y==(115+2+maze_offset-maze_shrink)) {
                                    toggle2();
                                    if (pixel!=0) {
                                        if (edge==1) {
                                            if (corner2==1) {
                                                AY[y] = BlockInfo(251, 0, red, 0 );
                                                AY[y+1] = BlockInfo(66,0,curve,0);
                                            } else {
                                                if ( ((((int)xx+3)%15)==0 || (((int)zz+3)%15)==0) || ( col.r==254 && ( ((((int)xx+3)%5)==0 || (((int)zz+3)%5)==0) ) ) ) {
                                                    AY[y] = BlockInfo(152, 0, 0, 0 );
                                                    AY[y+1] = BlockInfo(27,0,dir_x,0);
                                                } else {
                                                    AY[y] = BlockInfo(251, 0, red, 0 );
                                                    AY[y+1] = BlockInfo(27,0,dir_x,0);
                                                }
                                            }
                                            rails++;
                                            AY[y+2]=BlockInfo();
                                            if (x>0            && AX[x-1][z][y+1].id!=27   && AX[x-1][z][y+1].id!=66  ) { AX[x-1][z][y+1]=BlockInfo(); AX[x-1][z][y+2]=BlockInfo(); }
                                            if (z>0            && AX[x][z-1][y+1].id!=27   && AX[x][z-1][y+1].id!=66  ) { AX[x][z-1][y+1]=BlockInfo(); AX[x][z-1][y+2]=BlockInfo(); }
                                            if (x<511          && AX[x+1][z][y+1].id!=27   && AX[x+1][z][y+1].id!=66  ) { AX[x+1][z][y+1]=BlockInfo(); AX[x+1][z][y+2]=BlockInfo(); }
                                            if (z<511          && AX[x][z+1][y+1].id!=27   && AX[x][z+1][y+1].id!=66  ) { AX[x][z+1][y+1]=BlockInfo(); AX[x][z+1][y+2]=BlockInfo(); }
                                            if (x>0 && z>0     && AX[x-1][z-1][y+1].id!=27 && AX[x-1][z-1][y+1].id!=66) { AX[x-1][z-1][y+1]=BlockInfo(); AX[x-1][z-1][y+2]=BlockInfo(); }
                                            if (z>0 && x<511   && AX[x+1][z-1][y+1].id!=27 && AX[x+1][z-1][y+1].id!=66) { AX[x+1][z-1][y+1]=BlockInfo(); AX[x+1][z-1][y+2]=BlockInfo(); }
                                            if (x<511 && z<511 && AX[x+1][z+1][y+1].id!=27 && AX[x+1][z+1][y+1].id!=66) { AX[x+1][z+1][y+1]=BlockInfo(); AX[x+1][z+1][y+2]=BlockInfo(); }
                                            if (z<511 && x>0   && AX[x-1][z+1][y+1].id!=27 && AX[x-1][z+1][y+1].id!=66) { AX[x-1][z+1][y+1]=BlockInfo(); AX[x-1][z+1][y+2]=BlockInfo(); }
                                            hoppa(AX,x,z,y);
//                                            AY[y+3]=BlockInfo();

                                        } else if ( ((((int)xx+3)%5)==0 && (((int)zz+3)%5)==0)) {
                                            AY[y] = BlockInfo(89, 0, 0, 0 );
                                        } else if (rand()%30==0) {
                                            AY[y] = BlockInfo(95, 0, ret_color(rand()%256,rand()%256,rand()%256),0 );
                                        } else {
                                            if (red2==1) {
                                                if (AY[y].id==0 || AY[y].id==8) AY[y] = BlockInfo(95, 0, red,0 );
                                            } else {
                                                if (AY[y].id==0 || AY[y].id==8) AY[y] = BlockInfo(95, 0, white,0 );
                                            }
                                        }
                                    }
                                } else if (y==(107-2+maze_offset)) {
                                    if (pixel!=0) {
                                        if (edge==0 &&
                                            (
                                                (((int)xx+2)%5)==0 && (((int)zz+2)%5)==0 ||
                                                (((int)xx+4)%5)==0 && (((int)zz+2)%5)==0 ||
                                                (((int)xx+4)%5)==0 && (((int)zz+4)%5)==0 ||
                                                (((int)xx+2)%5)==0 && (((int)zz+4)%5)==0 ||

                                                (((int)xx+2)%5)==0 && (((int)zz+3)%5)==0 ||
                                                (((int)xx+4)%5)==0 && (((int)zz+3)%5)==0 ||
                                                (((int)xx+3)%5)==0 && (((int)zz+2)%5)==0 ||
                                                (((int)xx+3)%5)==0 && (((int)zz+4)%5)==0
                                            ) ) {
//                                            AY[y] = BlockInfo(89, 0, 0, 0 );
                                            AY[107-2+maze_offset] = BlockInfo(95, 0, 0, 0 );
                                            }
                                    }
                                } else if (y==(108-2+maze_offset)) {
                                    if (pixel!=0) {

                                        if (edge==0 && (rand()%10)<3 &&
                                            (   (((int)xx+2)%5)==0 && (((int)zz+2)%5)==0 ||
                                                (((int)xx+4)%5)==0 && (((int)zz+2)%5)==0 ||
                                                (((int)xx+4)%5)==0 && (((int)zz+4)%5)==0 ||
                                                (((int)xx+2)%5)==0 && (((int)zz+4)%5)==0
                                            ) ) {
                                            AY[y] = BlockInfo(89, 0, 0, 0 );
                                        } else if ( ((((int)xx+3)%5)==0 && (((int)zz+3)%5)==0) && edge2==0) {
                                            int what=rand()%20;
                                            setBoom(region,x,z,y);
                                            AY[107-2+maze_offset] = BlockInfo(89, 0, 0, 0 );
//                                            AY[107-2+maze_offset] = BlockInfo(251, 0, 0, 0 );
                                            AY[109-2+maze_offset] = BlockInfo(147, 0, 0, 0 );
                                        } else if ((((int)xx+1+(rand()%5))%5)==0 && (((int)zz+1+(rand()%5))%5)==0 && edge==0 && edge2==0) {
                                            int what=rand()%18;
                                            if (what<15) setRabbits(region,x,z,y);
                                            else if (what<=16) setWolf(region,x,z,y);
                                            else if (what==17) setRandom(region,x,z,y);
                                            else { setBoom(region,x,z,y); /* AY[107-2] = BlockInfo(251, 0, 0, 0 );*/ }
                                            AY[109-2+maze_offset] = BlockInfo(147, 0, 0, 0 );
                                        } else if ((((int)xx+1+(rand()%5))%5)==0 && (((int)zz+1+(rand()%5))%5)==0 && edge==0 && edge2==0) {
                                            int what=rand()%18;
                                            if (what<15) setRabbits(region,x,z,y);
                                            else if (what<=16) setWolf(region,x,z,y);
                                            else if (what==17) setRandom(region,x,z,y);
                                            else { setBoom(region,x,z,y); /* AY[107-2] = BlockInfo(251, 0, 0, 0 );*/ }
                                            AY[109-2+maze_offset] = BlockInfo(147, 0, 0, 0 );
                                        } else if ((((int)xx+1+(rand()%5))%5)==0 && (((int)zz+1+(rand()%5))%5)==0 && edge==0 && edge2==0) {
                                            int what=rand()%18;
                                            if (what<15) setRabbits(region,x,z,y);
                                            else if (what<=16) setWolf(region,x,z,y);
                                            else if (what==17) setRandom(region,x,z,y);
                                            else { setBoom(region,x,z,y); /* AY[107-2] = BlockInfo(251, 0, 0, 0 );*/ }
                                            AY[109-2+maze_offset] = BlockInfo(147, 0, 0, 0 );
/*
                                        } else if ((((int)xx+1+(rand()%5))%5)==0 && (((int)zz+1+(rand()%5))%5)==0 && edge==0 && edge2==0) {
                                            int what=rand()%16;
                                            if (what<15) setRabbits(region,x,z,y);
                                            else if (what==15) setWolf(region,x,z,y);
                                            else if (what==16) setRandom(region,x,z,y);
                                            else { setBoom(region,x,z,y);  }
                                            AY[109-2+maze_offset] = BlockInfo(147, 0, 0, 0 );
                                        } else if ((((int)xx+1+(rand()%5))%5)==0 && (((int)zz+1+(rand()%5))%5)==0 && edge==0 && edge2==0) {
                                            int what=rand()%16;
                                            if (what<15) setRabbits(region,x,z,y);
                                            else if (what==15) setWolf(region,x,z,y);
                                            else if (what==16) setRandom(region,x,z,y);
                                            else { setBoom(region,x,z,y);  }
                                            AY[109-2+maze_offset] = BlockInfo(147, 0, 0, 0 );
*/
                                        } else {
                                            if (red2==1)
                                                AY[y] = BlockInfo(251, 0, red, 0 );
                                            else
                                                AY[y] = BlockInfo(251, 0, white,0 );
                                        }
                                    }
                                }
//                                else if (y==107-2+maze_offset && (((int)xx+3)%5)==0 && (((int)zz+3)%5)==0 && pixel!=0) { AY[y] = BlockInfo(251, 0, ret_color(rand()%256,rand()%256,rand()%256),0 );  }
//                                else if (y==107-2+maze_offset) {  if (pixel!=0 && (rand()%2)==0)      AY[y] = BlockInfo(251-((251-95)*(rand()%2)), 0, ret_color(rand()%256,rand()%256,rand()%256),0 );  }
                               if (AY[y].id==95 && AY[y].data==0)  AY[y]=BlockInfo(20,0,0,0);
                            }
                        }
                    }







                    if (mcglobal==2) {
                        vector<pair<Pos, string> > SomeStuff;

                        printf(" Coral:\b\b\b\b\b\b\b");
//printf("\n");
                        for (int x = 1; x < 511; x++) {
                            xx=x+chunk_offsetx*16;
                            for (int z = 1; z < 511; z++) {
                                zz=z+chunk_offsetz*16;
                                toggle2();
                                for (int y = 1; y < 248; y++) {
                                    if (AX[x][z][y].id==8) {
                                        int t=(int)(80.0+40.0*( (float)(rand()%20)/80.0 + sin((xx+sin(zz/15)*5)/(15.0+sin(zz/20.0)*5.0))+sin((zz+sin(xx/15)*5)/(15.0+sin((float)y/22.0)*5.0))+sin(((float)y+sin((zz+xx)/25)*5)/(15.0+sin(xx/23.0)*5.0)) )  );
                                        if (t<0) t=0;
                                        int t2=(int)(7.5+1.5*( (float)(rand()%((int)(1+(t)/30)))/80.0 + sin((xx+sin(zz/25)*5)/(15.0+sin(zz/30.0)*5.0))+sin((zz+sin(xx/25)*5)/(15.0+sin((float)y/32.0)*5.0))+sin(((float)y+sin((zz+xx)/45)*5)/(15.0+sin(xx/33.0)*5.0)) )  );
                                        if ( ((t<(15+t2*4) && (rand()%10)<(t2)) || ( rand()%(1+t )==0 && (rand()%25)<(t2) )) && t>(t2*3+t/20) ) {
                                            int allwater=1;
                                            for (int xxx=-1; xxx<2 && (allwater==1); xxx++) {
                                                for (int zzz=-1; zzz<2 && (allwater==1); zzz++) {
                                                    for (int yyy=-1; yyy<2 && (allwater==1); yyy++) {
                                                        if (!(xxx==0 && yyy==0 && zzz==0)) {
    //                                                        if (AX[x+xxx][z+zzz][y+yyy].id!=8 && !AX[x+xxx][z+zzz][y+yyy].id==0) allwater=0;
                                                            if ( AX[x+xxx][z+zzz][y+yyy].id!=8 && AX[x+xxx][z+zzz][y+yyy].id!=1000 && !AX[x+xxx][z+zzz][y+yyy].id==0) allwater=0;
                                                        }
                                                    }
                                                }
                                            }
                                            if (allwater==0) {
                                                if (!(rand()%30)) {
                                                    setExtra2(x,z,y,"glowstone",SomeStuff);   AX[x][z][y]=BlockInfo(1000,0,0,0);
//                                                    setExtra(x,z,y,"glowstone");   AX[x][z][y]=BlockInfo(1000,0,0,0);
                                                } else {
                                                    float some1=(10+3.25*(  (float)(rand()%25)/80.0 + sin((xx+sin(zz/43)*4.3+sin((float)y/73)*2)/(15.0+sin(zz/42.0+(float)y/99)*5.0))+sin((zz+sin((xx+(float)y/3)/43)*4)/(15.0+sin((float)y/42.0+(float)zz/92.0)*5.0))+sin(((float)y+sin((zz+xx)/47)*3)/(15.0+sin(xx/41.0)*450+sin(zz/71.0)*2.1)) ));
                                                    float some2=(10+3.25*(  (float)(rand()%((int)(some1+5)))/80.0 + sin((xx+sin(zz/120)*3.8)/(15.0+sin(zz/112.0)*5.0))+sin((zz+sin(xx/143)*4)/(15.0+sin((float)y/82.0)*5.0))+sin(((float)y+sin((zz+xx)/168)*3)/(15.0+sin(xx/101.0)*5.0)) ));
                                                    int flow;
                                                    flow = (   sin((xx+some2)/(83.23+some1*3) + sin((zz)/73.75)/3 )  +  sin((zz)/(39.75+some2) + sin(((float)y)/34.87)/7.1  )  )*5+10;
                                                    flow+= (sin((xx)/(94.23+some1*2) + sin((zz)/(57.75+flow))/2 )+sin(((float)y)/(26.75+some2/2) + sin((xx+flow/2)/45.87)/5.3 ))*1.25+2.5;
                                                    flow+= (   sin(((float)y+some2)/(62.23+some1*2.1) + sin((zz)/(54.75+flow))/2.9 )  +  sin(((float)y)/(64.75+some1*1.8) + sin((xx+flow/2)/47.87)/6.2  )  )*15+30;
                                                    int t=100+((86-flow)*some1+(flow)*some2)/80;

                                                    int what=t%64;
                                                    if (what==0 || what==0+8 || what== 7+8*2 || what==3+8*3 || what==3+8*4 || what==4+8*5 || what==5+8*6 || what==0+8*7) { setExtra2(x,z,y,"tube_coral_block",SomeStuff);   AX[x][z][y]=BlockInfo(1000,0,0,0); }
                                                    if (what==1 || what==1+8 || what== 6+8*2 || what==4+8*3 || what==7+8*4 || what==2+8*5 || what==4+8*6 || what==7+8*7) { setExtra2(x,z,y,"brain_coral_block",SomeStuff);  AX[x][z][y]=BlockInfo(1000,0,0,0); }
                                                    if (what==2 || what==4+8 || what== 1+8*2 || what==2+8*3 || what==2+8*4 || what==6+8*5 || what==6+8*6 || what==2+8*7) { setExtra2(x,z,y,"bubble_coral_block",SomeStuff); AX[x][z][y]=BlockInfo(1000,0,0,0); }
                                                    if (what==3 || what==3+8 || what== 2+8*2 || what==7+8*3 || what==4+8*4 || what==7+8*5 || what==7+8*6 || what==3+8*7) { setExtra2(x,z,y,"fire_coral_block",SomeStuff);   AX[x][z][y]=BlockInfo(1000,0,0,0); }
                                                    if (what==4 || what==7+8 || what== 4+8*2 || what==5+8*3 || what==6+8*4 || what==1+8*5 || what==3+8*6 || what==1+8*7) { setExtra2(x,z,y,"horn_coral_block",SomeStuff);   AX[x][z][y]=BlockInfo(1000,0,0,0); }
                                                    if (what==5 || what==5+8 || what== 5+8*2 || what==1+8*3 || what==5+8*4 || what==0+8*5 || what==2+8*6 || what==4+8*7) { AX[x][z][y]=BlockInfo(8,0,0,0); }
                                                    if (what==6 || what==6+8 || what== 0+8*2 || what==0+8*3 || what==0+8*4 || what==3+8*5 || what==1+8*6 || what==6+8*7) { AX[x][z][y]=BlockInfo(8,0,0,0); }
                                                    if (what==7 || what==2+8 || what== 3+8*2 || what==6+8*3 || what==1+8*4 || what==5+8*5 || what==0+8*6 || what==5+8*7) { AX[x][z][y]=BlockInfo(8,0,0,0); }

/*
                                                    if (what==0) { setExtra(x,z,y,"minecraft:tube_coral_block");   AX[x][z][y]=BlockInfo(1000,0,0,0); }
                                                    if (what==1) { setExtra(x,z,y,"minecraft:brain_coral_block");  AX[x][z][y]=BlockInfo(1000,0,0,0); }
                                                    if (what==2) { setExtra(x,z,y,"minecraft:bubble_coral_block"); AX[x][z][y]=BlockInfo(1000,0,0,0); }
                                                    if (what==3) { setExtra(x,z,y,"minecraft:fire_coral_block");   AX[x][z][y]=BlockInfo(1000,0,0,0); }
                                                    if (what==4) { setExtra(x,z,y,"minecraft:horn_coral_block");   AX[x][z][y]=BlockInfo(1000,0,0,0); }
*/
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        printf(" Coral:\b\b\b\b\b\b\b");
//printf("\n");
                        for (int x = 1; x < 511; x++) {
                            xx=x+chunk_offsetx*16;
                            for (int z = 1; z < 511; z++) {
                                zz=z+chunk_offsetz*16;
                                toggle2();
                                for (int y = 1; y < 248; y++) {
                                    if (AX[x][z][y].id==8) {
                                        int t=(int)(80.0+40.0*( (float)(rand()%20)/80.0 + sin((xx+sin(zz/15)*5)/(15.0+sin(zz/20.0)*5.0))+sin((zz+sin(xx/15)*5)/(15.0+sin((float)y/22.0)*5.0))+sin(((float)y+sin((zz+xx)/25)*5)/(15.0+sin(xx/23.0)*5.0)) )  );
                                        if (t<0) t=0;
                                        int t2=(int)(7.5+1.5*( (float)(rand()%((int)(1+(t)/30)))/80.0 + sin((xx+sin(zz/25)*5)/(15.0+sin(zz/30.0)*5.0))+sin((zz+sin(xx/25)*5)/(15.0+sin((float)y/32.0)*5.0))+sin(((float)y+sin((zz+xx)/45)*5)/(15.0+sin(xx/33.0)*5.0)) )  );
                                        if ( ((t<(25+t2*3) && (rand()%10)<(t2)) || ( rand()%(1+t )==0 && (rand()%20)<(t2) ) ) && t>(-10+t2*3+t/20) ) {
                                            int allwater=1;
                                            for (int xxx=-1; xxx<2 && (allwater==1); xxx++) {
                                                for (int zzz=-1; zzz<2 && (allwater==1); zzz++) {
                                                    for (int yyy=-1; yyy<2 && (allwater==1); yyy++) {
                                                        if (!(xxx==0 && yyy==0 && zzz==0)) {
    //                                                        if (AX[x+xxx][z+zzz][y+yyy].id!=8 && !AX[x+xxx][z+zzz][y+yyy].id==0) allwater=0;
                                                            if ( AX[x+xxx][z+zzz][y+yyy].id!=8 && AX[x+xxx][z+zzz][y+yyy].id!=1000 && !AX[x+xxx][z+zzz][y+yyy].id==0) allwater=0;
                                                        }
                                                    }
                                                }
                                            }
                                            if (allwater==0) {
                                                if (!(rand()%30)) {
//                                                    setExtra(x,z,y,"glowstone");   AX[x][z][y]=BlockInfo(1000,0,0,0);
                                                    setExtra2(x,z,y,"glowstone",SomeStuff);   AX[x][z][y]=BlockInfo(1000,0,0,0);
                                                } else {
                                                    float some1=(10+3.25*(  (float)(rand()%25)/80.0 + sin((xx+sin(zz/43)*4.3+sin((float)y/73)*2)/(15.0+sin(zz/42.0+(float)y/99)*5.0))+sin((zz+sin((xx+(float)y/3)/43)*4)/(15.0+sin((float)y/42.0+(float)zz/92.0)*5.0))+sin(((float)y+sin((zz+xx)/47)*3)/(15.0+sin(xx/41.0)*450+sin(zz/71.0)*2.1)) ));
                                                    float some2=(10+3.25*(  (float)(rand()%((int)(some1+5)))/80.0 + sin((xx+sin(zz/120)*3.8)/(15.0+sin(zz/112.0)*5.0))+sin((zz+sin(xx/143)*4)/(15.0+sin((float)y/82.0)*5.0))+sin(((float)y+sin((zz+xx)/168)*3)/(15.0+sin(xx/101.0)*5.0)) ));
                                                    int flow;
                                                    flow = (   sin((xx+some2)/(83.23+some1*3) + sin((zz)/73.75)/3 )  +  sin((zz)/(39.75+some2) + sin(((float)y)/34.87)/7.1  )  )*5+10;
                                                    flow+= (sin((xx)/(94.23+some1*2) + sin((zz)/(57.75+flow))/2 )+sin(((float)y)/(26.75+some2/2) + sin((xx+flow/2)/45.87)/5.3 ))*1.25+2.5;
                                                    flow+= (   sin(((float)y+some2)/(62.23+some1*2.1) + sin((zz)/(54.75+flow))/2.9 )  +  sin(((float)y)/(64.75+some1*1.8) + sin((xx+flow/2)/47.87)/6.2  )  )*15+30;
                                                    int t=100+((86-flow)*some1+(flow)*some2)/80;

//                                                    int t=(int)(10+3.25*(  (float)(rand()%25)/80.0 + sin((xx+sin(zz/43)*4)/(15.0+sin(zz/42.0)*5.0))+sin((zz+sin(xx/43)*4)/(15.0+sin((float)y/42.0)*5.0))+sin(((float)y+sin((zz+xx)/47)*3)/(15.0+sin(xx/41.0)*5.0)) ));
                                                    int what=t%64;
                                                    if (what==0 || what==0+8 || what== 7+8*2 || what==3+8*3 || what==3+8*4 || what==4+8*5 || what==5+8*6 || what==0+8*7){ setExtra2(x,z,y,"tube_coral_block",SomeStuff);   AX[x][z][y]=BlockInfo(1001,0,0,0); }
                                                    if (what==1 || what==1+8 || what== 6+8*2 || what==4+8*3 || what==7+8*4 || what==2+8*5 || what==4+8*6 || what==7+8*7){ setExtra2(x,z,y,"brain_coral_block",SomeStuff);  AX[x][z][y]=BlockInfo(1001,0,0,0); }
                                                    if (what==2 || what==4+8 || what== 1+8*2 || what==2+8*3 || what==2+8*4 || what==6+8*5 || what==6+8*6 || what==2+8*7){ setExtra2(x,z,y,"bubble_coral_block",SomeStuff); AX[x][z][y]=BlockInfo(1001,0,0,0); }
                                                    if (what==3 || what==3+8 || what== 2+8*2 || what==7+8*3 || what==4+8*4 || what==7+8*5 || what==7+8*6 || what==3+8*7){ setExtra2(x,z,y,"fire_coral_block",SomeStuff);   AX[x][z][y]=BlockInfo(1001,0,0,0); }
                                                    if (what==4 || what==7+8 || what== 4+8*2 || what==5+8*3 || what==6+8*4 || what==1+8*5 || what==3+8*6 || what==1+8*7){ setExtra2(x,z,y,"horn_coral_block",SomeStuff);   AX[x][z][y]=BlockInfo(1001,0,0,0); }
                                                    if (what==5 || what==5+8 || what== 5+8*2 || what==1+8*3 || what==5+8*4 || what==0+8*5 || what==2+8*6 || what==4+8*7){ AX[x][z][y]=BlockInfo(8,0,0,0); }
                                                    if (what==6 || what==6+8 || what== 0+8*2 || what==0+8*3 || what==0+8*4 || what==3+8*5 || what==1+8*6 || what==6+8*7){ AX[x][z][y]=BlockInfo(8,0,0,0); }
                                                    if (what==7 || what==2+8 || what== 3+8*2 || what==6+8*3 || what==1+8*4 || what==5+8*5 || what==0+8*6 || what==5+8*7){ AX[x][z][y]=BlockInfo(8,0,0,0); }
 /*
                                                    if (what==0) { setExtra(x,z,y,"minecraft:tube_coral_block");   AX[x][z][y]=BlockInfo(1001,0,0,0); }
                                                    if (what==1) { setExtra(x,z,y,"minecraft:brain_coral_block");  AX[x][z][y]=BlockInfo(1001,0,0,0); }
                                                    if (what==2) { setExtra(x,z,y,"minecraft:bubble_coral_block"); AX[x][z][y]=BlockInfo(1001,0,0,0); }
                                                    if (what==3) { setExtra(x,z,y,"minecraft:fire_coral_block");   AX[x][z][y]=BlockInfo(1001,0,0,0); }
                                                    if (what==4) { setExtra(x,z,y,"minecraft:horn_coral_block");   AX[x][z][y]=BlockInfo(1001,0,0,0); }
*/
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        printf(" Coral:\b\b\b\b\b\b\b");
//printf("\n");
                        for (int x = 1; x < 511; x++) {
                            xx=x+chunk_offsetx*16;
                            for (int z = 1; z < 511; z++) {
                                zz=z+chunk_offsetz*16;
                                toggle2();
                                for (int y = 1; y < 248; y++) {
                                    if (AX[x][z][y].id==8) {
                                        int t=(int)(80.0+40.0*( (float)(rand()%20)/80.0 + sin((xx+sin(zz/15)*5)/(15.0+sin(zz/20.0)*5.0))+sin((zz+sin(xx/15)*5)/(15.0+sin((float)y/22.0)*5.0))+sin(((float)y+sin((zz+xx)/25)*5)/(15.0+sin(xx/23.0)*5.0)) )  );
                                        if (t<0) t=0;
                                        int t2=(int)(7.5+1.5*( (float)(rand()%((int)(1+(t)/30)))/80.0 + sin((xx+sin(zz/25)*5)/(15.0+sin(zz/30.0)*5.0))+sin((zz+sin(xx/25)*5)/(15.0+sin((float)y/32.0)*5.0))+sin(((float)y+sin((zz+xx)/45)*5)/(15.0+sin(xx/33.0)*5.0)) )  );
                                        if (( (t<(40+t2*2) && (rand()%10)<(t2)) || ( rand()%(1+t )==0 && (rand()%15)<(t2) ) ) && t>(-15+t2*3+t/20)) {
                                            int allwater=1;
                                            for (int xxx=-1; xxx<2 && (allwater==1); xxx++) {
                                                for (int zzz=-1; zzz<2 && (allwater==1); zzz++) {
                                                    for (int yyy=-1; yyy<2 && (allwater==1); yyy++) {
                                                        if (!(xxx==0 && yyy==0 && zzz==0)) {
    //                                                        if (AX[x+xxx][z+zzz][y+yyy].id!=8 && !AX[x+xxx][z+zzz][y+yyy].id==0) allwater=0;
                                                            if ( AX[x+xxx][z+zzz][y+yyy].id!=8 && AX[x+xxx][z+zzz][y+yyy].id!=1000 && !AX[x+xxx][z+zzz][y+yyy].id==0) allwater=0;
                                                        }
                                                    }
                                                }
                                            }
                                            if (allwater==0) {
                                                if (!(rand()%30)) {
                                                    setExtra2(x,z,y,"glowstone",SomeStuff);   AX[x][z][y]=BlockInfo(1000,0,0,0);
//                                                    setExtra(x,z,y,"minecraft:glowstone");   AX[x][z][y]=BlockInfo(1000,0,0,0);
                                                } else {
                                                    float some1=(10+3.25*(  (float)(rand()%25)/80.0 + sin((xx+sin(zz/43)*4.3+sin((float)y/73)*2)/(15.0+sin(zz/42.0+(float)y/99)*5.0))+sin((zz+sin((xx+(float)y/3)/43)*4)/(15.0+sin((float)y/42.0+(float)zz/92.0)*5.0))+sin(((float)y+sin((zz+xx)/47)*3)/(15.0+sin(xx/41.0)*450+sin(zz/71.0)*2.1)) ));
                                                    float some2=(10+3.25*(  (float)(rand()%((int)(some1+5)))/80.0 + sin((xx+sin(zz/120)*3.8)/(15.0+sin(zz/112.0)*5.0))+sin((zz+sin(xx/143)*4)/(15.0+sin((float)y/82.0)*5.0))+sin(((float)y+sin((zz+xx)/168)*3)/(15.0+sin(xx/101.0)*5.0)) ));
                                                    int flow;
                                                    flow = (   sin((xx+some2)/(83.23+some1*3) + sin((zz)/73.75)/3 )  +  sin((zz)/(39.75+some2) + sin(((float)y)/34.87)/7.1  )  )*5+10;
                                                    flow+= (sin((xx)/(94.23+some1*2) + sin((zz)/(57.75+flow))/2 )+sin(((float)y)/(26.75+some2/2) + sin((xx+flow/2)/45.87)/5.3 ))*1.25+2.5;
                                                    flow+= (   sin(((float)y+some2)/(62.23+some1*2.1) + sin((zz)/(54.75+flow))/2.9 )  +  sin(((float)y)/(64.75+some1*1.8) + sin((xx+flow/2)/47.87)/6.2  )  )*15+30;
                                                    int t=100+((86-flow)*some1+(flow)*some2)/80;

//                                                    int t=(int)(10+3.25*(  (float)(rand()%25)/80.0 + sin((xx+sin(zz/43)*4)/(15.0+sin(zz/42.0)*5.0))+sin((zz+sin(xx/43)*4)/(15.0+sin((float)y/42.0)*5.0))+sin(((float)y+sin((zz+xx)/47)*3)/(15.0+sin(xx/41.0)*5.0)) ));
                                                    int what=t%64;
                                                    if (what==0 || what==0+8 || what== 7+8*2 || what==3+8*3 || what==3+8*4 || what==4+8*5 || what==5+8*6 || what==0+8*7) { setExtra2(x,z,y,"tube_coral_block",SomeStuff);   AX[x][z][y]=BlockInfo(1002,0,0,0); }
                                                    if (what==1 || what==1+8 || what== 6+8*2 || what==4+8*3 || what==7+8*4 || what==2+8*5 || what==4+8*6 || what==7+8*7) { setExtra2(x,z,y,"brain_coral_block",SomeStuff);  AX[x][z][y]=BlockInfo(1002,0,0,0); }
                                                    if (what==2 || what==4+8 || what== 1+8*2 || what==2+8*3 || what==2+8*4 || what==6+8*5 || what==6+8*6 || what==2+8*7) { setExtra2(x,z,y,"bubble_coral_block",SomeStuff); AX[x][z][y]=BlockInfo(1002,0,0,0); }
                                                    if (what==3 || what==3+8 || what== 2+8*2 || what==7+8*3 || what==4+8*4 || what==7+8*5 || what==7+8*6 || what==3+8*7) { setExtra2(x,z,y,"fire_coral_block",SomeStuff);   AX[x][z][y]=BlockInfo(1002,0,0,0); }
                                                    if (what==4 || what==7+8 || what== 4+8*2 || what==5+8*3 || what==6+8*4 || what==1+8*5 || what==3+8*6 || what==1+8*7) { setExtra2(x,z,y,"horn_coral_block",SomeStuff);   AX[x][z][y]=BlockInfo(1002,0,0,0); }
                                                    if (what==5 || what==5+8 || what== 5+8*2 || what==1+8*3 || what==5+8*4 || what==0+8*5 || what==2+8*6 || what==4+8*7) { AX[x][z][y]=BlockInfo(8,0,0,0); }
                                                    if (what==6 || what==6+8 || what== 0+8*2 || what==0+8*3 || what==0+8*4 || what==3+8*5 || what==1+8*6 || what==6+8*7) { AX[x][z][y]=BlockInfo(8,0,0,0); }
                                                    if (what==7 || what==2+8 || what== 3+8*2 || what==6+8*3 || what==1+8*4 || what==5+8*5 || what==0+8*6 || what==5+8*7) { AX[x][z][y]=BlockInfo(8,0,0,0); }
/*
                                                    if (what==0) { setExtra(x,z,y,"minecraft:tube_coral_block");   AX[x][z][y]=BlockInfo(1002,0,0,0); }
                                                    if (what==1) { setExtra(x,z,y,"minecraft:brain_coral_block");  AX[x][z][y]=BlockInfo(1002,0,0,0); }
                                                    if (what==2) { setExtra(x,z,y,"minecraft:bubble_coral_block"); AX[x][z][y]=BlockInfo(1002,0,0,0); }
                                                    if (what==3) { setExtra(x,z,y,"minecraft:fire_coral_block");   AX[x][z][y]=BlockInfo(1002,0,0,0); }
                                                    if (what==4) { setExtra(x,z,y,"minecraft:horn_coral_block");   AX[x][z][y]=BlockInfo(1002,0,0,0); }
*/
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }

                        for (int x = 0; x < 512; x++) {
                            BlockInfo** AZ=AX[x];
                            for (int z = 0; z < 512; z++) {
                                BlockInfo* AY=AZ[z];
                                toggle2();
                                for (int y = 0; y < yl; y++) {
                                    if (  AY[y].id>=1000 && AY[y].id<=1004) {
                                        AY[y] = BlockInfo(8,0,0);
                                    }
                                }
                            }
                        }

//printf("\n");




                        printf(" Kelp:\b\b\b\b\b\b");
                        for (int x = 0; x < 512; x++) {
                            xx=x+chunk_offsetx*16;
                            for (int z = 0; z < 512; z++) {
                                zz=z+chunk_offsetz*16;
                                toggle2();
                                for (int y = 1; y < 248; y++) {
                                    if (AX[x][z][y].id==8 && AX[x][z][y-1].id!=8 && AX[x][z][y].id!=1003 && AX[x][z][y-1].id!=1003) {
                                        int t=(int)(10.0+4.0*( (float)(rand()%20)/80.0 + sin((xx+sin(zz/24)*10)/(16.0+sin(zz/20.0)*5.0))+sin((zz+sin(xx/26)*8)/(16.0+sin((float)y/22.0)*5.0))+sin(((float)y+sin((zz+xx)/44)*8)/(17.0+sin(xx/23.0)*5.0)) )  );
                                        if (t<0) t=0;
                                        if (   rand()%(1+t ) == 0 ) {
                                            char what[100];
                                            sprintf(what,"kelp[age=%d]",rand()%25);
                                            setExtra2(x,z,y,what,SomeStuff);
//                                            setExtra(x,z,y,what);
                                            AX[x][z][y]=BlockInfo(1003,0,0,0);
                                        }
                                    }
                                }
                            }
                        }
//printf("\n");
                        printf(" Coral:\b\b\b\b\b\b\b");
                        for (int x = 1; x < 511; x++) {
                            xx=x+chunk_offsetx*16;
                            for (int z = 1; z < 511; z++) {
                                zz=z+chunk_offsetz*16;
                                toggle2();
                                for (int y = 1; y < 248; y++) {
                                    if (AX[x][z][y].id==8) {
                                        int t=(int)(50.0+20.0*( (float)(rand()%20)/80.0 + sin((xx+sin(zz/17)*5)/(15.0+sin(zz/22.0)*5.0))+sin((zz+sin(xx/17)*5)/(15.0+sin((float)y/22.0)*5.0))+sin(((float)y+sin((zz+xx)/28)*5)/(15.0+sin(xx/23.0)*5.0)) )  );
                                        if (t<0) t=0;
                                        if ( (t<50 && (rand()%10)<5) || rand()%(1+t ) == 0 ) {
                                            int wall=0;
                                            for (int xxx=-1; xxx<2 && (wall==0); xxx++) {
                                                for (int zzz=-1; zzz<2 && (wall==0); zzz++) {
                                                    if (AX[x+xxx][z+zzz][y].id!=8 && AX[x+xxx][z+zzz][y].id!=1003 && AX[x+xxx][z+zzz][y].id!=1004 && !AX[x+xxx][z+zzz][y].id==0) wall=1;
                                                }
                                            }
                                            if (wall==1 && (rand()%2)==0) {
                                                int t=(int)(10+3.25*(  (float)(rand()%25)/80.0 + sin((xx+sin(zz/43)*4)/(15.0+sin(zz/42.0)*5.0))+sin((zz+sin(xx/43)*4)/(15.0+sin((float)y/42.0)*5.0))+sin(((float)y+sin((zz+xx)/47)*3)/(15.0+sin(xx/41.0)*5.0)) ));
                                                int what=t%5;
                                                if (what==0) { setExtra2(x,z,y,"tube_coral_fan",SomeStuff);  AX[x][z][y]=BlockInfo(1004,0,0,0); }
                                                if (what==1) { setExtra2(x,z,y,"brain_coral_fan",SomeStuff); AX[x][z][y]=BlockInfo(1004,0,0,0); }
                                                if (what==2) { setExtra2(x,z,y,"bubble_coral_fan",SomeStuff);AX[x][z][y]=BlockInfo(1004,0,0,0); }
                                                if (what==3) { setExtra2(x,z,y,"fire_coral_fan",SomeStuff);  AX[x][z][y]=BlockInfo(1004,0,0,0); }
                                                if (what==4) { setExtra2(x,z,y,"horn_coral_fan",SomeStuff);  AX[x][z][y]=BlockInfo(1004,0,0,0); }
/*
                                                if (what==0) { setExtra(x,z,y,"minecraft:tube_coral_fan");  AX[x][z][y]=BlockInfo(1004,0,0,0); }
                                                if (what==1) { setExtra(x,z,y,"minecraft:brain_coral_fan"); AX[x][z][y]=BlockInfo(1004,0,0,0); }
                                                if (what==2) { setExtra(x,z,y,"minecraft:bubble_coral_fan");AX[x][z][y]=BlockInfo(1004,0,0,0); }
                                                if (what==3) { setExtra(x,z,y,"minecraft:fire_coral_fan");  AX[x][z][y]=BlockInfo(1004,0,0,0); }
                                                if (what==4) { setExtra(x,z,y,"minecraft:horn_coral_fan");  AX[x][z][y]=BlockInfo(1004,0,0,0); }
*/
                                            } else if (AX[x][z][y-1].id!=8 && AX[x][z][y].id!=1003 && AX[x][z][y].id!=1004 && AX[x][z][y-1].id!=1003 && AX[x][z][y-1].id!=1004 ) {
                                                int t=(int)(10+3.25*(  (float)(rand()%25)/80.0 + sin((xx+sin(zz/43)*4)/(15.0+sin(zz/42.0)*5.0))+sin((zz+sin(xx/43)*4)/(15.0+sin((float)y/42.0)*5.0))+sin(((float)y+sin((zz+xx)/47)*3)/(15.0+sin(xx/41.0)*5.0)) ));
                                                int what=t%5;
                                                if (what==0) { setExtra2(x,z,y,"tube_coral",SomeStuff);  AX[x][z][y]=BlockInfo(1004,0,0,0); }
                                                if (what==1) { setExtra2(x,z,y,"brain_coral",SomeStuff); AX[x][z][y]=BlockInfo(1004,0,0,0); }
                                                if (what==2) { setExtra2(x,z,y,"bubble_coral",SomeStuff);AX[x][z][y]=BlockInfo(1004,0,0,0); }
                                                if (what==3) { setExtra2(x,z,y,"fire_coral",SomeStuff);  AX[x][z][y]=BlockInfo(1004,0,0,0); }
                                                if (what==4) { setExtra2(x,z,y,"horn_coral",SomeStuff);  AX[x][z][y]=BlockInfo(1004,0,0,0); }
/*
                                                if (what==0) { setExtra(x,z,y,"minecraft:tube_coral");   AX[x][z][y]=BlockInfo(1004,0,0,0); }
                                                if (what==1) { setExtra(x,z,y,"minecraft:brain_coral");  AX[x][z][y]=BlockInfo(1004,0,0,0); }
                                                if (what==2) { setExtra(x,z,y,"minecraft:bubble_coral"); AX[x][z][y]=BlockInfo(1004,0,0,0); }
                                                if (what==3) { setExtra(x,z,y,"minecraft:fire_coral");   AX[x][z][y]=BlockInfo(1004,0,0,0); }
                                                if (what==4) { setExtra(x,z,y,"minecraft:horn_coral");   AX[x][z][y]=BlockInfo(1004,0,0,0); }
*/
                                            }
                                        }
                                    }
                                }
                            }
                        }

                        printf(" Coral:\b\b\b\b\b\b\b");
                        for (int x = 1; x < 511; x++) {
                            xx=x+chunk_offsetx*16;
                            for (int z = 1; z < 511; z++) {
                                zz=z+chunk_offsetz*16;
                                toggle2();
                                for (int y = 1; y < 248; y++) {
                                    if (AX[x][z][y].id==8) {
                                        int t=(int)(80.0+40.0*( (float)(rand()%20)/80.0 + sin((xx+sin(zz/15)*5)/(15.0+sin(zz/20.0)*5.0))+sin((zz+sin(xx/15)*5)/(15.0+sin((float)y/22.0)*5.0))+sin(((float)y+sin((zz+xx)/25)*5)/(15.0+sin(xx/23.0)*5.0)) )  );
                                        if (t<0) t=0;
                                        int t2=(int)(7.5+1.5*( (float)(rand()%((int)(1+(t)/30)))/80.0 + sin((xx+sin(zz/25)*5)/(15.0+sin(zz/30.0)*5.0))+sin((zz+sin(xx/25)*5)/(15.0+sin((float)y/32.0)*5.0))+sin(((float)y+sin((zz+xx)/45)*5)/(15.0+sin(xx/33.0)*5.0)) )  );
                                        if ( ((t<(15+t2*4) && (rand()%10)<(t2)) || ( rand()%(1+t )==0 && (rand()%25)<(t2) )) && t>(-15+t2*3+t/20) ) {
                                            int wall=0;
                                            for (int xxx=-1; xxx<2 && (wall==0); xxx++) {
                                                for (int zzz=-1; zzz<2 && (wall==0); zzz++) {
                                                    if (AX[x+xxx][z+zzz][y].id!=8 && AX[x+xxx][z+zzz][y].id!=1003 && AX[x+xxx][z+zzz][y].id!=1004 && !AX[x+xxx][z+zzz][y].id==0) wall=1;
                                                }
                                            }
                                            if (wall==1 && (rand()%2)==0) {
                                                float some1=(10+3.25*(  (float)(rand()%25)/80.0 + sin((xx+sin(zz/43)*4.3+sin((float)y/73)*2)/(15.0+sin(zz/42.0+(float)y/99)*5.0))+sin((zz+sin((xx+(float)y/3)/43)*4)/(15.0+sin((float)y/42.0+(float)zz/92.0)*5.0))+sin(((float)y+sin((zz+xx)/47)*3)/(15.0+sin(xx/41.0)*450+sin(zz/71.0)*2.1)) ));
                                                float some2=(10+3.25*(  (float)(rand()%((int)(some1+5)))/80.0 + sin((xx+sin(zz/120)*3.8)/(15.0+sin(zz/112.0)*5.0))+sin((zz+sin(xx/143)*4)/(15.0+sin((float)y/82.0)*5.0))+sin(((float)y+sin((zz+xx)/168)*3)/(15.0+sin(xx/101.0)*5.0)) ));
                                                int flow;
                                                flow = (   sin((xx+some2)/(83.23+some1*3) + sin((zz)/73.75)/3 )  +  sin((zz)/(39.75+some2) + sin(((float)y)/34.87)/7.1  )  )*5+10;
                                                flow+= (sin((xx)/(94.23+some1*2) + sin((zz)/(57.75+flow))/2 )+sin(((float)y)/(26.75+some2/2) + sin((xx+flow/2)/45.87)/5.3 ))*1.25+2.5;
                                                flow+= (   sin(((float)y+some2)/(62.23+some1*2.1) + sin((zz)/(54.75+flow))/2.9 )  +  sin(((float)y)/(64.75+some1*1.8) + sin((xx+flow/2)/47.87)/6.2  )  )*15+30;
                                                int t=100+((86-flow)*some1+(flow)*some2)/80;
                                                int what=t%30;
                                                what=rand()%64;
                                                if (what==0 || what==0+8 || what== 7+8*2 || what==3+8*3 || what==3+8*4 || what==4+8*5 || what==5+8*6 || what==0+8*7) { setExtra2(x,z,y,"tube_coral_fan",SomeStuff);  AX[x][z][y]=BlockInfo(1004,0,0,0); }
                                                if (what==1 || what==1+8 || what== 6+8*2 || what==4+8*3 || what==7+8*4 || what==2+8*5 || what==4+8*6 || what==7+8*7) { setExtra2(x,z,y,"brain_coral_fan",SomeStuff); AX[x][z][y]=BlockInfo(1004,0,0,0); }
                                                if (what==2 || what==4+8 || what== 1+8*2 || what==2+8*3 || what==2+8*4 || what==6+8*5 || what==6+8*6 || what==2+8*7) { setExtra2(x,z,y,"bubble_coral_fan",SomeStuff);AX[x][z][y]=BlockInfo(1004,0,0,0); }
                                                if (what==3 || what==3+8 || what== 2+8*2 || what==7+8*3 || what==4+8*4 || what==7+8*5 || what==7+8*6 || what==3+8*7) { setExtra2(x,z,y,"fire_coral_fan",SomeStuff);  AX[x][z][y]=BlockInfo(1004,0,0,0); }
                                                if (what==4 || what==7+8 || what== 4+8*2 || what==5+8*3 || what==6+8*4 || what==1+8*5 || what==3+8*6 || what==1+8*7) { setExtra2(x,z,y,"horn_coral_fan",SomeStuff);  AX[x][z][y]=BlockInfo(1004,0,0,0); }
//                                                if (what==5 || what==5+8 || what== 5+8*2 || what==1+8*3 || what==5+8*4 || what==0+8*5 || what==2+8*6 || what==4+8*7)
//                                                if (what==6 || what==6+8 || what== 0+8*2 || what==0+8*3 || what==0+8*4 || what==3+8*5 || what==1+8*6 || what==6+8*7)
//                                                if (what==7 || what==2+8 || what== 3+8*2 || what==6+8*3 || what==1+8*4 || what==5+8*5 || what==0+8*6 || what==5+8*7)


/*
                                                if (what==0) { setExtra(x,z,y,"minecraft:tube_coral_fan");  AX[x][z][y]=BlockInfo(1004,0,0,0); }
                                                if (what==1) { setExtra(x,z,y,"minecraft:brain_coral_fan"); AX[x][z][y]=BlockInfo(1004,0,0,0); }
                                                if (what==2) { setExtra(x,z,y,"minecraft:bubble_coral_fan");AX[x][z][y]=BlockInfo(1004,0,0,0); }
                                                if (what==3) { setExtra(x,z,y,"minecraft:fire_coral_fan");  AX[x][z][y]=BlockInfo(1004,0,0,0); }
                                                if (what==4) { setExtra(x,z,y,"minecraft:horn_coral_fan");  AX[x][z][y]=BlockInfo(1004,0,0,0); }
*/
                                            } else if (AX[x][z][y-1].id!=8 && AX[x][z][y].id!=1003 && AX[x][z][y].id!=1004 && AX[x][z][y-1].id!=1003 && AX[x][z][y-1].id!=1004 ) {
                                                float some1=(10+3.25*(  (float)(rand()%25)/80.0 + sin((xx+sin(zz/43)*4.3+sin((float)y/73)*2)/(15.0+sin(zz/42.0+(float)y/99)*5.0))+sin((zz+sin((xx+(float)y/3)/43)*4)/(15.0+sin((float)y/42.0+(float)zz/92.0)*5.0))+sin(((float)y+sin((zz+xx)/47)*3)/(15.0+sin(xx/41.0)*450+sin(zz/71.0)*2.1)) ));
                                                float some2=(10+3.25*(  (float)(rand()%((int)(some1+5)))/80.0 + sin((xx+sin(zz/120)*3.8)/(15.0+sin(zz/112.0)*5.0))+sin((zz+sin(xx/143)*4)/(15.0+sin((float)y/82.0)*5.0))+sin(((float)y+sin((zz+xx)/168)*3)/(15.0+sin(xx/101.0)*5.0)) ));
                                                int flow;
                                                flow = (   sin((xx+some2)/(83.23+some1*3) + sin((zz)/73.75)/3 )  +  sin((zz)/(39.75+some2) + sin(((float)y)/34.87)/7.1  )  )*5+10;
                                                flow+= (sin((xx)/(94.23+some1*2) + sin((zz)/(57.75+flow))/2 )+sin(((float)y)/(26.75+some2/2) + sin((xx+flow/2)/45.87)/5.3 ))*1.25+2.5;
                                                flow+= (   sin(((float)y+some2)/(62.23+some1*2.1) + sin((zz)/(54.75+flow))/2.9 )  +  sin(((float)y)/(64.75+some1*1.8) + sin((xx+flow/2)/47.87)/6.2  )  )*15+30;
                                                int t=100+((86-flow)*some1+(flow)*some2)/80;
                                                int what=t%30;
                                                if (what==5 || what==9  || what==15 || what==18 || what==26) what=rand()%30;
                                                if (what==0 || what==8  || what==16 || what==21 || what==25) { setExtra2(x,z,y,"tube_coral",SomeStuff);  AX[x][z][y]=BlockInfo(1004,0,0,0); }
                                                if (what==1 || what==11 || what==17 || what==22 || what==29) { setExtra2(x,z,y,"brain_coral",SomeStuff); AX[x][z][y]=BlockInfo(1004,0,0,0); }
                                                if (what==2 || what==10 || what==13 || what==19 || what==28) { setExtra2(x,z,y,"bubble_coral",SomeStuff);AX[x][z][y]=BlockInfo(1004,0,0,0); }
                                                if (what==3 || what==7  || what==14 || what==23 || what==24) { setExtra2(x,z,y,"fire_coral",SomeStuff);  AX[x][z][y]=BlockInfo(1004,0,0,0); }
                                                if (what==4 || what==6  || what==12 || what==20 || what==27) { setExtra2(x,z,y,"horn_coral",SomeStuff);  AX[x][z][y]=BlockInfo(1004,0,0,0); }
/*
                                                if (what==0) { setExtra(x,z,y,"minecraft:tube_coral");   AX[x][z][y]=BlockInfo(1004,0,0,0); }
                                                if (what==1) { setExtra(x,z,y,"minecraft:brain_coral");  AX[x][z][y]=BlockInfo(1004,0,0,0); }
                                                if (what==2) { setExtra(x,z,y,"minecraft:bubble_coral"); AX[x][z][y]=BlockInfo(1004,0,0,0); }
                                                if (what==3) { setExtra(x,z,y,"minecraft:fire_coral");   AX[x][z][y]=BlockInfo(1004,0,0,0); }
                                                if (what==4) { setExtra(x,z,y,"minecraft:horn_coral");   AX[x][z][y]=BlockInfo(1004,0,0,0); }
*/
                                            }
                                        } else if (t<=(t2*3+t/20) && !(rand()%100)) {
                                            Pos position(region.x_ori + x+chunk_offsetx*16, region.z_ori + z+chunk_offsetz*16, region.y_ori + y);
                                            Pos position2(region.x_ori + x, region.z_ori + z, region.y_ori + y);
                                            MobEntity* mob;
                                            mob = new MobEntity(position, "minecraft:tropical_fish");
                                            editor.mca_coder.insertEntity(position2, mob);
                                            delete mob;
                                        }
                                    }
                                }
                            }
                        }
//printf("\n");
                        printf(" Planter:\b\b\b\b\b\b\b\b\b");


                        makeExtra2(region,SomeStuff);
//                        makeExtra(region);
//printf("\n");

                        printf(" Fish:\b\b\b\b\b\b");
//printf("\n");

                        for (int x = 0; x < 512; x++) {
                            xx=x+chunk_offsetx*16;
                            BlockInfo** AZ=AX[x];
                            for (int z = 0; z < 512; z++) {
                                zz=z+chunk_offsetz*16;
                                BlockInfo* AY=AZ[z];
                                toggle2();
                                for (int y = 0; y < yl; y++) {
                                    if (  AY[y].id==8) {
                                        if (rand()%10000==0) {
                                            int fish=rand()%7;
                                            if (!rand()%4) fish=rand()%4;
                                            if (!rand()%6) fish=rand()%4;
                                            Pos position(region.x_ori + x+chunk_offsetx*16, region.z_ori + z+chunk_offsetz*16, region.y_ori + y);
                                            Pos position2(region.x_ori + x, region.z_ori + z, region.y_ori + y);
                                            MobEntity* mob;
                                            if (fish==0) mob = new MobEntity(position, "minecraft:turtle");
                                            else if (fish==1) mob = new MobEntity(position, "minecraft:tropical_fish");
                                            else if (fish==2) mob = new MobEntity(position, "minecraft:pufferfish");
                                            else if (fish==3) mob = new MobEntity(position, "minecraft:dolphin");
                                            else if (fish==4) mob = new MobEntity(position, "minecraft:squid");
                                            else if (fish==5) mob = new MobEntity(position, "minecraft:salmon");
                                            else if (fish==6) mob = new MobEntity(position, "minecraft:cod");
                                            else if (fish==7) mob = new MobEntity(position, "minecraft:guardian");
                                            else if (fish==8) mob = new MobEntity(position, "minecraft:elder_guardian");
                                            editor.mca_coder.insertEntity(position2, mob);
                                            if (fish==1) {
                                                for (int t=0; t<(rand()%20); t++) editor.mca_coder.insertEntity(position2, mob);
                                            }
                                            delete mob;
                                        } else if (rand()%15000==0) {
                                            MobEntity* mob;
                                            Pos position(region.x_ori + x+chunk_offsetx*16, region.z_ori + z+chunk_offsetz*16, region.y_ori + y);
                                            Pos position2(region.x_ori + x, region.z_ori + z, region.y_ori + y);
                                            mob = new MobEntity(position, "minecraft:dolphin");
                                            editor.mca_coder.insertEntity(position2, mob);
                                            delete mob;
                                        } else if (rand()%1500000==0) {
                                            int fish=rand()%2;
                                            Pos position(region.x_ori + x+chunk_offsetx*16, region.z_ori + z+chunk_offsetz*16, region.y_ori + y);
                                            Pos position2(region.x_ori + x, region.z_ori + z, region.y_ori + y);
                                            MobEntity* mob;
                                            if (fish==0) mob = new MobEntity(position, "minecraft:guardian");
                                            else if (fish==1) mob = new MobEntity(position, "minecraft:elder_guardian");
                                            editor.mca_coder.insertEntity(position2, mob);
                                            delete mob;
                                        }
                                    }
                                }
                            }
                        }

                        for (int x = 0; x < 512; x++) {
                            BlockInfo** AZ=AX[x];
                            for (int z = 0; z < 512; z++) {
                                BlockInfo* AY=AZ[z];
                                toggle2();
                                for (int y = 0; y < yl; y++) {
                                    if (  AY[y].id>=1000 && AY[y].id<=1004) {
                                        AY[y] = BlockInfo(8,0,0);
                                    }
                                }
                            }
                        }
                    }











                    printf(" %d blocks = %5.2f%, #rails added = %d, #rails total = %d = %7.3f kilometers\n",num_blocks,100.0*(float)num_blocks/(1024*1024*64),rails,rails_tot,(float)rails_tot/1000);
                    rails=0;
                    rails_tot=0;
                    if (mcglobal==2 && num_command_blocks!=0) {
                        printf("#Command blocks=%d, #commands=%d, average=%d commands/block. ",num_command_blocks, num_com, (int)((float)num_com/(float)num_command_blocks));
                    }
                } else {
                }


                printf(" ");
                first_MCEDIT=0;
                region_x_old=0;
                region_z_old=0;

                if (mcglobal==1) {
                    mkdir("/Saves/test/region/done1");
                    char tmp[256];
                    sprintf(tmp, "/Saves/Test/region/done1/r.%d.%d.mca", region_x, region_z);
                    file_name_MCA=tmp;
                    editor.setRegion(region);
                    char tmp2[256];
                    mkdir("/Saves/test/region/done0/done");
                    sprintf(tmp, "/Saves/Test/region/done0/r.%d.%d.mca", region_x, region_z);
                    sprintf(tmp2, "/Saves/Test/region/done0/done/r.%d.%d.mca", region_x, region_z);
                    rename(tmp,tmp2);
                    CopyFile(tmp,fname.c_str(),false);
                } else if (mcglobal=2) {
                    mkdir("/Saves/test/region/done2");
                    char tmp[256];
                    sprintf(tmp, "/Saves/Test/region/done2/r.%d.%d.mca", region_x, region_z);
                    file_name_MCA=tmp;
                    editor.setRegion(region);
                    char tmp2[256];
                    mkdir("/Saves/test/region/done1/done");
                    sprintf(tmp, "/Saves/Test/region/done1/r.%d.%d.mca", region_x, region_z);
                    sprintf(tmp2, "/Saves/Test/region/done1/done/r.%d.%d.mca", region_x, region_z);
                    rename(tmp,tmp2);
                    CopyFile(tmp,fname.c_str(),false);
                } else {
                    file_name_MCA = MCAFileNameXZ(region_x, region_z);
                    editor.setRegion(region);
                }

//                printf(" Ready\n");
                if (MCEDITOR_stop==1 || file_exists("stop.txt")) {
                    printf("Stop requested, exiting\n");
//                    system("/saves/copy_test.bat");
                    send_message='x';
                    return 0;
                }
//                printf(" end loop\n");

//                printf("4) size_regions=%d, Region=%d,%d\n",size_regions,region_x,region_z);
            }
//            printf("5) size_regions=%d, Region=%d,%d\n",size_regions,region_x,region_z);
        }
//        printf("6) size_regions=%d, Region=%d,%d\n",size_regions,region_x,region_z);
    }
//    printf("7) size_regions=%d, Region=%d,%d\n",size_regions,region_x,region_z);
    send_message='x';
    return 0;
}



int jump_ready=1;

int read_request=0;
sf::Image* read_image;
int read_x,read_y;

void read_one_plot_WINMAIN(int x, int y, sf::Image* image) {
    MUTEX_MCEDITOR.lock();

    read_image=image;
    read_x=x;
    read_y=y;
    read_request=1;

    while (read_request==1) {
        MUTEX_MCEDITOR.unlock(); sf::sleep(sf::milliseconds(10)); MUTEX_MCEDITOR.lock();
    }
    MUTEX_MCEDITOR.unlock();

    return;
}

void make_mirror(sf::Image* image) {
//    printf("Mirroring\n");
    int x=image->getSize().x;
    int y=image->getSize().y;
    sf::Image img;
    img.create(x,y);
    img.copy(*image,0,0);
    sf::Color col;
    for (int yy=0; yy<y; yy++) {
        for (int xx=0; xx<x; xx++) {
//            printf("image->setPixel(%d,%d,img.getPixel(%d,%d))\n",xx,yy,x-xx-1,y-yy-1);
            image->setPixel(xx,yy,img.getPixel(x-xx-1,y-yy-1));
        }
    }

    return;
}

void hoppa2(BlockInfo*** AX, int x, int z, int y) {
    for (int xxx=-1; xxx<2; xxx++) {
        for (int zzz=-1; zzz<2; zzz++) {
            for (int yyy=-1; yyy<2; yyy++) {
                if (in_region(x+xxx, z+zzz, y+yyy, 0, 0, 11, xl , zl , yl-5)) {
                    if (AX[x+xxx][z+zzz][y+yyy].id==8) {
                        AX[x+xxx][z+zzz][y+yyy]=BlockInfo(95, 0, 0, 0);
                    }
                }
            }
        }
    }
}

void hoppa(BlockInfo*** AX, int x, int z, int y) {
    hoppa2(AX,x-1,z  ,y+1); hoppa2(AX,x-1,z  ,y+2);
    hoppa2(AX,x  ,z-1,y+1); hoppa2(AX,x  ,z-1,y+2);
    hoppa2(AX,x+1,z  ,y+1); hoppa2(AX,x+1,z  ,y+2);
    hoppa2(AX,x  ,z+1,y+1); hoppa2(AX,x  ,z+1,y+2);
    hoppa2(AX,x-1,z-1,y+1); hoppa2(AX,x-1,z-1,y+2);
    hoppa2(AX,x+1,z-1,y+1); hoppa2(AX,x+1,z-1,y+2);
    hoppa2(AX,x+1,z+1,y+1); hoppa2(AX,x+1,z+1,y+2);
    hoppa2(AX,x-1,z+1,y+1); hoppa2(AX,x-1,z+1,y+2);
}
/*
OOOOO OOOOO OOOOO OOOOO OOOOO OOO OOOOO OOOOO OOOOO OOOOO OOOOO
O   O O   O O   O O   O O   O O O O   O O   O O   O O   O O   O
OOO OOO OOO OOO OOO OOO OOO OOO OOO OOO OOO OOO OOO OOO OOO OOO
  O     O     O     O     O         O     O     O     O     O
OOO OOO O OOO O OOO OOO OOO OOO OOO OOO OOO OOO O OOO O OOO OOO
O   O O O O O O O O   O O   O O O O   O O   O O O O O O O O   O
OOOOO O OOO OOO O OOOOO OOOOO O O OOOOO OOOOO O OOO OOO O OOOOO
      O         O             O O             O         O
OOOOO O OOO OOO OOO OOOOOOO OOO OOO OOOOOOO OOO OOO OOO O OOOOO
O   O O O O O O   O O     O O     O O     O O   O O O O O O   O
OOO OOO O OOO O OOO OOO OOO OOO OOO OOO OOO OOO O OOO O OOO OOO
  O     O     O O     O O     O O     O O     O O     O     O
OOO OOO OOO OOO O OOO O O OOO O O OOO O O OOO O OOO OOO OOO OOO
O   O O   O O   O O O O O O O O O O O O O O O O   O O   O O   O
OOOOO OOOOO OOO OOO OOO OOO OOO OOO OOO OOO OOO OOO OOOOO OOOOO
              O                                 O
OOOOO OOOOO OOO OOO OOO OOO OOO OOO OOO OOO OOO OOO OOOOO OOOOO
O   O O   O O   O O O O O O O O O O O O O O O O   O O   O O   O
OOO OOO OOO OOO O OOO O O OOO O O OOO O O OOO O OOO OOO OOO OOO
  O     O     O O     O O     O O     O O     O O     O     O
OOO OOO O OOO O OOO OOO OOO OOO OOO OOO OOO OOO O OOO O OOO OOO
O   O O O O O O   O O     O O     O O     O O   O O O O O O   O
OOOOO O OOO OOO OOO OOOOOOO OOO OOO OOOOOOO OOO OOO OOO O OOOOO
      O         O             O O             O         O
OOOOO O OOO OOO O OOOOO OOOOO O O OOOOO OOOOO O OOO OOO O OOOOO
O   O O O O O O O O   O O   O O O O   O O   O O O O O O O O   O
OOO OOO O OOO O OOO OOO OOO OOO OOO OOO OOO OOO O OOO O OOO OOO
  O     O     O     O     O         O     O     O     O     O
OOO OOO OOO OOO OOO OOO OOO OOO OOO OOO OOO OOO OOO OOO OOO OOO
O   O O   O O   O O   O O   O O O O   O O   O O   O O   O O   O
OOOOO OOOOO OOOOO OOOOO OOOOO O O OOOOO OOOOO OOOOO OOOOO OOOOO
                              O O
OOOOO OOOOO OOOOO OOOOO OOOOO O O OOOOO OOOOO OOOOO OOOOO OOOOO
O   O O   O O   O O   O O   O O O O   O O   O O   O O   O O   O
OOO OOO OOO OOO OOO OOO OOO OOO OOO OOO OOO OOO OOO OOO OOO OOO
  O     O     O     O     O         O     O     O     O     O
OOO OOO O OOO O OOO OOO OOO OOO OOO OOO OOO OOO O OOO O OOO OOO
O   O O O O O O O O   O O   O O O O   O O   O O O O O O O O   O
OOOOO O OOO OOO O OOOOO OOOOO O O OOOOO OOOOO O OOO OOO O OOOOO
      O         O             O O             O         O
OOOOO O OOO OOO OOO OOOOOOO OOO OOO OOOOOOO OOO OOO OOO O OOOOO
O   O O O O O O   O O     O O     O O     O O   O O O O O O   O
OOO OOO O OOO O OOO OOO OOO OOO OOO OOO OOO OOO O OOO O OOO OOO
  O     O     O O     O O     O O     O O     O O     O     O
OOO OOO OOO OOO O OOO O O OOO O O OOO O O OOO O OOO OOO OOO OOO
O   O O   O O   O O O O O O O O O O O O O O O O   O O   O O   O
OOOOO OOOOO OOO OOO OOO OOO OOO OOO OOO OOO OOO OOO OOOOO OOOOO
              O                                 O
OOOOO OOOOO OOO OOO OOO OOO OOO OOO OOO OOO OOO OOO OOOOO OOOOO
O   O O   O O   O O O O O O O O O O O O O O O O   O O   O O   O
OOO OOO OOO OOO O OOO O O OOO O O OOO O O OOO O OOO OOO OOO OOO
  O     O     O O     O O     O O     O O     O O     O     O
OOO OOO O OOO O OOO OOO OOO OOO OOO OOO OOO OOO O OOO O OOO OOO
O   O O O O O O   O O     O O     O O     O O   O O O O O O   O
OOOOO O OOO OOO OOO OOOOOOO OOO OOO OOOOOOO OOO OOO OOO O OOOOO
      O         O             O O             O         O
OOOOO O OOO OOO O OOOOO OOOOO O O OOOOO OOOOO O OOO OOO O OOOOO
O   O O O O O O O O   O O   O O O O   O O   O O O O O O O O   O
OOO OOO O OOO O OOO OOO OOO OOO OOO OOO OOO OOO O OOO O OOO OOO
  O     O     O     O     O         O     O     O     O     O
OOO OOO OOO OOO OOO OOO OOO OOO OOO OOO OOO OOO OOO OOO OOO OOO
O   O O   O O   O O   O O   O O O O   O O   O O   O O   O O   O
OOOOO OOOOO OOOOO OOOOO OOOOO OOO OOOOO OOOOO OOOOO OOOOO OOOOO
*/











void fill_chunk_list() {
//start in middle, upper left quadrant first, ending at 15,16
    int n=0;
    chunk_list[n][0]=15;chunk_list[n++][1]=15;
    chunk_list[n][0]=15;chunk_list[n++][1]=14;
    chunk_list[n][0]=14;chunk_list[n++][1]=14;
    chunk_list[n][0]=14;chunk_list[n++][1]=15;
    chunk_list[n][0]=13;chunk_list[n++][1]=15;
    chunk_list[n][0]=12;chunk_list[n++][1]=15;
    chunk_list[n][0]=12;chunk_list[n++][1]=14;
    chunk_list[n][0]=13;chunk_list[n++][1]=14;
    chunk_list[n][0]=13;chunk_list[n++][1]=13;
    chunk_list[n][0]=12;chunk_list[n++][1]=13;
    chunk_list[n][0]=12;chunk_list[n++][1]=12;
    chunk_list[n][0]=13;chunk_list[n++][1]=12;
    chunk_list[n][0]=14;chunk_list[n++][1]=12;
    chunk_list[n][0]=14;chunk_list[n++][1]=13;
    chunk_list[n][0]=15;chunk_list[n++][1]=13;
    chunk_list[n][0]=15;chunk_list[n++][1]=12;
    chunk_list[n][0]=15;chunk_list[n++][1]=11;
    chunk_list[n][0]=14;chunk_list[n++][1]=11;
    chunk_list[n][0]=14;chunk_list[n++][1]=10;
    chunk_list[n][0]=15;chunk_list[n++][1]=10;
    chunk_list[n][0]=15;chunk_list[n++][1]=9;
    chunk_list[n][0]=15;chunk_list[n++][1]=8;
    chunk_list[n][0]=14;chunk_list[n++][1]=8;
    chunk_list[n][0]=14;chunk_list[n++][1]=9;
    chunk_list[n][0]=13;chunk_list[n++][1]=9;
    chunk_list[n][0]=13;chunk_list[n++][1]=8;
    chunk_list[n][0]=12;chunk_list[n++][1]=8;
    chunk_list[n][0]=12;chunk_list[n++][1]=9;
    chunk_list[n][0]=12;chunk_list[n++][1]=10;
    chunk_list[n][0]=13;chunk_list[n++][1]=10;
    chunk_list[n][0]=13;chunk_list[n++][1]=11;
    chunk_list[n][0]=12;chunk_list[n++][1]=11;
    chunk_list[n][0]=11;chunk_list[n++][1]=11;
    chunk_list[n][0]=10;chunk_list[n++][1]=11;
    chunk_list[n][0]=10;chunk_list[n++][1]=10;
    chunk_list[n][0]=11;chunk_list[n++][1]=10;
    chunk_list[n][0]=11;chunk_list[n++][1]=9;
    chunk_list[n][0]=11;chunk_list[n++][1]=8;
    chunk_list[n][0]=10;chunk_list[n++][1]=8;
    chunk_list[n][0]=10;chunk_list[n++][1]=9;
    chunk_list[n][0]=9;chunk_list[n++][1]=9;
    chunk_list[n][0]=9;chunk_list[n++][1]=8;
    chunk_list[n][0]=8;chunk_list[n++][1]=8;
    chunk_list[n][0]=8;chunk_list[n++][1]=9;
    chunk_list[n][0]=8;chunk_list[n++][1]=10;
    chunk_list[n][0]=9;chunk_list[n++][1]=10;
    chunk_list[n][0]=9;chunk_list[n++][1]=11;
    chunk_list[n][0]=8;chunk_list[n++][1]=11;
    chunk_list[n][0]=8;chunk_list[n++][1]=12;
    chunk_list[n][0]=8;chunk_list[n++][1]=13;
    chunk_list[n][0]=9;chunk_list[n++][1]=13;
    chunk_list[n][0]=9;chunk_list[n++][1]=12;
    chunk_list[n][0]=10;chunk_list[n++][1]=12;
    chunk_list[n][0]=11;chunk_list[n++][1]=12;
    chunk_list[n][0]=11;chunk_list[n++][1]=13;
    chunk_list[n][0]=10;chunk_list[n++][1]=13;
    chunk_list[n][0]=10;chunk_list[n++][1]=14;
    chunk_list[n][0]=11;chunk_list[n++][1]=14;
    chunk_list[n][0]=11;chunk_list[n++][1]=15;
    chunk_list[n][0]=10;chunk_list[n++][1]=15;
    chunk_list[n][0]=9;chunk_list[n++][1]=15;
    chunk_list[n][0]=9;chunk_list[n++][1]=14;
    chunk_list[n][0]=8;chunk_list[n++][1]=14;
    chunk_list[n][0]=8;chunk_list[n++][1]=15;
    chunk_list[n][0]=7;chunk_list[n++][1]=15;
    chunk_list[n][0]=6;chunk_list[n++][1]=15;
    chunk_list[n][0]=6;chunk_list[n++][1]=14;
    chunk_list[n][0]=7;chunk_list[n++][1]=14;
    chunk_list[n][0]=7;chunk_list[n++][1]=13;
    chunk_list[n][0]=7;chunk_list[n++][1]=12;
    chunk_list[n][0]=6;chunk_list[n++][1]=12;
    chunk_list[n][0]=6;chunk_list[n++][1]=13;
    chunk_list[n][0]=5;chunk_list[n++][1]=13;
    chunk_list[n][0]=5;chunk_list[n++][1]=12;
    chunk_list[n][0]=4;chunk_list[n++][1]=12;
    chunk_list[n][0]=4;chunk_list[n++][1]=13;
    chunk_list[n][0]=4;chunk_list[n++][1]=14;
    chunk_list[n][0]=5;chunk_list[n++][1]=14;
    chunk_list[n][0]=5;chunk_list[n++][1]=15;
    chunk_list[n][0]=4;chunk_list[n++][1]=15;
    chunk_list[n][0]=3;chunk_list[n++][1]=15;
    chunk_list[n][0]=3;chunk_list[n++][1]=14;
    chunk_list[n][0]=2;chunk_list[n++][1]=14;
    chunk_list[n][0]=2;chunk_list[n++][1]=15;
    chunk_list[n][0]=1;chunk_list[n++][1]=15;
    chunk_list[n][0]=0;chunk_list[n++][1]=15;
    chunk_list[n][0]=0;chunk_list[n++][1]=14;
    chunk_list[n][0]=1;chunk_list[n++][1]=14;
    chunk_list[n][0]=1;chunk_list[n++][1]=13;
    chunk_list[n][0]=0;chunk_list[n++][1]=13;
    chunk_list[n][0]=0;chunk_list[n++][1]=12;
    chunk_list[n][0]=1;chunk_list[n++][1]=12;
    chunk_list[n][0]=2;chunk_list[n++][1]=12;
    chunk_list[n][0]=2;chunk_list[n++][1]=13;
    chunk_list[n][0]=3;chunk_list[n++][1]=13;
    chunk_list[n][0]=3;chunk_list[n++][1]=12;
    chunk_list[n][0]=3;chunk_list[n++][1]=11;
    chunk_list[n][0]=3;chunk_list[n++][1]=10;
    chunk_list[n][0]=2;chunk_list[n++][1]=10;
    chunk_list[n][0]=2;chunk_list[n++][1]=11;
    chunk_list[n][0]=1;chunk_list[n++][1]=11;
    chunk_list[n][0]=0;chunk_list[n++][1]=11;
    chunk_list[n][0]=0;chunk_list[n++][1]=10;
    chunk_list[n][0]=1;chunk_list[n++][1]=10;
    chunk_list[n][0]=1;chunk_list[n++][1]=9;
    chunk_list[n][0]=0;chunk_list[n++][1]=9;
    chunk_list[n][0]=0;chunk_list[n++][1]=8;
    chunk_list[n][0]=1;chunk_list[n++][1]=8;
    chunk_list[n][0]=2;chunk_list[n++][1]=8;
    chunk_list[n][0]=2;chunk_list[n++][1]=9;
    chunk_list[n][0]=3;chunk_list[n++][1]=9;
    chunk_list[n][0]=3;chunk_list[n++][1]=8;
    chunk_list[n][0]=4;chunk_list[n++][1]=8;
    chunk_list[n][0]=5;chunk_list[n++][1]=8;
    chunk_list[n][0]=5;chunk_list[n++][1]=9;
    chunk_list[n][0]=4;chunk_list[n++][1]=9;
    chunk_list[n][0]=4;chunk_list[n++][1]=10;
    chunk_list[n][0]=4;chunk_list[n++][1]=11;
    chunk_list[n][0]=5;chunk_list[n++][1]=11;
    chunk_list[n][0]=5;chunk_list[n++][1]=10;
    chunk_list[n][0]=6;chunk_list[n++][1]=10;
    chunk_list[n][0]=6;chunk_list[n++][1]=11;
    chunk_list[n][0]=7;chunk_list[n++][1]=11;
    chunk_list[n][0]=7;chunk_list[n++][1]=10;
    chunk_list[n][0]=7;chunk_list[n++][1]=9;
    chunk_list[n][0]=6;chunk_list[n++][1]=9;
    chunk_list[n][0]=6;chunk_list[n++][1]=8;
    chunk_list[n][0]=7;chunk_list[n++][1]=8;
    chunk_list[n][0]=7;chunk_list[n++][1]=7;
    chunk_list[n][0]=6;chunk_list[n++][1]=7;
    chunk_list[n][0]=6;chunk_list[n++][1]=6;
    chunk_list[n][0]=7;chunk_list[n++][1]=6;
    chunk_list[n][0]=7;chunk_list[n++][1]=5;
    chunk_list[n][0]=7;chunk_list[n++][1]=4;
    chunk_list[n][0]=6;chunk_list[n++][1]=4;
    chunk_list[n][0]=6;chunk_list[n++][1]=5;
    chunk_list[n][0]=5;chunk_list[n++][1]=5;
    chunk_list[n][0]=5;chunk_list[n++][1]=4;
    chunk_list[n][0]=4;chunk_list[n++][1]=4;
    chunk_list[n][0]=4;chunk_list[n++][1]=5;
    chunk_list[n][0]=4;chunk_list[n++][1]=6;
    chunk_list[n][0]=5;chunk_list[n++][1]=6;
    chunk_list[n][0]=5;chunk_list[n++][1]=7;
    chunk_list[n][0]=4;chunk_list[n++][1]=7;
    chunk_list[n][0]=3;chunk_list[n++][1]=7;
    chunk_list[n][0]=3;chunk_list[n++][1]=6;
    chunk_list[n][0]=2;chunk_list[n++][1]=6;
    chunk_list[n][0]=2;chunk_list[n++][1]=7;
    chunk_list[n][0]=1;chunk_list[n++][1]=7;
    chunk_list[n][0]=0;chunk_list[n++][1]=7;
    chunk_list[n][0]=0;chunk_list[n++][1]=6;
    chunk_list[n][0]=1;chunk_list[n++][1]=6;
    chunk_list[n][0]=1;chunk_list[n++][1]=5;
    chunk_list[n][0]=0;chunk_list[n++][1]=5;
    chunk_list[n][0]=0;chunk_list[n++][1]=4;
    chunk_list[n][0]=1;chunk_list[n++][1]=4;
    chunk_list[n][0]=2;chunk_list[n++][1]=4;
    chunk_list[n][0]=2;chunk_list[n++][1]=5;
    chunk_list[n][0]=3;chunk_list[n++][1]=5;
    chunk_list[n][0]=3;chunk_list[n++][1]=4;
    chunk_list[n][0]=3;chunk_list[n++][1]=3;
    chunk_list[n][0]=3;chunk_list[n++][1]=2;
    chunk_list[n][0]=2;chunk_list[n++][1]=2;
    chunk_list[n][0]=2;chunk_list[n++][1]=3;
    chunk_list[n][0]=1;chunk_list[n++][1]=3;
    chunk_list[n][0]=0;chunk_list[n++][1]=3;
    chunk_list[n][0]=0;chunk_list[n++][1]=2;
    chunk_list[n][0]=1;chunk_list[n++][1]=2;
    chunk_list[n][0]=1;chunk_list[n++][1]=1;
    chunk_list[n][0]=0;chunk_list[n++][1]=1;
    chunk_list[n][0]=0;chunk_list[n++][1]=0;
    chunk_list[n][0]=1;chunk_list[n++][1]=0;
    chunk_list[n][0]=2;chunk_list[n++][1]=0;
    chunk_list[n][0]=2;chunk_list[n++][1]=1;
    chunk_list[n][0]=3;chunk_list[n++][1]=1;
    chunk_list[n][0]=3;chunk_list[n++][1]=0;
    chunk_list[n][0]=4;chunk_list[n++][1]=0;
    chunk_list[n][0]=5;chunk_list[n++][1]=0;
    chunk_list[n][0]=5;chunk_list[n++][1]=1;
    chunk_list[n][0]=4;chunk_list[n++][1]=1;
    chunk_list[n][0]=4;chunk_list[n++][1]=2;
    chunk_list[n][0]=4;chunk_list[n++][1]=3;
    chunk_list[n][0]=5;chunk_list[n++][1]=3;
    chunk_list[n][0]=5;chunk_list[n++][1]=2;
    chunk_list[n][0]=6;chunk_list[n++][1]=2;
    chunk_list[n][0]=6;chunk_list[n++][1]=3;
    chunk_list[n][0]=7;chunk_list[n++][1]=3;
    chunk_list[n][0]=7;chunk_list[n++][1]=2;
    chunk_list[n][0]=7;chunk_list[n++][1]=1;
    chunk_list[n][0]=6;chunk_list[n++][1]=1;
    chunk_list[n][0]=6;chunk_list[n++][1]=0;
    chunk_list[n][0]=7;chunk_list[n++][1]=0;
    chunk_list[n][0]=8;chunk_list[n++][1]=0;
    chunk_list[n][0]=8;chunk_list[n++][1]=1;
    chunk_list[n][0]=9;chunk_list[n++][1]=1;
    chunk_list[n][0]=9;chunk_list[n++][1]=0;
    chunk_list[n][0]=10;chunk_list[n++][1]=0;
    chunk_list[n][0]=11;chunk_list[n++][1]=0;
    chunk_list[n][0]=11;chunk_list[n++][1]=1;
    chunk_list[n][0]=10;chunk_list[n++][1]=1;
    chunk_list[n][0]=10;chunk_list[n++][1]=2;
    chunk_list[n][0]=11;chunk_list[n++][1]=2;
    chunk_list[n][0]=11;chunk_list[n++][1]=3;
    chunk_list[n][0]=10;chunk_list[n++][1]=3;
    chunk_list[n][0]=9;chunk_list[n++][1]=3;
    chunk_list[n][0]=9;chunk_list[n++][1]=2;
    chunk_list[n][0]=8;chunk_list[n++][1]=2;
    chunk_list[n][0]=8;chunk_list[n++][1]=3;
    chunk_list[n][0]=8;chunk_list[n++][1]=4;
    chunk_list[n][0]=9;chunk_list[n++][1]=4;
    chunk_list[n][0]=9;chunk_list[n++][1]=5;
    chunk_list[n][0]=8;chunk_list[n++][1]=5;
    chunk_list[n][0]=8;chunk_list[n++][1]=6;
    chunk_list[n][0]=8;chunk_list[n++][1]=7;
    chunk_list[n][0]=9;chunk_list[n++][1]=7;
    chunk_list[n][0]=9;chunk_list[n++][1]=6;
    chunk_list[n][0]=10;chunk_list[n++][1]=6;
    chunk_list[n][0]=10;chunk_list[n++][1]=7;
    chunk_list[n][0]=11;chunk_list[n++][1]=7;
    chunk_list[n][0]=11;chunk_list[n++][1]=6;
    chunk_list[n][0]=11;chunk_list[n++][1]=5;
    chunk_list[n][0]=10;chunk_list[n++][1]=5;
    chunk_list[n][0]=10;chunk_list[n++][1]=4;
    chunk_list[n][0]=11;chunk_list[n++][1]=4;
    chunk_list[n][0]=12;chunk_list[n++][1]=4;
    chunk_list[n][0]=13;chunk_list[n++][1]=4;
    chunk_list[n][0]=13;chunk_list[n++][1]=5;
    chunk_list[n][0]=12;chunk_list[n++][1]=5;
    chunk_list[n][0]=12;chunk_list[n++][1]=6;
    chunk_list[n][0]=12;chunk_list[n++][1]=7;
    chunk_list[n][0]=13;chunk_list[n++][1]=7;
    chunk_list[n][0]=13;chunk_list[n++][1]=6;
    chunk_list[n][0]=14;chunk_list[n++][1]=6;
    chunk_list[n][0]=14;chunk_list[n++][1]=7;
    chunk_list[n][0]=15;chunk_list[n++][1]=7;
    chunk_list[n][0]=15;chunk_list[n++][1]=6;
    chunk_list[n][0]=15;chunk_list[n++][1]=5;
    chunk_list[n][0]=14;chunk_list[n++][1]=5;
    chunk_list[n][0]=14;chunk_list[n++][1]=4;
    chunk_list[n][0]=15;chunk_list[n++][1]=4;
    chunk_list[n][0]=15;chunk_list[n++][1]=3;
    chunk_list[n][0]=15;chunk_list[n++][1]=2;
    chunk_list[n][0]=14;chunk_list[n++][1]=2;
    chunk_list[n][0]=14;chunk_list[n++][1]=3;
    chunk_list[n][0]=13;chunk_list[n++][1]=3;
    chunk_list[n][0]=12;chunk_list[n++][1]=3;
    chunk_list[n][0]=12;chunk_list[n++][1]=2;
    chunk_list[n][0]=13;chunk_list[n++][1]=2;
    chunk_list[n][0]=13;chunk_list[n++][1]=1;
    chunk_list[n][0]=12;chunk_list[n++][1]=1;
    chunk_list[n][0]=12;chunk_list[n++][1]=0;
    chunk_list[n][0]=13;chunk_list[n++][1]=0;
    chunk_list[n][0]=14;chunk_list[n++][1]=0;
    chunk_list[n][0]=14;chunk_list[n++][1]=1;
    chunk_list[n][0]=15;chunk_list[n++][1]=1;
    chunk_list[n][0]=15;chunk_list[n++][1]=0;
    chunk_list[n][0]=16;chunk_list[n++][1]=0;
    chunk_list[n][0]=16;chunk_list[n++][1]=1;
    chunk_list[n][0]=17;chunk_list[n++][1]=1;
    chunk_list[n][0]=17;chunk_list[n++][1]=0;
    chunk_list[n][0]=18;chunk_list[n++][1]=0;
    chunk_list[n][0]=19;chunk_list[n++][1]=0;
    chunk_list[n][0]=19;chunk_list[n++][1]=1;
    chunk_list[n][0]=18;chunk_list[n++][1]=1;
    chunk_list[n][0]=18;chunk_list[n++][1]=2;
    chunk_list[n][0]=19;chunk_list[n++][1]=2;
    chunk_list[n][0]=19;chunk_list[n++][1]=3;
    chunk_list[n][0]=18;chunk_list[n++][1]=3;
    chunk_list[n][0]=17;chunk_list[n++][1]=3;
    chunk_list[n][0]=17;chunk_list[n++][1]=2;
    chunk_list[n][0]=16;chunk_list[n++][1]=2;
    chunk_list[n][0]=16;chunk_list[n++][1]=3;
    chunk_list[n][0]=16;chunk_list[n++][1]=4;
    chunk_list[n][0]=17;chunk_list[n++][1]=4;
    chunk_list[n][0]=17;chunk_list[n++][1]=5;
    chunk_list[n][0]=16;chunk_list[n++][1]=5;
    chunk_list[n][0]=16;chunk_list[n++][1]=6;
    chunk_list[n][0]=16;chunk_list[n++][1]=7;
    chunk_list[n][0]=17;chunk_list[n++][1]=7;
    chunk_list[n][0]=17;chunk_list[n++][1]=6;
    chunk_list[n][0]=18;chunk_list[n++][1]=6;
    chunk_list[n][0]=18;chunk_list[n++][1]=7;
    chunk_list[n][0]=19;chunk_list[n++][1]=7;
    chunk_list[n][0]=19;chunk_list[n++][1]=6;
    chunk_list[n][0]=19;chunk_list[n++][1]=5;
    chunk_list[n][0]=18;chunk_list[n++][1]=5;
    chunk_list[n][0]=18;chunk_list[n++][1]=4;
    chunk_list[n][0]=19;chunk_list[n++][1]=4;
    chunk_list[n][0]=20;chunk_list[n++][1]=4;
    chunk_list[n][0]=21;chunk_list[n++][1]=4;
    chunk_list[n][0]=21;chunk_list[n++][1]=5;
    chunk_list[n][0]=20;chunk_list[n++][1]=5;
    chunk_list[n][0]=20;chunk_list[n++][1]=6;
    chunk_list[n][0]=20;chunk_list[n++][1]=7;
    chunk_list[n][0]=21;chunk_list[n++][1]=7;
    chunk_list[n][0]=21;chunk_list[n++][1]=6;
    chunk_list[n][0]=22;chunk_list[n++][1]=6;
    chunk_list[n][0]=22;chunk_list[n++][1]=7;
    chunk_list[n][0]=23;chunk_list[n++][1]=7;
    chunk_list[n][0]=23;chunk_list[n++][1]=6;
    chunk_list[n][0]=23;chunk_list[n++][1]=5;
    chunk_list[n][0]=22;chunk_list[n++][1]=5;
    chunk_list[n][0]=22;chunk_list[n++][1]=4;
    chunk_list[n][0]=23;chunk_list[n++][1]=4;
    chunk_list[n][0]=23;chunk_list[n++][1]=3;
    chunk_list[n][0]=23;chunk_list[n++][1]=2;
    chunk_list[n][0]=22;chunk_list[n++][1]=2;
    chunk_list[n][0]=22;chunk_list[n++][1]=3;
    chunk_list[n][0]=21;chunk_list[n++][1]=3;
    chunk_list[n][0]=20;chunk_list[n++][1]=3;
    chunk_list[n][0]=20;chunk_list[n++][1]=2;
    chunk_list[n][0]=21;chunk_list[n++][1]=2;
    chunk_list[n][0]=21;chunk_list[n++][1]=1;
    chunk_list[n][0]=20;chunk_list[n++][1]=1;
    chunk_list[n][0]=20;chunk_list[n++][1]=0;
    chunk_list[n][0]=21;chunk_list[n++][1]=0;
    chunk_list[n][0]=22;chunk_list[n++][1]=0;
    chunk_list[n][0]=22;chunk_list[n++][1]=1;
    chunk_list[n][0]=23;chunk_list[n++][1]=1;
    chunk_list[n][0]=23;chunk_list[n++][1]=0;
    chunk_list[n][0]=24;chunk_list[n++][1]=0;
    chunk_list[n][0]=25;chunk_list[n++][1]=0;
    chunk_list[n][0]=25;chunk_list[n++][1]=1;
    chunk_list[n][0]=24;chunk_list[n++][1]=1;
    chunk_list[n][0]=24;chunk_list[n++][1]=2;
    chunk_list[n][0]=24;chunk_list[n++][1]=3;
    chunk_list[n][0]=25;chunk_list[n++][1]=3;
    chunk_list[n][0]=25;chunk_list[n++][1]=2;
    chunk_list[n][0]=26;chunk_list[n++][1]=2;
    chunk_list[n][0]=26;chunk_list[n++][1]=3;
    chunk_list[n][0]=27;chunk_list[n++][1]=3;
    chunk_list[n][0]=27;chunk_list[n++][1]=2;
    chunk_list[n][0]=27;chunk_list[n++][1]=1;
    chunk_list[n][0]=26;chunk_list[n++][1]=1;
    chunk_list[n][0]=26;chunk_list[n++][1]=0;
    chunk_list[n][0]=27;chunk_list[n++][1]=0;
    chunk_list[n][0]=28;chunk_list[n++][1]=0;
    chunk_list[n][0]=28;chunk_list[n++][1]=1;
    chunk_list[n][0]=29;chunk_list[n++][1]=1;
    chunk_list[n][0]=29;chunk_list[n++][1]=0;
    chunk_list[n][0]=30;chunk_list[n++][1]=0;
    chunk_list[n][0]=31;chunk_list[n++][1]=0;
    chunk_list[n][0]=31;chunk_list[n++][1]=1;
    chunk_list[n][0]=30;chunk_list[n++][1]=1;
    chunk_list[n][0]=30;chunk_list[n++][1]=2;
    chunk_list[n][0]=31;chunk_list[n++][1]=2;
    chunk_list[n][0]=31;chunk_list[n++][1]=3;
    chunk_list[n][0]=30;chunk_list[n++][1]=3;
    chunk_list[n][0]=29;chunk_list[n++][1]=3;
    chunk_list[n][0]=29;chunk_list[n++][1]=2;
    chunk_list[n][0]=28;chunk_list[n++][1]=2;
    chunk_list[n][0]=28;chunk_list[n++][1]=3;
    chunk_list[n][0]=28;chunk_list[n++][1]=4;
    chunk_list[n][0]=28;chunk_list[n++][1]=5;
    chunk_list[n][0]=29;chunk_list[n++][1]=5;
    chunk_list[n][0]=29;chunk_list[n++][1]=4;
    chunk_list[n][0]=30;chunk_list[n++][1]=4;
    chunk_list[n][0]=31;chunk_list[n++][1]=4;
    chunk_list[n][0]=31;chunk_list[n++][1]=5;
    chunk_list[n][0]=30;chunk_list[n++][1]=5;
    chunk_list[n][0]=30;chunk_list[n++][1]=6;
    chunk_list[n][0]=31;chunk_list[n++][1]=6;
    chunk_list[n][0]=31;chunk_list[n++][1]=7;
    chunk_list[n][0]=30;chunk_list[n++][1]=7;
    chunk_list[n][0]=29;chunk_list[n++][1]=7;
    chunk_list[n][0]=29;chunk_list[n++][1]=6;
    chunk_list[n][0]=28;chunk_list[n++][1]=6;
    chunk_list[n][0]=28;chunk_list[n++][1]=7;
    chunk_list[n][0]=27;chunk_list[n++][1]=7;
    chunk_list[n][0]=26;chunk_list[n++][1]=7;
    chunk_list[n][0]=26;chunk_list[n++][1]=6;
    chunk_list[n][0]=27;chunk_list[n++][1]=6;
    chunk_list[n][0]=27;chunk_list[n++][1]=5;
    chunk_list[n][0]=27;chunk_list[n++][1]=4;
    chunk_list[n][0]=26;chunk_list[n++][1]=4;
    chunk_list[n][0]=26;chunk_list[n++][1]=5;
    chunk_list[n][0]=25;chunk_list[n++][1]=5;
    chunk_list[n][0]=25;chunk_list[n++][1]=4;
    chunk_list[n][0]=24;chunk_list[n++][1]=4;
    chunk_list[n][0]=24;chunk_list[n++][1]=5;
    chunk_list[n][0]=24;chunk_list[n++][1]=6;
    chunk_list[n][0]=25;chunk_list[n++][1]=6;
    chunk_list[n][0]=25;chunk_list[n++][1]=7;
    chunk_list[n][0]=24;chunk_list[n++][1]=7;
    chunk_list[n][0]=24;chunk_list[n++][1]=8;
    chunk_list[n][0]=25;chunk_list[n++][1]=8;
    chunk_list[n][0]=25;chunk_list[n++][1]=9;
    chunk_list[n][0]=24;chunk_list[n++][1]=9;
    chunk_list[n][0]=24;chunk_list[n++][1]=10;
    chunk_list[n][0]=24;chunk_list[n++][1]=11;
    chunk_list[n][0]=25;chunk_list[n++][1]=11;
    chunk_list[n][0]=25;chunk_list[n++][1]=10;
    chunk_list[n][0]=26;chunk_list[n++][1]=10;
    chunk_list[n][0]=26;chunk_list[n++][1]=11;
    chunk_list[n][0]=27;chunk_list[n++][1]=11;
    chunk_list[n][0]=27;chunk_list[n++][1]=10;
    chunk_list[n][0]=27;chunk_list[n++][1]=9;
    chunk_list[n][0]=26;chunk_list[n++][1]=9;
    chunk_list[n][0]=26;chunk_list[n++][1]=8;
    chunk_list[n][0]=27;chunk_list[n++][1]=8;
    chunk_list[n][0]=28;chunk_list[n++][1]=8;
    chunk_list[n][0]=28;chunk_list[n++][1]=9;
    chunk_list[n][0]=29;chunk_list[n++][1]=9;
    chunk_list[n][0]=29;chunk_list[n++][1]=8;
    chunk_list[n][0]=30;chunk_list[n++][1]=8;
    chunk_list[n][0]=31;chunk_list[n++][1]=8;
    chunk_list[n][0]=31;chunk_list[n++][1]=9;
    chunk_list[n][0]=30;chunk_list[n++][1]=9;
    chunk_list[n][0]=30;chunk_list[n++][1]=10;
    chunk_list[n][0]=31;chunk_list[n++][1]=10;
    chunk_list[n][0]=31;chunk_list[n++][1]=11;
    chunk_list[n][0]=30;chunk_list[n++][1]=11;
    chunk_list[n][0]=29;chunk_list[n++][1]=11;
    chunk_list[n][0]=29;chunk_list[n++][1]=10;
    chunk_list[n][0]=28;chunk_list[n++][1]=10;
    chunk_list[n][0]=28;chunk_list[n++][1]=11;
    chunk_list[n][0]=28;chunk_list[n++][1]=12;
    chunk_list[n][0]=28;chunk_list[n++][1]=13;
    chunk_list[n][0]=29;chunk_list[n++][1]=13;
    chunk_list[n][0]=29;chunk_list[n++][1]=12;
    chunk_list[n][0]=30;chunk_list[n++][1]=12;
    chunk_list[n][0]=31;chunk_list[n++][1]=12;
    chunk_list[n][0]=31;chunk_list[n++][1]=13;
    chunk_list[n][0]=30;chunk_list[n++][1]=13;
    chunk_list[n][0]=30;chunk_list[n++][1]=14;
    chunk_list[n][0]=31;chunk_list[n++][1]=14;
    chunk_list[n][0]=31;chunk_list[n++][1]=15;
    chunk_list[n][0]=30;chunk_list[n++][1]=15;
    chunk_list[n][0]=29;chunk_list[n++][1]=15;
    chunk_list[n][0]=29;chunk_list[n++][1]=14;
    chunk_list[n][0]=28;chunk_list[n++][1]=14;
    chunk_list[n][0]=28;chunk_list[n++][1]=15;
    chunk_list[n][0]=27;chunk_list[n++][1]=15;
    chunk_list[n][0]=26;chunk_list[n++][1]=15;
    chunk_list[n][0]=26;chunk_list[n++][1]=14;
    chunk_list[n][0]=27;chunk_list[n++][1]=14;
    chunk_list[n][0]=27;chunk_list[n++][1]=13;
    chunk_list[n][0]=27;chunk_list[n++][1]=12;
    chunk_list[n][0]=26;chunk_list[n++][1]=12;
    chunk_list[n][0]=26;chunk_list[n++][1]=13;
    chunk_list[n][0]=25;chunk_list[n++][1]=13;
    chunk_list[n][0]=25;chunk_list[n++][1]=12;
    chunk_list[n][0]=24;chunk_list[n++][1]=12;
    chunk_list[n][0]=24;chunk_list[n++][1]=13;
    chunk_list[n][0]=24;chunk_list[n++][1]=14;
    chunk_list[n][0]=25;chunk_list[n++][1]=14;
    chunk_list[n][0]=25;chunk_list[n++][1]=15;
    chunk_list[n][0]=24;chunk_list[n++][1]=15;
    chunk_list[n][0]=23;chunk_list[n++][1]=15;
    chunk_list[n][0]=23;chunk_list[n++][1]=14;
    chunk_list[n][0]=22;chunk_list[n++][1]=14;
    chunk_list[n][0]=22;chunk_list[n++][1]=15;
    chunk_list[n][0]=21;chunk_list[n++][1]=15;
    chunk_list[n][0]=20;chunk_list[n++][1]=15;
    chunk_list[n][0]=20;chunk_list[n++][1]=14;
    chunk_list[n][0]=21;chunk_list[n++][1]=14;
    chunk_list[n][0]=21;chunk_list[n++][1]=13;
    chunk_list[n][0]=20;chunk_list[n++][1]=13;
    chunk_list[n][0]=20;chunk_list[n++][1]=12;
    chunk_list[n][0]=21;chunk_list[n++][1]=12;
    chunk_list[n][0]=22;chunk_list[n++][1]=12;
    chunk_list[n][0]=22;chunk_list[n++][1]=13;
    chunk_list[n][0]=23;chunk_list[n++][1]=13;
    chunk_list[n][0]=23;chunk_list[n++][1]=12;
    chunk_list[n][0]=23;chunk_list[n++][1]=11;
    chunk_list[n][0]=22;chunk_list[n++][1]=11;
    chunk_list[n][0]=22;chunk_list[n++][1]=10;
    chunk_list[n][0]=23;chunk_list[n++][1]=10;
    chunk_list[n][0]=23;chunk_list[n++][1]=9;
    chunk_list[n][0]=23;chunk_list[n++][1]=8;
    chunk_list[n][0]=22;chunk_list[n++][1]=8;
    chunk_list[n][0]=22;chunk_list[n++][1]=9;
    chunk_list[n][0]=21;chunk_list[n++][1]=9;
    chunk_list[n][0]=21;chunk_list[n++][1]=8;
    chunk_list[n][0]=20;chunk_list[n++][1]=8;
    chunk_list[n][0]=20;chunk_list[n++][1]=9;
    chunk_list[n][0]=20;chunk_list[n++][1]=10;
    chunk_list[n][0]=21;chunk_list[n++][1]=10;
    chunk_list[n][0]=21;chunk_list[n++][1]=11;
    chunk_list[n][0]=20;chunk_list[n++][1]=11;
    chunk_list[n][0]=19;chunk_list[n++][1]=11;
    chunk_list[n][0]=18;chunk_list[n++][1]=11;
    chunk_list[n][0]=18;chunk_list[n++][1]=10;
    chunk_list[n][0]=19;chunk_list[n++][1]=10;
    chunk_list[n][0]=19;chunk_list[n++][1]=9;
    chunk_list[n][0]=19;chunk_list[n++][1]=8;
    chunk_list[n][0]=18;chunk_list[n++][1]=8;
    chunk_list[n][0]=18;chunk_list[n++][1]=9;
    chunk_list[n][0]=17;chunk_list[n++][1]=9;
    chunk_list[n][0]=17;chunk_list[n++][1]=8;
    chunk_list[n][0]=16;chunk_list[n++][1]=8;
    chunk_list[n][0]=16;chunk_list[n++][1]=9;
    chunk_list[n][0]=16;chunk_list[n++][1]=10;
    chunk_list[n][0]=17;chunk_list[n++][1]=10;
    chunk_list[n][0]=17;chunk_list[n++][1]=11;
    chunk_list[n][0]=16;chunk_list[n++][1]=11;
    chunk_list[n][0]=16;chunk_list[n++][1]=12;
    chunk_list[n][0]=16;chunk_list[n++][1]=13;
    chunk_list[n][0]=17;chunk_list[n++][1]=13;
    chunk_list[n][0]=17;chunk_list[n++][1]=12;
    chunk_list[n][0]=18;chunk_list[n++][1]=12;
    chunk_list[n][0]=19;chunk_list[n++][1]=12;
    chunk_list[n][0]=19;chunk_list[n++][1]=13;
    chunk_list[n][0]=18;chunk_list[n++][1]=13;
    chunk_list[n][0]=18;chunk_list[n++][1]=14;
    chunk_list[n][0]=19;chunk_list[n++][1]=14;
    chunk_list[n][0]=19;chunk_list[n++][1]=15;
    chunk_list[n][0]=18;chunk_list[n++][1]=15;
    chunk_list[n][0]=17;chunk_list[n++][1]=15;
    chunk_list[n][0]=17;chunk_list[n++][1]=14;
    chunk_list[n][0]=16;chunk_list[n++][1]=14;
    chunk_list[n][0]=16;chunk_list[n++][1]=15;
    chunk_list[n][0]=16;chunk_list[n++][1]=16;
    chunk_list[n][0]=16;chunk_list[n++][1]=17;
    chunk_list[n][0]=17;chunk_list[n++][1]=17;
    chunk_list[n][0]=17;chunk_list[n++][1]=16;
    chunk_list[n][0]=18;chunk_list[n++][1]=16;
    chunk_list[n][0]=19;chunk_list[n++][1]=16;
    chunk_list[n][0]=19;chunk_list[n++][1]=17;
    chunk_list[n][0]=18;chunk_list[n++][1]=17;
    chunk_list[n][0]=18;chunk_list[n++][1]=18;
    chunk_list[n][0]=19;chunk_list[n++][1]=18;
    chunk_list[n][0]=19;chunk_list[n++][1]=19;
    chunk_list[n][0]=18;chunk_list[n++][1]=19;
    chunk_list[n][0]=17;chunk_list[n++][1]=19;
    chunk_list[n][0]=17;chunk_list[n++][1]=18;
    chunk_list[n][0]=16;chunk_list[n++][1]=18;
    chunk_list[n][0]=16;chunk_list[n++][1]=19;
    chunk_list[n][0]=16;chunk_list[n++][1]=20;
    chunk_list[n][0]=17;chunk_list[n++][1]=20;
    chunk_list[n][0]=17;chunk_list[n++][1]=21;
    chunk_list[n][0]=16;chunk_list[n++][1]=21;
    chunk_list[n][0]=16;chunk_list[n++][1]=22;
    chunk_list[n][0]=16;chunk_list[n++][1]=23;
    chunk_list[n][0]=17;chunk_list[n++][1]=23;
    chunk_list[n][0]=17;chunk_list[n++][1]=22;
    chunk_list[n][0]=18;chunk_list[n++][1]=22;
    chunk_list[n][0]=18;chunk_list[n++][1]=23;
    chunk_list[n][0]=19;chunk_list[n++][1]=23;
    chunk_list[n][0]=19;chunk_list[n++][1]=22;
    chunk_list[n][0]=19;chunk_list[n++][1]=21;
    chunk_list[n][0]=18;chunk_list[n++][1]=21;
    chunk_list[n][0]=18;chunk_list[n++][1]=20;
    chunk_list[n][0]=19;chunk_list[n++][1]=20;
    chunk_list[n][0]=20;chunk_list[n++][1]=20;
    chunk_list[n][0]=21;chunk_list[n++][1]=20;
    chunk_list[n][0]=21;chunk_list[n++][1]=21;
    chunk_list[n][0]=20;chunk_list[n++][1]=21;
    chunk_list[n][0]=20;chunk_list[n++][1]=22;
    chunk_list[n][0]=20;chunk_list[n++][1]=23;
    chunk_list[n][0]=21;chunk_list[n++][1]=23;
    chunk_list[n][0]=21;chunk_list[n++][1]=22;
    chunk_list[n][0]=22;chunk_list[n++][1]=22;
    chunk_list[n][0]=22;chunk_list[n++][1]=23;
    chunk_list[n][0]=23;chunk_list[n++][1]=23;
    chunk_list[n][0]=23;chunk_list[n++][1]=22;
    chunk_list[n][0]=23;chunk_list[n++][1]=21;
    chunk_list[n][0]=22;chunk_list[n++][1]=21;
    chunk_list[n][0]=22;chunk_list[n++][1]=20;
    chunk_list[n][0]=23;chunk_list[n++][1]=20;
    chunk_list[n][0]=23;chunk_list[n++][1]=19;
    chunk_list[n][0]=23;chunk_list[n++][1]=18;
    chunk_list[n][0]=22;chunk_list[n++][1]=18;
    chunk_list[n][0]=22;chunk_list[n++][1]=19;
    chunk_list[n][0]=21;chunk_list[n++][1]=19;
    chunk_list[n][0]=20;chunk_list[n++][1]=19;
    chunk_list[n][0]=20;chunk_list[n++][1]=18;
    chunk_list[n][0]=21;chunk_list[n++][1]=18;
    chunk_list[n][0]=21;chunk_list[n++][1]=17;
    chunk_list[n][0]=20;chunk_list[n++][1]=17;
    chunk_list[n][0]=20;chunk_list[n++][1]=16;
    chunk_list[n][0]=21;chunk_list[n++][1]=16;
    chunk_list[n][0]=22;chunk_list[n++][1]=16;
    chunk_list[n][0]=22;chunk_list[n++][1]=17;
    chunk_list[n][0]=23;chunk_list[n++][1]=17;
    chunk_list[n][0]=23;chunk_list[n++][1]=16;
    chunk_list[n][0]=24;chunk_list[n++][1]=16;
    chunk_list[n][0]=25;chunk_list[n++][1]=16;
    chunk_list[n][0]=25;chunk_list[n++][1]=17;
    chunk_list[n][0]=24;chunk_list[n++][1]=17;
    chunk_list[n][0]=24;chunk_list[n++][1]=18;
    chunk_list[n][0]=24;chunk_list[n++][1]=19;
    chunk_list[n][0]=25;chunk_list[n++][1]=19;
    chunk_list[n][0]=25;chunk_list[n++][1]=18;
    chunk_list[n][0]=26;chunk_list[n++][1]=18;
    chunk_list[n][0]=26;chunk_list[n++][1]=19;
    chunk_list[n][0]=27;chunk_list[n++][1]=19;
    chunk_list[n][0]=27;chunk_list[n++][1]=18;
    chunk_list[n][0]=27;chunk_list[n++][1]=17;
    chunk_list[n][0]=26;chunk_list[n++][1]=17;
    chunk_list[n][0]=26;chunk_list[n++][1]=16;
    chunk_list[n][0]=27;chunk_list[n++][1]=16;
    chunk_list[n][0]=28;chunk_list[n++][1]=16;
    chunk_list[n][0]=28;chunk_list[n++][1]=17;
    chunk_list[n][0]=29;chunk_list[n++][1]=17;
    chunk_list[n][0]=29;chunk_list[n++][1]=16;
    chunk_list[n][0]=30;chunk_list[n++][1]=16;
    chunk_list[n][0]=31;chunk_list[n++][1]=16;
    chunk_list[n][0]=31;chunk_list[n++][1]=17;
    chunk_list[n][0]=30;chunk_list[n++][1]=17;
    chunk_list[n][0]=30;chunk_list[n++][1]=18;
    chunk_list[n][0]=31;chunk_list[n++][1]=18;
    chunk_list[n][0]=31;chunk_list[n++][1]=19;
    chunk_list[n][0]=30;chunk_list[n++][1]=19;
    chunk_list[n][0]=29;chunk_list[n++][1]=19;
    chunk_list[n][0]=29;chunk_list[n++][1]=18;
    chunk_list[n][0]=28;chunk_list[n++][1]=18;
    chunk_list[n][0]=28;chunk_list[n++][1]=19;
    chunk_list[n][0]=28;chunk_list[n++][1]=20;
    chunk_list[n][0]=28;chunk_list[n++][1]=21;
    chunk_list[n][0]=29;chunk_list[n++][1]=21;
    chunk_list[n][0]=29;chunk_list[n++][1]=20;
    chunk_list[n][0]=30;chunk_list[n++][1]=20;
    chunk_list[n][0]=31;chunk_list[n++][1]=20;
    chunk_list[n][0]=31;chunk_list[n++][1]=21;
    chunk_list[n][0]=30;chunk_list[n++][1]=21;
    chunk_list[n][0]=30;chunk_list[n++][1]=22;
    chunk_list[n][0]=31;chunk_list[n++][1]=22;
    chunk_list[n][0]=31;chunk_list[n++][1]=23;
    chunk_list[n][0]=30;chunk_list[n++][1]=23;
    chunk_list[n][0]=29;chunk_list[n++][1]=23;
    chunk_list[n][0]=29;chunk_list[n++][1]=22;
    chunk_list[n][0]=28;chunk_list[n++][1]=22;
    chunk_list[n][0]=28;chunk_list[n++][1]=23;
    chunk_list[n][0]=27;chunk_list[n++][1]=23;
    chunk_list[n][0]=26;chunk_list[n++][1]=23;
    chunk_list[n][0]=26;chunk_list[n++][1]=22;
    chunk_list[n][0]=27;chunk_list[n++][1]=22;
    chunk_list[n][0]=27;chunk_list[n++][1]=21;
    chunk_list[n][0]=27;chunk_list[n++][1]=20;
    chunk_list[n][0]=26;chunk_list[n++][1]=20;
    chunk_list[n][0]=26;chunk_list[n++][1]=21;
    chunk_list[n][0]=25;chunk_list[n++][1]=21;
    chunk_list[n][0]=25;chunk_list[n++][1]=20;
    chunk_list[n][0]=24;chunk_list[n++][1]=20;
    chunk_list[n][0]=24;chunk_list[n++][1]=21;
    chunk_list[n][0]=24;chunk_list[n++][1]=22;
    chunk_list[n][0]=25;chunk_list[n++][1]=22;
    chunk_list[n][0]=25;chunk_list[n++][1]=23;
    chunk_list[n][0]=24;chunk_list[n++][1]=23;
    chunk_list[n][0]=24;chunk_list[n++][1]=24;
    chunk_list[n][0]=25;chunk_list[n++][1]=24;
    chunk_list[n][0]=25;chunk_list[n++][1]=25;
    chunk_list[n][0]=24;chunk_list[n++][1]=25;
    chunk_list[n][0]=24;chunk_list[n++][1]=26;
    chunk_list[n][0]=24;chunk_list[n++][1]=27;
    chunk_list[n][0]=25;chunk_list[n++][1]=27;
    chunk_list[n][0]=25;chunk_list[n++][1]=26;
    chunk_list[n][0]=26;chunk_list[n++][1]=26;
    chunk_list[n][0]=26;chunk_list[n++][1]=27;
    chunk_list[n][0]=27;chunk_list[n++][1]=27;
    chunk_list[n][0]=27;chunk_list[n++][1]=26;
    chunk_list[n][0]=27;chunk_list[n++][1]=25;
    chunk_list[n][0]=26;chunk_list[n++][1]=25;
    chunk_list[n][0]=26;chunk_list[n++][1]=24;
    chunk_list[n][0]=27;chunk_list[n++][1]=24;
    chunk_list[n][0]=28;chunk_list[n++][1]=24;
    chunk_list[n][0]=28;chunk_list[n++][1]=25;
    chunk_list[n][0]=29;chunk_list[n++][1]=25;
    chunk_list[n][0]=29;chunk_list[n++][1]=24;
    chunk_list[n][0]=30;chunk_list[n++][1]=24;
    chunk_list[n][0]=31;chunk_list[n++][1]=24;
    chunk_list[n][0]=31;chunk_list[n++][1]=25;
    chunk_list[n][0]=30;chunk_list[n++][1]=25;
    chunk_list[n][0]=30;chunk_list[n++][1]=26;
    chunk_list[n][0]=31;chunk_list[n++][1]=26;
    chunk_list[n][0]=31;chunk_list[n++][1]=27;
    chunk_list[n][0]=30;chunk_list[n++][1]=27;
    chunk_list[n][0]=29;chunk_list[n++][1]=27;
    chunk_list[n][0]=29;chunk_list[n++][1]=26;
    chunk_list[n][0]=28;chunk_list[n++][1]=26;
    chunk_list[n][0]=28;chunk_list[n++][1]=27;
    chunk_list[n][0]=28;chunk_list[n++][1]=28;
    chunk_list[n][0]=28;chunk_list[n++][1]=29;
    chunk_list[n][0]=29;chunk_list[n++][1]=29;
    chunk_list[n][0]=29;chunk_list[n++][1]=28;
    chunk_list[n][0]=30;chunk_list[n++][1]=28;
    chunk_list[n][0]=31;chunk_list[n++][1]=28;
    chunk_list[n][0]=31;chunk_list[n++][1]=29;
    chunk_list[n][0]=30;chunk_list[n++][1]=29;
    chunk_list[n][0]=30;chunk_list[n++][1]=30;
    chunk_list[n][0]=31;chunk_list[n++][1]=30;
    chunk_list[n][0]=31;chunk_list[n++][1]=31;
    chunk_list[n][0]=30;chunk_list[n++][1]=31;
    chunk_list[n][0]=29;chunk_list[n++][1]=31;
    chunk_list[n][0]=29;chunk_list[n++][1]=30;
    chunk_list[n][0]=28;chunk_list[n++][1]=30;
    chunk_list[n][0]=28;chunk_list[n++][1]=31;
    chunk_list[n][0]=27;chunk_list[n++][1]=31;
    chunk_list[n][0]=26;chunk_list[n++][1]=31;
    chunk_list[n][0]=26;chunk_list[n++][1]=30;
    chunk_list[n][0]=27;chunk_list[n++][1]=30;
    chunk_list[n][0]=27;chunk_list[n++][1]=29;
    chunk_list[n][0]=27;chunk_list[n++][1]=28;
    chunk_list[n][0]=26;chunk_list[n++][1]=28;
    chunk_list[n][0]=26;chunk_list[n++][1]=29;
    chunk_list[n][0]=25;chunk_list[n++][1]=29;
    chunk_list[n][0]=25;chunk_list[n++][1]=28;
    chunk_list[n][0]=24;chunk_list[n++][1]=28;
    chunk_list[n][0]=24;chunk_list[n++][1]=29;
    chunk_list[n][0]=24;chunk_list[n++][1]=30;
    chunk_list[n][0]=25;chunk_list[n++][1]=30;
    chunk_list[n][0]=25;chunk_list[n++][1]=31;
    chunk_list[n][0]=24;chunk_list[n++][1]=31;
    chunk_list[n][0]=23;chunk_list[n++][1]=31;
    chunk_list[n][0]=23;chunk_list[n++][1]=30;
    chunk_list[n][0]=22;chunk_list[n++][1]=30;
    chunk_list[n][0]=22;chunk_list[n++][1]=31;
    chunk_list[n][0]=21;chunk_list[n++][1]=31;
    chunk_list[n][0]=20;chunk_list[n++][1]=31;
    chunk_list[n][0]=20;chunk_list[n++][1]=30;
    chunk_list[n][0]=21;chunk_list[n++][1]=30;
    chunk_list[n][0]=21;chunk_list[n++][1]=29;
    chunk_list[n][0]=20;chunk_list[n++][1]=29;
    chunk_list[n][0]=20;chunk_list[n++][1]=28;
    chunk_list[n][0]=21;chunk_list[n++][1]=28;
    chunk_list[n][0]=22;chunk_list[n++][1]=28;
    chunk_list[n][0]=22;chunk_list[n++][1]=29;
    chunk_list[n][0]=23;chunk_list[n++][1]=29;
    chunk_list[n][0]=23;chunk_list[n++][1]=28;
    chunk_list[n][0]=23;chunk_list[n++][1]=27;
    chunk_list[n][0]=22;chunk_list[n++][1]=27;
    chunk_list[n][0]=22;chunk_list[n++][1]=26;
    chunk_list[n][0]=23;chunk_list[n++][1]=26;
    chunk_list[n][0]=23;chunk_list[n++][1]=25;
    chunk_list[n][0]=23;chunk_list[n++][1]=24;
    chunk_list[n][0]=22;chunk_list[n++][1]=24;
    chunk_list[n][0]=22;chunk_list[n++][1]=25;
    chunk_list[n][0]=21;chunk_list[n++][1]=25;
    chunk_list[n][0]=21;chunk_list[n++][1]=24;
    chunk_list[n][0]=20;chunk_list[n++][1]=24;
    chunk_list[n][0]=20;chunk_list[n++][1]=25;
    chunk_list[n][0]=20;chunk_list[n++][1]=26;
    chunk_list[n][0]=21;chunk_list[n++][1]=26;
    chunk_list[n][0]=21;chunk_list[n++][1]=27;
    chunk_list[n][0]=20;chunk_list[n++][1]=27;
    chunk_list[n][0]=19;chunk_list[n++][1]=27;
    chunk_list[n][0]=18;chunk_list[n++][1]=27;
    chunk_list[n][0]=18;chunk_list[n++][1]=26;
    chunk_list[n][0]=19;chunk_list[n++][1]=26;
    chunk_list[n][0]=19;chunk_list[n++][1]=25;
    chunk_list[n][0]=19;chunk_list[n++][1]=24;
    chunk_list[n][0]=18;chunk_list[n++][1]=24;
    chunk_list[n][0]=18;chunk_list[n++][1]=25;
    chunk_list[n][0]=17;chunk_list[n++][1]=25;
    chunk_list[n][0]=17;chunk_list[n++][1]=24;
    chunk_list[n][0]=16;chunk_list[n++][1]=24;
    chunk_list[n][0]=16;chunk_list[n++][1]=25;
    chunk_list[n][0]=16;chunk_list[n++][1]=26;
    chunk_list[n][0]=17;chunk_list[n++][1]=26;
    chunk_list[n][0]=17;chunk_list[n++][1]=27;
    chunk_list[n][0]=16;chunk_list[n++][1]=27;
    chunk_list[n][0]=16;chunk_list[n++][1]=28;
    chunk_list[n][0]=16;chunk_list[n++][1]=29;
    chunk_list[n][0]=17;chunk_list[n++][1]=29;
    chunk_list[n][0]=17;chunk_list[n++][1]=28;
    chunk_list[n][0]=18;chunk_list[n++][1]=28;
    chunk_list[n][0]=19;chunk_list[n++][1]=28;
    chunk_list[n][0]=19;chunk_list[n++][1]=29;
    chunk_list[n][0]=18;chunk_list[n++][1]=29;
    chunk_list[n][0]=18;chunk_list[n++][1]=30;
    chunk_list[n][0]=19;chunk_list[n++][1]=30;
    chunk_list[n][0]=19;chunk_list[n++][1]=31;
    chunk_list[n][0]=18;chunk_list[n++][1]=31;
    chunk_list[n][0]=17;chunk_list[n++][1]=31;
    chunk_list[n][0]=17;chunk_list[n++][1]=30;
    chunk_list[n][0]=16;chunk_list[n++][1]=30;
    chunk_list[n][0]=16;chunk_list[n++][1]=31;
    chunk_list[n][0]=15;chunk_list[n++][1]=31;
    chunk_list[n][0]=15;chunk_list[n++][1]=30;
    chunk_list[n][0]=14;chunk_list[n++][1]=30;
    chunk_list[n][0]=14;chunk_list[n++][1]=31;
    chunk_list[n][0]=13;chunk_list[n++][1]=31;
    chunk_list[n][0]=12;chunk_list[n++][1]=31;
    chunk_list[n][0]=12;chunk_list[n++][1]=30;
    chunk_list[n][0]=13;chunk_list[n++][1]=30;
    chunk_list[n][0]=13;chunk_list[n++][1]=29;
    chunk_list[n][0]=12;chunk_list[n++][1]=29;
    chunk_list[n][0]=12;chunk_list[n++][1]=28;
    chunk_list[n][0]=13;chunk_list[n++][1]=28;
    chunk_list[n][0]=14;chunk_list[n++][1]=28;
    chunk_list[n][0]=14;chunk_list[n++][1]=29;
    chunk_list[n][0]=15;chunk_list[n++][1]=29;
    chunk_list[n][0]=15;chunk_list[n++][1]=28;
    chunk_list[n][0]=15;chunk_list[n++][1]=27;
    chunk_list[n][0]=14;chunk_list[n++][1]=27;
    chunk_list[n][0]=14;chunk_list[n++][1]=26;
    chunk_list[n][0]=15;chunk_list[n++][1]=26;
    chunk_list[n][0]=15;chunk_list[n++][1]=25;
    chunk_list[n][0]=15;chunk_list[n++][1]=24;
    chunk_list[n][0]=14;chunk_list[n++][1]=24;
    chunk_list[n][0]=14;chunk_list[n++][1]=25;
    chunk_list[n][0]=13;chunk_list[n++][1]=25;
    chunk_list[n][0]=13;chunk_list[n++][1]=24;
    chunk_list[n][0]=12;chunk_list[n++][1]=24;
    chunk_list[n][0]=12;chunk_list[n++][1]=25;
    chunk_list[n][0]=12;chunk_list[n++][1]=26;
    chunk_list[n][0]=13;chunk_list[n++][1]=26;
    chunk_list[n][0]=13;chunk_list[n++][1]=27;
    chunk_list[n][0]=12;chunk_list[n++][1]=27;
    chunk_list[n][0]=11;chunk_list[n++][1]=27;
    chunk_list[n][0]=10;chunk_list[n++][1]=27;
    chunk_list[n][0]=10;chunk_list[n++][1]=26;
    chunk_list[n][0]=11;chunk_list[n++][1]=26;
    chunk_list[n][0]=11;chunk_list[n++][1]=25;
    chunk_list[n][0]=11;chunk_list[n++][1]=24;
    chunk_list[n][0]=10;chunk_list[n++][1]=24;
    chunk_list[n][0]=10;chunk_list[n++][1]=25;
    chunk_list[n][0]=9;chunk_list[n++][1]=25;
    chunk_list[n][0]=9;chunk_list[n++][1]=24;
    chunk_list[n][0]=8;chunk_list[n++][1]=24;
    chunk_list[n][0]=8;chunk_list[n++][1]=25;
    chunk_list[n][0]=8;chunk_list[n++][1]=26;
    chunk_list[n][0]=9;chunk_list[n++][1]=26;
    chunk_list[n][0]=9;chunk_list[n++][1]=27;
    chunk_list[n][0]=8;chunk_list[n++][1]=27;
    chunk_list[n][0]=8;chunk_list[n++][1]=28;
    chunk_list[n][0]=8;chunk_list[n++][1]=29;
    chunk_list[n][0]=9;chunk_list[n++][1]=29;
    chunk_list[n][0]=9;chunk_list[n++][1]=28;
    chunk_list[n][0]=10;chunk_list[n++][1]=28;
    chunk_list[n][0]=11;chunk_list[n++][1]=28;
    chunk_list[n][0]=11;chunk_list[n++][1]=29;
    chunk_list[n][0]=10;chunk_list[n++][1]=29;
    chunk_list[n][0]=10;chunk_list[n++][1]=30;
    chunk_list[n][0]=11;chunk_list[n++][1]=30;
    chunk_list[n][0]=11;chunk_list[n++][1]=31;
    chunk_list[n][0]=10;chunk_list[n++][1]=31;
    chunk_list[n][0]=9;chunk_list[n++][1]=31;
    chunk_list[n][0]=9;chunk_list[n++][1]=30;
    chunk_list[n][0]=8;chunk_list[n++][1]=30;
    chunk_list[n][0]=8;chunk_list[n++][1]=31;
    chunk_list[n][0]=7;chunk_list[n++][1]=31;
    chunk_list[n][0]=6;chunk_list[n++][1]=31;
    chunk_list[n][0]=6;chunk_list[n++][1]=30;
    chunk_list[n][0]=7;chunk_list[n++][1]=30;
    chunk_list[n][0]=7;chunk_list[n++][1]=29;
    chunk_list[n][0]=7;chunk_list[n++][1]=28;
    chunk_list[n][0]=6;chunk_list[n++][1]=28;
    chunk_list[n][0]=6;chunk_list[n++][1]=29;
    chunk_list[n][0]=5;chunk_list[n++][1]=29;
    chunk_list[n][0]=5;chunk_list[n++][1]=28;
    chunk_list[n][0]=4;chunk_list[n++][1]=28;
    chunk_list[n][0]=4;chunk_list[n++][1]=29;
    chunk_list[n][0]=4;chunk_list[n++][1]=30;
    chunk_list[n][0]=5;chunk_list[n++][1]=30;
    chunk_list[n][0]=5;chunk_list[n++][1]=31;
    chunk_list[n][0]=4;chunk_list[n++][1]=31;
    chunk_list[n][0]=3;chunk_list[n++][1]=31;
    chunk_list[n][0]=3;chunk_list[n++][1]=30;
    chunk_list[n][0]=2;chunk_list[n++][1]=30;
    chunk_list[n][0]=2;chunk_list[n++][1]=31;
    chunk_list[n][0]=1;chunk_list[n++][1]=31;
    chunk_list[n][0]=0;chunk_list[n++][1]=31;
    chunk_list[n][0]=0;chunk_list[n++][1]=30;
    chunk_list[n][0]=1;chunk_list[n++][1]=30;
    chunk_list[n][0]=1;chunk_list[n++][1]=29;
    chunk_list[n][0]=0;chunk_list[n++][1]=29;
    chunk_list[n][0]=0;chunk_list[n++][1]=28;
    chunk_list[n][0]=1;chunk_list[n++][1]=28;
    chunk_list[n][0]=2;chunk_list[n++][1]=28;
    chunk_list[n][0]=2;chunk_list[n++][1]=29;
    chunk_list[n][0]=3;chunk_list[n++][1]=29;
    chunk_list[n][0]=3;chunk_list[n++][1]=28;
    chunk_list[n][0]=3;chunk_list[n++][1]=27;
    chunk_list[n][0]=3;chunk_list[n++][1]=26;
    chunk_list[n][0]=2;chunk_list[n++][1]=26;
    chunk_list[n][0]=2;chunk_list[n++][1]=27;
    chunk_list[n][0]=1;chunk_list[n++][1]=27;
    chunk_list[n][0]=0;chunk_list[n++][1]=27;
    chunk_list[n][0]=0;chunk_list[n++][1]=26;
    chunk_list[n][0]=1;chunk_list[n++][1]=26;
    chunk_list[n][0]=1;chunk_list[n++][1]=25;
    chunk_list[n][0]=0;chunk_list[n++][1]=25;
    chunk_list[n][0]=0;chunk_list[n++][1]=24;
    chunk_list[n][0]=1;chunk_list[n++][1]=24;
    chunk_list[n][0]=2;chunk_list[n++][1]=24;
    chunk_list[n][0]=2;chunk_list[n++][1]=25;
    chunk_list[n][0]=3;chunk_list[n++][1]=25;
    chunk_list[n][0]=3;chunk_list[n++][1]=24;
    chunk_list[n][0]=4;chunk_list[n++][1]=24;
    chunk_list[n][0]=5;chunk_list[n++][1]=24;
    chunk_list[n][0]=5;chunk_list[n++][1]=25;
    chunk_list[n][0]=4;chunk_list[n++][1]=25;
    chunk_list[n][0]=4;chunk_list[n++][1]=26;
    chunk_list[n][0]=4;chunk_list[n++][1]=27;
    chunk_list[n][0]=5;chunk_list[n++][1]=27;
    chunk_list[n][0]=5;chunk_list[n++][1]=26;
    chunk_list[n][0]=6;chunk_list[n++][1]=26;
    chunk_list[n][0]=6;chunk_list[n++][1]=27;
    chunk_list[n][0]=7;chunk_list[n++][1]=27;
    chunk_list[n][0]=7;chunk_list[n++][1]=26;
    chunk_list[n][0]=7;chunk_list[n++][1]=25;
    chunk_list[n][0]=6;chunk_list[n++][1]=25;
    chunk_list[n][0]=6;chunk_list[n++][1]=24;
    chunk_list[n][0]=7;chunk_list[n++][1]=24;
    chunk_list[n][0]=7;chunk_list[n++][1]=23;
    chunk_list[n][0]=6;chunk_list[n++][1]=23;
    chunk_list[n][0]=6;chunk_list[n++][1]=22;
    chunk_list[n][0]=7;chunk_list[n++][1]=22;
    chunk_list[n][0]=7;chunk_list[n++][1]=21;
    chunk_list[n][0]=7;chunk_list[n++][1]=20;
    chunk_list[n][0]=6;chunk_list[n++][1]=20;
    chunk_list[n][0]=6;chunk_list[n++][1]=21;
    chunk_list[n][0]=5;chunk_list[n++][1]=21;
    chunk_list[n][0]=5;chunk_list[n++][1]=20;
    chunk_list[n][0]=4;chunk_list[n++][1]=20;
    chunk_list[n][0]=4;chunk_list[n++][1]=21;
    chunk_list[n][0]=4;chunk_list[n++][1]=22;
    chunk_list[n][0]=5;chunk_list[n++][1]=22;
    chunk_list[n][0]=5;chunk_list[n++][1]=23;
    chunk_list[n][0]=4;chunk_list[n++][1]=23;
    chunk_list[n][0]=3;chunk_list[n++][1]=23;
    chunk_list[n][0]=3;chunk_list[n++][1]=22;
    chunk_list[n][0]=2;chunk_list[n++][1]=22;
    chunk_list[n][0]=2;chunk_list[n++][1]=23;
    chunk_list[n][0]=1;chunk_list[n++][1]=23;
    chunk_list[n][0]=0;chunk_list[n++][1]=23;
    chunk_list[n][0]=0;chunk_list[n++][1]=22;
    chunk_list[n][0]=1;chunk_list[n++][1]=22;
    chunk_list[n][0]=1;chunk_list[n++][1]=21;
    chunk_list[n][0]=0;chunk_list[n++][1]=21;
    chunk_list[n][0]=0;chunk_list[n++][1]=20;
    chunk_list[n][0]=1;chunk_list[n++][1]=20;
    chunk_list[n][0]=2;chunk_list[n++][1]=20;
    chunk_list[n][0]=2;chunk_list[n++][1]=21;
    chunk_list[n][0]=3;chunk_list[n++][1]=21;
    chunk_list[n][0]=3;chunk_list[n++][1]=20;
    chunk_list[n][0]=3;chunk_list[n++][1]=19;
    chunk_list[n][0]=3;chunk_list[n++][1]=18;
    chunk_list[n][0]=2;chunk_list[n++][1]=18;
    chunk_list[n][0]=2;chunk_list[n++][1]=19;
    chunk_list[n][0]=1;chunk_list[n++][1]=19;
    chunk_list[n][0]=0;chunk_list[n++][1]=19;
    chunk_list[n][0]=0;chunk_list[n++][1]=18;
    chunk_list[n][0]=1;chunk_list[n++][1]=18;
    chunk_list[n][0]=1;chunk_list[n++][1]=17;
    chunk_list[n][0]=0;chunk_list[n++][1]=17;
    chunk_list[n][0]=0;chunk_list[n++][1]=16;
    chunk_list[n][0]=1;chunk_list[n++][1]=16;
    chunk_list[n][0]=2;chunk_list[n++][1]=16;
    chunk_list[n][0]=2;chunk_list[n++][1]=17;
    chunk_list[n][0]=3;chunk_list[n++][1]=17;
    chunk_list[n][0]=3;chunk_list[n++][1]=16;
    chunk_list[n][0]=4;chunk_list[n++][1]=16;
    chunk_list[n][0]=5;chunk_list[n++][1]=16;
    chunk_list[n][0]=5;chunk_list[n++][1]=17;
    chunk_list[n][0]=4;chunk_list[n++][1]=17;
    chunk_list[n][0]=4;chunk_list[n++][1]=18;
    chunk_list[n][0]=4;chunk_list[n++][1]=19;
    chunk_list[n][0]=5;chunk_list[n++][1]=19;
    chunk_list[n][0]=5;chunk_list[n++][1]=18;
    chunk_list[n][0]=6;chunk_list[n++][1]=18;
    chunk_list[n][0]=6;chunk_list[n++][1]=19;
    chunk_list[n][0]=7;chunk_list[n++][1]=19;
    chunk_list[n][0]=7;chunk_list[n++][1]=18;
    chunk_list[n][0]=7;chunk_list[n++][1]=17;
    chunk_list[n][0]=6;chunk_list[n++][1]=17;
    chunk_list[n][0]=6;chunk_list[n++][1]=16;
    chunk_list[n][0]=7;chunk_list[n++][1]=16;
    chunk_list[n][0]=8;chunk_list[n++][1]=16;
    chunk_list[n][0]=8;chunk_list[n++][1]=17;
    chunk_list[n][0]=9;chunk_list[n++][1]=17;
    chunk_list[n][0]=9;chunk_list[n++][1]=16;
    chunk_list[n][0]=10;chunk_list[n++][1]=16;
    chunk_list[n][0]=11;chunk_list[n++][1]=16;
    chunk_list[n][0]=11;chunk_list[n++][1]=17;
    chunk_list[n][0]=10;chunk_list[n++][1]=17;
    chunk_list[n][0]=10;chunk_list[n++][1]=18;
    chunk_list[n][0]=11;chunk_list[n++][1]=18;
    chunk_list[n][0]=11;chunk_list[n++][1]=19;
    chunk_list[n][0]=10;chunk_list[n++][1]=19;
    chunk_list[n][0]=9;chunk_list[n++][1]=19;
    chunk_list[n][0]=9;chunk_list[n++][1]=18;
    chunk_list[n][0]=8;chunk_list[n++][1]=18;
    chunk_list[n][0]=8;chunk_list[n++][1]=19;
    chunk_list[n][0]=8;chunk_list[n++][1]=20;
    chunk_list[n][0]=9;chunk_list[n++][1]=20;
    chunk_list[n][0]=9;chunk_list[n++][1]=21;
    chunk_list[n][0]=8;chunk_list[n++][1]=21;
    chunk_list[n][0]=8;chunk_list[n++][1]=22;
    chunk_list[n][0]=8;chunk_list[n++][1]=23;
    chunk_list[n][0]=9;chunk_list[n++][1]=23;
    chunk_list[n][0]=9;chunk_list[n++][1]=22;
    chunk_list[n][0]=10;chunk_list[n++][1]=22;
    chunk_list[n][0]=10;chunk_list[n++][1]=23;
    chunk_list[n][0]=11;chunk_list[n++][1]=23;
    chunk_list[n][0]=11;chunk_list[n++][1]=22;
    chunk_list[n][0]=11;chunk_list[n++][1]=21;
    chunk_list[n][0]=10;chunk_list[n++][1]=21;
    chunk_list[n][0]=10;chunk_list[n++][1]=20;
    chunk_list[n][0]=11;chunk_list[n++][1]=20;
    chunk_list[n][0]=12;chunk_list[n++][1]=20;
    chunk_list[n][0]=13;chunk_list[n++][1]=20;
    chunk_list[n][0]=13;chunk_list[n++][1]=21;
    chunk_list[n][0]=12;chunk_list[n++][1]=21;
    chunk_list[n][0]=12;chunk_list[n++][1]=22;
    chunk_list[n][0]=12;chunk_list[n++][1]=23;
    chunk_list[n][0]=13;chunk_list[n++][1]=23;
    chunk_list[n][0]=13;chunk_list[n++][1]=22;
    chunk_list[n][0]=14;chunk_list[n++][1]=22;
    chunk_list[n][0]=14;chunk_list[n++][1]=23;
    chunk_list[n][0]=15;chunk_list[n++][1]=23;
    chunk_list[n][0]=15;chunk_list[n++][1]=22;
    chunk_list[n][0]=15;chunk_list[n++][1]=21;
    chunk_list[n][0]=14;chunk_list[n++][1]=21;
    chunk_list[n][0]=14;chunk_list[n++][1]=20;
    chunk_list[n][0]=15;chunk_list[n++][1]=20;
    chunk_list[n][0]=15;chunk_list[n++][1]=19;
    chunk_list[n][0]=15;chunk_list[n++][1]=18;
    chunk_list[n][0]=14;chunk_list[n++][1]=18;
    chunk_list[n][0]=14;chunk_list[n++][1]=19;
    chunk_list[n][0]=13;chunk_list[n++][1]=19;
    chunk_list[n][0]=12;chunk_list[n++][1]=19;
    chunk_list[n][0]=12;chunk_list[n++][1]=18;
    chunk_list[n][0]=13;chunk_list[n++][1]=18;
    chunk_list[n][0]=13;chunk_list[n++][1]=17;
    chunk_list[n][0]=12;chunk_list[n++][1]=17;
    chunk_list[n][0]=12;chunk_list[n++][1]=16;
    chunk_list[n][0]=13;chunk_list[n++][1]=16;
    chunk_list[n][0]=14;chunk_list[n++][1]=16;
    chunk_list[n][0]=14;chunk_list[n++][1]=17;
    chunk_list[n][0]=15;chunk_list[n++][1]=17;
    chunk_list[n][0]=15;chunk_list[n++][1]=16;
}


void print_chunk_list() {
    fill_chunk_list();
    for (int t=0; t<1024; t++) {
//        printf("chunk_list[%d]={%d,%d}\r",t,chunk_list[t][0],chunk_list[t][1]);
        reversed_chunk_list[chunk_list[t][0]][chunk_list[t][1]]=t;
    }
//    printf("\n");
}


int main_mceditor4()
{
    int region_x=0;
    int region_z=0;

    int skippy=0;
    int skippy2=0;
    int contin=1;
    int skipping=1;
    int light=0;
    int size_regions=0;
	srand(time(0));
	int first_loop=1;
    remove_block_entities=1;
    ceil_heigher=20;
    while (size_regions<60) {
        size_regions++;
        for (region_x=0; region_x<size_regions && MCEDITOR_stop==0; region_x++) {
            for (region_z=0; region_z<size_regions && MCEDITOR_stop==0; region_z++) {
                region_xxx=region_x;
                region_zzz=region_z;
                if (region_x<size_regions-1 && region_z<size_regions-1) {
                    continue;
                }
                toggle_2=0;toggle_3=0;
                if (contin==1) {
                    contin=0;
                }
                chunk_offsetx=region_x*32;
                chunk_offsetz=region_z*32;

                x00=0;
                y00=0;
                z00=0;
                yl=255;
                xl=512; zl=512;


    //            file_name_MCA = MCAFileNameXZ(region_x, region_z);
    //            editor.mca_coder.loadMCA(file_name_MCA);
                char tmp[256];
                sprintf(tmp, "/Saves/Test/region/r.%d.%d.mca", region_x, region_z);
//                string fname=MCAFileNameXZ(region_x, region_z);
                string fname=tmp;
                if ( file_exists(fname.c_str() ) ) {
                    if (skippy2>0) printf("\n");
                    skippy2=0;
                    if (skippy==0)
                        printf("File(s) exists, skipping %s",fname.c_str());
                    else
                        printf(", %s",fname.c_str());
                    skippy++;
                    continue;
                }
//                printf("here 12\n");

                char comm[100];
//                sprintf(comm,"copy %s %s","/Saves/Leeg/region/r.0.0.mca",fname.c_str());
                CopyFile("/Saves/Leeg/region/r.0.0.mca",fname.c_str(),false);

                skipping=1;
//                printf("Getting data\n");
                read_one_plot_WINMAIN(region_z*512, region_x*512 + 30720, &image_plot_extra);
                read_one_plot_WINMAIN(region_x*512-5, region_z*512-5, &image_plot);
                read_one_plot_WINMAIN(region_x*512-5, region_z*512-5, &image_plot3);
                read_one_plot_WINMAIN(region_x*512-5, region_z*512-5, &image_plot_org);

                for (int x = 0; x < 512; x++) {
                    for (int z = 0; z < 512; z++) {
                        if ( !( (image_plot.getPixel(x+5,z+5).r==0) && (image_plot.getPixel(x+5,z+5).b==0) && (image_plot.getPixel(x+5,z+5).g==0)) ) {
                            skipping=0;
                        }
                    }
                }
                if (skipping==1) {
                    if (skippy>0) printf("\n");
                    skippy=0;
                    if (skippy2==0)
                        printf("Empty...no data...skipping r.%d.%d",region_x,region_z);
                    else
                        printf(", r.%d.%d",region_x,region_z);
                    skippy2++;
                    continue;
                }
                for (int x = 0; x < 512+10; x++) {
                    for (int z = 0; z < 512+10; z++) {
                        float pixel;
                        float c;
                        sf::Color col;
                        col=image_plot.getPixel(x,z);
                        c=(col.r+col.b+col.g);
                        pixel = (c/(3));
                        if (col.a==0) pixel=0;
                        if (pixel!=0 && x>0 && x<511+10 && z>0 && z<511+10) {
                            for (int xxx=-1; xxx<=1; xxx++) {
                                for (int zzz=-1; zzz<=1; zzz++) {
//                                    if (xxx==0 || zzz==0) {
                                    if (xxx!=0 || zzz!=0) {
//                                        image_plot3.setPixel(x+xxx,z+zzz, col);
                                        if ((image_plot3.getPixel(x+xxx,z+zzz).r)!=254) image_plot3.setPixel(x+xxx,z+zzz, col);
                                    }
                                }
                            }
                        }
                    }
                }
                for (int x = 0; x < 512+10; x++) {
                    for (int z = 0; z < 512+10; z++) {
                        float pixel;
                        float c;
                        sf::Color col;
                        col=image_plot3.getPixel(x,z);
                        c=(col.r+col.b+col.g);
                        pixel = (c/(3));
                        if (col.a==0) pixel=0;
                        if (pixel!=0 && x>0 && x<511+10 && z>0 && z<511+10) {
                            for (int xxx=-1; xxx<=1; xxx++) {
                                for (int zzz=-1; zzz<=1; zzz++) {
//                                    if (xxx==0 || zzz==0) {
                                    if (xxx!=0 || zzz!=0) {
//                                        image_plot.setPixel(x+xxx,z+zzz, col);
                                        if ((image_plot.getPixel(x+xxx,z+zzz).r)!=254) image_plot.setPixel(x+xxx,z+zzz, col);
                                    }
                                }
                            }
                        }
                    }
                }

//                region.clearRegion();
                MCRegion region(x00, z00, y00, xl, zl, yl);
                if (skippy>0 || skippy2>0) printf("\n");
                skippy2=0;
                skippy=0;
                first_MCEDIT=1;
                editor.mca_coder.loadMCA("/Saves/Leeg/region/r.0.0.mca");
                editor.mca_coder.setPOSITIONS();
                first_MCEDIT=0;
                region_x_old=0,region_z_old=0;

                printf("- Creating region r.%d.%d.mca: ",region_x,region_z);

                BlockInfo*** AX=region.A;
                int leuk_max=1;
                if (1) {
                    int mix1;                int mix2;                int mix3;                int mix4;
                    int mix5;                int mix6;                int mix7;                int mix8;                int mix9;
                    int num_blocks=0;
//                    int leuk_max=rand()%4;

                    int yellow=ret_color(255,255,0);
                    int white=ret_color(255,255,255);
                    int red=ret_color(255,0,0);
                    int lightred=ret_color(255,64,32);
                    int darkred=ret_color(128,0,0);
                    int black=ret_color(0,0,0);
                    float darkblue=ret_color(0,0,128);

                    int a115=11;
                    int a109=5;
                    int a108=4;
                    int a107=3;

                    printf(" Maze:\b\b\b\b\b\b");
//                    if (!fast_build)
                    for (int x = 0; x < xl; x++) {
                        xx=x+chunk_offsetx*16;
                        BlockInfo** AZ=AX[x];
                        for (int z = 0; z < zl; z++) {
                            zz=z+chunk_offsetz*16;
                            BlockInfo* AY=AZ[z];
                            int r, g, b;
                            float pixel;
                            float pixel_org;

                            float c;
                            sf::Color col;
                            sf::Color col_org;
                            sf::Color col_extra;
                            col=image_plot.getPixel(x+5,z+5);
                            col_org=image_plot_org.getPixel(x+5,z+5);
                            col_extra=image_plot_extra.getPixel(x,z);

                            c=(col.r+col.b+col.g);
                            pixel = (c/(3));
                            if (col.a==0) pixel=0;

                            c=(col_org.r+col_org.b+col_org.g);
                            pixel_org = (c/(3));
                            if (col_org.a==0) pixel_org=0;

                            int x_off=1;
                            int z_off=1;

//                            if (!(x>0 && x<511)) {
//                                x_off=0;
//                            }
//                            if (!(z>0 && z<511)) {
//                                z_off=0;
//                            }


                            for (int y = 0; y < 256; y++) {
                                int edge=0;
                                int edge2=0;
                                int edge3=0;
                                int corner2=0;
                                int red2=0;
                                int dir_x=0;
                                int curve=0;
                                int c1;
                                int c2;
                                int c3;
                                int c4;

                                if (y==0) AY[y] = BlockInfo(7, 0, 0 );
                                if (y==1) AY[y] = BlockInfo(7, 0, 0 );

                                if (y>=a108-2 && y<=a115+2+ceil_heigher) {
                                    sf::Color col_side1;
                                    sf::Color col_side2;
                                    sf::Color col_side3;
                                    sf::Color col_side4;
                                    col_side1=image_plot.getPixel(x-x_off+5,    z+5);
                                    col_side2=image_plot.getPixel(x+5,          z-z_off+5);
                                    col_side3=image_plot.getPixel(x+x_off+5,    z+5);
                                    col_side4=image_plot.getPixel(x+5,          z+z_off+5);
                                    red2=0;
                                    if ( col.r==254 || (pixel==0 && (col_side1.r==254 || col_side2.r==254 || col_side3.r==254 || col_side4.r==254)) ) red2=1;
                                    c1=(col_side1.r+col_side1.b+col_side1.g);
                                    c2=(col_side2.r+col_side2.b+col_side2.g);
                                    c3=(col_side3.r+col_side3.b+col_side3.g);
                                    c4=(col_side4.r+col_side4.b+col_side4.g);
                                    if (c1==0 || c2==0 || c3==0 || c4==0) edge=1;
                                    dir_x=0;
                                    curve=0;
                                    if (c1!=0 && c3!=0) dir_x=1+8;
                                    if (c2!=0 && c4!=0) dir_x=0+8;
                                    if (c1!=0 && c2!=0 && c3==0 && c4==0) curve=8;
                                    if (c3!=0 && c4!=0 && c1==0 && c2==0) curve=6;
                                    if (c1!=0 && c4!=0 && c2==0 && c3==0) curve=7;
                                    if (c2!=0 && c3!=0 && c1==0 && c4==0) curve=9;
                                    if (edge==0) {
                                        col_side1=image_plot.getPixel(x-x_off+5,    z-z_off+5);
                                        col_side2=image_plot.getPixel(x+x_off+5,    z-z_off+5);
                                        col_side3=image_plot.getPixel(x+x_off+5,    z+z_off+5);
                                        col_side4=image_plot.getPixel(x-x_off+5,    z+z_off+5);
                                        c1=(col_side1.r+col_side1.b+col_side1.g);
                                        c2=(col_side2.r+col_side2.b+col_side2.g);
                                        c3=(col_side3.r+col_side3.b+col_side3.g);
                                        c4=(col_side4.r+col_side4.b+col_side4.g);
                                        if (c1==0 || c2==0 || c3==0 || c4==0) edge=1;
                                        if (c1==0 && c2!=0 && c3!=0 && c4!=0) curve=8;
                                        if (c1!=0 && c2==0 && c3!=0 && c4!=0) curve=9;
                                        if (c1!=0 && c2!=0 && c3==0 && c4!=0) curve=6;
                                        if (c1!=0 && c2!=0 && c3!=0 && c4==0) curve=7;
                                    }
                                    if (curve!=0) corner2=1;
                                }


                                if (/*y==a115+2 ||  y==a109-2   || y==a108-2+train_height || y==a109-2+train_height ||*/ y==a108-2) {

                                    sf::Color  col_side1=image_plot_org.getPixel(x-x_off+5,    z+5);
                                    sf::Color  col_side2=image_plot_org.getPixel(x+5,          z-z_off+5);
                                    sf::Color  col_side3=image_plot_org.getPixel(x+x_off+5,    z+5);
                                    sf::Color  col_side4=image_plot_org.getPixel(x+5,          z+z_off+5);
                                    c1=(col_side1.r+col_side1.b+col_side1.g);
                                    c2=(col_side2.r+col_side2.b+col_side2.g);
                                    c3=(col_side3.r+col_side3.b+col_side3.g);
                                    c4=(col_side4.r+col_side4.b+col_side4.g);
                                    if (c1==0 || c2==0 || c3==0 || c4==0) edge3=1;
                                    if (edge3==0) {
                                        col_side1=image_plot_org.getPixel(x-x_off+5,    z-z_off+5);
                                        col_side2=image_plot_org.getPixel(x+x_off+5,    z-z_off+5);
                                        col_side3=image_plot_org.getPixel(x+x_off+5,    z+z_off+5);
                                        col_side4=image_plot_org.getPixel(x-x_off+5,    z+z_off+5);
                                        c1=(col_side1.r+col_side1.b+col_side1.g);
                                        c2=(col_side2.r+col_side2.b+col_side2.g);
                                        c3=(col_side3.r+col_side3.b+col_side3.g);
                                        c4=(col_side4.r+col_side4.b+col_side4.g);
                                        if (c1==0 || c2==0 || c3==0 || c4==0) edge3=1;
                                    }

                                    col_side1=image_plot3.getPixel(x-x_off+5,    z+5);
                                    col_side2=image_plot3.getPixel(x+5,          z-z_off+5);
                                    col_side3=image_plot3.getPixel(x+x_off+5,    z+5);
                                    col_side4=image_plot3.getPixel(x+5,          z+z_off+5);
                                    c1=(col_side1.r+col_side1.b+col_side1.g);
                                    c2=(col_side2.r+col_side2.b+col_side2.g);
                                    c3=(col_side3.r+col_side3.b+col_side3.g);
                                    c4=(col_side4.r+col_side4.b+col_side4.g);
                                    if (c1==0 || c2==0 || c3==0 || c4==0) edge2=1;
                                    dir_x=0;
                                    curve=0;
                                    corner2=0;
                                    if (c1!=0 && c3!=0) dir_x=1+8;
                                    if (c2!=0 && c4!=0) dir_x=0+8;
                                    if (c1!=0 && c2!=0 && c3==0 && c4==0) curve=8;
                                    if (c3!=0 && c4!=0 && c1==0 && c2==0) curve=6;
                                    if (c1!=0 && c4!=0 && c2==0 && c3==0) curve=7;
                                    if (c2!=0 && c3!=0 && c1==0 && c4==0) curve=9;


                                    if (edge2==0) {
                                        col_side1=image_plot3.getPixel(x-x_off+5,    z-z_off+5);
                                        col_side2=image_plot3.getPixel(x+x_off+5,    z-z_off+5);
                                        col_side3=image_plot3.getPixel(x+x_off+5,    z+z_off+5);
                                        col_side4=image_plot3.getPixel(x-x_off+5,    z+z_off+5);
                                        c1=(col_side1.r+col_side1.b+col_side1.g);
                                        c2=(col_side2.r+col_side2.b+col_side2.g);
                                        c3=(col_side3.r+col_side3.b+col_side3.g);
                                        c4=(col_side4.r+col_side4.b+col_side4.g);
                                        if (c1==0 || c2==0 || c3==0 || c4==0) {
                                            edge2=1;
                                        }
                                        if (c1==0 && c2!=0 && c3!=0 && c4!=0) curve=8;
                                        if (c1!=0 && c2==0 && c3!=0 && c4!=0) curve=9;
                                        if (c1!=0 && c2!=0 && c3==0 && c4!=0) curve=6;
                                        if (c1!=0 && c2!=0 && c3!=0 && c4==0) curve=7;
                                    }
                                    if (curve!=0) corner2=1;
                                }


                                if (y>=a109-2 && y<a115+2+ceil_heigher) {
                                    toggle2();
                                    if (pixel!=0) {
                                        if (edge==1) {

                                            if ((rand()%100)==0 && y>=a109-2+3) {
                                                AY[y] = BlockInfo(89, 0, 0, 0 );
                                            } else {
                                                if (red2==1) {
                                                    if (AY[y].id==0 || AY[y].id==8) AY[y] = BlockInfo(95, 0, red,0 );
                                                }  else {
                                                    if (rand()%30==0) {
                                                        AY[y] = BlockInfo(95, 0, ret_color(rand()%256,rand()%256,rand()%256),0 );
                                                    } else {
                                                        if (AY[y].id==0 || AY[y].id==8) AY[y] = BlockInfo(95, 0, white,0 );
                                                    }
                                                }
                                            }
                                        } else {
                                            if ( y==a109-2 && ((((int)xx+3)%5)==0 && (((int)zz+3)%5)==0) ) {
                                                AY[y] = BlockInfo(147, 0, 0, 0 );
                                            } else if ( y==a109-2 && AY[y].id!=147 && AY[a108-2].id!=152) {
                                                darkblue=sin(xx/90+zz/100) + sin(xx/100+zz/90) + sin(xx/110+zz/100) + sin(xx/100+zz/110) + sin(xx/110+zz/90) + sin(xx/90+zz/110);
                                                darkblue+=sin(xx/190+zz/200) + sin(xx/200+zz/190) + sin(xx/210+zz/200) + sin(xx/200+zz/210) + sin(xx/210+zz/190) + sin(xx/190+zz/210);
                                                darkblue+=(sin(xx/19+zz/20) + sin(xx/20+zz/19) + sin(xx/21+zz/20) + sin(xx/20+zz/21) + sin(xx/21+zz/19) + sin(xx/19+zz/21))/3;
                                                darkblue=((darkblue+14)/28)*15.9;
                                                AY[y] = BlockInfo(171, 0, (int)darkblue, 0 );
                                            } else if (AY[y].id!=147 && AY[y].id!=66 && AY[y].id!=27) {
                                                AY[y] = BlockInfo();
                                            }
                                        }
                                    }
                                }
                                else if (y==a115+2+ceil_heigher) {
                                    toggle2();
                                    if (pixel!=0) {
                                        if (((((int)xx+3)%5)==0 && (((int)zz+3)%5)==0)) {
                                            AY[y] = BlockInfo(89, 0, 0, 0 );
                                        } else if (edge==1) {
                                            if (corner2==1) {
                                                AY[y] = BlockInfo(251, 0, red, 0 );
                                                AY[y+1] = BlockInfo(66,0,curve,0);
                                            } else {
                                                if ( ((((int)xx+3)%15)==0 || (((int)zz+3)%15)==0) || ( col.r==254 && ( ((((int)xx+3)%5)==0 || (((int)zz+3)%5)==0) ) ) ) {
                                                    AY[y] = BlockInfo(152, 0, 0, 0 );
                                                    AY[y+1] = BlockInfo(27,0,dir_x,0);
                                                } else {
                                                    AY[y] = BlockInfo(251, 0, red, 0 );
                                                    AY[y+1] = BlockInfo(27,0,dir_x,0);
                                                }
                                            }
                                            rails++;
                                            AY[y+2]=BlockInfo();
//hoppa
                                            if (x>0            && AX[x-1][z][y+1].id!=27   && AX[x-1][z][y+1].id!=66  ) { AX[x-1][z][y+1]=BlockInfo(); AX[x-1][z][y+2]=BlockInfo(); }
                                            if (z>0            && AX[x][z-1][y+1].id!=27   && AX[x][z-1][y+1].id!=66  ) { AX[x][z-1][y+1]=BlockInfo(); AX[x][z-1][y+2]=BlockInfo(); }
                                            if (x<511          && AX[x+1][z][y+1].id!=27   && AX[x+1][z][y+1].id!=66  ) { AX[x+1][z][y+1]=BlockInfo(); AX[x+1][z][y+2]=BlockInfo(); }
                                            if (z<511          && AX[x][z+1][y+1].id!=27   && AX[x][z+1][y+1].id!=66  ) { AX[x][z+1][y+1]=BlockInfo(); AX[x][z+1][y+2]=BlockInfo(); }
                                            if (x>0 && z>0     && AX[x-1][z-1][y+1].id!=27 && AX[x-1][z-1][y+1].id!=66) { AX[x-1][z-1][y+1]=BlockInfo(); AX[x-1][z-1][y+2]=BlockInfo(); }
                                            if (z>0 && x<511   && AX[x+1][z-1][y+1].id!=27 && AX[x+1][z-1][y+1].id!=66) { AX[x+1][z-1][y+1]=BlockInfo(); AX[x+1][z-1][y+2]=BlockInfo(); }
                                            if (x<511 && z<511 && AX[x+1][z+1][y+1].id!=27 && AX[x+1][z+1][y+1].id!=66) { AX[x+1][z+1][y+1]=BlockInfo(); AX[x+1][z+1][y+2]=BlockInfo(); }
                                            if (z<511 && x>0   && AX[x-1][z+1][y+1].id!=27 && AX[x-1][z+1][y+1].id!=66) { AX[x-1][z+1][y+1]=BlockInfo(); AX[x-1][z+1][y+2]=BlockInfo(); }
                                            hoppa(AX,x,z,y);
//                                            AY[y+3]=BlockInfo();
                                        } else if (rand()%30==0) {
                                            AY[y] = BlockInfo(95, 0, ret_color(rand()%256,rand()%256,rand()%256),0 );
                                        } else {
                                            if (red2==1) {
                                                if (AY[y].id==0 || AY[y].id==8) AY[y] = BlockInfo(95, 0, red,0 );
                                            } else {
                                                if (AY[y].id==0 || AY[y].id==8) AY[y] = BlockInfo(95, 0, white,0 );
                                            }
                                        }
                                    }
                                }
                                else if (y==a108-2) {
                                    if (pixel!=0) {
                                        if (edge==0 &&
                                            (   (((int)xx+2)%5)==0 && (((int)zz+2)%5)==0 ||
                                                (((int)xx+4)%5)==0 && (((int)zz+2)%5)==0 ||
                                                (((int)xx+4)%5)==0 && (((int)zz+4)%5)==0 ||
                                                (((int)xx+2)%5)==0 && (((int)zz+4)%5)==0
                                            ) ) {
                                            AY[y] = BlockInfo(89, 0, 0, 0 );
                                        } else if ((((int)xx+3)%5)==0 && (((int)zz+3)%5)==0 ) {
                                            int what=rand()%20;
                                            setBoom(region,x,z,y);
//                                            AY[a107-2] = BlockInfo(251, 0, 0, 0 );
                                            AY[a109-2] = BlockInfo(147, 0, 0, 0 );
                                        } else if ((((int)xx+1+(rand()%5))%5)==0 && (((int)zz+1+(rand()%5))%5)==0 && edge==0 && edge2==0) {
                                            int what=rand()%16;
                                            if (what<15) setRabbits(region,x,z,y);
                                            else if (what==15) setWolf(region,x,z,y);
                                            else if (what==16) setRandom(region,x,z,y);
                                            else {
                                                setBoom(region,x,z,y); //AY[a107-2] = BlockInfo(251, 0, 0, 0 );
                                            }
                                            AY[a109-2] = BlockInfo(147, 0, 0, 0 );
                                        } else if ((((int)xx+1+(rand()%5))%5)==0 && (((int)zz+1+(rand()%5))%5)==0 && edge==0 && edge2==0) {
                                            int what=rand()%16;
                                            if (what<15) setRabbits(region,x,z,y);
                                            else if (what==15) setWolf(region,x,z,y);
                                            else if (what==16) setRandom(region,x,z,y);
                                            else {
                                                setBoom(region,x,z,y); //AY[a107-2] = BlockInfo(251, 0, 0, 0 );
                                            }
                                            AY[a109-2] = BlockInfo(147, 0, 0, 0 );
                                        }
                                         else {
                                            if (!(rand()%5) && edge==0 && edge3==1) {
                                                //AY[y] = BlockInfo(251, 0, black, 0 );
                                                AY[y] = BlockInfo(89, 0, 0, 0 );
                                            } else {
                                                if (red2==1)
                                                    AY[y] = BlockInfo(251, 0, red, 0 );
                                                else
                                                    AY[y] = BlockInfo(251, 0, white,0 );
                                            }
                                        }
                                    }
                                }
//                                else if (y==a107-2 && (((int)xx+3)%5)==0 && (((int)zz+3)%5)==0 && pixel!=0) { AY[y] = BlockInfo(251, 0, ret_color(rand()%256,rand()%256,rand()%256),0 );  }
//                                else if (y==a107-2) {  if (pixel!=0 && (rand()%2)==0)      AY[y] = BlockInfo(251-((251-95)*(rand()%2)), 0, ret_color(rand()%256,rand()%256,rand()%256),0 );  }
//                                else if (y==106-2) {  if (pixel!=0 && (rand()%4)==0)      AY[y] = BlockInfo(251-((251-95)*(rand()%2)), 0, ret_color(rand()%256,rand()%256,rand()%256),0 );  }
//                                else if (y==105-2) {  if (pixel!=0 && (rand()%8)==0)      AY[y] = BlockInfo(251-((251-95)*(rand()%2)), 0, ret_color(rand()%256,rand()%256,rand()%256),0 );  }
//                                else if (y==104-2) {  if (pixel!=0 && (rand()%16)==0)     AY[y] = BlockInfo(251-((251-95)*(rand()%2)), 0, ret_color(rand()%256,rand()%256,rand()%256),0 );  }
                               if (AY[y].id==95 && AY[y].data==0) AY[y]=BlockInfo(20,0,0,0);
                            }
                        }
                    }

                    printf(" %d blocks = %5.2f%, #rails = %d, = %7.3f kilometers\n",num_blocks,100.0*(float)num_blocks/(1024*1024*64),rails,(float)rails/1000);
                    rails=0;
                }

                printf(" ");
                first_MCEDIT=0;
                region_x_old=0;
                region_z_old=0;
//                file_name_MCA = MCAFileNameXZ(region_x, region_z);
                mkdir("/Saves/test/region/done0");
                sprintf(tmp, "/Saves/Test/region/done0/r.%d.%d.mca", region_x, region_z);
                file_name_MCA = tmp;
                editor.setRegion(region);
                CopyFile(tmp,fname.c_str(),true);

//                char tmp[256];
//                sprintf(tmp, "/Saves/Test/region/done/r.%d.%d.mca", region_x, region_z);
//                CopyFile(file_name_MCA.c_str(),tmp,true);

                if (MCEDITOR_stop==1 || file_exists("stop.txt")) {
                    printf("Stop requested, exiting\n");
//                    system("/saves/copy_test.bat");
                    send_message='x';
                    return 0;
                }
            }
        }
    }
    return 0;
}

int ret_color2(int r, int g, int b);
int ret_color3(int r, int g, int b);

int main_mceditor5(int box_x, int box_y, int box_z, unsigned char* mc)
{
    int region_x=0;
    int region_z=0;

    int skippy=0;
    int skippy2=0;
    int contin=1;
    int skipping=1;
    int light=0;
    int size_regions=0;
	srand(time(0));
	int first_loop=1;
    remove_block_entities=1;
    bool zisout=false;
    bool xisout=false;
    while (size_regions<60) {
        size_regions++;
        for (region_x=0; region_x<size_regions && MCEDITOR_stop==0; region_x++) {

            zisout=false;

            for (region_z=0; region_z<size_regions && MCEDITOR_stop==0; region_z++) {
                region_xxx=region_x;
                region_zzz=region_z;
                if (region_x<size_regions-1 && region_z<size_regions-1) {
                    continue;
                }
                toggle_2=0;toggle_3=0;
                if (contin==1) {
                    contin=0;
                }
                chunk_offsetx=region_x*32;
                chunk_offsetz=region_z*32;

                if (xisout) {
                    xisout=false;
                    continue;
                }

                if ((chunk_offsetz*16+512)>=box_z && (chunk_offsetx*16+512)>=box_y) {
                    printf("End z && x\n");
                    continue;
                }
/*
                if ((chunk_offsetx*16+512)>=box_y) {
                    printf("End x\n");
                    continue;
                }
*/
                x00=0;
                y00=0;
                z00=0;
                yl=255;  xl=512; zl=512;


    //            file_name_MCA = MCAFileNameXZ(region_x, region_z);
    //            editor.mca_coder.loadMCA(file_name_MCA);
                char tmp[256];
                sprintf(tmp, "/Saves/Test/region/r.%d.%d.mca", region_x, region_z);
//                string fname=MCAFileNameXZ(region_x, region_z);
                string fname=tmp;
                if ( file_exists(fname.c_str() ) ) {
                    if (skippy2>0) printf("\n");
                    skippy2=0;
                    if (skippy==0)
                        printf("File(s) exists, skipping %s",fname.c_str());
                    else
                        printf(", %s",fname.c_str());
                    skippy++;
                    continue;
                }


                char comm[100];
//                sprintf(comm,"copy %s %s","/Saves/Leeg/region/r.0.0.mca",fname.c_str());
                CopyFile("/Saves/Leeg/region/r.0.0.mca",fname.c_str(),false);

//                region.clearRegion();
                MCRegion region(x00, z00, y00, xl, zl, yl);

                first_MCEDIT=1;
                editor.mca_coder.loadMCA("/Saves/Leeg/region/r.0.0.mca");
                editor.mca_coder.setPOSITIONS();
                first_MCEDIT=0;
                region_x_old=0,region_z_old=0;

                printf("- Creating region r.%d.%d.mca: ",region_x,region_z);

                size_t max_off=box_x*box_y*box_z*4;

                BlockInfo*** AX=region.A;
                if (1) {
                    int num_blocks=0;

                    printf(" City:\b\b\b\b\b\b");
                    for (int x = 0; x < xl; x++) {
                        xx=x+chunk_offsetx*16;
                        if (xx>box_y)  { xisout=true; break; }
                        BlockInfo** AZ=AX[x];
                        int cube_y=xx;
                        for (int z = 0; z < zl; z++) {
                            zz=z+chunk_offsetz*16;
                            if (zz>box_z) { break; }
                            BlockInfo* AY=AZ[z];
                            toggle2();
                            int cube_z=zz;
                            for (int y = 0; y < 256; y++) {
                                if (y==0) {
                                    AY[y] = BlockInfo(7, 0, 0 );
                                }
                                if (y<box_x+1) {
                                    if (y==0) {
                                        if (!(rand()%50)) AY[y] = BlockInfo(89, 0, 0, 0 );
                                        else AY[y] = BlockInfo(7, 0, 0 );
                                    } else {
                                        int cube_x=y-1;
                                        size_t off=(cube_x+(box_y-1-cube_y)*box_x+cube_z*box_x*box_y)*4;
                                        if (off>=max_off) {
                                            printf("Error offset %d>=%d\n",off,max_off);
                                        }

                                        if (mc[off+3]>0) {
                                            int r, g, b;
                                            r=mc[off];
                                            g=mc[off+1];
                                            b=mc[off+2];
                                            AY[y] = BlockInfo(251, 0, ret_color2(r,g,b),0 );
                                            num_blocks++;
                                        }
                                    }
                                } else {
                                    break;
                                }

//                                if (AY[y].id==0 || AY[y].id==8) AY[y] = BlockInfo(95, 0, ret_color(r,g,b),0 );
//                                AY[y] = BlockInfo(95, 0, ret_color(rand()%256,rand()%256,rand()%256),0 );

                            }
                        }
                    }

                    printf(" %d blocks = %5.2f%\n",num_blocks,100.0*(float)num_blocks/(1024*1024*64));
                }

                printf(" ");
                first_MCEDIT=0;
                region_x_old=0;
                region_z_old=0;
//                file_name_MCA = MCAFileNameXZ(region_x, region_z);
                mkdir("/Saves/test/region/done0");
                sprintf(tmp, "/Saves/Test/region/done0/r.%d.%d.mca", region_x, region_z);
                file_name_MCA = tmp;
                editor.setRegion(region);
                CopyFile(tmp,fname.c_str(),false);

//                char tmp[256];
//                sprintf(tmp, "/Saves/Test/region/done/r.%d.%d.mca", region_x, region_z);
//                CopyFile(file_name_MCA.c_str(),tmp,true);

                if (MCEDITOR_stop==1 || file_exists("stop.txt")) {
                    printf("Stop requested, exiting\n");
//                    system("/saves/copy_test.bat");
                    send_message='x';
                    return 0;
                }
            }
        }
    }
    return 0;
}

int main_mceditor6(int box_x, int box_y, int box_z, unsigned char* mc, int box_x_block_start, int box_y_block_start, int box_z_block_start, int box_x_total_start, int box_y_total_start, int box_z_total_start);
int main_mceditor6_plot(int box_x, int box_y, int box_z, unsigned char* mc,
                   int box_x_block_start, int box_y_block_start, int box_z_block_start,
                   int box_x_total_start, int box_y_total_start, int box_z_total_start);

int plotting=0;

int main_mceditor5_from_file(char* dat_filename, char* voxel_filename) {
    random_pixel=sf::Color(64+rand()%64,64+rand()%64,64+rand()%64,255);
    int box_x,box_y,box_z;
    char octant[200]="";
    int box_x_block_start;
    int box_y_block_start;
    int box_z_block_start;
    int box_x_block_end;
    int box_y_block_end;
    int box_z_block_end;
    int box_x_total_start;
    int box_y_total_start;
    int box_z_total_start;
    int box_x_total_end;
    int box_y_total_end;
    int box_z_total_end;
    long num_bytes;
    double num_bytes_double;
    char area[200]="";


    char line[200]="";
    FILE * pFile;
    pFile = fopen ( dat_filename , "rb" );
//    pFile = fopen ( "../cut/voxel.dat" , "rb" );
    if (pFile==NULL)
    {
        printf("FILE NOT FOUND: %s\n",dat_filename);
        return (1);
    }

    if( fgets (line,200, pFile)!=NULL )
    {
        int numread=sscanf(line,"X=%d Y=%d Z=%d\n",&box_x,&box_y,&box_z);
        if (numread!=3) {
            printf("Error reading X Y Z %s\n",dat_filename);
//            printf("Error reading X Y Z../cut/voxel.dat\n");
            fclose(pFile);
            return (0);
        }
        printf("box_x=            %6d box_y=           %6d  box_z=             %6d\n",box_x,box_y,box_z);
        if( fgets (line,200, pFile)!=NULL )
        {
            numread=sscanf(line,"OCTANT=%199[^\n]",octant);
            if (numread!=1) {
                printf("Error reading OCTANT %s\n",dat_filename);
//                printf("Error reading OCTANT ../cut/voxel.dat\n");
                fclose(pFile);
                return (0);
            }
        }
        printf("octant=%s\n",octant);
        if( fgets (line,200, pFile)!=NULL )
        {
            numread=sscanf(line,"BYTES=%ld\n",&num_bytes);
            if (numread!=1) {
                printf("Error reading BYTES %s num_bytes=%ld\n",dat_filename,num_bytes);
//                printf("Error reading BYTES ../cut/voxel.dat num_bytes=%ld\n",num_bytes);
                fclose(pFile);
                return (0);
            }
        }
        printf("num_bytes=%ld\n",num_bytes);
        if( fgets (line,200, pFile)!=NULL )
        {
            numread=sscanf(line,"ABS MIN X=%d Y=%d Z=%d\n",&box_x_block_start,&box_y_block_start,&box_z_block_start);
            if (numread!=3) {
                printf("Error reading ABS MIN %s\n",dat_filename);
//                printf("Error reading ABS MIN../cut/voxel.dat\n");
                fclose(pFile);
                return (0);
            }
        }
        printf("box_x_block_start=%6d box_y_block_start=%6d box_z_block_start=%6d\n",box_x_block_start,box_y_block_start,box_z_block_start);
        if( fgets (line,200, pFile)!=NULL )
        {
            numread=sscanf(line,"ABS MAX X=%d Y=%d Z=%d\n",&box_x_block_end,&box_y_block_end,&box_z_block_end);
            if (numread!=3) {
                printf("Error reading ABS MAX../cut/voxel.dat\n");
                printf("Error reading ABS MAX %s\n",dat_filename);
                fclose(pFile);
                return (0);
            }
        }
        printf("box_x_block_end=  %6d box_y_block_end=  %6d box_z_block_end=  %6d\n",box_x_block_end,box_y_block_end,box_z_block_end);
        if( fgets (line,200, pFile)!=NULL )
        {
            numread=sscanf(line,"TOTAL MIN X=%d Y=%d Z=%d\n",&box_x_total_start,&box_y_total_start,&box_z_total_start);
            if (numread!=3) {
//                printf("Error reading TOTAL MIN../cut/voxel.dat\n");
                printf("Error reading TOTAL MIN %s\n",dat_filename);
                fclose(pFile);
                return (0);
            }
        }
        printf("box_x_total_start=%6d box_y_total_start=%6d box_z_total_start=%6d\n",box_x_total_start,box_y_total_start,box_z_total_start);
        if( fgets (line,200, pFile)!=NULL )
        {
            numread=sscanf(line,"TOTAL MAX X=%d Y=%d Z=%d\n",&box_x_total_end,&box_y_total_end,&box_z_total_end);
            if (numread!=3) {
                printf("Error reading TOTAL MAX %s\n",dat_filename);
//                printf("Error reading TOTAL MAX../cut/voxel.dat\n");
                fclose(pFile);
                return (0);
            }
        }
        printf("box_x_total_end=  %6d box_y_total_end=  %6d box_z_total_end=  %6d\n",box_x_total_end,box_y_total_end,box_z_total_end);
        if( fgets (line,200, pFile)!=NULL )
        {
            numread=sscanf(line,"AREA=%199[^\n]",area);
            if (numread!=1) {
                printf("Error reading AREA %s\n",dat_filename);
//                printf("Error reading AREA../cut/voxel.dat\n");
                fclose(pFile);
                return (0);
            }
        }
        printf("area=%s\n",area);

/*
    ofs << "X=" << box_x << " Y=" << box_y << " Z=" << box_z << "\n";
    ofs << "OCTANT=" << fn.c_str() << "\n";
    ofs << "BYTES=" << tot_off << "\n";

    ofs << "ABS MIN X=" << box_x_block_start << " Y=" << box_y_block_start << " Z=" << box_z_block_start << "\n";
    ofs << "ABS MAX X=" << box_x_block_end   << " Y=" << box_y_block_end   << " Z=" << box_z_block_end   << "\n";
    ofs << "TOTAL MIN X=" << box_x_total_start << " Y=" << box_y_total_start << " Z=" << box_z_total_start << "\n";
    ofs << "TOTAL MAX X=" << box_x_total_end   << " Y=" << box_y_total_end   << " Z=" << box_z_total_end   << "\n";
    ofs << "AREA = " << area   << "\n";
*/


        printf("Loaded %s  X=%d y=%d Z=%d OCTANT=%s\n", dat_filename, box_x, box_y, box_z, octant);
//        printf("Loaded ../cut/voxel.dat  X=%d y=%d Z=%d OCTANT=%s\n", box_x, box_y, box_z, octant);
    }
    fclose(pFile);

    size_t tot_off=box_x*box_y*box_z*4;


    printf("Setting %dx%dx%dx4 s=%d bytes ", box_x, box_y, box_z, tot_off);
    unsigned char *mc = new unsigned char [tot_off];
    if (mc!=NULL) printf("OK!\n");
    else {
        printf("Error allocating memory\n");
        return (1);
    }
    printf("Ready\n");

//    std::memset(mc, 0x0, box_x * box_y * box_z * 4);

    printf("Loading %s (%dx%dx%dx4)(%u bytes)", voxel_filename, box_x, box_y, box_z, tot_off);
//    printf("Loading ../cut/voxel.raw (%dx%dx%dx4)(%u bytes)", box_x, box_y, box_z, tot_off);
    unsigned long long lSize;
    size_t result;
    pFile = fopen ( voxel_filename , "rb" );
    if (pFile==NULL) {
        printf("File error: %s\n",voxel_filename);
        delete [] mc;
        return (1);
    }
    fseek (pFile , 0 , SEEK_END);
    lSize = ftell (pFile);
    rewind (pFile);

    if (lSize!=tot_off) {
        printf(" Error (size) %s ... %u <-> %u\n", voxel_filename, lSize,tot_off);
//        fclose(pFile);
//        delete [] mc;
//        return (1);
    } else {
        printf(" -> Ok! -> Loading");
    }

    result = fread(mc,1,tot_off,pFile);
    fclose(pFile);

    if (result!=tot_off) {
        printf("Error loading %s\n",voxel_filename);
        delete [] mc;
        return (1);
    }

    printf(" -> Ok! -> %lld bytes loaded",result);
    printf(" -> Editing\n");

    printf("\n");
    printf("box_x_block_start=%6d   box_y_block_start=%6d   box_z_block_start=%6d\n",   box_x_block_start,                      box_y_block_start,                      box_z_block_start       );
    printf("box_x_block_end  =%6d   box_y_block_end  =%6d   box_z_block_end  =%6d\n",   box_x_block_end,                        box_y_block_end,                        box_z_block_end         );
    printf("dif_x_block      =%6d   dif_y_block      =%6d   dif_z_block      =%6d\n",   box_x_block_end-   box_x_block_start,   box_y_block_end-box_y_block_start,      box_z_block_end-box_z_block_start);
    printf("\n");
    printf("box_x_total_start=%6d   box_y_total_start=%6d   box_z_total_start=%6d\n",   box_x_total_start,                      box_y_total_start,                      box_z_total_start       );
    printf("box_x_total_end=  %6d   box_y_total_end=  %6d   box_z_total_end=  %6d\n",   box_x_total_end,                        box_y_total_end,                        box_z_total_end         );
    printf("dif_x_total      =%6d   dif_y_total      =%6d   dif_z_total      =%6d\n",   box_x_total_end-box_x_total_start,      box_y_total_end-box_y_total_start,      box_z_total_end-box_z_total_start);
    printf("\n");
    printf("Setting           %6d                    %6d                      %6d\n",   box_x,                                  box_y,                                  box_z);
    printf("\n");

//    main_mceditor6(
//        box_x, box_y, box_z,
//        mc,
//        box_x_block_start,                      box_y_block_start,                      box_z_block_start,
//        box_x_total_start,                      box_y_total_start-2048,                 box_z_total_start-2048
//    );
//    if (mirror!=4) sprintf(mc_text2,"%s",octant);
//    else sprintf(mc_text2,"");
    sprintf(mc_text2,"%s",octant);
    if (plotting) {
        main_mceditor6_plot(
            box_x, box_y, box_z,
            mc,
            box_x_block_start,                      box_y_block_start-2048,                     box_z_block_start+2048,
            box_x_total_start,                      box_y_total_end,                            box_z_total_start
        );
    } else {
        main_mceditor6(
            box_x, box_y, box_z,
            mc,
            box_x_block_start,                      box_y_block_start-2048,                     box_z_block_start+2048,
            box_x_total_start,                      box_y_total_end,                            box_z_total_start
        );
    }
    delete [] mc;
    char naam[200];
    mkdir("../cut/done");
    if (mirror==4) {
    } else {
        sprintf(naam,"move ..\\cut\\%s*.* ..\\cut\\done\\",voxel_filename);
        system(naam);
        sprintf(naam,"move ..\\cut\\%s*.* ..\\cut\\done\\",dat_filename);
        system(naam);
    }
}


int main_mceditor6(int box_x, int box_y, int box_z, unsigned char* mc,
                   int box_x_block_start, int box_y_block_start, int box_z_block_start,
                   int box_x_total_start, int box_y_total_start, int box_z_total_start)
{
    int rand_color=rand()%15;
    int region_x=0;
    int region_z=0;
//        printf("here 2\n");

    int skippy=0;
    int skippy2=0;
    int contin=1;
    int skipping=1;
    int light=0;
    int size_regions=0;
	srand(time(0));
	int first_loop=1;
    remove_block_entities=1;
    bool zisout=false;
    bool xisout=false;
    while (size_regions<450) {
        size_regions++;
        for (region_x=0; region_x<size_regions && MCEDITOR_stop==0; region_x++) {
            zisout=false;
            for (region_z=0; region_z<size_regions && MCEDITOR_stop==0; region_z++) {
                region_xxx=region_x;
                region_zzz=region_z;
                if (region_x<size_regions-1 && region_z<size_regions-1) {
                    continue;
                }
                toggle_2=0;toggle_3=0;
                if (contin==1) {
                    contin=0;
                }
                chunk_offsetx=region_x*32;;
                chunk_offsetz=region_z*32;

                x00=0;
                y00=0;
                z00=0;
                yl=256;  xl=512; zl=512;

                if ( chunk_offsetx*16+512 <  -box_y_block_start + box_y_total_start) continue;
                if ( chunk_offsetz*16+512 < + box_z_block_start - box_z_total_start) continue;
                if ( chunk_offsetx*16 > box_y - box_y_block_start  + box_y_total_start) continue;
                if ( chunk_offsetz*16 > box_z + box_z_block_start - box_z_total_start) continue;

                load_leeg=0;

                string fname=MCAFileNameXZ(region_x, region_z);
                char tmp[256];
                sprintf(tmp, "/Saves/Test/region/done0/r.%d.%d.mca", region_x, region_z);
                fname=tmp;
                if ( !file_exists(fname.c_str() ) ) {
                    if (!plotting) printf("File %s doesn't exists, creating new ",fname.c_str());
                    load_leeg=1;
                }

//                region.clearRegion();
                MCRegion region(x00, z00, y00, xl, zl, yl);

                int num_blocks=0;

                BlockInfo*** AX=region.A;

                if (skippy2>0) printf("\n");
//                if (skippy>0 || skippy2>0) printf("\n");
                skippy=0;
                skippy2=0;
                scan_image.create(512,512);
                int real_max_x=-std::numeric_limits<int>::max();
                int real_min_x=std::numeric_limits<int>::max();

                int real_max_z=-std::numeric_limits<int>::max();
                int real_min_z=std::numeric_limits<int>::max();

                int real_max_y=-std::numeric_limits<int>::max();
                int real_min_y=std::numeric_limits<int>::max();

                if (plotting) load_leeg=1;
                if (load_leeg) {
                    static bool first=true;
//                    if (first) {
                        remove_block_entities=1;
                        first_MCEDIT=1;
                        editor.mca_coder.loadMCA("/Saves/Leeg/region/r.0.0.mca");
                        first=false;
/*
                    } else {
                        for (int x = 0; x < xl; x++) {
                            BlockInfo** AZ=AX[x];
                            for (int z = 0; z < zl; z++) {
                                BlockInfo* AY=AZ[z];
                                for (int y = 0; y < 256; y++) {
                                        AY[y]=BlockInfo();
                                }
                                scan_image.setPixel(x,z,sf::Color(0,0,0,0));
                            }
                        }
                    }
*/

                    editor.mca_coder.setPOSITIONS();
                    first_MCEDIT=0;
                    region_x_old=0,region_z_old=0;
                    if (!plotting) printf("- Creating new region r.%d.%d.mca: ",region_x,region_z);
                    reset_block();
                } else {
                    remove_block_entities=0;
                    printf("File %s exists...",fname.c_str());
                    if (mirror==1) {
                        printf("mirror=1, continuing\n");
                        continue;
                    }
                    first_MCEDIT=1;
                    editor.mca_coder.loadMCA(fname.c_str());
                    first_MCEDIT=0;
                    region_x_old=0,region_z_old=0;

                    for (int x = 0; x < xl; x++) {
                        BlockInfo** AZ=AX[x];
                        for (int z = 0; z < zl; z++) {
                            toggle2();
                            BlockInfo* AY=AZ[z];
                            int max_y=-1;
                            for (int y = 0; y < 256; y++) {
                                BlockInfo bi=editor.mca_coder.getBlock(x,z,y);
                                if (bi.id!=0) {
                                    num_blocks++;
                                    AY[y]=BlockInfo(bi.id,bi.add,bi.data,bi.block_light,bi.sky_light);
                                    if (mcglobal==6) {
                                        if (mcglobal3>0 && y<=mcglobal3) {
                                            max_y=y;
                                        }
                                    } else if (mcglobal==7) {
                                        if (mcglobal3>0 && y==mcglobal3) {
                                            max_y=y;
                                        }
                                    } else {
                                        max_y=y;
                                    }
                                }
                                if (y<real_min_y) real_min_y=y;
                            }
                            if (max_y!=-1) {
                                int r_m,g_m,b_m;
                                ret_color_rev( AY[max_y].data, r_m, g_m, b_m );
                                scan_image.setPixel(x,z,sf::Color(r_m,g_m,b_m,255));

                                if (max_y>real_max_y) real_max_y=max_y;
                                if (x>real_max_x) real_max_x=x;
                                if (x<real_min_x) real_min_x=x;
                                if (z>real_max_z) real_max_z=z;
                                if (z<real_min_z) real_min_z=z;

                            } else {
                                scan_image.setPixel(x,z,sf::Color(0,0,0,0));
                            }
                        }
                    }
                    printf("  %d Blocks.  Adding: ",num_blocks);
                    reset_block();
                }
                region_counter[region_x][region_z]++;
/////

                char comm[100];

                size_t max_off=box_x*box_y*box_z*4;

                int num_blocks_added=0;
                int num_blocks_replaced=0;
                int num_blocks_deleted=0;
                int num_blocks_same=0;
                if (1) {
                    printf(" City:\b\b\b\b\b\b");
                    for (int x = 0; x < xl; x++) {
                        xx=x+chunk_offsetx*16;
                        BlockInfo** AZ=AX[x];
//ayay
                        int cube_y=xx + box_y_block_start - box_y_total_start;

                        for (int z = 0; z < zl; z++) {
                            zz=z+chunk_offsetz*16;
                            BlockInfo* AY=AZ[z];
                            toggle2();
                            int cube_z=zz - box_z_block_start+box_z_total_start;
                            int min_y=-1;
                            int max_y=-1;
                            int r_m;
                            int g_m;
                            int b_m;
                            if (load_leeg) scan_image.setPixel(x,z,sf::Color(0,0,0,0));
                            if (cube_y<0 || cube_y>=box_y) continue;
                            if (cube_z<0 || cube_z>=box_z) continue;

                            if (x>real_max_x) real_max_x=x;
                            if (x<real_min_x) real_min_x=x;
                            if (z>real_max_z) real_max_z=z;
                            if (z<real_min_z) real_min_z=z;

                            for (int y = 0; y < 256; y++) {
                                int o_id=AY[y].id;

//help
//                                if (o_id!=0) {
//                                    AY[y]=BlockInfo();
//                                }
                                if (y==0) {
                                    if (!(rand()%200)) {
//                                        if (AY[y].id==0) num_blocks_added++;
//                                        else num_blocks_replaced++;
                                        AY[y] = BlockInfo(89, 0, 0, 0 );
                                    } else {
//                                        if (AY[y].id==0) num_blocks_added++;
//                                        else num_blocks_replaced++;
                                        if ((xx+zz)%2)
                                            AY[y] = BlockInfo(251, 0, ret_color((128+region_z*25)%256,(128+region_x*37)%256,0),0 );
                                        else
                                            AY[y] = BlockInfo(251, 0, rand_color,0 );
                                    }
//                                    min_y=0;
//                                    max_y=0;
//                                    ret_color_rev( AY[y].data, r_m, g_m, b_m );
                                }


                                int cube_x=y - box_x_block_start + box_x_total_start;
                                if (y==box_x_block_start - box_x_total_start-1) {
                                    if (!(rand()%200)) {
//                                        if (AY[y].id==0) num_blocks_added++;
//                                        else num_blocks_replaced++;
                                        AY[y] = BlockInfo(89, 0, 0, 0 );
                                    } else {
//                                        if (AY[y].id==0) num_blocks_added++;
//                                        else num_blocks_replaced++;
                                        AY[y] = BlockInfo(251, 0, ret_color((128+region_z*25)%256,(128+region_x*37)%256,0),0 );
                                    }
//                                    max_y=y;
//                                    ret_color_rev( AY[y].data, r_m, g_m, b_m );
                                } else {
//                                    if (y==0) {
//                                        if (AY[y].id==0) num_blocks_added++;
//                                        else num_blocks_replaced++;
//                                        AY[y] = BlockInfo(251, 0, ret_color((128+region_z*25)%256,(128+region_x*37)%256,0),0 );
//                                    }
                                    if (cube_x<0 || cube_x>=box_x) continue;

                                    if (y>real_max_y) real_max_y=y;
                                    if (y<real_min_y) real_min_y=y;
//ayay
                                    size_t off=(cube_x+(box_y-1-cube_y)*box_x+cube_z*box_x*box_y)*4;
//                                    size_t off=(cube_x+cube_y*box_x+cube_z*box_x*box_y)*4;
                                    if (off>=max_off || off<0) {
                                        printf("Error offset %d>=%d\n",off,max_off);
                                        continue;
                                    }
                                    if (mc[off+3]>0) {
                                        if (min_y==-1) min_y=y;
                                        max_y=y;
                                        int r, g, b;
                                        r=mc[off];
                                        g=mc[off+1];
                                        b=mc[off+2];
                                        r_m=r;
                                        g_m=g;
                                        b_m=b;
//                                        if (!(rand()% (375-int(y*1.25)))) {
//                                            if (AY[y].id==0) num_blocks_added++;
//                                            else num_blocks_replaced++;
//                                            AY[y] = BlockInfo(89, 0, 0, 0 );
//                                        } else {
//                                            if (AY[y].id==0) num_blocks_added++;
//                                            else num_blocks_replaced++;
                                            int r2=r,g2=g,b2=b;
                                            AY[y] = BlockInfo(251, 0, ret_color(r2,g2,b2),0 );
//                                        }
                                    }
                                }
                                if (o_id==0 && AY[y].id!=0) num_blocks_added++;
                                else if (o_id!=0 && AY[y].id!=o_id) num_blocks_replaced++;
                                else if (o_id!=0 && AY[y].id==0) num_blocks_deleted++;
                                else if (AY[y].id!=0 && o_id==AY[y].id) num_blocks_same++;


//                                if (AY[y].id==0 || AY[y].id==8) AY[y] = BlockInfo(95, 0, ret_color(r,g,b),0 );
//                                AY[y] = BlockInfo(95, 0, ret_color(rand()%256,rand()%256,rand()%256),0 );

                            }

                            if (plotting) {
                                if (max_y!=-1) scan_image.setPixel(x,z,sf::Color(r_m,g_m,b_m,255));
                                else scan_image.setPixel(x,z,sf::Color(0,0,0,0));
                            } else {
                                if (max_y!=-1) {
                                    ret_color_rev( AY[max_y].data, r_m, g_m, b_m );
                                    scan_image.setPixel(x,z,sf::Color(r_m,g_m,b_m,255));
                                }
                                else scan_image.setPixel(x,z,sf::Color(0,0,0,0));
                            }
                            if (lights_on && min_y>2) {
                                if (!(rand()%100)) {
                                    if (AY[min_y-1].id==0) num_blocks_added++;
                                    else num_blocks_replaced++;
                                    AY[min_y-1] = BlockInfo(89, 0, 0, 0 );
//                                    if (AY[min_y].id==0) num_blocks_added++;
//                                    else num_blocks_replaced++;
//                                    AY[min_y] = BlockInfo(95, 0, ret_color(255,255,255), 0 );
                                }
                            }
                        }
                    }
                    int num_blocks_total=0;
                    for (int x = 0; x < xl; x++) {
                        BlockInfo** AZ=AX[x];

                        for (int z = 0; z < zl; z++) {
                            BlockInfo* AY=AZ[z];
                            for (int y = 0; y < 256; y++) {
                                if (AY[y].id!=0) {
                                    num_blocks_total++;
                                }
                            }
                        }
                    }
                    int num_blocks_deleted=0;
                    int num_blocks_same=0;
                    if (!plotting) printf("\n");
                    printf("\r%8d added. %8d replaced. %8d deleted. %8d same. Total = %8d = %5.2f%%  ",
                           num_blocks_added, num_blocks_replaced, num_blocks_deleted, num_blocks_same, num_blocks_total, 100.0*(float)num_blocks_total/(512*512*256));
                }
                printf("REGION=[%d][%d]  RR=[%3d-%3d] Y=[%3d-%3d] ZZ=[%3d-%3d] ",region_x,region_z,real_min_x,real_max_x,real_min_y,real_max_y,real_min_z,real_max_z);

                scan_x=region_x;
                scan_z=region_z;
                sprintf(mc_text1,"R.%d.%d.MCA",region_x,region_z);
                update_request=2;

                while (update_request) {
                    sf::sleep(sf::seconds(0.005));
                }

                if (!plotting) printf(" ");
                first_MCEDIT=0;
                region_x_old=0;
                region_z_old=0;
//                file_name_MCA = MCAFileNameXZ(region_x, region_z);
                mkdir("/Saves/test/region/done0");
                sprintf(tmp, "/Saves/Test/region/done0/r.%d.%d.mca", region_x, region_z);

                if (file_exists(tmp)) {
                    char cmd[200];
                    sprintf(cmd,"del %s",tmp);
                    while (replace_string(cmd,"/","\\"));
                    system(cmd);
                }
                file_name_MCA = tmp;
                if (!plotting) editor.setRegion(region);
                else printf("\n");

//                CopyFile(tmp,fname.c_str(),false);

//                char tmp[256];
//                sprintf(tmp, "/Saves/Test/region/done/r.%d.%d.mca", region_x, region_z);
//                CopyFile(file_name_MCA.c_str(),tmp,true);

                if (MCEDITOR_stop==1 || file_exists("stop.txt")) {
                    printf("Stop requested, exiting\n");
//                    system("/saves/copy_test.bat");
                    send_message='x';
                    return 0;
                }
            }
        }
    }
    return 0;
}

#include <../VOXEL.HPP>

extern std::vector<hit_one_region> vector_hit_regions;
extern hit_one_region* findRegion(int x, int z);
extern bool dont_write_to_region_voxels;
extern bool make_regions;
extern bool flushing_mode;

/*
#include <opencv2/core/core.hpp>

void splinterp(std::vector<cv::Vec4d>& out,std::vector<double> x);
double splinterpEval( std::vector<cv::Vec4d> spline, double t );
*/

int floor_y[512][512];

/*
void get_floor(MCRegion &R) {
    std::vector<double> value_vector;       value_vector.clear();
    std::vector<cv::Vec4d> equation_vector; equation_vector.clear();

    double value=0.0;
    value_vector.push_back((double)value);

    splinterp(equation_vector,value_vector);

    double value_interpolated;
    double index;
    value_interpolated=(float)splinterpEval(equation_vector, index);
}
*/

void get_floor(MCRegion &region, int height_add);
void fok_floor(MCRegion &region, int height_add);

int main_mceditor6_fixed(int region_x, int region_z, unsigned char* mc) {
//printf("hier 6\n");
   fast_sin_init();
    bool starting=true;
    hit_one_region* hit_one=findRegion(region_x, region_z);
//printf("hier 2\n");
    int rand_color=rand()%15;
//        printf("here 2\n");

    int box_x=256;
    int box_y=512;
    int box_z=512;
    int skippy=0;
    int skippy2=0;
    int contin=1;
    int skipping=1;
    int light=0;
    int size_regions=0;
	srand(time(0));
	int first_loop=1;
    remove_block_entities=1;
    bool zisout=false;
    bool xisout=false;

    region_xxx=region_x;
    region_zzz=region_z;
    toggle_2=0;toggle_3=0;
    if (contin==1) {
        contin=0;
    }
    chunk_offsetx=region_x*32;;
    chunk_offsetz=region_z*32;

    load_leeg=0;

    bool do_model=false;
extern std::string area;
    if (area=="Models") do_model=true;
    string fname=MCAFileNameXZ(region_x, region_z);
    char tmp[256];
    sprintf(tmp, "/Saves/Test/region/done0/r.%d.%d.mca", region_x, region_z);
    fname=tmp;
    if (file_exists("add_to_region.on")) {
        add_to_region=true;
        printf(" Add to region=on");
    } else add_to_region=false;

    if ( !file_exists(fname.c_str() ) ) {
        if (!plotting) printf("File %s doesn't exist, creating new ",fname.c_str());
        else {
            printf("Plotting: File %s doesn't exist, returning\n",fname.c_str());
            return 0;
        }
        load_leeg=1;
    } else {
//        if (region_x==6460 && region_z==-10413) {
//            printf("Updating %s ...\n",fname.c_str());
//        } else

        if (flushing && !(make_regions || flushing_mode)) {
            printf("flushing, file %s exists, adding to region...\n",fname.c_str());
        } else if (add_to_region) {
            printf("file %s exists, adding to region...\n",fname.c_str());
        } else if (!plotting) {
            printf("file %s exists, skipping...\n",fname.c_str());
            return 0;
        }
        else {
            if (plotting) printf(" Plotting: %s",fname.c_str());
        }
    }

//    region.initRegion();
//    region.clearRegion();
    MCRegion region(x00, z00, y00, xl, zl, yl);

    int num_blocks=0;

    BlockInfo*** AX=region.A;

    if (skippy2>0) printf("\n");
    skippy=0;
    skippy2=0;
    scan_image.create(512,512);
    int real_max_x=-std::numeric_limits<int>::max();
    int real_min_x=std::numeric_limits<int>::max();

    int real_max_z=-std::numeric_limits<int>::max();
    int real_min_z=std::numeric_limits<int>::max();

    int real_max_y=-std::numeric_limits<int>::max();
    int real_min_y=std::numeric_limits<int>::max();

//    if (plotting) load_leeg=1;
    if (load_leeg) {
        static bool first=true;

        remove_block_entities=1;
        first_MCEDIT=1;
        if (!file_exists("/Saves/Leeg/region/r.0.0.mca")) {
            if (!file_exists("../Leeg/region/r.0.0.mca")) {
                printf("Cannot find empty region template: %s or %s\n","/Saves/Leeg/region/r.0.0.mca","../Leeg/region/r.0.0.mca");
//                region.eraseRegion();
                return -1;
            } else {
                editor.mca_coder.loadMCA("../Leeg/region/r.0.0.mca");
            }
        } else {
            editor.mca_coder.loadMCA("/Saves/Leeg/region/r.0.0.mca");
        }
        editor.mca_coder.setPOSITIONS();
        first_MCEDIT=0;
        region_x_old=0,region_z_old=0;
        printf("- Creating region r.%d.%d.mca: ",region_x,region_z);

//        reset_block();
    } else {
        reset_block();
        remove_block_entities=0;
        printf(" File %s exists... ",fname.c_str());
        if (mirror==1) {
            printf("mirror=1, continuing\n");
//            region.eraseRegion();
            return 0;
        }
        first_MCEDIT=1;
        editor.mca_coder.loadMCA(fname.c_str());
        first_MCEDIT=0;
        region_x_old=0,region_z_old=0;
        printf("Ok. Testing: ");
        scan_image.create(512,512,sf::Color(0,0,0,0));
        for (int x = 0; x < xl; x++) {
            BlockInfo** AZ=AX[x];
            for (int z = 0; z < zl; z++) {
                toggle2();
                BlockInfo* AY=AZ[z];
                int max_y=-1;
                for (int y = 0; y < 256; y++) {
                    BlockInfo bi=editor.mca_coder.getBlock(x,z,y);
                    if (bi.id!=0) {
                        num_blocks++;
                        AY[y]=BlockInfo(bi.id,bi.add,bi.data,bi.block_light,bi.sky_light);
                        if (mcglobal==6) {
                            if (mcglobal3>0 && y<=mcglobal3) {
                                max_y=y;
                            }
                        } else if (mcglobal==7) {
                            if (mcglobal3>0 && y==mcglobal3) {
                                max_y=y;
                            }
                        } else {
                            max_y=y;
                        }
                    } else {
                        AY[y]=BlockInfo();
                    }
                    if (y<real_min_y) real_min_y=y;
                }
                if (max_y!=-1) {
                    int r_m,g_m,b_m;
                    ret_color_rev( AY[max_y].data, r_m, g_m, b_m );
                    scan_image.setPixel(x,z,sf::Color(r_m,g_m,b_m,255));

                    if (max_y>real_max_y) real_max_y=max_y;
                    if (x>real_max_x) real_max_x=x;
                    if (x<real_min_x) real_min_x=x;
                    if (z>real_max_z) real_max_z=z;
                    if (z<real_min_z) real_min_z=z;

                } else {
                    scan_image.setPixel(x,z,sf::Color(0,0,0,0));
                }
            }
        }
        printf(" Ok.\n");
        scan_x=region_x;
        scan_z=region_z;
        sprintf(mc_text1,"R.%d.%d.MCA",region_x,region_z);
//        if (!no_plotting) {
            update_request=2;
            while (update_request) {
                sf::sleep(sf::seconds(0.005));
            }
//        }
        if (plotting) {
//           region.eraseRegion();
           return 0;
        }
        else if (make_regions || flushing_mode) {
            printf("file %s exists, skipping...\n",fname.c_str());
            return 0;
        }

        printf("  %d Blocks.  Adding: ",num_blocks);
    }

    if (hit_one!=NULL) hit_one->index12++;

//    region_counter[region_x][region_z]++;

    char comm[100];

    size_t max_off=box_x*box_y*box_z*4;

    int num_blocks_added=0;
    int num_blocks_replaced=0;
    int num_blocks_deleted=0;
    int num_blocks_same=0;
    int height_add=0;

    int fff=1;
    if (file_exists("water.on")) {
        water_on=true;
        if (fff==1) printf("\n");
        fff=0;
        printf(" Water=on");
    } else water_on=false;

    if (file_exists("stone.on")) {
        stone_on=true;
        if (fff==1) printf("\n");
        fff=0;
        printf(" Stone=on");
    } else stone_on=false;

    if (file_exists("grass.on")) {
        grass_on=true;
        if (fff==1) printf("\n");
        fff=0;
        printf(" Grass=on");
    } else grass_on=false;

    if (file_exists("glass.on")) {
        glass_on=true;
        if (fff==1) printf("\n");
        fff=0;
        printf(" Glass=on");
    } else glass_on=false;

    int water_blue=ret_color(0,0,255);
    if (file_exists("blue_to_water.on")) {
        blue_to_water_on=true;
        if (fff==1) printf("\n");
        fff=0;
        printf(" Blue to water=on(color=%d)",water_blue);
        real_min_y=0;
    } else blue_to_water_on=false;

    if (file_exists("boom.on")) {
        boom_on=true;
        if (fff==1) printf("\n");
        fff=0;
        printf(" Boom=on");
    } else boom_on=false;

    if (file_exists("caves.on")) {
        caves_on=true;
        if (fff==1) printf("\n");
        fff=0;
        printf(" Caves=on");
    } else caves_on=false;

    if (file_exists("rooms.on")) {
        rooms_on=true;
        if (fff==1) printf("\n");
        fff=0;
        printf(" rooms=on");
    } else rooms_on=false;

    if (file_exists("coral.on")) {
        coral_on=true;
        if (fff==1) printf("\n");
        fff=0;
        printf(" Coral=on");
        height_add=7;
    } else coral_on=false;

    if (file_exists("maze.on")) {
        maze_on=true;
        if (fff==1) printf("\n");
        fff=0;
        printf(" Maze=on");
    } else maze_on=false;

    if (file_exists("lights.on")) {
        lights_on=true;
        if (fff==1) printf("\n");
        fff=0;
        printf(" Lights=on");
    } else lights_on=false;

    if (file_exists("massiv.on")) {
        massiv_on=true;
        if (fff==1) printf("\n");
        fff=0;
        printf(" Massiv=on");
    } else massiv_on=false;

    if (file_exists("turbo.on")) {
        turbo_on=true;
        if (fff==1) printf("\n");
        fff=0;
        printf(" Turbo=on");
    } else turbo_on=false;

    if (fff==0) printf("\n");

    if (1) {
        printf(" City:\b\b\b\b\b\b");
        for (int x = 0; x < xl; x++) {
            xx=x+chunk_offsetx*16;
            BlockInfo** AZ=AX[x];
//ayay
            int cube_y=x;

            for (int z = 0; z < zl; z++) {
                zz=z+chunk_offsetz*16;
                BlockInfo* AY=AZ[z];
                toggle2();
                int cube_z=z;
                int min_y=-1;
                int max_y=-1;
                int r_m;
                int g_m;
                int b_m;
                if (load_leeg) scan_image.setPixel(x,z,sf::Color(0,0,0,0));

                for (int y = height_add; y < 256; y++) {
                    int o_id=AY[y].id;
//help
//                                if (o_id!=0) {
//                                    AY[y]=BlockInfo();
//                                }
                    if (y==height_add) {
                        if (!(rand()%200)) {
                            AY[y] = BlockInfo(89, 0, 0, 0 );
                        } else {
                            if ((xx+zz)%2)
                                AY[y] = BlockInfo(251, 0, ret_color((128+region_z*25)%256,(128+region_x*37)%256,0),0 );
                            else
                                AY[y] = BlockInfo(251, 0, rand_color,0 );
                        }
                    }

                    int cube_x=y ;
                    size_t off=((y-height_add)+256*x+z*512*256)*4;
                    if (off>=max_off || off<0) {
                        printf("Error offset %d>=%d\n",off,max_off);
                        continue;
                    }
                    if (mc[off+3]>0) {
                        if (min_y==-1) min_y=y;
                        max_y=y;
                        int r, g, b;
                        r=mc[off];
                        g=mc[off+1];
                        b=mc[off+2];
                        r_m=r;
                        g_m=g;
                        b_m=b;
                        int r2=r,g2=g,b2=b;

                        int c=ret_color(r2,g2,b2);
//                        AY[y] = BlockInfo(1, 0, 0,0 );
                        AY[y] = BlockInfo(251, 0, c,0 );
                        if (massiv_on) {
                            for (int xxx=-4; xxx<5; xxx++) {
                                for (int zzz=-4; zzz<5; zzz++) {
                                    for (int yyy=-4; yyy<5; yyy++) {
                                        if (!(xxx==0 && yyy==0 && zzz==0)) {
                                            if (in_region(x+xxx, z+zzz, y+yyy, 0, 0, 0, xl , zl , yl)) {
                                                AX[x+xxx][z+zzz][y+yyy]=BlockInfo(251, 0, c, 0);
                                            }
                                        }
                                    }
                                }
                            }
                        }

                        if (x>real_max_x) real_max_x=x;
                        if (x<real_min_x) real_min_x=x;
                        if (y>real_max_y) real_max_y=y;
                        if (y<real_min_y) real_min_y=y;
                        if (z>real_max_z) real_max_z=z;
                        if (z<real_min_z) real_min_z=z;

                    }
                    if (o_id==0 && AY[y].id!=0) num_blocks_added++;
                    else if (o_id!=0 && AY[y].id!=o_id) num_blocks_replaced++;
                    else if (o_id!=0 && AY[y].id==0) num_blocks_deleted++;
                    else if (AY[y].id!=0 && o_id==AY[y].id) num_blocks_same++;
                }
//                if ((AY[0].id==0 && AY[1].id==0)) {
//                    AY[0] = BlockInfo(8, 0, 0, 0 );
//                    if (max_y<0) max_y=0;
//                    r_m=0; g_m=0; b_m=255;
//                }

                if (plotting) {
                    if (max_y!=-1) scan_image.setPixel(x,z,sf::Color(r_m,g_m,b_m,255));
                    else scan_image.setPixel(x,z,sf::Color(0,0,0,0));
                } else {
                    if (max_y!=-1) {
                        ret_color_rev( AY[max_y].data, r_m, g_m, b_m );
                        scan_image.setPixel(x,z,sf::Color(r_m,g_m,b_m,255));
                    }
                    else scan_image.setPixel(x,z,sf::Color(0,0,0,0));
                }
                if (lights_on && min_y>height_add) {
                    if (!do_model) {
                        if (!(rand()%75)) {
                            if (AY[min_y-1].id==0) num_blocks_added++;
                            else num_blocks_replaced++;
                            AY[min_y-1] = BlockInfo(89, 0, 0, 0 );
                        }
                    }
                }
            }
        }
        get_floor(region, height_add);
/*
        for (int x = 0; x < 512; x++) {
            BlockInfo** AZ=AX[x];
            for (int z = 0; z < 512; z++) {
                BlockInfo* AY=AZ[z];
                AY[floor_y[x][z]]=BlockInfo(89, 0, 0, 0 );
            }
        }
*/

        vector<pair<Pos, string> > SomeStuff;

        int num_blocks_total=0;
        int tears=0;
        int water=0;

        if (boom_on || rooms_on || caves_on) {
            editor.x_len = region.x_len, editor.z_len = region.z_len, editor.y_len = region.y_len;
            editor.x_ori = region.x_ori, editor.z_ori = region.z_ori, editor.y_ori = region.y_ori;
            editor.block_entities = region.B;
            editor.initArrays(editor.x_len + 00, editor.z_len + 00, 256);
            printf(" initBlocks\b\b\b\b\b\b\b\b\b\b\b");
            editor.initBlocks(region);
            printf(" computeSkyLight\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
            editor.computeSkyLight();
            ui ***skylight=editor.skylight;

            if (boom_on)
            for (int x = 0; x < xl; x++) {
                BlockInfo** AZ=AX[x];
                xx=x+chunk_offsetx*16;
                for (int z = 0; z < zl; z++) {
                    zz=z+chunk_offsetz*16;
                    BlockInfo* AY=AZ[z];
                    AY[0] = BlockInfo(7, 0, 0 );
                    for (int y = height_add; y < 256; y++) {
                        if (y+height_add<1) continue;
                        if (AY[y].id!=0 && AY[y].id!=8 && AY[y].id!=46 && y>floor_y[x][z]) {
                            num_blocks_total++;
                            float f_xx=xx+SEED;
                            float f_y=y+SEED;
                            float f_zz=zz+SEED;
                            int rr=int(2.0+2.0*sin((f_xx-f_zz+f_y)/158.77) + 8.0*(1.0+sin((f_xx+f_zz+f_y)/156.0))/2.0);
                            int b1=int( ( sin( float(f_xx)/279.83 + 0.35*sin( float(f_y)/185.83 ) ) + sin( float(f_y)/275.83 )  +  float(f_zz+ 0.27*sin( float(f_xx)/239.83 ) )/369.51 + 2.0)*300.0 + 500.0 )%300;
                            int b2=int( ( sin( float(f_xx+ 0.2*sin( float(f_zz)/345.83 ) )/299.83 ) + sin( float(f_y)/255.83 )  +  float(f_zz)/239.51 + 2.0  + 0.31*sin( float(f_y)/315.83 ))*300.0 + 500.0 )%300;
                            int b3=int( ( sin( float(f_xx+ 0.13*sin( float(f_zz)/445.83 ) )/139.83 ) + sin( float(f_y)/265.83 ) +  float(f_zz)/279.51 + 2.0  + 0.15*sin( float(f_y)/445.83 ))*300.0 + 700.0 )%350;
                            if (
                                    b3==75 || b3==211 || b1==140 || b1==190 || b2==135 || b2==288 ||
                                    b3==76 || b3==212 || b1==141 || b1==191 || b2==136 || b2==289 ||
                                    (b1+b2+b3)%300==75 || abs(b1+b2*2-b3+200)%300==220 ||
                                    (b1+b2+b3)%300==76 || abs(b1+b2*2-b3+200)%300==221

                                ) {
                                BlockInfo hop=AY[y];
                                if (!(rand()%25 && y<255)) {
                                    if (AY[y+1].id==0 && skylight[x][z][y+1]>=8) AY[y+1]=BlockInfo(46,0,0,0);
                                    num_blocks_total++;
                                }
                                if (y-1>=0  && AX[x][z][y-1].id==0 && skylight[x][z][y-1]==0) { num_blocks_total++;AX[x][z][y-1]=BlockInfo(46,0,0,0); if (AX[x][z][y-1-1].id==0) AX[x][z][y-1-1]=BlockInfo(hop.id,0,hop.data,0);}
                                if ((rand()%13)<=rr) if (x-1>=0  && AX[x-1][z][y].id==0 && skylight[x-1][z][y]==0) { num_blocks_total++;AX[x-1][z][y]=BlockInfo(46,0,0,0); if (AX[x-1][z][y-1].id==0) AX[x-1][z][y-1]=BlockInfo(hop.id,0,hop.data,0);}
                                if ((rand()%13)<=rr) if (x+1<512 && AX[x+1][z][y].id==0 && skylight[x+1][z][y]==0) { num_blocks_total++;AX[x+1][z][y]=BlockInfo(46,0,0,0); if (AX[x+1][z][y-1].id==0) AX[x+1][z][y-1]=BlockInfo(hop.id,0,hop.data,0);}
                                if ((rand()%13)<=rr) if (z-1>=0  && AX[x][z-1][y].id==0 && skylight[x][z-1][y]==0) { num_blocks_total++;AX[x][z-1][y]=BlockInfo(46,0,0,0); if (AX[x][z-1][y-1].id==0) AX[x][z-1][y-1]=BlockInfo(hop.id,0,hop.data,0);}
                                if ((rand()%13)<=rr) if (z+1<512 && AX[x][z+1][y].id==0 && skylight[x][z+1][y]==0) { num_blocks_total++;AX[x][z+1][y]=BlockInfo(46,0,0,0); if (AX[x][z+1][y-1].id==0) AX[x][z+1][y-1]=BlockInfo(hop.id,0,hop.data,0);}
                                if (y+1<256 && AX[x][z][y+1].id==0 && skylight[x][z][y+1]==0) { num_blocks_total++;AX[x][z][y+1]=BlockInfo(46,0,0,0); if (AX[x][z][y+1-1].id==0) AX[x][z][y+1-1]=BlockInfo(hop.id,0,hop.data,0);}
                            }
                        }
                    }
                }
            }
            int room_lights=0;
            printf("\ncounted=%d",num_blocks_total);
            int filled=0;
            num_blocks_total=0;
            int room_x=16;
            int room_y=14;
            int room_z=16;
            if (rooms_on)
            for (int x = 0; x < xl; x++) {
                BlockInfo** AZ=AX[x];
                xx=x+chunk_offsetx*16;
                for (int z = 0; z < zl; z++) {
                    BlockInfo* AY=AZ[z];
                    zz=z+chunk_offsetz*16;
                    for (int y = height_add; y < 254; y++) {
                        if (skylight[x][z][y]==0) {
//                            if (y>floor_y[x][z] &&       xx%8==4                 &&  zz%10==5                 &&  (y-floor_y[x][z])%8==0) {

                            if (y>floor_y[x][z] &&
                                ( (abs(xx)%room_x)==int(room_x/2) && (abs(zz)%room_z)==int(room_z/2)  && ((y-floor_y[x][z])%room_y)==0 ) ||
                                ( (abs(xx)%room_x)==0             && (abs(zz)%room_z)==int(room_z/2)  && ((y-floor_y[x][z])%room_y)==int(room_y/2) ) ||
                                ( (abs(xx)%room_x)==int(room_x/2) && (abs(zz)%room_z)==0              && ((y-floor_y[x][z])%room_y)==int(room_y/2) )
                                ) {
                                if (skylight[x][z][y+1]==0) {
                                    if (x>0 && x<511 && z>0 && z<511) {
                                        if (skylight[x-1][z][y]==0 && skylight[x+1][z][y]==0 && skylight[x][z-1][y]==0 && skylight[x][z+1][y]==0) {
                                            room_lights++;
                                            AY[y]=BlockInfo(89,0,0,0);
                                            continue;
                                        }
                                    }
                                }
                            }
//                            if (((zz%10==0 && (xx%8==4||xx%8==3)) || (xx%8==0 && (zz%10==5||zz%10==4))) && (y%8==1 || y%8==2)) {
//willem
                            if (    y>floor_y[x][z] &&
                                    (
                                        ((abs(zz)%room_z)==0 && ((abs(xx)%room_x)==int(room_x/2)||(abs(xx)%room_x)==int(room_x/2)+1)) ||
                                        ((abs(xx)%room_x)==0 && ((abs(zz)%room_z)==int(room_z/2)||(abs(zz)%room_z)==int(room_z/2)+1))
                                     ) && (
                                        ((y-floor_y[x][z]))%room_y==1 ||
                                        ((y-floor_y[x][z]))%room_y==2 ||
                                        ((y-floor_y[x][z]))%room_y==3
                                    )
                                ) {
                                continue;
                            } else {
                                if (y<=floor_y[x][z] && y<253) {
                                    if (AY[y].id==0) {
                                        if (!(rand()%(2+((y-height_add)*(y-height_add))/5)))
                                            AY[y]=BlockInfo(89,0,0,0);
                                        else if (!(rand()%(2+((y-height_add)*(y-height_add))/25)))
                                            AY[y]=BlockInfo(14,0,0,0);
                                        else
                                        {
                                            if (y<=floor_y[x][z]-15+rand()%4) {
//hopla de popla
//                                                AY[y]=BlockInfo();
                                                AY[y]=BlockInfo(1,0,0,0);
                                            }
                                            else {
                                                if (!(rand()%5000)) AY[y]=BlockInfo(2,0,0,0);
                                                AY[y]=BlockInfo(3,0,0,0);
                                            }
                                        }
                                    }
                                    continue;
                                }
                            }
                            static int ran[1000];
                            static bool first=true;
                            if (first) {
                                for (int n=0; n<1000; n++) ran[n]=rand()%16;
                                first=false;
                            }

                            if (AY[y].id==0 && ((abs(zz)%room_z)==0 || (abs(xx)%room_x)==0 || ((y-floor_y[x][z]))%room_y==0) && y>floor_y[x][z]) {
                                int hop=int((y-int(floor_y[x][z]))/room_y)+int(abs(zz)/room_z)+int(abs(xx)/room_x);
                                if ( !(int(float(hop*y)*7.423+101*(sin(float(y)*11.77)+1.0)+ran[(hop+y*5+int(33.31*(sin(float(y+int(abs(zz)/(room_z*2))+int(abs(xx)/(room_x*2)))/1.77)+1.0)))%1000])%2) && (zz%room_z)!=0 && (xx%room_x)!=0) {
                                    int c_r=ran[int(y*39.434+3.3214*float(hop))%1000];
                                    int c_r2;
                                    if ( !(int(y*39.434+4.7143*float(hop))%2) ) c_r2=ran[int(float(y*y)*7.334+2.4234*float(hop))%1000];
                                    else c_r2=c_r;
                                    if (abs(xx+zz)%2)
                                        AY[y]=BlockInfo(251,0,c_r,0);
                                    else
                                        AY[y]=BlockInfo(251,0,c_r2,0);
                                } else {
                                        AY[y]=BlockInfo(5,0,0,0);
                                }
                                num_blocks_total++;
                                filled++;
                                if ((y-floor_y[x][z])%room_y==0 && !(abs(xx)%room_x==0 || abs(zz)%room_z==0) && y<254) {
                                    if (AY[y+1].id==0 && !(rand()%1000)) {
                                        AY[y+1]=BlockInfo(255,0,0,0);

                                        if (AY[y+2].id==0 && !(rand()%2)) {
                                            AY[y+2]=BlockInfo(255,0,0,0);
                                        }
                                    }
                                }
                            }
                        } else {
                            if (AY[y].id!=0) num_blocks_total++;
                        }
                    }
                }
            }
//            if (caves_on)
            int counter1=0;
//            int counter2=0;

/*
            static int r1_prev=-999;
            static int r2_prev=-999;
            static int r3_prev=-999;
            static int r1_prev_x=-999;
            static int r2_prev_x=-999;
            static int r3_prev_x=-999;
            static int r1_prev_z=-999;
            static int r2_prev_z=-999;
            static int r3_prev_z=-999;
            static int x_prev=-999;
            static int y_prev=-999;
            static int z_prev=-999;

            static int starting_x=true;
            static int starting_z=true;
*/
            for (int x = 0; x < xl; x++) {
                BlockInfo** AZ=AX[x];
                xx=x+chunk_offsetx*16;
                for (int z = 0; z < zl; z++) {
                    zz=z+chunk_offsetz*16;
                    BlockInfo* AY=AZ[z];
                    AY[0] = BlockInfo(7, 0, 0 );
                    for (int y = height_add; y < 256; y++) {
                        if (y+height_add<1) continue;

                        if (AY[y].id!=0 && AY[y].id!=1 && AY[y].id!=8 && AY[y].id!=255 && (AY[y].id!=46 || !(rand()%2)) ) {
//                        if (AY[y].id!=0 && AY[y].id!=8 && AY[y].id!=999 && AY[y].id!=46 ) {
                            num_blocks_total++;
                            float s1=211.0+211.0*sin(2.0*M_PI*float(xx)/312.0);
                            float s2=211.0+211.0*cos(2.0*M_PI*float(zz)/312.0);
                            float s3=75.0+60.0*cos(2.0*M_PI*float(y)/120.0);
                            float f_xx=y/3+sin((float)zz/344.54)*512.0+sin((float)xx/284.0)*512.0;
                            float f_y =zz/5+sin((float)xx/324.65)*312.0+sin((float)y/364.0)*256.0;
                            float f_zz=xx/6+sin((float)zz/234.44)*512.0+sin((float)y/214.66)*512.0;
                            float rr=2.0+4.0*(1.0+sin((f_xx*2.0-f_zz+f_y)/358.77))/2.0 + 12.0*(1.0+sin((f_xx+f_zz*2.0-f_y)/314.0))/2.0;
                            float rr2=30.0*(1.0+sin((f_xx*-f_zz+f_y)/258.77))/2.0 + 60.0*(1.0+sin((f_xx+f_zz+f_y*2)/(410.0-rr*3)))/2.0;
                            float rr3=30.0*(1.0+sin((f_xx-f_zz-f_y*2)/458.77))/2.0 + 60.0*(1.0+sin((f_xx+f_zz+f_y-rr2)/442.0))/2.0;
                            int b1=int( ( sin( float(f_xx)/(399.83-rr2)                 + 0.12*sin( float(f_y+f_xx)/(475.83-rr2) ) )                + sin( float(f_y+f_xx)/(239.83+rr2) )               +  float(f_xx/30.0+f_y/10+ 5.17*sin( float(f_zz+f_y/2)/299.83 ) )/(319.51-rr3)                              + 2.0)*300.0 + 500.0 )%350;
                            int b2=int( ( sin( float(f_zz)/(339.83-rr3)                 + 0.11*sin( float(f_y+f_zz)/(415.83+rr2) ) )                + sin( float(f_y+f_zz)/(466.83+rr3) )               +  float(f_zz/5.0+f_xx/2.0+ 6.18*sin( float(f_xx-f_y/2)/339.83 ) )/(377.51+rr3)                               + 2.0)*300.0 + 500.0 )%350;
                            int b3=int( ( sin( float(f_xx)/(469.83-rr2/2.0+rr3/2.0)     + 0.14*sin( float(f_zz+f_y)/(355.83-rr3) ) )                + sin( float(f_zz-f_y)/(426.83+rr3/2.0+rr2/1.5) )   +  float(f_zz/5.0+ 5.16*sin( float(f_xx-f_zz)/489.83 ) )/(347.51-rr2)                                 + 2.0)*300.0 + 500.0 )%350;
                            int b4=int( ( sin( float(f_zz)/(369.83+rr2*5.0+rr3*7.0)     + 0.28*sin( float(f_xx-f_y)/(455.83+rr3*3.0-rr2*2.0) ) )    + sin( float(f_xx+f_y)/(226.83+rr3/2.0+rr2/1.5) )   +  float(f_y/15-f_zz/15 + 4.13*sin( float(f_xx-f_y*2.0)/(359.83+rr2*2.0+rr3*3.0) ) )/(347.51-rr2)   + 2.0)*300.0 + 700.0 )%300;
                            if (
                                 ( (b1==100 || b1==101) && ( b2== 90 || b3== 90 || b2== 91 || b3== 91) )  ||
                                 ( (b1==100 || b1==101) && ( b3== 75 || b2== 75 || b3== 76 || b2== 76) )  ||
                                 ( (b2==100 || b2==101) && ( b3==140 || b1==140 || b3==141 || b1==141) )  ||
                                 ( (b2==100 || b2==101) && ( b1==180 || b3== 80 || b1==181 || b3== 81) )  ||
                                 ( (b3==100 || b3==101) && ( b1== 140 || b1== 141)  )  ||
                                 ( (b3==100 || b3==101) && ( b2== 90  || b2== 91 )  )  ||
//                                 ( b3%140<3 && ( b2== 80 || b2== 81 || b4== 8 8 || b4== 89      ))  ||
//                                 ( b1%111<3 && ( b3==100 || b3==101  /*|| b2== 75 || b2== 76 */ )) ||
//                                 ( b4%150<3 && ( b2== 77 || b2== 78                 )) ||
                                 ( abs(y-(int)s3)<3 && abs(x-(int)s1)<3 && abs(z-(int)s2)<3   )
//                                 ( b4%256<3 && ( b1+b2 == 200 || b1+b2== 201        ))

//                            if (  (b1==25 || b1==26 || b1==27 || b1==75 || b1==76 || b1==77) && (b2==100 || b2==101 || b2==103 || b2==25 || b2==26 || b2==27 )
                                ) {
//                                if ((b1%25)==0 && (b2%25)==0) rr=rr2;
//                                else if ((b2%25)==0 && (b3%25)==0) rr=rr3;
                                BlockInfo hop=AY[y];
//                                if (!(rand()%25 && y<255)) {
//                                    if (AY[y+1].id==0 && skylight[x][z][y+1]>=8) AY[y+1]=BlockInfo(46,0,0,0);
//                                    num_blocks_total++;
//                                }
//willem
                                if (y>=floor_y[x][z]) {
                                    if (AX[x][z][y-1].id==0                                      && AX[x][z][y-1].id!=255 && skylight[x][z][y-1]==0) { num_blocks_total++;AX[x][z][y-1]=BlockInfo(46,0,0,0); if (AX[x][z][y-1-1].id==0) AX[x][z][y-1-1]=BlockInfo(hop.id,0,hop.data,0);}
                                    if ((rand()%20)<=(int)rr) if (x-1>=0  && AX[x-1][z][y].id==0 && AX[x-1][z][y].id!=255 && skylight[x-1][z][y]==0) { num_blocks_total++;AX[x-1][z][y]=BlockInfo(46,0,0,0); if (AX[x-1][z][y-1].id==0) AX[x-1][z][y-1]=BlockInfo(hop.id,0,hop.data,0);}
                                    if ((rand()%20)<=(int)rr) if (x+1<512 && AX[x+1][z][y].id==0 && AX[x+1][z][y].id!=255 && skylight[x+1][z][y]==0) { num_blocks_total++;AX[x+1][z][y]=BlockInfo(46,0,0,0); if (AX[x+1][z][y-1].id==0) AX[x+1][z][y-1]=BlockInfo(hop.id,0,hop.data,0);}
                                    if ((rand()%20)<=(int)rr) if (z-1>=0  && AX[x][z-1][y].id==0 && AX[x][z-1][y].id!=255 && skylight[x][z-1][y]==0) { num_blocks_total++;AX[x][z-1][y]=BlockInfo(46,0,0,0); if (AX[x][z-1][y-1].id==0) AX[x][z-1][y-1]=BlockInfo(hop.id,0,hop.data,0);}
                                    if ((rand()%20)<=(int)rr) if (z+1<512 && AX[x][z+1][y].id==0 && AX[x][z+1][y].id!=255 && skylight[x][z+1][y]==0) { num_blocks_total++;AX[x][z+1][y]=BlockInfo(46,0,0,0); if (AX[x][z+1][y-1].id==0) AX[x][z+1][y-1]=BlockInfo(hop.id,0,hop.data,0);}
                                    if ((rand()%20)<=(int)rr) if (y+1<256 && AX[x][z][y+1].id==0 && AX[x][z][y+1].id!=255 && skylight[x][z][y+1]==0) { num_blocks_total++;AX[x][z][y+1]=BlockInfo(46,0,0,0); if (AX[x][z][y+1-1].id==0) AX[x][z][y+1-1]=BlockInfo(hop.id,0,hop.data,0);}
//                                } else if (y<floor_y[x][z]-1 - (!caves_on)*25 && y>1) {
                                }
                                else if (caves_on && y<floor_y[x][z]-1 && y>1) {
                                    rr=rr+(200-y)/20.0;
                                    num_blocks_total++; AX[x][z][y]=BlockInfo(46,0,0,0);
                                    if ((rand()%25)<=(int)rr) if (x-1>=0  && AX[x-1][z][y].id!=255 && skylight[x-1][z][y]==0) { num_blocks_total++;AX[x-1][z][y]=BlockInfo(46,0,0,0); if (AX[x-1][z][y-1].id==0) AX[x-1][z][y-1]=BlockInfo(hop.id,0,hop.data,0);}
                                    if ((rand()%25)<=(int)rr) if (x+1<512 && AX[x+1][z][y].id!=255 && skylight[x+1][z][y]==0) { num_blocks_total++;AX[x+1][z][y]=BlockInfo(46,0,0,0); if (AX[x+1][z][y-1].id==0) AX[x+1][z][y-1]=BlockInfo(hop.id,0,hop.data,0);}
                                    if ((rand()%25)<=(int)rr) if (z-1>=0  && AX[x][z-1][y].id!=255 && skylight[x][z-1][y]==0) { num_blocks_total++;AX[x][z-1][y]=BlockInfo(46,0,0,0); if (AX[x][z-1][y-1].id==0) AX[x][z-1][y-1]=BlockInfo(hop.id,0,hop.data,0);}
                                    if ((rand()%25)<=(int)rr) if (z+1<512 && AX[x][z+1][y].id!=255 && skylight[x][z+1][y]==0) { num_blocks_total++;AX[x][z+1][y]=BlockInfo(46,0,0,0); if (AX[x][z+1][y-1].id==0) AX[x][z+1][y-1]=BlockInfo(hop.id,0,hop.data,0);}
                                    if ((rand()%25)<=(int)rr) if (y-1>=1  && AX[x][z][y-1].id!=255 && skylight[x][z][y-1]==0) { num_blocks_total++;AX[x][z][y-1]=BlockInfo(46,0,0,0); if (AX[x][z][y-1-1].id==0) AX[x][z][y-1-1]=BlockInfo(hop.id,0,hop.data,0);}
                                    if ((rand()%25)<=(int)rr) if (y+1<256 && AX[x][z][y+1].id!=255 && skylight[x][z][y+1]==0) { num_blocks_total++;AX[x][z][y+1]=BlockInfo(46,0,0,0); if (AX[x][z][y+1-1].id==0) AX[x][z][y+1-1]=BlockInfo(hop.id,0,hop.data,0);}
                                }
                            }
                        }
                    }
                }
            }
            printf("caves:\n");
            static bool first=true;
            static float d[31][31][31];
            if (first) {
                first=false;
                for (int xxx=-15; xxx<16; xxx++) {
                    for (int zzz=-15; zzz<16; zzz++) {
                        for (int yyy=-15; yyy<16; yyy++) {
                            d[xxx+15][zzz+15][yyy+15]=sqrt(float(xxx*xxx)+float(yyy*yyy)+float(zzz*zzz));
                        }
                    }
                }
            }

            for (int x = 0; x < xl; x++) {
                BlockInfo** AZ=AX[x];
                xx=x+chunk_offsetx*16;
                for (int z = 0; z < zl; z++) {
                    zz=z+chunk_offsetz*16;
                    BlockInfo* AY=AZ[z];
                    for (int y = height_add; y < 256; y++) {
                        if (y+height_add<1) continue;

                        if (AY[y].id!=254) {

                            float f_x_0=376.0*sin(float(xx + zz/2+ y   +200)/142.79);
                            float f_y_0=200.0*sin(float(y  +xx+zz)/130.54);
                            float f_z_0=336.0*sin(float(zz + y   +xx/2)/165.59);

                            float f_x_x=376.0*sin(float(xx+1 +zz/2 + y +200  )/142.79);
                            float f_y_x=200.0*sin(float(y  +xx+1+zz)/130.54);
                            float f_z_x=336.0*sin(float(zz + y   +(xx+1)/2)  /165.59);

                            float f_x_y=376.0*sin(float(xx + zz/2 + y+1  +200 )/142.79);
                            float f_y_y=200.0*sin(float(y+1  +xx+zz)/130.54);
                            float f_z_y=336.0*sin(float(zz + y+1   +xx/2)/165.59);

                            float f_x_z=376.0*sin(float(xx + (zz+1)/2 + y  +200 )  /142.79);
                            float f_y_z=200.0*sin(float(y  +xx+zz+1)/130.54);
                            float f_z_z=336.0*sin(float(zz+1 + y   +xx/2)/165.59);

                            float var1_0=(1.0+0.25*sin(float( xx+y+zz)/94.53 ));
                            float var2_0=(1.0+0.25*sin(float( xx+y-zz)/115.32));
                            float var3_0=(1.0+0.25*sin(float(-xx-y+zz)/83.21 ));

                            float var1_x=(1.0+0.25*sin(float( (xx+1)+y+zz)/94.53 ));
                            float var2_x=(1.0+0.25*sin(float( xx+1+y-zz)  /115.32));
                            float var3_x=(1.0+0.25*sin(float(-xx-1-y+zz)  /83.21 ));

                            float var1_y=(1.0+0.25*sin(float( xx+y+1+zz)/94.53 ));
                            float var2_y=(1.0+0.25*sin(float( xx+y+1-zz)/115.32));
                            float var3_y=(1.0+0.25*sin(float(-xx-y-1+zz)/83.21 ));

                            float var1_z=(1.0+0.25*sin(float( xx+y+zz+1)  /94.53 ));
                            float var2_z=(1.0+0.25*sin(float( xx+y-zz-1)  /115.32));
                            float var3_z=(1.0+0.25*sin(float(-xx-y+(zz+1))/83.21 ));

                            int r1,r2,r3;
                            int r1_x; int r2_x; int r3_x;
                            int r1_y; int r2_y; int r3_y;
                            int r1_z; int r2_z; int r3_z;
                            float f_x,f_y,f_z;
                            float var1,var2,var3;
                            for (int n=0; n<4; n++) {
                                if      (n==0)  { f_x=f_x_x; f_y=f_y_x; f_x=f_z_x; var1=var1_x; var2=var2_x; var3=var3_x;}
                                else if (n==1)  { f_x=f_x_y; f_y=f_y_y; f_x=f_z_y; var1=var1_y; var2=var2_y; var3=var3_y;}
                                else if (n==2)  { f_x=f_x_z; f_y=f_y_z; f_x=f_z_z; var1=var1_z; var2=var2_z; var3=var3_z;}
                                else            { f_x=f_x_0; f_y=f_y_0; f_x=f_z_0; var1=var1_0; var2=var2_0; var3=var3_0;}

                                r3= int(30.0 + 29.0*sin( (
                                         0.8*( var1*f_z/1.44  + var2*f_x/2.36 )           /  (93.3 * (1.0+var1*0.4*sin((var3*f_x/1.3 + f_y/2.4 + f_z    ) / 77.0)))   +
                                         var2*0.7*( var2*f_z/1.14  + var3*f_x/1.17 )           /  (89.4 * (1.0+var2*0.4*sin((f_x/1.7 + f_y     - var1*f_z    ) / 90.0)))   +
                                         var3*3.10*sin( (var3*f_z/1.36 + f_x/1.55 )   /  (112.6 * (1.0+0.4*sin((var2*f_x     + f_y     + f_z/2.1) / 51.0)))   ) +
                                         var1*4.15*sin( (f_z/1.67 + var3*f_x/1.64 )   /  (52.4 * (1.0+0.4*sin((f_x     - var1*f_y/2.7 + f_z/1.2) / 87.0)))   )
                                    )*0.8 ) );


                                r1= int( 200.0*sin( (
                                           0.7*( var2*f_x/2.23  +  f_z/2.3 )                       /   (97.3 * (1.0+var2*0.4*sin((-var3*f_x/1.2 + f_y     + f_z/1.5) / 133.0)))   +
                                           var2*0.6*( var3*f_x/1.44  +  f_z/1.5 )                            /   (113.3 * (1.0+var3*0.4*sin((-f_x-      var2*f_y/1.6 + f_z/1.3) / 124.0)))   +
                                           var3*1.8*sin( (var3*f_x/1.53 + f_z/1.1 )                /   (86.0 * (1.0+0.4*sin(( f_x + f_y     - var1*f_z/2.1    ) / 83.0)))   ) +
                                           var1*2.15*sin( (f_x/1.33 + var2*f_z/1.4 )                /   (98.0 * (1.0+0.4*sin(( f_x/1.8 - var3*f_y     + f_z/1.4) / 87.0)))   )
                                    )*0.60  ) );

                                r2= int( 200.0*sin( (
                                       0.7*( var3*f_z/2.02   +  f_x/2.30 )              / (126.3*(1.0+var3*0.3*sin(( f_x/1.2 + f_y/2.2 + var2*f_z      )  /117.0)))    +
                                       var3*0.6*( f_z/1.12   +  var1*f_x/1.22 )                  / (118.3*(1.0+var1*0.4*sin((-var3*f_x/1.3 - f_y     + f_z/1.7  )  /125.0)))    +
                                       var2*1.8*sin( (var2*f_z/1.0 + f_x/1.5 )          / (99.0*(1.0+0.4*sin(( f_x/1.32 - f_y     + var3*f_z      )  /85.0)))    ) +
                                       var1*2.15*sin( (f_z/1.5 + var3*f_x/1.7 )          / (83.0*(1.0+0.4*sin(( var1*f_x/1.5 + f_y/2.1 - f_z      )  /83.0)))    )
                                    )*0.60 ) );

                                if (n==0)       {r3_x=r3+height_add+1; r1_x=r1+255; r2_x=r2+255;}
                                else if (n==1)  {r3_y=r3+height_add+1; r1_y=r1+255; r2_y=r2+255;}
                                else if (n==2)  {r3_z=r3+height_add+1; r1_z=r1+255; r2_z=r2+255;}
                                else            {r3=  r3+height_add+1;   r1=r1+255;   r2=r2+255;}

                            }
                            int c1=0;
                            if ( !((r3>y && r3_x>y && r3_y>y && r3_z>y) || (r3<y && r3_x<y && r3_y<y && r3_z<y)) ) {
/*
                            if (    (r3>=y && (r3_x<=y || r3_y<=y || r3_z<=y) ) ||
                                    (r3<=y && (r3_x>=y || r3_y>=y || r3_z>=y) ) ||
                                    r3==y
                                    ) {
*/
/*

                                for (int n=0; n<4; n++) {
                                    if (n==0) { f_x=f_x_x; f_y=f_y_x; f_x=f_z_x; var1=var1_x; var2=var2_x; var3=var3_x;}
                                    else if (n==1) { f_x=f_x_y; f_y=f_y_y; f_x=f_z_y; var1=var1_y; var2=var2_y; var3=var3_y;}
                                    else if (n==2) { f_x=f_x_z; f_y=f_y_z; f_x=f_z_z; var1=var1_z; var2=var2_z; var3=var3_z;}
                                    else  { f_x=f_x_0; f_y=f_y_0; f_x=f_z_0; var1=var1_0; var2=var2_0; var3=var3_0;}
                                    r1= int( 140.0*sin( (
                                               ( var2*f_x/1.23  +  f_z/2.3 )                      /   (87.3 * (1.0+var2*0.4*sin((-var3*f_x/1.2 + f_y     + f_z/2.5) / 330.0)))   +
                                               ( var3*f_x/2.44  +  f_z/3.5 )                      /   (83.3 * (1.0+var3*0.4*sin((-f_x-      var2*f_y/2.6 + f_z/1.3) / 354.0)))   +
                                               var3*1.10*sin( (var1*f_x/1.53 + f_z/1.1 )               /   (86.0 * (1.0+0.4*sin(( f_x/2.7 + f_y     - var1*f_z    ) / 233.0)))   ) +
                                               var1*1.15*sin( (f_x/1.33 + var2*f_z/1.4 )               /   (81.0 * (1.0+0.4*sin(( f_x/2.8 - var3*f_y     + f_z/1.4) / 277.0)))   )
                                        )*0.55  ) );
                                    if (n==0)       {r1_x=r1+255; }
                                    else if (n==1)  {r1_y=r1+255; }
                                    else if (n==2)  {r1_z=r1+255; }
                                    else r1=r1+255;
                                }
                                for (int n=0; n<4; n++) {
                                    if (n==0) { f_x=f_x_x; f_y=f_y_x; f_x=f_z_x; var1=var1_x; var2=var2_x; var3=var3_x;}
                                    else if (n==1) { f_x=f_x_y; f_y=f_y_y; f_x=f_z_y; var1=var1_y; var2=var2_y; var3=var3_y;}
                                    else if (n==2) { f_x=f_x_z; f_y=f_y_z; f_x=f_z_z; var1=var1_z; var2=var2_z; var3=var3_z;}
                                    else  { f_x=f_x_0; f_y=f_y_0; f_x=f_z_0; var1=var1_0; var2=var2_0; var3=var3_0;}
                                    r2= int( 140.0*sin( (
                                           ( var3*f_z/2.02   +  f_x/1.30 )              / (86.3*(1.0+var3*0.3*sin(( f_x/1.2 + f_y/2.2 + var2*f_z      )  /387.0)))    +
                                           ( f_z/3.32   +  var1*f_x/2.42 )              / (88.3*(1.0+var1*0.4*sin((-var3*f_x/1.3 - f_y     + f_z/2.3  )  /365.0)))    +
                                           var2*1.10*sin( (var2*f_z/1.0 + f_x/1.5 )          / (89.0*(1.0+0.4*sin(( f_x/2.4 - f_y     + var3*f_z      )  /245.0)))    ) +
                                           var3*1.15*sin( (f_z/1.5 + var3*f_x/1.7 )          / (83.0*(1.0+0.4*sin(( var1*f_x/1.5 + f_y/2.1 - f_z      )  /243.0)))    )
                                        )*0.55 ) );
                                    if (n==0)       {r2_x=r2+255; }
                                    else if (n==1)  {r2_y=r2+255; }
                                    else if (n==2)  {r2_z=r2+255; }
                                    else r2=r2+255;
                                }
*/

                                if (
                                        ((r1>x && r1_x>x && r1_y>x && r1_z>x) || (r1<x && r1_x<x && r1_y<x && r1_z<x))
                                     &&
                                        ((r2>z && r2_x>z && r2_y>z && r2_z>z) || (r2<z && r2_x<z && r2_y<z && r2_z<z))
                                    ) {
                                    continue;
                                }
/*
                                if (! (
                                        (r1>=x && (r1_x<=x || r1_y<=x || r1_z<=x) ) ||
                                        (r1<=x && (r1_x>=x || r1_y>=x || r1_z>=x) ) ||
                                        (r2>=z && (r2_x<=z || r2_y<=z || r2_z<=z) ) ||
                                        (r2<=z && (r2_x>=z || r2_y>=z || r2_z>=z) ) ||
                                        r2==z || r1==x
                                       ) ) {
                                    continue;
                                }
*/

//                                    if (!(z==255+r2) && !(x==255+r1)) {
//                                        continue;
//                                    }

                                printf("\rx=%3d,z=%3d,y=%3d => %d\r",x,z,y,counter1);
                                counter1++;
                                AY[y]=BlockInfo(254,0,0,0);
                                for (int xxx=-15; xxx<16; xxx++) {
                                    for (int zzz=-15; zzz<16; zzz++) {
                                        for (int yyy=-15; yyy<16; yyy++) {
                                            if (xxx+x>=0 && xxx+x<512 && yyy+y>=0 && yyy+y<256 && zzz+z>=0 && zzz+z<512) {
                                                BlockInfo* hoppa=&AX[x+xxx][z+zzz][y+yyy];
                                                if (hoppa->id!=254) {
                                                    float dd=d[xxx+15][zzz+15][yyy+15];
                                                    if ( (xxx==0 && zzz==0 && abs(yyy)==2) || (xxx==0 && abs(zzz)==2 && yyy==0) || (abs(xxx)==2 && zzz==0 && yyy==0) || ( abs(xxx)+abs(yyy)+abs(zzz) <= 1  ) ) {
                                                        *hoppa=BlockInfo(46,0,0,0);
                                                    } else if (!(hoppa->id==46)) {
                                                        if (dd<4.0) {
                                                            *hoppa=BlockInfo(5, 0, 0, 0);
                                                        } else if (!(hoppa->id==5) && !(hoppa->id==8)) {
                                                            if (dd<17.0) {
                                                                int c=((int(abs(xxx+xx)+abs(yyy+y)+abs(zzz+zz))+rand()%20)/int(65.0+6.0*var1+5.0*var2+5.0*var3)+2500)%16;
                                                                *hoppa=BlockInfo(95,0,c,0);
                                                            } else if (!(hoppa->id==95)) {
                                                                if (dd<20.0) {
                                                                    if (rand()%20000 < int(  300.0+300.0*sin( (f_x+f_y+f_z)/100.0 ) ) ) *hoppa=BlockInfo(89,0,0,0);
                                                                }
                                                            }
                                                        }
                                                    }
                                                }

/*
                                                if (yyy==-3) {
                                                    int dept=3-(abs(xxx)+abs(zzz)/2);
                                                    if (y+yyy-4-dept>1+height_add) {
                                                        int c=((r1+r2+r3+rand()%10)/25+2500)%16;
                                                        hoppa=&AX[x+xxx][z+zzz][y+yyy-4-dept];
                                                        if (hoppa->id!=254 && hoppa->id!=46) *hoppa=BlockInfo(95,0,c,0);
                                                        if (y+yyy-5-dept>1+height_add) {
                                                            hoppa=&AX[x+xxx][z+zzz][y+yyy-5-dept];
                                                            if (hoppa->id!=254 && hoppa->id!=46) *hoppa=BlockInfo(95,0,c,0);
                                                            if (y+yyy-6-dept>1+height_add) {
                                                                hoppa=&AX[x+xxx][z+zzz][y+yyy-6-dept];
                                                                if (hoppa->id!=254 && hoppa->id!=95 && hoppa->id!=46) *hoppa=BlockInfo(89,0,0,0);
                                                            }
                                                        }
                                                    }
                                                }
*/
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }


            printf("\nroomlights=%d",room_lights);

            printf(" real=%d filled=%d",num_blocks_total,filled);
            num_blocks_total=0;

            editor.clearArrays(editor.x_len + 00, editor.z_len + 00, 256);
        }

        if (water_on) {
            for (int x = 0; x < xl; x++) {
                BlockInfo** AZ=AX[x];
                xx=x+chunk_offsetx*16;
                for (int z = 0; z < zl; z++) {
                    zz=z+chunk_offsetz*16;
                    BlockInfo* AY=AZ[z];

/*
                    float ran1=(1.0+sin(float(xx)/55.0+float(zz)/59.0) /(100.0));
                    float ran2=(1.0+sin(float(xx)/99.0+float(zz)/23.0) /(100.0*ran1));
                    float ran3=(1.0+sin(float(xx)/145.0+float(zz)/89.0)/(100.0*ran2));
                    float ran4=(1.0+sin(float(xx)/68.0+float(zz)/45.0) /(100.0*ran3));
                    float ran5=(1.0+sin(float(xx)/77.0+float(zz)/59.0) /(100.0*ran4));
                    float ran6=(1.0+sin(float(xx)/88.0+float(zz)/87.0) /(100.0*ran5));
                    float ran7=(1.0+sin(float(xx)/97.0+float(zz)/34.0) /(100.0*ran6));
                    float ran8=(1.0+sin(float(xx)/34.0+float(zz)/54.0) /(100.0*ran7));
*/

//                   float r1 = -0.143 * sin(1.65 * (ran2*float(xx)/50.0 + 1.73)) - 0.197 * sin(2.96 * (ran4*float(zz)/44.0+4.98)) - 0.012 * sin(7.23 * (ran6*float(xx)/55.0+3.17)) + 0.088 * sin(8.07 * (float(zz)/39.0+4.63));
//                   float r2 = -0.141 * sin(1.75 * (ran5*float(zz)/44.0 + 1.63)) - 0.166 * sin(3.96 * (ran8*float(xx)/38.0+5.38)) - 0.018 * sin(6.23 * (ran5*float(zz)/45.0+2.17)) + 0.078 * sin(8.07 * (float(xx)/59.0+3.63));
//                   float r3 = -0.123 * sin(1.55 * (ran6*float(zz+xx)/20.0 + 1.53)) - 0.185 * sin(2.46 * (ran1*float(xx)/25.0+4.28)) - 0.017 * sin(5.23 * (float(zz+xx/2)/35.0+3.17)) + 0.098 * sin(7.07 * (float(xx)/29.0+5.63));
//                   float r4 = -0.153 * sin(1.64 * (ran7*float(xx)/24.0 + 1.83)) - 0.194 * sin(2.76 * (ran7*float(zz-xx)/58.0+4.58)) - 0.016 * sin(4.23 * (float(xx)/25.0+3.17)) + 0.088 * sin(6.07 * (float(zz)/39.0+4.63));

                   float r1000x=(sin(float(xx)/345+float(zz)/399)+1.0)*100.0;
                   float r1000z=(cos(float(xx)/345+float(zz)/399)+1.0)*100.0;

                   float f1=1.0+(sin(float(xx)/245+float(zz)/399)+1.0)/15.0;
                   float f2=1.0+(cos(float(xx)/315+float(zz)/344)+1.0)/15.0;
                   float f3=1.0+(sin(float(xx)/444+float(zz)/659)+1.0)/15.0;
                   float f4=1.0+(cos(float(xx)/645+float(zz)/499)+1.0)/15.0;

                   float f5=1.0+(sin(float(xx)/345+float(zz)/499)+1.0)/15.0;
                   float f6=1.0+(cos(float(xx)/515+float(zz)/344)+1.0)/15.0;
                   float f7=1.0+(sin(float(xx)/564+float(zz)/559)+1.0)/15.0;
                   float f8=1.0+(cos(float(xx)/275+float(zz)/899)+1.0)/15.0;

                   float r1=( -0.143 * sin(1.65 * (float((xx)+r1000x)/150.0 + 1.73))                     - 0.180 * sin(2.96 * (float((zz)+r1000z)/44.0+4.98))                    - 0.012 * sin(7.23 * (float((xx)+r1000x)/55.0+3.17)) + 0.088 * sin(8.07 * (float((zz)+r1000z)/39.0+4.63)) );
                   float r2=( -0.141 * sin(1.75 * (float((zz)+r1000z)/123.0 + 1.63))                     - 0.160 * sin(3.96 * (float((xx)+r1000x)/48.0+5.38))                    - 0.018 * sin(6.23 * (float((zz)+r1000z)/85.0+2.17)) + 0.078 * sin(8.07 * (float((xx)+r1000x)/59.0+3.63)) );
                   float r3=( -0.123 * sin(1.55 * (float((zz)+r1000z+float(xx)+r1000x)/98.0 + 1.53))    - 0.180 * sin(2.46 * (float((xx)+r1000x)/25.0+4.28))                    - 0.017 * sin(5.23 * (float((zz)+r1000z)/65.0+3.17)) + 0.098 * sin(7.07 * (float((xx)+r1000x)/29.0+5.63)) );
                   float r4=( -0.153 * sin(1.64 * (float((xx)+r1000x)/78.0 + 1.83))                     - 0.190 * sin(2.76 * (float((zz)+r1000z-float(xx)+r1000x)/28.0+4.58))   - 0.016 * sin(4.23 * (float((xx)+r1000x)/75.0+3.17)) + 0.088 * sin(6.07 * (float((zz)+r1000z)/39.0+4.63)) );

                   r1+=f1*0.3*( -0.143 * sin(f5*1.65 * (float(xx)/50.0 + 1.73)) - f2*f3*0.183 * sin(2.96 * (float(zz)/44.0+f7*f3*4.98)) - 0.012 * sin(7.23 * (float(xx)/55.0+3.17)) + 0.088 * sin(f7*8.07 * (float(zz)/39.0+4.63)));
                   r2+=f2*0.3*( -0.141 * sin(f6*1.75 * (float(zz)/44.0 + 1.63)) - f3*f4*0.160 * sin(3.96 * (float(xx)/48.0+f5*f2*5.38)) - 0.018 * sin(6.23 * (float(zz)/45.0+2.17)) + 0.078 * sin(f8*8.67 * (float(xx)/59.0+3.63)));
                   r3+=f3*0.3*( -0.123 * sin(f7*1.55 * (float(zz)/20.0 + 1.53)) - f4*f1*0.180 * sin(2.46 * (float(xx)/25.0+f8*f4*4.28)) - 0.017 * sin(5.23 * (float(zz)/35.0+3.17)) + 0.098 * sin(f5*7.37 * (float(xx)/29.0+5.63)));
                   r4+=f4*0.3*( -0.153 * sin(f8*1.64 * (float(xx)/24.0 + 1.83)) - f1*f2*0.192 * sin(2.76 * (float(zz)/28.0+f6*f1*4.58)) - 0.016 * sin(4.23 * (float(xx)/25.0+3.17)) + 0.088 * sin(f6*6.07 * (float(zz)/39.0+4.63)));

                    float r7 = ((r1 + r2 + r3 + r4)+0.55)*40.0;
//                    float r1 = -0.143 * ran1 * sin(1.65 * (ran7*float(xx)/50.0 + 1.73*ran2)) -  ran9 * 0.180 * sin(2.96 * ran2 * (float(zz)/44.0+4.98)) - 0.012 * sin(7.23 * (float(xx)/55.0+3.17)) + 0.088 * sin(8.07 * (float(zz)/39.0+4.63));
//                    float r2 = -0.141 * ran2 * sin(1.75 * (ran8*float(zz)/44.0 + 1.63*ran3)) - ran10 * 0.160 * sin(3.96 * ran6 * (float(xx)/48.0+5.38)) - 0.018 * sin(6.23 * (float(zz)/45.0+2.17)) + 0.078 * sin(8.07 * (float(xx)/59.0+3.63));
//                    float r3 = -0.123 * ran3 * sin(1.55 * (ran5*float(zz+xx)/20.0 + 1.53*ran4)) - 0.180 * sin(2.46 * ran9 * (float(xx)/25.0+4.28)) - 0.017 * sin(5.23 * (float(zz*ran3*ran5)/35.0+3.17)) + 0.098 * sin(7.07 * ran7 * (float(xx)/29.0+5.63));
//                    float r4 = -0.153 * ran4 * sin(1.64 * (ran6*float(xx)/24.0 + 1.83*ran5)) - 0.190 * sin(2.76 * (float(zz-xx*ran10)/28.0+4.58*ran10)) - 0.016 * sin(4.23 * (float(xx)/25.0+3.17)) + 0.088 * sin(6.07 * (ran8 *float(zz)/39.0+4.63));

//                    float r7 = ((r1 + r2 + r3 + r4)+0.2)*60.0;

                    for (int y = height_add; y < 256; y++) {
                        if (AY[y].id==0) {
                            if (y-height_add == r7 && y>=30+height_add) {
                                AY[y]=BlockInfo(2,0,0,0);
                            } else  if (y-height_add < r7) {
                                if (!(rand()%100) && AY[y].id!=8) AY[y]=BlockInfo(89,0,0,0);
                                else AY[y]=BlockInfo(7,0,0,0);
                            } else {
                                if (y<30+height_add) {
/*
                                    if (!(rand()%250000)) {
                                        setExtra2(x,z,y,"minecraft:dolphin",SomeStuff);
                                    } else if (!(rand()%25000)) {
                                        setExtra2(x,z,y,"minecraft:tropical_fish",SomeStuff);
                                    } else if (!(rand()%250000)) {
                                        setExtra2(x,z,y,"minecraft:squid",SomeStuff);
                                    } else if (!(rand()%125000)) {
                                        setExtra2(x,z,y,"minecraft:salmon",SomeStuff);
                                    }
*/
                                    AY[y]=BlockInfo(8,0,0,0);
                                    water++;
                                }
                            }
                        }
                    }
                }
            }
        }

        for (int x = 0; x < xl; x++) {
            BlockInfo** AZ=AX[x];
            xx=x+chunk_offsetx*16;
            for (int z = 0; z < zl; z++) {
                zz=z+chunk_offsetz*16;
                BlockInfo* AY=AZ[z];
                AY[0] = BlockInfo(7, 0, 0 );

                for (int y = height_add; y < 256; y++) {

                    if (AY[y].id!=0) {
                        num_blocks_total++;
                        if (blue_to_water_on && y<253) {
                            if (AY[y].id==251 && AY[y].data==water_blue && AY[y+1].id==0 && AY[y+2].id==0) {
                                setExtra2(x,z,y+2,"water",SomeStuff);
//                                AY[y+1]=BlockInfo(9,0,8,0);
                                tears++;
                            }
                        }
                        if (grass_on) {
                            if (y<253) if (AY[y].id==251 && AY[y+1].id==0 && AY[y+2].id==0) {
                                AY[y+1]=BlockInfo(2,0,0,0);
                                num_blocks_added++;
                                num_blocks_added++;
                                if (!(rand()%5000)) AY[y+2]=BlockInfo(40,0,0,0);
                                else if (!(rand()%5000)) AY[y+2]=BlockInfo(39,0,0,0);
//                                else if (!(rand()%3000)) {
//                                    setExtra2(x,z,y+2,"minecraft:water",SomeStuff);
//                                    water++;
//                                }

                                else num_blocks_added--;
                            }
                        }
                        if (stone_on) {
                            if (AY[y].id==251) AY[y]=BlockInfo(4,0,0,0);
                        } else if (glass_on) {
                            if (AY[y].id==251) {
                                if (AY[y].data==0) AY[y]=BlockInfo(20,0,0,0);
                                else AY[y]=BlockInfo(95,0,AY[y].data,0);
                            }
                        }
                        if (!(rand()%2500)) {
                            if (AY[y].id==8) {
                                int c=rand()%16;
                                AY[y]=BlockInfo(89, 0, 0, 0);
                                for (int xxx=-1; xxx<2; xxx++) {
                                    for (int zzz=-1; zzz<2; zzz++) {
                                        for (int yyy=-1; yyy<2; yyy++) {
                                            if (!(xxx==0 && yyy==0 && zzz==0)) {
                                                if (in_region(x+xxx, z+zzz, y+yyy, 0, 0, 0, xl , zl , yl)) {
                                                    if (AX[x+xxx][z+zzz][y+yyy].id==0 || AX[x+xxx][z+zzz][y+yyy].id==8) {
                                                        if ( ! (AX[x+xxx][z+zzz][y+yyy].id==66 || AX[x+xxx][z+zzz][y+yyy].id==27 || AX[x+xxx][z+zzz][y+yyy-1].id==66 || AX[x+xxx][z+zzz][y+yyy-1].id==27) ) {
                                                             AX[x+xxx][z+zzz][y+yyy]=BlockInfo(95, 0, c, 0);
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        if (lights_on && !(rand()%250)) {
                            if (AY[y].id!=8) {
                                    AY[y]=BlockInfo(89,0,0,0);
                            }
                        }
                    }
                }
            }
        }

        if (maze_on) {
//            add_maze_to_region(region, region_x, region_z, 15,  7, 3);
//            add_maze_to_region(region, region_x, region_z, 22, -5, 2);

//            add_maze_to_region(region, region_x, region_z, 66, 7, 1);
//            add_maze_to_region(region, region_x, region_z, 73, -5, 0);

            add_maze_to_region(region, region_x, region_z, 125, 5, 3);
            add_maze_to_region(region, region_x, region_z, 131, -5, 2);

            add_maze_to_region(region, region_x, region_z, 220, 5, 1);
            add_maze_to_region(region, region_x, region_z, 226, -5, 0);
        }

        int coral=0;

        if (coral_on) {
            printf(" Coral:\b\b\b\b\b\b\b");
            for (int x = 1; x < 511; x++) {
                xx=x+chunk_offsetx*16;
                for (int z = 1; z < 511; z++) {
                    zz=z+chunk_offsetz*16;
                    toggle2();
                    for (int y = 1; y < 248; y++) {
                        if (AX[x][z][y].id==8) {
                            int t=(int)(80.0+40.0*( (float)(rand()%20)/80.0 + sin((float(xx)+sin(float(zz)/15)*5)/(15.0+sin(float(zz)/20.0)*5.0))+sin((float(zz)+sin(float(xx)/15)*5)/(15.0+sin((float)(y+100)/22.0)*5.0))+sin(((float)(y+100)+sin((float(zz)+float(xx))/25)*5)/(15.0+sin(float(xx)/23.0)*5.0)) )  );
                            if (t<0) t=0;
                            int t2=(int)(7.5+1.5*( (float)(rand()%((int)(1+(t)/30)))/80.0 + sin((float(xx)+sin(float(zz)/25)*5)/(15.0+sin(float(zz)/30.0)*5.0))+sin((float(zz)+sin(float(xx)/25)*5)/(15.0+sin((float)(y+100)/32.0)*5.0))+sin(((float)(y+100)+sin((float(zz)+float(xx))/45)*5)/(15.0+sin(float(xx)/33.0)*5.0)) )  );
                            if ( ((t<(15+t2*4) && (rand()%10)<(t2)) || ( rand()%(1+t )==0 && (rand()%25)<(t2) )) && t>(t2*3+t/20) ) {
                                int allwater=1;
                                for (int xxx=-1; xxx<2 && (allwater==1); xxx++) {
                                    for (int zzz=-1; zzz<2 && (allwater==1); zzz++) {
                                        for (int yyy=-1; yyy<2 && (allwater==1); yyy++) {
                                            if (!(xxx==0 && yyy==0 && zzz==0)) {
    //                                                        if (AX[x+xxx][z+zzz][y+yyy].id!=8 && !AX[x+xxx][z+zzz][y+yyy].id==0) allwater=0;
                                                if ( AX[x+xxx][z+zzz][(y+100)+yyy].id!=8 && AX[x+xxx][z+zzz][(y+100)+yyy].id!=1000 && !AX[x+xxx][z+zzz][(y+100)+yyy].id==0) allwater=0;
                                            }
                                        }
                                    }
                                }
                                if (allwater==0) {
                                    if (!(rand()%30)) {
                                        setExtra2(x,z,y,"glowstone",SomeStuff);   AX[x][z][y]=BlockInfo(1000,0,0,0);
    //                                                    setExtra(x,z,y,"minecraft:glowstone");   AX[x][z][y]=BlockInfo(1000,0,0,0);
                                    } else {
                                        float some1=(10+3.25*(  (float)(rand()%25)/80.0 + sin((float(xx)+sin(float(zz)/43)*4.3+sin((float)(y+100)/73)*2)/(15.0+sin(float(zz)/42.0+(float)(y+100)/99)*5.0))+sin((float(zz)+sin((float(xx)+(float)(y+100)/3)/43)*4)/(15.0+sin((float)(y+100)/42.0+(float)float(zz)/92.0)*5.0))+sin(((float)(y+100)+sin((float(zz)+float(xx))/47)*3)/(15.0+sin(float(xx)/41.0)*450+sin(float(zz)/71.0)*2.1)) ));
                                        float some2=(10+3.25*(  (float)(rand()%((int)(some1+5)))/80.0 + sin((float(xx)+sin(float(zz)/120)*3.8)/(15.0+sin(float(zz)/112.0)*5.0))+sin((float(zz)+sin(float(xx)/143)*4)/(15.0+sin((float)(y+100)/82.0)*5.0))+sin(((float)(y+100)+sin((float(zz)+float(xx))/168)*3)/(15.0+sin(float(xx)/101.0)*5.0)) ));
                                        int flow;
                                        flow = (   sin((float(xx)+some2)/(83.23+some1*3) + sin((float(zz))/73.75)/3 )  +  sin((float(zz))/(39.75+some2) + sin(((float)(y+100))/34.87)/7.1  )  )*5+10;
                                        flow+= (sin((float(xx))/(94.23+some1*2) + sin((float(zz))/(57.75+flow))/2 )+sin(((float)(y+100))/(26.75+some2/2) + sin((float(xx)+flow/2)/45.87)/5.3 ))*1.25+2.5;
                                        flow+= (   sin(((float)(y+100)+some2)/(62.23+some1*2.1) + sin((float(zz))/(54.75+flow))/2.9 )  +  sin(((float)(y+100))/(64.75+some1*1.8) + sin((float(xx)+flow/2)/47.87)/6.2  )  )*15+30;
                                        float t=100+((86-flow)*some1+(flow)*some2)/80;

                                        int what=(int)t%64;
                                        if (what==0 || what==0+8 || what== 7+8*2 || what==3+8*3 || what==3+8*4 || what==4+8*5 || what==5+8*6 || what==0+8*7) { setExtra2(x,z,y,"tube_coral_block",SomeStuff);   AX[x][z][y]=BlockInfo(1000,0,0,0); coral++;}
                                        if (what==1 || what==1+8 || what== 6+8*2 || what==4+8*3 || what==7+8*4 || what==2+8*5 || what==4+8*6 || what==7+8*7) { setExtra2(x,z,y,"brain_coral_block",SomeStuff);  AX[x][z][y]=BlockInfo(1000,0,0,0); coral++; }
                                        if (what==2 || what==4+8 || what== 1+8*2 || what==2+8*3 || what==2+8*4 || what==6+8*5 || what==6+8*6 || what==2+8*7) { setExtra2(x,z,y,"bubble_coral_block",SomeStuff); AX[x][z][y]=BlockInfo(1000,0,0,0); coral++; }
                                        if (what==3 || what==3+8 || what== 2+8*2 || what==7+8*3 || what==4+8*4 || what==7+8*5 || what==7+8*6 || what==3+8*7) { setExtra2(x,z,y,"fire_coral_block",SomeStuff);   AX[x][z][y]=BlockInfo(1000,0,0,0); coral++; }
                                        if (what==4 || what==7+8 || what== 4+8*2 || what==5+8*3 || what==6+8*4 || what==1+8*5 || what==3+8*6 || what==1+8*7) { setExtra2(x,z,y,"horn_coral_block",SomeStuff);   AX[x][z][y]=BlockInfo(1000,0,0,0); coral++; }
                                        if (what==5 || what==5+8 || what== 5+8*2 || what==1+8*3 || what==5+8*4 || what==0+8*5 || what==2+8*6 || what==4+8*7) { AX[x][z][y]=BlockInfo(8,0,0,0); }
                                        if (what==6 || what==6+8 || what== 0+8*2 || what==0+8*3 || what==0+8*4 || what==3+8*5 || what==1+8*6 || what==6+8*7) { AX[x][z][y]=BlockInfo(8,0,0,0); }
                                        if (what==7 || what==2+8 || what== 3+8*2 || what==6+8*3 || what==1+8*4 || what==5+8*5 || what==0+8*6 || what==5+8*7) { AX[x][z][y]=BlockInfo(8,0,0,0); }

    /*
                                        if (what==0) { setExtra(x,z,y,"minecraft:tube_coral_block");   AX[x][z][y]=BlockInfo(1000,0,0,0); }
                                        if (what==1) { setExtra(x,z,y,"minecraft:brain_coral_block");  AX[x][z][y]=BlockInfo(1000,0,0,0); }
                                        if (what==2) { setExtra(x,z,y,"minecraft:bubble_coral_block"); AX[x][z][y]=BlockInfo(1000,0,0,0); }
                                        if (what==3) { setExtra(x,z,y,"minecraft:fire_coral_block");   AX[x][z][y]=BlockInfo(1000,0,0,0); }
                                        if (what==4) { setExtra(x,z,y,"minecraft:horn_coral_block");   AX[x][z][y]=BlockInfo(1000,0,0,0); }
    */
                                    }
                                }
                            }
                        }
                    }
                }
            }
            printf(" Coral:\b\b\b\b\b\b\b");
    //printf("\n");
            for (int x = 1; x < 511; x++) {
                xx=x+chunk_offsetx*16;
                for (int z = 1; z < 511; z++) {
                    zz=z+chunk_offsetz*16;
                    toggle2();
                    for (int y = 1; y < 248; y++) {
                        if (AX[x][z][y].id==8) {
                            int t=(int)(80.0+40.0*( (float)(rand()%20)/80.0 + sin((float(xx)+sin(float(zz)/15)*5)/(15.0+sin(float(zz)/20.0)*5.0))+sin((float(zz)+sin(float(xx)/15)*5)/(15.0+sin((float)(y+100)/22.0)*5.0))+sin(((float)(y+100)+sin((float(zz)+float(xx))/25)*5)/(15.0+sin(float(xx)/23.0)*5.0)) )  );
                            if (t<0) t=0;
                            int t2=(int)(7.5+1.5*( (float)(rand()%((int)(1+(t)/30)))/80.0 + sin((float(xx)+sin(float(zz)/25)*5)/(15.0+sin(float(zz)/30.0)*5.0))+sin((float(zz)+sin(float(xx)/25)*5)/(15.0+sin((float)(y+100)/32.0)*5.0))+sin(((float)(y+100)+sin((float(zz)+float(xx))/45)*5)/(15.0+sin(float(xx)/33.0)*5.0)) )  );
                            if ( ((t<(25+t2*3) && (rand()%10)<(t2)) || ( rand()%(1+t )==0 && (rand()%20)<(t2) ) ) && t>(-10+t2*3+t/20) ) {
                                int allwater=1;
                                for (int xxx=-1; xxx<2 && (allwater==1); xxx++) {
                                    for (int zzz=-1; zzz<2 && (allwater==1); zzz++) {
                                        for (int yyy=-1; yyy<2 && (allwater==1); yyy++) {
                                            if (!(xxx==0 && yyy==0 && zzz==0)) {
    //                                                        if (AX[x+xxx][z+zzz][y+yyy].id!=8 && !AX[x+xxx][z+zzz][y+yyy].id==0) allwater=0;
                                                if ( AX[x+xxx][z+zzz][y+yyy].id!=8 && AX[x+xxx][z+zzz][y+yyy].id!=1000 && !AX[x+xxx][z+zzz][y+yyy].id==0) allwater=0;
                                            }
                                        }
                                    }
                                }
                                if (allwater==0) {
                                    if (!(rand()%30)) {
    //                                                    setExtra(x,z,y,"minecraft:glowstone");   AX[x][z][y]=BlockInfo(1000,0,0,0);
                                        setExtra2(x,z,y,"glowstone",SomeStuff);   AX[x][z][y]=BlockInfo(1000,0,0,0);
                                    } else {
                                        float some1=(10+3.25*(  (float)(rand()%25)/80.0 + sin((float(xx)+sin(float(zz)/43)*4.3+sin((float)(y+100)/73)*2)/(15.0+sin(float(zz)/42.0+(float)(y+100)/99)*5.0))+sin((float(zz)+sin((float(xx)+(float)(y+100)/3)/43)*4)/(15.0+sin((float)(y+100)/42.0+(float)float(zz)/92.0)*5.0))+sin(((float)(y+100)+sin((float(zz)+float(xx))/47)*3)/(15.0+sin(float(xx)/41.0)*450+sin(float(zz)/71.0)*2.1)) ));
                                        float some2=(10+3.25*(  (float)(rand()%((int)(some1+5)))/80.0 + sin((float(xx)+sin(float(zz)/120)*3.8)/(15.0+sin(float(zz)/112.0)*5.0))+sin((float(zz)+sin(float(xx)/143)*4)/(15.0+sin((float)(y+100)/82.0)*5.0))+sin(((float)(y+100)+sin((float(zz)+float(xx))/168)*3)/(15.0+sin(float(xx)/101.0)*5.0)) ));
                                        int flow;
                                        flow = (   sin((float(xx)+some2)/(83.23+some1*3) + sin((float(zz))/73.75)/3 )  +  sin((float(zz))/(39.75+some2) + sin(((float)(y+100))/34.87)/7.1  )  )*5+10;
                                        flow+= (sin((float(xx))/(94.23+some1*2) + sin((float(zz))/(57.75+flow))/2 )+sin(((float)(y+100))/(26.75+some2/2) + sin((float(xx)+flow/2)/45.87)/5.3 ))*1.25+2.5;
                                        flow+= (   sin(((float)(y+100)+some2)/(62.23+some1*2.1) + sin((float(zz))/(54.75+flow))/2.9 )  +  sin(((float)(y+100))/(64.75+some1*1.8) + sin((float(xx)+flow/2)/47.87)/6.2  )  )*15+30;
                                        float t=100+((86-flow)*some1+(flow)*some2)/80;

    //                                                    int t=(int)(10+3.25*(  (float)(rand()%25)/80.0 + sin((float(xx)+sin(float(zz)/43)*4)/(15.0+sin(float(zz)/42.0)*5.0))+sin((float(zz)+sin(float(xx)/43)*4)/(15.0+sin((float)(y+100)/42.0)*5.0))+sin(((float)(y+100)+sin((float(zz)+float(xx))/47)*3)/(15.0+sin(float(xx)/41.0)*5.0)) ));
                                        int what=(int)t%64;
                                        if (what==0 || what==0+8 || what== 7+8*2 || what==3+8*3 || what==3+8*4 || what==4+8*5 || what==5+8*6 || what==0+8*7){ setExtra2(x,z,y,"tube_coral_block",SomeStuff);   AX[x][z][y]=BlockInfo(1001,0,0,0);  coral++;}
                                        if (what==1 || what==1+8 || what== 6+8*2 || what==4+8*3 || what==7+8*4 || what==2+8*5 || what==4+8*6 || what==7+8*7){ setExtra2(x,z,y,"brain_coral_block",SomeStuff);  AX[x][z][y]=BlockInfo(1001,0,0,0);  coral++;}
                                        if (what==2 || what==4+8 || what== 1+8*2 || what==2+8*3 || what==2+8*4 || what==6+8*5 || what==6+8*6 || what==2+8*7){ setExtra2(x,z,y,"bubble_coral_block",SomeStuff); AX[x][z][y]=BlockInfo(1001,0,0,0);  coral++;}
                                        if (what==3 || what==3+8 || what== 2+8*2 || what==7+8*3 || what==4+8*4 || what==7+8*5 || what==7+8*6 || what==3+8*7){ setExtra2(x,z,y,"fire_coral_block",SomeStuff);   AX[x][z][y]=BlockInfo(1001,0,0,0);  coral++;}
                                        if (what==4 || what==7+8 || what== 4+8*2 || what==5+8*3 || what==6+8*4 || what==1+8*5 || what==3+8*6 || what==1+8*7){ setExtra2(x,z,y,"horn_coral_block",SomeStuff);   AX[x][z][y]=BlockInfo(1001,0,0,0);  coral++;}
                                        if (what==5 || what==5+8 || what== 5+8*2 || what==1+8*3 || what==5+8*4 || what==0+8*5 || what==2+8*6 || what==4+8*7){ AX[x][z][y]=BlockInfo(8,0,0,0); }
                                        if (what==6 || what==6+8 || what== 0+8*2 || what==0+8*3 || what==0+8*4 || what==3+8*5 || what==1+8*6 || what==6+8*7){ AX[x][z][y]=BlockInfo(8,0,0,0); }
                                        if (what==7 || what==2+8 || what== 3+8*2 || what==6+8*3 || what==1+8*4 || what==5+8*5 || what==0+8*6 || what==5+8*7){ AX[x][z][y]=BlockInfo(8,0,0,0); }
    /*
                                        if (what==0) { setExtra(x,z,y,"minecraft:tube_coral_block");   AX[x][z][y]=BlockInfo(1001,0,0,0); }
                                        if (what==1) { setExtra(x,z,y,"minecraft:brain_coral_block");  AX[x][z][y]=BlockInfo(1001,0,0,0); }
                                        if (what==2) { setExtra(x,z,y,"minecraft:bubble_coral_block"); AX[x][z][y]=BlockInfo(1001,0,0,0); }
                                        if (what==3) { setExtra(x,z,y,"minecraft:fire_coral_block");   AX[x][z][y]=BlockInfo(1001,0,0,0); }
                                        if (what==4) { setExtra(x,z,y,"minecraft:horn_coral_block");   AX[x][z][y]=BlockInfo(1001,0,0,0); }
    */
                                    }
                                }
                            }
                        }
                    }
                }
            }
            printf(" Coral:\b\b\b\b\b\b\b");
    //printf("\n");
            for (int x = 1; x < 511; x++) {
                xx=x+chunk_offsetx*16;
                for (int z = 1; z < 511; z++) {
                    zz=z+chunk_offsetz*16;
                    toggle2();
                    for (int y = 1; y < 248; y++) {
                        if (AX[x][z][y].id==8) {
                            int t=(int)(80.0+40.0*( (float)(rand()%20)/80.0 + sin((float(xx)+sin(float(zz)/15)*5)/(15.0+sin(float(zz)/20.0)*5.0))+sin((float(zz)+sin(float(xx)/15)*5)/(15.0+sin((float)(y+100)/22.0)*5.0))+sin(((float)(y+100)+sin((float(zz)+float(xx))/25)*5)/(15.0+sin(float(xx)/23.0)*5.0)) )  );
                            if (t<0) t=0;
                            int t2=(int)(7.5+1.5*( (float)(rand()%((int)(1+(t)/30)))/80.0 + sin((float(xx)+sin(float(zz)/25)*5)/(15.0+sin(float(zz)/30.0)*5.0))+sin((float(zz)+sin(float(xx)/25)*5)/(15.0+sin((float)(y+100)/32.0)*5.0))+sin(((float)(y+100)+sin((float(zz)+float(xx))/45)*5)/(15.0+sin(float(xx)/33.0)*5.0)) )  );
                            if (( (t<(40+t2*2) && (rand()%10)<(t2)) || ( rand()%(1+t )==0 && (rand()%15)<(t2) ) ) && t>(-15+t2*3+t/20)) {
                                int allwater=1;
                                for (int xxx=-1; xxx<2 && (allwater==1); xxx++) {
                                    for (int zzz=-1; zzz<2 && (allwater==1); zzz++) {
                                        for (int yyy=-1; yyy<2 && (allwater==1); yyy++) {
                                            if (!(xxx==0 && yyy==0 && zzz==0)) {
    //                                                        if (AX[x+xxx][z+zzz][y+yyy].id!=8 && !AX[x+xxx][z+zzz][y+yyy].id==0) allwater=0;
                                                if ( AX[x+xxx][z+zzz][y+yyy].id!=8 && AX[x+xxx][z+zzz][y+yyy].id!=1000 && !AX[x+xxx][z+zzz][y+yyy].id==0) allwater=0;
                                            }
                                        }
                                    }
                                }
                                if (allwater==0) {
                                    if (!(rand()%30)) {
                                        setExtra2(x,z,y,"glowstone",SomeStuff);   AX[x][z][y]=BlockInfo(1000,0,0,0);
    //                                                    setExtra(x,z,y,"minecraft:glowstone");   AX[x][z][y]=BlockInfo(1000,0,0,0);
                                    } else {
                                        float some1=(10+3.25*(  (float)(rand()%25)/80.0 + sin((float(xx)+sin(float(zz)/43)*4.3+sin((float)(y+100)/73)*2)/(15.0+sin(float(zz)/42.0+(float)(y+100)/99)*5.0))+sin((float(zz)+sin((float(xx)+(float)(y+100)/3)/43)*4)/(15.0+sin((float)(y+100)/42.0+(float)float(zz)/92.0)*5.0))+sin(((float)(y+100)+sin((float(zz)+float(xx))/47)*3)/(15.0+sin(float(xx)/41.0)*450+sin(float(zz)/71.0)*2.1)) ));
                                        float some2=(10+3.25*(  (float)(rand()%((int)(some1+5)))/80.0 + sin((float(xx)+sin(float(zz)/120)*3.8)/(15.0+sin(float(zz)/112.0)*5.0))+sin((float(zz)+sin(float(xx)/143)*4)/(15.0+sin((float)(y+100)/82.0)*5.0))+sin(((float)(y+100)+sin((float(zz)+float(xx))/168)*3)/(15.0+sin(float(xx)/101.0)*5.0)) ));
                                        int flow;
                                        flow = (   sin((float(xx)+some2)/(83.23+some1*3) + sin((float(zz))/73.75)/3 )  +  sin((float(zz))/(39.75+some2) + sin(((float)(y+100))/34.87)/7.1  )  )*5+10;
                                        flow+= (sin((float(xx))/(94.23+some1*2) + sin((float(zz))/(57.75+flow))/2 )+sin(((float)(y+100))/(26.75+some2/2) + sin((float(xx)+flow/2)/45.87)/5.3 ))*1.25+2.5;
                                        flow+= (   sin(((float)(y+100)+some2)/(62.23+some1*2.1) + sin((float(zz))/(54.75+flow))/2.9 )  +  sin(((float)(y+100))/(64.75+some1*1.8) + sin((float(xx)+flow/2)/47.87)/6.2  )  )*15+30;
                                        float t=100+((86-flow)*some1+(flow)*some2)/80;

    //                                                    int t=(int)(10+3.25*(  (float)(rand()%25)/80.0 + sin((xx+sin(float(zz)/43)*4)/(15.0+sin(float(zz)/42.0)*5.0))+sin((float(zz)+sin(float(xx)/43)*4)/(15.0+sin((float)y/42.0)*5.0))+sin(((float)y+sin((float(zz)+float(xx))/47)*3)/(15.0+sin(float(xx)/41.0)*5.0)) ));
                                        int what=(int)t%64;
                                        if (what==0 || what==0+8 || what== 7+8*2 || what==3+8*3 || what==3+8*4 || what==4+8*5 || what==5+8*6 || what==0+8*7) { setExtra2(x,z,y,"tube_coral_block",SomeStuff);   AX[x][z][y]=BlockInfo(1002,0,0,0);  coral++;}
                                        if (what==1 || what==1+8 || what== 6+8*2 || what==4+8*3 || what==7+8*4 || what==2+8*5 || what==4+8*6 || what==7+8*7) { setExtra2(x,z,y,"brain_coral_block",SomeStuff);  AX[x][z][y]=BlockInfo(1002,0,0,0);  coral++;}
                                        if (what==2 || what==4+8 || what== 1+8*2 || what==2+8*3 || what==2+8*4 || what==6+8*5 || what==6+8*6 || what==2+8*7) { setExtra2(x,z,y,"bubble_coral_block",SomeStuff); AX[x][z][y]=BlockInfo(1002,0,0,0);  coral++;}
                                        if (what==3 || what==3+8 || what== 2+8*2 || what==7+8*3 || what==4+8*4 || what==7+8*5 || what==7+8*6 || what==3+8*7) { setExtra2(x,z,y,"fire_coral_block",SomeStuff);   AX[x][z][y]=BlockInfo(1002,0,0,0);  coral++;}
                                        if (what==4 || what==7+8 || what== 4+8*2 || what==5+8*3 || what==6+8*4 || what==1+8*5 || what==3+8*6 || what==1+8*7) { setExtra2(x,z,y,"horn_coral_block",SomeStuff);   AX[x][z][y]=BlockInfo(1002,0,0,0);  coral++;}
                                        if (what==5 || what==5+8 || what== 5+8*2 || what==1+8*3 || what==5+8*4 || what==0+8*5 || what==2+8*6 || what==4+8*7) { AX[x][z][y]=BlockInfo(8,0,0,0); }
                                        if (what==6 || what==6+8 || what== 0+8*2 || what==0+8*3 || what==0+8*4 || what==3+8*5 || what==1+8*6 || what==6+8*7) { AX[x][z][y]=BlockInfo(8,0,0,0); }
                                        if (what==7 || what==2+8 || what== 3+8*2 || what==6+8*3 || what==1+8*4 || what==5+8*5 || what==0+8*6 || what==5+8*7) { AX[x][z][y]=BlockInfo(8,0,0,0); }
    /*
                                        if (what==0) { setExtra(x,z,y,"minecraft:tube_coral_block");   AX[x][z][y]=BlockInfo(1002,0,0,0); }
                                        if (what==1) { setExtra(x,z,y,"minecraft:brain_coral_block");  AX[x][z][y]=BlockInfo(1002,0,0,0); }
                                        if (what==2) { setExtra(x,z,y,"minecraft:bubble_coral_block"); AX[x][z][y]=BlockInfo(1002,0,0,0); }
                                        if (what==3) { setExtra(x,z,y,"minecraft:fire_coral_block");   AX[x][z][y]=BlockInfo(1002,0,0,0); }
                                        if (what==4) { setExtra(x,z,y,"minecraft:horn_coral_block");   AX[x][z][y]=BlockInfo(1002,0,0,0); }
    */
                                    }
                                }
                            }
                        }
                    }
                }
            }

            for (int x = 0; x < 512; x++) {
                BlockInfo** AZ=AX[x];
                for (int z = 0; z < 512; z++) {
                    BlockInfo* AY=AZ[z];
                    toggle2();
                    for (int y = 0; y < yl; y++) {
                        if (  AY[y].id>=1000 && AY[y].id<=1004) {
                            AY[y] = BlockInfo(8,0,0);
                        }
                    }
                }
            }

    //printf("\n");




            printf(" Kelp:\b\b\b\b\b\b");
            for (int x = 0; x < 512; x++) {
                xx=x+chunk_offsetx*16;
                for (int z = 0; z < 512; z++) {
                    zz=z+chunk_offsetz*16;
                    toggle2();
                    for (int y = 1; y < 248; y++) {
                        if (AX[x][z][y].id==8 && AX[x][z][y-1].id!=8 && AX[x][z][y].id!=1003 && AX[x][z][y-1].id!=1003) {
                            int t=(int)(10.0+4.0*( (float)(rand()%20)/80.0 + sin((float(xx)+sin(float(zz)/24)*10)/(16.0+sin(float(zz)/20.0)*5.0))+sin((float(zz)+sin(float(xx)/26)*8)/(16.0+sin((float)(y+100)/22.0)*5.0))+sin(((float)(y+100)+sin((float(zz)+float(xx))/44)*8)/(17.0+sin(float(xx)/23.0)*5.0)) )  );
                            if (t<0) t=0;
                            if (   rand()%(1+t ) == 0 ) {
                                char what[100];
                                sprintf(what,"kelp[age=%d]",rand()%25);
                                setExtra2(x,z,y,what,SomeStuff);
                                coral++;
    //                                            setExtra(x,z,y,what);
                                AX[x][z][y]=BlockInfo(1003,0,0,0);
                            }
                        }
                    }
                }
            }
    //printf("\n");
            printf(" Coral:\b\b\b\b\b\b\b");
            for (int x = 1; x < 511; x++) {
                xx=x+chunk_offsetx*16;
                for (int z = 1; z < 511; z++) {
                    zz=z+chunk_offsetz*16;
                    toggle2();
                    for (int y = 1; y < 248; y++) {
                        if (AX[x][z][y].id==8) {
                            int t=(int)(50.0+20.0*( (float)(rand()%20)/80.0 + sin((float(xx)+sin(float(zz)/17)*5)/(15.0+sin(float(zz)/22.0)*5.0))+sin((float(zz)+sin(float(xx)/17)*5)/(15.0+sin((float)(y+100)/22.0)*5.0))+sin(((float)(y+100)+sin((float(zz)+float(xx))/28)*5)/(15.0+sin(float(xx)/23.0)*5.0)) )  );
                            if (t<0) t=0;
                            if ( (t<50 && (rand()%10)<5) || rand()%(1+t ) == 0 ) {
                                int wall=0;
                                for (int xxx=-1; xxx<2 && (wall==0); xxx++) {
                                    for (int zzz=-1; zzz<2 && (wall==0); zzz++) {
                                        if (AX[x+xxx][z+zzz][y].id!=8 && AX[x+xxx][z+zzz][y].id!=1003 && AX[x+xxx][z+zzz][y].id!=1004 && !AX[x+xxx][z+zzz][y].id==0) wall=1;
                                    }
                                }
                                if (wall==1 && (rand()%2)==0) {
                                    float t=(10+3.25*(  (float)(rand()%25)/80.0 + sin((float(xx)+sin(float(zz)/43)*4)/(15.0+sin(float(zz)/42.0)*5.0))+sin((float(zz)+sin(float(xx)/43)*4)/(15.0+sin((float)(y+100)/42.0)*5.0))+sin(((float)(y+100)+sin((float(zz)+float(xx))/47)*3)/(15.0+sin(float(xx)/41.0)*5.0)) ));
                                    int what=(int)t%5;
                                    if (what==0) { setExtra2(x,z,y,"tube_coral_fan",SomeStuff);  AX[x][z][y]=BlockInfo(1004,0,0,0);  coral++;}
                                    if (what==1) { setExtra2(x,z,y,"brain_coral_fan",SomeStuff); AX[x][z][y]=BlockInfo(1004,0,0,0);  coral++;}
                                    if (what==2) { setExtra2(x,z,y,"bubble_coral_fan",SomeStuff);AX[x][z][y]=BlockInfo(1004,0,0,0);  coral++;}
                                    if (what==3) { setExtra2(x,z,y,"fire_coral_fan",SomeStuff);  AX[x][z][y]=BlockInfo(1004,0,0,0);  coral++;}
                                    if (what==4) { setExtra2(x,z,y,"horn_coral_fan",SomeStuff);  AX[x][z][y]=BlockInfo(1004,0,0,0);  coral++;}
    /*
                                    if (what==0) { setExtra(x,z,y,"minecraft:tube_coral_fan");  AX[x][z][y]=BlockInfo(1004,0,0,0); }
                                    if (what==1) { setExtra(x,z,y,"minecraft:brain_coral_fan"); AX[x][z][y]=BlockInfo(1004,0,0,0); }
                                    if (what==2) { setExtra(x,z,y,"minecraft:bubble_coral_fan");AX[x][z][y]=BlockInfo(1004,0,0,0); }
                                    if (what==3) { setExtra(x,z,y,"minecraft:fire_coral_fan");  AX[x][z][y]=BlockInfo(1004,0,0,0); }
                                    if (what==4) { setExtra(x,z,y,"minecraft:horn_coral_fan");  AX[x][z][y]=BlockInfo(1004,0,0,0); }
    */
                                } else if (AX[x][z][y-1].id!=8 && AX[x][z][y].id!=1003 && AX[x][z][y].id!=1004 && AX[x][z][y-1].id!=1003 && AX[x][z][y-1].id!=1004 ) {
                                    float t=(10+3.25*(  (float)(rand()%25)/80.0 + sin((float(xx)+sin(float(zz)/43)*4)/(15.0+sin(float(zz)/42.0)*5.0))+sin((float(zz)+sin(float(xx)/43)*4)/(15.0+sin((float)(y+100)/42.0)*5.0))+sin(((float)(y+100)+sin((float(zz)+float(xx))/47)*3)/(15.0+sin(float(xx)/41.0)*5.0)) ));
                                    int what=(int)t%5;
                                    if (what==0) { setExtra2(x,z,y,"tube_coral",SomeStuff);  AX[x][z][y]=BlockInfo(1004,0,0,0);  coral++;}
                                    if (what==1) { setExtra2(x,z,y,"brain_coral",SomeStuff); AX[x][z][y]=BlockInfo(1004,0,0,0);  coral++;}
                                    if (what==2) { setExtra2(x,z,y,"bubble_coral",SomeStuff);AX[x][z][y]=BlockInfo(1004,0,0,0);  coral++;}
                                    if (what==3) { setExtra2(x,z,y,"fire_coral",SomeStuff);  AX[x][z][y]=BlockInfo(1004,0,0,0);  coral++;}
                                    if (what==4) { setExtra2(x,z,y,"horn_coral",SomeStuff);  AX[x][z][y]=BlockInfo(1004,0,0,0);  coral++;}
    /*
                                    if (what==0) { setExtra(x,z,y,"minecraft:tube_coral");   AX[x][z][y]=BlockInfo(1004,0,0,0); }
                                    if (what==1) { setExtra(x,z,y,"minecraft:brain_coral");  AX[x][z][y]=BlockInfo(1004,0,0,0); }
                                    if (what==2) { setExtra(x,z,y,"minecraft:bubble_coral"); AX[x][z][y]=BlockInfo(1004,0,0,0); }
                                    if (what==3) { setExtra(x,z,y,"minecraft:fire_coral");   AX[x][z][y]=BlockInfo(1004,0,0,0); }
                                    if (what==4) { setExtra(x,z,y,"minecraft:horn_coral");   AX[x][z][y]=BlockInfo(1004,0,0,0); }
    */
                                }
                            }
                        }
                    }
                }
            }

            printf(" Coral:\b\b\b\b\b\b\b");
            for (int x = 1; x < 511; x++) {
                xx=x+chunk_offsetx*16;
                for (int z = 1; z < 511; z++) {
                    zz=z+chunk_offsetz*16;
                    toggle2();
                    for (int y = 1; y < 248; y++) {
                        if (AX[x][z][y].id==8) {
                            int t=(int)(80.0+40.0*( (float)(rand()%20)/80.0 + sin((float(xx)+sin(float(zz)/15)*5)/(15.0+sin(float(zz)/20.0)*5.0))+sin((float(zz)+sin(float(xx)/15)*5)/(15.0+sin((float)(y+100)/22.0)*5.0))+sin(((float)(y+100)+sin((float(zz)+float(xx))/25)*5)/(15.0+sin(float(xx)/23.0)*5.0)) )  );
                            if (t<0) t=0;
                            int t2=(int)(7.5+1.5*( (float)(rand()%((int)(1+(t)/30)))/80.0 + sin((float(xx)+sin(float(zz)/25)*5)/(15.0+sin(float(zz)/30.0)*5.0))+sin((float(zz)+sin(float(xx)/25)*5)/(15.0+sin((float)(y+100)/32.0)*5.0))+sin(((float)(y+100)+sin((float(zz)+float(xx))/45)*5)/(15.0+sin(float(xx)/33.0)*5.0)) )  );
                            if ( ((t<(15+t2*4) && (rand()%10)<(t2)) || ( rand()%(1+t )==0 && (rand()%25)<(t2) )) && t>(-15+t2*3+t/20) ) {
                                int wall=0;
                                for (int xxx=-1; xxx<2 && (wall==0); xxx++) {
                                    for (int zzz=-1; zzz<2 && (wall==0); zzz++) {
                                        if (AX[x+xxx][z+zzz][y].id!=8 && AX[x+xxx][z+zzz][y].id!=1003 && AX[x+xxx][z+zzz][y].id!=1004 && !AX[x+xxx][z+zzz][y].id==0) wall=1;
                                    }
                                }
                                if (wall==1 && (rand()%2)==0) {
                                    float some1=(10+3.25*(  (float)(rand()%25)/80.0 + sin((float(xx)+sin(float(zz)/43)*4.3+sin((float)(y+100)/73)*2)/(15.0+sin(float(zz)/42.0+(float)(y+100)/99)*5.0))+sin((float(zz)+sin((float(xx)+(float)(y+100)/3)/43)*4)/(15.0+sin((float)(y+100)/42.0+(float)float(zz)/92.0)*5.0))+sin(((float)(y+100)+sin((float(zz)+float(xx))/47)*3)/(15.0+sin(float(xx)/41.0)*450+sin(float(zz)/71.0)*2.1)) ));
                                    float some2=(10+3.25*(  (float)(rand()%((int)(some1+5)))/80.0 + sin((float(xx)+sin(float(zz)/120)*3.8)/(15.0+sin(float(zz)/112.0)*5.0))+sin((float(zz)+sin(float(xx)/143)*4)/(15.0+sin((float)(y+100)/82.0)*5.0))+sin(((float)(y+100)+sin((float(zz)+float(xx))/168)*3)/(15.0+sin(float(xx)/101.0)*5.0)) ));
                                    int flow;
                                    flow = (   sin((float(xx)+some2)/(83.23+some1*3) + sin((float(zz))/73.75)/3 )  +  sin((float(zz))/(39.75+some2) + sin(((float)(y+100))/34.87)/7.1  )  )*5+10;
                                    flow+= (sin((float(xx))/(94.23+some1*2) + sin((float(zz))/(57.75+flow))/2 )+sin(((float)(y+100))/(26.75+some2/2) + sin((float(xx)+flow/2)/45.87)/5.3 ))*1.25+2.5;
                                    flow+= (   sin(((float)(y+100)+some2)/(62.23+some1*2.1) + sin((float(zz))/(54.75+flow))/2.9 )  +  sin(((float)(y+100))/(64.75+some1*1.8) + sin((float(xx)+flow/2)/47.87)/6.2  )  )*15+30;
                                    float t=100+((86-flow)*some1+(flow)*some2)/80;
                                    int what=(int)t%30;
                                    what=rand()%64;
                                    if (what==0 || what==0+8 || what== 7+8*2 || what==3+8*3 || what==3+8*4 || what==4+8*5 || what==5+8*6 || what==0+8*7) { setExtra2(x,z,y,"tube_coral_fan",SomeStuff);  AX[x][z][y]=BlockInfo(1004,0,0,0); coral++;}
                                    if (what==1 || what==1+8 || what== 6+8*2 || what==4+8*3 || what==7+8*4 || what==2+8*5 || what==4+8*6 || what==7+8*7) { setExtra2(x,z,y,"brain_coral_fan",SomeStuff); AX[x][z][y]=BlockInfo(1004,0,0,0); coral++;}
                                    if (what==2 || what==4+8 || what== 1+8*2 || what==2+8*3 || what==2+8*4 || what==6+8*5 || what==6+8*6 || what==2+8*7) { setExtra2(x,z,y,"bubble_coral_fan",SomeStuff);AX[x][z][y]=BlockInfo(1004,0,0,0); coral++;}
                                    if (what==3 || what==3+8 || what== 2+8*2 || what==7+8*3 || what==4+8*4 || what==7+8*5 || what==7+8*6 || what==3+8*7) { setExtra2(x,z,y,"fire_coral_fan",SomeStuff);  AX[x][z][y]=BlockInfo(1004,0,0,0); coral++;}
                                    if (what==4 || what==7+8 || what== 4+8*2 || what==5+8*3 || what==6+8*4 || what==1+8*5 || what==3+8*6 || what==1+8*7) { setExtra2(x,z,y,"horn_coral_fan",SomeStuff);  AX[x][z][y]=BlockInfo(1004,0,0,0); coral++;}
    //                                                if (what==5 || what==5+8 || what== 5+8*2 || what==1+8*3 || what==5+8*4 || what==0+8*5 || what==2+8*6 || what==4+8*7)
    //                                                if (what==6 || what==6+8 || what== 0+8*2 || what==0+8*3 || what==0+8*4 || what==3+8*5 || what==1+8*6 || what==6+8*7)
    //                                                if (what==7 || what==2+8 || what== 3+8*2 || what==6+8*3 || what==1+8*4 || what==5+8*5 || what==0+8*6 || what==5+8*7)


    /*
                                    if (what==0) { setExtra(x,z,y,"minecraft:tube_coral_fan");  AX[x][z][y]=BlockInfo(1004,0,0,0); }
                                    if (what==1) { setExtra(x,z,y,"minecraft:brain_coral_fan"); AX[x][z][y]=BlockInfo(1004,0,0,0); }
                                    if (what==2) { setExtra(x,z,y,"minecraft:bubble_coral_fan");AX[x][z][y]=BlockInfo(1004,0,0,0); }
                                    if (what==3) { setExtra(x,z,y,"minecraft:fire_coral_fan");  AX[x][z][y]=BlockInfo(1004,0,0,0); }
                                    if (what==4) { setExtra(x,z,y,"minecraft:horn_coral_fan");  AX[x][z][y]=BlockInfo(1004,0,0,0); }
    */
                                } else if (AX[x][z][y-1].id!=8 && AX[x][z][y].id!=1003 && AX[x][z][y].id!=1004 && AX[x][z][y-1].id!=1003 && AX[x][z][y-1].id!=1004 ) {
                                    float some1=(10+3.25*(  (float)(rand()%25)/80.0 + sin((float(xx)+sin(float(zz)/43)*4.3+sin((float)(y+100)/73)*2)/(15.0+sin(float(zz)/42.0+(float)(y+100)/99)*5.0))+sin((float(zz)+sin((float(xx)+(float)(y+100)/3)/43)*4)/(15.0+sin((float)(y+100)/42.0+(float)float(zz)/92.0)*5.0))+sin(((float)(y+100)+sin((float(zz)+float(xx))/47)*3)/(15.0+sin(float(xx)/41.0)*450+sin(float(zz)/71.0)*2.1)) ));
                                    float some2=(10+3.25*(  (float)(rand()%((int)(some1+5)))/80.0 + sin((float(xx)+sin(float(zz)/120)*3.8)/(15.0+sin(float(zz)/112.0)*5.0))+sin((float(zz)+sin(float(xx)/143)*4)/(15.0+sin((float)(y+100)/82.0)*5.0))+sin(((float)(y+100)+sin((float(zz)+float(xx))/168)*3)/(15.0+sin(float(xx)/101.0)*5.0)) ));
                                    float flow;
                                    flow = (   sin((float(xx)+some2)/(83.23+some1*3) + sin((float(zz))/73.75)/3 )  +  sin((float(zz))/(39.75+some2) + sin(((float)(y+100))/34.87)/7.1  )  )*5+10;
                                    flow+= (sin((float(xx))/(94.23+some1*2) + sin((float(zz))/(57.75+flow))/2 )+sin(((float)(y+100))/(26.75+some2/2) + sin((float(xx)+flow/2)/45.87)/5.3 ))*1.25+2.5;
                                    flow+= (   sin(((float)(y+100)+some2)/(62.23+some1*2.1) + sin((float(zz))/(54.75+flow))/2.9 )  +  sin(((float)(y+100))/(64.75+some1*1.8) + sin((float(xx)+flow/2)/47.87)/6.2  )  )*15+30;
                                    float t=100+((86-flow)*some1+(flow)*some2)/80;
                                    int what=(int)t%30;
                                    if (what==5 || what==9  || what==15 || what==18 || what==26) what=rand()%30;
                                    if (what==0 || what==8  || what==16 || what==21 || what==25) { setExtra2(x,z,y,"tube_coral",SomeStuff);  AX[x][z][y]=BlockInfo(1004,0,0,0); }
                                    if (what==1 || what==11 || what==17 || what==22 || what==29) { setExtra2(x,z,y,"brain_coral",SomeStuff); AX[x][z][y]=BlockInfo(1004,0,0,0); }
                                    if (what==2 || what==10 || what==13 || what==19 || what==28) { setExtra2(x,z,y,"bubble_coral",SomeStuff);AX[x][z][y]=BlockInfo(1004,0,0,0); }
                                    if (what==3 || what==7  || what==14 || what==23 || what==24) { setExtra2(x,z,y,"fire_coral",SomeStuff);  AX[x][z][y]=BlockInfo(1004,0,0,0); }
                                    if (what==4 || what==6  || what==12 || what==20 || what==27) { setExtra2(x,z,y,"horn_coral",SomeStuff);  AX[x][z][y]=BlockInfo(1004,0,0,0); }
    /*
                                    if (what==0) { setExtra(x,z,y,"minecraft:tube_coral");   AX[x][z][y]=BlockInfo(1004,0,0,0); }
                                    if (what==1) { setExtra(x,z,y,"minecraft:brain_coral");  AX[x][z][y]=BlockInfo(1004,0,0,0); }
                                    if (what==2) { setExtra(x,z,y,"minecraft:bubble_coral"); AX[x][z][y]=BlockInfo(1004,0,0,0); }
                                    if (what==3) { setExtra(x,z,y,"minecraft:fire_coral");   AX[x][z][y]=BlockInfo(1004,0,0,0); }
                                    if (what==4) { setExtra(x,z,y,"minecraft:horn_coral");   AX[x][z][y]=BlockInfo(1004,0,0,0); }
    */
                                }
                            } else if (t<=(t2*3+t/20) && !(rand()%500)) {
                                Pos position(region.x_ori + x+chunk_offsetx*16, region.z_ori + z+chunk_offsetz*16, region.y_ori + y);
                                Pos position2(region.x_ori + x, region.z_ori + z, region.y_ori + y);
                                MobEntity* mob;
                                mob = new MobEntity(position, "minecraft:tropical_fish");
                                editor.mca_coder.insertEntity(position2, mob);
                                delete mob;
                            }
                        }
                    }
                }
            }
    //printf("\n");
            printf(" Planter:\b\b\b\b\b\b\b\b\b");

//            makeExtra2(region,SomeStuff);
    //                        makeExtra(region);
    //printf("\n");

            printf(" Fish:\b\b\b\b\b\b");
    //printf("\n");

            for (int x = 0; x < 512; x++) {
                xx=x+chunk_offsetx*16;
                BlockInfo** AZ=AX[x];
                for (int z = 0; z < 512; z++) {
                    zz=z+chunk_offsetz*16;
                    BlockInfo* AY=AZ[z];
                    toggle2();
                    for (int y = 0; y < yl; y++) {
                        if (  AY[y].id==8) {
                            if (rand()%50000==0) {
                                int fish=rand()%7;
                                if (!rand()%4) fish=rand()%4;
                                if (!rand()%6) fish=rand()%4;
                                Pos position(region.x_ori + x+chunk_offsetx*16, region.z_ori + z+chunk_offsetz*16, region.y_ori + y);
                                Pos position2(region.x_ori + x, region.z_ori + z, region.y_ori + y);
                                MobEntity* mob;
                                if (fish==0) mob = new MobEntity(position, "minecraft:turtle");
                                else if (fish==1) mob = new MobEntity(position, "minecraft:tropical_fish");
                                else if (fish==2) mob = new MobEntity(position, "minecraft:pufferfish");
                                else if (fish==3) mob = new MobEntity(position, "minecraft:dolphin");
                                else if (fish==4) mob = new MobEntity(position, "minecraft:squid");
                                else if (fish==5) mob = new MobEntity(position, "minecraft:salmon");
                                else if (fish==6) mob = new MobEntity(position, "minecraft:cod");
                                else if (fish==7) mob = new MobEntity(position, "minecraft:guardian");
                                else if (fish==8) mob = new MobEntity(position, "minecraft:elder_guardian");
                                editor.mca_coder.insertEntity(position2, mob);
                                if (fish==1) {
                                    for (int t=0; t<(rand()%20); t++) editor.mca_coder.insertEntity(position2, mob);
                                }
                                delete mob;
                            } else if (rand()%55000==0) {
                                MobEntity* mob;
                                Pos position(region.x_ori + x+chunk_offsetx*16, region.z_ori + z+chunk_offsetz*16, region.y_ori + y);
                                Pos position2(region.x_ori + x, region.z_ori + z, region.y_ori + y);
                                mob = new MobEntity(position, "minecraft:dolphin");
                                editor.mca_coder.insertEntity(position2, mob);
                                delete mob;
                            } else if (rand()%2500000==0) {
                                int fish=rand()%2;
                                Pos position(region.x_ori + x+chunk_offsetx*16, region.z_ori + z+chunk_offsetz*16, region.y_ori + y);
                                Pos position2(region.x_ori + x, region.z_ori + z, region.y_ori + y);
                                MobEntity* mob;
                                if (fish==0) mob = new MobEntity(position, "minecraft:guardian");
                                else if (fish==1) mob = new MobEntity(position, "minecraft:elder_guardian");
                                editor.mca_coder.insertEntity(position2, mob);
                                delete mob;
                            }
                        }
                    }
                }
            }

            for (int x = 0; x < 512; x++) {
                BlockInfo** AZ=AX[x];
                for (int z = 0; z < 512; z++) {
                    BlockInfo* AY=AZ[z];
                    toggle2();
                    for (int y = 0; y < yl; y++) {
                        if (  AY[y].id>=1000 && AY[y].id<=1004) {
                            AY[y] = BlockInfo(8,0,0);
                        }
                    }
                }
            }
        }
        int tnt_blocks=0;
        for (int x = 0; x < 512; x++) {
            xx=x+chunk_offsetx*16;
            BlockInfo** AZ=AX[x];
            for (int z = 0; z < 512; z++) {
                zz=z+chunk_offsetz*16;
                BlockInfo* AY=AZ[z];
                toggle2();
                for (int y = 1; y < 256; y++) {
                    if (AY[y].id==254) {
                        AY[y]=BlockInfo(5,0,0,0);
                    }
                    if (AY[y].id==46) {
                        int num_tnt=0;
                        for (int xxx=-1; xxx<2; xxx++) {
                            for (int zzz=-1; zzz<2; zzz++) {
                                for (int yyy=-1; yyy<2; yyy++) {
                                    if (xxx+x>=0 && xxx+x<512 && yyy+y>=0 && yyy+y<256 && zzz+z>=0 && zzz+z<512) {
                                        if (AX[x+xxx][z+zzz][y+yyy].id==46) num_tnt++;
                                    }
                                }
                            }
                        }
                        if (num_tnt>8) AY[y]=BlockInfo(5,0,0,0);
                    }


                    if (AY[y].id==255) {
                        MobEntity* mob;
                        Pos position(region.x_ori + xx, region.z_ori + zz, region.y_ori + y+1);
                        Pos position2(region.x_ori + x, region.z_ori + z, region.y_ori + y+1);
                        int n=rand()%12;
                        if (n==0) mob = new MobEntity(position, "minecraft:pig");
                        else if (n==1) mob = new MobEntity(position, "minecraft:sheep");
                        else if (n==2) mob = new MobEntity(position, "minecraft:chicken");
                        else if (n==3) mob = new MobEntity(position, "minecraft:cow");
                        else if (n==4) mob = new MobEntity(position, "minecraft:mule");
                        else if (n==5) mob = new MobEntity(position, "minecraft:cave_spider");
                        else if (n==6) mob = new MobEntity(position, "minecraft:spider");
                        else if (n==7) mob = new MobEntity(position, "minecraft:donkey");
                        else if (n==8) mob = new MobEntity(position, "minecraft:zombie");
                        else if (n==9) mob = new MobEntity(position, "minecraft:panda");
                        else if (n==10) mob = new MobEntity(position, "minecraft:slime");
                        else if (n==11) mob = new MobEntity(position, "minecraft:parrot");




                        editor.mca_coder.insertEntity(position2, mob);
                        delete mob;
//                        if (AY[y-1].id==0) AY[y-1]=BlockInfo(251,0,1,0);
                        AY[y]=BlockInfo();
                    } else if (AY[y].id==46) {
                        tnt_blocks++;
                    }
                }
            }
        }

        if (SomeStuff.size()>0) {
            print_chunk_list();
            printf(" Creating command blocks: %d",SomeStuff.size());
            makeExtra2(region,SomeStuff);
        }

//        if (turbo_on) {
//            for (int z=0; z<32; z++) {
//                for (int x=0; x<32; x++) {
//                    AX[x*16][z*16][2]=BlockInfo(,0,0,0);
//                    setBlock()
//                    setExtra2(1+x*16,1+z*16,2,"minecraft:redstone_block",SomeStuff);
//                }
//            }
//        }



        if (!plotting) printf("\n");
        printf("\r%8d added. %8d replaced. Total = %8d = %5.2f%%  tears = %d  water=%d  coral=%d  tnt=%d\n",
            num_blocks_added, num_blocks_replaced, num_blocks_total, 100.0*(float)num_blocks_total/(512*512*256),tears,water,coral,tnt_blocks);
    }
    printf("REGION=[%d][%d]  RR=[%3d-%3d] Y=[%3d-%3d] ZZ=[%3d-%3d] ",region_x,region_z,real_min_x,real_max_x,real_min_y,real_max_y,real_min_z,real_max_z);

    scan_x=region_x;
    scan_z=region_z;
    sprintf(mc_text1,"R.%d.%d.MCA",region_x,region_z);

//    if (!no_plotting) {


    num_blocks=0;
    scan_image.create(512,512,sf::Color(0,0,0,0));
    for (int x = 0; x < xl; x++) {
        BlockInfo** AZ=AX[x];
        for (int z = 0; z < zl; z++) {
            toggle2();
            BlockInfo* AY=AZ[z];
            int max_y=-1;
            for (int y = 0; y < 256; y++) {
                BlockInfo bi=AY[y];
                if (bi.id!=0) {
                    num_blocks++;
                    if (mcglobal==6) {
                        if (mcglobal3>0 && y<=mcglobal3) {
                            max_y=y;
                        }
                    } else if (mcglobal==7) {
                        if (mcglobal3>0 && y==mcglobal3) {
                            max_y=y;
                        }
                    } else {
                        max_y=y;
                    }
                }
                if (y<real_min_y) real_min_y=y;
            }
            if (max_y!=-1) {
                int r_m,g_m,b_m;
                ret_color_rev( AY[max_y].data, r_m, g_m, b_m );
                scan_image.setPixel(x,z,sf::Color(r_m,g_m,b_m,255));

                if (max_y>real_max_y) real_max_y=max_y;
                if (x>real_max_x) real_max_x=x;
                if (x<real_min_x) real_min_x=x;
                if (z>real_max_z) real_max_z=z;
                if (z<real_min_z) real_min_z=z;

            } else {
                scan_image.setPixel(x,z,sf::Color(0,0,0,0));
            }
        }

    }



    update_request=2;
    while (update_request) {
        sf::sleep(sf::seconds(0.005));
    }


    if (plot_cubes) {
        int blocks_shown=0;
        MUTEX_MCEDITOR.lock();
//        m_pointCloud3.resize(num_blocks);
//        m_pointCloud3.clear();

        for (int x = 0; x < 512; x++) {
            xx=x+chunk_offsetx*16;
            BlockInfo** AZ=AX[x];
            for (int z = 0; z < 512; z++) {
                zz=z+chunk_offsetz*16;
                BlockInfo* AY=AZ[z];
                toggle2();
                for (int y = 1; y < yl; y++) {
                    if (AY[y].id!=0) {
                        if (y>0 && y<255 && x>0 && x<511 & z>1 && z<511) {
                            if (  (
                                (AX[x-1][z-1][y-1].id!=0) &&
                                (AX[x+0][z-1][y-1].id!=0) &&
                                (AX[x+1][z-1][y-1].id!=0) &&
                                (AX[x-1][z+0][y-1].id!=0) &&
                                (AX[x+0][z+0][y-1].id!=0) &&
                                (AX[x+1][z+0][y-1].id!=0) &&
                                (AX[x-1][z+1][y-1].id!=0) &&
                                (AX[x+0][z+1][y-1].id!=0) &&
                                (AX[x+1][z+1][y-1].id!=0) &&

                                (AX[x-1][z-1][y+0].id!=0) &&
                                (AX[x+0][z-1][y+0].id!=0) &&
                                (AX[x+1][z-1][y+0].id!=0) &&
                                (AX[x-1][z+0][y+0].id!=0) &&
                                (AX[x+0][z+0][y+0].id!=0) &&
                                (AX[x+1][z+0][y+0].id!=0) &&
                                (AX[x-1][z+1][y+0].id!=0) &&
                                (AX[x+0][z+1][y+0].id!=0) &&
                                (AX[x+1][z+1][y+0].id!=0) &&

                                (AX[x-1][z-1][y+1].id!=0) &&
                                (AX[x+0][z-1][y+1].id!=0) &&
                                (AX[x+1][z-1][y+1].id!=0) &&
                                (AX[x-1][z+0][y+1].id!=0) &&
                                (AX[x+0][z+0][y+1].id!=0) &&
                                (AX[x+1][z+0][y+1].id!=0) &&
                                (AX[x-1][z+1][y+1].id!=0) &&
                                (AX[x+0][z+1][y+1].id!=0) &&
                                (AX[x+1][z+1][y+1].id!=0)

                             ) ) {
                                 continue;
                             }
                        }
                        int r,g,b;
                        if (AX[x][z][y].id==8) {
                            r=0;g=100;b=255;
                        }
                        else
                            ret_color_rev(AX[x][z][y].data,r,g,b);

                        m_pointCloud3.append(
                            sf::Vertex(
                                sf::Vector2f(
                                    (float)(xx),
                                    (float)(zz)
                                ),
                                sf::Color(r,g,b,y),
                                sf::Vector2f(
                                    (float) (((x+y+1000)%6)*256)*150.0,
                                    (float) (0)*150.0
                                )
                            )
                        );

//                m_pointCloud3[num].color = sf::Color(rand()%3+rand()%3+rand()%3,0,0,0);

//                        m_pointCloud3[blocks_shown].position.x=(float)x*256/scale_factor;
//                        m_pointCloud3[blocks_shown].position.y=(float)z*256/scale_factor;
//                        m_pointCloud3[blocks_shown].texCoords.x = (float) (((x+y+1000)%6)*256)*150.0;
//                        m_pointCloud3[blocks_shown].texCoords.y = (float) (0)*150.0;
//                        m_pointCloud3[blocks_shown].color = sf::Color(y,0,0,0);
                        blocks_shown++;
//                        if (blocks_shown>num_blocks) {printf("\nError block count\n"); y=yl; x=xl; z=zl;}
                    }
                }
            }
        }
//        m_pointCloud3.resize(blocks_shown);
        printf("\n%d blocks added to plot_cubes vertex\n",blocks_shown);
        MUTEX_MCEDITOR.unlock();
    }

    if (!plotting) printf(" ");
    first_MCEDIT=0;
    region_x_old=0;
    region_z_old=0;
//                file_name_MCA = MCAFileNameXZ(region_x, region_z);
    mkdir("/Saves");
    mkdir("/Saves/test");
    mkdir("/Saves/test/region");
    mkdir("/Saves/test/region/done0");
    sprintf(tmp, "/Saves/Test/region/done0/r.%d.%d.mca", region_x, region_z);

    if (file_exists(tmp) && !plotting) {
        char cmd[200];
        sprintf(cmd,"del %s",tmp);
        while (replace_string(cmd,"/","\\"));
        system(cmd);
    }
    file_name_MCA = tmp;
    if (!plotting) {
        editor.setRegion(region);
        if (hit_one!=NULL) hit_one->index12=0;

//        region_counter[region_x][region_z]=0;
        sprintf(mc_text2,"SAVED");

//        if (!no_plotting) {
            update_request=2;
            while (update_request) {
                sf::sleep(sf::seconds(0.005));
            }
//        }
        printf("Region ready, returning\n");
        sf::sleep(sf::seconds(0.1));
    }
    else printf("\n");

//                CopyFile(tmp,fname.c_str(),false);

//                char tmp[256];
//                sprintf(tmp, "/Saves/Test/region/done/r.%d.%d.mca", region_x, region_z);
//                CopyFile(file_name_MCA.c_str(),tmp,true);

//    if (MCEDITOR_stop==1 || file_exists("stop.txt")) {
//        printf("Stop requested, exiting\n");
//                    system("/saves/copy_test.bat");
//        send_message='x';
//        return 0;
//    }
//    region.eraseRegion();
    return 0;
}




void make_one_plot_WINMAIN(int x, int y, sf::Image* image, int type) {
    image->create(512+10,512+10,sf::Color(0,0,0,0));
    int add=0;
    int add2=250;
    if (type>1) { type-=2; add=20; add2=0; }

    for (int yy=-5; yy<512+5; yy++) {
        for (int xx=-5; xx<512+5; xx++) {
            if (type==0) { //vertical
                if (
                    ( (x+xx+3+5)%500)==add ||
                    ( ((y+yy+3+5)%500)==add2 && ( abs((x+xx+3+5)%500 - add) <= 150 ||  abs((x+xx+3+5)%500 - add) >= 350 )  )

                     ) { //every 500 blocks....
                    image->setPixel(xx+5,yy+5,sf::Color(255,255,255,255));
                    if (xx+5-1>=0 )      image->setPixel(xx+5-1,yy+5,sf::Color(255,255,255,255));
                    if (xx+5-2>=0 )      image->setPixel(xx+5-2,yy+5,sf::Color(255,255,255,255));
                    if (xx+5+1<512+10)   image->setPixel(xx+5+1,yy+5,sf::Color(255,255,255,255));
                    if (xx+5+2<512+10)   image->setPixel(xx+5+2,yy+5,sf::Color(255,255,255,255));

                    if (yy+5-1>=0 )      image->setPixel(xx+5,yy+5-1,sf::Color(255,255,255,255));
                    if (yy+5-2>=0 )      image->setPixel(xx+5,yy+5-2,sf::Color(255,255,255,255));
                    if (yy+5+1<512+10)   image->setPixel(xx+5,yy+5+1,sf::Color(255,255,255,255));
                    if (yy+5+2<512+10)   image->setPixel(xx+5,yy+5+2,sf::Color(255,255,255,255));
                }
            } else if (type==1) { //horizontal
                if (
                     ((y+yy+3+5)%500)==add ||
                    ( ((x+xx+3+5)%500)==add2 && ( abs((y+yy+3+5)%500 - add)  <= 150 ||  abs((y+yy+3+5)%500 - add)  >= 350 ) )

                    ) { //every 500 blocks....
                    image->setPixel(xx+5,yy+5,sf::Color(255,255,255,255));
                    if (yy+5-1>=0 )      image->setPixel(xx+5,yy+5-1,sf::Color(255,255,255,255));
                    if (yy+5-2>=0 )      image->setPixel(xx+5,yy+5-2,sf::Color(255,255,255,255));
                    if (yy+5+1<512+10)   image->setPixel(xx+5,yy+5+1,sf::Color(255,255,255,255));
                    if (yy+5+2<512+10)   image->setPixel(xx+5,yy+5+2,sf::Color(255,255,255,255));

                    if (xx+5-1>=0 )      image->setPixel(xx+5-1,yy+5,sf::Color(255,255,255,255));
                    if (xx+5-2>=0 )      image->setPixel(xx+5-2,yy+5,sf::Color(255,255,255,255));
                    if (xx+5+1<512+10)   image->setPixel(xx+5+1,yy+5,sf::Color(255,255,255,255));
                    if (xx+5+2<512+10)   image->setPixel(xx+5+2,yy+5,sf::Color(255,255,255,255));


                }
            }
        }
    }
}

//floor at:     bottom+2
//ceiling at:   bottom+13+ceil_heigher


void add_maze_to_region(MCRegion& region, int region_x, int region_z, int bottom, int extra_height, int type) {

    ceil_heigher=extra_height;

    int skipping=1;
    int red=ret_color(255,0,0);
    int white=ret_color(255,255,255);
    float darkblue=ret_color(0,0,128);

    make_one_plot_WINMAIN(region_x*512, region_z*512, &image_plot3, type);
    make_one_plot_WINMAIN(region_x*512, region_z*512, &image_plot_org, type);
    make_one_plot_WINMAIN(region_x*512, region_z*512, &image_plot, type);

    for (int x = 0; x < 512; x++) {
        for (int z = 0; z < 512; z++) {
            if ( !( (image_plot.getPixel(x+5,z+5).r==0) && (image_plot.getPixel(x+5,z+5).b==0) && (image_plot.getPixel(x+5,z+5).g==0)) ) {
                skipping=0;
                break;
            }
        }
        if (!skipping) break;
    }
    if (skipping==1) {
        printf("Empty...no data...skipping r.%d.%d",region_x,region_z);
        return;
    }
    for (int x = 0; x < 512+10; x++) {
        for (int z = 0; z < 512+10; z++) {
            float pixel;
            float c;
            sf::Color col;
            col=image_plot.getPixel(x,z);
            c=(col.r+col.b+col.g);
            pixel = (c/(3));
            if (col.a==0) pixel=0;
            if (pixel!=0 && x>0 && x<511+10 && z>0 && z<511+10) {
                for (int xxx=-1; xxx<=1; xxx++) {
                    for (int zzz=-1; zzz<=1; zzz++) {
                        if (xxx!=0 || zzz!=0) {
                            if ((image_plot3.getPixel(x+xxx,z+zzz).r)!=254) image_plot3.setPixel(x+xxx,z+zzz, col);
                        }
                    }
                }
            }
        }
    }
    for (int x = 0; x < 512+10; x++) {
        for (int z = 0; z < 512+10; z++) {
            float pixel;
            float c;
            sf::Color col;
            col=image_plot3.getPixel(x,z);
            c=(col.r+col.b+col.g);
            pixel = (c/(3));
            if (col.a==0) pixel=0;
            if (pixel!=0 && x>0 && x<511+10 && z>0 && z<511+10) {
                for (int xxx=-1; xxx<=1; xxx++) {
                    for (int zzz=-1; zzz<=1; zzz++) {
                        if (xxx!=0 || zzz!=0) {
                            if ((image_plot.getPixel(x+xxx,z+zzz).r)!=254) image_plot.setPixel(x+xxx,z+zzz, col);
                        }
                    }
                }
            }
        }
    }
    BlockInfo*** AX=region.A;

    printf(" Maze:\b\b\b\b\b\b");
//                    if (!fast_build)
    for (int x = 0; x < xl; x++) {
        xx=x+chunk_offsetx*16;
        BlockInfo** AZ=AX[x];
        for (int z = 0; z < zl; z++) {
            zz=z+chunk_offsetz*16;
            BlockInfo* AY=AZ[z];
            int r, g, b;
            float pixel;
            float pixel_org;

            float c;
            sf::Color col;
            sf::Color col_org;
            col=image_plot.getPixel(x+5,z+5);
            col_org=image_plot_org.getPixel(x+5,z+5);

            c=(col.r+col.b+col.g);
            pixel = (c/(3));
            if (col.a==0) pixel=0;

            c=(col_org.r+col_org.b+col_org.g);
            pixel_org = (c/(3));
            if (col_org.a==0) pixel_org=0;

            int x_off=1;
            int z_off=1;

            for (int y = 0; y < 256; y++) {
                int edge=0;
                int edge2=0;
                int edge3=0;
                int corner2=0;
                int red2=0;
                int dir_x=0;
                int curve=0;
                int c1;
                int c2;
                int c3;
                int c4;

                if (y>=bottom+4-2 && y<=bottom+11+2+ceil_heigher) {
                    sf::Color col_side1;
                    sf::Color col_side2;
                    sf::Color col_side3;
                    sf::Color col_side4;
                    col_side1=image_plot.getPixel(x-x_off+5,    z+5);
                    col_side2=image_plot.getPixel(x+5,          z-z_off+5);
                    col_side3=image_plot.getPixel(x+x_off+5,    z+5);
                    col_side4=image_plot.getPixel(x+5,          z+z_off+5);
                    red2=0;
                    if ( col.r==254 || (pixel==0 && (col_side1.r==254 || col_side2.r==254 || col_side3.r==254 || col_side4.r==254)) ) red2=1;
                    c1=(col_side1.r+col_side1.b+col_side1.g);
                    c2=(col_side2.r+col_side2.b+col_side2.g);
                    c3=(col_side3.r+col_side3.b+col_side3.g);
                    c4=(col_side4.r+col_side4.b+col_side4.g);
                    if (c1==0 || c2==0 || c3==0 || c4==0) edge=1;
                    dir_x=0;
                    curve=0;
                    if (c1!=0 && c3!=0) dir_x=1+8;
                    if (c2!=0 && c4!=0) dir_x=0+8;
                    if (c1!=0 && c2!=0 && c3==0 && c4==0) curve=8;
                    if (c3!=0 && c4!=0 && c1==0 && c2==0) curve=6;
                    if (c1!=0 && c4!=0 && c2==0 && c3==0) curve=7;
                    if (c2!=0 && c3!=0 && c1==0 && c4==0) curve=9;
                    if (edge==0) {
                        col_side1=image_plot.getPixel(x-x_off+5,    z-z_off+5);
                        col_side2=image_plot.getPixel(x+x_off+5,    z-z_off+5);
                        col_side3=image_plot.getPixel(x+x_off+5,    z+z_off+5);
                        col_side4=image_plot.getPixel(x-x_off+5,    z+z_off+5);
                        c1=(col_side1.r+col_side1.b+col_side1.g);
                        c2=(col_side2.r+col_side2.b+col_side2.g);
                        c3=(col_side3.r+col_side3.b+col_side3.g);
                        c4=(col_side4.r+col_side4.b+col_side4.g);
                        if (c1==0 || c2==0 || c3==0 || c4==0) edge=1;
                        if (c1==0 && c2!=0 && c3!=0 && c4!=0) curve=8;
                        if (c1!=0 && c2==0 && c3!=0 && c4!=0) curve=9;
                        if (c1!=0 && c2!=0 && c3==0 && c4!=0) curve=6;
                        if (c1!=0 && c2!=0 && c3!=0 && c4==0) curve=7;
                    }
                    if (curve!=0) corner2=1;
                }


                if ( y==bottom+4-2) {
                    sf::Color col_side1=image_plot3.getPixel(x-x_off+5,    z+5);
                    sf::Color col_side2=image_plot3.getPixel(x+5,          z-z_off+5);
                    sf::Color col_side3=image_plot3.getPixel(x+x_off+5,    z+5);
                    sf::Color col_side4=image_plot3.getPixel(x+5,          z+z_off+5);
                    c1=(col_side1.r+col_side1.b+col_side1.g);
                    c2=(col_side2.r+col_side2.b+col_side2.g);
                    c3=(col_side3.r+col_side3.b+col_side3.g);
                    c4=(col_side4.r+col_side4.b+col_side4.g);
                    if (c1==0 || c2==0 || c3==0 || c4==0) edge2=1;
                    dir_x=0;
                    curve=0;
                    corner2=0;
                    if (c1!=0 && c3!=0) dir_x=1+8;
                    if (c2!=0 && c4!=0) dir_x=0+8;
                    if (c1!=0 && c2!=0 && c3==0 && c4==0) curve=8;
                    if (c3!=0 && c4!=0 && c1==0 && c2==0) curve=6;
                    if (c1!=0 && c4!=0 && c2==0 && c3==0) curve=7;
                    if (c2!=0 && c3!=0 && c1==0 && c4==0) curve=9;


                    if (edge2==0) {
                        col_side1=image_plot3.getPixel(x-x_off+5,    z-z_off+5);
                        col_side2=image_plot3.getPixel(x+x_off+5,    z-z_off+5);
                        col_side3=image_plot3.getPixel(x+x_off+5,    z+z_off+5);
                        col_side4=image_plot3.getPixel(x-x_off+5,    z+z_off+5);
                        c1=(col_side1.r+col_side1.b+col_side1.g);
                        c2=(col_side2.r+col_side2.b+col_side2.g);
                        c3=(col_side3.r+col_side3.b+col_side3.g);
                        c4=(col_side4.r+col_side4.b+col_side4.g);
                        if (c1==0 || c2==0 || c3==0 || c4==0) {
                            edge2=1;
                        }
                        if (c1==0 && c2!=0 && c3!=0 && c4!=0) curve=8;
                        if (c1!=0 && c2==0 && c3!=0 && c4!=0) curve=9;
                        if (c1!=0 && c2!=0 && c3==0 && c4!=0) curve=6;
                        if (c1!=0 && c2!=0 && c3!=0 && c4==0) curve=7;
                    }
                    if (curve!=0) corner2=1;
                }


                if (y>=bottom+5-2 && y<bottom+11+2+ceil_heigher) {
                    toggle2();
                    if (pixel!=0) {
                        if (edge==1) {
                            if (red2==1) {
                                if (AY[y].id==0 || AY[y].id==8) AY[y] = BlockInfo(95, 0, red,0 );
                            }  else {
                                if (rand()%30==0) {
                                    AY[y] = BlockInfo(95, 0, ret_color(rand()%256,rand()%256,rand()%256),0 );
                                } else {
                                    if (AY[y].id==0 || AY[y].id==8) AY[y] = BlockInfo(95, 0, white,0 );
                                }
                            }
                        } else {
                            if ( y==bottom+5-2 && ((((int)xx+3)%5)==0 && (((int)zz+3)%5)==0) ) {
                                AY[y] = BlockInfo(147, 0, 0, 0 );
                            } else if ( y==bottom+5-2 && AY[y].id!=147 && AY[bottom+4-2].id!=152) {
                                darkblue=sin(float(xx)/40+float(zz)/500) + sin(float(xx)/70+float(zz)/90) + sin(float(xx)/110+float(zz)/100) + sin(float(xx)/100+float(zz)/110) + sin(float(xx)/110+float(zz)/90) + sin(float(xx)/90+float(zz)/110);
                                darkblue+=sin(float(xx)/90+float(zz)/200) + sin(float(xx)/150+float(zz)/190) + sin(float(xx)/150+float(zz)/120) + sin(float(xx)/200+float(zz)/210) + sin(float(xx)/210+float(zz)/190) + sin(float(xx)/190+float(zz)/210);
                                darkblue+=(sin(float(xx)/29+float(zz)/20) + sin(float(xx)/20+float(zz)/19) + sin(float(xx)/21+float(zz)/20) + sin(float(xx)/20+float(zz)/21) + sin(float(xx)/21+float(zz)/19) + sin(float(xx)/19+float(zz)/21))/3;
                                darkblue=((darkblue+14)/28)*15.9;
                                AY[y] = BlockInfo(171, 0, (int)darkblue, 0 );
                            } else if (AY[y].id!=147 && AY[y].id!=66 && AY[y].id!=27) {
                                AY[y] = BlockInfo();
                            }
                        }
                    }
                }
                else if (y==bottom+11+2+ceil_heigher) {
                    toggle2();
                    if (pixel!=0) {
                        if (((((int)xx+3)%5)==0 && (((int)zz+3)%5)==0)) {
                            AY[y] = BlockInfo(89, 0, 0, 0 );
                        } else if (edge==1) {
                            if (corner2==1) {
                                AY[y] = BlockInfo(251, 0, red, 0 );
                                AY[y+1] = BlockInfo(66,0,curve,0);
                            } else {
                                if ( ((((int)xx+3)%15)==0 || (((int)zz+3)%15)==0) || ( col.r==254 && ( ((((int)xx+3)%5)==0 || (((int)zz+3)%5)==0) ) ) ) {
                                    AY[y] = BlockInfo(152, 0, 0, 0 );
                                    AY[y+1] = BlockInfo(27,0,dir_x,0);
                                } else {
                                    AY[y] = BlockInfo(251, 0, red, 0 );
                                    AY[y+1] = BlockInfo(27,0,dir_x,0);
                                }
                            }
                            rails++;
                            if (y<253) if (AY[y+3].id!=0) {
                                if (!((xx+zz)%10)) AY[y+3]=BlockInfo(89,0,0,0);
                            }
                            AY[y+2]=BlockInfo();
//hoppa
                            if (x>0            && AX[x-1][z][y+1].id!=27   && AX[x-1][z][y+1].id!=66  ) { AX[x-1][z][y+1]=BlockInfo(); AX[x-1][z][y+2]=BlockInfo(); }
                            if (z>0            && AX[x][z-1][y+1].id!=27   && AX[x][z-1][y+1].id!=66  ) { AX[x][z-1][y+1]=BlockInfo(); AX[x][z-1][y+2]=BlockInfo(); }
                            if (x<511          && AX[x+1][z][y+1].id!=27   && AX[x+1][z][y+1].id!=66  ) { AX[x+1][z][y+1]=BlockInfo(); AX[x+1][z][y+2]=BlockInfo(); }
                            if (z<511          && AX[x][z+1][y+1].id!=27   && AX[x][z+1][y+1].id!=66  ) { AX[x][z+1][y+1]=BlockInfo(); AX[x][z+1][y+2]=BlockInfo(); }
                            if (x>0 && z>0     && AX[x-1][z-1][y+1].id!=27 && AX[x-1][z-1][y+1].id!=66) { AX[x-1][z-1][y+1]=BlockInfo(); AX[x-1][z-1][y+2]=BlockInfo(); }
                            if (z>0 && x<511   && AX[x+1][z-1][y+1].id!=27 && AX[x+1][z-1][y+1].id!=66) { AX[x+1][z-1][y+1]=BlockInfo(); AX[x+1][z-1][y+2]=BlockInfo(); }
                            if (x<511 && z<511 && AX[x+1][z+1][y+1].id!=27 && AX[x+1][z+1][y+1].id!=66) { AX[x+1][z+1][y+1]=BlockInfo(); AX[x+1][z+1][y+2]=BlockInfo(); }
                            if (z<511 && x>0   && AX[x-1][z+1][y+1].id!=27 && AX[x-1][z+1][y+1].id!=66) { AX[x-1][z+1][y+1]=BlockInfo(); AX[x-1][z+1][y+2]=BlockInfo(); }
                            hoppa(AX,x,z,y);
//                                            AY[y+3]=BlockInfo();
                        } else if (rand()%30==0) {
                            AY[y] = BlockInfo(95, 0, ret_color(rand()%256,rand()%256,rand()%256),0 );
                        } else {
                            if (red2==1) {
                                if (AY[y].id==0 || AY[y].id==8) AY[y] = BlockInfo(95, 0, red,0 );
                            } else {
                                if (AY[y].id==0 || AY[y].id==8) AY[y] = BlockInfo(95, 0, white,0 );
                            }
                        }
                    }
                }
                else if (y==bottom+4-2) {
                    if (pixel!=0) {
                        if (edge==0 &&
                            (   (((int)xx+2)%5)==0 && (((int)zz+2)%5)==0 ||
                                (((int)xx+4)%5)==0 && (((int)zz+2)%5)==0 ||
                                (((int)xx+4)%5)==0 && (((int)zz+4)%5)==0 ||
                                (((int)xx+2)%5)==0 && (((int)zz+4)%5)==0
                            ) ) {
                            AY[y] = BlockInfo(89, 0, 0, 0 );
                        } else if ((((int)xx+3)%5)==0 && (((int)zz+3)%5)==0 ) {
                            int what=rand()%20;
                            setBoom(region,x,z,y);
                            AY[bottom+3-2] = BlockInfo(251, 0, 0, 0 );
                            AY[bottom+5-2] = BlockInfo(147, 0, 0, 0 );
                        } else if ((((int)xx+1+(rand()%5))%5)==0 && (((int)zz+1+(rand()%5))%5)==0 && edge==0 && edge2==0) {
                            int what=rand()%16;
                            if (what<15) setRabbits(region,x,z,y);
                            else if (what==15) setWolf(region,x,z,y);
                            else if (what==16) setRandom(region,x,z,y);
                            else { setBoom(region,x,z,y); AY[bottom+3-2] = BlockInfo(251, 0, 0, 0 ); }
                            AY[bottom+5-2] = BlockInfo(147, 0, 0, 0 );
                        } else if ((((int)xx+1+(rand()%5))%5)==0 && (((int)zz+1+(rand()%5))%5)==0 && edge==0 && edge2==0) {
                            int what=rand()%16;
                            if (what<15) setRabbits(region,x,z,y);
                            else if (what==15) setWolf(region,x,z,y);
                            else if (what==16) setRandom(region,x,z,y);
                            else { setBoom(region,x,z,y); AY[bottom+3-2] = BlockInfo(251, 0, 0, 0 ); }
                            AY[bottom+5-2] = BlockInfo(147, 0, 0, 0 );
                        } else if ((((int)xx+1+(rand()%5))%5)==0 && (((int)zz+1+(rand()%5))%5)==0 && edge==0 && edge2==0) {
                            int what=rand()%16;
                            if (what<15) setRabbits(region,x,z,y);
                            else if (what==15) setWolf(region,x,z,y);
                            else if (what==16) setRandom(region,x,z,y);
                            else { setBoom(region,x,z,y); AY[bottom+3-2] = BlockInfo(251, 0, 0, 0 ); }
                            AY[bottom+5-2] = BlockInfo(147, 0, 0, 0 );
                        } else if ((((int)xx+1+(rand()%5))%5)==0 && (((int)zz+1+(rand()%5))%5)==0 && edge==0 && edge2==0) {
                            int what=rand()%7;
                            if (what<5) setRabbits(region,x,z,y);
                            else if (what==5) setWolf(region,x,z,y);
                            else if (what==6) setRandom(region,x,z,y);
                            else { setBoom(region,x,z,y); AY[bottom+3-2] = BlockInfo(251, 0, 0, 0 ); }
                            AY[bottom+5-2] = BlockInfo(147, 0, 0, 0 );
                        }
                         else {
                            if (red2==1)
                                AY[y] = BlockInfo(251, 0, red, 0 );
                            else
                                AY[y] = BlockInfo(251, 0, white,0 );
                        }
                    }
                }
                else if (y==bottom+3-2 && (((int)xx+3)%5)==0 && (((int)zz+3)%5)==0 && pixel!=0) {
                    AY[y] = BlockInfo(251, 0, ret_color(rand()%256,rand()%256,rand()%256),0 );
                }
                else if (y==bottom+3-2) {
                    if (pixel!=0 ) {
                        AY[y] = BlockInfo(95, 0, ret_color(rand()%256,rand()%256,rand()%256),0 );
                    }
                }
               if (AY[y].id==95 && AY[y].data==0)  AY[y]=BlockInfo(20,0,0,0);
            }
        }
    }
}

int main_mceditor6_plot(int box_x, int box_y, int box_z, unsigned char* mc,
                   int box_x_block_start, int box_y_block_start, int box_z_block_start,
                   int box_x_total_start, int box_y_total_start, int box_z_total_start)
{
    int rand_color=rand()%15;
    int region_x=0;
    int region_z=0;

    int skippy=0;
    int skippy2=0;
    int contin=1;
    int skipping=1;
    int light=0;
    int size_regions=0;
	srand(time(0));
	int first_loop=1;
    remove_block_entities=1;
    bool zisout=false;
    bool xisout=false;
    while (size_regions<100) {
        size_regions++;
        for (region_x=0; region_x<size_regions && MCEDITOR_stop==0; region_x++) {
            zisout=false;
            for (region_z=0; region_z<size_regions && MCEDITOR_stop==0; region_z++) {
                region_xxx=region_x;
                region_zzz=region_z;
                if (region_x<size_regions-1 && region_z<size_regions-1) {
                    continue;
                }
                toggle_2=0;toggle_3=0;
                if (contin==1) {
                    contin=0;
                }
                chunk_offsetx=region_x*32;
                chunk_offsetz=region_z*32;

//                x00=0;
//                y00=0;
//                z00=0;
//                yl=255;  xl=512; zl=512;

                if ( chunk_offsetx*16+512 <  -box_y_block_start + box_y_total_start) continue;
                if ( chunk_offsetz*16+512 < + box_z_block_start - box_z_total_start) continue;
                if ( chunk_offsetx*16 > box_y - box_y_block_start  + box_y_total_start) continue;
                if ( chunk_offsetz*16 > box_z + box_z_block_start - box_z_total_start) continue;

                load_leeg=0;

                string fname=MCAFileNameXZ(region_x, region_z);
                char tmp[256];
                sprintf(tmp, "/Saves/Test/region/done0/r.%d.%d.mca", region_x, region_z);
                fname=tmp;

                int num_blocks=0;

                if (skippy2>0) printf("\n");
//                if (skippy>0 || skippy2>0) printf("\n");
                skippy=0;
                skippy2=0;
                scan_image.create(512,512);

                region_counter[region_x][region_z]++;

                char comm[100];

                size_t max_off=box_x*box_y*box_z*4;

                int num_blocks_added=0;
                int num_blocks_replaced=0;
                int num_blocks_deleted=0;
                int num_blocks_same=0;
                for (int x = 0; x < xl; x++) {
                    xx=x+chunk_offsetx*16;
                    int cube_y=xx + box_y_block_start - box_y_total_start;

                    for (int z = 0; z < zl; z++) {
                        zz=z+chunk_offsetz*16;
                        int cube_z=zz - box_z_block_start+box_z_total_start;
                        int max_y=-1;
                        int r_m;
                        int g_m;
                        int b_m;
                        scan_image.setPixel(x,z,sf::Color(0,0,0,0));
                        if (cube_y<0 || cube_y>=box_y) continue;
                        if (cube_z<0 || cube_z>=box_z) continue;
                        for (int y = 0; y < 256; y++) {
                            int cube_x=y - box_x_block_start + box_x_total_start;
                            if (cube_x<0 || cube_x>=box_x) continue;
//                            scan_image.setPixel(x,z,sf::Color(0,0,0,0));
                            size_t off=(cube_x+(box_y-1-cube_y)*box_x+cube_z*box_x*box_y)*4;
                            if (off>=max_off || off<0) {
                                printf("Error offset %d>=%d\n",off,max_off);
                                continue;
                            }
                            if (mc[off+3]>0) {
                                max_y=y;
                                r_m=mc[off];
                                g_m=mc[off+1];
                                b_m=mc[off+2];
                            }
                        }
                        if (max_y!=-1) scan_image.setPixel(x,z,sf::Color(r_m,g_m,b_m,255));
//                        else scan_image.setPixel(x,z,sf::Color(0,0,0,0));
                    }
                }

                scan_x=region_x;
                scan_z=region_z;
                sprintf(mc_text1,"R.%d.%d.MCA",region_x,region_z);
                update_request=2;

                while (update_request) {
                    sf::sleep(sf::seconds(0.005));
                }

                if (!plotting) printf(" ");
                first_MCEDIT=0;
                region_x_old=0;
                region_z_old=0;

                if (MCEDITOR_stop==1 || file_exists("stop.txt")) {
                    printf("Stop requested, exiting\n");
                    send_message='x';
                    return 0;
                }
            }
        }
    }
    return 0;
}



/*
sf::Mutex block_mutex;

int block_count=0;
glm::ivec3* blocks;
int region_x_request=0;
int region_z_request=0;
glm::vec3* block_colors;

void wait_for_blocks() {
    bool recieved=false;
    while (!recieved) {
        sf::sleep(sf::seconds(1.0));
        block_mutex.lock();
        if (block_count>0) {

        }
    }
}
*/

int scan_done0_sub(char* octant, FILE* report, int box_x, int box_y, int box_z, int box_x_block_start, int box_y_block_start, int box_z_block_start, int box_x_total_start, int box_y_total_start, int box_z_total_start);

int scan_done0(FILE* report, char* dat_filename, char* voxel_filename)
{
    random_pixel=sf::Color(64+rand()%64,64+rand()%64,64+rand()%64,255);

    int box_x,box_y,box_z;
    char octant[200]="";
    int box_x_block_start;
    int box_y_block_start;
    int box_z_block_start;
    int box_x_block_end;
    int box_y_block_end;
    int box_z_block_end;
    int box_x_total_start;
    int box_y_total_start;
    int box_z_total_start;
    int box_x_total_end;
    int box_y_total_end;
    int box_z_total_end;
    long num_bytes;
    double num_bytes_double;
    char area[200]="";

    char line[200]="";
    FILE * pFile;
    pFile = fopen ( dat_filename , "rb" );
//    pFile = fopen ( "../cut/voxel.dat" , "rb" );
    if (pFile==NULL)
    {
        printf("FILE NOT FOUND: %s\n",dat_filename);
        return (1);
    }

    if( fgets (line,200, pFile)!=NULL )
    {
        int numread=sscanf(line,"X=%d Y=%d Z=%d\n",&box_x,&box_y,&box_z);
        if (numread!=3) {
            printf("Error reading X Y Z %s\n",dat_filename);
//            printf("Error reading X Y Z../cut/voxel.dat\n");
            fclose(pFile);
            return (0);
        }
//        printf("box_x=            %6d box_y=           %6d  box_z=             %6d\n",box_x,box_y,box_z);
        if( fgets (line,200, pFile)!=NULL )
        {
            numread=sscanf(line,"OCTANT=%199[^\n]",octant);
            if (numread!=1) {
                printf("Error reading OCTANT %s\n",dat_filename);
//                printf("Error reading OCTANT ../cut/voxel.dat\n");
                fclose(pFile);
                return (0);
            }
        }
//        printf("octant=%s\n",octant);
        if( fgets (line,200, pFile)!=NULL )
        {
            numread=sscanf(line,"BYTES=%ld\n",&num_bytes);
            if (numread!=1) {
                printf("Error reading BYTES %s num_bytes=%ld\n",dat_filename,num_bytes);
//                printf("Error reading BYTES ../cut/voxel.dat num_bytes=%ld\n",num_bytes);
                fclose(pFile);
                return (0);
            }
        }
//        printf("num_bytes=%ld\n",num_bytes);
        if( fgets (line,200, pFile)!=NULL )
        {
            numread=sscanf(line,"ABS MIN X=%d Y=%d Z=%d\n",&box_x_block_start,&box_y_block_start,&box_z_block_start);
            if (numread!=3) {
                printf("Error reading ABS MIN %s\n",dat_filename);
//                printf("Error reading ABS MIN../cut/voxel.dat\n");
                fclose(pFile);
                return (0);
            }
        }
//        printf("box_x_block_start=%6d box_y_block_start=%6d box_z_block_start=%6d\n",box_x_block_start,box_y_block_start,box_z_block_start);
        if( fgets (line,200, pFile)!=NULL )
        {
            numread=sscanf(line,"ABS MAX X=%d Y=%d Z=%d\n",&box_x_block_end,&box_y_block_end,&box_z_block_end);
            if (numread!=3) {
                printf("Error reading ABS MAX../cut/voxel.dat\n");
                printf("Error reading ABS MAX %s\n",dat_filename);
                fclose(pFile);
                return (0);
            }
        }
//        printf("box_x_block_end=  %6d box_y_block_end=  %6d box_z_block_end=  %6d\n",box_x_block_end,box_y_block_end,box_z_block_end);
        if( fgets (line,200, pFile)!=NULL )
        {
            numread=sscanf(line,"TOTAL MIN X=%d Y=%d Z=%d\n",&box_x_total_start,&box_y_total_start,&box_z_total_start);
            if (numread!=3) {
//                printf("Error reading TOTAL MIN../cut/voxel.dat\n");
                printf("Error reading TOTAL MIN %s\n",dat_filename);
                fclose(pFile);
                return (0);
            }
        }
//        printf("box_x_total_start=%6d box_y_total_start=%6d box_z_total_start=%6d\n",box_x_total_start,box_y_total_start,box_z_total_start);
        if( fgets (line,200, pFile)!=NULL )
        {
            numread=sscanf(line,"TOTAL MAX X=%d Y=%d Z=%d\n",&box_x_total_end,&box_y_total_end,&box_z_total_end);
            if (numread!=3) {
                printf("Error reading TOTAL MAX %s\n",dat_filename);
//                printf("Error reading TOTAL MAX../cut/voxel.dat\n");
                fclose(pFile);
                return (0);
            }
        }
//        printf("box_x_total_end=  %6d box_y_total_end=  %6d box_z_total_end=  %6d\n",box_x_total_end,box_y_total_end,box_z_total_end);
        if( fgets (line,200, pFile)!=NULL )
        {
            numread=sscanf(line,"AREA=%199[^\n]",area);
            if (numread!=1) {
                printf("Error reading AREA %s\n",dat_filename);
//                printf("Error reading AREA../cut/voxel.dat\n");
                fclose(pFile);
                return (0);
            }
        }
//        printf("area=%s\n",area);

/*
    ofs << "X=" << box_x << " Y=" << box_y << " Z=" << box_z << "\n";
    ofs << "OCTANT=" << fn.c_str() << "\n";
    ofs << "BYTES=" << tot_off << "\n";

    ofs << "ABS MIN X=" << box_x_block_start << " Y=" << box_y_block_start << " Z=" << box_z_block_start << "\n";
    ofs << "ABS MAX X=" << box_x_block_end   << " Y=" << box_y_block_end   << " Z=" << box_z_block_end   << "\n";
    ofs << "TOTAL MIN X=" << box_x_total_start << " Y=" << box_y_total_start << " Z=" << box_z_total_start << "\n";
    ofs << "TOTAL MAX X=" << box_x_total_end   << " Y=" << box_y_total_end   << " Z=" << box_z_total_end   << "\n";
    ofs << "AREA = " << area   << "\n";
*/


//        printf("Loaded %s  X=%d y=%d Z=%d OCTANT=%s\n", dat_filename, box_x, box_y, box_z, octant);
//        printf("Loaded ../cut/voxel.dat  X=%d y=%d Z=%d OCTANT=%s\n", box_x, box_y, box_z, octant);
    }
    fclose(pFile);

    size_t tot_off=box_x*box_y*box_z*4;



//    printf(" -> Testing witch regions are in here\n");

//    printf("\n");
//    printf("box_x_block_start=%6d   box_y_block_start=%6d   box_z_block_start=%6d\n",   box_x_block_start,                      box_y_block_start,                      box_z_block_start       );
//    printf("box_x_block_end  =%6d   box_y_block_end  =%6d   box_z_block_end  =%6d\n",   box_x_block_end,                        box_y_block_end,                        box_z_block_end         );
//    printf("dif_x_block      =%6d   dif_y_block      =%6d   dif_z_block      =%6d\n",   box_x_block_end-   box_x_block_start,   box_y_block_end-box_y_block_start,      box_z_block_end-box_z_block_start);
//    printf("\n");
//    printf("box_x_total_start=%6d   box_y_total_start=%6d   box_z_total_start=%6d\n",   box_x_total_start,                      box_y_total_start,                      box_z_total_start       );
//    printf("box_x_total_end=  %6d   box_y_total_end=  %6d   box_z_total_end=  %6d\n",   box_x_total_end,                        box_y_total_end,                        box_z_total_end         );
//    printf("dif_x_total      =%6d   dif_y_total      =%6d   dif_z_total      =%6d\n",   box_x_total_end-box_x_total_start,      box_y_total_end-box_y_total_start,      box_z_total_end-box_z_total_start);
//    printf("\n");
//    printf("Setting           %6d                    %6d                      %6d\n",   box_x,                                  box_y,                                  box_z);
//    printf("\n");
//
    report = fopen ( "report.txt" , "a" );
    fprintf(report,"\n\noctant: %s\n",octant);
    sprintf(mc_text2,"%s",octant);
    scan_done0_sub(octant, report,
        box_x, box_y, box_z,
        box_x_block_start,                      box_y_block_start+2048,                     box_z_block_start+2048,
        box_x_total_start,                      box_y_total_end,                            box_z_total_start
    );
    fclose(report);
}


int scan_done0_sub(char* octant, FILE* report, int box_x, int box_y, int box_z, int box_x_block_start, int box_y_block_start, int box_z_block_start, int box_x_total_start, int box_y_total_start, int box_z_total_start)
{

    int region_x=0;
    int region_z=0;

    int skippy=0;
    int skippy2=0;
    int contin=1;
    int skipping=1;
    int light=0;
    int size_regions=0;
	srand(time(0));
	int first_loop=1;
    remove_block_entities=1;
    bool zisout=false;
    bool xisout=false;
    while (size_regions<100) {
        size_regions++;
        for (region_x=0; region_x<size_regions && MCEDITOR_stop==0; region_x++) {
            zisout=false;
            for (region_z=0; region_z<size_regions && MCEDITOR_stop==0; region_z++) {

                int max_x_rel=-std::numeric_limits<int>::max();
                int max_x_abs=-std::numeric_limits<int>::max();
                int min_x_rel=std::numeric_limits<int>::max();
                int min_x_abs=std::numeric_limits<int>::max();

                int max_z_rel=-std::numeric_limits<int>::max();
                int max_z_abs=-std::numeric_limits<int>::max();
                int min_z_rel=std::numeric_limits<int>::max();
                int min_z_abs=std::numeric_limits<int>::max();

                int max_y=-std::numeric_limits<int>::max();
                int min_y=std::numeric_limits<int>::max();

                int real_max_x=-std::numeric_limits<int>::max();
                int real_min_x=std::numeric_limits<int>::max();

                int real_max_z=-std::numeric_limits<int>::max();
                int real_min_z=std::numeric_limits<int>::max();

                int real_max_y=-std::numeric_limits<int>::max();
                int real_min_y=std::numeric_limits<int>::max();

                region_xxx=region_x;
                region_zzz=region_z;
                if (region_x<size_regions-1 && region_z<size_regions-1) {
                    continue;
                }
                toggle_2=0;toggle_3=0;
                if (contin==1) {
                    contin=0;
                }
                chunk_offsetx=region_x*32;
                chunk_offsetz=region_z*32;

                x00=0;
                y00=0;
                z00=0;
                yl=255;  xl=512; zl=512;

                if ( chunk_offsetx*16+512 <  -box_y_block_start + box_y_total_start) {
                    continue;
                }

                if ( chunk_offsetz*16+512 < + box_z_block_start - box_z_total_start) {
                    continue;
                }

                if ( chunk_offsetx*16 > box_y - box_y_block_start  + box_y_total_start) {
                    continue;
                }

                if ( chunk_offsetz*16 > box_z + box_z_block_start - box_z_total_start) {
                    continue;
                }

                string fname=MCAFileNameXZ(region_x, region_z);
                char tmp[256];
                sprintf(tmp, "/Saves/Test/region/done0/r.%d.%d.mca", region_x, region_z);
                fname=tmp;
                bool nofile=false;
                if ( !file_exists(fname.c_str() ) ) {
                    nofile=true;
                    fprintf(report,"File %s doesn't exists!!!!!!!!!!!!!!",fname.c_str());
                    printf("File %s doesn't exists!!!!!!!!!!!!!!",fname.c_str());
                    region_counter[region_x][region_z]=9;
                } else {
//if (1 || region_counter[region_x][region_z]==0) {
                    region_counter[region_x][region_z]++;
                    if (region_counter[region_x][region_z] > 4) printf("File %s EXISTS %d TIMES!!!!!!!!!!!!!!!!!!!!!!!!!!!!!",fname.c_str(),region_counter[region_x][region_z]);
                }
                if (0 && region_counter[region_x][region_z]==1) {
//                region.clearRegion();
                    MCRegion region(x00, z00, y00, xl, zl, yl);

                    remove_block_entities=0;
//                    printf("File %s exists. ",fname.c_str());
                    first_MCEDIT=1;
                    editor.mca_coder.loadMCA(fname.c_str());
                    first_MCEDIT=0;
                    region_x_old=0,region_z_old=0;

                    BlockInfo*** AX=region.A;

                    for (int x = 0; x < xl; x++) {
                        BlockInfo** AZ=AX[x];
                        for (int z = 0; z < zl; z++) {
                            BlockInfo* AY=AZ[z];
                            for (int y = 0; y < 256; y++) {
                                BlockInfo bi=editor.mca_coder.getBlock(x,z,y);
                                if (bi.id!=0) AY[y]=BlockInfo(bi.id,bi.add,bi.data,bi.block_light,bi.sky_light);
                            }
                        }
                    }
                    reset_block();

                    for (int x = 0; x < xl; x++) {
                        BlockInfo** AZ=AX[x];
                        for (int z = 0; z < zl; z++) {
                            BlockInfo* AY=AZ[z];
                            for (int y = 0; y < 256; y++) {
                                if (AY[y].id!=0) {

                                    if (x>real_max_x) real_max_x=x;
                                    if (x<real_min_x) real_min_x=x;
                                    if (y>real_max_y) real_max_y=y;
                                    if (y<real_min_y) real_min_y=y;
                                    if (z>real_max_z) real_max_z=z;
                                    if (z<real_min_z) real_min_z=z;
                                    continue;
                                }
                            }
                        }
                    }
                }

                scan_image.create(512,512);
                if (1) {
                    for (int x = 0; x < xl; x++) {
                        xx=x+chunk_offsetx*16;
                        int cube_y=xx + box_y_block_start - box_y_total_start;
                        for (int z = 0; z < zl; z++) {
                            zz=z+chunk_offsetz*16;
                            int cube_z=zz - box_z_block_start+box_z_total_start;

                            if (!nofile) scan_image.setPixel(x,z,sf::Color(0,0,0,0));

                            if (cube_y<0 || cube_y>=box_y) {
                                scan_image.setPixel(x,z,sf::Color(0,0,0,0));
                                continue;
                            }
                            if (cube_z<0 || cube_z>=box_z) {
                                scan_image.setPixel(x,z,sf::Color(0,0,0,0));
                                continue;
                            }

                            for (int y = 0; y < 256; y++) {
                                int cube_x=y - box_x_block_start + box_x_total_start;
                                if (cube_x<0 || cube_x>=box_x) {
                                    scan_image.setPixel(x,z,sf::Color(0,0,0,0));
                                    continue;
                                }
                                if (y>max_y) {
                                    max_y=y;
                                }
                                if (y<min_y) {
                                    min_y=y;
                                }

                                if (z>max_z_rel) {
                                    max_z_rel=z;
                                    max_z_abs=zz;
                                }
                                if (z<min_z_rel) {
                                    min_z_rel=z;
                                    min_z_abs=zz;
                                }

                                if (x>max_x_rel) {
                                    max_x_rel=x;
                                    max_x_abs=xx;
                                }
                                if (x<min_x_rel) {
                                    min_x_rel=x;
                                    min_x_abs=xx;
                                }
                            }
                            if (nofile) {
                                scan_image.setPixel(x,z,sf::Color(255,0,0,255));
//                                else scan_image.setPixel(x,z,sf::Color(255,random_pixel.g/2,random_pixel.b/2,50));
                            } else {
                                if (max_y>=0) scan_image.setPixel(x,z,sf::Color(random_pixel.r,random_pixel.g,random_pixel.b,255));
//                                if (max_y>=0) scan_image.setPixel(x,z,sf::Color(max_y,max_y,max_y,255));
                                else scan_image.setPixel(x,z,sf::Color(0,0,0,0));
//                                else scan_image.setPixel(x,z,sf::Color(random_pixel.r,random_pixel.g,random_pixel.b,50));
                            }
                        }
                    }
                }
                printf("REGION X=%2d REGION Z=%2d  CNT=%d  X: MIN=(%3d,%5d) MAX=(%3d,%5d)  Z: MIN=(%3d,%5d) MAX=(%3d,%5d)  Y: MIN=%3d MAX=%3d",
                        region_x,region_z, region_counter[region_x][region_z],
                        min_x_rel,min_x_abs,max_x_rel,max_x_abs,
                        min_z_rel,min_z_abs,max_z_rel,max_z_abs,
                        min_y,max_y);
                fprintf(report, "REGION X=%2d REGION Z=%2d  CNT=%d  X: MIN=(%3d,%5d) MAX=(%3d,%5d)  Z: MIN=(%3d,%5d) MAX=(%3d,%5d)  Y: MIN=%3d MAX=%3d",
                        region_x,region_z, region_counter[region_x][region_z],
                        min_x_rel,min_x_abs,max_x_rel,max_x_abs,
                        min_z_rel,min_z_abs,max_z_rel,max_z_abs,
                        min_y,max_y);


/*
                if (region_counter[region_x][region_z]!=0) {
                    if (real_max_x!=511 || real_min_x!=0 || real_max_z!=511 || real_min_z!=0) {
                        printf("  GAP: X(%3d,%3d) Z(%3d,%3d)",real_min_x,real_max_x,real_min_z,real_max_z);
                        fprintf(report,"  GAP: X(%3d,%3d) Z(%3d,%3d)",real_min_x,real_max_x,real_min_z,real_max_z);
                        region_counter[region_x][region_z]=9;
                    }
                }
*/

                scan_x=region_x;
                scan_z=region_z;
                sprintf(mc_text1,"R.%d.%d.MCA",region_x,region_z);
                update_request=2;

                while (update_request) {
                    sf::sleep(sf::seconds(0.005));
                }
//                update_MC(sf::Image& image_local, region_x*512, region_z*512);

                printf("\n");
                fprintf(report, "\n");
                if (MCEDITOR_stop==1 || file_exists("stop.txt")) {
                    printf("Stop requested, exiting\n");
//                    system("/saves/copy_test.bat");
//                    send_message='x';
                    return 0;
                }
            }
        }
    }
    return 0;
}


int scan_done0_sub_plot(char* octant, FILE* report, unsigned char* mc, int box_x, int box_y, int box_z, int box_x_block_start, int box_y_block_start, int box_z_block_start, int box_x_total_start, int box_y_total_start, int box_z_total_start);

int scan_done0_plot(FILE* report, char* dat_filename, char* voxel_filename)
{
    random_pixel=sf::Color(64+rand()%64,64+rand()%64,64+rand()%64,255);

    int box_x,box_y,box_z;
    char octant[200]="";
    int box_x_block_start;
    int box_y_block_start;
    int box_z_block_start;
    int box_x_block_end;
    int box_y_block_end;
    int box_z_block_end;
    int box_x_total_start;
    int box_y_total_start;
    int box_z_total_start;
    int box_x_total_end;
    int box_y_total_end;
    int box_z_total_end;
    long num_bytes;
    double num_bytes_double;
    char area[200]="";

    char line[200]="";
    FILE * pFile;
    pFile = fopen ( dat_filename , "rb" );
//    pFile = fopen ( "../cut/voxel.dat" , "rb" );
    if (pFile==NULL)
    {
        printf("FILE NOT FOUND: %s\n",dat_filename);
        return (1);
    }

    if( fgets (line,200, pFile)!=NULL )
    {
        int numread=sscanf(line,"X=%d Y=%d Z=%d\n",&box_x,&box_y,&box_z);
        if (numread!=3) {
            printf("Error reading X Y Z %s\n",dat_filename);
//            printf("Error reading X Y Z../cut/voxel.dat\n");
            fclose(pFile);
            return (0);
        }
//        printf("box_x=            %6d box_y=           %6d  box_z=             %6d\n",box_x,box_y,box_z);
        if( fgets (line,200, pFile)!=NULL )
        {
            numread=sscanf(line,"OCTANT=%199[^\n]",octant);
            if (numread!=1) {
                printf("Error reading OCTANT %s\n",dat_filename);
//                printf("Error reading OCTANT ../cut/voxel.dat\n");
                fclose(pFile);
                return (0);
            }
        }
//        printf("octant=%s\n",octant);
        if( fgets (line,200, pFile)!=NULL )
        {
            numread=sscanf(line,"BYTES=%ld\n",&num_bytes);
            if (numread!=1) {
                printf("Error reading BYTES %s num_bytes=%ld\n",dat_filename,num_bytes);
//                printf("Error reading BYTES ../cut/voxel.dat num_bytes=%ld\n",num_bytes);
                fclose(pFile);
                return (0);
            }
        }
//        printf("num_bytes=%ld\n",num_bytes);
        if( fgets (line,200, pFile)!=NULL )
        {
            numread=sscanf(line,"ABS MIN X=%d Y=%d Z=%d\n",&box_x_block_start,&box_y_block_start,&box_z_block_start);
            if (numread!=3) {
                printf("Error reading ABS MIN %s\n",dat_filename);
//                printf("Error reading ABS MIN../cut/voxel.dat\n");
                fclose(pFile);
                return (0);
            }
        }
//        printf("box_x_block_start=%6d box_y_block_start=%6d box_z_block_start=%6d\n",box_x_block_start,box_y_block_start,box_z_block_start);
        if( fgets (line,200, pFile)!=NULL )
        {
            numread=sscanf(line,"ABS MAX X=%d Y=%d Z=%d\n",&box_x_block_end,&box_y_block_end,&box_z_block_end);
            if (numread!=3) {
                printf("Error reading ABS MAX../cut/voxel.dat\n");
                printf("Error reading ABS MAX %s\n",dat_filename);
                fclose(pFile);
                return (0);
            }
        }
//        printf("box_x_block_end=  %6d box_y_block_end=  %6d box_z_block_end=  %6d\n",box_x_block_end,box_y_block_end,box_z_block_end);
        if( fgets (line,200, pFile)!=NULL )
        {
            numread=sscanf(line,"TOTAL MIN X=%d Y=%d Z=%d\n",&box_x_total_start,&box_y_total_start,&box_z_total_start);
            if (numread!=3) {
//                printf("Error reading TOTAL MIN../cut/voxel.dat\n");
                printf("Error reading TOTAL MIN %s\n",dat_filename);
                fclose(pFile);
                return (0);
            }
        }
//        printf("box_x_total_start=%6d box_y_total_start=%6d box_z_total_start=%6d\n",box_x_total_start,box_y_total_start,box_z_total_start);
        if( fgets (line,200, pFile)!=NULL )
        {
            numread=sscanf(line,"TOTAL MAX X=%d Y=%d Z=%d\n",&box_x_total_end,&box_y_total_end,&box_z_total_end);
            if (numread!=3) {
                printf("Error reading TOTAL MAX %s\n",dat_filename);
//                printf("Error reading TOTAL MAX../cut/voxel.dat\n");
                fclose(pFile);
                return (0);
            }
        }
//        printf("box_x_total_end=  %6d box_y_total_end=  %6d box_z_total_end=  %6d\n",box_x_total_end,box_y_total_end,box_z_total_end);
        if( fgets (line,200, pFile)!=NULL )
        {
            numread=sscanf(line,"AREA=%199[^\n]",area);
            if (numread!=1) {
                printf("Error reading AREA %s\n",dat_filename);
//                printf("Error reading AREA../cut/voxel.dat\n");
                fclose(pFile);
                return (0);
            }
        }
//        printf("area=%s\n",area);

/*
    ofs << "X=" << box_x << " Y=" << box_y << " Z=" << box_z << "\n";
    ofs << "OCTANT=" << fn.c_str() << "\n";
    ofs << "BYTES=" << tot_off << "\n";

    ofs << "ABS MIN X=" << box_x_block_start << " Y=" << box_y_block_start << " Z=" << box_z_block_start << "\n";
    ofs << "ABS MAX X=" << box_x_block_end   << " Y=" << box_y_block_end   << " Z=" << box_z_block_end   << "\n";
    ofs << "TOTAL MIN X=" << box_x_total_start << " Y=" << box_y_total_start << " Z=" << box_z_total_start << "\n";
    ofs << "TOTAL MAX X=" << box_x_total_end   << " Y=" << box_y_total_end   << " Z=" << box_z_total_end   << "\n";
    ofs << "AREA = " << area   << "\n";
*/


//        printf("Loaded %s  X=%d y=%d Z=%d OCTANT=%s\n", dat_filename, box_x, box_y, box_z, octant);
//        printf("Loaded ../cut/voxel.dat  X=%d y=%d Z=%d OCTANT=%s\n", box_x, box_y, box_z, octant);
    }
    fclose(pFile);

    size_t tot_off=box_x*box_y*box_z*4;

    printf("Setting %dx%dx%dx4 s=%d bytes ", box_x, box_y, box_z, tot_off);
    unsigned char *mc = new unsigned char [tot_off];
    if (mc!=NULL) printf("OK!\n");
    else {
        printf("Error allocating memory\n");
        return (1);
    }
    printf("Ready\n");

//    std::memset(mc, 0x0, box_x * box_y * box_z * 4);


    printf("Loading %s (%dx%dx%dx4)(%u bytes)", voxel_filename, box_x, box_y, box_z, tot_off);
//    printf("Loading ../cut/voxel.raw (%dx%dx%dx4)(%u bytes)", box_x, box_y, box_z, tot_off);
    unsigned long long lSize;
    size_t result;
    pFile = fopen ( voxel_filename , "rb" );
    if (pFile==NULL) {
        printf("File error: %s\n",voxel_filename);
        delete [] mc;
        return (1);
    }
    fseek (pFile , 0 , SEEK_END);
    lSize = ftell (pFile);
    rewind (pFile);

    if (lSize!=tot_off) {
        printf(" Error (size) %s ... %u <-> %u\n", voxel_filename, lSize,tot_off);
//        fclose(pFile);
//        delete [] mc;
//        return (1);
    } else {
        printf(" -> Ok! -> Loading");
    }

    if (mirror!=3) result = fread(mc,1,tot_off,pFile);
    else result=tot_off;
    fclose(pFile);

    if (result!=tot_off) {
        printf("Error loading %s\n",voxel_filename);
        delete [] mc;
        return (1);
    }

    printf(" -> Ok! -> %lld bytes loaded",result);



//    printf(" -> Testing witch regions are in here\n");

//    printf("\n");
//    printf("box_x_block_start=%6d   box_y_block_start=%6d   box_z_block_start=%6d\n",   box_x_block_start,                      box_y_block_start,                      box_z_block_start       );
//    printf("box_x_block_end  =%6d   box_y_block_end  =%6d   box_z_block_end  =%6d\n",   box_x_block_end,                        box_y_block_end,                        box_z_block_end         );
//    printf("dif_x_block      =%6d   dif_y_block      =%6d   dif_z_block      =%6d\n",   box_x_block_end-   box_x_block_start,   box_y_block_end-box_y_block_start,      box_z_block_end-box_z_block_start);
//    printf("\n");
//    printf("box_x_total_start=%6d   box_y_total_start=%6d   box_z_total_start=%6d\n",   box_x_total_start,                      box_y_total_start,                      box_z_total_start       );
//    printf("box_x_total_end=  %6d   box_y_total_end=  %6d   box_z_total_end=  %6d\n",   box_x_total_end,                        box_y_total_end,                        box_z_total_end         );
//    printf("dif_x_total      =%6d   dif_y_total      =%6d   dif_z_total      =%6d\n",   box_x_total_end-box_x_total_start,      box_y_total_end-box_y_total_start,      box_z_total_end-box_z_total_start);
//    printf("\n");
//    printf("Setting           %6d                    %6d                      %6d\n",   box_x,                                  box_y,                                  box_z);
//    printf("\n");
//
    report = fopen ( "report.txt" , "a" );
    fprintf(report,"\n\noctant: %s\n",octant);
//    sprintf(mc_text2,"");
    sprintf(mc_text2,"%s",octant);
    scan_done0_sub_plot(octant, report, mc,
        box_x, box_y, box_z,
        box_x_block_start,                      box_y_block_start+2048,                     box_z_block_start+2048,
        box_x_total_start,                      box_y_total_end,                            box_z_total_start
    );
    fclose(report);

    delete [] mc;

/*
    char naam[200];
    mkdir("../cut/done");
    sprintf(naam,"move ..\\cut\\%s*.* ..\\cut\\done\\",voxel_filename);
    system(naam);
    sprintf(naam,"move ..\\cut\\%s*.* ..\\cut\\done\\",dat_filename);
    system(naam);
*/
}
extern int crossing;

void scan_done0_regionfiles(char* what) {
    mirror=3;
    crossing=3;
    unsigned char *mc;
    FILE* report = fopen ( "report.txt" , "a" );
    fprintf(report,"\n\nregion dir: %s\n",what);
    sprintf(mc_text2,"%d",mcglobal2);
    scan_done0_sub_plot(what, report, mc,
        256, 512*10, 512*10,
        0,                      0,                     0,
        0,                      0,                     0
    );
    fclose(report);
    mirror=0;
    crossing=0;
}


extern bool wuppie_all;


int scan_done0_sub_plot(char* octant, FILE* report, unsigned char* mc, int box_x, int box_y, int box_z, int box_x_block_start, int box_y_block_start, int box_z_block_start, int box_x_total_start, int box_y_total_start, int box_z_total_start)
{

    int region_x=0;
    int region_z=0;

    int skippy=0;
    int skippy2=0;
    int contin=1;
    int skipping=1;
    int light=0;
    int size_regions=0;
	srand(time(0));
	int first_loop=1;
    remove_block_entities=1;
    bool zisout=false;
    bool xisout=false;
    while (size_regions<100) {
        size_regions++;
        for (region_x=0; region_x<size_regions && MCEDITOR_stop==0; region_x++) {
            zisout=false;
            for (region_z=0; region_z<size_regions && MCEDITOR_stop==0; region_z++) {

                int max_x_rel=-std::numeric_limits<int>::max();
                int max_x_abs=-std::numeric_limits<int>::max();
                int min_x_rel=std::numeric_limits<int>::max();
                int min_x_abs=std::numeric_limits<int>::max();

                int max_z_rel=-std::numeric_limits<int>::max();
                int max_z_abs=-std::numeric_limits<int>::max();
                int min_z_rel=std::numeric_limits<int>::max();
                int min_z_abs=std::numeric_limits<int>::max();

                int max_y=-std::numeric_limits<int>::max();
                int min_y=std::numeric_limits<int>::max();

                int real_max_x=-std::numeric_limits<int>::max();
                int real_min_x=std::numeric_limits<int>::max();

                int real_max_z=-std::numeric_limits<int>::max();
                int real_min_z=std::numeric_limits<int>::max();

                int real_max_y=-std::numeric_limits<int>::max();
                int real_min_y=std::numeric_limits<int>::max();

                region_xxx=region_x;
                region_zzz=region_z;
                if (region_x<size_regions-1 && region_z<size_regions-1) {
                    continue;
                }
                toggle_2=0;toggle_3=0;
                if (contin==1) {
                    contin=0;
                }
                chunk_offsetx=region_x*32;
                chunk_offsetz=region_z*32;

                x00=0;
                y00=0;
                z00=0;
                yl=255;  xl=512; zl=512;


                if ( chunk_offsetx*16+512 <  -box_y_block_start + box_y_total_start) continue;
                if ( chunk_offsetz*16+512 < + box_z_block_start - box_z_total_start) continue;
                if ( chunk_offsetx*16 > box_y - box_y_block_start  + box_y_total_start) continue;
                if ( chunk_offsetz*16 > box_z + box_z_block_start - box_z_total_start) continue;

                string fname=MCAFileNameXZ(region_x, region_z);
                char tmp[256];

                if (mcglobal==6 || mcglobal==7)
                    sprintf(tmp, "%s/r.%d.%d.mca", octant, region_x, region_z);
                else
                    sprintf(tmp, "/Saves/Test/region/done0/r.%d.%d.mca", region_x, region_z);

                fname=tmp;
                bool nofile=false;
                if (wuppie_all) {
                    if ( !file_exists(fname.c_str() ) ) {
                        nofile=true;
                        fprintf(report,"File %s doesn't exists!!!!!!!!!!!!!!",fname.c_str());
                        printf("File %s doesn't exists!!!!!!!!!!!!!!",fname.c_str());
                        region_counter[region_x][region_z]=9;
                    } else {
    //if (1 || region_counter[region_x][region_z]==0) {
                        region_counter[region_x][region_z]++;
                        if (region_counter[region_x][region_z] > 4) printf("File %s EXISTS %d TIMES!!!!!!!!!!!!!!!!!!!!!!!!!!!!!",fname.c_str(),region_counter[region_x][region_z]);
                    }
                } else {
                    region_counter[region_x][region_z]=1;
                }
                scan_image.create(512,512);
                if (mirror==3 && region_counter[region_x][region_z]==1) {
                    printf("\n");
//                  region.clearRegion();
                    MCRegion region(x00, z00, y00, xl, zl, yl);

                    remove_block_entities=0;
//                    printf("File %s exists. ",fname.c_str());
                    first_MCEDIT=1;
                    editor.mca_coder.loadMCA(fname.c_str());
                    first_MCEDIT=0;
                    region_x_old=0,region_z_old=0;

                    BlockInfo*** AX=region.A;

                    for (int x = 0; x < xl; x++) {
                        BlockInfo** AZ=AX[x];
                        for (int z = 0; z < zl; z++) {
                            BlockInfo* AY=AZ[z];
                            int max_y=-1;
                            for (int y = 0; y < 256; y++) {
                                BlockInfo bi=editor.mca_coder.getBlock(x,z,y);
                                if (bi.id!=0) {
                                    AY[y]=BlockInfo(bi.id,bi.add,bi.data,bi.block_light,bi.sky_light);
                                    if (mcglobal==6) {
                                        if (mcglobal3>0 && y<=mcglobal3) {
                                            max_y=y;
                                        }
                                    } else if (mcglobal==7) {
                                        if (mcglobal3>0 && y==mcglobal3) {
                                            max_y=y;
                                        }
                                    } else {
                                        max_y=y;
                                    }
                                }
                            }
                            if (max_y!=-1) {
                                int r_m,g_m,b_m;
                                ret_color_rev( AY[max_y].data, r_m, g_m, b_m );
                                scan_image.setPixel(x,z,sf::Color(r_m,g_m,b_m,255));
                            } else {
                                scan_image.setPixel(x,z,sf::Color(0,0,0,0));
                            }
                        }
                    }
                    reset_block();

                    scan_x=region_x;
                    scan_z=region_z;
                    sprintf(mc_text1,"R.%d.%d.MCA",region_x,region_z);
                    update_request=2;

                    while (update_request) {
                        sf::sleep(sf::seconds(0.005));
                    }

                    size_t max_off=box_x*box_y*box_z*4;

                    for (int x = 0; x < xl; x++) {
                        BlockInfo** AZ=AX[x];
                        for (int z = 0; z < zl; z++) {
                            BlockInfo* AY=AZ[z];
                            for (int y = 0; y < 256; y++) {
                                if (AY[y].id!=0) {
                                    if (x>real_max_x) real_max_x=x;
                                    if (x<real_min_x) real_min_x=x;
                                    if (y>real_max_y) real_max_y=y;
                                    if (y<real_min_y) real_min_y=y;
                                    if (z>real_max_z) real_max_z=z;
                                    if (z<real_min_z) real_min_z=z;
                                    continue;
                                }
                            }
                        }
                    }
                    continue;
                }
                if (mirror==3) {
                    for (int x = 0; x < xl; x++) {
                        for (int z = 0; z < zl; z++) {
                            scan_image.setPixel(x,z,sf::Color(255,0,0,255));
                        }
                    }

                    scan_x=region_x;
                    scan_z=region_z;
                    sprintf(mc_text1,"R.%d.%d.MCA",region_x,region_z);
                    update_request=2;

                    while (update_request) {
                        sf::sleep(sf::seconds(0.005));
                    }
                    continue;
                }

                size_t max_off=box_x*box_y*box_z*4;

                if (1) {
                    for (int x = 0; x < xl; x++) {
                        xx=x+chunk_offsetx*16;
                        int cube_y=xx + box_y_block_start - box_y_total_start;
                        for (int z = 0; z < zl; z++) {
                            zz=z+chunk_offsetz*16;
                            int cube_z=zz - box_z_block_start+box_z_total_start;

                            if (!nofile) scan_image.setPixel(x,z,sf::Color(0,0,0,0));

                            if (cube_y<0 || cube_y>=box_y) {
                                scan_image.setPixel(x,z,sf::Color(0,0,0,0));
                                continue;
                            }
                            if (cube_z<0 || cube_z>=box_z) {
                                scan_image.setPixel(x,z,sf::Color(0,0,0,0));
                                continue;
                            }

                            int r_m;
                            int g_m;
                            int b_m;
                            for (int y = 0; y < 256; y++) {
                                int cube_x=y - box_x_block_start + box_x_total_start;
                                if (cube_x<0 || cube_x>=box_x) {
//                                    scan_image.setPixel(x,z,sf::Color(255,255,0,10));
                                    scan_image.setPixel(x,z,sf::Color(0,0,0,0));
                                    continue;
                                }
                                size_t off=(cube_x+(box_y-1-cube_y)*box_x+cube_z*box_x*box_y)*4;
//                                    size_t off=(cube_x+cube_y*box_x+cube_z*box_x*box_y)*4;
                                if (off>=max_off || off<0) {
                                    printf("Error offset %d>=%d\n",off,max_off);
                                    continue;
                                }

                                if (mc[off+3]>0) {
                                    if (min_y==-1) min_y=y;
                                    max_y=y;
                                    r_m=mc[off];
                                    g_m=mc[off+1];
                                    b_m=mc[off+2];
                                }

                                if (y>max_y) {
                                    max_y=y;
                                }
                                if (y<min_y) {
                                    min_y=y;
                                }

                                if (z>max_z_rel) {
                                    max_z_rel=z;
                                    max_z_abs=zz;
                                }
                                if (z<min_z_rel) {
                                    min_z_rel=z;
                                    min_z_abs=zz;
                                }

                                if (x>max_x_rel) {
                                    max_x_rel=x;
                                    max_x_abs=xx;
                                }
                                if (x<min_x_rel) {
                                    min_x_rel=x;
                                    min_x_abs=xx;
                                }
                            }

                            if (mirror==2) {
                                int idx=ret_color(r_m,g_m,b_m);
                                ret_color_rev( idx, r_m, g_m, b_m );
                            }
                            if (nofile) {
                                if (max_y!=-1) scan_image.setPixel(x,z,sf::Color(127+r_m/255,g_m,b_m,255));
                                else scan_image.setPixel(x,z,sf::Color(0,0,0,0));
//                                scan_image.setPixel(x,z,sf::Color(255,0,0,255));
//                                else scan_image.setPixel(x,z,sf::Color(255,random_pixel.g/2,random_pixel.b/2,50));
                            } else {
                                if (max_y!=-1) scan_image.setPixel(x,z,sf::Color(r_m,g_m,b_m,255));
                                else scan_image.setPixel(x,z,sf::Color(0,0,0,0));
//                                if (max_y>=0) scan_image.setPixel(x,z,sf::Color(random_pixel.r,random_pixel.g,random_pixel.b,255));
//                                if (max_y>=0) scan_image.setPixel(x,z,sf::Color(max_y,max_y,max_y,255));
//                                else scan_image.setPixel(x,z,sf::Color(random_pixel.r,random_pixel.g,random_pixel.b,50));
                            }
                        }
                    }
                }
                if (wuppie_all) printf("REGION X=%2d REGION Z=%2d  CNT=%d  X: MIN=(%3d,%5d) MAX=(%3d,%5d)  Z: MIN=(%3d,%5d) MAX=(%3d,%5d)  Y: MIN=%3d MAX=%3d",
                        region_x,region_z, region_counter[region_x][region_z],
                        min_x_rel,min_x_abs,max_x_rel,max_x_abs,
                        min_z_rel,min_z_abs,max_z_rel,max_z_abs,
                        min_y,max_y);
                if (wuppie_all) fprintf(report, "REGION X=%2d REGION Z=%2d  CNT=%d  X: MIN=(%3d,%5d) MAX=(%3d,%5d)  Z: MIN=(%3d,%5d) MAX=(%3d,%5d)  Y: MIN=%3d MAX=%3d",
                        region_x,region_z, region_counter[region_x][region_z],
                        min_x_rel,min_x_abs,max_x_rel,max_x_abs,
                        min_z_rel,min_z_abs,max_z_rel,max_z_abs,
                        min_y,max_y);


/*
                if (region_counter[region_x][region_z]!=0) {
                    if (real_max_x!=511 || real_min_x!=0 || real_max_z!=511 || real_min_z!=0) {
                        printf("  GAP: X(%3d,%3d) Z(%3d,%3d)",real_min_x,real_max_x,real_min_z,real_max_z);
                        fprintf(report,"  GAP: X(%3d,%3d) Z(%3d,%3d)",real_min_x,real_max_x,real_min_z,real_max_z);
                        region_counter[region_x][region_z]=9;
                    }
                }
*/

                scan_x=region_x;
                scan_z=region_z;
                sprintf(mc_text1,"R.%d.%d.MCA",region_x,region_z);
                update_request=2;

                while (update_request) {
                    sf::sleep(sf::seconds(0.005));
                }
//                update_MC(sf::Image& image_local, region_x*512, region_z*512);

                if (wuppie_all) printf("\n");
                if (wuppie_all) fprintf(report, "\n");
                if (MCEDITOR_stop==1 || file_exists("stop.txt")) {
                    printf("Stop requested, exiting\n");
//                    system("/saves/copy_test.bat");
//                    send_message='x';
                    return 0;
                }
            }
        }
    }
    return 0;
}

void fok_floor(MCRegion &region, int height_add) {
}

int floor_second[512][512];
int one_block[512][512];

void get_floor(MCRegion &region, int height_add) {
//    FILE* result;
//    result=fopen("result.txt","w");

    int heights_global_ar[256];
    size_t blocks_total=0;
    for (int y = 0; y < 256; y++) heights_global_ar[y]=0;
    int min_y;

    BlockInfo*** AX=region.A;
    for (int x = 0; x < 512; x++) {
        BlockInfo** AZ=AX[x];
        for (int z = 0; z < 512; z++) {
            BlockInfo* AY=AZ[z];
            min_y=-1;
            one_block[x][z]=0;
            for (int y = 255; y >= height_add+2 ; y--) {
                if (AY[y].id!=0) {
                    min_y=y;
                    one_block[x][z]++;
                    blocks_total++;
                }
            }
            floor_y[x][z]=min_y;
            floor_second[x][z]=min_y;
            if (one_block[x][z]==1) heights_global_ar[min_y]++;
        }
    }
//    printf("loaded\n");
    int max_height=0;
    int max_height_y=0;
    for (int y=height_add+2; y<254; y++ ) {
        int h=heights_global_ar[y]+heights_global_ar[y-1]+heights_global_ar[y-2]+heights_global_ar[y+1]+heights_global_ar[y+2];
        if (h > max_height) {
            max_height=h;
            max_height_y=y;
        }
    }
    printf("max_y=%d h=%d\n",max_height_y,max_height);

    for (int z = 0; z < zl; z++) {
        for (int x = 0; x < xl; x++) {

            if (floor_y[x][z]>max_height_y-3) {
                floor_y[x][z]=max_height_y-3;
                if (floor_y[x][z]<height_add) floor_y[x][z]=height_add;
                floor_second[x][z]=floor_y[x][z];
            }

//                floor_y[x][z]=max_height;
//                floor_second[x][z]=floor_y[x][z];
        }
    }
//    return;
/*
    for (int z = 0; z < zl; z++) {
        for (int x = 0; x < xl; x++) {
            if (one_block[x][z]==-1)
                fprintf(result,"X");
            else {
                if (one_block[x][z]==0)
                    fprintf(result," ");
                else if (one_block[x][z]==1)
                    fprintf(result,".");
                else if (one_block[x][z]<=9)
                    fprintf(result,"%d",one_block[x][z]);
                else
                    fprintf(result,"*");
            }

//            printf("%3d ",floor_y[x][z]);
        }
        fprintf(result,"\n");
//        printf("\n");
    }
    fprintf(result,"\n");
*/

/*
    for (int y=0; y<256; y+=16) {
        int tot_row=0;
        for (int yy=0; yy<8; yy++) {
            int yyy=y+yy;
            tot_row+=heights_global_ar[yyy];
            heights_global_ar[yyy]=0;
            if (tot_row) printf("y=%3d num=%d\n",yyy,tot_row);
        }
    }
*/
    bool changed=true;
    while (changed==true) {
        int flored=0;
        changed=false;
        for (int x = 0; x < xl; x++) {
            for (int z = 0; z < zl; z++) {
                min_y=floor_y[x][z];
                int min_y2=min_y;
                if (one_block[x][z]>1) {
                    for (int xx = -1; xx < 2; xx++) {
                        for (int zz = -1; zz < 2; zz++) {
                            int xxx=x+xx;
                            int zzz=z+zz;
                            if (xxx>=0 && xxx<512 && zzz>=0 && zzz<512) {
                                if (one_block[xxx][zzz]==1) {
                                    if (floor_y[xxx][zzz]!=-1 || min_y==-1) {
                                        if ( min_y > floor_y[xxx][zzz] || min_y==-1) {
                                            if (floor_y[xxx][zzz] < min_y2) min_y2=floor_y[xxx][zzz];
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                if (min_y2>=0) {
                    floor_second[x][z]=min_y2;
    //                one_block[x][z]=1;
//                    heights_global_ar[min_y2]++;
                }
            }
        }
        for (int z = 0; z < zl; z++) {
            for (int x = 0; x < xl; x++) {
                if (floor_second[x][z]!=floor_y[x][z]) {
                    floor_y[x][z]=floor_second[x][z];
                    changed=true;
                    flored++;
//                    one_block[x][z]=1;
                } else one_block[x][z]=1;
            }
        }
  /*
        printf("flored=%d\n",flored);
        for (int y=0; y<256; y++) {
            int tot_row=heights_global_ar[y];
            if (tot_row) printf("y=%3d num=%d\n",y,tot_row);
            heights_global_ar[y]=0;
        }
*/
    }


/*
    printf("loaded\n");
    int max_height=0;
    int max_height_y=0;
    for (int y=height_add+3; y<254; y++ ) {
        int h=heights_global_ar[y]+heights_global_ar[y-1]+heights_global_ar[y-2]+heights_global_ar[y+1]+heights_global_ar[y+2];
        if (h > max_height) {
            max_height=h;
            max_height_y=y;
        }
    }
    printf("max_y=%d h=%d\n",max_height_y,max_height);
*/


/*
    for (int z = 0; z < zl; z++) {
        for (int x = 0; x < xl; x++) {
            min_y=floor_y[x][z];
            int diff=0;
            for (int xx = -1; xx < 2; xx++) {
                for (int zz = -1; zz < 2; zz++) {
                    int xxx=x+xx;
                    int zzz=z+zz;
                    if (xxx>=0 && xxx<512 && zzz>=0 && zzz<512) {
                        diff+=(abs(min_y-floor_y[xxx][zzz]));
                    }
                }
            }
            if (diff>9) {
                fprintf(result,"*");
//                printf("*");
            }
            else {

                fprintf(result,"%d",diff);
//                printf("%d",diff);
            }
        }
        fprintf(result,"\n");
//        printf("\n");
    }
    fprintf(result,"\n");
//    printf("\n");
    for (int z = 0; z < zl; z++) {
        for (int x = 0; x < xl; x++) {
            fprintf(result,"%3d ",floor_y[x][z]);
//            printf("%3d ",floor_y[x][z]);
        }
        fprintf(result,"\n");
//        printf("\n");
    }
    fprintf(result,"\n");
//    printf("\n");
    for (int z = 0; z < zl; z++) {
        for (int x = 0; x < xl; x++) {
            if (one_block[x][z]==-1)
                fprintf(result,"X");
            else {
                if (one_block[x][z]==0)
                    fprintf(result," ");
                else if (one_block[x][z]==1)
                    fprintf(result,".");
                else if (one_block[x][z]<=9)
                    fprintf(result,"%d",one_block[x][z]);
                else
                    fprintf(result,"*");
            }

//            printf("%3d ",floor_y[x][z]);
        }
        fprintf(result,"\n");
//        printf("\n");
    }

    fclose(result);
*/
}


