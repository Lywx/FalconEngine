#pragma once

#include <FalconEngine/Graphics/SceneInclude.h>

#include <vector>

#include <FalconEngine/Graphics/Renderer/VisualTriangles.h>

namespace FalconEngine
{

class Material;
using MaterialSharedPtr = std::shared_ptr<Material>;
class Mesh : public VisualTriangles
{
    FALCON_ENGINE_RTTI_DECLARE;

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    Mesh(VertexFormatSharedPtr vertexFormat, VertexGroupSharedPtr vertexGroup, IndexBufferSharedPtr indexBuffer);
    virtual ~Mesh();

    void
    SetMaterial(MaterialSharedPtr material)
    {
        mMaterial = material;
    }

    const Material *
    GetMaterial() const
    {
        return mMaterial.get();
    }

protected:
    MaterialSharedPtr mMaterial;
};

typedef std::shared_ptr<Mesh> MeshSharedPtr;

}
