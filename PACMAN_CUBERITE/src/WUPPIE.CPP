//#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
//#include <SFML/Graphics/Image.hpp>
//#include <SFML/Graphics/Texture.hpp>
//#include <SFML/Graphics/RenderWindow.hpp>
//#include <SFML/OpenGL.hpp>
//#include <SFML/System.hpp>
#include <SFML/Graphics/Rect.hpp>
//#include <SFML/Network.hpp>
//#include <SFML/System/Mutex.hpp>
#include <glm/glm.hpp>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <cstring>

#include <../VOXEL.HPP>
#include <winsock2.h>
#include <dirent.h>

extern int mazemovex_voxel;
extern int mazemovey_voxel;
extern sf::Mutex cube_plot;
extern int plot_cubes;
extern float scale_factor;
extern sf::VertexArray m_pointCloud3;

extern float voxel_bottom;
int small=0;
extern int offset_real_y;
extern int block_count;
extern glm::ivec3* blocks;
extern bool wuppie_all;
void to_plot_cubes(Voxel& total_pos);


struct image_loader {
    std::string filename;
    sf::Image* image;
    bool ready=false;
    bool ok=true;
    size_t index;
    sf::Thread *thread_pointer;
    std::string previous="";
};

typedef double Vec2[2];
typedef double Vec3[3];
typedef double Vec4[4];
typedef int iVec3[3];

typedef unsigned char Rgb[3];

/*
void cross3d(const Vec3 &a, const Vec3 &b, Vec3 &result) {
	result[0]=a[1]*b[2] - a[2]*b[1];
	result[1]=a[0]*b[0] - a[0]*b[2];
	result[2]=a[0]*b[1] - a[1]*b[0];
}

float dot3d(const Vec3 &a, const Vec3 &b) {
	return a[0]*b[0]+a[1]*b[1]+a[2]*b[2];
}

bool interpolate_point(const Vec3 &a, const Vec3 &b, const Vec3 &c, const Vec3 &p, Vec4 &i) {
	Vec3 ap={ a[0]-p[0], a[1]-p[1], a[2]-p[2]};
	Vec3 bp={ b[0]-p[0], b[1]-p[1], b[2]-p[2]};
	Vec3 cp={ c[0]-p[0], c[1]-p[1], c[2]-p[2]};

	Vec3 a_min_b={ a[0]-b[0], a[1]-b[1], a[2]-b[2]};
	Vec3 a_min_c={ a[0]-c[0], a[1]-c[1], a[2]-c[2]};

	Vec3 va;    cross3d(a_min_b,a_min_c,va);
	Vec3 va1;   cross3d(bp,cp,va1);
    Vec3 va2;   cross3d(cp,ap,va2);
    Vec3 va3;   cross3d(ap,bp,va3);

	double  l=sqrt(va[0]*va[0]+va[1]*va[1]+va[2]*va[2]);
	if (l==0.0) return false;
	i[0]=sqrt(va1[0]*va1[0]+va1[1]*va1[1]+va1[2]*va1[2])/l;
	i[1]=sqrt(va2[0]*va2[0]+va2[1]*va2[1]+va2[2]*va2[2])/l;
	i[3]=sqrt(va3[0]*va3[0]+va3[1]*va3[1]+va3[2]*va3[2])/l;

	double dot1=dot3d(va,va1); i[0]=i[0] * (dot1 > 0) - (dot1 < 0);
	double dot2=dot3d(va,va2); i[1]=i[1] * (dot2 > 0) - (dot2 < 0);
	double dot3=dot3d(va,va3); i[2]=i[2] * (dot3 > 0) - (dot3 < 0);
    i[3]=-i[0]*a[0]-i[1]*a[1]-i[2]*a[2];

    return true;
//	var uv: Vector2 = uv1 * a1 + uv2 * a2 + uv3 * a3;
}

float determinant(const Vec3 &a, const Vec3 &b, const Vec3 &c) {
    return a[0]*b[1]*c[2] - a[0]*b[2]*c[1] - a[1]*b[0]*c[2] + a[1]*b[2]*c[0] + a[2]*b[0]*c[1]-a[2]*b[1]*c[0];
}

float which_side(const Vec3 &a, const Vec3 &b, const Vec3 &c, const Vec3 &p) {
	Vec3 f1={ a[0]-p[0], a[1]-p[1], a[2]-p[2]};

	Vec3 a_min_b={ a[0]-b[0], a[1]-b[1], a[2]-b[2]};
	Vec3 a_min_c={ a[0]-c[0], a[1]-c[1], a[2]-c[2]};

	return determinant(a_min_b,a_min_c,f1);
}

void get_plane(const Vec3 &a, const Vec3 &b, const Vec3 &c, Vec4 &plane) {
    Vec3 ba={b[0]-a[0],b[1]-a[1],b[2]-a[2]};
    Vec3 ca={c[0]-a[0],c[1]-a[1],c[2]-a[2]};

    plane[0]=(ba[1])*(ca[2])-(ca[1])*(ba[2]);
    plane[1]=(ba[2])*(ca[0])-(ca[2])*(ba[0]);
    plane[2]=(ba[0])*(ca[1])-(ca[0])*(ba[1]);
    plane[3]=-(plane[0]*a[0]+plane[1]*a[1]+plane[2]*a[2]);
}


bool distance_to_plane_sub(const Vec4 &plane, const Vec3 &p, double& d) {
    double root=sqrt(plane[0]*plane[0]+plane[1]*plane[1]+plane[2]*plane[2]);
    if (root==0.0) return false;
    d=fabs(plane[0]*p[0]+plane[1]*p[1]+plane[2]*p[2]+plane[3]);
    return true;
}

bool distance_to_plane(const Vec3 &a, const Vec3 &b, const Vec3 &c, const Vec3 &p, double &d) {
    Vec4 plane;
    get_plane(a, b, c, plane);
    return distance_to_plane_sub(plane, p, d);
}

double edgeFunction2(const Vec2 &a, const Vec2 &b, const Vec2 &c) {
	Vec2 a_min_b={ a[0]-b[0], a[1]-b[1]};
	Vec2 a_min_c={ a[0]-c[0], a[1]-c[1]};
    return (a_min_b[0]*a_min_c[1]-a_min_b[1]*a_min_c[0]);
}

double edgeFunction3(const Vec2 &a, const Vec2 &b, const Vec2 &c) {
    double A=sqrt(((b[0]-a[0])*(b[0]-a[0]))+((b[1]-a[1])*(b[1]-a[1])));
    double B=sqrt(((c[0]-b[0])*(c[0]-b[0]))+((c[1]-b[1])*(c[1]-b[1])));
    double C=sqrt(((a[0]-c[0])*(a[0]-c[0]))+((a[1]-c[1])*(a[1]-c[1])));
    double side=((A+B+C)/2);

    return sqrt(side*(side-A)*(side-B)*(side-C));
}
*/

bool showit=false;

inline
double edgeFunction(const Vec2 &a, const Vec2 &b, const Vec2 &c) {
    return (c[0]-a[0]) * (b[1]-a[1]) - (b[0]-a[0]) * (c[1]-a[1]);

//    if (ret==0.0 && showit) {
//        printf("\n( %7.3f - %7.3f] ) * ( %7.3f - %7.3f] ) - ( %7.3f - %7.3f] ) * ( %7.3f - %7.3f )  =  %7.3f * %7.3f - %7.3f * %7.3f  =  %7.3f - %7.3f  =  %7.3f\n" ,
//                                c[0] , a[0] , b[1] , a[1] , b[0] , a[0] , c[1] , a[1],
//                                (c[0]-a[0]) , (b[1]-a[1]) , (b[0]-a[0]) , (c[1]-a[1]),
//                                (c[0]-a[0]) * (b[1]-a[1]) , (b[0]-a[0]) * (c[1]-a[1]) , ret );
//    } else {
//        return ret;
//    }
//    return (  (c[0]-a[0]) * (b[1]-a[1]) - (b[0]-a[0]) * (c[1]-a[1])  );
}

/*
void projec_point_to_plane_sub(const Vec4 &plane, const Vec3 &p, Vec3& pp, const Vec3& orig)  {
    Vec3 v={p[0]-orig[0], p[1]-orig[1], p[2]-orig[2]};
    double dist = v[0]*plane[0] + v[1]*plane[1] + v[2]*plane[2];
    pp[0] = p[0] - dist*plane[0];
    pp[1] = p[1] - dist*plane[1];
    pp[2] = p[2] - dist*plane[2];
}

void projec_point_to_plane(const Vec3 &a, const Vec3 &b, const Vec3 &c, const Vec3 &p, Vec3& pp) {
    Vec4 plane;
    get_plane(a, b, c, plane);
    projec_point_to_plane_sub(plane, p, pp, a);
}

bool insideTriangle(const Vec2 &V0, const Vec2 &V1, const Vec2 &V2, const Vec2 &p)  {
    bool inside;

    double w0 = edgeFunction(V0, V2, p);
    double w1 = edgeFunction(V1, V0, p);
    double w2 = edgeFunction(V2, V1, p);

    return (w0 >= 0.0 && w1 >= 0.0 && w2 >= 0.0) || (w0 <= 0.0 && w1 <= 0.0 && w2 <= 0.0);
}

bool insideTriangle_3d(const Vec3 &a, const Vec3 &b, const Vec3 &c, const Vec3 &p)  {
    bool inside = true;

	Vec3 a_min_b={ a[0]-b[0], a[1]-b[1], a[2]-b[2]};
	Vec3 a_min_c={ a[0]-c[0], a[1]-c[1], a[2]-c[2]};

	Vec3 ap={ a[0]-p[0], a[1]-p[1], a[2]-p[2]};
	Vec3 bp={ b[0]-p[0], b[1]-p[1], b[2]-p[2]};
	Vec3 cp={ c[0]-p[0], c[1]-p[1], c[2]-p[2]};

	double area = fabs(dot3d(a_min_b,a_min_c))/2.0;
	if (area==0.0) return false;
	double w0=fabs(dot3d(bp,cp))/area;
	double w1=fabs(dot3d(cp,ap))/area;
	double w2=fabs(dot3d(ap,bp))/area;

//	if (w0>=0 && w0<=1 && w1>=0 && w1<=1 && w2>=0 && w2<=1 && ((w0+w1+w2)>0.99 || (w0+w1+w2)<1.01) ) return true;
	if (w0>=0 && w0<=1 && w1>=0 && w1<=1 && w2>=0 && w2<=1 && w0+w1+w2==1.0 ) return true;
	return false;
}
*/

