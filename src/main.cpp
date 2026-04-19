#include "raylib.h"
#include "game.hpp"

int main() {
    InitWindow(1280, 720, "square-kills-the-circle");
    SetTargetFPS(60);

    Game game;
    game.Init();

    // [Ne yapıyor] Ana game loop — pencere kapanana kadar çalışır.
    // [Neden böyle] WindowShouldClose() hem ESC tuşunu hem pencere X butonunu yakalar.
    // [Mekanikte yeri] Her frame: input al → oyun mantığını güncelle → ekrana çiz.
    while (!WindowShouldClose()) {
        float dt = GetFrameTime(); // saniye cinsinden geçen süre

        game.Update(dt);

        BeginDrawing();
        ClearBackground(DARKGRAY);
        game.Render();
        EndDrawing();
    }

    game.Shutdown();
    CloseWindow();
    return 0;
}
