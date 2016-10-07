#include <FalconEngine/Graphics/Scenes/Visual.h>

namespace FalconEngine {

Visual::Visual(VisualPrimitiveType primitiveType)
    : PrimitiveType(primitiveType),
      VertexFormat(nullptr), VertexBuffer(nullptr), IndexBuffer(nullptr),
      VisualEffectInstance(nullptr),
      ModelBound()
{
}

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
Visual::~Visual()
{
}

/************************************************************************/
/* Protected Members                                                    */
/************************************************************************/
void Visual::UpdateWorldBound()
{
    ModelBound.TransformBy(WorldTransform, WorldBound);
}

void Visual::UpdateModelBound()
{
    int numVertices = VertexBuffer->ElementNum();
    int stride = VertexFormat->GetStride();

    int posIndex = mVFormat->GetIndex(VertexFormat::AU_POSITION);
    if (posIndex == -1)
    {
        assertion(false, "Update requires vertex positions\n");
        return;
    }

    VertexFormat::AttributeType posType =
        mVFormat->GetAttributeType(posIndex);
    if (posType != VertexFormat::AT_FLOAT3
            &&  posType != VertexFormat::AT_FLOAT4)
    {
        assertion(false, "Positions must be 3-tuples or 4-tuples\n");
        return;
    }

    char *data = mVBuffer->GetData();
    int posOffset = mVFormat->GetOffset(posIndex);
    mModelBound.ComputeFromData(numVertices, stride, data + posOffset);

}

}
