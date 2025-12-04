#pragma once
#include "ELCGui.h"
#include <functional>
#include <string>

namespace ELC {
    namespace Popup {
        void Alert(const std::string& message);
        
        bool PromptAnswer(const std::string& message, 
                         const std::string& yesText = "Yes", 
                         const std::string& noText = "No");
        
        std::string PromptText(const std::string& message, 
                              const std::string& placeholder = "Enter text...",
                              const std::string& confirmText = "OK");
    }
}
