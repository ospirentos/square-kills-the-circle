#include "audio_manager.hpp"

// TODO: Aşama 5 — LoadSound, PlaySound, UnloadSound
void AudioManager::Init() {
    InitAudioDevice();
    // hitSound   = LoadSound("assets/sounds/hit.wav");
    // deathSound = LoadSound("assets/sounds/death.wav");
    // spawnSound = LoadSound("assets/sounds/spawn.wav");
}

void AudioManager::Shutdown() {
    // UnloadSound(hitSound);
    // UnloadSound(deathSound);
    // UnloadSound(spawnSound);
    CloseAudioDevice();
}

void AudioManager::PlayHit()   { /* PlaySound(hitSound);   */ }
void AudioManager::PlayDeath() { /* PlaySound(deathSound); */ }
void AudioManager::PlaySpawn() { /* PlaySound(spawnSound); */ }
