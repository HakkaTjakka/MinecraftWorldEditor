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
#include "colorcodes.hpp"

#define PRINT_FONT_SIZE 24
#define PRINT_FONT_OUTLINE 2
extern sf::Mutex animate_lock;
extern char SUBTITLE_FORMAT[];

sf::Clock rec_clock_tot;
sf::Clock rec_clock_frame;
sf::Clock play_clock_tot;
sf::Clock play_clock_frame;

extern sf::RenderTexture texture_final;
sf::RenderTexture texture_final_part;
sf::Sprite sprite_texture_final;

extern int record_pause;
float fps_record_tot=0.0;
float fps_record_frame=0.0;
float fps_playing_tot=0.0;
float fps_playing_frame=0.0;

extern sf::Mutex textfiles;
extern sf::RenderWindow SFMLView1;

sf::Mutex texture_ready_lock;
int texture_ready=0;

int isplaying=false;
sf::Mutex isplaying_lock;
void playing();
sf::Thread thread_playing(&playing);

int isrecording=false;
sf::Mutex isrecording_lock;
void recording_m_orig();
sf::Thread thread_recording_m_orig(&recording_m_orig);

void recording_end();
void recording();

int file_is_ok=0;
int timenow_part=0;
extern char lang_nq[];

extern sf::Mutex burn_next_sub_ready_mutex;
extern void print_to_screen(int var_font, char * text_to_print, int font_size, sf::Color paint_in, sf::Color paint_out, sf::Color paint_back, float outline, sf::Uint32 text_type );

extern void draw2(char *towrite, int xpos, int ypos, sf::Color inner, sf::Color outer);
extern sf::RenderWindow SFMLView1;
extern char raw_name[];
extern char source_time[];
extern void print_to_screen_buf(int var_font, char * text_to_print, int font_size, sf::Color paint_in, sf::Color paint_out, sf::Color paint_back, float outline, sf::Uint32 text_type );

char playing_info_static[1000]="";
char recording_info_static[1000]="";
float playing_time=0.0;
float recording_time=0.0;
extern int record_screen_num;
int playing_screen_num=0;
extern int crop_x;
extern int crop_x_size;
extern int crop;
extern char MOVIEDIR[];
extern select_movie(char *filename, char * path);
int playing_start(char * filename);
extern char error_msg2[];
extern int error_flag2;
extern int play_rate;
extern int rate_count;
extern int movieextern;
void Screenget3();
extern int flop;
extern int record_screen;
extern int recording_type;
extern int end_on_record;
extern burn_next_sub();
extern int replace_str(char *str, char *orig, char *rep);
extern int smooth;
int burn_next_sub_ready=0;
extern char SUBTITLES[];
char quote_subs[1000];
char quote_subs_extra[1000]="";
char quote_video[1000];
char quote_audio[1000];
int burn_subs=0;
extern int blending;
extern bool file_exists(const char * filename);
extern sf::Texture texture_from_ffmpeg;
extern sf::Texture texture_from_internet;
extern int ffmpegfile;
extern int internetfile;
extern int pen;
extern int pen_mode;
extern void savedata(char *naam, int data);
extern int size_internet;
extern int size_ffmpeg;
extern int size_movie;
extern int size_movie2;
extern void setffmpegfile();
extern void setinternetfile();
extern float rotation_ffmpeg;
extern float rotation_internet;
extern sf::Sprite sprite_from_ffmpeg;
extern sf::Sprite sprite_from_crop;
extern sf::Sprite sprite_from_internet;
extern float rot_speed_ffmpeg;
extern float rot_speed_internet;
extern char writer[];
extern int shift;
extern int rotate_ffmpeg;
extern int rotate_internet;
extern void plotplot();

int movie_width=0;
int movie_height=0;
int movie_sample_rate=0;
int movie_channels=0;
int movie_r_frame_rate1=0;
int movie_bit_rate=0;
int movie_r_frame_rate2=0;

sf::SoundBuffer movie_buffer;
int16_t audio_buf[1000000];
sf::Sound movie_sound;

extern sfe::Movie* live_movie;
extern int reload_init();

extern char FFMPEGCOMMAND[];
extern char FFMPEGCOMMAND_RGBA[];
extern int RGBA;
extern char FFMPEGCOMMANDIN[];
extern char FFMPEGCOMMANDIN_SUBS[]; //WHEN BURNING SUBS WITH "GET_VIDEOS" & "BURN_SUBS"
extern char FFMPEGCOMMANDIN_SUBS_RES[]; //WHEN BURNING SUBS WITH "GET_VIDEOS" & "BURN_SUBS"
extern char FFMPEGCOMMANDIN_FILTER_COMPLEX[];
extern char FFMPEGCOMMAND_M_ORIG[];
extern char FFMPEGCOMMAND_M_ORIG_AUDIO[];
extern char FFMPEGCOMMAND_CROP[];
extern char FFMPEGCOMMAND_CROP_RGBA[];
extern char FFMPEGCOMMAND_SCREENSHOT[];

char command_line[2000];

extern sf::Texture texture_from_movie_new;
extern sf::Texture texture_from_movie2_new;

unsigned char frame[1920*1080*4*4]; //??? *4 for 4k
//unsigned char frame[1920*1080*4*4*4]; //??? *4 for 4k
//unsigned char frame[1920*1080*3];
unsigned char frame_in[1920*1080*4*4]; //?????????????? ;/

FILE *pipeout;
FILE *pipein;
FILE *pipein_audio;

sf::Texture rec_texture;
sf::Texture rec_texture_in;

sf::Image * rec_image=NULL;
sf::Image * rec_image_part=NULL;
sf::Image * rec_image_in=NULL;

extern sf::Texture texture_from_ffmpeg;
extern sf::Texture texture_from_internet;

extern char record_outputfile[];
extern char record_outputfile_nq[];
void recording_m_orig();

char playing_filename[1000];

bool get_screenshot(sf::Texture* m_texture) {
    char command_line[2000];
    unsigned char* frame_in = (unsigned char*) calloc(1920*1080*4,1);
//    unsigned char frame_in[1920*1080*4];

    if (strlen(FFMPEGCOMMAND_SCREENSHOT)>0)
        sprintf(command_line,"%s",FFMPEGCOMMAND_SCREENSHOT);
    else
        sprintf(command_line,"%s","ffmpeg -rtbufsize 1024M -thread_queue_size 1024 -f gdigrab -i desktop -vframes 1 -q:v 2 -f image2pipe -vcodec rawvideo -pix_fmt rgba -");
    printf("COMMAND: %s\n",FFMPEGCOMMAND_SCREENSHOT);
    FILE* file;
    if (file=fopen("../convert/files/convert.log","a")) {
        fprintf(file,"%s\n",command_line);
        fclose(file);
    }
    FILE *pipein;
    pipein = popen(command_line, "rb");
    if (pipein==NULL) {
        printf("\nFailed to open pipe\n");
        return false;
    }
    int num_bytes=fread(frame_in, 1, 1920*1080*4, pipein);
    pclose(pipein);

    m_texture->create(1920,1080);
    m_texture->setSrgb(false);
    m_texture->setSmooth(false);

    m_texture->update((sf::Uint8*)frame_in);
    m_texture->copyToImage().saveToFile("screenshot.png");
    return true;
}
extern char quote_subs_extra2[];

