#include "MCA-NBT-EDIT.HPP"
#include "everything.hpp"


int bukkit_running=0;
sf::Color read_one_pixel(int x, int y);
int get_nearest(int x, int y);

int trans;
int t_diff;
extern void logfile(char *line);

char mobs[][50]={
    "bat",
    "blaze",
    "cat",
    "cave_spider",
//    "charged_creeper",
    "chicken",
    "cod",
    "cow",
//    "cow_with_name",
    "creeper",
    "dolphin",
    "donkey",
    "drowned",
    "elder_guardian",
//    "ender_dragon",
    "end_crystal",
    "enderman",
    "endermite",
    "evoker",
    "fox",
//    "ghast",
//    "giant_slime",
//    "giant_zombie",
    "guardian",
    "horse",
//    "horse_with_armor",
    "husk",
    "illusioner",
    "iron_golem",
//    "killer_bunny",
//    "lightning_bolt",
    "llama",
//    "magma_cube",
    "mooshroom",
    "mule",
    "ocelot",
    "panda",
    "parrot",
    "phantom",
    "pig",
//    "pig_with_saddle",
    "pillager",
    "polar_bear",
    "pufferfish",
    "rabbit",
    "ravager",
    "salmon",
    "sheep",
    "shulker",
    "shulker_bullet",
    "silverfish",
    "skeleton",
    "skeleton_horse",
//    "skeleton_trap",
    "slime",
//    "snow_man",
    "spider",
    "squid",
    "stray",
//    "tame_horse",
//    "tame_ocelot",
//    "tame_wolf",
    "trader_llama",
    "tropical_fish",
    "turtle",
    "vex",
    "villager",
    "vindicator",
    "wandering_trader",
    "witch",
//    "wither_boss",
    "wither_skeleton",
    "wolf",
    "zombie",
    "zombie_horse",
    "zombie_pigman",
    "zombie_villager"
};
// order false!!!!! (list_rgb)
// palette order... now.
char color_list_glass[][50]={
    "magenta_stained_glass",
    "pink_stained_glass",
    "red_stained_glass",
    "orange_stained_glass",
    "yellow_stained_glass",
    "lime_stained_glass",
    "green_stained_glass",
    "cyan_stained_glass",
    "light_blue_stained_glass",
    "blue_stained_glass",
    "purple_stained_glass",
    "brown_stained_glass",
    "light_gray_stained_glass",
    "gray_stained_glass",
    "black_stained_glass",
    "white_stained_glass",
    "glass"
};

char color_list_wool[][50]={
    "white_wool",
    "orange_wool",
    "magenta_wool",
    "light_blue_wool",
    "yellow_wool",
    "lime_wool",
    "pink_wool",
    "gray_wool",
    "light_gray_wool",
    "cyan_wool",
    "purple_wool",
    "blue_wool",
    "brown_wool",
    "green_wool",
    "red_wool",
    "black_wool",
    ""
};

int color_list_rgb[][3]={
    {0xF9,0xFF,0xFE},
    {0xF9,0x80,0x1D},
    {0xC7,0x4E,0xBD},
    {0x3A,0xB3,0xDA},
    {0xFE,0xD8,0x3D},
    {0x80,0xC7,0x1F},
    {0xF3,0x8B,0xAA},
    {0x47,0x4F,0x52},
    {0x9D,0x9D,0x97},
    {0x16,0x9C,0x9C},
    {0x89,0x32,0xB8},
    {0x3C,0x44,0xAA},
    {0x83,0x54,0x32},
    {0x5E,0x7C,0x16},
    {0xB0,0x2E,0x26},
    {0x1D,0x1D,0x21},
    {0xFF,0xFF,0xFF}
};

extern sf::Mutex loader_mutex;


int first_buk=1;


