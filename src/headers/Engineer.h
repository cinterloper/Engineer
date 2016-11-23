#ifndef ENGINEER_H_
#define ENGINEER_H_

#ifdef EAPI
# undef EAPI
#endif

#ifdef _WIN32
# ifdef EFL_ENGINEER_BUILD
#  ifdef DLL_EXPORT
#   define EAPI __declspec(dllexport)
#  else
#   define EAPI
#  endif /* ! DLL_EXPORT */
# else
#  define EAPI __declspec(dllimport)
# endif /* ! EFL_ENGINEER_BUILD */
#else
# ifdef __GNUC__
#  if __GNUC__ >= 4
#   define EAPI __attribute__ ((visibility("default")))
#  else
#   define EAPI
#  endif
# else
#  define EAPI
# endif
#endif /* ! _WIN32 */

#ifdef __cplusplus
extern "C" {
#endif

#define EFL_BETA_API_SUPPORT

#include <stdio.h>
#include <string.h>
#include <db.h>
#include <Ecore_Getopt.h>
#include <Elementary.h>

#include "../lib/engineer_math.h"
#include "../lib/engineer_game.h"
#include "../lib/engineer_scene.h"

#define UINT_NULL 0xFFFFFFFF
#define ULONG_NULL 0xFFFFFFFFFFFFFFFF

/// @file
/// @brief These routines are used for Engineer library interaction.

/// @brief Init / shutdown functions.
/// @defgroup Init  Init / Shutdown
///
/// @{
///
/// Functions of obligatory usage, handling proper initialization
/// and shutdown routines.
///
///  Before the usage of any other function, Engineer should be properly
/// initialized with @ref engineer_init() and the last call to Engineer's
/// functions should be @ref engineer_shutdown(), so everything will
/// be correctly freed.
///
/// Engineer logs everything with Eina Log, using the "engineer" log domain.

/// Initialize Engineer.
///
/// Initializes Engineer, its dependencies and modules. Should be the first
/// function of Engineer to be called.
///
/// @return The init counter value.
///
/// @see engineer_shutdown().
///
/// @ingroup Init

EAPI int engineer_init(void);

/// Shutdown Engineer
///
/// Shutdown Engineer. If init count reaches 0, all the internal structures will
/// be freed. Any Engineer library call after this point will leads to an error.
///
/// @return Engineer's init counter value.
///
/// @see engineer_init().
///
/// @ingroup Init

EAPI int engineer_shutdown(void);

/// @}

/// @brief Main group API that wont do anything
/// @defgroup Main Main
///
/// @{
///
/// @brief A function that doesn't do any good nor any bad
/// @ingroup Main

EAPI void engineer_run(void);

/// @}

EAPI Efl_Object *
eng_scene_new(char * name);

EAPI void
eng_module_load(Eo *obj, char *path);

EAPI uint
eng_entity_create(Eo *obj, uint parent, const char *name);

EAPI uint
eng_sector_create(Eo *obj, uint parent);

void
eng_free_cb(void *data);

#ifdef __cplusplus
}
#endif

#endif /* ENGINEER_H_ */
