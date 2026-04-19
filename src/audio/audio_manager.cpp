#include "audio_manager.hpp"
#include <cmath>
#include <cstdlib>

static const int   SAMPLE_RATE = 44100;
static const float PI2         = 2.0f * 3.14159265f;

// [Ne yapıyor] Frekansı startHz'den endHz'e doğrusal sweep eden ses üretir.
// [Neden phase birikimi] Her sample'da frekansı değiştirirken phase'i sürekli biriktirirsek
//                        ses kopukluğu (click) olmaz — akıcı geçiş sağlanır.
static Sound makeSweep(float startHz, float endHz, float durationSec, float volume = 0.4f) {
    int   frames = (int)(SAMPLE_RATE * durationSec);
    short* data  = (short*)malloc(frames * sizeof(short));

    float phase = 0.0f;
    for (int i = 0; i < frames; i++) {
        float progress = (float)i / frames;
        float freq     = startHz + (endHz - startHz) * progress;
        float fade     = 1.0f - progress; // sonuna doğru kısıl
        phase += PI2 * freq / SAMPLE_RATE;
        data[i] = (short)(volume * 32000.0f * fade * sinf(phase));
    }

    Wave wave  = { (unsigned int)frames, SAMPLE_RATE, 16, 1, data };
    Sound snd  = LoadSoundFromWave(wave);
    free(data);
    return snd;
}

void AudioManager::Init() {
    InitAudioDevice();
    // Hit: kısa, yüksek tık (600→300 Hz, 120ms)
    hitSound   = makeSweep(600.0f, 300.0f, 0.12f, 0.3f);
    // Death: aşağı süpürme (500→80 Hz, 450ms) — düşüş hissi
    deathSound = makeSweep(500.0f,  80.0f, 0.45f, 0.5f);
    // Spawn: yukarı süpürme (200→700 Hz, 200ms) — taze başlangıç
    spawnSound = makeSweep(200.0f, 700.0f, 0.20f, 0.25f);
}

void AudioManager::Shutdown() {
    UnloadSound(hitSound);
    UnloadSound(deathSound);
    UnloadSound(spawnSound);
    CloseAudioDevice();
}

void AudioManager::Update(float dt) {
    if (hitCooldown > 0.0f) hitCooldown -= dt;
}

// [Ne yapıyor] Cooldown dolmadan aynı ses tekrar çalmaz — çarpışma spam'ini önler.
void AudioManager::PlayHit() {
    if (hitCooldown <= 0.0f) {
        PlaySound(hitSound);
        hitCooldown = 0.18f;
    }
}

void AudioManager::PlayDeath() { PlaySound(deathSound); }
void AudioManager::PlaySpawn() { PlaySound(spawnSound); }
