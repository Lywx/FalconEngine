#pragma once

#include <FalconEngine/Graphics/GraphicsInclude.h>

#include <vector>

#include <FalconEngine/Graphics/Renderers/VisualTriangles.h>
#include <FalconEngine/Graphics/Renderers/Resources/IndexBuffer.h>
#include <FalconEngine/Graphics/Renderers/Resources/VertexBuffer.h>
#include <FalconEngine/Graphics/Scenes/Material.h>

namespace FalconEngine
{

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
