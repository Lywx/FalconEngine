#include <FalconEngine/Graphics/Renderers/VisualLines.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
VisualLines::VisualLines(VertexFormatSharedPtr vertexFormat, VertexGroupSharedPtr vertexGroup, bool vertexStrip) :
    Visual(
        vertexStrip
        ? PrimitiveType::LineStrip
        : PrimitiveType::Line, vertexFormat, vertexGroup, nullptr),
    mSegmentStrip(vertexStrip)
{
}

VisualLines::~VisualLines()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
int
VisualLines::GetSegmentNum() const
{
    return mSegmentStrip
           ? mVertexGroup->GetVertexNum() - 1
           : mVertexGroup->GetVertexNum() / 2;

}

}
