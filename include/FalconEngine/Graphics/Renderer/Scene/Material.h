#pragma once

#include <FalconEngine/Graphics/SceneInclude.h>

namespace FalconEngine
{

class Texture2d;

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
    const Texture2d *mAmbient;
    const Texture2d *mDiffuse;
    const Texture2d *mEmissive;
    const Texture2d *mSpecular;
    const Texture2d *mShininess;
};

}
