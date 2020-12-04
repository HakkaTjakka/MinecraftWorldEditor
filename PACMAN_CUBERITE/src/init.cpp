#define SFML_STATIC
#undef UNICODE
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <Windows.h>
#include <dirent.h>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <sfeMovie/Movie.hpp>
#include "StreamSelector.hpp"
#include <stdio.h>
#include <string.h>
extern int SEED;
extern int offset_picture_x;
extern int offset_picture_y;
extern int winmain_running;
int memory_set=0;
extern int read_mazeoff(int nopos);
extern int shade_map;
int maze_plotsizex;
int maze_plotsizey;
void dodirs();
extern double Fget_map_x,Fget_map_y;
extern int get_map_x,get_map_y,get_map_zoom;
extern int 		*pos_ghostx;
extern int 		*pos_ghosty;
extern float 	*fpos_ghostx;
extern float 	*fpos_ghosty;
extern float 	*fspeed_ghostx;
extern float 	*fspeed_ghosty;
extern int 		*check;
extern int level;
extern int force_game;
extern int MULTIPLAYER;
extern int BITMAPSX;
extern int BITMAPSY;
extern int MAXINMEM;
extern int PRELOAD;
extern int MAXGHOSTS;
extern int LOADLAST;
extern int SAVELAST;
extern int MAZEHEIGHT;
extern int MAZEWIDTH;
extern int DONTSAVEFILES;
extern int LOGFILE;
extern char MACRODIR[];
extern char SCRIPTDIR[];
extern char LEVELDIR[];
extern char MAPDIR[];
extern char MOVIEDIR[];
extern char SHADERDIR[];
extern char PICTUREDIR[];
char CONVERTDIR[2000];
extern char URLDIR[];
extern char FONTDIR[];
extern char BLENDINGPICTUREDIR[];
extern char FFMPEGCOMMAND[];
extern int RGBA;
extern char FFMPEGCOMMAND_RGBA[];
extern char FFMPEGCOMMANDIN[];
extern char FFMPEGCOMMANDIN_SUBS[];
extern char FFMPEGCOMMAND_CROP[];
extern char FFMPEGCOMMAND_CROP_RGBA[];
extern char FFMPEGCOMMAND_M_ORIG[];
extern char FFMPEGCOMMAND_M_ORIG_AUDIO[];
extern char FFMPEGCOMMAND_BURN_SUBS[];
extern int PIXELISBLACKTHRESHOLD;
extern int PIXELISWHITETHRESHOLD;
extern int PIXELISCOLORTHRESHOLD;
extern int PIXELISCOLOR_R;
extern int PIXELISCOLOR_G;
extern int PIXELISCOLOR_B;
extern int SAS_STARTX;
extern int SAS_STARTY;
extern int SAS_ZOOM;
extern int SAS_MAX_ZOOM;
extern char SAS_DIR[];
char SUBTITLES[10];
char SUBTITLE_FORMAT[10];
extern int SAS_ZOOM_DIRECTION;
extern char SAS_URL[];
extern char SAS_ORDER[];
char SAS_LAYER[2000];
char EARTH_ROOT1[2000]="";
char EARTH_ROOT2[2000]="";
char EARTH_ROOT3[2000]="";
char MODELS[2000]="";
int MUL_SAS_ZOOM_DIRECTION[50];
int MUL_SAS_MAX_ZOOM[50];
char MUL_SAS_URL[50][2000];
char MUL_SAS_ORDER[50][5];
int MUL_COUNTER=0;
int MUL_MATCH_LEVEL=0;
char MUL_SAS_EXTENSION[50][10];
char MUL_SAS_DIR[50][2000];

extern int MAZEOFF;
extern char SAS_EXTENSION[];

extern char *line;

extern int maxnumber;

extern char **Maze;
//extern char **Maze2;

extern int mazesizex;
extern int mazesizey;

//extern sf::RenderTexture ***totaltexturepointers;

extern int totalpicturex;
extern int totalpicturey;

extern char **used;
extern int **used2;
extern char **changed;
extern char **files;
extern char **files_mazes;

//extern sf::Sprite ***totalspritepointers;

extern int maxpicturex;
extern int maxpicturey;

extern char **maze_plot;

void cleanupmem();
void frexit(int err_no);
extern void logfile(char *line);
extern void ShowTaskBar(bool show);
extern void savedata(char *naam, int data);
int reload_init();

#include <iostream>
#include <fstream>

std::filebuf buf ;
std::streambuf* oldbuf;

