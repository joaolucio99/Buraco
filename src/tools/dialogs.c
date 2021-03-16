#include "../../lib/tools/dialogs.h"

    void on_dg_close_clicked(){        
        GtkWidget           *dialog;       
        dialog = GTK_WIDGET( gtk_builder_get_object( builder, "dialog" ));
        gtk_widget_hide( dialog );       
    }

    void set_dialog( char *text ){
        GtkWidget           *dialog;
        GtkLabel            *label;
        dialog = GTK_WIDGET( gtk_builder_get_object( builder, "dialog" ));
        label = GTK_LABEL( gtk_builder_get_object( builder, "dg_label" ));
            gtk_label_set_text( label , text );
            gtk_widget_show( dialog );
    }