#pragma once

#include <FalconEngine/Core/Macro.h>

#include <FalconEngine/Graphics/Renderer/Primitive.h>

namespace FalconEngine
{

class Aabb;

class IndexBuffer;

class Material;

class VertexBuffer;
class VertexFormat;
class VertexGroup;

// @summary Represents bundle of geometry and all the metadata used in rendering.
FALCON_ENGINE_CLASS_BEGIN Mesh :
public Object
{
    FALCON_ENGINE_RTTI_DECLARE;

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    explicit Mesh(std::shared_ptr<Primitive> primitive, std::shared_ptr<Material> material);
    virtual ~Mesh();

protected:
    Mesh();

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    const Aabb *
    GetAabb() const;

    const Material *
    GetMaterial() const;

    Material *
    GetMaterial();

    const std::shared_ptr<Material>&
    GetMaterialSp();

    void
    SetMaterial(std::shared_ptr<Material> material);

    const Primitive *
    GetPrimitive() const;

    std::shared_ptr<Primitive>
    GetPrimitive();

    /************************************************************************/
    /* Deep and Shallow Copy                                                */
    /************************************************************************/
    virtual void
    CopyTo(Mesh * lhs) const;

    virtual Mesh *
    GetClone() const;

protected:
    std::shared_ptr<Material> mMaterial;
    std::shared_ptr<Primitive> mPrimitive;
};
FALCON_ENGINE_CLASS_END

}