void adapt_raster_image(sf::Image &im_out,sf::Image* im_in, double factor, double tc[3][2], int w, int h, double bmin_pixel[2], double bmax_pixel[2]) {
/*
    float bmin_pixel[2];
    float bmax_pixel[2];

    bmin_pixel[0] = bmin_pixel[1] = std::numeric_limits<float>::max();
    bmax_pixel[0] = bmax_pixel[1] = -std::numeric_limits<float>::max();

    for (int l=0; l<3; l++) {
        bmin_pixel[0]=std::min(     float(tc[l][0]*w), bmin_pixel[0]);   bmax_pixel[0]=std::max(  float(tc[l][0]*w), bmax_pixel[0]);
        bmin_pixel[1]=std::min(     float(tc[l][1]*h), bmin_pixel[1]);   bmax_pixel[1]=std::max(  float(tc[l][1]*h), bmax_pixel[1]);
    }
*/
    sf::RenderTexture tex_out;
    tex_out.create(im_out.getSize().x,im_out.getSize().y,false);
    tex_out.setSmooth(true);
    tex_out.clear(sf::Color(0,255,0,255));

    int real_w=(bmax_pixel[0]-bmin_pixel[0]+1);
    int real_h=(bmax_pixel[1]-bmin_pixel[1]+1);

    sf::Texture tex_in;
//    tex_in.create(real_w+4,real_h+4);
    tex_in.create(real_w,real_h);
    tex_in.setSmooth(true);

//    tex_in.loadFromImage(*im_in,sf::IntRect(bmin_pixel[0],bmin_pixel[1],real_w+4,real_h+4));
    tex_in.loadFromImage(*im_in,sf::IntRect((int)bmin_pixel[0],(int)bmin_pixel[1],real_w,real_h));
    sf::Sprite spr_in;

    spr_in.setTexture(tex_in,true);

//    spr_in.setPosition(2,2);
//    spr_in.setPosition(0,0);

    spr_in.setOrigin( (float)real_w/2.0 , (float)real_h/2.0 );
    spr_in.setPosition( 0 , 0 );
    spr_in.setScale(factor,factor);

//    spr_in.setPosition( (float)im_out.getSize().x/2.0 , (float)im_out.getSize().y/2.0 );

//    spr_in.setOrigin(0,real_h-1);
    tex_out.draw(spr_in);
//    tex_out.draw(spr_in,sf::BlendNone);
    tex_out.display();
    im_out=tex_out.getTexture().copyToImage();
}

unsigned short *backup=NULL;
bool warning_done_x=false;
bool warning_done_y=false;
bool warning_done_z=false;
bool warning_done_x_min=false;
bool warning_done_y_min=false;
bool warning_done_z_min=false;
bool warning_done_topping=false;
//int rasterize(float v[3][3], float tc_org[3][2], int w_a, int h_a, int buf_count, int faces, sf::Image* image, float factor_a, sf::Image& image_copy,bool point,bool line,
//               float offset_x, float offset_y, float offset_z, int box_x, int box_y, int box_z, unsigned short* mc, float block_scale) {
//ayay2

extern bool hit_cube_y_start;
extern bool hit_cube_y_end;
extern bool hit_cube_z_start;
extern bool hit_cube_z_end;

