#include "collision.hpp"
#include <cmath>

// [Ne yapıyor] İki dairenin merkezleri arasındaki mesafeyi yarıçaplar toplamıyla karşılaştırır.
// [Neden distSquared] sqrt() pahalıdır — her frame yüzlerce kez çağrılır.
//                     Kare mesafe ile kare toplam karşılaştırmak matematiksel olarak eşdeğerdir.
bool CircleCircle(Vector2 posA, float rA, Vector2 posB, float rB) {
    float dx = posA.x - posB.x;
    float dy = posA.y - posB.y;
    float distSquared = dx * dx + dy * dy;
    float radiusSum = rA + rB;
    return distSquared <= radiusSum * radiusSum;
}

// [Ne yapıyor] İki eksen-hizalı dikdörtgenin 4 kenarını karşılaştırır.
// [Mantık] "Ayrılma testi": herhangi bir eksende boşluk varsa çarpışma YOK demektir.
//          4 koşulun hepsi sağlanırsa çarpışma VAR.
bool AABB(Rectangle a, Rectangle b) {
    return a.x < b.x + b.width  &&
           a.x + a.width > b.x  &&
           a.y < b.y + b.height &&
           a.y + a.height > b.y;
}

namespace Collision {

// [Ne yapıyor] Tüm aktif entity çiftlerini O(n²) ile tarar; örtüşenleri ayırır.
// [Neden O(n²) kabul edilebilir] Entity sayısı küçük (<100); optimizasyon Aşama 5+ konusu.
// [Tüm şekiller için CircleCircle] Entity.radius kare/üçgen için de yaklaşık sınır —
//   bu, görsel olarak yeterli; hassas SAT collision Aşama 3'te eklenecek.
void Update(std::vector<Entity>& entities) {
    for (int i = 0; i < (int)entities.size(); i++) {
        for (int j = i + 1; j < (int)entities.size(); j++) {
            Entity& a = entities[i];
            Entity& b = entities[j];
            if (!a.active || !b.active) continue;

            float dx = b.position.x - a.position.x;
            float dy = b.position.y - a.position.y;
            float distSq = dx * dx + dy * dy;
            float minDist = a.radius + b.radius;

            if (distSq >= minDist * minDist || distSq < 0.0001f) continue;

            // Gerçek mesafeyi hesapla (burada sqrt zorunlu — ayırma vektörü lazım)
            float dist    = sqrtf(distSq);
            float overlap = minDist - dist;

            // Çarpışma normali: A'dan B'ye giden birim vektör
            float nx = dx / dist;
            float ny = dy / dist;

            // Takım farkı gözetmeksizin sadece fiziksel ayırma — velocity AI sistemi yönetir
            a.position.x -= nx * overlap * 0.5f;
            a.position.y -= ny * overlap * 0.5f;
            b.position.x += nx * overlap * 0.5f;
            b.position.y += ny * overlap * 0.5f;
        }
    }
}

} // namespace Collision
