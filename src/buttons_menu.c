#include "../lib/buttons_menu.h"

    void on_button_exit_clicked(){
        gtk_main_quit();
    }

    void on_button_init_clicked( GtkButton *button, GtkStack *stack ){
        gtk_stack_set_visible_child_name (stack, "game_page" );
    }