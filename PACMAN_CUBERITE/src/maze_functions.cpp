#include "everything.hpp"

void plot_pixel(float x, float y, sf::Color mcolor, sf::Vector2f msize);
extern char SAS_DIR[];

void ffmpegfile_to_maze() {
/*
    if (texture_from_ffmpeg.getSize().x+2>maze_plotsizex) {
        sprintf(error_msg2,"SIZE PICTURE X=%d+2 > SIZE MAZE X=%d",texture_from_ffmpeg.getSize().x,maze_plotsizex);
        error_flag2=1;
        return;
    }
    if (texture_from_ffmpeg.getSize().y+2>maze_plotsizey) {
        sprintf(error_msg2,"SIZE PICTURE Y=%d+2 > SIZE MAZE Y=%d",texture_from_ffmpeg.getSize().y,maze_plotsizey);
        error_flag2=1;
        return;
    }
*/
    int max_x=texture_from_ffmpeg.getSize().x;
    int max_y=texture_from_ffmpeg.getSize().y;

    if (texture_from_ffmpeg.getSize().x>BITMAPSX*30) {
        sprintf(error_msg2,"SIZE PICTURE X=%d > SIZE MAZE X=%d TRUNCATING",texture_from_ffmpeg.getSize().x,BITMAPSX*30);
        error_flag2=1;
        max_x=BITMAPSX*30;
    }
    if (texture_from_ffmpeg.getSize().y>BITMAPSY*15) {
        sprintf(error_msg3,"SIZE PICTURE Y=%d > SIZE MAZE Y=%d  TRUNCATING",texture_from_ffmpeg.getSize().y,BITMAPSY*15);
        error_flag3=1;
        max_y=BITMAPSY*15;
    }

    sf::Image myimage;
    myimage=texture_from_ffmpeg.copyToImage();

    sf::Color pixel; int set_c;
    sf::Color pixel_l; int set_l;
    sf::Color pixel_ll; int set_ll;
    sf::Color pixel_r; int set_r;
    sf::Color pixel_rr; int set_rr;
    sf::Color pixel_u; int set_u;
    sf::Color pixel_uu; int set_uu;
    sf::Color pixel_d; int set_d;
    sf::Color pixel_dd; int set_dd;
    sf::Color pixel_rd; int set_rd;
    sf::Color pixel_ru; int set_ru;
    sf::Color pixel_ld; int set_ld;
    sf::Color pixel_lu; int set_lu;
//    int offset_x=(maze_plotsizex-texture_from_ffmpeg.getSize().x)/2;
//    int offset_y=(maze_plotsizey-texture_from_ffmpeg.getSize().y)/2;
    int offset_x=0;
    int offset_y=0;


/*
    for (int x=0; x<maze_plotsizex; x++) {
        for (int y=0; y<maze_plotsizey; y++) {
            pixel=myimage.getPixel(x,y);
            if (pixel.r>0 || pixel.g>0 || pixel.b>0) {
                maze_plot[x][y]=maze_plot[x][y]&127;
            }
        }
    }
*/

/*
    for (int x=0; x<max_x; x++) {
        for (int y=0; y<max_y; y++) {
            pixel=myimage.getPixel(x,y);
            pixel_l=myimage.getPixel((x-1+max_x)%max_x,y);
            pixel_ll=myimage.getPixel((x-2+max_x)%max_x,y);
            pixel_r=myimage.getPixel((x+1)%max_x,y);
            pixel_rr=myimage.getPixel((x+2)%max_x,y);
            pixel_u=myimage.getPixel(x,(y-1+max_y)%max_y);
            pixel_uu=myimage.getPixel(x,(y-2+max_y)%max_y);
            pixel_d=myimage.getPixel(x,(y+1)%max_y);
            pixel_dd=myimage.getPixel(x,(y+2)%max_y);
            pixel_rd=myimage.getPixel((x+1)%max_x,(y+1)%max_y);
            pixel_ru=myimage.getPixel((x+1)%max_x,(y-1+max_y)%max_y);
            pixel_ld=myimage.getPixel((x-1+max_x)%max_x,(y+1)%max_y);
            pixel_lu=myimage.getPixel((x-1+max_x)%max_x,(y-1+max_y)%max_y);
            if (pixel.r>0 || pixel.g>0 || pixel.b>0) set_c=1; else set_c=0;
            if (pixel_l.r>0 || pixel_l.g>0 || pixel_l.b>0) set_l=1; else set_l=0;
            if (pixel_ll.r>0 || pixel_ll.g>0 || pixel_ll.b>0) set_ll=1; else set_ll=0;
            if (pixel_r.r>0 || pixel_r.g>0 || pixel_r.b>0) set_r=1; else set_r=0;
            if (pixel_rr.r>0 || pixel_rr.g>0 || pixel_rr.b>0) set_rr=1; else set_rr=0;
            if (pixel_u.r>0 || pixel_u.g>0 || pixel_u.b>0) set_u=1; else set_u=0;
            if (pixel_uu.r>0 || pixel_uu.g>0 || pixel_uu.b>0) set_uu=1; else set_uu=0;
            if (pixel_d.r>0 || pixel_d.g>0 || pixel_d.b>0) set_d=1; else set_d=0;
            if (pixel_dd.r>0 || pixel_dd.g>0 || pixel_dd.b>0) set_dd=1; else set_dd=0;
            if (pixel_rd.r>0 || pixel_rd.g>0 || pixel_rd.b>0) set_rd=1; else set_rd=0;
            if (pixel_ru.r>0 || pixel_ru.g>0 || pixel_ru.b>0) set_ru=1; else set_ru=0;
            if (pixel_ld.r>0 || pixel_ld.g>0 || pixel_ld.b>0) set_ld=1; else set_ld=0;
            if (pixel_lu.r>0 || pixel_lu.g>0 || pixel_lu.b>0) set_lu=1; else set_lu=0;
            if (set_c==1) {
                            maze_plot[(x+offset_x-59+maze_plotsizex  )%maze_plotsizex][(y+offset_y-30+maze_plotsizey  )%maze_plotsizey]|=15;
                if (set_r) {
                            maze_plot[(x+offset_x-59+maze_plotsizex+1)%maze_plotsizex][(y+offset_y-30+maze_plotsizey  )%maze_plotsizey]|=15;
                }
                if (set_d) {
                            maze_plot[(x+offset_x-59+maze_plotsizex  )%maze_plotsizex][(y+offset_y-30+maze_plotsizey+1)%maze_plotsizey]|=15;
                }

                if (set_rr) {
                            maze_plot[(x+offset_x-59+maze_plotsizex+1)%maze_plotsizex][(y+offset_y-30+maze_plotsizey  )%maze_plotsizey]|=15;
                }
                if (set_dd) {
                            maze_plot[(x+offset_x-59+maze_plotsizex  )%maze_plotsizex][(y+offset_y-30+maze_plotsizey+1)%maze_plotsizey]|=15;
                }

                if (set_l) {
//                            maze_plot[(x+offset_x-59+maze_plotsizex  )%maze_plotsizex][(y+offset_y-30+maze_plotsizey  )%maze_plotsizey]|=8;
                }
                if (set_u) {
//                            maze_plot[(x+offset_x-59+maze_plotsizex  )%maze_plotsizex][(y+offset_y-30+maze_plotsizey  )%maze_plotsizey]|=2;
                }


//                if (set_rd) maze_plot[(x+offset_x-59+maze_plotsizex  )%maze_plotsizex][(y+offset_y-30+maze_plotsizey  )%maze_plotsizey]|=15;
//                if (set_lu) maze_plot[(x+offset_x-59+maze_plotsizex  )%maze_plotsizex][(y+offset_y-30+maze_plotsizey  )%maze_plotsizey]|=15;
//                if (set_ru) maze_plot[(x+offset_x-59+maze_plotsizex  )%maze_plotsizex][(y+offset_y-30+maze_plotsizey  )%maze_plotsizey]|=15;
//                if (set_ld) maze_plot[(x+offset_x-59+maze_plotsizex  )%maze_plotsizex][(y+offset_y-30+maze_plotsizey  )%maze_plotsizey]|=15;
//                if (set_l)  maze_plot[(x+offset_x-59+maze_plotsizex  )%maze_plotsizex][(y+offset_y-30+maze_plotsizey  )%maze_plotsizey]|=15;
//                if (set_u)  maze_plot[(x+offset_x-59+maze_plotsizex  )%maze_plotsizex][(y+offset_y-30+maze_plotsizey  )%maze_plotsizey]|=15;
            } else {
                if (  ((set_rr && set_r) || (set_dd && set_d))  || ( ((set_rr || set_rd) && (set_dd || set_rd)) && (!set_r && !set_d) )) {
                    maze_plot[(x+offset_x-59+maze_plotsizex  )%maze_plotsizex][(y+offset_y-30+maze_plotsizey  )%maze_plotsizey]|=15;
                }
            }
        }
    }
*/
/*
    for (int x=0; x<max_x; x++) {
        for (int y=0; y<max_y; y++) {
            pixel=myimage.getPixel(x,y);
            pixel_l=myimage.getPixel((x-1+max_x)%max_x,y);
            pixel_ll=myimage.getPixel((x-2+max_x)%max_x,y);
            pixel_r=myimage.getPixel((x+1)%max_x,y);
            pixel_rr=myimage.getPixel((x+2)%max_x,y);
            pixel_u=myimage.getPixel(x,(y-1+max_y)%max_y);
            pixel_uu=myimage.getPixel(x,(y-2+max_y)%max_y);
            pixel_d=myimage.getPixel(x,(y+1)%max_y);
            pixel_dd=myimage.getPixel(x,(y+2)%max_y);
            pixel_rd=myimage.getPixel((x+1)%max_x,(y+1)%max_y);
            pixel_ru=myimage.getPixel((x+1)%max_x,(y-1+max_y)%max_y);
            pixel_ld=myimage.getPixel((x-1+max_x)%max_x,(y+1)%max_y);
            pixel_lu=myimage.getPixel((x-1+max_x)%max_x,(y-1+max_y)%max_y);
            if (pixel.r>0 || pixel.g>0 || pixel.b>0) set_c=1; else set_c=0;
            if (pixel_l.r>0 || pixel_l.g>0 || pixel_l.b>0) set_l=1; else set_l=0;
            if (pixel_ll.r>0 || pixel_ll.g>0 || pixel_ll.b>0) set_ll=1; else set_ll=0;
            if (pixel_r.r>0 || pixel_r.g>0 || pixel_r.b>0) set_r=1; else set_r=0;
            if (pixel_rr.r>0 || pixel_rr.g>0 || pixel_rr.b>0) set_rr=1; else set_rr=0;
            if (pixel_u.r>0 || pixel_u.g>0 || pixel_u.b>0) set_u=1; else set_u=0;
            if (pixel_uu.r>0 || pixel_uu.g>0 || pixel_uu.b>0) set_uu=1; else set_uu=0;
            if (pixel_d.r>0 || pixel_d.g>0 || pixel_d.b>0) set_d=1; else set_d=0;
            if (pixel_dd.r>0 || pixel_dd.g>0 || pixel_dd.b>0) set_dd=1; else set_dd=0;
            if (pixel_rd.r>0 || pixel_rd.g>0 || pixel_rd.b>0) set_rd=1; else set_rd=0;
            if (pixel_ru.r>0 || pixel_ru.g>0 || pixel_ru.b>0) set_ru=1; else set_ru=0;
            if (pixel_ld.r>0 || pixel_ld.g>0 || pixel_ld.b>0) set_ld=1; else set_ld=0;
            if (pixel_lu.r>0 || pixel_lu.g>0 || pixel_lu.b>0) set_lu=1; else set_lu=0;


            if (set_c==0) {
                if (set_r==0 && set_rr==0) {
                     maze_plot[(x+offset_x-59+maze_plotsizex+1)%maze_plotsizex][(y+offset_y-30+maze_plotsizey  )%maze_plotsizey]&=(15-2);
                     maze_plot[(x+offset_x-59+maze_plotsizex+1)%maze_plotsizex][(y+offset_y-30+maze_plotsizey+1)%maze_plotsizey]&=(15-1);
                }
                if (set_d==0 && set_dd==0) {
                     maze_plot[(x+offset_x-59+maze_plotsizex  )%maze_plotsizex][(y+offset_y-30+maze_plotsizey+1)%maze_plotsizey]&=(15-8);
                     maze_plot[(x+offset_x-59+maze_plotsizex+1)%maze_plotsizex][(y+offset_y-30+maze_plotsizey+1)%maze_plotsizey]&=(15-4);
                }
                if (set_l==0 && set_ll==0) {
                     maze_plot[(x+offset_x-59+maze_plotsizex  )%maze_plotsizex][(y+offset_y-30+maze_plotsizey  )%maze_plotsizey]&=(15-2);
                     maze_plot[(x+offset_x-59+maze_plotsizex  )%maze_plotsizex][(y+offset_y-30+maze_plotsizey+1)%maze_plotsizey]&=(15-1);
                }
                if (set_u==0 && set_uu==0) {
                     maze_plot[(x+offset_x-59+maze_plotsizex  )%maze_plotsizex][(y+offset_y-30+maze_plotsizey  )%maze_plotsizey]&=(15-8);
                     maze_plot[(x+offset_x-59+maze_plotsizex+1)%maze_plotsizex][(y+offset_y-30+maze_plotsizey  )%maze_plotsizey]&=(15-4);
                }
            } else {

                if (set_rr==0 && set_r==0 && set_ll==0 && set_l==0) {
                    maze_plot[(x+offset_x-59+maze_plotsizex+1)%maze_plotsizex][(y+offset_y-30+maze_plotsizey  )%maze_plotsizey]&=(15-4);
                    maze_plot[(x+offset_x-59+maze_plotsizex+1)%maze_plotsizex][(y+offset_y-30+maze_plotsizey  )%maze_plotsizey]&=(15-2);
                }
                if (set_dd==0 && set_d==0 && set_uu==0 && set_u==0) {
                    maze_plot[(x+offset_x-59+maze_plotsizex  )%maze_plotsizex][(y+offset_y-30+maze_plotsizey+1)%maze_plotsizey]&=(15-1);
                    maze_plot[(x+offset_x-59+maze_plotsizex  )%maze_plotsizex][(y+offset_y-30+maze_plotsizey+1)%maze_plotsizey]&=(15-8);
                }
            }
        }
    }

    for (int x=0; x<max_x; x++) {
        for (int y=0; y<max_y; y++) {
            if ((maze_plot[(x+offset_x-59+maze_plotsizex-1)%maze_plotsizex][(y+offset_y-30+maze_plotsizey  )%maze_plotsizey]&8)==0)
                maze_plot[(x+offset_x-59+maze_plotsizex  )%maze_plotsizex][(y+offset_y-30+maze_plotsizey  )%maze_plotsizey]&=(15-4);
            if ((maze_plot[(x+offset_x-59+maze_plotsizex+1)%maze_plotsizex][(y+offset_y-30+maze_plotsizey  )%maze_plotsizey]&4)==0)
                maze_plot[(x+offset_x-59+maze_plotsizex  )%maze_plotsizex][(y+offset_y-30+maze_plotsizey  )%maze_plotsizey]&=(15-8);
            if ((maze_plot[(x+offset_x-59+maze_plotsizex  )%maze_plotsizex][(y+offset_y-30+maze_plotsizey-1)%maze_plotsizey]&2)==0)
                maze_plot[(x+offset_x-59+maze_plotsizex  )%maze_plotsizex][(y+offset_y-30+maze_plotsizey  )%maze_plotsizey]&=(15-1);
            if ((maze_plot[(x+offset_x-59+maze_plotsizex  )%maze_plotsizex][(y+offset_y-30+maze_plotsizey+1)%maze_plotsizey]&1)==0)
                maze_plot[(x+offset_x-59+maze_plotsizex  )%maze_plotsizex][(y+offset_y-30+maze_plotsizey  )%maze_plotsizey]&=(15-2);
        }
    }
*/

/*
    for (int x=0; x<max_x; x++) {
        for (int y=0; y<max_y; y++) {
            pixel=myimage.getPixel(x,y);
            if (pixel.r>0 || pixel.g>0 || pixel.b>0) {
                maze_plot[(x+offset_x-59+maze_plotsizex)%maze_plotsizex][(y+offset_y-30+maze_plotsizey)%maze_plotsizey]=
                maze_plot[(x+offset_x-59+maze_plotsizex)%maze_plotsizex][(y+offset_y-30+maze_plotsizey)%maze_plotsizey]|128;
            }
        }
    }
*/



    for (int x=0; x<max_x; x++) {
        for (int y=0; y<max_y; y++) {
            pixel=myimage.getPixel(x,y);
            if (pixel.r>0 || pixel.g>0 || pixel.b>0) {
                maze_plot[(x+offset_x-59+maze_plotsizex)%maze_plotsizex][(y+offset_y-30+maze_plotsizey)%maze_plotsizey]=
                maze_plot[(x+offset_x-59+maze_plotsizex)%maze_plotsizex][(y+offset_y-30+maze_plotsizey)%maze_plotsizey]|15;
            }
        }
    }

    for (int x=offset_x; x<max_x+offset_x; x++) {
        for (int y=offset_y; y<max_y+offset_y; y++) {
            if ((maze_plot[(x-1-59+maze_plotsizex)%maze_plotsizex][(y-  30+maze_plotsizey)%maze_plotsizey]&8)==0)
                 maze_plot[(x-  59+maze_plotsizex)%maze_plotsizex][(y-  30+maze_plotsizey)%maze_plotsizey]=
                 maze_plot[(x-  59+maze_plotsizex)%maze_plotsizex][(y-  30+maze_plotsizey)%maze_plotsizey]&(15-4);
            if ((maze_plot[(x+1-59+maze_plotsizex)%maze_plotsizex][(y-  30+maze_plotsizey)%maze_plotsizey]&4)==0)
                 maze_plot[(x-  59+maze_plotsizex)%maze_plotsizex][(y-  30+maze_plotsizey)%maze_plotsizey]=
                 maze_plot[(x-  59+maze_plotsizex)%maze_plotsizex][(y-  30+maze_plotsizey)%maze_plotsizey]&(15-8);
            if ((maze_plot[(x-  59+maze_plotsizex)%maze_plotsizex][(y-1-30+maze_plotsizey)%maze_plotsizey]&2)==0)
                 maze_plot[(x-  59+maze_plotsizex)%maze_plotsizex][(y-  30+maze_plotsizey)%maze_plotsizey]=
                 maze_plot[(x-  59+maze_plotsizex)%maze_plotsizex][(y-  30+maze_plotsizey)%maze_plotsizey]&(15-1);
            if ((maze_plot[(x-  59+maze_plotsizex)%maze_plotsizex][(y+1-30+maze_plotsizey)%maze_plotsizey]&1)==0)
                 maze_plot[(x-  59+maze_plotsizex)%maze_plotsizex][(y-  30+maze_plotsizey)%maze_plotsizey]=
                 maze_plot[(x-  59+maze_plotsizex)%maze_plotsizex][(y-  30+maze_plotsizey)%maze_plotsizey]&(15-2);
        }
    }

}

