#ifndef GAMECREDITS_HPP
#define GAMECREDITS_HPP

#include "globals.hpp"
#include "GameScreen.hpp"
#include "WindowManager.hpp"

class GameScreenCredits: public GameScreen {

    public:
        //Constructors
        GameScreenCredits();
        //Methods
        virtual void    run         (WindowManager& window, unsigned int& status);
        virtual void    getEvents   (WindowManager& window, unsigned int& status);
        //Fields

    private:
        //Constructors
        //Methods
        //Fields
        bool            start;
        unsigned int    maxTimeActive;
        sf::Clock       timeActive;
};

#endif
