#include "GunsManager.hpp"

GunsManager::GunsManager(unsigned int max_shoots):
    shoots(),
    last_shoot(),
    t_delay(100),
    a_shoots(max_shoots)
{
}

void GunsManager::addShoot(Texture& texture, Sprite& player) {
    if (a_shoots > 0 && last_shoot.getElapsedTime().asMilliseconds() > t_delay) {
        shoots.push_back(Lasr(texture, player));
        last_shoot.restart();
        a_shoots--;
    }
}

void GunsManager::draw(RenderWindow& window) {
    for (unsigned int i=0; i<shoots.size(); ++i) {
        if (shoots[i].drawable) {
            window.draw(shoots[i]);
        }
    }
}

void GunsManager::update(WorldManager& world) {

    for (unsigned int i=0; i<shoots.size(); ++i) {

        shoots[i].update();

        for (unsigned int j=0; j<world.a_asteroids/*asteroids.size()*/; ++j) {

            if (shoots[i].drawable && world.asteroids[j].alive && world.asteroids[j].drawable) {

                if (Collision::BoundingBoxTest(shoots[i], world.asteroids[j])) {

                    if (Collision::PixelPerfectTest(shoots[i], world.asteroids[j], 128)) {

                        world.notifyImpact(j, shoots[i].damage);

                        shoots[i].alive = false;
                    }
                }
            }
        }

        if (!shoots[i].alive) {
            shoots.erase(shoots.begin()+i);
        }
    }
}