void bukkit_thread_server() {
    char later[500][500];
    static int later_start=0;
    static int later_end=0;
    int start_blockx;
    int start_blocky;
    int end_blockx;
    int end_blocky;
    int size_block=8;
    int size_block1x;
    int size_block1y;
    int size_block2x;
    int size_block2y;
    int n;
    FILE * pfile;
    FILE * ffile;
    int hit=0;

    int px=0,py=0;
    int sx=0,sy=0;
    int ssx=0,ssy=0;

    static int y=100;
    static int x=0;
    static int z=0;      //minecraft block....

    int totx=x;
    int toty=y;


//    static int y=2;
//    static int x=0;
//    static int z=0;      //minecraft block....

    px=x/1920;
    sx=(x-px*1920)/16;
    ssx=(x-px*1920-sx*16);
    py=z/1080;
    sy=(z-py*1080)/9;
    ssy=(z-py*1080-sy*9);

    size_block1x=sin(    x/(30+sin(    z/22)*5))*18 + sin(    z/(33.123+sin(    x/19)*12))*10;
    size_block2x=sin((x+1)/(30+sin((z+1)/22)*5))*18 + sin((z+1)/(33.123+sin((x+1)/19)*12))*10;

    size_block1y=sin(    x/(32+sin(    z/21)*6))*14 + sin(    z/(37.123+sin(    x/17)*10))*10;
    size_block2y=sin((x+1)/(32+sin((z+1)/21)*6))*14 + sin((z+1)/(37.123+sin((x+1)/17)*10))*10;

    start_blockx=x*size_block+size_block1x-1;
    end_blockx  =(x+1)*size_block+size_block2x;

    start_blocky=z*size_block+size_block1y-1;
    end_blocky  =(z+1)*size_block+size_block2y;


    printf("start\r");
    printf("block=(%6d,%6d) pixel_tot=(%5d,%5d) bitmap=(%d,%d) -> maze=(%2d,%2d) -> pixel(%2d,%2d))\n", start_blockx,start_blocky, x,z, px,py, sx,sy, ssx,ssy);

    if (pfile=popen("mcrcon -t -c -H 127.0.0.1 -P 25575 -p hoppa >nul","w") ) {
        int dir;
        char com[1000];
        srand(time(0));

        if (!(ffile=fopen("E:/MODDING/SERVER/INPUT.TXT","w") ) ) {
            printf("Error writing to E:/MODDING/SERVER/INPUT.TXT\n");
            strcpy(error_msg2,"Error writing to E:/MODDING/SERVER/INPUT.TXT");
            error_flag2=1;
            return;
        }
        sprintf(com,"execute at @p run tp @p %d ~ %d",start_blockx-20,start_blocky +(int)(4.5*size_block));
//        printf("Teleporting (%6d,~,%6d)...",(px*1920+sx*16+ssx+10)*size_block,(py*1080+sy*9+9)*size_block);
        fprintf(ffile,"%s\n",com);

        sprintf(com,"gamerule maxEntityCramming 1000");
        fprintf(ffile,"%s\n",com);

        sprintf(com,"gamerule mobGriefing false");
        fprintf(ffile,"%s\n",com);

        sprintf(com,"execute as @e[nbt=!{ExplosionRadius:0}] run data merge entity @s {ExplosionRadius:0}");
        fprintf(ffile,"%s\n",com);

        fclose(ffile);
        printf("flushing...SENDING 'maze' COMMAND\r");
        fprintf(pfile,"maze\n");
        fflush(pfile);
        printf("                                                                                                                                      \r");
        printf("waiting 10.0 second(s) for teleport");  for (int i=0; i<100; i++) {  kiki(); sf::sleep(sf::seconds(.1)); printf("."); } printf("\r");
        while ( ESCAPE_PRESSED==0 && file_exists("E:/MODDING/SERVER/INPUT.TXT")) {
            printf("                                                                                                                                      \r");
            printf("Waiting for deletion file... \r");
            printf("                                                                                                                                      \r");
            printf("waiting 1.0 second(s) for testing again");  for (int i=0; i<10; i++) {  kiki(); sf::sleep(sf::seconds(.1)); printf("."); } printf("\r");
        }
        if (!(ffile=fopen("E:/MODDING/SERVER/INPUT.TXT","w") ) ) {
            printf("Error writing to E:/MODDING/SERVER/INPUT.TXT\n");
            strcpy(error_msg2,"Error writing to E:/MODDING/SERVER/INPUT.TXT");
            error_flag2=1;
            return;
        }
        printf("                                                                                                                            \r");
        printf("File deleted. Waiting 5.0 second(s) for producing first batch");  for (int i=0; i<50; i++) {  kiki(); sf::sleep(sf::seconds(.1)); printf("."); } printf("\r");
        printf("                                                                                                                            \r");
        printf("Producing first batch... \r");

//        sprintf(com,"effect give @a minecraft:mining_fatigue 1000000 5");
//        fprintf(ffile,"%s\n",com);

//        printf("waiting 10 second(s) for teleport");  for (int i=0; i<20; i++) { sf::sleep(sf::seconds(.5)); kiki(); printf("."); } printf("\n");

        int summon;
        float p;
        p=1;
        float totx;
        float toty;
        int n;
        int y2;
        int tot_startx=0;
        int tot_starty=0;
        int tot_count=0;
        int zz=9*2;
        int xx=0;
        int first=1;
        int h;
        while (bukkit_running==1 && ESCAPE_PRESSED==0) {
/*

            if (first==0) {
                xx++;if (x>3) {
                    xx=0;
                    zz++;
                    if (zz>9*9) return;
                }
            }
            px=xx/1920;
            sx=(xx-px*1920)/16;
            ssx=(xx-px*1920-sx*16);
            py=zz/1080;
            sy=(zz-py*1080)/9;
            ssy=(zz-py*1080-sy*9);


            if (first==1) first=0;

*/
            summon=0;

            x=(px*1920+sx*16+ssx);
            z=(py*1080+sy*9+ssy);
            n=get_nearest(x,z);
            sf::Color hcol=read_one_pixel(x+1920,z);             unsigned int h=hcol.toInteger();
            sf::Color hcolr=read_one_pixel(x+1920+1,z);          unsigned int hx_plus=hcolr.toInteger();
            sf::Color hcoll=read_one_pixel(x+1920-1,z);          unsigned int hx_min=hcoll.toInteger();
            sf::Color hcolu=read_one_pixel(x+1920,z+1);          unsigned int hz_plus=hcolu.toInteger();
            sf::Color hcold=read_one_pixel(x+1920,z-1);          unsigned int hz_min=hcold.toInteger();
            int dx=hx_plus-hx_min;
            int dz=hz_plus-hz_min;
            int change_block=(  (int) ( 0.20 * (sin((double)dx/pow(2.0,18.0)) + cos((double)dx/pow(2.0,18.0)))+0.5 )*sizeof(color_list_wool )   )%sizeof(color_list_wool);
            change_block=(change_block+sizeof(color_list_wool))%sizeof(color_list_wool);

            totx=x*4;
            toty=z*4;
            h=h>>25;
            y=10+h/3+(int)(0.10*(71.0+sin(totx/10)+sin(totx/95.4)*20+sin(toty/14.234)+sin(toty/84.3211)*20+sin(totx/33.4+toty/27.3244)*10+
            sin(totx/17)+sin(totx/144.4)*16+sin(toty/17.234)+sin(toty/166.3211)*16+sin(totx/38.4+toty/57.3244)*10));
            y2=h*2/3+(int)abs(0.3*(sin(totx/17)*5+sin(totx/32.4)*10+sin(toty/11.234)*5+sin(toty/34.3211)*10+sin(totx/13.4+toty/21.3244)*2+
            sin(totx/15)*5+sin(totx/24.4)*16+sin(toty/13.234)*5+sin(toty/36.3211)*16+sin(totx/28.4+toty/57.3244)*2))+rand()%5;

//            size_block1x=sin(    x/(30+sin(    z/22)*5))*18 + sin(    z/(33.123+sin(    x/19)*12))*10;
//            size_block2x=sin((x+1)/(30+sin((z+1)/22)*5))*18 + sin((z+1)/(33.123+sin((x+1)/19)*12))*10;
//            size_block1y=sin(    x/(32+sin(    z/21)*6))*14 + sin(    z/(37.123+sin(    x/17)*10))*10;
//            size_block2y=sin((x+1)/(32+sin((z+1)/21)*6))*14 + sin((z+1)/(37.123+sin((x+1)/17)*10))*10;

            start_blockx=x*size_block;  +size_block1x-1;
            end_blockx  =(x+1)*size_block;  +size_block2x;

            start_blocky=z*size_block;  +size_block1y-1;
            end_blocky  =(z+1)*size_block;  +size_block2y;

            tot_startx+=start_blockx;
            tot_starty+=start_blocky;

            tot_count++;

            if (trans>240) {
                if (t_diff>(int)(256*3/2)) {

                    sprintf(com,"fill %d %d %d %d %d %d %s replace",
                                start_blockx-1,   y-1,                      start_blocky+1,
                                end_blockx-1,     y-4,                      end_blocky+1,
//                            change_block);
                            "chiseled_quartz_block");
                    fprintf(ffile,"%s\n",com);

                    if (rand()%6) {
                        sprintf(com,"fill %d %d %d %d %d %d %s replace",
                                start_blockx,   y,                      start_blocky,
                                end_blockx,     y+size_block+1+y2,      end_blocky,
                                color_list_wool[change_block]);
//                                "bricks");
                    } else {
                        int hmmm=(int)( sin( (px*1920+sx*16+ssx)/15 )*16 + sin( (py*1080+sy*9+ssy)/19.55 )*14 + 10000 )%16;
                        sprintf(com,"fill %d %d %d %d %d %d %s hollow",
                                start_blockx,   y,                      start_blocky,
                                end_blockx,     y+size_block+1+y2,      end_blocky,
                                color_list_glass[hmmm]);
                        summon=1;
                    }
                    fprintf(ffile,"%s\n",com);
                } else {
                    sprintf(com,"fill %d %d %d %d %d %d %s replace",
                                start_blockx-3,   y-1,                      start_blocky-3,
                                end_blockx+3,     y-4,                      end_blocky+3,
                            "chiseled_quartz_block");
                    fprintf(ffile,"%s\n",com);
                    sprintf(com,"setblock %d %d %d %s replace",
                            (int)((start_blockx+end_blockx)/2),  y  ,
                            (int)((start_blocky+end_blocky)/2),
                            "yellow_carpet");
                    fprintf(ffile,"%s\n",com);
//                    sprintf(com,"setblock %d %d %d %s replace",px*1920+sx*16*2+ssx,y,py*1080+sy*9*3+ssy,color_list_wool[n]);
                }

//                printf("Sending command: %s -> ",com);
                if (summon==1) {
                    sprintf(com,"setblock %d %d %d %s replace",
                            (int)((start_blockx+end_blockx)/2), y+size_block+2+y2,
                            (int)((start_blocky+end_blocky)/2),
                            "torch");
                    fprintf(ffile,"%s\n",com);
                    sprintf(com,"fill %d %d %d %d %d %d %s replace",
                                start_blockx-1,   y-2,                      start_blocky-1,
                                end_blockx+1,     y,                      end_blocky+1,
                            "chiseled_quartz_block");
                    fprintf(ffile,"%s\n",com);
                    if (rand()%1) {
                        sprintf(com,"summon %s %d %d %d",
                        mobs[rand()%60],start_blockx+2,  y+1 ,start_blocky+2);
                        strcpy(later[later_end%500],com);later_end++; //fprintf(ffile,"%s\n",com);
                        sprintf(com,"summon %s %d %d %d",
                        mobs[rand()%60],end_blockx-3,  y+1 ,end_blocky-3);
                        strcpy(later[later_end%500],com);later_end++; //fprintf(ffile,"%s\n",com);
//                        printf("%s\n",com);
                    } else {
                        sprintf(com,"summon %s %d %d %d",
                        mobs[rand()%60],start_blockx+2,  y+1 ,start_blocky+2);
                        strcpy(later[later_end%500],com);later_end++; //fprintf(ffile,"%s\n",com);
                        sprintf(com,"summon %s %d %d %d",
                        mobs[rand()%60],end_blockx-3,  y+1 ,end_blocky-3);
                        strcpy(later[later_end%500],com);later_end++; //fprintf(ffile,"%s\n",com);
                        sprintf(com,"summon %s %d %d %d",
                        mobs[rand()%60],start_blockx+3,  y+2 ,start_blocky+ 2);
                        strcpy(later[later_end%500],com);later_end++; //fprintf(ffile,"%s\n",com);
                        sprintf(com,"summon %s %d %d %d",
                        mobs[rand()%60],end_blockx-3,  y+1 ,end_blocky-3);
                        strcpy(later[later_end%500],com);later_end++; //fprintf(ffile,"%s\n",com);
                        sprintf(com,"summon %s %d %d %d",
                        mobs[rand()%60],start_blockx+1,  y+4 ,start_blocky+2);
                        strcpy(later[later_end%500],com);later_end++; //fprintf(ffile,"%s\n",com);
                        sprintf(com,"summon %s %d %d %d",
                        mobs[rand()%60],end_blockx-3,  y+3 ,end_blocky-3);
                        strcpy(later[later_end%500],com);later_end++; //fprintf(ffile,"%s\n",com);
                        if (rand()%1000) {
                            sprintf(com,"summon %s %d %d %d",
                            mobs[rand()%60],start_blockx+2+1,  y+1 ,start_blocky+2+1);
                            strcpy(later[later_end%500],com);later_end++; //fprintf(ffile,"%s\n",com);
                            sprintf(com,"summon %s %d %d %d",
                            mobs[rand()%60],end_blockx-3-1,  y+1 ,end_blocky-3-1);
                            strcpy(later[later_end%500],com);later_end++; //fprintf(ffile,"%s\n",com);
                            sprintf(com,"summon %s %d %d %d",
                            mobs[rand()%60],start_blockx+3,  y+3 ,start_blocky+3);
                            strcpy(later[later_end%500],com);later_end++; //fprintf(ffile,"%s\n",com);
                            sprintf(com,"summon %s %d %d %d",
                            mobs[rand()%60],end_blockx-3,  y+3 ,end_blocky-3);
                            strcpy(later[later_end%500],com);later_end++; //fprintf(ffile,"%s\n",com);
                            if (rand()%1000) {
                                sprintf(com,"summon %s %d %d %d",
                                mobs[rand()%63],start_blockx+1,  y+1 ,start_blocky+2);
                                strcpy(later[later_end%500],com);later_end++; //fprintf(pfile,"%s\n",com);
                                sprintf(com,"summon %s %d %d %d",
                                mobs[rand()%63],end_blockx-2,  y+1 ,end_blocky-3);
                                strcpy(later[later_end%500],com);later_end++; //fprintf(pfile,"%s\n",com);
                                sprintf(com,"summon %s %d %d %d",
                                mobs[rand()%63],start_blockx+1,  y+3 ,start_blocky+2);
                                strcpy(later[later_end%500],com);later_end++; //fprintf(pfile,"%s\n",com);
                                sprintf(com,"summon %s %d %d %d",
                                mobs[rand()%63],end_blockx-3,  y+3 ,end_blocky-3);
                                strcpy(later[later_end%500],com);later_end++; //fprintf(ffile,"%s\n",com);
                                if (rand()%1000) {
                                    sprintf(com,"summon %s %d %d %d",
                                    mobs[rand()%60],start_blockx+3,  y+1 ,start_blocky+2);
                                    strcpy(later[later_end%500],com);later_end++; //fprintf(ffile,"%s\n",com);
                                    sprintf(com,"summon %s %d %d %d",
                                    mobs[rand()%60],end_blockx-3,  y+1 ,end_blocky-4);
                                    strcpy(later[later_end%500],com);later_end++; //fprintf(ffile,"%s\n",com);
                                    sprintf(com,"summon %s %d %d %d",
                                    mobs[rand()%60],start_blockx+3,  y+3 ,start_blocky+2);
                                    strcpy(later[later_end%500],com);later_end++; //fprintf(ffile,"%s\n",com);
                                    sprintf(com,"summon %s %d %d %d",
                                    mobs[rand()%60],end_blockx-3,  y+3 ,end_blocky-3);
                                    strcpy(later[later_end%500],com);later_end++; //fprintf(ffile,"%s\n",com);
                                    if (rand()%1000) {
                                        sprintf(com,"summon %s %d %d %d",
                                        mobs[rand()%60],start_blockx+3,  y+2 ,end_blocky+3);
                                        strcpy(later[later_end%500],com);later_end++; //fprintf(ffile,"%s\n",com);
                                        sprintf(com,"summon %s %d %d %d",
                                        mobs[rand()%60],end_blockx-3,  y+2 ,end_blocky-3);
                                        strcpy(later[later_end%500],com);later_end++; //fprintf(ffile,"%s\n",com);
                                        sprintf(com,"summon %s %d %d %d",
                                        mobs[rand()%60],start_blockx+2,  y+3 ,end_blocky+2);
                                        strcpy(later[later_end%500],com);later_end++; //fprintf(ffile,"%s\n",com);
                                        sprintf(com,"summon %s %d %d %d",
                                        mobs[rand()%60],end_blockx-3,  y+3 ,end_blocky-3);
                                        strcpy(later[later_end%500],com);later_end++; //fprintf(ffile,"%s\n",com);
                                    }
                                }
                            }
                        }
                    }
                }
                kiki();
            } else if (trans>10) {
                    sprintf(com,"fill %d %d %d %d %d %d %s replace",
                            start_blockx,  y  ,start_blocky,
                            end_blockx,y  ,end_blocky,color_list_glass[n]);
                fprintf(ffile,"%s\n",com);//fflush(pfile);
                kiki();
                printf(".");
            } else {}
            while ((later_end-later_start)>40) {
                fprintf(ffile,"%s\n",later[later_start%500]);
                later_start++;
            }
            if (later_start>500 && later_end>500) {
                later_start=later_start%500;
                later_end=later_end%500;
            }
            int flip_sx=0;
            ssy=ssy+1;
            int start_again=0;
            if (ssy==9) {
                loader_mutex.lock();
                monitor_off=1;
                loader_mutex.unlock();
                ssy=0;
                ssx=ssx+1;
                if (ssx==16) {
                    ssx=0;
                    sx=sx+1;
                    if (sx==120) {
                        flip_sx=1;
                        sx=0;
                        sy=sy+1;
                        if (sy==120) {
                            sy=0;
                            bukkit_running=0;
                            px=px+1;
                            if (px==totalpicturex) {
                                px=0;
                                py=py+1;
                                if (py==totalpicturey) {
                                    py=0;
                                    bukkit_running=0;
                                }
                            }
                        }
                    }
                }
                printf("\r");
                printf("                                                                                                                            \r");
//                fflush(pfile);
                hit++;

                if (hit==4 || flip_sx==1) {
                    tot_startx=tot_startx/tot_count;
                    tot_starty=tot_starty/tot_count;
                    tot_count=0;
                    if (flip_sx==1) {
                        if (flip_sx==1) {
                            printf("Waiting 20.0 extra second(s) for teleport (long jump)");  for (int i=0; i<20; i++) {  kiki(); sf::sleep(sf::seconds(1)); printf("."); } printf("\r");
                        }
                        x=(px*1920+sx*16+ssx);
                        z=(py*1080+sy*9+ssy);
                        sprintf(com,"execute at @p run tp @p %d ~ %d",x,z*size_block+size_block/2);
                    }
                    else
                        sprintf(com,"execute at @p run tp @p %d ~ %d",tot_startx,tot_starty);
                    fprintf(ffile,"%s\n",com);
                    tot_startx=0;
                    tot_startx=0;
                    hit=0;
//                    printf("Teleporting (%6d,~,%6d)...",(px*1920+sx*16+ssx)*size_block,(py*1080+sy*9+4)*size_block);
                    fclose(ffile);
                    printf("                                                                                                                              \r");
                    printf("SENDING 'maze' COMMAND....");
                    fprintf(pfile,"maze\n");
                    printf("Flushing...\r");
                    fflush(pfile);
                    printf("                                                                                                                                      \r");
                    printf("Waiting 2.0 second(s) for teleport");  for (int i=0; i<20; i++) {  kiki(); sf::sleep(sf::seconds(.1)); printf("."); } printf("\r");
                    if (flip_sx==1) {
                        printf("Waiting 10.0 extra second(s) for teleport (long jump)");  for (int i=0; i<10; i++) {  kiki(); sf::sleep(sf::seconds(1)); printf("."); } printf("\r");
                    }
                    if (p>0) p=p-0.02;
                    if (p>1)  {
                            printf("                                                                                                                                      \r");
                            printf("Waiting extra %d seconds...",(int)p);
                            for (int i=0; i<(int)p*5; i++) {  kiki(); sf::sleep(sf::seconds(.2)); printf("."); } printf("\r");
                    }
                    while ( ESCAPE_PRESSED==0 && file_exists("E:/MODDING/SERVER/INPUT.TXT")) {
                        p=p+0.5;
                        printf("                                                                                                                                      \r");
                        printf("Waiting for deletion file... Waiting 10.0 second(s) for testing again");  for (int i=0; i<50; i++) {  kiki(); sf::sleep(sf::seconds(.2)); printf("."); } printf("\r");
                        if (!file_exists("E:/MODDING/SERVER/INPUT.TXT")) {
                            sprintf(com,"Wait value minecraft mcrcon on file_exists()=%d",(int)p);
                            logfile(com);
                        }
//                        return;
                    }
                    if (!(ffile=fopen("E:/MODDING/SERVER/INPUT.TXT","w") ) ) {
                        printf("Error writing to E:/MODDING/SERVER/INPUT.TXT\n");
                        strcpy(error_msg2,"Error writing to E:/MODDING/SERVER/INPUT.TXT");
                        error_flag2=1;
                        return;
                    }
                    printf("                                                                                                                                      \r");
                    printf("File deleted. Waiting 2.0 second(s) for producing next batch");  for (int i=0; i<20; i++) {  kiki(); sf::sleep(sf::seconds(.1)); printf("."); }
                    printf("Producing next batch... \r");
                }
                kiki();
            }
            x=(px*1920+sx*16+ssx);
            z=(py*1080+sy*9+ssy);
            printf("\n");
            CONSOLE_SCREEN_BUFFER_INFO coninfo;
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            GetConsoleScreenBufferInfo(hConsole, &coninfo);
            coninfo.dwCursorPosition.Y -= 2;
            coninfo.dwCursorPosition.X = 0;
            SetConsoleCursorPosition(hConsole, coninfo.dwCursorPosition);
            printf("block=(%6d,%6d) pixel_tot=(%5d,%5d) bitmap=(%d,%d) -> maze=(%2d,%2d) -> pixel(%2d,%2d))\n", start_blockx,start_blocky, x,z, px,py, sx,sy, ssx,ssy);
            kiki();
            monitor_off=1;
        }

        fprintf(pfile,"Q\n");
        pclose(pfile);
        fclose(ffile);
        x=(px*1920+sx*16+ssx);
        z=(py*1080+sy*9+ssy);
        printf("block=(%6d,%6d) pixel_tot=(%5d,%5d) bitmap=(%d,%d) -> maze=(%2d,%2d) -> pixel(%2d,%2d))\n", start_blockx,start_blocky, x,z, px,py, sx,sy, ssx,ssy);
        if (ESCAPE_PRESSED) {
            ESCAPE_PRESSED=0;
            printf("Escape pressed....stop\n");
        }
        printf("Exiting...\n");
    } else {
        printf("Error opening: mcrcon -t -c -H 127.0.0.1 -P 25575 -p hoppa >nul\n");
        strcpy(error_msg2,"Error opening: mcrcon -t -c -H 127.0.0.1 -P 25575 -p hoppa >nul");
        error_flag2=1;
    }
}


