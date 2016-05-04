#include <FalconEngine/Graphics/Mesh.h>

namespace FalconEngine {

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
Mesh::Mesh()
    : m_Vertexes(std::make_shared<VertexList>(VertexList()))
    , m_Indexes(std::make_shared<IndexList>(IndexList()))
{
}

// Copy Constructor
Mesh::Mesh(const Mesh& rhs)
    : m_Vertexes(rhs.m_Vertexes)
    , m_Indexes(rhs.m_Indexes)
{
}

// Copy Assignment
/* virtual */ Mesh& Mesh::operator=(const Mesh& rhs)
{
    m_Vertexes = rhs.m_Vertexes;
    m_Indexes = rhs.m_Indexes;

    return *this;
}

// Move Constructor
Mesh::Mesh(Mesh&& rhs) noexcept
    : m_Vertexes(rhs.m_Vertexes)
    , m_Indexes(rhs.m_Indexes)
{
    rhs.m_Vertexes = nullptr;
    rhs.m_Indexes = nullptr;
}

// Move Assignment
/* virtual */ Mesh& Mesh::operator=(Mesh&& rhs)
{
    if (this != &rhs)
    {
        m_Vertexes = rhs.m_Vertexes;
        m_Indexes = rhs.m_Indexes;

        rhs.m_Vertexes = nullptr;
        rhs.m_Indexes = nullptr;
    }

    return *this;
}

/* virtual */ Mesh::~Mesh()
{
}

}