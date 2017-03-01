#include <FalconEngine/Graphics/Renderers/Resources/VertexGroup.h>
#include <FalconEngine/Graphics/Renderers/Resources/VertexBuffer.h>

using namespace std;

namespace FalconEngine
{

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
