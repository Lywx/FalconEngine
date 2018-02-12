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

FALCON_ENGINE_CLASS_BEGIN IndexBuffer :
public Buffer
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
FALCON_ENGINE_CLASS_END

}
