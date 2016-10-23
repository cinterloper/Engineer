#define EFL_BETA_API_SUPPORT
#include <Eo.h>
#include "engineer_database.eo.h"

typedef struct
{
} Engineer_Database_Data;

EOLIAN static void
_engineer_database_init(Eo *obj, Engineer_Database_Data *pd,
        char *type, char *name)
{
   if (pd->database == NULL)
   {
      char *tablename;
      char *filename;
      int   result;

      // Set up our Scene database table and file name strings.
      type      = strcat(pd->project, type);
      tablename = strcat(type, name);
      filename  = strcat(tablename, ".db");

      // Create the database handle object and use it to open the existing Scene database.
      // Note that if there is no pre-exsting Scene database, a new one will be created.
      result = db_create(&pd->database, NULL, 0);
      result = &pd->database->open
      (
         database,   // DB structure pointer
         NULL,       // Transaction pointer
         filename,   // Filename for the on-disk file that holds the database.
         tablename,  // Name symbol for the database.
         DB_HASH,    // Database access method
         DB_CREATE,  // Open flags
         0           // File mode (using defaults)
      );
   }
}

EOLIAN static void
_engineer_database_shutdown(Eo *obj, Engineer_Scene_Data *pd)
{
   if (pd->database != NULL) pd->database->close(pd->database, 0);
}

#include "engineer_database.eo.c"
