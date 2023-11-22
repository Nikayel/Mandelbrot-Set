#include "ComplexPlane.h"
#include <iostream>
#include <cmath>
using namespace std;

ComplexPlane::ComplexPlane(int pixelWidth, int pixelHeight)
{
    m_pixelWidth = pixelWidth;
    m_aspectRatio = (float)pixelWidth / (float)pixelHeight;
    m_plane_center = {0, 0};
    m_plane_size = {BASE_WIDTH, BASE_HEIGHT * m_aspectRatio};
    m_ZoomCount = 0;
    m_state = State::CALCULATING;
    // m_vArray =
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
            }
        }
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
}
void ComplexPlane::setMouseLocation(Vector2i mousPixel)
{
}
void ComplexPlane::loadText(Text &text)
{
}
int ComplexPlane::countIterations(Vector2f coord)
{
    return 0;
}
void ComplexPlane::iterationsToRGB(size_t count, Uint8 &r, Uint8 &g, Uint8 &b)
{
}
Vector2f ComplexPlane::mapPixelToCoords(Vector2i mousePixel)
{
    float xRatio = static_cast<float>(mousePixel.x) / static_cast<float>(m_pixelWidth);
    float yRatio = static_cast<float>(mousePixel.y) / static_cast<float>(m_pixelHeight);

    // Calculate the corresponding coordinates in the complex plane
    float xCoord = m_plane_center.x - 0.5f * m_plane_size.x + xRatio * m_plane_size.x;
    float yCoord = m_plane_center.y - 0.5f * m_plane_size.y + yRatio * m_plane_size.y;

    return {xCoord, yCoord};
}
