#include <FalconEngine/Graphics/Renderer/Resource/Texture3d.h>

using namespace std;

namespace FalconEngine
{

FALCON_ENGINE_TEXTURE_IMPLEMENT(Texture3d, TextureType::Texture3d);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
Texture3d::Texture3d(AssetSource assetSource,
                     const std::string& fileName,
                     const std::string& filePath,
                     int width,
                     int height,
                     int depth,
                     TextureFormat format,
                     ResourceCreationAccessMode accessMode,
                     ResourceCreationAccessUsage accessUsage,
                     int mipmapLevel)
    : Texture(assetSource, fileName, filePath, width, height, depth, format,
              TextureType::Texture3d, accessMode, accessUsage,
              ResourceStorageMode::Host, mipmapLevel)
{
}

Texture3d::~Texture3d()
{
}

}
