#include "EventManager.hpp"

EventManager::EventManager() {}

void EventManager::processEvents(SystemData& sys_data, Ship& player, GunsManager& guns, WorldManager& world) {

    if (!sys_data.paused){

        if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W)) {

            if (Keyboard::isKeyPressed(Keyboard::LControl)) player.jump();
            else player.accelUp();
        }

        if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S)) {

           player.accelDn();
        }

        if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A)) {

            if (Keyboard::isKeyPressed(Keyboard::LControl)) player.turn(-1, false);
            else player.turn(-1, true);
        }

        if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D)) {

            if (Keyboard::isKeyPressed(Keyboard::LControl)) player.turn(1, false);
            else player.turn(1, true);
        }

        if (Keyboard::isKeyPressed(Keyboard::Space)) {

            guns.addShoot(sys_data.texture[0], player);
        }

        if (Keyboard::isKeyPressed(Keyboard::Add)) {

            if (sys_data.zoom >= 0.25) {
                sys_data.view.zoom(0.95);
                sys_data.zoom *= 0.95;
            }
            if (sys_data.zoom <= 0.25) {
                sys_data.view.zoom(0.25 / sys_data.zoom);
                sys_data.zoom = 0.25;
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Subtract)) {

            if (sys_data.zoom <= 50) {
                sys_data.view.zoom(1.05);
                sys_data.zoom *= 1.05;
            }
            if (sys_data.zoom >= 50) {
                sys_data.view.zoom(50 / sys_data.zoom);
                sys_data.zoom = 50;
            }
        }
    }

    Event event;

    while (sys_data.window.pollEvent(event)) {

        if (event.type == Event::Closed) {

            sys_data.window.close();
        }

        if (event.type == Event::MouseWheelMoved) {

            if (!sys_data.paused) {

                sys_data.view.zoom(1 - (float) event.mouseWheel.delta / 5);
                sys_data.zoom *= 1 - (float) event.mouseWheel.delta / 5;

                if (sys_data.zoom <= 0.25) {
                    sys_data.view.zoom(0.25 / sys_data.zoom);
                    sys_data.zoom = 0.25;
                }
                if (sys_data.zoom >= 50) {
                    sys_data.view.zoom(50 / sys_data.zoom);
                    sys_data.zoom = 50;
                }
            }
        }

        if (event.type == Event::KeyPressed) {

            switch (event.key.code) {

                case Keyboard::F4:
                    if (Keyboard::isKeyPressed(Keyboard::LAlt)) { sys_data.window.close(); }
                break;

                case Keyboard::F11:

                    if (!sys_data.fullscr) {
                        sys_data.video.width = sys_data.video.getDesktopMode().width;
                        sys_data.video.height = sys_data.video.getDesktopMode().height;
                        sys_data.style = Style::Fullscreen;
                    }
                    else {
                        sys_data.video.width = SCR_W;
                        sys_data.video.height = SCR_H;
                        sys_data.style = Style::Default;
                    }

                    sys_data.window.create(sys_data.video, "SFML First Game", sys_data.style);
                    sys_data.window.setVerticalSyncEnabled(true);
                    sys_data.window.setMouseCursorVisible(false);
                    sys_data.window.setKeyRepeatEnabled(false);

                    sys_data.fullscr = !sys_data.fullscr;
                break;

                case Keyboard::Numpad0:
                    if (!sys_data.paused) {
                        sys_data.view.zoom(1 / sys_data.zoom);
                        sys_data.zoom = 1;
                    }
                break;

                case Keyboard::Return:
                    sys_data.reset = true;
                break;

                case Keyboard::Escape:
                    sys_data.paused = !sys_data.paused;
                break;

                case Keyboard::I:
                    sys_data.no_info = !sys_data.no_info;
                break;

                case Keyboard::F:
                    sys_data.no_fps = !sys_data.no_fps;
                break;

                case Keyboard::R:
                    if (!sys_data.paused) { sys_data.rot_fixed = !sys_data.rot_fixed; }
                break;

                case Keyboard::Y:
                    if (sys_data.over || sys_data.win) {
                        sys_data.reset = true;
                    }
                break;

                case Keyboard::N:
                    if (sys_data.over || sys_data.win) {
                        sys_data.window.close();
                    }
                break;
            }
        }
    }
}
