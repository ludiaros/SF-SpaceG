#include "GameScreenPlay.hpp"

GameScreenPlay::GameScreenPlay():
    world(),
    gunsm(),
    shipm()
{
    start = false;
}

void GameScreenPlay::run(WindowManager& window, unsigned int& status) {

    srand(time(NULL));

    //Verifica si hay que reiniciar el juego o continuar con la ultima instancia
    if (!start) {
        world.reset(window);//Reinicia el mundo (posiciona las estrellas y asteroides)
        gunsm.reset(window);
        shipm.reset(window);//Reincia las naves (reinicia el estado y la posicion de cada nave)
        start = true;
    }

    window.restartClock();

    //Actualiza la logica --------------------------------------------------------------------------
    world.update(window);
    gunsm.update(world, window);
    shipm.update(world, window);

    // Verifica si hay game over o win -------------------------------------------------------------
    if (shipm.playerDead()) {
        start = false;
        status = OVER;
    }

    if (world.activeCheckpoints == 0) {
        start = false;
        status = WIN;
    }

    // Renderiza los objetos actualizados ----------------------------------------------------------
    window.clear();
    window.resetView();
    window.view.setCenter(window.gameInfo.playerPosX, window.gameInfo.playerPosY);  //Hace que la camara siga a la nave
                                                                                    //controlada

    if (!window.rotationRef) { window.view.setRotation(0); }                        //Hace el angulo de la camara fijo
    else { window.view.setRotation(window.gameInfo.playerAngle); }                  //La camara rota siguiendo el
                                                                                    //angulo de la nave controlada

    world.draw(window);
    gunsm.draw(window);
    shipm.draw(window);

    window.drawLimits();

    window.setDefaultView();

    window.drawFPS();
    window.drawInfo(BOTTOMLEFT, 10, window.video.height-10);

    window.display();
}

void GameScreenPlay::getEvents(WindowManager& window, unsigned int& status) {

    window.eventMap["VK_UP"] = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
    window.eventMap["VK_W"] = sf::Keyboard::isKeyPressed(sf::Keyboard::W);

    window.eventMap["VK_DOWN"] = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
    window.eventMap["VK_S"] = sf::Keyboard::isKeyPressed(sf::Keyboard::S);

    window.eventMap["VK_LEFT"] = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
    window.eventMap["VK_A"] = sf::Keyboard::isKeyPressed(sf::Keyboard::A);

    window.eventMap["VK_RIGHT"] = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
    window.eventMap["VK_D"] = sf::Keyboard::isKeyPressed(sf::Keyboard::D);

    window.eventMap["VK_SPACE"] = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);

    if (window.eventMap["VK_ESCAPE"]) {
        window.eventMap["VK_ESCAPE"] = false;
        start = false;
        status = LOAD;
    }
    if (window.eventMap["VK_RETURN"]) {
        window.eventMap["VK_RETURN"] = false;
        status = PAUSED;
    }
}
