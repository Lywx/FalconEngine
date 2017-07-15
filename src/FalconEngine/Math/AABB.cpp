#include <FalconEngine/Math/AABB.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
AABB::AABB(const Vector3f& position)
{
    Initialize(position);
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
AABB::Initialize(const Vector3f& position)
{
    mMax = position;
    mMin = position;
}

void
AABB::Extend(const Vector3f& position)
{
    if (position.x > mMax.x)
    {
        mMax.x = position.x;
    }

    if (position.x < mMin.x)
    {
        mMin.x = position.x;
    }

    if (position.y > mMax.y)
    {
        mMax.y = position.y;
    }

    if (position.y < mMin.y)
    {
        mMin.y = position.y;
    }

    if (position.z > mMax.z)
    {
        mMax.z = position.z;
    }

    if (position.z < mMin.z)
    {
        mMin.z = position.z;
    }
}

}
