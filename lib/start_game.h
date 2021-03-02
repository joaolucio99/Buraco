#ifndef START_GAME
#define START_GAME
#include "tools.h"
#include "game_started.h"

    extern char name_player1[16];
    extern char name_player2[16];
    extern int p_ready[2];

    void control_inp_names();

    void on_switch_button1_state_set();

    void on_switch_button2_state_set();

    void on_player1_input_name_changed();

    void on_player2_input_name_changed();

    void on_start_clicked();

#endif