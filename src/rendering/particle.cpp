#include "particle.hpp"

// TODO: Aşama 5 — particle spawn, lifetime azaltma, alpha fade
namespace ParticleSystem {
    void Spawn(std::vector<Particle>& pool, Vector2 pos, Color color, int count) {
        (void)pool; (void)pos; (void)color; (void)count;
    }

    void Update(std::vector<Particle>& pool, float dt) {
        for (auto& p : pool) {
            if (!p.active) continue;
            p.lifetime -= dt;
            if (p.lifetime <= 0.0f) { p.active = false; continue; }
            p.position.x += p.velocity.x * dt;
            p.position.y += p.velocity.y * dt;
        }
    }

    void Draw(const std::vector<Particle>& pool) {
        (void)pool;
    }
}
