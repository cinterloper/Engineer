#ifdef GL_ES
precision highp float;
#endif

uniform vec2  resolution;
uniform float time;

float iBox(in vec3 ro, in vec3 rd, in vec4 box)
{
    float buffer;
    float tmin = ((box.x - box.w) - ro.x) / rd.x;
    float tmax = ((box.x + box.w) - ro.x) / rd.x;

    if (tmin > tmax)
    {
       buffer = tmin;
       tmin  = tmax;
       tmax  = buffer;
    }

    float tymin = ((box.y - box.w) - ro.y) / rd.y;
    float tymax = ((box.y + box.w) - ro.y) / rd.y;

    if (tymin > tymax)
    {
       buffer = tymin;
       tymin  = tymax;
       tymax  = buffer;
    }

    if ((tmin > tymax) || (tymin > tmax))
        return -1.0;

    if (tymin > tmin)
        tmin = tymin;

    if (tymax < tmax)
        tmax = tymax;

    float tzmin = ((box.y - box.w) - ro.z) / rd.z;
    float tzmax = ((box.y + box.w) - ro.z) / rd.z;

    if (tzmin > tzmax)
    {
       buffer = tzmin;
       tzmin  = tzmax;
       tzmax  = buffer;
    }

    if ((tmin > tzmax) || (tzmin > tmax))
        return -1.0;

    if (tzmin > tmin)
        tmin = tzmin;

    if (tzmax < tmax)
        tmax = tzmax;

    return tmin;
}

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

float iPlane(in vec3 ro, in vec3 rd, in vec4 pla)
{
   // Equation of a y-aligned plane: y = 0 = ro.y + t*rd.y
   return -ro.y/rd.y;
}

vec3 nPlane(in vec3 pos, in vec4 pla)
{
   return vec3(0.0, 1.0, 0.0);
}

vec4 sph1 = vec4(0.0,  1.0, -1.0,  1.0);
vec4 sph2 = vec4(0.0,  5.0,  0.0,  1.0);
vec4 box1 = vec4(0.0,  1.0,  0.0,  1.0);
vec4 pla1 = vec4(0.0, -1.0,  0.0,  1.0);
float intersect(in vec3 ro, in vec3 rd, out float resT)
{
   resT = 1000.0;
   float id = -1.0;

   float tpla  = iPlane(ro, rd, pla1);  // Intersect with a plane.
   float tsph1 = iSphere(ro, rd, sph1); // Intersect with a sphere.
   float tsph2 = iSphere(ro, rd, sph2);
   float tbox1 = iBox(ro, rd, box1);

   if(tsph1 > 0.0 && tsph1 > tbox1)
   {
      if(tsph2 > 0.0)
      {
         id = 2.0;
         resT = tsph2;
      }
      else if(tbox1 > 0.0)
      {
         id = 4.0;
         resT = tbox1;
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
      else if(tbox1 > 0.0)
      {
         id = 4.0;
         resT = tbox1;
      }
      else if(tpla > 0.0 && tpla < resT)
      {
         id = 3.0;
         resT = tpla;
      }
   }
   return id;
}

void main(void)
{
   // For the new input, we will need a list of objects to be displayed.
   // In this list, we must include each objects type, origin, orientation, size/scale.

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
   vec3 color = vec3(0.0);
   if(id == 1.0)
   {
      // If we hit the sphere
      vec3 pos  = rorigin + t*rdirection;
      vec3 nor  = nSphere(pos, sph1);
      float dif = clamp(dot(nor, light), 0.0, 1.0);
      color = vec3(0.0, 0.0, 1.0)*dif;
   }
   if(id == 2.0)
   {
      // If we hit the sphere
      vec3 pos  = rorigin + t*rdirection;
      vec3 nor  = nSphere(pos, sph2);
      float dif = clamp(dot(nor, light), 0.0, 1.0);
      color = vec3(0.0, 1.0, 1.0)*dif;
   }

   if(id == 3.0)
   {
      // If we hit the plane.
      vec3 pos  = rorigin + t*rdirection;
      vec3 nor  = nPlane(pos, pla1);
      float dif = clamp(dot(nor, light), 0.0, 1.0);
      color = vec3(1.0, 0.8, 0.6)*dif;

   }

   if(id == 4.0)
   {
      // If we hit the box.
      color = vec3(0.0, 1.0, 0.0);
   }

   gl_FragColor = vec4(color, 1.0);
}
