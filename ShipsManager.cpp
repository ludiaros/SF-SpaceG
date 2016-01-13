#include "ShipsManager.hpp"

ShipsManager::ShipsManager():
    ships(),
    playerShip(0),
    activeShips()
{
}

void ShipsManager::addShip() {
    ships.push_back(Ship());
}

void ShipsManager::draw(WindowManager& window) {

    for (std::size_t i=0; i<ships.size(); ++i) {

        if (ships[i].drawable) window.draw(ships[i]);
    }
}

void ShipsManager::update(WorldManager& world, WindowManager& window) {

    float delta = window.frameTime / (1000.f / 60.f);

    //if (window.eventMap[window.bindings["speedInc"]]) {
    if (window.eventMap["VK_UP"]) {
        ships[playerShip].accelUp(delta);
    }

    //if (window.eventMap[window.bindings["speedDec"]]) {
    if (window.eventMap["VK_DOWN"]) {
        ships[playerShip].accelDn(delta);
    }

    //if (window.eventMap[window.bindings["turnLeft"]]) {
    if (window.eventMap["VK_LEFT"]) {
        ships[playerShip].turn(delta, -1);
    }

    //if (window.eventMap[window.bindings["turnRight"]]) {
    if (window.eventMap["VK_RIGHT"]) {
        ships[playerShip].turn(delta, 1);
    }

    for (std::size_t i=0; i<ships.size(); ++i) {

        ships[i].update(world, delta);

        for (std::size_t j=0; j<world.activeAsteroids; ++j) {

            if (world.listAsteroids[j].drawable && world.listAsteroids[j].alive) {

                int x = ships[i].getX() - world.listAsteroids[j].getX();
                x = (x>0 ? x : -x);

                int y = ships[i].getY() - world.listAsteroids[j].getY();
                y = (y>0 ? y : -y);

                if (x + y < 1024) {//Distancia Manhattan
                    if (Collision::PixelPerfectTest(ships[i], world.listAsteroids[j], 128)) {

                        world.notifyImpact(j, ships[i].getCrashDmg());

                        ships[i].takeDamage(delta, world.listAsteroids[j].crashdmg);
                    }
                }
            }
        }

        for (unsigned int j=0; j<world.listCheckpoints.size(); ++j) {

            if (
                world.listCheckpoints[j].drawable &&
                world.listCheckpoints[j].alive &&
                !world.listCheckpoints[j].visited
            ) {

                int x = ships[i].getX() - world.listCheckpoints[j].getX();
                x = (x>0 ? x : -x);

                int y = ships[i].getY() - world.listCheckpoints[j].getY();
                y = (y>0 ? y : -y);

                if (x + y < 256) {//Distancia Manhattan
                    world.notifyLanding(j, 0);//type 0 si es desde una nave
                }
            }
        }
    }

    //Mantiene un registro de la posicion del jugador para otras clases que lo requieran
    //(Priciplamente el bucle principal del programa y GunsManager)
    window.gameInfo.playerSpeed = ships[playerShip].getSpeed();
    window.gameInfo.playerDamage = ships[playerShip].getDamage();
    window.gameInfo.playerShields = ships[playerShip].getShields();
    window.gameInfo.playerTime = ships[playerShip].getTime();
    window.gameInfo.playerPosX = ships[playerShip].getX();
    window.gameInfo.playerPosY = ships[playerShip].getY();
    window.gameInfo.playerAngle = ships[playerShip].getVAngle();
}

void ShipsManager::reset(WindowManager& window) {

    ships.clear();
    for (std::size_t i=0; i<window.gameInfo.maxShips; ++i) { addShip(); }
}

float ShipsManager::getPlayerSpeed() {

    return ships[playerShip].getSpeed();
}

float ShipsManager::getPlayerVAngle() {

    return ships[playerShip].getVAngle();
}

float ShipsManager::getPlayerDamage() {

    return ships[playerShip].getDamage();
}

float ShipsManager::getPlayerShields() {

    return ships[playerShip].getShields();
}

float ShipsManager::getPlayerTime() {

    return ships[playerShip].getTime();
}

bool ShipsManager::playerDead() {

    if (ships[playerShip].getDamage() == ships[playerShip].getDamageMax()) {
        return true;
    }
    return false;
}
