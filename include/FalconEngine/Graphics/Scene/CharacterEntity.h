#pragma once

#include <FalconEngine/Graphics/Header.h>

#include <FalconEngine/Graphics/Renderer/Entity/Entity.h>

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
