#include <FalconEngine/Graphics/Renderers/Resources/Texture2d.h>

using namespace boost;
using namespace std;

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
Texture2d::Texture2d(std::string fileName, std::string filePath, TextureFormat format, BufferUsage usage, int mipmapLevel) :
    Texture(fileName, filePath, format, TextureType::Texture2d, usage, mipmapLevel)
{
}

Texture2d::~Texture2d()
{
}

}
