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
void
VertexGroup::ClearVertexBuffer()
{
    mVertexBufferTable.clear();
}

bool
VertexGroup::ContainVertexBuffer(int bindingIndex, std::shared_ptr<VertexBuffer> vertexBuffer)
{
    return mVertexBufferTable.find(bindingIndex) != mVertexBufferTable.end()
           && mVertexBufferTable.at(bindingIndex).GetBuffer() == vertexBuffer.get();
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
VertexGroup::SetVertexBuffer(int bindingIndex, std::shared_ptr<VertexBuffer> vertexBuffer, int offset, int stride)
{
    FALCON_ENGINE_CHECK_NULLPTR(vertexBuffer);

    mVertexBufferTable.insert(std::make_pair(bindingIndex, VertexBufferBinding(vertexBuffer, bindingIndex, offset, stride)));
}

}
