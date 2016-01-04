#ifndef EVENTMANAGER_HPP
#define EVENTMANAGER_HPP

#include "Config.hpp"
#include "WindowManager.hpp"
#include "Ship.hpp"

using namespace sf;
using namespace std;

class EventManager {

    public:
        //Constructors
        EventManager();
        //Methods
        void processEvents  (WindowManager& window, GameState& gstate, EventList& events);
        //Fields

    private:
        //Constructors
        //Methods
        //Fields
};

#endif