int playing_start(char * filename)
{
    strcpy(playing_filename,filename);

    playing_screen_num=0;
    char quote_filename[1000];
    int timenow= time(0);
    int movie_width_prev=movie_width;
    int movie_height_prev=movie_height;
//    reload_init();
    sprintf(quote_filename,"\"%s\"",filename);

    if (!file_exists(filename)) {
        printf("File %s not found. Run makelist.bat in dir set to MOVIEDIR (pacman.ini)\n");
        return -1;
    }
// ffprobe -v error -select_streams v:0 -show_entries stream=width,height -of default=nw=1 holland_sound.mp4
    sprintf(command_line,"ffprobe.exe -v error -select_streams v:0 -show_entries stream=width,height,r_frame_rate,bit_rate -of default=nw=1 %s",quote_filename);
    FILE* file;
    if (file=fopen("../convert/files/convert.log","a")) {
        fprintf(file,"%s\n",command_line);
        fclose(file);
    }

    pipein = popen(command_line, "rb");
    if (pipein!=NULL) {
        char line1[100];
        char line2[100];
        char line3[100];
        char line4[100];
        fgets(line1,100,pipein);
        fgets(line2,100,pipein);
        fgets(line3,100,pipein);
        fgets(line4,100,pipein);
        pclose(pipein);

        if (strcmp(FFMPEGCOMMANDIN_SUBS_RES,"HD")==0) {
            printf("RECORDING IN HD\n");
            movie_width=1920;
            movie_height=1080;
        } else {
            printf("FUCK: %s\n",FFMPEGCOMMANDIN_SUBS_RES);
            sscanf(line1,"width=%d",&movie_width);
            sscanf(line2,"height=%d",&movie_height);
        }

        sscanf(line3,"r_frame_rate=%d/%d",&movie_r_frame_rate1,&movie_r_frame_rate2);
        sscanf(line4,"bit_rate=%d",&movie_bit_rate);
//        printf("FFPROBE: width=%d height=%d framerate=%d/%d\n",movie_width,movie_height,movie_r_frame_rate1,movie_r_frame_rate2);
    } else {
        printf("Error: %s\n",command_line);
        printf("ffprobe.exe not in path?\n",command_line);
        printf(command_line);
        printf("\n");
        return -1;
    }

    if (!burn_subs) {
        sprintf(command_line,"ffprobe.exe -v error -select_streams a:0 -show_entries stream=sample_rate,channels -of default=nw=1 %s",quote_filename);
        FILE* file;
        if (file=fopen("../convert/files/convert.log","a")) {
            fprintf(file,"%s\n",command_line);
            fclose(file);
        }
        pipein = popen(command_line, "rb");
        if (pipein!=NULL) {
            char line1[100];
            char line2[100];
            if (fgets(line1,100,pipein)!=0) {
                fgets(line2,100,pipein);
                pclose(pipein);
                sscanf(line1,"sample_rate=%d",&movie_sample_rate);
                sscanf(line2,"channels=%d",&movie_channels);
                printf("sample_rate=%d channels=%d\n",movie_sample_rate,movie_channels);
                movie_sound.setBuffer(movie_buffer);
            } else {
                pclose(pipein);
                movie_sample_rate=0;
                movie_channels=0;
                printf("No audio detected\n");
            }
        } else {
            printf("Error: %s\n",command_line);
            printf("ffprobe.exe not in path?\n",command_line);
            printf(command_line);
            printf("\n");
            return -1;
        }
        if (movie_r_frame_rate2!=0)
            sprintf(playing_info_static,"Resolution=%dx%d - Framerate=%d/%d=%5.3f Fps - Samplerate: %d Hz %d Bitrate: %d Channels\nFile=\"%s\"",
                    movie_width,movie_height,movie_r_frame_rate1,movie_r_frame_rate2,(float)movie_r_frame_rate1/(float)movie_r_frame_rate2,
                    movie_sample_rate,movie_channels,movie_bit_rate,filename
                    );
        else
            sprintf(playing_info_static,"Resolution=%dx%d - Framerate=%d/%d=??? Fps - Samplerate: %d Hz %d Bitrate: %d Channels\nFile=\"%s\"",
                    movie_width,movie_height,movie_r_frame_rate1,movie_r_frame_rate2,
                    movie_sample_rate,movie_channels,movie_bit_rate,filename
                    );
    } else {
        if (movie_r_frame_rate2!=0)
            sprintf(playing_info_static,"Time=%s - Resolution: %dx%d - Framerate=%d/%d=%5.3f Fps Bitrate: %d \nFile=%s\nSubs=%s",
                    source_time,movie_width,movie_height,
                    movie_r_frame_rate1,movie_r_frame_rate2,(float)movie_r_frame_rate1/(float)movie_r_frame_rate2,
                    movie_bit_rate,quote_video,quote_subs);
        else
            sprintf(playing_info_static,"Time=%s - Resolution: %dx%d - Framerate=%d/%d=??? Fps Bitrate: %d \nFile=%s\nSubs=%s ",
                    source_time,movie_width,movie_height,movie_r_frame_rate1,movie_r_frame_rate2,
                    movie_bit_rate,quote_video,quote_subs);
            print_to_screen_buf(1,playing_info_static,PRINT_FONT_SIZE,COL_BLUE,COL_WHITE,COL_WHITE_T,PRINT_FONT_OUTLINE,TXT_REG);
    }
//?????????
    if (burn_subs) {
        if (strlen(FFMPEGCOMMANDIN_SUBS)>0) {
//            std::string better;
            char better[5000]="";
            char better2[5000]="";

            sprintf(better2,FFMPEGCOMMANDIN_FILTER_COMPLEX,quote_subs_extra2);
            sprintf(better,"\"%s\"",better2);

//            sprintf(command_line,FFMPEGCOMMANDIN_SUBS,quote_filename,quote_subs_extra);

            sprintf(command_line,FFMPEGCOMMANDIN_SUBS,quote_filename,better);
        }
        else {
            sprintf(command_line,"ffmpeg.exe -v 0 -hide_banner -i %s -vf subtitles=%s -c:s mov_text -f image2pipe -vcodec rawvideo -pix_fmt rgba -",
                    quote_filename,quote_subs_extra);
        }
        print_to_screen_buf(1,command_line,PRINT_FONT_SIZE,COL_BLUE,COL_WHITE,COL_WHITE_T,PRINT_FONT_OUTLINE,TXT_REG);
    } else {
        char add[20]="";
        char sub[1000]="";
        char fn[1000]="";

        sprintf(add,".%s.%s",SUBTITLES,SUBTITLE_FORMAT);
//        sprintf(add,".%s.vtt",SUBTITLES);
        if (quote_filename[1]=='.') {
            replace_str(quote_filename,"..","[doublepoint]");
            sscanf(quote_filename,"%999[^.]",quote_subs);       strcat(quote_subs,add); strcat(quote_subs,"\"");
            replace_str(quote_subs,"[doublepoint]","..");
            sscanf(quote_filename,"\"%999[^.]",sub);
            strcpy(raw_name,sub);
            replace_str(raw_name,"[doublepoint]","..");
            strcat(sub,add);
            replace_str(sub,"[doublepoint]","..");
            replace_str(quote_filename,"[doublepoint]","..");
        } else {
            sscanf(quote_filename,"%999[^.]",quote_subs);       strcat(quote_subs,add); strcat(quote_subs,"\"");
            sscanf(quote_filename,"\"%999[^.]",sub);
            strcpy(raw_name,sub);
            replace_str(raw_name,"[doublepoint]","..");
            strcat(sub,add);
        }
        while (replace_str(sub,"\\","/"));
        sprintf(quote_subs_extra, "\"f='%s'\"",sub);
        sprintf(fn, "%s",sub);

        if (file_exists(fn)) {
            strcpy(lang_nq,SUBTITLES);
            strcat(playing_info_static,"\nSubs=\"");
            strcat(playing_info_static,sub);
            strcat(playing_info_static,"\"");
            if (strlen(FFMPEGCOMMANDIN_SUBS)>0)
                sprintf(command_line,FFMPEGCOMMANDIN_SUBS,quote_filename,quote_subs_extra);
            else
                sprintf(command_line,"ffmpeg.exe -hide_banner -i %s -vf subtitles=%s -c:s mov_text -f image2pipe -vcodec rawvideo -pix_fmt rgba -",
                        quote_filename,quote_subs_extra);
        } else {
            strcpy(lang_nq,"");
            if (strlen(FFMPEGCOMMANDIN)>0)
                sprintf(command_line,FFMPEGCOMMANDIN,quote_filename);
            else
                sprintf(command_line,"ffmpeg.exe -hide_banner -i %s -f image2pipe -vcodec rawvideo -pix_fmt rgba -",quote_filename);
        }
    }

    if (burn_subs && record_screen==1 && (movie_width_prev!=movie_width || movie_height_prev!=movie_height)) {
        printf("Can't continue recording, different size, end recording.\n");
        strcat(playing_info_static,"\nNew recording output file.");
        recording_end();
        record_screen_num=0;
    }

    printf(command_line);
    printf("\n");
//    FILE* file;
    if (file=fopen("../convert/files/convert.log","a")) {
        fprintf(file,"%s\n",command_line);
        fclose(file);
    }
    pipein = popen(command_line, "rb");
    if (pipein!=NULL) {
//        texture_from_ffmpeg.create(movie_width,movie_height);
        if (texture_from_internet.getSize().x!=movie_width || texture_from_internet.getSize().y!=movie_height) {
            texture_from_internet.create(movie_width,movie_height);
            if (smooth==1) texture_from_internet.setSmooth(true);
            else texture_from_internet.setSmooth(false);
        }

//        ffmpegfile=0;
//        internetfile=0;
        if (rec_image_in==NULL) {
            rec_image_in = new sf::Image();
        }
        rec_image_in->create(movie_width,movie_height);
        if (rec_image_in->getSize().x!=movie_width) printf("playing_start: rec_image_in->getSize().x!=movie_width\n");
        if (rec_image_in->getSize().y!=movie_height) printf("playing_start: rec_image_in->getSize().y!=movie_height\n");
        if (texture_from_internet.getSize().x!=movie_width) printf("playing_start: texture_from_internet.getSize().x!=movie_width\n");
        if (texture_from_internet.getSize().y!=movie_height) printf("playing_start: texture_from_internet.getSize().y!=movie_height\n");

/*
        if (movie_sample_rate!=0) {
            sprintf(command_line,"ffmpeg.exe -v 0 -hide_banner -i %s -f s16le -ac %d -ar %d -",
                    quote_filename,movie_channels,movie_sample_rate);
//            sprintf(command_line,"ffmpeg.exe -hide_banner -i %s -f image2pipe -acodec s16le -ac %d -ar %d -",quote_filename,movie_channels,movie_sample_rate);
            printf(command_line);
            printf("\n");
            pipein_audio = popen(command_line, "rb");
            if (pipein_audio!=NULL) {
                return 0;
            } else {
                fflush(pipein);
                pclose(pipein);
                printf("Error opening audio pipe: %s\n",command_line);
                printf("ffmpeg.exe not in path?\n");
                return -1;
            }
        } else {
            return 0;
        }
*/
        return 0;

    }
    printf("Error opening pipe: %s\n",command_line);
    printf("ffmpeg.exe not in path?\n");
    return -1;
}

