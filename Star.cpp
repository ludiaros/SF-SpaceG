#include "Star.hpp"

const double Star::PI = 4.0*atan(1);

Star::Star():
    drawable(true),
    alive(true)
{
    anim0 = rand()%20 - 10; //Determina la velocidad a la que parpadea la estrella
    anim1 = rand()%255;     //Indica el "cuadro" inicial de la animacion para que no se vean
                            //"sincronizadas" las animaciones de todas las estrellas
    zindex = 1 + rand()%16;  //Varia el tamaño de la estrella

    setPointCount(8);
    setRadius(zindex);
    setOrigin(getLocalBounds().width/2, getLocalBounds().height/2);
    setPosition(rand()%MAP_W, rand()%MAP_H);
}

void Star::update(View view) {

    if (
        getPosition().x < view.getCenter().x - view.getSize().x ||
        getPosition().x > view.getCenter().x + view.getSize().x ||
        getPosition().y < view.getCenter().y - view.getSize().y ||
        getPosition().y > view.getCenter().y + view.getSize().y
    ) {
        drawable = false;
    }
    else {

        if (anim1 < 25 || anim1 > 250) { anim0 = -anim0; }
        anim1 += anim0;

        if (alive) { setFillColor(Color(255, 255, 255, anim1)); }

        drawable = true;
    }
}
