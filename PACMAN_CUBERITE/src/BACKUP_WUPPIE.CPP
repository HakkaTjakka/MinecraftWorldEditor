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

struct image_loader {
    std::string filename;
    sf::Image* image;
    bool ready=false;
    bool ok=true;
    size_t index;
    sf::Thread *thread_pointer;
    std::string previous="";
};

typedef float Vec2[2];
typedef float Vec3[3];
typedef float Vec4[4];

typedef unsigned char Rgb[3];

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

	float  l=sqrt(va[0]*va[0]+va[1]*va[1]+va[2]*va[2]);
	if (l==0.0) return false;
	i[0]=sqrt(va1[0]*va1[0]+va1[1]*va1[1]+va1[2]*va1[2])/l;
	i[1]=sqrt(va2[0]*va2[0]+va2[1]*va2[1]+va2[2]*va2[2])/l;
	i[3]=sqrt(va3[0]*va3[0]+va3[1]*va3[1]+va3[2]*va3[2])/l;

	float dot1=dot3d(va,va1); i[0]=i[0] * (dot1 > 0) - (dot1 < 0);
	float dot2=dot3d(va,va2); i[1]=i[1] * (dot2 > 0) - (dot2 < 0);
	float dot3=dot3d(va,va3); i[2]=i[2] * (dot3 > 0) - (dot3 < 0);
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


bool distance_to_plane_sub(const Vec4 &plane, const Vec3 &p, float& d) {
    float root=sqrt(plane[0]*plane[0]+plane[1]*plane[1]+plane[2]*plane[2]);
    if (root==0.0) return false;
    d=fabs(plane[0]*p[0]+plane[1]*p[1]+plane[2]*p[2]+plane[3]);
    return true;
}

bool distance_to_plane(const Vec3 &a, const Vec3 &b, const Vec3 &c, const Vec3 &p, float&d) {
    Vec4 plane;
    get_plane(a, b, c, plane);
    return distance_to_plane_sub(plane, p, d);
}

float edgeFunction2(const Vec2 &a, const Vec2 &b, const Vec2 &c) {
    return (  (c[0]-a[0]) * (b[1]-a[1]) - (b[0]-a[0]) * (c[1]-a[1])  );
}

float edgeFunction(const Vec2 &a, const Vec2 &b, const Vec2 &c) {
    float ret=(c[0]-a[0]) * (b[1]-a[1]) - (b[0]-a[0]) * (c[1]-a[1]);
    if (ret==0.0) {
        printf("( %f - %f] ) * ( %f - %f] ) - ( %f - %f] ) * ( %f - %f )  =  %f * %f - %f * %f  =  %f - %f  =  %f" ,
                                c[0] , a[0] , b[1] , a[1] , b[0] , a[0] , c[1] , a[1],
                                (c[0]-a[0]) , (b[1]-a[1]) , (b[0]-a[0]) , (c[1]-a[1]),
                                (c[0]-a[0]) * (b[1]-a[1]) , (b[0]-a[0]) * (c[1]-a[1]) , ret );
    } else {
        return ret;
    }
//    return (  (c[0]-a[0]) * (b[1]-a[1]) - (b[0]-a[0]) * (c[1]-a[1])  );
}

void projec_point_to_plane_sub(const Vec4 &plane, const Vec3 &p, Vec3& pp, const Vec3& orig)  {
    Vec3 v={p[0]-orig[0], p[1]-orig[1], p[2]-orig[2]};
    float dist = v[0]*plane[0] + v[1]*plane[1] + v[2]*plane[2];
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

    float w0 = edgeFunction(V0, V2, p);
    float w1 = edgeFunction(V1, V0, p);
    float w2 = edgeFunction(V2, V1, p);

    return (w0 >= 0.0 && w1 >= 0.0 && w2 >= 0.0) || (w0 <= 0.0 && w1 <= 0.0 && w2 <= 0.0);
}

