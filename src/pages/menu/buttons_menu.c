#include "../../../lib/pages/menu/buttons_menu.h"

    void on_button_exit_clicked(){
        gtk_main_quit();
    }

    void on_button_init_clicked( GtkButton *button, GtkStack *stack ){          //call quando clica botao jogar, retorna a pilha de paginas
        gtk_stack_set_visible_child_name ( stack, "players_page" );         //acessando a pilha e procurando a pagina pelo nome
    }