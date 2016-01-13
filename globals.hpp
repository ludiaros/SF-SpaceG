#ifndef GLOBALS_HPP
#define GLOBALS_HPP

#define PI 3.14159265358979323846f

#define FPS     30

#define SCR_W   1350    //Ancho de la ventana
#define SCR_H   700     //Altura de la ventana

#define MAP_W   32000   //Ancho del mapa
#define MAP_H   32000   //Altura del mapa

enum GameScreenStates {LOAD, CONFIG, PLAY, PAUSED, RESET, OVER, WIN, CREDITS, EXIT};

enum Align {TOPLEFT, TOPCENTER, TOPRIGHT, MIDLEFT, MIDCENTER, MIDRIGHT, BOTTOMLEFT, BOTTOMCENTER, BOTTOMRIGHT};

struct GameData {//Refleja el estado de algunas variables del juego para ponerlas en pantalla
    unsigned int    maxCheckpoints;
    unsigned int    maxAsteroids;
    unsigned int    maxStars;
    unsigned int    maxShoots;
    unsigned int    maxShips;
    unsigned int    worldCheckpoints;
    unsigned int    worldAsteroids;
    unsigned int    gunShoots;
    float           playerSpeed;
    float           playerPosX;
    float           playerPosY;
    float           nextCheckpointX;
    float           nextCheckpointY;
    float           playerAngle;
    float           playerDamage;
    float           playerShields;
    float           playerTime;
};

#endif
