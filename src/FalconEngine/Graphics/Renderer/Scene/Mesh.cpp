#include <FalconEngine/Graphics/Renderer/Scene/Mesh.h>

#include <FalconEngine/Content/AssetManager.h>
#include <FalconEngine/Graphics/Renderer/PrimitiveTriangles.h>
#include <FalconEngine/Graphics/Renderer/Scene/Model.h>

using namespace std;

namespace FalconEngine
{

FALCON_ENGINE_RTTI_IMPLEMENT(Mesh, Visual);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
Mesh::Mesh(PrimitiveTrianglesSharedPtr primitives, MaterialSharedPtr material) :
    Visual(primitives),
    mMaterial(material)
{
}

Mesh::Mesh() :
    mMaterial()
{
}

Mesh::~Mesh()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
const Material *
Mesh::GetMaterial() const
{
    return mMaterial.get();
}

void
Mesh::SetMaterial(MaterialSharedPtr material)
{
    FALCON_ENGINE_CHECK_NULLPTR(material);

    mMaterial = material;
}

/************************************************************************/
/* Deep and Shallow Copy                                                */
/************************************************************************/
void
Mesh::CopyTo(Mesh *lhs) const
{
    Visual::CopyTo(lhs);

    lhs->mMaterial = mMaterial;
}

Mesh *
Mesh::GetClone() const
{
    auto clone = new Mesh();
    CopyTo(clone);
    return clone;
}

}
