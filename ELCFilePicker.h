#pragma once
#include <string>
#include <vector>
#include "ELCGui.h"   // for Gui, Button
#include "ELC.h"  // for Core::ShouldClose, BeginDrawing, etc.

namespace ELC {

// Cross-platform Raylib GUI file picker
// folder = path to open
// filters = list of file extensions, e.g., {"png","gif","ase"}
// returns the selected file path, or empty string if cancelled
std::string FilePickerGUI(const std::string& folder,
    const std::vector<std::string>& filters,
    const std::string& title,
    const std::string& description);

}
