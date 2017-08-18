#include <FalconEngine/Graphics/Renderer/Scene/Mesh.h>

#include <FalconEngine/Content/AssetManager.h>
#include <FalconEngine/Graphics/Renderer/PrimitiveTriangles.h>
#include <FalconEngine/Graphics/Renderer/Scene/Model.h>

using namespace std;

namespace FalconEngine
{

FALCON_ENGINE_RTTI_IMPLEMENT(Mesh, Object);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
Mesh::Mesh(std::shared_ptr<Primitive> primitives, std::shared_ptr<Material> material) :
    mMaterial(material),
    mPrimitive(primitives)
{
}

Mesh::Mesh() :
    mMaterial(),
    mPrimitive()
{
}

Mesh::~Mesh()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
const Aabb *
Mesh::GetAabb() const
{
    return mPrimitive->GetAabb();
}

const Material *
Mesh::GetMaterial() const
{
    return mMaterial.get();
}

Material *
Mesh::GetMaterial()
{
    return mMaterial.get();
}

const std::shared_ptr<Material>&
Mesh::GetMaterialSp()
{
    return mMaterial;
}

void
Mesh::SetMaterial(std::shared_ptr<Material> material)
{
    FALCON_ENGINE_CHECK_NULLPTR(material);

    mMaterial = material;
}

const Primitive *
Mesh::GetPrimitive() const
{
    return mPrimitive.get();
}

std::shared_ptr<Primitive>
Mesh::GetPrimitive()
{
    return mPrimitive;
}

/************************************************************************/
/* Deep and Shallow Copy                                                */
/************************************************************************/
void
Mesh::CopyTo(Mesh *lhs) const
{
    lhs->mMaterial  = mMaterial;
    lhs->mPrimitive = mPrimitive;
}

Mesh *
Mesh::GetClone() const
{
    auto clone = new Mesh();
    CopyTo(clone);
    return clone;
}

}
