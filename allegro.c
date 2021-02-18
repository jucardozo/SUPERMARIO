/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdio.h>
#include <stdlib.h>
#include "allegro.h"

//los bitmaps estan definidos en el punto h
ALLEGRO_DISPLAY *display;                       //se crean  puntero hacia estrucuras de allegro
ALLEGRO_SAMPLE *music = NULL;                  //Musica
ALLEGRO_SAMPLE *sound = NULL;                  //Sonido
ALLEGRO_TIMER *timer = NULL;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;        //Cola de eventos*/

extern int tecla;           //variables que necesito de main.c para algunas funciones
extern int pos[3];
extern int vida;
extern int puntaje;
extern int nivel;
extern int fin;
extern int stop;

int right_or_left = RIGHT;              //variable que me dice si lla ultima que se apreto fue derecha o izquierda

int inicializacion(){                                       //funcion que inicializa todo lo que es arreglo
    
/*ALLEGROOOOOOO*/
    /*INICIALIZACION DE ALLEGRO*/
    if (!al_init()){
        fprintf(stderr, "Unable to start allegro\n");                        //realizo la inicializacion de allegro
        return -1;
    } 
    else if (!al_init_image_addon()) {
        fprintf(stderr, "Unable to start image addon \n");          //si hubo un error en la inicializacion imprimo el srderr
        al_uninstall_system();
        return -1;
    } 
    else if (!(display = al_create_display(LARGO_DISPLAY, ANCHO_DISPLAY))) {         //se controlan si hubo problemas en las
        fprintf(stderr, "Unable to create display\n");                              //distintas inicializaciones 
        al_uninstall_system();
        al_shutdown_image_addon();                              
        return -1;
    } 
    else if (!(nintendo = al_load_bitmap("nintendo.jpg"))) {           //se carga imagen de nintendo
        fprintf(stderr, "Unable to load nintendo\n");
        al_uninstall_system();
        al_shutdown_image_addon();
        al_destroy_display(display);
        return -1;
    }
    else if (!(lobby = al_load_bitmap("lobby.jpg"))) {           //se carga imagen de lobby
        fprintf(stderr, "Unable to load lobby\n");
        al_uninstall_system();
        al_shutdown_image_addon();
        al_destroy_display(display);
        return -1;
    }
    else if (!(press_start = al_load_bitmap("press_start.jpg"))) {           //se carga imagen de press_start
        fprintf(stderr, "Unable to load press_start\n");
        al_uninstall_system();
        al_shutdown_image_addon();
        al_destroy_display(display);
        return -1;
    }
    else if (!(mar = al_load_bitmap("mar.png"))) {              // se carga en un bitmap la imagen que usaremos de base
        fprintf(stderr, "Unable to load mar\n");
        al_uninstall_system();
        al_shutdown_image_addon();
        al_destroy_display(display);
        return -1;
    }
    else if (!(agua = al_load_bitmap("agua.png"))) {           //se carga imagen de agua
        fprintf(stderr, "Unable to load agua\n");
        al_uninstall_system();
        al_shutdown_image_addon();
        al_destroy_display(display);
        return -1;
    }
    else if (!(vidas = al_load_bitmap("vida.jpeg"))) {           //se carga imagen de vidas
        fprintf(stderr, "Unable to load vidas\n");
        al_uninstall_system();
        al_shutdown_image_addon();
        al_destroy_display(display);
        return -1;
    }
    else if (!(vida_perdida = al_load_bitmap("vida_perdida.jpeg"))) {           //se carga imagen de vidas_perdida
        fprintf(stderr, "Unable to load vida_perdidas\n");
        al_uninstall_system();
        al_shutdown_image_addon();
        al_destroy_display(display);
        return -1;
    }
    else if (!(men_pausa = al_load_bitmap("pausa.jpg"))) {           //se carga imagen para el menu de pausa
        fprintf(stderr, "Unable to load men_pausa\n");
        al_uninstall_system();
        al_shutdown_image_addon();
        al_destroy_display(display);
        return -1;
    }
    else if (!(alga = al_load_bitmap("alga.png"))) {           //se carga imagen de alga
        fprintf(stderr, "Unable to load alga\n");
        al_uninstall_system();
        al_shutdown_image_addon();
        al_destroy_display(display);
        return -1;
    }
    else if (!(bloque = al_load_bitmap("bloque.png"))) {           //se carga imagen de bloque
        fprintf(stderr, "Unable to load bloque\n");
        al_uninstall_system();
        al_shutdown_image_addon();
        al_destroy_display(display);
        return -1;
    }
    else if (!(mario_adelante = al_load_bitmap("mario_adelante.png"))) {           //se carga imagen de mario mirando hacia adelante
        fprintf(stderr, "Unable to load mario_adelante\n");
        al_uninstall_system();
        al_shutdown_image_addon();
        al_destroy_display(display);
        return -1;
    }
    else if (!(mario_atras = al_load_bitmap("mario_atras.png"))) {           //se carga imagen de mario mirando hacia atras
        fprintf(stderr, "Unable to load mario_atras\n");
        al_uninstall_system();
        al_shutdown_image_addon();
        al_destroy_display(display);
        return -1;
    }
    else if (!(moneda = al_load_bitmap("moneda.png"))) {           //se carga imagen de moneda
        fprintf(stderr, "Unable to load moneda\n");
        al_uninstall_system();
        al_shutdown_image_addon();
        al_destroy_display(display);
        return -1;
    }
    else if (!(final = al_load_bitmap("final.png"))) {           //se carga imagen de final
        fprintf(stderr, "Unable to load final\n");
        al_uninstall_system();
        al_shutdown_image_addon();
        al_destroy_display(display);
        return -1;
    }
    else if (!(pez = al_load_bitmap("pez.png"))) {           //se carga imagen de pez
        fprintf(stderr, "Unable to load pez\n");
        al_uninstall_system();
        al_shutdown_image_addon();
        al_destroy_display(display);
        return -1;
    }
    else if (!(pes = al_load_bitmap("pes.png"))) {           //se carga imagen de pes
        fprintf(stderr, "Unable to load pes\n");
        al_uninstall_system();
        al_shutdown_image_addon();
        al_destroy_display(display);
        return -1;
    }
    else if (!(pulpo = al_load_bitmap("pulpo.png"))) {           //se carga imagen de pulpo
        fprintf(stderr, "Unable to load pulpo\n");
        al_uninstall_system();
        al_shutdown_image_addon();
        al_destroy_display(display);
        return -1;
    }
    
    /*INICIALIZACION FUENTE*/
    al_init_font_addon(); // initialize the font addon
    al_init_ttf_addon(); // initialize the ttf (True Type Font) addon
    
    font = al_load_ttf_font("letritas.ttf", 36, 0); //FUENTE PARA LA INFO DE ARRIBA 
    font_nivel = al_load_ttf_font("letritas.ttf", 100, 0); //FUENTE PARA EL NIVEL Y PARA EL GAMEOVER
    font_pausa = al_load_ttf_font("letritas.ttf", 36, 0); //FUENTE PARA LA PAUSA
    
    if (!font) {
        fprintf(stderr, "Could not load 'letritas.ttf'.\n");             //se carga la fuente font
        return -1;
    }
    if (!font_nivel) {
        fprintf(stderr, "Could not load 'letritas.ttf'.\n");             //se carga la fuente font_nivel
        return -1;
    }
    if (!font_pausa) {
        fprintf(stderr, "Could not load 'letritas.ttf'.\n");             //se carga la fuente font_pausa
        return -1;
    }
    
    /*INICIALIZACION TIMER*/
    timer = al_create_timer(1.0 / FPS); 
    if (!timer) {
        fprintf(stderr, "failed to create timer!\n");
        return -1;
    }
    
    /*INICIALIZAION MUSICA*/
    if (!al_install_audio()) {                                      //Inicializo el audio                                                   //
        fprintf(stderr, "failed to initialize audio!\n");                                                                                   //
        al_uninstall_system();                                                                                                              //
        al_shutdown_image_addon();                                                                                                          //
        al_destroy_display(display);                                                                                                        //
        return -1;                                                                                                                          //
    }                                                                                                                                       //
                                                                                                                                            //
    if (!al_init_acodec_addon()) {                                                                                                          //
        fprintf(stderr, "failed to initialize audio codecs!\n");                                                                            //
        al_uninstall_system();                                                                                                              //
        al_shutdown_image_addon();                                                                                                          //
        al_destroy_display(display);                                                                                                        //
        return -1;                                                                                                                          //
    }                                                                                                                                       //
                                                                                                                                            //
    if (!al_reserve_samples(2)) {                                                                                                           //
        fprintf(stderr, "failed to reserve samples!\n");                                                                                    //
        al_uninstall_system();                                                                                                              //
        al_shutdown_image_addon();                                                                                                          //
        al_destroy_display(display);                                                                                                        //
        return -1;                                                                                                                          //
    }                                                                                                                                       //
                                                                                                                                            //
    music = al_load_sample("musica.wav");  
    sound = al_load_sample("sonido_moneda.wav");//
                                                                                                                                            //
    if (!music) {                                                                                                                           //
        printf("Audio clip sample not loaded!\n");                                                                                          //
        al_uninstall_system();                                                                                                              //
        al_shutdown_image_addon();                                                                                                          //
        al_destroy_display(display);                                                                                                        //
        return -1;                                                                                                                          //
    }   
    
     if (!sound) {                                                                                                                           //
        printf("Audio clip sample not loaded!\n");                                                                                          //
        al_uninstall_system();                                                                                                              //
        al_shutdown_image_addon();                                                                                                          //
        al_destroy_display(display);                                                                                                        //
        return -1;                                                                                                                          //
    }    
    
    
    //////////////////////////////////
    /*INICIALIZO EVENTOS Y TECLADO*///
    /////////////////////////////////////////////////////////////////////////////////////////////////////
    event_queue = al_create_event_queue();                                                             //
    if (!event_queue) {                                                                                //
        fprintf(stderr, "failed to create event_queue!\n");                                            //
        destroy_allegro();                                                                             //
        return -1;                                                                                     //
    }                                                                                                  //
    if (!al_install_keyboard()) {                                                                      //
        fprintf(stderr, "failed to initialize the keyboard!\n");                                       //
        destroy_allegro();                                                                             //
        return -1;                                                                                     //
    }                                                                                                  //
    al_register_event_source(event_queue, al_get_keyboard_event_source());       //Evento teclado      //
    al_register_event_source(event_queue, al_get_display_event_source(display)); //Cruz roja de salir  //
    /////////////////////////////////////////////////////////////////////////////////////////////////////
      
    
    
    
    /*BIENVENIDA*/
    int hola_allegro = bienvenida_allegro();   //bienvenida por allegro
    if(hola_allegro == -1){
        return -1;
    }
 
}
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////*SE ARRANCA A JUGAR*/////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////////        



