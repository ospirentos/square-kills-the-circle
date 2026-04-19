# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Build

```bash
cmake -B build -S .
cmake --build build
./build/square-kills-the-circle
```

Gereksinimler: raylib 5.x ve Lua 5.4 sistem geneline kurulu olmalı. sol2 CMake tarafından FetchContent ile otomatik indirilir.

## Architecture

**Data-Oriented Design:** `Entity` bir struct'tır — tüm davranış `systems/` altındaki free function'larda yaşar. Entity'ye method ekleme.

**Akış:**
```
main.cpp → Game (game.hpp/cpp) → sistemler (systems/) + renderer (rendering/)
                                ↕
                         EntityManager (entity/)
                                ↕
                         Lua scripts (scripts/entities/)
```

**Sistem sorumlulukları:**
- `systems/physics` — `position += velocity * dt` (delta time zorunlu)
- `systems/collision` — CircleCircle ve AABB elle yazılır; raylib built-in ile karşılaştırılmaz, öğrenme amaçlı ayrı tutulur
- `systems/ai` — en yakın düşmanı bul, state machine geçişleri (IDLE→MOVING→ATTACKING→DEAD)
- `systems/combat` — hasar uygula, ölüm tespiti
- `rendering/particle` — çarpışma/ölüm VFX, lifetime bazlı alpha fade
- `scripting/lua_bridge` — sol2 üzerinden `scripts/entities/*.lua` dosyalarını okur, Entity struct'ını doldurur

**Entity state machine:**
```
IDLE → MOVING → ATTACKING → MOVING (yeni hedef)
                          → DEAD   (hp ≤ 0)
```

## Kodlama Kuralları

- Dosyalar: `snake_case.cpp`, sınıflar: `PascalCase`, fonksiyonlar: `camelCase`, sabitler: `UPPER_SNAKE`
- Tek dosyada 300 satır sınırı
- Hiçbir hareket sabit piksel/saniye kullanmaz — her zaman `* dt`
- `std::vector<Entity>` kullan, pointer array değil

## Geliştirme Aşamaları

1. Game Loop & Renderer — shape çizimi, delta time hareketi
2. Collision & Entity — CircleCircle, AABB, EntityManager, iki takım
3. AI & Combat — state machine, hedef bulma, hasar/ölüm
4. Lua Entegrasyonu — sol2 kurulumu, entity tanımlarını Lua'dan yükle
5. SFX & VFX — particle sistemi, audio
6. Polish — HP bar, screen shake, UI

## Lua Entity Tanımı

Her `scripts/entities/*.lua` dosyası `return {}` tablosu döner: `hp`, `speed`, `damage`, `radius`, `attack_range`, `attack_cooldown`, `color`, `on_spawn`, `on_attack`, `on_death` alanlarını içerir. C++ tarafında `lua_bridge.cpp` sol2 ile bunları okur.
