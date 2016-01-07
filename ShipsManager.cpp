#include "ShipsManager.hpp"

ShipsManager::ShipsManager(unsigned int max_ships):
    ships(),
    player_ship(0),
    n_ships(max_ships),
    active_ships(max_ships)
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

        for (unsigned int j=0; j<world.active_asteroids; ++j) {

            if (world.list_asteroids[j].drawable && world.list_asteroids[j].alive) {

                int x = ships[i].getX() - world.list_asteroids[j].getX();
                x = (x>0 ? x : -x);

                int y = ships[i].getY() - world.list_asteroids[j].getY();
                y = (y>0 ? y : -y);

                if (x + y < 1024) {//Distancia Manhattan
                    if (Collision::PixelPerfectTest(ships[i], world.list_asteroids[j], 128)) {

                        world.notifyImpact(j, ships[i].getCrashDmg());

                        ships[i].takeDamage(world.list_asteroids[j].crashdmg);
                    }
                }
            }
        }

        for (unsigned int j=0; j<world.list_checkpoints.size(); ++j) {

            if (
                world.list_checkpoints[j].drawable &&
                world.list_checkpoints[j].alive &&
                !world.list_checkpoints[j].visited
            ) {

                int x = ships[i].getX() - world.list_checkpoints[j].getX();
                x = (x>0 ? x : -x);

                int y = ships[i].getY() - world.list_checkpoints[j].getY();
                y = (y>0 ? y : -y);

                if (x + y < 256) {//Distancia Manhattan
                    world.notifyLanding(j, 0);//type 0 si es desde una nave
                }
            }
        }
    }

    //Mantiene un registro de la posicion del jugador para otras clases que lo requieran
    //(Priciplamente el bucle principal del programa y GunsManager)
    world.playerposx = ships[player_ship].getX();
    world.playerposy = ships[player_ship].getY();
    world.playerposangle = ships[player_ship].getVAngle();
}

void ShipsManager::reset() {

    ships.clear();
    for (unsigned int i=0; i<MAX_SHIPS; ++i) { addShip(); }
}

float ShipsManager::getPlayerSpeed() {

    return ships[player_ship].getSpeed();
}

float ShipsManager::getPlayerVAngle() {

    return ships[player_ship].getVAngle();
}

float ShipsManager::getPlayerDamage() {

    return ships[player_ship].getDamage();
}

float ShipsManager::getPlayerShields() {

    return ships[player_ship].getShields();
}

float ShipsManager::getPlayerTime() {

    return ships[player_ship].getTime();
}

bool ShipsManager::playerDead() {

    if (ships[player_ship].getDamage() == ships[player_ship].getDamageMax()) {
        return true;
    }
    return false;
}
