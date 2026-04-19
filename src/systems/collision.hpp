#pragma once
#include "raylib.h"

// [Ne yapıyor] Çarpışma kontrol fonksiyonları — elle yazılır, raylib built-in ile karşılaştırılır.
// [Öğrenme sırası] CircleCircle → AABB → SAT (Aşama 2, 3)

// İki daire çarpışıyor mu?
bool CircleCircle(Vector2 posA, float rA, Vector2 posB, float rB);

// İki eksen hizalı dikdörtgen çarpışıyor mu?
bool AABB(Rectangle a, Rectangle b);
