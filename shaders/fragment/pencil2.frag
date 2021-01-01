//copy
//precision highp float;
// use graphics 2
uniform sampler2D texture_surround[9];
uniform sampler2D texture_in;
uniform sampler2D texture_buffer;
uniform vec2 iResolution_buffer;
uniform vec2 pos_correction;
uniform int iMouse_on;
uniform vec2 iResolution;
uniform vec2 iMouse;
uniform vec2 iSubpixel;
uniform float iTime;
uniform int iFrame;
uniform int background_plot;
uniform int buffer_plot;
uniform vec2 pos_abs;
uniform int formula;
uniform float iRotate;
#define PI 3.141592653589793
uniform sampler2D texture_data;
uniform vec2 dResolution;

#define SHADERTOY
#ifdef SHADERTOY
#define Res0 iResolution.xy
#define Res1 dResolution.xy
#else
#define Res0 textureSize(texture_in,0)
#define Res1 textureSize(texture_data,0)
//#define iResolution Res0
#endif

#define Res  iResolution.xy

#define randSamp texture_data
#define colorSamp texture_in

#define iChannel1 texture_data
#define iChannel0 texture_in

vec2 getCol_A=Res.xy*.5;
vec2 getCol_B=vec2(Res0.y/Res.y);
vec2 getCol_C=vec2(Res.y/Res0.y/Res0.xy);

vec4 getRand(vec2 pos)
{
    vec2 uv=(pos-getCol_A);
    uv=uv.xy*getCol_C.xy + vec2(.5,.5);
	uv.y=1.0-uv.y;
    return texture(iChannel0,uv);

//	vec2 off = vec2( sin(iTime/10.0)*dResolution.x , cos(iTime/10.0)*dResolution.y );
//	pos = pos+off;

//    return textureLod(iChannel1,pos/Res1/iResolution.y*1080., 0.0);

//	return vec4(1.0,1.0,1.0,1.0);
}


vec4 getCol(vec2 pos)
{
    vec2 uv=(pos-getCol_A);
    uv=uv.xy*getCol_C.xy + vec2(.5,.5);
	uv.y=1.0-uv.y;

    vec4 c1=texture(iChannel0,uv);
    vec4 e=smoothstep(vec4(-0.05),vec4(-0.0),vec4(uv,vec2(1)-uv));
    c1=mix(vec4(1,1,1,0),c1,e.x*e.y*e.z*e.w);
    float d=clamp(dot(c1.xyz,vec3(-.5,1.,-.5)),0.0,1.0);
    vec4 c2=vec4(.7);
    return min(mix(c1,c2,1.8*d),.7);
}

vec4 getColHT(vec2 pos)
{
 	return smoothstep(.95,1.05,getCol(pos)*.8+.2+getRand(pos));
// 	return smoothstep(.95,1.05,getCol(pos)*.8+.2+getRand(pos*.7));
// 	return smoothstep(.95,1.05,getCol(pos)*.8+.2+getRand(pos*.7));
}

float getVal(vec2 pos)
{
    vec4 c=getCol(pos);
 	return pow(dot(c.xyz,vec3(.333)),1.)*1.;
}

vec2 getGrad(vec2 pos, float eps)
{
   	vec2 d=vec2(eps,0);
    return vec2(
        getVal(pos+d.xy)-getVal(pos-d.xy),
        getVal(pos+d.yx)-getVal(pos-d.yx)
    )/eps/2.;
}

#define AngleNum 3

#define SampNum 16
#define PI2 6.28318530717959

