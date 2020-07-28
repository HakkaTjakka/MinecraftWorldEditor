uniform sampler2D texture_in;
uniform vec2 pos_correction;		//given from program because of when plotting sprite over lots of textures, it changes position... so formula changes....so correction always centers sprite
uniform vec2 iResolution;
uniform vec2 iMouse;
uniform float iTime;

#ifdef GL_ES
precision mediump float;
#endif


void main() {
//    vec2 st = gl_FragCoord.xy / u_resolution.xy;
    vec2 st = (gl_FragCoord.xy-pos_correction.xy) / iResolution.xy;
    st.x *= iResolution.x / iResolution.y;
    st *= 5.0;
//    float r = cellular(st);
//    float b = cellular(st - vec2(0.0, sin(iTime * 0.5) * 0.5));
//    float r = (sin(st.x*0.3)+cos(st.y*1.72)+2.0)/4.0;
//    float g = (sin(st.y*2.1)+cos(st.x*0.66)+2.0)/4.0;
//    float b = (sin(st.x*1.9)+cos(st.y*1.99)+2.0)/4.0;
    float r = (sin(st.x*0.3-iTime*0.23)+cos(st.y*1.72+iTime*0.11+atan(st.x+st.y)*300)+2.0)/3.0;
    float g = (sin(st.y*2.1+iTime*0.54+atan(sin(st.x*.5+iTime*.6)/2-st.y/4)*200)+cos(-st.x*0.66-iTime*0.83+atan(sin(st.x*.5)/2-st.y/4)*200)+2.0)/3.0;
    float b = (sin(-st.x*1.9-iTime*0.75+atan(sin(st.y*.3+iTime*.8)/3+st.y/3.4)*200)+cos(st.y*1.99+iTime*0.52+atan(-st.x/3+cos(st.y)*.7/5)*150)+2.0)/3.0;
    r=r-floor(r+g);
    g=g-floor(g-b*2+2);
    b=b-floor(b+r);
    gl_FragColor = vec4(r, g, b, 1.0);
}
