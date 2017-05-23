#include <FalconEngine/Graphics/Renderer/PrimitivePoints.h>

namespace FalconEngine
{

FALCON_ENGINE_RTTI_IMPLEMENT(PrimitivePoints, Primitive);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PrimitivePoints::PrimitivePoints(std::shared_ptr<VertexBuffer> vertexBuffer) :
    Primitive(PrimitiveType::Point, vertexBuffer, nullptr)
{
}

PrimitivePoints::~PrimitivePoints()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
size_t
PrimitivePoints::GetPointNum() const
{
    return GetVertexNum();
}

}
