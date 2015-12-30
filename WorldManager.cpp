#include "WorldManager.hpp"

WorldManager::WorldManager(unsigned int max_asteroids):
    starfield(),
    structures(),
    asteroids(),
    n_asteroids(max_asteroids),
    a_asteroids(max_asteroids)
{
}

void WorldManager::addStar() {
    starfield.push_back(Star());
}

void WorldManager::addStructure() {
    structures.push_back(Structure());
}

void WorldManager::addAsteroid(Texture& texture) {
    asteroids.push_back(Asteroid(texture));
}

void WorldManager::draw(RenderWindow& window) {

    for (unsigned int i=0; i<starfield.size(); ++i) {
        if (starfield[i].drawable) {
            window.draw(starfield[i]);
        }
    }

    for (unsigned int i=0; i<structures.size(); ++i) {
        if (structures[i].drawable) {
            window.draw(structures[i]);
        }
    }

    for (unsigned int i=0; i<asteroids.size(); ++i) {
        if (asteroids[i].drawable) {
            window.draw(asteroids[i]);
        }
    }
}

void WorldManager::update(View view) {

    for (unsigned int i=0; i<starfield.size(); ++i) {
        if (starfield[i].alive) {
            starfield[i].update(view);
        }
    }

    for (unsigned int i=0; i<structures.size(); ++i) {
        if (structures[i].alive) {
            structures[i].update(view);
        }
    }

    for (unsigned int i=0; i<asteroids.size(); ++i) {
        if (asteroids[i].alive) {
            asteroids[i].update(view);
        }
    }
}

void WorldManager::notifyImpact(int i, float damage) {

    asteroids[i].setColor(Color(255, 128, 128, 128));//Colorea de amarillo y con transparencia del 50%

    if (asteroids[i].dmgact < asteroids[i].dmgmax) {
        asteroids[i].dmgact += damage;
    }
    else {
        asteroids[i].alive = false;           //Marca el objeto como inactivo (evita que
                                              //se mueva)

        asteroids.push_back(asteroids[i]);    //Envia el asteroide al final de la lista, con esto y
                                              //la variable a_asteroids se deshabilita la deteccion
                                              //de colisiones
        asteroids.erase(asteroids.begin()+i); //Borra el asteroide de la lista (en realidad debido a
                                              //la instruccion anterior queda una copia al final de
                                              //la lista)

        a_asteroids--;
    }
}

void WorldManager::notifyLanding(int i, int type) {

    if (type == 0) {//Impacto desde una nave
        structures[i].visited = true;
    }

    if (type == 1) {
        //Impacto desde un asteroide, debieria dañar la estacion (falta implementarlo)
    }
}

void WorldManager::reset() {

    starfield.clear();
    structures.clear();
    asteroids.clear();

    a_asteroids = n_asteroids;
}
