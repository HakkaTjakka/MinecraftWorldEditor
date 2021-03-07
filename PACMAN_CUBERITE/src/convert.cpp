#include "everything.hpp"

#define PRINT_FONT_SIZE 24
#define PRINT_FONT_OUTLINE 2

char quote_subs_extra2[5000];
int get_video_thread_running=0;
int burn_next_sub_thread_running=0;
sf::Mutex textfiles;
struct container_struct container_audio;
struct container_struct container_video;
void disp_close2();
extern sf::Mutex burn_next_sub_ready_mutex;
void get_videos();
void burn_next_sub();
void dos_command();

sf::Thread get_videos_thread(&get_videos);
sf::Thread burn_next_sub_thread(&burn_next_sub);
sf::Thread dos_command_thread(&dos_command);

char record_outputfile[1000]="";
char record_outputfile_nq[1000]="";

void print_to_screen_buf(int var_font, char * text_to_print, int font_size, sf::Color paint_in, sf::Color paint_out, sf::Color paint_back, float outline, sf::Uint32 text_type );

void get_videos() {
    int line_count=0;
    int ret=1;
    char link[1000]="";
    char filename[1000]="";;
    char line[1000]="";
    while (line_count<ret) {
        if (ESCAPE_PRESSED) {
            ESCAPE_PRESSED=0;
            printf("ABORTING\n");
            get_video_thread_running=0;
            return;
        }
        line_count++;
        ret=select_from_list2(link,"../convert/list.txt",line_count);
        if (ret==0) {
            printf("../convert/list.txt EMPTY?\n");
            get_video_thread_running=0;
            return;
        } else {
//            wprintf(L"\x1b[30;100m");
            printf("GETTING INFO: %d/%d : %s\n",line_count,ret,link);
//            wprintf(L"\x1b[0m");
            char com[1000];
            sprintf(com,"youtube-dl -i --skip-unavailable-fragments --geo-bypass --get-id --get-format --get-filename --get-duration \"%s\"",link);
            if (ESCAPE_PRESSED) {
                ESCAPE_PRESSED=0;
                printf("ABORTING\n");
                get_video_thread_running=0;
                return;
            }
//            sprintf(com,"youtube-dl -i --get-id --get-format --get-filename \"%s\" > video.info",link);
//            pipein = popen(com, "r");
//            system(com);
//            monitor_off=1;
            FILE * file;
            FILE * pfile;
            if (pfile=popen(com,"r") ) {
//            if (file=fopen("video.info","r") ) {
                if (ESCAPE_PRESSED) {
                    ESCAPE_PRESSED=0;
                    printf("ABORTING, WAITING FOR YOUTUBE-DL TO END\n");
                    while (fgets(line,1000,pfile)) printf("Waiting for youtube-dl -> %s",line);
                    printf("youtube-dl FINISHED\n");
                    pclose(pfile);
                    get_video_thread_running=0;
                    return;
                }
                char str_time[50]="";
                char idname[50]="";
                char videoname[1000]="";
                int videonum=0;
                char audioname[1000]="";
                char subsname[1000]="";
                char subsname_en[1000]="";
                int audionum=0;
                char line[1000];
                char dummy[1000];
                int file_count=0;
                while (fgets(line,1000,pfile)) {
                    file_count++;
                    if (file_count>1) {
//                        wprintf(L"\x1b[30;107m");
                        printf("GETTING MORE INFO (YOUTUBELIST#%d): %d/%d : %s\n",file_count,line_count,ret,link);
//                        wprintf(L"\x1b[0m");
                    }
                    printf("youtube-dl -> %s",line);

                    sscanf(line, "%50[^\n]", idname);
                    if (fgets(line,1000,pfile)) {
                        printf("youtube-dl -> %s",line);
                        strcpy(filename,line);
//                        printf("line(1)=%s\n",line);
//                        printf("filename=%s\n",filename);
                        while (strlen(filename)>=1 && filename[strlen(filename)-1]!='.') {
                            filename[strlen(filename)-1]='\0';
//                            printf("filename(2)=%s\n",filename);
                        }
                        if (strlen(filename)>=1) filename[strlen(filename)-1]='\0';
//                        sscanf(line, "%1000[^.]", filename);
//                        printf("line(2)=%s\n",line);
//                        printf("filename(3)=%s\n",filename);
                    } else {
                        printf("ERROR READING LINE 2 INFO FROM VIDEO.INFO FROM %s FAILED\n",link);
                        break;
                    }
                    if (fgets(line,1000,pfile)) {
                        printf("youtube-dl -> %s",line);
                        sscanf(line, "%50[^\n]", str_time);
                    } else {
                        printf("ERROR READING LINE 3 INFO FROM VIDEO.INFO FROM %s FAILED\n",link);
                        break;
                    }
                    if (fgets(line,1000,pfile)) {
                        printf("youtube-dl -> %s",line);
                        sscanf(line, "%s %100[^+]+%s", videoname,dummy,audioname);
                        printf("VIDEO=%s,AUDIO=%s,dummy=%s\n",videoname,audioname,dummy);
                    } else {
                        printf("ERROR READING LINE 4 INFO FROM PIPE YOUTUBE-DL FROM %s FAILED\n",link);
                        break;
                    }

                    videonum=atoi(videoname);
                    audionum=atoi(audioname);
                    get_container(&container_video,videonum);
                    get_container(&container_audio,audionum);
                    printf("VIDEO: %d isvideo=%d isaudio=%d extension=%s\n",videonum,container_video.isvideo,container_video.isaudio,container_video.extension);
                    if (audionum>0) {
                        printf("AUDIO: %d isvideo=%d isaudio=%d extension=%s\n",audionum,container_audio.isvideo,container_audio.isaudio,container_audio.extension);
                    }
    //                sprintf(videoname,"%d",videonum);
    //                sprintf(audioname,"%d",audionum);
                    if (container_video.isaudio && container_video.isvideo) {
                        strcpy(audioname,videoname);
                        audionum=videonum;
                        get_container(&container_audio,audionum);
                    }
                    if (ESCAPE_PRESSED) {
                        ESCAPE_PRESSED=0;
                        printf("ABORTING, WAITING FOR YOUTUBE-DL TO END\n");
                        while (fgets(line,1000,pfile)) printf("Waiting for youtube-dl -> %s\n",line);
                        printf("youtube-dl FINISHED\n");
                        pclose(pfile);
                        get_video_thread_running=0;
                        return;
                    }
                    if (videonum>0) {
//                        printf("VIDEO=%s,AUDIO=%s\n",videoname,audioname);
//                        wprintf(L"\x1b[34;47m");
                        printf("DOWNLOADING %s %s %s\n",idname,link,filename);
//                        wprintf(L"\x1b[0m");
                        sprintf(com,"getyoutube \"%s\"",idname);
                        system(com);
//                        if (audionum==0) {
//                            printf("extracting audio\n");
//                            char filename2[1000];
//                            sscanf(line, "%1000[^\n]", filename2);
//                            sprintf(com,"ffmpeg -i \"../convert/files/%s\" \"../convert/files/%s.f0.webm\"",filename2,filename);
//                            system(com);
//                        }
//                        monitor_off=1;
                        char test[1000];
                        int video_ok=0;
                        int audio_ok=0;
                        int subs_ok=0;
                        sprintf(test,"../convert/files/%s.f%d.%s",filename,videonum,container_video.extension);
//                        sprintf(test,"../convert/files/%s.f%d.webm",filename,videonum);
                        if (file_exists(test)) {
                            sprintf(videoname,"%s.f%d.%s",filename,videonum,container_video.extension);
                            printf("TESTED VIDEO: MATCH! %s\n",videoname);
//                            sprintf(videoname,"%s.f%d.webm",filename,videonum);
                            video_ok=1;
                        }  else {
                            char check[1000]="";
                            sprintf(check,"../convert/files/%s.f%d.%s.part",filename,videonum,container_video.extension);
                            if (file_exists(check)) {
                                sprintf(com,"move %s %s",check,test);
                                system(com);
                            }
                            if (file_exists(test)) {
                                sprintf(videoname,"%s.f%d.%s",filename,videonum,container_video.extension);
                                printf("TESTED VIDEO: MATCH! %s\n",videoname);
    //                            sprintf(videoname,"%s.f%d.webm",filename,videonum);
                                video_ok=1;
                            } else
                                printf("TESTED VIDEO: NO MATCH ../convert/files/%s.f%d.%s\n",filename,videonum,container_video.extension);
                        }
                        sprintf(test,"../convert/files/%s.f%d.%s",filename,audionum,container_audio.extension);
                        if (file_exists(test)) {
                            sprintf(audioname,"%s.f%d.%s",filename,audionum,container_audio.extension);
                            printf("TESTED AUDIO: MATCH! %s\n",audioname);
                            audio_ok=1;
                        } else {
                            printf("TESTED AUDIO: NO MATCH  ../convert/files/%s.f%d.%s\n",filename,audionum,container_audio.extension);
                        }
//nonono
//                        sprintf(test,"../convert/files/%s.%s",filename,SUBTITLES);
                        sprintf(test,"../convert/files/%s.%s.%s",filename,SUBTITLES,SUBTITLE_FORMAT);
//                        sprintf(test,"../convert/files/%s.%s.vtt",filename,SUBTITLES);
                        char lang[10]="";
                        char lang_en[10]="";
                        if (file_exists(test)) {
                            sprintf(subsname,"%s.%s.%s",filename,SUBTITLES,SUBTITLE_FORMAT);
//                            sprintf(subsname,"%s.%s.vtt",filename,SUBTITLES);
                            printf("TESTED SUBTITLES: MATCH! %s\n",subsname);
                            subs_ok=1;
                            strcpy(lang,SUBTITLES);
                        } else {
                                printf("TESTED SUBTITLES: NO MATCH ../convert/files/%s.%s.%s\n",filename,SUBTITLES,SUBTITLE_FORMAT);
//                                printf("TESTED SUBTITLES: NO MATCH ../convert/files/%s.%s.vtt\n",filename,SUBTITLES);
                                sprintf(test,"../convert/files/%s.%s.%s",filename,"en",SUBTITLE_FORMAT);
//                                sprintf(test,"../convert/files/%s.%s.vtt",filename,"en");
                                if (file_exists(test)) {
                                    sprintf(subsname,"%s.%s.%s",filename,"en",SUBTITLE_FORMAT);
//                                    sprintf(subsname,"%s.%s.vtt",filename,"en");
                                    strcpy(lang,"en");
                                    printf("TESTED SUBTITLES: MATCH! %s\n",subsname);
                                    subs_ok=1;
                                } else {
                                    printf("TESTED SUBTITLES: NO MATCH ../convert/files/%s.%s.%s\n",filename,"en",SUBTITLE_FORMAT);
//                                    printf("TESTED SUBTITLES: NO MATCH ../convert/files/%s.%s.vtt\n",filename,"en");
                                }
                        }
                        if (subs_ok==1 && strcmp("srt",SUBTITLE_FORMAT)==0) {
                            sprintf(com,"subtitle-overlap-fixer ../convert/files/\"%s\"",subsname);
                            system(com);
                            strcat(subsname,".fixed");

//english
                            sprintf(subsname_en,"%s.%s.%s",filename,"en",SUBTITLE_FORMAT);
//                                    sprintf(subsname,"%s.%s.vtt",filename,"en");
                            strcpy(lang_en,"en");
                            sprintf(com,"subtitle-overlap-fixer ../convert/files/\"%s\"",subsname_en);
                            system(com);
                            strcat(subsname_en,".fixed");

                        }
                        if (video_ok && audio_ok && subs_ok) {

                            textfiles.lock();
                            if (file=fopen("../convert/files/convert.txt","a")) {
                                fprintf(file,"VIDEO=\"%s\" AUDIO=\"%s\" SUBS=\"%s\" LANG=\"%s\" TIME=\"%s\"\n",videoname,audioname,subsname,lang,str_time);
                                fclose(file);
                            } else {
                                printf("CAN NOT WRITE TO FILE ../convert/files/convert.txt\n");
                            }
                            textfiles.unlock();
                            if (file=fopen("../convert/files/convert.bat","a")) {
                                char q_video[1000];
                                char q_audio[1000];
                                char q_subs[1000];
                                sprintf(q_video,"\"%s\"",videoname);
                                sprintf(q_audio,"\"%s\"",audioname);


                                char converted[1000]="";
                                strcpy(converted,subsname);
                                while (replace_str(converted,"\'","[single_quote]"));
                                while (replace_str(converted,"[single_quote]","\\'\\'\\\\'"));
                                sprintf(q_subs, "\"f='%s'\"",converted);
//                                sprintf(q_subs, "\"f='%s'\"",subsname);
                                char outputfile[1000];
                                char data[1000]="";

//                                sscanf(videoname,"%999[^.]",data);

                                strcpy(data,videoname);
                                while (strlen(data)>=1 && data[strlen(data)-1]!='.') {
                                    data[strlen(data)-1]='\0';
                                }
                                if (strlen(data)>=1) data[strlen(data)-1]='\0';

                                while (strlen(data)>=1 && data[strlen(data)-1]!='.') {
                                    data[strlen(data)-1]='\0';
                                }
                                if (strlen(data)>=1) data[strlen(data)-1]='\0';



                                sprintf(outputfile,"\"out/%s.%s.mp4\"",data,lang);
                                if (strlen(FFMPEGCOMMAND_BURN_SUBS)>0) {
                                    fprintf(file,FFMPEGCOMMAND_BURN_SUBS,
                                            q_video,q_audio,q_subs,outputfile);
                                    fprintf(file,"\n");
                                } else {
                                    fprintf(file,"ffmpeg.exe -hide_banner -i %s -i %s -map 0:v:0 -map 1:a:0 -strict -2 -vf subtitles=%s -c:s mov_text -c:v libx264 -preset veryfast -crf 23 -c:a aac -b:a 96k -pix_fmt yuv420p %s",
                                            q_video,q_audio,q_subs,outputfile);
                                    fprintf(file,"\n");
                                }
                                fclose(file);
                                if (go_burn) {
                                    burn_next_sub_ready_mutex.lock();
                                    start_burning=1;
                                    burn_next_sub_ready_mutex.unlock();
//                                    go_burn=0;
                                }
                            } else {
                                printf("CAN NOT WRITE TO FILE ../convert/files/convert.bat\n");
                            }
                            if (file=fopen("../convert/files/convert_en.bat","a")) {
                                char q_video[1000];
                                char q_audio[1000];
                                char q_subs[1000];
                                sprintf(q_video,"\"%s\"",videoname);
                                sprintf(q_audio,"\"%s\"",audioname);


                                char converted[1000]="";
                                strcpy(converted,subsname_en);
                                while (replace_str(converted,"\'","[single_quote]"));
                                while (replace_str(converted,"[single_quote]","\\'\\'\\\\'"));
                                sprintf(q_subs, "\"f='%s'\"",converted);
//                                sprintf(q_subs, "\"f='%s'\"",subsname);
                                char outputfile[1000];
                                char data[1000]="";

//                                sscanf(videoname,"%999[^.]",data);

                                strcpy(data,videoname);
                                while (strlen(data)>=1 && data[strlen(data)-1]!='.') {
                                    data[strlen(data)-1]='\0';
                                }
                                if (strlen(data)>=1) data[strlen(data)-1]='\0';

                                while (strlen(data)>=1 && data[strlen(data)-1]!='.') {
                                    data[strlen(data)-1]='\0';
                                }
                                if (strlen(data)>=1) data[strlen(data)-1]='\0';



                                sprintf(outputfile,"\"out/%s.%s.mp4\"",data,lang_en);
                                if (strlen(FFMPEGCOMMAND_BURN_SUBS)>0) {
                                    fprintf(file,FFMPEGCOMMAND_BURN_SUBS,
                                            q_video,q_audio,q_subs,outputfile);
                                    fprintf(file,"\n");
                                } else {
                                    fprintf(file,"ffmpeg.exe -hide_banner -i %s -i %s -map 0:v:0 -map 1:a:0 -strict -2 -vf subtitles=%s -c:s mov_text -c:v libx264 -preset veryfast -crf 23 -c:a aac -b:a 96k -pix_fmt yuv420p %s",
                                            q_video,q_audio,q_subs,outputfile);
                                    fprintf(file,"\n");
                                }
                                fclose(file);
                                if (go_burn) {
                                    burn_next_sub_ready_mutex.lock();
                                    start_burning=1;
                                    burn_next_sub_ready_mutex.unlock();
//                                    go_burn=0;
                                }
                            } else {
                                printf("CAN NOT WRITE TO FILE ../convert/files/convert.bat\n");
                            }


                        }
                        if (video_ok && audio_ok) {
                            textfiles.lock();
                            if (file=fopen("../convert/files/list.txt","a")) {
                                if (videonum==audionum) {
                                    fprintf(file,"%s\n",videoname);
                                    fclose(file);
                                } else {
                                    sprintf(test,"../convert/files/%s.%s",filename,container_video.extension);
                                    if (file_exists(test))
                                        fprintf(file,"%s.%s\n",filename,container_video.extension);
                                    else {
                                        sprintf(test,"../convert/files/%s.mkv",filename);
                                        if (file_exists(test))
                                            fprintf(file,"%s.mkv\n",filename);
                                        else {
                                            sprintf(test,"../convert/files/%s.mp4",filename);
                                            if (file_exists(test))
                                                fprintf(file,"%s.mp4\n",filename);
                                            else {
                                                sprintf(test,"../convert/files/%s.avi",filename);
                                                if (file_exists(test))
                                                    fprintf(file,"%s.avi\n",filename);
                                                else {
                                                    sprintf(test,"../convert/files/%s.webm",filename);
                                                    if (file_exists(test))
                                                        fprintf(file,"%s.webm\n",filename);
                                                }
                                            }
                                        }
                                    }
                                }
                                fclose(file);
                            } else {
                                printf("CAN NOT WRITE TO FILE ../convert/files/list.txt\n");
                            }
                            if (file=fopen("../convert/converted/list.txt","a")) {
                                if (videonum==audionum) {
                                    fprintf(file,"%s\n",videoname);
                                    fclose(file);
                                } else {
                                    sprintf(test,"../convert/files/%s.%s",filename,container_video.extension);
                                    if (file_exists(test))
                                        fprintf(file,"%s.%s\n",filename,container_video.extension);
                                    else {
                                        sprintf(test,"../convert/files/%s.mkv",filename);
                                        if (file_exists(test))
                                            fprintf(file,"%s.mkv\n",filename);
                                        else {
                                            sprintf(test,"../convert/files/%s.mp4",filename);
                                            if (file_exists(test))
                                                fprintf(file,"%s.mp4\n",filename);
                                            else {
                                                sprintf(test,"../convert/files/%s.avi",filename);
                                                if (file_exists(test))
                                                    fprintf(file,"%s.avi\n",filename);
                                                else {
                                                    sprintf(test,"../convert/files/%s.webm",filename);
                                                    if (file_exists(test))
                                                        fprintf(file,"%s.webm\n",filename);
                                                }
                                            }
                                        }
                                    }
                                }
                                fclose(file);
                            } else {
                                printf("CAN NOT WRITE TO FILE ../convert/converted/list.txt\n");
                            }

                            textfiles.unlock();
                        }
                    } else {
                        printf("ERROR GETTING VIDEOCODE AND/OR AUDIO CODE FROM ./VIDEO.INFO FAILED FOR %s %s\n",link,filename);
                    }
                }
                if (strlen(filename)==0) {
                    printf("ERROR READING LINE INFO FROM VIDEO.INFO FROM %s FAILED\n",link);
                }
                fflush(pfile);
                pclose(pfile);
            } else {
                printf("GETTING VIDEO.INFO FROM %s FAILED\n",link);
            }
        }
    }
    get_video_thread_running=0;
    return;
}

