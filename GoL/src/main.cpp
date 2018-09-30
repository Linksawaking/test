#include <SFML/Graphics.hpp>
#include <iostream>

#include "GoF.h"

int main()
{
    // Create the main window




    /*std::vector< std::vector< bool > > grille = { {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                    {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                    {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                    {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                    {0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};*/


    std::vector< std::vector< bool > > grille;
    grille.resize(80);
    for(unsigned int i(0);i<80;i++)
    {
        for(unsigned int j(0);j<80;j++)
        {
            grille[i].push_back(0);
        }
    }
    /*
    std::vector< std::vector< bool > > grille;
    grille.resize(5);
    for(unsigned int i(0);i<5;i++)
    {
        grille[i].resize(10);
        for(unsigned int j(0);j<10;j++)
        {
            grille[i][j] = grilleArray[i][j];
        }
    }*/

    GoF test(false, grille);

    sf::RenderWindow app(sf::VideoMode(grille.size()*TILESIZE.x, grille[0].size()*TILESIZE.y), "SFML window");

    sf::Clock clock;

	// Start the game loop
    while (app.isOpen())
    {
        // Process events
        sf::Event event;
        while (app.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                app.close();
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                sf::Vector2f mPos = sf::Vector2f(sf::Mouse::getPosition(app));
                test.setCaseState(sf::Vector2i(mPos.x/(TILESIZE.x), (mPos.y/(TILESIZE.y))), true);
            }
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::P)
                    test.setPause(!test.isPaused());
                if(event.key.code == sf::Keyboard::Right)
                    test.update();
            }

        }
        if (clock.getElapsedTime().asSeconds()>0.5)
        {
            clock.restart();
            test.update();
        }
        // Clear screen
        app.clear(sf::Color::Blue);

        // Draw the sprite
        app.draw(test);

        // Update the window
        app.display();
    }

    return EXIT_SUCCESS;
}
