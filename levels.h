/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#ifndef LEVELS_H
#define LEVELS_H

#ifdef __cplusplus
extern "C" {
#endif
    
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "levels.h"

/*DEFINES*/
#define SUPERFICIE 11
#define ALTURA 16
#define LARGO 70
#define BLOQUE 4
#define ALGA 2
#define FINAL 5
#define MONEDA 3
#define PRECIPICIO 9
#define PEZ 6
#define PES 8
#define FUEGO 10
#define PULPO 7
#define MARIO 1
#define AGUA 0
#define MOV_PULPO 4
#define MAX_ENEM 18
#define LARGO_ELEMENTO 40
#define ALTO_ELEMENTO 34
#define VELOCIDAD_PEZ 1.0
#define VELOCIDAD_PES 2.0
#define VELOCIDAD_PULPO 1.5
    
    
/*PROTOTIPOS*/
void creacionmap(int);                  //esta funcion crea los mapas, niveles: 1,2 y 3. en matrices de tamanio ALTOxLARGO, recibe que nivel es y no devuelve nada

#ifdef __cplusplus
}
#endif

#endif /* LEVELS_H */