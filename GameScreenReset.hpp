#ifndef GAMERESET_HPP
#define GAMERESET_HPP

#include "globals.hpp"
#include "GameScreen.hpp"
#include "WindowManager.hpp"

class GameScreenReset : public GameScreen {

    public:
        //Constructors
        GameScreenReset();
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
