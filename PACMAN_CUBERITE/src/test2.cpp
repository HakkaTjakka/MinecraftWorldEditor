
int main_mceditor3()
{
    int region_x=0;
    int region_z=0;

/*
    printf("Reading one empty regionfile as template\n");
    first_MCEDIT=1;
    editor_in.mca_coder.loadMCA("/Saves/Leeg/region/r.0.0.mca");
    first_MCEDIT=0;
    region_x_old=0,region_z_old=0;
*/
    int contin=1;
    int skipping=1;
    int light=0;
    int size_regions=0;
	srand(12345);
    while (size_regions<60) {
        size_regions++;
        for (region_x=0; region_x<size_regions && !MCEDITOR_stop; region_x++) {
            for (region_z=0; region_z<size_regions && !MCEDITOR_stop; region_z++) {
                if (region_x<size_regions-1 && region_z<size_regions-1) {
                    continue;
                }
                toggle_2=0;toggle_3=0;
                if (contin==1) {
    //                region_x=10;
    //                region_z=4;
                    contin=0;
                }
                chunk_offsetx=region_x*32;
                chunk_offsetz=region_z*32;

                int x0=0, y0=0, z0=0;
                int xl, yl, zl;
                yl = 255;
                xl=512; zl=512;


    //            file_name_MCA = MCAFileNameXZ(region_x, region_z);
    //            editor.mca_coder.loadMCA(file_name_MCA);
                string fname=MCAFileNameXZ(region_x, region_z);
                if ( file_exists(fname.c_str() ) ) {
                    printf("File %s exists, skipping\n",fname.c_str());
                    continue;
                }

                skipping=1;
    //            printf("Getting data\n");
                read_one_plot_WINMAIN(region_x*512, region_z*512 + 30720, &image_plot_extra);
                read_one_plot_WINMAIN(region_x*512, region_z*512, &image_plot);


    //            GET_DATA(region_x,region_z);
    //            printf("Got data, testing\n");
                for (int x = 0; x < 512; x++) {
                    for (int z = 0; z < 512; z++) {
                        if ( !( (image_plot.getPixel(x,z).r==0) && (image_plot.getPixel(x,z).b==0) && (image_plot.getPixel(x,z).b==0)) ) {
                            skipping=0;
                        }
                    }
                }
                if (skipping==1) {
                    printf("r.%d.%d Empty...no data...skipping\n",region_x,region_z);
                    continue;
                } else {
    //                printf("r.%d.%d Empty...not empty...processing\n",region_x,region_z);
                }



                MCRegion region(x0, z0, y0, xl, zl, yl);

                first_MCEDIT=1;
                editor.mca_coder.loadMCA("/Saves/Leeg/region/r.0.0.mca");
                editor.mca_coder.setPOSITIONS();
                first_MCEDIT=0;
                region_x_old=0,region_z_old=0;

                printf("- Creating region r.%d.%d.mca: ",region_x,region_z);

                int num_blocks=0;
                BlockInfo*** AX=region.A;


                printf(" Globes: ");
                for (int x = 0; x < xl; x++) {
                    float xx=x+chunk_offsetx*16;
                    BlockInfo** AZ=AX[x];
                    for (int z = 0; z < zl; z++) {
                        float zz=z+chunk_offsetz*16;
                        BlockInfo* AY=AZ[z];
                        int r, g, b;
                        float pixel;

                        float c;
                        sf::Color col;
                        sf::Color col_extra;
                        col=image_plot.getPixel(x,z);
                        col_extra=image_plot_extra.getPixel(x,z);

                        toggle2();

                        c=(col.r+col.b+col.g);
                        if (col.a==0) pixel=0;

//                        if (rand()%512<10 && rand()%512<10 && rand()%256<255)  {
                        if (rand()%512<50 && rand()%512<80 && rand()%256<25)  {
                            int size_globe=( sin( sin(xx/34.8)*3.1415 + sin(zz/45.7)*3.1415 ) + 1 )*300+50;
                            float s=(float)(rand()%size_globe+30)/11;
                            int xr=rand()%(511-(int)(s*2)-2);
                            int zr=rand()%(511-(int)(s*2)-2);

                            int yr=10+rand()%(240   -(int)(s*2)-2);
                            int colr=rand()%16;
                            int blockr;
                            if (rand()%30==0) blockr=95;
                            else blockr=251;
                            int color_one=rand()%16;
                            for (int xc=0; xc<(int)(s*2); xc++) {
                                for (int zc=0; zc<(int)(s*2); zc++) {
                                    toggle2();
                                    for (int yc=0; yc<(int)(s*2); yc++) {
                                        float some1;
                                        float some2;
                                        int r;
                                        int g;
                                        int b;
                                        int one_col=1;
                                        if ((rand()%10)>3) {
                                            one_col=0;
                                            some1=sin(sin((xx+xr+xc)/10)*2+sin((zz+zr+zc)/5.32)*2)*4;
                                            some2=sin(sin((xx+xr+xc)/15.23)*2+sin((zz+zr+zc)/13.32)*2)*4;
                                            int flow;
                                            flow = (   sin((xx+xr+xc)/(83.23+some1) + sin((zz+zr+zc)/73.75)/3 )  +  sin((zz+zr+zc)/(19.75+some2) + sin((xx+xr+xc)/34.87)/7.2  )  )*5+10;
                                            flow+= (sin((xx+xr+xc)/(94.23+some1/20) + sin((zz+zr+zc)/57.75)/2 )+sin((zz+zr+zc)/(26.75+some2/20) + sin((xx+xr+xc)/45.87)/5 ))*1.25+2.5;
                                            flow+= (   sin((xx+xr+xc)/(62.23+some1*2) + sin((zz+zr+zc)/54.75)/3 )  +  sin((zz+zr+zc)/(64.75+some2*3) + sin((xx+xr+xc)/47.87)/6.2  )  )*15+30;

                                            r=(int)( ( ( sin(((float)(zz+zr+zc)/18+(float)(xx+xr+xc)/7+(yc+yr)/6+some1)/30) +sin(flow/33-(float)(yc+yr)/36.66) ) + 2 ) * 60 ) + rand()%(int)(15);
                                            g=(int)( ( ( sin(((float)(yc+yr)/14+(float)(xx+xr+xc)/13+(float)(zz+zr+zc)/17+some1)/49) + sin(flow/74+(float)(yc+yr)/23.33) ) + 2 ) * 60 ) + rand()%(int)(15);
                                            b=(int)( ( ( sin(((float)(zz+zr+zc)/12+(float)(xx+xr+xc)/14+(float)(yc+yr)/12.5+some1)/53) + sin(flow/44+(float)(yc+yr)/30) ) + 2 ) * 60 ) + rand()%(int)(15);
                                        }

                                        if ( sqrt(
                                                  ((float)xc-s)*((float)xc-s) +
                                                  ((float)zc-s)*((float)zc-s) +
                                                  ((float)yc-s)*((float)yc-s)
                                                  )  < (s)
                                            ) {
//                                            if ((rand()%2)==0) {
//hop                                                AX[xr+xc][zr+zc][yr+yc]=BlockInfo(50, 0, 0 );
//                                            }
//                                            if ((rand()%300000)==0) {
//                                                if ((rand()%2)==0) {
//hop                                                    AX[xr+xc][zr+zc][yr+yc]=BlockInfo(50, 0, 0 );
    //                                                printf("Light globe: AX[%d][%d][%d].id=%d\n",xr+xc,zr+zc,yr+yc,AX[xr+xc][zr+zc][yr+yc].id);
//                                                } else {
//                                                    AX[xr+xc][zr+zc][yr+yc]=BlockInfo();
//                                                }
//                                            }
//                                            else
//                                                if ((rand()%10)==0) light=rand()%15;
//                                                else light=rand()%3;
                                                if (one_col)
                                                    AX[xr+xc][zr+zc][yr+yc]=BlockInfo(blockr, 0, ret_color(r,g,b),0 );
                                                else
                                                    AX[xr+xc][zr+zc][yr+yc]=BlockInfo(blockr, 0, color_one,0 );
                                        }
/*
                                        if ( (int) (sqrt(
                                                  ((float)xc-s)*((float)xc-s) +
                                                  ((float)zc-s)*((float)zc-s) +
                                                  ((float)yc-s)*((float)yc-s)
                                                  )/4)  == (int)(s/4)
                                            ) {
//                                                if ((rand()%(2))==0)
//hop                                                    AX[xr+xc+1][zr+zc+1][yr+yc+1]=BlockInfo(50, 0, 0 );
                                            }
*/
                                    }
                                }
                            }
//                            if (AX[xr+(int)s][zr+(int)s][yr+(int)s].id==0)
//hop                                AX[xr+(int)s][zr+(int)s][yr+(int)s]=BlockInfo(50, 0, 0 );
    //                        printf("Light globe middle: AX[%d][%d][%d].id=%d\n",xr+(int)s,zr+(int)s,yr+(int)s,AX[xr+(int)s][zr+(int)s][yr+(int)s].id);
                        }
                    }
                }

                printf(" Hollowing: ");
                for (int x = 0; x < 512; x++) {
                    float xx=x+chunk_offsetx*16;
                    BlockInfo** AZ=AX[x];
                    for (int z = 0; z < 512; z++) {
                        float zz=z+chunk_offsetz*16;
                        BlockInfo* AY=AZ[z];
                        toggle2();
                        for (int y = 10; y < yl; y++) {
                            if (AY[y].id!=0) {
                                if ( y>0 && y<255 && x>0 && x<511 & z>1 && z<511) {
//                                if ( ((rand()%300000)>1) && y>0 && y<255 && x>0 && x<511 & z>1 && z<511) {
                                    if (  (
    //                                        (AX[x-1][z][y].id!=0) &&
    //                                        (AX[x+1][z][y].id!=0) &&
    //                                        (AX[x][z-1][y].id!=0) &&
    //                                        (AX[x][z+1][y].id!=0) &&
    //                                        (AX[x][z][y-1].id!=0) &&
    //                                        (AX[x][z][y+1].id!=0) &&
                                            (AX[x-1][z-1][y-1].id!=0) &&
                                            (AX[x+0][z-1][y-1].id!=0) &&
                                            (AX[x+1][z-1][y-1].id!=0) &&
                                            (AX[x-1][z+0][y-1].id!=0) &&
                                            (AX[x+0][z+0][y-1].id!=0) &&
                                            (AX[x+1][z+0][y-1].id!=0) &&
                                            (AX[x-1][z+1][y-1].id!=0) &&
                                            (AX[x+0][z+1][y-1].id!=0) &&
                                            (AX[x+1][z+1][y-1].id!=0) &&

                                            (AX[x-1][z-1][y+0].id!=0) &&
                                            (AX[x+0][z-1][y+0].id!=0) &&
                                            (AX[x+1][z-1][y+0].id!=0) &&
                                            (AX[x-1][z+0][y+0].id!=0) &&
                                            (AX[x+0][z+0][y+0].id!=0) &&
                                            (AX[x+1][z+0][y+0].id!=0) &&
                                            (AX[x-1][z+1][y+0].id!=0) &&
                                            (AX[x+0][z+1][y+0].id!=0) &&
                                            (AX[x+1][z+1][y+0].id!=0) &&

                                            (AX[x-1][z-1][y+1].id!=0) &&
                                            (AX[x+0][z-1][y+1].id!=0) &&
                                            (AX[x+1][z-1][y+1].id!=0) &&
                                            (AX[x-1][z+0][y+1].id!=0) &&
                                            (AX[x+0][z+0][y+1].id!=0) &&
                                            (AX[x+1][z+0][y+1].id!=0) &&
                                            (AX[x-1][z+1][y+1].id!=0) &&
                                            (AX[x+0][z+1][y+1].id!=0) &&
                                            (AX[x+1][z+1][y+1].id!=0)

                                     ) ) {
//hop                                        if ((AX[x][z][y].id) == 50) {
    //                                        printf("Keep light: AX[%d][%d][%d].id=%d\n",x,z,y,AX[x][z][y].id);
//                                        } else {
                                            AX[x][z][y].id = 255;
//                                        }
                                     }
                                }
                            }
                        }
                    }
                }

                for (int x = 0; x < 512; x++) {
                    float xx=x+chunk_offsetx*16;
                    BlockInfo** AZ=AX[x];
                    for (int z = 0; z < 512; z++) {
                        float zz=z+chunk_offsetz*16;
                        BlockInfo* AY=AZ[z];
                        toggle2();
                        for (int y = 0; y < yl; y++) {
                            if (  AY[y].id==255) {
                                AY[y] = BlockInfo();
                            }
                        }
                    }
                }




                printf(" Globes: ");
                for (int x = 0; x < xl; x++) {
                    float xx=x+chunk_offsetx*16;
                    BlockInfo** AZ=AX[x];
                    for (int z = 0; z < zl; z++) {
                        float zz=z+chunk_offsetz*16;
                        BlockInfo* AY=AZ[z];
                        int r, g, b;
                        float pixel;

                        float c;
                        sf::Color col;
                        sf::Color col_extra;
                        col=image_plot.getPixel(x,z);
                        col_extra=image_plot_extra.getPixel(x,z);

                        toggle2();

                        c=(col.r+col.b+col.g);
                        if (col.a==0) pixel=0;

//                        if (rand()%512<10 && rand()%512<10 && rand()%256<25)  {
                        if (rand()%512<50 && rand()%512<80 && rand()%256<25)  {
                            int size_globe=( sin( sin(xx/64.8)*3.1415 + sin(zz/88.7)*3.1415 ) + 1 )*150;
                            float s=(float)(rand()%(size_globe+30))/11;
                            int xr=rand()%(511-(int)(s*2)-2);
                            int zr=rand()%(511-(int)(s*2)-2);
                            int yr=30+rand()%(240   -(int)(s*2)-2);
                            int colr=rand()%16;
                            int blockr;
                            if (rand()%3==0) blockr=95;
                            else blockr=251;
                            for (int xc=0; xc<(int)(s*2); xc++) {
                                for (int zc=0; zc<(int)(s*2); zc++) {
                                    toggle2();
                                    for (int yc=0; yc<(int)(s*2); yc++) {
                                        float some1;
                                        some1=sin(sin((xx+xr+xc)/10)*2+sin((zz+zr+zc)/5.32)*2)*4;
                                        float some2;
                                        some2=sin(sin((xx+xr+xc)/15.23)*2+sin((zz+zr+zc)/13.32)*2)*4;
                                        int flow;
                                        flow = (   sin((xx+xr+xc)/(33.23+some1) + sin((zz+zr+zc)/33.75)/3 )  +  sin((zz+zr+zc)/(4.75+some2) + sin((xx+xr+xc)/34.87)/3.2  )  )*5+10;
                                        flow+= (sin((xx+xr+xc)/(34.23+some1/20) + sin((zz+zr+zc)/57.75)/2 )+sin((zz+zr+zc)/(26.75+some2/20) + sin((xx+xr+xc)/45.87)/3 ))*1.25+2.5;
                                        flow+= (   sin((xx+xr+xc)/(12.23+some1*2) + sin((zz+zr+zc)/24.75)/3 )  +  sin((zz+zr+zc)/(34.75+some2*3) + sin((xx+xr+xc)/47.87)/3.2  )  )*15+30;

                                        int r;
                                        r=(int)( ( ( sin(((float)(zz+zr+zc)/8+(float)(xx+xr+xc)/7+(yc+yr)/3+some1)/30) +sin(flow/33-(float)(yc+yr)/16.66) ) + 2 ) * 60 ) + rand()%(int)(15);
                                        int g;
                                        g=(int)( ( ( sin(((float)(yc+yr)/4+(float)(xx+xr+xc)/3+(float)(zz+zr+zc)/7+some1)/29) + sin(flow/74+(float)(yc+yr)/13.33) ) + 2 ) * 60 ) + rand()%(int)(15);
                                        int b;
                                        b=(int)( ( ( sin(((float)(zz+zr+zc)/2+(float)(xx+xr+xc)/4+(float)(yc+yr)/2.5+some1)/13) + sin(flow/44+(float)(yc+yr)/20) ) + 2 ) * 60 ) + rand()%(int)(15);

                                        if ( sqrt(
                                                  ((float)xc-s)*((float)xc-s) +
                                                  ((float)zc-s)*((float)zc-s) +
                                                  ((float)yc-s)*((float)yc-s)
                                                  )  < (s)
                                            ) {
//                                            if ((rand()%2)==0) {
//hop                                                AX[xr+xc][zr+zc][yr+yc]=BlockInfo(50, 0, 0 );
//                                           }
/*                                            if ((rand()%300000)==0) {
                                                if ((rand()%2)==0) {
//hop                                                    AX[xr+xc][zr+zc][yr+yc]=BlockInfo(50, 0, 0 );
    //                                                printf("Light globe: AX[%d][%d][%d].id=%d\n",xr+xc,zr+zc,yr+yc,AX[xr+xc][zr+zc][yr+yc].id);
                                                } else {
                                                    AX[xr+xc][zr+zc][yr+yc]=BlockInfo();
                                                }
                                            }
                                            else
*/
//                                                if ((rand()%10)==0) light=rand()%15;
//                                                else light=rand()%3;
                                                AX[xr+xc][zr+zc][yr+yc]=BlockInfo(blockr, 0, ret_color(r,g,b),0 );
                                        }
/*
                                        if ( (int) (sqrt(
                                                  ((float)xc-s)*((float)xc-s) +
                                                  ((float)zc-s)*((float)zc-s) +
                                                  ((float)yc-s)*((float)yc-s)
                                                  )/4)  == (int)(s/4)
                                            ) {
//                                                if ((rand()%(2))==0)
//hop                                                    AX[xr+xc+1][zr+zc+1][yr+yc+1]=BlockInfo(50, 0, 0 );
                                            }
*/
                                    }
                                }
                            }
//                            if (AX[xr+(int)s][zr+(int)s][yr+(int)s].id==0)
//hop                                AX[xr+(int)s][zr+(int)s][yr+(int)s]=BlockInfo(50, 0, 0 );
    //                        printf("Light globe middle: AX[%d][%d][%d].id=%d\n",xr+(int)s,zr+(int)s,yr+(int)s,AX[xr+(int)s][zr+(int)s][yr+(int)s].id);
                        }
                        pixel = (c/(3));
                        for (int y = 0; y < yl; y++) {

    //                        region.A[x][z][y] = editor.mca_coder.getBlock(x+x0,z+z0,y+y0);
//                            if ((rand()%10)==0) light=rand()%15;
//                            else light=rand()%3;
                            if (y==0) {
                                AY[y] = BlockInfo(7, 0, 0 );
                            } else if (y==1) {
                                if (col.r==254)
                                    AY[y] = BlockInfo(251, 0, ret_color(255,0,0),0 );
                                else
                                    AY[y] = BlockInfo(251, 0, ret_color(255,255,255),0 );
                            } else if (y==2) {
                                if (pixel==0) AY[y] = BlockInfo(251, 0, ret_color(255,255,255),0 );
                                else {
    //                                AY[y] = BlockInfo();
                                }
                            } else if (y==3) {
                                if (pixel==0) {
                                    AY[y] = BlockInfo(95, 0, ret_color(col_extra.r,col_extra.g,col_extra.b),0 );
                                }  else {
    //                                AY[y] = BlockInfo();
                                }
//                            } else if (y==4 || y==5 || y==219 || y==218) {
//                                if ((rand()%(50))==0) {
//hop                                        AY[y] = BlockInfo(50, 0, 0 );
    //                                    printf(".");
//                                }
    //                            else AY[y] = BlockInfo();
                            } else if (y==220) {
                                if (pixel!=0) {
                                    AY[y] = BlockInfo(95, 0, ret_color(0,0,255),0 );
                                }  else {
    //                                AY[y] = BlockInfo();
                                }
                            }
                            else if (y==221) { if (pixel!=0) AY[y] = BlockInfo(251, 0, ret_color(255,255,25),0 ); }
                            else if (y>4) {
    //                            AY[y] = BlockInfo();
                            }
                            if (AY[y].data!=0) num_blocks++;
                        }
                    }
                }




                printf(" Hollowing: ");
                for (int x = 0; x < 512; x++) {
                    float xx=x+chunk_offsetx*16;
                    BlockInfo** AZ=AX[x];
                    for (int z = 0; z < 512; z++) {
                        float zz=z+chunk_offsetz*16;
                        BlockInfo* AY=AZ[z];
                        toggle2();
                        for (int y = 10; y < yl; y++) {
                            if (AY[y].id!=0) {
                                if ( ((rand()%300000)>1) && y>0 && y<255 && x>0 && x<511 & z>1 && z<511) {
                                    if (  (
    //                                        (AX[x-1][z][y].id!=0) &&
    //                                        (AX[x+1][z][y].id!=0) &&
    //                                        (AX[x][z-1][y].id!=0) &&
    //                                        (AX[x][z+1][y].id!=0) &&
    //                                        (AX[x][z][y-1].id!=0) &&
    //                                        (AX[x][z][y+1].id!=0) &&
                                            (AX[x-1][z-1][y-1].id!=0) &&
                                            (AX[x+0][z-1][y-1].id!=0) &&
                                            (AX[x+1][z-1][y-1].id!=0) &&
                                            (AX[x-1][z+0][y-1].id!=0) &&
                                            (AX[x+0][z+0][y-1].id!=0) &&
                                            (AX[x+1][z+0][y-1].id!=0) &&
                                            (AX[x-1][z+1][y-1].id!=0) &&
                                            (AX[x+0][z+1][y-1].id!=0) &&
                                            (AX[x+1][z+1][y-1].id!=0) &&

                                            (AX[x-1][z-1][y+0].id!=0) &&
                                            (AX[x+0][z-1][y+0].id!=0) &&
                                            (AX[x+1][z-1][y+0].id!=0) &&
                                            (AX[x-1][z+0][y+0].id!=0) &&
                                            (AX[x+0][z+0][y+0].id!=0) &&
                                            (AX[x+1][z+0][y+0].id!=0) &&
                                            (AX[x-1][z+1][y+0].id!=0) &&
                                            (AX[x+0][z+1][y+0].id!=0) &&
                                            (AX[x+1][z+1][y+0].id!=0) &&

                                            (AX[x-1][z-1][y+1].id!=0) &&
                                            (AX[x+0][z-1][y+1].id!=0) &&
                                            (AX[x+1][z-1][y+1].id!=0) &&
                                            (AX[x-1][z+0][y+1].id!=0) &&
                                            (AX[x+0][z+0][y+1].id!=0) &&
                                            (AX[x+1][z+0][y+1].id!=0) &&
                                            (AX[x-1][z+1][y+1].id!=0) &&
                                            (AX[x+0][z+1][y+1].id!=0) &&
                                            (AX[x+1][z+1][y+1].id!=0)

                                     ) ) {

//                                        if ((AX[x][z][y].id) == 50) {
    //                                        printf("Keep light: AX[%d][%d][%d].id=%d\n",x,z,y,AX[x][z][y].id);
//                                        } else {
                                            AX[x][z][y].id = 255;
//                                        }

                                     }
                                }
                            }
                        }
                    }
                }
                for (int x = 0; x < 512; x++) {
                    float xx=x+chunk_offsetx*16;
                    BlockInfo** AZ=AX[x];
                    for (int z = 0; z < 512; z++) {
                        float zz=z+chunk_offsetz*16;
                        BlockInfo* AY=AZ[z];
                        toggle2();
                        for (int y = 0; y < yl; y++) {
                            if (  AY[y].id==255) {
                                AY[y] = BlockInfo();
                            }
                        }
                    }
                }


//holes
                printf(" Holes: ");
                for (int x = 0; x < xl; x++) {
                    float xx=x+chunk_offsetx*16;
                    BlockInfo** AZ=AX[x];
                    for (int z = 0; z < zl; z++) {
                        float zz=z+chunk_offsetz*16;
                        BlockInfo* AY=AZ[z];
                        toggle2();
                        if (rand()%512<50 && rand()%512<60 && rand()%256<25)  {
                            int size_globe=( sin( sin(xx/34.8)*3.1415 + sin(zz/45.7)*3.1415 ) + 1 )*45+10;
                            float s=(float)(rand()%size_globe+30)/11;
                            int xr=rand()%(511-(int)(s*2)-2);
                            int zr=rand()%(511-(int)(s*2)-2);
                            int yr=55+rand()%(150-(int)(s*2)-2);

                            for (int xc=0; xc<(int)(s*2); xc++) {
                                for (int zc=0; zc<(int)(s*2); zc++) {
                                    toggle2();
                                    for (int yc=0; yc<(int)(s*2); yc++) {
                                        if ( sqrt(
                                                  ((float)xc-s)*((float)xc-s) +
                                                  ((float)zc-s)*((float)zc-s) +
                                                  ((float)yc-s)*((float)yc-s)
                                                  )  < (s) )
                                         {
                                            AX[xr+xc][zr+zc][yr+yc]=BlockInfo();
                                        }
                                    }
                                }
                            }
                            AX[xr+(int)s][zr+(int)s][yr+(int)s]=BlockInfo(50,0,0);
                        }
                    }
                }


                for (int x = 0; x < xl; x++) {
                    float xx=x+chunk_offsetx*16;
                    BlockInfo** AZ=AX[x];
                    for (int z = 0; z < zl; z++) {
                        float zz=z+chunk_offsetz*16;
                        BlockInfo* AY=AZ[z];
                        int r, g, b;
                        float pixel;

                        float c;
                        sf::Color col;
                        sf::Color col_extra;
                        col=image_plot.getPixel(x,z);
                        col_extra=image_plot_extra.getPixel(x,z);

                        int edge=0;
                        if (x>0 && x<511 && z>0 && z<511) {
                            sf::Color col_side1;
                            sf::Color col_side2;
                            sf::Color col_side3;
                            sf::Color col_side4;
                            col_side1=image_plot.getPixel(x-1,z);
                            col_side2=image_plot.getPixel(x,z-1);
                            col_side3=image_plot.getPixel(x+1,z);
                            col_side4=image_plot.getPixel(x,z+1);
                            int c1=(col_side1.r+col_side1.b+col_side1.g);
                            int c2=(col_side2.r+col_side2.b+col_side2.g);
                            int c3=(col_side3.r+col_side3.b+col_side3.g);
                            int c4=(col_side4.r+col_side4.b+col_side4.g);
                            if (c1==0 || c2==0 || c3==0 || c4==0) edge=1;
                            if (edge==0) {
                                col_side1=image_plot.getPixel(x-1,z-1);
                                col_side2=image_plot.getPixel(x+1,z-1);
                                col_side3=image_plot.getPixel(x+1,z+1);
                                col_side4=image_plot.getPixel(x-1,z+1);
                                c1=(col_side1.r+col_side1.b+col_side1.g);
                                c2=(col_side2.r+col_side2.b+col_side2.g);
                                c3=(col_side3.r+col_side3.b+col_side3.g);
                                c4=(col_side4.r+col_side4.b+col_side4.g);
                                if (c1==0 || c2==0 || c3==0 || c4==0) edge=1;
                            }

                        }

                        c=(col.r+col.b+col.g);
                        if (col.a==0) pixel=0;

                        pixel = (c/(3));
                        for (int y = 104; y <= 115; y++) {
//                            if ((rand()%10)==0) light=rand()%15;
//                            else light=rand()%3;

    //                        region.A[x][z][y] = editor.mca_coder.getBlock(x+x0,z+z0,y+y0);
                            if (y>=109 && y<115) {
                                toggle2();
                                if (pixel!=0) {
                                    if (pixel!=0 && edge==1) {
                                        if (col.r==254) {
                                            AY[y] = BlockInfo(95, 0, ret_color(255,0,0),0 );
                                        }  else {
                                            if (rand()%30==0)
                                                AY[y] = BlockInfo(95, 0, ret_color(rand()%256,rand()%256,rand()%256),0 );
                                            else
                                                AY[y] = BlockInfo(95, 0, ret_color(255,255,255),0 );
                                        }
                                    } else if (pixel!=0) {
                                        if (col.r==254) {
                                            if ((rand()%(20))<4) AY[y] = BlockInfo(50, 0, 0);
                                            else AY[y] = BlockInfo();
                                        } else {
                                            if ((rand()%(80))<3) AY[y] = BlockInfo(50, 0, 0);
                                            else AY[y] = BlockInfo();
                                        }
                                    } else {
//                                        AY[y] = BlockInfo();
                                    }
                                }// else AY[y] = BlockInfo();
                            }
                            else if (y==115) {
                                toggle2();
                                if (pixel!=0) {
                                    if (rand()%30==0)
                                        AY[y] = BlockInfo(95, 0, ret_color(rand()%256,rand()%256,rand()%256),0 );
                                    else {
                                        if (col.r==254) {
                                            AY[y] = BlockInfo(95, 0, ret_color(255,0,0),0 );
                                        } else {
                                            AY[y] = BlockInfo(95, 0, ret_color(255,255,255),0 );
                                        }
                                    }
                                } else {
//                                    AY[y] = BlockInfo();
                                }
                            }
                            else if (y==108) {
                                if (pixel!=0) {
                                    if (col.r==254)
                                        AY[y] = BlockInfo(251, 0, ret_color(255,0,0),0 );
                                    else
                                        AY[y] = BlockInfo(251, 0, ret_color(255,255,255),0 );
                                } //else  AY[y] = BlockInfo();
                            }
                            else if (y==107) {  if (pixel!=0 && (rand()%2)==0)      AY[y] = BlockInfo(251, 0, ret_color(rand()%256,rand()%256,rand()%256),0 );  }
                            else if (y==106) {  if (pixel!=0 && (rand()%4)==0)      AY[y] = BlockInfo(251, 0, ret_color(rand()%256,rand()%256,rand()%256),0 );  }
                            else if (y==105) {  if (pixel!=0 && (rand()%8)==0)      AY[y] = BlockInfo(251, 0, ret_color(rand()%256,rand()%256,rand()%256),0 );  }
                            else if (y==104) {  if (pixel!=0 && (rand()%16)==0)     AY[y] = BlockInfo(251, 0, ret_color(rand()%256,rand()%256,rand()%256),0 );  }
                            if (AY[y].data!=0) num_blocks++;
                        }
                    }
                }








                for (int x = 0; x < 512; x++) {
                    float xx=x+chunk_offsetx*16;
                    BlockInfo** AZ=AX[x];
                    for (int z = 0; z < 512; z++) {
                        float zz=z+chunk_offsetz*16;
                        BlockInfo* AY=AZ[z];
                        toggle2();
                        for (int y = 0; y < yl; y++) {
                            if (  AY[y].id==0) {
                                float some1;
                                some1=sin(sin((xx)/59)*2+sin((zz)/31.32)*2)*4;
                                float some2;
                                some2=sin(sin((xx)/35.23)*2+sin((zz)/57.32)*2)*4;
                                int flow;
                                flow = (   sin((xx)/(98.23+some1)    + sin((zz)/133.75)/3 )  +  sin((zz)/(154.75+some2)    + sin((xx)/314.87)/3.2  )  )*5+10;
                                flow+= (   sin((xx)/(134.23+some1/20) + sin((zz)/157.75)/2 )  +  sin((zz)/(166.75+some2/20) + sin((xx)/145.87)/3    )  )*1.25+2.5;
                                flow+= (   sin((xx)/(132.23+some1*2)  + sin((zz)/124.75)/3 )  +  sin((zz)/(144.75+some2*3)  + sin((xx)/147.87)/3.2  )  )*15+30;
                                float hop = (int)(sin(
                                                sin( (float)zz/(  250  + sin((float)xx/76 +(float)y/159   )*65  ) )*(3.1415 + (float)flow/150 + some1/8 ) +
                                                sin( (float)xx/(  250  + sin((float)zz/98 +(float)y/199  )*65  ) )*(3.1415 + (float)flow/150 + some2/9 ) +
                                                sin( (float)y /(  150  + sin((float)zz/40+(float)xx/145 )*62   ) )*(3.1415 + (float)flow/175 + (some1+some2)/21)
                                              ));
                                if (  (int)hop*16*32 == 0 || (int)((hop+1)*400)==(int)(flow*8) ||  (rand()%2000==0 && rand()%10==0 )  || (int)(((int)(100*flow))==4000 ) )
                                    {
                                        AY[y]=BlockInfo(50, 0, 0);
//                                        if ( (rand()%500)==0) printf(".");
                                    }

                            }

/*
                            if ( AY[y].id!=0 && (rand()%10)==0 ) {

                                int light =  rand() % ( (int) ( (    sin(
                                                        sin(zz/(  105      + sin(xx/188+y/79   )*50   )          )*3.1415 +
                                                        sin(xx/(  97.323   + sin(zz/233+y/89   )*50   )          )*3.1415 +
                                                        sin(y /(  114.383   + sin(zz/211+xx/145 )*50  )          )*3.1415
                                                ) + 3 )/6*15.9 )  );

//                                BlockInfo res = editor.mca_coder.getBlock(x, z, y).;
//                                res.block_light=light;
                                AY[y].block_light=light;
                            }
*/
                            if (  AY[y].id==0 && y<5) {
                                if ( (rand()%100000)==0 ) {
                                    AY[y]=BlockInfo(50, 0, 0 );
//                                    if ( (rand()%500)==0) printf(".");
                                }
                            }
                        }
                    }
                }

                printf(" %d blocks added\n",num_blocks);
                if (plot_cubes) {
                    int blocks_shown=0;
                    MUTEX_MCEDITOR.lock();
                    m_pointCloud3.resize(num_blocks);
                    for (int x = 0; x < 512; x++) {
                        float xx=x+chunk_offsetx*16;
                        BlockInfo** AZ=AX[x];
                        for (int z = 0; z < 512; z++) {
                            float zz=z+chunk_offsetz*16;
                            BlockInfo* AY=AZ[z];
                            toggle2();
        /*
                            int r, g, b;
                            float pixel;

                            float c;
                            sf::Color col;
                            sf::Color col_extra;
                            col=image_plot.getPixel(x,z);
                            col_extra=image_plot_extra.getPixel(x,z);

                            toggle2();toggle2();toggle2();toggle2();

                            c=(col.r+col.b+col.g);
                            if (col.a==0) pixel=0;

                            pixel = (c/(3));
        */
                            for (int y = 0; y < yl; y++) {
                                if (AY[y].id!=0) {
                                    if (y>0 && y<255 && x>0 && x<511 & z>1 && z<511) {
                                        if (  (
                                            (AX[x-1][z-1][y-1].id!=0) &&
                                            (AX[x+0][z-1][y-1].id!=0) &&
                                            (AX[x+1][z-1][y-1].id!=0) &&
                                            (AX[x-1][z+0][y-1].id!=0) &&
                                            (AX[x+0][z+0][y-1].id!=0) &&
                                            (AX[x+1][z+0][y-1].id!=0) &&
                                            (AX[x-1][z+1][y-1].id!=0) &&
                                            (AX[x+0][z+1][y-1].id!=0) &&
                                            (AX[x+1][z+1][y-1].id!=0) &&

                                            (AX[x-1][z-1][y+0].id!=0) &&
                                            (AX[x+0][z-1][y+0].id!=0) &&
                                            (AX[x+1][z-1][y+0].id!=0) &&
                                            (AX[x-1][z+0][y+0].id!=0) &&
                                            (AX[x+0][z+0][y+0].id!=0) &&
                                            (AX[x+1][z+0][y+0].id!=0) &&
                                            (AX[x-1][z+1][y+0].id!=0) &&
                                            (AX[x+0][z+1][y+0].id!=0) &&
                                            (AX[x+1][z+1][y+0].id!=0) &&

                                            (AX[x-1][z-1][y+1].id!=0) &&
                                            (AX[x+0][z-1][y+1].id!=0) &&
                                            (AX[x+1][z-1][y+1].id!=0) &&
                                            (AX[x-1][z+0][y+1].id!=0) &&
                                            (AX[x+0][z+0][y+1].id!=0) &&
                                            (AX[x+1][z+0][y+1].id!=0) &&
                                            (AX[x-1][z+1][y+1].id!=0) &&
                                            (AX[x+0][z+1][y+1].id!=0) &&
                                            (AX[x+1][z+1][y+1].id!=0)

                                         ) ) {
    //                                         printf("Hidden block at %3d %3d %3d\n",x,y,z);
                                             continue;
                                         }
                                    }
                                    m_pointCloud3[blocks_shown].position.x=(float)x*256/scale_factor;
                                    m_pointCloud3[blocks_shown].position.y=(float)z*256/scale_factor;
                                    m_pointCloud3[blocks_shown].texCoords.x = (float) (((x+y+1000)%6)*256)*150.0;
                                    m_pointCloud3[blocks_shown].texCoords.y = (float) (0)*150.0;
                                    m_pointCloud3[blocks_shown].color = sf::Color(y,0,0,0);
    //                                printf("Adding block %d at x=%f y=%f col.r=%3d\n",blocks_shown,m_pointCloud3[blocks_shown].position.x , m_pointCloud3[blocks_shown].position.y, m_pointCloud3[blocks_shown].color );
                                    blocks_shown++;
                                    if (blocks_shown>num_blocks) {printf("\nError block count\n"); y=yl; x=xl; z=zl;}
                                }
                            }
                        }
                    }
    //make hollow. (glass blobs)
                    m_pointCloud3.resize(blocks_shown);
                    printf(" %d blocks added to plot_cubes vertex\n",num_blocks);
                    MUTEX_MCEDITOR.unlock();
                }

    //            system("timeout 60");
                printf(" ");
                first_MCEDIT=0;
                region_x_old=0;
                region_z_old=0;
                file_name_MCA = MCAFileNameXZ(region_x, region_z);
                editor.setRegion(region);
    //            printf("\n");
                if (MCEDITOR_stop==1) {
                    printf("Stop requested, exiting\n");
                    system("/saves/copy_test.bat");
                    send_message='x';
                    return 0;
                }
            }
        }
    }
    return 0;
}

