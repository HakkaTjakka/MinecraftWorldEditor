
void WUPPIE2(std::vector<BufferObject> buffers, std::vector<tinyobj::material_t> &materials, float bmin_o[3], float bmax_o[3], double lat, double lon, std::string fn) {
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
        bmin_total[0]=bmin_total[0];
        bmin_total[1]=bmin_total[1];
        bmin_total[2]=bmin_total[2];
        bmax_total[0]=bmax_total[0];
        bmax_total[1]=bmax_total[1];
        bmax_total[2]=bmax_total[2];
//        printf("TOTAL: bmin = % 24.13f, % 24.13f, % 24.13f\n", bmin_total[0],                   bmin_total[1],                  bmin_total[2]);
//        printf("TOTAL: bmax = % 24.13f, % 24.13f, % 24.13f\n", bmax_total[0],                   bmax_total[1],                  bmax_total[2]);
//        printf("TOTAL: diff = % 24.13f, % 24.13f, % 24.13f\n", bmax_total[0]-bmin_total[0],     bmax_total[1]-bmin_total[1],    bmax_total[2]-bmin_total[2]);
    } else {
        printf("Error reading %s\n",dat_name);
    }


    unsigned char* image;
    sf::Image *sfml_image;

    int o_tot_hits=0;
    int o_tot_blocks=0;

//    unsigned char part[512][256][512];
    BufferObject one_buffer;

    glm::vec3 NORMALz;
    glm::mat4 test(1.0f);

    double tx;
    double ty;
    double tz;

//    printf("(original)\n");
//    printf("bmin = % 24.13f, % 24.13f, % 24.13f\n", bmin[0],           bmin[1],            bmin[2]);
//    printf("bmax = % 24.13f, % 24.13f, % 24.13f\n", bmax[0],           bmax[1],            bmax[2]);
//    printf("diff = % 24.13f, % 24.13f, % 24.13f\n", bmax[0]-bmin[0],   bmax[1]-bmin[1],    bmax[2]-bmin[2]);

//    tx=-0.5 * (bmax_o[0] + bmin_o[0]);
//    ty=-0.5 * (bmax_o[1] + bmin_o[1]);
//    tz=-0.5 * (bmax_o[2] + bmin_o[2]);

    double bmin_org[3];
    double bmax_org[3];
//    double bmin_triangle[3];
//    double bmax_triangle[3];
    double bmin[3];
    double bmax[3];
    double prev_bmin_org[3]={0,0,0};;
    double prev_bmax_org[3]={0,0,0};;
//    double bmin_pixel[2];
//    double bmax_pixel[2];

//    printf("lat=%lf  lon=%lf\n",lat,lon);
    bmin[0] = bmin[1] = bmin[2] = std::numeric_limits<double>::max();
    bmax[0] = bmax[1] = bmax[2] = -std::numeric_limits<double>::max();
//    NORMALz = glm::vec3((float)(cos(lat*M_PI/180.0)*cos(lon*M_PI/180.0)), (float)(cos(lat*M_PI/180)*sin(lon*M_PI/180)), (float)(sin(lat*M_PI/180)));
//    NORMALz = glm::normalize(NORMALz);

//    test=glm::mat4(  cos(lat*M_PI/180.0)*cos(lon*M_PI/180.0)    , cos(lat*M_PI/180.0)*sin(lon*M_PI/180.0)   , sin(lat*M_PI/180.0)   , 0.0,
//                    -sin(lon*M_PI/180.0)                        , cos(lon*M_PI/180.0)                       , 0.0                   , 0.0,
//                    -sin(lat*M_PI/180.0)*cos(lon*M_PI/180.0)    ,-sin(lat*M_PI/180.0)*sin(lon*M_PI/180.0)   , cos(lat*M_PI/180.0)   , 0.0,
//                    0.0                                         ,0.0                                        ,0.0                    , 1.0);

    int buf_count=0;
    double bmin_buf[buffers.size()][3];
    double bmax_buf[buffers.size()][3];
    for (auto u : buffers) {
        one_buffer=u;
//        small=0;
        bmin_org[0] = bmin_org[1] = bmin_org[2] = std::numeric_limits<double>::max();
        bmax_org[0] = bmax_org[1] = bmax_org[2] = -std::numeric_limits<double>::max();

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
                image=0;
                printf("Image not ok!!!!\n");
            }
            else {
                w=image_buffer[mat_id]->image->getSize().x;
                h=image_buffer[mat_id]->image->getSize().y;
                image=(unsigned char*)image_buffer[mat_id]->image->getPixelsPtr();
                sfml_image=image_buffer[mat_id]->image;
//                printf("Material id: %3d  w=%3d , h=%3d  ",mat_id,w,h);
            }
            no_texture=false;
        } else {
            printf("No material id: %d\n",mat_id);
            sf::sleep(sf::seconds(2.0));
            no_texture=true;
        }

        for (int faces=0; faces<num_faces; faces++) {
            for (int l=0; l<3; l++) {
                int offset=(stride*(l+faces*3));
                for (int k=0; k<3; k++) {
                    if (offset*sizeof(float) >= one_buffer.length-sizeof(int)) {
                        printf("Error offset\n");
                        return;
                    }
                    v[l][k]=VertexPointer[offset+k];
//                    n[l][k]=NormalPointer[offset+k];
//                    c[l][k]=ColorPointer[offset+k];
                    if (k<2) tc[l][k]=TexCoordPointer[offset+k];
                }

                glm::vec4 hop = glm::vec4(v[l][0], v[l][1], v[l][2], 1.0f);

                bmin_org[0]=std::min((double)hop.x, bmin_org[0]);   bmax_org[0]=std::max((double)hop.x, bmax_org[0]);
                bmin_org[1]=std::min((double)hop.y, bmin_org[1]);   bmax_org[1]=std::max((double)hop.y, bmax_org[1]);
                bmin_org[2]=std::min((double)hop.z, bmin_org[2]);   bmax_org[2]=std::max((double)hop.z, bmax_org[2]);
            } // triangle
        } // faces
        if (wuppie_all) printf("Material id: %3d  w=%3d , h=%3d  ",mat_id,w,h);
        if (wuppie_all) printf("Total: buffer: %3d/%3d  Faces: %7d  ==>  bmin=%-+7.2f %-+7.2f %-+7.2f  bmax=%-+7.2f %-+7.2f %-+7.2f  diff=%-+7.2f %-+7.2f %-+7.2f\n",
                buf_count+1, buffers.size(),num_faces,
                bmin_org[0],bmin_org[1],bmin_org[2],bmax_org[0],bmax_org[1],bmax_org[2],
                bmax_org[0]-bmin_org[0],bmax_org[1]-bmin_org[1],bmax_org[2]-bmin_org[2]);
        for (int t=0; t<3; t++) {

            bmin[t]=std::min(bmin[t], bmin_org[t]);
            bmax[t]=std::max(bmax[t], bmax_org[t]);

            bmin_buf[buf_count][t]=bmin_org[t];
            bmax_buf[buf_count][t]=bmax_org[t];
        }
        buf_count++;
    } //buffers

    if (wuppie_all) printf("\n(Scanned)\n");
    if (wuppie_all) printf("       bmin = % 24.13f, % 24.13f, % 24.13f\n", bmin[0],           bmin[1],            bmin[2]);
    if (wuppie_all) printf("       bmax = % 24.13f, % 24.13f, % 24.13f\n", bmax[0],           bmax[1],            bmax[2]);
    if (wuppie_all) printf("       diff = % 24.13f, % 24.13f, % 24.13f\n", bmax[0]-bmin[0],   bmax[1]-bmin[1],    bmax[2]-bmin[2]);
    if (wuppie_all) printf("(Original)\n");
    if (wuppie_all) printf("       bmin = % 24.13f, % 24.13f, % 24.13f\n", bmin_o[0],              bmin_o[1],            bmin_o[2]);
    if (wuppie_all) printf("       bmax = % 24.13f, % 24.13f, % 24.13f\n", bmax_o[0],              bmax_o[1],            bmax_o[2]);
    if (wuppie_all) printf("       diff = % 24.13f, % 24.13f, % 24.13f\n", bmax_o[0]-bmin_o[0],    bmax_o[1]-bmin[1],    bmax_o[2]-bmin_o[2]);
    if (wuppie_all) printf("(Total)\n");
    if (wuppie_all) printf("       bmin = % 24.13f, % 24.13f, % 24.13f\n", bmin_total[0],                   bmin_total[1],                  bmin_total[2]);
    if (wuppie_all) printf("       bmax = % 24.13f, % 24.13f, % 24.13f\n", bmax_total[0],                   bmax_total[1],                  bmax_total[2]);
    if (wuppie_all) printf("       diff = % 24.13f, % 24.13f, % 24.13f\n", bmax_total[0]-bmin_total[0],     bmax_total[1]-bmin_total[1],    bmax_total[2]-bmin_total[2]);

