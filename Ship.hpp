#ifndef SHIP_HPP
#define SHIP_HPP

#include <cmath>

#include "Config.hpp"
#include "TextureManager.hpp"
#include "WorldManager.hpp"

using namespace sf;
using namespace std;

class Ship : public Sprite {

    public:
        //Constructors
        Ship();
        //Methods
        void        setControl  (bool ctrl);
        void        takeDamage  (float damage);
        void        turn        (int dir, bool maxi);
        void        update      (WorldManager& world);
        void        accelUp     ();
        void        accelDn     ();
        void        accelIn     ();
        //void        reset       ();
        int         getX        ()                      { return (int) getPosition().x; };
        int         getY        ()                      { return (int) getPosition().y; };
        float       getDamage   ()                      { return (int) (dmgact*10) / 10.f; };
        float       getVAngle   ()                      { return (int) vangle; };
        float       getSpeed    ()                      { return (int) (vact*10) / 10.f; };
        float       getShields  ()                      { return (int) (shieldmax*10) / 10.f; };
        float       getCrashDmg ()                      { return crashdmg; };
        float       getDamageMax()                      { return dmgmax; };
        float       getTime     ();
        //FIelds
        bool        drawable;
        bool        alive;

    private:
        //Constructors
        //Methods
        //Fields
        Clock       t_crono;
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

        static const double PI;
};

#endif
