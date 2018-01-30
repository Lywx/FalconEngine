#include <FalconEngine/Graphics/Renderer/Scene/Model.h>

#include <FalconEngine/Core/Exception.h>
#include <FalconEngine/Graphics/Renderer/Scene/Node.h>

using namespace std;

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
Model::Model(AssetSource assetSource, const std::string& fileName, const std::string& filePath) :
    Asset(assetSource, AssetType::Model, fileName, filePath),
    mVertexNum(),
    mIndexNum()
{
}

Model::~Model()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
const Node *
Model::GetNode() const
{
    return mNode.get();
}

Node *
Model::GetNode()
{
    return mNode.get();
}

std::shared_ptr<Node>
Model::GetNodeSp()
{
    return mNode;
}

void
Model::SetNode(std::shared_ptr<Node> node)
{
    FALCON_ENGINE_CHECK_NULLPTR(node);

    mNode = node;
}

void
Model::SetSampler(std::shared_ptr<Sampler> sampler)
{
    FALCON_ENGINE_CHECK_NULLPTR(sampler);

    mSampler = sampler;
}

const Sampler *
Model::GetSampler() const
{
    return mSampler.get();
}

}