/*

int rasterize2(double v[3][3], double tc_org[3][2], int w_a, int h_a, int buf_count, int faces, sf::Image* image, double factor_a, sf::Image& image_copy,bool point,bool line,
               double offset_x, double offset_y, double offset_z, int box_x, int box_y, int box_z, unsigned short** mc_sub, double block_scale) {
//    factor=-factor*.5-0.25;

    double tc[3][2];
    for (int n=0; n<3; n++) {
//oh no!! adapt or not?
//o my god!!
//        if ( (tc_org[n][0]*w_a-0.5) == int(tc_org[n][0]*w_a-0.5) ) tc[n][0]=(tc_org[n][0]*w_a-0.5)/w_a;
//        else tc[n][0]=tc_org[n][0];
//        if ( (tc_org[n][1]*h_a-0.5) == int(tc_org[n][1]*h_a-0.5) ) tc[n][1]=(tc_org[n][1]*h_a-0.5)/h_a;
        //else tc[n][1]=tc_org[n][1];

//deze
//        tc[n][0]=(tc_org[n][0]*w_a-0.5)/w_a;
//        tc[n][1]=(tc_org[n][1]*h_a-0.5)/h_a;

        tc[n][0]=tc_org[n][0];
        tc[n][1]=tc_org[n][1];

    }


    sf::Color random_color=sf::Color(rand()%256,rand()%256,rand()%256,255);
    double bmin_pixel_o[2];
    double bmax_pixel_o[2];

    bmin_pixel_o[0] = bmin_pixel_o[1] = std::numeric_limits<double>::max();
    bmax_pixel_o[0] = bmax_pixel_o[1] = -std::numeric_limits<double>::max();

    for (int l=0; l<3; l++) {
        bmin_pixel_o[0]=std::min(     tc[l][0]*double(w_a), bmin_pixel_o[0]);   bmax_pixel_o[0]=std::max(  tc[l][0]*double(w_a), bmax_pixel_o[0]);
        bmin_pixel_o[1]=std::min(     tc[l][1]*double(h_a), bmin_pixel_o[1]);   bmax_pixel_o[1]=std::max(  tc[l][1]*double(h_a), bmax_pixel_o[1]);
    }

    int w=factor_a*(double)w_a;
    int h=factor_a*(double)h_a;

//    float factor=factor_a*.5f-0.5f;
    double factor=0.0;

    double bmin_pixel[2];
    double bmax_pixel[2];

    bmin_pixel[0] = bmin_pixel[1] = std::numeric_limits<double>::max();
    bmax_pixel[0] = bmax_pixel[1] = -std::numeric_limits<double>::max();

    for (int l=0; l<3; l++) {
        bmin_pixel[0]=std::min(     tc[l][0]*double(w)-factor, bmin_pixel[0]);   bmax_pixel[0]=std::max(  tc[l][0]*double(w)-factor, bmax_pixel[0]);
        bmin_pixel[1]=std::min(     tc[l][1]*double(h)-factor, bmin_pixel[1]);   bmax_pixel[1]=std::max(  tc[l][1]*double(h)-factor, bmax_pixel[1]);
//        bmin_pixel[0]=std::min(     float(tc[l][0]*w-factor-0.5), bmin_pixel[0]);   bmax_pixel[0]=std::max(  float(tc[l][0]*w-factor+0.5), bmax_pixel[0]);
//        bmin_pixel[1]=std::min(     float(tc[l][1]*h-factor-0.5), bmin_pixel[1]);   bmax_pixel[1]=std::max(  float(tc[l][1]*h-factor+0.5), bmax_pixel[1]);
    }
    int real_w;
    int real_h;
    if (factor_a!=1.0) {
        real_w=(bmax_pixel[0]-bmin_pixel[0]+1);
        real_h=(bmax_pixel[1]-bmin_pixel[1]+1);
    } else {
        real_w=(bmax_pixel_o[0]-bmin_pixel_o[0]+1);
        real_h=(bmax_pixel_o[1]-bmin_pixel_o[1]+1);
    }
    sf::Image im_out;
    im_out.create(real_w+4,real_h+4);
//    real_w++;
//    real_h++;

    if (factor_a!=1.0) {
        adapt_raster_image(im_out,image,factor_a,tc,w_a,h_a,bmin_pixel_o,bmax_pixel_o);
    }
    else {
//mein gott
//        im_out.copy(*image,2,2,sf::IntRect((int)bmin_pixel_o[0],h_a-1-(int)bmax_pixel_o[1],real_w,real_h));
//        im_out.copy(*image,2,2,sf::IntRect((int)bmin_pixel_o[0],(int)bmax_pixel_o[1]-1-real_h,real_w,real_h));

        int b_min_x=bmin_pixel_o[0]-1;
        int b_min_y=bmin_pixel_o[1]-1;
        int b_w=real_w+2;
        int b_h=real_h+2;
        int b_adj_x=0,b_adj_y=0;

        if (b_min_x<0) { b_min_x=0; b_adj_x=+1; }
        if (b_min_y<0) { b_min_y=0; b_adj_y=+1; }

        int b_adj_x2=0,b_adj_y2=0;

        if (b_min_x + b_w - b_adj_x  >= w_a) b_adj_x2=1;
        if (b_min_y + b_h - b_adj_y  >= h_a) b_adj_y2=1;


        im_out.copy(*image, 1+b_adj_x-1,    1+b_adj_y-1,    sf::IntRect( b_min_x, b_min_y,    b_w-b_adj_x -b_adj_x2,   b_h-b_adj_y -b_adj_y2 ));

        im_out.copy(*image, 1+b_adj_x+1,    1+b_adj_y+1,    sf::IntRect( b_min_x, b_min_y,    b_w-b_adj_x -b_adj_x2-1,   b_h-b_adj_y -b_adj_y2-1 ));

        im_out.copy(*image, 1+b_adj_x-1,    1+b_adj_y+1,    sf::IntRect( b_min_x, b_min_y,    b_w-b_adj_x -b_adj_x2,   b_h-b_adj_y -b_adj_y2-1 ));

        im_out.copy(*image, 1+b_adj_x+1,    1+b_adj_y-1,    sf::IntRect( b_min_x, b_min_y,    b_w-b_adj_x -b_adj_x2-1,   b_h-b_adj_y -b_adj_y2 ));

        im_out.copy(*image, 1+b_adj_x,      1+b_adj_y,      sf::IntRect( b_min_x, b_min_y,    b_w-b_adj_x -b_adj_x2,   b_h-b_adj_y -b_adj_y2 ));


//
//        if ( bmin_pixel_o[0]-1 >= 0  &&  bmin_pixel_o[1]-1>=0 &&  bmin_pixel_o[0]-1 + real_w+2 < w_a && bmin_pixel_o[1]-1 + real_h+2 < h_a)
//            im_out.copy(*image,1,1,sf::IntRect((int)bmin_pixel_o[0]-1,(int)bmin_pixel_o[1]-1,real_w+2,real_h+2));
//        else
//            im_out.copy(*image,2,2,sf::IntRect((int)bmin_pixel_o[0],(int)bmin_pixel_o[1],real_w,real_h));
//

    }
    char filename[2000];
    bool saved=false;
//    if (!(rand()%500)) {
//        saved=true;
//        sprintf(filename, "../cut/raster2d.%03d.%03d.start.png", buf_count, faces );
//        im_out.saveToFile(filename);
//    }

    static int num=0;
    Vec2 v0;
    Vec2 v1;
    Vec2 v2;
    v0[0] = tc[0][0]*(double)w-factor; v0[1] = tc[0][1]*(double)h-factor;
    v1[0] = tc[1][0]*(double)w-factor; v1[1] = tc[1][1]*(double)h-factor;
    v2[0] = tc[2][0]*(double)w-factor; v2[1] = tc[2][1]*(double)h-factor;

//testing

    double area;
//    if (!(line || point)) showit=true; else showit=false;
    showit=false;
//    area = edgeFunction(v2, v1, v0);

    bool skip_min_x=false;
    bool skip_max_x=false;
    bool skip_min_y=false;
    bool skip_max_y=false;

//deze
//    if (area==0 && 0) {
        if (v0[0]==bmin_pixel[0]) {
            v0[0]-=0.5f;
            skip_min_x=true;

        } else if (v0[0]==bmax_pixel[0]) {
             v0[0]+=0.5f;
             skip_max_x=true;
        }
        if (v0[1]==bmin_pixel[1]) {
            v0[1]-=0.5f;
            skip_min_y=true;
        } else if (v0[1]==bmax_pixel[1]) {
            v0[1]+=0.5f;
            skip_max_y=true;
        }

        if (v1[0]==bmin_pixel[0] && !skip_min_x) {
            v1[0]-=0.5f;
            skip_min_x=true;
        } else if (v1[0]==bmax_pixel[0] && !skip_max_x) {
            v1[0]+=0.5f;
            skip_max_x=true;
        }
        if (v1[1]==bmin_pixel[1] && !skip_min_y) {
            v1[1]-=0.5f;
            skip_min_y=true;
        } else if (v0[1]==bmax_pixel[1] && !skip_max_y) {
            v0[1]+=0.5f;
            skip_max_y=true;
        }

        if (v2[0]==bmin_pixel[0] && !skip_min_x) {
            v2[0]-=0.5f;
            skip_min_x=true;
        } else if (v2[0]==bmax_pixel[0] && !skip_max_x) {
             v2[0]+=0.5f;
             skip_max_x=true;
        }
        if (v2[1]==bmin_pixel[1] && !skip_min_y) {
            v2[1]-=0.5f;
            skip_min_y=true;
        } else if (v2[1]==bmax_pixel[1] && !skip_max_y) {
            v2[1]+=0.5f;
            skip_max_y=true;
        }
//    }
    area = edgeFunction(v2, v1, v0);


//    area = edgeFunction(v0, v1, v2);
//    showit=false;
//    if (area==0.0) {
//        area = edgeFunction(v1, v2, v0);
//        if (area==0.0) {
//            area = edgeFunction(v2, v0, v1);
//        }
//    }
//
//    if (real_w==1 || real_h==1 || point==1 || line==1 || area==0.0) {
//        printf("area=%6.3f  bmin=(%3d,%3d) max=(%3d,%3d)  real_w=%3d real_h=%3d  point=%d  line=%d  ",
//               area,(int)bmin_pixel[0],(int)bmin_pixel[1],(int)bmax_pixel[0],(int)bmax_pixel[1],real_w,real_h,point,line);
//        printf("TC:(%5.1f - %5.1f),(%5.1f - %5.1f),(%5.1f - %5.1f)\n",v0[0],v0[1],v1[0],v1[1],v2[0],v2[1]);
//    }

    int skip=true;
    if (!skip && !(point || line)) {
        if (area==0) {
            printf("\n\nAREA=0.0 NO POINT, NO LINE!!!\n");
            printf("area=%20.10f  bmin=(%3d,%3d) max=(%3d,%3d)  real_w=%3d real_h=%3d  point=%d  line=%d  ",
                area,(int)bmin_pixel[0],(int)bmin_pixel[1],(int)bmax_pixel[0],(int)bmax_pixel[1],real_w,real_h,point,line);
            printf("TC:(%5.1f - %5.1f),(%5.1f - %5.1f),(%5.1f - %5.1f)\n\n",v0[0],v0[1],v1[0],v1[1],v2[0],v2[1]);
            skip=true;
        }
    }
    if (!skip && area==0) {
        if (!(point || line)) {
            printf("\n\nAREA=0.0 NO POINT, NO LINE!!!\n");
            printf("area=%20.10f  bmin=(%3d,%3d) max=(%3d,%3d)  real_w=%3d real_h=%3d  point=%d  line=%d  ",
                area,(int)bmin_pixel[0],(int)bmin_pixel[1],(int)bmax_pixel[0],(int)bmax_pixel[1],real_w,real_h,point,line);
            printf("TC:(%5.1f - %5.1f),(%5.1f - %5.1f),(%5.1f - %5.1f)\n\n",v0[0],v0[1],v1[0],v1[1],v2[0],v2[1]);
        }
        skip=true;
    }
    if (!skip && area==0) {
        printf("area==0\n");
    }


//    printf("\n");
//    printf("TC:(%3d,%3d),(%3d,%3d),(%3d,%3d)\n",int(v0[0]),int(v0[1]),int(v1[0]),int(v1[1]),int(v2[0]),int(v2[1]));
    Vec3 c0 = {1, 0, 0};
    Vec3 c1 = {0, 1, 0};
    Vec3 c2 = {0, 0, 1};

    if (area!=0) {
        for (int plot_y = 0; plot_y < real_h+4; ++plot_y) {
            for (int plot_x = 0; plot_x < real_w+4; ++plot_x) {
//        for (int plot_y = 0; plot_y < real_h+4; ++plot_y) {
//            for (int plot_x = 0; plot_x < real_w+4; ++plot_x) {

//mein gott
//                int i=plot_x+bmin_pixel[0];
//                int j=plot_y+bmin_pixel[1];
                int i=plot_x-2+bmin_pixel[0];
                int j=plot_y-2+bmin_pixel[1];
//                int i=plot_x-2+bmin_pixel[0];
//                int j=plot_y-2+bmin_pixel[1];

    //            Vec2 p = {(float)i, (float)j};
                Vec2 p = {(double)i + 0.5f, (double)j + 0.5f};

//fok it!
//                float w0 = edgeFunction(v0, v2, p);
//                float w1 = edgeFunction(v1, v0, p);
//                float w2 = edgeFunction(v2, v1, p);

//jippie!!!
                float w1 = edgeFunction(v0, v2, p);
                float w2 = edgeFunction(v1, v0, p);
                float w0 = edgeFunction(v2, v1, p);


//                float w0 = edgeFunction(v1, v2, p);
//                float w1 = edgeFunction(v2, v0, p);
//                float w2 = edgeFunction(v0, v1, p);

                if ((w0 >= 0.0 && w1 >= 0.0 && w2 >= 0.0) || (w0 <= 0.0 && w1 <= 0.0 && w2 <= 0.0)) {
//                    float r;
//                    float g;
//                    float b;
                    double v_x;
                    double v_y;
                    double v_z;
                    if (area!=0.0) {
                        w0 /= area;
                        w1 /= area;
                        w2 /= area;
//                        r = (w0 * c0[0]) + (w1 * c1[0]) + (w2 * c2[0]);
//                        g = (w0 * c0[1]) + (w1 * c1[1]) + (w2 * c2[1]);
//                        b = (w0 * c0[2]) + (w1 * c1[2]) + (w2 * c2[2]);

                        v_x = (w0 * v[0][0]) + (w1 * v[1][0]) + (w2 * v[2][0]);
                        v_y = (w0 * v[0][1]) + (w1 * v[1][1]) + (w2 * v[2][1]);
                        v_z = (w0 * v[0][2]) + (w1 * v[1][2]) + (w2 * v[2][2]);
                    } else {
//                        r = (c0[0] + c1[0] + c2[0])/3.0;
//                        g = (c0[1] + c1[1] + c2[1])/3.0;
//                        b = (c0[2] + c1[2] + c2[2])/3.0;

                        v_x = (v[0][0] + v[1][0] + v[2][0])/3.0;
                        v_y = (v[0][1] + v[1][1] + v[2][1])/3.0;
                        v_z = (v[0][2] + v[1][2] + v[2][2])/3.0;
                    }
//mein gott
//                    if (plot_x<0 || plot_x>real_w+4-1 || plot_y<0 || plot_y>real_h+4-1 )  {
//                        printf("Outside boudaries\n");
//                    }
                    sf::Color pixel=im_out.getPixel(plot_x,plot_y);
//                    sf::Color pixel=im_out.getPixel(plot_x,real_h+4-1-plot_y);
//                    printf("Buffer: %d  face: %d  T:(%3d,%3d) = C:(%3d,%3d,%3d)  ->  3D:(%8.3f,%8.3f,%8.3f)",buf_count,faces,i,j,pixel.r, pixel.g, pixel.b, v_x, v_y, v_z );

                    int cube_x=(v_x-offset_x)*block_scale;
                    int cube_y=(v_y-offset_y)*block_scale;
                    int cube_z=(v_z-offset_z)*block_scale;

//                    int cube_x=(v_x-offset_x)*block_scale;
//                    int cube_y=-0.25+(v_y-offset_y)*block_scale  + 0.5*(v_y-offset_y)*block_scale/box_y;
//                    int cube_z=-0.25+(v_z-offset_z)*block_scale  + 0.5*(v_z-offset_z)*block_scale/box_z;
                    if (cube_y==0) hit_cube_y_start=true;
                    if (cube_y==box_y-1) hit_cube_y_end=true;
                    if (cube_z==0) hit_cube_z_start=true;
                    if (cube_z==box_z-1) hit_cube_z_end=true;
//                    int cube_x=v_x*block_scale-offset_x;
//                    int cube_y=-0.25+(v_y*block_scale-offset_y)*(((float)box_y+0.5)/(float)box_y);
//                    int cube_z=-0.25+(v_z*block_scale-offset_z)*(((float)box_z+0.5)/(float)box_z);;

                    if (wuppie_all) {
                        int real_y=cube_x+offset_real_y;
                        if (real_y>230) {
                            if (!warning_done_topping) {
                                printf("\nWarning: Topping: cube_x=%d  box_x=%d real y=%d(This message is only displayed once...)\n", cube_x, box_x, real_y);
                            }

                            float togo=real_y-230;
                            float new_real_y=230+togo/(1.0+(togo/25.0));
                            cube_x=new_real_y-offset_real_y;
                            if (!warning_done_topping) {
                                real_y=cube_x+offset_real_y;
                                printf("\nNew_cube_x=%d new_real_y=%d\n", cube_x, real_y);
                                warning_done_topping=true;
                            }
                        }
                    }

//
//wrong
//                    if (cube_x>(200+offset_x*block_scale)) {
//                        float togo=cube_x-200-offset_x*block_scale;
//                        float temper=200+togo/(1.0+(togo/50.0));
//                        cube_x=int(temper)+offset_x*block_scale;
//                    }
//

//                    printf("  -> MC:(%4d,%4d,%4d)\n",cube_x,cube_y,cube_z);

                    if (cube_x==-1) cube_x=0; else if (cube_x==box_x) cube_x--;
                    if (cube_y==-1) cube_y=0; else if (cube_y==box_y) cube_y--;
                    if (cube_z==-1) cube_z=0; else if (cube_z==box_z) cube_z--;
                    if (cube_x>=box_x) {
//                    if (cube_x>255) {
                        if (!warning_done_x) {
                            printf("\nWarning: cube_x=%d  box_x=%d (This message is only displayed once...)\n", cube_x, box_x);
                            warning_done_x=true;
                        }
                    }
                    else if (cube_y>=box_y) {
                        if (!warning_done_y) {
                            printf("\nWarning: cube_y=%d  box_y=%d (This message is only displayed once...)\n", cube_y, box_y);
                            warning_done_y=true;
                        }
                    }
                    else if (cube_z>=box_z) {
                        if (!warning_done_z) {
                            printf("\nWarning: cube_z=%d  box_z=%d (This message is only displayed once...)\n", cube_z, box_z);
                            warning_done_z=true;
                        }
                    }
                    else if (cube_x<0) printf("Warning: cube_x=%d  box_x=%d\n", cube_x, box_x);
                    else if (cube_y<0 ) printf("Warning: cube_y=%d  box_y=%d\n", cube_y, box_y);
                    else if (cube_z<0 ) printf("Warning: cube_z=%d  box_z=%d\n", cube_z, box_z);
                    else {

//                        size_t tot_off=(cube_x+cube_y*box_x+cube_z*box_x*box_y)*4;
                        size_t tot_off_x=(cube_y+cube_z*box_y)*4;
//                        int curr=mc[tot_off+3];
//                        mc[tot_off]     +=(unsigned short) pixel.r;
//                        mc[tot_off+1]   +=(unsigned short) pixel.g;
//                        mc[tot_off+2]   +=(unsigned short) pixel.b;
//                        mc[tot_off+3]++;
//ayay2
                        unsigned short * cube_x_p=mc_sub[cube_x];
                        int curr=cube_x_p[tot_off_x+3];
                        cube_x_p[tot_off_x]     +=(unsigned short) pixel.r;
                        cube_x_p[tot_off_x+1]   +=(unsigned short) pixel.g;
                        cube_x_p[tot_off_x+2]   +=(unsigned short) pixel.b;
                        cube_x_p[tot_off_x+3]++;

    //                    if (!(rand()%100)) printf("r=%f g=%f b=%f total rgb=%f\n",r,g,b,r+g+b);
    //                    printf("r=%f g=%f b=%f   area=%f   w0=%f w1=%f w2=%f   i=%d j=%d\n",r*255.0,g*255.0,b*255.0,area,w0,w1,w2,i,j);

/*
                        if (plot_x>=0 && plot_x<real_w+4 && plot_y>=0 && plot_y<real_h+4) {
                            if (plot_x==0 || plot_x==real_w+4-1 || plot_y==0 || plot_y==real_h+4-1) {
                                im_out.setPixel(plot_x,plot_y,sf::Color(128,128,128,255));
                            } else if (plot_x==1 || plot_x==real_w+4-2 || plot_y==1 || plot_y==real_h+4-2) {
                                im_out.setPixel(plot_x,plot_y,sf::Color(255,0,255,255));
                            } else {
    //                            im_out.setPixel(plot_x,plot_y,sf::Color((int)(r*255),(int)(g*255),(int)(b*255),255));
    //                            im_out.setPixel(plot_x,plot_y,sf::Color((int)(r*255),(int)(g*255),(int)(b*255),255));

                                static int flip=0;
                                int pixel_x=bmin_pixel_o[0]+(plot_x-2)/factor_a;
                                int pixel_y=bmin_pixel_o[1]+(plot_y-2)/factor_a;
                                sf::Color pixel2;
                                if (pixel_x>=0 && pixel_x<real_w+4 && pixel_y>=0 && pixel_y<real_h+4) {
                                    pixel2=image_copy.getPixel(pixel_x,pixel_y);
//ayay
//                                    pixel2.r=mc[tot_off]   / mc[tot_off+3];
//                                    pixel2.g=mc[tot_off+1] / mc[tot_off+3];
//                                    pixel2.b=mc[tot_off+2] / mc[tot_off+3];

                                    int curr2=cube_x_p[tot_off_x+3];

                                    pixel2.r=cube_x_p[tot_off_x]   / curr2;
                                    pixel2.g=cube_x_p[tot_off_x+1] / curr2;
                                    pixel2.b=cube_x_p[tot_off_x+2] / curr2;

                                    if (pixel2.a!=254 && pixel2.a!=252) {
                                        if (pixel2.a==250) {
                                            pixel2.a=252;
                                            image_copy.setPixel(pixel_x,pixel_y,pixel2);
                                        }
                                        else {
                                            pixel2.a=254;
                                            image_copy.setPixel(pixel_x,pixel_y,pixel2);
                                        }
                                    }
                                }
                            }
                        }


                    }
                } else {
//
//                    if (plot_x>=0 && plot_x<real_w+4 && plot_y>=0 && plot_y<real_h+4) {
//                        if (plot_x==0 || plot_x==real_w+4-1 || plot_y==0 || plot_y==real_h+4-1) {
//                            im_out.setPixel(plot_x,plot_y,sf::Color(255,255,0,255));
//                        } else if (plot_x==1 || plot_x==real_w+4-2 || plot_y==1 || plot_y==real_h+4-2) {
//                            im_out.setPixel(plot_x,plot_y,sf::Color(0,255,255,255));
//                        } else {
//    //                        sf::Color pixel=im_out.getPixel(plot_x,plot_y);
//    //                        im_out.setPixel(plot_x,plot_y,sf::Color((255+pixel.r*5)/6,pixel.g,pixel.b,255));
//                            im_out.setPixel(plot_x,plot_y,sf::Color(255,255,255,0));
//                        }
//                    }
//
                }
            }
        }
    } else {

        int sx=im_out.getSize().x;
        int sy=im_out.getSize().y;
        float vv[3][3];
        int pmin[3];
        int pmax[3];
        for (int l=0; l<3; l++) {
            pmin[l] =  std::numeric_limits<int>::max();
            pmax[l] = -std::numeric_limits<int>::max();
        }

        for (int l=0; l<3; l++) {
            vv[l][0] = (v[l][0]-offset_x)*block_scale;
            vv[l][1] = (v[l][1]-offset_y)*block_scale;
            vv[l][2] = (v[l][2]-offset_z)*block_scale;

            pmin[0]=std::min((int)vv[l][0],pmin[0]); pmax[0]=std::max((int)vv[l][0],pmax[0]);
            pmin[1]=std::min((int)vv[l][1],pmin[1]); pmax[1]=std::max((int)vv[l][1],pmax[1]);
            pmin[2]=std::min((int)vv[l][2],pmin[2]); pmax[2]=std::max((int)vv[l][2],pmax[2]);
        }
        Vec4 plane;
        get_plane(vv[0], vv[1], vv[2], plane);
        size_t d_x=(pmax[0]-pmin[0]+1);
        size_t d_y=(pmax[1]-pmin[1]+1);
        size_t d_z=(pmax[2]-pmin[2]+1);
        static size_t backup_len=0;

        if (backup_len<d_x*d_y*d_z*4) {
            static bool start=true;
            if (start==false) {
                delete [] backup;
                start=false;
            }
            backup_len=d_x*d_y*d_z*4;
            backup = new unsigned short [backup_len];
        }

        std::memset(backup, 0x0, backup_len*2);  //short

        Vec3 b;
        for (b[2]=pmin[2]; b[2]<=pmax[2]; b[2]++) {
            for (b[1]=pmin[1]; b[1]<=pmax[1]; b[1]++) {
                for (b[0]=pmin[0]; b[0]<=pmax[0]; b[0]++) {
                    Vec3 pp;
                    projec_point_to_plane_sub(plane, b, pp, vv[0]);
                    if (insideTriangle_3d( vv[0], vv[1], vv[2], pp)) {
                        Vec4 i;
                        if (interpolate_point(vv[0], vv[1], vv[2], pp, i)) {
                            float tc_x = (i[0] * v0[0]) + (i[1] * v1[0]) + (i[2] * v2[0]);
                            float tc_y = (i[0] * v0[1]) + (i[1] * v1[1]) + (i[2] * v2[1]);
                            tc_x=tc_x-bmin_pixel_o[0]+2;
                            tc_y=tc_y-bmin_pixel_o[1]+2;
                            if (tc_x>2 && tc_x<sx-2 && tc_y>2 && tc_y<sy-2) {
                                sf::Color pixel=im_out.getPixel(tc_x,tc_y);
                                pixel.a=254;
                                im_out.setPixel(tc_x, tc_y, pixel);
                                size_t offset=((b[0]-pmin[0]) + (b[1]-pmin[1])*d_x + (b[2]-pmin[2])*d_x*d_y)*4;
                                if (offset>=backup_len) printf("Error offset backup\n");
                                else {
                                    small++;
                                    size_t tot_off=offset;
                                    int curr=backup[tot_off+3];
                                    backup[tot_off]     +=(unsigned short) pixel.r;
                                    backup[tot_off+1]   +=(unsigned short) pixel.g;
                                    backup[tot_off+2]   +=(unsigned short) pixel.b;

//                                    backup[tot_off]     =int( ((float)backup[tot_off  ]*(float)curr+(float)pixel.r)/((float)curr+1.0) );
//                                    backup[tot_off+1]   =int( ((float)backup[tot_off+1]*(float)curr+(float)pixel.g)/((float)curr+1.0) );
//                                    backup[tot_off+2]   =int( ((float)backup[tot_off+2]*(float)curr+(float)pixel.b)/((float)curr+1.0) );
//
                                    backup[tot_off+3]++;

                                    if (tc_x>0 && tc_x<w && tc_y>0 && tc_y<h) {
                                        sf::Color pixel=image_copy.getPixel(tc_x,tc_y);
                                        if (pixel.a!=254 && pixel.a!=252) {
                                            if (pixel.a==250) {
                                                pixel.a=252;
                                                image_copy.setPixel(tc_x,tc_y,pixel);
                                            }
                                            else {
                                                pixel.a=254;
                                                image_copy.setPixel(tc_x,tc_y,pixel);
                                            }
                                        }
                                    } else {
                                        printf("Pixel out of image: x=%d y=%d\n",tc_x,tc_y);
                                    }
                                }
                            } else {
                                printf("Error texture coordinat\n");
                            }
                        }
                    }
                }
            }
        }
        for (b[2]=pmin[2]; b[2]<=pmax[2]; b[2]++) {
            for (b[1]=pmin[1]; b[1]<=pmax[1]; b[1]++) {
                for (b[0]=pmin[0]; b[0]<=pmax[0]; b[0]++) {
                    size_t offset=((b[0]-pmin[0]) + (b[1]-pmin[1])*d_x + (b[2]-pmin[2])*d_x*d_y)*4;
                    int curr_backup=backup[offset+3];
                    if (curr_backup>0) {
                        if (offset>=backup_len) printf("Error offset backup\n");
                        else {
                            if (b[0]<0 || b[0]>=box_x) printf("Error b[0]=%d  box_x=%d\n", b[0], box_x);
                            else if (b[1]<0 || b[1]>=box_y) printf("Error b[1]=%d  box_y=%d\n", b[1], box_y);
                            else if (b[2]<0 || b[2]>=box_z) printf("Error b[2]=%d  box_z=%d\n", b[2], box_z);
                            else {
//ayay
//                                size_t tot_off=(b[0]+b[1]*box_x+b[2]*box_x*box_y)*4;
//                                int curr=mc[tot_off+3];
//                                mc[tot_off]     +=backup[offset  ];
//                                mc[tot_off+1]   +=backup[offset+1];
//                                mc[tot_off+2]   +=backup[offset+2];
//                                mc[tot_off+3]+=(unsigned short)curr_backup;

                                size_t tot_off_x=(b[1]+b[2]*box_y)*4;
                                unsigned short * cube_x_p=mc_sub[(int)b[0]];
                                int curr=cube_x_p[tot_off_x+3];
                                cube_x_p[tot_off_x]     +=backup[offset  ];;
                                cube_x_p[tot_off_x+1]   +=backup[offset+1];;
                                cube_x_p[tot_off_x+2]   +=backup[offset+2];;
                                cube_x_p[tot_off_x+3]+=(unsigned short)curr_backup;

//                                mc[tot_off]     =(unsigned short)( ((float)mc[tot_off  ]*(float)curr + (float)backup[offset  ]*(float)curr_backup  )/((float)(curr+curr_backup)) );
//                                mc[tot_off+1]   =(unsigned short)( ((float)mc[tot_off+1]*(float)curr + (float)backup[offset+1]*(float)curr_backup  )/((float)(curr+curr_backup)) );
//                                mc[tot_off+2]   =(unsigned short)( ((float)mc[tot_off+2]*(float)curr + (float)backup[offset+2]*(float)curr_backup  )/((float)(curr+curr_backup)) );
                            }
                        }
                    }
                }
            }
        }

//sukkel        delete [] backup;

        for (int y=0; y<im_out.getSize().y; y++) {
            for (int x=0; x<im_out.getSize().x; x++) {
                if (x==0 || x==im_out.getSize().x-1 || y==0 || y==im_out.getSize().y-1) {
                    im_out.setPixel(x,y,sf::Color(255,255,0,255));
                } else if (x==1 || x==im_out.getSize().x-2 || y==1 || y==im_out.getSize().y-2) {
                    im_out.setPixel(x,y,sf::Color(0,255,255,255));
                } else {
                    sf::Color pixel=im_out.getPixel(x,y);
                    if (pixel.a==254) im_out.setPixel(x,y,sf::Color(pixel.r,pixel.g,pixel.b,255));
                    else  im_out.setPixel(x,y,sf::Color(255,255,255,0));
                }
            }
        }

    }


//    for (int y=0; y<image_copy.getSize().y; y++) {
//        for (int x=0; x<image_copy.getSize().x; x++) {
//            sf::Color color=image_copy.getPixel(x,y);
//            if (color.a==254) image_copy.setPixel(x,y,sf::Color(color.r,color.g,color.b,250));
//            if (color.a==254) image_copy.setPixel(x,y,sf::Color( (random_color.r+color.r*3)/4,(random_color.g+color.g*3)/4,(random_color.b+color.b*3)/4,250));
 //       }
 //   }
//

//    char filename[2000];
//    if (saved) {
//        sprintf(filename, "../cut/raster2d.%03d.%03d.png", buf_count, faces );
//        im_out.saveToFile(filename);
//    }

    return 0;
}
*/

