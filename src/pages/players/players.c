#include "../../../lib/pages/players/players.h"

    void on_start_clicked( GtkButton *button, GtkStack *stack ){        //inicar o jogo
        if( p_ready[0] != 1 || p_ready[1] != 1 ){       //verificando se 2 jogadores estão prontos
            set_dialog( "VOCÊ NÃO PODE INICIAR SEM QUE OS\nDOIS JOGADORES ESTEJAM PRONTOS" );
        } else {
            if( strcmp( name_player1, name_player2 ) == 0 ){        //verificando se os nomes não são iguais
                set_dialog( "VOCÊ NÃO PODE INICIAR COM O NOME\nDOS DOIS JOGADORES IGUAIS" );
            } else {
                get_players_data( name_player1, name_player2 );        //gerando informações dos players
                //create_player_log();
                generate_deck();
                //shuffle();
                set_first_player();
                deal_cards();
                gtk_stack_set_visible_child_name ( stack, "game_page" );
                set_hand( 0 );
                set_hand( 1 );
                trash = new_list();
                turn();
            }
        }
    }