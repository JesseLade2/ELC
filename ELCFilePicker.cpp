#include "ELCFilePicker.h"
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

namespace ELC {

std::string FilePickerGUI(const std::string& folder,
                          const std::vector<std::string>& filters,
                          const std::string& title,
                          const std::string& description)
{
    std::vector<std::string> entries;

    if (!fs::exists(folder)) {
        std::cout << "❌ Folder does not exist: " << folder << std::endl;
        return "";
    }

    // Collect folders + filtered files
    for (auto& entry : fs::directory_iterator(folder)) {

        if (entry.is_directory()) {
            entries.push_back(entry.path().string() + "/");   // add slash so it looks like folder
        }
        else if (entry.is_regular_file()) {
            std::string ext = entry.path().extension().string();
            if (!ext.empty() && ext[0] == '.') ext = ext.substr(1);

            for (auto& f : filters) {
                if (ext == f) {
                    entries.push_back(entry.path().string());
                    break;
                }
            }
        }
    }

    if (entries.empty()) {
        std::cout << "❌ No entries in folder: " << folder << std::endl;
        return "";
    }

    // GUI BUILD
    ELC::Gui gui;
    std::string selected = "";

    const float dialogW = 700;
    const float dialogH = 500;
    const float dialogX = (GetScreenWidth()  - dialogW) / 2;
    const float dialogY = (GetScreenHeight() - dialogH) / 2;

    // Scroll offset
    float scrollY = 0;

    // Build entry buttons
    int y = 150;
    for (auto& e : entries) {
        auto& btn = gui.emplace_back<ELC::Button>(
            ELC::Vec2{dialogX + 40, (float)y},
            ELC::Vec2{dialogW - 80, 40},
            e
        );

        btn.onClick = [&]() {
            // If folder (ends with '/'), open it
            if (!e.empty() && e.back() == '/') {
                std::string newFolder = e.substr(0, e.size() - 1);
        
                // Rebuild entries
                entries.clear();
                for (auto& entry : fs::directory_iterator(newFolder)) {
        
                    if (entry.is_directory()) {
                        entries.push_back(entry.path().string() + "/");
                    }
                    else if (entry.is_regular_file()) {
                        std::string ext = entry.path().extension().string();
                        if (!ext.empty() && ext[0] == '.') ext = ext.substr(1);
        
                        for (auto& f : filters) {
                            if (ext == f) {
                                entries.push_back(entry.path().string());
                                break;
                            }
                        }
                    }
                }
        
                // Clear GUI and rebuild buttons
                gui.widgets.clear();
                int y2 = 150;
                for (auto& e2 : entries) {
                    auto& btn2 = gui.emplace_back<ELC::Button>(
                        ELC::Vec2{dialogX + 40, (float)y2},
                        ELC::Vec2{dialogW - 80, 40},
                        e2
                    );
        
                    btn2.onClick = btn.onClick;  // recursive handler
        
                    y2 += 50;
                }
        
                return;
            }
        
            selected = e;
        };
        

        y += 50;
    }

    // Render loop
    while (!ELC::Core::ShouldClose() && selected.empty()) {

        // Dim background
        ELC::Core::BeginDrawing();
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Color{0,0,0,150});

        // Dialog box
        DrawRectangleRounded(
            {dialogX, dialogY, dialogW, dialogH},
            0.05f,
            8,
            Color{240,240,240,255}
        );

        // Title
        DrawText(title.c_str(), dialogX + 30, dialogY + 20, 32, BLACK);

        // Description
        DrawText(description.c_str(), dialogX + 30, dialogY + 65, 20, DARKGRAY);

        // Scroll
        float wheel = GetMouseWheelMove();
        if (wheel != 0) {
            scrollY += wheel * 20;
        }

        // Clamp scroll
        scrollY = std::min(scrollY, 0.0f);
        scrollY = std::max(scrollY, -(float)entries.size() * 50 + 300);

        // Apply scroll
        gui.SetOffsetY(scrollY);

        gui.Update();
        gui.Draw();

        ELC::Core::EndDrawing();
    }

    return selected;
}

} // namespace ELC
