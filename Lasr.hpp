#ifndef LASR_HPP
#define LASR_HPP

#include <cmath>

#include "globals.hpp"
#include "ResourceManager.hpp"
#include "WorldManager.hpp"

class Lasr : public sf::Sprite {

    public:
        //Constructors
        Lasr();
        //Methods
        void                update      (float delta);
        void                setAngle    (int a) { angle = a; }
        //Fields
        bool                drawable;
        bool                alive;
        int                 maxTimeActive;
        float               dx;
        float               dy;
        float               vact;
        float               damage;
        float               angle;
        sf::Clock           timeActive;

    private:
        //Constructors
        //Methods
        //Fields
};

#endif
