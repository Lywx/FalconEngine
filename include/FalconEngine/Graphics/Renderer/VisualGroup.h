#pragma once

#include <FalconEngine/Graphics/Header.h>

#include <vector>

namespace FalconEngine
{

class Spatial;
using SpatialSharedPtr = std::shared_ptr<Spatial>;

class Visual;
class FALCON_ENGINE_ITEM_GRAPHICS VisualGroup final
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    VisualGroup();
    ~VisualGroup();

public:
    std::vector<SpatialSharedPtr> mVisible;
};

}
