#include <FalconEngine/Graphics/Renderer/Resource/Texture2d.h>

using namespace std;

namespace FalconEngine
{

FALCON_ENGINE_TEXTURE_IMPLEMENT(Texture2d, TextureType::Texture2d);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
Texture2d::Texture2d()
{
}

Texture2d::Texture2d(AssetSource assetSource,
                     const std::string& fileName,
                     const std::string& filePath,
                     int width,
                     int height,
                     TextureFormat format,
                     ResourceCreationAccessMode accessMode,
                     ResourceCreationAccessUsage accessUsage,
                     int mipmapLevel) :
    Texture(assetSource, fileName, filePath, width, height, 1, format, TextureType::Texture2d, accessMode, accessUsage, ResourceStorageMode::Host, mipmapLevel)
{
}

Texture2d::~Texture2d()
{
}

}
