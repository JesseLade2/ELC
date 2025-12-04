#pragma once
#include <string>
#include <raylib.h>

namespace ELC {
    struct Vec2 {
        float x, y;
    };

    struct ELC_Color {
        unsigned char r, g, b, a;
    };

    // Colors
    static constexpr ELC_Color ELC_GRAY = {170, 170, 170, 255};
    static constexpr ELC_Color ELC_LIGHTGRAY = {200, 200, 200, 255};
    static constexpr ELC_Color ELC_DARKGRAY = {80, 80, 80, 255};
    static constexpr ELC_Color ELC_RAYWHITE = {245, 245, 245, 255};
    static constexpr ELC_Color ELC_BLACK = {0, 0, 0, 255};

    class Core {
    public:
        static float GetFrameTime();
        static bool Init(int width, int height, const std::string& title);
        static void Close();
        static void BeginDrawing();
        static void EndDrawing();
        static void ClearBackground(ELC_Color color);
        static Vec2 GetMousePosition();
        static bool IsMouseButtonPressed(int button);
        static int GetCharPressed();
        static int GetKeyPressed();
        static bool ShouldClose();
        static void DrawRectangle(float x, float y, float w, float h, ELC_Color color);
        static void DrawRectangleLinesEx(float x, float y, float w, float h, float lineThick, ELC_Color color);
        static void DrawText(const std::string& text, float x, float y, int fontSize, ELC_Color color);
        static Vec2 MeasureText(const std::string& text, int fontSize);
        
        // Type converters (DECLARATIONS ONLY)
        static Vector2 ToVector2(const Vec2& v);
        static ELC_Color ToELC_Color(Color c);
    };
}
