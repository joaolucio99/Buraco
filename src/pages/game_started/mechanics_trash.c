#include "../../../lib/pages/game_started/mechanics_trash.h"

    int row_trash[5] = { 0, 0, 0, 0, 0 };

    void on_card_trash_clicked(){       
        GtkWidget          *dialog;
        dialog = GTK_WIDGET( gtk_builder_get_object( builder, "card_purchased" ));
        generic_log_with_name( player[active].name, "Descartou a carta que pegou do baralho" );
            if( deck_amount_cards == -1) {
                if( deaths[0] == 0 && deaths[1] == 0 ){
                    if( dead1_amount_cards != -1 ){
                        dead1[dead1_amount_cards].active = 1;
                        dead1[dead1_amount_cards].active_on.trash = 1;
                            list_insert( trash, dead1[dead1_amount_cards] );
                            add_card_trash_view();
                        dead1_amount_cards--;
                        player[active].discard_card = 1;
                            gtk_widget_hide( dialog );
                    } else if( dead1_amount_cards == -1 && dead2_amount_cards != -1  ){
                        dead2[dead2_amount_cards].active = 1;
                        dead2[dead2_amount_cards].active_on.trash = 1;
                            list_insert( trash, dead2[dead2_amount_cards] );
                            add_card_trash_view();
                        dead2_amount_cards--;
                        player[active].discard_card = 1;
                            gtk_widget_hide( dialog );
                    }
                } else if( deaths[0] == 0 && deaths[1] == 1 ){
                    dead1[dead1_amount_cards].active = 1;
                    dead1[dead1_amount_cards].active_on.trash = 1;
                        list_insert( trash, dead1[dead1_amount_cards] );
                        add_card_trash_view();
                    dead1_amount_cards--;
                    player[active].discard_card = 1;
                        gtk_widget_hide( dialog );
                } else if( deaths[0] == 1 && deaths[1] == 0 ){
                    dead2[dead2_amount_cards].active = 1;
                    dead2[dead2_amount_cards].active_on.trash = 1;
                        list_insert( trash, dead2[dead2_amount_cards] );
                        add_card_trash_view();
                    dead2_amount_cards--;
                    player[active].discard_card = 1;
                        gtk_widget_hide( dialog );
                }
            } else{
                deck[deck_amount_cards].active = 1;
                deck[deck_amount_cards].active_on.trash = 1;
                    list_insert( trash, deck[deck_amount_cards] );
                    add_card_trash_view();
                deck_amount_cards--;
                player[active].discard_card = 1;
                    gtk_widget_hide( dialog );
            }
    }

    void on_trash_back_clicked(){      
        GtkWidget           *dialog;
        dialog = GTK_WIDGET( gtk_builder_get_object( builder, "trash" ));
            gtk_widget_hide( dialog );
    }

    void on_see_trash_clicked(){     
        GtkWidget           *dialog;
        dialog = GTK_WIDGET( gtk_builder_get_object( builder, "trash" ));
            gtk_widget_show( dialog );
    }

    void add_card_trash_view(){        
        GtkGrid         *trash_grid;
        GtkWidget       *image;
        GdkPixbuf       *pixbuf;
        char location[50];
        int count = list_count_size ( trash, 0 );
        trash_grid = GTK_GRID( gtk_builder_get_object( builder, "trash_grid" ));
            strcpy( location, "./assets/normal_cards/" );
            strcat( location, deck[deck_amount_cards].image );
        pixbuf = gdk_pixbuf_new_from_file( location, NULL );
        pixbuf = gdk_pixbuf_scale_simple( pixbuf, 54, 74, GDK_INTERP_BILINEAR );
        image = gtk_image_new_from_pixbuf( pixbuf );
            gtk_widget_set_name( image, deck[deck_amount_cards].widget );
            gtk_widget_show(image);
                if( count < 21 ){
                    gtk_grid_attach( trash_grid, image, (count-1), 0, 1, 1 );
                } else if( count > 20 && count < 41 ){
                    gtk_grid_attach( trash_grid, image, row_trash[0], 1, 1, 1 );
                    row_trash[0]++;
                } else if( count > 40 && count < 61 ){
                    gtk_grid_attach( trash_grid, image, row_trash[1], 2, 1, 1 );
                    row_trash[1]++;
                } else if( count > 60 && count < 81 ){
                    gtk_grid_attach( trash_grid, image, row_trash[2], 3, 1, 1 );
                    row_trash[2]++;
                } else if( count > 80 && count < 101 ){
                    gtk_grid_attach( trash_grid, image, row_trash[3], 4, 1, 1 );
                    row_trash[3]++;
                } else{
                    gtk_grid_attach( trash_grid, image, row_trash[4], 5, 1, 1 );
                    row_trash[4]++;
                }
    }

    void on_buy_trash_clicked(){      
        GtkWidget           *dialog;
        dialog = GTK_WIDGET( gtk_builder_get_object( builder, "trash" ));
        if( player[active].buy_card == 0 ){
            generic_log_with_name( player[active].name, "Comprou todo o lixo" );
            int count_trash = list_count_size( trash , 0 ) ; 
            int verification = list_count_size( trash , 1 ) ;
                if( verification == -1 ) set_dialog( "NÃO TEM CARTAS NO LIXO" );
                else{
                    int count_hand = list_count_size( player[active].hand , 0 );
                    GtkGrid          *hand;
                        if( active == 0 ) hand = GTK_GRID( gtk_builder_get_object( builder, "cards_place_p1" ));
                        else hand = GTK_GRID( gtk_builder_get_object( builder, "cards_place_p2" ));
                    header *aux = trash->start;
                        while( aux != NULL ){   
                            aux->l_card.active_on.trash = 0;
                            aux->l_card.active_on.hand = 1;
                            list_insert( player[active].hand, aux->l_card );
                            count_hand = list_count_size( player[active].hand , 0);
                                if( count_hand < 13 ) add_card_trash_to_hand( count_hand, hand , 114 , 158, aux->l_card.image, aux->l_card.widget );
                                else if( count_hand > 12 && count_hand < 16) add_card_trash_to_hand( count_hand, hand , 90 , 125, aux->l_card.image, aux->l_card.widget );
                                else if ( count_hand > 15 && count_hand < 20 ) add_card_trash_to_hand( count_hand, hand , 70 , 96, aux->l_card.image, aux->l_card.widget );
                                else if ( count_hand > 18 ) add_card_trash_to_hand( count_hand, hand , 54 , 74, aux->l_card.image, aux->l_card.widget );
                            aux = aux->next;
                        }
                        while( count_trash != -1 ){     
                            cards temp;
                                del_card_trash( count_trash );
                                list_remove( trash, &temp );
                                count_trash = list_count_size( trash , 1 ) ; 
                        }
                    player[active].buy_card = 1;
                } 
            check_size_render();
            gtk_widget_hide( dialog );
        } else set_dialog( "VOCÊ NÃO PODE COMPRAR O LIXO,\nPOIS JA COMPROU DO MONTE" );
    }

    void del_card_trash( int count_trash ){     
        GtkWidget       *image;
        GtkGrid         *trash_grid;
        trash_grid = GTK_GRID( gtk_builder_get_object( builder, "trash_grid" ));
            if( count_trash < 21 ){
                image=gtk_grid_get_child_at( trash_grid, (count_trash-1) , 0 );
                    gtk_widget_destroy( image );
            } else if( count_trash > 20 && count_trash < 41 ){
                image=gtk_grid_get_child_at( trash_grid, (row_trash[0]-1) , 1 );
                    gtk_widget_destroy( image );
                row_trash[0]--;
            } else if( count_trash > 40 && count_trash < 61 ){
                image=gtk_grid_get_child_at( trash_grid, (row_trash[1]-1) , 2 );
                    gtk_widget_destroy( image );
                row_trash[1]--;
            } else if( count_trash > 60 && count_trash < 81 ){
                image=gtk_grid_get_child_at( trash_grid, (row_trash[2]-1) , 3 );
                    gtk_widget_destroy( image );
                row_trash[2]--;
            } else if( count_trash > 80 && count_trash < 101 ){
                image=gtk_grid_get_child_at( trash_grid, (row_trash[3]-1) , 4 );
                    gtk_widget_destroy( image );
                row_trash[3]--;
            } else{
                image=gtk_grid_get_child_at( trash_grid, (row_trash[4]-1) , 5 );
                    gtk_widget_destroy( image );
                row_trash[4]--;
            }
    }

    void add_card_trash_to_hand( int count_cards , GtkGrid *hand, int width, int height, char *location_trash, char *widget_name){      
        GtkWidget       *image;
        GdkPixbuf      *pixbuf;
        char location[50];
            strcpy( location, "./assets/normal_cards/" );
            strcat( location, location_trash );
        pixbuf = gdk_pixbuf_new_from_file( location, NULL );
        pixbuf = gdk_pixbuf_scale_simple( pixbuf, width, height, GDK_INTERP_BILINEAR );
        image = gtk_image_new_from_pixbuf( pixbuf );
            gtk_widget_set_name( image, widget_name );
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