#include "ELC.h"
#include <raylib.h>
#include <iostream>

namespace ELC {

bool Core::Init(int width, int height, const std::string& title) {
    std::cout << "🔧 ELC::Core::Init() CALLED: " << width << "x" << height << " \"" << title << "\"" << std::endl;
    ::InitWindow(width, height, title.c_str());
    ::SetWindowPosition(100, 100);
    ::SetWindowState(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_ALWAYS_RUN);
    ::SetTargetFPS(60);
    std::cout << "  ✅ ELC Init SUCCESS!" << std::endl;
    return true;
}

void Core::Close() { ::CloseWindow(); }

void Core::BeginDrawing() { ::BeginDrawing(); }
void Core::EndDrawing() { ::EndDrawing(); }

void Core::ClearBackground(ELC_Color color) {
    ::ClearBackground({color.r, color.g, color.b, color.a});
}

Vec2 Core::GetMousePosition() {
    Vector2 m = ::GetMousePosition();
    return {m.x, m.y};
}

bool Core::IsMouseButtonPressed(int button) {
    return ::IsMouseButtonPressed(button);
}

int Core::GetCharPressed() { return ::GetCharPressed(); }
int Core::GetKeyPressed() { return ::GetKeyPressed(); }
bool Core::ShouldClose() { return ::WindowShouldClose(); }

void Core::DrawRectangle(float x, float y, float w, float h, ELC_Color color) {
    ::DrawRectangle((int)x, (int)y, (int)w, (int)h, {color.r, color.g, color.b, color.a});
}

void Core::DrawRectangleLinesEx(float x, float y, float w, float h, float lineThick, ELC_Color color) {
    ::DrawRectangleLinesEx({x, y, w, h}, lineThick, {color.r, color.g, color.b, color.a});
}

float Core::GetFrameTime() {
    return ::GetFrameTime();
}

void Core::DrawText(const std::string& text, float x, float y, int fontSize, ELC_Color color) {
    if (!text.empty()) {
        ::DrawText(text.c_str(), (int)x, (int)y, fontSize, {color.r, color.g, color.b, color.a});
    }
}

Vec2 Core::MeasureText(const std::string& text, int fontSize) {
    Vector2 size = ::MeasureTextEx(::GetFontDefault(), text.c_str(), (float)fontSize, 1);
    return {size.x, size.y};
}

Vector2 Core::ToVector2(const Vec2& v) { return {v.x, v.y}; }
ELC_Color Core::ToELC_Color(Color c) { return {c.r, c.g, c.b, c.a}; }

} // namespace ELC
