#include <FalconEngine/Graphics/Renderer/VisualPoints.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
VisualPoints::VisualPoints(VertexFormatSharedPtr vertexFormat) :
    Visual(PrimitiveType::Point, vertexFormat)
{
}

VisualPoints::VisualPoints(VertexFormatSharedPtr vertexFormat, VertexGroupSharedPtr vertexGroup) :
    Visual(PrimitiveType::Point, vertexFormat, vertexGroup, nullptr)
{
}

VisualPoints::~VisualPoints()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
int
VisualPoints::GetPointNum() const
{
    return GetVertexNum();
}

}
