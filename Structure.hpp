#ifndef STRUCTURE_HPP
#define STRUCTURE_HPP

#include <cmath>

#include "Config.hpp"

using namespace sf;
using namespace std;

class Structure : public CircleShape {

    public:
        //Constructors
        Structure();
        //Methods
        void                update      (View view);
        int                 getX        ()                      { return (int) getPosition().x; };
        int                 getY        ()                      { return (int) getPosition().y; };
        //Fields
        bool                drawable;
        bool                alive;
        bool                visited;
        float               damage;                 // Daño recibido?

    private:
        //Constructors
        //Methods
        //Fields
        static const double PI;
};

#endif
