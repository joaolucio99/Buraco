#include "../../../lib/pages/players/tools.h"

    char name_player1[16];
    char name_player2[16];
    int p_ready[2] = {0,0};

    void on_player1_input_name_changed( GtkEntry *input ){
        sprintf( name_player1, "%s", gtk_entry_get_text( input ));     //pegando as informações digitadas no input de nome
    }

    void on_player2_input_name_changed( GtkEntry *input ){
        sprintf( name_player2, "%s", gtk_entry_get_text( input ));
    }

    void on_switch_button1_state_set( GtkSwitch *state ){         //alteração estado botao switch player 1
        p_ready[0] = 0;
        control_inp_names( state, "player1_input_name", name_player1, 0 );
    }

    void on_switch_button2_state_set( GtkSwitch *state ){         //alteração estado botao switch player 2
        p_ready[1] = 0;
        control_inp_names( state, "player2_input_name", name_player2, 1 );
    }

    void control_inp_names( GtkSwitch *state, char *input_name, char *name_player, int choice){        //controlar os inputs de nomes
        GtkWidget           *input_player;
        input_player = GTK_WIDGET( gtk_builder_get_object( builder, input_name ));
            gtk_widget_unset_state_flags( input_player , GTK_STATE_FLAG_INSENSITIVE );      //libeirando a box para edição
        gboolean act_state = gtk_switch_get_active( state );      //pegando informação switch button
            if( act_state ){      //verificando estado botao switch
                if( strlen( name_player ) == 0 ){
                    gtk_switch_set_active( state , FALSE );     //alterando estado switch button
                    set_dialog( "VOCÊ NÃO PODE SELECIONAR PRONTO\nSEM UM NOME DEFINIDO" );
                } else{
                    gtk_switch_set_state( state, TRUE ); 
                    gtk_widget_set_state_flags( input_player , GTK_STATE_FLAG_INSENSITIVE , TRUE );        //travando a caixa de edição de nome       
                    p_ready[choice] = 1;    
                }
            }
    }

    void set_hand( int i ){
        GtkBox          *hand;
        GtkWidget       *image;
        GdkPixbuf       *pixbuf;
        GtkWidget       *hand_widget;
        header *aux = player[i].hand->start;
            if( i == 0 ) hand = GTK_BOX( gtk_builder_get_object( builder, "cards_place_p1" ));
            else hand = GTK_BOX( gtk_builder_get_object( builder, "cards_place_p2" ));
            if( i == 0 ) hand_widget = GTK_WIDGET( gtk_builder_get_object( builder, "cards_place_p1" ));
            else hand_widget = GTK_WIDGET( gtk_builder_get_object( builder, "cards_place_p2" ));
            while( aux != NULL ){
                char location[50];
                    strcpy( location, "./assets/normal_cards/" );
                    strcat( location, aux->l_card.image );
                pixbuf = gdk_pixbuf_new_from_file( location, NULL );
                pixbuf = gdk_pixbuf_scale_simple( pixbuf, 114, 158, GDK_INTERP_BILINEAR );
                image = gtk_image_new_from_pixbuf( pixbuf );
                    gtk_widget_show(image);
                    gtk_box_pack_start( hand, image, FALSE, FALSE, 0 );
                aux = aux->next;
            }  
        gtk_widget_hide(hand_widget);
    }