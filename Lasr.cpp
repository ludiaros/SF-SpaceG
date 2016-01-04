#include "Lasr.hpp"

const double Lasr::PI = 4.0*atan(1);

Lasr::Lasr():
    drawable(true),
    alive(true),
    frames(0),
    t_active(250),
    dx(),
    dy(),
    vact(10),
    damage(100),
    angle(0)
{
    setTexture(*TextureManager::getTexture(0));

    setTextureRect(IntRect(0, 0, 15, 75));

    setOrigin(getLocalBounds().width/2, getLocalBounds().height/2);
}

void Lasr::update() {

    if (frames < t_active) {

        setScale(getScale().x, 1.0 - (frames / t_active));

        dx = -vact * cos((90 + angle) * PI / 180);
        dy = -vact * sin((90 + angle) * PI / 180);

        if (vact > 0) {
            move(dx, dy);
            setRotation(angle);
        }
        frames++;
    }
    else {
        frames = 0;
        drawable = false;
        alive = false;
    }
}
