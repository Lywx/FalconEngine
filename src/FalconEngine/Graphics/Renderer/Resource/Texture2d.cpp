#include <FalconEngine/Graphics/Renderer/Resource/Texture2d.h>

using namespace boost;
using namespace std;

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
Texture2d::Texture2d(const std::string& fileName, const std::string& filePath, int width, int height, TextureFormat format, BufferUsage usage, int mipmapLevel) :
    TextureBuffer(fileName, filePath, width, height, 1, format, TextureType::Texture2d, usage, mipmapLevel)
{
}

Texture2d::~Texture2d()
{
}

}
