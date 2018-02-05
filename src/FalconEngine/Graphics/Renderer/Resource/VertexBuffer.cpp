#include <FalconEngine/Graphics/Renderer/Resource/VertexBuffer.h>
#include <FalconEngine/Graphics/Renderer/Resource/VertexBufferBinding.h>

using namespace std;

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
VertexBuffer::VertexBuffer(int vertexNum,
                           size_t vertexSize,
                           BufferStorageMode storageMode,
                           ResourceCreationAccessMode accessMode,
                           ResourceCreationAccessUsage accessUsage) :
    Buffer(vertexNum, vertexSize, storageMode, BufferType::VertexBuffer, accessMode, accessUsage)
{
}

VertexBuffer::~VertexBuffer()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
bool
VertexBuffer::IsBound() const
{
    return !mBinding.empty();
}

void
VertexBuffer::SetBinding(VertexBufferBinding *binding)
{
    if (binding)
    {
        auto iter = std::find(mBinding.begin(), mBinding.end(), binding);
        if (iter == mBinding.end())
        {
            mBinding.push_back(binding);
        }
    }
    else
    {
        mBinding.clear();
    }
}

void
VertexBuffer::SetDataOffset(int64_t dataOffset)
{
    Buffer::SetDataOffset(dataOffset);

    for (auto vertexBufferBindingIter = GetBindingBegin();
            vertexBufferBindingIter != GetBindingEnd();
            ++vertexBufferBindingIter)
    {
        (*vertexBufferBindingIter)->SetOffset(dataOffset);
    }
}

}
