#pragma once
#include "../entity/entity.hpp"
#include <vector>

// [Ne yapıyor] Hasar uygulama, HP kontrolü, ölüm tespiti.
namespace Combat {
    void Apply(Entity& attacker, Entity& target);
    void CheckDeaths(std::vector<Entity>& entities);
}
