#pragma once

#include <FalconEngine/Core/Macro.h>

#include <list>

#include <FalconEngine/Graphics/Renderer/Resource/Buffer.h>

namespace FalconEngine
{

FALCON_ENGINE_CLASS_BEGIN UniformBuffer :
public Buffer
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    UniformBuffer(size_t storageSize, ResourceStorageMode storageMode);
    virtual ~UniformBuffer();

    // TODO(Wuxiang): 2018-02-07 22:47.
};
FALCON_ENGINE_CLASS_END

}
