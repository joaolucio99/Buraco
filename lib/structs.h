#ifndef STRUCTS
#define STRUCTS

    typedef struct players{
        int score,ncard;
        char name[16];
    }players;  

    typedef struct cards{
        int suit,joker,active;
        char number[3],image[50];
    }cards;

#endif    