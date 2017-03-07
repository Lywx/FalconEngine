#pragma once

#include <FalconEngine/Graphics/SceneInclude.h>

#include <vector>

#include <FalconEngine/Content/Asset.h>
#include <FalconEngine/Math/Vector2.h>
#include <FalconEngine/Math/Vector3.h>

namespace FalconEngine
{

class Sampler;
using SamplerSharedPtr = std::shared_ptr<Sampler>;

class Node;
using NodeSharedPtr = std::shared_ptr<Node>;

using ModelIndex = int;

class ModelVertex
{
public:
    Vector3f mPosition;
    Vector3f mNormal;
    Vector2f mTexCoord;
};

class Model : public Asset
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    Model(const std::string& fileName, const std::string& filePath);
    virtual ~Model();

public:
    NodeSharedPtr
    GetNode();

    void
    SetNode(NodeSharedPtr node);

    void
    SetSampler(SamplerSharedPtr sampler);

    const Sampler *
    GetSampler() const;

    /************************************************************************/
    /* Model Loadtime Data                                                  */
    /************************************************************************/
public:
    std::vector<std::string> mTextureArchivePathList;                        // Model texture archive paths
    std::vector<std::string> mTextureFilePathList;                           // Model raw texture paths

    /************************************************************************/
    /* Model Runtime Data                                                   */
    /************************************************************************/
private:
    NodeSharedPtr    mNode;                                            // Model root node.
    SamplerSharedPtr mSampler;                                         // Model texture sampler.
};

}
