#include "everything.hpp"

void render_to_rel_pos();
double ddp=0.0;

void adapt_speed() {
    static int tell=0;
    double set_fspeedx,set_fspeedy;
    double alpha;
    pacman_to_rel_pos();
    render_to_rel_pos();
    if (rel_pos_in_map_y2-rel_pos_in_map_y==0.0) {
        if (rel_pos_in_map_x2>=rel_pos_in_map_x) set_fspeedx=-1.0;
        else set_fspeedx=1.0;
        set_fspeedy=0.0;
    } else {
        alpha=atan2((rel_pos_in_map_x2-rel_pos_in_map_x),(rel_pos_in_map_y2-rel_pos_in_map_y));
        set_fspeedx=-sin(alpha)*1.0;
        set_fspeedy=-cos(alpha)*1.0;
    }

    double dp;
    dp=sqrt((rel_pos_in_map_x1-rel_pos_in_map_x)*(rel_pos_in_map_x1-rel_pos_in_map_x)+(rel_pos_in_map_y1-rel_pos_in_map_y)*(rel_pos_in_map_y1-rel_pos_in_map_y));
    double dpt;
    if (sqrt((rel_pos_in_map_x2-rel_pos_in_map_x1)*(rel_pos_in_map_x2-rel_pos_in_map_x1)+(rel_pos_in_map_y2-rel_pos_in_map_y1)*(rel_pos_in_map_y2-rel_pos_in_map_y1))!=0.0) {
        dpt=sqrt((rel_pos_in_map_x2-rel_pos_in_map_x1)*(rel_pos_in_map_x2-rel_pos_in_map_x1)+(rel_pos_in_map_y2-rel_pos_in_map_y1)*(rel_pos_in_map_y2-rel_pos_in_map_y1));
        ddp=dp/dpt;
    }
    double accel=hold/((double)(sprite_from_canvas.getScale().x)*pow(2.0,level));

/*
    printf("a=%f IN=%d OUT=%d scl=%f lvl=%d hld=%f hlc_clc=%f hld_lvl=%d dp=%12.11f ddp=%f dpt=%12.11f rx=%12.11f ry=%12.11f r1x=%f r1y=%f r2x=%f r2y=%f spx=%f spy=%f ac=%f\n",
           alpha,
           DO_ZOOM_IN,DO_ZOOM_OUT,
           sprite_from_canvas.getScale().x,
           level,
           hold,
           (double)(sprite_from_canvas.getScale().x)*pow(2.0,level),
           hold_level,dp,ddp,dpt,
           rel_pos_in_map_x,rel_pos_in_map_y,
           rel_pos_in_map_x1,rel_pos_in_map_y1,
           rel_pos_in_map_x2,rel_pos_in_map_y2,
           set_fspeedx,set_fspeedy,accel
           );
*/
//    ddp_loop=ddp_loop+0.001/(1.0+dpt*100.0);
    double adapt_scale;
    if (ddp>1.0) ddp=1.0;
    if ((DO_ZOOM_IN || DO_ZOOM_OUT) && ddp>=0.0 && ddp<=1.0) {
        adapt_scale=sprite_from_canvas.getScale().x/(1.0+sin(ddp*PI+PI/2.0)/(40.0-dpt*20.0));
//        adapt_scale=sprite_from_canvas.getScale().x/(1.0+(1.0-cos(ddp*PI*2.0))*sin(ddp_slow*PI+PI/2.0)/(300.0-dpt*150.0));
    } else {
        adapt_scale=sprite_from_canvas.getScale().x;
//        printf("adapt_speed(): no zoom or ddp<0.0 or ddp>1.0\n");
    }

    scale_slow=(scale_slow*10.0+adapt_scale)/11.0;
    sprite_from_canvas.setScale(scale_slow,scale_slow);
//    sprite_from_canvas.setScale(adapt_scale,adapt_scale);

//    printf("new_scale=%10.7f ddp=%29.28lf\n",adapt_scale,ddp);
    if (ddp>0.50 && DO_ZOOM_OUT==1) {
        playsound=playsound|1;
        DO_ZOOM_OUT=0;
        DO_ZOOM_IN=1;
    } else {
        if (ddp<=0.50 && DO_ZOOM_OUT==0) {
            DO_ZOOM_OUT=1;
            playsound=playsound|2;
        }
    }
//        printf("adapt_speed(): do nothing\n");
//    }


//    if (ddp<0.99) {
//        double beta=ddp*PI;
//        set_fspeedx=set_fspeedx*(cos(beta));
//        set_fspeedy=set_fspeedy*(cos(beta));
//    } else {
//        set_fspeedx=set_fspeedx*(cos(100.0*(ddp-0.99)*PI)+1.0)/2.0;
//        set_fspeedy=set_fspeedy*(cos(100.0*(ddp-0.99)*PI)+1.0)/2.0;
//        speed_slowx=speed_slowx*(cos(100.0*(ddp-0.99)*PI)+1.0)/2.0;
//        speed_slowy=speed_slowy*(cos(100.0*(ddp-0.99)*PI)+1.0)/2.0;
//    }


    if (plot_all) {
        set_fspeedx=(set_fspeedx/sprite_from_canvas.getScale().x)*(sin(ddp*PI)+0.2);
        set_fspeedy=(set_fspeedy/sprite_from_canvas.getScale().x)*(sin(ddp*PI)+0.2);
    } else {
        set_fspeedx=(set_fspeedx)*4.0;
        set_fspeedy=(set_fspeedy)*4.0;
    }

    static int cnt=0;
    if (DO_ZOOM_OUT==0 && DO_ZOOM_IN==0) {
        cnt++;
    } else cnt==0;
    if ((ddp>0.99 || tell>0 || cnt>300) && DO_ZOOM_IN==0 && DO_ZOOM_OUT==0) {
        tell++;
//        printf("tell=%d\n",tell);
    }
    else tell=0;
    if (((ddp>0.9999 || tell>0) && DO_ZOOM_IN==0) && tell>200 ) {
        scale_slow=0.0;
        speed_slowx=0.0;
        speed_slowy=0.0;
        scale_slow=sprite_from_canvas.getScale().x;
        DO_ADAPT=0;
        set_fspeedx=0.0;
        set_fspeedy=0.0;
        ddp_loop=0.0;
//        forced_jump=1;
//        double rel_x_mem=rel_pos_in_map_x1;
//        double rel_y_mem=rel_pos_in_map_y1;
        rel_pos_in_map_x1=rel_pos_in_map_x2;
        rel_pos_in_map_y1=rel_pos_in_map_y2;
//        rel_pos_in_map_x2=rel_x_mem;
//        rel_pos_in_map_y2=rel_y_mem;
//printf("i am here!!!1\n");
        next_loc();
        DO_ADAPT=1;
        DO_ZOOM_OUT=1;
        DO_ZOOM_IN=0;
        playmusic=1;
//        printf("adapt_speed() next: DO_ZOOM_IN=0 DO_ZOOM_OUT=1\n");
/*
        char loc_str[200];
        if (select_location(loc_str,"locations\\list.txt")>0) {
            rel_pos_in_map_x1=rel_pos_in_map_x2;
            rel_pos_in_map_y1=rel_pos_in_map_y2;
            char str_x[100];
            char str_y[100];
//            sscanf(loc_str,"X=%199[^ ] Y=%199[^\0]",str_x,str_y);
            loc_str[strlen(loc_str)] = '\n';
                sscanf(loc_str,"X=%199[^ ] Y=%199[^\n]",str_x,str_y);
//            sscanf(loc_str,"X=%199[^ ] Y=%199[^\n]",str_x,str_y);
            printf("str_x=%s str_y=%s\n",str_x,str_y);
            rel_pos_in_map_x2=atof(str_x);
            rel_pos_in_map_y2=atof(str_y);
            printf ("string: %s\n",loc_str);
            printf ("atof: X=%29.28lf Y=%29.28lf\n",rel_pos_in_map_x2,rel_pos_in_map_y2);
            DO_ADAPT=1;
            DO_ZOOM_OUT=1;
            DO_ZOOM_IN=0;
            playmusic=1;
        }
*/
    }
    speed_slowx=(speed_slowx*(10+ddp*10)+set_fspeedx)/(11+ddp*10);
    speed_slowy=(speed_slowy*(10+ddp*10)+set_fspeedy)/(11+ddp*10);
    static double jippy=0.0;
    fspeedx=speed_slowx;
    fspeedy=speed_slowy;
    if (ddp>0.99) {
        fspeedx=fspeedx/(1.0+jippy/200.0);
        fspeedy=fspeedy/(1.0+jippy/200.0);
        jippy++;
    } else {
        jippy=0.0;
    }
//    fspeedx=set_fspeedx;
//    fspeedy=set_fspeedy;
//    plot_all_rotate_x=sin(fpstime/122.0)*30;
//    plot_all_rotate_y=sin(fpstime/165.0)*30;
//    plot_all_rotate_z=sin(fpstime/660.0)*520;
}

