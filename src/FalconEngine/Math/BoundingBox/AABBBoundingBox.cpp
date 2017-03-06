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
int
AABBBoundingBox::GetPositionNum() const
{
    return 36;
}

std::vector<Vector3f>
AABBBoundingBox::GetPositionList() const
{
    if (!mInitialized)
    {
        FALCON_ENGINE_THROW_EXCEPTION("Bounding box is not properly initialized.");
    }
    else if (mInitialized && !mModelPositionInitialized)
    {
        // Modified from http://www.opengl-tutorial.org/beginners-tutorials/tutorial-4-a-colored-cube/
        mModelPosition =
        {
            Vector3f(mXmin, mYmin, mZmin),  // triangle 1 Begin
            Vector3f(mXmin, mYmin, mZmax),
            Vector3f(mXmin, mYmax, mZmax),  // triangle 1 End
            Vector3f(mXmax, mYmax, mZmin),  // triangle 2 Begin
            Vector3f(mXmin, mYmin, mZmin),
            Vector3f(mXmin, mYmax, mZmin),  // triangle 2 End
            Vector3f(mXmax, mYmin, mZmax),
            Vector3f(mXmin, mYmin, mZmin),
            Vector3f(mXmax, mYmin, mZmin),
            Vector3f(mXmax, mYmax, mZmin),
            Vector3f(mXmax, mYmin, mZmin),
            Vector3f(mXmin, mYmin, mZmin),
            Vector3f(mXmin, mYmin, mZmin),
            Vector3f(mXmin, mYmax, mZmax),
            Vector3f(mXmin, mYmax, mZmin),
            Vector3f(mXmax, mYmin, mZmax),
            Vector3f(mXmin, mYmin, mZmax),
            Vector3f(mXmin, mYmin, mZmin),
            Vector3f(mXmin, mYmax, mZmax),
            Vector3f(mXmin, mYmin, mZmax),
            Vector3f(mXmax, mYmin, mZmax),
            Vector3f(mXmax, mYmax, mZmax),
            Vector3f(mXmax, mYmin, mZmin),
            Vector3f(mXmax, mYmax, mZmin),
            Vector3f(mXmax, mYmin, mZmin),
            Vector3f(mXmax, mYmax, mZmax),
            Vector3f(mXmax, mYmin, mZmax),
            Vector3f(mXmax, mYmax, mZmax),
            Vector3f(mXmax, mYmax, mZmin),
            Vector3f(mXmin, mYmax, mZmin),
            Vector3f(mXmax, mYmax, mZmax),
            Vector3f(mXmin, mYmax, mZmin),
            Vector3f(mXmin, mYmax, mZmax),
            Vector3f(mXmax, mYmax, mZmax),
            Vector3f(mXmin, mYmax, mZmax),
            Vector3f(mXmax, mYmin, mZmax)
        };

        mModelPositionInitialized = true;
    }

    return mModelPosition;
}

void
AABBBoundingBox::Initialize(Vector3f position)
{
    mXmin = position.x;
    mXmax = position.x;
    mYmin = position.y;
    mYmax = position.y;
    mZmin = position.z;
    mZmax = position.z;

    mInitialized = true;
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
