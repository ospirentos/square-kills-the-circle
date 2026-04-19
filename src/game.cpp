#include "game.hpp"
#include "systems/physics.hpp"
#include "systems/collision.hpp"
#include "systems/ai.hpp"
#include "systems/combat.hpp"
#include "rendering/renderer.hpp"
#include "rendering/particle.hpp"
#include "scripting/lua_bridge.hpp"
#include "raylib.h"

// [Ne yapıyor] EntityDef'i entity üzerine kopyalar; team ve position dışındaki her şey Lua'dan gelir.
static void applyDef(Entity& e, const EntityDef& def) {
    e.hp = e.maxHp   = def.hp;
    e.speed          = def.speed;
    e.damage         = def.damage;
    e.radius         = def.radius;
    e.attackRange    = def.attackRange;
    e.attackCooldown = def.attackCooldown;
    e.attackTimer    = 0.0f;
    e.color          = def.color;
}

void Game::spawnEntities() {
    EntityDef squareDef   = LuaBridge::load("scripts/entities/square.lua");
    EntityDef circleDef   = LuaBridge::load("scripts/entities/circle.lua");
    EntityDef triangleDef = LuaBridge::load("scripts/entities/triangle.lua");

    for (int i = 0; i < 4; i++) {
        Vector2 pos = { (float)GetRandomValue(60, 220), (float)GetRandomValue(60, 660) };
        Entity& e = entityManager.Spawn(EntityShape::SQUARE, Team::Red, pos);
        applyDef(e, squareDef);
    }
    for (int i = 0; i < 4; i++) {
        Vector2 pos = { (float)GetRandomValue(1060, 1220), (float)GetRandomValue(60, 660) };
        Entity& e = entityManager.Spawn(EntityShape::CIRCLE, Team::Blue, pos);
        applyDef(e, circleDef);
    }
    for (int i = 0; i < 3; i++) {
        Vector2 pos = { (float)GetRandomValue(480, 800), (float)GetRandomValue(40, 160) };
        Entity& e = entityManager.Spawn(EntityShape::TRIANGLE, Team::Green, pos);
        applyDef(e, triangleDef);
    }
    audio.PlaySpawn();
}

void Game::reset() {
    entityManager.Clear();
    particles.clear();
    gameOver    = false;
    shakeTimer  = 0.0f;
    spawnEntities();
}

void Game::Init() {
    audio.Init();
    spawnEntities();
}

// [Sistem sırası]
// AI → Physics → Collision → CheckDeaths → ölüm efektleri → kazanan tespiti → shake
void Game::Update(float dt) {
    if (IsKeyPressed(KEY_D)) debugDraw = !debugDraw;
    if (IsKeyPressed(KEY_R)) { reset(); return; }
    if (gameOver) return;

    AI::Update(entityManager.GetAll(), dt);
    Physics::Update(entityManager.GetAll(), dt);
    Collision::Update(entityManager.GetAll());
    Combat::CheckDeaths(entityManager.GetAll());

    // DEAD entity: particle patlat, ekranı sars, sesi çal
    for (auto& e : entityManager.GetAll()) {
        if (e.active && e.state == EntityState::DEAD) {
            ParticleSystem::Spawn(particles, e.position, e.color, 14);
            audio.PlayDeath();
            e.active   = false;
            shakeTimer = 0.28f;  // ölüm anında shake başlar
            shakeMag   = 7.0f;
        }
    }

    for (auto& e : entityManager.GetAll()) {
        if (e.active && e.state == EntityState::ATTACKING) {
            audio.PlayHit();
            break;
        }
    }

    // Kazanan tespiti: sadece bir takımın aktif entity'si kaldıysa
    bool redAlive = false, blueAlive = false, greenAlive = false;
    for (auto& e : entityManager.GetAll()) {
        if (!e.active) continue;
        if (e.team == Team::Red)   redAlive   = true;
        if (e.team == Team::Blue)  blueAlive  = true;
        if (e.team == Team::Green) greenAlive = true;
    }
    int aliveTeams = (int)redAlive + (int)blueAlive + (int)greenAlive;
    if (aliveTeams == 1) {
        gameOver   = true;
        winnerTeam = redAlive ? Team::Red : blueAlive ? Team::Blue : Team::Green;
    }

    // [Screen shake mantığı] shakeTimer sıfıra ulaşana kadar her frame
    // Render'da rastgele offset uygulanır. Burada sadece zamanlayıcı azaltılır.
    if (shakeTimer > 0.0f) shakeTimer -= dt;

    audio.Update(dt);
    ParticleSystem::Update(particles, dt);
}

void Game::Render() {
    // [Ne yapıyor] shakeTimer aktifken kamera rastgele offset alır — ekran titrer.
    // [Neden Camera2D] Tüm dünya koordinatlarını taşımak yerine kamerayı kaydırmak yeterli.
    Camera2D cam = {};
    cam.zoom = 1.0f;
    if (shakeTimer > 0.0f) {
        cam.offset = {
            (float)GetRandomValue(-(int)shakeMag, (int)shakeMag),
            (float)GetRandomValue(-(int)shakeMag, (int)shakeMag)
        };
    }

    BeginMode2D(cam);
        ParticleSystem::Draw(particles);
        Renderer::DrawEntities(entityManager.GetAll());
        Renderer::DrawHpBars(entityManager.GetAll());
        if (debugDraw) Renderer::DrawDebug(entityManager.GetAll());
    EndMode2D();

    // UI — kamera dışında: shake etkilemesin
    drawUI();
}

void Game::drawUI() {
    // Skor: her takımın kalan savaşçı sayısı
    int redCount = 0, blueCount = 0, greenCount = 0;
    for (auto& e : entityManager.GetAll()) {
        if (!e.active) continue;
        if (e.team == Team::Red)   redCount++;
        if (e.team == Team::Blue)  blueCount++;
        if (e.team == Team::Green) greenCount++;
    }

    DrawText(TextFormat("Kare  (K): %d", redCount),   10, 10, 20, RED);
    DrawText(TextFormat("Daire (M): %d", blueCount),  10, 36, 20, BLUE);
    DrawText(TextFormat("Ucgen (Y): %d", greenCount), 10, 62, 20, GREEN);
    DrawText("D = hitbox | R = yeniden basla", 10, 695, 16, DARKGRAY);

    if (!gameOver) return;

    // Yarı saydam overlay
    DrawRectangle(0, 0, 1280, 720, {0, 0, 0, 160});

    const char* winText = (winnerTeam == Team::Red)   ? "KARE TAKIMI KAZANDI!" :
                          (winnerTeam == Team::Blue)   ? "DAIRE TAKIMI KAZANDI!" :
                                                         "UCGEN TAKIMI KAZANDI!";
    Color winColor = (winnerTeam == Team::Red) ? RED : (winnerTeam == Team::Blue) ? BLUE : GREEN;

    int textW = MeasureText(winText, 52);
    DrawText(winText, (1280 - textW) / 2, 300, 52, winColor);

    int hintW = MeasureText("R = Yeniden Oyna", 28);
    DrawText("R = Yeniden Oyna", (1280 - hintW) / 2, 380, 28, WHITE);
}

void Game::Shutdown() {
    audio.Shutdown();
}