void pacman_to_rel_pos() {
    double pacx,pacy;
    double pixels_in_map;
    if (follow_ghost==1) {
        pacx=fmod((double)(-fpos_ghostx[follow_ghost_num]+1920+1920/2+maxpixelsx),(double)maxpixelsx);
        pacy=fmod((double)(-fpos_ghosty[follow_ghost_num]+1080+1080/2+maxpixelsy),(double)maxpixelsy);
    } else {
        pacx=fmod((double)(picturex*1920-fposx+1920/2),(double)maxpixelsx);
        pacy=fmod((double)(picturey*1080-fposy+1080/2),(double)maxpixelsy);
    }

    pixels_in_map=256*pow(2.0,(SAS_ZOOM));

    rel_pos_in_map_x=(double)(SAS_STARTX*256 + SAS_STARTX_a + (pacx) )/(double)(pixels_in_map);
    rel_pos_in_map_y=(double)(SAS_STARTY*256 + SAS_STARTY_a + (pacy) )/(double)(pixels_in_map);
}

void render_to_rel_pos() {
    double render_pacx,render_pacy;
    int pixels_in_map;
    pixels_in_map=256*(int)pow(2.0,(SAS_ZOOM));

    render_pacx=(render_picturex*1920-render_posx+1920/2)%maxpixelsx;
    render_pacy=(render_picturey*1080-render_posy+1080/2)%maxpixelsy;
    render_rel_pos_in_map_x=(double)(SAS_STARTX*256 + SAS_STARTX_a + (render_pacx) )/(double)(pixels_in_map);
    render_rel_pos_in_map_y=(double)(SAS_STARTY*256 + SAS_STARTY_a + (render_pacy) )/(double)(pixels_in_map);
//    printf("render: render_rel_pos_in_map_x=%29.28lf render_rel_pos_in_map_y=%29.28lf\n",render_rel_pos_in_map_x,render_rel_pos_in_map_y);
}

