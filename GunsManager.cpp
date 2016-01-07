#include "GunsManager.hpp"

GunsManager::GunsManager(unsigned int max_shoots):
    shoots(),
    last_shoot(),
    t_delay(100),
    a_shoots(max_shoots)
{
}

void GunsManager::draw(RenderWindow& window) {
    for (unsigned int i=0; i<shoots.size(); ++i) {
        if (shoots[i].drawable) {
            window.draw(shoots[i]);
        }
    }
}

void GunsManager::update(WorldManager& world, EventList& events) {

    if (events.shoot) {

        if (a_shoots > 0 && last_shoot.getElapsedTime().asMilliseconds() > t_delay) {

            Lasr sht = Lasr();
            sht.setPosition(world.playerposx, world.playerposy);
            sht.setAngle(world.playerposangle);
            shoots.push_back(sht);
            last_shoot.restart();
            a_shoots--;
        }
        events.shoot = false;
    }

    for (unsigned int i=0; i<shoots.size(); ++i) {

        shoots[i].update();

        for (unsigned int j=0; j<world.active_asteroids; ++j) {

            if (shoots[i].drawable && world.list_asteroids[j].alive && world.list_asteroids[j].drawable) {

                if (Collision::BoundingBoxTest(shoots[i], world.list_asteroids[j])) {

                    if (Collision::PixelPerfectTest(shoots[i], world.list_asteroids[j], 128)) {

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
