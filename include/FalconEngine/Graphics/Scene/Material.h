#pragma once

#include <FalconEngine/Graphics/SceneInclude.h>

#include <memory>

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
    Texture2d *mAmbient;
    Texture2d *mDiffuse;
    Texture2d *mEmissive;
    Texture2d *mSpecular;
    Texture2d *mShininess;
};

}
