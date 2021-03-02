#ifndef DECK
#define DECK
#include "tools.h"
#include "structs.h"

    extern cards deck[104];
    extern cards dead1[11];
    extern cards dead2[11];
    extern int deck_amount_cards;

    void set_deck_infos();

    void generate_deck();

    void shuffle();

    void deal_cards();

#endif    