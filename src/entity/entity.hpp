#pragma once
#include "raylib.h"

enum class EntityShape { CIRCLE, SQUARE, TRIANGLE };
enum class EntityState { IDLE, MOVING, ATTACKING, DEAD };
// [Dikkat] RED, BLUE, GREEN raylib macro'larıdır — enum değerleri PascalCase kullanır.
enum class Team { Red, Blue, Green };

// [Ne yapıyor] Oyundaki her savaşan birimin tüm verisini tutan struct.
// [Neden struct] Davranış burada değil, systems/ klasöründeki fonksiyonlarda olacak.
//               Data ve logic birbirinden ayrı tutulur — Data-Oriented Design prensibi.
struct Entity {
    int id;
    EntityShape shape;
    EntityState state;
    Team team;

    Vector2 position;
    Vector2 velocity;
    float radius; // kare ve üçgen için de yaklaşık collision radius kullanılır

    float hp;
    float maxHp;
    float damage;
    float speed;
    float attackRange;
    float attackCooldown;
    float attackTimer;

    Color color;
    bool active;
};
