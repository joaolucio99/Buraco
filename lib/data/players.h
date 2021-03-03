#ifndef PLAYERS
#define PLAYERS
#include "../tools/general_tools.h"
#include "../tools/structs.h"

    extern players player[2];
    extern int first_player[2];

    void get_players_data();

    void get_player_name_log();

    void create_player_log();

    void set_first_player();

#endif    