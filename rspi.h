/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   rspi.h
 * Author: jucardozo
 *
 * Created on February 16, 2021, 10:40 AM
 */

#ifndef RSPI_H
#define RSPI_H

#ifdef __cplusplus
extern "C" {
#endif
    

#include "levels.h"

/*DEFINES*/
#define up 100
#define right 101
#define left 102
#define down 103
#define pausa 104
#define salir 105
#define THRESHOLD 40	//Límite a partir del cual se mueve el LED encendido
#define HASTA_LED 54	//Limite de LED para imprimir en pantalla

/*PROTOTIPOS*/
int inicializacion(void);
void entrada_rspi ();
void print_mat_rspi(int arr [ALTURA][LARGO]);


#ifdef __cplusplus
}
#endif

#endif /* RSPI_H */

