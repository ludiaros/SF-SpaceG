#ifndef GAMEPLAY_HPP
#define GAMEPLAY_HPP

#include "globals.hpp"
#include "GameScreen.hpp"
#include "WindowManager.hpp"
#include "WorldManager.hpp"
#include "GunsManager.hpp"
#include "ShipsManager.hpp"

class GameScreenPlay : public GameScreen {

    public:
        //Constructors
        GameScreenPlay();
        //Methods
        virtual void    run         (WindowManager& window, unsigned int& status);
        virtual void    getEvents   (WindowManager& window, unsigned int& status);
        //Fields

    private:
        //Constructors
        //Methods
        //Fields
        bool            start;
        WorldManager    world;
        GunsManager     gunsm;
        ShipsManager    shipm;
};

#endif
