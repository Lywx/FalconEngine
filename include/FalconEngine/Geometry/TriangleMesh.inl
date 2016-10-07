TriangleVertexListPtr TriangleMesh::VertexListPtr() const
{
    return m_vertexList;
}

size_t TriangleMesh::VertexSize() const
{
    return m_vertexList->size();
}

Vector3f& TriangleMesh::VertexFront() const
{
    return m_vertexList->front();
}

TriangleIndexListPtr TriangleMesh::IndexListPtr() const
{
    return m_indexList;
}

size_t TriangleMesh::IndexSize() const
{
    return m_indexList->size();
}

TriangleIndex& TriangleMesh::IndexFront() const
{
    return m_indexList->front();
}
