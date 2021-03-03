#ifndef GAME_STARTED_TOOLS
#define GAME_STARTED_TOOLS
#include "../../tools/general_tools.h"
#include "game_started.h"

    extern int active;
    extern int count_round;

    void set_current_player();

    void on_pass_turn_clicked();

    void on_win_game_clicked();

    void set_current_hand();

#endif