#ifndef GAMEWIN_HPP
#define GAMEWIN_HPP

#include "globals.hpp"
#include "GameScreen.hpp"
#include "WindowManager.hpp"

class GameScreenWin : public GameScreen {

    public:
        //Constructors
        GameScreenWin();
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
