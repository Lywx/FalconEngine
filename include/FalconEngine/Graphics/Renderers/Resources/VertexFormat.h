#pragma once

#include <FalconEngine/Graphics/GraphicsInclude.h>
#include <FalconEngine/Graphics/Renderers/Resources/VertexBuffer.h>
#include <FalconEngine/Graphics/Renderers/Shaders/VertexAttribute.h>

namespace FalconEngine
{

class VertexRecord
{
public:
    VertexRecord(VertexBufferSharedPtr vertexBuffer, int bindingIndex, int offset, int stride) :
        mVertexBuffer(vertexBuffer),
        mBindingIndex(bindingIndex),
        mOffset(offset),
        mStride(stride)
    {
    }

    ~VertexRecord()
    {

    }

    int
    GetBindingIndex() const
    {
        return mBindingIndex;
    }

    int
    GetOffset() const
    {
        return mOffset;
    }

    int
    GetStride() const
    {
        return mStride;
    }

    const VertexBuffer *
    GetVertexBuffer() const
    {
        return mVertexBuffer.get();
    }

private:
    int                   mBindingIndex;
    int                   mOffset;
    int                   mStride;
    VertexBufferSharedPtr mVertexBuffer;
};

using VertexRecordVector = std::vector<VertexRecord>;

enum class VertexAttributeType;

class VertexFormat : public Object
{
    FALCON_ENGINE_RTTI_DECLARE;

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    VertexFormat();
    virtual ~VertexFormat();

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/

    /************************************************************************/
    /* Vertex Attribute Management                                          */
    /************************************************************************/
    void
    PushVertexAttribute(int attributeLocation, std::string attributeName, VertexAttributeType attributeType, bool attributeNormalized, int attributeBindingIndex);

    int
    GetVertexAttributeNum() const;

    VertexAttribute&
    GetVertexAttribute(int attributeIndex);

    /************************************************************************/
    /* Vertex Buffer Management                                             */
    /************************************************************************/
    void
    PushVertexBuffer(int bindingIndex, VertexBufferSharedPtr vertexBuffer, int offset, int stride);

public:
    // NOTE(Wuxiang): THe vertex attribute vector is assumed to be in order of
    // layout location in OpenGL. This rule is enforced by the PushAttribute function.
    VertexAttributeVector    mVertexAttributeVector;
    VertexRecordVector       mVertexRecordVector;

private:
    int                      mVertexAttributeOffset;

};

using VertexFormatSharedPtr = std::shared_ptr<VertexFormat>;

}
