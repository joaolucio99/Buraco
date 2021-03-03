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

    void set_current_hand(){
        GtkBox          *hand;
        GtkWidget       *image;
        GdkPixbuf       *pixbuf;
        pixbuf=gdk_pixbuf_new_from_file("./assets/normal_cards/2_Copas.png",NULL);
        pixbuf=gdk_pixbuf_scale_simple(pixbuf,114,158,GDK_INTERP_BILINEAR);
        hand = GTK_BOX( gtk_builder_get_object( builder, "cards_place" )); 
        image = gtk_image_new_from_pixbuf(pixbuf);
        gtk_widget_show(image);
        gtk_box_pack_start(hand , image , FALSE , FALSE , 0);
    }

    void on_pass_turn_clicked(){
        if( active == 0 ) active=1;
        else active=0;
        turn();
    }

    void on_win_game_clicked(){
        gtk_main_quit();
    }