#pragma once

#include <FalconEngine/Geometry/Model.h>

#include "GeometryMesh.h"

namespace FalconEngine {

class GeometryModel : public Model
{
public:
    GeometryModel();
    GeometryModel(GeometryMesh mesh);

    virtual void Render(double percent) override;

    void LoadModel(GeometryMesh mesh);

protected:
    GLuint EBO = 0; // Index Buffer

    GeometryMesh Mesh;
};

}