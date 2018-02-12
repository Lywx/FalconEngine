#pragma once

#include <FalconEngine/Core/Macro.h>

#if defined(FALCON_ENGINE_API_OPENGL)
#include <FalconEngine/Graphics/Renderer/Resource/Texture2d.h>
#include <FalconEngine/Platform/OpenGL/OpenGLLib.h>
#include <FalconEngine/Platform/OpenGL/OpenGLTexture.h>

namespace FalconEngine
{

FALCON_ENGINE_CLASS_BEGIN PlatformTexture2d :
public PlatformTexture
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    explicit PlatformTexture2d(Renderer *, const Texture2d * texture);
    virtual ~PlatformTexture2d();

protected:
    virtual void
    AllocateTexture() override final;
};
FALCON_ENGINE_CLASS_END

}

#endif