void Screenget3() {
/*
    if (record_screen==0 && burn_subs==0) {
        thread_playing.wait();
        if (movieextern==0) thread_playing.launch();
    } else {
        thread_playing.wait();
        if (movieextern==0) playing();
    }
*/
    if (isplaying==false) {
        texture_ready=0;
        isplaying_lock.lock();
        isplaying=true;
        isplaying_lock.unlock();
        thread_playing.launch();
    }

    if (texture_ready==1) {
        texture_from_internet.update((sf::Uint8*)frame_in);
//        if (sprite_from_internet.getScale().x<1.0)
//            texture_from_internet.generateMipmap();
        internetfile=0;
        if (!(record_screen==1 && recording_type==1)) {
            texture_ready_lock.lock();
            texture_ready=0;
            texture_ready_lock.unlock();
        } else {
            texture_ready_lock.lock();
            texture_ready=2;
            texture_ready_lock.unlock();
        }
    }
//    playing();
}

void playing()
//void playing(sf::Image * image)
{
//    printf("rec: play, s, ");
    static char filename[1000];

    strcpy(filename,playing_filename);

    size_t num_bytes;
    FILE * pipein_local=pipein;
    FILE * pipein_audio_local=pipein_audio;
    static sf::Clock clock_audio;

    play_clock_tot.restart();
    play_clock_frame.restart();
    num_bytes=movie_width*movie_height*4;
    while (num_bytes==movie_width*movie_height*4 && movieextern==0) {
        playing_screen_num++;
        while (record_pause==1) {
            sf::sleep(sf::microseconds(10));
//            printf("record: playing: sleep: playing_time=%f playing_screen_num=%d\n",playing_time,playing_screen_num);
        }
        num_bytes=fread(frame_in, 1, movie_width*movie_height*4, pipein_local);

        if (movie_r_frame_rate1!=0)
            playing_time=(float)playing_screen_num*((float)movie_r_frame_rate2/(float)movie_r_frame_rate1);

        if (playing_screen_num==0) {
            clock_audio.restart();
            play_clock_tot.restart();
        }

    //    printf("Read %zd bytes, expected %zd\n",num_bytes,(size_t)(movie_width*movie_height*4));
        if (num_bytes!=movie_width*movie_height*4) {
            if (burn_subs && record_screen==1 && (recording_type==1 || end_on_record==1)) {
                file_is_ok=1;
                printf("RECORDING ENDED\n");
                pipein=pipein_local;
                fclose(pipein_local);
                while (texture_ready!=0 && movieextern==0) sf::sleep(sf::microseconds(10));

                recording_end();
                record_screen=0;
    //            fflush(pipein);
                movieextern=1;

                isplaying_lock.lock();
                    isplaying=false;
                isplaying_lock.unlock();

                burn_next_sub_ready_mutex.lock();
                if (burn_subs) burn_next_sub_ready=1;
                burn_next_sub_ready_mutex.unlock();
                return;
            }
    //        fflush(pipein);
            pclose(pipein_local);
    //        fflush(pipein); //?????

            if (select_movie(filename,MOVIEDIR)>0) {
                if (playing_start(filename)==0) {
                    pipein_local=pipein;
                    pipein_audio_local=pipein_audio;
                    num_bytes=fread(frame_in, 1, movie_width*movie_height*4, pipein_local);
//                    strcpy(error_msg2,"EXTERNAL FFMPEG LOADING SUCCESFULL");
//                    error_flag2=1;
//                    Screenget3();
                    if (flop==0) rate_count=play_rate-1;
                    else rate_count=play_rate;
                } else {
//                    strcpy(error_msg2,"FAILED STARTING MOVIE FROM FFMPEG EXTERN");
//                    error_flag2=1;
                    movieextern=1;
                }
            }  else {
                printf("CAN NOT LOAD FILENAME FROM %s/list.txt\n",MOVIEDIR);
//                sprintf(error_msg2,"CAN NOT LOAD FILENAME FROM %s/list.txt",MOVIEDIR);
//                error_flag2=1;
                movieextern=1;
            }
        }
        if (num_bytes==movie_width*movie_height*4) {
            texture_ready_lock.lock();
            texture_ready=1;
            texture_ready_lock.unlock();

            fps_playing_tot=(float)playing_screen_num/play_clock_tot.getElapsedTime().asSeconds();
            fps_playing_frame=(fps_playing_frame*10.0+1.0/play_clock_frame.getElapsedTime().asSeconds())/11.0;
            animate_lock.lock();
            play_clock_frame.restart();
            animate_lock.unlock();


//            if (movie_sample_rate>0) {
/*
            if (movie_sample_rate>0 && movie_sound.getStatus()!=sf::Sound::Playing) {
                int num_bytes_audio=fread(audio_buf, 2, movie_sample_rate*movie_channels, pipein_audio_local);
                movie_buffer.loadFromSamples(audio_buf,movie_sample_rate,movie_channels,movie_sample_rate);
                if (movie_r_frame_rate1!=0) {
                    float fps=(float)movie_r_frame_rate2/(float)movie_r_frame_rate1;
                    if (fps!=0) {
                        float pitch=playing_time/clock_audio.getElapsedTime().asSeconds();
                        movie_sound.setPitch(pitch);
                        printf("pitch=%f\n",pitch);
                    }
                }
                movie_sound.play();
            }
*/

            while (texture_ready!=0 && movieextern==0) {
                    sf::sleep(sf::microseconds(1));
//                printf("record: playing: texture_ready: sleep: playing_time=%f playing_screen_num=%d\n",playing_time,playing_screen_num);
            }
        }
    }
    isplaying_lock.lock();
        isplaying=false;
    isplaying_lock.unlock();

//    printf("e\n");

//    rec_image_in->create(movie_width,movie_height,(sf::Uint8*)frame_in);
//    num_bytes=fread(frame_in, 1, movie_width*movie_height*4, pipein);


//    rec_image_in->create(movie_width,movie_height,(sf::Uint8*)frame_in);
//    if (rec_image_in->getSize().x!=movie_width) printf("playing: rec_image_in->getSize().x!=movie_width\n");
//    if (rec_image_in->getSize().y!=movie_height) printf("playing: rec_image_in->getSize().y!=movie_height\n");


//    texture_from_internet.update(*rec_image_in);
//    if (texture_from_internet.getSize().x!=movie_width) printf("playing: texture_from_internet.getSize().x!=movie_width\n");
//    if (texture_from_internet.getSize().y!=movie_height) printf("playing: texture_from_internet.getSize().y!=movie_height\n");

/*
//    if (movie_sample_rate>0) {
    if (movie_sample_rate>0 && movie_sound.getStatus()!=sf::Sound::Playing) {
//        printf("\n");
//        num_bytes=fread(audio_buf, 2, movie_sample_rate*movie_channels*movie_r_frame_rate2/movie_r_frame_rate1, pipein_audio);
        num_bytes=fread(audio_buf, 2, movie_sample_rate*movie_channels, pipein_audio_local);
//        movie_buffer.loadFromSamples(audio_buf,movie_sample_rate*movie_r_frame_rate2/movie_r_frame_rate1,movie_channels,movie_sample_rate);
        movie_buffer.loadFromSamples(audio_buf,movie_sample_rate,movie_channels,movie_sample_rate);
        movie_sound.play();
    }
*/

//    movie_buffer.loadFromSamples(,,movie_channels,movie_sample_rate);

//bool sf::SoundBuffer::loadFromSamples	(	const Int16 * 	samples,
//Uint64 	sampleCount,
//unsigned int 	channelCount,
//unsigned int 	sampleRate
//)

}

