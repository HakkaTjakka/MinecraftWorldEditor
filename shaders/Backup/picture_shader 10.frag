uniform sampler2D texture_in;
uniform sampler2D texture_buffer;
uniform vec2 pos_correction;
uniform int iMouse_on;
uniform int background_plot;
uniform int formula_on;
uniform vec2 iResolution;
uniform vec2 pos_abs;
uniform vec2 iMouse;
uniform float iTime;

#define NUMSPHERES 30

// The MIT License
// Copyright © 2017 Inigo Quilez
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software. THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.


// Experimenting with this rendering algorithm, in at attempt to get perfectly antialiased
// pixels without performing any supersampling.
//
// Key ingredients are:
// 1. analytical sphere to pixel overlap
//    http://iquilezles.org/www/articles/spherefunctions/spherefunctions.htm
// 2. analytical surface pattern filtering (ray differentials needed)
//    http://iquilezles.org/www/articles/morecheckerfiltering/morecheckerfiltering.htm
// 3. approximate soft shadows with a single ray
//    http://iquilezles.org/www/articles/sphereshadow/sphereshadow.htm


// Algorithm (for eaxh pixel):
//
// 1. interesect objects, and record pixel coverage into a list
// 2. sort list front to back
// 3. while list contains objects:
// 4.    shade (with ray differentials for AA)
// 5.    composite (front to back)
// 6.    early exit if opaque threshold reached
// 7. composite with background


//-------------------------------------------------------------------------------------------

#define Time (iTime+188.0)

vec3 sphNormal( in vec3 pos, in vec4 sph )
{
    return normalize(pos-sph.xyz);
}

vec2 sphDistances( in vec3 ro, in vec3 rd, in vec4 sph )
{
	vec3 oc = ro - sph.xyz;
    float b = dot( oc, rd );
    float c = dot( oc, oc ) - sph.w*sph.w;
    float h = b*b - c;
    float d = sqrt( max(0.0,sph.w*sph.w-h)) - sph.w;
    return vec2( d, -b-sqrt(max(h,0.0)) );
}

float sphSoftShadow( in vec3 ro, in vec3 rd, in vec4 sph )
{
    float s = 1.0;
    vec2 r = sphDistances( ro, rd, sph );
    if( r.y>0.0 )
        s = max(r.x,0.0)/r.y;
    return s;
}

float sphOcclusion( in vec3 pos, in vec3 nor, in vec4 sph )
{
    vec3  r = sph.xyz - pos;
    float l = length(r);
    float d = dot(nor,r);
    float res = d;

    if( d<sph.w ) res = pow(clamp((d+sph.w)/(2.0*sph.w),0.0,1.0),1.5)*sph.w;

    return clamp( res*(sph.w*sph.w)/(l*l*l), 0.0, 1.0 );

}

//-------------------------------------------------------------------------------------------

vec4 sphere[NUMSPHERES];
float sphereF[NUMSPHERES];
float vol;

//-------------------------------------------------------------------------------------------

float linesTextureGradBox( in float p, in float ddx, in float ddy, int id )
{
    float N = float( 2 + 7*((id>>1)&3) );

    float w = max(abs(ddx), abs(ddy)) + 0.01;
    float a = p + 0.5*w;
    float b = p - 0.5*w;
    return 1.0 - (floor(a)+min(fract(a)*N,1.0)-
                  floor(b)-min(fract(b)*N,1.0))/(N*w);
}

float computeU( in vec3 pos, in vec4 sph, int id )
{
    #if 1
    vec3 q = normalize( pos - sph.xyz );
    if ((id&2)==2) {
        float a;
        if ((id&4)==4)
            a = ((id&1)==1) ? acos(q.y) : atan(q.x,q.z);
        else
            a = ((id&1)==1) ? acos(q.y) : atan(q.z,q.y);
        return 6.0*(3.0/3.141593) * a;
    } else {
        float a = (pos-sph.xyz)[id&1]/sph.w;
        a += abs(a*a)*sign(a);
        return 5.0*(3.0/3.141593) * a;
    }
    #else
    float a = (pos-sph.xyz)[id&1]/sph.w;
    a += abs(a*a)*sign(a);
    return 5.0*(3.0/3.141593) * a;
    #endif
}

