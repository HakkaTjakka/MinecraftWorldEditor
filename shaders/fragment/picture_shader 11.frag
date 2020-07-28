//copy
//precision highp float;
uniform sampler2D texture_in;
uniform sampler2D texture_buffer;
uniform vec2 pos_correction;
uniform int iMouse_on;
uniform vec2 iResolution;
uniform vec2 iMouse;
uniform float iTime;
uniform int background_plot;

// License Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
// Created by S. Guillitte 2015

float zoom=1.;

vec2 cmul( vec2 a, vec2 b )  { return vec2( a.x*b.x - a.y*b.y, a.x*b.y + a.y*b.x ); }
vec2 csqr( vec2 a )  { return vec2( a.x*a.x - a.y*a.y, 2.*a.x*a.y  ); }


mat2 rot(float a) {
	return mat2(cos(a),sin(a),-sin(a),cos(a));
}

vec3 iSphere( in vec3 ro, in vec3 rd, in vec4 sph )//from iq
{
	vec3 oc = ro - sph.xyz;
	float b = dot( oc, rd );
	float c = dot( oc, oc ) - sph.w*sph.w;
	float h = b*b - c;
	if( h<0.0 ) return vec3(-1.0,-1.0,-b-h);
	h = sqrt(h);
	return vec3(-b-h, -b+h, h*h );
}

float map(in vec3 p) {

	float res = 0.;

    vec3 c = p;
	for (int i = 0; i < 10; ++i) {
        p =.7*abs(p)/dot(p,p) -.7;
        p.yz= csqr(p.yz);
        p=p.zxy;
        res += exp(-19. * abs(dot(p,c)));

	}
	return res/2.;
}



//vec3 raymarch( in vec3 ro, vec3 rd, vec2 tminmax )
vec4 raymarch( in vec3 ro, vec3 rd, vec2 tminmax )
{
    float t = tminmax.x;
//    float dt = .02;
    float dt = .02 - .0195*cos(iTime*.5);//animated
    vec4 col= vec4(0,0,0,1.0);
    float c = 0.;
    for( int i=0; i<64; i++ )
	{
        t+=dt*exp(-2.*c);
        if(t>tminmax.y)break;
//        vec3 pos = ro+t*rd;

        c = map(ro+t*rd);

//        col.xyz = .99*col.xyz+ .08*vec3(c*c, c, c*c*c);//green
//        col = .99*col+ .08*vec3(c*c*c, c*c, c);//blue
//        col = .99*col+ .08*vec3(c, c, c*c*c);//blue
        col.xyz = .99*col.xyz+ .08*vec3(c, c*c, c*c*c);//blue
    }
    return col;
}


vec4 main2(vec2 fragCoord )
{
	float time = iTime;
    vec2 q = (fragCoord.xy-pos_correction.xy) / iResolution.xy;
    vec2 p = -1.0 + 2.0 * q;
    p.x *= iResolution.x/iResolution.y;
    vec2 m = vec2(0.);
//	if( iMouse.z>0.0 )m = iMouse.xy/iResolution.xy*3.14;
    m-=.5;

    // camera

    vec3 ro = zoom*vec3(5.);
    ro.yz*=rot(m.y);
    ro.xz*=rot(m.x+ 0.1*time);
    vec3 ta = vec3( 0.0 , 0.0, 0.0 );
    vec3 ww = normalize( ta - ro );
    vec3 uu = normalize( cross(ww,vec3(0.0,1.0,0.0) ) );
    vec3 vv = normalize( cross(uu,ww));
    vec3 rd = normalize( p.x*uu + p.y*vv + 4.0*ww );

    vec3 tmm = iSphere( ro, rd, vec4(0.,0.,0.,2.) );

	// raymarch
    vec4 col = vec4(0,0,0,1.0);
//    if (tmm.x<0.) col = texture(texture_in, rd.xy).rgb;

    if (tmm.x<0.0) col = vec4(0);
    else {
//        col = vec4(raymarch(ro,rd,tmm),1.0);
        col.xyz = raymarch(ro,rd,tmm.xy).xyz;
        vec3 nor=(ro+tmm.x*rd)/2.;
        nor = reflect(rd, nor);
        float fre = pow(.5+ clamp(dot(nor,rd),0.0,1.0), 3. )*1.3;
        col.xyz += texture(texture_buffer, nor.xy).rgb * fre;
//        if (tmm.x<0.2) col.a = 1.0-tmm.x*5;
//        col.xyz=vec3(1.0-tmm.z*1.0);
        col.a=max(length(col.xyz),clamp(tmm.z*10.0*iResolution.x/1920.0,0,1));
//        col.xyz=col.xyz*(2.0+col.a);
    }

	// shade

    col.xyz =  .5 *(log(1.+col.xyz));
    col = clamp(col,0.,1.);
    return col;
}


void main() {
  gl_FragColor= main2(gl_FragCoord.xy);

//  vec4 background=texture(texture_in,(gl_FragCoord.xy/vec2(1920,1080)));

//  float tussen=gl_FragColor.g;
//  gl_FragColor.g=gl_FragColor.b;
//  gl_FragColor.b=1.0-gl_FragColor.g;
//  gl_FragColor.r=0.5+gl_FragColor.b/2.0;
//    gl_FragColor.r=(gl_FragColor.g+gl_FragColor.b)/2.0;

//  gl_FragColor= (main2(gl_FragCoord.xy)*4 +
//                (main2(gl_FragCoord.xy+vec2(-1,0)) + main2(gl_FragCoord.xy+vec2(0,-1)) + main2(gl_FragCoord.xy+vec2(1,0)) + main2(gl_FragCoord.xy+vec2(0,1)) )*2 +
//                 main2(gl_FragCoord.xy+vec2(-1,-1)) + main2(gl_FragCoord.xy+vec2(-1,1)) + main2(gl_FragCoord.xy+vec2(1,-1)) + main2(gl_FragCoord.xy+vec2(1,1)) )/16  ;

//	gl_FragColor = mix(gl_FragColor,background,background.a);

    if (background_plot==1) {
        vec4 background=texture(texture_in,(gl_FragCoord.xy/vec2(1920,1080)));
        gl_FragColor = mix(gl_FragColor,background,background.a);
    }
}


