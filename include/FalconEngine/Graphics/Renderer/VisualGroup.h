#pragma once

#include <FalconEngine/Graphics/Header.h>

#include <vector>

namespace FalconEngine
{

class Spatial;

    class Visual;
class FALCON_ENGINE_API VisualGroup final
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    VisualGroup();
    ~VisualGroup();

public:
    std::vector<std::shared_ptr<Spatial>> mVisible;
};

}
