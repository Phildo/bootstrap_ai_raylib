#ifndef GAME_H
#define GAME_H

#include "raylib.h"

struct MyGame {
    // Keep game-specific runtime state here as the design evolves.
    float totalTime = 0.0f;
    int frameCount = 0;
};

extern MyGame g;

void InitGame();
void UpdateGame(float dt);
void DrawGame();
void ShutdownGame();

#endif
