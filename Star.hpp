#ifndef STAR_HPP
#define STAR_HPP

#include <cmath>

#include "Config.hpp"

using namespace sf;
using namespace std;

class Star : public CircleShape {

    public:
        //Constructors
        Star();
        //Methods
        void                update  (View view);
        //Parameters
        bool                drawable;
        bool                alive;
        int                 zindex;
        int                 anim0;//Variable para animar el parpadeo de la estrella
        int                 anim1;//Variable para animar el parpadeo de la estrella

    private:
        //Parameters
        static const double PI;
};

#endif
