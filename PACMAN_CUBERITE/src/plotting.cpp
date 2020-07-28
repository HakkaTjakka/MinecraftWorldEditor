#define SFML_STATIC
#undef UNICODE
#include <winsock2.h>
#include <io.h>
#include "WinMain.h"
#include <stdio.h>
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
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <SFML/System/Mutex.hpp>
#include <SFML/Network/IpAddress.hpp>
#include <sfeMovie/Movie.hpp>
#include "StreamSelector.hpp"
#include "MediaInfo.hpp"

extern float ffmpeg_fixed_x;
extern float ffmpeg_fixed_y;
extern float internet_fixed_x;
extern float internet_fixed_y;
extern float movie_fixed_x;
extern float movie_fixed_y;
extern float movie2_fixed_x;
extern float movie2_fixed_y;

extern int plot_all;
extern int selector;
struct handler_struct {
    int blending;
    int plot_front;
    int show;
    int tile;
    int shader;
};
#define FFMPEG_SELECT 0
#define INTERNET_SELECT 1
#define MOVIE_SELECT 2
#define MOVIE2_SELECT 3
#define CANVAS_SELECT 4
extern struct handler_struct handler[];

extern sf::BlendMode MyBlendMode[];

extern int plot_internetfile;
extern int plot_ffmpegfile;
extern int plot_moviefile;
extern int plot_moviefile2;
extern int plot_front,plot_back;
extern int blending;
extern sf::BlendMode MyBlendingMode;

extern int movie_posx,movie_posy;
extern int movie2_posx,movie2_posy;
extern int ffmpeg_posx,ffmpeg_posy;
extern int internet_posx,internet_posy;

extern int movie_move;
extern int movie2_move;
extern int ffmpeg_move;
extern int size_ffmpeg;
extern int internet_move;

extern float rot_speed_movie;
extern float rot_speed_movie2;
extern float rot_speed_ffmpeg;
extern float rot_speed_internet;
extern float rot_speed_canvas;

extern float rotation_movie;
extern float rotation_movie2;
extern float rotation_ffmpeg;
extern float rotation_internet;
extern float rotation_canvas;

extern int rotate_movie;
extern int rotate_movie2;
extern int rotate_ffmpeg;
extern int rotate_internet;
extern int rotate_canvas;

extern sf::RenderTexture tussen_texture;
extern sf::RenderTexture backup_texture;
extern sf::Sprite backup_sprite;
extern sf::Sprite *spritemaxinmempoint[];
extern char **changed;
extern int reset_normal;

extern sf::Texture texture_from_movie_new;
extern sf::Texture texture_from_movie2_new;
extern void savedata(char *naam, int data);
extern int internetfile;
extern int ffmpegfile;
extern int movie;
extern int movie2;
extern int iFrame;
extern float run_time;
extern sf::RenderWindow SFMLView1;
extern sf::RenderTexture texture_from_buffer;
extern void DRAWMAZE(int totalx,int totaly);
extern int blank_maze;
extern int drawmazes;
extern int perform_quit;
extern double smooth_x;
extern double smooth_y;
extern int picturex;
extern int picturey;
extern int smooth;
float plot_abs_x,plot_abs_y;
extern int formula;
extern int buffer_shader;
extern sf::Shader shader_buffer;
extern char error_msg2[];
extern int error_flag2;
extern int plot_shader;
extern int BITMAPSX;
extern int BITMAPSY;
extern sf::Shader picture_shader;
extern int vertex_shader;
extern int fragment_shader;
void setffmpegfile();
extern sf::RenderStates picture_states;
extern int ffmpegfile;
extern int blend_on_movie;
extern sf::Texture texture_from_internet;
extern sf::Texture texture_from_ffmpeg;
extern sf::Sprite sprite_from_internet;
extern sf::Sprite sprite_from_ffmpeg;
extern sf::Sprite sprite_from_movie;
extern sf::Sprite sprite_from_movie2;
extern int render_picturex;
extern int render_picturey;
extern int render_posx;
extern int render_posy;
extern int maxpixelsx;
extern int maxpixelsy;
extern int totalpicturex;
extern int totalpicturey;
extern int maxpicturex;
extern int maxpicturey;
extern void blitter(char * line, int mode);
extern char *line;
//extern char line[];
extern int totalused;
extern int totalchanged;
extern int F2;
extern int MAXINMEM;
extern void go_save_some_bitmaps();
extern void ReadOneBitmap(int picturex,int picturey);
extern sf::RenderTexture *texturemaxinmempoint[];
extern int  **used2;
extern char error_msg[];
extern int error_flag;
extern int shader_ok;

void get_ffmpegfile() {
    int x,y;

    if (ffmpegfile==0 && blend_on_movie==0)
    {
//        if (plot_shader==0)
            setffmpegfile();

        sf::RenderTexture New_ffmpeg_texture;
        New_ffmpeg_texture.create(texture_from_ffmpeg.getSize().x,texture_from_ffmpeg.getSize().y);
        New_ffmpeg_texture.clear(sf::Color(0,0,0,0));
        sf::Sprite New_ffmpeg_sprite;

        int addx=0,addy=0;
        int globx=sprite_from_ffmpeg.getGlobalBounds().width;
        int globy=sprite_from_ffmpeg.getGlobalBounds().height;

        int sprite_posx_start;
        int sprite_posy_start;
        int sprite_posx_end;
        int sprite_posy_end;
        int arx_start;
        int ary_start;
        int arx_end;
        int ary_end;

        if (plot_shader==0) {
            sprite_posx_start=-render_posx +  (1920)/2 - globx/2 + maxpixelsx;
            sprite_posy_start=-render_posy +  (1080)/2 - globy/2 + maxpixelsy;
            sprite_posx_end=-render_posx +  (1920)/2 + globx/2 + maxpixelsx-1;
            sprite_posy_end=-render_posy +  (1080)/2 + globy/2 + maxpixelsy-1;

            arx_start=sprite_posx_start/1920;
            ary_start=sprite_posy_start/1080;
            arx_end=sprite_posx_end/1920;
            ary_end=sprite_posy_end/1080;

            arx_start=arx_start-totalpicturex;
            ary_start=ary_start-totalpicturey;
            arx_end=arx_end-totalpicturex;
            ary_end=ary_end-totalpicturey;
//            printf("arx_start=%d arx_end=%d ary_start=%d ary_end=%d\n",arx_start,arx_end,ary_start,ary_end);
        } else {
            arx_start=-BITMAPSX/2+1;ary_start=-BITMAPSY/2+1;
            arx_end=BITMAPSX/2;ary_end=BITMAPSY/2;
        }


        sprite_from_ffmpeg.setTexture(texture_from_ffmpeg,false);

        int number_bitmaps=0;

        sf::Transform MyTrans;
        sf::Transform MyTrans2;

        MyTrans=sprite_from_ffmpeg.getInverseTransform();
        MyTrans2.rotate(-sprite_from_ffmpeg.getRotation());

        for (x=arx_start; x<=arx_end; x++)
        {
            for (y=ary_start; y<=ary_end; y++)
            {
                number_bitmaps++;
                int arx=(render_picturex+x+totalpicturex)%(maxpicturex+1);
                int ary=(render_picturey+y+totalpicturey)%(maxpicturey+1);

                if (F2==1 && perform_quit==0)
                {
                    sprintf(line,"PROCESSING %d x %d TO BITMAPS (%d x %d) X=%3d,Y=%3d #=%d/%d",globx,globy, arx_end-arx_start+1,ary_end-ary_start+1,arx,ary,number_bitmaps,(arx_end-arx_start+1)*(ary_end-ary_start+1));
//                    blitter(line,1);
                }
                if (totalused>MAXINMEM)
                {
                    if (F2==1 && perform_quit==0)
                    {
                        strcat(line," DELETING/SAVING BITMAP");
                        blitter(line,1);
                    }
                    int oldx=picturex,oldy=picturey;
                    picturex=arx;picturey=ary;
                    go_save_some_bitmaps();
                    if (totalused>MAXINMEM+2)
                    {
                        go_save_some_bitmaps();
                        if (totalused>MAXINMEM+4)
                        {
                            go_save_some_bitmaps();
                        }
                    }
                    picturex=oldx;
                    picturey=oldy;
                } else {
                    if (F2==1 && perform_quit==0) blitter(line,1);
                }

                if (F2==1 && perform_quit==0)
                {
                    strcat(line," / LOADING BITMAP");
                    blitter(line,1);
                }
                ReadOneBitmap(arx,ary);
//                if (drawmazes==1 && blank_maze==0) DRAWMAZE(arx,ary);
                texturemaxinmempoint[used2[arx][ary]]->generateMipmap();

                New_ffmpeg_sprite.setTexture(texturemaxinmempoint[used2[arx][ary]]->getTexture(),true);
                New_ffmpeg_sprite.setTextureRect({0,0,1920,1080});

                New_ffmpeg_sprite.setOrigin((float)New_ffmpeg_texture.getSize().x/2.0,(float)New_ffmpeg_texture.getSize().y/2.0);

//                printf("CENTER: X=%f , Y=%f\n",(float)New_ffmpeg_texture.getSize().x/2.0,(float)New_ffmpeg_texture.getSize().y/2.0);

                sf::Vector2f point;

                point.x=(1920.0-(float)New_ffmpeg_texture.getSize().x )/2.0/sprite_from_ffmpeg.getScale().x;
                point.y=(1080.0-(float)New_ffmpeg_texture.getSize().y )/2.0/sprite_from_ffmpeg.getScale().y;

                point=MyTrans2.transformPoint(point);

//one line transparant at top?
//                point.x=ceil(point.x);
//                point.y=ceil(point.y);

                sf::Vector2f point_gw;
                point_gw=MyTrans.transformPoint( -(-render_posx-x*1920.0 -  (1920)/2),-(-render_posy-y*1080.0 -  (1080)/2))  -  point;
//                printf("POS: X=%f , Y=%f\n",point_gw.x,point_gw.y);

                New_ffmpeg_sprite.setPosition(  MyTrans.transformPoint( -(-render_posx-x*1920.0 -  (1920)/2),
                                                                        -(-render_posy-y*1080.0 -  (1080)/2))  -
                                                point
                                              );

                New_ffmpeg_sprite.setScale(1.0/sprite_from_ffmpeg.getScale().x,1.0/sprite_from_ffmpeg.getScale().y);
                New_ffmpeg_sprite.setRotation(-sprite_from_ffmpeg.getRotation());

                New_ffmpeg_texture.draw(New_ffmpeg_sprite);
            }
        }
        New_ffmpeg_texture.display();

        texture_from_ffmpeg.update(New_ffmpeg_texture.getTexture());
        texture_from_ffmpeg.generateMipmap();
//        texture_from_ffmpeg.loadFromImage(New_ffmpeg_texture.getTexture().copyToImage());

        sprintf(error_msg,"PROCESSED %d x %d TO BITMAPS (%d x %d) #=%d",globx,globy, arx_end-arx_start+1,ary_end-ary_start+1,number_bitmaps);
        error_flag=1;

        setffmpegfile(); //prevent flash in screen, sprite settings changed or something like that :P
    }
}


