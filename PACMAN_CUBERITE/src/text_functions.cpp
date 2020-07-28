#define SFML_STATIC
#undef UNICODE
#include <wchar.h>
#include <winsock2.h>
#include <io.h>
#include "WinMain.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
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

extern int ffmpeg_recurse;
extern void savedata(char *naam, int data);
extern sf::Text text;
extern sf::RenderWindow SFMLView1;
extern sf::Texture texture_from_ffmpeg;
extern set_mono(int on_off);

void draw2(char *towrite, int xpos, int ypos, sf::Color inner, sf::Color outer)
{
    text.setString(towrite);

    text.setOutlineColor(outer);
    text.setOutlineThickness(2.0);
    text.setFillColor(inner);
    text.setPosition(xpos,ypos);
    SFMLView1.draw(text);

    text.setFillColor(sf::Color::White);
}

void draw__on_texture(sf::RenderTexture& texture, char *towrite, int xpos, int ypos, sf::Color inner, sf::Color outer)
{
    text.setString(towrite);

    text.setOutlineColor(outer);
    text.setOutlineThickness(2.0);
    text.setFillColor(inner);
    text.setPosition(xpos,ypos);
    texture.draw(text);

    text.setFillColor(sf::Color::White);
}

void draw3(char *towrite, int xpos, int ypos, sf::Color inner, sf::Color outer)
{
    text.setString(towrite);
    text.setOutlineColor(outer);
    text.setOutlineThickness(2.0);
    text.setFillColor(inner);
    float bound=text.getGlobalBounds().width;
    text.setPosition(xpos-bound,ypos);
    SFMLView1.draw(text);
    text.setFillColor(sf::Color::White);
}

extern int GETFONT(char *naam);

long getMicrotime(){
	struct timeval currentTime;
	gettimeofday(&currentTime, NULL);
	return currentTime.tv_sec * (int)1e6 + currentTime.tv_usec;
}

sf::Font myfont;
sf::Text mytext;
char font_name[2000]="resources/ariblk.ttf";

void getFileNameFromPath(char* path)
{
    char * fn;
    char path_copy[2000];
    strcpy(path_copy,path);
    (fn = strrchr(path_copy, '\\')) ? ++fn : (fn = path_copy);
    strcpy(path,fn);
    return;
}

void mydraw(char *towrite, int xpos, int ypos, sf::Color inner, sf::Color outer)
{
    mytext.setString(towrite);
    mytext.setOutlineColor(outer);
    mytext.setOutlineThickness(2.0);
    mytext.setFillColor(inner);
    mytext.setPosition(xpos,ypos);
    SFMLView1.draw(mytext);
    mytext.setFillColor(sf::Color::White);
}

extern int ffmpegfile;
extern int size_ffmpeg;
extern int rotate_ffmpeg;
extern sf::Sprite sprite_from_ffmpeg;
extern float scale_now;
extern sf::Texture texture_from_ffmpeg;
extern float rotation_ffmpeg;
extern float rot_speed_ffmpeg;
extern sf::RenderTexture tussen_texture;
extern int smooth;
extern void setffmpegfile();
void set_mytext(int next_font);
sf::RenderTexture font_texture;

void set_mytext(int next_font) {
    static int first=0;
    static int first_set=0;
    int xsize;
    int ysize;
    int newfont=1;

    if (first==0) {
        myfont.loadFromFile(font_name);
        mytext.setFont(myfont);
        mytext.setFont(myfont);
        mytext.setFillColor(sf::Color::White);
        mytext.setCharacterSize(24);
        first=1;
        return;
    }
    if (next_font==1) {
        GETFONT(font_name);
        if (!myfont.loadFromFile(font_name))
            if (!myfont.loadFromFile(font_name))
                if (!myfont.loadFromFile(font_name))
                    if (!myfont.loadFromFile(font_name))
                        if (!myfont.loadFromFile(font_name))
                            if (!myfont.loadFromFile(font_name))
                                return;
        mytext.setFont(myfont);
        printf("Font loaded: %s\n",font_name);
    }
    return;
}

sf::Font myfont2;
sf::Text mytext2;
sf::Text mytext3;

void set_mytext2() {
    myfont2.loadFromFile("resources/consolab.ttf");
    mytext2.setFont(myfont2);
    mytext2.setFillColor(sf::Color::White);
    mytext2.setCharacterSize(24);
    mytext3.setFont(myfont2);
    mytext3.setFillColor(sf::Color::White);
    mytext3.setCharacterSize(16);
}

