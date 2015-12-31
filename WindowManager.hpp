#ifndef WINDOWMANAGER_HPP
#define WINDOWMANAGER_HPP

#include "Config.hpp"

using namespace sf;
using namespace std;

class WindowManager : public RenderWindow {

    public:
        //Constructors
        WindowManager();
        //Methods
        void            setDefaultView      ();
        void            toggleFullScreen    ();
        void            resetZoom           ();
        void            setZoom             (float z);
        void            setCenter           (Vector2f center);
        //Fields
        VideoMode       video;         //Modo de video (SFML sf::VideoMode)
        String          fps;           //Cadena que contiene el texto de FPS
        String          info;          //Cadena que contiene el texto de informacion
        Font            font;          //Fuente a usar en los textos (SFML sf::Font)
        View            view;          //Vista principal (SFML sf::View)
        Text            text;          //Textos a mostrar en pantalla (SFML sf::Text)
        Clock           t_fps;         //Temporizador para lle var la cuenta de FPS (SFML sf::Clock)
        bool            rot_fixed;     //Cambiar el punto de referencia para la rotacion (nave / mapa)
        bool            no_info;       //Mostrar / ocultar informacion en pantalla
        bool            no_fps;        //Mostrar /Ocultar contador FPS
        bool            fullscr;       //Iniciar en pantalla completa o modo ventana
        int             style;         //Indica si la ventana esta en pantalla completa
        int             px;
        int             py;
        float           zoom;
        float           zoom_min;
        float           zoom_max;

    private:
        //Fields
};

#endif
