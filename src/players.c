#include "../lib/players.h"

    players player[2];

    void get_players_data( char name_player1[16] , char name_player2[16] ){
            for( int i = 0; i < 2; i++ ){
                    if( i == 0 ) strncpy( player[i].name, name_player1 , 16);
                    else strncpy( player[i].name, name_player2 , 16);
                player[i].ncard = 0;
                player[i].score = 0;
            }
    }

    void get_player_name_log( char *final , int i ){
        char player_name[16];
        char result[128]="Jogador com Nickname: ";
            strcpy(player_name,player[i].name);
            strcat(result,player_name);
            strcat(result," - criado em ");
            strcpy(final,result);
    }

    void create_player_log(){
        FILE *player_log;
            for(int i=0;i<2;i++){
                char system_date[30];
                char player_text[128];
                char final_text[256];
                    get_player_name_log( player_text , i);
                    get_date(&system_date);
                    strcpy(final_text,player_text);
                    strcat(final_text,system_date);
                    strcat(final_text,"\n");
                player_log = fopen("./logs/players_log.txt","a");
                    if(player_log == NULL) printf("\n\nNao conseguiu abrir o arquivo\n\n");        //tratar erro se arquivo nao for aberto
                int result = fputs(final_text,player_log);
                    if(result == EOF) printf("\n\nNao conseguiu realizar a gravação\n\n");
            }
        fclose(player_log);
    }
