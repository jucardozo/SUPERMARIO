   /*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: El Salta, El Alito, El Micho
 *
 * Created on January 14, 2021, 4:23 PM
 */
/*DEFINES PARA EL HARDWARE*/
//buscan ser usadas como instrucciones para el precompilador
//#define RASPI
#define PC      //si estamos usando la libreria de allegro

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>
#include "levels.h"  
#include "motor.h" 
#ifdef PC
#include "allegro.h"
#endif
#ifdef RASPI
#include "rspi.h"
#endif

/*DEFINE PARA EL USO DEL JUEGO*/

#define up 100
#define right 101
#define left 102
#define down 103
#define pausa 104
#define salir 105




/*Globales*/
int nivel=1;
int stop;           //variable que uso para pausar el juego
int fin=1;
int puntaje=0;      /*se lleva el conteo del puntaje*/
int vida=3;         /*se lleva el conteo de las vidas*/
int tecla;          /*guarda el valor de tecla apretado*/
int(*niveles[2])[ALTURA][LARGO];        // es un arreglo de 3 punteros que apuntan a una matriz  
int pos[3];         /*es un arreglo que tiene en el primer elemento la fila , en el segundo la col(de la pos de mario) y en el ultimo la cantidad de movimineto del mapa*/
int lvl_1 [ALTURA][LARGO];  /*niveles vacios*/
int lvl_2 [ALTURA][LARGO];  
int lvl_3 [ALTURA][LARGO]; 


/**********************************/
/**********************************/
/*MUTEX Y THREAD*/
pthread_t th1,th2,th3,th4,th5;                  /*se crean thread para funciones necesarias*/





int main() {
    
    int boton=0 ,i;
#ifdef PC                   //solo se utiliza si lo vamos a jugat con allegro
    int init_correct=inicializacion();
    if (init_correct== -1){
        printf("fallo en inicializacion de ALLEGRO\n");
        vida=0;   
    } 
    pthread_create(&th1,NULL,entrad_allegro,NULL);  //modificado para allegro
#endif
    
#ifdef RASPI
    int init_correct=inicializacion();
    if(init_correct==-1){
        printf("fallo en la inicializacion de la raspi\n");
        vida=0;
    }
    pthread_create(&th1,NULL,entrada_rspi,NULL);  
#endif
     
    niveles[0]=&lvl_1;
    niveles[1]=&lvl_2;
    niveles[2]=&lvl_3;
    
    pthread_create(&th2,NULL,caida,NULL);
    pthread_create(&th3,NULL,enemigo_pez,NULL);
    pthread_create(&th4,NULL,enemigo_pes,NULL);
    pthread_create(&th5,NULL,enemigo_pulpo,NULL);
    
    while(vida>0){
        switch(nivel){          //habilita el control, automatico, de cada enemigo en cada nivel//
            case 1 ://nivel 1
                    creacionmap(nivel);
                    pos[0]=0;
                    pos[1]=0;
                    pos[2]=0;
#ifdef PC
                    draw_background (puntaje,nivel);
                    al_flip_display();                
                    print_lvl (nivel);
                    print_map_allegro(*niveles[0]);
#endif   
#ifdef RASPI
                    printf("**************NIVEL 1*****************\n");
                    printmat(*niveles[0]);  //imprime el nivel
#endif
                    i=0;fin=1; break;
            case 2 ://nivel 2
                    creacionmap(nivel);
                    pos[0]=0;
                    pos[1]=0;
                    pos[2]=0;
#ifdef PC
                    draw_background (puntaje,nivel);
                    al_flip_display();  
                    print_lvl (nivel);
                    print_map_allegro(*niveles[1]);
#endif
#ifdef RASPI
                  printf("**************NIVEL 2*****************\n");
                  printmat(*niveles[1]);  
#endif
                    
                    i=1;fin=1;boton=0;break;
            case 3 ://nivel 3
                    creacionmap(nivel);
                    pos[0]=0;
                    pos[1]=0;
                    pos[2]=0;
#ifdef PC
                    draw_background (puntaje,nivel);
                    al_flip_display(); 
                    print_lvl (nivel);
                    print_map_allegro(*niveles[2]);
#endif
#ifdef RASPI
                    printf("**************NIVEL 3*****************\n");
                    printmat(*niveles[2]);  //
#endif
                    boton=0;i=2;fin=1;break;
            default:
                fin=0;vida=0;break;
        }
        
        while(fin){
            if(tecla !=0 ){       /*si el boton es igual a cero , entonces hubo problema en la entrada*/
            
                ctrl_posicion(*niveles[i],pos);    /*busca a mario en el mapa y devuelve su posicion en pos */
                boton=tecla;
                if(boton==pausa){
                    stop=1;
                    tecla=0;
#ifdef RASPI
                    menu();
#endif
#ifdef PC
                    menu_allegro(puntaje,nivel,vida);
#endif

                    if(tecla==salir){          //salida provocada por el menu
                        fin=0;
                        vida=0;
                    }
                }
                else if (boton==salir){         //salida provocada por display
                        fin=0;
                        vida=0;
                }
                int val=reglas(*niveles[i],boton); /*val, guarda la evaluacion de reglas*/
                if(val==0){                  /*si el movimiento esta permitido , lo mueve efectivamente*/
                    
                    movimiento(*niveles[i],boton); /*realza el movimiento efectivo, solo de Mario*/         
#ifdef PC
                    print_map_allegro(*niveles[i]);
#endif
#ifdef RASPI
                    printmat(*niveles[i]);
#endif
                    tecla=0;
                }
                else if(val==2){             /*recogio una moneda*/   
                    puntaje+=10;
#ifdef RASPI
                    printf("PUNTAJE:%d\n",puntaje);  
#endif
                    movimiento(*niveles[i],boton);                    
#ifdef PC            
                    draw_background(puntaje,nivel);
                    print_map_allegro(*niveles[i]);
#endif
#ifdef RASPI
                 printmat(*niveles[i]);   
#endif
                    tecla=0;
                }
                else if(val==4){    //paso de nivel
                    puntaje+=100;                               /*si es 4 es porque llego a la meta*/
#ifdef RASPI
                    printf("Bien jugado,pasaste de nivel\n");
                    printf("PUNTAJE: %d\n",puntaje);
#endif 
                    tecla=0;
                    nivel+=1;
                    fin=0;
#ifdef PC            
                    draw_background(puntaje,nivel);
                    al_flip_display();
#endif
                }
                else if(val==3){
                    vida-=1;                                    /*si es 3 es porque mario perdio una vida*/
                    if(vida<0){
#ifdef PC
                        print_gameover(puntaje);
#endif
#ifdef RASPI
                        printf("PUNTAJE: %d\n",puntaje);
                        printf("GAME OVER\n");
#endif 
                        fin =0;
                        tecla=0;
                        
                    }
                    else
                    {           
#ifdef RASPI
                        printf("Perdiste una vida, te quedan: %d\n",vida);
#endif
#ifdef PC
                        print_vida();
#endif
                        tecla=0;
                    }
                }
             
            }
#ifdef PC           
            else{           //si no se detecto niguna entra por el teclado,acrualiza pantalla       

                print_map_allegro(*niveles[i]);
                print_vida();
            }
 #endif         
        }
        
    }
    stop=pausa;
    
#ifdef PC
    /*DESTROY ALLEGRO*/
    destroy_allegro();
#endif
    return 0;
}
