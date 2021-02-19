/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "rspi.h"
#include "disdrv.h"
#include "joydrv.h"
#include "levels.h"


extern int tecla;
extern int pos[3];
extern int vida;
extern int fin;
extern int stop;

extern int lvl_1[ALTURA][LARGO];
extern int lvl_2[ALTURA][LARGO];
extern int lvl_3[ALTURA][LARGO];

int inicializacion(void){
        joy_init();                 //se inicializa el joystick
	disp_init();	
	disp_clear();
	return 0;
}



void entrada_rspi (void){
    jcoord_t mycoord;            //se crea una variable tipo jcoord, q contendra las coordenadas de x e y
    jswitch_t myswitch;            //almacena el valor del pulsador, se lo utilizara para la pausa del juego
    printf("\n");
    printf("hola, entre a la entrad de raspi\n");
    printf("\n");
    while(1){
        joy_update();           //actualiza la posicion del joystick, sin realizar ningun movimiento efectivo
        mycoord=joy_get_coord();    //obtengo las coordenadas para luego compararlas
        myswitch=joy_get_switch();  //guarda el estado del pulsador 
        if(mycoord.x > THRESHOLD)
	{
		tecla = right;
	}
	if(mycoord.x < -THRESHOLD)
	{
		tecla = left;
	}
	if(mycoord.y > THRESHOLD)
	{
		tecla = up;
	}
	if(mycoord.y < -THRESHOLD)
	{
		tecla = down;
	}
        if(myswitch==J_PRESS){       //se pulso el pulsador del joystick
            tecla=pausa;
        }
        
    }
}

void print_mat_rspi(int arr[ALTURA][LARGO]){
    dcoord_t mypoint;

    if(((16+pos[2])-pos[1])<=8){        //se lee la columna en donde esta mario y se mueve le mapa si esta en la mitad
        pos[2]+=4;                      //la cantidad de este movimineto se guarda en el tercer elemento del arreglo, se elije por default que se mueva de a 4
    }
    if(pos[2]<HASTA_LED){
        for (int i=0;i<16;i++){
            for(int p=pos[2]; p<(16+pos[2]);p++){
		switch(arr[i][p]){
		    case PRECIPICIO:
                    case AGUA:
			mypoint.x=p-pos[2];
			mypoint.y=i;
			disp_write(mypoint,D_OFF);
			break;
                    case BLOQUE:
                    case ALGA:
                    case FINAL:
                    //case MONEDA:
                    case PEZ:
                    case PES:
                    case PULPO:
                    case MARIO:
			mypoint.x=p-pos[2];
			mypoint.y=i;
			disp_write(mypoint,D_ON);
			break;			
		}                
            }
        }
    disp_update();
    }
    else{
        for (int i=0;i<16;i++){
            for(int p=HASTA_LED; p<70;p++){
               switch(arr[i][p]){
		    case PRECIPICIO:
                    case AGUA:
			mypoint.x=p-HASTA_LED;
			mypoint.y=i;
			disp_write(mypoint,D_OFF);
			break;
                    case BLOQUE:
                    case ALGA:
                    case FINAL:
                    //case MONEDA:
                    case PEZ:
                    case PES:
                    case PULPO:
                    case MARIO:
			mypoint.x=p-HASTA_LED;
			mypoint.y=i;
			disp_write(mypoint,D_ON);
			break;			
		}  
            }
            
        } 
    disp_update();
    }
}
