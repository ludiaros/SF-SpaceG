#include "GameScreenManager.hpp"

GameScreenManager::GameScreenManager() {
}

void GameScreenManager::addState(int id, GameScreen* state) {

    listStates[id] = state;
}

GameScreen* GameScreenManager::getState() {

    return listStates[status];
}
