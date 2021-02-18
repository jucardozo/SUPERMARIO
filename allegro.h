/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#ifndef ALLEGRO_H
#define ALLEGRO_H

#ifdef __cplusplus
extern "C" {
#endif

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h> // NO OLVIDAR AGREGAR EN EL LINKER DEL PROYECTO
#include <allegro5/allegro_acodec.h> // NO OLVIDAR AGREGAR EN EL LINKER DEL PROYECTO*
#include <allegro5/allegro_font.h> //manejo de fonts
#include <allegro5/allegro_ttf.h> //Manejo de ttfs
#include "levels.h"         //solo para incluir defines
  
/*DEFINES*/
#define UP 100
#define RIGHT 101
#define LEFT 102
#define DOWN 103
#define PAUSA 104
#define SALIR 105 
#define TRUE 1
#define FALSE 0

/*ALLEGRO*/
#define FPS    60.0
#define LARGO_DISPLAY 640      //TAMANIO DE IMAGEN
#define ANCHO_DISPLAY 544      //TAMANIO DE IMAGEN
    
/*UBICACIONES EN PANTALLA*/
#define PUNTAJE_X 100.0
#define PUNTAJE_NUMERO_X 200.0
#define NIVEL_X 300.0
#define NIVEL_NUMERO_X 350.0
#define VIDA_X 450.0
#define VISTA_Y 10.0  
#define VIDA_1_X 500.0
#define VIDA_2_X 540.0
#define VIDA_3_X 580.0  
#define FONT_NIVEL_X 325.0
#define FONT_NIVEL_Y 250.0
#define SCORE_X 360.0
#define SCORE_Y 150.0
#define VIDAS_X 305.0
#define VIDAS_Y 350.0
#define MENU_X 155.0
#define MENU_Y 110.0

    
/*PROTOTIPOS*/
int bienvenida_allegro(void);                           //funcion que inicializa todo lo que es arreglo
int inicializacion();                                   //funcion que imprime la bienvenida del programa y el menu principial, y esta hasta que se aprete el enter o el espacio, si se apreto la cruz, devuelve un -1, sino devuelve  un 0, no recibe nada y devuelve un int
void print_map_allegro(int arr [ALTURA][LARGO]);        //funcion que carga e imprime todo lo que son las imagenes del mapa, es decir agarra informacion del arreglo de cada nivel y depende de que numero sea, imprime la imagen correspondiente, ademas imprime un "16x16" en proporcion de pixeles, recibe el arrgelo del nivel que esta y no devuelve nada
void draw_background (void);                            //funcion que carga el detras de escena del mario, es decir el mar con mas informacion, no recibe nada y no devuelve nada
void menu_allegro(void);                                //funcion que imprime el menu de pausa, no recibe nada y no devuelve nada
void print_lvl (void);                                  //funcion que imprime en que nivel estas antes de cada nivel, no recibe nada y no devuelve nada
void print_vida (void);                                 //funcion que me imprime las vidas que tiene el jugador, no recibe nada y no devuelve nada
void print_win(void);                                   //funcion que imprime en pantalla cuando el jugadir gana, no recibe nada y no devuelve nada
void print_gameover(void);                              //funcion que imprime GAME OVER y SCORE cuando perdes, no recibe nada y no devuelve nada
void destroy_allegro (void);                            //funcion que destruye todo allegro, no recibe nada y no devuelve nada

/*THREADS*/
void * entrad_allegro();                                //thread que recibe por comando el movimiento deseado por el jugador


/*PUNTEROS DE ALLEGRO*/
ALLEGRO_FONT *font;
ALLEGRO_FONT *font_nivel;
ALLEGRO_FONT *font_pausa;
ALLEGRO_BITMAP *mar;                         //que nos permitiran utilizar ciertas funciones de
ALLEGRO_BITMAP *agua;                        //allegro.
ALLEGRO_BITMAP *alga; 
ALLEGRO_BITMAP *lobby;
ALLEGRO_BITMAP *nintendo;
ALLEGRO_BITMAP *press_start;
ALLEGRO_BITMAP *vidas;
ALLEGRO_BITMAP *vida_perdida;
ALLEGRO_BITMAP *bloque;
ALLEGRO_BITMAP *mario_adelante;
ALLEGRO_BITMAP *mario_atras;                         
ALLEGRO_BITMAP *moneda;                   
ALLEGRO_BITMAP *final;
ALLEGRO_BITMAP *pez;
ALLEGRO_BITMAP *pes;
ALLEGRO_BITMAP *pulpo;
ALLEGRO_BITMAP *men_pausa;

#ifdef __cplusplus
}
#endif

#endif /* ALLEGRO_H */