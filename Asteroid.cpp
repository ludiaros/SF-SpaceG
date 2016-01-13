#include "Asteroid.hpp"

Asteroid::Asteroid():
    drawable(true),
    alive(true),
    visited(false),
    dx(0),
    dy(0),
    dmgact(0)
{
    int index = static_cast<int>(rand() % 9);
    std::ostringstream convert;
    convert << index << std::flush;
    std::string name = "rock" + convert.str();

    setTexture(*ResourceManager::getTexture(name));

    setOrigin(getLocalBounds().width/2, getLocalBounds().height/2);

    setPosition(rand()%MAP_W, rand()%MAP_H);

    zindex = rand()%8;

    float scale = 1 + (rand() % 5);

    setScale(scale, scale);

    vact = (rand() % 15) / 2; //Entre 0 y 10
    rangle = rand() % 360;
    tangle = rand() % 360;
    rturn = 0.250 + (rand() % 100) / 100.0;
    tturn = 0.005 + (rand() % 100) / 100.0;
    crashdmg = scale;//Si la escala va de 1 a 5 el daño causado va de 1 a 5
    dmgmax = scale * 100;//Si la escala va de 1 a 5 el daño maximo a recibir va de 100 a 1000
}

void Asteroid::update(sf::View view, float delta) {

    if (alive) { setColor(sf::Color(255 - zindex, 255 - zindex, 255 - zindex, 255)); }
    else { setColor(sf::Color(255, 0, 0, 128)); }

    if (visited) { setColor(sf::Color(255, 128, 128, 255)); }

    drawable = true;

    dx = -(vact * delta) * cos((90 + tangle) * PI / 180);
    dy = -(vact * delta) * sin((90 + tangle) * PI / 180);

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

        dx = -(vact * delta) * cos((90 + tangle) * PI / 180);
        dy = -(vact * delta) * sin((90 + tangle) * PI / 180);
    }

    rangle += (rturn * delta);
    tangle += (tturn * delta);

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
