#include "WorldManager.hpp"

WorldManager::WorldManager(unsigned int max_asteroids):
    starfield(),
    list_checkpoints(),
    list_asteroids(),
    playerposx(0),
    playerposy(0),
    playerposangle(0),
    active_asteroids(max_asteroids)
{
}

void WorldManager::addStar() {
    starfield.push_back(Star());
}

void WorldManager::addCheckPoint() {
    list_checkpoints.push_back(Structure());
}

void WorldManager::addAsteroid() {
    list_asteroids.push_back(Asteroid());
}

void WorldManager::draw(RenderWindow& window) {

    for (unsigned int i=0; i<starfield.size(); ++i) {
        if (starfield[i].drawable) {
            window.draw(starfield[i]);
        }
    }

    for (unsigned int i=0; i<list_checkpoints.size(); ++i) {
        if (list_checkpoints[i].drawable) {
            window.draw(list_checkpoints[i]);
        }
    }

    for (unsigned int i=0; i<list_asteroids.size(); ++i) {
        if (list_asteroids[i].drawable) {
            window.draw(list_asteroids[i]);
        }
    }
}

void WorldManager::update(View view) {

    for (unsigned int i=0; i<starfield.size(); ++i) {
        if (starfield[i].alive) {
            starfield[i].update(view);
        }
    }

    for (unsigned int i=0; i<list_checkpoints.size(); ++i) {
        if (list_checkpoints[i].alive) {
            list_checkpoints[i].update(view);
        }
    }

    for (unsigned int i=0; i<list_asteroids.size(); ++i) {
        if (list_asteroids[i].alive) {
            list_asteroids[i].update(view);
        }
    }
}

void WorldManager::notifyImpact(int i, float damage) {

    list_asteroids[i].setColor(Color(255, 128, 128, 128));//Colorea de amarillo y con transparencia del 50%

    if (list_asteroids[i].dmgact < list_asteroids[i].dmgmax) {
        list_asteroids[i].dmgact += damage;
    }
    else {
        list_asteroids[i].alive = false;                //Marca el objeto como inactivo (evita que
                                                        //se mueva)

        list_asteroids.push_back(list_asteroids[i]);    //Envia el asteroide al final de la lista, con esto y
                                                        //la variable a_asteroids se deshabilita la deteccion
                                                        //de colisiones
        list_asteroids.erase(list_asteroids.begin()+i); //Borra el asteroide de la lista (en realidad debido a
                                                        //la instruccion anterior queda una copia al final de
                                                        //la lista)

        active_asteroids--;
    }
}

void WorldManager::notifyLanding(int i, int type) {

    if (type == 0) {//Impacto desde una nave
        list_checkpoints[i].visited = true;
        active_checkpoints--;
    }

    if (type == 1) {//Impacto desde un asteroide
        //deberia dañar la estacion (falta implementarlo)
    }
}

void WorldManager::reset() {

    starfield.clear();
    list_checkpoints.clear();
    list_asteroids.clear();

    for (unsigned int i=0; i<MAX_STARS; ++i) { addStar(); }
    for (unsigned int i=0; i<CHECKPNTS; ++i) { addCheckPoint(); }
    for (unsigned int i=0; i<MAX_ASTER; ++i) { addAsteroid(); }

    active_asteroids   = MAX_ASTER;
    active_checkpoints = CHECKPNTS;
}