//extern int block_count;
//extern glm::ivec3* blocks;
//extern glm::vec3* block_colors;
//extern int region_x_request;
//extern int region_z_request;

//    double bmin_total[3];
//    double bmax_total[3];
//    float bmin_org[3];
//    float bmax_org[3];
//    float bmin_triangle[3];
//    float bmax_triangle[3];
//    float bmin[3];
//    float bmax[3];
//    float prev_bmin_org[3]={0,0,0};;
//    float prev_bmax_org[3]={0,0,0};;
//    float bmin_pixel[2];
//    float bmax_pixel[2];


//    float block_scale=4.0;
//    float block_bottom=bmin[0];
//    float block_scale=4.1*300.0/(bmax[0]-bmin[0]);
//    float block_scale=(4.0*5.6) * 255.0/(bmax[0]-bmin[0]);

//ENSCHEDE GROOT
//    bmin_total[0]=-10.0;
//    bmax_total[0]=70.0;
//    float block_scale=300.0/(bmax_total[0]-bmin_total[0]);

//ENSCHEDE KLEIN
    bmin_total[0]=-23.0;
    bmax_total[0]=145.0;
    double block_scale=500.0/(bmax_total[0]-bmin_total[0]);

//ayay
    int box_x_block_start=bmin[0]*block_scale;
    int box_y_block_start=bmin[1]*block_scale;
    int box_z_block_start=bmin[2]*block_scale;

    int box_x_block_end=bmax[0]*block_scale;
    int box_y_block_end=bmax[1]*block_scale;
    int box_z_block_end=bmax[2]*block_scale;

    int box_x_total_start=bmin_total[0]*block_scale;
    int box_y_total_start=bmin_total[1]*block_scale;
    int box_z_total_start=bmin_total[2]*block_scale;

    int box_x_total_end=bmax_total[0]*block_scale;
    int box_y_total_end=bmax_total[1]*block_scale;
    int box_z_total_end=bmax_total[2]*block_scale;

//help
    int box_x=box_x_block_end-box_x_block_start+1;
    if (wuppie_all) {
        if (box_x>255) box_x=255;
    }
    int box_y=box_y_block_end-box_y_block_start+1;//+2 if (box_y>512) box_y=512;//+2;
    int box_z=box_z_block_end-box_z_block_start+1;//+2 if (box_z>512) box_z=512;//+2;
//    int box_x=box_x_block_end-box_x_block_start+1; if (box_x>255) box_x=255;
//    int box_y=box_y_block_end-box_y_block_start+1;//+2 if (box_y>512) box_y=512;//+2;
//    int box_z=box_z_block_end-box_z_block_start+1;//+2 if (box_z>512) box_z=512;//+2;


/*
    int box_x=(bmax[0]-bmin[0])*block_scale; if (box_x>255) box_x=255;
    int box_y=(bmax[1]-bmin[1])*block_scale;//+2 if (box_y>512) box_y=512;//+2;
    int box_z=(bmax[2]-bmin[2])*block_scale;//+2 if (box_z>512) box_z=512;//+2;
*/

    offset_real_y=box_x_block_start - box_x_total_start;

//    block_scale*=1.0001;

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

//    unsigned short mc[box_x][box_y][box_z];

//    unsigned short *mc = new unsigned short [tot_off];



    unsigned short **mc_sub = (unsigned short **) malloc( sizeof(unsigned short *) * box_x);
    if (mc_sub==NULL)  {
        printf("Error allocating memory mc_sub\n");
        return;
    }

    for (int cube_x=0; cube_x<box_x; cube_x++) {
        mc_sub[cube_x] = (unsigned short *) malloc( sizeof(unsigned short) * tot_off_x);
        std::memset(mc_sub[cube_x], 0x0, sizeof(unsigned short) * tot_off_x);  //short
        if (mc_sub[cube_x]==NULL)  {
            printf("Error allocating memory mc_sub\n");
            return;
        }

    }

/*
    unsigned short **mc_sub = new unsigned short * [box_x];

    if (mc_sub==NULL)  {
        printf("Error allocating memory mc_sub\n");
        return;
    }
    for (int cube_x=0; cube_x<box_x; cube_x++) {
        mc_sub[cube_x] = new unsigned short [tot_off_x];
        if (mc_sub[cube_x]==NULL) {
            printf("Error allocating memory mc_sub[%d]\n",cube_x);
            return;
        }
        std::memset(mc_sub[cube_x], 0x0, tot_off_x*2);  //short
    }
*/

//    if (mc!=NULL) printf("OK!\n");
//    else {
//        printf("Error allocating memory\n");
//        return;
//    }

//    std::memset(mc, 0x0, tot_off*2);  //short

    char filename[2000];
    std::ofstream ofs;
    if (wuppie_all) {
        sprintf(filename, "../cut/voxel.dat");
    } else {
        sprintf(filename, "../cut/%s.dat",fn.c_str());
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
//    system("del ..\\cut\\voxel.tst");
//    sprintf(filename, "../cut/voxel.tst");
//    printf("Writing %s ...",filename);

//    pFile = fopen ( "../cut/voxel.tst" , "wb" );
//    fwrite( mc, tot_off, 1, pFile );
//    fclose(pFile);


/*
    printf("Reading file ../cut/voxel.raw ");
    pFile = fopen ( "../cut/voxel.raw" , "rb" );
    size_t result = fread(mc,1,tot_off*2,pFile);
    fclose(pFile);
    printf("%u bytes\n",result);

    unsigned char out[box_x*4];

    printf("Saving file ../cut/voxel.raw ");

    pFile = fopen ( "../cut/voxel.raw" , "wb" );
    result=0;
    for (int cube_z=0; cube_z<box_z; cube_z++) {
        for (int cube_y=0; cube_y<box_y; cube_y++) {
            for (int cube_x=0; cube_x<box_x; cube_x++) {
                size_t off=(cube_x+cube_y*box_x+cube_z*box_x*box_y)*4;
                out[cube_x*4] =(unsigned char)  mc[off];
                out[cube_x*4+1]=(unsigned char) mc[off+1];
                out[cube_x*4+2]=(unsigned char) mc[off+2];
                out[cube_x*4+3]=(unsigned char) mc[off+3];
                result+=4;
            }
            fwrite( out, box_x*4, 1, pFile );
        }
    }
    printf("%u bytes\n",result);
    return;
*/


/*

    ofs.open(filename);
//    ofs << "P6\n" << w << " " << h << "\n255\n";

    ofs.write((char*)mc, tot_off);
    ofs.close();
*/
    if (wuppie_all) printf("Ready\n");
//    int offset_x_int=box_x_block_start;
//    int offset_y_int=box_y_block_start;
//    int offset_z_int=box_z_block_start;

    int offset_x=box_x_block_start;
    int offset_y=box_y_block_start;
    int offset_z=box_z_block_start;
//    double offset_x=bmin[0];
//    double offset_y=bmin[1];
//    double offset_z=bmin[2];

    bmin[0] = bmin[1] = bmin[2] = std::numeric_limits<double>::max();
    bmax[0] = bmax[1] = bmax[2] = -std::numeric_limits<double>::max();

//!!!!!
    buf_count=0;
    int tot_faces=0;

    bool hit_cube_y_start=false;
    bool hit_cube_y_end=false;
    bool hit_cube_z_start=false;
    bool hit_cube_z_end=false;

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
                image=0;
                printf("Image not ok!!!!\n");
            }
            else {
                w=image_buffer[mat_id]->image->getSize().x;
                h=image_buffer[mat_id]->image->getSize().y;
                image=(unsigned char*)image_buffer[mat_id]->image->getPixelsPtr();
                sfml_image=image_buffer[mat_id]->image;
//                printf("Material id: %3d  w=%3d , h=%3d  ",mat_id,w,h);
            }
            no_texture=false;
        } else {
            printf("No material id: %d\n",mat_id);
            sf::sleep(sf::seconds(2.0));
            no_texture=true;
        }
        sf::Image image_copy;
        sf::Image* image=image_buffer[mat_id]->image;
