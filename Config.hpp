#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

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

using namespace sf;

struct SystemData {
    RenderWindow    window;        //Ventana principal del juego (sf::RenderWindow)
    VideoMode       video;         //Modo de video (SFML sf::VideoMode)
    Texture         texture[100];  //Texturas disponibles para el juego
    String          fps;           //Cadena que contiene el texto de FPS
    String          info;          //Cadena que contiene el texto de informacion
    Font            font;          //Fuente a usar en los textos (SFML sf::Font)
    View            view;          //Vista principal (SFML sf::View)
    Text            text;          //Textos a mostrar en pantalla (SFML sf::Text)
    Clock           t_fps;         //Temporizador para lle var la cuenta de FPS (SFML sf::Clock)
    bool            rot_fixed;     //Cambiar el punto de referencia para la rotacion (nave / mapa)
    bool            no_info;       //Mostrar / ocultar informacion en pantalla
    bool            no_fps;        //Mostrar /Ocultar contador FPS
    bool            fullscr;       //Iniciar en pantalla completa o modo ventana
    bool            reset;         //Forzar el reinicio del bucle principal del juego
    bool            paused;        //Pausar el bucle principal del juego
    bool            over;          //Indica si se termino el juego
    bool            win;           //Indica si se gano el juego
    int             style;         //Indica si la ventana esta en pantalla completa
    int             destx;
    int             desty;
    float           zoom;
};

#endif
