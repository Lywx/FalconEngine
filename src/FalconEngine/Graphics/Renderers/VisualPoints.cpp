#include <FalconEngine/Graphics/Renderers/VisualPoints.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
VisualPoints::VisualPoints(VertexFormatSharedPtr vertexFormat, VertexGroupSharedPtr vertexGroup, int vertexNum) :
    Visual(PrimitiveType::Point, vertexFormat, vertexGroup, nullptr)
{
    SetVertexNum(vertexNum);
    SetPrimitiveNum();
}

VisualPoints::VisualPoints(VertexFormatSharedPtr vertexFormat) :
    Visual(PrimitiveType::Point, vertexFormat),
    mPointNum(0)
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
    return mPointNum;
}

/************************************************************************/
/* Protected Members                                                    */
/************************************************************************/
void
VisualPoints::SetPrimitiveNum()
{
    Primitives::SetPrimitiveNum();

    mPointNum = mVertexNum;
}

}
