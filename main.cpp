#include "include/World.hpp"

#include <SFML/Graphics.hpp>

#include <iostream>

#define ZOOM_FRACTION 20

int main()
{
    // Create the main window
    sf::RenderWindow App(sf::VideoMode(WORLD_W, WORLD_H), "Game of Life");

    // Load a sprite to display
    sf::Image Image;
    if (!Image.LoadFromFile("cb.bmp"))
        return EXIT_FAILURE;
    sf::Sprite Sprite(Image);

    //Game of life;
    World gameOfLife;
    bool pausedGame = true;

    //View (pour zoom)
    sf::View zoomView;
    zoomView.SetHalfSize(WORLD_W / ZOOM_FRACTION, WORLD_H / ZOOM_FRACTION);
    bool zoom = false;

	// Start the game loop
    while (App.IsOpened())
    {
        // Process events
        sf::Event Event;
        while (App.GetEvent(Event))
        {
            // Close window : exit
            if (Event.Type == sf::Event::Closed)
                App.Close();
            // Simulation controls
            if (Event.Type == sf::Event::KeyPressed)
            {
                // Pause simulation
                if(Event.Key.Code == sf::Key::Space)
                {
                    if(pausedGame)
                        pausedGame = false;
                    else
                        pausedGame = true;
                }

                // Toggle zoom
                if(Event.Key.Code == sf::Key::Z)
                {
                    if(zoom)
                    {
                        zoom = false;
                        App.SetView(App.GetDefaultView());
                    }
                    else
                    {
                        zoom = true;
                        App.SetView(zoomView);
                    }
                }

                // Randomize each cell state
                if(Event.Key.Code == sf::Key::R)
                {
                    gameOfLife.Reset();
                }

                // Kill all cells
                if(Event.Key.Code == sf::Key::C)
                {
                    gameOfLife.Clear(false);
                }

                // Step by step (only when paused)
                if(Event.Key.Code == sf::Key::Right && pausedGame == true)
                {
                    if(Event.Key.Control)
                    {
                        for(unsigned int i=0; i<10; i++)
                        {
                            gameOfLife.ComputeNextStep();
                        }
                    }
                    else
                    {
                        gameOfLife.ComputeNextStep();
                    }
                }
                if(Event.Key.Code == sf::Key::E)
                {
                    gameOfLife.ToggleEpileptic();
                }
            }
            if(Event.Type == sf::Event::MouseMoved)
            {
                if(!zoom)
                {
                    zoomView.SetCenter(Event.MouseMove.X, Event.MouseMove.Y);
                }
            }
            if(Event.Type )

            // Change cell state according to mouse button
            if(Event.Type == sf::Event::MouseButtonReleased && zoom)
            {
                sf::Vector2f mousePos = App.ConvertCoords(Event.MouseButton.X, Event.MouseButton.Y);

                mousePos.x = floor(mousePos.x - 0.5f);
                mousePos.y = floor(mousePos.y - 0.5f);

                if(Event.MouseButton.Button == sf::Mouse::Left)
                    gameOfLife.SetCell((int) mousePos.x, (int) mousePos.y, true);
                if(Event.MouseButton.Button == sf::Mouse::Right)
                    gameOfLife.SetCell((int) mousePos.x, (int) mousePos.y, false);
            }
        }

        if(!pausedGame)
        {
            gameOfLife.ComputeNextStep();
        }

        App.Clear(sf::Color::White);
        gameOfLife.Draw(App);

        // Update the window
        App.Display();
    }

    return EXIT_SUCCESS;
}
