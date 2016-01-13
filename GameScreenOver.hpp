#ifndef GAMEOVER_HPP
#define GAMEOVER_HPP

#include "globals.hpp"
#include "GameScreen.hpp"
#include "WindowManager.hpp"

class GameScreenOver : public GameScreen {

    public:
        //Constructors
        GameScreenOver();
        //Methods
        virtual void    run         (WindowManager& window, unsigned int& status);
        virtual void    getEvents   (WindowManager& window, unsigned int& status);
        //Fields

    private:
        //Constructors
        //Methods
        //Fields
};

#endif
