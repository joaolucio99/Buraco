#include "../../../lib/pages/game_started/mechanics_edit_game.h"

    void on_button_edit_game_clicked(){     //clicar no botao de editar o jogo
        if( player[active].n_games != -1 ){
            GtkWidget              *dialog;
            GtkComboBoxText        *combo_box_text_games;       //jogo a selecionar
            GtkComboBox            *combo_box_games;
            GtkComboBoxText        *combo_box_text_hcards;  //cartas da mao
            GtkComboBox            *combo_box_hcards;
            int games_size = player[active].n_games+1;
            int count_list_games = 0;
            int count_list_gcards = 0;
            int count_list_hcards = 0;
            combo_box_text_games =  GTK_COMBO_BOX_TEXT( gtk_builder_get_object( builder, "game_to_edit" )); //selecionando a lista de texto que vai manipular
            combo_box_games =  GTK_COMBO_BOX( gtk_builder_get_object( builder, "game_to_edit" ));
            combo_box_text_hcards =  GTK_COMBO_BOX_TEXT( gtk_builder_get_object( builder, "card_to_add" ));
            combo_box_hcards =  GTK_COMBO_BOX( gtk_builder_get_object( builder, "card_to_add" ));
            dialog = GTK_WIDGET( gtk_builder_get_object( builder, "edit_game" ));        
                for( int i = 0; i < games_size; i++ ){      //aadicionando na lista de jogos editaveis
                    char game_name[30], id[10];
                        set_game_name_cb_box( game_name, i, id );
                        gtk_combo_box_text_insert( combo_box_text_games, count_list_games, id, game_name );
                    count_list_games++;
                }
                gtk_combo_box_set_active( combo_box_games, 0 );         
            header *aux = player[active].hand->start;          //adicionando na lista de cartas da mao para descer mesa
                while ( aux != NULL ){
                        char card_name[30];
                            set_card_name_cb_box( aux->l_card.suit, aux->l_card.number, card_name );
                            gtk_combo_box_text_insert( combo_box_text_hcards, count_list_hcards, aux->l_card.widget, card_name );
                        count_list_hcards++;
                        aux = aux->next;
                }
                gtk_combo_box_set_active( combo_box_hcards, 0 );
                gtk_widget_show( dialog );
        } else set_dialog( "VOCÊ NÃO PODE EDITAR JOGOS,\nPOIS VOCÊ NÂO TEM NENHUM" );
    }

    void on_game_to_edit_changed(){         //quando trocar o jogo para editar
        GtkComboBoxText        *combo_box_text_games;       
        GtkComboBox            *combo_box_games;
        GtkComboBoxText        *combo_box_text_gcards;
        GtkComboBox            *combo_box_gcards;
        combo_box_text_games =  GTK_COMBO_BOX_TEXT( gtk_builder_get_object( builder, "game_to_edit" )); //selecionando a lista de texto que vai manipular
        combo_box_games =  GTK_COMBO_BOX( gtk_builder_get_object( builder, "game_to_edit" ));
        combo_box_text_gcards =  GTK_COMBO_BOX_TEXT( gtk_builder_get_object( builder, "position_card_add" ));
        combo_box_gcards =  GTK_COMBO_BOX( gtk_builder_get_object( builder, "position_card_add" ));
        int count_list_gcards = 0;
        int position = gtk_combo_box_get_active ( combo_box_games );
            gtk_combo_box_text_remove_all( combo_box_text_gcards );
        header *aux = player[active].games[position]->start; 
            if( count_list_gcards == 0 ) {      //adiconando a opção de inserir carta no inicio
                    gtk_combo_box_text_insert( combo_box_text_gcards, count_list_gcards, "0", "Adicionar no início" );
                    count_list_gcards++;
                }
            while ( aux != NULL ){
                    char card_name[30];
                        set_card_name_cb_box( aux->l_card.suit, aux->l_card.number, card_name );
                        gtk_combo_box_text_insert( combo_box_text_gcards, count_list_gcards, aux->l_card.widget, card_name );
                    count_list_gcards++;
                    aux = aux->next;
                }
            gtk_combo_box_set_active( combo_box_gcards, 0 );
    }

    void on_edit_down_card_clicked(){
        
    }

    void set_game_name_cb_box( char *game_name, int number, char*game_id ){     //definir nome e id de cada jogo na lista
        char temp_number[4], temp_string[30], temp_id[10];
            sprintf( temp_number, "%i", number+1 ); 
            sprintf( temp_id, "%i", number ); 
            strcpy( temp_string, "Jogo " );
            strcat( temp_string, temp_number );
            strcpy( game_name , temp_string );
            strcpy( game_id , temp_id );
    }

    void on_edit_down_back_clicked(){       //fechar dialog de editar jogo
        GtkWidget              *dialog;
        GtkComboBoxText        *combo_box_text_games;       //jogo a selecionar
        GtkComboBoxText        *combo_box_text_gcards;  //cartas dos jogos
        GtkComboBoxText        *combo_box_text_hcards;  //cartas da mao
        combo_box_text_games =  GTK_COMBO_BOX_TEXT( gtk_builder_get_object( builder, "game_to_edit" ));
        combo_box_text_gcards =  GTK_COMBO_BOX_TEXT( gtk_builder_get_object( builder, "position_card_add" ));
        combo_box_text_hcards =  GTK_COMBO_BOX_TEXT( gtk_builder_get_object( builder, "card_to_add" ));
        dialog = GTK_WIDGET( gtk_builder_get_object( builder, "edit_game" ));
            gtk_combo_box_text_remove_all( combo_box_text_games );
            gtk_combo_box_text_remove_all( combo_box_text_gcards );
            gtk_combo_box_text_remove_all( combo_box_text_hcards );
            gtk_widget_hide( dialog );
    }