void bukkit_thread_server_v_1_0() {
    int size_block=11;
    int n;
    FILE * pfile;
    int hit=0;

    int px=0,py=0;
    int sx=0,sy=0;
    int ssx=0,ssy=0;


//    static int y=241;
//    static int x=2224/size_block;
//    static int z=204/size_block;      //minecraft block....

    static int y=241;
    static int x=1042;
    static int z=9;      //minecraft block....

    px=x/1920;
    sx=(x-px*1920)/16;
    ssx=(x-px*1920-sx*16);

    py=z/1080;
    sy=(z-py*1080)/18;
    ssy=(z-py*1080-sy*18);

    printf("start\n");
    printf("block=(%6d,%6d) pixel_tot=(%5d,%5d) bitmap=(%d,%d) -> maze=(%2d,%2d) -> pixel(%2d,%2d))\n", x*size_block,z*size_block, x,z, px,py, sx,sy, ssx,ssy);

    if (pfile=popen("mcrcon -t -c -H 127.0.0.1 -P 25575 -p hoppa >nul","w") ) {
        int dir;
        char com[1000];
        srand(time(0));

        sprintf(com,"tp @p %d %d %d",(px*1920+sx*16+ssx)*size_block,300,(py*1080+sy*18+9)*size_block);
        fprintf(pfile,"%s\n",com);
//        fflush(pfile);

        sprintf(com,"gamerule maxEntityCramming 1000");
        fprintf(pfile,"%s\n",com);
//        fflush(pfile);

        sprintf(com,"gamerule mobGriefing false");
        fprintf(pfile,"%s\n",com);
        fflush(pfile);

        sprintf(com,"execute as @e[nbt=!{ExplosionRadius:0}] run data merge entity @s {ExplosionRadius:0}");
        fprintf(pfile,"%s\n",com);
        fflush(pfile);

        sprintf(com,"effect give @a minecraft:mining_fatigue 1000000 5");
        fprintf(pfile,"%s\n",com);
        fflush(pfile);

        printf("waiting 10 second(s) for teleport");  for (int i=0; i<20; i++) { sf::sleep(sf::seconds(.5)); kiki(); printf("."); } printf("\n");

        int summon;
        while (bukkit_running==1 && ESCAPE_PRESSED==0) {
            summon=0;
            int n=get_nearest(px*1920+sx*16+ssx,py*1080+sy*18+ssy);
            if (trans>240) {
                if (t_diff>(int)(256*3/2)) {
                    if (rand()%10) {
                        sprintf(com,"fill %d %d %d %d %d %d %s replace",
                                (px*1920+sx*16+ssx)*size_block,  y  ,(py*1080+sy*18+ssy)*size_block,
                                (px*1920+sx*16+ssx)*size_block+(size_block-1),y+size_block+1,(py*1080+sy*18+ssy)*size_block+(size_block-1),"bricks");
                    } else {
                        int hmmm=(int)( sin( (px*1920+sx*16+ssx)/15 )*16 + sin( (py*1080+sy*18+ssy)/19.55 )*14 + 10000 )%16;
                        sprintf(com,"fill %d %d %d %d %d %d %s hollow",
                                (px*1920+sx*16+ssx)*size_block,  y  ,(py*1080+sy*18+ssy)*size_block,
                                (px*1920+sx*16+ssx)*size_block+(size_block-1),y+size_block+1,(py*1080+sy*18+ssy)*size_block+(size_block-1),color_list_glass[hmmm]);
                        summon=1;
                        fflush(pfile);
                        sf::sleep(sf::seconds(0.1));
                    }
                    fprintf(pfile,"%s\n",com);
                } else {
                    sprintf(com,"setblock %d %d %d %s replace",(px*1920+sx*16+ssx)*size_block+(int)(size_block/2),  y+2  ,(py*1080+sy*18+ssy)*size_block+(int)(size_block/2),"yellow_carpet");
                    fprintf(pfile,"%s\n",com);
                    sprintf(com,"fill %d %d %d %d %d %d %s replace",
                            (px*1920+sx*16+ssx)*size_block,  y  ,(py*1080+sy*18+ssy)*size_block,
                            (px*1920+sx*16+ssx)*size_block+(size_block-1),y  ,(py*1080+sy*18+ssy)*size_block+(size_block-1),"chiseled_quartz_block");
                    fprintf(pfile,"%s\n",com);
//                    sprintf(com,"setblock %d %d %d %s replace",px*1920+sx*16*2+ssx,y,py*1080+sy*18*3+ssy,color_list_wool[n]);
                }

//                printf("Sending command: %s -> ",com);
                if (summon==1) {
                    if (rand()%1) {
                        sprintf(com,"summon %s %d %d %d",
                        mobs[rand()%60],(px*1920+sx*16+ssx)*size_block+2,  y+1 ,(py*1080+sy*18+ssy)*size_block+2);
                        fprintf(pfile,"%s\n",com);
                        sprintf(com,"summon %s %d %d %d",
                        mobs[rand()%60],(px*1920+sx*16+ssx)*size_block+size_block-3,  y+1 ,(py*1080+sy*18+ssy)*size_block+size_block-3);
                        fprintf(pfile,"%s\n",com);
//                        printf("%s\n",com);
                    } else {
                        sprintf(com,"summon %s %d %d %d",
                        mobs[rand()%60],(px*1920+sx*16+ssx)*size_block+3,  y+2 ,(py*1080+sy*18+ssy)*size_block+ 2);
                        fprintf(pfile,"%s\n",com);
                        sprintf(com,"summon %s %d %d %d",
                        mobs[rand()%60],(px*1920+sx*16+ssx)*size_block+size_block-3,  y+1 ,(py*1080+sy*18+ssy)*size_block+size_block-3);
                        fprintf(pfile,"%s\n",com);
                        sprintf(com,"summon %s %d %d %d",
                        mobs[rand()%60],(px*1920+sx*16+ssx)*size_block+1,  y+4 ,(py*1080+sy*18+ssy)*size_block+2);
                        fprintf(pfile,"%s\n",com);
                        sprintf(com,"summon %s %d %d %d",
                        mobs[rand()%60],(px*1920+sx*16+ssx)*size_block+size_block-3,  y+3 ,(py*1080+sy*18+ssy)*size_block+size_block-3);
                        fprintf(pfile,"%s\n",com);
                        if (rand()%1000) {
                            sprintf(com,"summon %s %d %d %d",
                            mobs[rand()%60],(px*1920+sx*16+ssx)*size_block+2+1,  y+1 ,(py*1080+sy*18+ssy)*size_block+2+1);
                            fprintf(pfile,"%s\n",com);
                            sprintf(com,"summon %s %d %d %d",
                            mobs[rand()%60],(px*1920+sx*16+ssx)*size_block+size_block-3-1,  y+1 ,(py*1080+sy*18+ssy)*size_block+size_block-3-1);
                            fprintf(pfile,"%s\n",com);
                            sprintf(com,"summon %s %d %d %d",
                            mobs[rand()%60],(px*1920+sx*16+ssx)*size_block+3,  y+3 ,(py*1080+sy*18+ssy)*size_block+3);
                            fprintf(pfile,"%s\n",com);
                            sprintf(com,"summon %s %d %d %d",
                            mobs[rand()%60],(px*1920+sx*16+ssx)*size_block+size_block-3,  y+3 ,(py*1080+sy*18+ssy)*size_block+size_block-3);
                            fprintf(pfile,"%s\n",com);
                            if (rand()%1000) {
                                sprintf(com,"summon %s %d %d %d",
                                mobs[rand()%63],(px*1920+sx*16+ssx)*size_block+1,  y+1 ,(py*1080+sy*18+ssy)*size_block+2);
                                fprintf(pfile,"%s\n",com);
                                sprintf(com,"summon %s %d %d %d",
                                mobs[rand()%63],(px*1920+sx*16+ssx)*size_block+size_block-2,  y+1 ,(py*1080+sy*18+ssy)*size_block+size_block-3);
                                fprintf(pfile,"%s\n",com);
                                sprintf(com,"summon %s %d %d %d",
                                mobs[rand()%63],(px*1920+sx*16+ssx)*size_block+1,  y+3 ,(py*1080+sy*18+ssy)*size_block+2);
                                fprintf(pfile,"%s\n",com);
                                sprintf(com,"summon %s %d %d %d",
                                mobs[rand()%63],(px*1920+sx*16+ssx)*size_block+size_block-3,  y+3 ,(py*1080+sy*18+ssy)*size_block+size_block-3);
                                fprintf(pfile,"%s\n",com);
                                if (rand()%1000) {
                                    sprintf(com,"summon %s %d %d %d",
                                    mobs[rand()%60],(px*1920+sx*16+ssx)*size_block+3,  y+1 ,(py*1080+sy*18+ssy)*size_block+2);
                                    fprintf(pfile,"%s\n",com);
                                    sprintf(com,"summon %s %d %d %d",
                                    mobs[rand()%60],(px*1920+sx*16+ssx)*size_block+size_block-3,  y+1 ,(py*1080+sy*18+ssy)*size_block+size_block-4);
                                    fprintf(pfile,"%s\n",com);
                                    sprintf(com,"summon %s %d %d %d",
                                    mobs[rand()%60],(px*1920+sx*16+ssx)*size_block+3,  y+3 ,(py*1080+sy*18+ssy)*size_block+2);
                                    fprintf(pfile,"%s\n",com);
                                    sprintf(com,"summon %s %d %d %d",
                                    mobs[rand()%60],(px*1920+sx*16+ssx)*size_block+size_block-3,  y+3 ,(py*1080+sy*18+ssy)*size_block+size_block-3);
                                    fprintf(pfile,"%s\n",com);
                                    if (rand()%1000) {
                                        sprintf(com,"summon %s %d %d %d",
                                        mobs[rand()%60],(px*1920+sx*16+ssx)*size_block+3,  y+2 ,(py*1080+sy*18+ssy)*size_block+3);
                                        fprintf(pfile,"%s\n",com);
                                        sprintf(com,"summon %s %d %d %d",
                                        mobs[rand()%60],(px*1920+sx*16+ssx)*size_block+size_block-3,  y+2 ,(py*1080+sy*18+ssy)*size_block+size_block-3);
                                        fprintf(pfile,"%s\n",com);
                                        sprintf(com,"summon %s %d %d %d",
                                        mobs[rand()%60],(px*1920+sx*16+ssx)*size_block+2,  y+3 ,(py*1080+sy*18+ssy)*size_block+2);
                                        fprintf(pfile,"%s\n",com);
                                        sprintf(com,"summon %s %d %d %d",
                                        mobs[rand()%60],(px*1920+sx*16+ssx)*size_block+size_block-3,  y+3 ,(py*1080+sy*18+ssy)*size_block+size_block-3);
                                        fprintf(pfile,"%s\n",com);
                                    }
                                }
                            }
                        }
                    }
                }
                kiki();
                fflush(pfile);
                sf::sleep(sf::seconds(0.1));
//                printf("*");
            } else if (trans>10) {
                    sprintf(com,"fill %d %d %d %d %d %d %s replace",
                            (px*1920+sx*16+ssx)*size_block,  y  ,(py*1080+sy*18+ssy)*size_block,
                            (px*1920+sx*16+ssx)*size_block+(size_block-1),y  ,(py*1080+sy*18+ssy)*size_block+(size_block-1),color_list_glass[n]);
//                sprintf(com,"setblock %d %d %d %s replace",(px*1920+sx*16*2+ssx)*size_block,y,(py*1080+sy*18*3+ssy)*size_block,color_list_glass[n]);
//                printf("Sending command: %s -> ",com);
                fprintf(pfile,"%s\n",com);//fflush(pfile);
                fflush(pfile);
                kiki();
//                printf(".");
                fflush(pfile);
                sf::sleep(sf::seconds(0.1));
            } else {}
            ssy=ssy+1;
            if (ssy==18) {
                loader_mutex.lock();
                monitor_off=1;
                loader_mutex.unlock();
                ssy=0;
                ssx=ssx+1;
                if (ssx==16) {
                    ssx=0;
                    sx=sx+1;
                    if (sx==120) {
                        sx=0;
                        sy=sy+1;
                        if (sy==60) {
                            sy=0;
                            px=px+1;
                            if (px==totalpicturex) {
                                px=0;
                                py=py+1;
                                if (py==totalpicturey) {
                                    py=0;
                                    bukkit_running=0;
                                }
                            }
                        }
                    }
                    fflush(pfile);
                    sf::sleep(sf::seconds(1.0));
                }
                printf("\n");
//                fflush(pfile);
                hit++;
                if (hit==2) {
                    hit=0;
                    sprintf(com,"tp @p %d %d %d",(px*1920+sx*16+ssx)*size_block,300,(py*1080+sy*18+9)*size_block);
                    printf("Teleporting (%6d,%6d,%6d)...",(px*1920+sx*16+ssx+10)*size_block,300,(py*1080+sy*18+9)*size_block);
                    fprintf(pfile,"%s\n",com);
                    printf("flushing...");
                    fflush(pfile);
                    printf("waiting 0.2 second(s) for teleport");  for (int i=0; i<20; i++) {  kiki(); sf::sleep(sf::seconds(.01)); printf("."); } printf("\n");
                }
            }
            x=(px*1920+sx*16+ssx);
            z=(py*1080+sy*18+ssy);
            printf("block=(%6d,%6d) pixel_tot=(%5d,%5d) bitmap=(%d,%d) -> maze=(%2d,%2d) -> pixel(%2d,%2d))\r", x*size_block,z*size_block, x,z, px,py, sx,sy, ssx,ssy);
/*
            dir=rand()%6;
            if (dir==0) x=x-1;
            else if (dir==1) x=x+1;
            else if (dir==2) z=z-1;
            else if (dir==3) z=z+1;
            else if (dir==4 && y>5) y=y-1;
            else if (y<255) y=y+1;
            else {x=0;y=5;z=0;}
            c=rand()%16;

            sprintf(com,"setblock %d %d %d %s replace",x,y,z,color_list_wool[c]);
//            sprintf(com,"fill %d %d %d %d %d %d %s",x,y,z,x,y,z,color_list[c%17]);
//            printf("Sending command: %s -> ",com);
            fprintf(pfile,"%s\n",com);//fflush(pfile);
//            n=5; while (n>0 && bukkit_running==1) {n--; sf::sleep(sf::seconds(0.1)); } if (bukkit_running==0) break;
            printf(".");

/*
            fprintf(pfile,"fill 1 4 1 1 4 1 glass\nfill 0 4 0 0 4 0 stone\n");fflush(pfile);printf("Command send\n");
            n=5; while (n>0 && bukkit_running==1) {n--; sf::sleep(sf::seconds(0.2)); } if (bukkit_running==0) break;

            fprintf(pfile,"fill 1 4 1 1 4 1 stone\nfill 0 4 0 0 4 0 glass\n");fflush(pfile);printf("Command send\n");
            n=5; while (n>0 && bukkit_running==1) {n--; sf::sleep(sf::seconds(0.2)); } if (bukkit_running==0) break;

            fprintf(pfile,"fill 1 4 1 1 4 1 glass\nfill 0 4 0 0 4 0 stone\n");fflush(pfile);printf("Command send\n");
            n=5; while (n>0 && bukkit_running==1) {n--; sf::sleep(sf::seconds(0.2)); } if (bukkit_running==0) break;

            fprintf(pfile,"fill 1 4 1 1 4 1 stone\nfill 0 4 0 0 4 0 glass\n");fflush(pfile);printf("Command send\n");
            n=5; while (n>0 && bukkit_running==1) {n--; sf::sleep(sf::seconds(0.2)); } if (bukkit_running==0) break;
*/

        }
        fprintf(pfile,"Q\n");
        pclose(pfile);
        x=(px*1920+sx*16+ssx);
        z=(py*1080+sy*18+ssy);
        printf("block=(%6d,%6d) pixel_tot=(%5d,%5d) bitmap=(%d,%d) -> maze=(%2d,%2d) -> pixel(%2d,%2d))\n", x*size_block,z*size_block, x,z, px,py, sx,sy, ssx,ssy);
        if (ESCAPE_PRESSED) {
            ESCAPE_PRESSED=0;
            printf("Escape pressed....stop\n");
        }
        printf("Exiting...\n");
    }
}



