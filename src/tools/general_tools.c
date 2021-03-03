#include "../../lib/tools/general_tools.h"

    GtkBuilder      *builder;
    GtkWidget       *window;

    void on_window_main_destroy(){
        gtk_main_quit();
    }

    void get_date( char *s ){
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        char year[10],month[10],day[10],Hours[10],Minutes[10],Seconds[10];
            sprintf(year, "%i", tm.tm_year+1900);
            sprintf(month, "%i", tm.tm_mon+1);
            sprintf(day, "%i", tm.tm_mday);
            sprintf(Hours, "%i", tm.tm_hour);
            sprintf(Minutes, "%i", tm.tm_min);
            sprintf(Seconds, "%i", tm.tm_sec);
            strcat(day,"/");
            strcat(day,month);
            strcat(day,"/");
            strcat(day,year);
        char full_date[28];
            strcpy(full_date,day);
            strcat(full_date," - ");
            strcat(full_date,Hours);
            strcat(full_date,":");
            strcat(full_date,Minutes);
            strcat(full_date,":");
            strcat(full_date,Seconds);
            strcpy(s,full_date);
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