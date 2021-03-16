#include "../../../lib/pages/game_started/logs.h"

    void turn_log( int count_round_text, char *name ){      
        FILE *match_log;
        char system_date[30];
        char final_text[256];
        char temp_number[20];
            sprintf( temp_number, "%i", count_round_text );
            get_date( &system_date );
            strcpy( final_text, system_date );
            strcat( final_text, " - Turno ");
            strcat( final_text, temp_number );
            strcat( final_text, " - Player ");
            strcat( final_text, name );
            strcat( final_text, " \n");
        match_log = fopen( "./logs/match_log.txt", "a" );
            if( match_log == NULL ) printf( "\n\nNao conseguiu abrir o arquivo\n\n" );       
        int result = fputs( final_text, match_log );
            if( result == EOF ) printf( "\n\nNao conseguiu realizar a gravação\n\n" );
            fclose( match_log );
    }

    void generic_log_with_name( char *name, char *text ){
        FILE *match_log;
        char system_date[30];
        char final_text[256];
            get_date( &system_date );
            strcpy( final_text, system_date );
            strcat( final_text, " - Player ");
            strcat( final_text, name );
            strcat( final_text, " " );
            strcat( final_text, text );
            strcat( final_text, " \n" );
        match_log = fopen( "./logs/match_log.txt", "a" );
            if( match_log == NULL ) printf( "\n\nNao conseguiu abrir o arquivo\n\n" );       
        int result = fputs( final_text, match_log );
            if( result == EOF ) printf( "\n\nNao conseguiu realizar a gravação\n\n" );
            fclose( match_log );
    }

    void generic_log( char *text ){
        FILE *match_log;
        char system_date[30];
        char final_text[256];
            get_date( &system_date );
            strcpy( final_text, system_date );
            strcat( final_text, " - ");
            strcat( final_text, text );
            strcat( final_text, " \n" );
        match_log = fopen( "./logs/match_log.txt", "a" );
            if( match_log == NULL ) printf( "\n\nNao conseguiu abrir o arquivo\n\n" );       
        int result = fputs( final_text, match_log );
            if( result == EOF ) printf( "\n\nNao conseguiu realizar a gravação\n\n" );
            fclose( match_log );
    }

    void end_game_log(){
            generic_log( "PARTIDA FINALIZADA" );
        FILE *match_log;
        char system_date[30];
        char final_text[256];
            get_date( &system_date );
            strcpy( final_text, system_date );
            strcat( final_text, " - ");
            strcat( final_text, "Jogador vencedor " );
                if( player[0].score > player[1].score ) strcat( final_text, player[0].name );
                else strcat( final_text, player[1].name );
            strcat( final_text, " \n" );
        match_log = fopen( "./logs/match_log.txt", "a" );
            if( match_log == NULL ) printf( "\n\nNao conseguiu abrir o arquivo\n\n" );       
        int result = fputs( final_text, match_log );
            if( result == EOF ) printf( "\n\nNao conseguiu realizar a gravação\n\n" );
            fclose( match_log );
    }