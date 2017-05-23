#pragma once

#include <FalconEngine/Graphics/Header.h>

#include <stdexcept>
#include <memory>

#include <FalconEngine/Graphics/Renderer/Resource/Buffer.h>

namespace FalconEngine
{

enum class FALCON_ENGINE_API IndexType
{
    UnsignedShort,
    UnsignedInt
};

class FALCON_ENGINE_API IndexBuffer : public Buffer
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    IndexBuffer(int indexNum, IndexType indexType, BufferUsage usage);
    virtual ~IndexBuffer();

public:
    int       mOffset;
    IndexType mType;
};

}
