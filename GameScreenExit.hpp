#ifndef GAMEEXIT_HPP
#define GAMEEXIT_HPP

#include "globals.hpp"
#include "GameScreen.hpp"
#include "WindowManager.hpp"

class GameScreenExit : public GameScreen {

    public:
        //Constructors
        GameScreenExit();
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
