#pragma once

#include <FalconEngine/Platform/OpenGL/OpenGLLib.h>

#if defined(FALCON_ENGINE_API_OPENGL)
#include <vector>

#include <FalconEngine/Graphics/Renderer/Resource/Texture2dArray.h>
#include <FalconEngine/Platform/OpenGL/OpenGLTextureArray.h>

namespace FalconEngine
{

#pragma warning(disable: 4251)
class FALCON_ENGINE_API PlatformTexture2dArray : public PlatformTextureArray
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    explicit PlatformTexture2dArray(Renderer *, const Texture2dArray *textures);
    ~PlatformTexture2dArray();
};
#pragma warning(default: 4251)

}

#endif