#pragma once

#include <assimp/scene.h>

#include <FalconEngine/GraphicsInclude.h>
#include <FalconEngine/Graphics/Renderers/Texture2d.h>
#include <FalconEngine/Graphics/Scenes/Mesh.h>
#include <FalconEngine/Graphics/Scenes/Node.h>
#include <FalconEngine/Graphics/Scenes/Spatial.h>

namespace FalconEngine
{

class Model : public Object
{
    FALCON_ENGINE_DECLARE_RTTI;

public:
    void
    LoadFromModelFile(std::string modelFilePath);

public:
    std::string               m_filePath;
    std::string               m_fileDirPath;

    NodePtr                   m_nodeRoot;
    std::vector<Texture2dPtr> m_textureVector;
};

}
