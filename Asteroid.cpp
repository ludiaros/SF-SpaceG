#include "Asteroid.hpp"

const double Asteroid::PI = 4.0*atan(1);

Asteroid::Asteroid():
    drawable(true),
    alive(true),
    visited(false),
    dx(0),
    dy(0),
    dmgact(0)
{

    setTexture(*TextureManager::getTexture(2));

    setOrigin(getLocalBounds().width/2, getLocalBounds().height/2);

    setPosition(rand()%MAP_W, rand()%MAP_H);

    zindex = rand()%8;

    float scale = 10 + (rand() % 240);

    setScale(scale / 50, scale / 50);

    vact = (rand() % 10) / 2; //Entre 0 y 5
    rangle = rand() % 360;
    tangle = rand() % 360;
    rturn = (10 + (rand() % 15)) / 10;
    tturn = (5 + (rand() % 20)) / 10;
    crashdmg = scale / 25;//Si la escala va de 10 a 250 el daño causado va de 1 a 10
    dmgmax = scale * 4;//Si la escala va de 10 a 250 el daño maximo a recibir va de 50 a 1000
}

void Asteroid::update(View view) {

    if (alive) { setColor(Color(255 - zindex, 255 - zindex, 255 - zindex, 255)); }
    else { setColor(Color(255, 0, 0, 128)); }

    if (visited) { setColor(Color(255, 128, 128, 255)); }

    drawable = true;

    dx = -vact * cos((90 + tangle) * PI / 180);
    dy = -vact * sin((90 + tangle) * PI / 180);

    if (
        (getPosition().x + dx < 0) ||
        (getPosition().x + dx > MAP_W) ||
        (getPosition().y + dy < 0) ||
        (getPosition().y + dy > MAP_H)
    ) {
        if ((getPosition().x + dx < 0) || (getPosition().x + dx > MAP_W)) {
            tangle = -tangle;
        }
        if ((getPosition().y + dy < 0) || (getPosition().y + dy > MAP_H)) {
            tangle = 180-tangle;
        }

        dx = -vact * cos((90 + tangle) * (PI / 180));
        dy = -vact * sin((90 + tangle) * (PI / 180));
    }

    rangle += rturn;
    tangle += tturn;

    move(dx, dy);
    setRotation(rangle);

    if (
        getPosition().x < view.getCenter().x - view.getSize().x ||
        getPosition().x > view.getCenter().x + view.getSize().x ||
        getPosition().y < view.getCenter().y - view.getSize().y ||
        getPosition().y > view.getCenter().y + view.getSize().y
    ) {
        drawable = false;
    }
}
