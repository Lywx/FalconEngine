#pragma once

namespace FalconEngine {

class Rectangle2f
{
public:
    Rectangle2f();
    Rectangle2f(float x, float y, float width, float height);
    ~Rectangle2f();

    int X;
    int Y;
    int Width;
    int Height;
};

#include "Rectangle2f.inl"

}