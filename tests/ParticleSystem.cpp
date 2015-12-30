#include <SFML/Graphics.hpp>

#include <sstream>
#include <cmath>
#include <ctime>

class ParticleSystem : public sf::Drawable, public sf::Transformable {

    public:

        ParticleSystem(unsigned int count, unsigned int deviation) :
            m_particles(count),
            m_deviation(deviation),
            m_vertices(sf::Points, count),
            m_lifetime(sf::seconds(3)),
            m_emitter(0, 0)
        {
        }

        void setMaxSpeed(int mxspeed) {

            m_vmax = mxspeed;
        }

        void setEmitter(sf::Vector2f position) {

            m_emitter = position;
        }

        void setAperture(int aperture) {

            m_aperture = aperture;
        }

        void setAngle(int angle) {

            m_angle = angle;
        }

        void rotate(int angle) {

            m_angle += angle;
        }

        void update(sf::Time elapsed) {

            for (std::size_t i=0; i<m_particles.size(); ++i) {

                // update the particle lifetime
                m_particles[i].lifetime -= elapsed;

                // if the particle is dead, respawn it
                if (m_particles[i].lifetime <= sf::Time::Zero) resetParticle(i);

                // update the position of the corresponding vertex
                m_vertices[i].position += m_particles[i].velocity * elapsed.asSeconds();

                // update the alpha (transparency) of the particle according to its lifetime
                float ratio = m_particles[i].lifetime.asSeconds() / m_lifetime.asSeconds();

                m_vertices[i].color.a = static_cast<sf::Uint8>(ratio * 255);
            }
        }

    private:

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {

            // apply the transform
            states.transform *= getTransform();

            // our particles don't use a texture
            states.texture = NULL;

            // draw the vertex array
            target.draw(m_vertices, states);
        }

    private:

        struct Particle {
            sf::Vector2f velocity;
            sf::Time lifetime;
        };

        void resetParticle(std::size_t index) {

            // give a random velocity and lifetime to the particle
            float angle = (m_angle - m_aperture) + (std::rand() % (m_aperture * 2));
            float speed = 5 + (std::rand() % m_vmax);

            m_particles[index].velocity = sf::Vector2f(
                std::cos(angle * 3.14f / 180.f) * speed,
                std::sin(angle * 3.14f / 180.f) * speed
            );

            m_particles[index].lifetime = sf::milliseconds(1000 + (std::rand() % 1500));

            // reset the position of the corresponding vertex
            m_vertices[index].position = sf::Vector2f(
                (m_emitter.x - m_deviation) + (std::rand() % (m_deviation * 2)),
                (m_emitter.y - m_deviation) + (std::rand() % (m_deviation * 2))
            );
        }

        std::vector<Particle> m_particles;
        sf::VertexArray m_vertices;
        sf::Time m_lifetime;
        sf::Vector2f m_emitter;
        int m_deviation;
        int m_angle;
        int m_aperture;
        int m_vmax;
};

int main() {

    srand(std::time(NULL));

    // create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Particles");
    window.setVerticalSyncEnabled(true);

    // create the particle system
    ParticleSystem particles(10000, 25);

    // create a clock to track the elapsed time
    sf::Clock clock;
    sf::Clock timer;

    // run the main loop
    while (window.isOpen()) {

        // handle events

        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
            if (event.type == sf::Event::MouseWheelMoved) particles.rotate(event.mouseWheel.delta);
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

            // make the particle system emitter follow the mouse
            sf::Vector2i mouse = sf::Mouse::getPosition(window);
            particles.setEmitter(window.mapPixelToCoords(mouse));
            particles.setMaxSpeed(5+rand()%500);
            particles.setAperture(1);
        }

        /*if (timer.getElapsedTime().asMilliseconds() > 500) {

            particles.setEmitter(sf::Vector2f(200+rand()%400, 150+rand()%300));
            particles.setAperture(180);//5+rand()%175);
            particles.setAngle(rand()%360);

            timer.restart();
        }*/

        // update it
        sf::Time elapsed = clock.restart();
        particles.update(elapsed);

        // draw it
        window.clear();
        window.draw(particles);
        window.display();
    }

    return 0;
}
