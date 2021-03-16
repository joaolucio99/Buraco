#include "../../../lib/pages/game_started/mechanics_hit_game.h"

    void on_win_game_clicked(){         //clicar no botao de bater   
            if( player[active].n_games+1 > 0 ){
                int clean_canasta = 1;
                clean_canasta = check_canasta();    //verificar se tem canastra limpa
                    if( clean_canasta == 0 || player[active].buy_dead == 1 && list_count_size( player[active].hand, 1 ) == -1 ){
                        generic_log_with_name( player[active].name, "Bateu" );
                        GtkStack    *stack;
                        stack = GTK_STACK( gtk_builder_get_object( builder, "all_pages" ) );
                        player[active].hit = 1;
                            count_game_score( 0 );
                            count_game_score( 1 );
                            set_display_infos();
                            end_game_log();
                            gtk_stack_set_visible_child_name ( stack, "score_page" );
                    } else set_dialog("VOCÊ NÃO ESTÁ APTO\nPARA BATER");
            } else set_dialog("VOCÊ NÃO ESTÁ APTO\nPARA BATER");
    }

    void set_display_infos(){       //mostrar na tela o vencedor e perdedor
        GtkImage           *image_loser;
        GtkImage           *image_winner;
        GtkLabel           *label_name_loser; 
        GtkLabel           *label_name_winner; 
        GtkLabel           *label_score_loser; 
        GtkLabel           *label_score_winner; 
        image_loser = GTK_IMAGE( gtk_builder_get_object( builder, "rank2_image" ));
        image_winner = GTK_IMAGE( gtk_builder_get_object( builder, "rank1_image" ));
        label_name_loser = GTK_LABEL( gtk_builder_get_object( builder, "rank2_name" ));
        label_name_winner = GTK_LABEL( gtk_builder_get_object( builder, "rank1_name" ));
        label_score_loser = GTK_LABEL( gtk_builder_get_object( builder, "rank2_score" ));
        label_score_winner = GTK_LABEL( gtk_builder_get_object( builder, "rank1_score" ));
        char score1[50];
        char score2[50];
            strcpy(score1, " - ");
            strcpy(score2, " - ");
        char temp_n1[50];
        char temp_n2[50];
            sprintf( temp_n1, "%i", player[0].score );
            sprintf( temp_n2, "%i", player[1].score );
            strcat( score1, temp_n1 );
            strcat( score2, temp_n2 );
            if( player[0].score > player[1].score ){
                gtk_image_set_from_file( image_winner , player[0].icon );
                gtk_image_set_from_file( image_loser , player[1].icon );
                gtk_label_set_text( label_name_winner , player[0].name );
                gtk_label_set_text( label_name_loser , player[1].name );
                gtk_label_set_text( label_score_winner , score1 );
                gtk_label_set_text( label_score_loser , score2 );
            }else {
                gtk_image_set_from_file( image_winner , player[1].icon );
                gtk_image_set_from_file( image_loser , player[0].icon );
                gtk_label_set_text( label_name_winner , player[1].name );
                gtk_label_set_text( label_name_loser , player[0].name );
                gtk_label_set_text( label_score_winner , score2 );
                gtk_label_set_text( label_score_loser , score1 );
            }
    }

    void count_game_score( int i ){     //contagem dos pontos de todos jogos
        int hands_count = 0;
        for( int z = 0; z < player[i].n_games+1; z++ ){
            int cards_in_game = list_count_size( player[i].games[z] , 0 );
                if( cards_in_game == 14 && check_joker_hit( player[i].games[z] ) == 1 ){
                    math_score( i, z, 1000, &hands_count, 0 );
                } else if( cards_in_game == 14 && check_joker_hit( player[i].games[z] ) == 0 ){
                    math_score( i, z, 1000, &hands_count, 1 );
                } else if( cards_in_game == 13 && check_joker_hit( player[i].games[z] ) == 1 ){
                    math_score( i, z, 500, &hands_count, 0 );
                } else if( cards_in_game == 13 && check_joker_hit( player[i].games[z] ) == 0 ){
                    math_score( i, z, 500, &hands_count, 1 );
                } else if( cards_in_game >= 7 && check_joker_hit( player[i].games[z] ) == 1 ){
                    math_score( i, z, 0, &hands_count, 0 );
                } else if( cards_in_game >= 7 && check_joker_hit( player[i].games[z] ) == 0 ){
                    math_score( i, z, 0, &hands_count, 1 );
                } else{
                    math_score( i, z, 0, &hands_count, 2 );
                }
        }
    }

    void math_score( int i, int z, int value, int *hands_count, int canasta ){  //contagem dos pontos de cada jogo
        header *aux = player[i].games[z]->start;
        int value_cards = 0;
            while( aux != NULL ){
                value_cards = value_cards + aux->l_card.value;
                aux = aux->next;
            }
        int total_value = value_cards + value;
            if( player[i].hit == 1 ) total_value = total_value + 100;
            if( canasta == 0 ) total_value = total_value + 200;
            else if( canasta == 1 ) total_value = total_value + 100;
        int cards_in_hand = list_count_size( player[active].hand , 0 );
            if( cards_in_hand != 0 && *hands_count == 0 ){
                *hands_count = 1;
                header *aux2 = player[i].hand->start;
                    while( aux2 != NULL ){
                        cards_in_hand = cards_in_hand + aux2->l_card.value;
                        aux2 = aux2->next;
                    }
            }
        total_value = total_value - cards_in_hand;
        player[i].score = player[i].score + total_value;
    }

    int check_joker_hit( list *cards_to_check ){        //checar se a coringa no jogo
        header *aux = cards_to_check->start;
            while( aux != NULL ){
                if( aux->l_card.joker == 1) return 0;
                else aux = aux->next;
            }
        return 1;
    }

    int check_canasta(){   //checar se a canastra e limpa
        for( int i = 0; i < player[active].n_games+1; i++ ){
            int lenght = list_count_size( player[active].games[i] , 0 );
                if( lenght == 14 ){
                    header *aux = player[active].games[i]->start;
                        while( aux != NULL ){
                            if( aux->l_card.joker == 1 ){
                                return 1;
                            } else{
                                aux = aux->next;
                            }
                        }
                    return 0; 
                } else return 1;
        }
    }

    void check_game_end(){      //checar se o jogo acabou
        if( game_end == 1 ){
            GtkStack    *stack;
            stack = GTK_STACK( gtk_builder_get_object( builder, "all_pages" ) );
                count_game_score( 0 );
                count_game_score( 1 );
                set_display_infos();
                end_game_log();
                gtk_stack_set_visible_child_name ( stack, "score_page" );
        }
    }

    void on_exit_game_clicked(){        //saindo do jogo e limpando as memorias alocadas
        for( int i = 0; i < 2; i++ ){
            for( int z = 0; z < player[i].n_games+1; z++ ){
                list_free( player[i].games[z] );
            }
            list_free( player[i].hand );
        }
        list_free( trash );
        gtk_main_quit();
    }

    void on_go_to_menu_clicked(){       //voltar para o menu
        GtkStack    *stack;
        stack = GTK_STACK( gtk_builder_get_object( builder, "all_pages" ) );
            for( int i = 0; i < 2; i++ ){
                for( int z = 0; z < player[i].n_games+1; z++ ){
                    list_free( player[i].games[z] );
                }
                list_free( player[i].hand );
            }
            list_free( trash );
            gtk_stack_set_visible_child_name ( stack, "init_page" );
    }