int handle_init() {
	FILE * file;
	char var[300];
    char line2[2000];
	int numread=0;
   	int msgboxID;

//    buf.open( "stdout.txt", std::ios::err ) ;
//    buf.open( "stdout.txt", std::ios::out ) ;
//    buf.open( "stdout.txt", std::ios::stderr ) ;
//    oldbuf = std::cout.rdbuf( &buf ) ;
//  std::cout << "to file" << std::endl ;


    reload_init();


	pos_ghostx=		(int*)		calloc(MAXGHOSTS,sizeof(int));		if (pos_ghostx==NULL)		{msgboxID=MessageBox(NULL, "ERROR ALLECATING MEMORY", "ERROR",MB_OK); {cleanupmem();exit(1);} }
	pos_ghosty=		(int*)		calloc(MAXGHOSTS,sizeof(int));		if (pos_ghosty==NULL) 		{msgboxID=MessageBox(NULL, "ERROR ALLECATING MEMORY", "ERROR",MB_OK); {cleanupmem();exit(1);} }
	fpos_ghostx=	(float*)	calloc(MAXGHOSTS,sizeof(float));	if (fpos_ghostx==NULL) 		{msgboxID=MessageBox(NULL, "ERROR ALLECATING MEMORY", "ERROR",MB_OK); {cleanupmem();exit(1);} }
	fpos_ghosty=	(float*)	calloc(MAXGHOSTS,sizeof(float));	if (fpos_ghosty==NULL) 		{msgboxID=MessageBox(NULL, "ERROR ALLECATING MEMORY", "ERROR",MB_OK); {cleanupmem();exit(1);} }
	fspeed_ghostx=	(float*)	calloc(MAXGHOSTS,sizeof(float));	if (fspeed_ghostx==NULL)	{msgboxID=MessageBox(NULL, "ERROR ALLECATING MEMORY", "ERROR",MB_OK); {cleanupmem();exit(1);} }
	fspeed_ghosty=	(float*)	calloc(MAXGHOSTS,sizeof(float));	if (fspeed_ghosty==NULL) 	{msgboxID=MessageBox(NULL, "ERROR ALLECATING MEMORY", "ERROR",MB_OK); {cleanupmem();exit(1);} }
	check=			(int*)		calloc(MAXGHOSTS,sizeof(int));		if (check==NULL) 			{msgboxID=MessageBox(NULL, "ERROR ALLECATING MEMORY", "ERROR",MB_OK); {cleanupmem();exit(1);} }

	mazesizex=BITMAPSX*30*2;
	mazesizey=BITMAPSY*15*2;

    line=		(char*)		calloc(mazesizex+100,sizeof(char));	if (line==NULL)	            	{msgboxID=MessageBox(NULL, "ERROR ALLECATING MEMORY", "ERROR",MB_OK); {cleanupmem();exit(1);} }

    int i;

    Maze  		= (char **)	calloc(mazesizex+16 ,						sizeof(char *)); 	if (Maze==NULL)		{msgboxID=MessageBox(NULL, "ERROR ALLECATING MEMORY", "ERROR",MB_OK); {cleanupmem();exit(1);} }
    Maze[0] 	= (char *)	calloc((mazesizex+16) * (mazesizey+16) ,	sizeof(char));		if (Maze[0]==NULL)	{msgboxID=MessageBox(NULL, "ERROR ALLECATING MEMORY", "ERROR",MB_OK); {cleanupmem();exit(1);} }
    for(i=0; i<mazesizex+16; i++) Maze[i] = (*Maze+(mazesizey+16)*i);

	totalpicturex=BITMAPSX;
	totalpicturey=BITMAPSY;

    used  		= (char **)	calloc(totalpicturex ,					sizeof(char *)); 	if (used==NULL)			{msgboxID=MessageBox(NULL, "ERROR ALLECATING MEMORY", "ERROR",MB_OK); {cleanupmem();exit(1);} }
    used[0] 	= (char *)	calloc(totalpicturex*totalpicturey ,	sizeof(char));		if (used[0]==NULL)		{msgboxID=MessageBox(NULL, "ERROR ALLECATING MEMORY", "ERROR",MB_OK); {cleanupmem();exit(1);} }
    for(i=0; i<totalpicturex; i++) used[i] = (*used+totalpicturey*i);

    used2  		= (int **)	calloc(totalpicturex ,					sizeof(int *)); 	if (used2==NULL)		{msgboxID=MessageBox(NULL, "ERROR ALLECATING MEMORY", "ERROR",MB_OK); {cleanupmem();exit(1);} }
    used2[0] 	= (int  *)	calloc(totalpicturex*totalpicturey ,	sizeof(int));		if (used2[0]==NULL)		{msgboxID=MessageBox(NULL, "ERROR ALLECATING MEMORY", "ERROR",MB_OK); {cleanupmem();exit(1);} }
    for(i=0; i<totalpicturex; i++) used2[i] = (*used2+totalpicturey*i);

    changed  	= (char **)	calloc(totalpicturex ,					sizeof(char *)); 	if (changed==NULL)		{msgboxID=MessageBox(NULL, "ERROR ALLECATING MEMORY", "ERROR",MB_OK); {cleanupmem();exit(1);} }
    changed[0] 	= (char *)	calloc(totalpicturex*totalpicturey ,	sizeof(char));		if (changed[0]==NULL)	{msgboxID=MessageBox(NULL, "ERROR ALLECATING MEMORY", "ERROR",MB_OK); {cleanupmem();exit(1);} }
    for(i=0; i<totalpicturex; i++) changed[i] = (*changed+totalpicturey*i);

    files  		= (char **)	calloc(totalpicturex ,					sizeof(char *)); 	if (files==NULL)		{msgboxID=MessageBox(NULL, "ERROR ALLECATING MEMORY", "ERROR",MB_OK); {cleanupmem();exit(1);} }
    files[0] 	= (char *)	calloc(totalpicturex*totalpicturey ,	sizeof(char));		if (files[0]==NULL)		{msgboxID=MessageBox(NULL, "ERROR ALLECATING MEMORY", "ERROR",MB_OK); {cleanupmem();exit(1);} }
    for(i=0; i<totalpicturex; i++) files[i] = (*files+totalpicturey*i);

    files_mazes     = (char **)	calloc(totalpicturex ,					sizeof(char *)); 	if (files_mazes==NULL)		{msgboxID=MessageBox(NULL, "ERROR ALLECATING MEMORY", "ERROR",MB_OK); {cleanupmem();exit(1);} }
    files_mazes[0] 	= (char *)	calloc(totalpicturex*totalpicturey ,	sizeof(char));		if (files_mazes[0]==NULL)	{msgboxID=MessageBox(NULL, "ERROR ALLECATING MEMORY", "ERROR",MB_OK); {cleanupmem();exit(1);} }
    for(i=0; i<totalpicturex; i++) files_mazes[i] = (*files_mazes+totalpicturey*i);

	maxpicturex=BITMAPSX-1;
	maxpicturey=BITMAPSY-1;

	maze_plotsizex=BITMAPSX*30;
	maze_plotsizey=BITMAPSY*15;

    maze_plot  	= (char **)	calloc(maze_plotsizex ,					sizeof(char *)); 	if (maze_plot==NULL)	{msgboxID=MessageBox(NULL, "ERROR ALLECATING MEMORY", "ERROR",MB_OK); {cleanupmem();exit(1);} }
    maze_plot[0]= (char *)	calloc(maze_plotsizex*maze_plotsizey ,	sizeof(char));		if (maze_plot[0]==NULL)	{msgboxID=MessageBox(NULL, "ERROR ALLECATING MEMORY", "ERROR",MB_OK); {cleanupmem();exit(1);} }
    for(i=0; i<maze_plotsizex; i++) maze_plot[i] = (*maze_plot+maze_plotsizey*i);

	logfile((char*)"Allocating memory done succesfully");
    memory_set=1;

extern int SAS_STARTX_a;
extern int SAS_STARTY_a;
    SAS_STARTX_a=SAS_STARTX*256-(int)((float)(SAS_STARTX*256)/1920.0)*1920;
//    printf("X: tot=%d  /1920=%f\n",SAS_STARTX*256-SAS_STARTX_a,(float)(SAS_STARTX*256-SAS_STARTX_a)/1920.0);
    SAS_STARTY_a=SAS_STARTY*256-(int)((float)(SAS_STARTY*256)/1080.0)*1080;
//    printf("Y: tot=%d  /1080=%f\n",SAS_STARTY*256-SAS_STARTY_a,(float)(SAS_STARTY*256-SAS_STARTY_a)/1080.0);

//    printf("LOADED:\n");
//    printf("SAS:   x=%8d , y=%8d , zoom=%d\n",SAS_STARTX,SAS_STARTY,SAS_ZOOM);
//    printf("ADAPT: x=%8d , y=%8d \n" ,(int)(SAS_STARTX_a/256),(int)(SAS_STARTY_a/256));
//    printf("REST:  x=%8d , y=%8d \n" ,SAS_STARTX_a,SAS_STARTY_a);
//    printf("===========================\n");

    SAS_STARTX=SAS_STARTX-SAS_STARTX_a/256;
    SAS_STARTY=SAS_STARTY-SAS_STARTY_a/256;
    SAS_STARTX_a=SAS_STARTX_a-(int)(SAS_STARTX_a/256)*256;
    SAS_STARTY_a=SAS_STARTY_a-(int)(SAS_STARTY_a/256)*256;

    offset_picture_x=(SAS_STARTX*256-SAS_STARTX_a)/1920;
    offset_picture_y=(SAS_STARTY*256-SAS_STARTY_a)/1080;

//    printf("RECALCULATED:\n");
//    printf("SAS:   x=%8d , y=%8d , zoom=%d\n",SAS_STARTX,SAS_STARTY,SAS_ZOOM);
//    printf("ADAPT: x=%8d , y=%8d \n" ,(int)(SAS_STARTX_a/256),(int)(SAS_STARTY_a/256));
//    printf("REST:  x=%8d , y=%8d \n" ,SAS_STARTX_a,SAS_STARTY_a);

    Fget_map_x=(double)SAS_STARTX;
    Fget_map_y=(double)SAS_STARTY;
    get_map_x=SAS_STARTX;
    get_map_y=SAS_STARTY;
    get_map_zoom=SAS_ZOOM;

    dodirs();

	return 0;
}

