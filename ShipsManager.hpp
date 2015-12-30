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
        void            reset   ();
        void            addShip (Texture& texture);
        void            draw    (RenderWindow& window);
        void            update  (WorldManager& world);

        //Parameters
        vector<Ship>    ships;
        unsigned int    n_ships; //Numero de naves
        unsigned int    a_ships; //Naves activas
};

#endif
