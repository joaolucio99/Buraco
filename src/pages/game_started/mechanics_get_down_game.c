#include "../../../lib/pages/game_started/mechanics_get_down_game.h"

    int comb_amount_cards = 3; //contador de labels para player add cartas no jogo

    void on_button_get_down_game_clicked(){     //abrir botao descer novo jogo
        GtkWidget           *dialog;
        dialog = GTK_WIDGET( gtk_builder_get_object( builder, "new_game" ));
            for ( int i = 0; i < comb_amount_cards; i++ ){
                get_labels_info( i );
            }
            gtk_widget_show( dialog );
    }

    void on_adjustment1_button_game_value_changed(){        //quando o valor de cartas a descer e alterado
        GtkSpinButton *spin_button;
        GtkContainer  *container;
        container = GTK_CONTAINER( gtk_builder_get_object( builder, "view_dialog" ));
        spin_button = GTK_SPIN_BUTTON( gtk_builder_get_object( builder, "change_n_cards" ));
        int value =  (int)gtk_spin_button_get_value ( spin_button );       
            if( value > comb_amount_cards ){        //verificar se vai adicionar ou remover os campos de selecionar carta
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

    void get_labels_info( int number ){                 //pegando as carta para deixar o player selecionar
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

    void on_get_down_back_clicked(){        //dialog botao de voltar
        GtkWidget           *dialog;
        GtkComboBoxText        *combo_box_text;
        char selector_combo_box[50],temp_number[3];
        dialog = GTK_WIDGET( gtk_builder_get_object( builder, "new_game" ));
        for ( int i = 0; i < comb_amount_cards; i++ ){      //removendo as infos das cartas do label
                strcpy( selector_combo_box , "combo_card_");
                sprintf( temp_number, "%i", i );
                strcat( selector_combo_box , temp_number );
            combo_box_text =  GTK_COMBO_BOX_TEXT( gtk_builder_get_object( builder, selector_combo_box ));
                gtk_combo_box_text_remove_all( combo_box_text );
        }
            gtk_widget_hide( dialog );     
    }

    void on_get_down_card_clicked(){        //dialog botao de descer jogo
        //inico etapa pegando o nome das cartas que o jogador que descer jogo
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
        //fim da etapa      

        //inicio etapa pegar as cartas que é pra ser decidas pro jogo  
        cards               cards_to_check[comb_amount_cards];
            for( int l = 0; l < comb_amount_cards; l++ ){   // for para comparar cada carta escolhida para descer pro jogo
                header *aux = player[active].hand->start;
                    while( aux != NULL ){
                        if( strcmp( text_select[l], aux->l_card.widget ) == 0) {
                            cards_to_check[l] = aux->l_card;
                            break;
                        } else aux = aux->next;
                    }
                }
        //fim da etapa

        //inicio checagem se pode descer cartas
            if( letters_can_come_down == 0){
                printf("\n\nPODE DESCER\n\n");
            } else printf("\n\nNAO PODE DESCER\n\n");
    }

    int letters_can_come_down( cards cards_to_check[] , int amount ){
        for( int i = 0; i < amount-1; i++ ){
            if( cards_to_check[i].suit == cards_to_check[i+1].suit || cards_to_check[i].joker ==1 || cards_to_check[i+1].joker == 1 ){
                if ( strcmp( cards_to_check[i].number, cards_to_check[i+1].number ) == 0 || cards_to_check[i].joker ==1 || cards_to_check[i+1].joker == 1 ){
                    return 0;
                }
            } else return 1;
        }
    }

