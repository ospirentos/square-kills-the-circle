#pragma once

// Ana oyun state'ini ve sistemleri koordine eden sınıf.
// main.cpp yalnızca bu sınıfla konuşur; diğer sistemleri doğrudan çağırmaz.
class Game {
public:
    void Init();
    void Update(float dt);
    void Render();
    void Shutdown();
};
