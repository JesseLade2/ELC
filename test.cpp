#include "ELC.h"
#include "ELCFilePicker.h"
#include <iostream>

int main() {
    if (!ELC::Core::Init(800, 600, "🎉 ELC File Picker GUI")) return 1;
    std::string file = ELC::FilePickerGUI(".", {"png","gif","ase"});
    if (!file.empty()) {
        std::cout << "Selected file: " << file << std::endl;
    }

    ELC::Core::Close();
    return 0;
}
