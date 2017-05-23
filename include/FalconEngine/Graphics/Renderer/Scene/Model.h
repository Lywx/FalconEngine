#pragma once

#include <FalconEngine/Graphics/Header.h>

#include <vector>

#include <FalconEngine/Content/Asset.h>
#include <FalconEngine/Math/Vector2.h>
#include <FalconEngine/Math/Vector3.h>

namespace FalconEngine
{

class Sampler;

class Node;

using ModelIndex = int;

#pragma pack(push, 1)
class FALCON_ENGINE_API ModelVertex
{
public:
    Vector3f mPosition;
    Vector3f mNormal;
    Vector2f mTexCoord;
};
#pragma pack(pop)

#pragma warning(disable: 4251)
class FALCON_ENGINE_API Model : public Asset
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    Model(const std::string& fileName, const std::string& filePath);
    virtual ~Model();

public:
    const Node *
    GetNode() const;

    std::shared_ptr<Node>
    GetNode();

    void
    SetNode(std::shared_ptr<Node> node);

    void
    SetSampler(std::shared_ptr<Sampler> sampler);

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
    std::shared_ptr<Node> mNode;                                            // Model root node.
    std::shared_ptr<Sampler> mSampler;                                         // Model texture sampler.
};
#pragma warning(default: 4251)

}
