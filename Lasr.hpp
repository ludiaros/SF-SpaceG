#ifndef LASR_HPP
#define LASR_HPP

#include <cmath>

#include "Config.hpp"
#include "WorldManager.hpp"

using namespace sf;
using namespace std;

class Lasr : public Sprite {

    public:
        //Constructors
        Lasr();
        Lasr(Texture& texture, Sprite& player);
        //Methods
        void                update      ();
        //Parameters
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
        //Parameters
        static const double PI;
};

#endif