bool insideTriangle_3d(const Vec3 &a, const Vec3 &b, const Vec3 &c, const Vec3 &p)  {
    bool inside = true;

	Vec3 a_min_b={ a[0]-b[0], a[1]-b[1], a[2]-b[2]};
	Vec3 a_min_c={ a[0]-c[0], a[1]-c[1], a[2]-c[2]};

	Vec3 ap={ a[0]-p[0], a[1]-p[1], a[2]-p[2]};
	Vec3 bp={ b[0]-p[0], b[1]-p[1], b[2]-p[2]};
	Vec3 cp={ c[0]-p[0], c[1]-p[1], c[2]-p[2]};

	float area = fabs(dot3d(a_min_b,a_min_c))/2.0;
	if (area==0.0) return false;
	float w0=fabs(dot3d(bp,cp))/area;
	float w1=fabs(dot3d(cp,ap))/area;
	float w2=fabs(dot3d(ap,bp))/area;

//	if (w0>=0 && w0<=1 && w1>=0 && w1<=1 && w2>=0 && w2<=1 && ((w0+w1+w2)>0.99 || (w0+w1+w2)<1.01) ) return true;
	if (w0>=0 && w0<=1 && w1>=0 && w1<=1 && w2>=0 && w2<=1 && w0+w1+w2==1.0 ) return true;
	return false;
}

