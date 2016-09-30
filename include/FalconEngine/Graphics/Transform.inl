inline const Matrix4f& Transform::Matrix() const
{
    return m_matrix;
}

inline const Matrix4f& Transform::Rotation() const
{
    return m_matrix;
}

inline const Vector3f& Transform::Translation() const
{
    return m_translation;
}

inline const Vector3f& Transform::Scaling() const
{
    return m_scale;
}

inline Vector4f Transform::operator* (const Vector4f& vector) const
{
    return m_matrix * vector;
}

// TODO
//inline Transform Transform::operator*(const Transform& transform) const
//{
//    if (IsIdentity())
//    {
//        return transform;
//    }
//
//    if (transform.IsIdentity())
//    {
//        return *this;
//    }
//
//    Transform product;
//
//    if (mIsRSMatrix && transform.mIsRSMatrix)
//    {
//        if (mIsUniformScale)
//        {
//            product.SetRotate(m_Matrix * transform.mMatrix);
//
//            product.SetTranslate(GetUniformScale() * (
//                                     mMatrix * transform.mTranslate) + mTranslate);
//
//            if (transform.IsUniformScale())
//            {
//                product.SetUniformScale(
//                    GetUniformScale()*transform.GetUniformScale());
//            }
//            else
//            {
//                product.SetScale(GetUniformScale()*transform.GetScale());
//            }
//
//            return product;
//        }
//    }
//
//    // In all remaining cases, the matrix cannot be written as R*S*X+T.
//    Matrix4f matMA = (mIsRSMatrix ? mMatrix.TimesDiagonal(mScale) : mMatrix);
//    Matrix4f matMB = transform.mIsRSMatrix ?
//                     transform.mMatrix.TimesDiagonal(transform.mScale) :
//                     transform.mMatrix;
//
//    product.SetMatrix(matMA * matMB);
//    product.SetTranslate(matMA * transform.mTranslate + mTranslate);
//
//    return Transform(m_Matrix * transform.m_Matrix);
//}
