//copy
precision highp float;
uniform sampler2D texture_in;
uniform sampler2D texture_buffer;
uniform vec2 pos_correction;
uniform int iMouse_on;
uniform vec2 iResolution;
uniform vec2 iMouse;
uniform float iTime;


#define STEPS 100
#define STOPDIST 1e-3
#define FUDGE 1.
#define ITERS 4
#define PI 3.141592653589793

vec3 color=vec3(1.,1.,1.);
vec3 cam_pos;
float total_len;

vec3 peano_transform(vec3 p){
    const float blockiness = ITERS>0 ? .8 : 1.;
    const float gap=pow(2.,float(-ITERS))/(1.-pow(2.,float(-ITERS))+blockiness);
    const float final_piece=2.*(pow(2.,float(-ITERS))-gap*(1.-pow(2.,float(-ITERS)))) + PI*.5*gap;

    float sublen=total_len=pow(8.,float(ITERS))*final_piece;
    float s=1.;
	float add=0.;
    float rev=1.;
    float flip=1.;
    for(int i=0;i<ITERS;++i){
        sublen*=1./8.;
        float a=(s+gap)*.5;
        vec3 sp=sign(p);
        if(sp==vec3(-1.,-1.,-1.)){p=vec3(+p.z+a,+p.y+a,+p.x+a); add-=rev*sublen*3.5; flip*=-1.; }
        if(sp==vec3(+1.,-1.,-1.)){p=vec3(+p.z+a,+p.x-a,+p.y+a); add-=rev*sublen*2.5; }
        if(sp==vec3(+1.,+1.,-1.)){p=vec3(+p.z+a,+p.x-a,-p.y+a); add-=rev*sublen*1.5; rev*=-1.; }
        if(sp==vec3(-1.,+1.,-1.)){p=vec3(-p.y+a,-p.x-a,+p.z+a); add-=rev*sublen*0.5; flip*=-1.; }
        if(sp==vec3(-1.,+1.,+1.)){p=vec3(-p.y+a,-p.x-a,-p.z+a); add+=rev*sublen*0.5; flip*=-1.; rev*=-1.; }
        if(sp==vec3(+1.,+1.,+1.)){p=vec3(-p.z+a,+p.x-a,-p.y+a); add+=rev*sublen*1.5; }
        if(sp==vec3(+1.,-1.,+1.)){p=vec3(-p.z+a,+p.x-a,+p.y+a); add+=rev*sublen*2.5; rev*=-1.; }
        if(sp==vec3(-1.,-1.,+1.)){p=vec3(+p.y+a,-p.z+a,+p.x+a); add+=rev*sublen*3.5; rev*=-1.; }
        s=(s-gap)*.5;
    }
    if(p.y>-gap && p.z<gap) p=vec3(p.x,length(p.yz-vec2(-gap,gap))-gap,(atan(p.y+gap,gap-p.z)-PI*.25)*gap);
    else if(-p.y>p.z) p=vec3(p.x,-p.z,p.y+(1.-PI*.25)*gap);
    else p.z+=(PI*.25-1.)*gap;
    p.z=p.z*rev+add;
    p.x*=flip;
    return p;
}

float sdf_particle(vec3 p){
    return length(p.xy)-.02;
    float z=p.z*7.+iTime;
    p.xy*=mat2(cos(z*1.3),sin(z*1.3),-sin(z*1.3),cos(z*1.3));
    p.yz*=mat2(cos(z*1.7),sin(z*1.7),-sin(z*1.7),cos(z*1.7));
    p.zx*=mat2(cos(z*2.1),sin(z*2.1),-sin(z*2.1),cos(z*2.1));
    p=abs(p);
    //return max(max(p.x,p.y),p.z)-.02;
    return length(p)-.02;
}