sf::Thread bukkit_thread(&bukkit_thread_server);

void stop_bukkit_thread_server() {
    bukkit_thread.terminate();
}

void start_stop_bukkit_thread_server() {
    if (bukkit_running) {
        printf("Sending stop signal to bukkit thread...\n");
        strcpy(error_msg2,"Sending stop signal to bukkit thread...");
        bukkit_running=0;
        error_flag2=1;
        return;
    }
    bukkit_running=1;
    printf("Launching bukkit thread...\n");
    strcpy(error_msg2,"Launching bukkit thread...");
    error_flag2=1;
    bukkit_thread.launch();
}


void send_through_bukkitserver_mcrcon(char * command) {
    FILE * pfile;
    if (pfile=popen("mcrcon -t -c -H 127.0.0.1 -p hoppa","w") ) {
        for (int t=0; t<5; t++) {
            sf::sleep(sf::seconds(0.2));
            kiki();
        }
        fprintf(pfile,"fill 1 4 1 1 4 1 glass\nfill 0 4 0 0 4 0 stone\n");
        for (int t=0; t<5; t++) {
            sf::sleep(sf::seconds(0.2));
            kiki();
        }
        fprintf(pfile,"fill 1 4 1 1 4 1 stone\nfill 0 4 0 0 4 0 glass\n");
        for (int t=0; t<5; t++) {
            sf::sleep(sf::seconds(0.2));
            kiki();
        }
        fprintf(pfile,"fill 1 4 1 1 4 1 glass\nfill 0 4 0 0 4 0 stone\n");
        for (int t=0; t<5; t++) {
            sf::sleep(sf::seconds(0.2));
            kiki();
        }
        fprintf(pfile,"fill 1 4 1 1 4 1 stone\nfill 0 4 0 0 4 0 glass\nQ\n");
        pclose(pfile);
    }
    return;
}

