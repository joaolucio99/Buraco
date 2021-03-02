#include "../lib/start_game.h"

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
        GtkWidget           *name_dialog;
        GtkWidget           *input_player;
        name_dialog = GTK_WIDGET( gtk_builder_get_object( builder, "dialog_name" ));    //selecionando o widget do glade para realizar demais tarefas
        input_player = GTK_WIDGET( gtk_builder_get_object( builder, input_name ));
            gtk_widget_unset_state_flags( input_player , GTK_STATE_FLAG_INSENSITIVE );      //libeirando a box para edição
        gboolean act_state = gtk_switch_get_active( state );      //pegando informação switch button
            if( act_state ){      //verificando estado botao switch
                if( strlen( name_player ) == 0 ){
                    gtk_switch_set_active( state , FALSE );     //alterando estado switch button
                    gtk_widget_show( name_dialog );       //mostrando erro não ter digitado nome
                } else{
                    gtk_switch_set_state( state, TRUE ); 
                    gtk_widget_set_state_flags( input_player , GTK_STATE_FLAG_INSENSITIVE , TRUE );        //travando a caixa de edição de nome       
                    p_ready[choice] = 1;    
                }
            }
    }

    void on_start_clicked( GtkButton *button, GtkStack *stack ){        //inicar o jogo
        if( p_ready[0] != 1 || p_ready[1] != 1 ){       //verificando se 2 jogadores estão prontos
            GtkWidget           *ready_dialog;
            ready_dialog = GTK_WIDGET( gtk_builder_get_object( builder, "dialog_ready" ));
            gtk_widget_show( ready_dialog );
        } else {
            if( strcmp( name_player1, name_player2 ) == 0 ){        //verificando se os nomes não são iguais
                GtkWidget           *cmpname_dialog;
                cmpname_dialog = GTK_WIDGET( gtk_builder_get_object( builder, "dialog_cmpname" ));
                gtk_widget_show( cmpname_dialog );
            } else {
                get_players_data( name_player1, name_player2 );        //gerando informações dos players
                //create_player_log();
                generate_deck();
                shuffle();
                set_first_player();
                deal_cards();
                gtk_stack_set_visible_child_name ( stack, "game_page" );
                turn();
            }
        }
    }