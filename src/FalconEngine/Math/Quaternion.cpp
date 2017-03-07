#include <FalconEngine/Math/Quaternion.h>
#include <FalconEngine/Math/Matrix4.h>
#include "FalconEngine/CoreInclude.h"

namespace FalconEngine
{

Quaternion Quaternion::Identity = Quaternion(1, 0, 0, 0);

Quaternion
Quaternion::CreateFromAxisAngle(const Vector3f& axis, float angle)
{
    const float sin_angle = sinf(angle * 0.5f);
    return Quaternion(cosf(angle * 0.5f), axis.x * sin_angle, axis.y * sin_angle, axis.z * sin_angle);
}

Quaternion
Quaternion::CreateFromRotationMatrix(const Matrix4f& rotation)
{
    Quaternion result;

    // Before P284 (8.21), Fletcher Dunn, Ian Parberry 3D Math Primer for Graphics and Game Development, 2nd, 2011
    auto equation_4w_2_minus_1 = rotation[0][0] + rotation[1][1] + rotation[2][2];

    // (8.21)
    auto equation_4x_2_minus_1 = rotation[0][0] - rotation[1][1] - rotation[2][2];

    // (8.22)
    auto equation_4y_2_minus_1 = rotation[1][1] - rotation[0][0] - rotation[2][2];

    // (8.23)
    auto equation_4z_2_minus_1 = rotation[2][2] - rotation[0][0] - rotation[1][1];

    // Biggest value form in w, x, y, z
    auto equation_4v_2_minus_1_biggest = equation_4w_2_minus_1;
    int equation_4v_2_minus_1_biggest_index = 0;

    if (equation_4x_2_minus_1 > equation_4v_2_minus_1_biggest)
    {
        equation_4v_2_minus_1_biggest = equation_4x_2_minus_1;
        equation_4v_2_minus_1_biggest_index = 1;
    }

    if (equation_4y_2_minus_1 > equation_4v_2_minus_1_biggest)
    {
        equation_4v_2_minus_1_biggest = equation_4y_2_minus_1;
        equation_4v_2_minus_1_biggest_index = 2;
    }

    if (equation_4z_2_minus_1 > equation_4v_2_minus_1_biggest)
    {
        equation_4v_2_minus_1_biggest = equation_4z_2_minus_1;
        equation_4v_2_minus_1_biggest_index = 3;
    }

    // Max of x, y, z, w
    auto equation_wxyz_biggest = sqrt(equation_4v_2_minus_1_biggest + 1.0f) * 0.5f;
    auto equation_1_over_4_wxyz_biggest = 0.25f / equation_wxyz_biggest;

    switch (equation_4v_2_minus_1_biggest_index)
    {
    case 0:
        result.w = equation_wxyz_biggest;
        result.x = (rotation[2][1] - rotation[1][2]) * equation_1_over_4_wxyz_biggest;
        result.y = (rotation[0][2] - rotation[2][0]) * equation_1_over_4_wxyz_biggest;
        result.z = (rotation[1][0] - rotation[0][1]) * equation_1_over_4_wxyz_biggest;

        break;

    case 1:
        result.x = equation_wxyz_biggest;
        result.w = (rotation[2][1] - rotation[1][2]) * equation_1_over_4_wxyz_biggest;
        result.y = (rotation[1][0] + rotation[0][1]) * equation_1_over_4_wxyz_biggest;
        result.z = (rotation[0][2] + rotation[2][0]) * equation_1_over_4_wxyz_biggest;

        break;

    case 2:
        result.y = equation_wxyz_biggest;
        result.w = (rotation[0][2] - rotation[2][0]) * equation_1_over_4_wxyz_biggest;
        result.x = (rotation[1][0] + rotation[0][1]) * equation_1_over_4_wxyz_biggest;
        result.z = (rotation[2][1] + rotation[1][2]) * equation_1_over_4_wxyz_biggest;

        break;

    case 3:
        result.z = equation_wxyz_biggest;
        result.w = (rotation[1][0] - rotation[0][1]) * equation_1_over_4_wxyz_biggest;
        result.x = (rotation[0][2] - rotation[2][0]) * equation_1_over_4_wxyz_biggest;
        result.y = (rotation[2][1] - rotation[1][2]) * equation_1_over_4_wxyz_biggest;

        break;

    default:
        FALCON_ENGINE_THROW_ASSERTION_EXCEPTION();
    }

    return result;
}

}
