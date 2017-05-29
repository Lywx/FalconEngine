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

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
int
VertexGroup::GetElementNum() const
{
    if (mVertexBufferTable.size() == 0)
    {
        FALCON_ENGINE_THROW_RUNTIME_EXCEPTION("The vertex group is empty.");
    }

    // Use first vertex binding to determine the element number of entire vertex
    // group.
    auto vertexBinding = mVertexBufferTable.begin()->second;
    return vertexBinding.GetBuffer()->GetElementNum();
}

void
VertexGroup::ClearVertexBuffer()
{
    mVertexBufferTable.clear();
}

const VertexBuffer *
VertexGroup::GetVertexBuffer(int bindingIndex) const
{
    if (mVertexBufferTable.find(bindingIndex) == mVertexBufferTable.end())
    {
        FALCON_ENGINE_THROW_RUNTIME_EXCEPTION("The binding index is unspecified.");
    }

    return mVertexBufferTable.at(bindingIndex).GetBuffer();
}

std::shared_ptr<VertexBuffer>
VertexGroup::GetVertexBuffer(int bindingIndex)
{
    if (mVertexBufferTable.find(bindingIndex) == mVertexBufferTable.end())
    {
        FALCON_ENGINE_THROW_RUNTIME_EXCEPTION("The binding index is unspecified.");
    }

    return mVertexBufferTable.at(bindingIndex).GetBuffer();
}

void
VertexGroup::SetVertexBuffer(int bindingIndex, std::shared_ptr<VertexBuffer> vertexBuffer, int offset, int stride)
{
    FALCON_ENGINE_CHECK_NULLPTR(vertexBuffer);

    mVertexBufferTable.insert(std::make_pair(bindingIndex, VertexBufferBinding(vertexBuffer, bindingIndex, offset, stride)));
}

}
