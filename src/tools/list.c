#include "../../lib/tools/list.h"

    list* new_list(){   
        list *l=(list*)malloc(sizeof(list));
        l->start=NULL;
        return l;
    }

    int list_is_empty( list *l ){
        if( l->start == NULL ){
            return 1;
        } else {
            return 0;
        }
    }

    int list_insert( list *l , cards card_to_insert ){
        header *new=(header*)malloc(sizeof(header));
            if( new == NULL ){
                printf("\n Erro ao alocar memoria");
                return 1;
            }
        new->l_card = card_to_insert;
        new->next = NULL;
            if( l->start == NULL ){
                l->start = new;
            } else {
                header *aux = l->start;
                    while( aux->next != NULL ){
                        aux=aux->next;
                    }
                aux->next = new;
            }
        return 0;
    }

    int list_remove( list *l, cards *card_removed ){
        if( list_is_empty( l ) == 1 ){
            return 1;
        } else{
            header *aux;
            aux = l->start;
            header *previous;
                if( aux->next == NULL ){
                    *card_removed = aux->l_card;
                    free( aux );
                    l->start = NULL;
                } else{
                    while( aux->next != NULL ){
                        previous = aux;
                        aux = aux->next;
                    }
                previous->next = NULL;
                *card_removed = aux->l_card;
                    free( aux );
                return 0;
                }
        }
    }

    int list_insert_pos( list *l , cards card_to_insert, int pos){
        header *new = (header*)malloc(sizeof(header));
            if( new == NULL ) return 0;
        new->l_card = card_to_insert;
        new->next = NULL;
            if( list_is_empty( l ) == 1 ){
                l->start = new;
            } else if( pos == 0 ) {
                new->next = l->start;
                l->start = new;
            } else{
                header *aux = l->start;
                int count = 1;
                    while( aux != NULL && count != pos ){
                        aux = aux->next;
                        count++;
                    }
                new->next = aux->next;
                aux->next = new;
            }
        return 1;
    }

    int list_remove_pos( list *l, cards *card_removed, int pos){
        header *aux = l->start;
        header *previous;
            if( pos == 0 ){
                *card_removed = aux->l_card;
                l->start = aux->next;
                    free( aux );
            } else{
                int count = 0;
                    while( aux->next != NULL && count != pos ){
                        previous = aux;
                        aux = aux->next;
                        count++;
                    }
                previous->next = aux->next;
                *card_removed = aux->l_card;
                    free( aux );
            }
        return 1;
    }

    int list_count_size( list *l , int choice ){
        int cont = 0;
            if( list_is_empty( l ) == 1 ){
                if( choice == 0 ) return 0;
                else return -1;
            } else{
                header *aux = l->start;
                    while( aux != NULL ){
                        cont++;
                        aux = aux->next;
                    }
                return cont;
            }
    }

    int list_search_key( list *l, cards card_to_search , int *key ){
            if( l->start == NULL ) return 1;
        header *aux = l->start;
        int i = 0;
            while( (aux != NULL) && ( strcmp( aux->l_card.widget, card_to_search.widget ) != 0 ) ){
                aux = aux->next;
                i++;
            }
            if( aux == NULL ) return 1;
            else{
                *key = i;
                return 0;
            }
    }

    int list_search_pos( list *l, cards *searched_card , int pos ){   
        header *aux = l->start;
        int i = 0;
            while( aux != NULL && i<pos ){
                aux = aux->next;
                i++;
            }
        *searched_card = aux->l_card;
        return 0;
    }

    void list_print( list *l ){
        header *aux = l->start;
            printf("\nCartas: \n");
                while( aux != NULL ){
                    printf(" Valor: %i,  Naipe: %d,  Imagem: %s Joker: %i\n", aux->l_card.number, aux->l_card.suit, aux->l_card.image, aux->l_card.joker );
                    aux = aux->next;
                }
            printf("\n");
    }

    void list_free( list *l ){
        if( l != NULL ){
            header *aux;
                    while( l->start != NULL){
                        aux = l->start;
                        l->start = l->start->next;
                        free( aux );
                    }
                free( l );
        }
    }