#include <FalconEngine/Graphics/Renderer/BitmapGlyph.h>

namespace FalconEngine
{

BitmapGlyph::BitmapGlyph(int id, double width, double height, double offsetX,
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
