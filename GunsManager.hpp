#ifndef GUNSMANAGER_HPP
#define GUNSMANAGER_HPP

#include <vector>
#include <iostream>

#include "Config.hpp"
#include "Lasr.hpp"
#include "Collision.h"

using namespace sf;
using namespace std;

class GunsManager {

    public:
        //Constructors
        GunsManager(unsigned int max_ammos);
        //Methods
        void            addShoot    (int originx, int originy, int angle/*Texture& texture, Sprite& player*/);
        void            draw        (RenderWindow& window);
        void            update      (WorldManager& world, EventList& events);
        //Fields
        vector<Lasr>    shoots;
        Clock           last_shoot;
        int             t_delay;
        int             a_shoots;

    private:
        //Constructors
        //Methods
        //Fields
};

#endif