void setmoviefile()
{
    if ((movie_posx+render_posx-render_picturex*1920)>maxpixelsx/2)
        movie_posx=movie_posx-maxpixelsx;
    else if ((movie_posx+render_posx-render_picturex*1920)<-maxpixelsx/2)
        movie_posx=movie_posx+maxpixelsx;
    if ((movie_posy+render_posy-render_picturey*1080)>maxpixelsy/2)
        movie_posy=movie_posy-maxpixelsy;
    else if ((movie_posy+render_posy-render_picturey*1080)<-maxpixelsy/2)
        movie_posy=movie_posy+maxpixelsy;
    if (rotate_movie==1)
        rotation_movie=rotation_movie+rot_speed_movie;
    sprite_from_movie.setOrigin(texture_from_movie_new.getSize().x/2,texture_from_movie_new.getSize().y/2);
    sprite_from_movie.setRotation(rotation_movie);

    if (handler[MOVIE_SELECT].tile==1)  {
        sprite_from_movie.setOrigin(texture_from_movie_new.getSize().x*500,texture_from_movie_new.getSize().y*500);
        sprite_from_movie.setTextureRect( {
                -(int)texture_from_movie_new.getSize().x*0,
                -(int)texture_from_movie_new.getSize().y*0,
                 (int)texture_from_movie_new.getSize().x*1000,
                 (int)texture_from_movie_new.getSize().y*1000 } );

    } else {
        sprite_from_movie.setOrigin(texture_from_movie_new.getSize().x/2,texture_from_movie_new.getSize().y/2);
        sprite_from_movie.setTextureRect( {
                0,
                0,
                (int)texture_from_movie_new.getSize().x,
                (int)texture_from_movie_new.getSize().y } );
    }

    if (handler[MOVIE_SELECT].tile==2) {
        sprite_from_movie.setPosition(movie_fixed_x,movie_fixed_y);
    } else if (movie_move==1)
    {
        sprite_from_movie.setPosition((movie_posx+render_posx-render_picturex*1920)+(int)texture_from_movie_new.getSize().x/2, ( movie_posy + render_posy-render_picturey*1080)+(int)texture_from_movie_new.getSize().y/2 );
    } else {
        sprite_from_movie.setPosition( (1920)/2,(1080)/2);
    }
    if (handler[MOVIE_SELECT].tile==2) {
        plot_abs_x=(-render_posx+render_picturex*1920+(movie_fixed_x) );
        plot_abs_x=((int)plot_abs_x+maxpixelsx)%maxpixelsx;
        plot_abs_x=plot_abs_x/(BITMAPSX*1920.0)-0.5;

        plot_abs_y=(-render_posy+render_picturey*1080+(movie_fixed_y ) );
        plot_abs_y=((int)plot_abs_y+maxpixelsy)%maxpixelsy;
        plot_abs_y=plot_abs_y/(BITMAPSY*1080.0)-0.5;
    } else if (movie_move==1) {
        plot_abs_x=((movie_posx)+(int)texture_from_movie_new.getSize().x/2);
        plot_abs_x=((int)plot_abs_x+maxpixelsx)%maxpixelsx;
        plot_abs_x=plot_abs_x/(BITMAPSX*1920.0)-0.5;

        plot_abs_y=((movie_posy)+(int)texture_from_movie_new.getSize().y/2);
        plot_abs_y=((int)plot_abs_y+maxpixelsy)%maxpixelsy;
        plot_abs_y=plot_abs_y/(BITMAPSY*1080.0)-0.5;
    }
    else
    {
        plot_abs_x=(-render_posx+render_picturex*1920+(1920/2) );
        plot_abs_x=((int)plot_abs_x+maxpixelsx)%maxpixelsx;
        plot_abs_x=plot_abs_x/(BITMAPSX*1920.0)-0.5;

        plot_abs_y=(-render_posy+render_picturey*1080+(1080/2 ) );
        plot_abs_y=((int)plot_abs_y+maxpixelsy)%maxpixelsy;
        plot_abs_y=plot_abs_y/(BITMAPSY*1080.0)-0.5;

    }

    if (fragment_shader==1 || vertex_shader==1 || plot_shader>=1) {
        float sizex=(float)texture_from_movie_new.getSize().x*sprite_from_movie.getScale().x;
        float sizey=(float)texture_from_movie_new.getSize().y*sprite_from_movie.getScale().y;
        float corrx;
        float corry;
        corrx=(float) sprite_from_movie.getPosition().x - sizex/2.0;
        corry=(float) -sprite_from_movie.getPosition().y + 1080.0 - sizey/2.0;

        picture_shader.setUniform("iResolution",  sf::Vector2f( sizex,sizey) );
        picture_shader.setUniform("pos_correction",  sf::Vector2f( corrx, corry)  );
        picture_shader.setUniform("txt_correction",  sf::Vector2f( corrx, corry)  );
        picture_shader.setUniform("txt_resolution",  sf::Vector2f( -sizex,-sizey)  );
        if (buffer_shader==1) shader_buffer.setUniform("pos_correction",  sf::Vector2f( corrx, corry)  );
        picture_shader.setUniform("pos_abs",  sf::Vector2f(plot_abs_x,plot_abs_y) );

        if (movie_move==1)
        {
            picture_shader.setUniform("pos_correction2",  sf::Vector2f( (movie_posx+render_posx-render_picturex*1920)+(int)texture_from_movie_new.getSize().x/2, ( movie_posy + render_posy-render_picturey*1080)+(int)texture_from_movie_new.getSize().y/2 ) );
        } else {
            picture_shader.setUniform("pos_correction2",  sf::Vector2f( 1920/2, 1080/2)   );
        }
    }
}

void setmoviefile2()
{
    if ((movie2_posx+render_posx-render_picturex*1920)>maxpixelsx/2)
        movie2_posx=movie2_posx-maxpixelsx;
    else if ((movie2_posx+render_posx-render_picturex*1920)<-maxpixelsx/2)
        movie2_posx=movie2_posx+maxpixelsx;
    if ((movie2_posy+render_posy-render_picturey*1080)>maxpixelsy/2)
        movie2_posy=movie2_posy-maxpixelsy;
    else if ((movie2_posy+render_posy-render_picturey*1080)<-maxpixelsy/2)
        movie2_posy=movie2_posy+maxpixelsy;
    if (rotate_movie2==1)
        rotation_movie2=rotation_movie2+rot_speed_movie2;
    sprite_from_movie2.setOrigin(texture_from_movie2_new.getSize().x/2,texture_from_movie2_new.getSize().y/2);
    sprite_from_movie2.setRotation(rotation_movie2);


    if (handler[MOVIE2_SELECT].tile==1)  {
        sprite_from_movie2.setOrigin(texture_from_movie2_new.getSize().x*500,texture_from_movie2_new.getSize().y*500);
        sprite_from_movie2.setTextureRect( {
                -(int)texture_from_movie2_new.getSize().x*0,
                -(int)texture_from_movie2_new.getSize().y*0,
                 (int)texture_from_movie2_new.getSize().x*1000,
                 (int)texture_from_movie2_new.getSize().y*1000 } );

    } else {
        sprite_from_movie2.setOrigin(texture_from_movie2_new.getSize().x/2,texture_from_movie2_new.getSize().y/2);
        sprite_from_movie2.setTextureRect( {
                0,
                0,
                (int)texture_from_movie2_new.getSize().x,
                (int)texture_from_movie2_new.getSize().y } );
    }

    if (handler[MOVIE2_SELECT].tile==2) {
        sprite_from_movie2.setPosition(movie2_fixed_x,movie2_fixed_y);
    } else if (movie2_move==1)
    {
        sprite_from_movie2.setPosition( ( movie2_posx + render_posx-render_picturex*1920)+(int)texture_from_movie2_new.getSize().x/2,
                                        ( movie2_posy + render_posy-render_picturey*1080)+(int)texture_from_movie2_new.getSize().y/2 );
    }
    else
    {
        sprite_from_movie2.setPosition( (1920)/2,(1080)/2);
    }
    if (handler[MOVIE2_SELECT].tile==2) {
        plot_abs_x=(-render_posx+render_picturex*1920+(movie2_fixed_x) );
        plot_abs_x=((int)plot_abs_x+maxpixelsx)%maxpixelsx;
        plot_abs_x=plot_abs_x/(BITMAPSX*1920.0)-0.5;

        plot_abs_y=(-render_posy+render_picturey*1080+(movie2_fixed_y ) );
        plot_abs_y=((int)plot_abs_y+maxpixelsy)%maxpixelsy;
        plot_abs_y=plot_abs_y/(BITMAPSY*1080.0)-0.5;
    } else if (movie_move==1) {
        plot_abs_x=((movie2_posx)+(int)texture_from_movie2_new.getSize().x/2);
        plot_abs_x=((int)plot_abs_x+maxpixelsx)%maxpixelsx;
        plot_abs_x=plot_abs_x/(BITMAPSX*1920.0)-0.5;

        plot_abs_y=((movie2_posy)+(int)texture_from_movie2_new.getSize().y/2);
        plot_abs_y=((int)plot_abs_y+maxpixelsy)%maxpixelsy;
        plot_abs_y=plot_abs_y/(BITMAPSY*1080.0)-0.5;
    }
    else
    {
        plot_abs_x=(-render_posx+render_picturex*1920+(1920/2) );
        plot_abs_x=((int)plot_abs_x+maxpixelsx)%maxpixelsx;
        plot_abs_x=plot_abs_x/(BITMAPSX*1920.0)-0.5;

        plot_abs_y=(-render_posy+render_picturey*1080+(1080/2 ) );
        plot_abs_y=((int)plot_abs_y+maxpixelsy)%maxpixelsy;
        plot_abs_y=plot_abs_y/(BITMAPSY*1080.0)-0.5;

    }

    if (fragment_shader==1 || vertex_shader==1) {
        float sizex=(float)texture_from_movie2_new.getSize().x*sprite_from_movie2.getScale().x;
        float sizey=(float)texture_from_movie2_new.getSize().y*sprite_from_movie2.getScale().y;
        float corrx;
        float corry;
        corrx=(float) sprite_from_movie2.getPosition().x - sizex/2.0;
        corry=(float) -sprite_from_movie2.getPosition().y + 1080.0 - sizey/2.0;

        picture_shader.setUniform("iResolution",  sf::Vector2f( sizex,sizey) );
        picture_shader.setUniform("pos_correction",  sf::Vector2f( corrx, corry)  );
        picture_shader.setUniform("txt_correction",  sf::Vector2f( corrx, corry)  );
        picture_shader.setUniform("txt_resolution",  sf::Vector2f( -sizex,-sizey)  );
    }
}