int mul=0;

int reload_init() {
	FILE * file;
	char var[300];
	int numread;
   	int msgboxID;
    char line2[2000];
    static int first=1;

    MUL_COUNTER=0;
    MUL_MATCH_LEVEL=0;
	file=fopen("Pacman.ini","r");
	if (file==NULL) {
		return 1;
	} else {
		LOADLAST=1;
		SAVELAST=1;
	   	while( fgets (line2,2000, file)!=NULL ) {
//            printf("line2=%s",line2);
			if (strlen(line2)>0) line2[strlen(line2) - 1] = '\0'; else line2[0]='\0';
			numread=sscanf(line2,"%[^=]",var);
			if (numread>=0) {
				if 		(strcmp(var,"BITMAPSX")==0) 	                numread=sscanf(line2,"BITMAPSX=%d",	                    &BITMAPSX);
				else if (strcmp(var,"BITMAPSY")==0) 	                numread=sscanf(line2,"BITMAPSY=%d",	                    &BITMAPSY);
				else if (strcmp(var,"SEED")==0) 	                    numread=sscanf(line2,"SEED=%d",	                        &SEED);
				else if (strcmp(var,"MAXINMEM")==0) 	                numread=sscanf(line2,"MAXINMEM=%d",	                    &MAXINMEM);
				else if (strcmp(var,"PRELOAD")==0) 		                numread=sscanf(line2,"PRELOAD=%d",	                    &PRELOAD);
				else if (strcmp(var,"MAXGHOSTS")==0) 	                numread=sscanf(line2,"MAXGHOSTS=%d",	                &MAXGHOSTS);
				else if (strcmp(var,"LOADLAST")==0) 	                numread=sscanf(line2,"LOADLAST=%d",	                    &LOADLAST);
				else if (strcmp(var,"SAVELAST")==0) 	                numread=sscanf(line2,"SAVELAST=%d",	                    &SAVELAST);
				else if (strcmp(var,"MAZEWIDTH")==0) 	                numread=sscanf(line2,"MAZEWIDTH=%d",	                &MAZEWIDTH);
				else if (strcmp(var,"MAZEHEIGHT")==0) 	                numread=sscanf(line2,"MAZEHEIGHT=%d",                   &MAZEHEIGHT);
				else if (DONTSAVEFILES!=1 && strcmp(var,"DONTSAVEFILES")==0)                numread=sscanf(line2,"DONTSAVEFILES=%d",                &DONTSAVEFILES);
				else if (strcmp(var,"LOGFILE")==0)                      numread=sscanf(line2,"LOGFILE=%d",                      &LOGFILE);
				else if (strcmp(var,"MOVIEDIR")==0)                     numread=sscanf(line2,"MOVIEDIR=\"%1000[^\"]\"",          MOVIEDIR);
				else if (strcmp(var,"SUBTITLES")==0)                    numread=sscanf(line2,"SUBTITLES=\"%1000[^\"]\"",         SUBTITLES);
				else if (strcmp(var,"SUBTITLE_FORMAT")==0)              numread=sscanf(line2,"SUBTITLE_FORMAT=\"%1000[^\"]\"",   SUBTITLE_FORMAT);
				else if (strcmp(var,"SCRIPTDIR")==0)                    numread=sscanf(line2,"SCRIPTDIR=\"%1000[^\"]\"",         SCRIPTDIR);
				else if (strcmp(var,"MACRODIR")==0)                     numread=sscanf(line2,"MACRODIR=\"%1000[^\"]\"",          MACRODIR);
				else if (strcmp(var,"SHADERDIR")==0)                    numread=sscanf(line2,"SHADERDIR=\"%1000[^\"]\"",         SHADERDIR);
				else if (strcmp(var,"LEVELDIR")==0)                     numread=sscanf(line2,"LEVELDIR=\"%1000[^\"]\"",          LEVELDIR);
				else if (strcmp(var,"MAPDIR")==0)                       numread=sscanf(line2,"MAPDIR=\"%1000[^\"]\"",            MAPDIR);
				else if (strcmp(var,"PICTUREDIR")==0)                   numread=sscanf(line2,"PICTUREDIR=\"%200[^\"]\"",         PICTUREDIR);
				else if (strcmp(var,"CONVERTDIR")==0)                   numread=sscanf(line2,"CONVERTDIR=\"%2000[^\"]\"",        CONVERTDIR);
				else if (strcmp(var,"BLENDINGPICTUREDIR")==0)           numread=sscanf(line2,"BLENDINGPICTUREDIR=\"%1000[^\"]\"",BLENDINGPICTUREDIR);
				else if (strcmp(var,"URLDIR")==0)                       numread=sscanf(line2,"URLDIR=\"%1000[^\"]\"",            URLDIR);
				else if (strcmp(var,"FONTDIR")==0)                      numread=sscanf(line2,"FONTDIR=\"%1000[^\"]\"",           FONTDIR);
				else if (strcmp(var,"FFMPEG")==0)                       numread=sscanf(line2,"FFMPEG=\"%4999[^\"]\"",            FFMPEGCOMMAND);
				else if (strcmp(var,"RGBA")==0) 	                    numread=sscanf(line2,"RGBA=%d",	                        &RGBA);
				else if (strcmp(var,"FFMPEG_RGBA")==0)                  numread=sscanf(line2,"FFMPEG_RGBA=\"%4999[^\"]\"",       FFMPEGCOMMAND_RGBA);
				else if (strcmp(var,"FFMPEG_CROP")==0)                  numread=sscanf(line2,"FFMPEG_CROP=\"%4999[^\"]\"",       FFMPEGCOMMAND_CROP);
				else if (strcmp(var,"FFMPEG_CROP_RGBA")==0)             numread=sscanf(line2,"FFMPEG_CROP_RGBA=\"%4999[^\"]\"",  FFMPEGCOMMAND_CROP_RGBA);
				else if (strcmp(var,"FFMPEG_IN")==0)                    numread=sscanf(line2,"FFMPEG_IN=\"%4999[^\"]\"",         FFMPEGCOMMANDIN);
				else if (strcmp(var,"FFMPEG_IN_SUBS")==0)               numread=sscanf(line2,"FFMPEG_IN_SUBS=\"%4999[^\"]\"",    FFMPEGCOMMANDIN_SUBS);
				else if (strcmp(var,"FFMPEG_BURN_SUBS")==0)             numread=sscanf(line2,"FFMPEG_BURN_SUBS=\"%4999[^\"]\"",  FFMPEGCOMMAND_BURN_SUBS);
				else if (strcmp(var,"FFMPEG_M_ORIG")==0)                numread=sscanf(line2,"FFMPEG_M_ORIG=\"%4999[^\"]\"",     FFMPEGCOMMAND_M_ORIG);
				else if (strcmp(var,"FFMPEG_M_ORIG_AUDIO")==0)          numread=sscanf(line2,"FFMPEG_M_ORIG_AUDIO=\"%4999[^\"]\"",FFMPEGCOMMAND_M_ORIG_AUDIO);
				else if (strcmp(var,"PIXELISBLACKTHRESHOLD")==0)        numread=sscanf(line2,"PIXELISBLACKTHRESHOLD=%d",        &PIXELISBLACKTHRESHOLD);
				else if (strcmp(var,"PIXELISWHITETHRESHOLD")==0)        numread=sscanf(line2,"PIXELISWHITETHRESHOLD=%d",        &PIXELISWHITETHRESHOLD);
				else if (strcmp(var,"PIXELISCOLORTHRESHOLD")==0)        numread=sscanf(line2,"PIXELISCOLORTHRESHOLD=%d",        &PIXELISCOLORTHRESHOLD);
				else if (strcmp(var,"PIXELISCOLOR_R")==0)               numread=sscanf(line2,"PIXELISCOLOR_R=%d",               &PIXELISCOLOR_R);
				else if (strcmp(var,"PIXELISCOLOR_G")==0)               numread=sscanf(line2,"PIXELISCOLOR_G=%d",               &PIXELISCOLOR_G);
				else if (strcmp(var,"PIXELISCOLOR_B")==0)               numread=sscanf(line2,"PIXELISCOLOR_B=%d",               &PIXELISCOLOR_B);
				else if (strcmp(var,"SAS_STARTX")==0)                   numread=sscanf(line2,"SAS_STARTX=%d",                   &SAS_STARTX);
				else if (strcmp(var,"SAS_STARTY")==0)                   numread=sscanf(line2,"SAS_STARTY=%d",                   &SAS_STARTY);
				else if (strcmp(var,"SAS_ZOOM")==0)                     numread=sscanf(line2,"SAS_ZOOM=%d",                     &SAS_ZOOM);
				else if (strcmp(var,"SAS_ZOOM_DIRECTION")==0) {
                    numread=sscanf(line2,"SAS_ZOOM_DIRECTION=%d",           &SAS_ZOOM_DIRECTION);
                    MUL_SAS_ZOOM_DIRECTION[MUL_COUNTER]=SAS_ZOOM_DIRECTION;
				}
				else if (strcmp(var,"SAS_DIR")==0) {
                    numread=sscanf(line2,"SAS_DIR=\"%1999[^\"]\"",          SAS_DIR);
                    strcpy(MUL_SAS_DIR[MUL_COUNTER],SAS_DIR);
				}
				else if (strcmp(var,"SAS_LAYER")==0)                    numread=sscanf(line2,"SAS_LAYER=\"%1999[^\"]\"",        SAS_LAYER);
				else if (strcmp(var,"SAS_URL")==0) {
                    numread=sscanf(line2,"SAS_URL=\"%1999[^\"]\"",          SAS_URL);
                    strcpy(MUL_SAS_URL[MUL_COUNTER],SAS_URL);
				}
				else if (strcmp(var,"SAS_ORDER")==0) {
                    numread=sscanf(line2,"SAS_ORDER=\"%9[^\"]\"",           SAS_ORDER);
                    strcpy(MUL_SAS_ORDER[MUL_COUNTER],SAS_ORDER);
				}
				else if (strcmp(var,"SAS_EXTENSION")==0) {
                    numread=sscanf(line2,"SAS_EXTENSION=\"%20[^\"]\"",      SAS_EXTENSION);
                    strcpy(MUL_SAS_EXTENSION[MUL_COUNTER],SAS_EXTENSION);
				}
				else if (strcmp(var,"SAS_MAX_ZOOM")==0) {
                    numread=sscanf(line2,"SAS_MAX_ZOOM=%d",                 &SAS_MAX_ZOOM);
                    MUL_SAS_MAX_ZOOM[MUL_COUNTER]=SAS_MAX_ZOOM;
                    MUL_COUNTER++;
//                    printf("level=%d SAS_MAX_ZOOM=%d URL=%s\n",level,SAS_MAX_ZOOM,SAS_URL);
                    if (SAS_MAX_ZOOM>=level) MUL_MATCH_LEVEL++;
				}
				else if (strcmp(var,"MAZEOFF")==0)                      numread=sscanf(line2,"MAZEOFF=%d",                      &MAZEOFF);
				else if (strcmp(var,"MULTIPLAYER")==0)                  numread=sscanf(line2,"MULTIPLAYER=%d",                  &MULTIPLAYER);
				else if (strcmp(var,"EARTH_ROOT1")==0)                  numread=sscanf(line2,"EARTH_ROOT1=\"%1999[^\"]\"",      &EARTH_ROOT1);
				else if (strcmp(var,"EARTH_ROOT2")==0)                  numread=sscanf(line2,"EARTH_ROOT2=\"%1999[^\"]\"",      &EARTH_ROOT2);
				else if (strcmp(var,"EARTH_ROOT3")==0)                  numread=sscanf(line2,"EARTH_ROOT3=\"%1999[^\"]\"",      &EARTH_ROOT3);
				else if (strcmp(var,"MODELS")==0)                       numread=sscanf(line2,"MODELS=\"%1999[^\"]\"",           &MODELS);
				else {
                    if (first==1) {
                        if (strcmp(var,"FORCE_GAME")==0)                   numread=sscanf(line2,"FORCE_GAME=%d",                   &force_game);
                    }
				}
			}
	   	}
		fclose(file);
		if (BITMAPSX<2) 					 			{msgboxID=MessageBox(NULL, "BITMAPSX NOT FOUND OR <2\nDEFAULTING TO BITMAPSX=4", 						"ERROR",MB_OKCANCEL); if (msgboxID == IDCANCEL) {cleanupmem();exit(1);} else BITMAPSX=4;}
		if (BITMAPSY<2)  								{msgboxID=MessageBox(NULL, "BITMAPSY NOT FOUND OR <2\nDEFAULTING TO BITMAPSY=4", 						"ERROR",MB_OKCANCEL); if (msgboxID == IDCANCEL) {cleanupmem();exit(1);} else BITMAPSY=4;}
		if (MAXINMEM<10) 								{msgboxID=MessageBox(NULL, "MAXINMEM NOT FOUND OR <16\nDEFAULTING TO MAXINMEM=64",			 			"ERROR",MB_OKCANCEL); if (msgboxID == IDCANCEL) {cleanupmem();exit(1);} else MAXINMEM=64;}
		if (MAXINMEM>1000) 								{msgboxID=MessageBox(NULL, "MAXINMEM NOT FOUND OR <16 OR>780\nDEFAULTING TO MAXINMEM=76",	 			"ERROR",MB_OKCANCEL); if (msgboxID == IDCANCEL) {cleanupmem();exit(1);} else MAXINMEM=76;}
		if (PRELOAD<0 || PRELOAD>1) 					{msgboxID=MessageBox(NULL, "PRELOAD <0 OR >1 OR NOT FOUND\nMUST BE 0 OR 1\nDEFAULTING TO 0", 			"ERROR",MB_OKCANCEL); if (msgboxID == IDCANCEL) {cleanupmem();exit(1);} else PRELOAD=0;}
		if (MAXGHOSTS<4) 								{msgboxID=MessageBox(NULL, "MAXGHOSTS NOT FOUND OR <4\nDEFAULTING TO MAXGHOSTS=100", 					"ERROR",MB_OKCANCEL); if (msgboxID == IDCANCEL) {cleanupmem();exit(1);} else MAXGHOSTS=100;}
		if (PRELOAD==1 && MAXINMEM<BITMAPSX*BITMAPSY) 	{msgboxID=MessageBox(NULL, "PRELOAD=1 MAXINMEM TO SMALL FOR PRELOAD", 									"ERROR",MB_OKCANCEL); if (msgboxID == IDCANCEL) {cleanupmem();exit(1);} else PRELOAD=0;}
		if (LOADLAST!=0 && LOADLAST!=1)					{msgboxID=MessageBox(NULL, "LOADLAST MUST BE 0 OR 1\nDEFAULTING TO 1 (LOADLAST)", 						"ERROR",MB_OKCANCEL); if (msgboxID == IDCANCEL) {cleanupmem();exit(1);} else LOADLAST=1;}
		if (SAVELAST!=0 && SAVELAST!=1)					{msgboxID=MessageBox(NULL, "SAVELAST MUST BE 0 OR 1\nDEFAULTING TO 1 (SAVELAST)",	 					"ERROR",MB_OKCANCEL); if (msgboxID == IDCANCEL) {cleanupmem();exit(1);} else SAVELAST=1;}
		if (MAZEWIDTH>BITMAPSX*30)						{msgboxID=MessageBox(NULL, "MAZEWIDTH MUST BE 0 FOR RANDOM OR MAX BITMAPSX*30\nDEFAULTING TO 0",		"ERROR",MB_OKCANCEL); if (msgboxID == IDCANCEL) {cleanupmem();exit(1);} else MAZEWIDTH=0;}
		if (MAZEHEIGHT>BITMAPSY*15)						{msgboxID=MessageBox(NULL, "MAZEHEIGHT MUST BE 0 FOR RANDOM OR MAX BITMAPSY*15\nDEFAULTING TO 0",		"ERROR",MB_OKCANCEL); if (msgboxID == IDCANCEL) {cleanupmem();exit(1);} else MAZEHEIGHT=0;}
	}

	maxnumber=MAXGHOSTS;
//moved up (../) otherwise codeblocks searches directories when editing and hangs long time.... :(
    if (strcmp(LEVELDIR,"")==0)             strcpy(LEVELDIR,            "../levels");
    if (strcmp(MOVIEDIR,"")==0)             strcpy(MOVIEDIR,            "../movies");
    if (strcmp(SCRIPTDIR,"")==0)            strcpy(SCRIPTDIR,           "../scripts");
    if (strcmp(MACRODIR,"")==0)             strcpy(MACRODIR,            "../macros");
    if (strcmp(MAPDIR,"")==0)               strcpy(MAPDIR,              "../map_pictures");
    if (strcmp(PICTUREDIR,"")==0)           strcpy(PICTUREDIR,          "../pictures");
    if (strcmp(BLENDINGPICTUREDIR,"")==0)   strcpy(BLENDINGPICTUREDIR,  "../blendingpictures");
    if (strcmp(URLDIR,"")==0)               strcpy(URLDIR,              "../url");
    if (strcmp(FONTDIR,"")==0)              strcpy(FONTDIR,             "../fonts");
    if (strcmp(SHADERDIR,"")==0)            strcpy(SHADERDIR,           "../shaders");
    if (strcmp(SAS_ORDER,"")==0)            strcpy(SAS_ORDER,           "XYZ");

//SAS_URL="http://khms3.google.com/kh/v=815&src=app&x=%d&y=%d&z=%d&s=Galileo"
//SAS_ZOOM_DIRECTION=0
//SAS_ORDER="XYZ"
/*
    extern sf::RenderTexture *texturemaxinmem;
    extern sf::RenderTexture **texturemaxinmempoint;
    extern int *used_maxinmem;
    extern sf::Sprite **spritemaxinmempoint;

    if (texturemaxinmem==NULL) texturemaxinmem = new sf::RenderTexture [MAXINMEM];
    if (texturemaxinmempoint==NULL) texturemaxinmempoint = new sf::RenderTexture* [MAXINMEM];
    if (used_maxinmem==NULL) used_maxinmem = new int [MAXINMEM];
    if (spritemaxinmempoint==NULL) spritemaxinmempoint = new sf::Sprite* [MAXINMEM];
*/
    if (mul<MUL_COUNTER) {
        strcpy(SAS_URL,MUL_SAS_URL[mul]);
        strcpy(SAS_DIR,MUL_SAS_DIR[mul]);
        strcpy(SAS_ORDER,MUL_SAS_ORDER[mul]);
        SAS_ZOOM_DIRECTION=MUL_SAS_ZOOM_DIRECTION[mul];
        SAS_MAX_ZOOM=MUL_SAS_MAX_ZOOM[mul];
        strcpy(SAS_EXTENSION,MUL_SAS_EXTENSION[mul]);
    } else {
        mul=0;
    }
//    printf("SAS_URL=%s\n",SAS_URL);
    char ip[200];
    char page[200];
    if (SAS_URL[0]>='0' && SAS_URL[0]<='9') {
        int dummy;
        if (toupper(SAS_URL[5])=='S') sscanf(SAS_URL, "%dhttps://%199[^/]/%199[^\n]",&dummy, ip,page );
        else sscanf(SAS_URL, "%dhttp://%199[^/]/%199[^\n]",&dummy, ip,page);
        if (shade_map>=1) sprintf(LEVELDIR,"%s/%s-%d",MAPDIR,ip,dummy);
    } else {
        if (toupper(SAS_URL[4])=='S') sscanf(SAS_URL, "https://%199[^/]/%199[^\n]", ip,page );
        else sscanf(SAS_URL, "http://%199[^/]/%199[^\n]", ip,page);
        if (shade_map>=1) sprintf(LEVELDIR,"%s/%s",MAPDIR,ip);
    }
    if (shade_map>=1) {
        // reload map position if they are there. Otherwise map positions get messed up.
        read_mazeoff(1);
    }
//    printf("SAS_LAYER=%s\n",SAS_LAYER);
//    printf("       ip=%s\n",ip);
    if (strcmp(SAS_LAYER,ip)==0) {
//        printf("same\n");
        strcpy(SAS_LAYER,"\0");
    }
    dodirs();
    first=0;
	return 0;
}

