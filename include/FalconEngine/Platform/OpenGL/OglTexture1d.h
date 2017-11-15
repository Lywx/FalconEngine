#pragma once

#include <FalconEngine/Platform/OpenGL/OglMapping.h>
#include <FalconEngine/Platform/OpenGL/OglTexture.h>

#include <FalconEngine/Graphics/Renderer/Resource/Buffer.h>
#include <FalconEngine/Graphics/Renderer/Resource/Texture1d.h>

namespace FalconEngine
{

class FALCON_ENGINE_API PlatformTexture1d : public PlatformTexture
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    explicit PlatformTexture1d(const Texture1d *texture);
    ~PlatformTexture1d();
};

}
