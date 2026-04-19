#pragma once
#include "../entity/entity.hpp"
#include <vector>

// [Ne yapıyor] Entity'lerin pozisyonunu velocity ve delta time'a göre günceller.
// [Kural] Hiçbir hareket sabit sayı kullanmaz — her zaman dt ile çarpılır.
namespace Physics {
    void Update(std::vector<Entity>& entities, float dt);
}
