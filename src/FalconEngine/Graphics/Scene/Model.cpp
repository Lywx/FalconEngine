#include <FalconEngine/Graphics/Scene/Model.h>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

using namespace std;

namespace FalconEngine
{

Model::Model(const std::string& fileName, const std::string& filePath) :
    Asset(fileName, filePath)
{
}

Model::~Model()
{
}
}
