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
VertexGroup::GetVertexNum() const
{
    if (mVertexBufferBindingTable.size() == 0)
    {
        FALCON_ENGINE_THROW_RUNTIME_EXCEPTION("The vertex group is empty.");
    }

    // Use first vertex binding to determine the element number of entire vertex
    // group.
    const shared_ptr<const VertexBufferBinding>& vertexBufferBinding
        = mVertexBufferBindingTable.begin()->second;
    return vertexBufferBinding->GetBuffer()->GetElementNum();
}

void
VertexGroup::ClearVertexBuffer()
{
    mVertexBufferBindingTable.clear();
}

const VertexBuffer *
VertexGroup::GetVertexBuffer(unsigned int bindingIndex) const
{
    CheckVertexBufferBindingValid(bindingIndex);

    const shared_ptr<const VertexBufferBinding>& vertexBufferBinding
        = mVertexBufferBindingTable.at(bindingIndex);
    return vertexBufferBinding->GetBuffer();
}

std::shared_ptr<VertexBuffer>
VertexGroup::GetVertexBuffer(unsigned int bindingIndex)
{
    CheckVertexBufferBindingValid(bindingIndex);

    return mVertexBufferBindingTable.at(bindingIndex)->GetBuffer();
}

void
VertexGroup::SetVertexBuffer(
    unsigned int                         bindingIndex,
    const std::shared_ptr<VertexBuffer>& vertexBuffer,
    int64_t                              offset,
    int                                  stride)
{
    FALCON_ENGINE_CHECK_NULLPTR(vertexBuffer);

    auto vertexBufferBinding = make_shared<VertexBufferBinding>(
                                   vertexBuffer, bindingIndex, offset,
                                   stride, this);

    vertexBuffer->SetBinding(vertexBufferBinding.get());

    mVertexBufferBindingTable.emplace(
        bindingIndex, std::move(vertexBufferBinding));
}

std::shared_ptr<VertexBufferBinding>
VertexGroup::FindVertexBufferBinding(const VertexBuffer *vertexBuffer) const
{
    if (vertexBuffer->IsBound())
    {
        for (list<VertexBufferBinding *>::const_iterator
                vertexBufferBindingIter = vertexBuffer->GetBindingBegin();
                vertexBufferBindingIter != vertexBuffer->GetBindingEnd();
                ++vertexBufferBindingIter)
        {
            const VertexBufferBinding *vertexBufferBinding
                = *vertexBufferBindingIter;

            if (vertexBufferBinding->GetGroup() == this)
            {
                auto iter = mVertexBufferBindingTable.find(
                                vertexBufferBinding->GetIndex());
                if (iter != mVertexBufferBindingTable.end())
                {
                    return iter->second;
                }
            }
        }
    }

    // Return null when both key is not registered or buffer is not the same.
    return nullptr;
}

std::shared_ptr<VertexBufferBinding>
VertexGroup::GetVertexBufferBinding(unsigned int bindingIndex) const
{
    CheckVertexBufferBindingValid(bindingIndex);

    return mVertexBufferBindingTable.at(bindingIndex);
}

/************************************************************************/
/* Private Members                                                      */
/************************************************************************/
void
VertexGroup::CheckVertexBufferBindingValid(unsigned int bindingIndex) const
{
    if (mVertexBufferBindingTable.find(bindingIndex) == mVertexBufferBindingTable.end())
    {
        FALCON_ENGINE_THROW_RUNTIME_EXCEPTION("The binding index is unspecified.");
    }
}

}
