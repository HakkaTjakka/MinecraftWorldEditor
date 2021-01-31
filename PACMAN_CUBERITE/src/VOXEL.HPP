#ifndef VOXEL_HPP_INCLUDED
#define VOXEL_HPP_INCLUDED

typedef unsigned short us;

extern bool sort_cubic;
extern bool sort_voxels_on_l;

struct Voxel {
    int x,y,z;
    unsigned int r,g,b,l;
    unsigned char status;
    signed char face;

    Voxel(): x(0), y(0), z(0), r(0), g(0), b(0), l(0), status(0), face(0) {};

    Voxel(int x_, int y_, int z_, unsigned int r_ = 0 , unsigned int g_ = 0 , unsigned int b_ = 0 , unsigned int l_ = 0 , unsigned char status_ = 0, signed char face_ = 0 )
            : x(x_), y(y_), z(z_), r(r_), g(g_), b(b_), l(l_), status(status_), face(face_)  {};

    bool operator < (const Voxel &B) const
    {

        if (sort_voxels_on_l) return l < B.l;

        int ay = y , by = B.y;

        int ay_d=ay/512; if (ay<0) ay_d--;
        int by_d=by/512; if (by<0) by_d--;

        if (ay_d != by_d) {
//        if ((int)(ay / 512) != (int)(by / 512)) {
            return ay < by;
        } else {
            int az = z, bz = B.z;

            int az_d=az/512; if (az<0) az_d--;
            int bz_d=bz/512; if (bz<0) bz_d--;

            if (az_d != bz_d) {
//            if ((int)(az / 512) != (int)(bz / 512)) {
                return az < bz;
            } else {
                int ax = x, bx = B.x;
                if (sort_cubic) {
                    int ax_d=ax/256; if (ax<0) ax_d--;
                    int bx_d=bx/256; if (bx<0) bx_d--;
                    if (ax_d != bx_d) {
//                    if ((int)(ax / 256) != (int)(bx / 256)) {
                        return ax < bx;
                    } else {
                        if (ay!=by) return ay < by;
                        else if (az!=bz) return az < bz;
                        else return ax < bx;
                    }
                } else {
                    if (ay!=by) return ay < by;
                    else if (az!=bz) return az < bz;
                    else return ax < bx;
                }
            }
        }
    }
};



struct hit_one_region {
    int x,z;
    int index0=0;    int index1=0;    int index2=0;    int index3=0;
    int index4=0;    int index5=0;    int index6=0;    int index7=0;
    int index8=0;    int index9=0;    int index10=0;    int index11=0;
    int index12=0;

    hit_one_region(): x(0), z(0), index0(0), index1(0), index2(0), index3(0), index4(0), index5(0), index6(0), index7(0), index8(0), index9(0), index10(0), index11(0), index12(0)  {};

    hit_one_region( int x_,     int z_,     int index0_=0,      int index1_=0,      int index2_=0,      int index3_=0,
                                            int index4_=0,      int index5_=0,      int index6_=0,      int index7_=0,
                                            int index8_=0,      int index9_=0,      int index10_=0,     int index11_=0,     int index12_=0 )
                    : x(x_),    z(z_),      index0(index0_),    index1(index1_),    index2(index2_),    index3(index3_),
                                            index4(index4_),    index5(index5_),    index6(index6_),    index7(index7_),
                                            index8(index8_),    index9(index9_),    index10(index10_),  index11(index11),  index12(index12) {};

    bool operator < (const hit_one_region &B) const
    {
        if (z != B.z) return z < B.z;
        else return x < B.x;
//        return index8 < B.index8;

    }

/*
    bool operator = (const Voxel &B) const
    {
        return (z == B.z && x == B.x);
    }
*/
};

struct cubic_region {
    int region_floor;
    int x,z;

    cubic_region(): region_floor(0), x(0), z(0) {};

    cubic_region( int region_floor_, int x_, int z_ ) : region_floor(region_floor_), x(x_), z(z_) {};

/*
    bool operator < (const cubic_region &B) const
    {
        if (sort_regions_circle) {
            if (x!=B.x || z!=B.z) {
                double dist=sqrt( (x-region_center_x)*(x-region_center_x) + (z-region_center_z)*(z-region_center_z) );
                double Bdist=sqrt( (B.x-region_center_x)*(B.x-region_center_x) + (B.z-region_center_z)*(B.z-region_center_z) );
                return( dist < Bdist );
            }
            return region_floor < B.region_floor;
        }

        if (x != B.x) return x < B.x;
        if (z != B.z) return z < B.z;
        return region_floor < B.region_floor;
    }
*/
};



#endif // VOXEL_HPP_INCLUDED




