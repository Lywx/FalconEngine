#include <FalconEngine/Graphics/Renderer/VisualLines.h>
#include <FalconEngine/Graphics/Renderer/Resources/VertexGroup.h>

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
size_t
VisualLines::GetSegmentNum() const
{
    return mSegmentStrip
           ? mVertexGroup->GetVertexNum() - 1
           : mVertexGroup->GetVertexNum() / 2;

}

}
