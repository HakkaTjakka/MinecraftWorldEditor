#include <stdio.h>
#include <math.h>

#define Xwidth 352
#define Yheight 288

//#define Xwidth 704
//#define Yheight 576

//   char bcol[Xwidth][Yheight];
//   char gcol[Xwidth][Yheight];
//   char rcol[Xwidth][Yheight];


typedef struct {
   char id_len;                 // ID Field (Number of bytes - max 255)
   char map_type;               // Colormap Field (0 or 1)
   char img_type;               // Image Type (7 options - color vs. compression)
   int  map_first;              // Color Map stuff - first entry index
   int  map_len;                // Color Map stuff - total entries in file
   char map_entry_size;         // Color Map stuff - number of bits per entry
   int  x;                      // X-coordinate of origin
   int  y;                      // Y-coordinate of origin
   int  width;                  // Width in Pixels
   int  height;                 // Height in Pixels
   char bpp;                    // Number of bits per pixel
   char misc;                   // Other stuff - scan origin and alpha bits
} targa_header;


void writeheader(targa_header h, FILE *tga)
  {
   fputc(h.id_len, tga);          // Write chars for ID, map, and image type
   fputc(h.map_type, tga);
   fputc(h.img_type, tga);
   fputc(h.map_first % 256, tga); // Write integer, low order byte first
   fputc(h.map_first / 256, tga); // Write second byte of integer, high order
   fputc(h.map_len % 256, tga);   // Another integer
   fputc(h.map_len / 256, tga);
   fputc(h.map_entry_size, tga);  // Write a char - only one byte
   fputc(h.x % 256, tga);         // More integers
   fputc(h.x / 256, tga);
   fputc(h.y % 256, tga);
   fputc(h.y / 256, tga);
   fputc(h.width % 256, tga);     // Even more integers
   fputc(h.width / 256, tga);
   fputc(h.height % 256, tga);
   fputc(h.height / 256, tga);
   fputc(h.bpp, tga);             // Write two chars
   fputc(h.misc, tga);
}

float maxim(float a, float b, float c)
  {
     float d;
     if (a>b) d=a; else d=b;
     if (c>d) d=c;
     return (d);
  }

float minim(float a, float b, float c)
  {
     float d;
     if (a<b) d=a; else d=b;
     if (c<d) d=c;
     return (d);
  }


