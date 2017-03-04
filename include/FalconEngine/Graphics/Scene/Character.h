#pragma once

#include <FalconEngine/Graphics/SceneInclude.h>

namespace FalconEngine
{

class Character : public Entity
{
    FALCON_ENGINE_RTTI_DECLARE;

public:
    explicit Character(const NodeSharedPtr node);
    virtual ~Character();
};

}
