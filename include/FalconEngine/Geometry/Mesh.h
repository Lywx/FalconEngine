#pragma once

#include <fstream>

#include <FalconEngine/Core/Objects/Object.h>
#include <memory>

namespace FalconEngine {

class Mesh : public Object
{
    FALCON_ENGINE_DECLARE_RTTI;

    Mesh();
    virtual ~Mesh();

    virtual void LoadMesh(std::initializer_list<std::wstring> fileNames) = 0;
};

typedef std::shared_ptr<Mesh> MeshPtr;

}
