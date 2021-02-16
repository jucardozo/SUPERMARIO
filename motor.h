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

    
    
void bienvenida (void);
void printmat(int arr[ALTURA][LARGO]); /*creo que no es necesario pasarle una arreglo*/
void movimiento(int arr[ALTURA][LARGO],int boton);  /*realiza el movimiento efectivo de mario*/
void ctrl_posicion(int arr[ALTURA][LARGO],int pos[3]);  /*Funcion que busca la posicion de mario en el mapa (Matriz), se le pasa el nivel y la cantidad de movimiento del mapa*/
int reglas (int arr[ALTURA][LARGO],int boton);      /*evalua la validez del movimietno del mario*/
int menu(void);

void * caida ();    /*caida de mario , impuesta por la gravedad */
void *entrad();
void * enemigo_pez();
void * enemigo_pes();
void * enemigo_pulpo();


#ifdef __cplusplus
}
#endif

#endif /* MOTOR_H */