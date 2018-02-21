#pragma once

#include <FalconEngine/Core/Macro.h>

// NOTE(Wuxiang): Disable warning C4201: nonstandard extension used : nameless struct/union.
#pragma warning(disable : 4201)
#include <glm/matrix.hpp>
#pragma warning(default : 4201)

namespace FalconEngine
{


class Vector3f;
class Matrix4f;


// @summary 3x3 matrix in column major format:
//
// (0.0, 1.0, 2.0, 3.0,
//  0.1, 1.1, 2.1, 3.1,
//  0.2, 1.2, 2.2, 3.2,
//  0.3, 1.3, 2.3, 3.3)
#pragma pack(push, 1)
FALCON_ENGINE_CLASS_BEGIN Matrix3f final:
public glm::mat3
{
public:
    /************************************************************************/
    /* Static Members                                                       */
    /************************************************************************/
    static Matrix3f Zero;
    static Matrix3f Identity;

    static Matrix3f Inverse(const Matrix3f & mat);
    static Matrix3f Transpose(const Matrix3f & mat);

    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    Matrix3f();
    Matrix3f(const glm::vec3 & v0, const glm::vec3 & v1, const glm::vec3 & v2);
    Matrix3f(
        const float & x0, const float & y0, const float & z0,
        const float & x1, const float & y1, const float & z1,
        const float & x2, const float & y2, const float & z2);

    virtual ~Matrix3f();

    // Explicit Conversion
    explicit Matrix3f(const Matrix4f & m);

    // Implicit Conversion
    Matrix3f(const glm::mat3 & m);
    operator glm::mat3();
};
#pragma pack(pop)
FALCON_ENGINE_CLASS_END

}
