#include "physics.hpp"

// TODO: Aşama 2 — position += velocity * dt
namespace Physics {
    void Update(std::vector<Entity>& entities, float dt) {
        for (auto& e : entities) {
            if (!e.active) continue;
            e.position.x += e.velocity.x * dt;
            e.position.y += e.velocity.y * dt;
        }
    }
}
