#ifndef EVENTMANAGER_HPP
#define EVENTMANAGER_HPP

#include "Config.hpp"
#include "GunsManager.hpp"
#include "WorldManager.hpp"
#include "Ship.hpp"

using namespace sf;
using namespace std;

class EventManager {

    public:

        //Constructors
        EventManager();

        //Methods
        void processEvents  (SystemData& sys_data, Ship& player, GunsManager& guns, WorldManager& world);
};

#endif
