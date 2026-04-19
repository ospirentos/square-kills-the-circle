#include "particle.hpp"
#include <cmath>

namespace ParticleSystem {

// [Ne yapıyor] pool içindeki ilk pasif particle'ı bulur ve doldurur; yoksa yeni ekler.
// [Neden pool] Her frame malloc/free yerine önceden ayrılmış bellek kullanmak daha hızlı.
void Spawn(std::vector<Particle>& pool, Vector2 pos, Color color, int count) {
    for (int i = 0; i < count; i++) {
        // Rastgele açı: 0-360 derece
        float angle = (float)GetRandomValue(0, 360) * DEG2RAD;
        float speed = (float)GetRandomValue(60, 200);

        Particle p{};
        p.position    = pos;
        p.velocity    = { cosf(angle) * speed, sinf(angle) * speed };
        p.color       = color;
        p.lifetime    = (float)GetRandomValue(30, 80) / 100.0f; // 0.3 - 0.8 saniye
        p.maxLifetime = p.lifetime;
        p.radius      = (float)GetRandomValue(3, 7);
        p.active      = true;

        // Pool'da boş slot ara
        bool placed = false;
        for (auto& slot : pool) {
            if (!slot.active) { slot = p; placed = true; break; }
        }
        if (!placed) pool.push_back(p);
    }
}

// [Ne yapıyor] Her particle'ın ömrünü azaltır, pozisyonunu ilerletir.
// [Sürtünme] velocity *= 0.92 — her frame hız %8 azalır, hareket doğal yavaşlar.
void Update(std::vector<Particle>& pool, float dt) {
    for (auto& p : pool) {
        if (!p.active) continue;
        p.lifetime -= dt;
        if (p.lifetime <= 0.0f) { p.active = false; continue; }
        p.velocity.x *= 0.92f;
        p.velocity.y *= 0.92f;
        p.position.x += p.velocity.x * dt;
        p.position.y += p.velocity.y * dt;
    }
}

// [Ne yapıyor] Kalan ömür oranını alpha'ya yazar; particle yaşlandıkça solar.
// [Alpha hesabı] ratio = lifetime / maxLifetime → 1.0 (yeni) … 0.0 (ölü)
//               255 * ratio → tam opak'tan şeffafa.
void Draw(const std::vector<Particle>& pool) {
    for (const auto& p : pool) {
        if (!p.active) continue;
        float ratio = p.lifetime / p.maxLifetime;
        Color c = p.color;
        c.a = (unsigned char)(255.0f * ratio);
        DrawCircleV(p.position, p.radius * ratio, c); // küçülüp solar
    }
}

} // namespace ParticleSystem
