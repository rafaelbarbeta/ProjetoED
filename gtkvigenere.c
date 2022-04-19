#include <gtk/gtk.h>
#include <ctype.h>
#include <stdlib.h>
#include "lista.h"
#include "deque.h"

typedef struct { //struct que irá conter os argumentos para callback dos botões (no caso, o ponteiro para o texto e a chave)
  GtkTextBuffer *bufferTexto;
  GtkTextBuffer *bufferChave;
} myArgs;

char criptografarCaractere(char chartexto,char charchave) {
    //a função de criptografia irá processar todos os caracteres como se fossem minúsculos, para facilidade de código
    //por isso, é necessário guardar se o caractere no texto original era maiúsculo ou não
    int eraMaiusculo = 0;
    if (isupper(chartexto))
        eraMaiusculo = 1;
    chartexto = tolower(chartexto);
    //sendo que a letra a tem valor ascii = 97, se subtrairmos 97 de todos os caracteres, eles ficam ordenados de 0 até 25, o que facilita a criptografia
    chartexto = chartexto - 97;
    charchave = tolower(charchave) - 97;
    int charcrip = (chartexto + charchave) % 26; //definição matemática da cifra de vigenère
    charcrip = charcrip + 97; //soma-se 97 novamante para que o caractere volte a ser codificavel em ASCII
    if (eraMaiusculo)
        charcrip = toupper(charcrip);
    return charcrip;
}

char descriptografarCaractere(char chartexto,char charchave) {
    //a função para descriptografar irá processar todos os caracteres como se fossem minúsculos, para facilidade de código
    //por isso, é necessário guardar se o caractere no texto original era maiúsculo ou não
    int eraMaiusculo = 0;
    if (isupper(chartexto))
        eraMaiusculo = 1;
    chartexto = tolower(chartexto);
    //sendo que a letra a tem valor ascii = 97, se subtrairmos 97 de todos os caracteres, eles ficam ordenados de 0 até 25, o que facilita para descriptografar
    chartexto = chartexto - 97;
    charchave = tolower(charchave) - 97;
    int chardecrip = (chartexto - charchave + 26) % 26; //definição matemática da cifra de vigenère
    chardecrip = chardecrip + 97; //soma-se 97 novamante para que o caractere volte a ser codificavel em ASCII
    if (eraMaiusculo)
        chardecrip = toupper(chardecrip);
    return chardecrip;
}

static void criptografar(GtkButton *botao,myArgs* user_data) {
    listaEnc textoCrip;
    deque chave;
    myArgs *args =  (myArgs*)user_data;
    GtkTextIter it;
    //inicia o deque e a lista
    startDeque(&chave,100);
    startList(&textoCrip);

    //coloca a chave no deque caractere por caractere. O(n)
    for (gtk_text_buffer_get_start_iter(GTK_TEXT_BUFFER(args->bufferChave),&it); !gtk_text_iter_is_end(&it); gtk_text_iter_forward_char(&it)) {
      char charchave;
      charchave =  gtk_text_iter_get_char(&it);
      addEndDeque(&chave,charchave);
    }

    //percorre o buffer da text area com um iterador, criptografando os caracteres e colocando eles na lista para futuro uso. O(n)
    for (gtk_text_buffer_get_start_iter(GTK_TEXT_BUFFER(args->bufferTexto),&it); !gtk_text_iter_is_end(&it); gtk_text_iter_forward_char(&it)) {
        char charchave; //caractere que guarda 1 caractere da chave
        char chartexto; //caractere que guarda 1 caractere do texto original
        char caractereCrip;
        charchave = viewStartDeque(&chave);
        chartexto = gtk_text_iter_get_char(&it);
        //por padrao, o caractereCrip e o proprio caractere do texto (serve para o caso de chartexto nao seja alfabetico)
        caractereCrip = chartexto;
        if (isalpha(chartexto)) {
          caractereCrip = criptografarCaractere(chartexto,charchave);
          //retira o caractere do inicio do deque e o coloca no final, garantindo a circulariadade da chave para o texto
          removeStartDeque(&chave);
          addEndDeque(&chave,charchave);
        }
        addEndList(&textoCrip,caractereCrip);
    }
    GtkWidget *janelaResultado;
    GtkWidget *viewTextoCrip;
    GtkTextBuffer *bufferViewTextoCrip;
    janelaResultado = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(janelaResultado),"Texto Criptografado!");
    viewTextoCrip = gtk_text_view_new();
    bufferViewTextoCrip = gtk_text_view_get_buffer(GTK_TEXT_VIEW(viewTextoCrip));
    gtk_container_add(GTK_CONTAINER(janelaResultado),viewTextoCrip);
    
    //constroi o text_buffer com o texto criptogrado na lista encadeada
    iterador i;
    gtk_text_buffer_get_start_iter(GTK_TEXT_BUFFER(bufferViewTextoCrip),&it);
    gtk_text_view_set_editable(GTK_TEXT_VIEW(viewTextoCrip),FALSE);

    char *letra = malloc(sizeof(char)); 
    for (i = firstElementList(&textoCrip); !endList(i); nextElementList(&i)) {
        *letra = (char)getElementList(i);
        gtk_text_buffer_insert(bufferViewTextoCrip,&it,letra,sizeof(char));
        gtk_text_iter_forward_char(&it);
    }

    gtk_widget_show_all (janelaResultado);
    //destroi o deque e a lista
    wreckDeque(&chave);
    wreckList(&textoCrip);
}

