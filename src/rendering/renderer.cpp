#include "renderer.hpp"
#include "raylib.h"

// [Ne yapıyor] Entity'nin shape türüne bakarak doğru raylib çizim fonksiyonunu çağırır.
// [Neden switch] Entity sayısı az, her frame bu döngü çalışır — sade ve hızlı.
// [Üçgen neden DrawPoly] raylib'de düzenli çokgen çizer; 3 kenar = eşkenar üçgen.
namespace Renderer {
    void DrawEntities(const std::vector<Entity>& entities) {
        for (const auto& e : entities) {
            if (!e.active) continue;

            switch (e.shape) {
                case EntityShape::CIRCLE:
                    DrawCircleV(e.position, e.radius, e.color);
                    break;

                case EntityShape::SQUARE: {
                    // Kareyi pozisyonun merkezine hizala
                    float half = e.radius;
                    DrawRectangle(
                        (int)(e.position.x - half),
                        (int)(e.position.y - half),
                        (int)(half * 2),
                        (int)(half * 2),
                        e.color
                    );
                    break;
                }

                case EntityShape::TRIANGLE:
                    // DrawPoly: merkez, kenar sayısı, yarıçap, döndürme açısı, renk
                    DrawPoly(e.position, 3, e.radius, 0.0f, e.color);
                    break;
            }
        }
    }

    // [Ne yapıyor] Entity'nin üstüne iki katmanlı bar çizer: gri zemin + renkli HP oranı.
    // [Oran hesabı] hp/maxHp → 0.0 ile 1.0 arası; bu değer bar genişliğini belirler.
    void DrawHpBars(const std::vector<Entity>& entities) {
        const float BAR_W  = 36.0f;
        const float BAR_H  = 5.0f;
        const float BAR_Y_OFFSET = 10.0f; // entity'nin üstünden ne kadar yukarıda

        for (const auto& e : entities) {
            if (!e.active) continue;

            float ratio = e.hp / e.maxHp;
            float x = e.position.x - BAR_W * 0.5f;
            float y = e.position.y - e.radius - BAR_Y_OFFSET - BAR_H;

            // Gri zemin (dolu bar)
            DrawRectangle((int)x, (int)y, (int)BAR_W, (int)BAR_H, DARKGRAY);
            // Renkli doluluk
            Color barColor = (e.team == Team::Red) ? RED : (e.team == Team::Blue) ? BLUE : GREEN;
            DrawRectangle((int)x, (int)y, (int)(BAR_W * ratio), (int)BAR_H, barColor);
        }
    }

    void DrawDebug(const std::vector<Entity>& entities) {
        for (const auto& e : entities) {
            if (!e.active) continue;
            // Yeşil daire = collision sınırı — çarpışma sistemini ayıklarken kullanılır
            DrawCircleLines((int)e.position.x, (int)e.position.y, e.radius, GREEN);
        }
    }
}
