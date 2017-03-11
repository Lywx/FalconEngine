#include <FalconEngine/Graphics/Renderer/Resource/VertexGroup.h>
#include <FalconEngine/Graphics/Renderer/Resource/VertexBuffer.h>

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

size_t
VertexGroup::GetVertexNum() const
{
    if (mVertexBufferTable.size() == 0)
    {
        FALCON_ENGINE_THROW_RUNTIME_EXCEPTION("The vertex group is empty.");
    }

    return mVertexBufferTable.begin()->second.GetBuffer()->GetElementNum();
}

void
VertexGroup::SetVertexBuffer(int bindingIndex, VertexBufferSharedPtr vertexBuffer, int offset, int stride)
{
    FALCON_ENGINE_CHECK_NULLPTR(vertexBuffer);

    mVertexBufferTable.insert(std::make_pair(bindingIndex, VertexBufferBinding(vertexBuffer, bindingIndex, offset, stride)));
}

}