void setinternetfile()
{
    if ((internet_posx+render_posx-render_picturex*1920)>maxpixelsx/2)
        internet_posx=internet_posx-maxpixelsx;
    else if ((internet_posx+render_posx-render_picturex*1920)<-maxpixelsx/2)
        internet_posx=internet_posx+maxpixelsx;
    if ((internet_posy+render_posy-render_picturey*1080)>maxpixelsy/2)
        internet_posy=internet_posy-maxpixelsy;
    else if ((internet_posy+render_posy-render_picturey*1080)<-maxpixelsy/2)
        internet_posy=internet_posy+maxpixelsy;
    if (rotate_internet==1)
        rotation_internet=rotation_internet+rot_speed_internet;
    sprite_from_internet.setRotation(rotation_internet);

//    sprite_from_internet.setOrigin(texture_from_internet.getSize().x/2,texture_from_internet.getSize().y/2);

    if (handler[INTERNET_SELECT].tile==1)  {
        sprite_from_internet.setOrigin(texture_from_internet.getSize().x*500,texture_from_internet.getSize().y*500);
        sprite_from_internet.setTextureRect( {
                -(int)texture_from_internet.getSize().x*0,
                -(int)texture_from_internet.getSize().y*0,
                 (int)texture_from_internet.getSize().x*1000,
                 (int)texture_from_internet.getSize().y*1000 } );

    } else {
        sprite_from_internet.setOrigin(texture_from_internet.getSize().x/2,texture_from_internet.getSize().y/2);
        sprite_from_internet.setTextureRect( {
                0,
                0,
                (int)texture_from_internet.getSize().x,
                (int)texture_from_internet.getSize().y } );
    }

    if (handler[INTERNET_SELECT].tile==2) {
        sprite_from_internet.setPosition(internet_fixed_x,internet_fixed_y);
    } else if (internet_move==1)
    {
        if (smooth==0)
            sprite_from_internet.setPosition(
                                             (internet_posx + render_posx-render_picturex*1920)+(int)texture_from_internet.getSize().x/2-(float)smooth_x+(float)((int)smooth_x),
                                             (internet_posy + render_posy-render_picturey*1080)+(int)texture_from_internet.getSize().y/2-(float)smooth_y+(float)((int)smooth_y)
                                              );
        else
            sprite_from_internet.setPosition(
                                             (internet_posx + render_posx-render_picturex*1920)+(int)texture_from_internet.getSize().x/2,
                                             (internet_posy + render_posy-render_picturey*1080)+(int)texture_from_internet.getSize().y/2
                                              );
    }
    else
    {
        sprite_from_internet.setPosition( (1920)/2,(1080)/2);
    }

    if (handler[INTERNET_SELECT].tile==2) {
        plot_abs_x=(-render_posx+render_picturex*1920+(internet_fixed_x) );
        plot_abs_x=((int)plot_abs_x+maxpixelsx)%maxpixelsx;
        plot_abs_x=plot_abs_x/(BITMAPSX*1920.0)-0.5;

        plot_abs_y=(-render_posy+render_picturey*1080+(internet_fixed_y ) );
        plot_abs_y=((int)plot_abs_y+maxpixelsy)%maxpixelsy;
        plot_abs_y=plot_abs_y/(BITMAPSY*1080.0)-0.5;
    } else if (internet_move==1)
    {
        plot_abs_x=((internet_posx)+(int)texture_from_internet.getSize().x/2);
        plot_abs_x=((int)plot_abs_x+maxpixelsx)%maxpixelsx;
        plot_abs_x=plot_abs_x/(BITMAPSX*1920.0)-0.5;

        plot_abs_y=((internet_posy)+(int)texture_from_internet.getSize().y/2);
        plot_abs_y=((int)plot_abs_y+maxpixelsy)%maxpixelsy;
        plot_abs_y=plot_abs_y/(BITMAPSY*1080.0)-0.5;
    }
    else
    {
        plot_abs_x=(-render_posx+render_picturex*1920+(1920/2) );
        plot_abs_x=((int)plot_abs_x+maxpixelsx)%maxpixelsx;
        plot_abs_x=plot_abs_x/(BITMAPSX*1920.0)-0.5;

        plot_abs_y=(-render_posy+render_picturey*1080+(1080/2 ) );
        plot_abs_y=((int)plot_abs_y+maxpixelsy)%maxpixelsy;
        plot_abs_y=plot_abs_y/(BITMAPSY*1080.0)-0.5;
    }


    if (fragment_shader==1 || vertex_shader==1 || plot_shader>=1) {
        float sizex=(float)texture_from_internet.getSize().x*sprite_from_internet.getScale().x;
        float sizey=(float)texture_from_internet.getSize().y*sprite_from_internet.getScale().y;
        float corrx;
        float corry;
        corrx=(float) sprite_from_internet.getPosition().x - sizex/2.0;
        corry=(float) -sprite_from_internet.getPosition().y + 1080.0 - sizey/2.0;

        picture_shader.setUniform("iResolution",  sf::Vector2f( sizex,sizey) );
        picture_shader.setUniform("pos_correction",  sf::Vector2f( corrx, corry)  );
        picture_shader.setUniform("txt_correction",  sf::Vector2f( (smooth_x)+(int)texture_from_internet.getSize().x/2, ( smooth_y)+(int)texture_from_internet.getSize().y/2 ) );
        picture_shader.setUniform("txt_resolution",  sf::Vector2f( -sizex,-sizey)  );
        if (buffer_shader==1) shader_buffer.setUniform("pos_correction",  sf::Vector2f( corrx, corry)  );
        picture_shader.setUniform("pos_abs",  sf::Vector2f(plot_abs_x,plot_abs_y) );

        if (internet_move==1)
        {
            picture_shader.setUniform("pos_correction2",  sf::Vector2f( (internet_posx+render_posx-render_picturex*1920)+(int)texture_from_internet.getSize().x/2, ( internet_posy + render_posy-render_picturey*1080)+(int)texture_from_internet.getSize().y/2 ) );
        } else {
            picture_shader.setUniform("pos_correction2",  sf::Vector2f( 1920/2, 1080/2)   );
        }
    }
}
extern int shade_map;
extern int SAS_ZOOM;
extern int NO_RECT;