/*
void adapt_raster_image2(sf::Image &im_out,sf::Image* im_in, double factor, double tc[3][2], int w, int h, double bmin_pixel[2], double bmax_pixel[2]) {

//    float bmin_pixel[2];
 //   float bmax_pixel[2];

//    bmin_pixel[0] = bmin_pixel[1] = std::numeric_limits<float>::max();
//    bmax_pixel[0] = bmax_pixel[1] = -std::numeric_limits<float>::max();

//    for (int l=0; l<3; l++) {
//        bmin_pixel[0]=std::min(     float(tc[l][0]*w), bmin_pixel[0]);   bmax_pixel[0]=std::max(  float(tc[l][0]*w), bmax_pixel[0]);
//        bmin_pixel[1]=std::min(     float(tc[l][1]*h), bmin_pixel[1]);   bmax_pixel[1]=std::max(  float(tc[l][1]*h), bmax_pixel[1]);
//    }

    sf::RenderTexture tex_out;
    tex_out.create(im_out.getSize().x,im_out.getSize().y,false);
    tex_out.setSmooth(true);
    tex_out.clear(sf::Color(0,255,0,255));

    int real_w=(bmax_pixel[0]-bmin_pixel[0]+1);
    int real_h=(bmax_pixel[1]-bmin_pixel[1]+1);

    sf::Texture tex_in;
//    tex_in.create(real_w+4,real_h+4);
    tex_in.create(real_w,real_h);
    tex_in.setSmooth(true);

//    tex_in.loadFromImage(*im_in,sf::IntRect(bmin_pixel[0],bmin_pixel[1],real_w+4,real_h+4));
    tex_in.loadFromImage(*im_in,sf::IntRect((int)bmin_pixel[0],(int)bmin_pixel[1],real_w,real_h));
    sf::Sprite spr_in;

    spr_in.setTexture(tex_in,true);

//    spr_in.setPosition(2,2);
//    spr_in.setPosition(0,0);

    spr_in.setOrigin( (float)real_w/2.0 , (float)real_h/2.0 );
    spr_in.setPosition( 0 , 0 );
    spr_in.setScale(factor,factor);

//    spr_in.setPosition( (float)im_out.getSize().x/2.0 , (float)im_out.getSize().y/2.0 );

//    spr_in.setOrigin(0,real_h-1);
    tex_out.draw(spr_in);
//    tex_out.draw(spr_in,sf::BlendNone);
    tex_out.display();
    im_out=tex_out.getTexture().copyToImage();
}
*/

