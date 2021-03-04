#ifndef GAME_STARTED_TOOLS
#define GAME_STARTED_TOOLS
#include "../../tools/general_tools.h"
#include "game_started.h"

    extern int active;
    extern int count_round;

    void set_current_player();

    void set_current_hand();

    void on_buy_card_clicked();

    void on_pass_turn_clicked();

    void on_win_game_clicked();

    void on_card_trash_clicked();

    void add_card_on_hand();

#endif