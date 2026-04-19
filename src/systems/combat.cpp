#include "combat.hpp"

// TODO: Aşama 3 — hasar, cooldown, ölüm implementasyonları
namespace Combat {
    void Apply(Entity& attacker, Entity& target) {
        target.hp -= attacker.damage;
    }

    // [Ne yapıyor] HP<=0 olanları DEAD işaretler; active=false'ı Game yapar (particle spawn için).
    void CheckDeaths(std::vector<Entity>& entities) {
        for (auto& e : entities) {
            if (e.active && e.hp <= 0.0f)
                e.state = EntityState::DEAD;
        }
    }
}
