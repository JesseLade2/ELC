#include "ELCGui.h"
#include <raylib.h>

void ELC::Gui::Update() {
    for (auto& w : widgets) w->Update();
}

void ELC::Gui::Draw() {
    for (auto& w : widgets) w->Draw();
}

void ELC::Button::Update() {
    Vector2 mouse = ELC::Core::ToVector2(ELC::Core::GetMousePosition());
    if (CheckCollisionPointRec(mouse, rect) && ELC::Core::IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if (onClick) onClick();
    }
}

void ELC::Button::Draw() {
    Vector2 mouse = ELC::Core::ToVector2(ELC::Core::GetMousePosition());
    bool hover = CheckCollisionPointRec(mouse, rect);
    
    ELC_Color bg = hover ? ELC::ELC_LIGHTGRAY : ELC::ELC_GRAY;
    ELC::Core::DrawRectangle(rect.x, rect.y, rect.width, rect.height, bg);
    ELC::Core::DrawRectangleLinesEx(rect.x, rect.y, rect.width, rect.height, 2.0f, ELC::ELC_DARKGRAY);
    
    ELC::Core::DrawText(text, rect.x + 10, rect.y + (rect.height - 20) / 2, 16, ELC::ELC_BLACK);
}

void ELC::TextBox::Update() {
    Vector2 mouse = ELC::Core::ToVector2(ELC::Core::GetMousePosition());
    
    if (CheckCollisionPointRec(mouse, rect) && ELC::Core::IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        focused = true;
    }
    if (!CheckCollisionPointRec(mouse, rect) && ELC::Core::IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        focused = false;
    }
}

void ELC::TextBox::Draw() {
    ELC_Color bg = focused ? ELC::ELC_RAYWHITE : ELC::ELC_LIGHTGRAY;
    ELC::Core::DrawRectangle(rect.x, rect.y, rect.width, rect.height, bg);
    ELC::Core::DrawRectangleLinesEx(rect.x, rect.y, rect.width, rect.height, 2.0f, ELC::ELC_GRAY);
    
    std::string display = text.empty() ? placeholder : text;
    ELC_Color textColor = text.empty() ? ELC::ELC_DARKGRAY : ELC::ELC_BLACK;
    
    ELC::Core::DrawText(display, rect.x + 8, rect.y + (rect.height - 20) / 2, 16, textColor);
    
    if (focused && ((int)(GetTime() * 2)) % 2) {
        float textWidth = ELC::Core::MeasureText(display, 16).x;
        ELC::Core::DrawRectangle(rect.x + 8 + textWidth, rect.y + 8, 2, (int)(rect.height - 16), ELC::ELC_BLACK);
    }
}

void ELC::TextBox::OnChar(int key) {
    if (focused && key >= 32 && key <= 125 && text.size() < 100) {
        text += (char)key;
    }
}

void ELC::TextBox::OnKeyDown(int key) {
    if (focused) {
        if (key == KEY_BACKSPACE && !text.empty()) text.pop_back();
        else if (key == KEY_ENTER) focused = false;
    }
}
