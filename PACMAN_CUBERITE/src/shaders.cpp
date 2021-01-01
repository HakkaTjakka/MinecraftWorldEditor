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
extern int GETSHADER_BUFFER(char *naam);
extern int GETSHADER_VERTEX(char *naam);
extern int GETSHADER_GEOMETRY(char *naam);
extern int GETSHADER_FRAGMENT(char *naam, int up_down);
extern char SHADERDIR[];

//extern int use_buffer;
//sf::Shader channel0_shader;
extern sf::Sprite *sprite_buffer;
extern int iFrame;
extern int swapper;
extern int BITMAPSX;
extern int BITMAPSY;
extern int fragment_shader;
extern int vertex_shader;
extern int buffer_shader;

extern sf::Shader picture_shader;
extern sf::Shader shader_buffer;
extern sf::RenderStates picture_states;
extern sf::RenderStates buffer_states;
extern bool file_exists(const char * filename);
extern char error_msg2[];
extern int error_flag2;
extern char error_msg3[];
extern int error_flag3;

extern int internetfile;
extern int ffmpegfile;
extern int movie;
extern int movie2;

extern sf::Texture texture_from_internet;
extern sf::Texture texture_from_ffmpeg;
extern sf::Texture texture_from_movie_new;
extern sf::Texture texture_from_movie2_new;
extern sf::RenderTexture texture_from_buffer;
extern sf::RenderTexture texture_from_buffer2;
sf::RenderTexture texture_data;

int shader_ok=0;
//sf::RenderTexture iChannel0;
char frag_name[2000];
char vert_name[2000];
char buf_name[2000];

int load_fragment_filename(int up_down) {
    static int frag_next=0;

    sprintf(frag_name,"%s/fragment/picture_shader.frag",SHADERDIR);
    if (!file_exists(frag_name)) {
        GETSHADER_FRAGMENT(frag_name,up_down);
        if (!file_exists(frag_name)) {
            fragment_shader=0;
            sprintf(error_msg2,"FRAGMENT SHADER NOT FOUND: %s",frag_name);
            error_flag2=1;
            return 0;
        }
    }
    sprintf(error_msg2,"FRAGMENT SHADER FOUND: %s",frag_name);
    error_flag2=1;
}

int load_vertex_filename() {
    if (vertex_shader==1) {
        sprintf(vert_name,"%s/vertex/picture_shader.vert",SHADERDIR);
        if (!file_exists(vert_name)) {
            GETSHADER_VERTEX(vert_name);
            if (!file_exists(vert_name)) {
                vertex_shader=0;
                sprintf(error_msg2,"VERTEX SHADER NOT FOUND: %s",vert_name);
                error_flag2=1;
                return 0;
            }
        }
    }
    sprintf(error_msg2,"VERTEX SHADER FOUND: %s",frag_name);
    error_flag2=1;
}

int load_buffer_filename() {

    sprintf(buf_name,"%s/buffer/picture_shader.frag",SHADERDIR);
    if (!file_exists(buf_name)) {
        GETSHADER_BUFFER(buf_name);
        if (!file_exists(buf_name)) {
            buffer_shader=0;
            sprintf(error_msg2,"BUFFER SHADER NOT FOUND: %s",buf_name);
            error_flag2=1;
            return 0;
        }
    }
    sprintf(error_msg2,"BUFFER SHADER FOUND: %s",buf_name);
    error_flag2=1;
}