/*
int rasterize(double v[3][3], double tc_org[3][2], int w_a, int h_a, int buf_count, int faces, sf::Image* image, double factor_a, sf::Image& image_copy,bool point,bool line,
               int offset_x, int offset_y, int offset_z, int box_x, int box_y, int box_z, unsigned short** mc_sub, double block_scale) {


    int bmin_vertex[3];
    int bmax_vertex[3];

    double tc[3][2];
    for (int n=0; n<3; n++) {
        tc[n][0]=tc_org[n][0]*(double)w_a;
        tc[n][1]=tc_org[n][1]*(double)h_a;
        bmin_vertex[n] = std::numeric_limits<double>::max();
        bmax_vertex[n] = -std::numeric_limits<double>::max();
    }

    sf::Color random_color=sf::Color(rand()%256,rand()%256,rand()%256,255);
    double bmin_pixel_o[2];
    double bmax_pixel_o[2];

    bmin_pixel_o[0] = bmin_pixel_o[1] = std::numeric_limits<double>::max();
    bmax_pixel_o[0] = bmax_pixel_o[1] = -std::numeric_limits<double>::max();

    for (int l=0; l<3; l++) {
        bmin_pixel_o[0]=std::min(     tc[l][0], bmin_pixel_o[0]);   bmax_pixel_o[0]=std::max(  tc[l][0], bmax_pixel_o[0]);
        bmin_pixel_o[1]=std::min(     tc[l][1], bmin_pixel_o[1]);   bmax_pixel_o[1]=std::max(  tc[l][1], bmax_pixel_o[1]);

        for (int n=0; n<3; n++) {
            bmin_vertex[l]=std::min(  (int)v[n][l], bmin_vertex[l]);
            bmax_vertex[l]=std::max(  (int)v[n][l], bmax_vertex[l]);
        }
    }



    char filename[2000];
    bool saved=false;

    static int num=0;

    double area;
    showit=false;

    bool skip_min_x=false;
    bool skip_max_x=false;
    bool skip_min_y=false;
    bool skip_max_y=false;


    if (tc[0][0]==bmin_pixel_o[0]) {
        tc[0][0]-=0.5f;
        skip_min_x=true;
    } else if (tc[0][0]==bmax_pixel_o[0]) {
        tc[0][0]+=0.5f;
        skip_max_x=true;
    }
    if (tc[0][1]==bmin_pixel_o[1]) {
        tc[0][1]-=0.5f;
        skip_min_y=true;
    } else if (tc[0][1]==bmax_pixel_o[1]) {
        tc[0][1]+=0.5f;
        skip_max_y=true;
    }

    if (tc[1][0]==bmin_pixel_o[0] && !skip_min_x) {
        tc[1][0]-=0.5f;
        skip_min_x=true;
    } else if (tc[1][0]==bmax_pixel_o[0] && !skip_max_x) {
        tc[1][0]+=0.5f;
        skip_max_x=true;
    }
    if (tc[1][1]==bmin_pixel_o[1] && !skip_min_y) {
        tc[1][1]-=0.5f;
        skip_min_y=true;
    } else if (tc[1][1]==bmax_pixel_o[1] && !skip_max_y) {
        tc[1][1]+=0.5f;
        skip_max_y=true;
    }

    if (tc[2][0]==bmin_pixel_o[0] && !skip_min_x) {
        tc[2][0]-=0.5f;
        skip_min_x=true;
    } else if (tc[2][0]==bmax_pixel_o[0] && !skip_max_x) {
         tc[2][0]+=0.5f;
         skip_max_x=true;
    }
    if (tc[2][1]==bmin_pixel_o[1] && !skip_min_y) {
        tc[2][1]-=0.5f;
        skip_min_y=true;
    } else if (tc[2][1]==bmax_pixel_o[1] && !skip_max_y) {
        tc[2][1]+=0.5f;
        skip_max_y=true;
    }

    bmin_pixel_o[0] = bmin_pixel_o[1] = std::numeric_limits<double>::max();
    bmax_pixel_o[0] = bmax_pixel_o[1] = -std::numeric_limits<double>::max();

    for (int l=0; l<3; l++) {
        bmin_pixel_o[0]=std::min(     tc[l][0], bmin_pixel_o[0]);   bmax_pixel_o[0]=std::max(  tc[l][0], bmax_pixel_o[0]);
        bmin_pixel_o[1]=std::min(     tc[l][1], bmin_pixel_o[1]);   bmax_pixel_o[1]=std::max(  tc[l][1], bmax_pixel_o[1]);
    }
//+asterix/
    area = edgeFunction(tc[2], tc[1], tc[0]);

    if (area!=0) {
        for (int plot_y = (int)bmin_pixel_o[1]-1; plot_y <= (int)bmax_pixel_o[1]+1; plot_y++) {
            for (int plot_x = (int)bmin_pixel_o[0]-1; plot_x <= (int)bmax_pixel_o[0]+1; plot_x++) {
                if ((int)plot_x<0 || (int)plot_x>=w_a || (int)plot_y<0 || (int)plot_y>=h_a) continue;

                Vec2 p = {(double)plot_x+0.5, (double)plot_y+0.5};
//                Vec2 p = {plot_x+0.5, plot_y+0.5};
                double w1 = edgeFunction(tc[0], tc[2], p);
                double w2 = edgeFunction(tc[1], tc[0], p);
                double w0 = edgeFunction(tc[2], tc[1], p);

                if ((w0 >= 0.0 && w1 >= 0.0 && w2 >= 0.0) || (w0 <= 0.0 && w1 <= 0.0 && w2 <= 0.0)) {
                    double v_x;
                    double v_y;
                    double v_z;
                    w0 /= area;
                    w1 /= area;
                    w2 /= area;

                    v_x = (w0 * (double)v[0][0]) + (w1 * (double)v[1][0]) + (w2 * (double)v[2][0]);
                    v_y = (w0 * (double)v[0][1]) + (w1 * (double)v[1][1]) + (w2 * (double)v[2][1]);
                    v_z = (w0 * (double)v[0][2]) + (w1 * (double)v[1][2]) + (w2 * (double)v[2][2]);

                    sf::Color pixel=image->getPixel((int)plot_x,(int)plot_y);
//                    sf::Color pixel=image->getPixel(plot_x+bmin_pixel_o[0],plot_y+bmin_pixel_o[1]);

                    int cube_x=v_x;
                    int cube_y=v_y;
                    int cube_z=v_z;
//                    int cube_x=v_x-offset_x;
//                    int cube_y=v_y-offset_y;
//                    int cube_z=v_z-offset_z;
//                    int cube_x=v_x*block_scale-offset_x;
//                    int cube_y=v_y*block_scale-offset_y;
//                    int cube_z=v_z*block_scale-offset_z;
//                    int cube_x=(v_x-offset_x)*block_scale;
//                    int cube_y=(v_y-offset_y)*block_scale;
//                    int cube_z=(v_z-offset_z)*block_scale;

                    if (cube_y==0) hit_cube_y_start=true;
                    if (cube_y==box_y-1) hit_cube_y_end=true;
                    if (cube_z==0) hit_cube_z_start=true;
                    if (cube_z==box_z-1) hit_cube_z_end=true;

                    if (wuppie_all) {
                        int real_y=cube_x+offset_real_y;
                        if (real_y>230) {
                            if (!warning_done_topping) {
                                printf("\nWarning: Topping: cube_x=%d  box_x=%d  real_y=%d  offset_x=%d  offset_real_y=%d (This message is only displayed once...)\n", cube_x, box_x, real_y,offset_x, offset_real_y);
                            }

                            float togo=real_y-230;
                            float new_real_y=230+togo/(1.0+(togo/25.0));
                            cube_x=new_real_y-offset_real_y;
                            if (!warning_done_topping) {
                                real_y=cube_x+offset_real_y;
                                printf("\nNew_cube_x=%d new_real_y=%d\n", cube_x, real_y);
                                warning_done_topping=true;
                            }
                        }
                    }

                    if (cube_x==-1) cube_x=0; else if (cube_x==box_x) cube_x--;
                    if (cube_y==-1) cube_y=0; else if (cube_y==box_y) cube_y--;
                    if (cube_z==-1) cube_z=0; else if (cube_z==box_z) cube_z--;
                    if (cube_x>=box_x) {
                        if (!warning_done_x) {
                            printf("\nWarning: cube_x=%d  box_x=%d (This message is only displayed once...)\n", cube_x, box_x);
                            warning_done_x=true;
                        }
                    }
                    else if (cube_y>=box_y) {
                        if (!warning_done_y) {
                            printf("\nWarning: cube_y=%d  box_y=%d (This message is only displayed once...)\n", cube_y, box_y);
                            warning_done_y=true;
                        }
                    }
                    else if (cube_z>=box_z) {
                        if (!warning_done_z) {
                            printf("\nWarning: cube_z=%d  box_z=%d (This message is only displayed once...)\n", cube_z, box_z);
                            warning_done_z=true;
                        }
                    }
                    else if (cube_x<0) printf("Warning: cube_x=%d  box_x=%d\n", cube_x, box_x);
                    else if (cube_y<0 ) printf("Warning: cube_y=%d  box_y=%d\n", cube_y, box_y);
                    else if (cube_z<0 ) printf("Warning: cube_z=%d  box_z=%d\n", cube_z, box_z);
                    else {

                        size_t tot_off_x=(cube_y+cube_z*box_y)*4;
                        unsigned short * cube_x_p=mc_sub[cube_x];
                        int curr=cube_x_p[tot_off_x+3];
                        cube_x_p[tot_off_x]     +=(unsigned short) pixel.r;
                        cube_x_p[tot_off_x+1]   +=(unsigned short) pixel.g;
                        cube_x_p[tot_off_x+2]   +=(unsigned short) pixel.b;
                        cube_x_p[tot_off_x+3]++;
                    }
                } else {
                }
            }
        }
    }
    return 0;
}

void magic(double v[3][3], double tc[3][2], struct image_loader* image_buffer, int buf_count, int faces, sf::Image& image_copy, int offset_x, int offset_y, int offset_z, int box_x, int box_y, int box_z, unsigned short **mc_sub, double block_scale) {

    double factor=1;
    int w = image_buffer->image->getSize().x;
    int h = image_buffer->image->getSize().y;

    bool point=false;
    if ( tc[0][0]==tc[1][0] && tc[0][0]==tc[2][0] && tc[0][1]==tc[1][1] && tc[0][1]==tc[2][1] ) { point=true; }

    bool line=false;
    if ( tc[0][0]==tc[1][0] && tc[0][1]==tc[1][1] )  { line=true; }
    if ( tc[1][0]==tc[2][0] && tc[1][1]==tc[2][1] )  { line=true; }
    if ( tc[2][0]==tc[0][0] && tc[2][1]==tc[0][1] )  { line=true; }

    if ( tc[0][0]==tc[1][0] && tc[0][0]==tc[2][0] )  { line=true; }
    if ( tc[0][1]==tc[1][1] && tc[0][1]==tc[2][1] )  { line=true; }


    rasterize(v, tc, w, h, buf_count, faces, image_buffer->image, factor, image_copy, point, line, offset_x, offset_y, offset_z, box_x, box_y, box_z, mc_sub, block_scale);
}

*/
extern std::vector<Voxel> voxels;
extern int check_tot_hits;
extern int check_tot_blocks;
extern toggle2();

