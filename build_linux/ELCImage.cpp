#include "ELCImage.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define CUTE_ASEPRITE_IMPLEMENTATION
#include "cute_aseprite.h"

#include <raylib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <stdint.h>

namespace ELC {

static constexpr float GIF_BASE_FPS     = 10.0f;   
static constexpr float GIF_SLOWMO_MULT  = 0.5f;    

Image::Image(const std::string& filepath) {
    Load(filepath);
}

Image::~Image() {
    if (texture.id > 0) {
        ::UnloadTexture(texture);
        std::cout << "🧹 ELC::Image UNLOADED texture.id=" << texture.id << std::endl;
    }
    for (auto& frame : frames) {
        if (frame.id > 0) ::UnloadTexture(frame);
    }
    frames.clear();
    delays.clear();
}

void Image::Load(const std::string& filepath) {
    // 🔥 CLEANUP
    if (texture.id > 0) ::UnloadTexture(texture);
    for (auto& frame : frames) if (frame.id > 0) ::UnloadTexture(frame);
    frames.clear(); delays.clear();

    isAnimated = false; currentFrame = 0; animationTimer = 0.0f; 
    frameTime = 0.0f; width = 0; height = 0; isAseprite = false; 
    numFrames = 0; animName.clear(); texture = {0};

    std::string ext = filepath.substr(filepath.find_last_of(".") + 1);
    std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);

    // 🔥 ASEPRITE + CUTE_ASEPRITE!!
    if (ext == "ase" || ext == "aseprite") {
        if (LoadAseprite(filepath)) return;
        std::cout << "⚠️ CUTE_ASEPRITE failed, PNG fallback...\n";
    }

    // 🔥 GIF
    if (ext == "gif") {
        if (LoadGif(filepath)) return;
        std::cout << "⚠️ GIF failed, PNG fallback...\n";
    }

    // 🔥 PNG/JPG FALLBACK
    ::Image img = ::LoadImage(filepath.c_str());
    if (img.data) {
        width = img.width; height = img.height;
        texture = ::LoadTextureFromImage(img);
        ::UnloadImage(img);
        std::cout << "✅ ELC::Image PNG LOADED: " << filepath
                  << " (" << width << "x" << height << ")\n";
    } else {
        std::cout << "❌ ELC::Image FAILED: " << filepath << std::endl;
    }
}

bool Image::LoadAseprite(const std::string& filepath) {
    printf("🔍 DEBUG: Loading %s...\n", filepath.c_str());
    
    ase_t* ase = cute_aseprite_load_from_file(filepath.c_str(), nullptr);
    if (!ase) {
        printf("❌ DEBUG: cute_aseprite_load_from_file FAILED!\n");
        return false;
    }

    printf("🔍 DEBUG ase_t dump:\n");
    printf("  ase->w = %d, ase->h = %d\n", ase->w, ase->h);
    printf("  ase->grid_w = %d, ase->grid_h = %d\n", ase->grid_w, ase->grid_h);
    printf("  ase->frame_count = %d\n", ase->frame_count);
    printf("  ase->mode = %d\n", ase->mode);

    width = ase->w;
    height = ase->h;
    numFrames = ase->frame_count;

    isAseprite = true;
    isAnimated = (numFrames > 1);
    frameTime = 1.0f / 12.0f;

    frames.clear();
    frames.resize(numFrames);
    
    // 🔥 REAL PIXEL BLENDING FROM cute_aseprite!
    for (int f = 0; f < numFrames; ++f) {
        ase_frame_t* frame = &ase->frames[f];
        printf("🔍 Frame %d: duration=%dms, cel_count=%d, pixels=%p\n", 
               f, frame->duration_milliseconds, frame->cel_count, (void*)frame->pixels);

        // 🔥 COPY PRE-BLENDED RGBA PIXELS DIRECTLY!
        std::vector<uint8_t> pixels((size_t)width * height * 4);
        ase_color_t* src_pixels = frame->pixels;
        
        for (int i = 0; i < width * height; ++i) {
            int idx = i * 4;
            pixels[idx + 0] = src_pixels[i].r;
            pixels[idx + 1] = src_pixels[i].g;
            pixels[idx + 2] = src_pixels[i].b;
            pixels[idx + 3] = src_pixels[i].a;
        }

        ::Image img = {0};
        img.data = pixels.data();
        img.width = width;
        img.height = height;
        img.mipmaps = 1;
        img.format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8;
        
        frames[f] = ::LoadTextureFromImage(img);
        printf("🔍 Frame %d texture.id = %u ✅\n", f, frames[f].id);

    }

 

    texture = frames.empty() ? ::Texture2D{0} : frames[0];
    cute_aseprite_free(ase);

    printf("✅FRAMES ! %d FRAMES (%dx%d) → ANIMATE! 🚀\n", 
           numFrames, width, height);
    return true;
}




bool Image::LoadGif(const std::string& filepath) {
    std::ifstream file(filepath, std::ios::binary | std::ios::ate);
    if (!file.is_open()) return false;

    auto size = file.tellg();
    file.seekg(0);
    std::vector<unsigned char> buffer(size);
    file.read((char*)buffer.data(), size);
    file.close();

    int x, y, z, comp;
    int* delays = nullptr;
    stbi_uc* data = stbi_load_gif_from_memory(buffer.data(), size, &delays, &x, &y, &z, &comp, 4);
    
    if (data && z > 0) {
        width = x; height = y; isAnimated = (z > 1);
        frameTime = 1.0f / GIF_BASE_FPS;

        frames.reserve(z);
        for (int i = 0; i < z; i++) {
            ::Image frameImg = {
                .data = data + i * x * y * 4,
                .width = x, .height = y,
                .mipmaps = 1,
                .format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8
            };
            frames.push_back(::LoadTextureFromImage(frameImg));
        }

        texture = frames[0];
        stbi_image_free(data);
        if (delays) stbi_image_free(delays);

        std::cout << "✅ GIF LOADED: " << z << " frames!\n";
        return true;
    }
    if (data) stbi_image_free(data);
    return false;
}

void Image::UpdateAnimation(float deltaTime) {
    if (!isAnimated || frames.empty()) return;
    animationTimer += deltaTime;
    if (animationTimer >= frameTime) {
        animationTimer = 0;
        currentFrame = (currentFrame + 1) % frames.size();
        texture = frames[currentFrame];
    }
}

void Image::Draw(float x, float y, ELC_Color tint) {
    if (!IsLoaded()) return;
    ::DrawTexture(texture, (int)x, (int)y, (Color){tint.r, tint.g, tint.b, tint.a});
}

void Image::DrawScaled(float x, float y, float scale, ELC_Color tint) {
    if (!IsLoaded()) return;
    ::DrawTextureEx(texture, {(float)x, (float)y}, 0, scale, (Color){tint.r, tint.g, tint.b, tint.a});
}

} // namespace ELC
