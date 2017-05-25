#include <FalconEngine/Graphics/Renderer/Scene/Model.h>
#include <FalconEngine/Graphics/Renderer/Scene/Node.h>

using namespace std;

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
Model::Model(AssetSource assetSource, const std::string& fileName, const std::string& filePath) :
    Asset(assetSource, AssetType::Model, fileName, filePath)
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

std::shared_ptr<Node>
Model::GetNode()
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
