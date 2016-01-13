#ifndef RESOURCEMANAGER_HPP
#define RESOURCEMANAGER_HPP

#include <SFML/Graphics.hpp>

#include <map>

#include "globals.hpp"

class ResourceManager {

    public:
        //Constructors
        ResourceManager();
        //Methods
        static bool                                 addFont     (sf::String name, sf::String path);
        static bool                                 addTexture  (sf::String name, sf::String path);
        static sf::Font*                            getFont     (sf::String name);
        static sf::Texture*                         getTexture  (sf::String name);
        //Fields
        static std::map<sf::String, sf::Texture*>   textures;
        static std::map<sf::String, sf::Font*>      fonts;

    private:
        //Constructors
        //Methods
        //Fields
};

#endif
