#include <FalconEngine/Graphics/Renderer/PrimitivePoints.h>

namespace FalconEngine
{

FALCON_ENGINE_RTTI_IMPLEMENT(PrimitivePoints, Primitive);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PrimitivePoints::PrimitivePoints(VertexFormatSharedPtr vertexFormat) :
    Primitive(PrimitiveType::Point, vertexFormat)
{
}

PrimitivePoints::PrimitivePoints(VertexFormatSharedPtr vertexFormat, VertexGroupSharedPtr vertexGroup) :
    Primitive(PrimitiveType::Point, vertexFormat, vertexGroup, nullptr)
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