void mydraw2(char *towrite, int xpos, int ypos, sf::Color inner, sf::Color outer)
{
    mytext2.setString(towrite);
    mytext2.setOutlineColor(outer);
    mytext2.setOutlineThickness(2.0);
    mytext2.setFillColor(inner);
    mytext2.setPosition(xpos,ypos);
//    mytext2.setOrigin(mytext2.getLocalBounds().left,mytext2.getLocalBounds().top);
    mytext2.setPosition(xpos+mytext2.getOutlineThickness(),ypos+mytext2.getOutlineThickness());
    mytext2.setOrigin(0,0);
    SFMLView1.draw(mytext2);
    mytext2.setFillColor(sf::Color::White);
}


void mydraw_texture(char *towrite, int xpos, int ypos, sf::Color inner, sf::Color outer, sf::RenderTexture * m_texture)
{
    mytext3.setString(towrite);
    mytext3.setOutlineColor(outer);
    mytext3.setOutlineThickness(1.0);
    mytext3.setFillColor(inner);
    mytext3.setPosition(xpos,ypos);
    mytext3.setPosition(xpos+mytext3.getOutlineThickness(),ypos+mytext3.getOutlineThickness());
    mytext3.setOrigin(0,0);
    m_texture->draw(mytext3);
}


void make_text(int next_font) {
    static sf::Font myfont;
    static sf::Text mytext;
    static char font_name[200]="resources/ariblk.ttf";
    static int first=0;
    static int first_set=0;
    int xsize;
    int ysize;
    long mytime=getMicrotime();
    char mytime_text[100];
    int newfont=1;
/*
    time_t seconds;
    seconds = time(NULL);
    double mytime=seconds;
*/
    if (first==0) {
        myfont.loadFromFile(font_name);
        mytext.setFont(myfont);
        first=1;
        return;
    }
    if (next_font==1) {
        GETFONT(font_name);
        myfont.loadFromFile(font_name);
        mytext.setFont(myfont);
    }
//    sprintf(mytime_text,"%lld\n",mytime);
    strcat(mytime_text,font_name);

    mytext.setString(font_name);
    mytext.setRotation((float)mytime/1000000*360/60);
    mytext.setCharacterSize(72);
    mytext.setScale(1,1);
    mytext.setFillColor(sf::Color::Blue);
    mytext.setOutlineColor(sf::Color::White);
    mytext.setOutlineThickness(1);
    mytext.setStyle(sf::Text::Regular);   // Regular, Bold, Italic, Underlined, StrikeThrough
    if (next_font==1 || first_set==0) {
        first_set=1;
        xsize=mytext.getLocalBounds().width;
        ysize=mytext.getLocalBounds().height;
        mytext.setOrigin((int)(xsize/2),(int)(ysize/2));
    }
//    xsize=mytext.getGlobalBounds().width;
//    ysize=mytext.getGlobalBounds().height;
    mytext.setPosition((int)(1920/2),(int)(1080/2));
    SFMLView1.draw(mytext);
    return;
}

extern int var_font;

extern wchar_t line_w[];

