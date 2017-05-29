#include <FalconEngine/Graphics/Renderer/PrimitivePoints.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PrimitivePoints::PrimitivePoints(std::shared_ptr<VertexFormat> vertexFormat, std::shared_ptr<VertexGroup> vertexGroup) :
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
