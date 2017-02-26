#include <FalconEngine/Graphics/Scenes/Model.h>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

using namespace std;

namespace FalconEngine
{

FALCON_ENGINE_RTTI_IMPLEMENT(Model, Asset);

Model::Model(const std::string& fileName, const std::string& filePath) :
    Asset(fileName, filePath)
{
}

Model::~Model()
{
}
}