void *entrad_allegro(){             //thread que recibe por comando el movimiento deseado por el jugador
    enum MYKEYS {
    KEY_W, KEY_S, KEY_A, KEY_D,ESC,ENTER,ESPACIO //enumero mis letras oa q quede mas fachero el arrgelo
    };
    int key_pressed[5] = {FALSE, FALSE, FALSE, FALSE,FALSE}; //Estado de teclas, true cuando esta apretada
    while(1){
        
        ALLEGRO_EVENT ev;
        if (al_get_next_event(event_queue, &ev)){ //Toma un evento de la cola.
            if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {       //pregunta si hay alguna tecla presionada,
                    switch (ev.keyboard.keycode) {         //en el caso de que lo haya marca como true, la presionada
                        case ALLEGRO_KEY_W:
                        case ALLEGRO_KEY_UP:
                            key_pressed[KEY_W] = TRUE;
                            tecla=UP;
                            break;

                        case ALLEGRO_KEY_S:
                        case ALLEGRO_KEY_DOWN:
                            key_pressed[KEY_S] = TRUE;
                            tecla=DOWN;
                            break;

                        case ALLEGRO_KEY_A:
                        case ALLEGRO_KEY_LEFT:
                            key_pressed[KEY_A] = TRUE;
                            tecla=LEFT;
                            right_or_left = LEFT;
                            break;

                        case ALLEGRO_KEY_D:
                        case ALLEGRO_KEY_RIGHT:
                            key_pressed[KEY_D] = TRUE;
                            tecla=RIGHT;
                            right_or_left = RIGHT;
                            break;
                            
                        case ALLEGRO_KEY_ESCAPE:
                            key_pressed[ESC]=TRUE;
                            tecla=PAUSA;
                            break;
                    }
                }
                else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
                    switch (ev.keyboard.keycode) {
                        case ALLEGRO_KEY_W:
                        case ALLEGRO_KEY_UP:
                            key_pressed[KEY_W] = FALSE;
                            break;

                        case ALLEGRO_KEY_S:
                        case ALLEGRO_KEY_DOWN:
                            key_pressed[KEY_S] = FALSE;
                            break;

                        case ALLEGRO_KEY_A:
                        case ALLEGRO_KEY_LEFT:
                            key_pressed[KEY_A] = FALSE;
                            break;

                        case ALLEGRO_KEY_D:
                        case ALLEGRO_KEY_RIGHT:
                            key_pressed[KEY_D] = FALSE;
                            break;

                        case ALLEGRO_KEY_ESCAPE:
                            key_pressed[ESC]=FALSE;
                            break;
                    }
                }
                else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){            //Si se quiso cerrar el display                                                                     //
                    tecla=SALIR;
                    
                }

            }
    }
}