vec4 shade( in vec3 rd, in vec3 pos, in vec3 ddx_pos, in vec3 ddy_pos,
            in vec3 nor, in int id, in vec4 sph )
{
    // compute UVs and filter shape

	float u     = computeU(     pos, sph, id );
    float ddx_u = computeU( ddx_pos, sph, id );
    float ddy_u = computeU( ddy_pos, sph, id );

    // texture
	vec3 col;
//	col.zyx = vec3(0.0, 0.0,0.8);
//	col.xyz = vec3(0.0, 0.2 + 0.4*clamp(1.0-sph.w*2.0,0.0,2.0),0.8);
//	col.xyz = vec3(float(id)/1.0, 0.2 + 0.4*clamp(1.0-sph.w*2.0,0.0,2.0),0.8);
	col = vec3(0.0, 0.2 + 0.4*clamp(1.0-sph.w*2.0,0.0,2.0),0.8);
//	col = vec3( 0.2 + 0.4*clamp(1.0-sph.w*2.0,0.0,2.0),0.8,0.0);
    col *= 1.0 - linesTextureGradBox( u, ddx_u-u, ddy_u-u, id );
	col *= sphereF[id];

    // lighting

    vec3 ref = reflect(rd,normalize(nor-0.2*rd)); //vec3 ref = reflect(rd,nor);

	// compute reflection shadow, ambient occlusion and edge proximty
    float sha = 1.0;
	float occ = 1.0;
	float pro = 1e10;
	for( int i=0; i<NUMSPHERES; i++ )
    {
        if( i!=id )
        {
        sha = min( sha, 10.0*sphSoftShadow(pos+0.005*nor,ref,sphere[i]) );
        pro = min( pro, abs(length(pos-sphere[i].xyz)-sphere[i].w) );
      //occ = min( occ, 1.0 - sphOcclusion( pos, nor, sphere[i] ) );
	    occ *= 1.0 - sphOcclusion( pos, nor, sphere[i] );
        }
	}

    float fre = clamp(1.0+dot(rd,nor),0.0,1.0);
    occ = occ*0.5 + 0.5*occ*occ;

	// light-surface interaction
    vec3 lig = vec3(occ)*1.4;
    lig *= 0.7 + 0.3*nor.y;
    lig += 0.5*fre*fre*occ;
    lig *= col;
    lig += 1.2*smoothstep(-0.1,0.10,ref.y )*occ*sha * (0.03+0.97*pow(fre,4.0));

    // glow
	float g = clamp(pro/(1.0+15.0*vol),0.0,0.5*sph.w);
//    lig.bgr += (0.2+0.8*vol)*vec3(  0.5*vol,  0,  1.0)*exp(-15000.0*g*g*20.0);
//    lig.bgr += (0.1+0.9*vol)*vec3(  0.0,      0,  1.0)*exp(-2000.0*g*g*20.0);

    lig += (0.2+0.8*vol)*vec3(  0.5*vol,  0.4+0.4*vol,  1.0)*exp(-15000.0*g*g*20.0);
    lig += (0.1+0.9*vol)*vec3(  0.0,      0.50,         1.0)*exp(-2000.0*g*g*20.0);

    return vec4(lig,1.0);
}