extern sf::RenderTexture texture_point;
extern sf::Color pixel_color;
extern char **used;
extern int **used2;
extern sf::RenderTexture *texturemaxinmempoint[];
extern sf::Sprite sprite_point;
extern sf::Image image_point;

int get_nearest(int x, int y) {
    int r1,g1,b1,a1;
    sf::Color color;
    color=read_one_pixel(x,y);
    r1=color.r;g1=color.g;b1=color.b;a1=color.a;

    int t_diff_best=3*256;
    int n_best=0;
    for (int p=0; p<16; p++) {
        t_diff=abs(r1-color_list_rgb[p][0]);
        t_diff+=abs(g1-color_list_rgb[p][1]);
        t_diff+=abs(b1-color_list_rgb[p][2]);
        if (t_diff<t_diff_best) {
            t_diff_best=t_diff;
            n_best=p;
        }
    }
    trans=a1;
//    printf("x=%5d y=%5d pixel_color.rgba=%2x %2x %2x %2x best=(%2d)%2x %2x %2x\n",
//        x,y,r1,g1,b1,a1,n_best,color_list_rgb[n_best][0],color_list_rgb[n_best][1],color_list_rgb[n_best][2]);
    return n_best;
}


sf::Color read_one_pixel(int x, int y) {
    int picturex=(int)x/1920;
    int posx=x-1920.0*picturex;
    picturex=(picturex+totalpicturex)%totalpicturex;
    int picturey=(int)y/1080;
    int posy=y-1080.0*picturey;
    picturey=(picturey+totalpicturey)%totalpicturey;

    int mapx,mapy;
    int xdraw=(posx);
    if (xdraw>=1920)
    {
        xdraw=xdraw-1920;
        mapx=1;
    }
    else
        mapx=0;
    int ydraw=(posy);
    if (ydraw>=1080)
    {
        ydraw=ydraw-1080;
        mapy=1;
    }
    else
        mapy=0;

    int arx=(picturex+mapx)%(maxpicturex+1);
    int ary=(picturey+mapy)%(maxpicturey+1);

    if (totalused>MAXINMEM)
    {
        go_save_some_bitmaps();
    }
    if (used[arx][ary]==0) ReadOneBitmap(arx,ary);

//    printf("x=%5d y=%5d picturex=%d picturey=%d posx=%4d posy=%4d arx=%d ary=%d\n",
//           x,y,picturex,picturey,posx,posy,arx,ary);

    sprite_point.setTexture(texturemaxinmempoint[used2[arx][ary]]->getTexture(),false);
    sprite_point.setTextureRect(   { xdraw, ydraw,1, 1 }  );
    sprite_point.setPosition(0,0);
    texture_point.clear();
    texture_point.draw(sprite_point);
    texture_point.display();
    image_point=texture_point.getTexture().copyToImage();
    pixel_color=image_point.getPixel(0,0);
    return pixel_color;
}

