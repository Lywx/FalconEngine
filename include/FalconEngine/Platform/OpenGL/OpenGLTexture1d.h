#pragma once

#include <FalconEngine/Core/Macro.h>

#if defined(FALCON_ENGINE_API_OPENGL)
#include <FalconEngine/Graphics/Renderer/Resource/Buffer.h>
#include <FalconEngine/Graphics/Renderer/Resource/Texture1d.h>
#include <FalconEngine/Platform/OpenGL/OpenGLLib.h>
#include <FalconEngine/Platform/OpenGL/OpenGLTexture.h>

namespace FalconEngine
{

FALCON_ENGINE_CLASS_BEGIN PlatformTexture1d :
public PlatformTexture
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    explicit PlatformTexture1d(Renderer * renderer, const Texture1d * texture);
    virtual ~PlatformTexture1d();

private:
    /************************************************************************/
    /* Protected Members                                                    */
    /************************************************************************/
    virtual void
    AllocateTexture() override final;
};

}

#endif