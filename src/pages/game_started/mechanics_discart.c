#include "../../../lib/pages/game_started/mechanics_trash.h"

    void on_discard_button_clicked(){
        GtkWidget              *dialog;
        GtkComboBoxText        *combo_box_text;
        GtkComboBox            *combo_box;
        header *aux = player[active].hand->start;
        int count_list = 0;
        combo_box_text =  GTK_COMBO_BOX_TEXT( gtk_builder_get_object( builder, "cards_list_discart" ));
        combo_box =  GTK_COMBO_BOX( gtk_builder_get_object( builder, "cards_list_discart" ));
        dialog = GTK_WIDGET( gtk_builder_get_object( builder, "discart" ));
                while ( aux != NULL ){
                    char card_name[30];
                        set_card_name_cb_box( aux->l_card.suit, aux->l_card.number, card_name );
                        gtk_combo_box_text_insert( combo_box_text, count_list, aux->l_card.image, card_name );
                    count_list++;
                    aux = aux->next;
                }
            gtk_combo_box_set_active( combo_box, 0 );
            gtk_widget_show( dialog );
    }

    void set_card_name_cb_box( int suit , char *number, char *card_name ){    //formar a string para definir nome da carta
        char temp[50];
            strcpy( temp, number );
            strcat( temp , " - " );
                if( suit == 1) strcat( temp , "Copas" );    
                else if( suit == 2) strcat( temp, "Paus");                    
                else if( suit == 3) strcat( temp, "Espadas");                   
                else strcat( temp, "Ouros" );   
            strcpy( card_name, temp );
    }

    void on_discart_card_clicked(){     //dialog botao discartar
        GtkComboBox        *combo_box;
        GtkGrid          *hand;
        char *text_select;
        char text_compare[30];
        int count_grid = list_count_size( player[active].hand );
        combo_box =  GTK_COMBO_BOX( gtk_builder_get_object( builder, "cards_list_discart" ));
        text_select = (char*)gtk_combo_box_get_active_id (combo_box);
            strcpy( text_compare, "./assets/normal_cards/" );
            strcat( text_compare, text_select);
            free( text_select );
                if( active == 0 ) hand = GTK_GRID( gtk_builder_get_object( builder, "cards_place_p1" ));
                else hand = GTK_GRID( gtk_builder_get_object( builder, "cards_place_p2" ));
                    for( int z = 0; z < count_grid ; z++ ){
                        if( count_grid < 24 ) {
                            GtkWidget       *image;
                            image = gtk_grid_get_child_at( hand, z, 0 );
                        
                        }
                        //else gtk_grid_attach( hand, new_img, count_grid, 0, 1, 1 );
                    }
    }     

    void on_discart_back_clicked(){     //dialog botao voltar
        GtkWidget          *dialog;
        GtkComboBoxText        *combo_box;
        combo_box =  GTK_COMBO_BOX_TEXT( gtk_builder_get_object( builder, "cards_list_discart" ));
        dialog = GTK_WIDGET( gtk_builder_get_object( builder, "discart" ));
            gtk_combo_box_text_remove_all( combo_box );
            gtk_widget_hide( dialog );
    }