//#include "VIEWER/viewer_my_inits.h"
#include <../MCA-NBT-EDIT.HPP>
#include <../VOXEL.HPP>
#include <map>
#include <string>
#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>

#include "MCEditor/MCEditor.h"
#include "MCEditor/BlockEntity.h"
#include "MCEditor/MCACoder.h"

extern int region_floor;
extern hit_one_region* findRegion(int x, int z);
extern std::vector<hit_one_region> vector_hit_regions;
extern bool plot_only;
extern int mirror;
extern sf::Image scan_image;
extern int plotting;
extern int MCEDITOR_running;
bool get_block=false;
extern sf::RenderWindow SFMLView1;
extern bool cubic;
extern int replace_str(char* str, char* orig, char* rep);
extern std::vector<Voxel> voxels;
extern std::vector<Voxel> voxels_total;
extern void quick_toggle();
extern int ret_color(int r, int g, int b);
extern unsigned char region_block[];
extern int main_mceditor6_fixed(int region_x, int region_z, unsigned char* mc);
extern MCEditor editor;

void voxels_to_object(char* picture_file) {

    Voxel one;
    int bmin_x,bmin_y,bmin_z;
    int bmax_x,bmax_y,bmax_z;
    bmin_x = bmin_y = bmin_z = std::numeric_limits<int>::max();
    bmax_x = bmax_y = bmax_z = -std::numeric_limits<int>::max();

    voxels.clear();

    printf("Number of voxels=%d -> compressing\n",voxels_total.size());

    if (voxels_total.size()>0) {
        printf("Sorting on position ");
        sort(voxels_total.begin(), voxels_total.end());
        printf("ready.\n");
        Voxel last=voxels_total[0];
        Voxel total_pos=Voxel(last.x,last.y,last.z,0,0,0,0,0);
        size_t n;
        for (n=0; n<voxels_total.size(); n++) {
            if (!(n%1000)) {
                float perc=100.0*(float)n/(float)voxels.size();
                printf("\r%5.3f%% ",perc);
                quick_toggle();
            }
            if (last.x==voxels_total[n].x && last.y==voxels_total[n].y && last.z==voxels_total[n].z) {
                total_pos.r+=voxels_total[n].r*voxels_total[n].l;
                total_pos.g+=voxels_total[n].g*voxels_total[n].l;
                total_pos.b+=voxels_total[n].b*voxels_total[n].l;
                total_pos.l+=voxels_total[n].l;
                if (n==voxels_total.size()-1) {
                    total_pos.status=0; //new
                    if (total_pos.l>1) {
                        total_pos.r/=total_pos.l;
                        total_pos.g/=total_pos.l;
                        total_pos.b/=total_pos.l;
//                        total_pos.l=1;
                    }
//kloten
                    total_pos.l=ret_color(total_pos.r,total_pos.g,total_pos.b);
                    voxels.push_back(total_pos);
                }
            } else {
                total_pos.status=0; //new
                if (total_pos.l>1) {
                    total_pos.r/=total_pos.l;
                    total_pos.g/=total_pos.l;
                    total_pos.b/=total_pos.l;
//                    total_pos.l=1;
                }
//kloten
                total_pos.l=ret_color(total_pos.r,total_pos.g,total_pos.b);
                voxels.push_back(total_pos);
                last=voxels_total[n];
                total_pos=last;
                if (n==voxels_total.size()-1) {
                    total_pos.status=0; //new
                    if (total_pos.l>1) {
                        total_pos.r/=total_pos.l;
                        total_pos.g/=total_pos.l;
                        total_pos.b/=total_pos.l;
//                        total_pos.l=1;
                    }
//kloten
                    total_pos.l=ret_color(total_pos.r,total_pos.g,total_pos.b);
                    voxels.push_back(total_pos);
                }
            }
        }
        float perc=100.0*(float)n/(float)voxels.size();
        printf("\r%5.3f%% ",perc);
    }
    voxels_total.clear();
    printf("Number of voxels=%d (compressed)\n",voxels.size());

//    sort(voxels.begin(), voxels.end());

    for (auto u : voxels) {
        one=u;
        if (u.x>bmax_x) bmax_x=u.x;
        if (u.x<bmin_x) bmin_x=u.x;
        if (u.y>bmax_y) bmax_y=u.y;
        if (u.y<bmin_y) bmin_y=u.y;
        if (u.z>bmax_z) bmax_z=u.z;
        if (u.z<bmin_z) bmin_z=u.z;
    }
    int bdif_x,bdif_y,bdif_z;
    bdif_x=bmax_x-bmin_x+1;
    bdif_y=bmax_y-bmin_y+1;
    bdif_z=bmax_z-bmin_z+1;

    printf("x: min=%8d  max=%8d  width=%4d\n",bmin_x,bmax_x,bdif_x);
    printf("y: min=%8d  max=%8d  width=%4d\n",bmin_y,bmax_y,bdif_y);
    printf("z: min=%8d  max=%8d  width=%4d\n",bmin_z,bmax_z,bdif_z);

    int offset_x,offset_z,offset_y=0;

    int num=sscanf(picture_file,"r.%d.%d.vox",&offset_x,&offset_z);
    if (num==2) {
        printf("Assuming region voxelfile: %s : r.%d.%d.vox\n",picture_file,offset_x,offset_z);
        offset_x=offset_x*512;
        offset_z=offset_z*512;
    } else {
        offset_x=bmin_x;
        offset_y=bmin_y;
        offset_z=bmin_z;
    }
    if (file_exists("../cut/offsets.txt")) {
        FILE* HOP;
        char line[200];
        if ((HOP = fopen ("../cut/offsets.txt", "r"))!=NULL) {
            printf("Loading offsets from ../cut/offsets.txt : ");
            if (fgets (line,200, HOP)!=NULL) {
                printf("Loaded : %s\n",line);
                if ( sscanf(line,"X=%d Y=%d Z=%d", &offset_x, &offset_y, &offset_z) != 3) {
                    printf("Error loading offsets\n");
                }
            }
            printf("Assuming offsets : x=%d , y=%d , z=%d\n",offset_x, offset_y, offset_z);
        }
    } else {
        printf("Assuming offsets = x=%d , y=%d , z=%d\n",offset_x, offset_y, offset_z);
    }


    bdif_x=bdif_x+1; // extra for +/- 1
    bdif_y=bdif_y+1;
    bdif_z=bdif_z+1;

    int x_z=bdif_x*bdif_z;

    sort_voxels_on_l=true;
    printf("Sorting on color ");
    sort(voxels.begin(), voxels.end());
    printf("ready. Indexing:\n");
    sort_voxels_on_l=false;

    std::map<unsigned long long int, int> voxels_indexed;
    std::map<unsigned long long int, int>::iterator it;
    int index_second=0;
    for (auto u : voxels) {
        one=u;
        unsigned long long int index_first=(one.x-bmin_x) + (one.z-bmin_z)*bdif_x + (one.y-bmin_y)*x_z;
        voxels_indexed.insert(std::make_pair(index_first,index_second));
        if (!(index_second%1000)) {
            float perc=100.0*(float)index_second/(float)voxels.size();
            printf("\r%5.3f%% ",perc);
            quick_toggle();
        }

        index_second++;
    }
    if (voxels.size()>0) {
        float perc=100.0*(float)index_second/(float)voxels.size();
        printf("\r%5.3f%% ",perc);
    }
    printf("Number indexed  =%d Testing:",voxels_indexed.size());
    index_second=0;
//    getchar();

    for (auto u : voxels_indexed) {
        one=voxels[u.second];
        unsigned long long int index_first=(one.x-bmin_x) + (one.z-bmin_z)*bdif_x + (one.y-bmin_y)*x_z;
        if (index_first!=u.first) printf("\nERROR: ");
//        if (index_second!=u.second || index_first!=u.first) printf("\nERROR: ");
//        printf("indexed[%3d]=%3llu -> ", index_second, u.first);
//        printf("voxels[%3d]=%3llu -> (%d,%d,%d),(%d,%d,%d),(%d)        \n",
//                u.second, index_first, one.y, one.x, one.z, one.r, one.g, one.b, one.l );
        index_second++;
    }
    printf("\n");

    index_second=0;
    printf("Finding (common/shared/reduced) vertices/cube corners:\n");

    std::map<unsigned long long int, glm::ivec2> voxels_corners;
    std::map<unsigned long long int, glm::ivec2>::iterator it_corners;
//    std::map<unsigned long long int, int> voxels_corners;
//    std::map<unsigned long long int, int>::iterator it_corners;
    int t_x=0,t_y=0,t_z=0;
    int t_xy=0,t_xz=0,t_yz=0;
    int t_xyz=0;
    int t_tot=0;
    int z0[27];
    for (int n=0; n<27; n++) z0[n]=0;
    int i=1;
    for (auto u : voxels) {
        one=u;
        int one_x=(one.x-bmin_x);
        int one_y=(one.y-bmin_y);
        int one_z=(one.z-bmin_z);
        unsigned long long int index_first=(one_x) + (one_z)*bdif_x + (one_y)*x_z;
        it = voxels_indexed.find(index_first);
        if ( it == voxels_indexed.end() ) {
            printf("Error\n");
            printf("voxels[%6d]=%15llu -> (%d,%d,%d),(%d,%d,%d),(%d)\n",
                    index_second, index_first, one.y, one.x, one.z, one.r, one.g, one.b, one.l );
        } else {
            int x=0,y=0,z=0;
            int xy=0,xz=0,yz=0;
            int xyz=0,tot=0;
            if (voxels_indexed.find(index_first-1)!=voxels_indexed.end()) {
                x++;
            } else {
                it_corners = voxels_corners.find(index_first);
                if ( it_corners == voxels_corners.end() ) voxels_corners.insert(std::make_pair(index_first,glm::ivec2(1,i++))); else it_corners->second.x++;

                it_corners = voxels_corners.find(index_first+bdif_x);
                if ( it_corners == voxels_corners.end() ) voxels_corners.insert(std::make_pair(index_first+bdif_x,glm::ivec2(1,i++))); else it_corners->second.x++;

                it_corners = voxels_corners.find(index_first+bdif_x+x_z);
                if ( it_corners == voxels_corners.end() ) voxels_corners.insert(std::make_pair(index_first+bdif_x+x_z,glm::ivec2(1,i++))); else it_corners->second.x++;

                it_corners = voxels_corners.find(index_first+x_z);
                if ( it_corners == voxels_corners.end() ) voxels_corners.insert(std::make_pair(index_first+x_z,glm::ivec2(1,i++))); else it_corners->second.x++;
            }

            if (voxels_indexed.find(index_first+1)!=voxels_indexed.end()) {
                x++;
            } else {
                it_corners = voxels_corners.find(index_first+1);
                if ( it_corners == voxels_corners.end() ) voxels_corners.insert(std::make_pair(index_first+1,glm::ivec2(1,i++))); else it_corners->second.x++;

                it_corners = voxels_corners.find(index_first+1+x_z);
                if ( it_corners == voxels_corners.end() ) voxels_corners.insert(std::make_pair(index_first+1+x_z,glm::ivec2(1,i++))); else it_corners->second.x++;

                it_corners = voxels_corners.find(index_first+1+bdif_x+x_z);
                if ( it_corners == voxels_corners.end() ) voxels_corners.insert(std::make_pair(index_first+1+bdif_x+x_z,glm::ivec2(1,i++))); else it_corners->second.x++;

                it_corners = voxels_corners.find(index_first+1+bdif_x);
                if ( it_corners == voxels_corners.end() ) voxels_corners.insert(std::make_pair(index_first+1+bdif_x,glm::ivec2(1,i++))); else it_corners->second.x++;
            }

            if (voxels_indexed.find(index_first-bdif_x)!=voxels_indexed.end()) {
                z++;
            } else {
                it_corners = voxels_corners.find(index_first);
                if ( it_corners == voxels_corners.end() ) voxels_corners.insert(std::make_pair(index_first,glm::ivec2(1,i++))); else it_corners->second.x++;

                it_corners = voxels_corners.find(index_first+x_z);
                if ( it_corners == voxels_corners.end() ) voxels_corners.insert(std::make_pair(index_first+x_z,glm::ivec2(1,i++))); else it_corners->second.x++;

                it_corners = voxels_corners.find(index_first+1+x_z);
                if ( it_corners == voxels_corners.end() ) voxels_corners.insert(std::make_pair(index_first+1+x_z,glm::ivec2(1,i++))); else it_corners->second.x++;

                it_corners = voxels_corners.find(index_first+1);
                if ( it_corners == voxels_corners.end() ) voxels_corners.insert(std::make_pair(index_first+1,glm::ivec2(1,i++))); else it_corners->second.x++;
            }

            if (voxels_indexed.find(index_first+bdif_x)!=voxels_indexed.end()) {
                z++;
            } else {
                it_corners = voxels_corners.find(index_first+bdif_x);
                if ( it_corners == voxels_corners.end() ) voxels_corners.insert(std::make_pair(index_first+bdif_x,glm::ivec2(1,i++))); else it_corners->second.x++;

                it_corners = voxels_corners.find(index_first+1+bdif_x);
                if ( it_corners == voxels_corners.end() ) voxels_corners.insert(std::make_pair(index_first+1+bdif_x,glm::ivec2(1,i++))); else it_corners->second.x++;

                it_corners = voxels_corners.find(index_first+1+bdif_x+x_z);
                if ( it_corners == voxels_corners.end() ) voxels_corners.insert(std::make_pair(index_first+1+bdif_x+x_z,glm::ivec2(1,i++))); else it_corners->second.x++;

                it_corners = voxels_corners.find(index_first+bdif_x+x_z);
                if ( it_corners == voxels_corners.end() ) voxels_corners.insert(std::make_pair(index_first+bdif_x+x_z,glm::ivec2(1,i++))); else it_corners->second.x++;
            }

            if (voxels_indexed.find(index_first-x_z)!=voxels_indexed.end()) {
                y++;
            } else {
                it_corners = voxels_corners.find(index_first);
                if ( it_corners == voxels_corners.end() ) voxels_corners.insert(std::make_pair(index_first,glm::ivec2(1,i++))); else it_corners->second.x++;

                it_corners = voxels_corners.find(index_first+1);
                if ( it_corners == voxels_corners.end() ) voxels_corners.insert(std::make_pair(index_first+1,glm::ivec2(1,i++))); else it_corners->second.x++;

                it_corners = voxels_corners.find(index_first+1+bdif_x);
                if ( it_corners == voxels_corners.end() ) voxels_corners.insert(std::make_pair(index_first+1+bdif_x,glm::ivec2(1,i++))); else it_corners->second.x++;

                it_corners = voxels_corners.find(index_first+bdif_x);
                if ( it_corners == voxels_corners.end() ) voxels_corners.insert(std::make_pair(index_first+bdif_x,glm::ivec2(1,i++))); else it_corners->second.x++;
            }

            if (voxels_indexed.find(index_first+x_z)!=voxels_indexed.end()) {
                y++;
            } else {
                it_corners = voxels_corners.find(index_first+x_z);
                if ( it_corners == voxels_corners.end() ) voxels_corners.insert(std::make_pair(index_first+x_z,glm::ivec2(1,i++))); else it_corners->second.x++;

                it_corners = voxels_corners.find(index_first+bdif_x+x_z);
                if ( it_corners == voxels_corners.end() ) voxels_corners.insert(std::make_pair(index_first+bdif_x+x_z,glm::ivec2(1,i++))); else it_corners->second.x++;

                it_corners = voxels_corners.find(index_first+1+bdif_x+x_z);
                if ( it_corners == voxels_corners.end() ) voxels_corners.insert(std::make_pair(index_first+1+bdif_x+x_z,glm::ivec2(1,i++))); else it_corners->second.x++;

                it_corners = voxels_corners.find(index_first+1+x_z);
                if ( it_corners == voxels_corners.end() ) voxels_corners.insert(std::make_pair(index_first+1+x_z,glm::ivec2(1,i++))); else it_corners->second.x++;
            }

/*
            if (voxels_indexed.find(index_first-1-bdif_x)!=voxels_indexed.end()) xz++;
            if (voxels_indexed.find(index_first-1+bdif_x)!=voxels_indexed.end()) xz++;
            if (voxels_indexed.find(index_first+1-bdif_x)!=voxels_indexed.end()) xz++;
            if (voxels_indexed.find(index_first+1+bdif_x)!=voxels_indexed.end()) xz++;

            if (voxels_indexed.find(index_first-1-x_z)!=voxels_indexed.end()) xy++;
            if (voxels_indexed.find(index_first-1+x_z)!=voxels_indexed.end()) xy++;
            if (voxels_indexed.find(index_first+1-x_z)!=voxels_indexed.end()) xy++;
            if (voxels_indexed.find(index_first+1+x_z)!=voxels_indexed.end()) xy++;

            if (voxels_indexed.find(index_first-bdif_x-x_z)!=voxels_indexed.end()) yz++;
            if (voxels_indexed.find(index_first-bdif_x+x_z)!=voxels_indexed.end()) yz++;
            if (voxels_indexed.find(index_first+bdif_x-x_z)!=voxels_indexed.end()) yz++;
            if (voxels_indexed.find(index_first+bdif_x+x_z)!=voxels_indexed.end()) yz++;

            if (voxels_indexed.find(index_first-1-bdif_x-x_z)!=voxels_indexed.end()) xyz++;
            if (voxels_indexed.find(index_first-1-bdif_x+x_z)!=voxels_indexed.end()) xyz++;
            if (voxels_indexed.find(index_first-1+bdif_x-x_z)!=voxels_indexed.end()) xyz++;
            if (voxels_indexed.find(index_first-1+bdif_x+x_z)!=voxels_indexed.end()) xyz++;
            if (voxels_indexed.find(index_first+1-bdif_x-x_z)!=voxels_indexed.end()) xyz++;
            if (voxels_indexed.find(index_first+1-bdif_x+x_z)!=voxels_indexed.end()) xyz++;
            if (voxels_indexed.find(index_first+1+bdif_x-x_z)!=voxels_indexed.end()) xyz++;
            if (voxels_indexed.find(index_first+1+bdif_x+x_z)!=voxels_indexed.end()) xyz++;

//            printf("Connections: x(%d) y(%d) z(%d) xy(%d) xz(%d) yz(%d) xyz(%d) tot(%2d)  ",
//                   x,y,z,xy,xz,yz,xyz,x+y+z+xy+xz+yz+xyz);
//            printf("voxels[%6d]=%15llu -> (%d,%d,%d),(%d,%d,%d),(%d)\n",
//                    index_second, index_first, one.y, one.x, one.z, one.r, one.g, one.b, one.l );
*/
            t_x+=x;
            t_y+=y;
            t_z+=z;
//            t_xy+=xy;
//            t_xz+=xz;
//            t_yz+=yz;
//            t_xyz+=xyz;
//            tot=x+y+z+xy+xz+yz+xyz;
            tot=x+y+z;
            t_tot+=tot;
            z0[tot]++;
        }
        if (!(index_second%1000)) {
            float perc=100.0*(float)index_second/(float)voxels.size();
            printf("\r%5.3f%% ",perc);
            quick_toggle();
        }

//        if (!(index_second%100)) quick_toggle();
        index_second++;
    }
    if (voxels.size()>0) {
        float perc=100.0*(float)index_second/(float)voxels.size();
        printf("\r%5.3f%% ",perc);
    }
    printf(" ready (%d)\n",index_second);
    if (index_second>0) {
//        printf("avg:   x=%5.3f\n",(float)t_x/(float)index_second);
//        printf("avg:   y=%5.3f\n",(float)t_y/(float)index_second);
//        printf("avg:   z=%5.3f\n",(float)t_z/(float)index_second);
//        printf("avg:  xy=%5.3f\n",(float)t_xy/(float)index_second);
//        printf("avg:  xz=%5.3f\n",(float)t_xz/(float)index_second);
//        printf("avg:  yz=%5.3f\n",(float)t_yz/(float)index_second);
//        printf("avg: xyz=%5.3f\n",(float)t_xyz/(float)index_second);
//        printf("avg: tot=%5.3f\n",(float)t_tot/(float)index_second);
        printf("avg. connected faces/cube sides:  +/-x , +/-y , +/-z = %5.3f\n",(float)(t_x+t_y+t_z)/(float)index_second);
//        printf("avg:  x+y+z+xy+xz+yz=%5.3f\n",(float)(t_x+t_y+t_z+t_xy+t_xz+t_yz)/(float)index_second);
        t_tot=0;
//        for (int n=0; n<27; n++) {
        for (int n=0; n<7; n++) {
            printf("#%2d = %6d",n,z0[n]);
            if (n==0) printf(" no faces connected to other cube(s)\n");
            else if (n==6) printf(" all faces connected (hidden cube)\n");
            else printf("\n");
            t_tot+=z0[n];
        }
        printf("#tot= %6d\n",t_tot);
    }
    printf("#cubes * 6    =%d faces\n",voxels.size()*6);
    printf("#faces hidden =%d faces\n",t_x+t_y+t_z);
    printf("#faces left   =%d faces\n",voxels.size()*6 - (t_x+t_y+t_z) );
    printf("reduced to %5.3f%%\n", 100.0*(float)(voxels.size()*6 - (t_x+t_y+t_z))/(float)(voxels.size()*6.0)  );

    int zv[24];
    for (int n=0; n<24; n++) zv[n]=0;
    printf("#Vertices=%d\n",voxels_corners.size());
    t_tot=0;

    char filename[2000];
    mkdir("../objects");
    sprintf(filename,"%s/%s.obj","../objects",picture_file);
    FILE* out;
    if ( (out=fopen(filename,"w"))==NULL) {
        printf("Cannot open %s for writing.\n",filename);
        return;
    }
    char line[2000];
    for (int n=0; n<16; n++) {
        sprintf(line,"if not exist ..\\objects\\concrete_%02d.png copy resources\\concrete_%02d.png ..\\objects\\concrete_%02d.png",n,n,n);
        system(line);
    }

//    system("if not exist ..\\objects\\concrete.png copy resources\\concrete_64x64.png ..\\objects\\concrete.png");

    system("if not exist ..\\objects\\concrete.mtl copy resources\\concrete.mtl ..\\objects");

    sprintf(line, "mtllib concrete.mtl\n"); fprintf(out,line); // printf(line);

//kloten
//    sprintf(line, "o %s\n",picture_file); fprintf(out,line); // printf(line);
//    fprintf(out, "# vertices\n");

    index_second=0;

//    std::map<unsigned long long int, glm::ivec2>::iterator it_corners;

    if (voxels_corners.size()>0) {

        for (it_corners = voxels_corners.begin(); it_corners != voxels_corners.end(); it_corners++) {
//        for (auto u : voxels_corners) {
//            unsigned long long int index_first=u.first;  // (one.x-bmin_x) + (one.z-bmin_z)*bdif_x + (one.y-bmin_y)*x_z;

            unsigned long long int index_first=it_corners->first;  // (one.x-bmin_x) + (one.z-bmin_z)*bdif_x + (one.y-bmin_y)*x_z;

            int y=(int)(index_first/(unsigned long long int)x_z);
            index_first=index_first-(unsigned long long int)y*(unsigned long long int)x_z;

            int z=(int)(index_first/(unsigned long long int)bdif_x);
            index_first=index_first-(unsigned long long int)z*(unsigned long long int)bdif_x;

            int x=(int)index_first;
            y=y+bmin_y;
            z=z+bmin_z;
            x=x+bmin_x;

//            sprintf(line,"v %.1f %.1f %.1f #index=%d\n",(float)y,(float)x,(float)z,u.second.y);
            sprintf(line,"v %.1f %.1f %.1f\n",(float)(y-offset_x),(float)(x-offset_y),(float)(z-offset_z));
            while (replace_str(line,",","."));    fprintf(out,line);    //1 printf(line);
//            zv[u.second.x]++;
            zv[it_corners->second.x]++;
//            t_tot+=u.second.x;
            t_tot+=it_corners->second.x;

            if (!(index_second%1000)) {
                float perc=100.0*(float)index_second/(float)voxels_corners.size();
                printf("\r%5.3f%% ",perc);
                quick_toggle();
            }

//            if (!(index_second%100)) quick_toggle();
            index_second++;
//            u.second.y=index_second;
            it_corners->second.y=index_second;
//            it_corners->second=glm::ivec2(it_corners->second.x,index_second);
//            printf(line,"v %.1f %.1f %.1f #index=%d\n",(float)y,(float)x,(float)z,u.second.y);
//            printf("v %.1f %.1f %.1f #index=%d\n",(float)y,(float)x,(float)z,it_corners->second.y);
        }
        if (voxels_corners.size()>0) {
            float perc=100.0*(float)index_second/(float)voxels_corners.size();
            printf("\r%5.3f%% ",perc);
        }
        for (int n=0; n<24; n++) {
            if (zv[n]!=0) printf("#%2d = %6d",n,zv[n]);
            if (n==3) printf(" one connected cube\n");
//            else if (n==8) printf(" 2x2x2 connected cubes\n");
            else if (zv[n]!=0) printf("\n");
        }
        printf("avg: %5.3f connected faces / vertice\n",(float)t_tot/(float)voxels_corners.size());
        printf("avg: %5.3f vertices / block\n",(float)voxels_corners.size()/voxels.size());
        printf("#cubes * 8=%d vertices\n",voxels.size()*8);
        printf("reduced to %5.3f%%\n",100.0*(float)voxels_corners.size()/(float)(voxels.size()*8.0));
    }

    fprintf(out, "# UV\n");
    for (int n=0; n<1; n++) {
        float left=(float)n*1.0/1.0+2.0/64.0;
        float right=((float)n+1.0)*1.0/1.0-2.0/64.0;
        sprintf(line,"vt %f %f\n",left,2.0/64.0); while (replace_str(line,",",".")); fprintf(out,line);
        sprintf(line,"vt %f %f\n",right,2.0/64.0); while (replace_str(line,",",".")); fprintf(out,line);
        sprintf(line,"vt %f %f\n",right,1.0-2.0/64.0); while (replace_str(line,",",".")); fprintf(out,line);
        sprintf(line,"vt %f %f\n",left,1.0-2.0/64.0); while (replace_str(line,",",".")); fprintf(out,line);
    }
    for (int n=0; n<1; n++) {
        float left=(float)n*1.0/1.0+12.0/64.0;
        float right=((float)n+1.0)*1.0/1.0-12.0/64.0;
        sprintf(line,"vt %f %f\n",left,12.0/64.0); while (replace_str(line,",",".")); fprintf(out,line);
        sprintf(line,"vt %f %f\n",right,12.0/64.0); while (replace_str(line,",",".")); fprintf(out,line);
        sprintf(line,"vt %f %f\n",right,1.0-12.0/64.0); while (replace_str(line,",",".")); fprintf(out,line);
        sprintf(line,"vt %f %f\n",left,1.0-12.0/64.0); while (replace_str(line,",",".")); fprintf(out,line);
    }
//    fprintf(out, "vt 0.0 0.0\n");
//    fprintf(out, "vt 0.0625 0.0\n");
//    fprintf(out, "vt 0.0625 1.0\n");

//    fprintf(out, "usemtl concrete\n");

    index_second=0;

    int color_index_previous=-1;
    for (auto u : voxels) {
        one=u;
        if (one.l!=color_index_previous) {
            fprintf(out, "o concrete_%02d\n",one.l);
            fprintf(out, "usemtl concrete_%02d\n",one.l);
            color_index_previous=one.l;
        }
        int one_x=(one.x-bmin_x);
        int one_y=(one.y-bmin_y);
        int one_z=(one.z-bmin_z);
        unsigned long long int index_first=(one_x) + (one_z)*bdif_x + (one_y)*x_z;
        it = voxels_indexed.find(index_first);
        size_t vertice_index;
        if ( it == voxels_indexed.end() ) {
            printf("Error\n");
            printf("voxels[%6d]=%15llu -> (%d,%d,%d),(%d,%d,%d),(%d)\n",
                    index_second, index_first, one.y, one.x, one.z, one.r, one.g, one.b, one.l );
        } else {

//            int color=ret_color(u.r,u.g,u.b);
//            int color_index=1 + color*4;
            int color_index=1; // add side index....kloten

//            it=voxels_indexed.find(index_first-1); if (it!=voxels_indexed.end()) {

//          BOTTOM
            if (voxels_indexed.find(index_first-1)!=voxels_indexed.end()) {
            } else {
                it_corners = voxels_corners.find(index_first+x_z);
                if ( it_corners == voxels_corners.end() ) printf("Error 1\n");
                else {
                    vertice_index = it_corners->second.y;
                    it_corners->second.x--;
                    if (it_corners->second.x<0) printf("Error 2\n");
                    else {
                        sprintf(line,"f %d/%d",vertice_index,color_index+3); while (replace_str(line,",",".")); fprintf(out,line);
                    }
                }

                it_corners = voxels_corners.find(index_first+bdif_x+x_z);
                if ( it_corners == voxels_corners.end() ) printf("Error 1\n");
                else {
                    vertice_index = it_corners->second.y;
                    it_corners->second.x--;
                    if (it_corners->second.x<0) printf("Error 2\n");
                    else {
                        sprintf(line," %d/%d",vertice_index,color_index+0); while (replace_str(line,",",".")); fprintf(out,line);
                    }
                }

                it_corners = voxels_corners.find(index_first+bdif_x);
                if ( it_corners == voxels_corners.end() ) printf("Error 1\n");
                else {
                    vertice_index = it_corners->second.y;
                    it_corners->second.x--;
                    if (it_corners->second.x<0) printf("Error 2\n");
                    else {
                        sprintf(line," %d/%d",vertice_index,color_index+1); while (replace_str(line,",",".")); fprintf(out,line);
                    }
                }

                it_corners = voxels_corners.find(index_first);
                if ( it_corners == voxels_corners.end() ) printf("Error 1\n");
                else {
                    vertice_index = it_corners->second.y;
                    it_corners->second.x--;
                    if (it_corners->second.x<0) printf("Error 2\n");
                    else {
                        sprintf(line," %d/%d\n",vertice_index,color_index+2); while (replace_str(line,",",".")); fprintf(out,line);
                    }
                }
            }

//          TOP
            if (voxels_indexed.find(index_first+1)!=voxels_indexed.end()) {
            } else {

                it_corners = voxels_corners.find(index_first+1+bdif_x);
                if ( it_corners == voxels_corners.end() ) printf("Error 1\n");
                else {
                    vertice_index = it_corners->second.y;
                    it_corners->second.x--;
                    if (it_corners->second.x<0) printf("Error 2\n");
                    else {
                        sprintf(line,"f %d/%d",vertice_index,color_index); while (replace_str(line,",",".")); fprintf(out,line);
                    }
                }

                it_corners = voxels_corners.find(index_first+1+bdif_x+x_z);
                if ( it_corners == voxels_corners.end() ) printf("Error 1\n");
                else {
                    vertice_index = it_corners->second.y;
                    it_corners->second.x--;
                    if (it_corners->second.x<0) printf("Error 2\n");
                    else {
                        sprintf(line," %d/%d",vertice_index,color_index+1); while (replace_str(line,",",".")); fprintf(out,line);
                    }
                }

                it_corners = voxels_corners.find(index_first+1+x_z);
                if ( it_corners == voxels_corners.end() ) printf("Error 1\n");
                else {
                    vertice_index = it_corners->second.y;
                    it_corners->second.x--;
                    if (it_corners->second.x<0) printf("Error 2\n");
                    else {
                        sprintf(line," %d/%d",vertice_index,color_index+2); while (replace_str(line,",",".")); fprintf(out,line);
                    }
                }

                it_corners = voxels_corners.find(index_first+1);
                if ( it_corners == voxels_corners.end() ) printf("Error 1\n");
                else {
                    vertice_index = it_corners->second.y;
                    it_corners->second.x--;
                    if (it_corners->second.x<0) printf("Error 2\n");
                    else {
                        sprintf(line," %d/%d\n",vertice_index,color_index+3); while (replace_str(line,",",".")); fprintf(out,line);
                    }
                }
            }

            //back
            if (voxels_indexed.find(index_first-bdif_x)!=voxels_indexed.end()) {
            } else {

                it_corners = voxels_corners.find(index_first+1);
                if ( it_corners == voxels_corners.end() ) printf("Error 1\n");
                else {
                    vertice_index = it_corners->second.y;
                    it_corners->second.x--;
                    if (it_corners->second.x<0) printf("Error 2\n");
                    else {
                        sprintf(line,"f %d/%d",vertice_index,color_index+2); while (replace_str(line,",",".")); fprintf(out,line);
                    }
                }

                it_corners = voxels_corners.find(index_first+1+x_z);
                if ( it_corners == voxels_corners.end() ) printf("Error 1\n");
                else {
                    vertice_index = it_corners->second.y;
                    it_corners->second.x--;
                    if (it_corners->second.x<0) printf("Error 2\n");
                    else {
                        sprintf(line," %d/%d",vertice_index,color_index+3); while (replace_str(line,",",".")); fprintf(out,line);
                    }
                }

                it_corners = voxels_corners.find(index_first+x_z);
                if ( it_corners == voxels_corners.end() ) printf("Error 1\n");
                else {
                    vertice_index = it_corners->second.y;
                    it_corners->second.x--;
                    if (it_corners->second.x<0) printf("Error 2\n");
                    else {
                        sprintf(line," %d/%d",vertice_index,color_index+0); while (replace_str(line,",",".")); fprintf(out,line);
                    }
                }

                it_corners = voxels_corners.find(index_first);
                if ( it_corners == voxels_corners.end() ) printf("Error 1\n");
                else {
                    vertice_index = it_corners->second.y;
                    it_corners->second.x--;
                    if (it_corners->second.x<0) printf("Error 2\n");
                    else {
                        sprintf(line," %d/%d\n",vertice_index,color_index+1); while (replace_str(line,",",".")); fprintf(out,line);
                    }
                }
            }

//          front
            if (voxels_indexed.find(index_first+bdif_x)!=voxels_indexed.end()) {
            } else {

                it_corners = voxels_corners.find(index_first+bdif_x+x_z);
                if ( it_corners == voxels_corners.end() ) printf("Error 1\n");
                else {
                    vertice_index = it_corners->second.y;
                    it_corners->second.x--;
                    if (it_corners->second.x<0) printf("Error 2\n");
                    else {
                        sprintf(line,"f %d/%d",vertice_index,color_index+1); while (replace_str(line,",",".")); fprintf(out,line);
                    }
                }

                it_corners = voxels_corners.find(index_first+1+bdif_x+x_z);
                if ( it_corners == voxels_corners.end() ) printf("Error 1\n");
                else {
                    vertice_index = it_corners->second.y;
                    it_corners->second.x--;
                    if (it_corners->second.x<0) printf("Error 2\n");
                    else {
                        sprintf(line," %d/%d",vertice_index,color_index+2); while (replace_str(line,",",".")); fprintf(out,line);
                    }
                }

                it_corners = voxels_corners.find(index_first+1+bdif_x);
                if ( it_corners == voxels_corners.end() ) printf("Error 1\n");
                else {
                    vertice_index = it_corners->second.y;
                    it_corners->second.x--;
                    if (it_corners->second.x<0) printf("Error 2\n");
                    else {
                        sprintf(line," %d/%d",vertice_index,color_index+3); while (replace_str(line,",",".")); fprintf(out,line);
                    }
                }

                it_corners = voxels_corners.find(index_first+bdif_x);
                if ( it_corners == voxels_corners.end() ) printf("Error 1\n");
                else {
                    vertice_index = it_corners->second.y;
                    it_corners->second.x--;
                    if (it_corners->second.x<0) printf("Error 2\n");
                    else {
                        sprintf(line," %d/%d\n",vertice_index,color_index+0); while (replace_str(line,",",".")); fprintf(out,line);
                    }
                }
            }

//          left?
            if (voxels_indexed.find(index_first-x_z)!=voxels_indexed.end()) {
            } else {

                it_corners = voxels_corners.find(index_first+bdif_x);
                if ( it_corners == voxels_corners.end() ) printf("Error 1\n");
                else {
                    vertice_index = it_corners->second.y;
                    it_corners->second.x--;
                    if (it_corners->second.x<0) printf("Error 2\n");
                    else {
                        sprintf(line,"f %d/%d",vertice_index,color_index+1); while (replace_str(line,",",".")); fprintf(out,line);
                    }
                }

                it_corners = voxels_corners.find(index_first+1+bdif_x);
                if ( it_corners == voxels_corners.end() ) printf("Error 1\n");
                else {
                    vertice_index = it_corners->second.y;
                    it_corners->second.x--;
                    if (it_corners->second.x<0) printf("Error 2\n");
                    else {
                        sprintf(line," %d/%d",vertice_index,color_index+2); while (replace_str(line,",",".")); fprintf(out,line);
                    }
                }

                it_corners = voxels_corners.find(index_first+1);
                if ( it_corners == voxels_corners.end() ) printf("Error 1\n");
                else {
                    vertice_index = it_corners->second.y;
                    it_corners->second.x--;
                    if (it_corners->second.x<0) printf("Error 2\n");
                    else {
                        sprintf(line," %d/%d",vertice_index,color_index+3); while (replace_str(line,",",".")); fprintf(out,line);
                    }
                }

                it_corners = voxels_corners.find(index_first);
                if ( it_corners == voxels_corners.end() ) printf("Error 1\n");
                else {
                    vertice_index = it_corners->second.y;
                    it_corners->second.x--;
                    if (it_corners->second.x<0) printf("Error 2\n");
                    else {
                        sprintf(line," %d/%d\n",vertice_index,color_index+0); while (replace_str(line,",",".")); fprintf(out,line);
                    }
                }
            }

//          right?
            if (voxels_indexed.find(index_first+x_z)!=voxels_indexed.end()) {
            } else {

                it_corners = voxels_corners.find(index_first+1+x_z);
                if ( it_corners == voxels_corners.end() ) printf("Error 1\n");
                else {
                    vertice_index = it_corners->second.y;
                    it_corners->second.x--;
                    if (it_corners->second.x<0) printf("Error 2\n");
                    else {
                        sprintf(line,"f %d/%d",vertice_index,color_index+2); while (replace_str(line,",",".")); fprintf(out,line);
                    }
                }

                it_corners = voxels_corners.find(index_first+1+bdif_x+x_z);
                if ( it_corners == voxels_corners.end() ) printf("Error 1\n");
                else {
                    vertice_index = it_corners->second.y;
                    it_corners->second.x--;
                    if (it_corners->second.x<0) printf("Error 2\n");
                    else {
                        sprintf(line," %d/%d",vertice_index,color_index+3); while (replace_str(line,",",".")); fprintf(out,line);
                    }
                }

                it_corners = voxels_corners.find(index_first+bdif_x+x_z);
                if ( it_corners == voxels_corners.end() ) printf("Error 1\n");
                else {
                    vertice_index = it_corners->second.y;
                    it_corners->second.x--;
                    if (it_corners->second.x<0) printf("Error 2\n");
                    else {
                        sprintf(line," %d/%d",vertice_index,color_index+0); while (replace_str(line,",",".")); fprintf(out,line);
                    }
                }

                it_corners = voxels_corners.find(index_first+x_z);
                if ( it_corners == voxels_corners.end() ) printf("Error 1\n");
                else {
                    vertice_index = it_corners->second.y;
                    it_corners->second.x--;
                    if (it_corners->second.x<0) printf("Error 2\n");
                    else {
                        sprintf(line," %d/%d\n",vertice_index,color_index+1); while (replace_str(line,",",".")); fprintf(out,line);
                    }
                }
            }
        }
        if (!(index_second%1000)) {
            float perc=100.0*(float)index_second/(float)voxels.size();
            printf("\r%5.3f%% ",perc);
            quick_toggle();
        }
        index_second++;
    }
    if (voxels.size()>0) {
        float perc=100.0*(float)index_second/(float)voxels.size();
        printf("\r%5.3f%% ",perc);
    }

    fclose(out);
    printf("Ready\n");
}



