#define SFML_STATIC
#undef UNICODE
#include <conio.h>
#include <wchar.h>
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

extern char SHADERDIR[];
extern char error_msg[];
extern int error_flag;
extern struct stat stat_buffer;

bool file_exists(const char * filename)
{
//    struct stat stat_buffer;
    int exist = stat(filename,&stat_buffer);
    if (exist==0)
    {
        return true;
    }
//    strcpy(error_msg,"FILE NOT FOUND: ");
//    strcat(error_msg,filename);
//    error_flag=1;
    return false;
}

bool file_exists2(const char * filename)
{
    if (FILE * file = fopen(filename, "r"))
    {
        fclose(file);
        strcpy(error_msg,"FILE EXISTS, PRESS AGAIN TO CONFIRM: ");
        strcat(error_msg,filename);
        error_flag=1;
        return true;
    }
    return false;
}

bool file_exists3(const char * filename)
{
    if (FILE * file = fopen(filename, "r"))
    {
        fclose(file);
        return true;
    }
    return false;
}

extern int LOGFILE;

void savevalue_float(char *filenaam, double value)
{
    FILE* file = fopen (filenaam, "w");

    if (file!=NULL)
    {
        fprintf (file, "%29.28lf\n",value);
        fclose (file);
    }
    return;
}

double loadvalue_float(char *filenaam)
{
    FILE* file = fopen (filenaam, "r");
    double value;
    if (file!=NULL)
    {
        fscanf (file, "%lf\n",&value);
        fclose (file);
    }
    return value;
}

void savedata(char *naam, int data)
{
    if (LOGFILE==1)
    {
        FILE* file = fopen ("data.txt", "a");
        int i = 0;
        char score[20];

        if (file!=NULL)
        {
            sprintf(score,"%d",data);
            //		itoa(data,score,10);
            fprintf (file, "%s %s\n",score,naam);
            fclose (file);
        }
    }
    return;
}

void logfile(char *line)
{
    if (LOGFILE==1)
    {
        FILE* file = fopen ("logfile.txt", "a");

        if (file!=NULL)
        {
            fprintf (file, "%s\n",line);
            fclose (file);
        }
    }
    return;
}

extern char LEVELDIR[];
extern int replace_str(char *str, char *orig, char *rep);

int check_dir(int BITMAPSX,int BITMAPSY,int level)
{
    char dirname[1000];
    char err[100];
    DIR* dir;
    int msgboxID;

//    strcpy(dirname,"levels");
    strcpy(dirname,LEVELDIR);
   	while (replace_str(dirname,"/","\\\\"));
    dir = opendir(dirname);
    if (!dir)
    {
        mkdir(dirname);
        dir = opendir(dirname);
        if (!dir)
        {
            msgboxID=MessageBox(NULL, "CANNOT CREATE DIRECOTRY FOR LEVELS", "ERROR",MB_OK);
            return(1);
        }
        if (dir)
            closedir(dir);
    }

//    sprintf(dirname,"levels\\%dx%d",BITMAPSX,BITMAPSY);
    sprintf(dirname,"%s\\%dx%d",LEVELDIR,BITMAPSX,BITMAPSY);
   	while (replace_str(dirname,"/","\\\\"));
    dir = opendir(dirname);
    if (!dir)
    {
        mkdir(dirname);
        dir = opendir(dirname);
        if (!dir)
        {
            sprintf(err,"CANNOT MAKE DIRECTORY %s",dirname);
            msgboxID=MessageBox(NULL, err, "ERROR",MB_OK);
            return(1);
        }
        if (dir)
            closedir(dir);
    }

//    sprintf(dirname,"levels\\%dx%d\\%03d",BITMAPSX,BITMAPSY,level);
    sprintf(dirname,"%s\\%dx%d\\%03d",LEVELDIR,BITMAPSX,BITMAPSY,level);
   	while (replace_str(dirname,"/","\\\\"));
    dir = opendir(dirname);
    if (!dir)
    {
        mkdir(dirname);
        dir = opendir(dirname);
        if (!dir)
        {
            sprintf(err,"CANNOT MAKE DIRECTORY %s",dirname);
            msgboxID=MessageBox(NULL, err, "ERROR",MB_OK);
            return(1);
        }
        if (dir)
            closedir(dir);
    }

    return 0;
}