void text_to_ffmpeg(char * in,int font_size, sf::Color inner, sf::Color outer) {
    sf::Text *mytext_var;

    if (var_font==1) mytext_var=&mytext;
    else mytext_var=&mytext2;
    float font_size_old=mytext_var->getCharacterSize();

    mytext_var->setString(in);

    mytext_var->setOutlineColor(outer);
    mytext_var->setFillColor(inner);
    mytext_var->setOutlineThickness(2.0);
//    mytext_var->setFillColor(sf::Color::Red);
//    mytext_var->setPosition(mytext_var->getOutlineThickness()*2,mytext_var->getOutlineThickness()*2);
    mytext_var->setPosition(0,0);

    float s=(float)font_size;
    mytext_var->setCharacterSize(s);
    int xsize=9999999;
    int ysize=9999999;
    while ((xsize>1850 ) && s>10) {
        xsize=mytext_var->getGlobalBounds().width+mytext_var->getOutlineThickness()*4;
//        xsize=mytext_var->getGlobalBounds().width+mytext_var->getOutlineThickness()*2;
//        ysize=mytext.getGlobalBounds().height+mytext.getOutlineThickness()*2;
        if ((xsize>1850 ) && s>10) {
            s=s-1;
            mytext_var->setCharacterSize((int)s);
        }
    }
//    ysize=s+mytext_var->getOutlineThickness()*4;
    mytext_var->setString("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ`~!@#$%^&*()_+1234567890{}[];:'\"\|,<.>/?");

    ysize=mytext_var->getGlobalBounds().height+mytext_var->getOutlineThickness()*2;


//    mytext_var->setOrigin(mytext_var->getGlobalBounds().left,mytext_var->getGlobalBounds().top);
//    mytext_var->setOrigin(mytext_var->getOutlineThickness()*2,mytext_var->getOutlineThickness()*2+2);
//    mytext_var->setOrigin(mytext_var->getLocalBounds().left,mytext_var->getOutlineThickness()*2);
    mytext_var->setOrigin(mytext_var->getLocalBounds().left-mytext_var->getOutlineThickness()*2,mytext_var->getLocalBounds().top);
    mytext_var->setString(in);

    texture_from_ffmpeg.create(xsize,ysize);
    font_texture.create(xsize,ysize);
    font_texture.clear(sf::Color(255,255,255,0));

    if (smooth==1) font_texture.setSmooth(true); else font_texture.setSmooth(false);
    if (smooth==1) texture_from_ffmpeg.setSmooth(true); else texture_from_ffmpeg.setSmooth(false);
    font_texture.draw(*mytext_var);
    font_texture.display();

    texture_from_ffmpeg.update(font_texture.getTexture());
    texture_from_ffmpeg.generateMipmap();
    ffmpegfile=0;
    sprite_from_ffmpeg.setTexture(texture_from_ffmpeg,true);
    mytext_var->setCharacterSize(font_size_old);
}

extern bool file_exists(const char * filename);
int font_to_ffmpeg_size=0;
char fn[2000]="";

void font_to_ffmpeg() {
    static float s=288;

    set_mytext(1);

    if (font_to_ffmpeg_size==0) {
        if (file_exists("text.txt")) {
            if (FILE * file = fopen("text.txt", "r"))
            {
                strcpy(fn,"");
                char fn2[2000]="";
                while ( fgets (fn2,2000, file)!=NULL ) {
                    sprintf(fn,"%s%s",fn,fn2);
    //                sprintf(fn,"Fuck\nthe\nSystem");
    //                sprintf(fn,fn2);
                }
                mytext.setString(fn);
                fclose(file);
            }
            else
                mytext.setString("text.txt is empty?");
        } else {
            strcpy(fn,font_name);
            getFileNameFromPath(fn);
            mytext.setString(fn);
        }
    }

    if (ffmpegfile==0) {
        s=s*sprite_from_ffmpeg.getScale().x;
    } else if (font_to_ffmpeg_size==0) {
        s=288;
    }
    mytext.setCharacterSize(s);
//    mytext.setOutlineThickness(2);
    mytext.setOutlineThickness(s/27);

//    mytext.setOutlineColor(sf::Color(55,55,255,255));
//    mytext.setFillColor(sf::Color(0,0,0,255));
    mytext.setOutlineColor(sf::Color(255,255,255,255));
    mytext.setFillColor(sf::Color(255,255,0,255));


//    mytext.setOutlineThickness(10.0*sprite_from_ffmpeg.getScale().x);
//    mytext.setOutlineThickness(10.0*sprite_from_ffmpeg.getScale().x);
//    mytext.setFillColor(sf::Color::White);
//    mytext.setFillColor(sf::Color(rand()%256,rand()%256,rand()%256,255));


    mytext.setPosition(mytext.getOutlineThickness(),mytext.getOutlineThickness());

    int xsize=9999999;
    int ysize=9999999;
    xsize=mytext.getGlobalBounds().width+mytext.getOutlineThickness()*2;
    ysize=mytext.getGlobalBounds().height+mytext.getOutlineThickness()*2;
//    while ((xsize>4000 || ysize>4000) && s>10) {
//        xsize=mytext.getGlobalBounds().width+mytext.getOutlineThickness()*2;
//        ysize=mytext.getGlobalBounds().height+mytext.getOutlineThickness()*2;
//        if ((xsize>4000 || ysize>4000) && s>10) {
//            s=s/2;
//            mytext.setCharacterSize((int)s);
//        }
//    }
//    if (s<=10) return;

    char line[100];

    mytext.setOrigin(mytext.getGlobalBounds().left,mytext.getLocalBounds().top);
    mytext.setOrigin(mytext.getGlobalBounds().left,mytext.getLocalBounds().top);
//    sprintf(line,"before font to ffmpeg: size = X=%d,Y=%d",xsize,ysize);
//    savedata(line,0);
    texture_from_ffmpeg.create(xsize,ysize);
    font_texture.create(xsize,ysize);
    font_texture.clear(sf::Color(0,0,0,0));

    if (smooth==1) font_texture.setSmooth(true); else font_texture.setSmooth(false);
    if (smooth==1) texture_from_ffmpeg.setSmooth(true); else texture_from_ffmpeg.setSmooth(false);
    font_texture.draw(mytext);
    font_texture.display();

    texture_from_ffmpeg.update(font_texture.getTexture());
    texture_from_ffmpeg.generateMipmap();
    ffmpegfile=0;
//    size_ffmpeg=1;
//    rotate_ffmpeg=0;
//    sprite_from_ffmpeg.setScale(1.0,1.0);
//    scale_now=1.0;
//    rotation_ffmpeg=0.0;
//    rot_speed_ffmpeg=0.0;
    sprite_from_ffmpeg.setTexture(texture_from_ffmpeg,true);
//    setffmpegfile();

    mytext.setCharacterSize(24);
}


