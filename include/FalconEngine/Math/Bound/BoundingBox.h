#pragma once

#include <FalconEngine/Math/Header.h>

#include <vector>

#include <FalconEngine/Math/Vector3.h>

namespace FalconEngine
{

class FALCON_ENGINE_API BoundingBox
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    BoundingBox();
    virtual ~BoundingBox();

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    virtual int
    GetModelPositionNum() const = 0;

    virtual std::vector<Vector3f>
    GetModelPositionList() const = 0;
};

}