//////////////////////////////////////////////////////////////////////////

int bienvenida_allegro(void){                   //funcion que imprime la bienvenida del programa y el menu principial, y esta hasta que se aprete el enter o el espacio, si se apreto la cruz, devuelve un -1, sino devuelve  un 0, no recibe nada y devuelve un int
    
    /*PANTALLA NINTENDO*/
    al_clear_to_color(al_map_rgb(255, 255, 255));
    al_flip_display();
    al_rest(1.0);
    al_play_sample(music, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);              //Damos bienvenida al usuario 
    al_draw_scaled_bitmap(nintendo,0, 0, al_get_bitmap_width(nintendo), al_get_bitmap_height(nintendo),0, 0, LARGO_DISPLAY, ANCHO_DISPLAY,0);      //imprimo nintendo                                //
    al_flip_display();                                                      //Muestro la imagen de bienvenida
    al_rest(4.0);
    al_clear_to_color(al_map_rgb(255, 255, 255));
    al_flip_display();
    al_rest(1.0);
    al_draw_scaled_bitmap(lobby,0, 0, al_get_bitmap_width(lobby), al_get_bitmap_height(lobby),0, 0, LARGO_DISPLAY, ANCHO_DISPLAY,0);      //imprimo lobby
    al_flip_display();
    
    /*PANTALLA DE LOBBY + PRESS_START*/
    int mientras = 1;
    while (mientras){                                             //Me quedo aca hasta que se apriete enter o se cierre el programa                             //
        ALLEGRO_EVENT ev0;                                                 //Struct toma todos los eventos de la cola                                                    //
        if (al_get_next_event(event_queue, &ev0)){                   //Damos entrada de teclado por allegro                                                              //
            if (ev0.type == ALLEGRO_EVENT_DISPLAY_CLOSE){            //Si se quiso cerrar el display                                                                     //
                destroy_allegro();                                                                                                                                //
                return -1;                                                                                                                                                //
            }                                                                                                                                                            //
            else if ((ev0.type == ALLEGRO_EVENT_KEY_DOWN) && (ev0.keyboard.keycode == ALLEGRO_KEY_ENTER)|| (ev0.keyboard.keycode == ALLEGRO_KEY_SPACE)){              //sino tranqui, salgo del while sin problema     //
                mientras = 0;   
            }
        }    
        al_draw_bitmap(press_start,100,340,0);          //IMPRIMO PRESS START
        al_flip_display();
        al_rest(1.0);
        al_draw_scaled_bitmap(lobby,0, 0, al_get_bitmap_width(lobby), al_get_bitmap_height(lobby),0, 0, LARGO_DISPLAY, ANCHO_DISPLAY,0);        //HAGO TITILARLO
        al_flip_display();
        al_rest(1.0);
    }                               //HASTA QUE SE APRETE ENTER O ESPACIO
    return 0;
   
}


