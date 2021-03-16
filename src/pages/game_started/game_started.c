#include "../../../lib/pages/game_started/game_started.h"

    void turn(){        
            if( count_round == 0 ){
                if( first_player[0] == 0) active = 0;
                else active = 1;
            }
        turn_log( count_round, player[active].name );
        set_current_player( player[active].icon, player[active].name );
        check_size_render();
        set_current_hand();
        check_game_end();
        count_round++;
    }