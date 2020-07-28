// smooth test
uniform sampler2D texture_in;
uniform vec2 pos_correction;
uniform vec2 txt_correction;
uniform vec2 txt_resolution;
uniform vec2 iResolution;
uniform vec2 i;
uniform float iTime;
uniform vec2 iMouse;
uniform float iRotate;
uniform vec2 iSubpixel;
uniform ivec2 texture_index;
uniform sampler2D texture_surround[4];


//const float ratio=iResolution.x/iResolution.y;

mat2 rotate(float a) {
	float c = cos(a);
	float s = sin(a);
	return mat2(c, s, -s, c);
//	return mat2(c*ratio, s*ratio, -s, c);
}

mat2 rotje=rotate(iTime*0.1);

vec4 getPix(vec2 uv) {
    int nText=int( mod(int(floor(uv.x+1.0))+texture_index.x+1,2)+mod(int(floor(uv.y+1.0))+texture_index.y+1,2)*2);

    return texture2D(  texture_surround[nText]  , fract(uv) );
}

void main( )
{
	const float pi=3.141592;
//	vec2 uv= (( gl_FragCoord.xy-txt_correction.xy-fract(subpixel.xy) )/iResolution.xy-0.5)*vec2(1.0,-1.0);

//	vec2 uv= (( gl_FragCoord.xy-pos_correction.xy+fract(subpixel.xy) )/iResolution.xy-0.5)*vec2(1.0,-1.0);

//	vec2 uv= (gl_FragCoord.xy-txt_correction.xy)/iResolution.xy*vec2(-1.0,1.0);

//	vec2 uv= (gl_FragCoord.xy-txt_correction.xy-fract(iSubpixel.xy))/iResolution.xy*vec2(-1.0,1.0);

//	vec2 uv= (gl_FragCoord.xy - txt_correction.xy + fract(iSubpixel.xy))/iResolution.xy*vec2(-1.0,1.0);

//	vec2 uv= (gl_FragCoord.xy - txt_correction.xy)/iResolution.xy*vec2(-1.0,1.0);

//	vec2 uv= (gl_FragCoord.xy - txt_correction.xy + fract(iSubpixel.xy))/iResolution.xy*vec2(-1.0,1.0);

//	vec2 uv= (gl_FragCoord.xy-pos_correction.xy)/iResolution.xy*vec2(1.0,-1.0);

//    gl_FragColor=getPix( rotate(iTime*0.01) * uv.xy + fract(subpixel.xy) );

//    gl_FragColor=getPix(uv.xy);

//	vec2 uv= (gl_FragCoord.xy - pos_correction.xy + fract(iSubpixel.xy))/iResolution.xy*vec2(-1.0,1.0);
	vec2 uv= (gl_FragCoord.xy - txt_correction.xy - fract(iSubpixel.xy))/iResolution.xy*vec2(-1.0,1.0);
//    gl_FragColor=texture2D(texture_in,uv.xy);
    gl_FragColor=getPix(  uv.xy  ) ;

//    gl_FragColor=texture2D(texture_in,fract(rotate(-iRotate)*uv.xy+fract(subpixel.xy)));

//    gl_FragColor=getPix( rotate(iTime*0.00)*uv.xy+fract(subpixel.xy) );
}
