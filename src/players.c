#include "../lib/players.h"

    players player[2];

    void get_players_data( players player[2] , char name_player1[16] , char name_player2[16] ){
            for( int i = 0; i < 2; i++ ){
                    if( i == 0 ) strncpy( player[i].name, name_player1 , 16);
                    else strncpy( player[i].name, name_player2 , 16);
                player[i].ncard = 0;
                player[i].score = 0;
            }
    }

