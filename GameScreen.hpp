#ifndef GAME_HPP
#define GAME_HPP

#include "globals.hpp"
#include "WindowManager.hpp"

class GameScreen {

    public:
        //Constructors
        GameScreen();
        //Methods
        virtual void    run         (WindowManager& window, unsigned int& status);
        virtual void    getEvents   (WindowManager& window, unsigned int& status);
        //Fields
        unsigned int    id;

    private:
        //Constructors
        //Methods
        //Fields
};

#endif
