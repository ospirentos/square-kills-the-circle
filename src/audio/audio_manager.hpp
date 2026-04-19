#pragma once
#include "raylib.h"

// [Ne yapıyor] Ses dosyalarını yükler ve oyun olaylarına göre çalar.
// [Bağımlılık] raylib InitAudioDevice() main.cpp'de çağrılmış olmalı.
class AudioManager {
public:
    void Init();
    void Shutdown();
    void PlayHit();
    void PlayDeath();
    void PlaySpawn();

private:
    Sound hitSound;
    Sound deathSound;
    Sound spawnSound;
};
