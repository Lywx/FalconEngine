#include <FalconEngine/Graphics/Renderers/VisualLines.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
VisualLines::VisualLines(VertexBufferSharedPtr vertexBuffer, bool lineStrip) :
    Visual(
        lineStrip
        ? PrimitiveType::LineStrip
        : PrimitiveType::Line, vertexBuffer, nullptr),
    mSegmentStrip(lineStrip)
{
    mSegmentNum = lineStrip
                  ? vertexBuffer->mElementNum - 1
                  : vertexBuffer->mElementNum / 2;
}

VisualLines::~VisualLines()
{
}

}