extern int reload_init();
extern char error_msg2[];
extern int error_flag2;
extern char *line;
extern int mazesizex;
extern int mazesizey;


int select_from_list(char *filename, char * path, int next)
{
    FILE* file;
    char naam[2000];

//    reload_init();
    sprintf(naam,"%s/list.txt",path);

    file = fopen (naam, "r");

    if (file==NULL)
    {
        sprintf(error_msg2,"FILE NOT FOUND: %s",naam);
        error_flag2=2;
        strcpy(filename,"");
        return 0;
    }

//    char var[100];
    int number=0;
    int max=0;
    int random=0;
    if (fgets (line,mazesizex*2+100, file)!=NULL )
    {
        char command[20];
        sscanf(line,"RANDOM=%[^\n]\n",command);
        if (strcmp("ON",command)==0)
            random=1;
        else
            max++;
    }
    while (fgets (line,mazesizex*2+100, file)!=NULL )
    {
        max++;
    }
    if (max==0)
    {
        sprintf(error_msg,"FILE %s IS EMPTY",naam);
        error_flag=2;
        strcpy(filename,"");
        fclose (file);
        return(0);
    }
//    number=((rand()*rand())%max)+1;
    if (random==0) {
        number=next;
        if (number>max) number=1;
    }
    else {
        number=(rand()*rand()+rand())%max+2
        ;
    }

    fclose (file);
    file = fopen (naam, "r");
    int i;
    for (i=0; i<number; i++)
    {
        fgets (line,mazesizex*2+100, file);
    }
    if (toupper(line[0])=='H' && toupper(line[1])=='T' && toupper(line[2])=='T' && toupper(line[3])=='P')
    {
        strcpy(filename,line);
    }
    else
    {
        if (line[1]!=':')
        {
            strcpy(filename,path);
            strcat(filename,"/");
        }
        else
            strcpy(filename,"");
        strcat(filename,line);
    }

    if (filename[strlen(filename)-1]=='\r' || filename[strlen(filename)-1]=='\n')
        filename[strlen(filename)-1]='\0';

    sprintf(error_msg,"FILE %d SELECTED FROM %s: %s",number,naam,filename);
    error_flag=2;
    fclose (file);
    return (max);
}

int select_from_list2(char *filename, char * path, int next)
{
    FILE* file;
    char naam[2000];
    char line[10000];

    reload_init();
    sprintf(naam,"%s",path);

    file = fopen (naam, "r");

    if (file==NULL)
    {
        sprintf(error_msg2,"FILE NOT FOUND: %s",naam);
        error_flag2=2;
        strcpy(filename,"");
        return 0;
    }

//    char var[100];
    int number=0;
    int max=0;
    int random=0;
    if (fgets (line,10000, file)!=NULL )
    {
        char command[20];
        sscanf(line,"RANDOM=%[^\n]\n",command);
        if (strcmp("ON",command)==0)
            random=1;
        else
            max++;
    }
    while (fgets (line,10000, file)!=NULL )
    {
        max++;
    }
    if (max==0)
    {
        sprintf(error_msg,"FILE %s IS EMPTY",naam);
        error_flag=2;
        strcpy(filename,"");
        fclose (file);
        return(0);
    }
//    number=((rand()*rand())%max)+1;
    if (random==0) {
        number=next;
        if (number>max) number=1;
    }
    else {
        number=(rand()*rand()+rand())%max+2;
    }

    fclose (file);
    file = fopen (naam, "r");
    int i;
    for (i=0; i<=number; i++)
    {
        fgets (line,10000, file);
    }
    strcpy(filename,line);

    if (filename[strlen(filename)-1]=='\r' || filename[strlen(filename)-1]=='\n')
        filename[strlen(filename)-1]='\0';

extern char error_msg3[];
extern int error_flag3;
    sprintf(error_msg3,"LINE %d SELECTED FROM %s: %s",number,naam,filename);
    error_flag3=2;
    fclose (file);
    return (max);
}


