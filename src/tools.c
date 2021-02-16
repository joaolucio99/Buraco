#include "../lib/tools.h"

    GtkBuilder      *builder;
    GtkWidget       *window;

    void on_window_main_destroy(){
        gtk_main_quit();
    }

    void load_css(){
        GtkCssProvider *provider;  
        GdkDisplay *display;
        GdkScreen *screen;

        const gchar *css_style_file = "style.css"; //referenciando o nome do arquivo css
        GFile *css_fp               = g_file_new_for_path ( css_style_file );  //criando var armazenamento arquivo
        GError *error               = 0;

        provider = gtk_css_provider_new(); 
        display  = gdk_display_get_default();
        screen   = gdk_display_get_default_screen( display );

        gtk_style_context_add_provider_for_screen( screen, GTK_STYLE_PROVIDER( provider) , GTK_STYLE_PROVIDER_PRIORITY_APPLICATION ); //adicionando provider na execução
        gtk_css_provider_load_from_file ( provider , css_fp , &error );     //referenciando o arquivo css a ser usado no provider

        g_object_unref ( provider );
    }