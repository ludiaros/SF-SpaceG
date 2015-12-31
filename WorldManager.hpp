#ifndef WORLDMANAGER_HPP
#define WORLDMANAGER_HPP

#include <vector>

#include "Config.hpp"
#include "Star.hpp"
#include "Structure.hpp"
#include "Asteroid.hpp"

using namespace sf;
using namespace std;

class WorldManager {

    public:
        //Constructors
        WorldManager(unsigned int max_asteroids);
        //Methods
        void                reset           ();
        void                addStar         ();
        void                addStructure    ();
        void                addAsteroid     ();
        void                draw            (RenderWindow& window);
        void                update          (View view);
        void                notifyCollision (Asteroid& astrd);
        void                notifyImpact    (int i, float damage);
        void                notifyLanding   (int i, int type);
        //Fields
        vector<Star>        starfield;
        vector<Structure>   checkpnt;
        vector<Asteroid>    asteroids;
        int                 playerposx;
        int                 playerposy;
        int                 playerposangle;
        unsigned int        n_asteroids;    //Cantidad de asteroides
        unsigned int        a_asteroids;    //Asteroids activos (los asteroides inactivos no se
                                            //borran solo se deshabilita la interaccion con ellos)

    private:
        //Constructors
        //Methods
        //Fields
};

#endif
