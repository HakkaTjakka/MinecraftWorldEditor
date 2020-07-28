precision highp float;
uniform sampler2D texture_buffer;
uniform vec2 iResolution;
uniform vec2 pos_correction;
uniform int iFrame;
uniform int iTime;
uniform int iMouse_on;
uniform vec2 iMouse;

#define RotNum 5
#define Res  iResolution
#define Res1 iResolution

const float ang = 2.0*3.1415926535/float(RotNum);
mat2 m = mat2(cos(ang),sin(ang),-sin(ang),cos(ang));

vec4 randS(vec2 uv)
{
    return texture(texture_buffer,uv*Res.xy/Res1.xy)-vec4(0.5);
}

float getRot(vec2 pos, vec2 b)
{
    vec2 p = b;
    float rot=0.0;

    for(int i=0;i<RotNum;i++)
    {
        rot=rot+dot(   texture(   texture_buffer , fract((pos+p)/Res.xy)  ).xy - vec2(0.5,0.5)  ,  p.yx*vec2(1,-1)   );
        p = m*p;
    }
    return rot/float(RotNum)/dot(b,b);
}

float circle(in vec2 _st, in float _radius, in vec2 position){
    vec2 dist = (_st-position)*iResolution.xy/iResolution.y;
	return 1.-smoothstep(_radius-(_radius*0.05),
                         _radius+(_radius*0.05),
                         dot(dist,dist)*4.0);
}

