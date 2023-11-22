#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <iostream>
class ComplexPlane : public sf::Drawable
{
public:
    // Constants
    const unsigned int MAX_ITER = 64;
    const float BASE_WIDTH = 4.0;
    const float BASE_HEIGHT = 4.0;
    const float BASE_ZOOM = 0.5;

    // Enum class
    enum class State
    {
        CALCULATING,
        DISPLAYING
    };

    // Constructors and destructor
    ComplexPlane(int pixelWidth, int pixelHeight);

    // Member functions
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    void updateRender();
    void zoomIn();
    void zoomOut();
    void setCenter(sf::Vector2i mousePixel);
    void setMouseLocation(sf::Vector2i mousePixel);
    void loadText(sf::Text &text);
    size_t countIterations(sf::Vector2f coord);
    void iterationsToRGB(size_t count, sf::Uint8 &r, sf::Uint8 &g, sf::Uint8 &b);
    sf::Vector2f mapPixelToCoords(sf::Vector2i mousePixel);

private:
    // Private member functions
    void initializeVertexArray();

    // Private member variables
    int m_pixelWidth;
    int m_pixelHeight;
    float m_aspectRatio;
    sf::Vector2f m_plane_center;
    sf::Vector2f m_plane_size;
    int m_zoomCount;
    State m_State;
    sf::VertexArray m_vArray;
    sf::Vector2f m_mouseLocation;
};