void playing_end()
{
//    rec_texture.create(1,1);
//    delete rec_image;
//    rec_image=NULL;
    thread_playing.wait();
//    thread_playing.terminate();
    if (movie_sample_rate>0) {
//        fflush(pipein_audio);
//        pclose(pipein_audio);
    }
//    fflush(pipein);
  pclose(pipein);
}

int recording_start_m_orig()
{
    int timenow= time(0);
//    float frame_rate=live_movie->getFramerate();
//    if (frame_rate==0.0)
//        frame_rate=30.0;

    reload_init();

    char str_part[2000]="";
    timenow_part=timenow;

    if (burn_subs) {
        sprintf(str_part,"\"../record/%s.%s.PART%d.mp4\"",raw_name,lang_nq,timenow_part);
//        printf("recording_start_m_orig() 1:\n");
        file_is_ok=0;
//        printf("recording_start_m_orig() 2:\n");

        if (strlen(FFMPEGCOMMAND_M_ORIG_AUDIO)>0)
            sprintf(command_line,FFMPEGCOMMAND_M_ORIG_AUDIO,
                    movie_width,movie_height,movie_r_frame_rate1,movie_r_frame_rate2,quote_audio,str_part);
//                    movie_width,movie_height,movie_r_frame_rate1,movie_r_frame_rate2,quote_audio,record_outputfile);
        else
            sprintf(command_line,"ffmpeg.exe -hide_banner -f rawvideo -vcodec rawvideo -pix_fmt rgb24 -s %dx%d -framerate %d/%d -i - -i %s -c copy -map 0:v:0 -map 1:a:0 -strict -2 -c:v libx264 -preset veryfast -crf 23 -c:a copy -pix_fmt yuv420p %s",
                    movie_width,movie_height,movie_r_frame_rate1,movie_r_frame_rate2,quote_audio,record_outputfile,str_part);
//                    movie_width,movie_height,movie_r_frame_rate1,movie_r_frame_rate2,quote_audio,record_outputfile);
            print_to_screen_buf(1,command_line,PRINT_FONT_SIZE,COL_BLUE,COL_WHITE,COL_WHITE_T,PRINT_FONT_OUTLINE,TXT_REG);
//        printf("recording_start_m_orig() 3:\n");
    } else {
        if (strlen(lang_nq)>0)
            sprintf(str_part,"\"%s.%s.PART%d.mp4\"",raw_name,lang_nq,timenow_part);
        else
            sprintf(str_part,"\"%s.PART%d.mp4\"",raw_name,timenow_part);

        if (strlen(FFMPEGCOMMAND_M_ORIG)>0)
            sprintf(command_line,FFMPEGCOMMAND_M_ORIG,
                    movie_width,movie_height,movie_r_frame_rate1,movie_r_frame_rate2,str_part);
        else
            sprintf(command_line,"ffmpeg.exe -hide_banner -f rawvideo -vcodec rawvideo -pix_fmt rgb24 -s %dx%d -framerate %d/%d -i - -an -c:v libx264 %s",
                    movie_width,movie_height,movie_r_frame_rate1,movie_r_frame_rate2,str_part);
        strcpy(quote_audio,"(not yet)");
    }

    if (movie_r_frame_rate2!=0)
        sprintf(recording_info_static,"Resolution=%dx%d - Framerate=%d/%d=%5.3f Fps - Samplerate: %d Hz %d Channels\nFile =%s\nAudio=%s",
                movie_width,movie_height,movie_r_frame_rate1,movie_r_frame_rate2,(float)movie_r_frame_rate1/(float)movie_r_frame_rate2,
                movie_sample_rate,movie_channels,str_part,quote_audio
                );
    else
        sprintf(recording_info_static,"Resolution=%dx%d - Framerate=%d/%d=??? Fps - Samplerate: %d Hz %d Channels\nFile=%s\nAudio=%s",
                movie_width,movie_height,movie_r_frame_rate1,movie_r_frame_rate2,
                movie_sample_rate,movie_channels,str_part,quote_audio
                );
    printf(command_line);
    printf("\n");
    FILE* file;
    if (file=fopen("../convert/files/convert.log","a")) {
        fprintf(file,"%s\n",command_line);
        fclose(file);
    }
    pipeout = popen(command_line, "wb");
    if (pipeout!=NULL) {
//        printf("popen ok!\n");
        return 0;
    }
    else
        printf("popen NULL!\n");
    return -1;
}

void Screenshot3_m_orig()
{
	if (rec_image==NULL)
    {
        rec_image = new sf::Image();
    }

//    *rec_image=texture_from_internet.copyToImage();
//    *rec_image=texture_from_ffmpeg.copyToImage();
//    *rec_image=texture_from_movie_new.copyToImage();

//    if (rec_image->getSize().x!=movie_width) printf("Screenshot3_m_orig: rec_image->getSize().x!=movie_width\n");
//    if (rec_image->getSize().y!=movie_height) printf("Screenshot3_m_orig: rec_image->getSize().y!=movie_height\n");
//    if (texture_from_internet.getSize().x!=movie_width) printf("Screenshot3_m_orig: texture_from_internet.getSize().x!=movie_width\n");
//    if (texture_from_internet.getSize().y!=movie_height) printf("Screenshot3_m_orig: texture_from_internet.getSize().y!=movie_height\n");

//    rec_image_in->create(movie_width,movie_height,(sf::Uint8*)frame_in);

//    printf("Screenshot3_m_orig() 1:\n");

//    if (texture_ready>0)
//        recording_m_orig();


    if (movie_r_frame_rate1!=0)
        recording_time=(float)record_screen_num*((float)movie_r_frame_rate2/(float)movie_r_frame_rate1);

    if (isrecording==false) {
        isrecording_lock.lock();
        isrecording=true;
        isrecording_lock.unlock();
        thread_recording_m_orig.launch();
    }
//    printf("Screenshot3_m_orig() 2:\n");
}



