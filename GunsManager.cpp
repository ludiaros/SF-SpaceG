#include "GunsManager.hpp"

GunsManager::GunsManager():
    shoots(),
    lastShoot(),
    delayShoot(100),
    activeShoots()
{
}

void GunsManager::draw(WindowManager& window) {
    for (std::size_t i=0; i<shoots.size(); ++i) {
        if (shoots[i].drawable) {
            window.draw(shoots[i]);
        }
    }
}

void GunsManager::update(WorldManager& world, WindowManager& window) {

    float delta = window.frameTime / (1000.f / 60.f);

    //if (window.eventMap[window.bindings["shoot"]]) {
    if (window.eventMap["VK_SPACE"]) {

        if (activeShoots > 0 && lastShoot.getElapsedTime().asMilliseconds() > delayShoot) {

            Lasr sht = Lasr();
            sht.setPosition(window.gameInfo.playerPosX, window.gameInfo.playerPosY);
            sht.setAngle(window.gameInfo.playerAngle);
            shoots.push_back(sht);
            lastShoot.restart();
            activeShoots--;
        }
    }

    for (std::size_t i=0; i<shoots.size(); ++i) {

        shoots[i].update(delta);

        for (std::size_t j=0; j<world.activeAsteroids; ++j) {

            if (shoots[i].drawable && world.listAsteroids[j].alive && world.listAsteroids[j].drawable) {

                if (Collision::BoundingBoxTest(shoots[i], world.listAsteroids[j])) {

                    if (Collision::PixelPerfectTest(shoots[i], world.listAsteroids[j], 128)) {

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

    window.gameInfo.gunShoots = activeShoots;
}

void GunsManager::reset(WindowManager& window) {

    shoots.clear();
    activeShoots = window.gameInfo.maxShoots;
}