#define freep(x) if (x!=NULL) free(x);
extern sf::RenderWindow SFMLView1;
extern void terminate_monitor();
extern void terminate_animator();
extern void terminate_background_blitter();
extern void terminate_set_monimem_terminator();
extern void terminate_thread();
extern int  go_on;

extern FILE *pipein;
extern int movieextern;

void frexit(int err_no) {
//    std::cout.rdbuf( oldbuf ) ;
    terminate_monitor();
//    SFMLView1.close();
    ShowTaskBar(true);
//    printf("Press ENTER key to Continue\n");
//    getchar();
    if (memory_set==1) {
//        cleanupmem();
        memory_set=0;
    }
    winmain_running=0;
    sf::sleep(sf::milliseconds(100));
    terminate_monitor();
//    terminate_animator();
    terminate_background_blitter();
    terminate_set_monimem_terminator();
    terminate_thread();
    if (movieextern==0)
        pclose(pipein);

    printf("Main thread waiting to get terminated\n");
//	getchar();
//	exit(err_no);
    go_on=0;
    return;
}


extern void stopmovie();
extern void stopmovie2();

extern sfe::Movie *live_movie;
extern StreamSelector *live_selector;

extern sfe::Movie *live_movie2;
extern StreamSelector *live_selector2;

extern sf::Texture texture_from_movie_new;
extern sf::Texture texture_from_movie2_new;

