#ifndef GUNSMANAGER_HPP
#define GUNSMANAGER_HPP

#include <vector>

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
        void            addShoot    (Texture& texture, Sprite& player);
        void            draw        (RenderWindow& window);
        void            update      (WorldManager& world);

        //Parameters
        vector<Lasr>    shoots;
        Clock           last_shoot;
        int             t_delay;
        int             a_shoots;
};

#endif