void print_map_allegro(int arr [ALTURA][LARGO]){            //funcion que carga e imprime todo lo que son las imagenes del mapa, es decir agarra informacion del arreglo de cada nivel y depende de que numero sea, imprime la imagen correspondiente, ademas imprime un "16x16" en proporcion de pixeles, recibe el arrgelo del nivel que esta y no devuelve nada
    

     float largo_elemento=0;            //variables que usamos para movernos por elementos, ya que la imagen se divide en 16x16 cuadrados de 40x34 pixeles
     float alto_elemento=0;             //cada imagen es de 40x34 pixeles
 
    if(((16+pos[2])-pos[1])<=8){        //se lee la columna en donde esta mario y se mueve le mapa si esta en la mitad
        pos[2]+=4;                      //la cantidad de este movimineto se guarda en el tercer elemento del arreglo, se elije por default que se mueva de a 4
    }  
    if(pos[2]<56){
        for (int i=0;i<16;i++){                     //entramos en un for para leer por filas al arreglo
            for(int p=pos[2]; p<(16+pos[2]);p++){   //entramos en un for para leer por columnas al arreglo

                switch(arr[i][p]){                  //dependiendo de que numero sea, dibuja la respectiva imagen en cierto lugar
                    case PRECIPICIO:
                    case AGUA:
                        al_draw_bitmap(agua,largo_elemento,alto_elemento,0);
                        break;
                    case BLOQUE:
                        al_draw_bitmap(bloque,largo_elemento,alto_elemento,0);
                        break;
                    case ALGA:
                        al_draw_bitmap(alga,largo_elemento,alto_elemento,0);
                        break;
                    case FINAL:
                        al_draw_bitmap(final,largo_elemento,alto_elemento,0);
                        break;
                    case MONEDA:
                        al_draw_bitmap(moneda,largo_elemento,alto_elemento,0);
                        break;
                    case PEZ:
                        al_draw_bitmap(pez,largo_elemento,alto_elemento,0);
                        break;
                    case PES:
                        al_draw_bitmap(pes,largo_elemento,alto_elemento,0);
                        break;
                    case PULPO:
                        al_draw_bitmap(pulpo,largo_elemento,alto_elemento,0);
                        break;
                    case MARIO:
                        if(right_or_left == RIGHT){                                             //dependiendo cual tecla (derecha o izquierda) se apreto ultima, dibuja a mario para adelante o mario para atras
                            al_draw_bitmap(mario_adelante,largo_elemento,alto_elemento,0);
                        }
                        else if(right_or_left == LEFT){
                            al_draw_bitmap(mario_atras,largo_elemento,alto_elemento,0);
                        }
                        break;
                    default:
                        break;
                }
                largo_elemento += LARGO_ELEMENTO;           //cada vez que se mueve por columna, se mueve 40 pixeles, ya que es el largo de cada imagen
            }
            largo_elemento = 0;                     //una vez que termina la fila, ponemos la variable en X en 0 para volver a arrancar
            alto_elemento += ALTO_ELEMENTO;         //sumo 34 pixeles en Y ya que es el alto en pixeles de cada imagen

        }
     
        al_flip_display();    //lo imprimo
    }
    else{                                               //LO MISMO QUE LO DE ARRIBA
        for (int i=0;i<16;i++){
            for(int p=54; p<(70);p++){

                switch(arr[i][p]){
                    case PRECIPICIO:
                    case AGUA:
                        al_draw_bitmap(agua,largo_elemento,alto_elemento,0);
                        break;
                    case BLOQUE:
                        al_draw_bitmap(bloque,largo_elemento,alto_elemento,0);
                        break;
                    case ALGA:
                        al_draw_bitmap(alga,largo_elemento,alto_elemento,0);
                        break;
                    case FINAL:
                        al_draw_bitmap(final,largo_elemento,alto_elemento,0);
                        break;
                    case MONEDA:
                        al_draw_bitmap(moneda,largo_elemento,alto_elemento,0);
                        break;
                    case PEZ:
                        al_draw_bitmap(pez,largo_elemento,alto_elemento,0);
                        break;
                    case PES:
                        al_draw_bitmap(pes,largo_elemento,alto_elemento,0);
                        break;
                    case PULPO:
                        al_draw_bitmap(pulpo,largo_elemento,alto_elemento,0);
                        break;
                    case MARIO:
                        if(right_or_left == RIGHT){
                            al_draw_bitmap(mario_adelante,largo_elemento,alto_elemento,0);
                        }
                        else if(right_or_left == LEFT){
                            al_draw_bitmap(mario_atras,largo_elemento,alto_elemento,0);
                        }
                        break;
                    default:
                        break;
                }
                largo_elemento += LARGO_ELEMENTO;
            }
            largo_elemento = 0;
            alto_elemento += ALTO_ELEMENTO;
        }
     
        al_flip_display();
    }
  
 }

