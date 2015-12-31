#include "ShipsManager.hpp"

ShipsManager::ShipsManager(unsigned int max_ships):
    ships(),
    player_ship(0),
    n_ships(max_ships),
    a_ships(max_ships)
{
}

void ShipsManager::addShip() {
    ships.push_back(Ship());
}

void ShipsManager::draw(RenderWindow& window) {

    for (unsigned int i=0; i<ships.size(); ++i) {

        if (ships[i].drawable) window.draw(ships[i]);
    }
}

void ShipsManager::update(WorldManager& world, EventList& events) {

    if (events.jump) {
        ships[player_ship].jump();
        events.jump = false;
    }
    if (events.accelUp) {
        ships[player_ship].accelUp();
        events.accelUp = false;
    }
    if (events.accelDn) {
        ships[player_ship].accelDn();
        events.accelDn = false;
    }
    if (events.smallTurnLeft) {
        ships[player_ship].turn(-1, false);
        events.smallTurnLeft = false;
    }
    if (events.turnLeft) {
        ships[player_ship].turn(-1, true);
        events.turnLeft = false;
    }
    if (events.smallTurnRight) {
        ships[player_ship].turn(1, false);
        events.smallTurnRight = false;
    }
    if (events.turnRight) {
        ships[player_ship].turn(1, true);
        events.turnRight = false;
    }

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

        for (unsigned int j=0; j<world.checkpnt.size(); ++j) {

            if (
                world.checkpnt[j].drawable &&
                world.checkpnt[j].alive &&
                !world.checkpnt[j].visited
            ) {

                int x = ships[i].getX() - world.checkpnt[j].getX();
                x = (x>0 ? x : -x);

                int y = ships[i].getY() - world.checkpnt[j].getY();
                y = (y>0 ? y : -y);

                if (x + y < 256) {//Distancia Manhattan
                    world.notifyLanding(j, 0);//type 0 si es desde una nave
                    ships[i].markCheckP();
                }
            }
        }
    }

    world.playerposx = ships[0].getX();
    world.playerposy = ships[0].getY();
    world.playerposangle = ships[0].getVAngle();
}

void ShipsManager::reset() {
    ships.clear();
}
