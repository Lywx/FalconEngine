#pragma once

#include <FalconEngine/Core/Common.h>

#include <vector>

namespace FalconEngine
{

class Spatial;
class Visual;

// NEW(Wuxiang): Implement frustum culling.
// @summary Represents hierarchical structure of part of a scene graph for efficient rendering.
class FALCON_ENGINE_API SpatialGroup final
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    SpatialGroup();
    ~SpatialGroup();

public:
    std::vector<std::shared_ptr<Spatial>> mVisible;
};

}
