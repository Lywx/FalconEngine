#pragma once

#include <FalconEngine/Graphics/SceneInclude.h>

namespace FalconEngine
{

class CharacterEntity : public Entity
{
    FALCON_ENGINE_RTTI_DECLARE;

public:
    explicit CharacterEntity(const NodeSharedPtr node);
    virtual ~CharacterEntity();
};

}
