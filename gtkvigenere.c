#include <gtk/gtk.h>

static void criptografar(GtkApplication* app, gpointer user_data) {
    printf("Botao clicado!\n");
}

static void descriptografar(GtkApplication* app, gpointer user_data) {
  printf("Outro clicado!\n");
}
static void
activate (GtkApplication* app, gpointer user_data) {
  //ponteiros para widgets
  GtkWidget *window;
  GtkWidget *principalBox;
  GtkWidget *labelTexto;
  GtkWidget *texto;
  GtkTextBuffer *bufferTexto;
  GtkWidget *labelChave;
  GtkWidget *chave;
  GtkEntryBuffer *bufferChave;
  GtkWidget *buttonCrip, *buttonDecrip;
  GtkWidget *boxButton;

  //Define a janela principal do programa
  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Cifra De Vigenère");
  gtk_window_set_default_size (GTK_WINDOW (window), 200, 200);
  gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);

  //rótulo "Insira o texto para Criptografar/Descriptografar" com cor vede 
  labelTexto = gtk_label_new(NULL);
  gtk_label_set_markup(GTK_LABEL(labelTexto),"<span foreground='green' font_family='Times New Roman' weight='bold'>Insira o texto para Criptografar/Descriptografar</span>");

  //Cria o buffer e text_view para o texto a ser criptografado/descriptografado
  texto = gtk_text_view_new();
  bufferTexto = gtk_text_view_get_buffer(GTK_TEXT_VIEW(texto));

  //label da chave
  labelChave = gtk_label_new(NULL);
  gtk_label_set_markup(GTK_LABEL(labelChave),"<span foreground='green' font_family='Times New Roman' weight='bold'>Insira a chave (max: 100 caracteres)</span>");

  //Cria o buffer e text_view para o texto a ser criptografado/descriptografado
  bufferChave = gtk_entry_buffer_new(NULL,-1);
  chave = gtk_entry_new_with_buffer(GTK_ENTRY_BUFFER(bufferChave));
  
  //cria dois botões, um para criptografar utilizando a chave, outra para descriptografar
  buttonCrip = gtk_button_new_with_label("Criptografar!");
  buttonDecrip = gtk_button_new_with_label("Descriptografar!");
  boxButton = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_box_pack_start(GTK_BOX(boxButton),buttonCrip,TRUE,TRUE,10);
  gtk_box_pack_start(GTK_BOX(boxButton),buttonDecrip,TRUE,TRUE,10);
  g_signal_connect(GTK_BUTTON(buttonCrip),"clicked",G_CALLBACK(criptografar),NULL);
  g_signal_connect(GTK_BUTTON(buttonDecrip),"clicked",G_CALLBACK(descriptografar),NULL);


  //Cria uma "caixa" para conter as widgets. Define a orientação como vertical
  principalBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_container_add(GTK_CONTAINER(window),principalBox);
  gtk_box_pack_start(GTK_BOX(principalBox),labelTexto,FALSE,FALSE,10);
  gtk_box_pack_start(GTK_BOX(principalBox),texto,TRUE,TRUE,30);
  gtk_box_pack_start(GTK_BOX(principalBox),labelChave,FALSE,FALSE,10);
  gtk_box_pack_start(GTK_BOX(principalBox),chave,TRUE,TRUE,30);
  gtk_box_pack_start(GTK_BOX(principalBox),boxButton,FALSE,FALSE,10);
  gtk_widget_show_all (window);
}

int
main (int    argc, char **argv)
{
  GtkApplication *app;
  int status;
  app = gtk_application_new("ed.projeto", G_APPLICATION_FLAGS_NONE);
  g_signal_connect(app,"activate",G_CALLBACK(activate),NULL);
  status = g_application_run(G_APPLICATION(app),argc,argv);
  g_object_unref(app);
  return status;
}