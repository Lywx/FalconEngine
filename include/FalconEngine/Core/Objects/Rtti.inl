inline const char *Rtti::GetName() const
{
    return m_Name;
}

inline bool Rtti::IsExactly(const Rtti& type) const
{
    return &type == this;
}