void text_to_ffmpeg_w(wchar_t * in,int font_size, sf::Color inner, sf::Color outer, sf::Uint32 type) {
    sf::Text *mytext_var;

    if (var_font==1) {
        mytext_var=&mytext;
    }
    else mytext_var=&mytext2;
    float font_size_old=mytext_var->getCharacterSize();
    mytext_var->setStyle(type);


//    mytext_var->setString(in);
    mytext_var->setString((wchar_t *) in);
//    mytext_var->setString((wchar_t*)line_w);
    mytext_var->setOutlineColor(outer);
    mytext_var->setFillColor(inner);
    if (font_size<24) mytext_var->setOutlineThickness(0.0);
    else mytext_var->setOutlineThickness(3.0);
//    else mytext_var->setOutlineThickness(2.0);
//    printf("olt=%f\n",mytext_var->getOutlineThickness());
//    else mytext_var->setOutlineThickness(1*font_size/24);
//    mytext_var->setFillColor(sf::Color::Red);
//    mytext_var->setPosition(mytext_var->getOutlineThickness()*2,mytext_var->getOutlineThickness()*2);
    mytext_var->setPosition(0,0);

    float s=(float)font_size;
    mytext_var->setCharacterSize(s);
    int xsize=9999999;
    int ysize=9999999;
//    xsize=9999999;
//    ysize=9999999;
    while ((xsize>32000 ) && s>10) {
        xsize=mytext_var->getGlobalBounds().width+mytext_var->getOutlineThickness()*4;

        if ((xsize>32000 ) && s>10) {
            s=s-1;
            mytext_var->setCharacterSize((int)s);
        }
    }
//    ysize=s+mytext_var->getOutlineThickness()*4;
    mytext_var->setString("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZàáâãäæçèéêëíîïğñòóôõöùúûüışÿ`~!@#$%^&*()_+1234567890{}[];:'\"\|,<.>/?");

    ysize=mytext_var->getGlobalBounds().height+mytext_var->getOutlineThickness()*2;

//    mytext_var->setOrigin(mytext_var->getGlobalBounds().left,mytext_var->getGlobalBounds().top);
//    mytext_var->setOrigin(mytext_var->getOutlineThickness()*2,mytext_var->getOutlineThickness()*2+2);
//    mytext_var->setOrigin(mytext_var->getLocalBounds().left,mytext_var->getOutlineThickness()*2);
    mytext_var->setOrigin(mytext_var->getLocalBounds().left-mytext_var->getOutlineThickness()*2,mytext_var->getLocalBounds().top);
    mytext_var->setString((wchar_t*)line_w);
//    mytext_var->setString(in);

    texture_from_ffmpeg.create(xsize,ysize);
    font_texture.create(xsize,ysize);
    font_texture.clear(sf::Color(255,255,255,0));

    if (smooth==1) font_texture.setSmooth(true); else font_texture.setSmooth(false);
    if (smooth==1) texture_from_ffmpeg.setSmooth(true); else texture_from_ffmpeg.setSmooth(false);
    font_texture.draw(*mytext_var);
    font_texture.display();

    texture_from_ffmpeg.update(font_texture.getTexture());
    texture_from_ffmpeg.generateMipmap();
    ffmpegfile=0;
    sprite_from_ffmpeg.setTexture(texture_from_ffmpeg,true);
    mytext_var->setCharacterSize(font_size_old);
}

