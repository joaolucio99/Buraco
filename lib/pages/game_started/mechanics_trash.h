#ifndef MECHANICS_TRASH
#define MECHANICS_TRASH
#include "../../tools/general_tools.h"
#include "tools.h"
#include "game_started.h"
#include "mechanics_discart.h"

    extern int row_trash[5];

    void on_card_trash_clicked();

    void on_trash_back_clicked();

    void on_see_trash_clicked();

    void add_card_trash_view();

    void on_buy_trash_clicked();

    void add_card_trash_to_hand();

    void del_card_trash();

#endif