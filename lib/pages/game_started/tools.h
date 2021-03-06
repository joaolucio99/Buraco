#ifndef GAME_STARTED_TOOLS
#define GAME_STARTED_TOOLS
#include "../../tools/general_tools.h"
#include "game_started.h"
#include "mechanics_trash.h"
#include "mechanics_discart.h"
#include "mechanics_edit_game.h"
#include "mechanics_get_down_game.h"
#include "mechanics_hit_game.h"
#include "logs.h"

    extern int active;
    extern int count_round;
    extern int count_row2_p1;
    extern int count_row2_p2;
    extern int game_end;
    extern int deaths[2];

    void set_current_player();

    void set_current_hand();

    void on_buy_card_clicked();

    void on_pass_turn_clicked();

    void on_win_game_clicked();

    void check_game_end();

    void on_buy_dead_clicked();

    void add_card_on_hand();

    void check_size_render();

    void size_configs();

    void add_card_size_config();

#endif