#ifdef GL_ES
precision highp float;
#endif

uniform vec2  resolution;
uniform float time;

struct Collider
{
   uint  type;
   vec3  location;
   float size;
};

struct Collision
{
   float distance;
   vec3  deflection;
};

Collision iSphere(in vec3 ro, in vec3 rd, in Collider sph)
{
   // So, a Sphere centered at the origin has equation |xyz| = r
   //    meaning, |xyz|^2 = r^2, meaning <xyz, xyz> = r^2, now
   //    xyz = ro + t*rd, therefore |ro|^2 + t^2 + 2<ro, rd>t - r^2 = 0
   //    which is a quadratic equation, so:

   vec3 oc = ro - sph.location;
   float b = 2.0 * dot(oc, rd);
   float c = dot(oc, oc) - sph.size * sph.size;
   float h = b * b - 4.0 * c;

   if(h < 0.0) return Collision(-1.0, vec3(0.0, 0.0, 0.0));

   float distance = (-b -sqrt(h)) / 2.0;
   vec3  normal   = ((ro + distance * rd) - sph.location) / sph.size;

   return Collision(distance, normal);
}

Collision iBox(in vec3 ro, in vec3 rd, in Collider box)
{
    float buffer;
    float tmin = ((box.location.x - box.size) - ro.x) / rd.x;
    float tmax = ((box.location.x + box.size) - ro.x) / rd.x;

    if (tmin > tmax)
    {
       buffer = tmin;
       tmin  = tmax;
       tmax  = buffer;
    }

    float tymin = ((box.location.y - box.size) - ro.y) / rd.y;
    float tymax = ((box.location.y + box.size) - ro.y) / rd.y;

    if (tymin > tymax)
    {
       buffer = tymin;
       tymin  = tymax;
       tymax  = buffer;
    }

    if ((tmin > tymax) || (tymin > tmax))
        return Collision(-1.0, vec3(0.0, 0.0, 0.0));

    if (tymin > tmin)
        tmin = tymin;

    if (tymax < tmax)
        tmax = tymax;

    float tzmin = ((box.location.z - box.size) - ro.z) / rd.z;
    float tzmax = ((box.location.z + box.size) - ro.z) / rd.z;

    if (tzmin > tzmax)
    {
       buffer = tzmin;
       tzmin  = tzmax;
       tzmax  = buffer;
    }

    if ((tmin > tzmax) || (tzmin > tmax))
        return Collision(-1.0, vec3(0.0, 0.0, 0.0));

    if (tzmin > tmin)
        tmin = tzmin;

    if (tzmax < tmax)
        tmax = tzmax;

    return Collision(tmin, vec3(0.0, 0.0, 1.0));
}

Collision iPlane(in vec3 ro, in vec3 rd, in Collider pla)
{
   // Normal of an up facing y plane: 0.0, 1.0, 0.0
   // Equation of a y-aligned plane: y = 0 = ro.y + t*rd.y

   return Collision(-ro.y/rd.y, vec3(0.0, 1.0, 0.0));
}

int intersect(in vec3 ray_origin, in vec3 ray_direction, out Collision intersection)
{
   int   type;
   uint  count;
   bool  selector;
   uint  nearest;
   float interval;

   Collider  objects[4];
   Collision collisions[4];


   // Lets set up some test objects.
   objects[0] = Collider(1, vec3( 1.0,  1.0,  0.0), 1.0);
   objects[1] = Collider(1, vec3( 0.0,  5.0,  0.0), 1.0);
   objects[2] = Collider(2, vec3( 0.0,  1.0,  0.0), 1.0);
   objects[3] = Collider(3, vec3( 0.0, -1.0,  0.0), 1.0);

   // Lets move the first sphere in our object list.
   objects[0].location.x = 8.0 * cos(time);
   objects[0].location.z = 8.0 * sin(time);


   // For each of the objects in our objectlist, run an intersection test.
   for(count = 0; count < 4; count++)
   {
      switch(objects[count].type)
      {
         case 1: // Sphere Collider.
            collisions[count] = iSphere(ray_origin, ray_direction, objects[count]);
         break;

         case 2: // Box Collider.
            collisions[count] = iBox(ray_origin, ray_direction, objects[count]);
         break;

         case 3: // Plane Collider.
            collisions[count] = iPlane(ray_origin, ray_direction, objects[count]);
         break;
      }
   }

   // Set up our maximum draw distance.
   interval = 1000.0;

   // Since we are assuming everything is 100% opaque, find the nearest collision, if any.
   for(count = 0; count < 4; count++)
   {
      selector  = collisions[count].distance > 0.0;
      selector *= collisions[count].distance < interval;
      nearest   = selector ? count : nearest;
      interval  = selector ? collisions[count].distance : interval;
   }

   //if(!(nearest + 1))
   //{
      intersection.distance   = collisions[nearest].distance;
      intersection.deflection = collisions[nearest].deflection;
      type = objects[nearest].type;
   //}
   return type;
}

void main(void)
{
   // For the new input, we will need a list of objects to be displayed.
   // In this list, we must include each objects type, origin, orientation, size/scale.

   vec3 light = normalize(vec3(.57703));

   // uv are the pixel co-ordinates from 0 to 1.
   vec2 uv = (gl_FragCoord.xy/resolution.xy);

   // We generate a ray with origin ro and direction rd.
   vec3 ray_origin    = vec3(0, 1.0, 12.0);
   vec3 ray_direction = normalize(vec3((-1.0+2.0*uv) * vec2(1.78,1.0), -1.0));

   // We intersect the ray with the 3d scene.
   Collision intersection;
   int type = intersect(ray_origin, ray_direction, intersection);

   // We draw black by default.
   vec3 color = vec3(0.0);
   if(type == 1)
   {
      // If we hit a sphere
      float dif = dot(intersection.deflection, light);
      color = vec3(0.0, 0.0, 1.0) * dif;
   }
   else if(type == 2)
   {
      // If we hit a box.
      float dif = dot(intersection.deflection, light);
      color = vec3(0.0, 1.0, 0.0) * dif;
   }
   else if(type == 3)
   {
      // If we hit a plane.
      float dif = dot(intersection.deflection, light);
      color = vec3(1.0, 0.8, 0.6) * dif;
   }

   gl_FragColor = vec4(color, 1.0);
}
