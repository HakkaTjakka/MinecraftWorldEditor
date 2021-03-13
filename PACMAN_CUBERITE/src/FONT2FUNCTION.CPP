#include <conio.h>
#include <stdio.h>
#include <dos.h>
#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>

void font2function_sub(int chain);

void font2function() {
    font2function_sub(0);
    font2function_sub(1);
    font2function_sub(2);
}

void font2function_sub(int chain) {
    sf::Image fontimage;
    fontimage.loadFromFile("resources/abc_16x16.png");
    printf("Size x=%d, y=%d\n",fontimage.getSize().x,fontimage.getSize().y);
    mkdir("mcfunctions");
    int offset_x=0;
    int offset_y=0;
    int offset_z=0;
    char block_inner[100]="concrete 0";
    char block_outer[100]="concrete 13"; //dark green
    char block_back[100]="concrete 4";
    char block_back2[100]="glowstone 0";
    char block_outline[100]="concrete 14";
    char block_fill[100]="stained_glass 5"; //lime green
    char remove_inner[100]="air 0";
    char remove_outer[100]="air 0";
    char remove_back[100]="air 0";
    char remove_outline[100]="air 0";
//    char remove_inner[100]="stained_glass 0";
//    char remove_outer[100]="stained_glass 14";
//    char remove_back[100]="stained_glass 4";
//    char remove_outline[100]="stained_glass 6";

    std::string substring;

    if (chain==0) {
        substring="XDIR";
//        offset_x=16;
    } else if (chain==1) {
        substring="YDIR";
//        offset_y=16;
    } else if (chain==2) {
        substring="ZDIR";
//        offset_z=16;
    }
    int offset_inner=0;
    int offset_outer=-1;
    int offset_back=0;
    for (int l=1; l<=26; l++) {
        FILE* mcfunction;
        char fname[100];
        sprintf(fname,"mcfunctions/letter_%s_%c.mcfunction",substring.c_str(),64+l);
        mcfunction=fopen(fname,"w");

        printf("%c",64+l);

        int o=-8;
        int n_o=7;
//        int o=-8;
//        int n_o=7;

        int z=o-1;
        int n_z=n_o+1;

//        int k=z-1;
//        int n_k=n_z+1;

        int k=z;
        int n_k=n_z;

        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s keep\n",
                 offset_x +   k,                    offset_y + k,                   offset_z + n_z,
                 offset_x + n_k,                    offset_y + n_k,                 offset_z + n_z,                 block_outline);   //Z+
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s keep\n",
                 offset_x +   k,                    offset_y + k,                   offset_z +   z,
                 offset_x + n_k,                    offset_y + n_k,                 offset_z +   z,                 block_outline);   //Z-
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s keep\n",
                 offset_x +   z,                    offset_y + k,                   offset_z +   k,
                 offset_x +   z,                    offset_y + n_k,                 offset_z +   n_k,               block_outline);   //X-
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s keep\n",
                 offset_x + n_z,                    offset_y + k,                   offset_z +   k,
                 offset_x + n_z,                    offset_y + n_k,                 offset_z + n_k,                 block_outline);   //X+
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s keep\n",
                 offset_x +   k,                    offset_y + n_z,                 offset_z +   k,
                 offset_x + n_k,                    offset_y + n_z,                 offset_z + n_k,                 block_outline);   //Y+
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s keep\n",
                 offset_x +   k,                    offset_y + z,                   offset_z + k,
                 offset_x + n_k,                    offset_y + z,                   offset_z + n_k,                 block_outline);   //Y-



        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s replace %s\n",
                 offset_x +   o,                    offset_y + o,                   offset_z + n_z,
                 offset_x + n_o,                    offset_y + n_o,                 offset_z + n_z,                 block_back,block_outline);   //Z+
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s replace %s\n",
                 offset_x +   o,                    offset_y + o,                   offset_z +   z,
                 offset_x + n_o,                    offset_y + n_o,                 offset_z +   z,                 block_back,block_outline);   //Z-
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s replace %s\n",
                 offset_x +   z,                    offset_y + o,                   offset_z +   o,
                 offset_x +   z,                    offset_y + n_o,                 offset_z +   n_o,               block_back,block_outline);   //X-
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s replace %s\n",
                 offset_x + n_z,                    offset_y + o,                   offset_z +   o,
                 offset_x + n_z,                    offset_y + n_o,                 offset_z + n_o,                 block_back,block_outline);   //X+
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s replace %s\n",
                 offset_x +   o,                    offset_y + n_z,                 offset_z +   o,
                 offset_x + n_o,                    offset_y + n_z,                 offset_z + n_o,                 block_back,block_outline);   //Y+
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s replace %s\n",
                 offset_x +   o,                    offset_y + z,                   offset_z + o,
                 offset_x + n_o,                    offset_y + z,                   offset_z + n_o,                 block_back,block_outline);   //Y-



        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s replace %s\n",
                 offset_x +   o,                    offset_y + o,                    offset_z + n_z  + offset_inner,
                 offset_x + n_o,                    offset_y + n_o,                  offset_z + n_z  + offset_inner,                    remove_outline,block_fill);   //Z+
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s replace %s\n",
                 offset_x +   o,                    offset_y + o,                    offset_z +   z  - offset_inner,
                 offset_x + n_o,                    offset_y + n_o,                  offset_z +   z  - offset_inner,                    remove_outline,block_fill);   //Z-
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s replace %s\n",
                 offset_x +   z  - offset_inner,    offset_y + o,                    offset_z +   o,
                 offset_x +   z  - offset_inner,    offset_y + n_o,                  offset_z +   n_o,                                  remove_outline,block_fill);   //X-
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s replace %s\n",
                 offset_x + n_z  + offset_inner,    offset_y + o,                    offset_z +   o,
                 offset_x + n_z  + offset_inner,    offset_y + n_o,                  offset_z + n_o,                                    remove_outline,block_fill);   //X+
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s replace %s\n",
                 offset_x +   o,                    offset_y + n_z  + offset_inner,  offset_z +   o,
                 offset_x + n_o,                    offset_y + n_z  + offset_inner,  offset_z + n_o,                                    remove_outline,block_fill);   //Y+
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s replace %s\n",
                 offset_x +   o,                    offset_y + z  - offset_inner,    offset_z + o,
                 offset_x + n_o,                    offset_y + z  - offset_inner,    offset_z + n_o,                                    remove_outline,block_fill);   //Y-


        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s replace %s\n",
                 offset_x +   o,                    offset_y + o,                    offset_z + n_z  + offset_inner,
                 offset_x + n_o,                    offset_y + n_o,                  offset_z + n_z  + offset_inner,                    remove_inner,block_fill);   //Z+
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s replace %s\n",
                 offset_x +   o,                    offset_y + o,                    offset_z +   z  - offset_inner,
                 offset_x + n_o,                    offset_y + n_o,                  offset_z +   z  - offset_inner,                    remove_inner,block_fill);   //Z-
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s replace %s\n",
                 offset_x +   z  - offset_inner,    offset_y + o,                    offset_z +   o,
                 offset_x +   z  - offset_inner,    offset_y + n_o,                  offset_z +   n_o,                                  remove_inner,block_fill);   //X-
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s replace %s\n",
                 offset_x + n_z  + offset_inner,    offset_y + o,                    offset_z +   o,
                 offset_x + n_z  + offset_inner,    offset_y + n_o,                  offset_z + n_o,                                    remove_inner,block_fill);   //X+
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s replace %s\n",
                 offset_x +   o,                    offset_y + n_z  + offset_inner,  offset_z +   o,
                 offset_x + n_o,                    offset_y + n_z  + offset_inner,  offset_z + n_o,                                    remove_inner,block_fill);   //Y+
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s replace %s\n",
                 offset_x +   o,                    offset_y + z  - offset_inner,    offset_z + o,
                 offset_x + n_o,                    offset_y + z  - offset_inner,    offset_z + n_o,                                    remove_inner,block_fill);   //Y-




        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s replace %s\n",
                 offset_x +   o,                    offset_y + o,                    offset_z + n_z  + offset_inner,
                 offset_x + n_o,                    offset_y + n_o,                  offset_z + n_z  + offset_inner,                    remove_inner,block_inner);   //Z+
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s replace %s\n",
                 offset_x +   o,                    offset_y + o,                    offset_z +   z  - offset_inner,
                 offset_x + n_o,                    offset_y + n_o,                  offset_z +   z  - offset_inner,                    remove_inner,block_inner);   //Z-
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s replace %s\n",
                 offset_x +   z  - offset_inner,    offset_y + o,                    offset_z +   o,
                 offset_x +   z  - offset_inner,    offset_y + n_o,                  offset_z +   n_o,                                  remove_inner,block_inner);   //X-
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s replace %s\n",
                 offset_x + n_z  + offset_inner,    offset_y + o,                    offset_z +   o,
                 offset_x + n_z  + offset_inner,    offset_y + n_o,                  offset_z + n_o,                                    remove_inner,block_inner);   //X+
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s replace %s\n",
                 offset_x +   o,                    offset_y + n_z  + offset_inner,  offset_z +   o,
                 offset_x + n_o,                    offset_y + n_z  + offset_inner,  offset_z + n_o,                                    remove_inner,block_inner);   //Y+
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s replace %s\n",
                 offset_x +   o,                    offset_y + z  - offset_inner,    offset_z + o,
                 offset_x + n_o,                    offset_y + z  - offset_inner,    offset_z + n_o,                                    remove_inner,block_inner);   //Y-


        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s replace %s\n",
                 offset_x +   o,                    offset_y + o,                    offset_z + n_z  + offset_outer,
                 offset_x + n_o,                    offset_y + n_o,                  offset_z + n_z  + offset_outer,                    remove_outer,block_outer);   //Z+
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s replace %s\n",
                 offset_x +   o,                    offset_y + o,                    offset_z +   z  - offset_outer,
                 offset_x + n_o,                    offset_y + n_o,                  offset_z +   z  - offset_outer,                    remove_outer,block_outer);   //Z-
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s replace %s\n",
                 offset_x +   z  - offset_outer,    offset_y + o,                    offset_z +   o,
                 offset_x +   z  - offset_outer,    offset_y + n_o,                  offset_z +   n_o,                                  remove_outer,block_outer);   //X-
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s replace %s\n",
                 offset_x + n_z  + offset_outer,    offset_y + o,                    offset_z +   o,
                 offset_x + n_z  + offset_outer,    offset_y + n_o,                  offset_z + n_o,                                    remove_outer,block_outer);   //X+
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s replace %s\n",
                 offset_x +   o,                    offset_y + n_z  + offset_outer,  offset_z +   o,
                 offset_x + n_o,                    offset_y + n_z  + offset_outer,  offset_z + n_o,                                    remove_outer,block_outer);   //Y+
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s replace %s\n",
                 offset_x +   o,                    offset_y + z  - offset_outer,    offset_z + o,
                 offset_x + n_o,                    offset_y + z  - offset_outer,    offset_z + n_o,                                    remove_outer,block_outer);   //Y-






        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s replace %s\n",
                 offset_x +   o,                    offset_y + o,                    offset_z + n_z  + offset_back,
                 offset_x + n_o,                    offset_y + n_o,                  offset_z + n_z  + offset_back,                     remove_back,block_back);   //Z+
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s replace %s\n",
                 offset_x +   o,                    offset_y + o,                    offset_z +   z  - offset_back,
                 offset_x + n_o,                    offset_y + n_o,                  offset_z +   z  - offset_back,                     remove_back,block_back);   //Z-
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s replace %s\n",
                 offset_x +   z  - offset_back,     offset_y + o,                    offset_z +   o,
                 offset_x +   z  - offset_back,     offset_y + n_o,                  offset_z +   n_o,                                  remove_back,block_back);   //X-
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s replace %s\n",
                 offset_x + n_z  + offset_back,     offset_y + o,                    offset_z +   o,
                 offset_x + n_z  + offset_back,     offset_y + n_o,                  offset_z + n_o,                                    remove_back,block_back);   //X+
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s replace %s\n",
                 offset_x +   o,                    offset_y + n_z  + offset_back,   offset_z +   o,
                 offset_x + n_o,                    offset_y + n_z  + offset_back,   offset_z + n_o,                                    remove_back,block_back);   //Y+
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s replace %s\n",
                 offset_x +   o,                    offset_y + z  - offset_back,     offset_z + o,
                 offset_x + n_o,                    offset_y + z  - offset_back,     offset_z + n_o,                                    remove_back,block_back);   //Y-







        std::string all_back="";
        std::string all_outer="";
        std::string all_inner="";
        std::string all_fill="";
        char p[1000]="";
        for (int c_y=-8; c_y<8; c_y++) {
            for (int c_x=-8; c_x<8; c_x++) {
                sf::Color pixel=fontimage.getPixel(32*16+l*16+8+c_x,8+c_y);

                int x=c_x;
                int y=-c_y-1;

                int n_x=-c_x-1;
                int n_y=c_y;

                if (pixel.a==0) {
                    sprintf(p, "setblock ~%d ~%d ~%d %s keep\n", offset_x +   x,                    offset_y + y,                    offset_z + n_z  + offset_back,    block_back);  all_back+= std::string()+p;  //front
                    sprintf(p, "setblock ~%d ~%d ~%d %s keep\n", offset_x + n_x,                    offset_y + y,                    offset_z +   z  - offset_back,    block_back);  all_back+= std::string()+p;  //back
                    sprintf(p, "setblock ~%d ~%d ~%d %s keep\n", offset_x +   z  - offset_back,     offset_y + y,                    offset_z +   x,                   block_back);  all_back+= std::string()+p;  //left
                    sprintf(p, "setblock ~%d ~%d ~%d %s keep\n", offset_x + n_z  + offset_back,     offset_y + y,                    offset_z + n_x,                   block_back);  all_back+= std::string()+p;  //right
                    sprintf(p, "setblock ~%d ~%d ~%d %s keep\n", offset_x +   x,                    offset_y + n_z  + offset_back,   offset_z + n_y,                   block_back);  all_back+= std::string()+p;  //bottom
                    sprintf(p, "setblock ~%d ~%d ~%d %s keep\n", offset_x + n_x,                    offset_y + z  - offset_back,     offset_z + n_y,                   block_back);  all_back+= std::string()+p;  //top

                    sprintf(p, "setblock ~%d ~%d ~%d %s keep\n", offset_x +   x,                    offset_y + y,                    offset_z + n_z  + offset_back,    block_back,block_fill);  all_fill+= std::string()+p;  //front
                    sprintf(p, "setblock ~%d ~%d ~%d %s keep\n", offset_x + n_x,                    offset_y + y,                    offset_z +   z  - offset_back,    block_back,block_fill);  all_fill+= std::string()+p;  //back
                    sprintf(p, "setblock ~%d ~%d ~%d %s keep\n", offset_x +   z  - offset_back,     offset_y + y,                    offset_z +   x,                   block_back,block_fill);  all_fill+= std::string()+p;  //left
                    sprintf(p, "setblock ~%d ~%d ~%d %s keep\n", offset_x + n_z  + offset_back,     offset_y + y,                    offset_z + n_x,                   block_back,block_fill);  all_fill+= std::string()+p;  //right
                    sprintf(p, "setblock ~%d ~%d ~%d %s keep\n", offset_x +   x,                    offset_y + n_z  + offset_back,   offset_z + n_y,                   block_back,block_fill);  all_fill+= std::string()+p;  //bottom
                    sprintf(p, "setblock ~%d ~%d ~%d %s keep\n", offset_x + n_x,                    offset_y + z  - offset_back,     offset_z + n_y,                   block_back,block_fill);  all_fill+= std::string()+p;  //top
                } else if (pixel.r==0) {
                    sprintf(p,"setblock ~%d ~%d ~%d %s\n", offset_x +   x,                    offset_y + y,                    offset_z + n_z  + offset_outer,   block_outer);  all_outer+=std::string()+p;  //front
                    sprintf(p,"setblock ~%d ~%d ~%d %s\n", offset_x + n_x,                    offset_y + y,                    offset_z +   z  - offset_outer,   block_outer);  all_outer+=std::string()+p;   //back
                    sprintf(p,"setblock ~%d ~%d ~%d %s\n", offset_x +   z  - offset_outer,    offset_y + y,                    offset_z +   x,                   block_outer);  all_outer+=std::string()+p;   //left
                    sprintf(p,"setblock ~%d ~%d ~%d %s\n", offset_x + n_z  + offset_outer,    offset_y + y,                    offset_z + n_x,                   block_outer);  all_outer+=std::string()+p;   //right
                    sprintf(p,"setblock ~%d ~%d ~%d %s\n", offset_x +   x,                    offset_y + n_z  + offset_outer,  offset_z + n_y,                   block_outer);  all_outer+=std::string()+p;   //bottom
                    sprintf(p,"setblock ~%d ~%d ~%d %s\n", offset_x + n_x,                    offset_y + z  - offset_outer,    offset_z + n_y,                   block_outer);  all_outer+=std::string()+p;   //top

                } else {
                    sprintf(p,"setblock ~%d ~%d ~%d %s keep\n", offset_x +   x,                    offset_y + y,                    offset_z + n_z  + offset_inner,   block_inner);  all_inner+=std::string()+p;   //Z+
                    sprintf(p,"setblock ~%d ~%d ~%d %s keep\n", offset_x + n_x,                    offset_y + y,                    offset_z +   z  - offset_inner,   block_inner);  all_inner+=std::string()+p;   //Z-
                    sprintf(p,"setblock ~%d ~%d ~%d %s keep\n", offset_x +   z  - offset_inner,    offset_y + y,                    offset_z +   x,                   block_inner);  all_inner+=std::string()+p;   //X-
                    sprintf(p,"setblock ~%d ~%d ~%d %s keep\n", offset_x + n_z  + offset_inner,    offset_y + y,                    offset_z + n_x,                   block_inner);  all_inner+=std::string()+p;   //X+
                    sprintf(p,"setblock ~%d ~%d ~%d %s keep\n", offset_x +   x,                    offset_y + n_z  + offset_inner,  offset_z + n_y,                   block_inner);  all_inner+=std::string()+p;   //Y+
                    sprintf(p,"setblock ~%d ~%d ~%d %s keep\n", offset_x + n_x,                    offset_y + z  - offset_inner,    offset_z + n_y,                   block_inner);  all_inner+=std::string()+p;   //Y-
                }
            }
        }

        fprintf(mcfunction,all_back.c_str());
        fprintf(mcfunction,all_inner.c_str());
        fprintf(mcfunction,all_outer.c_str());


        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s keep\n",
                 offset_x +   k,                    offset_y + k,                   offset_z + n_z,
                 offset_x + n_k,                    offset_y + n_k,                 offset_z + n_z,                 block_outline);   //Z+
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s keep\n",
                 offset_x +   k,                    offset_y + k,                   offset_z +   z,
                 offset_x + n_k,                    offset_y + n_k,                 offset_z +   z,                 block_outline);   //Z-
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s keep\n",
                 offset_x +   z,                    offset_y + k,                   offset_z +   k,
                 offset_x +   z,                    offset_y + n_k,                 offset_z +   n_k,               block_outline);   //X-
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s keep\n",
                 offset_x + n_z,                    offset_y + k,                   offset_z +   k,
                 offset_x + n_z,                    offset_y + n_k,                 offset_z + n_k,                 block_outline);   //X+
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s keep\n",
                 offset_x +   k,                    offset_y + n_z,                 offset_z +   k,
                 offset_x + n_k,                    offset_y + n_z,                 offset_z + n_k,                 block_outline);   //Y+
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s keep\n",
                 offset_x +   k,                    offset_y + z,                   offset_z + k,
                 offset_x + n_k,                    offset_y + z,                   offset_z + n_k,                 block_outline);   //Y-

        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s replace %s\n",
                 offset_x +   o,                    offset_y + o,                    offset_z + n_z  + offset_back,
                 offset_x + n_o,                    offset_y + n_o,                  offset_z + n_z  + offset_back,                     remove_outline,block_outline);   //Z+
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s replace %s\n",
                 offset_x +   o,                    offset_y + o,                    offset_z +   z  - offset_back,
                 offset_x + n_o,                    offset_y + n_o,                  offset_z +   z  - offset_back,                     remove_outline,block_outline);   //Z-
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s replace %s\n",
                 offset_x +   z  - offset_back,     offset_y + o,                    offset_z +   o,
                 offset_x +   z  - offset_back,     offset_y + n_o,                  offset_z +   n_o,                                  remove_outline,block_outline);   //X-
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s replace %s\n",
                 offset_x + n_z  + offset_back,     offset_y + o,                    offset_z +   o,
                 offset_x + n_z  + offset_back,     offset_y + n_o,                  offset_z + n_o,                                    remove_outline,block_outline);   //X+
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s replace %s\n",
                 offset_x +   o,                    offset_y + n_z  + offset_back,   offset_z +   o,
                 offset_x + n_o,                    offset_y + n_z  + offset_back,   offset_z + n_o,                                    remove_outline,block_outline);   //Y+
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s replace %s\n",
                 offset_x +   o,                    offset_y + z  - offset_back,     offset_z + o,
                 offset_x + n_o,                    offset_y + z  - offset_back,     offset_z + n_o,                                    remove_outline,block_outline);   //Y-

