#include <FalconEngine/Graphics/Renderer/Shader/ShaderSource.h>

using namespace std;

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
ShaderSource::ShaderSource(AssetSource assetSource, std::string fileName, std::string filePath) :
    Asset(assetSource, AssetType::Shader, fileName, filePath)
{
}

ShaderSource::~ShaderSource()
{
}

}
