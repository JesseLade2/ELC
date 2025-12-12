#include "ELCFilePicker.h"
#include "ELC.h"
#include <filesystem>
#include <algorithm>

namespace fs = std::filesystem;

namespace ELC {

    FilePickerResult FilePicker::Open(const std::string& title,
        const std::string& description,
        const std::vector<std::string>& filters,
        bool pickFolder,
        const std::string& defaultPath) {
FilePickerResult result;
currentPath = defaultPath.empty() ? fs::current_path().string() : defaultPath;
RefreshDirectory();

float scrollOffset = 0.0f;
float listHeight = 350.0f;
float maxScroll = 0.0f;

bool done = false;
while (!done && !Core::ShouldClose()) {
Core::BeginDrawing();
Core::ClearBackground({220,220,220,255});

// Calculate max scroll
int totalItems = (int)folders.size() + (int)files.size();
maxScroll = std::max(0.0f, totalItems * 24.0f - listHeight);
scrollOffset = std::clamp(scrollOffset, 0.0f, maxScroll);

// Scroll wheel
float wheel = GetMouseWheelMove();
scrollOffset -= wheel * 24.0f;
scrollOffset = std::clamp(scrollOffset, 0.0f, maxScroll);

DrawFilePicker(title, description, filters, pickFolder, scrollOffset, listHeight);

Vec2 mousePos = Core::GetMousePosition();
Vector2 mouse = Core::ToVector2(mousePos);

// Mouse selection
int idx = 0;
float listStartY = 120.0f;
for (auto& f : folders) {
    float y = listStartY + idx * 24 - scrollOffset;
    if (y >= listStartY && y <= listStartY + listHeight) {
        if (CheckCollisionPointRec(mouse, {60,y,500,22})) {
            if (Core::IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                selectedIndex = idx; 
                if (f == "..") currentPath = fs::path(currentPath).parent_path().string();
                else currentPath = fs::path(currentPath) / f;
                inputText.clear();
                RefreshDirectory();
                break; 
            }
        }
    }
    idx++;
}

for (auto& f : files) {
    if (!MatchFilter(f, filters)) continue;
    float y = listStartY + idx * 24 - scrollOffset;
    if (y >= listStartY && y <= listStartY + listHeight) {
        if (CheckCollisionPointRec(mouse, {60,y,500,22})) {
            if (Core::IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                selectedIndex = idx;
            }
        }
    }
    idx++;
}


// Buttons on the right side of the list
float buttonW = 70, buttonH = 25;
float buttonX = 580, buttonY = 120;

if (DrawButton(buttonX, buttonY, buttonW, buttonH, "OPEN")) {
if (selectedIndex >= 0) {
std::vector<std::string> allItems = folders;
for (auto& f : files) if (MatchFilter(f, filters)) allItems.push_back(f);
result.path = fs::path(currentPath) / allItems[selectedIndex];
result.cancelled = false;
done = true;
} else if (!inputText.empty()) {
result.path = fs::path(currentPath) / inputText;
result.cancelled = false;
done = true;
}
}
if (DrawButton(buttonX, buttonY + 40, buttonW, buttonH, "CANCEL")) {
done = true;
result.cancelled = true;
}

// Keyboard input
int key;
while ((key = Core::GetCharPressed()) != 0) {
if (key >= 32 && key <= 125) inputText += (char)key;
}
if (Core::GetKeyPressed() == KEY_BACKSPACE && !inputText.empty()) inputText.pop_back();

Core::EndDrawing();
}

return result;
}
void FilePicker::RefreshDirectory() {
    files.clear(); folders.clear();
    for (auto& entry : fs::directory_iterator(currentPath)) {
        if (entry.is_directory()) folders.push_back(entry.path().filename().string());
        else files.push_back(entry.path().filename().string());
    }
    std::sort(folders.begin(), folders.end());
    std::sort(files.begin(), files.end());

    // 🔹 ADD ".." for parent navigation if not root
    if (fs::path(currentPath).has_parent_path()) {
        folders.insert(folders.begin(), "..");
    }
}


bool FilePicker::MatchFilter(const std::string& filename, const std::vector<std::string>& filters) {
    if (filters.empty()) return true;
    std::string ext = fs::path(filename).extension().string();
    std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
    for (auto& f : filters) {
        std::string filter = f;
        std::transform(filter.begin(), filter.end(), filter.begin(), ::tolower);
        if (filter == ext) return true;
    }
    return false;
}

void FilePicker::DrawFilePicker(const std::string& title,
    const std::string& description,
    const std::vector<std::string>& filters,
    bool pickFolder,
    float scrollOffset,
    float listHeight) {
float x = 50, y = 50, w = 700, h = 450;
Core::DrawRectangle(x, y, w, h, {240,240,240,255});
Core::DrawRectangleLinesEx(x, y, w, h, 2, {100,100,100,255});
Core::DrawText(title, x+10, y+10, 20, {0,0,0,255});
Core::DrawText(description, x+10, y+40, 16, {50,50,50,255});

float listStartY = y + 80;
int idx = 0;

for (auto& f : folders) {
float yPos = listStartY + idx * 24 - scrollOffset;
if (yPos >= listStartY && yPos <= listStartY + listHeight) {
if (selectedIndex == idx) Core::DrawRectangle(x+10, yPos-2, w-120, 22, {100,150,255,255});
Core::DrawText(f.c_str(), x+40, yPos, 16, {0,0,0,255});
DrawIcon("icons/folder.png", x+10, yPos, 20);
}
idx++;
}

for (auto& f : files) {
if (!MatchFilter(f, filters)) continue;
float yPos = listStartY + idx * 24 - scrollOffset;
if (yPos >= listStartY && yPos <= listStartY + listHeight) {
if (selectedIndex == idx) Core::DrawRectangle(x+10, yPos-2, w-120, 22, {100,150,255,255});
Core::DrawText(f.c_str(), x+40, yPos, 16, {0,0,0,255});
DrawIcon("icons/file.png", x+10, yPos, 20);
}
idx++;
}

// Input box at bottom
Core::DrawRectangle(x+10, y+h-60, w-20, 30, {255,255,255,255});
Core::DrawRectangleLinesEx(x+10, y+h-60, w-20, 30, 2, {100,100,100,255});
Core::DrawText(inputText.empty() ? "Enter filename..." : inputText, x+15, y+h-55, 16, {0,0,0,255});
}


void FilePicker::DrawIcon(const std::string& path, float x, float y, float size) {
    static std::unordered_map<std::string, Image> iconCache;
    if (iconCache.find(path) == iconCache.end()) {
        Image img(path);
        iconCache[path] = img; // store ELC::Image directly
    }
    Image& img = iconCache[path];
    if (img.IsLoaded()) {
        float scale = size / std::max((float)img.width, (float)img.height);
        img.DrawScaled(x, y, scale, {255,255,255,255});
    }
}

bool FilePicker::DrawButton(float x, float y, float w, float h, const std::string& text) {
    Vec2 mousePos = Core::GetMousePosition();
    Vector2 mouse = Core::ToVector2(mousePos);
    bool hover = CheckCollisionPointRec(mouse, {x,y,w,h});
    ELC_Color bg = hover ? ELC_Color{180,180,255,255} : ELC_Color{200,200,200,255};
Core::DrawRectangle(x, y, w, h, bg);
    Core::DrawRectangleLinesEx(x, y, w, h, 2, {100,100,100,255});
    Core::DrawText(text, x+10, y+5, 16, {0,0,0,255});
    return hover && Core::IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}

} // namespace ELC