//        fprintf(mcfunction,all_fill.c_str());

        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s keep\n",
                 offset_x +   o,                    offset_y + o,                    offset_z + n_z  + offset_inner,
                 offset_x + n_o,                    offset_y + n_o,                  offset_z + n_z  + offset_inner,                    block_fill);   //Z+
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s keep\n",
                 offset_x +   o,                    offset_y + o,                    offset_z +   z  - offset_inner,
                 offset_x + n_o,                    offset_y + n_o,                  offset_z +   z  - offset_inner,                    block_fill);   //Z-
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s keep\n",
                 offset_x +   z  - offset_inner,    offset_y + o,                    offset_z +   o,
                 offset_x +   z  - offset_inner,    offset_y + n_o,                  offset_z +   n_o,                                  block_fill);   //X-
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s keep\n",
                 offset_x + n_z  + offset_inner,    offset_y + o,                    offset_z +   o,
                 offset_x + n_z  + offset_inner,    offset_y + n_o,                  offset_z + n_o,                                    block_fill);   //X+
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s keep\n",
                 offset_x +   o,                    offset_y + n_z  + offset_inner,  offset_z +   o,
                 offset_x + n_o,                    offset_y + n_z  + offset_inner,  offset_z + n_o,                                    block_fill);   //Y+
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s keep\n",
                 offset_x +   o,                    offset_y + z  - offset_inner,    offset_z + o,
                 offset_x + n_o,                    offset_y + z  - offset_inner,    offset_z + n_o,                                    block_fill);   //Y-

        fprintf(mcfunction,all_fill.c_str());


        int next_letter=l+1; if (next_letter>26) next_letter=1;
        fprintf(mcfunction,"setblock ~ ~ ~ air 0\n");