void setffmpegfile()
{
//    if (!(shade_map && fragment_shader)) {
        if ((ffmpeg_posx+render_posx-render_picturex*1920)>maxpixelsx/2) ffmpeg_posx=ffmpeg_posx-maxpixelsx;
        else if ((ffmpeg_posx+render_posx-render_picturex*1920)<-maxpixelsx/2) ffmpeg_posx=ffmpeg_posx+maxpixelsx;
        if ((ffmpeg_posy+render_posy-render_picturey*1080)>maxpixelsy/2) ffmpeg_posy=ffmpeg_posy-maxpixelsy;
        else if ((ffmpeg_posy+render_posy-render_picturey*1080)<-maxpixelsy/2) ffmpeg_posy=ffmpeg_posy+maxpixelsy;
//    }

    if (rotate_ffmpeg==1) {
        rotation_ffmpeg=rotation_ffmpeg+rot_speed_ffmpeg;
    }
    sprite_from_ffmpeg.setRotation(rotation_ffmpeg);

    if (handler[FFMPEG_SELECT].tile==1)  {
        sprite_from_ffmpeg.setOrigin(texture_from_ffmpeg.getSize().x*5000,texture_from_ffmpeg.getSize().y*5000);
        sprite_from_ffmpeg.setTextureRect( {
                -(int)texture_from_ffmpeg.getSize().x*0,
                -(int)texture_from_ffmpeg.getSize().y*0,
                 (int)texture_from_ffmpeg.getSize().x*10000,
                 (int)texture_from_ffmpeg.getSize().y*10000 } );

    } else {
        sprite_from_ffmpeg.setOrigin(
                                     (float)texture_from_ffmpeg.getSize().x/2 ,
                                     (float)texture_from_ffmpeg.getSize().y/2
                                     );

        if (NO_RECT==0) sprite_from_ffmpeg.setTextureRect( {
                0,
                0,
                (int)texture_from_ffmpeg.getSize().x,
                (int)texture_from_ffmpeg.getSize().y } );
    }

    if (shade_map>=1 && fragment_shader==1 && 0) {
        ffmpeg_move=1;
        size_ffmpeg=1;
//        ffmpeg_posx=pow(2.0,(double)SAS_ZOOM+7.0);
//        ffmpeg_posy=pow(2.0,(double)SAS_ZOOM+7.0);

/*
        start_posx=ffmpeg_posx-1920/2+(int)texture_from_ffmpeg.getSize().x/2;
        start_posy=ffmpeg_posy-1080/2+(int)texture_from_ffmpeg.getSize().y/2;

        ffmpeg_posx=-render_posx+render_picturex*1920+(1920/2-(int)texture_from_ffmpeg.getSize().x/2);
        ffmpeg_posy=-render_posy+render_picturey*1080+(1080/2-(int)texture_from_ffmpeg.getSize().y/2);

        sprite_from_ffmpeg.setPosition((ffmpeg_posx+render_posx-render_picturex*1920), ( ffmpeg_posy + render_posy-render_picturey*1080) );
*/

        ffmpeg_posx=pow(2.0,(double)SAS_ZOOM+7.0)+(-(int)texture_from_ffmpeg.getSize().x/2);
        ffmpeg_posy=pow(2.0,(double)SAS_ZOOM+7.0)+(-(int)texture_from_ffmpeg.getSize().y/2);

//        if ((ffmpeg_posx+render_posx-render_picturex*1920)>maxpixelsx/2) ffmpeg_posx=ffmpeg_posx-maxpixelsx;
//        else if ((ffmpeg_posx+render_posx-render_picturex*1920)<-maxpixelsx/2) ffmpeg_posx=ffmpeg_posx+maxpixelsx;
//        if ((ffmpeg_posy+render_posy-render_picturey*1080)>maxpixelsy/2) ffmpeg_posy=ffmpeg_posy-maxpixelsy;
//        else if ((ffmpeg_posy+render_posy-render_picturey*1080)<-maxpixelsy/2) ffmpeg_posy=ffmpeg_posy+maxpixelsy;

        sprite_from_ffmpeg.setPosition(
            (ffmpeg_posx+render_posx-render_picturex*1920)+(int)texture_from_ffmpeg.getSize().x/2,
            (ffmpeg_posy+render_posy-render_picturey*1080)+(int)texture_from_ffmpeg.getSize().y/2
        );
//        sprite_from_ffmpeg.setPosition((ffmpeg_posx+render_posx-render_picturex*1920)+(int)texture_from_ffmpeg.getSize().x/2, ( ffmpeg_posy + render_posy-render_picturey*1080)+(int)texture_from_ffmpeg.getSize().y/2 );
        sprite_from_ffmpeg.setScale(256.0/(double)texture_from_ffmpeg.getSize().x*pow(2.0,(double)SAS_ZOOM),
                                    256.0/(double)texture_from_ffmpeg.getSize().y*pow(2.0,(double)SAS_ZOOM));
    } else if (handler[FFMPEG_SELECT].tile==2) {
        sprite_from_ffmpeg.setPosition(
                                       ffmpeg_fixed_x,
                                       ffmpeg_fixed_y
        );
    } else if (ffmpeg_move==1) {
        if (smooth)
            sprite_from_ffmpeg.setPosition(
                (float)(ffmpeg_posx+render_posx-render_picturex*1920)+(float)texture_from_ffmpeg.getSize().x/2-(float)smooth_x+(float)((int)smooth_x),
                (float)(ffmpeg_posy+render_posy-render_picturey*1080)+(float)texture_from_ffmpeg.getSize().y/2-(float)smooth_y+(float)((int)smooth_y)
            );
        else
            sprite_from_ffmpeg.setPosition(
                (float)(ffmpeg_posx+render_posx-render_picturex*1920)+(float)texture_from_ffmpeg.getSize().x/2.0,
                (float)(ffmpeg_posy+render_posy-render_picturey*1080)+(float)texture_from_ffmpeg.getSize().y/2.0
            );
    } else {
        sprite_from_ffmpeg.setPosition(
                                       (1920)/2,
                                       (1080)/2
        );
    }

    if (handler[FFMPEG_SELECT].tile==2) {
        plot_abs_x=(-render_posx+render_picturex*1920+(ffmpeg_fixed_x) );
        plot_abs_x=((int)plot_abs_x+maxpixelsx)%maxpixelsx;
        plot_abs_x=plot_abs_x/(BITMAPSX*1920.0)-0.5;

        plot_abs_y=(-render_posy+render_picturey*1080+(ffmpeg_fixed_y ) );
        plot_abs_y=((int)plot_abs_y+maxpixelsy)%maxpixelsy;
        plot_abs_y=plot_abs_y/(BITMAPSY*1080.0)-0.5;
    } else if (ffmpeg_move==1)
    {
        plot_abs_x=((ffmpeg_posx)+(int)texture_from_ffmpeg.getSize().x/2);
        plot_abs_x=((int)plot_abs_x+maxpixelsx)%maxpixelsx;
        plot_abs_x=plot_abs_x/(BITMAPSX*1920.0)-0.5;

        plot_abs_y=((ffmpeg_posy)+(int)texture_from_ffmpeg.getSize().y/2);
        plot_abs_y=((int)plot_abs_y+maxpixelsy)%maxpixelsy;
        plot_abs_y=plot_abs_y/(BITMAPSY*1080.0)-0.5;
    }
    else
    {
        plot_abs_x=(-render_posx+render_picturex*1920+(1920/2) );
        plot_abs_x=((int)plot_abs_x+maxpixelsx)%maxpixelsx;
        plot_abs_x=plot_abs_x/(BITMAPSX*1920.0)-0.5;

        plot_abs_y=(-render_posy+render_picturey*1080+(1080/2 ) );
        plot_abs_y=((int)plot_abs_y+maxpixelsy)%maxpixelsy;
        plot_abs_y=plot_abs_y/(BITMAPSY*1080.0)-0.5;
    }

    if (fragment_shader==1 || vertex_shader==1 || plot_shader>=1) {
        float sizex;
        float sizey;
extern int no_scale;
//        if (no_scale) {
//            sizex=(float)texture_from_ffmpeg.getSize().x;
//            sizey=(float)texture_from_ffmpeg.getSize().y;
//        } else {
            sizex=(float)texture_from_ffmpeg.getSize().x*sprite_from_ffmpeg.getScale().x;
            sizey=(float)texture_from_ffmpeg.getSize().y*sprite_from_ffmpeg.getScale().y;
//        }
        float corrx;
        float corry;
        corrx=(float) sprite_from_ffmpeg.getPosition().x - sizex/2.0;
        corry=(float) -sprite_from_ffmpeg.getPosition().y + 1080.0 - sizey/2.0;


        picture_shader.setUniform("iScale",  sf::Vector2f( sprite_from_ffmpeg.getScale().x,sprite_from_ffmpeg.getScale().y) );
        picture_shader.setUniform("iResolution",  sf::Vector2f( sizex,sizey) );
        picture_shader.setUniform("pos_correction",  sf::Vector2f( corrx, corry)  );
//        picture_shader.setUniform("txt_correction",  sf::Vector2f( (smooth_x)+(int)texture_from_ffmpeg.getSize().x/2, ( smooth_y)+(int)texture_from_ffmpeg.getSize().y/2 ) );
//        picture_shader.setUniform("txt_resolution",  sf::Vector2f( -sizex,-sizey)  );
        if (buffer_shader==1) shader_buffer.setUniform("pos_correction",  sf::Vector2f( corrx, corry)  );
        picture_shader.setUniform("pos_abs",  sf::Vector2f(plot_abs_x,plot_abs_y) );

        if (plot_shader==1 && plot_ffmpegfile==1)
            picture_shader.setUniform("iRotate", (float)0.0);

        if (ffmpeg_move==1)
        {
            picture_shader.setUniform("pos_correction2",  sf::Vector2f( (ffmpeg_posx+render_posx-render_picturex*1920)+(int)texture_from_ffmpeg.getSize().x/2, ( ffmpeg_posy + render_posy-render_picturey*1080)+(int)texture_from_ffmpeg.getSize().y/2 ) );
        } else {
            picture_shader.setUniform("pos_correction2",  sf::Vector2f( 1920/2, 1080/2)   );
        }
    }
}

void setcanvasfile()
{
    if (rotate_canvas==1) {
        rotation_canvas=rotation_canvas+rot_speed_canvas;
    }
}


