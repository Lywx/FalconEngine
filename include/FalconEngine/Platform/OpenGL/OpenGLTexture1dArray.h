#pragma once

#include <FalconEngine/Core/Macro.h>

#if defined(FALCON_ENGINE_API_OPENGL)
#include <vector>

#include <FalconEngine/Graphics/Renderer/Resource/Texture1dArray.h>
#include <FalconEngine/Platform/OpenGL/OpenGLLib.h>
#include <FalconEngine/Platform/OpenGL/OpenGLTexture.h>

namespace FalconEngine
{

FALCON_ENGINE_CLASS_BEGIN PlatformTexture1dArray :
public PlatformTexture
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    explicit PlatformTexture1dArray(Renderer *, const Texture1dArray * textureArray);
    virtual ~PlatformTexture1dArray();

private:
    virtual void
    AllocateTexture() override final;
};
FALCON_ENGINE_CLASS_END

}

#endif