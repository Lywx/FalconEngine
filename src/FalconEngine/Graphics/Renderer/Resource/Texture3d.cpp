#include <FalconEngine/Graphics/Renderer/Resource/Texture3d.h>

using namespace std;

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
Texture3d::Texture3d(AssetSource assetSource, const std::string& fileName, const std::string& filePath, int width, int height, int depth, TextureFormat format, BufferUsage usage, int mipmapLevel)
    : TextureBuffer(assetSource, fileName, filePath, width, height, depth, format, TextureType::Texture3d, usage, mipmapLevel)
{
}

Texture3d::~Texture3d()
{
}

}
