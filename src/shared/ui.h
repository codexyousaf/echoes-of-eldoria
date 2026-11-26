// src/shared/ui.h - colours, layout, helpers. Owner: D (frozen on Day 1)
#pragma once
#include "raylib.h"
#include <string>

namespace ui {

const int WIN_W = 1000;
const int WIN_H = 650;

// Layout (story, battle and ending screens use MAIN_AREA; title, codex and game over use the full window)
const Rectangle TOP_BAR     = {0, 0, 1000, 40};
const Rectangle MAIN_AREA   = {10, 50, 680, 410};
const Rectangle PLAYER_AREA = {700, 50, 290, 230};
const Rectangle QUEST_AREA  = {700, 290, 290, 170};
const Rectangle LOG_AREA    = {10, 470, 980, 170};

// Dark fantasy colours (named COL_ so they never clash with raylib colour macros)
const Color COL_BG     = {20, 22, 40, 255};
const Color COL_PANEL  = {32, 36, 64, 255};
const Color COL_BORDER = {90, 84, 140, 255};
const Color COL_TEXT   = {235, 232, 245, 255};
const Color COL_DIM    = {140, 138, 165, 255};
const Color COL_GOLD   = {230, 190, 80, 255};
const Color COL_HP     = {70, 190, 110, 255};
const Color COL_ENEMY  = {200, 70, 70, 255};

inline void drawPanel(Rectangle r) {
    DrawRectangleRec(r, COL_PANEL);
    DrawRectangleLinesEx(r, 2, COL_BORDER);
}

inline void drawBar(Rectangle r, int value, int maxValue, Color fill) {
    DrawRectangleRec(r, Color{50, 50, 70, 255});
    float f = (maxValue > 0) ? (float)value / (float)maxValue : 0.0f;
    if (f < 0.0f) f = 0.0f;
    if (f > 1.0f) f = 1.0f;
    DrawRectangleRec(Rectangle{r.x, r.y, r.width * f, r.height}, fill);
    DrawRectangleLinesEx(r, 2, COL_TEXT);
}

// Word-wrapped text inside box.width. Returns the y position after the last line.
inline float drawWrappedText(const std::string& text, Rectangle box, int fontSize, Color color) {
    float y = box.y;
    float lineH = fontSize * 1.4f;
    std::string line, word;
    for (size_t i = 0; i <= text.size(); ++i) {
        char c = (i < text.size()) ? text[i] : ' ';
        if (c == ' ' || c == '\n') {
            if (!word.empty()) {
                std::string test = line.empty() ? word : line + " " + word;
                if (!line.empty() && MeasureText(test.c_str(), fontSize) > (int)box.width) {
                    DrawText(line.c_str(), (int)box.x, (int)y, fontSize, color);
                    y += lineH;
                    line = word;
                } else {
                    line = test;
                }
                word.clear();
            }
            if (c == '\n' && !line.empty()) {   // hard line break
                DrawText(line.c_str(), (int)box.x, (int)y, fontSize, color);
                y += lineH;
                line.clear();
            }
        } else {
            word += c;
        }
    }
    if (!line.empty()) {
        DrawText(line.c_str(), (int)box.x, (int)y, fontSize, color);
        y += lineH;
    }
    return y;
}

} // namespace ui