int update_shader() {
//    static int frag_next=0;
//    char frag_name[2000];

/*
    if (fragment_shader==1) {
        sprintf(frag_name,"%s/fragment/picture_shader.frag");
        if (!file_exists(frag_name)) {
            GETSHADER_FRAGMENT(frag_name,up_down);
            if (!file_exists(frag_name)) {
                fragment_shader=0;
                sprintf(error_msg2,"FRAGMENT SHADER NOT FOUND: %s",frag_name);
                strcat(error_msg2,frag_name);
                error_flag2=1;
                return 0;
            }
        }
*/

/*        if (file_exists("shaders/picture_shader.frag")) {
            strcpy(frag_name,"shaders/picture_shader.frag");
        } else {
            if (up_down==-1) frag_next--; else if (up_down==1) frag_next++;
            if (frag_next==0) frag_next==1;
            sprintf(frag_name,"shaders/picture_shader %d.frag",frag_next);
            if (! file_exists(frag_name)) {
                frag_next=1;
                sprintf(frag_name,"shaders/picture_shader %d.frag",frag_next);
            }
        }
        strcpy(error_msg2,"LOADED FRAGMENT SHADER: ");
        strcat(error_msg2,frag_name);
        error_flag2=1;
    }
*/

    if (fragment_shader==1 && vertex_shader==1) {
        if (!picture_shader.loadFromFile(vert_name, frag_name))
//        if (!picture_shader.loadFromFile("shaders/picture_shader.vert", frag_name))
//        if (!picture_shader.loadFromFile("shaders/picture_shader.vert", "shaders/picture_shader.frag"))
        {
            sprintf(error_msg2,"FRAGMENT SHADER ERROR: %s",frag_name);
            error_flag2=1;
            sprintf(error_msg3,"OR VERTEX SHADER ERROR: %s",vert_name);
            error_flag3=1;
            MessageBox(
                NULL,
                error_msg2,
                error_msg3,
                MB_ICONEXCLAMATION | MB_OK | MB_TOPMOST
            );
            vertex_shader=0;
            fragment_shader=0;
            picture_states.shader=NULL;
            shader_ok=0;
            return 1;
        }
        picture_shader.setUniform("texture_in", sf::Shader::CurrentTexture);
        picture_shader.setUniform("iResolution",  sf::Vector2f( 1920.0,1080.0) );
        if (ffmpegfile==0) picture_shader.setUniform("iRealRes",  sf::Vector2f( (float)texture_from_ffmpeg.getSize().x,(float)texture_from_ffmpeg.getSize().y) );
        else if (internetfile==0) picture_shader.setUniform("iRealRes",  sf::Vector2f( (float)texture_from_internet.getSize().x,(float)texture_from_internet.getSize().y) );
        else if (movie==0) picture_shader.setUniform("iRealRes",  sf::Vector2f( (float)texture_from_movie_new.getSize().x,(float)texture_from_movie_new.getSize().y) );
        else if (movie2==0) picture_shader.setUniform("iRealRes",  sf::Vector2f( (float)texture_from_movie2_new.getSize().x,(float)texture_from_movie2_new.getSize().y) );
    }
    else if (fragment_shader==1) {
        if (!picture_shader.loadFromFile(frag_name, sf::Shader::Fragment))
        {
            sprintf(error_msg2,"FRAGMENT SHADER ERROR: %s",frag_name);
            error_flag2=1;
            MessageBox(
                NULL,
                error_msg2,
                (char*)frag_name,
                MB_ICONEXCLAMATION | MB_OK | MB_TOPMOST
            );
            fragment_shader=0;
            picture_states.shader=NULL;
            shader_ok=0;
            return 1;
        }
        picture_shader.setUniform("texture_in", sf::Shader::CurrentTexture);
        picture_shader.setUniform("texture_buffer", texture_from_buffer.getTexture());
        picture_shader.setUniform("iResolution",  sf::Vector2f( (float)texture_from_ffmpeg.getSize().x,(float)texture_from_ffmpeg.getSize().y) );
    } else if (vertex_shader==1) {
//        if (!picture_shader.loadFromFile("shaders/picture_shader.vert", sf::Shader::Vertex))
        if (!picture_shader.loadFromFile(vert_name, sf::Shader::Vertex))
        {
            sprintf(error_msg2,"VERTEX SHADER ERROR: %s",vert_name);
            error_flag2=1;
            MessageBox(
                NULL,
                error_msg2,
                vert_name,
                MB_ICONEXCLAMATION | MB_OK | MB_TOPMOST
            );
            vertex_shader=0;
            picture_states.shader=NULL;
            shader_ok=0;
            return 1;
        }

    }

    if (vertex_shader==1 || fragment_shader==1) {
        picture_states.shader = &picture_shader; shader_ok=1;
        bool first=true;
        if (first) {
            first=false;

            texture_data.setSmooth(TRUE);
            texture_data.generateMipmap();
            texture_data.setRepeated(true);

            sf::Texture texture_load;
            sf::Sprite sprite_load;
            texture_load.loadFromFile("resources/random001.png");
            sprite_load.setTexture(texture_load,true);
            texture_data.create( texture_load.getSize().x , texture_load.getSize().y );
            texture_data.draw(sprite_load);
            texture_data.display();
        }
        picture_shader.setUniform("dResolution",  sf::Vector2f( (float)texture_data.getSize().x,(float)texture_data.getSize().y) );
        picture_shader.setUniform("texture_data", texture_data.getTexture());
    }
    else picture_states.shader=NULL;

    return 0;
}

