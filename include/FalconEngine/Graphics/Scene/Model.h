#pragma once

#include <FalconEngine/Graphics/SceneInclude.h>

#include <vector>

#include <FalconEngine/Content/Asset.h>

namespace FalconEngine
{

struct ModelVertex
{
    Vector3f mPosition;
    Vector3f mNormal;
    Vector2f mTexCoord;
};

using ModelIndex = int;

class Sampler;
using SamplerSharedPtr = std::shared_ptr<Sampler>;

class Node;
using NodeSharedPtr = std::shared_ptr<Node>;

class Model : public Asset
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    Model(const std::string& fileName, const std::string& filePath);
    virtual ~Model();

public:
    void
    SetNode(NodeSharedPtr node)
    {
        mNode = node;
    }

    NodeSharedPtr
    GetNode()
    {
        return mNode;
    }

    void
    SetSampler(SamplerSharedPtr sampler)
    {
        mSampler = sampler;
    }

    const Sampler *
    GetSampler() const
    {
        return mSampler.get();
    }

    /************************************************************************/
    /* Model Loadtime Data                                                  */
    /************************************************************************/
public:
    std::vector<std::string> mTextureArchivePathVector;                        // Model texture archive paths
    std::vector<std::string> mTextureFilePathVector;                           // Model raw texture paths

    /************************************************************************/
    /* Model Runtime Data                                                   */
    /************************************************************************/
private:
    NodeSharedPtr            mNode;                                            // Model root node.
    SamplerSharedPtr         mSampler;                                         // Model texture sampler.
};

}
