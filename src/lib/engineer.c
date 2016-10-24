#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "Engineer.h"

static int _engineer_init = 0;
int _engineer_lib_log_dom = -1;

EAPI int
engineer_init(void)
{
   _engineer_init++;
   if (_engineer_init > 1) return _engineer_init;

   eina_init();

   _engineer_lib_log_dom = eina_log_domain_register("engineer", EINA_COLOR_CYAN);
   if (_engineer_lib_log_dom < 0)
     {
	EINA_LOG_ERR("Engineer can not create its log domain.");
	goto shutdown_eina;
     }

   // Put here your initialization logic of your library

   eina_log_timing(_engineer_lib_log_dom, EINA_LOG_STATE_STOP, EINA_LOG_STATE_INIT);

   return _engineer_init;

 shutdown_eina:
   eina_shutdown();
   _engineer_init--;

   return _engineer_init;
}

EAPI int
engineer_shutdown(void)
{
   _engineer_init--;
   if (_engineer_init != 0) return _engineer_init;

   eina_log_timing(_engineer_lib_log_dom,
		   EINA_LOG_STATE_START,
		   EINA_LOG_STATE_SHUTDOWN);

   // Put here your shutdown logic

   eina_log_domain_unregister(_engineer_lib_log_dom);
   _engineer_lib_log_dom = -1;

   eina_shutdown();

   return _engineer_init;
}

EAPI void
engineer_run(void)
{
   Eo *scene = eng_scene_new("My Scene");
   uint entityid = eng_entity_create(scene, 0, "Sector1");
   eng_sector_create(scene, entityid);
}

EAPI Efl_Object *
eng_scene_new(char *name) // add a pointer to the game.
{
   return efl_add(ENGINEER_SCENE_CLASS, NULL,
           engineer_scene_name_set(efl_added, name)); // need to set up project pathing.
}

EAPI void
eng_module_load(Eo *obj, char *path)
{
   //engineer_scene_module_load(obj, path);
}

EAPI uint
eng_entity_create(Eo *obj, uint parent, const char *name)
{
   return engineer_scene_entity_create(obj, parent, name);
}

EAPI uint
eng_sector_create(Eo *obj, uint parent)
{
   return engineer_scene_sector_create(obj, parent);
}

EAPI void
eng_free_cb(void *data)
{
   free(data);
}
