#include <FalconEngine/Graphics/Scenes/Material.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/

FALCON_ENGINE_RTTI_IMPLEMENT(Material, Object);

Material::Material() :
    mAmbient(nullptr),
    mDiffuse(nullptr),
    mEmissive(nullptr),
    mSpecular(nullptr)
{
}

Material::~Material()
{
}

}
