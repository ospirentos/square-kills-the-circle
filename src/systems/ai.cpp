#include "ai.hpp"
#include "combat.hpp"
#include <cmath>
#include <cfloat>

namespace AI {

// [Ne yapıyor] Verilen entity için karşı takımdan en yakın aktif entity'yi döner.
// [Neden her frame] Entity sayısı az (<100); önbellekleme Aşama 5+ konusu.
static Entity* findNearestEnemy(Entity& self, std::vector<Entity>& entities) {
    Entity* nearest = nullptr;
    float nearestDistSq = FLT_MAX;

    for (auto& other : entities) {
        if (!other.active || other.team == self.team) continue;
        float dx = other.position.x - self.position.x;
        float dy = other.position.y - self.position.y;
        float distSq = dx * dx + dy * dy;
        if (distSq < nearestDistSq) {
            nearestDistSq = distSq;
            nearest = &other;
        }
    }
    return nearest;
}

// [Ne yapıyor] Her entity için state machine'i bir adım ilerletir.
// [State akışı]
//   IDLE    → MOVING    : hedef bulununca
//   MOVING  → ATTACKING : hedef menzile girince (dist <= attackRange)
//   ATTACKING → MOVING  : hedef ölünce, yeni hedef ara
//   Herhangi → DEAD     : Combat::CheckDeaths halleder
void Update(std::vector<Entity>& entities, float dt) {
    for (auto& e : entities) {
        if (!e.active || e.state == EntityState::DEAD) continue;

        Entity* target = findNearestEnemy(e, entities);

        // Hedef yoksa (tüm düşmanlar öldü): dur ve bekle
        if (!target) {
            e.state = EntityState::IDLE;
            e.velocity = {0.0f, 0.0f};
            continue;
        }

        float dx = target->position.x - e.position.x;
        float dy = target->position.y - e.position.y;
        float dist = sqrtf(dx * dx + dy * dy);

        if (dist <= e.attackRange) {
            // Menzilde: saldır
            e.state = EntityState::ATTACKING;
            e.velocity = {0.0f, 0.0f}; // yerinde dur

            e.attackTimer -= dt;
            if (e.attackTimer <= 0.0f) {
                Combat::Apply(e, *target);
                e.attackTimer = e.attackCooldown; // cooldown'u sıfırla
            }
        } else {
            // Menzil dışı: hedefe doğru ilerle
            // [Normalize] Hem x hem y'yi mesafeye bölerek birim vektör elde ediyoruz.
            // Sonra speed ile çarparak hız kazandırıyoruz — her yöndeki hız eşit olur.
            e.state = EntityState::MOVING;
            e.velocity = {
                (dx / dist) * e.speed,
                (dy / dist) * e.speed
            };
        }
    }
}

} // namespace AI
