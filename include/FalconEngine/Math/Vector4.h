#pragma once

#include <FalconEngine/Math/Header.h>

// NOTE(Wuxiang): Disable warning C4201: nonstandard extension used : nameless struct/union.
#pragma warning(disable : 4201)

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#pragma warning(default : 4201)

namespace FalconEngine
{

class Color;
class Vector3f;

// Assume vector are column vector
#pragma pack(push, 1)
class FALCON_ENGINE_ITEM_MATH Vector4f : public glm::vec4
{
public:
    const static Vector4f One;
    const static Vector4f Zero;
    const static Vector4f UnitX;
    const static Vector4f UnitY;
    const static Vector4f UnitZ;
    const static Vector4f UnitW;

    Vector4f();
    Vector4f(const Vector3f& v, const float w);
    Vector4f(const float x, const float y, const float z, const float w);

    // Implicit Conversion
    Vector4f(const glm::vec4& v);
};
#pragma pack(pop)

#pragma pack(push, 1)
class FALCON_ENGINE_ITEM_MATH Vector4i : public glm::ivec4
{
public:
    Vector4i();
    Vector4i(const int x, const int y, const int z, const int w);
};
#pragma pack(pop)

}
