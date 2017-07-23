#pragma once

#include <FalconEngine/Graphics/Common.h>

#include <list>

#include <FalconEngine/Graphics/Renderer/Resource/Buffer.h>

namespace FalconEngine
{

class VertexBufferBinding;

#pragma warning(disable: 4251)
class FALCON_ENGINE_API VertexBuffer : public Buffer
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    VertexBuffer(int               vertexNum,
                 size_t            vertexSize,
                 BufferStorageMode storageMode,
                 BufferUsage       usage);
    virtual ~VertexBuffer();

public:
    bool
    IsBound() const;

    // @summary Set vertex buffer binding for vertex buffer.
    // @params If set to null, the function would remove all existing buffer
    // binding.
    // @remark Allow multiple binding per buffer for maximum buffer use.
    void
    SetBinding(VertexBufferBinding *binding);

    auto
    GetBindingBegin() const
    {
        return mBinding.cbegin();
    }

    auto
    GetBindingEnd() const
    {
        return mBinding.cend();
    }

    auto
    GetBindingBegin()
    {
        return mBinding.begin();
    }

    auto
    GetBindingEnd()
    {
        return mBinding.end();
    }

    // @remark This function would synchronize with vertex buffer binding.
    virtual void
    SetDataOffset(int64_t dataOffset) override;

private:
    std::list<VertexBufferBinding *> mBinding;
};
#pragma warning(default: 4251)

}
