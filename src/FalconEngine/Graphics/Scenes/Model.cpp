#include <FalconEngine/Graphics/Scenes/Model.h>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

using namespace std;

namespace FalconEngine
{

void Model::LoadFromModelFile(std::string modelFilePath)
{
    m_filePath    = modelFilePath;
    m_fileDirPath = modelFilePath.substr(0, modelFilePath.find_last_of('/'));

    static Assimp::Importer importer;

    const aiScene *scene = importer.ReadFile(modelFilePath, aiProcess_Triangulate | aiProcess_FlipUVs);
    if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        throw runtime_error(string("Error: ") + importer.GetErrorString());
    }

    m_nodeRoot = make_shared<Node>(scene, scene->mRootNode);
}

}
