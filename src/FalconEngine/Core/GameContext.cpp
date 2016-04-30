#include <FalconEngine/Core/GameContext.h>

namespace FalconEngine {
namespace Core {

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
GameContext::GameContext()
{

}

GameContext::GameContext(const GameContext& rhs)
{
}

GameContext& GameContext::operator=(const GameContext& rhs)
{
    return *this;
}

GameContext::GameContext(GameContext&& rhs) noexcept
{
}

GameContext& GameContext::operator=(GameContext&& rhs) noexcept
{
    return *this;
}

GameContext::~GameContext()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void GameContext::Initialize() {};
void GameContext::Exit() {};

void GameContext::RenderBegin() {}
void GameContext::Render(double percent) { }
void GameContext::RenderEnd() {}

void GameContext::Update(double elapsed) { }
void GameContext::UpdateInput() { }

}
}