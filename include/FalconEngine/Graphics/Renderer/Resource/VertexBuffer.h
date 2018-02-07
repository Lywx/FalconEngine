#pragma once

#include <FalconEngine/Core/Macro.h>

#include <list>

#include <FalconEngine/Graphics/Renderer/Resource/Buffer.h>

namespace FalconEngine
{

class VertexBufferBinding;

FALCON_ENGINE_CLASS_BEGIN VertexBuffer :
public Buffer
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    VertexBuffer(int vertexNum,
                 size_t vertexSize,
                 ResourceCreationAccessMode accessMode,
                 ResourceCreationAccessUsage accessUsage,
                 ResourceStorageMode storageMode);
    virtual ~VertexBuffer();

public:
    bool
    IsBound() const;

    // @summary Set vertex buffer binding for vertex buffer.
    // @params If set to null, the function would remove all existing buffer
    // binding.
    // @remark Allow multiple binding per buffer for maximum buffer use.
    void
    SetBinding(VertexBufferBinding * binding);

    std::list<VertexBufferBinding *>::const_iterator
    GetBindingBegin() const
    {
        return mBinding.cbegin();
    }

    std::list<VertexBufferBinding *>::const_iterator
    GetBindingEnd() const
    {
        return mBinding.cend();
    }

    std::list<VertexBufferBinding *>::iterator
    GetBindingBegin()
    {
        return mBinding.begin();
    }

    std::list<VertexBufferBinding *>::iterator
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
FALCON_ENGINE_CLASS_END

}
