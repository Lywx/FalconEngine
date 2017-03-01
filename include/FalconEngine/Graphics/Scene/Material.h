#pragma once

#include <FalconEngine/Graphics/SceneInclude.h>

#include <memory>

namespace FalconEngine
{

class Texture2d;
using Texture2dSharedPtr = std::shared_ptr<Texture2d>;

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
    Texture2dSharedPtr mAmbient;
    Texture2dSharedPtr mDiffuse;
    Texture2dSharedPtr mEmissive;
    Texture2dSharedPtr mSpecular;
    Texture2dSharedPtr mShininess;
};

}