void ffmpegfile_to_maze2() {
    int tot=mazesizey;
    int scount=100;
    int x,y;


    sf::Image myimage;

    sf::Color pixel; int set_c;
    sf::Color pixel_l; int set_l;
    sf::Color pixel_r; int set_r;
    sf::Color pixel_u; int set_u;
    sf::Color pixel_d; int set_d;

    if (ffmpegfile==0) {
        if (ffmpegfile==1) {
            sprintf(error_msg2,"NO PICTURE FROM SHIFT-P");
            error_flag2=1;
            return;
        }

        int max_x=texture_from_ffmpeg.getSize().x;
        int max_y=texture_from_ffmpeg.getSize().y;

        if (texture_from_ffmpeg.getSize().x>BITMAPSX*30*2) {
            sprintf(error_msg2,"SIZE PICTURE X=%d > SIZE MAZE X=%d TRUNCATING",texture_from_ffmpeg.getSize().x,BITMAPSX*30*2);
            error_flag2=1;
            max_x=BITMAPSX*30*2;
        }
        if (texture_from_ffmpeg.getSize().y>BITMAPSY*15*2) {
            sprintf(error_msg3,"SIZE PICTURE Y=%d > SIZE MAZE Y=%d  TRUNCATING",texture_from_ffmpeg.getSize().y,BITMAPSY*15*2);
            error_flag3=1;
            max_y=BITMAPSY*15*2;
        }
        myimage=texture_from_ffmpeg.copyToImage();
        for (y=0; y<=mazesizey; y++)
        {
            scount--;
            if (scount==0)
            {
                scount=1000;
                sprintf(line,"CLEANING MAZE LINE=%d/%d",y,tot);
                blitter(line,1);
            }
            for (x=0; x<=mazesizex; x++)
            {

                if (x==0 || y==0)
                    Maze[x][y]='O';
                else
                    Maze[x][y]='%';
            }
        }
        sprintf(line,"CLEANING MAZE LINE=%d/%d",y,tot);
        blitter(line,1);

        for (x=0; x<max_x; x++) {
            for (y=0; y<max_y; y++) {
                pixel=myimage.getPixel(x,y);
                pixel_l=myimage.getPixel((x-1+max_x)%max_x,y);
                pixel_r=myimage.getPixel((x+1)%max_x,y);
                pixel_u=myimage.getPixel(x,(y-1+max_y)%max_y);
                pixel_d=myimage.getPixel(x,(y+1)%max_y);
                if (pixel.r>0 || pixel.g>0 || pixel.b>0) set_c=1; else set_c=0;
                if (pixel_l.r>0 || pixel_l.g>0 || pixel_l.b>0) set_l=1; else set_l=0;
                if (pixel_r.r>0 || pixel_r.g>0 || pixel_r.b>0) set_r=1; else set_r=0;
                if (pixel_u.r>0 || pixel_u.g>0 || pixel_u.b>0) set_u=1; else set_u=0;
                if (pixel_d.r>0 || pixel_d.g>0 || pixel_d.b>0) set_d=1; else set_d=0;
                if (pixel.r==0 && pixel.g==0 && pixel.b==0) {
                    Maze[x+1][y+1]=' ';
                } else if (pixel.r==255 && pixel.g==255 && pixel.b==0) {
                    Maze[x+1][y+1]='*';
                } else if (pixel.r==255 && pixel.g==0 && pixel.b==255) {
                    Maze[x+1][y+1]='O';
                } else if (pixel.r==255 && pixel.g==255 && pixel.b==255) {
                    Maze[x+1][y+1]='%';
                } else if (pixel.r==0 && pixel.g==255 && pixel.b==0) {
                    Maze[x+1][y+1]='-';
                } else if (pixel.r==0 && pixel.g==0 && pixel.b==255) {
                    Maze[x+1][y+1]='|';
                }
            }
        }
        zetom();
    } else {
        reversed_zetom();
        int max_x=BITMAPSX*30;
        int max_y=BITMAPSY*15;
//        if (max_x*2>=16384) max_x=16384/2;
//        if (max_y*2>=16384) max_y=16384/2;
        myimage.create(max_x*2,max_y*2);
        if (myimage.getSize().x!=max_x*2 || myimage.getSize().y!=max_y*2) {
            sprintf(error_msg3,"CAN NOT CREATE IMAGE SIZE X=%d Y=%d",BITMAPSX*30*2,BITMAPSY*15*2);
            error_flag3=1;
            return;
        }
        for (x=0; x<max_x*2; x++) {
            for (y=0; y<max_y*2; y++) {
                pixel=sf::Color(255,0,0,255);
                if (Maze[x+1][y+1]==' ') pixel=sf::Color(0,0,0,255);
                if (Maze[x+1][y+1]=='%') pixel=sf::Color(255,255,255,255);
                if (Maze[x+1][y+1]=='*') pixel=sf::Color(0,0,0,255);
                if (Maze[x+1][y+1]=='O') pixel=sf::Color(255,0,255,255);
                if (Maze[x+1][y+1]=='-') pixel=sf::Color(0,0,0,255);
                if (Maze[x+1][y+1]=='|') pixel=sf::Color(0,0,0,255);
/*
                pixel=sf::Color(255,0,0,255);
                if (Maze[x+1][y+1]==' ') pixel=sf::Color(0,0,0,255);
                if (Maze[x+1][y+1]=='%') pixel=sf::Color(255,255,255,255);
                if (Maze[x+1][y+1]=='*') pixel=sf::Color(255,255,0,255);
                if (Maze[x+1][y+1]=='O') pixel=sf::Color(255,0,255,255);
                if (Maze[x+1][y+1]=='-') pixel=sf::Color(0,255,0,255);
                if (Maze[x+1][y+1]=='|') pixel=sf::Color(0,0,255,255);;
*/
                myimage.setPixel(x,y,pixel);
            }
        }
        texture_from_ffmpeg.create(max_x*2,max_y*2);
        texture_from_ffmpeg.loadFromImage(myimage);
        ffmpegfile=0;
        sprite_from_ffmpeg.setTexture(texture_from_ffmpeg,true);
        sprite_from_ffmpeg.setScale(1.0,1.0);
        rot_speed_ffmpeg=0.0;
        scale_now=1.0;
        setffmpegfile();
    }
}


