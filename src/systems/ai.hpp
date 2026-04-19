#pragma once
#include "../entity/entity.hpp"
#include <vector>

// [Ne yapıyor] Her entity için en yakın düşmanı bulur, state machine geçişlerini yönetir.
// [State akışı] IDLE → MOVING → ATTACKING → (MOVING veya DEAD)
namespace AI {
    void Update(std::vector<Entity>& entities, float dt);
}
