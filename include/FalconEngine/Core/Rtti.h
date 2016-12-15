#pragma once

namespace FalconEngine
{

class Rtti
{
public:
    Rtti (const char *name, const Rtti *baseType);
    ~Rtti ();

    inline const char *GetTypeName() const;

    inline bool IsExactly(const Rtti& type) const;
    bool        IsDerived(const Rtti& type) const;

private:
    const char *m_typeName;
    const Rtti *m_typeBase;
};

#include "Rtti.inl"
}

#define FALCON_ENGINE_DECLARE_RTTI \
public: \
    static const Rtti Type; \
    \
    virtual const Rtti& GetType() const \
    { \
        return Type; \
    }

#define FALCON_ENGINE_IMPLEMENT_RTTI(klass, baseklass) \
    const Rtti klass::Type(#klass, &baseklass::Type)