void reverse_maze() {
    for (int x=0; x<maze_plotsizex; x++) {
        for (int y=0; y<maze_plotsizey; y++) {
                if (maze_plot[(x-59+maze_plotsizex)%maze_plotsizex][(y-30+maze_plotsizey)%maze_plotsizey]>0)
                    maze_plot[(x-59+maze_plotsizex)%maze_plotsizex][(y-30+maze_plotsizey)%maze_plotsizey]=0;
                else
                    maze_plot[(x-59+maze_plotsizex)%maze_plotsizex][(y-30+maze_plotsizey)%maze_plotsizey]=15;
        }
    }

    for (int x=0; x<maze_plotsizex; x++) {
        for (int y=0; y<maze_plotsizey; y++) {

            if ((maze_plot[(x-1-59+maze_plotsizex)%maze_plotsizex][(y-  30+maze_plotsizey)%maze_plotsizey]&8)==0)
                 maze_plot[(x-  59+maze_plotsizex)%maze_plotsizex][(y-  30+maze_plotsizey)%maze_plotsizey]=
                 maze_plot[(x-  59+maze_plotsizex)%maze_plotsizex][(y-  30+maze_plotsizey)%maze_plotsizey]&(15-4);
            if ((maze_plot[(x+1-59+maze_plotsizex)%maze_plotsizex][(y-  30+maze_plotsizey)%maze_plotsizey]&4)==0)
                 maze_plot[(x-  59+maze_plotsizex)%maze_plotsizex][(y-  30+maze_plotsizey)%maze_plotsizey]=
                 maze_plot[(x-  59+maze_plotsizex)%maze_plotsizex][(y-  30+maze_plotsizey)%maze_plotsizey]&(15-8);
            if ((maze_plot[(x-  59+maze_plotsizex)%maze_plotsizex][(y-1-30+maze_plotsizey)%maze_plotsizey]&2)==0)
                 maze_plot[(x-  59+maze_plotsizex)%maze_plotsizex][(y-  30+maze_plotsizey)%maze_plotsizey]=
                 maze_plot[(x-  59+maze_plotsizex)%maze_plotsizex][(y-  30+maze_plotsizey)%maze_plotsizey]&(15-1);
            if ((maze_plot[(x-  59+maze_plotsizex)%maze_plotsizex][(y+1-30+maze_plotsizey)%maze_plotsizey]&1)==0)
                 maze_plot[(x-  59+maze_plotsizex)%maze_plotsizex][(y-  30+maze_plotsizey)%maze_plotsizey]=
                 maze_plot[(x-  59+maze_plotsizex)%maze_plotsizex][(y-  30+maze_plotsizey)%maze_plotsizey]&(15-2);

/*
            if (!maze_plot[(x-1-59+maze_plotsizex)%maze_plotsizex][(y-  30+maze_plotsizey)%maze_plotsizey]&16)
                maze_plot[(x-  59+maze_plotsizex)%maze_plotsizex][(y-  30+maze_plotsizey)%maze_plotsizey]&=15-4;
            if (!maze_plot[(x+1-59+maze_plotsizex)%maze_plotsizex][(y-  30+maze_plotsizey)%maze_plotsizey]&16)
                maze_plot[(x-  59+maze_plotsizex)%maze_plotsizex][(y-  30+maze_plotsizey)%maze_plotsizey]&=15-8;
            if (!maze_plot[(x-  59+maze_plotsizex)%maze_plotsizex][(y-1-30+maze_plotsizey)%maze_plotsizey]&16)
                maze_plot[(x-  59+maze_plotsizex)%maze_plotsizex][(y-  30+maze_plotsizey)%maze_plotsizey]&=15-1;
            if (!maze_plot[(x-  59+maze_plotsizex)%maze_plotsizex][(y+1-30+maze_plotsizey)%maze_plotsizey]&16)
                maze_plot[(x-  59+maze_plotsizex)%maze_plotsizex][(y-  30+maze_plotsizey)%maze_plotsizey]&=15-2;

            if (maze_plot[(x-1-59+maze_plotsizex)%maze_plotsizex][(y-  30+maze_plotsizey)%maze_plotsizey]&16)
                maze_plot[(x-  59+maze_plotsizex)%maze_plotsizex][(y-  30+maze_plotsizey)%maze_plotsizey]|=4;
            if (maze_plot[(x+1-59+maze_plotsizex)%maze_plotsizex][(y-  30+maze_plotsizey)%maze_plotsizey]&16)
                maze_plot[(x-  59+maze_plotsizex)%maze_plotsizex][(y-  30+maze_plotsizey)%maze_plotsizey]|=8;
            if (maze_plot[(x-  59+maze_plotsizex)%maze_plotsizex][(y-1-30+maze_plotsizey)%maze_plotsizey]&16)
                maze_plot[(x-  59+maze_plotsizex)%maze_plotsizex][(y-  30+maze_plotsizey)%maze_plotsizey]|=1;
            if (maze_plot[(x-  59+maze_plotsizex)%maze_plotsizex][(y+1-30+maze_plotsizey)%maze_plotsizey]&16)
                maze_plot[(x-  59+maze_plotsizex)%maze_plotsizex][(y-  30+maze_plotsizey)%maze_plotsizey]|=2;
*/

        }
    }
    for (int x=0; x<maze_plotsizex; x++) {
        for (int y=0; y<maze_plotsizey; y++) {
                maze_plot[(x-  59+maze_plotsizex)%maze_plotsizex][(y-  30+maze_plotsizey)%maze_plotsizey]&=15;
        }
    }
}