int select_movie(char *filename, char * path)
{
    static int next=0;
    static int total=0;
    next++;
    if (next>total) next=1;
    total=select_from_list(filename, path, next);
    if (total==0)
        return 0;
    return next;
}

int select_geodat(char *filename, char * path)
{
    static int next=0;
    static int total=0;
    next++;
    if (next>total) next=1;
    total=select_from_list(filename, path, next);
    if (total==0)
        return 0;
    return next;
}

int select_macro(char *filename, char * path)
{
    static int next=0;
    static int total=0;
    next++;
    if (next>total) next=1;
    total=select_from_list(filename, path, next);
    if (total==0)
        return 0;
    return next;
}

int select_line_from_file_w(char *line_of_text, char * path);
int select_line_from_file(char *line_of_text, char * path);

int select_location(char *filename, char * path)
{
    return select_line_from_file(filename, path);
}


int file_is_open_line_from_file=0;
int max_line_from_file=0;
FILE* file_from_file;
char naam_from_file[1000]="";

int select_line_from_file(char *line_of_text, char * path)
{
    char line[4000]="";
    if (file_is_open_line_from_file==1 && strcmp(path,naam_from_file)==0)
    {
    } else {
        if (file_is_open_line_from_file==1) fclose(file_from_file);
        sprintf(naam_from_file,"%s",path);
        file_from_file = fopen (naam_from_file, "r");
        max_line_from_file=0;
        file_is_open_line_from_file=1;
    }

    if (file_from_file==NULL)
    {
        sprintf(error_msg,"ERROR: FILE NOT FOUND: %s",naam_from_file);
        error_flag=2;
        strcpy(line_of_text,error_msg2);
        max_line_from_file=0;
        file_is_open_line_from_file=0;
        return (-1);
    }

    if (fgets (line,4000, file_from_file)!=NULL )
    {
        max_line_from_file++;
    } else {
        fclose(file_from_file);
        max_line_from_file=0;
        file_is_open_line_from_file=0;
        return (-1);
    }
    if (max_line_from_file==0)
    {
        sprintf(error_msg,"WARNING: FILE %s IS EMPTY",naam_from_file);
        error_flag=2;
        strcpy(line_of_text,error_msg);
        file_is_open_line_from_file=0;
        max_line_from_file=0;
        fclose (file_from_file);
        return(-1);
    }
    strcpy(line_of_text,line);
    if (line_of_text[strlen(line_of_text)-1]=='\r' || line_of_text[strlen(line_of_text)-1]=='\n')
        line_of_text[strlen(line_of_text)-1]='\0';

    sprintf(error_msg,"LINE %d SELECTED FROM %s: %.100s",max_line_from_file,naam_from_file,line_of_text);
    error_flag=1;
    return (max_line_from_file);
}

int next_textfile=0;
int total_textfile=0;
int start_textfile=1;
int select_textfile(char *filename, char * path)
{
    if (next_textfile==total_textfile && start_textfile==0) {
        next_textfile=0;
        total_textfile=0;
        start_textfile=1;
        return -1;
    }
    start_textfile=0;
    next_textfile++;
    total_textfile=select_from_list(filename, path, next_textfile);
    if (total_textfile==0)
        return 0;
    return next_textfile;
}

int select_nextline(char *line_of_text, char * path)
{
    return select_line_from_file(line_of_text, path);
}


extern char FONTDIR[];

int GETFONT(char *naam)
{
    static int next=0;
    static int total=0;
    next++;
    if (next>total)
        next=1;
    total=select_from_list(naam, FONTDIR, next);
    if (total==0)
        return 0;
    return next;
}

extern char PICTUREDIR[];
extern char BLENDINGPICTUREDIR[];

int GETPICTURE(char *naam)
{
    static int next=0;
    static int total=0;
    if (strcmp("RESET",naam)==0) next=0;
    next++;
    if (next>total)
        next=1;
    total=select_from_list(naam, PICTUREDIR, next);
    if (total==0)
        return 0;
    return next;
}

int GET_LAT_LON_FROM_FILE_LIST(char *naam)
{
    static int next=0;
    static int total=0;
    if (strcmp("RESET",naam)==0) next=0;
    next++;
    if (next>total)
        next=1;
    total=select_from_list2(naam, "../LAT_LON/list.txt", next);
    if (total==0)
        return 0;
    return next;
}

