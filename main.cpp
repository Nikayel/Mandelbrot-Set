// main.cpp
#include <SFML/Graphics.hpp>
#include "ComplexPlane.h"

using namespace std;
using namespace sf;

int main()
{
    // Get desktop resolution
    int desktopWidth = VideoMode::getDesktopMode().width;
    int desktopHeight = VideoMode::getDesktopMode().height;

    // Divide by 2 for a smaller screen
    int screenWidth = desktopWidth / 2;
    int screenHeight = desktopHeight / 2;

    // Construct RenderWindow
    RenderWindow window(VideoMode(screenWidth, screenHeight), "Mandelbrot Set");

    // Construct ComplexPlane
    ComplexPlane complexPlane(screenWidth, screenHeight);

    // Construct Font and Text objects
    Font font;
    if (!font.loadFromFile("arial.ttf"))
    {
        // Handle font loading error
        cerr << "Error loading font file." << endl;
        return -1;
    }
    Text text("", font, 16);
    text.setPosition(10, 10);

    // Begin the main loop
    while (window.isOpen())
    {
        // Handle Input segment
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                // Handle window close event
                window.close();
            }
            else if (event.type == Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == Mouse::Right)
                {
                    // Right-click to zoom out
                    complexPlane.zoomOut();
                    complexPlane.setCenter(Mouse::getPosition(window));
                    if (complexPlane.getState() == ComplexPlane::State::DISPLAYING)
                        complexPlane.setState(ComplexPlane::State::CALCULATING);
                }
                else if (event.mouseButton.button == Mouse::Left)
                {
                    // Left-click to zoom in
                    complexPlane.zoomIn();
                    complexPlane.setCenter(Mouse::getPosition(window));
                    if (complexPlane.getState() == ComplexPlane::State::DISPLAYING)
                        complexPlane.setState(ComplexPlane::State::CALCULATING);
                }
            }
            else if (event.type == Event::MouseMoved)
            {
                // Set mouse location for display
                complexPlane.setMouseLocation(Mouse::getPosition(window));
                if (complexPlane.getState() == ComplexPlane::State::DISPLAYING)
                    complexPlane.setState(ComplexPlane::State::CALCULATING);
            }
            else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
            {
                // Close the window on escape key press
                window.close();
            }
        }

        // Update Scene segment
        complexPlane.updateRender();
        complexPlane.loadText(text);

        // Current mouse position
        //Vector2f mouseCoords = complexPlane.getMouseLocation();
        //stringstream mousePos;
        //mousePos << "Mouse Position: (" << mouseCoords.x << ", " << mouseCoords.y << ")";
        //text.setString(mousePos.str());

        // Draw Scene segment
        window.clear();
        window.draw(complexPlane);
        window.draw(text);
        window.display();
    }

    return 0;
}
