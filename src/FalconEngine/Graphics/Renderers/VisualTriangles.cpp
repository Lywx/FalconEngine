#include <FalconEngine/Graphics/Renderers/VisualTriangles.h>

namespace FalconEngine
{

FALCON_ENGINE_RTTI_IMPLEMENT(VisualTriangles, Visual);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
VisualTriangles::VisualTriangles() :
    Visual(PrimitiveType::Triangle),
    mTriangleNum(0)
{
    // NOTE(Wuxiang): The user for this constructor should be responsible for
    // correctly initializing the mTriangleNum.
}

VisualTriangles::VisualTriangles(VertexFormatSharedPtr vertexFormat, int vertexNum, IndexBufferSharedPtr indexBuffer) :
    Visual(PrimitiveType::Triangle, vertexFormat, indexBuffer)
{
    SetVertexNum(vertexNum);
    SetPrimitiveNum();
}

VisualTriangles::~VisualTriangles()
{
}

/************************************************************************/
/* Protected Members                                                    */
/************************************************************************/
void
VisualTriangles::SetPrimitiveNum()
{
    Primitives::SetPrimitiveNum();

    if (mIndexBuffer)
    {
        mTriangleNum = mIndexBuffer->mElementNum / 3;
    }
    else
    {
        mTriangleNum = mVertexNum / 3;
    }
}

}
