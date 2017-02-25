#pragma once

#include <FalconEngine/Graphics/GraphicsInclude.h>

#include <memory>

namespace FalconEngine
{

class Texture;
class Material : public Object
{
    FALCON_ENGINE_RTTI_DECLARE;

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    Material();
    virtual ~Material ();

public:
    const Texture *mAmbient;
    const Texture *mDiffuse;
    const Texture *mEmissive;
    const Texture *mSpecular;
    const Texture *mShininess;
};

using MaterialSharedPtr = std::shared_ptr<Material>;

}