//        fprintf(mcfunction,"fill ~ ~ ~ ~ ~ ~ planks 0 replace air 0\n",next_letter);
//        fprintf(mcfunction,"fill ~ ~ ~ ~ ~ ~ air 0 replace command_block 0\n",next_letter);

//        fprintf(mcfunction,"fill ~ ~ ~ ~ ~ ~ command_block 0 keep {Command:\"function abc:next_%c\"}\n",next_letter+64);

//        fprintf(mcfunction,"fill ~ ~ ~ ~ ~ ~ command_block 0 keep {Command:\"function abc:next_%c\",auto:1b}\n",next_letter+64);

        fprintf(mcfunction,"setblock ~%d ~%d ~%d air 0\n",offset_x,offset_y,offset_z);
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d repeating_command_block 0 keep {Command:\"function abc:next_%s_%c\",auto:1b}\n",offset_x,offset_y,offset_z,offset_x,offset_y,offset_z,substring.c_str(),next_letter+64);

////        fprintf(mcfunction,"fill ~ ~ ~ ~ ~ ~ repeating_command_block 0 keep {Command:\"function abc:next_%c\",auto:1b}\n",next_letter+64);

//        fprintf(mcfunction,"fill ~ ~ ~ ~ ~ ~ air 0 replace planks 0\n",next_letter);


