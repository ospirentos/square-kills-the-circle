#include "collision.hpp"

// [Ne yapıyor] İki dairenin merkezleri arasındaki mesareyi yarıçaplar toplamıyla karşılaştırır.
// [Neden distSquared] sqrt() pahalıdır — her frame yüzlerce kez çağrılır.
//                     Kare mesafe ile kare toplam karşılaştırmak matematiksel olarak eşdeğerdir.
bool CircleCircle(Vector2 posA, float rA, Vector2 posB, float rB) {
    float dx = posA.x - posB.x;
    float dy = posA.y - posB.y;
    float distSquared = dx * dx + dy * dy;
    float radiusSum = rA + rB;
    return distSquared <= radiusSum * radiusSum;
}

// TODO: Aşama 2 — AABB implementasyonu
bool AABB(Rectangle a, Rectangle b) {
    return a.x < b.x + b.width  &&
           a.x + a.width > b.x  &&
           a.y < b.y + b.height &&
           a.y + a.height > b.y;
}
