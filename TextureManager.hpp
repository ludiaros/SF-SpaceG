#ifndef TEXTUREMANAGER_HPP
#define TEXTUREMANAGER_HPP

#include <vector>

#include "Config.hpp"

using namespace sf;
using namespace std;

class TextureManager {

    public:
        //Constructors
        TextureManager();
        //Methods
        static bool             addTexture(string path);
        static Texture*          getTexture(int id);
        //Fields
        static vector<Texture*>  texture_list;

    private:
        //Constructors
        //Methods
        //Fields
};

#endif
