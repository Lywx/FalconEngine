#include <FalconEngine/Geometry/GeometryModel.h>

#define BUFFER_OFFSET(offset) ((void *)(offset))

namespace FalconEngine {
namespace Geometry {

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
GeometryModel::GeometryModel()
    : Mesh(GeometryMesh())
{

}

GeometryModel::GeometryModel(GeometryMesh mesh)
{
    LoadModel(mesh);
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void GeometryModel::LoadModel(GeometryMesh mesh)
{
    Mesh = mesh;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Math::Vector3) * Mesh.VertexSize(), &Mesh.VertexFront(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Math::Index) * Mesh.IndexSize(), &Mesh.IndexFront(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), static_cast<GLvoid *>(nullptr));
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void GeometryModel::Render(double percent)
{
    // Set mvp

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, int(sizeof(Math::Index) * Mesh.IndexSize()), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

}
}