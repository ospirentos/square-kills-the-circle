# square-kills-the-circle

2D Auto Battler — kare, üçgen ve daire şeklindeki entity'ler otomatik savaşır.

## Stack

- C++17
- raylib 5.x — renderer, input, audio
- Lua 5.4 — entity scripting
- sol2 — C++ ↔ Lua bridge
- CMake 3.20+

## Kurulum

### Gereksinimler

- CMake 3.20+
- raylib 5.x (sistem geneline kurulu)
- Lua 5.4 (sistem geneline kurulu)
- Git

### Derleme

```bash
cmake -B build -S .
cmake --build build
./build/square-kills-the-circle
```

## Proje Yapısı

```
src/          - C++ kaynak dosyaları
scripts/      - Lua entity tanımları
assets/       - Ses dosyaları (WAV)
```

## Geliştirme Aşamaları

- [ ] Aşama 1 — Game Loop & Renderer
- [ ] Aşama 2 — Collision & Entity
- [ ] Aşama 3 — AI & Combat
- [ ] Aşama 4 — Lua Entegrasyonu
- [ ] Aşama 5 — SFX & VFX
- [ ] Aşama 6 — Polish
