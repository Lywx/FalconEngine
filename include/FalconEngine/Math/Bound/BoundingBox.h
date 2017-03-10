#pragma once

#include <FalconEngine/MathInclude.h>

#include <vector>

#include <FalconEngine/Math/Vector3.h>

namespace FalconEngine
{

class BoundingBox
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
