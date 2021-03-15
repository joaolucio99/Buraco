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

    void on_edit_down_card_clicked(){
        GtkComboBox            *combo_box_games;
        GtkComboBox            *combo_box_position_choice;
        GtkComboBox            *combo_box_hcards;
        GtkComboBoxText        *combo_box_text_games;       //jogo a selecionar
        GtkComboBoxText        *combo_box_text_hcards;
        GtkWidget              *dialog;
        cards card_to_add;      //carta que vai ser adicionada no jogo
        combo_box_games =  GTK_COMBO_BOX( gtk_builder_get_object( builder, "game_to_edit" ));
        combo_box_position_choice =  GTK_COMBO_BOX( gtk_builder_get_object( builder, "position_card_add" ));
        combo_box_hcards =  GTK_COMBO_BOX( gtk_builder_get_object( builder, "card_to_add" ));
        combo_box_text_games =  GTK_COMBO_BOX_TEXT( gtk_builder_get_object( builder, "game_to_edit" ));
        combo_box_text_hcards =  GTK_COMBO_BOX_TEXT( gtk_builder_get_object( builder, "card_to_add" ));
        dialog = GTK_WIDGET( gtk_builder_get_object( builder, "edit_game" ));
        int position_game = gtk_combo_box_get_active ( combo_box_games );        //pegando posição de qual jogo a pessoa quer adicionar
        int choice_position = gtk_combo_box_get_active ( combo_box_position_choice );        //pegando a opção escolhida de adicionar ou remover
        int position_card_toadd = gtk_combo_box_get_active ( combo_box_hcards );        //pegando posição carta quer adicionar 
            list_search_pos( player[active].hand, &card_to_add, position_card_toadd );  //definindo a carta que quer adicionar
            check_joker( position_game );       //função verificar se o dois que esta no jogo é um coringa
            check_card_to_down( card_to_add, position_game, choice_position, position_card_toadd );
            check_render_game_all();
            check_size_render();
            gtk_combo_box_text_remove_all( combo_box_text_games );
            gtk_combo_box_text_remove_all( combo_box_text_hcards );
            gtk_widget_hide( dialog );
    }

    int check_card_to_down( cards card_to_add, int position_game, int choice, int position_card_toadd ){      //função verificar cartas se pode descer
        if( choice == 0 ){ //adicionar inicio do jogo
            if( card_to_add.joker == 1 ){   //se a carta adicionar for coringa
                if( count_joker( position_game ) == 0 || card_to_add.number == player[active].games[position_game]->start->l_card.number-1 && card_to_add.suit == player[active].games[position_game]->start->l_card.suit ){   //verficando se tem algum coringa no jogo
                    if( player[active].games[position_game]->start->l_card.number != 1 ){       //se nao esta adicionando antes do AS
                        cards temp;
                            list_remove_pos( player[active].hand, &temp, position_card_toadd );
                            list_insert_pos( player[active].games[position_game] , temp, 0 );
                    } else set_dialog( "VOCÊ NÃO PODE ADICIONAR\nANTES DO ÁS" );
                } else set_dialog( "VOCÊ NÃO PODE USAR\nDOIS CORINGAS" );
            } else{     //se a carta adicionar nao for coringa
                if( player[active].games[position_game]->start->l_card.number != 1 ){
                    header *aux = player[active].games[position_game]->start;
                        if( card_to_add.number == aux->l_card.number-1 && card_to_add.suit == aux->l_card.suit || aux->l_card.joker == 1 && card_to_add.number == aux->next->l_card.number-2 && card_to_add.suit == aux->next->l_card.suit ){
                            cards temp;
                                list_remove_pos( player[active].hand, &temp, position_card_toadd );
                                list_insert_pos( player[active].games[position_game] , temp, 0 );
                        } else set_dialog( "CARTA INVÁLIDA PARA\nO JOGO ATUAL" );
                } else set_dialog( "VOCÊ NÃO PODE ADICIONAR\nANTES DO ÁS" );
            }
        } 
        else if( choice == 1 ){   //adicionar no fim
            int count_cards = list_count_size( player[active].games[position_game], 0 );
            cards ref,ref2;
                list_search_pos( player[active].games[position_game] , &ref, count_cards-1 );  
                list_search_pos( player[active].games[position_game] , &ref2, count_cards-2 );
                if( card_to_add.joker == 1 ){       //se a carta adicionar e coringa
                    if( count_joker( position_game ) == 0 ){
                        if( ref.number != 1 ){
                            cards temp;
                                list_remove_pos( player[active].hand, &temp, position_card_toadd );
                                list_insert( player[active].games[position_game], temp );
                        } else set_dialog( "VOCÊ NÃO PODE ADICIONAR\nAPÓS DO ÁS" );
                    } else set_dialog( "VOCÊ NÃO PODE USAR\nDOIS CORINGAS" );
                } else{
                    if( ref.number != 1 ){
                        if( card_to_add.number-1 == ref.number && card_to_add.suit == ref.suit && ref.joker != 1 || ref.joker == 1 && card_to_add.number-2 == ref2.number && card_to_add.suit == ref2.suit ){
                            cards temp;
                                list_remove_pos( player[active].hand, &temp, position_card_toadd );
                                list_insert( player[active].games[position_game] , temp);
                        } else set_dialog( "CARTA INVÁLIDA PARA\nO JOGO ATUAL" );
                    } else set_dialog( "VOCÊ NÃO PODE ADICIONAR\nAPÓS DO ÁS" );
                }

        } 
        else if( choice == 2 ){   //remover coringa e adicionar carta
            if( count_joker(position_game) != 0 ){
                header *aux = player[active].games[position_game]->start;
                int joker_position = 0;
                int list_lenght = list_count_size( player[active].games[position_game] );
                    while( aux != NULL ){   //decobrindo posição coringa
                        if( aux->l_card.joker == 1){
                            break;
                        } else{
                            joker_position++;
                            aux = aux->next;
                        }
                    }
                cards after_joker, before_joker;
                    if( joker_position == 0 ){      //se o coringa estiver no inico do jogo
                        list_search_pos( player[active].games[position_game], &after_joker, joker_position+1);
                            if( card_to_add.number+1 == after_joker.number && card_to_add.suit == after_joker.suit || card_to_add.joker == 1 ){
                                cards temp_hand, temp_game;
                                list_remove_pos( player[active].hand, &temp_hand, position_card_toadd );  //removendo carta da mao
                                list_remove_pos( player[active].games[position_game], &temp_game, 0 );  //removendo do jogo
                                list_insert_pos( player[active].games[position_game] , temp_hand, 0 );  //inserindo no jogo a carta da mao
                                list_insert( player[active].hand, temp_game ); //inserindo na mao a carta do jogo
                            } else set_dialog( "CARTA INVÁLIDA PARA\nO JOGO ATUAL" );
                    }
                    else if( joker_position == list_lenght - 1 ) {  //coringa tiver no final
                        list_search_pos( player[active].games[position_game], &before_joker, joker_position-1);
                            if( card_to_add.number-1 == before_joker.number && card_to_add.suit == before_joker.suit || card_to_add.number == 1 && before_joker.number == 13 || card_to_add.joker == 1 ){
                                cards temp_hand, temp_game;
                                list_remove_pos( player[active].hand, &temp_hand, position_card_toadd );
                                list_remove( player[active].games[position_game], &temp_game );
                                list_insert( player[active].games[position_game], temp_hand );
                                list_insert( player[active].hand, temp_game );
                            } else set_dialog( "CARTA INVÁLIDA PARA\nO JOGO ATUAL" );
                    }
                    else{   //coringa tiver no meio
                        list_search_pos( player[active].games[position_game], &after_joker, joker_position+1);
                        list_search_pos( player[active].games[position_game], &before_joker, joker_position-1);
                            if( before_joker.number == 12 && after_joker.number == 1 && card_to_add.number == 13){
                                cards temp_hand, temp_game;
                                    list_remove_pos( player[active].hand, &temp_hand, position_card_toadd );
                                    list_remove_pos( player[active].games[position_game], &temp_game, joker_position );
                                    list_insert_pos( player[active].games[position_game] , temp_hand, joker_position );
                                    list_insert( player[active].hand, temp_game );
                            } else if ( card_to_add.number-1 == before_joker.number && card_to_add.number+1 == after_joker.number && card_to_add.suit == before_joker.suit && card_to_add.suit == after_joker.suit || card_to_add.joker == 1 ){
                                cards temp_hand, temp_game;
                                    list_remove_pos( player[active].hand, &temp_hand, position_card_toadd );
                                    list_remove_pos( player[active].games[position_game], &temp_game, joker_position );
                                    list_insert_pos( player[active].games[position_game] , temp_hand, joker_position );
                                    list_insert( player[active].hand, temp_game );
                            } else set_dialog( "CARTA INVÁLIDA PARA\nO JOGO ATUAL" );
                    }
            } else set_dialog( "NÃO TEM CORINGA NO JOGO\nATUAL PARA SER REMOVIDO" );
        }
    }

    void check_render_game_all(){
        GtkGrid         *player_game_grid;
        GtkWidget       *image;
        GdkPixbuf       *pixbuf;
            if( active == 0 ) player_game_grid = GTK_GRID( gtk_builder_get_object( builder, "game_player1" ) );
            else player_game_grid = GTK_GRID( gtk_builder_get_object( builder, "game_player2" ) );
            for( int i = 0; i < player[active].n_games+1; i++ ){
                    GtkWidget *image_remove;
                    int count_images = 0;
                    image_remove = gtk_grid_get_child_at( player_game_grid, count_images, i );
                        while( image_remove != NULL ){
                            if( count_images == 0 ){
                                gtk_widget_destroy( image_remove );
                                count_images++;
                            } else{
                                image_remove = gtk_grid_get_child_at( player_game_grid, count_images, i );
                                gtk_widget_destroy( image_remove );
                                count_images++;
                            }
                        }
            }
            for( int i = 0; i < player[active].n_games+1; i++ ){      
                header *aux = player[active].games[i]->start;
                int count_column = 0;
                    while( aux != NULL ){
                            char location[50];
                            strcpy( location, "./assets/small_cards/" );
                            strcat( location, aux->l_card.image );
                        pixbuf = gdk_pixbuf_new_from_file( location, NULL );
                        pixbuf = gdk_pixbuf_scale_simple( pixbuf, 30, 41, GDK_INTERP_BILINEAR );
                        image = gtk_image_new_from_pixbuf( pixbuf );
                            gtk_widget_set_name( image, aux->l_card.widget );
                            gtk_widget_show( image );
                            gtk_grid_attach( player_game_grid, image, count_column, i, 1, 1 );
                        count_column++;
                        aux = aux->next;
                    }
            }
    }

    int count_joker( int position_game ){       // ver se tem coringa no jogo
        header *aux = player[active].games[position_game]->start;
            while( aux != NULL ){
                if( aux->l_card.joker == 1) return 1;
                else aux = aux->next;
            }
        return 0;
    }

    void check_joker( int position_game ){          //verificar cartas do jogo pra analisar se carta atual como coringa ou não
        int count_list = list_count_size ( player[active].games[position_game], 0 );
        header *aux = player[active].games[position_game]->start;
        int count=0;
            while( aux != NULL && count < count_list-1 ){
                    if( aux->l_card.joker == 1 ){
                        if( aux->l_card.suit == aux->next->l_card.suit && aux->l_card.number+1 == aux->next->l_card.number || aux->next->l_card.joker == 1 ){       //verificar se a carta esta como coringa
                            if( count != 0 ){
                                    cards temp;
                                        list_remove_pos( player[active].games[position_game], &temp, count );
                                    temp.joker = 0;
                                        list_insert_pos( player[active].games[position_game], temp, count );
                            } else{
                                if( aux->l_card.suit == aux->next->next->l_card.suit && aux->l_card.number+2 == aux->next->next->l_card.number ){
                                    cards temp;
                                    list_remove_pos( player[active].games[position_game], &temp, count );
                                    temp.joker = 0;
                                    list_insert_pos( player[active].games[position_game], temp, count );
                                }
                            }        
                        }
                    }
                aux = aux->next;
                count++;
            }
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
        GtkComboBoxText        *combo_box_text_hcards;  //cartas da mao
        combo_box_text_games =  GTK_COMBO_BOX_TEXT( gtk_builder_get_object( builder, "game_to_edit" ));
        combo_box_text_hcards =  GTK_COMBO_BOX_TEXT( gtk_builder_get_object( builder, "card_to_add" ));
        dialog = GTK_WIDGET( gtk_builder_get_object( builder, "edit_game" ));
            gtk_combo_box_text_remove_all( combo_box_text_games );
            gtk_combo_box_text_remove_all( combo_box_text_hcards );
            gtk_widget_hide( dialog );
    }