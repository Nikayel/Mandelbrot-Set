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
void ComplexPlane::setMouseLocation(Vector2i mousPixel)
{
    m_mouseLocation = mapPixelToCoords(mousePixel);
}
void ComplexPlane::loadText(Text &text)
{
    text.setString("Hello, World!");
    text.setPosition(10.0f, 10.0f);
    // or
    //  stringstream ss;
    //  ss << "Zoom Count: " << m_ZoomCount << "\n";
    //  ss << "Center: (" << m_plane_center.x << ", " << m_plane_center.y << ")\n";
    //  ss << "Mouse Location: (" << m_mouseLocation.x << ", " << m_mouseLocation.y << ")\n";
    //  text.setString(ss.str());
}
int ComplexPlane::countIterations(Vector2f coord)
{
    return 0;
}
void ComplexPlane::iterationsToRGB(size_t count, Uint8 &r, Uint8 &g, Uint8 &b)
{
    // Define constants mapping the colors
    const size_t colorRegionCount = 5;
    const size_t colorRegionSize = MAX_ITER / colorRegionCount;

    // Color for MAX_ITER
    if (count == MAX_ITER)
    {
        r = 0;
        g = 0;
        b = 0;
    }
    // will technicly be black if everything goes to zero
    else
    {
        // Determine the color region for the given iteration count
        size_t region = count / colorRegionSize;

        // Calculate a smooth color gradient within the region
        size_t regionIteration = count % colorRegionSize;
        float colorFactor = static_cast<float>(regionIteration) / colorRegionSize;

        // Define HSV values for different regions
        float hue = 0.0; // Default hue for low iteration counts

        // Adjust hue for different regions
        switch (region)
        {
        case 1:
            hue = 240.0;
            break;
        case 2:
            hue = 180.0;
            break;
        case 3:
            hue = 120.0;
            break;
        case 4:
            hue = 60.0;
            break;
        }
        // I put default as red

        // Converting HSV to RGB
        float c = 1.0;
        float x = (1.0 - std::abs(std::fmod(hue / 60.0, 2.0) - 1.0)) * c;
        float m = 0.0;

        if (hue >= 0.0 && hue < 60.0)
        {
            r = static_cast<Uint8>((c + m) * 255);
            g = static_cast<Uint8>((x + m) * 255);
            b = static_cast<Uint8>((m) * 255);
        }
        else if (hue >= 60.0 && hue < 120.0)
        {
            r = static_cast<Uint8>((x + m) * 255);
            g = static_cast<Uint8>((c + m) * 255);
            b = static_cast<Uint8>((m) * 255);
        }
        else if (hue >= 120.0 && hue < 180.0)
        {
            r = static_cast<Uint8>((m) * 255);
            g = static_cast<Uint8>((c + m) * 255);
            b = static_cast<Uint8>((x + m) * 255);
        }
        else if (hue >= 180.0 && hue < 240.0)
        {
            r = static_cast<Uint8>((m) * 255);
            g = static_cast<Uint8>((x + m) * 255);
            b = static_cast<Uint8>((c + m) * 255);
        }
        else if (hue >= 240.0 && hue < 300.0)
        {
            r = static_cast<Uint8>((x + m) * 255);
            g = static_cast<Uint8>((m) * 255);
            b = static_cast<Uint8>((c + m) * 255);
        }
        else
        {
            r = static_cast<Uint8>((c + m) * 255);
            g = static_cast<Uint8>((m) * 255);
            b = static_cast<Uint8>((x + m) * 255);
        }

        // Adjusting the color based on the color factor within the region
        r = static_cast<Uint8>((r * (1.0 - colorFactor)) + (255 * colorFactor));
        g = static_cast<Uint8>((g * (1.0 - colorFactor)) + (255 * colorFactor));
        b = static_cast<Uint8>((b * (1.0 - colorFactor)) + (255 * colorFactor));
    }
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
