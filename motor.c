/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#include "motor.h"


extern int tecla;                           //variables que necesito de main.c para algunas funciones
extern int reinicio;
extern int pos[3];
extern int stop;
extern int(*niveles[2])[ALTURA][LARGO];
extern int puntaje;
extern int vida;
extern int nivel;


extern int lvl_1[ALTURA][LARGO];            //la matriz de los niveles que estan en main.c
extern int lvl_2[ALTURA][LARGO];
extern int lvl_3[ALTURA][LARGO];

pthread_mutex_t lock1,lock2;                //para crear candados en las funciones


void bienvenida (void){             //funcion que le da la bievenida al usuario por display, no recibe nada y no devuellve nada
    printf("Bienvenido a la beta del super mario\n");
}


void movimiento(int arr[ALTURA][LARGO], int boton){         //funcion que realiza el movimiento efectivo de mario, recibe un arreglo (nivel) e un int (boton) y no devuelve nada
    
   pthread_mutex_lock(&lock1);      /*esta funcion tiene un candado , de tal manera que no se pisen con otra llamdada*/
   int i=pos[0];                    /*es decir que trabaja solo con una llamda y luego atiende las siguientes*/
   int j=pos[1];
   switch(boton){
       case UP:
           arr[i-1][j]=1;
           arr[i][j]=0;
           break;
       case DOWN:
           arr[i+1][j]=1;
           arr[i][j]=0;
           break;
       case RIGHT:
           arr[i][j+1]=1;
           arr[i][j]=0;
           break;
       case LEFT:
           arr[i][j-1]=1;
           arr[i][j]=0;
           break;
   }
   pthread_mutex_unlock(&lock1);
}

void ctrl_posicion(int arr[ALTURA][LARGO],int pos[3]){              //funcion que recibe la matriz nivel, y una matriz en donde se va a guarda la posicion de mario y no devuelve nada
    
    pthread_mutex_lock(&lock2);     /*tambien posee un candado*/
    if((16+pos[2])<LARGO){          /*en el ultimo elemento se guarda la cnatidad de movimiento del mapa*/
        for (int col=pos[2];col<(16+pos[2]);col++){     /*se centra la busqueda de mario en un cuadrado de 16 por 16 que coincide con lo mostrado por printmat*/
            for(int fil=0;fil<16;fil++){
                if(arr[fil][col]==1){
                    pos[0]=fil;
                    pos[1]=col;
                }
            }
        }
    }
    else{
        for (int col=pos[2];col<LARGO;col++){
            for(int fil=0;fil<16;fil++){
                if(arr[fil][col]==1){
                    pos[0]=fil;
                    pos[1]=col;
                }

            }      
        }
    }
    pthread_mutex_unlock(&lock2);
}

void printmat(int arr[ALTURA][LARGO]){          //funcion que imprime la matriz nivel dependiendo de donde este el mario de 16x16, recibe una matriz (nivel) y no devuelve nada
    if(((16+pos[2])-pos[1])<=8){        //se lee la columna en donde esta mario y se mueve le mapa si esta en la mitad
        pos[2]+=4;                      //la cantidad de este movimineto se guarda en el tercer elemento del arreglo, se elije por default que se mueva de a 4
    }  
    if(pos[2]<56){
        for (int i=0;i<16;i++){
            for(int p=pos[2]; p<(16+pos[2]);p++){
                printf("%d",arr[i][p]);
            }
            printf("\n");
        }
    }
    else{
        for (int i=0;i<16;i++){
            for(int p=56; p<(70);p++){
                printf("%d",arr[i][p]);
            }
            printf("\n");
        }
    }
}



int reglas(int arr[ALTURA][LARGO],int boton){                   //funcion que se le pasa una matriz (nivel) en el que se esta jugando, y el comando accionado (boton) y no devuelve nada
                            /*se devuelve 1 si el movimiento no esta permitido,2 si agarro una moneda,3 si murio 4 si llego al final y 0 si el movimineto esta permitido*/
    int i=pos[0];           /*copio la posicion de actual de mario*/
    int j=pos[1];           /*i es fila y j es col*/
 
    if (boton==UP){
        i-=1;
    }
    else if (boton==DOWN){
        i+=1;
    }
    else if(boton ==RIGHT){
        j+=1;
    }
    else if(boton==LEFT){                   /*CONTROLAR QUE NO SEA NEGATIVO*/
        j-=1;
    }    
    switch(arr[i][j]){
            case BLOQUE: 
            case ALGA:
            case SUPERFICIE:return 1; break;    /* si es un obstaculo, devuelvo 1*/
            case MONEDA: return 2; break;       /*si es una moneda, devuelvo 2 */
            case PULPO:
            case PEZ:
            case PES:
            case PRECIPICIO:
            case FUEGO: return 3;break;         /*si es un enemigo o maleficio para mario, devuelvo 3*/
            case FINAL: return 4;break;         /*si es la meta, devuelvo 4*/
            default: return 0;break;            /*si es otra cosa, devuelvo 0*/
    }
}