vec4 mainImage( vec2 fragCoord )
{
	vec4 fragColor = vec4(0);
//    vec2 pos = fragCoord+4.0*sin(iTime*1.*vec2(1,1.7))*iResolution.y/400.;
    vec2 pos = fragCoord;
    vec3 col = vec3(0);
    vec3 col2 = vec3(0);
    float sum=0.;
    for(int i=0;i<AngleNum;i++)
    {
        float ang=PI2/float(AngleNum)*(float(i)+.8)+iTime*0.4;
        vec2 v=vec2(cos(ang),sin(ang));
        for(int j=0;j<SampNum;j++)
        {
            vec2 dpos  = v.yx*vec2(1,-1)*float(j)*iResolution.y/400.;
            vec2 dpos2 = v.xy*float(j*j)/float(SampNum)*.5*iResolution.y/400.;
	        vec2 g;
            float fact;
            float fact2;

            for(float s=-1.;s<=1.;s+=2.)
            {
                vec2 pos2=pos+s*dpos+dpos2;
                vec2 pos3=pos+(s*dpos+dpos2).yx*vec2(1,-1)*2.;
            	g=getGrad(pos2,.4);
//            	fact=dot(g,v)-.5*abs(dot(g,v.yx*vec2(1,-1)))*(1.-getVal(pos2));
            	fact=dot(g,v)-.5*abs(dot(g,v.yx*vec2(1,-1)))/**(1.-getVal(pos2))*/;
            	fact2=dot(normalize(g+vec2(.0001)),v.yx*vec2(1,-1));
                
                fact=clamp(fact,0.,.05);
                fact2=abs(fact2);
                
                fact*=1.-float(j)/float(SampNum);
            	col += fact;
            	col2 += fact2*getColHT(pos3).xyz;
            	sum+=fact2;
            }
        }
    }
    col/=float(SampNum*AngleNum)*.75/sqrt(iResolution.y);
    col2/=sum;
//    col.x*=(.6+.8*getRand(pos*.7).x);
    col.x*=(.6+.8*getRand(pos).x);
    col.x=1.-col.x;
    col.x*=col.x*col.x;

//    vec2 s=sin(pos.xy*.1/sqrt(iResolution.y/400.));
//    vec3 karo=vec3(1);
//    karo-=.5*vec3(.25,.1,.1)*dot(exp(-s*s*80.),vec2(1));
//    float r=length(pos-iResolution.xy*.5)/iResolution.x;
//    float vign=1.-r*r*r;

//	fragColor = vec4(vec3(col.x),1);

	fragColor = vec4(col.x*(getCol(fragCoord).xyz+col2)/2.0,1);
//	fragColor = vec4(col.x*col2,1);
//	fragColor = vec4(vec3(col.x*( getCol(pos) + col2 )/2.0),1);
//	fragColor = vec4(vec3(col.x*col2),1);
//	fragColor = vec4(col.x*col2*vign,1);
//	fragColor = vec4(col.x*col2*karo*vign,1);
//	fragColor = vec4(vec3(col.x*col2*karo*vign),1);
    //fragColor=getCol(fragCoord);
	return fragColor;
}

void main_copy()
{

    if (background_plot==1) {
        vec2 uv = vec2(1.0,-1.0)*(gl_FragCoord.xy-pos_correction.xy) /iResolution.xy;
        gl_FragColor = texture(texture_buffer,uv);   // from picture
        vec4 background=texture(texture_in,(gl_FragCoord.xy/vec2(1920,1080)));
        gl_FragColor = mix(gl_FragColor,background,background.a);           // back/front plotting.
    } else {
//        vec2 uv = vec2(1.0,-1.0)*(gl_FragCoord.xy-pos_correction.xy) / iResolution.xy;   //just copy and show. (Do nothing, maybe smooth blur when drawing?)

        vec2 coord = (gl_FragCoord.xy-pos_correction.xy);
		
		gl_FragColor = mainImage(coord.xy);


//        gl_FragColor = texture(texture_in,uv);
//		float trans=(gl_FragColor.r+gl_FragColor.g+gl_FragColor.b)/3.0;
//        vec4 background=texture(texture_data,(gl_FragCoord.xy/dResolution));
//        gl_FragColor = mix(gl_FragColor,background,trans);
    }
}

void main() {
    main_copy();
}
