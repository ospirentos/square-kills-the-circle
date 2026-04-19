#pragma once
#include "raylib.h"

// [Ne yapıyor] Procedural sine wave sesleri üretir ve oyun olaylarına göre çalar.
// [Bağımlılık] Init() Game::Init() içinden çağrılmalı — InitWindow'dan sonra.
class AudioManager {
public:
    void Init();
    void Shutdown();
    void Update(float dt);  // hit cooldown sayacını günceller
    void PlayHit();
    void PlayDeath();
    void PlaySpawn();

private:
    Sound hitSound;
    Sound deathSound;
    Sound spawnSound;
    float hitCooldown = 0.0f; // aynı frame'de spam çalmayı önler
};