void recording_m_orig()
{
//    int x, y;
//    sf::Uint8* ImageBytes;
//    static const sf::Uint8* ImageBytes;
//    ImageBytes=(sf::Uint8*)image->getPixelsPtr();
//    int width=image->getSize().x;
//    int height=image->getSize().y;
    int width=movie_width;
    int height=movie_height;
    FILE * pipeout_local=pipeout;

//    rec_image_in->create(movie_width,movie_height,(sf::Uint8*)frame_in);
//    if (image->getSize().x!=movie_width) printf("recording_m_orig: rec_image.getSize().x!=movie_width\n");
//    if (image->getSize().y!=movie_height) printf("recording_m_orig: rec_image.getSize().y!=movie_height\n");



    rec_clock_tot.restart();
    rec_clock_frame.restart();

    while (record_screen==1) {
        while (record_pause==1 && record_screen==1) sf::sleep(sf::microseconds(1));
        while (texture_ready==0 && record_screen==1) sf::sleep(sf::microseconds(1));
        if (record_screen==0) continue;

/*
        ptr=frame_in;
        for (int p=height*width; p!=0; p--) {

                fwrite(ptr, 1, 3, pipeout_local);
                ptr+=4;
        }
*/
        register unsigned char * ptr=frame_in;
        register unsigned char * frm=frame;
        for (register int p=height*width; p!=0; p--) {
                *frm++=*ptr++;
                *frm++=*ptr++;
                *frm++=*ptr++;
                ptr++;
        }
        fwrite(frame, 1, height*width*3, pipeout_local);
//        fwrite(frm, 1, height*width*3, pipeout_local);

        record_screen_num++;
        while (texture_ready!=2 && record_screen==1) sf::sleep(sf::microseconds(1));
        texture_ready_lock.lock();
        texture_ready=0;
        texture_ready_lock.unlock();

        fps_record_tot=(float)record_screen_num/rec_clock_tot.getElapsedTime().asSeconds();
        fps_record_frame=(fps_record_frame*10.0+1.0/rec_clock_frame.getElapsedTime().asSeconds())/11.0;
        rec_clock_frame.restart();
    }
    isrecording_lock.lock();
    isrecording=false;
    isrecording_lock.unlock();
    texture_ready_lock.lock();
    texture_ready=0;
    texture_ready_lock.unlock();
}


int timenow;

int recording_start(int x, int y)
{

    rec_clock_tot.restart();
    rec_clock_frame.restart();

    timenow= time(0);

//    reload_init();

//FFMPEG_M_CROP="ffmpeg -hide_banner -f rawvideo -vcodec rawvideo -pix_fmt rgb24 -s 1920x1080 -r 60 -i - -filter:v "crop=%d:1080:%d:0" -an -c:v libx264 -preset slow -crf 23 -c:a copy -pix_fmt yuv420p ../record/output%d.mp4"
    if (crop==0) {
        if (RGBA) {
            if (strlen(FFMPEGCOMMAND_RGBA)>0)
                sprintf(command_line,FFMPEGCOMMAND_RGBA,x,y,timenow);
            else
                sprintf(command_line,"ffmpeg.exe -hide_banner -f rawvideo -vcodec rawvideo -pix_fmt rgba -s %dx%d -r 60 -i - -an -c:v libx264 -pix_fmt yuv444p -preset veryfast -crf 23 ../record/output%d_rgba.mp4",x,y,timenow);
        } else {
            if (strlen(FFMPEGCOMMAND)>0)
                sprintf(command_line,FFMPEGCOMMAND,x,y,timenow);
            else
                sprintf(command_line,"ffmpeg.exe -hide_banner -f rawvideo -vcodec rawvideo -pix_fmt rgb24 -s %dx%d -r 60 -i - -an -c:v libx264 -pix_fmt yuv420p -preset veryfast -crf 23 ../record/output%d.mp4",x,y,timenow);
        }
    } else {
        sf::FloatRect fr=sprite_from_crop.getGlobalBounds();

        sprite_texture_final.setTexture(texture_final.getTexture(),false);
        sprite_texture_final.setTextureRect({fr.left,fr.top,fr.width,fr.height});
        texture_final_part.create(fr.width,fr.height,false);
        texture_final_part.setSmooth(true);
        texture_final_part.clear(sf::Color(0,0,0,0));
        if (rec_image_part==NULL) {
            rec_image_part = new sf::Image();
        }
//sf::RenderTexture texture_final_part;
//sf::Sprite sprite_texture_final;

/*
        int scale_x=texture_from_ffmpeg.getSize().x*sprite_from_ffmpeg.getScale().x;
        int scale_y=texture_from_ffmpeg.getSize().y*sprite_from_ffmpeg.getScale().y;
        if (scale_x>1920) scale_x=1920;
        if (scale_y>1080) scale_y=1080;
        if (float(scale_x)/2.0!=int(scale_x/2.0)) scale_x-=1;
        if (float(scale_y)/2.0!=int(scale_y/2.0)) scale_y-=1;
*/

        if (RGBA) {
            if (strlen(FFMPEGCOMMAND_CROP_RGBA)>0)
//                sprintf(command_line,FFMPEGCOMMAND_CROP_RGBA,scale_x,scale_y,int((1920-scale_x)/2),int((1080-scale_y)/2),timenow);
                sprintf(command_line,FFMPEGCOMMAND_CROP_RGBA, int(fr.width),int(fr.height),timenow);
//                    int(fr.width),int(fr.height),int(fr.left),int(fr.top),timenow);
//-filter_complex "scale=300:-"
//                sprintf(command_line,"ffmpeg -hide_banner -f rawvideo -vcodec rawvideo -pix_fmt rgba -s %dx%d -r 60 -i - -an -filter_complex \"scale=300:-1\" -c:v png ../record/output%d_rgba.avi",
//                sprintf(command_line,"ffmpeg -hide_banner -f rawvideo -vcodec rawvideo -pix_fmt rgba -s %dx%d -r 60 -i - -an -c:v png ../record/output%d_rgba.avi",
//                   int(fr.width),int(fr.height),timenow);

            else
                sprintf(command_line,"ffmpeg -hide_banner -f rawvideo -vcodec rawvideo -pix_fmt rgba -s %dx%d -r 60 -i - -an -c:v png ../record/output%d_rgba.avi",
                   int(fr.width),int(fr.height),timenow);
//                sprintf(command_line,"ffmpeg -hide_banner -f rawvideo -vcodec rawvideo -pix_fmt rgba -s 1920x1080 -r 60 -i - -filter:v crop=%d:%d:%d:%d -an -c:v png ../record/output%d_rgba.avi",
//                   int(fr.width),int(fr.height),int(fr.left),int(fr.top),timenow);
        } else {
            if (strlen(FFMPEGCOMMAND_CROP)>0)
                sprintf(command_line,FFMPEGCOMMAND_CROP,
//                    int(fr.width),int(fr.height),int(fr.left),int(fr.top),timenow);
                    int(fr.width),int(fr.height),timenow);
            else
                sprintf(command_line,"ffmpeg -hide_banner -f rawvideo -vcodec rawvideo -pix_fmt rgb24 -s %dx%d -r 60 -i - -filter:v crop=%d:%d:%d:%d -an -c:v libx264 -preset slow -crf 23 -pix_fmt yuv420p ../record/output%d.mp4",
                        int(fr.width),int(fr.height),timenow);
//                sprintf(command_line,"ffmpeg -hide_banner -f rawvideo -vcodec rawvideo -pix_fmt rgb24 -s 1920x1080 -r 60 -i - -filter:v crop=%d:%d:%d:%d -an -c:v libx264 -preset slow -crf 23 -pix_fmt yuv420p ../record/output%d.mp4",
//                        int(fr.width),int(fr.height),int(fr.left),int(fr.top),timenow);
        }
    }

    printf(command_line);
    printf("\n");
    FILE* file;
    if (file=fopen("../convert/files/convert.log","a")) {
        fprintf(file,"%s\n",command_line);
        fclose(file);
    }
    pipeout = popen(command_line, "wb");
    if (pipeout!=NULL)
        return 0;
    else
        return -1;
}

void Screenshot3_window(sf::RenderWindow& window) {
	static sf::Vector2u windowSize = window.getSize();
	if (rec_image==NULL) {
        rec_texture.create(windowSize.x, windowSize.y);
        rec_image = new sf::Image();
	}
	rec_texture.update(window);
	*rec_image=rec_texture.copyToImage();

    recording();
    recording_time=(float)record_screen_num/60.0;
}

