#pragma once

#include <FalconEngine/Graphics/Common.h>

#include <FalconEngine/Math/Matrix4.h>
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
    // @summary Return default right-handed coordinate system, where Y points
    // upward, Z points inward, X points rightward.
    static Coordinate GetStandard()
    {
        static const Coordinate sGame = Coordinate(Vector3f::UnitX,
                                        Vector3f::UnitY,
                                        Vector3f::UnitZ);

        return sGame;
    }

    // @summary Return mathematical right-handed coordinate system, where Z points
    // upward, X points inward, Y points rightward. This representation is typically
    // seen in math books.
    static Coordinate GetMathematical()
    {
        static const Coordinate sMath = Coordinate(Vector3f::UnitY,
                                        Vector3f::UnitZ,
                                        Vector3f::UnitX);
        return sMath;
    }

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    Coordinate(Vector3f axisX,
               Vector3f axisY,
               Vector3f axisZ);

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    Vector3f
    GetAxisX() const;

    Vector3f
    GetAxisY() const;

    Vector3f
    GetAxisZ() const;

    // @summary Coordinate transform from standard basis to given basis.
    const Matrix4f&
    GetTransform() const;

    // @summary Inverse transform from given basis to standard basis.
    const Matrix4f&
    GetInverse() const;

private:
    Matrix4f mTransform; // Coordinate transform from standard basis to given basis.
    Matrix4f mInverse;   // Inverse transform from given basis to standard basis.
};

}
