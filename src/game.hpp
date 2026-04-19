#pragma once
#include "entity/entity_manager.hpp"
#include "entity/entity.hpp"
#include "rendering/particle.hpp"
#include "audio/audio_manager.hpp"
#include <vector>

class Game {
public:
    void Init();
    void Update(float dt);
    void Render();
    void Shutdown();

private:
    void spawnEntities();
    void reset();
    void drawUI();

    EntityManager         entityManager;
    std::vector<Particle> particles;
    AudioManager          audio;

    // Screen shake
    float shakeTimer = 0.0f;
    float shakeMag   = 0.0f;

    // Game-over
    bool gameOver       = false;
    Team winnerTeam     = Team::Red;

    bool debugDraw = false;
};