int menu(void){                             //funcion que imprime el menu de pausa, no recibe nada y devuelve un 0
    printf("************MENU(BETA)*************\n");
    printf("PUNTAJE:%d\n",puntaje);
    printf("VIDA:%d\n",vida);
    printf("NIVEL:%d\n",nivel);
   // printf("Para reanudar el juego presione nuevamente p, para finalizar la partida presione f\n");
    int fin=1;
    while(fin){
        if( tecla==PAUSA){
            stop=0;
            fin=0;
            tecla=0;
             printf("reanudando juego...\n");
        }  
        else if( tecla==SALIR){
            fin=0;
            printf("saliendo del juego....\n");
        }
            
    }
   
    return 0;
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                                                //
//                                                    /////////////////////////                                                   //
//                                                    ///*FUNCIONES THREADS*///                                                   //
//                                                    /////////////////////////                                                   //
//                                                                                                                                //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void*  caida ( ){                           //thread para la caida de mario , impuesta por la gravedad
    int boton_aux=DOWN;
    int val;
    
    while(1){
        while(stop){        //pauso el thread , porque pausaron le juego
        }
        sleep(1);
        ctrl_posicion(*niveles[nivel-1],pos);
        val=reglas(*niveles[nivel-1],boton_aux);
        if(val==0){                  /*si el movimiento esta permitido , lo mueve efectivamente*/
            movimiento(*niveles[nivel-1],boton_aux); /*realza el movimiento efectivo, solo de Mario*/            
        }
        else if(val==2){             /*recogio una moneda*/          
            puntaje+=10;
            printf("PUNTAJE:%d\n",puntaje);
            movimiento(*niveles[nivel-1],boton_aux);
        }
        else if(val==4){     
            puntaje+=100;
            printf("Bien jugado,pasaste primer nivel\n");
            printf("PUNTAJE: %d",puntaje);          
        }
        else if(val==3){
               
            vida-=1;
            if(vida<0){
                printf("GAME OVER\n");
                printf("PUNTAJE: %d",puntaje);
            }
        }

    }
    
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                                                //
//                                                    ////////////////////////                                                    //
//                                                    ///*ENEMIGOS THREADS*///                                                    //
//                                                    ////////////////////////                                                    //
//                                                                                                                                //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void * enemigo_pez(){               //thread que controla los movimientos del pez que va mas rapido en el mapa
    while(1){
        printf("reinicie papa\n");
        int pez = 1;                //variable que uso para el while
        int reboot=0;

        int *pezes [MAX_ENEM];             //creo arreglo de punteros para guardar las posiciones de los peces  
        int * dir_niveles [3] = {&lvl_1[0][0],&lvl_2[0][0],&lvl_3[0][0]};       //arreglo depunteros que contiene la direccion del primer elemento de la matriz de cada nivel

        pezes[0]= &lvl_1[4][24];     //estas son las posiciones iniciales de los peces en la matriz
        pezes[1]= &lvl_1[9][26];     //PARA EL NIVEL 1
        pezes[2]= &lvl_1[8][37];  

        pezes[3]= &lvl_2[8][5];     //estas son las posiciones iniciales de los peces en la matriz
        pezes[4]= &lvl_2[8][18];     //PARA EL NIVEL 2
        pezes[5]= &lvl_2[3][24];
        pezes[6]= &lvl_2[10][35];     
        pezes[7]= &lvl_2[13][43];
        pezes[8]= &lvl_2[12][58]; 

        pezes[9]= &lvl_3[4][14];     //estas son las posiciones iniciales de los peces en la matriz
        pezes[10]= &lvl_3[10][16];     //PARA EL NIVEL 3
        pezes[11]= &lvl_3[12][18];
        pezes[12]= &lvl_3[6][22];     
        pezes[13]= &lvl_3[8][24];
        pezes[14]= &lvl_3[5][27];
        pezes[15]= &lvl_3[11][29];     
        pezes[16]= &lvl_3[7][48];     
        pezes[17]= &lvl_3[3][56];

        
        int nivel_var = nivel;
        int cant_pez = 3*nivel_var;           //cantidad de enemigos PEZ por nivel

        int q=0;
        int i;
        int hasta;
        int valor1 [MAX_ENEM];		//arreglo que guardo las posiciones de los peZes
        int valor2 [MAX_ENEM];		//arreglo que salvo las posiciones de los peZes

        if(nivel == 1){                     //cantidad de enemigos PEZ por nivel y hasta donde llegan en el arreglo de punteros
            i=0;
            hasta=3;
        }
        else if (nivel == 2){
            i=3;
            hasta=9;
        }
        else{
            i=9;
            hasta=18;
        }

        while (  (pez)  && (nivel_var==nivel)){                //hasta que no hayan peZes o hasta que cambie de nivel      
            printf("reinicio:%d,pez:%d, nivel_var:%d\n",reinicio,pez,nivel_var);
            while (stop){               //para la pausa

            }
            if(reinicio==1){
                printf("pongo pez en cero\n");
                pez=0;
                reboot=1;
            }

            if(cant_pez == 0){
                                        //que pare si no hay mas peZes
                pez = 0;
            }

            else if (  (  ( pezes[i] - (dir_niveles[nivel_var-1]) )    % LARGO  )  == 0){         //si esta en la columna 0, entonces listo el PEZ

                *pezes[i]=AGUA;                                                     //que me ponga agua
                                                                      //ya el primer PEZ no existe
                while(i < (hasta-1)){                               //ahora el arreglo tiene solo dos pescados, en pezes[0] y en pezes[1] .
                    pezes[i]=pezes[i+1];
                    valor1[i]=valor1[i+1];
                    valor2[i]=valor2[i+1];
                    i++;
                }		
                cant_pez -=1;                                                   //bajo la cantidad de PEZ porque van desapareciendo
                hasta -=1;

            }		

            else{								//SI NO ESTA EN LA PRIMER COLUMNA
                if(q<cant_pez){								//SI SE MUEVE POR PRIMERA VEZ
                    while (i < hasta){		            
                        valor1[i] = *(pezes[i]-1);               //guardo el valor para salvar lo que valia antes de que caiga el pez               
                        if(valor1[i]==MARIO){       
                            vida-=1;
#ifdef RASPI
                            printf("Perdiste una vida , te quedan:%d\n",vida);
#endif
                        }        
                                //aca ya salve el valor de lo que habia y se guarda en valor

                        *(pezes[i]-1) = PEZ;            //muevo el PEZ para la izquierda        
                        * pezes[i] = AGUA;             //cuando se movio por primera vez, que me ponga agua donde arranco el PEZ
                        q++;                                            //todo es para que avance un pez, aumento i para que vaya al otro pez

                        pezes [i] -= 1;					//la nueva direeccion del pez es la de la izquuierda
                        i++;
                    }
                    sleep(VELOCIDAD_PEZ);             //velocidad de los peZes
                }			
                else{
                    while (i < hasta){		        
                        valor2[i] = *(pezes[i]-1);               //guardo el valor para salvar lo que valia antes de que caiga el pez	
                        if(valor2[i]==MARIO){       
                            vida-=1;
#ifdef RASPI
                            printf("Perdiste una vida , te quedan:%d\n",vida);
#endif
                        }     
                                    //aca ya salve el valor de lo que habia y se guarda en valor
                        *(pezes[i]-1) = PEZ;            //muevo el PEZ para la izquierda	
                        * pezes [i] = valor1[i];        //salvo lo que habia antes	       


                        pezes [i] -= 1;					//la nueva direeccion del pez es la de la izquuierda
                        if ((valor2[i] == MARIO) || (valor2[i] == PULPO) || (valor2[i] == PES) || (valor2[i] == PEZ)){
                            valor2[i] = AGUA;                              //si justo hay otra cos, que me ponga agua
                        }
                        valor1 [i]= valor2[i];			//pongo en valor 1 lo que esta valor 2  asi ya se vuelve a poner otra vez
                        i++;                            //todo es para que avance un pez, aumento i para que vaya al otro pez
                    }
                    sleep(VELOCIDAD_PEZ);             //velocidades de los peZes
                }

            }		

            if(nivel_var == 1){                     //vuelvo a arrancar desde el primer pez
                i=0;
            }
            else if (nivel_var == 2){
                i=3;
            }
            else{
                i=9;
            }

        }  
        if(reboot==0){
            while(nivel_var == nivel){          //esto esta si ya no quedaron peces, el thread vuelve a arrancar cuando cambia de nivel
                printf("estor afuera\n");
            }
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void * enemigo_pes(){           //thread que controla los movimientos del pes que va mas lento en el mapa
    while(1){
        int pes = 1;                //variable que uso para el while
        int reboot=0;
        int *peses [MAX_ENEM];             //creo arreglo de punteros para guardar las posiciones de los peces  
        int * dir_niveles [3] = {&lvl_1[0][0],&lvl_2[0][0],&lvl_3[0][0]};       //arreglo depunteros que contiene la direccion del primer elemento de la matriz de cada nivel

        peses[0]= &lvl_1[5][12];     //estas son las posiciones iniciales de los peces en la matriz
        peses[1]= &lvl_1[11][22];
        peses[2]= &lvl_1[6][44];      

        peses[3]= &lvl_2[12][8];     //estas son las posiciones iniciales de los peces en la matriz
        peses[4]= &lvl_2[6][21];     //PARA EL NIVEL 2
        peses[5]= &lvl_2[11][28];
        peses[6]= &lvl_2[4][35];     
        peses[7]= &lvl_2[4][46];
        peses[8]= &lvl_2[9][61];

        peses[9]= &lvl_3[7][11];     //estas son las posiciones iniciales de los peces en la matriz
        peses[10]= &lvl_3[11][16];     //PARA EL NIVEL 3
        peses[11]= &lvl_3[13][17];
        peses[12]= &lvl_3[3][20];     
        peses[13]= &lvl_3[6][29];
        peses[14]= &lvl_3[9][35];
        peses[15]= &lvl_3[4][41];     
        peses[16]= &lvl_3[8][56];     
        peses[17]= &lvl_3[12][64];

        
        int nivel_var = nivel;
        int cant_pes = 3*nivel_var;           //cantidad de enemigos PES por nivel

        int q=0;
        int i;
        int hasta;
        int valor3 [MAX_ENEM];		//arreglo que guardo las posiciones de los peSes
        int valor4 [MAX_ENEM];		//arreglo que salvo las posiciones de los peSes

        if(nivel == 1){                     //cantidad de enemigos PES por nivel y hasta donde llegan en el arreglo de punteros
            i=0;
            hasta=3;
        }
        else if (nivel == 2){
            i=3;
            hasta=9;
        }
        else{
            i=9;
            hasta=18;
        }

        while ((pes) && (nivel_var==nivel)){                //hasta que no hayan peSes o hasta que cambie de nivel 
            while (stop){               //para la pausa
            }
            if(reinicio==1){
                pes=0;
                reboot=1;
            }

            if(cant_pes == 0){

                pes = 0;                    //que pare si no hay mas peSes
            }

            else if (  (  ( peses[i] - (dir_niveles[nivel_var-1]) )    % LARGO  )  == 0){         //si esta en la columna 0, entonces listo el PES

                *peses[i]=AGUA;                                                     //que me ponga agua
                                                                      //ya el primer PES no existe
                while(i < (hasta-1)){                               //ahora el arreglo tiene solo dos pescados, en peses[0] y en peses[1] .
                    peses[i]=peses[i+1];
                    valor3[i]=valor3[i+1];
                    valor4[i]=valor4[i+1];
                    i++;
                }		
                cant_pes -=1;                                                   //bajo la cantidad de PES porque van desapareciendo
                hasta -=1;

            }		

            else{								//SI NO ESTA EN LA PRIMER COLUMNA
                if(q<cant_pes){								//SI SE MUEVE POR PRIMERA VEZ
                    while (i < hasta){		            
                        valor3[i] = *(peses[i]-1);               //guardo el valor para salvar lo que valia antes de que caiga el pes               
                        if(valor3[i]==MARIO){       
                            vida-=1;
#ifdef RASPI
                            printf("Perdiste una vida , te quedan:%d\n",vida);
#endif
                        }        
                                //aca ya salve el valor de lo que habia y se guarda en valor

                        *(peses[i]-1) = PES;            //muevo el PES para la izquierda        
                        * peses[i] = AGUA;             //cuando se movio por primera vez, que me ponga agua donde arranco el PES
                        q++;                                            //todo es para que avance un pes, aumento i para que vaya al otro pes

                        peses [i] -= 1;					//la nueva direeccion del pes es la de la izquuierda
                        i++;
                    }
                    sleep(VELOCIDAD_PES);                 //velocidad de los peSes
                }			
                else{
                    while (i < hasta){		        
                        valor4[i] = *(peses[i]-1);               //guardo el valor para salvar lo que valia antes de que caiga el pes	
                        if(valor4[i]==MARIO){       
                            vida-=1;
#ifdef RASPI
                            printf("Perdiste una vida , te quedan:%d\n",vida);
#endif
                        } 
                                    //aca ya salve el valor de lo que habia y se guarda en valor
                        *(peses[i]-1) = PES;            //muevo el PES para la izquierda	
                        * peses [i] = valor3[i];        //salvo lo que habia antes	       

                        peses [i] -= 1;	
                        if ((valor4[i] == MARIO) || (valor4[i] == PULPO) || (valor4[i] == PES) || (valor4[i] == PEZ)){
                            valor4[i] = AGUA;                              //si justo hay otra cos, que me ponga agua
                        }                               //la nueva direeccion del pes es la de la izquuierda
                        valor3 [i]= valor4[i];			//pongo en valor 3 lo que esta valor 4  asi ya se vuelve a poner otra vez
                        i++;                            //todo es para que avance un pes, aumento i para que vaya al otro pes
                    }
                    sleep(VELOCIDAD_PES);         //velocidad de los peSes
                }

            }		

            if(nivel_var == 1){                     //vuelvo a arrancar desde el primer pes
                i=0;
            }
            else if (nivel_var == 2){
                i=3;
            }
            else{
                i=9;
            }

        }  
        if(reboot==0){
            while(nivel_var == nivel){

            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void * enemigo_pulpo(){                 //thread que controla los movimientos del pulpo
    while(1){


        int *pulpos [MAX_ENEM];             //creo arreglo de punteros para guardar las posiciones de los pulpos

        pulpos[0]= &lvl_1[10][6];     //estas son las posiciones iniciales de los pulpos en la matriz
        pulpos[1]= &lvl_1[12][28];     //PARA EL NIVEL 1
        pulpos[2]= &lvl_1[11][45];

        pulpos[3]= &lvl_2[8][13];     //estas son las posiciones iniciales de los pulpos en la matriz
        pulpos[4]= &lvl_2[11][22];     //PARA EL NIVEL 2
        pulpos[5]= &lvl_2[8][31];
        pulpos[6]= &lvl_2[8][38];    
        pulpos[7]= &lvl_2[9][53];     
        pulpos[8]= &lvl_2[9][63];

        pulpos[9]= &lvl_3[13][21];     //estas son las posiciones iniciales de los peces en la matriz
        pulpos[10]= &lvl_3[7][26];     //PARA EL NIVEL 3
        pulpos[11]= &lvl_3[8][34];
        pulpos[12]= &lvl_3[11][36];     
        pulpos[13]= &lvl_3[13][41];
        pulpos[14]= &lvl_3[10][42];
        pulpos[15]= &lvl_3[11][53];     
        pulpos[16]= &lvl_3[10][55];     
        pulpos[17]= &lvl_3[7][63];

        
        
        int nivel_var = nivel;
        int cant_pulpo = 3*nivel_var;     //cantidad de enemigos PULPO por nivel 
        
        int f;
        int hasta;
        int q=0;
        int k;
        int valor5 [MAX_ENEM];	//arreglo que guardo las posiciones de los pulpos
        int valor6 [MAX_ENEM];	//arreglo que salvo las posiciones de los pulpos

        if(nivel == 1){                     //cantidad de enemigos PEZ por nivel
            f=0;
            hasta=3;
        }
        else if (nivel == 2){
            f=3;
            hasta=9;
        }
        else{
            f=9;
            hasta=18;
        }

        while (nivel_var==nivel){       //hasta que cambie de nivel, si cambia, vuelve a arrancar con nivel_var con otro numerp
            while (stop){               //para la pausa
            }
            if(q<cant_pulpo){
                while(f<hasta){				
                    valor5 [f]= *(pulpos[f]-LARGO);               //guardo el valor para salvar lo que valia antes de que caiga el pulpo
                    if(valor5[f]==MARIO){       
                            vida-=1;
#ifdef RASPI
                            printf("Perdiste una vida , te quedan:%d\n",vida);
#endif
                        } 
                                    //aca ya salve el valor de lo que habia y se guarda en valor
                    *(pulpos[f]-LARGO) = PULPO;            //muevo el PULPO 
                    * pulpos[f] = AGUA;             //cuando se movio por primera vez, que me ponga agua donde arranco el PULPO			
                    q++;
                    pulpos [f] -= LARGO;					//la nueva direeccion del pulpo es la de una para arriba
                    f++;							//hasta el ultimpo pulpo, todos se mueven para arriba
                }
                sleep(VELOCIDAD_PULPO);     //velocidad de los pulpos
            }	
            else{		
                for(k=0;k<MOV_PULPO;k++){				//MOVIMIENTO DEL PULPO PARA ARRIBA
                    while(f<hasta){			
                        valor6 [f]= *(pulpos[f]-LARGO);               //guardo el valor para salvar lo que valia antes de que caiga el pulpo	
                        if(valor6[f]==MARIO){       
                            vida-=1;
#ifdef RASPI
                            printf("Perdiste una vida , te quedan:%d\n",vida);
#endif
                        } 
                                            //aca ya salve el valor de lo que habia y se guarda en valor
                        *(pulpos[f]-LARGO) = PULPO;            //muevo el PULPO 
                                                                   //aca entro cuando el PULPO ya se movio mas de una vez
                        * pulpos [f] = valor5[f];        //salvo lo que habia antes		
                        pulpos [f] -= LARGO;				//la nueva direeccion del pulpo es la de una para arriba
                        if ((valor6[f] == MARIO) || (valor6[f] == PULPO) || (valor6[f] == PES) || (valor6[f] == PEZ)){
                            valor6[f] = AGUA;
                        }
                        valor5 [f]= valor6[f];				//pongo en valor 1 lo que esta valor 2  asi ya se vuelve a poner otra vez
                        f++;							//hasta el ultimpo pulpo, todos se mueven para arriba
                    }
                    sleep(1.5);     //velocidad de los peSes
                    if(nivel_var == 1){                     //vuelvo a arrancar desde el primer pulpo
                        f=0;
                    }
                    else if (nivel_var == 2){
                        f=3;
                    }
                    else{
                        f=9;
                    }
                }		
                for(k=0;k<MOV_PULPO;k++){				//MOVIMIENTO DEL PULPO PARA ABAJO
                    while(f<hasta){					
                        valor6 [f]= *(pulpos[f]+LARGO);               //guardo el valor para salvar lo que valia antes de que caiga el pulpo
                        if(valor6[f]==MARIO){       
                            vida-=1;
#ifdef RASPI
                            printf("Perdiste una vida , te quedan:%d\n",vida);
#endif
                        } 
                                                                   //aca ya salve el valor de lo que habia y se guarda en valor
                        *(pulpos[f]+LARGO) = PULPO;            //muevo el PULPO 
                                                                //aca entro cuando el PULPO ya se movio mas de una vez
                        * pulpos [f] = valor5[f];        //salvo lo que habia antes                                        
                        pulpos [f] += LARGO;				//la nueva direeccion del pulpo es la de una para abajo
                        if ((valor6[f] == MARIO) || (valor6[f] == PULPO) || (valor6[f] == PES) || (valor6[f] == PEZ)){
                            valor6[f] = AGUA;                              //si justo hay otra cos, que me ponga agua
                        }
                        valor5 [f]= valor6[f];				//pongo en valor 1 lo que esta valor 2  asi ya se vuelve a poner otra vez
                        f++;							//hasta el ultimpo pulpo, todos se mueven para abajo
                    }
                    sleep(VELOCIDAD_PULPO);     //velocidad de los peSes
                    if(nivel_var == 1){                     //vuelvo a arrancar desde el primer pulpo
                        f=0;
                    }
                    else if (nivel_var == 2){
                        f=3;
                    }
                    else{
                        f=9;
                    }
                }		
            }		
            if(nivel == 1){                     //vuelvo a arrancar desde el primer pulpo
                f=0;
            }
            else if (nivel == 2){
                f=3;
            }
            else{
                f=9;
            }
        }		
    }	
}

void clear_map(int arr[ALTURA][LARGO]){                    //funcion que recibe la amtriz nivel y la llena de ceros 
    int i , j ;
    for(i=0;i<ALTURA;i++){
        for(j=0;j<LARGO;j++){
            arr[i][j]=0;
        }
    }
}


