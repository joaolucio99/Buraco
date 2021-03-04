#include "../../../lib/pages/game_started/game_started.h"

    void turn(){        //responsavel pelo controle de turnos no jogo
            if( count_round == 0 ){
                if( first_player[0] == 0) active = 0;
                else active = 1;
            }
        set_current_player( player[active].icon, player[active].name );
        set_current_hand();
        count_round++;
    }