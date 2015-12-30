#include "ShipsManager.hpp"

ShipsManager::ShipsManager(unsigned int max_ships):
    ships(),
    n_ships(max_ships),
    a_ships(max_ships)
{
}

void ShipsManager::addShip(Texture& texture) {
    ships.push_back(Ship(texture));
}

void ShipsManager::draw(RenderWindow& window) {

    for (unsigned int i=0; i<ships.size(); ++i) {

        if (ships[i].drawable) window.draw(ships[i]);
    }
}

void ShipsManager::update(WorldManager& world) {

    for (unsigned int i=0; i<ships.size(); ++i) {

        ships[i].update(world);

        for (unsigned int j=0; j<world.a_asteroids/*asteroids.size()*/; ++j) {

            if (world.asteroids[j].drawable && world.asteroids[j].alive) {

                int x = ships[i].getX() - world.asteroids[j].getX();
                x = (x>0 ? x : -x);

                int y = ships[i].getY() - world.asteroids[j].getY();
                y = (y>0 ? y : -y);

                if (x + y < 1024) {//Distancia Manhattan
                    if (Collision::PixelPerfectTest(ships[i], world.asteroids[j], 128)) {

                        world.notifyImpact(j, ships[i].crashdmg);

                        ships[i].takeDamage(world.asteroids[j].crashdmg);
                    }
                }
            }
        }

        for (unsigned int j=0; j<world.structures.size(); ++j) {

            if (
                world.structures[j].drawable &&
                world.structures[j].alive &&
                !world.structures[j].visited
            ) {

                int x = ships[i].getX() - world.structures[j].getX();
                x = (x>0 ? x : -x);

                int y = ships[i].getY() - world.structures[j].getY();
                y = (y>0 ? y : -y);

                if (x + y < 256) {//Distancia Manhattan
                    world.notifyLanding(j, 0);//type 0 si es desde una nave
                    ships[i].markCheckP();
                }
            }
        }
    }
}

void ShipsManager::reset() {
    ships.clear();
}
