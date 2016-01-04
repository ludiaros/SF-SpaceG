#include <SFML/Window.hpp>

#include <sstream>
#include <iostream>
#include <ctime>
#include <cmath>

#include "Config.hpp"

#include "GunsManager.hpp"
#include "WorldManager.hpp"
#include "ShipsManager.hpp"

#include "TextureManager.hpp"
#include "WindowManager.hpp"
#include "EventManager.hpp"

EventList    events;
GameState    gstate;

EventManager eventm;
WindowManager window;
WorldManager world(MAX_ASTER);
GunsManager  gunsm(MAX_SHOOT);
ShipsManager shipm(MAX_SHIPS);

int main(int argc, char **argv) {

    gstate.reset  = false;
    gstate.paused = false;
    gstate.over   = false;
    gstate.win    = false;

    events.jump           = false;
    events.accelUp        = false;
    events.accelDn        = false;
    events.turnLeft       = false;
    events.smallTurnLeft  = false;
    events.turnRight      = false;
    events.smallTurnRight = false;
    events.shoot          = false;

    TextureManager::addTexture("res/gfx/ammo.png");
    TextureManager::addTexture("res/gfx/ship.png");
    TextureManager::addTexture("res/gfx/rock.png");
    TextureManager::addTexture("res/gfx/uarr.png");

    while (window.isOpen()) {

        gstate.reset = false;
        gstate.paused = false;
        gstate.over = false;
        gstate.win = false;

        window.resetZoom();

        srand((unsigned) time(NULL)); //Define la semilla para la generacion de numeros aleatorios

        world.reset();
        shipm.reset();
        for (unsigned int i=0; i<MAX_SHIPS; ++i) { shipm.addShip(); }

        while (!gstate.reset && window.isOpen()) {

            window.t_fps.restart();

            // Event -------------------------------------------------------
            eventm.processEvents(window, gstate, events);

            // Logic -------------------------------------------------------
            if (!gstate.paused && !gstate.over && !gstate.win) {

                world.update(window.view);
                gunsm.update(world, events);
                shipm.update(world, events);
            }

            if (shipm.ships[0].dmgact == shipm.ships[0].dmgmax) {

                gstate.over = true;
                shipm.ships[0].reset();
            }

            if (shipm.ships[0].checkpoints == CHECKPNTS) {

                gstate.win = true;
                shipm.ships[0].reset();
            }

            // Render ------------------------------------------------------
            window.clear();
            window.setView(window.view);
            window.view.setCenter(world.playerposx, world.playerposy);

            if (!window.rot_fixed) { window.view.setRotation(0); }
            else { window.view.setRotation(world.playerposangle); }

            world.draw(window);
            gunsm.draw(window);
            shipm.draw(window);

            window.drawLimits();

            window.setView(window.getDefaultView());
            window.drawFPS();
            window.drawInfo();

            if (gstate.paused) {
                window.drawText("PAUSED", 64, SCR_W/2, SCR_H/2);
            }

            if (gstate.over) {
                window.drawText("   GAME OVER   \nPlay again? y/n", 64, SCR_W/2, SCR_H/2);
            }

            if (gstate.win) {
                window.drawText("    YOU WIN    \nPlay again? y/n", 64, SCR_W/2, SCR_H/2);
            }

            window.display();

            // Messages and GUI --------------------------------------------
            stringstream txt2;
            //txt2 << "Posi: " << shipm.ships[0].getX() << ", " << shipm.ships[0].getY() << endl;
            //txt2 << "ZOOM: " << sdata.zoom << endl;
            txt2 << "ZOOM: " << window.zoom << endl;
            txt2 << "Velo: " << shipm.ships[0].getSpeed() << endl;
            txt2 << "Angl: " << shipm.ships[0].getVAngle() << endl;
            txt2 << "Damg: " << shipm.ships[0].getDamage() << endl;
            txt2 << "Time: " << shipm.ships[0].getTime() << endl;
            txt2 << endl;
            txt2 << "Checkpoints: " << shipm.ships[0].checkpoints << endl;
            txt2 << "Asteroids: " << world.a_asteroids << endl;
            txt2 << "Shields: " << shipm.ships[0].shieldmax << endl;
            txt2 << "AMMO: "  << gunsm.a_shoots << flush;
            window.info = txt2.str();

            stringstream txt1;
            txt1 << 1000/window.t_fps.getElapsedTime().asMilliseconds() << flush;
            window.fps = txt1.str();
        }
    }

    return EXIT_SUCCESS;
}
