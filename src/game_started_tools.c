#include "../lib/game_started_tools.h"

    int active;
    int count_round=0;

    void set_current_player( char *location, char *name ){
        GtkImage           *image;
        GtkLabel           *label; 
        image = GTK_IMAGE( gtk_builder_get_object( builder, "player_active_icon" ));
        label = GTK_LABEL( gtk_builder_get_object( builder, "player_active_name" ));
            gtk_image_set_from_file( image , location );
            gtk_label_set_text( label , name );
    }

    void on_pass_turn_clicked(){
        if( active == 0 ) active=1;
        else active=0;
        turn();
    }

    void on_win_game_clicked(){
        gtk_main_quit();
    }