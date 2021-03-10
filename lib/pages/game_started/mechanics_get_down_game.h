#ifndef MECHANICS_GET_DOWN_GAME
#define MECHANICS_GET_DOWN_GAME
#include "../../tools/general_tools.h"
#include "tools.h"

    extern int comb_amount_cards;

    void on_adjustment1_button_game_value_changed();

    void get_labels_info();

    void hand_to_table();

    int cards_can_come_down();

    void cards_on_table();

    void on_button_get_down_game_clicked();

    void on_get_down_card_clicked();

    void on_get_down_back_clicked();

#endif