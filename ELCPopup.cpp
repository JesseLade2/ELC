#include "ELCPopup.h"
#include <raylib.h>

namespace ELC {
namespace Popup {

// Global popup state (single popup at a time)
static Gui popupGui;
static bool popupActive = false;
static std::string resultText;
static bool resultBool;
static bool resultReady = false;
static std::function<void()> waitForClose;

static Rectangle GetScreenCenterRect(float width, float height) {
    Vec2 mouse = Core::GetMousePosition(); // Dummy call to init
    int sw = ::GetScreenWidth();
    int sh = ::GetScreenHeight();
    float x = (sw - width) / 2.0f;
    float y = (sh - height) / 2.0f;
    return {x, y, width, height};
}

static void DrawModalOverlay() {
    if (!popupActive) return;
    
    // Semi-transparent overlay - FIXED: Use raw raylib Color
    ::DrawRectangle(0, 0, ::GetScreenWidth(), ::GetScreenHeight(), (Color){0, 0, 0, 180});
    
    popupGui.Draw();
}

void Alert(const std::string& message) {
    popupActive = true;
    resultReady = false;
    popupGui.widgets.clear();
    
    // Centered popup ~400x200
    Rectangle bgRect = GetScreenCenterRect(400, 200);
    
    // Message text widget (non-interactive)
    auto& msgLabel = popupGui.emplace_back<Button>(Vec2{bgRect.x + 20, bgRect.y + 40}, 
                                                   Vec2{bgRect.width - 40, 60}, message);
    msgLabel.onClick = nullptr; // No click
    
    // OK button
    auto& okBtn = popupGui.emplace_back<Button>(Vec2{bgRect.x + 120, bgRect.y + 140}, 
                                                Vec2{160, 40}, "OK");
    okBtn.onClick = [&]() {
        popupActive = false;
        resultReady = true;
    };
    
    // Wait loop (non-blocking, call in main loop)
    while (popupActive && !Core::ShouldClose()) {
        Core::BeginDrawing();
        Core::ClearBackground(ELC_BLACK);
        DrawModalOverlay();
        Core::EndDrawing();
        popupGui.Update();  // FIXED: Single draw loop
    }
}

bool PromptAnswer(const std::string& message, const std::string& yesText, const std::string& noText) {
    popupActive = true;
    resultReady = false;
    popupGui.widgets.clear();
    
    Rectangle bgRect = GetScreenCenterRect(420, 220);
    
    // Message
    auto& msgLabel = popupGui.emplace_back<Button>(Vec2{bgRect.x + 20, bgRect.y + 40}, 
                                                   Vec2{bgRect.width - 40, 60}, message);
    msgLabel.onClick = nullptr;
    
    // Yes/No buttons
    float btnW = 100, btnH = 40, btnGap = 20;
    float btnY = bgRect.y + 140;
    auto& yesBtn = popupGui.emplace_back<Button>(Vec2{bgRect.x + 80, btnY}, 
                                                 Vec2{btnW, btnH}, yesText);
    yesBtn.onClick = [&]() {
        resultBool = true;
        popupActive = false;
        resultReady = true;
    };
    
    auto& noBtn = popupGui.emplace_back<Button>(Vec2{bgRect.x + 240, btnY}, 
                                                Vec2{btnW, btnH}, noText);
    noBtn.onClick = [&]() {
        resultBool = false;
        popupActive = false;
        resultReady = true;
    };
    
    // Wait loop
    while (popupActive && !Core::ShouldClose()) {
        Core::BeginDrawing();
        Core::ClearBackground(ELC_BLACK);
        DrawModalOverlay();
        Core::EndDrawing();
        popupGui.Update();
    }
    
    return resultBool;
}

std::string PromptText(const std::string& message, const std::string& placeholder, const std::string& confirmText) {
    popupActive = true;
    resultReady = false;
    resultText.clear();
    popupGui.widgets.clear();
    
    Rectangle bgRect = GetScreenCenterRect(450, 260);
    
    // Message
    auto& msgLabel = popupGui.emplace_back<Button>(Vec2{bgRect.x + 20, bgRect.y + 30}, 
                                                   Vec2{bgRect.width - 40, 50}, message);
    msgLabel.onClick = nullptr;
    
    // Text input
    auto& textBox = popupGui.emplace_back<TextBox>(Vec2{bgRect.x + 30, bgRect.y + 90}, 
                                                   Vec2{bgRect.width - 60, 40}, placeholder);
    
    // Confirm button
    auto& confirmBtn = popupGui.emplace_back<Button>(Vec2{bgRect.x + 150, bgRect.y + 170}, 
                                                     Vec2{150, 45}, confirmText);
    confirmBtn.onClick = [&]() {
        resultText = textBox.text;
        popupActive = false;
        resultReady = true;
    };
    
    // ESC/Cancel handling - FIXED: Use raw raylib IsKeyPressed
    waitForClose = [&]() {
        if (::IsKeyPressed(KEY_ESCAPE)) {
            resultText.clear();
            popupActive = false;
            resultReady = true;
        }
    };
    
    // Wait loop with text input
    while (popupActive && !Core::ShouldClose()) {
        int ch = Core::GetCharPressed();
        int key = Core::GetKeyPressed();
        if (ch) textBox.OnChar(ch);
        if (key) textBox.OnKeyDown(key);
        
        Core::BeginDrawing();
        Core::ClearBackground(ELC_BLACK);
        DrawModalOverlay();
        Core::EndDrawing();
        popupGui.Update();
        if (waitForClose) waitForClose();
    }
    
    return resultText;
}

} // Popup
} // ELC