void rel_pos_to_pacman() {
    double x,y;
    int pixels_in_map=256*(int)pow(2.0,(SAS_ZOOM));

    x= (rel_pos_in_map_x*(double)(pixels_in_map))-SAS_STARTX*256-SAS_STARTX_a;
    y= (rel_pos_in_map_y*(double)(pixels_in_map))-SAS_STARTY*256-SAS_STARTY_a ;
    if (x<0 || x>=maxpixelsx || y<0 || y>=maxpixelsy) {
        sprintf(error_msg5,"POSITION OUT OF MAP!!!! RELOADING. X=%d,Y=%d",x,y);
        reset_map=1;
        insert_key((WPARAM)'>');
        reset_map=0;
        printf("%s\n",error_msg);
        error_flag5=1;
//        if (x<0) rel_pos_in_map_x=0.0;
//        if (x>=maxpixelsx) rel_pos_in_map_x=1.0;
//        if (y<0) rel_pos_in_map_y=0.0;
//        if (y>=maxpixelsy) rel_pos_in_map_y=1.0;
        x= (rel_pos_in_map_x*(double)(maxpixelsx));
        y= (rel_pos_in_map_y*(double)(maxpixelsy));
    }
    x=x-1920/2;
    y=y-1080/2;

    x=fmod((double)(maxpixelsx+x),(double)maxpixelsx); if (x<0) x=0;
    y=fmod((double)(maxpixelsy+y),(double)maxpixelsy); if (y<0) y=0;

    smooth_x=x;
    smooth_y=y;
    picturex=(int)(x/1920);
    fposx=x-(double)(1920*picturex);
    picturey=(int)(y/1080);
    fposy=y-(double)(1080*picturey);
    fposx=-fposx;
    fposy=-fposy;
    posx=(int)fposx;
    posy=(int)fposy;
    if (follow_ghost==1) {
        fpos_ghostx[follow_ghost_num]=-x+1920;
        fpos_ghosty[follow_ghost_num]=-y+1080;
        pos_ghostx[follow_ghost_num]=fpos_ghostx[follow_ghost_num];
        pos_ghosty[follow_ghost_num]=fpos_ghosty[follow_ghost_num];
    }
}


