#pragma once

#include <FalconEngine/Graphics/Header.h>

#include <stdexcept>
#include <memory>

#include <FalconEngine/Graphics/Renderer/Resource/Buffer.h>

namespace FalconEngine
{

enum class FALCON_ENGINE_ITEM_GRAPHICS IndexType
{
    UnsignedShort,
    UnsignedInt
};

class FALCON_ENGINE_ITEM_GRAPHICS IndexBuffer : public Buffer
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    IndexBuffer(size_t indexNum, IndexType indexType, BufferUsage usage);
    virtual ~IndexBuffer();

public:
    int       mOffset;
    IndexType mType;
};

typedef std::shared_ptr<IndexBuffer> IndexBufferSharedPtr;
}
