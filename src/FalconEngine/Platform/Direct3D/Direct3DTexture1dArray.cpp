#include <FalconEngine/Platform/Direct3D/Direct3DTexture1dArray.h>

#if defined(FALCON_ENGINE_API_DIRECT3D)
#include <FalconEngine/Graphics/Renderer/Resource/Texture1dArray.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PlatformTexture1dArray::PlatformTexture1dArray(Renderer *renderer, const Texture1dArray *textureArray) :
    PlatformTexture1d(renderer, textureArray)
{
}

PlatformTexture1dArray::~PlatformTexture1dArray()
{
}

}

#endif