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
uniform float iTime;
uniform int iFrame;
uniform int background_plot;
uniform int buffer_plot;
uniform vec2 pos_abs;
uniform int formula;
uniform float iRotate;
#define PI 3.141592653589793

vec4 GetPix_multi(vec2 uv) {
    int nText=int(floor(uv.x+1.0)+floor(uv.y+1.0)*3.0);
    return texture(  texture_surround[nText]  , fract(uv) );
}
//          1
//        1 2 1
//      1 2 4 2 1
//        1 2 1
//          1
vec4 AA_multi(vec2 uv, vec2 delta)
{
    vec4 col=vec4(0.0);
    col+=GetPix_multi(uv)*4.0;
    col+=GetPix_multi(uv+vec2(delta.x,0.0)        )*2.0;
    col+=GetPix_multi(uv+vec2(-delta.x,0.0)       )*2.0;
    col+=GetPix_multi(uv+vec2(0.0,delta.y)        )*2.0;
    col+=GetPix_multi(uv+vec2(0.0,-delta.y)       )*2.0;
    col+=GetPix_multi(uv+vec2(delta.x,delta.y)    );
    col+=GetPix_multi(uv+vec2(-delta.x,delta.y)   );
    col+=GetPix_multi(uv+vec2(delta.x,-delta.y)   );
    col+=GetPix_multi(uv+vec2(-delta.x,-delta.y)  );
    delta*=2.0;
    col+=GetPix_multi(uv+vec2(delta.x,0.0)        );
    col+=GetPix_multi(uv+vec2(-delta.x,0.0)       );
    col+=GetPix_multi(uv+vec2(0.0,delta.y)        );
    col+=GetPix_multi(uv+vec2(0.0,-delta.y)       );

    col=col/20.0;
    return col;
}

vec4 getPix_one(vec2 uv)
{
    return texture(texture_in,uv);
}

vec4 AA_one(sampler2D the_texture, vec2 uv, vec2 delta)
{
    vec4 col=vec4(0.0);
    col+=texture(the_texture,uv)*4.0;
    col+=texture(the_texture,uv+vec2(delta.x,0.0)        )*2.0;
    col+=texture(the_texture,uv+vec2(-delta.x,0.0)       )*2.0;
    col+=texture(the_texture,uv+vec2(0.0,delta.y)        )*2.0;
    col+=texture(the_texture,uv+vec2(0.0,-delta.y)       )*2.0;
    col+=texture(the_texture,uv+vec2(delta.x,delta.y)    );
    col+=texture(the_texture,uv+vec2(-delta.x,delta.y)   );
    col+=texture(the_texture,uv+vec2(delta.x,-delta.y)   );
    col+=texture(the_texture,uv+vec2(-delta.x,-delta.y)  );
    delta*=2.0;
    col+=texture(the_texture,uv+vec2(delta.x,0.0)        );
    col+=texture(the_texture,uv+vec2(-delta.x,0.0)       );
    col+=texture(the_texture,uv+vec2(0.0,delta.y)        );
    col+=texture(the_texture,uv+vec2(0.0,-delta.y)       );

    col=col/20.0;
    return col;
}

float getVal_multi(vec2 uv) {
    int nText=int(floor(uv.x+1.0)+floor(uv.y+1.0)*3.0);
    return length(texture(texture_surround[nText]  , fract(uv) ).xyz);
}

vec2 getGrad_multi(vec2 uv,vec2 delta) {

     return vec2( getVal_multi(uv+vec2(delta.x,0)) - getVal_multi(uv-vec2(delta.x,0)) , getVal_multi(uv+vec2(0,delta.y)) - getVal_multi(uv-vec2(0,delta.y)) )/delta;
}

float getVal_one(sampler2D the_texture,vec2 uv)
{
    return length( texture(the_texture,uv).xyz);
}

vec2 getGrad_one(sampler2D the_texture,vec2 uv,vec2 delta) {

     return vec2(  getVal_one(the_texture,uv+vec2(delta.x,0)) - getVal_one(the_texture,uv-vec2(delta.x,0)) , getVal_one(the_texture,uv+vec2(0,delta.y)) - getVal_one(the_texture,uv-vec2(0,delta.y)) )/delta;
}


