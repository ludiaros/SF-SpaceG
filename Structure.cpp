#include "Structure.hpp"

const double Structure::PI = 4.0*atan(1);

Structure::Structure():
    drawable(true),
    alive(true),
    visited(false),
    damage(0)
{
    setPointCount(8);
    setRadius(256);
    setOrigin(getLocalBounds().width/2, getLocalBounds().height/2);
    setPosition(rand()%MAP_W, rand()%MAP_H);
    setFillColor(Color(0, 0, 0, 0));
    setOutlineThickness(128);
}

void Structure::update(View view) {

    if (alive) { setOutlineColor(Color(128, 255, 128, 255)); }
    else { setOutlineColor(Color(255, 0, 0, 128)); }

    if (visited) { setOutlineColor(Color(128, 64, 64, 255)); }

    drawable = true;
    setRotation(getRotation()+1);

    if (
        getPosition().x < view.getCenter().x - view.getSize().x ||
        getPosition().x > view.getCenter().x + view.getSize().x ||
        getPosition().y < view.getCenter().y - view.getSize().y ||
        getPosition().y > view.getCenter().y + view.getSize().y
    ) {
        drawable = false;
    }
}
