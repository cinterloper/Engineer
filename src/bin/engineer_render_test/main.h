#ifndef _ENGINEER_RENDER_TEST_MAIN_H_
#define _ENGINEER_RENDER_TEST_MAIN_H_

//#ifdef HAVE_CONFIG_H
//# include "config.h"
//#endif

//#if ENABLE_NLS
//# include <libintl.h>
//#endif

//#include "gettext.h"
#include "../../headers/Engineer.h"
#include <stdio.h>

#define COPYRIGHT "Copyright © 2016 Matthew Kolar <mjkolar@charter.net> and various contributors (see AUTHORS)."

//extern char *title;

Eo *
engineer_render_test_window_init();

Eo *
engineer_render_test_viewport_init(Eo *window);

void
engineer_render_test_game_init(Eo *root, Eo *viewport);

#endif
