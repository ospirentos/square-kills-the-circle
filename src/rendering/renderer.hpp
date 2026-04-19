#pragma once
#include "../entity/entity.hpp"
#include <vector>

// [Ne yapıyor] Entity shape'lerine göre ekrana çizer; debug mode'da hitbox'ları gösterir.
namespace Renderer {
    void DrawEntities(const std::vector<Entity>& entities);
    void DrawDebug(const std::vector<Entity>& entities);
}
