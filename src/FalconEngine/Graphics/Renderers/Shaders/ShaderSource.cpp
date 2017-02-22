#include <FalconEngine/Graphics/Renderers/Shaders/ShaderSource.h>

using namespace std;

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
ShaderSource::ShaderSource(std::string fileName, std::string filePath) :
    Asset(fileName, filePath)
{
}

ShaderSource::~ShaderSource()
{
}

}
