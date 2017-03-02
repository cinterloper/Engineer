#ifdef GL_ES
precision highp float;
#endif

uniform vec2  resolution;
uniform float time;

float iSphere(in vec3 ro, in vec3 rd, in vec4 sph)
{
   // So, a Sphere centered at the origin has equation |xyz| = r
   //    meaning, |xyz|^2 = r^2, meaning <xyz, xyz> = r^2, now
   //    xyz = ro + t*rd, therefore |ro|^2 + t^2 + 2<ro, rd>t - r^2 = 0
   //    which is a quadratic equation, so:
   vec3 oc = ro - sph.xyz;
   float b = 2.0*dot(oc, rd);
   float c = dot(oc, oc) - sph.w*sph.w;
   float h = b*b - 4.0*c;

   if(h < 0.0) return -1.0;
   float t = (-b -sqrt(h))/2.0;
   return t;
}

vec3 nSphere(in vec3 pos, in vec4 sph)
{
   return (pos - sph.xyz)/sph.w;
}

float iPlane(in vec3 ro, in vec3 rd)
{
   // Equation of a plane: y = 0 = ro.y + t*rd.y
   return -ro.y/rd.y;
}

vec3 nPlane(in vec3 pos)
{
   return vec3(0.0, 1.0, 0.0);
}

vec4 sph1 = vec4(0.0, 1.0, -1.0, 1.0);
vec4 sph2 = vec4(0.0, 1.0,  0.0, 1.0);
float intersect(in vec3 ro, in vec3 rd, out float resT)
{
   resT = 1000.0;
   float id   = -1.0;

   float tpla  = iPlane(ro, rd);        // Intersect with a plane.
   float tsph1 = iSphere(ro, rd, sph1); // Intersect with a sphere.
   float tsph2 = iSphere(ro, rd, sph2);

   if(tsph1 > 0.0 && tsph1 < tsph2)
   {
      if(tsph1 > 0.0)
      {
         id = 1.0;
         resT = tsph1;
      }
      else if(tsph2 > 0.0)
      {
         id = 2.0;
         resT = tsph2;
      }
      else if(tpla > 0.0 && tpla < resT)
      {
         id = 3.0;
         resT = tpla;
      }
   }
   else
   {
      if(tsph2 > 0.0)
      {
         id = 2.0;
         resT = tsph2;
      }
      else if(tsph1 > 0.0)
      {
         id = 1.0;
         resT = tsph1;
      }
      else if(tpla > 0.0 && tpla < resT)
      {
         id = 3.0;
         resT = tpla;
      }
   }
   return id;
}

void main( void )
{
   vec3 light = normalize(vec3(.57703));

   // uv are the pixel co-ordinates from 0 to 1.
   vec2 uv = (gl_FragCoord.xy/resolution.xy);

   // Lets move that sphere.
   sph1.x = 8.0 * cos(time);
   sph1.z = 8.0 * sin(time);

   // We generate a ray with origin ro and direction rd.
   vec3 rorigin = vec3(0, 1.0, 12.0);
   vec3 rdirection = normalize(vec3((-1.0+2.0*uv) * vec2(1.78,1.0), -1.0));

   // We intersect the ray with the 3d scene.
   float t;
   float id = intersect(rorigin, rdirection, t);

   // We draw black by default.
   vec3 col = vec3(0.0);
   if(id == 1.0)
   {
      // If we hit the sphere
      vec3 pos = rorigin + t*rdirection;
      vec3 nor = nSphere(pos, sph1);
      float dif = clamp(dot(nor, light), 0.0, 1.0);
      col = vec3(0.0, 0.0, 1.0)*dif;
   }
   if(id == 2.0)
   {
      // If we hit the sphere
      vec3 pos = rorigin + t*rdirection;
      vec3 nor = nSphere(pos, sph2);
      float dif = clamp(dot(nor, light), 0.0, 1.0);
      col = vec3(0.0, 1.0, 1.0)*dif;
   }

   if(id == 3.0)
   {
      // If we hit the plane.
      vec3 pos = rorigin + t*rdirection;
      vec3 nor = nPlane(pos);
      float dif = clamp(dot(nor, light), 0.0, 1.0);
      col = vec3(1.0, 0.8, 0.6)*dif;

   }

   gl_FragColor = vec4(col, 1.0);
}
