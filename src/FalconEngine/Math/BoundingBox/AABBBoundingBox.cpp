#include <FalconEngine/Math/Bound/AABBBoundingBox.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
AABBBoundingBox::AABBBoundingBox(Vector3f position)
{
    Initialize(position);
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
AABBBoundingBox::Initialize(Vector3f position)
{
    mXmin = position.x;
    mXmax = position.x;
    mYmin = position.y;
    mYmax = position.y;
    mZmin = position.z;
    mZmax = position.z;
}

void
AABBBoundingBox::Update(Vector3f position)
{
    if (position.x > mXmax)
    {
        mXmax = position.x;
    }

    if (position.x < mXmin)
    {
        mXmin = position.x;
    }

    if (position.y > mYmax)
    {
        mYmax = position.y;
    }

    if (position.y < mYmin)
    {
        mYmin = position.y;
    }

    if (position.z > mZmax)
    {
        mZmax = position.z;
    }

    if (position.z < mZmin)
    {
        mZmin = position.z;
    }
}
}
