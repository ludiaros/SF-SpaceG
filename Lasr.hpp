#ifndef LASR_HPP
#define LASR_HPP

#include <cmath>

#include "Config.hpp"
#include "TextureManager.hpp"
#include "WorldManager.hpp"

using namespace sf;
using namespace std;

class Lasr : public Sprite {

    public:
        //Constructors
        Lasr();
        //Methods
        void                update      ();
        void                setAngle    (int a) { angle = a; }
        //Fields
        bool                drawable;
        bool                alive;
        int                 frames;
        int                 t_active;
        float               dx;
        float               dy;
        float               vact;
        float               damage;
        float               angle;

    private:
        //Constructors
        //Methods
        //Fields
        static const double PI;
};

#endif