int main(void) {
   FILE *tga;               // Pointer to a FILE
   targa_header header;     // Variable of targa_header type
   int x, y;
   float  xx, yy;
   float  xx1, yy1;
   float  xx2, yy2;
   int  xd, yd;
   float  x1, y1;
   int r,g,b;
   float rr,gg,bb;
   float r1,g1,b1;
   float r2,g2,b2;
   float r3,g3,b3;
   float r4,g4,b4;
   float r5,g5,b5;
   float rg,gb,br;
   float s,s1,s2,s3;
   float ww;
   char filename[30];
   int p;
   float offset;
   float offset2;
   float straal1;
   float straal2;
   float p1,p2,p3;
   int pmod1,pmod2,pmod3;
   int pdir1,pdir2,pdir3;



/* First, set all the fields in the header to appropriate values */
   header.id_len = 0;          /* no ID field */
   header.map_type = 0;        /* no colormap */
   header.img_type = 2;        /* trust me */
   header.map_first = 0;       /* not used */
   header.map_len = 0;         /* not used */
   header.map_entry_size = 0;  /* not used */
   header.x = 0;               /* image starts at (0,0) */
   header.y = 0;
   header.width = Xwidth;         /* image is 200 x 100 */
   header.height = Yheight;
   header.bpp = 24;            /* 24 bits per pixel */
   header.misc = 0x20;         /* scan from upper left corner */

   pdir1=pdir2=pdir3=1;
   pmod1=pmod2=pmod3=0;

   for (p=0; p<100000; p++) {


      sprintf(filename,"output/test%05d.tga",p);
      tga = fopen(filename, "wb"); /* Write the header information  */
      writeheader(header, tga);

      offset=2*3.1415/100*p;
      offset2=(sin(2*3.1415/500*p)+1)*3.1415;

      pmod1=pmod1+pdir1; if (pmod1==100) pdir1=-1; if (pmod1==0) pdir1=1;
      pmod2=pmod2+pdir2; if (pmod2==140) pdir2=-1; if (pmod2==0) pdir2=1;
      pmod3=pmod3+pdir3; if (pmod3==170) pdir3=-1; if (pmod3==0) pdir3=1;
      p1=(float)(pmod1)/100;
      p2=(float)(pmod2)/140;
      p3=(float)(pmod3)/170;
      printf("%f,%f,%f ",p1,p2,p3);
      printf("p=%05d\n",p);

      for(y = 0; y < Yheight; y++)
      {
            yy=(float)(y-Yheight/2);

            for(x = 0; x < Xwidth; x++)  {

                  xx=(float)(x-Xwidth/2);

                  yy1=(xx)*sin(-offset2)+(yy)*cos(-offset2);
                  xx1=(xx)*cos(-offset2)-(yy)*sin(-offset2);

                  yy2=(xx)*sin(offset2*1.2)+(yy)*cos(offset2*1.2);
                  xx2=(xx)*cos(offset2*1.2)-(yy)*sin(offset2*1.2);


                  straal1=sqrt((yy1)*(yy1)+(xx1-100)*(xx1-100));
                  straal2=sqrt((yy2)*(yy2)+(xx2+100)*(xx2+100));

                  xx1=xx1+straal1*cos(sin(straal1/200+offset*2.3));
                  yy1=yy1+straal1*sin(cos(straal1/200+offset*2.4));

                  xx2=xx2+straal2*cos(sin(straal2/200+offset*2.5));
                  yy2=yy2+straal2*sin(cos(straal2/200+offset*2.6));

                  rr=255.99/4*(sin( offset*0.1+(xx1-100)*(xx1-100)/5000)+cos( offset*2.7+(yy1-000)*(yy1-000)/4000 ) + 2);
                  gg=255.99/4*(sin( offset*1.2+(xx1-100)*(yy1-000)/5000)+cos( offset*1.8+(xx1-100)*(yy1-000)/4000 ) + 2);
                  bb=255.99/4*(cos( offset*2.3+(xx1-100)*(xx1-100)/5000)+sin( offset*1.9+(yy1-000)*(yy1-000)/4000 ) + 2);

                  rg=255.99/4*(sin( offset*1.4+(xx2+100)*(xx2-000)/5000)+cos( offset*3.0+(yy2-000)*(yy2-125)/4000 ) + 2);
                  gb=255.99/4*(sin( offset*1.5+(xx2-200)*(yy2-000)/5000)+cos( offset*2.1+(xx2-000)*(yy2+125)/4000 ) + 2);
                  br=255.99/4*(cos( offset*1.6+(xx2+200)*(xx2-100)/5000)+sin( offset*2.2+(yy2-000)*(yy2+125)/4000 ) + 2);


                  r1=maxim(rr,rg,gb);
                  g1=maxim(gg,gb,rg);
                  b1=maxim(bb,br,gb);

                  r2=minim(rr,rg,gb);
                  g2=minim(gg,gb,rg);
                  b2=minim(bb,br,gb);

                  rr=p1*r2 + (1-p1)*r1;
                  gg=p2*g2 + (1-p2)*g1;
                  bb=p3*b2 + (1-p3)*b1;

                  b=((int)bb)%256;fputc(  b, tga);
                  g=((int)gg)%256;fputc(  g, tga);
                  r=((int)rr)%256;fputc(  r, tga);
                  xx=(float)(x-Xwidth/2);

                  yy1=(xx)*sin(-offset2)+(yy)*cos(-offset2);
                  xx1=(xx)*cos(-offset2)-(yy)*sin(-offset2);

                  yy2=(xx)*sin(offset2*1.2)+(yy)*cos(offset2*1.2);
                  xx2=(xx)*cos(offset2*1.2)-(yy)*sin(offset2*1.2);


                  straal1=sqrt((yy1)*(yy1)+(xx1-100)*(xx1-100));
                  straal2=sqrt((yy2)*(yy2)+(xx2+100)*(xx2+100));

                  xx1=xx1+straal1*cos(sin(straal1/200+offset*2.3));
                  yy1=yy1+straal1*sin(cos(straal1/200+offset*2.4));

                  xx2=xx2+straal2*cos(sin(straal2/200+offset*2.5));
                  yy2=yy2+straal2*sin(cos(straal2/200+offset*2.6));

                  rr=255.99/4*(sin( offset*0.1+(xx1-100)*(xx1-100)/5000)+cos( offset*2.7+(yy1-000)*(yy1-000)/4000 ) + 2);
                  gg=255.99/4*(sin( offset*1.2+(xx1-100)*(yy1-000)/5000)+cos( offset*1.8+(xx1-100)*(yy1-000)/4000 ) + 2);
                  bb=255.99/4*(cos( offset*2.3+(xx1-100)*(xx1-100)/5000)+sin( offset*1.9+(yy1-000)*(yy1-000)/4000 ) + 2);

                  rg=255.99/4*(sin( offset*1.4+(xx2+100)*(xx2-000)/5000)+cos( offset*3.0+(yy2-000)*(yy2-125)/4000 ) + 2);
                  gb=255.99/4*(sin( offset*1.5+(xx2-200)*(yy2-000)/5000)+cos( offset*2.1+(xx2-000)*(yy2+125)/4000 ) + 2);
                  br=255.99/4*(cos( offset*1.6+(xx2+200)*(xx2-100)/5000)+sin( offset*2.2+(yy2-000)*(yy2+125)/4000 ) + 2);


                  r1=maxim(rr,rg,gb);
                  g1=maxim(gg,gb,rg);
                  b1=maxim(bb,br,gb);

                  r2=minim(rr,rg,gb);
                  g2=minim(gg,gb,rg);
                  b2=minim(bb,br,gb);

                  rr=p1*r2 + (1-p1)*r1;
                  gg=p2*g2 + (1-p2)*g1;
                  bb=p3*b2 + (1-p3)*b1;

                  b=((int)bb)%256;fputc(  b, tga);
                  g=((int)gg)%256;fputc(  g, tga);
                  r=((int)rr)%256;fputc(  r, tga);

           }
      }
      fclose(tga);
   }
   return 0;
}


