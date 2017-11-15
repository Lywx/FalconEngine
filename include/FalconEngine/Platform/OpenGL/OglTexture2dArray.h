#pragma once

#include <FalconEngine/Platform/OpenGL/OglMapping.h>
#include <FalconEngine/Platform/OpenGL/OglTextureArray.h>

#include <vector>

#include <FalconEngine/Graphics/Renderer/Resource/Texture2dArray.h>

namespace FalconEngine
{

#pragma warning(disable: 4251)
class FALCON_ENGINE_API PlatformTexture2dArray : public PlatformTextureArray
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    explicit PlatformTexture2dArray(const Texture2dArray *textures);
    ~PlatformTexture2dArray();
};
#pragma warning(default: 4251)

}