int pictures_to_ffmpegfile() {
    char naam[2000];

    sf::Image myimage;
    myimage.create(BITMAPSX,BITMAPSY);
    int total_pictures_level=0;
    int totalx,totaly;

    sprintf(naam,"%s/%dx%d/%03d",LEVELDIR,BITMAPSX,BITMAPSY,level);
    DIR *dr = opendir(naam);

    SFMLView1.setVerticalSyncEnabled(false);
    if (dr == NULL)  // opendir returns NULL if couldn't open directory
    {
        strcpy(error_msg2,"Could not open current directory");
        error_flag2=1;
        return -1;
    }
    struct dirent *de;
    char mask[300];
    char filename[300];
    if (drawmazes==0)
        strcpy(mask,"picture.%d.%d.png");
    else
        strcpy(mask,"picture_maze.%d.%d.png");

    while ((de = readdir(dr)) != NULL) {
        strcpy(filename,de->d_name);
        if (sscanf(filename, mask, &totaly, &totalx )==2) {
            myimage.setPixel(totalx,totaly,sf::Color(255,255,255,255));
            total_pictures_level++;
            sprintf(line,"SCANNING FILES: FOUND: %d OF %d  X=%06d,Y=%06d  %s",total_pictures_level,BITMAPSX*BITMAPSY,totalx,totaly,filename);
            printf(line);printf("\n");
            blitter(line,1);
        } else {
            sprintf(line,"SCANNING FILES: FOUND: %d OF %d  SKIPPING           %s",total_pictures_level,BITMAPSX*BITMAPSY,filename);
            printf(line);printf("\n");
            blitter(line,1);
        }
    }
    closedir(dr);
    if (sync==1) SFMLView1.setVerticalSyncEnabled(true);

    texture_from_ffmpeg.create(BITMAPSX,BITMAPSY);
    texture_from_ffmpeg.loadFromImage(myimage);
    ffmpegfile=0;
    sprite_from_ffmpeg.setTexture(texture_from_ffmpeg,true);
    sprite_from_ffmpeg.setScale(1.0,1.0);
    rot_speed_ffmpeg=0.0;
    scale_now=1.0;
    setffmpegfile();
}