/*

void WUPPIE_SUBS_OLD(std::vector<BufferObject> buffers, std::vector<tinyobj::material_t> &materials, float bmin_o[3], float bmax_o[3], double lat, double lon, std::string fn) {

//printf("I am here 1\n");
    random_pixel=sf::Color(64+rand()%64,64+rand()%64,64+rand()%64,255);
    wuppie_all=false;
    FILE* voxel_file_pointer=NULL;
    bool plot_only_on=false;
    if (!plot_only) {

        printf("CREATING ARRAY 512*256*512*4 = %d BYTES:",512*256*512*4);
        mc2 = (unsigned char*) malloc(512*256*512*4);
        printf(" OK. CLEARING:");
        std::memset(mc2, 0x0, 512*256*512*4);
        printf(" OK\n");
    } else {
        plot_only_on=true;
    }

//    static int first=1;
    vector_hit_regions.clear();
    if (first_wuppie==1) {
        first_wuppie=0;
        for (int z=0; z<1000; z++) {
            for (int x=0; x<1000; x++) {
                hit_regions[x][z][11]=0;
                region_counter[x][z]=0;
            }
        }
        DIR* dr = opendir("/saves/test/region/done0");
        struct dirent *de;
//sukkel
        if (!plot_only_on && (mirror==3 || mirror==4)) {
            printf("REGIONS: ");
            int x,z;
            char picture_file[200];
            while ((de = readdir(dr)) != NULL) {
                if ((strstr(de->d_name, ".mca")) != NULL) {
    //                printf(de->d_name);
                    printf("%s ",de->d_name);
                    if (!flushing) {
                        sscanf(de->d_name,"r.%d.%d.mca",&x,&z);
//                        printf("r.%d.%d.mca ",x,z);
                        if (mirror==4) {
                            sprintf(picture_file,"../cut/r.%d.%d.jpg",x,z);
                            if (file_exists(picture_file)) {
                                scan_image.loadFromFile(picture_file);
                                plot_only=1;
                            } else {
                                scan_image.create(512,512,sf::Color(128,128,128,128));
                                plotting=1;
                                plot_only=1;
                                MCEDITOR_running=1;
                                main_mceditor6_fixed(x, z, mc2);
                                MCEDITOR_running=0;
                                plotting=0;
                            }
                        } else if (mirror==3) {
                            scan_image.create(512,512,sf::Color(128,128,128,128));
                            plotting=1;
                            plot_only=1;
                            MCEDITOR_running=1;
                            main_mceditor6_fixed(x, z, mc2);
                            MCEDITOR_running=0;
                            plotting=0;
                        }
//                        sprintf(mc_text1,"R.%d.%d.MCA",x,z);
//                        sprintf(mc_text2,"SAVED");
//                        scan_x=x;
//                        scan_z=z;
//                        plotting=2;
//                        update_request=2;
//                        while (update_request) {
//                            sf::sleep(sf::seconds(0.005));
//                        }
                        plot_only=0;
                    }
                    vector_hit_regions.push_back(hit_one_region(x,z));
                    hit_one_region* hit_one=&vector_hit_regions[vector_hit_regions.size()-1];
//                    hit_one_region* hit_one=&(*vector_hit_regions.end());
                    hit_one->index11=1;
                    hit_one->index12=1;
                    hit_regions[x][z][11]=1;
                    region_counter[x][z]=1;
                }
            }
        }
        closedir(dr);
        printf("\n");
        if (mirror==3) {
            free(mc2);
            return;
        }
    }

    FILE* dummy;
    char new_file_raw[100];
    char new_file_dat[100];

//    BufferObject one_buffer;
    int count=0;

    voxels.clear();
    char new_name[200];

    sprintf(new_name,"../cut/%s",fn.c_str());
//    mkdir(new_name);
//Amsterdam
//    std::vector<BufferObject> buffers_sub;
//    for (std::vector<BufferObject>::iterator it=buffers.begin(), end = buffers.end(); it != end; ++it) {
//        one_buffer=*it;
//        buffers_sub.push_back(one_buffer);
//        count++;
//    }

    printf("%s\n",fn.c_str());

    int ret=2;
//loaded flushed file.vox
    if (buffers.size()==0) ret=3;
    static int box_x;
    static int box_y;
    static int box_z;

    static int box_x_block_start;
    static int box_y_block_start;
    static int box_z_block_start;

    static int box_x_block_end;
    static int box_y_block_end;
    static int box_z_block_end;

    static int box_x_total_start;
    static int box_y_total_start;
    static int box_z_total_start;

    static int box_x_total_end;
    static int box_y_total_end;
    static int box_z_total_end;
    if (!flushing && ret==2)
        ret=WUPPIE_VECTOR(buffers, materials, bmin_o, bmax_o, lat, lon, fn);
    if (ret==-1) {
        printf("ERROR %s\n",fn.c_str());
    } else if (ret==0) {
        printf("File exists, skipping\n");
        return;
    } else if (ret!=2) {
//        printf("voxels[0] = SIZE:        X=%6d, Y=%6d, Z=%6d\n", voxels[0].x, voxels[0].y, voxels[0].z );
//        printf("voxels[1] = START:       X=%6d, Y=%6d, Z=%6d\n", voxels[1].x, voxels[1].y, voxels[1].z );
//        printf("voxels[2] = END:         X=%6d, Y=%6d, Z=%6d\n", voxels[2].x, voxels[2].y, voxels[2].z );
//        printf("voxels[3] = TOTAL START: X=%6d, Y=%6d, Z=%6d\n", voxels[3].x, voxels[3].y, voxels[3].z );
//        printf("voxels[4] = TOTAL END:   X=%6d, Y=%6d, Z=%6d\n", voxels[4].x, voxels[4].y, voxels[4].z );

        if (ret==1) {
            box_x=voxels[0].x; box_x_block_start=voxels[1].x; box_x_block_end=voxels[2].x; box_x_total_start=voxels[3].x; box_x_total_end=voxels[4].x;
            box_y=voxels[0].y; box_y_block_start=voxels[1].y; box_y_block_end=voxels[2].y; box_y_total_start=voxels[3].y; box_y_total_end=voxels[4].y;
            box_z=voxels[0].z; box_z_block_start=voxels[1].z; box_z_block_end=voxels[2].z; box_z_total_start=voxels[3].z; box_z_total_end=voxels[4].z;
        }
//        int count=0;

        printf("\n");
        printf("NEW NUMBER OF VOXELS                 %9d  ",voxels.size()-5);
        int total_hits=0;
        for (size_t count=5; count<voxels.size(); count++ ) {
            total_hits+=voxels[count].l;
//            voxels[count].x =voxels[count].x - box_x_total_start;   //y height
//            voxels[count].x =voxels[count].x - box_x_total_start;   //y height
//hellup
////            voxels[count].x =voxels[count].x - box_x_block_start;   //y height
            voxels[count].x +=1;
            voxels[count].z =(box_z_total_end - box_z_total_start) - voxels[count].z + 2048;   //(region z) zz
            voxels[count].y =voxels[count].y + 2048;   //(region x) xx

//            voxels[count].x =voxels[count].x + box_x_block_start - box_x_total_start;   //y height
//            voxels[count].y =-voxels[count].y - box_y_block_start - box_y_total_start  + 2048;   //(region x) xx
////            voxels[count].z =voxels[count].z + box_z_block_start - box_z_total_start + 2048;   //(region z) zz
//            voxels[count].x =voxels[count].x;   //y height
//            voxels[count].x =voxels[count].x - box_x_block_start      - box_x_total_start;   //y height
//            voxels[count].y =voxels[count].y - box_y_block_start-2048 + box_y_total_end;     //(region x) xx
        }
        printf("NEW NUMBER OF HITS:                  %9d\n",total_hits);

        std::vector<Voxel> voxels_temp;

        if (voxels.size()>5) {
//            printf("SORTING VOXELS TO TEMP: ");
            sort(voxels.begin()+5, voxels.end());
//            printf("Ok. TOTAL/AVERAGE/COMPRESS: ");
            Voxel last=voxels[5];
            Voxel total_pos=Voxel(last.x,last.y,last.z,0,0,0,0);
            for (size_t n=5; n<voxels.size(); n++) {
                if (last.x==voxels[n].x && last.y==voxels[n].y && last.z==voxels[n].z) {
                    total_pos.r+=voxels[n].r;
                    total_pos.g+=voxels[n].g;
                    total_pos.b+=voxels[n].b;
                    total_pos.l+=voxels[n].l;
                    if (n==voxels.size()-1) {
                        total_pos.status=0; //new
                        voxels_temp.push_back(total_pos);
                    }
                } else {
                    total_pos.status=0; //new
                    voxels_temp.push_back(total_pos);
                    last=voxels[n];
                    total_pos=last;
                    if (n==voxels.size()-1) {
                        total_pos.status=0; //new
                        voxels_temp.push_back(total_pos);
                    }
                }
            }
        }

//        printf("\n");
        printf("SORTED NUMBER OF NEW VOXELS:         %9d  ",voxels_temp.size());
        total_hits=0;
        for (auto u : voxels_temp) {
            total_hits+=u.l;
        }
        printf("SORTED NUMBER OF NEW HITS:           %9d  ",total_hits);
        if (voxels_temp.size()>0) printf("HITS/VOXEL=%f\n",(double)total_hits/(double)voxels_temp.size());
        else printf ("\n");


        printf("TOTAL NUMBER OF VOXELS:              %9d  ",voxels_total.size());
        total_hits=0;
        for (auto u : voxels_total) {
            total_hits+=u.l;
        }
        printf("TOTAL NUMBER OF HITS:                %9d\n",total_hits);

//        printf("ADDING TOTAL! VOXELS TO TEMP! VOXELS:  ");
        Voxel one;
        for (auto u : voxels_total) {
            one=u;
            voxels_temp.push_back(one);
        }
//        printf("CLEARING TOTAL: ");
        voxels_total.clear();
//        printf("OK.\n");

        printf("NEW TOTAL NUMBER OF VOXELS:          %9d  ",voxels_temp.size());
        total_hits=0;
        for (auto u : voxels_temp) {
            total_hits+=u.l;
        }
        printf("NEW TOTAL NUMBER OF HITS:            %9d\n",total_hits);

        int pixel_adds=0;
        if (voxels_temp.size()>0) {
//            printf("SORTING BOTH VOXELS BACK TO TOTAL VOXELS: ");
            sort(voxels_temp.begin(), voxels_temp.end());
//            printf("Ok. TOTAL/AVERAGE/COMPRESS: ");
            Voxel last=voxels_temp[0];
            Voxel total_pos=Voxel(last.x,last.y,last.z,0,0,0,0,last.status);
            for (size_t n=0; n<voxels_temp.size(); n++) {
                if (last.x==voxels_temp[n].x && last.y==voxels_temp[n].y && last.z==voxels_temp[n].z) {
                    total_pos.r+=voxels_temp[n].r;
                    total_pos.g+=voxels_temp[n].g;
                    total_pos.b+=voxels_temp[n].b;
                    total_pos.l+=voxels_temp[n].l;
                    if (voxels_temp[n].status != total_pos.status==0) pixel_adds++;
                    if (voxels_temp[n].status==0) total_pos.status=0;
                    if (n==voxels_temp.size()-1) {
                        voxels_total.push_back(total_pos);
                    }
                } else {
                    voxels_total.push_back(total_pos);
                    last=voxels_temp[n];
                    total_pos=last;
                    if (n==voxels_temp.size()-1) {
                        voxels_total.push_back(total_pos);
                    }
                }
            }
        }


//        printf("\n");
        printf("SORTED NEW TOTAL NUMBER OF VOXELS:   %9d  ",voxels_total.size());
        total_hits=0;
        for (auto u : voxels_total) {
            total_hits+=u.l;
        }
        printf("SORTED NEW TOTAL NUMBER OF HITS:     %9d  ",total_hits);
        if (voxels_total.size()>0) printf("HITS/VOXEL=%f  ",(double)total_hits/(double)voxels_total.size());
        if (pixel_adds>0) printf(" PIXEL ADDS: %d" ,pixel_adds);
        printf ("\n");


//        printf("\n");
        count=0;
//        for (auto u : voxels_total) {
//            printf("srt:region[%3d][%3d] POS[%3d][%3d][%3d] voxels_total[%3d]=Voxel(%6d,%6d,%6d,%4d,%4d,%4d,%4d)\n",
//                   u.y/512,u.z/512, u.y%512,u.x,u.z%512, count++,u.x,u.y,u.z,u.r,u.g,u.b,u.l);
//        }

//        printf("SCANNING REGIONS:\n");
        for (int z=0; z<1000; z++) {
            for (int x=0; x<1000; x++) {
                hit_regions[x][z][0]=std::numeric_limits<int>::max();
                hit_regions[x][z][1]=-std::numeric_limits<int>::max();
                hit_regions[x][z][2]=std::numeric_limits<int>::max();
                hit_regions[x][z][3]=-std::numeric_limits<int>::max();
                hit_regions[x][z][4]=std::numeric_limits<int>::max();
                hit_regions[x][z][5]=-std::numeric_limits<int>::max();
                hit_regions[x][z][6]=0;
                hit_regions[x][z][7]=0;
                hit_regions[x][z][8]=0;
                hit_regions[x][z][9]=0;
                hit_regions[x][z][10]=0;
            }
        }
        int one_region[512][512];
        for (int zz=0; zz<512; zz++) {
            for (int xx=0; xx<512; xx++) {
                one_region[xx][zz]=0;
            }
        }

        if (voxels_total.size()>0) {
            int min_x=std::numeric_limits<int>::max();
            int max_x=-std::numeric_limits<int>::max();
            int min_y=std::numeric_limits<int>::max();
            int max_y=-std::numeric_limits<int>::max();
            int min_z=std::numeric_limits<int>::max();
            int max_z=-std::numeric_limits<int>::max();
            int rx,rz;
            Voxel one=voxels_total[0];
            bool plot_region=false;
//            if (one.status==0) {
//                plot_region=true;
//            }
            int y=one.y,z=one.z;
            rx=y/512;
            rz=z/512;

            Voxel prev;
            int rx_prev;
            int rz_prev;

            int total_voxels_column=0;
            int num_voxels=voxels_total.size();
            int voxel_index=0;
            int total_voxels_region=0;
            int total_hits_region=0;
            size_t total_voxels_all_regions=0;
            size_t total_hits_all_regions=0;
//            for (auto u : voxels_total) {
            int n=0;
//            printf("\n");
//            printf("region[%3d][%3d] POS[%3d][%3d][%3d] voxels_total[%3d]=Voxel(%6d,%6d,%6d,%4d,%4d,%4d,%4d)\n",
//                   rx,rz,one.y%512,one.x,one.z%512,n,one.x,one.y,one.z,one.r,one.g,one.b,one.l);
            while (n<voxels_total.size()) {
                prev=one;
                rx_prev=rx; rz_prev=rz;
                int total_columns=0;

                int prev_xx=-1;
                scan_image.create(512,512,sf::Color(0,0,0,0));
                bool xz00=false,xz01=false,xz10=false,xz11=false;
                int new_hits_region=0;
                while (rx==rx_prev && rz==rz_prev && n<voxels_total.size()) {
                    prev=one;
                    rx_prev=rx; rz_prev=rz;
                    while (y==prev.y && z==prev.z && n<voxels_total.size()) {
                        if (prev.status==0) {
//                            plot_region=true; //new blocks....update region file. if exists....
                            new_hits_region++;
                        }
                        total_voxels_column++;
                        total_hits_region+=one.l;
                        prev=one;
                        rx_prev=rx; rz_prev=rz;
                        n++;
                        if (n<voxels_total.size()) {
                            one=voxels_total[n];
                            y=one.y; z=one.z; rx=y/512; rz=z/512;
//                            printf("region[%3d][%3d] POS[%3d][%3d][%3d] voxels_total[%3d]=Voxel(%6d,%6d,%6d,%4d,%4d,%4d,%4d)\n",
//                                   rx,rz,one.y%512,one.x,one.z%512,n,one.x,one.y,one.z,one.r,one.g,one.b,one.l);
                        }
                    }
                    total_columns++;
                    if (!xz00 && (prev.y%512)==  0 && (prev.z%512)==  0) xz00=true;
                    if (!xz01 && (prev.y%512)==  0 && (prev.z%512)==511) xz01=true;
                    if (!xz10 && (prev.y%512)==511 && (prev.z%512)==  0) xz10=true;
                    if (!xz11 && (prev.y%512)==511 && (prev.z%512)==511) xz11=true;
                    one_region[prev.y%512][prev.z%512]=total_voxels_column;
                    total_voxels_region+=total_voxels_column;
                    scan_image.setPixel(prev.y%512,prev.z%512,sf::Color(prev.r/prev.l,prev.g/prev.l,prev.b/prev.l,255));
                    if (plot_region==false && prev.status==0) { // new top block.... display top view.
                        plot_region=true;
                    }

                    if (rx!=rx_prev || rz!=rz_prev) {
                        printf("region[%3d][%3d] total_column[%3d][tot][%3d]=%3d total_culumns=%d =%6.2f%%\r",
                               rx_prev,rz_prev,
                               prev.y%512,prev.z%512,
                               total_voxels_column,
                               total_columns,
                               100.0*(float)total_columns/(512.0*512.0));

                    }

                    prev_xx=prev.y;
                    total_voxels_column=0;
                    min_x=std::min(min_x,prev.x);
                    max_x=std::max(max_x,prev.x);
                    min_y=std::min(min_y,prev.y%512);
                    max_y=std::max(max_y,prev.y%512);
                    min_z=std::min(min_z,prev.z%512);
                    max_z=std::max(max_z,prev.z%512);
                }
                hit_one_region* hit_one=findRegion(rx_prev,rz_prev);
                if (hit_one==NULL) {
                    vector_hit_regions.push_back(hit_one_region(rx_prev,rz_prev));
                    hit_one=&(*vector_hit_regions.end());
                }
                if (new_hits_region) {
                    if (!flushing) {
                        scan_x=rx_prev;
                        scan_z=rz_prev;
                        sprintf(mc_text1,"R.%d.%d.MCA",scan_x,scan_z);
                        sprintf(mc_text2,"%s %7d HITS",fn.c_str(),new_hits_region);

                        if (hit_one->index11 == 0)
                            plotting=1;
                        else
                            plotting=3;

                        if (hit_regions[rx_prev][rz_prev][11]==0)
                            plotting=1;
                        else
                            plotting=3;

                        update_request=2;
                        while (update_request) {
                            sf::sleep(sf::seconds(0.005));
                        }
                    } else {
                        scan_image.create(512,512,sf::Color(0,0,0,0));
                    }
                    region_counter[rx_prev][rz_prev]++;
                    hit_one->index12++;
                }
                hit_one->index0=min_x;
                hit_one->index1=max_x;
                hit_one->index2=min_y;
                hit_one->index3=max_y;
                hit_one->index4=min_z;
                hit_one->index5=max_z;
                hit_one->index6=total_voxels_region;
                hit_one->index7=total_hits_region;
                hit_one->index8=total_columns;
                if (xz00 && xz01 && xz10 && xz11) hit_one->index9=1;
                else hit_one->index9=0;
                hit_one->index10=new_hits_region;

                hit_regions[rx_prev][rz_prev][0]=min_x;
                hit_regions[rx_prev][rz_prev][1]=max_x;
                hit_regions[rx_prev][rz_prev][2]=min_y;
                hit_regions[rx_prev][rz_prev][3]=max_y;
                hit_regions[rx_prev][rz_prev][4]=min_z;
                hit_regions[rx_prev][rz_prev][5]=max_z;
                hit_regions[rx_prev][rz_prev][6]=total_voxels_region;
                hit_regions[rx_prev][rz_prev][7]=total_hits_region;
                hit_regions[rx_prev][rz_prev][8]=total_columns;
                if (xz00 && xz01 && xz10 && xz11) hit_regions[rx_prev][rz_prev][9]=1;
                else hit_regions[rx_prev][rz_prev][9]=0;
                hit_regions[rx_prev][rz_prev][10]=new_hits_region;

                plot_region=false;

                printf("\rREGION [%3d][%3d] ",rx_prev,rz_prev);
                total_columns=0;
                int total_voxels=0;
                for (int zz=0; zz<512; zz++) {
                    for (int xx=0; xx<512; xx++) {
                        if (one_region[xx][zz]>0) {
                            total_columns++;
                            total_voxels+=one_region[xx][zz];
                        }
                        one_region[xx][zz]=0;
                    }
                }

                printf("NEW HITS=%7d  VOXELS=%9d  ", hit_regions[rx_prev][rz_prev][10], total_voxels);
                printf("%7d  ", total_voxels_region);
                printf("HITS=%10d  ", total_hits_region);
                printf("RR=[%3d-%3d] Y=[%4d-%4d] ZZ=[%3d-%3d]  ",min_y,max_y,min_x,max_x,min_z,max_z);
//                printf("MIN RR=%3d Y=%3d ZZ=%3d  ", min_y,min_x,min_z);
//                printf("MAX RR=%3d Y=%3d ZZ=%3d  ", max_y,max_x,max_z);
                printf("HITS/VOXEL=%6.2f  ", (double)total_hits_region/(double)total_voxels_region );
                printf("COLUMNS=%6d (%6.2f%%)\r", total_columns,100.0*(double)total_columns/(512.0*512.0) );

                total_voxels_all_regions+=total_voxels_region;
                total_voxels_region=0;
                total_hits_all_regions+=total_hits_region;
                total_hits_region=0;
                min_x=std::numeric_limits<int>::max();
                max_x=-std::numeric_limits<int>::max();
                min_y=std::numeric_limits<int>::max();
                max_y=-std::numeric_limits<int>::max();
                min_z=std::numeric_limits<int>::max();
                max_z=-std::numeric_limits<int>::max();
//                printf("\n");

                voxel_index++;
            }

            printf("\r");
            printf("TOTAL VOXELS:                        %9d  ",total_voxels_all_regions);
            printf("TOTAL HITS:                         %10d  ",total_hits_all_regions);
            printf("HITS/VOXEL=%6.2f                               \n", (double)total_hits_all_regions/(double)total_voxels_all_regions );

            total_voxels_all_regions=0;
            total_hits_all_regions=0;
            int total_columns_all_regions=0;
            printf("TESTING HIT REGIONS:\n");
            int NUMBER_OF_REGIONS=0;
            for (int x=0; x<1000; x++) {
                for (int z=0; z<1000; z++) {
                    if (hit_regions[x][z][6]>0) {
                        NUMBER_OF_REGIONS++;
                        printf("REGION [%3d][%3d]  ",x,z);
                        printf("VOXELS=%9d (%6.2f%%)  ", hit_regions[x][z][6],100.0*(double)hit_regions[x][z][6]/(512.0*512.0*256.0));
//                        printf("MIN RR=%3d Y=%3d ZZ=%3d  ", hit_regions[x][z][2],hit_regions[x][z][0],hit_regions[x][z][4]);
//                        printf("MAX RR=%3d Y=%3d ZZ=%3d ", hit_regions[x][z][3],hit_regions[x][z][1],hit_regions[x][z][5]);

                        printf("RR=[%3d-%3d] Y=[%4d-%4d] ZZ=[%3d-%3d]  ",
                                hit_regions[x][z][2],hit_regions[x][z][3],
                                hit_regions[x][z][0],hit_regions[x][z][1],
                                hit_regions[x][z][4],hit_regions[x][z][5]);

                        printf("COLUMNS=%6d (%6.2f%%)  ", hit_regions[x][z][8],100.0*(double)hit_regions[x][z][8]/(512.0*512.0));
                        printf("HITS=%10d HITS/VOXEL=%6.2f  ", hit_regions[x][z][7], (double)hit_regions[x][z][7]/(double)hit_regions[x][z][6]);

                        if (hit_regions[x][z][2]==0 && hit_regions[x][z][3]==511) printf("X+"); else printf("  ");
                        if (hit_regions[x][z][4]==0 && hit_regions[x][z][5]==511) printf("Z+"); else printf("  ");
                        if (hit_regions[x][z][11]) printf(" SAVED");
                        else printf(" HOLD ");
                        if (hit_regions[x][z][8]==512*512) printf(" COLUMNS=100%%");
                        if (hit_regions[x][z][9]) printf(" CORNERS=4");
                        if (hit_regions[x][z][6]!=hit_regions[x][z][10] && hit_regions[x][z][10]!=0) {
                            printf(" NEW=%d",hit_regions[x][z][10]);
                        }
                        printf("\n");
                        total_voxels_all_regions+=hit_regions[x][z][6];
                        total_hits_all_regions+=hit_regions[x][z][7];
                        total_columns_all_regions+=hit_regions[x][z][8];
                    }
                }
            }
            printf("TOTAL VOXELS:                        %9d  ",total_voxels_all_regions);
            printf("TOTAL HITS:                         %10d  ", total_hits_all_regions);
            printf("TOTAL HITS/VOXEL=%f  ", (double)total_hits_all_regions/(double)total_voxels_all_regions );
            printf("AVG COLUMNS/REGION=%6.2f%%\n", 100.0*(double)total_columns_all_regions/(512*512*NUMBER_OF_REGIONS) );
            printf("NEW NUMBER OF TOTAL VOXELS:          %9d  ",voxels_total.size());
            total_hits=0;
            int total_new=0;
//            for (auto u : voxels_total) {
            for (int n=0; n<voxels_total.size(); n++) {
//                if (u.status==0) {
//                    u.status=1;
//                    total_new++;
//                }
//                total_hits+=u.l;
                if (voxels_total[n].status==0) {
                    voxels_total[n].status=1;
                    total_new++;
                }
                total_hits+=voxels_temp[n].l;
            }
            printf("NEW NUMBER OF TOTAL HITS:           %10d\n",total_hits);
            printf("TOTAL NEW VOXELS:                    %9d\n",total_new);
        }

        printf("%3d buffers. Ready.\n",buffers.size());
    }

    if (voxels_total.size()>0) {
//        if (voxels_total.size()>200000000) flushing=true;
        if (flushing) printf("FLUSHING:\n");
        int NUMBER_OF_REGIONS=0;
        for (int x=0; x<1000; x++) {
            for (int z=0; z<1000; z++) {
                if (hit_regions[x][z][6]>0) {
                    NUMBER_OF_REGIONS++;
                    if ((voxels_total.size()>200000000) || hit_regions[x][z][8]==512*512 || hit_regions[x][z][9] || flushing || hit_regions[x][z][11]) {
                        if (hit_regions[x][z][11])
                            printf("UPDATING REGION [%3d][%3d]  ",x,z);
                        else
                            printf("CREATING REGION [%3d][%3d]  ",x,z);
                        if (hit_regions[x][z][8]==512*512) printf(" COLUMNS=100%% ");
                        if (hit_regions[x][z][9]) printf(" 4 CORNERS ");
//                        unsigned char *mc2 = (unsigned char*) malloc(512*256*512*4);
                        int first=-1;
                        int hits=0;
                        int voxels=0;
                        int count=0;
                        int columns=0;
                        int prev_x=-1,prev_z=-1;
//                        if (voxel_to_file) {
//                            char fname[200]; sprintf (fname,"../cut/r.%d.%d.vox",x,z);
//                            voxel_file_pointer=fopen(fname,"a");
//                            printf("Outputing voxels to %s\n",fname);
//                        }
                        int TOP_MIN=0;
                        int TOP_MAX=220;
                        int TOPPED_MIN=0;
                        int TOPPED_MAX=0;
                        std::memset(mc2, 0x0, 512*256*512*4);
                        for (auto u : voxels_total) {
                            if ( (int)(u.y/512)==x && (int)(u.z/512)==z ) {
                                if (prev_x!=u.y || prev_z!=u.z) columns++;
                                prev_x=u.y; prev_z=u.z;
                                if (first==-1) first=count;
                                hits+=u.l;
                                if (!(voxels%4096)) printf("count=%d  first=%d  voxels=%d  hits=%d  columns=%d (%6.2f%%)\r",
                                                          count, first, voxels, hits, columns, 100.0*(double)columns/(512.0*512.0));
//                                if (u.l>0 && voxel_to_file) {
//                                    fprintf(voxel_file_pointer,"(%d,%d,%d),(%d,%d,%d),(%d)\n",
//                                            u.y, u.x, u.z,  u.r/u.l,u.g/u.l, u.b/u.l,  u.l );
//                                }
                                if (!plot_only_on) {
                                    if (u.x>=0 && u.x<220 && u.l>0) {
                                        size_t off_x=(u.x+256*(u.y%512)+(u.z%512)*512*256)*4;
                                        mc2[off_x]=u.r/u.l;
                                        mc2[off_x+1]=u.g/u.l;
                                        mc2[off_x+2]=u.b/u.l;
                                        mc2[off_x+3]=u.l;
                                    } else if (u.l>0) {
                                        if (u.x<1) {
                                            if (u.x<TOP_MIN) TOP_MIN=u.x;
                                            TOPPED_MIN++;
                                            size_t off_x=(1+256*(u.y%512)+(u.z%512)*512*256)*4;
                                            mc2[off_x]=u.r/u.l;
                                            mc2[off_x+1]=u.g/u.l;
                                            mc2[off_x+2]=u.b/u.l;
                                            mc2[off_x+3]=u.l;
                                        } else if (u.x>=220) {
                                            if (u.x>TOP_MAX) TOP_MAX=u.x;
                                            TOPPED_MAX++;
                                            float togo=u.x-220;
                                            float new_real_y=220+togo/(1.0+(togo/60.0)); if (new_real_y>=256.) new_real_y=255.0;
                                            size_t off_x=((int)new_real_y+256*(u.y%512)+(u.z%512)*512*256)*4;
                                            mc2[off_x]=u.r/u.l;
                                            mc2[off_x+1]=u.g/u.l;
                                            mc2[off_x+2]=u.b/u.l;
                                            mc2[off_x+3]=u.l;
                                        }
                                    } else {
                                        printf("ERROR: u.l=0\n");
                                    }
                                }
                                voxels++;
                            }
                            count++;
                        }
                        printf("                                                                                                                            \n");
                        if (TOPPED_MIN>0) printf("TOPPED_MIN=%d (MIN=%d)\n",TOPPED_MIN,TOP_MIN);
                        if (TOPPED_MAX>0) printf("TOPPED_MAX=%d (MAX=%d)\n",TOPPED_MAX,TOP_MAX);
//                        if (voxel_file_pointer!=NULL) fclose(voxel_file_pointer);
                        if (voxels==0 || hits==0 || first==-1 || count==0) {
                            printf("\nERROR: count=%d  first=%d  voxels=%d  hits=%d\n",count, first, voxels, hits);
                        } else {
                            printf("\rTOTAL: VOXELS %d  HITS: %d  FROM %d to %d  COLUMNS: %d  Creating region file r.%d.%d..mca\n",
                                   voxels, hits, first, first+voxels, columns, x,z);
                            plotting=0;
                            hit_regions[x][z][11]++;
                            if (hit_regions[x][z][11]==1) sprintf(mc_text2,"SAVING");
                            else sprintf(mc_text2,"SAVING %d",hit_regions[x][z][11]);
                            region_counter[x][z]=0;
                            if (!plot_only_on) {
//                                scan_image.create(512,512,sf::Color(0,0,0,0));
                                MCEDITOR_running=1;
                                main_mceditor6_fixed(x,z,mc2);
                                MCEDITOR_running=0;
                            }


                            printf("Deleting array: ");
                            printf("Ok.  Erasing region from total voxels:\n");
                            printf("Size voxels_total:     %10d\n",voxels_total.size());
                            voxels_total.erase(voxels_total.begin()+first,voxels_total.begin()+first+voxels);
                            printf("Erased voxels:         %10d\n",voxels);
                            printf("New size voxels_total: %10d\n",voxels_total.size());
                            printf("New size + voxels:     %10d\n",voxels_total.size()+voxels);
                        }
                    }
                }
            }
        }
        if (voxel_to_file) {
            char fname[200]; sprintf (fname,"../cut/%s.VOX",area.c_str());
            voxel_file_pointer=fopen(fname,"w");
            printf("Outputing voxels to %s\n",fname);
            for (auto u : voxels_total) {
                if (u.l>0 && voxel_to_file) {
                    fprintf(voxel_file_pointer,"(%d,%d,%d),(%d,%d,%d),(%d)\n",
                            u.y, u.x, u.z,  u.r/u.l,u.g/u.l, u.b/u.l,  u.l );
                }
            }
            if (voxel_file_pointer!=NULL) fclose(voxel_file_pointer);
            voxel_to_file=false;
        }

    }
    if (!plot_only_on) {
        char naam[200];
        mkdir("../cut/done");
        sprintf(naam,"move ..\\cut\\%s.* ..\\cut\\done\\",fn.c_str());
        system(naam);
    }
    if (!plot_only_on) free(mc2);
    wuppie_all=true;
    return ;
}

*/