float getVal_super_multi(vec2 uv, vec2 delta)  // multi means 8 surrounding textures are in uniform. (see getpix_multi)
{
//    return length(texture(texture_buffer,uv).xyz);
    vec3 col=vec3(0.0);
    col+=GetPix_multi(uv).xyz*4.0;
    col+=GetPix_multi(uv+vec2(delta.x,0.0)        ).xyz*2.0;
    col+=GetPix_multi(uv+vec2(-delta.x,0.0)       ).xyz*2.0;
    col+=GetPix_multi(uv+vec2(0.0,delta.y)        ).xyz*2.0;
    col+=GetPix_multi(uv+vec2(0.0,-delta.y)       ).xyz*2.0;
    col+=GetPix_multi(uv+vec2(delta.x,delta.y)    ).xyz;
    col+=GetPix_multi(uv+vec2(-delta.x,delta.y)   ).xyz;
    col+=GetPix_multi(uv+vec2(delta.x,-delta.y)   ).xyz;
    col+=GetPix_multi(uv+vec2(-delta.x,-delta.y)  ).xyz;
    delta*=2.0;
    col+=GetPix_multi(uv+vec2(delta.x,0.0)        ).xyz;
    col+=GetPix_multi(uv+vec2(-delta.x,0.0)       ).xyz;
    col+=GetPix_multi(uv+vec2(0.0,delta.y)        ).xyz;
    col+=GetPix_multi(uv+vec2(0.0,-delta.y)       ).xyz;

    col=col/20.0;
    return length(col);
}

float getVal_super(sampler2D the_texture, vec2 uv, vec2 delta)
{
//    return length(texture(texture_buffer,uv).xyz);
    vec3 col=vec3(0.0);
    col+=texture(the_texture,uv).xyz*4.0;
    col+=texture(the_texture,uv+vec2(delta.x,0.0)        ).xyz*2.0;
    col+=texture(the_texture,uv+vec2(-delta.x,0.0)       ).xyz*2.0;
    col+=texture(the_texture,uv+vec2(0.0,delta.y)        ).xyz*2.0;
    col+=texture(the_texture,uv+vec2(0.0,-delta.y)       ).xyz*2.0;
    col+=texture(the_texture,uv+vec2(delta.x,delta.y)    ).xyz;
    col+=texture(the_texture,uv+vec2(-delta.x,delta.y)   ).xyz;
    col+=texture(the_texture,uv+vec2(delta.x,-delta.y)   ).xyz;
    col+=texture(the_texture,uv+vec2(-delta.x,-delta.y)  ).xyz;
    delta*=2.0;
    col+=texture(the_texture,uv+vec2(delta.x,0.0)        ).xyz;
    col+=texture(the_texture,uv+vec2(-delta.x,0.0)       ).xyz;
    col+=texture(the_texture,uv+vec2(0.0,delta.y)        ).xyz;
    col+=texture(the_texture,uv+vec2(0.0,-delta.y)       ).xyz;
    col=col/20.0;
    return length(col);
}
vec2 getGrad_super(sampler2D the_texture,vec2 uv,vec2 delta) {

     return vec2(  getVal_super(the_texture,uv+vec2(delta.x,0),delta) - getVal_super(the_texture,uv-vec2(delta.x,0),delta) , getVal_super(the_texture,uv+vec2(0,delta.y),delta) - getVal_super(the_texture,uv-vec2(0,delta.y),delta) )/delta;
}

vec2 getGrad_super_multi(vec2 uv,vec2 delta) {

     return vec2(  getVal_super_multi(uv+vec2(delta.x,0),delta) - getVal_super_multi(uv-vec2(delta.x,0),delta) , getVal_super_multi(uv+vec2(0,delta.y),delta) - getVal_super_multi(uv-vec2(0,delta.y),delta) )/delta;
}

mat2 rotate(float a) {
	float c = cos(a);
	float s = sin(a);
	return mat2(c, s, -s, c);
}


