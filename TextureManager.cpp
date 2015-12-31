#include "TextureManager.hpp"

vector<Texture*>  TextureManager::texture_list;

TextureManager::TextureManager() {}

bool TextureManager::addTexture(string path) {

    texture_list.push_back(new Texture());
    texture_list[texture_list.size()-1]->loadFromFile(path);
}

Texture* TextureManager::getTexture(int id) {
    return texture_list[id];
}

