#pragma once

#include <FalconEngine/MathInclude.h>
#include <FalconEngine/Math/Bound/BoundingBox.h>
#include <FalconEngine/Math/Vector3.h>

namespace FalconEngine
{

class AABBBoundingBox sealed : public BoundingBox
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    explicit AABBBoundingBox(Vector3f position);
    virtual ~AABBBoundingBox() = default;

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    void
    Update(Vector3f position);

private:
    /************************************************************************/
    /* Private Members                                                      */
    /************************************************************************/
    void
    Initialize(Vector3f position);

public:
    float mXmax;
    float mXmin;

    float mYmax;
    float mYmin;

    float mZmax;
    float mZmin;
};

}