extern sf::Sprite **spritemaxinmempoint;
extern sf::Sprite *sprite_buffer;

void cleanupmem() {
	freep(line);
	freep(pos_ghostx);
	freep(pos_ghosty);
	freep(fpos_ghostx);
	freep(fpos_ghosty);
	freep(fspeed_ghostx);
	freep(fspeed_ghosty);
	freep(check);
    freep(Maze[0]);
    freep(Maze);
    freep(used[0]);
   	freep(used);
    freep(used[0]);
   	freep(used2);
    freep(changed[0]);
   	freep(changed);
    freep(files[0]);
    freep(files);
    freep(files_mazes[0]);
    freep(files_mazes);
    freep(maze_plot[0]);
    freep(maze_plot);

    for (int xx=0; xx<MAXINMEM+12; xx++)
    {
        if (spritemaxinmempoint[xx]!=NULL) delete spritemaxinmempoint[xx];
        spritemaxinmempoint[xx]=NULL;

    }
    if (sprite_buffer!=NULL) delete sprite_buffer;
    sprite_buffer=NULL;
    if (live_movie!=NULL) stopmovie();
    if (live_movie2!=NULL) stopmovie2();
    memory_set=0;
}


int replace_str(char *str, char *orig, char *rep)
{
//    char buffer[strlen(str)+2000];
    static char buffer[2000];
    char *p;
    if(!(p = strstr(str, orig)))  // Is 'orig' even in 'str'?
        return false;
    strncpy(buffer, str, p-str); // Copy characters from 'str' start to 'orig' st$
    buffer[p-str] = '\0';
    sprintf(buffer+(p-str), "%s%s", rep, p+strlen(orig));
    strcpy(str,buffer);
    return true;
}

