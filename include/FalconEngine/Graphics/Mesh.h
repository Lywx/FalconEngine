#pragma once

#include <vector>
#include <memory>

#include <FalconEngine/Math/Vector2.h>
#include <FalconEngine/Math/Vector3.h>
#include <FalconEngine/Math/Index.h>

namespace FalconEngine {
namespace Graphics {

typedef std::vector<Math::Vector3> VertexList;
typedef std::vector<Math::Vector2> TextureList;
typedef std::vector<Math::Index>   IndexList;

class Mesh
{
public:
    friend void swap(Mesh&, Mesh&);

    Mesh();

    Mesh(const Mesh& rhs);                    // Copy Constructor
    virtual Mesh& operator=(const Mesh& rhs); // Copy Assignment

    Mesh(Mesh&& rhs) noexcept;                // Move Constructor
    virtual Mesh& operator=(Mesh&& rhs);      // Move Assignment

    virtual ~Mesh();

    std::shared_ptr<VertexList> Vertexes() const { return m_Vertexes; }
    size_t                      VertexSize() const { return m_Vertexes->size(); }
    Math::Vector3&              VertexFront() const { return m_Vertexes->front(); }

    std::shared_ptr<IndexList> Indexes() const { return m_Indexes; }
    size_t                     IndexSize() const { return m_Indexes->size(); }
    Math::Index&               IndexFront() const { return m_Indexes->front(); }

    virtual void LoadMesh(std::initializer_list<std::wstring> fileNames) = 0;

protected:
    std::shared_ptr<VertexList> m_Vertexes;
    std::shared_ptr<IndexList>  m_Indexes;
};

inline void swap(Mesh &lhs, Mesh &rhs)
{
    using std::swap;
    swap(lhs.m_Vertexes, rhs.m_Vertexes);
    swap(lhs.m_Indexes, rhs.m_Indexes);
}

}
}