void draw_background (void){              //funcion que carga el detras de escena del mario, es decir el mar con mas informacion, no recibe nada y no devuelve nada
    
    al_draw_scaled_bitmap(mar,0, 0, al_get_bitmap_width(mar), al_get_bitmap_height(mar),0, 0, LARGO_DISPLAY, ANCHO_DISPLAY,0);      //CARGO BACKGROUND (el mar)
    al_draw_text(font, al_map_rgb(255, 255, 255), PUNTAJE_X , VISTA_Y , ALLEGRO_ALIGN_CENTER, "PUNTAJE:");                  
    al_draw_textf(font, al_map_rgb(255, 255, 255), PUNTAJE_NUMERO_X , VISTA_Y , ALLEGRO_ALIGN_CENTER, "%d",puntaje);                //cargo PUNTAJE: y el puntaje en el cielo
    al_draw_text(font, al_map_rgb(255, 255, 255), NIVEL_X , VISTA_Y , ALLEGRO_ALIGN_CENTER, "NIVEL:");                              //cargo NIVEL: y el nivel en el cielo
    al_draw_textf(font, al_map_rgb(255, 255, 255), NIVEL_NUMERO_X , VISTA_Y , ALLEGRO_ALIGN_CENTER, "%d",nivel);
    al_draw_text(font, al_map_rgb(255, 255, 255), VIDA_X , VISTA_Y , ALLEGRO_ALIGN_CENTER, "VIDA:");                                //cargo VIDA:
    if(vida==3){                                    //si tiene tres vidas, cargo tres corazones
        al_draw_bitmap(vidas,VIDA_1_X,VISTA_Y,0);
        al_draw_bitmap(vidas,VIDA_2_X,VISTA_Y,0);
        al_draw_bitmap(vidas,VIDA_3_X,VISTA_Y,0);
    }
    else if(vida==2){                               //si tiene dos vidas, cargo dos corazones y uno roto
        al_draw_bitmap(vidas,VIDA_1_X,VISTA_Y,0);
        al_draw_bitmap(vidas,VIDA_2_X,VISTA_Y,0); 
        al_draw_bitmap(vida_perdida,VIDA_3_X,VISTA_Y,0);        
    }
    else if(vida==1){                               //si tiene una vida, cargo un corazon y dos rotos
        al_draw_bitmap(vidas,VIDA_1_X,VISTA_Y,0); 
        al_draw_bitmap(vida_perdida,VIDA_2_X,VISTA_Y,0); 
        al_draw_bitmap(vida_perdida,VIDA_3_X,VISTA_Y,0);
    }
    else if(vida==0){                               //si tiene cero vidas, cargo tres rotos
        al_draw_bitmap(vida_perdida,VIDA_1_X,VISTA_Y,0); 
        al_draw_bitmap(vida_perdida,VIDA_2_X,VISTA_Y,0); 
        al_draw_bitmap(vida_perdida,VIDA_3_X,VISTA_Y,0);
    }
}

