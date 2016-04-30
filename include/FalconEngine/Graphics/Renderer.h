#pragma once

#include <FalconEngine/Geometry/Model.h>

namespace FalconEngine {
namespace Graphics {

class Renderer
{
public:
    Renderer();
    ~Renderer();

    void Render(Geometry::Model& model) const;
};

}
}