extern WORLD_STRUCT world;
extern int shut_up;
int MC_fb=0;

void MC_DO_BATCH1(char* worldregiondir, char* filename) {
    MCA_MODE=LOAD_NBT;

    SILENT=0;
    if (MC_fb==1) { print_header=1; MC_fb=0; } else print_header=0;
    REGION_STRUCT* region_struct=append_mca_file_to_world(worldregiondir,filename);
    SILENT=1;

//    PLOT_REGION(region_struct);

    update_or_create_chunks_from_region_tags(region_struct);
    chunks_to_memory_mca(region_struct);
    save_region_binary_to_file(region_struct);

    print_header=0;
    erase_region(region_struct);
//    destroy(&world);
    SILENT=0;
}


void MC_DO_SOMETHING(char* worldregiondir, char* filename) {
    tot_chunks_written=0;

    MC_DO_BATCH1(worldregiondir, filename);

}

void MC_do_something_with_all(char* worldregiondir) {
    mien_tied=0.0;
    mien_tied_total=0.0;
    MC_fb=1;

    tied=0.0;tied_total=0.0;print_header=1;
    printf("%6.1f %6.3f ",tied_total,tied);
    printf("2) DO SOMETHING WITH ALL:\n");

    DIR* dr = opendir(worldregiondir);
    struct dirent *de;

    printf("TO DO: ");
    while ((de = readdir(dr)) != NULL) {
        if ((strstr(de->d_name, ".mca")) != NULL) {
            printf(de->d_name);
        }
    }
    closedir(dr);
    dr = opendir(worldregiondir);
    while ((de = readdir(dr)) != NULL) {
        if ((strstr(de->d_name, ".mca")) != NULL) {
            MC_DO_SOMETHING(worldregiondir,de->d_name);
        }
    }
    closedir(dr);


    SILENT=0;

    list_world(world,-1);
    printf(" %d Regions\r",world.number_of_regions);

    erase_regions();

    destroy(&world);

    tied=GetCounterNanoseconds();
    tied_total=tied_total+tied;

    xalloc_stats_quiet=1;
    xalloc_stats();

    printf("%6.1f %6.3f END DO SOMETHING: ",tied_total,tied);
    printf("Total chunks read=%u\n",tot_chunks_appended);
    tot_chunks_appended=0;
    printf("___________________________________________________________________________________________________________________________________________________________________________________________________________________________________________\n");
//    system("timeout 3 >nul");
    tied_total=0;

}
extern size_t XALLOC_MEM_START;
extern int server_running;
extern char send_message;

