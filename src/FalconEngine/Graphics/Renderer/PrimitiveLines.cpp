#include <FalconEngine/Graphics/Renderer/PrimitiveLines.h>
#include <FalconEngine/Graphics/Renderer/Resources/VertexGroup.h>

namespace FalconEngine
{

FALCON_ENGINE_RTTI_IMPLEMENT(PrimitiveLines, Primitive);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PrimitiveLines::PrimitiveLines(VertexFormatSharedPtr vertexFormat, VertexGroupSharedPtr vertexGroup, bool vertexStrip) :
    Primitive(vertexStrip
              ? PrimitiveType::LineStrip
              : PrimitiveType::Line, vertexFormat, vertexGroup, nullptr),
    mSegmentStrip(vertexStrip)
{
}

PrimitiveLines::~PrimitiveLines()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
bool
PrimitiveLines::SegmentStrip() const
{
    return mSegmentStrip;
}

size_t
PrimitiveLines::GetSegmentNum() const
{
    return mSegmentStrip
           ? mVertexGroup->GetVertexNum() - 1
           : mVertexGroup->GetVertexNum() / 2;

}

}
