#pragma once

#include <FalconEngine/Core/Macro.h>

#if defined(FALCON_ENGINE_API_OPENGL)
#include <vector>

#include <FalconEngine/Graphics/Renderer/Resource/Texture2dArray.h>
#include <FalconEngine/Platform/OpenGL/OpenGLLib.h>
#include <FalconEngine/Platform/OpenGL/OpenGLTexture.h>

namespace FalconEngine
{

FALCON_ENGINE_CLASS_BEGIN PlatformTexture2dArray :
public PlatformTexture
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    explicit PlatformTexture2dArray(Renderer *, const Texture2dArray * textureArray);
    virtual ~PlatformTexture2dArray();

private:
    virtual void
    AllocateTexture() override final;
};
FALCON_ENGINE_CLASS_END

}

#endif