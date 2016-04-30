#include <FalconEngine/Geometry/Model.h>

namespace FalconEngine {
namespace Geometry {

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
Model::Model() : VAO(0), VBO(0)
{
}

// Copy Constructor
Model::Model(const Model& rhs)
{
    VAO = rhs.VAO;
    VBO = rhs.VBO;
}

// Copy Assignment
Model& Model::operator=(const Model& rhs)
{
    VAO = rhs.VAO;
    VBO = rhs.VBO;

    return *this;
}

// Move Constructor
Model::Model(Model&& rhs)
    : VAO(rhs.VAO)
    , VBO(rhs.VBO)
{
}

// Move Assignment
Model& Model::operator=(Model&& rhs)
{
    if (this != &rhs)
    {
        VAO = rhs.VAO;
        VBO = rhs.VBO;

        rhs.VAO = 0;
        rhs.VBO = 0;
    }

    return *this;
}

Model::~Model()
{
    VAO = 0;
    VBO = 0;
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void Model::Render(double percent)
{
}

}
}