int update_buffer_shader(int up_down) {
//    static int frag_next=0;
//    char frag_name[100];

/*    if (buffer_shader==1) {
        if (file_exists("shaders/buffer_shader.frag")) {
            strcpy(frag_name,"shaders/buffer_shader.frag");
        } else {
            if (up_down==-1) frag_next--; else frag_next++;
            if (frag_next==0) frag_next==1;
            sprintf(frag_name,"shaders/buffer_shader %d.frag",frag_next);
            if (! file_exists(frag_name)) {
                frag_next=1;
                sprintf(frag_name,"shaders/buffer_shader %d.frag",frag_next);
            }
        }

        strcpy(error_msg2,"LOADED BUFFER SHADER: ");
        strcat(error_msg2,frag_name);
        error_flag2=1;
    }
*/
    if (buffer_shader==1) {
        if (!shader_buffer.loadFromFile(buf_name, sf::Shader::Fragment))
//        if (!shader_buffer.loadFromFile(frag_name, sf::Shader::Fragment))
//        if (!picture_shader.loadFromFile("shaders/picture_shader.frag", sf::Shader::Fragment))
        {
            sprintf(error_msg2,"BUFFER SHADER ERROR: %s",buf_name);
            error_flag2=1;
            MessageBox(
                NULL,
                error_msg2,
                buf_name,
                MB_ICONEXCLAMATION | MB_OK | MB_TOPMOST
            );
            buffer_shader=0;
            return 1;
        }
//        picture_shader.setUniform("iResolution",  sf::Vector2f( 1920.0,1080.0) );
        iFrame=0;
        if (ffmpegfile==0) {
                texture_from_buffer.create((float)texture_from_ffmpeg.getSize().x,(float)texture_from_ffmpeg.getSize().y);
                texture_from_buffer.setRepeated(TRUE);
                texture_from_buffer.setSmooth(TRUE);
                texture_from_buffer2.create((float)texture_from_ffmpeg.getSize().x,(float)texture_from_ffmpeg.getSize().y);
                texture_from_buffer2.setRepeated(TRUE);
                texture_from_buffer2.setSmooth(TRUE);
                sf::Sprite sprite1;
                sprite1.setTexture(texture_from_ffmpeg,true);
                texture_from_buffer.draw(sprite1);
                texture_from_buffer.display();
                texture_from_buffer2.draw(sprite1);
                texture_from_buffer2.display();
                shader_buffer.setUniform("iRealRes",  sf::Vector2f( (float)texture_from_ffmpeg.getSize().x,(float)texture_from_ffmpeg.getSize().y) );
                shader_buffer.setUniform("iResolution",  sf::Vector2f( (float)texture_from_ffmpeg.getSize().x,(float)texture_from_ffmpeg.getSize().y) );
        } else if (movie==0) {
                texture_from_buffer.create((float)texture_from_movie_new.getSize().x,(float)texture_from_movie_new.getSize().y);
                texture_from_buffer.setRepeated(TRUE);
                texture_from_buffer.setSmooth(TRUE);
                texture_from_buffer2.create((float)texture_from_movie_new.getSize().x,(float)texture_from_movie_new.getSize().y);
                texture_from_buffer2.setRepeated(TRUE);
                texture_from_buffer2.setSmooth(TRUE);
                sf::Sprite sprite1;
                sprite1.setTexture(texture_from_movie_new,true);
                texture_from_buffer.draw(sprite1);
                texture_from_buffer.display();
                shader_buffer.setUniform("iRealRes",  sf::Vector2f( (float)texture_from_movie_new.getSize().x,(float)texture_from_movie_new.getSize().y) );
                shader_buffer.setUniform("iResolution",  sf::Vector2f( (float)texture_from_movie_new.getSize().x,(float)texture_from_movie_new.getSize().y) );
        } else if (movie2==0) {
                texture_from_buffer.create((float)texture_from_movie2_new.getSize().x,(float)texture_from_movie2_new.getSize().y);
                texture_from_buffer.setRepeated(TRUE);
                texture_from_buffer.setSmooth(TRUE);
                texture_from_buffer2.create((float)texture_from_movie2_new.getSize().x,(float)texture_from_movie2_new.getSize().y);
                texture_from_buffer2.setRepeated(TRUE);
                texture_from_buffer2.setSmooth(TRUE);
                sf::Sprite sprite1;
                sprite1.setTexture(texture_from_movie2_new,true);
                texture_from_buffer.draw(sprite1);
                texture_from_buffer.display();
                shader_buffer.setUniform("iRealRes",  sf::Vector2f( (float)texture_from_movie2_new.getSize().x,(float)texture_from_movie2_new.getSize().y) );
                shader_buffer.setUniform("iResolution",  sf::Vector2f( (float)texture_from_movie2_new.getSize().x,(float)texture_from_movie2_new.getSize().y) );
        }
        else if (internetfile==0) picture_shader.setUniform("iRealRes",  sf::Vector2f( (float)texture_from_internet.getSize().x,(float)texture_from_internet.getSize().y) );

        swapper=0;
        shader_buffer.setUniform("iFrame",   iFrame );
        shader_buffer.setUniform("texture_in", sf::Shader::CurrentTexture);
        shader_buffer.setUniform("texture_buffer", texture_from_buffer.getTexture());
        picture_shader.setUniform("texture_buffer", texture_from_buffer.getTexture());

//        else if (movie==0) picture_shader.setUniform("iRealRes",  sf::Vector2f( (float)texture_from_movie_new.getSize().x,(float)texture_from_movie_new.getSize().y) );
//        else if (movie2==0) picture_shader.setUniform("iRealRes",  sf::Vector2f( (float)texture_from_movie2_new.getSize().x,(float)texture_from_movie2_new.getSize().y) );

        if (buffer_shader==1) buffer_states.shader = &shader_buffer;
        else buffer_states.shader=NULL;

        sprite_buffer->setTexture(texture_from_buffer.getTexture(),true);

    } else {
        texture_from_buffer2.create((float)1.0,(float)1.0);
        shader_buffer.setUniform("texture_buffer", texture_from_buffer.getTexture());
        picture_shader.setUniform("texture_buffer", texture_from_buffer.getTexture());
    }
    return 0;
}
