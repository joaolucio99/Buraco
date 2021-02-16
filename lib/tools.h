#ifndef TOOLS
#define TOOLS
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <string.h>
#include "structs.h"
#include "players.h"

    extern GtkBuilder      *builder;        
    extern GtkWidget       *window;

    void on_window_main_destroy();

    void load_css();

#endif