int dos_command_thread_running=0;
extern int end_screen;
extern int trim(char * text);

void trimTrailing(char * str)
{
    int index, i;

    /* Set default index */
    index = -1;

    /* Find last index of non-white space character */
    i = 0;
    while(str[i] != '\0')
    {
        if(str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
        {
            index= i;
        }

        i++;
    }

    /* Mark next character to last non-white space character as NULL */
    str[index + 1] = '\0';
}
void dos_command() {
    char line[10000]="";

    printf("DOS COMMAND: ");
    char com[1000];
    int cnt=0;
    int c;
    while ((c = getchar()) != '\n' && cnt < 1000) {
        com[cnt] = c;
        ++cnt;
    }
    com[cnt]='\0';
//    printf("com=%s\n",com);
//    sscanf("%s",com);
    if (ESCAPE_PRESSED) {
        ESCAPE_PRESSED=0;
        printf("ABORTING\n");
        dos_command_thread_running=0;
        return;
    }
    if (strlen(com)==0) {
        dos_command_thread_running=0;
        return;
    }
    print_to_screen_buf(1,com,36,COL_GREEN,COL_WHITE,COL_WHITE_T,PRINT_FONT_OUTLINE,TXT_REG);
    FILE * pfile;
    if (pfile=popen(com,"r") ) {
        while (fgets(line,10000,pfile)) {
            trimTrailing(line);
            if (strlen(line)>100) {
                char token=line[100];
                printf("-> %s\n",line);
                line[100]='\0';
                print_to_screen_buf(1,line,36,COL_CYAN,COL_WHITE,COL_WHITE_T,PRINT_FONT_OUTLINE,TXT_REG);
                line[100]=token;
                print_to_screen_buf(1,&line[100],36,COL_CYAN,COL_WHITE,COL_WHITE_T,PRINT_FONT_OUTLINE,TXT_REG);
            } else {
                print_to_screen_buf(1,line,36,COL_CYAN,COL_WHITE,COL_WHITE_T,PRINT_FONT_OUTLINE,TXT_REG);
                printf("-> %s\n",line);
            }
            if (ESCAPE_PRESSED) {
                pclose(pfile);
                ESCAPE_PRESSED=0;
                printf("<ESC> ABORTED\n");
                print_to_screen_buf(1,"<ESC> ABORTED",PRINT_FONT_SIZE,COL_RED,COL_WHITE,COL_WHITE_T,PRINT_FONT_OUTLINE,TXT_REG);
                dos_command_thread_running=0;
                return;
            }
            if (end_screen) {
                end_screen=0;
                pclose(pfile);
                printf("<END SCREEN>\n");
                print_to_screen_buf(1,"<ESC> ABORTED",PRINT_FONT_SIZE,COL_RED,COL_WHITE,COL_WHITE_T,PRINT_FONT_OUTLINE,TXT_REG);
                dos_command_thread_running=0;
                return;
            }
        }
        pclose(pfile);
    } else {
        printf("\nFAILED\n");
    }

    dos_command_thread_running=0;
    return;
}


void start_get_videos_thread() {
    if (!get_video_thread_running) {
        get_video_thread_running=1;
        get_videos_thread.launch();
//        printf("start_get_videos_thread()\n");
    } else {
        printf("Allready running....\n");
    }
}

void start_dos_command_thread() {
    if (!dos_command_thread_running) {
        dos_command_thread_running=1;
        dos_command_thread.launch();
//        printf("start_get_videos_thread()\n");
    } else {
        printf("Allready running....\n");
    }
}

void start_burn_next_sub_thread() {
    if (!burn_next_sub_thread_running) {
//      SFMLView1.setActive(false);
        if (record_screen==0) {
            burn_next_sub_thread_running=1;
            burn_next_sub_thread.launch();
        }
//        printf("burn_next_sub_tread.launch()\n");
    } else {
        printf("Allready running....\n");
        if (record_screen==0 && movieextern==0) {
            printf("Terminating....\n");
            burn_next_sub_thread.terminate();
            sf::sleep(sf::milliseconds(1000));
            printf("And running again....\n");
            burn_next_sub_thread.launch();
        } else
            printf("Allready running....(press 'b' and/or 'r'/SHFT-r)\n");
    }
}

char raw_name[2000];
char source_time[50];
char lang_nq[10]="";


void burn_next_sub() {
    static int line_count=1;
    static int ret=1;
    playsound=playsound|2;

    char data[1000]="";
    textfiles.lock();
    ret=select_from_list2(data,"../convert/files/convert.txt",line_count);
    textfiles.unlock();
    if (line_count>ret) {
        line_count=0;
        ret=1;
    }
    while (line_count<=ret) {
        if (ESCAPE_PRESSED) {
            ESCAPE_PRESSED=0;
            printf("ABORTING\n");
            burn_next_sub_thread_running=0;
            line_count=0;
            ret=1;
            return;
        }
        char print_line[1000]="";
        char videoname[1000]="";
        char videoname_nq[1000]="";
        char audioname[1000]="";
        char audioname_nq[1000]="";
        char subsname[1000]="";
        char recordname[1000]="";
        char subsname_nq[1000]="";

        textfiles.lock();
        ret=select_from_list2(data,"../convert/files/convert.txt",line_count);
        textfiles.unlock();

        if (ret==0) {
            sprintf(print_line,"../convert/files/convert.txt EMPTY?");
            printf("%s\n",print_line);
            line_count=0;
            burn_next_sub_thread_running=0;
            return;
        } else {
            line_count++;
            sscanf(data,"VIDEO=\"%999[^\"]\" AUDIO=\"%999[^\"]\" SUBS=\"%999[^\"]\" LANG=\"%9[^\"]\" TIME=\"%50[^\"]\"", videoname,audioname,subsname,lang_nq,source_time);
            if (strlen(videoname)==0) {
                printf("No video name detected. Empty line in convert.txt?\n");
                continue;
            }

//            sscanf(videoname,"%999[^.]",data);

            strcpy(data,videoname);
            while (strlen(data)>=1 && data[strlen(data)-1]!='.') {
                data[strlen(data)-1]='\0';
            }
            if (strlen(data)>=1) data[strlen(data)-1]='\0';

            while (strlen(data)>=1 && data[strlen(data)-1]!='.') {
                data[strlen(data)-1]='\0';
            }
            if (strlen(data)>=1) data[strlen(data)-1]='\0';


            strcpy(raw_name,data);
            sprintf(recordname,             "%s.%s.mp4",data,lang_nq);
            sprintf(record_outputfile,      "\"../record/%s.%s.mp4\"",data,lang_nq);
            sprintf(record_outputfile_nq,   "../record/%s.%s.mp4",data,lang_nq);
            sprintf(videoname_nq,           "../convert/files/%s",videoname);
            sprintf(audioname_nq,           "../convert/files/%s",audioname);
            sprintf(subsname_nq,            "../convert/files/%s",subsname);
            int cont=0;

            int maxlen=0;
            if (strlen(recordname)>maxlen) maxlen=strlen(recordname);
            if (strlen(videoname) >maxlen) maxlen=strlen(videoname);
            if (strlen(audioname) >maxlen) maxlen=strlen(audioname);
            if (strlen(subsname)  >maxlen) maxlen=strlen(subsname);
            char record_add[1000]="";
            char video_add[1000] ="";
            char audio_add[1000]="";
            char subs_add[1000]  ="";
            while ( strlen(recordname) + strlen(record_add) < maxlen) strcat(record_add," ");
            while ( strlen(videoname)  + strlen(video_add)  < maxlen) strcat(video_add, " ");
            while ( strlen(audioname)  + strlen(audio_add)  < maxlen) strcat(audio_add, " ");
            while ( strlen(subsname)   + strlen(subs_add)   < maxlen) strcat(subs_add,  " ");
            if (file_exists(record_outputfile_nq)) {
/*
                textfiles.lock();
                if (FILE * file=fopen("../convert/files/converted.txt","a")) {
                    fprintf(file,"VIDEO=\"%s\" AUDIO=\"%s\" SUBS=\"%s\" LANG=\"%s\" TIME=\"%s\"\n",videoname,audioname,subsname,lang_nq,source_time);
                    fclose(file);
                } else {
                    printf("CAN NOT WRITE TO FILE ../convert/files/converted.txt\n");
                }
                textfiles.unlock();
*/
                disp_open();

                    sprintf(print_line,"OUTPUT VIDEO FILE: \"%s\" EXISTS, SKIPPING. (DELETE IF NOT OK)",record_outputfile_nq);
                    printf("%s\n",print_line);
                    cont=1;
                    sprintf(print_line,"OUTPUT   = \"%s\"%s (../record/) EXISTS, SKIPPING. (DELETE IF NOT OK)",recordname,record_add);
                    print_to_screen_buf(1,print_line,PRINT_FONT_SIZE,COL_RED,COL_WHITE,COL_WHITE_T50,PRINT_FONT_OUTLINE,TXT_REG);

                disp_close2();

                char str_part[2000]="";
                if (file_exists(videoname_nq) || file_exists(audioname_nq) || file_exists(subsname_nq) ) {
                    disp_open();
                        sprintf(print_line,"MOVING FILES FROM ../CONVERT/FILES/ TO ../CONVERT/CONVERTED/ ...");
                        printf("%s\n",print_line);
                        print_to_screen_buf(1,print_line,PRINT_FONT_SIZE,COL_CYAN,COL_WHITE,COL_WHITE_T,PRINT_FONT_OUTLINE,TXT_REG);
                    disp_close2();

                    sprintf(str_part,"move \"..\\convert\\files\\%s*.*\" ..\\convert\\converted\\",raw_name);
                    FILE * pfile;
                    if (pfile=popen(str_part,"r") ) {
                        char line[1000]="";
                        while (fgets(line,1000,pfile)) {
                            printf("%s",line);
                            disp_open();

                                print_to_screen_buf(1,line,PRINT_FONT_SIZE,COL_CYAN,COL_WHITE,COL_WHITE_T,PRINT_FONT_OUTLINE,TXT_REG);

                            disp_close2();
                        }
                        pclose(pfile);

                    } else {
                        disp_open();

                        print_to_screen_buf(1,"Error opening pipe for move.",PRINT_FONT_SIZE,COL_RED,COL_WHITE,COL_WHITE_T,PRINT_FONT_OUTLINE,TXT_REG);

                        disp_close2();
                    }
                }
                continue;
            } else {
                disp_open();

                    sprintf(print_line,"OUTPUT   = \"%s\"%s (../record/)",recordname,record_add);
                    print_to_screen_buf(1,print_line,PRINT_FONT_SIZE,COL_BLUE,COL_WHITE,COL_WHITE_T50,PRINT_FONT_OUTLINE,TXT_REG);
                    printf("%s\n",print_line);

                disp_close2();
            }

            if (!file_exists(videoname_nq)) {
                disp_open();
                    sprintf(print_line,"INPUT VIDEO FILE: \"%s\" FILE DOES NOT EXIST",videoname_nq);
                    printf("%s\n",print_line);
                    cont=1;
    //                sprintf( print_line, "VIDEO    = \"%s\"%s NOT FOUND!!!",videoname_nq,video_add);
                    sprintf( print_line, "VIDEO    = \"%s\"%s (../convert/files) NOT FOUND!!!",videoname, video_add );
                    print_to_screen_buf(1,print_line,PRINT_FONT_SIZE,COL_WHITE,COL_RED,COL_WHITE_T,PRINT_FONT_OUTLINE,TXT_REG);

                disp_close2();
            } else {
                disp_open();

                    sprintf( print_line, "VIDEO    = \"%s\"%s (../convert/files) %s",videoname, video_add, get_info_video(videoname_nq));
                    printf("%s\n",print_line);
                    print_to_screen_buf(1,print_line,PRINT_FONT_SIZE,COL_BLUE,COL_WHITE,COL_WHITE_T,PRINT_FONT_OUTLINE,TXT_REG);

                disp_close2();
            }

            if (!file_exists(audioname_nq)) {
                disp_open();

                sprintf(print_line,"INPUT AUDIO FILE: \"%s\" FILE DOES NOT EXIST",audioname_nq);
                printf("%s\n",print_line);
                cont=1;
                sprintf(print_line,"AUDIO    = \"%s\"%s (../convert/files) NOT FOUND!!!",audioname_nq,audio_add);
                print_to_screen_buf(1,print_line,PRINT_FONT_SIZE,COL_WHITE,COL_RED,COL_WHITE_T,PRINT_FONT_OUTLINE,TXT_REG);

                disp_close2();

            } else {
                disp_open();

                sprintf(print_line,"AUDIO    = \"%s\"%s (../convert/files) %s",audioname, audio_add, get_info_audio(audioname_nq));
                printf("%s\n",print_line);
                print_to_screen_buf(1,print_line,PRINT_FONT_SIZE,COL_BLUE,COL_WHITE,COL_WHITE_T,PRINT_FONT_OUTLINE,TXT_REG);

                disp_close2();
            }

            if (!file_exists(subsname_nq)) {
                disp_open();

                sprintf(print_line,"INPUT SUBTITLE FILE: \"%s\" FILE DOES NOT EXIST",subsname_nq);
                printf("%s\n",print_line);
                cont=1;
                sprintf(print_line,"SUBTITLE = \"%s\"%s (../convert/files) NOT FOUND!!!",subsname_nq,subs_add);
                print_to_screen_buf(1,print_line,PRINT_FONT_SIZE,COL_WHITE,COL_RED,COL_WHITE_T,PRINT_FONT_OUTLINE,TXT_REG);

                disp_close2();
            } else {
                sprintf(print_line,"SUBTITLE = \"%s\"%s (../convert/files)",subsname,subs_add);
                disp_open();

                printf("%s\n",print_line);
                print_to_screen_buf(1,print_line,PRINT_FONT_SIZE,COL_BLUE,COL_WHITE,COL_WHITE_T,PRINT_FONT_OUTLINE,TXT_REG);

                disp_close2();
            }

            if (cont || combine) {
                continue;
            }

            sprintf(quote_video,"\"../convert/files/%s\"",videoname);
            sprintf(quote_audio,"\"../convert/files/%s\"",audioname);
            sprintf(quote_subs, "\"../convert/files/%s\"",subsname);


            char converted[1000]="";
            strcpy(converted,subsname);
            while (replace_str(converted,"\'","[single_quote]"));
//            while (replace_str(converted,"\;","[dot_comma]"));

            while (replace_str(converted,"[single_quote]","\\'\\'\\\\'"));
//            while (replace_str(converted,"[dot_comma]","\\'\\;\\\\'"));

//#FFMPEG_IN_SUBS="ffmpeg.exe -v 0 -hide_banner -i %s -vf subtitles=%s -c:s mov_text -f image2pipe -vcodec rawvideo -pix_fmt rgba -"


            sprintf(quote_subs_extra, "subtitles=f='../convert/files/%s'",converted);
            sprintf(quote_subs_extra2, "%s",converted);
//            sprintf(quote_subs_extra, "subtitles=f='../convert/files/%s'",converted);
//            sprintf(quote_subs_extra, "\"f='../convert/files/%s'\"",converted);

            recording_type=1;

            burn_next_sub_ready_mutex.lock();
            burn_subs=1;
            burn_next_sub_ready_mutex.unlock();

            disp_open();

            printf("LOADING: %s\n",videoname_nq);

            if (playing_start(videoname_nq)==0) {
                play_rate=1;
                strcpy(print_line,"EXTERNAL FFMPEG LOADING SUCCESFULL");
                print_to_screen_buf(1,print_line,PRINT_FONT_SIZE,COL_BLUE,COL_WHITE,COL_WHITE_T,PRINT_FONT_OUTLINE,TXT_REG);
                printf("%s\n",print_line);
                if (flop==0) rate_count=play_rate-1;
                else rate_count=play_rate;
                record_screen_num=0;
                flop=0;
                if (flop==0) rate_count=play_rate-1;
                else rate_count=play_rate;
                playsound=playsound|6;
                sf::sleep(sf::milliseconds(500.0));
                if (recording_start_m_orig()!=0)
                {
                    strcpy(print_line,"RECORDING_START_M_ORIG() FAILED");
                    print_to_screen_buf(1,print_line,PRINT_FONT_SIZE,COL_BLUE,COL_WHITE,COL_WHITE_T,PRINT_FONT_OUTLINE,TXT_REG);
                    printf("%s\n",print_line);
                    record_screen=0;
                    burn_next_sub_ready_mutex.lock();
                    burn_subs=0;
                    burn_next_sub_ready_mutex.unlock();
                    movieextern=1;
                    playing_end();
                    sf::sleep(sf::milliseconds(500.0));

                    burn_next_sub_thread_running=0;
                    playsound=playsound|7;

                    disp_close2();

                    return;
                }
                else
                {
                    sprintf(print_line,"RECORDING MOVIE 'b' ORIGINAL SIZE %d x %d",texture_from_internet.getSize().x,texture_from_internet.getSize().y);
                    print_to_screen_buf(1,print_line,PRINT_FONT_SIZE,COL_BLUE,COL_WHITE,COL_WHITE_T,PRINT_FONT_OUTLINE,TXT_REG);
                    printf("%s\n",print_line);
                    burn_next_sub_ready_mutex.lock();
                    movieextern=0;
                    record_pause=0;
                    record_screen=1;
//                    playing_end();
//                    SFMLView1.setVerticalSyncEnabled(true);
                    play_rate=1;
                    burn_next_sub_thread_running=0;

                    disp_close2();
                    playsound=playsound|8;
                    printf("EXITING BURN TRHEAD\n");
                    burn_next_sub_ready_mutex.unlock();
                    sf::sleep(sf::milliseconds(500.0));
                    return;
                }
            } else {
                strcpy(print_line,"FAILED STARTING MOVIE FROM FFMPEG EXTERN");
                movieextern=1;
                recording_type=0;
                playsound=playsound|5;
            }
            disp_close2();
        }
    }
//    burn_subs=0;
//    line_count=0;
    playsound=playsound|4;
    burn_next_sub_thread_running=0;
    return;
}


void get_container(struct container_struct * container, int num) {
    switch (num) {
        case 5	 : strcpy(container->extension,"flv");	container->isaudio=1; container->isvideo=1; break; // 	240p	-	    -	    -
        case 6	 : strcpy(container->extension,"flv");	container->isaudio=1; container->isvideo=1; break; // 	270p	-	    -	    -
        case 17	 : strcpy(container->extension,"3gp");	container->isaudio=1; container->isvideo=1; break; // 	144p	-	    -	    -
        case 18	 : strcpy(container->extension,"mp4");	container->isaudio=1; container->isvideo=1; break; // 	360p	-	    -	    -
        case 22	 : strcpy(container->extension,"mp4");	container->isaudio=1; container->isvideo=1; break; // 	720p	-	    -	    -
        case 34	 : strcpy(container->extension,"flv");	container->isaudio=1; container->isvideo=1; break; // 	360p	-	    -	    -
        case 35	 : strcpy(container->extension,"flv");	container->isaudio=1; container->isvideo=1; break; // 	480p	-	    -	    -
        case 36	 : strcpy(container->extension,"3gp");	container->isaudio=1; container->isvideo=1; break; // 	180p	-	    -	    -
        case 37	 : strcpy(container->extension,"mp4");	container->isaudio=1; container->isvideo=1; break; // 	1080p	-	    -	    -
        case 38	 : strcpy(container->extension,"mp4");	container->isaudio=1; container->isvideo=1; break; // 	3072p	-	    -	    -
        case 43	 : strcpy(container->extension,"webm");	container->isaudio=1; container->isvideo=1; break; // 	360p	-	    -	    -
        case 44	 : strcpy(container->extension,"webm");	container->isaudio=1; container->isvideo=1; break; // 	480p	-	    -	    -
        case 45	 : strcpy(container->extension,"webm");	container->isaudio=1; container->isvideo=1; break; // 	720p	-	    -	    -
        case 46	 : strcpy(container->extension,"webm");	container->isaudio=1; container->isvideo=1; break; // 	1080p	-	    -	    -
        case 82	 : strcpy(container->extension,"mp4");	container->isaudio=1; container->isvideo=1; break; // 	360p	-	    -	    3D
        case 83	 : strcpy(container->extension,"mp4");	container->isaudio=1; container->isvideo=1; break; // 	480p	-	    -	    3D
        case 84	 : strcpy(container->extension,"mp4");	container->isaudio=1; container->isvideo=1; break; // 	720p	-	    -	    3D
        case 85	 : strcpy(container->extension,"mp4");	container->isaudio=1; container->isvideo=1; break; // 	1080p	-	    -	    3D
        case 92	 : strcpy(container->extension,"hls");	container->isaudio=1; container->isvideo=1; break; // 	240p	-	    -	    3D
        case 93	 : strcpy(container->extension,"hls");	container->isaudio=1; container->isvideo=1; break; // 	360p	-	    -	    3D
        case 94	 : strcpy(container->extension,"hls");	container->isaudio=1; container->isvideo=1; break; // 	480p	-	    -	    3D
        case 95	 : strcpy(container->extension,"hls");	container->isaudio=1; container->isvideo=1; break; // 	720p	-	    -	    3D
        case 96	 : strcpy(container->extension,"hls");	container->isaudio=1; container->isvideo=1; break; // 	1080p	-	    -	    -
        case 100 : strcpy(container->extension,"webm");	container->isaudio=1; container->isvideo=1; break; // 	360p	-	    -	    3D
        case 101 : strcpy(container->extension,"webm");	container->isaudio=1; container->isvideo=1; break; // 	480p	-	    -	    3D
        case 102 : strcpy(container->extension,"webm");	container->isaudio=1; container->isvideo=1; break; // 	720p	-	    -	    3D
        case 132 : strcpy(container->extension,"hls");	container->isaudio=1; container->isvideo=1; break; // 	240p	-	    -
        case 133 : strcpy(container->extension,"mp4");	container->isaudio=0; container->isvideo=1; break; //	    240p	-	    -
        case 134 : strcpy(container->extension,"mp4");	container->isaudio=0; container->isvideo=1; break; //	    360p	-	    -
        case 135 : strcpy(container->extension,"mp4");	container->isaudio=0; container->isvideo=1; break; //	    480p	-	    -
        case 136 : strcpy(container->extension,"mp4");	container->isaudio=0; container->isvideo=1; break; //	    720p	-	    -
        case 137 : strcpy(container->extension,"mp4");	container->isaudio=0; container->isvideo=1; break; //	    1080p	-	    -
        case 138 : strcpy(container->extension,"mp4");	container->isaudio=0; container->isvideo=1; break; //	    2160p60	-	    -
        case 139 : strcpy(container->extension,"m4a");	container->isaudio=1; container->isvideo=0; break; //	    -	    48k	    -
        case 140 : strcpy(container->extension,"m4a");	container->isaudio=1; container->isvideo=0; break; //	    -	    128k	-
        case 141 : strcpy(container->extension,"m4a");	container->isaudio=1; container->isvideo=0; break; //	    -	    256k	-
        case 151 : strcpy(container->extension,"hls");	container->isaudio=1; container->isvideo=1; break; //	72p	    -	    -
        case 160 : strcpy(container->extension,"mp4");	container->isaudio=0; container->isvideo=1; break; //	    144p	-	    -
        case 167 : strcpy(container->extension,"webm");	container->isaudio=0; container->isvideo=1; break; //	    360p	-	    -
        case 168 : strcpy(container->extension,"webm");	container->isaudio=0; container->isvideo=1; break; //	    480p	-	    -
        case 169 : strcpy(container->extension,"webm");	container->isaudio=0; container->isvideo=1; break; //	    1080p	-	    -
        case 171 : strcpy(container->extension,"webm");	container->isaudio=1; container->isvideo=0; break; //	    -	    128k	-
        case 218 : strcpy(container->extension,"webm");	container->isaudio=0; container->isvideo=1; break; //	    480p	-	    -
        case 219 : strcpy(container->extension,"webm");	container->isaudio=0; container->isvideo=1; break; //	    144p	-	    -
        case 242 : strcpy(container->extension,"webm");	container->isaudio=0; container->isvideo=1; break; //	    240p	-	    -
        case 243 : strcpy(container->extension,"webm");	container->isaudio=0; container->isvideo=1; break; //	    360p	-	    -
        case 244 : strcpy(container->extension,"webm");	container->isaudio=0; container->isvideo=1; break; //	    480p	-	    -
        case 245 : strcpy(container->extension,"webm");	container->isaudio=0; container->isvideo=1; break; //	    480p	-	    -
        case 246 : strcpy(container->extension,"webm");	container->isaudio=0; container->isvideo=1; break; //	    480p	-	    -
        case 247 : strcpy(container->extension,"webm");	container->isaudio=0; container->isvideo=1; break; //	    720p	-	    -
        case 248 : strcpy(container->extension,"webm");	container->isaudio=0; container->isvideo=1; break; //	    1080p	-	    -
        case 249 : strcpy(container->extension,"webm");	container->isaudio=1; container->isvideo=0; break; //	    -	    50k	    -
        case 250 : strcpy(container->extension,"webm");	container->isaudio=1; container->isvideo=0; break; //	    -	    70k	    -
        case 251 : strcpy(container->extension,"webm");	container->isaudio=1; container->isvideo=0; break; //	    -	    160k	-
        case 264 : strcpy(container->extension,"mp4");	container->isaudio=0; container->isvideo=1; break; //	    1440p	-	    -
        case 266 : strcpy(container->extension,"mp4");	container->isaudio=0; container->isvideo=1; break; //	    2160p60	-	    -
        case 271 : strcpy(container->extension,"webm");	container->isaudio=0; container->isvideo=1; break; //	    1440p	-	    -
        case 272 : strcpy(container->extension,"webm");	container->isaudio=0; container->isvideo=1; break; //	    4320p	-	    -
        case 278 : strcpy(container->extension,"webm");	container->isaudio=0; container->isvideo=1; break; //	    144p	-	    -
        case 298 : strcpy(container->extension,"mp4");	container->isaudio=0; container->isvideo=1; break; //	    720p60	-	    -
        case 299 : strcpy(container->extension,"mp4");	container->isaudio=0; container->isvideo=1; break; //	    1080p60	-	    -
        case 302 : strcpy(container->extension,"webm");	container->isaudio=0; container->isvideo=1; break; //	    720p60	-	    -
        case 303 : strcpy(container->extension,"webm");	container->isaudio=0; container->isvideo=1; break; //	    1080p60	-	    -
        case 308 : strcpy(container->extension,"webm");	container->isaudio=0; container->isvideo=1; break; //	    1440p60	-	    -
        case 313 : strcpy(container->extension,"webm");	container->isaudio=0; container->isvideo=1; break; //	    2160p	-	    -
        case 315 : strcpy(container->extension,"webm");	container->isaudio=0; container->isvideo=1; break; //	    2160p60	-	    -
        case 330 : strcpy(container->extension,"webm");	container->isaudio=0; container->isvideo=1; break; //	    144p60	-	    hdr
        case 331 : strcpy(container->extension,"webm");	container->isaudio=0; container->isvideo=1; break; //	    240p60	-	    hdr
        case 332 : strcpy(container->extension,"webm");	container->isaudio=0; container->isvideo=1; break; //	    360p60	-	    hdr
        case 333 : strcpy(container->extension,"webm");	container->isaudio=0; container->isvideo=1; break; //	    480p60	-	    hdr
        case 334 : strcpy(container->extension,"webm");	container->isaudio=0; container->isvideo=1; break; //	    720p60	-	    hdr
        case 335 : strcpy(container->extension,"webm");	container->isaudio=0; container->isvideo=1; break; //	    1080p60	-	    hdr
        case 336 : strcpy(container->extension,"webm");	container->isaudio=0; container->isvideo=1; break; //	    1440p60	-	    hdr
        case 337 : strcpy(container->extension,"webm");	container->isaudio=0; container->isvideo=1; break; //	    2160p60	-	    hdr
        default  : strcpy(container->extension,"");	    container->isaudio=0; container->isvideo=0; break; //	    2160p60	-	    hdr

            break;

    }
    return;
}

void disp_open() {
//    something_to_do=1;
//    animate_lock.lock();
//    SFMLView1.setActive(true);
//    something_to_do=0;
}

void disp_close() {
//    SFMLView1.setActive(false);
//    animate_lock.unlock();
//    while (something_to_do) sf::sleep(sf::milliseconds(1.0));
}

void disp_close2() {
//    SFMLView1.setActive(false);
//    animate_lock.unlock();
//    sf::sleep(sf::milliseconds(100.0));
//    while (something_to_do) sf::sleep(sf::milliseconds(10.0));
}


struct pts_struct {
    int var_font;
    char text_to_print[2000];
    int font_size;
    sf::Color paint_in;
    sf::Color paint_out;
    sf::Color paint_back;
    float outline;
    sf::Uint32 text_type;
};

struct pts_struct pts;

void print_to_screen_buf(int var_font, char * text_to_print, int font_size, sf::Color paint_in, sf::Color paint_out, sf::Color paint_back, float outline, sf::Uint32 text_type ) {
    int is_one=1;

    while (is_one) {
        animate_lock.lock();
        if (something_to_do==0) {
            is_one=0;
            continue;
        } else animate_lock.unlock();
        sf::sleep(sf::milliseconds(10.0));
    }

    pts.var_font=var_font;
    strcpy(pts.text_to_print,text_to_print);
    pts.font_size=font_size;
    pts.paint_in=paint_in;
    pts.paint_out=paint_out;
    pts.paint_back=paint_back;
    pts.text_type=text_type;
    pts.outline=outline;
    something_to_do=1;

    animate_lock.unlock();
}
//                    print_to_screen_buf(1,print_line,PRINT_FONT_SIZE,COL_RED,COL_WHITE,COL_WHITE_T50,PRINT_FONT_OUTLINE,TXT_REG);

