#include <FalconEngine/Graphics/Renderer/Resources/VertexGroup.h>
#include <FalconEngine/Graphics/Renderer/Resources/VertexBuffer.h>

using namespace std;

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
VertexGroup::VertexGroup()
{
}

VertexGroup::~VertexGroup()
{
}

int
VertexGroup::GetVertexNum() const
{
    if (mVertexBufferTable.size() == 0)
    {
        FALCON_ENGINE_THROW_EXCEPTION("The vertex group is empty.");
    }

    return mVertexBufferTable.begin()->second.GetBuffer()->GetElementNum();
}

void
VertexGroup::SetVertexBuffer(int bindingIndex, VertexBufferSharedPtr vertexBuffer, int offset, int stride)
{
    mVertexBufferTable.insert(std::make_pair(bindingIndex, VertexBufferBinding(vertexBuffer, bindingIndex, offset, stride)));
}

}
