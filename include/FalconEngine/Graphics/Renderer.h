#pragma once

#include <FalconEngine/Geometry/Model.h>

namespace FalconEngine {


class Renderer
{
public:
    Renderer();
    ~Renderer();

    void Render(Model& model) const;
};

}
