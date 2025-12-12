#pragma once
#include "ELCGui.h"
#include "ELCImage.h"
#include <string>
#include <vector>
#include <functional>
#include <unordered_map>

namespace ELC {

struct FilePickerResult {
    std::string path;
    bool cancelled = true;
};

class FilePicker {
public:
    FilePicker() = default;

    FilePickerResult Open(const std::string& title,
                          const std::string& description,
                          const std::vector<std::string>& filters = {},
                          bool pickFolder = false,
                          const std::string& defaultPath = "");

private:
    std::string currentPath;
    std::vector<std::string> files;
    std::vector<std::string> folders;

    std::string inputText;
    int selectedIndex = -1;

    void RefreshDirectory();
    void DrawFilePicker(const std::string& title,
                        const std::string& description,
                        const std::vector<std::string>& filters,
                        bool pickFolder,
                        float scrollOffset,
                        float listHeight
                    );
    bool MatchFilter(const std::string& filename, const std::vector<std::string>& filters);
    void DrawIcon(const std::string& path, float x, float y, float size);

    // Cached icons
    std::unordered_map<std::string, Texture2D> iconCache;

    // Button helpers
    bool DrawButton(float x, float y, float w, float h, const std::string& text);
};

} // namespace ELC