void menu_allegro(void){            //funcion que imprime el menu de pausa, no recibe nada y no devuelve nada
    
    al_draw_bitmap(men_pausa,MENU_X,MENU_Y,0);              //imprime una parte del lobby
    al_draw_text(font_pausa, al_map_rgb(255, 255, 255), FONT_NIVEL_X,FONT_NIVEL_Y+20, ALLEGRO_ALIGN_CENTER, "PRESIONE ESC PARA CONTINUAR");
    al_draw_text(font_pausa, al_map_rgb(255, 255, 255), FONT_NIVEL_X, FONT_NIVEL_Y+85, ALLEGRO_ALIGN_CENTER, "APRIETE LA X PARA CERRAR EL JUEGO");
    al_flip_display();      //imprime PRESIONE ESC PARA CONTINUAR y APRIETE LA X PARA CERRAR EL JUEGO en el medio de la pantalla
    int end=1;
    while(end){
        if( tecla==PAUSA){      //si volvio a apretar esc entonces vuelve al juego e imprime background
            stop=0;
            end=0;
            tecla=0;
             draw_background();
        }  
        else if( tecla==SALIR){             //si apreto la cruz roja entonces imprime saliendo, espera y sale del juego
            end=0;
            al_clear_to_color(al_map_rgb(255, 255, 255));
            al_draw_text(font_pausa, al_map_rgb(0, 0, 0), FONT_NIVEL_X, FONT_NIVEL_Y, ALLEGRO_ALIGN_CENTER, "saliendo del juego...");
            al_flip_display();
            al_rest(1.5);
        }    
    }
}