int GETSHADER_FRAGMENT(char *naam,int up_down)
{
    static int next=0;
    static int total=0;
    char dir[2000];
    sprintf(dir,"%s/fragment",SHADERDIR);
    if (up_down==-1) {
        if (next>0) next--;
        else next=total;
    }
    else {
        next++;
    }
    if (next>total)
        next=1;
    total=select_from_list(naam, dir, next);
    if (total==0)
        return 0;
    return next;
}

int GETSHADER_VERTEX(char *naam)
{
    static int next=0;
    static int total=0;
    char dir[2000];
    sprintf(dir,"%s/vertex",SHADERDIR);
    next++;
    if (next>total)
        next=1;
    total=select_from_list(naam, dir, next);
    if (total==0)
        return 0;
    return next;
}

int GETSHADER_GEOMETRY(char *naam)
{
    static int next=0;
    static int total=0;
    char dir[2000];
    sprintf(dir,"%s/geometry",SHADERDIR);
    next++;
    if (next>total)
        next=1;
    total=select_from_list(naam, dir, next);
    if (total==0)
        return 0;
    return next;
}

int GETSHADER_BUFFER(char *naam)
{
    static int next=0;
    static int total=0;
    char dir[2000];
    sprintf(dir,"%s/buffer",SHADERDIR);
    next++;
    if (next>total)
        next=1;
    total=select_from_list(naam, dir, next);
    if (total==0)
        return 0;
    return next;
}


int GETBLENDINGPICTURE(char *naam)
{
    static int next=0;
    static int total=0;
    next++;
    if (next>total)
        next=1;
    total=select_from_list(naam, BLENDINGPICTUREDIR, next);
    if (total==0)
        return 0;
    return next;
}

int kut()
{
   FILE * pFile;
   wchar_t mystring [100];

   pFile = fopen ("myfile.txt" , "r");
   if (pFile != NULL)
   {
     if ( fgetws (mystring , 100 , pFile) != NULL )
       fputws ( mystring, stdout );
     fclose (pFile);
   }
   return 0;
}

wchar_t line_w[100000];

int select_line_from_file_w(char * line_of_text, char * path)
{

    if (file_is_open_line_from_file==1 && strcmp(path,naam_from_file)==0)
    {
    } else {
        if (file_is_open_line_from_file==1) fclose(file_from_file);
        sprintf(naam_from_file,"%s",path);
        file_from_file = fopen (naam_from_file, "r");
        max_line_from_file=0;
        file_is_open_line_from_file=1;
    }

    if (file_from_file==NULL)
    {
        sprintf(error_msg,"ERROR: FILE NOT FOUND: %s",naam_from_file);
        error_flag=2;
        strcpy(line_of_text,error_msg);
        max_line_from_file=0;
        file_is_open_line_from_file=0;
        return (-1);
    }

    if (fgetws(line_w,100000, file_from_file)!=NULL )
 //   if (fgets (line_w,mazesizex*2+100, file_from_file)!=NULL )
    {
        strcpy(line_of_text,"ok");
//        printf("select: lot=%s\n",line_w);
        max_line_from_file++;
    } else {
        fclose(file_from_file);
        max_line_from_file=0;
        file_is_open_line_from_file=0;
        return (-1);
    }
    if (max_line_from_file==0)
    {
        sprintf(error_msg,"WARNING: FILE %s IS EMPTY",naam_from_file);
        error_flag=2;
        strcpy(line_of_text,error_msg);
        file_is_open_line_from_file=0;
        max_line_from_file=0;
        fclose (file_from_file);
        return(-1);
    }
    strcpy(line_of_text,line);
    if (line_of_text[strlen(line_of_text)-1]=='\r' || line_of_text[strlen(line_of_text)-1]=='\n')
        line_of_text[strlen(line_of_text)-1]='\0';

    sprintf(error_msg,"LINE %d SELECTED FROM %s: %s",max_line_from_file,naam_from_file,line_of_text);
    error_flag=1;
    return (max_line_from_file);
}

