inline const char *Rtti::GetTypeName() const
{
    return m_typeName;
}

inline bool Rtti::IsExactly(const Rtti& type) const
{
    return &type == this;
}

