#pragma once

#include <FalconEngine/Platform/OpenGL/OpenGLLib.h>

#if defined(FALCON_ENGINE_API_OPENGL)
#include <FalconEngine/Graphics/Renderer/Resource/Buffer.h>
#include <FalconEngine/Graphics/Renderer/Resource/Texture1d.h>
#include <FalconEngine/Platform/OpenGL/OpenGLTexture.h>

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

#endif