//void WUPPIE(std::vector<BufferObject> buffers, std::vector<tinyobj::material_t> &materials, float bmin_o[3], float bmax_o[3], double lat, double lon, std::string fn);

/*

void WUPPIE(std::vector<BufferObject> buffers, std::vector<tinyobj::material_t> &materials, float bmin_o[3], float bmax_o[3], double lat, double lon, std::string fn) {
    int flop=0;
    char new_file[100];
    sprintf(new_file,"../cut/%s.RAW",fn.c_str());
    if (file_exists(new_file)) {
        printf("%s exists\n",new_file);
        sprintf(new_file,"../cut/%s.DAT",fn.c_str());
        if (file_exists(new_file)) {
            printf("And %s exists, exiting\n",new_file,new_file);
            return;
        } else {
            printf("%s doesn't exists\n",new_file);
        }
    } else {
        if (wuppie_all) printf("%s doesn't exists\n",new_file);
    }

    double bmin_total[3];
    double bmax_total[3];
    char dat_name[200];
    char line[200];
    sprintf(dat_name,"%s.DAT",area.c_str());
    FILE* HOP;
    if ((HOP = fopen (dat_name, "r"))!=NULL) {
        if (fgets (line,200, HOP)!=NULL) {
            while (replace_str(line,".",","));
            sscanf(line,"TOTAL MIN: X=%lf Y=%lf Z=%lf\n",&bmin_total[0],&bmin_total[1],&bmin_total[2]);
        }
        if (fgets (line,200, HOP)!=NULL) {
            while (replace_str(line,".",","));
            sscanf(line,"TOTAL MAX: X=%lf Y=%lf Z=%lf\n",&bmax_total[0],&bmax_total[1],&bmax_total[2]);
        }
        fclose(HOP);
    } else {
        printf("Error reading %s\n",dat_name);
    }

//    unsigned char* image;
//    sf::Image *sfml_image;

    int o_tot_hits=0;
    int o_tot_blocks=0;

    BufferObject one_buffer;

//    glm::vec3 NORMALz;
//    glm::mat4 test(1.0f);

//    double tx;
//    double ty;
//    double tz;

    double bmin[3];
    double bmax[3];

    int buf_count=0;

    bmin[0] = bmin[1] = bmin[2] = std::numeric_limits<double>::max();
    bmax[0] = bmax[1] = bmax[2] = -std::numeric_limits<double>::max();

    bmin_total[0]=-23.0;
    bmax_total[0]=145.0;
    double block_scale=500.0/(bmax_total[0]-bmin_total[0]);

    for (auto u : buffers) {
        one_buffer=u;

        int num_faces=(one_buffer.length-sizeof(int)) / (3 + 3 + 3 + 2) / 3 / sizeof(float);     // 3:vtx, 3:normal, 3:col, 2:texcoord
        float v[3][3];
//        float n[3][3];
//        float c[3][3];
        float tc[3][2];
        int stride = (3 + 3 + 2 + 3);
        float* real_buffer = (float*)(one_buffer.buffer + sizeof(int));
        float* VertexPointer=real_buffer;
//        float* NormalPointer=real_buffer + 3;
//        float* ColorPointer=real_buffer + 6;
        float* TexCoordPointer=real_buffer + 9;
//        float* TexCoordPointer=real_buffer + 9;
        int mat_id;
        memcpy(&mat_id,one_buffer.buffer,sizeof(int));

        static bool no_texture;
        int w=0;
        int h=0;
        if (mat_id < materials.size()-1)
        {
            if (!image_buffer[mat_id]->ok) {
//                image=0;
                printf("Image not ok!!!!\n");
            }
            else {
                w=image_buffer[mat_id]->image->getSize().x;
                h=image_buffer[mat_id]->image->getSize().y;
//                image=(unsigned char*)image_buffer[mat_id]->image->getPixelsPtr();
//                sfml_image=image_buffer[mat_id]->image;
//                printf("Material id: %3d  w=%3d , h=%3d  ",mat_id,w,h);
            }
            no_texture=false;
        } else {
            printf("No material id: %d\n",mat_id);
            sf::sleep(sf::seconds(2.0));
            no_texture=true;
        }
        sf::Image image_copy; //dummy
        sf::Image* image=image_buffer[mat_id]->image;

        for (int faces=0; faces<num_faces; faces++) {
            for (int l=0; l<3; l++) {
                int offset=(stride*(l+faces*3));
                for (int k=0; k<3; k++) {
                    if (offset*sizeof(float) >= one_buffer.length-sizeof(int)) {
                        printf("Error offset\n");
                        return;
                    }
                    v[l][k]=VertexPointer[offset+k]*block_scale;
//                    n[l][k]=NormalPointer[offset+k];
//                    c[l][k]=ColorPointer[offset+k];
                    if (k<2) tc[l][k]=TexCoordPointer[offset+k];
                } //point

                glm::vec3 hop = glm::vec4(v[l][0], v[l][1], v[l][2], 1.0f);

                bmin[0]=std::min((double)hop.x, bmin[0]);   bmax[0]=std::max((double)hop.x, bmax[0]);
                bmin[1]=std::min((double)hop.y, bmin[1]);   bmax[1]=std::max((double)hop.y, bmax[1]);
                bmin[2]=std::min((double)hop.z, bmin[2]);   bmax[2]=std::max((double)hop.z, bmax[2]);
            } // triangle
        } // faces
    } //buffers

    double mid_block[3];
    for (int n=0; n<3; n++) {
        mid_block[n]=(bmax[n]-bmin[n])/2.0;
        bmin[n]=(bmin[n] - mid_block[n])*1.001 + mid_block[n];
        bmax[n]=(bmax[n] - mid_block[n])*1.001 + mid_block[n];
    }

//    for (int n=0; n<3; n++) {
//        bmin[n]=bmin[n]*block_scale;
//        bmax[n]=bmax[n]*block_scale;
//        bmin[n]=bmin_o[n]*block_scale;
//        bmax[n]=bmax_o[n]*block_scale;
//    }

    int box_x_block_start=bmin[0];
    int box_y_block_start=bmin[1];
    int box_z_block_start=bmin[2];

    int box_x_block_end=bmax[0];
    int box_y_block_end=bmax[1];
    int box_z_block_end=bmax[2];

    int box_x_total_start=bmin_total[0]*block_scale;
    int box_y_total_start=bmin_total[1]*block_scale;
    int box_z_total_start=bmin_total[2]*block_scale;

    int box_x_total_end=bmax_total[0]*block_scale;
    int box_y_total_end=bmax_total[1]*block_scale;
    int box_z_total_end=bmax_total[2]*block_scale;

    int box_x=box_x_block_end-box_x_block_start+1;
    if (wuppie_all) {
        if (box_x>255) box_x=255;
    }
    int box_y=box_y_block_end-box_y_block_start+1;
    int box_z=box_z_block_end-box_z_block_start+1;

    offset_real_y=box_x_block_start - box_x_total_start;

    if (wuppie_all) {
        printf("\n");
        printf("box_x_block_start=%6d   box_y_block_start=%6d   box_z_block_start=%6d\n",box_x_block_start,box_y_block_start,box_z_block_start);
        printf("box_x_block_end  =%6d   box_y_block_end  =%6d   box_z_block_end  =%6d\n",box_x_block_end,box_y_block_end,box_z_block_end);
        printf("dif_x_block      =%6d   dif_y_block      =%6d   dif_z_block      =%6d\n",box_x_block_end-box_x_block_start,box_y_block_end-box_y_block_start,box_z_block_end-box_z_block_start);
        printf("\n");
        printf("box_x_total_start=%6d   box_y_total_start=%6d   box_z_total_start=%6d\n",box_x_total_start,box_y_total_start,box_z_total_start);
        printf("box_x_total_end=  %6d   box_y_total_end=  %6d   box_z_total_end=  %6d\n",box_x_total_end,box_y_total_end,box_z_total_end);
        printf("dif_x_total      =%6d   dif_y_total      =%6d   dif_z_total      =%6d\n",box_x_total_end-box_x_total_start,box_y_total_end-box_y_total_start,box_z_total_end-box_z_total_start);
        printf("\n");
        printf("Setting           %6d                     %6d                     %6d\n", box_x, box_y, box_z);
        printf("\n");
    }

    LONG64 tot_off=box_x*box_y*box_z*4;
    LONG64 tot_off_x=box_y*box_z*4;

    if (wuppie_all) printf("Setting %dx%dx%dx4x2 bytes=%u bytes ", box_x, box_y, box_z, tot_off*2);

    unsigned short **mc_sub = (unsigned short **) malloc( sizeof(unsigned short *) * box_x);
    if (mc_sub==NULL)  {     printf("Error allocating memory mc_sub\n");      return;    }
    for (int cube_x=0; cube_x<box_x; cube_x++) {
        mc_sub[cube_x] = (unsigned short *) malloc( sizeof(unsigned short) * tot_off_x);
        if (mc_sub[cube_x]==NULL)  {         printf("Error allocating memory mc_sub\n");        return;    }
        std::memset(mc_sub[cube_x], 0x0, sizeof(unsigned short) * tot_off_x);  //short
    }

    char filename[2000];
    std::ofstream ofs;
    if (wuppie_all) {
        sprintf(filename, "../cut/voxel.dat");
    } else {
        sprintf(filename, "../cut/%s.DAT",fn.c_str());
    }

    if (wuppie_all) printf("Writing %s ...",filename);
    ofs.open(filename);
    ofs << "X=" << box_x << " Y=" << box_y << " Z=" << box_z << "\n";
    ofs << "OCTANT=" << fn.c_str() << "\n";
    ofs << "BYTES=" << tot_off << "\n";
    ofs << "ABS MIN X=" << box_x_block_start << " Y=" << box_y_block_start << " Z=" << box_z_block_start << "\n";
    ofs << "ABS MAX X=" << box_x_block_end   << " Y=" << box_y_block_end   << " Z=" << box_z_block_end   << "\n";
    ofs << "TOTAL MIN X=" << box_x_total_start << " Y=" << box_y_total_start << " Z=" << box_z_total_start << "\n";
    ofs << "TOTAL MAX X=" << box_x_total_end   << " Y=" << box_y_total_end   << " Z=" << box_z_total_end   << "\n";
    ofs << "AREA=" << area   << "\n";

    ofs.close();
    if (wuppie_all) printf("Ready\n");

    if (wuppie_all) {
        sprintf(new_file,"../cut/%s.DAT",fn.c_str());
        CopyFile("../cut/voxel.dat",new_file,false);
    }

    FILE* pFile;
    if (wuppie_all) printf("Ready\n");

    int offset_x=box_x_block_start;
    int offset_y=box_y_block_start;
    int offset_z=box_z_block_start;
    double offset_xyz[3]={offset_x, offset_y, offset_z};
//    int offset_x=box_x_block_start+1;
//    int offset_y=box_y_block_start+1;
//    int offset_z=box_z_block_start+1;

//    bmin[0] = bmin[1] = bmin[2] = std::numeric_limits<double>::max();
//    bmax[0] = bmax[1] = bmax[2] = -std::numeric_limits<double>::max();

    buf_count=0;
    int tot_faces=0;

    bool hit_cube_y_start=false;
    bool hit_cube_y_end=false;
    bool hit_cube_z_start=false;
    bool hit_cube_z_end=false;

    double bmin_org[3];
    double bmax_org[3];

    for (auto u : buffers) {
        one_buffer=u;

        bmin_org[0] = bmin_org[1] = bmin_org[2] = std::numeric_limits<double>::max();
        bmax_org[0] = bmax_org[1] = bmax_org[2] = -std::numeric_limits<double>::max();

        int num_faces=(one_buffer.length-sizeof(int)) / (3 + 3 + 3 + 2) / 3 / sizeof(float);     // 3:vtx, 3:normal, 3:col, 2:texcoord
        double v[3][3];
//        float n[3][3];
//        float c[3][3];
        double tc[3][2];
        int stride = (3 + 3 + 2 + 3);
        float* real_buffer = (float*)(one_buffer.buffer + sizeof(int));
        float* VertexPointer=real_buffer;
//        float* NormalPointer=real_buffer + 3;
//        float* ColorPointer=real_buffer + 6;
        float* TexCoordPointer=real_buffer + 9;
//        float* TexCoordPointer=real_buffer + 9;
        int mat_id;
        memcpy(&mat_id,one_buffer.buffer,sizeof(int));

        static bool no_texture;
        int w=0;
        int h=0;
        if (mat_id < materials.size()-1)
        {
            if (!image_buffer[mat_id]->ok) {
//                image=0;
                printf("Image not ok!!!!\n");
            }
            else {
                w=image_buffer[mat_id]->image->getSize().x;
                h=image_buffer[mat_id]->image->getSize().y;
//                image=(unsigned char*)image_buffer[mat_id]->image->getPixelsPtr();
//                sfml_image=image_buffer[mat_id]->image;
//                printf("Material id: %3d  w=%3d , h=%3d  ",mat_id,w,h);
            }
            no_texture=false;
        } else {
            printf("No material id: %d\n",mat_id);
            sf::sleep(sf::seconds(2.0));
            no_texture=true;
        }
        sf::Image image_copy; //dummy
        sf::Image* image=image_buffer[mat_id]->image;

        for (int faces=0; faces<num_faces; faces++) {
            for (int l=0; l<3; l++) {
                int offset=(stride*(l+faces*3));
                for (int k=0; k<3; k++) {
                    if (offset*sizeof(float) >= one_buffer.length-sizeof(int)) {
                        printf("Error offset\n");
                        return;
                    }
                    v[l][k]=VertexPointer[offset+k]*block_scale-offset_xyz[k];
                    v[l][k]=(v[l][k] - mid_block[k])*1.001 + mid_block[k];
//                    n[l][k]=NormalPointer[offset+k];
//                    c[l][k]=ColorPointer[offset+k];
                    if (k<2) tc[l][k]=TexCoordPointer[offset+k];
                } //point

                glm::vec4 hop = glm::vec4(v[l][0], v[l][1], v[l][2], 1.0f);

                bmin_org[0]=std::min((double)hop.x, bmin_org[0]);   bmax_org[0]=std::max((double)hop.x, bmax_org[0]);
                bmin_org[1]=std::min((double)hop.y, bmin_org[1]);   bmax_org[1]=std::max((double)hop.y, bmax_org[1]);
                bmin_org[2]=std::min((double)hop.z, bmin_org[2]);   bmax_org[2]=std::max((double)hop.z, bmax_org[2]);

            } // triangle

            warning_done_y=false;
            warning_done_z=false;

           if (!no_texture) magic(v,tc,image_buffer[mat_id], buf_count, faces,image_copy, offset_x, offset_y, offset_z, box_x, box_y, box_z, mc_sub, block_scale);

        } // faces

        warning_done_x=false;
        warning_done_topping=false;
//        if (wuppie_all)
            printf("Material id: %3d  w=%3d , h=%3d  ",mat_id,w,h);
//        if (wuppie_all)
            printf("Total: buffer: %3d/%3d  Faces: %7d  ==>  bmin=%-+7.2f %-+7.2f %-+7.2f  bmax=%-+7.2f %-+7.2f %-+7.2f  diff=%-+7.2f %-+7.2f %-+7.2f\n",
                buf_count+1, buffers.size(),num_faces,
                bmin_org[0],bmin_org[1],bmin_org[2],bmax_org[0],bmax_org[1],bmax_org[2],
                bmax_org[0]-bmin_org[0],bmax_org[1]-bmin_org[1],bmax_org[2]-bmin_org[2]);

        buf_count++;
        tot_faces+=num_faces;
    } //buffers


    if (wuppie_all) printf("\nRecalc\n");

    for (int cube_z=0; cube_z<box_z; cube_z++) {
        for (int cube_y=0; cube_y<box_y; cube_y++) {
            int max_x=-1;
            size_t off_x=(cube_y+cube_z*box_y)*4;
            for (int cube_x=0; cube_x<box_x; cube_x++) {
                float num=mc_sub[cube_x][off_x+3];
                if (num>0) {
                    mc_sub[cube_x][off_x+0]=(unsigned short)((float)mc_sub[cube_x][off_x+0]/num);
                    mc_sub[cube_x][off_x+1]=(unsigned short)((float)mc_sub[cube_x][off_x+1]/num);
                    mc_sub[cube_x][off_x+2]=(unsigned short)((float)mc_sub[cube_x][off_x+2]/num);
                }
            }
        }
    }

    if (wuppie_all) {
        if (file_exists("../cut/voxel.raw")) system("del ..\\cut\\voxel.raw");
        sprintf(filename, "../cut/voxel.raw");
        printf("Writing %s ...",filename);
    }
//    sprintf(new_file,"../cut/%s.DAT",fn.c_str());

    if (wuppie_all) pFile = fopen ( "../cut/voxel.raw" , "wb" );
    else {
        sprintf(new_file,"../cut/%s.RAW",fn.c_str());
        pFile = fopen ( new_file , "wb" );
    }

    unsigned char out[box_x*4];

    for (int cube_z=0; cube_z<box_z; cube_z++) {
        for (int cube_y=0; cube_y<box_y; cube_y++) {
            for (int cube_x=0; cube_x<box_x; cube_x++) {
//ayay2
                size_t off_x=(cube_y+cube_z*box_y)*4;
//                size_t off=(cube_x+cube_y*box_x+cube_z*box_x*box_y)*4;
                out[cube_x*4] =(unsigned char)  mc_sub[cube_x][off_x];
                out[cube_x*4+1]=(unsigned char) mc_sub[cube_x][off_x+1];
                out[cube_x*4+2]=(unsigned char) mc_sub[cube_x][off_x+2];
                out[cube_x*4+3]=(unsigned char) mc_sub[cube_x][off_x+3];
//                out[cube_x*4] =(unsigned char)  mc[off];
//                out[cube_x*4+1]=(unsigned char) mc[off+1];
//                out[cube_x*4+2]=(unsigned char) mc[off+2];
//                out[cube_x*4+3]=(unsigned char) mc[off+3];
            }
            fwrite( out, box_x*4, 1, pFile );
            toggle2();
        }
    }

//    fwrite( mc, tot_off*2, 1, pFile );
    fclose(pFile);


    if (wuppie_all) printf("Clearing memory ");

    for (int cube_x=0; cube_x<box_x; cube_x++) {
        free(mc_sub[cube_x]);
//        delete [] mc_sub[cube_x];
    }
    free(mc_sub);

//    delete [] mc_sub;

//    delete [] mc;

//extern char *backup;
    //delete [] backup;

    if (wuppie_all) printf(" Ready.\n");

    sprintf(new_file,"../cut/%s.RAW",fn.c_str());
    if (wuppie_all) {
        printf("Copying %s to %s...","../cut/voxel.raw",new_file);
        CopyFile("../cut/voxel.raw",new_file,false);
        printf(" Ready.\n");
    }

    if (wuppie_all) printf("Setting %d x %d x %d x 4 : bytes=%u bytes ", box_x, box_y, box_z, tot_off);

    unsigned char *mc2 = new unsigned char [tot_off];
    if (mc2!=NULL) {
            if (wuppie_all) printf("OK!\n");
    } else {
        printf("Error allocating memory\n");
        return;
    }

    std::memset(mc2, 0x0, tot_off);  //short

    if (wuppie_all) {
        printf("Reading file ../cut/voxel.raw ");
        pFile = fopen ( "../cut/voxel.raw" , "rb" );
        size_t result = fread(mc2,1,tot_off,pFile);
        fclose(pFile);
        printf("%u bytes\n",result);
    } else {
        pFile = fopen ( new_file , "rb" );
        size_t result = fread(mc2,1,tot_off,pFile);
        fclose(pFile);
    }

extern char mc_text2[];
    if (!plotting) sprintf(mc_text2,"%s",fn.c_str());
    else sprintf(mc_text2,"");

    if (plotting) {
        main_mceditor6_plot(
            box_x, box_y, box_z,
            mc2,
            box_x_block_start,                      box_y_block_start-2048,                     box_z_block_start+2048,
            box_x_total_start,                      box_y_total_end,                            box_z_total_start
        );
    } else {
        main_mceditor6(
            box_x, box_y, box_z,
            mc2,
            box_x_block_start,                      box_y_block_start-2048,                     box_z_block_start+2048,
            box_x_total_start,                      box_y_total_end,                            box_z_total_start
        );
    }

    delete [] mc2;
    if (!plotting) {
        char naam[200];
        mkdir("../cut/done");
        sprintf(naam,"move ..\\cut\\%s.* ..\\cut\\done\\",fn.c_str());
        system(naam);
    }
}
*/