void print_lvl (void){             //funcion que imprime en que nivel estas antes de cada nivel, no recibe nada y no devuelve nada
    al_rest(0.5);
    al_draw_textf(font_nivel, al_map_rgb(0, 0, 0), FONT_NIVEL_X, FONT_NIVEL_Y , ALLEGRO_ALIGN_CENTER, "NIVEL %d",nivel);        //imprime que NIVEL y cual es, en blanco con efecto 3D
    al_draw_textf(font_nivel, al_map_rgb(255, 255, 255), FONT_NIVEL_X+5 , FONT_NIVEL_Y-5 , ALLEGRO_ALIGN_CENTER, "NIVEL %d",nivel);
    al_flip_display();
    al_rest(1.0);
}

void print_vida (void){                     //funcion que me imprime las vidas que tiene el jugador, no recibe nada y no devuelve nada
    if(vida==2){                                    //si tiene dos vidas, imprime dos corazones completos y uno roto
        al_draw_bitmap(vidas,VIDA_1_X,VISTA_Y,0);
        al_draw_bitmap(vidas,VIDA_2_X,VISTA_Y,0); 
        al_draw_bitmap(vida_perdida,VIDA_3_X,VISTA_Y,0);        
    }
    else if(vida==1){                               //si tiene una vida, imprime un corazon completo y dos rotos
        al_draw_bitmap(vidas,VIDA_1_X,VISTA_Y,0); 
        al_draw_bitmap(vida_perdida,VIDA_2_X,VISTA_Y,0); 
        al_draw_bitmap(vida_perdida,VIDA_3_X,VISTA_Y,0);
    }
    else if(vida==0){                               //si no tiene mas vidas, imprime tres corazones rotos
        al_draw_bitmap(vida_perdida,VIDA_1_X,VISTA_Y,0); 
        al_draw_bitmap(vida_perdida,VIDA_2_X,VISTA_Y,0); 
        al_draw_bitmap(vida_perdida,VIDA_3_X,VISTA_Y,0);
    }
}

