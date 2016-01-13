#ifndef STRUCTURE_HPP
#define STRUCTURE_HPP

#include <SFML/Graphics.hpp>

#include <cmath>

#include "globals.hpp"

class Structure : public sf::CircleShape {

    public:
        //Constructors
        Structure();
        //Methods
        void                update      (sf::View view, float delta);
        float               getX        ()                      { return getPosition().x; };
        float               getY        ()                      { return getPosition().y; };
        //Fields
        bool                drawable;
        bool                alive;
        bool                visited;
        float               damage;                 // Daño recibido?

    private:
        //Constructors
        //Methods
        //Fields
};

#endif
