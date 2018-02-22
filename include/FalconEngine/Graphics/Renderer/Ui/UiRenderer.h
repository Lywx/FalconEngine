#pragma once

#include <FalconEngine/Core/Macro.h>

#include <limits>
#include <map>
#include <string>
#include <vector>

namespace FalconEngine
{

class Renderer;

// @summary The font renderer is the class you would call to draw a string on
// the screen.
FALCON_ENGINE_CLASS_BEGIN UiRenderer final
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    UiRenderer();
    ~UiRenderer();

public:
    /************************************************************************/
    /* Rendering Engine API                                                 */
    /************************************************************************/
    void
    Destroy();

};
FALCON_ENGINE_CLASS_END

}