void test_minecraft() {
    if (file_exists("/Saves/Test/region.original")) {
        printf("Set region.original back to region & region back to region.new:\n");
        if (file_exists("/Saves/Test/region")) {
            if (file_exists("/Saves/Test/region.new")) {
                printf("Error: /Saves/Test/region.new found....\n");
            }
            printf("Renaming /Saves/Test/region back to /Saves/Test/region.new...\n");
            rename("/Saves/Test/region","/Saves/Test/region.new");

            printf("Renaming /Saves/Test/region.original back to /Saves/Test/region....\n");
            rename("/Saves/Test/region.original","/Saves/Test/region");
        } else {
            printf("Error: /Saves/Test/region not found....\n");
            printf("Renaming /Saves/Test/region.original back to /Saves/Test/region....\n");
            rename("/Saves/Test/region.original","/Saves/Test/region");
        }
    }

    static int first=0;
    if (first==0) {
        xalloc_get_tot_mem();
        XALLOC_MEM_START=memory_total;
        first=1;
    }

//    shut_up=1;
    MC_do_something_with_all("/Saves/Test/region");
    SILENT=1;
    erase_regions();
    destroy(&world);
    SILENT=0;
//    monitor_off=1;
//    shut_up=0;

    if (file_exists("/Saves/Test/region.new")) {
        printf("Set region to region.original & region.new to region:\n");
        if (!file_exists("/Saves/Test/region.original")) {
            printf("Renaming /Saves/Test/region to /Saves/Test/region.original...\n");
            rename("/Saves/Test/region","/Saves/Test/region.original");

            printf("Renaming /Saves/Test/region.new to /Saves/Test/region....\n");
            rename("/Saves/Test/region.new","/Saves/Test/region");
        } else {
            printf("Error: /Saves/Test/region.original found....\n");
        }
    }

//    if (server_running) {
//        printf("Server running. Stopping it..");
//        send_message='S';
//        while (server_running) { printf("."); sf::sleep(sf::seconds(0.2)); }
//        printf("server stopped\n");
//    }
//    printf("Starting server (again)..");
//    send_message='s';
//    while (!server_running) { printf("."); sf::sleep(sf::seconds(0.2)); }
//    printf("\nServer running on region.new (->region)....waiting for server to stop (ctrl+shift '/')\n");
//    while (server_running) { sf::sleep(sf::seconds(1.0)); }
//    printf("Server stopped....renaming directories back\n");

    if (file_exists("/Saves/Test/region.original")) {
        printf("Set region.original back to region & region back to region.new:\n");
        if (file_exists("/Saves/Test/region")) {
            if (file_exists("/Saves/Test/region.new")) {
                printf("Error: /Saves/Test/region.new found....\n");
            }
            printf("Renaming /Saves/Test/region back to /Saves/Test/region.new...\n");
            rename("/Saves/Test/region","/Saves/Test/region.new");

            printf("Renaming /Saves/Test/region.original back to /Saves/Test/region....\n");
            rename("/Saves/Test/region.original","/Saves/Test/region");
        } else {
            printf("Error: /Saves/Test/region not found....\n");
            printf("Renaming /Saves/Test/region.original back to /Saves/Test/region....\n");
            rename("/Saves/Test/region.original","/Saves/Test/region");
        }
    }
}


int MC_running=0;

void MC_wait_for_return() {
    test_minecraft();
    printf("MC stopped\n");
    MC_running=0;
}

sf::Thread MC(&MC_wait_for_return);

void launch_MC() {
    if (MC_running==1) {
        printf("MC already running.....stop server to end\n");
        return;
    }
    MC_running=1;
    MC.launch();
}

void terminate_MC() {  // Never use this.....otherwise memory leaks.
    MC.terminate();
}
