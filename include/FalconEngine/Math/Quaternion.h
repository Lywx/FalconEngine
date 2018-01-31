#pragma once

#include <FalconEngine/Core/Macro.h>

// NOTE(Wuxiang): Disable warning C4201: nonstandard extension used : nameless struct/union.
#pragma warning(disable : 4201)

#include <glm/gtc/quaternion.hpp>

#pragma warning(default : 4201)

#include <FalconEngine/Math/Vector3.h>

namespace FalconEngine
{

// Forward declaration for circular dependency
class Matrix4f;
class FALCON_ENGINE_API Quaternion : public glm::quat
{
public:
    /************************************************************************/
    /* Static Members                                                       */
    /************************************************************************/
    static const Quaternion Identity;

    static Quaternion
    CreateFromAxisAngle(const Vector3f& axis, float angle);;

    // NEW(Wuxiang): Implement conversion from euler angle.
    // static Quaternion
    // CreateFromEulerAngle(const Vector3& axis, float angle);;

    static Quaternion
    CreateFromRotationMatrix(const Matrix4f& rotation);

    static Quaternion
    Normalize(const Quaternion& quat);

    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    Quaternion();
    Quaternion(const float w,
               const float x,
               const float y,
               const float z);

    // Implicit Conversion
    Quaternion(const glm::quat quat);

    // Explicit Conversion
    explicit operator glm::quat() const;
};

}