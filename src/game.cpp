#include "game.h"

// Global state on purpose for easy AI-driven iteration.
MyGame g;

void InitGame() {
    g = {};
}

void UpdateGame(float dt) {
    g.frameCount += 1;
    g.totalTime += dt;
}

void DrawGame() {
    const Color background = {24, 24, 30, 255};
    ClearBackground(background);

    DrawText("No gameplay yet.", 32, 32, 36, RAYWHITE);
    DrawText("Design state and behavior in src/game.cpp.", 32, 80, 24, SKYBLUE);
    DrawText("Window controls are managed in src/main.cpp.", 32, 114, 20, GRAY);
}

void ShutdownGame() {
}