int REGION_TO_VOXEL_stop=0;
int REGION_TO_VOXEL_running=0;

void REGION_TO_VOXEL_THREAD();

sf::Thread REGION_TO_VOXEL(&REGION_TO_VOXEL_THREAD);

void launch_REGION_TO_VOXEL()
{
    if (REGION_TO_VOXEL_running==1)
    {
        printf("Region to voxel thread already running\n");
        return;
    }
    REGION_TO_VOXEL_running=1;
    REGION_TO_VOXEL.launch();
}

void regions_to_voxelfiles();

void REGION_TO_VOXEL_THREAD()
{
    printf("Region to voxel thread starting");
    sf::sleep(sf::seconds(0.5));
    printf(".");
    sf::sleep(sf::seconds(0.5));
    printf(".");
    sf::sleep(sf::seconds(0.5));
    printf(".");
    sf::sleep(sf::seconds(0.5));
    printf(".\n");
    regions_to_voxelfiles();
    REGION_TO_VOXEL_stop=0;
    REGION_TO_VOXEL_running=0;
    SFMLView1.requestFocus();
    printf("Region to voxel thread end\n");
}


void terminate_REGION_TO_VOXEL()
{
    REGION_TO_VOXEL.terminate();
}

void regions_to_voxelfiles() {
    char voxel_file[200];
    mkdir("../voxels");
    cubic=false;
    int num_regions=0;
    std::map<long long int, cubic_region> cubic_regions_mapped;
    std::map<long long int, cubic_region> cubic_regions_mapped_unique;
    std::map<long long int, cubic_region>::iterator it;

    cubic_region one_cubic_region;
    printf("\n");

    DIR* dr_ROOT = opendir("/saves/tovoxels/region");
    struct dirent *de_ROOT;
    while ((de_ROOT = readdir(dr_ROOT)) != NULL) {
//        printf("DIR: /saves/tovoxels/region/%s\n",de_ROOT->d_name);
        for(int i=0;i<strlen(de_ROOT->d_name);i++){
            de_ROOT->d_name[i] = tolower(de_ROOT->d_name[i]);
        }

        if ((strstr(de_ROOT->d_name, "done")) != NULL) {
            sscanf(de_ROOT->d_name,"done%d",&region_floor);
            char floor_dir[2000];
            sprintf(floor_dir,"/saves/tovoxels/region/%s",de_ROOT->d_name);
            printf("DIR: /saves/tovoxels/region/%s\n",de_ROOT->d_name);

            DIR* dr = opendir(floor_dir);
            struct dirent *de;
            while ((de = readdir(dr)) != NULL) {
//                            printf("DIR: /saves/test/region/%s/%s\n",de_ROOT->d_name,de->d_name);
                for(int i=0;i<strlen(de->d_name);i++){
                    de->d_name[i] = tolower(de->d_name[i]);
                }
                if ((strstr(de->d_name, ".mca")) != NULL) {
                    int x,z;
                    sscanf(de->d_name,"r.%d.%d.mca",&x,&z);
                    printf("r.%d.%d.mca ",x,z);
                    one_cubic_region.x=x;
                    one_cubic_region.z=z;
                    one_cubic_region.region_floor=region_floor;
//                            cubic_regions.push_back(one_cubic_region);
                    cubic_regions_mapped.insert(std::make_pair( z*100000000+100*x+region_floor, one_cubic_region));
                }
            }
            closedir(dr);
        }

        printf("\n\n");
    }
    closedir(dr_ROOT);

    char region_dir[2000];
    sprintf(region_dir,"/saves/tovoxels/region");
    printf("DIR: /saves/tovoxels/region\n");

    DIR* dr2 = opendir(region_dir);
    struct dirent *de2;
    while ((de2 = readdir(dr2)) != NULL) {
//                            printf("DIR: /saves/test/region/%s/%s\n",de_ROOT->d_name,de->d_name);
        for(int i=0;i<strlen(de2->d_name);i++){
            de2->d_name[i] = tolower(de2->d_name[i]);
        }
        if ((strstr(de2->d_name, ".mca")) != NULL) {
            int x,z;
            sscanf(de2->d_name,"r.%d.%d.mca",&x,&z);
            printf("r.%d.%d.mca ",x,z);
            one_cubic_region.x=x;
            one_cubic_region.z=z;
            one_cubic_region.region_floor=region_floor;
//                            cubic_regions.push_back(one_cubic_region);
            cubic_regions_mapped.insert(std::make_pair( z*100000000+100*x+region_floor, one_cubic_region));
        }
    }
    closedir(dr2);
    voxels.clear();

    if (cubic_regions_mapped.size()>0) {
        int prev_x=-99999999;
        int prev_z=-99999999;
        it = cubic_regions_mapped.begin();

        bool does_exist;
        while(it != cubic_regions_mapped.end()) {
            int x=it->second.x;
            int z=it->second.z;
            region_floor=it->second.region_floor;
            if (x==prev_x && z==prev_z) {
//                printf(",");
            }
            printf("\nRegion(%d,%d) ",x,z);
            if (x!=prev_x || z!=prev_z) {
                if (prev_x!=-99999999) {
//                                printf("\n");
                }
                sprintf(voxel_file,"../voxels/r.%d.%d.vox",x,z);
                does_exist=false;
//                does_exist=file_exists(voxel_file);
//                if (does_exist) printf("Voxelfile exists: %s, skipping\n",voxel_file);
//                else printf("\n");

                hit_one_region* hit_one=findRegion(x,z);
                if (hit_one==NULL) {
                    vector_hit_regions.push_back(hit_one_region(x,z));
                    hit_one=&vector_hit_regions[vector_hit_regions.size()-1];
                }
                hit_one->index11=1;
                hit_one->index12=1;
            }
//                        if (!flushing && (mirror==3 || does_exist==false) ) {

            if (does_exist==false ) {
                printf("floor (%d)\n",region_floor);
                bool plot_only_old=plot_only;
                mirror==3;
                plot_only=1;
                scan_image.create(512,512,sf::Color(128,128,128,128));
                plotting=1;
                MCEDITOR_running=1;
                get_block=true;
                main_mceditor6_fixed(x, z, region_block);
                printf("Loaded region file. Clearing: ");
                editor.mca_coder.clearModification();
//                printf(" 2");
//                editor.clearArrays(512,512,256);
                printf(" Ready\n");

                if (voxels.size()>0) {
                    char fname[200];
                    FILE* voxel_file_pointer=fopen(voxel_file,"a");
                    if (voxel_file_pointer!=NULL) {
                        printf("Appending voxels to %s\n",voxel_file);
                        for (auto u : voxels) {
                            if (u.l>0) {
                                fprintf(voxel_file_pointer,"(%d,%d,%d),(%d,%d,%d),(%d)\n",
                                        u.y, u.x, u.z,  u.r/u.l,u.g/u.l, u.b/u.l,  u.l );
                            }
                        }
                        fclose(voxel_file_pointer);
                    } else {
                        printf("Error writing to %s\n",fname);
                    }
                    voxels.clear();
                }

                get_block=false;
                MCEDITOR_running=0;
                plotting=0;
                plot_only=plot_only_old;
            }
            prev_x=x;
            prev_z=z;
            it++;
        }
        printf("\n");
    }
}

