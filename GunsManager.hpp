#ifndef GUNSMANAGER_HPP
#define GUNSMANAGER_HPP

#include <vector>

#include "globals.hpp"
#include "WindowManager.hpp"
#include "Lasr.hpp"
#include "Collision.h"

class GunsManager {

    public:
        //Constructors
        GunsManager();
        //Methods
        void                addShoot    (int originx, int originy, int angle);
        void                draw        (WindowManager& window);
        void                reset       (WindowManager& window);
        void                update      (WorldManager& world, WindowManager& window);
        //Fields
        int                 delayShoot;
        int                 activeShoots;
        std::vector<Lasr>   shoots;
        sf::Clock           lastShoot;

    private:
        //Constructors
        //Methods
        //Fields
};

#endif
