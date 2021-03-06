#include "../../../lib/pages/game_started/mechanics_trash.h"

    void on_discard_button_clicked(){
        if( player[active].buy_card == 1){
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
                            gtk_combo_box_text_insert( combo_box_text, count_list, aux->l_card.widget, card_name );
                        count_list++;
                        aux = aux->next;
                    }
                gtk_combo_box_set_active( combo_box, 0 );
                gtk_widget_show( dialog );
        } else set_dialog( "VOCÊ NÃO PODE DESCARTAR SEM QUE\nCOMPRE CARTA" );
    }

    void on_discart_card_clicked(){     //dialog botao discartar
        if( player[active].discard_card == 0 ){
            GtkComboBox        *combo_box;
            GtkGrid            *hand;
            GtkWidget          *dialog;
            GtkComboBoxText    *combo_box_text;
            char *text_select;
            int count_grid = list_count_size( player[active].hand, 0 );
            dialog = GTK_WIDGET( gtk_builder_get_object( builder, "discart" ));
            combo_box_text =  GTK_COMBO_BOX_TEXT( gtk_builder_get_object( builder, "cards_list_discart" ));
            combo_box =  GTK_COMBO_BOX( gtk_builder_get_object( builder, "cards_list_discart" ));
            text_select = (gchar*)gtk_combo_box_get_active_id (combo_box);      // nome da carta que a pessoa quer descartar    
                if( active == 0 ) hand = GTK_GRID( gtk_builder_get_object( builder, "cards_place_p1" ));
                else hand = GTK_GRID( gtk_builder_get_object( builder, "cards_place_p2" ));
                for( int z = 0; z < count_grid ; z++ ){     //inicio percorrer as linhas para selecionar a carta
                    if( z < 24 ) {
                        GtkWidget       *image;
                        image = gtk_grid_get_child_at( hand, z, 0 );
                        char *current_card_widget_name;
                        current_card_widget_name = (gchar*)gtk_widget_get_name( image );   //nome da carta atual do grid
                            if( strcmp( text_select, current_card_widget_name ) == 0 ){   //se a carta for igual
                                header *aux = player[active].hand->start;
                                    while( aux != NULL ){
                                        if( strcmp( text_select, aux->l_card.widget ) == 0) break;
                                        else aux = aux->next;
                                    }
                                int position_card;
                                    list_search_key( player[active].hand, aux->l_card, &position_card );
                                cards temp;
                                    list_remove_pos( player[active].hand, &temp, position_card );
                                temp.active_on.hand = 0;
                                temp.active_on.trash = 0;
                                    list_insert( trash, temp );
                                    gtk_widget_destroy( image );
                                    hand_to_trash( temp );
                                player[active].discard_card = 1;
                                    gtk_combo_box_text_remove_all( combo_box_text );
                                    gtk_widget_hide( dialog );
                                return;
                            }
                    } else{     //tiver mais de uma linha de cartas
                        int count_p_rows;
                        if( active == 0 ) count_p_rows = count_row2_p1;
                        else count_p_rows = count_row2_p2;
                        for(int k=0; k < count_p_rows; k++){
                            GtkWidget       *image;
                            image = gtk_grid_get_child_at( hand, k, 1 );
                            char *current_card_widget_name;
                            current_card_widget_name = (gchar*)gtk_widget_get_name( image );   //nome da carta atual do grid
                                if( strcmp( text_select, current_card_widget_name ) == 0 ){   //se a carta for igual
                                    header *aux = player[active].hand->start;
                                        while( aux != NULL ){
                                            if( strcmp( text_select, aux->l_card.widget ) == 0) break;
                                            else aux = aux->next;
                                        }
                                    int position_card;
                                        list_search_key( player[active].hand, aux->l_card, &position_card );
                                    cards temp;
                                        list_remove_pos( player[active].hand, &temp, position_card );
                                    temp.active_on.hand = 0;
                                    temp.active_on.trash = 0;
                                        list_insert( trash, temp );
                                        gtk_widget_destroy( image );
                                        hand_to_trash( temp );
                                    player[active].discard_card = 1;
                                        if( active == 0 ) count_row2_p1--;
                                        else count_row2_p2--;
                                        gtk_combo_box_text_remove_all( combo_box_text );
                                        gtk_widget_hide( dialog );
                                    return;
                            }
                        }
                    }
                }
        } else set_dialog( "VOCÊ NÃO PODE DESCARTAR MAIS\nQUE UMA CARTA" ); 
    }  

    void hand_to_trash( cards temp ){       //enviar carta pro lixo
        GtkGrid         *trash_grid;
        GtkWidget       *image;
        GdkPixbuf       *pixbuf;
        char location[50];
        int count = list_count_size ( trash, 0 );
        trash_grid = GTK_GRID( gtk_builder_get_object( builder, "trash_grid" ));
            strcpy( location, "./assets/normal_cards/" );
            strcat( location, temp.image );
        pixbuf = gdk_pixbuf_new_from_file( location, NULL );
        pixbuf = gdk_pixbuf_scale_simple( pixbuf, 54, 74, GDK_INTERP_BILINEAR );
        image = gtk_image_new_from_pixbuf( pixbuf );
        gtk_widget_set_name( image, temp.widget );
            gtk_widget_show(image);
                if( count < 21 ){
                    gtk_grid_attach( trash_grid, image, (count-1), 0, 1, 1 );
                } else if( count > 20 && count < 41 ){
                    gtk_grid_attach( trash_grid, image, row_trash[0], 1, 1, 1 );
                    row_trash[0]++;
                } else if( count > 40 && count < 61 ){
                    gtk_grid_attach( trash_grid, image, row_trash[1], 2, 1, 1 );
                    row_trash[1]++;
                } else if( count > 60 && count < 81 ){
                    gtk_grid_attach( trash_grid, image, row_trash[2], 3, 1, 1 );
                    row_trash[2]++;
                } else if( count > 80 && count < 101 ){
                    gtk_grid_attach( trash_grid, image, row_trash[3], 4, 1, 1 );
                    row_trash[3]++;
                } else{
                    gtk_grid_attach( trash_grid, image, row_trash[4], 5, 1, 1 );
                    row_trash[4]++;
                }
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

    void on_discart_back_clicked(){     //dialog botao voltar
        GtkWidget          *dialog;
        GtkComboBoxText        *combo_box;
        combo_box =  GTK_COMBO_BOX_TEXT( gtk_builder_get_object( builder, "cards_list_discart" ));
        dialog = GTK_WIDGET( gtk_builder_get_object( builder, "discart" ));
            gtk_combo_box_text_remove_all( combo_box );
            gtk_widget_hide( dialog );
    }