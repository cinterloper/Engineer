#ifndef ENGINEER_MAIN_H_
#define ENGINEER_MAIN_H_

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#if ENABLE_NLS
# include <libintl.h>
#endif

#include "gettext.h"
#include "engineer_window.h"

#define COPYRIGHT "Copyright © 2016 Matthew Kolar <mjkolar@charter.net> and various contributors (see AUTHORS)."

EAPI Eina_Bool
engineer_editor_init();

EAPI Eina_Bool
engineer_editor_shutdown();

#endif
