#include "octspace.h"

//               +Z      <- Octspace subdivides (recursively) in this order.
//     4---5     /       <- It correlates the Z, Y, X vectors as bit switches, with negative vectors
//    /|  /|    /        <- encoded as zero.  By a wild coincidence, ordering the resulting list of
//   0---1 |   @----+X   <- positions by ascending binary count gives us a Morton Order.
//   | 6-|-7   |         <- That won't be useful at all later...
//   |/  |/    |
//   2---3     |
//            +Y

Engineer_Octspace *
engineer_octspace_factory(Eo *scene)
{
   Engineer_Octspace *octspace = malloc(sizeof(Engineer_Octspace));
   uint count;

   octspace->scene = scene;

   for(count =  1; count < 22; count++)
   {
      octspace->level[count] = eina_inarray_new(sizeof(Engineer_Octspace_Node_01to21), 0);
   }
   for(count = 22; count < 43; count++)
   {
      octspace->level[count] = eina_inarray_new(sizeof(Engineer_Octspace_Node_22to42), 0);
   }
   for(count = 43; count < 64; count++)
   {
      octspace->level[count] = eina_inarray_new(sizeof(Engineer_Octspace_Node_43to63), 0);
   }

   new->childmask = 0;

   return new;
}

void
engineer_octspace_disposal(Engineer_Octspace *octspace)
{
   uint count;

   for(count = 1; count < 64; count++)
   {
     eina_inarray_free(octspace->level[count]);
   }
   free(octspace);
}

void
engineer_octspace_insert(Engineer_Octspace *octspace, uint64_t transformid)
{
   // Get the Transform's position and bounds Vec3.
   Engineer_Component_Class *class;
   uint64_t classid;
   Eo *node, *module;
   Vec3 *buffer, position, bounds;
   int32_t depth, scale;

   node = efl_parent_get(octspace->scene);
   classid = engineer_hash_murmur3("Transform", strlen("Transform"), 242424);
   class = engineer_node_module_class_lookup(node, classid);
   module = engineer_scene_module_get(octspace->scene, class);

   buffer   = class->component_state_get(module, transformid, "position");
   position = *buffer;
   free(buffer);

   buffer   = class->component_state_get(module, transformid, "bounds");
   bounds   = *buffer;
   free(buffer);

   //while(depth > 0)
   //{
   //   //Check to see if the current node is a leaf.
   //   if(octspace->childmask == 0)
   //   {
   //      If so, check to see which suboctant the current occupant intersects with.
   //      Change this node to a branch, and create a new leaf at said suboctant.
   //      Put the current occupant into the new leaf.
   //      Increase branch population by 1.
   //   }
   //
   //   Find which suboctant the target intersects with.
   //   Does that suboctant already exist? If so, set it as our current node and start over.
   //   If not, create that new suboctant leaf and set the target as it's payload, and insert it
   //     into the appropriate depth level.
   //}
}

void
engineer_octspace_remove(Engineer_Octspace *octspace)
{
}

void
engineer_octspace_sprout(Engineer_Octspace *octspace,
        uint32_t depth, uint32_t index, uint32_t octant)
{
}

void
engineer_octspace_prune(Engineer_Octspace *octspace,
        uint32_t depth, uint32_t index)
{
}

Vec3
engineer_octspace_intersect_point(Engineer_Octspace *octspace,
        uint32_t depth, uint32_t nodeindex, Vec3 point)
{
   uint64_t height, pivot, octant, scale = 63;
   Eina_Inarray *level;
   Vec3 index;

   // Set our current node to the octspace root.
   height = scale - depth;
   pivot  = 2 << height;

   switch(depth)
   {
      case  1 ... 21:
      {
         Engineer_Octspace_Node_01to21 *node;

         octant = 0;
         if(point.x > pivot) octant += 4;
         if(point.y > pivot) octant += 2;
         if(point.z > pivot) octant += 1;

         level    = octspace->level[depth];
         node     = eina_inarray_nth(level, nodeindex);
         index.x += node->index + octant << (3 * (height % 21));
      }
      break;
      case 22 ... 42:
      {
         Engineer_Octspace_Node_22to42 *node;

         octant = 0;
         if(point.x > pivot) octant += 4;
         if(point.y > pivot) octant += 2;
         if(point.z > pivot) octant += 1;

         level    = octspace->level[depth];
         node     = eina_inarray_nth(level, nodeindex);
         index.x  = node->index.x;
         index.y += node->index.y + octant << (3 * (height % 21));
      }
      break;
      case 43 ... 63:
      {
         Engineer_Octspace_Node_43to63 *node;

         octant = 0;
         if(point.x > pivot) octant += 4;
         if(point.y > pivot) octant += 2;
         if(point.z > pivot) octant += 1;

         level    = octspace->level[depth];
         node     = eina_inarray_nth(level, nodeindex);
         index.x  = node->index.x;
         index.y  = node->index.y;
         index.z += node->index.z + octant << (3 * height);
      }
      break;
   }

   return index;
}

Vec3
engineer_octspace_intersect_box(Engineer_Octspace *octspace,
        uint32_t depth, uint32_t nodeindex, Vec3 target, Vec3 orientation, Vec3 bounds)
{

}

uint32_t
engineer_octspace_search(Engineer_Octspace *octspace,
        uint32_t depth, Vec3 index)
{
   Eina_Inarray *domain;
   uint32_t count, pivot, iteration, increment;

   domain    = octspace->level[depth];
   count     = eina_inarray_count(domain);
   pivot     = count / 2;
   iteration = 1;
   increment = 1;

   switch(depth)
   {
      case 1  ... 21:
      {
         Engineer_Octspace_Node_01to21 *node;
         while(increment > 0)
         {
            increment = count / (2 << iteration);

            node  = eina_inarray_nth(domain, pivot);
            pivot = (node->index > index.x)
                          ? pivot + increment : pivot - increment;
            iteration += 1;
         }
      }
      break;
      case 22 ... 42:
      {
         Engineer_Octspace_Node_22to42 *node;
         while(increment > 0)
         {
            increment = count / (2 << iteration);

            node  = eina_inarray_nth(domain, pivot);
            pivot = (node->index.x > index.x &&
                     node->index.y > index.y )
                       ? pivot + increment : pivot - increment;
            iteration += 1;
         }
      }
      break;
      case 43 ... 63:
      {
         Engineer_Octspace_Node_43to63 *node;
         while(increment > 0)
         {
            increment = count / (2 << iteration);

            node  = eina_inarray_nth(domain, pivot);
            pivot =(node->index.x > index.x &&
                    node->index.y > index.y &&
                    node->index.z > index.z )
                       ? pivot + increment : pivot - increment;
            iteration += 1;
         }
      }
      break;
   }

   return pivot;
}