vec4 render( in vec3 ro, in vec3 rd, in float px,
             in vec3 ddx_ro, in vec3 ddy_ro,
             in vec3 ddx_rd, in vec3 ddy_rd)
{
    vec3 tao[NUMSPHERES];

    // intersect spheres
    int num = 0;
	for( int i=0; i<NUMSPHERES; i++ )
	{
		vec4 sph = sphere[i];
        vec2 dt = sphDistances( ro, rd, sph );
        float d = dt.x;
	    float t = dt.y;
        //if( t<0.0 ) continue; // skip stuff behind camera

        float s = max( 0.0, d/t );
        if( s < px ) // intersection, or close enough to an intersection
        {
            tao[num].x = t;                         // depth
            tao[num].y = 1.0 - clamp(s/px,0.0,1.0); // pixel coverage
            tao[num].z = float(i);                  // object id
            num++;
        }
	}

    if( num==0 ) return vec4(0.0);

    // (bubble) sort intersections, front to back
	for( int i=0; i<num-1; i++ )
    for( int j=i+1; j<num; j++ )
    {
        if( tao[j].x < tao[i].x )
        {
            vec3 tm = tao[i];
            tao[i] = tao[j];
            tao[j] = tm;
        }
	}

    // front to back composite to minimize shading cost
    vec4 col = vec4(0.0);
    float ot = tao[0].x;
	for( int i=0; i<num; i++ )
    {
        float t   = tao[i].x;
        float al  = tao[i].y;
        float fid = tao[i].z;
        int   iid = int(fid);

        /*
        if( i+1<num )
        {
        	al *= clamp( 0.5 + 0.5*(tao[i+1].x-t)/(px*2.0*t), 0.0, 1.0 );
        }
        */

        vec4 sph = sphere[iid];
        vec3 pos = ro + t*rd;
//        if (t>7.0) continue;
        vec3 nor = sphNormal( pos, sph );

        // compute ray differentials
        vec3 ddx_pos = ddx_ro - ddx_rd*dot(ddx_ro-pos,nor)/dot(ddx_rd,nor);
        vec3 ddy_pos = ddy_ro - ddy_rd*dot(ddy_ro-pos,nor)/dot(ddy_rd,nor);

        // shade
        vec4 tmpcol = shade( rd, pos, ddx_pos, ddy_pos, nor, iid, sph );

        // multiply transparency by coverage
        tmpcol.a *= al;

        // composite
        col.xyz = (1.0-col.w)*tmpcol.w*tmpcol.xyz + col.xyz;
	    col.w   = 1.0 - (1.0-tmpcol.w)*(1.0-col.w);  //col.w = col.w + tmpcol.w - tmpcol.w*col.w;

        // early exit on opaque surfaces
        if( col.a>0.999 ) break;
    }

    return col;
}


void calcCamera( out vec3 ro, out vec3 ta )
{
    float an = 0.05*Time;

    if (formula_on==0) {
        ro = vec3(2.5*sin(pos_abs.x*3.141593),sin(pos_abs.y*3.141593)*2.5,-7.0);
//        ro = vec3(2.5*sin(pos_abs.x*3.141593),sin(pos_abs.y*3.141593)*2.5,2.5*cos(an));
//        ro = vec3(2.5*sin(an),sin(pos_abs.y*3.141593)*2.5,2.5*cos(an));
    } else {
        ro = vec3(2.5*sin(an),0.0,2.5*cos(an));
    }
//	ro = vec3(2.5*sin(an),1.0*cos(0.5*an),2.5*cos(an));
    ta = vec3(0.0,0.0,0.0);
}


void calcRayForPixel( in vec2 pix, in float fl, out vec3 resRo, out vec3 resRd )
{
	vec2 p = vec2(0);

    if (formula_on==0) {
        p = (2.0*pix-iResolution.xy) / iResolution.y/5.0;
    } else {
        p = (2.0*pix-iResolution.xy) / iResolution.y;
    }

    // camera movement
	vec3 ro, ta;
	calcCamera( ro, ta );
    // camera matrix
    vec3 ww = normalize( ta - ro );
    vec3 uu = normalize( cross(ww,vec3(0.0,1.0,0.0) ) );
    vec3 vv = normalize( cross(uu,ww));
	// create view ray
	vec3 rd = normalize( p.x*uu + p.y*vv + fl*ww );

	resRo = ro;
	resRd = rd;
}

vec3 hash3( float n ) { return fract(sin(vec3(n,n+1.0,n+2.0))*158.5453123); }

