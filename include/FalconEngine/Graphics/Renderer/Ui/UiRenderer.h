#pragma once

#include <FalconEngine/Graphics/Common.h>

#include <limits>
#include <map>
#include <string>
#include <vector>

namespace FalconEngine
{

class Renderer;

// @summary The font renderer is the class you would call to draw a string on
// the screen.
#pragma warning(disable: 4251)
class FALCON_ENGINE_API UiRenderer final
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    UiRenderer();
    ~UiRenderer();

public:
};
#pragma warning(default: 4251)

}
