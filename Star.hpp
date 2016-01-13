#ifndef STAR_HPP
#define STAR_HPP

#include <SFML/Graphics.hpp>

#include <cmath>

#include "globals.hpp"

class Star : public sf::CircleShape {

    public:
        //Constructors
        Star();
        //Methods
        void                update  (sf::View view, float delta);
        //Fields
        bool                drawable;
        bool                alive;
        int                 zindex;
        int                 anim0;//Variable para animar el parpadeo de la estrella
        int                 anim1;//Variable para animar el parpadeo de la estrella

    private:
        //Constructors
        //Methods
        //Fields
};

#endif
