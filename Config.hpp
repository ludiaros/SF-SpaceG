#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <stdio.h>
#include <SFML/Graphics.hpp>

#define MAX_STARS   10000   //Cantidad de estrellas
#define MAX_ASTER   2500    //Cantidad de asteroides
                            //PROBLEMA:Cuando se asigna 1550 o menos da error
                            //(se cuelga el programa, ?? porque exactamente ese numero?)
#define MAX_SHOOT   10000   //Cantidad de municion (ammo)
#define MAX_SHIPS   1       //Numero de naves, aun no implementado (Si se pone mas de una las
                            //siguientes quedan estaticas en la zona de partida)

#define CHECKPNTS   5       //Velocidad de movimiento del laser

#define SCR_W       1350    //Ancho de la ventana
#define SCR_H       700     //Altura de la ventana

#define MAP_W       32000   //Ancho del mapa
                            //PROBLEMA:No situa objetos por fuera del area de 32000 x 32000
                            //con un tamaño mayor sigue ubicando los objetos en esta area
                            //Problema con el tipo de dato puede ser?
#define MAP_H       32000   //Altura del mapa

#define RUNNING     0
#define PAUSED      1
#define RESET       2
#define OVER        3
#define WIN         4

#define TOPLEFT     0
#define TOPCENTER   1
#define TOPRIGHT    2
#define MIDLEFT     3
#define MIDCENTER   4
#define MIDRIGHT    5
#define BOTLEFT     6
#define BOTCENTER   7
#define BOTRIGHT    8

using namespace sf;

struct GameState {
    int             status; //Ver los valores en la linea 25 de Config.hpp
};

struct EventList {
    bool            accelUp;
    bool            accelDn;
    bool            turnLeft;
    bool            smallTurnLeft;
    bool            turnRight;
    bool            smallTurnRight;
    bool            shoot;
};

#endif
