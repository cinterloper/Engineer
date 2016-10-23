#define EFL_BETA_API_SUPPORT
#include <Eo.h>
#include "engineer_module_template.h"

typedef struct {} Engineer_Module_Template_Data;

typedef struct
{
}
Component_Data;

static inline void
engineer_component_update(Component_Data *component)
{
}

EOLIAN static Efl_Object *
_engineer_module_template_engineer_module_init(Eo *obj, Engineer_Module_Template_Data *pd)
{ return efl_add(ENGINEER_MODULE_TEMPLATE_CLASS, NULL); }

EOLIAN static unsigned int
_engineer_module_template_engineer_module_size(Eo *obj, Engineer_Module_Template_Data *pd)
{ return sizeof(Component_Data); }

EOLIAN static void
_engineer_module_template_engineer_module_component_update(Eo *obj, Engineer_Module_Template_Data *pd,
        void *component) { engineer_component_update(component); }

#include "engineer_module_template.eo.c"
