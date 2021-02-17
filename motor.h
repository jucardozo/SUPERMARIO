/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#ifndef MOTOR_H
#define MOTOR_H

#ifdef __cplusplus
extern "C" {
#endif
    
#include "levels.h"
#include "motor.h"
#include "allegro.h" 
    
    
/*PROTOTIPOS*/
void bienvenida (void);                                     //funcion que le da la bievenida al usuario por display, no recibe nada y no devuellve nada
void movimiento(int arr[ALTURA][LARGO],int boton);          //funcion que recibe la matriz nivel, y un arreglo en donde se va a guarda la posicion de mario y no devuelve nada
void ctrl_posicion(int arr[ALTURA][LARGO],int pos[3]);      //funcion que recibe la matriz nivel, y una matriz en donde se va a guarda la posicion de mario y no devuelve nada
void printmat(int arr[ALTURA][LARGO]);                      //funcion que imprime la matriz nivel dependiendo de donde este el mario de 16x16, recibe una matriz (nivel) y no devuelve nada
int reglas (int arr[ALTURA][LARGO],int boton);              //funcion que se le pasa una matriz (nivel) en el que se esta jugando, y el comando accionado (boton) y no devuelve nada
int menu(void);                                             //funcion que imprime el menu de pausa, no recibe nada y devuelve un 0

/*THREADS*/
void * caida ();                                            //thread para la caida de mario , impuesta por la gravedad                                            
void * enemigo_pez();                                       //thread que controla los movimientos del pez que va mas rapido en el mapa
void * enemigo_pes();                                       //thread que controla los movimientos del pes que va mas lento en el mapa
void * enemigo_pulpo();                                     //thread que controla los movimientos del pulpo en el mapa


#ifdef __cplusplus
}
#endif

#endif /* MOTOR_H */