static void descriptografar(GtkWidget *botao, gpointer user_data) {
    listaEnc textoDecrip;
    deque chave;
    myArgs *args =  (myArgs*)user_data;
    GtkTextIter it;
    //inicia o deque e a lista
    startDeque(&chave,100);
    startList(&textoDecrip);

    //coloca a chave no deque caractere por caractere. O(n)
    for (gtk_text_buffer_get_start_iter(GTK_TEXT_BUFFER(args->bufferChave),&it); !gtk_text_iter_is_end(&it); gtk_text_iter_forward_char(&it)) {
      char charchave;
      charchave =  gtk_text_iter_get_char(&it);
      addEndDeque(&chave,charchave);
    }

    //percorre o buffer da text area com um iterador, descriptografando os caracteres e colocando eles na lista para futuro uso. O(n)
    for (gtk_text_buffer_get_start_iter(GTK_TEXT_BUFFER(args->bufferTexto),&it); !gtk_text_iter_is_end(&it); gtk_text_iter_forward_char(&it)) {
        char charchave; //caractere que guarda 1 caractere da chave
        char chartexto; //caractere que guarda 1 caractere do texto original
        char caractereDecrip;
        charchave = viewStartDeque(&chave);
        chartexto = gtk_text_iter_get_char(&it);
        //por padrao, o caractereDecrip e o proprio caractere do texto (serve para o caso de chartexto nao seja alfabetico)
        caractereDecrip = chartexto;
        if (isalpha(chartexto)) {
          caractereDecrip = descriptografarCaractere(chartexto,charchave);
          //retira o caractere do inicio do deque e o coloca no final, garantindo a circulariadade da chave para o texto
          removeStartDeque(&chave);
          addEndDeque(&chave,charchave);
        }
        addEndList(&textoDecrip,caractereDecrip);
    }
    GtkWidget *janelaResultado;
    GtkWidget *viewTextoCrip;
    GtkTextBuffer *bufferViewTextoCrip;
    janelaResultado = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(janelaResultado),"Texto Descriptografado!");
    viewTextoCrip = gtk_text_view_new();
    bufferViewTextoCrip = gtk_text_view_get_buffer(GTK_TEXT_VIEW(viewTextoCrip));
    gtk_container_add(GTK_CONTAINER(janelaResultado),viewTextoCrip);
    
    //constroi o text_buffer com o texto descriptografado na lista encadeada
    iterador i;
    gtk_text_buffer_get_start_iter(GTK_TEXT_BUFFER(bufferViewTextoCrip),&it);
    gtk_text_view_set_editable(GTK_TEXT_VIEW(viewTextoCrip),FALSE);

    char *letra = malloc(sizeof(char)); 
    for (i = firstElementList(&textoDecrip); !endList(i); nextElementList(&i)) {
        *letra = (char)getElementList(i);
        gtk_text_buffer_insert(bufferViewTextoCrip,&it,letra,sizeof(char));
        gtk_text_iter_forward_char(&it);
    }

    gtk_widget_show_all (janelaResultado);
    //destroi o deque e a lista
    wreckDeque(&chave);
    wreckList(&textoDecrip);
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
  GtkTextBuffer *bufferChave;
  GtkWidget *buttonCrip, *buttonDecrip;
  GtkWidget *boxButton;

  //Define a janela principal do programa
  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Cifra De Vigenère");
  gtk_window_set_default_size (GTK_WINDOW (window), 300, 600);
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

  //Cria o buffer e text_view para a chave a ser criptografado/descriptografado
  chave = gtk_text_view_new();
  bufferChave = gtk_text_view_get_buffer(GTK_TEXT_VIEW(chave));

  //argumentos para as funções chamadas pelos botões
  myArgs *args;
  args = g_new(myArgs,1);
  args->bufferTexto = bufferTexto;
  args->bufferChave = bufferChave;


  //cria dois botões, um para criptografar utilizando a chave, outra para descriptografar
  buttonCrip = gtk_button_new_with_label("Criptografar!");
  buttonDecrip = gtk_button_new_with_label("Descriptografar!");
  boxButton = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_box_pack_start(GTK_BOX(boxButton),buttonCrip,TRUE,TRUE,10);
  gtk_box_pack_start(GTK_BOX(boxButton),buttonDecrip,TRUE,TRUE,10);
  //define a função que deve ser chamada quando um dos botões é clicado. Passa a struct "args" como parâmetro
  g_signal_connect(GTK_BUTTON(buttonCrip),"clicked",G_CALLBACK(criptografar),args);
  g_signal_connect(GTK_BUTTON(buttonDecrip),"clicked",G_CALLBACK(descriptografar),args);


  //Cria uma "caixa" para conter as widgets. Define a orientação como vertical
  principalBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_container_add(GTK_CONTAINER(window),principalBox);
  gtk_box_pack_start(GTK_BOX(principalBox),labelTexto,FALSE,FALSE,10);
  gtk_box_pack_start(GTK_BOX(principalBox),texto,TRUE,TRUE,30);
  gtk_box_pack_start(GTK_BOX(principalBox),labelChave,FALSE,FALSE,10);
  gtk_box_pack_start(GTK_BOX(principalBox),chave,FALSE,TRUE,30);
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