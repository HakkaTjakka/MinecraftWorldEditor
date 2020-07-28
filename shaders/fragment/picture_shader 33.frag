//shader 33 FLAME CUBE

uniform sampler2D texture_in;
uniform vec2 pos_correction;
uniform vec2 iResolution;
uniform vec2 iMouse;
uniform float iTime;
uniform vec2 pos_pacman;

float burn;

mat2 rot(float a)
{
    float s=sin(a), c=cos(a);
    return mat2(s, c, -c, s);
}

float map(vec3 p)
{
    float d = max(max(abs(p.x), abs(p.y)), abs(p.z)) - .5;
    burn = d;

    mat2 rm = rot(-iTime/3. + length(p));
    p.xy *= rm, p.zy *= rm;

    vec3 q = abs(p) - iTime;
    q = abs(q - round(q));

    rm = rot(iTime);
    q.xy *= rm, q.xz *= rm;

    d = min(d, min(min(length(q.xy), length(q.yz)), length(q.xz)) + .01);

    burn = pow(d - burn, 2.);

    return d;
}

void main()
{
    vec3 rd = normalize(vec3(2.*gl_FragCoord.xy-iResolution.xy, iResolution.y)),
         ro = vec2(0, -2).xxy;

    mat2 r1 = rot(iTime/4.), r2 = rot(iTime/2.);
    rd.xz *= r1, ro.xz *= r1, rd.yz *= r2, ro.yz *= r2;

    //rd += max(.0, -.5*map(ro)+.1) * normalize(texture(iChannel0, fragCoord/iResolution.x).xyz-.5);

    float t = .0, i = 30. * (1. - exp(-.2*iTime-.1));
    for(;i-->0.;)t += map(ro+rd*t) / 2.;

    gl_FragColor = vec4(1.-burn, 2.*exp(-t/4.-1.), exp(-t), 1);
}