void plotplot()
{
    int x,y;

    if (plot_ffmpegfile==1 && blend_on_movie==0)
    {
        setffmpegfile();
        plot_ffmpegfile=0;
        texture_from_ffmpeg.generateMipmap();

        int addx=0,addy=0;
        int globx=sprite_from_ffmpeg.getGlobalBounds().width;
        int globy=sprite_from_ffmpeg.getGlobalBounds().height;
        if (vertex_shader==1) {
            globx+=500;
            globy+=500;
        }

        int sprite_posx_start;
        int sprite_posy_start;
        int sprite_posx_end;
        int sprite_posy_end;
        int arx_start;
        int ary_start;
        int arx_end;
        int ary_end;

        sprite_posx_start=-render_posx +  (1920)/2 - globx/2 + maxpixelsx;
        sprite_posy_start=-render_posy +  (1080)/2 - globy/2 + maxpixelsy;
        sprite_posx_end=-render_posx +  (1920)/2 + globx/2 + maxpixelsx;
        sprite_posy_end=-render_posy +  (1080)/2 + globy/2 + maxpixelsy;

        arx_start=sprite_posx_start/1920;
        ary_start=sprite_posy_start/1080;
        arx_end=sprite_posx_end/1920;
        ary_end=sprite_posy_end/1080;

        arx_start=arx_start-totalpicturex;
        ary_start=ary_start-totalpicturey;
        arx_end=arx_end-totalpicturex;
        ary_end=ary_end-totalpicturey;

        if (handler[FFMPEG_SELECT].tile==1) {
//            if (arx_start<0) arx_start=0;
//            if (arx_end>=BITMAPSX) arx_end=BITMAPSX-1;
//            if (ary_start<0) ary_start=0;
//            if (ary_end>=BITMAPSY) ary_end=BITMAPSY-1;
            arx_start=-render_picturex;
            arx_end=-render_picturex+BITMAPSX-1;
            ary_start=-render_picturey;
            ary_end=-render_picturey+BITMAPSY-1;
            globx=maxpixelsx;
            globy=maxpixelsy;
        }

        sprite_from_ffmpeg.setTexture(texture_from_ffmpeg,false);

        int number_bitmaps=0;

        if (plot_shader>=1 && ((vertex_shader==0 && fragment_shader==0))) {
            if (shader_ok==0) {
                strcpy(error_msg2,"NO SHADER SELECTED, CTRL-S PLOT SHADER OFF, ALT-F2 SELECT SHADER");
                error_flag2=1;
                return;
            } else {
                picture_states.shader = &picture_shader;
            }
            picture_shader.setUniform("background_plot",  0 );
            picture_shader.setUniform("formula_on",  formula==1 );

            if (movie==0) {
                picture_shader.setUniform("texture_buffer", texture_from_movie_new);
                picture_shader.setUniform("iResolution_buffer",  sf::Vector2f( texture_from_movie_new.getSize().x,texture_from_movie_new.getSize().y) );
            }  else if (movie2==0) {
                picture_shader.setUniform("texture_buffer", texture_from_movie2_new);
                picture_shader.setUniform("iResolution_buffer",  sf::Vector2f( texture_from_movie2_new.getSize().x,texture_from_movie2_new.getSize().y) );
            } else if (ffmpegfile==0) {
                picture_shader.setUniform("texture_buffer", texture_from_ffmpeg);
                picture_shader.setUniform("iResolution_buffer",  sf::Vector2f( texture_from_ffmpeg.getSize().x,texture_from_ffmpeg.getSize().y) );
            } else if (internetfile==0) {
                picture_shader.setUniform("texture_buffer", texture_from_internet);
                picture_shader.setUniform("iResolution_buffer",  sf::Vector2f( texture_from_internet.getSize().x,texture_from_internet.getSize().y) );
            } else if (buffer_shader==1) {
                picture_shader.setUniform("iResolution_buffer",  sf::Vector2f( texture_from_buffer.getSize().x,texture_from_buffer.getSize().y) );
            } else {
                picture_shader.setUniform("iResolution_buffer",  sf::Vector2f( 1920.0,1080.0) );
            }

            if (plot_shader==1) picture_shader.setUniform("iTime",   run_time );
            if ( ffmpegfile==0) {
                if ( sf::Mouse::isButtonPressed(sf::Mouse::Right) && ffmpegfile==0) {
                    picture_shader.setUniform("iMouse",  sf::Vector2f( (float) (sf::Mouse::getPosition(SFMLView1).x) / SFMLView1.getSize().x,
                                                                       (float) (sf::Mouse::getPosition(SFMLView1).y) / SFMLView1.getSize().y ) );
                    picture_shader.setUniform("iMouse_on",  1 );
                } else {
                    picture_shader.setUniform("iMouse_on",  0 );
                }
                picture_shader.setUniform("iFrame",   iFrame );
            }
        }

        if (plot_shader==1) {
//        if ( (vertex_shader==1 || fragment_shader==1) && plot_shader==1) {
            picture_shader.setUniform("iResolution",  sf::Vector2f( texture_from_ffmpeg.getSize().x,texture_from_ffmpeg.getSize().y) );
            picture_shader.setUniform("pos_correction",  sf::Vector2f(  (float) 0.0, (float) 0.0 )  );
            picture_shader.setUniform("txt_correction",  sf::Vector2f( (float) 0.0, (float) 0.0  )  );
            picture_shader.setUniform("txt_resolution",  sf::Vector2f( sf::Vector2f( texture_from_ffmpeg.getSize().x,texture_from_ffmpeg.getSize().y)  ) );

            sf::Sprite sprite;
            tussen_texture.create(texture_from_ffmpeg.getSize().x,texture_from_ffmpeg.getSize().y);
            tussen_texture.clear(sf::Color(0,0,0,0));

            sprite.setTexture(texture_from_ffmpeg,false);
            sprite.setTextureRect({0,0,(int)texture_from_ffmpeg.getSize().x,(int)texture_from_ffmpeg.getSize().y});

            sprite.setOrigin(texture_from_ffmpeg.getSize().x/2,texture_from_ffmpeg.getSize().y/2);
            sprite.setPosition(texture_from_ffmpeg.getSize().x/2,texture_from_ffmpeg.getSize().y/2);

            picture_states.blendMode=sf::BlendAlpha;
            tussen_texture.draw(sprite,picture_states);
            tussen_texture.display();
            if (blending>=1) {
                picture_states.blendMode=MyBlendingMode;
            }
//changethis
            texture_from_ffmpeg.loadFromImage(tussen_texture.getTexture().copyToImage());

            strcpy(error_msg2,"SHADER CONVERTED TO TEXTURE, CAN PUT OFF NOW (ALT-F1/F2,CTRL-S) AND PLOT (F8)");
            error_flag2=1;
            tussen_texture.create(1,1);
            return ;
        }

        float sizex;
        float sizey;
        if (fragment_shader==1 || plot_shader==2) {
            sizex=(float)texture_from_ffmpeg.getSize().x*sprite_from_ffmpeg.getScale().x;
            sizey=(float)texture_from_ffmpeg.getSize().y*sprite_from_ffmpeg.getScale().y;
        } else {
            sizex=0.0;
            sizey=0.0;
        }
        for (x=arx_start; x<=arx_end; x++)
        {
            for (y=ary_start; y<=ary_end; y++)
            {
                number_bitmaps++;
                int arx=(render_picturex+x+totalpicturex*10)%(maxpicturex+1);
                int ary=(render_picturey+y+totalpicturey*10)%(maxpicturey+1);

                if (F2==1 && perform_quit==0)
                {
                    sprintf(line,"PROCESSING %d x %d TO BITMAPS (%d x %d) X=%3d,Y=%3d #=%d/%d",globx,globy, arx_end-arx_start+1,ary_end-ary_start+1,arx,ary,number_bitmaps,(arx_end-arx_start+1)*(ary_end-ary_start+1));
                    blitter(line,1);
                }
                if (totalused>MAXINMEM)
                {
                    if (F2==1 && perform_quit==0)
                    {
                        strcat(line," SAVING BITMAP");
                        blitter(line,1);
                    }

                    int oldx=picturex,oldy=picturey;
                    picturex=arx;picturey=ary;

                    int render_oldx=render_picturex,render_oldy=render_picturey;
                    render_picturex=arx;render_picturey=ary;

                    go_save_some_bitmaps();
                    if (totalused>MAXINMEM)
                    {
                        go_save_some_bitmaps();
                        if (totalused>MAXINMEM)
                        {
                            go_save_some_bitmaps();
                            if (totalused>MAXINMEM)
                            {
                                go_save_some_bitmaps();
                                if (totalused>MAXINMEM)
                                {
                                    go_save_some_bitmaps();
                                }
                            }
                        }
                    }
                    picturex=oldx;
                    picturey=oldy;
                    render_picturex=render_oldx;
                    render_picturey=render_oldy;
                }

                if (F2==1  && perform_quit==0)
                {
                    strcat(line," / LOADING BITMAP");
                    blitter(line,1);
                }
                ReadOneBitmap(arx,ary);
                if (plot_all==0) texturemaxinmempoint[used2[arx][ary]]->generateMipmap();
                sprite_from_ffmpeg.setPosition(	-render_posx-x*1920 +  (1920)/2+(float)smooth_x-(float)((int)smooth_x),
                                                -render_posy-y*1080 +  (1080)/2+(float)smooth_y-(float)((int)smooth_y) );
//                sprite_from_ffmpeg.setPosition(	-render_posx-x*1920 +  (1920)/2, -render_posy-y*1080 +  (1080)/2 );
                if (fragment_shader==1 || vertex_shader==1 || buffer_shader==1) {
                    picture_shader.setUniform("pos_correction2",  sf::Vector2f( -render_posx-x*1920 + 1920/2, -render_posy-y*1080 + 1080/2)   );
                    picture_shader.setUniform("pos_correction",  sf::Vector2f( -render_posx-x*1920 - (sizex-1920.0)/2.0  , +render_posy+y*1080 + 1080.0*0.0 + (1080.0-sizey)/2.0  )  );
                    picture_shader.setUniform("txt_correction",  sf::Vector2f( -render_posx-x*1920 - (sizex-1920.0)/2.0  , +render_posy+y*1080 + 1080.0*0.0 + (1080.0-sizey)/2.0  )  );
                }

                if ((plot_front==1 && handler[FFMPEG_SELECT].plot_front==0) || handler[FFMPEG_SELECT].plot_front==1)
                {
                    if ((blending>=1 && handler[FFMPEG_SELECT].blending==0) || handler[FFMPEG_SELECT].blending>=1 ) {
                        if (blending<2 && handler[FFMPEG_SELECT].blending==2) {
                            sf::BlendMode old_mode=picture_states.blendMode;
                            picture_states.blendMode=MyBlendMode[4];
                            texturemaxinmempoint[used2[arx][ary]]->draw(sprite_from_ffmpeg,picture_states);
                            picture_states.blendMode=old_mode;
                        } else
                            texturemaxinmempoint[used2[arx][ary]]->draw(sprite_from_ffmpeg,picture_states);
                    } else {
                        sf::BlendMode old_mode=picture_states.blendMode;
                        picture_states.blendMode=sf::BlendAlpha;
                        texturemaxinmempoint[used2[arx][ary]]->draw(sprite_from_ffmpeg,picture_states);
                        picture_states.blendMode=old_mode;
                    }
                }
                else
                {
                    backup_texture.clear(sf::Color(0,0,0,0));
                    spritemaxinmempoint[used2[arx][ary]]->setPosition(0,0);
                    backup_texture.draw(*spritemaxinmempoint[used2[arx][ary]]);
                    backup_texture.display();

                    texturemaxinmempoint[used2[arx][ary]]->clear(sf::Color(0,0,0,0));
                    texturemaxinmempoint[used2[arx][ary]]->draw(sprite_from_ffmpeg,picture_states);

                    if ((blending>=1 && handler[FFMPEG_SELECT].blending==0) || handler[FFMPEG_SELECT].blending==1 )
                        texturemaxinmempoint[used2[arx][ary]]->draw(backup_sprite,MyBlendingMode);
                    else
                        texturemaxinmempoint[used2[arx][ary]]->draw(backup_sprite);

                }

                if (drawmazes==1 && plot_back==1 && blank_maze==0) DRAWMAZE(arx,ary);
                else {
                    texturemaxinmempoint[used2[arx][ary]]->display();
                    if (plot_all) texturemaxinmempoint[used2[arx][ary]]->generateMipmap();
                }

                if (changed[arx][ary]==0)
                {
                    changed[arx][ary]=1;
                    totalchanged++;
                }
            }
        }
//        if (vertex_shader==1) {
//            sprite_from_ffmpeg.setTexture(texture_from_ffmpeg,false);
//        }
        if (F2==1 && perform_quit==0) {
            sprintf(error_msg,"PROCESSED %d x %d TO BITMAPS (%d x %d) #=%d",globx,globy, arx_end-arx_start+1,ary_end-ary_start+1,number_bitmaps);
            error_flag=1;
        }

        if (reset_normal==1)
        {
            blending=0;
            reset_normal=0;
        }
//        setffmpegfile(); //prevent flash in screen, sprite settings changed or something like that :P
    }

    if (plot_internetfile==1)
    {
        setinternetfile();
        plot_internetfile=0;
//		internetfile=1;

        int addx=0,addy=0;
        int globx=sprite_from_internet.getGlobalBounds().width;
        int globy=sprite_from_internet.getGlobalBounds().height;

        int sprite_posx_start;
        int sprite_posy_start;
        int sprite_posx_end;
        int sprite_posy_end;
        int arx_start;
        int ary_start;
        int arx_end;
        int ary_end;

//        if (rotate_internet==1) {
        sprite_posx_start=-render_posx +  (1920)/2 - globx/2 + maxpixelsx;
        sprite_posy_start=-render_posy +  (1080)/2 - globy/2 + maxpixelsy;
        sprite_posx_end=-render_posx +  (1920)/2 + globx/2 + maxpixelsx;
        sprite_posy_end=-render_posy +  (1080)/2 + globy/2 + maxpixelsy;

        arx_start=sprite_posx_start/1920;
        ary_start=sprite_posy_start/1080;
        arx_end=sprite_posx_end/1920;
        ary_end=sprite_posy_end/1080;

        arx_start=arx_start-totalpicturex;
        ary_start=ary_start-totalpicturey;
        arx_end=arx_end-totalpicturex;
        ary_end=ary_end-totalpicturey;

        sprite_from_internet.setTexture(texture_from_internet,false);

        int number_bitmaps=0;

        if (plot_shader==1 && ((vertex_shader==0 && fragment_shader==0))) {
            strcpy(error_msg2,"NO SHADER SELECTED, CTRL-S PLOT SHADER OFF, ALT-F2 SELECT SHADER");
            error_flag2=1;
            return;
        }

        if ( (vertex_shader==1 || fragment_shader==1) && plot_shader==1) {
            sf::Sprite sprite;
            tussen_texture.create(texture_from_internet.getSize().x,texture_from_internet.getSize().y);
            tussen_texture.clear(sf::Color(0,0,0,0));

            sprite.setTexture(texture_from_internet,false);
            sprite.setTextureRect({0,0,(int)texture_from_internet.getSize().x,(int)texture_from_internet.getSize().y});

            sprite.setOrigin(texture_from_internet.getSize().x/2,texture_from_internet.getSize().y/2);
            sprite.setPosition(texture_from_internet.getSize().x/2,texture_from_internet.getSize().y/2);

//            sprite.setPosition(0.0,0.0);
            picture_shader.setUniform("iResolution",  sf::Vector2f( texture_from_internet.getSize().x,texture_from_internet.getSize().y) );
            picture_shader.setUniform("pos_correction",  sf::Vector2f(  (float) 0.0, (float) 0.0 )  );
            picture_states.blendMode=sf::BlendAlpha;
            tussen_texture.draw(sprite,picture_states);
            tussen_texture.display();
            if (blending>=1) {
//            if (blending>=1|| handler[INTERNET_SELECT].blending==1) {
                picture_states.blendMode=MyBlendingMode;
            }

            texture_from_internet.loadFromImage(tussen_texture.getTexture().copyToImage());
            strcpy(error_msg2,"SHADER CONVERTED TO TEXTURE, CAN PUT OFF NOW (ALT-F1/F2,CTRL-S) AND PLOT (F8)");
            error_flag2=1;
            tussen_texture.create(1,1);
            return ;
        }

        float sizex;
        float sizey;
        if (fragment_shader==1) {
            sizex=(float)texture_from_internet.getSize().x*sprite_from_internet.getScale().x;
            sizey=(float)texture_from_internet.getSize().y*sprite_from_internet.getScale().y;
        }

        for (x=arx_start; x<=arx_end; x++)
        {
            for (y=ary_start; y<=ary_end; y++)
            {
                number_bitmaps++;

                int arx=(render_picturex+x+totalpicturex)%(maxpicturex+1);
                int ary=(render_picturey+y+totalpicturey)%(maxpicturey+1);

                if (F2==1 && perform_quit==0)
                {
                    sprintf(line,"PROCESSING %d x %d TO BITMAPS (%d x %d) X=%3d,Y=%3d #=%d/%d",globx,globy, arx_end-arx_start+1,ary_end-ary_start+1,arx,ary,number_bitmaps,(arx_end-arx_start+1)*(ary_end-ary_start+1));
                    blitter(line,1);
                }
                if (totalused>MAXINMEM)
                {
                    if (F2==1 && perform_quit==0)
                    {
                        strcat(line," SAVING BITMAP");
                        blitter(line,1);
                    }
                    int oldx=picturex,oldy=picturey;
                    picturex=arx;picturey=ary;
                    go_save_some_bitmaps();
                    if (totalused>MAXINMEM+2)
                    {
                        go_save_some_bitmaps();
                        if (totalused>MAXINMEM+4)
                        {
                            go_save_some_bitmaps();
                        }
                    }
                    picturex=oldx;
                    picturey=oldy;
                }

                if (F2==1 && perform_quit==0)
                {
                    strcat(line," / LOADING BITMAP");
                    blitter(line,1);
                }

                ReadOneBitmap(arx,ary);

                sprite_from_internet.setPosition(	-render_posx-x*1920 +  (1920)/2, -render_posy-y*1080 +  (1080)/2 );

                if (fragment_shader==1 || vertex_shader==1 || buffer_shader==1) {
                    picture_shader.setUniform("pos_correction2",  sf::Vector2f( -render_posx-x*1920 + 1920/2, -render_posy-y*1080 + 1080/2)   );
                    picture_shader.setUniform("pos_correction",  sf::Vector2f( -render_posx-x*1920 - (sizex-1920.0)/2.0  , +render_posy+y*1080 + 1080.0*0.0 + (1080.0-sizey)/2.0  )  );
                    picture_shader.setUniform("txt_correction",  sf::Vector2f( -render_posx-x*1920 - (sizex-1920.0)/2.0  , +render_posy+y*1080 + 1080.0*0.0 + (1080.0-sizey)/2.0  )  );
                }

                if ((plot_front==1 && handler[INTERNET_SELECT].plot_front==0) || handler[INTERNET_SELECT].plot_front==1)
                {
                    if ((blending>=1 && handler[INTERNET_SELECT].blending==0) || handler[INTERNET_SELECT].blending>=1 ) {
                        if (blending<2 && handler[INTERNET_SELECT].blending==2) {
                            sf::BlendMode old_mode=picture_states.blendMode;
                            picture_states.blendMode=MyBlendMode[4];
                            texturemaxinmempoint[used2[arx][ary]]->draw(sprite_from_internet,picture_states);
                            picture_states.blendMode=old_mode;
                        } else
                            texturemaxinmempoint[used2[arx][ary]]->draw(sprite_from_internet,picture_states);
                    } else {
                        sf::BlendMode old_mode=picture_states.blendMode;
                        picture_states.blendMode=sf::BlendAlpha;
                        texturemaxinmempoint[used2[arx][ary]]->draw(sprite_from_internet,picture_states);
                        picture_states.blendMode=old_mode;
                    }
                }
                else
                {
                    backup_texture.clear(sf::Color(0,0,0,0));
                    spritemaxinmempoint[used2[arx][ary]]->setPosition(0,0);
                    backup_texture.draw(*spritemaxinmempoint[used2[arx][ary]]);
                    backup_texture.display();

                    texturemaxinmempoint[used2[arx][ary]]->clear(sf::Color(0,0,0,0));
                    texturemaxinmempoint[used2[arx][ary]]->draw(sprite_from_internet,picture_states);

                    if ((blending>=1 && handler[INTERNET_SELECT].blending==0) || handler[INTERNET_SELECT].blending==1 )
                        texturemaxinmempoint[used2[arx][ary]]->draw(backup_sprite,MyBlendingMode);
                    else
                        texturemaxinmempoint[used2[arx][ary]]->draw(backup_sprite);
                }

/*

                if (plot_front==1)
                {
                    if ((blending>=1 && handler[INTERNET_SELECT].blending!=-1) || handler[INTERNET_SELECT].blending==1 ) {
//                    if (blending>=1) {
                        if (handler[INTERNET_SELECT].blending==1)
                            texturemaxinmempoint[used2[arx][ary]]->draw(sprite_from_internet,picture_states);
                        else
                            texturemaxinmempoint[used2[arx][ary]]->draw(sprite_from_internet);
                    }
                    else
                        if (handler[INTERNET_SELECT].blending==1)
                            texturemaxinmempoint[used2[arx][ary]]->draw(sprite_from_internet,picture_states);
                        else
                            texturemaxinmempoint[used2[arx][ary]]->draw(sprite_from_internet);
                }
                else
                {
                    backup_texture.clear(sf::Color(0,0,0,0));
                    spritemaxinmempoint[used2[arx][ary]]->setPosition(0,0);
                    backup_texture.draw(*spritemaxinmempoint[used2[arx][ary]]);
                    backup_texture.display();
                    texturemaxinmempoint[used2[arx][ary]]->clear(sf::Color(0,0,0,0));


                    if (handler[INTERNET_SELECT].blending==1)
                        texturemaxinmempoint[used2[arx][ary]]->draw(sprite_from_internet,picture_states);
                    else
                        texturemaxinmempoint[used2[arx][ary]]->draw(sprite_from_internet);

                    if (blending>=1)
                        texturemaxinmempoint[used2[arx][ary]]->draw(backup_sprite,MyBlendingMode);
                    else
                        texturemaxinmempoint[used2[arx][ary]]->draw(backup_sprite);

                }
*/



                if (drawmazes==1 && plot_back==1 && blank_maze==0) DRAWMAZE(arx,ary);
                else {
                    texturemaxinmempoint[used2[arx][ary]]->display();
                    if (plot_all) texturemaxinmempoint[used2[arx][ary]]->generateMipmap();
                }

                texturemaxinmempoint[used2[arx][ary]]->display();

                if (changed[arx][ary]==0)
                {
                    changed[arx][ary]=1;
                    totalchanged++;
                }
            }
        }
        sprintf(error_msg,"PROCESSED %d x %d TO BITMAPS (%d x %d) #=%d",globx,globy, arx_end-arx_start+1,ary_end-ary_start+1,number_bitmaps);
        error_flag=1;
//        texture_from_internet.create(1,1);
        setinternetfile();
    }

    if (plot_moviefile==1)
    {
        setmoviefile();
        plot_moviefile=0;

        int addx=0,addy=0;

        int globx;
        int globy;
//wow2
        if (blend_on_movie>=1 && ffmpegfile==0) {
            globx=sprite_from_ffmpeg.getGlobalBounds().width;
            globy=sprite_from_ffmpeg.getGlobalBounds().height;
        } else {
            globx=sprite_from_movie.getGlobalBounds().width;
            globy=sprite_from_movie.getGlobalBounds().height;
        }

        if (vertex_shader==1) {
            globx+=200;
            globy+=200;
        }

        int sprite_posx_start;
        int sprite_posy_start;
        int sprite_posx_end;
        int sprite_posy_end;
        int arx_start;
        int ary_start;
        int arx_end;
        int ary_end;

        sprite_posx_start=-render_posx +  (1920)/2 - globx/2 + maxpixelsx;
        sprite_posy_start=-render_posy +  (1080)/2 - globy/2 + maxpixelsy;
        sprite_posx_end=-render_posx +  (1920)/2 + globx/2 + maxpixelsx;
        sprite_posy_end=-render_posy +  (1080)/2 + globy/2 + maxpixelsy;

        arx_start=sprite_posx_start/1920;
        ary_start=sprite_posy_start/1080;
        arx_end=sprite_posx_end/1920;
        ary_end=sprite_posy_end/1080;

        arx_start=arx_start-totalpicturex;
        ary_start=ary_start-totalpicturey;
        arx_end=arx_end-totalpicturex;
        ary_end=ary_end-totalpicturey;

//        sprite_from_movie.setTexture(texture_from_movie_new,false);

        sf::Sprite sprite;
        if (blend_on_movie>=1 && ffmpegfile==0)
        {
            if (tussen_texture.getSize()!=texture_from_ffmpeg.getSize())
            {
                tussen_texture.create(texture_from_ffmpeg.getSize().x,texture_from_ffmpeg.getSize().y);
//                savedata("creating texture",0);
            }

            tussen_texture.clear(sf::Color(0,0,0,0));
            if (smooth==1) tussen_texture.setSmooth(true);
            else tussen_texture.setSmooth(false);

            sf::Vector2f wanted_size = {(float)texture_from_ffmpeg.getSize().x,(float)texture_from_ffmpeg.getSize().y};
            sf::Vector2f new_size;

            sf::Vector2f movie_size = {(float)texture_from_movie_new.getSize().x,(float)texture_from_movie_new.getSize().y};;
//            sf::Vector2f movie_size = live_movie->getSize();
            sf::Vector2f target_size = movie_size;

            extern void logfile(char *line);

            if (movie_size.x==0.0 || movie_size.y==0.0) {
                logfile("ERROR SIZE movie_size PLOT_MOVIEFILE()");
                return;
            }
            float source_ratio = movie_size.x / movie_size.y;
            float target_ratio = wanted_size.x / wanted_size.y;

            if (source_ratio > target_ratio)
            {
                target_size.x = movie_size.x * wanted_size.x / movie_size.x;
                target_size.y = movie_size.y * wanted_size.x / movie_size.x;
            }
            else
            {
                target_size.x = movie_size.x * wanted_size.y / movie_size.y;
                target_size.y = movie_size.y * wanted_size.y / movie_size.y;
            }

            if (target_size.x==0.0 || target_size.y==0.0) {
                logfile("ERROR SIZE target_size PLOT_MOVIEFILE()");
                return;
            }

            if (blend_on_movie==2) {
                if (target_size.x<wanted_size.x) {
                    target_size.y=target_size.y*wanted_size.x/target_size.x;
                    target_size.x=wanted_size.x;
                } else if (target_size.y<wanted_size.y) {
                    target_size.x=target_size.x*wanted_size.y/target_size.y;
                    target_size.y=wanted_size.y;
                }
            }

            new_size = target_size;
            sprite.setScale((float)new_size.x / movie_size.x, (float)new_size.y / movie_size.y);


            sprite.setTexture(texture_from_movie_new,false);
            sprite.setTextureRect({0,0,texture_from_movie_new.getSize().x,texture_from_movie_new.getSize().y});
            sprite.setOrigin(texture_from_movie_new.getSize().x/2,texture_from_movie_new.getSize().y/2);
//            sprite.setScale(sprite_from_movie.getScale());
//wow
//            sprite.setRotation(sprite_from_movie.getRotation());
            sprite.setRotation(0.0);
            sprite.setPosition(texture_from_ffmpeg.getSize().x/2,texture_from_ffmpeg.getSize().y/2);

            tussen_texture.draw(sprite);

            sprite.setTexture(texture_from_ffmpeg,false);
            sprite.setTextureRect({0,0,texture_from_ffmpeg.getSize().x,texture_from_ffmpeg.getSize().y});
            sprite.setOrigin(0.0,0.0);
            sprite.setScale(1.0,1.0);
            sprite.setRotation(0.0);
            sprite.setPosition(0.0,0.0);

            static sf::BlendMode MyBlendingMode_movie(  sf::BlendMode::One,sf::BlendMode::One,sf::BlendMode::Add,
                                                        sf::BlendMode::One,sf::BlendMode::SrcAlpha,sf::BlendMode::Add);

            tussen_texture.draw(sprite,MyBlendingMode_movie);
//            tussen_texture.draw(sprite);
            tussen_texture.display();

            sprite.setTexture(tussen_texture.getTexture(),false);
            sprite.setTextureRect({0,0,(int)tussen_texture.getSize().x,(int)tussen_texture.getSize().y});
//wow3
//            sprite.setRotation(sprite_from_ffmpeg.getRotation());
//            sprite.setRotation(sprite_from_movie.getRotation());
            sprite.setRotation(sprite_from_ffmpeg.getRotation());
            sprite.scale(sprite_from_ffmpeg.getScale());
            sprite.setOrigin(sprite_from_ffmpeg.getOrigin());
        } else {
//            sf::Sprite sprite;
            tussen_texture.create(texture_from_movie_new.getSize().x,texture_from_movie_new.getSize().y);
            tussen_texture.clear(sf::Color(0,0,0,0));
            if (smooth==1) tussen_texture.setSmooth(true);
            else tussen_texture.setSmooth(false);

            sprite.setTexture(texture_from_movie_new,false);
            sprite.setTextureRect({0,0,(int)texture_from_movie_new.getSize().x,(int)texture_from_movie_new.getSize().y});
            sprite.setPosition(0.0,0.0);
            tussen_texture.draw(sprite);
            tussen_texture.display();

            sprite.setTexture(tussen_texture.getTexture(),false);
            sprite.setTextureRect({0,0,(int)tussen_texture.getSize().x,(int)tussen_texture.getSize().y});
            sprite.setRotation(sprite_from_movie.getRotation());
            sprite.scale(sprite_from_movie.getScale());
            sprite.setOrigin(sprite_from_movie.getOrigin());
        }

        int number_bitmaps=0;

        float sizex;
        float sizey;
//wow2
        if (fragment_shader==1 || vertex_shader==1 || plot_shader==2) {
            if (blend_on_movie>=1 && ffmpegfile==0) {
                sizex=(float)texture_from_ffmpeg.getSize().x*sprite_from_ffmpeg.getScale().x;
                sizey=(float)texture_from_ffmpeg.getSize().y*sprite_from_ffmpeg.getScale().y;
            } else {
                sizex=(float)texture_from_movie_new.getSize().x*sprite_from_movie.getScale().x;
                sizey=(float)texture_from_movie_new.getSize().y*sprite_from_movie.getScale().y;
            }
        } else {
            sizex=0.0;
            sizey=0.0;
        }
        for (x=arx_start; x<=arx_end; x++)
        {
            for (y=ary_start; y<=ary_end; y++)
            {
                number_bitmaps++;

                int arx=(render_picturex+x+totalpicturex)%(maxpicturex+1);
                int ary=(render_picturey+y+totalpicturey)%(maxpicturey+1);

                if (F2==1 && perform_quit==0)
                {
                    sprintf(line,"PROCESSING %d x %d TO BITMAPS (%d x %d) X=%3d,Y=%3d #=%d/%d",globx,globy, arx_end-arx_start+1,ary_end-ary_start+1,arx,ary,number_bitmaps,(arx_end-arx_start+1)*(ary_end-ary_start+1));
                    blitter(line,1);
                }
                if (totalused>MAXINMEM)
                {
                    if (F2==1 && perform_quit==0)
                    {
                        strcat(line," SAVING BITMAP");
                        blitter(line,1);
                    }
                    int oldx=picturex,oldy=picturey;
                    picturex=arx;picturey=ary;
                    go_save_some_bitmaps();
                    if (totalused>MAXINMEM+2)
                    {
                        go_save_some_bitmaps();
                        if (totalused>MAXINMEM+4)
                        {
                            go_save_some_bitmaps();
                        }
                    }
                    picturex=oldx;
                    picturey=oldy;
                }

                if (F2==1  && perform_quit==0)
                {
                    strcat(line," / LOADING BITMAP");
                    blitter(line,1);
                }
                ReadOneBitmap(arx,ary);
//daar
                sprite.setPosition(	-render_posx-x*1920 +  (1920)/2, -render_posy-y*1080 +  (1080)/2 );
                if (fragment_shader==1 || vertex_shader==1 || buffer_shader==1) {
                    picture_shader.setUniform("pos_correction2",  sf::Vector2f( -render_posx-x*1920 + 1920/2, -render_posy-y*1080 + 1080/2)   );
                    picture_shader.setUniform("pos_correction",  sf::Vector2f( -render_posx-x*1920 - (sizex-1920.0)/2.0  , +render_posy+y*1080 + 1080.0*0.0 + (1080.0-sizey)/2.0  )  );
                    picture_shader.setUniform("txt_correction",  sf::Vector2f( -render_posx-x*1920 - (sizex-1920.0)/2.0  , +render_posy+y*1080 + 1080.0*0.0 + (1080.0-sizey)/2.0  )  );
                }


                if ((plot_front==1 && handler[MOVIE_SELECT].plot_front==0) || handler[MOVIE_SELECT].plot_front==1)
                {
                    if ((blending>=1 && handler[MOVIE_SELECT].blending==0) || handler[MOVIE_SELECT].blending>=1 ) {
                        if (blending<2 && handler[MOVIE_SELECT].blending==2) {
                            sf::BlendMode old_mode=picture_states.blendMode;
                            picture_states.blendMode=MyBlendMode[4];
                            texturemaxinmempoint[used2[arx][ary]]->draw(sprite,picture_states);
                            picture_states.blendMode=old_mode;
                        } else
                            texturemaxinmempoint[used2[arx][ary]]->draw(sprite,picture_states);
                    } else {
                        sf::BlendMode old_mode=picture_states.blendMode;
                        picture_states.blendMode=sf::BlendAlpha;
                        texturemaxinmempoint[used2[arx][ary]]->draw(sprite,picture_states);
                        picture_states.blendMode=old_mode;
                    }
                }
                else
                {
                    backup_texture.clear(sf::Color(0,0,0,0));
                    spritemaxinmempoint[used2[arx][ary]]->setPosition(0,0);
                    backup_texture.draw(*spritemaxinmempoint[used2[arx][ary]]);
                    backup_texture.display();

                    texturemaxinmempoint[used2[arx][ary]]->clear(sf::Color(0,0,0,0));
                    texturemaxinmempoint[used2[arx][ary]]->draw(sprite,picture_states);

                    if ((blending>=1 && handler[MOVIE_SELECT].blending==0) || handler[MOVIE_SELECT].blending==1 )
                        texturemaxinmempoint[used2[arx][ary]]->draw(backup_sprite,MyBlendingMode);
                    else
                        texturemaxinmempoint[used2[arx][ary]]->draw(backup_sprite);
                }

/*
                if (plot_front==1)
                {
                    if (blending>=1)
                        texturemaxinmempoint[used2[arx][ary]]->draw(sprite,picture_states);
                    else
                        texturemaxinmempoint[used2[arx][ary]]->draw(sprite,picture_states);
                }
                else
                {
                    backup_texture.clear(sf::Color(0,0,0,0));
                    spritemaxinmempoint[used2[arx][ary]]->setPosition(0,0);
                    backup_texture.draw(*spritemaxinmempoint[used2[arx][ary]]);
                    backup_texture.display();

                    texturemaxinmempoint[used2[arx][ary]]->clear(sf::Color(0,0,0,0));
                    texturemaxinmempoint[used2[arx][ary]]->draw(sprite,picture_states);

                    if (blending>=1)
                        texturemaxinmempoint[used2[arx][ary]]->draw(backup_sprite,MyBlendingMode);
                    else
                        texturemaxinmempoint[used2[arx][ary]]->draw(backup_sprite);
                }
*/


                if (drawmazes==1 && plot_back==1 && blank_maze==0) DRAWMAZE(arx,ary);
                else {
                    texturemaxinmempoint[used2[arx][ary]]->display();
                    if (plot_all) texturemaxinmempoint[used2[arx][ary]]->generateMipmap();
                }

                if (changed[arx][ary]==0)
                {
                    changed[arx][ary]=1;
                    totalchanged++;
                }
            }
        }
        if (F2==1 && perform_quit==0) {
            sprintf(error_msg,"PROCESSED %d x %d TO BITMAPS (%d x %d) #=%d",globx,globy, arx_end-arx_start+1,ary_end-ary_start+1,number_bitmaps);
            error_flag=1;
        }
        setmoviefile(); //prevent flash in screen, sprite settings changed or something like that :P
    }

    if (plot_moviefile2==1)
    {
        setmoviefile2();
        plot_moviefile2=0;

        int addx=0,addy=0;
        int globx=sprite_from_movie2.getGlobalBounds().width;
        int globy=sprite_from_movie2.getGlobalBounds().height;

        int sprite_posx_start;
        int sprite_posy_start;
        int sprite_posx_end;
        int sprite_posy_end;
        int arx_start;
        int ary_start;
        int arx_end;
        int ary_end;

        sprite_posx_start=-render_posx +  (1920)/2 - globx/2 + maxpixelsx;
        sprite_posy_start=-render_posy +  (1080)/2 - globy/2 + maxpixelsy;
        sprite_posx_end=-render_posx +  (1920)/2 + globx/2 + maxpixelsx;
        sprite_posy_end=-render_posy +  (1080)/2 + globy/2 + maxpixelsy;

        arx_start=sprite_posx_start/1920;
        ary_start=sprite_posy_start/1080;
        arx_end=sprite_posx_end/1920;
        ary_end=sprite_posy_end/1080;

        arx_start=arx_start-totalpicturex;
        ary_start=ary_start-totalpicturey;
        arx_end=arx_end-totalpicturex;
        ary_end=ary_end-totalpicturey;


//        sprite_from_movie2.setTexture(texture_from_movie2_new,false);

        sf::Sprite sprite;
        tussen_texture.create(texture_from_movie2_new.getSize().x,texture_from_movie2_new.getSize().y);
        tussen_texture.clear(sf::Color(0,0,0,0));

        sprite.setTexture(texture_from_movie2_new,false);
        sprite.setTextureRect({0,0,(int)texture_from_movie2_new.getSize().x,(int)texture_from_movie2_new.getSize().y});
        sprite.setPosition(0.0,0.0);
        tussen_texture.draw(sprite);
        tussen_texture.display();

        sprite.setTexture(tussen_texture.getTexture(),false);
        sprite.setTextureRect({0,0,(int)tussen_texture.getSize().x,(int)tussen_texture.getSize().y});
        sprite.setRotation(sprite_from_movie2.getRotation());
        sprite.scale(sprite_from_movie2.getScale());
        sprite.setOrigin(sprite_from_movie2.getOrigin());

        int number_bitmaps=0;

        float sizex;
        float sizey;
        if (fragment_shader==1) {
            sizex=(float)texture_from_movie2_new.getSize().x*sprite_from_movie2.getScale().x;
            sizey=(float)texture_from_movie2_new.getSize().y*sprite_from_movie2.getScale().y;
        }

        for (x=arx_start; x<=arx_end; x++)
        {
            for (y=ary_start; y<=ary_end; y++)
            {
                number_bitmaps++;

                int arx=(render_picturex+x+totalpicturex)%(maxpicturex+1);
                int ary=(render_picturey+y+totalpicturey)%(maxpicturey+1);

                if (F2==1 && perform_quit==0)
                {
                    sprintf(line,"PROCESSING %d x %d TO BITMAPS (%d x %d) X=%3d,Y=%3d #=%d/%d",globx,globy, arx_end-arx_start+1,ary_end-ary_start+1,arx,ary,number_bitmaps,(arx_end-arx_start+1)*(ary_end-ary_start+1));
                    blitter(line,1);
                }
                if (totalused>MAXINMEM)
                {
                    if (F2==1 && perform_quit==0)
                    {
                        strcat(line," SAVING BITMAP");
                        blitter(line,1);
                    }
                    go_save_some_bitmaps();
                    int oldx=picturex,oldy=picturey;
                    picturex=arx;picturey=ary;
                    if (totalused>MAXINMEM+2)
                    {
                        go_save_some_bitmaps();
                        if (totalused>MAXINMEM+4)
                        {
                            go_save_some_bitmaps();
                        }
                    }
                    picturex=oldx;
                    picturey=oldy;
                }

                if (F2==1 && perform_quit==0)
                {
                    strcat(line," / LOADING BITMAP");
                    blitter(line,1);
                }

                ReadOneBitmap(arx,ary);

                sprite.setPosition(	-render_posx-x*1920 +  (1920)/2, -render_posy-y*1080 +  (1080)/2 );

                if (fragment_shader==1) {
                    picture_shader.setUniform("pos_correction",  sf::Vector2f( -render_posx-x*1920 - (sizex-1920.0)/2.0  , +render_posy+y*1080 + 1080.0*0.0 + (1080.0-sizey)/2.0  )  );
                }


                if ((plot_front==1 && handler[MOVIE2_SELECT].plot_front==0) || handler[MOVIE2_SELECT].plot_front==1)
                {
                    if ((blending>=1 && handler[MOVIE2_SELECT].blending==0) || handler[MOVIE2_SELECT].blending>=1 ) {
                        if (blending<2 && handler[MOVIE2_SELECT].blending==2) {
                            sf::BlendMode old_mode=picture_states.blendMode;
                            picture_states.blendMode=MyBlendMode[4];
                            texturemaxinmempoint[used2[arx][ary]]->draw(sprite,picture_states);
                            picture_states.blendMode=old_mode;
                        } else
                            texturemaxinmempoint[used2[arx][ary]]->draw(sprite,picture_states);
                    } else {
                        sf::BlendMode old_mode=picture_states.blendMode;
                        picture_states.blendMode=sf::BlendAlpha;
                        texturemaxinmempoint[used2[arx][ary]]->draw(sprite,picture_states);
                        picture_states.blendMode=old_mode;
                    }
                }
                else
                {
                    backup_texture.clear(sf::Color(0,0,0,0));
                    spritemaxinmempoint[used2[arx][ary]]->setPosition(0,0);
                    backup_texture.draw(*spritemaxinmempoint[used2[arx][ary]]);
                    backup_texture.display();

                    texturemaxinmempoint[used2[arx][ary]]->clear(sf::Color(0,0,0,0));
                    texturemaxinmempoint[used2[arx][ary]]->draw(sprite,picture_states);

                    if ((blending>=1 && handler[MOVIE2_SELECT].blending==0) || handler[MOVIE2_SELECT].blending==1 )
                        texturemaxinmempoint[used2[arx][ary]]->draw(backup_sprite,MyBlendingMode);
                    else
                        texturemaxinmempoint[used2[arx][ary]]->draw(backup_sprite);
                }

/*
                if (plot_front==1)
                {
                    if (blending>=1)
                        texturemaxinmempoint[used2[arx][ary]]->draw(sprite,picture_states);
//                        texturemaxinmempoint[used2[arx][ary]]->draw(sprite,MyBlendingMode);
                    else
//                        texturemaxinmempoint[used2[arx][ary]]->draw(sprite);
                        texturemaxinmempoint[used2[arx][ary]]->draw(sprite,picture_states);
                }
                else
                {
                    backup_texture.clear(sf::Color(0,0,0,0));
                    spritemaxinmempoint[used2[arx][ary]]->setPosition(0,0);
                    backup_texture.draw(*spritemaxinmempoint[used2[arx][ary]]);
                    backup_texture.display();

                    texturemaxinmempoint[used2[arx][ary]]->clear(sf::Color(0,0,0,0));
                    texturemaxinmempoint[used2[arx][ary]]->draw(sprite,picture_states);

                    if (blending>=1)
                        texturemaxinmempoint[used2[arx][ary]]->draw(backup_sprite,MyBlendingMode);
//                        texturemaxinmempoint[used2[arx][ary]]->draw(backup_sprite,picture_states);
                    else
                        texturemaxinmempoint[used2[arx][ary]]->draw(backup_sprite);
//                        texturemaxinmempoint[used2[arx][ary]]->draw(backup_sprite,picture_states);
                }

*/



                if (drawmazes==1 && plot_back==1 && blank_maze==0) DRAWMAZE(arx,ary);
                else {
                    texturemaxinmempoint[used2[arx][ary]]->display();
                    if (plot_all) texturemaxinmempoint[used2[arx][ary]]->generateMipmap();
                }

                if (changed[arx][ary]==0)
                {
                    changed[arx][ary]=1;
                    totalchanged++;
                }
            }
        }
        sprintf(error_msg,"PROCESSED %d x %d TO BITMAPS (%d x %d) #=%d",globx,globy, arx_end-arx_start+1,ary_end-ary_start+1,number_bitmaps);
        error_flag=1;
        setmoviefile2(); //prevent flash in screen, sprite settings changed or something like that :P
    }
}
