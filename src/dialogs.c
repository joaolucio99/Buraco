#include "../lib/dialogs.h"

    void on_dg_close_clicked(){        //botão de fechar o dialog de nome jogador
        GtkWidget           *dialog;       
        dialog = GTK_WIDGET( gtk_builder_get_object( builder, "dialog" ));
        gtk_widget_hide( dialog );       //escondendo o dialog
    }