void main()
{
    vec2 pos=gl_FragCoord.xy;
//    float rnd=randS(vec2(float(iFrame)/Res.x,0.5/Res1.y)).x;
    float rnd=randS(vec2(iTime/Res.x,0.5/Res1.y)).x;
    vec2 b=vec2(cos(ang*rnd),sin(ang*rnd));
    vec2 v=vec2(0);
    float bbMax=0.7*Res.y; bbMax*=bbMax;
    for(int l=0;l<20;l++)
    {
        if ( dot(b,b) > bbMax ) break;
        vec2 p = b;
        for(int i=0;i<RotNum;i++)
        {
            v+=p.yx*getRot(pos+p,b);
            p = m*p;
        }
        b*=2.0;
    }
    gl_FragColor=texture(  texture_buffer  ,  fract( (pos+v*vec2(-1,1)*2.0-vec2(0,0))/Res.xy )  );  //!!!!!!!!!
//    gl_FragColor=texture(  texture_buffer  ,  fract( (pos+v*vec2(-1,1)*2.0)/Res.xy )  );
//    gl_FragColor.xyz=clamp(  (1.0+sin(float(iFrame)/19.0)*0.01) * texture(  texture_buffer  ,  fract( (pos+v*vec2(-1,1)*2.0)/Res.xy ) ).xyz  , vec3(0.0), vec3(1.0) ).xyz   ;
//    gl_FragColor= texture(  texture_buffer  ,  fract( (pos+v*vec2(-1,1)*2.0)/Res.xy ) )  ;
//    if (gl_FragColor.xyz==vec3(0))  gl_FragColor.a=0.0;
//    gl_FragColor.a=(gl_FragColor.r+gl_FragColor.g+gl_FragColor.b)/3.0;
    gl_FragColor.a=1.0;

    vec2 mid=vec2(gl_FragCoord.xy-iResolution.xy/2.0);
    vec2 rotje=vec2( sin(float(iFrame)/10.0)*40.0 , cos(float(iFrame)/10.0)*40.0 );
    vec2 r2=vec2(sin(float(iFrame)/1770.0) , cos(float(iFrame)/10.0));
    vec2 r3=vec2(sin(float(iFrame)/307.0) , cos(float(iFrame)/307.0));

//    if ( floor( ((mid+rotje               )/ 2.0) ) == vec2(0) ) gl_FragColor.rgb=vec3(0);
//    if ( floor( ((mid+rotje+vec2(-200,   0))/ 2.0) ) == vec2(0) ) gl_FragColor.rgb=vec3(0);
//    if ( floor( ((mid+rotje+vec2( 200,   0))/ 2.0) ) == vec2(0) ) gl_FragColor.rgb=vec3(0);

//if (iMouse_on==1) {
//    if ( floor( ((mid+rotje*2+vec2(-550, -450)*r2)/188.0) ) == vec2(0) ) gl_FragColor.rgb+=vec3(0.5,0,0);
//    if ( floor( ((mid+rotje*2+vec2(-250, 450)*r2)/50.0) ) == vec2(0) ) gl_FragColor.rgb+=vec3(0.05,0,0);
//    if ( floor( ((mid+rotje*2+vec2(-250, 0)*r2)/50.0) ) == vec2(0) ) gl_FragColor.rgb+=vec3(0.05,0,0);

//    if ( floor( ((mid+rotje*2+vec2( 250,  250)*r2)/40.0) ) == vec2(0) ) gl_FragColor.rgb-=vec3(0.25,0,0);
//    if ( floor( ((mid+rotje*2+vec2( -250,  350)*r2)/40.0) ) == vec2(0) ) gl_FragColor.rgb-=vec3(0.25,0,0);
//    if ( floor( ((mid+rotje*2+vec2( 350,  350)*r2)/40.0) ) == vec2(0) ) gl_FragColor.rgb-=vec3(0.25,0,0);
//    if ( floor( ((mid+rotje*2+vec2( 350,  -250)*r2)/40.0) ) == vec2(0) ) gl_FragColor.rgb-=vec3(0.25,0,0);
//    if ( floor( ((mid+rotje*2+vec2( 450,  -350)*r2)/40.0) ) == vec2(0) ) gl_FragColor.rgb-=vec3(0.25,0,0);

//}

//    if ( floor( ((mid+rotje+vec2(   0,  0)*r2)/2.0) ) == vec2(0) ) gl_FragColor.rgb=vec3(0.0);
//    if ( floor( ((mid+vec2(  170, 170))/120.0) ) == vec2(0) ) gl_FragColor.rgb=vec3(1.0);
//    if ( floor( ((mid+vec2(  -170, 170))/120.0) ) == vec2(0) ) gl_FragColor.rgb=vec3(1.0,0.0,0.0);
//    if ( floor( ((mid+vec2(     0, 170))/120.0) ) == vec2(0) ) gl_FragColor.rgb=vec3(0.0);

//    if ( floor( ((mid+vec2(  40, 40)*r3)/20.0) ) == vec2(0) ) gl_FragColor.rgb=(vec3(1.0)-gl_FragColor.rgb)*vec3(0.01)+gl_FragColor.rgb;
//    if ( floor( ((mid+rotje+vec2( 000,-200))/50.0) ) == vec2(0) ) gl_FragColor.rgb+=vec3(0.05,0.05,0.05);


    vec2 scr=vec2(0);
    float highlight=0.0;

    if (iFrame>=100) {
        scr=(gl_FragCoord.xy/Res.xy)*2.0-vec2(1.0);

//        int modje=int(mod((float(iFrame)-100.0)/250.0,2.0));
//        if (modje==0)            gl_FragColor.r += abs(0.07*scr.x / (dot(scr,scr)/0.03+0.3));
//        else if (modje==1)       gl_FragColor.r -= abs(0.5*scr.x / (dot(scr,scr)/0.005+0.03));
//        gl_FragColor.gb -= abs((0.14*scr.xy / (dot(scr,scr)/0.05+0.3)));


        int modje=int(mod((float(iFrame)-100.0)/50.0,7.0));
        highlight = cos(float(iFrame)/55.0) *0.08+0.014;


        if (sin(float(iFrame)/27.0) + sin(float(iFrame)/34.0) > 1.6) {
            if (modje==0)            gl_FragColor.rg -= abs(highlight*scr.xy / (dot(scr,scr)/0.05+0.3));
            else if (modje==1)       gl_FragColor.gb -= abs(highlight*scr.xy / (dot(scr,scr)/0.05+0.3));
            else if (modje==2)       gl_FragColor.br -= abs(highlight*scr.xy / (dot(scr,scr)/0.05+0.3));
            else if (modje==3)       gl_FragColor.rb += abs(highlight*scr.xy / (dot(scr,scr)/0.05+0.3));
            else if (modje==4)       gl_FragColor.bg += abs(highlight*scr.xy / (dot(scr,scr)/0.05+0.3));
            else if (modje==5)       gl_FragColor.gr += abs(highlight*scr.xy / (dot(scr,scr)/0.05+0.3));
        } else {
            if (modje==0)            gl_FragColor.rg += (highlight*scr.xy / (dot(scr,scr)/0.05+0.3));
            else if (modje==1)       gl_FragColor.gb += (highlight*scr.xy / (dot(scr,scr)/0.05+0.3));
            else if (modje==2)       gl_FragColor.br += (highlight*scr.xy / (dot(scr,scr)/0.05+0.3));
            else if (modje==3)       gl_FragColor.rb += (highlight*scr.xy / (dot(scr,scr)/0.05+0.3));
            else if (modje==4)       gl_FragColor.bg += (highlight*scr.xy / (dot(scr,scr)/0.05+0.3));
            else if (modje==5)       gl_FragColor.gr += (highlight*scr.xy / (dot(scr,scr)/0.05+0.3));
        }

    }

//}

    if (iFrame>=200) {
        int modje=int(mod((iFrame-200)/59.0,12.0));
        if (sin(float(iFrame)/23.0) + sin(float(iFrame)/33.0) > 1.6) {
            if (modje==0)            gl_FragColor.rg += abs(highlight*scr.xy / (dot(scr,scr)/0.05+0.3));
            else if (modje==2)       gl_FragColor.gb += abs(highlight*scr.xy / (dot(scr,scr)/0.05+0.3));
            else if (modje==4)       gl_FragColor.br += abs(highlight*scr.xy / (dot(scr,scr)/0.05+0.3));
            else if (modje==6)       gl_FragColor.rb -= abs(highlight*scr.xy / (dot(scr,scr)/0.05+0.3));
            else if (modje==8)       gl_FragColor.bg -= abs(highlight*scr.xy / (dot(scr,scr)/0.05+0.3));
            else if (modje==10)      gl_FragColor.gr -= abs(highlight*scr.xy / (dot(scr,scr)/0.05+0.3));
        } else {
            if (modje==0)            gl_FragColor.rg += (highlight*scr.xy / (dot(scr,scr)/0.05+0.3));
            else if (modje==2)       gl_FragColor.gb += (highlight*scr.xy / (dot(scr,scr)/0.05+0.3));
            else if (modje==4)       gl_FragColor.br += (highlight*scr.xy / (dot(scr,scr)/0.05+0.3));
            else if (modje==6)       gl_FragColor.rb += (highlight*scr.xy / (dot(scr,scr)/0.05+0.3));
            else if (modje==8)       gl_FragColor.bg += (highlight*scr.xy / (dot(scr,scr)/0.05+0.3));
            else if (modje==10)      gl_FragColor.gr += (highlight*scr.xy / (dot(scr,scr)/0.05+0.3));
        }
    }
    if (iMouse_on==1) {
        scr=((gl_FragCoord.xy/Res.xy));
        scr.y=1.0-scr.y;
//        float Circle=circle(scr,0.1,iMouse);
        float Circle=circle(scr,0.1,vec2(0.5));
        gl_FragColor+=vec4(iMouse.x*Circle,iMouse.y*Circle,0.0,0.0);
    }

//        gl_FragColor.xy += (0.01*scr.xy / (dot(scr,scr)/0.1+0.3));
}

//    if(iFrame<=4 || KEY_I>0.5) fragColor=texture(iChannel2,fragCoord.xy/Res.xy);
