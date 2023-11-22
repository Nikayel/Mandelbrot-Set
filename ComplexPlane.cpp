// ComplexPlane.cpp
#include "ComplexPlane.h"
#include <cmath> // for pow function

using namespace std;

ComplexPlane::ComplexPlane(int pixelWidth, int pixelHeight)
    : m_pixelWidth(pixelWidth), m_pixelHeight(pixelHeight), m_aspectRatio(static_cast<float>(pixelHeight) / pixelWidth),
      m_plane_center({0.0f, 0.0f}), m_plane_size({BASE_WIDTH, BASE_HEIGHT * m_aspectRatio}),
      m_zoomCount(0), m_State(State::CALCULATING)
{
    initializeVertexArray();
}

void ComplexPlane::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_vArray, states);
}

void ComplexPlane::updateRender()
{
    if (m_State == State::CALCULATING)
    {
        for (int i = 0; i < m_pixelHeight; ++i)
        {
            for (int j = 0; j < m_pixelWidth; ++j)
            {
                // Set position in VertexArray
                m_vArray[j + i * m_pixelWidth].position = {static_cast<float>(j), static_cast<float>(i)};

                // Map pixel to coordinates in the complex plane
                sf::Vector2f coord = mapPixelToCoords({j, i});

                // Count iterations and update color
                size_t count = countIterations(coord);
                sf::Uint8 r, g, b;
                iterationsToRGB(count, r, g, b);
                m_vArray[j + i * m_pixelWidth].color = {r, g, b};
            }
        }
        m_State = State::DISPLAYING;
    }
}

void ComplexPlane::zoomIn()
{
    ++m_zoomCount;
    float xSize = BASE_WIDTH * pow(BASE_ZOOM, m_zoomCount);
    float ySize = BASE_HEIGHT * m_aspectRatio * pow(BASE_ZOOM, m_zoomCount);
    m_plane_size = {xSize, ySize};
    m_State = State::CALCULATING;
}

void ComplexPlane::zoomOut()
{
    if (m_zoomCount > 0)
    {
        --m_zoomCount;
        float xSize = BASE_WIDTH * pow(BASE_ZOOM, m_zoomCount);
        float ySize = BASE_HEIGHT * m_aspectRatio * pow(BASE_ZOOM, m_zoomCount);
        m_plane_size = {xSize, ySize};
        m_State = State::CALCULATING;
    }
}

void ComplexPlane::setCenter(sf::Vector2i mousePixel)
{
    sf::Vector2f newCenter = mapPixelToCoords(mousePixel);
    m_plane_center = newCenter;
    m_State = State::CALCULATING;
}

void ComplexPlane::setMouseLocation(sf::Vector2i mousePixel)
{
    m_mouseLocation = mapPixelToCoords(mousePixel);
}

void ComplexPlane::loadText(sf::Text &text)
{
}

size_t ComplexPlane::countIterations(sf::Vector2f coord)
{
}

void ComplexPlane::iterationsToRGB(size_t count, sf::Uint8 &r, sf::Uint8 &g, sf::Uint8 &b)
{
}

sf::Vector2f ComplexPlane::mapPixelToCoords(sf::Vector2i mousePixel)
{
}

void ComplexPlane::initializeVertexArray()
{
}
