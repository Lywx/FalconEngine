#include <FalconEngine/Graphics/Renderers/VisualPoints.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
VisualPoints::VisualPoints(VertexBufferSharedPtr vertexBuffer) :
    Visual(PrimitiveType::Point, vertexBuffer, nullptr)
{
    mPointNum = vertexBuffer->mElementNum;
}

VisualPoints::~VisualPoints()
{
}

}