int rasterize(double v[3][3], double tc_org[3][2], int w_a, int h_a, int buf_count, int faces, sf::Image* image, double factor_a, sf::Image& image_copy,
               int offset_x, int offset_y, int offset_z, int box_x, int box_y, int box_z, unsigned short** mc_sub, double block_scale) {
    int bmin_vertex[3];
    int bmax_vertex[3];
    int size_vertex[3];

    double tc[3][2];
    for (int n=0; n<3; n++) {
        tc[n][0]=tc_org[n][0]*(double)w_a;
        tc[n][1]=tc_org[n][1]*(double)h_a;
        bmin_vertex[n] = std::numeric_limits<double>::max();
        bmax_vertex[n] = -std::numeric_limits<double>::max();
    }

    sf::Color random_color=sf::Color(rand()%256,rand()%256,rand()%256,255);
    double bmin_pixel_o[2];
    double bmax_pixel_o[2];

    bmin_pixel_o[0] = bmin_pixel_o[1] = std::numeric_limits<double>::max();
    bmax_pixel_o[0] = bmax_pixel_o[1] = -std::numeric_limits<double>::max();

    for (int l=0; l<3; l++) {
        bmin_pixel_o[0]=std::min(     tc[l][0], bmin_pixel_o[0]);   bmax_pixel_o[0]=std::max(  tc[l][0], bmax_pixel_o[0]);
        bmin_pixel_o[1]=std::min(     tc[l][1], bmin_pixel_o[1]);   bmax_pixel_o[1]=std::max(  tc[l][1], bmax_pixel_o[1]);

        for (int n=0; n<3; n++) {
            bmin_vertex[l]=std::min(  (int)v[n][l], bmin_vertex[l]);
            bmax_vertex[l]=std::max(  (int)v[n][l], bmax_vertex[l]);
        }
        size_vertex[l]=bmax_vertex[l]-bmin_vertex[l]+1;
    }

    Voxel one;
    std::vector<Voxel> mini_voxel;

    char filename[2000];
    bool saved=false;

    static int num=0;

    double area;
    showit=false;

    bool skip_min_x=false;
    bool skip_max_x=false;
    bool skip_min_y=false;
    bool skip_max_y=false;

    area = edgeFunction(tc[2], tc[1], tc[0]);

//    double filler=pixels_per_block/block_scale;
extern double pixels_per_block_glob;
extern double pixels_per_block_glob_rev;
//    double filler=1.0/(pixels_per_block_glob/block_scale);
//    double filler=0.25*pixels_per_block_glob;
//    if (filler>0.5) filler=0.5;

//    double filler=1.0/(pixels_per_block_glob);
//    if (scale)
//    double filler=2.8/block_scale;
//    double filler=3.0/block_scale;
//    if (filler>1.0) filler=1.0;
//    double filler=2.0/block_scale;
//    double filler=0.10*(block_scale/pixels_per_block_glob);
    double filler;
    filler=pixels_per_block_glob/4.0;
    if (area!=0) {
        for (double plot_y = bmin_pixel_o[1]-1; plot_y <= bmax_pixel_o[1]+1; plot_y+=filler) {
            toggle2();
            for (double plot_x = bmin_pixel_o[0]-1; plot_x <= bmax_pixel_o[0]+1; plot_x+=filler) {
                if ((int)plot_x<0 || (int)plot_x>=w_a || (int)plot_y<0 || (int)plot_y>=h_a) continue;

                Vec2 p = {(double)plot_x, (double)plot_y};
//                Vec2 p = {(double)plot_x+0.5, (double)plot_y+0.5};
//                Vec2 p = {(double)plot_x+0.5*3.0/block_scale, (double)plot_y+0.5*3.0/block_scale};
//                Vec2 p = {plot_x+0.5, plot_y+0.5};
                double w1 = edgeFunction(tc[0], tc[2], p);
                double w2 = edgeFunction(tc[1], tc[0], p);
                double w0 = edgeFunction(tc[2], tc[1], p);

                if ((w0 >= 0.0 && w1 >= 0.0 && w2 >= 0.0) || (w0 <= 0.0 && w1 <= 0.0 && w2 <= 0.0)) {
                    double v_x;
                    double v_y;
                    double v_z;
                    w0 /= area;
                    w1 /= area;
                    w2 /= area;


                    v_x = (w0 * (double)v[0][0]) + (w1 * (double)v[1][0]) + (w2 * (double)v[2][0]);
                    v_y = (w0 * (double)v[0][1]) + (w1 * (double)v[1][1]) + (w2 * (double)v[2][1]);
                    v_z = (w0 * (double)v[0][2]) + (w1 * (double)v[1][2]) + (w2 * (double)v[2][2]);

                    int cube_x=v_x;
                    int cube_y=v_y;
                    int cube_z=v_z;
//                    int cube_x=(w0 * (double)v[0][0]) + (w1 * (double)v[1][0]) + (w2 * (double)v[2][0]);
//                    int cube_y=(w0 * (double)v[0][1]) + (w1 * (double)v[1][1]) + (w2 * (double)v[2][1]);
//                    int cube_z=(w0 * (double)v[0][2]) + (w1 * (double)v[1][2]) + (w2 * (double)v[2][2]);

/*
                    int real_y=cube_x+offset_real_y;
                    if (real_y>230) {
                        if (!warning_done_topping) {
                            printf("\nWarning: Topping: cube_x=%d  box_x=%d  real_y=%d  offset_x=%d  offset_real_y=%d (This message is only displayed once...)\n",
                                   cube_x, box_x, real_y,offset_x, offset_real_y);

                        }

                        float togo=real_y-230;
                        float new_real_y=230+togo/(1.0+(togo/35.0));
                        cube_x=new_real_y-offset_real_y;
                        if (!warning_done_topping) {
                            real_y=cube_x+offset_real_y;
                            printf("New_cube_x=%d new_real_y=%d\n", cube_x, real_y);
                            warning_done_topping=true;
                        }
                    } else if (real_y<10) {
                        if (!warning_done_topping) {
                            printf("\nWarning: Topping: cube_x=%d  box_x=%d  real_y=%d  offset_x=%d  offset_real_y=%d (This message is only displayed once...)\n", cube_x, box_x, real_y,offset_x, offset_real_y);
                        }

                        float togo=10-real_y;
                        float new_real_y=10-togo/(1.0+(togo/17.0));
                        cube_x=new_real_y-offset_real_y;
                        if (!warning_done_topping) {
                            real_y=cube_x+offset_real_y;
                            printf("New_cube_x=%d new_real_y=%d\n", cube_x, real_y);
                            warning_done_topping=true;
                        }
                    }
*/
                    sf::Color pixel=image->getPixel((int)plot_x,(int)plot_y);

//                    if (cube_x>=0 && cube_x<256) {
                        one=Voxel(cube_x,cube_y,cube_z,pixel.r,pixel.g,pixel.b,1,1);
//                        printf("X=%3d Y=%3d Z=%3d\n",cube_x,cube_y,cube_z);
    //                    one=Voxel((int)v_x,(int)v_y,(int)v_z,pixel.r,pixel.g,pixel.b,1,0);
                        mini_voxel.push_back(one);
                        check_tot_hits++;

//                    }

/*
                    if (cube_y==0) hit_cube_y_start=true;
                    if (cube_y==box_y-1) hit_cube_y_end=true;
                    if (cube_z==0) hit_cube_z_start=true;
                    if (cube_z==box_z-1) hit_cube_z_end=true;
*/

/*

                    if (cube_x==-1) cube_x=0; else if (cube_x==box_x) cube_x--;
                    if (cube_y==-1) cube_y=0; else if (cube_y==box_y) cube_y--;
                    if (cube_z==-1) cube_z=0; else if (cube_z==box_z) cube_z--;
                    if (cube_x>=box_x) {
                        if (!warning_done_x) {
                            printf("\nWarning: cube_x=%d  box_x=%d (This message is only displayed once...)\n", cube_x, box_x);
                            warning_done_x=true;
                        }
                    }
                    else if (cube_y>=box_y) {
                        if (!warning_done_y) {
                            printf("\nWarning: cube_y=%d  box_y=%d (This message is only displayed once...)\n", cube_y, box_y);
                            warning_done_y=true;
                        }
                    }
                    else if (cube_z>=box_z) {
                        if (!warning_done_z) {
                            printf("\nWarning: cube_z=%d  box_z=%d (This message is only displayed once...)\n", cube_z, box_z);
                            warning_done_z=true;
                        }
                    } else if (cube_x<0) {
                        if (!warning_done_x_min) {
                            printf("\nWarning: cube_x=%d  box_x=%d (This message is only displayed once...)\n", cube_x, box_x);
                            warning_done_x_min=true;
                        }
                    }
                    else if (cube_y<0) {
                        if (!warning_done_y_min) {
                            printf("\nWarning: cube_y=%d  box_y=%d (This message is only displayed once...)\n", cube_y, box_y);
                            warning_done_y_min=true;
                        }
                    }
                    else if (cube_z<0) {
                        if (!warning_done_z_min) {
                            printf("\nWarning: cube_z=%d  box_z=%d (This message is only displayed once...)\n", cube_z, box_z);
                            warning_done_z_min=true;
                        }
                    }
                    else {
                        one=Voxel((int)cube_x,(int)cube_y,(int)cube_z,pixel.r,pixel.g,pixel.b,1);
//                        one=Voxel((int)v_x,(int)v_y,(int)v_z,pixel.r,pixel.g,pixel.b,1);
                        mini_voxel.push_back(one);
                        check_tot_hits++;
                        size_t tot_off_x=(cube_y+cube_z*box_y)*4;
                        unsigned short * cube_x_p=mc_sub[cube_x];
                        int curr=cube_x_p[tot_off_x+3];
                        if (curr==0) check_tot_blocks++;

                        cube_x_p[tot_off_x]     +=(unsigned short) pixel.r;
                        cube_x_p[tot_off_x+1]   +=(unsigned short) pixel.g;
                        cube_x_p[tot_off_x+2]   +=(unsigned short) pixel.b;
                        cube_x_p[tot_off_x+3]++;
                    }
*/

                }
            }
        }
    }


    if (mini_voxel.size()>0) {

//        std::vector<Voxel> mini_voxel_new;
        Voxel adder=Voxel();
//        int count=0;
/*
        printf("\n");
        for (auto u : mini_voxel) {
            printf("org: mini_voxel[%3d]=Voxel(%6d,%6d,%6d,%4d,%4d,%4d,%4d)\n",count++,u.x,u.y,u.z,u.r,u.g,u.b,u.l);
            adder.x+=u.x;
            adder.y+=u.y;
            adder.z+=u.z;
            adder.r+=u.r;
            adder.g+=u.g;
            adder.b+=u.b;
            adder.l+=u.l;
        }
        printf("-----------------------------------------------------------------\n");
        printf("tot: mini_voxel[%3d]=                     Voxel(%4d,%4d,%4d,%4d)\n",count,adder.r,adder.g,adder.b,adder.l);
*/
        sort(mini_voxel.begin(), mini_voxel.end());
/*
        count=0;
        printf("\n");
        for (auto u : mini_voxel) {
            printf("srt: mini_voxel[%3d]=Voxel(%6d,%6d,%6d,%4d,%4d,%4d,%4d)\n",count++,u.x,u.y,u.z,u.r,u.g,u.b,u.l);
        }
*/
        size_t total_hits=0;
        size_t total_voxels=0;

        Voxel last=mini_voxel[0];
        Voxel total_pos=Voxel(last.x,last.y,last.z);
        for (size_t n=0; n<mini_voxel.size(); n++) {
            if (last.x==mini_voxel[n].x && last.y==mini_voxel[n].y && last.z==mini_voxel[n].z) {
                total_pos.r+=mini_voxel[n].r;
                total_pos.g+=mini_voxel[n].g;
                total_pos.b+=mini_voxel[n].b;
                total_pos.l+=mini_voxel[n].l;
                if (n==mini_voxel.size()-1) {
                    total_hits+=total_pos.l;
                    total_voxels+=1;
                    total_pos.x+=voxel_bottom;
                    total_pos.y+=mazemovex_voxel;
                    total_pos.z+=mazemovey_voxel;

                    voxels.push_back(total_pos);
                    if (plot_cubes) to_plot_cubes(total_pos);
                }
            } else {
                total_hits+=total_pos.l;
                total_voxels+=1;
                    total_pos.x+=voxel_bottom;
                total_pos.y+=mazemovex_voxel;
                total_pos.z+=mazemovey_voxel;

                voxels.push_back(total_pos);
                if (plot_cubes) to_plot_cubes(total_pos);
                last=mini_voxel[n];
                total_pos=last;
                if (n==mini_voxel.size()-1) {
                    total_hits+=total_pos.l;
                    total_voxels+=1;
                    total_pos.x+=voxel_bottom;
                    total_pos.y+=mazemovex_voxel;
                    total_pos.z+=mazemovey_voxel;
                    voxels.push_back(total_pos);
                    if (plot_cubes) to_plot_cubes(total_pos);
                }
            }
        }
//        if (total_voxels>0) printf("HITS/VOXEL=%f",(double)total_hits/(double)total_voxels);

/*
        count=0;
        printf("\n");
        adder=Voxel();
        for (auto u : mini_voxel_new) {
            printf("new: mini_voxel[%3d]=Voxel(%6d,%6d,%6d,%4d,%4d,%4d,%4d)\n",count++,u.x,u.y,u.z,u.r,u.g,u.b,u.l);
            adder.x+=u.x;
            adder.y+=u.y;
            adder.z+=u.z;
            adder.r+=u.r;
            adder.g+=u.g;
            adder.b+=u.b;
            adder.l+=u.l;
        }
        printf("-----------------------------------------------------------------\n");
        printf("tot: mini_voxel[%3d]=                     Voxel(%4d,%4d,%4d,%4d)\n",count,adder.r,adder.g,adder.b,adder.l);
        printf("\n");
*/
    }
    return 0;
}
extern int replace_str(char *str, char *orig, char *rep);

