#include "GoF.h"

#include <iostream>

GoF::GoF(bool iniState, std::vector< std::vector< bool > > iniGrid) : m_isPaused(iniState)
{
    m_step = 0;
    m_grid.resize(iniGrid.size());
    for(unsigned int i(0);i<iniGrid.size();i++)
    {
        m_grid[i].resize(iniGrid[0].size());
    }

    m_vertex.setPrimitiveType(sf::Quads);
    m_vertex.resize(m_grid.size() * m_grid[0].size() * 4);

    for(unsigned int i(0);i<m_grid.size();i++)
    {
        for(unsigned int j(0);j<m_grid[0].size();j++)
        {
            setCaseState(sf::Vector2i(i, j), iniGrid[i][j]);
        }
    }
}

GoF::~GoF()
{
    //dtor
}

void GoF::update()
{
    if(!m_isPaused)
    {
        std::vector< std::vector< int > > counterGrid;

        counterGrid.resize(m_grid.size());
        for(unsigned int i(0);i<m_grid.size();i++)
        {
            counterGrid[i].resize(m_grid[0].size());
        }

        for(unsigned int i(0);i<m_grid.size();i++)
        {
            for(unsigned int j(0);j<m_grid[0].size();j++)
            {
                if(m_grid[i][j])
                {
                    if(i!=0 && j!=0)
                        counterGrid[i-1][j-1]++;
                    if(j!=0)
                        counterGrid[i][j-1]++;
                    if(i!=0)
                        counterGrid[i-1][j]++;
                    if(i!=m_grid.size()-1 && j!=0)
                        counterGrid[i+1][j-1]++;
                    if(i!=m_grid.size()-1)
                        counterGrid[i+1][j]++;
                    if(i!=m_grid.size()-1 && j!=m_grid[0].size()-1)
                        counterGrid[i+1][j+1]++;
                    if(i!=0 && j!=m_grid[0].size()-1)
                        counterGrid[i-1][j+1]++;
                    if(j!=m_grid[0].size()-1)
                        counterGrid[i][j+1]++;
                }
            }
        }
        for(unsigned int i(0);i<counterGrid.size();i++)
        {
            for(unsigned int j(0);j<counterGrid[0].size();j++)
            {
                if(m_grid[i][j] && (counterGrid[i][j]!=2 && counterGrid[i][j]!=3))
                    setCaseState(sf::Vector2i(i,j), false);
                else if(!m_grid[i][j] && counterGrid[i][j]==3)
                    setCaseState(sf::Vector2i(i,j), true);
            }
        }
    m_step++;
    std::cout << m_step << std::endl;
    }

}

void GoF::setPause(bool newState)
{
    m_isPaused = newState;
}

void GoF::setCaseState(sf::Vector2i changingCase, bool newState)
{
    m_grid[changingCase.x][changingCase.y] = newState;

    sf::Vertex* quad = &m_vertex[(changingCase.x + changingCase.y * m_grid.size()) * 4];

    quad[0].position = sf::Vector2f(changingCase.x * TILESIZE.x, changingCase.y * TILESIZE.y);
    quad[1].position = sf::Vector2f((changingCase.x+1) * TILESIZE.x, changingCase.y * TILESIZE.y);
    quad[2].position = sf::Vector2f((changingCase.x+1) * TILESIZE.x, (changingCase.y+1) * TILESIZE.y);
    quad[3].position = sf::Vector2f(changingCase.x * TILESIZE.x, (changingCase.y+1) * TILESIZE.y);

    if(newState)
    {
        quad[0].color = sf::Color::Black;
        quad[1].color = sf::Color::Black;
        quad[2].color = sf::Color::Black;
        quad[3].color = sf::Color::Black;
    }
    else
    {
        quad[0].color = sf::Color::White;
        quad[1].color = sf::Color::White;
        quad[2].color = sf::Color::White;
        quad[3].color = sf::Color::White;
    }

}

bool GoF::isPaused()
{
    return m_isPaused;
}


void GoF::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    target.draw(m_vertex, states);
}
