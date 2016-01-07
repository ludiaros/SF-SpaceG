#include <SFML/Window.hpp>

#include <sstream>
#include <ctime>

#include "Config.hpp"

#include "EventManager.hpp"
#include "WindowManager.hpp"
#include "TextureManager.hpp"

#include "WorldManager.hpp"
#include "GunsManager.hpp"
#include "ShipsManager.hpp"

EventList       events;
GameState       gstate;

EventManager    eventm;
WindowManager   window;

WorldManager    world(MAX_ASTER);
GunsManager     gunsm(MAX_SHOOT);
ShipsManager    shipm(MAX_SHIPS);

int main(int argc, char **argv) {

    //Carga las texturas a usar por el juego
    TextureManager::addTexture("res/gfx/ammo.png");
    TextureManager::addTexture("res/gfx/ship.png");
    TextureManager::addTexture("res/gfx/rock.png");
    TextureManager::addTexture("res/gfx/uarr.png");

    while (window.isOpen()) {//Evita que el juego se cierre cuando status == RESET

        gstate.status = RUNNING;//Inicia el juego en modo running

        window.resetZoom();//Reinicia el factor de zoom si se reinicia el juego

        srand((unsigned) time(NULL)); //Define la semilla para la generacion de numeros aleatorios

        world.reset();//Reinicia el mundo (posiciona las estrellas y asteroides)
        shipm.reset();//Reincia las naves (reinicia el estado y la posicion de cada nave)

        //Si status == RESET rompe este bucle y pasa a la linea 36 de Game.cpp
        while (gstate.status != RESET && window.isOpen()) {

            //Reinicia el contador de FPS
            window.t_fps.restart();

            // Eventos -----------------------------------------------------
            eventm.processEvents(window, gstate, events);

            if (gstate.status == RUNNING) {

                // Actualizacion de la logica del juego ------------------------
                world.update(window.view);
                gunsm.update(world, events);
                shipm.update(world, events);

                if (shipm.playerDead()) {
                    gstate.status = OVER;
                }

                if (world.active_checkpoints == 0) {

                    gstate.status = WIN;
                }
            }

            // Renderiza los objetos actualizados --------------------------
            window.clear();
            window.resetView();
            window.view.setCenter(world.playerposx, world.playerposy);  //Hace que la camara siga a
                                                                        //la nave controlada


            if (!window.rot_fixed) { window.view.setRotation(0); }  //Hace el angulo de la camara
                                                                    //fijo
            else { window.view.setRotation(world.playerposangle); } //La camara rota siguiendo el
                                                                    //angulo de la nave controlada

            world.draw(window);
            gunsm.draw(window);
            shipm.draw(window);

            window.drawLimits();

            window.setDefaultView();

            window.drawFPS();
            window.drawInfo();

            if (gstate.status == PAUSED) {
                window.drawText("PAUSED", MIDCENTER, 64, SCR_W/2, SCR_H/2);
            }

            if (gstate.status == OVER) {
                window.drawText("   GAME OVER   \nPlay again? y/n", MIDCENTER, 64, SCR_W/2, SCR_H/2);
            }

            if (gstate.status == WIN) {
                window.drawText("    YOU WIN    \nPlay again? y/n", MIDCENTER, 64, SCR_W/2, SCR_H/2);
            }

            window.display();

            // Messages and GUI --------------------------------------------
            stringstream txt2;
            txt2 << "      Speed : " << shipm.getPlayerSpeed() << endl;
            txt2 << "      Angle : " << shipm.getPlayerVAngle() << endl;
            txt2 << "     Damage : " << shipm.getPlayerDamage() << endl;
            txt2 << "     Shield : " << shipm.getPlayerShields() << endl;
            txt2 << "       Time : " << shipm.getPlayerTime() << endl;
            txt2 << endl;
            txt2 << "Checkpoints : " << world.active_checkpoints << endl;
            txt2 << "  Asteroids : " << world.active_asteroids << endl;
            txt2 << "       AMMO : " << gunsm.a_shoots << flush;
            window.info = txt2.str();

            stringstream txt1;
            txt1 << 1000/window.t_fps.getElapsedTime().asMilliseconds() << flush;
            window.fps = txt1.str();
        }
    }

    return EXIT_SUCCESS;
}
