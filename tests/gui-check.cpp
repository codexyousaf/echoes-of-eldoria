// tests/gui-check.cpp - run with: make gui-check
// A window with a clickable button must open. This proves raylib and raygui work.
#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

int main() {
    InitWindow(640, 360, "Echoes of Eldoria - setup check");
    SetTargetFPS(60);
    int clicks = 0;
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(Color{20, 22, 40, 255});
        DrawText("Setup OK! raylib and raygui work.", 40, 40, 24, RAYWHITE);
        if (GuiButton(Rectangle{40, 120, 200, 48}, "Click me")) clicks++;
        DrawText(TextFormat("Clicks: %d", clicks), 40, 190, 22, GOLD);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}