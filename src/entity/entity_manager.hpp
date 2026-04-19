#pragma once
#include "entity.hpp"
#include <vector>

// [Ne yapıyor] Tüm entity'lerin listesini tutar; spawn/despawn işlemlerini yönetir.
// [Diğer sistemlerle ilişki] systems/ altındaki her sistem EntityManager'dan
//                            entity listesini alarak üzerinde çalışır.
class EntityManager {
public:
    Entity& Spawn(EntityShape shape, Team team, Vector2 position);
    void Remove(int id);
    std::vector<Entity>& GetAll();

private:
    std::vector<Entity> entities;
    int nextId = 0;
};
