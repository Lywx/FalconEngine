#include <FalconEngine/Graphics/Renderer/PrimitivePoints.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PrimitivePoints::PrimitivePoints(
    const std::shared_ptr<VertexFormat>& vertexFormat,
    const std::shared_ptr<VertexGroup>& vertexGroup) :
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
