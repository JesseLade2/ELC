#pragma once
#include "ELC.h"
#include <string>
#include <vector>

namespace ELC {
    class Image {
    public:
        std::string animName;       
        int numFrames = 0;          
        bool isAseprite = false;    

        ::Texture2D texture = {0};
        int width = 0, height = 0;
        bool isAnimated = false;
        float frameTime = 0.0f;     
        int currentFrame = 0;
        std::vector<::Texture2D> frames;
        std::vector<int> delays;          
        float animationTimer = 0.0f;
        
        Image() = default;
        Image(const std::string& filepath);
        ~Image();
        
        void Draw(float x, float y, ELC_Color tint = ELC_RAYWHITE);
        void DrawScaled(float x, float y, float scale, ELC_Color tint = ELC_RAYWHITE);
        void UpdateAnimation(float deltaTime);
        bool IsLoaded() const { return texture.id > 0 || !frames.empty(); }
        void Load(const std::string& filepath);
        
    private:
        bool LoadGif(const std::string& filepath);
        bool LoadAseprite(const std::string& filepath);
    };
}