void coin_sound(void){
    al_play_sample(sound,1,0,1,ALLEGRO_PLAYMODE_ONCE,NULL);             //reproduce el sonido una sola vez cuando mario colecta una moneda     
}

void print_win(void){           //funcion que imprime en pantalla cuando el jugadir gana, no recibe nada y no devuelve nada
    al_clear_to_color(al_map_rgb(0, 0, 0));                                                                         //imprime pantalla en negro
    al_flip_display();
    al_draw_textf(font_nivel, al_map_rgb(255, 255, 255), SCORE_X, SCORE_Y, ALLEGRO_ALIGN_CENTER, "SCORE  %d",puntaje);      //impreme el score que hiciste GAME OVER en 3D
    al_draw_text(font_nivel, al_map_rgb(0, 0, 255), FONT_NIVEL_X-5, FONT_NIVEL_Y+5 , ALLEGRO_ALIGN_CENTER, "YOU WIN");
    al_draw_text(font_nivel, al_map_rgb(255, 0, 0), FONT_NIVEL_X, FONT_NIVEL_Y , ALLEGRO_ALIGN_CENTER, "YOU WIN");
    al_draw_text(font_nivel, al_map_rgb(255, 255, 255), FONT_NIVEL_X+5 , FONT_NIVEL_Y-5 , ALLEGRO_ALIGN_CENTER, "YOU WIN");
    al_draw_textf(font_nivel, al_map_rgb(255, 255, 255), VIDAS_X, VIDAS_Y, ALLEGRO_ALIGN_CENTER, "VIDAS %d",vida);
    al_flip_display();
    al_rest(2.5); 
}

void print_gameover(void){           //funcion que imprime GAME OVER y SCORE cuando perdes, no recibe nada y no devuelve nada
    al_clear_to_color(al_map_rgb(0, 0, 0));                                                                         //imprime pantalla en negro
    al_flip_display();
    al_draw_textf(font_nivel, al_map_rgb(255, 255, 255), SCORE_X, SCORE_Y, ALLEGRO_ALIGN_CENTER, "SCORE  %d",puntaje);      //impreme el score que hiciste GAME OVER en 3D
    al_draw_text(font_nivel, al_map_rgb(0, 0, 255), FONT_NIVEL_X-5, FONT_NIVEL_Y+5 , ALLEGRO_ALIGN_CENTER, "GAME OVER");
    al_draw_text(font_nivel, al_map_rgb(255, 0, 0), FONT_NIVEL_X, FONT_NIVEL_Y , ALLEGRO_ALIGN_CENTER, "GAME OVER");
    al_draw_text(font_nivel, al_map_rgb(255, 255, 255), FONT_NIVEL_X+5 , FONT_NIVEL_Y-5 , ALLEGRO_ALIGN_CENTER, "GAME OVER");
    al_flip_display();
    al_rest(2.5); 
}

void destroy_allegro (void){            //funcion que destruye todo allegro, no recibe nada y no devuelve nada
    printf("\n");
    printf("cerrando allegro...\n");
    al_destroy_display(display);                //se libera la memoria dinamica , destruyendo los elemntos usados
    al_destroy_bitmap(nintendo);
    al_destroy_bitmap(lobby);
    al_destroy_bitmap(press_start);
    al_destroy_bitmap(mar);
    al_destroy_bitmap(agua);
    al_destroy_bitmap(vidas);
    al_destroy_bitmap(vida_perdida);
    al_destroy_bitmap(alga);
    al_destroy_bitmap(bloque);
    al_destroy_bitmap(mario_adelante);
    al_destroy_bitmap(mario_atras);
    al_destroy_bitmap(moneda);
    al_destroy_bitmap(final);
    al_destroy_bitmap(pez);
    al_destroy_bitmap(pes);
    al_destroy_bitmap(pulpo);
    al_destroy_bitmap(men_pausa);
    al_uninstall_audio();                                                                                                                                    //
    al_destroy_sample(music);
    al_destroy_sample(sound);
    al_destroy_timer(timer);
    al_destroy_event_queue(event_queue); 
}