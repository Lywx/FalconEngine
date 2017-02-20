#include <FalconEngine/Graphics/Renderers/VisualLines.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
VisualLines::VisualLines(VertexFormatSharedPtr vertexFormat, int vertexNum, bool vertexStrip) :
    Visual(
        vertexStrip
        ? PrimitiveType::LineStrip
        : PrimitiveType::Line, vertexFormat, nullptr),
    mSegmentStrip(vertexStrip)
{
    SetVertexNum(vertexNum);
    SetPrimitiveNum();
}

VisualLines::~VisualLines()
{
}

/************************************************************************/
/* Protected Members                                                    */
/************************************************************************/
void
VisualLines::SetPrimitiveNum()
{
    Primitives::SetPrimitiveNum();

    mSegmentNum = mSegmentStrip
                  ? mVertexNum - 1
                  : mVertexNum / 2;
}

}
