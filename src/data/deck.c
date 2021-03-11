#include "../../lib/data/deck.h"

    cards deck[104];
    cards dead1[11];
    cards dead2[11];
    list *trash;
    int deck_amount_cards=103;

    void generate_deck(){
        int number_widget[104];
                for( int i = 0; i < 104; i++ ){ //preenchendo suits
                    number_widget[i] = i;
                    if( i<26 ) deck[i].suit = 1;
                    else if( i>25 && i<52 ) deck[i].suit = 2;
                    else if( i>51 && i<78 ) deck[i].suit = 3;
                    else if( i>77 && i<104 ) deck[i].suit = 4;
                }
            fisher_yates( number_widget );
            for(int i = 0; i < 104; i++ ){ //preenchendo resto das info das cartas
                if( deck[i].suit == 1 ){
                    if( i<2 ) set_deck_infos( 1 , "_Copas.png" , 0 , i, number_widget );
                    else if( i>1 && i<4 ) set_deck_infos( 2 , "_Copas.png" , 1 ,i, number_widget );
                    else if( i>3 && i<6 ) set_deck_infos( 3 , "_Copas.png" , 0 , i, number_widget );
                    else if( i>5 && i<8 ) set_deck_infos( 4 , "_Copas.png" , 0 , i, number_widget );
                    else if( i>7 && i<10 ) set_deck_infos( 5 , "_Copas.png" , 0 , i, number_widget );
                    else if( i>9 && i<12 ) set_deck_infos( 6 , "_Copas.png" , 0 , i, number_widget );
                    else if( i>11 && i<14 ) set_deck_infos( 7 , "_Copas.png" , 0 , i, number_widget );
                    else if( i>13 && i<16 ) set_deck_infos( 8 , "_Copas.png" , 0 , i, number_widget );
                    else if( i>15 && i<18 ) set_deck_infos( 9 , "_Copas.png" , 0 , i, number_widget );
                    else if( i>17 && i<20 ) set_deck_infos( 10 , "_Copas.png" , 0 , i, number_widget );
                    else if( i>19 && i<22 ) set_deck_infos( 11 , "_Copas.png" , 0 , i, number_widget );
                    else if( i>21 && i<24 ) set_deck_infos( 12 , "_Copas.png" , 0 , i, number_widget );
                    else if( i>23 && i<26 ) set_deck_infos( 13 , "_Copas.png" , 0 , i, number_widget );
                } else if( deck[i].suit == 2 ){
                    if( i>25 && i<28 ) set_deck_infos( 1 , "_Paus.png" , 0 , i, number_widget );
                    else if( i>27 && i<30 ) set_deck_infos( 2 , "_Paus.png" , 1 ,i, number_widget );
                    else if( i>29 && i<32 ) set_deck_infos( 3 , "_Paus.png" , 0 , i, number_widget );
                    else if( i>31 && i<34 ) set_deck_infos( 4 , "_Paus.png" , 0 , i, number_widget );
                    else if( i>33 && i<36 ) set_deck_infos( 5 , "_Paus.png" , 0 , i, number_widget );
                    else if( i>35 && i<38 ) set_deck_infos( 6 , "_Paus.png" , 0 , i, number_widget );
                    else if( i>37 && i<40 ) set_deck_infos( 7 , "_Paus.png" , 0 , i, number_widget );
                    else if( i>39 && i<42 ) set_deck_infos( 8 , "_Paus.png" , 0 , i, number_widget );
                    else if( i>41 && i<44 ) set_deck_infos( 9 , "_Paus.png" , 0 , i, number_widget );
                    else if( i>43 && i<46 ) set_deck_infos( 10 , "_Paus.png" , 0 , i, number_widget );
                    else if( i>45 && i<48 ) set_deck_infos( 11 , "_Paus.png" , 0 , i, number_widget );
                    else if( i>47 && i<50 ) set_deck_infos( 12 , "_Paus.png" , 0 , i, number_widget );
                    else if( i>49 && i<52 ) set_deck_infos( 13 , "_Paus.png" , 0 , i, number_widget );
                } else if( deck[i].suit == 3 ){
                    if( i>51 && i<54 ) set_deck_infos( 1 , "_Espadas.png" , 0 , i, number_widget );
                    else if( i>53 && i<56 ) set_deck_infos( 2 , "_Espadas.png" , 1 ,i, number_widget );
                    else if( i>55 && i<58 ) set_deck_infos( 3 , "_Espadas.png" , 0 , i, number_widget );
                    else if( i>57 && i<60 ) set_deck_infos( 4 , "_Espadas.png" , 0 , i, number_widget );
                    else if( i>59 && i<62 ) set_deck_infos( 5 , "_Espadas.png" , 0 , i, number_widget );
                    else if( i>61 && i<64 ) set_deck_infos( 6 , "_Espadas.png" , 0 , i, number_widget );
                    else if( i>63 && i<66 ) set_deck_infos( 7 , "_Espadas.png" , 0 , i, number_widget );
                    else if( i>65 && i<68 ) set_deck_infos( 8 , "_Espadas.png" , 0 , i, number_widget );
                    else if( i>67 && i<70 ) set_deck_infos( 9 , "_Espadas.png" , 0 , i, number_widget );
                    else if( i>69 && i<72 ) set_deck_infos( 10 , "_Espadas.png" , 0 , i, number_widget );
                    else if( i>71 && i<74 ) set_deck_infos( 11 , "_Espadas.png" , 0 , i, number_widget );
                    else if( i>73 && i<76 ) set_deck_infos( 12 , "_Espadas.png" , 0 , i, number_widget );
                    else if( i>75 && i<78 ) set_deck_infos( 13 , "_Espadas.png" , 0 , i, number_widget );
                } else if( deck[i].suit == 4 ){
                    if( i>77 && i<80 ) set_deck_infos( 1 , "_Ouro.png" , 0 , i, number_widget );
                    else if( i>79 && i<82 ) set_deck_infos( 2 , "_Ouro.png" , 1 ,i, number_widget );
                    else if( i>81 && i<84 ) set_deck_infos( 3 , "_Ouro.png" , 0 , i, number_widget );
                    else if( i>83 && i<86 ) set_deck_infos( 4 , "_Ouro.png" , 0 , i, number_widget );
                    else if( i>85 && i<88 ) set_deck_infos( 5 , "_Ouro.png" , 0 , i, number_widget );
                    else if( i>87 && i<90 ) set_deck_infos( 6 , "_Ouro.png" , 0 , i, number_widget );
                    else if( i>89 && i<92 ) set_deck_infos( 7 , "_Ouro.png" , 0 , i, number_widget );
                    else if( i>91 && i<94 ) set_deck_infos( 8 , "_Ouro.png" , 0 , i, number_widget );
                    else if( i>93 && i<96 ) set_deck_infos( 9 , "_Ouro.png" , 0 , i, number_widget );
                    else if( i>95 && i<98 ) set_deck_infos( 10 , "_Ouro.png" , 0 , i, number_widget );
                    else if( i>97 && i<100 ) set_deck_infos( 11 , "_Ouro.png" , 0 , i, number_widget );
                    else if( i>99 && i<102 ) set_deck_infos( 12 , "_Ouro.png" , 0 , i, number_widget );
                    else if( i>101 && i<104 ) set_deck_infos( 13 , "_Ouro.png" , 0 , i, number_widget );
                };
            }
    }

    void set_deck_infos( int number , char *location , int joker , int i, int number_widget[] ){   
        char number_[3], location_[50], final[50], temp_number[4], temp[50], temp_number_deck[3];
            sprintf( temp_number_deck, "%i", number ); 
                if( number == 1) strcpy( number_, "A" );
                else if( number > 1 && number < 11) strcpy( number_, temp_number_deck );
                else if( number == 11 ) strcpy( number_, "J" );
                else if( number == 12 ) strcpy( number_, "Q" );
                else if( number == 13 ) strcpy( number_, "K" );
            strcpy( location_, location );
            deck[i].number = number;            
            strcpy( final, number_ );
            strcat( final, location_ );
            strcpy( deck[i].image, final );
            strcpy( temp, deck[i].image );      //salvando localizao da imagem temporariamente
            strcat( temp, "*" );
            sprintf( temp_number, "%i", number_widget[i] );     //convertendo numero aleatorio em string
            strcat( temp, temp_number );
            strcpy( deck[i].widget, temp );
        deck[i].active = 0;
        deck[i].joker = joker;
    }

    void shuffle(){         //função embaralhar usando Fisher–Yates
        int i = 104, j;
        srand( time(NULL) );
        cards temp;
            while( --i > 0 ){
                j = rand() % i;
                temp = deck[j];
                deck[j] = deck[i];
                deck[i] = temp;
            }
    }

    void deal_cards(){
            for( int i = 0; i < 14; i++){
                deck[i].active = 1;
                deck[i].active_on.hand = 1;
                if( i == 0) list_insert( player[first_player[0]].hand, deck[0] );
                else if ( i == 1 ) list_insert( player[first_player[0]].hand, deck[1] );
                else if ( i == 2 ) list_insert( player[first_player[0]].hand, deck[2] );
                else if ( i == 3 ) list_insert( player[first_player[0]].hand, deck[4] );
                else if ( i == 4 ) list_insert( player[first_player[0]].hand, deck[6] );
                else if ( i == 5 ) list_insert( player[first_player[0]].hand, deck[8] );
                else if ( i == 6 ) list_insert( player[first_player[0]].hand, deck[10] );
                else if ( i == 7 ) list_insert( player[first_player[0]].hand, deck[12] );
                else if ( i == 8 ) list_insert( player[first_player[0]].hand, deck[14] );
                else if ( i == 9 ) list_insert( player[first_player[0]].hand, deck[16] );
                else if ( i == 10 ) list_insert( player[first_player[0]].hand, deck[18] );
                else if ( i == 11 ) list_insert( player[first_player[0]].hand, deck[20] );
                else if ( i == 12 ) list_insert( player[first_player[0]].hand, deck[22] );
                else if ( i == 13 ) list_insert( player[first_player[0]].hand, deck[24] );
            }
            for( int i = 0; i < 14; i++){
                deck[i].active = 1;
                deck[i].active_on.hand = 1;
                if( i == 0) list_insert( player[first_player[1]].hand, deck[52] );
                else if ( i == 1 ) list_insert( player[first_player[1]].hand, deck[53] );
                else if ( i == 2 ) list_insert( player[first_player[1]].hand, deck[54] );
                else if ( i == 3 ) list_insert( player[first_player[1]].hand, deck[56] );
                else if ( i == 4 ) list_insert( player[first_player[1]].hand, deck[58] );
                else if ( i == 5 ) list_insert( player[first_player[1]].hand, deck[60] );
                else if ( i == 6 ) list_insert( player[first_player[1]].hand, deck[62] );
                else if ( i == 7 ) list_insert( player[first_player[1]].hand, deck[64] );
                else if ( i == 8 ) list_insert( player[first_player[1]].hand, deck[66] );
                else if ( i == 9 ) list_insert( player[first_player[1]].hand, deck[68] );
                else if ( i == 10 ) list_insert( player[first_player[1]].hand, deck[70] );
                else if ( i == 11 ) list_insert( player[first_player[1]].hand, deck[72] );
                else if ( i == 12 ) list_insert( player[first_player[1]].hand, deck[74] );
                else if ( i == 13 ) list_insert( player[first_player[1]].hand, deck[76] );
            }
            /*for( int i = 103; i > 92; i--){
                deck[i].active = 1;
                deck[i].active_on.hand = 1;
                    list_insert( player[first_player[0]].hand, deck[i] );
            }
            for( int i = 92; i > 81; i--){
                deck[i].active = 1;
                deck[i].active_on.hand = 1;
                    list_insert( player[first_player[1]].hand, deck[i] );
            }*/
        int count = 10;
            for( int i = 81; i > 70 ; i-- ){
                deck[i].active = 1;
                deck[i].active_on.dead1 = 1;
                dead1[count] = deck[i];
                count--;
            }
        count = 10;
            for( int i = 70; i > 59 ; i-- ){
                deck[i].active = 1;
                deck[i].active_on.dead2 = 1;
                dead2[count] = deck[i];
                count--;
            }
        deck_amount_cards = 59;
    }

    void fisher_yates( int number[] ){
        int i = 104, j;
        srand( time(NULL) );
        int temp;
            while( --i > 0 ){
                j = rand() % i;
                temp = number[j];
                number[j] = number[i];
                number[i] = temp;
            }
    }