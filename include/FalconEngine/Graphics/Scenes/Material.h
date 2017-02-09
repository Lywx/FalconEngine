#pragma once

#include <FalconEngine/Graphics/GraphicsInclude.h>

namespace FalconEngine
{

class Material : public Object
{
    FALCON_ENGINE_RTTI_DECLARE;

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    Material ();
    virtual ~Material ();

public:
    Color mAmbient;
    Color mDiffuse;
    Color mEmissive;
    Color mSpecular;
};

}
