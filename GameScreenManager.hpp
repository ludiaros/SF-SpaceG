#ifndef GAMEMANAGER_HPP
#define GAMEMANAGER_HPP

#include <map>

#include "globals.hpp"

#include "GameScreen.hpp"
#include "GameScreenLoad.hpp"
#include "GameScreenConfig.hpp"
#include "GameScreenPlay.hpp"
#include "GameScreenPause.hpp"
#include "GameScreenOver.hpp"
#include "GameScreenWin.hpp"
#include "GameScreenReset.hpp"
#include "GameScreenCredits.hpp"
#include "GameScreenExit.hpp"

class GameScreenManager {

    public:
        //Constructors
        GameScreenManager();
        //Methods
        void                    addState    (int id, GameScreen* state);
        GameScreen*                   getState    ();
        //Fields
        unsigned int            status;


    private:
        //Constructors
        //Methods
        //Fields
        std::map<int, GameScreen*>    listStates;
};

#endif
