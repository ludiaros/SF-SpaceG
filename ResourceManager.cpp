#include "ResourceManager.hpp"

std::map<sf::String, sf::Texture*> ResourceManager::textures;
std::map<sf::String, sf::Font*>    ResourceManager::fonts;

ResourceManager::ResourceManager() {}

bool ResourceManager::addFont(sf::String name, sf::String path) {

    fonts[name] = new sf::Font();
    if (fonts[name]->loadFromFile(path)) {
        return true;
    }
    return false;
}

bool ResourceManager::addTexture(sf::String name, sf::String path) {

    textures[name] = new sf::Texture();
    if (textures[name]->loadFromFile(path)) {
        return true;
    }
    return false;
}

sf::Font* ResourceManager::getFont(sf::String name) {
    return fonts[name];
}

sf::Texture* ResourceManager::getTexture(sf::String name) {
    return textures[name];
}

