#include "../lib/dialogs.h"

    void on_dg_name_close_clicked(){        //botão de fechar o dialog de nome jogador
        GtkWidget           *name_dialog;       
        name_dialog = GTK_WIDGET( gtk_builder_get_object( builder, "dialog_name" ));
        gtk_widget_hide( name_dialog );       //escondendo o dialog
    }

    void on_dg_ready_close_clicked(){
        GtkWidget           *ready_dialog;
        ready_dialog = GTK_WIDGET( gtk_builder_get_object( builder, "dialog_ready" ));
        gtk_widget_hide( ready_dialog );
    }

    void on_dg_cmpname_close_clicked(){
        GtkWidget           *cmpname_dialog;
        cmpname_dialog = GTK_WIDGET( gtk_builder_get_object( builder, "dialog_cmpname" ));
        gtk_widget_hide( cmpname_dialog );
    }