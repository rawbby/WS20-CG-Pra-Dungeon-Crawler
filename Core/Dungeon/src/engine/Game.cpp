#include "Game.hpp"

namespace engine
{
    void Game::update (float delta)
    {
        m_collision_service.update(m_registry, delta);
        m_render_service.update(m_registry, delta);
    }
}
