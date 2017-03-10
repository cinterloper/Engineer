#version 310 es

#ifdef GL_ES
precision highp float;
#endif

#define MISS Collision(-1, -1.0, vec3(0.0, 0.0, 0.0))

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

struct Ray
{
   vec3 inverse;
   vec3 signs;
};

layout (std430, binding = 0) buffer shader_data // Not used yet.
{
   Collider objects[];
};

uniform vec2      resolution;
uniform float     time;

out vec4 FragColor;

Collision iSphere(in vec3 ray_origin, in vec3 ray_direction, in Collider sphere)
{
   vec3 oc = ray_origin - sphere.location;
   float b = 2.0 * dot(oc, ray_direction);
   float c = dot(oc, oc) - sphere.size * sphere.size;
   float h = b * b - 4.0 * c;

   if(h < 0.0) return Collision(-1, -1.0, vec3(0.0, 0.0, 0.0));

   float distance = (-b -sqrt(h)) / 2.0;
   vec3  normal   = ((ray_origin + distance * ray_direction) - sphere.location) / sphere.size;

   return Collision(-1, distance, normal);
}

Collision iBox(in vec3 ray_origin, in vec3 ray_direction, in Collider box)
{
    float tmin, tmax, tymin, tymax, tzmin, tzmax;
    vec3 inverse, sign;

    inverse = vec3(1.0) / ray_direction;
    sign.x  = float(inverse.x >= 0.0) * 2.0 - 1.0;
    sign.y  = float(inverse.y >= 0.0) * 2.0 - 1.0;
    sign.z  = float(inverse.z >= 0.0) * 2.0 - 1.0;

    tmin  = ((box.location.x - (box.size * sign.x)) - ray_origin.x) * inverse.x;
    tmax  = ((box.location.x + (box.size * sign.x)) - ray_origin.x) * inverse.x;

    tymin = ((box.location.y - (box.size * sign.y)) - ray_origin.y) * inverse.y;
    tymax = ((box.location.y + (box.size * sign.y)) - ray_origin.y) * inverse.y;

    if ((tmin > tymax) || (tymin > tmax))
        return MISS;
    if (tymin > tmin)
        tmin = tymin;
    if (tymax < tmax)
        tmax = tymax;

    tzmin = ((box.location.z - (box.size * sign.z)) - ray_origin.z) * inverse.z;
    tzmax = ((box.location.z + (box.size * sign.z)) - ray_origin.z) * inverse.z;

    if ((tmin > tzmax) || (tzmin > tmax))
        return MISS;
    if (tzmin > tmin)
        tmin = tzmin;
    if (tzmax < tmax)
        tmax = tzmax;

    return Collision(-1, tmin, vec3(0.0, 0.0, 1.0));
}

Collision iPlane(in vec3 ray_origin, in vec3 ray_direction, in Collider pla)
{
   // Normal of an up facing y plane: 0.0, 1.0, 0.0
   // Equation of a y-aligned plane: y = 0 = ro.y + t*rd.y
   // Normal of a camera facing z plane: 0.0, 0.0, 1.0;

   return Collision(-1, -ray_origin.y/ray_direction.y, vec3(0.0, 1.0, 0.0));
}

Collision
intersect(in vec3 ray_origin, in vec3 ray_direction, in Collider object[4]) // in Collider object[4]
{
   Collision tests[4];
   int       type;
   int       count;
   bool      selector;
   int       nearest;
   float     interval;

   // For each of our objects, run an intersection test.
   for(count = 0; count < 4; count++)
   {
      switch(object[count].type)
      {
         case uint(1): // Sphere Collider.
            tests[count] = iSphere(ray_origin, ray_direction, object[count]);
         break;

         case uint(2): // Box Collider.
            tests[count] = iBox(ray_origin, ray_direction, object[count]);
         break;

         case uint(3): // Plane Collider.
            tests[count] = iPlane(ray_origin, ray_direction, object[count]);
         break;

         //case 4: // ***Incoming*** Mass/SVO collider.
         //break;
      }
   }

   // Set up our maximum draw distance.
   interval = 1000.0;

   // Since we are presuming everything is 100% opaque, find the nearest collision, if any.
   for(count = 0; count < 4; count++)
   {
      selector = tests[count].distance > 0.0;
      selector = selector && (tests[count].distance < interval);
      nearest  = selector ? int(count) : nearest;
      interval = selector ? tests[count].distance : interval;
   }

   if(interval == 10000.0) return Collision(-1, -1.0, vec3(0.0, 0.0, 0.0));

   tests[nearest].subject = nearest;
   return tests[nearest];
}

void main(void)
{
   Collider object[4];
   //                    Type,    Location,         Size,   Color
   object[0] = Collider(uint(1), vec3( 1.0,  1.0,  0.0), 1.0, vec3(0.0, 1.0, 1.0));
   object[1] = Collider(uint(1), vec3( 0.0,  5.0,  0.0), 1.0, vec3(0.0, 0.0, 1.0));
   object[2] = Collider(uint(2), vec3( 0.0,  1.0,  0.0), 1.0, vec3(0.0, 1.0, 0.0));
   object[3] = Collider(uint(3), vec3( 0.0, -1.0,  0.0), 1.0, vec3(1.0, 0.8, 0.6));

   // Lets move the first sphere in our object list.
   object[0].location.x = 8.0 * cos(time);
   object[0].location.z = 8.0 * sin(time);

   // Some constant light from a constant direction for all objects, no shadows yet.
   vec3 light_direction = normalize(vec3(.57703));

   // uv are the pixel co-ordinates from 0 to 1.
   vec2 uv = (gl_FragCoord.xy/resolution.xy);

   // We generate a ray with origin ro and direction rd.
   vec3 ray_origin    = vec3(0.0, 1.0, 12.0);
   vec3 ray_direction = normalize(vec3((-1.0+2.0*uv) * vec2(1.78, 1.0), -1.0));

   // We intersect the ray with the 3d scene.
   Collision collision = intersect(ray_origin, ray_direction, object); // ,object

   // We draw black by default.
   vec3 pixel = vec3(0.0);

   if(collision.subject > -1)
   {
      // Apply our object color to the pixel.
      pixel = object[collision.subject].color;

      // Apply some simple lighting to our object surfaces.
      pixel *= dot(collision.deflection, light_direction);
   }

   FragColor = vec4(pixel, 1.0);
}
