inline int ControlledObject::GetControllerNum() const
{
    return m_ControllerNum;
}

inline ControllerPtr ControlledObject::GetController(int i) const
{
    if (0 <= i && i < m_ControllerNum)
    {
        return m_Controllers[i];
    }

    throw std::invalid_argument("Invalid controller index.\n");
}
