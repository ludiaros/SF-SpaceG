#include "Lasr.hpp"

Lasr::Lasr():
    drawable(true),
    alive(true),
    maxTimeActive(1000),
    dx(),
    dy(),
    vact(25.0),
    damage(100),
    angle(0),
    timeActive()
{
    setTexture(*ResourceManager::getTexture("ammo"));

    setTextureRect(sf::IntRect(0, 0, 15, 75));

    setOrigin(getLocalBounds().width/2, getLocalBounds().height/2);

    timeActive.restart();
}

void Lasr::update(float delta) {

    if (timeActive.getElapsedTime().asMilliseconds() < maxTimeActive) {

        setScale(getScale().x, 1.0 - (timeActive.getElapsedTime().asMilliseconds() / maxTimeActive));

        dx = -(vact * delta) * cos((90 + angle) * PI / 180);
        dy = -(vact * delta) * sin((90 + angle) * PI / 180);

        if (vact > 0) {
            move(dx, dy);
            setRotation(angle);
        }
    }
    else {
        drawable = false;
        alive = false;
    }
}
