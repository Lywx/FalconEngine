#pragma once

#include <glm/gtc/quaternion.hpp>

#include <FalconEngine/Math/Vector3.h>

namespace FalconEngine
{

// Forward declaration for circular dependency
class Matrix4f;
class Quaternion : public glm::quat
{
public:
    /************************************************************************/
    /* Static Members                                                       */
    /************************************************************************/
    static Quaternion Identity;
    static Quaternion CreateFromAxisAngle(const Vector3f& axis, float angle);;

    // TODO(Wuxiang)
    // static Quaternion CreateFromEulerAngle(const Vector3& axis, float angle);;

    static Quaternion CreateFromRotationMatrix(const Matrix4f& rotation);

    Quaternion() : glm::quat() { }
    Quaternion
    (
        const float w,
        const float x,
        const float y,
        const float z
    ) : glm::quat(w, x, y, z) {}

    // Implicit Conversion
    Quaternion(const glm::quat quat) : glm::quat(quat) {}
};

}