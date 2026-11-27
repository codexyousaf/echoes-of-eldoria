// src/shared/ui.h - window, fonts, colours, layout and drawing helpers. Owner: D
//
// Every screen draws on a FIXED 1280 x 720 canvas. ui::begin() / ui::end() scale that canvas
// to any window size (maximised, resized, or full screen with F11) and correct the mouse
// position, so nobody has to think about the real screen size.
//
// Main loop of main.cpp and of every demo:
//     ui::init("title");
//     while (!WindowShouldClose()) { ui::begin();  ...draw everything...;  ui::end(); }
//     ui::shutdown();
// Do NOT call BeginDrawing / EndDrawing yourself any more.
#pragma once
#include "raylib.h"
#include <cmath>
#include <string>

namespace ui {

// ---------- canvas size, font sizes, layout ----------
const int WIN_W = 1280;
const int WIN_H = 720;

const int FONT_SMALL = 18;
const int FONT_BODY  = 22;
const int FONT_TITLE = 30;

// Layout (story, battle and ending screens use MAIN_AREA; title, codex and game over use the full canvas)
const Rectangle TOP_BAR     = {0, 0, 1280, 48};
const Rectangle MAIN_AREA   = {12, 58, 884, 462};
const Rectangle PLAYER_AREA = {908, 58, 360, 260};
const Rectangle QUEST_AREA  = {908, 328, 360, 192};
const Rectangle LOG_AREA    = {12, 530, 1256, 178};

// ---------- colours: a night sky with one warm dawn colour ----------
// (named COL_ so they never clash with raylib colour macros)
const Color COL_BG     = {14, 16, 36, 255};      // night
const Color COL_BG2    = {40, 26, 66, 255};      // dusk violet near the horizon
const Color COL_PANEL  = {24, 27, 58, 235};
const Color COL_BORDER = {82, 76, 140, 255};
const Color COL_TEXT   = {239, 231, 212, 255};   // parchment
const Color COL_DIM    = {154, 151, 184, 255};
const Color COL_GOLD   = {240, 185, 91, 255};    // dawn: the one accent
const Color COL_HP     = {91, 201, 138, 255};
const Color COL_ENEMY  = {217, 100, 90, 255};

// ---------- internal state (header-only, C++17 inline variables) ----------
inline RenderTexture2D canvas = {};
inline Font fontTitle = {};
inline Font fontBody  = {};
inline bool ready = false;          // true after init()

inline Font titleFont() { return ready ? fontTitle : GetFontDefault(); }
inline Font bodyFont()  { return ready ? fontBody  : GetFontDefault(); }
inline float spacing(int size) { return size * 0.04f; }

// ---------- window ----------
inline void init(const char* windowTitle) {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(WIN_W, WIN_H, windowTitle);
    SetWindowMinSize(640, 360);
    SetExitKey(KEY_NULL);                       // Esc must not close the game; the X button does
    SetTargetFPS(60);
    MaximizeWindow();                           // start as big as the screen allows

    fontTitle = LoadFontEx("assets/fonts/UncialAntiqua-Regular.ttf", 72, nullptr, 0);
    fontBody  = LoadFontEx("assets/fonts/Almendra-Regular.ttf", 48, nullptr, 0);
    // If a font file is missing raylib falls back to its default font, so the game still runs.
    if (fontTitle.texture.id != GetFontDefault().texture.id) SetTextureFilter(fontTitle.texture, TEXTURE_FILTER_BILINEAR);
    if (fontBody.texture.id  != GetFontDefault().texture.id) SetTextureFilter(fontBody.texture,  TEXTURE_FILTER_BILINEAR);

    canvas = LoadRenderTexture(WIN_W, WIN_H);
    SetTextureFilter(canvas.texture, TEXTURE_FILTER_BILINEAR);
    ready = true;
}

inline void shutdown() {
    if (!ready) return;
    UnloadRenderTexture(canvas);
    if (fontTitle.texture.id != GetFontDefault().texture.id) UnloadFont(fontTitle);
    if (fontBody.texture.id  != GetFontDefault().texture.id) UnloadFont(fontBody);
    ready = false;
    CloseWindow();
}

// How much the 1280 x 720 canvas is enlarged to fit the real window.
inline float scale() {
    float sx = (float)GetScreenWidth()  / (float)WIN_W;
    float sy = (float)GetScreenHeight() / (float)WIN_H;
    return (sx < sy) ? sx : sy;
}

// Start of a frame: F11 toggles full screen, the mouse is mapped into canvas coordinates.
inline void begin() {
    if (IsKeyPressed(KEY_F11)) ToggleBorderlessWindowed();
    float s = scale();
    SetMouseOffset(-(int)((GetScreenWidth()  - WIN_W * s) * 0.5f),
                   -(int)((GetScreenHeight() - WIN_H * s) * 0.5f));
    SetMouseScale(1.0f / s, 1.0f / s);
    BeginTextureMode(canvas);
    ClearBackground(COL_BG);
}

// End of a frame: draw the canvas centred and enlarged, with dark bars if the window shape differs.
inline void end() {
    EndTextureMode();
    float s = scale();
    float w = WIN_W * s, h = WIN_H * s;
    BeginDrawing();
    ClearBackground(Color{6, 7, 18, 255});
    DrawTexturePro(canvas.texture,
                   Rectangle{0, 0, (float)WIN_W, -(float)WIN_H},          // negative height: render textures are upside down
                   Rectangle{(GetScreenWidth() - w) * 0.5f, (GetScreenHeight() - h) * 0.5f, w, h},
                   Vector2{0, 0}, 0.0f, WHITE);
    EndDrawing();
}

// ---------- text ----------
inline Vector2 measure(const std::string& s, int size, bool useTitleFont = false) {
    return MeasureTextEx(useTitleFont ? titleFont() : bodyFont(), s.c_str(), (float)size, spacing(size));
}

// Body font text at (x, y).
inline void text(const std::string& s, float x, float y, int size, Color c) {
    DrawTextEx(bodyFont(), s.c_str(), Vector2{x, y}, (float)size, spacing(size), c);
}

// Text centred inside a rectangle (both ways).
inline void textCentered(const std::string& s, Rectangle box, int size, Color c, bool useTitleFont = false) {
    Vector2 m = measure(s, size, useTitleFont);
    DrawTextEx(useTitleFont ? titleFont() : bodyFont(), s.c_str(),
               Vector2{box.x + (box.width - m.x) * 0.5f, box.y + (box.height - m.y) * 0.5f},
               (float)size, spacing(size), c);
}

// Panel / section heading in the title font, dawn gold.
inline void drawHeading(const std::string& s, float x, float y, int size = FONT_TITLE) {
    DrawTextEx(titleFont(), s.c_str(), Vector2{x, y}, (float)size, spacing(size), COL_GOLD);
}

// Word-wrapped body text inside box.width. Returns the y position after the last line.
inline float drawWrappedText(const std::string& str, Rectangle box, int fontSize, Color color) {
    float y = box.y;
    float lineH = fontSize * 1.45f;
    std::string line, word;
    for (size_t i = 0; i <= str.size(); ++i) {
        char c = (i < str.size()) ? str[i] : ' ';
        if (c == ' ' || c == '\n') {
            if (!word.empty()) {
                std::string test = line.empty() ? word : line + " " + word;
                if (!line.empty() && measure(test, fontSize).x > box.width) {
                    text(line, box.x, y, fontSize, color);
                    y += lineH;
                    line = word;
                } else {
                    line = test;
                }
                word.clear();
            }
            if (c == '\n' && !line.empty()) {      // hard line break
                text(line, box.x, y, fontSize, color);
                y += lineH;
                line.clear();
            }
        } else {
            word += c;
        }
    }
    if (!line.empty()) {
        text(line, box.x, y, fontSize, color);
        y += lineH;
    }
    return y;
}

// ---------- shapes and widgets ----------
// DrawRectangleRounded wants a ratio, not pixels: this turns a corner radius in pixels into that ratio.
inline float radiusRatio(Rectangle r, float radius) {
    float m = ((r.width < r.height) ? r.width : r.height) * 0.5f;
    return (m > 0.0f) ? radius / m : 0.0f;
}

inline void drawPanel(Rectangle r) {
    DrawRectangleRounded(r, radiusRatio(r, 10), 10, COL_PANEL);
    DrawRectangleRoundedLinesEx(r, radiusRatio(r, 10), 10, 2.0f, COL_BORDER);
}

// Pill-shaped bar with a soft highlight and "value / max" written inside.
inline void drawBar(Rectangle r, int value, int maxValue, Color fill, bool showNumbers = true) {
    DrawRectangleRounded(r, 1.0f, 12, Color{10, 11, 28, 255});
    float f = (maxValue > 0) ? (float)value / (float)maxValue : 0.0f;
    if (f < 0.0f) f = 0.0f;
    if (f > 1.0f) f = 1.0f;
    if (f > 0.0f) {
        Rectangle fr = {r.x, r.y, r.width * f, r.height};
        if (fr.width < r.height) fr.width = r.height;        // keep the round end visible
        DrawRectangleRounded(fr, 1.0f, 12, fill);
        DrawRectangleRounded(Rectangle{fr.x + 4, fr.y + 3, fr.width - 8, fr.height * 0.3f}, 1.0f, 8, ColorAlpha(WHITE, 0.18f));
    }
    DrawRectangleRoundedLinesEx(r, 1.0f, 12, 2.0f, COL_BORDER);
    if (showNumbers) textCentered(TextFormat("%d / %d", value, maxValue), r, FONT_SMALL, COL_TEXT);
}

// Button. Lifts and glows gold when the mouse is over it, darkens while pressed.
// Returns true on the frame the mouse is released over it. enabled = false draws it greyed out (locked choice).
inline bool button(Rectangle r, const std::string& label, bool enabled = true) {
    Vector2 m = GetMousePosition();
    bool hover = enabled && CheckCollisionPointRec(m, r);
    bool down  = hover && IsMouseButtonDown(MOUSE_BUTTON_LEFT);
    Rectangle d = r;
    if (hover && !down) d.y -= 2;                            // small lift
    Color fill = !enabled ? Color{20, 22, 44, 210}
               : down     ? Color{58, 50, 100, 255}
               : hover    ? Color{52, 56, 112, 255}
                          : COL_PANEL;
    DrawRectangleRounded(d, radiusRatio(d, 8), 10, fill);
    if (hover) {
        Rectangle g = {d.x - 3, d.y - 3, d.width + 6, d.height + 6};
        DrawRectangleRoundedLinesEx(g, radiusRatio(g, 10), 10, 3.0f, ColorAlpha(COL_GOLD, 0.28f));
    }
    DrawRectangleRoundedLinesEx(d, radiusRatio(d, 8), 10, 2.0f,
                                hover ? COL_GOLD : (enabled ? COL_BORDER : Color{50, 50, 80, 255}));
    textCentered(label, d, FONT_BODY, !enabled ? COL_DIM : (hover ? COL_GOLD : COL_TEXT));
    return hover && IsMouseButtonReleased(MOUSE_BUTTON_LEFT);
}

// ---------- background and title ----------
inline float hash01(int i, int salt) {                       // cheap repeatable "random" number 0..1
    float v = std::sin((float)(i * 127 + salt * 311) * 12.9898f) * 43758.5453f;
    return v - std::floor(v);
}

// Night sky, the faint glow of the Dawn Crystal on the horizon, and slow embers drifting upward.
inline void drawBackdrop(bool embers = true) {
    DrawRectangleGradientV(0, 0, WIN_W, WIN_H, COL_BG, COL_BG2);
    DrawCircleGradient(Vector2{WIN_W * 0.5f, (float)WIN_H + 140.0f}, 640.0f,
                       ColorAlpha(COL_GOLD, 0.24f), ColorAlpha(COL_GOLD, 0.0f));
    if (!embers) return;
    float t = (float)GetTime();
    for (int i = 0; i < 46; ++i) {
        float speed = 8.0f + 18.0f * hash01(i, 1);
        float x = hash01(i, 2) * WIN_W + std::sin(t * 0.4f + (float)i) * 14.0f;
        float y = std::fmod(hash01(i, 3) * WIN_H - t * speed, (float)WIN_H);
        if (y < 0.0f) y += (float)WIN_H;
        float twinkle = 0.5f + 0.5f * std::sin(t * (0.8f + hash01(i, 4)) + (float)i);
        float radius = 1.0f + 1.8f * hash01(i, 5);
        float alpha = 0.12f + 0.5f * twinkle * (y / (float)WIN_H);     // brighter near the horizon
        DrawCircleV(Vector2{x, y}, radius, ColorAlpha(COL_GOLD, alpha));
    }
}

// Big title in the title font with a slowly pulsing golden glow. Used once, on the title screen.
inline void drawGlowTitle(const std::string& s, float centerX, float y, int size) {
    Vector2 m = measure(s, size, true);
    float x = centerX - m.x * 0.5f;
    float pulse = 0.14f + 0.06f * std::sin((float)GetTime() * 1.6f);
    for (int i = 0; i < 8; ++i) {
        float a = (float)i * 0.7853982f;
        DrawTextEx(titleFont(), s.c_str(), Vector2{x + std::cos(a) * 3.5f, y + std::sin(a) * 3.5f},
                   (float)size, spacing(size), ColorAlpha(COL_GOLD, pulse));
    }
    DrawTextEx(titleFont(), s.c_str(), Vector2{x, y}, (float)size, spacing(size), COL_TEXT);
}

}  // namespace ui
