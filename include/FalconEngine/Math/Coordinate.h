#pragma once

#include <FalconEngine/Graphics/Header.h>

#include <FalconEngine/Math/Vector3.h>

namespace FalconEngine
{

// @summary Represents a coordinate system.
class FALCON_ENGINE_API Coordinate
{
public:
    /************************************************************************/
    /* Static Members                                                       */
    /************************************************************************/
    static const Coordinate Game;
    static const Coordinate Math;

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    Coordinate(Vector3f xAxis,
               Vector3f yAxis,
               Vector3f zAxis);

public:
    Vector3f mXAxis;
    Vector3f mYAxis;
    Vector3f mZAxis;
};

}