void recording_part();

void Screenshot3() {
	static sf::Vector2u windowSize = texture_final.getSize();
//	static sf::Sprite testimage;
	if (rec_image==NULL) {
        rec_texture.create(windowSize.x, windowSize.y);
        rec_image = new sf::Image();
	}
	if (crop) {
        texture_final_part.draw(sprite_texture_final);
        texture_final_part.display();
        *rec_image_part=texture_final_part.getTexture().copyToImage();
        texture_final_part.clear(sf::Color(0,0,0,0));
        recording_part();
	} else {
        *rec_image=texture_final.getTexture().copyToImage();
        recording();
	}
    recording_time=(float)record_screen_num/60.0;
//	rec_texture.update(texture_final.getTexture());
//	*rec_image=rec_texture.copyToImage();
}

void Screenshot3_sfmlview1() {
	static sf::Vector2u windowSize = SFMLView1.getSize();
//	static sf::Sprite testimage;
	if (rec_image==NULL) {
        rec_texture.create(windowSize.x, windowSize.y);
        rec_image = new sf::Image();
	}
	rec_texture.update(SFMLView1);
	*rec_image=rec_texture.copyToImage();

    recording();
    recording_time=(float)record_screen_num/60.0;
}

void recording_part()
{
//    sf::Color Color;
    static const sf::Uint8* ImageBytes;

    ImageBytes=rec_image_part->getPixelsPtr();
    int x=rec_image_part->getSize().x, y=rec_image_part->getSize().y;
//    sf::Clock clock_timer;
//    clock_timer.restart();
//    INT64 the_time;
    register int pos_in=0;
    register int pos_out=0;
    register int total_pixels=x*y;
    register int byte_counter;
    if (RGBA) {
        for (byte_counter=0 ; byte_counter++<total_pixels;) {
                frame[pos_out++] = (char) ImageBytes[pos_in++];
                frame[pos_out++] = (char) ImageBytes[pos_in++];
                frame[pos_out++] = (char) ImageBytes[pos_in++];
                frame[pos_out++] = (char) ImageBytes[pos_in++];
        }
        fwrite(frame, 1, x*y*4, pipeout);
    } else {
        for (byte_counter=0 ; byte_counter++<total_pixels;) {
                frame[pos_out++] = (char) ImageBytes[pos_in++];
                frame[pos_out++] = (char) ImageBytes[pos_in++];
                frame[pos_out++] = (char) ImageBytes[pos_in++];
                pos_in++;
        }
        fwrite(frame, 1, x*y*3, pipeout);
    }
    fflush(pipeout);

//    the_time=clock_timer.getElapsedTime().asMicroseconds();
//    printf("Elapsed time write frame to ffmpeg: %zd microseconds\n",the_time);
}

void recording()
{
//    sf::Color Color;
    static const sf::Uint8* ImageBytes;

    ImageBytes=rec_image->getPixelsPtr();
    int x=rec_image->getSize().x, y=rec_image->getSize().y;
//    sf::Clock clock_timer;
//    clock_timer.restart();
//    INT64 the_time;
    register int pos_in=0;
    register int pos_out=0;
    register int total_pixels=x*y;
    register int byte_counter;
    if (RGBA) {
        for (byte_counter=0 ; byte_counter++<total_pixels;) {
                frame[pos_out++] = (char) ImageBytes[pos_in++];
                frame[pos_out++] = (char) ImageBytes[pos_in++];
                frame[pos_out++] = (char) ImageBytes[pos_in++];
                frame[pos_out++] = (char) ImageBytes[pos_in++];
        }
        fwrite(frame, 1, x*y*4, pipeout);
    } else {
        for (byte_counter=0 ; byte_counter++<total_pixels;) {
                frame[pos_out++] = (char) ImageBytes[pos_in++];
                frame[pos_out++] = (char) ImageBytes[pos_in++];
                frame[pos_out++] = (char) ImageBytes[pos_in++];
                pos_in++;
        }
        fwrite(frame, 1, x*y*3, pipeout);
    }
    fflush(pipeout);

//    the_time=clock_timer.getElapsedTime().asMicroseconds();
//    printf("Elapsed time write frame to ffmpeg: %zd microseconds\n",the_time);
}




void recording___()
{
    const sf::Uint8* ImageBytes=rec_image->getPixelsPtr();
//    int x, y;
//    register int pos_in=0;
//    register int pos_out=0;
    int total_bytes=1920*1080;
//    register int byte_counter;
    unsigned char * ptr;
    ptr=(unsigned char *) ImageBytes;
    unsigned char * frm=frame;
    for (register int p=total_bytes; p!=0; p--) {
            *frm++=*ptr++;
            *frm++=*ptr++;
            *frm++=*ptr++;
            ptr++;
//            frame[pos_out]=ptr[pos_out]; pos_out++;
//            fwrite(ptr, 1, 3, pipeout);
//            ptr+=4;

    }
    fwrite(frame, 1, 1920*1080*3, pipeout);
/*
    for (byte_counter=0 ; byte_counter++<total_bytes;)
//    for (y=0 ; y<1080 ; y++) {
//        for (x=0 ; x<1920 ; x++)
        {
            frame[pos_out++] = (char) ImageBytes[pos_in++];
            frame[pos_out++] = (char) ImageBytes[pos_in++];
            frame[pos_out++] = (char) ImageBytes[pos_in++];
            pos_in++;
//            frame[(y*1920+x)*3+0] = (char) ImageBytes[(y*1920+x)*4+0];
//            frame[(y*1920+x)*3+1] = (char) ImageBytes[(y*1920+x)*4+1];
//            frame[(y*1920+x)*3+2] = (char) ImageBytes[(y*1920+x)*4+2];
        }
//    }
    fwrite(frame, 1, 1920*1080*3, pipeout);
//    fflush(pipeout);
*/

    fps_record_tot=(float)record_screen_num/rec_clock_tot.getElapsedTime().asSeconds();
    fps_record_frame=(fps_record_frame*10.0+1.0/rec_clock_frame.getElapsedTime().asSeconds())/11.0;
    animate_lock.lock();
    rec_clock_frame.restart();
    animate_lock.unlock();

//    the_time=clock_timer.getElapsedTime().asMicroseconds();
//    printf("Elapsed time write frame to ffmpeg: %zd microseconds\n",the_time);
}

