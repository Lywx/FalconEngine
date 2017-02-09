#pragma once

#include <FalconEngine/Graphics/GraphicsInclude.h>

#include <assimp/scene.h>

#include <FalconEngine/Graphics/Renderers/Resources/Texture2d.h>
#include <FalconEngine/Graphics/Scenes/Mesh.h>
#include <FalconEngine/Graphics/Scenes/Node.h>

namespace FalconEngine
{

struct ModelVertex
{
    Vector3f mPosition;
    Vector3f mNormal;
    Vector2f mTexCoord;
};

using ModelIndex = int;

class Model : public Asset
{
    FALCON_ENGINE_RTTI_DECLARE;

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    Model(std::string fileName, std::string filePath);
    virtual ~Model();

public:
    Node                     mRootNode;
    std::vector<Texture2d *> mTextureVector;

    /************************************************************************/
    /* Model Loadtime Data                                                  */
    /************************************************************************/
    std::vector<std::string>  mTextureArchivePathVector;                       // Texture Archive paths
    std::vector<std::string>  mTextureFilePathVector;                          // Raw texture paths
};

typedef std::shared_ptr<Model> ModelSharedPtr;
typedef std::unique_ptr<Model> ModelUniquePtr;

}
