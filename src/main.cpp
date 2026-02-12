#include "game.h"

struct AppState {
    int windowedWidth = 1280;
    int windowedHeight = 720;
    bool fullscreen = false;
    bool showOverlay = true;
};

static void ToggleFullscreenMode(AppState& app) {
    if (!app.fullscreen) {
        app.windowedWidth = GetScreenWidth();
        app.windowedHeight = GetScreenHeight();

        const int monitor = GetCurrentMonitor();
        SetWindowSize(GetMonitorWidth(monitor), GetMonitorHeight(monitor));
        ToggleFullscreen();
        app.fullscreen = true;
        return;
    }

    ToggleFullscreen();
    app.fullscreen = false;
    SetWindowSize(app.windowedWidth, app.windowedHeight);
}

static void CycleWindowSize(AppState& app) {
    if (app.fullscreen) return;

    static const int sizes[][2] = {
        {960, 540},
        {1280, 720},
        {1600, 900},
        {1920, 1080},
    };
    const int count = static_cast<int>(sizeof(sizes) / sizeof(sizes[0]));

    const int currentW = GetScreenWidth();
    const int currentH = GetScreenHeight();
    int currentIndex = 0;

    for (int i = 0; i < count; ++i) {
        if (sizes[i][0] == currentW && sizes[i][1] == currentH) {
            currentIndex = i;
            break;
        }
    }

    const int next = (currentIndex + 1) % count;
    app.windowedWidth = sizes[next][0];
    app.windowedHeight = sizes[next][1];
    SetWindowSize(app.windowedWidth, app.windowedHeight);
}

int main() {
    AppState app;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    InitWindow(app.windowedWidth, app.windowedHeight, "bootstrap_ai_raylib");
    SetTargetFPS(60);

    InitGame();

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_F11)) ToggleFullscreenMode(app);
        if (IsKeyPressed(KEY_F5)) CycleWindowSize(app);
        if (IsKeyPressed(KEY_F1)) app.showOverlay = !app.showOverlay;

        const float dt = GetFrameTime();
        UpdateGame(dt);

        BeginDrawing();
        DrawGame();

        if (app.showOverlay) {
            DrawRectangle(16, 16, 420, 134, Fade(BLACK, 0.45f));
            DrawText("Window Controls", 28, 28, 24, LIME);
            DrawText("F11 Fullscreen | F5 Resize | F1 Overlay", 28, 58, 20, RAYWHITE);
            DrawText(TextFormat("Window: %d x %d", GetScreenWidth(), GetScreenHeight()), 28, 86, 20, RAYWHITE);
            DrawText(TextFormat("FPS: %d", GetFPS()), 28, 112, 20, RAYWHITE);
        }

        EndDrawing();
    }

    ShutdownGame();
    CloseWindow();
    return 0;
}
