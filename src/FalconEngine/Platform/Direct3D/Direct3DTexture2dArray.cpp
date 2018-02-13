#include <FalconEngine/Platform/Direct3D/Direct3DTexture2dArray.h>

#if defined(FALCON_ENGINE_API_DIRECT3D)
#include <FalconEngine/Graphics/Renderer/Resource/Texture2dArray.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PlatformTexture2dArray::PlatformTexture2dArray(Renderer *renderer, const Texture2dArray *textureArray) :
    PlatformTexture2d(renderer, textureArray)
{
}

PlatformTexture2dArray::~PlatformTexture2dArray()
{
}

}

#endif