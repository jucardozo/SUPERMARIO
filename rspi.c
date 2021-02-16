/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "rspi.h"

extern int tecla;
extern int pos[3];
extern int vida;
extern int fin;
extern int stop;

int inicializacion(void){
        joy_init();                  //se inicializa el joystick
        init_sound();                //se inicializa el sonido
        if(player_status==READY){   //si el audio esta listo para usarse , lo reproduce
            set_file_to_play("musica.wav"); //controlar , posiblemente se lo este mandando mal
            play_sound();
        }
        else{
            return -1;
        }
        
}



void entrada_rspi (){
    jcoord_t mycoord;            //se crea una variable tipo jcoord, q contendra las coordenadas de x e y
    jswitch myswitch;            //almacena el valor del pulsador, se lo utilizara para la pausa del juego
    int difx=0,dify=0;
    while(1){
        joy_update();           //actualiza la posicion del joystick, sin realizar ningun movimiento efectivo
        mycoord=joy_get_coord();    //obtengo las coordenadas para luego compararlas
        myswitch=jot_get_switch();  //guarda el estado del pulsador 
        difx=(mycoord.x-pos[1]);    //se saca la diferencia entre la posicion real de mario , con la actualizacion del joystick
        dify=(mycoord.y-pos[0]);
        switch(difx){               //evalua movimientos en x o en columnas
            case 1:                 //si la diferencia es 1 entonces se esta moviendo a la derecha
                tecla=right;
                break;
            case -1:
                tecla=left;
                break;
            default:               //si no encontro diferencia , entonces no se movio en x
                break;
        }
        switch(dify){              //analiza movimientos en y o en filas
            case 1:
                tecla=down;
                break;
            case -1:
                tecla=up;
                break;
            default:
                break;                                        
        }        
        if(myswitch==J_PRESS){       //se pulso el pulsador del joystick
            tecla=pausa;
        }
        
    }
}