void dodirs() {
	char dirname[1000];
	char err[1000];
	DIR* dir;
   	int msgboxID;

//   	char test[200]="maindir/subdir1/subdir2";
//   	while (replace_str(test,"/","\\\\"));
//   	printf(test);printf("\n");

	dir = opendir("..\\convert");
	if (!dir)
	{
		mkdir("..\\convert");
		dir = opendir("..\\convert");
		if (!dir) { sprintf(err,"4 CANNOT CREATE DIRECTORY %s","..\\convert"); msgboxID=MessageBox(NULL, err , "ERROR",MB_OK); frexit(1); }
	    if (dir) closedir(dir);
	} else closedir(dir);

	dir = opendir("..\\convert\\files");
	if (!dir)
	{
		mkdir("..\\convert\\files");
		dir = opendir("..\\convert\\files");
		if (!dir) { sprintf(err,"5 CANNOT CREATE DIRECTORY %s","..\\convert\\files"); msgboxID=MessageBox(NULL, err , "ERROR",MB_OK); frexit(1); }
	    if (dir) closedir(dir);
	} else closedir(dir);

	dir = opendir("..\\convert\\converted");
	if (!dir)
	{
		mkdir("..\\convert\\converted");
		dir = opendir("..\\convert\\converted");
		if (!dir) { sprintf(err,"6 CANNOT CREATE DIRECTORY %s","..\\convert\\converted"); msgboxID=MessageBox(NULL, err , "ERROR",MB_OK); frexit(1); }
	    if (dir) closedir(dir);
	} else closedir(dir);

	dir = opendir("..\\convert\\files\\out");
	if (!dir)
	{
		mkdir("..\\convert\\files\\out");
		dir = opendir("..\\convert\\files\\out");
		if (!dir) { sprintf(err,"7 CANNOT CREATE DIRECTORY %s","..\\convert\\files\\out"); msgboxID=MessageBox(NULL, err , "ERROR",MB_OK); frexit(1); }
	    if (dir) closedir(dir);
	} else closedir(dir);


//	strcpy(dirname,"..\\map_pictures");
    strcpy(dirname,MAPDIR);
   	while (replace_str(dirname,"/","\\\\"));
	dir = opendir(dirname);
	if (!dir)
	{
		mkdir(dirname);
		dir = opendir(dirname);
		if (!dir) { sprintf(err,"8 CANNOT CREATE DIRECTORY %s",dirname); msgboxID=MessageBox(NULL, err , dirname,MB_OK); frexit(1); }
	    if (dir) closedir(dir);
	} else closedir(dir);

    char ip[200];
    char page[200];
    if (SAS_URL[0]>='0' && SAS_URL[0]<='9') {
        int dummy;
        if (toupper(SAS_URL[5])=='S') sscanf(SAS_URL, "%dhttps://%199[^/]/%199[^\n]",&dummy, ip,page );
        else sscanf(SAS_URL, "%dhttp://%199[^/]/%199[^\n]",&dummy, ip,page);
        sprintf(page,"\\%s-%d",ip,dummy);
    } else {
        if (toupper(SAS_URL[4])=='S') sscanf(SAS_URL, "https://%199[^/]/%199[^\n]", ip,page );
        else sscanf(SAS_URL, "http://%199[^/]/%199[^\n]", ip,page);
        sprintf(page,"\\%s",ip);
    }
    strcat(dirname,page);
	dir = opendir(dirname);
	if (!dir)
	{
		mkdir(dirname);
		dir = opendir(dirname);
		if (!dir) { sprintf(err,"9 CANNOT CREATE DIRECTORY %s",dirname); msgboxID=MessageBox(NULL, err , "ERROR",MB_OK); frexit(1); }
	    if (dir) closedir(dir);
	} else closedir(dir);


//	strcpy(dirname,"..\\levels");
    strcpy(dirname,LEVELDIR);
   	while (replace_str(dirname,"/","\\\\"));
	dir = opendir(dirname);
	if (!dir)
	{
		mkdir(dirname);
		dir = opendir(dirname);
		if (!dir) { sprintf(err,"10 CANNOT CREATE DIRECTORY %s",dirname); msgboxID=MessageBox(NULL, err , "ERROR",MB_OK); frexit(1); }
	    if (dir) closedir(dir);
	} else closedir(dir);


//    sprintf(dirname,"..\\levels\\%dx%d",BITMAPSX,BITMAPSY);
    sprintf(dirname,"%s\\%dx%d",LEVELDIR,BITMAPSX,BITMAPSY);
   	while (replace_str(dirname,"/","\\\\"));
    dir = opendir(dirname);
    if (!dir){
		mkdir(dirname);
		dir = opendir(dirname);
		if (!dir) { sprintf(err,"11 CANNOT CREATE DIRECTORY %s",dirname); msgboxID=MessageBox(NULL, err , "ERROR",MB_OK); frexit(1); }
	    if (dir) closedir(dir);
	} else closedir(dir);


//	strcpy(dirname,"..\\movies");
    strcpy(dirname,MOVIEDIR);
   	while (replace_str(dirname,"/","\\\\"));
  	dir = opendir(dirname);
	if (!dir)
	{
		mkdir(dirname);
		dir = opendir(dirname);
		if (!dir) { sprintf(err,"12 CANNOT CREATE DIRECTORY %s",dirname); msgboxID=MessageBox(NULL, err , "ERROR",MB_OK); frexit(1); }
	    if (dir) closedir(dir);
	} else closedir(dir);

    strcpy(dirname,SCRIPTDIR);
   	while (replace_str(dirname,"/","\\\\"));
  	dir = opendir(dirname);
	if (!dir)
	{
		mkdir(dirname);
		dir = opendir(dirname);
		if (!dir) { sprintf(err,"13 CANNOT CREATE DIRECTORY %s",dirname); msgboxID=MessageBox(NULL, err , "ERROR",MB_OK); frexit(1); }
	    if (dir) closedir(dir);
	} else closedir(dir);

    strcpy(dirname,MACRODIR);
   	while (replace_str(dirname,"/","\\\\"));
  	dir = opendir(dirname);
	if (!dir)
	{
		mkdir(dirname);
		dir = opendir(dirname);
		if (!dir) { sprintf(err,"14 CANNOT CREATE DIRECTORY %s",dirname); msgboxID=MessageBox(NULL, err , "ERROR",MB_OK); frexit(1); }
	    if (dir) closedir(dir);
	} else closedir(dir);

	strcpy(dirname,"..\\record");
	dir = opendir(dirname);
	if (!dir)
	{
		mkdir(dirname);
		dir = opendir(dirname);
		if (!dir) { sprintf(err,"15 CANNOT CREATE DIRECTORY %s",dirname); msgboxID=MessageBox(NULL, err , "ERROR",MB_OK); frexit(1); }
	    if (dir) closedir(dir);
	} else closedir(dir);


//	strcpy(dirname,"..\\pictures");
    strcpy(dirname,PICTUREDIR);
   	while (replace_str(dirname,"/","\\\\"));
	dir = opendir(dirname);
	if (!dir)
	{
		mkdir(dirname);
		dir = opendir(dirname);
		if (!dir) { sprintf(err,"16 CANNOT CREATE DIRECTORY %s",dirname); msgboxID=MessageBox(NULL, err , "ERROR",MB_OK); frexit(1); }
	    if (dir) closedir(dir);
	} else closedir(dir);

    strcpy(dirname,BLENDINGPICTUREDIR);
   	while (replace_str(dirname,"/","\\\\"));
	dir = opendir(dirname);
	if (!dir)
	{
		mkdir(dirname);
		dir = opendir(dirname);
		if (!dir) { sprintf(err,"1 CANNOT CREATE DIRECTORY %s",dirname); msgboxID=MessageBox(NULL, err , "ERROR",MB_OK); frexit(1); }
	    if (dir) closedir(dir);
	} else closedir(dir);


    strcpy(dirname,URLDIR);
   	while (replace_str(dirname,"/","\\\\"));
	dir = opendir(dirname);
	if (!dir)
	{
		mkdir(dirname);
		dir = opendir(dirname);
		if (!dir) { sprintf(err,"2 CANNOT CREATE DIRECTORY %s",dirname); msgboxID=MessageBox(NULL, err , "ERROR",MB_OK); frexit(1); }
	    if (dir) closedir(dir);
	} else closedir(dir);

	strcpy(dirname,FONTDIR);
   	while (replace_str(dirname,"/","\\\\"));
	dir = opendir(dirname);
	if (!dir)
	{
		mkdir(dirname);
		dir = opendir(dirname);
		if (!dir) { sprintf(err,"3 CANNOT CREATE DIRECTORY %s",dirname); msgboxID=MessageBox(NULL, err , "ERROR",MB_OK); frexit(1); }
	    if (dir) closedir(dir);
	} else closedir(dir);

/*
	strcpy(dirname,"pictures");
	dir = opendir(dirname);
	if (!dir)
	{
		mkdir(dirname);
		dir = opendir(dirname);
		if (!dir) { sprintf(err,"CANNOT CREATE DIRECTORY %s",dirname); msgboxID=MessageBox(NULL, err , "ERROR",MB_OK); frexit(1); }
	    if (dir) closedir(dir);
	} else closedir(dir);
*/
}
