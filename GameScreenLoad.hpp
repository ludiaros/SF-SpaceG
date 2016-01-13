#ifndef GAMELOAD_HPP
#define GAMELOAD_HPP

#include <vector>

#include "globals.hpp"
#include "GameScreen.hpp"
#include "WindowManager.hpp"

class GameScreenLoad : public GameScreen {

    public:
        //Constructors
        GameScreenLoad();
        //Methods
        virtual void                run             (WindowManager& window, unsigned int& status);
        virtual void                getEvents       (WindowManager& window, unsigned int& status);
        //Fields

    private:
        //Constructors
        //Methods
        //Fields
        unsigned int                cursor;
        sf::Vector2i                mousePos;
        std::vector<sf::String>     menuOptions;
        std::vector<sf::IntRect>    clickArea;
};

#endif
