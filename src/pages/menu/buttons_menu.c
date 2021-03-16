#include "../../../lib/pages/menu/buttons_menu.h"

    void on_button_exit_clicked(){ 
        gtk_main_quit();
    }

    void on_button_rules_clicked(){
        GtkStack    *stack;
        stack = GTK_STACK( gtk_builder_get_object( builder, "all_pages" ) );
            gtk_stack_set_visible_child_name ( stack, "rules_page" );
    }

    void on_back_rules_clicked(){
        GtkStack    *stack;
        stack = GTK_STACK( gtk_builder_get_object( builder, "all_pages" ) );
            gtk_stack_set_visible_child_name ( stack, "init_page" );
    }

    void on_button_init_clicked( GtkButton *button, GtkStack *stack ){         
        gtk_stack_set_visible_child_name ( stack, "players_page" );        
    }