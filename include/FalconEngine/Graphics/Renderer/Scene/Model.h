#pragma once

#include <FalconEngine/Core/Macro.h>

#include <vector>

#include <FalconEngine/Content/Asset.h>
#include <FalconEngine/Math/Vector2.h>
#include <FalconEngine/Math/Vector3.h>

namespace FalconEngine
{

class Sampler;

class Node;

FALCON_ENGINE_CLASS_BEGIN Model :
public Asset
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    Model(AssetSource assetSource, const std::string & fileName, const std::string & filePath);
    virtual ~Model();

public:
    const Node *
    GetNode() const;

    Node *
    GetNode();

    std::shared_ptr<Node>
    GetNodeSp();

    void
    SetNode(std::shared_ptr<Node> node);

    void
    SetSampler(std::shared_ptr<Sampler> sampler);

    const Sampler *
    GetSampler() const;

public:
    /************************************************************************/
    /* Model Metadata                                                       */
    /************************************************************************/
    int mIndexNum;
    int mVertexNum;

private:
    /************************************************************************/
    /* Model Runtime Data                                                   */
    /************************************************************************/
    // Model root node.
    std::shared_ptr<Node> mNode;

    // Model texture sampler.
    std::shared_ptr<Sampler> mSampler;
};
FALCON_ENGINE_CLASS_END

}
