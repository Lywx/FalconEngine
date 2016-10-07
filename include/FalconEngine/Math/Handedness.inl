inline Vector3f Handedness::Left(const Matrix4f& view) const
{
    return -Right(view);
};

inline Vector3f Handedness::Down(const Matrix4f& view) const
{
    return -Up(view);
};

inline Vector3f Handedness::Backward(const Matrix4f& view) const
{
    return -Forward(view);
};

