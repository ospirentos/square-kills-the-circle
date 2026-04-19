#pragma once
#include "raylib.h"
#include <vector>

// [Ne yapıyor] Çarpışma ve ölüm anında ekranda kısa ömürlü görsel efektler yayar.
struct Particle {
    Vector2 position;
    Vector2 velocity;
    Color color;
    float lifetime;    // kalan süre (saniye)
    float maxLifetime;
    float radius;
    bool active;
};

namespace ParticleSystem {
    void Spawn(std::vector<Particle>& pool, Vector2 pos, Color color, int count);
    void Update(std::vector<Particle>& pool, float dt);
    void Draw(const std::vector<Particle>& pool);
}
