#pragma once

#include <FalconEngine/Graphics/SceneInclude.h>
#include <FalconEngine/Graphics/Renderer/Visual.h>

namespace FalconEngine
{

class IndexBuffer;
using IndexBufferSharedPtr = std::shared_ptr<IndexBuffer>;

class Material;
using MaterialSharedPtr = std::shared_ptr<Material>;

class PrimitiveTriangles;
using PrimitiveTrianglesSharedPtr = std::shared_ptr<PrimitiveTriangles>;

class VertexBuffer;
using VertexBufferSharedPtr = std::shared_ptr<VertexBuffer>;

class VertexFormat;
using VertexFormatSharedPtr = std::shared_ptr<VertexFormat>;

class VertexGroup;
using VertexGroupSharedPtr = std::shared_ptr<VertexGroup>;

class Mesh : public Visual
{
    FALCON_ENGINE_RTTI_DECLARE;

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    explicit Mesh(PrimitiveTrianglesSharedPtr primitive);
    virtual ~Mesh();

    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    const Material *
    GetMaterial() const;

    void
    SetMaterial(MaterialSharedPtr material);

protected:
    MaterialSharedPtr mMaterial;
};

}
