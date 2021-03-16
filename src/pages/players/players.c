#include "../../../lib/pages/players/players.h"

    void on_start_clicked( GtkButton *button, GtkStack *stack ){        
        if( p_ready[0] != 1 || p_ready[1] != 1 ){       
            set_dialog( "VOCÊ NÃO PODE INICIAR SEM QUE OS\nDOIS JOGADORES ESTEJAM PRONTOS" );
        } else {
            if( strcmp( name_player1, name_player2 ) == 0 ){        
                set_dialog( "VOCÊ NÃO PODE INICIAR COM O NOME\nDOS DOIS JOGADORES IGUAIS" );
            } else {
                get_players_data( name_player1, name_player2 );        
                create_player_log();
                generate_deck();
                shuffle();
                set_first_player();
                deal_cards();
                gtk_stack_set_visible_child_name ( stack, "game_page" );
                set_hand( 0 );
                set_hand( 1 );
                trash = new_list();
                log_start_round();
                turn();
            }
        }
    }

    void log_start_round(){   
        FILE *match_log;
            char system_date[30];
            char final_text[256];
                get_date( &system_date );
                strcpy( final_text, system_date );
                strcat( final_text, " - PARTIDA INICIADA\n");
            match_log = fopen( "./logs/match_log.txt", "a" );
                    if( match_log == NULL ) printf( "\n\nNao conseguiu abrir o arquivo\n\n" );        //tratar erro se arquivo nao for aberto
            int result = fputs( final_text, match_log );
                if( result == EOF ) printf( "\n\nNao conseguiu realizar a gravação\n\n" );
        fclose( match_log );
    }