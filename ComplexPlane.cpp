// ComplexPlane.cpp
#include "ComplexPlane.h"
#include <iostream>
#include <cmath>

ComplexPlane::ComplexPlane(int pixelWidth, int pixelHeight)
{
    m_pixelWidth = pixelWidth;
    m_aspectRatio = (float)pixelWidth / (float)pixelHeight;
    m_plane_center = {0, 0};
    m_plane_size = {BASE_WIDTH, BASE_HEIGHT * m_aspectRatio};
    m_ZoomCount = 0;
    m_state = State::CALCULATING;

    // Assuming m_vArray is a VertexArray, initialize it with the correct size
    m_vArray.setPrimitiveType(Points);
    m_vArray.resize(m_pixelWidth * m_pixelHeight);
}

void ComplexPlane::draw(RenderTarget &target, RenderStates states) const
{
    target.draw(m_vArray);
}

void ComplexPlane::updateRender()
{
    if (m_state == State::CALCULATING)
    {
        for (int i = 0; i < m_pixelHeight; i++)
        {
            for (int j = 0; j < m_pixelWidth; j++)
            {
                m_vArray[j + i * m_pixelWidth].position = {(float)j, (float)i};
                Vector2f coordinate = mapPixelToCoords({j, i});
                size_t count = countIterations(coordinate);

                Uint8 r;
                Uint8 g;
                Uint8 b;

                iterationsToRGB(count, r, g, b);
                m_vArray[j + i * m_pixelWidth].color = {r, g, b};
            }
        }
        m_state = State::DISPLAYING;
    }
}

void ComplexPlane::zoomIn()
{
    m_ZoomCount++;
    float localXVariable = BASE_WIDTH * (pow(BASE_ZOOM, m_ZoomCount));
    float localYVariable = BASE_HEIGHT * m_aspectRatio * (pow(BASE_ZOOM, m_ZoomCount));
    m_plane_size = {localXVariable, localYVariable};
    m_state = State::CALCULATING;
}

void ComplexPlane::zoomOut()
{
    m_ZoomCount--;
    float localXVariable = BASE_WIDTH * (pow(BASE_ZOOM, m_ZoomCount));
    float localYVariable = BASE_HEIGHT * m_aspectRatio * (pow(BASE_ZOOM, m_ZoomCount));
    m_plane_size = {localXVariable, localYVariable};
    m_state = State::CALCULATING;
}

void ComplexPlane::setCenter(Vector2i mousePixel)
{
    Vector2f newCenter = mapPixelToCoords(mousePixel);
    m_plane_center = newCenter;
    m_state = State::CALCULATING;
}

void ComplexPlane::setMouseLocation(Vector2i mousePixel)
{
    m_mouseLocation = mapPixelToCoords(mousePixel);
}

void ComplexPlane::loadText(Text &text)
{
    text.setString("Hello, World!");
    text.setPosition(10.0f, 10.0f);
}

int ComplexPlane::countIterations(Vector2f coord)
{
    // Implement your iteration counting logic here
    return 0;
}

void ComplexPlane::iterationsToRGB(size_t count, Uint8 &r, Uint8 &g, Uint8 &b)
{
    // Implement your color mapping logic here
}

Vector2f ComplexPlane::mapPixelToCoords(Vector2i mousePixel)
{
    float xRatio = static_cast<float>(mousePixel.x) / static_cast<float>(m_pixelWidth);
    float yRatio = static_cast<float>(mousePixel.y) / static_cast<float>(m_pixelHeight);

    float xCoord = m_plane_center.x - 0.5f * m_plane_size.x + xRatio * m_plane_size.x;
    float yCoord = m_plane_center.y - 0.5f * m_plane_size.y + yRatio * m_plane_size.y;

    return {xCoord, yCoord};
}
