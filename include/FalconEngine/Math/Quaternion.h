#pragma once

#include <glm/gtc/quaternion.hpp>

#include "Vector3f.h"

namespace FalconEngine {

// Forward declaration for circular dependency
class Matrix4f;
class Quaternion : public glm::quat
{
public:
    static Quaternion Identity;

    static Quaternion FromAxisAngle(const Vector3f& axis, float angle);;

    // NEW
    // static Quaternion FromEulerAngle(const Vector3& axis, float angle);;

    static Quaternion FromRotationMatrix(const Matrix4f& rotation);

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