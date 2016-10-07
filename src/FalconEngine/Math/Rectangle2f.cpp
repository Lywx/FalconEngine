#include <FalconEngine/Math/Rectangle2f.h>

namespace FalconEngine {

Rectangle2f::Rectangle2f() :
    X(0),
    Y(0),
    Width(0),
    Height(0)
{
}

inline Rectangle2f::Rectangle2f(float x, float y, float width, float height) :
    X(x),
    Y(y),
    Width(width),
    Height(height)
{
}

Rectangle2f::~Rectangle2f()
{
}
}
