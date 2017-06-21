#include <FalconEngine/Math/Coordinate.h>
#include <FalconEngine/Math/Vector4.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
Coordinate::Coordinate(Vector3f axisX,
                       Vector3f axisY,
                       Vector3f axisZ) :
    mTransform(Matrix4f::Identity)
{
    mTransform[0][0] = axisX[0];
    mTransform[0][1] = axisX[1];
    mTransform[0][2] = axisX[2];

    mTransform[1][0] = axisY[0];
    mTransform[1][1] = axisY[1];
    mTransform[1][2] = axisY[2];

    mTransform[2][0] = axisZ[0];
    mTransform[2][1] = axisZ[1];
    mTransform[2][2] = axisZ[2];

    mInverse = Matrix4f::Inverse(mTransform);
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
Vector3f
Coordinate::GetAxisX() const
{
    return Vector3f(mTransform[0][0], mTransform[0][1], mTransform[0][2]);
}

Vector3f
Coordinate::GetAxisY() const
{
    return Vector3f(mTransform[1][0], mTransform[1][1], mTransform[1][2]);
}

Vector3f
Coordinate::GetAxisZ() const
{
    return Vector3f(mTransform[2][0], mTransform[2][1], mTransform[2][2]);
}

const Matrix4f&
Coordinate::GetTransform() const
{
    return mTransform;
}

const Matrix4f&
Coordinate::GetInverse() const
{
    return mInverse;
}

}
