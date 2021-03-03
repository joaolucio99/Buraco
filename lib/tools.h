#ifndef TOOLS
#define TOOLS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <gtk/gtk.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
#include "list.h"
#include "structs.h"
#include "players.h"
#include "deck.h"
#include "dialogs.h"

    extern GtkBuilder      *builder;        
    extern GtkWidget       *window;

    void on_window_main_destroy();

    void get_date();

    void load_css();

#endif