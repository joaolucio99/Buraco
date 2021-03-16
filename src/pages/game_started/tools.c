#include "../../../lib/pages/game_started/tools.h"
    
    int active;   
    int count_round = 0;  
    int count_row2_p1 = 0;     
    int count_row2_p2 = 0;      
    int deaths[2] = { 0, 0 };      
    int game_end = 0;       

    void set_current_player( char *location, char *name ){      
        GtkImage           *image;
        GtkLabel           *label; 
        image = GTK_IMAGE( gtk_builder_get_object( builder, "player_active_icon" ));
        label = GTK_LABEL( gtk_builder_get_object( builder, "player_active_name" ));
            gtk_image_set_from_file( image , location );
            gtk_label_set_text( label , name );
    }

    void set_current_hand(){      
        GtkWidget       *hand_p1;
        GtkWidget       *hand_p2;
        hand_p1 = GTK_WIDGET( gtk_builder_get_object( builder, "cards_place_p1" ));
        hand_p2 = GTK_WIDGET( gtk_builder_get_object( builder, "cards_place_p2" ));
            if( active == 0 ) {
                gtk_widget_show( hand_p1 );
                gtk_widget_hide( hand_p2 );
            } else{
                gtk_widget_show( hand_p2 );
                gtk_widget_hide( hand_p1 );
            }
    }

    void on_buy_card_clicked(){    
        if( player[active].buy_card == 0 ){
            if( deck_amount_cards == -1) {
                generic_log( "Cartas do baralho acabou" );
                if( deaths[0] == 0 && deaths[1] == 0 ){
                    generic_log( "Morto 1 e 2 passaram para o baralho" );
                    if( dead1_amount_cards != -1 ){
                        GtkImage           *image;
                        GtkWidget          *dialog;
                        image = GTK_IMAGE( gtk_builder_get_object( builder, "img_cart_purchased" ));
                        dialog = GTK_WIDGET( gtk_builder_get_object( builder, "card_purchased" ));
                        char location[50];
                            strcpy( location, "./assets/normal_cards/" );
                            strcat( location, dead1[dead1_amount_cards].image );
                            gtk_image_set_from_file( image , location );
                        player[active].buy_card = 1;
                            gtk_widget_show( dialog );
                    } else if( dead1_amount_cards == -1 && dead2_amount_cards != -1  ){
                        GtkImage           *image;
                        GtkWidget          *dialog;
                        image = GTK_IMAGE( gtk_builder_get_object( builder, "img_cart_purchased" ));
                        dialog = GTK_WIDGET( gtk_builder_get_object( builder, "card_purchased" ));
                        char location[50];
                            strcpy( location, "./assets/normal_cards/" );
                            strcat( location, dead2[dead2_amount_cards].image );
                            gtk_image_set_from_file( image , location );
                        player[active].buy_card = 1;
                            gtk_widget_show( dialog );
                            generic_log_with_name( player[active].name, "comprou uma carta" );
                    } else{
                        set_dialog( "AS CARTAS ACABARAM" );
                        game_end = 1;
                        generic_log( "JOGO FINALIZADO, AS CARTAS ACABARAM" );
                        check_game_end();
                        return;
                    }
                } else if( deaths[0] == 0 && deaths[1] == 1 ){
                    generic_log( "Morto 1 passou para o baralho" );
                    if( dead1_amount_cards != -1 ){
                        GtkImage           *image;
                        GtkWidget          *dialog;
                        image = GTK_IMAGE( gtk_builder_get_object( builder, "img_cart_purchased" ));
                        dialog = GTK_WIDGET( gtk_builder_get_object( builder, "card_purchased" ));
                        char location[50];
                            strcpy( location, "./assets/normal_cards/" );
                            strcat( location, dead1[dead1_amount_cards].image );
                            gtk_image_set_from_file( image , location );
                        player[active].buy_card = 1;
                            gtk_widget_show( dialog );
                            generic_log_with_name( player[active].name, "comprou uma carta" );
                    } else{
                        set_dialog( "AS CARTAS ACABARAM" );
                        game_end = 1;
                        generic_log( "JOGO FINALIZADO, AS CARTAS ACABARAM" );
                        check_game_end();
                        return;
                    }
                } else if( deaths[0] == 1 && deaths[1] == 0 ){
                    generic_log( "Morto 2 passou para o baralho" );
                    if( dead2_amount_cards != -1 ){
                        GtkImage           *image;
                        GtkWidget          *dialog;
                        image = GTK_IMAGE( gtk_builder_get_object( builder, "img_cart_purchased" ));
                        dialog = GTK_WIDGET( gtk_builder_get_object( builder, "card_purchased" ));
                        char location[50];
                            strcpy( location, "./assets/normal_cards/" );
                            strcat( location, dead2[dead2_amount_cards].image );
                            gtk_image_set_from_file( image , location );
                        player[active].buy_card = 1;
                            gtk_widget_show( dialog );
                            generic_log_with_name( player[active].name, "comprou uma carta" );
                    } else{
                        set_dialog( "AS CARTAS ACABARAM" );
                        game_end = 1;
                        generic_log( "JOGO FINALIZADO, AS CARTAS ACABARAM" );
                        check_game_end();
                        return;
                    }
                } else{
                    set_dialog( "AS CARTAS ACABARAM" );
                    game_end = 1;
                    generic_log( "JOGO FINALIZADO, AS CARTAS ACABARAM" );
                    check_game_end();
                    return;
                }            
            } 
            else{
                GtkImage           *image;
                GtkWidget          *dialog;
                image = GTK_IMAGE( gtk_builder_get_object( builder, "img_cart_purchased" ));
                dialog = GTK_WIDGET( gtk_builder_get_object( builder, "card_purchased" ));
                char location[50];
                    strcpy( location, "./assets/normal_cards/" );
                    strcat( location, deck[deck_amount_cards].image );
                    gtk_image_set_from_file( image , location );
                player[active].buy_card = 1;
                    gtk_widget_show( dialog );
                    generic_log_with_name( player[active].name, "Comprou uma carta" );
            }
        } else set_dialog( "VOCÊ NÃO PODE COMPRAR DUAS CARTAS\nPOR TURNO" );
    }

    void on_pass_turn_clicked(){      
            if( player[active].discard_card == 1 ){
                player[active].buy_card = 0;
                player[active].discard_card = 0;
                generic_log_with_name( player[active].name, "Passou a vez" );
                    if( active == 0 ) active=1;
                    else active=0;
                turn();
            } else set_dialog( "VOCÊ NÃO PODE PASSAR O TURNO\nSEM DESCARTAR NENHUMA CARTA" );
    }

    void on_buy_dead_clicked(){         
        int count_cards = list_count_size( player[active].hand , 1 );
            if( player[active].buy_dead == 0 && count_cards == -1 ){
                if( deaths[0] == 0 ){
                    generic_log_with_name( player[active].name, "Comprou o morto" );
                    deaths[0] = 1;
                        for( int i = 0; i < 11; i++ ){
                            list_insert( player[active].hand, dead1[i] );
                        }
                    player[active].buy_dead = 1;
                    check_size_render();
                } else if( deaths[0] != 0 && deaths[1] == 0 ){
                    generic_log_with_name( player[active].name, "Comprou o morto" );
                    deaths[1] = 1;
                        for( int i = 0; i < 11; i++ ){
                            list_insert( player[active].hand, dead2[i] );
                        }
                    player[active].buy_dead = 1;
                    check_size_render();
                } else{
                    set_dialog("NÃO TEM MORTOS PARA COMPRAR");
                }
            } else set_dialog("VOCÊ NÃO ESTÁ APTO\nPARA COMPRAR O MORTO");
    }

    void on_card_buy_clicked(){       
        GtkWidget          *dialog;
        dialog = GTK_WIDGET( gtk_builder_get_object( builder, "card_purchased" ));
        generic_log_with_name( player[active].name, "Comprou a carta que pegou do baralho" );
            if( deck_amount_cards == -1) {
                if( deaths[0] == 0 && deaths[1] == 0 ){
                    if( dead1_amount_cards != -1 ){
                        dead1[dead1_amount_cards].active = 1;
                        dead1[dead1_amount_cards].active_on.hand = 1;
                            list_insert( player[active].hand, dead1[dead1_amount_cards] );
                            add_card_on_hand();
                        dead1_amount_cards--;
                            gtk_widget_hide( dialog );
                    } else if( dead1_amount_cards == -1 && dead2_amount_cards != -1  ){
                        dead2[dead2_amount_cards].active = 1;
                        dead2[dead2_amount_cards].active_on.hand = 1;
                            list_insert( player[active].hand, dead2[dead2_amount_cards] );
                            add_card_on_hand();
                        dead2_amount_cards--;
                            gtk_widget_hide( dialog );
                    }
                } else if( deaths[0] == 0 && deaths[1] == 1 ){
                    dead1[dead1_amount_cards].active = 1;
                    dead1[dead1_amount_cards].active_on.hand = 1;
                        list_insert( player[active].hand, dead1[dead1_amount_cards] );
                        add_card_on_hand();
                    dead1_amount_cards--;
                        gtk_widget_hide( dialog );
                } else if( deaths[0] == 1 && deaths[1] == 0 ){
                    dead2[dead2_amount_cards].active = 1;
                    dead2[dead2_amount_cards].active_on.hand = 1;
                        list_insert( player[active].hand, dead2[dead2_amount_cards] );
                        add_card_on_hand();
                    dead2_amount_cards--;
                        gtk_widget_hide( dialog );
                }
            } else{
                deck[deck_amount_cards].active = 1;
                deck[deck_amount_cards].active_on.hand = 1;
                    list_insert( player[active].hand, deck[deck_amount_cards] );
                    add_card_on_hand();
                deck_amount_cards--;
                    gtk_widget_hide( dialog );
            }
    }

    void add_card_on_hand(){       
        int count_cards = list_count_size ( player[active].hand, 0 ); 
        GtkGrid          *hand;
            if( active == 0 ) hand = GTK_GRID( gtk_builder_get_object( builder, "cards_place_p1" ));
            else hand = GTK_GRID( gtk_builder_get_object( builder, "cards_place_p2" ));
            if( count_cards < 13 ) add_card_size_config( hand, count_cards, 114, 158 );
            else if( count_cards > 12 && count_cards < 16) add_card_size_config( hand, count_cards, 90, 125 );
            else if ( count_cards > 15 && count_cards < 20 ) add_card_size_config( hand, count_cards, 70, 96 );
            else if ( count_cards > 18 ) add_card_size_config( hand, count_cards, 54, 74 );
    }

    void check_size_render(){      
        int count_cards = list_count_size( player[active].hand, 0 );
            if( count_cards < 12 ) size_configs( 114, 158 );
            else if( count_cards > 11 && count_cards < 15) size_configs( 90, 125 );
            else if ( count_cards > 14 && count_cards < 19 ) size_configs( 70, 96 );
            else if ( count_cards > 18 ) size_configs( 54, 74 );
            
    }

    void size_configs( int width , int height ){       
        int count_grid = 0;
        int count_grid2 = 0;
        GtkGrid          *hand;
        GtkWidget       *new_img;
        GdkPixbuf       *pixbuf;
        header *aux = player[active].hand->start;
            if( active == 0 ) hand = GTK_GRID( gtk_builder_get_object( builder, "cards_place_p1" ));
            else hand = GTK_GRID( gtk_builder_get_object( builder, "cards_place_p2" ));
            if( aux != NULL ){
                while( aux != NULL ){
                char location[50];
                    strcpy( location, "./assets/normal_cards/" );
                    strcat( location, aux->l_card.image );
                pixbuf = gdk_pixbuf_new_from_file( location, NULL );
                pixbuf = gdk_pixbuf_scale_simple( pixbuf, width, height, GDK_INTERP_BILINEAR );
                    if( count_grid == 0 ){
                        gtk_grid_remove_row( hand, 0 );
                        gtk_grid_remove_row( hand, 1 );
                    }
                new_img = gtk_image_new_from_pixbuf( pixbuf );
                    gtk_widget_show( new_img );
                    gtk_widget_set_name( new_img, aux->l_card.widget );
                        if( count_grid == 0 ){
                            gtk_grid_insert_row( hand, 0 );
                            gtk_grid_insert_row( hand, 1 );
                                for( int z = 0; z < 24; z ++){
                                    gtk_grid_insert_column( hand, z );
                                }
                        }
                        if( count_grid > 23 ){
                            gtk_grid_attach( hand, new_img, count_grid2, 1, 1, 1 );
                            count_grid2++;
                        } else {
                            gtk_grid_attach( hand, new_img, count_grid, 0, 1, 1 );
                            count_grid++;
                        }
                aux = aux->next;
                }
            } else{
                gtk_grid_remove_row( hand, 0 );
                gtk_grid_remove_row( hand, 1 );
            }
            
    }

    void add_card_size_config( GtkGrid *hand, int count_cards, int width, int height ){      
        GtkWidget       *image;
        GdkPixbuf      *pixbuf;
        char location[50];
            strcpy( location, "./assets/normal_cards/" );
            strcat( location, deck[deck_amount_cards].image );
        pixbuf = gdk_pixbuf_new_from_file( location, NULL );
        pixbuf = gdk_pixbuf_scale_simple( pixbuf, width, height, GDK_INTERP_BILINEAR );
        image = gtk_image_new_from_pixbuf( pixbuf );
            gtk_widget_set_name( image, deck[deck_amount_cards].widget );
            gtk_widget_show(image);
                if( count_cards > 24 ){     
                    if( active == 0 ) {     
                        gtk_grid_attach( hand, image, count_row2_p1, 1, 1, 1 );    
                        count_row2_p1++;
                    } else {
                        gtk_grid_attach( hand, image, count_row2_p2, 1, 1, 1 );
                        count_row2_p2++;
                    }
                } else gtk_grid_attach( hand, image, (count_cards-1), 0, 1, 1 );
    }