int pictures_to_ffmpegfile_2() {
    char naam[2000];

    sf::Image myimage;
    myimage.create(BITMAPSX,BITMAPSY);
    int total_pictures_level=0;
    int totalx,totaly;
    int totalx_dir,totaly_dir;

    char mask[300];
    strcpy(mask,"picture.%d.%d.png");
    for (totaly=0; totaly<BITMAPSY; totaly++) {
        char filename[300];
        struct dirent *de;

        sprintf(naam,"%s/map.z%d/pictures/y%d",
                LEVELDIR,get_map_zoom,offset_picture_y+totaly);
        DIR *dr;
        dr = opendir(naam);

        SFMLView1.setVerticalSyncEnabled(false);
        if (dr == NULL)  // opendir returns NULL if couldn't open directory
        {
            continue;
        }

        while ((de = readdir(dr)) != NULL) {
            strcpy(filename,de->d_name);
            if (sscanf(filename, mask, &totaly_dir, &totalx_dir )==2) {
                if (totaly_dir-offset_picture_y>=0 && totaly_dir-offset_picture_y<BITMAPSY)
                    if (totalx_dir-offset_picture_x>=0 && totalx_dir-offset_picture_x<BITMAPSX) {
                        myimage.setPixel(totalx_dir-offset_picture_x,totaly_dir-offset_picture_y,sf::Color(255,255,255,255));
                        total_pictures_level++;
                        sprintf(line,"SCANNING FILES: FOUND: %d OF %d  X=%06d,Y=%06d  %s",
                                total_pictures_level,BITMAPSX*BITMAPSY,totalx_dir-offset_picture_x,totaly_dir-offset_picture_y,filename);
//                        printf(line);printf("\n");
                        blitter(line,1);
                    }
            } else {
                sprintf(line,"SCANNING FILES: FOUND: %d OF %d  SKIPPING           %s",total_pictures_level,BITMAPSX*BITMAPSY,filename);
//                printf(line);printf("\n");
                blitter(line,1);
            }
        }
        closedir(dr);
        if (sync==1) SFMLView1.setVerticalSyncEnabled(true);



/*        for (totalx=0; totalx<BITMAPSX; totalx++) {

            sprintf(naam,"%s/map.z%d/pictures/y%d/picture.%06d.%06d.png",
                    LEVELDIR,get_map_zoom,offset_picture_y+totaly,offset_picture_y+totaly,offset_picture_x+totalx);
            if (file_exists(naam)) {
                total_pictures_level++;
                myimage.setPixel(totalx,totaly,sf::Color(255,255,255,255));
            }
            sprintf(line,"SCANNING FILES X=%3d,Y=%3d %d/%d %s",totalx,totaly,total_pictures_level,BITMAPSX*BITMAPSY,naam);
            blitter(line,1);
        }
*/
        kiki();
        if (ESCAPE==1) {
            ESCAPE=0;
            goexit=0;
            totaly=BITMAPSY;
            totalx=BITMAPSX;
        }
    }

    texture_from_ffmpeg.create(BITMAPSX,BITMAPSY);
    texture_from_ffmpeg.loadFromImage(myimage);
    ffmpegfile=0;
    sprite_from_ffmpeg.setTexture(texture_from_ffmpeg,true);
    sprite_from_ffmpeg.setScale(1.0,1.0);
    rot_speed_ffmpeg=0.0;
    scale_now=1.0;
    setffmpegfile();
}

