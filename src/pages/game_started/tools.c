#include "../../../lib/pages/game_started/tools.h"
    
    int active;
    int count_round=0;

    void set_current_player( char *location, char *name ){      //mostrar na area do player nome e imagem
        GtkImage           *image;
        GtkLabel           *label; 
        image = GTK_IMAGE( gtk_builder_get_object( builder, "player_active_icon" ));
        label = GTK_LABEL( gtk_builder_get_object( builder, "player_active_name" ));
            gtk_image_set_from_file( image , location );
            gtk_label_set_text( label , name );
    }

    void set_current_hand() {       //renderizar mao do player atual
        GtkWidget       *hand_p1;
        GtkWidget       *hand_p2;
        hand_p1 = GTK_WIDGET( gtk_builder_get_object( builder, "cards_place_p1" ));
        hand_p2 = GTK_WIDGET( gtk_builder_get_object( builder, "cards_place_p2" ));
            if( active == 0 ) {
                gtk_widget_show( hand_p1 );
                gtk_widget_hide( hand_p2 );
            } else{
                gtk_widget_show( hand_p2 );
                gtk_widget_hide( hand_p1 );
            }
    }

    void on_buy_card_clicked(){      //clicar no botao de comprar carta
        GtkImage           *image;
        GtkWidget          *dialog;
        image = GTK_IMAGE( gtk_builder_get_object( builder, "img_cart_purchased" ));
        dialog = GTK_WIDGET( gtk_builder_get_object( builder, "card_purchased" ));
        char location[50];
            strcpy( location, "./assets/normal_cards/" );
            strcat( location, deck[deck_amount_cards].image );
            gtk_image_set_from_file( image , location );
            gtk_widget_show( dialog );
    }

    void on_pass_turn_clicked(){        //clicar no botao passar a vez do jogador
        if( active == 0 ) active=1;
        else active=0;
        turn();
    }

    void on_win_game_clicked(){         //clicar no botao de bater
        gtk_main_quit();
    }

    void on_card_trash_clicked(){       //dialog botao jogar carta pro lixo
        GtkWidget          *dialog;
        dialog = GTK_WIDGET( gtk_builder_get_object( builder, "card_purchased" ));
        deck[deck_amount_cards].active = 1;
        deck[deck_amount_cards].active_on.trash = 1;
            list_insert( trash, deck[deck_amount_cards] );
        deck_amount_cards--;
            gtk_widget_hide( dialog );
    }

    void on_card_buy_clicked(){         //dialog botao comprar carta
        GtkWidget          *dialog;
        dialog = GTK_WIDGET( gtk_builder_get_object( builder, "card_purchased" ));
        deck[deck_amount_cards].active = 1;
        deck[deck_amount_cards].active_on.hand = 1;
            list_insert( player[active].hand, deck[deck_amount_cards] );
            add_card_on_hand();
        deck_amount_cards--;
            gtk_widget_hide( dialog );
    }

    void add_card_on_hand(){        //mostra visualmente a carta adicionada a mão
        GtkBox          *hand;
        GtkWidget       *image;
        GdkPixbuf       *pixbuf;
            if( active == 0 ) hand = GTK_BOX( gtk_builder_get_object( builder, "cards_place_p1" ));
            else hand = GTK_BOX( gtk_builder_get_object( builder, "cards_place_p2" ));
        char location[50];
            strcpy( location, "./assets/normal_cards/" );
            strcat( location, deck[deck_amount_cards].image );
            pixbuf = gdk_pixbuf_new_from_file( location, NULL );
            pixbuf = gdk_pixbuf_scale_simple( pixbuf, 114, 158, GDK_INTERP_BILINEAR );
            image = gtk_image_new_from_pixbuf( pixbuf );
                gtk_widget_show(image);
                gtk_box_pack_start( hand, image, FALSE, FALSE, 0 );
    }

