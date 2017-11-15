#pragma once

#include <FalconEngine/Core/Common.h>

namespace FalconEngine
{

class FALCON_ENGINE_API Window
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    Window();
    Window(int width, int height, float near, float far);

public:
    int   mWidth;
    int   mHeight;
    float mNear;
    float mFar;
};

}