#pragma once

#include <FalconEngine/Graphics/Common.h>

#include <stdexcept>
#include <memory>

#include <FalconEngine/Graphics/Renderer/Resource/Buffer.h>

namespace FalconEngine
{

class FALCON_ENGINE_API ShaderBuffer : public Buffer
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    explicit ShaderBuffer(BufferUsage usage);
    virtual ~ShaderBuffer();
};

}
