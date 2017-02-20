#include <FalconEngine/Graphics/Renderers/VisualPoints.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
VisualPoints::VisualPoints(VertexFormatSharedPtr vertexFormat, int vertexNum) :
    Visual(PrimitiveType::Point, vertexFormat)
{
    SetVertexNum(vertexNum);
    SetPrimitiveNum();
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
