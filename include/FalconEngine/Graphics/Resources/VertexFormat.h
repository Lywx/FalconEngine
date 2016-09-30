#pragma once

#include <FalconEngine/Core/Objects/Object.h>

namespace FalconEngine {

class VertexFormat : public Object
{
public:
    VertexFormat(int numAttributes);
    virtual ~VertexFormat();
};

}