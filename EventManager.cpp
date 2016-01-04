#include "EventManager.hpp"

EventManager::EventManager() {}

void EventManager::processEvents(WindowManager& window, GameState& gstate, EventList& events) {

    if (!gstate.paused){

        if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W)) {
            events.accelUp = true;
        }

        if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S)) {
            events.accelDn = true;
        }

        if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A)) {
            events.turnLeft = true;
        }

        if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D)) {
            events.turnRight = true;
        }

        if (Keyboard::isKeyPressed(Keyboard::Space)) {
            events.shoot = true;
        }

        if (Keyboard::isKeyPressed(Keyboard::Add)) {

            if (window.zoom >= 0.25) {
                window.view.zoom(0.95);
                window.zoom *= 0.95;
            }
            if (window.zoom <= 0.25) {
                window.view.zoom(0.25 / window.zoom);
                window.zoom = 0.25;
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Subtract)) {

            if (window.zoom <= 50) {
                window.view.zoom(1.05);
                window.zoom *= 1.05;
            }
            if (window.zoom >= 50) {
                window.view.zoom(50 / window.zoom);
                window.zoom = 50;
            }
        }
    }

    Event event;

    while (window.pollEvent(event)) {

        if (event.type == Event::Closed) {

            window.close();
        }

        if (event.type == Event::MouseWheelMoved) {

            if (!gstate.paused) {

                window.view.zoom(1 - (float) event.mouseWheel.delta / 5);
                window.zoom *= 1 - (float) event.mouseWheel.delta / 5;

                if (window.zoom <= 0.25) {
                    window.view.zoom(0.25 / window.zoom);
                    window.zoom = 0.25;
                }
                if (window.zoom >= 50) {
                    window.view.zoom(50 / window.zoom);
                    window.zoom = 50;
                }
            }
        }

        if (event.type == Event::KeyPressed) {

            switch (event.key.code) {

                case Keyboard::F4:
                    if (Keyboard::isKeyPressed(Keyboard::LAlt)) { window.close(); }
                break;

                case Keyboard::F11:
                    window.toggleFullScreen();
                break;

                case Keyboard::Numpad0:
                    if (!gstate.paused) {
                        window.view.zoom(1 / window.zoom);
                        window.zoom = 1;
                    }
                break;

                case Keyboard::Return:
                    gstate.reset = true;
                break;

                case Keyboard::Escape:
                    gstate.paused = !gstate.paused;
                break;

                case Keyboard::I:
                    window.no_info = !window.no_info;
                break;

                case Keyboard::F:
                    window.no_fps = !window.no_fps;
                break;

                case Keyboard::R:
                    if (!gstate.paused) { window.rot_fixed = !window.rot_fixed; }
                break;

                case Keyboard::Y:
                    if (gstate.over || gstate.win) {
                        gstate.reset = true;
                    }
                break;

                case Keyboard::N:
                    if (gstate.over || gstate.win) {
                        window.close();
                    }
                break;
            }
        }
    }
}
