//copy
precision highp float;
uniform sampler2D texture_in;
uniform sampler2D texture_buffer;
uniform vec2 pos_correction;
uniform int iMouse_on;
uniform vec2 iResolution;
uniform vec2 iMouse;
uniform float iTime;

// "Twisted Ladder" by dr2 - 2018
// License: Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License

float PrBox2Df (vec2 p, vec2 b);
float PrRoundCylDf (vec3 p, float r, float rt, float h);
vec2 Rot2D (vec2 q, float a);

vec3 qHit;
float dstFar;
int idObj;
const float pi = 3.14159;

#define DMINQ(id) if (d < dMin) { dMin = d;  idObj = id;  qHit = q; }

float ObjDf (vec3 p)
{
  vec3 q;
  float dMin, d, a, r, ns;
  r = 3.5;
  ns = 32.;
  dMin = dstFar;
  q = p;
  a = atan (q.z, q.x);
  q.xz = vec2 (length (q.xz) - r, q.y);
  q.xz = Rot2D (q.xz, 1.5 * a);
  q.xz = Rot2D (q.xz, - pi * (floor (atan (q.z, q.x) / pi + 0.5)));
  q.x -= 1.;
  d = length (PrBox2Df (q.xz, vec2 (0.3))) - 0.05;
  DMINQ (1);
  q = p;
  a = atan (q.z, - q.x) / (2. * pi);
  a = 2. * pi * (floor (ns * a) + 0.5) / ns;
  q.xz = Rot2D (q.xz, a);
  q.x += r;
  q.xy = Rot2D (q.xy, 1.5 * a);
  d = PrRoundCylDf (q.xzy, 0.2, 0.02, 1.45);
  DMINQ (2);
  return 0.4 * dMin;
}

float ObjRay (vec3 ro, vec3 rd)
{
  float dHit, d;
  dHit = 0.;
  for (int j = 0; j < 200; j ++) {
    d = ObjDf (ro + rd * dHit);
    if (d < 0.0002 || dHit > dstFar) break;
    dHit += d;
  }
  return dHit;
}

vec3 ObjNf (vec3 p)
{
  vec4 v;
  vec2 e = vec2 (0.0001, -0.0001);
  v = vec4 (ObjDf (p + e.xxx), ObjDf (p + e.xyy), ObjDf (p + e.yxy), ObjDf (p + e.yyx));
  return normalize (vec3 (v.x - v.y - v.z - v.w) + 2. * v.yzw);
}

vec3 BgCol (vec3 rd)
{
  return vec3 (0.6, 0.6, 1.) * (0.05 + 0.245 * (rd.y + 1.) * (rd.y + 1.));
}

vec4 ShowScene (vec3 ro, vec3 rd)
{
//  vec3 col, vn;
  vec3 vn;
  vec4 col;
  float dstObj;
  col=vec4(0,0,0,0);
//  col = BgCol (rd);
//  col = BgCol (rd);
  dstObj = ObjRay (ro, rd);
  if (dstObj < dstFar) {
    col.a=1.0;
    ro += dstObj * rd;
    vn = ObjNf (ro);
    if (dot (rd, vn) < -0.001) col.xyz = BgCol (reflect (rd, vn));
    if (idObj == 1) col.xyz *= vec3 (1., 1., 0.9) * (0.95 + 0.05 * cos (8. * pi * qHit.z));
    else if (idObj == 2) col.xyz *= vec3 (1., 0.9, 0.9) * mix (1., 0.95 +
       0.05 * cos (16. * atan (qHit.z, - qHit.x)), step (abs (qHit.y), 1.44));
  }
  return clamp (col, 0., 1.);
}

vec4 main2(vec2 fragCoord)
{
  mat3 vuMat;
  vec4 mPtr;
//  vec3 ro, rd, col;
  vec3 ro, rd;
  vec4 col;
  vec2 canvas, uv, uvs, ori, ca, sa;
  float el, az, zmFac;
  canvas = iResolution.xy;
  uv = 2. * (fragCoord.xy-pos_correction.xy) / canvas - 1.;
  uvs = uv;
  uv.x *= canvas.x / canvas.y;
  mPtr.xy = iMouse.xy;
  mPtr.xy = mPtr.xy / canvas - 0.5;
  az = 0.5 * pi;
  el = -0.3 * pi;
  if (mPtr.z > 0.) {
    az += 3. * pi * mPtr.x;
    el += pi * mPtr.y;
  }
  el = clamp (el, -0.5 * pi, 0.5 * pi);
  ori = vec2 (el, az);
  ca = cos (ori+vec2(iTime/20.0));
  sa = sin (ori+vec2(iTime/20.0));
  vuMat = mat3 (ca.y, 0., - sa.y, 0., 1., 0., sa.y, 0., ca.y) *
          mat3 (1., 0., 0., 0., ca.x, - sa.x, 0., sa.x, ca.x);
  ro = vuMat * vec3 (0., 0., -20.);
  zmFac = 4.8 - abs (el);
  rd = vuMat * normalize (vec3 (uv, zmFac));
  dstFar = 40.;

  col = ShowScene (ro, rd);
  uvs *= uvs * uvs;
  col.xyz *= mix (0.8, 1., pow (1. - 0.5 * length (uvs * uvs), 4.));

  return col;
}


void main() {
  gl_FragColor= main2(gl_FragCoord.xy);

//  gl_FragColor= (main2(gl_FragCoord.xy)*4 +
//                ( main2(gl_FragCoord.xy+vec2(-1,0)) + main2(gl_FragCoord.xy+vec2(0,-1)) + main2(gl_FragCoord.xy+vec2(1,0)) + main2(gl_FragCoord.xy+vec2(0,1)) )*2 +
//                 main2(gl_FragCoord.xy+vec2(-1,-1)) + main2(gl_FragCoord.xy+vec2(-1,1)) + main2(gl_FragCoord.xy+vec2(1,-1)) + main2(gl_FragCoord.xy+vec2(1,1)) )/16  ;
}


float PrBox2Df (vec2 p, vec2 b)
{
  vec2 d;
  d = abs (p) - b;
  return min (max (d.x, d.y), 0.) + length (max (d, 0.));
}

float PrRoundCylDf (vec3 p, float r, float rt, float h)
{
  float dxy, dz;
  dxy = length (p.xy) - r;
  dz = abs (p.z) - h;
  return min (min (max (dxy + rt, dz), max (dxy, dz + rt)), length (vec2 (dxy, dz) + rt) - rt);
}

vec2 Rot2D (vec2 q, float a)
{
  return q * cos (a) + q.yx * sin (a) * vec2 (-1., 1.);
}
