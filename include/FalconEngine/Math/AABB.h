#pragma once

#include <FalconEngine/Core/Macro.h>

#include <FalconEngine/Math/Matrix4.h>
#include <FalconEngine/Math/Vector3.h>

namespace FalconEngine
{

#pragma pack(push, 1)
FALCON_ENGINE_CLASS_BEGIN Aabb final
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    explicit Aabb(const Vector3f & position);
    ~Aabb() = default;

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    void
    Extend(const Vector3f & position);

private:
    /************************************************************************/
    /* Private Members                                                      */
    /************************************************************************/
    void
    Initialize(const Vector3f & position);

public:
    Vector3f mMax;
    Vector3f mMin;
};
#pragma pack(pop)
FALCON_ENGINE_CLASS_END

}