//        image_copy.create(image->getSize().x,image->getSize().y);
//        image_copy.copy(*image,0,0,sf::IntRect(0,0,image->getSize().x,image->getSize().y));


        if (!no_texture) {
            char filename[2000];
            sprintf(filename, "../cut/raster_tot.%03d.org.png", buf_count );
//wuppie
//            image_copy.saveToFile(filename);
//            image_buffer[mat_id]->image->saveToFile(filename);
        }

        for (int faces=0; faces<num_faces; faces++) {
//            bmin_triangle[0] = bmin_triangle[1] = bmin_triangle[2] = std::numeric_limits<float>::max();
//            bmax_triangle[0] = bmax_triangle[1] = bmax_triangle[2] = -std::numeric_limits<float>::max();

//            bmin_pixel[0] = bmin_pixel[1] = std::numeric_limits<float>::max();
//            bmax_pixel[0] = bmax_pixel[1] = -std::numeric_limits<float>::max();

            for (int l=0; l<3; l++) {
                int offset=(stride*(l+faces*3));
                for (int k=0; k<3; k++) {
                    if (offset*sizeof(float) >= one_buffer.length-sizeof(int)) {
                        printf("Error offset\n");
                        return;
                    }
                    v[l][k]=VertexPointer[offset+k];
//                    n[l][k]=NormalPointer[offset+k];
//                    c[l][k]=ColorPointer[offset+k];
                    if (k<2) tc[l][k]=TexCoordPointer[offset+k];
                } //point

                glm::vec4 hop = glm::vec4(v[l][0], v[l][1], v[l][2], 1.0f);

                bmin_org[0]=std::min((double)hop.x, bmin_org[0]);   bmax_org[0]=std::max((double)hop.x, bmax_org[0]);
                bmin_org[1]=std::min((double)hop.y, bmin_org[1]);   bmax_org[1]=std::max((double)hop.y, bmax_org[1]);
                bmin_org[2]=std::min((double)hop.z, bmin_org[2]);   bmax_org[2]=std::max((double)hop.z, bmax_org[2]);
if (0) {
//                bmin_triangle[0]=std::min(hop.x, bmin_triangle[0]);   bmax_triangle[0]=std::max(hop.x, bmax_triangle[0]);
//                bmin_triangle[1]=std::min(hop.y, bmin_triangle[1]);   bmax_triangle[1]=std::max(hop.y, bmax_triangle[1]);
//                bmin_triangle[2]=std::min(hop.z, bmin_triangle[2]);   bmax_triangle[2]=std::max(hop.z, bmax_triangle[2]);

//                bmin_pixel[0]=std::min(tc[l][0], bmin_pixel[0]);   bmax_pixel[0]=std::max(tc[l][0], bmax_pixel[0]);
//                bmin_pixel[1]=std::min(tc[l][1], bmin_pixel[1]);   bmax_pixel[1]=std::max(tc[l][1], bmax_pixel[1]);

//                hop = hop * test;

//                VertexPointer[offset]=hop.x;
//                VertexPointer[offset+1]=hop.y;
//                VertexPointer[offset+2]=hop.z;

//                bmin[0]=std::min(hop.x, bmin[0]);   bmax[0]=std::max(hop.x, bmax[0]);
//                bmin[1]=std::min(hop.y, bmin[1]);   bmax[1]=std::max(hop.y, bmax[1]);
//                bmin[2]=std::min(hop.z, bmin[2]);   bmax[2]=std::max(hop.z, bmax[2]);

//                    printf("Offset: %7d/%7d  Vertice: %d %-+9.3f %-+9.3f %-+9.3f  ==>  %-+9.3f %-+9.3f %-+9.3f  bmin=%-+9.3f %-+9.3f %-+9.3f  bmax=%-+9.3f %-+9.3f %-+9.3f\n",
//                            offset*sizeof(float),one_buffer.length,l,v[l][0],v[l][1],v[l][2],hop.x,hop.y,hop.z,
//                            bmin[0],bmin[1],bmin[2],bmax[0],bmax[1],bmax[2]);


/*
                if (false) {
                    if (prev_bmin_org[0]!=bmin_org[0] ||    prev_bmin_org[1]!=bmin_org[1] ||    prev_bmin_org[2]!=bmin_org[2] ||
                        prev_bmax_org[0]!=bmax_org[0] ||    prev_bmax_org[1]!=bmax_org[1] ||    prev_bmax_org[2]!=bmax_org[2] ) {
                        printf("Material id: %3d  w=%3d , h=%3d  ",mat_id,w,h);
                        printf("Buffer: %3d/%3d  Face: %7d/%7d  ==>  bmin=%-+7.2f %-+7.2f %-+7.2f  bmax=%-+7.2f %-+7.2f %-+7.2f  diff=%-+7.2f %-+7.2f %-+7.2f\r",
                                buf_count, buffers.size(), faces+1, num_faces,
                                bmin_org[0],bmin_org[1],bmin_org[2],bmax_org[0],bmax_org[1],bmax_org[2],
                                bmax_org[0]-bmin_org[0],bmax_org[1]-bmin_org[1],bmax_org[2]-bmin_org[2]);
                    }
                    prev_bmin_org[0]=bmin_org[0];   prev_bmin_org[1]=bmin_org[1];   prev_bmin_org[2]=bmin_org[2];
                    prev_bmax_org[0]=bmax_org[0];   prev_bmax_org[1]=bmax_org[1];   prev_bmax_org[2]=bmax_org[2];
                }
*/

//                    printf("Offset: %7d/%7d  Vertice: %d %-+9.3f %-+9.3f %-+9.3f  ==>  %-+9.3f %-+9.3f %-+9.3f\n",
//                            offset*sizeof(float),one_buffer.length,l,v[l][0],v[l][1],v[l][2],hop.x,hop.y,hop.z);
}


            } // triangle
/*
            if (!true) {
                printf("Material id: %3d  w=%3d , h=%3d  ",mat_id,w,h);
                printf("Buffer: %3d/%3d  Face: %7d/%7d  ==>  bmin=%-+7.2f %-+7.2f %-+7.2f  bmax=%-+7.2f %-+7.2f %-+7.2f  diff=%-+7.2f %-+7.2f %-+7.2f  pmin=%-+7.2f %-+7.2f  pmax=%-+7.2f %-+7.2f  diff=%-+7.2f %-+7.2f\n",
                        buf_count, buffers.size(), faces+1, num_faces,
                        bmin_triangle[0],bmin_triangle[1],bmin_triangle[2],bmax_triangle[0],bmax_triangle[1],bmax_triangle[2],
                        bmax_triangle[0]-bmin_triangle[0],bmax_triangle[1]-bmin_triangle[1],bmax_triangle[2]-bmin_triangle[2],
                        bmin_pixel[0]*w,bmin_pixel[1]*h,bmax_pixel[0]*w,bmax_pixel[1]*h,
                        bmax_pixel[0]*w-bmin_pixel[0]*w,bmax_pixel[1]*h-bmin_pixel[1]*h);
            }
*/

            if (!false)
            flop++;
            if (wuppie_all && !no_texture && ((flop%150)==1) ) {
//            if (!no_texture && (flop%50)==1 || 1) {
                float AB_V; float BC_V; float CA_V;
                float AB_P; float BC_P; float CA_P;
                float AB_R=0.0; float BC_R=0.0; float CA_R=0.0;
                AB_V=sqrt(
                          (v[0][0]-v[1][0])*(v[0][0]-v[1][0]) +
                          (v[0][1]-v[1][1])*(v[0][1]-v[1][1]) +
                          (v[0][2]-v[1][2])*(v[0][2]-v[1][2])
                          );
                BC_V=sqrt(
                          (v[1][0]-v[2][0])*(v[1][0]-v[2][0]) +
                          (v[1][1]-v[2][1])*(v[1][1]-v[2][1]) +
                          (v[1][2]-v[2][2])*(v[1][2]-v[2][2])
                          );
                CA_V=sqrt(
                          (v[2][0]-v[0][0])*(v[2][0]-v[0][0]) +
                          (v[2][1]-v[0][1])*(v[2][1]-v[0][1]) +
                          (v[2][2]-v[0][2])*(v[2][2]-v[0][2])
                          );
                AB_P=sqrt(
                          (w*tc[0][0]-w*tc[1][0])*(w*tc[0][0]-w*tc[1][0]) +
                          (h*tc[0][1]-h*tc[1][1])*(h*tc[0][1]-h*tc[1][1])
                          );
                BC_P=sqrt(
                          (w*tc[1][0]-w*tc[2][0])*(w*tc[1][0]-w*tc[2][0]) +
                          (h*tc[1][1]-h*tc[2][1])*(h*tc[1][1]-h*tc[2][1])
                          );
                CA_P=sqrt(
                          (w*tc[2][0]-w*tc[0][0])*(w*tc[2][0]-w*tc[0][0]) +
                          (h*tc[2][1]-h*tc[0][1])*(h*tc[2][1]-h*tc[0][1])
                          );
                if (AB_V!=0.0) AB_R=AB_P/AB_V;
                if (BC_V!=0.0) BC_R=BC_P/BC_V;
                if (CA_V!=0.0) CA_R=CA_P/CA_V;

                printf("\rV:(%-+10.3f,%-+10.3f,%-+10.3f) T:(%-+10.3f,%-+10.3f,%-+10.3f) T/V:(%-+10.3f,%-+10.3f,%-+10.3f)  TC:(%3d,%3d),(%3d,%3d),(%3d,%3d) ",
                       AB_V,BC_V,CA_V,
                       AB_P,BC_P,CA_P,
                       AB_R,BC_R,CA_R,
                       int(w*tc[0][0]),int(h*tc[0][1]),int(w*tc[1][0]),int(h*tc[1][1]),int(w*tc[2][0]),int(h*tc[2][1]));

//                printf("V:(%-+10.3f,%-+10.3f,%-+10.3f) - (%-+10.3f,%-+10.3f,%-+10.3f) (%-+10.3f,%-+10.3f,%-+10.3f)  T:(%-+10.3f,%-+10.3f,%-+10.3f) - (%-+10.3f,%-+10.3f,%-+10.3f) (%-+10.3f,%-+10.3f,%-+10.3f)\n",
//                    v[0][0],    v[0][1],    v[0][2]     , v[1][0],      v[1][1],    v[1][2]     , v[2][0],      v[2][1],    v[2][2],
//                    tc[0][0]*w, tc[0][1]*h, 0.0         , tc[1][0]*w,   tc[1][1]*h, 0.0         , tc[2][0]*w,   tc[2][1]*h, 0.0);


           }

//hier
//            printf("face 1: %d/%d = ",faces,num_faces);
//ayay2
            warning_done_y=false;
            warning_done_z=false;

           if (!no_texture) magic(v,tc,image_buffer[mat_id], buf_count, faces,image_copy, offset_x, offset_y, offset_z, box_x, box_y, box_z, mc_sub, block_scale);

//           if (!no_texture) magic(v,tc,image_buffer[mat_id], buf_count, faces,image_copy, offset_x, offset_y, offset_z, box_x, box_y, box_z, mc, block_scale);
//            printf("Ok * ");
//           printf(".");
        } // faces

        warning_done_x=false;
        warning_done_topping=false;
        if (wuppie_all) printf("Ready! ");
        if (!no_texture && 0) {
            printf("Saving!\r");

//            sf::Image* image=image_buffer[mat_id]->image;
            sf::Color random_color=sf::Color(rand()%256,rand()%256,rand()%256,255);
            for (int y=0; y<image_copy.getSize().y; y++) {
                for (int x=0; x<image_copy.getSize().x; x++) {
                    sf::Color color=image_copy.getPixel(x,y);
//                    if (color.a==254 || color.a==253) image->setPixel(x,y,sf::Color(255,255,255,255));
//                    if (color.a==250) image_copy.setPixel(x,y,sf::Color( (random_color.r+color.r*2)/3,(random_color.g+color.g*2)/3,(random_color.b+color.b*2)/3,255));
                    if (color.a==252) image_copy.setPixel(x,y,sf::Color((color.r+127)%255,color.g,color.b,255));
                    else if (color.a==255) image_copy.setPixel(x,y,sf::Color( (255*3-color.r)/4,(255-color.g)/2,(255-color.b)/2,128));
//                    else if (color.a==255) image_copy.setPixel(x,y,sf::Color( (255-color.r)/2,(255-color.g)/2,(255-color.b)/2,255));
                }
            }


/*
            for (int y=0; y<image_buffer[mat_id]->image->getSize().y; y++) {
                for (int x=0; x<image_buffer[mat_id]->image->getSize().x; x++) {
                    sf::Color color=image_buffer[mat_id]->image->getPixel(x,y);
                    if (color.a==254 || color.a==253) image_buffer[mat_id]->image->setPixel(x,y,sf::Color(255,255,255,255));
                    else if (color.a==252) image_buffer[mat_id]->image->setPixel(x,y,sf::Color(255,0,0,255));
                }
            }
*/


            char filename[2000];
            sprintf(filename, "../cut/raster_tot.%03d.png", buf_count );
//wuppie
//            image_copy.saveToFile(filename);
//            image_buffer[mat_id]->image->saveToFile(filename);
        } else {
            printf("\r");
        }
        if (wuppie_all) printf("\rMaterial id: %3d  w=%3d , h=%3d  ",mat_id,w,h);
        if (wuppie_all) printf("Total: buffer: %3d/%3d  Faces: %7d  ==>  bmin=%-+7.2f %-+7.2f %-+7.2f  bmax=%-+7.2f %-+7.2f %-+7.2f  diff=%-+7.2f %-+7.2f %-+7.2f\n",
                buf_count+1, buffers.size(),num_faces,
                bmin_org[0],bmin_org[1],bmin_org[2],bmax_org[0],bmax_org[1],bmax_org[2],
                bmax_org[0]-bmin_org[0],bmax_org[1]-bmin_org[1],bmax_org[2]-bmin_org[2]);
