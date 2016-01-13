#ifndef WINDOWMANAGER_HPP
#define WINDOWMANAGER_HPP

#include <cmath>
#include <map>
#include <sstream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "globals.hpp"
#include "ResourceManager.hpp"

class WindowManager : public sf::RenderWindow {

    public:
        //Constructors
        WindowManager();
        //Methods
        void                        drawCompass         ();
        void                        drawFPS             ();
        void                        drawInfo            (int align, int x, int y);
        void                        drawLimits          ();
        void                        drawText            (sf::String txt, sf::String fontId, int fontsize, int align, int x, int y);
        void                        getWindowEvents     (unsigned int& status);
        void                        resetZoom           ();
        void                        resetView           ();
        void                        restartClock        ();
        void                        setCenter           (sf::Vector2f center);
        void                        setDefaultView      ();
        void                        setZoom             (float z);
        void                        toggleFullScreen    ();
        //Fields
        bool                        fullscr;        //Iniciar en pantalla completa o modo ventana
        bool                        rotationRef;    //Cambiar el punto de referencia para la rotacion (nave / mapa)
        bool                        showFPS;        //Mostrar /Ocultar contador FPS
        bool                        showInfo;       //Mostrar / ocultar informacion en pantalla
        bool                        showLimits;     //Mostrar /Ocultar Limites del area
        float                       frameTime;      //Tiempo que tarda en renderizarse un cuadro
        GameData                    gameInfo;       //Variables relacionadas con el juego
        sf::VideoMode               video;          //Modo de video (SFML sf::VideoMode)
        sf::View                    view;           //Vista principal (SFML sf::View)
        std::map<sf::String, bool>  eventMap;       //Banderas que representan los eventos de teclado

    private:
        //Constructors
        //Methods
        //Fields
        int                 px;
        int                 py;
        int                 style;         //Indica si la ventana esta en pantalla completa
        float               zoom;
        float               zoomMin;
        float               zoomMax;
        std::stringstream   convert;
        sf::Clock           clockFPS;       //Temporizador para lle var la cuenta de FPS
        sf::Font            font;           //Fuente a usar en los textos
        sf::String          fps;            //Cadena que contiene el texto de FPS
        sf::String          info;           //Cadena que contiene el texto de informacion
        sf::String          title;          //
        sf::Text            text;           //Textos a mostrar en pantalla
        sf::VertexArray     limits;
};

#endif
