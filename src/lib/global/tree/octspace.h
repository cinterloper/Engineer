#ifndef _ENGINEER_OCTSPACE_H_
#define _ENGINEER_OCTSPACE_H_

#include "../../../headers/Engineer.h"

typedef struct
{
   uint32_t      version;
   Eina_Inarray *depth[64];

   uint32_t childmask:30;
   uint32_t lock:2

   uint64_t population;
}
Engineer_Octspace;

typedef struct
{
   uint64_t depth00:3, depth01:3, depth02:3, depth03:3, depth04:3, depth05:3, depth06:3, depth07:3;
   uint64_t depth08:3, depth09:3, depth10:3, depth11:3, depth12:3, depth13:3, depth14:3, depth15:3;
   uint64_t depth16:3, depth17:3, depth18:3, depth19:3, depth20:3, depth21:3,
}
Engineer_Octspace_Index_HighSegment

typedef struct
{
   uint64_t depth22:3, depth23:3, depth24:3, depth25:3, depth26:3, depth27:3, depth28:3, depth29:3;
   uint64_t depth30:3, depth31:3, depth32:3, depth33:3, depth34:3, depth35:3, depth36:3, depth37:3;
   uint64_t depth38:3, depth39:3, depth40:3, depth41:3, depth42:3;
}
Engineer_Octspace_Index_MidSegment

typedef struct
{
   uint64_t depth43:3, depth44:3, depth45:3, depth46:3, depth47:3, depth48:3, depth49:3, depth50:3;
   uint64_t depth51:3, depth52:3, depth53:3, depth54:3, depth55:3, depth56:3, depth57:3, depth58:3;
   uint64_t depth59:3, depth60:3, depth61:3, depth62:3, depth63:3;
}
Engineer_Octspace_Index_LowSegment

typedef struct
{
   Engineer_Octspace_Index_HighSegment highindex;

   uint32_t parent;

   uint64_t lock:8, childmask:20;
   uint64_t topdepth:6,  bottomdepth:6;
   uint64_t updepth:6,   downdepth:6;
   uint64_t leftdepth:6, rightdepth:6;

   uint32_t top,  bottom;
   uint32_t up,   down;
   uint32_t left, right;

   uint64_t entitytransformid; // If this node is a leaf, store an entities transform componentid,
                             // if not, store the total number of child leaves.
}
Engineer_Octspace_Node_0to21;

typedef struct
{
   Engineer_Octspace_Index_HighSegment highindex;
   Engineer_Octspace_Index_MidSegment  midindex;

   uint32_t parent;

   uint64_t lock:2,      childmask:26;
   uint64_t topdepth:5,  bottomdepth:5;
   uint64_t updepth:5,   downdepth:5;
   uint64_t leftdepth:5, rightdepth:5;

   uint32_t top,  bottom;
   uint32_t up,   down;
   uint32_t left, right;

   uint64_t entitytransformid;
}
Engineer_Octspace_Node_22to42;

typedef struct
{
   Engineer_Octspace_Index_HighSegment highindex;
   Engineer_Octspace_Index_MidSegment  midindex;
   Engineer_Octspace_Index_LowSegment  lowindex;

   uint32_t parent;

   uint64_t lock:2,      childmask:26;
   uint64_t topdepth:5,  bottomdepth:5;
   uint64_t updepth:5,   downdepth:5;
   uint64_t leftdepth:5, rightdepth:5;

   uint32_t top,  bottom;
   uint32_t up,   down;
   uint32_t left, right;

   uint64_t entitytransformid;
}
Engineer_Octspace_Node_43to63;

Engineer_Octspace *
engineer_octspace_factory()
{
   Engineer_Octspace *new = calloc(1, sizeof(Engineer_Octspace));
   uint count;

   for(count =  0; count < 22; count++)
   {
      new->depth[count] = eina_inarray_new(sizeof(Engineer_Octspace_Node_0to21),  0);
   }
   for(count = 22; count < 43; count++)
   {
      new->depth[count] = eina_inarray_new(sizeof(Engineer_Octspace_Node_22to42), 0);
   }
   for(count = 43; count < 64; count++)
   {
      new->depth[count] = eina_inarray_new(sizeof(Engineer_Octspace_Node_43to63), 0);
   }

   return new;
}

void
engineer_octspace_insert(Engineer_Octspace *octspace, uint64_t transformid)
{
   // Get the Transforms position and bounds Vec3.

   // Find our root node.

   // while(iterating == EINA_TRUE)
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
   //   If not, create that new suboctant leaf and set the target as it's payload.
   //}
   // First we need to figure out which octree suboctant the inserted mass's origin intersects with.
   // When we have that information, we check to see if that suboctant already exists.
   // If not, check to see if current node is a leaf
   //create it and insert the proper values for neighbors. Then put in the payload. Exit.

   // If that node is not a leaf, check the child mask for present children, and retrieve them.

   // Run the insert func again on the child nodes

   // If the node is a leaf, take the current occupant out and turn it into a branch.
   // Check to see which octant the current occupant is in, and create a new leaf there.
   //
   // Check to see if the target will occupy the same suboctant as the target.
}

void
engineer_octspace_remove()
{
}

#endif
