// main.cpp
#include <SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include "ComplexPlane.h"

using namespace std;
using namespace sf;

int main()
{
    int desktopWidth = VideoMode::getDesktopMode().width;
    int desktopHeight = VideoMode::getDesktopMode().height;
    int screenWidth = desktopWidth / 2;
    int screenHeight = desktopHeight / 2;

    RenderWindow window(VideoMode(screenWidth, screenHeight), "Mandelbrot Set");
    ComplexPlane complexPlane(screenWidth, screenHeight);

    Font font;
    if (!font.loadFromFile("arial.ttf"))
    {
        cerr << "Error loading font file." << endl;
        return -1;
    }

    Text text("", font, 16);
    text.setPosition(10, 10);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
            else if (event.type == Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == Mouse::Right)
                {
                    complexPlane.zoomOut();
                    complexPlane.setCenter(Mouse::getPosition(window));
                    if (complexPlane.getState() == State::DISPLAYING)
                        complexPlane.setState(State::CALCULATING);
                }
                else if (event.mouseButton.button == Mouse::Left)
                {
                    complexPlane.zoomIn();
                    complexPlane.setCenter(Mouse::getPosition(window));
                    if (complexPlane.getState() == State::DISPLAYING)
                        complexPlane.setState(State::CALCULATING);
                }
            }
            else if (event.type == Event::MouseMoved)
            {
                complexPlane.setMouseLocation(Mouse::getPosition(window));
                if (complexPlane.getState() == State::DISPLAYING)
                    complexPlane.setState(State::CALCULATING);
            }
            else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
            {
                window.close();
            }
        }

        complexPlane.updateRender();
        complexPlane.loadText(text);

        window.clear();
        window.draw(complexPlane);
        window.draw(text);
        window.display();
    }

    return 0;
}
