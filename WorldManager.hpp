#ifndef WORLDMANAGER_HPP
#define WORLDMANAGER_HPP

#include <vector>

#include "globals.hpp"
#include "WindowManager.hpp"
#include "Star.hpp"
#include "Structure.hpp"
#include "Asteroid.hpp"

class WorldManager {

    public:
        //Constructors
        WorldManager();
        //Methods
        void                    addAsteroid         ();
        void                    addCheckPoint       ();
        void                    addStar             ();
        void                    draw                (WindowManager& window);
        void                    notifyImpact        (int i, float damage);
        void                    notifyLanding       (int i, int type);
        void                    reset               (WindowManager& window);
        void                    update              (WindowManager& window);
        //Fields
        unsigned int            activeAsteroids;    //Asteroids activos (los asteroides inactivos no se
                                                    //borran solo se deshabilita la interaccion con ellos)
        unsigned int            activeCheckpoints;  //Checkpoints que aun no se han visitado
        std::vector<Asteroid>   listAsteroids;
        std::vector<Structure>  listCheckpoints;
        std::vector<Star>       starfield;

    private:
        //Constructors
        //Methods
        //Fields
};

#endif