float sdf_inner(vec3 p){
    const float period=.05;
    float z=p.z+iTime*.1;
    p.z=mod(z,period)-.5*.05;
    if(mod(floor(z/period),10.)==0.) color=vec3(.8,.2,.2)*4.;
    else color=vec3(.2,.8,.2)*1.5;
    return sdf_particle(p);

    const float blockiness = ITERS>0 ? .5 : 1.;
    const float gap=pow(2.,float(-ITERS))/(1.-pow(2.,float(-ITERS))+blockiness);
    const float final_piece=2.*(pow(2.,float(-ITERS))-gap*(1.-pow(2.,float(-ITERS)))) + PI*.5*gap;
    //color=vec3(fract(p.z), fract(p.z*2.3), fract(p.z*1.7))*2.;

    //float ang=sin(p.z+iTime*1.3)*sin(iTime*3.);
    float ang=p.z*2.;
    float thickness=pow(max(0.,sin(p.z*3.+iTime*3.)-.95)*20.,.4)*.03+.02;
    //float thickness=step(.93,sin(p.z*3.+iTime*3.))*.03+.02;
    //float thickness=.04;
    p.xy*=mat2(cos(ang),sin(ang),-sin(ang),cos(ang));
    p.xy=abs(p.xy);
    //return length(p.xy)-thickness;
    return max(p.x,p.y)-thickness;
}

float sdf_main(vec3 p){
    vec3 ap=abs(p);
    float d_bbox=-1.1+max(max(ap.x,ap.y),ap.z);
    float d_cam=.2-distance(p,cam_pos);
    float d_cuts=max(d_bbox,d_cam);

    float d_curve=sdf_inner(peano_transform(p));
    if(d_cuts>d_curve && abs(d_curve)<1e-2) color=vec3(3.);
    return max(d_cuts,d_curve);
}

vec4 main2(vec2 fragCoord )
{
    vec4 fragColor;
    vec2 uv=((fragCoord.xy-pos_correction.xy)*2.-iResolution.xy)/iResolution.x;
    vec2 mouse=(iMouse.xy*2.-iResolution.xy)/iResolution.x;
//    vec2 click=(iMouse.zw*2.-iResolution.xy)/iResolution.x;

    vec2 pan;
//
//    if(iMouse.z<=0.){
        //pan=vec2(iTime/3., sin(iTime/2.)*.4); // inside view
        pan=vec2(iTime/10., sin(iTime/20.)*.4); // outside view
    //}else{
//     	pan=mouse-click;
//        pan.x*=6.;
//        pan.y*=1.5;
//    }

    //vec3 pos0=vec3(sin(pan.x),pan.y,cos(pan.x))*.8; // inside view
    vec3 pos0=vec3(sin(pan.x),pan.y,cos(pan.x))*3.; // outside view
    cam_pos=pos0;
    //vec3 dir=normalize(cross(-pos0,vec3(0.,1.,0.))); // inside view
    vec3 dir=normalize(-pos0); // outside view
    vec3 xdir=normalize(cross(vec3(0.,1.,0.),dir));
    vec3 ydir=normalize(cross(xdir,dir));
    dir+=uv.x*xdir+uv.y*ydir;
    dir=normalize(dir);

    vec3 pos=pos0;
    for(int i=0;i<STEPS;++i){
    	float d=sdf_main(pos)*FUDGE;
        pos+=dir*d;
        if(abs(d)<STOPDIST){
            fragColor=vec4(vec3(sqrt(float(i)/float(STEPS)))*color,1.);
            return fragColor;
        }
        if(length(pos)>1e3){
            fragColor=vec4(vec3(sqrt(float(i)/float(STEPS)))*vec3(1.,.5,.7),1.);
            return fragColor;
        }
    }
	fragColor = vec4(.2,.5,.7, 1.0);
    return fragColor;
}

void main() {
  gl_FragColor= main2(gl_FragCoord.xy);
//  gl_FragColor= (main2(gl_FragCoord.xy)*4 +
//                ( main2(gl_FragCoord.xy+vec2(-1,0)) + main2(gl_FragCoord.xy+vec2(0,-1)) + main2(gl_FragCoord.xy+vec2(1,0)) + main2(gl_FragCoord.xy+vec2(0,1)) )*2 +
//                 main2(gl_FragCoord.xy+vec2(-1,-1)) + main2(gl_FragCoord.xy+vec2(-1,1)) + main2(gl_FragCoord.xy+vec2(1,-1)) + main2(gl_FragCoord.xy+vec2(1,1)) )/16  ;
}

