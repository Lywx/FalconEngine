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
    const char *mTypeName;
    const Rtti *mTypeBase;
};

inline const char *Rtti::GetTypeName() const
{
    return mTypeName;
}

inline bool Rtti::IsExactly(const Rtti& type) const
{
    return &type == this;
}

}

#define FALCON_ENGINE_RTTI_DECLARE \
public: \
    static const Rtti Type; \
    \
    virtual const Rtti& GetType() const \
    { \
        return Type; \
    }

#define FALCON_ENGINE_RTTI_IMPLEMENT(klass, baseklass) \
    const Rtti klass::Type(#klass, &baseklass::Type)
