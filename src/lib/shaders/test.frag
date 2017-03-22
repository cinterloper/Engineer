#version 310 es

#ifdef GL_ES
precision highp float;
#endif

#define MISS   Collision(-1, -1.0, vec3(0.0, 0.0, 0.0))
#define ORIGIN vec3(0.0, 0.0, 0.0);

struct Collider
{
   vec3  location;
   uint  type;
   vec3  color;
   float size;
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

layout (std430, binding = 1) buffer shader_data
{
   Collider objects[];
};

uniform vec2  resolution;
uniform uint  count;

out vec4 FragColor;

Collision iSphere(in vec3 ray_origin, in vec3 ray_direction, in Collider sphere)
{
   vec3 oc = ray_origin - sphere.location;
   float b = 2.0 * dot(oc, ray_direction);
   float c = dot(oc, oc) - sphere.size * sphere.size;
   float h = b * b - 4.0 * c;

   if(h < 0.0) return MISS;

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

    vec3 normal;

    return Collision(-1, tmin, vec3(0.0, 0.0, 1.0));
}

Collision iPlane(in vec3 ray_origin, in vec3 ray_direction, in Collider plane)
{
   // Normal of an up facing y plane: 0.0, 1.0, 0.0
   // Equation of a y-aligned plane: y = 0 = ray_origin.y + t * ray_direction.y
   // Normal of a camera facing z plane: 0.0, 0.0, 1.0;

   return Collision(-1, plane.location.y/ray_direction.y, vec3(0.0, 1.0, 0.0));
}

Collision
intersect(in vec3 ray_origin, in vec3 ray_direction)
{
   Collision tests[4];
   int       type;
   int       counter;
   bool      selector;
   int       nearest;
   float     draw_distance;
   float     interval;

   // Set up our maximum draw distance.
   draw_distance = pow(2.0, 32.0);
   interval = draw_distance;

   // For each of our objects, run an intersection test.
   for(counter = 0; counter < int(count); counter++)
   {
      switch(objects[counter].type)
      {
         case uint(1): // Sphere Collider.
            tests[counter] = iSphere(ray_origin, ray_direction, objects[counter]);
         break;

         case uint(2): // Box Collider.
            tests[counter] = iBox(ray_origin, ray_direction, objects[counter]);
         break;

         case uint(3): // Plane Collider.
            tests[counter] = iPlane(ray_origin, ray_direction, objects[counter]);
         break;

         //case 4: // ***Incoming*** Mass/SVO collider.
         //break;
      }
   }

   // Since we are presuming everything is 100% opaque, find the nearest collision, if any.
   for(counter = 0; counter < int(count); counter++)
   {
      selector = tests[counter].distance > 0.0;
      selector = selector && (tests[counter].distance < interval);
      nearest  = selector ? int(counter) : nearest;
      interval = selector ? tests[counter].distance : interval;
   }

   if(interval == draw_distance) return MISS;

   tests[nearest].subject = nearest;
   return tests[nearest];
}

void main(void)
{
   // Some constant light from a constant direction for all objects, no shadows yet.
   vec3 light_direction = normalize(vec3(.57703));

   // uv are the pixel co-ordinates from 0 to 1.
   vec2 uv = (gl_FragCoord.xy/resolution.xy);

   // We generate a ray with origin ro and direction rd.
   vec2 aspect_ratio  = vec2(1.78, 1.0);
   vec3 ray_origin    = ORIGIN;
   vec3 ray_direction = normalize(vec3((-1.0+2.0*uv) * aspect_ratio, -1.0));

   // We intersect the ray with the 3d scene.
   Collision collision = intersect(ray_origin, ray_direction);

   // We draw black by default.
   vec3 pixel = vec3(0.0);

   if(collision.subject > -1)
   {
      // Apply our object color to the pixel.
      pixel = objects[collision.subject].color;

      // Apply some simple lighting to our object surfaces.
      pixel *= dot(collision.deflection, light_direction);
   }

   FragColor = vec4(pixel, 1.0);
}
