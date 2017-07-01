#pragma once

#include <FalconEngine/Math/Common.h>

#include <string>

// NOTE(Wuxiang): Disable warning C4201: nonstandard extension used : nameless struct/union.
#pragma warning(disable : 4201)

#include <glm/glm.hpp>
#include <glm/vec2.hpp>

#pragma warning(default : 4201)

namespace FalconEngine
{

// Assume vector are column vector
#pragma pack(push, 1)
class FALCON_ENGINE_API Vector2f : public glm::vec2
{
public:
    /************************************************************************/
    /* Static Members                                                       */
    /************************************************************************/
    static const Vector2f One;
    static const Vector2f Zero;
    static const Vector2f UnitX;
    static const Vector2f UnitY;

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    Vector2f();
    Vector2f(const float& x, const float& y);

    // Implicit Conversion
    Vector2f(const glm::vec2& v);
};
#pragma pack(pop)

FALCON_ENGINE_API std::string
to_string(const Vector2f& v);

// @summary Represents a point in 2D space
#pragma pack(push, 1)
class FALCON_ENGINE_API Vector2i : public glm::ivec2
{
public:
    static const Vector2i Zero;

public:
    Vector2i();
    Vector2i(const int x, const int y);
    Vector2i(const float x, const float y);

    // Implicit Conversion
    Vector2i(const glm::ivec2 v);

    // Explicit Conversion
    explicit operator glm::ivec2() const;
    explicit operator Vector2f() const;
};
#pragma pack(pop)

FALCON_ENGINE_API std::string
to_string(const Vector2i& v);

}
