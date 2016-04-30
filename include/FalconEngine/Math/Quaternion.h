#pragma once

#include <glm/gtc/quaternion.hpp>

#include "Vector3.h"

namespace FalconEngine {
namespace Math {

// Forward declaration for circular dependency
struct Matrix;

struct Quaternion : glm::quat
{
    static Quaternion Identity;

    static Quaternion FromAxisAngle(const Vector3& axis, float angle);;

    // NEW
    // static Quaternion FromEulerAngle(const Vector3& axis, float angle);;

    static Quaternion FromRotationMatrix(const Matrix& rotation);

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
}