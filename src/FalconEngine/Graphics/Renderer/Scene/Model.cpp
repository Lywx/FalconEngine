#include <FalconEngine/Graphics/Renderer/Scene/Model.h>

using namespace std;

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
Model::Model(const std::string& fileName, const std::string& filePath) :
    Asset(fileName, filePath)
{
}

Model::~Model()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
NodeSharedPtr
Model::GetNode()
{
    return mNode;
}

void Model::SetNode(NodeSharedPtr node)
{
    mNode = node;
}

void
Model::SetSampler(SamplerSharedPtr sampler)
{
    mSampler = sampler;
}

const Sampler *
Model::GetSampler() const
{
    return mSampler.get();
}

}
