#pragma once
#include "raylib.h"
#include "../entity/entity.hpp"
#include <vector>

// [Öğrenme sırası] CircleCircle → AABB → SAT (Aşama 2, 3)

// İki daire çarpışıyor mu?
bool CircleCircle(Vector2 posA, float rA, Vector2 posB, float rB);

// İki eksen hizalı dikdörtgen çarpışıyor mu?
bool AABB(Rectangle a, Rectangle b);

// [Ne yapıyor] Tüm entity çiftlerini kontrol eder, örtüşenleri iter.
// [Kapsam] Aşama 2: fiziksel ayırma. Aşama 3'te state geçişleri buraya eklenecek.
namespace Collision {
    void Update(std::vector<Entity>& entities);
}
