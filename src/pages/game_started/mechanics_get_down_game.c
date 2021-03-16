#include "../../../lib/pages/game_started/mechanics_get_down_game.h"

    int comb_amount_cards = 3;

    void on_button_get_down_game_clicked(){     
        GtkWidget           *dialog;
        dialog = GTK_WIDGET( gtk_builder_get_object( builder, "new_game" ));
            for ( int i = 0; i < comb_amount_cards; i++ ){
                get_labels_info( i );
            }
            gtk_widget_show( dialog );
    }

    void on_adjustment1_button_game_value_changed(){        
        GtkSpinButton *spin_button;
        GtkContainer  *container;
        container = GTK_CONTAINER( gtk_builder_get_object( builder, "view_dialog" ));
        spin_button = GTK_SPIN_BUTTON( gtk_builder_get_object( builder, "change_n_cards" ));
        int value =  (int)gtk_spin_button_get_value ( spin_button );       
            if( value > comb_amount_cards ){       
                GtkWidget   *new_combox_box_text;
                char selector_combo_box[50],temp_number[3];
                    strcpy( selector_combo_box , "combo_card_");
                    sprintf( temp_number, "%i", comb_amount_cards );
                    strcat( selector_combo_box , temp_number );
                new_combox_box_text = GTK_WIDGET( gtk_builder_get_object( builder, selector_combo_box ));
                    get_labels_info( comb_amount_cards );
                    gtk_widget_show( new_combox_box_text );
                comb_amount_cards++;
            } else if( value < comb_amount_cards || value == comb_amount_cards ){       
                GtkComboBoxText        *combo_box_text;
                GtkWidget           *remove_combox_box_text;
                char selector_combo_box[50],temp_number[3];
                    strcpy( selector_combo_box , "combo_card_");
                    sprintf( temp_number, "%i", comb_amount_cards-1 );
                    strcat( selector_combo_box , temp_number );
                remove_combox_box_text = GTK_WIDGET( gtk_builder_get_object( builder, selector_combo_box ));
                combo_box_text =  GTK_COMBO_BOX_TEXT( gtk_builder_get_object( builder, selector_combo_box ));
                    gtk_combo_box_text_remove_all( combo_box_text );
                    gtk_widget_hide( remove_combox_box_text );
                comb_amount_cards--;
            }
    }

    void get_labels_info( int number ){               
        GtkComboBoxText        *combo_box_text;
        GtkComboBox            *combo_box;
        header *aux = player[active].hand->start;
        int count_list = 0;
        char selector_combo_box[50],temp_number[3];
            strcpy( selector_combo_box , "combo_card_");
            sprintf( temp_number, "%i", number );
            strcat( selector_combo_box , temp_number );
        combo_box_text =  GTK_COMBO_BOX_TEXT( gtk_builder_get_object( builder, selector_combo_box ));
        combo_box =  GTK_COMBO_BOX( gtk_builder_get_object( builder, selector_combo_box ));
                    while ( aux != NULL ){
                        char card_name[30];
                            set_card_name_cb_box( aux->l_card.suit, aux->l_card.number, card_name );
                            gtk_combo_box_text_insert( combo_box_text, count_list, aux->l_card.widget, card_name );
                        count_list++;
                        aux = aux->next;
                    }
                gtk_combo_box_set_active( combo_box, 0 );
    }

    void on_get_down_back_clicked(){        
        GtkWidget           *dialog;
        GtkComboBoxText        *combo_box_text;
        char selector_combo_box[50],temp_number[3];
        dialog = GTK_WIDGET( gtk_builder_get_object( builder, "new_game" ));
        for ( int i = 0; i < comb_amount_cards; i++ ){   
                strcpy( selector_combo_box , "combo_card_");
                sprintf( temp_number, "%i", i );
                strcat( selector_combo_box , temp_number );
            combo_box_text =  GTK_COMBO_BOX_TEXT( gtk_builder_get_object( builder, selector_combo_box ));
                gtk_combo_box_text_remove_all( combo_box_text );
        }
            gtk_widget_hide( dialog );     
    }

    void on_get_down_card_clicked(){        
        GtkComboBox        *combo_box;
        char *text_select[comb_amount_cards];   
        char selector_combo_box[50],temp_number[3];
            for( int z = 0; z < comb_amount_cards; z++ ){      
                strcpy( selector_combo_box , "combo_card_");
                sprintf( temp_number, "%i", z );
                strcat( selector_combo_box , temp_number );
                combo_box =  GTK_COMBO_BOX( gtk_builder_get_object( builder, selector_combo_box ));
                text_select[z] = (gchar*)gtk_combo_box_get_active_id (combo_box);
            }
        cards cards_to_check[comb_amount_cards];
            for( int l = 0; l < comb_amount_cards; l++ ){   
                header *aux = player[active].hand->start;
                    while( aux != NULL ){
                        if( strcmp( text_select[l], aux->l_card.widget ) == 0) {
                            cards_to_check[l] = aux->l_card;
                            break;
                        } else aux = aux->next;
                    }
                }
            int controller = cards_can_come_down( cards_to_check, comb_amount_cards );
                if( controller == 0 ) { 
                    player[active].n_games++;
                    cards_on_table( cards_to_check, comb_amount_cards );
                    check_size_render();
                    generic_log_with_name( player[active].name, "Desceu um jogo para a mesa" );
                    on_get_down_back_clicked();
                }
                if( controller == 1 ) set_dialog( "VOCÊ NÃO PODE DESCER,\nJOGO INVÁLIDO" );
                if( controller == -100 ) set_dialog( "VOCÊ NÃO PODE USAR MAIS\nQUE UM CORINGA" );
    }

    void cards_on_table( cards _cards_[], int amount ){     
        GtkGrid            *hand;
        int count_grid = list_count_size( player[active].hand, 0 );     
            if( active == 0 ) hand = GTK_GRID( gtk_builder_get_object( builder, "cards_place_p1" ));
            else hand = GTK_GRID( gtk_builder_get_object( builder, "cards_place_p2" ));
            for( int l = 0; l < amount; l++ ){  
                for( int z = 0; z < count_grid ; z++ ){   
                    if( z < 24 ) {
                        GtkWidget       *image;
                        image = gtk_grid_get_child_at( hand, z, 0 );
                        char *current_card_widget_name;
                        current_card_widget_name = (gchar*)gtk_widget_get_name( image );  
                            if( strcmp( _cards_[l].widget, current_card_widget_name ) == 0 ){  
                                int position_card;
                                    list_search_key( player[active].hand, _cards_[l], &position_card );
                                cards temp;
                                    list_remove_pos( player[active].hand, &temp, position_card );    
                                temp.active_on.hand = 0;
                                temp.active = 0;
                                    if( l == 0 ) player[active].games[player[active].n_games] = new_list();
                                list_insert( player[active].games[player[active].n_games], temp );
                                    hand_to_table( temp , player[active].n_games );
                            }
                    } else{     
                        int count_p_rows;
                        if( active == 0 ) count_p_rows = count_row2_p1;
                        else count_p_rows = count_row2_p2;
                        for(int k=0; k < count_p_rows; k++){
                            GtkWidget       *image;
                            image = gtk_grid_get_child_at( hand, k, 1 );
                            char *current_card_widget_name;
                            current_card_widget_name = (gchar*)gtk_widget_get_name( image ); 
                                if( strcmp( _cards_[l].widget, current_card_widget_name ) == 0 ){ 
                                    int position_card;
                                        list_search_key( player[active].hand, _cards_[l], &position_card );
                                    cards temp;
                                        list_remove_pos( player[active].hand, &temp, position_card );    
                                    temp.active_on.hand = 0;
                                    temp.active = 0;
                                        if( l == 0 ) player[active].games[player[active].n_games] = new_list();
                                    list_insert( player[active].games[player[active].n_games], temp );
                                        hand_to_table( temp , player[active].n_games );
                                        if( active == 0 ) count_row2_p1--;
                                        else count_row2_p2--;
                            }
                        }
                    }
                }
            }
    }

    void hand_to_table( cards temp  , int choice ){     
        GtkGrid         *table_grid;
        GtkWidget       *image;
        GdkPixbuf       *pixbuf;
        char location[50];
        int count = list_count_size ( player[active].games[player[active].n_games], 0 );
            if( active == 0 ) table_grid = GTK_GRID( gtk_builder_get_object( builder, "game_player1" ));
            else table_grid = GTK_GRID( gtk_builder_get_object( builder, "game_player2" ));
            strcpy( location, "./assets/small_cards/" );
            strcat( location, temp.image );
        pixbuf = gdk_pixbuf_new_from_file( location, NULL );
        pixbuf = gdk_pixbuf_scale_simple( pixbuf, 30, 41, GDK_INTERP_BILINEAR );
        image = gtk_image_new_from_pixbuf( pixbuf );
        gtk_widget_set_name( image, temp.widget );
            gtk_widget_show(image);
            if( choice == 0){
                gtk_grid_attach( table_grid, image, (count-1), choice, 1, 1 );
            } else if( choice == 1){
                gtk_grid_attach( table_grid, image, (count-1), choice, 1, 1 );
            } else if( choice == 2){
                gtk_grid_attach( table_grid, image, (count-1), choice, 1, 1 );
            } else if( choice == 3){
                gtk_grid_attach( table_grid, image, (count-1), choice, 1, 1 );
            } else if( choice == 4){
                gtk_grid_attach( table_grid, image, (count-1), choice, 1, 1 );
            } else if( choice == 5){
                gtk_grid_attach( table_grid, image, (count-1), choice, 1, 1 );
            } else if( choice == 6){
                gtk_grid_attach( table_grid, image, (count-1), choice, 1, 1 );
            } else if( choice == 7){
                gtk_grid_attach( table_grid, image, (count-1), choice, 1, 1 );
            } else if( choice == 8){
                gtk_grid_attach( table_grid, image, (count-1), choice, 1, 1 );
            } else if( choice == 9){
                gtk_grid_attach( table_grid, image, (count-1), choice, 1, 1 );
            }
    }

    int cards_can_come_down( cards cards_[] , int amount ){     
        int result = 0, joker, joker_position, joker_amount = 0;
            for( int i = 0; i < amount; i++ ){     
                if( cards_[i].joker == 1 ){
                    joker_amount++;
                    joker = 1;
                }
            }

            if( cards_[1].joker == 1 ){    
                if( cards_[1].number + 1 == cards_[2].number && cards_[1].suit == cards_[2].suit && cards_[1].number - 1 == cards_[0].number && cards_[1].suit == cards_[0].suit || cards_[2].joker == 1 || cards_[0].joker == 1){
                    cards_[1].joker = 0;
                    joker_amount--;
                }
            }

            if( cards_[0].joker == 1 ){     
                if( cards_[1].number == 3 && cards_[0].suit == cards_[1].suit || cards_[1].joker == 1){
                    cards_[0].joker = 0;
                    joker_amount--;
                }
            }

            if( joker_amount > 1 ){     
                return -100; 
            }

            for( int i = 0; i < amount; i++ ){  
                if( cards_[i].joker == 1 ){
                    joker_position = i;
                    break;
                } 
            }

            if( joker_amount == 1 ){    
                for( int i = 0; i < amount-1; i++ ){
                    if( cards_[i].number + 1 == cards_[i+1].number && cards_[i].suit == cards_[i+1].suit || cards_[i].joker == 1 || cards_[i+1].joker == 1 && i != amount-2 || cards_[i].number == 13 && cards_[i+1].number == 1 ) result = 0;
                    else if( i == amount-2 ){
                        if( (cards_[i].number + 1) == cards_[i+1].number && cards_[i].suit == cards_[i+1].suit || cards_[i].joker == 1 || cards_[i].number == 13 && cards_[i+1].number == 1 ) result = 0;
                        else{
                            if( cards_[i+1].joker == 1  ) result = 0;
                            else return 1;
                        }
                    }
                    else return 1;
                }
            } else{     
                for( int i = 0; i < amount-1; i++ ){
                    if( (cards_[i].number + 1) == cards_[i+1].number && cards_[i].suit == cards_[i+1].suit || cards_[i].number == 13 && cards_[i+1].number == 1 ) result = 0;
                    else return 1;
                }
            }
            return result;
    }

