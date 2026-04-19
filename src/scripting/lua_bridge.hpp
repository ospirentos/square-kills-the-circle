#pragma once
#include "raylib.h"

// [Ne yapıyor] Bir Lua entity dosyasından okunan ham stat verisini taşır.
// [Neden ayrı struct] Entity spawn'dan bağımsız — aynı def birden fazla entity'ye uygulanabilir.
struct EntityDef {
    float hp;
    float speed;
    float damage;
    float radius;
    float attackRange;
    float attackCooldown;
    Color color;
};

// [Ne yapıyor] scripts/entities/*.lua dosyasını sol2 ile yükler, EntityDef olarak döner.
// [sol2 nerede] Sadece lua_bridge.cpp içinde include edilir — derleme süresini korumak için.
namespace LuaBridge {
    EntityDef load(const char* scriptPath);
}
