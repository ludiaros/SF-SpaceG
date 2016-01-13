#ifndef ASTEROID_HPP
#define ASTEROID_HPP

#include <cmath>
#include <sstream>

#include "globals.hpp"
#include "ResourceManager.hpp"

class Asteroid : public sf::Sprite {

    public:
        //Constructors
        Asteroid();
        //Methods
        void                update  (sf::View view, float delta);
        float               getX    ()                  { return getPosition().x; };
        float               getY    ()                  { return getPosition().y; };
        //Fields
        bool                drawable;
        bool                alive;
        bool                visited;
        int                 zindex;
        float               dx;                     //Delta de desplazamiento en el eje x
        float               dy;                     //Delta de desplazamiento en el eje y
        float               vact;                   //Velocidad actual
        float               rangle;                 //Angulo de rotacion
        float               tangle;                 //Angulo de traslacion
        float               rturn;                  //Tasa de giro en el angulo de rotacion
        float               tturn;                  //Tasa de giro en el angulo de traslacion
        float               dmgact;                 //Daño recibido
        float               dmgmax;                 //Daño maximo a recibir
        float               crashdmg;               //Daño que puede causar a otro objeto al chocar

    private:
        //Fields
};

#endif
