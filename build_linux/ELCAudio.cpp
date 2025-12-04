#include "ELCAudio.h"
#include <raylib.h>
#include <iostream>

namespace ELC {

Sound::Sound(const std::string& filepath) {
    sound = ::LoadSound(filepath.c_str());
    if (!IsLoaded()) {
        std::cout << "❌ ELC::Sound FAILED: " << filepath << std::endl;
        return;
    }
    std::cout << "✅ ELC::Sound LOADED: " << filepath << std::endl;
}

Sound::~Sound() {
    if (IsLoaded()) ::UnloadSound(sound);
}

void Sound::Play() {
    if (IsLoaded()) ::PlaySound(sound);
}

bool Sound::IsPlaying() const {
    return ::IsSoundPlaying(sound);
}

void Sound::Stop() {
    ::StopSound(sound);
}

Music::Music(const std::string& filepath) {
    music = ::LoadMusicStream(filepath.c_str());
    if (!IsLoaded()) {
        std::cout << "❌ ELC::Music FAILED: " << filepath << std::endl;
        return;
    }
    ::SetMusicVolume(music, 0.5f);  // Default chill volume
    std::cout << "✅ ELC::Music LOADED: " << filepath << std::endl;
}

Music::~Music() {
    if (IsLoaded()) ::UnloadMusicStream(music);
}

void Music::Play() {
    if (IsLoaded()) ::PlayMusicStream(music);
}

void Music::Pause() { if (IsLoaded()) ::PauseMusicStream(music); }
void Music::Resume() { if (IsLoaded()) ::ResumeMusicStream(music); }
void Music::Stop() { if (IsLoaded()) ::StopMusicStream(music); }

void Music::Update() {
    if (IsLoaded()) ::UpdateMusicStream(music);
}

void Music::SetVolume(float volume) {
    if (IsLoaded()) ::SetMusicVolume(music, volume);
}

bool Music::IsPlaying() const {
    return ::IsMusicStreamPlaying(music);
}

} // namespace ELC