void magic(double v[3][3], double tc[3][2], struct image_loader* image_buffer, int buf_count, int faces, sf::Image& image_copy, int offset_x, int offset_y, int offset_z, int box_x, int box_y, int box_z, unsigned short **mc_sub, double block_scale) {

    double factor=1;
    int w = image_buffer->image->getSize().x;
    int h = image_buffer->image->getSize().y;

    rasterize(v, tc, w, h, buf_count, faces, image_buffer->image, factor, image_copy, offset_x, offset_y, offset_z, box_x, box_y, box_z, mc_sub, block_scale);
}

void magic2(double v[3][3], double tc[3][2], sf::Image* image, int buf_count, int faces, sf::Image& image_copy, int offset_x, int offset_y, int offset_z, int box_x, int box_y, int box_z, unsigned short **mc_sub, double block_scale) {

    double factor=1;
    int w = image->getSize().x;
    int h = image->getSize().y;

    rasterize(v, tc, w, h, buf_count, faces, image, factor, image_copy, offset_x, offset_y, offset_z, box_x, box_y, box_z, mc_sub, block_scale);
}

extern std::vector<Voxel> voxels_total;
extern std::string area;
extern bool file_exists(const char * filename);

bool load_voxels() {
    char fname[200]; sprintf (fname,"../cut/%s.vox",area.c_str());
    size_t check_tot_lines=0;
    size_t check_tot_voxels=0;
    size_t check_tot_errors=0;

    if (file_exists(fname)) {
        FILE* voxel_file_pointer=NULL;

        printf("OPENING VOXEL FILE: %s ",fname);
        voxel_file_pointer=fopen(fname,"r");
        if (voxel_file_pointer!=NULL) {
            voxels_total.clear();
            printf("OK. READING VOXELS\n");
            char fline[200]="";
            Voxel one;
            int xxx,yyy,zzz;
            int r,g,b,l;
            char x_str[20];
            char y_str[20];
            char z_str[20];

            while (fgets (fline,200, voxel_file_pointer)!=NULL ) {
                check_tot_lines++;

//                    fprintf(voxel_file_pointer,"(%d,%d,%d),(%d,%d,%d),(%d)\n",
//                            u.y, u.x, u.z,  u.r/u.l,u.g/u.l, u.b/u.l,  u.l );
//                while (replace_str(fline,"(",""));
//                while (replace_str(fline,")",""));
//                while (replace_str(fline,","," "));

                int num;

//                if ( (num=sscanf(fline,"(%20[^,]%20[^,]%20[^)],(%u,%u,%u,%u)",y_str,x_str,z_str,&r,&g,&b,&l))==7 ) {  //??
//                    xxx=atoi(x_str);
//                    yyy=atoi(y_str);
//                    zzz=atoi(z_str);
//                if (sscanf(fline,"%d,%d,%d,%u,%u,%u,%u",&yyy,&xxx,&zzz,&r,&g,&b,&l)==7) {
//                if (sscanf(fline,"%d,%d,%d,%u,%u,%u,%u",&yyy,&xxx,&zzz,&r,&g,&b,&l)==7) {
                if (sscanf(fline,"(%d,%d,%d),(%d,%d,%d),(%d)",&yyy,&xxx,&zzz,&r,&g,&b,&l)==7) {
                    check_tot_voxels++;
//                    printf("x,y,z=%ld,%ld,%ld\n",x,y,z);
                    if (!(check_tot_lines%100000)) printf("%dK %dK (%6d,%4d,%6d),(%3d,%3d,%3d),(%3d)        \r",
                                                    check_tot_lines/1000, check_tot_voxels/1000, yyy, xxx, zzz, r, g, b, l);
//                    one=Voxel(xxx,yyy,zzz,r,g,b,1,(unsigned char)1); // hold
                    one=Voxel(xxx,yyy,zzz,r,g,b,1,(unsigned char)0); // new

//                    fprintf(voxel_file_pointer,"(%d,%d,%d),(%d,%d,%d),(%d)\n",
//                            u.y, u.x, u.z,  u.r/u.l,u.g/u.l, u.b/u.l,  u.l );

                    voxels_total.push_back(one);
                }
                else {
                    printf("Error reading line %d from %s\n",check_tot_lines,fname);
                    if (check_tot_errors>10) {
                        voxels_total.clear();
                        return 0;
                    }
                }
            }
        } else {
            printf("Error opening %s\n",fname);
            return 0;
        }
        if (voxel_file_pointer!=NULL) fclose(voxel_file_pointer);
    } else {
        printf("FILE %s DOESN'T EXIST!\n",fname);
       return 0;
    }
    printf("READY: %d %d                                              \n",check_tot_lines,check_tot_voxels);
    return 1;
}

