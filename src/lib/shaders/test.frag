//#version 130

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
   vec3  color;
};

struct Collision
{
   int   subject;
   float distance;
   vec3  deflection;
};

Collision iSphere(in vec3 ray_origin, in vec3 ray_direction, in Collider sph)
{
   vec3 oc = ray_origin - sph.location;
   float b = 2.0 * dot(oc, ray_direction);
   float c = dot(oc, oc) - sph.size * sph.size;
   float h = b * b - 4.0 * c;

   if(h < 0.0) return Collision(-1, -1.0, vec3(0.0, 0.0, 0.0));

   float distance = (-b -sqrt(h)) / 2.0;
   vec3  normal   = ((ray_origin + distance * ray_direction) - sph.location) / sph.size;

   return Collision(-1, distance, normal);
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
        return Collision(-1, -1.0, vec3(0.0, 0.0, 0.0));

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
        return Collision(-1, -1.0, vec3(0.0, 0.0, 0.0));

    if (tzmin > tmin)
        tmin = tzmin;

    if (tzmax < tmax)
        tmax = tzmax;

    return Collision(-1, tmin, vec3(0.0, 0.0, 1.0));
}

Collision iPlane(in vec3 ro, in vec3 rd, in Collider pla)
{
   // Normal of an up facing y plane: 0.0, 1.0, 0.0
   // Equation of a y-aligned plane: y = 0 = ro.y + t*rd.y

   return Collision(-1, -ro.y/rd.y, vec3(0.0, 1.0, 0.0));
}

Collision
intersect(in vec3 ray_origin, in vec3 ray_direction, in Collider objects[])
{
   Collision tests[4];
   int       type;
   uint      count;
   bool      selector;
   uint      nearest;
   float     interval;

   // For each of our objects, run an intersection test.
   for(count = 0; count < 4; count++)
   {
      switch(objects[count].type)
      {
         case 1: // Sphere Collider.
            tests[count] = iSphere(ray_origin, ray_direction, objects[count]);
         break;

         case 2: // Box Collider.
            tests[count] = iBox(ray_origin, ray_direction, objects[count]);
         break;

         case 3: // Plane Collider.
            tests[count] = iPlane(ray_origin, ray_direction, objects[count]);
         break;
      }
   }

   // Set up our maximum draw distance.
   interval = 1000.0;

   // Since we are presuming everything is 100% opaque, find the nearest collision, if any.
   for(count = 0; count < 4; count++)
   {
      selector  = tests[count].distance > 0.0;
      selector *= tests[count].distance < interval;
      nearest   = selector ? count : nearest;
      interval  = selector ? tests[count].distance : interval;
   }

   if(interval == 10000.0) return Collision(-1, -1.0, vec3(0.0, 0.0, 0.0));

   tests[nearest].subject = nearest;
   return tests[nearest];
}

void main(void)
{
   // For the new input, we will need a list of objects to be displayed.
   // In this list, we must include each objects type, origin, orientation, size/scale.
   // Lets set up some test objects.
   Collider objects[4];
   objects[0] = Collider(1, vec3( 1.0,  1.0,  0.0), 1.0, vec3(0.0, 1.0, 1.0));
   objects[1] = Collider(1, vec3( 0.0,  5.0,  0.0), 1.0, vec3(0.0, 0.0, 1.0));
   objects[2] = Collider(2, vec3( 0.0,  1.0,  0.0), 1.0, vec3(0.0, 1.0, 0.0));
   objects[3] = Collider(3, vec3( 0.0, -1.0,  0.0), 1.0, vec3(1.0, 0.8, 0.6));

   // Lets move the first sphere in our object list.
   objects[0].location.x = 8.0 * cos(time);
   objects[0].location.z = 8.0 * sin(time);

   // Some constant light from a constant direction for all objects, no shadows yet.
   vec3 light_direction = normalize(vec3(.57703));

   // uv are the pixel co-ordinates from 0 to 1.
   vec2 uv = (gl_FragCoord.xy/resolution.xy);

   // We generate a ray with origin ro and direction rd.
   vec3 ray_origin    = vec3(0, 1.0, 12.0);
   vec3 ray_direction = normalize(vec3((-1.0+2.0*uv) * vec2(1.78,1.0), -1.0));

   // We intersect the ray with the 3d scene.
   Collision collision = intersect(ray_origin, ray_direction, objects);

   // We draw black by default.
   vec3 pixel = vec3(0.0);

   if(collision.subject > -1)
   {
      // Apply our object color to the pixel.
      pixel = objects[collision.subject].color;

      // Apply some simple lighting to our object surfaces.
      pixel *= dot(collision.deflection, light_direction);
   }

   gl_FragColor = vec4(pixel, 1.0);
}
