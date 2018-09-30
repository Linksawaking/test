#ifndef GOF_H
#define GOF_H

#include <SFML/Graphics.hpp>
#include <vector>

const sf::Vector2f TILESIZE(8, 8);

class GoF : public sf::Drawable, public sf::Transformable
{
    public:
        GoF(bool iniState, std::vector< std::vector< bool > > iniGrid);
        ~GoF();

        void update();
        void setPause(bool newState);
        bool isPaused();
        void setCaseState(sf::Vector2i changingCase, bool newState);
    protected:
        std::vector<std::vector< bool > > m_grid;
        bool m_isPaused;
        int m_step;
        sf::VertexArray m_vertex;

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif // GOF_H
