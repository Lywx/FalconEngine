#pragma once

#include <FalconEngine/Platform/OpenGL/OpenGLLib.h>

#if defined(FALCON_ENGINE_API_OPENGL)
#include <FalconEngine/Graphics/Renderer/Resource/Texture2d.h>
#include <FalconEngine/Platform/OpenGL/OglTexture.h>

namespace FalconEngine
{

class FALCON_ENGINE_API PlatformTexture2d : public PlatformTexture
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    explicit PlatformTexture2d(const Texture2d *texture);
    ~PlatformTexture2d();
};

}

#endif