#include <iostream>
#include <cmath>
#include <string>
#include "globals.h"
#include "MCEditor.h"
using namespace std;

struct RGB
{
    int r, g, b;
    RGB() {}
    RGB(int r_, int g_, int b_)
        :r(r_), g(g_), b(b_) {}

    double operator - (const RGB &C) const
    {
        double r_ = (r + C.r) / 2.0;
        double dr = r - C.r, dg = g - C.g, db = b - C.b;
        double d1 = 2 + r_ / 256.0, d2 = 2 + (255 - r_) / 256.0;
        return sqrt(d1 * dr * dr + 4 * dg * dg + d2 * db * db);
    }
    double operator + (const RGB &C) const
    {
        double ret=( fabs(r-C.r) +  fabs(g-C.g) + fabs(b-C.b));
        return ret;
    }
    RGB operator * (const RGB &C) const
    {
        return RGB(r*C.r, g*C.g, b*C.b);
    }
};

const RGB Preset2[16] = {
    RGB(0	,   0	    ,0	    ),       //black
    RGB(0	,   0	    ,170	),      //dark_blue
    RGB(0	,   170	    ,0	    ),      //dark_green
    RGB(0	,   170	    ,170	),      //dark_aqua
    RGB(170,	0	    ,0	    ),      //dark_red
    RGB(170,	0		,170	),      //dark_purple
    RGB(255,	170		,0	    ),      //gold
    RGB(170,	170		,170	),      //gray
    RGB(85	,   85	    ,85	    ),      //dark_gray
    RGB(85,	    85		,255	),      //blue
    RGB(85	,   255	    ,85	    ),      //green
    RGB(85	,   255	    ,255	),      //aqua
    RGB(255,	85		,85	    ),      //red
    RGB(255,	85		,255	),      //light_purple
    RGB(255,	255		,85	    ),      //yellow
    RGB(255,	255		,255	)       //white

};

unsigned char color_table[16][3]={
    {0	,   0	    ,0	    },       //black
    {0	,   0	    ,170	},      //dark_blue
    {0	,   170	    ,0	    },      //dark_green
    {0	,   170	    ,170	},      //dark_aqua
    {170,	0	    ,0	    },      //dark_red
    {170,	0		,170	},      //dark_purple
    {255,	170		,0	    },      //gold
    {170,	170		,170	},      //gray
    {85	,   85	    ,85	    },      //dark_gray
    {85,	85		,255	},      //blue
    {85	,   255	    ,85	    },      //green
    {85	,   255	    ,255	},      //aqua
    {255,	85		,85	    },      //red
    {255,	85		,255	},      //light_purple
    {255,	255		,85	    },      //yellow
    {255,	255		,255	}      //white
};

const RGB Preset[16] = {
    RGB(209, 214, 215),     RGB(211, 105, 41),  RGB(157, 58, 155),  RGB(65, 136, 194),
    RGB(232, 178, 63),      RGB(114, 168, 54),  RGB(201, 109, 144), RGB(53, 56, 60),
    RGB(125, 125, 116),     RGB(53, 118, 134),  RGB(92, 36, 152),   RGB(41, 48, 139),
    RGB(92, 60, 33),        RGB(76, 90, 40),    RGB(133, 40, 35),   RGB(1, 1, 1)
};

bool adapt_colors=true;

int ret_color(int r, int g, int b)
{

/*
    if (ri>128+20) r=r+(255-ri)/5;
    else if (ri<128-20) r=r-ri/5;

    if (gi>128+20) g=g+(255-gi)/5;
    else if (gi<128-20) g=g-gi/5;

    if (bi>128+20) b=b+(255-bi)/5;
    else if (bi<128-20) b=b-bi/5;
*/


    RGB pixel_color = RGB(r, g, b);

    int idx = 0;
    double res = 1e9;
    for (int k = 0; k < 16; k++)
    {

        double dis = pixel_color - Preset[k];

        if (dis < res)
        {
            res = dis;
            idx = k;
        }
    }
    if (adapt_colors) {
        if (idx==6) idx=14;

/*
        else if (idx==7) {
            if (r>g+10 && r>b+10) {
                idx=14;
            } else if (g>r+10 && g>b+10) {
                idx=13;
            } else if (b>r+40 && b>g+40) {
                idx=11;
            }
        } else if (idx==8) {
            if (r>g+10 && r>b+10) {
                idx=1;
            } else if (g>r+10 && g>b+10) {
                idx=5;
            } else if (b>r+40 && b>g+40) {
                idx=3;
            }
        }
*/

    }
    return idx;
}

void ret_color_rev(int idx, int&r,int&g,int&b )
{
    RGB pixel_color = Preset[idx];
    r=pixel_color.r;
    g=pixel_color.g;
    b=pixel_color.b;

}

const int Mos_Preset_trans[16] = {
    14, 10, 9, 6,
    89, 8, 11, 3,
    7, 2, 12, 254,
    1,4,13,253
};

int ret_Mos_color_rev(int idx)
{
    return Mos_Preset_trans[idx];
}

int ret_Mos_color(int r, int g, int b)
{
    int idx=ret_color(r, g, b);
    return Mos_Preset_trans[idx];
}


int ret_color2(int r,int g,int b) {
//*0.299
//*0.587
//*0.114

    RGB pixel_color = RGB(r, g, b) * RGB(0.7,0.7,0.5);

    unsigned char idx = 0;
    double res = 9999999999;
    for (int k = 0; k < 16; k++)
    {
//        float average = (r + g + b) / 3;
//        float dis = (r - average) + (g - average) + (b - average);

//        FLOAT dis=( Preset[k].r-r  + Preset[k].b-b + Preset[k].b-b );

//        int dr=color_table[k][0]-r;
//        int dg=color_table[k][0]-b;
//        int db=color_table[k][0]-b;

//        float dis=sqrt( dr*dr + dg*dg + db*db );

        double dis = pixel_color - (Preset[k] * RGB(0.7,0.7,0.5));

        if (dis < res)
        {
            res = dis;
            idx = k;
        }
    }
    return idx;
}

int ret_color3(int r,int g,int b) {

//    RGB pixel_color = RGB(r, g, b);

//*0.299
//*0.587
//*0.114
    int idx = 0;
    float res = 9999999999;
    for (int k = 0; k < 16; k++)
    {
        float dr=(float)(color_table[k][0]-r);
        float dg=(float)(color_table[k][1]-g);
        float db=(float)(color_table[k][2]-b);

        float dis= dr*dr + dg*dg + db*db;

        if (dis < res)
        {
            res = dis;
            idx = k;
        }
    }
    return idx;
}