//        fprintf(mcfunction,"setblock ~16 ~ ~ air 0\n",next_letter);
//        fprintf(mcfunction,"fill ~16 ~ ~ ~16 ~ ~ repeating_command_block 0 keep {Command:\"function abc:letter_%c\",auto:1b}\n",next_letter+64);

//        fprintf(mcfunction,"setblock ~-16 ~ ~ air 0\n",next_letter);



        fclose(mcfunction);

        sprintf(fname,"mcfunctions/next_%s_%c.mcfunction",substring.c_str(),next_letter+64);
        mcfunction=fopen(fname,"w");
        fprintf(mcfunction,"setblock ~ ~ ~ air 0\n",next_letter);

        if (chain==0) {
            fprintf(mcfunction,"setblock ~%d ~%d ~%d air 0\n",
                    -offset_x+16,-offset_y,-offset_z);
            fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d repeating_command_block 0 keep {Command:\"/function abc:letter_%s_%c\",auto:1b}\n",
                    -offset_x+16,-offset_y,-offset_z,
                    -offset_x+16,-offset_y,-offset_z,substring.c_str(),next_letter+64);
            if (next_letter==26) {
                fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d repeating_command_block 0 keep {Command:\"/function abc:next_%s_%c\",auto:1b}\n",
                    -offset_x+32,-offset_y+16-16,-offset_z,
                    -offset_x+32,-offset_y+16-16,-offset_z,"YDIR",2+64);
            }
            if (next_letter==25) {
                fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d repeating_command_block 0 keep {Command:\"/function abc:next_%s_%c\",auto:1b}\n",
                    -offset_x+48,-offset_y,-offset_z+16-16,
                    -offset_x+48,-offset_y,-offset_z+16-16,"ZDIR",2+64);
            }
        } else if (chain==1) {
            fprintf(mcfunction,"setblock ~%d ~%d ~%d air 0\n",
                    -offset_x,-offset_y+16,-offset_z);
            fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d repeating_command_block 0 keep {Command:\"/function abc:letter_%s_%c\",auto:1b}\n",
                    -offset_x,-offset_y+16,-offset_z,
                    -offset_x,-offset_y+16,-offset_z,substring.c_str(),next_letter+64);
            if (next_letter==26) {
                fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d repeating_command_block 0 keep {Command:\"/function abc:next_%s_%c\",auto:1b}\n",
                    -offset_x+16-16,-offset_y+32,-offset_z,
                    -offset_x+16-16,-offset_y+32,-offset_z,"XDIR",2+64);
            }
            if (next_letter==25) {
                fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d repeating_command_block 0 keep {Command:\"/function abc:next_%s_%c\",auto:1b}\n",
                    -offset_x,-offset_y+48,-offset_z+16-16,
                    -offset_x,-offset_y+48,-offset_z+16-16,"ZDIR",2+64);
            }
        } else if (chain==2) {
            fprintf(mcfunction,"setblock ~%d ~%d ~%d air 0\n",
                    -offset_x,-offset_y,-offset_z+16);
            fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d repeating_command_block 0 keep {Command:\"/function abc:letter_%s_%c\",auto:1b}\n",
                    -offset_x,-offset_y,-offset_z+16,
                    -offset_x,-offset_y,-offset_z+16,substring.c_str(),next_letter+64);
            if (next_letter==26) {
                fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d repeating_command_block 0 keep {Command:\"/function abc:next_%s_%c\",auto:1b}\n",
                    -offset_x+16-16,-offset_y,-offset_z+32,
                    -offset_x+16-16,-offset_y,-offset_z+32,"XDIR",2+64);
            }
            if (next_letter==25) {
                fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d repeating_command_block 0 keep {Command:\"/function abc:next_%s_%c\",auto:1b}\n",
                    -offset_x,-offset_y+16-16,-offset_z+48,
                    -offset_x,-offset_y+16-16,-offset_z+48,"YDIR",2+64);
            }

        }

////        fprintf(mcfunction,"fill ~ ~ ~ ~ ~ ~ command_block 0 keep {Command:\"/function abc:letter_%c\"}\n",next_letter+64);

        fclose(mcfunction);
    }
    printf("\n");
}


