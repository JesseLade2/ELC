#include "ELCFilePicker.h"
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

namespace ELC {

std::string FilePickerGUI(const std::string& folder,
                          const std::vector<std::string>& filters) {
    std::vector<std::string> files;

    if (!fs::exists(folder)) {
        std::cout << "❌ Folder does not exist: " << folder << std::endl;
        return "";
    }

    // Collect files matching filters
    for (auto& entry : fs::directory_iterator(folder)) {
        if (entry.is_regular_file()) {
            std::string ext = entry.path().extension().string();
            if (!ext.empty() && ext[0] == '.') ext = ext.substr(1);

            for (auto& f : filters) {
                if (ext == f) {
                    files.push_back(entry.path().string());
                    break;
                }
            }
        }
    }

    if (files.empty()) {
        std::cout << "❌ No files found in folder: " << folder << std::endl;
        return "";
    }

    // Create GUI
    ELC::Gui gui;
    std::string selectedFile;

    int y = 50;
    for (auto& file : files) {
        auto& btn = gui.emplace_back<ELC::Button>(
            ELC::Vec2{50.0f, (float)y},   // position
            ELC::Vec2{600.0f, 40.0f},     // size
            file                          // label (std::string or const char* depending on constructor)
        );
        
        btn.onClick = [&selectedFile, &file]() {
            selectedFile = file;
        };
        y += 50;
    }

    // Render loop until a file is selected or window closed
    while (!ELC::Core::ShouldClose() && selectedFile.empty()) {
        ELC::Core::BeginDrawing();
        ELC::Core::ClearBackground(ELC::ELC_RAYWHITE);

        gui.Update();
        gui.Draw();

        ELC::Core::EndDrawing();
    }

    return selectedFile;
}

} // namespace ELC
