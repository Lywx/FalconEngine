#include <FalconEngine/Graphics/Renderer/PrimitiveLines.h>
#include <FalconEngine/Graphics/Renderer/Resource/VertexGroup.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PrimitiveLines::PrimitiveLines(std::shared_ptr<VertexFormat> vertexFormat, std::shared_ptr<VertexGroup> vertexGroup, std::shared_ptr<IndexBuffer> indexBuffer, bool vertexStrip) :
    Primitive(vertexStrip
              ? PrimitiveType::LineStrip
              : PrimitiveType::Line, vertexFormat, vertexGroup, indexBuffer),
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
           ? mVertexGroup->GetElementNum() - 1
           : mVertexGroup->GetElementNum() / 2;

}

}
