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
Mesh::Mesh(PrimitiveTrianglesSharedPtr primitives) :
    Visual(primitives)
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
    mMaterial = material;
}
}
