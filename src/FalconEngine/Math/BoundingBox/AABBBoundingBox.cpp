#include <FalconEngine/Math/Bound/AABBBoundingBox.h>

namespace FalconEngine
{

/************************************************************************/
/* Static Members                                                       */
/************************************************************************/
std::vector<Vector3f>
AABBBoundingBox::GetCubeModelPositionList()
{
    static auto sCubeModelXmax = 1.0f;
    static auto sCubeModelYmax = 1.0f;
    static auto sCubeModelZmin = 1.0f;
    static auto sCubeModelXmin = -1.0f;
    static auto sCubeModelYmin = -1.0f;
    static auto sCubeModelZmax = -1.0f;
    static std::vector<Vector3f> sCubeModelPositionList;
    if (sCubeModelPositionList.empty())
    {
        sCubeModelPositionList =
        {
            Vector3f(sCubeModelXmin, sCubeModelYmin, sCubeModelZmin), // triangle 1 Begin
            Vector3f(sCubeModelXmin, sCubeModelYmin, sCubeModelZmax),
            Vector3f(sCubeModelXmin, sCubeModelYmax, sCubeModelZmax), // triangle 1 End
            Vector3f(sCubeModelXmax, sCubeModelYmax, sCubeModelZmin), // triangle 2 Begin
            Vector3f(sCubeModelXmin, sCubeModelYmin, sCubeModelZmin),
            Vector3f(sCubeModelXmin, sCubeModelYmax, sCubeModelZmin), // triangle 2 End
            Vector3f(sCubeModelXmax, sCubeModelYmin, sCubeModelZmax),
            Vector3f(sCubeModelXmin, sCubeModelYmin, sCubeModelZmin),
            Vector3f(sCubeModelXmax, sCubeModelYmin, sCubeModelZmin),
            Vector3f(sCubeModelXmax, sCubeModelYmax, sCubeModelZmin),
            Vector3f(sCubeModelXmax, sCubeModelYmin, sCubeModelZmin),
            Vector3f(sCubeModelXmin, sCubeModelYmin, sCubeModelZmin),
            Vector3f(sCubeModelXmin, sCubeModelYmin, sCubeModelZmin),
            Vector3f(sCubeModelXmin, sCubeModelYmax, sCubeModelZmax),
            Vector3f(sCubeModelXmin, sCubeModelYmax, sCubeModelZmin),
            Vector3f(sCubeModelXmax, sCubeModelYmin, sCubeModelZmax),
            Vector3f(sCubeModelXmin, sCubeModelYmin, sCubeModelZmax),
            Vector3f(sCubeModelXmin, sCubeModelYmin, sCubeModelZmin),
            Vector3f(sCubeModelXmin, sCubeModelYmax, sCubeModelZmax),
            Vector3f(sCubeModelXmin, sCubeModelYmin, sCubeModelZmax),
            Vector3f(sCubeModelXmax, sCubeModelYmin, sCubeModelZmax),
            Vector3f(sCubeModelXmax, sCubeModelYmax, sCubeModelZmax),
            Vector3f(sCubeModelXmax, sCubeModelYmin, sCubeModelZmin),
            Vector3f(sCubeModelXmax, sCubeModelYmax, sCubeModelZmin),
            Vector3f(sCubeModelXmax, sCubeModelYmin, sCubeModelZmin),
            Vector3f(sCubeModelXmax, sCubeModelYmax, sCubeModelZmax),
            Vector3f(sCubeModelXmax, sCubeModelYmin, sCubeModelZmax),
            Vector3f(sCubeModelXmax, sCubeModelYmax, sCubeModelZmax),
            Vector3f(sCubeModelXmax, sCubeModelYmax, sCubeModelZmin),
            Vector3f(sCubeModelXmin, sCubeModelYmax, sCubeModelZmin),
            Vector3f(sCubeModelXmax, sCubeModelYmax, sCubeModelZmax),
            Vector3f(sCubeModelXmin, sCubeModelYmax, sCubeModelZmin),
            Vector3f(sCubeModelXmin, sCubeModelYmax, sCubeModelZmax),
            Vector3f(sCubeModelXmax, sCubeModelYmax, sCubeModelZmax),
            Vector3f(sCubeModelXmin, sCubeModelYmax, sCubeModelZmax),
            Vector3f(sCubeModelXmax, sCubeModelYmin, sCubeModelZmax)
        };
    }

    return sCubeModelPositionList;
}

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
AABBBoundingBox::AABBBoundingBox(Vector3f position)
{
    InitializePosition(position);
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
Matrix4f
AABBBoundingBox::GetCubeModelPositionTransform() const
{
    auto center = (Vector3f(mXmax, mYmax, mZmax) - Vector3f(mXmin, mYmin, mZmin)) / 2.0f;
    auto scaling = Matrix4f::CreateScale(center.x, center.y, center.z);
    auto translation = Matrix4f::CreateTranslation(center);

    // NOTE(Wuxiang): Scale (-1, -1, -1), (1, 1, 1) cube first, then translate
    // to correct model position.
    return translation * scaling;
}

int
AABBBoundingBox::GetModelPositionNum() const
{
    return 36;
}

std::vector<Vector3f>
AABBBoundingBox::GetModelPositionList() const
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
AABBBoundingBox::InitializePosition(Vector3f position)
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
AABBBoundingBox::UpdatePosition(Vector3f position)
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