//GRADATION
void main_Grad( )
//void main()
{
    vec4 kS = vec4(.7, .5, .9, 1.0);
    vec4 kA = vec4(0.0, .0, .0, 1.0);
    vec4 kD;
    vec3 light=vec3(1.5, 1.5, -5.0); // zzzzz 2.0
    vec3 ro = vec3(0.0,0.0, -1.0);
    vec2 uv;
    vec3 n;

    if (formula==2 && background_plot==1 ) {         //dont use....formula=2 on this one.
        uv = rotate(iRotate)*((gl_FragCoord.xy) / vec2(1920,1080));
        kD = texture(texture_in,uv);
//        n = vec3(getGrad_super(texture_in,uv,1.0/vec2(1920,1080)),-150.0);    //get from texture_in
        n = vec3(getGrad_super_multi(uv,1.0/vec2(1920,1080)),-150.0);           //get from 9 textures uniform.
//        n = vec3(getGrad_super_multi(uv,1.0/vec2(1920,1080)),-150.0);
    } else  if ((formula==1 || formula==3) && background_plot==1 ) {
        if (buffer_plot==1) {
            uv = rotate(iRotate)*((gl_FragCoord.xy-pos_correction.xy) / iResolution.xy);
            kD = texture(texture_buffer,uv);
            n = vec3(getGrad_super(texture_buffer,uv,1.0/iResolution_buffer.xy),-150.0);
        } else {
//            uv =(gl_FragCoord.xy-pos_correction.xy) / iResolution.xy;
            uv = rotate(iRotate)*(vec2(1.0,-1.0)*(gl_FragCoord.xy-pos_correction.xy) / iResolution.xy);
            kD = texture(texture_buffer,uv);            //from picture. texture_in is bitmap screen.
            n = vec3(getGrad_super(texture_buffer,uv,1.0/iResolution_buffer),-150.0);  // iResolution is total screen size (BITMAPSX x 1920,BITMAPSY * 1080).
//            n = vec3(getGrad_super(texture_buffer,uv,1.0/vec2(1920,1080)),-150.0);  // iResolution is total screen size (BITMAPSX x 1920,BITMAPSY * 1080).
//            n = vec3(getGrad_super(texture_buffer,uv,1.0/iResolution.xy),-150.0);
        }
    } else {
        if (buffer_plot==1) {
            uv = rotate(iRotate)*((gl_FragCoord.xy-pos_correction.xy) / iResolution.xy);
            kD = texture(texture_buffer,uv);
            n = vec3(getGrad_super(texture_buffer,uv,1.0/iResolution_buffer.xy),-150.0);
        } else {
//            uv =(gl_FragCoord.xy-pos_correction.xy) / iResolution.xy;
            uv = (vec2(1.0,-1.0)*(rotate(iRotate)*(gl_FragCoord.xy-pos_correction.xy)) / iResolution.xy);
            kD = texture(texture_in,uv);
            n = vec3(getGrad_super(texture_in,uv,1.0/vec2(1920,1080)),-150.0);
        }
    }
    n=normalize(n);
    vec3 lp = normalize(light );
    float diff = 1.2 * clamp(dot( n,lp), 0.0, 1.);
    float spec = (2.5) * pow(max(dot(reflect(-lp, n), ro), 0.), 120.);
//    gl_FragColor = clamp(   vec4(kA + kD.xyz * (diff ) + kS * ( spec ), 1.0) , 0.0 , 1.0);

    gl_FragColor = clamp(   kA + kD * (diff ) + kS * ( spec ) , 0.0 , 1.0);
//    gl_FragColor = clamp(   kA + kD * (diff )  , 0.0 , 1.0);
    if (background_plot==1 && formula!=2) {
        vec4 background=texture(texture_in,(gl_FragCoord.xy/vec2(1920,1080)));
//        gl_FragColor = mix(gl_FragColor,background,background.a);
    }
}

//COPY
void main_copy()
//void main()
{
//    if (background_plot==1) {
//        vec4 background=texture(texture_in,(gl_FragCoord.xy/vec2(1920,1080)));
//        gl_FragColor = mix(gl_FragColor,background,background.a);
//    }

    if (background_plot==1) {
        vec2 uv = vec2(1.0,-1.0)*(gl_FragCoord.xy-pos_correction.xy) /iResolution.xy;
        gl_FragColor = texture(texture_buffer,uv);   // from picture
        vec4 background=texture(texture_in,(gl_FragCoord.xy/vec2(1920,1080)));
        gl_FragColor = mix(gl_FragColor,background,background.a);           // back/front plotting.
    } else {
        vec2 uv = vec2(1.0,-1.0)*(gl_FragCoord.xy-pos_correction.xy) / iResolution.xy;   //just copy and show. (Do nothing, maybe smooth blur when drawing?)
        gl_FragColor = texture(texture_in,uv);
    }
}
//ANTI ALIASING
//void main()
void main_aa()
{
    if (formula==2 && background_plot==1 ) {
        vec2 uv = (gl_FragCoord.xy) / vec2(1920,1080);
        gl_FragColor = AA_multi(uv,1.0/vec2(1920,1080));
    } else  if ((formula==1 || formula==3) && background_plot==1 ) {
        vec2 uv = vec2(1.0,-1.0)*(gl_FragCoord.xy-pos_correction.xy) / iResolution.xy;
        gl_FragColor = AA_one(texture_buffer,uv,1.0/iResolution_buffer.xy); // iResolution_buffer = size picture. iResolution = size picture * scale . We need picture pixels, not screen pixels.
    } else {
        vec2 uv = vec2(1.0,-1.0)*(gl_FragCoord.xy-pos_correction.xy) / iResolution.xy;
        gl_FragColor = AA_one(texture_in,uv,1.0/iResolution_buffer.xy); // iResolution_buffer = size picture. iResolution = size picture * scale . We need picture pixels, not screen pixels.???
    }
}

void main() {
    main_Grad();
//    main_aa();
//    main_aa();
//    main_aa();
//    main_copy();
//    if (background_plot==1) {
//        vec4 background=texture(texture_in,(gl_FragCoord.xy/vec2(1920,1080)));
//        gl_FragColor = mix(gl_FragColor,background,background.a);
//    }
}
