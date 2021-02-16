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
    
#define up 100
#define right 101
#define left 102
#define down 103
#define pausa 104
#define salir 105

#define FPS    60.0

/*ALLEGRO*/
#define LARGO_DISPLAY 640      //TAMANIO DE IMAGEN
#define ANCHO_DISPLAY 544      //TAMANIO DE IMAGEN
    
#define PUNTAJE_X 100.0
#define PUNTAJE_NUMERO_X 200.0
#define NIVEL_X 300.0
#define NIVEL_NUMERO_X 350.0
#define VIDA_X 450.0
#define VISTA_Y 10.0
    
#define VIDA_1_X 500.0
#define VIDA_2_X 540.0
#define VIDA_3_X 580.0
    
#define FONT_NIVEL_X 325
#define FONT_NIVEL_Y 250

    
    
int bienvenida_allegro(void);
int inicializacion();
void draw_background (int,int);
void * entrad_allegro();    /*recibe por comando el movimiento deseado por el jugador*/
void print_map_allegro(int arr [ALTURA][LARGO]);
void print_lvl (int nivel);
void print_vida (void);
int menu_allegro(int punt, int niv,int vid);
void print_gameover(int puntaje);
void destroy_allegro (void);



ALLEGRO_FONT *font;
ALLEGRO_FONT *font_nivel;
ALLEGRO_FONT *font_pausa;
ALLEGRO_BITMAP *mar;                         //que nos permitiran utilizar ciertas funciones de
ALLEGRO_BITMAP *agua;                           //allegro.
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

#ifdef __cplusplus
}
#endif

#endif /* ALLEGRO_H */