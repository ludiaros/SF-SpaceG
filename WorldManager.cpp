#include "WorldManager.hpp"

WorldManager::WorldManager():
    starfield(),
    listCheckpoints(),
    listAsteroids(),
    activeAsteroids()
{
}

void WorldManager::addStar() {
    starfield.push_back(Star());
}

void WorldManager::addCheckPoint() {
    listCheckpoints.push_back(Structure());
}

void WorldManager::addAsteroid() {
    listAsteroids.push_back(Asteroid());
}

void WorldManager::draw(WindowManager& window) {

    for (std::size_t i=0; i<starfield.size(); ++i) {
        if (starfield[i].drawable) {
            window.draw(starfield[i]);
        }
    }

    for (std::size_t i=0; i<listCheckpoints.size(); ++i) {
        if (listCheckpoints[i].drawable) {
            window.draw(listCheckpoints[i]);
        }
    }

    for (std::size_t i=0; i<listAsteroids.size(); ++i) {
        if (listAsteroids[i].drawable) {
            window.draw(listAsteroids[i]);
        }
    }
}

void WorldManager::update(WindowManager& window) {

    float delta = window.frameTime / (1000.f / 60.f);

    for (std::size_t i=0; i<starfield.size(); ++i) {
        if (starfield[i].alive) {
            starfield[i].update(window.view, delta);
        }
    }

    for (std::size_t i=0; i<listCheckpoints.size(); ++i) {
        if (listCheckpoints[i].alive) {
            listCheckpoints[i].update(window.view, delta);
        }
    }

    for (std::size_t i=0; i<listAsteroids.size(); ++i) {
        if (listAsteroids[i].alive) {
            listAsteroids[i].update(window.view, delta);
        }
    }

    window.gameInfo.worldCheckpoints = activeCheckpoints;
    window.gameInfo.worldAsteroids = activeAsteroids;
}

void WorldManager::notifyImpact(int i, float damage) {

    listAsteroids[i].setColor(sf::Color(255, 128, 128, 128));//Colorea de amarillo y con transparencia del 50%

    if (listAsteroids[i].dmgact < listAsteroids[i].dmgmax) {
        listAsteroids[i].dmgact += damage;
    }
    else {
        listAsteroids[i].alive = false;                //Marca el objeto como inactivo (evita que
                                                        //se mueva)

        listAsteroids.push_back(listAsteroids[i]);    //Envia el asteroide al final de la lista, con esto y
                                                        //la variable a_asteroids se deshabilita la deteccion
                                                        //de colisiones
        listAsteroids.erase(listAsteroids.begin()+i); //Borra el asteroide de la lista (en realidad debido a
                                                        //la instruccion anterior queda una copia al final de
                                                        //la lista)

        activeAsteroids--;
    }
}

void WorldManager::notifyLanding(int i, int type) {

    if (type == 0) {//Impacto desde una nave
        listCheckpoints[i].visited = true;
        activeCheckpoints--;
    }

    if (type == 1) {//Impacto desde un asteroide
        //deberia dañar la estacion (falta implementarlo)
    }
}

void WorldManager::reset(WindowManager& window) {

    starfield.clear();
    listCheckpoints.clear();
    listAsteroids.clear();

    for (std::size_t i=0; i<window.gameInfo.maxStars; ++i) { addStar(); }
    for (std::size_t i=0; i<window.gameInfo.maxCheckpoints; ++i) { addCheckPoint(); }
    for (std::size_t i=0; i<window.gameInfo.maxAsteroids; ++i) { addAsteroid(); }

    activeAsteroids   = window.gameInfo.maxAsteroids;
    activeCheckpoints = window.gameInfo.maxCheckpoints;
}
