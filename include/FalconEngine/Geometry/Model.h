#pragma once

#include <vector>

#define GLEW_STATIC
#include <GL/glew.h>

namespace FalconEngine {

class Model
{
public:

    Model();

    Model(const Model& rhs);                    // Copy Constructor
    virtual Model& operator=(const Model& rhs); // Copy Assignment

    Model(Model&& rhs);                         // Move Constructor
    virtual Model& operator=(Model&& rhs);      // Move Assignment

    virtual ~Model();

    virtual void Render(double percent);

protected:
    GLuint VAO;                                 // Vertex Array
    GLuint VBO;                                 // Vertex Buffer
};

}
