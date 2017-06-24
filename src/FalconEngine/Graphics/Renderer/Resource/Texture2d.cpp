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

Texture2d::Texture2d(AssetSource        assetSource,
                     const std::string& fileName,
                     const std::string& filePath,
                     int                width,
                     int                height,
                     TextureFormat      format,
                     BufferUsage        usage,
                     int                mipmapLevel) :
    TextureStorage(assetSource, fileName, filePath, width, height, 1, format, TextureType::Texture2d, usage, mipmapLevel)
{
}

Texture2d::~Texture2d()
{
}

}
