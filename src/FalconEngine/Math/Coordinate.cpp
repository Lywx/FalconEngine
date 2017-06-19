#include <FalconEngine/Math/Coordinate.h>

namespace FalconEngine
{

/************************************************************************/
/* Static Members                                                       */
/************************************************************************/
const Coordinate
Coordinate::Math = Coordinate(Vector3f::UnitY,
                              Vector3f::UnitZ,
                              Vector3f::UnitX);

const Coordinate
Coordinate::Game = Coordinate(Vector3f::UnitX,
                              Vector3f::UnitY,
                              Vector3f::UnitZ);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
Coordinate::Coordinate(Vector3f xAxis, Vector3f yAxis, Vector3f zAxis):
    mXAxis(xAxis),
    mYAxis(yAxis),
    mZAxis(zAxis)
{
}

}
