#pragma once

#include <FalconEngine/GraphicsInclude.h>

#include <vector>

namespace FalconEngine
{

class Spatial;
using SpatialSharedPtr = std::shared_ptr<Spatial>;

class Visual;
class VisualGroup sealed
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
