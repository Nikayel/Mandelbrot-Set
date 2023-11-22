// main.cpp
#include <SFML/Graphics.hpp>
#include "ComplexPlane.h"

using namespace std;

int main()
{
    // Get desktop resolution
    int desktopWidth = sf::VideoMode::getDesktopMode().width;
    int desktopHeight = sf::VideoMode::getDesktopMode().height;

    // Divide by 2 for a smaller screen
    int screenWidth = desktopWidth / 2;
    int screenHeight = desktopHeight / 2;

    // Construct RenderWindow
    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "Mandelbrot Set");

    // Construct ComplexPlane
    ComplexPlane complexPlane(screenWidth, screenHeight);

    // Construct Font and Text objects
    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
    {
        // Handle font loading error
        return -1;
    }
    sf::Text text("", font, 16);
    text.setPosition(10, 10);

    // Begin the main loop
    while (window.isOpen())
    {
        // Handle Input segment
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                // Handle window close event
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Right)
                {
                    // Right-click to zoom out
                    complexPlane.zoomOut();
                    complexPlane.setCenter(sf::Mouse::getPosition(window));
                }
                else if (event.mouseButton.button == sf::Mouse::Left)
                {
                    // Left-click to zoom in
                    complexPlane.zoomIn();
                    complexPlane.setCenter(sf::Mouse::getPosition(window));
                }
                complexPlane.setState(ComplexPlane::State::CALCULATING);
            }
            else if (event.type == sf::Event::MouseMoved)
            {
                // Set mouse location for display
                complexPlane.setMouseLocation(sf::Mouse::getPosition(window));
                complexPlane.setState(ComplexPlane::State::CALCULATING);
            }
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            {
                // Close the window on escape key press
                window.close();
            }
        }

        // Update Scene segment
        complexPlane.updateRender();
        complexPlane.loadText(text);

        // Currect mouse position
        sf::Vector2f mouseCoords = complexPlane.getMouseLocation();
        std::stringstream mousePos;
        mousePos << "Mouse Position: (" << mouseCoords.x << ", " << mouseCoords.y << ")";
        text.setString(mousePos.str());

        // Draw Scene segment
        window.clear();
        window.draw(complexPlane);
        window.draw(text);
        window.display();
    }

    return 0;
}
