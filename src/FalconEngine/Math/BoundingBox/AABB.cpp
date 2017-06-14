#include <FalconEngine/Math/Bound/AABB.h>

namespace FalconEngine
{

/************************************************************************/
/* Static Members                                                       */
/************************************************************************/
std::vector<Vector3f>
CreateLineMesh()
{
    static auto sCubeModelXmax = 1.0f;
    static auto sCubeModelYmax = 1.0f;
    static auto sCubeModelZmin = 1.0f;
    static auto sCubeModelXmin = -1.0f;
    static auto sCubeModelYmin = -1.0f;
    static auto sCubeModelZmax = -1.0f;

    auto cubeLineMeshModelPositionList =
    {
        Vector3f(sCubeModelXmin, sCubeModelYmin, sCubeModelZmin), // line 1
        Vector3f(sCubeModelXmax, sCubeModelYmin, sCubeModelZmin),

        Vector3f(sCubeModelXmin, sCubeModelYmax, sCubeModelZmin), // line 2
        Vector3f(sCubeModelXmax, sCubeModelYmax, sCubeModelZmin),

        Vector3f(sCubeModelXmin, sCubeModelYmin, sCubeModelZmax), // line 3
        Vector3f(sCubeModelXmax, sCubeModelYmin, sCubeModelZmax),

        Vector3f(sCubeModelXmin, sCubeModelYmax, sCubeModelZmax), // line 4
        Vector3f(sCubeModelXmax, sCubeModelYmax, sCubeModelZmax),

        Vector3f(sCubeModelXmin, sCubeModelYmin, sCubeModelZmin), // line 1
        Vector3f(sCubeModelXmin, sCubeModelYmax, sCubeModelZmin),

        Vector3f(sCubeModelXmax, sCubeModelYmin, sCubeModelZmin), // line 2
        Vector3f(sCubeModelXmax, sCubeModelYmax, sCubeModelZmin),

        Vector3f(sCubeModelXmin, sCubeModelYmin, sCubeModelZmax), // line 3
        Vector3f(sCubeModelXmin, sCubeModelYmax, sCubeModelZmax),

        Vector3f(sCubeModelXmax, sCubeModelYmin, sCubeModelZmax), // line 4
        Vector3f(sCubeModelXmax, sCubeModelYmax, sCubeModelZmax),

        Vector3f(sCubeModelXmin, sCubeModelYmin, sCubeModelZmin), // line 1
        Vector3f(sCubeModelXmin, sCubeModelYmin, sCubeModelZmax),

        Vector3f(sCubeModelXmin, sCubeModelYmax, sCubeModelZmin), // line 2
        Vector3f(sCubeModelXmin, sCubeModelYmax, sCubeModelZmax),

        Vector3f(sCubeModelXmax, sCubeModelYmin, sCubeModelZmin), // line 3
        Vector3f(sCubeModelXmax, sCubeModelYmin, sCubeModelZmax),

        Vector3f(sCubeModelXmax, sCubeModelYmax, sCubeModelZmin), // line 4
        Vector3f(sCubeModelXmax, sCubeModelYmax, sCubeModelZmax),
    };

    return cubeLineMeshModelPositionList;
}

std::vector<Vector3f>
AABB::GetUnitPositionList()
{
    static std::vector<Vector3f> sUnitModelPositionList = CreateLineMesh();;
    return sUnitModelPositionList;
}

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
AABB::AABB(Vector3f position)
{
    InitializePosition(position);
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
Matrix4f
CreateModelPositionTransform(float xmax, float ymax, float zmax, float xmin, float ymin, float zmin)
{
    auto maxCorner = Vector3f(xmax, ymax, zmax);
    auto minCorner = Vector3f(xmin, ymin, zmin);
    auto halfSize = (maxCorner - minCorner) / 2.0f;

    auto scaling     = Matrix4f::CreateScale(halfSize.x, halfSize.y, halfSize.z);
    auto translation = Matrix4f::CreateTranslation(minCorner + halfSize);

    // NOTE(Wuxiang): Scale (-1, -1, -1), (1, 1, 1) cube first, then translate
    // to correct model position.
    return translation * scaling;
}

Matrix4f
AABB::GetModelPositionTransform() const
{
    const static Matrix4f sModelTransform = CreateModelPositionTransform(mXmax, mYmax, mZmax, mXmin, mYmin, mZmin);
    return sModelTransform;
}

int
AABB::GetModelPositionNum() const
{
    return 24;
}

std::vector<Vector3f>
AABB::GetModelPositionList() const
{
    if (!mInitialized)
    {
        FALCON_ENGINE_THROW_RUNTIME_EXCEPTION("Bounding box is not properly initialized.");
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
AABB::InitializePosition(Vector3f position)
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
AABB::UpdatePosition(Vector3f position)
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
