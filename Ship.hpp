#ifndef SHIP_HPP
#define SHIP_HPP

#include <cmath>

#include "globals.hpp"
#include "ResourceManager.hpp"
#include "WorldManager.hpp"

class Ship : public sf::Sprite {

    public:
        //Constructors
        Ship();
        //Methods
        void        accelDn     (float delta);
        void        accelIn     (float delta);
        void        accelUp     (float delta);
        void        setControl  (bool ctrl);
        void        setSpeed    (float speed)           { vact = speed; };
        void        takeDamage  (float delta, float damage);
        void        turn        (float delta, int dir);
        void        update      (WorldManager& world, float delta);
        int         getTime     ();
        float       getCrashDmg ()                      { return crashdmg; };
        float       getDamage   ()                      { return (dmgact * 10) / 10.f; };
        float       getDamageMax()                      { return dmgmax; };
        float       getShields  ()                      { return (shieldmax * 10) / 10.f; };
        float       getSpeed    ()                      { return (vact * 10) / 10.f; };
        float       getVAngle   ()                      { return vangle; };
        float       getX        ()                      { return getPosition().x; };
        float       getY        ()                      { return getPosition().y; };
        //Fields
        bool        drawable;
        bool        alive;

    private:
        //Constructors
        //Methods
        //Fields
        bool        control;
        bool        start;
        int         time;                   // Tiempo empleado en completar el recorrido
        float       dx;                     // Delta de desplazamiento en el eje x
        float       dy;                     // Delta de desplazamiento en el eje y
        float       vact;                   // Velocidad actual
        float       vmin;                   // Velocidad minima
        float       vmax;                   // Velocidad maxima con la aceleracion normal
        float       vjmp;                   // Velocidad de salto
        float       accelup;                // Tasa de aceleracion
        float       acceldn;                // Tasa de desaceleracion
        float       accelin;                // Desaceleracion por friccion?
        float       mangle;                 // Angulo de movimiento
        float       vangle;                 // Angulo de posicion (hacia donde apunta la nave)
        float       turnf;                  // Tasa de giro maximo (full)
        float       turns;                  // Giro leve (small)
        float       dmgact;                 // Daño recibido
        float       dmgmax;                 // Daño maximo a recibir
        float       crashdmg;               // Daño que puede causar a otro objeto al chocar
        float       shieldmax;              // Escudos
        float       shieldreg;              // Escudos regeneracion
        sf::Clock   t_crono;
};

#endif
