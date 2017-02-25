#include <FalconEngine/Graphics/Renderers/Resources/VertexGroup.h>

using namespace std;

namespace FalconEngine
{

FALCON_ENGINE_RTTI_IMPLEMENT(VertexGroup, Object);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
VertexGroup::VertexGroup() :
    mVertexNum(0)
{
}

VertexGroup::~VertexGroup()
{
}

void VertexGroup::SetVertexBuffer(int bindingIndex, VertexBufferSharedPtr vertexBuffer, int offset, int stride)
{
    if (GetVertexNum() == 0)
    {
        SetVertexNum(vertexBuffer->GetElementNum());
    }

    mVertexBufferTable.insert(std::make_pair(bindingIndex, VertexBufferBinding(vertexBuffer, bindingIndex, offset, stride)));
}
}
