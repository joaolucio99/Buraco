#ifndef STRUCTS
#define STRUCTS

    typedef struct is_active{
        int dead1, dead2, trash, hand;
    }is_active;

    typedef struct cards{
        int suit, joker, active;
        char number[3], image[50];
        is_active active_on;
    }cards;

    typedef struct header{
        cards l_card;
        struct header *next;
    }header;

    typedef struct list{
        header *start;
    }list;

    typedef struct players{
        int score, ncard;
        char name[16],icon[30];
        list *hand;
    }players;  

#endif    