extern sf::RenderTexture *texturemaxinmempoint[];
extern int  **used2;

int pictures_to_ffmpegfile_3() {
    char naam[2000];
    double avg_x=0.0;
    double avg_y=0.0;
    int total_pictures_level=0;
    int totalx,totaly;
    int totalx_dir,totaly_dir;
    int tiles_in_map=(int)pow(2.0,(get_map_zoom));
    int left=-1;
    int top=-1;
    int old_left=-1;
    int old_top=-1;

    char masky[300];
    char maskx[300];
    char filenamey[300];
    struct dirent *dey;
//    strcpy(masky,"%d");

    if (strlen(SAS_DIR)>0) {
        strcpy(masky,"%d.png");
        strcpy(maskx,"%d.png");
        sprintf(naam,"%s/z%d", SAS_DIR,get_map_zoom);
    } else {
        strcpy(masky,"y%d.png");
        strcpy(maskx,"x%d.png");
        sprintf(naam,"%s/map.z%d", LEVELDIR,get_map_zoom);
    }
//    strcpy(maskx,"%d.png");

    SFMLView1.setVerticalSyncEnabled(false);

//    sprintf(naam,"C:/SAS/cache_gmt/osm_gps_tile/z19");
    DIR *dry;
    dry = opendir(naam);
    if (dry == NULL)  // opendir returns NULL if couldn't open directory
    {
        return -1;
    }
    while ((dey = readdir(dry)) != NULL) {
        strcpy(filenamey,dey->d_name);
//        printf("filenamey=%s\n",filenamey);
        if (sscanf(filenamey, masky, &totaly_dir )==1) {
            if (top==-1 || totaly_dir>top) top=totaly_dir;
            char filenamex[300];
            struct dirent *dex;
//            sprintf(naam,"C:/SAS/cache_gmt/osm_gps_tile/z19/%d",totaly_dir);
            if (strlen(SAS_DIR)>0) {
                sprintf(naam,"%s/z%d/%d", SAS_DIR,get_map_zoom,totaly_dir);
            } else {
                sprintf(naam,"%s/map.z%d/y%d", LEVELDIR,get_map_zoom,totaly_dir);

            }
            DIR *drx;
            drx = opendir(naam);
            if (drx == NULL)
            {
                continue;
            }
            int one;
            one=1;
            while ((dex = readdir(drx)) != NULL) {
                strcpy(filenamex,dex->d_name);
//                printf("filenamex=%s\n",filenamex);
                if (sscanf(filenamex, maskx, &totalx_dir )==1) {
                    if (one==1) { left=totalx_dir; one=0; }
                    plot_pixel(totalx_dir,totaly_dir,sf::Color(0,64,0,255),sf::Vector2f(1.0,1.0));
                    total_pictures_level++;
                    avg_x+=totalx_dir;
                    avg_y+=totaly_dir;
                }
            }
            closedir(drx);
        }
        sprintf(line,"SCANNING FILES: FOUND: %d OF %d x %d  X=%06d,Y=%06d", total_pictures_level,tiles_in_map,tiles_in_map,totalx_dir,totaly_dir);
        if (left!=-1 && top !=-1 && (old_left!=left || old_top!=top)) {
            picturex=(int) ( ( (left+maxpixelsx)%maxpixelsx ) / 1920 );
            posx=(left+maxpixelsx)%maxpixelsx-1920*picturex;
            posx=-posx;
            fposx=posx;
            picturex=(picturex+totalpicturex)%totalpicturex;

            picturey=(int)((top-1080+maxpixelsy)%maxpixelsy)/1080;
            posy=(top-1080+maxpixelsy)%maxpixelsy-1080*picturey;
            picturey=(picturey+totalpicturey)%totalpicturey;
            posy=-posy;
            fposy=posy;
            forced_jump=1;
            follow_ghost_pos();
        }
        old_left=left;old_top=top;
        blitter(line,1);
        kiki();
        if (ESCAPE==1) {
            ESCAPE=0;
            goexit=0;
            break;
        }
    }
    closedir(dry);
    if (total_pictures_level>0) {
        avg_x=avg_x/(double)total_pictures_level;
        avg_y=avg_y/(double)total_pictures_level;
        picturex=(int) ( ( ((int)avg_x-1920/2+maxpixelsx)%maxpixelsx ) / 1920 );
        posx=((int)avg_x-1920/2+maxpixelsx)%maxpixelsx-1920*picturex;
        posx=-posx;
        fposx=posx;
        picturex=(picturex+totalpicturex)%totalpicturex;

        picturey=(int)(((int)avg_y-1080/2+maxpixelsy)%maxpixelsy)/1080;
        posy=((int)avg_y-1080/2+maxpixelsy)%maxpixelsy-1080*picturey;
        picturey=(picturey+totalpicturey)%totalpicturey;
        posy=-posy;
        fposy=posy;
        forced_jump=1;
        follow_ghost_pos();
    }
    if (sync==1) SFMLView1.setVerticalSyncEnabled(true);
}

