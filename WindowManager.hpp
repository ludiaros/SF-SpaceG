#ifndef WINDOWMANAGER_HPP
#define WINDOWMANAGER_HPP

#include "Config.hpp"

using namespace std;

class WindowManager : public RenderWindow {

    public:
        //Constructors
        WindowManager();
        //Methods
        void            drawLimits          ();
        void            drawFPS             ();
        void            drawInfo            ();
        void            setDefaultView      ();
        void            toggleFullScreen    ();
        void            resetZoom           ();
        void            resetView           ();
        void            setZoom             (float z);
        void            setCenter           (sf::Vector2f center);
        void            drawText            (String txt, int align, int fontsize, int x, int y);
        //Fields
        sf::Clock       t_fps;         //Temporizador para lle var la cuenta de FPS (SFML sf::Clock)
        sf::Font        font;          //Fuente a usar en los textos (SFML sf::Font)
        sf::String      title;         //
        sf::String      fps;           //Cadena que contiene el texto de FPS
        sf::String      info;          //Cadena que contiene el texto de informacion
        sf::Text        text;          //Textos a mostrar en pantalla (SFML sf::Text)
        sf::VideoMode   video;         //Modo de video (SFML sf::VideoMode)
        sf::View        view;          //Vista principal (SFML sf::View)
        bool            rot_fixed;     //Cambiar el punto de referencia para la rotacion (nave / mapa)
        bool            show_info;     //Mostrar / ocultar informacion en pantalla
        bool            show_fps;      //Mostrar /Ocultar contador FPS
        bool            show_limits;   //Mostrar /Ocultar Limites del area
        bool            fullscr;       //Iniciar en pantalla completa o modo ventana

    private:
        //Constructors
        //Methods
        //Fields
        int             px;
        int             py;
        int             style;         //Indica si la ventana esta en pantalla completa
        float           zoom;
        float           zoom_min;
        float           zoom_max;
        VertexArray     limits;
};

#endif
