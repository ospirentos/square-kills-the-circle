#include "entity_manager.hpp"

// TODO: Aşama 2 — spawn, remove, getAll implementasyonları
Entity& EntityManager::Spawn(EntityShape shape, Team team, Vector2 position) {
    Entity e{};
    e.id = nextId++;
    e.shape = shape;
    e.team = team;
    e.position = position;
    e.state = EntityState::IDLE;
    e.active = true;
    entities.push_back(e);
    return entities.back();
}

void EntityManager::Remove(int id) {
    for (auto& e : entities) {
        if (e.id == id) { e.active = false; }
    }
}

std::vector<Entity>& EntityManager::GetAll() {
    return entities;
}
