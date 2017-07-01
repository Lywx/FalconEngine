#pragma once

#include <FalconEngine/Graphics/Common.h>

#include <stdexcept>
#include <memory>

#include <FalconEngine/Graphics/Renderer/Resource/Buffer.h>
#include "FalconEngine/Math/Rectangle.h"

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
    IndexBuffer(int indexNum, IndexType indexType, BufferStorageMode storageMode, BufferUsage usage);
    virtual ~IndexBuffer();

public:
    IndexType
    GetIndexType() const;

private:
    IndexType mType;
};

}