int pictures_to_ffmpegfile_4() {
    char naam[2000];
    double avg_x=0.0;
    double avg_y=0.0;
    int total_pictures_level=0;
    int totalx,totaly;
    int totalx_dir,totaly_dir;
    int tiles_in_mapx=(int)(pow(2.0,(get_map_zoom))*256.0/1920.0+1);
    int tiles_in_mapy=(int)(pow(2.0,(get_map_zoom))*256.0/1080.0+1);
    int left=-1;
    int top=-1;
    int old_left=-1;
    int old_top=-1;

    char masky[300];
//    strcpy(masky,"%d");
    strcpy(masky,"y%d");
    char maskx[300];
//    strcpy(maskx,"%d.png");
    strcpy(maskx,"picture.%d.%d.png");

    SFMLView1.setVerticalSyncEnabled(false);

    char filenamey[300];
    struct dirent *dey;
//    sprintf(naam,"C:/SAS/cache_gmt/osm_gps_tile/z19");
    sprintf(naam,"%s/map.z%d/pictures", LEVELDIR,get_map_zoom);
    DIR *dry;
    dry = opendir(naam);
    if (dry == NULL)  // opendir returns NULL if couldn't open directory
    {
        return -1;
    }
    while ((dey = readdir(dry)) != NULL) {
        strcpy(filenamey,dey->d_name);
//        printf("filenamey=%s\n",filenamey);
        if (sscanf(filenamey, masky, &totaly_dir )==1) {
            if (top==-1 || totaly_dir*1080.0/256.0>top) top=totaly_dir*1080.0/256.0;
            char filenamex[300];
            struct dirent *dex;
//            sprintf(naam,"C:/SAS/cache_gmt/osm_gps_tile/z19/%d",totaly_dir);
            sprintf(naam,"%s/map.z%d/pictures/y%d", LEVELDIR,get_map_zoom,totaly_dir);
            DIR *drx;
            drx = opendir(naam);
            if (drx == NULL)
            {
                continue;
            }
            int one;
            one=1;
            while ((dex = readdir(drx)) != NULL) {
                strcpy(filenamex,dex->d_name);
//                printf("filenamex=%s\n",filenamex);
                if (sscanf(filenamex, maskx, &totaly_dir, &totalx_dir)==2) {
                    if (one==1) { left=totalx_dir*1920.0/256.0; one=0; }
                    plot_pixel((float)totalx_dir*1920.0/256.0,(float)totaly_dir*1080.0/256.0,sf::Color(64,0,0,255),sf::Vector2f(1920.0/256.0,1080.0/256.0));
                    total_pictures_level++;
                    avg_x+=totalx_dir*1920.0/256.0;
                    avg_y+=totaly_dir*1080.0/256.0;
                }
            }
            closedir(drx);
        }
        sprintf(line,"SCANNING FILES: FOUND: %d OF %d x %d  X=%06d,Y=%06d", total_pictures_level,tiles_in_mapx,tiles_in_mapy,totalx_dir,totaly_dir);
        if (left!=-1 && top !=-1 && (old_left!=left || old_top!=top)) {
            picturex=(int) ( ( (left+maxpixelsx)%maxpixelsx ) / 1920 );
            posx=(left+maxpixelsx)%maxpixelsx-1920*picturex;
            posx=-posx;
            fposx=posx;
            picturex=(picturex+totalpicturex)%totalpicturex;

            picturey=(int)((top-1080+maxpixelsy)%maxpixelsy)/1080;
            posy=(top-1080+maxpixelsy)%maxpixelsy-1080*picturey;
            picturey=(picturey+totalpicturey)%totalpicturey;
            posy=-posy;
            fposy=posy;
            forced_jump=1;
            follow_ghost_pos();
        }
        old_left=left;old_top=top;
        blitter(line,1);
        kiki();
        if (ESCAPE==1) {
            ESCAPE=0;
            goexit=0;
            break;
        }
    }
    closedir(dry);
    if (total_pictures_level>0) {
        avg_x=avg_x/(double)total_pictures_level;
        avg_y=avg_y/(double)total_pictures_level;
        picturex=(int) ( ( ((int)avg_x-1920/2+maxpixelsx)%maxpixelsx ) / 1920 );
        posx=((int)avg_x-1920/2+maxpixelsx)%maxpixelsx-1920*picturex;
        posx=-posx;
        fposx=posx;
        picturex=(picturex+totalpicturex)%totalpicturex;

        picturey=(int)(((int)avg_y-1080/2+maxpixelsy)%maxpixelsy)/1080;
        posy=((int)avg_y-1080/2+maxpixelsy)%maxpixelsy-1080*picturey;
        picturey=(picturey+totalpicturey)%totalpicturey;
        posy=-posy;
        fposy=posy;
        forced_jump=1;
        follow_ghost_pos();
    }
    if (sync==1) SFMLView1.setVerticalSyncEnabled(true);
}

