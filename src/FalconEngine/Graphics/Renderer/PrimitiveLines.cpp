#include <FalconEngine/Graphics/Renderer/PrimitiveLines.h>
#include <FalconEngine/Graphics/Renderer/Resource/VertexBuffer.h>

namespace FalconEngine
{

FALCON_ENGINE_RTTI_IMPLEMENT(PrimitiveLines, Primitive);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PrimitiveLines::PrimitiveLines(std::shared_ptr<VertexBuffer> vertexBuffer, bool vertexStrip) :
    Primitive(vertexStrip
              ? PrimitiveType::LineStrip
              : PrimitiveType::Line, vertexBuffer, nullptr),
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
           ? mVertexBuffer->GetElementNum() - 1
           : mVertexBuffer->GetElementNum() / 2;

}

}