vec4 main2(vec2 fragCoord )
{
    //-----------------------------------------------------
    // animate
    //-----------------------------------------------------
    vol = 1.0;
//    for( int i=0; i<16; i++ )
//    {
//        float v = texelFetch( iChannel0, ivec2(i*16,1), 0 ).x-0.5;
//        vol += v*v;
//    }
    vol/=16.0;
    vol = vol*8.0;
    for( int i=0; i<NUMSPHERES; i++ )
	{
		float id  = float(i);
        float ra = pow(id/float(NUMSPHERES-1),8.0);
	    vec3  pos = cos( 6.2831*hash3(id*14.0) + 0.5*(1.0-0.7*ra)*hash3(id*7.0)*Time*0.15 );
        if (formula_on==0)
            pos = normalize(pos) * vec3(0.9,0.28,1.1);
        else
            pos = normalize(pos) * vec3(1.3,0.55,1.0);
//        pos *= 1.2-0.8*ra;

//        float f = 2.0-ra;//float(i)/float(NUMSPHERES);
        float f = (2.0-ra)/3.0;//float(i)/float(NUMSPHERES);
//        float a = (0.2+0.8*f)*textureLod( iChannel0, vec2(0.5*f,0.5/2.0), 0.0 ).x;
        float a = (0.2+0.8*f)*0.5;

        sphere[i] = vec4( pos, 0.5*(0.2+0.7*ra) );
        sphereF[i] = 0.0 + 1.0*a;
        sphere[i].w *= 0.1 + 3.25*a;
        sphere[i].xyz *= 1.0 + 0.2*a*(1.0-0.5*ra);
    }

	vec2 q = (fragCoord.xy-pos_correction.xy) / iResolution.xy;
    vec2 p = (2.0*(fragCoord.xy-pos_correction.xy)-iResolution.xy)/iResolution.y;

    //-----------------------------------------------------
    // camera
    //-----------------------------------------------------
    const float fl = 1.8;
	vec3 ro, rd, ddx_ro, ddx_rd, ddy_ro, ddy_rd;
	calcRayForPixel( fragCoord - pos_correction + vec2(0.0,0.0), fl, ro, rd );
	calcRayForPixel( fragCoord - pos_correction + vec2(1.0,0.0), fl, ddx_ro, ddx_rd );
	calcRayForPixel( fragCoord - pos_correction + vec2(0.0,1.0), fl, ddy_ro, ddy_rd );

    float px;
    if (formula_on==0) {
        px = (2.0/iResolution.y)*(1.0/fl)/5.0;
    } else {
        px = (2.0/iResolution.y)*(1.0/fl);
    }


    //-----------------------------------------------------
	// render
    //-----------------------------------------------------

    // background
//	vec4 col = vec4(0.02) + 0.02*rd.y + 0.1*smoothstep(-0.1,0.3,rd.y);
	vec4 col = vec4(0,0,0,1);

    // spheres
    vec4 res = render( ro, rd, px, ddx_ro, ddy_ro, ddx_rd, ddy_rd );
    col.xyz = col.xyz*(1.0-res.w) + res.xyz;
    col.a=res.a;
    //-----------------------------------------------------
	// postpro
    //-----------------------------------------------------
    // gamma
    col.xyz = pow( col.xyz, vec3(0.4545) );

    // vignetting
    col.xyz *= 0.25 + 0.75*pow(16.0*q.x*q.y*(1.0-q.x)*(1.0-q.y),0.1);

    // dithering
    col.xyz += (1.0/255.0)*hash3(q.x+13.0*q.y);

	return vec4( col);
}

void main() {
  gl_FragColor= main2(gl_FragCoord.xy);


//  float tussen=gl_FragColor.g;
//  gl_FragColor.r=1.0-gl_FragColor.b*2.0;
//  gl_FragColor.b=1.0-gl_FragColor.g;
//  gl_FragColor.r=0.5+gl_FragColor.b/2.0;
//    gl_FragColor.r=(gl_FragColor.g+gl_FragColor.b)/2.0;

//  gl_FragColor= (main2(gl_FragCoord.xy)*4 +
//                ( main2(gl_FragCoord.xy+vec2(-1,0)) + main2(gl_FragCoord.xy+vec2(0,-1)) + main2(gl_FragCoord.xy+vec2(1,0)) + main2(gl_FragCoord.xy+vec2(0,1)) )*2 +
//                 main2(gl_FragCoord.xy+vec2(-1,-1)) + main2(gl_FragCoord.xy+vec2(-1,1)) + main2(gl_FragCoord.xy+vec2(1,-1)) + main2(gl_FragCoord.xy+vec2(1,1)) )/16  ;
    if (background_plot==1) {
        vec4 background=texture(texture_in,(gl_FragCoord.xy/vec2(1920,1080)));
        gl_FragColor = mix(gl_FragColor,background,background.a);
    }
}