void recording_end()
{
//    rec_texture.create(1,1);
//    delete rec_image;
//    rec_image=NULL;
    char drawtext[1000]="";
//    strcat(drawtext,"FLUSHING RECORD PIPE...");
//    strcpy(error_msg2,"FLUSHING RECORD PIPE..."); error_flag2=1;
    if (burn_subs)
        print_to_screen_buf(1,drawtext,PRINT_FONT_SIZE,COL_BLUE,COL_WHITE,COL_WHITE_T,PRINT_FONT_OUTLINE,TXT_REG);
//    draw2(drawtext,770,400,sf::Color::Red,sf::Color::White);
//    SFMLView1.display();
    fflush(pipeout);
//    sf::sleep(sf::milliseconds(1000));
    pclose(pipeout);
    if (burn_subs) {
        if (file_is_ok) {
            textfiles.lock();
            if (FILE * file=fopen("../convert/files/converted.txt","a")) {
                fprintf(file,"VIDEO=%s AUDIO=%s SUBS=%s LANG=\"%s\" TIME=\"%s\"\n",quote_video,quote_audio,quote_subs,lang_nq,source_time);
                fclose(file);
            } else {
                printf("CAN NOT WRITE TO FILE ../convert/files/converted.txt\n");
            }
            textfiles.unlock();

            strcat(drawtext,"\nFILE OK, RENAMING...");
//            draw2(drawtext,770,400,sf::Color::Red,sf::Color::White);
//            SFMLView1.display();
            print_to_screen_buf(1,"FILE OK, RENAMING...",24,COL_CYAN,COL_WHITE,COL_WHITE_T,PRINT_FONT_OUTLINE,TXT_REG);

            char str_part[2000]="";
            char str_from[2000]="";
            char str_to[2000]="";

            sprintf(str_from,"../record/%s.%s.PART%d.mp4",raw_name,lang_nq,timenow_part);
            strcpy(str_to,record_outputfile_nq);

            if (!file_exists(str_from)) {
                sprintf(drawtext,"Can not find outputfile: %s",str_from);
                printf("%s\n",drawtext);
                print_to_screen_buf(1,drawtext,24,COL_RED,COL_WHITE,COL_WHITE_T,PRINT_FONT_OUTLINE,TXT_REG);
            }

            rename(str_from,str_to);

            if (!file_exists(str_to)) {
//             	while (replace_str(str_from,"/","\\"));
//             	while (replace_str(str_to,"/","\\"));
                sprintf(str_part,"move \"%s\" \"%s\"",str_from,str_to);
                system(str_part);
            }

            if (!file_exists(str_to)) {
//             	while (replace_str(str_from,"/","\\"));
//             	while (replace_str(str_to,"/","\\"));
                sprintf(str_part,"rename \"%s\" \"%s\"",str_from,str_to);
                system(str_part);
            }


            if (!file_exists(str_to)) {
             	while (replace_str(str_from,"/","\\"));
             	while (replace_str(str_to,"/","\\"));
                sprintf(str_part,"move \"%s\" \"%s\"",str_from,str_to);
                system(str_part);
            }

            if (!file_exists(str_to)) {
                sprintf(str_part,"rename \"%s\" \"%s\"",str_from,str_to);
                system(str_part);
            }

            if (!file_exists(str_to)) {
                rename(str_from,str_to);
            }


            if (!file_exists(str_to)) {
                sprintf(drawtext,"ERROR RENAMING FILE...");
                error_flag2=1;
                printf("%s\n",drawtext);
                print_to_screen_buf(1,drawtext,24,COL_RED,COL_WHITE,COL_WHITE_T,PRINT_FONT_OUTLINE,TXT_REG);

                sprintf(drawtext,"FROM: %s",str_from);
                printf("%s\n",drawtext);
                print_to_screen_buf(1,drawtext,24,COL_RED,COL_WHITE,COL_WHITE_T,PRINT_FONT_OUTLINE,TXT_REG);
                sprintf(drawtext,"TO:   %s",str_to);
                printf("%s\n",drawtext);
                print_to_screen_buf(1,drawtext,24,COL_RED,COL_WHITE,COL_WHITE_T,PRINT_FONT_OUTLINE,TXT_REG);
                sprintf(drawtext,"ERROR RENAMING FILE...");

                strcat(drawtext,"\nERROR RENAMING FILE...");
//                draw2(drawtext,770,400,sf::Color::Red,sf::Color::White);
//                SFMLView1.display();
//                sf::sleep(sf::milliseconds(1500));
//                draw2(drawtext,770,400,sf::Color::Red,sf::Color::White);
//                SFMLView1.display();
//                sf::sleep(sf::milliseconds(1500));
//                draw2(drawtext,770,400,sf::Color::Red,sf::Color::White);
//                SFMLView1.display();
//                sf::sleep(sf::milliseconds(1500));
            } else {
                sprintf(drawtext,"OK...");
                error_flag2=1;
                printf("%s\n",drawtext);
                print_to_screen_buf(1,drawtext,24,COL_CYAN,COL_WHITE,COL_WHITE_T,PRINT_FONT_OUTLINE,TXT_REG);
                strcat(drawtext,"\nOK...");
//                draw2(drawtext,770,400,sf::Color::Red,sf::Color::White);
//                SFMLView1.display();
                sf::sleep(sf::milliseconds(1000));

            }
            sprintf(drawtext,"MOVING FILES FROM ../CONVERT/FILES/ TO ../CONVERT/CONVERTED/ ...");
            error_flag2=1;
            printf("%s\n",drawtext);
            print_to_screen_buf(1,drawtext,24,COL_CYAN,COL_WHITE,COL_WHITE_T,PRINT_FONT_OUTLINE,TXT_REG);
            strcat(drawtext,"\nMOVING FILES FROM ../CONVERT/FILES/ TO ../CONVERT/CONVERTED/ ...");
//            draw2(drawtext,770,400,sf::Color::Red,sf::Color::White);
//            SFMLView1.display();

            sprintf(str_part,"move \"..\\convert\\files\\%s*.*\" ..\\convert\\converted\\",raw_name);
            FILE * pfile;
            if (pfile=popen(str_part,"r") ) {
                char line[1000]="";
                while (fgets(line,1000,pfile)) {
                    printf("%s",line);
                    print_to_screen_buf(1,line,24,COL_CYAN,COL_WHITE,COL_WHITE_T,PRINT_FONT_OUTLINE,TXT_REG);
                }
                pclose(pfile);

            } else {
                sprintf(drawtext,"Error opening pipe for move.");
                error_flag2=1;
                printf("%s\n",drawtext);
                print_to_screen_buf(1,drawtext,24,COL_RED,COL_WHITE,COL_WHITE_T,PRINT_FONT_OUTLINE,TXT_REG);
                strcat(drawtext,"\nError opening pipe for move.");
//                draw2(drawtext,770,400,sf::Color::Red,sf::Color::White);
//                SFMLView1.display();
            }
//            system(str_part);

//            draw2("DONE...",770,400+24*4,sf::Color::Red,sf::Color::White);
            print_to_screen_buf(1,"DONE....",PRINT_FONT_SIZE,COL_BLUE,COL_WHITE,COL_WHITE_T,PRINT_FONT_OUTLINE,TXT_REG);
//            SFMLView1.display();

//            sf::sleep(sf::milliseconds(1500));

        } else {
            sprintf(drawtext,"FILE NOT OK, SKIP RENAME, DELETE IF NOT NEEDED...");
            error_flag2=1;
            printf("%s\n",drawtext);
            print_to_screen_buf(1,drawtext,24,COL_RED,COL_WHITE,COL_WHITE_T,PRINT_FONT_OUTLINE,TXT_REG);
//            draw2("FILE NOT OK, SKIP RENAME, DELETE IF NOT NEEDED...",770,400+24,sf::Color::Red,sf::Color::White);
//            SFMLView1.display();
//            sf::sleep(sf::milliseconds(500));
//            draw2("FILE NOT OK, SKIP RENAME, DELETE IF NOT NEEDED...",770,400+24,sf::Color::Yellow,sf::Color::White);
//            SFMLView1.display();
//            sf::sleep(sf::milliseconds(500));
//            draw2("FILE NOT OK, SKIP RENAME, DELETE IF NOT NEEDED...",770,400+24,sf::Color::Red,sf::Color::White);
//            SFMLView1.display();
//            sf::sleep(sf::milliseconds(2000));
        }
    }
}


void Screenshot_old()
{
    sf::Vector2u windowSize = SFMLView1.getSize();
    sf::Texture texture;
    texture.create(windowSize.x, windowSize.y);
    texture.update(SFMLView1);
    texture.copyToImage().saveToFile("Screenshot.png");

    blending=0;

    if (file_exists("Screenshot.png"))
    {
        if (texture_from_ffmpeg.loadFromFile("Screenshot.png"))
        {
            texture_from_ffmpeg.generateMipmap();
            ffmpegfile=0;
            pen=1;
            pen_mode=2;
        }
        else
        {
            savedata((char*)"failed loading Screenshot.png",0);
            ffmpegfile=1;
        }
    }
    if (ffmpegfile==0)
    {
        size_ffmpeg=0;
        rotate_ffmpeg=0;
        sprite_from_ffmpeg.setScale(1.0,1.0);
        rotation_ffmpeg=0.0;
        rot_speed_ffmpeg=1.0;
        sprite_from_ffmpeg.setTexture(texture_from_ffmpeg,false);
        setffmpegfile();
        sprite_from_ffmpeg.setTextureRect( { 0,0,(int)texture_from_ffmpeg.getSize().x, (int)texture_from_ffmpeg.getSize().y } );
        extern int smooth;
        if (smooth==1) texture_from_ffmpeg.setSmooth(TRUE);
        else texture_from_ffmpeg.setSmooth(TRUE);
        texture_from_ffmpeg.setRepeated(TRUE);
    }
    else
    {
        savedata((char*)"mislukt",0);
        sprintf(writer,"invalid texture %s\n size x=%d, size y=%d","Screenshot.png",(int)texture_from_ffmpeg.getSize().x, (int)texture_from_ffmpeg.getSize().y );
        MessageBox(NULL, writer,"NOT LOADED", MB_ICONEXCLAMATION | MB_OK);
    }
    shift=0;
    rotation_ffmpeg=0.0;
    rot_speed_ffmpeg=0.0;
    rotate_ffmpeg=0;
}