//        bmin[0]=std::min(bmin[0], bmin_org[0]);   bmax[0]=std::max(bmax[0], bmax_org[0]);
//        bmin[1]=std::min(bmin[1], bmin_org[1]);   bmax[1]=std::max(bmax[1], bmax_org[1]);
//        bmin[2]=std::min(bmin[2], bmin_org[2]);   bmax[2]=std::max(bmax[2], bmax_org[2]);


        if (buf_count==buffers.size()-1 ) {
//        if (buf_count==buffers.size() || (buf_count%10)==0) {
            int tot_hits=0;
            int tot_blocks=0;
            int m_i_n[3];
            int m_a_x[3];
            m_i_n[0] = m_i_n[1] = m_i_n[2] = std::numeric_limits<int>::max();
            m_a_x[0] = m_a_x[1] = m_a_x[2] = -std::numeric_limits<int>::max();

            double avg_x; float avg_y; float avg_z;
            avg_x=0;avg_y=0;avg_z=0;
            for (int cube_z=0; cube_z<box_z; cube_z++) {
                for (int cube_y=0; cube_y<box_y; cube_y++) {
                    for (int cube_x=0; cube_x<box_x; cube_x++) {
    //ayay
    //                    size_t off=(cube_x+cube_y*box_x+cube_z*box_x*box_y)*4;
                        size_t off_x=(cube_y+cube_z*box_y)*4;

                        if (mc_sub[cube_x][off_x+3]>0) {
    //                    if (mc[off+3]>0) {
                            tot_blocks++;
                            tot_hits+=mc_sub[cube_x][off_x+3];
    //                        tot_hits+=mc[off+3];
                            m_i_n[0]=std::min(m_i_n[0], cube_x);   m_a_x[0]=std::max(m_a_x[0], cube_x);
                            m_i_n[1]=std::min(m_i_n[1], cube_y);   m_a_x[1]=std::max(m_a_x[1], cube_y);
                            m_i_n[2]=std::min(m_i_n[2], cube_z);   m_a_x[2]=std::max(m_a_x[2], cube_z);
                            avg_x=avg_x+cube_x;
                            avg_y=avg_y+cube_y;
                            avg_z=avg_z+cube_z;
                        }
                    }
                }
            }
            if (tot_blocks==0) printf("tot_blocks==0\n");
            else if (box_x==0) printf("box_x=0\n");
            else if (box_y==0) printf("box_y=0\n");
            else if (box_z==0) printf("box_z=0\n");
            else {
                double a_x=avg_x/tot_blocks/box_x;
                double a_y=avg_y/tot_blocks/box_y;
                double a_z=avg_z/tot_blocks/box_z;

                size_t size_filled=(m_a_x[0]-m_i_n[0])*(m_a_x[1]-m_i_n[1])*(m_a_x[2]-m_i_n[2]);
                float percentage_filled=100*size_filled/(box_x*box_y*box_z);
                float percentage_filled_blocks=100*tot_blocks/(box_x*box_y*box_z);
                printf("\rTotal: buffer: %3d/%3d  Faces: %7d  ==>  ",  buf_count+1, buffers.size(),tot_faces);
                printf(" Blocks: %8d(%6d) Hits: %8d(%6d) Avg: %4.1f ",tot_blocks, tot_blocks-o_tot_blocks, tot_hits, tot_hits-o_tot_hits, float(tot_hits)/float(tot_blocks));
                printf("Min: (%4d,%4d,%4d) Max: (%4d,%4d,%4d) Diff: (%4d,%4d,%4d) (%3d%%,%3d%%,%3d%%) (%3d%%,%3d%%,%3d%%) (%4.1f%%) (%6.3f%%)\n",
                    m_i_n[0], m_i_n[1], m_i_n[2],
                    m_a_x[0], m_a_x[1], m_a_x[2],
                    m_a_x[0]-m_i_n[0], m_a_x[1]-m_i_n[1], m_a_x[2]-m_i_n[2],
                    int(100*(m_a_x[0]-m_i_n[0])/box_x),int(100*(m_a_x[1]-m_i_n[1])/box_y),int(100*(m_a_x[2]-m_i_n[2])/box_z),
                    int(a_x*100),int(a_y*100),int(a_z*100),
                       percentage_filled,percentage_filled_blocks   );
            }
            o_tot_blocks=tot_blocks;
            o_tot_hits=tot_hits;
        } else {
//            printf("\n");
        }
        buf_count++;
        tot_faces+=num_faces;


    } //buffers


    if (wuppie_all) printf("\nRecalc\n");

    for (int cube_z=0; cube_z<box_z; cube_z++) {
        for (int cube_y=0; cube_y<box_y; cube_y++) {
            for (int cube_x=0; cube_x<box_x; cube_x++) {
                size_t off_x=(cube_y+cube_z*box_y)*4;
                float num=mc_sub[cube_x][off_x+3];
                if (num>0) {
                    mc_sub[cube_x][off_x+0]=(unsigned short)((float)mc_sub[cube_x][off_x+0]/num);
                    mc_sub[cube_x][off_x+1]=(unsigned short)((float)mc_sub[cube_x][off_x+1]/num);
                    mc_sub[cube_x][off_x+2]=(unsigned short)((float)mc_sub[cube_x][off_x+2]/num);
                }
            }
        }
    }
    for (int cube_z=0; cube_z<box_z; cube_z++) {
        for (int cube_y=0; cube_y<box_y; cube_y++) {
            size_t off_x=(cube_y+cube_z*box_y)*4;
            int max_x=0;
            for (int cube_x=0; cube_x<box_x; cube_x++) {
                float num=mc_sub[cube_x][off_x+3];

                if (num==0) {
                    if (cube_y==0 || cube_z==0 || cube_y==box_y-1 || cube_z==box_z-1) {
                        size_t dest;
                        if (cube_y==0) {
                            if (!hit_cube_y_start) {
                                dest=((1)+cube_z*box_y)*4;
                                mc_sub[cube_x][off_x+0]=mc_sub[cube_x][dest+0];
                                mc_sub[cube_x][off_x+1]=mc_sub[cube_x][dest+1];
                                mc_sub[cube_x][off_x+2]=mc_sub[cube_x][dest+2];
                                mc_sub[cube_x][off_x+3]=mc_sub[cube_x][dest+3];
//                                printf("y- ");
                            }
                        } else if (cube_y==box_y-1) {
                            if (!hit_cube_y_end) {
                                dest=((box_y-2)+cube_z*box_y)*4;
                                mc_sub[cube_x][off_x+0]=mc_sub[cube_x][dest+0];
                                mc_sub[cube_x][off_x+1]=mc_sub[cube_x][dest+1];
                                mc_sub[cube_x][off_x+2]=mc_sub[cube_x][dest+2];
                                mc_sub[cube_x][off_x+3]=mc_sub[cube_x][dest+3];
//                                printf("y+ ");

                            }
                        }
                        if (cube_z==0) {
                            if (!hit_cube_z_start) {
                                dest=(cube_y+(1)*box_y)*4;
                                mc_sub[cube_x][off_x+0]=mc_sub[cube_x][dest+0];
                                mc_sub[cube_x][off_x+1]=mc_sub[cube_x][dest+1];
                                mc_sub[cube_x][off_x+2]=mc_sub[cube_x][dest+2];
                                mc_sub[cube_x][off_x+3]=mc_sub[cube_x][dest+3];
//                                printf("z- ");
                            }
                        } else if (cube_z==box_z-1) {
                            if (!hit_cube_z_end) {
                                dest=(cube_y+(box_z-2)*box_y)*4;
                                mc_sub[cube_x][off_x+0]=mc_sub[cube_x][dest+0];
                                mc_sub[cube_x][off_x+1]=mc_sub[cube_x][dest+1];
                                mc_sub[cube_x][off_x+2]=mc_sub[cube_x][dest+2];
                                mc_sub[cube_x][off_x+3]=mc_sub[cube_x][dest+3];
//                                printf("z+ ");
                                max_x=cube_x;
                            }
                        }
                    }
                }
                if (mc_sub[cube_x][off_x+3]>0) max_x=cube_x;
            }
            if (cube_y==0 || cube_z==0 || cube_y==box_y-1 || cube_z==box_z-1) {
                mc_sub[max_x][off_x]/=2;
                mc_sub[max_x][off_x+1]/=2;
                mc_sub[max_x][off_x+2]=mc_sub[max_x][off_x+2]/2+128;
                mc_sub[max_x][off_x+3]=1;
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

extern char *backup;
    delete [] backup;

    if (wuppie_all) {
        printf(" Ready.\n");

        sprintf(new_file,"../cut/%s.RAW",fn.c_str());
        if (wuppie_all) {
            printf("Copying %s to %s...","../cut/voxel.raw",new_file);
            CopyFile("../cut/voxel.raw",new_file,false);
            printf(" Ready.\n");
        }

        if (wuppie_all) printf("Setting %d x %d x %d x 4 : bytes=%u bytes ", box_x, box_y, box_z, tot_off);

        unsigned char *mc2 = new unsigned char [tot_off];
        if (mc2!=NULL && wuppie_all) printf("OK!\n");
        else {
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

    //    main_mceditor6(
    //        box_x, box_y, box_z,
    //        mc2,
    //        box_x_block_start,                      box_y_total_end-box_y_block_start,                  box_z_block_start,
    //        box_x_total_start,                      box_y_total_end+2048-box_y_block_start,             box_z_total_start-2048
    //    );
extern char mc_text2[];
        sprintf(mc_text2,"%s",fn.c_str());

        main_mceditor6(
            box_x, box_y, box_z,
            mc2,
            box_x_block_start,                      box_y_block_start+2048,                     box_z_block_start+2048,
//joepie
            box_x_total_start,                      box_y_total_end-1,                            box_z_total_start
        );

        delete [] mc2;

        char naam[200];
        mkdir("../cut/done");
        sprintf(naam,"move ..\\cut\\%s.* ..\\cut\\done\\",fn.c_str());
        system(naam);
    }


//    printf("\nResult:  diff=%-+5.0f %-+5.0f %-+5.0f  ==>  diff=%-+5.0f %-+5.0f %-+5.0f\n",
//            bmax_org[0]-bmin_org[0],bmax_org[1]-bmin_org[1],bmax_org[2]-bmin_org[2],
//            bmax[0]-bmin[0],bmax[1]-bmin[1],bmax[2]-bmin[2]);

/*
    for (size_t m = 0; m < materials.size(); m++)
    {
        if (!image_buffer[m]->ok) {
            image=0;
            printf("Image not ok!!!!\n");
        }
        else {
            int w=image_buffer[m]->image->getSize().x;
            int h=image_buffer[m]->image->getSize().y;
            image=(unsigned char*)image_buffer[m]->image->getPixelsPtr();
            sfml_image=image_buffer[m]->image;
        }
    }
*/
}






//***********************backup

int WUPPIE_VECTOR(std::vector<BufferObject> buffers, std::vector<tinyobj::material_t> &materials, float bmin_o[3], float bmax_o[3], double lat, double lon, std::string fn) {
    int flop=0;
    char new_file[100];
    sprintf(new_file,"../cut/%s.RAW",fn.c_str());
    if (file_exists(new_file)) {
        printf("%s exists\n",new_file);
        sprintf(new_file,"../cut/%s.DAT",fn.c_str());
        if (file_exists(new_file)) {
            printf("And %s exists, exiting\n",new_file,new_file);
            return 0;
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
        return-1;
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


//Enschede
//    bmin_total[0]=-23.0;
//    bmax_total[0]=145.0;

    bmin_total[0]=-12;
    bmax_total[0]=185;
    double block_scale=700.0/(bmax_total[0]-bmin_total[0]);

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
                        return-1;
                    }
                    v[l][k]=VertexPointer[offset+k]*block_scale;
//                    v[l][k]=(v[l][k])*1.0005;
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

    double offset_xyz[3];

//    if ( (quad==0 && y_half_min && z_half_min) || (quad==1 && y_half_max && z_half_min) || (quad==2 && y_half_min && z_half_max) || (quad==3  && y_half_max && z_half_max) ) {
//        if (!no_texture) magic(v,tc,image_buffer[mat_id], buf_count, faces,image_copy, offset_x, offset_y, offset_z, box_x, box_y, box_z, mc_sub, block_scale);
//    }

/*
    if (quad==0) {
        bmax[1]=(bmax[1]+bmin[1])/2.0+2;
        bmax[2]=(bmax[2]+bmin[2])/2.0+2;
    } else if (quad==1) {
        bmin[1]=(bmax[1]+bmin[1])/2.0-2;
        bmax[2]=(bmax[2]+bmin[2])/2.0+2;
    } else if (quad==2) {
        bmax[1]=(bmax[1]+bmin[1])/2.0+2;
        bmin[2]=(bmax[2]+bmin[2])/2.0-2;
    } else if (quad==3) {
        bmin[1]=(bmax[1]+bmin[1])/2.0-2;
        bmin[2]=(bmax[2]+bmin[2])/2.0-2;
    }
*/



    double mid_block[3];
    double mid_total[3];
    for (int n=0; n<3; n++) {
        mid_block[n]=(bmax[n]+bmin[n])/2.0;
        mid_total[n]=(bmax_total[n]+bmin_total[n])/2.0;

//        offset_xyz[n]=bmin[n]-2;

//        offset_xyz[n]=bmin[n] - 4 + (mid_block[n]-mid_total[n])*0.001;
//        offset_xyz[n]=(bmin[n] - mid_total[n])*1.001 + mid_total[n]-2;



        offset_xyz[n]=bmin[n]  -  (mid_block[n] - mid_total[n])*0.001 -6;

        bmin[n]=bmin[n]  -  (mid_block[n] - mid_total[n])*0.001;
        bmax[n]=bmax[n]  -  (mid_block[n] - mid_total[n])*0.001;

//        bmin[n]=bmin[n]  + (bmin[n] - mid_total[n])*0.001;
//        bmax[n]=bmax[n]  + (bmax[n] - mid_total[n])*0.001;

//        bmin[n]=bmin[n]  + (bmin[n]-mid_block[n])*0.0005   +   (mid_block[n]-mid_total[n])*0.0005;
//        bmax[n]=bmax[n]  + (bmax[n]-mid_block[n])*0.0005   +   (mid_block[n]-mid_total[n])*0.0005;
//        bmin[n]=(bmin[n] - mid_block[n])*1.0005 + mid_block[n];
//        bmax[n]=(bmax[n] - mid_block[n])*1.0005 + mid_block[n];
    }


//    for (int n=0; n<3; n++) {
//        bmin[n]=bmin[n]*block_scale;
//        bmax[n]=bmax[n]*block_scale;
//        bmin[n]=bmin_o[n]*block_scale;
//        bmax[n]=bmax_o[n]*block_scale;
//    }

    int box_x_block_start=bmin[0]-6;
    int box_y_block_start=bmin[1]-6;
    int box_z_block_start=bmin[2]-6;

    int offset_x=offset_xyz[0];
    int offset_y=offset_xyz[1];
    int offset_z=offset_xyz[2];
//    double offset_xyz[3]={offset_x, offset_y, offset_z};

    int box_x_block_end=bmax[0]+12;
    int box_y_block_end=bmax[1]+12;
    int box_z_block_end=bmax[2]+12;

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

    Voxel one;

    one=Voxel(box_x,box_y,box_z);
    voxels.push_back(one);

    one=Voxel(box_x_block_start, box_y_block_start, box_z_block_start);
    voxels.push_back(one);

    one=Voxel(box_x_block_end, box_y_block_end, box_z_block_end);
    voxels.push_back(one);

    one=Voxel(box_x_total_start, box_y_total_start, box_z_total_start);
    voxels.push_back(one);

    one=Voxel(box_x_total_end, box_y_total_end, box_z_total_end);
    voxels.push_back(one);

//    printf("voxels[0] = SIZE:        X=%6d, Y=%6d, Z=%6d\n", voxels[0].x, voxels[0].y, voxels[0].z );
//    printf("voxels[1] = START:       X=%6d, Y=%6d, Z=%6d\n", voxels[1].x, voxels[1].y, voxels[1].z );
//    printf("voxels[2] = END:         X=%6d, Y=%6d, Z=%6d\n", voxels[2].x, voxels[2].y, voxels[2].z );
//    printf("voxels[3] = TOTAL START: X=%6d, Y=%6d, Z=%6d\n", voxels[3].x, voxels[3].y, voxels[3].z );
//    printf("voxels[4] = TOTAL END:   X=%6d, Y=%6d, Z=%6d\n", voxels[4].x, voxels[4].y, voxels[4].z );

//    for (auto u : voxels) {
//        printf("VOXEL SIZE: X=%d, Y=%d, Z=%d\n",u.x,u.y,u.z);
//    }

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
    if (mc_sub==NULL)  {     printf("Error allocating memory mc_sub\n");      return-1;    }
    for (int cube_x=0; cube_x<box_x; cube_x++) {
        mc_sub[cube_x] = (unsigned short *) malloc( sizeof(unsigned short) * tot_off_x);
        if (mc_sub[cube_x]==NULL)  {         printf("Error allocating memory mc_sub\n");        return-1;    }
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

//    int offset_x=box_x_block_start;
//    int offset_y=box_y_block_start;
//    int offset_z=box_z_block_start;

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
//            bool y_half_min=false;
//            bool y_half_max=false;
//            bool z_half_min=false;
//            bool z_half_max=false;

            for (int l=0; l<3; l++) {
                int offset=(stride*(l+faces*3));
                for (int k=0; k<3; k++) {
                    if (offset*sizeof(float) >= one_buffer.length-sizeof(int)) {
                        printf("Error offset\n");
                        return-1;
                    }
                    v[l][k]=VertexPointer[offset+k]*block_scale-offset_xyz[k];
                    v[l][k]=(v[l][k] - mid_block[k])*1.001 + mid_block[k];
//                    n[l][k]=NormalPointer[offset+k];
//                    c[l][k]=ColorPointer[offset+k];
                    if (k<2) tc[l][k]=TexCoordPointer[offset+k];
                } //point
//                if (v[l][1] <= (double)box_y/2.0+2.0) y_half_min=true;
//                if (v[l][1] >= (double)box_y/2.0-2.0) y_half_max=true;
//                if (v[l][2] <= (double)box_z/2.0+2.0) z_half_min=true;
//                if (v[l][2] >= (double)box_z/2.0-2.0) z_half_max=true;

                glm::vec4 hop = glm::vec4(v[l][0], v[l][1], v[l][2], 1.0f);

                bmin_org[0]=std::min((double)hop.x, bmin_org[0]);   bmax_org[0]=std::max((double)hop.x, bmax_org[0]);
                bmin_org[1]=std::min((double)hop.y, bmin_org[1]);   bmax_org[1]=std::max((double)hop.y, bmax_org[1]);
                bmin_org[2]=std::min((double)hop.z, bmin_org[2]);   bmax_org[2]=std::max((double)hop.z, bmax_org[2]);

            } // triangle

//            if ( (quad==0 && y_half_min) || (quad==1 && y_half_max) || (quad==2 && z_half_min) || (quad==3 && z_half_max) ) {
//            if ( (quad==0 && y_half_min && z_half_min) || (quad==1 && y_half_max && z_half_min) || (quad==2 && y_half_min && z_half_max) || (quad==3  && y_half_max && z_half_max) ) {
                if (!no_texture) magic(v,tc,image_buffer[mat_id], buf_count, faces,image_copy, offset_x, offset_y, offset_z, box_x, box_y, box_z, mc_sub, block_scale);
//            }

        } // faces
//        if (wuppie_all)
            printf("Material id: %3d  w=%3d , h=%3d  ",mat_id,w,h);
//        if (wuppie_all)
            printf("Total: buffer: %3d/%3d  Faces: %7d  ==>  bmin=%-+7.2f %-+7.2f %-+7.2f  bmax=%-+7.2f %-+7.2f %-+7.2f  diff=%-+7.2f %-+7.2f %-+7.2f\r",
                buf_count+1, buffers.size(),num_faces,
                bmin_org[0],bmin_org[1],bmin_org[2],bmax_org[0],bmax_org[1],bmax_org[2],
                bmax_org[0]-bmin_org[0],bmax_org[1]-bmin_org[1],bmax_org[2]-bmin_org[2]);

        buf_count++;
        tot_faces+=num_faces;
    } //buffers
    warning_done_y=false;
    warning_done_z=false;
    warning_done_x=false;
    warning_done_y_min=false;
    warning_done_z_min=false;
    warning_done_x_min=false;
    warning_done_topping=false;
    printf("\n");
    int tot_hits=0;
    int tot_blocks=0;
    int m_i_n[3];
    int m_a_x[3];
    m_i_n[0] = m_i_n[1] = m_i_n[2] = std::numeric_limits<int>::max();
    m_a_x[0] = m_a_x[1] = m_a_x[2] = -std::numeric_limits<int>::max();

    double avg_x; float avg_y; float avg_z;
    avg_x=0;avg_y=0;avg_z=0;
    for (int cube_z=0; cube_z<box_z; cube_z++) {
        for (int cube_y=0; cube_y<box_y; cube_y++) {
            for (int cube_x=0; cube_x<box_x; cube_x++) {
//ayay
//                    size_t off=(cube_x+cube_y*box_x+cube_z*box_x*box_y)*4;
                size_t off_x=(cube_y+cube_z*box_y)*4;

                if (mc_sub[cube_x][off_x+3]>0) {
//                    if (mc[off+3]>0) {
                    tot_blocks++;
                    tot_hits+=mc_sub[cube_x][off_x+3];
//                        tot_hits+=mc[off+3];
                    m_i_n[0]=std::min(m_i_n[0], cube_x);   m_a_x[0]=std::max(m_a_x[0], cube_x);
                    m_i_n[1]=std::min(m_i_n[1], cube_y);   m_a_x[1]=std::max(m_a_x[1], cube_y);
                    m_i_n[2]=std::min(m_i_n[2], cube_z);   m_a_x[2]=std::max(m_a_x[2], cube_z);
                    avg_x=avg_x+cube_x;
                    avg_y=avg_y+cube_y;
                    avg_z=avg_z+cube_z;
                }
            }
        }
    }
    if (tot_blocks==0) printf("tot_blocks==0\n");
    else if (box_x==0) printf("box_x=0\n");
    else if (box_y==0) printf("box_y=0\n");
    else if (box_z==0) printf("box_z=0\n");
    else {
        double a_x=avg_x/tot_blocks/box_x;
        double a_y=avg_y/tot_blocks/box_y;
        double a_z=avg_z/tot_blocks/box_z;

        size_t size_filled=(m_a_x[0]-m_i_n[0])*(m_a_x[1]-m_i_n[1])*(m_a_x[2]-m_i_n[2]);
        float percentage_filled=100*size_filled/(box_x*box_y*box_z);
        float percentage_filled_blocks=100*tot_blocks/(box_x*box_y*box_z);
        printf("\rTotal: buffer: %3d/%3d  Faces: %7d  ==>  ",  buf_count+1, buffers.size(),tot_faces);
        printf(" Blocks: %8d(%6d) Hits: %8d(%6d) Avg: %4.1f ",tot_blocks, tot_blocks-o_tot_blocks, tot_hits, tot_hits-o_tot_hits, float(tot_hits)/float(tot_blocks));
        printf("Min: (%4d,%4d,%4d) Max: (%4d,%4d,%4d) Diff: (%4d,%4d,%4d) (%3d%%,%3d%%,%3d%%) (%3d%%,%3d%%,%3d%%) (%4.1f%%) (%6.3f%%)\n",
            m_i_n[0], m_i_n[1], m_i_n[2],
            m_a_x[0], m_a_x[1], m_a_x[2],
            m_a_x[0]-m_i_n[0], m_a_x[1]-m_i_n[1], m_a_x[2]-m_i_n[2],
            int(100*(m_a_x[0]-m_i_n[0])/box_x),int(100*(m_a_x[1]-m_i_n[1])/box_y),int(100*(m_a_x[2]-m_i_n[2])/box_z),
            int(a_x*100),int(a_y*100),int(a_z*100),
               percentage_filled,percentage_filled_blocks   );
    }
    o_tot_blocks=tot_blocks;
    o_tot_hits=tot_hits;











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

    unsigned char *mc2 = (unsigned char*) malloc(tot_off);

//    unsigned char *mc2 = new unsigned char [tot_off];
    if (mc2!=NULL) {
            if (wuppie_all) printf("OK!\n");
    } else {
        printf("Error allocating memory\n");
        return-1;
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
//    if (!plotting) sprintf(mc_text2,"%s",fn.c_str());
//    else sprintf(mc_text2,"");
    sprintf(mc_text2,"%s",fn.c_str());

    if (plotting) {
            main_mceditor6_plot(
                voxels[0].x, voxels[0].y, voxels[0].z,
                mc2,
                voxels[1].x, voxels[1].y+2048,  voxels[1].z+2048,
                voxels[3].x, voxels[4].y-1,     voxels[3].z
            );
//        main_mceditor6_plot(
//            box_x, box_y, box_z,
//            mc2,
//            box_x_block_start,                      box_y_block_start+2048,                     box_z_block_start+2048,
//            box_x_total_start,                      box_y_total_end-1,                            box_z_total_start
//        );
    } else {
//        printf("here 1\n");
        main_mceditor6(
            box_x, box_y, box_z,
            mc2,
            box_x_block_start,                      box_y_block_start+2048,                     box_z_block_start+2048,
            box_x_total_start,                      box_y_total_end-1,                            box_z_total_start
        );
    }

//    delete [] mc2;
    free(mc2);
    if (!plotting) {
        char naam[200];
        mkdir("../cut/done");
        sprintf(naam,"move ..\\cut\\%s.* ..\\cut\\done\\",fn.c_str());
        system(naam);
    }
    return 1;
}

std::vector<Voxel> voxels_total;

void WUPPIE_SUBS(std::vector<BufferObject> buffers, std::vector<tinyobj::material_t> &materials, float bmin_o[3], float bmax_o[3], double lat, double lon, std::string fn) {
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
    plotting=false;

//    std::vector<BufferObject> buffers_sub;
//    for (std::vector<BufferObject>::iterator it=buffers.begin(), end = buffers.end(); it != end; ++it) {
//        one_buffer=*it;
//        buffers_sub.push_back(one_buffer);
//        count++;
//    }

    printf("%s\n",fn.c_str());
//    printf("%s quadrant 1\n",fn.c_str());
//    quad=0;
    int ret=WUPPIE_VECTOR(buffers, materials, bmin_o, bmax_o, lat, lon, fn);
//    printf("%s quadrant 2\n",fn.c_str());
//    quad=1;
//    ret=WUPPIE_VECTOR(buffers, materials, bmin_o, bmax_o, lat, lon, fn);
//    printf("%s quadrant 2\n",fn.c_str());
//    quad=2;
//    ret=WUPPIE_VECTOR(buffers, materials, bmin_o, bmax_o, lat, lon, fn);
//    printf("%s quadrant 2\n",fn.c_str());
//    quad=3;
//    ret=WUPPIE_VECTOR(buffers, materials, bmin_o, bmax_o, lat, lon, fn);

    if (ret==-1) {
        printf("ERROR %s\n",fn.c_str());
    } else if (ret==0) {
//        printf("File exists, skipping\n");
    } else {
//        sprintf(new_file_raw,"../cut/%s.RAW",fn.c_str());
//        sprintf(new_file_dat,"../cut/%s.DAT",fn.c_str());
        printf("voxels[0] = SIZE:        X=%6d, Y=%6d, Z=%6d\n", voxels[0].x, voxels[0].y, voxels[0].z );
        printf("voxels[1] = START:       X=%6d, Y=%6d, Z=%6d\n", voxels[1].x, voxels[1].y, voxels[1].z );
        printf("voxels[2] = END:         X=%6d, Y=%6d, Z=%6d\n", voxels[2].x, voxels[2].y, voxels[2].z );
        printf("voxels[3] = TOTAL START: X=%6d, Y=%6d, Z=%6d\n", voxels[3].x, voxels[3].y, voxels[3].z );
        printf("voxels[4] = TOTAL END:   X=%6d, Y=%6d, Z=%6d\n", voxels[4].x, voxels[4].y, voxels[4].z );


/*
        int count=0;

        printf("NEW NUMBER OF VOXELS: %7d\n",voxels.size()-5);
        int total_hits=0;
        for (auto u : voxels) {
            if (count<5) { count++; continue; }
            total_hits+=u.l;
        }
        printf("NEW NUMBER OF HITS:   %7d\n",total_hits);

        printf("\n");

        printf("CURRENT NUMBER OF TOTAL VOXELS: %7d\n",voxels_total.size());
        total_hits=0;
        for (auto u : voxels_total) {
            total_hits+=u.l;
        }
        printf("CURRENT NUMBER OF TOTAL HITS:   %7d\n",total_hits);

        printf("\n");

        printf("ADDING TOTAL! VOXELS TO NEW! VOXELS:\n");
        Voxel one;
        for (auto u : voxels_total) {
            one=u;
            voxels.push_back(one);
        }
        printf("CLEARING TOTAL:\n");
        voxels_total.clear();

        if (voxels.size()>5) {
            printf("SORTING BOTH VOXELS BACK TO TOTAL VOXELS: ");
            sort(voxels.begin()+5, voxels.end());
            printf("Ok. TOTAL/AVERAGE/COMPRESS: ");
            Voxel last=voxels[5];
            Voxel total_pos=Voxel(last.x,last.y,last.z);
            for (int n=5; n<voxels.size(); n++) {
                if (last.x==voxels[n].x && last.y==voxels[n].y && last.z==voxels[n].z) {
                    total_pos.r+=voxels[n].r;
                    total_pos.g+=voxels[n].g;
                    total_pos.b+=voxels[n].b;
                    total_pos.l+=voxels[n].l;
                    if (n==voxels.size()-1) {
                        total_pos.r/=total_pos.l;
                        total_pos.g/=total_pos.l;
                        total_pos.b/=total_pos.l;
                        voxels_total.push_back(total_pos);
                    }
                } else {
                    total_pos.r/=total_pos.l;
                    total_pos.g/=total_pos.l;
                    total_pos.b/=total_pos.l;
                    voxels_total.push_back(total_pos);
                    last=voxels[n];
                    total_pos=last;
                    if (n==voxels.size()-1) {
                        total_pos.r/=total_pos.l;
                        total_pos.g/=total_pos.l;
                        total_pos.b/=total_pos.l;
                        voxels_total.push_back(total_pos);
                    }
                }
            }
        }

        printf("\n");

        printf("NEW NUMBER OF TOTAL VOXELS: %7d\n",voxels_total.size());
        total_hits=0;
        for (auto u : voxels_total) {
            total_hits+=u.l;
        }
        printf("NEW NUMBER OF TOTAL HITS:   %7d\n",total_hits);

        printf("Ready freddy\n");

//            main_mceditor6_plot(
//                voxels[0].x, voxels[0].y, voxels[0].z,
//                mc2,
//                voxels[1].x, voxels[1].y+2048,  voxels[1].z+2048,
//                voxels[3].x, voxels[4].y-1,     voxels[3].z
//            );

*/
//        main_mceditor5_from_file(new_file_dat,new_file_raw);
    //    scan_done0_plot(dummy, new_file_dat,new_file_raw);
        printf("%3d buffers. Ready.\n",buffers.size());
    }

    plotting=false;
    return ;
}

