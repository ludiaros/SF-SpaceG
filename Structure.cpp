#include "Structure.hpp"

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
    setFillColor(sf::Color(0, 0, 0, 0));
    setOutlineThickness(128);
}

void Structure::update(sf::View view, float delta) {

    if (alive) { setOutlineColor(sf::Color(128, 255, 128, 255)); }
    else { setOutlineColor(sf::Color(255, 0, 0, 128)); }

    if (visited) { setOutlineColor(sf::Color(128, 64, 64, 255)); }

    drawable = true;
    setRotation(getRotation() + delta);

    if (
        getPosition().x < view.getCenter().x - view.getSize().x ||
        getPosition().x > view.getCenter().x + view.getSize().x ||
        getPosition().y < view.getCenter().y - view.getSize().y ||
        getPosition().y > view.getCenter().y + view.getSize().y
    ) {
        drawable = false;
    }
}
