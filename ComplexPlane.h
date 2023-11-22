#pragma once
#ifndef COMPLEXPLANE_H
#define COMPLEXPLANE_H

#include <SFML/Graphics.hpp>
using namespace sf;

const unsigned int MAX_ITER = 64;
const float BASE_WIDTH = 4.0;
const float BASE_HEIGHT = 4.0;
const float BASE_ZOOM = 0.5;

enum class State
{
    CALCULATING,
    DISPLAYING
};

class ComplexPlane : public Drawable
{
public:
    ComplexPlane(int pixelWidth, int pixelHeight);
    void draw(RenderTarget &target, RenderStates states) const;
    void updateRender();
    void zoomIn();
    void zoomOut();
    void setCenter(Vector2i mousePixel);
    void setMouseLocation(Vector2i mousPixel);
    void loadText(Text &text);

private:
    float m_aspectRatio;
    int m_ZoomCount;
    Vector2f m_plane_size;
    Vector2f m_plane_center;
    Vector2i m_pixel_size;
    Vector2f m_mouseLocation;
    State m_state;
    VertexArray m_vArray;
    int m_pixelWidth;
    int m_pixelHeight;

    int countIterations(Vector2f coord);
    void iterationsToRGB(size_t count, Uint8 &r, Uint8 &g, Uint8 &b);
    Vector2f mapPixelToCoords(Vector2i mousePixel);
};

#endif