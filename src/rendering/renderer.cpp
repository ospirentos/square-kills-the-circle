#include "renderer.hpp"
#include "raylib.h"

// TODO: Aşama 1 — DrawCircle, DrawRectangle, DrawPoly ile shape rendering
namespace Renderer {
    void DrawEntities(const std::vector<Entity>& entities) {
        for (const auto& e : entities) {
            if (!e.active) continue;
            // TODO: shape'e göre çiz
        }
    }

    void DrawDebug(const std::vector<Entity>& entities) {
        for (const auto& e : entities) {
            if (!e.active) continue;
            DrawCircleLines((int)e.position.x, (int)e.position.y, e.radius, GREEN);
        }
    }
}
