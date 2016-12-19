#include <FalconEngine/Core/Object.h>

namespace FalconEngine
{

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
const Rtti Object::Type("Object", nullptr);

Object::~Object()
{
}

bool Object::IsExactly(const Rtti& type) const
{
    return GetType().IsExactly(type);
}

bool Object::IsExactlyTypeOf(const Object *object) const
{
    return object && GetType().IsExactly(object->GetType());
}

bool Object::IsDerived(const Rtti& type) const
{
    return GetType().IsDerived(type);
}

bool Object::IsDerivedTypeOf(const Object *object) const
{
    return object && GetType().IsDerived(object->GetType());
}

}