#include <FalconEngine/Graphics/Renderers/Resources/Texture2d.h>

using namespace boost;
using namespace std;

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
Texture2d::Texture2d(std::string fileName, std::string filePath, int width, int height, TextureFormat format, BufferUsage usage, int mipmapLevel) :
    TextureBuffer(fileName, filePath, width, height, 1, format, TextureType::Texture2d, usage, mipmapLevel)
{
}

Texture2d::~Texture2d()
{
}

}