extern char **changed;

void plot_pixel(float x, float y, sf::Color mcolor, sf::Vector2f msize) {
    static int prevx=-1,prevy=-1;
    static int first=1;
    static sf::RectangleShape square;

    int picturex=(int)x/1920;
    float posx=x-1920*picturex;
    picturex=(picturex+totalpicturex)%totalpicturex;

    int picturey=(int)y/1080;
    float posy=y-1080*picturey;
    picturey=(picturey+totalpicturey)%totalpicturey;

    ReadOneBitmap(picturex,picturey);
    if (first==1) {
        first=0;
        square.setOrigin(0.0,0.0);
//        square.setOutlineColor(sf::Color(border_col_r,border_col_g,border_col_b,0));
        square.setOutlineThickness(0.0);
    }
    square.setSize(msize);
    square.setFillColor(mcolor);
    square.setPosition(posx,posy);
    texturemaxinmempoint[used2[picturex][picturey]]->draw(square,sf::BlendAdd);
//    texturemaxinmempoint[used2[picturex][picturey]]->display();

    if (prevx!=-1) {
        if (prevx!=picturex || prevy!=picturey) {
            texturemaxinmempoint[used2[prevx][prevy]]->display();
        }
        if (changed[picturex][picturey]==0)
        {
            changed[picturex][picturey]=1;
            totalchanged++;
        }
    }

    prevx=picturex;
    prevy=picturey;
}

extern int hoog;
extern int breed;

void maze_to_ffmpeg() {
    sf::Image myimage;
//    int max_x=breed;
//    int max_y=hoog;
    int max_x=BITMAPSX*30;
    int max_y=BITMAPSY*15;
    sf::Color pixel;
    int x,y;

    reversed_zetom();


    myimage.create(max_x*2+2,max_y*2+2);

    if (myimage.getSize().x!=max_x*2+2 || myimage.getSize().y!=max_y*2+2) {
        sprintf(error_msg3,"CAN NOT CREATE IMAGE SIZE X=%d Y=%d",BITMAPSX*30*2,BITMAPSY*15*2);
        error_flag3=1;
        return;
    }
    for (x=0; x<max_x*2; x++) {
        for (y=0; y<max_y*2; y++) {
            pixel=sf::Color(0,0,0,255);
            if (Maze[x+1][y+1]=='%') pixel=sf::Color(0,0,0,255);
            if (Maze[x+1][y+1]==' ') pixel=sf::Color(255,255,255,255);
                if (Maze[x+1][y+1]=='*') pixel=sf::Color(254,254,254,255);
//                if (Maze[x+1][y+1]=='O') pixel=sf::Color(255,0,255,255);
                if (Maze[x+1][y+1]=='-') pixel=sf::Color(128,128,128,255);
                if (Maze[x+1][y+1]=='|') pixel=sf::Color(127,127,127,255);
/*
            pixel=sf::Color(255,0,0,255);
            if (Maze[x+1][y+1]==' ') pixel=sf::Color(0,0,0,255);
            if (Maze[x+1][y+1]=='%') pixel=sf::Color(255,255,255,255);
            if (Maze[x+1][y+1]=='*') pixel=sf::Color(255,255,0,255);
            if (Maze[x+1][y+1]=='O') pixel=sf::Color(255,0,255,255);
            if (Maze[x+1][y+1]=='-') pixel=sf::Color(0,255,0,255);
            if (Maze[x+1][y+1]=='|') pixel=sf::Color(0,0,255,255);;
*/
            myimage.setPixel(x,y,pixel);
        }
    }
    for (int xx=0; xx<=max_x*2; xx++) {
        pixel=sf::Color(0,0,0,255);
        myimage.setPixel(xx,max_y*2,pixel);
    }
    for (int yy=0; yy<max_y*2; yy++) {
        pixel=sf::Color(0,0,0,255);
        myimage.setPixel(max_x*2,yy,pixel);
    }
    texture_from_ffmpeg.create(max_x*2+1,max_y*2+1);
    texture_from_ffmpeg.loadFromImage(myimage);
    ffmpegfile=0;
    sprite_from_ffmpeg.setTexture(texture_from_ffmpeg,true);
    sprite_from_ffmpeg.setScale(1.0,1.0);
    rot_speed_ffmpeg=0.0;
    scale_now=1.0;
    setffmpegfile();
}
