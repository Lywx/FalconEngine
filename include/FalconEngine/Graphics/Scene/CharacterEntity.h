#pragma once

#include <FalconEngine/Graphics/SceneInclude.h>

namespace FalconEngine
{

class FALCON_ENGINE_ITEM_GRAPHICS CharacterEntity : public Entity
{
    FALCON_ENGINE_RTTI_DECLARE;

public:
    explicit CharacterEntity(const NodeSharedPtr node);
    virtual ~CharacterEntity();
};

}
