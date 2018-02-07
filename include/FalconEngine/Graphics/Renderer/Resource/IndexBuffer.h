#pragma once

#include <FalconEngine/Core/Macro.h>

#include <stdexcept>
#include <memory>

#include <FalconEngine/Graphics/Renderer/Resource/Buffer.h>

namespace FalconEngine
{

enum class IndexType
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
    IndexBuffer(int indexNum,
                IndexType indexType,
                ResourceCreationAccessMode accessMode,
                ResourceCreationAccessUsage accessUsage,
                ResourceStorageMode storageMode);
    virtual ~IndexBuffer();

public:
    IndexType
    GetIndexType() const;

private:
    IndexType mType;
};

}