void Screenshot()
{
    sf::Vector2u windowSize = SFMLView1.getSize();
    texture_from_ffmpeg.create(windowSize.x, windowSize.y);
    texture_from_ffmpeg.update(SFMLView1);
    sprite_from_ffmpeg.setTextureRect( { 0,0,(int)texture_from_ffmpeg.getSize().x, (int)texture_from_ffmpeg.getSize().y } );
    setffmpegfile();
    ffmpegfile=0;
}





//
// combine.c - Join multiple MP4 videos and PNG images into one video
// Written by Ted Burke - last updated 12-2-2017
//
// To compile:
//
//    gcc combine.c
//


/*
// Video resolution
#define W 1280
#define H 720

// Allocate a buffer to store one frame_demo
unsigned char frame_demo[H][W][3] = {0};

void demo_main()
{
    int count, n;
    FILE *pipein;
    FILE *pipeout;

    // Open output pipe
    pipeout = popen("ffmpeg -y -f rawvideo -vcodec rawvideo -pix_fmt rgb24 -s 1280x720 -r 25 -i - -f mp4 -q:v 5 -an -vcodec mpeg4 combined.mp4", "w");

    // Write first 50 frame_demos using original video title image from title_original.png
    pipein = popen("ffmpeg -i title_original.png -f image2pipe -vcodec rawvideo -pix_fmt rgb24 -", "r");
    count = fread(frame_demo, 1, H*W*3, pipein);
    for (n=0 ; n<50 ; ++n)
    {
        fwrite(frame_demo, 1, H*W*3, pipeout);
        fflush(pipeout);
    }
    fflush(pipein);
    pclose(pipein);

    // Copy all frame_demos from teapot.mp4 to output pipe
    pipein = popen("ffmpeg -i teapot.mp4 -f image2pipe -vcodec rawvideo -pix_fmt rgb24 -", "r");
    while(1)
    {
        count = fread(frame_demo, 1, H*W*3, pipein);
        if (count != H*W*3) break;
        fwrite(frame_demo, 1, H*W*3, pipeout);
        fflush(pipeout);
    }
    fflush(pipein);
    pclose(pipein);

    // Write next 50 frame_demos using modified video title image from title_modified.png
    pipein = popen("ffmpeg -i title_modified.png -f image2pipe -vcodec rawvideo -pix_fmt rgb24 -", "r");
    count = fread(frame_demo, 1, H*W*3, pipein);
    for (n=0 ; n<50 ; ++n)
    {
        fwrite(frame_demo, 1, H*W*3, pipeout);
        fflush(pipeout);
    }
    fflush(pipein);
    pclose(pipein);

    // Copy all frame_demos from output.mp4 to output pipe
    pipein = popen("ffmpeg -i output.mp4 -f image2pipe -vcodec rawvideo -pix_fmt rgb24 -", "r");
    while(1)
    {
        count = fread(frame_demo, 1, H*W*3, pipein);
        if (count != H*W*3) break;
        fwrite(frame_demo, 1, H*W*3, pipeout);
        fflush(pipeout);
    }
    fflush(pipein);
    pclose(pipein);

    // Flush and close output pipe
    fflush(pipeout);
    pclose(pipeout);
}
*/

char * get_info_video(char * filename) {
    char command_line[2000];
    FILE *pipein;
    int movie_width=0;
    int movie_height=0;
    int movie_r_frame_rate1=0;
    int movie_r_frame_rate2=0;
    static char return_info[1000]="";
    strcpy(return_info,"(No Info)");
    char quote_filename[1000];
    sprintf(quote_filename,"\"%s\"",filename);

    sprintf(command_line,"ffprobe.exe -v error -select_streams v:0 -show_entries stream=width,height,r_frame_rate,bit_rate -of default=nw=1 %s",quote_filename);
    FILE* file;
    if (file=fopen("../convert/files/convert.log","a")) {
        fprintf(file,"%s\n",command_line);
        fclose(file);
    }
    pipein = popen(command_line, "rb");
    if (pipein!=NULL) {
        char line1[100];
        char line2[100];
        char line3[100];
        char line4[100];
        fgets(line1,100,pipein);
        fgets(line2,100,pipein);
        fgets(line3,100,pipein);
        fgets(line4,100,pipein);
        pclose(pipein);
        sscanf(line4,"bit_rate=%d",&movie_bit_rate);
        if (strcmp(FFMPEGCOMMANDIN_SUBS_RES,"HD")==0) {
            printf("RECORDING IN HD\n");
            movie_width=1920;
            movie_height=1080;
        } else {
            printf("FUCK: %s\n",FFMPEGCOMMANDIN_SUBS_RES);
            sscanf(line1,"width=%d",&movie_width);
            sscanf(line2,"height=%d",&movie_height);
        }

        sscanf(line3,"r_frame_rate=%d/%d",&movie_r_frame_rate1,&movie_r_frame_rate2);
//        printf("width=%d\n",movie_width);
//        printf("height=%d\n",movie_height);
//        printf("r_frame_rate=%d/%d\n",movie_r_frame_rate1,movie_r_frame_rate2);
        if (movie_r_frame_rate2!=0)
            sprintf(return_info,"(%dx%d - %d/%d=%5.3f Fps Bitrate=%d)",
                    movie_width,movie_height,movie_r_frame_rate1,movie_r_frame_rate2,(float)movie_r_frame_rate1/(float)movie_r_frame_rate2,movie_bit_rate);
        else
            sprintf(return_info,"(%dx%d - %d/%d=??? Bitrate=%d)",
                    movie_width,movie_height,movie_r_frame_rate1,movie_r_frame_rate2,movie_bit_rate);
    } else {
        printf("Error: %s\n",command_line);
        printf("ffprobe.exe not in path?\n",command_line);
        printf(command_line);
        printf("\n");
        sprintf(return_info,"(No Info: ffprobe.exe not in path?)");
        return return_info;
    }
    return return_info;
}

char * get_info_audio(char * filename) {
    char command_line[2000];
    FILE *pipein;
    int movie_sample_rate;
    int movie_channels;
    static char return_info[1000]="";
    strcpy(return_info,"(No Info)");
    char quote_filename[1000];
    sprintf(quote_filename,"\"%s\"",filename);

    sprintf(command_line,"ffprobe.exe -v error -select_streams a:0 -show_entries stream=sample_rate,channels -of default=nw=1 %s",quote_filename);
    FILE* file;
    if (file=fopen("../convert/files/convert.log","a")) {
        fprintf(file,"%s\n",command_line);
        fclose(file);
    }
    pipein = popen(command_line, "rb");
    if (pipein!=NULL) {
        char line1[100];
        char line2[100];
        if (fgets(line1,100,pipein)!=0) {
            fgets(line2,100,pipein);
            pclose(pipein);
            sscanf(line1,"sample_rate=%d",&movie_sample_rate);
            sscanf(line2,"channels=%d",&movie_channels);
//            printf("sample_rate=%d\n",movie_sample_rate);
//            printf("channels=%d\n",movie_channels);
//            movie_sound.setBuffer(movie_buffer);
            sprintf(return_info,"(%d Hz - %d Channels)",movie_sample_rate,movie_channels);
        } else {
            pclose(pipein);
            movie_sample_rate=0;
            movie_channels=0;
            printf("No audio detected\n");
            sprintf(return_info,"(No audio detected)");
        }
    } else {
        printf("Error: %s\n",command_line);
        printf("ffprobe.exe not in path?\n",command_line);
        printf(command_line);
        printf("\n");
        sprintf(return_info,"(No Info: ffprobe.exe not in path?)");
        return return_info;
    }

    return return_info;
}

