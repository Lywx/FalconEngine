#include <FalconEngine/Graphics/Renderers/Resources/Texture3d.h>

using namespace std;

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
Texture3d::Texture3d(std::string fileName, std::string filePath, TextureFormat format, BufferUsage usage, int mipmapLevel)
    : Texture(fileName, filePath, format, TextureType::Texture3d, usage, mipmapLevel)
{
}

Texture3d::~Texture3d()
{
}

}
