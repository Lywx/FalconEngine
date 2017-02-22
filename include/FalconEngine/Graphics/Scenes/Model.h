#pragma once

#include <FalconEngine/Graphics/GraphicsInclude.h>

#include <FalconEngine/Graphics/Renderers/Resources/Texture2d.h>
#include <FalconEngine/Graphics/Renderers/Resources/Sampler.h>
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
    void
    SetNode(NodeSharedPtr node)
    {
        mNode = node;
    }

    Node *
    GetNode()
    {
        return mNode.get();
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

    int
    GetTextureNum() const
    {
        return mTextures.size();
    }

    const Texture2d *
    GetTexture(int index) const
    {
        return mTextures[index];
    }

    void
    PushTexture(Texture2d *texture)
    {
        mTextures.push_back(texture);
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

    // NOTE(Wuxiang): The reason I use a vector of texture is that texture imported
    // from the model file might not be identical in the size, format, etc. The
    // heterogeneity would cause extra cost on texture array object so that it is
    // impossible to use texture array.

    std::vector<Texture2d *> mTextures;                                        // Model texture.
    SamplerSharedPtr         mSampler;                                         // Model texture sampler.
};

typedef std::shared_ptr<Model> ModelSharedPtr;
typedef std::unique_ptr<Model> ModelUniquePtr;

}
