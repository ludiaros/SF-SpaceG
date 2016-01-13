#include "GameScreenExit.hpp"

GameScreenExit::GameScreenExit() {
}

void GameScreenExit::run(WindowManager& window, unsigned int& status) {
    //Guardar estados, liberar recursos...
    window.close();
}

void GameScreenExit::getEvents(WindowManager& window, unsigned int& status) {
}
