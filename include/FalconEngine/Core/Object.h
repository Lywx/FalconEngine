#pragma once

#include <FalconEngine/Core/Rtti.h>

namespace FalconEngine
{

class Object
{
public:
    virtual ~Object();

    FALCON_ENGINE_RTTI_DECLARE

    bool IsExactly(const Rtti& type) const;
    bool IsExactlyTypeOf(const Object *object) const;

    bool IsDerived(const Rtti& type) const;
    bool IsDerivedTypeOf(const Object *object) const;
};

}