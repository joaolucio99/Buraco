#ifndef DECK
#define DECK
#include "../tools/general_tools.h"
#include "../tools/structs.h"

    extern cards deck[104];
    extern cards dead1[11];
    extern cards dead2[11];
    extern int deck_amount_cards;
    extern int dead1_amount_cards;
    extern int dead2_amount_cards;
    extern list *trash;

    void set_deck_infos();

    void generate_deck();

    void shuffle();

    void deal_cards();

    void fisher_yates();

#endif    