void next_loc() {
    char loc_str[1000]="";
    char dir_str[10000]="";
    if (select_geodat(dir_str,"../geodata")==0) {
        double tmp;
        tmp=rel_pos_in_map_x1; rel_pos_in_map_x1=rel_pos_in_map_x2; rel_pos_in_map_x2=tmp;
        tmp=rel_pos_in_map_y1; rel_pos_in_map_y1=rel_pos_in_map_y2; rel_pos_in_map_y2=tmp;
        sprintf(going_to,"NO ../geodata dir or list.txt available");
        printf("NO ../geodata dir or list.txt available");
        strcpy(error_msg,going_to);
        error_flag=1;
    }
    static int last=1;
    int now=select_from_list2(loc_str,dir_str,last);
    printf("now=%d last=%d\n",now,last);
    if (now==0) {
        double tmp;
        tmp=rel_pos_in_map_x1; rel_pos_in_map_x1=rel_pos_in_map_x2; rel_pos_in_map_x2=tmp;
        tmp=rel_pos_in_map_y1; rel_pos_in_map_y1=rel_pos_in_map_y2; rel_pos_in_map_y2=tmp;
        sprintf(going_to,"%s DOES NOT EXIST (../geodata/list.txt)",dir_str);
        printf("%s DOES NOT EXIST (../geodata/list.txt)",dir_str);
        strcpy(error_msg,going_to);
        error_flag=1;
    } else {
        if (last<now) last++; else last=1;
//    if (select_from_list2(loc_str,"locations",0)>0) {
//    if (select_location(loc_str,"locations\\cities15000.txt")>0) {
        char str_ar[25][1000]={"","","","","","","","","","","","","","","","","","","","","","","","",""};
        char very_long[10000]="";
//        loc_str[strlen(loc_str)] = '\n';
        int x=0;
        int offset=0;
        int tot=1;
        int len=strlen(loc_str);
        while (x<20 && tot==1)
        {
//            strcpy(str_ar[x],"empty");
            if (loc_str[offset]!="\t"[0]) {
//                if (x==3) {
//                    while (offset<len && loc_str[offset]!='\t') {
//                        offset++;
//                    }
//                    strcpy(very_long,"");
//                    if (offset>=len) tot=0;
//                } else {
                    tot=sscanf(loc_str + offset, "%9999[^\t\n]", very_long);
//                }
            }
            else {
                strcpy(very_long,"");
            }

            if ( tot == 1) {
                offset += strlen(very_long);
//                strcpy(str_ar[x],very_long);
                sprintf(str_ar[x],"%.999s",very_long);
                if (offset<3999) {
                    if (loc_str[offset] != '\0')
                    {
                        ++offset;
                    }
                    x++;
                } else {
                    tot=0;
                }
            }
        }
//        while (x<20)
//        {
//            strcpy(str_ar[x],"empty");
//            x++;
//        }

        printf("str_ar[ 0]=%s\n",str_ar[0]);
        printf("str_ar[ 1]=%s\n",str_ar[1]);
        printf("str_ar[ 2]=%s\n",str_ar[2]);
        printf("str_ar[ 3]=%s\n",str_ar[3]);
        printf("str_ar[ 4]=%s\n",str_ar[4]);
        printf("str_ar[ 5]=%s\n",str_ar[5]);
        printf("str_ar[ 6]=%s\n",str_ar[6]);
        printf("str_ar[ 7]=%s\n",str_ar[7]);
        printf("str_ar[ 8]=%s\n",str_ar[8]);
        printf("str_ar[ 9]=%s\n",str_ar[9]);
        printf("str_ar[10]=%s\n",str_ar[10]);
        printf("str_ar[11]=%s\n",str_ar[11]);
        printf("str_ar[12]=%s\n",str_ar[12]);
        printf("str_ar[13]=%s\n",str_ar[13]);
        printf("str_ar[14]=%s\n",str_ar[14]);
        printf("str_ar[15]=%s\n",str_ar[15]);
        printf("str_ar[16]=%s\n",str_ar[16]);
        printf("str_ar[17]=%s\n",str_ar[17]);
        printf("str_ar[18]=%s\n",str_ar[18]);

        printf("FROM FILE: %s\n",dir_str);
        char tst[100];
        sscanf(str_ar[0],"%99[^=]",tst);
        if (strcmp(tst,"LATITUDE")==0) {
            char longitude[100];
            char latitude[100];
            sscanf(str_ar[0],"LATITUDE=%s LONGITUDE=%99[^\n]",latitude,longitude);
            replace_str(latitude,".",",");
            replace_str(longitude,".",",");
//            printf("%s %s\n",latitude,longitude);
//            printf("%f %f\n",atof(latitude),atof(longitude));
            rel_pos_in_map_x2 = (atof(longitude) + 180.0) / 360.0 ;
            rel_pos_in_map_y2 = (1.0 - log( tan(atof(latitude)*PI/180.0) + 1.0 / cos(atof(latitude)*PI/180.0)) / PI) / 2.0;
            printf("relative:    X=%f   Y=%f\n",rel_pos_in_map_x2,rel_pos_in_map_y2);
            printf("tilenum:     X=%f   Y=%f\n",rel_pos_in_map_x2*pow(2,SAS_ZOOM),rel_pos_in_map_y2*pow(2,SAS_ZOOM));
            printf("inverse:   lng=%f lat=%f\n",rel_pos_in_map_x2*360.0-180.0,180.0/PI*atan(0.5 * (exp(PI-2.0*PI*rel_pos_in_map_y2) - exp(-(PI-2.0*PI*rel_pos_in_map_y2)))));
            sprintf(going_to,"LAT=%f LNG=%f",180.0/PI*atan(0.5 * (exp(PI-2.0*PI*rel_pos_in_map_y2) - exp(-(PI-2.0*PI*rel_pos_in_map_y2)))),
                    rel_pos_in_map_x2*360.0-180.0);
        } else if (str_ar[0][0]=='X' && str_ar[0][1]=='=') {
            sscanf(str_ar[0],"X=%lf Y=%lf",&rel_pos_in_map_x2,&rel_pos_in_map_y2);
            printf("relative:    X=%f   Y=%f\n",rel_pos_in_map_x2,rel_pos_in_map_y2);
            printf("tilenum:     X=%f   Y=%f\n",rel_pos_in_map_x2*pow(2,SAS_ZOOM),rel_pos_in_map_y2*pow(2,SAS_ZOOM));
            printf("inverse:   lng=%f lat=%f\n",rel_pos_in_map_x2*360.0-180.0,180.0/PI*atan(0.5 * (exp(PI-2.0*PI*rel_pos_in_map_y2) - exp(-(PI-2.0*PI*rel_pos_in_map_y2)))));
            sprintf(going_to,"LAT=%f LNG=%f",180.0/PI*atan(0.5 * (exp(PI-2.0*PI*rel_pos_in_map_y2) - exp(-(PI-2.0*PI*rel_pos_in_map_y2)))),
                    rel_pos_in_map_x2*360.0-180.0);
        } else if (strcmp(str_ar[0],"NL")==0 || (atof(str_ar[9])!=0.0 && atof(str_ar[10])!=0.0)) {
            replace_str(str_ar[9],".",",");
            replace_str(str_ar[10],".",",");
            rel_pos_in_map_x2 = (atof(str_ar[10]) + 180.0) / 360.0 ;
            rel_pos_in_map_y2 = (1.0 - log( tan(atof(str_ar[9])*PI/180.0) + 1.0 / cos(atof(str_ar[9])*PI/180.0)) / PI) / 2.0;
            sprintf(going_to,"LAT=%f LNG=%f %s %s %s %s",atof(str_ar[9]),atof(str_ar[10]),str_ar[1],str_ar[2],str_ar[3],str_ar[5]);
            printf("read:      lng=%f lat=%f\n",atof(str_ar[10]),atof(str_ar[9]));
            printf("relative:    X=%f   Y=%f\n",rel_pos_in_map_x2,rel_pos_in_map_y2);
            printf("tilenum:     X=%f   Y=%f\n",rel_pos_in_map_x2*pow(2,SAS_ZOOM),rel_pos_in_map_y2*pow(2,SAS_ZOOM));
            printf("inverse:   lng=%f lat=%f\n",rel_pos_in_map_x2*360.0-180.0,180.0/PI*atan(0.5 * (exp(PI-2.0*PI*rel_pos_in_map_y2) - exp(-(PI-2.0*PI*rel_pos_in_map_y2)))));
        } else {
            replace_str(str_ar[4],".",",");
            replace_str(str_ar[5],".",",");
            rel_pos_in_map_x2 = (atof(str_ar[5]) + 180.0) / 360.0 ;
            rel_pos_in_map_y2 = (1.0 - log( tan(atof(str_ar[4])*PI/180.0) + 1.0 / cos(atof(str_ar[4])*PI/180.0)) / PI) / 2.0;
            sprintf(going_to,"LAT=%f LNG=%f %s %s",atof(str_ar[4]),atof(str_ar[5]),str_ar[1],str_ar[17]);
            printf("read:      lng=%f lat=%f\n",atof(str_ar[5]),atof(str_ar[4]));
            printf("relative:    X=%f   Y=%f\n",rel_pos_in_map_x2,rel_pos_in_map_y2);
            printf("tilenum:     X=%f   Y=%f\n",rel_pos_in_map_x2*pow(2,SAS_ZOOM),rel_pos_in_map_y2*pow(2,SAS_ZOOM));
            printf("inverse:   lng=%f lat=%f\n",rel_pos_in_map_x2*360.0-180.0,180.0/PI*atan(0.5 * (exp(PI-2.0*PI*rel_pos_in_map_y2) - exp(-(PI-2.0*PI*rel_pos_in_map_y2)))));
        }
        strcpy(error_msg,going_to);
        error_flag=1;
        sprintf(error_msg2,"FROM FILE: %s",dir_str);
        error_flag2=1;
    }
}

void lat_lon_to_rel(double latitude, double longitude, double &rel_pos_in_map_x, double &rel_pos_in_map_y ) {
    rel_pos_in_map_x = (longitude + 180.0) / 360.0 ;
    double c=cos(latitude*PI/180.0);
    if (c!=0.0) rel_pos_in_map_y = (1.0 - log( tan(latitude*PI/180.0) + 1.0 / c ) / PI) / 2.0;
}

void rel_to_lat_lon(double rel_pos_in_map_x, double rel_pos_in_map_y, double &latitude, double &longitude) {
   longitude=rel_pos_in_map_x*360.0-180.0;
   double c=PI*atan(0.5 * (exp(PI-2.0*PI*rel_pos_in_map_y) - exp(-(PI-2.0*PI*rel_pos_in_map_y))));
   if (c!=0.0) latitude=180.0/c;
}
