#pragma once

#include <FalconEngine/Math/Common.h>

#include <FalconEngine/Math/Matrix4.h>
#include <FalconEngine/Math/Vector3.h>

namespace FalconEngine
{

#pragma warning(disable : 4251)
#pragma pack(push, 1)
class FALCON_ENGINE_API Aabb final
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    explicit Aabb(const Vector3f& position);
    ~Aabb() = default;

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    void
    Extend(const Vector3f& position);

private:
    /************************************************************************/
    /* Private Members                                                      */
    /************************************************************************/
    void
    Initialize(const Vector3f& position);

public:
    Vector3f mMax;
    Vector3f mMin;
};
#pragma pack(pop)
#pragma warning(default : 4251)

}