void adapt_raster_image(sf::Image &im_out,sf::Image* im_in, float factor, float tc[3][2], uint32_t w, uint32_t h, float bmin_pixel[2], float bmax_pixel[2]) {
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
    tex_out.setSmooth(!true);
    tex_out.clear(sf::Color(0,255,0,255));

    int real_w=(bmax_pixel[0]-bmin_pixel[0]+1);
    int real_h=(bmax_pixel[1]-bmin_pixel[1]+1);

    sf::Texture tex_in;
//    tex_in.create(real_w+4,real_h+4);
    tex_in.create(real_w,real_h);
    tex_in.setSmooth(!true);

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

char *backup=NULL;

int rasterize(float v[3][3], float tc[3][2], uint32_t w_a, uint32_t h_a, int buf_count, int faces, sf::Image* image, float factor_a, sf::Image& image_copy,bool point,bool line,
               float offset_x, float offset_y, float offset_z, int box_x, int box_y, int box_z, char* mc, float block_scale) {
//    factor=-factor*.5-0.25;

    sf::Color random_color=sf::Color(rand()%256,rand()%256,rand()%256,255);
    float bmin_pixel_o[2];
    float bmax_pixel_o[2];

    bmin_pixel_o[0] = bmin_pixel_o[1] = std::numeric_limits<float>::max();
    bmax_pixel_o[0] = bmax_pixel_o[1] = -std::numeric_limits<float>::max();

    for (int l=0; l<3; l++) {
        bmin_pixel_o[0]=std::min(     float(tc[l][0]*w_a), bmin_pixel_o[0]);   bmax_pixel_o[0]=std::max(  float(tc[l][0]*w_a), bmax_pixel_o[0]);
        bmin_pixel_o[1]=std::min(     float(tc[l][1]*h_a), bmin_pixel_o[1]);   bmax_pixel_o[1]=std::max(  float(tc[l][1]*h_a), bmax_pixel_o[1]);
    }

    uint32_t w=factor_a*w_a;
    uint32_t h=factor_a*h_a;

    float factor=factor_a*.5f-0.5f;

    float bmin_pixel[2];
    float bmax_pixel[2];

    bmin_pixel[0] = bmin_pixel[1] = std::numeric_limits<float>::max();
    bmax_pixel[0] = bmax_pixel[1] = -std::numeric_limits<float>::max();

    for (int l=0; l<3; l++) {
        bmin_pixel[0]=std::min(     float(tc[l][0]*w-factor), bmin_pixel[0]);   bmax_pixel[0]=std::max(  float(tc[l][0]*w-factor), bmax_pixel[0]);
        bmin_pixel[1]=std::min(     float(tc[l][1]*h-factor), bmin_pixel[1]);   bmax_pixel[1]=std::max(  float(tc[l][1]*h-factor), bmax_pixel[1]);
//        bmin_pixel[0]=std::min(     float(tc[l][0]*w-factor-0.5), bmin_pixel[0]);   bmax_pixel[0]=std::max(  float(tc[l][0]*w-factor+0.5), bmax_pixel[0]);
//        bmin_pixel[1]=std::min(     float(tc[l][1]*h-factor-0.5), bmin_pixel[1]);   bmax_pixel[1]=std::max(  float(tc[l][1]*h-factor+0.5), bmax_pixel[1]);
    }
    int real_w=(bmax_pixel[0]-bmin_pixel[0]+1);
    int real_h=(bmax_pixel[1]-bmin_pixel[1]+1);

    sf::Image im_out;
    im_out.create(real_w+4,real_h+4);
//    real_w++;
//    real_h++;

    if (factor_a!=1.0)
        adapt_raster_image(im_out,image,factor_a,tc,w_a,h_a,bmin_pixel_o,bmax_pixel_o);
    else {
        im_out.copy(*image,2,2,sf::IntRect((int)bmin_pixel_o[0],(int)bmin_pixel_o[1],real_w,real_h));
    }
    char filename[2000];
    bool saved=false;
    if (!(rand()%500)) {
        saved=true;
        sprintf(filename, "../cut/raster2d.%03d.%03d.start.png", buf_count, faces );
        im_out.saveToFile(filename);
    }

    static int num=0;
    Vec2 v0;
    Vec2 v1;
    Vec2 v2;
    v0[0] = tc[0][0]*w-factor; v0[1] = tc[0][1]*h-factor;
    v1[0] = tc[1][0]*w-factor; v1[1] = tc[1][1]*h-factor;
    v2[0] = tc[2][0]*w-factor; v2[1] = tc[2][1]*h-factor;

    if (!(line || point)) {
        if (v0[0]==bmin_pixel[0]) v0[0]-=0.5f; else if (v0[0]==bmax_pixel[0]) v0[0]+=0.5f;
        if (v0[1]==bmin_pixel[1]) v0[1]-=0.5f; else if (v0[1]==bmax_pixel[1]) v0[1]+=0.5f;

        if (v1[0]==bmin_pixel[0]) v1[0]-=0.5f; else if (v1[0]==bmax_pixel[0]) v1[0]+=0.5f;
        if (v1[1]==bmin_pixel[1]) v1[1]-=0.5f; else if (v1[1]==bmax_pixel[1]) v1[1]+=0.5f;

        if (v2[0]==bmin_pixel[0]) v2[0]-=0.5f; else if (v2[0]==bmax_pixel[0]) v2[0]+=0.5f;
        if (v2[1]==bmin_pixel[1]) v2[1]-=0.5f; else if (v2[1]==bmax_pixel[1]) v2[1]+=0.5f;
    }

    float area;
    area = edgeFunction(v2, v1, v0);

/*
    if (real_w==1 || real_h==1 || point==1 || line==1 || area==0.0) {
        printf("area=%6.3f  bmin=(%3d,%3d) max=(%3d,%3d)  real_w=%3d real_h=%3d  point=%d  line=%d  ",
               area,(int)bmin_pixel[0],(int)bmin_pixel[1],(int)bmax_pixel[0],(int)bmax_pixel[1],real_w,real_h,point,line);
        printf("TC:(%5.1f - %5.1f),(%5.1f - %5.1f),(%5.1f - %5.1f)\n",v0[0],v0[1],v1[0],v1[1],v2[0],v2[1]);
    }
*/
    int skip=false;
    if (!(point || line)) {
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
    }

//    printf("\n");
//    printf("TC:(%3d,%3d),(%3d,%3d),(%3d,%3d)\n",int(v0[0]),int(v0[1]),int(v1[0]),int(v1[1]),int(v2[0]),int(v2[1]));
    Vec3 c0 = {1, 0, 0};
    Vec3 c1 = {0, 1, 0};
    Vec3 c2 = {0, 0, 1};

    if (area!=0) {
        for (int plot_y = 0; plot_y < real_h+4; ++plot_y) {
            for (int plot_x = 0; plot_x < real_w+4; ++plot_x) {

                uint32_t i=plot_x+bmin_pixel[0]-2;
                uint32_t j=plot_y+bmin_pixel[1]-2;

    //            Vec2 p = {(float)i, (float)j};
                Vec2 p = {(float)i + 0.5f, (float)j + 0.5f};

                float w0 = edgeFunction(v0, v2, p);
                float w1 = edgeFunction(v1, v0, p);
                float w2 = edgeFunction(v2, v1, p);

                if ((w0 >= 0.0 && w1 >= 0.0 && w2 >= 0.0) || (w0 <= 0.0 && w1 <= 0.0 && w2 <= 0.0)) {
                    w0 /= area;
                    w1 /= area;
                    w2 /= area;
                    float r = (w0 * c0[0]) + (w1 * c1[0]) + (w2 * c2[0]);
                    float g = (w0 * c0[1]) + (w1 * c1[1]) + (w2 * c2[1]);
                    float b = (w0 * c0[2]) + (w1 * c1[2]) + (w2 * c2[2]);

                    float v_x = (w0 * v[0][0]) + (w1 * v[1][0]) + (w2 * v[2][0]);
                    float v_y = (w0 * v[0][1]) + (w1 * v[1][1]) + (w2 * v[2][1]);
                    float v_z = (w0 * v[0][2]) + (w1 * v[1][2]) + (w2 * v[2][2]);
                    sf::Color pixel=im_out.getPixel(plot_x,plot_y);
//                    printf("Buffer: %d  face: %d  T:(%3d,%3d) = C:(%3d,%3d,%3d)  ->  3D:(%8.3f,%8.3f,%8.3f)",buf_count,faces,i,j,pixel.r, pixel.g, pixel.b, v_x, v_y, v_z );

                    int cube_x=(v_x-offset_x)*block_scale;
                    int cube_y=(v_y-offset_y)*block_scale;
                    int cube_z=(v_z-offset_z)*block_scale;
//                    printf("  -> MC:(%4d,%4d,%4d)\n",cube_x,cube_y,cube_z);

                    if (cube_x<0 || cube_x>=box_x) printf("Error cube_x=%d  box_x=%d\n", cube_x, box_x);
                    else if (cube_y<0 || cube_y>=box_y) printf("Error cube_y=%d  box_y=%d\n", cube_y, box_y);
                    else if (cube_z<0 || cube_z>=box_z) printf("Error cube_z=%d  box_z=%d\n", cube_z, box_z);
                    else {
                        size_t tot_off=(cube_x+cube_y*box_x+cube_z*box_x*box_y)*4;
                        int curr=mc[tot_off+3];
                        mc[tot_off]     =int( ((float)mc[tot_off  ]*(float)curr+(float)pixel.r)/((float)curr+1.0) );
                        mc[tot_off+1]   =int( ((float)mc[tot_off+1]*(float)curr+(float)pixel.g)/((float)curr+1.0) );
                        mc[tot_off+2]   =int( ((float)mc[tot_off+2]*(float)curr+(float)pixel.b)/((float)curr+1.0) );
                        mc[tot_off+3]++;
                    }

//                    if (!(rand()%100)) printf("r=%f g=%f b=%f total rgb=%f\n",r,g,b,r+g+b);
//                    printf("r=%f g=%f b=%f   area=%f   w0=%f w1=%f w2=%f   i=%d j=%d\n",r*255.0,g*255.0,b*255.0,area,w0,w1,w2,i,j);

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
                            sf::Color pixel=image_copy.getPixel(pixel_x,pixel_y);
                            if (pixel.a!=254 && pixel.a!=252) {
                                if (pixel.a==250) {
//                                        pixel.r=(255-pixel.r)/2.0;
                                    pixel.a=252;
                                    image_copy.setPixel(pixel_x,pixel_y,pixel);
//                                        im_out.setPixel(plot_x,plot_y,sf::Color(255,0,0,253));
                                }
                                else {
//                                        pixel.r=(pixel.r*5)/6.0; // random_color
//                                        pixel.g=(pixel.g*5)/6.0;
//                                        pixel.b=(pixel.b*5)/6.0;
                                    pixel.a=254;
                                    image_copy.setPixel(pixel_x,pixel_y,pixel);
                                }
                            }
                        }
                    }
                } else {
                    if (plot_x>=0 && plot_x<real_w+4 && plot_y>=0 && plot_y<real_h+4) {
                        if (plot_x==0 || plot_x==real_w+4-1 || plot_y==0 || plot_y==real_h+4-1) {
                            im_out.setPixel(plot_x,plot_y,sf::Color(255,255,0,255));
                        } else if (plot_x==1 || plot_x==real_w+4-2 || plot_y==1 || plot_y==real_h+4-2) {
                            im_out.setPixel(plot_x,plot_y,sf::Color(0,255,255,255));
                        } else {
    //                        sf::Color pixel=im_out.getPixel(plot_x,plot_y);
    //                        im_out.setPixel(plot_x,plot_y,sf::Color((255+pixel.r*5)/6,pixel.g,pixel.b,255));
                            im_out.setPixel(plot_x,plot_y,sf::Color(255,255,255,0));
                        }
                    }
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
            backup = new char [backup_len];
        }

        std::memset(backup, 0x0, backup_len);

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
                                    size_t tot_off=offset;
                                    int curr=backup[tot_off+3];
                                    backup[tot_off]     =int( ((float)backup[tot_off  ]*(float)curr+(float)pixel.r)/((float)curr+1.0) );
                                    backup[tot_off+1]   =int( ((float)backup[tot_off+1]*(float)curr+(float)pixel.g)/((float)curr+1.0) );
                                    backup[tot_off+2]   =int( ((float)backup[tot_off+2]*(float)curr+(float)pixel.b)/((float)curr+1.0) );
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
                                size_t tot_off=(b[0]+b[1]*box_x+b[2]*box_x*box_y)*4;
                                int curr=mc[tot_off+3];
                                mc[tot_off]     =int( ((float)mc[tot_off  ]*(float)curr + (float)backup[offset  ]*(float)curr_backup  )/((float)(curr+curr_backup)) );
                                mc[tot_off+1]   =int( ((float)mc[tot_off+1]*(float)curr + (float)backup[offset+1]*(float)curr_backup  )/((float)(curr+curr_backup)) );
                                mc[tot_off+2]   =int( ((float)mc[tot_off+2]*(float)curr + (float)backup[offset+2]*(float)curr_backup  )/((float)(curr+curr_backup)) );
                                mc[tot_off+3]+=curr_backup;
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

    for (int y=0; y<image_copy.getSize().y; y++) {
        for (int x=0; x<image_copy.getSize().x; x++) {
            sf::Color color=image_copy.getPixel(x,y);
//            image_copy.setPixel(x,y,sf::Color(color.r,color.g,color.b,255));
            if (color.a==254) image_copy.setPixel(x,y,sf::Color( (random_color.r+color.r*3)/4,(random_color.g+color.g*3)/4,(random_color.b+color.b*3)/4,250));
        }
    }


//    char filename[2000];
    if (saved) {
        sprintf(filename, "../cut/raster2d.%03d.%03d.png", buf_count, faces );
        im_out.saveToFile(filename);
    }

    return 0;
}



void magic(float v[3][3], float tc[3][2], struct image_loader* image_buffer, int buf_count, int faces, sf::Image& image_copy, float offset_x, float offset_y, float offset_z, int box_x, int box_y, int box_z, char* mc, float block_scale) {
    float factor=1;
    uint32_t w = image_buffer->image->getSize().x;
    uint32_t h = image_buffer->image->getSize().y;

    bool point=false;
    if ( tc[0][0]==tc[1][0] && tc[0][0]==tc[2][0] && tc[0][1]==tc[1][1] && tc[0][1]==tc[2][1] ) { point=true; }

    bool line=false;
    if ( tc[0][0]==tc[1][0] && tc[0][1]==tc[1][1] )  { line=true; }
    if ( tc[1][0]==tc[2][0] && tc[1][1]==tc[2][1] )  { line=true; }
    if ( tc[2][0]==tc[0][0] && tc[2][1]==tc[0][1] )  { line=true; }

    if ( tc[0][0]==tc[1][0] && tc[0][0]==tc[2][0] )  { line=true; }
    if ( tc[0][1]==tc[1][1] && tc[0][1]==tc[2][1] )  { line=true; }


    rasterize(v, tc, w, h, buf_count, faces, image_buffer->image, factor, image_copy, point, line, offset_x, offset_y, offset_z, box_x, box_y, box_z, mc, block_scale);
}


/*

//    Rgb *framebuffer = new Rgb[w * h];
//    std::memset(framebuffer, 0x0, w * h * 3);


//                framebuffer[j * w + i][0] = (unsigned char)(0);
//                framebuffer[j * w + i][1] = (unsigned char)(0);
//                framebuffer[j * w + i][2] = (unsigned char)(255);


                framebuffer[j * w + i][0] = (unsigned char)(r * 255.0);
                framebuffer[j * w + i][1] = (unsigned char)(g * 255.0);
                framebuffer[j * w + i][2] = (unsigned char)(b * 255.0);




//    std::ofstream ofs;
    char filename[2000];
//    sprintf(filename, "../cut/raster2d.%03d.%03d.ppm", buf_count, faces );
//    ofs.open(filename);
//    ofs << "P6\n" << w << " " << h << "\n255\n";
//    ofs.write((char*)framebuffer, w * h * 3);
//    ofs.close();
    sprintf(filename, "../cut/raster2d.%03d.%03d.png", buf_count, faces );
    im_out.saveToFile(filename);

//    delete [] framebuffer;
*/
