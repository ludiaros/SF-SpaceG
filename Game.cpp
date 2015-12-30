#include <SFML/Window.hpp>

#include <sstream>
#include <iostream>
#include <ctime>
#include <cmath>

#include "Config.hpp"

#include "EventManager.hpp"
#include "GunsManager.hpp"
#include "WorldManager.hpp"
#include "ShipsManager.hpp"

SystemData   sdata;

EventManager event;
WorldManager world(MAX_ASTER);
GunsManager  gunsm(MAX_SHOOT);
ShipsManager shipm(MAX_SHIPS);

int main(int argc, char **argv) {

    sdata.video.bitsPerPixel = sdata.video.getDesktopMode().bitsPerPixel;
    sdata.video.width = SCR_W;
    sdata.video.height = SCR_H;
    sdata.style = Style::Default;
    sdata.window.create(sdata.video, "SFML First Game", sdata.style);
    sdata.window.setVerticalSyncEnabled(true);
    sdata.window.setMouseCursorVisible(false);
    sdata.window.setKeyRepeatEnabled(false);
    sdata.view.reset(FloatRect(0, 0, sdata.video.width, sdata.video.height));

    sdata.reset = false;
    sdata.paused = false;
    sdata.over = false;
    sdata.win = false;

    sdata.zoom = 1;

    if (!sdata.texture[0].loadFromFile("res/gfx/ammo.png")) return EXIT_FAILURE;
    if (!sdata.texture[1].loadFromFile("res/gfx/uarr.png")) return EXIT_FAILURE;
    if (!sdata.texture[8].loadFromFile("res/gfx/rock.png")) return EXIT_FAILURE;
    if (!sdata.texture[9].loadFromFile("res/gfx/ship.png")) return EXIT_FAILURE;

    if (!sdata.font.loadFromFile("res/font/DejaVuSansMono.ttf")) return EXIT_FAILURE;

    ///////////////////////////////////////////////////////
//    VertexArray limits(LinesStrip, 5);
//    limits[0].position = Vector2f(0, MAP_H);
//    limits[0].color = Color(0, 255, 0, 255);
//    limits[1].position = Vector2f(0, 0);
//    limits[1].color = Color(0, 255, 0, 255);
//    limits[2].position = Vector2f(MAP_W, 0);
//    limits[2].color = Color(0, 255, 0, 255);
//    limits[3].position = Vector2f(MAP_W, MAP_H);
//    limits[3].color = Color(0, 255, 0, 255);
//    limits[4].position = Vector2f(0, MAP_H);
//    limits[4].color = Color(0, 255, 0, 255);
    ///////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////
//    Sprite compass;
//    compass.setTexture(sdata.texture[1]);
//    compass.setOrigin(compass.getLocalBounds().width/2, compass.getLocalBounds().height/2);
//    compass.setPosition(SCR_W-64, SCR_H-64);
//    float x, y, theta;
    ///////////////////////////////////////////////////////

    while (sdata.window.isOpen()) {

        sdata.reset = false;
        sdata.paused = false;
        sdata.over = false;
        sdata.win = false;

        if (sdata.zoom != 1) { sdata.view.zoom(1 / sdata.zoom); }
        sdata.zoom = 1;

        srand((unsigned) time(NULL)); //Define la semilla para la generacion de numeros aleatorios

        world.reset();
        shipm.reset();
        for (unsigned int i=0; i<MAX_STARS; ++i) { world.addStar(); }
        for (unsigned int i=0; i<CHECKPNTS; ++i) { world.addStructure(); }
        for (unsigned int i=0; i<MAX_ASTER; ++i) { world.addAsteroid(sdata.texture[8]); }
        for (unsigned int i=0; i<MAX_SHIPS; ++i) { shipm.addShip(sdata.texture[9]); }

        while (!sdata.reset && sdata.window.isOpen()) {

            sdata.t_fps.restart();

            // Event -------------------------------------------------------
            event.processEvents(sdata, shipm.ships[0], gunsm, world);

            // Logic -------------------------------------------------------
            if (!sdata.paused && !sdata.over && !sdata.win) {
                world.update(sdata.view);
                gunsm.update(world);
                shipm.update(world);
            }

            if (shipm.ships[0].dmgact == shipm.ships[0].dmgmax) {
                sdata.over = true;
                shipm.ships[0].reset();
            }

            if (shipm.ships[0].checkpoints == CHECKPNTS) {
                sdata.win = true;
                shipm.ships[0].reset();
            }
            // Render ------------------------------------------------------
            sdata.window.clear();

            sdata.window.setView(sdata.view);

            sdata.view.setCenter(shipm.ships[0].getX(), shipm.ships[0].getY());

            if (!sdata.rot_fixed) { sdata.view.setRotation(0); }
            else { sdata.view.setRotation(shipm.ships[0].getRotation()); }

            world.draw(sdata.window);
            gunsm.draw(sdata.window);
            shipm.draw(sdata.window);

            ///////////////////////////////////////////////////////
            /*sdata.window.draw(limits);*/
            ///////////////////////////////////////////////////////

            sdata.window.setView(sdata.window.getDefaultView());

            if (!sdata.no_fps) {
                sdata.text = Text("FPS: " + sdata.fps, sdata.font, 16);
                sdata.text.setStyle(Text::Bold);
                sdata.text.setPosition(5, 5);
                sdata.window.draw(sdata.text);
            }

            if (!sdata.no_info) {
                sdata.text = Text(sdata.info, sdata.font, 16);
                sdata.text.setStyle(Text::Bold);
                sdata.text.setPosition(5, sdata.video.height-200);
                sdata.window.draw(sdata.text);
            }

            if (sdata.paused) {
                sdata.text = Text("PAUSED", sdata.font, 64);
                sdata.text.setStyle(Text::Bold);
                sdata.text.setOrigin(sdata.text.getLocalBounds().width/2, sdata.text.getLocalBounds().height/2);
                sdata.text.setPosition(660, 325);
                sdata.window.draw(sdata.text);
            }

            if (sdata.over) {
                sdata.text = Text("   GAME OVER   \nPlay again? y/n", sdata.font, 64);
                sdata.text.setStyle(Text::Bold);
                sdata.text.setOrigin(sdata.text.getLocalBounds().width/2, sdata.text.getLocalBounds().height/2);
                sdata.text.setPosition(660, 325);
                sdata.window.draw(sdata.text);
            }

            if (sdata.win) {
                sdata.text = Text("    YOU WIN    \nPlay again? y/n", sdata.font, 64);
                sdata.text.setStyle(Text::Bold);
                sdata.text.setOrigin(sdata.text.getLocalBounds().width/2, sdata.text.getLocalBounds().height/2);
                sdata.text.setPosition(660, 325);
                sdata.window.draw(sdata.text);
            }

            ///////////////////////////////////////////////////////
            /*x = shipm.ships[0].getX() - sdata.destx;
            y = shipm.ships[0].getY() - sdata.desty;
            theta = (acos(y / (sqrt(x*x + y*y))) * 180 / 3.141596);
            compass.setRotation(theta);
            sdata.window.draw(compass);*/
            ///////////////////////////////////////////////////////

            sdata.window.display();

            // Messages and GUI --------------------------------------------

            stringstream txt2;
            //txt2 << "Posi: " << shipm.ships[0].getX() << ", " << shipm.ships[0].getY() << endl;
            txt2 << "ZOOM: " << sdata.zoom << endl;
            txt2 << "Velo: " << shipm.ships[0].getSpeed() << endl;
            txt2 << "Angl: " << shipm.ships[0].getVAngle() << endl;
            txt2 << "Damg: " << shipm.ships[0].getDamage() << endl;
            txt2 << "Time: " << shipm.ships[0].getTime() << endl;
            txt2 << endl;
            txt2 << "Checkpoints: " << shipm.ships[0].checkpoints << endl;
            txt2 << "Asteroids: " << world.a_asteroids << endl;
            txt2 << "Shields: " << shipm.ships[0].shieldmax << endl;
            txt2 << "AMMO: "  << gunsm.a_shoots << flush;
            sdata.info = txt2.str();

            stringstream txt1;
            txt1 << 1000/sdata.t_fps.getElapsedTime().asMilliseconds() << flush;
            sdata.fps = txt1.str();
        }
    }

    return EXIT_SUCCESS;
}