extern char mc_text0[100];
extern char mc_text1[100];
extern char mc_text2[100];
extern int plotting;
extern int main_mceditor6_fixed(int region_x, int region_z, unsigned char* mc);
extern int MCEDITOR_running;
extern unsigned char region_block[];

bool no_plotting=false;
extern std::vector<Voxel> voxels_total;

bool make_region_from_voxel(int x, int z) {
    char fname[200];
    sprintf(fname,"../cut/r.%d.%d.vox",x,z);

    std::vector<Voxel> voxels_temp;

    size_t check_tot_lines=0;
    size_t check_tot_voxels=0;
    size_t check_tot_errors=0;

    voxels_temp.clear();
    if (file_exists(fname)) {
        FILE* voxel_file_pointer=NULL;

        printf("OPENING VOXEL FILE: %s ",fname);
        voxel_file_pointer=fopen(fname,"r");
        if (voxel_file_pointer!=NULL) {
            printf("OK. READING VOXELS\n");
            char fline[200]="";
            Voxel one;
            int xxx,yyy,zzz;
            int r,g,b,l;
            char x_str[20];
            char y_str[20];
            char z_str[20];

            while (fgets (fline,200, voxel_file_pointer)!=NULL ) {
                check_tot_lines++;
                int num;
                if (sscanf(fline,"(%d,%d,%d),(%d,%d,%d),(%d)",&yyy,&xxx,&zzz,&r,&g,&b,&l)==7) {
                    check_tot_voxels++;
                    if (!(check_tot_lines%100000)) printf("%dK %dK (%6d,%4d,%6d),(%3d,%3d,%3d),(%3d)        \r",
                                                    check_tot_lines/1000, check_tot_voxels/1000, yyy, xxx, zzz, r, g, b, l);
                    one=Voxel(xxx,yyy,zzz,r,g,b,1,(unsigned char)0); // new
                    voxels_temp.push_back(one);
                }
                else {
                    printf("Error reading line %d from %s\n",check_tot_lines,fname);
                    if (check_tot_errors>10) {
                        voxels_temp.clear();
                        fclose(voxel_file_pointer);
                        return 0;
                    }
                }
            }
        } else {
            printf("Error opening %s\n",fname);
            return 0;
        }
        if (voxel_file_pointer!=NULL) fclose(voxel_file_pointer);
    } else {
        printf("FILE %s DOESN'T EXIST!\n",fname);
       return 0;
    }

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
    printf("READY: %d %d                                              \n",check_tot_lines,check_tot_voxels);
    if (voxels_temp.size()==0) {
        printf("\nERROR: voxels=%d\n", voxels);
        return 0;
    }
    voxels_temp.clear();
    return 1;
}

void to_plot_cubes(Voxel& total_pos) {
   cube_plot.lock();
    m_pointCloud3.append(
        sf::Vertex(
            sf::Vector2f(
                (float)(total_pos.y),
                (float)(total_pos.z)
            ),
            sf::Color(total_pos.r/total_pos.l,total_pos.g/total_pos.l,total_pos.b/total_pos.l,total_pos.x),
            sf::Vector2f(
                (float) (((total_pos.y+total_pos.z+1000)%6)*256)*150.0,
                (float) (0)*150.0
            )
        )
    );
    cube_plot.unlock();
}
