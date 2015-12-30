#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <ctime>

#define SCR_W 600
#define SCR_H 600

class Light : public sf::Sprite {

    public:

        Light() {
            m_layer.create(SCR_W, SCR_H);
            setTexture(m_layer.getTexture());
        }

        void update(float x, float y) {

            m_light.setPosition(sf::Vector2f((float) x, (float) y));
            m_layer.clear(sf::Color(0, 0, 0, 240));
            m_layer.draw(m_light, sf::BlendNone);
            m_layer.display();
        }

        void addLight(int radius, float x, float y) {

            m_lightTexture.create(radius*2, radius*2);//Textura que contiene el circulo iluminado

            m_lightTexture.clear(sf::Color(0, 0, 0, 240));

            for (unsigned int i=0; i<radius; ++i) {

                temp.setRadius(radius-(i*1.f));
                temp.setOrigin(sf::Vector2f(-(i*1.f), -(i*1.f)));
                temp.setFillColor(sf::Color(0, 0, 0, 240-(i*(240/radius))));
                temp.setPosition(sf::Vector2f(0.f, 0.f));

                m_lightTexture.draw(temp, sf::BlendNone);
            }

            m_lightTexture.display();

            m_light.setTexture(m_lightTexture.getTexture(), true);
            m_light.setOrigin(m_light.getLocalBounds().width/2, m_light.getLocalBounds().height/2);
            m_light.setPosition(x, y);
        }

        void removeLight() {
            m_light = Sprite();
        }

    private:

        sf::RenderTexture m_lightTexture;
        sf::RenderTexture m_layer;

        sf::Sprite m_light;

        sf::CircleShape temp;
};

int main() {

    srand(std::time(NULL));

    sf::RenderWindow window(sf::VideoMode(SCR_W, SCR_H), "Flashlight!");
    window.setFramerateLimit(60);
    window.setMouseCursorVisible(true);

    sf::RectangleShape rect(sf::Vector2f(100.f, 100.f));
    rect.setPosition(SCR_W/2 - 50, SCR_H/2 - 50);
    rect.setFillColor(sf::Color::Black);

    Light light;

    while(window.isOpen()) {

        sf::Event event;

        while(window.pollEvent(event)) {

            if (event.type == sf::Event::Closed) window.close();
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            light.addLight(rand()%250, sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);

        if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
            light.removeLight();

        light.update(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);

        window.clear(sf::Color::White);

        window.draw(rect);
        window.draw(light);

        window.display();
    }
}
