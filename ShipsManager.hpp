#ifndef SHIPSMANAGER_HPP
#define SHIPSMANAGER_HPP

#include <vector>

#include "Config.hpp"
#include "Ship.hpp"
#include "Collision.h"

using namespace sf;
using namespace std;

class ShipsManager {

    public:
        //Constructors
        ShipsManager(unsigned int max_ships);
        //Methods
        void            reset               ();
        void            addShip             ();
        bool            playerDead          ();
        float           getPlayerSpeed      ();
        float           getPlayerVAngle     ();
        float           getPlayerDamage     ();
        float           getPlayerShields    ();
        float           getPlayerTime       ();
        void            draw                (RenderWindow& window);
        void            update              (WorldManager& world, EventList& events);
        //Fields
        vector<Ship>    ships;
        unsigned int    player_ship;
        unsigned int    n_ships; //Numero de naves
        unsigned int    active_ships; //Naves activas

    private:
        //Constructors
        //Methods
        //Fields
};

#endif
