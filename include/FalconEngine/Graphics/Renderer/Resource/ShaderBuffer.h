#pragma once

#include <FalconEngine/Core/Macro.h>

#include <FalconEngine/Graphics/Renderer/Resource/Buffer.h>

namespace FalconEngine
{

class FALCON_ENGINE_API ShaderBuffer : public Buffer
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    ShaderBuffer(size_t storageSize,
                 BufferStorageMode storageMode,
                 ResourceCreationAccessMode accessMode,
                 ResourceCreationAccessUsage accessUsage);
    virtual ~ShaderBuffer();
};

}
