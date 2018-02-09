#include <FalconEngine/Core/Object.h>

namespace FalconEngine
{

/************************************************************************/
/* Static Members                                                       */
/************************************************************************/
const Rtti
Object::sRttiType("Object", nullptr);

const Rtti&
Object::GetStaticType()
{
    return sRttiType;
}

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
Object::~Object()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
const Rtti&
Object::GetDynamicType() const
{
    return sRttiType;
}

bool
Object::IsExactly(const Rtti& type) const
{
    return GetDynamicType().IsExactly(type);
}

bool
Object::IsDerived(const Rtti& type) const
{
    return GetDynamicType().IsDerived(type);
}

bool
Object::HasSameType(const Object *object) const
{
    return object && IsExactly(object->GetDynamicType());
}

bool
Object::HasDerivedType(const Object *object) const
{
    return object && IsDerived(object->GetDynamicType());
}
}
