#ifndef SHIPSMANAGER_HPP
#define SHIPSMANAGER_HPP

#include <SFML/Graphics.hpp>

#include <vector>
#include <iostream>

#include "globals.hpp"
#include "WindowManager.hpp"
#include "Ship.hpp"
#include "Collision.h"

class ShipsManager {

    public:
        //Constructors
        ShipsManager();
        //Methods
        void                reset               (WindowManager& window);
        void                addShip             ();
        bool                playerDead          ();
        float               getPlayerSpeed      ();
        float               getPlayerVAngle     ();
        float               getPlayerDamage     ();
        float               getPlayerShields    ();
        float               getPlayerTime       ();
        void                draw                (WindowManager& window);
        void                update              (WorldManager& world, WindowManager& window);
        //Fields
        std::vector<Ship>   ships;
        unsigned int        playerShip;
        unsigned int        activeShips; //Naves activas

    private:
        //Constructors
        //Methods
        //Fields
};

#endif
