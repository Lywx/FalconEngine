#include <FalconEngine/Math/Aabb.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
Aabb::Aabb(const Vector3f& position)
{
    Initialize(position);
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
Aabb::Initialize(const Vector3f& position)
{
    mMax = position;
    mMin = position;
}

void
Aabb::Extend(const Vector3f& position)
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
