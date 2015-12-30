#ifndef ASTEROID_HPP
#define ASTEROID_HPP

#include <cmath>

#include "Config.hpp"

using namespace sf;
using namespace std;

class Asteroid : public Sprite {

    public:
        //Constructors
        Asteroid();
        Asteroid(Texture& texture);
        //Methods
        void                update  (View view);
        int                 getX    ()              { return (int) getPosition().x; };
        int                 getY    ()              { return (int) getPosition().y; };
        //Parameters
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
        //Parameters
        static const double PI;
};

#endif
