#include <FalconEngine/Graphics/Renderer/Font/FontGlyph.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
FontGlyph::FontGlyph():
    mId(0),
    mPage(0),
    mWidth(0),
    mHeight(0),
    mOffsetX(0),
    mOffsetY(0),
    mAdvance(0),
    mS1(0),
    mT1(0),
    mS2(0),
    mT2(0)
{
}

FontGlyph::FontGlyph(int id, double width, double height, double offsetX,
                     double offsetY, double advance, int page, double s1, double t1,
                     double s2, double t2) :
    mId(id),
    mPage(page),
    mWidth(width),
    mHeight(height),
    mOffsetX(offsetX),
    mOffsetY(offsetY),
    mAdvance(advance),
    mS1(s1),
    mT1(t1),
    mS2(s2),
    mT2(t2)
{
}

}
